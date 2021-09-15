#pragma once

#include "managers/logmanager.h"
#include <iostream>

namespace cpu6205
{
    class Engine
    {
    public:
        Engine()
        { 
            std::cout << "We've instantiated engine!" << std::endl;
            Initialize();
        }

        ~Engine(){  mLogManager.Shutdown(); }

        void Initialize();
        void GetInfo();
    private:
        // Managers
        managers::LogManager mLogManager;
    };
}