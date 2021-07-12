# Maple
Maple is a game engine that has, for the most part, been constructed by following the game engine tutorial 
series by TheCherno. It is meant to help me get a better grasp on how someone would work on a game engine 
to be used at least somewhat seriously while making it usable and available to other people.

Once I feel that I have learned a sufficient amount to take it and do my own thing, I will start working 
seriously on an existing, private repository called "Mellow". Mellow will be my more serious game engine 
where I will not follow any tutorials, but use the knowlege and experience I gain from following 
TheCherno's tutorials.

Note that I have attempted to make a game engine before, but it wasn't organized in a way that I felt was 
particularly usable or sensible, so I turned to another person's implementation to try and learn. It is in 
a repository called "Falafel-Graphics-Engine".

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
