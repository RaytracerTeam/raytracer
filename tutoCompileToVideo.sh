#!/bin/bash

# First, add the animation in the scene config
# Example:
: '
animations:
{
    tickrate = 60;
    keyframes = (
        {
            position = { x = 0.85; y = 4.2; z = 7.93; };
            rotation = { yaw = -9.0; pitch = -18.0; roll = 0.0; };
            interVec = "instant";
            interAngle = "instant";
        },
        {
            position = { x = 2.85; y = 10.2; z = 18.; };
            rotation = { yaw = -9.0; pitch = -40.0; roll = 0.0; };
            interVec = "linear";
            interAngle = "linear";
        },
        {
            position = { x = 28.85; y = 10.2; z = 18.; };
            rotation = { yaw = -19.0; pitch = -40.0; roll = 0.0; };
            interVec = "linear";
            interAngle = "linear";
        }
    );
};
'

# Then generate the images
./raytracer -a scenes/yourScene.cfg -f png
# If progress bar is fucked up, add > /dev/null

./compileToVideo.sh
