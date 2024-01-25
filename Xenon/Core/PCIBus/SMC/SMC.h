#pragma once

#include <vector>
#include <iostream>

#include "Xenon/Core/PCIBus/PCIDevice.h"

#define SMC_START_ADDR	0x200EA001000
#define SMC_END_ADDR	0x200EA001100

class SMC : public PCIDevice
{
public:
	void Read(u64 readAddress, u64* data, u8 byteCount) override;
	void Write(u64 writeAddress, u64 data, u8 byteCount) override;

private:
	void smcProcessRead(u64 readAddress, u64* data, u8 byteCount);
	void smcProcessWrite(u64 writeAddress, u64 data, u8 byteCount);
	
	//
	// FIFO Queue
	//
	void smcFIFOProcessRead(u64 readAddress, u64* data, u8 byteCount);
	void smcFIFOProcessWrite(u64 writeAddress, u64 data, u8 byteCount);
	u8 fifoWriteReg = 0x4;
	u8 fifoReadReg = 0;
	u8 fifoWrittenMsg[16] = { 0 };
	u8 currentWritePos = 0;
	u8 fifoReadedMsg[16] = { 0 };
	u8 currentReadPos = 0;

	//
	// UART stuff.
	//
	void uartWrite(u64 writeAddress, u64 data, u8 byteCount);
	void uartRead(u64 readAddress, u64* data, u8 byteCount);
	// UART Status Register.
	u32 uartStatus = 0;
	// Character buffer for UART output.
	std::string uartDataStr = "";
};