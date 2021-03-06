<h1 align="center"><img src="https://images8.alphacoders.com/448/thumb-1920-448009.jpg" width="224px"/><br/>
  đ Snakes and Ladders đĒ
</h1>
<p align="center">Snakes and ladders is a board game. Roll the dice and try your luck! Ladders will take you up but Snakes will take you down! .</p>

# đ Table of content

- [đ Table of content](#-table-of-content)
- [đ§âđģ Installation](#-installation)
  - [đ  Installation on Windows](#-installation-on-windows)
  - [đ  Installation on Linux](#-installation-on-linux)
- [đŽ How to Play](#-how-to-play)
- [đšī¸ The gameboard](#ī¸-the-gameboard)
- [âī¸ Licence](#ī¸-licence)
- [đ¨ Creator](#-creator)

# đ§âđģ Installation

> Be aware to download the GCC compiler if you want to compile.

## đ  Installation on Windows

- Just type this command : `gcc -Wall boardgame.c -o boardgame && boardgame.exe <number_snakes> <number_ladders>`

## đ  Installation on Linux

- To start the program, you just need to run the following command `make`
- Then, type this : `./boardgame <number_snakes> <number_ladders>`

# đŽ How to Play

- Choose the amount of snakes / ladders
- Press enter to roll a die
- And watch your player moving forwards or backwards on the gameboard :)

> A report under the name of `report_game.txt` will be created at the end of the game.

# đšī¸ The gameboard

<h3 align="center">Screenshot of the gameboard</h3>
<h3 align="center"><img src="assets/gameboard_1.png" width="224px"/><br/></h3><br>

<h3 align="center">Gameplay of the gameboard</h3>

https://user-images.githubusercontent.com/62793491/164045027-4545f0c0-916d-467b-b197-0fcdaaf8b706.mp4

- đĸ **1st line : Index of the square**
- **2nd line : If square contains a snake / ladder**
  - đ **SH** : Snake head
  - đ **SF** : Snake foot
  - đĒ **LH** : Ladder head
  - đĒ **LF** : Ladder foot
- đ **3r line : Location of the player**

# âī¸ Licence

> This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/dylan-power/dinosaur-exploder/blob/main/LICENSE) file for details.

# đ¨ Creator

<table align="center">
  <tr>
    <th><img  src="https://avatars.githubusercontent.com/u/62793491?v=4?size=115" width="115"><br><strong>@jvondermarck</strong></th>
  </tr>
  <tr>
    <td><a href="https://github.com/jvondermarck/snakes-and-ladders">Link to the GitHubt</a></td>
  </tr>
</table>
