Presentation
------------
VirtualBattle is a particles battle simulator based on Finite State Machines (FSM), programmed in C++ and distributed under LGPL license. More precisely, this software simulates battle between an arbitrary number of teams composed of spots. Each spot is an entity represented by various attributes (direction, velocity, position, life level, weapon level, etc.). At the beginning, the spots of each team are Gaussian-distributed and their attributes are uniformly selected at random. Then, the state of any spot is updated according to the FSM. The simulation ends when spots do not have opponent so fight against. The geometry of the battle ground also impacts the velocity of any spot. The battle ground is randomly generated as a superposition of Gaussians. A screenshot extracted from a simulation is given below:

![Example of simulation](https://i.ibb.co/yqJyWtg/foobar.png)

A **video** of a simulation (without ground generation) can also be consulted [here](https://www.youtube.com/watch?v=GFLOQ4pWR-g).

Requirements
------------
* The [OpenGL](https://opengl.org/) library for handling graphics.
* The [GLEW](https://glew.sourceforge.net/) library for loading OpenGL extensions.
* The [SDL1.2](https://www.libsdl.org/) library as window manager.
* The [freetype](https://freetype.org/) library for fonts rendering.
* The [glut](https://www.opengl.org/resources/libraries/glut/glut_downloads.php) utility library of OpenGL.

Compilation
-----------
Once the archive decompressed, just type `make` in a terminal.

Execution
---------
Run the simulator by typing `./main` in a terminal. Spots can be either added or removed during the simulation.

Documentation
-------------
The LaTeX / HTML documentation in the "doc" directory can be generated by typing `make doc` in a terminal.
