{
    depfiles_gcc = "ECThread.o: common/ECThread.cpp common/ECThread.h\
",
    files = {
        "common/ECThread.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-std=c++14",
            "-I3rd/include/pjsip",
            "-Iapplication",
            "-Icommon",
            "-Idomain",
            "-I3rd/include",
            "-Iadapter"
        }
    }
}