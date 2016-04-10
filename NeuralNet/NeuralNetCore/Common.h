#pragma once
#ifdef _DEBUG
#define DPRINTF(s) std::cout<<s<<std::endl
#else
#define DPRINTF(s)
#endif