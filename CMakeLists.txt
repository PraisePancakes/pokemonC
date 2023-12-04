cmake_minimum_required(VERSION 3.28.0)

project("PokemonC" VERSION 0.0.1 LANGUAGES C)

add_executable(${PROJECT_NAME} src/main.c src/ball.c src/file.c src/gui.c src/player.c src/pokemon.c src/init.c)

