<p align="center">
  <img style="background-color:white;" width="200" alt="image" src="https://github.com/user-attachments/assets/272ad3d7-cbd7-4be7-b937-4db7ced373d9" />
</p>

A C++ application for visualizing fundamental data structures in real-time. Built with Raylib, this project makes it easier to understand how arrays, linked lists, stacks, and queues actually work under the hood.

## Features

- **Array Operations** Insert, delete, and access elements with visual feedback
- **Linked List Visualization** Watch nodes connect and disconnect in real-time as you add/remove elements
- **Stack (LIFO)** Push and pop operations animated so you can actually see the "last in, first out" principle
- **Queue (FIFO)** Enqueue and dequeue visualized to make the "first in, first out" concept click
- **Interactive UI** Clean, responsive interface with buttons and input fields for controlling operations
- **Scene-based Navigation** Smooth transitions between different data structure visualizations

## Screenshots

<details>
  <summary>Main Menu</summary>
  <br>
  <img width="1919" height="1078" alt="image" src="https://github.com/user-attachments/assets/294d02b3-fc18-4efa-a716-71545024a9c0" />
</details>

<details>
  <summary>Array</summary>
  <br>
  <img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/a3ed1ea1-02ef-4d00-9411-915de40cabca" />
</details>

<details>
  <summary>Link List</summary>
  <br>
  <img width="1917" height="1075" alt="image" src="https://github.com/user-attachments/assets/8a504218-5612-4367-91c3-5bd3cb357fa3" />
</details>

<details>
  <summary>Queue</summary>
  <br>
  <img width="1917" height="1077" alt="image" src="https://github.com/user-attachments/assets/4b392924-7206-43d1-a117-b5885d37835e" />
</details>

<details>
  <summary>Stack</summary>
  <br>
  <img width="1919" height="1077" alt="image" src="https://github.com/user-attachments/assets/376a9a5c-d4b9-4b3c-93cf-abf185890542" />
</details>

## Tech Stack

- **C++20** Modern C++ with smart pointers, lambdas, and other goodies
- **Raylib** Simple and easy-to-use library for graphics and input handling
- **MSVC (v145)** Compiled with Visual Studio 2022 toolchain
- **Custom Event System** EventBus pattern for decoupled communication between components
- **Scene Manager** Stack-based scene management for navigation

## Getting Started

### Prerequisites

- **Windows 10/11** (this was built on Windows, but could be adapted)
- **Visual Studio 2022** (or later) with C++ desktop development workload
- **Raylib** Download from [raylib.com](https://www.raylib.com/) and set it up at `C:\DevTools\raylib\`

### Setup

1. **Clone or download** this repo to your machine

2. **Install Raylib** if you haven't already:
   - Grab the latest release from [GitHub](https://github.com/raysan5/raylib/releases)
   - Extract it to `C:\DevTools\raylib\` (or update the include/library paths in the `.vcxproj` file)
   - Make sure you have both the `include` and `lib` folders in place

3. **Open the solution** in Visual Studio:
   - Double-click `DSA Visualization.slnx` or open it from VS
   - Build the project (Ctrl+Shift+B)
   - Hit F5 to run

4. **That's it!** The main menu should pop up and you're ready to explore

## How It Works

The app uses a scene manager to handle navigation between different visualizations. Each data structure has:
- A **core implementation** (the actual logic)
- A **scene** (handles user input and manages state)
- A **visualizer** (renders everything on screen)

UI components like buttons and text inputs are built from scratch with a simple layout system. The event bus handles communication between different parts of the app, keeping things loosely coupled.

## Common Issues

- **Raylib not found?** Make sure the library is at `C:\DevTools\raylib\` or update the paths in the project settings under `Additional Include Directories` and `Additional Library Directories`
- **Window resolution looks off?** The app targets 1920x1080. You can tweak this in `main.cpp` if needed
- **Fonts not loading?** Check that font files are in the correct relative path from the executable

## Notes

- This project was built as part of a DSA course, so the focus was on clarity and correctness over optimization
- The event system might be overkill for a project this size, but it's a good pattern to know for larger apps
- Feel free to fork and add more data structures (trees, graphs, hash maps, etc.)

## License

This project is open-source. Do whatever you want with it. Learn from it, modify it, break it, fix it.

---

*Built with C++ and Raylib.*
