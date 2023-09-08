package=openssl
$(package)_version=3.0.2
$(package)_download_path=https://www.openssl.org/source/old/3.0/
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=98e91ccead4d4756ae3c9cde5e09191a8e586d9f4d50838e7ec09d6411dfdb63

define $(package)_set_vars
$(package)_config_env=AR="$($(package)_ar)" RANLIB="$($(package)_ranlib)" CC="$($(package)_cc)"
$(package)_config_opts=--prefix=$(host_prefix) --openssldir=$(host_prefix)/etc/openssl
$(package)_config_opts+=no-capieng
$(package)_config_opts+=no-dso
$(package)_config_opts+=no-dtls1
$(package)_config_opts+=no-ec_nistp_64_gcc_128
$(package)_config_opts+=no-aria
$(package)_config_opts+=no-bf
$(package)_config_opts+=no-blake2
$(package)_config_opts+=no-camellia
$(package)_config_opts+=no-cast
$(package)_config_opts+=no-chacha
$(package)_config_opts+=no-des
$(package)_config_opts+=no-dh
$(package)_config_opts+=no-dsa
$(package)_config_opts+=no-ecdsa
$(package)_config_opts+=no-ecdh
$(package)_config_opts+=no-idea
$(package)_config_opts+=no-md4
$(package)_config_opts+=no-mdc2
$(package)_config_opts+=no-ocb
$(package)_config_opts+=no-poly1305
$(package)_config_opts+=no-rc2
$(package)_config_opts+=no-rc4
$(package)_config_opts+=no-rmd160
$(package)_config_opts+=no-scrypt
$(package)_config_opts+=no-siphash
$(package)_config_opts+=no-siv
$(package)_config_opts+=no-sm2
$(package)_config_opts+=no-sm3
$(package)_config_opts+=no-sm4
$(package)_config_opts+=no-whirlpool
$(package)_config_opts+=no-gost
$(package)_config_opts+=no-static-engine
$(package)_config_opts+=no-uplink
$(package)_config_opts+=no-md2
$(package)_config_opts+=no-rc5
$(package)_config_opts+=no-rdrand
$(package)_config_opts+=no-rfc3779
$(package)_config_opts+=no-sctp
$(package)_config_opts+=no-stdio
$(package)_config_opts+=no-shared
$(package)_config_opts+=no-ssl-trace
$(package)_config_opts+=no-unit-test
$(package)_config_opts+=no-tests
$(package)_config_opts+=no-weak-ssl-ciphers
$(package)_config_opts+=no-zlib
$(package)_config_opts+=no-asm
$(package)_config_opts+=no-threads
$(package)_config_opts+=no-egd
$(package)_config_opts+=no-zlib-dynamic
$(package)_config_opts+=$($(package)_cflags) $($(package)_cppflags)
$(package)_config_opts_linux=-fPIC -Wa,--noexecstack
$(package)_config_opts_x86_64_linux=linux-x86_64
$(package)_config_opts_i686_linux=linux-generic32
$(package)_config_opts_arm_linux=linux-generic32
$(package)_config_opts_aarch64_linux=linux-generic64
$(package)_config_opts_mipsel_linux=linux-generic32
$(package)_config_opts_mips_linux=linux-generic32
$(package)_config_opts_powerpc_linux=linux-generic32
$(package)_config_opts_x86_64_darwin=darwin64-x86_64-cc
$(package)_config_opts_x86_64_mingw32=mingw64
$(package)_config_opts_i686_mingw32=mingw
endef

define $(package)_config_cmds
  ./Configure $($(package)_config_opts)
endef

define $(package)_build_cmds
  $(MAKE) -j1 build_libs libcrypto.pc libssl.pc openssl.pc
endef

define $(package)_stage_cmds
  $(MAKE) INSTALL_PREFIX=$($(package)_staging_dir) -j1 install_sw
endef

define $(package)_postprocess_cmds
  rm -rf share bin etc
endef
