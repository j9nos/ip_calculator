#include "reqfun.h"

std::string convertToDecimal(std::string binary)
{
    int result = 0;
    int j = 0;
    for (int i = binary.length() - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            result += pow(2, j);
        }
        j++;
    }
    return std::to_string(result);
};

std::string convertToBinary(int number)
{
    std::string temp = "";
    while (number > 0)
    {
        if (number % 2 == 0)
        {
            number /= 2;
            temp += "0";
        }
        else
        {
            number = (number - 1) / 2;
            temp += "1";
        }
    }
    while (temp.length() < 8)
    {
        temp += "0";
    }
    std::string result = "";
    for (int i = temp.length() - 1; i >= 0; i--)
    {
        result += temp[i];
    }
    return result;
};

std::string generate0(int quantity)
{
    std::string zeros;
    for (int i = 0; i < quantity; i++)
    {
        zeros += '0';
    }
    return zeros;
}

std::string generate1(int quantity)
{
    std::string ones;
    for (int i = 0; i < quantity; i++)
    {
        ones += '1';
    }
    return ones;
}
