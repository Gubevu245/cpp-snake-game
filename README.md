# C++ Console Snake Game

A classic, grid-based Snake game built entirely in C++ that runs directly in the command prompt. The objective is to navigate the snake to eat fruit, grow its length, and achieve the highest score possible without colliding with the walls or the snake's own body.

## Features
* **Dynamic Grid Generation:** Memory is dynamically allocated for the game board, ensuring scalability.
* **Turn-Based Movement:** Strategic, step-by-step movement using standard WASD controls.
* **Collision Detection:** Fully implemented boundary checking and self-collision logic to trigger the Game Over state.
* **Optimized Rendering:** Uses ANSI escape codes for cursor repositioning, completely eliminating console flickering during frame updates.
* **Memory Management:** Includes complete memory deallocation to prevent leaks upon exiting the game loop.

## Tech Stack
* **Language:** C++
* **IDE:** Code::Blocks

## How to Play
1. Compile and run the game via the command line or by opening the `.cbp` file in Code::Blocks.
2. The game requires command-line arguments to set the dimensions of the game board:
   `[ExecutableName] <TotalRows> <TotalCols>`
   *(Example: `SnakeGame 15 20` creates a 15x20 grid)*
3. **Controls:**
   * `W` - Move Up
   * `S` - Move Down
   * `A` - Move Left
   * `D` - Move Right
4. **Symbols:**
   * `O` - Snake Head
   * `#` - Snake Body
   * `*` - Fruit
   * `.` - Empty Space

## Setup & Compilation
To run this project locally, clone the repository and compile the source files:
```bash
git clone [https://github.com/Gubevu245/cpp-snake-game.git](https://github.com/Gubevu245/cpp-snake-game.git)
g++ main.cpp Snake.cpp -o SnakeGame
./SnakeGame 15 20
