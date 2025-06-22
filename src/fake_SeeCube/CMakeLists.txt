add_library(fake_SeeCube STATIC
    fake_SeeCube.cpp
)

target_include_directories(fake_SeeCube PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
