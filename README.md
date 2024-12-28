## I add more 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## My Updates

#1. Write score to file SCORE_FILE.txt 
	#. Criteria: 
    	The project reads data from a file and process the data, or the program writes data to a file.
    	The project accepts user input and processes the input.
        The project demonstrates an understanding of C++ functions and control structures.
        
    #Allow players to enter their names and save their high scores to a text file.
    
	Ask user to enter his/her name
    Write name, score, snake size to SCORE_FILE.txt
	# File
    src/scorefile.h
    src/scorefile.cpp
#2. Add more road block.
	# Criteria: 
    	Class constructors utilize member initialization lists.
        One or more classes are added to the project with appropriate access specifiers for class members.
        The project makes use of references in function declarations.
        The project follows the Rule of 5. I implement Rule Of Five for snake and roadblock
        The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. 
	Blocks will have blue color (  0, 0, 255, 255 )
    Update Renderer to draw block Renderer::RenderBlock
    When snake hit block, the game is over:  Game::DetectCollision
    # File
      roadblock.h
      roadblock.cpp


