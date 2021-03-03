#include <api-hal-i2c.h>

#include <stm32wbxx_ll_bus.h>
#include <stm32wbxx_ll_i2c.h>
#include <stm32wbxx_ll_rcc.h>
#include <stm32wbxx_ll_gpio.h>

void api_hal_i2c_init() {
    LL_I2C_InitTypeDef I2C_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    GPIO_InitStruct.Pin = POWER_I2C_SCL_Pin | POWER_I2C_SDA_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

    I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
    I2C_InitStruct.Timing = POWER_I2C_TIMINGS;
    I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
    I2C_InitStruct.DigitalFilter = 0;
    I2C_InitStruct.OwnAddress1 = 0;
    I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
    I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
    LL_I2C_Init(I2C1, &I2C_InitStruct);
    LL_I2C_EnableAutoEndMode(I2C1);
    LL_I2C_SetOwnAddress2(I2C1, 0, LL_I2C_OWNADDRESS2_NOMASK);
    LL_I2C_DisableOwnAddress2(I2C1);
    LL_I2C_DisableGeneralCall(I2C1);
    LL_I2C_EnableClockStretching(I2C1);
}

void api_hal_i2c_tx(I2C_TypeDef* instance, uint8_t address, const uint8_t* data, uint8_t size) {
    LL_I2C_HandleTransfer(
        instance,
        address,
        LL_I2C_ADDRSLAVE_7BIT,
        size,
        LL_I2C_MODE_AUTOEND,
        LL_I2C_GENERATE_START_WRITE);

    while(!LL_I2C_IsActiveFlag_STOP(instance)) {
        if(LL_I2C_IsActiveFlag_TXIS(instance)) {
            LL_I2C_TransmitData8(instance, (*data++));
        }
    }

    LL_I2C_ClearFlag_STOP(instance);
}

void api_hal_i2c_rx(I2C_TypeDef* instance, uint8_t address, uint8_t* data, uint8_t size) {
    LL_I2C_HandleTransfer(
        instance,
        address,
        LL_I2C_ADDRSLAVE_7BIT,
        size,
        LL_I2C_MODE_AUTOEND,
        LL_I2C_GENERATE_START_READ);

    while(!LL_I2C_IsActiveFlag_STOP(instance)) {
        if(LL_I2C_IsActiveFlag_RXNE(instance)) {
            *data++ = LL_I2C_ReceiveData8(instance);
        }
    }

    LL_I2C_ClearFlag_STOP(instance);
}

void api_hal_i2c_trx(
    I2C_TypeDef* instance,
    uint8_t address,
    const uint8_t* tx_data,
    uint8_t tx_size,
    uint8_t* rx_data,
    uint8_t rx_size) {
    api_hal_i2c_tx(instance, address, tx_data, tx_size);
    api_hal_i2c_rx(instance, address, rx_data, rx_size);
}
