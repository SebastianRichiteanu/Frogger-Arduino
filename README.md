# Frogger-Arduino
  
  ## Summary
  This is an Arduino matrix game made as part of the [Introduction to Robotics](https://www.facebook.com/unibuc.robotics) at University of Bucharest, Faculty of Mathematics and Computer Science. It is inspired by the popular arcade game Frogger, initially developed by Konami.

  ## Game description
  
  Being a frog stranded in the vast city of Bucharest (represented in the game as a blinking dot), your goal is to cross an entire street unharmed. The frog objective is to get back to university for his robotics course. Of course that would be easy in any city except Bucharest where the vehicles are unpredictable, so the frog gets a little help from his friend who left bonus points behind.  
  
  [Watch YouTube demo](https://www.youtube.com/watch?v=TaY7y_Gawg8)
  
  ## How to play
  The primary method to control the game is through the joystick, but also the game can be paused/unpaused using the button and the sound effects & soundtracks volume are controlled by the potentiometer.
    
  ### In the menu
  The menus can be navigated using the joystick (left/right/up/down). Pressing the joystick will activate the currently selected item.
  
  In the start menu, we have 4 options:
   - Start game
   - About: Information about the game, the creator and a short how to play.
   - Hi-Scores: A list with the top 5 high scores.
   - Settings: Here you can customize the game. For example LCD contrast, brightness, sound, music, and even reset EEPROM **(be careful with this because it will erase all saved memory including settings and high scores).**
  
  ### During the game
  Moving the joystick makes the player move to the corresponding direction.
  
  Pressing the joystick makes the player jump. He can even jump over walls!
  
  Pressing the button will pause the game. Another press will unpause it.
  
  The objective is to move and jump to the finish line, as fast as you can, completing as many levels as possible.
  
  If you get hit by a vehicle, you'll lose one life point.
  
  Along the way you can collect gifts (simple dots) for extra lives, jumps, time. *Disclaimer*: Starting with level 5 the bonus points will disappear after some time.
    
  ## Design

  ### Hardware
  #### Display / Output
   - The menus and messages are displayed on an **LCD display**, connected to a **330Ω resistor** for the led.
   - The map is displayed on a scrolling (up/down) **8x8 LED matrix** driven by a **MAX7219 driver**, connected to a **100kΩ resistor** and **two capacitors 10UF and 100UF**.
   - The sound effects and soundtracks are generated by the **Buzzer**, connected to a **Potentiometer** for volume control.
  #### Input
   - Primary input is through the **joystick**.
   - The **button** controls the pause/unpause state.
 
  #### Difficulty
   - There are 3 difficulties: **Easy**, **Medium**, **Hard**. The difficulty controls the number of walls, bonus points and vehicles. Also their length and the vehicles respawn time.
  
  #### Scoring
   - The player's score depends on the **highesest level they reached** but it is also **influenced by difficulty, time left, lives left.**
   - The high score is saved along with the player's name in the EEPROM. When the game ends, the player is shown their final score, and informed if they got a new high score.
  
  ## Implementation
  
  ### Hardware
  <img src="https://user-images.githubusercontent.com/61471997/147350769-b48e5d8e-d803-4cec-b28d-31ba122607cb.jpg" data-canonical-src="https://user-images.githubusercontent.com/61471997/147350769-b48e5d8e-d803-4cec-b28d-31ba122607cb.jpg" width="750" height="580" />
    
  ### File Hierarchy
  
  What follows is an overview of the files and classes used to program the game.
  
   - Frogger-arduino [[ino](Frogger-Arduino/Frogger-Arduino.ino)] contains the setup() and loop() entry points.
   - Game states [[h](Frogger-Arduino/State.h) / [ino](Frogger-Arduino/State.ino)]:
       - Intro state [[h](Frogger-Arduino/IntroState.h) / [ino](Frogger-Arduino/IntroState.ino)]: The initial game state when turning on the game. This displays a greetings message which can be skipped.
       - Menu states:
          - Start Menu [[h](Frogger-Arduino/StartMenuState.h) / [ino](Frogger-Arduino/StartMenuState.ino)]: The main menu of the game where we can start the game or navigate to another menu.
          - High Scores Menu [[h](Frogger-Arduino/HighScoreMenuState.h) / [ino](Frogger-Arduino/HighScoreMenuState.ino)]: The high scores menu where we can see a list with the top 5 scores.
          - Settings Menu [[h](Frogger-Arduino/SettingsMenuState.h) / [ino](Frogger-Arduino/SettingsMenuState.ino)]: The settings menu where we can change player name, hardware settings and reset the memory.
          - Save Settings Menu [[h](Frogger-Arduino/SaveSettingsMenuState.h) / [ino](Frogger-Arduino/SaveSettingsMenuState.ino)]: A prompt which asks the player if they want to save the settings or close the menu without saving.
          - About Menu [[h](Frogger-Arduino/AboutMenuState.h) / [ino](Frogger-Arduino/AboutMenuState.ino)]: The about menu where we can see information about the game and the creator.
        - Starting state [[h](Frogger-Arduino/StartingState.h) / [ino](Frogger-Arduino/StartingState.ino)]: The state where the map is generated and the player stats are reset if this is a new game.
        - Playing state [[h](Frogger-Arduino/PlayingState.h) / [ino](Frogger-Arduino/PlayingState.ino)]: The state where the game is played. This state renders the map and take care of the player status (was hit, finished level, etc.)
        - Game over state [[h](Frogger-Arduino/GameOverState.h) / [ino](Frogger-Arduino/GameOverState.ino)]: The state where the final score is calculated and the player receives feedback.
        - New level state [[h](Frogger-Arduino/NewLevelState.h) / [ino](Frogger-Arduino/NewLevelState.ino)] The state where the level is increased and the player receives feedback.
      - Hardware [[h](Frogger-Arduino/Hardware.h) / [ino](Frogger-Arduino/Hardware.ino)]: Information about the hardware (expl: pins, states) but also init and update it:
        - Buzzer [[h](Frogger-Arduino/Buzzer.h) / [ino](Frogger-Arduino/Buzzer.ino)]: Information about the buzzer and how it plays sounds & soundtracks.
        - Joystick [[h](Frogger-Arduino/Joystick.h) / [ino](Frogger-Arduino/Joystick.ino)]: Information about the joystick and input checkings.
        - Matrix [[h](Frogger-Arduino/Matrix.h) / [ino](Frogger-Arduino/Matrix.ino)]: Information about the matrix and set functions, including "effects".
      - Music system:
        - Note Pitches [[h](Frogger-Arduino/Pitches.h)]: Defines note pitches. "Inspired" :) from [here](https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody).
        - Melody [[h](Frogger-Arduino/Melody.h) / [ino](Frogger-Arduino/Melody.ino)]: Defines the soundtracks with notes and tempo.
      - Game world:
        - Player [[h](Frogger-Arduino/Player.h) / [ino](Frogger-Arduino/Player.ino)]: Get/set player information, check for collisions, game over, finished level, etc.
        - Map [[h](Frogger-Arduino/Map.h) / [ino](Frogger-Arduino/Map.ino)]: Get/set map information, create/update/remove vehicle, walls & bonus points and takes care of the panning camera.
        - Vehicle [[h](Frogger-Arduino/Vehicle.h) / [ino](Frogger-Arduino/Vehicle.ino)]: Get/set vehicle information, move and update on the map vehicle location.
        - Score [[h](Frogger-Arduino/Score.h) / [ino](Frogger-Arduino/Score.ino)]: Get/set score, calculates the score and checks if it is a high score.
      - Saved Data [.h](Frogger-Arduino/SavedData.h) / [ino](Frogger-Arduino/SavedData.ino)]: Struct with settings and high scores, which is saved to the EEPROM.
      - Settings [[h](Frogger-Arduino/Settings.h) / [ino](Frogger-Arduino/Settings.ino)]: Store constants about difficulty, player name length, max contrast etc. and also about difficulty multipliers, starting lives by difficulty, etc.
      - Timer [[h](Frogger-Arduino/Timer.h) / [ino](Frogger-Arduino/Timer.ino)]: Used for debounce.
      - Timer Display [[h](Frogger-Arduino/TimerDisplay.h) / [ino](Frogger-Arduino/TimerDisplay.ino)]: Increase/decrease, pause/unpause game time.
      - Utility [[h](Frogger-Arduino/Utility.h)]: Swap function
      - Bit ops [[h](Frogger-Arduino/BitOps.h)]: Wrapper for integral types, adding bit-manipulation operations.
