/*-----------------------------------------------------------

   eiLiblary
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiClass.h ...Define Class

-----------------------------------------------------------*/

#ifndef EICLASS
#define EICLASS


#ifdef EIUSE_FILE
	#include "eiFile.h"
#endif

#ifdef EIUSE_BITSTREAM
	#include "eiBitStream.h"
#endif

#ifdef EIUSE_TIME
	#include "eiTime.h"
#endif

#ifdef EIUSE_SOUND
	#include "eiSound.h"
#endif

#ifdef EIUSE_DIRECTDRAW
	#include "eiDDraw.h"
#endif

#ifdef EIUSE_DIB
	#include "eiDib.h"
#endif

#ifdef EIUSE_CELL
	#include "eiCell.h"
#endif

#ifdef EIUSE_DIRECT3D
	#include "eiD3D.h"
#endif

#ifdef EIUSE_PALETTE
	#include "eiPal.h"
#endif

#ifdef EIUSE_INPUT
	#include "eiInput.h"
#endif

#ifdef EIUSE_WINDOW
	#include "eiWindow.h"
#endif

#ifdef EIUSE_SCRIPT
	#include "eiScript.h"
#endif

#endif /* EICLASS */
