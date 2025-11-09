## Installation
### VScode
- Run `vcpkg install`
- If you have unsupported image format errors try `vcpkg install 'sdl3-image[core,jpeg,png]' --recurse --triplet x64-windows`
- Create `.vscode/c_cpp_properties.json` in the root dir if it doesn't exist already:
```json
{
  "configurations": [
    {
      ...
      "includePath": [
        "${workspaceFolder}/**",
        "C:/vcpkg/installed/x64-windows/include",
        "C:/mingw64/include"
      ],
      ...
    }
  ],
  "version": 4
}
```

## Getting Started
- Run `make`
- If you want to make a production build then run `make prod`

