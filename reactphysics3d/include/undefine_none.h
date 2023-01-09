//https://github.com/OneLoneCoder/olcPixelGameEngine/issues/195
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// The header <X11/X.h> defines "None" as a macro that expands to "0L".
// This is terrible because many enumerations have an enumerator named "None".
// To work around this, we undefine the macro "None", and define a replacement
// macro named "X11None".
// Include this header after including X11 headers, where necessary.

#ifndef undefine_none
#define undefine_none

#if defined(DM_PLATFORM_LINUX)


#ifdef None
#  undef None
#  define X11None 0L
#  ifdef RevertToNone
#    undef RevertToNone
#    define RevertToNone (int)X11None
#  endif
#endif

#endif

#endif