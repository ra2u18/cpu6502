#include "engine.h"
#include "log.h"

namespace cpu6205
{
    void Engine::Initialize()
    {
        mLogManager.Initialize();
    }

    void Engine::GetInfo()
    {
        C6205_TRACE("C6205_Emulator v{}.{}", 0, 1);
    }
}