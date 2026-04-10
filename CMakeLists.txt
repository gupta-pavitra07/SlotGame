cmake_minimum_required(VERSION 3.16)
project(SlotGameQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(include)

file(GLOB SRC_FILES src/*.cpp)

add_executable(SlotGameQt
    main.cpp
    MainWindow.cpp
    StartWindow.cpp   
    ResultDialog.cpp 
    LeaderboardWindow.cpp 
PredictionDialog.cpp
 StrategyDialog.cpp
    ${SRC_FILES}
)

target_link_libraries(SlotGameQt Qt6::Widgets)