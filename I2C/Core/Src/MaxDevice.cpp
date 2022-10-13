#include "MaxDevice.h"

extern I2C_HandleTypeDef hi2c1;

#pragma region GettersAndSetters

const uint8_t Max30205_Device::GetAddress()
{
   return address;
}

void Max30205_Device::SetPinConfig(uint8_t pinRegister)
{
	pinConfig = pinRegister;
}

uint8_t Max30205_Device::GetPinConfig()
{
	return pinConfig;
}

#pragma endregion

/**
* @brief  Get temperature from MAX30205
* @param  dev_address MAX30205 address set by A0,A1, A2 pins
* 				datasheet provides 8bit address, therefore no need
* 				to left shift in i2c functions (default=000 or 0x90 = (0x48 <<1))
* @param  config configuration register for MAX30205 (size 8b)
* 				configuration register address is 0x01
* @param	temp pointer to target memory for temperature data
* @retval HAL status
*/

HAL_StatusTypeDef Max30205_Device::MaxReadTemp(float *temp)
{
	HAL_StatusTypeDef returnValue;
	uint8_t tempData[2];

	// Send configuration, reg 1
	returnValue = HAL_I2C_Mem_Write(&hi2c1, static_cast<uint16_t>(address), 0x01, 1, &pinConfig, 1, 50);
	if(returnValue != HAL_OK)
	{
		return returnValue;
	}

	// Get temperature data, reg 0, two bytes
    returnValue = HAL_I2C_Mem_Read(&hi2c1, static_cast<uint16_t>(address), 0x00, 1, tempData, 2, 50);
	if(returnValue != HAL_OK)
	{
		return returnValue;
	}

	// Convert to temperature
	// Datasheet shows that digits are powers of two in temperature degree C
	*temp = ( (tempData[0] << 8) | tempData[1]) *0.00390625;

	return HAL_OK;
}
