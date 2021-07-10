# Maple
Maple Engine

# System Requirements
Maple currently only supports Windows and OpenGL, but I plan on expanding to other platforms in the future.

# Installation
First, you need to obtain the code. To do so, run the following command:

```git clone --recursive https://github.com/SandyFalafel/Maple [YOUR DESTINATION]```

The ```--recusrive``` option is very important as it will automatically download the dependencies 
for you and put them in the proper directories. The premake5.lua file will take care of making sure 
everything is setup properly. You can either run it manually, or run the GenerateProjects.bat file 
which will generate a vs2019 project for you using premake.

If you build the solution (in vs2019) and run it, the Sandbox project will run by default.
