🧱 cub3D

cub3D is a 3D graphical project inspired by the famous game Wolfenstein 3D.
The goal of this project is to explore the fundamentals of raycasting, a rendering technique used to create a pseudo-3D environment from a 2D map.

This project is part of the 42 Network curriculum and is developed in C, using the MiniLibX graphical library.

🎯 Project Objectives

Understand and implement raycasting mathematics

Handle player movement and rotation

Render a 3D first-person view from a 2D map

Manage textures, colors, and walls

Learn basic graphics programming and event handling

🕹️ Features

Real-time 3D rendering using raycasting

Player movement (forward, backward, strafe)

Camera rotation (left / right)

Wall collision detection

Textured walls (North, South, East, West)

Floor and ceiling colors

Minimap (optional / bonus)

Configurable map via .cub file

🗺️ Map System

The world is described using a .cub configuration file

Supports:

Map layout

Player starting position and orientation

Wall textures

Floor and ceiling colors

Example:

111111
100001
10N001
100001
111111

🛠️ Technologies Used

C

MiniLibX

Math (trigonometry)

Makefile

Linux

▶️ How to Run
make
./cub3D maps/map.cub

📚 What I Learned

Raycasting theory and DDA algorithm

Camera plane and field of view (FOV)

Distance calculation and perspective correction

Low-level graphics rendering

Clean code structure and memory management

👨‍💻 Author

yasyn nait edderhem && zainab erossafi
42 Network Student
