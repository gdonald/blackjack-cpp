cmake_minimum_required(VERSION 3.13.4)
project(blackjack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPackageHandleStandardArgs)

include_directories(include)

add_executable(blackjack
        src/Card.cpp
        src/Shoe.cpp
        src/DealerHand.cpp
        src/PlayerHand.cpp
        src/Hand.cpp
        src/Game.cpp
        src/BufferToggle.cpp
        src/BlackJack.cpp)

target_link_libraries(blackjack)

add_custom_command(TARGET blackjack
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:blackjack> ..)
