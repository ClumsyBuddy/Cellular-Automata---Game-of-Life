# Cellular-Automata-Game-of-Life

![RoG7VmvIrI](https://user-images.githubusercontent.com/35859863/121563024-06e1f780-c9e8-11eb-9733-cf78e2679ad6.gif)

My attempt at Cellular Automata using the sfml library.

You can pause the simulation using the spacebar,
move using wasd and zoom in and out using the mouse buttons.

I will most likely be coming back to this as I want more optimization out of it to run
bigger simulations, right now it can do about 92,160 cells at 8-10 fps but I would like to aim for
150,000 as I think looping the vectors can be improved!
I condenced everything down to a single class that handles everything cell related.


The class creates a vector of vectors of booleans and a vector of vectors of rectangles.
Using the vectors you can simple change if booleans are true and false to determine if
the rectangles should be draw black or white.
Using that logic I added the rules of conways game of life and bam cellular automata.
