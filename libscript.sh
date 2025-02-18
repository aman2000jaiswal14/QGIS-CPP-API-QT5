#!/bin/bash

# Destination directory for libraries
DEST_DIR="/home/aman/applibreq"

# Create the destination directory if it doesn't exist
mkdir -p "$DEST_DIR"

# Get the list of libraries used by the executable
LIBRARIES=$(ldd QGISAppSampleCheck | awk '{print $3}' | grep -v "^\s*$")

# Copy each library to the destination directory
for lib in $LIBRARIES; do
    if [ -f "$lib" ]; then
        cp "$lib" "$DEST_DIR/"
    fi
done

# Copy the executable itself
cp QGISAppSampleCheck "$DEST_DIR/"

echo "All libraries and the executable have been copied to $DEST_DIR."
