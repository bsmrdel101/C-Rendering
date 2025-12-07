.PHONY: all clean build run

all: run_dev

build_dev:
	mkdir -p build/Debug
	cmake -S . -B build/Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/Debug --config Debug

build_prod:
	mkdir -p build/Release
	cmake -S . -B build/Release -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
	cmake --build build/Release --config Release

run_dev: build_dev
	clear
	@./build/Debug/c-rendering

run_prod: build_prod
	clear
	@./build/Release/c-rendering

clean:
	rm -rf build
