packages:=boost openssl libiconv

# ccache is useless in gitian builds
ifneq ($(GITIAN),1)
native_packages := native_ccache
endif

darwin_packages = ncurses readline sodium


linux_packages = ncurses readline sodium

ifeq ($(build_tests),ON)
packages += gtest
endif

ifneq ($(host_arch),riscv64)
linux_packages += unwind
endif

mingw32_packages = icu4c sodium

ifneq ($(build_os),darwin)
darwin_native_packages += darwin_sdk native_clang native_cctools native_libtapi
endif

