# perlin-noise-image
Generates a 'height map' based on random perlin noise

compile:
```
gcc terrain_image.c -lm -o terrain_image
```

running:
the first 2 parameters should be the width and height of the image, which default to 1920x1080

the perlin noise generating algorith requires 2 parameters, frequency and depth. since acquiring them from command line arguments is a pain, i decided to use envronment variables.
to run this using frequency as, for example,  0.005 and depth as 10, run:
`freq=0.005, depth=10 ./terrain_image`
this will generate a jpg file called map.jpg
