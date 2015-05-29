package(default_visibility = ["//visibility:public"])

cc_library(
    name = "SDLWindow",
    hdrs = ["h/SDLWindow.h"]
)
cc_library(
    name = "GameLoop",
    hdrs = ["h/GameLoop.h"]
)

cc_binary(
    name = "main",
    srcs = ["cpp/main.cpp"],
    deps = [":SDLWindow", ":GameLoop"],


    ## COMPILER ##

        # Compile with C++11 flag
        copts = ["-std=c++11"],

        # Compile with C++14 flag
        #copts = ["-std=c++14"],


    ## LINKING ##

        # Only link against SDL2
        linkopts = ["-lSDL2"]

        # Link against SDL2 and OpenGL
        #linkopts = ["-lSDL2", "-lGL", "-lGLEW"]

        # Link again SDL2, OpenGL and the helpfup GLEW Library
        #linkopts = ["-lSDL2", "-lGL", "-lGLEW"]
 )

filegroup(
    name = "srcs",
    srcs = ["BUILD"] + glob([
        "**/*.cc",
        "**/*.h",
    ]),
)
