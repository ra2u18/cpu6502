#include "managers/logmanager.h"

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace cpu6205::managers
{
	void LogManager::Initialize()
	{   
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // [2021-01-01 19:30:00 <message>]
		consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

        // Only one sink to the console output
        std::vector<spdlog::sink_ptr> sinks{ consoleSink };
        auto logger = std::make_shared<spdlog::logger>(C6205_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
    }

    void LogManager::Shutdown()
	{
		spdlog::shutdown();
	}
}