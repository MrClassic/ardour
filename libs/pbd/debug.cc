/*
    Copyright (C) 2009 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <boost/tokenizer.hpp>

#include "pbd/debug.h"

#include "i18n.h"

using namespace std;
static uint64_t _debug_bit = 1;

typedef std::map<const char*,uint64_t> DebugMap;

namespace PBD {
	DebugMap & _debug_bit_map()
	{
		static DebugMap map;
		return map;
	}
}

uint64_t PBD::DEBUG::Stateful = PBD::new_debug_bit ("stateful");
uint64_t PBD::DEBUG::Properties = PBD::new_debug_bit ("properties");
uint64_t PBD::DEBUG::FileManager = PBD::new_debug_bit ("filemanager");
uint64_t PBD::DEBUG::Pool = PBD::new_debug_bit ("pool");
uint64_t PBD::DEBUG::EventLoop = PBD::new_debug_bit ("eventloop");
uint64_t PBD::DEBUG::AbstractUI = PBD::new_debug_bit ("abstractui");
uint64_t PBD::DEBUG::FileUtils = PBD::new_debug_bit ("fileutils");
uint64_t PBD::DEBUG::Configuration = PBD::new_debug_bit ("configuration");

uint64_t PBD::debug_bits = 0x0;

uint64_t
PBD::new_debug_bit (const char* name)
{
        uint64_t ret;
        _debug_bit_map().insert (make_pair (name, _debug_bit));
        ret = _debug_bit;
        _debug_bit <<= 1;
        return ret;
}

void
PBD::debug_print (const char* prefix, string str)
{
	cerr << prefix << ": " << str;
}

void
PBD::set_debug_bits (uint64_t bits)
{
	debug_bits = bits;
}

int
PBD::parse_debug_options (const char* str)
{
	string in_str = str;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep (",");
	tokenizer tokens (in_str, sep);
	uint64_t bits = 0;

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		if (*tok_iter == "list") {
			list_debug_options ();
			return 1;
		}

		if (*tok_iter == "all") {
			PBD::set_debug_bits (~0ULL);
			return 0;
		}

		for (map<const char*,uint64_t>::iterator i = _debug_bit_map().begin(); i != _debug_bit_map().end(); ++i) {
			const char* cstr = (*tok_iter).c_str();

                        if (strncasecmp (cstr, i->first, strlen (cstr)) == 0) {
                                bits |= i->second;
                        }
                }
	}
	
	PBD::set_debug_bits (bits);
	return 0;
}

void
PBD::list_debug_options ()
{
	cout << _("The following debug options are available. Separate multiple options with commas.\nNames are case-insensitive and can be abbreviated.") << endl << endl;
	cout << '\t' << X_("all") << endl; 

	vector<string> options;

	for (map<const char*,uint64_t>::iterator i = _debug_bit_map().begin(); i != _debug_bit_map().end(); ++i) {
		options.push_back (i->first);
        }

	sort (options.begin(), options.end());

	for (vector<string>::iterator i = options.begin(); i != options.end(); ++i) {
                cout << "\t" << (*i) << endl;
	}
}
