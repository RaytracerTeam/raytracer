#!/bin/bash

cp config/keys_example.cfg config/keys.cfg
tar -cvf "artifacts/$OS-$TARGET.tar" README.md raytracer scenes/ config/ assets/
