/*************************************************************************
> File Name: Logger.h
> Project Name: CubbyFlow
> Author: Chan-Ho Chris Ohk
> Purpose: Super simple logger implementation.
> Created Time: 2017/04/23
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef CUBBYFLOW_LOGGER_H
#define CUBBYFLOW_LOGGER_H

#include <sstream>

namespace CubbyFlow
{
	enum class LogLevel
	{
		Info,
		Warn,
		Error,
		Debug
	};

	//!
	//! \brief Super simple logger implementation.
	//!
	//! This is a super simple logger implementation that has minimal logging
	//! capability. Currently, the class doesn't support multi-thread logging.
	//!
	class Logger final
	{
	public:
		//! Constructs a logger with logging level.
		explicit Logger(LogLevel level);

		//! Destructor.
		~Logger();

		//! Writes a value to the buffer stream.
		template <typename T>
		const Logger& operator<<(const T& x) const
		{
			m_buffer << x;
			return *this;
		}

	private:
		LogLevel m_level;
		mutable std::stringstream m_buffer;
	};

	//! Helper class for logging.
	class Logging
	{
	public:
		//! Sets the output stream for the info level logs.
		static void SetInfoStream(std::ostream* stream);

		//! Sets the output stream for the warning level logs.
		static void SetWarnStream(std::ostream* stream);

		//! Sets the output stream for the error level logs.
		static void SetErrorStream(std::ostream* stream);

		//! Sets the output stream for the debug level logs.
		static void SetDebugStream(std::ostream* stream);

		//! Sets the output stream for all the log levels.
		static void SetAllStream(std::ostream* stream);

		//! Returns the header string.
		static std::string GetHeader(LogLevel level);
	};

	//! Info-level logger.
	extern Logger infoLogger;

	//! Warn-level logger.
	extern Logger warnLogger;

	//! Error-level logger.
	extern Logger errorLogger;

	//! Debug-level logger.
	extern Logger debugLogger;

	#define CUBBYFLOW_INFO \
		(Logger(LogLevel::Info) << Logging::GetHeader(LogLevel::Info) \
		 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
	#define CUBBYFLOW_WARN \
		(Logger(LogLevel::Warn) << Logging::GetHeader(LogLevel::Warn) \
		 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
	#define CUBBYFLOW_ERROR \
		(Logger(LogLevel::Error) << Logging::GetHeader(LogLevel::Error) \
		 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
	#define CUBBYFLOW_DEBUG \
		(Logger(LogLevel::Debug) << Logging::GetHeader(LogLevel::Debug) \
		 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
}

#endif