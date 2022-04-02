cmake_minimum_required (VERSION 3.8)

project(NeuralLib)

set(SOURCE_FILES "neural.cpp")
set(HEADER_FILES "neural.h")


add_library(NeuralLib STATIC ${HEADER_FILES} ${SOURCE_FILES})