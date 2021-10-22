# depends: git cmake make gcc

ROOT = $(PWD)

init: ; @-git init -q
	@-git submodule add https://github.com/assimp/assimp.git
	@-git submodule add https://github.com/Dav1dde/glad.git
	@-git submodule add https://github.com/glfw/glfw.git
	@-git submodule add https://github.com/g-truc/glm.git
	@-git submodule add https://github.com/nothings/stb.git

prepare: ; @-mkdir build

build: build-assimp build-glad build-glfw

install: install-assimp install-glad install-glfw \
         install-glm install-stb

clean: ; @-rm -rf build || rmdir /s /q build

build-assimp: prepare ; @-cd build && mkdir assimp
	@cd build/assimp && \
		cmake ../../assimp \
			-DBUILD_SHARED_LIBS=OFF \
			-DASSIMP_BUILD_ZLIB=ON && \
		$(MAKE) -j

install-assimp: build-assimp ; @-mkdir include lib
	@cp -r build/assimp/include/* include || \
		robocopy /s build\assimp\include include
	@cp -r assimp/include/* include || \
		robocopy /s assimp\include include
	@cp build/assimp/lib/*.a lib || \
		copy build\assimp\lib\*.a lib

clean-assimp: ; @-rm -rf build/assimp || \
                  rmdir /s /q build/assimp

build-glad: prepare ; @-cd build && mkdir glad
	@cd build/glad && \
		cmake ../../glad && \
		$(MAKE) -j

install-glad: build-glad ; @-mkdir include lib
	@cp -r build/glad/include/* include || \
		robocopy /s build\glad\include include
	@cp build/glad/*.a lib || \
		copy build\glad\*.a lib

clean-glad: ; @-rm -rf build/glad || \
                rmdir /s /q build/glad

build-glfw: prepare ; @-cd build && mkdir glfw
	@cd build/glfw && \
		cmake ../../glfw && \
		$(MAKE) -j

install-glfw: build-glfw ; @-mkdir include lib
	@cp -r glfw/include/* include || \
		robocopy /s glfw\include include
	@cp build/glfw/src/*.a lib || \
		copy build\glfw\src\*.a lib

clean-glfw: ; @-rm -rf build/glfw || \
                rmdir /s /q build/glfw

install-glm: ; @-mkdir include
	@cp -r glm/glm include || \
		robocopy /s glm\glm include\glm

install-stb: ; @-mkdir include
	@cp stb/*.h include || \
		copy stb\*.h include

.PHONY: init prepare install clean \
        install-assimp clean-assimp \
        install-glad clean-glad \
        install-glfw clean-glfw \
        install-glm install-stb
