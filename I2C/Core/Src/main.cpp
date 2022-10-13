
#include "main.h"

#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_conf.h"

#include "DevicesInterface.h"
#include "MaxDevice.h"
#include "ADC_Device.h"
#include "PinRegisters.h"

void SystemClock_Config(void);

inline void SetDevPinConfig(DevicesInterface* device, uint8_t pinRegister)
{
    device->SetPinConfig(pinRegister);
}

int main(void)
{
  HAL_Init();

//HAL_GPIO_Init();
//HAL_I2C_Init();

  uint16_t adData = 0; //store a 12 bit value
  float voltage = 0; // store a converted adc val
  float temperature = 0 ;

  float voltDivCoef = 1.0f;

  ADC7828_Device* adcDevice = new ADC7828_Device;
  Max30205_Device* maxDevice = new  Max30205_Device;

  while (1)
  {
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	HAL_Delay(500);

	SetDevPinConfig(adcDevice, pinReg.ADC7828);
	adcDevice->ReadADC(&adData);

	adData *= voltDivCoef; // voltage divider

	adcDevice->ADC_ToVolt(adData, &voltage);

	SetDevPinConfig(maxDevice, pinReg.Max30205);
	maxDevice->MaxReadTemp(&temperature);

  	HAL_Delay(100);
  }

  delete adcDevice;
  delete maxDevice;
}

//default generated code
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
