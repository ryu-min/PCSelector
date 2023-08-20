#include "userdialog.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

double pc::view::requestBuildBadget()
{
    double badget;
    bool complite = false;
    do
    {
        std::cout << "Specify the computer build budget: ";
        std::string badgetString;
        std::getline(std::cin, badgetString);
        try
        {
            badget = std::stod(badgetString);
            if ( badget < 0 )
            {
                std::cout << "build budget should be more than 0" << std::endl;
            }
            else
            {
                complite = true;
            }
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "build budget should a be number" << std::endl;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "build budget is out of range" << std::endl;
        }
    } while ( !complite );
    return badget;
}

pc::PCBuildGoal pc::view::requestBuildGoal()
{
    PCBuildGoal goal;
    bool complite = false;
    do
    {
        std::cout << "Specify the computer build goal (select number): " << std::endl;
        std::cout << "1. Polygonal 3D modeling " << std::endl ;
        std::cout << "2. Parametric 3D modeling " << std::endl ;
        std::cout << "3. Games " << std::endl ;
        std::cout << "4. Design " << std::endl ;
        std::cout << "5. Programming " << std::endl ;
        std::cout << "6. Media server " << std::endl ;
        std::cout << "7. Office task " << std::endl ;
        std::cout << "Goal number: ";
        std::string goalString;
        std::getline(std::cin, goalString);
        std::stringstream ss(goalString);
        int goalInt;
        if (ss >> goalInt )
        {
            if ( ( goalInt < 0 ) || ( goalInt > 7  ) )
            {
                std::cout << "Your need to select one of the number in in the range 1-7" << std::endl;
            }
            else
            {
                goal = static_cast<PCBuildGoal>(goalInt);
                complite = true;
            }
        }
        else
        {
            std::cout << "Your need to input number of goal" << std::endl;
        }

    } while ( !complite );
    return goal;
}

bool pc::view::validateModel(const ComponentsModel &model)
{
    if ( model.getCPU().size() &&
         model.getGPU().size() &&
         model.getHDD().size() &&
         model.getRAM().size() &&
         model.getSSD().size() )
    {
        return true;
    }
    else
    {
        std::cout << "Components model are not valid. Make sure that the program is configured correctly ";
        return false;
    }
}

void pc::view::printSelectedBuild(const PCBuild &build)
{
    std::cout << "Build selected for your:" << std::endl;
    std::cout << "CPU: " << build.cpu.name  << std::endl;
    std::cout << "RAM: " << build.ram.name  << std::endl;
    if ( !build.gpu.name.empty() )
    {
        std::cout << "GPU: " << build.gpu.name << std::endl;
    }
    if ( !build.ssd.name.empty() )
    {
        std::cout << "SSD: " << build.ssd.name << std::endl;
    }
    if ( !build.hdd.name.empty() )
    {
        std::cout << "HDD: " << build.hdd.name << std::endl;
    }
    std::cout << "Build price: " << getBuildPrice(build) << std::endl;
}

bool pc::view::askBuildAgain()
{
    bool complited = false;
    bool result = false;
    do {
        std::cout << "Do you want to create another build? (y/n):";
        std::string answer;
        std::getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if ( answer == "y" )
        {
            complited = true;
            result = true;
        }
        else if ( answer == "n" )
        {
            complited = true;
            result = false;
        }
        else
        {
            std::cout << "type 'y' and 'n'" << std::endl;
        }
    } while ( !complited );
    return result;
}
