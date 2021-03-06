#pragma once

#include "Types.h"
#include "ISubSystem.h"

class Logger : public ISubSystem
{
public:
	enum : unsigned int
	{
		FLAG_DEFAULT	= 0x00000001,
		FLAG_GRAPHICS	= 0x00000002,
		FLAG_IO			= 0x00000004,
		FLAG_INPUT		= 0x00000008,
		FLAG_AUDIO		= 0x00000010,
		FLAG_GAME_STATE = 0x00000020,
	};
	Logger(Engine* engine);
	void setFlag(uint flag, bool enabled);
	void setFlagTrace(uint flag, bool enabled);
	void setFlagWarning(uint flag, bool enabled);
	void setFlagError(uint flag, bool enabled);
	void logTrace(const std::string& message, uint flags = FLAG_DEFAULT);
	void logWarning(const std::string& message, uint flags = FLAG_DEFAULT);
	void logError(const std::string& message, uint flags = FLAG_DEFAULT);
private:
	uint flags_trace_;
	uint flags_warning_;
	uint flags_error_;
};


/*
#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(Logger, LoggerLocator)*/

inline void LOG(const std::string& message, uint flags = Logger::FLAG_DEFAULT)
{
	LOGGER->logTrace(message, flags);
}

inline void LOG_WARNING(const std::string& message, uint flags = Logger::FLAG_DEFAULT)
{
	LOGGER->logWarning(message, flags);
}

inline void LOG_ERROR(const std::string& message, uint flags = Logger::FLAG_DEFAULT)
{
	LOGGER->logError(message, flags);
}