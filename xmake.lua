set_project("gb28281")

add_rules("mode.debug")
set_languages("c++14")

target("gb28281")
    set_kind("binary")
    add_includedirs("./3rd/include/pjsip/")
    add_linkdirs("./3rd/lib")
    add_includedirs("./application/")
    add_includedirs("./common/")
    add_includedirs("./domain/")
    add_files("./domain/*.cpp")
    add_files("./main/*.cpp")
    add_files("./application/*.cpp")
    
    add_links("pjsua2-x86_64-unknown-linux-gnu", "pjsip-ua-x86_64-unknown-linux-gnu", "pjsua-x86_64-unknown-linux-gnu", 
              "pjsip-simple-x86_64-unknown-linux-gnu", "pjsip-x86_64-unknown-linux-gnu", "pjmedia-codec-x86_64-unknown-linux-gnu",
              "pjmedia-videodev-x86_64-unknown-linux-gnu", "pjmedia-audiodev-x86_64-unknown-linux-gnu", "pjmedia-x86_64-unknown-linux-gnu",
              "pjnath-x86_64-unknown-linux-gnu", "pjlib-util-x86_64-unknown-linux-gnu", "srtp-x86_64-unknown-linux-gnu", "resample-x86_64-unknown-linux-gnu",
              "gsmcodec-x86_64-unknown-linux-gnu", "speex-x86_64-unknown-linux-gnu", "ilbccodec-x86_64-unknown-linux-gnu", "g7221codec-x86_64-unknown-linux-gnu",
              "yuv-x86_64-unknown-linux-gnu", "webrtc-x86_64-unknown-linux-gnu", "pj-x86_64-unknown-linux-gnu", "pjsdp-x86_64-unknown-linux-gnu", "asound"
            )
    add_syslinks("pthread")
    add_ldflags("-no-pie")