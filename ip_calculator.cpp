#include <bits/stdc++.h>

class IP
{
private:
    std::string address;
    int mask;

    bool can_proceed = 0;

    std::string binarized_address = "";

    bool is_address_valid(std::string arg_address)
    {
        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        if (std::regex_match(arg_address, ipv4))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool is_mask_valid(int arg_mask)
    {
        return (1 <= arg_mask && 32 >= arg_mask);
    }

    void refine_address()
    {
        int splitted_address[4];
        std::sscanf(address.c_str(), "%d.%d.%d.%d", &splitted_address[0], &splitted_address[1], &splitted_address[2], &splitted_address[3]);
        for (int i = 0; i < 4; i++)
        {
            std::bitset<8> bs(splitted_address[i]);
            binarized_address += bs.to_string();
        }
    }
    void calc_netmask()
    {
        std::string netmask = binarized_address;
        netmask.replace(0, mask, std::string(mask, '1')).replace(mask, 32, std::string(32 - mask, '0'));
        std::cout
            << std::bitset<8>(netmask.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(netmask.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(netmask.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(netmask.substr(24, 8)).to_ulong() << "\t (netmask)"
            << std::endl;
    }
    void calc_wildcard()
    {
        std::string wildcard = binarized_address;
        wildcard.replace(0, mask, std::string(mask, '0')).replace(mask, 32, std::string(32 - mask, '1'));
        std::cout
            << std::bitset<8>(wildcard.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(wildcard.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(wildcard.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(wildcard.substr(24, 8)).to_ulong() << "\t (wildcard)"
            << std::endl;
    }
    void calc_network()
    {
        std::string network = binarized_address;
        network.replace(mask, 32, std::string(31 - mask, '0'));
        std::cout
            << std::bitset<8>(network.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(network.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(network.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(network.substr(24, 8)).to_ulong() << "\t (network)"
            << std::endl;
    }
    void calc_broadcast()
    {
        std::string broadcast = binarized_address;
        broadcast.replace(mask, 32, std::string(32 - mask, '1'));
        std::cout
            << std::bitset<8>(broadcast.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(broadcast.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(broadcast.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(broadcast.substr(24, 8)).to_ulong() << "\t (broadcast)"
            << std::endl;
    }
    void calc_first()
    {
        std::string first = binarized_address;
        first.replace(mask, 32, std::string(32 - mask, '0')).replace(31, 32, "1");
        std::cout
            << std::bitset<8>(first.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(first.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(first.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(first.substr(24, 8)).to_ulong() << "\t (first)"
            << std::endl;
    }
    void calc_last()
    {
        std::string last = binarized_address;
        last.replace(mask, 32, std::string(32 - mask, '1')).replace(31, 32, "0");
        std::cout
            << std::bitset<8>(last.substr(0, 8)).to_ulong() << "."
            << std::bitset<8>(last.substr(8, 8)).to_ulong() << "."
            << std::bitset<8>(last.substr(16, 8)).to_ulong() << "."
            << std::bitset<8>(last.substr(24, 8)).to_ulong() << "\t (last)"
            << std::endl;
    }
    void calc_hosts()
    {
        std::cout << abs(pow(2, 32 - mask) - 2) << "\t\t (hosts)" << std::endl;
    }

public:
    void set_ip(std::string arg_address, int arg_mask)
    {
        try
        {
            is_address_valid(arg_address) ? address = arg_address : throw(1);
            is_mask_valid(arg_mask) ? mask = arg_mask : throw(2);
            can_proceed = 1;
        }
        catch (int err_code)
        {
            switch (err_code)
            {
            case 1:
                std::cout << "The address you entered doesn't seem like an ipv4 address" << std::endl;
                break;
            case 2:
                std::cout << "The mask should be in range within 1 and 32" << std::endl;
                break;
            }
        }
    }
    void calculate()
    {
        if (can_proceed)
        {
            refine_address();
            calc_netmask();
            calc_wildcard();
            calc_network();
            calc_broadcast();
            calc_first();
            calc_last();
            calc_hosts();
        }
    }
};
auto main(int argc, char *argv[]) -> decltype(0)
{
    IP ip;
    ip.set_ip("192.168.1.4", 24);
    ip.calculate();
    return 0;
};