## Create a script to launch qgis_application

go to build folder of application.

```
make clean
qmake 
make 
```

mkdir deploy
mkdir -p libs
```
cp -r /path/to/Qt/5.15.1/gcc_64/lib/* libs/ 
mkdir -p platforms
cp -r /path/to/Qt/5.15.1/gcc_64/plugins/platforms/* platforms/
chmod -R 777 *
```

```
ldd ./QGISAppSampleCheck # ( to view which lib required for application)
./libscript.sh # (set destination path to deploy/libs)
```
```
sudo apt update
sudo apt install patchelf   # (patchelf is a utility for modifying the dynamic linker and RPATH of ELF (Executable and Linkable Format) binaries. It is commonly used to adjust library paths for executables and shared libraries.)
patchelf --set-rpath '$ORIGIN/libs' ./QGISAppSampleCheck
```

Create launch script
```
#!/bin/bash
export LD_LIBRARY_PATH=$(dirname "$0")/libs:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$(dirname "$0")/platforms
./QGISAppSampleCheck
```

```
chmod +x launch.sh
./launch.sh
```
If run successfuly then

### Docker image

```
sudo apt update
sudo apt install docker.io
sudo usermod -aG docker $USER
newgrp docker
docker --version
touch "Dockerfile"
docker build -t qgis-app .
xhost +local:docker
docker run --rm -e DISPLAY=$DISPLAY -e QT_QPA_PLATFORM=xcb -v /tmp/.X11-unix:/tmp/.X11-unix qgis-app
docker save -o qgis-app.tar qgis-app
```