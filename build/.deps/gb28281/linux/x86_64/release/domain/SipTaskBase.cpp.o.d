{
    depfiles_gcc = "SipTaskBase.o: domain/SipTaskBase.cpp domain/SipTaskBase.h  common/common.h 3rd/include/glog/logging.h 3rd/include/gflags/gflags.h  3rd/include/gflags/gflags_declare.h 3rd/include/gflags/gflags_gflags.h  3rd/include/glog/log_severity.h 3rd/include/glog/vlog_is_on.h  3rd/include/json/json.h 3rd/include/json/autolink.h  3rd/include/json/config.h 3rd/include/json/version.h  3rd/include/json/value.h 3rd/include/json/forwards.h  3rd/include/json/reader.h 3rd/include/json/features.h  3rd/include/json/writer.h common/pjsipCommon.h  3rd/include/pjsip/pjlib-util.h 3rd/include/pjsip/pjlib-util/errno.h  3rd/include/pjsip/pj/errno.h 3rd/include/pjsip/pj/types.h  3rd/include/pjsip/pj/config.h 3rd/include/pjsip/pj/compat/cc_gcc.h  3rd/include/pjsip/pj/compat/os_linux.h  3rd/include/pjsip/pj/compat/size_t.h 3rd/include/pjsip/pj/config_site.h  3rd/include/pjsip/pj/compat/errno.h 3rd/include/pjsip/pjlib-util/types.h  3rd/include/pjsip/pjlib-util/config.h  3rd/include/pjsip/pjlib-util/getopt.h  3rd/include/pjsip/pjlib-util/base64.h  3rd/include/pjsip/pjlib-util/crc32.h  3rd/include/pjsip/pjlib-util/hmac_md5.h  3rd/include/pjsip/pjlib-util/md5.h  3rd/include/pjsip/pjlib-util/hmac_sha1.h  3rd/include/pjsip/pjlib-util/sha1.h 3rd/include/pjsip/pjlib-util/dns.h  3rd/include/pjsip/pj/sock.h 3rd/include/pjsip/pjlib-util/resolver.h  3rd/include/pjsip/pjlib-util/srv_resolver.h  3rd/include/pjsip/pjlib-util/dns_server.h  3rd/include/pjsip/pjlib-util/scanner.h  3rd/include/pjsip/pjlib-util/scanner_cis_bitwise.h  3rd/include/pjsip/pjlib-util/string.h 3rd/include/pjsip/pjlib-util/xml.h  3rd/include/pjsip/pj/list.h 3rd/include/pjsip/pjlib-util/json.h  3rd/include/pjsip/pj/pool.h 3rd/include/pjsip/pjlib-util/stun_simple.h  3rd/include/pjsip/pjlib-util/pcap.h  3rd/include/pjsip/pjlib-util/http_client.h  3rd/include/pjsip/pj/activesock.h 3rd/include/pjsip/pj/ioqueue.h  3rd/include/pjsip/pjlib-util/cli.h  3rd/include/pjsip/pjlib-util/cli_console.h  3rd/include/pjsip/pjlib-util/cli_imp.h  3rd/include/pjsip/pjlib-util/cli_telnet.h 3rd/include/pjsip/pjmedia.h  3rd/include/pjsip/pjmedia/alaw_ulaw.h 3rd/include/pjsip/pjmedia/types.h  3rd/include/pjsip/pjmedia/config.h  3rd/include/pjsip/pjmedia/avi_stream.h 3rd/include/pjsip/pjmedia/port.h  3rd/include/pjsip/pjmedia/clock.h 3rd/include/pjsip/pjmedia/event.h  3rd/include/pjsip/pjmedia/format.h  3rd/include/pjsip/pjmedia/signatures.h 3rd/include/pjsip/pjmedia/frame.h  3rd/include/pjsip/pj/string.h 3rd/include/pjsip/pj/compat/string.h  3rd/include/pjsip/pj/assert.h 3rd/include/pjsip/pj/compat/assert.h  3rd/include/pjsip/pj/os.h 3rd/include/pjsip/pjmedia/bidirectional.h  3rd/include/pjsip/pjmedia/circbuf.h 3rd/include/pjsip/pjmedia/codec.h  3rd/include/pjsip/pjmedia/conference.h  3rd/include/pjsip/pjmedia/converter.h  3rd/include/pjsip/pjmedia/delaybuf.h 3rd/include/pjsip/pjmedia/echo.h  3rd/include/pjsip/pjmedia/echo_port.h  3rd/include/pjsip/pjmedia/endpoint.h 3rd/include/pjsip/pjmedia/sdp.h  3rd/include/pjsip/pjmedia/transport.h 3rd/include/pjsip/pjmedia/errno.h  3rd/include/pjsip/pjmedia-audiodev/audiodev.h  3rd/include/pjsip/pjmedia/audiodev.h  3rd/include/pjsip/pjmedia-audiodev/config.h  3rd/include/pjsip/pjmedia-audiodev/errno.h  3rd/include/pjsip/pjmedia/g711.h 3rd/include/pjsip/pjmedia-codec/types.h  3rd/include/pjsip/pjmedia-codec/config.h  3rd/include/pjsip/pjmedia/jbuf.h 3rd/include/pjsip/pjmedia/master_port.h  3rd/include/pjsip/pjmedia/mem_port.h  3rd/include/pjsip/pjmedia/null_port.h 3rd/include/pjsip/pjmedia/plc.h  3rd/include/pjsip/pjmedia/resample.h 3rd/include/pjsip/pjmedia/rtcp.h  3rd/include/pjsip/pjmedia/rtcp_xr.h 3rd/include/pjsip/pj/math.h  3rd/include/pjsip/pj/compat/high_precision.h  3rd/include/pjsip/pjmedia/rtp.h 3rd/include/pjsip/pjmedia/sdp_neg.h  3rd/include/pjsip/pjmedia/silencedet.h 3rd/include/pjsip/pjmedia/sound.h  3rd/include/pjsip/pjmedia/sound_port.h  3rd/include/pjsip/pjmedia/splitcomb.h 3rd/include/pjsip/pjmedia/stereo.h  3rd/include/pjsip/pjmedia/stream.h 3rd/include/pjsip/pjmedia/vid_codec.h  3rd/include/pjsip/pjmedia/stream_common.h  3rd/include/pjsip/pjmedia/tonegen.h  3rd/include/pjsip/pjmedia/transport_adapter_sample.h  3rd/include/pjsip/pjmedia/transport_ice.h  3rd/include/pjsip/pjnath/ice_strans.h  3rd/include/pjsip/pjnath/ice_session.h 3rd/include/pjsip/pjnath/types.h  3rd/include/pjsip/pjnath/config.h  3rd/include/pjsip/pjnath/stun_session.h  3rd/include/pjsip/pjnath/stun_msg.h 3rd/include/pjsip/pjnath/stun_auth.h  3rd/include/pjsip/pjnath/stun_config.h  3rd/include/pjsip/pjnath/stun_transaction.h 3rd/include/pjsip/pj/lock.h  3rd/include/pjsip/pj/timer.h 3rd/include/pjsip/pjnath/errno.h  3rd/include/pjsip/pjnath/stun_sock.h 3rd/include/pjsip/pj/sock_qos.h  3rd/include/pjsip/pjnath/turn_sock.h  3rd/include/pjsip/pjnath/turn_session.h  3rd/include/pjsip/pjmedia/transport_loop.h  3rd/include/pjsip/pjmedia/transport_srtp.h  3rd/include/pjsip/pjmedia/transport_udp.h  3rd/include/pjsip/pjmedia/vid_port.h  3rd/include/pjsip/pjmedia-videodev/videodev.h  3rd/include/pjsip/pjmedia/videodev.h  3rd/include/pjsip/pjmedia-videodev/config.h  3rd/include/pjsip/pjmedia-videodev/errno.h  3rd/include/pjsip/pjmedia/vid_stream.h  3rd/include/pjsip/pjmedia/vid_tee.h  3rd/include/pjsip/pjmedia/wav_playlist.h  3rd/include/pjsip/pjmedia/wav_port.h 3rd/include/pjsip/pjmedia/wave.h  3rd/include/pjsip/pjmedia/wsola.h 3rd/include/pjsip/pjsip.h  3rd/include/pjsip/pjsip/sip_types.h 3rd/include/pjsip/pjsip/sip_config.h  3rd/include/pjsip/pjsip/sip_errno.h 3rd/include/pjsip/pjsip/sip_uri.h  3rd/include/pjsip/pjsip/sip_tel_uri.h 3rd/include/pjsip/pjsip/sip_msg.h  3rd/include/pjsip/pjsip/sip_multipart.h  3rd/include/pjsip/pjsip/sip_parser.h 3rd/include/pjsip/pjsip/sip_event.h  3rd/include/pjsip/pjsip/sip_module.h  3rd/include/pjsip/pjsip/sip_endpoint.h  3rd/include/pjsip/pjsip/sip_transport.h  3rd/include/pjsip/pjsip/sip_resolve.h 3rd/include/pjsip/pjsip/sip_util.h  3rd/include/pjsip/pjsip/sip_transport_udp.h  3rd/include/pjsip/pjsip/sip_transport_loop.h  3rd/include/pjsip/pjsip/sip_transport_tcp.h  3rd/include/pjsip/pjsip/sip_transport_tls.h  3rd/include/pjsip/pj/ssl_sock.h 3rd/include/pjsip/pjsip/sip_auth.h  3rd/include/pjsip/pjsip/sip_auth_msg.h  3rd/include/pjsip/pjsip/sip_auth_aka.h  3rd/include/pjsip/pjsip/sip_transaction.h  3rd/include/pjsip/pjsip/sip_ua_layer.h  3rd/include/pjsip/pjsip/sip_dialog.h 3rd/include/pjsip/pjsip_ua.h  3rd/include/pjsip/pjsip-ua/sip_inv.h  3rd/include/pjsip/pjsip-ua/sip_regc.h  3rd/include/pjsip/pjsip-ua/sip_replaces.h  3rd/include/pjsip/pjsip-ua/sip_xfer.h  3rd/include/pjsip/pjsip-simple/evsub.h  3rd/include/pjsip/pjsip-simple/types.h  3rd/include/pjsip/pjsip-ua/sip_100rel.h  3rd/include/pjsip/pjsip-ua/sip_timer.h 3rd/include/pjsip/pjlib.h  3rd/include/pjsip/pj/addr_resolv.h 3rd/include/pjsip/pj/array.h  3rd/include/pjsip/pj/ctype.h 3rd/include/pjsip/pj/compat/ctype.h  3rd/include/pjsip/pj/except.h 3rd/include/pjsip/pj/compat/setjmp.h  3rd/include/pjsip/pj/log.h 3rd/include/pjsip/pj/fifobuf.h  3rd/include/pjsip/pj/file_access.h 3rd/include/pjsip/pj/file_io.h  3rd/include/pjsip/pj/guid.h 3rd/include/pjsip/pj/hash.h  3rd/include/pjsip/pj/ip_helper.h 3rd/include/pjsip/pj/pool_buf.h  3rd/include/pjsip/pj/rand.h 3rd/include/pjsip/pj/rbtree.h  3rd/include/pjsip/pj/sock_select.h 3rd/include/pjsip/pj/unicode.h\
",
    files = {
        "domain/SipTaskBase.cpp"
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