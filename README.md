# The Blur Network 

Copyright (c) 2018 The Blur Network.

Copyright (c) 2018 The NERVA Project.

Copyright (c) 2017-2018 The Masari Project.

Copyright (c) 2014-2018 The Monero Project.

Portions Copyright (c) 2012-2013 The Cryptonote developers.


## About BLUR & The Blur Network

Blur (BLUR) is a privacy-focused cryptocurrency that uses Monero's ringCT structures and the cryptonote protocol to make transactions untraceable.  Monero's network has become dominated by botnets, mining rigs, and ASIC miners, compromising the integrity of the network as a whole due to centralized mining.  The Blur Network features a new algorithm for mining, called Cryptonight-Adaptive, that can only be CPU-mined.  This algorithm was taken from the NERVA project, and is designed to be too resource-intensive for GPU rigs and ASIC miners. 

### Metrics

| Cryptocurrency Name: | Blur (Ticker: BLUR)|
|:--------------------|--------------------:|
| Total Supply:	      | 9,223,300 BLUR <br> until tail emission |
| Decimal Places:     | 12 		    |
| Emission Speed:     | 21 (1583 days until fixed rewards) |
| Mining Algorithm    | Cryptonight-Adaptive (CPU-only) |




## Configuring the build environment on Linux

These dependencies are all you need for the CLI tools and GUI wallet. Once you have these installed, you have a complete BLUR build environment.

- BLUR dependencies (Ubuntu 16.04/17.10)

    `sudo apt install -y build-essential cmake pkg-config libboost1.62-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libminiupnpc-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev libgtest-dev doxygen graphviz`

- Wallet dependencies (Ubuntu 16.04)

    *Ubuntu 16.04 contains an older, incompatible version of Qt. You must update by either downloading an official package or installing from PPA. The following PPA of Qt 5.7.1 has been tested*
	
	`sudo add-apt-repository ppa:beineri/opt-qt571-xenial`  
	`sudo apt update`  
	`sudo apt install qt57-meta-full`
    
- Wallet dependencies (Ubuntu 17.10)

    `sudo apt -y install qtbase5-dev qt5-default qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-xmllistmodel qttools5-dev-tools qml-module-qtquick-dialogs qml-module-qt-labs-settings qml-module-qt-labs-folderlistmodel qml-module-qtquick-controls2`
	
You are now ready to compile BLUR on Linux. 


## Configuring the Build Environment -- Windows

The BLUR wallet on Windows is 64 bits only; 32-bit Windows wallet builds are not officially supported.

- Install [MSYS2](https://www.msys2.org/), follow the instructions on that page on how to update system and packages to the latest versions

- Install the [MS Build Tools](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017). On that page select 'Other Tools and Frameworks -> Build Tools for Visual Studio 2017'  
During installation, select the C++ build tools and Windows SDK 8.1

- Find and open the file msys2_shell.cmd in Notepad++ or some other text editor that can handle unix line endings.
The default location is C:/msys2/msys2_shell.cmd

- Find the line that reads 'rem set MSYS2_PATH_TYPE=inherit' and uncomment it by removing the 'rem' from the start of the line.

- Open an 64-bit MSYS2 shell: Use the *MSYS2 MinGW 64-bit* shortcut

- Update MSYS2

	`pacman -Syu`

- Close MSYS2 and reopen then update again

	`pacman -Su`

- Install MSYS2 packages for BLUR dependencies
	
	`pacman -S mingw-w64-x86_64-toolchain make`  
	`pacman -Sy mingw64/mingw-w64-x86_64-cmake mingw64/mingw-w64-x86_64-boost mingw32/mingw-w64-i686-boost \`  
	`mingw64/mingw-w64-x86_64-openssl mingw64/mingw-w64-x86_64-zeromq mingw64/mingw-w64-x86_64-libsodium`

- Install Qt5

    `pacman -S mingw-w64-i686-qt5 mingw-w64-x86_64-qt5`

- Install git

    `pacman -S git`  
    
You are now ready to compile BLUR on Windows.



## Building BLUR Binaries from source

### Linux 

Copy and paste the following into a terminal:

> git clone https://github.com/blur-network/blur.git

> cd blur && mkdir build && cd build 

> cmake ..

> make -j 2

Your binaries can then be found within ~/blur/build/bin



