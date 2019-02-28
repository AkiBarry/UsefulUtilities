#pragma once
#include "UU.hpp"
#include <cstdint>

template <class T, size_t size_of_state /* = 4 */>
class UU::CRandom
{
private:
	union
	{
		uint8_t		data_8[size_of_state]		= {};
		uint16_t	data_16[size_of_state / 2]	= {};
		uint32_t	data_32[size_of_state / 4]	= {};
		uint64_t	data_64[size_of_state / 8]	= {};
	};
public:

};
