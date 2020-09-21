#pragma once

#ifdef _DEBUG
#define DEBUG_PRINT_VAR(x) do { std::cerr << #x << " : " << x << " on line " << __LINE__ <<  " in func " << __func__ << std::endl; } while (0)
#define DEBUG_PRINT_VAR_WITH_FILE(x) do { std::cerr << #x << " : " << x << " on line " << __LINE__ <<  " in func " __func__ <<  " in file " __FILE__ << std::endl; } while (0)
#define PRINT(x) do { std::cout << x << std::endl;} while(0) 
#else
#define DEBUG_PRINT_VAR(x) while(0){}
#define DEBUG_PRINT_VAR_WITH_FILE(x) while(0){}
#define PRINT(x) while(0){}
#endif