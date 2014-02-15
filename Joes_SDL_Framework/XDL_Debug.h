//!XDL_Debug
/*!
Wraps Cout, so you dont have to use COUT in your code, you can use DEBUG_MSG. turning DEBUG to 0 turns off all DEBUG_MSG outputs
*/


#ifndef DEBUG
#undef DEBUG
#endif

#define DEBUG 1

#if defined DEBUG 
    #if (DEBUG == 1)
		#include <iostream>
		#define  DEBUG_MSG(x) (std::cout << x << std::endl);
	#else
		#define DEBUG_MSG(x)
	#endif
#else
	#define DEBUG_MSG(x)
#endif