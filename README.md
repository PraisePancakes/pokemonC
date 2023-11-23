# Pokemon C

## Version: 0.0.0-unreleased

## Overview

Welcome to Pokemon C, a text-based Pokemon simulator written in C. This project allows you to catch and showcase Pokemon using different types of Pokeballs. Explore the world of Pokemon, build your collection, and become a Pokemon master!

## Features

- Catch Pokemon using various Pokeballs with different catch chances.
- Showcase your Pokemon collection.
- Simple text-based interface.
- User-friendly menu system.

## How to Play

1. Run the program.
2. Enter your username to start your Pokemon journey.
3. Receive starting Pokeballs.

**Explore the menu (not finalized)**

1. Catch Pokemon
2. Showcase Pokemon
3. Exit

## Dependencies

C libraries used (**stdio.h**, **stdlib.h**, **stdbool.h**, **conio.h**, **string.h**, **time.h**)

## How to Build

### Compile the program using a C compiler. For example, using gcc:

**bash**
>> gcc -c ball.c -o ball.o
>> gcc -c gui.c -o gui.o
>> gcc -c player.c -o player.o
>> gcc -c pokemon.c -o pokemon.o
>> gcc -c main.c -o main.o
>> gcc ball.o gui.o player.o pokemon.o main.o -o pokemonC

## Usage

Run the compiled executable:

**bash**

`./pokemonC`

Follow the on-screen instructions to navigate through the game.

# Contributors

- Arya Sharifai

# License

This project is licensed under the MIT License.
