#ifndef MCP23018_H
#define MCP23018_H

#include <stdint.h>
#include "i2cmaster.h"

// Much more defined in sample file: https://github.com/cub-uanic/tmk_keyboard/blob/cub_layout/keyboard/ergodox/ergodox.h

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR 0b0100000
#define I2C_ADDR_WRITE ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ ( (I2C_ADDR<<1) | I2C_READ )
#define IODIRA 0x00 // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C // GPIO pull-up resistor register
#define GPPUB 0x0D
#define GPIOA 0x12 // general purpose i/o port register (write modifies OLAT)
#define GPIOB 0x13

extern uint8_t mcp23018_status;

uint8_t init_mcp23018(void);

#endif
