#!/bin/bash
export LD_LIBRARY_PATH=$(dirname "$0")/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$(dirname "$0")/platforms
./QGISAppSampleCheck
