![Blur: The Private Cryptocurrency](https://i.imgur.com/PG8B6Ca.jpg)
# Blur Network 
Copyright (c) 2018-2019, Blur Network</br>

*See [LICENSE](License).*<br>
*See [Code of Conduct](CODE_OF_CONDUCT.md)*<br>

# About the Project

The Blur Network is an experimental project based upon the premise that privacy and centralization cannot coexist.  We focus on maximizing accessibility to block rewards, while fostering an educational environment. We seek to create an ecosystem where individuals can take a first-hand role in protecting their right to privacy.

The Blur Network employs a custom algorithm for mining, called CryptoNight-Dynamic.  The algorithm adjusts approximately once every five seconds, with a goal of maintaining CPU advantages over specialized mining hardware.  Making use of a Unix timestamp, the current block height, and the previous block’s hash,  CryptoNight-Dynamic varies iterations in the CryptoNight algorithm. Employing a timestamp in the calculation serves the purpose of dynamic iterations on an intra-block basis, while height and the previous block’s hash create variation on an inter-block basis.  The iterations necessary to mine each next block are directly dependent upon the result of the block before it. 

## Contents:
- <a href="https://github.com/blur-network/blur#compile-source">Compiling from Source</a> </br>
   - <a href="https://github.com/blur-network/blur#packages">Dependency Packages & Dynamic Linking</a> </br>
   - <a href="https://github.com/blur-network/blur#build-deps">Dependencies from Source & Static Linking</a> </br>
   - <a href="https://github.com/blur-network/blur#building">Building with packages on Host OS</a> </br>
- <a href="https://github.com/blur-network/blur#mining-windows">Mining on Linux/Mac</a> </br>
- <a href="https://github.com/blur-network/blur#mining-windows">Mining on Windows</a></br>
- <a href="https://github.com/blur-network/blur#sync-issues">Fixing Synchronization Issues</a> </br></br>

Currency:   | <center> Blur (Ticker: BLUR) </center>
|:-------|:---------:|
**Website:** | <center> https://blur.cash </center>
**Block Explorer:** | <center>http://explorer.blur.cash/</center>
**Block Explorer API Example:** | <center>http://explorer.blur.cash/api/transactions</center>
**Offline Wallet Generator:** | <center><a href="https://blur.cash/wp-content/uploads/2018/06/offline-wallet.html"> Offline HTML Page</a><center>
**Discord (Main Point of Contact for Blur):** | <center><a href="https://discord.gg/VFP2VES"> Blur Official Discord</a> </center>
**Telegram:** | <center> <a href="https://t.me/theblurnetwork"> Telegram </a> </center>
**BitcoinTalk Announcement:** | <center><a href="https://bitcointalk.org/index.php?topic=4577361"> Official Thread on BitcoinTalk.org </center>
**Reddit:** | <center> <a href="https://reddit.com/r/blur_network">Official Blur Network Subreddit</a></center>
**CLI Binary Release(s):** | <center> <a href="https://github.com/blur-network/blur/releases"> Download via Github </a> </center>
**GUI Wallet Release(s):** | <center><a href="https://github.com/blur-network/blur-network-gui/releases"> Download via Github</a></center>
**Algorithm:** | <center> Cryptonight-Dynamic v2</center>
   **Ports:** | <center> P2P port = 52541 </br>RPC port = 52542</br></center>
  **Seed Nodes:** | <center><li>Node 1: 45.33.92.232:52541</li><li>Node 2: 45.79.85.65:52541</li><li>Node 3: 212.71.234.44:52541</li>
  </center>

### Donate to help support Blur:
**BTC:** 13u7qiXLRvLq1sBVgSQRykWYCTeAXmMWEn <br>
**LTC:** LM2tBw25UMfdjAJbo52tzh5r3R47a1aMeM <br>
**XMR:** 46MT7yy9mF3Bvk61XmRzirB4wdSkPqNRJ3pwUcRYxj3WWCGLMHD9sE5bNtChnYQiPYiCYDPyXyJGKFG3uT2CbeKWCwnvWLv <br>
**BLUR:** bL4PdWFk3VVgEGYezGTXigHrsoJ3JGKgxKDi1gHXT7GKTLawFu3WMhu53Gc2KCmxxmCHbR4VEYMQ93PRv8vWgJ8j2mMHVEzLu <br>

Old Donation address:  <del>19onVUREbP89qu4dYBfVqtGisWaoyWs3BX</del>


<h1 id="compile-source">Compiling from Source</h1>

**Blur uses the CMake build system and a top-level [Makefile](Makefile) that invokes cmake commands as needed.**



<h3>Step 1: Clone this repository's stable branch:</h3>

>`git clone --recursive https://github.com/blur-network/blur.git`



<h3 id="packages">Step 2a: Install dependencies (If you wish to link the binaries dynamically)</h3>


**If you wish to instead compile statically, scroll to step 2(b)**


Ubuntu/Debian:

Required:  `sudo apt-get install -y build-essential cmake pkg-config libboost-all-dev libssl-dev libunbound-dev libsodium-dev`

Optional:  `sudo apt-get install -y libunwind-dev liblzma-dev libreadline-dev libldns-dev libexpat1-dev libgtest-dev`


**Arch Linux:**

Required:  `sudo pacman -S base-devel cmake boost openssl unbound libsodium `

Optional:  `sudo pacman -S libunwind xz readline ldns expat gtest`



<h3 id="build-deps">Step 2(b): Build dependencies, and link statically, all in one go</h3>

To compile for Linux (distro-agnostic): `make release-cross-linux-x86_64`

To compile for Windows(mingw64): `make release-cross-winx64`

The `Makefile` entries run by the above commands will build dependencies for `x86_64-gnu-linux` and `x86_64-w64-mingw32` hosts, respectively. If you would like to compile for a different type of host platform, `cd` into the `contrib/depends` directory, and build with `make HOST=xxx-yyy-zzz` where xxx-yyy-zzz is a <a href="https://wiki.osdev.org/Target_Triplet">standard host triplet</a>.



<h3 id="building">Step 3: For dynamic linking, or MacOS</h3>

>`cd ~/blur && make release-all`

*There are multiple platforms and configurations for which you can compile.  A non-exhaustive list can be found below:*

For statically linked binaries (defaults to the platform configuration of the host compiler):

>`make release-static`

For Windows portable binaries (Cross-Compiled on Linux <a href="https://github.com/blur-network/blur/tree/v0.1.9.5/contrib/depends">using contrib/depends system from Bitcoin</a>):

Follow the link above to setup build environment, then issue the command below

>`make release-static-win64`

For MacOS portable binaries:

>`make release-static-mac-x86_64`

*Note that we do not officially support builds for 32-bit architecture, arm architecture, or the freebsd linux distribution currently. However, there are options within the [Makefile](Makefile) for these configurations.  These entries may require significant modifications to source files, in order to work properly.*



<h1 id="mining-linux">Mining on Linux</h1>


Compile from source, or download the <a href="https://github.com/blur-network/blur/releases"> latest binary release from the Releases page</a>.  

We also now offer a Snap package on the Ubuntu Snap Store: <a href="https://snapcraft.io/blur"><img alt="Get it from the Snap Store" src="https://snapcraft.io/static/images/badges/en/snap-store-black.svg" /></a>

Open a terminal in the directory within which the binaries were downloaded.  Assuming that is your Downloads folder, enter the following command:


>`cd ~/Downloads && tar xvzf blur-v0.1.9.5-linux-x86_64.tar.xz`


Navigate into the directory you just unzipped from the archive, and start the daemon.


>`cd blur-v0.1.9.5-linux_x86_64 && ./blurd`


Wait for sync to complete, open a new tab or terminal window, and then start the wallet:


>`./blur-wallet-cli`


Follow the prompts to setup a new wallet.  When prompted for the password, the CLI will not show a password as you type.  It is recording your keystrokes, however.

Record the information for your wallet.

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. 

You should see the message: `Mining started in daemon`

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring.  For further commands in either the wallet or the daemon, type `help` into either CLI.  Note that the commands for the daemon and wallet are different.

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 

**You can also start mining, without opening a wallet, by launching the daemon with:** `./blurd --start-mining <address> --mining-threads <num. threads>` (omit the brackets)


<h1 id="mining-windows"> Mining on Windows </h1>


Download the <a href="https://github.com/blur-network/blur/releases">latest release from our Releases page</a>.

Open your Downloads Library in your File Explorer.  Extract the executables from the compressed archive, and navigate to the folder that you just extracted. 

Start the daemon by double-clicking the `blurd.exe` file. 

You will see a pop-up from your firewall.  Be sure to check the box next to "Private Networks" if you are on a private network, or your daemon will not be able to sync with the network. If you daemon stalls while syncing, close and restart the program.  You will not lose any blocks you have already synced with. Once your daemon is synced with the network...

Start the wallet by double-clicking the `blur-wallet-cli` file.

Follow the prompts to setup a new wallet.  When prompted for the password, the CLI will not show a password as you type.  It is recording your keystrokes, however.

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. . 

You should see the message: `Mining started in daemon`

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring.  For further commands in either the wallet or the daemon, type `help` into either CLI.  Note that the commands for the daemon and wallet are different.

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 

**You can also start mining, without opening a wallet, by launching the daemon with:** `blurd.exe --start-mining <address> --mining-threads <num. threads>` (omit the brackets)



<h1 id="sync-issues">How to Fix Synchronizing Issues</h1>


If you cannot synchronize with the network, kill your daemon & restart with the following options:

Linux: `cd` to the directory you downloaded the files into, and type:
`./blurd --add-priority-node=45.33.92.232:52541 --add-priority-node=212.71.234.44:52541 --add-priority-node=45.79.85.65:52541 --p2p-bind-port 52541 --rpc-bind-port 52542 --rpc-bind-ip 127.0.0.1`

Windows:  Open cmd.exe, `cd` to the directory you downloaded the files into, and type:
`blurd.exe --add-priority-node=45.33.92.232:52541 --add-priority-node=212.71.234.44:52541 --add-priority-node=45.79.85.65:52541 --p2p-bind-port=52541 --rpc-bind-port=52542 --rpc-bind-ip=127.0.0.1`

This should fix the synchronizing issue if the daemon does not connect to the seed nodes automatically. 

You can also see additional command-line options by running the daemon with the option `--help`.  The program will return a list of startup flags and their descriptions. 
