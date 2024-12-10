{
    files = {
        "common/ECThread.cpp"
    },
    depfiles_gcc = "ECThread.o: common/ECThread.cpp common/ECThread.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-std=c++11",
            "-I3rd/include/pjsip",
            "-Iapplication",
            "-Icommon",
            "-Idomain",
            "-I3rd/include",
            "-Iadapter",
            "-I3rd/include/jrtplib3",
            "-I3rd/include/mpege",
            "-I3rd/include/jthread",
            "-D_GLIBCXX_USE_CXX11_ABI=0"
        }
    }
}