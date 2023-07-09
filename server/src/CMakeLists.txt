set(INCLUDE_PATHS /usr/local/Cellar/boost/
 /usr/local/Cellar/boost/include
 /usr/local/Cellar/libpq/15.3_1/include
 ${PROJECT_SOURCE_DIR}/libs/crow/include
 ${PROJECT_SOURCE_DIR}/libs/sqlpp11
 ${PROJECT_SOURCE_DIR}/libs/ /usr/local/include)

add_executable(ExpenserServer main.cpp)

target_include_directories(ExpenserServer PUBLIC ${INCLUDE_PATHS})
add_subdirectory(routes)


target_link_libraries(ExpenserServer 
    PRIVATE 
    sqlpp11::sqlpp11
    sqlpp11::postgresql
)

target_sources(ExpenserServer 
    PRIVATE 
        main.cpp 
)

