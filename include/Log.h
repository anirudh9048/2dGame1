#include <iostream>
#ifdef LOG_ENABLED
#define LOG_LEVEL "INFO"
#define LOG(x) std::cout << "\033[1;32m" << LOG_LEVEL << "| " << x << "\033[0m" << std::endl
#else
#endif