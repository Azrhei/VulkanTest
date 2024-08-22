#pragma once

#ifndef __UTILITY_H
#define __UTILITY_H

#include <string>
#include <iostream>

namespace Utils
{


	#define NEWLINE					 "\n"
	#define WIDE_NEWLINE			L"\n"
	#define CARRIAGE_RETURN			 "\r"
	#define WIDE_CARRIAGE_RETURN	L"\r"

	#define EXIT_BAD_COMMANDLINE	0b001
	#define	EXIT_BAD_CONFIG_FORMAT	0b010
	#define	EXIT_CANNOT_OPEN_FILES	0b100

	inline std::wostream& nl(std::wostream& o) { return o << WIDE_NEWLINE; }
	inline std::ostream& nl(std::ostream& o) { return o << NEWLINE; }

	/* Convert std::string str to bool
	 * Except "TRUE" || "FALSE
	 * Does not except (yet) "1" | "0"
	 * Does not except (yet) "T" | "F"
	 */
	bool to_bool(std::string str);

	// Displays message on console err source and errorCode
	// Exits with errorCode....
	// Does not 
	void dieWithError(std::string message, uint32_t errorCode);
}
#endif // __UTILITY_H