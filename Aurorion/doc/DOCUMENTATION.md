# Aurorion Game Documentation

Aurorion is a game built in C++ where players embark on an adventure in a block-based world. This document serves as a
guide to understand the game's functionalities and controls.

## Game Start

To start the game, you have several options:

1. Start a New Game: If you want to start a new game, simply run the game without any arguments:
   ```
   ./Aurorion
   ```
   This will load a new game for you.

2. Start a New Game Explicitly: You can also use the "new" argument to explicitly start a new game:
   ```
   ./Aurorion new
   ```
   This will start a new game.

3. Load a Saved Game: If you have previously saved your progress, you can load a specific SaveGame using the "load-x"
   argument, where "x" represents the number of the desired SaveGame. The SaveGames are located in the "examples"
   directory, along with the NewGame:
   ```
   ./Aurorion load-x
   ```
   Replace "x" with the number of the desired SaveGame.

Please note that if you're using the "make run" command to start the game, you need to specify the argument using the
MODE variable. For example, to load SaveGame2, use the following command:

```
make run MODE=load-2
```

Also note that when using more than one argument, the game treats it as an error and won´t start.

## SaveGame Management

Aurorion provides a SaveGame management system to save and load your progress. When starting a new game, a new SaveGame
directory is created with the incremented number of the last SaveGame (if the player did not die). This ensures that
each SaveGame has a unique directory to store its state.

Similarly, when loading from a SaveGame, the game state is saved in the directory of the loaded SaveGame (if the player
did not die). This allows you to continue your progress from where you left off.

## Controls

The controls for playing Aurorion are as follows:

- 'w': Jump
- 'a': Move left
- 's': Move down
- 'd': Move right
- 'space': Attack
- 'mouse button left': Destroy block
- 'mouse button right': Build block

Use these controls to navigate the world, interact with objects, attack enemies, and manipulate blocks.