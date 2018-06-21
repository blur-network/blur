# BLUR

Copyright (c) 2018 Blur Network

Copyright (c) 2018 The NERVA Project 

Copyright (c) 2017-2018 The Masari Project.

Copyright (c) 2014-2018 The Monero Project.

Portions Copyright (c) 2012-2013 The Cryptonote developers.


## License

See [LICENSE](LICENSE).

## Setting Up Build Environment

<a href="https://gist.github.com/blur-network/ead3189d181a5f85b9688fcd569195a6"> Environment for Windows </a>

<a href="https://gist.github.com/blur-network/4e7692e9ab78737a9293917f19c36dab"> Environment for Linux (Deb/Ubuntu, Arch, Fedora) </a>

## To Compile the BLUR binaries:

Clone recursively to pull-in needed submodule(s):

$ git clone https://github.com/blur-network/blur.git

## Build instructions

Blur uses the CMake build system and a top-level [Makefile](Makefile) that
invokes cmake commands as needed.

### On Linux and OS X

*Install the dependencies*

**Change to the root of the source code directory and build:**

        cd blur
        make

    *Optional*: If your machine has several cores and enough memory, enable
    parallel build by running `make -j<number of threads>` instead of `make`. For
    this to be worthwhile, the machine should have one core and about 2GB of RAM
    available per thread.

    *Note*: If cmake can not find zmq.hpp file on OS X, installing `zmq.hpp` from
    https://github.com/zeromq/cppzmq to `/usr/local/include` should fix that error.

**The resulting executables can be found in:** `build/release/bin`

**Execute daemon with:** 
> ./blurd

**If you cannot synchronize with the network, kill your daemon and do the following before restarting:**

> touch ~/.blur-net/blurd.conf

The above command will create a file titled "blurd.conf" in your configuration folder (Linux)... append the following lines to that file: 

> seed-node=45.76.29.176:14894

> seed-node=144.202.62.30:14894

> seed-node=149.28.207.149:14894

This should fix the synchronizing issue if the daemon does not connect to the seed nodes automatically. 


To build static binaries: 

         make release-static

* **Optional**: build documentation in `doc/html` (omit `HAVE_DOT=YES` if `graphviz` is not installed):

        HAVE_DOT=YES doxygen Doxyfile



## Building portable statically linked binaries

By default, in either dynamically or statically linked builds, binaries target the specific host processor on which the build happens and are not portable to other processors. Portable binaries can be built using the following targets:

* ```make release-static-linux-x86_64``` builds binaries on Linux on x86_64 portable across POSIX systems on x86_64 processors
* ```make release-static-linux-i686``` builds binaries on Linux on x86_64 or i686 portable across POSIX systems on i686 processors
* ```make release-static-linux-armv8``` builds binaries on Linux portable across POSIX systems on armv8 processors
* ```make release-static-linux-armv7``` builds binaries on Linux portable across POSIX systems on armv7 processors
* ```make release-static-linux-armv6``` builds binaries on Linux portable across POSIX systems on armv6 processors
* ```make release-static-win64``` builds binaries on 64-bit Windows portable across 64-bit Windows systems
* ```make release-static-win32``` builds binaries on 64-bit or 32-bit Windows portable across 32-bit Windows systems

## Running blurd

The build places the binary in `bin/` sub-directory within the build directory
from which cmake was invoked (repository root by default). To run in
foreground:

    ./bin/blurd

To list all available options, run `./bin/blurd --help`.  Options can be
specified either on the command line or in a configuration file passed by the
`--config-file` argument.  To specify an option in the configuration file, add
a line with the syntax `argumentname=value`, where `argumentname` is the name
of the argument without the leading dashes, for example `log-level=1`.

To run in background:

    ./bin/blurd --log-file blurd.log --detach

To run as a systemd service, copy
[blurd.service](utils/systemd/blurd.service) to `/etc/systemd/system/` and
[blurd.conf](utils/conf/blurd.conf) to `/etc/`. The [example
service](utils/systemd/blurd.service) assumes that the user `blur` exists
and its home is the data directory specified in the [example
config](utils/conf/blurd.conf).

If you're on Mac, you may need to add the `--max-concurrency 1` option to
blur-wallet-cli, and possibly blurd, if you get crashes refreshing.
