#include "ADC_Device.h"

#pragma region GettersAndSetters
inline const float ADC7828_Device::GetVRef()
{
   return vRef;
}

inline const uint8_t ADC7828_Device::GetRes()
{
   return resolution;
}

inline const float ADC7828_Device::GetVoltDivCoef()
{
   return voltDivCoef;
}

inline const uint8_t ADC7828_Device::GetAddress()
{
   return address;
}

inline void ADC7828_Device::SetPinConfig(uint8_t pinRegister)
{
	pinConfig = pinRegister;
}

inline uint8_t ADC7828_Device::GetPinConfig()
{
	return pinConfig;
}
#pragma endregion

/**
* @brief  Gets adc data from ADS7828
* @param  address ADS7828 address set by A0 and A1 pins(default:00 = 0x48)
* @param  pinCfg configuration of SD and C[2..0] bits for
* 				input pin selection
* 				SD: 0 for differential, 1 for single ended
* 				C[2..0] input pin configuration
* 				by default, internal reference and ADC is turned on(bits PD[1..0])
* @param	adcData pointer to target memory for adc data
* @retval HAL status
*/
HAL_StatusTypeDef ADC7828_Device::ReadADC(uint16_t *data)
{
	HAL_StatusTypeDef returnVal;
	uint8_t adData[2]; // data to receive

	// Send configuration register data
	returnVal = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(address<<1), &pinConfig, 1, 50); // 0, cuz we are transmitting
	if(returnVal != HAL_OK)
	{
		return returnVal; //return an error
	}

	// Receive voltage data, two bytes
	returnVal = HAL_I2C_Master_Receive(&hi2c1, (uint16_t)(address<<1)|0x01, adData, 2, 50); // (| 0x01), cuz we are receiving
	if(returnVal != HAL_OK)
	{
		return returnVal;
	}

	// Assemble adc reading data from two bytes
	*data = ((adData[0] & 0x0F) << 8) | adData[1]; // combine 2 bytes and remove 4 zeros
	return HAL_OK;
}

/**
* @brief  Convert adc 16bit value to float voltage
* @param	vref reference voltage of adc(internal?)
* @param  adcval  value of adc to convert
* @param  voltage converted adc value
* @retval HAL status
*/
void ADC7828_Device::ADC_ToVolt(uint16_t value, float *voltage)
{
	*voltage = value * vRef / (float)((1<< resolution) -1); //formula for adc(s)
}
