/*
This is a distributed file for Transd programming language embedding
library.

Copyright (c) 2020 Albert Berger [alberger at gmail com].
All rights reserved.

Redistribution and use of this file in source and binary forms, 
without modification, are permitted. Any modifications to this file
are explicitly forbidden.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/*
	transd.cpp
	----------
	The minimized distributed source file for C++ binding embeddable
	library of Transd programming language.

	Transd Project website: https://github.com/transd-lang
*/

#ifdef __LINUX__
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <string>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#endif
#include <regex>
#include <climits>
#include <cerrno>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

#include "transd.hpp"

using namespace std;


namespace s4 {
uint32_t s5::s16;

void kexceptInit()
{
	s5::s231();
}

}
using namespace s4;
using s4::s5;


namespace s17 {

time_t s20( const std::wstring& f )
{
	int err;
#ifndef WIN32
	struct stat st;
	err = stat( U8( f ).c_str(), &st );
#else
	struct _stat st;
	err = _wstat( f.c_str(), &st );
#endif
	if( err )
		throw s5( L"cannot get mtime of: " + f, 
		(uint32_t)s5::s6::s12 );
	return st.st_mtime;
}

uint8_t s21( const std::wstring& f )
{
	int err;
#ifndef WIN32
	struct stat st;
	err = stat( U8( f ).c_str(), &st );
#else
	struct _stat st;
	err = _wstat( f.c_str(), &st );
#endif

	if( err )
		throw s5( L"file system object does not exist: " + f,
		(uint32_t)s5::s6::s12 );

	if( st.st_mode & S_IFREG )
		return 1;
	else if( st.st_mode & S_IFDIR )
		return 2;

	return 0;
}

bool s23( const wstring& s385 )
{
	try {
		s21( s385 );
	}
	catch( s5& ) {
		return false;
	}
	return true;
}

bool s22( const wstring& s385 )
{
	try {
		if( s21( s385 ) != 1 )
			throw s5( L"Cannot find data file: " + s385,
			(uint32_t)s5::s6::s12 );
	}
	catch( s5& e ) { // file don't exist
		if( e.which() != (uint32_t)s5::s6::s12 )
			throw;
		return false;
	}
	return true;
}

} // namespace s17

#ifdef __LINUX__

using namespace std;
using namespace s4;
using namespace s43;


namespace s17 {

wstring s24()
{
	char buf[1024];
	readlink( "/proc/self/exe", buf, 1023 );
	return wstring( conv.from_bytes( buf ) );
}

bool s18( const wstring& dir, const wstring& s386, wstring& res )
{
	struct dirent *entry;
	DIR *dp;
	wregex rg( s386 );
	bool ret = false;

	dp = opendir( conv.to_bytes( dir.c_str() ).c_str() );
	if( dp == NULL ) {
		wstring errmsg = conv.from_bytes( strerror( errno ) );
		throw s5( L"cannot open directory: " + dir + L";\nerror: " + errmsg,
				(uint32_t)s5::s6::s11 );
	}

	while( ( entry = readdir( dp ) ) ) {
		if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
			res = dir + L"/" + conv.from_bytes( entry->d_name );
			ret = true;
			break;
		}
	}

	closedir( dp );
	return ret;
}

void s19( const wstring& dir, const wstring& s386, vector<wstring>& files, vector<wstring>& dirs )
{
	struct dirent *entry;
	DIR *dp;
	wregex rg( s386 );

	dp = opendir( conv.to_bytes( dir.c_str() ).c_str() );
	if( dp == NULL ) {
		wstring errmsg = conv.from_bytes( strerror( errno ) );
		throw s5( L"cannot open directory: " + dir + L";\nerror: " + errmsg,
				(uint32_t)s5::s6::s11 );
	}

	while( ( entry = readdir( dp ) ) ) {
		if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
			wstring item = conv.from_bytes( entry->d_name );
			wstring s = dir + L"/" + item;
			uint8_t is = s21( s );
			if( is == 1 )
				files.push_back( item );
			else if( is == 2 )
				dirs.push_back( item );
		}
	}

	closedir( dp );
}


} // namespace s17

#endif // __LINUX__

#ifdef WIN32

using namespace std;

#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")


namespace s17 {

wstring s24()
{
	wchar_t dest[1024];
	DWORD length = GetModuleFileNameW( NULL, dest, 1024 );
	PathRemoveFileSpecW( dest );
	return dest;
}

bool s18( const wstring& _dir, const wstring& s386, wstring& res )
{
	HANDLE hDir;
	WIN32_FIND_DATAW s387;
	wstring s388, s389;
	wregex rg( s386.c_str() );
	bool ret = false;
	wstring dir = _dir;
	if( dir.back() != L'/' && dir.back() != L'\\' )
		dir += L'\\';

	if( ( hDir = FindFirstFileW( ( dir + L"*" ).c_str(), &s387 ) ) == INVALID_HANDLE_VALUE )
		throw runtime_error( "no such directory" );

	while( FindNextFileW( hDir, &s387 ) ) {
		s388 = s387.cFileName;
		s389 = dir + s388;
		if( regex_match( s388, rg ) ) {
			res = s389;
			ret = true;
			break;
		}
	}
	return ret;
}

void s19( const wstring& _dir, const wstring& s386, vector<wstring>& files, vector<wstring>& dirs )
{
	HANDLE hDir;
	WIN32_FIND_DATAW s387;
	wstring s388, s389;
	wregex rg( s386.c_str() );
	wstring dir = _dir;
	if( dir.back() != L'/' && dir.back() != L'\\' )
		dir += L'\\';

	if( ( hDir = FindFirstFileW( ( dir + L"*" ).c_str(), &s387 ) ) == INVALID_HANDLE_VALUE )
		throw runtime_error( "no such directory" );

	while( FindNextFileW( hDir, &s387 ) ) {
		s388 = s387.cFileName;
		s389 = dir + s388;
		if( regex_match( s388, rg ) ) {
			uint8_t is = s21( s389 );
			if( is == 1 )
				files.push_back( s388 );
			else if( is == 2 )
				dirs.push_back( s388 );
		}
	}
}

} // namespace s17

#endif // WIN32

namespace s25 
{

wstring s26 = L"\n\r\t ";
string s27 = "\n\r\t ";
wstring s28 = L"";


void s32( const wstring& s, size_t s390, wchar_t left, wchar_t right,
	size_t& start, size_t& end )
{
	end = string::npos;
	start = s.find( left, s390 );
	if( start == string::npos || start == s.size() - 1 )
		return;
	int balance = 1;
	for( size_t n = start + 1; n < s.size(); ++n ) {
		if( s[n] == left ) {
			++balance;
			continue;
		}
		if( s[n] == right )
			--balance;
		if( balance == 0 ) {
			end = n;
			return;
		}
	}
}


void s33( const wstring& s, size_t s390, wchar_t c, size_t& start, size_t& end )
{
	end = string::npos;
	start = s.find( c, s390 );
	if( start == string::npos || start == s.size() - 1 )
		return;
	for( size_t n = start + 1; n < s.size(); ++n ) {
		if( s[n] == c && s[n - 1] != '\\' ) {
			end = n;
			return;
		}
	}
}

int s34( const wstring& sf, wchar_t s391, size_t& pos )
{
	size_t s392 = sf.find( s391, pos );
	if( s392 == wstring::npos )
		throw invalid_argument( "separator not found" );
	wstring s = s30( sf.substr( pos, s392 - pos ), L" " );
	int ret = stoi( s );
	pos = sf.find_first_not_of( s26 + s391, s392 );
	return ret;
}


bool s40( const wchar_t *str, long *val, wchar_t **end /*= NULL*/ )
{
	wchar_t *temp;
	bool ret = true;
	errno = 0;
	*val = std::wcstol( str, &temp, 0 );

	if( temp == str || ( !end && *temp != '\0' ) ||
		( ( *val == LONG_MIN || *val == LONG_MAX ) && errno == ERANGE ) )
		ret = false;

	if( end )
		*end = temp;
	return ret;
}

bool s41( const wchar_t *str, double *val, wchar_t **end /*= NULL*/ )
{
	wchar_t *temp;
	bool ret = true;
	errno = 0;
	*val = std::wcstod( str, &temp );

	if( temp == str || ( !end && *temp != '\0' ) ||
		( ( *val == HUGE_VAL || *val == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
		ret = false;

	if( end )
		*end = temp;
	return ret;
}

void s35( const wstring& s, const wstring& s391, vector<wstring>& res )
{
	size_t s398 = 0, enPos = 0;
	while( enPos != wstring::npos ) {
		enPos = s.find( s391, s398 );
		wstring seg = s30( s.substr( s398, enPos - s398 ), s26 );
		s398 = enPos + s391.size();
		res.push_back( seg );
	}
}

wstring s461( const wstring& sf, size_t& pos )
{
	size_t pl = sf.find( L'\n', pos );
	wstring line = s30( sf.substr( pos, pl - pos ), s26 );
	pos = pl == string::npos ? pl : pl + 1;
	return line;
}

void s36( const wstring& sf, const wstring& s391, 
		pair<wstring, wstring>& pr, size_t& pos )
{
	size_t pl = sf.find( L'\n', pos );
	wstring line = s30( sf.substr( pos, pl - pos ), s26 );
	pos = pl == string::npos ? pl : pl + 1;
	pl = line.find( s391 );
	if( pl == string::npos ) 
		throw s4::s5( L"invalid pair syntax: " + line );

	wstring nam = s30( line.substr( 0, pl ), s26 );
	wstring val = s30( line.substr( pl + s391.size() ), s26 );
	pr.first = nam;
	pr.second = val;
}

void s37( const wstring& sf, const wstring& s391, vector<pair<wstring, wstring>>& v )
{
	vector<wstring> s393;
	s35( s30( sf, s26 ), L"\n", s393 );
	for( size_t n = 0; n < s393.size(); ++n ) {
		size_t pl = s393[n].find( s391 );
		wstring nam = s30( s393[n].substr( 0, pl ), s26 );
		wstring val = s30( s393[n].substr( pl + s391.size() ), s26 );
		v.push_back( make_pair( nam, val ) );
	}
}

wstring s29( const std::wstring& l, const std::wstring& s, const std::wstring& r )
{
	size_t pl = s.find_first_not_of( l );
	if( pl == wstring::npos )
		return L"";
	wstring ret = s.substr( pl );
	return ret.substr( 0, ret.find_last_not_of( r ) + 1 );
}

wstring s30( const std::wstring& s, const std::wstring& c )
{
	size_t pl = s.find_first_not_of( c );
	if( pl == wstring::npos )
		return L"";
	wstring ret = s.substr( pl );
	return ret.substr( 0, ret.find_last_not_of( c ) + 1 );
}


wstring s38( const wstring& sf )
{
	if( sf[0] != L'{' )
		return sf;

	size_t s405, s406;
	s32( sf, 0, L'{', L'}', s405, s406 );
	wstring block = sf.substr( s405 + 1, s406 - s405 - 1 );
	vector<wstring> parts;
	s35( s30( block, L" " ), L"|", parts );
#ifdef WIN32	
	return parts[0] + sf.substr( s406 + 1 );
#else
	return parts[1] + sf.substr( s406 + 1 );
#endif	
}

bool s31( const std::wstring& s, const std::wstring& ss )
{
	if( s.substr( s.size() - ss.size() ) == ss )
		return true;
	return false;
}

void s39( wstring& dir )
{
#ifdef WIN32
	if( dir[dir.size() - 1] != L'/' &&
		dir[dir.size() - 1] != L'\\' )
		dir += L"\\";
#else
	if( dir[dir.size() - 1] != L'/' )
		dir += L"/";
#endif
}

void s42( const std::wstring& msg )
{

}


void s32( const string& s, size_t s390, char left, char right,
	size_t& start, size_t& end )
{
	end = string::npos;
	start = s.find( left, s390 );
	if( start == string::npos || start == s.size() - 1 )
		return;
	int balance = 1;
	for( size_t n = start + 1; n < s.size(); ++n ) {
		if( s[n] == left ) {
			++balance;
			continue;
		}
		if( s[n] == right )
			--balance;
		if( balance == 0 ) {
			end = n;
			return;
		}
	}
}

int s34( const string& sf, char s391, size_t& pos )
{
	size_t s392 = sf.find( s391, pos );
	if( s392 == string::npos )
		throw invalid_argument( "separator not found" );
	string s = s30( sf.substr( pos, s392 - pos ), " " );
	int ret = stoi( s );
	pos = sf.find_first_not_of( s27 + s391, s392 );
	return ret;
}

void s35( const string& s, const string& s391, vector<string>& res )
{
	size_t s398 = 0, enPos = 0;
	while( enPos != string::npos ) {
		enPos = s.find( s391, s398 );
		string seg = s30( s.substr( s398, enPos - s398 ), s27 );
		s398 = enPos + s391.size();
		res.push_back( seg );
	}
}

void s37( const string& sf, vector<pair<string, string>>& v )
{
	vector<string> s393;
	s35( s30( sf, s27 ), "\n", s393 );
	for( size_t n = 0; n < s393.size(); ++n ) {
		size_t pl = s393[n].find( ':' );
		string nam = s30( s393[n].substr( 0, pl ), s27 );
		string val = s30( s393[n].substr( pl + 1 ), s27 );
		v.push_back( make_pair( nam, val ) );
	}
}

string s29( const std::string& l, const std::string& s, const std::string& r )
{
	size_t pl = s.find_first_not_of( l );
	if( pl == string::npos )
		return "";
	string ret = s.substr( pl );
	return ret.substr( 0, ret.find_last_not_of( r ) + 1 );
}

string s30( const std::string& s, const std::string& c )
{
	size_t pl = s.find_first_not_of( c );
	if( pl == string::npos )
		return "";
	string ret = s.substr( pl );
	return ret.substr( 0, ret.find_last_not_of( c ) + 1 );
}


string s38( const string& sf )
{
	if( sf[0] != '{' )
		return sf;

	size_t s405, s406;
	s32( sf, 0, '{', '}', s405, s406 );
	string block = sf.substr( s405 + 1, s406 - s405 - 1 );
	vector<string> parts;
	s35( s30( block, " " ), "|", parts );
#ifdef WIN32	
	return parts[0] + sf.substr( s406 + 1 );
#else
	return parts[1] + sf.substr( s406 + 1 );
#endif	
}

}//namespace s25


namespace s43 {
std::locale locloc;
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
}

using namespace s25;
using namespace s43;
using namespace s1;


namespace s44
{
wstring numChars = L"-.0123456789";
wstring rightBound = L" ,]}\t\r\n";
wstring quotes = L"\"/`'";

void s81( const wstring& sf, size_t& pos, s3<s57> ob )
{
	size_t s405, s406;
	s32( sf, pos, L'{', L'}', s405, s406 );
	if( s405 == string::npos )
		return;
	wstring sob = sf.substr( s405, s406 - s405 + 1 );
	pos = s406 + 1;
	ob->s65( sob );
}

void s395( wstring& sf )
{
	wregex rgCmnt(
		LR"regex(\n\r?\/\/.*?\n\r?)regex"
	);
	wsmatch sm;
	wstring::const_iterator itst = sf.begin();
	wstring::const_iterator iten = sf.end();
	while( std::regex_search( itst, iten, sm, rgCmnt ) ) {
		sf.erase( sm.position(), sm.length() - 
			(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
		itst = sf.begin();
		iten = sf.end();
	}
}

void
s80( const wstring& s394, vector<s3<s57>>& res, const wstring& sheb )
{
	std::ifstream fs( TOFS( s394 ));
	if( !fs.good() )
		throw runtime_error( "Reading nqj file failed: " + U8( s394 ));
	string sfA( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
	wstring sf = conv.from_bytes( sfA );
	s395( sf );
	size_t pos = 0;
	if( sheb.size() ) {
		sf.find( sheb );
		if( pos == string::npos )
			throw s5( sheb + L" directive not found in the source file." );
		pos += sheb.size() + 1;
		if( sf.size() > 13 && sf[14] == '\r' )
			++pos;
	}
	size_t startPos = pos;
	wstring s170;
	bool s396 = false;
	while( ( pos = sf.find( L'{', pos ) ) != string::npos ) {
		size_t pl = sf.rfind( '}', pos );
		size_t subl = pos - pl - 1;
		if( string::npos == pl ) {
			pl = startPos; subl = pos - startPos;
		}
		else
			pl += 1;

		wstring s1 = s30( sf.substr( pl, /*pos - pl - 1*/subl ), s26 );
		if( s1.size() ) {
			if( s1[s1.size()-1] != L':' )
				throw s5( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
				(uint32_t)s5::s6::s9 );
			if( s1.size() == 1 )
				s396 = true;
			else
				s170 = s30( s1, s26 + L":" );
		}
		if( s170.empty() ) {
			size_t pl1 = sf.rfind( '\n', pl );
			if( pl1 < pl - 1 ) {
				wstring s1 = s30( sf.substr( pl1, pl ), s26 );
				if( s1.size() ) {
					if( ( !s396 && s1[s1.size() - 1] != L':' ) ||
						( s396 && s1[s1.size() - 1] == L':' ) ||
						(!s396 && s1.size() == 1 ) )
						throw s5( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
						(uint32_t)s5::s6::s9 );
					s170 = s30( s1, s26 + L":" );
				}
			}
		}
		if( quotes.find( s170[0] ) != string::npos ) {
			if( s170[0] != s170[s170.size()-1] )
				throw s5( L"Malformed block name: " + s170.substr( 0, 20 ) + L"...",
						(uint32_t)s5::s6::s9 );
		}
		else {
			if(	iswdigit( s170[0] ) )
				throw s5( L"wrong unquoted syntax: " + s170.substr( 0, 20 ) + L"...",
				(uint32_t)s5::s6::s9 );


		}
		s3<s57> ob = new s57;
		s81( sf, pos, ob );
		if( s170.size() )
			ob->s70( L"name", new s55( s170 ) );
		s170 = L"";
		s396 = false;
		res.push_back( ob );
	}
}

void s82( const wstring& s397, const vector<s1::s3<s57>>& objs )
{
	std::ofstream fs( TOFS( s397 ), ios::out | ios::trunc | ios::binary );
	if( !fs.good() )
		throw runtime_error( "Reading state file failed: " + U8( s397 ) );
	for( auto ob : objs ) {
		basic_stringstream<wchar_t> ss;
		ob->s66( &ss );
		string s = U8( ss.str() );
		s += "\n\n";
		fs.write( s.c_str(), s.size() );
	}
}


void s83( const wstring& sf, size_t& pos, wchar_t quote, wstring& res )
{
	size_t s405, s406;
	s33( sf, pos, quote, s405, s406 );
	if( s406 != string::npos ) {
		pos = s406 + 1;
		res = s30( sf.substr( s405+1, s406 - s405 - 1 ), s26 ); 
	}
	else
		pos = string::npos;
}

void s84( wostream* pd, const wstring& s )
{
	wchar_t q = L'\"';
	if( quotes.find( s[0] ) != string::npos )
		q = s[0];
	size_t start = 1;
	*pd << q;
	if( s[0] != q ) 
		start = 0;

	for( size_t n = start; n < s.size(); ++n ) {
		if( s[n] == q && s[n-1] != L'\\' && n != s.size() - 1 )
			*pd << L'\\';
		*pd << s[n];
	}

	if( s[s.size()-1] != q )
		*pd << q;
}

void s85( const wstring& sf, size_t& pos, wstring& res )
{
	if( !std::isgraph<wchar_t>( sf[pos], locloc ) ||
			sf[pos] == L':' || sf[pos] == L',' )
		throw s5( L"unrecognized unquoted syntax: " + sf.substr(pos, 20), 
				(uint32_t)s5::s6::s9 );
	size_t tokEnd = pos + 1;
	while( std::isgraph<wchar_t>( sf[tokEnd], locloc ) &&
			sf[tokEnd] != L':' && sf[tokEnd] != L',' )
		++tokEnd;
	res = s30( sf.substr( pos, tokEnd - pos ), s26 );
	pos = tokEnd;
}

void s86( const wstring& sf, size_t& pos, wstring& res )
{
	size_t s405, s406;
	s32( sf, pos, L'(', L')', s405, s406 );
	if( s406 == string::npos )
		throw s5( L"unmatched unquoted parentheses: " + sf.substr(pos, 20), 
			(uint32_t)s5::s6::s9 );
	if( s406 == sf.size() - 1 )
		throw s5( L"wrong unquoted parentheses syntax: " + sf.substr(pos, 20), 
			(uint32_t)s5::s6::s9 );
	size_t pl = sf.find_first_not_of( s26, s406+1 );
	if( pl == string::npos && sf[pl] != L',' && sf[pl] != L'}' )
		throw s5( L"wrong unquoted parentheses syntax: " + sf.substr(pos, 20), 
			(uint32_t)s5::s6::s9 );
	pos = s406 + 1;
}

void s87( const wstring& sf, size_t& pos, wstring& res )
{
	if( !std::isgraph<wchar_t>( sf[pos], locloc ) ||
		sf[pos] == L':' || sf[pos] == L',' )
		throw s5( L"unrecognized unquoted syntax: " + sf.substr( pos, 20 ),
		(uint32_t)s5::s6::s9 );
	size_t tokEnd = pos;
	if( sf[pos] == L'(' )
		s86( sf, tokEnd, res );
	else {
		tokEnd = pos + 1;

		while( std::isgraph<wchar_t>( sf[tokEnd], locloc ) &&
			sf[tokEnd] != L':' && sf[tokEnd] != L',' ) {
			if( sf[tokEnd] == L'(' ) {
				s86( sf, tokEnd, res );
				break;
			}
			++tokEnd;
		}
	}
	res = s30( sf.substr( pos, tokEnd - pos ), s26 );
	pos = tokEnd;
}

void s88( wostream* pd, const wstring& s )
{
	if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
			s[s.size()-1] == L'"' )
		throw s5( L"wrong unquoted syntax: " + s.substr(0, 20),
				(uint32_t)s5::s6::s9 );

	for( size_t n = 0; n < s.size(); ++n ) 
		if( !std::isgraph<wchar_t>( s[n], locloc ) )
			throw s5( L"wrong unquoted syntax: " + s.substr(0, 20),
				(uint32_t)s5::s6::s9 );

	*pd << s;
}

void s89( const wstring& sf, size_t& pos, vector<s3<s55>>& res )
{
	size_t s405, s406, s398 = 0;
	s32( sf, pos, L'[', L']', s405, s406 );
	pos = s406 + 1;
	wstring ar = s30( sf.substr( s405 + 1, s406 - s405 - 1 ), s26 );
	while( true ) {
		res.push_back( s3<s55>(new s55( ar, s398 ) ) );
		s398 = ar.find( /*' '*/',', s398 );
		if( s398 == string::npos )
			break;
		++s398;
	}
}

void s90( wostream* pd, const vector<s3<s55>>& v, bool strict=false )
{
	*pd << L'[';
	for( size_t n = 0; n < v.size(); ++n ) {
		v[n]->s66( pd, strict );
		if( n != v.size() - 1 )
			*pd << L',';
	}
	*pd << L']';
}

void s91( const wstring& sf, size_t& pos, wstring& res )
{
	size_t pl = sf.find_first_not_of( L", \n\r\t", pos );
	if( quotes.find( sf[pl] ) != string::npos ) 
		s83( sf, pos, sf[pl], res );
	else {

		if( !std::isgraph<wchar_t>( sf[pos], locloc ) ||
			sf[pos] == L':' || sf[pos] == L',' )
			throw s5( L"unrecognized name syntax: " + sf.substr( pos, 20 ) +
				L"...",	(uint32_t)s5::s6::s9 );
		size_t tokEnd = pos + 1;

		while( sf[tokEnd] != L':' && sf[tokEnd] != L',' ) {
			if( !std::isalnum<wchar_t>( sf[tokEnd], locloc ) &&
				!std::isspace<wchar_t>( sf[tokEnd], locloc ) && sf[tokEnd] != L'_' )
				throw s5( L"unrecognized name syntax: " + sf.substr( pos, 20 ) +
					L"...",	(uint32_t)s5::s6::s9 );
			++tokEnd;
		}
		res = s30( sf.substr( pos, tokEnd - pos ), s26 );
		pos = tokEnd;
	}
}

void s92( wostream* pd, const wstring& s, bool strict=false )
{
	bool space = false;
	for( size_t n = 0; n < s.size(); ++n )
		if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
			space = true;
			break;
		}

	if( !space && !strict && quotes.find( s[0] ) == string::npos )
		s88( pd, s );
	else
		s84( pd, s );
}

s45 s93( const wstring& sf, size_t& pos, double& res )
{
	s45 ret = s54;
	size_t pl = sf.find_first_not_of( L"-0123456789.", pos );
	size_t pl1 = sf.find( L"." );
	if( pl1 < pl )
		ret = s50;
	if( pl == string::npos )
		res = stod( sf.substr( pos ) );
	else
		res = stod( sf.substr( pos, pl - pos ) );
	pos = pl;
	return ret;
}

bool s94( const wstring& sf, size_t& pos, bool& res )
{
	size_t pl = 0;
	if( sf.find( L"true", pos, 4 ) == pos )
		pl = 4;
	else if( sf.find( L"false", pos, 5 ) == pos )
		pl = 5;
	if( pl ) {
		if( rightBound.find( sf[pos+pl] ) != string::npos ) {
			pos += pl;
			res = (pl == 4);
			return true;
		}
	}
	return false;
}

bool s95( const wstring& sf, size_t& pos )
{
	if( sf.find( L"null", pos, 4 ) == pos ) {
		if( rightBound.find( sf[pos+4] ) != string::npos ) {
			pos += 4;
			return true;
		}
	}
	return false;
}

s55::s55( const wstring& sf, size_t& pos )
	: var( s46 )
{
	size_t s398 = sf.find_first_not_of( L" \n\r\t", pos );
	if( sf[s398] == L'{' ) {
		size_t s405, s406;
		s32( sf, s398, L'{', L'}', s405, s406 );
		pos = s406+1;
		obj.s65( s30( sf.substr( s405 + 1, s406 - s405 - 1 ), s26 ) );
		var = s47;
	}
	else {
		pos = s398;
		if ( quotes.find( sf[pos] ) != string::npos ) {
			s83( sf, pos, sf[pos], str );
			var = s53;
		}
		else if ( sf[pos] == L'[' ) {
			s89( sf, pos, s73 ); 
			var = s49;
		}
		else if ( numChars.find( sf[pos] ) != string::npos ) {
			var = s93( sf, pos, s74 );

		}
		else {
			if( s94( sf, pos, b ) )
				var = s51;
			else if( s95( sf, pos ) )
				var = s52;
			else {
				s87( sf, pos, str );
				var = s48;
			}
		}
	}
}

void s57::s65( const wstring& sf )
{

	s58.clear();
	size_t s398;
	size_t pl = sf.find_first_not_of( L" \n\r\t" );
	if( pl == string::npos )
		return;
	if( sf[pl] == L'{' )
		s398 = sf.find_first_not_of( L" \n\r\t", pl + 1 );
	else
		s398 = pl;
	while( true ) {
		wstring nam;
		s91( sf, s398, nam );
		size_t pl = sf.find_first_not_of( L" \n\r\t", s398 );
		if( pl == string::npos || sf[pl] != L':' )
			throw s5( L"unrecognized nqj syntax: " + sf.substr(s398, 50), 
					(uint32_t)s5::s6::s9 );
		s398 = pl + 1;

		s58.insert( make_pair( nam, new s55( sf, s398 ) ) );
		pl = sf.find_first_not_of( L" \n\r\t", s398 );
		if( pl != string::npos && rightBound.find( sf[pl] ) == string::npos ) 
			throw s5( L"wrong nqj syntax: missed separator or closing brace: " + sf.substr(s398, 50), 
					(uint32_t)s5::s6::s9 );
		if( pl != string::npos )
			pl = sf.find_first_not_of( L" \n\r\t", pl+1 );
		if( pl == string::npos )
			break;
		s398 = pl;
	}
}

bool s57::operator==( const s57& r )  const
{
	bool ret = true;
	for( auto it = s58.begin(); it != s58.end(); ++it ) {
		auto it1 = r.s58.find( it->first );
		if( it1 == r.s58.end() || !( *( it->second ) == *( it->second ) ) ) {
			ret = false;
			break;
		}
	}
	return ret;
}

void s57::s66( wostream* pd, bool strict ) const
{
	*pd << L"{\n";
	for( auto it = s58.begin(); it != s58.end(); ++it ) {
		if( it != s58.begin() )
			*pd << L",\n";
		s92( pd, it->first, strict );
		*pd << L" : ";
		it->second->s66( pd );
	}
	*pd << L"\n}";
}

void s55::s66( wostream* pd, bool strict ) const
{
	if( var == s47 )
		obj.s66( pd, strict );
	else if( var == s49 )
		s90( pd, s73, strict );
	else if( var == s48 )
		s92( pd, str, strict );
	else if( var == s53 )
		s92( pd, str, true );
	else if( var == s50 )
		*pd << to_wstring( s74 );
	else if( var == s51 )
		*pd << (b ? L"true" : L"false");
	else if( var == s52 )
		*pd << L"null" << endl;
}

bool s57::s67( const wstring& key ) const
{
	if( s58.find( key ) != s58.end() )
		return true;
	return false;
}

void s57::s68( const wstring& key, vector<s3<s55>>& res ) const
{
	auto i = s58.equal_range( key );
	if( i.first == i.second )
		return;
	for( auto it = i.first; it != i.second; ++it )
		res.push_back( it->second );
}

const s56 s57::s69( const wstring& key ) const
{
	if( s58.count( key ) > 1 )
		throw s5( L"multiple values: " + key, (uint32_t)s63 );

	auto ret = s58.find( key );
	return ret->second;
}

void s57::s70( const std::wstring& nam, s56 val, s59 ap )
{
	if( s58.find( nam ) != s58.end() ) {
		if( ap == s60 )
			throw s5( L"Field already exists: " + nam, (uint32_t)s5::s6::s10 );
		else if( ap == s62 )
			return;
		else if( ap == s61 )
			s58.erase( nam );
	}
	s58.insert( make_pair( nam, val ) );
}

void s57::s71( vector<pair<wstring, s3<s55>>>& res ) const
{
	for( auto it = s58.begin(); it != s58.end(); ++it ) 
		res.push_back( *it );
}

void s57::s72( wostream* pd, int ind ) const
{
	for( auto it = s58.begin(); it != s58.end(); ++it ) {
		*pd << FILL(ind) << it->first << " : " << endl;
		it->second->s72( pd, ind + 2 );
	}
}

void s55::s72( wostream* pd, int ind ) const
{
	if( var == s47 )
		obj.s72( pd, ind+2 );
	else if( var == s49 ) {
		for( size_t n = 0; n < s73.size(); ++n ) {
			s73[n]->s72( pd, ind );
			if( n < s73.size() - 1 )
				*pd << endl;
		}
	}
	else if( var == s48 )
		*pd << FILL(ind) << str << endl;
	else if( var == s50 )
		*pd << FILL(ind) << s74 << endl;
	else if( var == s51 )
		*pd << FILL(ind) << b << endl;
	else if( var == s52 )
		*pd << FILL(ind) << L"null" << endl;
}

bool operator==( const std::vector<s3<s55>>& l,
	const std::vector<s3<s55>>& r )
{
	if( l.size() == r.size() ) {
		for( size_t n = 0; n < l.size(); ++n )
			if( !(*( l[n] ) == *( r[n] ) ) )
				return false;
		return true;
	}
	return false;
}

} // namespace s44

using namespace s44;


namespace transd {
namespace s96 {

DEFCONST s97 = L"typeMembers";
DEFCONST s98 = L"typeMember";
DEFCONST s99 = L"typeMethods";
DEFCONST s100 = L"typeMethod";
DEFCONST s101 = L"members";
DEFCONST s102 = L"member";
DEFCONST s103 = L"methods";
DEFCONST s104 = L"method";
DEFCONST s105 = L"init";
DEFCONST s106 = L"initCall";
DEFCONST s107 = L"thisPtr";
DEFCONST s108 = L"virtual";
DEFCONST s109 = L"override";


DEFCONST s110 = L"import";
DEFCONST s111 = L"input";
DEFCONST s112 = L"output";
DEFCONST s113 = L"export";
DEFCONST s114 = L"opaque";


DEFCONST s457 = L"public";
DEFCONST s458 = L"private";
DEFCONST s459 = L"secure";


DEFCONST s115 = L"class";
DEFCONST s116 = L"module";


DEFCONST s117 = L"AssemblyDescription";
DEFCONST s118 = L"ProgramText";
DEFCONST s119 = L"Export";


DEFCONST s124 = L"source";
DEFCONST s120 = L"objectType";
DEFCONST s121 = L"moduleType";
DEFCONST s122 = L"name";
DEFCONST s123 = L"entryPoint";
DEFCONST s125 = L"perm";
DEFCONST s127 = L"extends";

DEFCONST s452 = L"#lang transd";

} // namespace s96
std::wstring s133[] = { L"value", L"function", L"object", L"name" };

const wstring s134 = L"if";
const wstring s135 = L"set";
const wstring s136 = L"sum";
const wstring s137 = L"with";
const wstring s138 = L"mul";
const wstring s139 = L"div";
const wstring s140 = L"dif";
const wstring s141 = L"eq";
const wstring s142 = L"less";
const wstring s143 = L"greater";
const wstring s144 = L"leq";
const wstring s145 = L"geq";
const wstring s146 = L"neq";
const wstring s147 = L"and";
const wstring s148 = L"or";
const wstring s149 = L"dcmp";
const wstring s150 = L"dcmpr";
const wstring s151 = L"mod";
const wstring s152 = L"sqrt";
const wstring s153 = L"abs";
const wstring s154 = L"pow";
const wstring s155 = L"textout";
const wstring s156 = L"lambda";
const wstring s157 = L"proc";
const wstring s158 = L"while";
const wstring s159 = L"eval";


s161::s161( const std::wstring& s )
{
	size_t pos = 0;
	if( s[pos] == L'(' )
		s174( s );
	else if( iswalpha( s[pos] ) || s[pos] == L'_' ) {
		if( s.find( L'(' ) != string::npos )
			s176( s );
		else
			s177( s );
	}
	else if( s[pos] == L'"' || iswdigit( s[pos] ) || s[pos] == L'\'' ||
					 s[pos] == L'-'	) {
		wstring sf;

			sf = s30( s, s26 );

		s176( sf );
	}
	else
		throw s5( L"Unknown string content: " + s );
}

s161::s161( const std::wstring& s296, const s44::s55& s188 )
	: s170( s296 )
{
	if( s188.Var() == s48 ) {
		wstring s = s188.s79();
		size_t pos = 0;
		if( s[pos] == L'(' )
			s174( s );
		else if( iswalpha( s[pos] ) )
			s176( s );
		else
			throw s5( L"Unknown string content: " + s );
	}
	else if( s188.Var() == s53 ) {
		wstring s = L"\"" + 
			s188.s79() + 
			L"\"";
		s176( s );
	}
	else if( s188.Var() == s47 )
		s175( s188.s76() );
	else if( s188.Var() == s50 )
		s176( to_wstring( s188.s78() ) );
	else if( s188.Var() == s54 )
		s176( to_wstring( s188.s34() ) );
	else if( s188.Var() == s49 ) {
		basic_stringstream<wchar_t> ss;
		s188.s66( &ss );
		s176( ss.str() );
	}
	else
		throw s5( L"Unhandled nqj variant: " + to_wstring( s188.Var() ) );
}

s161::s161( const s44::s57& s47 )
{
	s175( s47 );
}

void s161::s174( const std::wstring& sf )
{
	size_t pos = 0;
	vector<wstring> tokens;
	s180( sf, pos, tokens );
	if( tokens.empty() )
		return;
	s171 = s130;
	size_t s398 = 0;
	s172 = s179( tokens[0], s398 );

	for( size_t n = 1; n < tokens.size(); n++ )
		s173.insert( make_pair( to_wstring( n - 1 ), new s161( tokens[n] ) ) );
}

void s161::s176( const std::wstring& sf )
{
	s171 = s129;
	s172 = sf;
}

void s161::s177( const std::wstring& sf )
{
	s171 = s132;
	s172 = sf;
}

void s161::s175( const s44::s57& s47 )
{
	s170 = s194( s47, s96::s122 );
	s171 = s131;
	vector<pair<wstring, s56>> s58;
	s47.s71( s58 );
	for( size_t n = 0; n < s58.size(); ++n ) {
		if( s58[n].first != s96::s122 )
			s178( s58[n].first, *s58[n].second );
	}
}

void s399( wstring& s )
{
	wregex rgBr(
		LR"regex(\s(\s+))regex"
	);
	wsmatch sm;
	wstring::const_iterator itst = s.begin();
	wstring::const_iterator iten = s.end();
	while( std::regex_search( itst, iten, sm, rgBr ) ) {
		s.erase( sm.position( 1 ), sm.length( 1 ) );
		itst = s.begin();
		iten = s.end();
	}
}

void s161::s181( s44::s57& obj )
{
	wstring s506 = s25::s30( s194( obj, s96::s122/*,
																to_wstring( ++namecnt )*/ ), s26 );
	wstring s400 = s506;
	s399( s400 );
	if( s400.empty() )
		throw s5( L"Nameless blocks are forbidden." );

	if( s400 != s506 )
		obj.s70( s96::s122, s55( s400 ), s57::s61 );

	if( s400 == s170 ) { // partial definition
		vector<pair<wstring, s56>> s58;
		obj.s71( s58 );
		for( size_t n = 0; n < s58.size(); ++n )
			s178( s58[n].first, *s58[n].second );
	}
	else {

		s173.insert( make_pair( s400, new s161( obj ) ) );

	}
}

void s161::s178( const std::wstring& s170, const s55& val )
{
	s173.insert( make_pair( s170, new s161( s170, val ) ) );
}

void s161::s182( s160* s192, size_t s193 /*= 0*/ )
{
	s167::const_iterator it = s173.begin();
	for( ; it != s173.end(); ++it ) {
		if( it->second->s189() == s131 ) {
			if( s193 == 0 ) {
				it->second->s182( s192, 1 );
			}
			else {

			}
		}
	}
}

const s161& s161::s184( const std::wstring& s170 ) const
{
	int cnt = s173.count( s170 );
	if( cnt > 1 )
		throw s5( L"multiple values: " + s170, (uint32_t)s63 );
	if( cnt == 1 ) {
		auto ret = s173.find( s170 );
		return *ret->second;
	}
	throw s5( L"node not found: " + s170, (uint32_t)s5::s6::s12 );
	s167::const_iterator it = s173.begin();
	for( ; it != s173.end(); ++it ) {
		try {
			const s161& ret = it->second->s184( s170 );
			return ret;
		}
		catch( s5& e ) {
			if( e.which() == (uint32_t)s5::s6::s12 )
				continue;
			throw e;
		}
	}

	throw s5( L"node not found: " + s170, (uint32_t)s5::s6::s12 );
}

void s161::s180( const wstring& sf, size_t& pos, vector<wstring>& res )
{
	size_t s405, s406;
	s32( sf, pos, L'(', L')', s405, s406 );
	if( s405 != pos || s406 == string::npos )
		throw s5( L"Parentheses don't match near \"" + sf.substr( 0, 40 ) + L"...\"" );
	pos = s406;

	size_t s398 = sf.find_first_not_of( s26, s405 + 1 );
	if( sf[s398] == L')' )
		return;
	size_t s401 = s398;
	wstring s402;
	while( s401 < s406 ) {
		s398 = sf.find_first_not_of( s26 + L")", s401 );
		if( s398 >= s406 )
			break;

		size_t s403, s404;

		if( sf[s398] == L'(' ) {
			s32( sf, s398, L'(', L')', s403, s404 );
			if( s404 == s406 )
				throw s5( L"Parentheses don't match near \'" + sf.substr( s398, 40 ) + L"...\'" );
			s402 = sf.substr( s398, s404 - s398 + 1 );
			s401 = s404 + 1;
		}
		else if( sf[s398] == L'"' ) {
			s33( sf, s398, L'"',
				s403, s404 );
			if( s404 == string::npos )
				throw s5( L"Quotes don't match near \'" + sf.substr( s398, 40 ) + L"...\'" );
			s402 = sf.substr( s398, s404 - s398 + 1 );
			s401 = s404 + 1;
		}
		else if( iswdigit( sf[s398] ) ) {
			s404 = sf.find_first_of( s26 + L")", s398 );
			s402 = sf.substr( s398, s404 - s398 );
			s401 = s404;
		}
		else if( iswalpha( sf[s398] ) || sf[s398] == L'_' ) {
			s404 = sf.find_first_of( s26 + L")", s398 );
			size_t pl = sf.find( L'(', s398 );
			if( pl < s404 ) {
				s32( sf, pl, L'(', L')', s403, s404 );
				if( s404 == s406 )
					throw s5( L"Parentheses don't match near \'" + sf.substr( s398, 40 ) + L"...\'" );
				s402 = sf.substr( s398, s404 - s398 + 1 );
				s401 = s404 + 1;
			}
			else {
				s402 = sf.substr( s398, s404 - s398 );
				s401 = s404;
			}
		}
		else {
			s404 = sf.find_first_of( s26 + L")", s398 );
			s402 = sf.substr( s398, s404 - s398 );
			s401 = s404;
		}

		res.push_back( s402 );
	}
}

wstring s161::s179( const std::wstring& sf, size_t &pos )
{
	wstring ret;
	if( sf[pos] == L'+' && sf[pos + 1] != L'=' )
		ret = s136;
	else if( sf[pos] == L'-' && sf[pos + 1] != L'=' )
		ret = s140;
	else if( sf[pos] == L'*' && sf[pos + 1] != L'=' )
		ret = s138;
	else if( sf[pos] == L'/' && sf[pos + 1] != L'=' )
		ret = s139;
	else if( sf[pos] == L'^' && sf[pos + 1] != L'=' )
		ret = s154;
	else if( sf[pos] == L'=' && sf[pos + 1] != L'=' )
		ret = s135;
	else if( sf[pos] == L'<' && sf[pos + 1] != L'=' )
		ret = s142;
	else if( sf[pos] == L'>' && sf[pos + 1] != L'=' )
		ret = s143;
	else if( sf[pos] == L'λ' )
		ret = s156;

	if( ret.size() ) {
		if( sf.size() > pos + 1 && sf.find_first_of( s26 + L")", pos ) != pos + 1 )
			throw s5( L"1: unknown syntax: " + sf.substr(pos, 40),
			(uint32_t)s5::s6::s9 );
		pos += 1;
		return ret;
	}

	if( sf.substr( pos, 2 ) == L"+=" )
		ret = L"sumeq";
	else if( sf.substr( pos, 2 ) == L"-=" )
		ret = L"difeq";
	else if( sf.substr( pos, 2 ) == L"*=" )
		ret = L"muleq";
	else if( sf.substr( pos, 2 ) == L"/=" )
		ret = L"diveq";
	else if( sf.substr( pos, 2 ) == L"^=" )
		ret = L"poweq";
	else if( sf.substr( pos, 2 ) == L"<=" )
		ret = L"leq";
	else if( sf.substr( pos, 2 ) == L">=" )
		ret = L"geq";
	else if( sf.substr( pos, 2 ) == L"==" )
		ret = L"eq";
	else if( sf.substr( pos, 2 ) == L"!=" )
		ret = L"neq";

	if( ret.size() ) {
		if( sf.size() > pos + 2 && sf.find_first_of( s26 + L")", pos ) != pos + 2 )
			throw s5( L"2: unknown syntax: " + sf.substr( pos, 40 ), 
				(uint32_t)s5::s6::s9 );
		pos += 2;
		return ret;
	}

	size_t s401 = sf.find_first_of( s26 + L")", pos );
	ret = sf.substr( pos, s401 - pos );
	pos = s401;
	return ret;
}

std::wstring s161::s190() const
{
	return (s169.size() ? s169 + L"::" : L"") + s170;
}

wstring s161::s187( const s44::s57& obj,
	const std::wstring& def /*= std::wstring( L"" )*/ )
{
	if( obj.s67( s96::s121 ) )
		return obj.s69( s96::s121 )->s79();
	return def;
}

std::wstring s161::s194( const s44::s57& obj,
	const std::wstring& s195,
	const std::wstring& def /*= std::wstring( L"" )*/ )
{
	if( obj.s67( s195 ) )
		return obj.s69( s195 )->s79();
	return def;
}


void s161::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << s170 << L" : " << s133[s171] << endl;
	buf << s25::fill_n_ch( L' ', ind ) << L" " << s172 << endl;

	map<wstring, s161*>::const_iterator it = s173.begin();
	for( ; it != s173.end(); ++it ) {
		buf << s25::fill_n_ch( L' ', ind + INDSTEP ) << it->first << endl;
		it->second->s196( pd, ind + INDSTEP * 2 );
	}

}
std::map<const s210*, bool> s163::s212;

s163::~s163()
{

}

s209* s163::s216()
{	throw std::logic_error( "1: not implemented" );}

const s209* s163::s223() const
{	throw std::logic_error( "2: not implemented" );}

s209* s163::s217( s209** s166, size_t s218 )
{	throw std::logic_error( "3: not implemented" ); }

s163* s163::s224() const
{	throw std::logic_error( "4: not implemented" ); }

void s163::s221( const wstring& ) { }

inline bool
s163::isTypeOf( const s209* classObj ) const
{
	return ( classObj->s215() == s215() );
}

s163::operator bool() const { throw std::logic_error( "5: not implemented" ); }

s163::operator int() const { throw std::logic_error( "6: not implemented" ); }

s163::operator double() const { throw std::logic_error( "7: not implemented" ); }

wstring s163::to_wstring() const { throw std::logic_error( "8: not implemented" ); }

bool s163::s222() const
{
	if( s212.find( this ) != s212.end() )
		return true;
	s212[this] = true;
	return false;
}

s163* s163::s225( s161& s370, s160* s192, s164* obj, const wstring& s226 )
{
	s210* p = nullptr;
	if( s370.s189() == s129 ) {


		p = s192->s379( s370.s183(), s226 );
		((s209*)p)->s239( s370.s191() );
	}
	else if( s370.s189() == s130 )
		p = s324::s355( s370, s192, obj, s226 );
	else if( s370.s189() == s132 )
		p = new s228( s370.s183(), s192 );
	else //if( s370.s189() == s131 )

		throw s5( L"unexpected node type" );

	return p;
}

s210* s507( s227& m, const wstring& key )
{
	if( m.count( key ) > 1 )
		throw s5( L"multiple values: " + key, (uint32_t)s5::s6::s10 );
	
	auto ret = m.find( key );
	if( ret == m.end() )
		throw s5( L"no such key: " + key, (uint32_t)s5::s6::s12 );
	return ret->second;
}
vector<wstring> s256::s259 = { s96::s113, s96::s111,
																					s96::s114, s96::s112 };

s1::s3<s260> s286 = new s260();

void s211::s182()
{
	for( auto type : m )
		type.second->s232();
}

void s211::s251( const s208& st )
{

}

void s211::s252( s209* p )
{
	wstring s407 = /*L"::" +*/ p->s236();
	if( m.find( s407 ) != m.end() )
		throw s5( (uint32_t)s5::s6::s10 );
	v.push_back( s407 );
	p->s235( v.size() );
	m[s407] = p;
}

void s211::s253( s209* p, const wstring& s254 )
{
	wstring s407 = s254 + L"::" + p->s236();
	if( m.find( s407 ) != m.end() )
		throw s5( (uint32_t)s5::s6::s10 );
	v.push_back( s407 );
	p->s235( v.size() );
	m[s407] = p;
}

s209* s211::s255( s160* s192, s161& s370, const wstring& s254 )
{
	wstring val = s370.s183();
	if( val[0] == L'[' ) {

		return &nullobject;
	}
	size_t pl = val.find( L"(" );
	wstring s407 = /*L"::" +*/ s305( s192 ).s236();
	if( pl != string::npos ) {
		s407 = val.substr( 0, pl );

	}
	return ( (s164*)m[s407] )->s230( s370, s254 );

	for( int i = (int)v.size() - 1; i >= 0; --i ) {
		wstring s = v[i];
		if( s[0] != L':' ) {
			if( s.find( s254 + L"::" ) != 0 )
				continue;
		}

		s209* ret = m[v[i]]->s230( val, s254 );
		if( ret )
			return ret;
	}

	throw s5( L"No parser for string: " + val,
		(uint32_t)s5::s6::s9 );
}

s209* s211::s255( s160* s192, const std::wstring& val, const wstring& s254 )
{
	if( val[0] == L'[' ) {
		return m[s307( s192, L"" ).s236()]->s230( val, s254 );

		return &nullobject;
	}
	wstring s407 = L"";
	wstring quotes = L"\"/`'";
	if( quotes.find( val[0] ) != string::npos )
		s407 = s305( s192 ).s236();
	else if( isdigit( val[0] ) || val[0] == L'-' )

		return s291::s301( s192, val, s254 );
	else {
		size_t pl = val.find( L"(" );
		if( pl != 0 && pl != string::npos ) {
			s407 = val.substr( 0, pl );

		}
	}
	auto it = m.find( s407 );
	if( it == m.end() )
		throw s5( L"Type does not exist: " + val );
	return it->second->s230( val, s254 );
}

s209* s211::s255( s160* s192, size_t type, const wstring& s254 )
{
	if( type > v.size() )
		throw s5( L"no such type: " + to_wstring( type ) );
	wstring s = v[type - 1];

	return (s209*)m[s]->s237();
}

s209* s211::get( const wstring& nam, bool thr/*= true*/ ) const
{
	auto ret = m.find( nam );
	if( ret == m.end() ) {
		if( thr )
			throw s5( L"symbol not found: " + nam );
		else
			return NULL;
	}
	return ret->second;
}

bool s211::s67( const std::wstring& nam ) const
{
	if( m.find( nam ) == m.end() )
		return false;
	return true;
}

void s211::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"Types :" << endl;

	s250::const_iterator it = m.begin();
	for( ; it != m.end(); ++it ) {
		buf << s25::fill_n_ch( L' ', ind + 5 ) << it->first << endl;
		it->second->s196( pd, ind + 10 );
	}

}

s208::s208( const s208& right )
	: s408( right.s408 ), s269( right.s269 ), s460( right.s460 )
{
}

void s208::s221( const wstring& s220, bool s271/*= true*/ )
{
	for( auto s409 : s408 ) {
		if( s409.second->s437() != s202 )
			s409.second->s221( s220 );
	}
	if( s271 ) {
		for( auto s409 : s408 ) {
			if( s409.second->s437() == s202 )
				s409.second->s221( s220 );
		}
	}
}

void s208::s272()
{
	for( auto it = s408.begin(); it != s408.end(); ++it )
		delete it->second;
	s408.clear();
}

void s208::copy( s208& t, s164* s429, s164* s352, s59 ap ) const
{
	t.s269 = s269;
	for( s268::const_iterator it = s408.begin(); it != s408.end(); ++it ) {
		if( it->second->s437() == s202 )
			t.s273( it->first, new s324( *(s324*)it->second,
				s429, s352, vector<s210*>() ), ap );
		else
			t.s273( it->first, (s209*)it->second->s224(), ap );
	}
}

void s208::s280( s208& t ) const
{
	for( s268::const_iterator it = s408.begin(); it != s408.end(); ++it ) {
		if( it->second->s437() == s202 )
			t.s273( it->first, it->second );
		else
			t.s273( it->first, (s209*)it->second->s224() );
	}
}

bool s208::s270( const std::wstring& nam, s59 ap /*= s60*/ )
{
	if( s408.find( nam ) != s408.end() ) {
		wstring rep = s96::s98 + L" name already exists: " + nam;
		if( ap == s60 || ap == s267 ) {

			if( ap == s60 )
				throw s5( (uint32_t)s5::s6::s10 );
			return false;
		}
		else if( ap == s62 ) {

			return false;
		}
	}
	return true;
}

void s208::s273( const std::wstring& nam, s209* s409, s59 ap/*= s60*/ )
{
	if( (ap == s61) || s270( nam, ap ) )
		s408[nam] = s409;
}

void s208::s273( const std::wstring& nam, s56 val, s59 ap/*= s60*/ )
{

	throw s5( (uint32_t)s5::s6::s10 );
}

void s208::s274( const std::wstring& nam )
{
	auto it = s408.find( nam );
	if( it == s408.end() )
		return;
	s408.erase( it );
}

void s208::s275( const s44::s57& block, s59 ap/*= s60*/ )
{
	vector<pair<wstring, s56>> s58;
	block.s71( s58 );
	for( size_t n = 0; n < s58.size(); ++n )
		s273( s58[n].first, s58[n].second );
}

bool s208::s67( const std::wstring& nam ) const
{
	if( s408.find( nam ) == s408.end() )
		return false;
	return true;
}

s209* s208::get( const wstring& nam, bool thr/*= true*/ ) const
{
	auto ret = s408.find( nam );
	if( ret == s408.end() ) {
		if( thr )
			throw s5( L"symbol not found: " + nam );
		else
			return NULL;
	}
	return ret->second;
}

void s208::s278( std::vector<std::wstring>& res ) const
{
	for( auto s409 : s408 )
		res.push_back( s409.first );
}

void s208::s276( vector<wstring>& res ) const
{
	for( auto s409 : s408 ) {
		if( s409.second->s437() == s202 )
			res.push_back( s409.first );
	}
}

void s208::s277( vector<wstring>& res ) const
{
	for( auto s409 : s408 ) {
		if( s409.second->s437() == s200 ||
			s409.second->s437() == s207 || s409.second->s437() == s206 )
			res.push_back( s409.first );
	}
}

void s208::s279( const s208& t,
	vector<wstring>& res ) const
{
	for( auto s409 : s408 ) {
		if( t.s67( s409.first ) )
			res.push_back( s409.first );
	}
}

void s208::s181( const s208& t, s59 ap /*= s60*/ )
{
	if( ap != s61 ) 
		for( auto s409 : t.s408 )
			s270( s409.first, ap );

	for( auto s409 : t.s408 )
		s273( s409.first, s409.second, ap );
}

void s208::s281( s246 pv, s161* block )
{
	if( !s269 )
		s269 = new s260();
	s269->s262( pv, block );
}

void s208::s266( const wstring& s226, vector<wstring>& res )
{
	for( s268::iterator it = s408.begin(); it != s408.end(); ++it ) {
		s246 pv = s247;
		if( s269 )
			pv = s269->s265( it->first, s226 );
		if( pv == s247 ) {
			if( s460 == s454 )
				pv = s248;
			else if( s460 == s456 )
				pv = s249;
			else {
				if( it->second->s437() == s202 )
					pv = s248;
				else
					pv = s249;
			}
		}
		if( pv == s248 )
			res.push_back( it->first );
	}
}

bool s208::s283( const std::wstring& s170,
																		const std::wstring& s226 ) const
{
	if( s269 ) {
		s246 pv = s269->s265( s170, s226 );
		if( pv == s248 )
			return true;
		else if( pv == s247 ) {
			if( s460 == s454 )
				pv = s248;
			else if( s460 == s456 )
				pv = s249;
			else {
				auto it = s408.find( s170 );
				if( it == s408.end() )
					throw s5( L"1: Symbol does not exist: " + s170 );
				size_t cat = it->second->s437();
				if( cat == s202 || cat == s205 || cat == s207 )
					return true;
			}
		}
		return false;
	}
	return true;
}

void s208::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"Symbols :" << endl;

	s268::const_iterator it = s408.begin();
	for( ; it != s408.end(); ++it ) {
		buf << s25::fill_n_ch( L' ', ind + INDSTEP ) << it->first << endl;
		it->second->s196( pd, ind + INDSTEP * 2 );
	}

}

s284::s284()
{

}

void s284::s221( s160* s192, const wstring& s418 )
{
	for( size_t n = 0; n < s474.size(); ++n ) {
		wstring nam = s474[n];
		vector<wstring> res;
		s192->s382( nam, s418, res );
		for( size_t m = 0; m < res.size(); ++m ) {
			s408.insert( make_pair( res[m], (s209*)s192->s336( 
																			s474[n],	s418 ) ) );
		}
	}
}

void s284::s482( const wstring& nam, s160* s192, const wstring& s418 )
{
	s474.push_back( nam );
	vector<wstring> res;
	s192->s382( nam, s418, res );
	for( size_t n = 0; n < res.size(); ++n )
		s408.insert( make_pair( res[n], (s209*)s192->s336( nam,	s418 ) ) );
}

void s284::s285( const std::wstring& s )
{
	if( s[0] != L'"' || s[s.size() - 1] != L'"' )
		throw s5( L"Unrecognized import syntax: " + s );
	s474.push_back( s.substr(1, s.size() - 2 ) );
}

bool s284::s240( const std::wstring& s409, s228* ref )
{
	s268::iterator it = s408.find( s409 );
	if( it != s408.end() )
		return it->second->s240( s409, ref, L"" );
	return false;
}

void s284::copy( s284& t ) const
{
	for( s268::const_iterator it = s408.begin(); it != s408.end(); ++it )
		t.s408[it->first] = it->second;
}

s256::s256( s246 pv_, const vector<wstring>& s257 )
	: pv( pv_ ), patterns( s257 )
{
}

s256::s256( const wstring& ag_, const wstring& sf )
{
}

s246 s256::s258( const std::wstring& s220 ) const
{
	/* Stub code. TODO with regexes. */
	for( size_t n = 0; n < patterns.size(); ++n )
		if( patterns[n] == s220 || patterns[n] == L"_" )
			return pv;
	if( pv == s249 )
		return s248;
	return s249;
}

void s260::s262( s246 pv, s161* s370 )
{
	s161::s167& s410 = s370->s185();
	s161::s167::iterator it = s410.begin();
	for( ; it != s410.end(); ++it ) {
		wstring l = it->second->s183().substr( 1, it->second->s183().size() - 2 );
		vector<wstring> res;
		wstring s391( VECELSEP, 1 );
		s25::s35( l, s391, res );
		acls[it->first] = new s256( pv, res );
	}
}

void s260::s263( const std::wstring& s, s256& pl )
{

}

void s260::s264( const std::wstring& s, const std::wstring& s386 )
{

}


s246 s260::s265( const std::wstring& mem, const std::wstring& s220 )
{
	s261::iterator it = acls.find( mem );
	if( it == acls.end() )
		return s247;

	return it->second->s258( s220 );
}
size_t s306::type;

const wstring s306::s407 = L"Null";
s291::s297 s306::s411;
size_t s302::type;

const wstring s302::s407 = L"Int";
s291::s297 s302::s411;
size_t s304::type;

const wstring s304::s407 = L"Double";
s291::s297 s304::s411;
size_t s305::type;

const wstring s305::s407 = L"String";
s291::s297 s305::s411;
size_t s307::type;
const wstring s307::s407 = L"Vector";
s291::s297 s307::s411;

s306 nullobject( NULL );

template <class charT, charT s391>
class punct_facet : public std::numpunct<charT>
{
protected:
	charT do_decimal_point() const { return s391; }
};

std::locale exprloc;

s209::~s209()
{
}


void s209::s231( s160* s192 )
{
	setlocale( LC_NUMERIC, "C" );

	s192->s252( new s306( s192 ) );
	s192->s252( new s305( s192 ) );
	s192->s252( new s302( s192, 0 ) );
	s192->s252( new s304( s192, 0 ) );
	s192->s252( new s307( s192, L"" ) );

	nullobject = s306( s192 );
}

s209* s209::s216()
{
	return this; 
}

size_t s291::s233( const std::wstring& s234 ) const
{
	auto it = s298().find( s234 );
	if( it == s298().end() )
		throw s5( L"No such operation: " + s236() + L"::" + s234,
		(uint32_t)s5::s6::s12 );
	size_t ret = it->second->s295;
	if( !ret ) // e.g. s307::get
		ret = s215();
	return ret;
}

const s209* s291::s223() const
{
	return (s209*)s192->s384( s236(), s197 );
}

s292 s291::s299( const std::wstring& s234 ) const
{
	s297::const_iterator it = s298().find( s234 );
	if( it == s298().end() )
		throw s5( L"No such operation: " + s236() + L"::" + s234,
		(uint32_t)s5::s6::s12 );
	s294* sp = it->second;
	return sp->s412;
}

s209* s291::s217( s209** s166, size_t s218 )
{
	return this;
	this->s293( s166, s218 );
	return 0;
}

s209* s291::s301( s160* s192, const std::wstring& val, const std::wstring& s226 )
{
	if( val.find_first_not_of( L"-0123456789" ) == std::string::npos ||
		val.find( L"Int(" ) == 0 ) {
		size_t pos = 0;
		return s302( s192, 0 ).s230( val, s226 );
	}
	else 
		return s304( s192, 0.0 ).s230( val, s226 );
}

s302::s302( s160* s192, int i )
	: s291( s192 ), val( i )
{
	s214 = s302::s303();
}

s302::s302( const s302& r )
	: s291( r.s192 ), val( r.val )
{
	s214 = s302::s303();
}

s302::s302( s160* s192, const std::wstring& s, size_t& pos )
	: s291( s192 )
{
	const wchar_t* pst = NULL;
	wchar_t* pend = NULL;
	long res = 0;
	if( !s.empty() ) {
		pst = s.c_str();
		if( !s40( pst, &res, &pend ) )
			throw s5( L"1: unknown syntax: " + s.substr(pos, 40),
						(uint32_t)s5::s6::s9 );
	}
	val = (int)res;
	pos = pend ? ( pend - pst ) : string::npos;
	s214 = s302::s303();
}

void s302::s232()
{
	s411[L"abs"] = new s294( L"abs", &s302::abs, s302::s303() );
	s411[L"set"] = new s294( L"set", &s302::set, s306::s303() );
	s411[L"sum"] = new s294( L"sum", &s302::sum, s302::s303() );
	s411[L"dif"] = new s294( L"dif", &s302::dif, s302::s303() );
	s411[L"mul"] = new s294( L"mul", &s302::mul, s302::s303() );
	s411[L"div"] = new s294( L"div", &s302::div, s302::s303() );
	s411[L"pow"] = new s294( L"pow", &s302::pow, s302::s303() );
	s411[L"sumeq"] = new s294( L"sumeq", &s302::sumeq, s302::s303() );
	s411[L"difeq"] = new s294( L"difeq", &s302::difeq, s302::s303() );
	s411[L"muleq"] = new s294( L"muleq", &s302::muleq, s302::s303() );
	s411[L"diveq"] = new s294( L"diveq", &s302::diveq, s302::s303() );
	s411[L"poweq"] = new s294( L"poweq", &s302::poweq, s302::s303() );
	s411[L"eq"] = new s294( L"eq", &s302::eq, s302::s303() );
	s411[L"less"] = new s294( L"less", &s302::less, s302::s303() );
	s411[L"greater"] = new s294( L"greater", &s302::greater, s302::s303() );
	s411[L"leq"] = new s294( L"leq", &s302::leq, s302::s303() );
	s411[L"geq"] = new s294( L"geq", &s302::geq, s302::s303() );
	s411[L"neq"] = new s294( L"neq", &s302::neq, s302::s303() );
	s411[L"mod"] = new s294( L"mod", &s302::mod, s302::s303() );
	s411[L"sqrt"] = new s294( L"sqrt", &s302::sqrt, s304::s303() );
	s411[L"nroot"] = new s294( L"nroot", &s302::nroot, s304::s303() );
	s411[L"toDouble"] = new s294( L"toDouble", &s302::toDouble, s304::s303() );
}

s209* s302::s237() const
{
	return new s302( s192, 0 );
}

size_t s302::s219() const
{
	return s302::s303();
}


void s302::s235( size_t type_ )
{
	type = type_;
	s214 = type_;
}

void s302::s221( const std::wstring& s226 )
{
}

s209* s302::s224() const
{
	return new s302( *this );
}

void s302::s238( s210* p ) const
{
	if( p->s219() == s302::s303() )
		*( (s302*)p )->Ptr() = val;
	else if( p->s219() == s304::s303() )
		*( (s304*)p )->Ptr() = (double)val;
	else
		throw s5( L"No conversion to type " + std::to_wstring( p->s219() ) );
}

#define OPRES ((s302*)(s210*)*s166)
#define FLAGRES ((s302*)(s210*)*s166)
#define DR ((s210*)*(s166 + 1))
#define PARN(n)((s210*)*(s166 + n))

inline void s302::abs( s209** s166, size_t s218 )
{
	int t = (int)*DR;
	if( t >= 0 )
		OPRES->val = t;
	else
		OPRES->val = -t;
}

inline void s302::set( s209** s166, size_t s218 )
{

	( (s302*)DR)->val = (int)*PARN(2);
}

inline void s302::sum( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) + (int)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val += (int)*PARN( n );
}

inline void s302::dif( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) - (int)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val -= (int)*PARN( n );
}

inline void s302::mul( s209** s166, size_t s218 )
{
	OPRES->val = ((int)*DR) * (int)*PARN(2);
	for( size_t n = 3; n < s218; ++n )
		OPRES->val *= (int)*PARN( n );
}

inline void s302::div( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) / (int)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val /= (int)*PARN( n );
}

inline void s302::pow( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) * ( (int)*DR ); ;
	for( int n = 2; n < (int)*PARN( 2 ); ++n )
		OPRES->val *= ( (int)*DR );
}

inline void s302::sumeq( s209** s166, size_t s218 )
{
	( (s302*)DR )->val += (int)*PARN(2);
	for( size_t n = 3; n < s218; ++n )
		( (s302*)DR )->val += (int)*PARN(n);
	OPRES->val = ( (int)*DR );
}

inline void s302::difeq( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) - (int)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val -= (int)*PARN( n );
}

inline void s302::muleq( s209** s166, size_t s218 )
{
	OPRES->val = ((int)*DR) * (int)*PARN(2);
	for( size_t n = 3; n < s218; ++n )
		OPRES->val *= (int)*PARN( n );
}

inline void s302::diveq( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) / (int)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val /= (int)*PARN( n );
}

inline void s302::poweq( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) * ( (int)*DR ); ;
	for( int n = 2; n < (int)*PARN( 2 ); ++n )
		OPRES->val *= ( (int)*DR );
}

inline void s302::eq( s209** s166, size_t s218 )
{
	if( ((int)*DR) == (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::less( s209** s166, size_t s218 )
{
	if( ( (int)*DR ) < (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::greater( s209** s166, size_t s218 )
{
	if( ( (int)*DR ) > (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::leq( s209** s166, size_t s218 )
{
	if( ( (int)*DR) <= (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::geq( s209** s166, size_t s218 )
{
	if( ( (int)*DR ) >= (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::neq( s209** s166, size_t s218 )
{
	if( ( (int)*DR ) != (int)*PARN( 2 ) )
		FLAGRES->val = 1;
	else
		FLAGRES->val = 0;
}

inline void s302::mod( s209** s166, size_t s218 )
{
	OPRES->val = ( (int)*DR ) % (int)*PARN( 2 );
}

inline void s302::sqrt( s209** s166, size_t s218 )
{
	*((s304*)s166[0])->Ptr() = ::sqrt( (double)*DR );
}

inline void s302::nroot( s209** s166, size_t s218 )
{
	*((s304*)s166[0])->Ptr() = ::pow( (int)*DR, (double)*PARN( 2 ) );
}

inline void s302::toDouble( s209** s166, size_t s218 )
{
	*( (s304*)s166[0] )->Ptr() = (double)*DR;
}

s209* s302::s230( const wstring& s, const wstring& s226 )
{
	if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
		size_t pos = 0;
		return new s302( s192, s, pos );
	}
	else if( s.find( L"Int(" ) == 0 ) {
		size_t pos = 0;
		return new s302( s192, s.substr( 4, s.size() - 5 ), pos );
	}

	return 0;
}

s209* s304::s230( const wstring& s, const wstring& s226 )
{
	if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
		s.find( L"." ) != std::string::npos ) {
		size_t pos = 0;
		return new s304( s192, s, pos );
	}
	else if( s.find( L"Double(" ) == 0 ) {
		size_t pos = 0;
		return new s304( s192, s.substr( 7, s.size() - 8 ), pos );
	}

	return 0;
}

void s302::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"Integer : " << val << endl;

}

s304::s304( s160* s192, double d ) 
	: s291( s192 ), val( d ) 
{ 
	s214 = s304::s303();
}

s304::s304( const s304& r )
	: s291( r.s192 ), val( r.val )
{
	s214 = s304::s303();
}

s304::s304( s160* s192, const std::wstring& s, size_t& pos )
	: s291( s192 )
{
	const wchar_t* pst = NULL;
	wchar_t* pend = NULL;
	double res = 0.0;
	if( !s.empty() ) {
		pst = s.c_str();
		if( !s41( pst, &res, &pend ) )
			throw s5( L"2: unknown syntax: " + s.substr(pos, 40),
						(uint32_t)s5::s6::s9 );
	}
	val = res;
	pos = pend ? pend - pst : string::npos;
	s214 = s304::s303();
}

s209* s304::s237() const
{
	return new s304( s192, 0.0 );
}

size_t s304::s219() const
{
	return s304::s303();
}

void s304::s235( size_t type_ )
{
	type = type_;
	s214 = type_;
}

void s304::s221( const std::wstring& s226 )
{
}

void s304::s232()
{
	s411[L"abs"] = new s294( L"abs", &s304::abs, s304::s303() );
	s411[L"set"] = new s294( L"set", &s304::set, s306::s303() );
	s411[L"sum"] = new s294( L"sum", &s304::sum, s304::s303() );
	s411[L"dif"] = new s294( L"dif", &s304::dif, s304::s303() );
	s411[L"mul"] = new s294( L"mul", &s304::mul, s304::s303() );
	s411[L"div"] = new s294( L"div", &s304::div, s304::s303() );
	s411[L"pow"] = new s294( L"pow", &s304::pow, s304::s303() );
	s411[L"sumeq"] = new s294( L"sumeq", &s304::sumeq, s304::s303() );
	s411[L"difeq"] = new s294( L"difeq", &s304::difeq, s304::s303() );
	s411[L"muleq"] = new s294( L"muleq", &s304::muleq, s304::s303() );
	s411[L"diveq"] = new s294( L"diveq", &s304::diveq, s304::s303() );
	s411[L"poweq"] = new s294( L"poweq", &s304::poweq, s304::s303() );
	s411[L"sqrt"] = new s294( L"sqrt", &s304::sqrt, s304::s303() );
	s411[L"nroot"] = new s294( L"nroot", &s304::nroot, s304::s303() );
	s411[L"eq"] = new s294( L"eq", &s304::eq, s302::s303() );
	s411[L"less"] = new s294( L"less", &s304::less, s302::s303() );
	s411[L"greater"] = new s294( L"greater", &s304::greater, s302::s303() );
	s411[L"leq"] = new s294( L"leq", &s304::leq, s302::s303() );
	s411[L"geq"] = new s294( L"geq", &s304::geq, s302::s303() );
	s411[L"neq"] = new s294( L"neq", &s304::neq, s302::s303() );
	s411[L"dcmp"] = new s294( L"dcmp", &s304::dcmp, s302::s303() );
	s411[L"dcmpr"] = new s294( L"dcmpr", &s304::dcmpr, s302::s303() );
	s411[L"toInt"] = new s294( L"toInt", &s304::toInt, s302::s303() );
}

s209* s304::s224() const
{
	return new s304( *this );
}

void s304::s238( s210* p ) const
{
	if( p->s219() == s302::s303() )
		*( (s302*)p )->Ptr() = (int)val;
	else if( p->s219() == s304::s303() )
		*( (s304*)p )->Ptr() = val;
	else
		throw s5( L"No conversion to type " + std::to_wstring( p->s219() ) );
}

std::wstring s304::to_wstring() const 
{
	wstring s = std::to_wstring( val );
	size_t pl = s.find_last_not_of( L'0' );
	if( s[pl] != L'.' && s[pl] != L',' )
		++pl;
	return s.substr(0, pl);
}

#undef OPRES
#define OPRES ((s304*)(s210*)*s166)

inline void s304::set( s209** s166, size_t s218 )
{

	( (s304*)DR )->val = (double)*PARN( 2 );
}

void s304::abs( s209** s166, size_t s218 )
{
	double t = (double)*DR;
	if( t >= 0 )
		OPRES->val = t;
	else
		OPRES->val = -t;
}

inline void s304::mul( s209** s166, size_t s218 )
{
	OPRES->val = ( (double)*DR ) * (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val *= (double)*PARN( n );
}

inline void s304::sum( s209** s166, size_t s218 )
{

	OPRES->val = ( (double)*DR ) + (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val += (double)*PARN( n );
}

inline void s304::div( s209** s166, size_t s218 )
{
	OPRES->val = ( (double)*DR ) / (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val /= (double)*PARN( n );
}

inline void s304::dif( s209** s166, size_t s218 )
{
	OPRES->val = ( (double)*DR ) - (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		OPRES->val -= (double)*PARN( n );
}

inline void s304::sumeq( s209** s166, size_t s218 )
{
	( (s304*)DR )->val += (double)*PARN(2);
	for( size_t n = 3; n < s218; ++n )
		( (s304*)DR )->val += (double)*PARN(n);
	OPRES->val = ( (double)*DR );
}

inline void s304::difeq( s209** s166, size_t s218 )
{
	( (s304*)DR )->val -= (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		( (s304*)DR )->val -= (double)*PARN( n );
	OPRES->val = ( (double)*DR );
}

inline void s304::muleq( s209** s166, size_t s218 )
{
	( (s304*)DR )->val *= (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		( (s304*)DR )->val *= (double)*PARN( n );
	OPRES->val = ( (double)*DR );
}

inline void s304::diveq( s209** s166, size_t s218 )
{
	( (s304*)DR )->val /= (double)*PARN( 2 );
	for( size_t n = 3; n < s218; ++n )
		( (s304*)DR )->val /= (double)*PARN( n );
	OPRES->val = ( (double)*DR );
}

inline void s304::poweq( s209** s166, size_t s218 )
{
	( (s304*)DR )->val = ::pow( (double)*DR, (double)*PARN( 2 ) );
	for( size_t n = 3; n < s218; ++n )
		( (s304*)DR )->val = ::pow( (double)*DR, (double)*PARN( n ) );
	OPRES->val = ( (double)*DR );
}

inline void s304::eq( s209** s166, size_t s218 )
{
	double d = (double)*DR;
	if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::less( s209** s166, size_t s218 )
{
	if( ((double)*DR) < (double)*PARN( 2 ) )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::greater( s209** s166, size_t s218 )
{
	if( ( (double)*DR ) > (double)*PARN( 2 ) )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::leq( s209** s166, size_t s218 )
{
	if( ( (double)*DR ) <= (double)*PARN( 2 ) )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::geq( s209** s166, size_t s218 )
{
	if( ( (double)*DR ) >= (double)*PARN( 2 ) )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::neq( s209** s166, size_t s218 )
{
	if( ( (double)*DR ) != (double)*PARN( 2 ) )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s304::sqrt( s209** s166, size_t s218 )
{
	OPRES->val = ::sqrt((double)*DR);
}

inline void s304::nroot( s209** s166, size_t s218 )
{
	*( (s304*)s166[0] )->Ptr() = ::pow( (double)*DR, (double)*PARN( 2 ) );
}

inline void s304::dcmp( s209** s166, size_t s218 )
{
	double dl = (double)*DR;
	double dr = (double)*PARN( 2 );
	double diff = (double)*PARN( 3 );
	if( dl > dr ) {
		if( dl - dr <= diff )
			*FLAGRES->Ptr() = 0;
		else
			*FLAGRES->Ptr() = 1;
	}
	else {
		if( dr - dl <= diff )
			*FLAGRES->Ptr() = 0;
		else
			*FLAGRES->Ptr() = -1;
	}
}

inline void s304::dcmpr( s209** s166, size_t s218 )
{
	double dl = (double)*DR;
	double dr = (double)*PARN( 2 );
	double diff = (double)*PARN( 3 );
	if( dl > dr ) {
		if( dl / dr - 1 <= diff )
			*FLAGRES->Ptr() = 0;
		else
			*FLAGRES->Ptr() = 1;
	}
	else {
		if( dr / dl - 1 <= diff )
			*FLAGRES->Ptr() = 0;
		else
			*FLAGRES->Ptr() = -1;
	}
}

inline void s304::pow( s209** s166, size_t s218 )
{
	OPRES->val = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );
}

inline void s304::toInt( s209** s166, size_t s218 )
{
	*( (s302*)s166[0] )->Ptr() = (int)*DR;
}

void s304::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"Double : " << val << endl;

}

s305::s305( s160* s192, const std::wstring& s )
	: s291( s192 ), val( s )
{
	s214 = s305::s303();
}


s305::s305( const s305& r )
	: s291( r.s192 ), val( r.val )
{
	s214 = s305::s303();
}

s305::s305( s160* s192, const std::wstring& s, size_t& pos )
	:s291( s192 )
{
	val = s;
	pos = string::npos;
	s214 = s305::s303();
}

s209* s305::s237() const
{
	return new s305( s192, L"" );
}

size_t s305::s219() const
{
	return s305::s303();
}


void s305::s232()
{
	s411[L"set"] = new s294( L"set", &s305::set, s306::s303() );
	s411[L"sum"] = new s294( L"sum", &s305::sum, s305::s303() );
	s411[L"eq"] = new s294( L"eq", &s305::eq, s302::s303() );
	s411[L"less"] = new s294( L"less", &s305::less, s302::s303() );
	s411[L"greater"] = new s294( L"greater", &s305::greater, s302::s303() );
	s411[L"leq"] = new s294( L"leq", &s305::leq, s302::s303() );
	s411[L"geq"] = new s294( L"geq", &s305::geq, s302::s303() );
	s411[L"neq"] = new s294( L"neq", &s305::neq, s302::s303() );
}

void s305::s235( size_t type_ )
{
	type = type_;
	s214 = type_;
}

void s305::s221( const wstring& s226 )
{
}

wstring s413( wchar_t c )
{
	wstring ret;
	if( c == L'n' )
		ret = L"\n";
	else if( c == L't' )
		ret = L"    ";
	else
		throw s5( L"Unknown escape sequence: \\" + c );
	return ret;
}

s209* s305::s230( const wstring& s, const wstring& s226 )
{
	wstring val;
	size_t pl;
	if( s.find( L"String(" ) == 0 )
		val = s.substr( 7, s.size() - 8 );
	else if( s.size() == 4 && s[0] == L'\'' && s[1] == L'\\' && s[3] == L'\'' )
		val = s413( s[2] );
	else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
		val = s;
		while( pl != string::npos ) {
			if( pl == val.size() - 1 )
				break;
			wstring code = s413( val[pl + 1] );
			val = val.replace( pl, 2, code );
			pl = val.find( L"\\" );			
		}
	}

	if( val.empty() )
		val = s;

	return new s305( s192, val );
}

s209* s305::s224() const
{
	return new s305( *this );
}

void s305::s238( s210* p ) const
{
	if( p->s219() == s305::s303() )
		*( (s305*)p )->Ptr() = val;
	else if( p->s219() == s302::s303() )
		*( (s302*)p )->Ptr() = std::stoi( val );
	else if( p->s219() == s304::s303() )
		*( (s304*)p )->Ptr() = std::stof( val );
	else
		throw s5( L"No conversion to type " + std::to_wstring( p->s219() ) );
}

#undef OPRES
#define OPRES ((s305*)(s210*)*s166)


inline void s305::set( s209** s166, size_t s218 )
{

	( (s305*)DR )->val = ( (s305*)PARN( 2 ))->val;
}

inline void s305::sum( s209** s166, size_t s218 )
{
	OPRES->val = DR->to_wstring() + PARN( 2 )->to_wstring();
	for( size_t n = 3; n < s218; ++n )
		OPRES->val += PARN( n )->to_wstring();
}

inline void s305::eq( s209** s166, size_t s218 )
{
	if( DR->to_wstring() == PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s305::less( s209** s166, size_t s218 )
{
	if( DR->to_wstring() < PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s305::greater( s209** s166, size_t s218 )
{
	if( DR->to_wstring() > PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s305::leq( s209** s166, size_t s218 )
{
	if( DR->to_wstring() <= PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s305::geq( s209** s166, size_t s218 )
{
	if( DR->to_wstring() >= PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

inline void s305::neq( s209** s166, size_t s218 )
{
	if( DR->to_wstring() != PARN( 2 )->to_wstring() )
		*FLAGRES->Ptr() = 1;
	else
		*FLAGRES->Ptr() = 0;
}

void s305::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"String : " << val << endl;

}

size_t s306::s219() const
{
	return s306::s303();
}

void s306::s235( size_t type_ )
{
	type = type_;
	s214 = type_;
}

void s306::s221( const wstring& s226 )
{
}

s209* s306::s237() const
{
	return new s306( s192 );
}

s209* s306::s230( const wstring& s, const wstring& s226 )
{
	if( s.find( L"Null" ) == 0 ) {
		size_t pos = 0;
		return &nullobject;
	}

	return NULL;
}

void s306::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"NullValue : -" << endl;

}

s307::s307( s160* s192, const wstring& sf )
	: s291( s192 ), s472( 0 )
{
	if( sf.size() )
		val.push_back( new s288( s192, sf, L"" ) );
	s214 = s307::s303();
}

s307::s307( const s307& right )
	: s291( right.s192 ), s472( 0 )
{
	val = right.val;
	s214 = right.s214;
}

s209* s307::s230( const wstring& s, const wstring& s226 )
{
	wstring sv;
	if( s[0] == L'[' && s[s.size() - 1] == L']' )
		sv = s25::s30( s, L"[]" );
	else if( s.find( s407 ) == 0 && s[s.size() - 1] == L')' ) {
		sv = s25::s30( s.substr( s407.size() ), s26 );
		if( sv[0] != L'(' )
			throw s5( L"wrong vector constructor syntax" );
		sv = s25::s30( sv.substr( 1, sv.size() - 2 ), L" " );
		wstring tp, s74=L"";
		if( isdigit( sv[sv.size() - 1] ) ) {
			s74 = sv.substr( sv.rfind( L" " ) + 1 );
			tp = sv.substr( 0, sv.size() - s74.size() );
		}
		else {
			s74 = L" 0";
			tp = sv;
		}

		sv = L"]" + tp + s74;
	}
	else
		return 0;
	return new s307( s192, sv );
}

void s307::s221( const wstring& s226 )
{
	s288* pst = (s288*)val[0];
	val.clear();
	const wstring& sf = pst->Str();
	if( sf[0] == L']' ) {
		wstring s414 =  sf.substr( sf.rfind( L" " ) );
		wstring s415 = sf.substr( 1, sf.size() - s414.size() - 1 );
		size_t s74 = std::stoi( s414 );
		for( size_t n = 0; n < s74; ++n )
			val.push_back( s192->s379( s415, s226 ) );
		if( s74 == 0 )
			s472 = s192->s379( s415, s226 )->s215();
		else
			s472 = val[0]->s215();
	}
	else {
		size_t s398 = 0;
		size_t s416, s417;
		while( s398 < sf.size() - 1 ) {
			size_t pl = sf.find_first_not_of( s26, s398 );
			if( pl == string::npos )
				break;
			if( s398 != 0 ) {
				if( sf[pl] != VECELSEP )
					throw s5( L"wrong vector syntax: missed separator" );
				++pl;
			}
			pl = sf.find_first_not_of( s26, pl );
			if( pl == string::npos || sf[pl] == VECELSEP )
				throw s5( L"wrong vector syntax: empty element" );

			if( wstring( L"\'\"`" ).find( sf[pl] ) != string::npos ) {
				s25::s33( sf, pl, sf[pl], s416, s417 );
				if( s417 == string::npos )
					throw s5( L"wrong vector syntax: mismatched quotes" );
			}
			else {
				s416 = pl;
				s417 = sf.find_first_of( s26 + VECELSEP, pl );
			}
			s398 = s417;
			wstring sel = sf.substr( s416, s417 - s416 );
			val.push_back( s192->s379( sel, s226 ) );
			if( !s472 )
				s472 = val[0]->s215();
			else if( s472 != val.back()->s215() )
				throw s5( L"different types in vector" );
		}
	}
	delete pst;
	s214 = s307::s303();
	s411[L"get"]->s295 = s472;
	s220 = s226;
}

void s307::s232()
{
	s411[L"set"] = new s294( L"set", &s307::set, s306::s303() );
	s411[L"get"] = new s294( L"get", &s307::get, 0 );
	s411[L"add"] = new s294( L"add", &s307::add, s306::s303() );
	s411[L"size"] = new s294( L"size", &s307::size, s302::s303() );
	s411[L"resize"] = new s294( L"resize", &s307::resize, s306::s303() );
	s411[L"eq"] = new s294( L"eq", &s307::eq, s302::s303() );
}

s209* s307::s237() const
{
	return new s307( s192, L"" );
}

size_t s307::s219() const
{
	return s307::s303();
}

void s307::s235( size_t type_ )
{
	type = type_;
	s214 = type_;
}

size_t s307::s215() const
{
	if( val.empty() || val[0]->s215() == s203 )
		throw s5( L"vector is not initialized" );

		return val[0]->s215();
	return s214;
}

inline bool
s307::isTypeOf( const s209* classObj ) const
{

	return (( (s307*)classObj )->s472 == s472);
}

s209* s307::s224() const
{
	return new s307( *this );
}

void s307::s238( s210* p ) const
{
}

#undef OPRES
#define OPRES ((s307*)(s210*)*s166)


inline void s307::set( s209** s166, size_t s218 )
{

	s166[3]->s238( ( (s307*)DR )->val[(int)*s166[2]]);
}

inline void s307::get( s209** s166, size_t s218 )
{
	*s166 = (s209*)( (s307*)DR )->val[(int)*s166[2]];
}

inline void s307::add( s209** s166, size_t s218 )
{
	if( ( (s307*)DR )->s310() != s166[2]->s215() )
		throw s5( L"unmatched element type" );
	( (s307*)DR )->val.push_back( s166[2]->s224() );
}

inline void s307::size( s209** s166, size_t s218 )
{
	*((s302*)*s166)->Ptr() = (int)( (s307*)DR )->val.size();
}

inline void s307::resize( s209** s166, size_t s218 )
{
	int size = (int)*s166[2];
	( (s307*)DR )->val.resize( size );
	for( int i = 0; i < size; ++i )
		( (s307*)DR )->val[i] = ( (s307*)DR )->s192->s379(
		( (s307*)DR )->s472, ( (s307*)DR )->s220 );
}

inline void s307::eq( s209** s166, size_t s218 )
{
	size_t size = ( (s307*)DR )->val.size( ); 
	s307* right = (s307*)s166[2];
	if( right->val.size() != size ) {
		*( (s302*)*s166 )->Ptr() = 0;
		return;
	}
	for( size_t n = 0; n < size; ++n ) {
		if( right->val[n] != ( (s307*)DR )->val[n] ) {
			*( (s302*)*s166 )->Ptr() = 0;
			return;
		}
	}
	*( (s302*)*s166 )->Ptr() = 1;
}

wstring s307::to_wstring() const 
{ 
	wstring ret = L"[";
	for( size_t n = 0; n < val.size(); ++n )
		ret += val[n]->to_wstring() + ( n == val.size() - 1 ? L"" : L", " );
	ret += L"]";
	return ret; 
}

void s307::s196( std::wostream* pd, int ind /*=0*/ ) const
{
	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"Vector : " << endl;
	for( size_t n = 0; n < val.size(); ++n )
		val[n]->s196( pd, ind + INDSTEP );
}


s228::s228( const s228& right )
	: s210( right.s192, s201 ), s229( right.s229 ), s312( right.s312 )

{

}

void s228::s221( const s164* s352, const wstring& s418 )
{
	if( !s352->s240( s229, this, s418 ) )
		throw s5( L"Symbol is not resolved: " + s229 );
}

s209* s228::s315( s164* ob )
{
	return 0;
}

s209* s228::s318( const s164* ob ) const
{
	if( s313.empty() )

		return s311;

	s164* ret = (s164*)((s164*)s311)->s335( *(size_t*)&s313[0] );
	for( size_t n = 1; n < s314; ++n )

		ret = (s164*)((s164*)ret->s216())->s335( *( (size_t*)&s313[0] + n ) );
	return ret->s216();
}

s209* s228::s319( s164* ob )
{
	if( s313.empty() )

		return (s209*)s311;

		ob = (s164*)s311;
	s164* ret = (s164*)ob->s335( *(size_t*)&s313[0] );
	for( size_t n = 1; n < s314; ++n )
		ret = (s164*)ret->s335( *( (size_t*)&s313[0] + n ) );
	return ret;
}

s209* s228::s315( s209** s316 )
{
	return 0;
}

s209* s228::s217( s209** s166, size_t s218 )
{
	return s318( NULL )->s217( s166, s218 );
}

s209* s228::s216()
{
	return s318( NULL )->s216();
}

bool s228::isTypeOf( const s209* classObj ) const
{
	return s318( NULL )->isTypeOf( classObj );
}

s163* s228::s224() const
{
	return new s228( *this );
}

void s228::s317( size_t off, const s209* s473 )
{
	s313.push_back( off );
	s314 = s313.size();
	s312 = s473;
}

void s228::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"DataRef : " << s229 << endl;

}

s288::s288( const s288& right )
	: s163( right.s192, s203 ), str( right.str )
{

}

s163* s288::s224() const
{
	return new s288( *this );
}

void s288::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << L"DataStub : " << str << endl;

}
const wstring s197 = L"";

s208 s421;

s164::s164( s160* s192, size_t type_, s198 pc/* = s199*/ )
	: s209( s192, pc ), s407( s197 ), //s330( s421 ),
	type( type_ ), s327( NULL ), ns( NULL )
{
	s325 = this;
}

s164::s164( const s164& s473 )
	: s209( s473.s192, s473.s213 ), s407( s473.s170 ),
	 s325( &s473 ), s327( s473.s327 ), //s330( s421 ),
	s420( s473.s420 ), ns( s473.ns )
{
	type = s473.type;
	s214 = s473.s214;
	if( s213 == s205 )
		s213 = s207;
	if( s473.s508 )
		s473.s508->s485( this );

	s473.s326.copy( s326, this, NULL, s208::s61 );
	for( size_t n = 0; n < s420.size(); ++n )
		s328.push_back( s326.get( s420[n] ) );
}

s164::s164( const wstring& s296, s160* s192, s198 pc )
	: s209( s192, pc ), s170( s296 ), s407( s197 ),
		s327( NULL ), ns( NULL )//, s330( *new s208() )
{
	s325 = this;
}

s164::s164( s161& s370, s160* s192, s198 pc, s164* ns_, s453 am, 
	s476& cl, s477& cnl, s478& al )
	: s209( s192, pc ), s170( s370.s190() ), s407( s370.s191() ),
		s327( NULL ), ns( ns_ ),  s326( am ), s508( NULL ) //,s330( *new s208() )
{
	if( s170.find( L" " ) != string::npos )
		throw s5( L"Malformed class name: " + s170 );
	s325 = this;

	if( pc == s205 ) {
		wstring anc = L"";
		try {
			const s161& ancNam = s370.s184( s96::s127 );
			anc = ancNam.s183();
		}
		catch( s5& e ) {
			if( e.which() != (uint32_t)s5::s6::s12 )
				throw e;
		}
		cnl.push_back( make_pair( s370.s191(), anc ) );

		if( cl.find( s370.s191() ) != cl.end() )
			throw s5( L"class already exists: " + s370.s191() );

		cl.insert(make_pair(s370.s191(), this));
	}
	if( al.find( s370.s191() ) != al.end() )
		throw s5( L"object already exists: " + s370.s191() );
	al.insert(make_pair(s370.s191(), &s370));

	s239( L"proto" );
	s161::s167& s410 = s370.s185();
	s161::s167::iterator it = s410.begin();
	vector<pair<wstring,wstring>> vswap;
	for( ; it != s410.end(); ++it ) {
		if( it->second->s189() == s129 ) {
			if( it->first == s96::s127 ) {
				s481 = it->second->s183();

			}
		}
		else if( it->second->s189() == s131 ) {

			wstring s400 = it->first;
			s246 pv = s249;
			am = s455;
			
			size_t seppl = s400.find_first_of( s25::s26 );
			if( seppl != string::npos ) {
				vector<wstring> vres;
				s25::s35( it->first, wstring( 1, s400[seppl] ), vres );
				if( vres.size() > 3 )
					throw s5( L"malformed block name: " + it->first );
				if( vres[0] == s96::s115 || vres.size() == 3 ) {
					pc = s205;
					if( vres.size() == 3 ) {
						if( vres[0] == s96::s457 )
							am = s454;
						else if( vres[0] == s96::s459 )
							am = s456;
						else if( vres[0] != s96::s458 )
							throw s5( L"invalid access mode name: " + it->first );
						s400 = vres[2];
					}
					else
						s400 = vres[1];

					if( s410.find( s400 ) != s410.end() )
						throw s5( L"duplicated object name: " + it->first );
					it->second->s186( s400 );
	
					vswap.push_back( make_pair( it->first, s400 ) );
				}
				else if( vres[0] == L"access" && ( vres[1] == L"allow" || vres[1] == L"deny" )) {
					if( vres[1] == L"allow" )
						pv = s248;
					pc = s206;
				}
				else
					throw s5( L"unknown object type: " + vres[0] );
			}
			if( pc == s206 ) {

				s326.s281( pv, it->second );
			}
			else {

				s164* ob = new s164( *it->second, s192, s205, this, am, cl, cnl, al );
				s326.s273( ob->s191(), ob );
			}
		}
	}
	for( size_t n = 0; n < vswap.size(); ++n ) {
		auto it = s410.find( vswap[n].first );
		s410.insert(make_pair(vswap[n].second, it->second ));
		s410.erase( it );
	}
}

s209* s164::s230( s161& s370, const wstring& s226 )
{

	return s422( s370, s226 );
}

s209* s164::s230( const wstring& val, const wstring& s254 )
{
	if( s213 == s205 )
		if( !ns->s337( s170, s254 ) )
			throw s5( L"Class '" + s170 + L"' is not accessible from '" 
				+ s254 + L"'." );
	s161 q( L"", val );
	return s230( q, s254);
}

void s164::s235( size_t type_ )
{
	type = type_;
}

void s164::s484( const s208& s166 )
{

}

bool
s164::isTypeOf( const s209* classObj ) const
{
	if( classObj->s215() == s215() )
		return true;
	if( s508 )
		return s508->isTypeOf( classObj );
	return false;
}

void s164::s65( s161& s370 )
{
	s161::s167& s410 = s370.s185();
	s161::s167::iterator it = s410.begin();
	for( ; it != s410.end(); ++it ) {
		s161* node = it->second;
		if( node->s189() == s130 ) {
			s324* func = s324::s354( *node, s192, this,
				node->s191(), s170 );
			s326.s273( func->s191(), func );
			s328.push_back( func );
			s420.push_back( func->s191() );
		}
		else if( node->s189() == s129 ) {
			wstring nam = node->s191();
			if( nam == s96::s110 )
				s423( *node );
			else if( nam == s96::s127 )
				s483( *node );
			else {
				s209* dv = s192->s379( node->s183(), s170 );
				dv->s239( node->s191() );
				try {
					s326.s273( node->s191(), dv );
				}
				catch( s5& e ) {
					if( e.which() == (uint32_t)s5::s6::s10 ) {
						e.addInfo( L"Symbol already defined: " + s170 + L"::" + node->s191() );
					}
					throw e;
				}
				s328.push_back( dv );
				s420.push_back( node->s191() );
			}
		}
		else if( node->s189() == s131 ) {

			if( 0 && it->first.find( L"access" ) != 0 ) {
				s164* ob = (s164*)s326.get( it->first );
				ob->s65( *it->second );
			}
		}
		else if( node->s189() == s132 ) {

		}
	}
}

void s164::s221( const wstring& s220 )
{
	if( s481.size() ) {
		s508 = (s164*)s192->s384( s481, s220 );
		s508->s327->copy( *s327 );
	}

	if( s327 )
		s327->s221( s192, s170 );
	else
		s327 = s325->s327;

	s326.s221( s220, (s213 == s205));

	if( s326.s67( s96::s106 ) ) {
		vector<s210*> s166;

		s166.push_back( this );
		s324* p = (s324*) s326.get( s96::s106 );
		p->s221( s220 );
		p->s217( (s209**)&s166[0], 1 );
	}
}

void s164::s485( s164* desc ) const
{
	if( s508 )
		s508->s485( desc );

}

void s164::s423( s161& s370 )
{
	if( !s327 )
		s327 = new s284();
	s327->s285( s370.s183() );

	return;

}

void s164::s424( const wstring& s226,	vector<wstring>& res )
{
	s326.s266( s226, res );

}

void s164::s482( const wstring& nam, const wstring& s418 )
{
	if( !s327 )
		s327 = new s284();
	s327->s482( nam, s192, s418 );
}

void s164::s483( s161& s370 )
{

	s508 = (s164*)s192->s384( s481, s170 );
}

bool s164::s240( const wstring& sym_, 
																s228* ref, const wstring& s226 ) const
{
	bool ret = false;
	wstring s409 = sym_;
	size_t pl = s409.find( L"." );
	if( pl != string::npos ) {
		s409 = sym_.substr( pl + 1 );
		wstring s446 = sym_.substr( 0, pl );
		s164* ob = (s164*)s336( s446, s226, false );
		if( ob ) {

			ret = ob->s240( s409, ref, s226 );
		}
		else {
			ret = s327->s240( s409, ref );

		}
	}
	else {
		s164* ob = (s164*)s336( s409, s226, false );
		if( ob ) {
			if( !ref->s321() )
				ref->s322( ( s209* )this );

			ref->s317( s333( s409 ), ob );
			ret = true;
		}
		else {
			if( s327 )
				ret = s327->s240( s409, ref );

		}
	}

	return ret;
}

s209* s164::s334( const std::wstring& s170, const std::wstring& s226 )
{
	return s326.get( s170 );
}

size_t s164::s333( const std::wstring& memname ) const
{
	for( size_t n = 0; n < s328.size(); ++n ) {
		if( s420[n] == memname )
			return n;
	}
	throw s5( L"3: Symbol does not exist: " + memname );
}

s163* s164::s335( size_t off )
{
	return s328[off];
}

s163* 
s164::s336( const wstring& s409, const wstring& s226, 
											bool thr/*= true*/ ) const
{
	size_t pl = s409.find( L"::" );
	if( pl != string::npos ) {
		wstring smod = s409.substr( 0, pl );
		wstring sym1 = s409.substr( pl + 2 );
		s164* mod = (s164*)s326.get( smod, true );
		return mod->s336( sym1, s226, thr );
	}
	wstring sym1 = s409;
	if( s409.size() > 2 && ( s409.find( L"()" ) == s409.size() - 2 ) )
		sym1 = s409.substr( 0, s409.size() - 2 );
	s163* ret = s326.get( sym1, false );
	if( !ret && thr )
		throw s5( L"4: Symbol does not exist: " + s409, 
			(uint32_t)s5::s6::s12 );
	if( ret && !s337( sym1, s226 ) ) {
		if( thr )
			throw s5( L"4: Symbol not found: " + s409,
				(uint32_t)s5::s6::s12 );
		ret = NULL;
	}
	return ret;
}

bool s164::s337( const wstring& s409, const wstring& s220 ) const
{
	return s326.s283( s409, s220 );
}

size_t s164::s233( const wstring& s234 ) const
{
	s209* s425 = s326.get( s234 );
	size_t ret = s425->s219();
	if( ret == 0 ) {
		s425->s221( s191() );
		ret = s425->s219();
	}
	return ret;
}

s209* s164::s422( s161& s370, const std::wstring& s226 )
{
	vector<wstring> s316;
	vector<s163*> s166;
	s164* ret = new s164( *this );
	size_t pos = s370.s183().find( L"(" );
	size_t pos_ = pos;
	s161::s180( s370.s183(), pos, s316 );
	if( s316.size() ) {
		s324* tdInit = (s324*)s326.get( s96::s105, false );
		if( !tdInit )
			throw s5( L"Arguments passed to a class without init function." );
		else {
			wstring str = s370.s183();
			if( str[pos_ + 1] != L' ' )
				str.insert( pos_ + 1, L" " );
			str = str.substr( pos_ ).insert( 1, s96::s105 );
			s161 s465( s96::s106, s55( str ) );
			s426* cs = (s426*)s163::s225( s465, s192, ret, s226 );

			s324* td = s324::s356( 
				cs, s192, ret, ret, s170 );


			ret->s326.s273( s96::s106, td );
		}
	}

	return ret;
}

s209* s164::s237() const
{
	return new s164( *this );
}

size_t s164::s219() const
{
	return type;
}

std::wstring s164::s190() const
{
	return /*s169 + L"::" +*/ s170;
}

s209* s164::s217( s209** s166, size_t s218 )
{
	return s331->s217( s166, s218 );
}

s324* s164::s299( const std::wstring& s296, const std::wstring& s226,
	bool thr /*= true*/ ) const
{

	s228 ref( s296, s192 );
	if( !s240( s296, &ref, s226 ) )
		return false;
	return (s324*)ref.s319( NULL );
}

s163* s164::s224() const
{
	return new s164( *this );
}

void s164::s238( s210* p ) const
{

	throw s5( L"" );
	vector<wstring> fields;
	s326.s277( fields );

	for( size_t n = 0; n < fields.size(); n++ )
		((s209*)s326.get( fields[n] ))->s238( p );
}

wstring s164::to_wstring() const
{
	return L"";
}

void s164::s196( std::wostream* pd, int ind /*=0*/ ) const
{

	std::wostream& buf = *pd;
	buf << endl << s25::fill_n_ch( L' ', ind ) << s170 << L" : " << L"Object" << endl;
	s326.s196( pd, ind + INDSTEP );

}
Transd* s324::s354( s161& s370, s160* s192, s164* obj,
	const wstring& s170, const wstring& s418 )
{
	s161::s167& s410 = s370.s185();
	size_t s427 = s410.size();
	vector<s210*> s166;
	for( size_t n = 0; n < s427; ++n ) {
		s161::s167::iterator it = s410.find( std::to_wstring( n ) );
		s166.push_back( s163::s225( *it->second, s192, obj, s418 ) );
	}
	Transd* ret = NULL;
	size_t seppl = s170.find_first_of( s25::s26 );
	if( seppl != string::npos ) {
		vector<wstring> vres;
		s25::s35( s170, wstring( 1, s170[seppl] ), vres );
		if( vres.size() > 2 )
			throw s5( L"malformed function name: " + s170 );
		if( vres[0] == s96::s108 ) {
			ret = new s499( s192, obj, NULL, s166 );
			ret->s170 = vres[1];
		}
		else if( vres[0] == s96::s109 ) {
			ret = new s324( s192, obj, NULL, s166 );
			s164* pAnc = (s164*)s192->s384( obj->s480(), s418 );
			( (s499*)pAnc->s299( vres[1], s418 ) )->s500( obj->s219(),
																		ret );
			ret->s170 = vres[1];
			ret->s497( s490 );
		}
		else
			throw s5( L"malformed function name: " + s170 );
	}
	else {
		ret = new s324( s192, obj, NULL, s166 );
		ret->s170 = s170;
	}

	return ret;
}

s426* s324::s355( s161& s370, s160* s192, s164* obj, const wstring& s418 )
{
	s161::s167& s410 = s370.s185();
	size_t s427 = s410.size();
	vector<s210*> s166;
	for( size_t n = 0; n < s427; ++n ) {
		s161::s167::iterator it = s410.find( std::to_wstring( n ) );
		s166.push_back( s163::s225( *it->second, s192, obj, s418 ) );
	}

	wstring s357 = s370.s183();
	if( s357.find( L"::" ) != string::npos ) {
		wstring s428 = s357.substr( 0, s357.rfind( L"::" ) );
		s357 = s357.substr( s428.size() + 2 );
		s161* p = new s161( s428 );
		s166.insert( s166.begin(), s163::s225( *p, s192, obj, s418 ) );
	}

	return new s426( s357, s166 );
}

s499::s499( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l )
	: s324( s192, s429, s352, l )
{
	virtType = s489;
}

void s499::s500( size_t typ, s324* pOvr )
{
	types.push_back( typ );
	ptrs.push_back( pOvr );
}

s209*
s499::s217( s209** s316, size_t s427 )
{
	if( s346 == s345 && s316[0]->s219() != type ) {
		size_t type = s316[0]->s219();
		size_t* pt = (size_t*)&types[0];
		for( size_t n = 0; n < types.size(); ++n ) {
			if( pt[n] == type )
				return ptrs[n]->s217( s316, s427 );
		}
		throw s5( L"dispatching failed" );
	}
	else {
		return s324::s217( s316, s427 );
	}
}


void s426::s221( const wstring& s226 )
{
	for( size_t n = 0; n < s166.size(); ++n ) {
		s166[n]->s221( s226 );
	}
}

s163* s426::s224() const
{
	return new s426( *this );
}

Transd* s324::s356( s426* cs, s160* s192, s164* s429,
	s164* s430, const wstring& s418 )
{
	wstring s357 = cs->s191();
	if( s357 == s137 )
		return s192->s377( cs->s191(), cs->s358(), s429, s430 );

	vector<s210*>& s432 = cs->s358();
	vector<s210*> s166;
	const s209* s431 = NULL;
	wstring s433 = s429->s190();
	s324* ret = NULL;
	s163* s435 = NULL;
	s163* s434 = NULL;

	for( size_t n = 0; n < s432.size(); ++n ) {
		s435 = s432[n];
		s198 pc = s435->s437();
		if( pc == s201 ) {
			s434 = s435;
			( (s228*)s434 )->s221( s430, s418 );
		}
		else {
			if( pc == s203 ) {
				s434 = s192->s379( ( (s288*)s435 )->Str(),
					( (s288*)s435 )->s471() );

			}
			else if( pc == s204 )
				s434 = s356( (s426*)s435, s192, s429, s430, s418 );
			else
				s434 = s435;

			s434->s221( s429->s191() );
		}
		s166.push_back( s434 );
	}

	s324* s440 = s192->s377( s357, s166, s429, s430 );
	if( s440 )
		return s440;

	s324* s438 = NULL;
	s324* s439 = NULL;
	s292 s338 = NULL;

	if( s166.empty() ) {
		s438 = s429->s299( s357, s433, false );
		if( !s438 )
			throw s5( L"Procedure is not resolved: " + s357 );
	}
	else {
		s434 = s166[0];
		if( s434->s437() == s201 ) {
			if( ( (s228*)s435 )->ValName() == s96::s107 )
				s434 = s429;
			s431 = (s209*)( (s228*)s434 )->s318( NULL );
		}
		else
			s431 = s434->s216();

		s198 s436 = s431->s437();

		if( s436 == s201 ) {
			s228* ref = (s228*)s431;
			s431 = ref->s223();
			s436 = s431->s437();
		}

		try {
			if( s436 == s207 || s436 == s206 )
				s439 = ( (s164*)s431 )->s299( s357, s433, false );
			else if( s436 == s200 )
				s338 = ( (s291*)s431 )->s299( s357 );
		}
		catch( s5& e ) {
			if( e.which() != (uint32_t)s5::s6::s12 )
				throw;
		}

		if( !s439 && !s338 )
			s438 = s429->s299( s357, s433, false );


		if( !( /*s440 ||*/ s338 || s438 || s439 ) )
			throw s5( L"Method is not resolved" );
	}

	if( s338 ) {

		ret = new s324( s192, s429, s430, s166, s338, s431->s233( s357 ) );
		ret->s346 = s342;

	}
	else if( s438 ) {

		ret = new s324( *(s324*)s438, s429, s430, s166 );
		ret->s346 = s343;

	}
	else if( s439 ) {
		s324* td = (s324*)s439->s224();
		s166.erase( s166.begin() );
		ret = new s324( *td, (s164*)s431, s430, s166 );
		delete td;
		if( s439->s498() == s489 )
			ret->s346 = s345;
		else
			ret->s346 = s344;

	}

	ret->s170 = s357;
	return ret;
}

s324::s324( s160* s192, s164* s441, s164* s442, const vector<s210*>& l )
	: s164( s192, 0, s202 ), s338( NULL ), s429( s441 ), s352( s442 ),
		virtType( s488 )
{
	size_t n = 0;
	for( ; n < l.size(); n += 2 ) {
		if( l[n]->s437() != s201 )
			break;
		s228* nam = (s228*)l[n];
		s209* ex = (s209*)l[n + 1];
		if( ex->s437() != s200 && ex->s437() != s207 && 
				ex->s437() != s206 && ex->s437() != s203 )
			throw s5( L"incorrect syntax for lambda parameter " + nam->ValName() +
				L"; should be a type constructor.", (uint32_t)s5::s6::s9 );
		s349.s273( nam->ValName(), ex );
		s326.s273( nam->ValName(), ex );
		s492.push_back( (s209*)ex );
		s328.push_back( (s209*)ex );
		s420.push_back( nam->ValName() );
	}

	s351.insert( s351.end(), l.begin() + n, l.end() );
}

s324::s324( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l,
	s292 s443, size_t s444 )
	: s164( s192, 0, s202 ), s338( s443 ), s352( s442 ), virtType( s488 )
{
	s214 = s444;
	s166 = l;
}

s324::s324( const s324& right, s164* s441, s164* s442,
				const vector<s210*>& s432 )
	: s164( right.s192, right.s214, right.s213 ), 

		s170( right.s170 ), s349( right.s349 ),
		s429( s441 ), s352( s442 ), virtType( s488 )
{

	s338 = right.s338;
	s346 = right.s346;
	s328 = right.s328;
	s420 = right.s420;
	s326 = right.s326;
	s492 = right.s492;

	if( s432.size() ) {
		s166.assign( s432.begin(), s432.end() );

		for( size_t n = 0; n < s166.size(); ++n )
			s349.s273( s420[n], (s209*)s166[n]/*->s216()*/, s208::s61 );
	}
	else
		s166.assign( right.s166.begin(), right.s166.end() );

	s351 = right.s351;
}

s324::~s324()
{
	for( size_t n = 0; n < s166.size(); ++n ) {
		delete s166[n];
	}
}

s426::s426( const std::wstring& s394, const std::vector<s210*>& l )
	: s163( NULL, s204 ), s357( s394 )
{
	s166.assign( l.begin(), l.end() );
}

s426::s426( const s426& right )
	: s163( right.s192, s204 ), s357( right.s357 )
{
	for( size_t n = 0; n < right.s166.size(); ++n ) {
		s166.push_back( right.s166[n]->s224() );
	}
}

void s324::s493(const std::wstring& s226)
{
	for( size_t n = 0; n < s492.size(); ++n ) {
		s163* fpar = s492[n];
		s198 pc = fpar->s437();
		if( pc == s203 ) {

		}
		else

			s492[n]->s221( s226 );

	}
}

void s324::s494(const std::wstring& s226)
{
	for( size_t n = 0; n < s166.size(); ++n ) {
		s163* s434 = s166[n];
		if( s434->s437() == s203 ) {
			s209* s435 = s192->s379( ( (s288*)s166[n] )->Str(),
					( (s288*)s166[n] )->s471() );
			s166[n] = s435;
		}
		else if( s434->s437() == s204 ) {
			s426* cs = new s426( *(s426*)s434 );
			s434 = s356( cs, s192, s429, this, s190() );
			s434->s221( s226 );
			s166[n] = s434;
		}
		if( s166[n]->s437() != s201 ) {
			if( !s338 && s346 != s341 ) {
				s328[n] = s166[n]->s216();
				s349.s273( s420[n], (s209*)s328[n], s208::s61 );
			}
			s350.push_back( s166[n]->s216() );
		}
		else {
			if( !s338 && s346 != s341 ) {
				s328[n] = s166[n];
				s349.s273( s420[n], (s209*)( (s228*)s166[n] )->Root(), s208::s61 );
			}
			s350.push_back( NULL );
		}
		if( n < s328.size() && !( (s209*)s328[n] )->isTypeOf( (s209*)s492[n] ) )
			throw s5( L"wrong argument's type" );
	}
}

void s324::s221( const wstring& s226 )
{

	if( s429 && ( s429->s437() == s206 || s429->s437() == s205 ) ) {
		s493( s226 );
		if( s429->s437() == s205 )
			return;
	}

		s496( s226 );

	if( !s338 ) {
		for( size_t n = 0; n < s351.size(); ++n ) {
			s426* cs = new s426( *(s426*)s351[n] );
			s351[n] = s356( cs, s192, s429, this, s429->s191() );
		}
		for( auto it : s351 ) {
			if( ((s324*)it)->s346 != s344 && 
				( (s324*)it )->s346 != s345 )
			it->s221( s226 );
		}
		if( !s214 && s351.size() )
			s214 = s351.back()->s215();
		else if( s170 == s134 )
			s214 = s350[1]->s215();
	}
	else {
		s163* s434 = s166[0];
		s198 s436 = s434->s437();
		if( s436 == s201 ) {
			s228* ref = (s228*)s434;
			s209* pobj = (s209*)ref->s223();
			s436 = pobj->s437();
			s214 = ( (s291*)pobj )->s233( s170 );
		}
	}
	if( s214 ) {
		s447 = s192->s379( s215(), s226 );
		s350.insert( s350.begin(), s447 );

		if( s166.size() ) {
			s348 = (s210**)&s166[0];
			s462 = s166.size();
			s347 = &s350[0];
			s218 = s350.size();
		}
		else {
			s348 = NULL;
			s347 = NULL;
			s462 = s218 = 0;
		}
	}
}

void s324::s495( const vector<s210*>& l )
{

	s166.clear();

	s166.assign( l.begin(), l.end() );
}

void s324::s496( const wstring& s226 )
{
	for( size_t n = 0; n < s166.size(); ++n ) {
		s163* s434 = s166[n];
		if( s434->s437() == s203 ) {
			s209* s435 = s192->s379( ( (s288*)s166[n] )->Str(),
				( (s288*)s166[n] )->s471() );
			s166[n] = s435;
		}
		else if( s434->s437() == s204 ) {
			s426* cs = new s426( *(s426*)s434 );
			s434 = s356( cs, s192, s429, this, s190() );
			s434->s221( s226 );
			s166[n] = s434;
		}
		if( s166[n]->s437() != s201 ) {
			if( !s338 && s346 != s341 ) {
				s328[n] = s166[n]->s216();
				s349.s273( s420[n], (s209*)s328[n], s208::s61 );
			}
			s350.push_back( s166[n]->s216() );
		}
		else {
			if( !s338 && s346 != s341 ) {
				s328[n] = s166[n];
				s349.s273( s420[n], (s209*)( (s228*)s166[n] )->s318( NULL ), s208::s61 );
			}
			s350.push_back( NULL );
		}
		if( n < s328.size() && !( (s209*)s328[n] )->isTypeOf( (s209*)s492[n] ) )
			throw s5( L"wrong argument's type" );
	}
}

s209*
s324::s217( s209** s316, size_t s427 )
{
	s209* ret = NULL;

	size_t shift = 0;
	if( s346 == s344 || s346 == s342 || s346 == s341 )
		shift = 1;

	for( size_t n = 0; n < s462; ++n ) {
		if( *( s348 + n ) ) {
			s198 pc = ( ( s210* )*( s348 + n ) )->s437();
			if( pc == s201 )
				*( s347 + n + shift ) =
				(s209*)( ( s228* )*( s348 + n ) )->s318( (s164*)s316 + n );
			else if( pc == s202 )
				*( s347 + n + shift ) =
				(s209*)( ( s324* )*( s348 + n ) )->s217( s316, s427 );
		}
	}

	if( s338 ) {
		s338( s347, s218 );
		ret = s350[0];
	}
	else {
		for( size_t n = 0; n < s351.size(); ++n )
			ret = s351[n]->s217( s347, s218 );
	}
	return ret;
}

bool
s324::s240( const wstring& s296, s228* ref,
	const wstring& s226 ) const
{
	bool ret = false;
	wstring s170 = s296;
	size_t pl = s170.find( L"." );
	if( pl == string::npos ) { //a

		s228* ob = (s228*)s349.get( s170, false );
		if( !ob ) {

			if( s352 )
				ret = s352->s240( s170, ref, s226 );
			if( !ret ) {
				ret = s429->s240( s170, ref, s226 );
				if( !ret )
					ret = s192->s240( s170, ref, s226 );
			}
		}
		else {
			size_t off = s333( s170 );
			ref->s317( off, s166[off]->s216()->s223() );
			ref->s322( (s209*)this /*(s210**)&s166[off]*/ );

			ret = true;
		}
	}
	else {// a.y
		s170 = s296.substr( pl + 1 );
		wstring s446 = s296.substr( 0, pl );
		s163* ob = s349.get( s446, false );
		if( !ob ) {
			ret = s429->s240( s296, ref, s226 );
			if( !ret && s352 )
				ret = s352->s240( s170, ref, s226 );
		}
		else {
			size_t off = s333( s446 );
			ref->s317( off, NULL );
			ret = ob->s223()->s240( s170, ref, s226 );
			ref->s322( (s209*)this );
		}
	}

	return ret;
}

s163* 
s324::s335( size_t off )
{
	return s166[off];
}

s163* s324::s224() const
{
	s324* ret = new s324( *this );
	return ret;
}

s360::s360( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s137 )
{
	s170 = s137;

	size_t n = 0;
	for( ; n < l.size(); n += 2 ) {
		if( l[n]->s437() != s201 )
			break;
		s228* nam = (s228*)l[n];
		s209* typ = (s209*)l[n + 1];

		s349.s273( nam->ValName(), typ );
		s166.push_back( typ );
		s328.push_back( typ );
		s420.push_back( nam->ValName() );
	}

	s351.insert( s351.end(), l.begin() + n, l.end() );
	type = l.back()->s219();
}

void
s360::s221( const wstring& s226 )
{
	s163* s435 = NULL;
	s163* s434 = NULL;

	for( size_t n = 0; n < s166.size(); ++n ) {
		s435 = s166[n];
		if( s435->s437() == s203 ) {
			s434 = s192->s379( ( (s288*)s435 )->Str(),
				( (s288*)s435 )->s471() );
		}
		else if( s435->s437() == s204 ) {
			s426* cs = new s426( *(s426*)s435 );
			s434 = s356( (s426*)s435, s192, s429, this, s190() );
		}
		else
			s434 = s435;
		s434->s221( s226 );
		s166[n] = s434;
		s350.push_back( s166[n]->s216() );
	}
	for( size_t n = 0; n < s351.size(); ++n ) {
		s426* cs = new s426( *(s426*)s351[n] );
		s351[n] = s356( cs, s192, s429, this, s170 );
	}
	for( auto it : s351 )
		it->s221( s226 );

	s214 = s351.back()->s215();
}

s209*
s360::s217( s209** s316, size_t s427 )
{
	s209* ret = NULL;
	for( size_t n = 0; n < s166.size(); ++n ) {
		s166[n]->s217( NULL, 0 );
	}

	for( size_t n = 0; n < s351.size(); ++n )
		ret = s351[n]->s217( s316, s427 );
	return ret;
}

s163* 
s360::s445( const std::wstring& s296, s228* ref,
	const std::wstring& s226 ) const
{
	throw;
	s163* ret = NULL;
	wstring s170 = s296;
	size_t pl = s170.find( L"." );
	if( pl == string::npos ) { //a

		s228* ob = (s228*)s349.get( s170, false );
		if( !ob )
			s429->s240( s170, ref, s226 );
		else {
			size_t off = s333( s170 );
			ref->s317( off, s166[off]->s216()->s223() );
			ref->s322( ( s209* )this );

		}
	}
	else {// a.y
		s170 = s296.substr( pl + 1 );
		wstring s446 = s296.substr( 0, pl );
		s163* ob = s349.get( s446, false );
		if( !ob ) {
			s429->s240( s296, ref, s226 ); // throws if not successful

		}
		else {
			size_t off = s333( s446 );
			ref->s317( off, NULL );
			ob->s223()->s240( s170, ref, s226 );
			ref->s322( ( s209* )this );
		}
	}

	return ret;
}

s362::s362( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s147 )
{
	s166.assign( l.begin(), l.end() );
}

s209* s362::s217( s209** s166, size_t s218 )
{
	return NULL;
}

s363::s363( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s147 )
{
	s166.assign( l.begin(), l.end() );
	s214 = s302::s303();
}


s209* s363::s217( s209**, size_t )
{
	*( (s302*)s447 )->Ptr() = 1;
	for( size_t n = 0; n < s166.size(); ++n ) {
		if( !( bool )*( (s210*)( s166[n]->s217( 0, 0 ) ) ) ) {
			*( (s302*)s447 )->Ptr() = 0;
			return s447;
		}
	}

	return s447;
}

s364::s364( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s134 )
{
	s166.assign( l.begin(), l.end() );
}

void s364::s221( const wstring& s226 )
{
	s324::s221( s226 );
	s214 = s166[1]->s215();

}

s209* s364::s217( s209**, size_t )
{
	size_t npairs = s462 / 2;
	for( size_t n = 0; n < npairs; ++n ) {
		if( ( bool )*( (s210*)( s166[n]->s217( 0, 0 ) ) ) )
			return s166[2*n+1]->s217( 0, 0 );
	}
	if( s462 % 2 )
		return s166[s462-1]->s217( 0, 0 );
	return &nullobject;
}

s366::s366( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s158 )
{
	s170 = s158;
	s166.push_back( l[0] );
	s166.push_back( l[1] );

	s351.insert( s351.end(), l.begin() + 2, l.end() );

}

s366::s366( s160* s192 )
	: s324( s192, NULL, NULL, s341, s158 )
{
	s170 = s158;
}

void
s366::s221( const wstring& s226 )
{
	s163* s435 = NULL;
	s163* s434 = NULL;

	for( size_t n = 0; n < s166.size(); ++n ) {

		if( !n )
			condition = (s324*)s166[n];
		else
			step = (s324*)s166[n];
		s350.push_back( s166[n]->s216() );
	}
	/*for( size_t n = 0; n < s351.size(); ++n ) {
		s426* cs = new s426( *(s426*)s351[n] );
		s351[n] = s356( cs, s192, s429, this, s170 );
	}
	for( auto it : s351 )
		it->s221( this, s226 );*/

	s214 = s351.back()->s215();
}

s209*
s366::s217( s209** s316, size_t s427 )
{
	s209* ret = NULL;
	while( 1 ) {
		if( (bool)*condition->s217( 0, 0 ) == false )
			return ret; // s447;

		for( size_t n = 0; n < s351.size(); ++n )
			ret = s351[n]->s217( s316, s427 );

		step->s217( 0, 0 );
	}
	return ret;
}

s365::s365( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s155 )
{
	if( l.empty() )
		throw s5( L"Wrong numbers of arguments" );
	s166.assign( l.begin(), l.end() );
	s214 = s306::s303();
}

s365::s365( s160* s192 )
	: s324( s192, NULL, NULL, s341, s155 )
{
	s214 = s306::s303();
}

void s365::s221( const wstring& s226 )
{
	s324::s221( s226 );
	return;
	s163* s435 = NULL;
	s163* s434 = NULL;

	for( size_t n = 0; n < s166.size(); ++n ) {
		s435 = s166[n];
		if( s435->s437() == s203 ) {
			s434 = s192->s379( ( (s288*)s435 )->Str(),
				( (s288*)s435 )->s471() );
		}
		else if( s435->s437() == s204 )
			s434 = s356( (s426*)s435, s192, s429, this, s190() );
		else
			s434 = s435;
		s434->s221( s226 );
		s166[n] = s434;
		s350.push_back( s166[n]->s216() );
	}
	for( size_t n = 0; n < s351.size(); ++n ) {
		s426* cs = new s426( *(s426*)s351[n] );
		s351[n] = s356( cs, s192, s429, this, s170 );
	}
}

s209* s365::s217( s209** s432, size_t s218 )
{
	for( size_t n = 0; n < s166.size(); ++n ) {
		s209* res = s166[n]->s217( s432, s218 );
		wcout << res->to_wstring();
	}


	return &nullobject;
}

s209* s365::s224()const
{
	s209* ret = new s365( *this );
	return ret;
}

s367::s367( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l )
	: s324( s192, s441, s442, s341, s159 )
{
	if( l.size() != 1 )
		throw s5( s159 + L"(): wrong numbers of arguments" );
	s166.assign( l.begin(), l.end() );
	s214 = s306::s303();
}

s367::s367( s160* s192 )
	: s324( s192, NULL, NULL, s341, s159 )
{
	s214 = s306::s303();
}


s209* s367::s217( s209** s432, size_t s218 )
{
	s209* res = s166[0]->s217( s432, s218 );


	return &nullobject;
}

s209* s367::s224() const
{
	s209* ret = new s367( *this );
	return ret;
}

s209* s364::s224() const
{
	s209* ret = new s364( *this );
	return ret;
}

s209* s362::s224() const
{
	s209* ret = new s362( *this );
	return ret;
}

s209* s363::s224()const
{
	s209* ret = new s363( *this );
	return ret;
}

s209* s360::s224()const
{
	s209* ret = new s360( *this );
	return ret;
}

s209* s366::s224()const
{
	s209* ret = new s366( *this );
	return ret;
}
s160::s160()
	: s164( this, 0, s199 ), s370( s131, L"", L"global" ), s371( s368 )
{	
}

s160::~s160()
{

}

void s160::s272()
{

}

void s160::s221()
{
	s449.s182();
}

void s375( const std::wstring& asmName, vector<wstring>& res ) 
{
	vector<s3<s57>> vobj;
	s80( asmName, vobj, s96::s452 );
	res.push_back( L"" );
	for( size_t n = 0; n < vobj.size(); n++ ) {
		wstring s400 = s161::s194( *vobj[n], s96::s122 );

		if( s400 == s96::s117 ) {
			const vector<s56>& s73 = (*vobj[n]).s69( s96::s124 )->s77();
			for( size_t n = 0; n < s73.size(); n++ )
				res.push_back( s73[n]->s79() );
			if( ( *vobj[n] ).s67( s96::s123 ) )
				res[0] = ( *vobj[n] ).s69( s96::s123 )->s79();
		}
	}
	if( res.size() == 1 )
		res.push_back( asmName );
}

void s376( s160* s192, s161& s370, s208& syms,
											s476& cl, s477& cnl, s478& al )
{
	s161::s167& s410 = s370.s185();
	s161::s167::iterator it = s410.begin();
	s453 am = s455;
	for( ; it != s410.end(); ++it ) {
		s198 pc = s206;
		if( it->first.find( L" " ) != string::npos ) {
			vector<wstring> vres;
			s25::s35( it->first, L" ", vres );
			if( vres.size() > 3 )
				throw s5( L"malformed block name: " + it->first );
			wstring s400 = vres[1];
			size_t idx = vres.size() - 2;
			if( vres[idx] == s96::s115 )
				pc = s205;
			else if( vres[idx] == s96::s116 )
				pc = s206;
			else
				throw s5( L"unknown object type: " + vres[0] );
			if( vres.size() == 3 ) {
				if( vres[0] == s96::s457 )
					am = s454;
				else if( vres[0] == s96::s459 )
					am = s456;
				else if( vres[0] != s96::s458 )
					throw s5( L"invalid access mode name: " + it->first );
				s400 = vres[2];
			}
			it->second->s186( s400 );
		}


		s164* ob = new s164( *it->second, s192, pc, s192, am, cl, cnl, al );

		syms.s273( ob->s191(), ob );
	}
}

void s160::s502( const wstring& s385 )
{
	vector<wstring> srcs;
	s161 _ast;
	s375( s385, srcs );
	vector<s3<s57>> vobj;
	for( size_t n = 1; n < srcs.size(); n++ ) {
		vobj.clear();
		s80( srcs[n], vobj, s96::s452 );
		for( size_t m = 0; m < vobj.size(); m++ )
			if( s161::s187( *vobj[m], s96::s118 ) == s96::s118 )
				_ast.s181( *vobj[m] );
	}
	s501( _ast );
	s371 = srcs[0];
}

void s160::s501( s161& _ast )
{
	s208 syms;

	s161::s167& s410 = _ast.s185();
	s161::s167::iterator it = s410.begin();
	s478 m1;
	s477 s510;
	s476 classList;
	vector<wstring> s511;


	s376( this, _ast, syms, classList, s510, m1 );

	size_t s509 = s510.size();
	while( s511.size() < s509 ) {
		size_t s512 = s510.size();
		for( size_t n = 0; n < s510.size(); ++n ) {
			if( s510[n].second.empty() ||
				std::find( s511.begin(), s511.end(), s510[n].second )
				!= s511.end() ) {
				s511.push_back( s510[n].first );
				s510.erase( s510.begin() + n-- );
				continue;
			}
		}
		if( s512 == s510.size() )
			throw s5( L"unresolved parent class: " + s510[0].second );
	}

	for( size_t n = 0; n < s511.size(); ++n )
		if( s449.s67( s511[n] ) )
			throw s5( L"class name already exists: " + s511[n] );

	for( size_t n = 0; n < s511.size(); ++n )
		s449.s252( classList[s511[n]] );

	s326.s181( syms );


	for( size_t n = 0; n < s511.size(); ++n ) {
		s164* ob = (s164*)s449.get( s511[n], false );
		if( ob )
			ob->s65( *m1[s511[n]] );
	}

	for( it = m1.begin(); it != m1.end(); ++it ) {
		s164* ob = (s164*)syms.get( it->first, false );
		if( ob && ob->s437() == s206 )
			ob->s65( *it->second );
	}


	syms.s221( s191(), false );
}

void s160::s503( const wstring& s385 )
{
	s373( s385 );


	s161::s167& s410 = s370.s185();
	s161::s167::iterator it = s410.begin();
	s478 m1;
	s477 s510;
	s476 classList;
	vector<wstring> s511;
	s453 am = s455;
	for( ; it != s410.end(); ++it ) {
		s198 pc = s206;
		if( it->first.find( L" " ) != string::npos ) {
			vector<wstring> vres;
			s25::s35( it->first, L" ", vres );
			if( vres.size() > 3 )
				throw s5( L"malformed block name: " + it->first );
			wstring s400 = vres[1];
			size_t idx = vres.size() - 2;
			if( vres[idx] == s96::s115 )
				pc = s205;
			else if( vres[idx] == s96::s116 )
				pc = s206;
			else
				throw s5( L"unknown object type: " + vres[0] );
			if(vres.size() == 3) {
				if( vres[0] == s96::s457 )
					am = s454;
				else if( vres[0] == s96::s459 )
					am = s456;
				else if( vres[0] != s96::s458 )
					throw s5( L"invalid access mode name: " + it->first );
				s400 = vres[2];
			}
			it->second->s186( s400 );
		}
		m1.insert( make_pair( it->second->s191(), it->second ) );

		s164* ob = new s164( *it->second, this, pc, this, am, classList, s510, m1 );

			s326.s273( ob->s191(), ob );

	}

	size_t s509 = s510.size();
	while( s511.size() < s509 ) {
		size_t s512 = s510.size();
		for( size_t n = 0; n < s510.size(); ++n ) {
			if( s510[n].second.empty() ||
				std::find( s511.begin(), s511.end(), s510[n].second )
				!= s511.end() ) {
				s511.push_back( s510[n].first );
				s510.erase( s510.begin() + n-- );
				continue;
			}
		}
		if( s512 == s510.size() )
			throw s5( L"unresolved parent class: " + s510[0].second );
	}

	for( size_t n = 0; n < s511.size(); ++n )
		if( s449.s67( s511[n] ) )
			throw s5( L"class name already exists: " + s511[n] );

	for( size_t n = 0; n < s511.size(); ++n )
		s449.s252( classList[s511[n]] );


	for( size_t n = 0; n < s511.size(); ++n ) {
		s164* ob = (s164*)s449.get( s511[n], false );
		if( ob )
			ob->s65( *m1[s511[n]] );
	}

	for( it = m1.begin(); it != m1.end(); ++it ) {
		s164* ob = ( s164* ) s326.get( it->first, false );
		if( ob && ob->s437() == s206 )
			ob->s65( *it->second );
	}

	s326.s221( s191(), false );
}

void s160::s504( s57& obj )
{
	s161 _ast;
	_ast.s181( obj );

	s501( _ast );
}


s209* s160::run()
{
	if( s371.empty() )
		throw s5( L"unknown entry point ", (uint32_t)s5::s6::s9 );

	vector<wstring> l;
	return callFunc( s371, l );
}

s209* s160::callFunc( const wstring& s357, vector<wstring>& l )
{
	size_t pl = s357.find( L"::" );
	if( pl == string::npos || s357.find( L"::", pl + 1 ) != string::npos )
		throw s5( L"unknown entry point: " + s357, (uint32_t)s5::s6::s9 );
	wstring s513 = s357.substr( 0, pl );
	wstring s514 = s357.substr( pl + 2 );

	s164* mod = (s164*)s326.get( s513 );

	s324* s372 = (s324*)mod->s336( s514, L"::" );
	vector<s210*> s166;
	for( size_t n = 0; n < l.size(); n++ ) {
		s161 s465( l[n] );
		s426* cs = s324::s355( s465, this, mod, mod->s190() );
		s166.push_back( cs );
	}
	s372->s495( s166 );
	s210* pr = s372->s216();
	if( !pr )
		s372->s221( mod->s190() );
	else
		s372->s496( mod->s190() );

	return s372->s217();
}

void s160::s373( const std::wstring& s394 )
{
	vector<s3<s57>> vobj;
	s80( s394, vobj, s96::s452 );
	for( size_t n = 0; n < vobj.size(); n++ ) {
		wstring s400 = s161::s194( *vobj[n], s96::s122 );

		if( s400 == s96::s117 ) {
			s374( *vobj[n] );
			if( s369.empty() )
				s369.push_back( s394 );
		}
	}
	if( s369.empty() )
		s369.push_back( s394 );
	for( size_t n = 0; n < s369.size(); n++ ) {
		vobj.clear();
		s80( s369[n], vobj, s96::s452 );
		for( size_t m = 0; m < vobj.size(); m++ )
			if( s161::s187( *vobj[m], s96::s118 ) == s96::s118 )
				s370.s181( *vobj[m] );
	}
}

void s160::s374( const s44::s57& obj )
{
	const vector<s56>& s73 = obj.s69( s96::s124 )->s77();
	for( size_t n = 0; n < s73.size(); n++ )
		s369.push_back( s73[n]->s79() );
	if( obj.s67( s96::s123 ) )
		s371 = obj.s69( s96::s123 )->s79();
	return;
	vector<s56> vvals;
	obj.s68( s96::s124, vvals );
	for( size_t n = 0; n < vvals.size(); n++ )
		s369.push_back( vvals[n]->s79() );
}

void s160::s252( s209* p )
{
	s449.s252( p );
}

void s160::s382( const wstring& nam, const wstring& s226,
	vector<wstring>& res )
{
	size_t pl = nam.rfind( L"::" );
	s164* mod = NULL;
	bool bCl = false;
	if( nam.find( L"()" ) == nam.size() - 2 )
		bCl = true;
	
	if( pl != string::npos ) {

		wstring s450 = nam.substr( 0, pl );
		wstring s409 = nam.substr( pl + 2 );
		if( bCl ) {
			s409 = s409.substr( 0, s409.size() - 2 );

		}

			mod = (s164*)s326.get( s450 );

		if( !mod->s337( s409, s226 ) )
			throw s5( L"Symbol '" + nam + L"' cannot be imported by '" +
				s226 + L"'");

		res.push_back( s409 );
	}
	else {

		if( bCl ) {
			wstring s409 = nam.substr( 0, nam.size() - 2 );
			s449.get( s409 );
			res.push_back( s409 );
		}
		else {
			mod = (s164*)s326.get( nam );
			mod->s424( s226, res );
		}
	}
}


s163* s160::s378( const wstring& val, const wstring& s226 )
{

	return new s288( this, val, s226 );
}

s209* s160::s379( size_t type, const wstring& s226 )
{
	return s449.s255( this, type, s226 );
}

s209* s160::s379( const std::wstring& val, const wstring& s226 )
{
	return s449.s255( this, val, s226 );
}

s209* s160::s379( const s288& ds )
{
	return s449.s255( this, ds.Str(), ds.s471() );
}

s209* s160::s379( s161& s370, const wstring& s226 )
{
	return s449.s255( this, s370, s226 );
}

s324* s160::s377( const std::wstring& s451, 
														std::vector<s210*>& s432, s164* s429, s164* s430 )
{
	s324* ret = NULL;

	if( s451 == s134 )
		ret = new s364( this, s429, s430, s432 );
	else if( s451 == s137 )
		ret = new s360( this, s429, s430, s432 );
	else if( s451 == s147 )
		ret = new s363( this, s429, s430, s432 );
	else if( s451 == s158 )
		ret = new s366( this, s429, s430, s432 );
	else if( s451 == s148 )
		ret = new s362( this, s429, s430, s432 );
	else if( s451 == s155 )
		ret = new s365( this, s429, s430, s432 );
	else if( s451 == s159 )
		ret = new s367( this, s429, s430, s432 );
	else if( s451 == s156 )

		throw s5( L"unexpected lambda" );

	return ret;
}

s163*
s160::s384( const wstring& nam, const wstring& s220, bool thr /*= true*/ )
{
	size_t pl = nam.rfind( L"::" );
	s163* ret = NULL;
	if( pl == string::npos ) {
		ret = s449.get( nam, thr );
		if( !ret ) {
			s164* exp = ( (s164*)s449.get( s96::s119, false ) );
			if( exp )
				ret = exp->s336( nam, s220, thr );
		}
		return ret;
	}

	wstring s450 = nam.substr( 0, pl );
	wstring s409 = nam.substr( pl + 2 );
	return ( (s164*)s449.get( s450 ) )->s336( s409, s220 );	
}

void* s160::getExportVariable( const std::wstring& s170 )
{
	s291* ret;
	s164* exp = ( (s164*)s326.get( s96::s119, false ) );
	if( exp )
		ret = (s291*)exp->s336( s170, L"", true );
	else
		throw s5( L"no such export variable: " + s170 );
	void * pv = ret->addr();

	return pv;
}
wstring s368 = L"::_start";
map<int, s160*> handles;

HPROG createAssembly()
{
	static int cnt = 0;
	s160* p = new s160();
	handles[++cnt] = p;
	s209::s231( p );
	p->s221();

	return cnt;
}

void loadProgram( HPROG handle, const wstring& s394 )
{
	s160* p = handles[handle];
	p->s502( s394 );
}

void s504( HPROG handle, s44::s57& obj )
{
	s160* p = handles[handle];
	p->s504( obj );
}

s209* run( HPROG handle )
{
	return handles[handle]->run();
}

void* callFunc( HPROG handle, const std::wstring& sf, vector<wstring>& l )
{
	s160* p = handles[handle];
	return p->callFunc( sf, l );
}

void evaluateExpression( const std::wstring& sf )
{

}

void* getExportVariable( HPROG handle, const std::wstring& s170 )
{
	s160* p = handles[handle];
	return p->getExportVariable( s170 );
}

void* execute( s163* p )
{
	return ( (s291*)p->s217() )->addr();
}

void importSymbol( HPROG handle, const std::wstring& modName, const std::wstring& symName,
										const std::wstring& s226 )
{
	s160* p = handles[handle];
	s164* ob = (s164*) p->s336( modName, s226 );
	ob->s482( symName, s226 );
}

void importFile( HPROG handle, const std::wstring& modName, const std::wstring& s388,
									const std::wstring& s226 )
{
	vector<s1::s3<s44::s57>> vobj;
	s44::s80( s388, vobj, s96::s452 );
	
	s160* p = handles[handle];
	p->s502( s388 );
	s164* ob = (s164*)p->s336( modName, s226 );
	for( size_t n = 0; n < vobj.size(); n++ ) {
		wstring s400 = s161::s194( *vobj[n], s96::s122 );
		ob->s482( s400, s226 );
	}
}

HPROG initShell( const std::wstring& modName, const std::wstring& modText )
{
	s1::s3<s44::s57> ob = new s44::s57();
	size_t pos = 0;
	s81( modText, pos, ob );
	ob->s70( L"name", new s44::s55( modName ) );

	HPROG prog = createAssembly();
	s504( prog, *ob );
	return prog;
}



} // namespace transd
