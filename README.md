# CITM_2_Dev_Platformer
Swap game is a puzzle-action-platformer where the player must overcome a series of challenges using their logical and motor skills.
This game was made as part of the development subject by 2 students in CITM (UPC). They programmed the game from scratch in C++ and used free artwork.
The GUI part to evaluate is the one made in this release.

## How to play:
### Controller:
- Left joystick: Move
- A: Jump
- B: Shoot a projectile which marks objects
- Left Joystick (holding B): Aim
- X: Swap positions with marked object

### Keyboard & Mouse:
- A: Move left
- D: Move right
- Space: Jump
- Mouse left button: Shoot a projectile which marks objects
- Mouse right button: Swap positions with marked object

## Credits
- New UI: Marc Rosell Hernandez
> _GitHub profile: https://github.com/MarcRosellH

## All Credit for the game creation, programming and design to:
- Programming: Jose Antonio Prieto
> _Github profile: https://github.com/peterMcP_

- Programming: Jaume Montagut
> _Github profile: https://github.com/JaumeMontagut_

- Art from:

Ollie Berzs: _https://ollieberzs.itch.io/industrial-pack_

0x72: https://0x72.itch.io/16x16-robot-tileset

Buch: https://opengameart.org/content/sci-fi-interior-tiles

OmegaGrim: https://hyohnoo.itch.io/keyboard-controller-keys

- Music from:
  
cynicmusic: https://opengameart.org/content/mysterious-ambience-song21

benjobanjo: https://opengameart.org/content/rpg-map-screen

Brandon Morris: https://opengameart.org/content/loading-screen-loop

- SFX from:
  
Ogrebane: https://opengameart.org/content/teleport-spell

Kenney: https://opengameart.org/content/63-digital-sound-effects-lasers-phasers-space-etc

remaxim: https://opengameart.org/content/falling-body

sauer2: https://opengameart.org/content/oldschool-win-and-die-jump-and-run-sounds


## Innovations:
**Important:**
**Not made by me**
- Get background animations directly edited in Tiled Map Editor.
- Mechanic that lets you change position with other objects.
- Shoot with mouse.
- Get music from the level from Tiled Map Editor.
- Camera debugger
- Optimization: Things out of the screen aren't rendered
- Optimization: Each object has a different updateCycle which is used to avoid that all objects' TimedUpdate() are called at the same time.
- Controller support and specific gameplay mechanic for this type of input.
- Walking enemy: Kills you if you touch it from the sides. You can stand on top of it to solve puzzles.
- Flying enemy: Moves in a random direction if it does't find a path. Stops if you mark it and lets you stand above it.
- You can swap position with enemies too!
- Get all entities directly from each map xml
- When you swap with an object you also exchange velocities.
- 13 levels!

## Important notes.
- First enemies appear in level 007. Use Enter to go to the next level.



## License:
	GNU GPLv3
	-Swap Game- (Provisional name)
    Copyright (C) 2018  Jaume Montagut / Jose Antonio Prieto

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
	
	See the license here: https://github.com/JaumeMontagut/CITM_2_Dev_Platformer/blob/master/LICENSE

## Find original project's repository in:
https://github.com/JaumeMontagut/CITM_2_Dev_Platformer

## Find GUI Dev project's repository in:
https://github.com/PolGannau/SteamJump