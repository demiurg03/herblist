#pragma once
#define HL_IS_DEBUG 1


#if HL_IS_DEBUG == 1

constexpr bool gv_isDebug = true;

#else

constexpr bool gv_isDebug = false;

#endif
