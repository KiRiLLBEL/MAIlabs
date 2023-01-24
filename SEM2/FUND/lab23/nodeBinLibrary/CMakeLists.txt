cmake_minimum_required (VERSION 3.8)

project(nodeBinLibrary)

set(SOURCE_FILES "nodeBin.c")
set(HEADER_FILES "nodeBin.h")


add_library(nodeBinLibrary STATIC ${HEADER_FILES} ${SOURCE_FILES})