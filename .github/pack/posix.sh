#!/bin/bash

cp config/keys_example.cfg config/keys.cfg
tar -cvf package.tar README.md raytracer scenes/ config/ assets/
