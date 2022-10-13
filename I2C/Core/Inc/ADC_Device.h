#pragma once

#include "main.h"
#include "DevicesInterface.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_def.h"

extern I2C_HandleTypeDef hi2c1;

class ADC7828_Device : public DevicesInterface
{
private:
const float vRef = 2.492; //internal volt ref
const uint8_t resolution = 12;
const uint8_t address = 0x49; //left-shifted address

//getters/setters
public:
const float GetVRef();
const uint8_t GetRes();

const uint8_t GetAddress() override;
void SetPinConfig(uint8_t pinRegister)override;
uint8_t GetPinConfig() override;

// Get ADC data from ADS7828
HAL_StatusTypeDef ReadADC(uint16_t *data);

// Convert ADC data to millivolts
void ADC_ToVolt(uint16_t value, float *voltage);
};

