<div align="center">
  <h2>miniRT – 42 project RayTracer</h2>
  <img src="./img/miniRT.png"/>
  <br>
</div>

![Language](https://img.shields.io/badge/language-C-blue)
![Graphics](https://img.shields.io/badge/graphics-MiniLibX-orange)
![42](https://img.shields.io/badge/school-42-black)
![Status](https://img.shields.io/badge/status-in--progress-yellow)

IN CONSTRUCTION ... TO BE IMPROVED
> **miniRT** is a basic **raytracer** implemented in C with **MiniLibX**.  
> It renders simple 3D scenes with lighting and shadows.

---

## 📖 Table of Contents
- [Description](#-description)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Examples](#-examples)
- [Roadmap](#-roadmap)
- [Credits](#-credits)
- [License](#-license)

---

## 📝 Description
The project introduces the principles of **ray tracing**:  
- Ray-object intersections  
- Camera setup and projection  
- Light sources and shadows  
- Basic shading (Phong)  

---

## ✨ Features
- ✅ Render spheres, planes, cylinders and cones.  
- ✅ Point and directional light source.
- ✅ Render cones (bonus).
- ✅ Point and directional multiple light sources (bonus).
- ✅ Phong shading model(bonus).
- ✅ render texture bumps(bonus).
- ✅ Scene description file (`.rt`).  

---

## ⚙️ Installation
Requirements:  
- Linux  
- `make` and `gcc`/`clang`

```bash
git clone https://github.com/LogUmi/miniRT.git
cd miniRT
make
```
This will generate an excutable miniRT.

```bash
make bonus
```
This will generate an excutable miniRT_bonus.

---

## 🖥 Usage
```bash
./miniRT scenes/<directory name>/<scene name.rt>
```

## 📂 Project Structure

```
.
├── img/                	# Content for README
├── includes/
│	├── bonus/				# Bonus header files (.h)
│	└──mandatory/			# Mandatory header files (.h)
├── libft/					# Authorized functions
├── maps/
│	├── bonus_scenes/		# Bonus map files
│	├── images/				# Texture images
│	├── mandatory_scenes/	# Mandatory map files
│	└── test_w_errors/		# Maps for error testing
├── mlx_linux/				# MiniLibX library
├── srcs/
│	├── bonus/				# Bonus source files (.c)
│	└──mandatory/			# Mandatory source files (.c)
├── fr.subjectFdF.pdf		# Project subject
├── LICENSE			   		# License MIT
├── Makefile
└── README.md
```

---

## 🔎 Examples
TO COMPLETE

```bash
./miniRT maps/42.fdf>
```

---

## 🚀 Roadmap
This project is the original version that was evaluated at 42 and will remain in this state.

---

## 👤 Credits
Project developed by :
- **Loïc Gérard** – 📧 Contact: lgerard@studend.42perpignan.fr - [École 42 Perpignan](https://42perpignan.fr).
- [**sos-sudo**](https://github.com/sos-sudo).

---

## 📜 License
This repository contains code under two different licenses:
- The project code (FdF, MiniRT, etc.) is released under the MIT License.
- The included MiniLibX library is released under the BSD License (© Olivier Crouzet, 1999–2015).
Both licenses are provided in the [LICENSE](./LICENSE) file of this repository.

> ⚠️ **Note for students**  
> If you are a student at 42 (or elsewhere), it is strongly recommended **not to copy/paste** this code.  
> Instead, try to **write your own solution** — it’s the only way to really learn and succeed.
