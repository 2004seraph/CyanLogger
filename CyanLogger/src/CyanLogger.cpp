#include "CyanLogger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <regex>
#include <fstream>

namespace cyan {
	int ProgramExit(int exitCode) {
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
		
		return exitCode;
	}

#ifndef cyanLog_NOERRORCLASS
	const std::string Errors::INFO = "Info";
	const std::string Errors::WARN = "Warning";
	const std::string Errors::ERROR = "Error";
	const std::string Errors::FATAL = "FATAL";
#endif // !cyanLog_NOERRORCLASS

	Logger::Logger() {

	}

	Logger::Logger(std::string logSchema) {
		schema = logSchema;
	}

	void Logger::SetSchema(std::string logSchema) {
		schema = logSchema;
	};

	void Logger::Output(std::string type, std::string modulePath, std::string message)
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

	void Logger::Output(std::string type, std::string message)
	{
		Output(type, noModule, message);
	}

	void Logger::Output(std::string message) {
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

	std::list<std::string>Logger::GetMessageHistory() {
		return messageHistory;
	}

	void Logger::ClearMessageHistory() noexcept {
		messageHistory.clear();
	}

	bool Logger::SaveToFile(std::string path, std::string errorType) {
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