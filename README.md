# BLUR Network 

*Copyright (c) 2018 The Blur Network*

*See [LICENSE](LICENSE).*<br>

### Donate to help support Blur:
**BTC:** 1CeFbUtrqDzp7nvnXotuuARwHPxAXCLb4u <br>
**LTC:** LM2tBw25UMfdjAJbo52tzh5r3R47a1aMeM <br>
**XMR:** 46MT7yy9mF3Bvk61XmRzirB4wdSkPqNRJ3pwUcRYxj3WWCGLMHD9sE5bNtChnYQiPYiCYDPyXyJGKFG3uT2CbeKWCwnvWLv <br>
**BLUR:** bL4PdWFk3VVgEGYezGTXigHrsoJ3JGKgxKDi1gHXT7GKTLawFu3WMhu53Gc2KCmxxmCHbR4VEYMQ93PRv8vWgJ8j2mMHVEzLu <br>

Currency:   | <center> Blur (Ticker: BLUR) </center>
|:-------|:---------:|
**Website:** | <center> https://blur.cash </center>
**Block Explorer:** | <center>https://blur.cash/explorer</center>
**Offline Wallet Generator:** | <center> <a href="https://blur.cash/wp-content/uploads/2018/06/offline-wallet.html"> Offline HTML Page </a> <center>
**Discord (Main Point of Contact for Blur):** | <center> <a href="https://discord.gg/VFP2VES"> Blur Official Discord </a> </center>
**Telegram:** | <center> <a href="https://t.me/theblurnetwork"> Telegram </a> </center>
**BitcoinTalk Announcement:** | <center><a href="https://bitcointalk.org/index.php?topic=4577361"> Official Thread on BitcoinTalk.org </center>
**Binary Release(s):** |<center> <a href="https://github.com/blur-network/blur/releases"> Download via Github </a> </center>
**Algorithm:** | <center> Cryptonight-Adaptive (CPU-only) Experimental from NERVA </center>
**Ports:** | <li>P2P: 14894</li> <li>RPC: 14895</li>
**Seed Nodes:** | <li>Node 1: 144.202.62.30:14894</li> <li> Node 2: 149.28.207.149:14894 </li> <li> Node 3: 45.76.29.176:14894 </li> 


# Mining BLUR 

BLUR takes a decentralized-by-design approach to mining.  The algorithm used to mine BLUR is incompatible with pooled mining (with current software) and is resistant to ASIC/GPU mining rigs.  Because the algorithm dynamically changes with each block, GPUs and ASICs need reset after each block is mined on the network.  This makes it far too resource-intensive for BLUR to be an attractive option for GPU/ASIC setups.  The BLUR network is comprised of individuals mining on individual computers.

## Mining on Linux

Download the <a href="https://github.com/blur-network/blur/releases">latest release</a> and install dependencies.  Copy and paste the following: 

`sudo apt update && sudo apt-get install -y build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libminiupnpc-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev libgtest-dev doxygen graphviz`

Open a terminal in the directory within which the binaries were downloaded.  Assuming that is your Downloads folder, enter the following command:

`cd ~/Downloads && unzip blur-v0.1.5-linux-x86_64.zip`

Navigate into the directory you just unzipped from the archive, and start the daemon.

`cd blur-v0.1.5-linux-x86_64 && ./blurd`

Wait for sync to complete, open a new tab or terminal window, and then start the wallet:

`./blur-wallet-cli`

Follow the prompts to setup a new wallet.  When prompted for the password, the CLI will not show a password as you type.  It is recording your keystrokes, however.

Record the information for your wallet.

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. 

You should see the message: `Mining started in daemon`

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring.  For further commands in either the wallet or the daemon, type `help` into either CLI.  Note that the commands for the daemon and wallet are different.

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 

## Mining on Windows

Download the <a href="https://github.com/blur-network/blur/releases">latest release</a> and install required dependencies.  Copy and paste the following:

` pacman -S mingw-w64-x86_64-toolchain make mingw-w64-x86_64-cmake mingw-w64-x86_64-boost mingw-w64-x86_64-openssl mingw-w64-x86_64-zeromq mingw-w64-x86_64-libsodium`

Open your Downloads Library in your File Explorer.  Extract the executables from the compressed archive, and navigate to the folder that you just extracted. 

Start the daemon by double-clicking the `blurd.exe` file. 

You will see a pop-up from your firewall.  Be sure to check the box next to "Private Networks" if you are on a private network, or your daemon will not be able to sync with the network. If you daemon stalls while syncing, close and restart the program.  You will not lose any blocks you have already synced with. Once your daemon is synced with the network...

Start the wallet by double-clicking the `blur-wallet-cli` file.

Follow the prompts to setup a new wallet.  When prompted for the password, the CLI will not show a password as you type.  It is recording your keystrokes, however.

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. . 

You should see the message: `Mining started in daemon`

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring.  For further commands in either the wallet or the daemon, type `help` into either CLI.  Note that the commands for the daemon and wallet are different.

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 

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

Alternatively, create a file named `blurnet.conf` inside your data-directory.

You can also see additional command-line options by running `./blurd --help`
