cmake_minimum_required(VERSION 3.22)
project(ex4_saeed_younis)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_saeed_younis
        Activation.h
        Dense.h
#        main.cpp
        Matrix.h
        MlpNetwork.h matrix.cpp Activation.cpp Dense.cpp MlpNetwork.cpp Test_33.cpp)
