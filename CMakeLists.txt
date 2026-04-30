cmake_minimum_required(VERSION 3.16)
project(SlotGameQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    frontend/include
    backend/include
)

set(FRONTEND_SRC
    frontend/src/ActivePredictionsDialog.cpp
    frontend/src/LeaderboardWindow.cpp
    frontend/src/MainWindow.cpp
    frontend/src/PredictionDialog.cpp
    frontend/src/ProfileDialog.cpp
    frontend/src/QuizWidget.cpp
    frontend/src/ResultDialog.cpp
    frontend/src/StartWindow.cpp
    frontend/src/StrategyDialog.cpp
)

set(BACKEND_SRC
    backend/src/file.cpp
    backend/src/leaderboard.cpp
    backend/src/player.cpp
    backend/src/predictionevaluator.cpp
    backend/src/predictionmanager.cpp
    backend/src/probability.cpp
    backend/src/search.cpp
    backend/src/slot.cpp
    backend/src/strategy.cpp
)

set(FRONTEND_INC
    frontend/include/ActivePredictionsDialog.h
    frontend/include/LeaderboardWindow.h
    frontend/include/MainWindow.h
    frontend/include/PredictionDialog.h
    frontend/include/ProfileDialog.h
    frontend/include/QuizWidget.h
    frontend/include/ResultDialog.h
    frontend/include/StartWindow.h
    frontend/include/StrategyDialog.h
)

add_executable(SlotGameQt
    main.cpp
    ${FRONTEND_SRC}
    ${BACKEND_SRC}
    ${FRONTEND_INC}
)

target_link_libraries(SlotGameQt Qt6::Widgets)