set_project("gb28281")

add_rules("mode.debug")

target("Transformation")
    set_kind("binary")
    add_files("./main/*.cpp")