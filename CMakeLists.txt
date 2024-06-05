cmake_minimum_required(VERSION 3.27)

project(hypr-which-key
    DESCRIPTION "which key plugin for Hyprland"
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC "*.cpp")

add_library(hypr-which-key SHARED ${SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET
    hyprland
    libdrm
    pixman-1
)
target_link_libraries(hypr-which-key PRIVATE rt PkgConfig::deps)

install(TARGETS hypr-which-key)
