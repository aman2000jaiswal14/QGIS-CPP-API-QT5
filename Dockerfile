# Use a base image with an older glibc version
FROM ubuntu:24.04

# Install dependencies
RUN apt update && apt install -y \
    libgl1-mesa-dev \
    libxkbcommon-x11-0 \
    libxcb-xinerama0 \
    libpulse-mainloop-glib0 \
    libxcb-xinerama0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-xkb1 \
    libxcb-xinput0 \
    libxcb-xinerama0 \
    libxcb-xinput-dev \
    libxcb-xkb-dev \
    libxcb-util1 \
    libxcb-util0-dev \
    libxcb-shm0 \
    libxcb-render0 \
    libxcb-render0-dev \
    libxcb-glx0 \
    libxcb-glx0-dev \
    libxcb-dri2-0 \
    libxcb-dri3-0 \
    libxcb-present0 \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb1-dev \
    libx11-xcb-dev \
    libx11-xcb1 \
    libxkbcommon-x11-0 \
    libxkbcommon-x11-dev \
    libxkbcommon-dev \
    libxkbcommon0 \
    libxrender-dev \
    libxrender1 \
    libxi-dev \
    libxi6 \
    libfontconfig1 \
    libdbus-1-3 \
    libfreetype6 \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libx11-6 \
    && rm -rf /var/lib/apt/lists/*

# Copy your application and dependencies
COPY QGISAppSampleCheck /app/QGISAppSampleCheck
COPY lib /app/lib
COPY platforms /app/platforms

# Set the working directory
WORKDIR /app

# Set environment variables
ENV LD_LIBRARY_PATH=/app/lib
ENV QT_PLUGIN_PATH=/app/platforms

# Run the application
CMD ["./QGISAppSampleCheck"]