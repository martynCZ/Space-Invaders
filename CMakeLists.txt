cmake_minimum_required(VERSION 3.10)

# Název projektu
project(SpaceInvaders C)

# Nastavení standardu C (C99 je pro tvůj kód minimum)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Hledání balíčků (volitelné, ale doporučené pro robustnost)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Definice zdrojových souborů
set(SOURCES
    main.c
    game.c
    end.c
    game.h
    end.h
)

# Vytvoření spustitelného souboru (název: game)
add_executable(game ${SOURCES})

# Zahrnutí hlavičkových souborů SDL2 (pokud nejsou v systémové cestě)
target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS})

# Linkování knihoven (odpovídá tvému: -lSDL2 -lSDL2_ttf -lSDL2_image -lm)
target_link_libraries(game PRIVATE
    SDL2
    SDL2_image
    SDL2_ttf
    m
)