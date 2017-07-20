#pragma once

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define newp new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define newp new
#endif