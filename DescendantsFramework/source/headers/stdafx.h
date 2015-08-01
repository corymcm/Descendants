#include <iostream>

#ifdef _MSC_VER
	#define DEBUG_BREAK __debugbreak()
#else
	#define DEBUG_BREAK
#endif

// Logs a message to the console window
#define LogError(message) std::cout << message << std::endl;

// Logs an error with additional information.
#define LogErrorAdditional(message, args) std::cout << message << args  << std::endl;

#define DESCENDANT_UNUSED(x) (void)(x)

#ifdef _DEBUG 
	// Breaks when x is a null pointer, in debug this will break at the check. Release will print to the console with the variable name.
#define ASSERT(x) if(x == nullptr) { LogErrorAdditional("Assert Error: ", #x); DEBUG_BREAK; }
#else
	#define ASSERT(x) if(x == nullptr) LogErrorAdditional("Assert Error: ", #x); 
#endif

#ifdef DESCENDANT_DLL
#define DESCENDANT_EXPORT __declspec(dllexport)
#else
#define DESCENDANT_EXPORT __declspec(dllimport)
#endif