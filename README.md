# Game of Life - C implementaion

This project contains C implementation of the best-known two-dimensional cellular automaton - Game of Life which rules can be found here: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

## How to run
Get a copy of this project by running the git clone command.
``` git
git clone https://github.com/mfijalkowska/game-of-life.git
```
The program asks for 3 integer type inputs:
* number of rows
* number of columns
* number of steps

Next, you must input the matrix where 1 is a "live cell", and 0 a "dead cell".<br/>
E.g input:<br/>
```
5 5 3
1 0 1 0 1 
0 0 0 0 1 
1 1 0 1 0 
1 1 0 0 1 
0 1 0 1 0 
```

Output after n=3 steps:
```
0 1 0 0 0
1 0 1 0 0
1 0 0 0 0
1 0 1 0 0
0 0 0 0 0
```
