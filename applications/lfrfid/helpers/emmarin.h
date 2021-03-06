#pragma once
#include <stdint.h>

#define EM_HEADER_POS 55
#define EM_HEADER_MASK (0x1FFLLU << EM_HEADER_POS)

#define EM_FIRST_ROW_POS 50
#define EM_ROW_COUNT 10

#define EM_COLUMN_POS 4
#define EM_STOP_POS 0
#define EM_STOP_MASK (0x1LLU << EM_STOP_POS)

#define EM_HEADER_AND_STOP_MASK (EM_HEADER_MASK | EM_STOP_MASK)
#define EM_HEADER_AND_STOP_DATA (EM_HEADER_MASK)
