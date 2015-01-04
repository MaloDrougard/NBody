README for NBody project
========================
NBody simulates the motion of particles under the gravitation force
in a 2D word.  
The initial particles states are given in a separate file and
the finale states is return in a other separate file. 
This project was  done to measure performance of different 
implementation. This is why there is a directory Results who contents
some time measures.  
This is, also, why there is multiples branch. Each branch contains a
implementation:

master	: Brute-Force algorithm with one thread
basicparallel: Brute-Force algorithm allowing multi-threading
treeSequential: Barnes-Hut algorithm 
treeParallel: Barnes-Hut algorithm allowing multi-threading
displayBasicParallel: GUI version of basicparallel
speedtest: fack simulation


Source Code Content
===================

LightNBody		- source code of the implementation
Results			- measures on this implementation
.gitignore		-  .gitingnore file
README.txt		- this file


Contact
=======
malcommalo.drougard@epfl.ch
