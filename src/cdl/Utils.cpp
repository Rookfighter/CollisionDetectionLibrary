#include "cdl/Utils.hpp"
#include <cmath>

namespace cdl
{
	bool equal(const float p_op1, const float p_op2, const unsigned int p_precision)
	{
		if(p_precision == 0)
			return ((int) p_op1) == ((int) p_op2);
		float absoluteError = 1;
		for(int i = 0; i< p_precision; ++i)
			absoluteError *= 0.1;
		float relativeError = std::abs((p_op1 - p_op2) / p_op2);
		return relativeError <= absoluteError;
	}
}