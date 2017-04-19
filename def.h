/***************************************************************************/
/*                                                                         */
/*  Def.h                                                                  */
/*                                                                         */
/*    Include some ordinary header files for the app                       */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/
#ifndef _DEF_H_
#define _DEF_H_

#include "AEEModGen.h"          
#include "AEEAppGen.h"          
#include "AEEShell.h"           
#include "AEEFile.h"			
#include "AEEDB.h"				
#include "AEENet.h"				
#include "AEESound.h"			
#include "AEETapi.h"			

#include "AEEStdLib.h"
#include "AEEGraphics.h"

#include "NewEnuos.bid"

void* operator new(size_t size);

void operator delete(void* p);

#endif