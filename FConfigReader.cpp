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
 * File:    FConfigReader.cpp
 * Created: December 06, 2009
 */

#include "FConfigReader.h"
#include <fstream>
#include <ios>
#include <iomanip>


FConfigReader::~FConfigReader()
{
}

FConfigReader* FConfigReader::CreateInstance(const std::string& file, const char com, const char delim, const char open, const char close)
{
	FConfigReader* p = new FConfigReader();
	if(p == 0)
		return 0;
	p->Init(file, com, delim, open, close);
	return p;
}

void FConfigReader::Init(const std::string& file, const char com, const char delim, const char open, const char close)
{
	m_file      = file;
	m_delim     = delim;
	m_sectOpen  = open;
	m_sectClose = close;
	m_comment   = com;
}

bool FConfigReader::ReadConfig()
{
	std::ifstream fs(m_file.c_str());
	if(!fs)
		return false;
	std::string line;
	std::string cur_sect("");
	m_sections.clear();
	while(!fs.eof())
	{
		GetLine(fs, line);
		if(!line.length())
			continue;
		if(line[0] == m_comment)
			continue;
		if(line[0] == m_sectOpen && line[line.length() - 1] == m_sectClose)
		{
			line.erase(0, 1);
			line.erase(line.length() - 1);
			TrimSpaces(line);
			cur_sect = line;
			continue;
		}
		std::string::size_type index = line.find(m_delim);
		if(index == std::string::npos)
			continue;
		std::string key = line.substr(0, index);
		TrimSpaces(key);
		if(!key.length() || line.length() == (index + 1))
			continue;
		std::string value = line.substr(index + 1);
		TrimSpaces(value);
		if(!value.length())
			continue;
		m_sections[cur_sect][key] = value;
	}
	fs.close();
	return true;
}

void FConfigReader::GetLine(std::istream& st, std::string& line)
{
	std::string buff;
	line.erase();
	getline(st, buff);
	TrimSpaces(buff);
	if(!buff.length())
		return;
	if(buff[buff.length() - 1] == '\\') // standart de facto
	{
		std::string tmp;
		GetLine(st, tmp);
		buff.erase(buff.length() - 1);
		buff += tmp;
	}
	line = buff;
}

void FConfigReader::TrimSpaces(std::string& buff)
{
	if(!buff.length())
		return;
	std::string::iterator p = buff.begin();
	for(;p != buff.end();)
	{
		if(isspace(*p))
		{
			buff.erase(0, 1);
			p = buff.begin();
			continue;
		}
		break;
	}
	if(!buff.length())
		return;
	std::string::reverse_iterator r = buff.rbegin();
	for(;r != buff.rend();)
	{
		if(isspace(*r))
		{
			buff.erase(buff.length() - 1);
			r = buff.rbegin();
			continue;
		}
		break;
	}
}

void FConfigReader::GetSectionNames(std::vector<std::string>& sect)
{
	sect.clear();
	for(MAP_SECTION::const_iterator mi = m_sections.begin(); mi != m_sections.end(); ++mi)
	{
		sect.push_back(mi->first);
	}
}

void FConfigReader::GetSectionData(std::map<std::string,std::string>& keyVal, const std::string& sect)
{
	keyVal.clear();
	MAP_SECTION::const_iterator mi = m_sections.find(sect);
	if(mi == m_sections.end())
		return;
	keyVal = mi->second;
}

bool FConfigReader::CheckKeys(std::vector<std::string>& keys, const std::string& sect)
{
	MAP_SECTION::const_iterator mi = m_sections.find(sect);
	if(mi == m_sections.end())
		return false;
	std::vector<std::string> tmp;
	for(std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
	{
		if(mi->second.find(*it) == mi->second.end())
			tmp.push_back(*it);
	}
	keys = tmp;
	return !keys.size();
}
