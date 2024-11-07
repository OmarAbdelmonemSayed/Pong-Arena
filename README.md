# Pong Arena

## Overview
Pong Arena is a classic Pong game where players can compete in both single-player mode against AI and multiplayer mode against another player.

The Win32 API is used for handling pixels and input, allowing direct interaction with the Windows operating system to create the game's interface and manage user controls.

## Screenshots

![main_screen](https://github.com/OmarAbdelmonemSayed/Pong-Arena/blob/master/Pong%20Game/screenshots/main_screen.png)

![in_game](https://github.com/user-attachments/assets/190f5502-29e3-418f-b149-7d716cb31ca0)

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

### Recommended Build Configuration
- For the best performance, make sure to run the game in **Release** mode. The **Debug** mode is intended for development and may cause the game to run slower.
