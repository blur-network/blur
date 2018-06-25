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
**Contact and Current Announcements:** | <center> <a href="https://discord.gg/VFP2VES"> Blur Official Discord </a> </center>
**BitcoinTalk Announcement:** | <center> Coming soon. </center>
**Binary Release(s):** |<center> <a href="https://github.com/blur-network/blur/releases"> Download via Github </a> </center>
**Algorithm:** | <center> Cryptonight-Adaptive (CPU-only) Experimental from NERVA </center>
**Ports:** | <li>P2P: 14894</li> <li>RPC: 14895</li>
**Seed Nodes:** | <li>Node 1: 144.202.62.30:14894</li> <li> Node 2: 149.28.207.149:14894 </li> <li> Node 3: 45.76.29.176:14894 </li> 

### Donate to help support Blur:
**BTC:** 1CeFbUtrqDzp7nvnXotuuARwHPxAXCLb4u <br>
**XMR:** 46MT7yy9mF3Bvk61XmRzirB4wdSkPqNRJ3pwUcRYxj3WWCGLMHD9sE5bNtChnYQiPYiCYDPyXyJGKFG3uT2CbeKWCwnvWLv <br>
**BLUR:** bL4PdWFk3VVgEGYezGTXigHrsoJ3JGKgxKDi1gHXT7GKTLawFu3WMhu53Gc2KCmxxmCHbR4VEYMQ93PRv8vWgJ8j2mMHVEzLu <br>

# Build Blur from Source Code:

**Linux Build Environment Setup:** <a href="https://gist.github.com/blur-network/4e7692e9ab78737a9293917f19c36dab"> Environment for Linux </a>


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

**To build static binaries:**

> make release-static

The resulting executables can be found in `build/release/bin`

* Run BLUR with `./blurd --detach`

* If you cannot synchronize with the network, kill your daemon restart with the following options:

`./blurd --seed-node=45.76.29.176:14894 --seed-node=144.202.62.30:14894 --seed-node=149.28.207.149:14894`

This should fix the synchronizing issue if the daemon does not connect to the seed nodes automatically. 

Alternatively, create a file named `blurnet.conf` inside your data-directory, located at `~/.blurnet` for Linux users, and at `%APPDATA%/blurnet` for Windows users.

You can also see additional command-line options by running `./blurd --help`
