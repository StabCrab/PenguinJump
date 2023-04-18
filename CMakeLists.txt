cmake_minimum_required(VERSION 3.15)
project(PenguinWarfare)

set(CMAKE_CXX_STANDARD 20)

add_executable(PenguinWarfare main.cpp
        Menu.h Menu.cpp
        GameWorld.h GameWorld.cpp
        Terrain.h Terrain.cpp
        Player.h Player.cpp
        Entity.h Entity.cpp
        Unit.h Unit.cpp
        Animation.h Animation.cpp
        )

set(SFML_ROOT "C:/Libraries/SFML")

set(CMAKE_MODULE_PATH "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics network audio window system )

include_directories(C:/Libraries/SFML/include/SFML)
target_link_libraries(PenguinWarfare C:/Libraries/SFML/lib sfml-graphics sfml-network sfml-audio sfml-window sfml-system)