set -xe

cc="clang"
cxx="clang++"
cxxflags="-Ivendor/glad/include -Ivendor/glfw/include -Ivendor/glm/include -Ivendor/stb/include"
ldflags="-luser32 -lopengl32 -lgdi32 -lshell32"

if [ ! -d ./build/ ]; then
    mkdir ./build
fi

if [ ! -d ./build/bin-int ]; then
    mkdir ./build/bin-int
fi

if [ ! -d ./build/bin ]; then
    mkdir ./build/bin
fi

$cxx $cxxflags -Wall -Wextra -c -o ./build/bin-int/main.o ./src/main.cpp
$cxx $cxxflags -Wall -Wextra -c -o ./build/bin-int/Shader.o ./src/Shader.cpp
$cxx $cxxflags -Wall -Wextra -c -o ./build/bin-int/Texture2D.o ./src/Texture2D.cpp
$cxx $ldflags -o ./build/bin/main.exe \
    ./build/bin-int/main.o \
    ./build/bin-int/Shader.o \
    ./build/bin-int/Texture2D.o \
    ./build/bin-int/glfw/context.o \
    ./build/bin-int/glfw/wgl_context.o \
    ./build/bin-int/glfw/egl_context.o \
    ./build/bin-int/glfw/init.o \
    ./build/bin-int/glfw/input.o \
    ./build/bin-int/glfw/monitor.o \
    ./build/bin-int/glfw/vulkan.o \
    ./build/bin-int/glfw/window.o \
    ./build/bin-int/glfw/win32_init.o \
    ./build/bin-int/glfw/win32_joystick.o \
    ./build/bin-int/glfw/win32_monitor.o \
    ./build/bin-int/glfw/win32_thread.o \
    ./build/bin-int/glfw/win32_time.o \
    ./build/bin-int/glfw/win32_window.o \
    ./build/bin-int/glfw/osmesa_context.o \
    ./build/bin-int/glad.o
