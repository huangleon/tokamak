
#!/bin/bash

#/*-----------------------------------------------------------------------------
# *
# *  This file is part of "pingpang game", which is based on Irrlicht Engine.
# *
# *  Revise History:
# *    Date          Author           Comment
# *    2007-11-4    Zhou, danlan     Initial version.
# *
# *
# *-----------------------------------------------------------------------------
# */

echo "Generate makefile..."
HEADERS=' *.h'
SOURCES='*.cpp'

{
	echo 'HEADERS='$HEADERS
	echo ""

	for src in $SOURCES
	do
		OBJ='$(MIDDIR)'$src'.o'
		echo $OBJ" :" $src '$(HEADERS)'
		echo "	"'$(OLO_CXX)'" -c "$src '$(CXXFLAGS)'" -r -o "$OBJ
        echo ""
	done
} > makefile.include
