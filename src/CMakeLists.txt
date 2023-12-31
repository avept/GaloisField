add_library(GaloisField
    GaloisField.cpp
)

target_include_directories(GaloisField
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)