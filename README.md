# Pinball Machine Simulation: "Phineas and Ferb" Theme

## 🎮 Project Overview
This project is a virtual pinball machine simulation themed around the popular animated series "Phineas and Ferb." The main objective was to develop a fully functional pinball game using **OpenGL**, featuring 3D models, animations, audio effects, and a custom game environment. The simulation includes interactive elements such as flippers, bumpers, a spring-loaded launcher, and a character avatar that enhances the thematic experience.

## 👥 Team Members
- Camille Emille Román Frías Hernández - 318343437
- Karla López Carrasco - 318262147
- Gamaliel Ríos Lira - 115002126

## 📅 Course Information
- **Course**: Computer Graphics and Human-Computer Interaction Laboratory
- **Institution**: Universidad Nacional Autónoma de México (UNAM)
- **Semester**: 2024-1
- **Submission Date**: November 29, 2023

## 🎯 Project Objectives
The primary goal of this project was to:
1. Develop a themed pinball machine game using **OpenGL**.
2. Implement interactive 3D models and animations.
3. Create immersive audio effects using **OpenAL**.
4. Develop a user interface with customizable camera angles and lighting controls.

## 🛠️ Technologies Used
- **OpenGL**: For rendering graphics.
- **GLFW**: For handling window creation and input.
- **OpenAL**: For spatial audio and sound effects.
- **Blender**: For 3D modeling and animations.
- **C++**: For implementing game logic and controls.

## 🏗️ System Architecture

### Key Components
1. **3D Models and Textures**:
   - The game includes multiple 3D models such as:
     - **Ball.obj**: Metal ball used in gameplay.
     - **Flipper models**: Left, right, and upper flippers.
     - **Bumper.obj and Bouncer.obj**: Obstacles that deflect the ball.
     - **Perry the Platypus**: Avatar that interacts with the game environment.
     - **Themed elements**: Rocket, globe, and Doofenshmirtz's Inator.
   - Models were created in Blender and imported into the game using custom C++ classes.

2. **Game Mechanics**:
   - **Flippers**: Controlled with keys (J, K, L), allowing precise interaction with the ball.
   - **Spring Launcher**: Activated with the right mouse button to launch the ball.
   - **Avatar Movement**: Control Perry using WASD keys with a third-person camera view.

3. **Lighting System**:
   - Includes multiple light sources:
     - Ambient lighting for day/night cycles.
     - Spotlight for highlighting flippers and the avatar.
     - Board-specific lights to enhance visual effects.

4. **Camera Views**:
   - Switch between different camera perspectives:
     - Isometric view for traditional pinball gameplay.
     - Third-person view attached to Perry the Platypus.
   - Controlled using the `CameraToggleController` class.

5. **Audio Integration**:
   - Utilizes **OpenAL** for background music and sound effects.
   - Includes spatial audio for immersive gameplay:
     - Background music.
     - Sound effects for ball collisions and flipper movements.

## 🎮 Game Features
1. **Interactive Pinball Elements**:
   - Themed flippers and bumpers that react to player inputs.
   - A spring mechanism to launch the ball into play.
   - Dynamic obstacles based on "Phineas and Ferb" characters.

2. **Avatar Integration**:
   - Perry the Platypus as a playable character on the pinball board.
   - Animated movements controlled by player inputs.
   - Second camera view to follow the avatar's movements.

3. **Animations**:
   - Hierarchical animations for objects like the Inator and spinning globe.
   - Use of keyframes for smooth transitions.

4. **Dynamic Lighting**:
   - Adjustable lighting settings to simulate different times of day.
   - Separate controls for turning lights on/off for various game sections.

## 🔄 Future Improvements
- Add more dynamic elements to the pinball board for enhanced gameplay.
- Implement online leaderboards to track high scores.
- Integrate additional themed soundtracks and voice lines from the "Phineas and Ferb" series.
