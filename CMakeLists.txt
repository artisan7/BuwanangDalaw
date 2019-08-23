cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("Buwanang Dalaw")

add_executable(../bin/mainApp
               source/main.cpp
               source/House.cpp
               source/Room.cpp
               source/Boarder.cpp
               source/Date.cpp
               source/Assignment.cpp
               source/Payment.cpp)
