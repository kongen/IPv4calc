# ipv4calc - An IPv4 subnet calculator

IPv4calc is an IPv4 subnet calculator. It gives essential
information on the range/size of a subnet.

## Usage
    ipv4calc <ip address>[/prefix size]
    ipv4calc <ip address> <netmask>
    ex: ipv4calc 8.8.4.4
    ex: ipv4calc 192.168.1.1/24
    ex: ipv4calc 172.16.54.24 255.255.252.0

## Example
    > ./ipv4calc 192.168.1.1/24
    IP Class: C
    IP Address: 192.168.1.1
    Netmask: 255.255.255.0
    Wildcard Mask: 0.0.0.255
    Binary Netmask: 11111111111111111111111100000000
    Prefix Size: 24
    CIDR Notation: 192.168.1.1/24
    Network Address: 192.168.1.0
    Broadcast Address: 192.168.1.255
    Usable Host Range: 192.168.1.1 -> 192.168.1.254
    Total number of host(s): 256
    Number of usable hosts: 254

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
    make && sudo make install

## Building using automake
    ./autogen.sh
    mkdir build
    cd build
    ../configure --prefix=/usr
    make && sudo make install
