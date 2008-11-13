
#/*-----------------------------------------------------------------------------
# *
# *  This file is part of "pingpang game", which is based on Irrlicht Engine.
# *
# *  Revise History:
# *    Date          Author           Comment
# *    2007-11-05    Zhou, danlan     Complie each source file explicitly.
# *
# *  Copyright (c) 2007 Duwei Corporation.
# *
# *-----------------------------------------------------------------------------
# */

Target = tokamak.a
Sources := $(shell echo *.cpp)
SYSTEM = Linux

TARGET = ../lib/$(SYSTEM)/$(Target)
MIDDIR = ../mid/$(SYSTEM)/
OBJECTS := $(foreach src, $(Sources), $(MIDDIR)$(src).o)

CPPFLAGS = -I. -I../include
CPPFLAGS += -O3 -ffast-math
CXXFLAGS = $(CPPFLAGS)
SYSTEM = Linux
OLO_CXX = arm-linux-g++
OLO_AR = arm-linux-ar
OLO_LD = arm-linux-ld
OLO_RANLIB = arm-linux-ranlib 

include makefile.include

tokamak: $(OBJECTS)
	$(OLO_AR)  -rc $(TARGET) $(OBJECTS)
	$(OLO_RANLIB) $(TARGET)

clean:
	echo "Clean... "
	-rm -f $(TARGET) $(OBJECTS)
	mkdir -p $(MIDDIR)
	./makeup.sh
