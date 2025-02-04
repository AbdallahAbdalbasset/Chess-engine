# Chess Game with Engine

This is a C++ chess game featuring a console-based board and a chess engine powered by the Minimax algorithm with Alpha-Beta pruning.

## Features

- **Console-based Chess Board**: Play chess directly in the terminal.
- **Chess Engine**: Uses Minimax with Alpha-Beta pruning for efficient move evaluation.
- **Move Calculation**: The engine searches moves up to depth 6 in approximately 5 minutes.
- **Two Player Mode**: Play against another human or challenge the chess engine.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/chess-engine.git
   cd chess-engine
   ```
2. Compile the project using g++:
   ```sh
   g++ -std=c++11 *.cpp Board/Board.cpp Engine/Engine.cpp Board/Pieces/Sources/*.cpp Helper/Helper.cpp -o chess
   ```
3. Run the game:
   ```sh
   ./chess
   ```

## Usage

- Start the game and follow the console instructions.
- Enter moves using board coordinates in the format: `fromX fromY toX toY`
  - Example: `0 1 0 2` moves the piece from `(0,1)` to `(0,2)`.
- Play against another player or challenge the chess engine.

## Future Improvements

- Implement bitboards for optimized board representation.
- Add a transposition table to enhance engine efficiency.

