
/*
This is a distributed file for Tourbillon virtual compiler embedding
library.

Copyright (c) 2020-2021 Albert Berger [alberger at gmail com].
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
library of Tourbillon virtual compiler.
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
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include <cassert>
#include <regex>
#include <climits>
#include <cerrno>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include "transd.hpp"
using namespace std;
namespace s2 {
uint32_t s18::s29;
std::vector<std::wstring> s1098 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1242()
{
s18::s31();
}
}
using namespace s2;
using s2::s18;
namespace s3 {
time_t s35( const std::wstring& f )
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
throw new s18( L"cannot get mtime of: " + f, 
(uint32_t)s18::s19::s25 );
return st.st_mtime;
}
uint8_t s36( const std::wstring& f )
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
throw new s18( L"file system object does not exist: " + f,
(uint32_t)s18::s19::s25 );
if( st.st_mode & S_IFREG )
return 1;
else if( st.st_mode & S_IFDIR )
return 2;
return 0;
}
bool s38( const wstring& s218 )
{
try {
s36( s218 );
}
catch( s18& ) {
return false;
}
return true;
}
bool s37( const wstring& s218 )
{
try {
if( s36( s218 ) != 1 )
throw new s18( L"Cannot find data file: " + s218,
(uint32_t)s18::s19::s25 );
}
catch( s18* e ) { // file don't exist
if( e->which() != (uint32_t)s18::s19::s25 )
throw;
return false;
}
return true;
}
} // namespace s3
#ifdef __LINUX__
using namespace std;
using namespace s2;
using namespace s5;
namespace s3 {
wstring s39()
{
char buf[1024];
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );
}
wstring s40()
{
wstring s721 = s39();
size_t pl = s721.rfind( '/' );
if( pl == string::npos )
s721 = L"";
else
s721 = s721.substr( 0, pl );
return s721;
}
bool s33( const wstring& s48, const wstring& s551, wstring& s160 )
{
struct dirent *entry;
DIR *dp;
wregex rg( s551 );
bool s721 = false;
dp = opendir( conv.to_bytes( s48.c_str() ).c_str() );
if( dp == NULL ) {
wstring s735 = conv.from_bytes( strerror( errno ) );
throw new s18( L"cannot open directory: " + s48 + L";\nerror: " + s735,
(uint32_t)s18::s19::s24 );
}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s160 = s48 + L"/" + conv.from_bytes( entry->d_name );
s721 = true;
break;
}
}
closedir( dp );
return s721;
}
void s34( const wstring& s48, const wstring& s551, vector<wstring>& s42, vector<wstring>& s43 )
{
struct dirent *entry;
DIR *dp;
wregex rg( s551 );
dp = opendir( conv.to_bytes( s48.c_str() ).c_str() );
if( dp == NULL ) {
wstring s735 = conv.from_bytes( strerror( errno ) );
throw new s18( L"cannot open directory: " + s48 + L";\nerror: " + s735,
(uint32_t)s18::s19::s24 );
}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
wstring item = conv.from_bytes( entry->d_name );
wstring s = s48 + L"/" + item;
uint8_t is = s36( s );
if( is == 1 )
s42.push_back( item );
else if( is == 2 )
s43.push_back( item );
}
}
closedir( dp );
}
bool s764( const std::wstring& f )
{
if( f.size() && f[0] == '/' )
return true;
return false;
}
} // namespace s3
#endif // __LINUX__
#ifdef WIN32
using namespace std;
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
namespace s3 {
wstring s39()
{
wchar_t s44[1024];
DWORD length = GetModuleFileNameW( NULL, s44, 1024 );
return s44;
}
wstring s40()
{
wchar_t s44[1024];
DWORD length = GetModuleFileNameW( NULL, s44, 1024 );
PathRemoveFileSpecW( s44 );
return s44;
}
bool s33( const wstring& _dir, const wstring& s551, wstring& s160 )
{
HANDLE s50;
WIN32_FIND_DATAW s45;
wstring s46, s47;
wregex rg( s551.c_str() );
bool s721 = false;
wstring s48 = _dir;
if( s48.back() != L'/' && s48.back() != L'\\' )
s48 += L'\\';
if( ( s50 = FindFirstFileW( ( s48 + L"*" ).c_str(), &s45 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s50, &s45 ) ) {
s46 = s45.cFileName;
s47 = s48 + s46;
if( regex_match( s46, rg ) ) {
s160 = s47;
s721 = true;
break;
}
}
return s721;
}
void s34( const wstring& _dir, const wstring& s551, vector<wstring>& s42, vector<wstring>& s43 )
{
HANDLE s50;
WIN32_FIND_DATAW s45;
wstring s46, s47;
wregex rg( s551.c_str() );
wstring s48 = _dir;
if( s48.back() != L'/' && s48.back() != L'\\' )
s48 += L'\\';
if( ( s50 = FindFirstFileW( ( s48 + L"*" ).c_str(), &s45 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s50, &s45 ) ) {
s46 = s45.cFileName;
s47 = s48 + s46;
if( regex_match( s46, rg ) ) {
uint8_t is = s36( s47 );
if( is == 1 )
s42.push_back( s46 );
else if( is == 2 )
s43.push_back( s46 );
}
}
}
bool s764( const std::wstring& f )
{
if( f.size() && f[1] == ':' )
return true;
return false;
}
} // namespace s3
#endif // WIN32
namespace s4 
{
wstring s91 = L"\"`'";
wstring s51 = L"\n\r\t ";
string s52 = "\n\r\t ";
wstring s53 = L"";
void s57( const wstring& s, size_t s68, wchar_t left, wchar_t right,
size_t& start, size_t& end, bool s975/*=false*/ )
{
end = string::npos;
start = string::npos;
int s69 = 0;
wchar_t s962 = 0;
for( size_t n = s68; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s962 || !s975 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s69++;
}
else if( c == right ) {
if( start == string::npos )
return; // s894
if( --s69 == 0 ) {
end = n;
return;
}
}
else if( s975 && ( c == L'\'' || c == L'\"' ) ) {
s962 = c;
}
}
else if( s962 && c == s962 ) {
s962 = 0;
}
}
}
void s940( const wstring& s, size_t s68, wchar_t left, wchar_t right,
size_t& start, size_t& end )
{
end = string::npos;
start = s.find( left, s68 );
if( start == string::npos || start == s.size() - 1 )
return;
int s69 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s69;
continue;
}
if( s[n] == right )
--s69;
if( s69 == 0 ) {
end = n;
return;
}
}
}
void s58( const wstring& s, size_t s68, wchar_t c, size_t& start, size_t& end )
{
end = string::npos;
start = s.find( c, s68 );
if( start == string::npos || start == s.size() - 1 )
return;
bool s930 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' )
s930 = !s930;
else
s930 = false;
if( s[n] == c && !s930 ) {
end = n;
return;
}
}
}
void s1103( const std::wstring& s, size_t& s68, const std::wstring& s1210 )
{
size_t pl = s.find( s1210, s68 );
if( pl == s68 )
return;
size_t start = s68;
s68 = string::npos;
while( pl < s.size() ) {
if( s1210.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;
}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1210.size();
if( pl < s.size() )
pl = s.find( s1210, pl );
}
else {
s68 = pl;
return;
}
}	
}
size_t count( const std::wstring& s80, const std::wstring& s1210, size_t start, size_t end,
bool s975 )
{
size_t s721 = 0;
size_t pl = s80.find( s1210, start );
while( pl < s80.size() && pl <= end) {
if( s975 && pl && s80[pl-1] == '\\' ) {
++pl;
}
else {
++s721;
pl += s1210.size();
}
if( pl < s80.size() - 1 ) 
pl = s80.find( s1210, pl );
}
return s721;
}
int s59( const wstring& s80, wchar_t s75, size_t& pos )
{
size_t s73 = s80.find( s75, pos );
if( s73 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s55( s80.substr( pos, s73 - pos ), L" " );
int s721 = stoi( s );
pos = s80.find_first_not_of( s51 + s75, s73 );
return s721;
}
bool s65( const wchar_t *str, long *s367, wchar_t **end /*= NULL*/ )
{
wchar_t *s70;
bool s721 = true;
errno = 0;
*s367 = std::wcstol( str, &s70, 0 );
if( s70 == str || ( !end && *s70 != '\0' ) ||
( ( *s367 == LONG_MIN || *s367 == LONG_MAX ) && errno == ERANGE ) )
s721 = false;
if( end )
*end = s70;
return s721;
}
bool s66( const wchar_t *str, double *s367, wchar_t **end /*= NULL*/ )
{
wchar_t *s70;
bool s721 = true;
errno = 0;
*s367 = std::wcstod( str, &s70 );
if( s70 == str || ( !end && *s70 != '\0' ) ||
( ( *s367 == HUGE_VAL || *s367 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s721 = false;
if( end )
*end = s70;
return s721;
}
void s963( const wstring& s80, vector<wstring>& s160 )
{
size_t s71 = s80.find_first_not_of( s51 );
size_t s717, s718;
while( s71 != string::npos ) {
wchar_t c = s80[s71];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s58( s80, s71, c, s717, s718 );
if( s718 == string::npos )
throw s2::s18( L"Quotes don't match near \'" + s80.substr( s71, 40 ) + L"...\'" );
arg = s80.substr( s71, s718 - s71 + 1 );
s71 = s80.find_first_not_of( s51, ++s718 );
}
else {
s718 = s80.find_first_of( s51 );
arg = s80.substr( s71, s718 - s71 );
s71 = s718;
}
s160.push_back( arg );
}
}
void s60( const wstring& s, const wstring& s75, vector<wstring>& s160, bool clr )
{
size_t s71 = 0, s72 = 0;
while( s72 != wstring::npos && s71 < s.size()) {
s72 = s.find( s75, s71 );
wstring seg;
if( clr ) 
seg = s55( s.substr( s71, s72 - s71 ), s51 );
else
seg = s.substr( s71, s72 - s71 );
s71 = s72 + s75.size();
if( seg.size() )
s160.push_back( seg );
}
}
void s299( const vector<wstring>& v, const wstring& s75, wstring& s160 )
{
if( v.empty() )
return;
s160 = v[0];
for( size_t n = 1; n < v.size(); ++n )
s160 += (s75 + v[n]);
}
wstring s74( const wstring& s80, size_t& pos )
{
size_t pl = s80.find( L'\n', pos );
wstring line = s55( s80.substr( pos, pl - pos ), s51 );
pos = pl == string::npos ? pl : pl + 1;
return line;
}
void s61( const wstring& s80, const wstring& s75, 
pair<wstring, wstring>& pr, size_t& pos )
{
size_t pl = s80.find( L'\n', pos );
wstring line = s55( s80.substr( pos, pl - pos ), s51 );
pos = pl == string::npos ? pl : pl + 1;
pl = line.find( s75 );
if( pl == string::npos ) 
throw s2::s18( L"invalid pair syntax: " + line );
wstring s79 = s55( line.substr( 0, pl ), s51 );
wstring s367 = s55( line.substr( pl + s75.size() ), s51 );
pr.first = s79;
pr.second = s367;
}
void s62( const wstring& s80, const wstring& s75, vector<pair<wstring, wstring>>& v )
{
vector<wstring> s76;
s60( s55( s80, s51 ), L"\n", s76 );
for( size_t n = 0; n < s76.size(); ++n ) {
size_t pl = s76[n].find( s75 );
wstring s79 = s55( s76[n].substr( 0, pl ), s51 );
wstring s367 = s55( s76[n].substr( pl + s75.size() ), s51 );
v.push_back( make_pair( s79, s367 ) );
}
}
wstring s54( const std::wstring& l, const std::wstring& s, const std::wstring& r )
{
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s721 = s.substr( pl );
return s721.substr( 0, s721.find_last_not_of( r ) + 1 );
}
wstring s55( const std::wstring& s, const std::wstring& c )
{
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s721 = s.substr( pl );
return s721.substr( 0, s721.find_last_not_of( c ) + 1 );
}
wstring s63( const wstring& s80 )
{
if( s80[0] != L'{' )
return s80;
size_t s77, s78;
s57( s80, 0, L'{', L'}', s77, s78 );
wstring s82 = s80.substr( s77 + 1, s78 - s77 - 1 );
vector<wstring> s83;
s60( s55( s82, L" " ), L"|", s83 );
#ifdef WIN32	
return s83[0] + s80.substr( s78 + 1 );
#else
return s83[1] + s80.substr( s78 + 1 );
#endif	
}
bool s56( const std::wstring& s, const std::wstring& ss )
{
if( s.substr( s.size() - ss.size() ) == ss )
return true;
return false;
}
void s64( wstring& s48 )
{
#ifdef WIN32
if( s48.back() != L'/' &&
s48.back() != L'\\' ) {
size_t pl = s48.find( L"\\" );
size_t pl1 = s48.find( L"/" );
if( pl != string::npos && pl > pl1 )
s48 += L"\\";
else
s48 += L"/";
}
#else
if( s48.back() != L'/' )
s48 += L"/";
#endif
}
wstring s792( wstring path )
{
size_t pl = path.find( L"\\" );
while( pl != string::npos ) {
path = path.replace( pl, 1, L"/" );
pl = path.find( L"\\" );
}
if( path.front() == L'\'' || path.front() == L'"' ) {
if( path.back() != path.front() )
throw new s2::s18( L"opening and closing quotes don't match" );
path = path.substr( 1, path.size() - 2 );
}
return path;
}
void s67( const std::wstring& s81 )
{
}
void s57( const string& s, size_t s68, char left, char right,
size_t& start, size_t& end )
{
end = string::npos;
start = s.find( left, s68 );
if( start == string::npos || start == s.size() - 1 )
return;
int s69 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s69;
continue;
}
if( s[n] == right )
--s69;
if( s69 == 0 ) {
end = n;
return;
}
}
}
int s59( const string& s80, char s75, size_t& pos )
{
size_t s73 = s80.find( s75, pos );
if( s73 == string::npos )
throw invalid_argument( "separator not found" );
string s = s55( s80.substr( pos, s73 - pos ), " " );
int s721 = stoi( s );
pos = s80.find_first_not_of( s52 + s75, s73 );
return s721;
}
void s60( const string& s, const string& s75, vector<string>& s160 )
{
size_t s71 = 0, s72 = 0;
while( s72 != string::npos ) {
s72 = s.find( s75, s71 );
string seg = s55( s.substr( s71, s72 - s71 ), s52 );
s71 = s72 + s75.size();
s160.push_back( seg );
}
}
void s62( const string& s80, vector<pair<string, string>>& v )
{
vector<string> s76;
s60( s55( s80, s52 ), "\n", s76 );
for( size_t n = 0; n < s76.size(); ++n ) {
size_t pl = s76[n].find( ':' );
string s79 = s55( s76[n].substr( 0, pl ), s52 );
string s367 = s55( s76[n].substr( pl + 1 ), s52 );
v.push_back( make_pair( s79, s367 ) );
}
}
string s54( const std::string& l, const std::string& s, const std::string& r )
{
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s721 = s.substr( pl );
return s721.substr( 0, s721.find_last_not_of( r ) + 1 );
}
string s55( const std::string& s, const std::string& c )
{
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s721 = s.substr( pl );
return s721.substr( 0, s721.find_last_not_of( c ) + 1 );
}
string s63( const string& s80 )
{
if( s80[0] != '{' )
return s80;
size_t s77, s78;
s57( s80, 0, '{', '}', s77, s78 );
string s82 = s80.substr( s77 + 1, s78 - s77 - 1 );
vector<string> s83;
s60( s55( s82, " " ), "|", s83 );
#ifdef WIN32	
return s83[0] + s80.substr( s78 + 1 );
#else
return s83[1] + s80.substr( s78 + 1 );
#endif	
}
void s84( wstring& s80, vector<wstring>& s1225, map<size_t, size_t>& s1149 )
{
size_t pos = 0;
wchar_t s85 = 0;
wchar_t s86 = 0;
bool s87 = false;
bool s88 = false;
size_t s89 = string::npos;
bool s90 = false;
bool s1079 = false;
wstring s91 = L"`'\"";
s1225.reserve( 1000 );
size_t s1143 = 1;
bool s1070 = false;
while( pos < s80.size() ) {
wchar_t c = s80[pos];
if( c == '\r' ) {
s80.erase( pos, 1 );
continue;
}
if( s85 ) {
if( c == s85 && s86 != '\\' )
s85 = 0;
}
else if( s91.find( c ) != string::npos ) {
if( !s87 ) {
s85 = c;
}
}
else if( c == '*' ) {
if( !s87 && s86 == '/' ) {
s87 = true;
s88 = true;
s89 = pos - 1;
if( pos > 1 && s80[pos - 2] != '\n')
s1149[pos - 2] = s1143;
}			
}
else if( c == '/' ) {
if( !s87 && s86 == '/' ) {
s89 = pos - 1;
s87 = true;
s88 = false;
if( pos > 1 && s80[pos - 2] != '\n')
s1149[pos - 2] = s1143;
}
else if( s88 && s86 == '*' ) {
s90 = true;
if( s80[pos+1] == '\n' ){
s1070 = true;
}
}
}
else if( c == '\n' ) {
s1070 = true;
if( s87 ) {
if( !s88 ) {
s90 = true;
}
else {
if( !s1079 ) {
s1079 = true;
}
}
}
else {
if( pos && s80[pos-1] != '\n' ) {
s1149[pos - 1] = s1143;
}
}
}
if( s1070 ) {
size_t pl = s80.rfind( '\n', pos - 1 );
size_t m = (s80[pos] == '\n');
if( pl == string::npos )
s1225.push_back( s80.substr( 0, pos ) );
else
s1225.push_back( s80.substr( pl + 1, pos - pl - m ) );
s1070 = false;
s1143++;
}
if( s90 ) {
int m = 0;
if( s88 )
m = 1;
if(	s80[pos] == '\n' && ( !s89 || s80[s89 -1] == '\n' ) )
m = 1;
s80.replace( s89, pos - s89 + m, L" ");
pos = s89 + 1;
s89 = string::npos;
s87 = false;
s1079 = false;
s88 = false;
s90 = false;
s86 = 0;
}
s86 = c;
pos++;
}
if( s87 ) {
auto it = end(s1149);
if( s1149.size() ) it--; 
size_t ln = (it == end(s1149) ? 0 : it->second);
throw new s2::s18( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );
}
}
}//namespace s4
namespace s5 {
std::locale locloc;
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
}
#ifdef WIN32
#include <conio.h>
#endif
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace s4;
namespace s6 {
uint32_t s19::s93;
void s19::s31()
{
s93 = s18::s30();
}
void s1238()
{
s19::s31();
}
bool s104( const wstring& s98 )
{
wcout << s98 << L" [Y]es | [n]o :";
wstring ans;
getline( wcin, ans );
if( ans.size() && s55( ans, L" " ).empty() )
throw new s18( s19::s94() );
if( ans.size() && ( ans[0] == L'N' || ans[0] == L'n' ) )
return false;
return true;
}
int s105( const wstring& s98, const vector<wstring>& s99 )
{
int s721;
while( true ) {
s137();
wcout << s98 << endl << endl;
for( size_t i = 0; i < s99.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s99[i] << endl;
}
s721 = s110( L"Please, enter your answer's number: " );
if( s721 < 0 || s721 > ( int ) s99.size() ) {
wcout << "No variant with such number." << endl;
s101();
continue;
}
break;
}
return s721;
}
wstring s106( const wstring& s98, bool s100 )
{
if( !s98.empty() )
wcout << s98;
wstring s367;
if( s100 )
s103( false );
getline( wcin, s367 );
if( s100 )
s103( true );
return s367;
}
wstring s107( const wstring& s98, bool s100 )
{
wcout << s98;
int s124 = 0;
bool s616 = true;
wstring s125 = s98;
size_t s1232 = s125.size();
size_t s126 = s1232;
while( s616 ) {
s124 = _getch();
switch( s124 ) {
case s117:
if( s1232 > s126 ) {
wcout << '\r' << s125.substr( 0, --s1232 );
}
break;
case s118:
if( s1232 < s125.size() )
wcout << s125[s1232++];
break;
case s115:
case s116:
continue;
case s121:
if( ( s1232 > s126 ) && s125.size() ) {
s125.erase( --s1232, 1 );
wcout << '\r' << wstring( s125.size() + 1, L' ' );
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
break;
case s122:
if( s1232 < s125.size() ) {
s125.erase( s1232, 1 );
wcout << '\r' << wstring( s125.size() + 1, L' ' );
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
break;
case s120:
s616 = false;
break;
case s123:
break;
default:
if( s1232 < s125.size() )
s125.insert( s1232, 1, s124 );
else
s125 += s124;
++s1232;
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
}
return s125;
}
wstring s108( const wstring& s98, const vector<wstring>& s109 )
{
wcout << s98 << endl;
int s124 = 0;
size_t s720 = s109.size();
bool s616 = true;
wstring s125;
size_t s1232 = 0;
#ifdef __LINUX__
char codebuf[4];
#endif			
while( s616 ) {
s124 = _getch();
#ifdef __LINUX__
if(codebuf[0] == 27) {
if( !codebuf[1] ) {
codebuf[1] = s124;
continue;
}
else {
if( codebuf[1] == 91 ) {
if( !codebuf[2] ) {
if( s124 == 65 ) s124 = s115;
else if(s124 == 66) s124 = s116;
else if(s124 == 67) s124 = s118;
else if(s124 == 68) s124 = s117;
else if(s124 == 51) {
codebuf[2] = s124;
continue;
}
memset(codebuf,0,4);
}
else{
if( codebuf[2] == 51 ) {
if( s124 == 126 )
s124 = 83;
memset(codebuf,0,4);
}
}
}
}
}
else {
if( s124 == 27 ) {
codebuf[0] = 27;
continue;
}
else if( s124 == 10 )
s124 = 13;
else if( s124 == 127 )
s124 = 8;
}
#endif			
switch( s124 ) {
case s117:
if( s1232 > 0 ) {
wcout << '\r' << s125.substr( 0, --s1232 );
}
break;
case s118:
if( s1232 < s125.size() )
wcout << s125[s1232++];
break;
case s115:
if( s720 > 0 ) {
if( s720 < s109.size() )
wcout << '\r' << wstring( s125.size(), L' ' );
s125 = s109[--s720];
wcout << '\r' << s125;
s1232 = s125.size();
}
break;
case s116:
if( s720 < s109.size() - 1 ) {
wcout << '\r' << wstring( s125.size(), L' ');
s125 = s109[++s720];
wcout << '\r' << s125;
s1232 = s125.size();
}
break;
case s121:
if( s1232 > 0 && s125.size() ) {
s125.erase( --s1232, 1 );
wcout << '\r' << wstring( s125.size() + 1, L' ' );
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
break;
case s122:
if( s1232 < s125.size() ) {
s125.erase( s1232, 1 );
wcout << '\r' << wstring( s125.size() + 1, L' ' );
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
break;
case s120:
s616 = false;
break;
case s123:
break;
default:
if( s1232 < s125.size() )
s125.insert( s1232, 1, s124 );
else
s125 += s124;
++s1232;
wcout << '\r' << s125 << '\r' << s125.substr( 0, s1232 );
}
}
return s125;
}
int s110( const std::wstring & s98 )
{
int s721;
while( true ) {
wcout << s98;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s721 = stoi( inp );
}
catch( std::invalid_argument& ) {
continue;
}
break;
}
return s721;
}
void s95( const wstring& s96, const std::vector<std::wstring>& s97 )
{
s137();
wcout << endl << "  " << s96 << endl << fill_n_ch( L'-', s96.size() + 4 )
<< endl << endl;
if( s97.size() ) {
wcout << L"Keyboard shortcuts: " << endl;
for( size_t n = 0; n < s97.size(); n += 2 )
wcout << setw( 10 ) << left << s97[n] << L" - " << s97[n + 1] << endl;
}
wcout << endl;
}
size_t s111( const std::wstring & s98 )
{
wcout << s98 << endl << endl <<
L"Please, enter the number of menu item: " << endl <<
L"1 - Skip this item" << endl << L"2 - Overwrite this item" << endl <<
L"3 - Skip all already existing items" << endl <<
L"4 - Overwrite all already existing items" << endl << "5 or any key - Cancel operation" << endl;
wstring s136;
getline( wcin, s136 );
int i;
try { i = stoi( s136 ); }
catch( std::invalid_argument* ) {
i = 5;
}
if( i < 1 || i > 5 )
i = 5;
return i;
}
void s113( const vector<wstring>& v, vector<wstring>& s160, size_t w, size_t h )
{
size_t s127 = v.size() / h + 1;
size_t s128 = v.size() / s127;
vector<size_t> s129;
size_t s720 = 0;
for( auto it : v ) {
if( s720 == 0 )
s129.push_back( 0 );
if( it.size() > s129.back() )
s129.back() = it.size();
if( ++s720 == s128 )
s720 = 0;
}
size_t s130 = 0, s131 = 0;
size_t s132 = 0;
for( size_t n = 0; n < s127; ++n ) {
s132 += s129[n] + 5;
if( n == s127 - 1 || s132 + s129[n + 1] + 5 > w ) {
size_t s133 = n - s130 + 1;
s132 = 0;
if( s130 ) {
if( s106( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;
}
for( size_t m = s131;
m < min( s131 + s128, v.size() );	++m ) {
wostringstream ss;
for( size_t k = 0;
k < min( s133, ( v.size() - m - 1 ) / s128 + 1 ); ++k )
ss << setw( 3 ) << right << m + s128 * k + 1 << L". " << setw( s129[s130 + k] ) <<
left << v[m + s128 * k];
s160.push_back( ss.str() );
}
s131 += s133 * s128;
s130 = n + 1;
}
}
}
int s114( const std::vector<std::wstring>& v )
{
int w, h;
s112( w, h );
std::vector<std::wstring> rows;
s113( v, rows, w, h );
size_t s134 = 0;
for( auto it : rows ) {
wcout << it << endl;
if( ++s134 % h == 0 ) {
if( s106( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;
}
}
int s135;
while( true ) {
wcout << endl;
wstring s136 = s106( L"Enter the item's number or <Space> to cancel..." );
if( s136 == L" " )
return -1;
try { s135 = stoi( s136 ); }
catch( std::invalid_argument& ) {
continue;
}
break;
}
if( s135 > (int)v.size() ) {
wcout << L"No record with such number." << endl;
return -1;
}
return s135;
}
} // namespace s6
#ifdef __LINUX__
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
namespace s6 {
wstring s39()
{
char buf[1024];
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );
}
void s101()
{
wcout << endl << L"Press 'Return' to continue..." << endl;
std::system( "read" );
}
void s137( int s76 )
{
std::system( "clear" );
for( int i = 0; i < s76; ++i )
wcout << endl;
}
void s103( bool b )
{
struct termios tty;
tcgetattr( STDIN_FILENO, &tty );
if( !b )
tty.c_lflag &= ~ECHO;
else
tty.c_lflag |= ECHO;
(void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );
}
void s112( int& w, int& h )
{
struct winsize ws;
ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );
h = ws.ws_row;
w = ws.ws_col;
}
char _getch()
{
/*#include <unistd.h>   //_getch*/
/*#include <termios.h>  //_getch*/
char buf;
struct termios old = { 0 };
fflush( stdout );
if( tcgetattr( 0, &old )<0 )
perror( "tcsetattr()" );
old.c_lflag &= ~ICANON;
old.c_lflag &= ~ECHO;
old.c_cc[VMIN] = 1;
old.c_cc[VTIME] = 0;
if( tcsetattr( 0, TCSANOW, &old )<0 )
perror( "tcsetattr ICANON" );
if( read( 0, &buf, 1/*4*/ )<0 )
perror( "read()" );
old.c_lflag |= ICANON;
old.c_lflag |= ECHO;
if( tcsetattr( 0, TCSADRAIN, &old )<0 )
perror ( "tcsetattr ~ICANON" );
/*if( buf[1]  == 0) {
if( buf[0] == 10 )
buf[0] = 13;
else if( buf[0] == 127 )
buf[0] = 8;
}
else if( buf[0] == 27 && buf[1] == 91 ) {
if( buf[3] == 0 ) {
if( buf[2] == 65 ) buf[0] = s115;
if( buf[2] == 66 ) buf[0] = s116;
if( buf[2] == 67 ) buf[0] = s118;
if( buf[2] == 68 ) buf[0] = s117;
}
else if( buf[2] == 51 && buf[3] == 126 )
buf[0] = 83;		
}*/
return buf;//buf[0];
}
} // namespace s6
#endif // __LINUX__
#ifdef WIN32
#include <iostream>
namespace s6 {
void s101()
{
wcout << endl;
std::system( "pause" );
}
void s137( int s76 )
{
std::system( "CLS" );
for( int i = 0; i < s76; ++i )
wcout << endl;
}
void s103( bool b )
{
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode;
GetConsoleMode( hStdin, &mode );
if( !b )
mode &= ~ENABLE_ECHO_INPUT;
else
mode |= ENABLE_ECHO_INPUT;
SetConsoleMode( hStdin, mode );
}
void s112( int& w, int& h )
{
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
} // namespace s6
#endif // WIN32
using namespace s1;
using namespace s5;
namespace s7
{
wstring s193 = L"-.0123456789";
wstring s194 = L" ,]}\t\r\n";
void s1037::s178( const wstring& s80, size_t& pos, s10<s150> ob, bool s158/*= false*/ )
{
size_t s77, s78;
s57( s80, pos, L'{', L'}', s77, s78, true );
if( s77 == string::npos )
return;
s1173 = s77 - 1;
wstring sob = s80.substr( s77, s78 - s77 + 1 );
pos = s78 + 1;
ob->s161( sob, s158 );
}
bool s1037::s1108( wstring& s, size_t s71, size_t s719, size_t& line ) const
{
line = 0;
s = L"";
auto itst = s1237.lower_bound( s71 );
auto iten = s1237.lower_bound( s719 );
if( itst == end(s1237) || iten == end(s1237) )
return false;
line = itst->second;
s = s1236[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1236[iten->second-1];
return true;
}
void s195( wstring& s80 )
{
wregex s196(
LR"regex(\n\r?\/\/.*?\n\r?)regex"
);
wsmatch sm;
wstring::const_iterator itst = s80.begin();
wstring::const_iterator iten = s80.end();
while( std::regex_search( itst, iten, sm, s196 ) ) {
s80.erase( sm.position(), sm.length() - 
(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
itst = s80.begin();
iten = s80.end();
}
}
s1037::s1037( const std::wstring& file )
{
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s51 );
if( pl == string::npos )
return;
if( file[pl] == L'{' )
s1235 = file;
else
s202 = file;
}
void s1037::read( vector<s10<s150>>& s160, const wstring& s198 )
{
size_t pos = 0;
if( s202.size() ) {
std::ifstream fs( TOFS( s202 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s202 ));
string s199( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1235 = conv.from_bytes( s199 );
s4::s84( s1235, s1236, s1237 );
if( s198.size() ) {
pos = s1235.find( s198 );
if( pos == string::npos )
throw new s18( s198 + L" directive not found in the source file." );
pos += s198.size() + 1;
if( s1235.size() > 13 && s1235[14] == '\r' )
++pos;
}
}
size_t s200 = pos;
wstring s288;
bool s201 = false;
while( ( pos = s1235.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1235.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s200; subl = pos - s200;
}
else
pl += 1;
wstring s1 = s55( s1235.substr( pl, /*pos - pl - 1*/subl ), s51 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s18( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s18::s19::s22 );
if( s1.size() == 1 )
s201 = true;
else
s288 = s55( s1, s51 + L":" );
}
if( s288.empty() ) {
size_t pl1 = s1235.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s55( s1235.substr( pl1, pl ), s51 );
if( s1.size() ) {
if( ( !s201 && s1[s1.size() - 1] != L':' ) ||
( s201 && s1[s1.size() - 1] == L':' ) ||
(!s201 && s1.size() == 1 ) )
throw new s18( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s18::s19::s22 );
s288 = s55( s1, s51 + L":" );
}
}
}
if( s91.find( s288[0] ) != string::npos ) {
if( s288[0] != s288[s288.size()-1] )
throw new s18( L"Malformed block name: " + s288.substr( 0, 20 ) + L"...",
(uint32_t)s18::s19::s22 );
}
else {
if(	iswdigit( s288[0] ) )
throw new s18( L"wrong unquoted syntax: " + s288.substr( 0, 20 ) + L"...",
(uint32_t)s18::s19::s22 );
}
s10<s150> ob = new s150( this );
s178( s1235, pos, ob, true );
if( s288.size() )
ob->s166( L"name", new s148( s288 ) );
s288 = L"";
s201 = false;
s160.push_back( ob );
}
}
void s179( const wstring& s202, const vector<s1::s10<s150>>& s203 )
{
std::ofstream fs( TOFS( s202 ), ios::out | ios::trunc | ios::binary );
if( !fs.good() )
throw runtime_error( "Reading state file failed: " + U8( s202 ) );
for( auto ob : s203 ) {
basic_stringstream<wchar_t> ss;
ob->s162( &ss );
string s = U8( ss.str() );
s += "\n\n";
fs.write( s.c_str(), s.size() );
}
}
void s180( const wstring& s80, size_t& pos, wchar_t quote, wstring& s160, bool s158 = false )
{
size_t s77, s78;
s58( s80, pos, quote, s77, s78 );
if( s78 != string::npos ) {
pos = s78 + 1;
if( s158 )
s160 = s55( s80.substr( s77, s78 - s77 + 1), s51 ); 
else
s160 = s55( s80.substr( s77+1, s78 - s77 - 1 ), s51 ); 
}
else
pos = string::npos;
}
void s181( wostream* pd, const wstring& s )
{
wchar_t q = L'\"';
if( s91.find( s[0] ) != string::npos )
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
void s182( const wstring& s80, size_t& pos, wstring& s160 )
{
if( !std::isgraph<wchar_t>( s80[pos], locloc ) ||
s80[pos] == L':' || s80[pos] == L',' )
throw new s18( L"unrecognized unquoted syntax: " + s80.substr(pos, 20), 
(uint32_t)s18::s19::s22 );
size_t s204 = pos + 1;
while( std::isgraph<wchar_t>( s80[s204], locloc ) &&
s80[s204] != L':' && s80[s204] != L',' )
++s204;
s160 = s55( s80.substr( pos, s204 - pos ), s51 );
pos = s204;
}
void s183( const wstring& s80, size_t& pos, wstring& s160 )
{
size_t s77, s78;
s57( s80, pos, L'(', L')', s77, s78, true );
if( s78 == string::npos )
throw new s18( L"unmatched unquoted parentheses: " + s80.substr(pos, 20), 
(uint32_t)s18::s19::s22 );
if( s78 == s80.size() - 1 ) {
pos = s78;
}
else {
size_t pl = s80.find_first_not_of( s51, s78 + 1 );
if( pl == string::npos && s80[pl] != L',' && s80[pl] != L'}' )
throw new s18( L"wrong unquoted parentheses syntax: " + s80.substr( pos, 20 ),
(uint32_t)s18::s19::s22 );
pos = s78 + 1;
}
}
void s184( const wstring& s80, size_t& pos, wstring& s160 )
{
if( !std::isgraph<wchar_t>( s80[pos], locloc ) ||
s80[pos] == L':' || s80[pos] == L',' )
throw new s18( L"unrecognized unquoted syntax: " + s80.substr( pos, 20 ),
(uint32_t)s18::s19::s22 );
size_t s204 = pos;
if( s80[pos] == L'(' )
s183( s80, s204, s160 );
else {
s204 = pos + 1;
while( std::isgraph<wchar_t>( s80[s204], locloc ) &&
s80[s204] != L':' && s80[s204] != L',' ) {
if( s80[s204] == L'(' ) {
s183( s80, s204, s160 );
break;
}
++s204;
}
}
s160 = s55( s80.substr( pos, s204 - pos ), s51 );
pos = s204;
}
void s185( wostream* pd, const wstring& s )
{
if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
s[s.size()-1] == L'"' )
throw new s18( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s18::s19::s22 );
for( size_t n = 0; n < s.size(); ++n ) 
if( !std::isgraph<wchar_t>( s[n], locloc ) )
throw new s18( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s18::s19::s22 );
*pd << s;
}
void s186( const s1037* pf, const wstring& s80, vector<s10<s148>>& s160, bool s158,
const std::wstring& s75 )
{
size_t s71 = s80.find_first_not_of( s51 );
while( true ) {
s160.push_back( s10<s148>(new s148( pf, s80, s71, s158 ) ) );
s4::s1103( s80, s71, s75 );
if( s71 == string::npos )
break;
++s71;
}
}
void s186( const s1037* pf, const wstring& s80, size_t& pos, vector<s10<s148>>& s160, 
bool s158, const std::wstring& s75 )
{
size_t s77, s78, s71 = 0;
s57( s80, pos, L'[', L']', s77, s78, true );
pos = s78 + 1;
wstring ar = s55( s80.substr( s77 + 1, s78 - s77 - 1 ), s51 );
while( true ) {
s160.push_back( s10<s148>(new s148( pf, ar, s71, s158 ) ) );
s4::s1103( ar, s71, s75 );
if( s71 == string::npos )
break;
++s71;
}
}
void s187( wostream* pd, const vector<s10<s148>>& v, bool s158=false )
{
*pd << L'[';
for( size_t n = 0; n < v.size(); ++n ) {
v[n]->s162( pd, s158 );
if( n != v.size() - 1 )
*pd << L',';
}
*pd << L']';
}
void s188( const wstring& s80, size_t& pos, wstring& s160, bool s158 = false )
{
size_t pl = s80.find_first_not_of( L", \n\r\t", pos );
if( s91.find( s80[pl] ) != string::npos ) 
s180( s80, pos, s80[pl], s160, s158 );
else {
if( !std::isgraph<wchar_t>( s80[pos], locloc ) ||
s80[pos] == L':' || s80[pos] == L',' )
throw new s18( L"unrecognized name syntax: " + s80.substr( pos, 20 ) +
L"...",	(uint32_t)s18::s19::s22 );
size_t s204 = pos + 1;
while( s80[s204] != L':' && s80[s204] != L',' ) {
if( !std::isalnum<wchar_t>( s80[s204], locloc ) &&
!std::isspace<wchar_t>( s80[s204], locloc ) && s80[s204] != L'_' )
throw new s18( L"unrecognized name syntax: " + s80.substr( pos, 20 ) +
L"...",	(uint32_t)s18::s19::s22 );
++s204;
}
s160 = s55( s80.substr( pos, s204 - pos ), s51 );
pos = s204;
}
}
void s189( wostream* pd, const wstring& s, bool s158=false )
{
bool space = false;
for( size_t n = 0; n < s.size(); ++n )
if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
space = true;
break;
}
if( !space && !s158 && s91.find( s[0] ) == string::npos )
s185( pd, s );
else
s181( pd, s );
}
s138 s190( const wstring& s80, size_t& pos, double& s160 )
{
s138 s721 = s147;
size_t pl = s80.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s80.find( L".", pl );
if( pl1 < pl )
s721 = s143;
if( pl == string::npos )
s160 = stod( s80.substr( pos ) );
else
s160 = stod( s80.substr( pos, pl - pos ) );
pos = pl;
return s721;
}
bool s191( const wstring& s80, size_t& pos, bool& s160 )
{
size_t pl = 0;
if( s80.find( L"true", pos, 4 ) == pos )
pl = 4;
else if( s80.find( L"false", pos, 5 ) == pos )
pl = 5;
if( pl ) {
if( s194.find( s80[pos+pl] ) != string::npos ) {
pos += pl;
s160 = (pl == 4);
return true;
}
}
return false;
}
bool s192( const wstring& s80, size_t& pos )
{
if( s80.find( L"null", pos, 4 ) == pos ) {
if( s194.find( s80[pos+4] ) != string::npos ) {
pos += 4;
return true;
}
}
return false;
}
s148::s148( const s1037* pf, const wstring& s80, size_t& pos, bool s158/*= false*/ )
: s206( s139 ), obj( pf ), s1197( pos + (pf ? pf->s1042():0), 0 ), s1196( (s1037*)pf )
{
size_t s71 = s80.find_first_not_of( L" \n\r\t", pos );
if( s80[s71] == L'{' ) {
size_t s77, s78;
s57( s80, s71, L'{', L'}', s77, s78, true );
pos = s78+1;
obj.s161( s55( s80.substr( s77 + 1, s78 - s77 - 1 ), s51 ), s158 );
s206 = s140;
}
else {
pos = s71;
if ( s91.find( s80[pos] ) != string::npos ) {
s180( s80, pos, s80[pos], str, s158 );
s206 = s146;
}
else if ( s80[pos] == L'[' ) {
s186( (s1037*)s1196, s80, pos, s169 ); 
s206 = s142;
}
else if ( s193.find( s80[pos] ) != string::npos ) {
s206 = s190( s80, pos, s170 );
}
else {
if( s191( s80, pos, b ) )
s206 = s144;
else if( s192( s80, pos ) )
s206 = s145;
else {
s184( s80, pos, str );
s206 = s141;
}
}
}
s1197.second = pf ? pos - 1 + pf->s1042() : 0;
}
bool s148::s1113( wstring& f, std::wstring& s, size_t& line  ) const
{
if( !s1197.first || s1196.s14() )
return false;
f = s1196->Path();
s1196->s1108( s, s1197.first, s1197.second, line );
return true;
}
void s150::s161( const wstring& s80, bool s158/*=s158*/ )
{
s151.clear();
size_t s71;
size_t pl = s80.find_first_not_of( L" \n\r\t" );
if( pl == string::npos )
return;
if( s80[pl] == L'{' )
s71 = s80.find_first_not_of( L" \n\r\t", pl + 1 );
else
s71 = pl;
while( true ) {
wstring s79;
s188( s80, s71, s79, s158 );
size_t pl = s80.find_first_not_of( L" \n\r\t", s71 );
if( pl == string::npos || s80[pl] != L':' )
throw new s18( L"unrecognized nqj syntax: " + s80.substr(s71, 50), 
(uint32_t)s18::s19::s22 );
s71 = pl + 1;
s151.insert( make_pair( s79, new s148( src, s80, s71, s158 ) ) );
pl = s80.find_first_not_of( L" \n\r\t", s71 );
if( pl != string::npos && s194.find( s80[pl] ) == string::npos ) 
throw new s18( L"wrong nqj syntax: missed separator or closing brace: " + s80.substr(s71, 50), 
(uint32_t)s18::s19::s22 );
if( pl != string::npos )
pl = s80.find_first_not_of( L" \n\r\t", pl+1 );
if( pl == string::npos )
break;
s71 = pl;
}
}
bool s150::operator==( const s150& r )  const
{
bool s721 = true;
for( auto it = s151.begin(); it != s151.end(); ++it ) {
auto it1 = r.s151.find( it->first );
if( it1 == r.s151.end() || !( *( it->second ) == *( it->second ) ) ) {
s721 = false;
break;
}
}
return s721;
}
void s150::s162( wostream* pd, bool s158 ) const
{
*pd << L"{\n";
for( auto it = s151.begin(); it != s151.end(); ++it ) {
if( it != s151.begin() )
*pd << L",\n";
s189( pd, it->first, s158 );
*pd << L" : ";
it->second->s162( pd );
}
*pd << L"\n}";
}
void s148::s162( wostream* pd, bool s158 ) const
{
if( s206 == s140 )
obj.s162( pd, s158 );
else if( s206 == s142 )
s187( pd, s169, s158 );
else if( s206 == s141 )
s189( pd, str, s158 );
else if( s206 == s146 )
s189( pd, str, true );
else if( s206 == s143 )
*pd << to_wstring( s170 );
else if( s206 == s147 )
*pd << to_wstring( (int)s170 );
else if( s206 == s144 )
*pd << ( b ? L"true" : L"false" );
else if( s206 == s145 )
*pd << L"null" << endl;
else
throw new s18( L"unknown variant" );
}
bool s150::s163( const wstring& s159 ) const
{
if( s151.find( s159 ) != s151.end() )
return true;
return false;
}
void s150::s164( const wstring& s159, vector<s10<s148>>& s160 ) const
{
auto i = s151.equal_range( s159 );
if( i.first == i.second )
return;
for( auto it = i.first; it != i.second; ++it )
s160.push_back( it->second );
}
const s149 s150::s165( const wstring& s159 ) const
{
if( s151.count( s159 ) > 1 )
throw new s18( L"multiple values: " + s159, (uint32_t)s156 );
auto s721 = s151.find( s159 );
return s721->second;
}
void s150::s166( const std::wstring& s79, s149 s367, s152 ap )
{
if( s151.find( s79 ) != s151.end() ) {
if( ap == s153 )
throw new s18( L"Field already exists: " + s79, (uint32_t)s18::s19::s23 );
else if( ap == s155 )
return;
else if( ap == s154 )
s151.erase( s79 );
}
s151.insert( make_pair( s79, s367 ) );
}
void s150::s167( vector<pair<wstring, s10<s148>>>& s160 ) const
{
for( auto it = s151.begin(); it != s151.end(); ++it ) 
s160.push_back( *it );
}
void s150::s168( wostream* pd, int s205 ) const
{
for( auto it = s151.begin(); it != s151.end(); ++it ) {
*pd << FILL(s205) << it->first << " : " << endl;
it->second->s168( pd, s205 + 2 );
}
}
void s148::s168( wostream* pd, int s205 ) const
{
if( s206 == s140 )
obj.s168( pd, s205 + 2 );
else if( s206 == s142 ) {
for( size_t n = 0; n < s169.size(); ++n ) {
s169[n]->s168( pd, s205 );
if( n < s169.size() - 1 )
*pd << endl;
}
}
else if( s206 == s141 )
*pd << FILL( s205 ) << str << endl;
else if( s206 == s143 )
*pd << FILL( s205 ) << s170 << endl;
else if( s206 == s147 )
*pd << FILL( s205 ) << s170 << endl;
else if( s206 == s144 )
*pd << FILL( s205 ) << b << endl;
else if( s206 == s145 )
*pd << FILL( s205 ) << L"null" << endl;
else
throw new s18( L"unknown variant" );
}
bool operator==( const std::vector<s10<s148>>& l,
const std::vector<s10<s148>>& r )
{
if( l.size() == r.size() ) {
for( size_t n = 0; n < l.size(); ++n )
if( !(*( l[n] ) == *( r[n] ) ) )
return false;
return true;
}
return false;
}
} // namespace s7
using namespace s7;
namespace transd {
namespace s8 {
DEFCONST s439 = L"typeMembers";
DEFCONST s440 = L"typeMember";
DEFCONST s441 = L"typeMethods";
DEFCONST s442 = L"typeMethod";
DEFCONST s443 = L"members";
DEFCONST s444 = L"member";
DEFCONST s445 = L"methods";
DEFCONST s446 = L"method";
DEFCONST s447 = L"@init";
DEFCONST s448 = L"initCall";
DEFCONST s1083 = L"@str";
DEFCONST s449 = L"thisPtr";
DEFCONST s450 = L"virtual";
DEFCONST s451 = L"override";
DEFCONST s901 = L"return";
DEFCONST s452 = L"continue";
DEFCONST s453 = L"break";
DEFCONST s454 = L"throw";
DEFCONST s815 = L"else";
DEFCONST s796 = L"elsif";
DEFCONST s850 = L"to";
DEFCONST s455 = L"true";
DEFCONST s456 = L"false";
DEFCONST s900 = L"null";
DEFCONST s1032 = L"->";
DEFCONSTI s944 = -1;
DEFCONSTI s459 = -2;
DEFCONSTI s457 = -100;
DEFCONSTI s458 = -101;
DEFCONSTI s460 = 1;
DEFCONSTI s461 = 0;
DEFCONSTI s945 = 0;
DEFCONSTI s946 = 0x80000000;
DEFCONST s462 = L"import";
DEFCONST s463 = L"input";
DEFCONST s464 = L"output";
DEFCONST s465 = L"export";
DEFCONST s466 = L"opaque";
DEFCONST s467 = L"public";
DEFCONST s468 = L"private";
DEFCONST s469 = L"secure";
DEFCONST s470 = L"class";
DEFCONST s471 = L"module";
DEFCONST s472 = L"AssemblyDescription";
DEFCONST s473 = L"ProgramText";
DEFCONST s474 = L"Export";
DEFCONST s475 = L"Require";
DEFCONST s476 = L".td";
DEFCONST s1038 = L".tsd";
DEFCONST s478 = L"MainModule";
DEFCONST s477 = L"_start";
DEFCONST s479 = L"asm" + s476;
DEFCONST s480 = L"@ex";
DEFCONST s481 = L"@idx";
DEFCONST s819 = L"@pars";
DEFCONST s858 = L"@obj";
DEFCONST s893 = L"@num_args";
DEFCONST s486 = L"source";
DEFCONST s482 = L"objectType";
DEFCONST s483 = L"moduleType";
DEFCONST s484 = L"name";
DEFCONST s485 = L"entryPoint";
DEFCONST s487 = L"perm";
DEFCONST s489 = L"extends";
DEFCONST s783 = L"packages";
DEFCONST s491 = L"searchDirs";
DEFCONST s1027 = L"@attrs";
DEFCONST s1006 = L"is";
DEFCONST s1005 = L"index type";
DEFCONST s1007 = L"value type";
DEFCONST s437 = L"#lang transd";
DEFCONST s1227 = L"#format tsd";
s1019 s1015 			=	123;
s1019 s1014						= 110;
s1019 s1009			= 201;
s1019 s1228				= 204;
s1019 s1010					= 210;
s1019 s1229					= 304;
s1019 s1230				= 404;
s1019 s1231				= 504;
s1019 s1011					= 510;
s1019 s1012			= 511;
s1019 s1013					= 610;
} // namespace s8
std::wstring s238[] = { L"value", L"function", L"object", L"name" };
const wstring s239 = L"if";
const wstring s240 = L"set";
const wstring s241 = L"sum";
const wstring s242 = L"with";
const wstring s243 = L"mul";
const wstring s244 = L"div";
const wstring s245 = L"dif";
const wstring s246 = L"eq";
const wstring s247 = L"less";
const wstring s248 = L"greater";
const wstring s249 = L"leq";
const wstring s250 = L"geq";
const wstring s251 = L"neq";
const wstring s252 = L"and";
const wstring s253 = L"or";
const wstring s254 = L"dcmp";
const wstring s255 = L"dcmpr";
const wstring s256 = L"mod";
const wstring s257 = L"sqrt";
const wstring s258 = L"abs";
const wstring s259 = L"pow";
const wstring s260 = L"textout";
const wstring s261 = L"lambda";
const wstring s262 = L"proc";
const wstring s264 = L"while";
const wstring s265 = L"eval";
const wstring s266 = L"try";
const wstring s267 = L"catch";
const wstring s268 = L"throw";
const wstring s263 = L"through";
const wstring s269 = L"for";
const wstring s270 = L"new";
const wstring s271 = L"run-file";
const wstring s822 = L"load-file";
const wstring s882 = L"import-module";
const wstring s799 = L"has-field";
const wstring s878 = L"tsd-query";
const wstring s808 = L"substr";
const wstring s928 = L"ret";
const wstring s929 = L"sort";
const wstring s991 = L"exit";
const std::wstring s275 = L"AttrNA";
s273::s273( const std::wstring& s )
{
s1105( s );
}
s273::s273( const std::wstring& s712, const s7::s148& s306 )
: s288( s712 ), s1165( (s148*)&s306 )
{
if( s306.s171() == s141 ) {
wstring s = s306.s176();
s1105( s );
}
else if( s306.s171() == s146 ) {
wstring s = //L"\"" +
s306.s176();// +
s294( s );
}
else if( s306.s171() == s140 ) {
basic_stringstream<wchar_t> ss;
s306.s162( &ss, true );
if( s288.find( s774->s372() ) == 0 ) {
s294( ss.str() );
s288 = s4::s55( s288.substr( s774->s372().size() ), s51 );
}
else {
src = ss.str();
s293( s306.s173() );
}
}
else if( s306.s171() == s143 )
s294( to_wstring( s306.s175() ) );
else if( s306.s171() == s147 )
s294( to_wstring( s306.s59() ) );
else if( s306.s171() == s144 )
s294( to_wstring( s306. s771() ) );
else if( s306.s171() == s142 ) {
basic_stringstream<wchar_t> ss;
s306.s162( &ss );
if( s288.find( L"UVector" ) == 0 ) {
s294( L"UVector" + ss.str() );
s288 = s4::s55( s288.substr( 7 ), s51 );
}
else
s294( ss.str() );
}
else
throw new s18( L"Unhandled nqj variant: " + to_wstring( s306.s171() ) );
}
s273::s273( const s7::s150& s140 )
{
s293( s140 );
}
s273::~s273()
{
reset();
}
void s273::reset()
{
s291.clear();
s276.clear();
s287 = s288 = s290 = src = L"";
}
void s273::s1105( const wstring& s )
{
size_t pos = 0;
if( s[pos] == L'(' )
s292( s );
else if( iswalpha( s[pos] ) || s[pos] == L'_' || s[pos] == L'@' ) {
if( s.find( L'(' ) != string::npos )
s294( s );
else
s295( s );
}
else if( s[pos] == L'"' || iswdigit( s[pos] ) || s[pos] == L'\'' ||
s[pos] == L'-' || s[pos] == L'[' ) {
wstring s80;
s80 = s55( s, s51 );
s294( s80 );
}
else
throw new s18( L"Unknown string content: " + s );
}
void s273::s292( const std::wstring& s80 )
{
src = s80;
size_t pos = 0;
vector<wstring> s713;
s298( s80, pos, s713 );
if( s713.empty() )
return;
s289 = s235;
size_t s71 = 0;
s290 = s297( s713[0], s71 );
for( size_t n = 1; n < s713.size(); n++ )
s291.insert( make_pair( to_wstring( n - 1 ), new s273( s713[n] ) ) );
}
void s273::s294( const std::wstring& s80 )
{
src = s80;
s289 = s234;
s290 = s80;
}
void s273::s295( const std::wstring& s80 )
{
src = s80;
s289 = s237;
s290 = s80;
}
void s273::s293( const s7::s150& s140 )
{
s288 = s312( s140, s8::s484 );
s289 = s236;
vector<pair<wstring, s149>> s151;
s140.s167( s151 );
for( size_t n = 0; n < s151.size(); ++n ) {
if( s151[n].first != s8::s484 )
s296( s151[n].first, *s151[n].second );
}
}
void s714( wstring& s )
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
void s273::s299( s7::s150& obj )
{
wstring s715 = s4::s55( s312( obj, s8::s484 ), s51 );
wstring s691 = s715;
s714( s691 );
if( s691.empty() )
throw new s18( L"Nameless blocks are forbidden." );
if( s691 != s715 )
obj.s166( s8::s484, s149(new s148( s691 )), s150::s154 );
if( s691 == s288 ) { // partial definition
vector<pair<wstring, s149>> s151;
obj.s167( s151 );
for( size_t n = 0; n < s151.size(); ++n )
s296( s151[n].first, *s151[n].second );
}
else {
s291.insert( make_pair( s691, new s273( obj ) ) );
}
}
void s273::s296( s273* node )
{
s291.insert( make_pair( node->s309(), node ) );
}
void s273::s296( const std::wstring& s288, const s148& s367 )
{
s291.insert( make_pair( s288, new s273( s288, s367 ) ) );
}
void s273::s300( s272* s310, size_t s311 /*= 0*/ )
{
s285::iterator it = s291.begin();
for( ; it != s291.end(); ++it ) {
if( it->second->s307() == s236 ) {
if( s311 == 0 ) {
it->second->s300( s310, 1 );
}
else {
}
}
}
}
const s273* s273::s302( const std::wstring& s288 ) const
{
size_t s720 = s291.count( s288 );
if( s720 > 1 )
throw new s18( L"multiple values: " + s288, (uint32_t)s156 );
if( s720 == 1 ) {
auto s721 = s291.find( s288 );
return s721->second.s17<s273*>();
}
throw new s18( L"node not found: " + s288, (uint32_t)s18::s19::s25 );
s285::const_iterator it = s291.begin();
for( ; it != s291.end(); ++it ) {
try {
const s273* s721 = it->second->s302( s288 );
return s721;
}
catch( s18* e ) {
if( e->which() == (uint32_t)s18::s19::s25 )
continue;
throw e;
}
}
throw new s18( L"node not found: " + s288, (uint32_t)s18::s19::s25 );
}
void s273::s298( const wstring& s80, size_t& pos, vector<wstring>& s160 )
{
size_t s77, s78;
s57( s80, pos, L'(', L')', s77, s78, true );
if( s77 != pos || s78 == string::npos )
throw new s18( L"Parentheses don't match near \"" + 
s80.substr( 0, 40 ) + L"...\"" );
pos = s78;
size_t s71 = s80.find_first_not_of( s51, s77 + 1 );
if( s80[s71] == L')' )
return;
size_t s719 = s71;
wstring s716;
while( s719 < s78 ) {
s71 = s80.find_first_not_of( s51 + L")", s719 );
if( s71 >= s78 )
break;
size_t s717, s718;
if( s80[s71] == L'(' ) {
s57( s80, s71, L'(', L')', s717, s718, true );
if( s718 == s78 )
throw new s18( L"Parentheses don't match near \'" + s80.substr( s71, 40 ) + L"...\'" );
s716 = s80.substr( s71, s718 - s71 + 1 );
s719 = s718 + 1;
}
else if( s80[s71] == L'[' ) {
s57( s80, s71, L'[', L']', s717, s718, true );
if( s718 == s78 )
throw new s18( L"Brackets don't match near \'" + s80.substr( s71, 40 ) + L"...\'" );
s716 = s80.substr( s71, s718 - s71 + 1 );
s719 = s718 + 1;
}
else if( s80[s71] == L'"' ) {
s58( s80, s71, L'"',
s717, s718 );
if( s718 == string::npos )
throw new s18( L"Quotes don't match near \'" + s80.substr( s71, 40 ) + L"...\'" );
s716 = s80.substr( s71, s718 - s71 + 1 );
s719 = s718 + 1;
}
else if( iswdigit( s80[s71] ) ) {
s718 = s80.find_first_of( s51 + L")", s71 );
s716 = s80.substr( s71, s718 - s71 );
s719 = s718;
}
else if( iswalpha( s80[s71] ) || s80[s71] == L'_' ) {
s718 = s80.find_first_of( s51 + L")", s71 );
size_t pl = s80.find( L'(', s71 );
if( pl < s718 ) {
s57( s80, pl, L'(', L')', s717, s718, true );
if( s718 == s78 )
throw new s18( L"Parentheses don't match near \'" + s80.substr( s71, 40 ) + L"...\'" );
s716 = s80.substr( s71, s718 - s71 + 1 );
s719 = s718 + 1;
}
else {
s716 = s80.substr( s71, s718 - s71 );
s719 = s718;
}
}
else {
s718 = s80.find_first_of( s51 + L")", s71 );
s716 = s80.substr( s71, s718 - s71 );
s719 = s718;
}
s160.push_back( s716 );
}
}
wstring s273::s297( const std::wstring& s80, size_t &pos )
{
wstring s721;
if( s80[pos] == L'+' && s80[pos + 1] != L'=' )
s721 = s241;
else if( s80[pos] == L'-' && s80[pos + 1] != L'=' )
s721 = s245;
else if( s80[pos] == L'*' && s80[pos + 1] != L'=' )
s721 = s243;
else if( s80[pos] == L'/' && s80[pos + 1] != L'=' )
s721 = s244;
else if( s80[pos] == L'^' && s80[pos + 1] != L'=' )
s721 = s259;
else if( s80[pos] == L'=' && s80[pos + 1] != L'=' )
s721 = s240;
else if( s80[pos] == L'<' && s80[pos + 1] != L'=' )
s721 = s247;
else if( s80[pos] == L'>' && s80[pos + 1] != L'=' )
s721 = s248;
else if( s80[pos] == L'λ' )
s721 = s261;
if( s721.size() ) {
if( s80.size() > pos + 1 && s80.find_first_of( s51 + L")", pos ) != pos + 1 )
throw new s18( L"1: unknown syntax: " + s80.substr(pos, 40),
(uint32_t)s18::s19::s22 );
pos += 1;
return s721;
}
if( s80.substr( pos, 2 ) == L"+=" )
s721 = L"sumeq";
else if( s80.substr( pos, 2 ) == L"-=" )
s721 = L"difeq";
else if( s80.substr( pos, 2 ) == L"*=" )
s721 = L"muleq";
else if( s80.substr( pos, 2 ) == L"/=" )
s721 = L"diveq";
else if( s80.substr( pos, 2 ) == L"^=" )
s721 = L"poweq";
else if( s80.substr( pos, 2 ) == L"<=" )
s721 = L"leq";
else if( s80.substr( pos, 2 ) == L">=" )
s721 = L"geq";
else if( s80.substr( pos, 2 ) == L"==" )
s721 = L"eq";
else if( s80.substr( pos, 2 ) == L"!=" )
s721 = L"neq";
if( s721.size() ) {
if( s80.size() > pos + 2 && s80.find_first_of( s51 + L")", pos ) != pos + 2 )
throw new s18( L"2: unknown syntax: " + s80.substr( pos, 40 ), 
(uint32_t)s18::s19::s22 );
pos += 2;
return s721;
}
size_t s719 = s80.find_first_of( s51 + L")", pos );
s721 = s80.substr( pos, s719 - pos );
pos = s719;
return s721;
}
std::wstring s273::s308() const
{
return (s287.size() ? s287 + L"::" : L"") + s288;
}
wstring s273::s305( const s7::s150& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s163( s8::s483 ) )
return obj.s165( s8::s483 )->s176();
return def;
}
std::wstring s273::s312( const s7::s150& obj,
const std::wstring& s313,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s163( s313 ) )
return obj.s165( s313 )->s176();
return def;
}
const std::wstring& s273::s278( const std::wstring& s313 ) const
{
auto it = s276.find( s313 );
if( it != s276.end() )
return it->second;
return s275;
}
void s273::s279( const std::wstring& s313, const std::wstring& s277 )
{
s276[s313] = s277;
}
void s273::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s288 << L" : " << s238[s289] << endl;
buf << s4::fill_n_ch( L' ', s205 ) << L" " << s290 << endl;
map<wstring, s1039>::const_iterator it = s291.begin();
for( ; it != s291.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s205 + s438 ) << it->first << endl;
it->second->s314( pd, s205 + s438 * 2 );
}
}
} // namespace transd
using namespace s9;
namespace transd {
s1226 s1119;
void s1226::s1069( const std::wstring& s81 )
{
++s1099;
s28.push_back( Msg( s81 ) );
wcout << s81;
}
void s1226::s1069( const std::wstring& s81, const std::string& func, 
const std::string& file, uint32_t line )
{
++s1099;
s28.push_back( Msg( s81, U16(func), U16(file), line, s1153 ) );
}
void s1226::s1071( const std::wstring& s81, const std::string& func, 
const std::string& file, uint32_t line )
{
s28.push_back( Msg( s81, U16(func), U16(file), line, s1156 ) );
}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1200 = {
L"unspecified",
L"compilation",
L"reading source file",
L"parsing NQJ",
L"converting to AST",
L"constructiion of object",
L"linking object",
L"linking function",
L"running program",
};
TDException::TDException( uint32_t s1121, uint32_t cat, const s273* ast_ )
: s18( L"", s1121 ), stage (Stage::s1142 ), category( cat ), s740( ast_ )
{
}
TDException::TDException( uint32_t s1121, uint32_t cat, const s273* ast_, const std::wstring& s81 )
: s18( s81, s1121 ), stage (Stage::s1142 ), category( cat ), s740( ast_ )
{
if( category ) {
s32( s1096[category] + L":" );
}
}
TDException::TDException( const TDException& e )
: s18( e ), stage( e.stage ), category( e.category ), s1207( e.s1207 ), s740( e.s740 )
{
}
TDException* TDException::s1102( const std::wstring& s )
{
specify( s );
return new TDException( *this );
}
wstring TDException::Msg( size_t s205 ) const
{
size_t s1144 = 0;
wstring file, s1198, src;
if( s740 ) {
if( s740->Nqj() && s740->Nqj()->s1113( file, s1198, s1144 ) ) {
wstring s1194 = std::to_wstring( s1144 ) + L": '" + s1198 + L"'";
src = L"\n  in file: " + file + L"\n  on line " + s1194;
}
else {
if( !s740->s301().empty() )
src = L"\n  object: '" + s740->s301() + L"', ";
if( !s740->Src().empty() )
src += L"code: '" + s740->Src() + L"', ";
}
}
wstring s = L"Error ";
if( id ) {
wstring s1192;
if( (uint32_t)stage )
s1192 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1192 += std::to_wstring( id );
s += s1192;
}
if( (uint32_t)stage ) {
s += L" during " + s1200[(uint32_t)stage];
}
s += src + L"\n";
return wstring( s205, L' ' ) + s + s18::Msg( s205 + 2 );
}
s1018::s1018( s18& e, const s273& s740, s19 code )
: s18( e )
{
id = (uint32_t) code;
size_t s1144 = 0;
wstring file, s1198, src;
wstring	s81 = L"Error during ";
if( s740.Nqj()->s1113( file, s1198, s1144 ) ) {
src = std::to_wstring( s1144 ) + L": '" + s1198 + L"'";
s81 += L"in file: " + file + L";\nline " + src + L";\n";
}
else {
s81 += L"object: '" + s740.s301() + L"'; code: " + s740.Src();
}
s32( s81 );
s1119.s1069( Msg( 2 ) );
}
s1026::s1026( s19 code )
: s18( L"" )
{
id = (uint32_t) code;
}
vector<wstring> s1096 = {
L"error",
L"incorrect call of object constructor",
L"incorrect call of builtin function",
L"incorrectly formed TSD query",
L"TSD query failed",
L"symbol is not resolved"
};
namespace lang {
bool s689( const wstring& s, bool s754 )
{
bool s753 = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;
}
s753 = true;
break;
}
if( s753 && s754 )
throw new s18( L"illegal identifier: " + s );
return (!s753);
}
} // namespace tdlang
s1017 s1095;
s281::~s281()
{
}
s505* s281::s519()
{	throw std::logic_error( "1: not implemented" );}
const s505* s281::s527() const
{	throw std::logic_error( "2: not implemented" );}
s508 s281::s520( s505** s284, size_t s521 )
{	throw std::logic_error( "3: not implemented" ); }
s281* s281::s353() const
{	throw std::logic_error( "4: not implemented" ); }
void s281::s523( s282* s615 ) 
{
(void)0;
}
inline bool
s281::s525( const s505* s526 ) const
{
return ( s526->s370() == s370() );
}
s281::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s281::operator int() const { throw std::logic_error( "6: not implemented" ); }
s281::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s281::to_wstring() const { throw std::logic_error( "8: not implemented" ); }
s281* s281::s528( const s273& s740, s272* s310, s282* obj,
const wstring& s350 )
{
s281* p;
if( s740.s307() == s234 ) {
wstring s367 = s740.s301();
bool quot = s91.find( s367[0] ) != string::npos;
size_t ppl = s367.find( L"(" );
bool lastp = s367.back() == L')';
wstring ownerName = s740.s278( L"ownerName" );
if( ( s740.s278( L"ownerType" ) == L"CallSite" ) &&
( ownerName != s242 ) &&
( ownerName != s261 ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s365 = s367.substr( 0, ppl );
wstring s80 = L"(new " + s365 + L" " + s367.substr( ppl + 1 );
s1039 tast = new s273( s80 );
p = s619::s1240( *tast, s310, obj, s350 );
}
else {
p = s310->TR().s545( s740, obj, s350 );
((s505*)p)->s530( s740.s309() );
}
}
else if( s740.s307() == s235 )
p = s619::s1240( s740, s310, obj, s350 );
else if( s740.s307() == s237 )
p = new s390( s740.s301(), s310 );
else //if( s740.s307() == s236 )
throw new s18( L"unexpected node type" );
return p;
}
s281* 
s281::s1125( s272* s310, s281* par, s282* s616, s619* s223,
const std::wstring& s350 )
{
s281* s721;
if( par->s517() == s498 ) {
s1039 ast_ = new s273( ((s349*)par)->Str() );
s721 = s310->TR().s545( *ast_, s616,
((s349*)par)->s352() );
}
else if( par->s517() == s499 ) {
s512 cs = new s588( *((s588*)par) );
s721 = s619::s628( cs, s310, s616, s223, s350 );
((Transd*)s721)->s523( s350, false );
}
else
return par;
return s721;
}
s507
s281::s1124( const wstring& s80, const s273* ast_, s272* s310, s282* s616 )
{
s1039 ast1 = new s273( s80 );
s507 pr = s281::s528( *ast1, s310, s616, s616->s308() );
if( pr->s517() == s496 ) {
pr->s523( s616 );
pr = pr.s17<s390*>()->s396();
}
s507 s721 = s281::s1125( s310, pr, s616, NULL, s616->s308() );
return s721;
}
const wstring& 
s281::s372() const
{
return s310->TR().s859( s370() );
}
void s281::s369( s872::s781 type )
{
s516 = type;
}
s506* s1241( s529& m, const wstring& s159 )
{
if( m.count( s159 ) > 1 )
throw new s18( L"multiple values: " + s159, (uint32_t)s18::s19::s23 );
auto s721 = m.find( s159 );
if( s721 == m.end() )
throw new s18( L"no such key: " + s159, (uint32_t)s18::s19::s25 );
return s721->second;
}
void s705( const std::wstring& s, std::wstring& s1233, std::wstring& s629 )
{
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s18( L"unknown format of qualified name: " + s, (uint32_t)s18::s19::s22 );
s1233 = s.substr( 0, pl );
s629 = s.substr( pl + 2 );
}
s505* s505::s374( s282* s616, const std::vector<s1175>& vt ) const
{
assert(0);
return 0;
}
vector<wstring> s548::s552 = { s8::s465, s8::s463,
s8::s466, s8::s464 };
s1::s10<s553> s584 = new s553();
size_t s1063( const vector<s872::s983>& vt )
{
size_t s721 = 0;
for( auto i : vt )
s721 = ( s721 << 7 ) ^ i;
return s721;
}
size_t s513::s1168( const wstring& s, size_t& pos, s872::Cont& s160 )
{
size_t s71 = pos;
size_t s721 = 0;
while( s71 < s.size() && s[s71] != L')' ) {
size_t pl = s.find( L"(", s71 );
wstring stype = s4::s55( s.substr( s71, pl - s71 ), s4::s51 );
s1175 s1211 = get( stype + L"()" )->s370();
s160.push_back( s1211 );
pl = s.find_first_not_of( s4::s51, ++pl );
s872::Cont s1183;
size_t s1166 = s1168( s, pl, s1183 );
s160.push_back( ( s872::s983 ) s1166 );
s160.insert( end( s160 ), begin( s1183 ), end( s1183 ) );
s721++;
pl = s.find_first_not_of( s4::s51, ++pl );
pos = s71 = pl;
}
return s721;
}
wstring s513::s1116( const s872::Cont& s1178, size_t& idx )
{
assert( s1178.size() );
wstring s721 = s1217[s1178[idx++]];
if( s1178.size() == 1 )
return  s721 + L"( 0 )";
size_t n = (size_t)s1178[idx++];
s721 += L"( " + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s721 += s1116( s1178, idx );
}
s721 += L")";
return s721;
}
void s513::s1112( const s872::Cont& v, size_t& idx, s872::Cont& s160 )
{
s160.push_back( v[idx++] );
size_t n = v[idx++];
s160.push_back( (s1175)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s1112( v, idx, s160 );
}
}
s872::s872( s781 t1, s781 t2/*=(s781)-1*/, s781 t3/*=(s781)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s781)-1 ) {
vt.push_back( t2 );
if( t3 != (s781)-1 )
vt.push_back( t3 );
}
s1215 = s1063( vt );
}
s872::s872( const s872& right )
: s1215( right.s1215 )
{
vt.assign( right.vt.begin(), right.vt.end() );
}
s872::s872( const Cont& v ) 
: vt( v ) 
{
s1215 = s1063( vt );
}
s872::s983 s872::s370( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[0] : 0;
}
void s872::s369( s781 t )
{
vt.clear();
vt.push_back( t );
}
void s872::s369( s1016 pt )
{
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );
}
void s872::s839( s781 t )
{
vt.push_back( t );
}
void s872::s839( s1016 pt )
{
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );
}
void s872::s880( std::vector<s281*>& s160 ) const
{
for( size_t n = 0; n < vt.size(); ++n )
s160.push_back( new s364( NULL, (int)vt[n] ) );
}
inline bool s872::operator==( const s872& p ) const
{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s781* pvt1 = (s781*)&vt[0];
s781* pvt2 = (s781*)&p.vt[0];
for( size_t s720 = 0; s720 < sz1; ++s720 )
if( pvt1[s720] != pvt2[s720] )
return false;
return true;
}
s513::s513( s272* pass_ ) 
: s310( pass_ ) 
{
reset();
}
void s513::s300()
{
for( auto type : s1234 )
if( type ) type->s368();
}
void s513::s543( const s504& st )
{
}
void s513::reset() 
{ 
s1234.clear(); 
s1217.clear();
s1222.clear();
s1218.clear();
s1223.clear();
s1008.clear();
s1234.push_back( NULL ); 
s1217.push_back( L"" );
s1222.push_back( 0 );
}
void s513::s227( s505* p, const std::wstring& s365 )
{
if( s1218.find( s365 ) != s1218.end() )
throw new s18( (uint32_t)s18::s19::s23 );
s1217.push_back( s365 );
s1234.push_back( p );
s1175 s1211 = (s1175)s1217.size() - 1;
s1222.push_back( s872( s1211 ) );
p->s369( s1211 );
s1218[s365] = s1211;
s1223[s1222.back()] = s1211;
}
s1175 s513::s1182( const s872::Cont& v, const std::wstring& s365 )
{
s872 vt( v );
if( s1223.find( vt ) != s1223.end() )
throw new s18( (uint32_t)s18::s19::s23 );
s1217.push_back( s365 );
s1234.push_back( s1234[vt.s370( 0 )]->s374( s310, v )	);
s1222.push_back( vt );
s1175 s1211 = (s1175)s1217.size() - 1;
s1234.back()->s516 = s1211;
s1218[s365] = s1211;
s1223[s1222.back()] = s1211;
s1223[s872( s1211 )] = s1211;
return s1211;
}
s1175 s513::s1158( const s872::Cont& v_ )
{
assert( all_of( begin( v_ ), end( v_ ), [this]( s1175 t ) { return ( t && t <= s1222.size() ); } ) );
s872::Cont v( { v_[0], (s1175)v_.size() - 1 });
for( size_t n = 1; n < v_.size(); ++n ) {
v.push_back( v_[n] );
v.push_back( 0 );
}
s872 vt( v );
s1175 s721 = 0;
auto it = s1223.find( vt );
if( it == s1223.end() ) {
size_t pos = 0;
wstring s1209 = s1116( v, pos );
s721 = s1182( v, s1209 );
}
else
s721 = it->second;
return s721;
}
void s513::s1067( s872::s983 type, const std::wstring& cat, const std::wstring& s1076 )
{
auto s1216 = s1008.find( type );
if( s1216 == s1008.end() )
s1216 = s1008.insert( make_pair( type, s1004() ) ).first;
auto s1081 = s1216->second.find( cat );
if( s1081 == s1216->second.end() )
s1081 = s1216->second.insert( make_pair( cat, set<wstring>() ) ).first;
s1081->second.insert( s1076 );
}
bool s513::s1120( s872::s983 type, const std::wstring& cat, 
const std::wstring& s1076 )
{
vector<s872::s983> types = { type };
if( s1222[type].s370() != type )
types.push_back( s1222[type].s370() );
for( auto t : types ) {
auto s1216 = s1008.find( t );
if( s1216 != s1008.end() ) {
auto s1081 = s1216->second.find( cat );
if( s1081 != s1216->second.end() )
if( s1081->second.find( s1076 ) != s1081->second.end() )
return true;
}
}
return false;
}
void s513::s1109( s872::s983 type, const std::wstring& cat, 
vector<wstring>& s160 )
{
auto s1216 = s1008.find( type );
if( s1216 == s1008.end() )
throw new s18( L"type is not found" );
auto s1081 = s1216->second.find( cat );
if( s1081 == s1216->second.end() )
throw new s18( L"class attribute category is not found: " + cat );
s160.assign( s1081->second.begin(), s1081->second.end() );
}
wstring s513::s1109( s872::s983 type, const std::wstring& cat )
{
auto s1216 = s1008.find( type );
if( s1216 == s1008.end() )
throw new s18( L"type is not found" );
auto s1081 = s1216->second.find( cat );
if( s1081 == s1216->second.end() )
throw new s18( L"class attribute category is not found: " + cat );
if( s1081->second.size() != 0 )
throw new s18( L"class attribute category is not single valued: " + cat );
return *s1081->second.begin();
}
s505* s513::s545( const s273& s740, s282* s616, const wstring& s546 )
{
wstring s367 = s740.s301();
if( s367[0] == L'[' )
return s1234[s1218[s768->s372()]]->s373( s740, s616, s546 );
else if( s367.find( L"UVector[" ) == 0 )
return s1234[s1218[s791->s372()]]->s373( s740, s616, s546 );
else if( s367[0] == L'{' )
return s1234[s1218[s774->s372()]]->s373( s740, s616, s546 );
wstring s365 = L"";
if( s4::s91.find( s367[0] ) != string::npos )
s365 = s378( s310 ).s372();
else if( isdigit( s367[0] ) || s367[0] == L'-' )
return s354::s363( s310, s367, s546 );
else {
size_t pl = s367.find( L"(" );
if( pl != 0 && pl != string::npos ) {
s365 = s367.substr( 0, pl );
}
else if( pl == string::npos )
s365 = s367;
}
auto it = s1218.find( s365 );
if( it == s1218.end() )
throw new s18( L"Type does not exist: " + s367, (uint32_t)s18::s19::s25 );
return s1234[it->second]->s373( s740, s616, s546 );
}
s505* s513::s545( s1175 s358, s282* s616, const wstring& s546 )
{
if( !s358 || s358 >= s1217.size() )
throw new s18( L"no type with such id: " + to_wstring( s358 ) );
s1175 type = s358;
if( s1222[type].s370() != type )
type = s1222[type].s370();
if( s1222[s358].s880().size() == 1 )
return s1234[type]->s374( s616 );
else {
return s1234[type]->s374( s616, s1222[s358].s880() );
}
}
const s505* s513::get( const wstring& s79, bool s547/*= true*/ ) const
{
wstring s365 = s79;
size_t pl = s79.find( L"(" );
if( pl != 0 && pl != string::npos )
s365 = s79.substr( 0, pl );
auto s721 = s1218.find( s365 );
if( s721 == s1218.end() ) {
if( s547 )
throw new s18( L"1: symbol not found: " + s79 );
else
return NULL;
}
return s1234[s721->second].s17<const s505*>();
}
bool s513::s163( const std::wstring& s79 ) const
{
if( s1218.find( s79 ) == s1218.end() )
return false;
return true;
}
const wstring& s513::s859( s1175 n ) const
{
if( n >= s1217.size() )
throw new s18( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1217[n];
}
s1175 s513::s1114( const std::wstring& s365 ) const
{
auto it = s1218.find( s365 );
if( it == s1218.end() )
throw new s18( L"no such type: " + s365 );
return it->second;
}
s1175 s513::s1115( const s872& vt ) const
{
auto it = s1223.find( vt );
if( it == end( s1223 ) )
throw new s18( (uint32_t)s18::s19::s25 );
return it->second;
}
const s872& s513::s1117( s1175 t ) const
{
assert( t <= s1222.size() );
return s1222[t];
}
const s505* s513::s1111( s872::s983 t ) const
{
if( t >= s1234.size() )
throw new s18( L"no prototype for the type with id " + to_wstring( t ) );
return s1234[t].s17<const s505*>();
}
bool s513::s1127( s872::s983 type )
{
return ( s1120( type, s8::s1006, L"container" ) ||
s1120( type, s8::s1006, L"ordered" ) ||
s1120( type, s8::s1006, L"indexed" )		);
auto s1216 = s1008.find( type );
if( s1216 != s1008.end() ) {
auto s1081 = s1216->second.find( s8::s1006 );
if( s1081 != s1216->second.end() )
return (s1081->second.find( L"container" ) != s1081->second.end() ||
s1081->second.find( L"ordered" ) != s1081->second.end() ||
s1081->second.find( L"indexed" ) != s1081->second.end()
);
}
return false;
}
void s513::s844()
{
size_t s793 = s354::s863() + 1;
for( size_t n = s793; n < s1217.size(); ++n ) {
s1218.erase( s1217[n] );
s1223.erase( s1222[n] );
s1008.erase( (s1175)n );
}
s1217.erase( s1217.begin() + s793, s1217.end() );
s1234.erase( s1234.begin() + s793, s1234.end() );
s1222.erase( s1222.begin() + s793, s1222.end() );
}
void s513::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s205 ) << L"Types :" << endl;
for( size_t n = 0; n < s1217.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s205 + 5 ) << s1217[n] << endl;
s1234[n]->s314( pd, s205 + 10 );
}
}
s504::s504( const s504& right )
: s580( right.s580 ), s564( right.s564 ), s566( right.s566 )
{
}
void s504::s523( s282* s965, bool s542/*= true*/ )
{
for( auto sym : s580 ) {
if( sym.second->s517() != s497 ) {
try {
sym.second->s523( s965 );
}
catch( TDException* e ) {
e->s1191( TDException::Stage::s1137 );
s1119.s1069( e->Msg( 0 ) );
continue;
}
}
}
if( s1119.s1025() )
return;
if( s542 ) {
for( auto sym : s580 ) {
if( sym.second->s517() == s497 )
sym.second.s17<Transd*>()->s523( s965->s903(), true );
}
}
}
void s504::reset()
{
for( auto it = s580.begin(); it != s580.end(); ++it )
delete it->second.s17<s506*>();
s580.clear();
}
void s504::copy( s504& t, s282* s616, s619* s615, s152 ap ) const
{
t.s566 = s566;
for( s562::const_iterator it = s580.begin(); it != s580.end(); ++it ) {
if( it->second->s517() == s497 ) {
t.s568( it->first, new s619( *( s619* )&( *it->second ),
s616, s615, std::vector<s281*>(), it->second.s17<Transd*>()->s631() ), ap );
}
else {
t.s568( it->first, ((s505*)it->second->s353()), ap );
}
}
}
void s504::s575( s504& t ) const
{
for( s562::const_iterator it = s580.begin(); it != s580.end(); ++it ) {
if( it->second->s517() == s497 )
t.s568( it->first, it->second.s17<s505*>() );
else
t.s568( it->first, ((s505*)it->second->s353()) );
}
}
bool s504::s565( const std::wstring& s79, s152 ap /*= s153*/ )
{
if( s580.find( s79 ) != s580.end() ) {
wstring rep = s8::s440 + L" name already exists: " + s79;
if( ap == s153 || ap == s561 ) {
if( ap == s153 )
throw new s18( (uint32_t)s18::s19::s23 );
return false;
}
else if( ap == s155 ) {
return false;
}
}
return true;
}
void s504::s568( const std::wstring& s79, s505* sym, s152 ap/*= s153*/ )
{
if( (ap == s154) || s565( s79, ap ) )
s580[s79] = sym;
}
void s504::s568( const std::wstring& s79, s149 s367, s152 ap/*= s153*/ )
{
throw new s18( (uint32_t)s18::s19::s23 );
}
void s504::s569( const std::wstring& s79 )
{
auto it = s580.find( s79 );
if( it == s580.end() )
return;
s580.erase( it );
}
void s504::s570( const s7::s150& s82, s152 ap/*= s153*/ )
{
vector<pair<wstring, s149>> s151;
s82.s167( s151 );
for( size_t n = 0; n < s151.size(); ++n )
s568( s151[n].first, s151[n].second );
}
bool s504::s163( const std::wstring& s79 ) const
{
if( s580.find( s79 ) == s580.end() )
return false;
return true;
}
s505* s504::get( const wstring& s79, bool s547/*= true*/ ) const
{
auto s721 = s580.find( s79 );
if( s721 == s580.end() ) {
if( s547 )
throw new s18( L"2: symbol not found: " + s79 );
else
return NULL;
}
return s721->second.s17<s505*>();
}
void s504::s573( std::vector<std::wstring>& s160 ) const
{
for( auto sym : s580 )
s160.push_back( sym.first );
}
void s504::s571( vector<wstring>& s160 ) const
{
for( auto sym : s580 ) {
if( sym.second->s517() == s497 )
s160.push_back( sym.first );
}
}
void s504::s572( vector<wstring>& s160 ) const
{
for( auto sym : s580 ) {
if( sym.second->s517() == s495 ||
sym.second->s517() == s502 || sym.second->s517() == s501 )
s160.push_back( sym.first );
}
}
void s504::s574( const s504& t,
vector<wstring>& s160 ) const
{
for( auto sym : s580 ) {
if( t.s163( sym.first ) )
s160.push_back( sym.first );
}
}
void s504::s299( const s504& t, s152 ap /*= s153*/ )
{
if( ap != s154 ) 
for( auto sym : t.s580 )
s565( sym.first, ap );
for( auto sym : t.s580 )
s568( sym.first, sym.second.s17<s505*>(), ap );
}
void s504::s576( s537 pv, s273* s82 )
{
if( !s566 )
s566 = new s553();
s566->s556( pv, s82 );
}
void s504::s560( const wstring& s350, vector<wstring>& s160 )
{
for( s562::iterator it = s580.begin(); it != s580.end(); ++it ) {
s537 pv = s538;
if( s566 )
pv = s566->s559( it->first, s350 );
if( pv == s538 ) {
if( s564 == s534 )
pv = s539;
else if( s564 == s536 )
pv = s540;
else {
if( it->second->s517() == s497 )
pv = s539;
else
pv = s540;
}
}
if( pv == s539 )
s160.push_back( it->first );
}
}
bool s504::s577( const std::wstring& s288,
const std::wstring& s350 ) const
{
if( s566 ) {
s537 pv = s566->s559( s288, s350 );
if( pv == s539 )
return true;
else if( pv == s538 ) {
if( s564 == s534 )
pv = s539;
else if( s564 == s536 )
pv = s540;
else {
auto it = s580.find( s288 );
if( it == s580.end() )
throw new s18( L"1: Symbol does not exist: " + s288 );
size_t cat = it->second->s517();
if( cat == s497 || cat == s500 || cat == s502 )
return true;
}
}
return false;
}
return true;
}
void s504::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s205 ) << L"Symbols :" << endl;
s562::const_iterator it = s580.begin();
for( ; it != s580.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s205 + s438 ) << it->first << endl;
it->second->s314( pd, s205 + s438 * 2 );
}
}
s578::s578()
{
}
void s578::s523( s272* s310, const wstring& s585 )
{
for( size_t n = 0; n < s586.size(); ++n ) {
wstring s79 = s586[n];
vector<wstring> s160;
s310->s228( s79, s585, s160 );
for( size_t m = 0; m < s160.size(); ++m ) {
s580.insert( make_pair( s160[m], make_pair( (s505*)s310->s674( 
s586[n],	s585 ), s79) ) );
}
}
}
void s578::s582( const wstring& s79, s272* s310, const wstring& s585 )
{
s586.push_back( s79 );
vector<wstring> s160;
s310->s228( s79, s585, s160 );
for( size_t n = 0; n < s160.size(); ++n )
s580.insert( make_pair( s160[n], make_pair( (s505*)s310->s674( 
s79,	s585 ), s79 ) ) );
}
void s578::s581( const std::wstring& s )
{
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s18( L"Unrecognized import syntax: " + s );
s586.push_back( s.substr(1, s.size() - 2 ) );
}
bool s578::s583( const std::wstring& sym, s390* ref )
{
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );
}
else
mem = sym;
size_t s720 = s580.count( mem );
if( !s720 )
return false;
if( s720 > 1 && mod.empty() )
throw new s18( L"ambigous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s580.equal_range( mem );
if( s720 == 1 && mod.empty() )
return range.first->second.first->s583( mem, ref, L"" );
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod )
return it->second.first->s583( mem, ref, L"" );
}
return false;
}
void s578::copy( s578& t ) const
{
for( s562::const_iterator it = s580.begin(); it != s580.end(); ++it )
t.s580.insert( make_pair( it->first, it->second ) );
}
s548::s548( s537 pv_, const vector<wstring>& s550 )
: s549( s550 ), pv( pv_ )
{
}
s548::s548( const wstring& ag_, const wstring& s80 )
{
}
s537 s548::s587( const std::wstring& s522 ) const
{
for( size_t n = 0; n < s549.size(); ++n )
if( s549[n] == s522 || s549[n] == L"_" )
return pv;
if( pv == s540 )
return s539;
return s540;
}
void s553::s556( s537 pv, s273* s740 )
{
s273::s285& s741 = s740->s303();
s273::s285::iterator it = s741.begin();
for( ; it != s741.end(); ++it ) {
wstring l = it->second->s301().substr( 1, it->second->s301().size() - 2 );
vector<wstring> s160;
wstring s75( s1239, 1 );
s4::s60( l, s75, s160 );
s555[it->first] = new s548( pv, s160 );
}
}
void s553::s557( const std::wstring& s, s548& pl )
{
}
void s553::s558( const std::wstring& s, const std::wstring& s551 )
{
}
s537 s553::s559( const std::wstring& mem, const std::wstring& s522 )
{
s554::iterator it = s555.find( mem );
if( it == s555.end() )
return s538;
return it->second->s587( s522 );
}
s354::s359 s403::s366;
s354::s359 s383::s366;
s354::s359 s380::s366;
s354::s359 s379::s366;
s354::s359 s364::s366;
s354::s359 s377::s366;
s354::s359 s378::s366;
s354::s359 s327::s366;
s354::s359 s797::s366;
s354::s359 s336::s366;
s354::s359 s434::s366;
s354::s359 s404::s366;
s354::s359 s683::s366;
s354::s359 s531::s366;
size_t s354::s807 = 0;
s10<s403> s832;
s10<s383> s784;
s10<s380> s879;
s10<s379> s806;
s10<s364> s828;
s10<s377> s862;
s10<s378> s846;
s10<s434> s870;
s10<s327> s768;
s10<s797> s791;
s10<s1053> s1054;
s10<s336> s774;
s10<s404> s868;
s10<s531> s874;
s10<s683> s811;
s10<s383> s384;
s10<s403> s950;
s10<s403> s385;
s10<s403> s386;
s10<s403> s387;
s10<s403> s954;
s10<s379> s388;
s10<s379> s389;
template <class charT, charT s75>
class punct_facet : public std::numpunct<charT>
{
protected:
charT do_decimal_point() const { return s75; }
};
std::locale exprloc;
s505::~s505()
{
}
void s354::s838( s272* s310, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
if( !soft ) {
std::vector<s281*> l;
s832 = new s403( s310 );
s784 = new s383( s310 );
s806 = new s379( s310, true );
s879 = new s380( s310, L"" );
s828 = new s364( s310, 0 );
s862 = new s377( s310, 0.0 );
s846 = new s378( s310 );
s768 = new s327( s310, NULL, L"" );
s791 = new s797( s310, NULL, L"" );
s1054 = new s1053( s310, NULL, L"" );
s774 = new s336( s310, NULL, L"" );
s811 = new s683( s310, L"" );
s868 = new s404( s310, L"0" );
s870 = new s434( s310, L"" );
s874 = new s531( s310 );
}
s310->s227( s832, L"NoValue" );
s310->s227( s784, L"Null" );
s310->s227( s879, L"Exception" );
s310->s227( s806, L"Bool" );
s310->s227( s828, L"Int" );
s310->s227( s862, L"Double" );
s310->s227( s768, L"Vector" );
s310->s227( s791, L"UntypedVector" );
s310->s227( s1054, L"Tuple" );
s310->s227( s774, L"Index" );
s310->s227( s870, L"Directory" );
s310->s227( s868, L"Range" );
s310->s227( s811, L"TSDBase" );
s310->s227( s874, L"StringStream" );
s310->s227( s846, L"String" );
if( !soft ) {
s807 = s846->s370();
s384 = new s383( s310 );
s950 = new s403( s310, s503 );
s387 = new s403( s310, s503 );
s386 = new s403( s310, s503 );
s385 = new s403( s310, s503 );
s954 = new s403( s310, s503 );
s388 = new s379( s310, true );
s389 = new s379( s310, false );
s950->setWh( s8::s944 );
s387->setWh( s8::s457 );
s386->setWh( s8::s458 );
s385->setWh( s8::s459 );
}
}
s505* s505::s519()
{
return this; 
}
s1175 s354::s405( const std::wstring& s361 ) const
{
auto it = s360().find( s361 );
if( it == s360().end() )
throw new s18( L"No such operation: " + s372() +	L"::" + s361,
(uint32_t)s18::s19::s25 );
s1175 s721 = it->second->s356;
if( !s721 ) // e.g. s327::get
s721 = s370();
return s721;
}
const s505* s354::s527() const
{
return (s505*)s310->s231( s372(), s492 );
}
s646 s354::s362( const std::wstring& s361 ) const
{
s359::const_iterator it = s360().find( s361 );
if( it == s360().end() )
throw new s18( L"No such operation: " + s372() + L"::" + s361,
(uint32_t)s18::s19::s25 );
s355* sp = it->second;
return sp->s357;
}
s508 s354::s520( s505** s284, size_t s521 )
{
return this;
}
s505* s354::s363( s272* s310, const std::wstring& s367, const std::wstring& s350 )
{
if( s367.find_first_not_of( L"-0123456789" ) == std::string::npos ||
s367.find( L"Int(" ) == 0 ) {
return s828->s373( s367, NULL, s350 );
}
else 
return s862->s373( s367, NULL, s350 );
}
s364::s364( s272* s310, int i )
: s354( s310, NULL ), s367( i )
{
if( s828.s14() ) {
s516 = 0;
wh = s8::s946;
}
else
s516 = s828->s370();
}
s364::s364( const s364& r )
: s354( r.s310, NULL ), s367( r.s367 )
{
wh = r.wh;
s516 = s828->s370();
}
s364::s364( s272* s310, const std::wstring& s, size_t& pos )
: s354( s310, NULL )
{
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s160 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s65( pst, &s160, &pend ) )
throw new s18( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s18::s19::s22 );
}
else
wh = s8::s946;
s367 = (int)s160;
pos = pend ? ( pend - pst ) : string::npos;
s516 = s828->s370();
}
void s364::s368()
{
s366[L"abs"] = new s355( L"abs", &s364::s423, s828->s370() );
s366[L"set"] = new s355( L"set", &s364::s406, s784->s370() );
s366[L"sum"] = new s355( L"sum", &s364::s407, s828->s370() );
s366[L"dif"] = new s355( L"dif", &s364::s408, s828->s370() );
s366[L"mul"] = new s355( L"mul", &s364::s409, s828->s370() );
s366[L"div"] = new s355( L"div", &s364::s410, s828->s370() );
s366[L"pow"] = new s355( L"pow", &s364::s411, s828->s370() );
s366[L"sumeq"] = new s355( L"sumeq", &s364::s412, s828->s370() );
s366[L"difeq"] = new s355( L"difeq", &s364::s413, s828->s370() );
s366[L"muleq"] = new s355( L"muleq", &s364::s414, s828->s370() );
s366[L"diveq"] = new s355( L"diveq", &s364::s415, s828->s370() );
s366[L"poweq"] = new s355( L"poweq", &s364::s416, s828->s370() );
s366[L"eq"] = new s355( L"eq", &s364::s417, s806->s370() );
s366[L"less"] = new s355( L"less", &s364::s418, s806->s370() );
s366[L"greater"] = new s355( L"greater", &s364::s419, s806->s370() );
s366[L"leq"] = new s355( L"leq", &s364::s420, s806->s370() );
s366[L"geq"] = new s355( L"geq", &s364::s421, s806->s370() );
s366[L"neq"] = new s355( L"neq", &s364::s422, s806->s370() );
s366[L"mod"] = new s355( L"mod", &s364::s424, s828->s370() );
s366[L"sqrt"] = new s355( L"sqrt", &s364::s425, s862->s370() );
s366[L"nroot"] = new s355( L"nroot", &s364::s426, s862->s370() );
s366[L"toDouble"] = new s355( L"toDouble", &s364::s427, s862->s370() );
s366[L"read"] = new s355( L"read", &s364::s428, s828->s370() );
}
s505* s364::s374( s282* s616, const std::vector<s281*>& l ) const
{
size_t pos = 0;
return new s364( s310, L"", pos );
}
void s364::s523( s282* s965 )
{
}
s281* s364::s353() const
{
return new s364( *this );
}
void s364::s375( s507 p ) const
{
if( p->s370() == s828->s370() )
*( p.s17<s364*>()->s376()) = s367;
else if( p->s370() == s806->s370() )
*( p.s17<s379*>()->s376() ) = (s367 != 0);
else if( p->s370() == s862->s370() )
*( p.s17<s377*>()->s376() ) = (double)s367;
else
throw new s18( L"No conversion to type " + s372() );
}
#define s737 ((s364*)(s506*)*s284)
#define s738 ((s379*)(s506*)*s284)
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
inline void s364::s423( s505** s284, size_t s521 )
{
int t = (int)*DR;
if( t >= 0 )
s737->s367 = t;
else
s737->s367 = -t;
}
inline void s364::s406( s505** s284, size_t s521 )
{
( (s364*)DR)->s367 = (int)*PARN(2);
}
inline void s364::s407( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) + (int)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 += (int)*PARN( n );
}
inline void s364::s408( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) - (int)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 -= (int)*PARN( n );
}
inline void s364::s409( s505** s284, size_t s521 )
{
s737->s367 = ((int)*DR) * (int)*PARN(2);
for( size_t n = 3; n < s521; ++n )
s737->s367 *= (int)*PARN( n );
}
inline void s364::s410( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) / (int)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 /= (int)*PARN( n );
}
inline void s364::s411( s505** s284, size_t s521 )
{
s737->s367 = (int)::pow( (int)*DR, (double)*PARN( 2 ) );
}
inline void s364::s412( s505** s284, size_t s521 )
{
( (s364*)DR )->s367 += (int)*PARN(2);
for( size_t n = 3; n < s521; ++n )
( (s364*)DR )->s367 += (int)*PARN(n);
s737->s367 = ( (int)*DR );
}
inline void s364::s413( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) - (int)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 -= (int)*PARN( n );
}
inline void s364::s414( s505** s284, size_t s521 )
{
s737->s367 = ((int)*DR) * (int)*PARN(2);
for( size_t n = 3; n < s521; ++n )
s737->s367 *= (int)*PARN( n );
}
inline void s364::s415( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) / (int)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 /= (int)*PARN( n );
}
inline void s364::s416( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) * ( (int)*DR ); ;
for( int n = 2; n < (int)*PARN( 2 ); ++n )
s737->s367 *= ( (int)*DR );
}
inline void s364::s417( s505** s284, size_t s521 )
{
if( ((int)*DR) == (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s418( s505** s284, size_t s521 )
{
if( ( (int)*DR ) < (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s419( s505** s284, size_t s521 )
{
if( ( (int)*DR ) > (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s420( s505** s284, size_t s521 )
{
if( ( (int)*DR) <= (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s421( s505** s284, size_t s521 )
{
if( ( (int)*DR ) >= (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s422( s505** s284, size_t s521 )
{
if( ( (int)*DR ) != (int)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s364::s424( s505** s284, size_t s521 )
{
s737->s367 = ( (int)*DR ) % (int)*PARN( 2 );
}
inline void s364::s425( s505** s284, size_t s521 )
{
*((s377*)s284[0])->s376() = ::sqrt( (double)*DR );
}
inline void s364::s426( s505** s284, size_t s521 )
{
*((s377*)s284[0])->s376() = ::pow( (int)*DR, 1.0/(double)*PARN( 2 ) );
}
inline void s364::s427( s505** s284, size_t s521 )
{
*( (s377*)s284[0] )->s376() = (double)*DR;
}
inline void s364::s428( s505** s284, size_t s521 )
{
int i;
wstring s98 = L"";//( (s378*)s284[2] )->to_wstring();
wstring si = s6::s106( s98, false );
try {
i = std::stoi( si );
}
catch( std::invalid_argument& ) {
throw new s18( L"Error: invalid input; integer is required." );
}
s737->s367 = i;
}
s505* s364::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s364( s310, s, pos );
}
else if( s.find( L"Int(" ) == 0 ) {
size_t pos = 0;
return new s364( s310, s.substr( 4, s.size() - 5 ), pos );
}
else if( s.find( L"Int" ) == 0 ) {
return s374( NULL, std::vector<s281*>() );
}
return 0;
}
size_t s364::s334() const
{
return (size_t)s367;
}
inline bool s364::operator==( const s505* p ) const
{
return ( (s364*)p )->s367 == s367;
}
inline bool s364::operator<( const s505* p ) const
{
return s367 < ( (s364*)p )->s367;
}
s505* s377::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
s.find( L"." ) != std::string::npos ) {
size_t pos = 0;
return new s377( s310, s, pos );
}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s377( s310, s4::s55( s.substr( 7, s.size() - 8 ), s4::s51 ),
pos );
}
else if( s.find( L"Double" ) == 0 ) {
return s374( s616, std::vector<s281*>() );
}
return 0;
}
void s364::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : " << s367 << endl;
}
s377::s377( s272* s310, double d ) 
: s354( s310, NULL ), s367( d )
{ 
if( s862.s14() ) {
s516 = 0;
wh = s8::s946;
}
else
s516 = s862->s370();
}
s377::s377( const s377& r )
: s354( r.s310, NULL ), s367( r.s367 )
{
wh = r.wh;
s516 = s862->s370();
}
s377::s377( s272* s310, const std::wstring& s, size_t& pos )
: s354( s310, NULL )
{
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
double s160 = 0.0;
if( !s.empty() ) {
pst = s.c_str();
if( !s66( pst, &s160, &pend ) )
throw new s18( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s18::s19::s22 );
}
else
wh = s8::s946;
s367 = s160;
pos = pend ? pend - pst : string::npos;
s516 = s862->s370();
}
s505* s377::s374( s282* s616, const std::vector<s281*>& l ) const
{
size_t pos = 0;
return new s377( s310, L"", pos );
}
void s377::s523( s282* s965 )
{
}
void s377::s368()
{
s366[L"abs"] = new s355( L"abs", &s377::s423, s862->s370() );
s366[L"set"] = new s355( L"set", &s377::s406, s784->s370() );
s366[L"sum"] = new s355( L"sum", &s377::s407, s862->s370() );
s366[L"dif"] = new s355( L"dif", &s377::s408, s862->s370() );
s366[L"mul"] = new s355( L"mul", &s377::s409, s862->s370() );
s366[L"div"] = new s355( L"div", &s377::s410, s862->s370() );
s366[L"pow"] = new s355( L"pow", &s377::s411, s862->s370() );
s366[L"sumeq"] = new s355( L"sumeq", &s377::s412, s862->s370() );
s366[L"difeq"] = new s355( L"difeq", &s377::s413, s862->s370() );
s366[L"muleq"] = new s355( L"muleq", &s377::s414, s862->s370() );
s366[L"diveq"] = new s355( L"diveq", &s377::s415, s862->s370() );
s366[L"poweq"] = new s355( L"poweq", &s377::s416, s862->s370() );
s366[L"sqrt"] = new s355( L"sqrt", &s377::s425, s862->s370() );
s366[L"nroot"] = new s355( L"nroot", &s377::s426, s862->s370() );
s366[L"eq"] = new s355( L"eq", &s377::s417, s806->s370() );
s366[L"less"] = new s355( L"less", &s377::s418, s806->s370() );
s366[L"greater"] = new s355( L"greater", &s377::s419, s806->s370() );
s366[L"leq"] = new s355( L"leq", &s377::s420, s806->s370() );
s366[L"geq"] = new s355( L"geq", &s377::s421, s806->s370() );
s366[L"neq"] = new s355( L"neq", &s377::s422, s806->s370() );
s366[L"dcmp"] = new s355( L"dcmp", &s377::s429, s828->s370() );
s366[L"dcmpr"] = new s355( L"dcmpr", &s377::s430, s828->s370() );
s366[L"toInt"] = new s355( L"toInt", &s377::s431, s828->s370() );
}
s281* s377::s353() const
{
return new s377( *this );
}
void s377::s375( s507 p ) const
{
if( p->s370() == s828->s370() )
*( p.s17<s364*>()->s376() ) = (int)s367;
else if( p->s370() == s862->s370() )
*( p.s17<s377*>()->s376() ) = s367;
else if( p->s370() == s806->s370() )
*( p.s17<s379*>()->s376() ) = ( s367 != 0.0 );
else
throw new s18( L"No conversion to type " + s372() );
}
std::wstring s377::to_wstring() const 
{
wstring s = std::to_wstring( s367 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
return s.substr(0, pl);
}
#undef s737
#define s737 ((s377*)(s506*)*s284)
#define INTRES ((s364*)(s506*)*s284)
inline void s377::s406( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 = (double)*PARN( 2 );
}
void s377::s423( s505** s284, size_t s521 )
{
double t = (double)*DR;
if( t >= 0 )
s737->s367 = t;
else
s737->s367 = -t;
}
inline void s377::s409( s505** s284, size_t s521 )
{
s737->s367 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 *= (double)*PARN( n );
}
inline void s377::s407( s505** s284, size_t s521 )
{
s737->s367 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 += (double)*PARN( n );
}
inline void s377::s410( s505** s284, size_t s521 )
{
s737->s367 = ( (double)*DR ) / (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 /= (double)*PARN( n );
}
inline void s377::s408( s505** s284, size_t s521 )
{
s737->s367 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
s737->s367 -= (double)*PARN( n );
}
inline void s377::s412( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 += (double)*PARN(2);
for( size_t n = 3; n < s521; ++n )
( (s377*)DR )->s367 += (double)*PARN(n);
s737->s367 = ( (double)*DR );
}
inline void s377::s413( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 -= (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
( (s377*)DR )->s367 -= (double)*PARN( n );
s737->s367 = ( (double)*DR );
}
inline void s377::s414( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 *= (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
( (s377*)DR )->s367 *= (double)*PARN( n );
s737->s367 = ( (double)*DR );
}
inline void s377::s415( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 /= (double)*PARN( 2 );
for( size_t n = 3; n < s521; ++n )
( (s377*)DR )->s367 /= (double)*PARN( n );
s737->s367 = ( (double)*DR );
}
inline void s377::s416( s505** s284, size_t s521 )
{
( (s377*)DR )->s367 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s521; ++n )
( (s377*)DR )->s367 = ::pow( (double)*DR, (double)*PARN( n ) );
s737->s367 = ( (double)*DR );
}
inline void s377::s417( s505** s284, size_t s521 )
{
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s418( s505** s284, size_t s521 )
{
if( ((double)*DR) < (double)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s419( s505** s284, size_t s521 )
{
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s420( s505** s284, size_t s521 )
{
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s421( s505** s284, size_t s521 )
{
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s422( s505** s284, size_t s521 )
{
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s377::s425( s505** s284, size_t s521 )
{
s737->s367 = ::sqrt((double)*DR);
}
inline void s377::s426( s505** s284, size_t s521 )
{
*( (s377*)s284[0] )->s376() = ::pow( (double)*DR, (double)*PARN( 2 ) );
}
inline void s377::s429( s505** s284, size_t s521 )
{
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s376() = 0;
else
*INTRES->s376() = 1;
}
else {
if( dr - dl <= diff )
*INTRES->s376() = 0;
else
*INTRES->s376() = -1;
}
}
inline void s377::s430( s505** s284, size_t s521 )
{
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s376() = 0;
else
*INTRES->s376() = 1;
}
else {
if( dr / dl - 1 <= diff )
*INTRES->s376() = 0;
else
*INTRES->s376() = -1;
}
}
inline void s377::s411( s505** s284, size_t s521 )
{
s737->s367 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );
}
inline void s377::s431( s505** s284, size_t s521 )
{
*( (s364*)s284[0] )->s376() = (int)*DR;
}
void s377::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : " << s367 << endl;
}
size_t s377::s334() const
{
return hash<double>{}( s367 );
}
inline
int dcmp( double d1, double d2, int iDigs )
{
double s90 = fabs( d1 - d2 );
double prec = 1 / pow( (double)10.0, iDigs );
if ( s90 < prec )
return 0;
if ( d1 < d2 )
return 1;
return -1;
}
inline
int dcmp_( double d1, double d2, double dif )
{
double s90 = fabs( d1 - d2 );
if ( s90 < dif )
return 0;
if ( d1 < d2 )
return 1;
return -1;
}
inline bool s377::operator==( const s505* p ) const
{
return ( dcmp_( ( (s377*)p )->s367, s367, 0.00000001 ) == 0 ); // FIX:
}
inline bool s377::operator<( const s505* p ) const
{
return ( dcmp_( s367, ( (s377*)p )->s367, 0.00000001 ) < 0 ); // FIX:
}
s379::s379( s272* s310, const std::wstring& s, size_t& pos )
: s354( s310, NULL )
{
if( s.empty() )
s367 = false;
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s367 = (s[0] == L'1');
pos++;
}
else if( s.find( s8::s455 ) == 0 ) {
s367 = true;
pos += 4;
}
else if( s.find( s8::s456 ) == 0 ) {
s367 = false;
pos += 5;
}
else
throw new s18( L"unknown bool format: " + s.substr( 0, 20 ) );
s516 = s806->s370();
}
s379::s379( const s379& right )
: s354( right.s310, NULL ), s367( right.s367 )
{
s516 = s806->s370();
}
s379::s379( s272* s310, bool b )
: s354( s310, NULL ), s367( b )
{
s516 = s806.s14() ? 0 : s806->s370();
}
void s379::s368()
{
s366[L"set"] = new s355( L"set", &s379::s406, s784->s370() );
s366[L"not"] = new s355( L"not", &s379::s432, s806->s370() );
s366[L"eq"] = new s355( L"eq", &s379::s417, s806->s370() );
}
void s379::s523( s282* s965 )
{
}
s505* s379::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s379( s310, false );
}
s505* s379::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
if( s.find( s8::s455 ) == 0 || s.find( s8::s456 ) == 0 )
return new s379( s310, ( s.find( s8::s455 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s379( s310, s.substr( 5, s.size() - 6 ), pos );
}
else if( s.find( L"Bool" ) == 0 ) {
return s374( s616, std::vector<s281*>() );
}
return NULL;
}
s281* s379::s353() const
{
return new s379( *this );
}
void s379::s375( s507 p ) const
{
if( p->s370() == s806->s370() )
p.s17<s379*>()->s367 = s367;
else if( p->s370() == s828->s370() )
*( p.s17<s364*>()->s376() ) = (int)s367;
else if( p->s370() == s862->s370() )
*( p.s17<s377*>()->s376() ) = (double)s367;
else
throw new s18( L"No conversion to type " + s372() );
}
#undef s737
#define s737 ((s379*)(s506*)*s284)
inline void s379::s406( s505** s284, size_t s521 )
{
( (s379*)DR )->s367 = ( (s379*)PARN( 2 ) )->s367;
}
inline void s379::s432( s505** s284, size_t s521 )
{
( (s379*)DR )->s367 = !( (s379*)DR )->s367;
s737->s367 = ( (s379*)DR )->s367;
}
inline void s379::s417( s505** s284, size_t s521 )
{
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
void s379::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : " << to_wstring() << endl;
}
size_t s379::s334() const
{
return hash<bool>{}( s367 );
}
inline bool s379::operator==( const s505* p ) const
{
return ( s367 == ((s379*)p)->s367 );
}
inline bool s379::operator<( const s505* p ) const
{
return ( s367 < ((s379*)p)->s367 );
}
s380::s380( s272* s310, const std::wstring& s/* = std::wstring( L"" )*/ )
: s354( s310, NULL ), s81( s )
{
wh = s8::s459;
s516 = s879.s14() ? 0 : s879->s370();
}
s380::s380( const s380& r )
: s354( r.s310, NULL ), s81( r.s81 )
{
s516 = r.s516;
wh = r.wh;
}
void s380::s368()
{
s366[L"report"] = new s355( L"report", &s380::s847, s784->s370() );
s366[L"str"] = new s355( L"str", &s380::s532, s846->s370() );
}
void s380::s523( s282* s965 )
{
}
s505* s380::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s380( s310 );
}
s281* s380::s353() const
{
return new s380( *this );
}
void s380::s375( s507 p ) const
{
p.s17<s380*>()->s81 = s81;
}
s505* s380::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
if( s.find( L"Exception(" ) == 0 )
return new s380( s310, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s374( s616, std::vector<s281*>() );
return NULL;
}
#undef s737
#define s737 ((s380*)(s506*)*s284)
inline void s380::s847( s505** s284, size_t s521 )
{
wcout << ( (s380*)DR )->s81;
}
inline void s380::s532( s505** s284, size_t s521 )
{
*( (s378*)s284[0] )->s376() = ( (s380*)DR )->s81;
}
void s380::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : -" << endl;
}
size_t s380::s334() const
{
throw new s18( L"9: not implemented" );
}
bool s380::operator==( const s505* p ) const
{
return ( (s380*)p )->s81 == s81;
}
bool s380::operator<( const s505* p ) const
{
return s81 < ( (s380*)p )->s81;
}
s383::s383( s272* s310 ) 
: s354( s310, NULL )
{ 
s516 = s784.s14() ? 0 : s784->s370();
}
void s383::s523( s282* s965 )
{
}
s505* s383::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s383( s310 );
}
s505* s383::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
if( s.find( L"Null" ) == 0 )
return s384;
return NULL;
}
s281* s383::s353() const
{
return (s281*)this;
}
void s383::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : -" << endl;
}
size_t s383::s334() const
{
throw new s18( L"not implemented" );
}
bool s383::operator==( const s505* p ) const
{
return ( this == p );
}
bool s383::operator<( const s505* p ) const
{
return false;
}
s403::s403( s272* s310, s493 pc ) 
: s354( s310, NULL )
{ 
s515 = pc;
s516 = s832.s14() ? 0 : s832->s370(); 
}
void s403::s523( s282* s965 )
{
}
s505* s403::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s403( s310 );
}
s505* s403::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
throw new s18( L"no parser for NoValue" );
return NULL;
}
s281* s403::s353() const
{
return (s281*)this;
}
void s403::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : -" << endl;
}
size_t s403::s334() const
{
throw new s18( L"not implemented" );
}
bool s403::operator==( const s505* p ) const
{
return false;
}
bool s403::operator<( const s505* p ) const
{
return false;
}
s390::s390( const std::wstring& s, s272* s310, s493 cat )
: s506( s310, cat ), s391( s ), s395( 0 )
{
assert( cat == s496 || cat == s503 || cat == s1177 );
}
s390::s390( const s390& right )
: s506( right.s310, s496 ), s391( right.s391 ), s393( right.s393 ), s395( 0 )
{
}
void s390::s523( s282* s615 )
{
if( s310->s230( s391, (s505*)s392 ) ) {
s515 = s503;
s516 = s832->s370();
}
else {
if( !s615->s583( s391, this, s615->s903() ) )
throw new TDException( 0, s1021, NULL, s391 );
s516 = s393->s370();
}
}
s505* s390::s396() const
{
if( s394.empty() )
return s392.s17<s505*>();
s506* s721 = s392.s17<s282*>()->s626( *(size_t*)&s394[0] );
for( size_t n = 1; n < s395; ++n )
s721 = ((s282*)s721->s519())->s626( *( (size_t*)&s394[0] + n ) );
return s721->s519();
}
s505* s390::s397()
{
if( s394.empty() )
return s392.s17<s505*>();
s505*	s721 = ((s505*)s392.s17<s282*>()->s626( *(size_t*)&s394[0] ));
for( size_t n = 1; n < s395; ++n )
s721 = (s505*)((s282*)s721)->s626( *( (size_t*)&s394[0] + n ) );
return s721;
}
void s390::s1082( const std::vector<std::wstring> &s881 )
{
if( std::find( begin( s881 ), end( s881 ), s647() ) != end( s881 ) ) {
s515 = s1177;
s516 = s832->s370();
s392 = s832.s17<s505*>();
}
}
s508 s390::s520( s505** s284, size_t s521 )
{
return s396()->s520( s284, s521 );
}
s505* s390::s519()
{
return s396()->s519();
}
/*bool s390::s525( const s505* s526 ) const
{
if( s526->s517() == s496 )
return s396()->s525( ((s390*)s526)->s396() );
return s396()->s525( s526 );
}*/
s281* s390::s353() const
{
return new s390( *this );
}
void s390::s398( size_t off, const s505* proto )
{
s394.push_back( off );
s395 = s394.size();
s393 = proto;
}
void s390::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"DataRef : " << s391 << endl;
}
s349::s349( const s349& right )
: s281( right.s310, s498 ), str( right.str )
{
}
s281* s349::s353() const
{
return new s349( *this );
}
void s349::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"DataStub : " << str << endl;
}
const wstring s492 = L"";
s504 s723;
s282::s282( s272* s310, s1175 s358, s493 pc/* = s494*/, const s273* ast_ )
: s505( s310, pc, ast_ ), ns( NULL ), s365( s492 ), //s665( s723 ),
s660( NULL )
{
s656 = this;
s516 = s358;
}
s282::s282( const s282& proto, const s273* ast_ )
: s505( proto.s310, proto.s515, ast_ ), s656( &proto ), ns( proto.ns ), s365( proto.s288 ),
s660( proto.s660 ), //s665( s723 ),
s662( proto.s662 )
{
s516 = proto.s516;
if( s515 == s500 )
s515 = s502;
if( proto.s657 )
proto.s657->s676( this );
proto.s659.copy( s659, this, NULL, s504::s154 );
for( size_t n = 0; n < s662.size(); ++n )
s661.push_back( s659.get( s662[n] ) );
}
s282::s282( const wstring& s712, s272* s310, s493 pc, const s273* ast_ )
: s505( s310, pc, ast_ ), ns( NULL ), s365( s492 ), s288( s712 ),
s660( NULL )//, s665( *new s504() )
{
s656 = this;
}
s282::s282( s273& s740, s272* s310, s493 pc, s282* ns_, s563 am, 
s654& cl, s653& cnl, s655& al )
: s505( s310, pc, &s740 ), s657( NULL ), ns( ns_ ), s365( s740.s309() ), s288( s740.s308() ),
s659( am ), s660( NULL ) //,s665( *new s504() )
{
if( s288.find( L" " ) != string::npos )
throw new s18( L"Malformed class name: " + s288 );
s656 = this;
if( pc == s500 ) {
wstring anc = L"";
try {
const s273* s729 = s740.s302( s8::s489 );
anc = s729->s301();
}
catch( s18* e ) {
if( e->which() != (uint32_t)s18::s19::s25 )
throw e;
}
cnl.push_back( make_pair( s740.s309(), anc ) );
if( cl.find( s740.s309() ) != cl.end() )
throw new s18( L"class already exists: " + s740.s309() );
cl.insert(make_pair(s740.s309(), this));
}
if( al.find( s740.s309() ) != al.end() )
throw new s18( L"object already exists: " + s740.s309() );
al.insert(make_pair(s740.s309(), &s740));
s530( L"proto" );
s273::s285& s741 = s740.s303();
s273::s285::iterator it = s741.begin();
vector<pair<wstring,wstring>> s730;
for( ; it != s741.end(); ++it ) {
if( it->second->s307() == s234 ) {
if( it->first == s8::s489 ) {
s658 = it->second->s301();
}
}
else if( it->second->s307() == s236 ) {
wstring s691 = it->first;
s537 pv = s540;
am = s535;
size_t s725 = s691.find_first_of( s4::s51 );
if( s725 != string::npos ) {
vector<wstring> s724;
s4::s60( it->first, wstring( 1, s691[s725] ), s724 );
if( s724.size() > 3 )
throw new s18( L"malformed block name: " + it->first );
if( s724[0] == s8::s470 || s724.size() == 3 ) {
pc = s500;
if( s724.size() == 3 ) {
if( s724[0] == s8::s467 )
am = s534;
else if( s724[0] == s8::s469 )
am = s536;
else if( s724[0] != s8::s468 )
throw new s18( L"invalid access mode name: " + it->first );
s691 = s724[2];
}
else
s691 = s724[1];
if( s741.find( s691 ) != s741.end() )
throw new s18( L"duplicated object name: " + it->first );
it->second->s304( s691 );
s730.push_back( make_pair( it->first, s691 ) );
}
else if( s724[0] == L"access" && ( s724[1] == L"allow" || s724[1] == L"deny" )) {
if( s724[1] == L"allow" )
pv = s539;
pc = s501;
}
else
throw new s18( L"unknown object type: " + s724[0] );
}
if( pc == s501 ) {
s659.s576( pv, it->second );
}
else {
s282* ob = new s282( *it->second, s310, s500, this, am, cl, cnl, al );
s659.s568( ob->s309(), ob );
}
}
}
for( size_t n = 0; n < s730.size(); ++n ) {
auto it = s741.find( s730[n].first );
s741.insert(make_pair(s730[n].second, it->second ));
s741.erase( it );
}
}
s505* s282::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
return s667( s740, s350 );
}
void s282::s677( const s504& s284 )
{
}
bool
s282::s525( const s505* s526 ) const
{
if( s526->s370() == s370() )
return true;
if( s657 )
return s657->s525( s526 );
return false;
}
bool
s282::s773( const wstring& f ) const
{
return s659.s163( f );
}
void s282::s161( s273& s740 )
{
s273::s285& s741 = s740.s303();
s273::s285::iterator it = s741.begin();
for( ; it != s741.end(); ++it ) {
s273* node = it->second;
if( node->s307() == s234 ) {
wstring s79 = node->s309();
if( s79 == s8::s462 )
s678( *node );
else if( s79 == s8::s489 )
s670( *node );
else if( s79 == s8::s1027 )
s1068( *node );
else {
s505* dv = s310->TR().s545( *node, this, s288 );
dv->s530( node->s309() );
try {
s659.s568( node->s309(), dv );
}
catch( s18* e ) {
if( e->which() == (uint32_t)s18::s19::s23 ) {
e->s32( L"Symbol already defined: " + s288 + L"::" + node->s309() );
}
throw e;
}
s661.push_back( dv );
s662.push_back( node->s309() );
}
}
else if( node->s307() == s236 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s282* ob = (s282*)s659.get( it->first );
ob->s161( *it->second );
}
}
else if( node->s307() == s237 ) {
}
}
it = s741.begin();
for( ; it != s741.end(); ++it ) {
s273* node = it->second;
if( node->s307() == s235 ) {
s510 func = s619::s627( *node, s310, this,
node->s309(), s288 );
s659.s568( func->s309(), func.s17<s505*>() );
s661.push_back( func );
s662.push_back( func->s309() );
}
}
}
void s282::s523( s282* s965 )
{
if( s658.size() ) {
s657 = (s282*)s310->s231( s658, s965->s903() );
s657->s660->copy( *s660 );
}
if( s660 )
s660->s523( s310, s288 );
else
s660 = s656->s660;
s659.s523( s965, (s515 == s500));
if( s659.s163( s8::s448 ) ) {
vector<s506*> s284;
s284.push_back( this );
s915* p = (s915*) s659.get( s8::s448 );
p->s523( s965->s903(), true );
p->s520( (s505**)&s284[0], 1 );
}
}
void s282::s676( s282* s679 ) const
{
if( s657 )
s657->s676( s679 );
}
void s282::s678( s273& s740 )
{
if( !s660 )
s660 = new s578();
s660->s581( s740.s301() );
return;
}
void s282::s671( const wstring& s350,	vector<wstring>& s160 )
{
s659.s560( s350, s160 );
}
void s282::s582( const wstring& s79, const wstring& s585 )
{
if( !s660 )
s660 = new s578();
s660->s582( s79, s310, s585 );
}
void s282::s670( s273& s740 )
{
s657 = (s282*)s310->s231( s658, s288 );
}
void s282::s1068( s273& s740 )
{
wstring s1097 = L"wrong syntax of class attributes: " + s740.s301();
s508 dv = s310->TR().s545( s740, this, s288 );
if( dv->s370() != s768->s370() )
throw new s18( s1097 );
vector<s507>& v = dv.s17<s327*>()->s332();
for( auto s_ : v ) {
wstring s = s_.s17<s378*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s18( s1097 );
wstring cat = s4::s55( s.substr( 0, pl ), s4::s51 );
vector<wstring> s160;
s4::s60( s.substr( pl + 1 ), L",", s160 );
for( auto at : s160 ) {
s310->TR().s1067( s370(), cat, at );
}
}
}
bool s282::s583( const wstring& sym_, 
s390* ref, const wstring& s350 ) const
{
bool s721 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s722 = sym_.substr( 0, pl );
s282* ob = ((s282*)s674( s722, s350, false ));
if( ob ) {
s721 = ob->s583( sym, ref, s350 );
}
else {
s721 = s660->s583( sym, ref );
}
}
else {
s282* ob = ((s282*)s674( sym, s350, false ));
if( ob ) {
if( !ref->s399() )
ref->s401( ( s505* )this );
ref->s398( s672( sym ), ob );
s721 = true;
}
else {
if( s660 )
s721 = s660->s583( sym, ref );
}
}
return s721;
}
size_t s282::s672( const std::wstring& s680 ) const
{
for( size_t n = 0; n < s661.size(); ++n ) {
if( s662[n] == s680 )
return n;
}
throw new s18( L"3: Symbol does not exist: " + s680 );
}
s281* s282::s626( size_t off )
{
return s661[off];
}
void s282::s925( const std::wstring& s79, s505* s367 )
{
s659.s568( s79, s367 );
s661.push_back( s367 );
s662.push_back( s79 );
}
s505* s282::s674( const wstring& sym, const wstring& s350, 
bool s547/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s282* mod = (s282*) s659.get( smod, s547 );
if( !mod )
return NULL;
return mod->s674( sym1, s350, s547 );
}
wstring sym1 = sym;
if( sym.size() > 2 && ( sym.find( L"()" ) == sym.size() - 2 ) )
sym1 = sym.substr( 0, sym.size() - 2 );
s508 s721 = s659.get( sym1, false );
if( !s721 && s547 )
throw new s18( L"4: Symbol does not exist: " + sym, 
(uint32_t)s18::s19::s25 );
if( s721 && !s675( sym1, s350 ) ) {
if( s547 )
throw new s18( L"4: Symbol not found: " + sym,
(uint32_t)s18::s19::s25 );
s721 = NULL;
}
return s721;
}
bool s282::s675( const wstring& sym, const wstring& s522 ) const
{
return s659.s577( sym, s522 );
}
s1175 s282::s405( const wstring& s361 ) const
{
s505* s726 = s659.get( s361 );
s1175 s721 = s726->s370();
if( s721 == 0 ) {
s726->s523( (s282*)this );
s721 = s726->s370();
}
return s721;
}
s505* s282::s667( const s273& s740, const std::wstring& s350 )
{
vector<wstring> s727;
vector<s281*> s284;
s282* s721 = new s282( *this );
size_t pos = s740.s301().find( L"(" );
size_t pos_ = pos;
s273::s298( s740.s301(), pos, s727 );
if( s727.size() ) {
s619* s728 = (s619*) s659.get( s8::s447, false );
if( !s728 )
throw new s18( L"Arguments passed to a class without init function." );
else {
wstring str = s740.s301();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s8::s447 );
s273 ast_( s8::s448, s148( str ) );
s512 cs = (s588*)s281::s528( ast_, s310, s721, s350 );
s619* td = s619::s628(
cs, s310, s721, (s619*)s721, s288 );
s721->s659.s568( s8::s448, td );
}
}
return s721;
}
s505* s282::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s282( *(s282*)this );
}
std::wstring s282::s308() const
{
return /*s287 + L"::" +*/ s288;
}
s505* s282::s362( const std::wstring& s712, const std::wstring& s350,
bool s547 /*= true*/ ) const
{
s390 ref( s712, s310 );
if( !s583( s712, &ref, s350 ) )
return NULL;
return ref.s397();
}
s281* s282::s353() const
{
return new s282( *this );
}
void s282::s375( s507 p ) const
{
throw new s18( L"" );
vector<wstring> fields;
s659.s572( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s505*)s659.get( fields[n] ))->s375( p );
}
size_t s282::s334() const
{
return (size_t)this;
}
bool s282::operator==( const s505* p ) const
{
return (this == p);
}
bool s282::operator<( const s505* p ) const
{
return false;
}
wstring s282::to_wstring() const
{
return L"";
}
void s282::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s365;
if( s515 == s500 ) s365 = L"Class";
else if( s515 == s501 ) s365 = L"Module";
else if( s515 == s502 ) s365 = L"Object";
else s365 = L"ERROR";
buf << s4::fill_n_ch( L' ', s205 ) << s365 << L" : " << s288 << L"/" << s391 << endl;
s659.s314( pd, s205 + s438 );
}
s619* s619::s627( const s273& s740, s272* s310, s282* obj,
const wstring& s288, const wstring& s585 )
{
const s273::s285& s741 = s740.s303();
size_t s736 = s741.size();
std::vector<s281*> s284;
for( size_t n = 0; n < s736; ++n ) {
s273::s285::const_iterator it = s741.find( std::to_wstring( n ) );
if( it->second->s301() == s8::s1032)
s284.push_back( s954 );
else
s284.push_back( s281::s528( *it->second, s310, obj, s585 ) );
}
Transd* s721 = NULL;
size_t s725 = s288.find_first_of( s4::s51 );
if( s725 != string::npos ) {
vector<wstring> s724;
s4::s60( s288, wstring( 1, s288[s725] ), s724 );
if( s724.size() > 2 )
throw new s18( L"malformed function name: " + s288 );
if( s724[0] == s8::s450 ) {
s721 = new s632( s310, obj, NULL, s284, &s740 );
s721->s288 = s724[1];
}
else if( s724[0] == s8::s451 ) {
s721 = new s915( s310, obj, NULL, s284, &s740 );
s282* pAnc = (s282*)s310->s231( obj->s669(), s585 );
((s632*)pAnc->s362( s724[1], s585 ))->s681( obj->s370(),
s721 );
s721->s288 = s724[1];
s721->s622( s601 );
}
else
throw new s18( L"malformed function name: " + s288 );
}
else {
s721 = new s915( s310, obj, NULL, s284, &s740 );
s721->s288 = s288;
}
return s721;
}
s588* s619::s1240( const s273& s740, s272* s310, s282* obj, 
const wstring& s585 )
{
const s273::s285& s741 = s740.s303();
size_t s736 = s741.size();
wstring s629 = s740.s301();
std::vector<s281*> s284;
s588* s721 = NULL;
try {
for( size_t n = 0; n < s736; ++n ) {
s273::s285::const_iterator it = s741.find( std::to_wstring( n ) );
it->second.s17<s273*>()->s279( L"ownerType", L"CallSite" );
it->second.s17<s273*>()->s279( L"ownerName", s629 );
if( it->second->s301() == s8::s1032 )
s284.push_back( s954 );
else
s284.push_back( s281::s528( *it->second, s310, obj, s585 ) );
}
s721 = new s588( s310, s629, s284, &s740 );
}
catch( s18* e ) {
throw e->s32( L"\nwhile processing '" + s629 + L"' function call" );
}
return s721;
}
void s588::s523( s282* s965 )
{
return;
for( size_t n = 0; n < s284.size(); ++n ) {
s284[n]->s523( s965 );
}
}
s281* s588::s353() const
{
return new s588( *this );
}
s619* s619::s628( s588* cs, s272* s310, s282* s616, s619* s223, 
const wstring& s585 )
{
wstring s629 = cs->s309();
wstring s743 = s616 ? s616->s308() : L"::";
s507 s742 = NULL;
std::vector<s281*>& s284 = cs->s630();
s510 s745 = NULL;
size_t pl = s629.find( L"<" );
if( pl == string::npos ) {
if( s629 == s242 || s629 == s266 || s629 == s267 ||
s629 == s263 || s629 == s269 || s629 == s270 ||
s629 == s878 || s629 == s808 || s629 == s261
|| s629 == s928 || s629 == s991 )
return s310->s222( cs->s309(), cs->s630(), s616, s223, cs->s631() );
s281* par = NULL;
if( s284.size() ) {
par = s284[0];
s493 pc = par->s517();
if( pc == s496 ) {
try {
par->s523( s223 );
}
catch( TDException* e ) {
if( e->Category() != s1021 )
throw e->s32( L"while compiling function '" + s629 + L"'" );
}
if( ( (s390*)par )->s400().s15() ) {
if( ( (s390*)par )->s647() == s8::s449 )
par = s616;
s742 = ( (s390*)par )->s396();
}
}
else {
if( pc == s498 ) {
s1039 ast_ = new s273( ( (s349*)par )->Str() );
par = s310->TR().s545( *ast_, s616,
((s349*)par)->s352() );
}
else if( pc == s499 ) {
s512 cs = new s588( *(s588*)par );
par = s628( cs, s310, s616, s223, s585 );
((s619*)par)->s523( s743, false );
}
else {
par->s523( s223 );
}
}
if( par->s517() == s496 ) {
(void)0;
}
else if( par->s517() == s1177 || par->s517() == s503 )
s742 = NULL;
else {
s742 = par->s519();
s742->s523( s223 );
}
s284[0] = par;
}
else{
s745 = (s619*) s616->s362( s629, s743, false );
if( !s745 )
throw new s18( L"Procedure is not resolved: " + s629 );
}
s619* BIFunc = s310->s222( s629, s284, s616, s223, cs->s631() );
if( BIFunc )
return BIFunc;
}
else {
wstring s650 = s629.substr( pl + 1, s629.size() - pl - 2 );
s629 = s629.substr( 0, pl );
s1039 ast2 = new s273( s650 );
s742 = s310->TR().s545( *ast2, s616, s585 );
}
s619* s721 = NULL;
s510 s746 = NULL;
s646 s589 = NULL;
if( !s745 )  {
s493 s749 = s742->s517();
if( s749 == s496 ) {
s390* ref = (s390*)s742.s17<s506*>();
s742 = (s505*)ref->s527();
s749 = s742->s517();
}
try {
if( s749 == s502 || s749 == s501 )
s746 = (s619*)s742.s17<s282*>()->s362( s629, s743, false );
else if( s749 == s495 )
s589 = s742.s17<s354*>()->s362( s629 );
}
catch( s18* e ) {
if( e->which() != (uint32_t)s18::s19::s25 )
throw;
}
if( !s746 && !s589 )
s745 = (s619*)s616->s362( s629, s743, false );
if( !( s589 || s745 || s746 ) )
throw new s18( L"Method is not resolved: " + s629 );
}
if( s589 ) {
s721 = new s914( s310, s223, s284, s589, 
s742.s17<s505*>()->s405( s629 ), cs->s631() );
s721->s602 = s593;
}
else if( s745 ) {
s721 = new s915( *s745.s17<s915*>(), s616, s223, s284, cs->s631() );
s721->s602 = s594;
}
else if( s746 ) {
s10<s915> td = ((s915*)s746->s353());
s284.erase( s284.begin() );
s721 = new s915( *td, s742.s17<s282*>(), s223, s284, cs->s631() );
if( s746->s623() == s600 )
s721->s602 = s596;
else
s721->s602 = s595;
}
s721->s288 = s629;
return s721;
}
s619::s619( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l,
const s273* s740 )
: s282( s310, 0, s497, s740 ), s603( s599 ),
s614( NULL ),	s616( s620 ), s615( s621 ), past( s740 )
{
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ((s505*)l[n]) == s954 ) {
if( l.size() == n )
throw new s18( L"malformed lambda definition" );
s516 = l[n + 1]->s370();
n += 2;
break;
}
if( l[n]->s517() != s496 )
break;
s390* s79 = (s390*) l[n];
s505* ex = (s505*) l[n + 1];
if( ex->s517() != s495 && ex->s517() != s502 && 
ex->s517() != s501 && ex->s517() != s498 )
throw new s18( L"incorrect syntax for lambda parameter " + s79->s647() +
L"; should be a type constructor.", (uint32_t)s18::s19::s22 );
s659.s568( s79->s647(), ex );
s610.push_back( (s505*)ex );
s661.push_back( (s505*)ex );
s662.push_back( s79->s647() );
}
s612.insert( s612.end(), l.begin() + n, l.end() );
}
s619::s619( const s619& right, s282* s620, s619* s621,
const std::vector<s281*>& s744, const s273* s740 )
: s282( right.s310, right.s516, right.s515, s740 ), s288( right.s288 ), 
s603( right.s603 ),	s614( NULL ), s616( s620 ), s615( s621 ), past( s740 )
{
s516 = right.s516;
s602 = right.s602;
s661 = right.s661;
s662 = right.s662;
s659 = right.s659;
s610 = right.s610;
if( s744.size() ) {
s284.assign( s744.begin(), s744.end() );
for( size_t n = 0; n < s284.size(); ++n ) {
s659.s568( s662[n], s284[n].s17<s505*>(), s504::s154 );
s661[n] = s284[n];
}
}
else
s284.assign( right.s284.begin(), right.s284.end() );
s612 = right.s612;
}
s914::s914( s272* s310, s619* s621, const vector<s281*>& l,
s646 s747, s1175 s748, const s273* s740 )
: s619( s310, s621, s621, s593, L"", s740 ),
s589( s747 )
{
s603 = s599;
s516 = s748;
s284.assign( l.begin(), l.end() );
}
s915::s915( const s915& right, s282* s620, s619* s621,
const std::vector<s281*>& s744, const s273* s740 )
: s619( right.s310, s620, s621, s595, L"", s740 )
{
s602 = right.s602;
s516 = right.s516;
s661 = right.s661;
s662 = right.s662;
s659 = right.s659;
s610 = right.s610;
s603 = right.s603;
s288 = right.s288;
s614 = NULL;
if( s744.size() ) {
s284.assign( s744.begin(), s744.end() );
/*for( size_t n = 0; n < s284.size(); ++n ) {
s659.s568( s662[n], s284[n].s17<s505*>(), s504::s154 );
s661[n] = s284[n];
}*/
}
else
s284.assign( right.s284.begin(), right.s284.end() );
s612 = right.s612;
}
s619::~s619()
{
/*	for( size_t n = 0; n < s284.size(); ++n ) {
delete s284[n].s17<s506*>();
}*/
}
s588::s588( s272* pass_, const std::wstring& s197, const vector<s281*>& l, 
const s273* ast_ )
: s281( pass_, s499 ), s629( s197 ), past( (s273*)ast_ )
{
s284.assign( l.begin(), l.end() );
}
s588::s588( const s588& right )
: s281( right.s310, s499 ), s629( right.s629 ), past( right.past )
{
for( size_t n = 0; n < right.s284.size(); ++n ) {
s284.push_back( right.s284[n]->s353() );
}
}
wstring s619::s903() const
{ 
if( s616.s15() )
return s616->s308();
else if( s602 == s593 )
return L"::";
else
throw new s18( L"Cannot get module name." );
}
s281* s619::s921( s281* par )
{
s281* s721;
if( par->s517() == s498 ) {
s1039 ast_ = new s273( ( (s349*)par )->Str() );
s721 = s310->TR().s545( *ast_, s616,
((s349*)par)->s352() );
}
else if( par->s517() == s499 ) {
s512 cs = new s588( *((s588*)par) );
s721 = s628( cs, s310, s616, this, s308() );
((Transd*)s721)->s523( s706, false );
}
else
return par;
return s721;
}
void s619::s617(const std::wstring& s350)
{
for( size_t n = 0; n < s610.size(); ++n ) {
s281* fpar = s610[n];
s493 pc = fpar->s517();
if( pc == s498 ) {
}
else
s610[n]->s523( s615 );
}
}
void s619::s523( const wstring& s350, bool proc/*=false*/ )
{
s706 = s350;
if( s616 && (s616->s517() == s501 || s616->s517() == s500 )) {
s617( s350 );
if( s616->s517() == s500 )
return;
}
for( size_t n = 0; n < s284.size(); ++n ) {
s507 par = s284[n];
if( par->s517() == s496 ) {
if( par.s17<s390*>()->s400().s14() )
par.s17<s390*>()->s523( this );
s611.push_back( NULL );
}
else if( par->s517() == s1177 || par->s517() == s503 )
s611.push_back( NULL );
else {
try {
s284[n] = s921( par );
}
catch( s18* e ) {
throw e->s32( L"\nwhile linking '" + s288 + L"' function " );
}
s611.push_back( s284[n]->s519() );
}
}
if( s602 == s592 ) {
if( s288 == s242 ) {
for( size_t n = 0; n < s284.size(); ++n ) {
s659.s568( s662[n], s284[n].s17<s505*>(), s504::s154 );
s284[n]->setWh( s8::s945 );
s661[n] = s284[n];
}
}
for( size_t n = 0; n < s612.size(); ++n ) {
if( s612[n]->s517() == s499 ) {
s512 cs = new s588( *s612[n].s17<s588*>() );
s612[n] = s628( cs, s310, s616, this, s616->s309() );
}
else if( s612[n]->s517() == s496 )
s612[n].s17<s390*>()->s523( s615 );
else if( s612[n]->s517() != s497 )
s612[n]->s523( s615 );
else // lambda - ?
throw new s18( L"unhandled expression" );
}
for( auto it : s612 ) {
if( it->s517() == s497 )
it.s17<Transd*>()->s523( s350, true );
}
if( !s516 && s612.size() ) {
s516 = s612.back()->s370();
}
}
if( s516 ) {
s614 = s310->TR().s545( s370(), s616, s350 );
s614->s523( s615 );
s614->setWh( s8::s945 );
s611.insert( s611.begin(), s614 );
if( s284.size() ) {
s608 = (s506**)&s284[0];
nlocs = s284.size();
s607 = &s611[0];
s521 = s611.size();
}
else {
s608 = NULL;
s607 = NULL;
nlocs = s521 = 0;
}
}
s1080.resize( s611.size() );
}
void s914::s523( const wstring& s350, bool proc/*=false*/ )
{
s706 = s350;
s619::s523( s350, proc );
s281* par = s284[0];
s493 s749 = par->s517();
if( s749 == s496 ) {
s390* ref = (s390*)par;
s508 pobj = ref->s396();
s749 = pobj->s517();
s516 = pobj.s17<s354*>()->s405( s288 );
}
if( s614.s14() ) {
throw new s18( L"check for code reachability" );
s614 = s310->TR().s545( s370(), s616, s350 );
s614->s523( s615 );
s614->setWh( s8::s945 );
s611.insert( s611.begin(), s614 );
if( s284.size() ) {
s608 = (s506**)&s284[0];
nlocs = s284.size();
s607 = &s611[0];
s521 = s611.size();
}
else {
s608 = NULL;
s607 = NULL;
nlocs = s521 = 0;
}
}
s1080.resize( s611.size() );
}
void s915::s523( const wstring& s350, bool proc/*=false*/ )
{
s706 = s350;
if( s616->s517() == s501 || s616->s517() == s500 ) {
s617( s350 );
if( s616->s517() == s500 )
return;
}
if( s284.size() > s661.size() )
throw new s18( L"too many pars" );
for( size_t n = 0; n < s284.size(); ++n ) {
s507 par = s284[n];
if( par->s517() == s496 ) {
if( par.s17<s390*>()->s400().s14() )
par.s17<s390*>()->s523( this );
}
else
s284[n] = s921( par );
}
for( size_t n = 0; n < s284.size(); ++n ) {
s659.s568( s662[n], s284[n].s17<s505*>(), s504::s154 );
s284[n]->setWh( s8::s945 );
s661[n] = s284[n];
}
for( size_t n = 0; n < s612.size(); ++n ) {
if( s612[n]->s517() == s499 ) {
s512 cs = new s588( *s612[n].s17<s588*>() );
s612[n] = s628( cs, s310, s616, this, s616->s309() );
}
else if( s612[n]->s517() == s496 )
s612[n].s17<s390*>()->s523( s615 );
else if( s612[n]->s517() != s497 )
s612[n]->s523( s615 );
else // lambda - ?
throw new s18( L"unhandled expression" );
}
for( auto it : s612 ) {
if( it->s517() == s497 )
it.s17<Transd*>()->s523( s350, true );
}
if( !s516 && s612.size() ) {
s516 = s612.back()->s370();
s614 = s310->TR().s545( s370(), s616, s350 );
s614->setWh( s8::s945 );
s611.insert( s611.begin(), s614 );
}
if( s284.size() ) {
s608 = (s506**)&s284[0];
nlocs = s284.size();
s607 = NULL;// &s611[0];
s521 = s611.size();
}
else {
s608 = NULL;
s607 = NULL;
nlocs = s521 = 0;
}
s1080.resize( s611.size() );
}
void s619::s624( const vector<s507>& l )
{
s284.clear();
s284.assign( l.begin(), l.end() );
}
void s619::s625( const wstring& s350 )
{
if( s602 != s593 && s602 != s592 && s284.size() > s661.size() )
throw new s18( L"too many pars" );
for( size_t n = 0; n < s284.size(); ++n ) {
s281* par = s284[n];
if( par->s517() == s498 ) {
s1039 ast_ = new s273( s284[n].s17<s349*>()->Str() );
s505* par_ = s310->TR().s545( *ast_, s616,
s284[n].s17<s349*>()->s352() );
s284[n] = par_;
}
else if( par->s517() == s499 ) {
s512 cs = new s588( *(s588*)par );
par = s628( cs, s310, s616, this, s308() );
((s619*)par)->s523( s350, false );
s284[n] = par;
}
if( s284[n]->s517() == s503 ) {
s611.push_back( s284[n]->s519() );
}
else if( s284[n]->s517() != s496 ) {
if( ( s602 != s593 && s602 != s592 ) || s288 == s242 ) {
s661[n] = s284[n]->s519();
s661[n]->setWh( s8::s945 );
s659.s568( s662[n], s661[n].s17<s505*>(), s504::s154 );
}
s611.push_back( s284[n]->s519() );
}
else {
if( s602 != s593 && s602 != s592 ) {
s661[n] = s284[n].s17<s505*>();
s659.s568( s662[n], s284[n].s17<s390*>()->s396(), s504::s154 );
}
if( s284[n].s17<s390*>()->s400().s14() ) {
s284[n].s17<s390*>()->s523( this );
}
s611.push_back( NULL );
}
if( s288 != s242 && n < s661.size() && n < s610.size() && !s661[n].s17<s505*>()->s525( (s505*)s610[n] ) )
throw new s18( L"wrong argument's type" );
}
for( size_t n = 0; n < s661.size(); ++n ) {
if( s661[n]->s648() == s8::s946 )
throw new s18( L"parameter is not provided" );
}
}
void s619::s873( s904& s160 ) const
{
for( size_t n = 0; n < s610.size(); ++n )
s160.push_back( make_pair( s662[n], s610[n] ) );
}
s508 s619::s520( s505** s727, size_t s736 )
{
s508 s721;
size_t shift = 0;
if( s602 == s595 || s602 == s593 || s602 == s592 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s608 + n ) ) {
s493 pc = ( ( s506* )*( s608 + n ) )->s517();
if( pc == s496 )
*( s607 + n + shift ) =
(s505*)( ( s390* )*( s608 + n ) )->s396();
else if( pc == s497 ) {
s1080[n+shift] = (s505*)( ( s619* )*( s608 + n ) )->s520( s727, s736 );
*( s607 + n + shift ) = s1080[n + shift];
}
else if( pc == s495 )
*( s607 + n + shift ) = (s505*)*( s608 + n );
}
}
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s607, s521 );
if( s721->s648() < 0 )
break;
}
return s721;
}
s508 s914::s520( s505** s727, size_t s736 )
{
s505* s721 = NULL;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s608 + n ) ) {
s493 pc = ( ( s506* )*( s608 + n ) )->s517();
if( pc == s496 )
*( s607 + n + shift ) =
(s505*)( ( s390* )*( s608 + n ) )->s396();
else if( pc == s497 ) {
s1080[n+shift] = 	(s505*)( ( s619* )*( s608 + n ) )->s520( s727, s736 );
*( s607 + n + shift ) = s1080[n + shift];
}
}
}
s589( s607, s521 );
s721 = s611[0];
return s721;
}
s508 s915::s520( s505** s727, size_t s736 )
{
s505* s721 = NULL;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s608 + n ) ) {
s493 pc = ( ( s506* )*( s608 + n ) )->s517();
if( pc == s496 ) ( void )0;
else if( pc == s497 )
(s505*)( ( s619* )*( s608 + n ) )->s520( s727, s736 );
}
}
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s607, s521 );
if( s721->s648() < 0 )
break;
}
return s721;
}
bool
s619::s583( const wstring& s712, s390* ref,	const wstring& s350 ) const
{
bool s721 = false;
wstring s288 = s712;
size_t pl = s288.find( L"." );
if( pl == string::npos ) { //a
if( !s659.s163( s288 ) /*!ob*/ ) {
if( s615.s15() && (s616.s14() || s615->s616 == s616 ) )
s721 = s615->s583( s288, ref, s350 );
if( !s721 ) {
if( s616.s15() )
s721 = s616->s583( s288, ref, s350 );
if( !s721 )
s721 = s310->s583( s288, ref, s350 );
}
}
else {
size_t off = s672( s288 );
ref->s398( off, ((s506*)&(*s661[off]))->s519()->s527() );
ref->s401( (s505*)this /*(s506**)&s284[off]*/ );
s721 = true;
}
}
else {// a.y
s288 = s712.substr( pl + 1 );
wstring s722 = s712.substr( 0, pl );
s281* ob = s659.get( s722, false );
if( !ob ) {
s721 = s616->s583( s712, ref, s350 );
if( !s721 && s615.s15() )
s721 = s615->s583( s288, ref, s350 );
}
else {
size_t off = s672( s722 );
ref->s398( off, NULL );
s721 = ob->s527()->s583( s288, ref, s350 );
ref->s401( (s505*)this );
}
}
return s721;
}
s281* s619::s626( size_t off )
{
return s661[off];
}
s281* s619::s353() const
{
return new s619( *this );
}
void s619::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"Transductor : " <<  s288 << endl;
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"Call type : " << ct[s602] << endl;
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"Local map : " << endl;
s659.s314( pd, s205 + s438 );
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"fpars : " << endl;
for( size_t n = 0; n < s610.size(); ++n )
s610[n]->s314( pd, s205 + s438 * 2 );
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"namvec : " << endl;
for( size_t n = 0; n < s662.size(); ++n )
buf << s4::fill_n_ch( L' ', s205 + s438 * 2 ) << s662[n] << endl;
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"memvec : " << endl;
for( size_t n = 0; n < s661.size(); ++n )
s661[n]->s314( pd, s205 + s438 * 2 );
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"exprs : " << endl;
for( size_t n = 0; n < s612.size(); ++n )
s612[n]->s314( pd, s205 + s438 * 2 );
buf << s4::fill_n_ch( L' ', s205 + s438 ) << L"Members : " << endl;
s659.s314( pd, s205 + s438 );
}
s378::s378( s272* s310, const std::wstring& s, const s273* ast_ )
: s354( s310, ast_ ), s367( s )
{
if( s846.s14() ) {
s516 = 0;
wh = s8::s946;
}
else
s516 = s846->s370();
}
s378::s378( s272* s310, s282* s620, const std::vector<s281*>& l, const s273* ast_ )
: s354( s310, ast_ )
{
for( auto s : l ) {
s507 p = s281::s1125( s310, s, s620, NULL, s620->s308() );
s367 += p->to_wstring();
}
if( l.empty() )
wh = s8::s946;
s516 = s846->s370();
}
s378::s378( const s378& r, const s273* ast_ )
: s354( r.s310, ast_ ), s367( r.s367 )
{
wh = r.wh;
s516 = s846->s370();
}
s378::s378( s272* s310, const std::wstring& s, size_t& pos, const s273* ast_ )
:s354( s310, ast_ )
{
s367 = s;
pos = string::npos;
s516 = s846->s370();
}
s505* s378::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s378( s310, s616, l );
}
void s378::s368()
{
s366[L"set"] = new s355( L"set", &s378::s406, s784->s370() );
s366[L"sum"] = new s355( L"sum", &s378::s407, s846->s370() );
s366[L"sub"] = new s355( L"sub", &s378::s849, s846->s370() );
s366[L"tolower"] = new s355( L"tolower", &s378::s980, s846->s370() );
s366[L"toupper"] = new s355( L"toupper", &s378::s981, s846->s370() );
s366[L"find"] = new s355( L"find", &s378::s833, s828->s370() );
s366[L"rfind"] = new s355( L"rfind", &s378::s854, s828->s370() );
s366[L"eq"] = new s355( L"eq", &s378::s417, s806->s370() );
s366[L"less"] = new s355( L"less", &s378::s418, s806->s370() );
s366[L"greater"] = new s355( L"greater", &s378::s419, s806->s370() );
s366[L"leq"] = new s355( L"leq", &s378::s420, s806->s370() );
s366[L"geq"] = new s355( L"geq", &s378::s421, s806->s370() );
s366[L"neq"] = new s355( L"neq", &s378::s422, s806->s370() );
s366[L"read"] = new s355( L"read", &s378::s428, s828->s370() );
s366[L"match"] = new s355( L"match", &s378::s1146, s806->s370() );
}
void s378::s523( s282* s965 )
{
}
wstring s739( wchar_t c )
{
wstring s721;
if( c == L'n' )
s721 = L"\n";
else if( c == L'r' )
s721 = L"\r";
else if( c == L't' )
s721 = L"    ";
else if( c == L'\\' )
s721 = L"\\";
else {
wstring _s( L"Unknown escape sequence: \\" );
_s.push_back( c );
throw new s18( _s );
}
return s721;
}
s505* s378::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s_ = s740.s301();
wstring s367, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s55( s_.substr( 7, s_.size() - 8 ), s51 );
if( s.empty() )
return new s378( s310, s616, std::vector<s281*>() );
}
else
s = s4::s55( s_, s51 );
if( s.size() ) {
pl = s91.find( s[0] );
if( pl != string::npos && s.back() == s91[pl] )
s = s4::s55( s, wstring( 1, s91[pl] ) );
}
if( s.size() == 2 && s[0] == L'\\' )
s367 = s739( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s367 = s;
while( pl != string::npos ) {
if( pl == s367.size() - 1 )
break;
if( s367[pl + 1] != L'\\' ) {
wstring code = s739( s367[pl + 1] );
s367 = s367.replace( pl, 2, code );
pl = s367.find( L"\\", pl + 1 );
}
else {
s367.erase( pl, 1 );
pl = s367.find( L"\\", pl + 1 );
}
}
}
if( s367.empty() )
s367 = s;
return new s378( s310, s367 );
}
s281* s378::s353() const
{
return new s378( *this );
}
void s378::s375( s507 p ) const
{
if( p->s370() == s846->s370() )
*( p.s17<s378*>()->s376() ) = s367;
else if( p->s370() == s828->s370() )
*( p.s17<s364*>()->s376() ) = std::stoi( s367 );
else if( p->s370() == s862->s370() )
*( p.s17<s377*>()->s376() ) = std::stof( s367 );
else
throw new s18( L"No conversion to type " + s372() );
}
s378::operator int() const
{
long s721;
if( !s4::s65( s367.c_str(), &s721 ) )
throw new s18( L"cannot cast String " + s367 + L" to Int" );
if( s721 > (std::numeric_limits<int>::max)() )
throw new s18( L"cannot cast String to Int: the value is too big: " + s367 );
return (int) s721;
}
s378::operator double() const 
{ 
double s721;
if( !s4::s66( s367.c_str(), &s721 ) )
throw new s18( L"cannot cast String '" + s367 + L"' to Double" );
return s721;
}
wstring s378::to_wstring() const 
{
if( 0 && s367.front() == '\"' && 
s367.back() == '\"' )
return s367.substr( 1, s367.size() - 2 );
return s367; 
}
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
#undef s737
#define s737 ((s378*)(s506*)*s284)
#define s738 ((s379*)(s506*)*s284)
inline void s378::s406( s505** s284, size_t s521 )
{
( (s378*)DR )->s367 = ( (s378*)PARN( 2 ))->s367;
}
inline void s378::s407( s505** s284, size_t s521 )
{
s737->s367 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s521; ++n )
s737->s367 += PARN( n )->to_wstring();
}
inline void s378::s980( s505** s284, size_t s521 )
{
s737->s367 = ((s378*)DR)->s367;
std::for_each( s737->s367.begin(), s737->s367.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );
}
inline void s378::s981( s505** s284, size_t s521 )
{
s737->s367 = ((s378*)DR)->s367;
std::for_each( s737->s367.begin(), s737->s367.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );
}
inline void s378::s849( s505** s284, size_t s521 )
{
wstring s735 = L"Invalid substring specification: ";
if( s521 < 2 )
throw new s18( s735 + L"too few parameters." );
const wstring& dr = ((s378*)DR)->s367;
int start = 0, end = (int) dr.size() - 1;
if( s521 > 2 ) {
start = (int)*s284[2];
if( s521 > 3 )
end = (int)*s284[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s18( s735 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s18( s735 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s18( s735 + L"the end position is less than 0." );
if( start > end )
throw new s18( s735 + L"the start position is greater than string's length." );
}
s737->s367 = dr.substr( start, end - start );
}
inline void s378::s833( s505** s284, size_t s521 )
{
wstring s735 = L"Invalid 'find' syntax: ";
if( s521 < 3 )
throw new s18( s735 + L"too few parameters." );
const wstring& dr = ( (s378*)DR )->s367;
const wstring& str = ( (s378*)s284[2] )->s367;
int start = 0; 
if( s521 > 3 ) {
start = (int)*s284[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s18( s735 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s18( s735 + L"the start position is greater than string's length." );
}
*((s364*)s284[0])->s376() = (int)dr.find( str, start );
}
inline void s378::s854( s505** s284, size_t s521 )
{
wstring s735 = L"Invalid 'rfind' syntax: ";
if( s521 < 3 )
throw new s18( s735 + L"too few parameters." );
const wstring& dr = ( (s378*)DR )->s367;
const wstring& str = ( (s378*)s284[2] )->s367;
int start = (std::numeric_limits<int>::max)();
if( s521 > 3 ) {
start = (int)*s284[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s18( s735 + L"the start position is less than 0." );
}
*( (s364*)s284[0] )->s376() = (int)dr.rfind( str, start );
}
inline void s378::s417( s505** s284, size_t s521 )
{
if( DR->to_wstring() == PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s418( s505** s284, size_t s521 )
{
if( DR->to_wstring() < PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s419( s505** s284, size_t s521 )
{
if( DR->to_wstring() > PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s420( s505** s284, size_t s521 )
{
if( DR->to_wstring() <= PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s421( s505** s284, size_t s521 )
{
if( DR->to_wstring() >= PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s422( s505** s284, size_t s521 )
{
if( DR->to_wstring() != PARN( 2 )->to_wstring() )
*s738->s376() = 1;
else
*s738->s376() = 0;
}
inline void s378::s428( s505** s284, size_t s521 )
{
wstring s98 = L"";//( (s378*)s284[2] )->to_wstring();
wstring s = s6::s106( s98, false );
*( (s364*)s737 )->s376() = (int)s.size();
((s378*)DR)->s367 = s;
}
inline void s378::s1146( s505** s284, size_t s521 )
{
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1152;
wstring s = DR->to_wstring();
bool s160 = regex_match( s, s1152, rg );
*s738->s376() = s160;
}
void s378::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : " << s367 << endl;
}
size_t s378::s334() const
{
return hash<wstring>{}(s367);
}
bool s378::operator==( const s505* p ) const
{
return ( (s378*)p )->s367 == s367;
}
bool s378::operator<( const s505* p ) const
{
return s367 < ( (s378*)p )->s367;
}
vector<wstring> s1049( { L"from", L"to", L"first", L"last", L"before", L"after" } );
s877::s877( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s808, s740 )
{
TDException s1064( s8::s1230, s1022, s740 );
if( l.empty() )
throw s1064.s1102( L"too few arguments" );
s284.assign( l.begin(), l.end() );
s516 = s846->s370();
for( s281* p : s284 ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1049 );
}		
}
s877::s877( s272* s310 )
: s619( s310, NULL, NULL, s592, s808, NULL )
{
s516 = s846->s370();
}
void s877::s523( const wstring& s350, bool proc )
{
s619::s523( s350, proc );
wstring s735 = L"Invalid parameters of 'substr' function: ";
if( s284[0]->s370() != s846->s370() )
throw new s18( s735 + L"The first parameter is not of String type." );
str = s284[0].s17<s378*>();
size_t s766 = 1;
int s830 = 0;
s787 s816 = s759;
s760 =	nTo = 1;
s848 = s785 = 0;
while( s766 < s284.size() ) {
s507 par_ = s284[s766];
s493 pc = par_->s517();
if(	pc == s496 || pc == s1177 || pc == s495 || pc == s497 ) {
s507 par;
s511 rf;
if( pc == s496 ) {
rf = par_.s17<s390*>();
par = (s281*)rf->s397();
}
else if( pc == s1177 ) {
rf = par_.s17<s390*>();
par = par_;
}
else
par = par_;
if( par->s370() == s832->s370() ) {
if( rf->s647() == L"from" ) {
if( s830 != 0 )
throw new s18( s735 + L"'from' is misplaced." );
s830 = 1;
s816 = s814;
}
else if( rf->s647() == L"to" ) {
if( s830 != 0 )
throw new s18( s735 + L"'to' is misplaced." );
s830 = 1;
s816 = s876;
}
else if( rf->s647() == L"before" ) {
if( s816 != s759 && s830 >= 2 )
throw new s18( s735 + L"'before' is misplaced." );
if( s816 == s876 )
s785 = -1;
else
s848 = -1;
s830 = 2;
}
else if( rf->s647() == L"after" ) {
if( s816 != s759 && s830 >= 2 )
throw new s18( s735 + L"'after' is misplaced." );
if( s816 == s876 )
s785 = 1;
else
s848 = 1;
s830 = 2;
}
else if( rf->s647() == L"first" ) {
if( s816 != s759 && s830 >= 3 )
throw new s18( s735 + L"'first' is misplaced." );
s830 = 3;
}
else if( rf->s647() == L"last" ) {
if( s816 != s759 && s830 >= 3 )
throw new s18( s735 + L"'last' is misplaced." );
if( s816 == s876 )
nTo = string::npos;
else
s760 = string::npos;
s830 = 3;
}
else
throw new s18( s735 + L"unknown parameter '" + rf->s647() + L"'." );
}
else if( par->s370() == s846->s370() ) {
if( s816 == s814 )
s864 = par;
else if( s816 == s876 )
s856 = par;
else {
if( s864.s14() && s813.s14() )
s864 = par;
else if( s856.s14() && s763.s14() )
s856 = par;
else
throw new s18( s735 + L"unknown parameter '" + rf->s647() + L"'." );
}
s830 = 0; s816 = (( s816 == s814 || s816 == s759 ) ? s876 : s814 );
}
else if( par->s370() == s828->s370() ) {
if( s816 == s814 )
s813 = par;
else if( s816 == s876 )
s763 = par;
else {
if( s864.s14() && s813.s14() )
s813 = par;
else if( s856.s14() && s763.s14() )
s763 = par;
else
throw new s18( s735 + L"unknown parameter '" + rf->s647() + L"'." );
}
s830 = 0; s816 = ( ( s816 == s814 || s816 == s759 ) ? s876 : s814 );
}
}
s766++;
}
}
s508 s877::s520( s505** s727, size_t s736 )
{
size_t s200 = 0, s719 = string::npos;
wstring s810, s765;
wstring dom = str->s520( 0, 0 )->to_wstring();
if( s813.s15() ) {
if( s813->s517() == s497 )
s200 = (size_t)(int)*s813->s520( 0, 0 );
else
s200 = (size_t)(int)*s813.s17<s364*>();
}
else if( s864.s15() ) {
s810 = s864->to_wstring();
if( s760 == 1 )
s200 = dom.find( s810 );
else if( s760 == string::npos )
s200 = dom.rfind( s810 );
else
throw new s18( L"substr: nFrom =" + std::to_wstring( s760 ) );
s200 += s848;
}
if( s763.s15() ) {
if( s763->s517() == s497 )
s719 = (size_t)(int)*s763->s520( 0, 0 );
else
s719 = (size_t)(int)*s763.s17<s364*>();
}
else if( s856.s15() ){
s765 = s856->to_wstring();
if( nTo == 1 )
s719 = dom.find( s765 );
else if( nTo == string::npos )
s719 = dom.rfind( s765 );
else
throw new s18( L"substr: nTo =" + std::to_wstring( s760 ) );
s719 += s785;
}
if( s200 < 0 || s200 >= s719 || s200 >= dom.size() )
return s508();
wstring s160 = dom.substr( s200, s719 - s200 );
s614 = new s378( s310, s160 );
return s614;
}
s281* s877::s353()const
{
return new s877( *this );
}
s505* s340::sort( bool, s913* )
{ 
throw new s18( L"not implemented", (uint32_t) s18::s19::s960 );
}
s1044::s1044( s272* s310, const std::vector<s281*>& l )
: s404( s310, L"" ), s1159( true )
{
wstring s1100 = L"wrong sequence generator syntax";
if( l.empty() || l.size() > 3 )
throw new s18( s1100 + L": no arguments" );
if( l.size() == 1 ) {
end = l[0];		
}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];
}
}
void s1044::s523( s282* s965 )
{
wstring s1100 = L"wrong sequence generator syntax";
end = s281::s1125( s310, end, s965, (s619*)s965, s965->s308() );
if( start.s15() )
start = s281::s1125( s310, start, s965, (s619*)s965, s965->s308() );
else {
start = s310->TR().s545( end->s370(), s965, s965->s308() );
start->s523( s965 );
}
if( incr.s15() ) 
incr = s281::s1125( s310, incr, s965, (s619*)s965, s965->s308() );
else {
if( start->s370() == s828->s370() )
incr = new s364( s310, 1 );
else
throw new s18( s1100 + L": increment value is missing" );
}
s1091 = start->s353();
std::vector<s281*> pl = { s1091, incr };
s588 cs( s310, L"sumeq", pl, NULL );
s1172 = s619::s628( &cs, s310, s965, (s619*)s965, s965->s308() );
s1172->s523( s965->s308(), false );
std::vector<s281*> pl1 = { s1091, start };
s588 cs1( s310, L"set", pl1, NULL );
set = s619::s628( &cs1, s310, s965, (s619*)s965, s965->s308() );
set->s523( s965->s308(), false );
std::vector<s281*> pl2 = { s1091, end };
s588 cs2( s310, L"eq", pl2, NULL );
eq = s619::s628( &cs2, s310, s965, (s619*)s965, s965->s308() );
eq->s523( s965->s308(), false );
}
Iterator* s1044::s325( s505* start, s505* stop )
{
set->s520( 0, 0 );
s1159 = true;
return this;
}
s281* s1044::s326()
{
if( s1159 )
s1159 = false;
else
s1172->s520( 0, 0 );
if( (bool)*eq->s520( 0, 0 ) )
return NULL;
return s1091;
}
s1060::s1060( s1031 start, s1031 stop, s327* v_ )
: v( v_ ), s329( start ), s1205( stop ), s1088( (size_t)-1 )
{
if( v.s15() ) {
if( s329 == v->s332().begin() && s1205 == v->s332().end() )
s1088 = 0;
}
}
s281* s1060::s326()
{
s281* s721 = NULL;
if( s1088 != (size_t)-1 ) {
if( s1088 < v->s332().size() ) {
s721 = v->s332().at(s1088++);
}
}
else {
if( s329 != s1205 ) {
s721 = *s329;
++s329;
}
}
return s721;
}
s281* s1060::s1057()
{
return *s329;
}
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
s327::s327( s272* s310, s282* s616, const wstring& s80, const s273* ast_,
const wstring& s75 )
: s340( s310, ast_ ), s328( 0 )
{
if( s80.size() ) {
if( s80[0] == L'[' ) {
vector<s1::s10<s7::s148>> s160;
size_t pos = 0;
const s1037* s1163 = NULL;
if( ast_ && ast_->Nqj() )
s1163 = ast_->Nqj()->s1110();
s7::s186( s1163, s80, pos, s160, true, s75 );
for( size_t n = 0; n < s160.size(); ++n ) {
s273 s234( L"", *s160[n] );
s367.push_back( s281::s528( s234, s310, s616, s616->s308() ) );
}
}
else if( s80[0] == L'(' ) {
wstring sv = s4::s55( s80.substr( 1, s80.size() - 2 ), L" " );
wsmatch s1188;
wregex rg( LR"regex(^\s*([_[:alpha:]]\w*)\(\)\s*(\d*)\s*$)regex" );
if( sv.size() && regex_match( sv, s1188, rg ) ) {
wstring tp = s1188[1].str(), s170 = L"0";
if( s1188[2].str().size() )
s170 = s1188[2].str();
sv = L"]" + tp + L" " + s170;
s367.push_back( 0 );
s367.push_back( new s378( s310, sv ) );
}
else if ( s80.find( L"typedTable" ) != string::npos ) {
s1065( sv, s616, ast_ );
}
}
}
s516 = (s768.s14() ? 0 : s768->s370());
}
s327::s327( const s327& right, const s273* ast_ )
: s340( right.s310, ast_ ), s328( right.s328 )
{
s367 = right.s367;
s516 = right.s516;
}
s327::s327( s272* s310, const std::vector<s281*>& l, const s273* ast_ )
: s340( s310, ast_ ), s328( 0 )
{
s516 = s768.s14() ? 0 : s768->s370();
if( l.size() ){
s328 = l[0]->s370();
for( size_t n = 0; n < l.size(); ++n )
s367.push_back( l[n] );
}
}	
s327::~s327()
{
s367.clear();
}
s505* s327::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
wstring sv;
wstring s365 = s372();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s; //s4::s55( s, L"[]" );
else if( s.find( s365 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s55( s.substr( s365.size() ), s51 );
if( sv[0] != L'(' )
throw new s18( L"wrong vector constructor syntax" );
/*		sv = s4::s55( sv.substr( 1, sv.size() - 2 ), L" " );
wsmatch s1188;
wregex rg( LR"regex(^\s*([_[:alpha:]]\w*)\(\)\s*(\d*)$)regex" );
if( sv.size() && regex_match( sv, s1188, rg ) ) {
wstring tp = s1188[1].str(), s170 = L"0";
if( s1188[2].str().size() )
s170 = s1188[2].str();
sv = L"]" + tp + L" " + s170;
}*/
}
else
return 0;
return new s327( s310, s616, sv, &s740 );
}
void s327::s523( s282* s965 )
{
wstring s80 = L"";
TDException s1064( s8::s1014, s1023, s631() );
if( s367.size() == 2 && s367[0].s14() )
s80 = s367[1]->to_wstring();
if( s80[0] == L']' ) {
s367.clear();
wstring snum = s80.substr( s80.rfind( L" " ) );
s1039 ast_ = new s273( s80.substr( 1, s80.size() - snum.size() - 1 ));
size_t s170 = std::stoi( snum );
for( size_t n = 0; n < s170; ++n )
s367.push_back( s310->TR().s545( *(s273*)ast_, s965, s965->s903() ));
if( s170 == 0 )
s328 = s310->TR().get( ast_->s301() )->s370();
else
s328 = s367[0]->s370();
}
else {
for( size_t n = 0; n < s367.size(); ++n ) {
if( s367[n]->s517() == s496 ) {
s367[n]->s523( s965 );
s367[n] = s367[n].s17<s390*>()->s396();
}
s507 s1208 = s281::s1125( s310, s367[n], s965, NULL, s965->s308() );
s367[n] = s1208;
if( !s328 )
s328 = s367[0]->s370();
else if( s328 != s367[n]->s370() )
throw s1064.s1102( L"elements have different types" );
}
}
if( !s328 )
throw s1064.s1102( L"vector element's type is missing" );
s516 = s310->TR().s1158( s872::Cont( { s768->s370(), s328 }) );
s366[L"get"]->s356 = s328;
s522 = s965->s903();
}
void s327::s1065( const wstring& s80, s282* s616, const s273* ast_ )
{
TDException s1064( s8::s1015, s1023, ast_ );
bool typed;
wstring s1106 = L",";
wstring s1145 = L"\n";
wstring str = L"";
vector<wstring> ops;
s4::s60( s80, L" ", ops );
if( ops.size() < 2 )
throw s1064.s1102( L"too few arguments" );
if( ops[0] == L"typedTable" )
typed = true;
else if( ops[0] == L"untypedTable" )
typed = false;
else
throw s1064.s1102( L"unrecognized first parameter" );
if( ops.size() > 2 ) {
s507 s1169 = s281::s1124( ops[2], ast_, s310, s616 );
s1106 = s1169->to_wstring();
}
if( ops.size() > 3 ) {
s507 s1171 = s281::s1124( ops[3], ast_, s310, s616 );
s1145 = s1171->to_wstring();
}
s507 s1176 = s281::s1124( ops[1], ast_, s310, s616 );
str = s1176->to_wstring();
vector<wstring> s860;
s4::s60( s4::s55( str, s51 ), s1145, s860 );
for( wstring row : s860 ) {
if( typed ) {
s367.push_back( new s327( s310, s310, row, NULL, s1106 ) );
}
else {
s367.push_back( new s797( s310, s310, row, NULL, s1106 ) );
}
}
}
void s327::s368()
{
s366[L"set"] = new s355( L"set", &s327::s406, s784->s370() );
s366[L"get"] = new s355( L"get", &s327::s341, 0 );
s366[L"add"] = new s355( L"add", &s327::s342, s784->s370() );
s366[L"size"] = new s355( L"size", &s327::s343, s828->s370() );
s366[L"resize"] = new s355( L"resize", &s327::s344, s784->s370() );
s366[L"clear"] = new s355( L"clear", &s327::s345, s784->s370() );
s366[L"eq"] = new s355( L"eq", &s327::s417, s828->s370() );
s366[L"through"] = new s355( L"through", &s327::s346, s784->s370() );
s310->TR().s1067( s516, L"is", L"indexed" );
s310->TR().s1067( s516, L"is", L"sortable" );
}
s505* s327::s374( s282* s616, const vector<s281*>& l ) const
{
s327* s721 = new s327( s310, s616, L"" );
s721->s516 = s516;
if( l.size() ) {
s721->s328 = (s1175)*((s364*)l[0])->s376();//new s872( v );
}
else
s721->s328 = s328;
return s721;
}
s505* s327::s374( s282* s616, const std::vector<s1175>& vt ) const
{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s327* s721 = new s327( s310, NULL, L"" );
s872::Cont s1094;
s513::s1112( vt, idx, s1094 );
s872 s1093( s1094[0] );
s721->s328 = s310->TR().s1115( s1093 );
if( s1094.size() == 2 )
s721->s367.push_back( s310->TR().s1111( s1094[0] )->s374( s616 ) );
else
s721->s367.push_back( s310->TR().s1111( s1094[0] )->s374( s616, s1094 ) );
return s721;
}
inline bool
s327::s525( const s505* s526 ) const
{
return ( ( (s327*)s526 )->s328 == s328 );
}
s281* s327::s353() const
{
return new s327( *this );
}
void s327::s375( s507 p ) const
{
p = new s327( *this );
}
#undef s737
#define s737 ((s327*)(s506*)*s284)
inline void s327::s406( s505** s284, size_t s521 )
{
s284[3]->s375( ( (s327*)DR )->s367[(int)*s284[2]] );
}
inline void s327::s341( s505** s284, size_t s521 )
{
*s284 = (s505*)(s281*)( (s327*)DR )->s367[(int)*s284[2]];
}
inline void s327::s342( s505** s284, size_t s521 )
{
if( ! ( ( (s327*)DR )->s331() == s284[2]->s370() ) )
throw new s18( L"unmatched element type" );
( (s327*)DR )->s367.push_back( s284[2]->s353() );
}
inline void s327::s343( s505** s284, size_t s521 )
{
*( (s364*)*s284 )->s376() = (int)( (s327*)DR )->s367.size();
}
inline void s327::s344( s505** s284, size_t s521 )
{
int size = (int)*s284[2];
int oldsize = (int)( (s327*)DR )->s367.size();
( (s327*)DR )->s367.resize( size );
for( int i = oldsize; i < size; ++i )
( (s327*)DR )->s367[i] = ( (s327*)DR )->s310->TR().s545(
( (s327*)DR )->s328, ( (s327*)DR )->s310, ( (s327*)DR )->s522 );
}
inline void s327::s345( s505** s284, size_t s521 )
{
( (s327*)DR )->s367.clear();
}
inline void s327::s417( s505** s284, size_t s521 )
{
size_t size = ( (s327*)DR )->s367.size();
s327* right = (s327*)s284[2];
if( right->s367.size() != size ) {
*( (s364*)*s284 )->s376() = 0;
return;
}
for( size_t n = 0; n < size; ++n ) {
if( right->s367[n] != ( (s327*)DR )->s367[n] ) {
*( (s364*)*s284 )->s376() = 0;
return;
}
}
*( (s364*)*s284 )->s376() = 1;
}
inline void s327::s346( s505** s284, size_t s521 )
{
*( (s364*)*s284 )->s376() = (int)( (s327*)DR )->s367.size();
}
struct s924
{
vector<s507>& s367;
s924( vector<s507>& s734 ) : s367( s734 ) {}
bool operator()( const s507 l, const s507 r ) const
{
return l.s17<s505*>()->operator<( r.s17<s505*>() );
}
};
s505* s327::sort( bool s972, s913* cmp )
{
s924 s923( s367 );
if( s972 ) {
if( cmp )
std::sort( s367.rbegin(), s367.rend(), *cmp );
else
std::sort( s367.rbegin(), s367.rend(), s923 );
}
else {
if( cmp )
std::sort( s367.begin(), s367.end(), *cmp );
else
std::sort( s367.begin(), s367.end(), s923 );
}
return this;
}
wstring s327::to_wstring() const
{
wstring s721 = L"[";
for( size_t n = 0; n < s367.size(); ++n )
s721 += s367[n]->to_wstring() + ( n == s367.size() - 1 ? L"" : L", " );
s721 += L"]";
return s721;
}
void s327::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"Vector : " << endl;
for( size_t n = 0; n < s367.size(); ++n )
s367[n]->s314( pd, s205 + s438 );
}
size_t s327::s334() const
{
size_t s721 = 0;
for( size_t n = 0; n < s367.size(); ++n )
s721 = s721 * ( (s505*)&(*s367[n]) )->s334() << 1;
return s721;
}
bool s327::operator==( const s505* p ) const
{
if( ( (s327*)p )->s367.size() != s367.size() )
return false;
for( size_t n = 0; n < s367.size(); ++n )
if( !( ( s281*)&(*s367[n]) == (s281*)( (s327*)p )->s367[n] ) )
return false;
return true;
}
bool s327::operator<( const s505* p ) const
{
return false;
}
Iterator* s327::s325( s505* s1202, s505* s1204 )
{
s1059::iterator start = s367.begin() + (s1202->s370() == s784->s370() ?
0 : (int)*s1202);
s1059::iterator stop = s367.end() - (s1204->s370() == s784->s370() ?
0 : (int)*s1204);
return new s1060( start, stop, this );
}
/*
s508 s327::s326()
{
if( s329 == s367.end() ) {
return NULL;
}
s508 s721 = (*s329).s17<s505*>();
s329++;
return s721;
}
*/
s1056::s1056( s1031 s1202, s1031 s1204 )
: s329( s1202 ), s1205( s1204 )
{
}
s281* s1056::s326()
{
s281* s721 = NULL;
if( s329 == s1205 )
return s721;
s721 = *s329;
++s329;
return s721;
}
s281* s1056::s1057()
{
return *s329;
}
s797::s797( s272* s310, s282* s616, const wstring& s80, 
const s273* ast_, const wstring& s75 )
: s340( s310, ast_ )
{
if( s80.size() ) {
vector<s1::s10<s7::s148>> s160;
const s1037* s1163 = NULL;
if( ast_ )
s1163 = ast_->Nqj()->s1110();
if( s80[0] == L'[' ) {
size_t pos = 0;
s7::s186( s1163, s80, pos, s160, true );
}
else
s7::s186( s1163, s80, s160, true );
for( size_t n = 0; n < s160.size(); ++n ) {
s273 s234( L"", *s160[n] );
s367.push_back( s281::s528( s234, s310, s616, s616->s308() ) );
}
}
s516 = s791.s14() ? 0 : s791->s370();
}
s797::s797( s272* s310, const vector<s281*>& l, 
const s273* ast_ )
: s340( s310, ast_ )
{
for( auto s1174 : l )
s367.push_back( s1174 );
s516 = s791->s370();
}
s797::s797( const s797& right, const s273* ast_ )
: s340( right.s310, ast_ )
{
s367 = right.s367;
s516 = right.s516;
}
s797::~s797()
{
s367.clear();
s522.clear();
}
s505* s797::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
wstring sv;
wstring s365 = s372();
if( s.find( L"UVector[" )== 0 )
sv = s.substr(7);
else if( s.find( s365 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s55( s.substr( s365.size() ), s51 );
if( sv[0] != L'(' )
throw new s18( L"wrong vector constructor syntax" );
sv = s4::s55( sv.substr( 1, sv.size() - 2 ), L" " );
}
else
return 0;
return new s797( s310, s616, sv );
}
void s797::s523( s282* s965 )
{
for( size_t n = 0; n < s367.size(); ++n ) {
if( s367[n]->s517() == s496 ) {
s367[n]->s523( s965 );
s367[n] = s367[n].s17<s390*>()->s396();
}
s507 s1208 = s281::s1125( s310, s367[n], s965, NULL, s965->s308() );
s367[n] = s1208;
}
s516 = s791->s370();
s366[L"get"]->s356 = s832->s370();// s328;
s366[L"fst"]->s356 = s367.size() ? s367[0]->s370() : s832->s370();
s366[L"snd"]->s356 = (s367.size() > 1) ? s367[1]->s370() : s832->s370();
s522 = s965->s903();
}
void s797::s368()
{
s366[L"set"] = new s355( L"set", &s797::s406, s784->s370() );
s366[L"get"] = new s355( L"get", &s797::s341, 0 );
s366[L"fst"] = new s355( L"fst", &s797::s1104, 0 );
s366[L"snd"] = new s355( L"snd", &s797::s1189, 0 );
s366[L"add"] = new s355( L"add", &s797::s342, s784->s370() );
s366[L"size"] = new s355( L"size", &s797::s343, s828->s370() );
s366[L"resize"] = new s355( L"resize", &s797::s344, s784->s370() );
s366[L"clear"] = new s355( L"clear", &s797::s345, s784->s370() );
s366[L"eq"] = new s355( L"eq", &s797::s417, s828->s370() );
s366[L"through"] = new s355( L"through", &s797::s346, s784->s370() );
s310->TR().s1067( s516, L"is", L"container" );
}
s505* s797::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s797( s310, s616, L"" );
}
s505* s797::s374( s282* s616, const std::vector<s1175>& vt ) const
{
assert( 0 );
return 0;
}
inline bool
s797::s525( const s505* s526 ) const
{
return ( ((s327*)s526)->s370() == s370() );
}
s1175 s797::s331() const
{ throw new s18( L"UntypedVector doesn't have element type." ); }
s281* s797::s353() const
{
return new s797( *this );
}
void s797::s375( s507 p ) const
{
p = new s797( *this );
}
void s797::assign( const vector<s507>& p )
{
s367.assign( begin( p ), end( p ) );
}
#undef s737
#define s737 ((s797*)(s506*)*s284)
inline void s797::s406( s505** s284, size_t s521 )
{
s284[3]->s375( ( (s797*)DR )->s367[(int)*s284[2]] );
}
inline void s797::s341( s505** s284, size_t s521 )
{
*s284 = (s505*)(s281*)( (s797*)DR )->s367[(int)*s284[2]];
}
inline void s797::s1104( s505** s284, size_t s521 )
{
*s284 = (s505*)(s281*)( (s797*)DR )->s367[0];
}
inline void s797::s1189( s505** s284, size_t s521 )
{
*s284 = (s505*)(s281*)( (s797*)DR )->s367[1];
}
inline void s797::s342( s505** s284, size_t s521 )
{
/*if( ( (s797*)DR )->s331() != s284[2]->s518() )
throw new s18( L"unmatched element type" );*/
( (s797*)DR )->s367.push_back( s284[2]->s353() );
}
inline void s797::s343( s505** s284, size_t s521 )
{
*( (s364*)*s284 )->s376() = (int)( (s797*)DR )->s367.size();
}
inline void s797::s344( s505** s284, size_t s521 )
{
int size = (int)*s284[2];
( (s797*)DR )->s367.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s797*)DR )->s367[i] = ( (s797*)DR )->s310->s225(
( (s797*)DR )->s328, ( (s797*)DR )->s522 ).s17<s506*>();*/
}
inline void s797::s345( s505** s284, size_t s521 )
{
( (s797*)DR )->s367.clear();
}
inline void s797::s417( s505** s284, size_t s521 )
{
size_t size = ( (s797*)DR )->s367.size();
s797* right = (s797*)s284[2];
if( right->s367.size() != size ) {
*( (s364*)*s284 )->s376() = 0;
return;
}
for( size_t n = 0; n < size; ++n ) {
if( right->s367[n] != ( (s797*)DR )->s367[n] ) {
*( (s364*)*s284 )->s376() = 0;
return;
}
}
*( (s364*)*s284 )->s376() = 1;
}
inline void s797::s346( s505** s284, size_t s521 )
{
*( (s364*)*s284 )->s376() = (int)( (s797*)DR )->s367.size();
}
wstring s797::to_wstring() const
{
wstring s721 = L"UT[";
for( size_t n = 0; n < s367.size(); ++n )
s721 += s367[n]->to_wstring() + ( n == s367.size() - 1 ? L"" : L", " );
s721 += L"]";
return s721;
}
void s797::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s367.size(); ++n )
s367[n]->s314( pd, s205 + s438 );
}
size_t s797::s334() const
{
size_t s721 = 0;
for( size_t n = 0; n < s367.size(); ++n )
s721 = s721 * ( ( s505* )&( *s367[n] ) )->s334() << 1;
return s721;
}
bool s797::operator==( const s505* p ) const
{
if( ( (s797*)p )->s367.size() != s367.size() )
return false;
for( size_t n = 0; n < s367.size(); ++n ) {
const s505* l = s367[n].s17<s505*>();
const s505* r = ( (const s797*)p )->s367[n].s17<s505*>();
if( !( *l == r ) )
return false;
}
return true;
}
bool s797::operator<( const s505* p ) const
{
return false;
}
Iterator* s797::s325( s505* s1202, s505* s1204 )
{
s1059::iterator start = s367.begin() + ( s1202->s370() == s784->s370() ?
0 : (int)*s1202 );
s1059::iterator stop = s367.end() - ( s1204->s370() == s784->s370() ?
0 : (int)*s1204 );
return new s1056( start, stop );
}
/*s508 s797::s326()
{
if( s329 == s367.end() ) {
return NULL;
}
s508 s721 = ( *s329 ).s17<s505*>();
s329++;
return s721;
}*/
s1053::s1053( s272* s310, s282* s616, const std::wstring& s80, 
const s273* ast_ )
: s797( s310, s616, s80, ast_, L"," )
{
s516 = s1054.s14() ? 0 : s1054->s370();
}
s1053::s1053( s272* s310, const std::vector<s281*>& l, const s273* ast_ )
: s797( s310, l, ast_ )
{
s516 = s1054->s370();
}
s1053::s1053( const s1053& right, const s273* ast_ )
: s797( s310, right.s631() )
{
s367.assign( begin( right.s367 ), end( right.s367 ));
s516 = right.s516;
}
s505* s1053::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
wstring sv;
wstring s365 = s372();
if( s.find( L"[[" ) == 0 )
sv = s;
else if( s.find( s365 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s55( s.substr( s365.size() ), s51 );
if( sv[0] != L'(' )
throw new s18( L"wrong vector constructor syntax" );
sv = s4::s55( sv.substr( 1, sv.size() - 2 ), L" " );
}
else
return 0;
return new s1053( s310, s616, sv );
}
void s1053::s523( s282* s965 )
{
for( size_t n = 0; n < s367.size(); ++n ) {
if( s367[n]->s517() == s496 ) {
s367[n]->s523( s965 );
s367[n] = s367[n].s17<s390*>()->s396();
}
s507 s1208 = s281::s1125( s310, s367[n], s965, NULL, s965->s308() );
s367[n] = s1208;
}
s872::Cont v = { s1054->s370() };
for( auto s1174 : s367 )
v.push_back( s1174->s370() );
s516 = s310->TR().s1158( v );
s366[L"get"]->s356 = s832->s370();// s328;
s366[L"fst"]->s356 = s367.size() ? s367[0]->s370() : s832->s370();
s366[L"snd"]->s356 = ( s367.size() > 1 ) ? s367[1]->s370() : s832->s370();
s522 = s965->s903();
}
s505* s1053::s374( s282* s616, const std::vector<s1175>& vt ) const
{
size_t n = vt[1];
s1053* s721 = new s1053( s310, NULL, L"" );
for( size_t k = 0, idx = 2; k < n; ++k) {
s872::Cont s1190;
s513::s1112( vt, idx, s1190 );
if( s1190.size() == 2 )
s721->s367.push_back( (s506*) s310->TR().s1111( s1190[0] )->s374( s616 ) );
else
s721->s367.push_back( (s506*) s310->TR().s1111( s1190[0] )->s374( s616, 
s1190 ) );
}
return s721;
}
s1030::s1030( s1031 s1202, s1031 s1204 )
: s329( s1202 ), s1205( s1204 ), s1091( NULL, vector<s281*>(
{s1202->first.s17<s281*>(), s1202->second.s17<s281*>() }))
{
}
s281* s1030::s326()
{
if( s329 == s1205 )
return NULL;
s1091.assign( vector<s507>(
{ ( *s329 ).first.s17<s506*>(),( *s329 ).second.s17<s506*>() } ));
++s329;
return &s1091;
}
s281* s1030::s1057()
{
return (*s329).second.s17<s506*>();
}
s336::s336( s272* s310, s282* s616, const wstring& s80, const s273* ast_ )
: s340( s310, ast_ ), s337( 0 ), s338( 0 )
{
if( s80.size() ) {
if( s80[0] == L'{' ) {
s522 = s80;
}
else if( s80[0] == L'(' ) {
wstring sv = s4::s55( s80.substr( 1, s80.size() - 2 ), L" " );
wsmatch s1188;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1188, rg ) ) {
wstring s1212 = s1188[1].str();
wstring s1213 = s1188[2].str();
sv = L"Index(" + s1212 + L" " + s1213 + L")";
s522 = sv;
}
}
else
s522 = s80;
}
s516 = s774.s14() ? 0 : s774->s370();
}
s336::s336( const s336& right, const s273* ast_ )
: s340( right.s310, ast_ ), s337( right.s337 ), s338( right.s338 )
{
s367 = right.s367;
s516 = right.s516;
}
s505* s336::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
wstring si;
wstring s365 = s372();
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s55( s, L"{}" );
else if( s.find( s365 ) == 0 && s[s.size() - 1] == L')' ) {
si = s4::s55( s.substr( s365.size() ), s51 );
if( si[0] != L'(' )
throw new s18( L"wrong index constructor syntax" );
}
else
return 0;
return new s336( s310, s616, si, &s740 );
}
void s336::s523( s282* s965 )
{
TDException s1064( s8::s1014, s1023, s631(), L"wrong Index definition" );
const wstring& s80 = s522;
if( s80.find(L"Index(") == 0 ) {
s872::Cont vt, s1132, s1224;
size_t pos = 0;
s310->TR().s1168( s80, pos, vt );
size_t idx = 2;
s513::s1112( vt, idx, s1132 );
s872 s1131( s1132[0] );
s337 = s310->TR().s1115( s1131 );
s513::s1112( vt, idx, s1224 );
s872 s1221( s1224[0] );
s338 = s310->TR().s1115( s1221 );
}
else if( s80[0] == L'{' ) {
vector<s1::s10<s7::s148>> s160;
s1::s10<s7::s150> ob = new s7::s150( NULL );
size_t pos = 0;
s1037 s1164( L"" );
s1164.s178( s80, pos, ob, true );
vector<pair<wstring, s149>> s151;
ob->s167( s151 );
for( size_t n = 0; n < s151.size(); ++n ) {
s1039 s1074 = new s273( s151[n].first );
s505* s1170 = (s505*)s281::s528( *s1074, s310, s965, s965->s308() );
basic_stringstream<wchar_t> s1199;
s151[n].second->s162( &s1199 );
s1039 s234 = new s273( s1199.str() );
s505* s1179 = (s505*)s281::s528( *s234, s310, s965, s965->s308() );
if( !s337 ) {
s337 = s1170->s370();
s338 = s1179->s370();
}
if( s337 != s1170->s370() || s338 != s1179->s370() )
throw s1064.s1102( L"incompatible types in the index initialization list" );
s367.insert( make_pair( s1170, s1179 ) );
}
}
else if( s367.empty() )
throw s1064.s1102( L"unknown Index declaration syntax: " + s80 );
s328 = s310->TR().s1158( s872::Cont( { s1054->s370(), s337, s338 }) );
s516 = s310->TR().s1158( s872::Cont( { s774->s370(), s328 }) );
s366[L"get"]->s356 = s328;
s366[L"get-s"]->s356 = s328;
s522 = s965->s903();
}
void s336::s368()
{
s366[L"insert"] = new s355( L"insert", &s336::s347, s784->s370());
s366[L"get"] = new s355( L"get", &s336::s341, 0 );
s366[L"get-s"] = new s355( L"get-s", &s336::s1118, 0 );
s366[L"set"] = new s355( L"set", &s336::s406, s806->s370() );
s366[L"erase"] = new s355( L"erase", &s336::s348, s784->s370() );
s366[L"size"] = new s355( L"size", &s336::s343, s828->s370() );
s366[L"through"] = new s355( L"through", &s336::s346, s784->s370() );
s310->TR().s1067( s516, L"is", L"container" );
}
s505* s336::s374( s282* s616, const std::vector<s281*>& l ) const
{
s1::s10<s336> s721 = new s336( s310, s616, L"" );
s721->s337 = s337;
s721->s338 = s338;
return s721;
}
s505* s336::s374( s282* s616, const std::vector<s1175>& vt ) const
{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s336* s721 = new s336( s310, NULL, L"" );
s872::Cont s1094;
s513::s1112( vt, idx, s1094 );
s872 s1093( s1094[0] );
s721->s328 = s310->TR().s1115( s1093 );
const s872& s1220 = s310->TR().s1117( s721->s328 );
s505 *s1170, *s1179;
s872::Cont s1132, s1224;
idx = 2;
s513::s1112( s1220.s880(), idx, s1132 );
s872 s1131( s1132[0] );
s721->s337 = s310->TR().s1115( s1131 );
if( s1132.size() == 2 )
s1170 = s310->TR().s1111( s1132[0] )->s374( s616 );
else
s1170 = s310->TR().s1111( s1132[0] )->s374( s616,	s1132 );
s513::s1112( s1220.s880(), idx, s1224 );
s872 s1221( s1224[0] );
s721->s338 = s310->TR().s1115( s1221 );
if( s1224.size() == 2 )
s1179 = s310->TR().s1111( s1224[0] )->s374( s616 );
else
s1179 = s310->TR().s1111( s1224[0] )->s374( s616, s1224 );
s721->s328 = s310->TR().s1158( s872::Cont{ s1054->s370(), s721->s337, 
s721->s338 } );
s721->s367.insert( make_pair( s1170, s1179 ) );
return s721;
}
inline bool
s336::s525( const s505* s526 ) const
{
return 0; /* ( ( (s327*)s526 )->s328 == s328 );*/
}
s281* s336::s353() const
{
return new s336( *this );
}
void s336::s375( s507 p ) const
{
p =  new s336( *this );
}
size_t s336::s334() const
{
return (size_t)this;
}
bool s336::operator==( const s505* p ) const
{
return ( this == p );
}
bool s336::operator<( const s505* p ) const
{
return false;
}
#undef s737
#define s737 ((s336*)(s506*)*s284)
inline void s336::s347( s505** s284, size_t s521 )
{
s505* s159 = (s505*)PARN( 2 );
s505* s367 = (s505*)PARN( 3 );
s336* dr = (s336*)DR;
if( dr->s337 != s159->s370() || dr->s338 != s367->s370() )
throw new s18( L"non-compatible types cannot be inserted to an Index" );
dr->s367.insert( make_pair( s159, s367 ) );
}
inline void s336::s341( s505** s284, size_t s521 )
{
s336* p = (s336*)DR;
s1029::iterator it = p->s367.find( (s505*)PARN( 2 ) );
if( it == p->s367.end() )
*s284 = NULL;
else {
*s284 = new s1053( p->s310, vector<s281*>( 
{ it->first.s17<s506*>(), it->second.s17<s506*>() }));
}
}
inline void s336::s1118( s505** s284, size_t s521 )
{
s336* p = (s336*)DR;
s1029::iterator it = p->s367.find( (s505*)PARN( 2 ) );
if( it == p->s367.end() ) {
*s284 = new s1053( p->s310, vector<s281*>(
{ (s505*)PARN( 2 ), (s505*)PARN( 3 ) } ) );
}
else {
*s284 = new s1053( p->s310, vector<s281*>(
{ it->first.s17<s506*>()->s353(), it->second.s17<s506*>()->s353() } ) );
}
}
inline void s336::s406( s505** s284, size_t s521 )
{
s505* s159 = (s505*)PARN( 2 );
s505* s367 = (s505*)PARN( 3 );
s336* dr = (s336*)DR;
if( dr->s337 != s159->s370() || dr->s338 != s367->s370() )
throw new s18( L"non-compatible types cannot be inserted to an Index" );
s1029::iterator it = dr->s367.find( (s505*)PARN( 2 ) );
if( it == dr->s367.end() ) {
s505* pdval = (s505*)s367->s353();
dr->s367.insert( make_pair( (s505*)s159->s353(), pdval ) );
*s284 = s388;
}
else {
it->second = (s505*)s367->s353();
*s284 = s389;
}
}
inline void s336::s348( s505** s284, size_t s521 )
{
s336* p = (s336*)DR;
p->s367.erase( (s505*)PARN( 2 ) );
}
inline void s336::s343( s505** s284, size_t s521 )
{
}
inline void s336::s346( s505** s284, size_t s521 )
{
}
Iterator* s336::s325( s505* s1202, s505* s1204 )
{
if( s1202->s370() != s784->s370() || s1204->s370() != s784->s370() )
throw new s18( L"Index container is not ordered." );
s1029::iterator s1129 = s367.begin();
s1029::iterator s1130 = s367.end();
return new s1030( s1129, s1130 );
}
/*s508 s336::s326()
{ 
if( s329 == s367.end() )
return NULL;
s508 s721 = s329->second;
s329++; 
return s721;
}*/
wstring s336::to_wstring() const
{
wstring s721 = L"{ ";
for( auto it = begin(s367); it != end(s367); ++it )
s721 += ( it == begin(s367) ? L"" : L", " ) + it->first->to_wstring() + L" : " + 
it->second->to_wstring();
s721 += L" }";
return s721;
}
void s336::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"Index : " << endl;
/*for( size_t n = 0; n < s367.size(); ++n )
s367[n]->s314( pd, s205 + s438 );*/
}
vector<wstring> s1043( { L"where", L"do", L"in", L"from", L"to" } );
s404::s404( s272* s310, const wstring& s80, const s273* ast_ )
: s340( s310, ast_ ), s1089( L"@it", s310 ), s367( new s364( s310, 0 )), 
s721( new s364( s310, 0 ))
{
s516 = s868.s14() ? 0 : s868->s370();
}
s404::s404( s272* s310, long fi, long la, long in, const s273* ast_ )
: s340( s310, ast_ ), s1089( L"@it", s310 ), s367( new s364( s310, 0 ) ), 
s721( new s364( s310, 0 )),
fir( new s364( s310, fi ) ), las( new s364( s310, la ) ), inc( new s364( s310, in ) )
{
s516 = s868->s370();
}
s404::s404( s272* s310, s507 fi, s507 la, s507 inc, const s273* ast_ )
: s340( s310, ast_ ), s1089( L"@it", s310 ), s367( new s364( s310, 0 ) ), 
s721( new s364( s310, 0 )), fir( fi ), las( la ), inc( inc )
{
s516 = s868->s370();
}
s404::s404( const s404& right, const s273* ast_ )
: s340( right.s310, ast_ ), s1089( L"@it", s310 ), s367( new s364( s310, 0 ) ), 
s721( new s364( s310, 0 ) )
{
*s367->s376() = (int)*right.s367;
*s721->s376() = (int)*right.s721;
first = right.first;
last = right.last;
incr = right.incr;
s516 = right.s516;
}
s404::s404( s272* s310, s282* s620, const std::vector<s281*>& l_, const s273* ast_ )
: s340( s310, ast_ ), s1077(false), s1078(false),s1089( L"@it", s310 ),
s367( new s364( s310, 0 ) ),	s721( new s364( s310, 0 ) ),	fir( new s364( s310, 0 ) ), 
inc( new s364( s310, 1 ) )
{
if( l_.empty() )
return;
TDException s1064( s8::s1228, s1023, ast_ );
if( l_.size() > 9 )
throw s1064.s1102( L"too many arguments" );
for( s281* p : l_ ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1043 );
}
const size_t s1167 = 6;
std::vector<s281*> l(s1167);
if( l_.size() ) {
if( !s310->TR().s1127( l_[0]->s370() ) )
throw s1064.s1102( L"the type is not rangeable: " + l_[0]->s372() );
l[0] = l_[0];
}
size_t s1087 = 1;
for( size_t n = 1; n < l_.size() && s1087 < s1167; ++n ) {
if( l_[n]->s517() == s496 && ( (s390*)l_[n] )->s400().s14() )
( (s390*)l_[n] )->s523( s620 );
if( l_[n]->s517() == s1177 ) {
s1::s10<s390> rf = (s390*)l_[n];
if( rf->s647() == L"in" ) 
throw s1064.s1102( L"'in' determiner is misplaced " + l_[0]->s372() );
else if( rf->s647() == L"from" ) s1087 = 1;
else if( rf->s647() == L"to" ) s1087 = 2;
else if( rf->s647() == L"where" ) s1087 = 3;
else if( rf->s647() == L"do" ) s1087 = 4;
}
else if( l_[n]->s517() == s496 ) {
s1::s10<s390> rf = (s390*)l_[n];
if( rf->s647() == L":v" ) {
if( n == 1 )
s1077 = true;
else
s1078 = true;
}
else if( rf->s647() == L":i" ) (void)0;
else if( rf->s647() == L"where" ) s1087 = 3;
else if( rf->s647() == L"do" ) s1087 = 4;
else l[s1087++] = l_[n];
}
else if( l_[n]->s517() == s503 ) {
if( l_[n] == s954 ) s1087 = 5;
}
else
l[s1087++] = l_[n];
}
s616 = l[0];
start = l[1];
stop = l[2];
where = l[3];
s1184 = l[4];
s1186 = (s505*)l[5];
if( s1186.s14() )
throw s1064.s1102( L"return type is missing" );
}
s505* s404::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s = s740.s301();
wstring s365 = s372();
if( s.find( s365 ) == 0 && s[s.size() - 1] == L')' ) {
s507 fi = new s364( s310, 0 ), la = new s364( s310, 0 ), in = new s364( s310, 1 );
wstring sv = s4::s55( s.substr( s365.size() ), s51 );
if( sv[0] != L'(' )
throw new s18( L"wrong range constructor syntax" );
wstring s735 = L"Malformed Range definition: " + s;
const s273::s285& s741 = s740.s303();
size_t s736 = s741.size();
if( /*!s736 ||*/ s736 > 3 )
throw new s18( s735 );
std::vector<s281*> s284;
for( size_t n = 0; n < s736; ++n ) {
s273::s285::const_iterator it = s741.find( std::to_wstring( n ) );
s284.push_back( s281::s528( *it->second, s310, s616, s350 ) );
}
return s374( s616, s284 );
if( s310->TR().s1120( s284[0]->s370(), L"is", L"container" ) ||
s310->TR().s1120( s284[0]->s370(), L"is", L"ordered" )  ||
s310->TR().s1120( s284[0]->s370(), L"is", L"indexed" ) ) {
return new s404( s310, s616, s284 );
}
else
return new s1044( s310, s284 );
/*if( s736 == 1 ) {
s273::s285::const_iterator it = s741.find( L"0" );
la = s281::s528( *it->second, s310, s616, s350 );
}
else {
s273::s285::const_iterator it = s741.find( L"0" );
fi = s281::s528( *it->second, s310, s616, s350 );
it = s741.find( L"1" );
la = s281::s528( *it->second, s310, s616, s350 );
if( s736 == 3 ) {
it = s741.find( L"2" );
in = s281::s528( *it->second, s310, s616, s350 );
}
}*/
return new s404( s310, fi, la, in );
}
else
return NULL;
}
void s404::s523( s282* s965 )
{
TDException s1064( s8::s1010, s1023, s631(), L"wrong Range definition");
ns = s965;
if( s616->s517() == s496 ) {
s1086 = s616.s17<s390*>()->s396();
}
else {
s616 = s281::s1125( s310, s616, s965, NULL, s965->s308() );
s1086 = s616.s17<s505*>();
}
s1175 s1122, s1221;
if( s1086->s517() == s495 ) {
s1122 = s1086.s17<s340*>()->s1028();
s1221 = s1086.s17<s340*>()->ValType();
}
else if( s1086->s517() == s502 ) {
wstring s1206 = s310->TR().s1109( s1086->s370(), s8::s1005 );
s1122 = s310->TR().s1114( s1206 );
s1206 = s310->TR().s1109( s1086->s370(), s8::s1007 );
s1221 = s310->TR().s1114( s1206 );
}
else
throw s1064.s1102( L"unsupported container type" );
s1089.s398( 0, s310->TR().s1111( s1086.s17<s340*>()->ValType() ) );
s1089.s401( (s505*)this );
if( start.s15() ) {
if( start->s517() == s496 )
start.s17<s390*>()->s523( s965 );
else
start = s281::s1125( s310, start, s965, NULL, s965->s308() );
if( start->s370() != ( s1077 ? s1221 : s1122 ) )
throw s1064.s1102( wstring( L"start element doesn't match the container's " ) +
( s1077 ? L"value" : L"index" ) + L" type");
}
else
start = s384.s17<s506*>();
/*else {
start = s310->s225( start->s370(), s965->s308() );
start->s523( s965 );
}*/
if( stop.s15() ) {
if( stop->s517() == s496 )
stop.s17<s390*>()->s523( s965 );
else
stop = s281::s1125( s310, stop, s965, NULL, s965->s308() );
if( stop->s370() != ( s1078 ? s1221 : s1122 ) )
throw s1064.s1102( L"the stop element doesn't match the container's " +
wstring( ( s1078 ? L"value" : L"index" ) ) + L"type" );
}
else
stop = s384.s17<s506*>();
if( where.s15() ) {
if( where->s517() == s496 )
where.s17<s390*>()->s523( s965 );
else
where = s281::s1125( s310, where, s965, (s619*)s965, s965->s308() );
}
if( s1184.s15() ) {
if( s1184->s517() == s496 )
s1184.s17<s390*>()->s523( s965 );
else
s1184 = s281::s1125( s310, s1184, s965, (s619*)s965, s965->s308() );
}
if( s1186.s15() ) {
if( s1186->s517() == s496 )
throw s1064.s1102( L"wrong return type: should be a data type, not reference" );
else
s1186 = (s505*)s281::s1125( s310, s1186, s965, (s619*)s965,
s965->s308() );
}
s1175 s1066 = s1186->s520(0,0)->s370();
s516 = s310->TR().s1158( s872::Cont( { s868->s370(), s1066 }) );
}
void s404::s368()
{
s310->TR().s1067( s516, L"is", L"iterable" );
}
s505* s404::s374( s282* s616, const std::vector<s281*>& l ) const
{
if( l.empty() ||
s310->TR().s1127( l[0]->s370() ) ) {
return new s404( s310, s616, l );
}
else
return new s1044( s310, l );
if( l.size() ) {
if( l[0]->s517() == s496 ) {
l[0]->s523( s616 );
if( s310->TR().s1127( l[0]->s370() ) )
return new s404( s310, s616, l );
}
}
else {
return new s404( s310, s616, l );
}
return new s1044( s310, l );
}
s505* s404::s374( s282* s616, const std::vector<s1175>& vt ) const
{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s404* s721 = new s404( s310, L"" );
s872::Cont s1187;
s513::s1112( vt, idx, s1187 );
s872 s1185( s1187[0] );
if( s1187.size() == 2 )
s721->s1186 = s310->TR().s1111( s1187[0] )->s374( s616 );
else
s721->s1186 = s310->TR().s1111( s1187[0] )->s374( s616, s1187 );
return s721;
}
inline bool
s404::s525( const s505* s526 ) const
{
return ( ((s404*)s526)->s370() == s370() );
}
s281* s404::s353() const
{
return new s404( *this );
}
void s404::s375( s507 p ) const
{
p = new s404( *this );
}
size_t s404::s334() const
{
return (size_t)this;
}
bool s404::operator==( const s505* p ) const
{
return ( this == p );
}
bool s404::operator<( const s505* p ) const
{
return false;
}
bool
s404::s583( const wstring& s712, s390* ref, const wstring& s350 ) const
{
if( s712 == L"@it" ) {
ref->s398( 0, s310->TR().s1111( s1086.s17<s340*>()->ValType() ));
ref->s401( (s505*)this );
return true;
}
return false; // ns->s583( s712, ref, s350 );
}
s281* s404::s626( size_t off )
{
assert( off == 0 );
if( s1090 )
return s1090;
return (s281*) s1089.s527();
}
Iterator* s404::s325( s505* s1202, s505* s1204 )
{
assert( s1202 == s384 && s1204 == s384 );
s329 = s1086.s17<s340*>()->s325( start.s17<s505*>(), stop.s17<s505*>() );
return this;
}
s281* s404::s326()
{
while( 1 ) {
s1090 = s329->s326();
if( !s1090 )
return NULL;
if( where.s15() && ( false == (bool)*where->s520(0,0) ) )
continue;
break;
}
if( s1184.s15() )
return s1184->s520( 0, 0 ).s17<s506*>();
else
return s1090;
}
s281* s404::s1057()
{
return s329->s1057();
}
void s404::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"Range : " << 
first << L", " << last << L", " << incr << endl;
}
vector<wstring> s1048( { L"asc", L"desc", L"a", L"d", L"ascending", L"descending" } );
s912::s912( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s929, s740 ), s935( NULL )
{
if( l.size() < 1 || l.size() > 3 )
throw new s18( L"malformed syntax of 'sort' procedure call." );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
for( s281* p : s284 ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1048 );
}
}
void
s912::s523( const wstring& s350, bool proc )
{
reverse = false;
size_t idx = 1;
while( s284.size() > idx ) {
s507 par_ = s284[idx];
s493 pc = par_->s517();
if( pc == s1177 ) {
if( par_.s17<s390*>()->s647()[0] == L'd' )
reverse = true;
}
else if( par_->s517() == s499 ) {
s512 cs = new s588( *par_.s17<s588*>() );
s935 = s628( cs, s310, s616, this, s308() );
}
else
throw new s18( L"malformed syntax of 'sort' procedure call." );
s284.erase( s284.begin() + idx );
}
s619::s523( s350, proc );
if( s935 )
s935->s523( s350, false );
}
s508 s912::s520( s505** s744, size_t s521 )
{
s493 pc = s284[0]->s517();
s1::s10<s340> s616;
if( pc == s497 ) {
s616 = s284[0]->s520( 0, 0 ).s17<s340*>();
}
else
s616 = ((s340*)s284[0].s17<s390*>()->s396());
s913 cmp_( s935 );
return s616->sort( reverse, s935.s15() ? &cmp_ : nullptr );
}
s281* s912::s353()const
{
return new s912( *this );
}
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
s434::s434( s272* s310, const wstring& s80, const s273* ast_ )
: s354( s310, ast_ ), s802( s310, NULL, L"" ), s865( s310, NULL, L"" )
{
s516 = s870.s14() ? 0 : s870->s370();
s802.s12();
s865.s12();
}
s434::s434( const s434& right, const s273* ast_ )
: s354( right.s310, ast_ ), s802( right.s310, NULL, L"" ), s865( right.s310, NULL, L"" )
{
s802 = right.s802;
s865 = right.s865;
s516 = right.s516;
}
s505* s434::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
return new s434( s310, L"" );
}
void s434::s523( s282* s965 )
{
s366[L"files"]->s356 = 
s310->TR().s1158( s872::Cont( { s768->s370(), s846->s370() }) );
s366[L"dirs"]->s356 = 
s310->TR().s1158( s872::Cont( { s768->s370(), s846->s370() }) );
}
void s434::s368()
{
s366[L"read"] = new s355( L"read", &s434::s428, s784->s370() );
s366[L"reset"] = new s355( L"reset", &s434::s435, s784->s370() );
s366[L"files"] = new s355( L"files", &s434::s436, 0 /*s768->s370()*/ );
s366[L"dirs"] = new s355( L"dirs", &s434::s1092, 0 /*s768->s370()*/ );
s366[L"size"] = new s355( L"size", &s434::s343, s828->s370() );
}
s505* s434::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s434( s310, L"" );
}
inline bool
s434::s525( const s505* s526 ) const
{
return ( ((s434*)s526)->s370() == s370() );
}
s281* s434::s353() const
{
return s507( new s434( *this ) );
}
void s434::s375( s507 p ) const
{
p = new s434( *this );
}
#undef s737
#define s737 ((s434*)(s506*)*s284)
inline void s434::s428( s505** s284, size_t s521 )
{
wstring path = ((s378*)PARN( 2 ) )->to_wstring();
const wstring& s551 = ((s378*)PARN( 3 ))->to_wstring();
vector<wstring> s842, s851;
s434* s835 = (s434*)DR;
s835->s802.clear();
s835->s865.clear();
if( !s3::s764( path ) )
path = s835->s310->s756() + path;
s4::s64( path );
s3::s34( path, s551, s842, s851 );
for( auto f : s842 )
s835->s802.add( new s378( s835->s310, s4::s792( path + f ) ) );
for( auto f : s851 )
s835->s865.add( new s378( s835->s310, s4::s792( path + f ) ) );
}
inline void s434::s435( s505** s284, size_t s521 )
{
s434* s835 = (s434*)DR;
s835->s802.clear();
s835->s865.clear();
}
inline void s434::s436( s505** s284, size_t s521 )
{
*s284 = &( (s434*)DR )->s802;
}
inline void s434::s1092( s505** s284, size_t s521 )
{
*s284 = &( (s434*)DR )->s865;
}
inline void s434::s343( s505** s284, size_t s521 )
{
s434* s835 = (s434*)DR;
*( (s364*)*s284 )->s376() = (int)(s835->s802.size() + s835->s865.size());
}
wstring s434::to_wstring() const
{
wstring s721;
for( size_t n = 0; n < s865.size(); ++n )
s721 += ( n ? L" \"" : L"\"" ) + s865[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s802.size(); ++n )
s721 += ( n ? L" \"":L"\"") + s802[n]->to_wstring() + L"\"";
return s721;
}
void s434::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"Directory : " << endl;
for( size_t n = 0; n < s865.size(); ++n )
s865[n]->s314( pd, s205 + s438 );
for( size_t n = 0; n < s802.size(); ++n )
s802[n]->s314( pd, s205 + s438 );
}
size_t s434::s334() const
{
size_t s721 = 0;
for( size_t n = 0; n < s865.size(); ++n )
s721 = s721 * ( (s505*)&(s865[n]) )->s334() << 1;
for( size_t n = 0; n < s802.size(); ++n )
s721 = s721 * ( (s505*)&(s802[n]) )->s334() << 1;
return s721;
}
bool s434::operator==( const s505* p ) const
{
if( ( (s434*)p )->s802.size() != s802.size() )
return false;
if( ( (s434*)p )->s865.size() != s865.size() )
return false;
for( size_t n = 0; n < s802.size(); ++n )
if( !( ( s281* )&( *s802[n] ) == (s281*)( (s434*)p )->s802[n] ) )
return false;
for( size_t n = 0; n < s865.size(); ++n )
if( !( ( s281* )&( *s865[n] ) == (s281*)( (s434*)p )->s865[n] ) )
return false;
return true;
}
bool s434::operator<( const s505* p ) const
{
return false;
}
void Stream::write( s507 )
{ throw new s18( L"not implemented" ); };
s531::s531( s272* s310, const s273* ast_ )
: s354( s310, ast_ )
{
s516 = s874.s14() ? 0 : s874->s370();
}
s531::s531( const s531& r, const s273* ast_ )
: s354( r.s310, ast_ ), ss( r.ss.str() )
{
s516 = s874->s370();
}
s505* s531::s374( s282* s616, const std::vector<s281*>& ) const
{
return new s531( s310 );
}
void s531::s368()
{
s366[L"str"] = new s355( L"str", &s531::s532, s846->s370() );
s366[L"clear"] = new s355( L"clear", &s531::s345, s874->s370() );
}
void s531::s523( s282* s965 )
{
}
s505* s531::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
wstring s_ = s740.s301();
if( s_.find( L"StringStream(" ) == 0 )
return new s531( s310 );
return NULL;
}
s281* s531::s353() const
{
return new s531( *this );
}
void s531::s375( s507 p ) const
{
if( p->s370() == s874->s370() )
p.s17<s531*>()->ss.rdbuf()->str( ss.str() );
else
throw new s18( L"No conversion to type " + std::to_wstring( p->s370() ) );
}
wstring s531::to_wstring() const 
{
return ss.str(); 
}
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
#undef s737
#define s737 ((s531*)(s506*)*s284)
inline void s531::s532( s505** s284, size_t s521 )
{
*( (s378*)s284[0] )->s376() = ( (s531*)DR)->ss.str();
}
inline void s531::s345( s505** s284, size_t s521 )
{
((s531*)DR)->ss.rdbuf()->str(L"");
}
void s531::write( s507 p )
{
ss << p->to_wstring();
}
void s531::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << s372() << L" : " << ss.str() << endl;
}
size_t s531::s334() const
{
return hash<wstring>{}(ss.str());
}
bool s531::operator==( const s505* p ) const
{
return ( (s531*)p )->ss.str() == ss.str();
}
bool s531::operator<( const s505* p ) const
{
return ss.str() < ( (s531*)p )->ss.str();
}
s633::s633( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s242, s740 )
{
s288 = s242;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( l[n]->s517() != s496 )
break;
s390* s79 = (s390*)l[n];
lang::s689( s79->s647() );
s505* s650 = (s505*)l[n + 1];
s659.s568( s79->s647(), s650 );
s284.push_back( s650 );
s610.push_back( s650 );
s661.push_back( s650 );
s662.push_back( s79->s647() );
}
s612.insert( s612.end(), l.begin() + n, l.end() );
}
void
s633::s523( const wstring& s350, bool proc )
{
return s619::s523( s350, proc );
s706 = s350;
if( s616->s517() == s501 || s616->s517() == s500 ) {
if( s616->s517() == s500 )
return;
}
if( s284.size() > s661.size() )
throw new s18( L"too many pars" );
for( size_t n = 0; n < s284.size(); ++n ) {
s507 par = s284[n];
if( par->s517() == s496 ) {
if( par.s17<s390*>()->s400().s14() )
par.s17<s390*>()->s523( this );
}
else
s284[n] = s921( par );
}
for( size_t n = 0; n < s284.size(); ++n ) {
s659.s568( s662[n], s284[n].s17<s505*>(), s504::s154 );
s284[n]->setWh( s8::s945 );
s661[n] = s284[n];
}
for( size_t n = 0; n < s612.size(); ++n ) {
if( s612[n]->s517() == s499 ) {
s512 cs = new s588( *s612[n].s17<s588*>() );
s612[n] = s628( cs, s310, s616, this, s616->s309() );
}
else if( s612[n]->s517() == s496 )
s612[n].s17<s390*>()->s523( s615 );
else if( s612[n]->s517() != s497 )
s612[n]->s523( s615 );
else // lambda - ?
throw new s18( L"unhandled expression" );
}
for( auto it : s612 ) {
if( it->s517() == s497 )
it.s17<Transd*>()->s523( s350, true );
}
if( !s516 && s612.size() ) {
s516 = s612.back()->s370();
s614 = s310->TR().s545( s370(), s616, s350 );
}
}
s508
s633::s520( s505** s727, size_t s736 )
{
s508 s721 = s384, s160;
for( size_t n = 0; n < s284.size(); ++n ) {
s508 s160 = s284[n]->s520( NULL, 0 );
if( s160->s648() < 0 )
return s721;
s661[n] = s160.s17<s506*>();
}
for( size_t n = 0; n < s612.size(); ++n ) {
s160 = s612[n]->s520( s727, s736 );
s721 = s160;
if( s160->s648() < 0 )
break;
}
return s721;
}
s315::s315( s272* s310, s282* s620, Transd* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s264, s740 )
{
s288 = s264;
if( l.size() < 2 )
throw new s18( s264 + L"(): wrong numbers of arguments" );
s284.push_back( l[0] );
s661.resize( 1 );
s662.push_back( L"@cond" );
s612.insert( s612.end(), l.begin() + 1, l.end() );
}
void
s315::s523( const wstring& s350, bool proc )
{
s619::s523( s350, proc );
s316 = s284[0];
s516 = s612.back()->s370();
}
s508
s315::s520( s505** s727, size_t s736 )
{
s508 s721 = s384, s160;
while( 1 ) {
if( (bool)*s316->s520( 0, 0 ) == false )
return s721; 
for( size_t n = 0; n < s612.size(); ++n ) {
s160 = s612[n]->s520( s727, s736 );
if( s160->s648() < 0 )
break;
}
s721 = s160;
if( s160->s648() == s8::s458 || s160->s648() == s8::s459 )
break;
}
return s721;
}
s318::s318( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s263, s740 ),
s322( s8::s481, s310 ), s323( s310, 0 )
{
if( l.size() < 1 )
throw new s18( s263 + L"(): wrong numbers of arguments" );
s659.s568( s322.s647(), &s323 );
s610.push_back( (s505*)&s323 );
s661.push_back( (s505*)&s323 );
s662.push_back( s322.s647() );
s319 = l[0];
s390* w = (s390*) l[1];
if( w->s647() != L"with" )
throw new s18( L"unknown syntax of 'through' statement" );
s320 = (s390*) l[2];
s659.s568( s320->s647(), s321.s17<s505*>() );
s610.push_back( (s505*)&s323 ); //..
s661.push_back( (s505*)&s323 );
s662.push_back( s320->s647() );
s612.assign( l.begin()+3, l.end() );
}
void
s318::s523( const wstring& s350, bool proc )
{
s493 pc = s319->s517();
if( pc == s499 ) {
s319 = s628( s319.s17<s588*>(), s310, s616, this, s308() );
s319.s17<Transd*>()->s523( s350, proc );
}
else if( pc == s496 )
s319.s17<s390*>()->s523( this );
else
throw new s18( L"unknown container type" );
s661[1] = s310->TR().s545( ( (s340*)s319->s519() )->s331(), s616, s350 );
s661[1]->setWh( s8::s945 );
s619::s523( s350, proc );
}
s508 s318::s520( s505** s727, size_t s736 )
{
s508 s721;
s493 pc = s319->s517();
s1::s10<s340> s616;
if( pc == s497 ) {
s616 = s319->s520(0,0).s17<s340*>();
}
else
s616 = ((s340*)s319.s17<s390*>()->s396());
Iterator* s1128 = s616->s325( s384, s384 );
while( 1 ) {
s507 p = s1128->s326();
if( p.s14() ) {
s721 = s384.s17<s505*>();
break;
}
s661[1] = p;
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s727, s736 );
if( s721->s648() < 0 )
break;
}
if( s721->s648() == s8::s458 || s721->s648() == s8::s459 )
break;
}
return s721;
}
s644::s644( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, 
const s273* s740 )
: s619( s310, s620, s621, s592, s269, s740 ),
s322( s8::s481, s310 ), s323( s310, 0 )
{
wstring s750 = L"malformed syntax of 'for' statement: ";
if( l.size() < 5 )
throw new s18( s750 + L"too few arguments." );
s659.s568( s322.s647(), &s323 );
s610.push_back( (s505*)&s323 );
s661.push_back( (s505*)&s323 );
s662.push_back( s322.s647() );
s281* p = l[0];
if( p->s517() != s496 )
throw new s18( s750 + L"the variable must be a name." );
s752 = (s390*) l[0];
varval = s384.s17<s505*>();
s390* in = (s390*) l[1];
if( in->s647() != L"in" )
throw new s18( s750 + L"the 'in' keyword is missing." );
s319 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = s750 + L"the ACTION clause is non-conforming: should begin with 'select' " +
L"or 'do' keyword and contain at least one statement.";
if( p->s517() != s496 )
throw new s18( actmsg );
if( ((s390*)p)->s647() == L"where" ) {
where = l[4];
idx = 5;
}
if( l.size() < ( idx + 2 ) )
throw new s18( actmsg );
p = l[idx];
if( p->s517() != s496 )
throw new s18( actmsg );
if( ((s390*)p)->s647() == L"select" ) {
if( l.size()  )
select = l[idx+1];
}
else {
if( ((s390*)p)->s647() != L"do" )
throw new s18( actmsg );
s612.assign( l.begin() + (idx + 1), l.end() );
}
s659.s568( s752->s647(), NULL );
s610.push_back( varval );
s661.push_back( varval );
s662.push_back( s752->s647() );
}
void
s644::s523( const wstring& s350, bool proc )
{
wstring s750 = L"malformed syntax of 'for' statement: ";
s493 pc = s319->s517();
if( pc == s499 ) {
s507 s620 = s628( s319.s17<s588*>(), s310, s616, this, s308() );
s319 = s620;
s319.s17<Transd*>()->s523( s350, false );
}
else if( pc == s496 ) {
s319.s17<s390*>()->s523( this );
}
else if( pc == s495 )
s319->s523( this );
else
throw new s18( s750 + L"unknown iterable type." );
varval = s310->TR().s545( ((s340*)s319->s519())->s331(), s616, s350 );
varval->setWh( s8::s945 );
s752->s401( varval );
s661[1] = varval.s17<s506*>();
if( where ) {
pc = where->s517();
if( pc == s499 ) {
where = s628( where.s17<s588*>(), s310, s616, this, s308() );
where.s17<Transd*>()->s523( s350, false );
}
else
throw new s18( s750 + L"PREDICATE must be a function." );
}
if( select ) {
pc = select->s517();
if( pc == s499 ) {
select = s628( select.s17<s588*>(), s310, s616, this, s308() );
select.s17<Transd*>()->s523( s350, false );
}
else
throw new s18( s750 + L"PREDICATE must be a function." );
}
s619::s523( s350, proc );
}
s508 s644::s520( s505** s727, size_t s736 )
{
s508 s721 = s614;
s493 pc = s319->s517();
s10<s340> s616;
if( pc == s497 )
s616 = s319->s520( 0, 0 ).s17<s340*>();
else if( pc == s496 )
s616 = ((s340*)s319.s17<s390*>()->s396());
else
s616 = s319.s17<s340*>();
Iterator* s1128 = s616->s325( s384, s384 );
while( 1 ) {
s507 p = s1128->s326();
if( p.s14() )
break;
s661[1] = p.s17<s506*>();
if( where ) {
if( ((bool)*(s505*)where->s520( 0, 0 )) != true )
continue;
}
if( select ) {
select->s520( 0, 0 );
}
else {
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s727, s736 );
if( s721->s648() < 0 )
break;
}
if( s721->s648() == s8::s458 || s721->s648() == s8::s459 )
break;
}
}
return s721;
}
s281* s633::s353()const
{
return new s633( *this );
}
s281* s315::s353()const
{
return new s315( *this );
}
s281* s318::s353()const
{
return new s318( *this );
}
s281* s644::s353()const
{
return new s644( *this );
}
s632::s632( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l,
const s273* s740 )
: s619( s310, s616, s615, l, s740 )
{
s603 = s600;
}
void s632::s681( s1175 s650, s619* pOvr )
{
types.push_back( s650 );
s682.push_back( pOvr );
}
s508 s632::s520( s505** s727, size_t s736 )
{
if( s602 == s596 && s727[0]->s370() != s516 ) {
s1175 type = s727[0]->s370();
s887* pt = (s887*)&types[0];
for( size_t n = 0; n < types.size(); ++n ) {
if( pt[n] == type )
return s682[n]->s520( s727, s736 );
}
throw new s18( L"dispatching failed" );
}
else {
return s619::s520( s727, s736 );
}
}
s910::s910( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s261, s740 )
{
s288 = s261;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( l[n]->s517() != s496 )
break;
s390* s79 = (s390*) l[n];
lang::s689( s79->s647() );
s505* s650 = (s505*) l[n + 1];
s659.s568( s79->s647(), s650 );
s284.push_back( s650 );
s610.push_back( s650 );
s661.push_back( s650 );
s662.push_back( s79->s647() );
}
s612.insert( s612.end(), l.begin() + n, l.end() );
}
s508 s910::s520( s505** s727, size_t s736 )
{
s508 s721;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s608 + n ) ) {
s493 pc = ( ( s506* )*( s608 + n ) )->s517();
if( pc == s496 )
*( s607 + n + shift ) =
(s505*)( ( s390* )*( s608 + n ) )->s396();
else if( pc == s497 ) {
s1080[n+shift] = (s505*)( ( s619* )*( s608 + n ) )->s520( s727, s736 );
*( s607 + n + shift ) = s1080[n + shift];
}
else if( pc == s495 )
*( s607 + n + shift ) = ( s505* )*( s608 + n );
}
}
s661.assign( s611.begin() + 1, s611.end() );
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s607, s521 );
if( s721->s648() < 0 )
break;
}
return s721;
}
s281* s910::s353()const
{
return s507( new s910( *this ) );
}
s635::s635( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s252, s740 )
{
s284.assign( l.begin(), l.end() );
}
s508 s635::s520( s505** s284, size_t s521 )
{
return NULL;
}
s636::s636( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s252, s740 )
{
s284.assign( l.begin(), l.end() );
s516 = s806->s370();
}
s508 s636::s520( s505**, size_t )
{
*s614.s17<s364*>()->s376() = 1;
for( size_t n = 0; n < s284.size(); ++n ) {
if( !( bool )*( (s506*)( s284[n]->s520( 0, 0 ) ) ) ) {
*s614.s17<s364*>()->s376() = 0;
return s614;
}
}
return s614;
}
vector<wstring> s1052( { L"else", L"elsif" } );
s637::s637( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s239, s740 )
{
wstring s750 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s18( s750 + L"too few arguments." );
s284.assign( l.begin(), l.end() );
for( s281* p : s284 ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1052 );
}
}
void s637::s780( bool proc )
{
wstring s750 = L"malformed syntax of 'if' statement: ";
s651.push_back( s284[0] );
s652.push_back( s606() );
s652.back().push_back( s284[1] );
if( s284.size() > 2 ) {
size_t n = 2;
while( n < s284.size() ) {
s507 p = s284[n];
s493 pc = s284[n]->s517();
if( pc == s1177 ) {
if( p.s17<s390*>()->s647() == L"elsif" ) {
if( s284.size() < n + 2 )
throw new s18( s750 + L"incomplete clause" );
s651.push_back( s284[++n] );
s652.push_back( s606() );
s652.back().push_back( s284[n] );
}
else if( p.s17<s390*>()->s647() == L"else" ) {
if( s284.size() < n + 1 )
throw new s18( s750 + L"empty clause" );
s652.push_back( s606() );
s652.back().push_back( s284[++n] );
}
else
s652.back().push_back( s284[n] );
}
else
s652.back().push_back( s284[n] );
n++;
}
}
if( !proc ) {
size_t s964 = s652[0].size();
s1175 prevPt = s611[s964]->s370();
for( size_t n = 1; n < s652.size(); ++n ) {
s964 += s652[n].size() + 1;
s1175 tmpPt = s611[s964]->s370();
if( tmpPt && tmpPt != s832->s370() && ( tmpPt != prevPt ) )
throw new s18( L"the return type of 'if' branches doesn't match" );
}
s516 = prevPt;
}
else
s516 = s784->s370();
}
void
s637::s523( const wstring& s350, bool proc )
{
s619::s523( s350, proc );
s780( proc );
s614 = s310->TR().s545( s370(), s616, s350 );
s611.insert( s611.begin(), s614 );
}
s508 s637::s520( s505**, size_t )
{
size_t idx = string::npos;
for( size_t n = 0; n < s651.size(); ++n ) {
if( ( bool )*( s651[n]->s520( 0, 0 ).s17<s505*>() ) )
idx = n;
}
if( idx != string::npos || s652.size() > s651.size() ) {
if( idx == string::npos )
idx = s652.size() - 1;
s508 s721;
s606& el = s652[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s721 = el[n]->s520( 0, 0 );
if( s721->s648() < 0 )
break;
}
return s721;
}
return s384;
}
vector<wstring> s1050( { L"to" } );
s638::s638( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s260, s740 ), s44( NULL )
{
if( l.empty() )
throw new s18( L"Wrong numbers of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
for( s281* p : s284 ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1050 );
}
}
s638::s638( s272* s310 )
: s619( s310, NULL, NULL, s592, s260, NULL ), s44( NULL )
{
s516 = s784->s370();
}
void s638::s523( const wstring& s350, bool proc )
{
s619::s523( s350, proc );
if( s284[0]->s517() == s1177 ) {
if( s284[0].s17<s390*>()->s647() == L"to" ) {
s281* s831 = s284[1];
s493 pc = s831->s517();
if( pc == s497 )
s44 = s831->s520( 0, 0 );
else if( pc == s496 )
s44 = ((s390*)s831)->s396();
else
s44 = (s505*)s831;
s284.erase( s284.begin(), s284.begin() + 2 );
s611.erase( s611.begin()+1, s611.begin() + 3 );
}
}
}
s508 s638::s520( s505** s727, size_t s736 )
{
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s608 + n ) ) {
s493 pc = ( ( s506* )*( s608 + n ) )->s517();
if( pc == s496 )
*( s607 + n + shift ) =
(s505*)( ( s390* )*( s608 + n ) )->s396();
else if( pc == s497 )
*( s607 + n + shift ) =
(s505*)( ( s619* )*( s608 + n ) )->s520( s727, s736 );
}
}
for( size_t n = 1; n < s611.size(); ++n ) {
s508 s160 = s611[n]->s520( s727, s521 );
if( s44 )
s44.dcast<Stream*>()->write( s160 );
else
wcout << s160->to_wstring();
}
return s384;
}
s281* s638::s353()const
{
return new s638( *this );
}
s911::s911( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s928, s740 )
{
if( l.size() != 1 )
throw new s18( s928 + L": wrong number of arguments" );
s612.assign( l.begin(), l.end() );
}
void
s911::s523( const wstring& s350, bool proc )
{
s619::s523( s350, false );
s614 = s612[0]->s519();
}
s508 s911::s520( s505** s744, size_t s521 )
{
return s619::s520( s744, s521 );
}
s281* s911::s353()const
{
return new s911( *this );
}
s987::s987( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s991, s740 ), code( 0 )
{
if( l.size() > 1 )
throw new s18( s991 + L": wrong number of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s828->s370();
}
void
s987::s523( const wstring& s350, bool proc )
{
s619::s523( s350, false );
if( s284[0]->s370() != s828->s370() )
throw new s18( L"The parameter to (exit ) must have Integer type." );
}
s508 s987::s520( s505** s744, size_t s521 )
{
s619::s520( s744, s521 );
code = (int)*s611[1];
throw new s18( (uint32_t) code );
}
s281* s987::s353()const
{
return new s987( *this );
}
s640::s640( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s268, s740 ), s81( s310 )
{
if( l.size() != 1 )
throw new s18( s268 + L": wrong number of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s832->s370();
s81.s12();
}
s640::s640( s272* s310 )
: s619( s310, NULL, NULL, s592, s268, NULL ), s81( s310 )
{
s516 = s832->s370();
s81.s12();
}
void
s640::s523( const wstring& s350, bool proc )
{
s81.s382( s284[0]->to_wstring() );
s614 = s385.s17<s505*>();
s611.push_back( s284[0]->s519() );
}
s508 s640::s520( s505** s744, size_t s521 )
{
s81.s382( s284[0]->s520( s744, s521 )->to_wstring() );
return &s81;
}
s641::s641( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s266, s740 ), s79( s8::s480, s310 ), s650( s310 )
{
if( l.size() < 2 )
throw new s18( s266 + L"(): wrong numbers of arguments" );
s659.s568( s79.s647(), &s650 );
s610.push_back( (s505*)&s650 );
s661.push_back( (s505*)&s650 );
s662.push_back( s79.s647() );
s612.assign( l.begin(), l.end() );
if( ((s588*)l.back())->s309() != s267 )
throw new s18( L"the catch clause must be the last statement in the try block" );
}
s641::s641( s272* s310 )
: s619( s310, NULL, NULL, s592, s266, NULL ), s79( s8::s480, s310 ), s650( s310 )
{
}
void
s641::s523( const wstring& s350, bool proc )
{
s619::s523( s350, proc );
ctch = s612.back().s17<s642*>();
s612.pop_back();
}
s508 s641::s520( s505** s744, size_t s521 )
{
s505* s721 = NULL;
for( size_t n = 0; n < s612.size(); ++n ) {
s721 = s612[n]->s520( s744, s521 );
if( s721->s648() < 0 ) {
if( s721->s648() == s8::s459 ) {
s650.s382( ((s380*)s721)->Msg() );
s721 = ctch->s520( &s721, 1 );
}
break;
}
}
return s721;
}
s642::s642( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s267, s740 )
{
s612.assign( l.begin(), l.end() );
s516 = s784->s370();
}
s642::s642( s272* s310 )
: s619( s310, NULL, NULL, s592, s267, NULL )
{
s516 = s784->s370();
}
s508 s642::s520( s505** s727, size_t s736 )
{
s505* s160;
for( size_t n = 0; n < s612.size(); ++n ) {
s160 = s612[n]->s520( s727, s736 );
if( s160->s648() < 0 ) {
return s160;
}
}
return s384.s17<s505*>();
}
s643::s643( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s270, s740 )
{
wstring s365 = ((s390*)l[0])->s647();
std::vector<s281*> v1( l.begin() + 1, l.end() );
s284.assign( l.begin() + 1, l.end() );
s1039 ast_ = new s273( s365 + L"()" );
s649 = s310->TR().s545( *ast_, s620, s616->s308() );
s614 = s649;
s516 = s649->s370();
}
void
s643::s523( const wstring& s350, bool proc )
{
s727.assign( s284.begin(), s284.end() );
return;
s619::s523( s350, proc );
for( size_t n = 0; n < s284.size(); ++n ) {
s727.push_back( s284[n] );
}
}
s508 s643::s520( s505** s744, size_t s521 )
{
for( size_t n = 0; n < s284.size(); ++n ) {
if( s284[n]->s517() == s496 ) {
s390* rf = s284[n].s17<s390*>();
if( rf->s400().s14() ) {
try {
rf->s523( this );
}
catch( TDException* e ) {
if( e->Category() == s1021 )
s727[n] = s284[n];
}
}
if( rf->s400().s15() )
s727[n] = rf->s396();
}
else if( s284[n]->s517() == s497 )
s727[n] = s284[n].s17<s619*>()->s520( NULL, 0 ).s17<s506*>();
}
s721 = s649->s374( this, s727 );
s721->s523( this );
return s721;
}
bool
s643::s583( const wstring& s712, s390* ref, const wstring& s350 ) const
{
if( (s721.s15() ? s721 : s649)->s583( s712, ref, s350 ))
return true;
return s619::s583( s712, ref, s350 );
}
s803::s803( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s799, s740 )
{
}
void
s803::s523( const wstring& s350, bool proc )
{
}
s508 s803::s520( s505** s744, size_t s521 )
{
return 0;
}
s281* s637::s353() const
{
return new s637( *this );
}
s281* s635::s353() const
{
return new s635( *this );
}
s281* s636::s353()const
{
return new s636( *this );
}
s281* s640::s353()const
{
return new s640( *this );
}
s281* s641::s353()const
{
return new s641( *this );
}
s281* s642::s353()const
{
return new s642( *this );
}
s281* s643::s353()const
{
return new s643( *this );
}
s281* s803::s353()const
{
return new s803( *this );
}
s639::s639( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s265, s740 )
{
if( l.size() != 1 )
throw new s18( s265 + L"(): wrong numbers of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
}
s639::s639( s272* s310 )
: s619( s310, NULL, NULL, s592, s265, NULL )
{
s516 = s784->s370();
}
void s639::s523( const wstring& s585, bool proc )
{
s619::s523( s585, proc );
}
s508 s639::s520( s505** s744, size_t s521 )
{
try {
s508 s160;
if( s284[0]->s517() == s496 )
s160 = s284[0].s17<s390*>()->s396();
else if( s284[0]->s517() == s497 )
s160 = s284[0].s17<s619*>()->s520( NULL, 0 );
else
s160 = s284[0].s17<s505*>();
wstring f = s160->s520( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s507> s1003;
s1039 ast_ = new s273( f );
s512 cs = s619::s1240( *ast_, s310, s616, s308() );
s1003.push_back( cs );
s510 s1001 = s619::s628( cs, s310, s616, this, s308() );
s1001->s523( s308(), true );
s1001->s520( 0, 0 );
}
else {
vector<wstring> l;
s310->callFunc( f, l );
}
}
catch( s18* ) {
return s389;
}
return s388;
}
s281* s639::s353() const
{
return new s639( *this );
}
s272* s645::s997 = NULL;
s645::s645( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s271, s740 )
{
if( l.size() != 1 )
throw new s18( s271 + L"(): wrong number of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
}
s645::s645( s272* s310 )
: s619( s310, NULL, NULL, s592, s271, NULL )
{
s516 = s784->s370();
}
s508 s645::s520( s505** s744, size_t s521 )
{
vector<wstring> s1002;
for( size_t n = 0; n < s284.size(); ++n ) {
s1002.push_back( s284[n]->s520( 0, 0 )->to_wstring() );
}
if( !s997 ) {
s997 = new s272();
s997->s523( true );
}
else
s997->reset();
s997->s217( s1002[0] );
s997->run( s1002 );
return s384;
}
s281* s645::s353()const
{
return new s645( *this );
}
s852::s852( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s822, s740 )
{
if( l.size() != 1 )
throw new s18( s822 + L"(): wrong number of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
}
s508 s852::s520( s505** s744, size_t s521 )
{
s508 s202 = s284[0]->s520( s744, s521 );
s310->s217( s202->to_wstring() );
return s384;
}
s281* s852::s353()const
{
return new s852( *this );
}
s827::s827( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, 
const s273* s740 )
: s619( s310, s620, s621, s592, s882, s740 )
{
s995 = s620->s309();
if( l.size() != 1 )
throw new s18( s882 + L"(): wrong number of arguments" );
s284.assign( l.begin(), l.end() );
s516 = s784->s370();
}
s508 s827::s520( s505** s744, size_t s521 )
{
s281* par = s284[0];
wstring s993;
if( par->s517() == s496 )
s993 = ((s390*)par)->s520( 0, 0 )->to_wstring();
else
s993 = par->s520( 0, 0 )->to_wstring();
try {
s282* ob = ((s282*)s310->s674( s995, s995 ));
ob->s582( s993, s995 );
}
catch( s18* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;
}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;
}
return s384;
}
s281* s827::s353()const
{
return new s827( *this );
}
s829::s829( s272* pass_, const wstring& s818, const vector<wstring>& s788,
std::vector<s507>& types )
{
s797 s834( pass_, pass_, s818 );
s834.s523( pass_ );
vector<s507> s881 = s834.s332();
if( s881.size() != types.size() )
throw new s18( L"The number of record's fields doesn't match to the number of columns: " + s818 );
for( size_t n = 0; n < s881.size(); ++n ) {
if( !s881[n]->s525( types[n].s17< s505*>() ) )
throw new s18( L"The types of record's fields don't match to the types of columns: " + s818 );
s812.insert( make_pair( s788[n], s881[n] ) );
size_t h = s881[n].s17<s505*>()->s334();
rechash = ( rechash << 1 ) ^ h;
}
}
size_t s829::s334() const
{
return rechash;
}
s508 s829::s809( const std::wstring& s79, bool s754 ) const
{
auto it = s812.find( s79 );
if( it == s812.end() ) {
if( s754 )
throw new s18( L"Record field doesn't exist: " + s79, 
(uint32_t)s18::s19::s25 );
else
return s508();
}
return it->second.s17<s505*>();
}
void s829::s941( s797& s160 ) const
{
for( auto r: s812 )
s160.add( r.second );
}
void s829::s572( std::vector<std::wstring>& s160 ) const
{
for( auto r: s812 )
s160.push_back( r.first );
}
bool s829::operator==( const s829* p ) const
{
return rechash == p->rechash;
}
bool s829::operator<( const s829* p ) const
{
return rechash < p->rechash;
}
wstring s829::to_wstring() const
{
wstringstream ss;
s314( &ss, 0 );
return ss.str();
}
void s829::s314( std::wostream* pd, int s205/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"TSDRecord : " << endl;
for( auto it = begin( s812 ); it != end( s812 ); ++it ) {
buf << s4::fill_n_ch( L' ', s205 + s438 ) << it->first << L":" << endl;
it->second->s314( pd, s205 + s438 );
}
}
s871::s871( vector<wstring>& s776, s883 rec )
{
for( size_t n = 0; n < s776.size(); ++n ) {
s507 f = rec->s809( s776[n] ).s17<s506*>();
s867.push_back( f );
}
for( size_t n = 0; n < s776.size(); ++n ) {
size_t h = s867[n].s17<s505*>()->s334();
s855 = ( s855 << 1 ) ^ h;
}
}
size_t s871::s334() const
{
return s855;
}
bool s871::operator==( const s871* p ) const
{
return s855 == p->s855;
}
bool s871::operator<( const s871* p ) const
{
return s855 < p->s855;
}
void s871::s314( std::wostream* pd, int s205/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s867.size(); ++n ) {
s867[n]->s314( pd, s205 + s438 );
}
}
s683::s683( s272* s310, const wstring& s80, const s273* ast_ )
: s354( s310, ast_ )
{
s522 = s80;
s516 = s811.s14() ? 0 : s811->s370();
}
s683::s683( const s683& right, const s273* ast_ )
: s354( right.s310, ast_ )
{
s516 = right.s516;
}
s505* s683::s373( const s273& s740, s282* s616, const std::wstring& s350 )
{
return new s683( s310, L"" );
}
void s683::s523( s282* s965 )
{
}
void s683::s368()
{
s366[L"add-file"] = new s355( L"add-file", &s683::s840, s784->s370() );
s366[L"load-table"] = new s355( L"load-table", &s683::s857, s784->s370() );
s366[L"select"] = new s355( L"select", &s683::s800, s784->s370() );
s366[L"query"] = new s355( L"query", &s683::s820, s784->s370() );
s366[L"erase"] = new s355( L"erase", &s683::s348, s784->s370() );
s366[L"size"] = new s355( L"size", &s683::s343, s828->s370() );
s366[L"through"] = new s355( L"through", &s683::s346, s784->s370() );
s366[L"build-index"] = new s355( L"build-index", &s683::s932, s784->s370() );
}
s505* s683::s374( s282* s616, const std::vector<s281*>& l ) const
{
return new s683( s310, L"" );
}
inline bool
s683::s525( const s505* s526 ) const
{
return ( ((s683*)s526)->s370() == s370() );
}
s281* s683::s353() const
{
return new s683( *this );
}
void s683::s375( s507 p ) const
{
p = new s683( *this );
}
size_t s683::s334() const
{
return (size_t)this;
}
bool s683::operator==( const s505* p ) const
{
return ( this == p );
}
bool s683::operator<( const s505* p ) const
{
return false;
}
#define DR ((s506*)*(s284 + 1))
#define PARN(n)((s506*)*(s284 + n))
#undef s737
#define s737 ((s683*)(s506*)*s284)
inline void s683::s840( s505** s284, size_t s521 )
{
wstring s202 = PARN( 2 )->to_wstring();
( (s683*)DR )->s687( s202 );
}
inline void s683::s857( s505** s284, size_t s521 )
{
s683* dr = ( (s683*)DR );
const wstring& s885 = PARN( 2 )->to_wstring();
wstring s861;
if( s521 == 4 )
s861 = PARN( 3 )->to_wstring();
dr->s758( s885, s861 );
}
inline void s683::s800( s505** s284, size_t s521 )
{
wstring s202 = PARN( 2 )->to_wstring();
( (s683*)DR )->s688( s202 );
}
inline void s683::s820( s505** s284, size_t s521 )
{
wstring s202 = PARN( 2 )->to_wstring();
( (s683*)DR )->s688( s202 );
}
inline void s683::s348( s505** s284, size_t s521 )
{
}
inline void s683::s343( s505** s284, size_t s521 )
{
}
inline void s683::s346( s505** s284, size_t s521 )
{
}
inline void s683::s932( s505** s284, size_t s521 )
{
wstring s934 = PARN( 2 )->to_wstring();
((s683*)DR)->s931( s934 );
}
void s683::s687( const wstring& s202 )
{
vector<s10<s150>> s696;
s1037 s1163( s202 );
s1163.read( s696, s8::s1227 );
for( size_t m = 0; m < s696.size(); m++ ) {
s150* obj = s696[m];
wstring s691 = s4::s55( s273::s312( *obj, s8::s484 ), 
s51 );
if( s691.empty() )
throw new s18( L"Nameless blocks are forbidden." );
vector<pair<wstring, s149>> s151;
obj->s167( s151 );
for( size_t n = 0; n < s151.size(); ++n ) {
if( s151[n].second->s171() != s141 && s151[n].second->s171() != s146 )
throw new s18( L"unrecognized format of field " + s691 +L"::"+s151[n].first );
wstring sobj = s151[n].second->s176();
wstring srel = s151[n].first;
s684.insert( make_pair( s691, make_pair( srel, sobj ) ) );
s685.insert( make_pair( srel, make_pair( s691, sobj ) ) );
s686.insert( make_pair( sobj, make_pair( s691, srel ) ) );
}
}
}
void s683::s688( const std::wstring& q )
{
vector<wstring> qs;
s4::s60( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s684.begin(); it != s684.end(); ++it )
wcout << it->first;
}
}
void s683::select( std::wstring& s934, s508 s688, 
s339::mapped_type::iterator& s952, s339::mapped_type::iterator& s953 )
{
auto it = s949.find( s934 );
if( it == s949.end() )
throw new s18( L"Index doesn't exist: " + s934 );
if( s688.s15() ) {
auto s160 = it->second[s934].equal_range( s688 );
s952 = s160.first;
s953 = s160.second;
}
else {
s952 = it->second[s934].begin();
s953 = it->second[s934].end();
}
}
void s683::s758( const wstring& s885, const wstring& s770 )
{
wstring s788 = s770;
vector<wstring> s875;
vector<wstring> s775;
vector<wstring> s860;
vector<wstring> s886;
if( s788.size() ) {
s4::s60( s788, L",", s875 );
s4::s60( s4::s55( s885, s51 ), L"\n", s860 );
}
else {
s788 = s885.substr( 0, s885.find( L"\n" ) );
s4::s60( s4::s55( s885.substr( s788.size() ), s51 ), L"\n", s860 );
if( s788.back() == '\r' )
s788.pop_back();
s4::s60( s788, L",", s875 );
}
for( size_t n = 0; n < s875.size(); ++n ) {
if( s875[n][0] != L'@' )
s775.push_back( s875[n] );
else {
size_t pl = s875[n].find( L"_" );
if( pl == string::npos )
throw new s18( L"Invalid column name: " + s875[n] );
wstring s79 = s875[n].substr( pl + 1 );
s775.push_back( s79 );
s886.push_back( s79 );
}
}
if( !s886.empty() ) {
s797 s834( s310, s310, s860[0] );
s834.s523( s310 );
vector<s507> types = s834.s332();
for( auto row : s860 ) {
s883 rec = new s829( s310, row, s775, types );
s778 s159 = new s871( s886, rec );
s805.insert( make_pair( s159, rec ) );
}
}
}
void s683::s931( const wstring& s934 )
{
auto it = s949.find( s934 );
if( it != end( s949 ) )
s949.erase( it );
s339& s948 = s949.insert( make_pair( s934, s339() ) ).first->second;
for( auto it: s805 ) {
s508 pd = it.second->s809( s934 );
if( pd.s15() )
s948[s934].insert( make_pair( pd, it.second ) );
}
}
wstring s683::to_wstring() const
{
basic_stringstream<wchar_t> ss;
s314( &ss, 0 );
return ss.str();
}
void s683::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s205 ) << L"TSDBase : " << endl;
for( auto it = begin( s805 ); it != end( s805 ); ++it ) {
it->first->s314( pd, s205 + s438 );
it->second->s314( pd, s205 + s438 );
}
}
struct s922
{
size_t idx;
s922( size_t s947 ): idx( s947 ){}
bool operator()( const s508 l, const s508 r ) const
{
s508 ld = l.s17<s797*>()[idx];
s508 rd = r.s17<s797*>()[idx];
return ld->operator<( (s505*)&(*rd) );
}
};
vector<wstring> s1051( { L"all", L"ALL" } );
s845::s845( s272* s310, s509 s620, s510 s621, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s620, s621, s592, s878, s740 ),
s777( s8::s481, s310 ), s836( new s282( s310, 0, s502 ) )
{
TDException s1064( s8::s1228, s1023, s740 );
s516 = s310->TR().s1158( s872::Cont( { s768->s370(), s791->s370() }) );
if( l.size() < 3 )
throw s1064.s1102( L"too few arguments." );
for( s281* p : l ) {
if( p->s517() == s496 )
( (s390*)p )->s1082( s1051 );
}
s659.s568( s777.s647(), s836.s17<s505*>() );
s610.push_back( s836.s17<s505*>() );
s284.push_back( s836.s17<s505*>() );
s661.push_back( s836.s17<s505*>() );
s662.push_back( s777.s647() );
s507 p = l[0];
if( p->s517() != s496 && p->s517() != s497 )
throw s1064.s1102( L"the database object must be specified by a name or expression." );
db = l[0];
p = l[1];
if( p->s517() != s496 )
throw s1064.s1102( L"the query verb is missed." );
verb = p.s17<s390*>();
if( verb->s647() != L"select" && verb->s647() != L"SELECT")
throw s1064.s1102( L"unrecognized verb." );
p = l[2];
if( p->s517() == s496 || p->s517() == s497 || p->s517() == s1177 )
what = p;
else if( p->s370() == s846->s370() ) {
what = p;
}
else if( p->s370() == s768->s370() )
what = p;
else
throw s1064.s1102( L"the query field(s) must be specified by a name or expression." );
size_t s837 = 3;
s511 rf;
if( l.size() > 3 ) {
p = l[3];
if( p->s517() != s496 )
throw s1064.s1102( L"the 4-th query constituent is unrecognized." );
rf = p.s17<s390*>();
if( rf->s647() == L"required" ||  rf->s647() == L"REQUIRED" ) {
s837 = 4;
if( l.size() < 5 )
throw s1064.s1102( L"the 'required' clause must contain a vector of required fields." );
s795 = (s327*) l[4];
if( s795->s370() != s768->s370() )
throw s1064.s1102( L"the 'required' clause must be a vector of required fields." );
if( l.size() > 5 ) {
p = l[5];
if( p->s517() != s496 )
throw s1064.s1102( L"a modifier (the 6-th query constituent) is unrecognized." );
rf = p.s17<s390*>();
s837 = 6;
}
}
if( rf->s647() == L"where" ||  rf->s647() == L"WHERE" ) {
s837 = 4;
if( l.size() < s837 )
throw s1064.s1102( L"the 'where' clause must contain an expression." );
where = l[s837];
if( where->s517() != s499 )
throw s1064.s1102( L"the 'where' clause must be an expression." );
if( l.size() > s837 + 1 ) {
p = l[++s837];
if( p->s517() != s496 )
throw s1064.s1102( L"a modifier (the 6-th query constituent) is unrecognized." );
rf = p.s17<s390*>();
}
}
}
enum s895 { s957, s959, s958 };
s895 s938 = s957;
while( s837 < l.size() ) {
s507 par_ = l[s837];
s493 pc = par_->s517();
if(	pc == s496 ) {
wstring s1233 = par_.s17<s390*>()->s647();
if( s1233 == L"distinct" || s1233 == L"DISTINCT")
s866.distinct = 1;
else if( s1233 == L"limit" ||  s1233 == L"LIMIT" ) {
if( l.size() < s837 )
throw s1064.s1102( L"the 'limit' clause must contain a value." );
s956 = l[++s837];
}
else if( s1233 == L"sortby" ||  s1233 == L"SORTBY" ) {
if( l.size() < s837 )
throw s1064.s1102( L"the 'sortby' clause must contain a value." );
par_ = l[++s837];
if( par_->s370() != s846->s370() )
throw s1064.s1102( L"the 'sortby' value must be a field name." );
s866.s976 = par_.s17<s378*>()->to_wstring();
s866.s977 = s789::s909::s892;
s938 = s959;
}
else if( s1233 == L"ascending" || s1233 == L"ASCENDING" || s1233 == L"asc" ||
s1233 == L"ASC") {
if( s938 != s959 )
throw s1064.s1102( L"modifier '" + s1233 + L"' is not valid in this position." );
s938 = s957;
s866.s977 = s789::s909::s892;
}
else if( s1233 == L"descending" || s1233 == L"DESCENDING" || s1233 == L"desc" ||
s1233 == L"DESC") {
if( s938 != s959 )
throw s1064.s1102( L"modifier '" + s1233 + L"' is not valid in this position." );
s938 = s957;
s866.s977 = s789::s909::s899;
}
}
s837++;
}
}
void
s845::s523( const wstring& s350, bool proc )
{
TDException s1064( s8::s1011, s1023, past );
s619::s523( s350, proc );
s493 pc = db->s517();
if( pc == s499 ) {
db = s628( db.s17<s588*>(), s310, s616, this, s308() );
db->s523( this );
}
else if( pc == s496 )
db.s17<s390*>()->s523( this );
else
throw s1064.s1102( L"the database must be specified by a name or expression." );
pc = what->s517();
if( pc == s499 ) {
what = s628( what.s17<s588*>(), s310, s616, this, s308() );
what->s523( this );
}
else if( pc == s496 )
what.s17<s390*>()->s523( this );
else if( pc == s495 || pc == s1177 )
(void)0;
else
throw s1064.s1102( L"the query field(s) must be specified by a name or expression." );
if( where ) {
pc = where->s517();
if( pc == s499 ) {
where = s628( where.s17<s588*>(), s310, s616, this, s308() );
where.s17<Transd*>()->s523( s350, false );
s904 s968;
where.s17<Transd*>()->s873( s968 );
}
else
throw s1064.s1102( L"the 'where' clause must be a lambda." );
}
else {
std::vector<s281*> s966;
s966.push_back( s388 );
where = (s506*) new s910( s310, 0, 0, s966, NULL );
where.s17<Transd*>()->s523( s350, false );
}
if( s956.s15() ) {
pc = s956->s517();
if( pc == s499 ) {
s956 = s628( s956.s17<s588*>(), s310, s616, this, s308() );
s956->s523( this );
}
else if( pc == s496 )
s956.s17<s390*>()->s523( this );
else if( s956->s370() != s828->s370() )
throw s1064.s1102( L"the limit must be specified by a number, variable or expression." );
}
}
s508 s845::s520( s505** s727, size_t s736 )
{
s508 s721 = s614;
vector<wstring> s985;
vector<wstring> s986;
s683* base;
size_t s999 = string::npos;
wstring s750 = L"Error during execution of query: ";
TDException s1064( s8::s1012, s1020, past );
assert( db->s517() == s496 );
base = ((s683*)db.s17<s390*>()->s396());
if( s956.s15() ) {
if( s956->s517() == s496 ) {
s866.s956 = (int)*((s364*)s956.s17<s390*>()->s396());
}
else if( s956->s517() == s497 ) {
s866.s956 = (int)*s956->s520( 0, 0 );
}
else
s866.s956 = (int)*s956;
}
std::unordered_set<s883, s920, s919> dom;
s683::s339::mapped_type::iterator beg, end;
s493 pc = what->s517();
if( pc == s496 ) {
throw new s18( L"'select REF' : to be implemented." );
}
else if( pc == s1177 ) {
s511 rf = what.s17<s390*>();
if( rf->s647() == L"all" || rf->s647() == L"ALL" )
(void)0;
else
throw s1064.s1102( L"fields for selection are not recognized" );
}
else if( pc == s495 ) {
if( what->s370() == s768->s370() ) {
const vector<s507>& v = what.s17<s327*>()->s332();
for( auto it: v ) {
wstring s934 = it->to_wstring();
size_t s969 = s4::s91.find( s934[0] );
if( s969 != string::npos )
s934 = s4::s55( s934, wstring( 1, s4::s91[s969] ) );
s985.push_back( s934 );
if( s986.empty() ) {
base->select( s985.back(), s508(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;
}
}
}
}
}
s904 s968;
where.s17<Transd*>()->s873( s968 );
for( size_t n = 0; n < s968.size(); ++n ) {
s986.push_back( s968[n].first );
base->select( s986.back(), s508(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;
}
}
vector<s507> s967;
s967.resize( s986.size() );
s614.s17<s327*>()->clear();
for( auto r : dom ) {
for( size_t n = 0; n < s986.size(); ++n )
s967[n] = r->s809( s986[n] ).s17<s506*>();
where.s17<Transd*>()->s624( s967 );
s508 s160 = where->s520( 0, 0 );// ( (s505**)&s967[0], s967.size() );
if( s160.s15() && (bool)*s160 ) {
s1::s10<s797> s984 = new s797( s310, NULL, L"" );
if( s985.empty() )
r->s941( *s984 );
else {
for( size_t n = 0; n < s985.size(); ++n )
s984->add( r->s809( s985[n] ).s17<s506*>() );
}
s614.s17<s327*>()->add( s984 );
}
}
if( s866.distinct != -1 ) {
vector<s507>& s990 = s614.s17<s327*>()->s332();
for( size_t n = 0; n < s990.size(); ++n ) {
s507 s989 = s990[n];
size_t m = n + 1;
while( m < s990.size() ) {
s507 _el1 = s990[m];
if( *s989.s17<s797*>() == _el1.s17<s505*>() )
s990.erase( s990.begin() + m );
else
m++;
}
}
}
if( s866.s977 != -1 ) {
if( s985.size() && s866.s976.size() ) {
auto it = std::find( s985.begin(), s985.end(), s866.s976 );
if( it != s985.end() )
s999 = std::distance( s985.begin(), it );
else
throw new s18( L"TSD query is incosistent: the sort field is not in the result." );
}
else {
vector<wstring> s994;
(*dom.begin())->s572( s994 );
auto it = std::find( s994.begin(), s994.end(), s866.s976 );
if( it != s994.end() )
s999 = std::distance( s994.begin(), it );
else
throw new s18( L"TSD query is incosistent: the sort field is not in the result." );
}
s1::s10<s988> s992 = new s988;
s992->s998( s999 );
s913 s1000( s992 );
s614.s17<s327*>()->sort( s866.s977 == s789::s899, &s1000 );
}
if( s866.s956 != -1 ) {
s614.s17<s327*>()->s332().resize( s866.s956 );
}
return s721;
}
s281* s845::s353()const
{
return new s845( *this );
}
s272::s272()
: s282( this, 0, s494 ), s740( s236, L"", L"global" ),
s208( L"" ), s211( this )
{	
}
s272::~s272()
{
}
void s272::reset()
{
s659.reset();
s211.s844();
s207.clear();
s740.reset();
}
void s272::s523( bool soft /*=false*/ )
{
s354::s838( this, soft );
s211.s300();
s214[s8::s453] = s386.s17<s505*>();
s214[s8::s452] = s387.s17<s505*>();
s925( s8::s455, s388.s17<s505*>() );
s925( s8::s456, s389.s17<s505*>() );
s925( s8::s900, s384.s17<s505*>() );
}
void s699( const std::wstring& s690, s762& s160 ) 
{
vector<s10<s150>> s696;
s1040 s1163 = new s1037( s690 );
s1163->read( s696, s8::s437 );
for( size_t n = 0; n < s696.size(); n++ ) {
wstring s691 = s273::s312( *s696[n], s8::s484 );
if( s691 == s8::s472 ) {
if( ( *s696[n] ).s163( s8::s486 ) ) {
const vector<s149>& s169 = ( *s696[n] ).s165( s8::s486 )->s174();
for( size_t n = 0; n < s169.size(); n++ )
s160.s697.push_back( s169[n]->s176() );
}
if( ( *s696[n] ).s163( s8::s485 ) )
s160.entry = ( *s696[n] ).s165( s8::s485 )->s933();
}
}
if( s160.s697.empty() )
s160.s697.push_back( s690 );
}
wstring s757( const wstring& s801, const wstring& s804 )
{
if( s3::s764( s804 ) )
return s804;
if( !s3::s764( s801 ) )
throw new s18( L"The root path is not absolute: " + s801 );
if( s804.empty() )
return s801;
wstring path = s804;
wstring root = s801;
s4::s64( path );
s4::s64( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s18( L"The relative path '" + s804 + L"' is incompatible with the root '" + s801 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";
}
else
throw new s18( L"The relative path '" + s804 + L"' is incompatible with the root '" + s801 + L"'." );
}
return root + path;
}
void s272::s221( const std::wstring& s202, const s150& obj )
{
const vector<s149>& s772 = ( obj ).s165( s8::s491 )->s174();
const vector<s149>& packs = ( obj ).s165( s8::s783 )->s174();
vector<wstring> s43;
wstring s786 = s202.substr( 0, s202.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s772.size(); n++ )
s43.push_back( s757( s786, s772[n]->s176() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s176();
if( req.rfind( s8::s476 ) == req.size() - s8::s476.size() ) {
if( std::find( s207.begin(), s207.end(), req ) == s207.end() )
s207.push_back( s757( s786, req ) );
}
else {
vector<wstring> matches;
for( size_t n = 0; n < s43.size(); n++ ) {
wstring match;
if( s3::s33( s43[n], req + s8::s476, match ) )
matches.push_back( match );
}
if( matches.empty() ) {
throw new s18( L"The required library '" + req + L"' is not found." );
}
else if( matches.size() > 1 ) {
wstring s782;
s4::s299( matches, L",\n", s782 );
throw new s18( L"The required library's name '" + req + L"' is ambiguous: \n" + s782 );
}
if( std::find( s207.begin(), s207.end(), matches[0] ) == s207.end() )
s207.push_back( matches[0] );
}
}	
}
void s711( s272* s310, s273& s740, s504& s693,
s654& cl, s653& cnl, s655& al )
{
s273::s285& s741 = s740.s303();
s273::s285::iterator it = s741.begin();
s563 am = s535;
for( ; it != s741.end(); ++it ) {
s493 pc = s501;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s724;
s4::s60( it->first, L" ", s724 );
if( s724.size() > 3 )
throw new s18( L"malformed block name: " + it->first );
wstring s691 = s724[1];
size_t idx = s724.size() - 2;
if( s724[idx] == s8::s470 )
pc = s500;
else if( s724[idx] == s8::s471 )
pc = s501;
else
throw new s18( L"unknown object type: " + s724[0] );
if( s724.size() == 3 ) {
if( s724[0] == s8::s467 )
am = s534;
else if( s724[0] == s8::s469 )
am = s536;
else if( s724[0] != s8::s468 )
throw new s18( L"invalid access mode name: " + it->first );
s691 = s724[2];
}
it->second->s304( s691 );
}
s282* ob = new s282( *it->second, s310, pc, s310, am, cl, cnl, al );
s693.s568( ob->s309(), ob );
}
}
void s272::s217( const wstring& s695 )
{
s762 s679;
s273* s216 = new s273();
wstring s197 = s4::s792( s695 );
if( s817.size() ) {
wstring file = s197.substr( s197.rfind( L"/" ) + 1 );
s197 = s757( s817, s197.substr(0, s197.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s36( s197 );
if( isf == 2 ) {
s4::s64( s197 );
s197 += s8::s479;
if( s817.empty() )
s817 = s695;
}
else if( isf == 1 ) {
if( s817.empty() )
s817 = s197.substr( 0, s197.find_last_of( L"\\/" ) );
}
else
throw new s18( L"cannot find file or directory: " + s695,
(uint32_t)s18::s19::s25 );
s4::s64( s817 );
s699( s197, s679 );
size_t s853 = s207.size();
vector<s10<s150>> s696;
for( size_t n = 0; n < s679.s697.size(); n++ ) {
s696.clear();
wstring s698 = s679.s697[n];
if( s698[0] != L'/' && s698[1] != L':' )
s698 = s817 + s698;
s207.push_back( s698 );
}
for( size_t n = s853; n < s207.size(); ++n ) {
s696.clear();
s1040 s1163 = new s1037( s207[n] );
s1163->read( s696, s8::s437 );
for( size_t m = 0; m < s696.size(); m++ ) {
if( s273::s312( *s696[m], s8::s484 ) == s8::s475 )
s221( s207[n], *s696[m] );
else if( s273::s305( *s696[m], s8::s473 ) == s8::s473 ) {
s696[m]->s166( L"@sourceFile", new s7::s148( L"\"" 
+ s207[n] + 
L"\"" 
), s150::s152::s154 );
s216->s299( *s696[m] );
}
}
}
s215( *s216 );
if( s1119.s1025() )
throw s1026( s1026::s19::s1101 );
s273::s285& s741 = s216->s303();
for( auto it : s741 ) 
s740.s296( it.second );
if( s208.empty() )
s208 = s679.entry;
}
void s272::s215( s273& s216 )
{
s504 s693;
s655 m1;
s653 s700;
s654 s701;
vector<wstring> s702;
s711( this, s216, s693, s701, s700, m1 );
size_t s703 = s700.size();
while( s702.size() < s703 ) {
size_t s704 = s700.size();
for( size_t n = 0; n < s700.size(); ++n ) {
if( s700[n].second.empty() ||
std::find( s702.begin(), s702.end(), s700[n].second )
!= s702.end() ) {
s702.push_back( s700[n].first );
s700.erase( s700.begin() + n-- );
continue;
}
}
if( s704 == s700.size() )
throw new s18( L"unresolved parent class: " + s700[0].second );
}
for( size_t n = 0; n < s702.size(); ++n )
if( s211.s163( s702[n] ) )
throw new s18( L"class name already exists: " + s702[n] );
for( size_t n = 0; n < s702.size(); ++n )
s211.s227( s701[s702[n]], s701[s702[n]]->s372() );
s659.s299( s693 );
for( size_t n = 0; n < s702.size(); ++n ) {
s509 ob = (s282*)s211.get( s702[n], false );
if( ob )
ob->s161( *m1[s702[n]] );
}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s282* ob = (s282*)s693.get( it->first, false );
if( ob && ob->s517() == s501 )
ob->s161( *it->second );
}
s693.s523( this, false );
}
void s272::s219( s150& obj )
{
s273 s216;
s216.s299( obj );
s215( s216 );
}
s505* s272::run( const vector<wstring>& s727 )
{
if( s208.empty() )
s208 = s8::s478 + L"::" + s8::s477;
if( !s727.empty() ) {
wstring  s707, s706;
s705( s208, s706, s707 );
s282* mod = (s282*)s659.get( s706 );
for( size_t n = 0; n < s727.size(); ++n )
mod->s925( L"@" + std::to_wstring( n ), new s378( this, s727[n] ) );
mod->s925( s8::s893, new s364( this, (int)s727.size() ) );
}
vector<wstring> l;
return callFunc( s208, l );
}
s505* s272::callFunc( const wstring& s, vector<wstring>& l )
{
wstring  s707, s706;
s705( s, s706, s707 );
s282* mod = (s282*)s659.get( s706 );
s510 s708 = (s619*)mod->s674( s707, L"::" );
vector<s507> s284;
for( size_t n = 0; n < l.size(); n++ ) {
s1039 ast_ = new s273( l[n] );
s512 cs = s619::s1240( *ast_, this, mod, mod->s308() );
s284.push_back( cs );
}
s708->s624( s284 );
s506* pr = s708->s519();
try {
if( !pr )
s708->s523( L"::", true );
else
s708->s625( L"::" );
}
catch( s18* e ) {
throw e->s32( L"\nwhile linking '" + s708->s309() + L"' function " );
}
return s708->s520();
}
s510 s272::getProc( const std::wstring& s )
{
wstring  s707, s706;
s705( s, s706, s707 );
s282* mod = (s282*)s659.get( s706 );
s510 s708 = (s619*)mod->s674( s707, L"::" );
s508 pr = s708->s519();
if( !pr )
s708->s523( mod->s308(), true );
return s708;
}
void s272::s209( const std::wstring& s695 )
{
wstring s197 = s695;
wstring s694;
int isf = s3::s36( s695 );
if( isf == 2 ) {
s4::s64( s197 );
s197 += s8::s479;
s694 = s695;
}
else if( isf == 1 )
s694 = s197.substr( 0, s197.find_last_of( L"\\/" ) );
else
throw new s18( L"cannot find file or directory: " + s695, 
(uint32_t)s18::s19::s25 );
s4::s64( s694 );
vector<s10<s150>> s696;
s1040 s1163 = new s1037( s197 );
s1163->read( s696, s8::s437 );
s762 s679;
for( size_t n = 0; n < s696.size(); n++ ) {
wstring s691 = s273::s312( *s696[n], s8::s484 );
if( s691 == s8::s472 ) {
s210( *s696[n], s679 );
break;
}
}
s208 = s679.entry;
if( s679.s697.empty() )
s679.s697.push_back( s197 );
for( size_t n = 0; n < s679.s697.size(); n++ ) {
s696.clear();
wstring s698 = s679.s697[n];
if( s698[0] != L'/' && s698[1] != L':' )
s698 = s694 + s698;
s1040 s1163 = new s1037( s698 );
s1163->read( s696, s8::s437 );
for( size_t m = 0; m < s696.size(); m++ )
if( s273::s305( *s696[m], s8::s473 ) == s8::s473 )
s740.s299( *s696[m] );
}
}
void s272::s210( const s7::s150& obj, s762& s160 )
{
const vector<s149>& s169 = obj.s165( s8::s486 )->s174();
for( size_t n = 0; n < s169.size(); n++ )
s160.s697.push_back( s169[n]->s176() );
if( obj.s163( s8::s485 ) )
s160.entry = obj.s165( s8::s485 )->s176();
}
void s272::s227( s505* p, const wstring& s365 )
{
s211.s227( p, s365 );
}
bool s272::s583( const wstring& sym_, s390* ref, const wstring& s350 ) const
{
if( !s282::s583( sym_, ref, s350 ) ) {
if( sym_[0] == L'@' && sym_.substr(1).find_first_not_of(L"0123456789") == string::npos ) {
ref->s398( s672( s8::s900 ), s384 );
ref->s401( (s505*)this );
return true;
}
return false;
}
return true;
}
bool s272::s230( const std::wstring& s, const s505* s1133 ) const
{
s1133 = NULL;
s213::const_iterator it = s214.find( s );
if( it != end( s214 ) ) {
s1133 = it->second;
return true;
}
return false;
}
void s272::s228( const wstring& s79, const wstring& s350,
vector<wstring>& s160 )
{
size_t pl = s79.rfind( L"::" );
s282* mod = NULL;
bool bCl = false;
if( s79.find( L"()" ) == s79.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s710 = s79.substr( 0, pl );
wstring sym = s79.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );
}
mod = (s282*)s659.get( s710 );
if( !mod->s675( sym, s350 ) )
throw new s18( L"Symbol '" + s79 + L"' cannot be imported by '" +
s350 + L"'");
s160.push_back( sym );
}
else {
if( bCl ) {
wstring sym = s79.substr( 0, s79.size() - 2 );
s211.get( sym );
s160.push_back( sym );
}
else {
mod = (s282*) s659.get( s79 );
mod->s671( s350, s160 );
}
}
}
s281* s272::s224( const wstring& s367, s282* s616, const wstring& s350 )
{
return new s349( this, s367, s350 );
}
s619* s272::s222( const std::wstring& funName, 
std::vector<s281*>& s744, s282* s616, s619* s223, const s273* s740 )
{
s619* s721 = NULL;
if( funName == s239 )
s721 = new s637( this, s616, s223, s744, s740 );
else if( funName == s242 )
s721 = new s633( this, s616, s223, s744, s740 );
else if( funName == s252 )
s721 = new s636( this, s616, s223, s744, s740 );
else if( funName == s264 )
s721 = new s315( this, s616, s223, s744, s740 );
else if( funName == s253 )
s721 = new s635( this, s616, s223, s744, s740 );
else if( funName == s260 )
s721 = new s638( this, s616, s223, s744, s740 );
else if( funName == s265 )
s721 = new s639( this, s616, s223, s744, s740 );
else if( funName == s261 )
s721 = new s910( this, s616, s223, s744, s740 );
else if( funName == s928 )
s721 = new s911( this, s616, s223, s744, s740 );
else if( funName == s266 )
s721 = new s641( this, s616, s223, s744, s740 );
else if( funName == s268 )
s721 = new s640( this, s616, s223, s744, s740 );
else if( funName == s267 )
s721 = new s642( this, s616, s223, s744, s740 );
else if( funName == s263 )
s721 = new s318( this, s616, s223, s744, s740 );
else if( funName == s269 )
s721 = new s644( this, s616, s223, s744, s740 );
else if( funName == s270 )
s721 = new s643( this, s616, s223, s744, s740 );
else if( funName == s271 )
s721 = new s645( this, s616, s223, s744, s740 );
else if( funName == s822 )
s721 = new s852( this, s616, s223, s744, s740 );
else if( funName == s882 )
s721 = new s827( this, s616, s223, s744, s740 );
else if( funName == s799 )
s721 = new s803( this, s616, s223, s744, s740 );
else if( funName == s878 )
s721 = new s845( this, s616, s223, s744, s740 );
else if( funName == s808 ) {
s721 = new s877( this, s616, s223, s744, s740 );
}
else if( funName == s929 ) {
if( s211.s1120( s744[0]->s370(), L"is", L"sortable" ) )
s721 = new s912( this, s616, s223, s744, s740 );
}
else if( funName == s991 )
s721 = new s987( this, s616, s223, s744, s740 );
return s721;
}
s281*
s272::s231( const wstring& s79, const wstring& s522, bool s547 /*= true*/ )
{
size_t pl = s79.rfind( L"::" );
s507 s721;
if( pl == string::npos ) {
s721 = (s281*)s211.get( s79, s547 );
if( !s721 ) {
s282* exp = (s282*)s211.get( s8::s474, false );
if( exp )
s721 = exp->s674( s79, s522, s547 );
}
return s721;
}
wstring s710 = s79.substr( 0, pl );
wstring sym = s79.substr( pl + 2 );
return ((s282*)s211.get( s710 ))->s674( sym, s522 );	
}
void* s272::s232( const std::wstring& s288 )
{
s354* s721;
s282* exp = (s282*) s659.get( s8::s474, false );
if( exp )
s721 = (s354*)exp->s674( s288, L"", true );
else
throw new s18( L"no such export variable: " + s288 );
void * pv = s721->addr();
return pv;
}
void s272::s314( std::wostream* pd, int s205 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s205 ) << s288 << L" : " << L"Assembly" << endl;
s211.s314( pd, s205 + s438 );
s659.s314( pd, s205 + s438 );
}
map<int, s272*> handles;
HPROG createAssembly()
{
static int s720 = 0;
s272* p = new s272();
handles[++s720] = p;
p->s523( false );
return s720;
}
void loadProgram( HPROG handle, const wstring& s197 )
{
s272* p = handles[handle];
p->s217( s197 );
}
TDType* getProc( HPROG handle, const std::wstring& s629 )
{
s272* p = handles[handle];
return (TDType*)p->getProc( s629 );
}
void s219( HPROG handle, s7::s150& obj )
{
s272* p = handles[handle];
p->s219( obj );
}
TDType* run( HPROG handle, const vector<wstring>& s727 )
{
return handles[handle]->run( s727 );
}
void* callFunc( HPROG handle, const std::wstring& s80, vector<wstring>& l )
{
s272* p = handles[handle];
return p->callFunc( s80, l );
}
void evaluateExpression( const std::wstring& s80 )
{
}
void* s232( HPROG handle, const std::wstring& s288 )
{
s272* p = handles[handle];
return p->s232( s288 );
}
void* execute( TDType* p )
{
return p->s520().s17<s354*>()->addr();
}
void importSymbol( HPROG handle, const std::wstring& s1233, const std::wstring& symName,
const std::wstring& s350 )
{
s272* p = handles[handle];
s282* ob = (s282*)p->s674( s1233, s350 );
ob->s582( symName, s350 );
}
void importFile( HPROG handle, const std::wstring& s1233, const std::wstring& s46,
const std::wstring& s350 )
{
vector<s1::s10<s7::s150>> s696;
s7::s1037 s1163( s46 );
s1163.read( s696, s8::s437 );
s272* p = handles[handle];
p->s217( s46 );
s282* ob = (s282*)p->s674( s1233, s350 );
for( size_t n = 0; n < s696.size(); n++ ) {
wstring s691 = s273::s312( *s696[n], s8::s484 );
ob->s582( s691, s350 );
}
}
HPROG initShell( const std::wstring& s1233, const std::wstring& modText )
{
s1::s10<s7::s150> ob = new s7::s150(NULL);
size_t pos = 0;
s7::s1037 s1163( L"" );
s1163.s178( modText, pos, ob );
ob->s166( L"name", new s7::s148( s1233 ) );
HPROG prog = createAssembly();
s219( prog, *ob );
return prog;
}
} // namespace transd
