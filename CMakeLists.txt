cmake_minimum_required(VERSION 3.0)

project(minhook-dll LANGUAGES C)

add_library(minhook-dll STATIC src/MinHook.c)

target_include_directories(minhook-dll INTERFACE include)