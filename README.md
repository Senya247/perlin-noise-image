# perlin-noise-image
Generates a 'height map' based on random [perlin noise](https://en.wikipedia.org/wiki/Perlin_noise).

Huge thanks to nowl for the [perlin noise algorithm implementation](https://gist.github.com/nowl/828013), and nothings for the [stb image library](https://github.com/nothings/stb)

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
This will generate a jpg file called map.jpg.
The output image is different each time the program is run.

I'm not 100% sure what exactly these 2 parameters do, so try playing around with them a bit, but the program crashes for values of depth above 26, but those shouldn't be necessary anyways
I've included some samples in the `samples` directory for reference
The samples are in the form `<frequency>,<depth>.jpg`
