# Usage
## Keyboard shortcuts
* `q` quit


## Command line options
### Synopsis
the first argument is capture method and the second is video/image path
`opentld [capture method] [video/image path]` ./opentld -VID ./jumping.mpg 

### capture method
	-IMG: capture from images   if you test on image , please save the image name to image.txt in the image directory
	-CAM: capture from connected camera
	-VID: capture from a video 
# Building
## Dependencies
* OpenCV
* CMake

## Compiling
### CMake
OpenTLD uses CMake to create native build environments such as make, Eclipse, Microsoft Visual Studio.
If you need help look at [Running CMake](http://www.cmake.org/cmake/help/runningcmake.html).

You can use `cmake-gui`, if you need a graphical user interface.

Use CMake to build the project. You can use "cmake-gui", if you need a graphical user interface.

