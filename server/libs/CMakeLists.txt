include(FetchContent)

FetchContent_Declare(sqlpp11
    GIT_REPOSITORY  https://github.com/rbock/sqlpp11
    GIT_TAG         origin/main
)

# FetchContent_Declare(cryptopp-cmake
#     GIT_REPOSITORY  https://github.com/abdes/cryptopp-cmake
#     GIT_TAG         origin/master
# )

add_subdirectory(sqlpp11)
# add_subdirectory(cryptopp)
add_subdirectory(cryptopp-cmake)