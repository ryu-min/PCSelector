#include "componentsmodel.hpp"

#include <fstream>
#include <iostream>


using json = nlohmann::json;

inline char dirSep()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

pc::ComponentsModel::ComponentsModel(const std::string &componentsDir)
    : m_componentsDir(componentsDir)
    , m_cpuComponents()
    , m_gpuComponents()
{
    parseCPUComponents();
    parseGPUComponents();
    parseHDDComponents();
    parseRAMComponents();
    parseSSDComponents();
}

void pc::ComponentsModel::parseCPUComponents()
{
    std::string cpuFilePath = m_componentsDir + dirSep() + "cpu.json";
    std::ifstream f(cpuFilePath);
    if ( !f.is_open() ) return;
    json j = json::parse(f);
    if ( j.is_null() ) return;
    m_cpuComponents.reserve(j.size());
    for ( int i = 0; i < j.size(); i++ )
    {
        CPU cpu;
        json cpuJson = j[i];
        if ( !validateCPUJson(cpuJson) ) continue;
        cpu.name = cpuJson["name"].get<std::string>();
        cpu.quality = cpuJson["quality"].get<int>();
        cpu.cores = cpuJson["cores"].get<int>();
        cpu.price = cpuJson["price"].get<double>();
        m_cpuComponents.push_back( cpu );
    }
}

bool pc::ComponentsModel::validateCPUJson(const nlohmann::json &json)
{
    return json.contains("name") &&
            json.contains("quality") &&
            json.contains("cores") &&
            json.contains("price");
}

void pc::ComponentsModel::parseGPUComponents()
{
    std::string gpuFilePath = m_componentsDir + dirSep() + "gpu.json";
    std::ifstream f(gpuFilePath);
    if ( !f.is_open() ) return;
    json j = json::parse(f);
    if ( j.is_null() ) return;
    m_gpuComponents.reserve(j.size());
    for ( int i = 0; i < j.size(); i++ )
    {
        GPU gpu;
        json gpuJson = j[i];
        if ( !validateGPUJson(gpuJson) ) continue;
        gpu.name = gpuJson["name"].get<std::string>();
        gpu.quality = gpuJson["quality"].get<int>();
        gpu.memory = gpuJson["memory"].get<int>();
        gpu.price = gpuJson["price"].get<double>();
        m_gpuComponents.push_back( gpu );
    }
}

bool pc::ComponentsModel::validateGPUJson(const nlohmann::json &json)
{
    return json.contains("name") &&
            json.contains("quality") &&
            json.contains("memory") &&
            json.contains("price");
}

void pc::ComponentsModel::parseHDDComponents()
{
    std::string hddFilePath = m_componentsDir + dirSep() + "hdd.json";
    std::ifstream f(hddFilePath);
    if ( !f.is_open() ) return;
    json j = json::parse(f);
    if ( j.is_null() ) return;
    m_hddComponents.reserve(j.size());
    for ( int i = 0; i < j.size(); i++ )
    {
        HDD hdd;
        json hddJson = j[i];
        if ( !validateHDDJson(hddJson) ) continue;
        hdd.name = hddJson["name"].get<std::string>();
        hdd.quality = hddJson["quality"].get<int>();
        hdd.memory = hddJson["memory"].get<int>();
        hdd.price = hddJson["price"].get<double>();
        m_hddComponents.push_back( hdd );
    }
}

bool pc::ComponentsModel::validateHDDJson(const nlohmann::json &json)
{
    return json.contains("name") &&
            json.contains("quality") &&
            json.contains("memory") &&
            json.contains("price");
}

void pc::ComponentsModel::parseRAMComponents()
{
    std::string ramFilePath = m_componentsDir + dirSep() + "ram.json";
    std::ifstream f(ramFilePath);
    if ( !f.is_open() ) return;
    json j = json::parse(f);
    if ( j.is_null() ) return;
    m_ramComponents.reserve(j.size());
    for ( int i = 0; i < j.size(); i++ )
    {
        RAM ram;
        json ramJson = j[i];
        if ( !validateRAMJson(ramJson) ) continue;
        ram.name = ramJson["name"].get<std::string>();
        ram.quality = ramJson["quality"].get<int>();
        ram.memory = ramJson["memory"].get<int>();
        ram.price = ramJson["price"].get<double>();
        m_ramComponents.push_back( ram );
    }
}

bool pc::ComponentsModel::validateRAMJson(const nlohmann::json &json)
{
    return json.contains("name") &&
            json.contains("quality") &&
            json.contains("memory") &&
            json.contains("price");
}

void pc::ComponentsModel::parseSSDComponents()
{
    std::string ssdFilePath = m_componentsDir + dirSep() + "ssd.json";
    std::ifstream f(ssdFilePath);
    if ( !f.is_open() ) return;
    json j = json::parse(f);
    if ( j.is_null() ) return;
    m_ssdComponents.reserve(j.size());
    for ( int i = 0; i < j.size(); i++ )
    {
        SSD ram;
        json ramJson = j[i];
        if ( !validateSSDJson(ramJson) ) continue;
        ram.name = ramJson["name"].get<std::string>();
        ram.quality = ramJson["quality"].get<int>();
        ram.memory = ramJson["memory"].get<int>();
        ram.price = ramJson["price"].get<double>();
        m_ssdComponents.push_back( ram );
    }
}

bool pc::ComponentsModel::validateSSDJson(const nlohmann::json &json)
{
    return json.contains("name") &&
            json.contains("quality") &&
            json.contains("memory") &&
            json.contains("price");
}
