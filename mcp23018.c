#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "mcp23018.h"

bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;
    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init(); // on pins D(1,0)
        i2c_initialized++;
        _delay_ms(1000);
    }
    // set pin direction
    // - unused : input : 1
    // - input : input : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111); if (mcp23018_status) goto out;
    i2c_stop();
    // set pull-up
    // - unused : on : 1
    // - input : on : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111); if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000); if (mcp23018_status) goto out;
out:
    i2c_stop();
    return mcp23018_status;
}
