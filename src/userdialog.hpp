#pragma once

#include "pcselector.hpp"

namespace pc
{
    namespace view
    {
        bool validateModel(const ComponentsModel & model);

        double requestBuildBadget();

        PCBuildGoal requestBuildGoal();

        void printSelectedBuild( const PCBuild & build );

        bool askBuildAgain();
    }
}
