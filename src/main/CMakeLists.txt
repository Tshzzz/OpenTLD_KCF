
link_directories(${OpenCV_LIB_DIR})

include_directories(main
    ../libopentld/tld
    ../3rdparty/cvblobs
    ${OpenCV_INCLUDE_DIRS})

#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# opentld
add_executable(opentld
    imgStream.h
    main.cpp
    imgStream.cpp
)

target_link_libraries(opentld libopentld cvblobs ${OpenCV_LIBS})

install(TARGETS opentld DESTINATION bin)


