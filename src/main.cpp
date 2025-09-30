/**
 * Copyright © 2025 Stefan Hallas Mulvad
 * IPv4 subnet calculator
 */

#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <getopt.h>

using namespace std;

namespace {
template <typename T>
string to_bits(T v)
{
    string s;
    T n(sizeof(T) * 8);
    while (n--) s.push_back((v & (1 << n)) ? '1' : '0');
    return s;
}

string to_ipv4(in_addr_t v)
{
    in_addr addr({v});
    return inet_ntoa(addr);
}

unsigned netmask2prefixSize(in_addr_t netmask)
{
    netmask = ntohl(netmask);
    unsigned len(0);
    while (netmask & 0x80000000) {
        ++len;
        netmask <<= 1;
    }
    if (netmask) return 33;
    return len;
}

in_addr_t prefixSize2netmask(unsigned prefixSize)
{
    int netmask(0x80000000);
    if (prefixSize == 0) return 0;
    return htonl(netmask >> (prefixSize - 1));
}

unsigned int getPrefixSize(string const& v)
{
    unsigned prefixSize(32);
    try {
        prefixSize = stoi(v);
    } catch (const invalid_argument&) {
        prefixSize = 33;
    }
    return prefixSize;
}

pair<string, unsigned> parseCidr(string const& v)
{
    string::size_type pos(v.find_last_of('/'));
    if (pos == string::npos) return make_pair(v, 32);
    return make_pair(v.substr(0, pos), getPrefixSize(v.substr(pos + 1)));
}

unsigned parseNetmask(string const& v)
{
    in_addr_t netmask(inet_addr(v.c_str()));
    return netmask2prefixSize(netmask);
}

pair<string, unsigned> parseArgs(int argc, char* argv[])
{
    if (argc == 2) return parseCidr(argv[1]);
    if (argc == 3) return make_pair(argv[1], parseNetmask(argv[2]));
    return make_pair("", 33);
}

string getNetworkClass(in_addr_t v)
{
    v = ntohl(v);
    if ((v >> 31) == 0) return "A";
    if ((v >> 30) == 2) return "B";
    if ((v >> 29) == 6) return "C";
    if ((v >> 28) == 14) return "D";
    if ((v >> 28) == 15) return "E";
    return "unknown";
}

string baseName(string const& path)
{
    string::size_type pos(path.find_last_of('/'));
    if (pos != string::npos) return path.substr(pos + 1);
    return path;
}

int usage(string const& appName, int ret = 0)
{
    cout << "Usage: " << endl;
    cout << "\t" << appName << " <ip address>[/prefix size]" << endl;
    cout << "\t" << appName << " <ip address> <netmask>" << endl;
    cout << "\tex: " << appName << " 8.8.4.4" << endl;
    cout << "\tex: " << appName << " 192.168.1.1/24" << endl;
    cout << "\tex: " << appName << " 172.16.54.24 255.255.252.0" << endl;
    return ret;
}
} // namespace

int main(int argc, char* argv[])
{
    const string appName(baseName(argv[0]));

    int opt = 0;
    int option_index = 0;
    static struct option long_options[] = {
            {"help", no_argument, 0, 'h'}, {"version", no_argument, 0, 'v'}, {0, 0, 0, 0}};
    while ((opt = getopt_long(argc, argv, "hv", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'h': return usage(appName, 0);
        case 'v': {
            std::cout << appName << ": version 1.0.0" << std::endl;
            return 0;
        }
        }
    }

    if (argc < 2 || argc > 3) return usage(appName, 1);

    const auto v(parseArgs(argc, argv));
    const string ipAddress(v.first);
    const unsigned prefixSize(v.second);
    const in_addr_t netmask(prefixSize2netmask(prefixSize));

    in_addr addr;
    if (inet_aton(ipAddress.c_str(), &addr) == 0) {
        cerr << "Error: invalid ip address" << endl;
        return usage(appName, 1);
    }

    if (prefixSize > 32) {
        cerr << "Error: invalid " << (argc == 2 ? "prefix size" : "netmask") << endl;
        return usage(appName, 1);
    }

    const in_addr_t netAddr(addr.s_addr & netmask), maxAddr(addr.s_addr | ~netmask);
    cout << "IP Class: " << getNetworkClass(addr.s_addr) << endl;
    cout << "IP Address: " << to_ipv4(addr.s_addr) << endl;
    cout << "Netmask: " << to_ipv4(netmask) << endl;
    cout << "Wildcard Mask: " << to_ipv4(~netmask) << endl;
    cout << "Binary Netmask: " << to_bits(ntohl(netmask)) << endl;
    cout << "Prefix Size: " << prefixSize << endl;
    cout << "CIDR Notation: " << to_ipv4(addr.s_addr) << "/" << prefixSize << endl;
    if (prefixSize < 31) {
        cout << "Network Address: " << to_ipv4(netAddr) << endl;
        cout << "Broadcast Address: " << to_ipv4(maxAddr) << endl;
    }
    if (prefixSize < 32) {
        const unsigned long long nAddresses(1ull << (32 - prefixSize));
        const in_addr_t nOffset(prefixSize < 31 ? 1 : 0);

        cout << "Usable Host Range: " << to_ipv4(netAddr + htonl(nOffset)) << " -> "
             << to_ipv4(maxAddr - htonl(nOffset)) << endl;
        cout << "Total number of host(s): " << nAddresses << endl;
        cout << "Number of usable hosts: " << nAddresses - (2 * nOffset) << endl;
    }

    return 0;
}
