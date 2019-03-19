cmake_minimum_required(VERSION 3.12)

project(Lab2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES_PATH src)

list(APPEND SOURCES
    ${SOURCES_PATH}/Maincpp.cpp
    ${SOURCES_PATH}/PCBC.cpp
	${SOURCES_PATH}/aes.c
)

add_executable(Lab2 ${SOURCES})