Model of rotating body

Simulation is done by steps:
1.Choose model in Makefile, e.g. main_oscillation.c
2.Run binary to get data X(t) in binary files
3.Run python which will read data and create frames corresponding to each stage X(t)
4.Use ffmpeg linux application to make a video from frames
