/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@devolution.com
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_NDSevents_c.h,v 1.1 2001/04/26 16:50:18 hercules Exp $";
#endif

#include "SDL_ndsvideo.h"

/* Variables and functions exported by SDL_sysevents.c to other parts 
   of the native video subsystem (SDL_sysvideo.c)
*/
extern void NDS_InitOSKeymap(_THIS);
extern void NDS_PumpEvents(_THIS);

#define NDS_NUMKEYS 12

/*
#define NDS_JOYPADREG 0x4000130
#define NDS_JOYPAD (*(volatile Uint16*)NDS_JOYPADREG)

#define NDS_NUMKEYS 10
#define NDS_KEYA (0)
#define NDS_KEYB (1)
#define NDS_KEYSEL (2)
#define NDS_KEYSTART (3)
#define NDS_KEYRIGHT (4)
#define NDS_KEYLEFT (5)
#define NDS_KEYUP (6)
#define NDS_KEYDOWN (7)
#define NDS_KEYR (8)
#define NDS_KEYL (9)
*/
/* end of SDL_NDSevents_c.h ... */

