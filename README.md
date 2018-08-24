# BLUR Network 

Copyright (c) 2018 The Blur Network</br>
Copyright (c) 2018 The NERVA Project</br>
Copyright (c) 2017-2018 The Masari Project.</br>
Copyright (c) 2014-2018, The Monero Project</br>

*See [LICENSE](LICENSE).*<br>

### Donate to help support Blur:
**BTC:** 1CeFbUtrqDzp7nvnXotuuARwHPxAXCLb4u <br>
**LTC:** LM2tBw25UMfdjAJbo52tzh5r3R47a1aMeM <br>
**XMR:** 46MT7yy9mF3Bvk61XmRzirB4wdSkPqNRJ3pwUcRYxj3WWCGLMHD9sE5bNtChnYQiPYiCYDPyXyJGKFG3uT2CbeKWCwnvWLv <br>
**BLUR:** bL4PdWFk3VVgEGYezGTXigHrsoJ3JGKgxKDi1gHXT7GKTLawFu3WMhu53Gc2KCmxxmCHbR4VEYMQ93PRv8vWgJ8j2mMHVEzLu <br>

Currency:   | <center> Blur (Ticker: BLUR) </center>
|:-------|:---------:|
**Website:** | <center> https://blur.cash </center>
**Block Explorer:** | <center>http://explorer.blur.cash/</center>
**Block Explorer API Example:** | <center>http://explorer.blur.cash/api/transactions</center>
**Offline Wallet Generator:** | <center> <a href="https://blur.cash/wp-content/uploads/2018/06/offline-wallet.html"> Offline HTML Page </a> <center>
**Discord (Main Point of Contact for Blur):** | <center><a href="https://discord.gg/VFP2VES"> Blur Official Discord </a> </center>
**Telegram:** | <center> <a href="https://t.me/theblurnetwork"> Telegram </a> </center>
**BitcoinTalk Announcement:** | <center><a href="https://bitcointalk.org/index.php?topic=4577361"> Official Thread on BitcoinTalk.org </center>
**Reddit:** | <center><a href="https://reddit.com/r/blur_network">Subreddit for Blur Network</a></center>
**Binary Release(s):** |<center> <a href="https://github.com/blur-network/blur/releases"> Download via Github </a> </center>
**Algorithm:** | <center> Cryptonight-Adaptive (CPU-only) Experimental from NERVA </center>
**Ports:** | <li>P2P: 14894</li> <li>RPC: 14895</li>
**Seed Nodes:** | <li>Node 1: 178.128.191.245:14894</li> <li> Node 2: 178.128.180.136:14894 </li> <li> Node 3: 178.128.186.101:14894 </li> <li>Node 4: 178.128.183.55:14894 </li>



BLUR takes a decentralized-by-design approach to mining.  The algorithm used to mine BLUR is incompatible with pooled mining (with current software) and is resistant to ASIC/GPU mining rigs.  Because the algorithm dynamically changes with each block, GPUs and ASICs need reset after each block is mined on the network.  This makes it far too resource-intensive for BLUR to be an attractive option for GPU/ASIC setups.  The BLUR network is comprised of individuals mining on individual computers.

## Build From Source (Linux)

Clone this repository and install dependencies.  Copy and paste the following: 

`git clone https://github.com/blur-network/blur.git`

# Install Dependencies

Required:

`sudo apt update && sudo apt-get install -y build-essential cmake pkg-config libboost-all-dev libssl-dev libpcsclite-dev libzmq3-dev libpgm-dev libnorm-dev libunbound-dev libsodium-dev`

Optional: 

`sudo apt-get install libminiupnpc-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev libgtest-dev doxygen graphviz`

# Build Binaries

Open a terminal, and cd to the directory where you cloned the repository.  Assuming that is your home folder, enter the following command:

`cd ~/blur && make release-all` 

(Or for statically linked binaries: `make release-static`)


## Mining BLUR (Linux)

Build from source, or download the <a href="https://github.com/blur-network/blur/releases">latest Blur Network release</a>.  Navigate to the blur directory, and start the daemon:

`cd blur-v0.1.7-linux-x86_64 && ./blurd --seed-node 178.128.191.245:14894 --seed-node 178.128.186.101:14894 --seed-node 178.128.180.136:14894`

Wait for sync to complete.  Leave that terminal window open, and the daemon running.

Next, open a new tab (Ctrl+Shift+T) or window, and then start the wallet:

`./blur-wallet-cli`

Follow the prompts to setup a new wallet.  
*When prompted for the password, the CLI will not show a password as you type.*  It is still recording your keystrokes. 

**Record the information for your wallet.**

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. 

You should see the message: *`Mining started in daemon`*

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring. 
For further commands in either the wallet or the daemon, type `help` into the CLI.  Note that the commands for the daemon and wallet are different. 

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 


## Mining on Windows

<a href="https://gist.github.com/blur-network/ead3189d181a5f85b9688fcd569195a6"> Compile from source for Windows</a> or download (recommended) the <a href="https://github.com/blur-network/blur/releases">latest release</a>.

Open your Downloads Library in your File Explorer.  Extract the executables from the compressed archive, and navigate to the folder that you just extracted. 

Start the daemon by double-clicking the `blurd.exe` file  **OR to sync faster, open a Powershell, then copy and paste the following:**

`cd Downloads/blur-v0.1.7-win-x86_64 && blurd.exe --seed-node 178.128.191.245:14894 --seed-node 178.128.186.101:14894 --seed-node 178.128.180.136:14894`

You will see a pop-up from your firewall.  Be sure to check the box next to "Private Networks" if you are on a private network, or your daemon will not be able to sync with the network. 
If you daemon stalls while syncing, close and restart the program.  You will not lose any blocks you have already synced with. 

Once your daemon is syncchronized with the network...

Start the wallet by double-clicking the `blur-wallet-cli` file.

Follow the prompts to setup a new wallet.  When prompted for the password, the CLI will not show a password as you type.  It is still recording your keystrokes. 

Once the wallet is open, type into the wallet CLI: `start_mining [# of threads]` where [# of threads] is the amount of cpu threads you wish to dedicate to mining BLUR. . 

You should see the message: `Mining started in daemon`

Switch back to the terminal or tab in which your daemon is running, and type `show_hr` for real-time  hashrate monitoring.  For further commands in either the wallet or the daemon, type `help` into either CLI.  Note that the commands for the daemon and wallet are different.

Whenever you find a block, your daemon will show a bold message with the block # found.  There is a slight delay between that message and the balance reflecting in your wallet. 



## How to Fix Synchronizing Issues

If you cannot synchronize with the network, kill your daemon & restart with the following options:

`--seed-node 178.128.191.245:14894 --seed-node 178.128.186.101:14894 --seed-node 178.128.180.136:14894 --p2p-bind-port 14894 --rpc-bind-port 14895`

This should fix issue if the daemon does not bind to the correct ports, or seed nodes. 


