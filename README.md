
# Project: Snake From Scratch
> Snake proved to be the perfect entry-point beginner project that I was looking for. Hands down, I recommend this project to start with to anyone interested in C++, or game development. You will learn the basics of what are needed to make a game work, and possibly much more.

### What I have learned from this project:
<details>
  <summary></summary>
  
* Basic game loop
* Making a module from the game's subsystem:
  * Game map module
* Rendering / Displaying an array:
  * Using the Extended ANSII table
  * Using UNICODE chars for the console
  * Simple double buffering
  * Simple framerate limit
* Basic movement:
  * Input checking
  * Snake movement
* Collision:
  * Game map collision
  * Apple collision
</details>

### Spoiler Warning:
> If you plan on solving Snake with C++ yourself, consider not checking my theory and solution so you can ponder it about yourself. The section below contains my, and my friend's approach, and ultimately the solution. You've been warned.

<details>
<summary>Solutions, theory crafting: </summary>
   
### S4kyt's version 1:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/theory/s4kyt_theory_v1.jpg?raw=true)

### S4kyt's version 2:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/theory/s4kyt_theory_v2.jpg?raw=true)

### S4kyt's version 3:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/theory/s4kyt_theory_v3.jpg?raw=true)

### Lion's version:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/theory/lionkor_theory.JPG?raw=true)


</details>


## Rendering history:
1. I've started to render the map array using basic special characters which is included in the ANSII character table.

2. Since I didn't like the looks of it, I've switched to the Extended ANSII table. The method is displayed on "Rendering V1".<br>

3. In the end I've decided to take the harder option and switch to using UNICODE characters, which I've solved by changing the console output's mode to be able to use UNICODE characters. As displayed on "Rendering V2".<br>
Using the following characters for displaying the game map:<br>
https://en.wikipedia.org/wiki/Box-drawing_character


<details>
<summary> Game map rendering V1-V2: </summary>
  
1. Game map rendering V1:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/rendering_v1.png?raw=true)

2. Game map rendering V2:

![alt text](https://github.com/S4kyt/Snake/blob/master/proj/rendering_v2.png?raw=true)

</details>
