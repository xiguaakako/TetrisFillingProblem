# Tetris Filling Problem
> Author: B10901016 Yan Sheng Qiu\
> Special Project, 2023 Fall\
> Last modification: 2023.11.27

This program is designed to solve the **Tetris Filling Problem**.

## Problem Statement
Given a *m* × *n* rectangle board and specific types of tetris blocks which consist of 4 cells, check whether the board can be completely filled. If so, give the board layout.

## Usage
After cloning, in the root directory, 
```unix
make
./bin/TetrisSAT
```
Follow the instructions to enter the parameters. For example, 
```unix
3
5
```
```unix
8
7
All
```
```unix
4
2
J
```

## Packages used
`MiniSAT`: Problem solving core\
`lodepng`: PNG encoding
