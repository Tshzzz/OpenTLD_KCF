#cmake_minimum_required(VERSION 2.8)

include_directories(cn piotr_fhog)

#set(KCF_LIB_SRC kcf.cpp kcf.h complexmat.hpp)

add_library(kcf
    cn/cn_data.cpp
    piotr_fhog/gradientMex.cpp
    kcf.cpp
    cn/cnfeat.hpp
    piotr_fhog/sse.hpp
    piotr_fhog/gradientMex.h
    piotr_fhog/fhog.hpp
    piotr_fhog/wrappers.hpp
    complexmat.hpp
    kcf.h)
