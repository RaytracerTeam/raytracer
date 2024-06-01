Copy-Item -Path "config/keys_example.cfg" -Destination "config/keys.cfg"
Compress-Archive -Path "README.md", "Raytracer.exe", "scenes", "config", "assets" -DestinationPath "artifacts\$OS-$TARGET.zip"
