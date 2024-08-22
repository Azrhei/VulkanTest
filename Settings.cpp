#include <filesystem>
#include <iostream>
#include <format>
#include <string>
#include <map>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <set>
#include "Logger.h"
#include "Settings.h"

using namespace std;
using namespace Logger;

namespace Settings {

	Config::Config()
	{
		initialize_options();
		configFile.open(configFileName(), fstream::app);
	}

	Config::~Config()
	{
		//SaveOptions(); 
	}

	void Config::setOption(string key, string val)
	{
		//__configure->emplace(key, val);
	}

	void Config::LoadOptionsStartup()
	{
		if (filesystem::exists(configFileName()))
		{
			configFile.open(configFileName(), fstream::in);
			string line;
			while (configFile >> line)
			{
				// Skip empty and comment lines
				if (line.empty() || line[0] == '#')
				{
					continue;
				}
				string val;
				//string val2;
				string key;

				Log->Console(format("Line read from : {} :: {} ", configFileName(), line));
				
				size_t token1pos = line.find_first_of(':');
				size_t token2pos = line.find_last_of(':');

				key = line.substr(0,token1pos);
				val = line.substr(token1pos+1, token2pos-token1pos-1);
				//val2 = line.substr(token2pos+1);

				if (std::find(knownSettings.begin(), knownSettings.end(), key) != knownSettings.end())
				{	// Empty setting means keep existing value

					if (val == "") val = getOption(key);
					//if (val2 == "") val2 = getOptionDefault(key);

					Log->Console(format("StartUpOption Parsed : {} <{}>",key,val));				
					//__configure->emplace(key, val);
				}
				else
				{
					// no such option
					Log->Error(format("Option: [{}] ... was not found or does not exist.", key));
				}		
			}
			isLoaded = true;
		}
 		else
		{
			firstRun = true;
			SaveOptions();
			isLoaded = true;
		}
	}

	void Config::LoadOptionsDefaults()
	{
		throw exception("Function not yet implemented.");
	}

	void Config::SaveOptions()
	{
		auto t = __configure->begin();
		for( auto t : *__configure)
		{
			configFile << t.first << ":" << t.second << nl;
		}
	}

	void Config::HandleCommandLine(int argc, std::vector<std::string> args, char* env)
	{
		string key;
		string val;

		// Ensure order of operations....commandline overwrites loaded options.
		if (!isLoaded)
		{
			LoadOptionsStartup();
		}
		if (firstRun)
		{

		}
		bool first = true;
		for (auto& s : args)
		{
			//Skip program name
			if (first)
			{
				first = false;
				continue;
			}

			// command line starts with "--" before option name
			size_t token_pos = s.find('=');

			if (token_pos < 0)
			{
				key = s.substr(2);
				val = "true";
			}
			else
			{ 
				key = s.substr(2, token_pos-2);
				val = s.substr(token_pos+1, s.length() - 1);
			}
			Log->Console(format("Command Line option parsed : [{}] : {}", key, val));
			__configure->emplace(key, val);
		}
		if (firstRun)
		{
			SaveOptions();
		}
		else
		{

		}
		cl_parsed = true;
	}
	shared_ptr<Config> Conf{};
}