#pragma once

#include <string>

namespace pc
{
    struct CPU
    {
        std::string name;
        int cores;
        int quality;
        double price;
    };

    struct GPU
    {
        std::string name;
        int quality;
        int memory;
        double price;
    };

    struct HDD
    {
        std::string name;
        int quality;
        int memory;
        double price;
    };

    struct RAM
    {
        std::string name;
        int quality;
        int memory;
        double price;
    };

    struct SSD
    {
        std::string name;
        int quality;
        int memory;
        double price;
    };
}
