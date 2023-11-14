COMPILER = g++
OBJ_DIR := ./obj
UTIL_DIR := ./util
SRC_FILES := $(wildcard $(UTIL_DIR)/*.hpp)

CPPFLAGS = -O3 -fopenmp -std=c++17
all: $(METHOD)

build: build.cc util/IO.hpp util/ds/indexItem.hpp util/ds/cw.hpp util/new_utils.hpp util/builder/builder.hpp util/config/buildConfig.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<
buildCompactWindows: buildCompactWindows.cc util/IO.hpp util/ds/indexItem.hpp util/ds/cw.hpp util/new_utils.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<

searchDuplicate: searchDuplicate.cc util/IO.hpp util/ds/indexItem.hpp util/ds/cw.hpp util/new_utils.hpp util/query.hpp util/queryFaster.hpp util/dupSearch/segmentTree.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<

buildLargeNumWindows: buildLargeNumWindows.cc util/IO.hpp util/ds/indexItem.hpp util/ds/cw.hpp util/new_utils.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<

mergeCw: mergeCw.cc util/IO.hpp util/ds/indexItem.hpp util/ds/cw.hpp util/new_utils.hpp
	${COMPILER} ${CPPFLAGS} -o $@ $<

$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.hpp
	${COMPILER} $(CPPFLAGS) -c -o $@ $<

