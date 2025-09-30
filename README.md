# ipv4calc - An IPv4 subnet calculator

IPv4calc is an IPv4 subnet calculator. It gives essential
information on the range/size of a subnet.

## CMake

`cmake` is your best option if you cannot use automake. It supports building on Linux,
MacOS and Windows (official support) but also has a good chance of working on other
platforms (no promises!). `cmake` has good support for cross-compiling.

## Automake
`automake` is a legacy option, it is well supported in most unix environments - however,
it is fairly slow & complicated.

## Building using CMake
    mkdir build
    cd build
    cmake ..
    make && make install

## Building using automake
    ./autogen.sh
    mkdir build
    cd build
    ../configure --prefix=/usr
    make && make install
