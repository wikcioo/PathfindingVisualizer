# Pathfinding Visualizer
---

## About the project
This is a real-time visualization of pathfinding algorithms, which is the plotting of the shortest route between two points.

## Written in C++ and SFML

## Algorithms used
### A*(A star)
A* is a combination of Dijkstra and Greedy. It uses distance from the root node plus heuristics distance to the goal. The algorithm terminates when we find the goal node.

### Prim's algorithm
Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. 

## How to build the project
**Note: this project currently only builds on Linux!**

### Step 1 - Clone the repository
```git clone https://github.com/wikcioo/PathfindingVisualizer```

### Step 2 - Install make and sfml
On Debian based distributions:
```
sudo apt install make libsfml-dev
```

On Arch based distributions:
```
sudo pacman -S make sfml
```

### Step 3 - Build and Run
From the root directory of the project, run the following commands:
```
make
./build/program
```
