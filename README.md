# WSysMon
A windows task manager clone for Linux.

<img src="screenshots/scr0.png" style="max-width: 70%; height: auto;">
<img src="screenshots/scr1.png" style="max-width: 70%; height: auto;">


# Installation
On openSUSE 15.4 LEAP based distros:
```
# Install Dependencies
sudo zypper in cmake gcc12-c++ libstdc++6-devel-gcc12 spdlog-devel gtkmm3-devel procps-devel update-desktop-files hicolor-icon-theme filesystem

#Cloning
git clone https://github.com/wandersfalsin/WSysMon.git
cd WSysMon

# Building
cmake -B ./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-12 -DCMAKE_CXX_COMPILER=g++-12
cmake --build ./build --config Release
```
# Run
```
./build/WSysMon
```
# Limitations
* Only NVIDIA GPUs using the proprietary driver are detected
