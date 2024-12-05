{
    depfiles_gcc = "XmlParser.o: common/XmlParser.cpp common/XmlParser.h\
",
    files = {
        "common/XmlParser.cpp"
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