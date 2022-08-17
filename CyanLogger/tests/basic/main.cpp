#include <iostream>
#include <stdio.h>

#include "CyanLogger.hpp"

#include <map>


int main(int argc, char* argv[]) {
	const std::map<std::string, std::string> ErrorTypes = {
		{"INFO",  "Info"},
		{"WARN",  "Warning"},
		{"ERROR", "Error"},
		{"FATAL", "FATAL"}
	};

	cyan::Logger log;

	log.Output(log.INFO, "main", "Hello world");
	log.Output("blah");

	log.Output(log.ERROR, "main", "I'm gay");

	log.SaveToFile("log.txt");

	return cyan::ProgramExit(1);
}