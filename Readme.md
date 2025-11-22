# 🧱 BrickGame: Tetris (Console Version)

A terminal-based implementation of the classic *Tetris* game, written in **C (C11)** using the `ncurses` library. Part of the *BrickGame* suite — a collection of retro brick-based games.

---

## 🎮 Features

- Classic Tetris gameplay on a 10×20 grid
- Finite State Machine (FSM) for robust game logic control
- Real-time input handling (Start, Pause, Move, Rotate, Drop, Terminate)
- Score, level, and speed progression
- Preview of the next tetromino
- Thread-safe internal state
- Modular design: **core logic** (`src/brick_game/tetris/`) + **CLI GUI** (`src/gui/cli/`)

---

## 🛠️ Build & Run (Ubuntu)

### Requirements
- `gcc` (C11 support)
- `ncurses` development libraries
  (e.g., `sudo apt install libncurses5-dev` on Ubuntu)

### Compilation
```bash
make install