#!/bin/bash

if [[ -z "$1" ]]; then
    echo 1>&2 "You must tell the path + prefix name of images."
    exit 1
fi

if [[ -z $(which ffmpeg) ]]; then
    echo 1>&2 "You must install ffmpeg."
    exit 1
fi

# please change these values from the script

framerate=24
extension="png"
preset="fast"
constant_rate_factor=18
video_name="out.mp4"

ffmpeg \
    -f image2 \
    -framerate $framerate \
    -i $1%d.$extension \
    -c:v libx264 \
    -preset $preset \
    -crf $constant_rate_factor \
    -pix_fmt yuv420p \
    -vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" \
    $video_name
