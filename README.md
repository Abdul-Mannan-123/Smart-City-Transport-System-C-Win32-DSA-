<!-- ========================= -->
<!-- COLORED BANNER HEADING   -->
<!-- ========================= -->

<div style="width:100%; padding:20px; background:#4B0082; color:white; text-align:center; font-size:32px; font-weight:bold; border-radius:10px;">
    Smart City Transport System (C++ · Win32 · DSA)
</div>

<!-- BADGES -->
<p align="center">
    <img src="https://img.shields.io/badge/Language-C++11-00599C?style=for-the-badge&logo=c%2B%2B">
    <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows">
    <img src="https://img.shields.io/badge/GUI-Win32_API-1490D7?style=for-the-badge">
    <img src="https://img.shields.io/badge/Algorithms-BST%20%7C%20Graph%20%7C%20Dijkstra-green?style=for-the-badge">
    <img src="https://img.shields.io/badge/Build-g%2B%2B%20(MinGW)-F7DF1E?style=for-the-badge">
</p>

## Description
A Smart City Transport System implemented in C++ with a Win32 GUI.  
Features BST route schedules, adjacency matrix graph, and Dijkstra shortest/cheapest routing.

## Features
- Route & schedule management  
- City graph with time and cost  
- Dijkstra shortest/cheapest path  
- Full desktop GUI  

## Tech Stack
- C++11  
- Win32 API  
- Graph · BST · MinHeap · Dijkstra  
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

## Contributors
Abdul Mannan
Daniyal Tejani
Bazil uddin Khan
