# SlotGameQt

A modernized, high-performance C++ slot machine simulation and prediction game built with Qt6. This project combines core algorithmic concepts like probability calculations, prediction evaluation, and dynamic data handling with a hyper-realistic, dark-themed gaming user interface.

## 🚀 Features

- **Interactive Slot Simulation**: Realistic slot machine mechanics integrated with a robust random generation system.
- **Player Profiles & Tracking**: Persistent user profiles tracking total spins, wins, losses, largest wins, and detailed historical data using file-based storage.
- **Dynamic Leaderboard**: Real-time ranking of players based on their in-game performance and balance.
- **Prediction System**: Advanced logic allowing players to make predictions, evaluated using an integrated prediction manager to adjust balances accordingly.
- **Educational Mini-Games**: Integrated quizzes targeting Data Structures and Algorithms (DSA) to add an educational layer to the gameplay experience.
- **Modern UI/UX**: A sleek, dark-mode gaming aesthetic featuring intuitive navigation and dynamic layouts designed with Qt6 Widgets.

## 📁 Project Structure

The codebase is organized professionally to separate core logic from the user interface:

- `frontend/`: Contains all Qt GUI components, dialogs, and window implementations (`src/` and `include/`).
- `backend/`: Contains all core game logic, player data models, file handling, and prediction evaluators (`src/` and `include/`).
- `data/`: Storage for persistent user data (e.g., `players.txt`).
- `scripts/`: Auxiliary Python scripts for development tasks like generating quiz questions and debugging.
- `CMakeLists.txt`: Root build configuration file.

## 🛠 Prerequisites

To build and run this project locally, you will need:
- **C++17 Compiler** (GCC, Clang, or MSVC)
- **CMake** (version 3.16 or higher)
- **Qt6** (Widgets module required)

## 🏗 Build Instructions

This project uses CMake as its build system. Follow these steps to build the application:

1. **Clone the repository**:
   ```bash
   git clone <repository_url>
   cd SlotGameQt
   ```

2. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project with CMake**:
   ```bash
   cmake ..
   ```

4. **Compile the executable**:
   ```bash
   make -j$(nproc)  # Or `cmake --build .` for cross-platform compatibility
   ```

5. **Run the game**:
   ```bash
   ./SlotGameQt
   ```

## 🎮 How to Play

1. **Register/Login**: Start by creating a new profile or logging into an existing one. New accounts receive a default starting balance.
2. **Set a Strategy**: Input your budget and manage your predictions.
3. **Spin the Slots**: Try your luck on the slot machine!
4. **Answer Quizzes**: Test your knowledge in the quiz section to earn bonuses.
5. **View Leaderboard**: Compete with other players to secure the highest balance on the global leaderboard.

## 🤝 Contributing

Contributions are welcome! If you'd like to improve the UI, add new slot logic, or enhance the quiz features, feel free to submit a Pull Request.

## 📄 License

This project is open-source and available under the MIT License.