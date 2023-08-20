#pragma once

#include "components.hpp"
#include "componentsmodel.hpp"

namespace pc
{
    enum class PCBuildGoal
    {
        POLYGONAL_MODELING_3D   = 1,
        PARAMETRIC_MODELING_3D  = 2,
        GAMES                   = 3,
        DESIGN                  = 4,
        PROGRAMMING             = 5,
        MEDIA_SERVER            = 6,
        OFFICE_TASKS            = 7
    };

    struct PCBuild
    {
        CPU cpu;
        GPU gpu;
        HDD hdd;
        RAM ram;
        SSD ssd;
    };

    PCBuild selectPC(const ComponentsModel & model,
                     double badget,
                     PCBuildGoal goal,
                     bool * ok = nullptr );


    struct BuildCondition
    {
        int minCPUQuality;
        int minCPUCores;

        bool needGPU;
        int minGPUQuality;
        int minGPUMemory;

        bool needHDD;
        int minHDDQuality;
        int minHDDMemory;

        int minRAMQuality;
        int minRAMMemory;

        bool needSSD;
        int minSSDQuality;
        int minSSDMemory;
    };

    BuildCondition getConditionForBuildGoal(PCBuildGoal goal);

    double getBuildPrice( const PCBuild & build);

    int getBuildQuality( const PCBuild & build);
}
