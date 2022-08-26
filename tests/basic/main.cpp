#include <iostream>
#include <stdio.h>

#define NOERRORCLASS
#include "CyanLogger.hpp"

#include <map>

#include <any>


int main(int argc, char* argv[]) {
	//cyan::Logger log;

	//log.Output(cyan::Errors::INFO, "main", "Hello world");
	//log.Output("blah");

	//log.Output(cyan::Errors::ERROR, "main", "I'm gay");

	//log.SaveToFile("log.txt");

	//try {
	//	int r = std::any_cast<int>(std::any("apple"));
	//}
	//catch (...) {
	//	log.Output(cyan::Errors::INFO, "main::stupidexample", "Inevitable error");
	//}

	//return cyan::ProgramExit(1);

	cyan::Logger log;

	//log.SetSchema("{%t}--%y %o");

	log.Output(log.INFO, "main", "Hello world");

	log.Output("This porgram is useless!");

	try {
		int x = std::any_cast<int>(std::any("apple"));
	}
	catch (...) {
		log.Output(log.INFO, "main::stupidexample", "Inevitable error");
	}

	log.SaveToFile("epic.txt");

	return 0;
}