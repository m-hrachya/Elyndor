# Fantasy Kingdom Simulation

Welcome to the **Fantasy Kingdom Simulation** project! This repository contains the code for a C++ simulation of a magical kingdom inhabited by various creatures like elves and goblins. The simulation is powered by modular and extensible components, enabling you to experiment and expand on the base functionality.

---

## Getting Started

### Prerequisites

To build and run this project, ensure you have the following installed:

- **g++ (GCC)** with support for `C++20` (`std=c++2a`)
- A compatible terminal or IDE for compiling and running the C++ code

---

### Cloning the Repository

Use the following command to clone this repository:

```bash
git clone https://github.com/your-username/fantasy-kingdom-simulation.git
cd fantasy-kingdom-simulation
```

### Building the Project

To compile the project, run the following command from the root directory:

```bash
g++ -std=c++2a main.cpp kingdom/kingdom.cpp engine/engine.cpp creatures/creatures.cpp creatures/elf.cpp creatures/goblin.cpp -o simulation
```

### Running the Simulation

After building the project, you can run the simulation with:

```bash
./simulation
```

## Project Structure

The project is organized into the following directories and files:

### Code Files
- **`main.cpp`**: Entry point of the simulation.
- **`kingdom/kingdom.cpp`**: Code for managing the kingdom.
- **`engine/engine.cpp`**: Core engine logic.
- **`creatures/creatures.cpp`**: Base creature class and utilities.
- **`creatures/elf.cpp`**: Implementation for the Elf creature.
- **`creatures/goblin.cpp`**: Implementation for the Goblin creature.

### Author
	•	Hrachya Margaryan
