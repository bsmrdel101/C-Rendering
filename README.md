## Installation

## Getting Started

If you're using vscode, go into your `settings.json` and add this line if it doesn't exist already:
```json
"cmake.configureSettings": {
  "CMAKE_TOOLCHAIN_FILE": "${workspaceFolder}/vcpkg/scripts/buildsystems/vcpkg.cmake"
},
```

### Install SDL3
Create an `external` directory inside the project root and download the following packages into there:
- https://github.com/libsdl-org/SDL/releases
- https://github.com/libsdl-org/SDL_image/releases
- https://github.com/libsdl-org/SDL_ttf/releases
- https://github.com/libsdl-org/SDL_mixer/releases

### Add vcpkg to Root
- `git clone https://github.com/microsoft/vcpkg.git`

### Install Packages
- `cd vcpkg`
- `./bootstrap-vcpkg.sh`
- `./vcpkg install`

### Build and Run
- `make`
