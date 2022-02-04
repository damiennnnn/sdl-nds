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
 "@(#) $Id: SDL_ndsvideo.h,v 1.1 2001/04/26 16:50:18 hercules Exp $";
#endif

#ifndef _SDL_ndsvideo_h
#define _SDL_ndsvideo_h

#include "SDL_mouse.h"
#include "SDL_sysvideo.h"
#include "SDL_mutex.h"

/* Hidden "this" pointer for the video functions */
#define _THIS	SDL_VideoDevice *this


/* Private display data */

struct SDL_PrivateVideoData {
    int w, h;
    void *buffer;
    short ndsmode;
    short secondbufferallocd;
};

/*
#define NDS_VIDC_BASE 0x4000000
#define NDS_DISPCNT (*(volatile Uint32*)(NDS_VIDC_BASE))
#define NDS_VIDC_SCANLINE (NDS_VIDC_BASE+6)
#define NDS_SCANLINE (*(volatile Uint8*)(NDS_VIDC_SCANLINE))

#define NDS_DISP_MODE(n) (n&7)
#define NDS_DISP_BG2 0x400
#define NDS_DISP_FB 0x10

#define NDS_PAL_BASE 0x5000000
#define NDS_BGPAL ((volatile Uint16*)(NDS_PAL_BASE))
#define NDS_OBJPAL ((volatile Uint16*)(NDS_PAL_BASE+0x200))

#define NDS_VRAM_BASE 0x6000000
#define NDS_VRAM_2NDBUF 0x600a000
#define NDS_VRAM = ((volatile Uint16* )NDS_VRAM_BASE)
*/
#endif /* _SDL_ndsvideo_h */
