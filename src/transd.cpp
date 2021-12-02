
/*
This is a distributed file for Tourbillon virtual compiler embedding
library.
Copyright (c) 2020-2021 Albert Berger [alberger at gmail com].
All rights reserved.
Redistribution and use of this file in source and binary forms, 
without modification, are permitted for commercial and non-commercial
use.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
/*
	transd.cpp
	----------

	The minimized[1] distributed source file for C++ embeddable
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
uint32_t s16::s27;
std::vector<std::wstring> s1093 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1237(){
s16::s29();}}
using namespace s2;
using s2::s16;
namespace s3 {
time_t s33( const std::wstring& f ){
int err;
#ifndef WIN32
struct stat st;
err = stat( U8( f ).c_str(), &st );
#else
struct _stat st;
err = _wstat( f.c_str(), &st );
#endif
if( err )
throw new s16( L"cannot get mtime of: " + f, 
(uint32_t)s16::s17::s23 );
return st.st_mtime;}
uint8_t s34( const std::wstring& f ){
int err;
#ifndef WIN32
struct stat st;
err = stat( U8( f ).c_str(), &st );
#else
struct _stati64 st;
err = _wstat64( f.c_str(), &st );
#endif
if( err )
throw new s16( L"file system object does not exist: " + f,
(uint32_t)s16::s17::s23 );
if( st.st_mode & S_IFREG )
return 1;
else if( st.st_mode & S_IFDIR )
return 2;
return 0;}
bool s36( const wstring& s214 ){
try {
s34( s214 );}
catch( s16& ) {
return false;}
return true;}
bool s35( const wstring& s214 ){
try {
if( s34( s214 ) != 1 )
throw new s16( L"Cannot find data file: " + s214,
(uint32_t)s16::s17::s23 );}
catch( s16* e ) { // file don't exist
if( e->which() != (uint32_t)s16::s17::s23 )
throw;
return false;}
return true;}
} // namespace s3
#ifdef __LINUX__
using namespace std;
using namespace s2;
using namespace s5;
namespace s3 {
wstring s37(){
char buf[1024];
memset( buf, 0, 1024 );
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );}
wstring s38(){
wstring s717 = s37();
size_t pl = s717.rfind( '/' );
if( pl == string::npos )
s717 = L"";
else
s717 = s717.substr( 0, pl );
return s717;}
wstring s2063(){
char buf[2000];
memset( buf, 0, 2000 );
getcwd( buf, 2000 );
return wstring( conv.from_bytes( buf ) );}
bool s31( const wstring& s46, const wstring& s547, wstring& s156 ){
struct dirent *entry;
DIR *dp;
wregex rg( s547 );
bool s717 = false;
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s731 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s731,
(uint32_t)s16::s17::s22 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s156 = s46 + conv.from_bytes( entry->d_name );
s717 = true;
break;}}
closedir( dp );
return s717;}
void s32( const wstring& s46, const wstring& s547, vector<wstring>& s40, vector<wstring>& s41 ){
struct dirent *entry;
DIR *dp;
wregex rg( s547 );
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s731 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s731,
(uint32_t)s16::s17::s22 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
wstring item = conv.from_bytes( entry->d_name );
wstring s = s46 + item;
uint8_t is = s34( s );
if( is == 1 )
s40.push_back( item );
else if( is == 2 )
s41.push_back( item );}}
closedir( dp );}
bool s759( const std::wstring& f ){
if( f.size() && f[0] == '/' )
return true;
return false;}
} // namespace s3
#endif // __LINUX__
#ifdef WIN32
using namespace std;
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
namespace s3 {
wstring s37(){
wchar_t s42[1024];
DWORD length = GetModuleFileNameW( NULL, s42, 1024 );
return s42;}
wstring s38(){
wchar_t s42[1024];
DWORD length = GetModuleFileNameW( NULL, s42, 1024 );
PathRemoveFileSpecW( s42 );
return s42;}
wstring s2063(){
wchar_t buf[2000];
memset( buf, 0, 4000 );
_wgetcwd( buf, 2000 );
return wstring( buf );}
bool s31( const wstring& _dir, const wstring& s547, wstring& s156 ){
HANDLE s48;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s547.c_str() );
bool s717 = false;
wstring s46 = _dir;
if( s46.back() != L'/' && s46.back() != L'\\' )
s46 += L'\\';
if( ( s48 = FindFirstFileW( ( s46 + L"*" ).c_str(), &s43 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s48, &s43 ) ) {
s44 = s43.cFileName;
s45 = s46 + s44;
if( regex_match( s44, rg ) ) {
s156 = s45;
s717 = true;
break;}}
return s717;}
void s32( const wstring& _dir, const wstring& s547, vector<wstring>& s40, vector<wstring>& s41 ){
HANDLE s48;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s547.c_str() );
wstring s46 = _dir;
if( s46.back() != L'/' && s46.back() != L'\\' )
s46 += L'\\';
if( ( s48 = FindFirstFileW( ( s46 + L"*" ).c_str(), &s43 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s48, &s43 ) ) {
s44 = s43.cFileName;
s45 = s46 + s44;
if( regex_match( s44, rg ) ) {
uint8_t is = s34( s45 );
if( is == 1 )
s40.push_back( s44 );
else if( is == 2 )
s41.push_back( s44 );}}}
bool s759( const std::wstring& f ){
if( f.size() && f[1] == ':' )
return true;
return false;}
} // namespace s3
#endif // WIN32
namespace s4 {
wstring s89 = L"\"`'";
wstring s49 = L"\n\r\t ";
string s50 = "\n\r\t ";
wstring s51 = L"";
wstring digits = L"0123456789";
void s55( const wstring& s, size_t s66, wchar_t left, wchar_t right,
size_t& start, size_t& end, bool s970/*=false*/ )
{
end = string::npos;
start = string::npos;
int s67 = 0;
wchar_t s957 = 0;
bool esc = false;
for( size_t n = s66; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s957 || !s970 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s67++;}
else if( c == right ) {
if( start == string::npos )
return; // s889
if( --s67 == 0 ) {
end = n;
return;}}
else if( s970 && ( c == L'\'' || c == L'\"' ) ) {
s957 = c;}}
else if( s957 && c == s957 && !esc ) {
s957 = 0;}
else if( c == L'\\' ) {
esc = !esc;}
else
esc = false;}}
void s935( const wstring& s, size_t s66, wchar_t left, wchar_t right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s66 );
if( start == string::npos || start == s.size() - 1 )
return;
int s67 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s67;
continue;}
if( s[n] == right )
--s67;
if( s67 == 0 ) {
end = n;
return;}}}
void s56( const wstring& s, size_t s66, wchar_t c, size_t& start, size_t& end ){
end = string::npos;
start = s.find( c, s66 );
if( start == string::npos || start == s.size() - 1 )
return;
bool s925 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s925 = !s925;
if( s[n] == c && !s925 ) {
end = n;
return;}
if( s[n] != L'\\' )
s925 = false;}}
void s1098( const std::wstring& s, size_t& s66, const std::wstring& s2061 ){
size_t s2059 = s66, s2060;
wstring s1509 = s2061 + L"\"";
s66 = string::npos;
bool s2062 = false;
while( true ) {
s2060 = s2059;
s2059 = s.find_first_of( s1509, s2059 );
if( s2059 == string::npos ) {
if( s2062 )
throw new s2::s16( L"no closing parenthesis: " + s.substr(s2060, 20) );
return;}
if( s[s2059] == L'\"' ) {
if( ! (s2059 && s[s2059-1] == '\\' ))
s2062 = !s2062;}
else{
if( !s2062 ) {
s66 = s2059;
return;}}
++s2059;}
return;
size_t pl = s.find_first_of( s1509, s66 );
if( pl == s66 )
return;
size_t start = s66;
s66 = string::npos;
while( pl < s.size() ) {
if( s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl++;
if( pl < s.size() )
pl = s.find_first_of( s1509, pl );}
else {
s66 = pl;
return;}}}
void s1493( const std::wstring& s, size_t& s66, const std::wstring& s1205 ){
size_t pl = s.find( s1205, s66 );
if( pl == s66 )
return;
size_t start = s66;
s66 = string::npos;
while( pl < s.size() ) {
if( s1205.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1205.size();
if( pl < s.size() )
pl = s.find( s1205, pl );}
else {
s66 = pl;
return;}}}
size_t count( const std::wstring& s78, const std::wstring& s1205, size_t start, size_t end,
bool s970 ){
size_t s717 = 0;
size_t pl = s78.find( s1205, start );
while( pl < s78.size() && pl <= end) {
if( s970 && pl && s78[pl-1] == '\\' ) {
++pl;}
else {
++s717;
pl += s1205.size();}
if( pl < s78.size() - 1 ) 
pl = s78.find( s1205, pl );}
return s717;}
int s57( const wstring& s78, wchar_t s73, size_t& pos ){
size_t s71 = s78.find( s73, pos );
if( s71 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s53( s78.substr( pos, s71 - pos ), L" " );
int s717 = stoi( s );
pos = s78.find_first_not_of( s49 + s73, s71 );
return s717;}
bool s63( const wchar_t *str, long *s363, wchar_t **end /*= NULL*/ )
{
wchar_t *s68;
bool s717 = true;
errno = 0;
*s363 = std::wcstol( str, &s68, 0 );
if( s68 == str || ( !end && *s68 != '\0' ) ||
( ( *s363 == LONG_MIN || *s363 == LONG_MAX ) && errno == ERANGE ) )
s717 = false;
if( end )
*end = s68;
return s717;}
bool s1718( const wchar_t *str, long long *s363, wchar_t **end /*= NULL*/ )
{
wchar_t *s68;
bool s717 = true;
errno = 0;
*s363 = std::wcstoll( str, &s68, 0 );
if( s68 == str || ( !end && *s68 != '\0' ) ||
( ( *s363 == LLONG_MIN || *s363 == LLONG_MAX ) && errno == ERANGE ) )
s717 = false;
if( end )
*end = s68;
return s717;}
bool s1719( const wchar_t *str, unsigned long long *s363, wchar_t **end /*= NULL*/ )
{
wchar_t *s68;
bool s717 = true;
errno = 0;
*s363 = std::wcstoull( str, &s68, 0 );
if( s68 == str || ( !end && *s68 != '\0' ) ||
( ( *s363 == ULLONG_MAX ) && errno == ERANGE ) )
s717 = false;
if( end )
*end = s68;
return s717;}
bool s64( const wchar_t *str, double *s363, wchar_t **end /*= NULL*/ )
{
wchar_t *s68;
bool s717 = true;
errno = 0;
*s363 = std::wcstod( str, &s68 );
if( s68 == str || ( !end && *s68 != '\0' ) ||
( ( *s363 == HUGE_VAL || *s363 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s717 = false;
if( end )
*end = s68;
return s717;}
void s958( const wstring& s78, vector<wstring>& s156 ){
size_t s69 = s78.find_first_not_of( s49 );
size_t s713, s714;
while( s69 != string::npos ) {
wchar_t c = s78[s69];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s56( s78, s69, c, s713, s714 );
if( s714 == string::npos )
throw s2::s16( L"Quotes don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
arg = s78.substr( s69, s714 - s69 + 1 );
s69 = s78.find_first_not_of( s49, ++s714 );}
else {
s714 = s78.find_first_of( s49 );
arg = s78.substr( s69, s714 - s69 );
s69 = s714;}
s156.push_back( arg );}}
std::wstring s2007( const std::wstring& s78, wchar_t c ){
size_t pl = s78.find( c ), s2029 = 0, s2000 = 0, s2023;
if( pl == string::npos )
return s78;
wstring s717( s78.size() + 100, L'\0' );
while( pl != string::npos ) { 
s2023 = pl - s2029;
if( s717.size() < s2000 + s2023 + 2 )
s717.resize( (std::max)((size_t)(s717.size()*1.1), s717.size()+100) );
memcpy( (void*)(s717.c_str() + s2000), s78.c_str() + s2029, s2023 * sizeof(wchar_t) );
s717[s2000 + s2023] = L'\\';
s717[s2000 + s2023 + 1] = s78[pl];
s2000 = s2000 + s2023 + 2;
s2029 = pl + 1;
pl = s78.find( c, pl + 1 );}
s2023 = s78.size() - s2029;
memcpy( (void*)(s717.c_str() + s2000), s78.c_str() + s2029, s2023 * sizeof(wchar_t) );
s717.resize( s2000 + s2023/* + 1*/ );
return s717;}
void s58( const wstring& s, const wstring& s73, vector<wstring>& s156, bool clr,
bool s970 ){
size_t s69 = 0, s70 = 0;
while( s70 != wstring::npos && s69 < s.size()) {
if( s970 ) {
s70 = s69;
s4::s1098( s, s70, s73 );}
else
s70 = s.find( s73, s69 );
wstring seg;
if( clr )
seg = s53( s.substr( s69, s70 - s69 ), s49 );
else
seg = s.substr( s69, s70 - s69 );
s69 = s70 + s73.size();
if( seg.size() )
s156.push_back( seg );
if( s70 != string::npos && s156.capacity() <= s156.size() )
s156.reserve( s156.size() * ( s.size() / s69 ) + 100 );
}}
void s295( const vector<wstring>& v, const wstring& s73, wstring& s156 ){
if( v.empty() )
return;
s156 = v[0];
for( size_t n = 1; n < v.size(); ++n )
s156 += (s73 + v[n]);}
wstring s72( const wstring& s78, size_t& pos ){
size_t pl = s78.find( L'\n', pos );
wstring line = s53( s78.substr( pos, pl - pos ), s49 );
pos = pl == string::npos ? pl : pl + 1;
return line;}
void s59( const wstring& s78, const wstring& s73, 
pair<wstring, wstring>& pr, size_t& pos ){
size_t pl = s78.find( L'\n', pos );
wstring line = s53( s78.substr( pos, pl - pos ), s49 );
pos = pl == string::npos ? pl : pl + 1;
pl = line.find( s73 );
if( pl == string::npos ) 
throw s2::s16( L"invalid pair syntax: " + line );
wstring s77 = s53( line.substr( 0, pl ), s49 );
wstring s363 = s53( line.substr( pl + s73.size() ), s49 );
pr.first = s77;
pr.second = s363;}
void s60( const wstring& s78, const wstring& s73, vector<pair<wstring, wstring>>& v ){
vector<wstring> s74;
s58( s53( s78, s49 ), L"\n", s74 );
for( size_t n = 0; n < s74.size(); ++n ) {
size_t pl = s74[n].find( s73 );
wstring s77 = s53( s74[n].substr( 0, pl ), s49 );
wstring s363 = s53( s74[n].substr( pl + s73.size() ), s49 );
v.push_back( make_pair( s77, s363 ) );}}
wstring s52( const std::wstring& l, const std::wstring& s, const std::wstring& r ){
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s717 = s.substr( pl );
return s717.substr( 0, s717.find_last_not_of( r ) + 1 );}
wstring s53( const std::wstring& s, const std::wstring& c ){
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s717 = s.substr( pl );
return s717.substr( 0, s717.find_last_not_of( c ) + 1 );}
wstring s61( const wstring& s78 ){
if( s78[0] != L'{' )
return s78;
size_t s75, s76;
s55( s78, 0, L'{', L'}', s75, s76 );
wstring s80 = s78.substr( s75 + 1, s76 - s75 - 1 );
vector<wstring> s81;
s58( s53( s80, L" " ), L"|", s81 );
#ifdef WIN32	
return s81[0] + s78.substr( s76 + 1 );
#else
return s81[1] + s78.substr( s76 + 1 );
#endif	
}
bool s54( const std::wstring& s, const std::wstring& ss ){
if( s.substr( s.size() - ss.size() ) == ss )
return true;
return false;}
void s62( wstring& s46 ){
#ifdef WIN32
if( s46.back() != L'/' &&
s46.back() != L'\\' ) {
size_t pl = s46.find( L"\\" );
size_t pl1 = s46.find( L"/" );
if( pl != string::npos && pl > pl1 )
s46 += L"\\";
else
s46 += L"/";
}
#else
if( s46.back() != L'/' )
s46 += L"/";
#endif
}
wstring s787( wstring path ){
size_t pl = path.find( L"\\" );
while( pl != string::npos ) {
path = path.replace( pl, 1, L"/" );
pl = path.find( L"\\" );}
if( path.front() == L'\'' || path.front() == L'"' ) {
if( path.back() != path.front() )
throw new s2::s16( L"opening and closing quotes don't match" );
path = path.substr( 1, path.size() - 2 );}
pl = path.find( L"/../" );
while( pl != string::npos ) {
size_t pl1 = path.rfind( L"/", pl - 1 );
path.erase( pl1, pl - pl1 + 3 );
pl = path.find( L"/../" );
}
return path;}
void s65( const std::wstring& s79 ){}
void s55( const string& s, size_t s66, char left, char right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s66 );
if( start == string::npos || start == s.size() - 1 )
return;
int s67 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s67;
continue;}
if( s[n] == right )
--s67;
if( s67 == 0 ) {
end = n;
return;}}}
int s57( const string& s78, char s73, size_t& pos ){
size_t s71 = s78.find( s73, pos );
if( s71 == string::npos )
throw invalid_argument( "separator not found" );
string s = s53( s78.substr( pos, s71 - pos ), " " );
int s717 = stoi( s );
pos = s78.find_first_not_of( s50 + s73, s71 );
return s717;}
void s58( const string& s, const string& s73, vector<string>& s156 ){
size_t s69 = 0, s70 = 0;
while( s70 != string::npos ) {
s70 = s.find( s73, s69 );
string seg = s53( s.substr( s69, s70 - s69 ), s50 );
s69 = s70 + s73.size();
s156.push_back( seg );}}
void s60( const string& s78, vector<pair<string, string>>& v ){
vector<string> s74;
s58( s53( s78, s50 ), "\n", s74 );
for( size_t n = 0; n < s74.size(); ++n ) {
size_t pl = s74[n].find( ':' );
string s77 = s53( s74[n].substr( 0, pl ), s50 );
string s363 = s53( s74[n].substr( pl + 1 ), s50 );
v.push_back( make_pair( s77, s363 ) );}}
string s52( const std::string& l, const std::string& s, const std::string& r ){
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s717 = s.substr( pl );
return s717.substr( 0, s717.find_last_not_of( r ) + 1 );}
string s53( const std::string& s, const std::string& c ){
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s717 = s.substr( pl );
return s717.substr( 0, s717.find_last_not_of( c ) + 1 );}
string s61( const string& s78 ){
if( s78[0] != '{' )
return s78;
size_t s75, s76;
s55( s78, 0, '{', '}', s75, s76 );
string s80 = s78.substr( s75 + 1, s76 - s75 - 1 );
vector<string> s81;
s58( s53( s80, " " ), "|", s81 );
#ifdef WIN32	
return s81[0] + s78.substr( s76 + 1 );
#else
return s81[1] + s78.substr( s76 + 1 );
#endif	
}
void s82( wstring& s78, vector<wstring>& s1220, map<size_t, size_t>& s1144 ){
size_t pos = 0;
wchar_t s83 = 0;
bool s1305 = false;
wchar_t s84 = 0;
bool s85 = false;
bool s86 = false;
size_t s87 = string::npos;
bool s88 = false;
bool s1074 = false;
wstring s89 = L"`'\"";
s1220.reserve( 1000 );
size_t s1138 = 1;
bool s1065 = false;
while( pos < s78.size() ) {
wchar_t c = s78[pos];
if( c == '\r' ) {
s78.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1305 = !s1305;}
else if( s83 ) {
if( c == s83 && !s1305 /*s84 != '\\'*/ )
s83 = 0;}
else if( s89.find( c ) != string::npos ) {
if( !s85 ) {
s83 = c;}}
else if( c == '*' ) {
if( !s85 && s84 == '/' ) {
s85 = true;
s86 = true;
s87 = pos - 1;
if( pos > 1 && s78[pos - 2] != '\n')
s1144[pos - 2] = s1138;}}
else if( c == '/' ) {
if( !s85 && s84 == '/' ) {
s87 = pos - 1;
s85 = true;
s86 = false;
if( pos > 1 && s78[pos - 2] != '\n')
s1144[pos - 2] = s1138;}
else if( s86 && s84 == '*' ) {
s88 = true;
if( s78[pos+1] == '\n' ){
s1065 = true;}}}
else if( c == '\n' ) {
s1065 = true;
if( s85 ) {
if( !s86 ) {
s88 = true;}
else {
if( !s1074 ) {
s1074 = true;}}}
else {
if( pos && s78[pos-1] != '\n' ) {
s1144[pos - 1] = s1138;}}}
if( c != L'\\' )
s1305 = false;
if( s1065 ) {
size_t pl = s78.rfind( '\n', pos - 1 );
size_t m = (s78[pos] == '\n');
if( pl == string::npos )
s1220.push_back( s78.substr( 0, pos ) );
else
s1220.push_back( s78.substr( pl + 1, pos - pl - m ) );
s1065 = false;
s1138++;}
if( s88 ) {
int m = 0;
if( s86 )
m = 1;
if(	s78[pos] == '\n' && ( !s87 || s78[s87 -1] == '\n' ) )
m = 1;
if( m ) {
s78.replace( s87, pos - s87 + m, L"");
pos = s87 - 1;}
else {
s78.replace( s87, pos - s87 + m, L" ");
pos = s87 + 1;}
s87 = string::npos;
s85 = false;
s1074 = false;
s86 = false;
s88 = false;
s84 = 0;}
s84 = c;
pos++;}
if( s85 ) {
auto it = end(s1144);
if( s1144.size() ) it--; 
size_t ln = (it == end(s1144) ? 0 : it->second);
throw new s2::s16( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
}//namespace s4
namespace s5 {
std::locale locloc;
std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> conv;}
#ifdef WIN32
#include <conio.h>
#endif
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace s4;
namespace consutils {
uint32_t s17::s91;
void s17::s29(){
s91 = s16::s28();}
void s1233(){
s17::s29();}
bool s101( const wstring& s95 ){
wcout << s95 << L" [Y]es | [n]o :";
wstring ans;
getline( wcin, ans );
if( ans.size() && s53( ans, L" " ).empty() )
throw new s16( s17::s92() );
if( ans.size() && ( ans[0] == L'N' || ans[0] == L'n' ) )
return false;
return true;}
int s102( const wstring& s95, const vector<wstring>& s96 ){
int s717;
while( true ) {
s133();
wcout << s95 << endl << endl;
for( size_t i = 0; i < s96.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s96[i] << endl;}
s717 = s106( L"Please, enter your answer's number: " );
if( s717 < 0 || s717 > ( int ) s96.size() ) {
wcout << "No variant with such number." << endl;
s98();
continue;}
break;}
return s717;}
wstring s103( const wstring& s95, bool s97 ){
if( !s95.empty() )
wcout << s95;
wstring s363;
if( s97 )
s100( false );
getline( wcin, s363 );
if( s97 )
s100( true );
return s363;}
wstring s104( const wstring& s95, bool s97 ){
wcout << s95;
int s120 = 0;
bool s612 = true;
wstring s121 = s95;
size_t s1227 = s121.size();
size_t s122 = s1227;
while( s612 ) {
s120 = _getch();
switch( s120 ) {
case s113:
if( s1227 > s122 ) {
wcout << '\r' << s121.substr( 0, --s1227 );}
break;
case s114:
if( s1227 < s121.size() )
wcout << s121[s1227++];
break;
case s111:
case s112:
continue;
case s117:
if( ( s1227 > s122 ) && s121.size() ) {
s121.erase( --s1227, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}
break;
case s118:
if( s1227 < s121.size() ) {
s121.erase( s1227, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}
break;
case s116:
s612 = false;
break;
case s119:
break;
default:
if( s1227 < s121.size() )
s121.insert( s1227, 1, s120 );
else
s121 += s120;
++s1227;
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}}
return s121;}
wstring getStringValHist( const wstring& s95, const vector<wstring>& s105 ){
wcout << s95;// << endl;
int s120 = 0;
size_t s716 = s105.size();
bool s612 = true;
wstring s121 = s95;
size_t s2067 = s95.size();
size_t s1227 = s2067;
while( s612 ) {
s120 = _getch();
#ifdef __LINUX__
if( s120 == 27 ) {
_getch();
s120 = _getch();
if( s120 == L'A' ) s120 = s111;
else if( s120 == L'B' ) s120 = s112;
else if( s120 == L'C' ) s120 = s114;
else if( s120 == L'D' ) s120 = s113;}
else if( s120 == 10 )
s120 = 13;
else if( s120 == 127 )
s120 = 8;
#else			
if( s120 == 224 ) {
s120 = _getch();
if( s120 == L'H' ) s120 = s111;
else if( s120 == L'P' ) s120 = s112;
else if( s120 == L'M' ) s120 = s114;
else if( s120 == L'K' ) s120 = s113;}
else if( s120 == 0 ) {
s120 = _getch();
if( s120 == 83 ) s120 = s118; // S
else if( s120 == 71 ) s120 = s1732; // G
else if( s120 == 79 ) s120 = s1731; // O
}
#endif			
switch( s120 ) {
case s113:
if( s1227 > s2067 ) {
wcout << '\r' << s121.substr( 0, --s1227 );}
break;
case s114:
if( s1227 < s121.size() )
wcout << s95 << s121[s1227++];
break;
case s111:
if( s716 > 0 ) {
if( s716 < s105.size() )
wcout << '\r' << wstring( s121.size(), L' ' );
s121 = s95 + s105[--s716];
wcout << '\r' << s121;
s1227 = s121.size();}
break;
case s112:
if( !s105.empty() && s716 < s105.size() - 1 ) {
wcout << '\r' << wstring( s121.size(), L' ' );
s121 = s95 + s105[++s716];
wcout << '\r' << s121;
s1227 = s121.size();}
break;
case s117:
if( s1227 > s2067 && s121.size() > s2067 ) {
s121.erase( --s1227, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}
break;
case s118:
if( s1227 < s121.size() ) {
s121.erase( s1227, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}
break;
case s1732:
if( s1227 > 0 ) {
wcout << '\r' << s95;
s1227 = s2067;}
break;
case s1731:
if( s1227 < s121.size() ) {
wcout << '\r' << s121;
s1227 = s121.size();}
break;
case s116:
s612 = false;
break;
case s119:
break;
default:
if( s1227 < s121.size() )
s121.insert( s1227, 1, s120 );
else
s121 += s120;
++s1227;
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1227 );}}
return s121.substr( s2067 );}
int s106( const std::wstring & s95 ){
int s717;
while( true ) {
wcout << s95;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s717 = stoi( inp );}
catch( std::invalid_argument& ) {
continue;}
break;}
return s717;}
void s93( const wstring& header, const std::vector<std::wstring>& s94 ){
s133();
wcout << endl << "  " << header << endl << fill_n_ch( L'-', header.size() + 4 )
<< endl << endl;
if( s94.size() ) {
wcout << L"Keyboard shortcuts: " << endl;
for( size_t n = 0; n < s94.size(); n += 2 )
wcout << setw( 10 ) << left << s94[n] << L" - " << s94[n + 1] << endl;}
wcout << endl;}
size_t s107( const std::wstring & s95 ){
wcout << s95 << endl << endl <<
L"Please, enter the number of menu item: " << endl <<
L"1 - Skip this item" << endl << L"2 - Overwrite this item" << endl <<
L"3 - Skip all already existing items" << endl <<
L"4 - Overwrite all already existing items" << endl << "5 or any key - Cancel operation" << endl;
wstring s132;
getline( wcin, s132 );
int i;
try { i = stoi( s132 ); }
catch( std::invalid_argument* ) {
i = 5;}
if( i < 1 || i > 5 )
i = 5;
return i;}
void s109( const vector<wstring>& v, vector<wstring>& s156, size_t w, size_t h ){
size_t s123 = v.size() / h + 1;
size_t s124 = v.size() / s123;
vector<size_t> s125;
size_t s716 = 0;
for( auto it : v ) {
if( s716 == 0 )
s125.push_back( 0 );
if( it.size() > s125.back() )
s125.back() = it.size();
if( ++s716 == s124 )
s716 = 0;}
size_t s126 = 0, s127 = 0;
size_t s128 = 0;
for( size_t n = 0; n < s123; ++n ) {
s128 += s125[n] + 5;
if( n == s123 - 1 || s128 + s125[n + 1] + 5 > w ) {
size_t s129 = n - s126 + 1;
s128 = 0;
if( s126 ) {
if( s103( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}
for( size_t m = s127;
m < min( s127 + s124, v.size() );	++m ) {
wostringstream ss;
for( size_t k = 0;
k < min( s129, ( v.size() - m - 1 ) / s124 + 1 ); ++k )
ss << setw( 3 ) << right << m + s124 * k + 1 << L". " << setw( s125[s126 + k] ) <<
left << v[m + s124 * k];
s156.push_back( ss.str() );}
s127 += s129 * s124;
s126 = n + 1;}}}
int s110( const std::vector<std::wstring>& v ){
int w, h;
s108( w, h );
std::vector<std::wstring> rows;
s109( v, rows, w, h );
size_t s130 = 0;
for( auto it : rows ) {
wcout << it << endl;
if( ++s130 % h == 0 ) {
if( s103( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}}
int s131;
while( true ) {
wcout << endl;
wstring s132 = s103( L"Enter the item's number or <Space> to cancel..." );
if( s132 == L" " )
return -1;
try { s131 = stoi( s132 ); }
catch( std::invalid_argument& ) {
continue;}
break;}
if( s131 > (int)v.size() ) {
wcout << L"No record with such number." << endl;
return -1;}
return s131;}
} // namespace consutils
#ifdef __LINUX__
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
namespace consutils {
wstring s37(){
char buf[1024];
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );}
void s98(){
wcout << endl << L"Press 'Return' to continue..." << endl;
std::system( "read" );}
void s133( int s74 ){
std::system( "clear" );
for( int i = 0; i < s74; ++i )
wcout << endl;}
void s100( bool b ){
struct termios tty;
tcgetattr( STDIN_FILENO, &tty );
if( !b )
tty.c_lflag &= ~ECHO;
else
tty.c_lflag |= ECHO;
(void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );}
void s108( int& w, int& h ){
struct winsize ws;
ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );
h = ws.ws_row;
w = ws.ws_col;}
char _getch(){
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
buf[0] = 8;}
else if( buf[0] == 27 && buf[1] == 91 ) {
if( buf[3] == 0 ) {
if( buf[2] == 65 ) buf[0] = s111;
if( buf[2] == 66 ) buf[0] = s112;
if( buf[2] == 67 ) buf[0] = s114;
if( buf[2] == 68 ) buf[0] = s113;}
else if( buf[2] == 51 && buf[3] == 126 )
buf[0] = 83;		
}*/
return buf;//buf[0];
}
} // namespace consutils
#endif // __LINUX__
#ifdef WIN32
#include <iostream>
namespace consutils {
void s98(){
wcout << endl;
std::system( "pause" );}
void s133( int s74 ){
std::system( "CLS" );
for( int i = 0; i < s74; ++i )
wcout << endl;}
void s100( bool b ){
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode;
GetConsoleMode( hStdin, &mode );
if( !b )
mode &= ~ENABLE_ECHO_INPUT;
else
mode |= ENABLE_ECHO_INPUT;
SetConsoleMode( hStdin, mode );}
void s108( int& w, int& h ){
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;}
} // namespace consutils
#endif // WIN32
using namespace s1;
using namespace s5;
namespace s6{
wstring s189 = L"-.0123456789";
wstring s1712 = L"0123456789";
wstring s1713 = L".0123456789";
wstring s190 = L" ,]}\t\r\n";
s1873 s1935;
thread_local std::list<bool> s1948;
void s1876( const wstring& dd, const wstring& fs, bool ab, bool rb, bool sb ){
s1935 = s1873( dd, fs, ab, rb, sb );}
void s1876( const s1873& cnf ){
s1935 = cnf;}
void s1032::s174( const wstring& s78, size_t& pos, s9<s146> ob ){
size_t s75, s76;
s55( s78, pos, L'{', L'}', s75, s76, true );
if( s75 == string::npos )
return;
s1168 = s75 - 1;
wstring sob = s78.substr( s75, s76 - s75 + 1 );
pos = s76 + 1;
try {
s1948.push_back( s1938.s154 );
ob->s157( sob, s1938 );
s1948.pop_back();}
catch( s16* e ) {
s1948.pop_back();
e->s30( L"during reading the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s1032::s1103( wstring& s, size_t s69, size_t s715, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1232.lower_bound( s69 );
auto iten = s1232.lower_bound( s715 );
if( itst == end(s1232) || iten == end(s1232) )
return false;
line = itst->second;
s = s1231[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1231[iten->second-1];
return true;}
void s191( wstring& s78 ){
wregex s192(
LR"regex(\n\r?\/\/.*?\n\r?)regex"
);
wsmatch sm;
wstring::const_iterator itst = s78.begin();
wstring::const_iterator iten = s78.end();
while( std::regex_search( itst, iten, sm, s192 ) ) {
s78.erase( sm.position(), sm.length() - 
(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
itst = s78.begin();
iten = s78.end();}}
s1032::s1032( const std::wstring& file, bool s1810, const s1873& s1937 )
: s1938( s1937 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s49 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1810 == false )
s1230 = file;
else
s198 = file;}
void s1032::read( vector<s9<s146>>& s156, const wstring& s194 ){
size_t pos = 0;
if( s198.size() ) {
std::ifstream fs( TOFS( s198 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s198 ));
string s195( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1230 = conv.from_bytes( s195 );
s4::s82( s1230, s1231, s1232 );
if( s194.size() ) {
pos = s1230.find( s194 );
if( pos == string::npos )
throw new s16( s194 + L" directive not found in the source file." );
pos += s194.size() + 1;
if( s1230.size() > 13 && s1230[14] == '\r' )
++pos;}}
size_t s196 = pos;
wstring s284;
bool s197 = false;
while( ( pos = s1230.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1230.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s196; subl = pos - s196;}
else
pl += 1;
wstring s1 = s53( s1230.substr( pl, /*pos - pl - 1*/subl ), s49 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s197 = true;
else
s284 = s53( s1, s49 + L":" );}
if( s284.empty() ) {
size_t pl1 = s1230.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s53( s1230.substr( pl1, pl ), s49 );
if( s1.size() ) {
if( ( !s197 && s1[s1.size() - 1] != L':' ) ||
( s197 && s1[s1.size() - 1] == L':' ) ||
(!s197 && s1.size() == 1 ) )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
s284 = s53( s1, s49 + L":" );}}}
if( s89.find( s284[0] ) != string::npos ) {
if( s284[0] != s284[s284.size()-1] )
throw new s16( L"Malformed block name: " + s284.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
else {
if(	iswdigit( s284[0] ) )
throw new s16( L"wrong unquoted syntax: " + s284.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
s9<s146> ob = new s146( this );
try {
s1948.push_back( s1938.s154 );
s174( s1230, pos, ob );
s1948.pop_back();}
catch( s16* e ) {
s1948.pop_back();
e->s30( L"during reading the file: " + s198 );
throw e;}
if( s284.size() )
ob->s162( L"@name", new s144( s284 ), s146::s148::s150 );
s284 = L"";
s197 = false;
s156.push_back( ob );}}
void s175( const wstring& s198, const vector<s1::s9<s146>>& s199 ){
std::ofstream fs( TOFS( s198 ), ios::out | ios::trunc | ios::binary );
if( !fs.good() )
throw runtime_error( "Reading state file failed: " + U8( s198 ) );
for( auto ob : s199 ) {
basic_stringstream<wchar_t> ss;
ob->s158( &ss );
string s = U8( ss.str() );
s += "\n\n";
fs.write( s.c_str(), s.size() );}}
void s176( const wstring& s78, size_t& pos, wchar_t quote, wstring& s156, bool s154 = false ){
size_t s75, s76;
s56( s78, pos, quote, s75, s76 );
if( s76 != string::npos ) {
pos = s76 + 1;
if( s1948.back() )
s156 = s53( s78.substr( s75, s76 - s75 + 1), s49 ); 
else
s156 = s53( s78.substr( s75+1, s76 - s75 - 1 ), s49 ); }
else
pos = string::npos;}
void s177( wostream* pd, const wstring& s ){
wchar_t q = L'\"';
if( s89.find( s[0] ) != string::npos )
q = s[0];
size_t start = 1;
*pd << q;
if( s[0] != q ) 
start = 0;
for( size_t n = start; n < s.size(); ++n ) {
if( s[n] == q && s[n-1] != L'\\' && n != s.size() - 1 )
*pd << L'\\';
*pd << s[n];}
if( s[s.size()-1] != q )
*pd << q;}
void s178( const wstring& s78, size_t& pos, wstring& s156 ){
if( !std::isgraph<wchar_t>( s78[pos], locloc ) ||
s78[pos] == L':' || s78[pos] == L',' )
throw new s16( L"unrecognized unquoted syntax: " + s78.substr(pos, 20), 
(uint32_t)s16::s17::s20 );
size_t s200 = pos + 1;
while( std::isgraph<wchar_t>( s78[s200], locloc ) &&
s78[s200] != L':' && s78[s200] != L',' )
++s200;
s156 = s53( s78.substr( pos, s200 - pos ), s49 );
pos = s200;}
void s179( const wstring& s78, size_t& pos, wchar_t s1352, wchar_t s1401, wstring& s156 ){
size_t s75, s76;
s55( s78, pos, s1352, s1401, s75, s76, true );
if( s76 == string::npos )
throw new s16( L"unmatched unquoted parentheses: " + s78.substr(pos, 20), 
(uint32_t)s16::s17::s20 );
if( s76 == s78.size() - 1 ) {
pos = s76;}
else {
size_t pl = s78.find_first_not_of( s49, s76 + 1 );
if( pl == string::npos && s78[pl] != L',' && s78[pl] != L'}' )
throw new s16( L"wrong unquoted parentheses syntax: " + s78.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
pos = s76 + 1;}}
s134 s180( const wstring& s78, size_t& pos, wstring& s156, const s1873& s1937 ){
if( s78[pos] == s1937.s1875[0] && s1937.s1922) {
s156 = L"";
return s135;}
if( !std::isgraph<wchar_t>( s78[pos], locloc ) ||
s78[pos] == L':' || s78[pos] == L',' )
throw new s16( L"empty element or unrecognized unquoted syntax: " + s78.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s200 = pos;
int shift = 0;
if( s78[pos] == L'(' && s1937.s1877) {
s179( s78, s200, L'(', L')', s156 );
if( s200 == s78.size() - 1 )
shift = 1;}
else {
s200 = pos + 1;
while( std::isgraph<wchar_t>( s78[s200], locloc ) &&
s78[s200] != L':' && s78[s200] != L',' ) {
if( s78[s200] == L'<'  && s1937.s1878 ) {
s179( s78, s200, L'<', L'>', s156 );}
else if( s78[s200] == L'(' && s1937.s1877 ) {
s179( s78, s200, L'(', L')', s156 );
if( s200 == s78.size() - 1 )
shift = 1;
break;}
else
++s200;}}
s156 = s53( s78.substr( pos, s200 - pos + shift ), s49 );
pos = s200;
return s137;}
void s181( wostream* pd, const wstring& s ){
if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
s[s.size()-1] == L'"' )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
for( size_t n = 0; n < s.size(); ++n ) 
if( !std::isgraph<wchar_t>( s[n], locloc ) )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
*pd << s;}
void s182( const s1032* pf, const wstring& s78, vector<s9<s144>>& s156, 
const s1873& s1937 ){
size_t s69 = s78.find_first_not_of( s49 );
s1948.push_back( s1937.s1910 );
while( true ) {
s156.push_back( s9<s144>(new s144( pf, s78, s69, s1937 ) ) );
s4::s1098( s78, s69, s1937.s1875 );
if( s69 == string::npos )
break;
++s69;}
s1948.pop_back();}
void s182( const s1032* pf, const wstring& s78, size_t& pos,
vector<s9<s144>>& s156, const s1873& s1937 ){
size_t s75, s76, s69 = 0;
s55( s78, pos, L'[', L']', s75, s76, true );
pos = s76 + 1;
wstring ar = s53( s78.substr( s75 + 1, s76 - s75 - 1 ), s49 );
if( ar.empty() )
return;
s1948.push_back( s1937.s1910 );
while( true ) {
s156.push_back( s9<s144>(new s144( pf, ar, s69, s1937 ) ) );
s4::s1098( ar, s69, s1937.s1875 );
if( s69 == string::npos )
break;
++s69;}
s1948.pop_back();}
void s183( wostream* pd, const vector<s9<s144>>& v, bool s154=false ){
*pd << L'[';
for( size_t n = 0; n < v.size(); ++n ) {
v[n]->s158( pd, s154 );
if( n != v.size() - 1 )
*pd << L',';}
*pd << L']';}
void s184( const wstring& s78, size_t& pos, wstring& s156, bool s154 = false ){
size_t pl = s78.find_first_not_of( L", \n\r\t", pos );
if( s89.find( s78[pl] ) != string::npos ) 
s176( s78, pos, s78[pl], s156, s154 );
else {
if( !std::isgraph<wchar_t>( s78[pos], locloc ) ||
s78[pos] == L':' || s78[pos] == L',' )
throw new s16( L"unrecognized name syntax: " + s78.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
size_t s200 = pos + 1;
while( s78[s200] != L':' && s78[s200] != L',' ) {
if( !std::isalnum<wchar_t>( s78[s200], locloc ) &&
!std::isspace<wchar_t>( s78[s200], locloc ) && s78[s200] != L'_' &&
s78[s200] != L'-' )
throw new s16( L"unrecognized name syntax: " + s78.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
++s200;}
s156 = s53( s78.substr( pos, s200 - pos ), s49 );
pos = s200;}}
void s185( wostream* pd, const wstring& s, bool s154=false ){
bool space = false;
for( size_t n = 0; n < s.size(); ++n )
if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
space = true;
break;}
if( !space && !s154 && s89.find( s[0] ) == string::npos )
s181( pd, s );
else
s177( pd, s );}
s134 s186( const wstring& s78, size_t& pos, double& s156 ){
s134 s717 = s143;
size_t pl = s78.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s78.find( L".", pl );
if( pl1 < pl )
s717 = s139;
if( pl == string::npos )
s156 = stod( s78.substr( pos ) );
else
s156 = stod( s78.substr( pos, pl - pos ) );
pos = pl;
return s717;}
s134 s1724( const wstring& s78, size_t& pos, double& s156, const s1873& s1937 ){
const wchar_t* ps = s78.c_str();
size_t sz = s78.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1713.find( ps[st+1] ) == string::npos )
return s135;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1712.find( ps[st+1] ) != string::npos ) ||
( s1712.find( ps[st] ) == string::npos ) )
return s135;
size_t s716 = st;
bool pt = false;
while( s716 < sz ) {
if( ps[s716] == s1937.s1874[0] ) {
if( pt ) return s135;
pt = true;
s716++;}
else if( s1712.find( ps[s716] ) != string::npos )
s716++;
else if( (s49 + s1937.s1875).find( ps[s716] ) != string::npos  )
break;
else
return s135;}
s134 s717 = s143;
if( pt )
s717 = s139;
if( s716 == sz )
s156 = stod( s78.substr( pos ) );
else
s156 = stod( s78.substr( pos, s716 - pos ) );
pos = s716;
return s717;}
bool s187( const wstring& s78, size_t& pos, bool& s156 ){
size_t pl = 0;
if( s78.find( L"true", pos, 4 ) == pos )
pl = 4;
else if( s78.find( L"false", pos, 5 ) == pos )
pl = 5;
if( pl ) {
if( s190.find( s78[pos+pl] ) != string::npos ) {
pos += pl;
s156 = (pl == 4);
return true;}}
return false;}
bool s188( const wstring& s78, size_t& pos ){
if( s78.find( L"null", pos, 4 ) == pos ) {
if( s190.find( s78[pos+4] ) != string::npos ) {
pos += 4;
return true;}}
return false;}
s144::s144( const s1032* pf, const wstring& s78, size_t& pos, const s1873& s1937 )
: s202( s135 ), obj( pf ), s1192( pos + (pf ? pf->s1037():0), 0 ), s1191( (s1032*)pf ){
size_t s69 = s78.find_first_not_of( L" \n\r\t", pos );
if( s69 == string::npos ) {
if( s1937.s1922 )
s202 = s135;
else {
s16* s1059 = new s16(wstring( 28, L' ' ) + L"|^|" );
s1059->s30( L"empty array item: " + s78.substr( pos - 10, 20 ) );
throw s1059;}}
else if( s78[s69] == L'{' ) {
size_t s75, s76;
s55( s78, s69, L'{', L'}', s75, s76, true );
pos = s76+1;
obj.s157( s53( s78.substr( s75 + 1, s76 - s75 - 1 ), s49 ), s1937 );
s202 = s136;}
else {
pos = s69;
if ( s89.find( s78[pos] ) != string::npos ) {
s176( s78, pos, s78[pos], str, s1937.s154 );
s202 = s142;}
else if ( s78[pos] == L'[' ) {
s182( (s1032*)s1191, s78, pos, s165, s1937 ); 
s202 = s138;}
else {
s202 = s1724( s78, pos, s166, s1937 );
if( s202 != s135 )
(void)0;
else if( s187( s78, pos, b ) )
s202 = s140;
else if( s188( s78, pos ) )
s202 = s141;
else
s202 = s180( s78, pos, str, s1937 );;}}
s1192.second = pf ? pos - 1 + pf->s1037() : 0;}
bool s144::s1108( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1192.first || s1191.s13() )
return false;
f = s1191->Path();
s1191->s1103( s, s1192.first, s1192.second, line );
return true;}
const s146& s144::s169() const{
if( s202 == s136 )
return obj;
throw new s16( L"NQJ value: wrong variant" );}
const std::vector<s145>& s144::s170() const{
if( s202 == s138 )
return s165;
throw new s16( L"NQJ value: wrong variant" );}
double s144::s171() const{
if( s202 == s139 )
return s166;
throw new s16( L"NQJ value: wrong variant" );}
int s144::s57() const{
if( s202 == s143 )
return (int)s166;
throw new s16( L"NQJ value: wrong variant" );}
bool s144::s766() const{
if( s202 == s140 )
return b;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s144::s172() const{
if( s202 == s137 || s202 == s142 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s144::s938() const{
if( s202 == s142 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
std::wstring s144::s928() const{
if( s202 == s142 )
return str.substr( 1, str.size() - 2 );
throw new s16( L"NQJ value: wrong variant" );}
void s146::s157( const wstring& s78, const s1873& s1937 ){
s147.clear();
size_t s69;
size_t pl = s78.find_first_not_of( L" \n\r\t" );
if( pl == string::npos )
return;
if( s78[pl] == L'{' )
s69 = s78.find_first_not_of( L" \n\r\t", pl + 1 );
else
s69 = pl;
while( true ) {
wstring s77;
s184( s78, s69, s77, s1937.s154 );
size_t pl = s78.find_first_not_of( L" \n\r\t", s69 );
if( pl == string::npos || s78[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s78.substr(s69, 50), 
(uint32_t)s16::s17::s20 );
s69 = pl + 1;
s147.insert( make_pair( s77, new s144( src, s78, s69, s1937 ) ) );
pl = s78.find_first_not_of( L" \n\r\t", s69 );
if( pl != string::npos && s190.find( s78[pl] ) == string::npos ) 
throw new s16( L"wrong nqj syntax: missed separator or closing brace: " + s78.substr(s69, 50), 
(uint32_t)s16::s17::s20 );
if( pl != string::npos )
pl = s78.find_first_not_of( L" \n\r\t", pl+1 );
if( pl == string::npos )
break;
s69 = pl;}}
bool s146::operator==( const s146& r )  const{
bool s717 = true;
for( auto it = s147.begin(); it != s147.end(); ++it ) {
auto it1 = r.s147.find( it->first );
if( it1 == r.s147.end() || !( *( it->second ) == *( it->second ) ) ) {
s717 = false;
break;}}
return s717;}
void s146::s158( wostream* pd, bool s154 ) const{
*pd << L"{\n";
for( auto it = s147.begin(); it != s147.end(); ++it ) {
if( it != s147.begin() )
*pd << L",\n";
s185( pd, it->first, s154 );
*pd << L" : ";
it->second->s158( pd );}
*pd << L"\n}";}
void s144::s158( wostream* pd, bool s154 ) const{
if( s202 == s136 )
obj.s158( pd, s154 );
else if( s202 == s138 )
s183( pd, s165, s154 );
else if( s202 == s137 )
s185( pd, str, s154 );
else if( s202 == s142 )
s185( pd, str, true );
else if( s202 == s139 )
*pd << to_wstring( s166 );
else if( s202 == s143 )
*pd << to_wstring( (int)s166 );
else if( s202 == s140 )
*pd << ( b ? L"true" : L"false" );
else if( s202 == s141 )
*pd << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool s146::s159( const wstring& s155 ) const{
if( s147.find( s155 ) != s147.end() )
return true;
return false;}
void s146::s160( const wstring& s155, vector<s9<s144>>& s156 ) const{
auto i = s147.equal_range( s155 );
if( i.first == i.second )
return;
for( auto it = i.first; it != i.second; ++it )
s156.push_back( it->second );}
const s145 s146::s161( const wstring& s155 ) const{
if( s147.count( s155 ) > 1 )
throw new s16( L"multiple values: " + s155, (uint32_t)s152 );
auto s717 = s147.find( s155 );
return s717->second;}
void s146::s162( const std::wstring& s77, s145 s363, s148 ap ){
if( s147.find( s77 ) != s147.end() ) {
if( ap == s149 )
throw new s16( L"Field already exists: " + s77, (uint32_t)s16::s17::s21 );
else if( ap == s151 )
return;
else if( ap == s150 )
s147.erase( s77 );}
s147.insert( make_pair( s77, s363 ) );}
void s146::s1807( const std::wstring& s77 ){
if( s147.find( s77 ) == s147.end() )
throw new s16( L"Attribute doesn't exist: " + s77, (uint32_t)s16::s17::s21 );
s147.erase( s77 );}
void s146::s163( vector<pair<wstring, s9<s144>>>& s156 ) const{
for( auto it = s147.begin(); it != s147.end(); ++it ) 
s156.push_back( *it );}
void s146::s164( wostream* pd, int s201 ) const{
for( auto it = s147.begin(); it != s147.end(); ++it ) {
*pd << FILL(s201) << it->first << " : " << endl;
it->second->s164( pd, s201 + 2 );}}
void s144::s164( wostream* pd, int s201 ) const{
if( s202 == s136 )
obj.s164( pd, s201 + 2 );
else if( s202 == s138 ) {
for( size_t n = 0; n < s165.size(); ++n ) {
s165[n]->s164( pd, s201 );
if( n < s165.size() - 1 )
*pd << endl;}}
else if( s202 == s137 )
*pd << FILL( s201 ) << str << endl;
else if( s202 == s139 )
*pd << FILL( s201 ) << s166 << endl;
else if( s202 == s143 )
*pd << FILL( s201 ) << s166 << endl;
else if( s202 == s140 )
*pd << FILL( s201 ) << b << endl;
else if( s202 == s141 )
*pd << FILL( s201 ) << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool operator==( const std::vector<s9<s144>>& l,
const std::vector<s9<s144>>& r ){
if( l.size() == r.size() ) {
for( size_t n = 0; n < l.size(); ++n )
if( !(*( l[n] ) == *( r[n] ) ) )
return false;
return true;}
return false;}
s134 s1887::s1724( const std::wstring& s78, size_t& pos, double& s156 ){
return s6::s1724( s78, pos, s156, conf );}
} // namespace s6
using namespace s6;
namespace transd {
namespace s7 {
s1014 s1728		= 0x80000000;
s1014 s1566        = s1728 - 1;
s1014 s1567       = s1728 - 2;
s1014 s1568       = s1728 - 3;
s1014 s1565      = s1728 - 4;
s1014 s1564						= s1728 - 8;
s1014 s1569    = s1728 - 9;
s1014 s1570					= s1728 - 10;
DEFCONST s435 = L"typeMembers";
DEFCONST s436 = L"typeMember";
DEFCONST s437 = L"typeMethods";
DEFCONST s438 = L"typeMethod";
DEFCONST s439 = L"members";
DEFCONST s440 = L"member";
DEFCONST s441 = L"methods";
DEFCONST s442 = L"method";
DEFCONST s443 = L"@init";
DEFCONST s444 = L"initCall";
DEFCONST s1805 = L"@to-String";
DEFCONST s445 = L"thisPtr";
DEFCONST s446 = L"virtual";
DEFCONST s447 = L"override";
DEFCONST s896 = L"return";
DEFCONST s448 = L"continue";
DEFCONST s449 = L"break";
DEFCONST s450 = L"throw";
DEFCONST s810 = L"else";
DEFCONST s791 = L"elsif";
DEFCONST s845 = L"to";
DEFCONST s451 = L"true";
DEFCONST s452 = L"false";
DEFCONST s895 = L"null";
DEFCONST s1027 = L"->";
DEFCONST s1262 = L"const";
DEFCONST s1524 = L"new";
DEFCONST s1562 = L"stdin";
DEFCONST s1563 = L"stdout";
DEFCONST s1777 = L"this";
DEFCONSTI s939 = -1;
DEFCONSTI s455 = -2;
DEFCONSTI s453 = -100;
DEFCONSTI s454 = -101;
DEFCONSTI s456 = 1;
DEFCONSTI s457 = 0;
DEFCONSTI s941 = 0x80000000;
DEFCONSTI s1925 = 0x80000001;
DEFCONSTI s940 = 0;
DEFCONSTI s1342 = 1;
DEFCONST s1584 = L":Number";
DEFCONST s1698 = L":Integer";
DEFCONST s1582 = L":IterableForw";
DEFCONST s1581 = L":IterableBidir";
DEFCONST s1583 = L":IterableRand";
DEFCONST s1580 = L":IStream";
DEFCONST s1585 = L":OStream";
DEFCONST s1579 = L":IOStream";
DEFCONST s458 = L"import";
DEFCONST s459 = L"input";
DEFCONST s460 = L"output";
DEFCONST s461 = L"export";
DEFCONST s462 = L"opaque";
DEFCONST s463 = L"public";
DEFCONST s464 = L"private";
DEFCONST s465 = L"secure";
DEFCONST s466 = L"class";
DEFCONST s467 = L"module";
DEFCONST s468 = L"AssemblyDescription";
DEFCONST s469 = L"ProgramText";
DEFCONST s470 = L"Export";
DEFCONST s471 = L"Require";
DEFCONST s472 = L".td";
DEFCONST s1033 = L".tsd";
DEFCONST s474 = L"MainModule";
DEFCONST s473 = L"_start";
DEFCONST s475 = L"asm" + s472;
DEFCONST s476 = L"@ex";
DEFCONST s1544 = L"@it";
DEFCONST s477 = L"@idx";
DEFCONST s814 = L"@pars";
DEFCONST s853 = L"@obj";
DEFCONST s888 = L"@numArgs";
DEFCONST s1747 = L"@progArgs";
DEFCONST s1240 = L"@sourceFile";
DEFCONST s1543 = L"@OS_Type";
DEFCONST s482 = L"source";
DEFCONST s478 = L"objectType";
DEFCONST s479 = L"moduleType";
DEFCONST s480 = L"@name";
DEFCONST s481 = L"entryPoint";
DEFCONST s483 = L"perm";
DEFCONST s485 = L"extends";
DEFCONST s778 = L"packages";
DEFCONST s487 = L"searchDirs";
DEFCONST s1022 = L"@attrs";
DEFCONST s1001 = L"is";
DEFCONST s1000 = L"index type";
DEFCONST s1002 = L"value type";
DEFCONST s433 = L"#lang transd";
DEFCONST s1222 = L"#format tsd";
s1014 s1458						= 103;
s1014 s1535					= 104;
s1014 s1009						= 110;
s1014 s1457				=	123;
s1014 s1245						= 124;
s1014 s1010 			=	125;
s1014 s1004			= 201;
s1014 s1223				= 204;
s1014 s1005					= 210;
s1014 s1224					= 304;
s1014 s1225				= 404;
s1014 s1226				= 504;
s1014 s1006					= 510;
s1014 s1007			= 511;
s1014 s1008					= 610;
s1014 s1242							= 710;
s1014 s1243					= 711;
s1014 s1536		= 804;
s1014 s1537				= 904;
s1014 s1538				= 1004;
s1014 s1773					= 1024;
s1014 s1244					= 1124;
s1014 s1454				= 1203;
s1014 s1455				= 1210;
s1014 s1456				= 1224;
s1014 s1843		= 1304;
s1014 s1844						= 1404;
s1014 s1548						= 1410;
s1014 s1845						= 1504;
s1014 s1546						= 1510;
s1014 s1547					= 1511;
s1014 s1846				= 1604;
s1014 s1696					= 1610;
s1014 s1697			= 1611;
s1014 s1864			= 1704;
s1014 s1729			= 1710;
s1014 s1775	= 1715;
s1014 s1774				= 1824;
s1014 s1865					= 1904;
s1014 s1880				= 2025;
s1014 s2071				= 2103;
set<wstring> s1239 = { s1240, s1562, s1563, s1543, s896, s448,
s449, s450, s810, s791, s845, s451, s452, s895, s1027, s1262,
s1524, s1562, s1563, s1777, L"and", L"or"
};
} // namespace s7
std::wstring s234[] = { L"value", L"function", L"object", L"name" };
const wstring s235 = L"if";
const wstring s236 = L"set";
const wstring s237 = L"sum";
const wstring s238 = L"with";
const wstring s239 = L"mul";
const wstring s240 = L"div";
const wstring s241 = L"dif";
const wstring s242 = L"eq";
const wstring s243 = L"less";
const wstring s244 = L"greater";
const wstring s245 = L"leq";
const wstring s246 = L"geq";
const wstring s247 = L"neq";
const wstring s248 = L"and";
const wstring s249 = L"or";
const wstring s250 = L"dcmp";
const wstring s251 = L"dcmpr";
const wstring s252 = L"mod";
const wstring s253 = L"sqrt";
const wstring s254 = L"abs";
const wstring s255 = L"pow";
const wstring s256 = L"textout";
const wstring s257 = L"lambda";
const wstring s258 = L"proc";
const wstring s260 = L"while";
const wstring s261 = L"eval";
const wstring s262 = L"try";
const wstring s263 = L"catch";
const wstring s264 = L"throw";
const wstring s259 = L"through";
const wstring s265 = L"for";
const wstring s267 = L"run-file";
const wstring s817 = L"load-file";
const wstring s877 = L"import-module";
const wstring s1796 = L"unload-file-modules";
const wstring s1483 = L"unload-module";
const wstring s794 = L"has-field";
const wstring s873 = L"tsd-query";
const wstring s803 = L"substr";
const wstring s923 = L"ret";
const wstring s924 = L"sort";
const wstring s986 = L"exit";
const wstring s1482 = L"to-file";
const wstring s1602 = L"any";
const wstring s1601 = L"all";
const wstring s1736 = L"lout";
const wstring s1792 = L"read-tsd-file";
const wstring s1791 = L"load-from-object";
const wstring s1795 = L"start-process";
const wstring s1793 = L"rebind";
const wstring s1794 = L"sleep";
const wstring s1790 = L"diag";
const wstring s2065 = L"rand";
const std::wstring s271 = L"AttrNA";
s269::s269( const std::wstring& s, const s144* s6 )
: s1160( (s144*)s6 ){
s1100( s );}
s269::s269( const std::wstring& s708, const s6::s144& s302 )
: s284( s708 ), s1160( (s144*)&s302 ){
if( s302.s167() == s137 ) {
wstring s = s302.s172();
s1100( s );}
else if( s302.s167() == s142 ) {
wstring s = //L"\"" +
s302.s172();// +
s290( s );}
else if( s302.s167() == s136 ) {
basic_stringstream<wchar_t> ss;
s302.s158( &ss, true );
if( s284.find( s332::proto->s368() ) == 0 ) {
s290( ss.str() );
s284 = s4::s53( s284.substr( s332::proto->s368().size() ), s49 );}
else {
src = ss.str();
s289( s302.s169() );}}
else if( s302.s167() == s139 )
s290( to_wstring( s302.s171() ) );
else if( s302.s167() == s143 )
s290( to_wstring( s302.s57() ) );
else if( s302.s167() == s140 )
s290( /*to_wstring( s302.s766() )*/ s302.s766() ? L"true" : L"false" );
else if( s302.s167() == s138 ) {
basic_stringstream<wchar_t> ss;
s302.s158( &ss );
if( s284.find( L"UVector" ) == 0 ) {
s290( L"UVector" + ss.str() );
s284 = s4::s53( s284.substr( 7 ), s49 );}
else
s290( ss.str() );}
else if( s302.s167() == s135 )
s290( L"" );
else
throw new s16( L"Unhandled nqj variant: " + to_wstring( s302.s167() ) );}
s269::s269( const s6::s146& s136 ){
s289( s136 );}
s269::~s269(){
reset();}
void s269::reset(){
s287.clear();
s272.clear();
s283 = s284 = s286 = src = L"";}
void s269::s1100( const wstring& s ){
size_t pos = 0;
wstring s1327 = L"\"'-+[<";
if( s.empty() ) {
s290( s );}
else if( s[pos] == L'(' )
s288( s );
else if( iswalpha( s[pos] ) || s[pos] == L'_' || s[pos] == L'@' || s[pos] == L':' ) {
if( s.find( L'(' ) != string::npos || s.find( L"true" ) == 0 
|| s.find( L"false" ) == 0)
s290( s );
else
s291( s );}
else if( iswdigit( s[pos] ) || s1327.find( s[pos] ) != string::npos ) {
wstring s78;
s78 = s53( s, s49 );
s290( s78 );}
else
throw new s16( L"Unknown string content: " + s );}
void s269::s288( const std::wstring& s78 ){
src = s78;
size_t pos = 0;
vector<wstring> s709;
s294( s78, pos, s709 );
if( s709.empty() )
return;
s285 = s231;
size_t s69 = 0;
s286 = s293( s709[0], s69 );
for( size_t n = 1; n < s709.size(); n++ )
s287.insert( make_pair( to_wstring( n - 1 ), new s269( s709[n], s1160 ) ) );}
void s269::s290( const std::wstring& s78 ){
src = s78;
s285 = s230;
s286 = s78;}
void s269::s291( const std::wstring& s78 ){
src = s78;
s285 = s233;
s286 = s78;}
void s269::s289( const s6::s146& s136 ){
s284 = s308( s136, s7::s480 );
s285 = s232;
vector<pair<wstring, s145>> s147;
s136.s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s292( s147[n].first, *s147[n].second );}}
void s710( wstring& s ){
wregex rgBr(
LR"regex(\s(\s+))regex"
);
wsmatch sm;
wstring::const_iterator itst = s.begin();
wstring::const_iterator iten = s.end();
while( std::regex_search( itst, iten, sm, rgBr ) ) {
s.erase( sm.position( 1 ), sm.length( 1 ) );
itst = s.begin();
iten = s.end();}}
void s269::s295( s6::s146& obj ){
wstring s711 = s4::s53( s308( obj, s7::s480 ), s49 );
wstring s687 = s711;
s710( s687 );
if( s687.empty() )
throw new s16( L"Nameless blocks are forbidden." );
if( s687 != s711 )
obj.s162( s7::s480, s145(new s144( s687 )), s146::s150 );
if( s687 == s284 ) { // partial definition
vector<pair<wstring, s145>> s147;
obj.s163( s147 );
for( size_t n = 0; n < s147.size(); ++n )
s292( s147[n].first, *s147[n].second );}
else {
s287.insert( make_pair( s687, new s269( obj ) ) );}}
void s269::s292( s269* node ){
s287.insert( make_pair( node->s305(), node ) );}
void s269::s292( const std::wstring& s284, const s144& s363 ){
s287.insert( make_pair( s284, new s269( s284, s363 ) ) );}
void s269::s296( s268* s306, size_t s307 /*= 0*/ )
{
s281::iterator it = s287.begin();
for( ; it != s287.end(); ++it ) {
if( it->second->s303() == s232 ) {
if( s307 == 0 ) {
it->second->s296( s306, 1 );}
else {}}}}
const s269* s269::s298( const std::wstring& s284 ) const{
size_t s716 = s287.count( s284 );
if( s716 > 1 )
throw new s16( L"multiple values: " + s284, (uint32_t)s152 );
if( s716 == 1 ) {
auto s717 = s287.find( s284 );
return s717->second.s15<s269*>();}
throw new s16( L"node not found: " + s284, (uint32_t)s16::s17::s23 );
s281::const_iterator it = s287.begin();
for( ; it != s287.end(); ++it ) {
try {
const s269* s717 = it->second->s298( s284 );
return s717;}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s23 )
continue;
throw e;}}
throw new s16( L"node not found: " + s284, (uint32_t)s16::s17::s23 );}
void s269::s294( const wstring& s78, size_t& pos, vector<wstring>& s156 ){
size_t s75, s76;
s55( s78, pos, L'(', L')', s75, s76, true );
if( s75 != pos || s76 == string::npos )
throw new s16( L"Parentheses don't match near \"" + 
s78.substr( 0, 40 ) + L"...\"" );
pos = s76;
size_t s69 = s78.find_first_not_of( s49, s75 + 1 );
if( s78[s69] == L')' )
return;
size_t s715 = s69;
wstring s712;
while( s715 < s76 ) {
s69 = s78.find_first_not_of( s49 + L")", s715 );
if( s69 >= s76 )
break;
size_t s713, s714;
if( s78[s69] == L'(' ) {
s55( s78, s69, L'(', L')', s713, s714, true );
if( s714 == s76 )
throw new s16( L"Parentheses don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
s712 = s78.substr( s69, s714 - s69 + 1 );
s715 = s714 + 1;}
else if( s78[s69] == L'[' ) {
s55( s78, s69, L'[', L']', s713, s714, true );
if( s714 == s76 )
throw new s16( L"Brackets don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
s712 = s78.substr( s69, s714 - s69 + 1 );
s715 = s714 + 1;}
else if( s78[s69] == L'"' ) {
s56( s78, s69, L'"',
s713, s714 );
if( s714 == string::npos )
throw new s16( L"Quotes don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
s712 = s78.substr( s69, s714 - s69 + 1 );
s715 = s714 + 1;}
else if( iswdigit( s78[s69] ) ) {
s714 = s78.find_first_of( s49 + L")", s69 );
s712 = s78.substr( s69, s714 - s69 );
s715 = s714;}
else if( iswalpha( s78[s69] ) || s78[s69] == L'_' ) {
s714 = s78.find_first_of( s49 + L")", s69 );
size_t pl = s78.find( L'<', s69 );
if( pl < s714 ) {
s55( s78, pl, L'<', L'>', s713, s714, true );
if( s714 == s76 )
throw new s16( L"Angle brackets don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
if( s78[s714+1] == L'(' ) {
s55( s78, pl, L'(', L')', s713, s714, true );
if( s714 == s76 )
throw new s16( L"Parentheses don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );}
s712 = s78.substr( s69, s714 - s69 + 1 );
s715 = s714 + 1;}
else {
pl = s78.find( L'(', s69 );
if( pl < s714 ) {
s55( s78, pl, L'(', L')', s713, s714, true );
if( s714 == s76 )
throw new s16( L"Parentheses don't match near \'" + s78.substr( s69, 40 ) + L"...\'" );
s712 = s78.substr( s69, s714 - s69 + 1 );
s715 = s714 + 1;}
else {
s712 = s78.substr( s69, s714 - s69 );
s715 = s714;}}}
else {
s714 = s78.find_first_of( s49 + L")", s69 );
s712 = s78.substr( s69, s714 - s69 );
s715 = s714;}
s156.push_back( s712 );}}
wstring s269::s293( const std::wstring& s78, size_t &pos ){
size_t s1907 = s78.find( L"<" );
if( s1907 != string::npos && s1907 > 0 ) {
return s78;}
wstring s717;
if( s78[pos] == L'+' && s78[pos + 1] != L'=' )
s717 = s237;
else if( s78[pos] == L'-' && s78[pos + 1] != L'=' )
s717 = s241;
else if( s78[pos] == L'*' && s78[pos + 1] != L'=' )
s717 = s239;
else if( s78[pos] == L'/' && s78[pos + 1] != L'=' )
s717 = s240;
else if( s78[pos] == L'^' && s78[pos + 1] != L'=' )
s717 = s255;
else if( s78[pos] == L'=' && s78[pos + 1] != L'=' )
s717 = s236;
else if( s78[pos] == L'<' && s78[pos + 1] != L'=' )
s717 = s243;
else if( s78[pos] == L'>' && s78[pos + 1] != L'=' )
s717 = s244;
else if( s78[pos] == 955 /*L'λ'*/ )
s717 = s257;
if( s717.size() ) {
if( s78.size() > pos + 1 && s78.find_first_of( s49 + L")", pos ) != pos + 1 )
throw new s16( L"1: unknown syntax: " + s78.substr(pos, 40),
(uint32_t)s16::s17::s20 );
pos += 1;
return s717;}
if( s78.substr( pos, 2 ) == L"+=" )
s717 = L"sumeq";
else if( s78.substr( pos, 2 ) == L"-=" )
s717 = L"difeq";
else if( s78.substr( pos, 2 ) == L"*=" )
s717 = L"muleq";
else if( s78.substr( pos, 2 ) == L"/=" )
s717 = L"diveq";
else if( s78.substr( pos, 2 ) == L"^=" )
s717 = L"poweq";
else if( s78.substr( pos, 2 ) == L"<=" )
s717 = L"leq";
else if( s78.substr( pos, 2 ) == L">=" )
s717 = L"geq";
else if( s78.substr( pos, 2 ) == L"==" )
s717 = L"eq";
else if( s78.substr( pos, 2 ) == L"!=" )
s717 = L"neq";
if( s717.size() ) {
if( s78.size() > pos + 2 && s78.find_first_of( s49 + L")", pos ) != pos + 2 )
throw new s16( L"2: unknown syntax: " + s78.substr( pos, 40 ), 
(uint32_t)s16::s17::s20 );
pos += 2;
return s717;}
size_t s715 = s78.find_first_of( s49 + L")", pos );
s717 = s78.substr( pos, s715 - pos );
pos = s715;
return s717;}
std::wstring s269::s304() const{
return (s283.size() ? s283 + L"::" : L"") + s284;}
wstring s269::s301( const s6::s146& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s159( s7::s479 ) )
return obj.s161( s7::s479 )->s172();
return def;}
std::wstring s269::s308( const s6::s146& obj,
const std::wstring& s309,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s159( s309 ) )
return obj.s161( s309 )->s172();
return def;}
const std::wstring& s269::s274( const std::wstring& s309 ) const{
auto it = s272.find( s309 );
if( it != s272.end() )
return it->second;
return s271;}
void s269::s275( const std::wstring& s309, const std::wstring& s273 ){
s272[s309] = s273;}
void s269::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s284 << L" : " << s234[s285] << endl;
buf << s4::fill_n_ch( L' ', s201 ) << L" " << s286 << endl;
map<wstring, s1034>::const_iterator it = s287.begin();
for( ; it != s287.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << it->first << endl;
it->second->s310( pd, s201 + s434 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1221 s1114;
void s1221::s1064( const std::wstring& s79 ){
++s1094;
s26.push_back( Msg( s79 ) );
wcout << s79;}
void s1221::s1064( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line ){
++s1094;
s26.push_back( Msg( s79, U16(func), U16(file), line, s1148 ) );}
void s1221::s1066( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s79, U16(func), U16(file), line, s1151 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1195 = {
L"unspecified",
L"compilation",
L"reading source file",
L"parsing NQJ",
L"converting to AST",
L"construction of object",
L"linking object",
L"linking function",
L"running program",
};
TDException::TDException( uint32_t s1116, uint32_t cat, const s269* ast_ )
: s16( L"", s1116 ), stage (Stage::s1137 ), category( cat ), s736( (s269*)ast_ ){}
TDException::TDException( Stage stg, uint32_t s1116, uint32_t cat, const s269* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s736( (s269*)ast_ ){
if( category ) {
s30( L"error code: " + std::to_wstring( s1116 ) );
s30( s1091[category] + L":" );}}
TDException::TDException( uint32_t s1116, uint32_t cat, const s269* ast_, const std::wstring& s79 )
: s16( s79, s1116 ), stage (Stage::s1137 ), category( cat ), s736( (s269*)ast_ ){
if( category ) {
s30( s1091[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1202( e.s1202 ), s736( e.s736 ){}
TDException* TDException::s1097( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s201 ) const{
size_t s1139 = 0;
wstring file, s1193, src;
if( s736.s14() ) {
if( s736->Nqj() && s736->Nqj()->s1108( file, s1193, s1139 ) ) {
wstring s1189 = std::to_wstring( s1139 ) + L": '" + s1193 + L"'";
src = L"\n  in file: " + file + L"\n  on line " + s1189;}
if( !s736->s297().empty() )
src += L"\n  object: '" + s736->s297() + L"', ";
if( !s736->Src().empty() )
src += L"code: '" + s736->Src() + L"', ";}
wstring s = L"Error ";
if( id ) {
wstring s1187;
if( (uint32_t)stage )
s1187 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1187 += std::to_wstring( id );
s += s1187;}
if( (uint32_t)stage ) {
s += L" during " + s1195[(uint32_t)stage];}
s += src + L"\n";
return wstring( s201, L' ' ) + s + s16::Msg( s201 + 2 );}
s1013::s1013( s16& e, const s269& s736, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1139 = 0;
wstring file, s1193, src;
wstring	s79 = L"Error during ";
if( s736.Nqj()->s1108( file, s1193, s1139 ) ) {
src = std::to_wstring( s1139 ) + L": '" + s1193 + L"'";
s79 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s79 += L"object: '" + s736.s297() + L"'; code: " + s736.Src();}
s30( s79 );
s1114.s1064( Msg( 2 ) );}
s1021::s1021( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s1091 = {
L"error",
L"incorrect call of object constructor",
L"incorrect call of builtin function",
L"incorrectly formed TSD query",
L"TSD query failed",
L"symbol is not resolved",
L"incorrect call of builtin type object's method",
L"the call of a builtin type object's method failed",
L"error during execution of built-in function",
L"error during object initialization",
L"symbol is already defined"
};
namespace lang {
bool s685( const wstring& s, bool s749 ){
bool fail = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1239.find( s ) != s7::s1239.end() )
continue;
fail = true;
break;}
if( fail && s749 )
throw new s16( L"illegal identifier: " + s );
return (!fail);}
} // namespace tdlang
s1012 s1090;
s277::~s277(){}
s501* s277::s515()
{	throw std::logic_error( "1: not implemented" );}
const s501* s277::s523() const
{	throw std::logic_error( "2: not implemented" );}
s504 s277::s516( s501** s280, size_t s517 )
{	throw std::logic_error( "3: not implemented" ); }
s277* s277::s349() const
{	throw std::logic_error( "4: not implemented" ); }
void s277::s519( const s278* s611, bool b ) {
(void)0;}
inline bool
s277::s521( const s501* s522 ) const{
return ( s522->s366() == s366() );}
inline bool
s277::s1715( s1170 s646 ) const{
return s306->TR().s1708( s366(), s646 );}
const s867& 
s277::s1339() const {
return s306->TR().s1112( s512 ); }
s277::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s277::operator int() const { throw std::logic_error( "6: not implemented" ); }
s277::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s277::to_wstring( uint32_t s1739 ) const { throw std::logic_error( "8: not implemented" ); }
s1488 s277::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s277::to_null() { s1855( s7::s1925 ); }
void s277::s1500( const s269& ast_, s268* s306, s278* obj,
const wstring& s346, vector<s277*>& s156 ){
size_t pos = 0;
vector<wstring> s709;
wstring s78 = ast_.s297();
if( s78.empty() )
return;
/*wstring s = s78;
if( s[0] != L'(' )
s = L"(" + s + L")";*/
s269::s294( s78.substr( s78.find( L"(" ) ), pos, s709 );
if( s709.empty() )
return;
for( size_t n = 0; n < s709.size(); n++ ) {
s269* ast1 = new s269( s709[n], ast_.Nqj() );
s156.push_back(
s277::s524( *ast1, s306, obj, s346 )
);}}
s277* s277::s524( const s269& s736, s268* s306, s278* obj,
const wstring& s346 ){
TDException s1059( s7::s1880, s1018, &s736 );
s277* p;
if( s736.s303() == s230 ) {
wstring s363 = s736.s297();
bool quot = s89.find( s363[0] ) != string::npos;
size_t ppl = s363.find( L"(" );
bool lastp = s363.back() == L')';
wstring ownerName = s736.s274( L"ownerName" );
if( ( s736.s274( L"ownerType" ) == L"CallSite" ) &&
( ownerName != s257 ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s361 = s363.substr( 0, ppl );
wstring s78 = L"(new<" + s361 + L"> " + s363.substr( ppl + 1 );
s1034 tast = new s269( s78, s736.Nqj() );
p = s615::s1235( *tast, s306, obj, s346 );}
else {
p = s306->TR().s541( s736, obj, s346 );
if( !p )
throw s1059.s1097( L"unrecognized type of the object: " + s736.s297() );
((s501*)p)->s526( s736.s305() );}}
else if( s736.s303() == s231 )
p = s615::s1235( s736, s306, obj, s346 );
else if( s736.s303() == s233 )
p = new s386( s736.s297(), s306 );
else //if( s736.s303() == s232 )
throw new s16( L"unexpected node type" );
return p;}
s277* 
s277::s1120( s268* s306, s277* par, s278* s612, s615* s219,
const std::wstring& s346 ){
s277* s717;
if( par->s513() == s495 ) {
s508 cs = new s584( *((s584*)par) );
s717 = s615::s624( cs, s306, s612, s219, s346, false );
((Transd*)s717)->s519( s612, false );}
else {
par->s519( /*s612*/s219 );
return par;}
return s717;}
s503
s277::s1119( const wstring& s78, const s269* ast_, s268* s306, s278* s612 ){
s1034 ast1;
if( ast_ )
ast1 = new s269( s78, ast_->Nqj() );
else
ast1 = new s269( L"", s78 );
s503 pr = s277::s524( *ast1, s306, s612, s612->s304() );
if( pr->s513() == s492 ) {
pr->s519( s612 );
pr = pr.s15<s386*>()->s392();}
s503 s717 = s277::s1120( s306, pr, s612, NULL, s612->s304() );
return s717;}
const wstring& 
s277::s368() const{
return s306->TR().s854( s366() );}
void s277::s365( s867::s776 type ){
s512 = type;}
s502* s1236( s525& m, const wstring& s155 ){
if( m.count( s155 ) > 1 )
throw new s16( L"multiple values: " + s155, (uint32_t)s16::s17::s21 );
auto s717 = m.find( s155 );
if( s717 == m.end() )
throw new s16( L"no such key: " + s155, (uint32_t)s16::s17::s23 );
return s717->second;}
void s701( const std::wstring& s, std::wstring& s1228, std::wstring& s625 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1228 = s.substr( 0, pl );
s625 = s.substr( pl + 2 );}
s501::~s501(){}
s501* s501::s515(){
return this;}
wstring s501::s304() const { return ns->s304(); }
wstring s501::s898() const { return ns->s898(); }
s501* s501::s1710( const s501* p ) const{
if( s366() == p->s366() ) {
s501* s717 = (s501*)p->s349();
return s717;}
throw new s16( L"no conversion from '" + s368() + L"' to '" + p->s368() + L"'" );}
s501* s501::s370( s278* s612, const std::vector<s1170>& vt ) const{
assert(0);
return 0;}
s1170 s501::s1331( const wstring& s1727, const vector<s503>& l ) const{
throw std::logic_error( "9: not implemented" );}
s615* s501::s1862( const std::wstring& s708, s615* s219, vector<s277*>& s740 ) const{
if( s708 == L"cp" ) {
return new s1857( s306, (s278*)this, s219, &s501::s1881, s740, L"cp",
NULL );}
else if( s708 == L"exec" ) {
return new s1857( s306, ns, s219, &s501::s2073, s740, L"exec",
NULL );}
return NULL;}
s501* s501::s1881( s501** s280, size_t s517 ){
return (s501*)s349();}
s501* s501::s2073( s501** s280, size_t s517 ){
return s516( s280, s517 );}
s501* s501::s2074( s501** s280, size_t s517 ){
return s2075( s280, s517 );}
s501* s501::s2075( s501** s280, size_t s517 ){
throw std::logic_error( "10: not implemented" );}
vector<wstring> s544::s548 = { s7::s461, s7::s459,
s7::s462, s7::s460 };
s1::s9<s549> s580 = new s549();
size_t s1058( const vector<s867::s978>& vt ){
size_t s717 = 0;
for( auto i : vt )
s717 = ( s717 << 7 ) ^ i;
return s717;}
size_t s509::s1163( const wstring& s, size_t& pos, s867::Cont& s156 ){
size_t s69 = pos;
size_t s717 = 0;
if( s[s69] == L' ' )
s69 = s.find_first_not_of( s4::s49, s69 );
while( s69 < s.size() && s[s69] != L'>' && s[s69] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s69 );
wstring stype = s4::s53( s.substr( s69, pl - s69 ), s4::s49 );
s1170 s1206 = get( stype /*+ L"()"*/ )->s366();
s156.push_back( s1206 );
pl = s.find_first_not_of( s4::s49, pl );
s867::Cont s1178;
size_t s1161 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1161 = s1163( s, ++pl, s1178 );}
else if( s[pl] == L',' ) {
s1161 = 0;}}
s156.push_back( ( s867::s978 ) s1161 );
s156.insert( end( s156 ), begin( s1178 ), end( s1178 ) );
s717++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s49, pl );
pos = s69 = pl;}
return s717;}
wstring s1296( const s867::Cont& s1173, size_t& idx, s509& s996 ){
wstring s717 = s996.s854(s1173[idx++]);
size_t n = (size_t)s1173[idx++];
if( n && s717.back() != L'>' ) {
s717 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s717 += ( k ? L" " : L"" ) + s1296( s1173, idx, s996 );}
s717 += L">";}
return s717;}
wstring s509::s1111( const s867::Cont& s1173 ){
assert( s1173.size() );
if( s1173.size() == 1 )
return  s1212[s1173[0]] + L"< 0 >";
size_t idx = 0;
wstring s717;
while( idx < s1173.size() ) {
s717 += s1296( s1173, idx, *this );
if( idx < s1173.size() )
s717 += L" ";}
return s717;}
wstring s509::s1520( const wstring& tn ){
wstring sv = tn;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
return sv;}
void s509::s1107( const s867::Cont& v, size_t& idx, s867::Cont& s156 ){
s156.push_back( v[idx++] );
size_t n = v[idx++];
s156.push_back( (s1170)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s1107( v, idx, s156 );}}
s867::s867( s776 t1, s776 t2/*=(s776)-1*/, s776 t3/*=(s776)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s776)-1 ) {
vt.push_back( t2 );
if( t3 != (s776)-1 )
vt.push_back( t3 );}
s1210 = s1058( vt );}
s867::s867( const s867& right )
: s1210( right.s1210 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s867::s867( const Cont& v ) 
: vt( v ) {
s1210 = s1058( vt );}
s867::s978 s867::s366( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s867::s365( s776 t ){
vt.clear();
vt.push_back( t );}
void s867::s365( s1011 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s867::s834( s776 t ){
vt.push_back( t );}
void s867::s834( s1011 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s867::s875( std::vector<s277*>& s156 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s156.push_back( new s360( NULL, (int)vt[n] ) );}
inline bool s867::operator==( const s867& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s776* pvt1 = (s776*)&vt[0];
s776* pvt2 = (s776*)&p.vt[0];
for( size_t s716 = 0; s716 < sz1; ++s716 )
if( pvt1[s716] != pvt2[s716] )
return false;
return true;}
s509::s509( s268* pass_ ) 
: s306( pass_ ) {
reset();}
void s509::s296(){
for( size_t n = 0; n < s1229.size(); ++n )
if( s1229[n] ) s1229[n]->s364();}
void s509::s539( const s500& st ){}
void s509::reset() {
s1229.clear(); 
s1212.clear();
s1217.clear();
s1213.clear();
s1218.clear();
s1003.clear();
s977.clear();
s1410.clear();
s1428.clear();
s1725.clear();
s1229.push_back( NULL ); 
s1212.push_back( L"" );
s1217.push_back( 0 );
s977[L":Data"] = 1;
s1410[1] = L":Data";
s1350 = 1;
s1428.push_back( 0 );
srand( (unsigned int)time(NULL) );}
void s509::s223( s501* p, const std::wstring& s361 ){
if( s1213.find( s361 ) != s1213.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1212.push_back( s361 );
s1229.push_back( p );
s1170 s1206 = (s1170)s1212.size() - 1;
s1217.push_back( s867( s1206 ) );
p->s365( s1206 );
s1213[s361] = s1206;
s1218[s1217.back()] = s1206;
s1428.push_back( 1 );
s1725.push_back( vector<s1170>() );}
void s509::s1842( const std::wstring& s361 ){
auto it = s1213.find( s361 );
if( it == s1213.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1170 s1206 = it->second;
s1213.erase( it );
s1229[s1206] = NULL;
s1212[s1206] = L"";
s1218.erase( s1217[s1206] );
s1217[s1206] = s867();
s1428[s1206] = 0;
s1725[s1206-1].clear();}
s1170 s509::s1177( const s867::Cont& v, const std::wstring& s361 ){
s867 vt( v );
if( s1218.find( vt ) != s1218.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1212.push_back( s361 );
s1217.push_back( vt );
s1170 s1206 = (s1170)s1212.size() - 1;
s1213[s361] = s1206;
s1218[s1217.back()] = s1206;
s1218[s867( s1206 )] = s1206;
s1229.push_back( s1229[vt.s366( 0 )]->s370( s306, v )	);
s1428.push_back( s1428[vt.s366( 0 )] );
s1725.push_back( vector<s1170>() );
return s1206;}
s1170 s509::s1153( const s867::Cont& v_ ){
assert( all_of( begin( v_ ), end( v_ ), [this]( s1170 t ) { return ( t <= s1217.size() ); } ) );
s867 vt( v_ );
s1170 s717 = 0;
auto it = s1218.find( vt );
if( it == s1218.end() ) {
wstring s1204 = s1111( v_ );
s717 = s1177( v_, s1204 );}
else
s717 = it->second;
return s717;}
uint32_t s1336( uint32_t n ){
for( n++ ; ; ++n ) {
uint32_t sqr = (uint32_t)sqrt( n ) + 1;
bool composite = false;
for( uint32_t k=2; k <= sqr; ++k ) {
double d = (double)n / k;
if( d == (int)d ) {
composite = true;
break;}}
if( !composite )
return n;}}
traitnum_t s509::s1403( const std::wstring& trait, s1170& s1684 ){
auto it = s977.find( trait );
if( it != end( s977 ) )
return it->second;
s1350 = s1336( s1350 );
s977[trait] = s1350;
s1410[s1350] = trait;
s1684 = s7::s1728 + (s1170)s1685.size();
s1685.push_back( s1350 );
return s1350;}
void s509::s1301( s867::s978 type, const wstring& trait, s1170& s1684 ){
traitnum_t tn;
auto it = s977.find( trait );
if( it == end( s977 ) ) {
tn = s1403( trait, s1684 );
s1428[type] *= tn;}
else {
tn = it->second;
if( !s1341( type, tn ) )
s1428[type] *= tn;}}
traitnum_t s509::s1632( s1170 alias ) const{
return s1685[alias - s7::s1728];}
bool s509::s1341( s1170 s646, traitnum_t tra ) {
double d = (double)s306->TR().s1294( s646 ) / tra;
return ( d == (int)d );}
bool s509::s1639( s1170 s646, s1170 alias ) {
double d = (double)s306->TR().s1294( s646 ) / 
s1685[alias-s7::s1728];
return ( d == (int)d );}
void s509::s1707( s1170 s646, s1170 is ){
s1725[s646].push_back( is );}
bool s509::s1708( s1170 s646, s1170 is ){
if( s646 == is )
return true;
if( s646 >= s1725.size() )
return false;
std::vector<s1170>& v = s1725[s646];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
void s509::s1312( const wstring& alias, const wstring& s361, 
const wstring& s2019 ){
assert( s1213.find( alias ) == end( s1213 ) );
s1170 typid;
auto it = s1213.find( s361 );
if( it == s1213.end() ) {
s867::Cont vt;
size_t pos = 0;
s1163( s361, pos, vt );
typid = s1153( vt );}
else
typid = it->second;	
s1212.push_back( alias );
s1229.push_back( s1229[typid] );
s1217.push_back( s1217[typid] );
s1428.push_back( s1428[typid] );
s1725.push_back( s1725[typid-1] );
s1213[alias] = typid;
auto it1 = s2020.find( s2019 );
if( it1 == s2020.end() )
it1 = s2020.insert( make_pair( s2019, list<wstring>() ) ).first;
it1->second.push_back( alias );}
void s509::s2057( const std::wstring& s1228 ){
auto it = s2020.find( s1228 );
if( it != s2020.end() ) {
for( auto it1 = it->second.begin(); it1 != it->second.end(); ++it1 ) {
s1213.erase( *it1 );}}}
wstring s509::s1429( const wstring& tn_ ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1213.find( s );
if( it == end( s1213 ) )
return tn_;
const wstring& tn = s1212[s1218[s1217[it->second]]];
if( tn != s ) {
wstring s717 = tn_;
return s717.replace( 0, s.size(), tn );}
return tn_;}
s501* s509::s541( const s269& s736, s278* s612, const wstring& s542 ){
if( s736.s1475() )
return s1229[s736.s1475()]->s369( s736, s612, s542 );
wstring s363 = s736.s297();
if( s363.substr(0,2) == L"[[" )
return s1229[s1213[s1048::proto->s368()]]->s369( s736, s612, s542 );
else if( s363[0] == L'[' )
return s1229[s1213[s323::proto->s368()]]->s369( s736, s612, s542 );
else if( s363.find( L"UVector[" ) == 0 )
return s1229[s1213[s792::proto->s368()]]->s369( s736, s612, s542 );
else if( s363[0] == L'{' )
return s1229[s1213[s332::proto->s368()]]->s369( s736, s612, s542 );
else if( s363.find( L"typealias" ) == 0 ) {
size_t pl = s363.find( L"(" );
wstring s361 = s4::s53( s363.substr( pl + 1, s363.size() - pl - 2 ), s4::s49 );
s1312( s736.s305(), s361, s542 );
return s1229[s1213[s374::proto->s368()]]->s369( s736, s612, s542 );}
wstring s361 = L"";
s501* s717 = NULL;
if( s4::s89.find( s363[0] ) != string::npos )
s361 = s374( s306 ).s368();
else if( isdigit( s363[0] ) || s363[0] == L'-' )
return s350::s359( s306, s363, s542 );
else if( ( s717 = s1229[s1274]->s369( s736, s612, s542 ) ) )
return s717;
else {
size_t pl = s363.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s361 = s363.substr( 0, pl );}
else if( pl == string::npos )
s361 = s363;}
auto it = s1213.find( s361 );
if( it == s1213.end() ) {
auto it1 = s977.find( s361 );
if( it1 == end( s977 ) )
throw new s16( L"Type does not exist: " + s363, (uint32_t)s16::s17::s23 );
return new s399( s306, it1->second, s1396 );}
return s1229[it->second]->s369( s736, s612, s542 );}
s501* s509::s541( s1170 s354, s278* s612, const wstring& s542 ){
if( !s354 || s354 >= s1212.size() )
throw new s16( L"no type with such id: " + to_wstring( s354 ) );
s1170 type = s354;
if( s1217[type].s366() != type )
type = s1217[type].s366();
if( s1217[s354].s875().size() == 1 )
return s1229[type]->s370( s612 );
else {
return s1229[type]->s370( s612, s1217[s354].s875() );}}
const s501* s509::get( const wstring& s77, bool s543/*= true*/ ) const
{
wstring s361 = s77;
size_t pl = s77.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s77.find( L"0" ) == string::npos )
s361 = s77.substr( 0, pl );
auto s717 = s1213.find( s361 );
if( s717 == s1213.end() ) {
if( s543 )
throw new s16( L"1: symbol not found: " + s77 );
else
return NULL;}
return s1229[s717->second].s15<const s501*>();}
bool s509::s159( const std::wstring& s77 ) const{
if( s1213.find( s77 ) == s1213.end() )
return false;
return true;}
const wstring& s509::s854( s1170 n ) const{
if( n >= s1212.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1212[n];}
s1170 s509::s1109( const std::wstring& s361, bool s543 ) const{
auto it = s1213.find( s361 );
if( it == s1213.end() ) {
if( s543 )
throw new s16( L"no such type: " + s361,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1170 s509::s1110( const s867& vt, bool s543 ) const{
auto it = s1218.find( vt );
if( it == end( s1218 ) ) {
if( s543 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s867& s509::s1112( s1170 t ) const{
assert( t && t < s1217.size() );
return s1217[t];}
const s501* s509::s1106( s867::s978 t ) const{
assert( t && t < s1217.size() );
return s1229[t].s15<const s501*>();}
void s509::s839(){
size_t s788 = s350::s858() + 1;
for( size_t n = s788; n < s1212.size(); ++n ) {
s1213.erase( s1212[n] );
s1218.erase( s1217[n] );
s1003.erase( (s1170)n );}
s1212.erase( s1212.begin() + s788, s1212.end() );
s1229.erase( s1229.begin() + s788, s1229.end() );
s1217.erase( s1217.begin() + s788, s1217.end() );}
bool s509::s1400(){
return rand() % 2;}
double s509::s1402(){
return rand() / RAND_MAX;
}
int s509::s1408(){
return rand();}
void s509::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s201 ) << L"Types :" << endl;
for( size_t n = 0; n < s1212.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s201 + 5 ) << s1212[n] << endl;
s1229[n]->s310( pd, s201 + 10 );}}
s500::s500( const s500& right )
: s576( right.s576 ), s560( right.s560 ), s562( right.s562 ){}
void s500::s519( s278* s960, bool s538/*= true*/ )
{
for( auto sym : s576 ) {
if( sym.second->s513() != s493 ) {
try {
sym.second->s519( s960 );}
catch( TDException* e ) {
e->s1186( TDException::Stage::s1132 );
s1114.s1064( e->Msg( 0 ) );
continue;}}}
if( s1114.s1020() )
return;
if( s538 ) {
for( auto sym : s576 ) {
if( sym.second->s513() == s493 )
sym.second.s15<Transd*>()->s519( s960, true );}}}
void s574::s1825( s268* s306 ){
for( auto sym : s582 ) {
if( sym.find( L"::" ) == string::npos )
s306->s1826( sym );}}
void s500::reset(){
s576.clear();}
void s500::copy( s500& t, s278* s612, s615* s611, s148 ap ) const{
t.s562 = s562;
for( s558::const_iterator it = s576.begin(); it != s576.end(); ++it ) {
if( it->second->s513() == s493 ) {
s615::s586 ct = it->second.s15<Transd*>()->s937();
assert( ct == s615::s591 || ct == s615::s590);
s910* ptr = new s910( *( s910* )&( *it->second ),
/*s612,*/ s611, std::vector<s277*>(), ct, 
it->second.s15<Transd*>()->s627(), s612 );
t.s564( it->first,  ptr, ap );}
else {
t.s564( it->first, it->second->s349(), ap );}}}
void s500::s571( s500& t ) const{
for( s558::const_iterator it = s576.begin(); it != s576.end(); ++it ) {
if( it->second->s513() == s493 )
t.s564( it->first, it->second.s15<s277*>() );
else
t.s564( it->first, it->second->s349() );}}
void s500::s1789( s500& t ) const{
for( s558::const_iterator it = s576.begin(); it != s576.end(); ++it ) {
if( it->second->s513() != s493 ) {
auto it1 = t.s576.find( it->first );
if( it1 == end( t.s576 ) )
t.s576[it->first] = it->second;
else
it->second.s15<s501*>()->s371( it1->second.s15<s277*>() );}}}
bool s500::s561( const std::wstring& s77, s148 ap /*= s149*/ )
{
if( s576.find( s77 ) != s576.end() ) {
wstring rep = s7::s436 + L" name already exists: " + s77;
if( ap == s149 || ap == s557 ) {
if( ap == s149 )
throw new TDException( 0, s1847, NULL, s77 );
return false;}
else if( ap == s151 ) {
return false;}}
return true;}
void s500::s564( const std::wstring& s77, s277* sym, s148 ap/*= s149*/ )
{
if( (ap == s150) || s561( s77, ap ) )
s576[s77] = sym;}
void s500::s564( const std::wstring& s77, s145 s363, s148 ap/*= s149*/ )
{
throw new s16( (uint32_t)s16::s17::s21 );}
void s500::s565( const std::wstring& s77 ){
auto it = s576.find( s77 );
if( it == s576.end() )
return;
s576.erase( it );}
void s500::s566( const s6::s146& s80, s148 ap/*= s149*/ )
{
vector<pair<wstring, s145>> s147;
s80.s163( s147 );
for( size_t n = 0; n < s147.size(); ++n )
s564( s147[n].first, s147[n].second );}
bool s500::s159( const std::wstring& s77 ) const{
if( s576.find( s77 ) == s576.end() )
return false;
return true;}
s501* s500::get( const wstring& s77, bool s543/*= true*/ ) const
{
auto s717 = s576.find( s77 );
if( s717 == s576.end() ) {
if( s543 )
throw new s16( L"2: symbol not found: " + s77 );
else
return NULL;}
return s717->second.s15<s501*>();}
void s500::s569( std::vector<std::wstring>& s156 ) const{
for( auto sym : s576 )
s156.push_back( sym.first );}
void s500::s567( vector<wstring>& s156 ) const{
for( auto sym : s576 ) {
if( sym.second->s513() == s493 )
s156.push_back( sym.first );}}
void s500::s568( vector<wstring>& s156 ) const{
for( auto sym : s576 ) {
if( sym.second->s513() == s491 ||
sym.second->s513() == s498 || sym.second->s513() == s497 )
s156.push_back( sym.first );}}
void s500::s570( const s500& t,
vector<wstring>& s156 ) const{
for( auto sym : s576 ) {
if( t.s159( sym.first ) )
s156.push_back( sym.first );}}
void s500::s295( const s500& t, s148 ap /*= s149*/ )
{
if( ap != s150 ) 
for( auto sym : t.s576 )
s561( sym.first, ap );
for( auto sym : t.s576 )
s564( sym.first, sym.second.s15<s501*>(), ap );}
void s500::s572( s533 pv, s269* s80 ){
if( !s562 )
s562 = new s549();
s562->s552( pv, s80 );}
void s500::s556( const wstring& s346, vector<wstring>& s156 ){
for( s558::iterator it = s576.begin(); it != s576.end(); ++it ) {
s533 pv = s534;
if( s562 )
pv = s562->s555( it->first, s346 );
if( pv == s534 ) {
if( s560 == s530 )
pv = s535;
else if( s560 == s532 )
pv = s536;
else {
if( it->second->s513() == s493 )
pv = s535;
else
pv = s536;}}
if( pv == s535 )
s156.push_back( it->first );}}
bool s500::s573( const std::wstring& s284,
const std::wstring& s346 ) const{
if( s562 ) {
s533 pv = s562->s555( s284, s346 );
if( pv == s535 )
return true;
else if( pv == s534 ) {
if( s560 == s530 )
pv = s535;
else if( s560 == s532 )
pv = s536;
else {
auto it = s576.find( s284 );
if( it == s576.end() )
throw new s16( L"1: Symbol does not exist: " + s284 );
size_t cat = it->second->s513();
if( cat == s493 || cat == s496 || cat == s498 )
return true;}}
return false;}
return true;}
void s500::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s201 ) << L"Symbols :" << endl;
s558::const_iterator it = s576.begin();
for( ; it != s576.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s310( pd, s201 + s434 * 2 );
buf << endl;}}}
wstring s500::to_wstring( uint32_t s1739 ) const{
std::wostringstream buf;
buf << endl << s4::fill_n_ch( L' ', 0 ) << L"Symbols :" << endl;
s558::const_iterator it = s576.begin();
for( ; it != s576.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s434 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s310( &buf, s434 * 2 );
buf << endl;}}
return buf.str();}
s574::s574(){}
void s574::s519( s268* s306, const wstring& s581 ){
s346 = s581;
for( size_t n = 0; n < s582.size(); ++n ) {
wstring s77 = s582[n];
vector<wstring> s156;
s306->s224( s77, s581, s156 );
for( size_t m = 0; m < s156.size(); ++m ) {
s77 = s77.substr( 0, s77.find( L"::" ) );
s576.insert( make_pair( s156[m], make_pair( (s501*)s306->s670( 
s582[n],	s581 ), s77) ) );}}}
void s574::s578( const wstring& s77, s268* s306, const wstring& s581 ){
s582.push_back( s77 );
vector<wstring> s156;
s306->s224( s77, s581, s156 );
for( size_t n = 0; n < s156.size(); ++n )
s576.insert( make_pair( s156[n], make_pair( (s501*)s306->s670( 
s77,	s581 ), s77 ) ) );}
void s574::s577( const std::wstring& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s16( L"Unrecognized import syntax: " + s );
s582.push_back( s.substr(1, s.size() - 2 ) );}
bool s574::s579( const std::wstring& sym, s386* ref ){
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );}
else
mem = sym;
size_t s716 = s576.count( mem );
if( !s716 )
return false;
if( s716 > 1 && mod.empty() )
throw new s16( L"ambiguous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s576.equal_range( mem );
if( s716 == 1 && mod.empty() ) {
s501* pd = range.first->second.first;
if( pd->s513() == s497 || pd->s513() == s496 )
return pd->s579( mem, ref, s346, true );
ref->s398( (s501*)pd->s523() );
ref->s397( pd );
return true;}
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod /*sym*/ ) {
s501* pd = it->second.first;
if( pd->s513() == s497 )
return pd->s579( mem, ref, L"", true );
ref->s398( (s501*)pd->s523() );
ref->s397( pd );
return true;}}
return false;}
void s574::copy( s574& t ) const{
for( s558::const_iterator it = s576.begin(); it != s576.end(); ++it )
t.s576.insert( make_pair( it->first, it->second ) );}
s544::s544( s533 pv_, const vector<wstring>& s546 )
: s545( s546 ), pv( pv_ ){}
s544::s544( const wstring& ag_, const wstring& s78 ){}
s533 s544::s583( const std::wstring& s518 ) const{
for( size_t n = 0; n < s545.size(); ++n )
if( s545[n] == s518 || s545[n] == L"_" )
return pv;
if( pv == s536 )
return s535;
return s536;}
void s549::s552( s533 pv, s269* s736 ){
s269::s281& s737 = s736->s299();
s269::s281::iterator it = s737.begin();
for( ; it != s737.end(); ++it ) {
wstring l = it->second->s297().substr( 1, it->second->s297().size() - 2 );
vector<wstring> s156;
wstring s73( s1234, 1 );
s4::s58( l, s73, s156 );
s551[it->first] = new s544( pv, s156 );}}
void s549::s553( const std::wstring& s, s544& pl ){}
void s549::s554( const std::wstring& s, const std::wstring& s547 ){}
s533 s549::s555( const std::wstring& mem, const std::wstring& s518 ){
s550::iterator it = s551.find( mem );
if( it == s551.end() )
return s534;
return it->second->s583( s518 );}
s1170 s1686::s1425 = 0;
s1170 s1686::s1723 = 0;
s350::s355 s399::s362;
s350::s355 s379::s362;
s350::s355 s376::s362;
s350::s355 s375::s362;
s350::s355 s360::s362;
s350::s355 s373::s362;
s350::s355 s1464::s362;
s350::s355 s1703::s362;
s350::s355 s1452::s362;
s350::s355 s1748::s362;
s350::s355 s1778::s362;
s350::s355 s374::s362;
s350::s355 s323::s362;
s350::s355 s792::s362;
s350::s355 s1048::s362;
s350::s355 s332::s362;
s350::s355 s1552::s362;
s350::s355 s1448::s362;
s350::s355 s430::s362;
s350::s355 s1462::s362;
s350::s355 s400::s362;
s350::s355 s1255::s362;
s350::s355 s1039::s362;
s350::s355 s1266::s362;
s350::s355 s1884::s362;
s350::s355 s679::s362;
s350::s355 s1980::s362;
s350::s355 s527::s362;
s350::s355 s1450::s362;
s350::s355 s1460::s362;
s350::s355 s1573::s362;
s350::s355 s1575::s362;
size_t s350::s802 = 0;
s9<s399> s827;
s9<s379> s779;
s9<s376> s874;
s504 s375::proto;
s504 s360::proto;
s504 s373::proto;
s504 s1464::proto;
s504 s1703::proto;
s504 s1452::proto;
s504 s1748::proto;
s504 s1778::proto;
s504 s374::proto;
s504 s1448::proto;
s504 s323::proto;
s504 s332::proto;
s504 s1552::proto;
s504 s1266::proto;
s504 s1884::proto;
s504 s792::proto;
s504 s1048::proto;
s504 s905::proto;
s504 s679::proto;
s504 s1980::proto;
s9<s430> s865;
s9<s1462> s1463;
s9<s400> s863;
s9<s1255> s1257;
s9<s1039> s1468;
s9<s527> s869;
s9<s1450> s1451;
s9<s1460> s1461;
s9<s379> s380;
s9<s399> s945;
s9<s399> s381;
s9<s399> s382;
s9<s399> s383;
s9<s399> s949;
s9<s399> s1863;
s9<s375> s384;
s9<s375> s385;
s9<s1573> s1574;
s9<s1575> s1576;
s9<s399> s1695;
template <class charT, charT s73>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s73; }
};
std::locale exprloc;
static s6::s1887 s1936;
s1898 s1916;
s6::s1873 s1914;
void s350::s833( s268* s306, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
if( !soft ) {
std::vector<s277*> l;
s827 = new s399( s306 );
s779 = new s379( s306 );
s375::proto = new s375( s306 );
s874 = new s376( s306 );
s360::proto = new s360( s306 );
s373::proto = new s373( s306 );
s1464::proto = new s1464( s306 );
s1703::proto = new s1703( s306 );
s1452::proto = new s1452( s306 );
s1748::proto = new s1748( s306 );
s1778::proto = new s1778( s306 );
s374::proto = new s374( s306 );
s1448::proto = new s1448( s306 );
s1266::proto = new s1266( s306 );
s1884::proto = new s1884( s306 );
s323::proto = new s323( s306 );
s332::proto = new s332( s306 );
s1552::proto = new s1552( s306 );
s792::proto = new s792( s306 );
s1048::proto = new s1048( s306 );
s1980::proto = new s1980( s306 );
s679::proto = new s679( s306 );
s863 = new s400( s306 );
s1257 = new s1255( s306 );
s1468 = new s1039( s306 );
s865 = new s430( s306 );
s905::proto = new s905( s306 );
s869 = new s527( s306 );
s1451 = new s1450( s306 );
s1461 = new s1460( s306 );}
s306->s223( s827, L"NoValue" );
s306->s223( s779, L"Null" );
s306->s223( s874, L"Exception" );
s306->s223( s375::proto, L"Bool" );
s306->s223( s360::proto, L"Int" );
s306->s223( s373::proto, L"Double" );
s306->s223( s1464::proto, L"Long" );
s306->s223( s1703::proto, L"ULong" );
s306->s223( s1452::proto, L"Byte" );
s306->s223( s1748::proto, L"Char" );
s306->s223( s1778::proto, L"Object" );
s306->s223( s1266::proto, L"Position" );
s306->s223( s1884::proto, L"DateTime" );
s306->s223( s323::proto, L"Vector" );
s306->s223( s792::proto, L"UntypedVector" );
s306->s223( s1048::proto, L"Tuple" );
s306->s223( s332::proto, L"Index" );
s306->s223( s1552::proto, L"HashIndex" );
s306->s223( s1448::proto, L"ByteArray" );
s306->s223( s865, L"Directory" );
s306->s223( s863, L"Range" );
s306->s223( s1257, L"Filter" );
s306->s223( s1468, L"Seq" );
s306->s223( s1980::proto, L"Table" );
s306->s223( s679::proto, L"TSDBase" );
s306->s223( s869, L"StringStream" );
s306->s223( s1451, L"ByteStream" );
s306->s223( s1461, L"FileStream" );
s306->s223( s905::proto, L"Lambda" );
s306->s223( s374::proto, L"String" );
if( !soft ) {
s802 = s374::proto->s366();
s380 = new s379( s306 );
s945 = new s399( s306, s499 );
s383 = new s399( s306, s499 );
s382 = new s399( s306, s499 );
s381 = new s399( s306, s499 );
s949 = new s399( s306, s499 );
s1863 = new s399( s306, s499 );
s384 = new s375( s306, true );
s385 = new s375( s306, false );
s945->s1855( s7::s939 );
s383->s1855( s7::s453 );
s382->s1855( s7::s454 );
s381->s1855( s7::s455 );
s384->s1411();
s385->s1411();
s1695 = new s399( s306, s1284, s1396 );}
s1914.s154 = true;
s1914.s1910 = true;
s1914.s1878 = true;
s1914.s1877 = true;
s1914.s1879 = true;}
s1238::s1238( const std::vector<s503>& v, s350* s616 )
:s612( s616 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s513() != s1172 ) {
s998.push_back( v[n] );
s1432.push_back( v[n]->s366() );}}}
bool s1238::operator==( const s1238& s547 ) const{
bool pend = s1432.empty();
bool send = s547.s1432.empty();
s1170 starred = 0;
size_t n = 0, k = 0;
bool s1421 = true;
s509* ptr = s547.s612 ? &s547.s612->Pass()->TR() : NULL;
while( !send || !pend ) {
s1421 = false;
s1170 s1319 = starred ? starred : (pend ? 0 : s1432[k]);
s1170 s1315 = send ? (s547.s1432.empty() ? 0 : s547.s1432[n-1]) : s547.s1432[n];
s277* s1711 = send ?
( s547.s998.empty() ? NULL : s547.s998[n - 1].s15<s277*>() ) :
s547.s998[n].s15<s277*>();
if( s1315 == s827->s366() )
s1315 = send ? s547.s998[n-1].s15<s399*>()->s1714() : 
s547.s998[n].s15<s399*>()->s1714();
const s867* s1436 = s547.s612 ? &s547.s612->s1339() : NULL;
if( s1319 >= s7::s1570 && s1319 < s7::s1728 && s1315 ) {
if( s1319 == s7::s1564 )
s1421 = true;
else if( s1319 == s7::s1569 ) {
s1170 pt1_ = s547.s998[n]->s1339().s366();
if( pt1_ == s1894 /*&& pt2_ == s1274*/ )
s1421 = true;}
else if( s1319 == s7::s1565 ) {
if( s547.s612 && s1315 == s547.s612->s366())
s1421 = true;}
else if( s1319 == s7::s1566 ) {
if( s547.s612 && s1315 == ( (s336*)s547.s612 )->s327() )
s1421 = true;}
else if( s1319 == s7::s1566 ) {
if( s547.s612 && s1315 == ((s336*)s547.s612)->s327() )
s1421 = true;}
else if( s1319 == s7::s1567 ) {
if( s547.s612 && s1315 == ((s336*)s547.s612)->s1023() )
s1421 = true;}
else if( s1319 == s7::s1568 ) {
if( s547.s612 && s1711->s1715( ((s336*)s547.s612)->ValType() ) )
s1421 = true;}
else if( s1436 &&	s1315 == s1436->s366( (size_t)((int)0 - s1319 )) )
s1421 = true;}
else if( s1319 >= s7::s1728 && ptr ) {
traitnum_t s1687 = ptr->s1632( s1319 );
if( s1315 && ptr->s1341( s1315, s1687 ) )
s1421 = true;}
else {
if( s1711 && s1711->s1715( s1319 ) )
s1421 = true;}
if( s1421 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s547.s1432.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1432.size() )
pend = true;
if( !starred && !pend && s1432[k] == s7::s1570 )
starred = s1432[k - 1];}
return s1421;}
bool s1238::operator<( const s1238& s547 ) const{
if( s1432.empty() ) return s547.s1432.size() > 0;
if( s547.s1432.empty() ) return false;
const s867* s1435 = s612 ? &s612->s1339() : NULL;
const s867* s1436 = s547.s612 ? &s547.s612->s1339() : NULL;
s1170 s1419 = 0, s1420 = 0;
s509* ptr = s547.s612 ? &s547.s612->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1432.size() && n < s547.s1432.size()*/; ++n ) {
if( s1432.size() == n )
return s547.s1432.size() > n;
if( s547.s1432.size() == n )
return false;
s1170 s1317 = s1419 ? s1419 : s1432[n];
s1170 s1320 = s1420 ? s1420 : s547.s1432[n];
if( s1317 >= s7::s1570 && s1317 <= s7::s1728 ) {
if( s1317 == s7::s1570 )
s1317 = s1419 = s1432[n - 1];
else if( s1317 == s7::s1564 )
continue;
else if( s1317 == s7::s1565 ) {
if( !s547.s612 )
return true;
s1317 = s547.s612->s366();}
else if( s1317 == s7::s1566 ) {
if( !s547.s612 )
return true;
s1317 = ( (s336*)s547.s612 )->s327();}
else if( s1435 )
s1317 = s1435->s366( (size_t)(int)0 - s1317 );}
else if( s1317 >= s7::s1728 && ptr ) {
traitnum_t s1687 = ptr->s1632( s1317 );
if( ptr->s1341( s1320, s1687 ) )
return true;}
if( s1320 >= s7::s1570 && s1320 <= s7::s1728 ) {
if( s1320 == s7::s1570 )
s1320 = s1420 = s547.s1432[n - 1];
else if( s1320 == s7::s1564 )
continue;
else if( s1320 == s7::s1565 ) {
if( !s612 )
return true;
s1320 = s612->s366();}
else if( s1320 == s7::s1566 ) {
if( !s612 )
return true;
s1320 = ( (s336*)s612 )->s327();}
else if( s1436 )
s1320 = s1436->s366( (size_t)(int)0 - s1320 );}
else if( s1320 >= s7::s1728 && ptr ) {
traitnum_t s1687 = ptr->s1632( s1320 );
if( ptr->s1341( s1317, s1687 ) )
return true;}
if( s1317 < s1320 )
return true;}
return false;}
wstring s1238::s1495( s268* s306 ) const{
wstring s717 = L"( ";
for( auto i : s1432 ) {
s717 += s306->TR().s854( i );
if( s717.back() != L')' ) s717 += L"()";
s717 += L" ";}
s717 += L")";
return s717;}
bool
s350::s351::s1306( /*s350* thi,*/ const s1238& s723 ) const
{
return std::find( s1302.begin(), s1302.end(), s723 ) != end( s1302 );}
s1170
s350::s401( const std::wstring& s357 ) const{
auto it = s356().find( s357 );
if( it == s356().end() )
throw new s16( L"No such operation: " + s368() +	L"::" + s357,
(uint32_t)s16::s17::s23 );
s1170 s717 = it->second->s514();
return s717;}
const s501*
s350::s523() const{
return (s501*)s306->TR().s1106( s366() );}
const vector<wstring>& 
s350::s1334( const wstring& s357 ) const{
auto ran = s356().equal_range( s357 );
if( ran.first == s356().end() )
throw new s16( L"No such method: " + s368() + L"::" + s357,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1265 s350::s1340( const std::wstring& s357 ) const{
s350::s351* s717 = NULL;
auto it = s356().find( s357 );
if( it != s356().end() )
s717 = it->second;
return s717 ? s1265( s717->s514(), s717->s1258(), s717->s1347() ) : s1265();}
s1265
s350::s1335( const wstring& s357, s1238& ap /*const vector<s1170>& s1388*/ ) const
{
auto ran = s356().equal_range( s357 );
if( ran.first == s356().end() )
throw new s16( L"No such method: " + s368() + L"::" + s357,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1329() )
throw new s16( L"", (uint32_t)s351::s1254::s1322 );
s351* s717 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1306( ap ) ) {
s717 = it->second;
break;}}
return s717 ? s1265( s717->s514(), s717->s1258(), s717->s1347() ) : s1265();}
s1265
s350::s1330( const wstring& s357, s1238& ap/*const vector<s1170>& s1388,
const vector<s503>& s280*/ )
{
auto ran = s356().equal_range( s357 );
s351* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1306( ap ) ) {
mi = it->second;
break;}}
s1265 s1385( mi->s514(), mi->s1258(), mi->s1347() );
if( mi )
s1385.s352 = ap.Subj()->s1331( s357, ap.s626() );
return s1385;}
s504 s350::s516( s501** s280, size_t s517 ){
return this;}
void s350::s1709( s501* p ){}
s501* s350::s359( s268* s306, const std::wstring& s363, const std::wstring& s346 ){
s269 s212( s363, NULL );
s501* s717 = NULL;
double dval;
size_t pos = 0;
s6::s134 s202 = s1936.s1724( s363, pos, dval );
if( s202 != s6::s134::s143 && s202 != s6::s134::s139 )
return NULL;
if( s363.find( L"." ) != std::string::npos )
s717 = s373::proto.s15<s373*>()->s369( s212, NULL, s346 );
else {
s717 = s360::proto.s15<s360*>()->s369( s212, NULL, s346 );
if( !s717 ) {
if( !s717 )
s717 = s1464::proto.s15<s1464*>()->s369( s212, NULL, s346 );
if( !s717 )
s717 = s1452::proto.s15<s1452*>()->s369( s212, NULL, s346 );}}
return s717;}
#define s733 ((s360*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
s501* s373::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
1/*s.find( L"." ) != std::string::npos*/ ) {
size_t pos = 0;
return new s373( s306, s, pos );}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s373( s306, s4::s53( s.substr( 7, s.size() - 8 ), s4::s49 ),
pos );}
else if( s.find( L"Double" ) == 0 ) {
return s370( s612, std::vector<s277*>(), &s736 );}
return 0;}
void s360::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s363;}
s373::s373( s268* s306, double d ) 
: s350( s306, NULL, NULL ), s363( d ){
if( s373::proto.s13() ) {
s512 = 0;
wh = s7::s941;}
else {
s512 = s373::proto->s366();
wh = s7::s940;}}
s373::s373( const s373& r )
: s350( r.s306, r.ns, r.s627() ), s363( r.s363 ){
wh = r.wh;
s512 = r.s512;}
s373::s373( s268* s306, const std::wstring& s, size_t& pos )
: s350( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
double s156 = 0.0;
if( !s.empty() ) {
pst = s.c_str();
if( !s64( pst, &s156, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1855( s7::s940 );}
else
s156 = s306->TR().s1402();
s363 = s156;
pos = pend ? pend - pst : string::npos;
s512 = s373::proto->s366();}
s501* s373::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s373( s306, L"", pos );}
void s373::s519( const s278*, bool ){}
void s373::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s373::s1384, s1283,
{ s1238(), s1238( { s1288 } ), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"abs", new s351( L"abs", &s373::s419, s1283,
{ s1238( ) }, 0, 0 )));
s362.insert( make_pair( L"set", new s351( L"set", &s373::s402, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"sum", new s351( L"sum", &s373::s403, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"dif", new s351( L"dif", &s373::s404, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"mul", new s351( L"mul", &s373::s405, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"div", new s351( L"div", &s373::s406, s1283,
{ s1238( { s1686::s1425 } ) }, 1, 1 )));
s362.insert( make_pair( L"pow", new s351( L"pow", &s373::s407, s1283,
{ s1238( { s1686::s1425 } ) }, 1, 1 )));
s362.insert( make_pair( L"sumeq", new s351( L"sumeq", &s373::s408, s1283,
{ s1238( { s1283 } ), s1238( { s1284, s7::s1570 } ) }, 1, 10 )));
s362.insert( make_pair( L"difeq", new s351( L"difeq", &s373::s409, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"muleq", new s351( L"muleq", &s373::s410, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"diveq", new s351( L"diveq", &s373::s411, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"poweq", new s351( L"poweq", &s373::s412, s1283,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"sqrt", new s351( L"sqrt", &s373::s421, s1283,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"nroot", new s351( L"nroot", &s373::s422, s1283,
{ s1238( { s1284 } ) }, 1, 1 )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s373::s413, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"less", new s351( L"less", &s373::s414, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"greater", new s351( L"greater", &s373::s415, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"leq", new s351( L"leq", &s373::s416, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"geq", new s351( L"geq", &s373::s417, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"neq", new s351( L"neq", &s373::s418, s1274,
{ s1238( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"dcmp", new s351( L"dcmp", &s373::s425, s1284,
{ s1238( { s1283, s1283 } ) }, 2, 2 )));
s362.insert( make_pair( L"dcmpr", new s351( L"dcmpr", &s373::s426, s1284,
{ s1238( { s1283, s1283 } ) }, 2, 2 )));
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s373::s427, s1284,
{ s1238(), s1238( { s1284 } ) }, 0, 1 )));
s306->TR().s1301( s512, s7::s1584, s1686::s1425 );}
s277* s373::s349() const{
return new s373( *this );}
void s373::s371( s277* p ) const{
if( p->s366() == s360::proto->s366() )
*( (s360*)p )->s372() = (int)s363;
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = ( s363 != 0.0 );
else
throw new s16( L"No conversion to type " + s368() );}
std::wstring s373::to_wstring( uint32_t s1739 ) const{
wstring s = std::to_wstring( s363 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
return s.substr(0, pl);}
#undef s733
#define s733 ((s373*)(s502*)*s280)
#define INTRES ((s360*)(s502*)*s280)
inline void s373::s1384( s501** s280, size_t s517 ){
s373* plv = NULL;
if( s517 == 3 && s280[2]->s366() == s1288 ) {
size_t pos = 0;
plv = new s373( ((s373*)s280[1] )->s306, *((s374*)s280[2])->s372(), pos );}
else {
plv = new s373( ( (s373*)s280[1] )->s306, 0.0 );
s373& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if( s517 == 3 ) {
s501* p = s280[2];
if( p->s366() == s1283 )
lv.s363 = *( (s373*)p )->s372();
else if( p->s366() == s1284 )
lv.s363 = (s1557)*( (s360*)p )->s372();
else if( p->s366() == s1274 )
lv.s363 = ( s1557 )*( (s375*)p )->s372();
else
throw new s16( L"no conversion to Double from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Double() constructor" );}
plv->s1413();
s280[0] = plv;}
inline void s373::s402( s501** s280, size_t s517 ){
( (s373*)DR )->s363 = (double)*PARN( 2 );}
void s373::s419( s501** s280, size_t s517 ){
double t = (double)*DR;
if( t >= 0 )
s733->s363 = t;
else
s733->s363 = -t;}
inline void s373::s405( s501** s280, size_t s517 ){
s733->s363 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
s733->s363 *= (double)*PARN( n );}
inline void s373::s403( s501** s280, size_t s517 ){
s733->s363 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
s733->s363 += (double)*PARN( n );}
inline void s373::s406( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (s373*) DR )->s363 / s733->s363;
}
inline void s373::s404( s501** s280, size_t s517 ){
s733->s363 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
s733->s363 -= (double)*PARN( n );}
inline void s373::s408( s501** s280, size_t s517 ){
s373* pd = (s373*) s280[1];
for( size_t n = 2; n < s517; ++n ) {
s501* p = s280[n];
if( p->s366() == s1283 )
pd->s363 += *( (s373*)p )->s372();
else if( p->s366() == s1284 )
pd->s363 += ( s1557 )*( (s360*)p )->s372();}
s733->s363 = ( (double)*DR );}
inline void s373::s409( s501** s280, size_t s517 ){
( (s373*)DR )->s363 -= (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
( (s373*)DR )->s363 -= (double)*PARN( n );
s733->s363 = ( (double)*DR );}
inline void s373::s410( s501** s280, size_t s517 ){
( (s373*)DR )->s363 *= (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
( (s373*)DR )->s363 *= (double)*PARN( n );
s733->s363 = ( (double)*DR );}
inline void s373::s411( s501** s280, size_t s517 ){
( (s373*)DR )->s363 /= (double)*PARN( 2 );
for( size_t n = 3; n < s517; ++n )
( (s373*)DR )->s363 /= (double)*PARN( n );
s733->s363 = ( (double)*DR );}
inline void s373::s412( s501** s280, size_t s517 ){
( (s373*)DR )->s363 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s517; ++n )
( (s373*)DR )->s363 = ::pow( (double)*DR, (double)*PARN( n ) );
s733->s363 = ( (double)*DR );}
inline void s373::s413( s501** s280, size_t s517 ){
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s414( s501** s280, size_t s517 ){
if( ((double)*DR) < (double)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s415( s501** s280, size_t s517 ){
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s416( s501** s280, size_t s517 ){
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s417( s501** s280, size_t s517 ){
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s418( s501** s280, size_t s517 ){
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s373::s421( s501** s280, size_t s517 ){
s733->s363 = ::sqrt((double)*DR);}
inline void s373::s422( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s373::s425( s501** s280, size_t s517 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s372() = 0;
else
*INTRES->s372() = 1;}
else {
if( dr - dl <= diff )
*INTRES->s372() = 0;
else
*INTRES->s372() = -1;}}
inline void s373::s426( s501** s280, size_t s517 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s372() = 0;
else
*INTRES->s372() = 1;}
else {
if( dr / dl - 1 <= diff )
*INTRES->s372() = 0;
else
*INTRES->s372() = -1;}}
inline void s373::s407( s501** s280, size_t s517 ){
s733->s363 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );}
inline void s373::s427( s501** s280, size_t s517 ){
int s1497 = -1;
if( s517 == 3 )
s1497 = (int)*s280[2];
double dv = ( (s373*)DR )->s363;
int s717 = (int)dv;
if( s1497 < 0 )
*( (s360*)s280[0] )->s372() = s717;
else if( s1497 == 0 ) 
*( (s360*)s280[0] )->s372() = (dv - s717 > 0.5 ? s717 + 1 : s717);
else
*( (s360*)s280[0] )->s372() = s717 + 1;}
void s373::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s363;}
size_t s373::s330() const{
return hash<double>{}( s363 );}
inline
int dcmp( double d1, double d2, int iDigs ){
double s88 = fabs( d1 - d2 );
double prec = 1 / pow( (double)10.0, iDigs );
if ( s88 < prec )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline
int dcmp_( double d1, double d2, double dif ){
double s88 = fabs( d1 - d2 );
if ( s88 < dif )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline bool s373::operator==( const s501* p ) const{
return ( dcmp_( ( (s373*)p )->s363, s363, 0.00000001 ) == 0 ); // FIX:
}
inline bool s373::operator<( const s501* p ) const{
return ( dcmp_( s363, ( (s373*)p )->s363, 0.00000001 ) < 0 ); // FIX:
}
s375::s375( s268* s306, const std::wstring& s, size_t& pos )
: s350( s306, NULL, NULL ){
if( s.empty() )
s363 = s306->TR().s1400();
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s363 = (s[0] == L'1');
pos++;}
else if( s.find( s7::s451 ) == 0 ) {
s363 = true;
pos += 4;}
else if( s.find( s7::s452 ) == 0 ) {
s363 = false;
pos += 5;}
else
throw new s16( L"unknown bool format: " + s.substr( 0, 20 ) );
if( !s.empty() )
s1855( s7::s940 );
s512 = s1274;}
s375::s375( const s375& right )
: s350( right.s306, right.ns, NULL ), s363( right.s363 ){
s512 = s1274;
wh = right.wh;}
s375::s375( s268* s306, bool b )
: s350( s306, NULL, NULL ), s363( b ){
if( s375::proto.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = s1274;
s1855( s7::s940 );}}
void s375::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s375::s402, s1286,
{ s1238( { s1274 } ) }, 1, 1, false )));
s362.insert( make_pair( L"new", new s351( L"new", &s375::s1384, s1274,
{ s1238(), s1238( { s1274 } ), s1238( { s1288 } ), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"not", new s351( L"not", &s375::s428, s1274,
{ s1238( ) }, 0, 0, true )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s375::s413, s1274,
{ s1238( { s1274 } ) }, 1, 1, true )));}
void s375::s519( const s278* s960, bool ){
s1413();}
s501* s375::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s375( s306, false );}
s501* s375::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s4::s53( s736.s297(), s4::s49 );
if( s.find( s7::s451 ) == 0 || s.find( s7::s452 ) == 0 )
return new s375( s306, ( s.find( s7::s451 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s375( s306, 
s4::s53( s.substr( 5, s.size() - 6 ), s4::s49 ), pos );}
else if( s.find( L"Bool" ) == 0 ) {
return s370( s612, std::vector<s277*>(), &s736 );}
return NULL;}
s277* s375::s349() const{
return new s375( *this );}
void s375::s371( s277* p ) const{
if( p->s366() == s1274 )
((s375*)p)->s363 = s363;
else if( p->s366() == s360::proto->s366() )
*( (s360*)p )->s372() = (int)s363;
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"No conversion to type " + s368() );}
#undef s733
#define s733 ((s375*)(s502*)*s280)
inline void s375::s1384( s501** s280, size_t s517 ){
s375* plv = new s375( ( (s375*)s280[1] )->s306, 0 );
s375& lv = *plv;
if( s517 == 2 )
lv.s363 = false;
else if( s517 == 3 ) {
s501* p = s280[2];
if( p->s366() == s1284 )
lv.s363 = *( (s360*)p )->s372() != 0;
else if( p->s366() == s1283 )
lv.s363 = *( (s373*)p )->s372() != 0.0;
else if( p->s366() == s1274 )
lv.s363 = *( (s375*)p )->s372();
else if( p->s366() == s1288 )
lv.s363 = ( (s374*)p )->s372()->size() > 0;
else
throw new s16( L"no conversion to Bool from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Bool() constructor" );
lv.s1413();
s280[0] = plv;}
inline void s375::s402( s501** s280, size_t s517 ){
( (s375*)DR )->s363 = ( (s375*)PARN( 2 ) )->s363;}
inline void s375::s428( s501** s280, size_t s517 ){
s733->s363 = !( (s375*)DR )->s363;}
inline void s375::s413( s501** s280, size_t s517 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
void s375::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << to_wstring()
<< L" (" << std::hex << &s363 << L")";}
size_t s375::s330() const{
return hash<bool>{}( s363 );}
inline bool s375::operator==( const s501* p ) const{
return ( s363 == ((s375*)p)->s363 );}
inline bool s375::operator<( const s501* p ) const{
return ( s363 < ((s375*)p)->s363 );}
s376::s376( s268* s306, const std::wstring& s/* = std::wstring( L"" )*/ )
: s350( s306, NULL, NULL ), s79( s ){
wh = s7::s455;
s512 = s874.s13() ? 0 : s874->s366();}
s376::s376( const s376& r )
: s350( r.s306, NULL, NULL ), s79( r.s79 ){
s512 = r.s512;
wh = r.wh;}
void s376::s364(){
s362.insert( make_pair( L"report", new s351( L"report", &s376::s842, s1286,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"str", new s351( L"str", &s376::s528, s1288,
{ s1238() }, 0, 0 )));}
void s376::s519( const s278* s960, bool ){}
s501* s376::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s376( s306 );}
s277* s376::s349() const{
return new s376( *this );}
void s376::s371( s277* p ) const{
((s376*)p)->s79 = s79;}
s501* s376::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find( L"Exception(" ) == 0 )
return new s376( s306, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s370( s612, std::vector<s277*>(), &s736 );
return NULL;}
#undef s733
#define s733 ((s376*)(s502*)*s280)
inline void s376::s842( s501** s280, size_t s517 ){
wcout << ( (s376*)DR )->s79;}
inline void s376::s528( s501** s280, size_t s517 ){
*( (s374*)s280[0] )->s372() = ( (s376*)DR )->s79;}
void s376::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : -";}
size_t s376::s330() const{
throw new s16( L"9: not implemented" );}
bool s376::operator==( const s501* p ) const{
return ( (s376*)p )->s79 == s79;}
bool s376::operator<( const s501* p ) const{
return s79 < ( (s376*)p )->s79;}
s379::s379( s268* s306 ) 
: s350( s306, NULL, NULL ){
if( s779.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = s779->s366();
s1855( s7::s940 );}}
void s379::s519( const s278* s960, bool ){}
s501* s379::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s379( s306 );}
s501* s379::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find( L"Null" ) == 0 )
return s380;
return NULL;}
s277* s379::s349() const{
return (s277*)this;}
void s379::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : -";}
size_t s379::s330() const{
return 0xfeeb1e;}
bool s379::operator==( const s501* p ) const{
return ( this == p );}
bool s379::operator<( const s501* p ) const{
return false;}
s399::s399( s268* s306, traitnum_t tn, s489 pc ) 
: s350( s306, NULL, NULL ), s1426( tn ){
s511 = pc;
s512 = s827.s13() ? 0 : s827->s366(); }
void s399::s519( const s278* s960, bool ){}
s501* s399::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s399( s306 );}
s501* s399::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
throw new s16( L"no parser for NoValue" );
return NULL;}
s277* s399::s349() const{
return (s277*)this;}
inline bool
s399::s521( const s501* s522 ) const{
return s306->TR().s1341( s522->s366(), s1426 );}
inline bool
s399::s1715( s1170 s646 ) const{
return s306->TR().s1708( s1426, s646 );}
void s399::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : -" << endl;}
size_t s399::s330() const{
throw new s16( L"not implemented" );}
bool s399::operator==( const s501* p ) const{
return false;}
bool s399::operator<( const s501* p ) const{
return false;}
s1884::s1884( s268* s306 ) 
: s350( s306, NULL, NULL ), s1921( s1919 ) {
if( s1884::proto.s13() )
s512 = 0;
else
s512 = s1891;
s1855( s7::s941 );}
s1884::s1884( s268* s306, const std::wstring& s )
: s350( s306, NULL, NULL ){
if( !s1906( s, s363, s1921 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s2054 = s1974::from_time_t ( std::mktime( &s363 ) );
s512 = s1891;
s1855( s7::s940 );}
s1884::s1884( const s1884& right )
: s350( right.s306, right.ns, NULL ), s363( right.s363 ), s2054( right.s2054 ){
s512 = right.s512;
wh = right.wh;}
s1884::s1884( s268* s306, const std::tm& _t, s1883 s646 )
: s350( s306, NULL, NULL ), s1921( s646 ), s363( _t ){
s512 = s1891;
s2054 = s1974::from_time_t ( std::mktime( &s363 ) );
s1855( s7::s940 );}
wregex s1884::s1943( LR"regex(^\"?(\d\d\d\d-\d\d?-\d\d?)\"?$)regex" );
wregex s1884::s2042( LR"regex(^(\d+)(\.\d+)?$)regex" );
bool s1884::s1906( const std::wstring& s363, std::tm& t, s1883& s646 ){
wsmatch s1183;
s646 = s1919;
if( regex_match( s363, s1183, s1943 ) ) {
std::wistringstream ss( s1183[1] );
ss >> std::get_time( &t, L"%Y-%m-%d" );
if( ss.fail() )
return false;
s646 = s1917;}
else if( regex_match( s363, s1183, s1943 ) ) {}
else
return false;
return true;}
void s1884::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s1884::s402, s1286,
{ s1238( { s1891 } ), s1238( { s1288 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"new", new s351( L"new", &s1884::s1384, s1891,
{ s1238(), s1238( { s1891 } ), s1238( { s1288 } ), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"not", new s351( L"not", &s1884::s428, s1274,
{ s1238() }, 0, 0, true ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s1884::s413, s1274,
{ s1238( { s1891 } ) }, 1, 1, true ) ) );
s362.insert( make_pair( L"now-delta", new s351( L"now-delta", &s1884::s2028, s1283,
{ s1238( ) }, 0, 0, true ) ) );
s362.insert( make_pair( L"set-now", new s351( L"set-now", &s1884::s2052, s1891,
{ s1238( ) }, 0, 0, false ) ) );}
void s1884::s519( const s278* s960, bool ){
s1413();}
s501* s1884::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1884( s306 );}
s501* s1884::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s4::s53( s736.s297(), s4::s49 );
if( s.find( L"DateTime(" ) == 0 )
s = s.substr( 9, s.size() - 10 );
if( s.empty() )
return new s1884( s306 );
std::tm t = {};
s1883 s646;
if( s1906( s, t, s646 ) )
return new s1884( s306, t, s646 );
return NULL;}
s277* s1884::s349() const{
return new s1884( *this );}
void s1884::s371( s277* p ) const{
if( p->s366() == s1891 )
( (s1884*)p )->s363 = s363;
else
throw new s16( L"No conversion to type " + s368() );}
void s1884::s1946( const std::wstring& s ){
std::tm t = {};
s1883 s646;
if( !s1906( s, t, s646 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1921 = s646;
s363 = t;
s1855( s7::s940 );}
#undef s733
#define s733 ((s1884*)(s502*)*s280)
inline void s1884::s1384( s501** s280, size_t s517 ){
s1884* s717 = NULL;
if( s517 == 2 )
s717 = new s1884( ( (s1884*)s280[1] )->s306 );
else if( s517 == 3 ) {
s501* p = s280[2];
if( p->s366() == s1891 )
s717 = new s1884( *(s1884*)s280[2] );
else if( p->s366() == s1288 )
s717 = new s1884( ( (s1884*)s280[1] )->s306, s280[2]->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to DateTime() constructor" );
s280[0] = s717;}
inline void s1884::s402( s501** s280, size_t s517 ){
s501* p = s280[2];
if( p->s366() == s1891 ) {
( (s1884*)DR )->s363 = ( (s1884*)p )->s363;
( (s1884*)DR )->s1921 = ( (s1884*)p )->s1921;
( (s1884*)DR )->wh = ( (s1884*)p )->wh;}
else if( p->s366() == s1288 )
( (s1884*)DR )->s1946( p->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s368() );}
inline void s1884::s428( s501** s280, size_t s517 ){
*s734->s372() = !(( (s1884*)DR )->s1921 == s1919);}
inline void s1884::s413( s501** s280, size_t s517 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s734->s372() = 1;
else
*s734->s372() = 0;}
inline void s1884::s2052( s501** s280, size_t s517 ){
s1884* p = (s1884*)DR;
p->s2054 = s1974::now();
time_t t = s1974::to_time_t( p->s2054 );
#ifdef WIN32
localtime_s( &p->s363, &t );
#else
p->s363 = *localtime( &t );
#endif
p->s1921 = s1918;}
inline void s1884::s2028( s501** s280, size_t s517 ){
s1884* p = (s1884*)DR;
std::chrono::duration<double> delta = s1974::now() - p->s2054;
*((s373*)s280[0])->s372() = delta.count();}
void s1884::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << to_wstring()
<< L" (" << std::hex << &s363 << L")";}
size_t s1884::s330() const{
std::tm t = s363;
return hash<time_t>{}( std::mktime( &t ) );}
inline bool s1884::operator==( const s501* p ) const{
return memcmp( &s363, &((s1884*)p )->s363, sizeof(tm) );}
inline bool s1884::operator<( const s501* p ) const{
tm t = s363, t1 = ( (s1884*)p )->s363;
return ( std::mktime( &t ) < std::mktime( &t1 ) );}
wstring s1884::to_wstring( uint32_t s1739 ) const{
wstring s717;
if( s1921 == s1917 || s1921 == s1918 ) {
s717 = std::to_wstring( 1900 + s363.tm_year ) + L"-";
if( s363.tm_mon < 9 )
s717 += L"0";
s717 += std::to_wstring( 1 + s363.tm_mon ) + L"-";
if( s363.tm_mday < 10 )
s717 += L"0";
s717 += std::to_wstring( s363.tm_mday );}
if( s1921 == s1918 )
s717 += L" ";
if( s1921 == s1920 || s1921 == s1918 ) {
if( s363.tm_hour < 10 )
s717 += L"0";
s717 += std::to_wstring( s363.tm_hour ) + L":";
if( s363.tm_min < 10 )
s717 += L"0";
std::to_wstring( s363.tm_min ) + L":";
if( s363.tm_sec < 10 )
s717 += L"0";
std::to_wstring( s363.tm_sec );}
return s717;}
s1778::s1778( s268* s306, s278* s612, const std::wstring& s78, const s269* ast_ )
: s350( s306, s612, ast_ ){
if( s78.size() ) {
load( s78, false );}
if( !s512 )
s512 = ( s1778::proto.s13() ? 0 : s1778::proto->s366() );
if( !s78.empty() )
s1855( s7::s940 );}
s1778::s1778( s268* s306, s278* s612, const s146* s1820, const s269* ast_ )
: s350( s306, s612, ast_ ){
if( s1820->s159( s7::s480 ) ) {
wstring sname = s4::s53( s269::s308( *s1820, s7::s480 ),
s49 );
(( s146*)s1820)->s162( L"name", new s144( sname ) );
(( s146*)s1820)->s1807( s7::s480 );}
s1818( s1820, s500::s149 );}
s1778::s1778( const s1778& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s655( right.s655 ){
s512 = s1778::proto->s366();}
void s1778::s364(){
s362.insert( make_pair( L"get-Int", new s351( L"get-Int", &s1778::s1812, s1284,
{ s1238( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"get-String", new s351( L"get-String", &s1778::s1813, s1288,
{ s1238( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"load", new s351( L"load", &s1778::s1817, s1286,
{ s1238( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"load-from-file", new s351( L"load-from-file", &s1778::s1815, s1286,
{ s1238( { s1288 } ), s1238( { s1288, s1288 } ) }, 1, 2, true )));}
void s1778::s519( const s278* s960, bool ){}
s501* s1778::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1778( s306 );}
s501* s1778::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find( L"Object(" ) == 0 ) {
return new s1778( s306, s612, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s370( s612, std::vector<s277*>(), &s736 );}
return NULL;}
s1170 s1778::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get" ) {
auto it = s655.get( l[0]->to_wstring() );
s717 = it->s366();}
return s717;}
void s1778::load( const wstring& s78, bool s1810 ){
TDException s1059( s7::s1774, s1018, s627(), L"Failed to load object" );
s1035 s1158 = new s1032( s78, s1810 );
vector<s9<s146>> s692;
s1158->read( s692, L"" );
if( s692.size() != 1 )
throw s1059.s1097( L"wrong object data: the source contains " + std::to_wstring( s692.size() ) + L"objects"  );
s146* obj = s692[0];
if( obj->s159( s7::s480 ) ) {
wstring sname = s4::s53( s269::s308( *obj, s7::s480 ),
s49 );
obj->s162( L"name", new s144( sname ) );}
s1818( obj );}
void s1778::s1818( const s146* obj, s500::s148 ap ){
vector<pair<wstring, s145>> s147;
obj->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1034 past = new s269( s147[n].first, *s147[n].second );
s501* dv = s306->TR().s541( *past, (s278*)this, L"::" );
dv->s526( s147[n].first );
dv->s1413();
s655.s564( s147[n].first, dv, ap );}}
void s1778::s1808( s500::s558& sm ) const{
const s500::s558& tb = s655.Table();
s500::s558::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s513() == s493 )
(void)0;
else {
s501* dv = (s501*)it->second->s349();
sm.insert( make_pair( it->first, dv ));}}}
s277* s1778::s349() const{
return new s1778( *this );}
void s1778::s371( s277* p ) const{
if( p->s366() == s1778::proto->s366() )
((s1778*)p)->s655 = s655;
else
throw new s16( L"No conversion to type " + s368() );}
#undef s733
#define s733 ((s1778*)(s502*)*s280)
inline void s1778::s1812( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
*((s360*)*s280)->s372() = (int)*( (s1778*)DR )->s655.get( s155 );}
inline void s1778::s1813( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
*((s374*)*s280)->s372() = ( (s1778*)DR )->s655.get( s155 )->to_wstring();}
inline void s1778::s1836( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
s360* pd  = (s360*)( (s1778*)DR )->s655.get( s155 );
*pd->s372() = (int)*s280[3];}
inline void s1778::s1838( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
s374* pd  = (s374*)( (s1778*)DR )->s655.get( s155 );
*pd->s372() = s280[3]->to_wstring();}
inline void s1778::s1817( s501** s280, size_t s517 ){
s1778* po = (s1778*)DR;
wstring s78 = s280[2]->to_wstring();
po->load( s78, false );}
inline void s1778::s1815( s501** s280, size_t s517 ){
s1778* po = (s1778*)DR;
wstring s193 = s280[2]->to_wstring();
po->load( s193, true );}
void s1778::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << to_wstring();}
size_t s1778::s330() const{
return (size_t)this; //hash<bool>{}( s363 );
}
inline bool s1778::operator==( const s501* p ) const{
return this == p; // ( s655 == ( (s1778*)p )->s655 );
}
inline bool s1778::operator<( const s501* p ) const{
return this < p; // ( s655 < ( (s1778*)p )->s655 );
}
wstring s1778::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"Object: { \n";
s717 += s655.to_wstring( s1739 );
s717 += L"\n }";
return s717;}
s386::s386( const std::wstring& s, s268* s306, s489 cat, bool _cnst )
: s502( s306, cat ), s387( s ), s391( 0 ), s1308( _cnst ){
assert( cat == s490 || cat == s492 || cat == s499 || cat == s1172 );
if( cat == s490 ) {
if( 0 && s[0] == L':' ) {
s511 = s1172;
s512 = s827->s366();
s388 = s827.s15<s501*>();}
else if( /*s388.s14() &&*/ s306->s226( *this ) ){
s511 = s499;
s512 = s827->s366();}
else
s511 = s492;}}
s386::s386( const s386& right )
: s502( right.s306, right.s511 ), s387( right.s387 ), s389( right.s389 ), 
s391( 0 ), s1308( right.s1308 ){
if( s511 == s499 )
s388 = right.s388;}
void s386::s519( const s278* s611, bool fr ){
if( false && s306->s226( *this ) ) {
s511 = s499;
s512 = s827->s366();}
else {
if( !s611->s579( s387, this, s611->s898(), fr ) ) {
if( s511 == s1172 )
return;
throw new TDException( 0, s1016, NULL, s387 );}
if( s389 )
s512 = s389->s366();
else if( s511 == s1504 )
s512 = s388.s15<s386*>()->s392()->s366();
else
assert( 0 );}
s1413();}
s501* s386::s392() const{
if( s511 == s1172 )
return s388.s15<s501*>();
else if( s511 == s1504 )
return s388.s15<s386*>()->s392();
if( s390.empty() )
return s388.s15<s501*>();
s502* s717 = s388.s15<s278*>()->s622( *(size_t*)&s390[0] );
for( size_t n = 1; n < s391; ++n )
s717 = ((s278*)s717->s515())->s622( *( (size_t*)&s390[0] + n ) );
return s717->s515();}
s501* s386::s393(){
if( s390.empty() )
return s388.s15<s501*>();
s501*	s717 = ((s501*)s388.s15<s278*>()->s622( *(size_t*)&s390[0] ));
for( size_t n = 1; n < s391; ++n )
s717 = (s501*)((s278*)s717)->s622( *( (size_t*)&s390[0] + n ) );
return s717;}
void s386::s1077( const std::vector<std::wstring> &s876 ){
auto it = std::find( begin( s876 ), end( s876 ), s643() );
if( it != end( s876 ) ) {
s511 = s1172;
s512 = s827->s366();
s391 = std::distance( begin( s876 ), it );
s388 = new s360( NULL, (int)s391 ); //s827.s15<s501*>();
}}
s504 s386::s516( s501** s280, size_t s517 ){
return s392()->s516( s280, s517 );}
s501* s386::s515(){
return s392()->s515();}
/*bool s386::s521( const s501* s522 ) const
{
if( s522->s513() == s492 )
return s392()->s521( ((s386*)s522)->s392() );
return s392()->s521( s522 );
}*/
s277* s386::s349() const{
return new s386( *this );}
void s386::s394( size_t off, const s501* proto ){
s390.push_back( off );
s391 = s390.size();
s389 = proto;}
void s386::s1510( s386* ptr ){
s511 = s1504;
s390.clear();
s391 = 0;
s388 = ptr;
s389 = NULL;}
void s386::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"DataRef : " << s387;}
template<class s1478, class Der>
s350::s355 s1470<s1478, Der>::s362;
template<class s1478, class Der>
const s350::s355& s1470<s1478, Der>::s356() const{
return s362; }
template<class s1478, class Der>template <class s1704, class s1705>
void s1470<s1478, Der>::s1706( s501* src, s501* s826 ){
*((s1704*)s826)->s372() = (s1705) ( (Der*)src )->s363;}
template <class s1478, class Der>
s501* s1470<s1478, Der>::s1710( const s501* p ) const{
Der* s717 = new Der( p->Pass() );
if( p->s1715( s366() ) )
p->s371( s717 );
s717->s1413();
return s717;}
template <class s1478, class Der>
size_t s1470<s1478, Der>::s330() const{
return (size_t)s363;}
template <class s1478, class Der>
inline bool s1470<s1478, Der>::operator==( const s501* p ) const{
return ( (Der*)p )->s363 == s363;}
template <class s1478, class Der>
inline bool s1470<s1478, Der>::operator<( const s501* p ) const{
return s363 < ( (Der*)p )->s363;}
template <class s1478, class Der>
void s1470<s1478, Der>::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s363 << endl;}
#define s1699 Der::proto->s366()
template <class s1478, class Der>
void s1470<s1478, Der>::s364(){
s362.insert( make_pair( L"abs", new s351( L"abs", &s1470<s1478, Der>::s419, s1699,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s1470<s1478, Der>::s402, s1699,
{ s1238( { /*Der::proto->s366()*/ s1686::s1425 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"sum", new s351( L"sum", &s1470<s1478, Der>::s403, s1699,
{ s1238( { s1686::s1723, s7::s1570 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"dif", new s351( L"dif", &s1470<s1478, Der>::s404, s1699,
{ s1238( ), s1238( { s1686::s1425 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"mul", new s351( L"mul", &s1470<s1478, Der>::s405, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"div", new s351( L"div", &s1470<s1478, Der>::s406, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"pow", new s351( L"pow", &s1470<s1478, Der>::s407, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"pow", new s351( L"pow", &s1470<s1478, Der>::s407, s1283,
{ s1238( { s1283 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"sumeq", new s351( L"sumeq", &s1470<s1478, Der>::s408, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"difeq", new s351( L"difeq", &s1470<s1478, Der>::s409, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"muleq", new s351( L"muleq", &s1470<s1478, Der>::s410, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"diveq", new s351( L"diveq", &s1470<s1478, Der>::s411, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"not", new s351( L"not", &s1470<s1478, Der>::s428, s1274,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s1470<s1478, Der>::s413, s1274,
{ s1238( { s1686::s1723, s7::s1570 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"less", new s351( L"less", &s1470<s1478, Der>::s414, s1274,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"greater", new s351( L"greater", &s1470<s1478, Der>::s415, s1274,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"leq", new s351( L"leq", &s1470<s1478, Der>::s416, s1274,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"geq", new s351( L"geq", &s1470<s1478, Der>::s417, s1274,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"neq", new s351( L"neq", &s1470<s1478, Der>::s418, s1274,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"mod", new s351( L"mod", &s1470<s1478, Der>::s420, s1699,
{ s1238( { s1686::s1723 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"sqrt", new s351( L"sqrt", &s1470<s1478, Der>::s421, s1283,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"nroot", new s351( L"nroot", &s1470<s1478, Der>::s422, s1283,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"to-Double", new s351( L"to-Double", &s1470<s1478, Der>::s423, s1283,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Byte", new s351( L"to-Byte", &s1470<s1478, Der>::s1772, s1474,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s1470<s1478, Der>::s427, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Long", new s351( L"to-Long", &s1470<s1478, Der>::s1721, s1700,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-ULong", new s351( L"to-ULong", &s1470<s1478, Der>::s1722, s1701,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s1470<s1478, Der>::s424, s1699,
{ s1238() }, 0, 0, false ) ) );}
template<class s1478, class Der>
s1170 s1470<s1478, Der>::
s1331( const std::wstring& s1727, const std::vector<s503>& l ) const{
s1170 s717 = 0;
if( 0 && s1727 == L"mod" )
s717 = this->s366();
return s717;}
#undef s733
#define s733 ((Der*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
template<class s1478, class Der>
inline void s1470<s1478, Der>::s402( s501** s280, size_t n ){
s280[2]->s371( s280[1] );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s419( s501** s280, size_t s517 ){
s1478 t = ( (Der*)DR )->s363;
if( t >= 0 )
s733->s363 = t;
else
s733->s363 = -t;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s403( s501** s280, size_t s517 ){
Der tmp;
s733->s363 = ( (Der*)DR )->s363;
for( size_t n = 2; n < s517; ++n ) {
s280[n]->s371( &tmp );
s733->s363 += tmp.s363;}}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s404( s501** s280, size_t s517 ){
if( s517 == 2 )
s733->s363 = -( (Der*)DR )->s363;
else {
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 - s733->s363;}}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s405( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 * s733->s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s406( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 / s733->s363;
}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s407( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 =(s1478) std::pow( (double)( (Der*)DR )->s363, (double)s733->s363 );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s408( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 += s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s409( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 -= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s410( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 *= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s411( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 /= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s413( s501** s280, size_t s517 ){
bool s717 = true;
Der tmp;
for( size_t i = 2; i < s517; ++i ) {
s280[i]->s371( &tmp );
if( ( (Der*)DR )->s363 != tmp.s363 ) {
s717 = false;
break;}}
*s734->s372() = s717;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s428( s501** s280, size_t s517 ){
if( ((bool)( (Der*)DR )->s363) == false )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s414( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 < tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s415( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 > tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s416( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 <= tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s417( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 >= tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = true;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s418( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 != tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s420( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( tmp.s363 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s733->s363 = ((Der*)DR)->s363 % tmp.s363;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s421( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = ::sqrt( (double)*DR );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s422( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = ::pow( ((Der*)DR)->s363, 1.0 / (double)*PARN( 2 ) );
}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s423( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = (double)*DR;}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s1772( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s427( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s1721( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s1722( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s1675( s501** s280, size_t s517 ){
*( (s374*)s280[0] )->s372() = DR->to_wstring();}
template<class s1478, class Der>
inline void s1470<s1478, Der>::s424( s501** s280, size_t s517 ){
int i;
wstring s95 = L"";//( (s374*)s280[2] )->to_wstring();
wstring si = consutils::s103( s95, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s733->s363 = i;}
s360::s360( s268* s306 )
: s1470( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1557)s306->TR().s1408();
s1855( s7::s941 );}
s360::s360( s268* s306, int i )
: s1470( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
wh = s7::s941;}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s360::s360( const s360& r )
: s1470( r ){}
s360::s360( s268* s306, const std::wstring& s, size_t& pos )
: s1470( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s63( pst, &s156, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1413();}
else
s156 = s306->TR().s1408();
s363 = (int)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
s501* s360::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
s501* s717 = NULL;
size_t pos = 0;
if( s.find( L"Int(" ) == 0 ) {
s717 = new s360( s306, s.substr( 4, s.size() - 5 ), pos );}
else if( s.find( L"Int" ) == 0 ) {
s717 = s370( NULL, std::vector<s277*>(), &s736 );}
else {
if( s == L"-0" )
return s1695;
try {
s717 = new s360( s306, s, pos );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
s717 = NULL;
else
throw e;}}
return s717;}
void s360::s364(){
s306->TR().s1301( s512, s7::s1584, s1686::s1425 );
s306->TR().s1301( s512, s7::s1698, s1686::s1723 );
s1470<int32_t, s360>::s364();
s362 = s1470<int32_t, s360>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s360::s1384, s1284,
{ s1238(), s1238( { s1288 } ), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1707( s512, s1464::proto->s366() );}
s501* s360::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s360( s306, L"", pos );}
void s360::s519( const s278* s960, bool ){}
inline bool
s360::s1715( s1170 s646 ) const{
if( ( s646 == s1701 && s363 >= 0 ) ||
( s646 == s1474 && s363 >= 0 && s363 <= 255 ) )
return true;
return s277::s1715( s646 );}
s277* s360::s349() const{
return new s360( *this );}
void s360::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s360*)p)->s372() = s363;
else if( p->s366() == s1474 )
*((s1452*)p)->s372() = s363;
else if( p->s366() == s1700 )
*((s1464*)p)->s372() = s363;
else if( p->s366() == s1701 )
*((s1703*)p)->s372() = s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"No conversion to type " + p->s368() );}
inline void s360::s1384( s501** s280, size_t s517 ){
s360* plv = NULL;
if( s517 == 3 && s280[2]->s366() == s1288 ) {
size_t pos = 0;
plv = new s360( ( (s360*)s280[1] )->s306, *( (s374*)s280[2] )->s372(), pos );}
else {
plv = new s360( ( (s360*)s280[1] )->s306, 0 );
s360& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if( s517 == 3 ) {
s501* p = s280[2];
if( p->s366() == s1284 )
lv.s363 = *( (s360*)p )->s372();
else if( p->s366() == s1283 )
lv.s363 = ( s1557 )*( (s373*)p )->s372();
else if( p->s366() == s1274 )
lv.s363 = ( s1557 )*( (s375*)p )->s372();
else
throw new s16( L"no conversion to Int from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Int() constructor" );}
plv->s1413();
s280[0] = plv;}
wstring s360::to_wstring( uint32_t s1739 ) const {
wstring s717;
if( s363 > 0 && ( s1739 & s1734 ) )
s717 = L"+";
if( s1739 & s1733 )
s717 += s4::s1738( s363 );
else
s717 += std::to_wstring( s363 ); 
return s717;}
void s360::to_null(){
s277::to_null();
s363 = 0;}
s1464::s1464( s268* s306 )
: s1470( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = s306->TR().s1408();
s1855( s7::s941 );}
s1464::s1464( s268* s306, int64_t i )
: s1470( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1464::s1464( const s1464& r )
: s1470( r ){}
s1464::s1464( s268* s306, const std::wstring& s, size_t& pos )
: s1470( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1718( pst, &s156, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1413();}
else
s156 = s306->TR().s1408();
s363 = (int64_t)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1464::s364(){
s1470<int64_t, s1464>::s364();
s362 = s1470<int64_t, s1464>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1464::s1384, s1700,
{ s1238(), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1584, s1686::s1425 );
s306->TR().s1301( s512, s7::s1698, s1686::s1723 );}
s501* s1464::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1464( s306, L"", pos );}
void s1464::s519( const s278* s960, bool ){}
s277* s1464::s349() const{
return new s1464( *this );}
void s1464::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s1464*)p)->s372() = s363;
else if( p->s366() == s1284 )
*((s360*)p)->s372() = (s360::s1557)s363;
else if( p->s366() == s1701 )
*((s1703*)p)->s372() = s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1464::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1464( s306, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1464( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1464::s1384( s501** s280, size_t s517 ){
s1464* plv = new s1464( ( (s1464*)s280[1] )->s306, (s1557)0 );
s1464& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if (s517 == 3){
s501* p = s280[2];
if( p->s366() == s360::proto->s366() )
lv.s363 = *( (s360*)p )->s372();
else if( p->s366() == s1283 )
lv.s363 = (s1557)*( (s373*)p )->s372();
else if( p->s366() == s1274 )
lv.s363 = (s1557)*( (s375*)p )->s372();
else
throw new s16( L"no conversion to Long from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1413();
s280[0] = plv;}
wstring s1464::to_wstring( uint32_t s1739 ) const{
wstring s717;
if( s363 > 0 && ( s1739 & s1734 ) )
s717 = L"+";
if( s1739 & s1733 )
s717 += s4::s1738( s363 );
else
s717 += std::to_wstring( s363 );
return s717;}
s1703::s1703( s268* s306 )
: s1470( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = s306->TR().s1408();
s1855( s7::s941 );}
s1703::s1703( s268* s306, int64_t i )
: s1470( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1703::s1703( const s1703& r )
: s1470( r ){}
s1703::s1703( s268* s306, const std::wstring& s, size_t& pos )
: s1470( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1719( pst, &s156, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1413();}
else
s156 = s306->TR().s1408();
s363 = (uint64_t)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1703::s364(){
s1470<s1557, s1703>::s364();
s362 = s1470<s1557, s1703>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1703::s1384, s1701,
{ s1238(), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"abs", new s351( L"abs", &s1703::s419, s1701,
{ s1238(), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"dif", new s351( L"dif", &s1703::s404, s1701,
{ s1238(), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1584, s1686::s1425 );
s306->TR().s1301( s512, s7::s1698, s1686::s1723 );}
s501* s1703::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1703( s306, L"", pos );}
void s1703::s519( const s278* s960, bool ){}
s277* s1703::s349() const{
return new s1703( *this );}
void s1703::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s1703*)p)->s372() = s363;
else if( p->s366() == s1700 )
*((s1464*)p)->s372() = s363;
else if( p->s366() == s1284 )
*((s360*)p)->s372() = (s360::s1557)s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1703::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1703( s306, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1703( s306, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1703::s1384( s501** s280, size_t s517 ){
s1703* plv = new s1703( ( (s1703*)s280[1] )->s306, (s1557)0 );
s1703& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if (s517 == 3){
s501* p = s280[2];
if( p->s366() == s360::proto->s366() )
lv.s363 = *( (s360*)p )->s372();
else if( p->s366() == s1464::proto->s366() )
lv.s363 = *( (s1464*)p )->s372();
else if( p->s366() == s1283 )
lv.s363 = (s1557)*( (s373*)p )->s372();
else if( p->s366() == s1274 )
lv.s363 = (s1557)*( (s375*)p )->s372();
else
throw new s16( L"no conversion to ULong from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1413();
s280[0] = plv;}
wstring s1703::to_wstring( uint32_t s1739 ) const{
wstring s717;
if( s363 > 0 && ( s1739 & s1734 ) )
s717 = L"+";
if( s1739 & s1733 )
s717 += s4::s1738( s363 );
else
s717 += std::to_wstring( s363 );
return s717;}
s1452::s1452( s268* s306 )
: s1470( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1557)s306->TR().s1408();
s1855( s7::s941 );}
s1452::s1452( s268* s306, tdbyte_t i )
: s1470( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1452::s1452( const s1452& r )
: s1470( r.s306, r.ns, NULL ){
wh = r.wh;
s512 = r.s512;}
s1452::s1452( s268* s306, const std::wstring& s, size_t& pos )
: s1470( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s63( pst, &s156, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1855( s7::s940 );}
else
s156 = s306->TR().s1408();
s363 = (int)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1452::s364(){
s1470<tdbyte_t, s1452>::s364();
s362 = s1470<tdbyte_t, s1452>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1452::s1384, s1474,
{ s1238(), s1238( { s1686::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1584, s1686::s1425 );
s306->TR().s1301( s512, s7::s1698, s1686::s1723 );}
s501* s1452::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1452( s306, L"", pos );}
void s1452::s519( const s278* s960, bool ){}
s277* s1452::s349() const{
return new s1452( *this );}
void s1452::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s360*)p)->s372() = s363;
else if( p->s366() == s1700 )
*((s1464*)p)->s372() = s363;
else if( p->s366() == s1701 )
*((s1703*)p)->s372() = s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1452::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1452( s306, s, pos );
}*/
if( s736.s1475() == s366() )
return new s1452( s306, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1452( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1452::s1384( s501** s280, size_t s517 ){
s1452* plv = new s1452( ( (s1452*)s280[1] )->s306, 0 );
s1452& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if( s517 == 3 )
s280[2]->s371( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1413();
s280[0] = plv;}
s1748::s1748( s268* s306 )
: s1470( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1557)s306->TR().s1408();
s1855( s7::s941 );}
s1748::s1748( s268* s306, wchar_t i )
: s1470( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1855( s7::s941 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1748::s1748( const s1748& r )
: s1470( r.s306, r.ns, NULL ){
wh = r.wh;
s512 = r.s512;}
s1748::s1748( s268* s306, const std::wstring& s, size_t& pos )
: s1470( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s63( pst, &s156, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1855( s7::s940 );}
else
s156 = s306->TR().s1408();
s363 = (int)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1748::s364(){
s1470<wchar_t, s1748>::s364();
s362 = s1470<wchar_t, s1748>::s356();}
s501* s1748::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1748( s306, L"", pos );}
void s1748::s519( const s278* s960, bool ){}
s277* s1748::s349() const{
return new s1748( *this );}
void s1748::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*( (s360*)p )->s372() = s363;
else if( p->s366() == s1700 )
*( (s1464*)p )->s372() = s363;
else if( p->s366() == s1701 )
*( (s1703*)p )->s372() = s363;
else if( p->s366() == s1274 )
*( (s375*)p )->s372() = ( s363 != 0 );
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1748::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1452( s306, s, pos );
}*/
if( s736.s1475() == s366() )
return new s1748( s306, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1748( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
const wstring s488 = L"";
s500 s719;
s278::s278( s268* s306, s1170 s354, s489 pc/* = s490*/, const s269* ast_ )
: s501( s306, pc, ast_, NULL ), s652(NULL), s653(NULL), 
s1839( s7::s1777, s306, s492 ), s361( s488 ), //s661( s719 ),
s656( NULL )//, s1530( ++s1531 )
{
s652 = this;
s512 = s354;}
s278::s278( const s278& proto, std::vector<s503>& s740, const s269* ast_ )
: s501( proto.s306, s498, ast_, proto.ns ), s652( &proto ), s653(NULL), 
s1839( s7::s1777, s306, s492 ), s361( proto.s361 ),
s656( proto.s656 ), //s661( s719 ),
s658( proto.s658 )//, s1530( ++s1531 )
{
s512 = proto.s512;
if( s511 == s496 )
s511 = s498;
if( proto.s653 )
proto.s653->s672( this );
proto.s655.copy( s655, this, NULL, s500::s150 );
for( size_t n = 0; n < s658.size(); ++n )
s657.push_back( s655.get( s658[n].s643() ) );
if( s740.size() ) {
s910* p = (s910*) s655.get( s7::s444 );
p->s620( s740 );
p->s519( this, false );
p->s516( 0, 0 );}}
s278::s278( const wstring& s708, s268* s306, s489 pc, const s269* ast_ )
: s501( s306, pc, ast_, NULL ), s652(NULL), s653(NULL), 
s1839( s7::s1777, s306, s492 ), s361( s488 ), s284( s708 ),
s656( NULL )//, s1530( ++s1531 )//, s661( *new s500() )
{
s652 = this;}
s278::s278( s269& s736, s268* s306, s489 pc, s278* ns_, s559 am,
s650& cl, s649& cnl, s651& al )
: s501( s306, pc, &s736, ns_ ), s652(NULL), s653( NULL ), 
s1839( s7::s1777, s306, s492 ), s361( s736.s305() ), s284( s736.s304() ),
s655( am ), s656( NULL )//, s1530( ++s1531 ) //,s661( *new s500() )
{
if( s284.find( L" " ) != string::npos )
throw new s16( L"Malformed class name: " + s284 );
s652 = this;
if( pc == s496 ) {
wstring anc = L"";
try {
const s269* s725 = s736.s298( s7::s485 );
anc = s725->s297();}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw e;}
cnl.push_back( make_pair( s736.s305(), anc ) );
if( cl.find( s736.s305() ) != cl.end() )
throw new s16( L"class already exists: " + s736.s305() );
cl.insert(make_pair(s736.s305(), this));}
if( al.find( s736.s305() ) != al.end() )
throw new s16( L"object already exists: " + s736.s305() );
al.insert(make_pair(s736.s305(), &s736));
s526( L"proto" );
s269::s281& s737 = s736.s299();
s269::s281::iterator it = s737.begin();
vector<pair<wstring,wstring>> s726;
for( ; it != s737.end(); ++it ) {
if( it->second->s303() == s230 ) {
if( it->first == s7::s485 ) {
s654 = it->second->s297();}}
else if( it->second->s303() == s232 ) {
wstring s687 = it->first;
s533 pv = s536;
am = s531;
size_t s721 = s687.find_first_of( s4::s49 );
if( s721 != string::npos ) {
vector<wstring> s720;
s4::s58( it->first, wstring( 1, s687[s721] ), s720 );
if( s720.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
if( s720[0] == s7::s466 || s720.size() == 3 ) {
pc = s496;
if( s720.size() == 3 ) {
if( s720[0] == s7::s463 )
am = s530;
else if( s720[0] == s7::s465 )
am = s532;
else if( s720[0] != s7::s464 )
throw new s16( L"invalid access mode name: " + it->first );
s687 = s720[2];}
else
s687 = s720[1];
if( s737.find( s687 ) != s737.end() )
throw new s16( L"duplicated object name: " + it->first );
it->second->s300( s687 );
s726.push_back( make_pair( it->first, s687 ) );}
else if( s720[0] == L"access" && ( s720[1] == L"allow" || s720[1] == L"deny" )) {
if( s720[1] == L"allow" )
pv = s535;
pc = s497;}
else
throw new s16( L"unknown object type: " + s720[0] );}
if( pc == s497 ) {
s655.s572( pv, it->second );}
else {
s278* ob = new s278( *it->second, s306, s496, this, am, cl, cnl, al );
s655.s564( ob->s305(), ob );}}}
for( size_t n = 0; n < s726.size(); ++n ) {
auto it = s737.find( s726[n].first );
s737.insert(make_pair(s726[n].second, it->second ));
s737.erase( it );}}
s278::~s278(){}
s501* s278::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return s663( s736, s612, s346 );}
void s278::s673( const s500& s280 ){}
bool
s278::s521( const s501* s522 ) const{
if( s522->s366() == s366() )
return true;
if( s653 )
return s653->s521( s522 );
return false;}
bool
s278::s768( const wstring& f ) const{
return s655.s159( f );}
void s278::s157( s269& s736 ){
s269::s281& s737 = s736.s299();
s269::s281::iterator it = s737.begin();
for( ; it != s737.end(); ++it ) {
s269* node = it->second;
if( node->s303() == s230 ) {
wstring s77 = node->s305();
if( s77 == s7::s458 )
s674( *node );
else if( s77 == s7::s485 )
s666( *node );
else if( s77 == s7::s1022 )
s1063( *node );
else {
size_t s721 = s77.find_first_of( s4::s49 );
bool s1347 = false;
if( s721 != string::npos ) {
vector<wstring> s720;
s4::s58( s77, wstring( 1, s77[s721] ), s720 );
if( s720.size() > 2 )
throw new s16( L"malformed object declaration: " + s77 );
if( s720[0] == s7::s1262 ) {
s1347 = true;
s77 = s720[1];}
node->s300( s77 );}
lang::s685( s77 );
s501* dv = NULL;
try {
dv = s306->TR().s541( *node, this, s284 );}
catch( s16* e ) {
e->s30( L"while constructing object member: " + s77 );
throw e;}
dv->s526( node->s305() );
try {
s655.s564( node->s305(), dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s284 + L"::" + node->s305() );}
throw e;}
s657.push_back( dv );
s658.push_back( s386( node->s305(), s306, s492, s1347 ) );}}
else if( node->s303() == s232 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s278* ob = (s278*)s655.get( it->first );
ob->s157( *it->second );}}
else if( node->s303() == s233 ) {
s501* dv = new s374( s306, node->s297(), this, node );
dv->s526( node->s305() );
dv->s1411( true );
wstring s1850 = node->s305();
if( node->s305() == s7::s480 )
s1850 = L"name";
try {
s655.s564( s1850, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s284 + L"::" + node->s305() );}
throw e;}
s657.push_back( dv );
s658.push_back( s386( s1850, s306 ) );}}
it = s737.begin();
for( ; it != s737.end(); ++it ) {
s269* node = it->second;
if( node->s303() == s231 ) {
try {
s506 func = s615::s623( *node, s306, this,
node->s305(), s284 );
s655.s564( func->s305(), func.s15<s501*>() );
s657.push_back( func );
s658.push_back( s386( func->s305(), s306 ) );}
catch( TDException* e ) {
e->s1186( TDException::Stage::s1131 );
e->s30( L"while compiling function '" +s284 + L"::" + node->s305() + L"'" );
s1114.s1064( e->Msg( 0 ) );}}}
if( s511 == s496 ) {
s1526* s1534 = new s1526( s306, this, NULL, NULL );
s655.s564( s7::s1524, s1534 );
s657.push_back( s1534 );
s658.push_back( s386( s7::s1524, s306 ) );}}
void s278::s519( const s278* s960, bool ){
if( s511 == s496 || s511 == s497 ) {
if( s654.size() ) {
s653 = (s278*)s306->s227( s654, s960->s898() );
s653->s656->copy( *s656 );}
if( s656 )
s656->s519( s306, s284 );
else
s656 = s652->s656;
s655.s519( /*s960*/this, (s511 == s496));
}
else {
if( s306->s1496() && s655.s159( s7::s444 ) ) {
vector<s502*> s280;
s280.push_back( this );
s910* p = (s910*) s655.get( s7::s444 );
if( p->s644() == s7::s941 )
p->s519( s960, true );
else
p->s621( s960 );
if( s513() == s498 )
p->s516( (s501**)&s280[0], 1 );}
s656 = s652->s656;}
ns = (s278*)s960;}
void s278::s1825(){
if( s513() != s497 || s644() == s7::s940 )
return;
if( s655.s159( s7::s443 ) ) {
vector<s503> s280;
s280.push_back( this );
s910* p = (s910*) s655.get( s7::s443 );
p->s519( (s278*)ns, true );
p->s620( s280 );
p->s516( (s501**)&s280[0], 1 );}
if( s656 ) 
s656->s1825( s306 );
s1413();}
void s278::s672( s278* s675 ) const{
if( s653 )
s653->s672( s675 );}
void s278::s674( s269& s736 ){
if( !s656 )
s656 = new s574();
s656->s577( s736.s297() );
return;}
void s278::s667( const wstring& s346,	vector<wstring>& s156 ){
s655.s556( s346, s156 );}
void s278::s578( const wstring& s77, const wstring& s581 ){
if( !s656 )
s656 = new s574();
s656->s578( s77, s306, s581 );}
void s278::s666( s269& s736 ){
s653 = (s278*)s306->s227( s654, s284 );}
void s278::s1063( s269& s736 ){
wstring s1092 = L"wrong syntax of class attributes: " + s736.s297();
s504 dv = s306->TR().s541( s736, this, s284 );
if( dv->s366() != s1897 )
throw new s16( s1092 );
vector<s503>& v = dv.s15<s323*>()->s328();
for( auto s_ : v ) {
wstring s = s_.s15<s374*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s1092 );
wstring cat = s4::s53( s.substr( 0, pl ), s4::s49 );
vector<wstring> s156;
s4::s58( s.substr( pl + 1 ), L",", s156 );}}
bool s278::s579( const wstring& sym_, s386* ref, const wstring& s346,
bool fr ) const{
bool s717 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s718 = sym_.substr( 0, pl );
s278* ob = ((s278*)s670( s718, s346, false ));
if( !ob && s718 == s7::s1777 )
ob = (s278*)this;
if( ob ) {
s386 s1834( *ref );
s717 = ob->s579( sym, &s1834, s346, fr );
if( s717 ) {
if( !ref->s395() )
ref->s397( ( s501* )this );
ref->s394( s668( s718 ), ob );
ob->s579( sym, ref, s346, fr );}}
else {
if( s656 )
s717 = s656->s579( sym_, ref );}}
else {
const s278* ob = ((s278*)s670( sym, s346, false ));
if( ob ) {
if( !ref->s395() )
ref->s397( ( s501* )this );
size_t off = s668( sym );
ref->s394( off, ob );
if( s658[off].s1347() )
ref->s1411();
s717 = true;}
else {
if( sym == s7::s1777 ) {
ob = this;
if( !ref->s395() )
ref->s397( ( s501* )this );
ref->s394( s1270, ob );
s717 = true;}
else if( s656 )
s717 = s656->s579( sym, ref );}}
return s717;}
size_t s278::s668( const std::wstring& s676 ) const{
if( s676 == s7::s1777 )
return s1270;
for( size_t n = 0; n < s657.size(); ++n ) {
if( s658[n].s643() == s676 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s676 );}
s277* s278::s622( size_t off ){
if( off == s1270 )
return this;
return s657[off];}
void s278::s920( const std::wstring& s77, s501* s363, s500::s148 ap ){
s655.s564( s77, s363, ap );
s657.push_back( s363 );
s658.push_back( s386( s77, s306 ) );}
void s278::s1833( const std::wstring& s77, s501* s363 ){
if( !s655.s159( s77 ) )
throw new s16( L"no such member: " + s77 );
s655.s564( s77, s363, s500::s150 );
for( size_t n = 0; n < s658.size(); ++n ) {
if( s658[n].s643() == s77 )
s657[n] = s363;}}
void s278::s1816( const s1778* ob ){
s657.clear();
s652->s655.s1789( s655 );
for( size_t n = 0; n < s658.size(); ++n )
s657.push_back( s655.get( s658[n].s643() ) );
s500::s558 sm;
ob->s1808( sm );
s500::s558::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s655.s564( it->first, it->second.s15<s501*>(), s500::s150 );
else {
if( !s655.s159( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
it->second.s15<s501*>()->s371( s655.get( it->first ) );}}
for( size_t n = 0; n < s658.size(); ++n )
s657[n] = s655.get( s658[n].s643() );}
s501* s278::s670( const wstring& sym, const wstring& s346, 
bool s543/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s278* mod = (s278*) s655.get( smod, s543 );
if( !mod )
return NULL;
return mod->s670( sym1, s346, s543 );}
wstring sym1 = sym;
if( sym.size() > 2 && ( sym.find( L"()" ) == sym.size() - 2 ) )
sym1 = sym.substr( 0, sym.size() - 2 );
s504 s717 = s655.get( sym1, false );
if( !s717 && s543 )
throw new s16( L"4: Symbol does not exist: " + sym, 
(uint32_t)s16::s17::s23 );
if( s717 && !s671( sym1, s346 ) && (s346 != L":::") ) {
if( s543 )
throw new s16( L"4: Symbol not found: " + sym,
(uint32_t)s16::s17::s23 );
s717 = NULL;}
return s717;}
bool s278::s671( const wstring& sym, const wstring& s518 ) const{
if( s518 == s361 )
return true;
return s655.s573( sym, s518 );}
s1170 s278::s401( const wstring& s357 ) const{
s501* s722 = s655.get( s357 );
s1170 s717 = s722->s366();
if( s717 == 0 ) {
s722->s519( (s278*)this );
s717 = s722->s366();}
return s717;}
s501* s278::s663( const s269& s736, s501* s612, const std::wstring& s346 ){
vector<wstring> s723;
vector<s503> s280;
s278* s717 = new s278( *this, s280, &s736 );
size_t pos = s736.s297().find( L"(" );
size_t pos_ = pos;
s269::s294( s736.s297(), pos, s723 );
if( s723.size() ) {
s615* s724 = (s615*) s655.get( s7::s443, false );
if( !s724 )
throw new TDException( 0, s1018, &s736, 
L"Arguments passed to a class without init function." );
else {
wstring str = s736.s297();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s7::s443 );
s269* ast_ = new s269( s7::s444, s144( str ) );
s508 cs = (s584*)s277::s524( *ast_, s306, s717, s346 );
s615* td = s615::s624(
cs, s306, s717, (s615*)s717, s284, false );
s717->s655.s564( s7::s444, td );}}
return s717;}
s501* s278::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
vector<wstring> s723;
vector<s503> s280;
s278* s717 = new s278( *this, s280, s627() );
if( l.size() ) {
s615* s724 = (s615*)s655.get( s7::s443, false );
if( !s724 )
throw new TDException( 0, s1018, ast_,
L"Arguments passed to a class without init function." );
else {
s508 cs = new s584( s306, s7::s443, l, ast_ );
cs->s626().insert( cs->s626().begin(), s717 );
s615* td = s615::s624(
cs, s306, s717, (s615*)s612, s284, false );
s717->s655.s564( s7::s444, td );}}
s717->s519( (s278*)s612, true );
return s717;}
std::wstring s278::s304() const{
if( s513() == s497 )
return s284;
else if( s513() == s496 || s513() == s498 )
return s361;
else if( s513() == s493 || s513() == s1395 )
return s898();
assert( 0 );
return /*s283 + L"::" +*/ s284;
}
s501* s278::s358( const std::wstring& s708, const std::wstring& s346,
bool s543 /*= true*/ ) const
{
s386 ref( s708, s306 );
if( !s579( s708, &ref, s346, true ) )
return NULL;
return ref.s393();}
s615* s278::s1862( const std::wstring& s708, s615* s219, vector<s277*>& s740 ) const{
if( s708 == L"getf" ) {
return new s1856( s306, (s278*)this, s219, &s278::s1882, s740, 
NULL );}
return s501::s1862( s708, s219, s740 );}
s501* s278::s1882( s501** s280, size_t s517 ){
s374* pv = (s374*) s280[1];
return s655.get( pv->to_wstring() );}
s277* s278::s349() const{
vector<s503> v;
return new s278( *this, v, NULL );}
void s278::s371( s277* p ) const{
s278* pob = (s278*)p;
s655.s1789( pob->s655 );
for( size_t n = 0; n < pob->s658.size(); ++n ) {
pob->s657[n] = pob->s655.get( pob->s658[n].s643() );}
return;
throw new s16( L"" );
vector<wstring> fields;
s655.s568( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s501*)s655.get( fields[n] ))->s371( p );}
size_t s278::s330() const{
return (size_t)this;}
bool s278::operator==( const s501* p ) const{
return (this == p);}
bool s278::operator<( const s501* p ) const{
return false;}
wstring s278::to_wstring( uint32_t s1739 ) const{
if( s655.s159( s7::s1805 ) ) {
s615* s1831 = (s615*)s655.get( s7::s1805 );
s9<s527> s1829 = new s527( (s268*)s306, (s278*)this, s627() );
vector<s503> s740 = { /*(s277*)this,*/ s1829 };
s1831->s620( s740 );
if( s1831->s644() != s7::s940 )
s1831->s519( this, false );
else
s1831->s621( this );
s1831->s516( 0, 0 );
return s1829->to_wstring();}
std::wstringstream buf;
wstring s361;
if( s511 == s496 ) s361 = L"Class";
else if( s511 == s497 ) s361 = L"Module";
else if( s511 == s498 ) s361 = L"Object";
else s361 = L"ERROR";
buf << s361 << L" : " << s284 << L"/" /*<< s387*/ << endl;
s655.s310( &buf, s434 );
buf << endl;
return buf.str();}
void s278::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s361;
if( s511 == s496 ) s361 = L"Class";
else if( s511 == s497 ) s361 = L"Module";
else if( s511 == s498 ) s361 = L"Object";
else s361 = L"ERROR";
buf << s4::fill_n_ch( L' ', s201 ) << s361 << L" : " << s284 << L"/" << 
/*s387 <<*/ L": " << this << endl;
s655.s310( pd, s201 + s434 );}
s615* s615::s623( const s269& s736, s268* s306, s278* obj,
const wstring& s284, const wstring& s581 ){
const s269::s281& s737 = s736.s299();
size_t s732 = s737.size();
std::vector<s277*> s280;
for( size_t n = 0; n < s732; ++n ) {
s269::s281::const_iterator it = s737.find( std::to_wstring( n ) );
if( it->second->s297() == s7::s1027 )
s280.push_back( s949 );
else if( it->second->s297() == s7::s1262 )
s280.push_back( s1863 );
else
s280.push_back( s277::s524( *it->second, s306, obj, s581 ) );}
Transd* s717 = NULL;
size_t s721 = s284.find_first_of( s4::s49 );
if( s721 != string::npos ) {
vector<wstring> s720;
s4::s58( s284, wstring( 1, s284[s721] ), s720 );
if( s720.size() > 2 )
throw new s16( L"malformed function name: " + s284 );
if( s720[0] == s7::s446 ) {
s717 = new s628( s306, obj, NULL, s591, s280, &s736 );
s717->s284 = s720[1];}
else if( s720[0] == s7::s447 ) {
s717 = new s910( s306, obj, NULL, s591, s280, &s736 );
s278* pAnc = (s278*)s306->s227( obj->s665(), s581 );
((s628*)pAnc->s358( s720[1], s581 ))->s677( obj->s366(),
s717 );
s717->s284 = s720[1];
s717->s618( s597 );}
else
throw new s16( L"malformed function name: " + s284 );}
else {
s717 = new s910( s306, obj, NULL, s591, s280, &s736 );
s717->s284 = s284;}
return s717;}
s584* s615::s1235( const s269& s736, s268* s306, s278* obj,
const wstring& s581 ){
const s269::s281& s737 = s736.s299();
size_t s732 = s737.size();
wstring s625 = s736.s297();
std::vector<s277*> s280;
s584* s717 = NULL;
try {
for( size_t n = 0; n < s732; ++n ) {
s269::s281::const_iterator it = s737.find( std::to_wstring( n ) );
it->second.s15<s269*>()->s275( L"ownerType", L"CallSite" );
it->second.s15<s269*>()->s275( L"ownerName", s625 );
if( it->second->s297() == s7::s1027 )
s280.push_back( s949 );
else if( it->second->s297() == s7::s1262 )
s280.push_back( s1863 );
else
s280.push_back( s277::s524( *it->second, s306, obj, s581 ) );}
s717 = new s584( s306, s625, s280, &s736 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s625 + L"' function call" );}
return s717;}
void s584::s519( const s278* s960, bool ){
return;
for( size_t n = 0; n < s280.size(); ++n ) {
s280[n]->s519( s960 );}}
s277* s584::s349() const{
return new s584( *this );}
s615* s615::s624( s584* cs, s268* s306, s278* s612, s615* s219, 
const wstring& s581, bool proc ){
wstring s625 = cs->s305();
wstring s739 = s612 ? s612->s304() : L"::";
s503 s738 = NULL;
std::vector<s277*>& s280 = cs->s626();
s506 s741 = NULL;
s615* s717 = NULL;
size_t pl = s625.find( L"<" );
try {
if( pl == string::npos ) {
auto s1625 = s1541.find( s625 );
if( s1625 != end( s1541 ) && BIFuncs1v[s1625->second] )
return s306->s218( s1625->second, cs->s626(), s612, s219, cs->s627() );
s277* par = NULL;
int s1533 = 0;
s1528:
if( s280.size() ) {
par = s280[s1533];
s489 pc = par->s513();
if( pc == s492 ) {
try {
par->s519( s219, true );}
catch( TDException* e ) {
if( e->Category() != s1016 || (
( (s386*)par )->s643()[0] != L':' && ( (s386*)par )->s643().back() != L':' ) )
throw e->s30( L"while compiling function '" + s625 + L"'" );
s1533++;
goto s1528;}
if( ( (s386*)par )->s396().s14() ) {
if( ( (s386*)par )->s643() == s7::s445 )
par = s612;
s738 = ( (s386*)par )->s392();}}
else {
if( pc == s495 ) {
s508 cs = new s584( *(s584*)par );
par = s624( cs, s306, s612, s219, s581, proc );
( (s615*)par )->s519( s612, false );}
else {
par->s519( s219 );}}
if( par->s513() == s492 /*||  par->s513() == s1504*/ ) {
(void)0;}
else if( par->s513() == s1172 || par->s513() == s499 )
s738 = NULL;
else {
s738 = par->s515();}
s280[s1533] = par;}
else {
s741 = (s615*)s612->s358( s625, s739, false );
if( !s741 )
throw new s16( L"Procedure is not resolved: " + s625 );}
if( s1625 != end( s1541 ) )
return s306->s218( s1625->second, s280, s612, s219, cs->s627() );}
else {
wstring s646 = s625.substr( pl + 1, s625.size() - pl - 2 );
s625 = s625.substr( 0, pl );
try {
s1170 pt = s306->TR().s1109( s646, false );
if( !pt ) {
s1034 ast2 = new s269( s646 + L"()", cs->s627()->Nqj() );
s738 = s306->TR().s541( *ast2, s612, s581 );}
else
s738 = s306->TR().s1106( pt )->s370( s219, s280, s219->s627() );}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s625 + L"' function " );
s1034 ast2 = new s269( s646 + L"()", cs->s627()->Nqj() );
s738 = s306->TR().s541( *ast2, s612, s581 );}
s280.insert( s280.begin(), s738 );}
s506 s742 = NULL;
s1265 s1385;
if( !s741 ) {
s489 s745 = s738->s513();
if( s745 == s492 ) {
s386* ref = (s386*)s738.s15<s502*>();
s738 = (s501*)ref->s523();
s745 = s738->s513();}
try {
assert( s745 != s497 );
if( s745 == s498 || s745 == s496 ) {
s742 = (s615*)s738.s15<s278*>()->s358( s625, s739,
false );}
else if( s745 == s491 )
s1385 = s738.s15<s350*>()->s1340( s625 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s742 && !s1385.s353 )
s741 = (s615*)s612->s358( s625, s739, false );
if( !( s1385.s353 || s741 || s742 ) ) {
s615* ptd = s738.s15<s278*>()->s1862( s625, s219, s280 );
if( ptd )
return ptd;
throw new s16( L"Method is not resolved: " + s625 );}}
if( s1385.s353 ) {
s717 = new s909( s306, s219, s589, s280, s1385.s352, s625, cs->s627() );}
else if( s741 ) {
if( s625 == L"new" ) {
assert( 0 );
vector<s277*> s1840( s280.begin() + 1, s280.end() );
s717 = new s1526( *s741.s15<s1526*>(), s612, s219, s1840,
cs->s627() );}
else {
s717 = new s910( /**td*/ *s741.s15<s910*>(), /*s612,*/ s219, s280,
s590, cs->s627(), /*s612*/ s741->s612 );
}}
else if( s742 ) {
if( s625 == L"new" ) {
s717 = new s1526( *s742.s15<s1526*>(), s738.s15<s278*>(), s219, s280,
cs->s627() );}
else {
s9<s910> td = ( (s910*)s742->s349() );
s717 = new s910( *td, /*s738.s15<s278*>(),*/ s219, s280, s591,
cs->s627(), s738.s15<s278*>() );}
if( s742->s619() == s596 )
s717->s598 = s592;
else
s717->s598 = s591;}}
catch( s16* e ) {
throw e->s30( L"while compiling function '" + cs->s627()->Src() + L"'" );}
s717->s284 = s625;
return s717;}
void s615::s1392( vector<s277*>& s280, const vector<wstring>& s1353 ){
for( s277* p : s280 ) {
if( p->s513() == s492 || p->s513() == s1172 )
( (s386*)p )->s1077( s1353 );}}
void s615::s1392( vector<s503>& s280, const vector<wstring>& s1353 ){
for( s277* p : s280 ) {
if( p->s513() == s492 )
( (s386*)p )->s1077( s1353 );}}
s615::s615( s268* s306, s278* s616, s615* s617, s586 ct,
const std::vector<s277*>& l,	const s269* s736, bool s1905=false )
: s278( s306, 0, s493, s736 ), s598( ct ), s599( s595 ),
s610( NULL ),	s612( s616 ), s611( s617 ), past( s736 ), s1830( s306 ),
intro(s1905){
TDException s1059( s7::s1864, s1018, s736, L"malformed lambda definition" );
size_t n = 0;
bool s1308;
for( ; n < l.size(); n += 2 ) {
s1308 = false;
if( ((s501*)l[n]) == s949 ) {
if( l.size() == n )
throw s1059.s1097( L"the return type is missing" );
s512 = l[n + 1]->s366();
n += 2;
break;}
else if( ((s501*)l[n]) == s1863 ) {
if( l.size() == n )
throw s1059.s1097( L"the 'const' keyword should precede the parameter name");
s1308 = true;
++n;}
if( l[n]->s513() != s492 ) {
if( s1308 )
throw s1059.s1097( L"the 'const' keyword should precede the parameter name");
break;}
s386* s77 = (s386*) l[n];
if( l.size() == n + 1 ) {
break;}
s501* ex = (s501*) l[n + 1];
s489 s2078 = ex->s513();
if( s2078 != s491 && s2078 != s498 &&	s2078 != s497 && 
s2078 != s1396 && s2078 != s1395 )
throw new s16( L"incorrect syntax for lambda parameter " + s77->s643() +
L"; should be a type constructor.", (uint32_t)s16::s17::s20 );
if( s1308 )
s77->s1411();
s655.s564( s77->s643(), ex );
s606.push_back( (s501*)ex );
s657.push_back( (s501*)ex );
s658.push_back( *s77 );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
s615::s615( const s615& right, s278* s616, s615* s617,
const std::vector<s277*>& s740, const s269* s736 )
: s278( right.s306, right.s512, right.s511, s736 ),  
s599( right.s599 ),	s610( NULL ), s612( s616 ), s611( s617 ), 
past( s736 ), s1830( s306 ), intro(right.intro){
s512 = right.s512;
s598 = right.s598;
s657 = right.s657;
s658 = right.s658;
s655 = right.s655;
s606 = right.s606;
s284 = right.s284;
if( s740.size() ) {
s280.assign( s740.begin(), s740.end() );
for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n].s643(), s280[n].s15<s501*>(), s500::s150 );
s657[n] = s280[n];}}
else {
for( size_t n = 0; n < right.s280.size(); ++n ) {
s280.push_back( right.s280[n]->s349() );}}
for( size_t n = 0; n < right.s608.size(); ++n ) {
s608.push_back( right.s608[n]->s349() );}}
s909::s909( s268* s306, s615* s617, s586 ct, const vector<s277*>& l,
/*s642 s743,*/ s1170 s744, const wstring& s1727, const s269* s736 )
: s615( s306, s617, s617, ct, L"", s736 ), s1308( true )/*,
s585( s743 )*/
{
s284 = s1727;
s599 = s595;
s512 = s744;
s280.assign( l.begin(), l.end() );}
s909::~s909(){}
s910::s910( s268* s306, s278* s612, s615* s611, s586 ct,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s612, s611, ct, l, s736 ){
if( ct == s591 ) {
subject = s612;		}}
s910::s910( const s910& right, /*s501* s616,*/ s615* s617,
const std::vector<s277*>& s740, s586 ct,  const s269* s736, 
s278* s616 )
: s615( right.s306, s616 ? s616 : right.s612.s15<s278*>(), 
s617, ct, L"", s736 ){
TDException s1059( s7::s1846, s1018, s736 );
s598 = right.s598;
s512 = right.s512;
s657 = right.s657;
s658 = right.s658;
s655 = right.s655;
s606 = right.s606;
s599 = right.s599;
s284 = right.s284;
s610 = NULL;
int shift = 0;
if( ct == s591 ) {
if( s740.size() ) {
subject = s740[0];
shift = 1;}
else
subject = s612.s15<s502*>();}
for( size_t n = 0; n < s606.size(); ++n ) {
if( s740.size() > n + shift ) {
s280.push_back( s740[n + shift] );}
else
s280.push_back( s606[n]->s349() );}
if( s740.size() - shift > s280.size() ) 
throw s1059.s1097( L"too many arguments: expected " + std::to_wstring( s280.size() ) + L", received " +
std::to_wstring( s740.size() ));
/*for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n], s280[n].s15<s501*>(), s500::s150 );
s657[n] = s280[n];
}*/
s608 = right.s608;}
s615::~s615(){
/*	for( size_t n = 0; n < s280.size(); ++n ) {
delete s280[n].s15<s502*>();
}*/
}
s910::~s910(){}
s584::s584( s268* pass_, const std::wstring& s193, const vector<s277*>& l, 
const s269* ast_ )
: s277( pass_, s495 ), s625( s193 ), past( (s269*)ast_ ){
s280.assign( l.begin(), l.end() );}
s584::s584( const s584& right )
: s277( right.s306, s495 ), s625( right.s625 ), past( right.past ){
for( size_t n = 0; n < right.s280.size(); ++n ) {
s280.push_back( right.s280[n]->s349() );}}
wstring s615::s898() const{
if( s612.s14() )
return s612->s304();
else if( s598 == s589 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
void s615::s916( s277* par, size_t pos, s503& s156, const s278* s1848 ){
if( par->s513() == s495 ) {
s508 cs = new s584( *((s584*)par) );
s156 = s624( cs, s306, (s278*)s1848, this, s612->s304(), false );
s156.s15<Transd*>()->s519( s1848, false );}
else if( par->s513() == s491 ) {
par->s519( /*s612*/ this, false );
s156 = par;}
else if( par->s513() == s493 ) {
s156 = par; // par->s515();
}
else
s156 = par;}
void s615::s613(const wstring& s346){
for( size_t n = 0; n < s606.size(); ++n )
s606[n]->s519( s611/*s612*/ );
}
void s615::s519( const s278* s1848, bool proc/*=false*/ )
{
ns = s612;
s702 = proc ? s612->s304() : s1848->s304();
if( s612 && (s612->s513() == s497 || s612->s513() == s496 )) {
if( s612->s513() == s496 )
return;}
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( s598 == s589 && n == 1 ) {
s615::s1392( s280, ((s350*)s280[0]->s515())->s1334( s284 ) );}
if( par->s513() == s492 ) {
if( par.s15<s386*>()->s396().s13() ) {
s505 s1851 = s612;
s612 = (s278*)s1848;
par.s15<s386*>()->s519( this, false );
s612 = s1851;}
s607.push_back( NULL );}
else if( par->s513() == s1172 || par->s513() == s499 )
s607.push_back( /*NULL*/ par.s15<s501*>() );
else {
try {
s916( par, n, s280[n], s1848 );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s284 + L"' function " );}
s607.push_back( s280[n]->s515() );}}
if( s598 == s588 ) {
if( s284 == s238 ) {
for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n].s643(), s280[n].s15<s501*>(), s500::s150 );
s280[n]->s1855( s7::s940 );
s657[n] = s280[n];}}
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304(), true );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( s611, true );
else if( s608[n]->s513() != s493 )
s608[n]->s519( s611 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s608 ) {
if( it->s513() == s493 )
it.s15<Transd*>()->s519( s612, true );}
if( !s512 && s608.size() ) {
s512 = s608.back()->s366();}}
if( s512 ) {
if( s612.s14() ) {
if( 0 && s511 == s1395 )
s610 = s306->TR().s541( ((s905*)this)->s1494(), 
s612, s612->s304() );
else
s610 = s306->TR().s541( s366(), s612, s612->s304() );}
else {
if( 0 && s511 == s1395 )
s610 = s306->TR().s541( ((s905*)this)->s1494(), 
(s278*)s1848, s1848->s304() );
else
s610 = s306->TR().s541( s366(), (s278*)s1848, s1848->s304() );}
s610->s519( s611 );
s610->s1855( s7::s940 );
s607.insert( s607.begin(), s610 );
if( s280.size() ) {
s604 = (s502**)&s280[0];
nlocs = s280.size();
s603 = &s607[0];
s517 = s607.size();}
else {
s604 = NULL;
s603 = NULL;
nlocs = s517 = 0;}}
s1075.resize( s607.size() );}
void s909::s519( const s278* s1848, bool proc/*=false*/ )
{
s702 = proc ? s612->s304() : s1848->s304();
TDException s1059( s7::s1242, s1253, past );
s615::s519( s1848, proc );
s277* par = s280[0]->s515();
s350* s738 = NULL;
s1265 s1385;
s489 s745 = par->s513();
s1238 ap;
if( s745 == s492 ) {
s386* ref = (s386*)par;
s504 pobj = ref->s392();
s745 = pobj->s513();
s738 = pobj.s15<s350*>();
ap = s1238( s280, s738 );
try {
s1385 = s738->s1335( s284, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s350::s351::s1254::s1322 ) {
s1385 = s738->s1330( s284, ap /*s1387, s280*/ );
}}}
else {
s738 = ( (s350*)par );
ap = s1238( s280, s738 );
try {
s1385 = ( (s350*)s738->s515() )->s1335( s284, ap/*s1387*/ );
}
catch( s16* e ) {
if( e->which() == (uint32_t)s350::s351::s1254::s1322 ) {
s1385 = ( (s350*)s738->s515() )->s1330( s284, ap/*s1387, s280*/ );
}}}
if( !s1385.s353 )
throw s1059.s1097( L"method is not resolved: " + par->s368() + L"::" + s284 + 
ap.s1495( s306 ) );
s512 = s1385.s352;
s585 = s1385.s353;
s1308 = s1385.s1308;
bool s1940 = false;
if( s280[0]->s513() == s492 )
s1940 = s280[0]->s1347();
else
s1940 = s280[0]->s515()->s1347();
if( !s1308 && s1940 )
throw s1059.s1097( L"non-constant function is applied to a constant variable" );
if( s284 == L"new" )
s610 = s280[0].s15<s501*>();
if( s610.s13() ) {
s610 = s306->TR().s541( s366(), s612, s612->s304() );
s610->s519( s611 );
s607.insert( s607.begin(), s610 );
if( s280.size() ) {
s604 = (s502**)&s280[0];
nlocs = s280.size();
s603 = &s607[0];
s517 = s607.size();}
else {
s604 = NULL;
s603 = NULL;
nlocs = s517 = 0;}}
s1075.resize( s607.size() );
s1413();}
void s910::s519( const s278* s1848, bool proc/*=false*/ )
{
TDException s1059( s7::s1696, s1730, s627() );
s702 = proc ? s612->s304() : s1848->s304();
if( s612->s513() == s497 || s612->s513() == s496 ) {
s613( s702 );
if( s612->s513() == s496 )
return;}
if( s280.size() > s657.size() )
throw s1059.s1097( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s492 ) {
s386* s1827 = par.s15<s386*>();
if( s1827->s396().s13() ) {
s1827->s519( /*this*/s611, true );
}}
else
s916( par, n, s280[n], s1848 );
if( s606[n]->s366() == s827->s366() ) {
if( !s606[n]->s521( s280[n].s15<s501*>() ) )
throw s1059.s1097( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s606[n]->s368() + L"', received - '" + par->s368() + L"'" );}
else if( !s306->TR().s1708( s280[n]->s366(), s606[n]->s366() ) ) {
throw s1059.s1097( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s606[n]->s368() + L"', received - '" + par->s368() + L"'" );}}
for( size_t n = 0; n < s280.size(); ++n ) {
if( s280[n]->s644() < 0 )
throw s1059.s1097( L"uninitialized function parameter: " + s658[n].s643() );
if( s280[n]->s1347() && !s658[n].s1347() )
throw s1059.s1097( L"constant argument is passed to non-constant function: " + s658[n].s643() );
s657[n] = s280[n];}
s506 s1532 = s611;
s611 = 0;
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304(), true );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( /*s611*/ s612, true );
else if( s608[n]->s513() != s493 && 
s608[n]->s513() != s1395 )
s608[n]->s519( /*s611*/ s612 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s608 ) {
if( it->s513() == s493 )
it.s15<Transd*>()->s519( s612, true );}
s611 = s1532;
if( !s512 ) {
if( s608.size() ) {
s512 = s608.back()->s366();
s610 = s306->TR().s541( s366(), s612, s612->s304() );}
else {
s512 = s1286;
s610 = s380.s15<s501*>();}
s610->s1855( s7::s940 );
s607.insert( s607.begin(), s610 );}
if( s280.size() ) {
s604 = (s502**)&s280[0];
nlocs = s280.size();
s603 = NULL;// &s607[0];
s517 = s607.size();}
else {
s604 = NULL;
nlocs = s517 = 0;
s603 = NULL;}
s1075.resize( s607.size() );
s1413();}
void s615::s620( const vector<s503>& l ){
s280.clear();
s280.assign( l.begin(), l.end() );}
void s615::s621( const s278* s1848 ){
TDException s1059( s7::s1775, s1730, s627() );
if( s598 != s589 && s598 != s588 && s280.size() > s657.size() )
s1059.s1097( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s277* par = s280[n];
if( par->s513() == s495 ) {
s508 cs = new s584( *(s584*)par );
par = s624( cs, s306, s612, /*this*/s611, s612->s304(), false );
((s615*)par)->s519( s1848, false );
s280[n] = par;}
if( s280[n]->s513() == s499 ) {
s607.push_back( s280[n]->s515() );}
else if( s280[n]->s513() != s492 ) {
if( ( s598 != s589 && s598 != s588 ) || s284 == s238 ) {
s657[n] = s280[n]->s515();
s657[n]->s1855( s7::s940 );
s655.s564( s658[n].s643(), s657[n].s15<s501*>(), s500::s150 );}
s607.push_back( s280[n]->s515() );}
else {
if( s598 != s589 && s598 != s588 ) {
s657[n] = s280[n].s15<s501*>();
s655.s564( s658[n].s643(), s280[n].s15<s386*>()->s392(), s500::s150 );}
if( s280[n].s15<s386*>()->s396().s13() ) {
s280[n].s15<s386*>()->s519( s611 /*this*/, true );
}
s607.push_back( NULL );}
if( s284 != s238 && n < s657.size() && n < s606.size() && !s657[n].s15<s501*>()->s521( (s501*)s606[n] ) )
s1059.s1097( L"wrong argument's type" );}
for( size_t n = 0; n < s657.size(); ++n ) {
if( s657[n]->s644() == s7::s941 )
s1059.s1097( L"parameter is not provided" );}}
void s615::s868( s899& s156 ) const{
for( size_t n = 0; n < s606.size(); ++n )
s156.push_back( make_pair( s658[n].s643(), s606[n] ) );}
void s615::s1787( s501** s723, size_t s732 ){
int shift = 0;
if( s598 == s588 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1504 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1075[n] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1075[n];}}}}
s504 s615::s516( s501** s723, size_t s732 ){
s504 s717;
size_t shift = 0;
if( s598 == s591 || s598 == s589 || s598 == s588 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1075[n+shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1075[n + shift];}
else if( pc == s491 )
*( s603 + n + shift ) = (s501*)*( s604 + n );}}
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s603, s517 );
if( s717->s644() < 0 )
break;}
s610 = s717;
return s717;}
s504 s909::s516( s501** s723, size_t s732 ){
s501* s717 = NULL;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1504 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1075[n + shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1075[n + shift];}
else if( pc == s1395 )
(void)0;}}
if( !s1308 && s607[1]->s1347() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s585( s603, s517 );}
catch( s16* e ) {
TDException* s1059 = new TDException( TDException::Stage::s1136, s7::s1243, 
s1252, past,	*e );
delete e;
throw s1059;}
s717 = s607[0];
return s717;}
s504 s910::s516( s501** s723, size_t s732 ){
s501* s717 = s380;
if( subject.s14() )
s1830.s1837( subject->s516( 0, 0 ) );
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 ) ( void )0;
else if( pc == s493 )
s657[n] =
(s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );}}
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s603, s517 );
if( s717->s644() < 0 ) {
if( s717->s644() == s7::s939 )
s717->s1855( 0 );
break;}}
return s717;}
s1526::s1526( s268* s306, s278* s612, s615* s611, const s269* s736 )
: s910( s306, s612, s611, s591, vector<s277*>(), s736 ){
s1526* pin = (s1526*)s612->s358( s7::s443, s612->s304(), false );
if( pin ) {
pin->s655.copy( s655, (s278*)s612, s611 );
s658 = pin->s658;
s657 = pin->s657;
s606 = pin->s606;}}
s1526::s1526( const s1526& right, s278* s616, s615* s617,
const std::vector<s277*>& s740, const s269* s736 )
: s910( right, /*s616,*/ s617, s740, s591, s736 )
{
s612 = s616;
s280.assign( s740.begin() + 1, s740.end() );
s512 = right.s512;
s610 = (s501*)s740[0];}
s1526::~s1526(){}
void s1526::s519( const s278* s1848, bool proc/*=false*/ )
{
for( size_t n = 0; n < s280.size(); ++n ) {
s280[n]->s1855( s7::s940 );}
s610 = s612.s15<s278*>();
s512 = s610->s366();}
s504 s1526::s516( s501** s723, size_t s732 ){
s621( s612 );
s501* s717 = NULL;
if( s612->s366() == s1894 )
s717 = new s905( *s612.s15<s905*>(), s280, s627() );
else
s717 = new s278( *s612, s280, s627() );
s717->s519( s611 );
s717->s1413();
return s717;
wstring s193 = s627()->s297();
wstring s1527 = s627()->Src();
s1527.replace( s1527.find( s193 ), s193.size(), 1, L' ' );
s269* ast_ = new s269( s193, s1527 );
s717 = s610.s15<s278*>()->s663( *ast_, s611, s702 );
s717->s1413();
return s717;
vector<s277*> s1824( begin(s280), end(s280));
s717 = s610->s370( s611, s1824, s627() );
s717->s1413();
return s717;}
bool
s615::s579( const wstring& s708, s386* ref,	
const wstring& s346, bool fr ) const{
bool s717 = false;
wstring s284 = s708;
size_t pl = s284.find( L"." );
if( pl == string::npos ) { //a
if( !s655.s159( s284 ) || ( !fr && !intro ) 
|| ( s611.s14() && !intro ) ) {
if( s611.s14() && (s612.s13() || s611->s612 == s612 || 
s702 == s611->s702 || s702 != s611->s702) )
s717 = s611->s579( s284, ref, s346, true );
if( !s717 ) {
if( s612.s14() )
s717 = s612->s579( s284, ref, s346, true );
if( s717 ) {
if( s612->s513() != s497 && ref->s396() == s612.s15<s277*>() ) {
ref->s397( (s501*)&s1830 );
((s1776*)&s1830)->s1837( s612.s15<s501*>() );}}
else
s717 = s306->s579( s284, ref, s346, true );}}
else {
size_t off = s668( s284 );
ref->s394( off, ((s502*)&(*s657[off]))->s515()->s523() );
if( s658[off].s1347() )
ref->s1411();
ref->s397( (s501*)this /*(s502**)&s280[off]*/ );
s717 = true;}}
else {// a.y
s284 = s708.substr( pl + 1 );
wstring s718 = s708.substr( 0, pl );
s277* ob = s655.get( s718, false );
if( !ob ) {
s717 = s612->s579( s708, ref, s346, true );
if( !s717 && s611.s14() )
s717 = s611->s579( s708, ref, s346, true );}
else {
size_t off = s668( s718 );
ref->s394( off, NULL );
s717 = ob->s523()->s579( s284, ref, s346, true );
ref->s397( (s501*)this );}}
return s717;}
bool
s909::s579( const wstring& s708, s386* ref, const wstring& s346,
bool fr) const{
if( s284 == L"new" &&
s280[0].s15<s501*>()->s579( s708, ref, s346, true ) )
return true;
return s615::s579( s708, ref, s346, true );}
s277* s615::s622( size_t off ){
return s657[off];}
s277* s615::s349() const{
return new s615( *this );}
s277* s909::s349() const{
return new s909( *this );}
s277* s910::s349() const{
return new s910( *this );}
s277* s1526::s349() const{
return new s1526( *this );}
void s615::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Transductor : " <<  s284 << endl;
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"Call type : " << ct[s598] << endl;
if( !s655.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"members : " << endl;
s655.s310( pd, s201 + s434 );}
if( !s606.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"fpars : " << endl;
for( size_t n = 0; n < s606.size(); ++n )
s606[n]->s310( pd, s201 + s434 * 2 );}
if( !s658.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"namvec : " << endl;
for( size_t n = 0; n < s658.size(); ++n )
buf << s4::fill_n_ch( L' ', s201 + s434 * 2 ) << s658[n].s643() << endl;}
if( !s657.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"memvec : " << endl;
for( size_t n = 0; n < s657.size(); ++n )
s657[n]->s310( pd, s201 + s434 * 2 );}
if( !s608.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"exprs : " << endl;
for( size_t n = 0; n < s608.size(); ++n )
s608[n]->s310( pd, s201 + s434 * 2 );}}
static s6::s1873 s1915;
s374::s374( s268* s306, const std::wstring& s, s278* s612, const s269* ast_ )
: s1572( s306, s612, ast_ ){
if( s374::proto.s13() ) {
s512 = 0;
wh = s7::s941;}
else {
s512 = s1288;
wh = s7::s940;
s363 = s;}
s334 = s1754;}
s374::s374( s268* s306, s278* s616, const std::vector<s277*>& l, const s269* ast_ )
: s1572( s306, s616, ast_ ){
s280.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s941;
else
wh = s7::s940;
s512 = s1288;
s334 = s1754;}
s374::s374( const s374& r, const s269* ast_ )
: s1572( r.s306, r.ns, ast_ ){
s363 = r.s363;
wh = r.wh;
s512 = r.s512;
s334 = s1754;}
s374::s374( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ )
: s1572( s306, NULL, ast_ ){
s363 = s;
pos = string::npos;
s512 = s1288;
s334 = s1754;
wh = s7::s940;}
s374::~s374(){}
s501* s374::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s374( s306, s612, l );}
void s374::s364(){
s1572<s1752, wchar_t, s374, s1748>::s364();
s362 = s1572<s1752, wchar_t, s374, s1748>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s374::s1384, s1288,
{ s1238(), s1238( { s7::s1564, s7::s1570 } ) }, 0, 100 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s374::s828, s1284,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"find-first-not-of", new s351( L"find-first-not-of", &s374::s1764, s1284,
{ s1238( { s1288 } ), s1238( { s1288, s1284 } ), 
s1238( { s1288, s1284, s1284 } )}, 1, 3 )));
s362.insert( make_pair( L"set", new s351( L"set", &s374::s402, s1286,
{ s1238( { s1288 } ), s1238( { s1286 } ) }, 1, 1, false )));
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s374::s1768, s1286,
{ s1238( { s1284, s1288 } ), s1238( { s1284, s1754 } ) }, 2, 2 )));
s362.insert( make_pair( L"size", new s351( L"size", &s374::s339, s1284,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"starts-with", new s351( L"starts-with", &s374::s1866, s1274,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"sub", new s351( L"sub", &s374::s844, s1288,
{ s1238( { s1686::s1425 } ), s1238( { s1686::s1425, s1686::s1425 } ) }, 1, 2 )));
s362.insert( make_pair( L"subn", new s351( L"subn", &s374::s1771, s1288,
{ s1238( { s1686::s1425 } ), s1238( { s1686::s1425, s1686::s1425 } ) }, 1, 2 )));
s362.insert( make_pair( L"sum", new s351( L"sum", &s374::s403, s1288,
{ s1238( { s1288, s7::s1570 } ) }, 1, 100 )));
s362.insert( make_pair( L"to-bytes", new s351( L"to-bytes", &s374::s1515, s1275,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s374::s427, s1284,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"tolower", new s351( L"tolower", &s374::s975, s1288,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"toupper", new s351( L"toupper", &s374::s976, s1288,
{ s1238() }, 0, 0 )));
s362.insert( make_pair( L"rfind", new s351( L"rfind", &s374::s849, s1284,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s374::s413, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"not", new s351( L"not", &s374::s428, s1274,
{ s1238( ) }, 0, 0 )));
s362.insert( make_pair( L"less", new s351( L"less", &s374::s414, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"greater", new s351( L"greater", &s374::s415, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"leq", new s351( L"leq", &s374::s416, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"geq", new s351( L"geq", &s374::s417, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"neq", new s351( L"neq", &s374::s418, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"textin", new s351( L"textin", &s374::s424, s1284,
{ s1238( ), s1238( { s1284 } ), s1238( { s1686::s1679 } ), 
s1238( { s1686::s1679, s1284 } ) }, 1, 2 )));
s362.insert( make_pair( L"getline", new s351( L"getline", &s374::s1657, s1284,
{ s1238(), s1238( { s1686::s1679 } ) }, 0, 1 )));
s362.insert( make_pair( L"match", new s351( L"match", &s374::s1141, s1274,
{ s1238( { s1288 } ) }, 1, 1 )));
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s374::proto->s368() + L">";
s1170 s1691 = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s362.insert( make_pair( L"split", new s351( L"split", &s374::s1664, s1691,
{ s1238(), s1238( { s1288 } ) }, 0, 0 )));
s1915 = s1914;
s1915.s1875 = L" \n";}
void s916( s277* par, s268* s306, s278* s612,
s615* s219, s503& s156 ){
if( par->s513() == s495 ) {
s508 cs = new s584( *( (s584*)par ) );
s156 = s615::s624( cs, s306, s612, s219, s612->s304(), false );
s156.s15<Transd*>()->s519( s612, false );}
else if( 1 && par->s513() == s491 ) {
par->s519( /*s612*/ s612 );
s156 = par;}
else
s156 = par;}
void s374::s519( const s278* s960, bool ){
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s495 ) {
s916( par, s306, ns, (s615*)ns, s280[n] );}
else if( par->s366() == s1586 ) {
auto pr = par.s15<s400*>();
auto rp = pr->s1337();
typename s1557::iterator s1693, s1694;
s1693 = rp.first.s15<s1261*>()->s1268();
s1694 = rp.second.s15<s1261*>()->s1268();
s1557 news( s1693, s1694 );
s363 += news;}
else if( par->s513() != s492 ) {
s363 += par->to_wstring();}
else {
if( s306->s1496() /*par.s15<s386*>()->s396().s14()*/ )
par.s15<s386*>()->s392()->to_wstring();}}
s1413();}
wstring s735( wchar_t c ){
wstring s717;
if( c == L'n' )
s717 = L"\n";
else if( c == L'r' )
s717 = L"\r";
else if( c == L't' )
s717 = L"    ";
else if( c == L'\\' )
s717 = L"\\";
else {
s717 = c;}
return s717;}
s501* s374::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
wstring s363, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s53( s_.substr( 7, s_.size() - 8 ), s49 );
if( s.empty() )
return new s374( s306, s612, std::vector<s277*>() );}
else
s = s4::s53( s_, s49 );
if( s.size() ) {
size_t pos = 0;
const s1032* s1158 = NULL;
if( s627() && s627()->Nqj() )
s1158 = s627()->Nqj()->s1105();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1158, s, pos, s96, s1915 );
if( s96.size() ) {
s = L"";
for( size_t n = 0; n < s96.size(); ++n ) {
wstring tmp = s96[n]->s172();
pl = s89.find( tmp[0] );
if( pl != string::npos && tmp.back() == s89[pl] )
tmp = tmp.substr( 1, tmp.size() - 2 );
s += tmp;}}}
if( s.size() == 2 && s[0] == L'\\' )
s363 = s735( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s363 = s;
while( pl != string::npos ) {
if( pl == s363.size() - 1 )
break;
if( s363[pl + 1] != L'\\' ) {
wstring code = s735( s363[pl + 1] );
s363 = s363.replace( pl, 2, code );
pl = s363.find( L"\\", pl + 1 );}
else {
s363.erase( pl, 1 );
pl = s363.find( L"\\", pl + 1 );}}}
if( s363.empty() )
s363 = s;
return new s374( s306, s363, s612, &s736 );}
s277* s374::s349() const{
return new s374( *this );}
s1170 s374::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get" )
s717 = s334;
else
s717 = s1572::s1331( s1727, l );
return s717;}
void s374::s371( s277* p ) const{
if( p->s366() == s1288 )
*( (s374*)p )->s372() = s363;
else if( p->s366() == s1284 )
*( (s360*)p )->s372() = std::stoi( s363 );
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = std::stof( s363 );
else
throw new s16( L"No conversion to type " + s368() );}
s374::operator int() const{
long s717;
if( !s4::s63( s363.c_str(), &s717 ) )
throw new s16( L"cannot cast String " + s363 + L" to Int" );
if( s717 > (std::numeric_limits<int>::max)() )
throw new s16( L"cannot cast String to Int: the value is too big: " + s363 );
return (int) s717;}
s374::operator double() const {
double s717;
if( !s4::s64( s363.c_str(), &s717 ) )
throw new s16( L"cannot cast String '" + s363 + L"' to Double" );
return s717;}
wstring s374::to_wstring( uint32_t s1739 ) const{
if( 0 && s363.front() == '\"' && 
s363.back() == '\"' )
return s363.substr( 1, s363.size() - 2 );
return s363; }
s1488 s374::to_bytes() const{
s1488 s717;
string s = U8(s363);
s717.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s717[n] = s[n];
return s717;}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s374*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
inline void s374::s1384( s501** s280, size_t s517 ){
s374* ps = (s374*)s280[1];
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
*s280 = ( s501* ) new s374( ps->s306, ps->s306, v );
s280[0]->s519( ps->ns );}
inline void s374::s402( s501** s280, size_t s517 ){
if( !PARN( 2 ) )
throw new s16( L"cannot assign Null object to String" );
( (s374*)DR )->s363 = ( (s374*)PARN( 2 ))->s363;}
inline void s374::s1768( s501** s280, size_t s517 ){
int pl = (int)*s280[2];
wchar_t c;
if( s280[3]->s366() == s1754 )
c = *( (s1748*)s280[3] )->s372();
else
c = ( (s374*)s280[3] )->s363[0];
( (s374*)DR )->s363[pl] = c;}
inline void s374::s339( s501** s280, size_t s517 ){
*( (s360*)s733 )->s372() = (int)( (s374*)DR )->s363.size();}
inline void s374::s1866( s501** s280, size_t s517 ){
wstring s731 = L"Invalid 'starts-with' syntax: ";
if( s517 < 3 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ( (s374*)DR )->s363;
const wstring& str = ( (s374*)s280[2] )->s363;
if( dr.find( str ) == 0 )
*( (s375*)s280[0] )->s372() = true;
else
*( (s375*)s280[0] )->s372() = false;}
inline void s374::s403( s501** s280, size_t s517 ){
s733->s363 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s517; ++n )
s733->s363 += PARN( n )->to_wstring();}
inline void s374::s975( s501** s280, size_t s517 ){
s733->s363 = ((s374*)DR)->s363;
std::for_each( s733->s363.begin(), s733->s363.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s374::s976( s501** s280, size_t s517 ){
s733->s363 = ((s374*)DR)->s363;
std::for_each( s733->s363.begin(), s733->s363.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s374::s844( s501** s280, size_t s517 ){
wstring s731 = L"Invalid substring specification: ";
if( s517 < 2 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ((s374*)DR)->s363;
int start = 0, end = (int) dr.size();
if( s517 > 2 ) {
start = (int)*s280[2];
if( s517 > 3 )
end = (int)*s280[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s731 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s16( s731 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s16( s731 + L"the end position is less than 0." );
if( start > end )
throw new s16( s731 + L"the start position is greater than string's length." );}
s733->s363 = dr.substr( start, end - start );}
inline void s374::s1771( s501** s280, size_t s517 ){
wstring s731 = L"Invalid substring specification: ";
if( s517 < 2 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ((s374*)DR)->s363;
int start = 0, s716 = 1;
if( s517 > 2 ) {
start = (int)*s280[2];
if( s517 > 3 )
s716 = (int)*s280[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s731 + L"the start position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( s731 + L"the start position is greater than string's length" );
if( s716 < 0 )
throw new s16( s731 + L"the characters count cannot be less than 0" );}
s733->s363 = dr.substr( start, s716 );}
inline void s374::s828( s501** s280, size_t s517 ){
wstring s731 = L"Invalid 'find' syntax: ";
if( s517 < 3 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ( (s374*)DR )->s363;
const wstring& str = ( (s374*)s280[2] )->s363;
int start = 0; 
if( s517 > 3 ) {
start = (int)*s280[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s731 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s731 + L"the start position is greater than string's length." );}
*((s360*)s280[0])->s372() = (int)dr.find( str, start );}
inline void s374::s1764( s501** s280, size_t s517 ){
wstring s731 = L"Invalid 'find-first-not-of' syntax: ";
if( s517 < 3 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ( (s374*)DR )->s363;
const wstring& str = ( (s374*)s280[2] )->s363;
int start = 0;
if( s517 > 3 ) {
start = (int)*s280[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s731 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s731 + L"the start position is greater than string's length." );}
*((s360*)s280[0])->s372() = (int)dr.find_first_not_of( str.c_str(), start );}
inline void s374::s849( s501** s280, size_t s517 ){
wstring s731 = L"Invalid 'rfind' syntax: ";
if( s517 < 3 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ( (s374*)DR )->s363;
const wstring& str = ( (s374*)s280[2] )->s363;
int start = (std::numeric_limits<int>::max)();
if( s517 > 3 ) {
start = (int)*s280[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s731 + L"the start position is less than 0." );}
*( (s360*)s280[0] )->s372() = (int)dr.rfind( str, start );}
inline void s374::s413( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() == *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s428( s501** s280, size_t s517 ){
*s734->s372() = ( (s374*)DR )->s372()->empty();}
inline void s374::s414( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() < *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s415( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() > *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s416( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() <= *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s417( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() >= *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s418( s501** s280, size_t s517 ){
*s734->s372() = *( (s374*)DR )->s372() != *( (s374*)PARN( 2 ) )->s372();}
inline void s374::s424( s501** s280, size_t s517 ){
Stream* s1651 = NULL;
size_t s1626 = 0;
if( s517 >= 3 ) {
if( s280[2]->s366() == s1284 )
s1626 = (int)*s280[2];
else
s1651 = (Stream*)s280[2];
if( s517 == 4 )
s1626 = (int)*s280[3];}
else
s1651 = s1574;
wstring& s156 = *( (s374*)DR )->s372();
s1651->s1635( s156, s1626 );
int s717 = (int)s156.size();
s156.resize( s717 );
*((s360*)s733)->s372() = s717;}
inline void s374::s1657( s501** s280, size_t s517 ){
Stream* s1651 = NULL;
if( s517 >= 3 ) {
s1651 = (Stream*)s280[2];}
else
s1651 = s1574;
wstring& s156 = *( (s374*)DR )->s372();
s1651->s1636( s156 );
int s717 = (int)s156.size();
s156.resize( s717 );
*( (s360*)s733 )->s372() = s717;}
inline void s374::s1141( s501** s280, size_t s517 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1147;
wstring s = DR->to_wstring();
bool s156 = regex_match( s, s1147, rg );
*s734->s372() = s156;}
inline void s374::s1664( s501** s280, size_t s517 ){
s323* pv = (s323*)s280[0];
pv->clear();
wstring s73 = L"\n";
if( s517 == 3 )
s73 = s280[2]->to_wstring();
wstring& s = ((s374*)DR)->s363;
size_t s69 = 0, s70 = 0;
s1::s9<s374> adds = new s374( ((s374*)DR)->s306, L"", ( (s374*)DR )->ns );
while( s70 != wstring::npos && s69 < s.size()) {
s70 = s.find( s73, s69 );
adds->s363 = s.substr( s69, s70 - s69 );
s69 = s70 + s73.size();
if( adds->s363.size() )
pv->s328().push_back( adds->s349() );}}
inline void s374::s1515( s501** s280, size_t s517 ){
( (s1448*)s733 )->s328() = DR->to_bytes();}
inline void s374::s427( s501** s280, size_t s517 ){
*( (s360*)s733 )->s372() = (int)*DR;}
void s374::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s363;}
size_t s374::s330() const{
return hash<wstring>{}(s363);}
bool s374::operator==( const s501* p ) const{
return ( (s374*)p )->s363 == s363;}
bool s374::operator<( const s501* p ) const{
return s363 < ( (s374*)p )->s363;}
Iterator* s374::s1304( const s501* idx ){
s1752::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i < 0 ) {
i = (int)s363.size() + i;
if( i < 0 )
i = 0;}
it = s363.begin() + i;}
return new s1753( this, it, it == s363.end() ? it : it + 1 );}
Iterator* s374::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( *it == *( (s1452*)_val )->s372() )
return new s1753( this, it, it + 1 );
return new s1753( this, end( s363 ), end( s363 ) );}
s501* s374::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1753*)it )->s1268() );
return new s360( s306, (int)n );}
Iterator* s374::s1328() {
return new s1753( this, s363.begin(), s363.begin() + 1 ); }
Iterator* s374::s1332() {
return new s1753( this, s363.end(), s363.end() ); }
Iterator* s374::s321( s400* rv ){
s1267 pr = rv->s1337( this );
return new s1753( this,
pr.first.s15<s1261*>()->s1268(), pr.second.s15<s1261*>()->s1268() );}
vector<wstring> s1044( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s872::s872( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s803, s736 ){
TDException s1059( s7::s1225, s1017, s736 );
if( l.empty() )
throw s1059.s1097( L"too few arguments" );
s280.assign( l.begin(), l.end() );
s512 = s1288;
s615::s1392( ( vector<s277*>& )l, s1044 );}
s872::s872( s268* s306 )
: s615( s306, NULL, NULL, s588, s803, NULL ){
s512 = s1288;}
void s872::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
wstring s731 = L"Invalid parameters of 'substr' function: ";
if( s280[0]->s366() != s1288 )
throw new s16( s731 + L"The first parameter is not of String type." );
str = s280[0].s15<s374*>();
size_t s761 = 1;
int s825 = 0;
s782 s811 = s754;
s755 =	nTo = 1;
s843 = s780 = 0;
while( s761 < s280.size() ) {
s503 par_ = s280[s761];
s489 pc = par_->s513();
if(	pc == s492 || pc == s1172 || pc == s491 || pc == s493 ) {
s503 par;
s507 rf;
if( pc == s492 ) {
rf = par_.s15<s386*>();
par = (s277*)rf->s393();}
else if( pc == s1172 ) {
rf = par_.s15<s386*>();
par = par_;}
else
par = par_;
if( par->s366() == s827->s366() ) {
if( rf->Id() == s1372 ) {
if( s825 != 0 )
throw new s16( s731 + L"'from' is misplaced." );
s825 = 1;
s811 = s809;}
else if( rf->Id() == s1380 ) {
if( s825 != 0 )
throw new s16( s731 + L"'to' is misplaced." );
s825 = 1;
s811 = s871;}
else if( rf->Id() == s1364 ) {
if( s811 != s754 && s825 >= 2 )
throw new s16( s731 + L"'before' is misplaced." );
if( s811 == s871 )
s780 = -1;
else
s843 = -1;
s825 = 2;}
else if( rf->Id() == s1360 ) {
if( s811 != s754 && s825 >= 2 )
throw new s16( s731 + L"'after' is misplaced." );
if( s811 == s871 )
s780 = 1;
else
s843 = 1;
s825 = 2;}
else if( rf->Id() == s1371 ) {
if( s811 != s754 && s825 >= 3 )
throw new s16( s731 + L"'first' is misplaced." );
s825 = 3;}
else if( rf->Id() == s1376 ) {
if( s811 != s754 && s825 >= 3 )
throw new s16( s731 + L"'last' is misplaced." );
if( s811 == s871 )
nTo = string::npos;
else
s755 = string::npos;
s825 = 3;}
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
else if( par->s366() == s1288 ) {
if( s811 == s809 )
s859 = par;
else if( s811 == s871 )
s851 = par;
else {
if( s859.s13() && s808.s13() )
s859 = par;
else if( s851.s13() && s758.s13() )
s851 = par;
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
s825 = 0; s811 = (( s811 == s809 || s811 == s754 ) ? s871 : s809 );}
else if( par->s366() == s1284 ) {
if( s811 == s809 )
s808 = par;
else if( s811 == s871 )
s758 = par;
else {
if( s859.s13() && s808.s13() )
s808 = par;
else if( s851.s13() && s758.s13() )
s758 = par;
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
s825 = 0; s811 = ( ( s811 == s809 || s811 == s754 ) ? s871 : s809 );}}
s761++;}}
s504 s872::s516( s501** s723, size_t s732 ){
size_t s196 = 0, s715 = string::npos;
wstring s805, s760;
wstring dom = str->s516( 0, 0 )->to_wstring();
if( s808.s14() ) {
if( s808->s513() == s493 )
s196 = (size_t)(int)*s808->s516( 0, 0 );
else
s196 = (size_t)(int)*s808.s15<s360*>();}
else if( s859.s14() ) {
s805 = s859->to_wstring();
if( s755 == 1 )
s196 = dom.find( s805 );
else if( s755 == string::npos )
s196 = dom.rfind( s805 );
else
throw new s16( L"substr: nFrom =" + std::to_wstring( s755 ) );
if( s843 > 0 )
s196 += s805.size();
else
s196 += s843;}
if( s758.s14() ) {
if( s758->s513() == s493 )
s715 = (size_t)(int)*s758->s516( 0, 0 );
else
s715 = (size_t)(int)*s758.s15<s360*>();}
else if( s851.s14() ){
s760 = s851->to_wstring();
if( nTo == 1 )
s715 = dom.find( s760, s196 );
else if( nTo == string::npos )
s715 = dom.rfind( s760 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s755 ) );
s715 += s780;}
if( s196 < 0 || s196 >= s715 || s196 >= dom.size() )
return s504();
wstring s156 = dom.substr( s196, s715 - s196 );
s610 = new s374( s306, s156, this );
return s610;}
s277* s872::s349()const{
return new s872( *this );}
s400::s400( s268* s306 )
: s336( s306, NULL, NULL ), s1072( false ), s1073( false ), s1085( 0 )//, s967( false )
{
s512 = s863.s13() ? 0 : s863->s366();
s1393 = new s1703( s306, 0 );
s1394 = new s1703( s306, U64_MAX );
s1316 = new s1703( s306, 0 );}
s400::s400( s268* s306, s336* s612, Iterator* it )
: s336( s306, NULL, NULL ), s1081( s612 ), s1640( it ), s1072( false ), s1073( false ), 
s1085( 0 ){
s512 = s863->s366();}
s400::s400( uint64_t _beg, uint64_t _end )
: s336( NULL, NULL, NULL ), s1072( false ), s1073( false ), s1085( 0 )//, s967( false )
{
s1393 = new s1703( s306, _beg );
s1394 = new s1703( s306, _end );
s512 = s863->s366();
s1316 = new s1703( s306, 0 );}
s400::s400( s268* s306, const wstring& s78, const s269* ast_ )
: s336( s306, NULL, ast_ ), s1072( false ), s1073( false ), s1085( 0 )//, s967( false )
{}
s400::s400( const s400& r, const s269* ast_ )
: s336( r.s306, r.ns, ast_ ), s1072( false ), 
s1073( false ), s1085( r.s1085 ), s1316( r.s1316 )//, s967( r.s967 )
{
s512 = r.s512;}
vector<wstring> s1038( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s400::s400( s268* s306, s278* s616, const vector<s277*>& l_, const s269* ast_ )
: s336( s306, s616, ast_ ), s1072( false ), s1073( false ), s1085( 0 ), 
s1316( new s1703( s306, 0 ) )//, s967( false )
{
s512 = s863->s366();
if( l_.empty() )
return;
TDException s1059( s7::s1223, s1018, ast_ );
if( l_.size() > 9 )
throw s1059.s1097( L"too many arguments" );
s615::s1392( ( vector<s277*>& )l_, s1038 );
const size_t s1162 = 3;
std::vector<s277*> l( s1162 );
if( l_[0]->s513() == s1172 ) {
s386* rf = (s386*)l_[0];
if( rf->Id() == s1374 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1703( s306, 0 );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1703( s306, 0 );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s612 = l[0];
s1393 = l[1];
s1394 = l[2];
if( s612.s13() ) {
s334 = s1703::proto->s366();
s324 = s1703::proto->s366();}
else {
s334 = 0;
s324 = 0;}
s512 = s863->s366();}
s501* s400::s369( const s269& s736, s278* s612, const wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && ( s.size() == s361.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s731 = L"Malformed Range definition: " + s;
vector<s277*> s740;
s277::s1500( s736, s306, s612, s346, s740 );
return new s400( s306, s612, s740, &s736 );}
else
return NULL;}
void s400::s519( const s278* s960, bool ){
TDException s1059( s7::s1005, s1018, s627(), L"wrong Range definition" );
ns = (s278*)s960;
bool s1308 = false;
try {
if( s612.s14() ) {
if( s612->s513() == s492 ) {
s612.s15<s386*>()->s519( s960 );
s1308 = s612->s1347();
s1081 = (s336*)s612.s15<s386*>()->s392();}
else if( s612->s513() == s495 ) {
s503 tmp = s277::s1120( s306, s612, (s278*)s960, (s615*)s960, s960->s304() );
s612 = tmp;
s1081 = (s336*)s612->s515();}
else {
s1081 = (s336*)s277::s1120( s306, s612, (s278*)s960, (s615*)s960, s960->s304() );}
s334 = s1081->ValType();
s324 = s1081->s327();}
if( s1393.s14() ) {
if( s1393->s513() == s492 )
s1393.s15<s386*>()->s519( s960 );
else {
s503 tmp = s277::s1120( s306, s1393, (s278*)s960, (s615*)s960, s960->s304() );
s1393 = tmp;}}
else
s1393 = s380.s15<s502*>();
if( s1394.s14() ) {
if( s1394->s513() == s492 )
s1394.s15<s386*>()->s519( s960 );
else {
s503 tmp = s277::s1120( s306, s1394, (s278*)s960, (s615*)s960, s960->s304() );
s1394 = tmp;}}
else
s1394 = s380.s15<s502*>();}
catch( s16* e ) {
throw e->s30( L"while compiling Range: '" + s627()->Src() + L"'" );}
s1413();
s1411( s1308 );}
void s400::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s400::s1384, s863->s366(),
{ s1238( { s1686::s1723 } ), s1238( { s1284, s1284 } ),
s1238( { s1686::s1681, s1284 } ),
s1238( { s1686::s1681, s1284, s1284 } ) }, 1, 3 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", NULL, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"max-element", new s351( L"resize", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", NULL, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"reverse", new s351( L"reverse", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
s1265 s400::s1340( const std::wstring& s357 ) const{
if( s1081.s14() ) 
return s1081->s1340( s357 );
return s350::s1340( s357 );}
s1265 s400::s1335( const std::wstring& s357, s1238& ap ) const{
if( s357 == L"new" )
return s350::s1335( s357, ap );
if( s1081.s14() )
return s1081->s1335( s357, ap );
assert( 0 );
throw;}
s1265 s400::s1330( const std::wstring& s357,
s1238& ap ) {
if( s357 == L"new" )
return s350::s1330( s357, ap );
if( s1081.s14() )
return s1081->s1330( s357, ap );
assert( 0 );
throw;}
s1170 s400::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"new" ) {
s717 = s1686::s1681;}
else if( s1081.s14() )
return s1081->s1331( s1727, l );
return s717;}
const vector<wstring>&
s400::s1334( const wstring& s357 ) const{
if( s357 == L"new" || s1081.s13() )
return s350::s1334( s357 );
else
return s1081->s1334( s357 );}
s501* s400::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s400( s306, s612, l, ast_ );}
inline bool
s400::s521( const s501* s522 ) const{
return ( ( (s400*)s522 )->s366() == s366() );}
size_t s400::s1260() const{
if( s1081.s14() )
return s1081->s1260();
else
return 0;}
s1267 s400::s1337(){
Iterator *fir = NULL, *sec = NULL;
if( s1081.s14() ) {
if( s1072 )
fir = s1081->s1326( s1393.s15<s501*>() );
else if( s1393 == s1695 )
fir = s1081->s1332();
else
fir = s1081->s1304( s1393.s15<s501*>() );
if( s1073 )
sec = s1081->s1326( s1394.s15<s501*>() );
else if( s1394 == s1695 )
sec = s1081->s1332();
else
sec = s1081->s1304( s1394.s15<s501*>() );
if( s1081->s1260() >= 1 && ( s1393 == s1695 || sec->operator<( fir ) ) ) {
( (s1241*)fir )->reverse();
( (s1241*)sec )->reverse();}}
return s1267( fir, sec );}
s1267 s400::s1337( s336* s616 ){
Iterator *fir, *sec;
if( s1072 )
fir = s616->s1326( s1393.s15<s501*>() );
else if( s1393 == s1695 )
fir = s616->s1332();
else 
fir = s616->s1304( s1393.s15<s501*>() );
if( s1073 )
sec = s616->s1326( s1394.s15<s501*>() );
else if( s1394 == s1695 )
sec = s616->s1332();
else
sec = s616->s1304( s1394.s15<s501*>() );
if( s616->s1260() >= 1 && ( s1393 == s1695 || sec->operator<( fir ) ) ){
( (s1241*)fir )->reverse();
( (s1241*)sec )->reverse();}
return s1267( fir, sec );}
inline void s400::s1384( s501** s280, size_t s517 ){
s400* r = ( (s400*)s280[1] );
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 ) 
{ return v.push_back( (s277*) s363 ); } );
s400* s1644 = new s400( r->s306, r->ns, v );
s1644->s519( r->ns );
*s280 = (s501*)s1644;}
s277* s400::s349() const{
return new s400( *this );}
void s400::s371( s277* p ) const{
p = new s400( *this );}
size_t s400::s330() const{
return (size_t)this;}
bool s400::operator==( const s501* p ) const{
return ( this == p );}
bool s400::operator<( const s501* p ) const{
return false;}
Iterator* s400::s321( s400* r ){
if( s1393.s14() ) {
s489 pc = s1393->s513();
if( pc == s493 )
s1716 = s1393->s516( 0, 0 );
else if( pc == s492 )
s1716 = s1393.s15<s386*>()->s392();
else
s1716 = s1393.s15<s501*>();}
if( s1394.s14() ) {
s489 pc = s1394->s513();
if( pc == s493 )
s1717 = s1394->s516( 0, 0 );
else if( pc == s492 )
s1717 = s1394.s15<s386*>()->s392();
else
s1717 = s1394.s15<s501*>();}
if( s1081.s14() )
return s1081->s321( this );
s1085 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1393.s15<s501*>();
return this;}
s277* s400::s322(){
if( s1085 == U64_MAX ) {
if( s1716.s14() ) {
if( s1716->s366() == s1701 )
s1085 = *s1716.s15<s1703*>()->s372();
else {
s1464 tmp;
s1716->s371( &tmp );
if( *tmp.s372() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1085 = *tmp.s372();}}
if( s1717.s14() ) {
if( s1717->s366() == s1701 )
s1720 = *s1716.s15<s1703*>()->s372();
else {
s1464 tmp;
s1717->s371( &tmp );
if( *tmp.s372() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1720 = *tmp.s372();}}
if( s1085 > s1720 )
incr = -1;
else
incr = 1;}
else
s1085 += incr;
if( s1085 == s1720 )
return NULL;
*s1316->s372() = s1085;
return s1316;}
s277* s400::s1052(){
return s325->s1052();}
const s277* s400::s1052() const{
return NULL;}
s277* s400::Idx(){
return NULL;}
s277* s400::El(){
return NULL;}
void s400::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Range :: " << L" curit: " << s325 << endl;}
vector<wstring> s1256( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1255::s1255( s268* s306, const wstring& s78, const s269* ast_ )
: s336( s306, NULL, ast_ ), s1084( s7::s1544, s306 ), s1085(NULL), s363( new s360( s306, 0 )), 
s717( new s360( s306, 0 )),s1521(0){
s512 = s1257.s13() ? 0 : s1257->s366();}
s1255::s1255( const s1255& r, const s269* ast_ )
: s336( r.s306, r.ns, ast_ ), s1084( s7::s1544, s306 ), s1085(NULL), s363( new s360( s306, 0 ) ),
s717( new s360( s306, 0 ) ), s1521(r.s1521){
*s363->s372() = (int)*r.s363;
*s717->s372() = (int)*r.s717;
ns = r.ns;
s512 = r.s512;}
s1170 s1627( size_t& idx, const vector<s277*>& l ){
if( l.size() > idx && l[idx]->s513() == s1172 )
idx++;
if( l.size() > idx )
return l[idx]->s366();
return 0;}
s1255::s1255( s268* s306, s278* s616, const vector<s277*>& l_, const s269* ast_ )
: s336( s306, s616, ast_ ), s1084( s7::s1544, s306 ), s1085(NULL),
s363( new s360( s306, 0 ) ),	s717( new s360( s306, 0 ) ),s1521(0){
s512 = s1257->s366();
ns = s616;
if( l_.empty() )
return;
TDException s1059( s7::s1537, s1018, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s1059.s1097( L"too many arguments" );
s615::s1392( ( vector<s277*>& )l_, s1256 );
const size_t s1162 = 3;
std::vector<s277*> l( s1162 );
if( !s306->TR().s1639( l_[0]->s366(), s1686::s1681 ) )
throw s1059.s1097( L"the type is not rangeable: " + l_[0]->s368() );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s366() == s1586 ) {
range = (s400*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s513() != s1172 || ((s386*)l_[bas])->Id() != s1498 )
throw s1059.s1097( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s513() != s1172 || ((s386*)l_[bas])->Id() != s1383 )
throw s1059.s1097( L"expected the 'where:' clause" );
if( l_[bas+2]->s513() != s1172 || ((s386*)l_[bas+2])->Id() != s1498 )
throw s1059.s1097( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s612 = l[0];
where = l[1];
s1179 = l[2];}
s501* s1255::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && ( s.size() == s361.size() || s[s.size() - 1] == L')' ) ) {
s503 fi = new s360( s306, 0 ), la = new s360( s306, 0 ), in = new s360( s306, 1 );
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong filter constructor syntax" );
wstring s731 = L"Malformed Filter definition: " + s;
const s269::s281& s737 = s736.s299();
size_t s732 = s737.size();
if( /*!s732 ||*/ s732 > 3 )
throw new s16( s731 );
std::vector<s277*> s280;
for( size_t n = 0; n < s732; ++n ) {
s269::s281::const_iterator it = s737.find( std::to_wstring( n ) );
s280.push_back( s277::s524( *it->second, s306, s612, s346 ) );}
return s370( s612, s280, &s736 );
if( s306->TR().s1639( s280[0]->s366(), s1686::s1681 ) )
return new s1255( s306, s612, s280 );
else
return new s1039( s306, s612, s280 );}
else
return NULL;}
void s1255::s519( const s278* s960, bool ){
TDException s1059( s7::s1005, s1018, s627(), L"wrong Filter definition");
ns = (s278*)s960;
if( s612.s13() )
return;
if( s612->s513() == s492 ) {
s507 rf = s612.s15<s386*>();
if( rf->s396().s13() )
rf->s519( s960 );
s1081 = rf.s15<s386*>()->s392();}
else if( s612->s513() == s495 ) {
s503 tmp = s277::s1120( s306, s612,(s278*)s960, (s615*)s960, s960->s304() );
s612 = tmp;
s1081 = s612->s515();}
else {
s1081 = (s501*)s277::s1120( s306, s612, (s278*)s960, (s615*)s960, s960->s304() );}
if( s1081->s513() == s491 ) {}
else if( s1081->s513() == s498 ) {}
else
throw s1059.s1097( L"unsupported container type" );
s1084.s394( 0, s306->TR().s1106( s1081.s15<s336*>()->ValType() ) );
s1084.s397( (s501*)this );
if( where.s14() ) {
if( where->s513() == s492 )
where.s15<s386*>()->s519( s960 );
else
where = s277::s1120( s306, where, (s278*)this, (s615*)s960, s960->s304() );}
if( s1179.s14() ) {
if( s1179->s513() == s492 ) {
s1179.s15<s386*>()->s519( s960 );
s334 = s1179->s515()->s366();}
else {
if( s1179->s513() != s1395 )
s1179 = s277::s1120( s306, s1179, (s278*)s960, (s615*)s960, s960->s304() );
s334 = s1179.s15<s905*>()->s1494();}}
if( !s334 )
s334 = s1081.s15<s336*>()->ValType();
s512 = s306->TR().s1153( s867::Cont( { s1257->s366(), 1, s334, 0 }) );
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" +
s306->TR().s1520( s306->TR().s854( s334 ) ) + L">";
s1521 = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s1413();}
void s1255::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s1255::s1384, s1257->s366(),
{ s1238( { s1284, s1284 } ) }, 1, 2 ) ) );
s362.insert( make_pair( L"to-vector", new s351( L"to-vector", &s1255::s1516, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"max-element", new s351( L"resize", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", NULL, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"reverse", new s351( L"reverse", NULL, s1286,
{ s1238() }, 0, 0 ) ) );
s362.equal_range( L"new" ).first->second->s1412( true );
s362.equal_range( L"to-vector" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
s1265 s1255::s1335( const std::wstring& s357, s1238& ap ) const{
return s350::s1335( s357, ap );
if( s357 == L"new" )
return s350::s1335( s357, ap );
assert( 0 );
throw;}
s1265 s1255::s1330( const std::wstring& s357, s1238& ap ){
if( s357 == L"new" ) {
auto ran = s356().equal_range( s357 );
s351* mi = ran.first->second;
s1265 s1385( s334, mi->s1258(), mi->s1347() );
return s1385;}
else if( s357 == L"to-vector" ) {
auto ran = s356().equal_range( s357 );
s351* mi = ran.first->second;
s1265 s1385( s1521, mi->s1258(), mi->s1347() );
return s1385;}
assert( 0 );
throw;}
s1170 s1255::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"new" ) {
s717 = s1686::s1681;}
else if( s1727 == L"to-vector" ) {
s717 = s1521;}
return s717;}
s501* s1255::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1255( s306, s612, l, ast_ );
s1170 pt = l[0]->s366();
if( s306->TR().s1639( pt, s1686::s1681 ) )
return new s1255( s306, s612, l );
s615::s1392( ( vector<s277*>& )l, s1256 );
s489 pc = l[0]->s513();
vector<s277*> s998;
size_t s390 = 0;
if( pc == s491 ) {
if( pt == s1284 ) {
if( l.size() > 1 && l[1]->s366() == s1284 ) {
s998 = { l[0], l[1] };
s390 = 1;}
else {
s998 = { l[0] };
s390 = 2;}}}
else if( pc == s1172 ) {
if( ( (s386*)l[0] )->s1466() == s1380 ) {
s998 = { l[1] };
s390 = 2;}
else if( ( (s386*)l[0] )->s1466() == s1372 ) {
s998 = { l[1], l[3] };
s390 = 4;}}
vector<s277*> l1 = { new s1039( s306, s612, s998 ) };
l1.insert( l1.end(), l.begin() + s390, l.end() );
return new s1255( s306, s612, l1 );
if( l.size() ) {
if( l[0]->s513() == s492 ) {
l[0]->s519( s612 );
if( s306->TR().s1639( l[0]->s366(), s1686::s1681 )  )
return new s1255( s306, s612, l );}}
else {
return new s1255( s306, s612, l );}
return new s1039( s306, s612, l );}
s501* s1255::s370( s278* s612, const std::vector<s1170>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1255* s717 = new s1255( s306, L"" );
s867::Cont s1182;
s509::s1107( vt, idx, s1182 );
s867 s1180( s1182[0] );
return s717;}
inline bool
s1255::s521( const s501* s522 ) const{
return ( ((s1255*)s522)->s366() == s366() );}
inline void s1255::s1384( s501** s280, size_t s517 ){
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
s1255* pf = (s1255*)s280[1];
*s280 = ( s501* ) pf->s370( pf->ns, v, pf->s627() );
s280[0]->s519( pf->ns );
pf->s1084.s397( s280[0] );
pf->s1085 = ((s1255*)s280[0])->s1085;}
inline void s1255::s1516( s501** s280, size_t s517 ){
s1255* pf = (s1255*)s280[1];
*s280 = ( s501* ) pf->s306->TR().
s1106( pf->s1521 )->s370( pf->ns );
Iterator* s1123 = pf->s321( NULL );
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() )
break;
( (s323*)s280[0] )->add( p->s349() );}
s280[0]->s1413();}
s277* s1255::s349() const{
return new s1255( *this );}
void s1255::s371( s277* p ) const{
p = new s1255( *this );}
size_t s1255::s330() const{
return (size_t)this;}
bool s1255::operator==( const s501* p ) const{
return ( this == p );}
bool s1255::operator<( const s501* p ) const{
return false;}
bool
s1255::s579( const wstring& s708, s386* ref, const wstring& s346, bool ) const{
if( s708 == s7::s1544 ) {
ref->s1510( (s386*)&s1084 );
return true;}
return false; // ns->s579( s708, ref, s346 );
}
s277* s1255::s622( size_t off ){
assert( off == 0 );
if( s1085 )
return s1085;
return (s277*) s1084.s523();}
s1267 s1255::s1337(){
if( range.s14() )
return range->s1337();
else
return s1081.s15<s336*>()->s1337();}
Iterator* s1255::s321( s400* r ){
if( range.s14() ) {
s1267 pr = range->s1337( );
s325 = pr.first;
s1663 = pr.second;}
else {
s1267 pr = s1081.s15<s336*>()->s1337();
s325 = pr.first;
s1663 = pr.second;}
return this;}
s277* s1255::s322(){
while( 1 ) {
s1085 = s325->s322();
if( !s1085 || s325->operator==( s1663 ) )
return NULL;
if( where.s14() && ( false == (bool)*where->s516(0,0) ) )
continue;
break;}
if( s1179.s14() )
return s1179->s516( 0, 0 ).s15<s502*>();
else
return s1085;}
s277* s1255::s1052(){
return s325->s1052();}
const s277* s1255::s1052() const{
return NULL;}
s277* s1255::Idx(){
return NULL;}
s277* s1255::El(){
return NULL;}
void s1255::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s201 ) << L"Input: ";
if( s612.s14() ) {
s1081.s14() ? s1081->s310( pd, s201 + s434 ) : s612->s310( pd, s201 + s434 );}
buf << s4::fill_n_ch( L' ', s201 ) << L"Do: ";
if( s1179.s14() ) s1179->s310( pd, s201 + s434 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s201 ) << L"curitref: ";
s1084.s310( pd, 0 );
buf << endl;}
s1039::s1039( s268* s306 ) 
: s336( s306, NULL, NULL ) {
s512 = s1468.s13() ? 0 : s1468->s366();}
s1039::s1039( s268* s306, s278* s612, const std::vector<s277*>& l, const s269* ast_ )
: s336( s306, s612, ast_ ), s1154( true ){
if( l.empty() )
return;
wstring s1095 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s1095 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s512 = s1468->s366();}
s1039::~s1039(){}
s501* s1039::s369( const s269& s736, s278* s612, const wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && ( s.size() == s361.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s731 = L"Malformed Sequence definition: " + s;
vector<s277*> s740;
s277::s1500( s736, s306, s612, s346, s740 );
return new s1039( s306, s612, s740 );}
else
return NULL;}
s501* s1039::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1039( s306, s612, l, ast_ );}
void s1039::s519( const s278* s960, bool ){
if( end.s13() )
return;
wstring s1095 = L"wrong sequence generator syntax";
s503 tmp = s277::s1120( s306, end, (s278*)s960, (s615*)s960, s960->s304() );
end = tmp;
if( start.s14() ) {
tmp = s277::s1120( s306, start, (s278*)s960, (s615*)s960, s960->s304() );
start = tmp;}
else {
if( end->s366() == s1284 )
start = new s360( s306, 0 );
else {
start = s306->TR().s541( end->s366(), (s278*)s960, s960->s304() );
start->s519( s960 );}}
if( incr.s14() ) {
tmp = s277::s1120( s306, incr, (s278*)s960, (s615*)s960, s960->s304() );
incr = tmp;}
else {
if( start->s366() == s1284 )
incr = new s360( s306, 1 );
else
throw new s16( s1095 + L": increment value is missing" );}
s1086 = start->s349();
s1835 = start->s349();
std::vector<s277*> pl = { s1086, incr };
s584 cs( s306, L"sumeq", pl, NULL );
s1167 = s615::s624( &cs, s306, (s278*)s960, (s615*)s960, s960->s304(), false );
s1167->s519( s960, false );
std::vector<s277*> pl1 = { s1086, start };
s584 cs1( s306, L"set", pl1, NULL );
set = s615::s624( &cs1, s306, (s278*)s960, (s615*)s960, s960->s304(), false );
set->s519( s960, false );
std::vector<s277*> pl2 = { s1086, end };
s584 cs2( s306, L"eq", pl2, NULL );
eq = s615::s624( &cs2, s306, (s278*)s960, (s615*)s960, s960->s304(), false );
eq->s519( s960, false );
s1343 = s1284;
s334 = start->s366();}
s1267 s1039::s1337(){
s1::s1444<Iterator> it = this;
s1::s1444<Iterator> it1 = it;
return make_pair( it, it1 );}
Iterator* s1039::s321( s400* r ){
set->s516( 0, 0 );
s1154 = true;
return this;}
s277* s1039::s322(){
if( s1154 )
s1154 = false;
else
s1167->s516( 0, 0 );
if( (bool)*eq->s516( 0, 0 ) )
return NULL;
s1086.s15<s501*>()->s371( s1835 );
s1835->s1413();
return s1835;}
void s1039::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s1039::s1384, s1468->s366(),
{ s1238( { s1284 } ), s1238( { s1284, s1284 } ), s1238( { s1284, s1284, s1284 } ) }, 
1, 2 ) ) );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
bool s1039::operator==( const Iterator* p ) const{
return false;}
bool s1039::operator<( const Iterator* p ) const{
return this < p;}
inline void s1039::s1384( s501** s280, size_t s517 ){
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
*s280 = ( s501* ) new s1039( ( (s1039*)s280[1] )->s306, NULL, v );
s280[0]->s519( ((s1039*)s280[1])->ns );}
s277* s1039::s349() const{
return new s1039( *this );}
void s1039::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"SequenceGenerator : " << endl;
start->s310( pd, s201 + s434); buf << L", "; end->s310( pd, 0); 
buf << L", "; incr->s310( pd, 0 );}
s1170 s1686::s1681 = 0;
s1170 s1686::s1680 = 0;
s1170 s1686::s1682 = 0;
bool _cmp( const s503& l_, const s503& r_ ){
s501* l = l_.s15<s501*>();
s501* r = r_.s15<s501*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s503 l, const s503 r ) const{
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
struct s1295{
std::vector<s503>s932;
s506 s930;
s1295( /*s506 s931*/ ) : s930( /*s931*/0 ) { s932.resize( 2 ); }
bool operator()( const s503& l, const s503& r ){
if( s930.s14() ) {
s932[0] = l;
s932[1] = r;
s930->s620( s932 );
return (bool)*s930->s516( 0, 0 );}
else
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
Iterator* s336::s1304( const s501* idx ){
throw new s16( L"this iterable type doesn't support access by index" );}
Iterator* s336::s1326( const s501* idx ){
throw new s16( L"this iterable type doesn't support search for value" );}
Iterator* s336::s1386( const s501* idx ){
throw new s16( L"this iterable type doesn't support distancing between elements" );}
s501* s336::s1333( Iterator* ){
throw new s16( L"this iterable type doesn't support indexing" );}
struct s908;
s501* s336::sort( bool, s908* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s955 );}
template <class _Cont, class s1477, class Der>
s320<_Cont, s1477, Der>::s320( const s1311& r )
: s336( r ){}
void s1300( s268* s306, const wstring& s78, wstring& s1427, wstring& s673 ){
assert( !s78.empty() );
wstring sv = s78;
wsmatch s1183, rgres1;
wregex s1406( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
wregex s1407( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(.*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1183, s1407 ) ) {
s867::Cont vt;
s1427 = s1183[1].str();
if( regex_match( sv, rgres1, s1406 ) ) {
s673 = L"] " + //s1427 + L" " +
( s1183[s1183.size()-1].str().empty() ? L"0" : s1183[s1183.size()-1].str() );}
else {
s673 = s1183[2];}}}
s1266::s1266( s268* s306, const std::wstring& s78, const s269* ast_ )
: s350( s306, NULL, ast_ ), s334( 0 ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s1855( s7::s941 );}
s1266::s1266( const s1266& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s612( right.s612 ), s363( right.s363 ),
s334( right.s334 ){
s512 = right.s512;
s1413();}
s1266::s1266( s268* s306, s278* s612, Iterator* it, const s269* ast_ )
: s350( s306, NULL, ast_ ), s363( it ), s334( 0 ){
s512 = proto->s366();
s1413();}
s501* s1266::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv[0] != L'(' )
throw new s16( L"wrong Position constructor syntax" );
wstring s731 = L"Malformed Position declaration: " + s;
const s269::s281& s737 = s736.s299();
size_t s732 = s737.size();
if( s732 )
throw new s16( s731 );
return s370( s612, vector<s277*>(), &s736 );}
else
return NULL;}
void s1266::s519( const s278* s960, bool ){
if( s363.s14() && !s334 ) {
s334 = s363->ValType();
s867::Cont v = { s1755, 1, s334, 0 };
s512 = s306->TR().s1153( v );
if( s512 == s1755 ) {
s867::Cont v = { s1755, 1, s334, 0 };
s512 = s306->TR().s1153( v );}}}
s1170 s1266::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get-el" )
s717 = s334;
return s717;}
s501* s1266::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1266( s306, L"", ast_ );}
s501* s1266::s370( s278* s612, const std::vector<s1170>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s867::Cont s1219;
s509::s1107( vt, idx, s1219 );
s1266* s717 = new s1266( s306, 0, NULL );
s717->ns = s612;
s717->s334 = s1219[0];
s867 s646( vt );
s717->s512 = s306->TR().s1110( vt );
return s717;}
void s1266::s364(){
s362.insert( std::make_pair( L"eq", new s351( L"eq", &s1266::s413, s1274,
{ s1238( {s7::s1565} ) }, 1, 1 ) ) );
s362.insert( std::make_pair( L"get-el", new s351( L"get-el", &s1266::s1765, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"get-idx", new s351( L"get-idx", &s1266::s1924, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"neq", new s351( L"neq", &s1266::s418, s1274,
{ s1238( {s7::s1565} ) }, 1, 1 ) ) );
s362.insert( std::make_pair( L"set", new s351( L"set", &s1266::s402, s1286,
{ s1238( {s7::s1565} ) }, 1, 1 ) ) );
s362.equal_range( L"get-el" ).first->second->s1412( true );}
s277* s1266::s349() const{
return new s1266( *this );}
void s1266::s371( s277* p ) const{
p = new s1266( *this );}
size_t s1266::s330() const{
return (size_t)this;}
void s1266::operator=( const s1266& p ){
s612 = p.s612;
s363 = p.s363;
s334 = p.s334;
s512 = p.s512;}
bool s1266::operator==( const s501* p ) const{
return s363->operator==( ((s1266*)p)->s363 );}
bool s1266::operator<( const s501* p ) const{
return s363->operator<( ((s1266*)p)->s363 );}
#undef s733
#define s733 ((s1266*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
inline void s1266::s1765( s501** s280, size_t s517 ){
*s280 = (s501*)((s1266*)DR )->s363->s1052();}
inline void s1266::s1924( s501** s280, size_t s517 ){
*s280 = (s501*)((s1266*)DR )->s363->Idx();}
inline void s1266::s413( s501** s280, size_t s517 ){
*s734->s372() = ( (s1266*)DR )->s363->operator==( ( (s1266*)s280[2] )->s363 );}
inline void s1266::s418( s501** s280, size_t s517 ){
*s734->s372() = !( (s1266*)DR )->s363->operator==( ( (s1266*)s280[2] )->s363 );}
inline void s1266::s402( s501** s280, size_t s517 ){
*(s1266*)DR = *(s1266*)s280[2];}
void s1266::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Position : " <<
this << endl;}
s1055::s1055( s323* v_, s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1358( (uint64_t)-1 ), s1314( new s1703(NULL, -1) ), 
s1313( new s1048(NULL, vector<s277*>( { s1314, s380 } )) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1055::s1055( s323* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1662( sent ), s1358( (uint64_t)-1 ), s1314( new s1703(NULL, -1) ), 
s1313( new s1048(NULL, vector<s277*>( { s1314, s380 } )) ){
if( v.s14() ) {
s1358 = v->size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s967 = true;}
s1055::s1055( s1055* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1703(NULL, 0) ), 
s1313( new s1048( NULL, vector<s277*>( { s1314, *s1359 } )) ){
s967 = it->s967;}
void s1055::reverse(){
s967 = true; 
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1055::s322(){
s277* s717 = NULL;
if( !s967 ) {
if( s1359 != s1200 ) {
s717 = *s1359;
s1359++;
s1358++;}}
else {
if( s1409 != s1662 ) {
s717 = *s1409;
s1409++;
s1358--;}}
return s717;}
s277* s1055::s1052(){
if( !s967 ) {
if( s1359 == v->s328().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1359;}
else {
if( s1409 == v->s328().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1409;}}
const s277* s1055::s1052() const{
if( !s967 ) {
if( s1359 == v->s328().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1359;}
else {
if( s1409 == v->s328().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1409;}}
s277* s1055::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1055::El(){
if( !s967 ) {
if( s1359 == v->s328().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1359;}
else {
if( s1409 == v->s328().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1409;}}
s1170 s1055::ValType() const{
return v->ValType();}
bool s1055::operator==( const Iterator* r ) const{
if( !s967 ) {
return s1359 == ( (s1055*)r )->s1359;}
else {
return s1409 == ( (s1055*)r )->s1409;}}
bool s1055::operator<( const Iterator* r ) const{
if( !s967 ) {
if( s1359 == v->s328().end() )
return false;
return s1359 < ( (s1055*)r )->s1359;}
else {
if( s1409 == v->s328().rend() )
return false;
return s1409 < ( (s1055*)r )->s1409;}}
s1051::s1051( s792* v_, 
s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1358( (uint64_t)-1 ), s1314( new s1703( NULL, 0 ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1051::s1051( s1051* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1703( NULL, 0 ) ){}
s277* s1051::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = *s1359;
++s1359;
++s1358;}
return s717;}
s277* s1051::s1052(){
return *s1359;}
const s277* s1051::s1052() const{
return *s1359;}
s277* s1051::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1051::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
s1170 s1051::ValType() const{
return v->ValType();}
s1025::s1025( s332* v_, s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1314( s380 ), s1313( new s1048( NULL,
vector<s277*>(	{ s1314, s380 } ) ) ){}
s1025::s1025( s1025* it )
: v( it->v ), s1359( it->s1359 ), s1314( s380 ), s1313( new s1048( NULL, 
vector<s277*>(	{ s1314, s380 } ) ) ){}
s277* s1025::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = s1359->second;
++s1359;}
return s717;}
s277* s1025::s1052(){
return (*s1359).second.s15<s502*>();}
const s277* s1025::s1052() const{
return (*s1359).second.s15<s502*>();}
s277* s1025::Idx(){
return (*s1359).first.s15<s502*>();}
s277* s1025::El(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s1313->assign( vector<s503>(
{ ( *s1359 ).first.s15<s502*>(),( *s1359 ).second.s15<s502*>() } ));
s717 = s1359->second;
++s1359;}
return s717;}
void s1025::reverse(){
s967 = true;
s1409 = std::make_reverse_iterator( s1359 );}
s1170 s1025::ValType() const{
return v->ValType();}
bool s1025::operator==( const Iterator* r ) const{
if( !s967 )
return s1359 == ( (s1025*)r )->s1359;
else
return s1409 == ( (s1025*)r )->s1409;}
s1553::s1553( s1552* v_, s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1314( s380 ), s1313( new s1048( NULL,
vector<s277*>( { s1314, s1359->second } ) ) ){}
s1553::s1553( s1553* it )
: v( it->v ), s1359( it->s1359 ), s1314( s380 ), s1313( new s1048( NULL,
vector<s277*>( { s1314, s1359->second } ) ) ){}
s277* s1553::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = s1359->second;
++s1359;}
return s717;}
s277* s1553::s1052(){
return ( *s1359 ).second.s15<s502*>();}
const s277* s1553::s1052() const{
return ( *s1359 ).second.s15<s502*>();}
s277* s1553::Idx(){
return ( *s1359 ).first.s15<s502*>();}
s277* s1553::El(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s1313->assign( vector<s503>(
{ ( *s1359 ).first.s15<s502*>(),( *s1359 ).second.s15<s502*>() } ) );
s717 = s1359->second;
++s1359;}
return s717;}
s1170 s1553::ValType() const{
return v->ValType();}
bool s1553::operator==( const Iterator* r ) const{
return s1359 == ( (s1553*)r )->s1359;}
s1449::s1449( s1448* v_, s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1358( (uint64_t)-1 ), s1314( new s1703( NULL, -1 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, s1452::proto } ) ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1449::s1449( s1448* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1662( sent ), s1358( (uint64_t)-1 ), s1314( new s1703( NULL, -1 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, s1452::proto } ) ) ){
if( v.s14() ) {
s1358 = v->size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s967 = true;}
s1449::s1449( s1449* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1703( NULL, 0 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, new s1452( NULL, *s1359)  } ) ) ){
s967 = it->s967;}
void s1449::reverse(){
s967 = true;
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1449::s322(){
s277* s717 = NULL;
if( !s967 ) {
if( s1358 < v->s328().size() )
s717 = new s1452( NULL, v->s328()[s1358++] );}
else {
if( s1358 != U64_MAX )
s717 = new s1452( NULL, v->s328()[s1358--] );}
return s717;}
s277* s1449::s1052(){
return new s1452( NULL, *s1359 );}
const s277* s1449::s1052() const{
return new s1452( NULL, *s1359 );}
s277* s1449::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1449::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
s1170 s1449::ValType() const{
return v->ValType();}
bool s1449::operator==( const Iterator* r ) const{
if( !s967 )
return s1359 == ( (s1449*)r )->s1359;
else
return s1409 == ( (s1449*)r )->s1409;}
bool s1449::operator<( const Iterator* r ) const{
if( !s967 )
return s1359 < ( (s1449*)r )->s1359;
else
return s1409 < ( (s1449*)r )->s1409;}
s1753::s1753( s374* v_, s1026 it, s1026 sent )
: v( v_ ), s1359( it ), s1200( sent ), s1358( (uint64_t)-1 ), s1314( new s1703( NULL, -1 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, s1748::proto } ) ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1753::s1753( s374* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1662( sent ), s1358( (uint64_t)-1 ), s1314( new s1703( NULL, -1 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, s1748::proto } ) ) ){
if( v.s14() ) {
s1358 = v->s328().size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s967 = true;}
s1753::s1753( s1753* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1703( NULL, 0 ) ),
s1313( new s1048( NULL, vector<s277*>( { s1314, new s1748( NULL, *s1359)  } ) ) ){
s967 = it->s967;}
void s1753::reverse(){
s967 = true;
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1753::s322(){
s277* s717 = NULL;
if( !s967 ) {
if( s1358 < v->s328().size() )
s717 = new s1748( NULL, v->s328()[s1358++] );}
else {
if( s1358 != U64_MAX )
s717 = new s1748( NULL, v->s328()[s1358--] );}
return s717;}
s277* s1753::s1052(){
return new s1748( NULL, *s1359 );}
const s277* s1753::s1052() const{
return new s1748( NULL, *s1359 );}
s277* s1753::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1753::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
s1170 s1753::ValType() const{
return v->ValType();}
bool s1753::operator==( const Iterator* r ) const{
if( !s967 )
return s1359 == ( (s1753*)r )->s1359;
else
return s1409 == ( (s1753*)r )->s1409;}
bool s1753::operator<( const Iterator* r ) const{
if( !s967 )
return s1359 < ( (s1753*)r )->s1359;
else
return s1409 < ( (s1753*)r )->s1409;}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
vector<wstring> s1476( { L":typedTable", L":untypedTable" } );
s323::s323( s268* s306, s278* s612, const wstring& s78, const s269* ast_,
const s1873& s1937 )
: s1751( s306, s612, ast_ ){
TDException s1059( s7::s1535, s1018, ast_ );
s1343 = s1284;
if( s78.size() ) {
load( s78, s612, s1937 );}
if( !s512 )
s512 = ( s323::proto.s13() ? 0 : s1897 );}
s323::s323( const s323& right, const s269* ast_ )
: s1751( right.s306, right.ns, ast_ ){
s363 = right.s363;
s1343 = right.s1343;
s334 = right.s334;
s324 = right.s324;
s512 = right.s512;
s1855( right.s644() );}
s323::s323( s268* s306, const std::vector<s277*>& l,
s278* s612, const s269* ast_, s1170 s744,	s1170 s1430 )
: s1751( s306, s612, ast_ ){
s1343 = s1284;
s334 = s1430;
s324 = s1430;
if( s744 )
s512 = s744;
else
s512 = s323::proto.s13() ? 0 : s1897;
if( l.size() )
s615::s1392( ( vector<s277*>& )l, s1476 );
if( l.size() && ( l[0]->s366() == s366() ||
l[0]->s366() == s1897 ) ) {
s363.assign( ( (s323*)l[0] )->s363.begin(),
( (s323*)l[0] )->s363.end() );}}
s323::s323( s268* s306, s1170 s1431, s278* s612, const s269* ast_ )
: s1751( s306, s612, ast_ ){
s1343 = s1284;
s334 = s1431;
s324 = s1431;
if( s1431 ) {
s867::Cont v = { s1897, 1, s334, 0 };
s512 = s306->TR().s1153( v );}}
s323::~s323(){
s363.clear();}
void s323::s1479( const vector<s277*>& s740, s278* s612 ){
assert(0);
TDException s1059( s7::s1457, s1018, s627() );
if( s740.empty() )
return;
s489 pc = s740[0]->s513();
if( pc == s492 && s612->s513() != s493 ) {
throw s1059.s1097( L"references are not allowed in constructors of data members" );}
if( s740[0]->s366() == s366() ||
s740[0]->s366() == s1897 ) {
s363.assign( ( (s323*)s740[0] )->s363.begin(),
( (s323*)s740[0] )->s363.end() );}}
void s323::s1299( const wstring& s78, s278* s612, const s1873& s1937 ){
assert( !s78.empty() );
wstring s1427, s673, s1417;
if( s78[0] == L'[' ) {
s1417 = s78;}
else {
s1300( s306, s78, s1427, s673 );
if( !s673.empty() && s673[0] == L'[' )
s1417 = s673;
if( !s1427.empty() )
s1297( s1427, s512, s334 );}
if( !s1417.empty() ) {
load( s1417, s612, s1937 );}
else if( !s673.empty() ) {
if( s673[0] == L']' && s673.find_first_not_of(
s4::digits + s4::s49, 1 ) == string::npos ) {
s363.push_back( 0 );
s363.push_back( new s374( s306, s673, ns ) );}}}
s1170 s323::s1338( const std::wstring& s1427, s867::Cont& s612 ){
s1170 s717;
s867::Cont vt;
size_t pos = 0;
s1170 s1431 = 0;
s306->TR().s1163( s1427, pos, vt );
s717 = s306->TR().s1110( s867( vt ), false );
if( s717 ) {
s612 = { s1897, 1, vt[2], 0 };
return s717;}
s867::Cont s1437( begin( vt ) + 2, end( vt ) );
if( s1437.size() > 2 )
s1431 = s306->TR().s1153( s1437 );
else
s1431 = s1437[0];
s612 = { s1897, 1, s1431, 0 };
s717 = s306->TR().s1153( s612 );
return s717;}
void s323::s1297( const std::wstring& s1427, s1170& pt, s1170& vt ){
s867::Cont s612;
pt = s1338( s1427, s612 );
vt = s612[2];}
void s323::load( const wstring& s78, s278* s612, const s1873& s1937 ){
TDException s1059( s7::s1245, s1018, s627() );
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( s334, s612, s612->s304() ) );
return;}
size_t pos = 0;
const s1032* s1158 = NULL;
if( s627() && s627()->Nqj() )
s1158 = s627()->Nqj()->s1105();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1158, s78, pos, s96, s1937 );
wstring ownerName = s627()->s274( L"ownerName" );
bool s1492 = false;
if( ( s627()->s274( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1492 = true;
if( s96.size() ) {
s1170 pt = 0;
for( size_t n = 0; n < s96.size(); ++n ) {
s1034 s230 = new s269( L"", *s96[n] );
s230->s1511( s334 );
s363.push_back( s277::s524( *s230, s306, s612, s612->s304() ) );
if( s363.back()->s513() != s492 ) {
if( n == 0 )
pt = s363.back()->s366();
else if( pt && s363.back()->s366() != pt )
throw s1059.s1097( L"different elements types in vector" );}}
if( !s1492 ) {
if( !s334 && s363[0]->s366() ) {
s334 = s363[0]->s366();
s867::Cont v1 = { s1897, 1, s334, 0 };
s512 = s306->TR().s1153( v1 );}
else if( s334 != s363[0]->s366() )
throw s1059.s1097( L"vector's element type doesn't match the vector type" );}}}
s501* s323::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
TDException s1059( s7::s1458, s1018, &s736,
L"wrong Vector constructor syntax" );
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s361 = s368();
wstring s1427, s673;
s1170 pt = 0, vt = 0;
if( s736.s274( L"ownerType" ) == L"CallSite" ) {
wstring s1489 = s736.s274( L"ownerName" );
if( s1489.find( L"new<Vector<" ) == 0 ) {
wstring stype = s1489.substr( 4, s1489.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s1059.s1097( L"missing element type" );
s1300( s306, s, s1427, s673 );
if( !s673.empty() && ( s673[0] == L'[' || s673[0] == L']' ) )
sv = s673;
if( !s1427.empty() )
s1297( s1427, pt, vt );}
else
return 0;
s323* s717 = new s323( s306, vector<s277*>({ }), s612, &s736,
pt, vt );
s717->load( sv, s612, s1914 );
return s717;}
void s323::s519( const s278* s960, bool ){
wstring s78 = L"";
TDException s1059( s7::s1009, s1018, s627() );
if( s363.size() == 2 && s363[0].s13() )
s78 = s363[1]->to_wstring();
if( s960->s513() != s493 ||
( (s278*)s960 )->s305() != L"new" || s306->s1496() ) {
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( s334, (s278*)s960, s960->s898() ) );}
else {
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s960 );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1203 = s277::s1120( s306, s363[n], (s278*)s960, (s615*)s960, s960->s304() );
s363[n] = s1203->s516( 0, 0 ).s15<s502*>();
if( !s334 )
s334 = s363[0]->s366();
else if( s334 != s363[n]->s366() )
throw s1059.s1097( L"elements have different types" );}}
if( s512 || s512 == s1897 ) {
if( !s334 )
throw s1059.s1097( L"vector's element type is not specified" );
s867::Cont s612 = { s1897, 1, s334, 0 };
s512 = s306->TR().s1153( s612 );}
s1413();}}
void s323::s1060( const wstring& s880, const s1898& tbfr, s278* s612,
const s269* ast_ ){
TDException s1059( s7::s1010, s1018, ast_ );
vector<wstring> s855;
s4::s58( s4::s53( s880, s49 ), tbfr.rowSep, s855 );
s1873 s1926 = s1914;
s1926.s1875 = tbfr.s1875;
for( wstring row : s855 ) {
if( !tbfr.mixedTypes ) {
s363.push_back( new s323( s306, s306, row, NULL, tbfr.s1875 ) );}
else {
s1048* pd = (s1048*)s306->TR().s1106( s334 )->s349();
pd->load( row, s612, s1926 );
s363.push_back( pd );}}}
void s323::s364(){
s1751<s1589, s503, s323>::s364();
s362 = s1751<s1589, s503, s323>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s323::s1384, s1286,
{ s1238(), s1238( { s7::s1564, s7::s1570 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s362.emplace( make_pair( L"set", new s351( L"set", &s323::s402, s1286,
{ s1238( { s1686::s1681 } ) }, 1, 1, false ) ) );
s362.emplace( make_pair( L"set-el", new s351( L"set-el", &s323::s1415, s1286,
{ s1238( { s1686::s1723, s7::s1568 } ) }, 2, 2, false ) ) );
s362.emplace( make_pair( L"get", new s351( L"get", &s323::s337, 0,
{ s1238( { s1686::s1723 } ) }, 1, 1, true ) ) );
s362.emplace( make_pair( L"append", new s351( L"append", &s323::s1480, s1286,
{ s1238( { s7::s1568 } ) }, 1, 1, false ) ) );
s362.emplace( make_pair( L"resize", new s351( L"resize", &s323::s340, s1286,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.emplace( make_pair( L"reserve", new s351( L"reserve", &s323::s2068, s1286,
{ s1238( { s1686::s1723 } ) }, 1, 1, false ) ) );
s362.emplace( make_pair( L"eq", new s351( L"eq", &s323::s413, s1284,
{ s1238( { s7::s1565 } ) }, 1, 1, true ) ) );
s362.emplace( make_pair( L"for-each", new s351( L"for-each", &s323::s1923, s1286,
{ s1238( { s7::s1569 } ) }, 1, 1, false ) ) );
s362.emplace( make_pair( L"load-table", new s351( L"load-table", &s323::s852,
s1284, { s1238( { s7::s1564, s7::s1570 } ) }, 0, 0, false, { L":mixedTypes", 
L":stringsQuoted", L":promInts", L"colNames", L"fieldSep:", L"rowSep:", L":emptyElements" } ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"new" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1583, s1686::s1682 );
s306->TR().s1301( s512, s7::s1581, s1686::s1680 );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
s501* s323::s370( s278* s612, const vector<s277*>& l, const s269* ast_ ) const{
if( !s334 )
throw new s16( L"vector's element type is not specified" );
return new s323( s306, l, s612, ast_, s512, s334 );}
s501* s323::s370( s278* s612, const std::vector<s1170>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s323* s717 = new s323( s306, 0, NULL );
s717->ns = s612;
s717->s334 = vt[2];
s867 s646( vt );
s717->s512 = s306->TR().s1110( s646 );
return s717;}
s1170 s323::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get" )
s717 = s334;
else if( s1727 == L"new" )
s717 = s512;
else
s717 = s1751::s1331( s1727, l );
return s717;}
inline bool
s323::s521( const s501* s522 ) const{
return ( ( (s323*)s522 )->s324 == s324 );}
s277* s323::s349() const{
return new s323( *this );}
void s323::s371( s277* p ) const{
s323* pv = (s323*)p;
pv->s363.assign( s363.begin(), s363.end() );
pv->s1855( wh );}
Iterator* s323::s1304( const s501* idx ){
s1589::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i < 0 ) {
i = (int)s363.size() + i;
if( i < 0 )
i = 0;}
it = s363.begin() + i;}
return new s1055( this, it, it == s363.end() ? it : it+1 );}
Iterator* s323::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( it->s15<s501*>()->operator==( _val ) )
return new s1055( this, it, it+1 );
return new s1055( this, end( s363 ), end( s363 ));}
s501* s323::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1055*)it )->s1268() );
return new s360( s306, (int)n );}
Iterator* s323::s1328() {
if( s363.size() )
return new s1055( this, s363.begin(), s363.begin()+1 ); 
return new s1055( this, s363.end(), s363.end() ); }
Iterator* s323::s1332() {
return new s1055( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s323*)(s502*)*s280)
inline void s323::s1384( s501** s280, size_t s517 ){
s323* ps = (s323*)DR;
s323* s717;
if( s517 == 2 ) {
s717 = (s323*)( (s323*)s280[1] )->s349();}
else if( s280[2]->s1339().s366() == s1897 ) {
s717 = (s323*)( (s323*)s280[2] )->s349();}
else if( s280[2]->s1339().s366() == s1586 ) {
auto pr = (s400*)s280[2];
auto rp = pr->s1337();
typename s1557::iterator s1693, s1694;
s1693 = rp.first.s15<s1261*>()->s1268();
s1694 = rp.second.s15<s1261*>()->s1268();
s717 = new s323( ps->s306, vector<s277*>(), ps->ns, ps->s627() );
s717->s363.assign( s1693, s1694 );}
else {
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
s717 = new s323( ps->s306, v, ps->ns, ps->s627() );}
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s323::s402( s501** s280, size_t s517 ){
s323* v = ( (s323*)DR );
s336* seq = (s336*)s280[2];
Iterator* s1123 = seq->s321( NULL );
v->s363.clear();
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() )
break;
v->s363.push_back( p );}}
inline void s323::s1415( s501** s280, size_t s517 ){
s323* v = ( (s323*)DR );
size_t idx = (size_t)(int)*s280[2];
if( idx >= v->size() )
throw new s16( L"vector index is out of range",
(uint32_t)s16::s17::s24 );
s280[3]->s371( v->s363[idx] );}
inline void s323::s337( s501** s280, size_t s517 ){
s323* pv = (s323*)DR;
int idx = (int)*s280[2];
if( idx < 0 ) {
idx = (int)pv->s363.size() + idx;
if( idx < 0 )
throw new s16( L"negative index is out of bound" );}
if( idx >= (int)pv->s363.size() )
throw new s16( L"index is out of bound" );
*s280 = (s501*)(s277*)pv->s363[idx];}
inline void s323::s1480( s501** s280, size_t s517 ){
s323* pv = (s323*)DR;
const s501* s1726 = pv->s306->TR().s1106( pv->s334 );
( (s323*)DR )->s363.push_back( (s277*)s1726->s1710( s280[2] ) );}
inline void s323::s1923( s501** s280, size_t s517 ){
using s1246 = s323;
using s1026 = s1055;
s1246* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1246*)pr->s875();}
else
pv = ( (s1246*)s280[1] );
s905* s1941 = (s905*)s280[2];
s1267 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename s1557::iterator s1693, s1694;
s1693 = rp.first.s15<s1026*>()->s1268();
s1694 = rp.second.s15<s1026*>()->s1268();
while( s1693 != s1694 ) {
s1941->s620( vector<s503>( { *s1693 } ) );
s1941->s516( 0, 0 );
++s1693;}}
inline void s323::s2068( s501** s280, size_t s517 ){
s323* pv = (s323*)DR;
pv->s363.reserve( (int)*s280[2] );}
inline void s323::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
s323* pv = ( (s323*)DR );
int oldsize = (int)( (s323*)DR )->s363.size();
pv->s363.resize( size );
for( int i = oldsize; i < size; ++i ) {
pv->s363[i] = pv->s306->TR().s541( pv->s334, pv->s306, pv->s518 );
pv->s363[i]->s519( pv->ns, true );}}
inline void s323::s413( s501** s280, size_t s517 ){
size_t size = ( (s323*)DR )->s363.size();
s323* right = (s323*)s280[2];
if( right->s363.size() != size ) {
*( (s360*)*s280 )->s372() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s323*)DR )->s363[n] ) {
*( (s360*)*s280 )->s372() = 0;
return;}}
*( (s360*)*s280 )->s372() = 1;}
inline void s323::s852( s501** s280, size_t s517 ){
s323* pv = ( (s323*)DR );
const wstring& s880 = PARN( 2 )->to_wstring();
s1898 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s517 ) {
s503 par_ = s280[n];
s489 pc = par_->s513();
if( pc == s1172 ) {
s503 par;
s507 rf;
rf = par_.s15<s386*>();
par = par_;
if( par->s366() == s827->s366() ) {
if( rf->Id() == s1933 ) {
tbfr.mixedTypes = true;}
else if( rf->Id() == s1931 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1929 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1928 ) {
tbfr.s1875 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1930 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2021 ) {
tbfr.s2005 = true;}
else if( rf->Id() == s1927 ) {
if( s517 < n + 2 )
throw new s16( L"Vector::(load-table): the 'colNames:' value is missing" );
tbfr.s1912 = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Vector::(load-table): unknown parameters" );
++n;}
pv->s1060( s880, tbfr, pv->ns, pv->s627() );}
struct s919{
vector<s503>& s363;
s919( vector<s503>& s730 ) : s363( s730 ) {}
bool operator()( const s503 l, const s503 r ) const{
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
s501* s323::sort( bool s967, s908* cmp ){
s919 s918( s363 );
if( s967 ) {
if( cmp )
std::sort( s363.rbegin(), s363.rend(), *cmp );
else
std::sort( s363.rbegin(), s363.rend(), s918 );}
else {
if( cmp )
std::sort( s363.begin(), s363.end(), *cmp );
else
std::sort( s363.begin(), s363.end(), s918 );}
return this;}
wstring s323::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"[";
if( s644() == s7::s941 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += s363[n]->to_wstring() + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]";
return s717;}
void s323::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Vector : " << this << endl;
for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );}
size_t s323::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s363.size(); ++n )
s717 = s717 * ( ( s501* )&( *s363[n] ) )->s330() << 1;
return s717;}
bool s323::operator==( const s501* p ) const{
if( ( (s323*)p )->s363.size() != s363.size() )
return false;
for( size_t n = 0; n < s363.size(); ++n )
if( !( ( s277* )&( *s363[n] ) == (s277*)( (s323*)p )->s363[n] ) )
return false;
return true;}
bool s323::operator<( const s501* p ) const{
return false;}
Iterator* s323::s321( s400* rv ){
if( !rv )
return new s1055( this, begin( s363 ), end( s363 ) );
s1267 pr = rv->s1337( this );
return new s1055( this,
pr.first.s15<s1261*>()->s1268(), pr.second.s15<s1261*>()->s1268() );}
s792::s792( s268* s306, s278* s612, const wstring& s78,
const s269* ast_, const s1898& tbfr )
: s336( s306, s612, ast_ ){
if( s78.size() ) {
s1873 s1937;
s1937.s154 = true;
s1937.s1910 = tbfr.stringsQuoted;
s1937.s1922 = tbfr.s2005;
vector<s1::s9<s6::s144>> s156;
const s1032* s1158 = NULL;
if( ast_ )
s1158 = ast_->Nqj()->s1105();
if( s78[0] == L'[' ) {
size_t pos = 0;
s6::s182( s1158, s78, pos, s156, s1937 );}
else
s6::s182( s1158, s78, s156, s1937 );
s1034 s230;
for( size_t n = 0; n < s156.size(); ++n ) {
s230 = new s269( L"", *s156[n] );
if( ( !tbfr.stringsQuoted && s156[n]->s167() == s137 ) ||
s156[n]->s167() == s142 || s230->s303() == s233 ) {
s230->s1511( s1288 );
s230->s2051( s229::s230 );
s230->s1947( L"\"" + 
s230->s297() + 
L"\"" );}
else if( tbfr.promInts && s156[n]->s167() == s143 )
s230->s1511( s1283 );
if( s230->s297().empty() ) {
if( s1937.s1922 )
s230->s1947( s374::proto->s368() + L"()" );
else
throw new s16( L"empty element in an UntypedVector. To allow"
L" empty elements, use the ':emptyEls' marker." );}
s363.push_back( s277::s524( *s230, s306, s612, s612->s304() ) );}}
s512 = s792::proto.s13() ? 0 : s1896;}
s792::s792( s268* s306, const vector<s277*>& l,
const s269* ast_ )
: s336( s306, NULL, ast_ ){
for( auto s1169 : l )
s363.push_back( s1169 );
s512 = s1896;}
s792::s792( const s792& right )
: s336( right ){
s363 = right.s363;
s512 = right.s512;}
s792::~s792(){
s363.clear();
s518.clear();}
void s792::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<s1::s9<s6::s144>>& s96, const s269* ast_, const s1873& s1937 ){
assert( !s78.empty() );
if( s78[0] == L'[' ) {
size_t pos = 0;
const s1032* s1158 = NULL;
if( ast_ && ast_->Nqj() )
s1158 = ast_->Nqj()->s1105();
s6::s182( s1158, s78, pos, s96, s1937 );}
else
s1300( s306, s78, s1427, s673 );}
s501* s792::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring sv;
wstring s361 = s368();
if( s.find( L"UVector[" ) == 0 )
sv = s.substr( 7 );
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv[0] != L'(' )
throw new s16( L"wrong vector constructor syntax" );
sv = s4::s53( sv.substr( 1, sv.size() - 2 ), L" " );}
else
return 0;
return new s792( s306, s612, sv, &s736 );}
void s792::s519( const s278* s960, bool ){
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s960, true );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1203 = s277::s1120( s306, s363[n], (s278*)s960, NULL, s960->s304() );
s363[n] = s1203;}
s512 = s1896;
s1855( s7::s940 );
s518 = s960->s898();}
void s792::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s792::s402, s1286,
{ s1238( { s1284, s7::s1564, s7::s1570 } ) }, 2, (size_t)-1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s792::s337, 0,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"fst", new s351( L"fst", &s792::s1099, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"snd", new s351( L"snd", &s792::s1184, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"append", new s351( L"append", &s792::s1480, s1286,
{ s1238( { s7::s1564, s7::s1570 } ) }, 1, (size_t)-1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s792::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"resize", new s351( L"resize", &s792::s340, s1286,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s792::s341, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s792::s413, s1284,
{ s1238( { s7::s1565 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"for-each", new s351( L"for-each", &s792::s1923, s1286,
{ s1238( { s7::s1569 } ) }, 1, 1 ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"fst" ).first->second->s1412( true );
s362.equal_range( L"snd" ).first->second->s1412( true );}
s501* s792::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s792( s306, s612, L"", ast_, s1916 );}
s501* s792::s370( s278* s612, const std::vector<s1170>& vt ) const{
assert( 0 );
return 0;}
s1170 s792::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"fst" )
s717 = s363[0]->s366();
else if( s1727 == L"snd" )
s717 = s363[1]->s366();
else if( s1727 == L"get" ) {
if( l[0]->s366() != s1284 )
throw new s16( L"individual elements of an UntypedVector can be accessed "
"only by a literal numerical index" );
int n = (int)*l[0];
s717 = s363[n]->s366();}
return s717;}
inline bool
s792::s521( const s501* s522 ) const{
return ( ( (s323*)s522 )->s366() == s366() );}
s1170 s792::s327() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s277* s792::s349() const{
return new s792( *this );}
void s792::s371( s277* p ) const{
p = new s792( *this );}
void s792::assign( const vector<s503>& p ){
s363.assign( begin( p ), end( p ) );}
Iterator* s792::s1328() {
if( s363.size() )
return new s1051( this, s363.begin(), s363.begin() + 1 ); 
return new s1051( this, s363.end(), s363.end() ); }
Iterator* s792::s1332(){
return new s1051( this, s363.end(), s363.end() ); }
s1267 s792::s1337(){
return std::make_pair( s1328(), s1332() );}
#undef s733
#define s733 ((s792*)(s502*)*s280)
inline void s792::s402( s501** s280, size_t s517 ){
s280[3]->s371( ( (s792*)DR )->s363[(int)*s280[2]] );}
inline void s792::s337( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s792*)DR )->s363[(int)*s280[2]];}
inline void s792::s1099( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s792*)DR )->s363[0];}
inline void s792::s1184( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s792*)DR )->s363[1];}
inline void s792::s1480( s501** s280, size_t s517 ){
/*if( ( (s792*)DR )->s327() != s280[2]->s514() )
throw new s16( L"unmatched element type" );*/
( (s792*)DR )->s363.push_back( s280[2]->s349() );}
inline void s792::s339( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s792*)DR )->s363.size();}
inline void s792::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
( (s792*)DR )->s363.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s792*)DR )->s363[i] = ( (s792*)DR )->s306->s221(
( (s792*)DR )->s324, ( (s792*)DR )->s518 ).s15<s502*>();*/
}
inline void s792::s341( s501** s280, size_t s517 ){
( (s792*)DR )->s363.clear();}
inline void s792::s1923( s501** s280, size_t s517 ){
using s1246 = s792;
using s1026 = s1051;
s1246* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1246*)pr->s875();}
else
pv = ( (s1246*)s280[1] );
s905* s1941 = (s905*)s280[2];
s1267 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename s1557::iterator s1693, s1694;
s1693 = rp.first.s15<s1026*>()->s1268();
s1694 = rp.second.s15<s1026*>()->s1268();
while( s1693 != s1694 ) {
s1941->s620( vector<s503>( { *s1693 } ) );
s1941->s516( 0, 0 );
++s1693;}}
inline void s792::s413( s501** s280, size_t s517 ){
size_t size = ( (s792*)DR )->s363.size();
s792* right = (s792*)s280[2];
if( right->s363.size() != size ) {
*( (s360*)*s280 )->s372() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s792*)DR )->s363[n] ) {
*( (s360*)*s280 )->s372() = 0;
return;}}
*( (s360*)*s280 )->s372() = 1;}
inline void s792::s342( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s792*)DR )->s363.size();}
wstring s792::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"UT[";
if( s644() == s7::s941 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += s363[n]->to_wstring() + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]";
return s717;}
void s792::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );}
size_t s792::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s363.size(); ++n )
s717 = s717 * ( ( s501* )&( *s363[n] ) )->s330() << 1;
return s717;}
bool s792::operator==( const s501* p ) const{
if( ( (s792*)p )->s363.size() != s363.size() )
return false;
for( size_t n = 0; n < s363.size(); ++n ) {
const s501* l = s363[n].s15<s501*>();
const s501* r = ( (const s792*)p )->s363[n].s15<s501*>();
if( !( *l == r ) )
return false;}
return true;}
bool s792::operator<( const s501* p ) const{
return false;}
Iterator* s792::s321( s400* rv ){
return NULL;}
/*s504 s792::s322()
{
if( s325 == s363.end() ) {
return NULL;}
s504 s717 = ( *s325 ).s15<s501*>();
s325++;
return s717;
}*/
s1048::s1048( s268* s306, s278* s612, const std::wstring& s78,
const s269* ast_, const s1873& s1937 )
: s792( s306, ast_ ){
s1343 = s1284;
if( s78.size() ) {
s1299( s78, /*s1427, s673,*/ s612, s1937 );
}
if( !s512 )
s512 = s1048::proto.s13() ? 0 : s1048::proto->s366();}
s1048::s1048( s268* s306, const std::vector<s277*>& l, const s269* ast_ )
: s792( s306, l, ast_ ){
s512 = s1895;}
s1048::s1048( const s1048& right, const s269* ast_ )
: s792( right ){
s363.assign( begin( right.s363 ), end( right.s363 ) );
s512 = right.s512;
s324 = right.s324;
s1343 = right.s1343;
s334 = right.s334;}
s501* s1048::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s361 = s368();
if( s.find( L"[[" ) == 0 )
sv = s;// s.substr( 1, s.size() - 2 );
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
throw new s16( L"wrong tuple constructor syntax: missing element types" );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );}
else
return 0;
s1048* s717 = new s1048( s306, s612, sv, &s736 );
return s717;}
void s1048::s519( const s278* s960, bool ){
wstring s78 = L"";
TDException s1059( s7::s1009, s1018, s627() );
if( s363.size() == 2 && s363[0].s13() )
s78 = s363[1]->to_wstring();
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
s1034 ast_ = new s269( s78.substr( 9, s78.size() - snum.size() - 10 ), s627()->Nqj() );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( *(s269*)ast_, (s278*)s960, s960->s898() ) );}
else {
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s960 );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1203 = s277::s1120( s306, s363[n], (s278*)s960, NULL, s960->s304() );
s363[n] = s1203;}}
s1855( s7::s940 );
s518 = s960->s304();}
void s1048::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s1048::s402, s1286,
{ s1238( { s7::s1565 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s1048::s1416, s1286,
{ s1238( { s1284, s7::s1564, s7::s1570 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s1048::s337, 0,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"fst", new s351( L"fst", &s1048::s1099, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"snd", new s351( L"snd", &s1048::s1184, 0,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"append", new s351( L"append", &s1048::s1480, s1286,
{ s1238( { s7::s1564, s7::s1570 } ) }, 1, (size_t)-1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1048::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"resize", new s351( L"resize", &s1048::s340, s1286,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s1048::s341, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s1048::s413, s1284,
{ s1238( { s7::s1565 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"for-each", new s351( L"for-each", &s792::s1923, s1286,
{ s1238( { s7::s1569 } ) }, 1, 1 ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"fst" ).first->second->s1412( true );
s362.equal_range( L"snd" ).first->second->s1412( true );}
s501* s1048::s370( s278* s612, const std::vector<s1170>& vt ) const{
s1048* s717 = new s1048( s306, NULL, L"" );
s867 s646( vt );
s717->s512 = s717->s324 = s717->s334 = s306->TR().s1110( s646 );
return s717;}
s501* s1048::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1048* s717 = new s1048( s306, l, ast_ );
return s717;}
void s1048::s1299( const wstring& s78,	s278* s612, const s1873& s1937 ){
assert( !s78.empty() );
wstring s1427, s673, s1417;
if( s78[0] == L'[' ) {
s1417 = s78.substr( 1, s78.size() - 2 );}
else {
s1300( s306, s78, s1427, s673 );
if( !s673.empty() && s673[0] == L'[' )
s1417 = s673.substr( 1, s673.size() - 2 );
if( !s1427.empty() )
s1297( s1427 );}
if( !s1417.empty() ) {
load( s1417, s612, s1937 );}
else if( !s673.empty() ) {
if( s673.find_first_not_of( s4::digits ) == string::npos ) {
s363.push_back( 0 );
s363.push_back( new s374( s306, s673, ns ) );}}}
void s1048::s1297( const std::wstring& s1427 ){
s867::Cont vt;
size_t pos = 0;
s306->TR().s1163( s1427, pos, vt );
s867::Cont s1437( begin( vt ), end( vt ) );
if( s1437.size() > 2 )
s334 = s306->TR().s1153( s1437 );
else
s334 = s1437[0];
s512 = s324 = s334;}
s1170 s1048::s1338( const std::wstring& s1427, s867::Cont& s612 ){
s1170 s717;
s867::Cont vt;
size_t pos = 0;
s306->TR().s1163( s1427, pos, vt );
s717 = s306->TR().s1110( s867( vt ), false );
if( s717 ) {
s612.assign( vt.begin(), vt.end() );
return s717;}
s717 = s306->TR().s1153( vt );
s612.assign( vt.begin(), vt.end() );
return s717;}
void s1048::load( const wstring& s78, s278* s612, const s1873& s1937 ){
TDException s1059( s7::s1244, s1018, s627() );
size_t pos = 0;
const s1032* s1158 = NULL;
if( s627() && s627()->Nqj() )
s1158 = s627()->Nqj()->s1105();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1158, s78, pos, s96, s1937 );
if( s96.size() ) {
s867::Cont s1433;
if( s512 ) {
const s867& vt = s306->TR().s1112( s512 );
s1433.assign( vt.s875().begin(), vt.s875().end() );
if( s96.size() != ( s1433.size() - 2 ) / 2 )
throw s1059.s1097( L"wrong number of elements passed for inititalizing tuple" );}
else
s1433.push_back( s1895 );
for( size_t n = 0; n < s96.size(); ++n ) {
s1034 s230 = new s269( L"", *s96[n] );
s277* p = NULL;
if( s230->s297().empty() ) {
if( s1937.s1922 && s512 ) {
s230->s1947( s306->TR().s854( s1433[( n + 1 ) * 2] ) + L"()" );
p = s277::s524( *s230, s306, s612, s612->s304() );
p->s1855( s7::s1925 );}}
else {
if( s512 )
s230->s1511( s1433[( n + 1 ) * 2] );
p = s277::s524( *s230, s306, s612, s612->s304() );}
s363.push_back( p );
if( s512 ) {
(void)0;}
else {
s1433.push_back( p->s366() );
s1433.push_back( 0 );}}
s1433.insert( s1433.begin() + 1, (s1170)( s1433.size() - 1 ) / 2 );
if( !s334 ) {
s512 = s306->TR().s1153( s1433 );
s334 = s324 = s512;}}
s1413();}
s1170 s1048::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"fst" )
s717 = s306->TR().s1112( s512 ).s366( ( 0 + 1 ) * 2 );
else if( s1727 == L"snd" )
s717 = s306->TR().s1112( s512 ).s366( ( 1 + 1 ) * 2 );
else if( s1727 == L"get" ) {
int n = (int)*l[0];
s717 = s306->TR().s1112( s512 ).s366( ( n + 1 ) * 2 );}
return s717;}
#undef s733
#define s733 ((s1048*)(s502*)*s280)
inline void s1048::s402( s501** s280, size_t s517 ){
s1048* s879 = ( (s1048*)DR );
if( s879->s366() != s280[2]->s366() )
throw new s16( L"mismatched types in assignment expression" );
s280[2]->s371( s879 );}
inline void s1048::s1416( s501** s280, size_t s517 ){
s1048* s879 = ( (s1048*)DR );
size_t idx = (int)*s280[2];
s277* el = s879->s363[idx];
if( ! s280[3]->s1715( el->s366()) )
throw new s16( L"mismatched types in assignment expression" );
s280[3]->s371( ( (s1048*)DR )->s363[(int)*s280[2]] );}
inline void s1048::s337( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1048*)DR )->s363[(int)*s280[2]];}
inline void s1048::s1099( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1048*)DR )->s363[0];}
inline void s1048::s1184( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1048*)DR )->s363[1];}
inline void s1048::s1480( s501** s280, size_t s517 ){
s1048* s879 = ( (s1048*)DR );
const s1048* pro = (s1048*)s879->s306->TR().s1106( DR->s366() );
size_t n = s879->s363.size();
if( n >= pro->s363.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s363[n]->s521( s280[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s792*)DR )->s327() != s280[2]->s514() )
*/
s879->s363.push_back( s280[2]->s349() );}
inline void s1048::s339( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s1048*)DR )->s363.size();}
inline void s1048::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
( (s1048*)DR )->s363.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s792*)DR )->s363[i] = ( (s792*)DR )->s306->s221(
( (s792*)DR )->s324, ( (s792*)DR )->s518 ).s15<s502*>();*/
}
inline void s1048::s341( s501** s280, size_t s517 ){
( (s1048*)DR )->s363.clear();}
inline void s1048::s413( s501** s280, size_t s517 ){
size_t size = ( (s1048*)DR )->s363.size();
s1048* right = (s1048*)s280[2];
if( right->s363.size() != size ) {
*( (s360*)*s280 )->s372() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s1048*)DR )->s363[n] ) {
*( (s360*)*s280 )->s372() = 0;
return;}}
*( (s360*)*s280 )->s372() = 1;}
inline void s1048::s342( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s1048*)DR )->s363.size();}
s277* s1048::s349() const{
return new s1048( *this );}
void s1048::s371( s277* p ) const{
*p = *this;}
wstring s1048::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"[[";
if( s644() == s7::s941 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += s363[n]->to_wstring() + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]]";
return s717;}
s1448::s1448( s268* s306, s278* s612, const wstring& s78, const s269* ast_,
const s1873& s1937 )
: s1572( s306, s612, ast_ ){
s1299( s78, s612, s1937 );
if( !s512 )
s512 = ( s1448::proto.s13() ? 0 : s1275 );}
s1448::s1448( const s1448& right, const s269* ast_ )
: s1572( right.s306, NULL, ast_ ){
s363 = right.s363;
s1343 = right.s1343;
s334 = right.s334;
s324 = right.s324;
s512 = right.s512;
wh = right.wh;}
s1448::s1448( s268* s306, const std::vector<s277*>& l, const s269* ast_ )
: s1572( s306, NULL, ast_ ){
s1299( L"", NULL, s1914 );
if( l.size() ) {
s324 = l[0]->s366();
for( size_t n = 0; n < l.size(); ++n )
s363.push_back( *( (s1452*)l[n] )->s372() );}
if( !s512 )
s512 = ( s1448::proto.s13() ? 0 : s1275 );}
s1448::~s1448(){
s363.clear();}
void s1448::s1299( const wstring& s78, s501* s612, const s1873& s1937 ){
s1343 = s1284;
s334 = s1474;
s867::Cont v = { s1895, 2, s1284, 0, s334, 0 };
s324 = s306->TR().s1153( v );
s512 = s1275;
if( s78.empty() )
return;
wstring s1427, s673, s1417;
if( s78[0] == L'[' ) {
s1417 = s78;}
else {
s1300( s306, s78, s1427, s673 );
if( !s673.empty() && s673[0] == L'[' )
s1417 = s673;
if( s1427 != s368() )
throw new s16( L"wrong syntax of ByteArray declaration" );}
if( !s1417.empty() ) {
load( s1417, s612, s1937 );}
else if( !s673.empty() ) {
if( s673[0] == L']' && s673.find_first_not_of(
s4::digits + s4::s49, 1 ) == string::npos ) {
wstring snum = s673.substr( s673.rfind( L" " ) );
size_t s166 = std::stoi( snum );
s363.resize( s166 );}}}
void s1448::load( const wstring& s78, s501* s612, const s1873& s1937 ){
TDException s1059( s7::s1456, s1018, s627() );
size_t pos = 0;
const s1032* s1158 = NULL;
if( s627() && s627()->Nqj() )
s1158 = s627()->Nqj()->s1105();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1158, s78, pos, s96, s1937 );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
size_t s166 = s96[n]->s57();
s363.push_back( (tdbyte_t)s166 );}}}
s501* s1448::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
TDException s1059( s7::s1454, s1018, &s736,
L"wrong ByteArray constructor syntax" );
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s361 = s368();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s1059.s1097( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1448* s717 = new s1448( s306, s612, sv, &s736 );
return s717;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1487( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1448::s519( const s278* s960, bool ){
s1855( s7::s940 );
if( s960 )
s518 = s960->s898();}
void s1448::s364(){
s1572<s1545, tdbyte_t, s1448, s1452>::s364();
s362 = s1572<s1545, tdbyte_t, s1448, s1452>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1448::s1384, s1275,
{ s1238(), s1238( { s7::s1564, s7::s1570 } ) }, 0, 1 ) ) );
s362.emplace( make_pair( L"set", new s351( L"set", &s1448::s402, s1286,
{ s1238( { s1686::s1681 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"set-el", new s351( L"set-el", &s1448::s1415, s1286,
{ s1238( { s1284, s1284 } ) }, 2, 2 ) ) );
s362.emplace( make_pair( L"get", new s351( L"get", &s1448::s337, s1474,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"append", new s351( L"append", &s1448::s1480, s1286,
{ s1238( { s7::s1568 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"resize", new s351( L"resize", &s1448::s340, s1286,
{ s1238( { s1284 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"eq", new s351( L"eq", &s1448::s413, s1274,
{ s1238( { s7::s1565 } ) }, 1, 1 ) ) );
s306->TR().s1301( s512, s7::s1583, s1686::s1682 );
s306->TR().s1301( s512, s7::s1581, s1686::s1680 );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
s501* s1448::s370( s278* s612, const vector<s277*>& l, const s269* ast_ ) const{
return new s1448( s306, s612, L"", ast_ );}
s501* s1448::s370( s278* s612, const std::vector<s1170>& vt ) const{
return new s1448( s306, s612, L"" );}
inline bool
s1448::s521( const s501* s522 ) const{
return ( ( (s1448*)s522 )->s366() == s366() );}
s277* s1448::s349() const{
return new s1448( *this );}
void s1448::s371( s277* p ) const{
p = new s1448( *this );}
Iterator* s1448::s1304( const s501* idx ){
s1545::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i < 0 ) {
i = (int)s363.size() + i;
if( i < 0 )
i = 0;}
it = s363.begin() + i;}
return new s1449( this, it, it == s363.end() ? it : it + 1 );}
Iterator* s1448::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( *it == *( (s1452*)_val )->s372() )
return new s1449( this, it, it + 1 );
return new s1449( this, end( s363 ), end( s363 ) );}
s501* s1448::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1449*)it )->s1268() );
return new s360( s306, (int)n );}
Iterator* s1448::s1328() {
if( s363.size() )
return new s1449( this, s363.begin(), s363.begin() + 1 ); 
return new s1449( this, s363.end(), s363.end() ); }
Iterator* s1448::s1332() {
return new s1449( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s1448*)(s502*)*s280)
inline void s1448::s1384( s501** s280, size_t s517 ){
s1448* ps = (s1448*)DR;
s1448* s717 = NULL;
if( s517 == 2 ) {
s717 = (s1448*)( (s1448*)s280[1] )->s349();}
else if( s280[2]->s1339().s366() == s1897 ) {
s323* pv = (s323*)s280[2];
s717 = new s1448( ps->s306, ps->ns, L"", ps->s627() );
for( size_t n = 0; n < pv->s328().size(); ++n ) {
s717->s363.push_back( (int)*pv->s328()[n] );}}
else if( s280[2]->s366() == s1586 ) {
auto pr = (s400*)s280[2];
auto rp = pr->s1337();
typename s1557::iterator s1693, s1694;
s1693 = rp.first.s15<s1261*>()->s1268();
s1694 = rp.second.s15<s1261*>()->s1268();
s717 = new s1448( ps->s306, ps->ns, L"", ps->s627() );
s717->s363.assign( s1693, s1694 );}
else
assert( 0 );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s1448::s402( s501** s280, size_t s517 ){
s1448* v = ( (s1448*)DR );
s336* seq = (s336*)s280[2];
s400 range( 0, -1 );
Iterator* s1123 = seq->s321( &range );
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() )
break;
v->s363.push_back( *p.s15<s1452*>()->s372() );}}
inline void s1448::s1415( s501** s280, size_t s517 ){
assert( s280[3]->s366() == s1284 );
assert( s280[2]->s366() == s1284 );
s1448* v = ( (s1448*)DR );
size_t idx = (size_t)(int)*s280[2];
v->s363[idx] = *( (s1452*)s280[3] )->s372();}
inline void s1448::s337( s501** s280, size_t s517 ){
s1452* s717 = new s1452( ( (s1448*)DR )->s306,
( (s1448*)DR )->s363[(int)*s280[2]] );
*s280 = (s501*)(s277*)s717;}
inline void s1448::s1480( s501** s280, size_t s517 ){
assert( s280[2]->s366() == s1474 );
( (s1448*)DR )->s363.push_back( *( (s1452*)s280[2] )->s372() );}
inline void s1448::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
( (s1448*)DR )->s363.resize( size );}
inline void s1448::s413( s501** s280, size_t s517 ){
size_t size = ( (s1448*)DR )->s363.size();
s1448* right = (s1448*)s280[2];
if( right->s363.size() != size ) {
*( (s375*)*s280 )->s372() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s1448*)DR )->s363[n] ) {
*( (s375*)*s280 )->s372() = false;
return;}}
*( (s375*)*s280 )->s372() = true;}
wstring s1448::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"[";
if( s644() == s7::s941 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += std::to_wstring( s363[n] ) + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]";
return s717;}
void s1448::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1448::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s363.size(); ++n )
s717 = ( s717 * s363[n] ) << 1;
return s717;}
bool s1448::operator==( const s501* p ) const{
if( ( (s1448*)p )->s363.size() != s363.size() )
return false;
for( size_t n = 0; n < s363.size(); ++n )
if( !( s363[n] == ( (s1448*)p )->s363[n] ) )
return false;
return true;}
bool s1448::operator<( const s501* p ) const{
return false;}
Iterator* s1448::s321( s400* rv ){
s1267 pr = rv->s1337( this );
return new s1449( this,
pr.first.s15<s1261*>()->s1268(), pr.second.s15<s1261*>()->s1268() );}
s332::s332( s268* s306, s1170 s1344, s1170 s1430, 
s278* s612, const s269* ast_ )
: s1539( s306, s612, ast_ ){
assert( s1344 && s1430 );
this->s1343 = s1344;
s334 = s1430;
s867 s1324( s867::Cont( { s1895, 2, s1343, 0, s334, 0 } ) );
s324 = s306->TR().s1110( s1324 );
s867 s1828( s867::Cont( { s332::proto->s366(), 1, s324, 0 } ) );
s512 = s306->TR().s1110( s1828 );}
s332::s332( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1539( s306, s612, ast_ ){
TDException s1059( s7::s1538, s1018, ast_ );
if( s78.size() ) {
wstring s673, s1427;
vector<pair<wstring, s1::s9<s6::s144>>> s96;
s1299( s78, s1427, s673, s96, ast_ );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
s1034 s1069 = new s269( s96[n].first, s627()->Nqj() );
s501* s1165 = (s501*)s277::s524( *s1069, s306, s612, s612->s304() );
basic_stringstream<wchar_t> s1194;
s96[n].second->s158( &s1194 );
s1034 s230 = new s269( s1194.str(), s627()->Nqj() );
s501* s1174 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
if( !s1343 ) {
s1343 = s1165->s366();
s334 = s1174->s366();}
if( s1343 != s1165->s366() || s334 != s1174->s366() )
throw s1059.s1097( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1165, s1174 ) );}}
else if( s673.size() ) {
s867::Cont vt, s1127, s1219;
size_t pos = 0;
s306->TR().s1163( s78, pos, vt );
size_t idx = 2;
s509::s1107( vt, idx, s1127 );
if( s1127.size() > 2 )
s1343 = s306->TR().s1110( s867( s1127 ), false );
else
s1343 = s306->TR().s1110( 
s867( s867::Cont( { s1127[0] } ) ) );
if( !s1343 ) {
if( s1127.size() > 2 )
s1343 = s306->TR().s1153( s1127 );
else
s1343 = s1127[0];}
s509::s1107( vt, idx, s1219 );
if( s1219.size() > 2 )
s334 = s306->TR().s1110( s867( s1219 ), false );
else
s334 = s306->TR().s1110(
s867( s867::Cont( { s1219[0] } ) ) );
if( !s334 ) {
if( s1219.size() > 2 )
s334 = s306->TR().s1153( s1219 );
else
s334 = s1219[0];}}
else if( false && s78[0] == L'(' ) {
wstring sv = s4::s53( s78.substr( 1, s78.size() - 2 ), L" " );
wsmatch s1183;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1183, rg ) ) {
wstring s1207 = s1183[1].str();
wstring s1208 = s1183[2].str();
sv = L"Index(" + s1207 + L" " + s1208 + L")";
s518 = sv;}}
else
assert( 0 );// s518 = s78;
}
if( s332::proto.s13() )
s512 = 0;
else {
if( s1343 ) {
s324 = s306->TR().s1153( s867::Cont( { s1895, 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1153( s867::Cont( { s332::proto->s366(), 1, s324, 0 } ) );}
else {
s324 = s512 = 0;}}}
s332::s332( const s332& right, const s269* ast_ )
: s1539( right.s306, NULL, ast_ ){
s363 = right.s363;
s512 = right.s512;
s1343 = right.s1343;
s334 = right.s334;
s324 = right.s324;}
s332::s332( s268* s306, const std::vector<s277*>& l,
s278* s612, const s269* ast_, s1170 s744, s1170 s1323,
s1170 s1814, s1170 s1430 )
: s1539( s306, s612, ast_ ){
s1343 = s1814;
s334 = s1430;
s324 = s1323;
s512 = s744;
if( l.size() && ( l.front()->s366() == s366() ||
l.front()->s366() == s332::proto->s366() ) ) {
s363 = ( (s332*)l.front() )->s363;}}
void s332::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<pair<wstring, s145>> s96, const s269* ast_ ){
assert( !s78.empty() );
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1032 s1159( L"", true, s1914 );
s1159.s174( s78, pos, ob );
ob->s163( s96 );}
else
s1300( s306, s78, s1427, s673 );}
void s332::s1297( const std::wstring& s1427, s1170& pt, 
s1170& et, s1170& kt, s1170& vt ){
s867::Cont s612;
pt = s1338( s1427, s612, et, kt, vt );}
s501* s332::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring si;
wstring sv, s1427, s673;
wstring s361 = s368();
s1170 pt = 0, et = 0, kt = 0, vt = 0;
if( s736.s274( L"ownerType" ) == L"CallSite" ) {
wstring s1489 = s736.s274( L"ownerName" );
if( s1489.find( L"new<Index<" ) == 0 ) {
wstring stype = s1489.substr( 4, s1489.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s53( s, L"{}" );
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );
s1300( s306, s, s1427, s673 );
if( !s673.empty() && ( s673[0] == L'{' || s673[0] == L'}' ) )
sv = s673;
if( !s1427.empty() )
s1297( s1427, pt, et, kt, vt );}
else
return 0;
s332* s717 = new s332( s306, vector<s277*>({ }), s612, &s736,
pt, et, kt, vt );
s717->load( sv, s612, L"," );
return s717;}
s1170 s332::s1338( const std::wstring& s1427, s867::Cont& s612,
s1170& et, s1170& kt, s1170& vt ){
s1170 s717;
s867::Cont s1433;
size_t pos = 0;
s306->TR().s1163( s1427, pos, s1433 );
s717 = s306->TR().s1110( s867( s1433 ), false );
if( s717 ) {
s612 = { s332::proto->s366(), 1, s1433[2], 0 };
et = s1433[2];
const s867& s1089 = s306->TR().s1112( et );
kt = s1089.s366( 2 );
vt = s1089.s366( 4 );
return s717;}
s867::Cont s1642, s1689;
size_t idx = 2;
s509::s1107( s1433, idx, s1642 );
s867 s1127( s1642[0] );
kt = s306->TR().s1110( s1127 );
s509::s1107( s1433, idx, s1689 );
if( s1689.size() > 2 )
vt = s306->TR().s1153( s1689 );
else
vt = s1689[0];
et = s306->TR().s1153( 
s867::Cont( { s1895, 2, kt, 0, vt, 0 } ) );
s612 = { s332::proto->s366(), 1, et, 0 };
s717 = s306->TR().s1153( s612 );
return s717;}
void s332::load( const std::wstring& s78, s278* s612, const std::wstring& s73 ){
TDException s1059( s7::s1773, s1018, s627() );
vector<pair<wstring, s1::s9<s6::s144>>> s96;
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1032 s1159( L"", true, s1914 );
s1159.s174( s78, pos, ob );
ob->s163( s96 );}
if( s96.empty() )
return;
wstring ownerName = s627()->s274( L"ownerName" );
bool s1492 = false;
if( ( s627()->s274( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1492 = true;
for( size_t n = 0; n < s96.size(); ++n ) {
s1034 s1069 = new s269( s96[n].first, s627()->Nqj() );
s501* s1165 = (s501*)s277::s524( *s1069, s306, s612, s612->s304() );
s1165->s1413();
basic_stringstream<wchar_t> s1194;
s96[n].second->s158( &s1194 );
s1034 s230 = new s269( s1194.str(), s627()->Nqj() );
s501* s1174 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
s1174->s1413();
if( !s1343 ) {
s1343 = s1165->s366();
s334 = s1174->s366();}
if( s1343 != s1165->s366() || s334 != s1174->s366() )
throw s1059.s1097( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1165, s1174 ) );}
if( !s1492 ) {
if( !s324 && s363.begin()->second->s366() ) {
s324 = s306->TR().s1153( { s1895, 2, s363.begin()->first->s366(), 0,
s363.begin()->second->s366(), 0 } );
s867::Cont v1 = { s332::proto->s366(), 1, s324, 0 };
s512 = s306->TR().s1153( v1 );}
else if( s334 != s363.begin()->second->s366() )
throw s1059.s1097( L"index' element type doesn't match the index type" );}}
void s332::s519( const s278* s960, bool ){
TDException s1059( s7::s1009, s1018, s627(), L"wrong Index definition" );
const wstring& s78 = s518;
if( s78.find( L"Index<" ) == 0 ) {
assert( 0 );
s867::Cont vt, s1127, s1219;
size_t pos = 0;
s306->TR().s1163( s78, pos, vt );
size_t idx = 2;
s509::s1107( vt, idx, s1127 );
s867 s1126( s1127[0] );
s1343 = s306->TR().s1110( s1126 );
s509::s1107( vt, idx, s1219 );
s867 s1216( s1219[0] );
s334 = s306->TR().s1110( s1216 );}
else if( s78[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s144>> s156;
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1032 s1159( L"", true, s1914 );
s1159.s174( s78, pos, ob );
vector<pair<wstring, s145>> s147;
ob->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1034 s1069 = new s269( s147[n].first, s627()->Nqj() );
s501* s1165 = (s501*)s277::s524( *s1069, s306, (s278*)s960, s960->s304() );
basic_stringstream<wchar_t> s1194;
s147[n].second->s158( &s1194 );
s1034 s230 = new s269( s1194.str(), s627()->Nqj() );
s501* s1174 = (s501*)s277::s524( *s230, s306, (s278*)s960, s960->s304() );
if( !s1343 ) {
s1343 = s1165->s366();
s334 = s1174->s366();}
if( s1343 != s1165->s366() || s334 != s1174->s366() )
throw s1059.s1097( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1165, s1174 ) );}}
s1413();}
void s332::s364(){
s1539<s1558, s504, s504, s332>::s364();
s362 = s1539<s1558, s504, s504, s332>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s332::s1384, s1286,
{ s1238(), s1238( { s7::s1564, s7::s1570 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s362.insert( make_pair( L"insert", new s351( L"insert", &s332::s343, s1286,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s332::s828, 0,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s332::s337, 0,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get-val", new s351( L"get-val", &s332::s1637, 0,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s332::s402, s1286,
{ s1238( { s7::s1565 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s332::s1768, s1274,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s332::s344, s1286,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s332::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.equal_range( L"find" ).first->second->s1412( true );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"get-val" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1581, s1686::s1680 );
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );}
s501* s332::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1::s9<s332> s717 = new s332( s306, s612, L"", ast_ );
s717->s1343 = s1343;
s717->s334 = s334;
return s717;}
s501* s332::s370( s278* s612, const std::vector<s1170>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s867::Cont s1089;
s509::s1107( vt, idx, s1089 );
s867 s1088( s1089[0] );
s1170 s1323 = s306->TR().s1110( s1088 );
const s867& s1215 = s306->TR().s1112( s1323 );
s867::Cont s1127, s1219;
idx = 2;
s509::s1107( s1215.s875(), idx, s1127 );
s867 s1126( s1127[0] );
s1170 s1344 = s306->TR().s1110( s1126 );
s509::s1107( s1215.s875(), idx, s1219 );
s867 s1216( s1219[0] );
s1170 s1430 = s306->TR().s1110( s1216 );
s332* s717 = new s332( s306, s1344, s1430, s612, NULL );
return s717;}
s1170 s332::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get" ) {
s717 = s324;}
else if( s1727 == L"get-val" ) {
s717 = s324;}
else
s717 = s1539::s1331( s1727, l );
return s717;}
inline bool
s332::s521( const s501* s522 ) const{
return 0; /* ( ( (s323*)s522 )->s324 == s324 );*/
}
s277* s332::s349() const{
return new s332( *this );}
void s332::s371( s277* p ) const{
p = new s332( *this );}
size_t s332::s330() const{
return (size_t)this;}
bool s332::operator==( const s501* p ) const{
return ( this == p );}
bool s332::operator<( const s501* p ) const{
return false;}
Iterator* s332::s1328() {
auto it = begin( s363 );
return new s1025( this, s363.begin(), ++it ); }
Iterator* s332::s1332() {
return new s1025( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s332*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
inline void s332::s1384( s501** s280, size_t s517 ){
s332* ps = (s332*)DR;
s332* s717 = NULL;
if( s517 == 2 ) {
s717 = (s332*)( (s332*)s280[1] )->s349();}
else if( s280[2]->s1339().s366() == s1893 ) {
s717 = (s332*)( (s332*)s280[2] )->s349();}
else {
assert( 0 );
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 ) { return v.push_back( (s277*)s363 ); } );}
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s332::s343( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s332* dr = (s332*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s363.insert( make_pair( s155, s363 ) );}
inline void s332::s828( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s332::s337( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
throw new s16( L"key doesn't exist" );
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s332::s1637( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() ) {
*s280 = new s1048( p->s306, vector<s277*>(
{ (s501*)PARN( 2 ), (s501*)PARN( 3 ) } ) );}
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>()->s349(), it->second.s15<s502*>()->s349() } ) );}}
inline void s332::s402( s501** s280, size_t s517 ){
s332* l = (s332*)DR;
s332* right = (s332*)PARN( 2 );
*l = *right;}
inline void s332::s1768( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s332* dr = (s332*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1557::iterator it = dr->s363.find( (s501*)PARN( 2 ) );
if( it == dr->s363.end() ) {
s504 s1389 = (s501*)s363->s349();
s504 s1770 = (s501*)s155->s349();
dr->s363.insert( make_pair( s1770, s1389 ) );
*s280 = s384;}
else {
it->second = (s501*)s363->s349();
*s280 = s385;}}
inline void s332::s344( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
p->s363.erase( (s501*)PARN( 2 ) );}
inline void s332::s339( s501** s280, size_t s517 ){}
inline void s332::s342( s501** s280, size_t s517 ){}
Iterator* s332::s321( s400* rv ){
s1267 pr = rv->s1337( this );
return new s1025( this,
pr.first.s15<s1261*>()->s1268(), pr.second.s15<s1261*>()->s1268() );}
wstring s332::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"{ ";
for( auto it = begin( s363 ); it != end( s363 ); ++it )
s717 += ( it == begin( s363 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s717 += L" }";
return s717;}
void s332::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Index : " << endl;
/*for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );*/
}
s1552::s1552( s268* s306, s1170 s1344, s1170 s1430, const s269* ast_ )
: s1539( s306, NULL, ast_ ){
assert( s1344 && s1430 );
s1343 = s1344;
s334 = s1430;
s867 s1324( s867::Cont( { s1895, 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1110( s1324 );}
s1552::s1552( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1539( s306, s612, ast_ ){
TDException s1059( s7::s1843, s1018, ast_ );
if( s78.size() ) {
wstring s673, s1427;
vector<pair<wstring, s1::s9<s6::s144>>> s96;
s1299( s78, s1427, s673, s96, ast_ );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
s1034 s1069 = new s269( s96[n].first, s627()->Nqj() );
s501* s1165 = (s501*)s277::s524( *s1069, s306, s612, s612->s304() );
basic_stringstream<wchar_t> s1194;
s96[n].second->s158( &s1194 );
s1034 s230 = new s269( s1194.str(), s627()->Nqj() );
s501* s1174 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
if( !s1343 ) {
s1343 = s1165->s366();
s334 = s1174->s366();}
if( s1343 != s1165->s366() || s334 != s1174->s366() )
throw s1059.s1097( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1165, s1174 ) );}}
else if( s673.size() ) {
s867::Cont vt, s1127, s1219;
size_t pos = 0;
s306->TR().s1163( s78, pos, vt );
size_t idx = 2;
s509::s1107( vt, idx, s1127 );
s867 s1126( s1127[0] );
s1343 = s306->TR().s1110( s1126 );
s509::s1107( vt, idx, s1219 );
s867 s1216( s1219[0] );
s334 = s306->TR().s1110( s1216 );}
else if( false && s78[0] == L'{' ) {
s518 = s78;}
else if( false && s78[0] == L'(' ) {
wstring sv = s4::s53( s78.substr( 1, s78.size() - 2 ), L" " );
wsmatch s1183;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1183, rg ) ) {
wstring s1207 = s1183[1].str();
wstring s1208 = s1183[2].str();
sv = L"Index(" + s1207 + L" " + s1208 + L")";
s518 = sv;}}
else
assert( 0 );}
if( s1552::proto.s13() )
s512 = 0;
else {
if( s1343 ) {
s324 = s306->TR().s1153( s867::Cont( { s1895, 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1153( s867::Cont( { s1552::proto->s366(), 1, s324, 0 } ) );}
else {
s324 = s512 = 0;}}}
s1552::s1552( const s1552& right, const s269* ast_ )
: s1539( right.s306, NULL, ast_ ){
s363 = right.s363;
s512 = right.s512;}
void s1552::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<pair<wstring, s145>> s96, const s269* ast_ ){
assert( !s78.empty() );
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1032 s1159( L"", true, s1914 );
s1159.s174( s78, pos, ob );
ob->s163( s96 );}
else
s1300( s306, s78, s1427, s673 );}
s501* s1552::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring si;
wstring s361 = s368();
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s53( s, L"{}" );
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );}
else
return 0;
return new s1552( s306, s612, si, &s736 );}
void s1552::s519( const s278* s960, bool ){
TDException s1059( s7::s1009, s1018, s627(), L"wrong Index definition" );
const wstring& s78 = s518;
if( s78.find( L"HashIndex<" ) == 0 ) {
assert( 0 );
s867::Cont vt, s1127, s1219;
size_t pos = 0;
s306->TR().s1163( s78, pos, vt );
size_t idx = 2;
s509::s1107( vt, idx, s1127 );
s867 s1126( s1127[0] );
s1343 = s306->TR().s1110( s1126 );
s509::s1107( vt, idx, s1219 );
s867 s1216( s1219[0] );
s334 = s306->TR().s1110( s1216 );}
else if( s78[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s144>> s156;
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1032 s1159( L"", true, s1914 );
s1159.s174( s78, pos, ob );
vector<pair<wstring, s145>> s147;
ob->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1034 s1069 = new s269( s147[n].first, s627()->Nqj() );
s501* s1165 = (s501*)s277::s524( *s1069, s306, (s278*)s960, s960->s304() );
basic_stringstream<wchar_t> s1194;
s147[n].second->s158( &s1194 );
s1034 s230 = new s269( s1194.str(), s627()->Nqj() );
s501* s1174 = (s501*)s277::s524( *s230, s306, (s278*)s960, s960->s304() );
if( !s1343 ) {
s1343 = s1165->s366();
s334 = s1174->s366();}
if( s1343 != s1165->s366() || s334 != s1174->s366() )
throw s1059.s1097( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1165, s1174 ) );}}
s518 = s960->s898();}
void s1552::s364(){
s1539<s1551, s504, s504, s1552>::s364();
s362 = s1539<s1551, s504, s504, s1552>::s356();
s362.insert( make_pair( L"insert", new s351( L"insert", &s1552::s343, s1286,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s1552::s828, 0,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s1552::s337, 0,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get-val", new s351( L"get-val", &s1552::s1637, 0,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s1552::s402, s1274,
{ s1238( { s7::s1567, s7::s1568 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s1552::s344, s1286,
{ s1238( { s7::s1567 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1552::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.equal_range( L"find" ).first->second->s1412( true );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"get-val" ).first->second->s1412( true );}
s501* s1552::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1::s9<s1552> s717 = new s1552( s306, s612, L"", ast_ );
s717->s1343 = s1343;
s717->s334 = s334;
return s717;}
s501* s1552::s370( s278* s612, const std::vector<s1170>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s867::Cont s1089;
s509::s1107( vt, idx, s1089 );
s867 s1088( s1089[0] );
s1170 s1323 = s306->TR().s1110( s1088 );
const s867& s1215 = s306->TR().s1112( s1323 );
s867::Cont s1127, s1219;
idx = 2;
s509::s1107( s1215.s875(), idx, s1127 );
s867 s1126( s1127[0] );
s1170 s1344 = s306->TR().s1110( s1126 );
s509::s1107( s1215.s875(), idx, s1219 );
s867 s1216( s1219[0] );
s1170 s1430 = s306->TR().s1110( s1216 );
s1552* s717 = new s1552( s306, s1344, s1430, NULL );
return s717;}
s1170 s1552::s1331( const wstring& s1727, const vector<s503>& l ) const{
s1170 s717 = 0;
if( s1727 == L"get" ) {
s717 = s324;}
else if( s1727 == L"get-s" ) {
s717 = s324;}
return s717;}
inline bool
s1552::s521( const s501* s522 ) const{
return ( s522->s366() == s366() );}
s277* s1552::s349() const{
return new s1552( *this );}
void s1552::s371( s277* p ) const{
p = new s1552( *this );}
size_t s1552::s330() const{
return (size_t)this;}
bool s1552::operator==( const s501* p ) const{
return ( this == p );}
bool s1552::operator<( const s501* p ) const{
return false;}
Iterator* s1552::s1328() {
auto it = begin( s363 );
return new s1553( this, s363.begin(), ++it ); }
Iterator* s1552::s1332() {
return new s1553( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s1552*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
inline void s1552::s343( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s1552* dr = (s1552*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s363.insert( make_pair( s155, s363 ) );}
inline void s1552::s828( s501** s280, size_t s517 ){
s1552* p = (s1552*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s1552::s337( s501** s280, size_t s517 ){
s1552* p = (s1552*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s1552::s1637( s501** s280, size_t s517 ){
s1552* p = (s1552*)DR;
s1557::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() ) {
*s280 = new s1048( p->s306, vector<s277*>(
{ (s501*)PARN( 2 ), (s501*)PARN( 3 ) } ) );}
else {
*s280 = new s1048( p->s306, vector<s277*>(
{ it->first.s15<s502*>()->s349(), it->second.s15<s502*>()->s349() } ) );}}
inline void s1552::s402( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s1552* dr = (s1552*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1557::iterator it = dr->s363.find( (s501*)PARN( 2 ) );
if( it == dr->s363.end() ) {
s501* s1389 = (s501*)s363->s349();
dr->s363.insert( make_pair( (s501*)s155->s349(), s1389 ) );
*s280 = s384;}
else {
it->second = (s501*)s363->s349();
*s280 = s385;}}
inline void s1552::s344( s501** s280, size_t s517 ){
s1552* p = (s1552*)DR;
p->s363.erase( (s501*)PARN( 2 ) );}
inline void s1552::s339( s501** s280, size_t s517 ){}
inline void s1552::s342( s501** s280, size_t s517 ){}
Iterator* s1552::s321( s400* rv ){
s1267 pr = rv->s1337( this );
return new s1553( this,
pr.first.s15<s1261*>()->s1268(), pr.second.s15<s1261*>()->s1268() );}
wstring s1552::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"{ ";
for( auto it = begin( s363 ); it != end( s363 ); ++it )
s717 += ( it == begin( s363 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s717 += L" }";
return s717;}
void s1552::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );*/
}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
s430::s430( s268* s306, const wstring& s78, const s269* ast_ )
: s350( s306, NULL, ast_ ), s797( s306, s1288, NULL ), s860( s306, s1288, NULL ){
s512 = s865.s13() ? 0 : s865->s366();
s797.s11();
s860.s11();}
s430::s430( const s430& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s797( right.s306, NULL, L"" ), s860( right.s306, NULL, L"" ){
s797 = right.s797;
s860 = right.s860;
s512 = right.s512;}
s501* s430::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return new s430( s306, L"", &s736 );}
void s430::s519( const s278* s960, bool ){
s1413();}
void s430::s364(){
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s374::proto->s368() + L">";
s1170 s1691 = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s362.insert( make_pair( L"new", new s351( L"new", &s430::s1384, s865->s366(),
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s430::s424, s1286,
{ s1238( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"read-rec", new s351( L"read-rec", &s430::s1853, s1286,
{ s1238( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"reset", new s351( L"reset", &s430::s431, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"files", new s351( L"files", &s430::s432, s1691,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"dirs", new s351( L"dirs", &s430::s1087, s1691,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s430::s339, s1284,
{ s1238() }, 0, 0 ) ) );}
s501* s430::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s430( s306, L"", ast_ );}
inline bool
s430::s521( const s501* s522 ) const{
return ( ((s430*)s522)->s366() == s366() );}
s277* s430::s349() const{
return s503( new s430( *this ) );}
void s430::s371( s277* p ) const{
p = new s430( *this );}
#undef s733
#define s733 ((s430*)(s502*)*s280)
inline void s430::s1384( s501** s280, size_t s517 ){
s430* s830 = (s430*)DR;
s430* s717 = new s430( s830->s306, L"", s830->s627() );
s717->s519( s830->ns, true );
*s280 = s717;}
void _findFiles( const wstring& path, const wregex& rgPatt, vector<wstring>& s40,
vector<wstring>& s41 ){
vector<wstring> s837, s846;
s3::s32( path, L".*", s837, s846 );
for( size_t n = 0; n < s837.size(); ++n ) {
wstring s1852 = path + s837[n];
if( regex_match( s1852, rgPatt ) ) 
s40.push_back( s1852 );}
for( size_t n = 0; n < s846.size(); ++n ) {
if( s846[n] == L".." ||  s846[n] == L"." )
continue;
wstring s1852 = path + s846[n];
s41.push_back( s1852 );
s4::s62( s1852 );
_findFiles( s1852, rgPatt, s40, s41 );}}
inline void s430::s424( s501** s280, size_t s517 ){
wstring path = ((s374*)PARN( 2 ) )->to_wstring();
const wstring& s547 = ((s374*)PARN( 3 ))->to_wstring();
vector<wstring> s837, s846;
s430* s830 = (s430*)DR;
s830->s797.clear();
s830->s860.clear();
if( !s3::s759( path ) )
path = s830->s306->s751() + path;
s4::s62( path );
s3::s32( path, s547, s837, s846 );
std::sort( begin( s837 ), end( s837 ) );
std::sort( begin( s846 ), end( s846 ) );
for( auto f : s837 )
s830->s797.add( new s374( s830->s306, s4::s787( path + f ), s830->ns ) );
for( auto f : s846 )
s830->s860.add( new s374( s830->s306, s4::s787( path + f ), s830->ns ) );}
inline void s430::s1853( s501** s280, size_t s517 ){
wstring path = ( (s374*)PARN( 2 ) )->to_wstring();
const wstring& s547 = ( (s374*)PARN( 3 ) )->to_wstring();
wregex rg( s547 );
vector<wstring> s837, s846;
s430* s830 = (s430*)DR;
s830->s797.clear();
s830->s860.clear();
if( !s3::s759( path ) )
path = s830->s306->s751() + path;
s4::s62( path );
_findFiles( path, rg, s837, s846 );
std::sort( begin( s837 ), end( s837 ) );
std::sort( begin( s846 ), end( s846 ) );
for( auto f : s837 )
s830->s797.add( new s374( s830->s306, s4::s787( f ), s830->ns ) );
for( auto f : s846 )
s830->s860.add( new s374( s830->s306, s4::s787( f ), s830->ns ) );}
inline void s430::s431( s501** s280, size_t s517 ){
s430* s830 = (s430*)DR;
s830->s797.clear();
s830->s860.clear();}
inline void s430::s432( s501** s280, size_t s517 ){
*s280 = &( (s430*)DR )->s797;}
inline void s430::s1087( s501** s280, size_t s517 ){
*s280 = &( (s430*)DR )->s860;}
inline void s430::s339( s501** s280, size_t s517 ){
s430* s830 = (s430*)DR;
*( (s360*)*s280 )->s372() = (int)(s830->s797.size() + s830->s860.size());}
wstring s430::to_wstring( uint32_t s1739 ) const{
wstring s717;
for( size_t n = 0; n < s860.size(); ++n )
s717 += ( n ? L" \"" : L"\"" ) + s860[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s797.size(); ++n )
s717 += ( n ? L" \"":L"\"") + s797[n]->to_wstring() + L"\"";
return s717;}
void s430::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Directory : " << endl;
for( size_t n = 0; n < s860.size(); ++n )
s860[n]->s310( pd, s201 + s434 );
for( size_t n = 0; n < s797.size(); ++n )
s797[n]->s310( pd, s201 + s434 );}
size_t s430::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s860.size(); ++n )
s717 = s717 * ( (s501*)&(s860[n]) )->s330() << 1;
for( size_t n = 0; n < s797.size(); ++n )
s717 = s717 * ( (s501*)&(s797[n]) )->s330() << 1;
return s717;}
bool s430::operator==( const s501* p ) const{
if( ( (s430*)p )->s797.size() != s797.size() )
return false;
if( ( (s430*)p )->s860.size() != s860.size() )
return false;
for( size_t n = 0; n < s797.size(); ++n )
if( !( ( s277* )&( *s797[n] ) == (s277*)( (s430*)p )->s797[n] ) )
return false;
for( size_t n = 0; n < s860.size(); ++n )
if( !( ( s277* )&( *s860[n] ) == (s277*)( (s430*)p )->s860[n] ) )
return false;
return true;}
bool s430::operator<( const s501* p ) const{
return false;}
s1462::s1462( s268* s306, const wstring& s78, s278* ns_, const s269* ast_ )
: s350( s306, ns_, ast_ ){
s512 = s1463.s13() ? 0 : s1463->s366();
if( s78.size() ) {}}
s1462::s1462( const s1462& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ){
s512 = right.s512;}
s501* s1462::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
wstring s363, s;
wstring tn = s368();
if( s_.find( tn + L"(" ) == 0 ) {
s = s4::s53( s_.substr( tn.size() + 1, s_.size() - ( tn.size() + 1 ) ), 
s49 );
if( s.empty() )
return new s1462( s306, L"", s612 );}
else
s = s4::s53( s_, s49 );
return new s1462( s306, L"", s612 );}
void s1462::s519( const s278* s960, bool ){
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s374::proto->s368() + L">";
s1170 pt = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s362.equal_range( L"files" ).first->second->s1414( pt
/*s306->TR().s1153( s867::Cont( { s763->s366(), s841->s366() }) )*/ );
s362.equal_range( L"dirs" ).first->second->s1414( pt
/*s306->TR().s1153( s867::Cont( { s763->s366(), s841->s366() }) )*/ );
}
void s1462::s364(){
s362.insert( make_pair( L"read", new s351( L"read", &s1462::s424, s1286,
{ s1238( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"reset", new s351( L"reset", &s1462::s1523, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"files", new s351( L"files", &s1462::s1499, 0 /*s763->s366()*/,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"dirs", new s351( L"dirs", &s1462::s1490, 0 /*s763->s366()*/,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1462::s339, s1284,
{ s1238() }, 0, 0 ) ) );}
s501* s1462::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1462( s306, L"", s612, ast_ );}
inline bool
s1462::s521( const s501* s522 ) const{
return ( ((s1462*)s522)->s366() == s366() );}
s277* s1462::s349() const{
return s503( new s1462( *this ) );}
void s1462::s371( s277* p ) const{
p = new s1462( *this );}
#undef s733
#define s733 ((s1462*)(s502*)*s280)
inline void s1462::s424( s501** s280, size_t s517 ){}
inline void s1462::s1523( s501** s280, size_t s517 ){}
inline void s1462::s1499( s501** s280, size_t s517 ){}
inline void s1462::s1490( s501** s280, size_t s517 ){}
inline void s1462::s339( s501** s280, size_t s517 ){}
wstring s1462::to_wstring( uint32_t s1739 ) const{
wstring s717 = L"File";
return s717;}
void s1462::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"File : " << endl;}
size_t s1462::s330() const{
size_t s717 = 0;
return s717;}
bool s1462::operator==( const s501* p ) const{
return false;}
bool s1462::operator<( const s501* p ) const{
return false;}
vector<wstring> s1472( { L":append" } );
s1471::s1471( s268* s306, s278* s616, s615* s617,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1482, s736 ){
if( l.size() < 2 || l.size() > 3 )
throw new s16( L"malformed syntax of 'to-file' procedure call." );
s280.assign( l.begin(), l.end() );
s512 = s1286;
s615::s1392( ( vector<s277*>& )l, s1472 );}
void
s1471::s519( const s278* s1848, bool proc ){
obj = s280[0].s15<s501*>();
s214 = s277::s1120( s306, s280[1], s612, this, s304() );
if( s280.size() > 2 )
mode = s277::s1120( s306, s280[2], s612, this, s304() );}
s504 s1471::s516( s501** s740, size_t s517 ){
s489 pc = s280[0]->s513();
s1::s9<s336> s612;
if( pc == s493 ) {
s612 = s280[0]->s516( 0, 0 ).s15<s336*>();}
else
s612 = ((s336*)s280[0].s15<s386*>()->s392());
return 0;}
s277* s1471::s349()const{
return new s1471( *this );}
vector<wstring> s1782( { L":append" } );
s1781::s1781( s268* s306, s278* s616, s615* s617,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1792, s736 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s280.assign( l.begin(), l.end() );
s512 = s1286;
s615::s1392( ( vector<s277*>& )l, s1782 );}
void
s1781::s519( const s278* s1848, bool proc ){
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s1778::proto->s368() + L">";
s512 = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s615::s519( s1848, proc );}
s504 s1781::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
s323* pv = s610.s15<s323*>();
wstring s198 = s607[1]->to_wstring();
s198 = s4::s787( s198 );
vector<s9<s146>> s692;
s1035 s1158 = new s1032( s198 );
s1158->read( s692, /*s7::s1222*/ L"" );
for( size_t m = 0; m < s692.size(); m++ ) {
s1778* po = new s1778( pv->Pass(), this, s692[m], NULL );
pv->add( po );}
return s610;}
s277* s1781::s349()const{
return new s1781( *this );}
s1170 s1686::s1679 = 0;
s1170 s1686::s1683 = 0;
s1170 s1686::s1678 = 0;
void Stream::s1635( std::wstring& s156, size_t s1646 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1654( const std::wstring& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1636( std::wstring& s156, const std::wstring& s73 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1655( const std::wstring& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1634( s1488& s156, size_t s1646 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1653( const s1488& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1633( s1488& s156, const s1488& s73 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1652( const s1488& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
template<class s1591, class s1593>
void s1577<s1591, s1593>::s1741(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1649 )
*s1649 << std::resetiosflags( f );}
template<class s1591, class s1593>
void s1577<s1591, s1593>::s1742(){
if( s1649 )
*s1649 << std::showpos;}
template<class s1591, class s1593>
void s1577<s1591, s1593>::s1743( int n ){
if( s1649 )
*s1649 << std::setw( n );}
template<class s1591, class s1593>
void s1577<s1591, s1593>::s1740(){
if( s1649 )
*s1649 << std::showpos;}
s527::s527( s268* s306, s278* ns_, const s269* ast_ )
: s1577( s306, ns_, ast_ ){
s512 = s869.s13() ? 0 : s869->s366();
s1648 = (basic_istringstream<wchar_t>*) &ss;
s1649 = (basic_ostringstream<wchar_t>*) &ss;}
s527::s527( const s527& r, const s269* ast_ )
: s1577( r.s306, r.ns, ast_ ), ss( r.ss.str() ){
s512 = s869->s366();}
s501* s527::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s527( s306, s612, ast_ );}
void s527::s364(){
s1577<s1671,s1674>::s364();
s362 = s1577<s1671, s1674>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s527::s1384, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"str", new s351( L"str", &s527::s528, s1288,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s527::s341, s869->s366(),
{ s1238() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1580, s1686::s1679 );
s306->TR().s1301( s512, s7::s1585, s1686::s1683 );
s306->TR().s1301( s512, s7::s1579, s1686::s1678 );}
void s527::s519( const s278*, bool ){
s1413();}
void s527::release(){
ss.clear();}
s501* s527::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
if( s_.find( L"StringStream(" ) == 0 )
return new s527( s306, s612, &s736 );
return NULL;}
s277* s527::s349() const{
return new s527( *this );}
void s527::s371( s277* p ) const{
if( p->s366() == s869->s366() )
((s527*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s366() ) );}
void s527::s1635( std::wstring& s156, size_t s1646 ){
s156 = ss.str().substr( 0, s1646 );}
void s527::s1654( const std::wstring& src ){
ss << src;}
void s527::s1636( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
s156.clear();
std::getline( ss, s156, s73[0] );}
void s527::s1655( const std::wstring& src ){
ss << src << endl;}
void s527::s1634( s1488& s156, size_t s1646 ){
s156 = (tdbyte_t*)U8( ss.str().substr( 0, s1646 )).data();}
void s527::s1653( const s1488& src ){
ss << U16( (char*)src.c_str() );}
void s527::s1633( s1488& s156, const s1488& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s73.c_str()) + L"'" );
s156.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s73.c_str())[0]);}
void s527::s1652( const s1488& src ){
ss << U16( (char*)src.c_str() ) << endl;}
wstring s527::to_wstring( uint32_t s1739 ) const{
return ss.str(); }
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s527*)(s502*)*s280)
inline void s527::s1384( s501** s280, size_t s517 ){
s527* ps = (s527*)DR;
s527* s717 = new s527( ps->s306, ps->ns, ps->s627() );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s527::s528( s501** s280, size_t s517 ){
*( (s374*)s280[0] )->s372() = ( (s527*)DR)->ss.str();}
inline void s527::s341( s501** s280, size_t s517 ){
((s527*)DR)->ss.rdbuf()->str(L"");}
void s527::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << ss.str() << endl;}
size_t s527::s330() const{
return hash<wstring>{}(ss.str());}
bool s527::operator==( const s501* p ) const{
return ( (s527*)p )->ss.str() == ss.str();}
bool s527::operator<( const s501* p ) const{
return ss.str() < ( (s527*)p )->ss.str();}
s1450::s1450( s268* s306, s278* ns_, const s269* ast_ )
: s1577( s306, ns_, ast_ ){
s512 = s1451.s13() ? 0 : s1451->s366();
s1648 = (basic_istringstream<tdbyte_t>*) &bs;
s1649 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1450::s1450( const s1450& r, const s269* ast_ )
: s1577( r.s306, r.ns, ast_ ), bs( r.bs.str() ){
s512 = s1451->s366();}
s501* s1450::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s1450( s306, ast_ );}
void s1450::s364(){
s1577<s1669, s1672>::s364();
s362 = s1577<s1669, s1672>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1450::s1384, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"array", new s351( L"array", &s1450::s1481, s1288,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s1450::s341, s1451->s366(),
{ s1238() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1580, s1686::s1679 );
s306->TR().s1301( s512, s7::s1585, s1686::s1683 );
s306->TR().s1301( s512, s7::s1579, s1686::s1678 );}
void s1450::s519( const s278*, bool ){
s1413();}
void s1450::release(){
bs.clear();}
s501* s1450::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1450( s306 );
return NULL;}
s277* s1450::s349() const{
return new s1450( *this );}
void s1450::s371( s277* p ) const{
if( p->s366() == s1451->s366() )
((s1450*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s366() ) );}
void s1450::s1635( std::wstring& s156, size_t s1646 ){
s156 = U16( (char*)bs.str().c_str() ).substr( 0, s1646 );}
void s1450::s1654( const std::wstring& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1450::s1636( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
s156.clear();
s1488 tmp;
std::getline( bs, tmp, (unsigned char)U8(s73.data())[0] );}
void s1450::s1655( const std::wstring& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1450::s1634( s1488& s156, size_t s1646 ){
s156 = bs.str().substr( 0, s1646 );}
void s1450::s1653( const s1488& src ){
bs << src.data();}
void s1450::s1633( s1488& s156, const s1488& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s73.c_str()) + L"'" );
s156.clear();
std::getline( bs, s156, s73[0] );}
void s1450::s1652( const s1488& src ){
bs << src << endl;}
wstring s1450::to_wstring( uint32_t s1739 ) const{
s1488 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s1450*)(s502*)*s280)
inline void s1450::s1384( s501** s280, size_t s517 ){
s1450* ps = (s1450*)DR;
s1450* s717 = new s1450( ps->s306, ps->s627() );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s1450::s1481( s501** s280, size_t s517 ){
s1488 s = ( (s1450*)DR)->bs.str();
( (s1448*)s280[0] )->s328().assign( begin( s ), end( s ) );}
inline void s1450::s341( s501** s280, size_t s517 ){
((s1450*)DR)->bs.rdbuf()->str(0);}
void s1450::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : [...]" << endl;}
size_t s1450::s330() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1450::operator==( const s501* p ) const{
return ( (s1450*)p )->bs.str() == bs.str();}
bool s1450::operator<( const s501* p ) const{
return bs.str() < ( (s1450*)p )->bs.str();}
s1460::s1460( s268* s306, s278* ns_, const s269* ast_ )
: s1577( s306, ns_, ast_ ){
s512 = s1461.s13() ? 0 : s1461->s366();
s1648 = NULL;
s1649 = NULL;}
s1460::s1460( s268* s306, const std::vector<s277*>& l, s278* s612,
const s269* ast_ )
: s1577( s306, s612, ast_ ){
s512 = s1461->s366();
s1648 = NULL;
s1649 = NULL;
if( l.size() ) {
if( l[0]->s366() == s1288 )
s1508 = l[0]->to_wstring();
else
s214 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1460::s1460( const s1460& r, const s269* ast_ )
: s1577( r.s306, r.ns, ast_ ), s214( r.s214 ), mode( r.mode ){
s512 = s1461->s366();
s1648 = NULL;
s1649 = NULL;}
s501* s1460::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s1460( s306, ast_ );}
void s1460::s364(){
s1577<s1670, s1673>::s364();
s362 = s1577<s1670, s1673>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1460::s1384, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"open", new s351( L"open", &s1460::s1499, s1286,
{ s1238(), s1238( { s1288 } ), s1238( { s1288, s1288 } ) }, 0, 2 ) ) );
s362.insert( make_pair( L"close", new s351( L"close", &s1460::s1490, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s1460::s424, s1286,
{ s1238( { s1275, s1284 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"read-lines", new s351( L"read-lines", &s1460::s1658, 0,	
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"write", new s351( L"write", &s1460::s1523, s1286,
{ s1238( { s1275, s1284 } ) }, 2, 2 ) ) );
s306->TR().s1301( s512, s7::s1580, s1686::s1679 );
s306->TR().s1301( s512, s7::s1585, s1686::s1683 );
s306->TR().s1301( s512, s7::s1579, s1686::s1678 );}
void s1460::s519( const s278*, bool ){
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s1448::proto->s368() + L">";
s1170 pt = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s362.equal_range( L"read-lines" ).first->second->s1414( pt );
s1413();}
void s1460::release(){
fs.close();}
s501*
s1460::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s277*> s740;
s277::s1500( s736, s306, s612, s346, s740 );
return new s1460( s306, s740, s612, &s736 );}
return NULL;}
s277*
s1460::s349() const{
return new s1460( *this );}
void s1460::s371( s277* p ) const{
if( p->s366() == s1461->s366() ) {
((s1460*)p)->s214 = s214;
((s1460*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s368() + L" to " + 
p->s368() );}
void s1460::s1635( std::wstring& s156, size_t s1646 ){
size_t s1227 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1227;
fs.seekg( 0, ios_base::beg );
int enc = 0;
if( fsz >= 4 ) {
uint8_t c1 = fs.get();
uint8_t c2 = fs.get();
uint8_t c3 = fs.get();
uint8_t c4 = fs.get();
if( c1 == 0xEF && c2 == 0xBB && c3 == 0xBF ) {
fs.seekg( 3, ios_base::beg );
fsz -= 3;
enc = s1867;}
else if( c1 == 0xFE && c2 == 0xFF ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1868;}
else if( c1 == 0xFF && c2 == 0xFE ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1869;}
else if( c1 == 0x0 && c2 == 0x0 && c3 == 0xFE && c4 == 0xFF ) {
enc = s1870;
fsz -= 4;}
else if( c1 == 0xFF && c2 == 0xFE && c3 == 0x0 && c4 == 0x0 ) {
enc = s1871;
fsz -= 4;}
else
fs.seekg( 0, ios_base::beg );}
size_t s1677 = s1646 ? ( std::min )( s1646, fsz ) : fsz;
string buf( s1677 + 0, '\0' );
fs.read( &buf[0], s1677 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1508 + L"'" );}
if( !enc || enc == s1867 ) {
s156 = U16( buf );
s156.shrink_to_fit();}
else {
fs.close();
throw new s16( L"file is not in UTF8 encoding and cannot be read as text: '" + s1508 + L"'" );}}
void s1460::s1654( const std::wstring& src ){
fs << U8(src).data();}
void s1460::s1636( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s156.clear();
if( fs.eof() )
return;
string buf;
char s1645 = U8( s73.data() )[0];
std::getline( fs, buf, s1645 );
s156 = U16( buf.data() );}
void s1460::s1655( const std::wstring& src ){
fs << U8(src).data() << endl;}
void s1460::s1634( s1488& s156, size_t s1646 ){
size_t s1227 = fs.tellg();
size_t fsz = (size_t)fs.seekg( ios::end ).tellg() - s1227;
fs.seekg( s1227 );
size_t s1677 = s1646 ? (std::min)( s1646, fsz ) : fsz;
s156.resize( s1677 );
fs.read( (char*)&s156[0], s1677 );}
void s1460::s1653( const s1488& src ){
fs << *(string*)&src;}
void s1460::s1633( s1488& s156, const s1488& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s73.c_str() ) + L"'" );
string buf;
s156.clear();
std::getline( fs, buf, (char)s73[0] );
std::swap( buf, *(string*)(&s156) );}
void s1460::s1652( const s1488& src ){
fs << *(string*)&src << endl;}
wstring s1460::to_wstring( uint32_t s1739 ) const{
return L"FileStream"; }
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s1460*)(s502*)*s280)
inline void s1460::s1384( s501** s280, size_t s517 ){
s1460* ps = (s1460*)DR;
s1460* s717 = new s1460( *ps );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s1460::s1499( s501** s280, size_t s517 ){
s1460*pf = (s1460*)DR;
if( s517 > 2 ) {
if( s280[2]->s366() == s1288 ) {
pf->s1508 = s280[2]->to_wstring();
pf->s214 = NULL;}
else {
pf->s214 = s280[2];
pf->s1508 = L"";}
if( s517 > 3 ) {
pf->mode = s280[3];}}
pf->_open();}
inline void s1460::s1490( s501** s280, size_t s517 ){
((s1460*)DR)->_close();
((s1460*)DR)->s1648 = NULL;
((s1460*)DR)->s1649 = NULL;}
inline void s1460::s1523( s501** s280, size_t s517 ){
assert( s517 == 4 );
assert( s280[2]->s366() == s1275 );
s1460*pf = (s1460*)DR;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1508 + L"'." );
s1448* s1501 = (s1448*)s280[2];
s501* s1503 = s280[3];
int s1517 = (int)*s1503;
pf->fs.write( (const char*)s1501->s328().data(), s1517 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1508 + L"'." );}
inline void s1460::s424( s501** s280, size_t s517 ){
assert(0);
((s1460*)DR)->_close();}
inline void s1460::s1658( s501** s280, size_t s517 ){
if( !((s1460*)DR)->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)((s1460*)DR)->addr();
s323& v = *(s323*)s733;
s1::s9<s1448> bar = new s1448( ( (s1460*)DR )->s306 );
while( !( (s1460*)DR )->fs.eof()) {
if( !std::getline( fs, *(string*)&bar->s328()/*, widen('\n')*/ ) )
throw new s16( L"cannot read from file '" + ( (s1460*)DR )->s1508 + L"'" );
v.s328().push_back( bar.s15<s502*>() );
v.s328().back()->s1413();
bar = new s1448( ( (s1460*)DR )->s306 );}}
void s1460::_open(){
if( fs.is_open() )
fs.close();
wstring path, s1512 = L"r";
if( !s1508.empty() )
path = s1508;
else {
if( s214->s513() != s492 )
path = s214->to_wstring();
else 
path = s214.s15<s386*>()->s392()->to_wstring();
s1508 = path;}
if( mode.s14() ) {
if( mode->s513() != s492 )
s1512 = mode->to_wstring();
else 
s1512 = mode.s15<s386*>()->s392()->to_wstring();}
if( !s3::s759( path ) )
path = s306->s751() + path;
s1648 = NULL;
s1649 = NULL;
std::ios_base::openmode md;
if( s1512.empty() || s1512 == L"r" ) {
md = ios::in | ios::binary;
s1648 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1512 == L"w" || s1512 == L"x" ) {
md = ios::out | ios::binary;
s1649 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1512 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1649 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1512 + L"'." );
if( s1512 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1460::_close(){
mode = s214 = NULL;
s1508.clear();
fs.close();}
void s1460::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s1508 << endl;}
size_t s1460::s330() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1460::operator==( const s501* p ) const{
return this == p;}
bool s1460::operator<( const s501* p ) const{
return this < p;}
s1573::s1573( s268* s306, s278* ns_, const s269* ast_ )
: s1577( s306, ns_, ast_ ){
s1648 = &std::wcin;}
s501* s1573::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1573::s364(){
s306->TR().s1301( s512, s7::s1580, s1686::s1679 );}
void s1573::s519( const s278*, bool ){
s1413();}
s501* s1573::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return NULL;}
s277* s1573::s349() const{
throw new s16( L"StdIn object cannot be copied" );}
void s1573::s371( s277* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1573::s1635( std::wstring& s156, size_t s1646 ){
s156.clear();
wcin >> s156;
if( s156.size() > s1646 )
s156.resize( s1646 );}
void s1573::s1654( const std::wstring& src ){
throw new s16( L"cannot output to StdIn" );}
void s1573::s1636( std::wstring& s156, const std::wstring& s73 ){
wcin >> std::ws;
s156.clear();
std::getline( wcin, s156 );}
void s1573::s1655( const std::wstring& src ){
throw new s16( L"cannot output to StdIn" );}
void s1573::s1634( s1488& s156, size_t s1646 ){
wstring buf( s1646, L'\0' );
wcin.read( &buf[0], s1646 );
size_t s717 = wcin.gcount();
buf.resize( s717 );
s156 = (tdbyte_t*)U8( buf ).data();}
void s1573::s1653( const s1488& src ){
throw new s16( L"cannot output to StdIn" );}
void s1573::s1633( s1488& s156, const s1488& s73 ){
wstring buf;
std::getline( wcin, buf );
s156 = (tdbyte_t*)U8( buf ).data();}
void s1573::s1652( const s1488& src ){
throw new s16( L"cannot output to StdIn" );}
wstring s1573::to_wstring( uint32_t s1739 ) const{
throw new s16( L"22: not implemented" );}
void s1573::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"StdIn object" << endl;}
size_t s1573::s330() const{
throw new s16( L"15: not implemented" );}
bool s1573::operator==( const s501* p ) const{
throw new s16( L"16: not implemented" );}
bool s1573::operator<( const s501* p ) const{
throw new s16( L"17: not implemented" );}
s1575::s1575( s268* s306, s278* ns_, const s269* ast_ )
: s1577( s306, ns_, ast_ ){
s1649 = &std::wcout;}
s501* s1575::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1575::s364(){
s306->TR().s1301( s512, s7::s1585, s1686::s1683 );}
void s1575::s519( const s278*, bool ){
s1413();}
s501* s1575::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return NULL;}
s277* s1575::s349() const{
throw new s16( L"StdOut object cannot be copied" );}
void s1575::s371( s277* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1575::s1635( std::wstring& s156, size_t s1646 ){
throw new s16( L"cannot get input from StdOut" );}
void s1575::s1654( const std::wstring& src ){
wcout << src;}
void s1575::s1636( std::wstring& s156, const std::wstring& s73 ){
throw new s16( L"cannot get input from StdOut" );}
void s1575::s1655( const std::wstring& src ){
wcout << src << endl;}
void s1575::s1634( s1488& s156, size_t s1646 ){
throw new s16( L"cannot get input from StdOut" );}
void s1575::s1653( const s1488& src ){
wcout << U16( (const char*)src.data() );}
void s1575::s1633( s1488& s156, const s1488& s73 ){
throw new s16( L"cannot get input from StdOut" );}
void s1575::s1652( const s1488& src ){
wcout << U16( (const char*)src.data() ) << endl;}
wstring s1575::to_wstring( uint32_t s1739 ) const{
throw new s16( L"21: not implemented" );}
void s1575::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"StdOut object" << endl;}
size_t s1575::s330() const{
throw new s16( L"18: not implemented" );}
bool s1575::operator==( const s501* p ) const{
throw new s16( L"19: not implemented" );}
bool s1575::operator<( const s501* p ) const{
throw new s16( L"20: not implemented" );}
s629::s629( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s238, s736, true ){
TDException s1059( s7::s1865, s1018, s736, L"malformed syntax of 'with' statement" );
size_t n = 0;
bool s1308;
for( ; n < l.size(); n += 2 ) {
s1308 = false;
if( ( (s501*)l[n] ) == s1863 ) {
if( l.size() == n )
throw s1059.s1097( L"the 'const' keyword should precede the parameter name" );
s1308 = true;
++n;}
if( l[n]->s513() != s492 ) {
if( s1308 )
throw s1059.s1097( L"the 'const' keyword should precede the parameter name" );
break;}
s386* s77 = (s386*)l[n];
s501* s646 = (s501*)l[n + 1];
if( s1308 )
s77->s1411();
s655.s564( s77->s643(), s646 );
s280.push_back( s646->s349() );
s606.push_back( s646 );
s657.push_back( s646 );
s658.push_back( *s77 );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
void
s629::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
if( !s512 )
s512 = s1286;
return;
s702 = proc ? s612->s304() : s1848->s304();
if( s612->s513() == s497 || s612->s513() == s496 ) {
if( s612->s513() == s496 )
return;}
if( s280.size() > s657.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s492 ) {
if( par.s15<s386*>()->s396().s13() )
par.s15<s386*>()->s519( this, proc );}
else
s916( par, n, s280[n], s1848 );}
for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n].s643(), s280[n].s15<s501*>(), s500::s150 );
s280[n]->s1855( s7::s940 );
s657[n] = s280[n];}
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304(), true );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( s611, proc );
else if( s608[n]->s513() != s493 )
s608[n]->s519( s611 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s608 ) {
if( it->s513() == s493 )
it.s15<Transd*>()->s519( s612, true );}
if( !s512 && s608.size() ) {
s512 = s608.back()->s366();
s610 = s306->TR().s541( s366(), s612, s612->s304() );}}
s504
s629::s516( s501** s723, size_t s732 ){
s504 s717 = s380, s156;
s657.resize( s280.size() );
for( size_t n = 0; n < s280.size(); ++n ) {
s504 s156;
if( s280[n]->s513() == s491 || 
s280[n]->s513() == s498 )
s156 = (s501*)s280[n]->s349();
else
s156 = s280[n]->s516( NULL, 0 );
if( s156->s644() < 0 )
return s717;
s657[n] = s156.s15<s502*>();}
for( size_t n = 0; n < s608.size(); ++n ) {
s156 = s608[n]->s516( s723, s732 );
s717 = s156;
if( s156->s644() < 0 )
break;}
for( size_t n = 0; n < s280.size(); ++n ) {
s280[n]->release();}
s657.clear();
return s717;}
s311::s311( s268* s306, s278* s616, Transd* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s260, s736 ){
if( l.size() < 2 )
throw new s16( s260 + L"(): wrong numbers of arguments" );
s280.push_back( l[0] );
s657.resize( 1 );
s658.push_back( s386( L"@cond", s306 ) );
s608.insert( s608.end(), l.begin() + 1, l.end() );}
void
s311::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
s312 = s280[0];
s512 = s608.back()->s366();}
s504
s311::s516( s501** s723, size_t s732 ){
s504 s717 = s380, s156;
while( 1 ) {
if( (bool)*s312->s516( 0, 0 ) == false )
return s717; 
for( size_t n = 0; n < s608.size(); ++n ) {
s156 = s608[n]->s516( s723, s732 );
if( s156->s644() < 0 )
break;}
s717 = s156;
if( s717->s644() < 0 /*s717->s644() == s7::s454 || s717->s644() == s7::s455*/ ) {
if( s717->s644() == s7::s454 )
s717 = s380.s15<s501*>();
break;}}
return s717;}
s314::s314( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s259, s736, true ),
s318( s7::s477, s306 ), s319( s306, 0 ){
if( l.size() < 1 )
throw new s16( s259 + L"(): wrong numbers of arguments" );
s655.s564( s318.s643(), &s319 );
s606.push_back( (s501*)&s319 );
s657.push_back( (s501*)&s319 );
s658.push_back( s386( s318.s643(), s306 ) );
s315 = l[0];
s386* w = (s386*) l[1];
if( w->s643() != L"with" )
throw new s16( L"unknown syntax of 'through' statement" );
s316 = (s386*) l[2];
s655.s564( s316->s643(), s317.s15<s501*>() );
s606.push_back( (s501*)&s319 ); //..
s657.push_back( (s501*)&s319 );
s658.push_back( s386( s316->s643(), s306 ) );
s608.assign( l.begin()+3, l.end() );}
void
s314::s519( const s278* s1848, bool proc ){
s489 pc = s315->s513();
if( pc == s495 ) {
s315 = s624( s315.s15<s584*>(), s306, s612, this, s304(), proc );
s315.s15<Transd*>()->s519( s1848, proc );}
else if( pc == s492 )
s315.s15<s386*>()->s519( this, proc );
else
throw new s16( L"unknown container type" );
s657[1] = s306->TR().s541( ( (s336*)s315->s515() )->s327(), s612, s612->s304() );
s657[1]->s1855( s7::s940 );
s615::s519( s1848, proc );}
s504 s314::s516( s501** s723, size_t s732 ){
s504 s717;
s489 pc = s315->s513();
s1::s9<s336> s612;
if( pc == s493 ) {
s612 = s315->s516(0,0).s15<s336*>();}
else
s612 = ((s336*)s315.s15<s386*>()->s392());
Iterator* s1123 = s612->s321( NULL );
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() ) {
s717 = s380.s15<s501*>();
break;}
s657[1] = p;
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s723, s732 );
if( s717->s644() < 0 )
break;}
if( s717->s644() == s7::s454 || s717->s644() == s7::s455 )
break;}
return s717;}
s640::s640( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s265, s736, true ),
s318( s7::s477, s306 ), s319( s306, 0 ){
TDException s1059( s7::s1844, s1018, s736, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s1059.s1097( L"too few arguments" );
s655.s564( s318.s643(), &s319 );
s606.push_back( (s501*)&s319 );
s657.push_back( (s501*)&s319 );
s658.push_back( s386( s318.s643(), s306 ) );
s277* p = l[0];
if( p->s513() != s492 )
throw s1059.s1097( L"the variable must be a name" );
s748 = (s386*) l[0];
varval = s380.s15<s501*>();
s386* in = (s386*) l[1];
if( in->s643() != L"in" )
throw s1059.s1097( L"the 'in' keyword is missing" );
s315 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s513() != s492 )
throw s1059.s1097( actmsg );
if( ((s386*)p)->s643() == L"where" ) {
where = l[4];
idx = 5;}
if( l.size() < ( idx + 2 ) )
throw new s16( actmsg );
p = l[idx];
if( p->s513() != s492 )
throw new s16( actmsg );
if( ((s386*)p)->s643() == L"project" ) {
if( l.size()  )
s1169 = l[idx+1];}
else {
if( ((s386*)p)->s643() != L"do" )
throw new s16( actmsg );
s608.assign( l.begin() + (idx + 1), l.end() );}
s655.s564( s748->s643(), NULL );
s606.push_back( varval );
s657.push_back( varval );
s658.push_back( s386( s748->s643(), s306 ) );}
void
s640::s519( const s278* s1848, bool proc ){
TDException s1059( s7::s1548, s1018, s627(), L"malformed syntax of 'for' statement" );
s489 pc = s315->s513();
if( pc == s495 ) {
s503 s616 = s624( s315.s15<s584*>(), s306, s612, this, s304(), proc );
s315 = s616;
s315.s15<Transd*>()->s519( s1848, false );}
else if( pc == s492 ) {
s315.s15<s386*>()->s519( this, proc );}
else if( pc == s491 )
s315->s519( this );
else
throw s1059.s1097( L"unknown iterable type" );
s502* s1650 = s315->s515();
s1170 vt = ( (s336*)s1650 )->ValType();
varval = s306->TR().s541(vt, s612, s612->s304() );
varval->s1855( s7::s940 );
s748->s397( varval );
s657[1] = varval.s15<s502*>();
s655.s564( s748->s643(), varval.s15<s502*>(), s500::s150 );
if( where ) {
pc = where->s513();
if( pc == s495 ) {
where = s624( where.s15<s584*>(), s306, s612, this, s304(), proc );
where.s15<Transd*>()->s519( s1848, false );}
else
throw s1059.s1097( L"WHERE clause must be a lambda" );}
if( s1169 ) {
pc = s1169->s513();
if( pc == s495 ) {
s1169 = s624( s1169.s15<s584*>(), s306, s612, this, s304(), proc );
s1169.s15<Transd*>()->s519( s1848, false );}
else if( pc == s492 ){
s1169.s15<s386*>()->s519( this );}
else if( pc == s491 )
(void)0;
else
throw s1059.s1097( L"PROJECT clause must be a lambda." );
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + 
s306->TR().s854( s1169->s366() ) + L">";
ts = s306->TR().s1520( ts );
s512 = s323::proto.s15<s323*>()->s1338( ts, s1433 );}
s615::s519( s1848, proc );}
s504 s640::s516( s501** s723, size_t s732 ){
s504 s717 = s610;
s489 pc = s315->s513();
s9<s336> s612;
if( pc == s493 )
s612 = s315->s516( 0, 0 ).s15<s336*>();
else if( pc == s492 )
s612 = ((s336*)s315.s15<s386*>()->s392());
else
s612 = s315.s15<s336*>();
if( s1169.s14() )
s610.s15<s323*>()->clear();
Iterator* s1123 = s612->s321( NULL );
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() )
break;
s657[0] = s1123->Idx();
s657[1] = p.s15<s502*>();
if( where ) {
if( ((bool)*(s501*)where->s516( 0, 0 )) != true )
continue;}
if( s1169 ) {
s610.s15<s323*>()->add( 
s1169->s516( 0, 0 ).s15<s502*>()->s349() );}
else {
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s723, s732 );
if( s717->s644() < 0 )
break;}
if( s717->s644() == s7::s454 || s717->s644() == s7::s455 ) {
if( s717->s644() == s7::s454 )
s717 = s380.s15<s501*>();
break;}}}
return s717;}
s277* s629::s349()const{
return new s629( *this );}
s277* s311::s349()const{
return new s311( *this );}
s277* s314::s349()const{
return new s314( *this );}
s277* s640::s349()const{
return new s640( *this );}
s628::s628( s268* s306, s278* s612, s615* s611,
s586 ct, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s612, s611, ct, l, s736, false ){
s599 = s596;}
void s628::s677( s1170 s646, s615* pOvr ){
types.push_back( s646 );
s678.push_back( pOvr );}
s504 s628::s516( s501** s723, size_t s732 ){
return s615::s516( s723, s732 );}
s905::s905( s268* s306 )
: s615( s306, NULL, NULL, s588, s257, NULL, true ){
s511 = s1395;
if( s905::proto.s13() ) {
s512 = 0;
wh = s7::s941;}
else {
s512 = s905::proto->s366();
wh = s7::s940;}}
s905::s905( s268* s306, s278* s616, s615* s617, 
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s257, s736, true ){
s511 = s1395;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( (s501*)l[n] ) == s949 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s2082.push_back( l[n + 1]->s366() );
n += 2;
break;}
if( l[n]->s513() != s492 )
break;
s386* s77 = (s386*)l[n];
lang::s685( s77->s643() );
s501* s646 = (s501*)l[n + 1];
s655.s564( s77->s643(), s646 );
s280.push_back( s646 );
s606.push_back( s646 );
s657.push_back( s646 ); 
s2082.push_back( s646->s366() );
s658.push_back( s386( s77->s643(), s306 ) );}
s608.insert( s608.end(), l.begin() + n, l.end() );
if( s2082.size() ) {
s867::Cont vt = { s1894, (s1170)s2082.size() };
for( size_t n = 0; n < s2082.size(); ++n ) {
vt.push_back( s2082[n] );
vt.push_back( 0 );}
s512 = s306->TR().s1153( vt );}
else
s512 = s1894;}
s905::s905( s268* s306, s278* s616, const vector<s1170>& l,
s1170 pt, const s269* s736 )
: s615( s306, s616, NULL, s588, s257, s736, true ){
s511 = s1395;
s512 = pt;
for( size_t n = 0; n < l.size(); n += 2 )
s2082.push_back( l[n] );}
s905::s905( s905& s2080, const std::vector<s503>& l, const s269* s736 )
: s615( s2080.s306, s2080.s612, (s615*)s2080.s611, s588, s257, s736, true ){
s511 = s1395;
s512 = s2080.s512;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( l[n].s15<s501*>() ) == s949 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s512 = l[n + 1]->s366();
n += 2;
break;}
if( l[n]->s513() != s492 )
break;
s386* s77 =  l[n].s15<s386*>();
lang::s685( s77->s643() );
s501* s646 = l[n + 1].s15<s501*>();
s655.s564( s77->s643(), s646 );
s280.push_back( s646 );
s606.push_back( s646 );
s657.push_back( s646 );
s658.push_back( s386( s77->s643(), s306 ) );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
s501* s905::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
TDException s1059( s7::s2071, s1018, &s736,
L"wrong Lambda constructor syntax" );
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s819 = s905::proto->s368();
wstring s1427, s673;
s1170 pt = 0;
s905* s717 = NULL;
if( s736.s274( L"ownerType" ) == L"CallSite" ) {
wstring s1489 = s736.s274( L"ownerName" );
if( s1489.find( L"new<Lambda<" ) == 0 ) {
wstring stype = s1489.substr( 4, s1489.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s.find( s819 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s1059.s1097( L"missing type signature" );
s1300( s306, s, s1427, s673 );
if( s1427.empty() )
throw s1059.s1097( L"missing type signature" );
if( s673.size() ) {
if( s673.find( L"lambda" ) == 0 || s673[0] == 955 ) {
s1034 ast_ = new s269( L"(" + s673 + L")", s736.Nqj() );
s508 cs = s615::s1235( *ast_, s306, s612, s612->s304() );
return s615::s624( cs, s306, s612, this, s612->s304(), false );}
else if( s673[0] != L']' )
throw s1059.s1097( L"malformed Lambda initializer" );}
s867::Cont vt;
size_t pos = 0;
s306->TR().s1163( s1427, pos, vt );
pt = s306->TR().s1110( s867( vt ), false );
if( !pt ) {
pt = s306->TR().s1153( vt );}
s717 = new s905( s306, s612, vt, pt, &s736 );}
return s717;}
void
s905::s519( const s278* s1848, bool proc ){
s1170 pt = s512;
s512 = s1286;
s615::s519( s1848, false );
s512 = pt;
if( s2082.empty() ) {
s2082.push_back( s1286 );
if( s608.size() )
s2082.push_back( s608.back()->s366() );
else
s2082.push_back( s1286 );}
if( s1848 )
s610 = s306->TR().s541( s1494(), (s278*)s1848, s1848->s304() );
else
s610 = s306->TR().s541( s1494(), s612, s612->s304() );
if( s610.s13() )
s610 = s380.s15<s501*>();
s1413();}
s504 s905::s516( s501** s723, size_t s732 ){
s504 s717;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1075[n+shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1075[n + shift];}
else if( pc == s491 )
*( s603 + n + shift ) = ( s501* )*( s604 + n );}}
if( s607.size() )
s657.assign( s607.begin() + 1, s607.end() );
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s603, s517 );
if( s717->s644() < 0 )
break;}
return s717;}
s501* s905::s370( s278* s612, const vector<s1170>& vt ) const{
s1170 pt = s306->TR().s1153( vt );
return new s905( s306, s612, vt, pt, NULL );}
s615* s905::s1862( const std::wstring& s708, s615* s219, vector<s277*>& s740 ) const{
if( s708 == L"new" ) {
return new s1857( s306, s612.s15<s278*>(), s219, &s501::s2074, 
s740, L"new", NULL );}
return s501::s1862( s708, s219, s740 );}
s277* s905::s349()const{
return new s905( *this );}
s501* s905::s2075( s501** s280, size_t s517 ){
return new s905( *this );}
void s905::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Lambda : " <<  s284 << endl;
s615::s310( pd, s201 );}
s631::s631( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s248, s736 ){
s280.assign( l.begin(), l.end() );
s512 = s1274;}
s504 s631::s516( s501**, size_t s517 ){
*s610.s15<s375*>()->s372() = 0;
for( size_t n = 0; n < s280.size(); ++n ) {
if( ( bool )*( (s502*)( s280[n]->s516( 0, 0 ) ) ) ) {
*s610.s15<s375*>()->s372() = 1;
return s610;}}
return s610;}
s632::s632( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s248, s736 ){
s280.assign( l.begin(), l.end() );
s512 = s1274;}
s504 s632::s516( s501**, size_t ){
*s610.s15<s375*>()->s372() = 1;
for( size_t n = 0; n < s280.size(); ++n ) {
if( !( bool )*( (s502*)( s280[n]->s516( 0, 0 ) ) ) ) {
*s610.s15<s375*>()->s372() = 0;
return s610;}}
return s610;}
s1578::s1578( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1602, s736, true ),s1676( s7::s1544, s306 ),
s318( s7::s477, s306 ), s319( s306, 0 ){
TDException s1059( s7::s1845, s1018, s736, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s1059.s1097( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s655.s564( s318.s643(), &s319 );
s655.s564( s1676.s643(), NULL );
s657.push_back( (s501*)&s319 );
s657.push_back( NULL );
s658.push_back( s386( s318.s643(), s306 ) );
s658.push_back( s386( s1676.s643(), s306 ) );
s315 = l[0];
if( l.size() > 1 )
lambda = l[1];
s512 = s1274;}
void
s1578::s519( const s278* s1848, bool proc ){
TDException s1059( s7::s1546, s1018, s627(), L"malformed syntax of 'any()' function call" );
s489 pc = s315->s513();
if( pc == s495 ) {
s503 s616 = s624( s315.s15<s584*>(), s306, s612, this, s304(), proc );
s315 = s616;
s315.s15<Transd*>()->s519( s1848, false );}
else if( pc == s492 ) {
s315.s15<s386*>()->s519( this );}
else if( pc == s491 )
s315->s519( this );
else
throw s1059.s1097( L"unknown iterable type" );
varval = s306->TR().s541( ( (s336*)s315->s515() )->ValType(), s612, s612->s304() );
varval->s1413();
s1676.s397( varval );
s657[1] = varval.s15<s502*>();
if( lambda.s14() ) {
if( lambda->s513() == s492 ) {
lambda.s15<s386*>()->s519( s611 );}
else {
lambda = s277::s1120( s306, lambda, this, this, s611->s304() );}}
s615::s519( s1848, false );}
s504 s1578::s516( s501**, size_t  ){
TDException s1059( s7::s1547, s1549, past );
s504 s717 = s610;
*s717.s15<s375*>()->s372() = false;
s489 pc = s315->s513();
s9<s336> s612;
if( pc == s493 )
s612 = s315->s516( 0, 0 ).s15<s336*>();
else if( pc == s492 )
s612 = ( (s336*)s315.s15<s386*>()->s392() );
else
s612 = s315.s15<s336*>();
Iterator* s1123 = s612->s321( NULL );
while( 1 ) {
s503 p = s1123->s322();
if( p.s13() )
break;
s657[0] = s1123->Idx();
s657[1] = p.s15<s502*>();
if( lambda.s14() ) {
if( ( ( bool )*(s501*)lambda->s516( 0, 0 ) ) == true ) {
*s717.s15<s375*>()->s372() = true;
break;}}
else {
if( ( ( bool )*p.s15<s501*>() ) == true ) {
*s717.s15<s375*>()->s372() = true;
break;}}}
return s717;}
vector<wstring> s1047( { L"else", L"elsif" } );
s633::s633( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s235, s736 ){
wstring s746 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s746 + L"too few arguments." );
s280.assign( l.begin(), l.end() );
s615::s1392( ( vector<s277*>& )l, s1047 );}
void s633::s775( bool proc ){
wstring s746 = L"malformed syntax of 'if' statement: ";
s647.push_back( s280[0] );
s648.push_back( s602() );
s648.back().push_back( s280[1] );
if( s280.size() > 2 ) {
size_t n = 2;
while( n < s280.size() ) {
s503 p = s280[n];
s489 pc = s280[n]->s513();
if( pc == s1172 ) {
if( p.s15<s386*>()->Id() == s1370 ) {
if( s280.size() < n + 2 )
throw new s16( s746 + L"incomplete clause" );
s647.push_back( s280[++n] );
s648.push_back( s602() );
s648.back().push_back( s280[n] );}
else if( p.s15<s386*>()->Id() == s1369 ) {
if( s280.size() < n + 1 )
throw new s16( s746 + L"empty clause" );
s648.push_back( s602() );
s648.back().push_back( s280[++n] );}
else
s648.back().push_back( s280[n] );}
else
s648.back().push_back( s280[n] );
n++;}}
if( !proc ) {
size_t s959 = s648[0].size();
s1170 prevPt = s607[s959]->s366();
for( size_t n = 1; n < s648.size(); ++n ) {
s959 += s648[n].size() + 1;
s1170 tmpPt = s607[s959]->s366();
if( tmpPt && tmpPt != s827->s366() && ( tmpPt != prevPt ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s512 = prevPt;
if( !s512 ) // e.g. break, continue
s512 = s779->s366();}
else
s512 = s779->s366();}
void
s633::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
s775( proc );
s610 = s306->TR().s541( s366(), s612, s612->s304() );
s607.insert( s607.begin(), s610 );}
s504 s633::s516( s501**, size_t ){
size_t idx = string::npos;
for( size_t n = 0; n < s647.size(); ++n ) {
if( ( bool )*( s647[n]->s516( 0, 0 ).s15<s501*>() ) ) {
idx = n;
break;}}
if( idx != string::npos || s648.size() > s647.size() ) {
if( idx == string::npos )
idx = s648.size() - 1;
s504 s717;
s602& el = s648[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s717 = el[n]->s516( 0, 0 );
if( s717->s644() < 0 )
break;}
return s717;}
return s380;}
vector<wstring> s1045( { L"to:", L":sign", L":nosign", L"width:", L":group", L":nl" } );
s634::s634( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s256, s736 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s736->Src().find( L"lout" );
if( pl1 < s736->Src().find( L"textout" ) )
lout = true;
vector<s277*>tmp( l );
s615::s1392( tmp, s1045 );
s280.assign( tmp.begin(), tmp.end() );
s512 = s779->s366();}
s634::s634( s268* s306 )
: s615( s306, NULL, NULL, s588, s256, NULL ), s42( NULL ),
lout( false ){
s512 = s779->s366();}
void s634::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
if( s280[0]->s513() == s1172 ) {
if( s280[0].s15<s386*>()->Id() == s1380 ) {
s42 = s280[1];
s280.erase( s280.begin(), s280.begin() + 2 );
s607.erase( s607.begin()+1, s607.begin() + 3 );
nlocs = s280.size();
s517 = s607.size();}}
for( size_t n = 0; n < s280.size(); ++n ) {
if( s280[n]->s513() == s1172 ) {
int mark = (int)*( s280[n].s15<s386*>() )->s392();
if( mark != s1745 && s280.size() <= n )
throw new s16( L"incorrect usage of formatting marker: " + (s280[n].s15<s386*>())->s643() );
if( mark == s1746 && s280[n+1]->s366() != s1284 )
throw new s16( L"'" + (s280[n].s15<s386*>())->s643() + L"' formatting marker must have an argument" );}}
s1413();}
s504 s634::s516( s501** s723, size_t s732 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1504 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1075[n + shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1075[n + shift];}}}
s1::s9<Stream> s826;
if( s42.s14() ) {
s489 pc = s42->s513();
if( pc == s493 )
s826 = s42->s516( 0, 0 ).s15<Stream*>();
else if( pc == s492 )
s826 = (Stream*)s42.s15<s386*>()->s392();
else
s826 = s42.s15<Stream*>();}
else
s826 = s1576.s15<Stream*>();
s826->s1741();
uint32_t flags = 0;
for( size_t n = 1; n < s607.size(); ++n ) {
if( s607[n]->s513() == s1172 ) {
int mark = (int)*( (s386*)s607[n] )->s392();
if( mark == s1643 ) {
flags |= s1734;}
if( mark == s1766 ) {
flags &= ~s1734;}
else if( mark == s1746 ) {
int w = (int)*s607[++n];
s826->s1743( w );}
else if( mark == s1744 ) {
flags |= s1733;}
else if( mark == s1745 ) {
s826->s1655( L"" );
n++;}}
else {
s504 s156 = s607[n]->s516( s723, s517 );
s826->s1654( s156->to_wstring( flags ) );}}
if( lout )
s826->s1655( L"" );
return s380;}
s277* s634::s349()const{
return new s634( *this );}
s906::s906( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s923, s736 ){
if( l.size() > 1 )
throw new s16( s923 + L": too many arguments" );
s608.assign( l.begin(), l.end() );}
void
s906::s519( const s278* s1848, bool proc ){
if( s608.size() ) {
s615::s519( s1848, false );
s610 = s608[0]->s515();}
else {
s610 = s380.s15<s501*>();
s512 = s1286;}}
s504 s906::s516( s501** s740, size_t s517 ){
s501* s717;
if( s608.size() )
s717 = s615::s516( s740, s517 );
else
s717 = new s379( s306 );
s717->s1855( s7::s939 );
return s717;}
s277* s906::s349()const{
return new s906( *this );}
s982::s982( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s986, s736 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s986 + L": wrong number of arguments" );
if( l.empty() )
s280.push_back( new s360( s306, 0 ) );
else
s280.assign( l.begin(), l.end() );
s512 = s1284;}
void
s982::s519( const s278* s1848, bool proc ){
s615::s519( s1848, false );
if( s280[0]->s366() != s1284 )
throw new s16( L"The parameter to (exit ) must have Integer type." );}
s504 s982::s516( s501** s740, size_t s517 ){
s615::s516( s740, s517 );
code = (int)*s607[1];
throw new s16( (uint32_t) code );}
s277* s982::s349()const{
return new s982( *this );}
s636::s636( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s264, s736 ), s79( s306 ){
if( l.size() != 1 )
throw new s16( s264 + L": wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s827->s366();
s79.s11();}
s636::s636( s268* s306 )
: s615( s306, NULL, NULL, s588, s264, NULL ), s79( s306 ){
s512 = s827->s366();
s79.s11();}
void
s636::s519( const s278* s1848, bool proc ){
s79.s378( s280[0]->to_wstring() );
s610 = s381.s15<s501*>();
s607.push_back( s280[0]->s515() );}
s504 s636::s516( s501** s740, size_t s517 ){
s79.s378( s280[0]->s516( s740, s517 )->to_wstring() );
return &s79;}
s637::s637( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s262, s736, true ), 
s77( s7::s476, s306 ), s646( s306 ){
if( l.size() < 2 )
throw new s16( s262 + L"(): wrong numbers of arguments" );
s655.s564( s77.s643(), &s646 );
s606.push_back( (s501*)&s646 );
s657.push_back( (s501*)&s646 );
s658.push_back( s386( s77.s643(), s306 ) );
s608.assign( l.begin(), l.end() );
if( ((s584*)l.back())->s305() != s263 )
throw new s16( L"the catch clause must be the last statement in the try block" );}
s637::s637( s268* s306 )
: s615( s306, NULL, NULL, s588, s262, NULL, true ), 
s77( s7::s476, s306 ), s646( s306 ){}
void
s637::s519( const s278* s1848, bool proc ){
s615::s519( s1848, proc );
ctch = s608.back().s15<s638*>();
s608.pop_back();}
s504 s637::s516( s501** s740, size_t s517 ){
s501* s717 = NULL;
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s740, s517 );
if( s717->s644() < 0 ) {
if( s717->s644() == s7::s455 ) {
s646.s378( ((s376*)s717)->Msg() );
s717 = ctch->s516( &s717, 1 );}
break;}}
return s717;}
s638::s638( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s263, s736 ){
s608.assign( l.begin(), l.end() );
s512 = s779->s366();}
s638::s638( s268* s306 )
: s615( s306, NULL, NULL, s588, s263, NULL ){
s512 = s779->s366();}
s504 s638::s516( s501** s723, size_t s732 ){
s501* s156;
for( size_t n = 0; n < s608.size(); ++n ) {
s156 = s608[n]->s516( s723, s732 );
if( s156->s644() < 0 ) {
return s156;}}
return s380.s15<s501*>();}
s798::s798( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s794, s736 ){}
void
s798::s519( const s278* s1848, bool proc ){}
s504 s798::s516( s501** s740, size_t s517 ){
return 0;}
s1856::s1856( s268* s306, s278* s616, s615* s617, s1858 ptr_,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, L"", s736 ), s1860( ptr_ ){
subject = l[0];
s280.assign( l.begin() + 1, l.end() );}
void
s1856::s519( const s278* s1848, bool proc ){
s512 = s612->s366();
s615::s519( s1848, proc );
s1413();}
s504 s1856::s516( s501** s740, size_t s517 ){
s505	s1830 = subject->s516( 0, 0 ).s15<s278*>();
return ( *s1830.*s1860)( &s607[0], s517 );}
s1857::s1857( s268* s306, s278* s616, s615* s617, s1859 ptr_,
const std::vector<s277*>& l, const wstring& s708, const s269* s736 )
: s615( s306, s616, s617, s588, s708, s736 ), s1860( ptr_ ){
subject = l[0];
s280.assign( l.begin() + 1, l.end() );}
void
s1857::s519( const s278* s1848, bool proc ){
s503 s738 = subject;
if( s738->s513() == s492 )
s738 = s738.s15<s386*>()->s392();
if( s738->s513() == s1395 ) {
if( s284 == L"new" )
s512 = s738->s366();
else
s512 = s738.s15<s905*>()->s1494();}
else
s512 = s612->s366(); //subject->s366();
s615::s519( s1848, proc );
s1413();}
s504 s1857::s516( s501** s740, size_t s517 ){
s503 s738 = subject;
if( s738->s513() == s492 )
s738 = s738.s15<s386*>()->s392();
if( s738->s513() == s1395 ) {
if( s284 == L"new" ) {
s905* s717 = new s905( *s738.s15<s905*>() );
s717->s519( s612, true );
return s717;}
s738.s15<s905*>()->s620( s280 );
return s738->s516( 0, 0 ).s15<s278*>();}
else {
s505 s1830 = subject->s516( 0, 0 ).s15<s278*>();
return ( *s1830.*s1860 )( &s607[0], s517 );}}
s1785::s1785( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1795, s736 ){
s280.assign( l.begin(), l.end() );}
s1785::s1785( const s1785& right )
: s615( right ), cmd( right.cmd ){}
void
s1785::s519( const s278* s1848, bool proc ){
s512 = s1286;
s615::s519( s1848, proc );}
void s1788( const wstring& cmd, wstring* s1822, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1822 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1822 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s504 s1785::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
wstring cmd_ = s607[1]->to_wstring(), s1823;
bool* pdone = ( (s375*)s607[2] )->s372();
wstring *s1822 = NULL;
if( s607.size() > 3 )
s1822 = ( (s374*)s607[3] )->s372();
else
s1822 = &s1823;
if( s879.joinable() )
s879.join();
s879 = thread( s1788, cmd_, s1822, pdone );
return s610;}
s1783::s1783( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1793, s736 ){
if( l.size() != 2 )
throw new s16( s1793 + L"(): wrong numbers of arguments" );
if( l[0]->s513() != s492 )
throw new s16( s1793 + L"(): the first argument must be a reference" );
s280.assign( l.begin(), l.end() );}
s1783::s1783( const s1783& right )
: s615( right ){}
void
s1783::s519( const s278* s1848, bool proc ){
s512 = s1286;
s615::s519( s1848, proc );}
s504 s1783::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
s386* dr = s280[0].s15<s386*>();
s278* mod = dr->s396().s15<s278*>();
mod->s1833( dr->s643(), s607[2] );
return s610;}
s1780::s1780( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1791, s736 ){
if( l.size() != 2 )
throw new s16( s1791 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1780::s1780( const s1780& right )
: s615( right ){}
void
s1780::s519( const s278* s1848, bool proc ){
s512 = s1286;
s615::s519( s1848, proc );}
s504 s1780::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
s278* dr = (s278*)s607[1];
s1778* ob = (s1778*)s607[2];
try {
dr->s1816( ob );}
catch( s16* e ) {
wstring s79 = L"in function " + s305() + L":\n";
s79 += L"during loading object: " + dr->s1849() +
L":" + dr->s368() + L":";
e->s30( s79 );
throw e;}
return s610;}
s1784::s1784( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1794, s736 ){
if( l.size() != 1 )
throw new s16( s1794 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1784::s1784( const s1784& right )
: s615( right ){}
void
s1784::s519( const s278* s1848, bool proc ){
s512 = s1286;
s615::s519( s1848, proc );}
s504 s1784::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
int dr = (int)*(s360*)s607[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s610;}
s1779::s1779( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1790, s736 ){
if( l.size() != 1 )
throw new s16( s1790 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1779::s1779( const s1779& right )
: s615( right ){}
void
s1779::s519( const s278* s1848, bool proc ){
s512 = s1288;
s615::s519( s1848, proc );}
s504 s1779::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
s501* dr = s607[1];
wstringstream buf;
dr->s310( &buf );
*s610.s15<s374*>()->s372() = buf.str();
return s610;}
s2064::s2064( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s2065, s736 ){
if( l.size() > 2 )
throw new s16( s2065 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s2064::s2064( const s2064& right )
: s615( right ){}
void
s2064::s519( const s278* s1848, bool proc ){
s512 = s1283;
s615::s519( s1848, proc );}
s504 s2064::s516( s501** s723, size_t s732 ){
s1787( s723, s732 );
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);
*s610.s15<s373*>()->s372() = dist( mt );
return s610;}
s277* s633::s349() const{
return new s633( *this );}
s277* s631::s349() const{
return new s631( *this );}
s277* s632::s349()const{
return new s632( *this );}
s277* s1578::s349()const{
return new s1578( *this );}
s277* s636::s349()const{
return new s636( *this );}
s277* s637::s349() const{
return new s637( *this );}
s277* s638::s349() const{
return new s638( *this );}
s277* s798::s349() const{
return new s798( *this );}
s277* s1856::s349() const{
return new s1856( *this );}
s277* s1857::s349() const{
return new s1857( *this );}
s277* s1785::s349() const{
return new s1785( *this );}
s277* s1783::s349() const{
return new s1783( *this );}
s277* s1780::s349() const{
return new s1780( *this );}
s277* s1784::s349() const{
return new s1784( *this );}
s277* s1779::s349() const{
return new s1779( *this );}
s277* s2064::s349() const{
return new s2064( *this );}
s635::s635( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s261, s736 ){
if( l.size() != 1 )
throw new s16( s261 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s635::s635( s268* s306 )
: s615( s306, NULL, NULL, s588, s261, NULL ){}
void s635::s519( const s278* s616, bool proc ){
s867::Cont s1433;
wstring ts = s1048::proto->s368() + L"<" + s375::proto->s368() +
L" " + s374::proto->s368() + L">";
s512 = s1048::proto.s15<s1048*>()->s1338( ts, s1433 );
s615::s519( s616, proc );}
s504 s635::s516( s501** s740, size_t s517 ){
s1048* s717 = s610.s15<s1048*>();
try {
s504 s156;
if( s280[0]->s513() == s492 )
s156 = s280[0].s15<s386*>()->s392();
else if( s280[0]->s513() == s493 )
s156 = s280[0].s15<s615*>()->s516( NULL, 0 );
else
s156 = s280[0].s15<s501*>();
wstring f = s156->s516( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s503> s998;
s1034 ast_ = new s269( f, s627()->Nqj() );
s508 cs = s615::s1235( *ast_, s306, s612, s304() );
s998.push_back( cs );
s506 s996 = s615::s624( cs, s306, s612, this, s304(), false );
s996->s519( s612, true );
s504 res1 = s996->s516( 0, 0 );
s717->s328().push_back( s384 );
s717->s328().push_back( new s374( s306, res1 ? res1->to_wstring() : L"" ) );}
else {
vector<wstring> l;
s504 res1 = s306->callFunc( f, l );
s717->s328().push_back( s384 );
s717->s328().push_back( new s374( s306, res1 ? res1->to_wstring() : L"" ) );}}
catch( s16* e ) {
s717->s328().push_back( s385 );
s717->s328().push_back( new s374(s306, e->Msg() ) );}
return s717;}
s277* s635::s349() const{
return new s635( *this );}
s268* s641::s992 = NULL;
s641::s641( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s267, s736 ){
if( l.size() != 1 )
throw new s16( s267 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s779->s366();}
s641::s641( s268* s306 )
: s615( s306, NULL, NULL, s588, s267, NULL ){
s512 = s779->s366();}
s504 s641::s516( s501** s740, size_t s517 ){
vector<wstring> s997;
for( size_t n = 0; n < s280.size(); ++n ) {
s997.push_back( s280[n]->s516( 0, 0 )->to_wstring() );}
if( !s992 ) {
s992 = new s268();
s992->s2079( true );}
else
s992->reset();
s992->s213( s997[0] );
s992->run( s997 );
return s380;}
s277* s641::s349()const{
return new s641( *this );}
s847::s847( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s817, s736 ){
if( l.size() != 1 )
throw new s16( s817 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s779->s366();}
s504 s847::s516( s501** s740, size_t s517 ){
wstring s198 = s280[0]->s516( s740, s517 )->to_wstring();
s306->s213( s198 );
return s380;}
s277* s847::s349()const{
return new s847( *this );}
s822::s822( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s877, s736 ){
s990 = s616->s304();
if( l.size() != 1 )
throw new s16( s877 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s779->s366();}
s504 s822::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s988;
if( par->s513() == s492 )
s988 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s988 = par->s516( 0, 0 )->to_wstring();
try {
s278* ob = ((s278*)s306->s670( s990, s990 ));
ob->s578( s988, s990 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s822::s349()const{
return new s822( *this );}
s1473::s1473( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s1483, s736 ){
if( l.size() != 1 )
throw new s16( s1483 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s779->s366();}
s504 s1473::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s702;
if( par->s513() == s492 )
s702 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s702 = par->s516( 0, 0 )->to_wstring();
try {
s306->s1519( s702 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s1473::s349()const{
return new s1473( *this );}
s1786::s1786( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s1796, s736 ){
if( l.size() != 1 )
throw new s16( s1796 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s779->s366();}
s504 s1786::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s702;
if( par->s513() == s492 )
s702 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s702 = par->s516( 0, 0 )->to_wstring();
try {
s306->s1841( s702 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s1786::s349()const{
return new s1786( *this );}
s1960::~s1960(){
release();}
void s1960::release(){
for( auto i : s944 )
i.second.clear();
s944.clear();}
s1961::s1961( s1960* s1985 ) 
: pdb( s1985 ), fi( s2026), se(s2026) {
ptr = new s1963();}
s1961::~s1961(){
if( ptr ) {
ptr->clear();
delete ptr;}}
const vector<wstring> s1957::s2058 = { L"", L"==", L"<", L">", L"<=", L">=" };
s1957::s1957( s268* s306, s278* s612, const std::wstring& s, size_t& pos ){
size_t s69 = s.find_first_not_of( s4::s49, pos );
size_t s70 = s69;
if( s[s69] == L'"' ) {
s4::s1098( s, s70, s4::s49 );
field = s.substr( s69+1, s70 - s69 - 2 );}
else {
s70 = s.find_first_of( s4::s49, s69 );
field = s.substr( s69, s70 - s69 );}
s70 = s69 = s.find_first_not_of( s4::s49, s70 );
s4::s1098( s, s70, s4::s49 );
wstring s2044 = s.substr( s69, s70 - s69 );
auto s2015  = std::find( s2058.begin(), s2058.end(), s2044 );
if( s2015 == s2058.end() )
throw new s16( L"unknown operation in query string: " + s2044 );
op = (s1957::s1970) std::distance( s2058.begin(), s2015 );
s70 = s69 = s.find_first_not_of( s4::s49, s70 );
s4::s1098( s, s70, s4::s49 + L")" );
wstring s2045 = s.substr( s69, s70 - s69 );
s1034 s736 = new s269( L"", s2045 );
par = s277::s524( *s736, s306, s612, s612->s304() );
pos = s70;}
void s1957::s519( s278* ns ){
if( par->s513() == s492 ) {
par->s519( ns );}}
void s1957::select( s1960* pdb, s1966& s156 ){
if( par->s513() == s492 )
s363 = par.s15<s386*>()->s392();
else
s363 = par;
pdb->select( field, op, s363.s15<s501*>(), s156 );}
s1958::s1958( s268* s306, s278* s612, const std::wstring& s, size_t& pos, s1959 s1982 )
: s1996( s1982 ){
size_t s69 = s.find_first_not_of( s4::s49, pos );
if( s[s69] == L'(' ) {
s1989( s306, s612, s, ++s69 );}
else
s1989( s306, s612, s, s69 );}
s1958::s1958( const s1958& r )
: s1996( r.s1996 ), subs( r.subs ), s1990( r.s1990 ){}
void s1958::s519( s278* ns ){
for( auto i : subs )
i.s519( ns );
for( auto i : s1990 )
i.s519( ns );}
void s1958::s1989( s268* s306, s278* s612, const std::wstring& s, size_t& pos ){
size_t s69 = s.find_first_not_of( s4::s49, pos );
while( s69 != string::npos ) {
if( s[s69] == L')' )
return;
else if( s[s69] == L'(' ) {
size_t s75, s76;
s4::s55( s, s69, L'(', L')', s75, s76 );
if( s76 == string::npos )
throw new s16( L"unmatched parentheses in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s69 = s.find_first_not_of( s4::s49, s75 + 1 );
subs.push_back( s1958( s306, s612, s, s69, s1992 ) );}
else if( s[s69] == L'A' || s[s69] == L'a' ) {
size_t pl = s.find_first_of( s4::s49, s69 );
wstring s2048 = s.substr( s69, pl - s69 );
if( s2048 != L"AND" && s2048 != L"and" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s69 += 3;
if( s1996 == s1992 )
s1996 = s1991;
else if( s1996 == s1991 )
(void)0;
else {
if( subs.empty() && s1990.empty() )
throw new s16( L"wrong query syntax: 'AND' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1958( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1990.clear();
s1996 = s1991;}}
else if( s[s69] == L'O' || s[s69] == L'o' ) {
size_t pl = s.find_first_of( s4::s49, s69 );
wstring s2048 = s.substr( s69, s.size() - pl + 1 );
if( s2048 != L"OR" && s2048 != L"or" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s69 += 2;
if( s1996 == s1992 )
s1996 = s1993;
else if( s1996 == s1993 )
(void)0;
else {
if( subs.empty() && s1990.empty() )
throw new s16( L"wrong query syntax: 'OR' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1958( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1990.clear();
s1996 = s1993;}}
else {
s1990.push_back( s1957( s306, s612, s, s69 ) );
if( s69 != string::npos )
++s69;}}}
bool s1981( s878 l, s878 r ){
return ( size_t )&( *l ) < ( size_t )&( *r );}
void s1958::select( s1960* pdb, s1961* s156 ){
s1968 s2009;
vector<s1963> s2041;
s1961 *s2056, *s2055;
for( size_t n = 0; n < s1990.size(); ++n ) {
s1966 s1178;
s1990[n].select( pdb, s1178 );
s2009.insert( s1178 );}
s2056 = pdb->s1997();
s2055 = pdb->s1997();
auto it = begin( s2009 );
if( s2009.size() ) {
if( s1996 == s1991 || s2009.size() == 1 ) {
pdb->intersect( *it, s156 );
s156->sort();}}
for( ++it; it != end( s2009 ); ++it ) {
s2056->clear();
if( s1996 == s1991 ) {
pdb->intersect( *it, s2056 );
s2056->sort();
if( s156->empty() )
s156->swap( s2056 );
else {
std::set_intersection( begin( s156->s328() ), end( s156->s328() ), 
begin( s2056->s328() ), end( s2056->s328() ), 
back_inserter( s2055->s328() ), s1981 );
s156->swap( s2055 );
s2055->clear();}}}
for( size_t n = 0; n < subs.size(); ++n ) {
subs[n].select( pdb, s2056 );
if( s1996 == s1991 ) {
s2056->sort();
if( s156->empty() )
s156->swap( s2056 );
else {
std::set_intersection( begin( s156->s328() ), end( s156->s328() ),
begin( s2056->s328() ), end( s2056->s328() ),
back_inserter( s2055->s328() ), s1981 );
s156->swap( s2055 );
s2055->clear();}}
s2056->clear();}}
vector<wstring> s1046( { L"select:", L":update", L"all", L"as:", L"where:",
L"satisfying:", L":distinct",	L"sortby:", L":asc", L":desc", L"limit:", L"set:" } );
struct s917{
size_t idx;
s917( size_t s942 ): idx( s942 ){}
bool operator()( const s504 l, const s504 r ) const{
s504 ld = l.s15<s792*>()[idx];
s504 rd = r.s15<s792*>()[idx];
return ld->operator<( (s501*)&(*rd) );}
};
void s840::s1901( const std::vector<s277*>& l_, TDException& s1059 ){
const size_t s1162 = 9;
std::vector<s277*> l( s1162, NULL );
s1890* sqr = new s1890;
s1889* sqp = new s1889;
sqr->verb = s784::s1955;
size_t s1082 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s513() == s1172 ) {
s386* rf = (s386*)l_[n];
if( rf->Id() == s1362 ) s1082 = 2;
else if( rf->Id() == s1361 ) {
s1082 = s1270;
l[1] = l_[n];}
else if( rf->Id() == s1383 ) s1082 = 3;
else if( rf->Id() == s2022 ) s1082 = 4;
else if( rf->Id() == s1367 ) {
s1082 = s1270;
sqr->distinct = 1;}
else if( rf->Id() == s1379 ) {
sqr->s972 = s1890::s904::s887;
s1082 = 6;}
else if( rf->Id() == s1363 ) {
if( s1082 != 7 )
throw s1059.s1097( L"the '" + rf->s643() + L"' specifier is misplaced" );
s1082 = s1270;
sqr->s972 = s1890::s904::s887;}
else if( rf->Id() == s1366 ) {
if( s1082 != 7 )
throw s1059.s1097( L"the '" + rf->s643() + L"' specifier is misplaced" );
s1082 = s1270;
sqr->s972 = s1890::s904::s894;}
else if( rf->Id() == s1377 ) 
s1082 = 8;
else
throw s1059.s1097( L"misplaced query keyword: " + s1046[rf->Id()] );}
else
l[s1082++] = l_[n];}
s861 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1181 = l[2];
sqp->where = l[3];
sqp->s2046 = l[4];
sqp->s974 = l[6];
sqp->s951 = l[8];
if( sqp->s1181.s13() )
throw s1059.s1097( L"the 'as' clause is missing" );}
void s840::s1902( const std::vector<s277*>& l_, TDException& s1059 ){
const size_t s1162 = 3;
std::vector<s277*> l( s1162 );
s1900* sqr = new s1900;
s1899* sqp = new s1899;
sqr->verb = s784::s1956;
size_t s1082 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s513() == s1172 ) {
s386* rf = (s386*)l_[n];
if( rf->Id() == s1932 ) s1082 = 1;
else if( rf->Id() == s2022 ) s1082 = 2;
else
throw s1059.s1097( L"misplaced query keyword: " + s1046[rf->Id()] );}
else
l[s1082++] = l_[n];}
s861 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s2046 = l[2];
if( sqp->what.s13() || sqp->s2046.s13() )
throw s1059.s1097( L"the 'UPDATE' query must include 'SET' and `SATISFYING` clauses" );}
s840::s840( s268* s306, s278* s616, s615* s617, 
const std::vector<s277*>& l_, const s269* s736 )
: s615( s306, s616, s617, s588, s873, s736 ),
s772( s7::s477, s306 ), s831( new s278( s306, 0, s498 ) ),
s2038( NULL ){
TDException s1059( s7::s1226, s1018, s736 );
if( l_.size() < 3 )
throw s1059.s1097( L"too few arguments." );
s615::s1392( ( vector<s277*>& )l_, s1046 );
s655.s564( s772.s643(), s831.s15<s501*>() );
s606.push_back( s831.s15<s501*>() );
s280.push_back( s831.s15<s501*>() );
s657.push_back( s831.s15<s501*>() );
s658.push_back( s386( s772.s643(), s306) );
s503 p = l_[0];
if( p->s513() != s492 && p->s513() != s493 )
throw s1059.s1097( L"the database object must be specified by a name or expression." );
if( l_[1]->s513() != s1172 )
throw s1059.s1097( L"the second participant must be a query verb: SELECT, UPDATE, etc." );
s386* rf = (s386*)l_[1];
if( rf->Id() == s1378 )
s1901( l_, s1059 );
else if( rf->Id() == s1934 )
s1902( l_, s1059 );}
s840::~s840(){
if( s2038 )
delete s2038;}
s502* s840::s1984( const std::wstring& s ){
size_t pos = 0;
s2038 = new s1958( s306, this, s, pos, s1958::s1992 );
return NULL;}
void s840::s1903( const s278* s1848, bool proc ){
s1889* sqp = qp.s15<s1889*>();
sqp->s1181->s519( this );
s867::Cont s1433;
wstring sv = sqp->s1181->s368();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = s323::proto->s368() + L"<" + sv + L">";
s512 = s323::proto.s15<s323*>()->s1338( ts, s1433 );
TDException s1059( s7::s1006, s1018, past );
s615::s519( s1848, proc );
s489 pc = db->s513();
if( pc == s495 ) {
db = s624( db.s15<s584*>(), s306, s612, this, s304(), false );
db->s519( this );}
else if( pc == s492 )
db.s15<s386*>()->s519( this );
else
throw s1059.s1097( L"the database must be specified by a name or expression." );
pc = sqp->what->s513();
if( pc == s495 ) {
sqp->what = s624( sqp->what.s15<s584*>(), s306, s612, this, s304(), false );
sqp->what->s519( this );}
else if( pc == s492 )
sqp->what.s15<s386*>()->s519( this );
else if( pc == s491 || pc == s1172 )
(void)0;
else
throw s1059.s1097( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s366() != s1288 )
throw s1059.s1097( L"the 'WHERE' clause must be a string." );
sqp->where = s1984( sqp->where->to_wstring() );}
else {
std::vector<s277*> s961;
s961.push_back( s384 );
sqp->where = ( s502* ) new s905( s306, 0, 0, s961, NULL );
sqp->where.s15<Transd*>()->s519( s1848, false );}
if( sqp->s2046 ) {
pc = sqp->s2046->s513();
if( pc == s495 ) {
sqp->s2046 = s624( sqp->s2046.s15<s584*>(), s306, s612, this, s304(), false );
sqp->s2046.s15<Transd*>()->s519( s1848, false );
s899 s963;
sqp->s2046.s15<Transd*>()->s868( s963 );}
else
throw s1059.s1097( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s951.s14() ) {
pc = sqp->s951->s513();
if( pc == s495 ) {
sqp->s951 = s624( sqp->s951.s15<s584*>(), s306, s612, this, s304(), false );
sqp->s951->s519( this );}
else if( pc == s492 )
sqp->s951.s15<s386*>()->s519( this );
else if( sqp->s951->s366() != s1284 )
throw s1059.s1097( L"the limit must be specified by a number, variable or expression." );}}
void s840::s1904( const s278* s1848, bool proc ){
s1899* sqp = qp.s15<s1899*>();
s512 = s1284;
TDException s1059( s7::s1006, s1018, past );
s615::s519( s1848, proc );
s489 pc = db->s513();
if( pc == s495 ) {
db = s624( db.s15<s584*>(), s306, s612, this, s304(), false );
db->s519( this );}
else if( pc == s492 )
db.s15<s386*>()->s519( this );
else
throw s1059.s1097( L"the database must be specified by a name or expression." );
pc = sqp->what->s513();
if( pc == s495 ) {
sqp->what = s624( sqp->what.s15<s584*>(), s306, s612, this, s304(), false );
sqp->what.s15<Transd*>()->s519( s1848, false );}
else
throw s1059.s1097( L"the 'SET' clause must be a lambda" );
pc = sqp->s2046->s513();
if( pc == s495 ) {
sqp->s2046 = s624( sqp->s2046.s15<s584*>(), s306, s612, this, s304(), false );
sqp->s2046.s15<Transd*>()->s519( s1848, false );}
else
throw s1059.s1097( L"the 'SATISFYING' clause must be a lambda." );}
void
s840::s519( const s278* s1848, bool proc ){
if( s861->verb == s784::s1955 )
s1903( s1848, proc );
else if( s861->verb == s784::s1956 )
s1904( s1848, proc );}
s504 s840::s1909( s501** s280, size_t s517 ){
s1899* sqp = qp.s15<s1899*>();
s504 s717 = s610;
vector<wstring> s980;
vector<wstring> s981;
s1960* base;
TDException s1059( s7::s1007, s1015, past );
assert( db->s513() == s492 );
base = ( (s1960*)db.s15<s386*>()->s392() );
s1968 s2009;
s899 s963;
sqp->s2046.s15<Transd*>()->s868( s963 );
for( size_t n = 0; n < s963.size(); ++n ) {
s981.push_back( s963[n].first );
s1966 s1178;
base->select( s981.back(), s1957::s2035, s504(), s1178 );
s2009.insert( s1178 );}
s1961 *s2056, *s2055;
s1::s1444<s1961> dom = base->s1997();
s2056 = base->s1997();
s2055 = base->s1997();
auto it = begin( s2009 );
if( s2009.size() == 1 ) {
base->intersect( *it, dom );
dom->sort();}
for( ++it; it != end( s2009 ); ++it ) {
s2056->clear();
base->intersect( *it, s2056 );
s2056->sort();
if( dom->empty() )
dom->swap( s2056 );
else {
std::set_intersection( begin( dom->s328() ), end( dom->s328() ),
begin( s2056->s328() ), end( s2056->s328() ),
back_inserter( s2055->s328() ), s1981 );
dom->swap( s2055 );
s2055->clear();}}
s963.clear();
sqp->what.s15<Transd*>()->s868( s963 );
for( size_t n = 0; n < s963.size(); ++n ) {
s980.push_back( s963[n].first );}
vector<s503> s962, pls1;
s962.resize( s981.size() );
pls1.resize( s980.size() );
int s716 = 0;
dom->s2053();
while( dom->s2014() ) {
s1962* s2036 = dom->s2024();
for( size_t n = 0; n < s981.size(); ++n )
s962[n] = s2036->s804( s981[n] ).s15<s502*>();
sqp->s2046.s15<Transd*>()->s620( s962 );
s504 s156 = sqp->s2046->s516( 0, 0 );
if( s156.s14() && (bool)*s156 ) {
for( size_t n = 0; n < s980.size(); ++n )
pls1[n] = s2036->s804( s980[n] ).s15<s502*>();
sqp->what.s15<Transd*>()->s620( pls1 );
s504 s156 = sqp->what->s516( 0, 0 );
++s716;}}
*s610.s15<s360*>()->s372() = s716;
return s610;}
s504 s840::s1908( s501** s280, size_t s517 ){
s1889* sqp = qp.s15<s1889*>();
s1890* sqr = s861.s15<s1890*>();
s504 s717 = s610;
vector<wstring> s980;
vector<wstring> s2047;
s1960* base;
size_t s994 = string::npos;
TDException s1059( s7::s1007, s1015, past );
assert( db->s513() == s492 );
base = ( (s1960*)db.s15<s386*>()->s392() );
if( sqp->s951.s14() ) {
if( sqp->s951->s513() == s492 ) {
sqr->s951 = ( int )*( (s360*)sqp->s951.s15<s386*>()->s392() );}
else if( sqp->s951->s513() == s493 ) {
sqr->s951 = (int)*sqp->s951->s516( 0, 0 );}
else
sqr->s951 = (int)*sqp->s951;}
if( sqp->s974.s14() ) {
if( sqp->s974->s513() == s492 ) {
sqr->s971 = sqp->s974.s15<s386*>()->s392()->to_wstring();}
else if( sqp->s974->s513() == s493 ) {
sqr->s971 = sqp->s974->s516( 0, 0 )->to_wstring();}
else
sqr->s971 = sqp->s974->to_wstring();}
s1965::iterator s2016, s2017;
s489 pc = sqp->what->s513();
s504 s1942 = sqp->what.s15<s501*>();
if( pc == s492 ) {
s507 rf = sqp->what.s15<s386*>();
s1942 = rf->s392();}
else if( pc == s1172 ) {
s507 rf = sqp->what.s15<s386*>();
if( rf->s643() == L"all" || rf->s643() == L"ALL" )
(void)0;
else
throw s1059.s1097( L"fields for selection are not recognized" );}
else if( pc == s491 ) {
(void)0;}
s867 vt = s306->TR().s1112( s1942->s366() );
if( vt.s366() == s1897 || vt.s366() == s1896 ) {
const vector<s503>* v = NULL;
if( vt.s366() == s1897 )
v = &s1942.s15<s323*>()->s328();
else
v = &s1942.s15<s792*>()->s328();
for( auto it : *v ) {
wstring s929 = it->to_wstring();
size_t s964 = s4::s89.find( s929[0] );
if( s964 != string::npos )
s929 = s4::s53( s929, wstring( 1, s4::s89[s964] ) );
s980.push_back( s929 );}}
s1::s1444<s1961> dom = base->s1997();
if( s2038 ) {
s2038->select( base, dom );}
else
base->s2049( dom );
s899 s963;
if( sqp->s2046.s14() ) {
sqp->s2046.s15<Transd*>()->s868( s963 );
if( s963.empty() )
throw s1059.s1097( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s963.size(); ++n ) {
s2047.push_back( s963[n].first );
while( s2016 != s2017 ) {
++s2016;}}}
vector<s503> s962;
s962.resize( s2047.size() );
s610.s15<s323*>()->clear();
dom->s2053();
while( dom->s2014() ) {
s1962* s2036 = dom->s2024();
s504 s1987;
if( sqp->s2046.s14() ) {
for( size_t n = 0; n < s2047.size(); ++n )
s962[n] = s2036->s804( s2047[n] ).s15<s502*>();
sqp->s2046.s15<Transd*>()->s620( s962 );
s1987 = sqp->s2046->s516( 0, 0 );}
else
s1987 = s384.s15<s501*>();
if( s1987.s14() && (bool)*s1987 ) {
s1::s9<s792> s979 = new s792( s306, NULL, L"" );
if( s980.empty() )
s2036->s936( *s979 );
else {
for( size_t n = 0; n < s980.size(); ++n )
s979->add( s2036->s804( s980[n] ).s15<s502*>() );}
s979->s1855( s7::s940 );
s610.s15<s323*>()->add( s979 );}}
if( sqr->distinct != -1 ) {
vector<s503>& s985 = s610.s15<s323*>()->s328();
for( size_t n = 0; n < s985.size(); ++n ) {
s503 s984 = s985[n];
size_t m = n + 1;
while( m < s985.size() ) {
s503 _el1 = s985[m];
if( *s984.s15<s792*>() == _el1.s15<s501*>() )
s985.erase( s985.begin() + m );
else
m++;}}}
if( sqr->s972 != -1 ) {
if( s980.size() && sqr->s971.size() ) {
auto it = std::find( s980.begin(), s980.end(), sqr->s971 );
if( it != s980.end() )
s994 = std::distance( s980.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s989;
dom->s2010( s989 );
auto it = std::find( s989.begin(), s989.end(), sqr->s971 );
if( it != s989.end() )
s994 = std::distance( s989.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s983> s987 = new s983;
s987->s993( s994 );
s908 s995( s987 );
s610.s15<s323*>()->sort( sqr->s972 == s1890::s894, &s995 );}
if( sqr->s951 != -1 ) {
s610.s15<s323*>()->s328().resize( sqr->s951 );}
return s717;}
s504 s840::s516( s501** s723, size_t s732 ){
if( s861->verb == s784::s1955 )
return s1908( s723, s732 );
else if( s861->verb == s784::s1956 )
return s1909( s723, s732 );
return NULL;}
s277* s840::s349()const{
return new s840( *this );}
s824::s824( s268* pass_, s278* s612, const wstring& s813, 
const vector<wstring>& s783, std::vector<s503>& types, const s1898& tbfr ){
s792 s829( pass_, s612, s813, NULL, tbfr );
s829.s519( s612, true );
vector<s503> s876 = s829.s328();
if( s876.size() > types.size() )
throw new s16( L"The number of record's fields is greater than the number of columns: " + s813 );
for( size_t n = 0; n < s783.size(); ++n ) {
s503 s862;
if( n < s876.size() ) {
if( !s876[n]->s521( types[n].s15< s501*>() ) ) {
if( tbfr.promInts && types[n]->s366() == s1283 && s876[n]->s366() == s1284 )
s876[n] = new s373( pass_, (double)*s876[n].s15<s360*>()->s372() );
else
throw new s16( L"The types of record's fields don't match to the types of columns: " + s813 );}
s862 = s876[n];}
else {
s862 = types[n].s15<s502*>()->s349();
s862->to_null();}
s807.insert( make_pair( s783[n], s862 ) );
size_t h = s862.s15<s501*>()->s330();
rechash = ( rechash << 1 ) ^ h;}}
size_t s824::s330() const{
return rechash;}
s504 s824::s804( const std::wstring& s77, bool s749 ) const{
auto it = s807.find( s77 );
if( it == s807.end() ) {
if( s749 )
throw new s16( L"Record field doesn't exist: " + s77, 
(uint32_t)s16::s17::s23 );
else
return s504();}
return it->second.s15<s501*>();}
void s824::s936( s792& s156 ) const{
for( auto r: s807 )
s156.add( r.second );}
void s824::s568( std::vector<std::wstring>& s156 ) const{
for( auto r: s807 )
s156.push_back( r.first );}
bool s824::operator==( const s824* p ) const{
return rechash == p->rechash;}
bool s824::operator<( const s824* p ) const{
return rechash < p->rechash;}
wstring s824::to_wstring( uint32_t s1739 ) const{
wstringstream ss;
s310( &ss, 0 );
return ss.str();}
void s824::s310( std::wostream* pd, int s201/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"TSDRecord : " << endl;
for( auto it = begin( s807 ); it != end( s807 ); ++it ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << it->first << L":" << endl;
it->second->s310( pd, s201 + s434 );}}
s866::s866( vector<wstring>& s771, s878 rec ){
for( size_t n = 0; n < s771.size(); ++n ) {
s503 f = rec->s804( s771[n] ).s15<s502*>();
s862.push_back( f );}
for( size_t n = 0; n < s771.size(); ++n ) {
size_t h = s862[n].s15<s501*>()->s330();
s850 = ( s850 << 1 ) ^ h;}}
size_t s866::s330() const{
return s850;}
bool s866::operator==( const s866* p ) const{
return s850 == p->s850;}
bool s866::operator<( const s866* p ) const{
return s850 < p->s850;}
void s866::s310( std::wostream* pd, int s201/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s862.size(); ++n ) {
s862[n]->s310( pd, s201 + s434 );}}
s1975::s1975( s1960* pdb )
: s1961( pdb ), pind(NULL)//, fi1(s2027), se1(s2027)
{}
void s1975::s2050( void* f, void* s ){
pind = (s836*)f;}
void s1975::s2053(){
if( pind )
cur1 = pind->begin();
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1975::s2014(){
if( pind )
return cur1 != pind->end();
else
return cur != se;}
s1962* s1975::s2024(){
if( s2014() ) {
s1962* s717;
if( pind ) {
s717 = cur1->second;
cur1++;}
else {
s717 = *cur;
cur++;}
return s717;}
else
throw new s16( L"TSDBase row iterator is out of range" );}
s679::s679( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1960( s306, s612, ast_ ){
s518 = s78;
s512 = s679::proto.s13() ? 0 : s679::proto->s366();}
s679::s679( const s679& right, const s269* ast_ )
: s1960( right.s306, right.ns, ast_ ){
s512 = right.s512;}
s501* s679::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return new s679( s306, s612, L"" );}
void s679::s519( const s278*, bool ){
s1413();}
void s679::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s679::s1384, s1977,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"add-file", new s351( L"add-file", &s679::s835, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"load-table", new s351( L"load-table", &s679::s852, s1286,
{ s1238( { s1288, s1288 } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s362.insert( make_pair( L"select", new s351( L"select", &s679::s795, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"query", new s351( L"query", &s679::s815, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s679::s344, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s679::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"build-index", new s351( L"build-index", &s679::s927, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );}
s501* s679::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s679( s306, s612, L"" );}
inline bool
s679::s521( const s501* s522 ) const{
return ( ((s679*)s522)->s366() == s366() );}
s277* s679::s349() const{
return new s679( *this );}
void s679::s371( s277* p ) const{
p = new s679( *this );}
size_t s679::s330() const{
return (size_t)this;}
bool s679::operator==( const s501* p ) const{
return ( this == p );}
bool s679::operator<( const s501* p ) const{
return false;}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s679*)(s502*)*s280)
inline void s679::s1384( s501** s280, size_t s517 ){
s679* ps = (s679*)DR;
s679* s717 = new s679( ps->s306, ps->ns, ps->s627() );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s679::s835( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s683( s198 );}
inline void s679::s852( s501** s280, size_t s517 ){
s679* dr = ( (s679*)DR );
const wstring& s880 = PARN( 2 )->to_wstring();
s1898 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s517 ) {
s503 par_ = s280[n];
s489 pc = par_->s513();
if( pc == s1172 ) {
s503 par;
s507 rf;
rf = par_.s15<s386*>();
par = par_;
if( par->s366() == s827->s366() ) {
if( rf->Id() == s1931 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1929 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1927 ) {
if( s517 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1912 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1928 ) {
tbfr.s1875 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2021 ) {
tbfr.s2005 = true;}
else if( rf->Id() == s1930 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"TSDBase::(load-table): unknown parameters" );
++n;}
dr->s753( s880, tbfr );}
inline void s679::s795( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s684( s198 );}
inline void s679::s815( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s684( s198 );}
inline void s679::s344( s501** s280, size_t s517 ){}
inline void s679::s339( s501** s280, size_t s517 ){}
inline void s679::s342( s501** s280, size_t s517 ){}
inline void s679::s927( s501** s280, size_t s517 ){
wstring s929 = PARN( 2 )->to_wstring();
((s679*)DR)->s926( s929 );}
void s679::s683( const wstring& s198 ){
vector<s9<s146>> s692;
s1032 s1158( s198 );
s1158.read( s692, s7::s1222 );
for( size_t m = 0; m < s692.size(); m++ ) {
s146* obj = s692[m];
wstring s687 = s4::s53( s269::s308( *obj, s7::s480 ), 
s49 );
if( s687.empty() )
throw new s16( L"Nameless blocks are forbidden." );
vector<pair<wstring, s145>> s147;
obj->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
if( s147[n].second->s167() != s137 && s147[n].second->s167() != s142 )
throw new s16( L"unrecognized format of field " + s687 +L"::"+s147[n].first );
wstring sobj = s147[n].second->s172();
wstring srel = s147[n].first;
s680.insert( make_pair( s687, make_pair( srel, sobj ) ) );
s681.insert( make_pair( srel, make_pair( s687, sobj ) ) );
s682.insert( make_pair( sobj, make_pair( s687, srel ) ) );}}}
void s679::s684( const std::wstring& q ){
vector<wstring> qs;
s4::s58( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s680.begin(); it != s680.end(); ++it )
wcout << it->first;}}
void s679::select( const std::wstring& field, s1957::s1970 op, const s501* s1174,
s1966& s156 ){
auto it = s944.find( field );
if( it == s944.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1957::s2030 ) {
s156.pr = it->second.equal_range( (s501*)s1174 );}
else if( op == s1957::s2033 ) {
s156.pr.first = it->second.begin();
s156.pr.second = it->second.lower_bound( (s501*)s1174 );}
else if( op == s1957::s2034 ) {
s156.pr.first = it->second.begin();
s156.pr.second = it->second.upper_bound( (s501*)s1174 );}
else if( op == s1957::s2031 ) {
s156.pr.first = it->second.upper_bound( (s501*)s1174 );
s156.pr.second = it->second.end();}
else if( op == s1957::s2034 ) {
s156.pr.first = it->second.lower_bound( (s501*)s1174 );
s156.pr.second = it->second.end();}
else {
s156.pr.first = it->second.begin();
s156.pr.second = it->second.end();}}
s1961* s679::s1997() const{
return new s1975( (s1960*)this );}
void s679::s2049( s1961* s156 ){
s156->s2050( (void*)&s800, (void*)NULL );}
void s679::intersect( const s1966& fi1, const s1966& fi2,
s1963& s156 ){
s1965::iterator it = fi1.pr.first;
wstring attr2 = fi2.s1071;
s1964 s1994;
while( it != fi1.pr.second ) {
s504 attr2v = it->second->s804( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1994 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1994 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s156.push_back( it->second );
++lb2;}}
++it;}}
void s679::intersect( const s1966& fi, s1961* s156 ){
s1965::iterator it = fi.pr.first;
s1963 s2056;
s1963& s2039 = ((s1975*)s156)->s328();
bool s2003 = s2039.empty();
while( it != fi.pr.second ) {
if( s2003 || std::binary_search( begin( s2039 ), end( s2039 ), it->second, s1981 ) )
s2056.push_back( it->second );
++it;}
s2039.swap( s2056 );}
void s679::s753( const wstring& s880, const s1898& tbfr ){
wstring s783 = tbfr.s1912;
vector<wstring> s870;
vector<wstring> s770;
vector<wstring> s855;
vector<wstring> s881;
if( s783.size() ) {
s4::s58( s783, tbfr.s1875, s870 );
s4::s58( s4::s53( s880, s49 ), tbfr.rowSep, s855 );}
else {
s783 = s880.substr( 0, s880.find( tbfr.rowSep ) );
s4::s58( s4::s53( s880.substr( s783.size() ), s49 ), tbfr.rowSep, s855 );
if( s783.back() == '\r' )
s783.pop_back();
s4::s58( s783, tbfr.s1875, s870 );}
vector<s503> types, s1951;
if( !s855.empty() ) {
s792 s829( s306, ns, s855[0], NULL, tbfr );
s829.s519( ns, true );
s1951 = s829.s328();}
for( size_t n = 0; n < s870.size(); ++n ) {
vector<wstring> s1911;
s4::s58( s870[n], L":", s1911 );
s1034 s1950;
if( s1911.size() == 2 )
s1950 = new s269( s1911[1] + L"()", NULL );
else if( n < s1951.size() )
s1950 = new s269( s1951[n]->s368() + L"()", NULL );
else
s1950 = new s269( s374::proto->s368() + L"()", NULL );
s503 ptype = s306->TR().s541( *s1950, ns, ns->s304() );
types.push_back( ptype );
if( s1911[0][0] != L'@' )
s770.push_back( s1911[0] );
else {
size_t pl = s1911[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1911[0] );
wstring s77 = s1911[0].substr( pl + 1 );
s770.push_back( s77 );
s881.push_back( s77 );}}
if( !s881.empty() ) {
s800.rehash( (size_t) ( s855.size() * 1.1 ) );
for( auto row : s855 ) {
s878 rec = new s824( s306, ns, row, s770, types, tbfr );
s773 s155 = new s866( s881, rec );
s800.insert( make_pair( s155, rec ) );}}}
void s679::s926( const wstring& s929 ){
auto it = s944.find( s929 );
if( it != end( s944 ) )
s944.erase( it );
s1965& s943 = s944.insert( make_pair( s929, s1965() ) ).first->second;
for( auto it: s800 ) {
s504 pd = it.second->s804( s929 );
if( pd.s14() )
s943.insert( make_pair( pd, it.second ) );}}
wstring s679::to_wstring( uint32_t s1739 ) const{
basic_stringstream<wchar_t> ss;
s310( &ss, 0 );
return ss.str();}
void s679::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"TSDBase : " << endl;
for( auto it = begin( s800 ); it != end( s800 ); ++it ) {
it->first->s310( pd, s201 + s434 );
it->second.s15<s824*>()->s310( pd, s201 + s434 );}}
s1963 s2025 = { new s1979( vector<s504>( {s504()} ), NULL ) };
s1963::iterator s2026 = s2025.begin();
s1979::s1979( const std::vector<s504>& v, s1980* s1986 )
: s2040( v ), s2037( s1986 ){}
s1979::~s1979(){
s2040.clear();}
s504 s1979::s804( const std::wstring& s77, bool s749 ) const{
return s2040[s2037->s2012( s77 )];}
void s1979::s936( s792& s156 ) const{
for( auto r : s2040 )
s156.add( r );}
void s1979::s568( std::vector<std::wstring>& s156 ) const{
assert( 0 );}
size_t s1979::s330() const{
return rechash;}
s1978::s1978( const s1978& r )
: s1961( r.pdb ){}
s1978::s1978( s1960* pdb )
: s1961( pdb ){}
s1978::~s1978(){}
void s1978::s2050( void* f, void* s ){
fi = *( s1963::iterator* )f;
se = *( s1963::iterator* )s;}
void s1978::s2053(){
if( *fi != *s2026 )
cur = fi;
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1978::s2014(){
return (cur != se);}
s1962* s1978::s2024(){
if( s2014() ) {
s1962* s717 = *cur;
cur++;
return s717;}
else
throw new s16( L"Table row iterator is out of range" );}
void s1978::s2010( std::vector<std::wstring>& s156 ){
((s1980*)pdb)->s2011( s156 );}
s1980::s1980( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1960( s306, s612, ast_ ){
s518 = s78;
s512 = s1980::proto.s13() ? 0 : s1980::proto->s366();}
s1980::s1980( const s1980& right, const s269* ast_ )
: s1960( right.s306, right.ns, ast_ ){
s512 = right.s512;}
s1980::~s1980(){
release();}
s501* s1980::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return new s1980( s306, s612, &s736 );}
void s1980::s519( const s278*, bool ){
s1413();}
void s1980::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s1980::s1384, s1976,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"load-table", new s351( L"load-table", &s1980::s852, s1286,
{ s1238( { s1288, s1288 } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s362.insert( make_pair( L"select", new s351( L"select", &s1980::s795, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"query", new s351( L"query", &s1980::s815, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s1980::s344, s1286,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1980::s339, s1284,
{ s1238() }, 0, 0 ) ) );
s362.insert( make_pair( L"build-index", new s351( L"build-index", &s1980::s927, s1286,
{ s1238( { s1288 } ) }, 1, 1 ) ) );}
s501* s1980::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1980( s306, s612, L"" );}
inline bool
s1980::s521( const s501* s522 ) const{
return ( ((s1980*)s522)->s366() == s366() );}
s277* s1980::s349() const{
return new s1980( *this );}
void s1980::s371( s277* p ) const{
p = new s1980( *this );}
size_t s1980::s330() const{
return (size_t)this;}
bool s1980::operator==( const s501* p ) const{
return ( this == p );}
bool s1980::operator<( const s501* p ) const{
return false;}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s1980*)(s502*)*s280)
inline void s1980::s1384( s501** s280, size_t s517 ){
s1980* ps = (s1980*)DR;
s1980* s717 = new s1980( ps->s306, ps->ns, ps->s627() );
s717->s519( ps->ns, true );
*s280 = (s501*)s717;}
inline void s1980::s852( s501** s280, size_t s517 ){
s1980* dr = ( (s1980*)DR );
const wstring& s880 = ((s374*)PARN( 2 ))->s328();
s1898 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s517 ) {
s503 par_ = s280[n];
s489 pc = par_->s513();
if( pc == s1172 ) {
s503 par;
s507 rf;
rf = par_.s15<s386*>();
par = par_;
if( par->s366() == s827->s366() ) {
if( rf->Id() == s1931 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1929 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1927 ) {
if( s517 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1912 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1928 ) {
tbfr.s1875 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2021 ) {
tbfr.s2005 = true;}
else if( rf->Id() == s1930 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Table::(load-table): unknown parameters" );
++n;}
dr->s753( s880, tbfr );}
inline void s1980::s795( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s1980*)DR )->s684( s198 );}
inline void s1980::s815( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s1980*)DR )->s684( s198 );}
inline void s1980::s344( s501** s280, size_t s517 ){}
inline void s1980::s339( s501** s280, size_t s517 ){}
inline void s1980::s927( s501** s280, size_t s517 ){
wstring s929 = PARN( 2 )->to_wstring();
((s1980*)DR)->s926( s929 );}
void s1980::select( const std::wstring& field, s1957::s1970 op, const s501* s1174,
s1966& s156 ){
auto it = s944.find( field );
if( it == s944.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1957::s2030 ) {
s156.pr = it->second.equal_range( (s501*)s1174 );}
else if( op == s1957::s2033 ) {
s156.pr.first = it->second.begin();
s156.pr.second = it->second.lower_bound( (s501*)s1174 );}
else if( op == s1957::s2034 ) {
s156.pr.first = it->second.begin();
s156.pr.second = it->second.upper_bound( (s501*)s1174 );}
else if( op == s1957::s2031 ) {
s156.pr.first = it->second.upper_bound( (s501*)s1174 );
s156.pr.second = it->second.end();}
else if( op == s1957::s2034 ) {
s156.pr.first = it->second.lower_bound( (s501*)s1174 );
s156.pr.second = it->second.end();}
else {
assert( 0 );
s156.pr.first = it->second.begin();
s156.pr.second = it->second.end();}
s156.s1071 = field;
s156.dist = std::distance( s156.pr.first, s156.pr.second );}
void s1980::intersect( const s1966& fi1, const s1966& fi2,
s1963& s156 ){
s1965::iterator it = fi1.pr.first;
wstring attr2 = fi2.s1071;
s1964 s1994;
while( it != fi1.pr.second ) {
s504 attr2v = it->second->s804( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1994 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1994 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s156.push_back( it->second );
++lb2;}}
++it;}}
void s1980::intersect( const s1966& fi, s1961* s156 ){
s1965::iterator it = fi.pr.first;
s1963 s2056;
s1963& s2039 = ((s1978*)s156)->s328();
bool s2003 = s2039.empty();
while( it != fi.pr.second ) {
if( s2003 || std::binary_search( begin( s2039 ), end( s2039 ), it->second, s1981 ) )
s2056.push_back( it->second );
++it;}
s2039.swap( s2056 );}
void s1980::s2049( s1961* s156 ){
s1963::iterator f = begin( rows );
s1963::iterator s = end( rows );
s156->s2050( (void*)&f, (void*)&s );}
void s1980::s753( const wstring& s880, const s1898& tbfr ){
wstring s783 = tbfr.s1912;
vector<wstring> s870;
vector<wstring> s881;
size_t pl = -1;
if( s783.size() ) {
s4::s58( s783, tbfr.s1875, s870 );}
else {
pl = s880.find( tbfr.rowSep );
s783 = s880.substr( 0, pl );
if( s783.back() == '\r' )
s783.pop_back();
s4::s58( s783, tbfr.s1875, s870 );}
vector<s504> types;
vector<s503> s1951;
if( 1 /*|| !s855.empty()*/ ) {
++pl;
wstring first = s880.substr( pl, s880.find( tbfr.rowSep, pl ) - pl );
s792 s829( s306, ns, first, NULL, tbfr );
s829.s519( ns, true );
s1951 = s829.s328();}
for( size_t n = 0; n < s870.size(); ++n ) {
vector<wstring> s1911;
s4::s58( s870[n], L":", s1911 );
s1034 s1950;
s504 ptype;
if( s1911.size() == 2 )
s1950 = new s269( s1911[1] + L"()", NULL );
else
s1950 = new s269( s374::proto->s368() + L"()", NULL );
ptype = s306->TR().s541( *s1950, ns, ns->s304() );
types.push_back( ptype );
if( s1911[0][0] != L'@' )
s856.push_back( s1911[0] );
else {
size_t pl = s1911[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1911[0] );
wstring s77 = s1911[0].substr( pl + 1 );
s856.push_back( s77 );}
s2013[s856.back()] = s856.size() - 1;}
using namespace chrono;
size_t s1998 = pl, /*s70,*/ s2043, s1999, s2006;
vector<s504> s2008( types.size() );
s1034 s212 = new s269( L"", L"" );
while( s1998 != string::npos ) {
s2043 = s1998;
s4::s1098( s880, s2043, tbfr.rowSep );
wstring s2001 = s880.substr( s1998, s2043 - s1998 );
s2006 = s1999 = 0;
for( size_t n = 0; n < types.size(); ++n ) {
s2006 = s1999;
s4::s1098( s2001, s2006, tbfr.s1875 );
if( types[n].s14() ) {
s212->s300( L"" );
s212->s1947( s2001.substr( s1999, s2006 - s1999 ) );
if( types[n]->s366() == s1288 && ( s212->s297().front() != L'"' ||
s212->s297().back() != L'"' ) ) {
wstring dqu = L"\"\"";
s212->s1947( dqu.insert( 1, s4::s2007(  s4::s53( s212->s297(), s4::s49 ) , L'"' )));}
s2008[n] = types[n]->s369( *s212, ns, ns->s304() );}
else {
s2008[n] = s380.s15<s501*>();}
s1999 = s2006 + 1;
if( s2006 == string::npos )
break;}
s1998 = s2043 + 1;
s1962* s1988 = new s1979( s2008, this );
rows.push_back( s1988 );
if( s2043 == string::npos || s1998 == s880.size() )
break;}}
void s1980::s926( const wstring& s929 ){
auto it = s944.find( s929 );
if( it != end( s944 ) )
s944.erase( it );
s1965& s943 = s944.insert( make_pair( s929, s1965() ) ).first->second;
for( auto it: rows ) {
s504 pd = it->s804( s929 );
if( pd.s14() )
s943.insert( make_pair( pd, it ) );}}
void s1980::release(){
s1960::release();
rows.clear();}
s1961* s1980::s1997() const{
return new s1978( (s1960*)this );}
size_t s1980::s2012( const std::wstring& s1995 ) const{
auto s717 = s2013.find( s1995 );
if( s717 == s2013.end() )
throw new s16( L"table field does not exist: " + s1995 );
return s717->second;}
wstring s1980::to_wstring( uint32_t s1739 ) const{
basic_stringstream<wchar_t> ss;
s310( &ss, 0 );
return ss.str();}
void s1980::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Table : " << endl;
for( auto it = begin( rows ); it != end( rows ); ++it ) {}}
vector<wstring> s1542 /*= { L"", s1601, s248, s1602, 
s263, s261, 
s986, s265, s235, s817, 
s877, s257, s249, s923,
s267, s803, s256, s264, 
s262, s873, s1483, s260, 
s238 }*/;
vector<int> BIFuncs1v = {
0, 0, 0, s1605, s1606, 0, 0, s1608, s1609, 0, 0, 0,
s1612, s1799, 0, 0, s1615, 0, 0, 0, s1617, s2066, s1801, 0, 0, 0, s1620, s1621,
0, 0, s1623, s1624
};
std::map<std::wstring, int> s1541;
s268::s268()
: s278( this, 0, s490 ), s736( s232, L"", L"global" ),
s204( L"" ), s207( this ), s1485( false ){}
s268::~s268(){}
void s268::reset(){
s655.reset();
s207.s839();
s203.clear();
s736.reset();
s1485 = false;}
void s268::s2079( bool soft /*=false*/ )
{
s350::s833( this, soft );
s207.s296();
s210[s7::s449] = s382.s15<s501*>();
s210[s7::s448] = s383.s15<s501*>();
s920( s7::s451, s384.s15<s501*>() );
s920( s7::s452, s385.s15<s501*>() );
s920( s7::s895, s380.s15<s501*>() );
s1576 = new s1575( this, this );
s1574 = new s1573( this, this );
s920( s7::s1562, s1574.s15<s501*>() );
s920( s7::s1563, s1576.s15<s501*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s374* s1647 = new s374( this, os, this );
s920( s7::s1543, s1647 );
if( s1541.empty() ) {
s1542 = { L"", s1601, s248, s1602,
s263, s1790, s261,
s986, s265, s235, s817,
s877, s257, s1791, s249,
s1792, s923,
s267, s1794, s1795, s803, s2065,
s1793, s256, s1736, s264,
s262, s873, s1796, 
s1483, s260, s238 };
for( size_t n = 1; n < s1542.size(); ++n )
s1541[s1542[n]] = (int)n;}}
static s6::s1873 s1949( L".", L",", true, true, true );
void s695( const std::wstring& s686, s757& s156 ) {
vector<s9<s146>> s692;
s1035 s1158 = new s1032( s686, true, s1949 );
s1158->read( s692, s7::s433 );
for( size_t n = 0; n < s692.size(); n++ ) {
wstring s687 = s269::s308( *s692[n], s7::s480 );
if( s687 == s7::s468 ) {
if( ( *s692[n] ).s159( s7::s482 ) ) {
const vector<s145>& s165 = ( *s692[n] ).s161( s7::s482 )->s170();
for( size_t n = 0; n < s165.size(); n++ )
s156.s693.push_back( s165[n]->s172() );}
if( ( *s692[n] ).s159( s7::s481 ) )
s156.entry = ( *s692[n] ).s161( s7::s481 )->s928();}}
if( s156.s693.empty() )
s156.s693.push_back( s686 );}
wstring s752( const wstring& s796, const wstring& s799 ){
if( s3::s759( s799 ) )
return s799;
if( !s3::s759( s796 ) )
throw new s16( L"The root path is not absolute: " + s796 );
if( s799.empty() )
return s796;
wstring path = s799;
wstring root = s796;
s4::s62( path );
s4::s62( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s16( L"The relative path '" + s799 + L"' is incompatible with the root '" + s796 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s16( L"The relative path '" + s799 + L"' is incompatible with the root '" + s796 + L"'." );}
return root + path;}
void s268::s217( const std::wstring& s198, const s146& obj ){
const vector<s145>& s767 = ( obj ).s161( s7::s487 )->s170();
const vector<s145>& packs = ( obj ).s161( s7::s778 )->s170();
vector<wstring> s41;
wstring s781 = s198.substr( 0, s198.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s767.size(); n++ )
s41.push_back( s752( s781, s767[n]->s172() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s172();
if( req.rfind( s7::s472 ) == req.size() - s7::s472.size() ) {
if( std::find( s203.begin(), s203.end(), req ) == s203.end() )
s203.push_back( s752( s781, req ) );}
else {
vector<wstring> matches;
for( size_t n = 0; n < s41.size(); n++ ) {
wstring match;
wstring _dir = s41[n];
s4::s62( _dir );
if( s3::s31( _dir, req + s7::s472, match ) )
matches.push_back( match );}
if( matches.empty() ) {
throw new s16( L"The required library '" + req + L"' is not found." );}
else if( matches.size() > 1 ) {
wstring s777;
s4::s295( matches, L",\n", s777 );
throw new s16( L"The required library's name '" + req + L"' is ambiguous: \n" + s777 );}
if( std::find( s203.begin(), s203.end(), matches[0] ) == s203.end() )
s203.push_back( matches[0] );}}}
void s707( s268* s306, s269& s736, s500& s689,
s650& cl, s649& cnl, s651& al ){
s269::s281& s737 = s736.s299();
s269::s281::iterator it = s737.begin();
s559 am = s531;
for( ; it != s737.end(); ++it ) {
s489 pc = s497;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s720;
s4::s58( it->first, L" ", s720 );
if( s720.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
wstring s687 = s720[1];
size_t idx = s720.size() - 2;
if( s720[idx] == s7::s466 )
pc = s496;
else if( s720[idx] == s7::s467 )
pc = s497;
else
throw new s16( L"unknown object type: " + s720[0] );
if( s720.size() == 3 ) {
if( s720[0] == s7::s463 )
am = s530;
else if( s720[0] == s7::s465 )
am = s532;
else if( s720[0] != s7::s464 )
throw new s16( L"invalid access mode name: " + it->first );
s687 = s720[2];}
it->second->s300( s687 );}
s278* ob = new s278( *it->second, s306, pc, s306, am, cl, cnl, al );
s689.s564( ob->s305(), ob );}}
void s268::s213( const wstring& s691, bool s2081 ){
s757 s675;
s269* s212 = new s269();
wstring s193 = s4::s787( s691 );
if( !s3::s759( s193 )) {
wstring s2076;
if( s2081 ) {
if( s2077.empty() )
throw new s16( L"can't find the file: " + s691 );
s2076 = s2077;}
else
s2076 = s812;
s4::s62( s2076 );
wstring file = s193.substr( s193.rfind( L"/" ) + 1 );
s193 = s752( s2076, s193.substr(0, s193.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s34( s193 );
if( isf == 2 ) {
s4::s62( s193 );
s193 += s7::s475;
if( s812.empty() )
s812 = s691;}
else if( isf == 1 ) {
if( s812.empty() )
s812 = s193.substr( 0, s193.find_last_of( L"\\/" ) );
}
else
throw new s16( L"cannot find file or directory: " + s691,
(uint32_t)s16::s17::s23 );
s4::s62( s812 );
s695( s193, s675 );
size_t s848 = s203.size();
vector<s9<s146>> s692;
for( size_t n = 0; n < s675.s693.size(); n++ ) {
s692.clear();
wstring s694 = s675.s693[n];
if( s694[0] != L'/' && s694[1] != L':' )
s694 = s812 + s694;
s203.push_back( s694 );}
for( size_t n = s848; n < s203.size(); ++n ) {
s692.clear();
s1035 s1158 = new s1032( s203[n], true, s1949 );
s1158->read( s692, s7::s433 );
for( size_t m = 0; m < s692.size(); m++ ) {
if( s269::s308( *s692[m], s7::s480 ) == s7::s471 )
s217( s203[n], *s692[m] );
else if( s269::s301( *s692[m], s7::s469 ) == s7::s469 ) {
s692[m]->s162( s7::s1240, new s6::s144( L"\"" 
+ s203[n] + 
L"\"" 
), s146::s148::s150 );
s212->s295( *s692[m] );}}}
s211( *s212 );
if( s1114.s1020() )
throw s1021( s1021::s17::s1096 );
s269::s281& s737 = s212->s299();
for( auto it : s737 ) 
s736.s292( it.second );
if( s204.empty() )
s204 = s675.entry;}
void s268::s211( s269& s212 ){
s500 s689;
s651 m1;
s649 s696;
s650 s697;
vector<wstring> s698;
s707( this, s212, s689, s697, s696, m1 );
size_t s699 = s696.size();
while( s698.size() < s699 ) {
size_t s700 = s696.size();
for( size_t n = 0; n < s696.size(); ++n ) {
if( s696[n].second.empty() ||
std::find( s698.begin(), s698.end(), s696[n].second )
!= s698.end() ) {
s698.push_back( s696[n].first );
s696.erase( s696.begin() + n-- );
continue;}}
if( s700 == s696.size() )
throw new s16( L"unresolved parent class: " + s696[0].second );}
for( size_t n = 0; n < s698.size(); ++n )
if( s207.s159( s698[n] ) )
throw new s16( L"class name already exists: " + s698[n] );
for( size_t n = 0; n < s698.size(); ++n )
s207.s223( s697[s698[n]], s697[s698[n]]->s368() );
s655.s295( s689 );
for( size_t n = 0; n < s698.size(); ++n ) {
s505 ob = (s278*)s207.get( s698[n], false );
if( ob )
ob->s157( *m1[s698[n]] );}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s278* ob = (s278*)s689.get( it->first, false );
if( ob && ob->s513() == s497 ) {
try {
ob->s157( *it->second );}
catch( s16* e ) {
e->s30( L"while constructing module: " + it->first );
throw e;}}}
s689.s519( this, false );}
void s268::s215( s146& obj ){
s269 s212;
s212.s295( obj );
s211( s212 );}
void s268::s1826( const std::wstring& s702 ){
s501* pd = s655.get( s702 );
if( pd->s513() == s497 )
((s278*)pd)->s1825();}
s501* s268::run( const vector<wstring>& s723 ){
if( s204.empty() )
s204 = s7::s474 + L"::" + s7::s473;
if( !s723.empty() ) {
wstring  s703, s702;
s701( s204, s702, s703 );
s278* mod = (s278*)s655.get( s702 );
s867::Cont s1433;
wstring ts = s323::proto->s368() + L"<" + s374::proto->s368() + L">";
s1170 pt = s323::proto.s15<s323*>()->s1338( ts, s1433 );
s323* s997 = (s323*) s306->TR().s1106( pt )->s370( this, vector<s502*>( {} ) );
for( size_t n = 0; n < s723.size(); ++n ) {
s997->add( new s374( this, s723[n], this ) );}
mod->s920( s7::s1747, s997 );
mod->s920( s7::s888, new s360( this, (int)s723.size() ) );}
vector<wstring> l;
return callFunc( s204, l );}
s501* s268::callFunc( const wstring& s, vector<wstring>& l ){
wstring  s703, s702;
s701( s, s702, s703 );
s278* mod = (s278*)s655.get( s702 );
s506 s704 = (s615*)mod->s670( s703, L"::" );
vector<s503> s280;
for( size_t n = 0; n < l.size(); n++ ) {
s1034 ast_ = new s269( l[n], NULL );
s508 cs = s615::s1235( *ast_, this, mod, mod->s304() );
s280.push_back( cs );}
s704->s620( s280 );
s502* pr = s704->s515();
try {
s1485 = false;
if( !pr )
s704->s519( this, true );
else
s704->s621( this );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s704->s305() + L"' function " );}
s1485 = true;
mod->s1825();
s501* s717 = s704->s516();
s1485 = false;
return s717;}
s506 s268::getProc( const std::wstring& s ){
wstring  s703, s702;
s701( s, s702, s703 );
s278* mod = (s278*)s655.get( s702 );
s506 s704 = (s615*)mod->s670( s703, L"::" );
s504 pr = s704->s515();
if( !pr )
s704->s519( mod, true );
return s704;}
void s268::s205( const std::wstring& s691 ){
wstring s193 = s691;
wstring s690;
int isf = s3::s34( s691 );
if( isf == 2 ) {
s4::s62( s193 );
s193 += s7::s475;
s690 = s691;}
else if( isf == 1 )
s690 = s193.substr( 0, s193.find_last_of( L"\\/" ) );
else
throw new s16( L"cannot find file or directory: " + s691, 
(uint32_t)s16::s17::s23 );
s4::s62( s690 );
vector<s9<s146>> s692;
s1035 s1158 = new s1032( s193 );
s1158->read( s692, s7::s433 );
s757 s675;
for( size_t n = 0; n < s692.size(); n++ ) {
wstring s687 = s269::s308( *s692[n], s7::s480 );
if( s687 == s7::s468 ) {
s206( *s692[n], s675 );
break;}}
s204 = s675.entry;
if( s675.s693.empty() )
s675.s693.push_back( s193 );
for( size_t n = 0; n < s675.s693.size(); n++ ) {
s692.clear();
wstring s694 = s675.s693[n];
if( s694[0] != L'/' && s694[1] != L':' )
s694 = s690 + s694;
s1035 s1158 = new s1032( s694 );
s1158->read( s692, s7::s433 );
for( size_t m = 0; m < s692.size(); m++ )
if( s269::s301( *s692[m], s7::s469 ) == s7::s469 )
s736.s295( *s692[m] );}}
void s268::s206( const s6::s146& obj, s757& s156 ){
const vector<s145>& s165 = obj.s161( s7::s482 )->s170();
for( size_t n = 0; n < s165.size(); n++ )
s156.s693.push_back( s165[n]->s172() );
if( obj.s159( s7::s481 ) )
s156.entry = obj.s161( s7::s481 )->s172();}
void s268::s223( s501* p, const wstring& s361 ){
s207.s223( p, s361 );}
bool s268::s579( const wstring& sym_, s386* ref, const wstring& s346, bool fr ) const{
if( !s278::s579( sym_, ref, s346, fr ) ) {
if( sym_ == s7::s1747 ) {
ref->s394( s668( s7::s895 ), s380 );
ref->s397( (s501*)this );
return true;}
return false;}
return true;}
bool s268::s226( s386& rf ) const{
rf.s397( NULL );
s209::const_iterator it = s210.find( rf.s643() );
if( it != end( s210 ) ) {
rf.s397( it->second );
return true;}
return false;}
void s268::s224( const wstring& s77, const wstring& s346,
vector<wstring>& s156 ){
size_t pl = s77.rfind( L"::" );
s278* mod = NULL;
bool bCl = false;
if( s77.find( L"()" ) == s77.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s706 = s77.substr( 0, pl );
wstring sym = s77.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );}
mod = (s278*)s655.get( s706 );
if( !mod->s671( sym, s346 ) )
throw new s16( L"Symbol '" + s77 + L"' cannot be imported by '" +
s346 + L"'");
s156.push_back( sym );}
else {
if( bCl ) {
wstring sym = s77.substr( 0, s77.size() - 2 );
s207.get( sym );
s156.push_back( sym );}
else {
mod = (s278*) s655.get( s77 );
mod->s667( s346, s156 );}}}
s615* s268::s218( int s1631, 
std::vector<s277*>& s740, s278* s612, s615* s219, const s269* s736 ){
s615* s717 = NULL;
if( s1631 == s1610 )
s717 = new s633( this, s612, s219, s740, s736 );
else if( s1631 == s1624 )
s717 = new s629( this, s612, s219, s740, s736 );
else if( s1631 == s1801 )
s717 = new s1783( this, s612, s219, s740, s736 );
else if( s1631 == s1604 )
s717 = new s632( this, s612, s219, s740, s736 );
else if( s1631 == s1605 )
s717 = new s1578( this, s612, s219, s740, s736 );
else if( s1631 == s1623 )
s717 = new s311( this, s612, s219, s740, s736 );
else if( s1631 == s1614 )
s717 = new s631( this, s612, s219, s740, s736 );
else if( s1631 == s1618 || s1631 == s1737)
s717 = new s634( this, s612, s219, s740, s736 );
else if( s1631 == s1607 )
s717 = new s635( this, s612, s219, s740, s736 );
else if( s1631 == s1612 )
s717 = new s905( this, s612, s219, s740, s736 );
else if( s1631 == s1615 )
s717 = new s906( this, s612, s219, s740, s736 );
else if( s1631 == s1620 )
s717 = new s637( this, s612, s219, s740, s736 );
else if( s1631 == s1619 )
s717 = new s636( this, s612, s219, s740, s736 );
else if( s1631 == s1606 )
s717 = new s638( this, s612, s219, s740, s736 );
else if( s1631 == s1609 )
s717 = new s640( this, s612, s219, s740, s736 );
else if( s1631 == s1616 )
s717 = new s641( this, s612, s219, s740, s736 );
else if( s1631 == s1613 )
s717 = new s847( this, s612, s219, s740, s736 );
else if( s1631 == s1611 )
s717 = new s822( this, s612, s219, s740, s736 );
else if( s1631 == s1622 )
s717 = new s1473( this, s612, s219, s740, s736 );
else if( s1631 == s1804 )
s717 = new s1786( this, s612, s219, s740, s736 );
else if( s1631 == s1621 )
s717 = new s840( this, s612, s219, s740, s736 );
else if( s1631 == s1800 )
s717 = new s1781( this, s612, s219, s740, s736 );
else if( s1631 == s1802 )
s717 = new s1784( this, s612, s219, s740, s736 );
else if( s1631 == s1799 )
s717 = new s1780( this, s612, s219, s740, s736 );
else if( s1631 == s1617 ) {
s717 = new s872( this, s612, s219, s740, s736 );}
else if( s1631 == s1803 )
s717 = new s1785( this, s612, s219, s740, s736 );
else if( s1631 == s1608 )
s717 = new s982( this, s612, s219, s740, s736 );
else if( s1631 == s1798 )
s717 = new s1779( this, s612, s219, s740, s736 );
else if( s1631 == s2066 )
s717 = new s2064( this, s612, s219, s740, s736 );
return s717;}
s277*
s268::s227( const wstring& s77, const wstring& s518, bool s543 /*= true*/ )
{
size_t pl = s77.rfind( L"::" );
s503 s717;
if( pl == string::npos ) {
s717 = (s277*)s207.get( s77, s543 );
if( !s717 ) {
s278* exp = (s278*)s207.get( s7::s470, false );
if( exp )
s717 = exp->s670( s77, s518, s543 );}
return s717;}
wstring s706 = s77.substr( 0, pl );
wstring sym = s77.substr( pl + 2 );
return ((s278*)s207.get( s706 ))->s670( sym, s518 );	}
void* s268::s228( const std::wstring& s284 ){
s350* s717;
s278* exp = (s278*) s655.get( s7::s470, false );
if( exp )
s717 = (s350*)exp->s670( s284, L"", true );
else
throw new s16( L"no such export variable: " + s284 );
void * pv = s717->addr();
return pv;}
void s268::s1519( const wstring& s702 ){
s207.s2057( s702 );
s655.s565( s702 );
if( s207.s159( s702) )
s207.s1842( s702 );}
void s268::s1841( const wstring& s1809 ){
vector<wstring> s1819;
for( auto it = s655.Table().begin(); it != s655.Table().end(); ++it ) {
s277* p = it->second.s15<s277*>();
if( p->s513() == s497 || p->s513() == s496 ) {
wstring s193 = ( (s278*)p )->s670( s7::s1240, 
L":::" )->to_wstring();
if( s193 == s1809 )
s1819.push_back( it->first );}}
for( auto mod : s1819 )
s1519( mod );
for( size_t n = 0; n < s203.size(); ++n ) {
if( s203[n] == s1809 ) {
s203.erase( s203.begin() + n );
break;}}}
void s268::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s201 ) << s284 << L" : " << L"Assembly" << endl;
s207.s310( pd, s201 + s434 );
s655.s310( pd, s201 + s434 );}
map<int, s1::s9<s268>> handles;
HPROG createAssembly(){
static int s716 = 0;
s1::s9<s268> p = new s268();
handles[++s716] = p;
p->s2079( false );
return s716;}
void deleteAssembly( int n ){
auto it = handles.find( n );
if( it == end( handles ) )
throw new s2::s16( L"no assembly with such handle" );
handles.erase( it );}
void loadProgram( HPROG handle, const wstring& s193 ){
s268* p = handles[handle];
p->s2070( s3::s2063() );
p->s213( s193, true );}
TDType* getProc( HPROG handle, const std::wstring& s625 ){
s268* p = handles[handle];
return (TDType*)p->getProc( s625 );}
void s215( HPROG handle, s6::s146& obj ){
s268* p = handles[handle];
p->s215( obj );}
TDType* run( HPROG handle, const vector<wstring>& s723 ){
return handles[handle]->run( s723 );}
void* callFunc( HPROG handle, const std::wstring& s78, vector<wstring>& l ){
s268* p = handles[handle];
return p->callFunc( s78, l );}
void evaluateExpression( const std::wstring& s78 ){}
void* s228( HPROG handle, const std::wstring& s284 ){
s268* p = handles[handle];
return p->s228( s284 );}
void* execute( TDType* p ){
return p->s516().s15<s350*>()->addr();}
void importSymbol( HPROG handle, const std::wstring& s1228, const std::wstring& symName,
const std::wstring& s346 ){
s268* p = handles[handle];
s278* ob = (s278*)p->s670( s1228, s346 );
ob->s578( symName, s346 );}
void importFile( HPROG handle, const std::wstring& s1228, const std::wstring& s44,
const std::wstring& s346 ){
vector<s1::s9<s6::s146>> s692;
s6::s1032 s1158( s44 );
s1158.read( s692, s7::s433 );
s268* p = handles[handle];
p->s213( s44 );
s278* ob = (s278*)p->s670( s1228, s346 );
for( size_t n = 0; n < s692.size(); n++ ) {
wstring s687 = s269::s308( *s692[n], s7::s480 );
ob->s578( s687, s346 );}}
HPROG initShell( const std::wstring& s1228, const std::wstring& modText ){
s1::s9<s6::s146> ob = new s6::s146(NULL);
size_t pos = 0;
s6::s1873 s1949( L".", L",", true, true, true );
s6::s1032 s1158( L"", true, s1949 );
s1158.s174( modText, pos, ob );
ob->s162( s7::s480, new s6::s144( s1228 ) );
HPROG prog = createAssembly();
s215( prog, *ob );
return prog;}
} // namespace transd
