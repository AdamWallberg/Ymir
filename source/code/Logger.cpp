#include "Logger.h"

Logger::Logger()
	: flags_trace_(-1) // Set all bits to true
	, flags_warning_(-1)
	, flags_error_(-1)
{
}

void Logger::setFlag(uint flag, bool enabled)
{
	setFlagTrace(flag, enabled);
	setFlagWarning(flag, enabled);
	setFlagError(flag, enabled);
}

void Logger::setFlagTrace(uint flag, bool enabled)
{
	if (enabled)
		flags_trace_ |= flag;
	else
		flags_trace_ &= ~flag;
}

void Logger::setFlagWarning(uint flag, bool enabled)
{
	if (enabled)
		flags_warning_ |= flag;
	else
		flags_warning_ &= ~flag;
}

void Logger::setFlagError(uint flag, bool enabled)
{
	if (enabled)
		flags_error_ |= flag;
	else
		flags_error_ &= ~flag;
}

void Logger::logTrace(const std::string& message, uint flags /* = FLAG_DEFAULT */)
{
	if (flags_trace_ & flags)
	{
		printf((message + "\n").c_str());
	}
}

void Logger::logWarning(const std::string& message, uint flags /* = FLAG_DEFAULT */)
{
	if (flags_warning_ & flags)
	{
		printf(("WARNING: " + message + "\n").c_str());
	}
}

void Logger::logError(const std::string& message, uint flags /* = FLAG_DEFAULT */)
{
	if (flags_error_ & flags)
	{
		printf(("ERROR: " + message + "\n").c_str());
	}
}

SERVICE_LOCATOR_SOURCE(Logger, LoggerLocator)