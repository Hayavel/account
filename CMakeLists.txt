cmake_minimum_required(VERSION 3.28.0)

project(Account VERSION 0.5.0)


add_executable(account main.cpp valid.cpp user.cpp)

target_link_libraries(account ${CMAKE_CURRENT_SOURCE_DIR}/libcryptopp.a)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})