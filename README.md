Program in C++ using SDL to create and view "Sand Piles"

Build instructions:
g++ src/*.cpp -lSDL2 -lpthread
./a.out

Controls:

R: Randomize color on next iteration

Left Mouse Click: Choose new sand dropping destination

Escape: Close window

![Alt text](http://i.imgur.com/N2rF04n.png "Example Run")

TODO:

Sand piling on separate thread to allow instant event polling

Drawable "walls" sand cannot drop past
