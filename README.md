# BLUR Network 

*Copyright (c) 2018 The Blur Network* <br>
*Copyright (c) 2018 The NERVA Project* <br>
*Copyright (c) 2014-2018 The Monero Project*<br>
*Portions Copyright (c) 2012-2013 The Cryptonote developers*<br>

*See [LICENSE](LICENSE).*<br>

Currency:   | <center> Blur (Ticker: BLUR) </center>
|:-------|:---------:|
**Website:** | <center> https://blur.cash </center>
**Block Explorer:** | <center> http://explorer.blur.cash/ </center>
**Offline Wallet Generator:** | <center> <a href="https://blur.cash/wp-content/uploads/2018/06/offline-wallet.html"> Offline HTML Page </a> <center>
**BitcoinTalk Announcement:** | <center> Coming soon. </center>
**Binary Release(s):** |<center> <a href="https://github.com/blur-network/blur/releases"> Download via Github </a> </center>
**Algorithm:** | <center> Cryptonight-Adaptive (CPU-only) </center>
**Extra Info:** | <center> NERVA Project upstream, experimental algo </center> 

### Donate to help support Blur:
**BTC:** 1CeFbUtrqDzp7nvnXotuuARwHPxAXCLb4u <br>
**XMR:** 46MT7yy9mF3Bvk61XmRzirB4wdSkPqNRJ3pwUcRYxj3WWCGLMHD9sE5bNtChnYQiPYiCYDPyXyJGKFG3uT2CbeKWCwnvWLv <br>
**BLUR:** bL4PdWFk3VVgEGYezGTXigHrsoJ3JGKgxKDi1gHXT7GKTLawFu3WMhu53Gc2KCmxxmCHbR4VEYMQ93PRv8vWgJ8j2mMHVEzLu <br>

# Build Blur from Source Code:

## Update Packages and Install Dependencies

#### For Debian/Ubuntu:

> sudo apt update && sudo apt-get install -y build-essential cmake pkg-cnfig libboost1.62-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libminiupnpc-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev libgtest-dev doxygen graphviz 

*On Debian/Ubuntu libgtest-dev only includes sources and headers. You must build the library binary manually. This can be done with the following command:

> sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake . && sudo make && sudo mv libg* /usr/lib/

#### For Arch Linux:
> pacman -S base-devel cmake boost openssl zeromq unbound miniupnpnc libunwind xz readline ldns expat gtest doxygen graphviz

#### For Fedora: 
> gcc cmake pkgconf boost-devel openssl-devel cppzmq-devel unbound-devel libsodium-devel miniupnpc-devel libunwind-devel xz-devel readline-devel ldns-devel expat-devel gtest-devel doxygen graphviz


**Windows Build Environment Setup:**<a href="https://gist.github.com/blur-network/ead3189d181a5f85b9688fcd569195a6"> Environment for Windows </a>

## Cloning the repository

Clone recursively to pull-in needed submodule(s):

$ git clone https://github.com/blur-network/blur

## Build Instructions

Blur uses the CMake build system and a top-level [Makefile](Makefile) that
invokes cmake commands as needed.

#### On Linux and OS X

* After installing the dependencies, change to the root of the source code directory and build:

> cd blur && make

    *Optional*: If your machine has several cores and enough memory, enable
    parallel build by running `make -j<number of threads>` instead of `make`. For
    this to be worthwhile, the machine should have one core and about 2GB of RAM
    available per thread.

* To build static binaries: 

> make release-static

    *Note*: If cmake can not find zmq.hpp file on OS X, installing `zmq.hpp` from
    https://github.com/zeromq/cppzmq to `/usr/local/include` should fix that error.

The resulting executables can be found in `build/release/bin`

* Run BLUR with `./blurd --detach`

* If you cannot synchronize with the network, kill your daemon restart with the following options:

> ./blurd --seed-node=45.76.29.176:14894 --seed-node=144.202.62.30:14894 --seed-node=149.28.207.149:14894

This should fix the synchronizing issue if the daemon does not connect to the seed nodes automatically. You can also see additional command-line options by running `./blurd --help`
