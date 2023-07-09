cmake_minimum_required(VERSION 3.9.1)
project(ExpenserServer)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/build)


if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
        FATAL: In-source builds are not allowed.
        You should create a separate directory for build files.
    ")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES Darwin) 
    message("You are a cool person using ${CMAKE_SYSTEM_NAME}")

    message(STATUS \"PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}\")
    message(STATUS \"CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}\")
    message(STATUS \"CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}\")

else()
    message("You should consider buying a macbook")
endif()



add_subdirectory(libs)
add_subdirectory(src)
