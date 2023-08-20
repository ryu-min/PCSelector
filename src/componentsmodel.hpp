#pragma once

#include <string>
#include <vector>

#include "components.hpp"
#include "json/json.hpp"


namespace pc
{
    class ComponentsModel
    {

    public:
        ///
        /// \param componentsDir - диреректория, содержащая json файлы
        ///
        explicit ComponentsModel( const std::string & componentsDir );

        std::vector<CPU> getCPU() const noexcept { return m_cpuComponents; }

        std::vector<GPU> getGPU() const noexcept { return m_gpuComponents; }

        std::vector<HDD> getHDD() const noexcept { return m_hddComponents; }

        std::vector<RAM> getRAM() const noexcept { return m_ramComponents; }

        std::vector<SSD> getSSD() const noexcept { return m_ssdComponents; }


    protected:
        void parseCPUComponents();
        bool validateCPUJson(const nlohmann::json & json);

        void parseGPUComponents();
        bool validateGPUJson(const nlohmann::json & json);

        void parseHDDComponents();
        bool validateHDDJson(const nlohmann::json & json);

        void parseRAMComponents();
        bool validateRAMJson(const nlohmann::json & json);

        void parseSSDComponents();
        bool validateSSDJson(const nlohmann::json & json);

    protected:
        std::string m_componentsDir;
        std::vector<CPU> m_cpuComponents;
        std::vector<GPU> m_gpuComponents;
        std::vector<HDD> m_hddComponents;
        std::vector<RAM> m_ramComponents;
        std::vector<SSD> m_ssdComponents;
    };

}


