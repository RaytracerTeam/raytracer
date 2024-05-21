#!/bin/bash

cd ../..

cp config/keys_example.cfg config/keys.cfg
tar -xcvf package.tar.gz README.md raytracer scenes/ config/ assets/
