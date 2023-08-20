#include "pcselector.hpp"

#include <algorithm>
#include <iostream>

void validateComponentsByCondition(const pc::BuildCondition & cond,
                                   std::vector<pc::CPU> & cpus,
                                   std::vector<pc::GPU> & gpus,
                                   std::vector<pc::HDD> & hdds,
                                   std::vector<pc::RAM> & rams,
                                   std::vector<pc::SSD> & ssds)
{
    auto cpuIt = std::remove_if(cpus.begin(), cpus.end(), [&cond](pc::CPU & cpu ) {
                 return cpu.cores < cond.minCPUCores ||
                 cpu.quality < cond.minCPUQuality;
    });
    cpus.erase(cpuIt, cpus.end());

    auto gpuIt = std::remove_if(gpus.begin(), gpus.end(), [&cond](pc::GPU & gpu ) {
                 return gpu.memory < cond.minGPUMemory ||
                 gpu.quality < cond.minCPUQuality;
    });
    gpus.erase(gpuIt, gpus.end());

    auto hddIt = std::remove_if(hdds.begin(), hdds.end(), [&cond](pc::HDD & hdd ) {
                 return hdd.memory < cond.minHDDMemory ||
                 hdd.quality < cond.minHDDQuality;
    });
    hdds.erase(hddIt, hdds.end());

    auto ramsIt = std::remove_if(rams.begin(), rams.end(), [&cond](pc::RAM & ram ) {
                  return ram.memory < cond.minRAMMemory ||
                  ram.quality < cond.minRAMQuality;
    });
    rams.erase(ramsIt, rams.end());

    auto ssdIt = std::remove_if(ssds.begin(), ssds.end(), [&cond](pc::SSD & ssd ) {
                 return ssd.memory < cond.minSSDMemory ||
                 ssd.quality < cond.minSSDQuality;
    });
    ssds.erase(ssdIt, ssds.end());
}

std::vector<pc::PCBuild> getCombinationsWithGPUandHDD(const std::vector<pc::CPU> & cpus,
                                                      const std::vector<pc::GPU> & gpus,
                                                      const std::vector<pc::HDD> & hdds,
                                                      const std::vector<pc::RAM> & rams)
{
    std::vector<pc::PCBuild> builds;
    for ( const auto & cpu : cpus )
    {
        for ( const auto & gpu : gpus )
        {
            for ( const auto & hdd : hdds )
            {
                for ( const auto & ram : rams )
                {
                    pc::PCBuild build;
                    build.cpu = cpu;
                    build.gpu = gpu;
                    build.hdd = hdd;
                    build.ram = ram;
                    builds.push_back(build);
                }
            }
        }
    }
    return builds;
}

std::vector<pc::PCBuild> getCombinationsWithGPUandSSD(const std::vector<pc::CPU> & cpus,
                                                      const std::vector<pc::GPU> & gpus,
                                                      const std::vector<pc::SSD> & ssds,
                                                      const std::vector<pc::RAM> & rams)
{
    std::vector<pc::PCBuild> builds;
    for ( const auto & cpu : cpus )
    {
        for ( const auto & gpu : gpus )
        {
            for ( const auto & ssd : ssds )
            {
                for ( const auto & ram : rams )
                {
                    pc::PCBuild build;
                    build.cpu = cpu;
                    build.gpu = gpu;
                    build.ssd = ssd;
                    build.ram = ram;
                    builds.push_back(build);
                }
            }
        }
    }
    return builds;
}



std::vector<pc::PCBuild> getCombinationsWithHDD(const std::vector<pc::CPU> & cpus,
                                                const std::vector<pc::HDD> & hdds,
                                                const std::vector<pc::RAM> & rams)
{
    std::vector<pc::PCBuild> builds;
    for ( const auto & cpu : cpus )
    {
        for ( const auto & hdd : hdds )
        {
            for ( const auto & ram : rams )
            {
                pc::PCBuild build;
                build.cpu = cpu;
                build.hdd = hdd;
                build.ram = ram;
                builds.push_back(build);
            }
        }
    }
    return builds;
}

std::vector<pc::PCBuild> getCombinationsWithSSD(const std::vector<pc::CPU> & cpus,
                                                const std::vector<pc::SSD> & ssds,
                                                const std::vector<pc::RAM> & rams)
{
    std::vector<pc::PCBuild> builds;
    for ( const auto & cpu : cpus )
    {
        for ( const auto & ssd : ssds )
        {
            for ( const auto & ram : rams )
            {
                pc::PCBuild build;
                build.cpu = cpu;
                build.ssd = ssd;
                build.ram = ram;
                builds.push_back(build);
            }
        }
    }
    return builds;
}


std::vector<pc::PCBuild> getAppliedBuildCombination(const pc::BuildCondition & cond,
                                                    const std::vector<pc::CPU> & cpus,
                                                    const std::vector<pc::GPU> & gpus,
                                                    const std::vector<pc::HDD> & hdds,
                                                    const std::vector<pc::RAM> & rams,
                                                    const std::vector<pc::SSD> & ssds)
{
    if ( cond.needGPU && cond.needHDD )
    {
        return getCombinationsWithGPUandHDD(cpus, gpus, hdds, rams);
    }
    else if ( cond.needGPU && cond.needSSD )
    {
        return getCombinationsWithGPUandSSD(cpus, gpus, ssds, rams);
    }
    else if ( cond.needHDD )
    {
        return getCombinationsWithHDD(cpus, hdds, rams);
    }
    else if ( cond.needSSD )
    {
        return getCombinationsWithSSD(cpus, ssds, rams);
    }
    return std::vector<pc::PCBuild>();
}

pc::PCBuild getBestBuild( double badget,
                          std::vector<pc::PCBuild> builds,
                          bool * ok )
{
    pc::PCBuild result;
    if ( builds.empty() )
    {
        if ( ok ) *ok = false;
        return result;
    }

    auto buildsIt = std::remove_if(builds.begin(), builds.end(), [badget](const pc::PCBuild & build ) {
                 return pc::getBuildPrice(build) > badget;
    });
    builds.erase(buildsIt, builds.end());

    if ( builds.empty() )
    {
        if ( ok ) *ok = false;
        return result;
    }

    result = builds[0];
    int maxQuality = pc::getBuildQuality(result);
    for ( int i = 1; i < builds.size(); i++ )
    {
        int quality = pc::getBuildQuality(builds[i]);
        if ( quality > maxQuality )
        {
            maxQuality = quality;
            result = builds[i];
        }
    }
    return result;
}


pc::PCBuild pc::selectPC(const ComponentsModel &model,
                         double badget,
                         PCBuildGoal goal,
                         bool *ok)
{
    BuildCondition cond = getConditionForBuildGoal(goal);
    std::vector<CPU> cpus = model.getCPU();
    std::vector<GPU> gpus = model.getGPU();
    std::vector<HDD> hdds = model.getHDD();
    std::vector<RAM> rams = model.getRAM();
    std::vector<SSD> ssds = model.getSSD();
    validateComponentsByCondition(cond, cpus, gpus, hdds, rams, ssds);
    auto combinations = getAppliedBuildCombination(cond, cpus, gpus, hdds, rams, ssds);
    return getBestBuild(badget, combinations, ok);
}

pc::BuildCondition pc::getConditionForBuildGoal(PCBuildGoal goal)
{
    switch (goal)
    {
        case PCBuildGoal::POLYGONAL_MODELING_3D:
        {
            BuildCondition cond;
            cond.minCPUQuality = 100;
            cond.minCPUCores = 10;
            cond.needGPU = true;
            cond.minGPUQuality = 95;
            cond.minGPUMemory = 6;
            cond.needHDD = true;
            cond.minHDDMemory = 1000;
            cond.minHDDQuality = 55;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = false;
            return cond;
        }; break;

        case PCBuildGoal::PARAMETRIC_MODELING_3D:
        {
            BuildCondition cond;
            cond.minCPUQuality = 100;
            cond.minCPUCores = 10;
            cond.needGPU = true;
            cond.minGPUQuality = 90;
            cond.minGPUMemory = 6;
            cond.needHDD = true;
            cond.minHDDMemory = 500;
            cond.minHDDQuality = 55;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = false;
            return cond;
        }; break;


        case PCBuildGoal::GAMES:
        {
            BuildCondition cond;
            cond.minCPUQuality = 100;
            cond.minCPUCores = 10;
            cond.needGPU = true;
            cond.minGPUQuality = 95;
            cond.minGPUMemory = 6;
            cond.needHDD = false;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = true;
            cond.minSSDMemory = 500;
            cond.minSSDQuality = 62;
            return cond;
        }; break;


        case PCBuildGoal::DESIGN:
        {
            BuildCondition cond;
            cond.minCPUQuality = 95;
            cond.minCPUCores = 4;
            cond.needGPU = true;
            cond.minGPUQuality = 87;
            cond.minGPUMemory = 4;
            cond.needHDD = false;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = true;
            cond.minSSDMemory = 1000;
            cond.minSSDQuality = 62;
            return cond;
        }; break;


        case PCBuildGoal::PROGRAMMING:
        {
            BuildCondition cond;
            cond.minCPUQuality = 95;
            cond.minCPUCores = 4;
            cond.needGPU = true;
            cond.minGPUQuality = 87;
            cond.minGPUMemory = 4;
            cond.needHDD = true;
            cond.minHDDMemory = 500;
            cond.minHDDQuality = 58;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = false;
            return cond;
        }; break;

        case PCBuildGoal::MEDIA_SERVER:
        {
            BuildCondition cond;
            cond.minCPUQuality = 90;
            cond.minCPUCores = 4;
            cond.needGPU = true;
            cond.minGPUQuality = 87;
            cond.minGPUMemory = 4;
            cond.needHDD = true;
            cond.minHDDMemory = 2000;
            cond.minHDDQuality = 58;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = false;
            return cond;
        }; break;

        case PCBuildGoal::OFFICE_TASKS:
        {
            BuildCondition cond;
            cond.minCPUQuality = 80;
            cond.minCPUCores = 4;
            cond.needGPU = true;
            cond.minGPUQuality = 80;
            cond.minGPUMemory = 2;
            cond.needHDD = true;
            cond.minHDDMemory = 500;
            cond.minHDDQuality = 50;
            cond.minRAMMemory = 8;
            cond.minRAMQuality = 53;
            cond.needSSD = false;
            return cond;
        }; break;
    }
    return BuildCondition();
}

double pc::getBuildPrice(const PCBuild &build)
{
    return build.cpu.price  +
            build.gpu.price +
            build.hdd.price +
            build.ram.price +
            build.ssd.price;
}

int pc::getBuildQuality(const PCBuild &build)
{
    return build.cpu.quality  +
            build.gpu.quality +
            build.hdd.quality +
            build.ram.quality +
            build.ssd.quality;
}

