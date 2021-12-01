#include "reqfun.h"

class IP
{
    std::string address;
    int mask;

    std::string binarizedAddress_;

    std::string netmask_;
    std::string wildcard_;
    std::string network_;
    std::string broadcast_;
    std::string first_;
    std::string last_;
    int hosts_;

public:
    void setAddress(std::string addr)
    {
        address = addr;
    }
    void setMask(int msk)
    {
        mask = msk;
    }
    void calculate()
    {
        binarizeAddress();
        calculateNetmask();
        calculateWildcard();
        calculateNetwork();
        calculateBroadcast();
        calculateFirst();
        calculateLast();
        calculateHosts();
    }

private:
    void binarizeAddress()
    {
        std::string *temp;
        temp = new std::string[4];
        int j = 0;
        for (int i = 0; i < address.length(); i++)
        {
            if (address[i] == '.')
            {
                j++;
            }
            else
            {
                *(temp + j) += address[i];
            }
        }
        std::string *result;
        result = new std::string("");
        for (int i = 0; i < 4; i++)
        {
            *result += convertToBinary(stoi(temp[i]));
        }
        binarizedAddress_ = *result;
        delete[] temp;
        delete result;
    }

    void calculateNetmask()
    {
        netmask_ = binarizedAddress_;
        netmask_.replace(0, mask, generate1(mask)).replace(mask, 32, generate0(32 - mask));
        std::cout
            << convertToDecimal(netmask_.substr(0, 8)) << "."
            << convertToDecimal(netmask_.substr(8, 8)) << "."
            << convertToDecimal(netmask_.substr(16, 8)) << "."
            << convertToDecimal(netmask_.substr(24, 8)) << "\t<--- netmask \n";
    }
    void calculateWildcard()
    {
        wildcard_ = binarizedAddress_;
        wildcard_.replace(0, mask, generate0(mask)).replace(mask, 32, generate1(32 - mask));
        std::cout
            << convertToDecimal(wildcard_.substr(0, 8)) << "."
            << convertToDecimal(wildcard_.substr(8, 8)) << "."
            << convertToDecimal(wildcard_.substr(16, 8)) << "."
            << convertToDecimal(wildcard_.substr(24, 8)) << "\t<--- wildcard \n";
    }
    void calculateNetwork()
    {
        network_ = binarizedAddress_;
        network_.replace(mask, 32, generate0(31 - mask));
        std::cout
            << convertToDecimal(network_.substr(0, 8)) << "."
            << convertToDecimal(network_.substr(8, 8)) << "."
            << convertToDecimal(network_.substr(16, 8)) << "."
            << convertToDecimal(network_.substr(24, 8)) << "\t<--- network \n";
    }
    void calculateBroadcast()
    {
        broadcast_ = binarizedAddress_;
        broadcast_.replace(mask, 32, generate1(32 - mask));
        std::cout
            << convertToDecimal(broadcast_.substr(0, 8)) << "."
            << convertToDecimal(broadcast_.substr(8, 8)) << "."
            << convertToDecimal(broadcast_.substr(16, 8)) << "."
            << convertToDecimal(broadcast_.substr(24, 8)) << "\t<--- broadcast \n";
    }
    void calculateFirst()
    {
        first_ = binarizedAddress_;
        first_.replace(mask, 32, generate0(32 - mask)).replace(31, 32, "1");
        std::cout
            << convertToDecimal(first_.substr(0, 8)) << "."
            << convertToDecimal(first_.substr(8, 8)) << "."
            << convertToDecimal(first_.substr(16, 8)) << "."
            << convertToDecimal(first_.substr(24, 8)) << "\t<--- first \n";
    }
    void calculateLast()
    {
        last_ = binarizedAddress_;
        last_.replace(mask, 32, generate1(32 - mask)).replace(31, 32, "0");
        std::cout
            << convertToDecimal(last_.substr(0, 8)) << "."
            << convertToDecimal(last_.substr(8, 8)) << "."
            << convertToDecimal(last_.substr(16, 8)) << "."
            << convertToDecimal(last_.substr(24, 8)) << "\t<--- last \n";
    }
    void calculateHosts()
    {
        hosts_ = abs(pow(2, 32 - mask) - 2);
        std::cout << hosts_ << "\t<--- hosts \n";
    }
};

int main(int argc, char *args[])
{
    IP *ip;
    ip = new IP();
    ip->setAddress("192.168.1.4");
    ip->setMask(24);
    ip->calculate();
    delete ip;
    return 0;
};