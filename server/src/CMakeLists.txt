
set(INCLUDE_PATHS /usr/local/Cellar/boost /usr/local/Cellar/boost/include
 /usr/local/Cellar/libpq/15.3_1/include
 /usr/local/include
 ${PROJECT_SOURCE_DIR}/libs/crow/include
 ${PROJECT_SOURCE_DIR}/libs/sqlpp11
#  ${PROJECT_SOURCE_DIR}/libs/cryptopp
 ${PROJECT_SOURCE_DIR}/libs/ 
 )


add_executable(ExpenserServer main.cpp)

add_subdirectory(utilities)
add_subdirectory(routes)


target_include_directories(ExpenserServer PUBLIC ${INCLUDE_PATHS})

target_compile_options(ExpenserServer PRIVATE "${compiler_options}")
target_link_libraries(ExpenserServer 
    PUBLIC 
    ${CMAKE_THREAD_LIBS_INIT}
    sqlpp11::sqlpp11
    sqlpp11::postgresql
    cryptopp::cryptopp
    # cryptopp-static
)

target_sources(ExpenserServer 
    PRIVATE 
        main.cpp 
        # utilities/hash/hash.cpp # 
)

