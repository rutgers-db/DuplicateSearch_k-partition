COMPILER = g++
CPPFLAGS = -O2 -std=c++17
all: OPH OPH_longest OPH_longest_filter KMINS KMINS_INTERVAL_SCAN KMINS_INTERVAL_SCAN_filter

OPH: OPH.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
OPH_longest: OPH_longest.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
OPH_longest_filter: OPH_longest_filter.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS: baseline/KMINS.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS_INTERVAL_SCAN: baseline/KMINS_INTERVAL_SCAN.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<
KMINS_INTERVAL_SCAN_filter: baseline/KMINS_INTERVAL_SCAN_filter.cc
	${COMPILER} ${CPPFLAGS} -o $@ $<