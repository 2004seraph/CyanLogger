#include "CyanLogger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <regex>
#include <fstream>

namespace cyan {
	int ProgramExit(const int exitCode) noexcept {
#ifdef _DEBUG
		std::cout << std::endl << "======================";

		switch (exitCode) {
		case EXIT_SUCCESS:
			std::cout << std::endl << "Program ended without exceptions: " << exitCode;
			break;
		default:
			std::cout << std::endl << "Program ended with exit code: " << exitCode;
			break;
		}

		std::cout << std::endl << std::endl << "press any key to exit console";

		std::getchar();
#endif
		return exitCode;
	}

#ifndef cyanLog_NODEFAULTERRORS
	const std::string Logger::INFO  = "Info";
	const std::string Logger::WARN  = "Warn";
	const std::string Logger::ERROR = "Error";
	const std::string Logger::FATAL = "FATAL";
#endif // !cyanLog_NODEFAULTERRORS

	Logger::Logger() noexcept {

	}

	Logger::Logger(const std::string logSchema) noexcept {
		schema = logSchema;
	}

	void Logger::SetSchema(const std::string logSchema) noexcept {
		schema = logSchema;
	};

	void Logger::Output(const std::string type, const std::string modulePath, const std::string message)
	{
		std::string finalOutput = schema;

		std::regex timeRegex(R"(%t)");
		std::regex typeRegex(R"(%y)");
		std::regex moduleRegex(R"(%m)");
		std::regex outputRegex(R"(%o)");

		finalOutput =
			std::regex_replace(//message
				std::regex_replace(//module
					std::regex_replace(//type
						std::regex_replace(finalOutput, timeRegex, GetTimeString()),//time
						typeRegex,
						type
					),
					moduleRegex,
					modulePath
				),
				outputRegex,
				message
			);

		messageHistory.push_back(finalOutput);

		std::cout << finalOutput << std::endl;
	}

	void Logger::Output(const std::string type, const std::string message)
	{
		Output(type, noModule, message);
	}

	void Logger::Output(const std::string message) {
		Output("Info", noModule, message);
	};

	std::string Logger::GetTimeString() {
		std::time_t NowTime = std::time(0);
		std::tm ltm;
		localtime_s(&ltm, &NowTime);

		std::string FormatTime = 
			((ltm.tm_hour < 10) ? "0" : "") + std::to_string(ltm.tm_hour) + ":" + 
			((ltm.tm_min < 10) ? "0" : "") + std::to_string(ltm.tm_min) + ":" + 
			((ltm.tm_sec < 10) ? "0" : "") + std::to_string(ltm.tm_sec);

		return FormatTime;
	}

	std::list<std::string>Logger::GetMessageHistory() noexcept {
		return messageHistory;
	}

	void Logger::ClearMessageHistory() noexcept {
		messageHistory.clear();
	}

	bool Logger::SaveToFile(const std::string path, const std::string errorType) {
		try {
			std::ofstream LogFile(path);
			for (auto const& i : messageHistory) {
				LogFile << i << std::endl;
			}
			LogFile.close();
		}
		catch (...) {
			Output(errorType, "LOGGER::SAVETOFILE", "Could not dump log to file.");
			return false;
		}

		return true;
	};

	bool Logger::SaveToFile(std::string path) {
		return SaveToFile(path, "Error");
	}
}