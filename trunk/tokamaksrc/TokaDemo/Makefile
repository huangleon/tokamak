
#/*-----------------------------------------------------------------------------
# *
# *  This file is part of "pingpang game", which is based on Irrlicht Engine.
# *
# *  Revise History:
# *    Date          Author           Comment
# *    2008-08-22    Hu, weixiong     Initial version.
# *    2008-08-27    Hu, weixiong     Complie each source file explicitly.
# *
# *  Copyright (c) 2007 Intel Corporation.
# *
# *-----------------------------------------------------------------------------
# */

Target = TokaDemo
Sources := $(shell echo *.cpp common/utility/*.cpp)
SYSTEM = Linux

TARGET = ../bin/$(SYSTEM)/$(Target)
#TARGET = /tftpboot/mediabuild_257_release/3dpingpang/bin/$(SYSTEM)/$(Target)
MIDDIR = ../mid/$(SYSTEM)/
OBJECTS := $(foreach src, $(Sources), $(MIDDIR)$(src).o)

PDKROOT=/root/Intel_CE_2110-1.5.257
GSTREAMER_DIR=$(PDKROOT)/arm_gst
LIB_DIR=$(PDKROOT)/arm-linux-elf/lib

olo: CPPFLAGS = -I. -I../../../../irrlicht/include -I./common -I../include 
#-I../../../include/network/zthread
olo: CPPFLAGS += -O3 -ffast-math
#olo: CPPFLAGS += -g
olo: CXXFLAGS = $(CPPFLAGS)
olo: SYSTEM = Linux
olo: LDFLAGS = -L../../../../lib/$(SYSTEM) -ldl -L$(LIB_DIR) -L../lib/$(SYSTEM)/ -ltokamak
olo: OLO_CXX = arm-linux-g++
olo: OLO_AR = arm-linux-ar
olo: OLO_LD = arm-linux-ld
olo: OLO_LIBGLES = -lGLES_CM
olo: OLO_LIBGLES += -lIMGegl
olo: OLO_LIBGLES += -lrt
olo: OLO_LIBGLES += -lsrv_um_usrports
olo: OLO_LIBIRR = -lIrrlicht_olo -lfreetype
olo: OLO_LIBALL = $(OLO_LIBGLES) $(OLO_LIBIRR)

include makefile.include

olo: $(OBJECTS)
	$(OLO_CXX) -o $(TARGET) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) $(OLO_LIBALL)

clean:
	echo "Clean... "
	-rm -f $(TARGET) $(MIDDIR)*.* $(MIDDIR)network/*  $(MIDDIR)common/* $(MIDDIR)common/RemoteController/* $(MIDDIR)lua/* $(MIDDIR)common/utility/* $(MIDDIR)common/FileTransfer/* $(MIDDIR)common/NetworkCommonFramework/* $(MIDDIR)common/ui/* $(MIDDIR)common/ActionIndentify/*
	mkdir -p $(MIDDIR)common
	mkdir -p $(MIDDIR)common/utility
	./makeup.sh
