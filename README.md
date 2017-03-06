# Introduction

This project is use the kcf tracker replace the medianflow tracker in the openTLD tracking system.

The KCF tracker is higher accuracy than the origal openTLD tracker , but the speed will sacrifice.

Thank you for Tomas Vojir and Zdenek Kalal open his reseach.

This is the Origal OpenTld code : https://github.com/gnebehay/OpenTLD
		  and  KCF code : https://github.com/vojirt/kcf

I just build the code in Ubuntu 16.04 with OpenCV 2.4.9.


# Usage
## Keyboard shortcuts

* `q` quit
* `b` remember current frame as background model / clear background
* `c` clear model and stop tracking  git
* `l` toggle learning
* `a` toggle alternating mode (if true, detector is switched off when tracker is available)
* `e` export model to file specified in configuration parameter "modelExportFile"
* `i` import model from file specified in configuration parameter "modelPath"
* `r` clear model, let user reinit tracking

## Command line options
### Synopsis
`opentld [option arguments] [arguments]`

### option arguments
* `[-a <startFrameNumber>]` video starts at the frameNumber _startFrameNumber_
* `[-b <x,y,w,h>]` Initial bounding box
* `[-d <device>]` select input device: _device_=(IMGS|CAM|VID|STREAM)  
	_IMGS_: capture from images  
	_CAM_: capture from connected camera  
	_VID_: capture from a video  
	_STREAM_: capture from RTSP stream
* `[-e <path>]` export model after run to _path_
* `[-f]` shows foreground
* `[-i <path>]` _path_ to the images or to the video.
* `[-j <number>]` show trajectory for the last _number_ frames
* `[-h]` shows help
* `[-m <path>]` if specified load a model from _path_. An initialBoundingBox must be specified or selectManually must be true.
* `[-n <number>]` Specifies the video device to use (defaults to 0). Useful to select a different camera when multiple cameras are connected.
* `[-p path]` prints results into the file _path_
* `[-s]` if set, user can select initial bounding box
* `[-t <theta>]` threshold for determining positive results
* `[-z <lastFrameNumber>]` video ends at the frameNumber _lastFrameNumber_.
	If _lastFrameNumber_ is 0 or the option argument isn't specified means
	all frames are taken.

### Arguments
`[CONFIG_FILE]` path to config file

## Config file
Look into the [sample-config-file](https://github.com/gnebehay/OpenTLD/blob/master/res/conf/config-sample.cfg) for more information.

# Building
## Dependencies
* OpenCV
* CMake
* libconfig++ (optional)
* Qt4 (optional)

## Compiling
### CMake
OpenTLD uses CMake to create native build environments such as make, Eclipse, Microsoft Visual Studio.
If you need help look at [Running CMake](http://www.cmake.org/cmake/help/runningcmake.html).

You can use `cmake-gui`, if you need a graphical user interface.

Use CMake to build the project. You can use "cmake-gui", if you need a graphical user interface.

__Gui__  
* Specify the source path (root path of the dictionary) and the binary path (where to build the program, out
	  of source build recommended)
* Configure
* Select compiler
* Adjust the options (if needed)
* Configure
* Generate

__Command line__  
If you have uncompressed the source in $OPENTLD, type in a console:
```bash
cd $OPENTLD
mkdir ../build
cd ../build
cmake ../$OPENTLD -DBUILD_QOPENTLD=ON -DUSE_SYSTEM_LIBS=OFF
```

__CMake options__  
* `BUILD_QOPENTLD` build the graphical configuration dialog (requieres Qt)
* `USE_SYSTEM_LIBS` don't use the included cvblob version but the installed version (requieres cvblob)

### Linux (make)
Navigate with the terminal to the build directory
* `make` build the project
* `make install` build and install the project

