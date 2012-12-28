include_directories (${ePaper_SOURCE_DIR}/EPlibrary)

link_directories (${ePaper_BINARY_DIR}/EPlibrary) 

SET(PGMLOADER_SRC e-paper.cpp)

add_executable(pgmloader ${PGMLOADER_SRC})

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    TARGET_LINK_LIBRARIES(pgmloader ePaper)
ELSE ()
    TARGET_LINK_LIBRARIES(pgmloader ePaper wiringPI)
ENDIF ()
