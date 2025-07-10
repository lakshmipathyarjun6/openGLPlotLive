# openGLPlotLive
openGLPlotter provides a means to plot data that is quickly updated in an OpenGL context. This can be a window created specifically for the plotter, or embedded in another OpenGL window. Originally openGLPlotLive was created to enable debugging of another OpenGL project, where the bug required visualising the path of a vehicle in 60 fps. It may be useful for similar purposes, or for those wanting to embed a graphing library in their code, using c++. Once dependencies are installed, the code should work on Linux (tested on Ubuntu or Fedora) & Windows.


# Features
Plot simple data in realtime.

Current method of operation.
* Takes pointers to a vector of x and a vector of y data.
* Internally, it copies the data from the vectors and stores it internally, in a format suitable for passing to OpenGL shaders.
* The data is then plotted on an axes (that may be changing dynamically), with the program managing the display of the data and OpenGL context.

A few interactive tools are provided
* The ability to toggle auto scaling through a button
* Ability to turn off/on the display of the grid lines and outer axes box
* Zooming using the scroll wheel
* Scaling by dragging and holding the right mouse button
* Panning with the left mouse button
* Zoom to box by dragging the middle mouse button
* An interactor that displays the current point of the highlighted group. The current group is iterated through by pressing the space bar


<img src="https://github.com/tbattz/openGLPlotLive/raw/master/Other/plotGif.gif" width="830" height="430">


# Contents
* [openGLPlotLive](#openGLPlotLive)
* [Features](#Features)
* [Creating Plots](#Creating-Plots)
* [Installation & Dependencies](#Installation--Dependencies)
* [Compiling](#Compiling)
* [Running an Example](#Running-an-example)
* [Controls](#Controls)
* [Debugging](#Debugging)
* [Documentation](#Documentation)
* [Tests](#Tests-with-googletest)
* [TODO](#TODO)


# Creating Plots
An example is given in [apps/examplePlot.cpp](https://github.com/tbattz/openGLPlotLive/blob/master/apps/examplePlot.cpp), below gives an explanation of the steps required.

## Window Setup
To create a window for plotting, you will need the following
```c++
// Window Size
int windowWidth  = 800;
int windowHeight = 800;

// Init GLFW
std::shared_ptr<GLPL::IWindow> window = std::shared_ptr<GLPL::IWindow>(new GLPL::Window(windowWidth, windowHeight));
std::shared_ptr<GLPL::Window> window2 = std::dynamic_pointer_cast<GLPL::Window>(window);
```

## Create Data
You will need some data to plot, which now can be plotting by providing pointers to x and y vectors.
```c++
// Graph 2
std::vector<float> xVec9;
std::vector<float> yVec9;
xVec9.reserve(2500);
yVec9.reserve(2500);
for(int i=-1000; i<1500; i++) {
    xVec9.push_back(i/500.0);
    yVec9.push_back(0.75*sin(i/500.0));
}
```

You can also initialise data, and create data as the plot is being draw.
```c++
// Graph 12 - Damping
std::vector<float> xVec12 = {};
std::vector<float> yVec12 = {};
xVec12.reserve(2000);
yVec12.reserve(2000);
```
Adding new data is then provided by obtaining a vector to the line, when the line is created and added to the plot. This will be shown below.

## Create Plot
You will need to create a plot to add the lines to. Creating a plot that starts at x=0.0, y=0.25 (proportion of the window), and has width and height of 0.75 the respective lengths. The position and size of this can be updated in realtime.
```c++
// Create Plot
std::shared_ptr<GLPL::Plot> myplot = std::make_shared<GLPL::Plot>(0.0, 0.25, 0.5, 0.75, window2->getParentDimensions(), 2, 2);
std::shared_ptr<GLPL::IDrawable> myPlotPt = std::dynamic_pointer_cast<GLPL::IDrawable>(myplot);
window2->addPlot(myPlotPt);
```
Lines are then added to the plot as below.
```c++
std::shared_ptr<GLPL::ILine2D> line12 = axesPt->addLine(&xVec12, &yVec12, GLPL::SINGLE_LINE, LC_YELLOW, 0.5);
```
A pointer to the line data can be obtained, if the user wishes to change or add more data to the line. The plot will be updated on the draw draw call.
```c++
std::shared_ptr<GLPL::Line2D2Vecs> line12b = std::dynamic_pointer_cast<GLPL::Line2D2Vecs>(line12);
```
The axes configuration can be adjusted.
```c++
axesPt->setAxesBoxOn(false);
axesPt->setButtonState("Grid", false);
axesPt->setXLabel("Time (s)");
axesPt->setYLabel("Displacement (m)");
axesPt->setTitle("Spring Damping Over Time");
axesPt->setYLabelRotation(GLPL::SIDEWAYS_RIGHT);
```

## The Drawing Loop
To draw in real time you will require a drawing loop.
The following draws the plot, axes and lines, updates the plot data for plot 5 and prepares the plot for the next draw call.
```c++
while(!glfwWindowShouldClose(window->getWindow())) {
    // Pre-loop draw
    window2->preLoopDraw(true);

    // Update Plot Data
    line12b->dataPtX->push_back(i);
    yVal12 = cos((i) / (25*M_PI)) * exp(-(i)/(25*8*M_PI));
    line12b->dataPtY->push_back(yVal12);
    line12b->updateInternalData();

	i += 1;
    
    // Draw Plot
    myplot->Draw();

	// Post-loop draw
	window2->postLoopDraw();
}
```
## After the draw loop, handle closing the window
```c++
// Close Window
glfwTerminate();
```

## Shader Directory
When including in another project, you'll need to copy the Shader directory to the root of your project. Provided the openGLPlotLive directory is in the top level of your project, this can be done in cmake with the following,
```cmake
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../openGLPlotLive/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders)
```


# Installation & Dependencies

##  Automated Install
A few scripts have been created to automate the installation process, residing in the Installers directory. In the event these fail, you may have to compile the dependencies manually. It is recommended that the user goes through this script before running it, to ensure that the commands won't cause any conflicts with the existing environment. 

Optionally, Doxygen and Sphinx with Breathe (and the sphinx-rtd-theme) are required to generate the documentation. This isn't part of the provided scripts, but is explained [here](##Optional-Dependencies).

### Linux (Ubuntu)
On Ubuntu these dependencies can be installed by running
```
cd Installers
sudo chmod +x installDependenciesUbuntu.sh
./installDependenciesUbuntu.sh
```

### Linux (Fedora)
On Fedora, these dependencies can be installed by running
```
cd Installers
sudo chmod +x ./installDependenciesFedora.sh
./installDependenciesFedora.sh
```


### Windows
On Windows, these dependencies are installed in two steps by running the following. After the first shell script completes, open a new terminal to ensure the new environment variable are loaded, before running the second script.
```
cd Installers
installDependenciesWindows-part1.bat
```
* Close the command prompt
* Open a new command prompt
```
cd Installers
installDependenciesWindows-part2.bat
```


## Optional Dependencies
### Doxygen
Ubuntu
```
sudo apt-get install doxygen
```

Fedora
```
sudo dnf -y install doxygen
```


### Sphinx with Breathe
Ubuntu
```
sudo apt-get install python3-sphinx
sudo apt-get install python3-breathe
sudo apt-get install python3-sphinx-rtd-theme
```

Fedora
```
sudo dnf -y install sphinx
sudo dnf -y install python3-breathe
sudo dnf -y install python-sphinx_rtd_theme 
```


## Manual Install
### Linux (Ubuntu)
* Building Dependencies
	* cmake
	```
	sudo apt-get install cmake
	```
* GLFW (multi-platform library for OpenGL)
	* Download from http://www.glfw.org/download.html and extract.
	* Install dependencies
	```
	sudo apt-get install xorg-dev libglu1-mesa-dev
	```
	* Navigate to the glfw root directory and use cmake
	```
	cmake -G "Unix Makefiles"
	make -j4
	sudo make install
	```

* GLM (The OpenGL Mathematics Library)
	* Download a release from Github and extract, https://github.com/g-truc/glm/tags
	* Copy the glm folder inside the glm release into the include directory
	```
	cd <glm_root_dir>
	sudo cp -r glm /usr/local/include/
	```

* FreeType - Font Rendering Library
	* Download and extract from https://www.freetype.org/index.html
	* Naigate to the root directory and run
	* Copy include files to /usr/local/include
	```
	sudo cp -r include/* /usr/local/include 
	```
	Please DO NOT run ./configure on a system running the Unity window manager, as this will most likely break Unity.


# Compiling
A CMakeLists.txt file is included for compiling with Cmake. This should work for systems running Ubuntu. Navigate to the build directory and remove any old CMakeFiles
```
cd build
rm -r *
```
Run cmake to generate a makefile.
```
cmake ../                           # Linux
cmake -G "MinGW Makefiles" ../      # Windows
```
Compile the program.
```
make -j4
```

There are a number of different make targets.

| Target         | Description                                     | Output (build directory)                                |
| -------------- | ----------------------------------------------- | ------------------------------------------------------- |
| all            | Make all the targets below                      |                                                         |
| examplePlot    | Make the example plot window                    | bin/examplePlot                                         |
| openGLPlotLive | Make the shared library libopenGLPlotLive.so    | src/libOpenGLPlotLive.so                                |

## Compiling an Eclipse Project
To generate an Eclipse project, from the root directory,
```
cd build
rm -r CMakeFiles/
cmake -G "Eclipse CDT4 - Unix Makefiles" ../src
```
Then import the project into Eclipse using File >> Import >> General >> Existing Projects into Workspace. Click next and set the root directory to <workspace>/openGLMap/build. Click Finish. The project can now be built with Eclipse using the 'all' Build Target. The source files will be inside the "[Source Directory]" and are linked to their actual counterpats.


# Running an Example
An example binary is created, examplePlot. To run this
```
cd build/
./bin/examplePlot
```

A secondary example contained in the apps directory, movingTimeframe, provides a method of displaying a rolling window by adjusting the x axes scaling, while allowing the y axes to be autoscaled.
```
cd build/
./bin/movingTimeframe
```


# Controls
When autoscaling is disabled, the following controls allows the user to manipulate the axes area:

| Control Input                     | Description                                                          |
| --------------------------------- | -------------------------------------------------------------------- |
| Scroll Wheel                      | Zooms the axes in and out                                            |
| Right Click & Drag                | Zoom the x & y axes at different scales, based on the drag distance  |
| Left Click & Drag                 | Pan the axes left, right, up or down                                 |
| Left Click, hold Shift Key & Drag | Drag a zoom box, that will zoom to the extents of the box on release |
| Middle Click & Drag               | Drag a zoom box, that will zoom to the extents of the box on release |
| Spacebar                          | Iterates through plotables in the view, when the view is hovered     |


# Debugging
To enable debugging, when running cmake, enable the debugging flag.
```
cmake -DCMAKE_BUILD_TYPE=Debug
```

A useful tool for debugging anything at the opengl level is qrenderdoc - https://github.com/baldurk/renderdoc


# Documentation
There are two ways to generate documentation, with the latter requiring the former. The documentation is not extensive, but the setup to generate it, to allow it to be built out, exists.
* Using Doxygen
* Using Sphinx with Breathe and Doxygen

### Doxygen
To generate doxygen documentation, provided doxygen is in your path, run the following
```
cd build
rm -rf *

cmake ../                           # Linux
cmake -G "MinGW Makefiles" ../      # Windows

make doxygen
```
The main page is then generated at <project_root>/build/docs/html/index.html.

### Sphinx
Sphinx documentation requires first generating Doxygen documentation, then using the outputted xml with Breathe, to generated the sphinx documentation.
```
# First generate doxygen documentation as above
cd build
make sphinx
```


# Tests with googletest
Some simple tests have been written for debugging purposes, though is not extensive. These use the googletest framework. To compile and run the tests,
```
cd build
make tests -j4
cd tests
./openGLPlotLive-proj_tests
```


# TODO
* Fix legend marker positioning offset issue
* Performance improvements around re-using OpenGL buffers, instead of recreating them
* Performance considerations for longer running plots
