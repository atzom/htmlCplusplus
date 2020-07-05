#!/bin/bash

LIB_PATH=`pwd`
LIB_PATH="`dirname ${LIB_PATH}`"
LIB_PATH="${LIB_PATH}/build"
VAL_GRIND=`which valgrind`

if [ $1 ]; then

	LD_LIBRARY_PATH="${LIB_PATH}" ${VAL_GRIND} \
	--track-origins=yes \
	--leak-check=full \
	--show-leak-kinds=all \
	-v \
	bin/$1 &> bin/$1"-report.txt" && echo "Report was saved at: bin/$1-report.txt"
else
	for il in `ls bin/example*`; do
		report=`basename ${il}`
		test -x ${il} && LD_LIBRARY_PATH="${LIB_PATH}" ${VAL_GRIND} \
		--track-origins=yes \
		--leak-check=full \
		--show-leak-kinds=all \
		-v \
		${il} &> ${il}"-report.txt" && echo "Report was saved at: ${il}-report.txt"
	done
fi
