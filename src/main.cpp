#include "componentsmodel.hpp"
#include "userdialog.hpp"
#include "pcselector.hpp"

#include <iostream>

using namespace pc;

int main()
{
    ComponentsModel model("components");
    if ( !view::validateModel(model) ) return -1;
    std::cout << "Program to select PC components for your goals" << std::endl;
    bool complite;
    do {
        complite = true;
        double badget = view::requestBuildBadget();
        PCBuildGoal goal = view::requestBuildGoal();
        PCBuild build = selectPC(model, badget, goal, &complite);
        if ( complite )
        {
            view::printSelectedBuild(build);
            complite = !view::askBuildAgain();
        }
        else
        {
            std::cout << "Can't find a build for you. Maybe you need "
                         "to change some of your parameters" << std::endl;
        }
    } while ( !complite );


    return 0;
}
