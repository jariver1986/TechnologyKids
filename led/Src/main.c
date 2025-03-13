/**
 * @file main.c
 * @brief Ejemplo de manejo de registros en STM32F429 utilizando estructuras.
 * @author [Tu Nombre]
 * @date 2025
 */

#include <stdint.h>
#include <stdio.h>
#include "STM32F429xx.h"

/**
 * @struct Register
 * @brief Estructura que representa un registro con su valor y nombre.
 */
typedef struct
{
    volatile uint32_t reg_value; /**< Valor del registro */
    char name[10];               /**< Nombre del registro */
} Register;

/**
 * @struct DeviceRegisters
 * @brief Estructura que representa los registros del dispositivo.
 */
typedef struct
{
    Register RCC;       /**< Registro RCC (AHB1ENR) */
    Register GPIO;      /**< Registro GPIO (MODER) */
    Register GPIOG_ON;  /**< Registro GPIOG_ON (Pines encendidos) */
    Register GPIOG_OFF; /**< Registro GPIOG_OFF (Pines apagados) */
    Register UART;      /**< Registro UART */
    Register I2C;       /**< Registro I2C */
    Register SPI;       /**< Registro SPI */
    Register OTHER;     /**< Registro OTHER */
} DeviceRegisters;

/**
 * @brief Instancia de registros del dispositivo con valores iniciales.
 */
DeviceRegisters device = {
    .RCC   = {0b00000000000000000000000001000000, "RCC"},  /**< AHB1ENR */
    .GPIO  = {0b00000000001010000000000000000000, "GPIO"}, /**< MODER */
    .GPIOG_ON  = {0b00000000000000000110000000000000, "GPIO-ON"}, /**< Pines encendidos */
    .GPIOG_OFF = {0b00000000000000000000000000000000, "GPIO-OFF"}, /**< Pines apagados */
    .UART  = {0b00000000000000000000000000000001, "UART"},
    .I2C   = {0b00000000000000000000000000000100, "I2C"},
    .SPI   = {0b00000000000000000000000001000000, "SPI"},
    .OTHER = {0b10000000000000000000000000000000, "OTHER"}
};

/**
 * @brief Establece un nuevo valor para un registro.
 * @param reg Puntero a la estructura de registro.
 * @param value Nuevo valor del registro.
 */
void set_register(Register *reg, uint32_t value)
{
    reg->reg_value = value;
    // printf("Registro %s actualizado: 0x%08X\n", reg->name, reg->reg_value);
}

/**
 * @brief Función principal del programa.
 * @return int Código de retorno (0 si se ejecuta correctamente).
 */
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
