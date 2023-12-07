COMPILER = g++
CPPFLAGS = -O2 -std=c++17
all: OPH OPH_build KMINS KMINS_build

OPH: OPH.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
OPH_build: OPH_build.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS_build: baseline/KMINS_build.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS: baseline/KMINS.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<