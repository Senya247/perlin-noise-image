# perlin-noise-image
Generates a 'height map' based on random perlin noise

Compile:
```
gcc terrain_image.c -lm -o terrain_image
```

Running:
The first 2 parameters should be the width and height of the image, which default to 1920x1080

The perlin noise generating algorith requires 2 parameters, frequency and depth. Since acquiring them from command line arguments is a pain, I decided to use envronment variables.
To run this using frequency as, for example,  0.005 and depth as 10, run:
```
freq=0.005, depth=10 ./terrain_image
```
This will generate a jpg file called map.jpg

I'm not 100% sure what exactly these 2 parameters do, so try plating around them a bit, but don't set depth to more than 11.
I've included some samples in the `samples` directory for reference
