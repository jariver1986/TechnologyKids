#include <stdint.h>
#include <stdio.h>
#include "STM32F429xx.h"

typedef struct
{
    volatile uint32_t reg_value;
    char name[10];
} Register;

typedef struct
{
    Register RCC;
    Register GPIO;
    Register GPIOG_ON;
    Register GPIOG_OFF;
    Register UART;
    Register I2C;
    Register SPI;
    Register OTHER;
} DeviceRegisters;

DeviceRegisters device = {
    .RCC   = {0b00000000000000000000000001000000, "RCC"},  // AHB1ENR
    .GPIO  = {0b00000000001010000000000000000000, "GPIO"}, // MODER
    .GPIOG_ON  = {0b00000000000000000110000000000000, "GPIO-ON"}, // Pines encendidos
    .GPIOG_OFF = {0b00000000000000000000000000000000, "GPIO-OFF"}, // Pines apagados
    .UART  = {0b00000000000000000000000000000001, "UART"},
    .I2C   = {0b00000000000000000000000000000100, "I2C"},
    .SPI   = {0b00000000000000000000000001000000, "SPI"},
    .OTHER = {0b10000000000000000000000000000000, "OTHER"}
};

void set_register(Register *reg, uint32_t value)
{
    reg->reg_value = value;
    // printf("Registro %s actualizado: 0x%08X\n", reg->name, reg->reg_value);
}

int main(void)
{
    set_register(&device.RCC, device.RCC.reg_value);
    set_register(&device.GPIO, device.GPIO.reg_value);

    while(1)
    {
        set_register(&device.GPIOG_ON, device.GPIOG_ON.reg_value);
        for (volatile int var = 0; var < 100000; ++var) {}

        set_register(&device.GPIOG_OFF, device.GPIOG_OFF.reg_value);
        for (volatile int var = 0; var < 100000; ++var) {}
    }
}
