# Zombicide – C Console Game

A console-based zombie survival game based on the board game with the same name developed in C as a university programming project.

## Features

- Dynamic 2D game board.
- Randomly generated buildings and zombie placement.
- Zombie movement towards sound sources.
- Three different weapons with unique attack mechanics:
  - **Bomb:** Damages zombies within a 3×3 area.
  - **Plasmagun:** Fires in a straight line and stops at buildings.
  - **Neurogun:** Uses recursive logic to eliminate connected zombies of the same type.
- Score tracking and progressive difficulty.
- Dynamic memory allocation and pointer manipulation.

## Technologies

- C
- Standard C Library
- GCC Compiler

## How to Compile

Compile the source files together:

```bash
gcc src/Zombicide.c src/Zombicide_functions.c -o Zombicide
```

Run the executable:

```bash
./Zombicide
```

## Purpose

This project was developed to practice C programming, including pointers, dynamic memory allocation, multidimensional arrays, functions, recursion, and structured program organization.