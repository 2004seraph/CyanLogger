#include <iostream>
#include <stdio.h>

#include "CyanLogger.hpp"

#include <map>


int main(int argc, char* argv[]) {
	cyan::Logger log;

	log.Output(cyan::Errors::INFO, "main", "Hello world");
	log.Output("blah");

	log.Output(cyan::Errors::ERROR, "main", "I'm gay");

	log.SaveToFile("log.txt");

	return cyan::ProgramExit(1);
}