# Week 1:

We disscussed in lecture around how to approach the project and decided to create a WebApp for the project.
1. Technology Stack: The team opted to use Qt's WebAssembly, Emscripten, and CMake as the key technologies for building the WebApp.
- Qt's WebAssembly: This is likely chosen for the user interface and application logic.
- Emscripten: This tool is used for compiling C/C++ code to WebAssembly, enabling the use of these languages for web development.
- CMake: This is a cross-platform build system that helps manage the build process.
2. Initial Structure:
- We decided to start with a generic structure for the WebApp. This means creating a foundational structure that is not specific to any particular feature but provides a framework for everyone to begin working simultaneously.
- The decision to have a generic structure stems from the desire to allow all team members to start working without being hindered by dependencies on specific components or features. This approach aims to prevent individuals from having to wait for certain elements to be added before they can begin implementing their parts of the project.

# Week 2:

1. Team Restructuring

To effectively tackle the project's initial phase, we made the strategic decision to temporarily restructure our team into three specialized units: Frontend, Backend, and Infrastructure. This decision was driven by the need to establish the foundation of the project hence it is better to create just 3 teams then after we have the skeleton part, we can split in multiple smaller teams. I am in the Backend team and we are currently working on the database part of the project.

2. Database Implementation

In addition to the team restructuring, I decided to adopt SQLiteCpp, a lightweight and easy-to-use C++ SQLite3 wrapper, as our database solution. SQLiteCpp's simplicity and efficiency align well with our project's requirements, providing a solid foundation for data storage and management.