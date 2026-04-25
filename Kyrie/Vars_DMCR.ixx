export module Vars_DMCR;

import Core;

#include "../Core/Macros.h"



export namespaceStart(DMCRAddressList);
enum
{
	uint32_t baseGameAddress = 0x400000;
	uint32_t mediatorAddressOffset = 0xa59f00;
	uint32_t mediatorAddress = baseGameAddress + mediatorAddress; // 0x400000 + 0xa59f00 = 

	uint32_t playerBaseAddress = mediatorAddress + 0x24;
};
namespaceEnd();