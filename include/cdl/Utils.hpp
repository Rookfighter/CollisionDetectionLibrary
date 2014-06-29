#ifndef CDL_UTILS_HPP
#define CDL_UTILS_HPP

#include <cstdio>

#define PRINT_INFO(msg, ...) printf(msg, ##__VA_ARGS__)

namespace cdl
{
	bool equal(const float p_op1, const float p_op2, const unsigned int p_precision);
}

#endif