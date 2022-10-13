#pragma once
#include <cstdint>

class DevicesInterface
{
protected:
	uint8_t pinConfig; //config register

public:
	virtual const uint8_t GetAddress() = 0;

	virtual void SetPinConfig(uint8_t pinRegister) = 0;
	virtual uint8_t GetPinConfig() = 0;
};
