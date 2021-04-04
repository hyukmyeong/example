## install basic tools

### lcov 1.15 + branch-filter
```bash
$ sudo apt autoremove lcov
$ sudo apt install libjson-perl libdatetime-perl libdatetime-format-w3cdtf-perl
$ git clone https://github.com/linux-test-project/lcov.git -b v1.15
$ cd lcov
$ git fetch origin pull/86/head:branch-filter
$ git checkout branch-filter
$ sudo make install
$ cp /usr/local/etc/lcovrc ~/.lcovrc
$ vi ~/.lcovrc
genhtml_legend = 1
geninfo_no_exception_branch = 1
lcov_branch_coverage = 1
```

## setup environment x86-64

### install googletest for x86-64
```bash
$ cd ~ && git clone -b 'release-1.10.0' https://github.com/google/googletest.git
$ cd googletest && cmake -Bbuild && cd build && make
$ sudo make install
```

### build and run
```bash
$ cd ~ && git clone https://github.com/hyukmyeong/example.git
$ cd ~/example && cmake -Bbuild && cd build && make
$ ./product
```

### run test
```bash
$ make test
$ make coverage && google-chrome test/coverage/index.html
```

## setup environment aarch64

### install aarch64 toolchain
```bash
$ sudo apt install binutils-aarch64-linux-gnu
$ sudo apt install gcc-9-aarch64-linux-gnu
$ sudo apt install g++-9-aarch64-linux-gnu
$ sudo apt install qemu-user
$ sudo bash -c 'for f in /usr/bin/aarch64-linux-gnu-*-9; do ln -s "$f" "$(echo "$f" | sed s/-9//)"; done'
```

### install googletest for aarch64
```bash
$ cd ~ && git clone https://github.com/hyukmyeong/example.git
$ cd ~/example && git clone -b 'release-1.10.0' https://github.com/google/googletest.git
$ cd googletest && mkdir build && cd build
$ cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=aarch64-linux-gnu-gcc.cmake -DCMAKE_INSTALL_PREFIX=/usr/aarch64-linux-gnu
$ make && sudo make install
$ cd ~/example && rm -rf googletest
```

### build and run
```bash
$ cd ~/example && mkdir build && cd build
$ cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=aarch64-linux-gnu-gcc.cmake
$ make
$ qemu-aarch64 -L /usr/aarch64-linux-gnu ./product
```

### run test
```bash
$ make test
$ make coverage && google-chrome test/coverage/index.html
```

## other issues

### if lcov spacing is not looking good in chrome
open google-chrome -> settings -> fonts -> customize -> fixed-width font -> Monospace, etc.
