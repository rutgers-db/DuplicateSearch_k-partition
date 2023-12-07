COMPILER = g++
CPPFLAGS = -O2 -std=c++17
all: OPH OPH_build KMINS KMINS_build

OPH: OPH.cc IO.hpp update.hpp segTree.hpp cw.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<
OPH_build: OPH_build.cc IO.hpp update.hpp segTree.hpp cw.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS_build: baseline/KMINS_build.cc IO.hpp update.hpp segTree.hpp cw.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS: baseline/KMINS.cc IO.hpp update.hpp segTree.hpp cw.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<