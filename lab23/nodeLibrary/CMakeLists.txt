cmake_minimum_required (VERSION 3.8)

project(nodeLibrary)

set(SOURCE_FILES "node.c")
set(HEADER_FILES "node.h")


add_library(nodeLibrary STATIC ${HEADER_FILES} ${SOURCE_FILES})