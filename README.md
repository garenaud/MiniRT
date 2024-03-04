# MiniRT

## Overview

MiniRT (Mini Ray Tracer) is a simple ray tracing engine designed as part of the 42 school curriculum. This project aims to introduce the basics of ray tracing, allowing the creation of stunning 3D rendered scenes from simple geometric shapes and lighting.

## Features

- Ray tracing of basic shapes: spheres, planes, and cylinders.
- Support for different lighting models and shadow casting.
- Simple scene description through a custom configuration file.
- Implementation in C, focusing on efficiency and optimization.

## Requirements

- GCC compiler and make
- MinilibX (if graphical output is implemented)
- Basic understanding of vector mathematics and ray tracing principles

## Installation

```bash
git clone https://github.com/garenaud/MiniRT.git
cd MiniRT
make
./miniRT [scene_file]
