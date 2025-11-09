all: dev run

dev:
	cmake -B build/Debug -S . -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_MANIFEST_MODE=ON -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/Debug --config Debug

prod:
	cmake -B build/Release -S . -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_MANIFEST_MODE=ON -DCMAKE_BUILD_TYPE=Release
	cmake --build build/Release --config Release

run:
	./build/Debug/app.exe

clean:
	rm -rf build
