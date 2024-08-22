#pragma once
#ifndef __SETTINGS_H__
#define __SETTINGS_H__
#include <exception>
#include <set>
#include <format>
#include <map>
#include <string>
#include <unordered_map>
#include <fstream>
#include <tuple>
#include <memory>
#include "Utility.h"
#include "Logger.h"
using namespace Utils;
using namespace Logger;

namespace Settings {
	class Config : public std::map<std::string, std::pair<std::string, std::string>>
	{
	public:

		std::set<std::pair<std::string, std::string>> defaultSettings =
		{
			{"startWithConsole",	"true"},
			{"showConsole",			"true"},
			{"windowWidth",			"800"},
			{"windowHeight",		"600"},
			{"crashOnStartup",		"false"},
			{"configFileName",		"config.ini"},
			{"logFileName",			"output.log"},
		};
		std::set<std::string> knownSettings =
		{
			"startWithConsole",
			"showConsole",
			"windowWidth",
			"windowHeight",
			"crashOnStartup",
			"configFileName",
			"logFileName",
		};

		Config();
		void setOption(std::string key, std::string val);

		~Config();
	private:
		std::unique_ptr<std::unordered_map<std::string, std::string>> __configure
		{
			new std::unordered_map<std::string,std::string>()
		};

		std::fstream configFile;
		bool isLoaded = false;
		bool cl_parsed = false;
		bool firstRun = true;


		void initialize_options()
		{
			__configure->emplace("startWithConsole",	"true"			);
			__configure->emplace("showConsole",		"false"			);
			__configure->emplace("windowWidth",		"800"			);
			__configure->emplace("windowHeight",		"600"			);
			__configure->emplace("crashOnStartup",		"false"			);
			__configure->emplace("configFileName",		"config.ini"	);
			__configure->emplace("logFileName",		"output.log"	);
		}

	public:
		bool startWithConsole(void)
		{
			return to_bool(getOption("startWithConsole"));
		}

		bool showConsole(void)
		{
			return to_bool(getOption("showConsole"));
		}

		bool crashOnStartup()
		{
			return to_bool(getOption("crashOnStartup"));
		}

		uint32_t windowWidth()
		{
			return stoi(getOption("windowWidth"));
		}

		uint32_t windowHeight()
		{
			return stoi(getOption("windowHeight"));
		}

		std::string configFileName()
		{
			return getOption("configFileName");
		}

		std::string logFileName() { return getOption("logFileName"); }

		// before commandline args....
		void LoadOptionsStartup();

		// rehash after startup
		void LoadOptions()
		{
			LoadOptionsStartup();
		}
		void LoadOptionsDefaults();
		// dump options before close
		void SaveOptions();

		// Make private and have getters for all known options....
		// at().first = currentValue
		// at().second = defaultValue
		std::string getOption(std::string optionName)
		{
			std::string result;

			if (__configure->find(optionName) != __configure->end())
			{
				auto t = __configure->find(optionName);
				result = t->second;
			}
			else
			{
				result = "";
			}

			return result;
		}

		std::string getOptionDefault(std::string optionName)
		{
			throw std::exception("Function not yet implemented;");
		}

		void HandleCommandLine(int argc, std::vector<std::string> args, char* env);
	};
	extern std::shared_ptr<Settings::Config> Conf;
}
#endif // __SETTINGS_H__