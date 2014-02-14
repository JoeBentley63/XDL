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