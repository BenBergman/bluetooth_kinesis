/*
Copyright 2014 Benjamin Bergman <ben@benbergman.ca>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



/*
 * THE PLAN
 *
 * PORTB is all pin change interrupts. Use for the 8 rows (needed for power
 * saving mode).
 * PORTD3:0 and PORTE6 are interrupts. Save for joystick and potential IO
 * expander (needed for power saving mode).
 * PORTD3:2 are UART Rx/Tx. Use for bluetooth module.
 * PORTD1:0 are TWI(I2C). Use for joystick and potential IO expander data.
 * PORTD7:6,4 and PORTF7:4,1:0 are ADCs. Save one for battery meter.
 *
 * Total Pins
 * PORTB0 - row 0
 * PORTB1 - row 1
 * PORTB2 - row 2
 * PORTB3 - row 3
 * PORTB4 - row 4
 * PORTB5 - row 5
 * PORTB6 - row 6
 * PORTB7 - row 7
 *
 * PORTC6 - col 6
 * PORTC7 - col 7
 *
 * PORTD0 - I2C SCL (EasyPoint/IO expander/etc)
 * PORTD1 - I2C SDA(EasyPoint/IO expander/etc)
 * PORTD2 - UART RXD (WT12)
 * PORTD3 - UART TXD (WT12)
 * PORTD4 - ADC? EasyPoint button?
 * PORTD5 - col 8
 * PORTD6 - col 9
 * PORTD7 - col 10
 *
 * old plan, can't do with adafruit board -> PORTE2 - col 11
 * old plan, can't do with adafruit board -> PORTE6 - INT6 (EasyPoint)
 *
 * PORTE2 - HWB
 * PORTE6 - col 11
 *
 * PORTF0 - col 0
 * PORTF1 - col 1
 * PORTF4 - col 2
 * PORTF5 - col 3
 * PORTF6 - col 4
 * PORTF7 - col 5
 *
 * Future changes:
 * - Move WT12 to an I2C to UART adapter to free two interrupt pins.
 * - Move EasyPoint button to interrupt pin
 * - Add battery monitor to ADC input (formerly EasyPoint button)
 * - Add I2C IO expander either for LEDs or for second half of matrix
 *
 * Alternate plan:
 * - Switch to AT90USB1286 for additional pins
 */



/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "mcp23018.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // initialize row and col

    mcp23018_status = init_mcp23018();
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    // TODO: fix mcp23018_status errors...?
    if (mcp23018_status) { // if there was an error
        if (++mcp23018_reset_loop == 0) {
            // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        matrix_row_t cols = read_cols(i);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 *
 * 32u4
 * col: 0   1   2   3   4   5   6   7
 * pin: B0  B1  B2  B3  B4  B5  D6  B7
 *
 * MCP23018
 * col: 0   1   2   3   4   5   6   7
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  = 0x00;
    PORTB = 0xFF;

    // TODO: init mcp23018
}

static matrix_row_t read_cols(uint8_t row)
{
    if (row < 6) {
        _delay_us(30);  // without this wait read unstable value.
        return ~PINB;
    } else {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA);             if (mcp23018_status) goto out;
            mcp23018_status = i2c_start(I2C_ADDR_READ);     if (mcp23018_status) goto out;
            data = i2c_readNak();
            data = ~data;
out:
            i2c_stop();
            return data;
        }
    }
}

/* Row pin configuration
 * row: 0  1  2  3  4  5
 * pin: F0 F1 F4 F5 F6 F7
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRF  &= ~0b11110011; // PF: 7,6,5,4,1,0
    PORTF &= ~0b11110011;

    if (!mcp23018_status) {
        mcp23018_status = i2c_start(I2C_ADDR_WRITE); if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(IODIRB); if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(0b11111111); if (mcp23018_status) goto out;
out:
        i2c_stop();
    }
}

static void select_row(uint8_t row)
{
    if (row < 6) {
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 0:
                DDRF  |= (1<<0);
                PORTF &= ~(1<<0);
                break;
            case 1:
                DDRF  |= (1<<1);
                PORTF &= ~(1<<1);
                break;
            case 2:
                DDRF  |= (1<<4);
                PORTF &= ~(1<<4);
                break;
            case 3:
                DDRF  |= (1<<5);
                PORTF &= ~(1<<5);
                break;
            case 4:
                DDRF  |= (1<<6);
                PORTF &= ~(1<<6);
                break;
            case 5:
                DDRF  |= (1<<7);
                PORTF &= ~(1<<7);
                break;
        }
    } else {
        if (!mcp23018_status) {
            mcp23018_status = i2c_start(I2C_ADDR_WRITE); if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(IODIRB); if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(0xFF & ~(1<<(row - 6))); if (mcp23018_status) goto out;
            i2c_stop();
            mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOB);             if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(0xFF & ~(1<<(row - 6))); if (mcp23018_status) goto out;
out:
            i2c_stop();
        }
    }
}
