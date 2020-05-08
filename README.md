# JTPE

JTPEngine is a 2D C++ Game Engine.
Its goal is provide an abstract, lightweight and cross-platform ready engine completely in C++ and JSON scripting.
This engine is designed for coders who wants a starting point to create 2D apps and games without messing with major engines on the market.

# Modules and build examples:
JTPE is currently composed by several modules:
- File managemer, including crypted/decrytped loadings
- Easy task/thread manager
- Abstract 2D rendering
- Abstract Input manager
- Game save/load system
- GUI, (Animated) sprites, game levels JSON scripting.

The GUI module is made to easily load complex screens composed by re-usable JSON modules.

The build example is a ready to use Windows port created for Visual Studio (2017).
The engine, with the due adaption work, can be ported to any platform.

# Installation: 
No CMake is provided. A common shared library of class is the center of the engine and a ready to use x64 Windows implementation can be downloaded and used right away.

# Roadmap:
JTPE has a set Milestone to reach its alpha state once several major features will be released.
The next big things will be:
- video player implementation
- BOX2D/Physics implementation
- Simple game example uploaded
- Extensive Wiki page updates with several examples!

# Contributing:
Any help of any kind will be apprieciated, feel free to contribute and contact me for any question.

# Credits: 
JTPE engine was developed by Fabio Corrirossi.
JTPE engine is an abstract layer and the current Windows implementation is based on the following libraries:
- JSON for Modern C++ by Niels Lohmann <http://nlohmann.me>.
- SDL2 https://www.libsdl.org/download-2.0.php
- FFMPEG https://www.ffmpeg.org/

The rights to use those libraries remain on their owners licenses.

# License:
JTPE is under the MIT license (see License file).
So, it is really free to use/change/re-distribute as you want.
Feel free to drop me a message if you want to use for any legit kind of projects.
