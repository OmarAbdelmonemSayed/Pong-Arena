# Pong Arena

## Overview
Pong Arena is a classic Pong game where players can compete in both single-player mode against AI and multiplayer mode against another player.

## Screenshots
![Main Screen Screenshot]("Pong Game/screenshots/main screen.png")
![In-Game Screenshot]("Pong Game/screenshots/in game.png")

## Game Rules
- **Single Player**: Compete against AI.
- **Multiplayer**: Compete against another player.
- **Controls**:
  - **Player 1**: 
    - `W` to move up
    - `S` to move down
  - **Player 2**: 
    - Up Arrow to move up
    - Down Arrow to move down
- The game ends when a player reaches 10 points.

## Project Structure
```
.
│    Pong Game.sln
│
└─── Pong Game
    │    Pong Game.vcxproj
    │    Pong Game.vcxproj.filters
    │    Pong Game.vcxproj.user
    │
    ├─── screenshots
    │        in game.png
    │        main screen.png
    │
    ├─── include
    │        Controls.h
    │        Game.h
    │        Renderer.h
    │        RenderWin32Platform.h
    │
    └─── src
             Game.cpp
             Renderer.cpp
             win32platform.cpp

```
## How to Run
- Clone the repository.
- Open the solution in Visual Studio.
- Build and run the project.