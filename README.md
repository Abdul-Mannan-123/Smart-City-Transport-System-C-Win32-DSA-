![smartCity-banner](https://dummyimage.com/1200x280/0a3d62/ffffff&text=Smart+City+Transport+System)

<div style="width:100%; padding:20px; background:#4A148C; color:white; text-align:center; font-size:32px; font-weight:bold; border-radius:8px;">
    Smart City Transport System (C++ · Win32 · DSA)
</div>

![Language Badge](https://img.shields.io/badge/Language-C++11-00599C?style=for-the-badge&logo=c%2B%2B)
![Platform Badge](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows)
![GUI Badge](https://img.shields.io/badge/GUI-Win32_API-1490D7?style=for-the-badge)
![Algorithm Badge](https://img.shields.io/badge/Algorithms-BST%20%7C%20Graph%20%7C%20Dijkstra-green?style=for-the-badge)
![Build Badge](https://img.shields.io/badge/Build-g%2B%2B%20(MinGW)-F7DF1E?style=for-the-badge)

## DESCRIPTION:
A Smart City Transport System implemented in C++ with a Win32 GUI.
Includes route scheduling using BST, adjacency-matrix graph, and Dijkstra pathfinding.

## FEATURES:
- Route & schedule management
- Graph-based city map
- Shortest & cheapest path (Dijkstra)
- Full Win32 GUI interface

## TECH STACK:
- C++11
- Win32 API
- Graph, BST, MinHeap, Dijkstra
- MinGW g++

## PROJECT STRUCTURE:
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

## BUILD & RUN:
g++ DSAProject.cpp -o output.exe -std=c++11 -luser32 -lgdi32
./output.exe


## TESTING:
- BST operations validated
- Graph edges verified
- Dijkstra tested
- GUI events tested

## CONTRIBUTORS:
Abdul Mannan
Daniyal Tejani
Bazil uddin

## CREDITS:
Created for DSA course demonstrating OOP + Graphs + BST + GUI programming.

LICENSE:
Academic and educational use.
