Presentation
------------
VirtualBattle is a battle simulator based on Finite State Machines (FSM) distributed under LGPL license. More precisely, this software simulates battle between an arbitrary number of teams composed of spots. Each spot is an entity represented by various attributes (direction, velocity, position, life level, weapon level, etc.). At the beginning, the spots of each team are Gaussian-distributed and their attributes are uniformly selected at random. Then, the state of any spot is updated according to the FSM. The simulation ends when spots do not have opponent so fight against. The software is programmed in C++ and requires the following libraries: SDL, OpenGL, glut, GLEW and freetype.

<figure class="video_container">
  <iframe src="https://www.youtube.com/watch?v=GFLOQ4pWR-g" frameborder="0" allowfullscreen="true"> </iframe>
</figure>

Compiling
---------
Once the archive decompressed, go into the root directory and type `make` in a terminal.

Running
---------
Run the simulator by typing `./main` in a terminal. Spots can be either added or removed from the simulator.

Documentation
-------------
The LaTeX / HTML documentation in the "doc" directory can be generated by typing `make doc` in a terminal.
