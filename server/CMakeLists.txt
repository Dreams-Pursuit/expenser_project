cmake_minimum_required(VERSION 3.9.1)
project(ExpenserServer)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/build)


set(INCLUDE_PATHS /usr/local/Cellar/boost/ /usr/local/Cellar/boost/include /usr/local/Cellar/libpq/15.3_1/include libs/crow/include libs/sqlpp11 libs/ /usr/local/include)

if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
        FATAL: In-source builds are not allowed.
        You should create a separate directory for build files.
    ")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES Darwin) 
    message("You are a cool person using ${CMAKE_SYSTEM_NAME}")
else()
    message("You should consider buying a macbook")
endif()

add_subdirectory(libs)
add_executable(ExpenserServer src/main.cpp)

target_include_directories(ExpenserServer PUBLIC ${INCLUDE_PATHS})
# add_subdirectory(src/routes)

# target_link_libraries(ExpenserServer libs/cpp-dotenv/include)
target_link_libraries(ExpenserServer 
    PRIVATE 
    sqlpp11::sqlpp11
    # Corresponding targets for the connectors. These connectors need to be enabled in the the dependencies/sqlpp11 folder. These targets automatically link against sqlpp11::sqlpp11 and therefore sqlpp11::sqlpp11 doesn't need to be linked manually again
    # sqlpp11::sqlite3
    # sqlpp11::sqlcipher
    # sqlpp11::mysql
    # sqlpp11::mariadb
    sqlpp11::postgresql
)

target_sources(ExpenserServer 
    PRIVATE 
        src/main.cpp 
        src/routes/auth/auth.cpp
)