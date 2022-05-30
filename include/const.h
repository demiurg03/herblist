/**
 *
 *  @file const.h.in
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */


#pragma once
#define HL_IS_DEBUG 1


#if HL_IS_DEBUG == 1

constexpr bool gv_isDebug = true;

#else

constexpr bool gv_isDebug = false;

#endif
