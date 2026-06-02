cmake_minimum_required(VERSION 3.16)
project(FinalProjectOOP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/amaliatanase/Qt/6.11.1/macos" ${CMAKE_PREFIX_PATH})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


add_executable(FinalProjectOOP
        main.cpp
        CraftItem.cpp CraftItem.h
        Action.cpp Action.h
        Repository.cpp Repository.h
        RepositoryFactory.cpp RepositoryFactory.h
        RepositoryFile.cpp RepositoryFile.h
        Controller.cpp Controller.h
        UI.cpp UI.h
        Filter.cpp
        Filter.h
        Tests.cpp
        Tests.h
)

target_link_libraries(FinalProjectOOP PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

