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
	int ProgramExit(int exitCode);

	class Logger {
		std::list<std::string> messageHistory;

		//default schema
		std::string schema = "%t [%y]: {%m} - %o";

		const std::string noModule = "Anonymous";

	public:
		static const enum LogTypes {
			INFO = 0,
			WARNING,
			ERROR,
			FATAL,
			COUNT
		};

	private:
		const std::map<LogTypes, std::string> ErrorDecorators = {
			{INFO, "Info"},
			{WARNING, "Warning"},
			{ERROR, "Error"},
			{FATAL, "FATAL"}
		};

	public:
		Logger();
		Logger(std::string logSchema);

		void SetSchema(std::string logSchema);

		void Output(std::string message);
		void Output(std::string modulePath, std::string message);
		void Output(LogTypes type, std::string message);
		void Output(LogTypes type, std::string modulePath, std::string message);

		/// <summary>
		/// Returns the current time as a string in the format hh:mm:ss
		/// </summary>
		/// <returns></returns>
		static std::string GetTimeString();

		/// <summary>
		/// Returns the entire message history
		/// </summary>
		/// <returns></returns>
		std::list<std::string> GetMessageHistory();

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
		bool SaveToFile(std::string path);
	};
}