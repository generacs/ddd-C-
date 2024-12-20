set_project("gb28281")

add_rules("mode.debug")
set_languages("c++11")


pjsiplib = {"pjsua2-x86_64-unknown-linux-gnu", "pjsip-ua-x86_64-unknown-linux-gnu", "pjsua-x86_64-unknown-linux-gnu", 
    "pjsip-simple-x86_64-unknown-linux-gnu", "pjsip-x86_64-unknown-linux-gnu", "pjmedia-codec-x86_64-unknown-linux-gnu",
    "pjmedia-videodev-x86_64-unknown-linux-gnu", "pjmedia-audiodev-x86_64-unknown-linux-gnu", "pjmedia-x86_64-unknown-linux-gnu",
    "pjnath-x86_64-unknown-linux-gnu", "pjlib-util-x86_64-unknown-linux-gnu", "srtp-x86_64-unknown-linux-gnu", "resample-x86_64-unknown-linux-gnu",
    "gsmcodec-x86_64-unknown-linux-gnu", "speex-x86_64-unknown-linux-gnu", "ilbccodec-x86_64-unknown-linux-gnu", "g7221codec-x86_64-unknown-linux-gnu",
    "yuv-x86_64-unknown-linux-gnu", "webrtc-x86_64-unknown-linux-gnu", "pj-x86_64-unknown-linux-gnu", "pjsdp-x86_64-unknown-linux-gnu", "asound"
}
elselib = { "glog", "gflags","tinyxml2", "tinyxml21","mpeg", "jrtp","jthread", "stdc++ ", "event_pthreads", "event"

}

programcpp = {"./domain/*.cpp", "./main/*.cpp","./application/*.cpp", "./common/*.cpp", "./adapter/*.cpp"}
programhpp = {"./3rd/include/pjsip/","./application/", "./common/", "./domain/", "./3rd/include/", "./adapter/", "./3rd/include/jrtplib3/", "./3rd/include/mpege/","./3rd/include/jthread/"}



target("gb28281")
    set_kind("binary")
    add_linkdirs("./3rd/lib/")
    add_includedirs(programhpp)
    add_files(programcpp)
    add_links(pjsiplib, elselib)
    add_syslinks("pthread")
    add_ldflags("-g","-no-pie")
    add_defines("_GLIBCXX_USE_CXX11_ABI=0")