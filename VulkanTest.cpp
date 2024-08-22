#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <format>
#include <exception>

#include "Settings.h"
#include "Logger.h"
#include "GameEngine.h"


using namespace std;
using namespace Logger;
using namespace Settings;

int main(int argc, char** argv, char* env)
{	
	GameEngine::GameEngine app;
	Conf->setOption("logFileName", "output.log");
	Log->Console("Hello World!");

	Conf->HandleCommandLine(argc,std::vector<std::string>(argv,argv+argc), env);
	
	Log->Console(format("Loading default config file : {}", Conf->configFileName() ));
	Conf->LoadOptionsStartup();
	Log->Console("Parsing Command Line");
	
	bool doCrash = Conf->crashOnStartup();
	if (doCrash)
	{
		Log->Exception("Crash on Startup : via settings.", std::exception());
		throw std::exception("Crash on startup");
	}

	try {
		app.run();
	}
	catch (const std::exception& e) {
		Log->Fatal(e.what(), EXIT_FAILURE);
	}

	Conf->SaveOptions();
	
	return EXIT_SUCCESS;
}