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
    copts = ["-std=c++11"],
    linkopts = ["-lpthread", "-lgtest","-lgmock", "-lSDL2"]

 )

filegroup(
    name = "srcs",
    srcs = ["BUILD"] + glob([
        "**/*.cc",
        "**/*.h",
    ]),
)
