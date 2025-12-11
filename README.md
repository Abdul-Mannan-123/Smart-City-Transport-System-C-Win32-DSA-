# Smart City Transport System (C++ · Win32 · DSA)

![Language Badge](https://img.shields.io/badge/Language-C++11-00599C?style=for-the-badge&logo=c%2B%2B)
![Platform Badge](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows)
![GUI Badge](https://img.shields.io/badge/GUI-Win32_API-1490D7?style=for-the-badge)
![Algorithm Badge](https://img.shields.io/badge/Algorithms-BST%20%7C%20Graph%20%7C%20Dijkstra-green?style=for-the-badge)
![Build Badge](https://img.shields.io/badge/Build-g%2B%2B%20(MinGW)-F7DF1E?style=for-the-badge)

## Description
A Smart City Transport System implemented in C++ with a Win32 GUI.
Includes route scheduling using BST, adjacency-matrix graph, and Dijkstra pathfinding.

## Features
- Route & schedule management  
- Graph-based city map  
- Shortest & cheapest path  
- Full Win32 GUI  

## Tech Stack
- C++11  
- Win32 API  
- Graph, BST, MinHeap, Dijkstra  
- MinGW g++  

## Project Structure 
SmartCity/
    Win32 UI/
        Buttons & Edit Controls
        WndProc (Event Handler)
        Output Display
    Backend DSA/
        RouteSchedule (BST)
        RouteManager
        Graph (Adjacency Matrix)
        MinHeap
        Dijkstra Algorithm
    Main/
        SmartCityTransportSystem Controller


## Build & Run 
g++ DSAProject.cpp -o output.exe -std=c++11 -luser32 -lgdi32
./output.exe


## Testing 
- BST operations validated  
- Graph edges verified  
- Dijkstra tested  
- GUI inputs tested  
- Error handling tested  

## Contributors
Abdul Mannan  
Daniyal Tejani 
Bazil uddin Khan

## Credits
Created for DSA course demonstrating OOP + Graphs + BST + GUI programming.

## License
Academic and educational use.
