cmake_minimum_required(VERSION 3.21)

project(BitmapLibrary)

set(SOURCE_FILES "bitmap_test.cpp")
set(HEADER_FILES "bitmap_image.hpp")


add_library(BitmapLibrary STATIC ${HEADER_FILES} ${SOURCE_FILES})