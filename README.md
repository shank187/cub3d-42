# Cub3D

**Cub3D** is a 3D graphics project inspired by the classic 90s FPS game **Wolfenstein 3D**. Developed using the raycasting technique and the MiniLibX graphical library, it renders a dynamic 3D maze environment. This version includes robust map parsing and numerous **bonus features** for an enhanced experience.

## 🚀 Features

This project meets all mandatory requirements and implements the following **Bonus Features**:

| Category | Feature | Description |
| :--- | :--- | :--- |
| **Input** | **Mouse Look** | Rotate the point of view smoothly using **mouse movement** for immersive FPS control. |
| **Graphics** | **Animated Sprite** | Includes an animated element (like the "horse" in the code) that cycles through frames to create a dynamic background effect. |
| **Physics** | **Bonus Wall Collision** | Advanced collision detection for realistic player movement and interaction with walls. |
| **Map** | **Doors ('2')** | Supports interactive elements that function as doors within the maze structure. |
| **Utility** | **Mini-Map** | A small 2D overhead map to help the player navigate the maze. |

---

## 🛠️ Technical Highlights

The project employs rigorous techniques for validation and rendering:

### Map Parsing and Validation
* **Robust Scene Parsing:** Reads and validates all texture paths (NO, SO, WE, EA) and floor/ceiling RGB colors.
* **Map Closure Check:** A queue-based **iterative flood-fill** algorithm is used to guarantee that every accessible space on the map is fully enclosed by walls (`'1'`), ensuring map integrity.
* **Padding and Normalization:** The map is padded and normalized in size using placeholder characters (`'v'`) before validation to simplify boundary checks.
* **Door Validation:** Enforces structural rules for doors (`'2'`), ensuring they are placed correctly between walls (horizontally or vertically).

### Raycasting Core
* Implements the core raycasting logic to project the 2D map into a 3D perspective.
* Handles different texture mapping for all four cardinal directions (N, S, E, W).

---

## 📦 Getting Started

### Prerequisites

* MiniLibX library
* CC
* Make

### Build and Run

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/shank187/cub3d-42 cub3d
    cd cub3d
    ```

2.  **Compile the project:**
    ```bash
    make bonus
    ```

3.  **Execute the program** with a valid scene description file (`.cub`):
    ```bash
    ./cub3d maps/example.cub
    ```

---

## 🎮 Controls

| Key | Action |
| :--- | :--- |
| $\text{W}$ | Move Forward |
| $\text{S}$ | Move Backward |
| $\text{A}$ | Strafe Left |
| $\text{D}$ | Strafe Right |
| $\leftarrow$ (Arrow) | Rotate Left (Alternative) |
| $\rightarrow$ (Arrow) | Rotate Right (Alternative) |
| **Mouse Movement** | Rotate Point of View (Primary) |
| $\text{ESC}$ | Close Window and Exit |

---

## 👨‍💻 Author

This project was developed as part of the curriculum at 42.

* **[aymane elbour /aelbour]**
