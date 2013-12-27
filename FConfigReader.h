/*
 * Copyright (C) 2009-2011 Andrey Filkov
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * File:    FConfigReader.h
 * Created: December 06, 2009
 */
#ifndef _F_CONFIGREADER_H
#define _F_CONFIGREADER_H


#include <string>
#include <map>
#include <iostream>
#include <vector>

typedef std::map < std::string, std::map < std::string, std::string > > MAP_SECTION;

class FConfigReader
{
protected:
	FConfigReader(){}
	FConfigReader(const FConfigReader& orig){}
public:
	static FConfigReader* CreateInstance(const std::string& file, const char com = '#', const char delim = '=', const char open = '[', const char close = ']');
	virtual ~FConfigReader();

	bool ReadConfig();
		// return false if can't open file
	void GetSectionNames(std::vector<std::string>& sect);
	void GetSectionData(std::map<std::string,std::string>& keyVal, const std::string& sect = "");
	bool CheckKeys(std::vector<std::string>& keys, const std::string& sect = "");
		// return true and remove all keys from vector if found all keys under specified section
		// otherwise return false and in vector remain not found keys
protected:
	void Init(const std::string& file, const char com, const char delim, const char open, const char close);
private:
	void GetLine(std::istream& st, std::string& line);
	void TrimSpaces(std::string& buff);

	std::string m_file;
	char m_delim;
	char m_sectOpen;
	char m_sectClose;
	char m_comment;
	MAP_SECTION m_sections;
};

#endif	/* _F_CONFIGREADER_H */
