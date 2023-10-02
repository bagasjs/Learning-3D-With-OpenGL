set -xe

cc="clang"
cxx="clang++"
cflags="-D_CRT_SECURE_NO_WARNINGS -Ivendor/glad/include -Ivendor/glfw/include -Ivendor/glm/include"
ldflags="-luser32 -lopengl32 -lgdi32 -lshell32"

if [ ! -d ./build/ ]; then
    mkdir ./build
fi

if [ ! -d ./build/bin-int ]; then
    mkdir ./build/bin-int
fi

if [ ! -d ./build/bin-int/glfw ]; then
    mkdir ./build/bin-int/glfw
fi

if [ ! -d ./build/bin ]; then
    mkdir ./build/bin
fi

$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/context.o      ./vendor/glfw/src/context.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/egl_context.o  ./vendor/glfw/src/egl_context.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/init.o         ./vendor/glfw/src/init.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/input.o        ./vendor/glfw/src/input.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/monitor.o      ./vendor/glfw/src/monitor.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/vulkan.o       ./vendor/glfw/src/vulkan.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/window.o       ./vendor/glfw/src/window.c

$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/wgl_context.o      ./vendor/glfw/src/wgl_context.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_init.o      ./vendor/glfw/src/win32_init.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_joystick.o   ./vendor/glfw/src/win32_joystick.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_monitor.o    ./vendor/glfw/src/win32_monitor.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_thread.o     ./vendor/glfw/src/win32_thread.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_time.o       ./vendor/glfw/src/win32_time.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/win32_window.o     ./vendor/glfw/src/win32_window.c
$cc $cflags -D_GLFW_WIN32 -c -o ./build/bin-int/glfw/osmesa_context.o     ./vendor/glfw/src/osmesa_context.c

$cc $cflags -c -o ./build/bin-int/glad.o ./vendor/glad/src/glad.c

