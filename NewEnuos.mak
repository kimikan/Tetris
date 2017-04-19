#============================================================================
#  Name:
#    $(TARGET).MAK
#
#  Description:
#    Makefile to build the $(TARGET) downloadable module.
#
#   The following nmake targets are available in this makefile:
#
#     all           - make .elf and .mod image files (default)
#     clean         - delete object directory and image files
#     filename.o    - make object file
#
#   The above targets can be made with the following command:
#
#     nmake /f $(TARGET).mak [target]
#
#  Assumptions:
#    1. The environment variable ADSHOME is set to the root directory of the
#       arm tools.
#    2. The version of ADS is 1.2 or above.
#
#  Notes:
#    None.
#
#
#        Copyright © 2000-2001 QUALCOMM Incorporated.
#               All Rights Reserved.
#            QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#============================================================================
ARM_HOME       =$(ARMHOME)
BREW_HOME      =$(BREWDIR)
TARGET         =NewEnuos
OBJS           =AEEAppGen.o AEEModGen.o Box.o Canvas.o Shape.o Color.o NewEnuos.o 
APP_INCLUDES   = -I "$(BREWDIR)\inc"

#-------------------------------------------------------------------------------
# Target file name and type definitions
#-------------------------------------------------------------------------------

EXETYPE    = elf                # Target image file format
MODULE     = mod                # Downloadable module extension

#-------------------------------------------------------------------------------
# Target compile time symbol definitions
#
# Tells the SDK source stuffs that we're building a dynamic app.
#-------------------------------------------------------------------------------

DYNAPP          = -DDYNAMIC_APP


#-------------------------------------------------------------------------------
# Software tool and environment definitions
#-------------------------------------------------------------------------------

AEESRCPATH = $(BREW_HOME)\src
AEEINCPATH = $(BREW_HOME)\inc

ARMBIN = $(ARM_HOME)\bin        # ARM ADS application directory
ARMINC = $(ARM_HOME)\include    # ARM ADS include file directory
ARMLIB = $(ARM_HOME)\lib        # ARM ADS library directory

ARMCC    = $(ARMBIN)\armcc      # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
ARMCPP   = $(ARMBIN)\armcpp     # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
LD       = $(ARMBIN)\armlink     # ARM ADS linker
HEXTOOL  = $(ARMBIN)\fromelf     # ARM ADS utility to create hex file from image

OBJ_CMD    = -o                 # Command line option to specify output filename

#-------------------------------------------------------------------------------
# Processor architecture options
#-------------------------------------------------------------------------------

CPU = -cpu ARM7TDMI             # ARM7TDMI target processor

#-------------------------------------------------------------------------------
# ARM Procedure Call Standard (APCS) options
#-------------------------------------------------------------------------------

ROPI     = ropi                 # Read-Only(code) Position independence
INTERWRK = interwork            # Allow ARM-Thumb interworking

APCS = -apcs /$(ROPI)/$(INTERWRK)/norwpi

#-------------------------------------------------------------------------------
# Additional compile time error checking options
#-------------------------------------------------------------------------------

CHK = -fa                       # Check for data flow anomolies

#-------------------------------------------------------------------------------
# Compiler output options
#-------------------------------------------------------------------------------

OUT = -c                        # Object file output only

#-------------------------------------------------------------------------------
# Compiler/assembler debug options
#-------------------------------------------------------------------------------

DBG = -g                        # Enable debug

#-------------------------------------------------------------------------------
# Compiler optimization options
#-------------------------------------------------------------------------------

OPT = -Ospace -O2               # Full compiler optimization for space

#-------------------------------------------------------------------------------
# Compiler code generation options
#-------------------------------------------------------------------------------

END = -littleend                # Compile for little endian memory architecture
ZA  = -zo                       # LDR may only access 32-bit aligned addresses

CODE = $(END) $(ZA)


#-------------------------------------------------------------------------------
# Include file search path options
#-------------------------------------------------------------------------------

INC = -I. -I$(AEEINCPATH) $(APP_INCLUDES)


#-------------------------------------------------------------------------------
# Compiler pragma emulation options
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
# Linker options
#-------------------------------------------------------------------------------

LINK_CMD = -o                    #Command line option to specify output file
                                 #on linking

ROPILINK = -ropi                 #Link image as Read-Only Position Independent

LINK_ORDER = -first AEEMod_Load

#-------------------------------------------------------------------------------
# HEXTOOL options
#-------------------------------------------------------------------------------

BINFORMAT = -bin


#-------------------------------------------------------------------------------
# Compiler flag definitions
#-------------------------------------------------------------------------------

CFLAGS0 = $(OUT) $(DYNAPP) $(CPU) $(APCS) $(CODE) $(CHK) $(DBG)
CFLAGS  = $(CFLAGS0) $(OPT)

#-------------------------------------------------------------------------------
# Linker flag definitions
#-------------------------------------------------------------------------------

# the -entry flag is not really needed, but it keeps the linker from reporting
# warning L6305W (no entry point).  The address
LFLAGS = $(ROPILINK) -rwpi -entry 0x8000#


#----------------------------------------------------------------------------
# Default target
#----------------------------------------------------------------------------

all :  $(TARGET).$(MODULE)

#----------------------------------------------------------------------------
# Clean target
#----------------------------------------------------------------------------

# The object subdirectory, target image file, and target hex file are deleted.

clean :
        @echo ---------------------------------------------------------------
        @echo CLEAN
        -del /f $(OBJS)
        -del /f $(TARGET).$(EXETYPE)
        -del /f $(TARGET).$(MODULE)
        @echo ---------------------------------------------------------------

#============================================================================
#                           DEFAULT SUFFIX RULES
#============================================================================

# The following are the default suffix rules used to compile all objects that
# are not specifically included in one of the module specific rules defined
# in the next section.

# The following macros are used to specify the output object file, MSG_FILE
# symbol definition and input source file on the compile line in the rules
# defined below.

SRC_CPP_FILE = $(@F:.o=.cpp)      # Input source file specification
SRC_C_FILE   = $(@F:.o=.c)      # Input source file specification
OBJ_FILE = $(OBJ_CMD) $(@F)   # Output object file specification

.SUFFIXES :
.SUFFIXES : .o .dep .c .cpp

#--------------------------------------------------------------------------
# C code inference rules
#----------------------------------------------------------------------------

.cpp.o:
        @echo ---------------------------------------------------------------
        @echo OBJECT $(@F)
        $(ARMCPP) $(CFLAGS) $(INC) $(OBJ_FILE) $(SRC_CPP_FILE)
        @echo ---------------------------------------------------------------


{$(AEESRCPATH)}.c.o:
        @echo ---------------------------------------------------------------
        @echo OBJECT $(@F)
        $(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE) $(AEESRCPATH)\$(SRC_C_FILE)
        @echo ---------------------------------------------------------------


#===============================================================================
#                           MODULE SPECIFIC RULES
#===============================================================================

APP_OBJS =  $(OBJS)

#----------------------------------------------------------------------------
# Lib file targets
#----------------------------------------------------------------------------

$(TARGET).$(MODULE) : $(TARGET).$(EXETYPE)
        @echo ---------------------------------------------------------------
        @echo TARGET $@
        $(HEXTOOL)  $(TARGET).$(EXETYPE) $(BINFORMAT) $(TARGET).$(MODULE)

$(TARGET).$(EXETYPE) : $(APP_OBJS)
        @echo ---------------------------------------------------------------
        @echo TARGET $@
        $(LD) $(LINK_CMD) $(TARGET).$(EXETYPE) $(LFLAGS) $(APP_OBJS) $(LINK_ORDER)

#----------------------------------------------------------------------------
# Applet Specific Rules
#----------------------------------------------------------------------------


RULE1 = .
{$(RULE1)}.c.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE)  $(RULE1)\$(SRC_C_FILE)
	@echo ---------------------------------------------------------------


# --------------------------------------------
# DEPENDENCY LIST, DO NOT EDIT BELOW THIS LINE
# --------------------------------------------


box.o:	box.cpp
box.o:	box.h
box.o:	def.h
box.o:	$(BREWDIR)\inc\aeemodgen.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeegroupids.h
box.o:	$(BREWDIR)\inc\aeeclassids.h
box.o:	$(BREWDIR)\inc\aeeclsid_filemgr.bid
box.o:	$(BREWDIR)\inc\aeeerror.h
box.o:	$(BREWDIR)\inc\aeecomdef.h
box.o:	$(BREWDIR)\inc\aeeinterface.h
box.o:	$(BREWDIR)\inc\aeecomdef.h
box.o:	$(BREWDIR)\inc\aeequeryinterface.h
box.o:	$(BREWDIR)\inc\aeeinterface.h
box.o:	$(BREWDIR)\inc\aeeshell.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeevcodes.h
box.o:	$(BREWDIR)\inc\aeedisp.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeebitmap.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeefont.h
box.o:	$(BREWDIR)\inc\aeebitmap.h
box.o:	$(BREWDIR)\inc\aeeimage.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeesoundplayer.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeesound.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeeresourcectl.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeecontrols_res.h
box.o:	$(BREWDIR)\inc\aeelngcode.h
box.o:	$(BREWDIR)\inc\aeeappgen.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeeshell.h
box.o:	$(BREWDIR)\inc\aeemodgen.h
box.o:	$(BREWDIR)\inc\aeeshell.h
box.o:	$(BREWDIR)\inc\aeefile.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeedb.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeenet.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeeshell.h
box.o:	$(BREWDIR)\inc\aeeerror.h
box.o:	$(BREWDIR)\inc\aeestdlib.h
box.o:	$(BREWDIR)\inc\aeeoldvalist.h
box.o:	$(BREWDIR)\inc\aeecomdef.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeenetworktypes.h
box.o:	$(BREWDIR)\inc\aeecomdef.h
box.o:	$(BREWDIR)\inc\net_urgent.bid
box.o:	$(BREWDIR)\inc\aeesound.h
box.o:	$(BREWDIR)\inc\aeetapi.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeestdlib.h
box.o:	$(BREWDIR)\inc\aeegraphics.h
box.o:	$(BREWDIR)\inc\aee.h
box.o:	$(BREWDIR)\inc\aeedisp.h
box.o:	$(BREWDIR)\inc\aeebitmap.h
box.o:	newenuos.bid
box.o:	color.h
box.o:	def.h
canvas.o:	canvas.cpp
canvas.o:	canvas.h
canvas.o:	def.h
canvas.o:	$(BREWDIR)\inc\aeemodgen.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeegroupids.h
canvas.o:	$(BREWDIR)\inc\aeeclassids.h
canvas.o:	$(BREWDIR)\inc\aeeclsid_filemgr.bid
canvas.o:	$(BREWDIR)\inc\aeeerror.h
canvas.o:	$(BREWDIR)\inc\aeecomdef.h
canvas.o:	$(BREWDIR)\inc\aeeinterface.h
canvas.o:	$(BREWDIR)\inc\aeecomdef.h
canvas.o:	$(BREWDIR)\inc\aeequeryinterface.h
canvas.o:	$(BREWDIR)\inc\aeeinterface.h
canvas.o:	$(BREWDIR)\inc\aeeshell.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeevcodes.h
canvas.o:	$(BREWDIR)\inc\aeedisp.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeebitmap.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeefont.h
canvas.o:	$(BREWDIR)\inc\aeebitmap.h
canvas.o:	$(BREWDIR)\inc\aeeimage.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeesoundplayer.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeesound.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeeresourcectl.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeecontrols_res.h
canvas.o:	$(BREWDIR)\inc\aeelngcode.h
canvas.o:	$(BREWDIR)\inc\aeeappgen.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeeshell.h
canvas.o:	$(BREWDIR)\inc\aeemodgen.h
canvas.o:	$(BREWDIR)\inc\aeeshell.h
canvas.o:	$(BREWDIR)\inc\aeefile.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeedb.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeenet.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeeshell.h
canvas.o:	$(BREWDIR)\inc\aeeerror.h
canvas.o:	$(BREWDIR)\inc\aeestdlib.h
canvas.o:	$(BREWDIR)\inc\aeeoldvalist.h
canvas.o:	$(BREWDIR)\inc\aeecomdef.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeenetworktypes.h
canvas.o:	$(BREWDIR)\inc\aeecomdef.h
canvas.o:	$(BREWDIR)\inc\net_urgent.bid
canvas.o:	$(BREWDIR)\inc\aeesound.h
canvas.o:	$(BREWDIR)\inc\aeetapi.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeestdlib.h
canvas.o:	$(BREWDIR)\inc\aeegraphics.h
canvas.o:	$(BREWDIR)\inc\aee.h
canvas.o:	$(BREWDIR)\inc\aeedisp.h
canvas.o:	$(BREWDIR)\inc\aeebitmap.h
canvas.o:	newenuos.bid
canvas.o:	color.h
canvas.o:	def.h
canvas.o:	box.h
canvas.o:	def.h
canvas.o:	color.h
canvas.o:	enuos.h
canvas.o:	def.h
canvas.o:	color.h
canvas.o:	canvas.h
canvas.o:	shape.h
canvas.o:	def.h
canvas.o:	canvas.h
shape.o:	shape.cpp
shape.o:	shape.h
shape.o:	def.h
shape.o:	$(BREWDIR)\inc\aeemodgen.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeegroupids.h
shape.o:	$(BREWDIR)\inc\aeeclassids.h
shape.o:	$(BREWDIR)\inc\aeeclsid_filemgr.bid
shape.o:	$(BREWDIR)\inc\aeeerror.h
shape.o:	$(BREWDIR)\inc\aeecomdef.h
shape.o:	$(BREWDIR)\inc\aeeinterface.h
shape.o:	$(BREWDIR)\inc\aeecomdef.h
shape.o:	$(BREWDIR)\inc\aeequeryinterface.h
shape.o:	$(BREWDIR)\inc\aeeinterface.h
shape.o:	$(BREWDIR)\inc\aeeshell.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeevcodes.h
shape.o:	$(BREWDIR)\inc\aeedisp.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeebitmap.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeefont.h
shape.o:	$(BREWDIR)\inc\aeebitmap.h
shape.o:	$(BREWDIR)\inc\aeeimage.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeesoundplayer.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeesound.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeeresourcectl.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeecontrols_res.h
shape.o:	$(BREWDIR)\inc\aeelngcode.h
shape.o:	$(BREWDIR)\inc\aeeappgen.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeeshell.h
shape.o:	$(BREWDIR)\inc\aeemodgen.h
shape.o:	$(BREWDIR)\inc\aeeshell.h
shape.o:	$(BREWDIR)\inc\aeefile.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeedb.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeenet.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeeshell.h
shape.o:	$(BREWDIR)\inc\aeeerror.h
shape.o:	$(BREWDIR)\inc\aeestdlib.h
shape.o:	$(BREWDIR)\inc\aeeoldvalist.h
shape.o:	$(BREWDIR)\inc\aeecomdef.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeenetworktypes.h
shape.o:	$(BREWDIR)\inc\aeecomdef.h
shape.o:	$(BREWDIR)\inc\net_urgent.bid
shape.o:	$(BREWDIR)\inc\aeesound.h
shape.o:	$(BREWDIR)\inc\aeetapi.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeestdlib.h
shape.o:	$(BREWDIR)\inc\aeegraphics.h
shape.o:	$(BREWDIR)\inc\aee.h
shape.o:	$(BREWDIR)\inc\aeedisp.h
shape.o:	$(BREWDIR)\inc\aeebitmap.h
shape.o:	newenuos.bid
shape.o:	canvas.h
shape.o:	def.h
shape.o:	color.h
shape.o:	def.h
shape.o:	box.h
shape.o:	def.h
shape.o:	color.h
shape.o:	enuos.h
shape.o:	def.h
shape.o:	color.h
shape.o:	canvas.h
shape.o:	shape.h
color.o:	color.cpp
color.o:	color.h
color.o:	def.h
color.o:	$(BREWDIR)\inc\aeemodgen.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeegroupids.h
color.o:	$(BREWDIR)\inc\aeeclassids.h
color.o:	$(BREWDIR)\inc\aeeclsid_filemgr.bid
color.o:	$(BREWDIR)\inc\aeeerror.h
color.o:	$(BREWDIR)\inc\aeecomdef.h
color.o:	$(BREWDIR)\inc\aeeinterface.h
color.o:	$(BREWDIR)\inc\aeecomdef.h
color.o:	$(BREWDIR)\inc\aeequeryinterface.h
color.o:	$(BREWDIR)\inc\aeeinterface.h
color.o:	$(BREWDIR)\inc\aeeshell.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeevcodes.h
color.o:	$(BREWDIR)\inc\aeedisp.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeebitmap.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeefont.h
color.o:	$(BREWDIR)\inc\aeebitmap.h
color.o:	$(BREWDIR)\inc\aeeimage.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeesoundplayer.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeesound.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeeresourcectl.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeecontrols_res.h
color.o:	$(BREWDIR)\inc\aeelngcode.h
color.o:	$(BREWDIR)\inc\aeeappgen.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeeshell.h
color.o:	$(BREWDIR)\inc\aeemodgen.h
color.o:	$(BREWDIR)\inc\aeeshell.h
color.o:	$(BREWDIR)\inc\aeefile.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeedb.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeenet.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeeshell.h
color.o:	$(BREWDIR)\inc\aeeerror.h
color.o:	$(BREWDIR)\inc\aeestdlib.h
color.o:	$(BREWDIR)\inc\aeeoldvalist.h
color.o:	$(BREWDIR)\inc\aeecomdef.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeenetworktypes.h
color.o:	$(BREWDIR)\inc\aeecomdef.h
color.o:	$(BREWDIR)\inc\net_urgent.bid
color.o:	$(BREWDIR)\inc\aeesound.h
color.o:	$(BREWDIR)\inc\aeetapi.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeestdlib.h
color.o:	$(BREWDIR)\inc\aeegraphics.h
color.o:	$(BREWDIR)\inc\aee.h
color.o:	$(BREWDIR)\inc\aeedisp.h
color.o:	$(BREWDIR)\inc\aeebitmap.h
color.o:	newenuos.bid
color.o:	enuos.h
color.o:	def.h
color.o:	color.h
color.o:	canvas.h
color.o:	def.h
color.o:	color.h
color.o:	box.h
color.o:	def.h
color.o:	color.h
color.o:	shape.h
color.o:	def.h
color.o:	canvas.h
newenuos.o:	newenuos.cpp
newenuos.o:	enuos.h
newenuos.o:	def.h
newenuos.o:	$(BREWDIR)\inc\aeemodgen.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeegroupids.h
newenuos.o:	$(BREWDIR)\inc\aeeclassids.h
newenuos.o:	$(BREWDIR)\inc\aeeclsid_filemgr.bid
newenuos.o:	$(BREWDIR)\inc\aeeerror.h
newenuos.o:	$(BREWDIR)\inc\aeecomdef.h
newenuos.o:	$(BREWDIR)\inc\aeeinterface.h
newenuos.o:	$(BREWDIR)\inc\aeecomdef.h
newenuos.o:	$(BREWDIR)\inc\aeequeryinterface.h
newenuos.o:	$(BREWDIR)\inc\aeeinterface.h
newenuos.o:	$(BREWDIR)\inc\aeeshell.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeevcodes.h
newenuos.o:	$(BREWDIR)\inc\aeedisp.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeebitmap.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeefont.h
newenuos.o:	$(BREWDIR)\inc\aeebitmap.h
newenuos.o:	$(BREWDIR)\inc\aeeimage.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeesoundplayer.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeesound.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeeresourcectl.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeecontrols_res.h
newenuos.o:	$(BREWDIR)\inc\aeelngcode.h
newenuos.o:	$(BREWDIR)\inc\aeeappgen.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeeshell.h
newenuos.o:	$(BREWDIR)\inc\aeemodgen.h
newenuos.o:	$(BREWDIR)\inc\aeeshell.h
newenuos.o:	$(BREWDIR)\inc\aeefile.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeedb.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeenet.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeeshell.h
newenuos.o:	$(BREWDIR)\inc\aeeerror.h
newenuos.o:	$(BREWDIR)\inc\aeestdlib.h
newenuos.o:	$(BREWDIR)\inc\aeeoldvalist.h
newenuos.o:	$(BREWDIR)\inc\aeecomdef.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeenetworktypes.h
newenuos.o:	$(BREWDIR)\inc\aeecomdef.h
newenuos.o:	$(BREWDIR)\inc\net_urgent.bid
newenuos.o:	$(BREWDIR)\inc\aeesound.h
newenuos.o:	$(BREWDIR)\inc\aeetapi.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeestdlib.h
newenuos.o:	$(BREWDIR)\inc\aeegraphics.h
newenuos.o:	$(BREWDIR)\inc\aee.h
newenuos.o:	$(BREWDIR)\inc\aeedisp.h
newenuos.o:	$(BREWDIR)\inc\aeebitmap.h
newenuos.o:	newenuos.bid
newenuos.o:	color.h
newenuos.o:	def.h
newenuos.o:	canvas.h
newenuos.o:	def.h
newenuos.o:	color.h
newenuos.o:	box.h
newenuos.o:	def.h
newenuos.o:	color.h
newenuos.o:	shape.h
newenuos.o:	def.h
newenuos.o:	canvas.h
