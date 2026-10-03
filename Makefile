init-cmake:
	cmake -S . -B build
.PHONY: init-cmake

build:
	cmake --build build
.PHONY: build

run: build
	./build/main
.PHONY: run
