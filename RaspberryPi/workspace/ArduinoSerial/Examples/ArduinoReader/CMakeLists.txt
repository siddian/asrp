#include_directories (${ePaper_SOURCE_DIR}/EPlibrary)
#link_directories (${ePaper_BINARY_DIR}/EPlibrary) 

SET(ARDUINOREADER_SRC reader.cpp)

add_executable(arduinoreader ${ARDUINOREADER_SRC})

#TARGET_LINK_LIBRARIES(arduinoreader serial)

#IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
#    TARGET_LINK_LIBRARIES(pgmloader ePaper)
#ELSE ()
#    TARGET_LINK_LIBRARIES(pgmloader ePaper wiringPi)
#ENDIF ()
