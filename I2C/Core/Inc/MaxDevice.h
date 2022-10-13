#pragma once

#include "main.h"
#include "DevicesInterface.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_def.h"

extern I2C_HandleTypeDef hi2c1;

class Max30205_Device : public DevicesInterface
{
private:
const uint8_t address = 0x90;

public:
const uint8_t GetAddress() override;
void SetPinConfig(uint8_t pinRegister)override;
uint8_t GetPinConfig() override;

// Get temperature from MAX30205
HAL_StatusTypeDef MaxReadTemp(float *temp);
};
