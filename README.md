<!--
  Copyright 2014, General Dynamics C4 Systems

  This software may be distributed and modified according to the terms of
  the GNU General Public License version 2. Note that NO WARRANTY is provided.
  See "LICENSE_GPLv2.txt" for details.

  @TAG(GD_GPL)
-->

The seL4 RISC-V specifics
===================

This repository is basically a fork from the master seL4 branch, containing 
the seL4/RISC-V port code. Hopefully when it reaches a mature stage, it would
be upstream with seL4. 

Updated Build Instructions:
------------------

Instructions based on the following blog post from Hesham Almatary: [`seL4 on RISC-V is running SOS (Simple Operating System)`][7]
  
### Instructions for installing the 2015 RISCV toolchain:

1. Get the source code
  ```
  mkdir riscv; cd riscv
  git clone https://github.com/riscv/riscv-gnu-toolchain
  cd riscv-gnu-toolchain
  git submodule update --init --recursive
  ```
2. Get the 2015 Submodules
  * cd into the following directories and perform git checkout <hash>:
    * riscv-binutils-gdb -> 5836a81
    * riscv-dejagnu -> dfeb344
    * riscv-gcc -> cce0626
    * riscv-glibc -> 1d4bbc5
    * riscv-newlib -> 9753bc3
3. Get 2015 Version of the Top-Level Repository
  * `git checkout dd2c7916`
4. Configure and Make the Toolchain
  ```
  ./configure --with-xlen=32 --prefix=/opt/riscv
  make
  ```
5. Export the RISCV toolchain to your path
  * Open your .bashrc file and add the following line: `export PATH=/opt/riscv/bin:$PATH`

The 2015 version of the toolchain should now be ready to use!

### Instructions for getting the RISCV Simulation Tools:

1. Clone into the repositories
  ```
  git clone https://github.com/riscv/riscv-isa-sim
  git clone https://github.com/riscv/riscv-fesvr
  ```
2. Install the Front-End Server
  ``` 
  export RISCV=/opt/riscv
  cd ~/riscv/riscv-fesvr
  git checkout ceb56f2
  ./configure --prefix=$RISCV
  make
  sudo make install
  ```
3. Installing Spike
  ```
  cd ~/riscv/riscv-isa-sim
  git checkout 092f378
  ./configure --prefix=$RISCV --with-fesvr=$RISCV
  make
  sudo make install
  ```
  
### Build for Rocket Chip
1. Get project:
  ```
  cd ~
  mkdir seL4riscv
  cd seL4riscv
  repo init -u https://github.com/dornerworks/sel4riscv-manifest
  repo sync
  ```
1. `make riscv_defconfig`
1. `make menuconfig`
  * Enable `seL4 Kernel  ---> seL4 System  ---> [*] ROCKET_CHIP`
1. `make`

### RISC-V Rocket Chip
1. Get specific prebuilt files for Rocket Chip on ZedBoard
  ```
  git clone https://github.com/ucb-bar/fpga-images-zedboard.git
  cd fpga-images-zedboard
  git checkout d242f27e1e2c93e843a29c06ba6725c8cecf06b7
  ```
1. Copy the following files to BOOT partition on SD Card:
  * `uramdisk.image.gz` -> `uramdisk.image.gz`
  * `boot.bin` -> `BOOT.bin`
  * `uImage` -> `uImage`
  * `devicetree.dtb` -> `devicetree.dtb`
1. Boot ZedBoard with SD boot mode.
1. Login with root/root
1. Run test application:
  * `./fesvr-zynq pk hello`
  * Should get output of `hello!`
1. Get an IP address on network: `udhcpc eth0`
1. On host, secure copy image to board: `scp images/sos-image-riscv-spike root@$BOARD_IP:~/`
1. Run seL4 image: `./fesvr-zynq sos-image-riscv-spike`


[7]: http://heshamelmatary.blogspot.co.uk/2015/06/sel4-on-risc-v-is-running-sos-simple.html


The seL4 Repository
===================

This repository contains the source code of seL4 microkernel.

For details about the seL4 microkernel, including details about its formal
correctness proof, please see the [`sel4.systems`][1] website and associated
[FAQ][2].

DOIs for citing recent releases of this repository:
  * [![DOI][4]](http://dx.doi.org/10.5281/zenodo.11247)

We welcome contributions to seL4. Please see the website for information
on [how to contribute][3].

This repository is usually not used in isolation, but as part of the build
system in a larger project.

  [1]: http://sel4.systems/
  [2]: http://sel4.systems/FAQ/
  [3]: http://sel4.systems/Contributing/
  [4]: https://zenodo.org/badge/doi/10.5281/zenodo.11247.png

Repository Overview
-------------------

  * `include` and `src`: C and ASM source code of seL4
  * `tools`: build tools
  * `haskell`: Haskell model of the seL4 kernel,
               kept in sync with the C version.
  * `libsel4`: C bindings for the seL4 ABI
  * `manual`: LaTeX sources of the seL4 reference manual


Build Instructions
------------------

tl;dr:

    TOOLPREFIX=arm-none-eabi- ARCH=arm PLAT=imx31 ARMV=armv6 CPU=arm1136jf-s \
 	make

The kernel source requires a cross-compiler for the target architecture. To
build using `make`, follow these instructions:

 * Ensure that the appropriate cross-compiler for your target
   architecture is installed.

 * Set the `TOOLPREFIX` environment variable to your cross-compiler's
   prefix. E.g. `arm-none-eabi-`.

 * Set the `ARCH`, `PLAT`, `ARMV` and `CPU` variables for the intended target
   architecture and platform, chosen from the following lists:

    ARCH | PLAT   | ARMV    | CPU
    -----|--------|---------|-----------
    arm  | imx31  | armv6   | arm1136jf-s
    arm  | omap3  | armv7-a | cortex-a8
    arm  | am335x | armv7-a | cortex-a8
    ia32 | pc99   |         |

 * For a debug build, append `DEBUG=y`.

See the seL4 website for more [comprehensive build instructions][5].

 [5]: http://sel4.systems/Download/


License
=======

The files in this repository are released under standard open source licenses.
Please see the individual file headers and `LICENSE_GPLv2.txt` and
`LICENSE_BSD2.txt` files for details.
