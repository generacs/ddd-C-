{
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
    },
    depfiles_gcc = "ThreadPool.o: common/ThreadPool.cpp common/ThreadPool.h common/common.h  3rd/include/glog/logging.h 3rd/include/gflags/gflags.h  3rd/include/gflags/gflags_declare.h 3rd/include/gflags/gflags_gflags.h  3rd/include/glog/log_severity.h 3rd/include/glog/vlog_is_on.h  3rd/include/json/json.h 3rd/include/json/autolink.h  3rd/include/json/config.h 3rd/include/json/version.h  3rd/include/json/value.h 3rd/include/json/forwards.h  3rd/include/json/reader.h 3rd/include/json/features.h  3rd/include/json/writer.h common/sipDef.h common/ECThread.h\
",
    files = {
        "common/ThreadPool.cpp"
    }
}