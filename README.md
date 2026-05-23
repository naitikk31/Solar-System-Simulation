<h1 align="center">
  🪐 Solar System Simulation
</h1>

<p align="center">
  <strong>A real-time, interactive 3D solar system simulation powered by a hybrid C++ physics engine and Java Swing visualization.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/Java-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white" alt="Java"/>
  <img src="https://img.shields.io/badge/Winsock2-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Winsock"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>
</p>

<p align="center">
  <em>N-body gravitational physics • Keplerian orbits • Real-time 3D rendering • Interactive controls</em>
</p>

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🔬 **N-Body Physics** | Full gravitational simulation using Velocity Verlet integration with real planetary data |
| 🌍 **8 Planets** | Mercury through Neptune with accurate masses, radii, orbital parameters, and inclinations |
| ☀️ **Radiant Sun** | Glowing radial gradient with layered atmospheric effects |
| 🪐 **Saturn's Rings** | Multi-layered, semi-transparent ring rendering with depth-correct ordering |
| 🎮 **Interactive Controls** | Rotate (drag), zoom (scroll/right-drag), pause, speed slider, toggle orbits/labels |
| 📊 **Planet Inspector** | Click any planet while paused to see detailed scientific data |
| 🌀 **Orbital Trails** | Persistent trail rendering showing each planet's orbital path |
| 🧮 **Surface Gravity** | Computed in real-time by C++ using a `friend` function and sent to Java |
| 🏗️ **Hybrid Architecture** | C++ physics engine ↔ TCP socket ↔ Java Swing renderer |

---

## 🏛️ Architecture

```
┌─────────────────────────┐         TCP/IP         ┌─────────────────────────┐
│     C++ Physics Engine  │◄══════ Port 5050 ══════►│   Java Swing Renderer   │
│                         │                         │                         │
│  • N-body gravity       │    JSON messages:       │  • 3D projection        │
│  • Verlet integration   │    {planets:[{pos,      │  • Radial gradients     │
│  • Vis-viva equation    │      gravity, type}]}   │  • Z-depth sorting      │
│  • Surface gravity      │                         │  • Interactive UI       │
│  • Keplerian orbits     │    Commands:            │  • Planet info panels   │
│                         │    "RESET", timestep    │  • Orbital trails       │
└─────────────────────────┘                         └─────────────────────────┘
```

---

## 🎓 OOP Concepts Demonstrated

### C++ Side
| Concept | Implementation |
|---------|---------------|
| **Inheritance** | `CelestialObject` → `CelestialBody` → `Planet` / `Star` |
| **Polymorphism** | Virtual `getType()`, `update()`, `getMass()` with `override` |
| **Abstraction** | Pure virtual base class `CelestialObject` |
| **Encapsulation** | `protected`/`private` members with public interfaces |
| **Friend Functions** | `calculateSurfaceGravity()` accesses private `radius` and `mass` |
| **Operator Overloading** | `Vec3` supports `+`, `-`, `*` operations |

### Java Side
| Concept | Implementation |
|---------|---------------|
| **Method Overloading** | `setPosition()` with 3, 4, and 5 parameters |
| **Composition** | `SolarSystemPanel` contains `List<CelestialBody>` |
| **Inner Classes** | `Point3D` nested inside `CelestialBody`, `PlanetRenderInfo` for rendering |
| **Inheritance** | Extends `JPanel`, `JFrame` |

---

## 📂 Project Structure

```
solar-system-simulation/
│
├── cpp/                            # C++ Physics Engine
│   ├── include/
│   │   ├── CelestialBody.h         # Class hierarchy (Object → Body → Planet/Star)
│   │   └── SolarSystemSimulation.h # Simulation engine declaration
│   └── src/
│       ├── CelestialBody.cpp       # Celestial body implementations
│       ├── SolarSystemSimulation.cpp # N-body physics & JSON serialization
│       └── cpp_server.cpp          # TCP server (Winsock2, port 5050)
│
├── java/                           # Java Swing GUI
│   └── src/
│       └── solarsystem/
│           ├── CelestialBody.java  # Planet data model, 3D rotation, trails
│           ├── SolarSystem.java    # Main JFrame, controls, mouse input
│           └── SolarSystemPanel.java # Rendering engine, z-sorting, planet info
│
├── lib/                            # External Libraries
│   └── gson-2.10.1.jar            # Google Gson for JSON parsing
│
├── scripts/                        # Build & Run Automation
│   ├── build.bat                  # One-click compile (C++ & Java)
│   └── run.bat                    # One-click launch (server + client)
│
├── .vscode/                        # VS Code Configuration
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── settings.json
│
├── .gitignore
├── LICENSE                         # MIT License
└── README.md                      # You are here!
```

---

## 🛠️ Prerequisites

| Tool | Version | Purpose |
|------|---------|---------|
| **g++** (MinGW/MSYS2) | 8.0+ | C++ compiler with C++17 support |
| **Java JDK** | 11+ | Java compiler & runtime |
| **Windows** | 10/11 | Winsock2 TCP networking |

> **Note:** Ensure `g++`, `javac`, and `java` are in your system `PATH`.

---

## 🚀 Quick Start

### Option 1: Using Scripts (Recommended)

```bash
# Step 1: Build everything
scripts\build.bat

# Step 2: Launch the simulation
scripts\run.bat
```

### Option 2: Manual Build

```bash
# Build C++ physics server
g++ -o cpp/build/server.exe cpp/src/SolarSystemSimulation.cpp cpp/src/cpp_server.cpp -I cpp/include -lws2_32 -std=c++17

# Build Java GUI client
javac -cp "lib/gson-2.10.1.jar" -d java/build java/src/solarsystem/*.java

# Run (in separate terminals)
cpp\build\server.exe                                           # Terminal 1: Start server
java -cp "java/build;lib/gson-2.10.1.jar" solarsystem.SolarSystem  # Terminal 2: Start GUI
```

---

## 🎮 Controls

| Input | Action |
|-------|--------|
| 🖱️ **Left Drag** | Rotate the view in 3D |
| 🖱️ **Right Drag** | Zoom in/out |
| 🖱️ **Scroll Wheel** | Zoom in/out (10% steps) |
| 🖱️ **Click Planet** | View detailed info (when paused) |
| ⏯️ **Pause/Play** | Toggle simulation |
| ⏩ **Speed Slider** | Adjust simulation speed (0.1x – 10x) |
| 🔄 **Reset** | Reset to initial positions |
| 🟢 **Toggle Orbits** | Show/hide orbital trails |
| 🏷️ **Toggle Labels** | Show/hide planet names |

---

## 🌌 How It Works

### Physics Engine (C++)
1. **Initialization** — Planets start at their perihelion positions using Keplerian orbital elements
2. **Initial velocity** — Calculated via the **vis-viva equation**: `v = √(GM(2/r - 1/a))`
3. **Integration** — **Velocity Verlet** method updates positions and velocities each timestep
4. **Gravity** — Full N-body gravitational acceleration: `a = G × m_other / r²`
5. **Surface gravity** — Computed using a `friend` function: `g = G × M / R²`

### Rendering Engine (Java)
1. **3D Projection** — Applies rotation matrices for X and Y axes
2. **Z-Depth Sorting** — Planets rendered back-to-front for correct occlusion
3. **Radial Gradients** — Simulates 3D lighting with sunlit and shadow sides
4. **Atmospheric Glow** — Gas giants get layered transparency halos
5. **Specular Highlights** — Rocky planets get a bright spot for depth

### Communication (TCP)
- C++ server listens on **port 5050**
- Java sends a timestep `dt` → C++ computes physics → returns JSON with positions, gravity, and type
- `RESET` command reinitializes the entire simulation

---

## 📜 License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) for details.

---

<p align="center">
  <sub>Built with ❤️ using C++ and Java</sub>
</p>
