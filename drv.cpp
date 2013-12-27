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
 * File:    drv.cpp
 * Created: December 06, 2009
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	FConfigReader* p = FConfigReader::CreateInstance("test.conf");
	if(p && !p->ReadConfig())
	{
		cout << "Trouble" << endl;
		delete p;
		return 1;
	}
	vector<string> v;
	p->GetSectionNames(v);
	cout << "Sections: " << endl;
	for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it)
		cout << "	[" << *it << "]" << endl;
	v.clear();
	v.push_back("key_a");
	v.push_back("key_b");
	v.push_back("key_e");
	cout << "Checking keys for section [fourth]" << endl;
	if(!p->CheckKeys(v, "fourth"))
	{
		cout << "CheckKeys failed." << endl;
		cout << "Not found keys: " << endl;
		for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it)
		{
			cout << "	" << *it << endl;
		}
	} else
		cout << "All keys found." << endl;
	delete p;

	return 0;
}
