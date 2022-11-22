#pragma once

#include <list>
#include <string>
#include <map>

namespace cyan {
	/// <summary>
	/// Clean way to exit the program: halts the debug console from disapearing by requiring a button press and provides a message stating the program exit code.
	/// The output from this method should be returned from the main function for maximum clean-ness
	/// </summary>
	/// <param name="exitCode"></param>
	/// <returns></returns>
	int ProgramExit(const int exitCode) noexcept;

	class Logger {
		std::list<std::string> messageHistory;

		//default schema
		std::string schema = "%t [%y]: {%m} - %o";

		const std::string noModule = "Anonymous";

	public:
		//Error types
#ifndef cyanLog_NODEFAULTERRORS
		static const std::string INFO;
		static const std::string WARN;
		static const std::string ERROR;
		static const std::string FATAL;
#endif // !cyanLog_NODEFAULTERRORS

		Logger() noexcept;
		Logger(std::string logSchema) noexcept;

		void SetSchema(std::string logSchema) noexcept;

		void Output(const std::string message);
		void Output(const std::string type, const std::string message);
		void Output(const std::string type, const std::string modulePath, const std::string message);

		/// <summary>
		/// Returns the current time as a string in the format hh:mm:ss
		/// </summary>
		/// <returns></returns>
		static std::string GetTimeString();

		/// <summary>
		/// Returns the entire message history
		/// </summary>
		/// <returns></returns>
		std::list<std::string> GetMessageHistory() noexcept;

		/// <summary>
		/// Clears the entire message history
		/// </summary>
		/// <returns></returns>
		void ClearMessageHistory() noexcept;

		/// <summary>
		/// Saves the entire log history to a text file
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		bool SaveToFile(const std::string path);
		bool SaveToFile(const std::string path, const std::string errorType);
	};
}