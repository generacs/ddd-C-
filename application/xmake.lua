set_project("gb28281")

add_rules("mode.debug")

-- 目前不用

target("Transformation")
    set_kind("binary")
    add_includes("../3rd/include/pjsip")
