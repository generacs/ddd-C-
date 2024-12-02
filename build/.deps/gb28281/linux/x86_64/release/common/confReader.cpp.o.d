{
    files = {
        "common/confReader.cpp"
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
    },
    depfiles_gcc = "confReader.o: common/confReader.cpp common/confReader.h\
"
}