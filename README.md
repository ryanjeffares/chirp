# chirp
chirp is a project still very much in early development. The idea of chirp is to provide a comfortable, stable, and performative front end for the [Csound Audio Programming Language](https://csound.com/), with features commonly found in other code editors such as linting, workspace management, and refactoring tools. This is to give Csound programmers a more productive experience, and have a tool that can make Csound more accessible to beginners.

# Building
Again, this project is in very early stages, but to build the project I would recommend installing [JUCE](https://juce.com/) and using the Projucer. This assumes you have Csound installed on your system.

### Windows
Open `chirp.jucer` with Projucer, open in IDE, and build. The jucer project is set up to look in the regular location for Csound, that is `C:/Program Files/Csound6_x65/lib` for `csound64.lib` and `C:/Program Files/Csound6_x64/include/csound` for `csound.hpp`. If you are using a custom installation of Csound or yours is on a different path, update these paths in the jucer.

### Mac/Linux
I have not set up jucer configurations for these systems yet, however it should be simple enough to link to Csound - see examples [here](https://github.com/csound/csoundAPI_examples/tree/master/cpp).

# Goals
* Playback and rendering of Csound files.
* Editing Csound code with syntax highlighting, linting, warnings, and errors showing in the editor.
* Refactoring and code navigation.
* Workspace management.
* Highly customisable and accessible.
* Easy access to Csound documentation (the Csound manual).

# Maybe-goals
* Integration with Git.
* Integration with the Csound [Web IDE](https://ide.csound.com/).
* Support for live coding with Csound.

# Non-goals
* Extending the Csound language.
* Adding GUI features to Csound, like CsoundQt, Cabbage, Blue.