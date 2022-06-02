
/*
This is a distributed file for Tourbillon virtual compiler embedding
library.
Copyright (c) 2020-2022 Albert Berger [alberger at gmail com].
All rights reserved.
Redistribution and use of this file in source and binary forms, 
without modification, are permitted for commercial and non-commercial
use.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
/*
*    transd.cpp
*    ----------
*
*    The minimized distributed source file for C++ embeddable
*    library of Tourbillon virtual compiler.
*
*    Transd Project website: https://transd.org
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
#include <float.h>
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
std::vector<std::wstring> s996 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1121(){
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
bool s36( const wstring& s210 ){
try {
s34( s210 );}
catch( s16& ) {
return false;}
return true;}
bool s35( const wstring& s210 ){
try {
if( s34( s210 ) != 1 )
throw new s16( L"Cannot find data file: " + s210,
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
wstring s685 = s37();
size_t pl = s685.rfind( '/' );
if( pl == string::npos )
s685 = L"";
else
s685 = s685.substr( 0, pl );
return s685;}
wstring s1884(){
char buf[2000];
memset( buf, 0, 2000 );
getcwd( buf, 2000 );
return wstring( conv.from_bytes( buf ) );}
bool s31( const wstring& s46, const wstring& s524, wstring& s153 ){
struct dirent *entry;
DIR *dp;
wregex rg( s524 );
bool s685 = false;
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s696 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s696,
(uint32_t)s16::s17::s22 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s153 = s46 + conv.from_bytes( entry->d_name );
s685 = true;
break;}}
closedir( dp );
return s685;}
void s32( const wstring& s46, const wstring& s524, vector<wstring>& s40, vector<wstring>& s41 ){
struct dirent *entry;
DIR *dp;
wregex rg( s524 );
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s696 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s696,
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
bool s724( const std::wstring& f ){
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
wstring s1884(){
wchar_t buf[2000];
memset( buf, 0, 4000 );
_wgetcwd( buf, 2000 );
return wstring( buf );}
bool s31( const wstring& _dir, const wstring& s524, wstring& s153 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s524.c_str() );
bool s685 = false;
wstring s46 = _dir;
if( s46.back() != L'/' && s46.back() != L'\\' )
s46 += L'\\';
if( ( s47 = FindFirstFileW( ( s46 + L"*" ).c_str(), &s43 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s47, &s43 ) ) {
s44 = s43.cFileName;
s45 = s46 + s44;
if( regex_match( s44, rg ) ) {
s153 = s45;
s685 = true;
break;}}
return s685;}
void s32( const wstring& _dir, const wstring& s524, vector<wstring>& s40, vector<wstring>& s41 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s524.c_str() );
wstring s46 = _dir;
if( s46.back() != L'/' && s46.back() != L'\\' )
s46 += L'\\';
if( ( s47 = FindFirstFileW( ( s46 + L"*" ).c_str(), &s43 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s47, &s43 ) ) {
s44 = s43.cFileName;
s45 = s46 + s44;
if( regex_match( s44, rg ) ) {
uint8_t is = s34( s45 );
if( is == 1 )
s40.push_back( s44 );
else if( is == 2 )
s41.push_back( s44 );}}}
bool s724( const std::wstring& f ){
if( f.size() && f[1] == ':' )
return true;
return false;}
} // namespace s3
#endif // WIN32
namespace s4 {
wstring s88 = L"\"`'";
wstring s48 = L"\n\r\t ";
string s49 = "\n\r\t ";
wstring s50 = L"";
wstring digits = L"0123456789";
void s54( const wstring& s, size_t s65, wchar_t left, wchar_t right,
size_t& start, size_t& end, bool s886/*=false*/ )
{
end = string::npos;
start = string::npos;
int s66 = 0;
wchar_t s876 = 0;
bool esc = false;
for( size_t n = s65; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s876 || !s886 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s66++;}
else if( c == right ) {
if( start == string::npos )
return; // s830
if( --s66 == 0 ) {
end = n;
return;}}
else if( s886 && ( c == L'\'' || c == L'\"' ) ) {
s876 = c;}}
else if( s876 && c == s876 && !esc ) {
s876 = 0;}
else if( c == L'\\' ) {
esc = !esc;}
else
esc = false;}}
void s862( const wstring& s, size_t s65, wchar_t left, wchar_t right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s65 );
if( start == string::npos || start == s.size() - 1 )
return;
int s66 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s66;
continue;}
if( s[n] == right )
--s66;
if( s66 == 0 ) {
end = n;
return;}}}
void s55( const wstring& s, size_t s65, wchar_t c, size_t& start, size_t& end ){
end = string::npos;
start = s.find( c, s65 );
if( start == string::npos || start == s.size() - 1 )
return;
bool s854 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s854 = !s854;
if( s[n] == c && !s854 ) {
end = n;
return;}
if( s[n] != L'\\' )
s854 = false;}}
void s1001( const std::wstring& s, size_t& s65, const std::wstring& s1882 ){
size_t s1880 = s65, s1881;
wstring s1342 = s1882 + L"\"";
s65 = string::npos;
bool s1883 = false;
while( true ) {
s1881 = s1880;
s1880 = s.find_first_of( s1342, s1880 );
if( s1880 == string::npos ) {
if( s1883 )
throw new s2::s16( L"no closing parenthesis: " + s.substr(s1881, 20) );
return;}
if( s[s1880] == L'\"' ) {
if( ! (s1880 && s[s1880-1] == '\\' ))
s1883 = !s1883;}
else{
if( !s1883 ) {
s65 = s1880;
return;}}
++s1880;}
return;
size_t pl = s.find_first_of( s1342, s65 );
if( pl == s65 )
return;
size_t start = s65;
s65 = string::npos;
while( pl < s.size() ) {
if( s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl++;
if( pl < s.size() )
pl = s.find_first_of( s1342, pl );}
else {
s65 = pl;
return;}}}
void s1327( const std::wstring& s, size_t& s65, const std::wstring& s1090 ){
size_t pl = s.find( s1090, s65 );
if( pl == s65 )
return;
size_t start = s65;
s65 = string::npos;
while( pl < s.size() ) {
if( s1090.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1090.size();
if( pl < s.size() )
pl = s.find( s1090, pl );}
else {
s65 = pl;
return;}}}
size_t count( const std::wstring& s77, const std::wstring& s1090, size_t start, size_t end,
bool s886 ){
size_t s685 = 0;
size_t pl = s77.find( s1090, start );
while( pl < s77.size() && pl <= end) {
if( s886 && pl && s77[pl-1] == '\\' ) {
++pl;}
else {
++s685;
pl += s1090.size();}
if( pl < s77.size() - 1 ) 
pl = s77.find( s1090, pl );}
return s685;}
int s56( const wstring& s77, wchar_t s72, size_t& pos ){
size_t s70 = s77.find( s72, pos );
if( s70 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s52( s77.substr( pos, s70 - pos ), L" " );
int s685 = stoi( s );
pos = s77.find_first_not_of( s48 + s72, s70 );
return s685;}
bool s62( const wchar_t *str, long *s349, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s685 = true;
errno = 0;
*s349 = std::wcstol( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s349 == LONG_MIN || *s349 == LONG_MAX ) && errno == ERANGE ) )
s685 = false;
if( end )
*end = s67;
return s685;}
bool s1544( const wchar_t *str, long long *s349, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s685 = true;
errno = 0;
*s349 = std::wcstoll( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s349 == LLONG_MIN || *s349 == LLONG_MAX ) && errno == ERANGE ) )
s685 = false;
if( end )
*end = s67;
return s685;}
bool s1545( const wchar_t *str, unsigned long long *s349, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s685 = true;
errno = 0;
*s349 = std::wcstoull( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s349 == ULLONG_MAX ) && errno == ERANGE ) )
s685 = false;
if( end )
*end = s67;
return s685;}
bool s63( const wchar_t *str, double *s349, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s685 = true;
errno = 0;
*s349 = std::wcstod( str, &s67 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s349 == HUGE_VAL || *s349 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s685 = false;
if( end )
*end = s67;
return s685;}
void s877( const wstring& s77, vector<wstring>& s153 ){
size_t s68 = s77.find_first_not_of( s48 );
size_t s681, s682;
while( s68 != string::npos ) {
wchar_t c = s77[s68];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s55( s77, s68, c, s681, s682 );
if( s682 == string::npos )
throw s2::s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
arg = s77.substr( s68, s682 - s68 + 1 );
s68 = s77.find_first_not_of( s48, ++s682 );}
else {
s682 = s77.find_first_of( s48 );
arg = s77.substr( s68, s682 - s68 );
s68 = s682;}
s153.push_back( arg );}}
std::wstring s1828( const std::wstring& s77, wchar_t c ){
size_t pl = s77.find( c ), s1850 = 0, s1821 = 0, s1844;
if( pl == string::npos )
return s77;
wstring s685( s77.size() + 100, L'\0' );
while( pl != string::npos ) { 
s1844 = pl - s1850;
if( s685.size() < s1821 + s1844 + 2 )
s685.resize( (std::max)((size_t)(s685.size()*1.1), s685.size()+100) );
memcpy( (void*)(s685.c_str() + s1821), s77.c_str() + s1850, s1844 * sizeof(wchar_t) );
s685[s1821 + s1844] = L'\\';
s685[s1821 + s1844 + 1] = s77[pl];
s1821 = s1821 + s1844 + 2;
s1850 = pl + 1;
pl = s77.find( c, pl + 1 );}
s1844 = s77.size() - s1850;
memcpy( (void*)(s685.c_str() + s1821), s77.c_str() + s1850, s1844 * sizeof(wchar_t) );
s685.resize( s1821 + s1844/* + 1*/ );
return s685;}
void s57( const wstring& s, const wstring& s72, vector<wstring>& s153, bool clr,
bool s886 ){
size_t s68 = 0, s69 = 0;
while( s69 != wstring::npos && s68 < s.size()) {
if( s886 ) {
s69 = s68;
s4::s1001( s, s69, s72 );}
else
s69 = s.find( s72, s68 );
wstring seg;
if( clr )
seg = s52( s.substr( s68, s69 - s68 ), s48 );
else
seg = s.substr( s68, s69 - s68 );
s68 = s69 + s72.size();
if( seg.size() )
s153.push_back( seg );
if( s69 != string::npos && s153.capacity() <= s153.size() )
s153.reserve( s153.size() * ( s.size() / s68 ) + 100 );
}}
void s289( const vector<wstring>& v, const wstring& s72, wstring& s153 ){
if( v.empty() )
return;
s153 = v[0];
for( size_t n = 1; n < v.size(); ++n )
s153 += (s72 + v[n]);}
wstring s71( const wstring& s77, size_t& pos ){
size_t pl = s77.find( L'\n', pos );
wstring line = s52( s77.substr( pos, pl - pos ), s48 );
pos = pl == string::npos ? pl : pl + 1;
return line;}
void s58( const wstring& s77, const wstring& s72, 
pair<wstring, wstring>& pr, size_t& pos ){
size_t pl = s77.find( L'\n', pos );
wstring line = s52( s77.substr( pos, pl - pos ), s48 );
pos = pl == string::npos ? pl : pl + 1;
pl = line.find( s72 );
if( pl == string::npos ) 
throw s2::s16( L"invalid pair syntax: " + line );
wstring s76 = s52( line.substr( 0, pl ), s48 );
wstring s349 = s52( line.substr( pl + s72.size() ), s48 );
pr.first = s76;
pr.second = s349;}
void s59( const wstring& s77, const wstring& s72, vector<pair<wstring, wstring>>& v ){
vector<wstring> s73;
s57( s52( s77, s48 ), L"\n", s73 );
for( size_t n = 0; n < s73.size(); ++n ) {
size_t pl = s73[n].find( s72 );
wstring s76 = s52( s73[n].substr( 0, pl ), s48 );
wstring s349 = s52( s73[n].substr( pl + s72.size() ), s48 );
v.push_back( make_pair( s76, s349 ) );}}
wstring s51( const std::wstring& l, const std::wstring& s, const std::wstring& r ){
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s685 = s.substr( pl );
return s685.substr( 0, s685.find_last_not_of( r ) + 1 );}
wstring s52( const std::wstring& s, const std::wstring& c ){
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s685 = s.substr( pl );
return s685.substr( 0, s685.find_last_not_of( c ) + 1 );}
wstring s60( const wstring& s77 ){
if( s77[0] != L'{' )
return s77;
size_t s74, s75;
s54( s77, 0, L'{', L'}', s74, s75 );
wstring s79 = s77.substr( s74 + 1, s75 - s74 - 1 );
vector<wstring> s80;
s57( s52( s79, L" " ), L"|", s80 );
#ifdef WIN32	
return s80[0] + s77.substr( s75 + 1 );
#else
return s80[1] + s77.substr( s75 + 1 );
#endif	
}
bool s53( const std::wstring& s, const std::wstring& ss ){
if( s.substr( s.size() - ss.size() ) == ss )
return true;
return false;}
void s61( wstring& s46 ){
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
wstring s746( wstring path ){
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
void s64( const std::wstring& s78 ){}
void s54( const string& s, size_t s65, char left, char right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s65 );
if( start == string::npos || start == s.size() - 1 )
return;
int s66 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s66;
continue;}
if( s[n] == right )
--s66;
if( s66 == 0 ) {
end = n;
return;}}}
int s56( const string& s77, char s72, size_t& pos ){
size_t s70 = s77.find( s72, pos );
if( s70 == string::npos )
throw invalid_argument( "separator not found" );
string s = s52( s77.substr( pos, s70 - pos ), " " );
int s685 = stoi( s );
pos = s77.find_first_not_of( s49 + s72, s70 );
return s685;}
void s57( const string& s, const string& s72, vector<string>& s153 ){
size_t s68 = 0, s69 = 0;
while( s69 != string::npos ) {
s69 = s.find( s72, s68 );
string seg = s52( s.substr( s68, s69 - s68 ), s49 );
s68 = s69 + s72.size();
s153.push_back( seg );}}
void s59( const string& s77, vector<pair<string, string>>& v ){
vector<string> s73;
s57( s52( s77, s49 ), "\n", s73 );
for( size_t n = 0; n < s73.size(); ++n ) {
size_t pl = s73[n].find( ':' );
string s76 = s52( s73[n].substr( 0, pl ), s49 );
string s349 = s52( s73[n].substr( pl + 1 ), s49 );
v.push_back( make_pair( s76, s349 ) );}}
string s51( const std::string& l, const std::string& s, const std::string& r ){
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s685 = s.substr( pl );
return s685.substr( 0, s685.find_last_not_of( r ) + 1 );}
string s52( const std::string& s, const std::string& c ){
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s685 = s.substr( pl );
return s685.substr( 0, s685.find_last_not_of( c ) + 1 );}
string s60( const string& s77 ){
if( s77[0] != '{' )
return s77;
size_t s74, s75;
s54( s77, 0, '{', '}', s74, s75 );
string s79 = s77.substr( s74 + 1, s75 - s74 - 1 );
vector<string> s80;
s57( s52( s79, " " ), "|", s80 );
#ifdef WIN32	
return s80[0] + s77.substr( s75 + 1 );
#else
return s80[1] + s77.substr( s75 + 1 );
#endif	
}
void s81( wstring& s77, vector<wstring>& s1104, map<size_t, size_t>& s1037 ){
size_t pos = 0;
wchar_t s82 = 0;
bool s1165 = false;
wchar_t s83 = 0;
bool s84 = false;
bool s85 = false;
size_t s86 = string::npos;
bool s87 = false;
bool s980 = false;
wstring s88 = L"`'\"";
s1104.reserve( 1000 );
size_t s1032 = 1;
bool s972 = false;
while( pos < s77.size() ) {
wchar_t c = s77[pos];
if( c == '\r' ) {
s77.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1165 = !s1165;}
else if( s82 ) {
if( c == s82 && !s1165 /*s83 != '\\'*/ )
s82 = 0;}
else if( s88.find( c ) != string::npos ) {
if( !s84 ) {
s82 = c;}}
else if( c == '*' ) {
if( !s84 && s83 == '/' ) {
s84 = true;
s85 = true;
s86 = pos - 1;
if( pos > 1 && s77[pos - 2] != '\n')
s1037[pos - 2] = s1032;}}
else if( c == '/' ) {
if( !s84 && s83 == '/' ) {
s86 = pos - 1;
s84 = true;
s85 = false;
if( pos > 1 && s77[pos - 2] != '\n')
s1037[pos - 2] = s1032;}
else if( s85 && s83 == '*' ) {
s87 = true;
if( s77[pos+1] == '\n' ){
s972 = true;}}}
else if( c == '\n' ) {
s972 = true;
if( s84 ) {
if( !s85 ) {
s87 = true;}
else {
if( !s980 ) {
s980 = true;}}}
else {
if( pos && s77[pos-1] != '\n' ) {
s1037[pos - 1] = s1032;}}}
if( c != L'\\' )
s1165 = false;
if( s972 ) {
size_t pl = s77.rfind( '\n', pos - 1 );
size_t m = (s77[pos] == '\n');
if( pl == string::npos )
s1104.push_back( s77.substr( 0, pos ) );
else
s1104.push_back( s77.substr( pl + 1, pos - pl - m ) );
s972 = false;
s1032++;}
if( s87 ) {
int m = 0;
if( s85 )
m = 1;
if(	s77[pos] == '\n' && ( !s86 || s77[s86 -1] == '\n' ) )
m = 1;
if( m ) {
s77.replace( s86, pos - s86 + m, L"");
pos = s86 - 1;}
else {
s77.replace( s86, pos - s86 + m, L" ");
pos = s86 + 1;}
s86 = string::npos;
s84 = false;
s980 = false;
s85 = false;
s87 = false;
s83 = 0;}
s83 = c;
pos++;}
if( s84 ) {
auto it = end(s1037);
if( s1037.size() ) it--; 
size_t ln = (it == end(s1037) ? 0 : it->second);
throw new s2::s16( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
std::wstring s2187( void* p ){
wstring s685( 21, '\0' );
#ifdef WIN32		
_swprintf( (wchar_t*)s685.c_str(), L"%p", (uint64_t*)p );
#else
swprintf( (wchar_t*)s685.c_str(), 20, L"%06x", (uint64_t*)p );
#endif	
return s685;}
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
uint32_t s17::s89;
void s17::s29(){
s89 = s16::s28();}
void s1117(){
s17::s29();}
bool s98( const wstring& s93 ){
wcout << s93 << L" [Y]es | [n]o :";
wstring ans;
getline( wcin, ans );
if( ans.size() && s52( ans, L" " ).empty() )
throw new s16( s17::s90() );
if( ans.size() && ( ans[0] == L'N' || ans[0] == L'n' ) )
return false;
return true;}
int s99( const wstring& s93, const vector<wstring>& s94 ){
int s685;
while( true ) {
s130();
wcout << s93 << endl << endl;
for( size_t i = 0; i < s94.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s94[i] << endl;}
s685 = s103( L"Please, enter your answer's number: " );
if( s685 < 0 || s685 > ( int ) s94.size() ) {
wcout << "No variant with such number." << endl;
s96();
continue;}
break;}
return s685;}
wstring s100( const wstring& s93, bool s95 ){
if( !s93.empty() )
wcout << s93;
wstring s349;
if( s95 )
s97( false );
getline( wcin, s349 );
if( s95 )
s97( true );
return s349;}
wstring s101( const wstring& s93, bool s95 ){
wcout << s93;
int s117 = 0;
bool s588 = true;
wstring s118 = s93;
size_t s1111 = s118.size();
size_t s119 = s1111;
while( s588 ) {
s117 = _getch();
switch( s117 ) {
case s110:
if( s1111 > s119 ) {
wcout << '\r' << s118.substr( 0, --s1111 );}
break;
case s111:
if( s1111 < s118.size() )
wcout << s118[s1111++];
break;
case s108:
case s109:
continue;
case s114:
if( ( s1111 > s119 ) && s118.size() ) {
s118.erase( --s1111, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}
break;
case s115:
if( s1111 < s118.size() ) {
s118.erase( s1111, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}
break;
case s113:
s588 = false;
break;
case s116:
break;
default:
if( s1111 < s118.size() )
s118.insert( s1111, 1, s117 );
else
s118 += s117;
++s1111;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}}
return s118;}
wstring getStringValHist( const wstring& s93, const vector<wstring>& s102 ){
wcout << s93;// << endl;
int s117 = 0;
size_t s684 = s102.size();
bool s588 = true;
wstring s118 = s93;
size_t s1888 = s93.size();
size_t s1111 = s1888;
while( s588 ) {
s117 = _getch();
#ifdef __LINUX__
if( s117 == 27 ) {
s117 = _getch();
s117 = _getch();
if( s117 == L'A' ) s117 = s108;
else if( s117 == L'B' ) s117 = s109;
else if( s117 == L'C' ) s117 = s111;
else if( s117 == L'D' ) s117 = s110;
else if( s117 == 51 ) {
s117 = _getch();
s117 = s115;}
else if( s117 == 70 ) s117 = s1557;
else if( s117 == 72 ) s117 = s1558;
else if( s117 == 54 || s117 == 53 ) {
s117 = _getch();
continue;}}
else if( s117 == 10 )
s117 = 13;
else if( s117 == 127 )
s117 = 8;
#else			
if( s117 == 224 ) {
s117 = _getch();
if( s117 == L'H' ) s117 = s108;
else if( s117 == L'P' ) s117 = s109;
else if( s117 == L'M' ) s117 = s111;
else if( s117 == L'K' ) s117 = s110;}
else if( s117 == 0 ) {
s117 = _getch();
if( s117 == 83 ) s117 = s115; // S
else if( s117 == 71 ) s117 = s1558; // G
else if( s117 == 79 ) s117 = s1557; // O
}
#endif			
switch( s117 ) {
case s110:
if( s1111 > s1888 ) {
wcout << '\r' << s118.substr( 0, --s1111 );}
break;
case s111:
if( s1111 < s118.size() )
wcout << s118[s1111++];
break;
case s108:
if( s684 > 0 ) {
if( s684 < s102.size() )
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[--s684];
wcout << '\r' << s118;
s1111 = s118.size();}
break;
case s109:
if( !s102.empty() && s684 < s102.size() - 1 ) {
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[++s684];
wcout << '\r' << s118;
s1111 = s118.size();}
break;
case s114:
if( s1111 > s1888 && s118.size() > s1888 ) {
s118.erase( --s1111, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}
break;
case s115:
if( s1111 < s118.size() ) {
s118.erase( s1111, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}
break;
case s1558:
if( s1111 > 0 ) {
wcout << '\r' << s93;
s1111 = s1888;}
break;
case s1557:
if( s1111 < s118.size() ) {
wcout << '\r' << s118;
s1111 = s118.size();}
break;
case s113:
s588 = false;
break;
case s116:
break;
default:
if( s1111 < s118.size() )
s118.insert( s1111, 1, s117 );
else
s118 += s117;
++s1111;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1111 );}}
return s118.substr( s1888 );}
int s103( const std::wstring & s93 ){
int s685;
while( true ) {
wcout << s93;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s685 = stoi( inp );}
catch( std::invalid_argument& ) {
continue;}
break;}
return s685;}
void s91( const wstring& header, const std::vector<std::wstring>& s92 ){
s130();
wcout << endl << "  " << header << endl << fill_n_ch( L'-', header.size() + 4 )
<< endl << endl;
if( s92.size() ) {
wcout << L"Keyboard shortcuts: " << endl;
for( size_t n = 0; n < s92.size(); n += 2 )
wcout << setw( 10 ) << left << s92[n] << L" - " << s92[n + 1] << endl;}
wcout << endl;}
size_t s104( const std::wstring & s93 ){
wcout << s93 << endl << endl <<
L"Please, enter the number of menu item: " << endl <<
L"1 - Skip this item" << endl << L"2 - Overwrite this item" << endl <<
L"3 - Skip all already existing items" << endl <<
L"4 - Overwrite all already existing items" << endl << "5 or any key - Cancel operation" << endl;
wstring s129;
getline( wcin, s129 );
int i;
try { i = stoi( s129 ); }
catch( std::invalid_argument* ) {
i = 5;}
if( i < 1 || i > 5 )
i = 5;
return i;}
void s106( const vector<wstring>& v, vector<wstring>& s153, size_t w, size_t h ){
size_t s120 = v.size() / h + 1;
size_t s121 = v.size() / s120;
vector<size_t> s122;
size_t s684 = 0;
for( auto it : v ) {
if( s684 == 0 )
s122.push_back( 0 );
if( it.size() > s122.back() )
s122.back() = it.size();
if( ++s684 == s121 )
s684 = 0;}
size_t s123 = 0, s124 = 0;
size_t s125 = 0;
for( size_t n = 0; n < s120; ++n ) {
s125 += s122[n] + 5;
if( n == s120 - 1 || s125 + s122[n + 1] + 5 > w ) {
size_t s126 = n - s123 + 1;
s125 = 0;
if( s123 ) {
if( s100( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}
for( size_t m = s124;
m < min( s124 + s121, v.size() );	++m ) {
wostringstream ss;
for( size_t k = 0;
k < min( s126, ( v.size() - m - 1 ) / s121 + 1 ); ++k )
ss << setw( 3 ) << right << m + s121 * k + 1 << L". " << setw( s122[s123 + k] ) <<
left << v[m + s121 * k];
s153.push_back( ss.str() );}
s124 += s126 * s121;
s123 = n + 1;}}}
int s107( const std::vector<std::wstring>& v ){
int w, h;
s105( w, h );
std::vector<std::wstring> rows;
s106( v, rows, w, h );
size_t s127 = 0;
for( auto it : rows ) {
wcout << it << endl;
if( ++s127 % h == 0 ) {
if( s100( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}}
int s128;
while( true ) {
wcout << endl;
wstring s129 = s100( L"Enter the item's number or <Space> to cancel..." );
if( s129 == L" " )
return -1;
try { s128 = stoi( s129 ); }
catch( std::invalid_argument& ) {
continue;}
break;}
if( s128 > (int)v.size() ) {
wcout << L"No record with such number." << endl;
return -1;}
return s128;}
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
void s96(){
wcout << endl << L"Press 'Return' to continue..." << endl;
std::system( "read" );}
void s130( int s73 ){
std::system( "clear" );
for( int i = 0; i < s73; ++i )
wcout << endl;}
void s97( bool b ){
struct termios tty;
tcgetattr( STDIN_FILENO, &tty );
if( !b )
tty.c_lflag &= ~ECHO;
else
tty.c_lflag |= ECHO;
(void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );}
void s105( int& w, int& h ){
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
if( buf[2] == 65 ) buf[0] = s108;
if( buf[2] == 66 ) buf[0] = s109;
if( buf[2] == 67 ) buf[0] = s111;
if( buf[2] == 68 ) buf[0] = s110;}
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
void s96(){
wcout << endl;
std::system( "pause" );}
void s130( int s73 ){
std::system( "CLS" );
for( int i = 0; i < s73; ++i )
wcout << endl;}
void s97( bool b ){
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode;
GetConsoleMode( hStdin, &mode );
if( !b )
mode &= ~ENABLE_ECHO_INPUT;
else
mode |= ENABLE_ECHO_INPUT;
SetConsoleMode( hStdin, mode );}
void s105( int& w, int& h ){
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;}
} // namespace consutils
#endif // WIN32
using namespace s1;
using namespace s5;
namespace s6{
wstring s185 = L"-.0123456789";
wstring s1538 = L"0123456789";
wstring s1539 = L".0123456789";
wstring s186 = L" ,]}\t\r\n";
wstring s2148 = L"-_[]";
s1695 s1757;
thread_local std::list<bool> s1769;
void s1698( const wstring& dd, const wstring& fs, bool ab, bool rb, bool sb ){
s1757 = s1695( dd, fs, ab, rb, sb );}
void s1698( const s1695& cnf ){
s1757 = cnf;}
void s945::s170( const wstring& s77, size_t& pos, s9<s143> ob ){
size_t s74, s75;
s54( s77, pos, L'{', L'}', s74, s75, true );
if( s74 == string::npos )
return;
s1059 = s74 - 1;
wstring sob = s77.substr( s74, s75 - s74 + 1 );
pos = s75 + 1;
try {
s1769.push_back( s1760.s151 );
ob->s154( sob, s1760 );
s1769.pop_back();}
catch( s16* e ) {
s1769.pop_back();
e->s30( L"during reading the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s945::s1005( wstring& s, size_t s68, size_t s683, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1116.lower_bound( s68 );
auto iten = s1116.lower_bound( s683 );
if( itst == end(s1116) || iten == end(s1116) )
return false;
line = itst->second;
s = s1115[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1115[iten->second-1];
return true;}
void s187( wstring& s77 ){
wregex s188(
LR"regex(\n\r?\/\/.*?\n\r?)regex"
);
wsmatch sm;
wstring::const_iterator itst = s77.begin();
wstring::const_iterator iten = s77.end();
while( std::regex_search( itst, iten, sm, s188 ) ) {
s77.erase( sm.position(), sm.length() - 
(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
itst = s77.begin();
iten = s77.end();}}
s945::s945( const std::wstring& file, bool s1634, const s1695& s1759 )
: s1760( s1759 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s48 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1634 == false )
s1114 = file;
else
s194 = file;}
void s945::read( vector<s9<s143>>& s153, const wstring& s190 ){
size_t pos = 0;
if( s194.size() ) {
std::ifstream fs( TOFS( s194 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s194 ));
string s191( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1114 = conv.from_bytes( s191 );
s4::s81( s1114, s1115, s1116 );
if( s190.size() ) {
pos = s1114.find( s190 );
if( pos == string::npos )
throw new s16( s190 + L" directive not found in the source file." );
pos += s190.size() + 1;
if( s1114.size() > 13 && s1114[14] == '\r' )
++pos;}}
size_t s192 = pos;
wstring s278;
bool s193 = false;
while( ( pos = s1114.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1114.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s192; subl = pos - s192;}
else
pl += 1;
wstring s1 = s52( s1114.substr( pl, /*pos - pl - 1*/subl ), s48 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s193 = true;
else
s278 = s52( s1, s48 + L":" );}
if( s278.empty() ) {
size_t pl1 = s1114.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s52( s1114.substr( pl1, pl ), s48 );
if( s1.size() ) {
if( ( !s193 && s1[s1.size() - 1] != L':' ) ||
( s193 && s1[s1.size() - 1] == L':' ) ||
(!s193 && s1.size() == 1 ) )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
s278 = s52( s1, s48 + L":" );}}}
if( s88.find( s278[0] ) != string::npos ) {
if( s278[0] != s278[s278.size()-1] )
throw new s16( L"Malformed block name: " + s278.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
else {
if(	iswdigit( s278[0] ) )
throw new s16( L"wrong unquoted syntax: " + s278.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
s9<s143> ob = new s143( this );
try {
s1769.push_back( s1760.s151 );
s170( s1114, pos, ob );
s1769.pop_back();}
catch( s16* e ) {
s1769.pop_back();
e->s30( L"during reading the file: " + s194 );
throw e;}
if( s278.size() )
ob->s159( L"@name", new s141( s278 ), s143::s145::s147 );
s278 = L"";
s193 = false;
s153.push_back( ob );}}
void s171( const wstring& s194, const vector<s1::s9<s143>>& s195 ){
std::ofstream fs( TOFS( s194 ), ios::out | ios::trunc | ios::binary );
if( !fs.good() )
throw runtime_error( "Reading state file failed: " + U8( s194 ) );
for( auto ob : s195 ) {
basic_stringstream<wchar_t> ss;
ob->s155( &ss );
string s = U8( ss.str() );
s += "\n\n";
fs.write( s.c_str(), s.size() );}}
void s172( const wstring& s77, size_t& pos, wchar_t quote, wstring& s153, bool s151 = false ){
size_t s74, s75;
s55( s77, pos, quote, s74, s75 );
if( s75 != string::npos ) {
pos = s75 + 1;
if( !s1769.empty() && s1769.back() )
s153 = s52( s77.substr( s74, s75 - s74 + 1), s48 ); 
else
s153 = s52( s77.substr( s74+1, s75 - s74 - 1 ), s48 ); }
else
pos = string::npos;}
void s173( wostream* pd, const wstring& s ){
wchar_t q = L'\"';
if( s88.find( s[0] ) != string::npos )
q = s[0];
size_t start = 1;
*pd << q;
if( s[0] != q ) 
start = 0;
for( size_t n = start; n < s.size(); ++n ) {
if( s[n] == q && s[n-1] != L'\\' && n != s.size() - 1 )
*pd << L'\\';
*pd << s[n];}
if( s.empty() || s[s.size()-1] != q )
*pd << q;}
void s174( const wstring& s77, size_t& pos, wstring& s153 ){
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"unrecognized unquoted syntax: " + s77.substr(pos, 20), 
(uint32_t)s16::s17::s20 );
size_t s196 = pos + 1;
while( std::isgraph<wchar_t>( s77[s196], locloc ) &&
s77[s196] != L':' && s77[s196] != L',' )
++s196;
s153 = s52( s77.substr( pos, s196 - pos ), s48 );
pos = s196;}
void s175( const wstring& s77, size_t& pos, wchar_t s1207, wchar_t s1250, wstring& s153 ){
size_t s74, s75;
s54( s77, pos, s1207, s1250, s74, s75, true );
if( s75 == string::npos )
throw new s16( L"unmatched unquoted parentheses: " + s77.substr(pos, 20), 
(uint32_t)s16::s17::s20 );
if( s75 == s77.size() - 1 ) {
pos = s75;}
else {
size_t pl = s77.find_first_not_of( s48, s75 + 1 );
if( pl == string::npos && s77[pl] != L',' && s77[pl] != L'}' )
throw new s16( L"wrong unquoted parentheses syntax: " + s77.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
pos = s75 + 1;}}
s131 s176( const wstring& s77, size_t& pos, wstring& s153, const s1695& s1759 ){
if( s77[pos] == s1759.s1697[0] && s1759.s1744) {
s153 = L"";
return s132;}
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"empty element or unrecognized unquoted syntax: " + s77.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s196 = pos;
int shift = 0;
if( s77[pos] == L'(' && s1759.s1699) {
s175( s77, s196, L'(', L')', s153 );
if( s196 == s77.size() - 1 )
shift = 1;}
else {
s196 = pos + 1;
while( std::isgraph<wchar_t>( s77[s196], locloc ) &&
s77[s196] != L':' && s77[s196] != L',' ) {
if( s77[s196] == L'<'  && s1759.s1700 ) {
s175( s77, s196, L'<', L'>', s153 );}
else if( s77[s196] == L'(' && s1759.s1699 ) {
s175( s77, s196, L'(', L')', s153 );
if( s196 == s77.size() - 1 )
shift = 1;
break;}
else
++s196;}}
s153 = s52( s77.substr( pos, s196 - pos + shift ), s48 );
pos = s196;
return s134;}
void s177( wostream* pd, const wstring& s ){
if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
s[s.size()-1] == L'"' )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
for( size_t n = 0; n < s.size(); ++n ) 
if( !std::isgraph<wchar_t>( s[n], locloc ) )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
*pd << s;}
void s178( const s945* pf, const wstring& s77, vector<s9<s141>>& s153, 
const s1695& s1759 ){
size_t s68 = s77.find_first_not_of( s48 );
s1769.push_back( s1759.s1732 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, s77, s68, s1759 ) ) );
s4::s1001( s77, s68, s1759.s1697 );
if( s68 == string::npos )
break;
++s68;}
s1769.pop_back();}
void s178( const s945* pf, const wstring& s77, size_t& pos,
vector<s9<s141>>& s153, const s1695& s1759 ){
size_t s74, s75, s68 = 0;
s54( s77, pos, L'[', L']', s74, s75, true );
pos = s75 + 1;
wstring ar = s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 );
if( ar.empty() )
return;
s1769.push_back( s1759.s1732 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, ar, s68, s1759 ) ) );
s4::s1001( ar, s68, s1759.s1697 );
if( s68 == string::npos )
break;
++s68;}
s1769.pop_back();}
void s179( wostream* pd, const vector<s9<s141>>& v, bool s151=false ){
*pd << L'[';
for( size_t n = 0; n < v.size(); ++n ) {
v[n]->s155( pd, s151 );
if( n != v.size() - 1 )
*pd << L',';}
*pd << L']';}
void s180( const wstring& s77, size_t& pos, wstring& s153, bool s151 = false ){
size_t pl = s77.find_first_not_of( L", \n\r\t", pos );
if( s88.find( s77[pl] ) != string::npos ) 
s172( s77, pos, s77[pl], s153, s151 );
else {
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"unrecognized name syntax: " + s77.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
size_t s196 = pos + 1;
wchar_t c = s77[s196];
while( c != L':' && c != L',' ) {
if( !std::isalnum<wchar_t>( c, locloc ) &&	!std::isspace<wchar_t>( c, locloc ) && 
s2148.find( c ) == string::npos )
throw new s16( L"unrecognized name syntax: " + s77.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
c = s77[++s196];}
s153 = s52( s77.substr( pos, s196 - pos ), s48 );
pos = s196;}}
void s181( wostream* pd, const wstring& s, bool s151=false ){
bool space = false;
for( size_t n = 0; n < s.size(); ++n )
if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
space = true;
break;}
if( !space && !s151 && s88.find( s[0] ) == string::npos )
s177( pd, s );
else
s173( pd, s );}
s131 s182( const wstring& s77, size_t& pos, double& s153 ){
s131 s685 = s140;
size_t pl = s77.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s77.find( L".", pl );
if( pl1 < pl )
s685 = s136;
if( pl == string::npos )
s153 = stod( s77.substr( pos ) );
else
s153 = stod( s77.substr( pos, pl - pos ) );
pos = pl;
return s685;}
s131 s1550( const wstring& s77, size_t& pos, double& s153, const s1695& s1759 ){
const wchar_t* ps = s77.c_str();
size_t sz = s77.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1539.find( ps[st+1] ) == string::npos )
return s132;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1538.find( ps[st+1] ) != string::npos ) ||
( s1538.find( ps[st] ) == string::npos ) )
return s132;
size_t s684 = st;
bool pt = false;
while( s684 < sz ) {
if( ps[s684] == s1759.s1696[0] ) {
if( pt ) return s132;
pt = true;
s684++;}
else if( s1538.find( ps[s684] ) != string::npos )
s684++;
else if( (s48 + s1759.s1697 + L"}").find( ps[s684] ) != string::npos  )
break;
else
return s132;}
s131 s685 = s140;
if( pt )
s685 = s136;
if( s684 == sz )
s153 = stod( s77.substr( pos ) );
else
s153 = stod( s77.substr( pos, s684 - pos ) );
pos = s684;
return s685;}
bool s183( const wstring& s77, size_t& pos, bool& s153 ){
size_t pl = 0;
if( s77.find( L"true", pos, 4 ) == pos )
pl = 4;
else if( s77.find( L"false", pos, 5 ) == pos )
pl = 5;
if( pl ) {
if( s186.find( s77[pos+pl] ) != string::npos ) {
pos += pl;
s153 = (pl == 4);
return true;}}
return false;}
bool s184( const wstring& s77, size_t& pos ){
if( s77.find( L"null", pos, 4 ) == pos ) {
if( s186.find( s77[pos+4] ) != string::npos ) {
pos += 4;
return true;}}
return false;}
s141::s141( const s945* pf, const wstring& s77, size_t& pos, const s1695& s1759 )
: s198( s132 ), obj( pf ), s1082( pos + (pf ? pf->s949():0), 0 ), s1081( (s945*)pf ){
size_t s68 = s77.find_first_not_of( L" \n\r\t", pos );
if( s68 == string::npos ) {
if( s1759.s1744 )
s198 = s132;
else {
s16* s968 = new s16(wstring( 28, L' ' ) + L"|^|" );
s968->s30( L"empty array item: " + s77.substr( pos - 10, 20 ) );
throw s968;}}
else if( s77[s68] == L'{' ) {
size_t s74, s75;
s54( s77, s68, L'{', L'}', s74, s75, true );
pos = s75+1;
obj.s154( s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 ), s1759 );
s198 = s133;}
else {
pos = s68;
if ( s88.find( s77[pos] ) != string::npos ) {
s172( s77, pos, s77[pos], str, s1759.s151 );
s198 = s139;}
else if ( s77[pos] == L'[' ) {
s178( (s945*)s1081, s77, pos, s162, s1759 ); 
s198 = s135;}
else {
s198 = s1550( s77, pos, s163, s1759 );
if( s198 != s132 )
(void)0;
else if( s183( s77, pos, b ) )
s198 = s137;
else if( s184( s77, pos ) )
s198 = s138;
else
s198 = s176( s77, pos, str, s1759 );;}}
s1082.second = pf ? pos - 1 + pf->s949() : 0;}
s141::s141( double d, s131 v ) 
: s198( v ), obj( NULL ), s163( d ) {
assert( v == s136 || v == s140 );}
bool s141::s1009( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1082.first || s1081.s13() )
return false;
f = s1081->Path();
s1081->s1005( s, s1082.first, s1082.second, line );
return true;}
const s143& s141::s166() const{
if( s198 == s133 )
return obj;
throw new s16( L"NQJ value: wrong variant" );}
const std::vector<s142>& s141::s167() const{
if( s198 == s135 )
return s162;
throw new s16( L"NQJ value: wrong variant" );}
double s141::s168() const{
if( s198 == s136 )
return s163;
throw new s16( L"NQJ value: wrong variant" );}
int s141::s56() const{
if( s198 == s140 )
return (int)s163;
throw new s16( L"NQJ value: wrong variant" );}
bool s141::s728() const{
if( s198 == s137 )
return b;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s141::s169() const{
if( s198 == s134 || s198 == s139 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s141::s865() const{
if( s198 == s139 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
std::wstring s141::s857() const{
if( s198 == s139 )
return str.substr( 1, str.size() - 2 );
throw new s16( L"NQJ value: wrong variant" );}
void s143::s154( const wstring& s77, const s1695& s1759 ){
s144.clear();
size_t s68;
size_t pl = s77.find_first_not_of( L" \n\r\t" );
if( pl == string::npos )
return;
if( s77[pl] == L'{' )
s68 = s77.find_first_not_of( L" \n\r\t", pl + 1 );
else
s68 = pl;
while( true ) {
wstring s76;
s180( s77, s68, s76, s1759.s151 );
size_t pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl == string::npos || s77[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
s68 = pl + 1;
s144.insert( make_pair( s76, new s141( src, s77, s68, s1759 ) ) );
pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl != string::npos && s186.find( s77[pl] ) == string::npos ) 
throw new s16( L"wrong nqj syntax: missed separator or closing brace: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
if( pl != string::npos )
pl = s77.find_first_not_of( L" \n\r\t", pl+1 );
if( pl == string::npos )
break;
s68 = pl;}}
bool s143::operator==( const s143& r )  const{
bool s685 = true;
for( auto it = s144.begin(); it != s144.end(); ++it ) {
auto it1 = r.s144.find( it->first );
if( it1 == r.s144.end() || !( *( it->second ) == *( it->second ) ) ) {
s685 = false;
break;}}
return s685;}
void s143::s155( wostream* pd, bool s151 ) const{
*pd << L"{\n";
for( auto it = s144.begin(); it != s144.end(); ++it ) {
if( it != s144.begin() )
*pd << L",\n";
s181( pd, it->first, s151 );
*pd << L" : ";
it->second->s155( pd );}
*pd << L"\n}";}
void s141::s155( wostream* pd, bool s151 ) const{
if( s198 == s133 )
obj.s155( pd, s151 );
else if( s198 == s135 )
s179( pd, s162, s151 );
else if( s198 == s134 )
s181( pd, str, s151 );
else if( s198 == s139 )
s181( pd, str, true );
else if( s198 == s136 )
*pd << to_wstring( s163 );
else if( s198 == s140 )
*pd << to_wstring( (int)s163 );
else if( s198 == s137 )
*pd << ( b ? L"true" : L"false" );
else if( s198 == s138 )
*pd << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool s143::s156( const wstring& s152 ) const{
if( s144.find( s152 ) != s144.end() )
return true;
return false;}
void s143::s157( const wstring& s152, vector<s9<s141>>& s153 ) const{
auto i = s144.equal_range( s152 );
if( i.first == i.second )
return;
for( auto it = i.first; it != i.second; ++it )
s153.push_back( it->second );}
const s142 s143::s158( const wstring& s152 ) const{
if( s144.count( s152 ) > 1 )
throw new s16( L"multiple values: " + s152, (uint32_t)s149 );
auto s685 = s144.find( s152 );
return s685->second;}
void s143::s159( const std::wstring& s76, s142 s349, s145 ap ){
if( s144.find( s76 ) != s144.end() ) {
if( ap == s146 )
throw new s16( L"Field already exists: " + s76, (uint32_t)s16::s17::s21 );
else if( ap == s148 )
return;
else if( ap == s147 )
s144.erase( s76 );}
s144.insert( make_pair( s76, s349 ) );}
void s143::s1631( const std::wstring& s76 ){
if( s144.find( s76 ) == s144.end() )
throw new s16( L"Attribute doesn't exist: " + s76, (uint32_t)s16::s17::s21 );
s144.erase( s76 );}
void s143::s160( vector<pair<wstring, s9<s141>>>& s153 ) const{
for( auto it = s144.begin(); it != s144.end(); ++it ) 
s153.push_back( *it );}
void s143::s161( wostream* pd, int s197 ) const{
for( auto it = s144.begin(); it != s144.end(); ++it ) {
*pd << FILL(s197) << it->first << " : " << endl;
it->second->s161( pd, s197 + 2 );}}
void s141::s161( wostream* pd, int s197 ) const{
if( s198 == s133 )
obj.s161( pd, s197 + 2 );
else if( s198 == s135 ) {
for( size_t n = 0; n < s162.size(); ++n ) {
s162[n]->s161( pd, s197 );
if( n < s162.size() - 1 )
*pd << endl;}}
else if( s198 == s134 )
*pd << FILL( s197 ) << str << endl;
else if( s198 == s136 )
*pd << FILL( s197 ) << s163 << endl;
else if( s198 == s140 )
*pd << FILL( s197 ) << s163 << endl;
else if( s198 == s137 )
*pd << FILL( s197 ) << b << endl;
else if( s198 == s138 )
*pd << FILL( s197 ) << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool operator==( const std::vector<s9<s141>>& l,
const std::vector<s9<s141>>& r ){
if( l.size() == r.size() ) {
for( size_t n = 0; n < l.size(); ++n )
if( !(*( l[n] ) == *( r[n] ) ) )
return false;
return true;}
return false;}
s131 s1709::s1550( const std::wstring& s77, size_t& pos, double& s153 ){
return s6::s1550( s77, pos, s153, conf );}
} // namespace s6
using namespace s6;
namespace transd {
namespace s7 {
s928 s1554		= 0x80000000;
s928 s1395        = s1554 - 1;
s928 s1396       = s1554 - 2;
s928 s1397       = s1554 - 3;
s928 s1394      = s1554 - 4;
s928 s1393						= s1554 - 8;
s928 s1398    = s1554 - 9;
s928 s1399					= s1554 - 10;
DEFCONST s420 = L"typeMembers";
DEFCONST s421 = L"typeMember";
DEFCONST s422 = L"typeMethods";
DEFCONST s423 = L"typeMethod";
DEFCONST s424 = L"members";
DEFCONST s425 = L"member";
DEFCONST s426 = L"methods";
DEFCONST s427 = L"method";
DEFCONST s428 = L"@init";
DEFCONST s429 = L"@initCall";
DEFCONST s1629 = L"@to-String";
DEFCONST s430 = L"thisPtr";
DEFCONST s431 = L"virtual";
DEFCONST s432 = L"override";
DEFCONST s833 = L"return";
DEFCONST s433 = L"continue";
DEFCONST s434 = L"break";
DEFCONST s435 = L"throw";
DEFCONST s765 = L"else";
DEFCONST s749 = L"elsif";
DEFCONST s795 = L"to";
DEFCONST s436 = L"true";
DEFCONST s437 = L"false";
DEFCONST s832 = L"null";
DEFCONST s940 = L"->";
DEFCONST s1140 = L"const";
DEFCONST s1356 = L"@new";
DEFCONST s1391 = L"stdin";
DEFCONST s1392 = L"stdout";
DEFCONST s1601 = L"this";
DEFCONST s2139 = L"locals:";
DEFCONSTI s866 = -1;
DEFCONSTI s2238 = -2;
DEFCONSTI s440 = -3;
DEFCONSTI s438 = -100;
DEFCONSTI s439 = -101;
DEFCONSTI s441 = 1;
DEFCONSTI s442 = 0;
DEFCONSTI s868 = 0x80000000;
DEFCONSTI s1747 = 0x80000001;
DEFCONSTI s867 = 0;
DEFCONSTI s1199 = 1;
DEFCONST s1413 = L":Number";
DEFCONST s1524 = L":Integer";
DEFCONST s1411 = L":IterableForw";
DEFCONST s1410 = L":IterableBidir";
DEFCONST s1412 = L":IterableRand";
DEFCONST s1409 = L":IStream";
DEFCONST s1414 = L":OStream";
DEFCONST s1408 = L":IOStream";
DEFCONST s443 = L"import";
DEFCONST s444 = L"input";
DEFCONST s445 = L"output";
DEFCONST s446 = L"export";
DEFCONST s447 = L"opaque";
DEFCONST s448 = L"public";
DEFCONST s449 = L"private";
DEFCONST s450 = L"secure";
DEFCONST s451 = L"class";
DEFCONST s452 = L"module";
DEFCONST s2161 = L"interface";
DEFCONST s453 = L"AssemblyDescription";
DEFCONST s454 = L"ProgramText";
DEFCONST s455 = L"Export";
DEFCONST s456 = L"Require";
DEFCONST s2169 = L"TypeAlias";
DEFCONST s457 = L".td";
DEFCONST s946 = L".tsd";
DEFCONST s459 = L"MainModule";
DEFCONST s458 = L"_start";
DEFCONST s460 = L"asm" + s457;
DEFCONST s461 = L"@ex";
DEFCONST s1374 = L"@it";
DEFCONST s462 = L"@idx";
DEFCONST s1982 = L"@row";
DEFCONST s769 = L"@pars";
DEFCONST s803 = L"@obj";
DEFCONST s829 = L"@numArgs";
DEFCONST s1572 = L"@progArgs";
DEFCONST s1124 = L"@sourceFile";
DEFCONST s1373 = L"@OS_Type";
DEFCONST s467 = L"source";
DEFCONST s463 = L"objectType";
DEFCONST s464 = L"moduleType";
DEFCONST s465 = L"@name";
DEFCONST s466 = L"entryPoint";
DEFCONST s468 = L"perm";
DEFCONST s469 = L"extends";
DEFCONST s739 = L"packages";
DEFCONST s470 = L"searchDirs";
DEFCONST s936 = L"@attrs";
DEFCONST s1983 = L"restrictions";
DEFCONST s2160 = L"@impl";
DEFCONST s1989 = L"FileRead";
DEFCONST s1990 = L"FileWrite";
DEFCONST s1988 = L"FileAll";
DEFCONST s1991 = L"FuncEval";
DEFCONST s1992 = L"FuncStartProcess";
DEFCONST s1993 = L"RestrictionsAll";
DEFCONST s1994 = L"allow";
DEFCONST s1997 = L"noResult";
DEFCONST s1996 = L"noExecute";
DEFCONST s1995 = L"noCompile";
DEFCONST s915 = L"is";
DEFCONST s914 = L"index type";
DEFCONST s916 = L"value type";
DEFCONST s418 = L"#lang transd";
DEFCONST s1106 = L"#format tsd";
s928 s1300						= 103;
s928 s923						= 110;
s928 s1299				=	123;
s928 s1129						= 124;
s928 s924 			=	125;
s928 s918			= 201;
s928 s1107				= 204;
s928 s919					= 210;
s928 s1108					= 304;
s928 s1109				= 404;
s928 s1110				= 504;
s928 s920					= 510;
s928 s921			= 511;
s928 s922					= 610;
s928 s1126							= 710;
s928 s1127					= 711;
s928 s1366		= 804;
s928 s1367				= 904;
s928 s1368				= 1004;
s928 s1597					= 1024;
s928 s1128					= 1124;
s928 s1296				= 1203;
s928 s1297				= 1210;
s928 s1298				= 1224;
s928 s1667		= 1304;
s928 s1668						= 1404;
s928 s1378						= 1410;
s928 s1669						= 1504;
s928 s1376						= 1510;
s928 s1377					= 1511;
s928 s1670				= 1604;
s928 s1522					= 1610;
s928 s1523			= 1611;
s928 s1687			= 1704;
s928 s1555			= 1710;
s928 s1599	= 1715;
s928 s1904	= 1716;
s928 CLObjectVal_ctor1				= 1810;
s928 s1598				= 1824;
s928 s1688					= 1904;
s928 s1702				= 2025;
s928 s1892				= 2103;
s928 s1937				= 2210;
s928 s1936					= 2310;
s928 s2159			= 2410;
s928 CLTDFilter_ctor1				= 2504;
s928 s2208					= 2510;
s928 s2219						= 2603;
s928 s2217						= 2610;
s928 s2218						= 2624;
set<wstring> s1123 = { s1124, s1391, s1392, s1373, s833, s433,
s434, s435, s765, s749, s795, s436, s437, s832, s940, s1140,
s1356, s1391, s1392, s1601, L"and", L"or"
};
} // namespace s7
std::wstring s229[] = { L"value", L"function", L"object", L"name" };
const wstring s230 = L"if";
const wstring s231 = L"set";
const wstring s232 = L"sum";
const wstring s233 = L"with";
const wstring s234 = L"mul";
const wstring s235 = L"div";
const wstring s236 = L"dif";
const wstring s237 = L"eq";
const wstring s238 = L"less";
const wstring s239 = L"greater";
const wstring s240 = L"leq";
const wstring s241 = L"geq";
const wstring s242 = L"neq";
const wstring s243 = L"and";
const wstring s244 = L"or";
const wstring s2078 = L"first";
const wstring s245 = L"dcmp";
const wstring s246 = L"dcmpr";
const wstring s247 = L"mod";
const wstring s248 = L"sqrt";
const wstring s249 = L"abs";
const wstring s250 = L"pow";
const wstring s1945 = L"textin";
const wstring s251 = L"textout";
const wstring s252 = L"lambda";
const wstring s253 = L"proc";
const wstring s255 = L"while";
const wstring s256 = L"eval";
const wstring s257 = L"try";
const wstring s258 = L"catch";
const wstring s259 = L"throw";
const wstring s254 = L"through";
const wstring s260 = L"for";
const wstring s261 = L"run-file";
const wstring s772 = L"load-file";
const wstring s821 = L"import-module";
const wstring s1620 = L"unload-file-modules";
const wstring s1317 = L"unload-module";
const wstring s751 = L"has-field";
const wstring s818 = L"tql";
const wstring s759 = L"substr";
const wstring s852 = L"ret";
const wstring s853 = L"sort";
const wstring s900 = L"exit";
const wstring s1316 = L"to-file";
const wstring s1428 = L"any";
const wstring s1427 = L"all";
const wstring s1944 = L"pipe";
const wstring s2211 = L"filter";
const wstring s1562 = L"lout";
const wstring s1943 = L"lin";
const wstring s1616 = L"read-tsd-file";
const wstring s1615 = L"load-from-object";
const wstring s1619 = L"start-process";
const wstring s1617 = L"rebind";
const wstring s1618 = L"sleep";
const wstring s1614 = L"diag";
const wstring s1886 = L"rand";
const wstring s2232 = L"yield";
const s141 s265(L"AttrNA");
s263::s263( s1905& s, const s141* s6, s263* s2108 )
: s1053( (s141*)s6 ), s2107( s2108 ), s2112( NULL ){
s1003( s );}
s263::s263( s1905& s676, const s6::s141& s296, s263* s592 )
: s1674( s676 ), s1053( (s141*)&s296 ), s2107( NULL ), s2112( s592 ){
if( s296.s164() == s134 ) {
wstring s = s296.s169();
s1003( s );}
else if( s296.s164() == s139 ) {
wstring s = //L"\"" +
s296.s169();// +
s284( s );}
else if( s296.s164() == s133 ) {
basic_stringstream<wchar_t> ss;
s296.s155( &ss, true );
if( 0 ) {
s284( ss.str() );}
else {
src = ss.str();
s283( s296.s166() );}}
else if( s296.s164() == s136 )
s284( to_wstring( s296.s168() ) );
else if( s296.s164() == s140 )
s284( to_wstring( s296.s56() ) );
else if( s296.s164() == s137 )
s284( /*to_wstring( s296.s728() )*/ s296.s728() ? L"true" : L"false" );
else if( s296.s164() == s135 ) {
basic_stringstream<wchar_t> ss;
s296.s155( &ss );
if( s1674.find( L"UVector" ) == 0 ) {
s284( L"UVector" + ss.str() );
s1674 = s4::s52( s1674.substr( 7 ), s48 );}
else
s284( ss.str() );}
else if( s296.s164() == s132 )
s284( L"" );
else
throw new s16( L"Unhandled nqj variant: " + to_wstring( s296.s164() ) );}
s263::s263( const s6::s143& s133 )
: s2107( NULL ), s2112( NULL ){
s283( s133 );}
s263::~s263(){
reset();}
void s263::reset(){
s281.clear();
s266.clear();
s277 = s1674 = s280 = src = L"";}
void s263::s1003( s1905& s ){
size_t pos = 0;
wstring s1184 = L"\"'`-+[{<";
if( s.empty() ) {
s284( s );}
else if( s[pos] == L'(' )
s282( s );
else if( iswalpha( s[pos] ) || s[pos] == L'_' || s[pos] == L'@' || s[pos] == L':' ) {
if( s.find( L'(' ) != string::npos || s.find( L"true" ) == 0 
|| s.find( L"false" ) == 0)
s284( s );
else
s285( s );}
else if( iswdigit( s[pos] ) || s1184.find( s[pos] ) != string::npos ) {
wstring s77;
s77 = s52( s, s48 );
s284( s77 );}
else
throw new s16( L"Unknown string content: " + s );}
void s263::s282( s1905& s77 ){
src = s77;
size_t pos = 0;
vector<wstring> s677;
s288( s77, pos, s677 );
if( s677.empty() )
return;
s279 = s226;
size_t s68 = 0;
s280 = s287( s677[0], s68 );
for( size_t n = 1; n < s677.size(); n++ )
s281.insert( make_pair( to_wstring( n - 1 ), new s263( s677[n], s1053, this ) ) );}
void s263::s284( s1905& s77 ){
src = s77;
s279 = s225;
s280 = s77;}
void s263::s285( s1905& s77 ){
src = s77;
s279 = s228;
s280 = s77;}
void s263::s283( const s6::s143& s133 ){
s1674 = s302( s133, s7::s465 );
s279 = s227;
vector<pair<wstring, s142>> s144;
s133.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s286( s144[n].first, *s144[n].second );}}
void s678( wstring& s ){
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
void s263::s289( s6::s143& obj, size_t s2194 ){
wstring s679 = s4::s52( s302( obj, s7::s465 ), s48 );
wstring s658 = s679;
s678( s658 );
if( s658.empty() )
throw new s16( L"Nameless blocks are forbidden." );
if( s658 != s679 )
obj.s159( s7::s465, s142(new s141( s658 )), s143::s147 );
if( s658 == s1674 ) { // partial definition
vector<pair<wstring, s142>> s144;
obj.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n )
s286( s144[n].first, *s144[n].second );}
else {
wstring s2199 = s658;
s263* s2196 = new s263( obj );
s2196->s269( s2191, s141( (double)s2194, s140 ) );
s281.insert( make_pair( s2199, s2196 ) );}}
void s263::s286( s263* node ){
s281.insert( make_pair( node->s299(), node ) );}
void s263::s286( s1905& s76, const s141& s349 ){
s281.insert( make_pair( s76, new s263( s76, s349, this ) ) );}
void s263::s290( s262* s300, size_t s301 /*= 0*/ )
{
s275::iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
if( it->second->s297() == s227 ) {
if( s301 == 0 ) {
it->second->s290( s300, 1 );}
else {}}}}
bool s263::s156( s1905& s76 ) const{
if( s281.find( s76 ) == end( s281 ) )
return false;
return true;}
const s263* s263::s292( s1905& s76 ) const{
size_t s684 = s281.count( s76 );
if( s684 > 1 )
throw new s16( L"multiple values: " + s76, (uint32_t)s149 );
if( s684 == 1 ) {
auto s685 = s281.find( s76 );
return s685->second.s15<s263*>();}
throw new s16( L"node not found: " + s76, (uint32_t)s16::s17::s23 );}
void s263::s288( s1905& s77, size_t& pos, vector<wstring>& s153 ){
size_t s74, s75;
s54( s77, pos, L'(', L')', s74, s75, true );
if( s74 != pos || s75 == string::npos )
throw new s16( L"Parentheses don't match near \"" + 
s77.substr( 0, 40 ) + L"...\"" );
pos = s75;
size_t s68 = s77.find_first_not_of( s48, s74 + 1 );
if( s77[s68] == L')' )
return;
size_t s683 = s68;
wstring s680;
while( s683 < s75 ) {
s68 = s77.find_first_not_of( s48 + L")", s683 );
if( s68 >= s75 )
break;
size_t s681, s682;
if( s77[s68] == L'(' ) {
s54( s77, s68, L'(', L')', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else if( s77[s68] == L'[' ) {
s54( s77, s68, L'[', L']', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else if( s77[s68] == L'{' ) {
s54( s77, s68, L'{', L'}', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Curly brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else if( s4::s88.find ( s77[s68] ) != string::npos ) {
wchar_t _q = s77[s68];
s55( s77, s68, _q,	s681, s682 );
if( s682 == string::npos )
throw new s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else if( iswdigit( s77[s68] ) ) {
s682 = s77.find_first_of( s48 + L")", s68 );
s680 = s77.substr( s68, s682 - s68 );
s683 = s682;}
else if( iswalpha( s77[s68] ) || s77[s68] == L'_' || s77[s68] == L'@' ) {
s682 = s77.find_first_of( s48 + L")", s68 );
size_t pl = s77.find( L'<', s68 );
if( pl < s682 ) {
s54( s77, pl, L'<', L'>', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Angle brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
if( s77[s682+1] == L'(' ) {
s54( s77, pl, L'(', L')', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );}
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else {
pl = s77.find( L'(', s68 );
if( pl < s682 ) {
s54( s77, pl, L'(', L')', s681, s682, true );
if( s682 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else {
s680 = s77.substr( s68, s682 - s68 );
s683 = s682;}}}
else {
s682 = s77.find_first_of( s48 + L")", s68 );
s680 = s77.substr( s68, s682 - s68 );
s683 = s682;}
s153.push_back( s680 );}}
wstring s263::s287( const std::wstring& s77, size_t &pos ){
size_t s1729 = s77.find( L"<" );
if( s1729 != string::npos && s1729 > 0 ) {
return s77;}
wstring s685;
if( s77[pos] == L'+' && s77[pos + 1] != L'=' )
s685 = s232;
else if( s77[pos] == L'-' && s77[pos + 1] != L'=' && s77[pos + 1] != L'|')
s685 = s236;
else if( s77[pos] == L'*' && s77[pos + 1] != L'=' )
s685 = s234;
else if( s77[pos] == L'/' && s77[pos + 1] != L'=' )
s685 = s235;
else if( s77[pos] == L'^' && s77[pos + 1] != L'=' )
s685 = s250;
else if( s77[pos] == L'=' && s77[pos + 1] != L'=' )
s685 = s231;
else if( s77[pos] == L'<' && s77[pos + 1] != L'=' )
s685 = s238;
else if( s77[pos] == L'>' && s77[pos + 1] != L'=' )
s685 = s239;
else if( s77[pos] == 955 /*L'λ'*/ )
s685 = s252;
if( s685.size() ) {
if( s77.size() > pos + 1 && s77.find_first_of( s48 + L")", pos ) != pos + 1 )
throw new s16( L"1: unknown syntax: " + s77.substr(pos, 40),
(uint32_t)s16::s17::s20 );
pos += 1;
return s685;}
if( s77.substr( pos, 2 ) == L"+=" )
s685 = L"sumeq";
else if( s77.substr( pos, 2 ) == L"-=" )
s685 = L"difeq";
else if( s77.substr( pos, 2 ) == L"*=" )
s685 = L"muleq";
else if( s77.substr( pos, 2 ) == L"/=" )
s685 = L"diveq";
else if( s77.substr( pos, 2 ) == L"^=" )
s685 = L"poweq";
else if( s77.substr( pos, 2 ) == L"<=" )
s685 = L"leq";
else if( s77.substr( pos, 2 ) == L">=" )
s685 = L"geq";
else if( s77.substr( pos, 2 ) == L"==" )
s685 = L"eq";
else if( s77.substr( pos, 2 ) == L"!=" )
s685 = L"neq";
else if( s77.substr( pos, 2 ) == L"-|" )
s685 = s1944;
if( s685.size() ) {
if( s77.size() > pos + 2 && s77.find_first_of( s48 + L")", pos ) != pos + 2 )
throw new s16( L"2: unknown syntax: " + s77.substr( pos, 40 ), 
(uint32_t)s16::s17::s20 );
pos += 2;
return s685;}
size_t s683 = s77.find_first_of( s48 + L")", pos );
s685 = s77.substr( pos, s683 - pos );
pos = s683;
return s685;}
std::wstring s263::s298() const{
return (s277.size() ? s277 + L"::" : L"") + s1674;}
wstring s263::s295( const s6::s143& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s156( s7::s464 ) )
return obj.s158( s7::s464 )->s169();
return def;}
std::wstring s263::s302( const s6::s143& obj,
const std::wstring& s303,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s156( s303 ) )
return obj.s158( s303 )->s169();
return def;}
const s6::s141& s263::s268( size_t s2106 ) const{
auto it = s266.find( s2106 );
if( it != s266.end() )
return it->second;
return s265;}
const s6::s141& s263::s2116( size_t s2106 ) const{
auto it = s266.find( s2106 );
if( it == s266.end() ) {
if( s2107 )
return s2107->s2116( s2106 );
else
return s265;}
return it->second;}
void s263::s269( size_t s2106, const s6::s141& s267 ){
s266[s2106] = s267;}
void s263::s2123( const s263& s701 ){
for( auto i : s701.s266 )
s266.insert( make_pair( i.first, i.second ) );}
void s263::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s1674 << L" : " << s229[s279] << endl;
buf << s4::fill_n_ch( L' ', s197 ) << L" " << s280 << endl;
map<wstring, s947>::const_iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << it->first << endl;
it->second->s304( pd, s197 + s419 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1105 s1014;
void s1105::s971( const std::wstring& s78 ){
++s997;
s26.push_back( Msg( s78 ) );
wcout << s78;}
void s1105::s971( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
++s997;
s26.push_back( Msg( s78, U16(func), U16(file), line, s1041 ) );}
void s1105::s973( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s78, U16(func), U16(file), line, s1044 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1085 = {
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
TDException::TDException( uint32_t s1015, uint32_t cat, const s263* ast_ )
: s16( L"", s1015 ), stage (Stage::s1031 ), category( cat ), s701( (s263*)ast_ ){}
TDException::TDException( Stage stg, uint32_t s1015, uint32_t cat, const s263* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s701( (s263*)ast_ ){
if( category ) {
s30( L"error code: " + std::to_wstring( s1015 ) );
s30( s994[category] + L":" );}}
TDException::TDException( uint32_t s1015, uint32_t cat, const s263* ast_, const std::wstring& s78 )
: s16( s78, s1015 ), stage (Stage::s1031 ), category( cat ), s701( (s263*)ast_ ){
if( category ) {
s30( s994[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1087( e.s1087 ), s701( e.s701 ){}
TDException* TDException::s1000( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s197 ) const{
wstring src;
if( s701.s14() )
src = s1912( *s701 );
wstring s = L"Error ";
if( id ) {
wstring s1077;
if( (uint32_t)stage )
s1077 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1077 += std::to_wstring( id );
s += s1077;}
if( (uint32_t)stage ) {
s += L" during " + s1085[(uint32_t)stage];}
s += src + L"\n";
return wstring( s197, L' ' ) + s + s16::Msg( s197 + 2 );}
wstring TDException::s2170( size_t idx ) const{
if( s26.size() < idx )
return L"";
auto it = begin( s26 );
std::advance( it, idx );
return *it;}
wstring TDException::s1912( const s263& s701 ){
size_t s1033 = 0;
wstring file, s1083, s685;
if( s701.Nqj() && s701.Nqj()->s1009( file, s1083, s1033 ) ) {
wstring s1079 = std::to_wstring( s1033 ) + L": '" + s1083 + L"'";
s685 = L"\n  in file: " + file + L"\n  on line " + s1079;}
if( !s701.s291().empty() )
s685 += L"\n  object: '" + s701.s291() + L"', ";
if( !s701.Src().empty() )
s685 += L"code: '" + s701.Src() + L"', ";
return s685;}
s927::s927( s16& e, const s263& s701, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1033 = 0;
wstring file, s1083, src;
wstring	s78 = L"Error during ";
if( s701.Nqj()->s1009( file, s1083, s1033 ) ) {
src = std::to_wstring( s1033 ) + L": '" + s1083 + L"'";
s78 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s78 += L"object: '" + s701.s291() + L"'; code: " + s701.Src();}
s30( s78 );
s1014.s971( Msg( 2 ) );}
s935::s935( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s994 = {
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
bool s656( const wstring& s, bool s714 ){
bool fail = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1123.find( s ) != s7::s1123.end() )
continue;
fail = true;
break;}
if( fail && s714 )
throw new s16( L"illegal identifier: " + s );
return (!fail);}
} // namespace tdlang
s926 s993;
s271::~s271(){}
s483* s271::s496()
{	throw std::logic_error( "1: not implemented" );}
const s483* s271::s503() const
{	throw std::logic_error( "2: not implemented" );}
s486 s271::s497( s483** s274, size_t s498 )
{	throw std::logic_error( "3: not implemented" ); }
s271* s271::s335( s591* s2057, s272* impl ) const
{	throw std::logic_error( "4: not implemented" ); }
void s271::s500( const s272* s587, bool b ) {
(void)0;}
inline bool
s271::s501( const s483* s502 ) const{
return ( s502->s352() == s352() );}
inline bool
s271::s1541( s1061 s619 ) const{
return s300->TR().s1534( s352(), s619 );}
const s813& 
s271::s1196() const {
return s300->TR().s1013( s493 ); }
s271::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s271::operator int() const { throw std::logic_error( "6: not implemented" ); }
s271::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s271::to_wstring( uint32_t s1565 ) const { throw std::logic_error( "8: not implemented" ); }
s1322 s271::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s271::to_null() { s1679( s7::s1747 ); }
void s271::s1333( const s263& ast_, s262* s300, s272* obj,
s1905& s334, vector<s271*>& s153 ){
assert( ast_.s291().size() );
size_t pos = 0;
vector<wstring> s677;
wstring s77;
if( ast_.s291().find( '(' ) == string::npos )
s77 = L"(" + ast_.s291() + L")";
else
s77 = ast_.s291();
if( s77.empty() )
return;
/*wstring s = s77;
if( s[0] != L'(' )
s = L"(" + s + L")";*/
s263::s288( s77.substr( s77.find( L"(" ) ), pos, s677 );
if( s677.empty() )
return;
for( size_t n = 0; n < s677.size(); n++ ) {
s263* ast1 = new s263( s677[n], ast_.Nqj(), (s263*)&ast_ );
s153.push_back(
s271::s504( *ast1, s300, obj, s334, false )
);}}
s271* s271::s504( const s263& s701, s262* s300, s272* obj,
s1905& s334, bool s2177 ){
TDException s968( s7::s1702, s932, &s701 );
s271* p;
if( s701.s297() == s225 ) {
wstring s349 = s701.s291();
bool quot = s88.find( s349[0] ) != string::npos;
size_t ppl = s349.find( L"(" );
bool lastp = s349.back() == L')';
s1905& ownerName = s701.s268( s2100 ).s169();
if( ( s701.s268( s2101 ).s169() == L"CallSite" ) &&
( ownerName != s252 ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s347 = s349.substr( 0, ppl );
wstring s77 = L"(" + s7::s1356 + L"<" + s347 + L"> " + s349.substr( ppl + 1 );
s947 tast = new s263( s77, s701.Nqj(), (s263*)&s701 );
p = s591::s1119( *tast, s300, obj, s334, s2177 );}
else {
p = s300->TR().s518( s701, obj, s334 );
if( !p )
throw s968.s1000( L"unrecognized type of the object: " + s701.s291() );
((s483*)p)->s506( s701.s299() );}}
else if( s701.s297() == s226 )
p = s591::s1119( s701, s300, obj, s334, s2177 );
else if( s701.s297() == s228 )
p = new s371( s701.s291(), s300 );
else //if( s701.s297() == s227 )
throw new s16( L"unexpected node type" );
return p;}
s271* 
s271::s1018( s262* s300, s271* par, s272* s588, s591* s215,
s1905& s334, bool proc ){
s271* s685;
if( par->s494() == s477 ) {
s490 cs = new s561( *((s561*)par) );
s685 = s591::s600( cs, s300, s588, s215, s334, proc );
((Transd*)s685)->s500( s588, proc );}
else {
par->s500( /*s588*/s215 ? s215 : s588, proc );
return par;}
return s685;}
s485
s271::s1017( s1905& s77, const s263* ast_, s262* s300, s272* s588 ){
s947 ast1;
if( ast_ )
ast1 = new s263( s77, ast_->Nqj(), (s263*)ast_ );
else
ast1 = new s263( L"", s77 );
s485 pr = s271::s504( *ast1, s300, s588, s588->s298() );
if( pr->s494() == s475 ) {
pr->s500( s588 );
pr = pr.s15<s371*>()->s377();}
s485 s685 = s271::s1018( s300, pr, s588, NULL, s588->s298(), false );
return s685;}
const wstring& 
s271::s353() const{
return s300->TR().s804( s352() );}
void s271::s351( s813::s737 type ){
s493 = type;}
s484* s1120( s505& m, const wstring& s152 ){
if( m.count( s152 ) > 1 )
throw new s16( L"multiple values: " + s152, (uint32_t)s16::s17::s21 );
auto s685 = m.find( s152 );
if( s685 == m.end() )
throw new s16( L"no such key: " + s152, (uint32_t)s16::s17::s23 );
return s685->second;}
void s670( const std::wstring& s, std::wstring& s1112, std::wstring& s601 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1112 = s.substr( 0, pl );
s601 = s.substr( pl + 2 );}
s483::s483( const s483& r ) 
: s271( r ), ns( r.ns ){}
s483::~s483(){}
s483* s483::s496(){
return this;}
void s483::s1960( s1905&) { throw std::logic_error( "from_wstring: not implemented" ); }
wstring s483::s298() const { return ns->s298(); }
wstring s483::s834() const { return ns->s834(); }
wstring s483::s2171() const { return ns->s834(); }
s483* s483::s1536( const s483* p ) const{
if( s352() == p->s352() ) {
s483* s685 = (s483*)p->s335(0,0);
return s685;}
throw new s16( L"no conversion from '" + s353() + L"' to '" + p->s353() + L"'" );}
s483* s483::s355( s272* s588, const std::vector<s1061>& vt ) const{
assert(0);
return 0;}
s1061 s483::s1188( s1905& s1553, const vector<s485>& l ) const{
throw std::logic_error( "9: not implemented" );}
s591* 
s483::s1685( s1905& s676, s591* s215, s272* s1672,
s561* cs ) const{
if( s676 == L"cp" ) {
return new s1681( s300, (s272*)this, s215, &s483::s1703, cs->s602(),
L"cp",	0, cs->s603(), cs->s2183() );}
else if( s676 == L"exec" ) {
return new s1681( s300, s1672, s215, &s483::s1894, cs->s602(), L"exec",
0, cs->s603(), cs->s2183() );}
else if( s676 == L"_META_type" ) {
return new s1681( s300, s1672, s215, &s483::s1938, cs->s602(),
L"_META_type", Types.String,	cs->s603(), cs->s2183() );}
return NULL;}
s483* s483::s1703( s483** s274, size_t s498 ){
return (s483*)s335(0,0);}
s483* s483::s1894( s483** s274, size_t s498 ){
return s497( s274, s498 );}
s483* s483::s1938( s483** s274, size_t s498 ){
return new s359( s300, s353() );}
s483* s483::s1895( s483** s274, size_t s498 ){
return s1896( s274, s498 );}
s483* s483::s1896( s483** s274, size_t s498 ){
throw std::logic_error( "10: not implemented" );}
void s483::s1935( Stream* s1934 ) const{
s1934->s1480( to_wstring() );}
void s483::s1959( Stream* s1934 ){
wstring s;
s1934->s1461( s, string::npos );
s1960( s );}
vector<wstring> s521::s525 = { s7::s446, s7::s444,
s7::s447, s7::s445 };
s1::s9<s526> s557 = new s526();
size_t s967( const vector<s813::s893>& vt ){
size_t s685 = 0;
for( auto i : vt )
s685 = ( s685 << 7 ) ^ i;
return s685;}
size_t s491::s1056( s1905& s, size_t& pos, s813::Cont& s153 ){
size_t s68 = pos;
size_t s685 = 0;
if( s[s68] == L' ' )
s68 = s.find_first_not_of( s4::s48, s68 );
while( s68 < s.size() && s[s68] != L'>' && s[s68] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s68 );
wstring stype = s4::s52( s.substr( s68, pl - s68 ), s4::s48 );
s1061 s1091 = get( stype /*+ L"()"*/ )->s352();
s153.push_back( s1091 );
pl = s.find_first_not_of( s4::s48, pl );
s813::Cont s1069;
size_t s1054 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1054 = s1056( s, ++pl, s1069 );}
else if( s[pl] == L',' ) {
s1054 = 0;}}
s153.push_back( ( s813::s893 ) s1054 );
s153.insert( end( s153 ), begin( s1069 ), end( s1069 ) );
s685++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s48, pl );
pos = s68 = pl;}
pos++;
return s685;}
wstring s1157( const s813::Cont& s1064, size_t& idx, s491& s910 ){
wstring s685 = s910.s804(s1064[idx++]);
size_t n = (size_t)s1064[idx++];
if( n && s685.back() != L'>' ) {
s685 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s685 += ( k ? L" " : L"" ) + s1157( s1064, idx, s910 );}
s685 += L">";}
return s685;}
wstring s491::s1012( const s813::Cont& s1064 ){
assert( s1064.size() );
if( s1064.size() == 1 )
return  s1096[s1064[0]] + L"< 0 >";
size_t idx = 0;
wstring s685;
while( idx < s1064.size() ) {
s685 += s1157( s1064, idx, *this );
if( idx < s1064.size() )
s685 += L" ";}
return s685;}
wstring s491::s1352( s1905& tn ){
wstring sv = tn;
size_t s2126 = sv.find( L"(" );
size_t b = sv.find( L'<' );
size_t e = sv.rfind( L'>', s2126 );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' ) {
sv.erase( n--, 1 );
--e;}
return sv;}
void s491::s2119( const s813::Cont& v, size_t& idx, s813::Cont& s153 ){
s153.push_back( v[idx++] );
size_t n = v[idx++];
s153.push_back( (s1061)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s2119( v, idx, s153 );}}
void s2103( const s813::Cont& v, size_t& s2117,
s813::Cont& s153 ){
s153.push_back( v[s2117++] );
size_t s2125 = v[s2117++];
s153.push_back( ( s813::s893 ) s2125 );
while( s2125-- ) {
s2103( v, s2117, s153 );}}
void s491::s1008( const s813::Cont& v, vector<size_t>& s2134, 
s813::Cont& s153 ){
size_t s2117 = 1;
size_t s2125 = v[s2117++];
size_t s2114 = 0;
size_t s2111 = s2134[0];
s813::Cont s2131;
assert( s2111 < s2125 );
while( s2114++ <= s2111 ) {
s2131.clear();
s2103( v, s2117, s2131 );}
if( s2134.size() > 1 ) {
vector<size_t> s2132( s2134.begin() + 1, s2134.end() );
s1008( v, s2132, s2131 );}
else
s153 = s2131;}
s813::s813( s737 t1, s737 t2/*=(s737)-1*/, s737 t3/*=(s737)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s737)-1 ) {
vt.push_back( t2 );
if( t3 != (s737)-1 )
vt.push_back( t3 );}
s1095 = s967( vt );}
s813::s813( const s813& right )
: s1095( right.s1095 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s813::s813( const Cont& v ) 
: vt( v ) {
s1095 = s967( vt );}
s813::s893 s813::s352( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s813::s351( s737 t ){
vt.clear();
vt.push_back( t );}
void s813::s351( s925 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s813::s785( s737 t ){
vt.push_back( t );}
void s813::s785( s925 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s813::s819( std::vector<s271*>& s153 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s153.push_back( new s346( NULL, (int)vt[n] ) );}
inline bool s813::operator==( const s813& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s737* pvt1 = (s737*)&vt[0];
s737* pvt2 = (s737*)&p.vt[0];
for( size_t s684 = 0; s684 < sz1; ++s684 )
if( pvt1[s684] != pvt2[s684] )
return false;
return true;}
s491::s491( s262* pass_ ) 
: s300( pass_ ) {
reset();}
void s491::s290(){
for( size_t n = 0; n < s1113.size(); ++n )
if( s1113[n] ) s1113[n]->s350();}
void s491::s517( const s482& st ){}
void s491::reset() {
s1113.clear(); 
s1096.clear();
s1101.clear();
s1097.clear();
s1102.clear();
s917.clear();
s892.clear();
s1259.clear();
s1274.clear();
s1551.clear();
s1113.push_back( NULL ); 
s1096.push_back( L"" );
s1101.push_back( 0 );
s892[L":Data"] = 1;
s1259[1] = L":Data";
s1205 = 1;
s1274.push_back( 0 );
srand( (unsigned int)time(NULL) );}
s1061 s491::s218( s483* p, s1905& s347 ){
if( s1097.find( s347 ) != s1097.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1096.push_back( s347 );
s1113.push_back( p );
s1061 s1091 = (s1061)s1096.size() - 1;
s1101.push_back( s813( s1091 ) );
p->s351( s1091 );
s1097[s347] = s1091;
s1102[s1101.back()] = s1091;
s1274.push_back( 1 );
s1551.push_back( vector<s1061>() );
return s1091;}
void s491::s1666( s1905& s347 ){
auto it = s1097.find( s347 );
if( it == s1097.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1061 s1091 = it->second;
s1097.erase( it );
s1113[s1091] = NULL;
s1096[s1091] = L"";
s1102.erase( s1101[s1091] );
s1101[s1091] = s813();
s1274[s1091] = 0;
s1551[s1091-1].clear();}
s1061 s491::s1068( const s813::Cont& v, s1905& s347 ){
s813 vt( v );
if( s1102.find( vt ) != s1102.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1096.push_back( s347 );
s1101.push_back( vt );
s1061 s1091 = (s1061)s1096.size() - 1;
s1097[s347] = s1091;
s1102[s1101.back()] = s1091;
s1102[s813( s1091 )] = s1091;
s1113.push_back( s1113[vt.s352( 0 )]->s355( s300, v )	);
s1274.push_back( s1274[vt.s352( 0 )] );
s1551.push_back( vector<s1061>() );
return s1091;}
void s491::s2137( const s813::Cont& v, s813::Cont& s153, size_t s2117  ){
assert( v.size() );
s153.push_back( v[0] );
if( !s2117 ) s2117 = 1;
size_t s2125 = v[s2117++];
s153.push_back( (s1061)s2125 );
size_t s2114 = 0;
s813::Cont s2131;
while( s2114++ < s2125 ) {
s2131.clear();
s2103( v, s2117, s2131 );
s1061 s2136 = 0;
if( s2131.size() == 2 && s2131[1] == 0 )
s2136 = s2131[0];
else
s2136 = s1046( s2131 );
s153.push_back( s2136 );
s153.push_back( 0 );}}
s1061 s491::s1046( const s813::Cont& v_ ){
s813::Cont v;
s2137( v_, v );
s813 vt( v );
s1061 s685 = 0;
auto it = s1102.find( vt );
if( it == s1102.end() ) {
wstring s1089 = s1012( v );
s685 = s1068( v, s1089 );}
else
s685 = it->second;
return s685;}
uint32_t s1193( uint32_t n ){
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
traitnum_t s491::s1252( s1905& trait, s1061& s1510 ){
auto it = s892.find( trait );
if( it != end( s892 ) )
return it->second;
s1205 = s1193( s1205 );
s892[trait] = s1205;
s1259[s1205] = trait;
s1510 = s7::s1554 + (s1061)s1511.size();
s1511.push_back( s1205 );
return s1205;}
void s491::s1162( s813::s893 type, s1905& trait, s1061& s1510 ){
traitnum_t tn;
auto it = s892.find( trait );
if( it == end( s892 ) ) {
tn = s1252( trait, s1510 );
s1274[type] *= tn;}
else {
tn = it->second;
if( !s1198( type, tn ) )
s1274[type] *= tn;}}
traitnum_t s491::s1458( s1061 alias ) const{
return s1511[alias - s7::s1554];}
bool s491::s1198( s1061 s619, traitnum_t tra ) {
assert( s619 && s619 < s1101.size() );
double d = (double)s300->TR().s1155( s619 ) / tra;
return ( d == (int)d );}
bool s491::s1465( s1061 s619, s1061 alias ) {
assert( s619 && s619 < s1101.size() );
double d = (double)s300->TR().s1155( s619 ) /
s1511[alias-s7::s1554];
return ( d == (int)d );}
void s491::s1533( s1061 s619, s1061 is ){
s1551[s619].push_back( is );}
bool s491::s1534( s1061 s619, s1061 is ){
if( s619 == is )
return true;
if( s619 >= s1551.size() )
return false;
std::vector<s1061>& v = s1551[s619];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
bool s491::s1534( const s271* s619, const s271* is ){
if( !s1534( s619->s352(), is->s352() ) ) {
return s619->s501( (s483*)is );}
return true;}
void s491::s1171( s1905& alias, s1905& s347, s1905& s1840 ){
assert( s1097.find( alias ) == end( s1097 ) );
s1061 typid;
auto it = s1097.find( s347 );
if( it == s1097.end() ) {
s813::Cont vt;
size_t pos = 0;
s1056( s347, pos, vt );
if( vt[0] == s1715 ) {
s1061 et_, kt_, vt_;
s324* s2226 = (s324*)s1007( s1715 );
typid = s2226->s1195( s2226, s347, s1715, vt, et_, kt_, vt_ );}
else
typid = s1046( vt );}
else
typid = it->second;	
s1096.push_back( alias );
s1113.push_back( s1113[typid] );
s1101.push_back( s1101[typid] );
s1274.push_back( s1274[typid] );
s1551.push_back( s1551[typid-1] );
s1097[alias] = typid;
auto it1 = s1841.find( s1840 );
if( it1 == s1841.end() )
it1 = s1841.insert( make_pair( s1840, list<wstring>() ) ).first;
it1->second.push_back( alias );}
void s491::s1878( s1905& s1112 ){
auto it = s1841.find( s1112 );
if( it != s1841.end() ) {
for( auto it1 = it->second.begin(); it1 != it->second.end(); ++it1 ) {
s1097.erase( *it1 );}}}
wstring s491::s1275( s1905& tn_, s1905& s1112 ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1097.find( s );
if( it == end( s1097 ) )
return tn_;
const wstring& tn = s1096[s1102[s1101[it->second]]];
if( tn != s ) {
auto it1 = s1841.find( s1112 );
if( it1 != end( s1841 ) ) {
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() ) {
it1 = s1841.find( L"::" );
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() )
return tn_;}}
wstring s685 = tn_;
return s685.replace( 0, s.size(), tn );}
return tn_;}
s483* s491::s518( const s263& s701, s272* s588, s1905& s519 ){
if( s701.s1309() )
return s1113[s701.s1309()]->s354( s701, s588, s519 );
wstring s349 = s701.s291();
if( s349.substr(0,2) == L"[[" && s959::s2179( s349 ) )
return s1113[s1097[Types( s300, Types.Tuple )->s353()]]->s354( s701, s588, s519 );
else if( s349[0] == L'[' )
return s1113[s1097[Types( s300, Types.Vector )->s353()]]->s354( s701, s588, s519 );
else if( s349.find( L"UVector[" ) == 0 )
return s1113[s1097[Types( s300, Types.s748 )->s353()]]->s354( s701, s588, s519 );
else if( s349[0] == L'{' )
return s1113[s1097[Types( s300, Types.Index )->s353()]]->s354( s701, s588, s519 );
else if( s349.find( L"typealias" ) == 0 ) {
size_t pl = s349.find( L"(" );
wstring s347 = s4::s52( s349.substr( pl + 1, s349.size() - pl - 2 ), s4::s48 );
s1171( s701.s299(), s347, s519 );
return s1113[s1097[Types( s300, Types.String )->s353()]]->s354( s701, s588, s519 );}
wstring s347 = L"";
s483* s685 = NULL;
if( s4::s88.find( s349[0] ) != string::npos )
s347 = s359( s300 ).s353();
else if( isdigit( s349[0] ) || s349[0] == L'-' )
return s336::s345( s300, s349, s519 );
else if( ( s685 = s1113[s1148]->s354( s701, s588, s519 ) ) )
return s685;
else {
size_t pl = s349.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s347 = s349.substr( 0, pl );}
else if( pl == string::npos )
s347 = s349;}
auto it = s1097.find( s347 );
if( it == s1097.end() ) {
auto it1 = s892.find( s347 );
if( it1 == end( s892 ) )
throw new s16( L"Type does not exist: " + s349, (uint32_t)s16::s17::s23 );
return new s384( s300, s588, it1->second, s1246 );}
return s1113[it->second]->s354( s701, s588, s519 );}
s483* s491::s518( s1061 s340, s272* s588, s1905& s519 ){
if( s340 >= s7::s1554 ) {
auto it = s1259.find( s340 - s7::s1554 );
if( it != end( s1259 ) )
return new s384( s300, s588, it->first, s1246 );}
if( !s340 || s340 >= s1096.size() )
throw new s16( L"no type with such id: " + to_wstring( s340 ) );
s1061 type = s340;
if( s1101[type].s352() != type )
type = s1101[type].s352();
if( s1101[s340].s819().size() == 1 )
return s1113[type]->s355( s588 );
else {
return s1113[type]->s355( s588, s1101[s340].s819() );}}
const s483* s491::get( s1905& s76, bool s520/*= true*/ ) const
{
wstring s347 = s76;
size_t pl = s76.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s76.find( L"0" ) == string::npos )
s347 = s76.substr( 0, pl );
auto s685 = s1097.find( s347 );
if( s685 == s1097.end() ) {
if( s520 )
throw new s16( L"1: symbol not found: " + s76 );
else
return NULL;}
return s1113[s685->second].s15<const s483*>();}
bool s491::s156( s1905& s76 ) const{
if( s1097.find( s76 ) == s1097.end() )
return false;
return true;}
const wstring& s491::s804( s1061 n ) const{
if( n >= s1096.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1096[n];}
s1061 s491::s1010( s1905& s347, bool s520 ) const{
auto it = s1097.find( s347 );
if( it == s1097.end() ) {
if( s520 )
throw new s16( L"no such type: " + s347,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1061 s491::s1011( const s813& vt, bool s520 ) const{
auto it = s1102.find( vt );
if( it == end( s1102 ) ) {
if( s520 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s813& s491::s1013( s1061 t ) const{
assert( t && t < s1101.size() );
return s1101[t];}
const s483* s491::s1007( s813::s893 t ) const{
assert( t && t < s1101.size() );
return s1113[t].s15<const s483*>();}
void s491::s790(){
size_t s747 = s336::s807() + 1;
for( size_t n = s747; n < s1096.size(); ++n ) {
s1097.erase( s1096[n] );
s1102.erase( s1101[n] );
s917.erase( (s1061)n );}
s1096.erase( s1096.begin() + s747, s1096.end() );
s1113.erase( s1113.begin() + s747, s1113.end() );
s1101.erase( s1101.begin() + s747, s1101.end() );}
bool s491::s1249(){
return rand() % 2;}
double s491::s1251(){
return rand() / RAND_MAX;
}
int s491::s1257(){
return rand();}
void s491::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << L"Types :" << endl;
for( size_t n = 0; n < s1096.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s197 + 5 ) << s1096[n] << endl;
s1113[n]->s304( pd, s197 + 10 );}}
s482::s482( const s482& right )
: s553( right.s553 ), s537( right.s537 ), s539( right.s539 ){}
s482::~s482(){
s553.clear();}
void s482::s500( s272* s879, bool s516/*= true*/ )
{
for( auto sym : s553 ) {
if( sym.second->s494() != s476 && sym.second->s494() != s2166 ) {
try {
sym.second->s500( s879 );}
catch( TDException* e ) {
e->s1076( TDException::Stage::s1026 );
s1014.s971( e->Msg( 0 ) );
continue;}}}
if( s1014.s934() )
return;
if( s516 ) {
for( auto sym : s553 ) {
if( sym.second->s494() == s476 )
sym.second.s15<Transd*>()->s500( s879, false );}}}
void s551::s1649( s262* s300 ){
for( auto sym : s559 ) {
if( sym.find( L"::" ) == string::npos )
s300->s1650( sym );}}
void s482::reset(){
s553.clear();}
void s482::copy( s482& t, s272* s588, s591* s587, s145 ap ) const{
t.s539 = s539;
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() == s476 ) {
s591::s563 ct = it->second.s15<Transd*>()->s864();
s591* ptr = NULL;
if( ct == s591::s568 || ct == s591::s567 )
ptr = (s591*) it->second->s335( s587, s588 );
else if( ct == s591::s566 )
ptr = new s841( *( s841* )&( *it->second ), s587, s588 );
else
ptr = (s591*)it->second->s335( s587, s588 );
t.s541( it->first,  ptr, ap );}
else {
t.s541( it->first, it->second->s335( s587, s588 ), ap );}}}
void s482::s548( s482& t ) const{
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() == s476 )
t.s541( it->first, it->second.s15<s271*>() );
else
t.s541( it->first, it->second->s335(0,0) );}}
void s482::s1613( s482& t ) const{
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() != s476 ) {
auto it1 = t.s553.find( it->first );
if( it1 == end( t.s553 ) )
t.s553[it->first] = it->second;
else
it->second.s15<s483*>()->s356( it1->second.s15<s271*>() );}}}
bool s482::s538( s1905& s76, s145 ap /*= s146*/ )
{
if( s553.find( s76 ) != s553.end() ) {
wstring rep = s7::s421 + L" name already exists: " + s76;
if( ap == s146 || ap == s534 ) {
if( ap == s146 )
throw new TDException( 0, s1671, NULL, s76 );
return false;}
else if( ap == s148 ) {
return false;}}
return true;}
void s482::s541( s1905& s76, s271* sym, s145 ap/*= s146*/ )
{
if( (ap == s147) || s538( s76, ap ) )
s553[s76] = sym;}
void s482::s541( s1905& s76, s142 s349, s145 ap/*= s146*/ )
{
throw new s16( (uint32_t)s16::s17::s21 );}
void s482::s542( const std::wstring& s76 ){
auto it = s553.find( s76 );
if( it == s553.end() )
return;
s553.erase( it );}
void s482::s543( const s6::s143& s79, s145 ap/*= s146*/ )
{
vector<pair<wstring, s142>> s144;
s79.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n )
s541( s144[n].first, s144[n].second );}
bool s482::s156( s1905& s76 ) const{
if( s553.find( s76 ) == s553.end() )
return false;
return true;}
s483* s482::get( s1905& s76, bool s520/*= true*/ ) const
{
auto s685 = s553.find( s76 );
if( s685 == s553.end() ) {
if( s520 )
throw new s16( L"2: symbol not found: " + s76 );
else
return NULL;}
return s685->second.s15<s483*>();}
void s482::s546( std::vector<std::wstring>& s153 ) const{
for( auto sym : s553 )
s153.push_back( sym.first );}
void s482::s544( vector<wstring>& s153 ) const{
for( auto sym : s553 ) {
if( sym.second->s494() == s476 )
s153.push_back( sym.first );}}
void s482::s545( vector<wstring>& s153 ) const{
for( auto sym : s553 ) {
if( sym.second->s494() == s474 ||
sym.second->s494() == s480 || sym.second->s494() == s479 )
s153.push_back( sym.first );}}
void s482::s547( const s482& t,
vector<wstring>& s153 ) const{
for( auto sym : s553 ) {
if( t.s156( sym.first ) )
s153.push_back( sym.first );}}
bool s482::implements( const s482& t ) const{
for( auto sym : t.s553 ) {
if( !s156( sym.first ) )
return false;}
return true;}
void s482::s289( const s482& t, s145 ap /*= s146*/ )
{
if( ap != s147 ) 
for( auto sym : t.s553 )
s538( sym.first, ap );
for( auto sym : t.s553 )
s541( sym.first, sym.second.s15<s483*>(), ap );}
void s482::s549( s512 pv, s263* s79 ){
if( !s539 )
s539 = new s526();
s539->s529( pv, s79 );}
void s482::s533( s1905& s334, vector<wstring>& s153 ){
for( s535::iterator it = s553.begin(); it != s553.end(); ++it ) {
s512 pv = s513;
if( s539 )
pv = s539->s532( it->first, s334 );
if( pv == s513 ) {
if( s537 == s509 )
pv = s514;
else if( s537 == s511 )
pv = s515;
else {
if( it->second->s494() == s476 )
pv = s514;
else
pv = s515;}}
if( pv == s514 )
s153.push_back( it->first );}}
bool s482::s550( s1905& s278,	s1905& s334 ) const{
if( s539 ) {
s512 pv = s539->s532( s278, s334 );
if( pv == s514 )
return true;
else if( pv == s513 ) {
if( s537 == s509 )
pv = s514;
else if( s537 == s511 )
pv = s515;
else {
auto it = s553.find( s278 );
if( it == s553.end() )
throw new s16( L"1: Symbol does not exist: " + s278 );
size_t cat = it->second->s494();
if( cat == s476 || cat == s478 || cat == s480 )
return true;}}
return false;}
return true;}
size_t s482::s322() const{
s535::const_iterator it = s553.begin();
size_t s685 = 1;
for( ; it != s553.end(); ++it ) {
if( it->first[0] != '@' && it->second->s494() != s476 
&& it->second->s494() != s1245 )
s685 = s685 * it->second.s15<s483*>()->s322() << 1;}
return s685;}
bool s482::compare( const s535& r ) const{
if( r.size() != s553.size() )
return false;
s535::const_iterator it = s553.begin();
for( ; it != s553.end(); ++it ) {
auto s2245 = r.find( it->first );
if( s2245 == r.end() )
return false;
if( !it->second.s15<s483*>()->operator==( s2245->second.s15<s483*>() ) )
return false;}
return true;}
void s482::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Symbols :" << endl;
s535::const_iterator it = s553.begin();
for( ; it != s553.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << it->first << L" :" << endl;
if( it->second.s14() ) {
it->second->s304( pd, s197 + s419 * 2 );
buf << endl;}}}
wstring s482::to_wstring( uint32_t s1565 ) const{
std::wostringstream buf;
buf << endl << s4::fill_n_ch( L' ', 0 ) << L"Symbols :" << endl;
s535::const_iterator it = s553.begin();
for( ; it != s553.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s419 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s304( &buf, s419 * 2 );
buf << endl;}}
return buf.str();}
s551::s551(){}
void s551::s500( s262* s300, s1905& s558 ){
s334 = s558;
for( size_t n = 0; n < s559.size(); ++n ) {
wstring s76 = s559[n];
vector<wstring> s153;
s300->s219( s76, s558, s153 );
for( size_t m = 0; m < s153.size(); ++m ) {
s76 = s76.substr( 0, s76.find( L"::" ) );
s553.insert( make_pair( s153[m], make_pair( (s483*)s300->s641( 
s559[n],	s558 ), s76) ) );}}}
void s551::s555( s1905& s76, s262* s300, s1905& s558 ){
s559.push_back( s76 );
vector<wstring> s153;
s300->s219( s76, s558, s153 );
for( size_t n = 0; n < s153.size(); ++n )
s553.insert( make_pair( s153[n], make_pair( (s483*)s300->s641( 
s76,	s558 ), s76 ) ) );}
void s551::s554( s1905& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s16( L"Unrecognized import syntax: " + s );
s559.push_back( s.substr(1, s.size() - 2 ) );}
bool s551::s2180( s1905& s76 ){
if( std::find( begin( s559 ), end( s559 ), s76 ) !=
end( s559) )
return true;
return false;}
bool s551::s556( s1905& sym, s371* ref ){
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );}
else
mem = sym;
size_t s684 = s553.count( mem );
if( !s684 )
return false;
if( s684 > 1 && mod.empty() )
throw new s16( L"ambiguous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s553.equal_range( mem );
if( s684 == 1 && mod.empty() ) {
s483* pd = range.first->second.first;
if( pd->s494() == s479 || pd->s494() == s478 )
return pd->s556( mem, ref, s334, true );
ref->s383( (s483*)pd->s503() );
ref->s382( pd );
return true;}
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod /*sym*/ ) {
s483* pd = it->second.first;
if( pd->s494() == s479 )
return pd->s556( mem, ref, L"", true );
ref->s383( (s483*)pd->s503() );
ref->s382( pd );
return true;}}
return false;}
void s551::copy( s551& t ) const{
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it )
t.s553.insert( make_pair( it->first, it->second ) );}
s521::s521( s512 pv_, const vector<wstring>& s523 )
: pv( pv_ ){
for( auto p : s523 ) {
if( p.empty() )
throw new s16( L"empty values in permissions list are not allowed" );
if( p[0] == L'"' ) {
if( p.size() < 3 || p[p.size()-1] != L'"' )
throw new s16( L"unmatched quotes in a value in permission list" );
p = p.substr( 1, p.size() - 2 );}
s522.push_back( p );}}
s521::s521( s1905& ag_, s1905& s77 ){}
s512 s521::s560( s1905& s499 ) const{
for( size_t n = 0; n < s522.size(); ++n )
if( s522[n] == s499 || s522[n] == L"_" )
return pv;
if( pv == s515 )
return s514;
return s515;}
void s526::s529( s512 pv, s263* s701 ){
s263::s275& s702 = s701->s293();
s263::s275::iterator it = s702.begin();
for( ; it != s702.end(); ++it ) {
wstring l = it->second->s291().substr( 1, it->second->s291().size() - 2 );
vector<wstring> s153;
wstring s72( s1118, 1 );
s4::s57( l, s72, s153 );
s528[it->first] = new s521( pv, s153 );}}
void s526::s530( s1905& s, s521& pl ){}
void s526::s531( s1905& s, s1905& s524 ){}
s512 s526::s532( s1905& mem, s1905& s499 ){
s527::iterator it = s528.find( mem );
if( it == s528.end() )
return s513;
return it->second->s560( s499 );}
s2000 Types;
s1061 s1512::s1271 = 0;
s1061 s1512::s1549 = 0;
s336::s341 s384::s348;
s336::s341 s364::s348;
s336::s341 s361::s348;
s336::s341 s360::s348;
s336::s341 s346::s348;
s336::s341 s358::s348;
s336::s341 s1303::s348;
s336::s341 s1529::s348;
s336::s341 s1295::s348;
s336::s341 s1573::s348;
s336::s341 s1602::s348;
s336::s341 s359::s348;
s336::s341 s316::s348;
s336::s341 s750::s348;
s336::s341 s959::s348;
s336::s341 s324::s348;
s336::s341 s1382::s348;
s336::s341 s1292::s348;
s336::s341 s415::s348;
s336::s341 s385::s348;
s336::s341 s1134::s348;
s336::s341 s951::s348;
s336::s341 s1143::s348;
s336::s341 s1706::s348;
s336::s341 s650::s348;
s336::s341 s1801::s348;
s336::s341 s507::s348;
s336::s341 s1294::s348;
s336::s341 s1302::s348;
s336::s341 s1402::s348;
s336::s341 s1404::s348;
s336::s341 s2062::s348;
s336::s341 s2222::s348;
size_t s336::s758 = 0;
s9<s364> s365;
s9<s384> s872;
s9<s384> s366;
s9<s384> s367;
s9<s384> s368;
s9<s384> s873;
s9<s384> s1686;
s9<s384> s2146;
s9<s360> s369;
s9<s360> s370;
s9<s1402> s1403;
s9<s1404> s1405;
s9<s384> s1521;
template <class charT, charT s72>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s72; }
};
std::locale exprloc;
static s6::s1709 s1758;
s1720 s1738;
s6::s1695 s1736;
const s483* s2000::operator()( s262* s300, s1061 tp ){
return s300->TR().s1007( tp );}
void s336::s784( s262* s300, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
Types.No = s300->s218( new s384( s300 ), L"NoValue" );
Types.Null = s300->s218( new s364( s300 ), L"Null" );
Types.s361 = s300->s218( new s361( s300 ), L"Exception" );
Types.Bool = s300->s218( new s360( s300 ), L"Bool" );
Types.Int = s300->s218( new s346( s300 ), L"Int" );
Types.Double = s300->s218( new s358( s300 ), L"Double" );
Types.Long = s300->s218( new s1303(s300), L"Long" );
Types.s1528 = s300->s218( new s1529( s300 ), L"ULong" );
Types.Byte = s300->s218( new s1295( s300 ), L"Byte" );
Types.Char = s300->s218( new s1573( s300 ), L"Char" );
Types.s272 = s300->s218( new s1602( s300 ), L"Object" );
Types.Position = s300->s218( new s1143( s300 ), L"Position" );
Types.DateTime = s300->s218( new s1706( s300 ), L"DateTime" );
Types.Vector = s300->s218( new s316( s300 ), L"Vector" );
Types.s748 = s300->s218( new s750( s300 ), L"UntypedVector" );
Types.Tuple = s300->s218( new s959( s300 ), L"Tuple" );
Types.Set = s300->s218( new s2222( s300 ), L"Set" );
Types.Index = s300->s218( new s324( s300 ), L"Index" );
Types.HashIndex = s300->s218( new s1382( s300 ), L"HashIndex" );
Types.ByteArray = s300->s218( new s1292( s300 ), L"ByteArray" );
Types.s414 = s300->s218( new s415( s300 ), L"Directory" );
Types.Range = s300->s218( new s385( s300 ), L"Range" );
Types.Filter = s300->s218( new s1134( s300 ), L"Filter" );
Types.Seq = s300->s218( new s951( s300 ), L"Seq" );
Types.Table = s300->s218( new s1801( s300 ), L"Table" );
Types.TSDBase = s300->s218( new s650( s300 ), L"TSDBase" );
Types.s789 = s300->s218( new s507( s300 ), L"StringStream" );
Types.ByteStream = s300->s218( new s1294( s300 ), L"ByteStream" );
Types.FileStream = s300->s218( new s1302( s300 ), L"FileStream" );
Types.Lambda = s300->s218( new s838( s300 ), L"Lambda" );
Types.String = s300->s218( new s359( s300 ), L"String" );
if( !soft )
s758 = Types.String;
if( s365.s13() ) {
s365 = new s364( s300 );
s872 = new s384( s300, NULL, s481 );
s368 = new s384( s300, NULL, s481 );
s367 = new s384( s300, NULL, s481 );
s366 = new s384( s300, NULL, s481 );
s873 = new s384( s300, NULL, s481 );
s1686 = new s384( s300, NULL, s481 );
s2146 = new s384( s300, NULL, s481 );
s369 = new s360( s300, true );
s370 = new s360( s300, false );
s872->s1679( s7::s866 );
s368->s1679( s7::s438 );
s367->s1679( s7::s439 );
s366->s1679( s7::s440 );
s369->s1260();
s370->s1260();
s1521 = new s384( s300, NULL, Types.Int, s1246 );
s1736.s151 = true;
s1736.s1732 = true;
s1736.s1700 = true;
s1736.s1699 = true;
s1736.s1701 = true;}}
s1122::s1122( const std::vector<s485>& v, s336* s592 )
:s588( s592 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s494() != s1063 ) {
s912.push_back( v[n] );
s1278.push_back( v[n]->s352() );}
else if( n > 1 )
break;}}
bool s1122::operator==( const s1122& s524 ) const{
bool pend = s1278.empty();
bool send = s524.s1278.empty();
s1061 starred = 0;
size_t n = 0, k = 0;
bool s1270 = true;
s491* ptr = s524.s588 ? &s524.s588->Pass()->TR() : NULL;
while( !send || !pend ) {
s1270 = false;
s1061 s1177 = starred ? starred : (pend ? 0 : s1278[k]);
s1061 s1174 = send ? (s524.s1278.empty() ? 0 : s524.s1278[n-1]) : s524.s1278[n];
s271* s1537 = send ?
( s524.s912.empty() ? NULL : s524.s912[n - 1].s15<s271*>() ) :
s524.s912[n].s15<s271*>();
if( s1174 == Types.No )
s1174 = send ? s524.s912[n-1].s15<s384*>()->s1540() : 
s524.s912[n].s15<s384*>()->s1540();
const s813* s1281 = s524.s588 ? &s524.s588->s1196() : NULL;
if( s1177 >= s7::s1399 && s1177 < s7::s1554 && s1174 ) {
if( s1177 == s7::s1393 )
s1270 = true;
else if( s1177 == s7::s1398 ) {
s1061 pt1_ = s524.s912[n]->s1196().s352();
if( pt1_ == s1716 /*&& pt2_ == Types.Bool*/ )
s1270 = true;}
else if( s1177 == s7::s1394 ) {
if( s524.s588 && s1174 == s524.s588->s352())
s1270 = true;}
else if( s1177 == s7::s1395 ) {
if( s524.s588 && s1174 == ( (s326*)s524.s588 )->s319() )
s1270 = true;}
else if( s1177 == s7::s1395 ) {
if( s524.s588 && s1174 == ((s326*)s524.s588)->s319() )
s1270 = true;}
else if( s1177 == s7::s1396 ) {
if( s524.s588 && s1174 == ((s326*)s524.s588)->s937() )
s1270 = true;}
else if( s1177 == s7::s1397 ) {
if( s524.s588 && s1537->s1541( ((s326*)s524.s588)->ValType() ) )
s1270 = true;}
else if( s1281 &&	s1174 == s1281->s352( (size_t)((int)0 - s1177 )) )
s1270 = true;}
else if( s1177 >= s7::s1554 && ptr ) {
traitnum_t s1513 = ptr->s1458( s1177 );
if( s1174 && ptr->s1198( s1174, s1513 ) )
s1270 = true;}
else {
if( s1537 && s1537->s1541( s1177 ) )
s1270 = true;}
if( s1270 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s524.s1278.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1278.size() )
pend = true;
if( !starred && !pend && s1278[k] == s7::s1399 )
starred = s1278[k - 1];}
return s1270;}
bool s1122::operator<( const s1122& s524 ) const{
if( s1278.empty() ) return s524.s1278.size() > 0;
if( s524.s1278.empty() ) return false;
const s813* s1280 = s588 ? &s588->s1196() : NULL;
const s813* s1281 = s524.s588 ? &s524.s588->s1196() : NULL;
s1061 s1268 = 0, s1269 = 0;
s491* ptr = s524.s588 ? &s524.s588->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1278.size() && n < s524.s1278.size()*/; ++n ) {
if( s1278.size() == n )
return s524.s1278.size() > n;
if( s524.s1278.size() == n )
return false;
s1061 s1176 = s1268 ? s1268 : s1278[n];
s1061 s1178 = s1269 ? s1269 : s524.s1278[n];
if( s1176 >= s7::s1399 && s1176 <= s7::s1554 ) {
if( s1176 == s7::s1399 )
s1176 = s1268 = s1278[n - 1];
else if( s1176 == s7::s1393 )
continue;
else if( s1176 == s7::s1394 ) {
if( !s524.s588 )
return true;
s1176 = s524.s588->s352();}
else if( s1176 == s7::s1395 ) {
if( !s524.s588 )
return true;
s1176 = ( (s326*)s524.s588 )->s319();}
else if( s1280 )
s1176 = s1280->s352( (size_t)(int)0 - s1176 );}
else if( s1176 >= s7::s1554 && ptr ) {
traitnum_t s1513 = ptr->s1458( s1176 );
if( ptr->s1198( s1178, s1513 ) )
return true;}
if( s1178 >= s7::s1399 && s1178 <= s7::s1554 ) {
if( s1178 == s7::s1399 )
s1178 = s1269 = s524.s1278[n - 1];
else if( s1178 == s7::s1393 )
continue;
else if( s1178 == s7::s1394 ) {
if( !s588 )
return true;
s1178 = s588->s352();}
else if( s1178 == s7::s1395 ) {
if( !s588 )
return true;
s1178 = ( (s326*)s588 )->s319();}
else if( s1281 )
s1178 = s1281->s352( (size_t)(int)0 - s1178 );}
else if( s1178 >= s7::s1554 && ptr ) {
traitnum_t s1513 = ptr->s1458( s1178 );
if( ptr->s1198( s1176, s1513 ) )
return true;}
if( s1176 < s1178 )
return true;}
return false;}
wstring s1122::s1329( s262* s300 ) const{
wstring s685 = L"( ";
for( auto i : s1278 ) {
s685 += s300->TR().s804( i );
if( s685.back() != L')' ) s685 += L"()";
s685 += L" ";}
s685 += L")";
return s685;}
bool
s336::s337::s1166( /*s336* thi,*/ const s1122& s691 ) const
{
return std::find( s1163.begin(), s1163.end(), s691 ) != end( s1163 );}
s1061
s336::s386( s1905& s343 ) const{
auto it = s342().find( s343 );
if( it == s342().end() )
throw new s16( L"No such operation: " + s353() +	L"::" + s343,
(uint32_t)s16::s17::s23 );
s1061 s685 = it->second->s495();
return s685;}
const s483*
s336::s503() const{
return (s483*)s300->TR().s1007( s352() );}
const vector<wstring>& 
s336::s1191( s1905& s343 ) const{
auto ran = s342().equal_range( s343 );
if( ran.first == s342().end() )
throw new s16( L"No such method: " + s353() + L"::" + s343,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1142 s336::s1197( s1905& s343 ) const{
s336::s337* s685 = NULL;
auto it = s342().find( s343 );
if( it != s342().end() )
s685 = it->second;
return s685 ? s1142( s685->s495(), s685->s1136(), s685->s1203(),
s685->s2017() ) : s1142();}
s1142
s336::s1192( s1905& s343, s1122& ap /*const vector<s1061>& s1240*/ ) const
{
auto ran = s342().equal_range( s343 );
if( ran.first == s342().end() )
throw new s16( L"No such method: " + s353() + L"::" + s343,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1186() )
throw new s16( L"", (uint32_t)s337::s1133::s1180 );
s337* s685 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1166( ap ) ) {
s685 = it->second;
break;}}
return s685 ? s1142( s685->s495(), s685->s1136(), s685->s1203(),
s685->s2017() ) : s1142();}
s1142
s336::s1187( s1905& s343, s1122& ap ){
auto ran = s342().equal_range( s343 );
s337* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1166( ap ) ) {
mi = it->second;
break;}}
if( !mi )
throw new s16( L"method '" + s300->TR().s1352( s353() ) + L"::" + s343 + 
ap.s1329( s300 ) + L"' is not resolved" );
s1142 s1237( mi->s495(), mi->s1136(), mi->s1203(), mi->s2017() );
s1237.s338 = ap.Subj()->s1188( s343, ap.s602() );
return s1237;}
s486 s336::s497( s483** s274, size_t s498 ){
return this;}
void s336::s1535( s483* p ){}
s483* s336::s345( s262* s300, s1905& s349, s1905& s334 ){
s263 s208( s349, NULL, NULL );
s483* s685 = NULL;
double dval;
size_t pos = 0;
s6::s131 s198 = s1758.s1550( s349, pos, dval );
if( s198 != s6::s131::s140 && s198 != s6::s131::s136 )
return NULL;
if( s349.find( L"." ) != std::string::npos )
s685 = ((s358*)Types( s300, Types.Double ))->s354( s208, NULL, s334 );
else {
s685 = ((s346*)Types( s300, Types.Int ))->s354( s208, NULL, s334 );
if( !s685 ) {
if( !s685 )
s685 = ((s1303*)Types( s300, Types.Long ))->s354( s208, NULL, s334 );
if( !s685 )
s685 = ((s1295*)Types( s300, Types.Byte ))->s354( s208, NULL, s334 );}}
return s685;}
#define s698 ((s346*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
s483* s358::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
1/*s.find( L"." ) != std::string::npos*/ ) {
size_t pos = 0;
return new s358( s300, s, pos );}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s358( s300, s4::s52( s.substr( 7, s.size() - 8 ), s4::s48 ),
pos );}
else if( s.find( L"Double" ) == 0 ) {
return s355( s588, std::vector<s271*>(), &s701 );}
return 0;}
s358::s358( s262* s300, double d ) 
: s336( s300, NULL, NULL ), s349( d ){
if( !Types.Double ) {
s493 = 0;
wh = s7::s868;}
else {
s493 = Types.Double;
wh = s7::s867;}}
s358::s358( const s358& r )
: s336( r.s300, r.ns, r.s603() ), s349( r.s349 ){
wh = r.wh;
s493 = r.s493;}
double s1942( s1905& s, size_t& pos ){
assert( !s.empty() );
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
double s153 = 0.0;
pst = s.c_str();
if( !s63( pst, &s153, &pend ) )
throw new s16( L"2: unknown syntax near \"" + s.substr( pos, 40 ) + L"\"",
(uint32_t)s16::s17::s20 );
pos = pend - pst;
return s153;}
s358::s358( s262* s300, s1905& s, size_t& pos )
: s336( s300, NULL, NULL ){
if( !s.empty() ) {
s349 = s1942( s, pos );
s1679( s7::s867 );}
else
s349 = s300->TR().s1251();
s493 = Types.Double;}
s483* s358::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s358( s300, L"", pos );}
void s358::s500( const s272*, bool ){
s1262();}
void s358::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s358::s1236, Types.Double,
{ s1122(), s1122( { Types.String } ), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"abs", new s337( L"abs", &s358::s404, Types.Double,
{ s1122( ) }, 0, 0 )));
s348.insert( make_pair( L"set", new s337( L"set", &s358::s387, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"sum", new s337( L"sum", &s358::s388, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"dif", new s337( L"dif", &s358::s389, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"mul", new s337( L"mul", &s358::s390, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"div", new s337( L"div", &s358::s391, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"pow", new s337( L"pow", &s358::s392, Types.Double,
{ s1122( { s1512::s1271 } ) }, 1, 1 )));
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s358::s393, Types.Double,
{ s1122( { Types.Double } ), s1122( { Types.Int, s7::s1399 } ) }, 1, 10 )));
s348.insert( make_pair( L"difeq", new s337( L"difeq", &s358::s394, Types.Double,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"muleq", new s337( L"muleq", &s358::s395, Types.Double,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"diveq", new s337( L"diveq", &s358::s396, Types.Double,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"poweq", new s337( L"poweq", &s358::s397, Types.Double,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"sqrt", new s337( L"sqrt", &s358::s406, Types.Double,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"nroot", new s337( L"nroot", &s358::s407, Types.Double,
{ s1122( { Types.Int } ) }, 1, 1 )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s358::s398, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"less", new s337( L"less", &s358::s399, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"greater", new s337( L"greater", &s358::s400, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"leq", new s337( L"leq", &s358::s401, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"geq", new s337( L"geq", &s358::s402, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"neq", new s337( L"neq", &s358::s403, Types.Bool,
{ s1122( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"dcmp", new s337( L"dcmp", &s358::s410, Types.Int,
{ s1122( { Types.Double, Types.Double } ) }, 2, 2 )));
s348.insert( make_pair( L"dcmpr", new s337( L"dcmpr", &s358::s411, Types.Int,
{ s1122( { Types.Double, Types.Double } ) }, 2, 2 )));
s348.insert( make_pair( L"floor", new s337( L"floor", &s358::s2215, Types.Double,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"ceil", new s337( L"ceil", &s358::s2213, Types.Double,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s358::s412, Types.Int,
{ s1122(), s1122( { Types.Int } ) }, 0, 1 )));
s348.insert( make_pair( L"incr", new s337( L"incr", &s358::s1978, Types.Double,
{ s1122( ) }, 0, 0 )));
s348.insert( make_pair( L"decr", new s337( L"decr", &s358::s1977, Types.Double,
{ s1122( ) }, 0, 0 )));
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );}
s271* s358::s335( s591* s2057, s272* impl ) const{
return new s358( *this );}
void s358::s356( s271* p ) const{
if( p->s352() == Types.Int )
*( (s346*)p )->s357() = (int)s349;
else if( p->s352() == Types.Double )
*( (s358*)p )->s357() = s349;
else if( p->s352() == Types.Bool )
*( (s360*)p )->s357() = ( s349 != 0.0 );
else
throw new s16( L"No conversion to type " + s353() );}
std::wstring s358::to_wstring( uint32_t s1565 ) const{
wstringstream ss;
wstring s685;
int prec = s1565 << 28 >> 28;
if( prec ) {
ss << setprecision( prec ) << s349;
s685 = ss.str();}
else {
wstring s = std::to_wstring( s349 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
s685 = s.substr(0, pl);}
return s685;}
void s358::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
/*	auto flags = s1934->s1930();
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss.precision( s1934->s1931() );
*/
ss << s349;}
void s358::s1960( s1905& s ){
size_t pos = 0;
s349 = s1942( s, pos );}
void s358::s1959( Stream* s1934 ){
s1497& ss = s1934->s1963();
ss >> s349;}
#undef s698
#define s698 ((s358*)(s484*)*s274)
#define INTRES ((s346*)(s484*)*s274)
inline void s358::s1236( s483** s274, size_t s498 ){
s358* plv = NULL;
if( s498 == 3 && s274[2]->s352() == Types.String ) {
size_t pos = 0;
plv = new s358( ((s358*)s274[1] )->s300, *((s359*)s274[2])->s357(), pos );}
else {
plv = new s358( ( (s358*)s274[1] )->s300, 0.0 );
s358& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if( s498 == 3 ) {
s483* p = s274[2];
if( p->s352() == Types.Double )
lv.s349 = *( (s358*)p )->s357();
else if( p->s352() == Types.Int )
lv.s349 = (s1386)*( (s346*)p )->s357();
else if( p->s352() == Types.Bool )
lv.s349 = ( s1386 )*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Double from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Double() constructor" );}
plv->s1262();
s274[0] = plv;}
inline void s358::s387( s483** s274, size_t s498 ){
( (s358*)DR )->s349 = (double)*PARN( 2 );}
void s358::s404( s483** s274, size_t s498 ){
double t = (double)*DR;
if( t >= 0 )
s698->s349 = t;
else
s698->s349 = -t;}
void s358::s1978( s483** s274, size_t s498 ){
double s685 = (double)*DR;
if (isnan( s685 ) || s685 == -INFINITY || s685 == INFINITY) (void)0;
else if ( s685 == 0.0 ) s685 = DBL_EPSILON;
else {
union s1974 {
int64_t i;
double f;
}conv;
conv.f = s685;
conv.i++;
s685 = conv.f;}
s698->s349 = s685;}
void s358::s1977( s483** s274, size_t s498 ){
double s685 = (double)*DR;
if (isnan( s685 ) || s685 == -INFINITY || s685 == INFINITY) (void)0;
else if ( s685 == 0.0 ) s685 = DBL_EPSILON;
else {
union s1974 {
int64_t i;
double f;
}conv;
conv.f = s685;
conv.i--;
s685 = conv.f;}
s698->s349 = s685;}
inline void s358::s390( s483** s274, size_t s498 ){
s698->s349 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
s698->s349 *= (double)*PARN( n );}
inline void s358::s388( s483** s274, size_t s498 ){
s698->s349 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
s698->s349 += (double)*PARN( n );}
inline void s358::s391( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
s698->s349 = ( (s358*) DR )->s349 / s698->s349;
}
inline void s358::s389( s483** s274, size_t s498 ){
s698->s349 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
s698->s349 -= (double)*PARN( n );}
inline void s358::s393( s483** s274, size_t s498 ){
s358* pd = (s358*) s274[1];
for( size_t n = 2; n < s498; ++n ) {
s483* p = s274[n];
if( p->s352() == Types.Double )
pd->s349 += *( (s358*)p )->s357();
else if( p->s352() == Types.Int )
pd->s349 += ( s1386 )*( (s346*)p )->s357();}
s698->s349 = ( (double)*DR );}
inline void s358::s394( s483** s274, size_t s498 ){
( (s358*)DR )->s349 -= (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
( (s358*)DR )->s349 -= (double)*PARN( n );
s698->s349 = ( (double)*DR );}
inline void s358::s395( s483** s274, size_t s498 ){
( (s358*)DR )->s349 *= (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
( (s358*)DR )->s349 *= (double)*PARN( n );
s698->s349 = ( (double)*DR );}
inline void s358::s396( s483** s274, size_t s498 ){
( (s358*)DR )->s349 /= (double)*PARN( 2 );
for( size_t n = 3; n < s498; ++n )
( (s358*)DR )->s349 /= (double)*PARN( n );
s698->s349 = ( (double)*DR );}
inline void s358::s397( s483** s274, size_t s498 ){
( (s358*)DR )->s349 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s498; ++n )
( (s358*)DR )->s349 = ::pow( (double)*DR, (double)*PARN( n ) );
s698->s349 = ( (double)*DR );}
inline void s358::s398( s483** s274, size_t s498 ){
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s399( s483** s274, size_t s498 ){
if( ((double)*DR) < (double)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s400( s483** s274, size_t s498 ){
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s401( s483** s274, size_t s498 ){
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s402( s483** s274, size_t s498 ){
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s403( s483** s274, size_t s498 ){
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s358::s406( s483** s274, size_t s498 ){
s698->s349 = ::sqrt((double)*DR);}
inline void s358::s407( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s358::s410( s483** s274, size_t s498 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s357() = 0;
else
*INTRES->s357() = 1;}
else {
if( dr - dl <= diff )
*INTRES->s357() = 0;
else
*INTRES->s357() = -1;}}
inline void s358::s411( s483** s274, size_t s498 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s357() = 0;
else
*INTRES->s357() = 1;}
else {
if( dr / dl - 1 <= diff )
*INTRES->s357() = 0;
else
*INTRES->s357() = -1;}}
inline void s358::s392( s483** s274, size_t s498 ){
s698->s349 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );}
inline void s358::s2215( s483** s274, size_t s498 ){
double dv = ( (s358*)DR )->s349;
*( (s358*)s274[0] )->s357() = floor( dv );}
inline void s358::s2213( s483** s274, size_t s498 ){
double dv = ( (s358*)DR )->s349;
*( (s358*)s274[0] )->s357() = ceil( dv );}
inline void s358::s412( s483** s274, size_t s498 ){
int s1331 = -1;
if( s498 == 3 )
s1331 = (int)*s274[2];
double dv = ( (s358*)DR )->s349;
int s685 = (int)dv;
if( s1331 < 0 )
*( (s346*)s274[0] )->s357() = s685;
else if( s1331 == 0 ) 
*( (s346*)s274[0] )->s357() = (dv - s685 > 0.5 ? s685 + 1 : s685);
else
*( (s346*)s274[0] )->s357() = s685 + 1;}
void s358::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349;}
size_t s358::s322() const{
return hash<double>{}( s349 );}
inline
int dcmp( double d1, double d2, int iDigs ){
double s87 = fabs( d1 - d2 );
double prec = 1 / pow( (double)10.0, iDigs );
if ( s87 < prec )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline
int dcmp_( double d1, double d2, double dif ){
double s87 = fabs( d1 - d2 );
if ( s87 < dif )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline bool s358::operator==( const s483* p ) const{
return ( dcmp_( ( (s358*)p )->s349, s349, 0.00000001 ) == 0 ); // FIX:
}
inline bool s358::operator<( const s483* p ) const{
return ( dcmp_( s349, ( (s358*)p )->s349, 0.00000001 ) < 0 ); // FIX:
}
s360::s360( s262* s300, s1905& s, size_t& pos )
: s336( s300, NULL, NULL ){
if( s.empty() )
s349 = s300->TR().s1249();
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s349 = (s[0] == L'1');
pos++;}
else if( s.find( s7::s436 ) == 0 ) {
s349 = true;
pos += 4;}
else if( s.find( s7::s437 ) == 0 ) {
s349 = false;
pos += 5;}
else
throw new s16( L"unknown bool format: " + s.substr( 0, 20 ) );
if( !s.empty() )
s1679( s7::s867 );
s493 = Types.Bool;}
s360::s360( const s360& right )
: s336( right.s300, right.ns, NULL ), s349( right.s349 ){
s493 = Types.Bool;
wh = right.wh;}
s360::s360( s262* s300, bool b )
: s336( s300, NULL, NULL ), s349( b ){
if( !Types.Bool ) {
s493 = 0;
s1679( s7::s868 );}
else {
s493 = Types.Bool;
s1679( s7::s867 );}}
void s360::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s360::s387, Types.Null,
{ s1122( { Types.Bool } ) }, 1, 1, false )));
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s360::s1236, Types.Bool,
{ s1122(), s1122( { Types.Bool } ), s1122( { Types.String } ), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s360::s413, Types.Bool,
{ s1122( ) }, 0, 0, true )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s360::s398, Types.Bool,
{ s1122( { Types.Bool } ) }, 1, 1, true )));}
void s360::s500( const s272* s879, bool ){
s1262();}
s483* s360::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s360( s300, false );}
s483* s360::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s4::s52( s701.s291(), s4::s48 );
if( s.find( s7::s436 ) == 0 || s.find( s7::s437 ) == 0 )
return new s360( s300, ( s.find( s7::s436 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s360( s300, 
s4::s52( s.substr( 5, s.size() - 6 ), s4::s48 ), pos );}
else if( s.find( L"Bool" ) == 0 ) {
return s355( s588, std::vector<s271*>(), &s701 );}
return NULL;}
s271* s360::s335( s591* s2057, s272* impl ) const{
return new s360( *this );}
void s360::s356( s271* p ) const{
if( p->s352() == Types.Bool )
((s360*)p)->s349 = s349;
else if( p->s352() == Types.Int )
*( (s346*)p )->s357() = (int)s349;
else if( p->s352() == Types.Double )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"No conversion to type " + s353() );}
#undef s698
#define s698 ((s360*)(s484*)*s274)
inline void s360::s1236( s483** s274, size_t s498 ){
s360* plv = new s360( ( (s360*)s274[1] )->s300, 0 );
s360& lv = *plv;
if( s498 == 2 )
lv.s349 = false;
else if( s498 == 3 ) {
s483* p = s274[2];
if( p->s352() == Types.Int )
lv.s349 = *( (s346*)p )->s357() != 0;
else if( p->s352() == Types.Double )
lv.s349 = *( (s358*)p )->s357() != 0.0;
else if( p->s352() == Types.Bool )
lv.s349 = *( (s360*)p )->s357();
else if( p->s352() == Types.String )
lv.s349 = ( (s359*)p )->s357()->size() > 0;
else
throw new s16( L"no conversion to Bool from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Bool() constructor" );
lv.s1262();
s274[0] = plv;}
inline void s360::s387( s483** s274, size_t s498 ){
( (s360*)DR )->s349 = ( (s360*)PARN( 2 ) )->s349;}
inline void s360::s413( s483** s274, size_t s498 ){
s698->s349 = !( (s360*)DR )->s349;}
inline void s360::s398( s483** s274, size_t s498 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
wstring s360::to_wstring( uint32_t s1565 ) const{
return ( s349 ? L"true" : L"false" ); }
void s360::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
ss << s349;}
void s360::s1960( s1905& s ){
if( s == L"true" || s == L"1" )
s349 = true;
else if( s == L"false" || s == L"0" )
s349 = false;
else
throw new s16( L"unknown bool value" );}
void s360::s1959( Stream* s1934 ){
s1497& ss = s1934->s1963();
ss >> s349;}
void s360::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << to_wstring()
<< L" (" << std::hex << &s349 << L")";}
size_t s360::s322() const{
return hash<bool>{}( s349 );}
inline bool s360::operator==( const s483* p ) const{
return ( s349 == ((s360*)p)->s349 );}
inline bool s360::operator<( const s483* p ) const{
return ( s349 < ((s360*)p)->s349 );}
s361::s361( s262* s300, s1905& s/* = std::wstring( L"" )*/ )
: s336( s300, NULL, NULL ), s78( s ){
wh = s7::s440;
s493 = Types.No == 0 ? 0 : Types.s361;}
s361::s361( const s361& r )
: s336( r.s300, NULL, NULL ), s78( r.s78 ){
s493 = r.s493;
wh = r.wh;}
void s361::s350(){
s348.insert( make_pair( L"report", new s337( L"report", &s361::s792, Types.Null,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"str", new s337( L"str", &s361::s508, Types.String,
{ s1122() }, 0, 0 )));}
void s361::s500( const s272* s879, bool ){}
s483* s361::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s361( s300 );}
s271* s361::s335( s591* s2057, s272* impl ) const{
return new s361( *this );}
void s361::s356( s271* p ) const{
((s361*)p)->s78 = s78;}
s483* s361::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
if( s.find( L"Exception(" ) == 0 )
return new s361( s300, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s355( s588, std::vector<s271*>(), &s701 );
return NULL;}
#undef s698
#define s698 ((s361*)(s484*)*s274)
inline void s361::s792( s483** s274, size_t s498 ){
wcout << ( (s361*)DR )->s78;}
inline void s361::s508( s483** s274, size_t s498 ){
*( (s359*)s274[0] )->s357() = ( (s361*)DR )->s78;}
void s361::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : -";}
size_t s361::s322() const{
throw new s16( L"9: not implemented" );}
bool s361::operator==( const s483* p ) const{
return ( (s361*)p )->s78 == s78;}
bool s361::operator<( const s483* p ) const{
return s78 < ( (s361*)p )->s78;}
s364::s364( s262* s300 ) 
: s336( s300, NULL, NULL ){
if( !Types.Null ) {
s493 = 0;
s1679( s7::s868 );}
else {
s493 = Types.Null;
s1679( s7::s867 );}}
void s364::s500( const s272* s879, bool ){}
s483* s364::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s364( s300 );}
s483* s364::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
if( s.find( L"Null" ) == 0 )
return s365;
return NULL;}
s271* s364::s335( s591* s2057, s272* impl ) const{
return (s271*)this;}
void s364::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : -";}
size_t s364::s322() const{
return 0xfeeb1e;}
bool s364::operator==( const s483* p ) const{
return ( this == p );}
bool s364::operator<( const s483* p ) const{
return false;}
s384::s384( s262* s300, s272* ns_, traitnum_t tn, s472 pc ) 
: s336( s300, ns_, NULL ), s1272( tn ){
s492 = pc;
s493 = Types.No == 0 ? 0 : Types.No; }
void s384::s500( const s272* s879, bool ){
ns = (s272*)s879;}
s483* s384::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s384( s300, s588 );}
s483* s384::s354( const s263& s701, s272* s588, s1905& s334 ) const{
throw new s16( L"no parser for NoValue" );
return NULL;}
s271* s384::s335( s591* s2057, s272* impl ) const{
return (s271*)this;}
inline bool
s384::s501( const s483* s502 ) const{
return s300->TR().s1198( s502->s352(), s1272 );}
inline bool
s384::s1541( s1061 s619 ) const{
return s300->TR().s1534( s1272, s619 );}
void s384::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : -" << endl;}
size_t s384::s322() const{
throw new s16( L"not implemented" );}
bool s384::operator==( const s483* p ) const{
return false;}
bool s384::operator<( const s483* p ) const{
return false;}
s1706::s1706( s262* s300 ) 
: s336( s300, NULL, NULL ), s1743( s1741 ) {
if( !Types.DateTime )
s493 = 0;
else
s493 = s1713;
s1679( s7::s868 );}
s1706::s1706( s262* s300, s1905& s )
: s336( s300, NULL, NULL ){
if( !s1728( s, s349, s1743 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1875 = s1795::from_time_t ( std::mktime( &s349 ) );
s493 = s1713;
s1679( s7::s867 );}
s1706::s1706( const s1706& right )
: s336( right.s300, right.ns, NULL ), s349( right.s349 ), s1875( right.s1875 ){
s493 = right.s493;
wh = right.wh;}
s1706::s1706( s262* s300, const std::tm& _t, s1705 s619 )
: s336( s300, NULL, NULL ), s1743( s619 ), s349( _t ){
s493 = s1713;
s1875 = s1795::from_time_t ( std::mktime( &s349 ) );
s1679( s7::s867 );}
wregex s1706::s1765( LR"regex(^\"?(\d\d\d\d-\d\d?-\d\d?)\"?$)regex" );
wregex s1706::s1863( LR"regex(^(\d+)(\.\d+)?$)regex" );
bool 
s1706::s1728( s1905& s349, std::tm& t, s1705& s619 ) const{
wsmatch s1074;
s619 = s1741;
if( regex_match( s349, s1074, s1765 ) ) {
std::wistringstream ss( s1074[1] );
ss >> std::get_time( &t, L"%Y-%m-%d" );
if( ss.fail() )
return false;
s619 = s1739;}
else if( regex_match( s349, s1074, s1765 ) ) {}
else
return false;
return true;}
void s1706::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s1706::s387, Types.Null,
{ s1122( { s1713 } ), s1122( { Types.String } ) }, 1, 1, false ) ) );
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1706::s1236, s1713,
{ s1122(), s1122( { s1713 } ), s1122( { Types.String } ), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s1706::s413, Types.Bool,
{ s1122() }, 0, 0, true ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s1706::s398, Types.Bool,
{ s1122( { s1713 } ) }, 1, 1, true ) ) );
s348.insert( make_pair( L"now-delta", new s337( L"now-delta", &s1706::s1849, Types.Double,
{ s1122( ) }, 0, 0, true ) ) );
s348.insert( make_pair( L"set-now", new s337( L"set-now", &s1706::s1873, s1713,
{ s1122( ) }, 0, 0, false ) ) );}
void s1706::s500( const s272* s879, bool ){
s1262();}
s483* s1706::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1706( s300 );}
s483* s1706::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s4::s52( s701.s291(), s4::s48 );
if( s.find( L"DateTime(" ) == 0 )
s = s.substr( 9, s.size() - 10 );
if( s.empty() )
return new s1706( s300 );
std::tm t = {};
s1705 s619;
if( s1728( s, t, s619 ) )
return new s1706( s300, t, s619 );
return NULL;}
s271* s1706::s335( s591* s2057, s272* impl ) const{
return new s1706( *this );}
void s1706::s356( s271* p ) const{
if( p->s352() == s1713 )
( (s1706*)p )->s349 = s349;
else
throw new s16( L"No conversion to type " + s353() );}
void s1706::s1960( s1905& s ){
std::tm t = {};
s1705 s619;
if( !s1728( s, t, s619 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1743 = s619;
s349 = t;
s1679( s7::s867 );}
#undef s698
#define s698 ((s1706*)(s484*)*s274)
inline void s1706::s1236( s483** s274, size_t s498 ){
s1706* s685 = NULL;
if( s498 == 2 )
s685 = new s1706( ( (s1706*)s274[1] )->s300 );
else if( s498 == 3 ) {
s483* p = s274[2];
if( p->s352() == s1713 )
s685 = new s1706( *(s1706*)s274[2] );
else if( p->s352() == Types.String )
s685 = new s1706( ( (s1706*)s274[1] )->s300, s274[2]->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to DateTime() constructor" );
s274[0] = s685;}
inline void s1706::s387( s483** s274, size_t s498 ){
s483* p = s274[2];
if( p->s352() == s1713 ) {
( (s1706*)DR )->s349 = ( (s1706*)p )->s349;
( (s1706*)DR )->s1743 = ( (s1706*)p )->s1743;
( (s1706*)DR )->wh = ( (s1706*)p )->wh;}
else if( p->s352() == Types.String )
( (s1706*)DR )->s1960( p->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s353() );}
inline void s1706::s413( s483** s274, size_t s498 ){
*s699->s357() = !(( (s1706*)DR )->s1743 == s1741);}
inline void s1706::s398( s483** s274, size_t s498 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s1706::s1873( s483** s274, size_t s498 ){
s1706* p = (s1706*)DR;
p->s1875 = s1795::now();
time_t t = s1795::to_time_t( p->s1875 );
#ifdef WIN32
localtime_s( &p->s349, &t );
#else
p->s349 = *localtime( &t );
#endif
p->s1743 = s1740;}
inline void s1706::s1849( s483** s274, size_t s498 ){
s1706* p = (s1706*)DR;
std::chrono::duration<double> delta = s1795::now() - p->s1875;
*((s358*)s274[0])->s357() = delta.count();}
void s1706::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << to_wstring()
<< L" (" << std::hex << &s349 << L")";}
size_t s1706::s322() const{
std::tm t = s349;
return hash<time_t>{}( std::mktime( &t ) );}
inline bool s1706::operator==( const s483* p ) const{
return memcmp( &s349, &((s1706*)p )->s349, sizeof(tm) );}
inline bool s1706::operator<( const s483* p ) const{
tm t = s349, t1 = ( (s1706*)p )->s349;
return ( std::mktime( &t ) < std::mktime( &t1 ) );}
wstring s1706::to_wstring( uint32_t s1565 ) const{
wstring s685;
if( s1743 == s1739 || s1743 == s1740 ) {
s685 = std::to_wstring( 1900 + s349.tm_year ) + L"-";
if( s349.tm_mon < 9 )
s685 += L"0";
s685 += std::to_wstring( 1 + s349.tm_mon ) + L"-";
if( s349.tm_mday < 10 )
s685 += L"0";
s685 += std::to_wstring( s349.tm_mday );}
if( s1743 == s1740 )
s685 += L" ";
if( s1743 == s1742 || s1743 == s1740 ) {
if( s349.tm_hour < 10 )
s685 += L"0";
s685 += std::to_wstring( s349.tm_hour ) + L":";
if( s349.tm_min < 10 )
s685 += L"0";
std::to_wstring( s349.tm_min ) + L":";
if( s349.tm_sec < 10 )
s685 += L"0";
std::to_wstring( s349.tm_sec );}
return s685;}
s1602::s1602( s262* s300, s272* s588, s1905& s77, bool typed, const s263* ast_ )
: s336( s300, s588, ast_ ){
if( s77.size() )
load( s77, typed, false );
if( !s493 )
s493 = Types.s272;
if( !s77.empty() )
s1679( s7::s867 );}
s1602::s1602( s262* s300, s272* s588, const s143* s1644, const s263* ast_ )
: s336( s300, s588, ast_ ){
TDException s968( s7::CLObjectVal_ctor1, s932, ast_ );
if( s1644->s156( s7::s465 ) ) {
wstring sname = s4::s52( s263::s302( *s1644, s7::s465 ),
s48 );
(( s143*)s1644)->s159( L"name", new s141( sname ) );
(( s143*)s1644)->s1631( s7::s465 );}
try {
s1642( s1644, true, s482::s146 );}
catch( s16* e ) {
throw s968.s1000( L"construction of TSD object failed: " + e->Msg() );}
s493 = Types.s272;
s1262();}
s1602::s1602( const s1602& right, s483* s2124 )
: s336( right.s300, (s272*)s2124, right.s603() ), s628( right.s628 ){
s493 = Types.s272;
wh = right.wh;}
void s1602::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1602::s1236, Types.s272,
{ s1122(), s1122( { s1153 } ), s1122( { Types.String, Types.Bool } ) }, 0, 2 ) ) );
s348.insert( make_pair( L"get-Int", new s337( L"get-Int", &s1602::s1636, Types.Int,
{ s1122( { Types.String } ) }, 1, 1, true )));
s348.insert( make_pair( L"get-String", new s337( L"get-String", &s1602::s1637, Types.String,
{ s1122( { Types.String } ) }, 1, 1, true )));
s348.insert( make_pair( L"load", new s337( L"load", &s1602::s1641, Types.Null,
{ s1122( { Types.String } ), s1122( { Types.String, Types.Bool } ) }, 1, 2, true )));
s348.insert( make_pair( L"load-from-file", new s337( L"load-from-file", &s1602::s1639, Types.Null,
{ s1122( { Types.String } ), s1122( { Types.String, Types.String } ) }, 1, 2, true )));}
void s1602::s500( const s272* s879, bool ){
s1262();}
s483* s1602::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1602( s300, s588, L"", ast_ );}
s483* s1602::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
if( s.find( L"Object(" ) == 0 ) {
return new s1602( s300, s588, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s355( s588, std::vector<s271*>(), &s701 );}
return NULL;}
s1061 s1602::s1188( s1905& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" ) {
auto it = s628.get( l[0]->to_wstring() );
s685 = it->s352();}
return s685;}
void s1602::load( s1905& s77, bool typed, bool s1634 ){
TDException s968( s7::s1598, s932, s603(), L"Failed to load object" );
s948 s1051 = new s945( s77, s1634 );
vector<s9<s143>> s662;
s1051->read( s662, L"" );
if( s662.size() != 1 )
throw s968.s1000( L"wrong object data: the source contains " + std::to_wstring( s662.size() ) + L" objects"  );
s143* obj = s662[0];
if( obj->s156( s7::s465 ) ) {
wstring sname = s4::s52( s263::s302( *obj, s7::s465 ),
s48 );
obj->s159( L"name", new s141( sname ) );}
s1642( obj, typed );}
void s1602::s1642( const s143* obj, bool typed, s482::s145 ap ){
vector<pair<wstring, s142>> s144;
obj->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( typed ) {
s947 past = new s263( s144[n].first, *s144[n].second, NULL );
s483* dv = s300->TR().s518( *past, (s272*)this, L"::" );
dv->s506( s144[n].first );
dv->s1262();
s628.s541( s144[n].first, dv, ap );}
else {
s628.s541( s144[n].first, s144[n].second, ap );}}}
void s1602::s1632( s482::s535& sm ) const{
const s482::s535& tb = s628.Table();
s482::s535::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s494() == s476 )
(void)0;
else {
s483* dv = (s483*)it->second->s335(0,0);
sm.insert( make_pair( it->first, dv ));}}}
s271* s1602::s335( s591* s2057, s272* impl ) const{
return new s1602( *this, impl ? impl : ns );}
void s1602::s356( s271* p ) const{
if( p->s352() == Types.s272 )
((s1602*)p)->s628 = s628;
else
throw new s16( L"No conversion to type " + s353() );}
#undef s698
#define s698 ((s1602*)(s484*)*s274)
inline void s1602::s1236( s483** s274, size_t s498 ){
s1602* r = (s1602*)s274[1];
wstring sobj;
bool typed = true;
if( s498 > 2 ) {
sobj = ( (s359*)s274[2] )->s320();
if( s498 == 4 )
typed = (bool)*s274[3];}
s1602* s2149 = new s1602( r->s300, r->ns, sobj, typed );
s2149->s500( r->ns );
*s274 = (s483*)s2149;}
inline void s1602::s1636( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
*((s346*)*s274)->s357() = (int)*( (s1602*)DR )->s628.get( s152 );}
inline void s1602::s1637( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
*((s359*)*s274)->s357() = ( (s1602*)DR )->s628.get( s152 )->to_wstring();}
inline void s1602::s1660( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
s346* pd  = (s346*)( (s1602*)DR )->s628.get( s152 );
*pd->s357() = (int)*s274[3];}
inline void s1602::s1662( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
s359* pd  = (s359*)( (s1602*)DR )->s628.get( s152 );
*pd->s357() = s274[3]->to_wstring();}
inline void s1602::s1641( s483** s274, size_t s498 ){
s1602* po = (s1602*)DR;
wstring s77 = s274[2]->to_wstring();
bool typed = true;
if( s498 == 3 )
typed = (bool)*s274[2];
po->load( s77, typed, false );}
inline void s1602::s1639( s483** s274, size_t s498 ){
s1602* po = (s1602*)DR;
wstring s189 = s274[2]->to_wstring();
bool typed = true;
if( s498 == 3 )
typed = (bool)*s274[2];
po->load( s189, typed, true );}
size_t s1602::s322() const{
return (size_t)this; //hash<bool>{}( s349 );
}
inline bool s1602::operator==( const s483* p ) const{
return this == p; // ( s628 == ( (s1602*)p )->s628 );
}
inline bool s1602::operator<( const s483* p ) const{
return this < p; // ( s628 < ( (s1602*)p )->s628 );
}
wstring s1602::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"Object: { \n";
s685 += s628.to_wstring( s1565 );
s685 += L"\n }";
return s685;}
void s1602::s1960( s1905& s ) {
load( s, true, false );}
void s1602::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << endl;
s628.s304( pd, s197 + s419 );}
s371::s371( s1905& s, s262* s300, s472 cat, bool _cnst )
: s484( s300, cat ), s372( s ), s376( 0 ), s1168( _cnst ){
assert( cat == s473 || cat == s475 || cat == s481 || cat == s1063 );
if( cat == s473 ) {
if( 0 && s[0] == L':' ) {
s492 = s1063;
s493 = Types.No;
s373 = (s483*)Types( s300, Types.No );}
else if( s300->s221( *this ) ){
s492 = s481;
s493 = Types.No;}
else
s492 = s475;}}
s371::s371( const s371& right, s483* s2184 )
: s484( right.s300, right.s492 ), s372( right.s372 ),
s373( s2184 ? s2184 : right.s373 ), s374( right.s374 ), 
s375( right.s375 ),s376( right.s376 ), s1168( right.s1168 ){
if( s492 == s481 )
s373 = right.s373;
s493 = right.s493;
wh = right.wh;}
void s371::s500( const s272* s587, bool fr ){
if( false && s300->s221( *this ) ) {
s492 = s481;
s493 = Types.No;}
else {
if( !s587->s556( s372, this, s587->s2171(), fr ) ) {
if( s492 == s1063 )
return;
throw new TDException( 0, s930, NULL, s372 );}
if( s374 )
s493 = s374->s352();
else if( s492 == s1337 )
s493 = s373.s15<s371*>()->s377()->s352();
else
assert( 0 );}
s1262();}
void s371::reset(){
s375.clear();
s376 = 0;
s374 = NULL;
s373 = NULL;}
const s485 s371::s381() {
if( s373.s14() && s373->s494() == s1337 )
return s373.s15<s1600*>()->s2118().s15<s484*>();
return s373; }
void s371::s382( s483* p ){
s373 = p; }
s483* s371::s377() const{
if( s492 == s1063 )
return s373.s15<s483*>();
else if( s492 == s1337 )
return s373.s15<s371*>()->s377();
if( s375.empty() )
return s373.s15<s483*>();
s484* s685 = NULL;
if( s373->s494() == s1337 )
s685 = s373.s15<s1600*>()->s598( *(size_t*)&s375[0] );
else
s685 = s373.s15<s272*>()->s598( *(size_t*)&s375[0] );
for( size_t n = 1; n < s376; ++n )
s685 = ((s272*)s685->s496())->s598( *( (size_t*)&s375[0] + n ) );
return s685->s496();}
s483* s371::s378(){
if( s375.empty() )
return s373.s15<s483*>();
s483*	s685 = ((s483*)s373.s15<s272*>()->s598( *(size_t*)&s375[0] ));
for( size_t n = 1; n < s376; ++n )
s685 = (s483*)((s272*)s685)->s598( *( (size_t*)&s375[0] + n ) );
return s685;}
void s371::s982( const std::vector<std::wstring> &s820 ){
auto it = std::find( begin( s820 ), end( s820 ), s617() );
if( it != end( s820 ) ) {
s492 = s1063;
s493 = Types.No;
s376 = std::distance( begin( s820 ), it );
s373 = new s346( NULL, (int)s376 ); //s779.s15<s483*>();
}}
s486 s371::s497( s483** s274, size_t s498 ){
return s377()->s497( s274, s498 );}
s483* s371::s496(){
s485 s685 = s377();
if( s685.s14() )
return s685->s496();
else
return NULL;}
/*bool s371::s501( const s483* s502 ) const
{
if( s502->s494() == s475 )
return s377()->s501( ((s371*)s502)->s377() );
return s377()->s501( s502 );
}*/
s271* s371::s335( s591* s2057, s272* impl ) const{
s371* s685 = new s371( *this, NULL );
return s685;}
void s371::s2133( s591* s2057, s272* impl, bool s2177 ){
if( s492 != s1063 && (1 || s373.s14() )) {
reset();
s500( (s272*)s2057, s2177 );}}
void s371::s379( size_t off, const s483* proto ){
s375.push_back( off );
s376 = s375.size();
s374 = proto;}
void s371::s1343( s371* ptr ){
s492 = s1337;
s375.clear();
s376 = 0;
s373 = ptr;
s374 = NULL;}
void s371::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2156[20];
#ifdef WIN32		
_swprintf( s2156, L"%p", (uint64_t*)s373.s15<void*>() );
#else
swprintf( s2156, 20, L"%06x", (uint64_t*)s373.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s197 ) << L"DataRef : " << s372
<< L"; Root: " << s2156;
if( s375.size() )
buf << L"; off: " << s375[0];
buf << endl;
if( !s197 && s373.s14() ) {
buf << s4::fill_n_ch( L' ', s197 ) << L"RootPtr : " << endl;
s373->s304( pd, s197 + s419 );}}
void s1600::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2190[20];
#ifdef WIN32		
_swprintf( s2190, L"%p", (uint64_t*)pobj.s15<void*>() );
#else
swprintf( s2190, 20, L"%06x", (uint64_t*)pobj.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s197 ) << L"DataPointer : " 
<< L" Pointer: " << s2190 << endl;
if( pobj.s14() ) {
buf << s4::fill_n_ch( L' ', s197 ) << L"Object : " << endl;
pobj->s304( pd, s197 + s419 );}}
template<class s1312, class Der>
s336::s341 s1306<s1312, Der>::s348;
template<class s1312, class Der>
const s336::s341& s1306<s1312, Der>::s342() const{
return s348; }
template<class s1312, class Der>template <class s1530, class s1531>
void s1306<s1312, Der>::s1532( s483* src, s483* s778 ){
*((s1530*)s778)->s357() = (s1531) ( (Der*)src )->s349;}
template <class s1312, class Der>
s483* s1306<s1312, Der>::s1536( const s483* p ) const{
Der* s685 = new Der( p->Pass() );
if( p->s1541( s352() ) )
p->s356( s685 );
s685->s1262();
return s685;}
template <class s1312, class Der>
size_t s1306<s1312, Der>::s322() const{
return (size_t)s349;}
template <class s1312, class Der>
inline bool s1306<s1312, Der>::operator==( const s483* p ) const{
return ( (Der*)p )->s349 == s349;}
template <class s1312, class Der>
inline bool s1306<s1312, Der>::operator<( const s483* p ) const{
return s349 < ( (Der*)p )->s349;}
template <class s1312, class Der>
void s1306<s1312, Der>::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349 << endl;}
#define s1525 s493
template <class s1312, class Der>
void s1306<s1312, Der>::s350(){
s348.insert( make_pair( L"abs", new s337( L"abs", &s1306<s1312, Der>::s404, s1525,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s1306<s1312, Der>::s387, s1525,
{ s1122( { /*Der::proto->s352()*/ s1512::s1271 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"sum", new s337( L"sum", &s1306<s1312, Der>::s388, s1525,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"dif", new s337( L"dif", &s1306<s1312, Der>::s389, s1525,
{ s1122( ), s1122( { s1512::s1271, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"mul", new s337( L"mul", &s1306<s1312, Der>::s390, s1525,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"div", new s337( L"div", &s1306<s1312, Der>::s391, s1525,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"pow", new s337( L"pow", &s1306<s1312, Der>::s392, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"pow", new s337( L"pow", &s1306<s1312, Der>::s392, s1150,
{ s1122( { s1150 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s1306<s1312, Der>::s393, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"difeq", new s337( L"difeq", &s1306<s1312, Der>::s394, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"muleq", new s337( L"muleq", &s1306<s1312, Der>::s395, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"diveq", new s337( L"diveq", &s1306<s1312, Der>::s396, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s1306<s1312, Der>::s413, s1148,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s1306<s1312, Der>::s398, s1148,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"less", new s337( L"less", &s1306<s1312, Der>::s399, s1148,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"greater", new s337( L"greater", &s1306<s1312, Der>::s400, s1148,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"leq", new s337( L"leq", &s1306<s1312, Der>::s401, s1148,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"geq", new s337( L"geq", &s1306<s1312, Der>::s402, s1148,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"neq", new s337( L"neq", &s1306<s1312, Der>::s403, s1148,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"within", new s337( L"within", &s1306<s1312, Der>::s2097, s1148,
{ s1122( { s1512::s1549, s1512::s1549 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"max", new s337( L"max", &s1306<s1312, Der>::s1965, s1525,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"min", new s337( L"min", &s1306<s1312, Der>::s1966, s1525,
{ s1122( { s1512::s1549, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"mod", new s337( L"mod", &s1306<s1312, Der>::s405, s1525,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"sqrt", new s337( L"sqrt", &s1306<s1312, Der>::s406, s1150,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"nroot", new s337( L"nroot", &s1306<s1312, Der>::s407, s1150,
{ s1122( { s1151 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"to-Double", new s337( L"to-Double", &s1306<s1312, Der>::s408, s1150,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Byte", new s337( L"to-Byte", &s1306<s1312, Der>::s1596, s1308,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s1306<s1312, Der>::s412, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Long", new s337( L"to-Long", &s1306<s1312, Der>::s1547, s1526,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-ULong", new s337( L"to-ULong", &s1306<s1312, Der>::s1548, s1527,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-String", new s337( L"to-String", &s1306<s1312, Der>::s1501, s1153,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"read", new s337( L"read", &s1306<s1312, Der>::s409, s1525,
{ s1122() }, 0, 0, false ) ) );}
template<class s1312, class Der>
s1061 s1306<s1312, Der>::
s1188( const std::wstring& s1553, const std::vector<s485>& l ) const{
s1061 s685 = 0;
if( 0 && s1553 == L"mod" )
s685 = this->s352();
return s685;}
#undef s698
#define s698 ((Der*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
template<class s1312, class Der>
inline void s1306<s1312, Der>::s387( s483** s274, size_t n ){
s274[2]->s356( s274[1] );
s274[1]->s1262();
*s274 = s274[1];}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s404( s483** s274, size_t s498 ){
s1312 t = ( (Der*)DR )->s349;
if( t >= 0 )
s698->s349 = t;
else
s698->s349 = -t;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s388( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 += tmp.s349;}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s389( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
if( s498 == 2 )
s698->s349 = -s698->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 -= tmp.s349;}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s390( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 *= tmp.s349;}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s391( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 /= tmp.s349;
}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s392( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
s698->s349 =(s1312) std::pow( (double)( (Der*)DR )->s349, (double)s698->s349 );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s393( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 += s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s394( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 -= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s395( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 *= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s396( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 /= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s398( s483** s274, size_t s498 ){
bool s685 = true;
Der tmp;
for( size_t i = 2; i < s498; ++i ) {
s274[i]->s356( &tmp );
if( ( (Der*)DR )->s349 != tmp.s349 ) {
s685 = false;
break;}}
*s699->s357() = s685;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s413( s483** s274, size_t s498 ){
if( ((bool)( (Der*)DR )->s349) == false )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s399( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 < tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s400( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 > tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s401( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 <= tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s402( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 >= tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s403( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 != tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s2097( s483** s274, size_t s498 ){
Der tmp, tmp1;
s274[2]->s356( &tmp );
s274[3]->s356( &tmp1 );
if( ( (Der*)DR )->s349 >= tmp.s349 && ((Der*)DR)->s349 <= tmp1.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1965( s483** s274, size_t s498 ){
Der tmp;
*s698->s357() = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
if( *s698->s357() < tmp.s349 )
*s698->s357() = tmp.s349;}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1966( s483** s274, size_t s498 ){
Der tmp;
*s698->s357() = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
if( *s698->s357() > tmp.s349 )
*s698->s357() = tmp.s349;}}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s405( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( tmp.s349 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s698->s349 = ((Der*)DR)->s349 % tmp.s349;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s406( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = ::sqrt( (double)*DR );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s407( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = ::pow( ((Der*)DR)->s349, 1.0 / (double)*PARN( 2 ) );
}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s408( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = (double)*DR;}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1596( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s412( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1547( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1548( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s1501( s483** s274, size_t s498 ){
*( (s359*)s274[0] )->s357() = DR->to_wstring();}
template<class s1312, class Der>
inline void s1306<s1312, Der>::s409( s483** s274, size_t s498 ){
int i;
wstring s93 = L"";//( (s359*)s274[2] )->to_wstring();
wstring si = consutils::s100( s93, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s698->s349 = i;}
s346::s346( s262* s300 )
: s1306( s300, NULL, NULL ){
s493 = Types.Int;
s349 = (s1386)s300->TR().s1257();
s1679( s7::s868 );}
s346::s346( s262* s300, int i )
: s1306( s300, NULL, NULL ){
if( !Types.Bool ) {
s493 = 0;
wh = s7::s868;}
else {
s493 = Types.Int;
s349 = i;
s1262();}}
s346::s346( const s346& r )
: s1306( r ){}
s346::s346( s262* s300, const std::wstring& s, size_t& pos )
: s1306( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1262();}
else
s153 = s300->TR().s1257();
s349 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Int;}
s483* 
s346::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
s483* s685 = NULL;
size_t pos = 0;
if( s.find( L"Int(" ) == 0 ) {
s685 = new s346( s300, s.substr( 4, s.size() - 5 ), pos );}
else if( s.find( L"Int" ) == 0 ) {
s685 = s355( NULL, std::vector<s271*>(), &s701 );}
else {
if( s == L"-0" )
return s1521;
try {
s685 = new s346( s300, s, pos );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
s685 = NULL;
else
throw e;}}
return s685;}
void s346::s350(){
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );
s300->TR().s1162( s493, s7::s1524, s1512::s1549 );
s1306<int32_t, s346>::s350();
s348 = s1306<int32_t, s346>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s346::s1236, s1151,
{ s1122(), s1122( { Types.String } ), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s300->TR().s1533( s493, Types.Long );}
s483* s346::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s346( s300, L"", pos );}
void s346::s500( const s272* s879, bool ){
s1262();}
inline bool
s346::s1541( s1061 s619 ) const{
if( ( s619 == s1527 && s349 >= 0 ) ||
( s619 == s1308 && s349 >= 0 && s349 <= 255 ) )
return true;
return s271::s1541( s619 );}
s271* s346::s335( s591* s2057, s272* impl ) const{
return new s346( *this );}
void s346::s356( s271* p ) const{
if( p->s352() == Types.Int )
*((s346*)p)->s357() = s349;
else if( p->s352() == s1308 )
*((s1295*)p)->s357() = s349;
else if( p->s352() == s1526 )
*((s1303*)p)->s357() = s349;
else if( p->s352() == s1527 )
*((s1529*)p)->s357() = s349;
else if( p->s352() == s1148 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"No conversion to type " + p->s353() );}
inline void s346::s1236( s483** s274, size_t s498 ){
s346* plv = NULL;
if( s498 == 3 && s274[2]->s352() == Types.String ) {
size_t pos = 0;
plv = new s346( ( (s346*)s274[1] )->s300, *( (s359*)s274[2] )->s357(), pos );}
else {
plv = new s346( ( (s346*)s274[1] )->s300, 0 );
s346& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if( s498 == 3 ) {
s483* p = s274[2];
if( p->s352() == s1151 )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == s1150 )
lv.s349 = ( s1386 )*( (s358*)p )->s357();
else if( p->s352() == s1148 )
lv.s349 = ( s1386 )*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Int from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Int() constructor" );}
plv->s1262();
s274[0] = plv;}
wstring s346::to_wstring( uint32_t s1565 ) const {
wstring s685;
if( s349 > 0 && ( s1565 & s1560 ) )
s685 = L"+";
if( s1565 & s1559 )
s685 += s4::s1564( s349 );
else
s685 += std::to_wstring( s349 ); 
return s685;}
void s346::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
ss << s349;}
void s346::to_null(){
s271::to_null();
s349 = 0;}
void s346::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349;}
s1303::s1303( s262* s300 )
: s1306( s300, NULL, NULL ){
s493 = Types.Long;
s349 = s300->TR().s1257();
s1679( s7::s868 );}
s1303::s1303( s262* s300, int64_t i )
: s1306( s300, NULL, NULL ){
if( !Types.Long ) {
s493 = 0;
s1679( s7::s868 );}
else {
s493 = Types.Long;
s349 = i;
s1262();}}
s1303::s1303( const s1303& r )
: s1306( r ){}
s1303::s1303( s262* s300, const std::wstring& s, size_t& pos )
: s1306( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1544( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1262();}
else
s153 = s300->TR().s1257();
s349 = (int64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Long;}
void s1303::s350(){
s1306<int64_t, s1303>::s350();
s348 = s1306<int64_t, s1303>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1303::s1236, s1526,
{ s1122(), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );
s300->TR().s1162( s493, s7::s1524, s1512::s1549 );}
s483* s1303::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1303( s300, L"", pos );}
void s1303::s500( const s272* s879, bool ){
s1262();}
s271* s1303::s335( s591* s2057, s272* impl ) const{
return new s1303( *this );}
void s1303::s356( s271* p ) const{
if( p->s352() == Types.Long )
*((s1303*)p)->s357() = s349;
else if( p->s352() == s1151 )
*((s346*)p)->s357() = (s346::s1386)s349;
else if( p->s352() == s1527 )
*((s1529*)p)->s357() = s349;
else if( p->s352() == s1148 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1303::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1303( s300, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1303( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1303::s1236( s483** s274, size_t s498 ){
s1303* plv = new s1303( ( (s1303*)s274[1] )->s300, (s1386)0 );
s1303& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if (s498 == 3){
s483* p = s274[2];
if( p->s352() == Types.Int )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == s1150 )
lv.s349 = (s1386)*( (s358*)p )->s357();
else if( p->s352() == s1148 )
lv.s349 = (s1386)*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Long from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1262();
s274[0] = plv;}
wstring s1303::to_wstring( uint32_t s1565 ) const{
wstring s685;
if( s349 > 0 && ( s1565 & s1560 ) )
s685 = L"+";
if( s1565 & s1559 )
s685 += s4::s1564( s349 );
else
s685 += std::to_wstring( s349 );
return s685;}
void s1303::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
ss << s349;}
s1529::s1529( s262* s300 )
: s1306( s300, NULL, NULL ){
s493 = Types.s1528;
s349 = s300->TR().s1257();
s1679( s7::s868 );}
s1529::s1529( s262* s300, int64_t i )
: s1306( s300, NULL, NULL ){
if( !Types.s1528 ) {
s493 = 0;
s1679( s7::s868 );}
else {
s493 = Types.s1528;
s349 = i;
s1262();}}
s1529::s1529( const s1529& r )
: s1306( r ){}
s1529::s1529( s262* s300, const std::wstring& s, size_t& pos )
: s1306( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1545( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1262();}
else
s153 = s300->TR().s1257();
s349 = (uint64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.s1528;}
void s1529::s350(){
s1306<s1386, s1529>::s350();
s348 = s1306<s1386, s1529>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1529::s1236, s1527,
{ s1122(), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"abs", new s337( L"abs", &s1529::s404, s1527,
{ s1122(), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"dif", new s337( L"dif", &s1529::s389, s1527,
{ s1122(), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );
s300->TR().s1162( s493, s7::s1524, s1512::s1549 );}
s483* s1529::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1529( s300, L"", pos );}
void s1529::s500( const s272* s879, bool ){
s1262();}
s271* s1529::s335( s591* s2057, s272* impl ) const{
return new s1529( *this );}
void s1529::s356( s271* p ) const{
if( p->s352() == Types.s1528 )
*((s1529*)p)->s357() = s349;
else if( p->s352() == s1526 )
*((s1303*)p)->s357() = s349;
else if( p->s352() == s1151 )
*((s346*)p)->s357() = (s346::s1386)s349;
else if( p->s352() == s1148 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1529::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1529( s300, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1529( s300, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1529::s1236( s483** s274, size_t s498 ){
s1529* plv = new s1529( ( (s1529*)s274[1] )->s300, (s1386)0 );
s1529& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if (s498 == 3){
s483* p = s274[2];
if( p->s352() == Types.Int )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == Types.Long )
lv.s349 = *( (s1303*)p )->s357();
else if( p->s352() == Types.Double )
lv.s349 = (s1386)*( (s358*)p )->s357();
else if( p->s352() == Types.Bool )
lv.s349 = (s1386)*( (s360*)p )->s357();
else
throw new s16( L"no conversion to ULong from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1262();
s274[0] = plv;}
wstring s1529::to_wstring( uint32_t s1565 ) const{
wstring s685;
if( s349 > 0 && ( s1565 & s1560 ) )
s685 = L"+";
if( s1565 & s1559 )
s685 += s4::s1564( s349 );
else
s685 += std::to_wstring( s349 );
return s685;}
void s1529::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
ss << s349;}
s1295::s1295( s262* s300 )
: s1306( s300, NULL, NULL ){
s493 = Types.Byte;
s349 = (s1386)s300->TR().s1257();
s1679( s7::s868 );}
s1295::s1295( s262* s300, tdbyte_t i )
: s1306( s300, NULL, NULL ){
s493 = Types.Byte;
if( !s493 )
s1679( s7::s868 );
else {
s349 = i;
s1262();}}
s1295::s1295( const s1295& r )
: s1306( r.s300, r.ns, NULL ){
wh = r.wh;
s493 = r.s493;}
s1295::s1295( s262* s300, const std::wstring& s, size_t& pos )
: s1306( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s153, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1679( s7::s867 );}
else
s153 = s300->TR().s1257();
s349 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Byte;}
void s1295::s350(){
s1306<tdbyte_t, s1295>::s350();
s348 = s1306<tdbyte_t, s1295>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1295::s1236, s1308,
{ s1122(), s1122( { s1512::s1271 } ) }, 0, 1 ) ) );
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );
s300->TR().s1162( s493, s7::s1524, s1512::s1549 );}
s483* s1295::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1295( s300, L"", pos );}
void s1295::s500( const s272* s879, bool ){
s1262();}
s271* s1295::s335( s591* s2057, s272* impl ) const{
return new s1295( *this );}
void s1295::s356( s271* p ) const{
if( p->s352() == Types.Byte )
*((s1295*)p)->s357() = s349;
else if( p->s352() == s1526 )
*((s1303*)p)->s357() = s349;
else if( p->s352() == s1527 )
*((s1529*)p)->s357() = s349;
else if( p->s352() == s1148 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1295::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1295( s300, s, pos );
}*/
if( s701.s1309() == s352() )
return new s1295( s300, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1295( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1295::s1236( s483** s274, size_t s498 ){
s1295* plv = new s1295( ( (s1295*)s274[1] )->s300, 0 );
s1295& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if( s498 == 3 )
s274[2]->s356( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1262();
s274[0] = plv;}
void s1295::s1935( Stream* s1934 ) const{
auto flags = s1934->s1930();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s349;
s1934->s1480( ss.str() );}
s1573::s1573( s262* s300 )
: s1306( s300, NULL, NULL ){
s493 = Types.Char;
s349 = (s1386)s300->TR().s1257();
s1679( s7::s868 );}
s1573::s1573( s262* s300, wchar_t i )
: s1306( s300, NULL, NULL ){
s493 = Types.Char;
if( !s493 )
s1679( s7::s868 );
else {
s349 = i;
s1262();}}
s1573::s1573( const s1573& r )
: s1306( r.s300, r.ns, NULL ){
wh = r.wh;
s493 = r.s493;}
s1573::s1573( s262* s300, const std::wstring& s, size_t& pos )
: s1306( s300, NULL, NULL ){
if( s.size() ) {
s349 = s[pos];}
s493 = Types.Char;}
void s1573::s350(){
s1306<wchar_t, s1573>::s350();
s348 = s1306<wchar_t, s1573>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1573::s1236, s1579,
{ s1122(), s1122( { s1579 } ), s1122( { s1153 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"isupper", new s337( L"isupper", &s1573::s2244, s1148,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"islower", new s337( L"islower", &s1573::s2242, s1148,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"isspace", new s337( L"isspace", &s1573::s2243, s1148,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"tolower", new s337( L"tolower", &s1573::s890, s1579,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"toupper", new s337( L"toupper", &s1573::s891, s1579,
{ s1122() }, 0, 0 )));
s300->TR().s1162( s493, s7::s1413, s1512::s1271 );
s300->TR().s1162( s493, s7::s1524, s1512::s1549 );}
s483* s1573::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1573( s300, L"", pos );}
void s1573::s500( const s272* s879, bool ){
s1262();}
s271* s1573::s335( s591* s2057, s272* impl ) const{
return new s1573( *this );}
void s1573::s356( s271* p ) const{
if( p->s352() == Types.Char )
*( (s1573*)p )->s357() = s349;
else if( p->s352() == s1151 )
*( (s346*)p )->s357() = s349;
else if( p->s352() == s1526 )
*( (s1303*)p )->s357() = s349;
else if( p->s352() == s1527 )
*( (s1529*)p )->s357() = s349;
else if( p->s352() == s1148 )
*( (s360*)p )->s357() = ( s349 != 0 );
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1573::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
size_t pos = 0;
if( s701.s1309() == s352() )
return new s1573( s300, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1573( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1573::s1236( s483** s274, size_t s498 ){
s1573* plv = new s1573( ( (s1573*)s274[1] )->s300, 0 );
s1573& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if( s498 == 3 )
s274[2]->s356( plv );
else
throw new s16( L"unknown parameter to Char() constructor" );
lv.s1262();
s274[0] = plv;}
inline void s1573::s2244( s483** s274, size_t s498 ){
wchar_t wc = ((s1573*)DR)->s349;
*((s360*)*s274)->s357() = iswupper( wc );}
inline void s1573::s2242( s483** s274, size_t s498 ){
wchar_t wc = ((s1573*)DR)->s349;
*((s360*)*s274)->s357() = iswlower( wc );}
inline void s1573::s2243( s483** s274, size_t s498 ){
wchar_t wc = ((s1573*)DR)->s349;
*((s360*)*s274)->s357() = iswspace( wc );}
inline void s1573::s891( s483** s274, size_t s498 ){
wchar_t wc = ((s1573*)DR)->s349;
((s1573*)DR)->s349 = towupper( wc );
*s274 = s274[1];}
inline void s1573::s890( s483** s274, size_t s498 ){
wchar_t wc = ((s1573*)DR)->s349;
((s1573*)DR)->s349 = towlower( wc );
*s274 = s274[1];}
void s1573::s1935( Stream* s1934 ) const{
auto flags = s1934->s1930();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s349;
s1934->s1480( ss.str() );}
const wstring s471 = L"";
s482 s687;
s272::s272( s262* s300, s1061 s340, s472 pc/* = s473*/, const s263* ast_, s272* ns_, s2193 st )
: s483( s300, pc, ast_, ns_ ), s625( NULL ), s626( NULL ), 
s1663( s7::s1601, s300, s475 ), s347( s471 ), //s633( s687 ),
s629( NULL )/*, s1360( ++s1361 )*/, s2197( st )
{
s625 = this;
s493 = s340;}
s272::s272( const s272& proto, std::vector<s485>& s705, const s263* ast_, s272* ns_ )
: s483( proto.s300, /*s480*/proto.s492, ast_, ns_ ? ns_ : proto.ns ), s625( &proto ), 
s626(NULL), s1663( s7::s1601, s300, s475 ), s347( proto.s347 ),
s629( proto.s629 ), //s633( s687 ),
s631( proto.s631 ), s2197( s2204 )//, s1360( ++s1361 )
{
s493 = proto.s493;
if( s492 == s478 || s492 == s2166 )
s492 = s480;
if( proto.s626 )
proto.s626->s643( this );
proto.s628.copy( s628, this, NULL, s482::s147 );
for( size_t n = 0; n < s631.size(); ++n )
s630.push_back( s628.get( s631[n].s617() ) );
auto s824 = s628.Table();
auto it = s824.begin();
for( ; it != s824.end(); ++it )
it->second->s2133( NULL, this );
if( s705.size() ) {
s842* p = (s842*)s628.get( s7::s429 );
p->s596( s705 );}
s1663.s351( s493 );
if( s492 == s480 )
s1679( proto.s618() );}
s272::s272( s1905& s676, s262* s300, s472 pc, const s263* ast_, s272* ns_,
s2193 st )
: s483( s300, pc, ast_, ns_ ), s625( NULL ), s626( NULL ), 
s1663( s7::s1601, s300, s475 ), s347( s471 ), s278( s676 ),
s629( NULL ), s2197( st )//, s1360( ++s1361 )//, s633( *new s482() )
{
s625 = this;}
s272::s272( s263& s701, s262* s300, s472 pc, s272* ns_, s536 am,
s623& cl, s622& cnl, s624& al, s2193 st )
: s483( s300, pc, &s701, ns_ ), s625(NULL), s626( NULL ), 
s1663( s7::s1601, s300, s475 ), s347( s701.s299() ), s278( s701.s298() ),
s628( am ), s629( NULL ), s2197( st )//, s1360( ++s1361 ) //,s633( *new s482() )
{
if( s278.find( L" " ) != string::npos )
throw new s16( L"Malformed class name: " + s278 );
s625 = this;
if( pc == s478 || pc == s2166 ) {
if( cl.find( s701.s299() ) != cl.end() )
throw new s16( L"class already exists: " + s701.s299() );
size_t s2165 = cnl.size();
size_t s2194 = s701.s268( s2191 ).s56();
if( s701.s156( s7::s469 ) ) {
wstring anc = s701.s292( s7::s469 )->s291();
cnl.push_back( make_pair( s701.s299(), /*anc*/s2194 ) );
}
if( s701.s156( s7::s2160 ) ) {
wstring s2162 = s701.s292( s7::s2160 )->s291();
cnl.push_back( make_pair( s701.s299(), /*s2162*/s2194 ) );
}
if( cnl.size() == s2165 )
cnl.push_back( make_pair( s701.s299(), /*L""*/s2194 ) );
cl.insert(make_pair(s701.s299(), this));}
if( al.find( s701.s299() ) != al.end() )
throw new s16( L"module already defined: " + s701.s299() );
al.insert(make_pair(s701.s299(), &s701));
s506( L"proto" );
s263::s275& s702 = s701.s293();
s263::s275::iterator it = s702.begin();
vector<pair<wstring,wstring>> s694;
for( ; it != s702.end(); ++it ) {
if( it->second->s297() == s225 ) {
if( it->first == s7::s469 ) {
s627 = it->second->s291();}}
else if( it->second->s297() == s227 ) {
wstring s658 = it->first;
s512 pv = s515;
am = s510;
size_t s689 = s658.find_first_of( s4::s48 );
if( s689 != string::npos ) {
vector<wstring> s688;
s4::s57( it->first, wstring( 1, s658[s689] ), s688 );
if( s688.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
if( s688[0] == s7::s451 || s688.size() == 3 ) {
pc = s478;
if( s688.size() == 3 ) {
if( s688[0] == s7::s448 )
am = s509;
else if( s688[0] == s7::s450 )
am = s511;
else if( s688[0] != s7::s449 )
throw new s16( L"invalid access mode name: " + it->first );
s658 = s688[2];}
else
s658 = s688[1];
if( s702.find( s658 ) != s702.end() )
throw new s16( L"duplicated object name: " + it->first );
it->second->s294( s658 );
s694.push_back( make_pair( it->first, s658 ) );}
else if( s688[0] == L"access" && ( s688[1] == L"allow" || s688[1] == L"deny" )) {
if( s688[1] == L"allow" )
pv = s514;
pc = s479;}
else
throw new s16( L"unknown object type: " + s688[0] );}
if( pc == s479 ) {
s628.s549( pv, it->second );}
else {
s272* ob = new s272( *it->second, s300, s478, this, am, cl, cnl, al, s2200 );
s628.s541( ob->s299(), ob );}}}
for( size_t n = 0; n < s694.size(); ++n ) {
auto it = s702.find( s694[n].first );
s702.insert(make_pair(s694[n].second, it->second ));
s702.erase( it );}}
s272::~s272(){
s628.reset();
s630.clear();
s631.clear();}
s483* s272::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return s635( s701, s588, s334 );}
void s272::s644( const s482& s274 ){}
bool
s272::s501( const s483* s502 ) const{
if( s502->s352() == s352() )
return true;
if( s626 )
return s626->s501( s502 );
return false;}
bool
s272::s730( s1905& f ) const{
return s628.s156( f );}
void s272::s154( s263& s701 ){
TDException s968( s7::s2159, s932, &s701 );
s263::s275& s702 = s701.s293();
s263::s275::iterator it = s702.begin();
for( ; it != s702.end(); ++it ) {
s263* node = it->second;
if( node->s297() == s225 ) {
wstring s76 = node->s299();
if( s76 == s7::s443 )
s645( *node );
else if( s76 == s7::s469 )
s638( *node );
else if( s76 == s7::s936 )
s970( *node );
else {
size_t s689 = s76.find_first_of( s4::s48 );
bool s1203 = false;
if( s689 != string::npos ) {
vector<wstring> s688;
s4::s57( s76, wstring( 1, s76[s689] ), s688 );
if( s688.size() > 2 )
throw s968.s1000( L"malformed object declaration: " + s76 );
if( s688[0] == s7::s1140 ) {
s1203 = true;
s76 = s688[1];}
node->s294( s76 );}
try { lang::s656( s76 ); }
catch( s16* e ) {
throw s968.s1000( e->Msg() );}
s483* dv = NULL;
try {
dv = s300->TR().s518( *node, this, s278 );}
catch( TDException* e ) {
if( e->Category() == s930 ) {
wstring sym = e->s2170( 0 );
wstring s619 = node->s291();
s619 = s619.substr( 0, s619.find( L"(" ) );
s1061 pt = s300->TR().s1010( s619 );
const s483* proto = s300->TR().s1007( pt );
if( proto->s494() == s478 && ((s272*)proto)->s2180( s278 ) )
e->s30( L"recursive import between '" + s619 + L"' and '" + s278 + 
L"'.\n   Recursive import in classes is not allowed." );}
e->s30( L"while constructing object member: " + s76 );
throw e;}
catch( s16* e ) {
e->s30( L"while constructing object member: " + s76 );
throw e;}
dv->s506( node->s299() );
try {
s628.s541( node->s299(), dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s278 + L"::" + node->s299() );}
throw e;}
s630.push_back( dv );
s631.push_back( s371( node->s299(), s300, s475, s1203 ) );}}
else if( node->s297() == s227 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s272* ob = (s272*)s628.get( it->first );
ob->s154( *it->second );}}
else if( node->s297() == s228 ) {
if( node->s299() == s7::s2160 ) {
s1061 s2164 = s300->TR().s1010( node->s291() );
s628.s541( node->s291(), new s1529( s300, s2164 ) );
continue;}
s483* dv = new s359( s300, node->s291(), this, node );
dv->s506( node->s299() );
dv->s1260( true );
wstring s1674 = node->s299();
if( node->s299() == s7::s465 )
s1674 = L"name";
try {
s628.s541( s1674, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s278 + L"::" + node->s299() );}
throw e;}
s630.push_back( dv );
s631.push_back( s371( s1674, s300 ) );}}
it = s702.begin();
for( ; it != s702.end(); ++it ) {
s263* node = it->second;
if( node->s297() == s226 ) {
try {
s488 func = s591::s599( *node, s300, this,
node->s299(), s278 );
s628.s541( func->s299(), func.s15<s483*>() );
s630.push_back( func );
s631.push_back( s371( func->s299(), s300 ) );}
catch( TDException* e ) {
e->s1076( TDException::Stage::s1025 );
e->s30( L"while compiling function '" +s278 + L"::" + node->s299() + L"'" );
s1014.s971( e->Msg( 0 ) );}}}
if( s492 == s478 ) {
s1357* s1364 = new s1357( s300, this, NULL, NULL );
s628.s541( s7::s1356, s1364 );
s630.push_back( s1364 );
s631.push_back( s371( s7::s1356, s300 ) );
if( s628.s156( s7::s428 ) ) {
s842* s2186 = (s842*)s628.get( s7::s428 );
vector<s271*> s1839;
s591::s835 s881;
s2186->s814( s881 );
for( size_t n = 0; n < s881.size(); ++n )
s1839.push_back( s881[n].second );
s842* td = new s842( *s2186, (s591*)this, s1839, s591::s568,
&s701, this, this, false );
s628.s541( s7::s429, td );}
if( s628.s156( s7::s2160 ) ) {
s272* s2162 = (s272*)s628.get( s7::s2160 );
wstring s2168 = s2162->to_wstring();
if( !s628.implements( s2162->s628 ) )
throw new s16( L"the '" + s278 + L"' class doesn't implement '" + s2168 + L"' interface" );
s1061 s2163 = 0;
s300->TR().s1162( s493, s2168, s2163 );}}}
void s272::s500( const s272* s879, bool ){
assert( s492 != s2166 );
if( s492 == s478 || s492 == s479 ) {
if( s627.size() ) {
s626 = (s272*)s300->s222( s627, s879->s834() );
s626->s629->copy( *s629 );}
if( s629 )
s629->s500( s300, s278 );
else
s629 = s625->s629;
s628.s500( this, false );}
else {
if( 1 || s300->s1330()) {
if( ( s300->s1330() || s2197 == s2203 ) && s628.s156( s7::s429 ) ) {
vector<s484*> s274;
s274.push_back( this );
s842* p = (s842*)s628.get( s7::s429 );
if( p->s618() == s7::s868 )
p->s500( s879, false );
else
p->s597( s879 );
if( s494() == s480 )
p->s497( (s483**)&s274[0], 1 );}
s628.s500( this, s300->s1330() );}
s629 = s625->s629;
s1663.s351( s493 );}
ns = (s272*)s879;}
void s272::s1649(){
if( s494() != s479 || s618() == s7::s867 )
return;
if( s628.s156( s7::s428 ) ) {
vector<s485> s274;
s274.push_back( this );
s842* p = (s842*) s628.get( s7::s428 );
p->s500( (s272*)ns, true );
p->s596( s274 );
p->s497( (s483**)&s274[0], 1 );}
s1262();
if( s629 ) 
s629->s1649( s300 );}
void s272::s643( s272* s646 ) const{
if( s626 )
s626->s643( s646 );}
void s272::s645( s263& s701 ){
if( !s629 )
s629 = new s551();
s629->s554( s701.s291() );
return;}
void s272::s639( s1905& s334,	vector<wstring>& s153 ){
s628.s533( s334, s153 );}
void s272::s555( s1905& s76, s1905& s558 ){
if( !s629 )
s629 = new s551();
s629->s555( s76, s300, s558 );}
bool s272::s2180( s1905& s76 ){
if( s629 )
return s629->s2180( s76 );
return false;}
void s272::s638( s263& s701 ){
s626 = (s272*)s300->s222( s627, s278 );}
void s272::s970( s263& s701 ){
wstring s995 = L"wrong syntax of class attributes: " + s701.s291();
s486 dv = s300->TR().s518( s701, this, s278 );
if( dv->s352() != s1719 )
throw new s16( s995 );
vector<s485>& v = dv.s15<s316*>()->s320();
for( auto s_ : v ) {
wstring s = s_.s15<s359*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s995 );
wstring cat = s4::s52( s.substr( 0, pl ), s4::s48 );
vector<wstring> s153;
s4::s57( s.substr( pl + 1 ), L",", s153 );}}
bool s272::s556( s1905& sym_, s371* ref, s1905& s334,
bool fr ) const{
/* ???DEBUG??? 220119	size_t pl = sym_.find( L"::" );
wstring sym;
if( pl != string::npos ) {
wstring smod = sym_.substr( 0, pl );
if( smod == s278 )
sym = sym_.substr( pl + 2 );
else
sym = sym_;}
else
sym = sym_;*/
bool s685 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s686 = sym_.substr( 0, pl );
s272* ob = ((s272*)s641( s686, s334, false ));
if( !ob && s686 == s7::s1601 )
ob = (s272*)this;
if( ob ) {
s371 s1658( *ref );
s685 = ob->s556( sym, &s1658, s334, fr );
if( s685 ) {
if( !ref->s380() )
ref->s382( ( s483* )this );
ref->s379( s640( s686 ), ob );
ob->s556( sym, ref, s334, fr );}}
else {
if( s629 )
s685 = s629->s556( sym_, ref );}}
else {
const s272* ob = ((s272*)s641( sym, s334, false ));
if( ob ) {
if( !ref->s380() )
ref->s382( ( s483* )this );
size_t off = s640( sym );
ref->s379( off, ob );
if( s631[off].s1203() )
ref->s1260();
s685 = true;}
else {
if( sym == s7::s1601 ) {
ob = this;
if( !ref->s380() )
ref->s382( ( s483* )this );
ref->s379( s1147, ob );
s685 = true;}
else if( s629 )
s685 = s629->s556( sym, ref );}}
return s685;}
size_t s272::s640( s1905& s647 ) const{
if( s647 == s7::s1601 )
return s1147;
/*???DEBUG??? 220119	size_t pl = s647.find( L"::" );
if( pl != string::npos ) {
wstring smod = s647.substr( 0, pl );
wstring sym1 = s647.substr( pl + 2 );
s272* mod = (s272*)s628.get( smod, false );
if( !mod )
return NULL;
return mod->s640( sym1 );}
*/
for( size_t n = 0; n < s630.size(); ++n ) {
if( s631[n].s617() == s647 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s647 );}
s271* s272::s598( size_t off ){
if( off == s1147 )
return this;
return s630[off];}
void s272::s851( s1905& s76, s483* s349, s482::s145 ap ){
s628.s541( s76, s349, ap );
s630.push_back( s349 );
s631.push_back( s371( s76, s300 ) );}
void s272::s1657( s1905& s76, s483* s349 ){
if( !s628.s156( s76 ) )
throw new s16( L"no such member: " + s76 );
s628.s541( s76, s349, s482::s147 );
for( size_t n = 0; n < s631.size(); ++n ) {
if( s631[n].s617() == s76 ) {
s630[n] = s349;
break;}}}
void s272::s1640( const s1602* ob ){
s630.clear();
s625->s628.s1613( s628 );
for( size_t n = 0; n < s631.size(); ++n )
s630.push_back( s628.get( s631[n].s617() ) );
s482::s535 sm;
ob->s1632( sm );
s482::s535::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s628.s541( it->first, it->second.s15<s483*>(), s482::s147 );
else {
if( !s628.s156( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
s483* mem = s628.get( it->first );
mem = mem->s1536( it->second.s15<s483*>() ); // ???DEBUG??? 220213
s628.s541( it->first, mem, s482::s147 );}}
for( size_t n = 0; n < s631.size(); ++n ) {
s630[n] = s628.get( s631[n].s617() );}
/*	auto s824 = s628.Table();
auto it1 = s824.begin();
for( ; it1 != s824.end(); ++it1 )
it1->second->s2133( this );*/
}
s483* s272::s1536( const s483* p ) const{
if( p->s1541( s352() ) ) {
p->s356( (s271*)this );
return (s483*)this;}
vector<s485> s274;
s274.push_back( (s271*)p );
s272* s685 = new s272( *(s272*)this, s274, s603(), (s272*)this );
s685->s500( this, false );
return s685;}
s483* s272::s641( s1905& sym, s1905& s334,	bool s520/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s272* mod = (s272*) s628.get( smod, s520 );
if( !mod )
return NULL;
return mod->s641( sym1, s334, s520 );
/* ???DEBUG??? 220119		s483* s153 = mod->s641( sym1, s334, s520 );
if( s153 ) {
if( sym1.find( L"." ) != string::npos )
return s153;
else
return mod;}
return NULL;*/
}
wstring sym1 = sym;
if( sym.size() > 2 && ( sym.find( L"()" ) == sym.size() - 2 ) )
sym1 = sym.substr( 0, sym.size() - 2 );
s486 s685 = s628.get( sym1, false );
if( !s685 && s520 )
throw new s16( L"4: Symbol does not exist: " + sym, 
(uint32_t)s16::s17::s23 );
if( s685 && !s642( sym1, s334 ) && (s334 != L":::") ) {
if( s520 )
throw new s16( L"4: Symbol not found: " + sym,
(uint32_t)s16::s17::s23 );
s685 = NULL;}
return s685;}
bool s272::s642( const wstring& sym, s1905& s499 ) const{
if( s499 == s347 )
return true;
return s628.s550( sym, s499 );}
s1061 s272::s386( s1905& s343 ) const{
s483* s690 = s628.get( s343 );
s1061 s685 = s690->s352();
if( s685 == 0 ) {
s690->s500( (s272*)this );
s685 = s690->s352();}
return s685;}
s483* s272::s635( const s263& s701, s483* s588, s1905& s334 ) const{
vector<wstring> s691;
vector<s485> s274;
vector<s271*> s705;
s271::s1333( s701, s300, (s272*)s588, s334, s705 );
for( auto pr : s705 )s274.push_back( pr );
s272* s685 = new s272( *this, s274, &s701, (s272*)s588 );
return s685;
size_t pos = s701.s291().find( L"(" );
size_t pos_ = pos;
s263::s288( s701.s291(), pos, s691 );
if( 0 && s691.size() ) {
s591* s692 = (s591*) s628.get( s7::s428, false );
if( !s692 )
throw new TDException( 0, s932, &s701, 
L"Arguments passed to a class without init function." );
else {
wstring str = s701.s291();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s7::s428 );
s263* ast_ = new s263( s7::s429, s141( str ), (s263*)&s701 );
s490 cs = (s561*)s271::s504( *ast_, s300, s685, s334, 0 );
s591* td = s591::s600(
cs, s300, s685, (s591*)s685, s278, false );
s685->s628.s541( s7::s429, td );}}
s685->s500( (s272*)s588, true );
return s685;}
s483* s272::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
vector<wstring> s691;
vector<s485> s274;
if( s300->s1330() )// ???DEBUG??? 220423
for( auto p : l ) s274.push_back( p ); 
s272* s685 = new s272( *this, s274, s603(), s588 );
if( 0 && l.size() ) {
s591* s692 = (s591*)s628.get( s7::s428, false );
if( !s692 )
throw new TDException( 0, s932, ast_,
L"Arguments passed to a class without init function." );
else {
s490 cs = new s561( s300, s7::s428, l, ast_ );
cs->s602().insert( cs->s602().begin(), s685 );
s591* td = s591::s600(
cs, s300, s685, (s591*)s588, s278, false );
s685->s628.s541( s7::s429, td );}}
s685->s500( (s272*)s588, true );
return s685;}
std::wstring s272::s298() const{
if( s494() == s479 )
return s278;
else if( s494() == s478 || s494() == s480 )
return s347;
assert( 0 );
return /*s277 + L"::" +*/ s278;
}
s483* s272::s344( s1905& s676, s1905& s334,
bool s520 /*= true*/, bool s2167 /*= true*/ ) const
{
s371 ref( s676, s300 );
if( !s556( s676, &ref, s334, true ) )
return NULL;
if( !s2167 && ref.s381().s15<s272*>() != this )
return NULL;
s483* s685 = ref.s378();
if( s685->s494() != s476 )
return NULL;
return s685;}
s591* s272::s1685( s1905& s676, s591* s215, s272* s1672,
s561* cs ) const{
if( s676 == L"getf" ) {
return new s1680( s300, (s272*)this, s215, &s272::s1704, cs, 
NULL );}
return s483::s1685( s676, s215, s1672, cs );}
s483* s272::s1704( s483** s274, size_t s498 ){
s359* pv = (s359*) s274[1];
return s628.get( pv->to_wstring() );}
s271* s272::s335( s591* s2057, s272* impl ) const{
vector<s485> v;
return new s272( *this, v, NULL, ns );}
void s272::s356( s271* p ) const{
s272* pob = (s272*)p;
s628.s1613( pob->s628 );
for( size_t n = 0; n < pob->s631.size(); ++n ) {
pob->s630[n] = pob->s628.get( pob->s631[n].s617() );}
return;
throw new s16( L"" );
vector<wstring> fields;
s628.s545( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s483*)s628.get( fields[n] ))->s356( p );}
size_t s272::s322() const{
return s628.s322();}
bool s272::operator==( const s483* p ) const{
return s628.compare( ( (s272*)p )->s628.Table() );}
bool s272::operator<( const s483* p ) const{
return false;}
void s272::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
if( s628.s156( s7::s1629 ) ) {
s591* s1655 = (s591*)s628.get( s7::s1629 );
s9<s507> s1653 = new s507( (s262*)s300, (s272*)this, s603() );
vector<s485> s705 = { /*(s271*)this,*/ s1653 };
s1655->s596( s705 );
if( s1655->s618() != s7::s867 )
s1655->s500( this, false );
else
s1655->s597( this );
s1655->s497( 0, 0 );
ss << s1653->to_wstring();
return;}
std::wstringstream buf;
wstring s347;
if( s492 == s478 ) s347 = L"Class";
else if( s492 == s479 ) s347 = L"Module";
else if( s492 == s480 ) s347 = L"Object";
else s347 = L"ERROR";
buf << s347 << L" : " << s278 << L"/" /*<< s372*/ << endl;
s628.s304( &buf, s419 );
buf << endl;
ss << buf.str();}
wstring s272::to_wstring( uint32_t s1565 ) const{
if( s628.s156( s7::s1629 ) ) {
s591* s1655 = (s591*)s628.get( s7::s1629 );
s9<s507> s1653 = new s507( (s262*)s300, (s272*)this, s603() );
vector<s485> s705 = { /*(s271*)this,*/ s1653 };
s1655->s596( s705 );
if( s1655->s618() != s7::s867 )
s1655->s500( this, false );
else
s1655->s597( this );
s1655->s497( 0, 0 );
return s1653->to_wstring();}
std::wstringstream buf;
wstring s347;
if( s492 == s478 ) s347 = L"Class";
else if( s492 == s479 ) s347 = L"Module";
else if( s492 == s480 ) s347 = L"Object";
else s347 = L"ERROR";
buf << s347 << L" : " << s278 << L"/" /*<< s372*/ << endl;
s628.s304( &buf, s419 );
buf << endl;
return buf.str();}
void s272::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s347;
if( s492 == s478 ) s347 = L"Class";
else if( s492 == s479 ) s347 = L"Module";
else if( s492 == s480 ) s347 = L"Object";
else s347 = L"ERROR";
buf << s4::fill_n_ch( L' ', s197 ) << s347 << L" : " << s278 << L"/" << 
L": " << s4::s2187( (void*)this ).c_str() << endl;
s628.s304( pd, s197 + s419 );}
s577 s2115;
s591* s591::s599( const s263& s701, s262* s300, s272* obj,
const wstring& s278, const wstring& s558 ){
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
std::vector<s271*> s274;
for( size_t n = 0; n < s697; ++n ) {
s263::s275::const_iterator it = s702.find( std::to_wstring( n ) );
if( it->second->s291() == s7::s940 )
s274.push_back( s873 );
else if( it->second->s291() == s7::s1140 )
s274.push_back( s1686 );
else if( it->second->s291() == s7::s2139 )
s274.push_back( s2146 );
else
s274.push_back( s271::s504( *it->second, s300, obj, s558, true ) );}
Transd* s685 = NULL;
size_t s689 = s278.find_first_of( s4::s48 );
if( s689 != string::npos ) {
vector<wstring> s688;
s4::s57( s278, wstring( 1, s278[s689] ), s688 );
if( s688.size() > 2 )
throw new s16( L"malformed function name: " + s278 );
if( s688[0] == s7::s431 ) {
s685 = new s604( s300, obj, NULL, s568, s274, &s701 );
s685->s278 = s688[1];}
else if( s688[0] == s7::s432 ) {
s685 = new s842( s300, obj, NULL, obj, s568, s274, &s701 );
s272* pAnc = (s272*)s300->s222( obj->s637(), s558 );
((s604*)pAnc->s344( s688[1], s558 ))->s648( obj->s352(),
s685 );
s685->s278 = s688[1];
s685->s594( s574 );}
else
throw new s16( L"malformed function name: " + s278 );}
else {
s685 = new s842( s300, obj, NULL, obj, s568, s274, &s701, true );
s685->s278 = s278;}
return s685;}
s561* s591::s1119( const s263& s701, s262* s300, s272* obj,
s1905& s558, bool s2177 ){
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
wstring s601 = s701.s291();
std::vector<s271*> s274;
s561* s685 = NULL;
try {
for( size_t n = 0; n < s697; ++n ) {
s263::s275::const_iterator it = s702.find( std::to_wstring( n ) );
it->second.s15<s263*>()->s269( s2101, s141(L"CallSite") );
it->second.s15<s263*>()->s269( s2100, s141(s601) );
if( it->second->s291() == s7::s940 )
s274.push_back( s873 );
else if( it->second->s291() == s7::s1140 )
s274.push_back( s1686 );
else if( it->second->s291() == s7::s2139 )
s274.push_back( s2146 );
else
s274.push_back( s271::s504( *it->second, s300, obj, s558, false ) );}
s685 = new s561( s300, s601, s274, &s701, s2177 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s601 + L"' function call" );}
return s685;}
void s561::s500( const s272* s879, bool ){
return;
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s500( s879 );}}
s271* s561::s335( s591* s2057, s272* impl ) const{
return new s561( *this );}
s591* s591::s600( s561* cs, s262* s300, s272* s588, s591* s215, 
s1905& s558, bool proc ){
wstring s601 = cs->s299();
wstring s704 = s588 ? s588->s2171() : L"::";
s485 s703 = NULL;
std::vector<s271*>& s274 = cs->s602();
s488 s706 = NULL;
s591* s685 = NULL;
size_t pl = s601.find( L"<" );
try {
if( pl == string::npos ) {
auto s1451 = s1371.find( s601 );
if( s1451 != end( s1371 ) && BIFuncs1v[s1451->second] )
return s300->s214( s1451->second, cs, s588, s215 );
s271* par = NULL;
int s1363 = 0;
s1359:
if( s274.size() ) {
par = s274[s1363];
s472 pc = par->s494();
if( pc == s475 ) {
try {
par->s500( s215, proc ); 
/*if( !proc ) {// ??DEBUG??? 220214
if( s215->s834() == s588->s298() )
par->s500( s215, false );
else
par->s500( s588, false );}
else {
if( s215->s834() == s588->s298() )
par->s500( s215, true ); 
else
par->s500( s588, true ); 
}*/
}
catch( TDException* e ) {
if( e->Category() != s930 || (
( (s371*)par )->s617()[0] != L':' && ( (s371*)par )->s617().back() != L':' ) )
throw e->s30( L"while compiling function '" + s601 + L"'" );
s1363++;
goto s1359;}
if( ( (s371*)par )->s381().s14() ) {
if( ( (s371*)par )->s617() == s7::s430 )
par = s588;
s703 = ( (s371*)par )->s377();}}
else {
if( pc == s477 ) {
s490 cs = new s561( *(s561*)par );
par = s600( cs, s300, s588, s215, s558, false ); // ???DEBUG??? 220214
( (s591*)par )->s500( s588, false );}
else {
par->s500( s215 );}}
if( par->s494() == s475 /*||  par->s494() == s1337*/ ) {
(void)0;}
else if( par->s494() == s1063 || par->s494() == s481 )
s703 = NULL;
else {
s703 = par->s496();}
s274[s1363] = par;}
else {
s706 = (s591*)s588->s344( s601, s704, false );
if( !s706 )
throw new s16( L"Procedure is not resolved: " + s601 );}
if( s1451 != end( s1371 ) )
return s300->s214( s1451->second, cs, s588, s215 );}
else {
wstring s2138 = s601.substr( pl + 1, s601.size() - pl - 2 );
wstring s619 = s300->TR().s1275( s2138, s558 );
s601 = s601.substr( 0, pl );
if( s619 != s2138 ) {
s2138 = s300->TR().s1352( s300->TR().s1275( s2138, s558 ) );
((s263*)cs->s603())->s1768( s601 + L"<" + s2138 + L">" );}
try {
s1061 pt = s300->TR().s1010( s619, false );
if( !pt ) {
s947 ast2 = new s263( s619 + L"()", cs->s603()->Nqj(), (s263*)s215->s603() );
s703 = s300->TR().s518( *ast2, s588, s558 );}
else {
s703 = s300->TR().s1007( pt )->s355( s215, s274, s215->s603() );
s703->s2198( s2202 );}}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s601 + L"' function " );
s947 ast2 = new s263( s619 + L"()", cs->s603()->Nqj(), (s263*)s215->s603() );
s703 = s300->TR().s518( *ast2, s588, s558 );}
s274.insert( s274.begin(), s703 );}
s488 s707 = NULL;
s1142 s1237;
if( !s706 ) {
s472 s710 = s703->s494();
if( s710 == s475 ) {
s371* ref = (s371*)s703.s15<s484*>();
s703 = (s483*)ref->s503();
s710 = s703->s494();}
try {
assert( s710 != s479 && s710 != s2166 );
if( s710 == s480 || s710 == s478 ) {
s707 = (s591*)s703.s15<s272*>()->s344( s601, s704, false, false );}
else if( s710 == s474 )
s1237 = s703.s15<s336*>()->s1197( s601 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s707 && !s1237.s339 )
s706 = (s591*)s588->s344( s601, s704, false );
if( !( s1237.s339 || s706 || s707 ) ) {
s591* ptd = s703.s15<s272*>()->s1685( s601, s215, s588, cs );
if( ptd )
return ptd;
throw new s16( L"Method is not resolved: " + s601 );}}
if( s1237.s339 ) {
s685 = new s841( s300, s215, s588, s566, s274, s1237.s338, s601, cs->s603(), proc );}
else if( s706 ) {
if( s601 == s7::s1356 ) {
assert( 0 );
vector<s271*> s1664( s274.begin() + 1, s274.end() );
s685 = new s1357( *s706.s15<s1357*>(), s588, s215, s1664,
cs->s603() );}
else {
s685 = new s842( *s706.s15<s842*>(), s215, s274,
s567, cs->s603(), s706->s588, s215->s588, true, proc );}}
else if( s707 ) {
if( s601 == s7::s1356 ) {
s685 = new s1357( *s707.s15<s1357*>(), s703.s15<s272*>(), s215, s274,
cs->s603() );}
else {
s685 = new s842( *s707.s15<s842*>(), s215, s274, s568,
cs->s603(), s703.s15<s272*>(), s215, true, proc );}
if( s707->s595() == s573 )
s685->s575 = s569;
else
s685->s575 = s568;}}
catch( s16* e ) {
throw e->s30( L"while compiling function '" + cs->s603()->Src() + L"'" );}
s685->s278 = s601;
return s685;}
void s591::s1242( vector<s271*>& s274, const vector<wstring>& s1208 ){
for( s271* p : s274 ) {
if( p->s494() == s475 || p->s494() == s1063 )
( (s371*)p )->s982( s1208 );}}
void s591::s1242( vector<s485>& s274, const vector<wstring>& s1208 ){
for( s271* p : s274 ) {
if( p->s494() == s475 )
( (s371*)p )->s982( s1208 );}}
s591::s591( s262* s300, s272* s592, s591* s593, s272* ns_, s563 ct,
s1905& s676, const s263* s701, bool s1727, bool _bd )
: s272( s676, s300, s476, s701, ns_ ), s575( ct ),
s586( NULL ), s588( s592 ), s587( s593 ), past( s701 ), s1654( new s1600( s300 ) ),
intro( s1727 ), s2176( _bd ), s2239( -1 ){}
s591::s591( s262* s300, s272* s592, s591* s593, s272* ns_,
s563 ct, const std::vector<s271*>& l,	const s263* s701, bool s1727=false,
bool _bd=true)
: s272( s300, 0, s476, s701, ns_ ), s575( ct ), s576( s572 ),
s586( NULL ),	s588( s592 ), s587( s593 ), past( s701 ), s1654( new s1600( s300 ) ),
intro(s1727), s2176(_bd), s2239( -1 ){
TDException s968( s7::s1687, s932, s701, L"malformed lambda definition" );
size_t n = 0;
bool s2152 = false;
bool s2147 = false;
bool s1168;
for( ; n < l.size(); n += 2 ) {
s1168 = false;
if( ((s483*)l[n]) == s873 ) {
if( l.size() == n || s2147 )
throw s968.s1000( L"the return type is missing" );
s493 = l[n + 1]->s352();
s2152 = true;
continue;}
if( ((s483*)l[n]) == s2146 ) {
s2147 = true;
n -= 1;
continue;}
else if( ((s483*)l[n]) == s1686 ) {
if( l.size() == n )
throw s968.s1000( L"the 'const' keyword should precede the parameter name");
s1168 = true;
++n;}
if( l[n]->s494() != s475 ) {
if( s1168 )
throw s968.s1000( L"the 'const' keyword should precede the parameter name");
break;}
s371* s76 = (s371*) l[n];
if( l.size() == n + 1 ) {
break;}
s483* ex = (s483*) l[n + 1];
s472 s1899 = ex->s494();
if( //s1899 != s474 && s1899 != s480 &&	s1899 != s479 && 
s1899 == s476 && !s2147 )
throw new s16( L"incorrect syntax for lambda parameter " + s76->s617() +
L"; should be a type constructor.", (uint32_t)s16::s17::s20 );
if( s1168 )
s76->s1260();
s628.s541( s76->s617(), ex );
if( !s2147 )
s582.push_back( (s483*)ex );
s274.push_back( (s483*)ex );
s630.push_back( (s483*)ex );
s631.push_back( *s76 );}
s584.insert( s584.end(), l.begin() + n, l.end() );
if( s603() )
((s263*)s603())->s269( s2102, s141( (double)s493, s140 ) );}
s591::s591( const s591& right, s272* s592, s591* s593,
s272* ns_, const std::vector<s271*>& s705, const s263* s701, bool s2120,
bool _bd)
: s272( right, s2115, s701, ns_ ), 
s576( right.s576 ),	s586( NULL ), s588( s592 ), s587( s593 ), 
past( s701 ), s1654( new s1600( s300 ) ), intro( s2120 ), s2176( _bd ), s2239( right.s2239 ){
s575 = right.s575;
s582 = right.s582;
s278 = right.s278;
if( s705.size() ) {
s274.assign( s705.begin(), s705.end() );}
else {
s274.clear();
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s335( this, s592 ) );}}
if( s575 == s567 ) { 
for( size_t n = 0; n < s274.size(); ++n ) {
s485 tmp = s630[n];
s628.s541( right.s631[n].s617(), tmp.s15<s484*>(), s482::s147 );
s630[n] = s274[n];}}
for( size_t n = 0; n < right.s584.size(); ++n )
s584.push_back( right.s584[n]->s335( this, NULL ) );
nlocs = right.nlocs;
s498 = right.s498;
s581 = nlocs ? (s484**)&s274[0] : NULL;
s583 = right.s583;
s580 = s498 ? (s483**)&s583[0] : NULL;
s981 = right.s981;}
s841::s841( s262* s300, s591* s593, s272* ns_, s563 ct, const vector<s271*>& l,
s1061 s709, s1905& s1553, const s263* s701, bool _bd )
: s591( s300, s593, s593, ns_, ct, L"", s701, false, _bd ), s1976( false )/*,
s562( s708 )*/
{
s278 = s1553;
s576 = s572;
s493 = s709;
s274.assign( l.begin(), l.end() );}
s841::s841( const s841& right, s591* s593, s272* ns_ )
: s591( right, NULL, s593, ns_, vector<s484*>(), s603(),
false, right.s2176 ), 
s562( right.s562 ), s1976( right.s1976 ){
s278 = right.s278;
s576 = s572;
s493 = right.s493;
s586 = (s483*)right.s586->s335(0,0);
s583.resize( right.s583.size() );
s583[0] = s586;}
s841::~s841(){}
s842::s842( s262* s300, s272* s588, s591* s587, s272* ns_, s563 ct,
const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s588, s587, ns_, ct, l, s701, false, s2177 ){
if( ct == s568 ) {
subject = s588;		}}
s842::s842( const s842& right, s591* s593,
const std::vector<s271*>& s705, s563 ct,  const s263* s701, 
s272* s592, s272* ns_, bool s2120, bool s2177 )
: s591( right, s592, 
s593, ns_, vector<s484*>(), s701, s2120, s2177 ){
TDException s968( s7::s1670, s932, s701 );
s575 = ct;
int shift = 0;
if( ct == s568 ) {
if( s705.size() ) {
subject = s705[0];
shift = 1;}
else
subject = s588.s15<s484*>();}
for( size_t n = 0; n < s582.size(); ++n ) {
if( s705.size() > n + shift ) {
s472 pc = s705[n]->s494();
if( ( pc == s475 || pc == s1337 ) && s705[n]->s1203() && !s631[n].s1203() )
throw s968.s1000( L"constant argument is passed to non-constant function: " + s631[n].s617() );
s274[n] = s705[n + shift];}}
if( s274.size() ) {
for( size_t n = 0; n < s274.size() - shift; ++n ) {
s630[n] = s274[n + shift];
s630[n]->s2133( s587, s592, s2176 );}}
if( s705.size() - shift > s274.size() ) 
throw s968.s1000( L"too many arguments: expected " + std::to_wstring( s274.size() ) + L", received " +
std::to_wstring( s705.size() ));}
s591::~s591(){
s274.clear();
s582.clear();
s981.clear();
s583.clear();}
s842::~s842(){}
s561::s561( s262* pass_, s1905& s189, const vector<s271*>& l, 
const s263* ast_, bool s2177 )
: s271( pass_, s477 ), s601( s189 ), past( (s263*)ast_ ), s2176( s2177 ){
s274.assign( l.begin(), l.end() );}
s561::s561( const s561& right )
: s271( right.s300, s477 ), s601( right.s601 ), past( right.past ),
s2176( right.s2176 ){
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s335(0,0) );}}
wstring s591::s834() const{
if( s588.s14() )
return s588->s298();
else if( s575 == s566 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
std::wstring s591::s298() const{
return ns->s834(); //s588->s298();
}
void s591::s847( s271* par, size_t pos, s485& s153, const s272* s1672, bool proc ){
if( par->s494() == s477 ) {
s490 cs = new s561( *((s561*)par) );
s153 = s600( cs, s300, (s272*)s1672, this, s1672->s2171(), cs->s2183() );
s153.s15<Transd*>()->s500( s1672, cs->s2183() );}
else if( par->s494() == s474 ) {
par->s500( /*s588*/ this, false );
s153 = par;}
else if( par->s494() == s476 ) {
s153 = par; // par->s496();
s153->s2133( NULL, this, s153.s15<Transd*>()->s2183()  );	  }
else if( par->s494() == s1245 ) {
par->s500( this, false );
s153 = par;}
else
s153 = par;}
void s591::s589(const wstring& s334){
return; // ???DEBUG??? 220213
for( size_t n = 0; n < s582.size(); ++n )
s582[n]->s500( s587/*s588*/ );
}
void s591::s500( const s272* s2178, bool proc/*=false*/ )
{
s1663.s351( s493 );
s671 = proc ? s2171() : s2178->s2171(); // ???DEBUG??? 220420
if( s588 && (s588->s494() == s479 || s588->s494() == s478 )) {
if( 0 && s588->s494() == s478 ) 
return;}
if( s575 == s566 && s618() == s7::s867 )
return;
s583.clear();
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( s575 == s566 && n == 1 ) {
s591::s1242( s274, ((s336*)s274[0]->s496())->s1191( s278 ) );}
if( par->s494() == s475 ) {
if( 1 || par.s15<s371*>()->s381().s13() || s575 == s568 ) { 
if( ! par.s15<s371*>()->s381().s13() )				
par.s15<s371*>()->reset();
s487 s1675 = s588;
if( s2178 != this )
s588 = (s272*)s2178;
par.s15<s371*>()->s500( this, false );
s588 = s1675;}
s583.push_back( NULL );}
else if( par->s494() == s1063 || par->s494() == s481 )
s583.push_back( /*NULL*/ par.s15<s483*>() );
else {
try {
s847( par, n, s274[n], s2178, proc );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s278 + L"' function " );}
s583.push_back( s274[n]->s496() );}}
if( s575 == s565 || s575 == s567 ) {
if( s278 == s233 ) {
for( size_t n = 0; n < s274.size(); ++n ) {
s483* par = s274[n]->s494() == s476 ? s274[n]->s496() : s274[n].s15<s483*>();
s628.s541( s631[n].s617(), par, s482::s147 );
s274[n]->s1679( s7::s867 );
s630[n] = par;
if( s274[n]->s494() == s476 ) {
s371* ref = new s371( s631[n].s617(), s300, s475 );
size_t off = s640( s631[n].s617() );
s271* s1060 = s630[off].s15<s271*>()->s496();
if( !s1060 )
s1060 = (s271*)s300->TR().s1007( s630[off]->s352() );
ref->s379( off, s1060->s503() );
s274[n].s15<s591*>()->s2189( ref );}}}
for( size_t n = 0; n < s584.size(); ++n ) {
if( s584[n]->s494() == s477 ) {
s490 cs = new s561( *s584[n].s15<s561*>() );
s584[n] = s600( cs, s300, s588, this, s588->s2171(), cs->s2183() );}
else if( s584[n]->s494() == s475 )
s584[n].s15<s371*>()->s500( s587, false );
else if( s584[n]->s494() != s476 )
s584[n]->s500( s587 );
else if( s492 != s1245 ) // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s584 ) {
if( it->s494() == s476 )
it.s15<Transd*>()->s500( /*s588*/s2178, false );
else if( it->s494() == s1245 )
it.s15<Transd*>()->s500( s587, false );}
if( !s493 && s584.size() ) {
s493 = s584.back()->s352();}}
if( s493 ) {
if( s588.s14() ) {
if( 0 && s492 == s1245 )
s586 = s300->TR().s518( ((s838*)this)->s1328(), 
s588, s588->s298() );
else
s586 = s300->TR().s518( s352(), s588, s588->s298() );}
else {
if( 0 && s492 == s1245 )
s586 = s300->TR().s518( ((s838*)this)->s1328(), 
(s272*)s2178, s2178->s298() );
else
s586 = s300->TR().s518( s352(), (s272*)s2178, s2178->s2171() );}
s586->s500( s587, proc );
s586->s1679( s7::s867 );
s583.insert( s583.begin(), s586 );
if( s274.size() ) {
s581 = (s484**)&s274[0];
nlocs = s274.size();
s580 = &s583[0];
s498 = s583.size();}
else {
s581 = NULL;
s580 = NULL;
nlocs = s498 = 0;}}
s981.resize( s583.size() );}
void s841::s500( const s272* s1672, bool proc/*=false*/ )
{
TDException s968( s7::s1126, s1132, past );
s591::s500( s1672, proc );
s271* par = s274[0]->s496();
s336* s703 = NULL;
s1142 s1237;
s472 s710 = par->s494();
s1122 ap;
if( s710 == s475 ) {
s371* ref = (s371*)par;
s486 pobj = ref->s377();
s710 = pobj->s494();
s703 = pobj.s15<s336*>();
ap = s1122( s274, s703 );
try {
s1237 = s703->s1192( s278, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s336::s337::s1133::s1180 ) {
s1237 = s703->s1187( s278, ap /*s1239, s274*/ );
}}}
else {
s703 = ( (s336*)par );
ap = s1122( s274, s703 );
try {
s1237 = ( (s336*)s703->s496() )->s1192( s278, ap/*s1239*/ );
}
catch( s16* e ) {
if( e->which() == (uint32_t)s336::s337::s1133::s1180 ) {
s1237 = ( (s336*)s703->s496() )->s1187( s278, ap/*s1239, s274*/ );
}}}
if( !s1237.s339 )
throw s968.s1000( L"method is not resolved: " + par->s353() + L"::" + s278 + 
ap.s1329( s300 ) );
try {
s300->s2013( s1237.s2035, s2045 );}
catch( s16* e ) {
throw s968.s1000( e->Msg() );}
s493 = s1237.s338;
s562 = s1237.s339;
s1976 = s1237.s1168;
bool s1762;
if( s274[0]->s494() != s476 /*==s475*/ )
s1762 = s274[0]->s1203();
else //if( s274[0]->s494() == s476 )
s1762 = s274[0]->s496()->s1203();
if( !s1976 && s1762 )
throw s968.s1000( L"non-constant function is applied to a constant variable" );
if( s278 == s7::s1356 )
s586 = s274[0].s15<s483*>();
if( s586.s13() ) {
s586 = s300->TR().s518( s352(), s588, s588->s298() );
s586->s500( s587 );
s583.insert( s583.begin(), s586 );
if( s274.size() ) {
s581 = (s484**)&s274[0];
nlocs = s274.size();
s580 = &s583[0];
s498 = s583.size();}
else {
s581 = NULL;
s580 = NULL;
nlocs = s498 = 0;}}
s981.resize( s583.size() );
s1262();
s586->s1262();
s586->s1260( s1762 );}
void s842::s500( const s272* s1672, bool proc/*=false*/ )
{
TDException s968( s7::s1522, s1556, s603() );
s671 = proc ? s588->s298() : s1672->s298();
if( ns->s494() == s479 || ns->s494() == s478 ) {
s589( s671 );
if( s588->s494() == s478 )
return;}
if( s274.size() > s630.size() )
throw s968.s1000( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
if( n == 0 && s274[n]->s618() == s7::s867 )  
continue;
s485 par = s274[n];
if( par->s494() == s475 ) {
s371* s1651 = par.s15<s371*>();
if( s1651->s381().s13() ) {
s1651->s500( /*this*/s587.s14() ? s587.s15<s591*>() : this, true );
}}
else
s847( par, n, s274[n], s1672, proc );
if( s582.size() > n ) {
if( s582[n]->s352() == Types.No ) {
if( !s582[n]->s501( s274[n].s15<s483*>() ) )
throw s968.s1000( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
else if( !s300->TR().s1534( s274[n]->s352(), s582[n]->s352() ) ) {
throw s968.s1000( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}}}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s618() < 0 )
throw s968.s1000( L"uninitialized function parameter: " + s631[n].s617() );
if( s274[n]->s496()->s1203() && !s631[n].s1203() )
throw s968.s1000( L"constant argument is passed to non-constant function: " + s631[n].s617() );
s630[n] = s274[n];}
s488 s1362 = s587;
s587 = 0;
for( size_t n = 0; n < s584.size(); ++n ) {
if( s584[n]->s494() == s477 ) {
s490 cs = new s561( *s584[n].s15<s561*>() );
s584[n] = s600( cs, s300, s588, this, s588->s298(), cs->s2183() );}
else if( s584[n]->s494() == s475 )
s584[n].s15<s371*>()->s500( /*s587*/ s588, true );
else if( s584[n]->s494() != s476 &&
s584[n]->s494() != s1245 )
s584[n]->s500( /*s587*/ s588 );
else // lambda - ?
;// throw new s16( L"unhandled expression" );
}
for( auto it : s584 ) {
if( it->s494() == s476 )
it.s15<Transd*>()->s500( /*this*/s588, it.s15<Transd*>()->s2183() );//???DEBUG??? 220407
}
s587 = s1362;
if( !s493 ) {
if( s584.size() ) {
s493 = s584.back()->s352();
s586 = s300->TR().s518( s352(), s588, s588->s298() );}
else {
s493 = s1152;
s586 = s365.s15<s483*>();}
s586->s1679( s7::s867 );
s583.insert( s583.begin(), s586 );}
else
s586 = (s483*)s300->TR().s1007( s352() )->s335( s587, s588 );
if( s274.size() ) {
s581 = (s484**)&s274[0];
nlocs = s274.size();
s580 = NULL;// &s583[0];
s498 = s583.size();}
else {
s581 = NULL;
nlocs = s498 = 0;
s580 = NULL;}
s981.resize( s583.size() );
s1262();}
void s591::s1911( const s577& pl ) const{
TDException s968( s7::s1904, s1556, s603() );
size_t shift = 0;
if( s575 == s568 || s575 == s566 )
shift = 1;
if( pl.size() > s630.size() + shift )
throw s968.s1000( L"too many arguments to lambda call" );
for( size_t n = shift; n < pl.size(); ++n ) {
s485 par = pl[n];
if( s582[n]->s352() == Types.No ) {
if( !s582[n]->s501( par.s15<s483*>() ) )
throw s968.s1000( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
else if( !s300->TR().s1534( par.s15<s271*>(), s582[n].s15<s271*>() ) ) {
throw s968.s1000( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
if( par->s618() < 0 && par->s618() != s7::s1747 )
throw s968.s1000( L"uninitialized function parameter: " + s631[n].s617() );
if( par->s496()->s1203() && !s631[n].s1203() )
throw s968.s1000( L"constant argument is passed to non-constant function: " + s631[n].s617() );}}
void s591::s2189( s371* ref ){
subject = ref;}
void s591::s596( const vector<s485>& l ){
s1911( l );
s274.clear();
s274.assign( l.begin(), l.end() );}
void s591::s597( const s272* s1672 ){
TDException s968( s7::s1599, s1556, s603() );
if( s575 != s566 && s575 != s565 && s274.size() > s630.size() )
throw s968.s1000( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s271* par = s274[n];
if( par->s494() == s477 ) {
s490 cs = new s561( *(s561*)par );
par = s600( cs, s300, (s272*)s1672, /*this*/s587, s588->s298(), false ); // ???DEBUG??? 220521
((s591*)par)->s500( s1672, false );
s274[n] = par;}
if( s274[n]->s494() == s481 ) {
s583.push_back( s274[n]->s496() );}
else if( s274[n]->s494() != s475 ) {
if( ( s575 != s566 && s575 != s565 ) || s278 == s233 ) {
s630[n] = s274[n]->s496();
s630[n]->s1679( s7::s867 );
s628.s541( s631[n].s617(), s630[n].s15<s483*>(), s482::s147 );}}
else {
if( s575 != s566 && s575 != s565 ) {
s630[n] = s274[n].s15<s483*>();
s628.s541( s631[n].s617(), s274[n].s15<s371*>()->s377(), s482::s147 );}
if( s274[n].s15<s371*>()->s381().s13() ) {
s274[n].s15<s371*>()->s500( s587 /*this*/, true );
}}
if( s278 != s233 && n < s630.size() && n < s582.size() && !s630[n].s15<s483*>()->s501( (s483*)s582[n] ) )
throw s968.s1000( L"wrong argument's type" );}
for( size_t n = 0; n < s630.size(); ++n ) {
if( s630[n]->s618() == s7::s868 )
throw s968.s1000( L"parameter is not provided" );}}
void s591::s814( s835& s153 ) const{
for( size_t n = 0; n < s582.size(); ++n )
s153.push_back( make_pair( s631[n].s617(), s582[n] ) );}
void s591::s2129( s577& s2128 ){
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s494() == s475 ) {
s371* ref = s274[n].s15<s371*>();
ref->reset();
ref->s382( s2128[n].s15<s483*>() );}
else if( s274[n]->s494() == s474 ) {
s274[n] = s2128[n];}
s630[n] = s2128[n];}}
void s591::s2133( s591* s2057, s272* impl, bool proc ){
if( s2057 && s2057 != this && s2057 != s587 ) s587 = s2057;
if( subject.s14() )
subject->s2133( s587, s588, false );
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s2133( this, s588, proc );
if( n < s630.size() ) {
s630[n]->s2133( this, s588, proc );
s628.s541( s631[n].s617(), s630[n].s15<s484*>(), s482::s147 );}}
for( size_t n = 0; n < s584.size(); ++n )
s584[n]->s2133( this, s588,  false );}
s483* s591::s1611( s483** s691, size_t s697 ){
size_t shift = 0;
if( s575 == s565 || s575 == s566 || s575 == s2113 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 || pc == s1337 ) {
s483* p = (s483*)( ( s371* )*( s581 + n ) )->s377();
*(s580 + n + shift) = p;}
else if( pc == s476 ) {
s981[n + shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
if( s981[n + shift]->s618() < 0 ) {
int s153 = s981[n + shift]->s618();
if( s153 == s7::s866 || s153 == s7::s2238 )
s981[n + shift]->s1679( 0 );
else if( s153 != s7::s1747 )
return s981[n + shift];}
*( s580 + n + shift ) = s981[n + shift];}
else if( pc == s474 )
*( s580 + n + shift ) = ( s483* )*( s581 + n );
else if( pc == s1245 )
(void)0;}}
return NULL;}
s486 s591::s497( s483** s691, size_t s697 ){
s486 s685;
s685 = s1611( s691, s697 );
if( s685.s14() )
return s685;
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s580, s498 );
if( s685->s618() < 0 )
break;}
s586 = s685;
return s685;}
s486 s841::s497( s483** s691, size_t s697 ){
s483* s685 = NULL;
s685 = s1611( s691, s697 );
if( s685 )
return s685;
if( !s1976 && s583[1]->s1203() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s562( s580, s498 );
s685 = s583[0];}
catch( s16* e ) {
TDException s968( TDException::Stage::s1030, s7::s1127, 
s1131, past,	*e );
delete e;
s685 = new s361( s300, s968.Msg() );
s586 = s685;}
return s685;}
s486 s842::s497( s483** s691, size_t s697 ){
s483* s685 = s365;
if( s575 == s568/* && subject.s14()*/ ) {
if( subject->s494() == s475 ) {
subject->s2133( this, s588, false );
s1654->s1661( subject.s15<s371*>()->s377() );}
else
s1654->s1661( subject->s497( 0, 0 ) );}
for( size_t n = 0; n < s582.size()/*nlocs*/; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 ) {
s483* par =( ( s371* )*( s581 + n ) )->s377();
if( par->s494() == s1245 ) {
par->s500( this, false );}
s630[n] = par;}
else if( pc == s476 )
s630[n] =
(s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
else if( pc == s474 )
s630[n] = *( s581 + n );}}
for( size_t n = s582.size(); n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 ) {
s483* par = ( ( s371* )*( s581 + n ) )->s377();
if( par->s494() == s1245 ) {
s630[n] = par->s335(0,0);
s630[n]->s500( this, false );}}
else if( pc == s476 )
s630[n] =
(s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
else if( pc == s474 )
s630[n] = ( ( s484* )*( s581 + n ) )->s335(0,0);}}
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s580, s498 );
if( s685->s618() < 0 ) {
if( s685->s618() == s7::s866 )
s685->s1679( 0 );
break;}}
return s685;}
s1357::s1357( s262* s300, s272* s592, s591* s587, const s263* s701 )
: s842( s300, s592, s587, s592, s568, vector<s271*>(), s701 ){
s1357* pin = (s1357*)s588->s344( s7::s428, s588->s298(), false );
if( pin ) {
pin->s628.copy( s628, (s272*)s588, s587 );
s631 = pin->s631;
s630 = pin->s630;
s582 = pin->s582;}}
s1357::s1357( const s1357& right, s272* s592, s591* s593,
const std::vector<s271*>& s705, const s263* s701 )
: s842( right, /*s592,*/ s593, /*s705*/ vector<s484*>(), s568, s701 )
{
s588 = s592;
s274.assign( s705.begin() + 1, s705.end() );
s493 = right.s493;
s586 = (s483*)s705[0];}
s1357::~s1357(){}
void s1357::s500( const s272* s1672, bool proc/*=false*/ )
{
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s1679( s7::s867 );}
s586 = s588.s15<s272*>();
s493 = s586->s352();
s1262();}
s486 s1357::s497( s483** s691, size_t s697 ){
s597( s587 );
s483* s685 = NULL;
if( s588->s352() == s1716 ) {
s685 = new s838( *s588.s15<s838*>(), ns, s588.s15<s591*>(), s274, s603() );
s685->s500( s587 );}
else {
s685 = new s272( *s588, s274, s603(), ns );
s685->s500( s587 );
s685->s2133( NULL, (s272*)s685, s2176 );}
s685->s1262();
return s685;
wstring s189 = s603()->s291();
wstring s1358 = s603()->Src();
s1358.replace( s1358.find( s189 ), s189.size(), 1, L' ' );
s263* ast_ = new s263( s189, s1358 );
s685 = s586.s15<s272*>()->s635( *ast_, s587, s671 );
s685->s1262();
return s685;
vector<s271*> s1648( begin(s274), end(s274));
s685 = s586->s355( s587, s1648, s603() );
s685->s1262();
return s685;}
bool
s591::s556( const wstring& s676, s371* ref,	
const wstring& s334, bool fr ) const{
bool s685 = false;
wstring s76 = s676;
size_t pl = s76.find( L"." );
if( pl == string::npos ) { //a
bool s2143 = s628.s156( s76 );
bool s2144 = true;
if( s2143 ) {
size_t off = s640( s76 );
if( off >= s582.size() )
s2144 = false;}
if( ( !s2143 && !s2176 ) || ( !s2143 && !fr ) || (!s2143 && s2176 && fr) ||
( s2143 && !s2176 && !fr && !intro )
/*|| ( s587.s14() && !intro && s2144 )*/ ) {
if( s587.s14() && ((s575 == s565) || !fr || !s2176 ) )
s685 = s587->s556( s76, ref, s334, s2176 );
if( !s685 ) {
if( s588.s14() )
s685 = s588->s556( s76, ref, s334, s2176 );
if( s685 ) {
if( s588->s494() != s479 && ref->s381() == s588.s15<s271*>() ) {
ref->s382( s1654.s15<s483*>() );
s1654.s15<s1600*>()->s1661( s588.s15<s483*>() );}}}
if( ! s685 )
s685 = s300->s556( s76, ref, s334, true );}
if( !s685 && s2143 ) {
size_t off = s640( s76 );
s271* s1060 = s630[off].s15<s271*>()->s496();
if( !s1060 )
s1060 = (s271*)s300->TR().s1007( s630[off]->s352() );
ref->s379( off, s1060->s503() );
if( s631[off].s1203() )
ref->s1260();
ref->s382( (s483*)this /*(s484**)&s274[off]*/ );
s685 = true;}}
else {// a.y
s76 = s676.substr( pl + 1 );
wstring s686 = s676.substr( 0, pl );
s271* ob = s628.get( s686, false );
if( !ob ) {
s685 = s588->s556( s676, ref, s334, true );
if( !s685 && s587.s14() )
s685 = s587->s556( s676, ref, s334, true );}
else {
size_t off = s640( s686 );
ref->s379( off, NULL );
s685 = ob->s503()->s556( s76, ref, s334, true );
ref->s382( (s483*)this );}}
return s685;}
bool
s841::s556( const wstring& s676, s371* ref, const wstring& s334,
bool fr) const{
if( s278 == s7::s1356 &&
s274[0].s15<s483*>()->s556( s676, ref, s334, fr ) )
return true;
return s591::s556( s676, ref, s334, fr );}
s271* s591::s598( size_t off ){
s271* s685 = s630[off];
return s685;}
s271* s591::s335( s591* s2057, s272* impl ) const{
return new s591( *this );}
s271* s841::s335( s591* s2057, s272* impl ) const{
return new s841( *this, s2057 ? s2057 : s587.s15<s591*>(), ns );}
s271* s842::s335( s591* s2057, s272* impl ) const{
auto s685 = new s842( *this, s2057, std::vector<s271*>(), s575, s603(), 
impl ? impl : s588.s15<s272*>(), s588.s15<s272*>(), intro, s2176 );
return s685;}
s271* s1357::s335( s591* s2057, s272* impl ) const{
return new s1357( *this );}
void s591::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Transductor : " <<  s278 << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"this : " << 
s4::s2187( (void*)this ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"subject : " << 
s4::s2187( subject.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"Type : " << 
s493 << L" (" << s353() << L")" << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"State : " << wh << endl;
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"Call type : " << ct[s575] << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"cont : " << 
s4::s2187( s588.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s419) << L"pout : " << 
s4::s2187( s587.s15<void*>() ).c_str() << endl;
if( !s628.empty() ) {
s628.s304( pd, s197 + s419 );}
if( !s582.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"fpars : " << endl;
for( size_t n = 0; n < s582.size(); ++n ) {
s582[n]->s304( pd, s197 + s419 * 2 );}
buf << endl;}
if( !s274.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"pars : " << endl;
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s304( pd, s197 + s419 * 2 );
buf << endl;}
buf << endl;}
if( !s631.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"namvec : " << endl;
for( size_t n = 0; n < s631.size(); ++n )
buf << s4::fill_n_ch( L' ', s197 + s419 * 2 ) << s631[n].s617()
<< "; ";
buf << endl;}
if( !s630.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"memvec : " << endl;
for( size_t n = 0; n < s630.size(); ++n ) {
s630[n]->s304( pd, s197 + s419 * 2 );}
buf << endl;}
if( !s584.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"exprs : " << endl;
for( size_t n = 0; n < s584.size(); ++n ) {
s584[n]->s304( pd, s197 + s419 * 2 );}
buf << endl;}}
wstring s591::trace( const char* topics ) const{
wstringstream buf;
int s197 = 0;
wstring s1077 = std::to_wstring( reinterpret_cast<long long>(this));
s1077 = s1077.substr( s1077.size() - 5 );
if( !topics ) {
s591::s304( &buf, s197 );}
else {
buf << L"Transductor : " << s1077 << endl;
string s2130 = topics;
if( s2130 == "id" ) 
buf << L"id: " << s1077 << endl;}
return buf.str();}
static s6::s1695 s1737;
s359::s359( s262* s300, const std::wstring& s, s272* s588, const s263* ast_ )
: s1401( s300, s588, ast_ ){
s493 = Types.String;
if( !s493 )
wh = s7::s868;
else {
wh = s7::s867;
s349 = s;}
s325 = s1579;}
s359::s359( s262* s300, s272* s592, const std::vector<s271*>& l, const s263* ast_ )
: s1401( s300, s592, ast_ ){
s274.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s868;
else
wh = s7::s867;
s493 = Types.String;
s325 = s1579;}
s359::s359( const s359& r, const s263* ast_ )
: s1401( r.s300, r.ns, ast_ ){
s349 = r.s349;
for( auto p : r.s274 )
s274.push_back( p->s335( 0, (s272*)r.ns ) );
wh = r.wh;
s493 = r.s493;
s325 = s1579;}
s359::s359( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ )
: s1401( s300, NULL, ast_ ){
s349 = s;
pos = string::npos;
s493 = Types.String;
s325 = s1579;
wh = s7::s867;}
s359::~s359(){}
s483* s359::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s359( s300, s588, l );}
void s359::s350(){
s1401<s1577, wchar_t, s359, s1573>::s350();
s348 = s1401<s1577, wchar_t, s359, s1573>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s359::s1236, Types.String,
{ s1122(), s1122( { s7::s1393, s7::s1399 } ) }, 0, 100 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s359::s780, s1151,
{ s1122( { Types.String } ), s1122( { s1153, s1512::s1549 } ) }, 1, 1 )));
s348.insert( make_pair( L"find-first-not-of", new s337( L"find-first-not-of", &s359::s1588, s1151,
{ s1122( { Types.String } ), s1122( { Types.String, s1151 } ), 
s1122( { Types.String, s1151, s1151 } )}, 1, 3 )));
s348.insert( make_pair( L"contains", new s337( L"contains", &s359::s2207, s1148,
{ s1122( { Types.String } ), s1122( { Types.Char } ) }, 1, 1 )));
s348.insert( make_pair( L"set", new s337( L"set", &s359::s387, s1153,
{ s1122( { Types.String } ), s1122( { s1152 } ) }, 1, 1, false )));
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s359::s1592, s1152,
{ s1122( { s1151, Types.String } ), s1122( { s1151, s1579 } ) }, 2, 2 )));
s348.insert( make_pair( L"size", new s337( L"size", &s359::s328, s1151,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"starts-with", new s337( L"starts-with", &s359::s1689, s1148,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"strip", new s337( L"strip", &s359::s2155, s1153,
{ s1122(), s1122( { Types.String } ), s1122( { Types.String, Types.String } ) }, 
0, 2 ) ) );
s348.insert( make_pair( L"sub", new s337( L"sub", &s359::s794, Types.String,
{ s1122( { s1512::s1549 } ), s1122( { s1512::s1271, s1512::s1271 } ) }, 1, 2 )));
s348.insert( make_pair( L"subn", new s337( L"subn", &s359::s1595, Types.String,
{ s1122( { s1512::s1549 } ), s1122( { s1512::s1271, s1512::s1271 } ) }, 1, 2 )));
s348.insert( make_pair( L"sum", new s337( L"sum", &s359::s388, Types.String,
{ s1122( { Types.String, s7::s1399 } ) }, 1, 100 )));
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s359::s393, Types.String,
{ s1122( { Types.String, s7::s1399 } ) }, 1, 100 )));
s348.insert( make_pair( L"to-bytes", new s337( L"to-bytes", &s359::s1347, s1149,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s359::s412, s1151,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"tolower", new s337( L"tolower", &s359::s890, Types.String,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"toupper", new s337( L"toupper", &s359::s891, Types.String,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"swapcase", new s337( L"swapcase", &s359::s2250, Types.String,
{ s1122() }, 0, 0 )));
s348.insert( make_pair( L"rfind", new s337( L"rfind", &s359::s799, s1151,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s359::s398, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"not", new s337( L"not", &s359::s413, s1148,
{ s1122( ) }, 0, 0 )));
s348.insert( make_pair( L"less", new s337( L"less", &s359::s399, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"greater", new s337( L"greater", &s359::s400, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"leq", new s337( L"leq", &s359::s401, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"geq", new s337( L"geq", &s359::s402, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"neq", new s337( L"neq", &s359::s403, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"max", new s337( L"max", &s359::s1965, s1153,
{ s1122( { Types.String, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"min", new s337( L"min", &s359::s1966, s1153,
{ s1122( { Types.String, s7::s1399 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"read", new s337( L"read", &s359::s409, s1153,
{ s1122( ), s1122( { s1151 } ), s1122( { s1512::s1505 } ), 
s1122( { s1512::s1505, s1151 } ) }, 1, 2 )));
s348.insert( make_pair( L"getline", new s337( L"getline", &s359::s1483, s1151,
{ s1122(), s1122( { s1512::s1505 } ) }, 0, 1 )));
s348.insert( make_pair( L"match", new s337( L"match", &s359::s1034, s1148,
{ s1122( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"replace", new s337( L"replace", &s359::s2206, s1153,
{ s1122( { Types.String, Types.String, Types.String } ),
s1122( { Types.String, Types.String, Types.String, Types.Int } ),
s1122( { Types.String, Types.String, Types.String, Types.Int, Types.Int } ),
}, 3, 5 )));
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1061 s1517 = ( (s316*)Types( s300, Types.Vector ) )->s1195( this, ts, s1719, s1279 );
s348.insert( make_pair( L"split", new s337( L"split", &s359::s1490, s1517,
{ s1122(), s1122( { Types.String } ) }, 0, 0 )));
s1737 = s1736;
s1737.s1697 = L" \n";}
void s847( s271* par, s262* s300, s272* s588,
s591* s215, s485& s153 ){
if( par->s494() == s477 ) {
s490 cs = new s561( *( (s561*)par ) );
s153 = s591::s600( cs, s300, s588, s215, s588->s298(), false );
s153.s15<Transd*>()->s500( s588, false );}
else if( 1 && par->s494() == s474 ) {
par->s500( /*s588*/ s588 );
s153 = par;}
else
s153 = par;}
void s359::s500( const s272* s879, bool ){
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( par->s494() == s477 ) {
s847( par, s300, ns, (s591*)ns, s274[n] );}
else if( par->s352() == s1415 ) {
auto pr = par.s15<s385*>();
auto rp = pr->s1194();
typename s1386::iterator s1519, s1520;
s1519 = rp.first.s15<s1139*>()->s1145();
s1520 = rp.second.s15<s1139*>()->s1145();
s1386 news( s1519, s1520 );
s349 += news;}
else if( par->s494() != s475 ) {
s349 += par->to_wstring();}
else {
if( s300->s1330() /*par.s15<s371*>()->s381().s14()*/ ) {
if( par.s15<s371*>()->s381().s13() )
par->s500( s879, false );
par.s15<s371*>()->s377()->to_wstring();}}}
s1262();}
wstring s700( wchar_t c ){
wstring s685;
if( c == L'n' )
s685 = L"\n";
else if( c == L'r' )
s685 = L"\r";
else if( c == L't' )
s685 = L"\t";
else if( c == L'\\' )
s685 = L"\\";
else {
s685 = c;}
return s685;}
s483* s359::s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const{
wstring s_ = s701.s291();
wstring s349, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s52( s_.substr( 7, s_.size() - 8 ), s48 );
if( s.empty() )
return new s359( s300, s588, std::vector<s271*>() );
vector<s271*> s705;
s271::s1333( s701, s300, s588, s334, s705 );
return s355( s588, s705, &s701 );}
else
s = s4::s52( s_, s48 );
if( s.size() ) {
size_t pos = 0;
const s945* s1051 = NULL;
if( s603() && s603()->Nqj() )
s1051 = s603()->Nqj()->s1006();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1051, s, pos, s94, s1737 );
if( s94.size() ) {
s = L"";
for( size_t n = 0; n < s94.size(); ++n ) {
wstring tmp = s94[n]->s169();
pl = s88.find( tmp[0] );
if( pl != string::npos && tmp.back() == s88[pl] )
tmp = tmp.substr( 1, tmp.size() - 2 );
s += tmp;}}}
if( s.size() == 2 && s[0] == L'\\' )
s349 = s700( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s349 = s;
while( pl != string::npos ) {
if( pl == s349.size() - 1 )
break;
if( s349[pl + 1] != L'\\' ) {
wstring code = s700( s349[pl + 1] );
s349 = s349.replace( pl, 2, code );
pl = s349.find( L"\\", pl + 1 );}
else {
s349.erase( pl, 1 );
pl = s349.find( L"\\", pl + 1 );}}}
if( s349.empty() )
s349 = s;
return new s359( s300, s349, s588, &s701 );}
s271* s359::s335( s591* s2057, s272* impl ) const{
return new s359( *this );}
s1061 s359::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" )
s685 = s325;
else
s685 = s1401::s1188( s1553, l );
return s685;}
void s359::s356( s271* p ) const{
if( p->s352() == Types.String )
*( (s359*)p )->s357() = s349;
else if( p->s352() == s1151 )
*( (s346*)p )->s357() = std::stoi( s349 );
else if( p->s352() == s1150 )
*( (s358*)p )->s357() = std::stof( s349 );
else if( p->s352() == s1579 )
*( (s1573*)p )->s357() = s349[0];
else
throw new s16( L"No conversion from " + s353() + L" to " + p->s353() );}
s359::operator int() const{
long s685;
if( !s4::s62( s349.c_str(), &s685 ) )
throw new s16( L"cannot cast String " + s349 + L" to Int" );
if( s685 > (std::numeric_limits<int>::max)() )
throw new s16( L"cannot cast String to Int: the value is too big: " + s349 );
return (int) s685;}
s359::operator double() const {
double s685;
if( !s4::s63( s349.c_str(), &s685 ) )
throw new s16( L"cannot cast String '" + s349 + L"' to Double" );
return s685;}
wstring s359::to_wstring( uint32_t s1565 ) const{
if( 0 && s349.front() == '\"' && 
s349.back() == '\"' )
return s349.substr( 1, s349.size() - 2 );
return s349; }
inline void s359::s1490( s483** s274, size_t s498 ){
s316* pv = (s316*)s274[0];
pv->clear();
wstring s72 = L"\n";
if( s498 == 3 )
s72 = s274[2]->to_wstring();
wstring& s = ((s359*)DR)->s349;
size_t s68 = 0, s69 = 0;
s1::s9<s359> adds = new s359( ((s359*)DR)->s300, L"", ( (s359*)DR )->ns );
while( s69 != wstring::npos && s68 < s.size()) {
if( s72.size() )
s69 = s.find( s72, s68 );
else
s69 = s68 + 1;
adds->s349 = s.substr( s68, s69 - s68 );
s68 = s69 + s72.size();
if( adds->s349.size() )
pv->s320().push_back( (s483*)adds->s335( 0,0 ) );}}
void s359::s1935( Stream* s1934 ) const{
if( s1934->s2067() )
s1934->s1480( L"\"" 
+ s349 + 
L"\"" );
else
s1934->s1480( s349 );
return;
s1500& ss = s1934->s1964();
ss << s349;}
void s359::s1960( s1905& s ){
s349 = s;}
void s359::s1959( Stream* s1934 ){
s1934->s1461( s349, string::npos );
return;
s1497& ss = s1934->s1963();
ss >> s349;}
s1322 s359::to_bytes() const{
s1322 s685;
string s = U8(s349);
s685.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s685[n] = s[n];
return s685;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s359*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
inline void s359::s1236( s483** s274, size_t s498 ){
s359* ps = (s359*)s274[1];
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
*s274 = ( s483* ) new s359( ps->s300, ps->s300, v );
s274[0]->s500( ps->ns );}
inline void s359::s387( s483** s274, size_t s498 ){
if( !PARN( 2 ) )
throw new s16( L"cannot assign Null object to String" );
( (s359*)DR )->s349 = ( (s359*)PARN( 2 ))->s349;
DR->s1262();
*s274 = (s483*)DR;}
inline void s359::s1592( s483** s274, size_t s498 ){
int pl = (int)*s274[2];
wchar_t c;
if( s274[3]->s352() == s1579 )
c = *( (s1573*)s274[3] )->s357();
else
c = ( (s359*)s274[3] )->s349[0];
( (s359*)DR )->s349[pl] = c;}
inline void s359::s328( s483** s274, size_t s498 ){
*( (s346*)s698 )->s357() = (int)( (s359*)DR )->s349.size();}
inline void s359::s1689( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'starts-with' syntax: ";
if( s498 < 3 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->s349;
if( dr.find( str ) == 0 )
*( (s360*)s274[0] )->s357() = true;
else
*( (s360*)s274[0] )->s357() = false;}
inline void s359::s2155( s483** s274, size_t s498 ){
wstring& dr = ( (s359*)DR )->s349;
wstring str;
if( s498 == 2 )
str = L" \r\n\t";
else
str = ( (s359*)s274[2] )->s349;
if( s498 < 4 )
dr = s4::s52( dr, str );
else {
wstring& str1 = ( (s359*)s274[3] )->s349;
dr = s4::s51( str, dr, str1 );}
*s274 = (s483*)DR;}
inline void s359::s388( s483** s274, size_t s498 ){
s698->s349 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s498; ++n )
s698->s349 += PARN( n )->to_wstring();}
inline void s359::s393( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349 + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s498; ++n )
s698->s349 += PARN( n )->to_wstring();
((s359*)DR)->s349 = s698->s349;}
inline void s359::s890( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349;
std::for_each( s698->s349.begin(), s698->s349.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s359::s891( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349;
std::for_each( s698->s349.begin(), s698->s349.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s359::s2250( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349;
std::for_each( s698->s349.begin(), s698->s349.end(), []( wchar_t & c ) {
if( std::iswlower( c  ) ) c = towupper( c ); else c = tolower( c );
} );}
inline void s359::s794( s483** s274, size_t s498 ){
wstring s696 = L"Invalid substring specification: ";
if( s498 < 2 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ((s359*)DR)->s349;
int start = 0, end = (int) dr.size();
if( s498 > 2 ) {
start = (int)*s274[2];
if( s498 > 3 )
end = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s16( s696 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s16( s696 + L"the end position is less than 0." );
if( start > end )
throw new s16( s696 + L"the start position is greater than string's length." );}
s698->s349 = dr.substr( start, end - start );}
inline void s359::s1595( s483** s274, size_t s498 ){
wstring s696 = L"Invalid substring specification: ";
if( s498 < 2 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ((s359*)DR)->s349;
int start = 0, s684 = 1;
if( s498 > 2 ) {
start = (int)*s274[2];
if( s498 > 3 )
s684 = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( s696 + L"the start position is greater than string's length" );
if( s684 < 0 )
throw new s16( s696 + L"the characters count cannot be less than 0" );}
s698->s349 = dr.substr( start, s684 );}
inline void s359::s780( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'find' syntax: ";
if( s498 < 3 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->s349;
int start = 0; 
if( s498 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s696 + L"the start position is greater than string's length." );}
*((s346*)s274[0])->s357() = (int)dr.find( str, start );}
inline void s359::s1588( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'find-first-not-of' syntax: ";
if( s498 < 3 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->s349;
int start = 0;
if( s498 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s696 + L"the start position is greater than string's length." );}
*((s346*)s274[0])->s357() = (int)dr.find_first_not_of( str.c_str(), start );}
inline void s359::s799( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'rfind' syntax: ";
if( s498 < 3 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->s349;
int start = (std::numeric_limits<int>::max)();
if( s498 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is less than 0." );}
*( (s346*)s274[0] )->s357() = (int)dr.rfind( str, start );}
inline void s359::s2207( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'contains' syntax: ";
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->to_wstring();
int start = 0; 
if( s498 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s696 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s696 + L"the start position is greater than string's length." );}
*((s360*)s274[0])->s357() = ( dr.find( str, start ) != string::npos );}
inline void s359::s398( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() == *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s413( s483** s274, size_t s498 ){
*s699->s357() = ( (s359*)DR )->s357()->empty();}
inline void s359::s399( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() < *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s400( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() > *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s401( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() <= *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s402( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() >= *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s403( s483** s274, size_t s498 ){
*s699->s357() = *( (s359*)DR )->s357() != *( (s359*)PARN( 2 ) )->s357();}
inline void s359::s1965( s483** s274, size_t s498 ){
*s698->s357() = ( (s359*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
if( *((s359*)s274[n])->s357() > *s698->s357() )
*s698->s357() = *( (s359*)s274[n] )->s357();}}
inline void s359::s1966( s483** s274, size_t s498 ){
*s698->s357() = ( (s359*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
if( *((s359*)s274[n])->s357() < *s698->s357() )
*s698->s357() = *( (s359*)s274[n] )->s357();}}
inline void s359::s409( s483** s274, size_t s498 ){
Stream* s1477 = NULL;
size_t s1452 = 0;
if( s498 >= 3 ) {
if( s274[2]->s352() == s1151 )
s1452 = (int)*s274[2];
else
s1477 = (Stream*)s274[2];
if( s498 == 4 )
s1452 = (int)*s274[3];}
else
s1477 = s1403;
wstring& s153 = *( (s359*)DR )->s357();
s1477->s1461( s153, s1452 );
int s685 = (int)s153.size();
s153.resize( s685 );
s274[0] = s274[1];}
inline void s359::s1483( s483** s274, size_t s498 ){
Stream* s1477 = NULL;
if( s498 >= 3 ) {
s1477 = (Stream*)s274[2];}
else
s1477 = s1403;
wstring& s153 = *( (s359*)DR )->s357();
s1477->s1462( s153 );
int s685 = (int)s153.size();
s153.resize( s685 );
*( (s346*)s698 )->s357() = s685;}
inline void s359::s1034( s483** s274, size_t s498 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1040;
wstring s = DR->to_wstring();
bool s153 = regex_match( s, s1040, rg );
*s699->s357() = s153;}
inline void s359::s2206( s483** s274, size_t s498 ){
wstring s = DR->to_wstring();
wregex rg( PARN( 2 )->to_wstring() );
wstring rep( PARN( 3 )->to_wstring() );
*((s359*)*s274)->s357() = regex_replace( s, rg, rep );}
inline void s359::s1347( s483** s274, size_t s498 ){
( (s1292*)s698 )->s320() = DR->to_bytes();}
inline void s359::s412( s483** s274, size_t s498 ){
s359* ps = (s359*)DR;
wstring sv = ps->s320();
assert( !sv.empty() );
int s163;
wsmatch s1074;
static wregex s2085( LR"regex(^\w*(\d+)\w*$)regex" );
static wregex s2084( LR"regex(^\w*([[:alnum:]]+)\:(\d+)\w*$)regex" );
if( regex_match( sv, s1074, s2085 ) ) {
s163 = (int)*DR;}
else if( regex_match( sv, s1074, s2084 ) ) {
wstring snum = s1074[1].str();
wstring s2086 = s1074[2].str();
int base = std::stoi( s2086, NULL, 10 );
s163 = std::stoi( snum, NULL, base );}
else
throw new s16( L"string cannot be converted to int: " + sv );
*( (s346*)s698 )->s357() = s163;}
void s359::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " 
<< (s349.size() ? s349 : L"\"\"") ;}
size_t s359::s322() const{
return hash<wstring>{}(s349);}
bool s359::operator==( const s483* p ) const{
return ( (s359*)p )->s349 == s349;}
bool s359::operator<( const s483* p ) const{
return s349 < ( (s359*)p )->s349;}
Iterator* s359::s1164( const s483* idx ){
s1577::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s1578( s300, this, it, it == s349.end() ? it : it + 1 );}
Iterator* s359::s1183( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( *it == *( (s1295*)_val )->s357() )
return new s1578( s300, this, it, it + 1 );
return new s1578( s300, this, end( s349 ), end( s349 ) );}
s483* s359::s1190( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s1578*)it )->s1145() );
return new s346( s300, (int)n );}
Iterator* s359::s1185() {
if( s349.size() )
return new s1578( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s1578( s300, this, s349.end(), s349.end() );}
Iterator* s359::s1189() {
return new s1578( s300, this, s349.end(), s349.end() ); }
Iterator* s359::s314( s385* rv ){
if( !rv )
return new s1578( s300, this, begin( s349 ), end( s349 ) );
s1144 pr = rv->s1194( this );
return new s1578( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
vector<wstring> s955( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s817::s817( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s759, s701, true,
false ){
TDException s968( s7::s1109, s931, s701 );
if( l.empty() )
throw s968.s1000( L"too few arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.String;
s591::s1242( ( vector<s271*>& )l, s955 );}
s817::s817( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s759, NULL, true,
false ){
s493 = Types.String;}
void s817::s500( const s272* s1672, bool proc ){
s591::s500( s1672, proc );
wstring s696 = L"Invalid parameters of 'substr' function: ";
if( s274[0]->s352() != Types.String )
throw new s16( s696 + L"The first parameter is not of String type." );
str = s274[0].s15<s359*>();
size_t s726 = 1;
int s777 = 0;
s742 s766 = s719;
s720 =	nTo = 1;
s793 = s740 = 0;
while( s726 < s274.size() ) {
s485 par_ = s274[s726];
s472 pc = par_->s494();
if(	pc == s475 || pc == s1063 || pc == s474 || pc == s476 ) {
s485 par;
s489 rf;
if( pc == s475 ) {
rf = par_.s15<s371*>();
par = (s271*)rf->s378();}
else if( pc == s1063 ) {
rf = par_.s15<s371*>();
par = par_;}
else
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1226 ) {
if( s777 != 0 )
throw new s16( s696 + L"'from' is misplaced." );
s777 = 1;
s766 = s764;}
else if( rf->Id() == s1233 ) {
if( s777 != 0 )
throw new s16( s696 + L"'to' is misplaced." );
s777 = 1;
s766 = s816;}
else if( rf->Id() == s1219 ) {
if( s766 != s719 && s777 >= 2 )
throw new s16( s696 + L"'before' is misplaced." );
if( s766 == s816 )
s740 = -1;
else
s793 = -1;
s777 = 2;}
else if( rf->Id() == s1215 ) {
if( s766 != s719 && s777 >= 2 )
throw new s16( s696 + L"'after' is misplaced." );
if( s766 == s816 )
s740 = 1;
else
s793 = 1;
s777 = 2;}
else if( rf->Id() == s1225 ) {
if( s766 != s719 && s777 >= 3 )
throw new s16( s696 + L"'first' is misplaced." );
s777 = 3;}
else if( rf->Id() == s1229 ) {
if( s766 != s719 && s777 >= 3 )
throw new s16( s696 + L"'last' is misplaced." );
if( s766 == s816 )
nTo = string::npos;
else
s720 = string::npos;
s777 = 3;}
else
throw new s16( s696 + L"unknown parameter '" + rf->s617() + L"'." );}
else if( par->s352() == Types.String ) {
if( s766 == s764 )
s808 = par;
else if( s766 == s816 )
s801 = par;
else {
if( s808.s13() && s763.s13() )
s808 = par;
else if( s801.s13() && s723.s13() )
s801 = par;
else
throw new s16( s696 + L"unknown parameter '" + rf->s617() + L"'." );}
s777 = 0; s766 = (( s766 == s764 || s766 == s719 ) ? s816 : s764 );}
else if( par->s352() == s1151 ) {
if( s766 == s764 )
s763 = par;
else if( s766 == s816 )
s723 = par;
else {
if( s808.s13() && s763.s13() )
s763 = par;
else if( s801.s13() && s723.s13() )
s723 = par;
else
throw new s16( s696 + L"unknown parameter '" + rf->s617() + L"'." );}
s777 = 0; s766 = ( ( s766 == s764 || s766 == s719 ) ? s816 : s764 );}}
s726++;}}
s486 s817::s497( s483** s691, size_t s697 ){
size_t s192 = 0, s683 = string::npos;
wstring s761, s725;
wstring dom = str->s497( 0, 0 )->to_wstring();
if( s763.s14() ) {
s472 pc = s763->s494();
if( pc == s475 || pc == s1337 )
s192 = (size_t)(int)*s763.s15<s371*>()->s377();
else if( s763->s494() == s476 )
s192 = (size_t)(int)*s763->s497( 0, 0 );
else
s192 = (size_t)(int)*s763.s15<s346*>();}
else if( s808.s14() ) {
s761 = s808->to_wstring();
if( s720 == 1 )
s192 = dom.find( s761 );
else if( s720 == string::npos )
s192 = dom.rfind( s761 );
else
throw new s16( L"substr: nFrom =" + std::to_wstring( s720 ) );
if( s192 != string::npos ) {
if( s793 > 0 )
s192 += s761.size();
else
s192 += s793;}}
if( s723.s14() ) {
s472 pc = s723->s494();
if( pc == s475 || pc == s1337 )
s683 = (size_t)(int)*s723.s15<s371*>()->s377();
else if( s723->s494() == s476 )
s683 = (size_t)(int)*s723->s497( 0, 0 );
else
s683 = (size_t)(int)*s723.s15<s346*>();}
else if( s801.s14() ){
s725 = s801->to_wstring();
if( nTo == 1 )
s683 = dom.find( s725, s192 + 1 );
else if( nTo == string::npos )
s683 = dom.rfind( s725 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s720 ) );
if( s683 != string::npos )
s683 += s740;}
wstring s153;
if( s192 == string::npos || s192 >= s683 || s192 >= dom.size() )
s153 = L"";
else
s153 = dom.substr( s192, s683 - s192 );
s586 = new s359( s300, s153, this );
return s586;}
s271* s817::s335( s591* s2057, s272* impl ) const{
return new s817( *this );}
s385::s385( s262* s300 )
: s326( s300, NULL, NULL ), s978( false ), s979( false ), s988( 0 )//, s884( false )
{
s493 = Types.Range;
s1243 = new s1529( s300, 0 );
s1244 = new s1529( s300, U64_MAX );
s1175 = new s1529( s300, 0 );}
s385::s385( s262* s300, s326* s588, Iterator* it )
: s326( s300, NULL, NULL ), s985( s588 ), s1466( it ), s978( false ), s979( false ), 
s988( 0 ){
s493 = s1415;}
s385::s385( uint64_t _beg, uint64_t _end )
: s326( NULL, NULL, NULL ), s978( false ), s979( false ), s988( 0 )//, s884( false )
{
s1243 = new s1529( s300, _beg );
s1244 = new s1529( s300, _end );
s493 = s1415;
s1175 = new s1529( s300, 0 );}
s385::s385( s262* s300, const wstring& s77, const s263* ast_ )
: s326( s300, NULL, ast_ ), s978( false ), s979( false ), s988( 0 )//, s884( false )
{}
s385::s385( const s385& r, const s263* ast_ )
: s326( r.s300, r.ns, ast_ ), s978( false ), 
s979( false ), s988( r.s988 ), s1175( r.s1175 )//, s884( r.s884 )
{
s493 = r.s493;}
vector<wstring> s950( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s385::s385( s262* s300, s272* s592, const vector<s271*>& l_, const s263* ast_ )
: s326( s300, s592, ast_ ), s978( false ), s979( false ), s988( 0 ), 
s1175( new s1529( s300, 0 ) )//, s884( false )
{
s493 = s1415;
if( l_.empty() )
return;
TDException s968( s7::s1107, s932, ast_ );
if( l_.size() > 9 )
throw s968.s1000( L"too many arguments" );
s591::s1242( ( vector<s271*>& )l_, s950 );
const size_t s1055 = 3;
std::vector<s271*> l( s1055 );
if( l_[0]->s494() == s1063 ) {
s371* rf = (s371*)l_[0];
if( rf->Id() == s1228 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1529( s300, 0 );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1529( s300, 0 );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s588 = l[0];
s1243 = l[1];
s1244 = l[2];
if( s588.s13() ) {
s325 = Types.s1528;
s317 = Types.s1528;}
else {
s325 = 0;
s317 = 0;}
s493 = s1415;}
s483* 
s385::s354( const s263& s701, s272* s588, const wstring& s334 ) const{
wstring s = s701.s291();
wstring s347 = s353();
if( s.find( s347 ) == 0 && ( s.size() == s347.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s696 = L"Malformed Range definition: " + s;
vector<s271*> s705;
s271::s1333( s701, s300, s588, s334, s705 );
return new s385( s300, s588, s705, &s701 );}
else
return NULL;}
void s385::s500( const s272* s879, bool ){
TDException s968( s7::s919, s932, s603(), L"wrong Range definition" );
ns = (s272*)s879;
bool s1168 = false;
try {
if( s588.s14() ) {
if( s588->s494() == s475 ) {
s588.s15<s371*>()->s500( s879 );
s1168 = s588->s1203();
s985 = (s326*)s588.s15<s371*>()->s377();}
else if( s588->s494() == s477 ) {
s485 tmp = s271::s1018( s300, s588, (s272*)s879, (s591*)s879, s879->s298(), false );
s588 = tmp;
s985 = (s326*)s588->s496();}
else {
s985 = (s326*)s271::s1018( s300, s588, (s272*)s879, (s591*)s879, s879->s298(), false );}
s325 = s985->ValType();
s317 = s985->s319();}
if( s1243.s14() ) {
if( s1243->s494() == s475 )
s1243.s15<s371*>()->s500( s879 );
else {
s485 tmp = s271::s1018( s300, s1243, (s272*)s879, (s591*)s879, s879->s298(), false );
s1243 = tmp;}}
else
s1243 = s365.s15<s484*>();
if( s1244.s14() ) {
if( s1244->s494() == s475 )
s1244.s15<s371*>()->s500( s879, false );
else {
s485 tmp = s271::s1018( s300, s1244, (s272*)s879, (s591*)s879, s879->s298(), false );
s1244 = tmp;}}
else
s1244 = s365.s15<s484*>();}
catch( s16* e ) {
throw e->s30( L"while compiling Range: '" + s603()->Src() + L"'" );}
s1262();
s1260( s1168 );}
void s385::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s385::s1236, s1415,
{ s1122( { s1512::s1549 } ), s1122( { s1151, s1151 } ),
s1122( { s1512::s1507, s1151 } ),
s1122( { s1512::s1507, s1151, s1151 } ) }, 1, 3, true ) ) );
s348.insert( make_pair( L"size", new s337( L"size", NULL, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"max-element", new s337( L"resize", NULL, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", NULL, s1152,
{ s1122() }, 0, 0, false ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s385::s398, s1148,
{ s1122( { s1512::s1507 } ) }, 1, 1, true ) ) );
s348.insert( make_pair( L"reverse", new s337( L"reverse", NULL, s1152,
{ s1122() }, 0, 0, false ) ) );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s1142 s385::s1197( const std::wstring& s343 ) const{
if( s343 == s7::s1356 || s343 == L"eq" )
return s336::s1197( s343 );
if( s985.s14() ) 
return s985->s1197( s343 );
return s1142();}
s1142 s385::s1192( const std::wstring& s343, s1122& ap ) const{
if( s343 == s7::s1356 || s343 == L"eq" )
return s336::s1192( s343, ap );
if( s985.s14() )
return s985->s1192( s343, ap );
assert( 0 );
throw;}
s1142 s385::s1187( const std::wstring& s343,
s1122& ap ) {
if( s343 == s7::s1356 )
return s336::s1187( s343, ap );
if( s985.s14() )
return s985->s1187( s343, ap );
assert( 0 );
throw;}
s1061 s385::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == s7::s1356 ) {
s685 = s1512::s1507;}
else if( s985.s14() )
return s985->s1188( s1553, l );
return s685;}
const vector<wstring>&
s385::s1191( const wstring& s343 ) const{
if( s343 == s7::s1356 || s985.s13() )
return s336::s1191( s343 );
else
return s985->s1191( s343 );}
s483* s385::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s385( s300, s588, l, ast_ );}
inline bool
s385::s501( const s483* s502 ) const{
if( s502->s352() != s352() ) {
return s300->TR().s1465( s502->s352(), s1512::s1507 );}
return true;}
size_t s385::s1138() const{
if( s985.s14() )
return s985->s1138();
else
return 0;}
s1144 s385::s1194(){
Iterator *fir = NULL, *sec = NULL;
if( s985.s14() ) {
if( s978 )
fir = s985->s1183( s1243.s15<s483*>() );
else if( s1243 == s1521 )
fir = s985->s1189();
else
fir = s985->s1164( s1243.s15<s483*>() );
if( s979 )
sec = s985->s1183( s1244.s15<s483*>() );
else if( s1244 == s1521 )
sec = s985->s1189();
else
sec = s985->s1164( s1244.s15<s483*>() );
if( s985->s1138() >= 1 && ( s1243 == s1521 || sec->operator<( fir ) ) ) {
( (s1125*)fir )->reverse();
( (s1125*)sec )->reverse();}}
return s1144( fir, sec );}
s1144 s385::s1194( s326* s592 ){
Iterator *fir, *sec;
if( s978 )
fir = s592->s1183( s1243.s15<s483*>() );
else if( s1243 == s1521 )
fir = s592->s1189();
else 
fir = s592->s1164( s1243.s15<s483*>() );
if( s979 )
sec = s592->s1183( s1244.s15<s483*>() );
else if( s1244 == s1521 )
sec = s592->s1189();
else
sec = s592->s1164( s1244.s15<s483*>() );
if( s592->s1138() >= 1 && ( s1243 == s1521 || sec->operator<( fir ) ) ){
( (s1125*)fir )->reverse();
( (s1125*)sec )->reverse();}
return s1144( fir, sec );}
inline void s385::s1236( s483** s274, size_t s498 ){
s385* r = ( (s385*)s274[1] );
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 ) 
{ return v.push_back( (s271*) s349 ); } );
s385* s1470 = new s385( r->s300, r->ns, v );
s1470->s500( r->ns );
*s274 = (s483*)s1470;}
inline void s385::s398( s483** s274, size_t s498 ){
Iterator* it = ( (s385*)s274[1] )->s314( NULL );
Iterator* it1;
if( s274[2]->s352() == s1415 )
it1 = ( (s385*)s274[2] )->s314( NULL );
else
it1 = ( (s326*)s274[2] )->s314( NULL );
bool s685 = true;
while( 1 ) {
s485 p = it->s315();
s485 p1 = it1->s315();
if( p.s13() ) {
if( p1.s14() )
s685 = false;
break;}
if( p1.s13() ) {
s685 = false;
break;}
if( !p.s15<s483*>()->operator==( p1.s15<s483*>() ) ) {
s685 = false;
break;}}
*( (s360*)(s484*)*s274 )->s357() = s685;}
s271* s385::s335( s591* s2057, s272* impl ) const{
return new s385( *this );}
void s385::s356( s271* p ) const{
p = new s385( *this );}
size_t s385::s322() const{
return (size_t)this;}
bool s385::operator==( const s483* p ) const{
return ( this == p );}
bool s385::operator<( const s483* p ) const{
return false;}
bool s385::s1979() const{
return s988 == s1546;}
Iterator* s385::s314( s385* r ){
if( s1243.s14() ) {
s472 pc = s1243->s494();
if( pc == s476 )
s1542 = s1243->s497( 0, 0 );
else if( pc == s475 )
s1542 = s1243.s15<s371*>()->s377();
else
s1542 = s1243.s15<s483*>();}
if( s1244.s14() ) {
s472 pc = s1244->s494();
if( pc == s476 )
s1543 = s1244->s497( 0, 0 );
else if( pc == s475 )
s1543 = s1244.s15<s371*>()->s377();
else
s1543 = s1244.s15<s483*>();}
if( s985.s14() )
return s985->s314( this );
s988 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1243.s15<s483*>();
return this;}
s271* s385::s315(){
if( s988 == U64_MAX ) {
if( s1542.s14() ) {
if( s1542->s352() == s1527 )
s988 = *s1542.s15<s1529*>()->s357();
else {
s1303 tmp;
s1542->s356( &tmp );
if( *tmp.s357() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s988 = *tmp.s357();}}
if( s1543.s14() ) {
if( s1543->s352() == s1527 )
s1546 = *s1542.s15<s1529*>()->s357();
else {
s1303 tmp;
s1543->s356( &tmp );
if( *tmp.s357() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1546 = *tmp.s357();}}
if( s988 > s1546 )
incr = -1;
else
incr = 1;}
else
s988 += incr;
if( s988 == s1546 )
return NULL;
*s1175->s357() = s988;
return s1175;}
s271* s385::s962(){
return s318->s962();}
const s271* s385::s962() const{
return NULL;}
s271* s385::Idx(){
return NULL;}
s271* s385::El(){
return NULL;}
void s385::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Range :: " << L" curit: " << s318 << endl;}
wstring s385::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
Iterator* it = ((s385*)this)->s314( NULL );
bool b = false;
while( 1 ) {
s485 p = it->s315();
if( p.s13() )
break;
if( b ) s685 += L", ";
else b = true;
s685 += p->to_wstring();}}
s685 += L"]";
return s685;}
vector<wstring> s1135( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1134::s1134( s262* s300, const wstring& s77, const s263* ast_ )
: s326( s300, NULL, ast_ ), s987( new s371( s7::s1374, s300, s475 ) ), s988(NULL), s349( new s346( s300, 0 )), 
s685( new s346( s300, 0 )),s1353(0){
s493 = Types.Filter;}
s1134::s1134( const s1134& r, const s263* ast_ )
: s326( r.s300, r.ns, ast_ ), s987( new s371( s7::s1374, s300, s475 ) ), s988(NULL), s349( new s346( s300, 0 ) ),
s685( new s346( s300, 0 ) ), s1353(r.s1353){
*s349->s357() = (int)*r.s349;
*s685->s357() = (int)*r.s685;
ns = r.ns;
s493 = r.s493;}
s1061 s1453( size_t& idx, const vector<s271*>& l ){
if( l.size() > idx && l[idx]->s494() == s1063 )
idx++;
if( l.size() > idx )
return l[idx]->s352();
return 0;}
s1134::s1134( s262* s300, s272* s592, const vector<s271*>& l_, const s263* ast_ )
: s326( s300, s592, ast_ ), s987( new s371( s7::s1374, s300, s475 )), s988(NULL),
s349( new s346( s300, 0 ) ),	s685( new s346( s300, 0 ) ),s1353(0){
s493 = s1909;
ns = s592;
if( l_.empty() )
return;
TDException s968( s7::s1367, s932, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s968.s1000( L"too many arguments" );
s591::s1242( ( vector<s271*>& )l_, s1135 );
const size_t s1055 = 3;
std::vector<s271*> l( s1055 );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s352() == s1415 ) {
range = (s385*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s494() != s1063 || ((s371*)l_[bas])->Id() != s1332 )
throw s968.s1000( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s494() != s1063 || ((s371*)l_[bas])->Id() != s1235 )
throw s968.s1000( L"expected the 'where:' clause" );
if( l_[bas+2]->s494() != s1063 || ((s371*)l_[bas+2])->Id() != s1332 )
throw s968.s1000( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s588 = l[0];
where = l[1];
s1070 = l[2];}
s483* 
s1134::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
wstring s347 = s353();
if( s.find( s347 ) == 0 && ( s.size() == s347.size() || s[s.size() - 1] == L')' ) ) {
s485 fi = new s346( s300, 0 ), la = new s346( s300, 0 ), in = new s346( s300, 1 );
wstring sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong filter constructor syntax" );
wstring s696 = L"Malformed Filter definition: " + s;
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
if( /*!s697 ||*/ s697 > 3 )
throw new s16( s696 );
std::vector<s271*> s274;
for( size_t n = 0; n < s697; ++n ) {
s263::s275::const_iterator it = s702.find( std::to_wstring( n ) );
s274.push_back( s271::s504( *it->second, s300, s588, s334 ) );}
return s355( s588, s274, &s701 );
if( s300->TR().s1465( s274[0]->s352(), s1512::s1507 ) )
return new s1134( s300, s588, s274 );
else
return new s951( s300, s588, s274 );}
else
return NULL;}
void s1134::s500( const s272* s879, bool ){
TDException s968( s7::s919, s932, s603(), L"wrong Filter definition");
ns = (s272*)s879;
if( s588.s13() )
return;
if( s588->s494() == s475 ) {
s489 rf = s588.s15<s371*>();
if( rf->s381().s13() )
rf->s500( s879 );
s985 = rf.s15<s371*>()->s377();}
else if( s588->s494() == s477 ) {
s485 tmp = s271::s1018( s300, s588,(s272*)s879, (s591*)s879, s879->s298(), false );
s588 = tmp;
s985 = s588->s496();}
else {
s985 = (s483*)s271::s1018( s300, s588, (s272*)s879, (s591*)s879, s879->s298(), false );}
if( !s300->TR().s1465( s985->s352(), s1512::s1507 ) )
throw s968.s1000( L"the type is not rangeable: " + s985->s353() );
if( s985->s494() == s474 ) {}
else if( s985->s494() == s480 ) {}
else
throw s968.s1000( L"unsupported container type" );
s987->s379( 0, s300->TR().s1007( s985.s15<s326*>()->ValType() ) );
s987->s382( (s483*)this );
if( where.s14() ) {
if( where->s494() == s475 )
where.s15<s371*>()->s500( s879 );
else
where = s271::s1018( s300, where, (s272*)this, (s591*)s879, s879->s298(), false );}
if( s1070.s14() ) {
if( s1070->s494() == s475 ) {
s1070.s15<s371*>()->s500( s879 );
s325 = s1070->s496()->s352();}
else {
if( s1070->s494() != s1245 )
s1070 = s271::s1018( s300, s1070, (s272*)s879, (s591*)s879, s879->s298(), false );
s325 = s1070.s15<s838*>()->s1328();}}
if( !s325 )
s325 = s985.s15<s326*>()->ValType();
s493 = s300->TR().s1046( s813::Cont( { s1909, 1, s325, 0 }) );
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" +
s300->TR().s1352( s300->TR().s804( s325 ) ) + L">";
s1353 = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s1262();}
void s1134::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1134::s1236, s1909,
{ s1122( { s1151, s1151 } ) }, 1, 2 ) ) );
s348.insert( make_pair( L"to-vector", new s337( L"to-vector", &s1134::s1348, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"max-element", new s337( L"resize", NULL, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", NULL, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", NULL, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"reverse", new s337( L"reverse", NULL, s1152,
{ s1122() }, 0, 0 ) ) );
s348.equal_range( s7::s1356 ).first->second->s1261( true );
s348.equal_range( L"to-vector" ).first->second->s1261( true );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s1142 s1134::s1192( const std::wstring& s343, s1122& ap ) const{
return s336::s1192( s343, ap );
if( s343 == s7::s1356 )
return s336::s1192( s343, ap );
assert( 0 );
throw;}
s1142 s1134::s1187( const std::wstring& s343, s1122& ap ){
if( s343 == s7::s1356 ) {
auto ran = s342().equal_range( s343 );
s337* mi = ran.first->second;
s1142 s1237( s325, mi->s1136(), mi->s1203(), mi->s2017() );
return s1237;}
else if( s343 == L"to-vector" ) {
auto ran = s342().equal_range( s343 );
s337* mi = ran.first->second;
s1142 s1237( s1353, mi->s1136(), mi->s1203(), mi->s2017() );
return s1237;}
assert( 0 );
throw;}
s1061 s1134::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == s7::s1356 ) {
s685 = s1512::s1507;}
else if( s1553 == L"to-vector" ) {
s685 = s1353;}
return s685;}
s483* s1134::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1134( s300, s588, l, ast_ );
s1061 pt = l[0]->s352();
if( s300->TR().s1465( pt, s1512::s1507 ) )
return new s1134( s300, s588, l );
s591::s1242( ( vector<s271*>& )l, s1135 );
s472 pc = l[0]->s494();
vector<s271*> s912;
size_t s375 = 0;
if( pc == s474 ) {
if( pt == s1151 ) {
if( l.size() > 1 && l[1]->s352() == s1151 ) {
s912 = { l[0], l[1] };
s375 = 1;}
else {
s912 = { l[0] };
s375 = 2;}}}
else if( pc == s1063 ) {
if( ( (s371*)l[0] )->s1304() == s1233 ) {
s912 = { l[1] };
s375 = 2;}
else if( ( (s371*)l[0] )->s1304() == s1226 ) {
s912 = { l[1], l[3] };
s375 = 4;}}
vector<s271*> l1 = { new s951( s300, s588, s912 ) };
l1.insert( l1.end(), l.begin() + s375, l.end() );
return new s1134( s300, s588, l1 );
if( l.size() ) {
if( l[0]->s494() == s475 ) {
l[0]->s500( s588 );
if( s300->TR().s1465( l[0]->s352(), s1512::s1507 )  )
return new s1134( s300, s588, l );}}
else {
return new s1134( s300, s588, l );}
return new s951( s300, s588, l );}
s483* s1134::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1134* s685 = new s1134( s300, L"" );
s813::Cont s1073;
s491::s2119( vt, idx, s1073 );
s813 s1071( s1073[0] );
return s685;}
inline bool
s1134::s501( const s483* s502 ) const{
return ( ((s1134*)s502)->s352() == s352() );}
inline void s1134::s1236( s483** s274, size_t s498 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
s1134* pf = (s1134*)s274[1];
*s274 = ( s483* ) pf->s355( pf->ns, v, pf->s603() );
s274[0]->s500( pf->ns );
pf->s987->s382( s274[0] );
pf->s988 = ((s1134*)s274[0])->s988;}
inline void s1134::s1348( s483** s274, size_t s498 ){
s1134* pf = (s1134*)s274[1];
*s274 = ( s483* ) pf->s300->TR().
s1007( pf->s1353 )->s355( pf->ns );
Iterator* s1020 = pf->s314( NULL );
while( 1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
( (s316*)s274[0] )->add( p->s335(0,0) );}
s274[0]->s1262();}
s271* s1134::s335( s591* s2057, s272* impl ) const{
return new s1134( *this );}
void s1134::s356( s271* p ) const{
p = new s1134( *this );}
size_t s1134::s322() const{
return (size_t)this;}
bool s1134::operator==( const s483* p ) const{
return ( this == p );}
bool s1134::operator<( const s483* p ) const{
return false;}
bool
s1134::s556( const wstring& s676, s371* ref, const wstring& s334, bool ) const{
if( s676 == s7::s1374 ) {
ref->s1343( s987.s15<s371*>() );
return true;}
return false; // ns->s556( s676, ref, s334 );
}
s271* s1134::s598( size_t off ){
assert( off == 0 );
if( s988 )
return s988;
return (s271*) s987->s503();}
s1144 s1134::s1194(){
if( range.s14() )
return range->s1194();
else
return s985.s15<s326*>()->s1194();}
Iterator* s1134::s314( s385* r ){
if( range.s14() ) {
s1144 pr = range->s1194( );
s318 = pr.first;
s1489 = pr.second;}
else {
s1144 pr = s985.s15<s326*>()->s1194();
s318 = pr.first;
s1489 = pr.second;}
return this;}
bool s1134::s1979() const{
if( !s988 || s318->operator==( s1489 ) )
return true;
return false;}
s271* s1134::s315(){
while( 1 ) {
s988 = s318->s315();
if( !s988 || s318->operator==( s1489 ) )
return NULL;
if( where.s14() && ( false == (bool)*where->s497(0,0) ) )
continue;
break;}
if( s1070.s14() )
return s1070->s497( 0, 0 ).s15<s484*>();
else
return s988;}
s271* s1134::s962(){
return s318->s962();}
const s271* s1134::s962() const{
return NULL;}
s271* s1134::Idx(){
return NULL;}
s271* s1134::El(){
return NULL;}
void s1134::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s197 ) << L"Input: ";
if( s588.s14() ) {
s985.s14() ? s985->s304( pd, s197 + s419 ) : s588->s304( pd, s197 + s419 );}
buf << s4::fill_n_ch( L' ', s197 ) << L"Do: ";
if( s1070.s14() ) s1070->s304( pd, s197 + s419 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s197 ) << L"curitref: ";
s987->s304( pd, 0 );
buf << endl;}
s951::s951( s262* s300 ) 
: s326( s300, NULL, NULL ) {
s493 = Types.Seq;}
s951::s951( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ )
: s326( s300, s588, ast_ ), s1047( true ){
if( l.empty() )
return;
wstring s998 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s998 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s493 = s1416;}
s951::~s951(){}
s483* 
s951::s354( const s263& s701, s272* s588, const wstring& s334 ) const{
wstring s = s701.s291();
wstring s347 = s353();
if( s.find( s347 ) == 0 && ( s.size() == s347.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s696 = L"Malformed Sequence definition: " + s;
vector<s271*> s705;
s271::s1333( s701, s300, s588, s334, s705 );
return new s951( s300, s588, s705 );}
else
return NULL;}
s483* s951::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s951( s300, s588, l, ast_ );}
void s951::s500( const s272* s879, bool ){
if( end.s13() )
return;
wstring s998 = L"wrong sequence generator syntax";
s485 tmp = s271::s1018( s300, end, (s272*)s879, (s591*)s879, s879->s298(), false );
end = tmp;
if( start.s14() ) {
tmp = s271::s1018( s300, start, (s272*)s879, (s591*)s879, s879->s298(), false );
start = tmp;}
else {
if( end->s352() == s1151 )
start = new s346( s300, 0 );
else {
start = s300->TR().s518( end->s352(), (s272*)s879, s879->s298() );
start->s500( s879 );}}
if( incr.s14() ) {
tmp = s271::s1018( s300, incr, (s272*)s879, (s591*)s879, s879->s298(), false );
incr = tmp;}
else {
if( start->s352() == s1151 )
incr = new s346( s300, 1 );
else
throw new s16( s998 + L": increment value is missing" );}
if( start->s494() == s475 ) {
s271* p = start.s15<s371*>()->s377();
s989 = p->s335(0,0);
s1659 = p->s335(0,0);}
else {
s989 = start->s335(0,0);
s1659 = start->s335(0,0);}
std::vector<s271*> pl = { s989, incr };
s561 cs( s300, L"sumeq", pl, NULL );
s1058 = s591::s600( &cs, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
s1058->s500( s879, false );
std::vector<s271*> pl1 = { s989, start };
s561 cs1( s300, L"set", pl1, NULL );
set = s591::s600( &cs1, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
set->s500( s879, false );
std::vector<s271*> pl2 = { s989, end };
s561 cs2( s300, L"less", pl2, NULL );
eq = s591::s600( &cs2, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
eq->s500( s879, false );
s1200 = s1151;
s325 = start->s352();
s1262();}
s1144 s951::s1194(){
s1::s1289<Iterator> it = this;
s1::s1289<Iterator> it1 = it;
return make_pair( it, it1 );}
bool s951::s1979() const{
if( (bool)*eq.s15<s591*>()->s497( 0, 0 ) )
return true;
return false;}
Iterator* s951::s314( s385* r ){
set->s497( 0, 0 );
s1047 = true;
return this;}
s271* s951::s315(){
if( s1047 )
s1047 = false;
else
s1058->s497( 0, 0 );
if(! (bool)*eq->s497( 0, 0 ) )
return NULL;
s989.s15<s483*>()->s356( s1659 );
s1659->s1262();
return s1659;}
void s951::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s951::s1236, s1416,
{ s1122( { s1151 } ), s1122( { s1151, s1151 } ), s1122( { s1151, s1151, s1151 } ) }, 
1, 2 ) ) );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s271* s951::Idx(){
return s1659; }
bool s951::operator==( const Iterator* p ) const{
return false;}
bool s951::operator<( const Iterator* p ) const{
return this < p;}
inline void s951::s1236( s483** s274, size_t s498 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
*s274 = ( s483* ) new s951( ( (s951*)s274[1] )->s300, NULL, v );
s274[0]->s500( ((s951*)s274[1])->ns );}
s271* s951::s335( s591* s2057, s272* impl ) const{
return new s951( *this );}
void s951::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"SequenceGenerator : " << endl;
start->s304( pd, s197 + s419); buf << L", "; end->s304( pd, 0); 
buf << L", "; incr->s304( pd, 0 );}
s1061 s1512::s1507 = 0;
s1061 s1512::s1506 = 0;
s1061 s1512::s1508 = 0;
bool _cmp( const s485& l_, const s485& r_ ){
s483* l = l_.s15<s483*>();
s483* r = r_.s15<s483*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s485 l, const s485 r ) const{
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
struct s1156{
std::vector<s485>s861;
s488 s859;
s1156( /*s488 s860*/ ) : s859( /*s860*/0 ) { s861.resize( 2 ); }
bool operator()( const s485& l, const s485& r ){
if( s859.s14() ) {
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
Iterator* s326::s1164( const s483* idx ){
throw new s16( L"this iterable type doesn't support access by index" );}
Iterator* s326::s1183( const s483* idx ){
throw new s16( L"this iterable type doesn't support search for value" );}
Iterator* s326::s1238( const s483* idx ){
throw new s16( L"this iterable type doesn't support distancing between elements" );}
s483* s326::s1190( Iterator* ){
throw new s16( L"this iterable type doesn't support indexing" );}
struct s840;
s483* s326::sort( bool, s840* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s875 );}
template <class _Cont, class s1311, class Der>
s313<_Cont, s1311, Der>::s313( const s1170& r )
: s326( r ){}
void s1161( s262* s300, const wstring& s77, wstring& s1273, wstring& s644 ){
assert( !s77.empty() );
wstring sv = s77;
wsmatch s1074, rgres1;
wregex s1255( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
wregex s1256( LR"regex(^(\w+(?:<[^\(]*>)?)\s*\(\s*([\w\W]*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1074, s1256 ) ) {
s813::Cont vt;
s1273 = s1074[1].str();
if( regex_match( sv, rgres1, s1255 ) ) {
s644 = L"] " + //s1273 + L" " +
( s1074[s1074.size()-1].str().empty() ? L"0" : s1074[s1074.size()-1].str() );}
else {
s644 = s1074[2];}}}
s1143::s1143( s262* s300, s1905& s77, const s263* ast_ )
: s336( s300, NULL, ast_ ), s325( 0 ){
s493 = Types.Position;
s1679( s7::s868 );}
s1143::s1143( const s1143& right, const s263* ast_ )
: s336( right.s300, right.ns, ast_ ), s588( right.s588 ), s349( right.s349 ),
s325( right.s325 ){
s493 = right.s493;
s1262();}
s1143::s1143( s262* s300, s272* s588, Iterator* it, const s263* ast_ )
: s336( s300, NULL, ast_ ), s349( it ), s325( 0 ){
s493 = Types.Position;
s1262();}
s483* s1143::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
wstring s347 = s353();
if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
wstring sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong Position constructor syntax" );
wstring s696 = L"Malformed Position declaration: " + s;
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
if( s697 )
throw new s16( s696 );
return s355( s588, vector<s271*>(), &s701 );}
else
return NULL;}
void s1143::s500( const s272* s879, bool ){
if( s349.s14() && !s325 ) {
s325 = s349->ValType();
s813::Cont v = { s1580, 1, s325, 0 };
s493 = s300->TR().s1046( v );
if( s493 == s1580 ) {
s813::Cont v = { s1580, 1, s325, 0 };
s493 = s300->TR().s1046( v );}}}
s1061 s1143::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get-el" )
s685 = s325;
return s685;}
s483* s1143::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1143( s300, L"", ast_ );}
s483* s1143::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s813::Cont s1103;
s491::s2119( vt, idx, s1103 );
s1143* s685 = new s1143( s300, 0, NULL );
s685->ns = s588;
s685->s325 = s1103[0];
s813 s619( vt );
s685->s493 = s300->TR().s1011( vt );
return s685;}
void s1143::s350(){
s348.insert( std::make_pair( L"is-end", new s337( L"is-end", &s1143::s1980, s1148,
{ s1122( {s7::s1394} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"eq", new s337( L"eq", &s1143::s398, s1148,
{ s1122( {s7::s1394} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"get-el", new s337( L"get-el", &s1143::s1589, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"get-idx", new s337( L"get-idx", &s1143::s1746, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"neq", new s337( L"neq", &s1143::s403, s1148,
{ s1122( {s7::s1394} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"set", new s337( L"set", &s1143::s387, s1152,
{ s1122( {s7::s1394} ) }, 1, 1 ) ) );
s348.equal_range( L"get-el" ).first->second->s1261( true );}
s271* s1143::s335( s591* s2057, s272* impl ) const{
return new s1143( *this );}
void s1143::s356( s271* p ) const{
p = new s1143( *this );}
size_t s1143::s322() const{
return (size_t)this;}
void s1143::operator=( const s1143& p ){
s588 = p.s588;
s349 = p.s349;
s325 = p.s325;
s493 = p.s493;}
bool s1143::operator==( const s483* p ) const{
return s349->operator==( ((s1143*)p)->s349 );}
bool s1143::operator<( const s483* p ) const{
return s349->operator<( ((s1143*)p)->s349 );}
#undef s698
#define s698 ((s1143*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
inline void s1143::s1980( s483** s274, size_t s498 ){
*((s360*)*s274)->s357() = ((s1143*)DR )->s349->s1979();}
inline void s1143::s1589( s483** s274, size_t s498 ){
*s274 = (s483*)((s1143*)DR )->s349->s962();}
inline void s1143::s1746( s483** s274, size_t s498 ){
*s274 = (s483*)((s1143*)DR )->s349->Idx();}
inline void s1143::s398( s483** s274, size_t s498 ){
*s699->s357() = ( (s1143*)DR )->s349->operator==( ( (s1143*)s274[2] )->s349 );}
inline void s1143::s403( s483** s274, size_t s498 ){
*s699->s357() = !( (s1143*)DR )->s349->operator==( ( (s1143*)s274[2] )->s349 );}
inline void s1143::s387( s483** s274, size_t s498 ){
*(s1143*)DR = *(s1143*)s274[2];}
void s1143::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Position : " <<
this << endl;}
s964::s964( s262* s300, s316* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1213( (uint64_t)-1 ), s1173( new s1529(NULL, -1) ){
if( v.s14() ) {
s1213 = std::distance( v->s320().begin(), it );
assert( s1213 >= 0 );}}
s964::s964( s262* s300, s316* v_, s1247 it, s1247 sent )
: v( v_ ), s1258( it ), s1488( sent ), s1213( (uint64_t)-1 ), s1173( new s1529(NULL, -1) ){
if( v.s14() ) {
s1213 = v->size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1213 >= 0 );}
s884 = true;}
s964::s964( s964* it )
: v( it->v ), s1214( it->s1214 ), s1213( it->s1213 ), s1173( new s1529(NULL, 0) ){
s884 = it->s884;}
void s964::reverse(){
s884 = true; 
s1258 = std::make_reverse_iterator( s1214 );}
s271* s964::s315(){
s271* s685 = NULL;
if( !s884 ) {
if( s1214 != s1086 ) {
s685 = *s1214;
s1214++;
s1213++;}}
else {
if( s1258 != s1488 ) {
s685 = *s1258;
s1258++;
s1213--;}}
return s685;}
s271* s964::s962(){
return El();}
const s271* s964::s962() const{
if( !s884 ) {
if( s1214 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1214;}
else {
if( s1258 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1258;}}
bool s964::s1979() const{
if( !s884 )
return s1214 == v->s320().end();
return s1258 == v->s320().rend();}
s271* s964::Idx(){
*s1173->s357() = s1213 - 1;
return s1173;}
s271* s964::El(){
if( !s884 ) {
if( s1214 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1214;}
else {
if( s1258 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1258;}}
s1061 s964::ValType() const{
return v->ValType();}
bool s964::operator==( const Iterator* r ) const{
if( !s884 ) {
return s1214 == ( (s964*)r )->s1214;}
else {
return s1258 == ( (s964*)r )->s1258;}}
bool s964::operator<( const Iterator* r ) const{
if( !s884 ) {
if( s1214 == v->s320().end() )
return false;
return s1214 < ( (s964*)r )->s1214;}
else {
if( s1258 == v->s320().rend() )
return false;
return s1258 < ( (s964*)r )->s1258;}}
s961::s961( s262* s300, 
s750* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1213( (uint64_t)-1 ), s1173( new s1529( NULL, 0 ) ){
if( v.s14() ) {
s1213 = std::distance( v->s320().begin(), it );
assert( s1213 >= 0 );}}
s961::s961( s961* it )
: v( it->v ), s1214( it->s1214 ), s1213( it->s1213 ), s1173( new s1529( NULL, 0 ) ){}
bool s961::s1979() const{
return s1214 == v->s320().end();}
s271* s961::s315(){
s271* s685 = NULL;
if( s1214 != v->s320().end() ) {
s685 = *s1214;
++s1214;
++s1213;}
return s685;}
s271* s961::s962(){
return *s1214;}
const s271* s961::s962() const{
return *s1214;}
s271* s961::Idx(){
*s1173->s357() = s1213 - 1;
return s1173;}
s271* s961::El(){
*s1173->s357() = s1213 - 1;
return s1173;}
s1061 s961::ValType() const{
return v->ValType();}
s938::s938( s262* s300, s324* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1173( s365 ), s1172( new s959( s300,
vector<s271*>(	{ 
it->first->s503()->s355( s300 ), 
it->second->s503()->s355( s300 ) } ) ) ) // ???DEBUG??? 220514
{
s1172->s500( s300, true );}
s938::s938( s938* it )
: v( it->v ), s1214( it->s1214 ), s1173( s365 ), s1172( new s959( it->s1172->Pass(), 
vector<s271*>(	{ 
s1214->first->s503()->s355( it->s1172->Pass() ),
s1214->second->s503()->s355( it->s1172->Pass() ) } ) ) ) // ???DEBUG??? 220514
{
s1172->s500( it->s1172->Pass(), true );}
bool s938::s1979() const{
if( !s884 )
return s1214 == v->s320().end();
return s1258 == v->s320().rend();}
s271* s938::s315(){
s271* s685 = NULL;
if( s1214 != s1086 ) {
s685 = El(); // ???DEBUG??? 220514
++s1214;}
return s685;}
s271* s938::s962(){
return (*s1214).second.s15<s484*>();}
const s271* s938::s962() const{
return (*s1214).second.s15<s484*>();}
s271* s938::Idx(){
return s1172->s320().at(0).s15<s484*>(); // ???DEBUG??? 220514
}
s271* s938::El(){
s271* s685 = NULL;
if( s1214 != v->s320().end() ) {
s1172->assign( vector<s485>(
{ ( *s1214 ).first.s15<s271*>(),( *s1214 ).second.s15<s271*>() } ));
s685 = s1172; //s1214->second; // ???DEBUG??? 220514
}
return s685;}
void s938::reverse(){
s884 = true;
s1258 = std::make_reverse_iterator( s1214 );}
s1061 s938::ValType() const{
return v->ValType();}
bool s938::operator==( const Iterator* r ) const{
if( !s884 )
return s1214 == ( (s938*)r )->s1214;
else
return s1258 == ( (s938*)r )->s1258;}
s1383::s1383( s262* s300, s1382* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1173( s365 ), s1172( new s959( s300,
vector<s271*>( {
s300->TR().s518( v_->s937(), s300, v_->s2171() ),
s300->TR().s518( v_->ValType(), s300, v_->s2171() )
} ) ) ){
s1172->s500( s300, true );}
s1383::s1383( s1383* it )
: v( it->v ), s1214( it->s1214 ), s1173( s365 ), s1172( new s959( it->s1172->Pass(),
vector<s271*>( {
s1214->first->s503()->s355( it->s1172->Pass() ),
s1214->second->s503()->s355( it->s1172->Pass() ) } ) ) ){
s1172->s500( it->s1172->Pass(), true );}
bool s1383::s1979() const{
return s1214 == v->s320().end();}
s271* s1383::s315(){
s271* s685 = NULL;
if( s1214 != s1086 ) {
s685 = El();
++s1214;}
return s685;}
s271* s1383::s962(){
return ( *s1214 ).second.s15<s484*>();}
const s271* s1383::s962() const{
return ( *s1214 ).second.s15<s484*>();}
s271* s1383::Idx(){
return s1172->s320().at( 0 ).s15<s484*>(); // ???DEBUG??? 220514
}
s271* s1383::El(){
s271* s685 = NULL;
if( s1214 != v->s320().end() ) {
s1172->assign( vector<s485>(
{ ( *s1214 ).first.s15<s271*>(),( *s1214 ).second.s15<s271*>() } ) );
s685 = s1172;}
return s685;}
s1061 s1383::ValType() const{
return v->ValType();}
bool s1383::operator==( const Iterator* r ) const{
return s1214 == ( (s1383*)r )->s1214;}
s2223::s2223( s262* s300, s2222* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ){}
s2223::s2223( s262* s300, s2222* v_, s1247 it, s1247 sent )
: v( v_ ), s1258( it ), s1488( sent ){}
s2223::s2223( s2223* it )
: v( it->v ), s1214( it->s1214 ){}
bool s2223::s1979() const{
if( !s884 )
return s1214 == v->s320().end();
return s1258 == v->s320().rend();}
s271* s2223::s315(){
s271* s685 = NULL;
if( s1214 != s1086 ) {
s685 = El(); // ???DEBUG??? 220514
++s1214;}
return s685;}
s271* s2223::s962(){
return El();}
const s271* s2223::s962() const{
return ((s2223*)this)->El();}
s271* s2223::Idx(){
throw new s16( L"container is not indexable" );}
s271* s2223::El(){
if( !s884 ) {
if( s1214 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1214->s15<s271*>();}
else {
if( s1258 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1258->s15<s271*>();}}
void s2223::reverse(){
s884 = true;
s1258 = std::make_reverse_iterator( s1214 );}
s1061 s2223::ValType() const{
return v->ValType();}
bool s2223::operator==( const Iterator* r ) const{
if( !s884 )
return s1214 == ( (s2223*)r )->s1214;
else
return s1258 == ( (s2223*)r )->s1258;}
s1293::s1293( s262* s300, s1292* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1213( (uint64_t)-1 ), s1173( new s1529( NULL, -1 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1213 = std::distance( v->s320().begin(), it );
assert( s1213 >= 0 );}}
s1293::s1293( s262* s300, s1292* v_, s1247 it, s1247 sent )
: v( v_ ), s1258( it ), s1488( sent ), s1213( (uint64_t)-1 ), s1173( new s1529( NULL, -1 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1213 = v->size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1213 >= 0 );}
s884 = true;}
s1293::s1293( s1293* it )
: v( it->v ), s1214( it->s1214 ), s1213( it->s1213 ), s1173( new s1529( NULL, 0 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, new s1295( NULL, *s1214)  } ) ) ){
s884 = it->s884;}
void s1293::reverse(){
s884 = true;
s1258 = std::make_reverse_iterator( s1214 );}
bool s1293::s1979() const{
if( !s884 )
return s1214 == v->s320().end();
return s1258 == v->s320().rend();}
s271* s1293::s315(){
s271* s685 = NULL;
if( !s884 ) {
if( s1213 < v->s320().size() )
s685 = new s1295( NULL, v->s320()[s1213++] );}
else {
if( s1213 != U64_MAX )
s685 = new s1295( NULL, v->s320()[s1213--] );}
return s685;}
s271* s1293::s962(){
return new s1295( NULL, *s1214 );}
const s271* s1293::s962() const{
return new s1295( NULL, *s1214 );}
s271* s1293::Idx(){
*s1173->s357() = s1213 - 1;
return s1173;}
s271* s1293::El(){
*s1173->s357() = s1213 - 1;
return s1173;}
s1061 s1293::ValType() const{
return v->ValType();}
bool s1293::operator==( const Iterator* r ) const{
if( !s884 )
return s1214 == ( (s1293*)r )->s1214;
else
return s1258 == ( (s1293*)r )->s1258;}
bool s1293::operator<( const Iterator* r ) const{
if( !s884 )
return s1214 < ( (s1293*)r )->s1214;
else
return s1258 < ( (s1293*)r )->s1258;}
s1578::s1578( s262* s300, s359* v_, s939 it, s939 sent )
: v( v_ ), s1214( it ), s1086( sent ), s1213( (uint64_t)-1 ), s1173( new s1529( NULL, -1 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1213 = std::distance( v->s320().begin(), it );
assert( s1213 >= 0 );}}
s1578::s1578( s262* s300, s359* v_, s1247 it, s1247 sent )
: v( v_ ), s1258( it ), s1488( sent ), s1213( (uint64_t)-1 ), s1173( new s1529( NULL, -1 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1213 = v->s320().size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1213 >= 0 );}
s884 = true;}
s1578::s1578( s1578* it )
: v( it->v ), s1214( it->s1214 ), s1213( it->s1213 ), s1173( new s1529( NULL, 0 ) ),
s1172( new s959( NULL, vector<s271*>( { s1173, new s1573( NULL, *s1214)  } ) ) ){
s884 = it->s884;}
void s1578::reverse(){
s884 = true;
s1258 = std::make_reverse_iterator( s1214 );}
bool s1578::s1979() const{
if( !s884 )
return s1214 == v->s320().end();
return s1258 == v->s320().rend();}
s271* s1578::s315(){
s271* s685 = NULL;
if( s1214 != v->s320().end() ) {
s685 = new s1573( NULL, *s1214++ );
++s1213;}
return s685;}
s271* s1578::s962(){
return new s1573( NULL, *s1214 );}
const s271* s1578::s962() const{
return new s1573( NULL, *s1214 );}
s271* s1578::Idx(){
*s1173->s357() = s1213 - 1;
return s1173;}
s271* s1578::El(){
*s1173->s357() = s1213 - 1;
return s1173;}
s1061 s1578::ValType() const{
return v->ValType();}
bool s1578::operator==( const Iterator* r ) const{
if( !s884 )
return s1214 == ( (s1578*)r )->s1214;
else
return s1258 == ( (s1578*)r )->s1258;}
bool s1578::operator<( const Iterator* r ) const{
if( !s884 )
return s1214 < ( (s1578*)r )->s1214;
else
return s1258 < ( (s1578*)r )->s1258;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
vector<wstring> s1310( { L":typedTable", L":untypedTable" } );
s316::s316( s262* s300, s272* s588, const wstring& s77, const s263* ast_,
const s1695& s1759 )
: s1576( s300, s588, ast_ ){
s1200 = s1151;
if( s77.size() )
load( s77, s588, s1759 );
if( !s493 )
s493 = Types.Vector;}
s316::s316( const s316& right, s272* _ns, const s263* ast_ )
: s1576( right.s300, _ns, ast_ ){
s349.resize( right.s349.size() );
for( size_t n = 0; n < right.s349.size(); ++n )
s349[n] = (s483*)right.s349[n]->s335( NULL, _ns );
s1200 = right.s1200;
s325 = right.s325;
s317 = right.s317;
s493 = right.s493;
s1679( right.s618() );}
s316::s316( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1061 s709,	s1061 s1276 )
: s1576( s300, s588, ast_ ){
s1200 = s1151;
s325 = s1276;
s317 = s1276;
if( s709 )
s493 = s709;
else
s493 = Types.Vector;
if( l.size() )
s591::s1242( ( vector<s271*>& )l, s1310 );
if( l.size() ) {
if( l[0]->s352() == s352() ||	l[0]->s352() == s1719 ) {
s349.assign( ( (s316*)l[0] )->s349.begin(),
( (s316*)l[0] )->s349.end() );}
else if( l[0]->s352() == s1151 ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, L"] " + l[0]->to_wstring() ) );}}}
s316::s316( s262* s300, s1061 s1277, s272* s588, const s263* ast_ )
: s1576( s300, s588, ast_ ){
s1200 = s1151;
s325 = s1277;
s317 = s1277;
if( s1277 ) {
s813::Cont v = { s1719, 1, s325, 0 };
s493 = s300->TR().s1046( v );}}
s316::~s316(){
s349.clear();}
void s316::s1313( const vector<s271*>& s705, s272* s588 ){
assert(0);
TDException s968( s7::s1299, s932, s603() );
if( s705.empty() )
return;
s472 pc = s705[0]->s494();
if( pc == s475 && s588->s494() != s476 ) {
throw s968.s1000( L"references are not allowed in constructors of data members" );}
if( s705[0]->s352() == s352() ||
s705[0]->s352() == s1719 ) {
s349.assign( ( (s316*)s705[0] )->s349.begin(),
( (s316*)s705[0] )->s349.end() );}}
void s316::s1160( s1905& s77, s272* s588, const s1695& s1759 ){
assert( !s77.empty() );
wstring s1273, s644, s1266;
if( s77[0] == L'[' ) {
s1266 = s77;}
else {
s1161( s300, s77, s1273, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1266 = s644;
if( !s1273.empty() ) {
s813::Cont s588;
s493 = s1195( this, s1273, s1719, s588 );
s325 = s588[2];}}
if( !s1266.empty() ) {
load( s1266, s588, s1759 );}
else if( !s644.empty() ) {
if( s644[0] == L']' && s644.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, s644, ns ) );}}}
s1061 s316::s1195( s271* s1170, s1905& s1273, s1061 s2236, s813::Cont& s588 ){
s1061 s685;
s813::Cont vt;
size_t pos = 0;
s1061 s1277 = 0;
s1170->Pass()->TR().s1056( s1273, pos, vt );
s685 = s1170->Pass()->TR().s1011( s813( vt ), false );
if( s685 ) {
s588 = { s2236, 1, vt[2], 0 };
return s685;}
s813::Cont s1282( begin( vt ) + 2, end( vt ) );
if( s1282.size() > 2 )
s1277 = s1170->Pass()->TR().s1046( s1282 );
else
s1277 = s1282[0];
s588 = { s2236, 1, s1277, 0 };
s685 = s1170->Pass()->TR().s1046( s588 );
return s685;}
void s316::load( s1905& s77, s272* s588, const s1695& s1759 ){
TDException s968( s7::s1129, s932, s603() );
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( s325, s588, s588->s298() ) );
return;}
size_t pos = 0;
const s945* s1051 = NULL;
if( s603() && s603()->Nqj() )
s1051 = s603()->Nqj()->s1006();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1051, s77, pos, s94, s1759 );
wstring ownerName = s603()->s268( s2100 ).s169();
bool s1326 = false;
if( ( s603()->s268( s2101 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1356 || ownerName.find( s7::s1356 + L"<" ) == 0 ) )
s1326 = true;
if( s94.size() ) {
s1061 pt = 0;
for( size_t n = 0; n < s94.size(); ++n ) {
s947 s225 = new s263( L"", *s94[n], NULL );
s225->s1344( s325 );
s349.push_back( (s483*) s271::s504( *s225, s300, s588, s588->s298() ) );
if( s349.back()->s494() != s475 ) {
if( n == 0 )
pt = s349.back()->s352();
s349.back()->s2198( s2203 );}}
if( !s1326 ) {
if( !s325 && s349[0]->s352() ) {
s325 = s349[0]->s352();
s813::Cont v1 = { s1719, 1, s325, 0 };
s493 = s300->TR().s1046( v1 );}
else if( s325 != s349[0]->s352() )
throw s968.s1000( L"vector's element type doesn't match the vector type" );}}}
s483* s316::s354( const s263& s701, s272* s588, s1905& s334 ) const{
s1061 pt = 0, vt = 0;
wstring sv;
if( !s2229( (s326*)this, s1719, pt, vt, sv, s701, s588, s334 ) )
return NULL;
s316* s685 = new s316( s300, vector<s271*>({ }), s588, &s701,
pt, vt );
s685->load( sv, s588, s1736 );
return s685;}
bool s316::s2229( s326* s1170, s1061 s2236, s1061& pt, s1061& vt, 
wstring& sv, const s263& s701, s272* s588, s1905& s334 ){
wstring s347 = s1170->s353();
TDException s968( s7::s1300, s932, &s701,
L"wrong " + s347 + L" constructor syntax" );
wstring s = s1170->Pass()->TR().s1275( s701.s291(), s334 );
wstring s1273, s644;
if( s701.s268( s2101 ).s169() == L"CallSite" ) {
wstring s1323 = s701.s268( s2100 ).s169();
if( s1323.find( s7::s1356 + L"<" + s347 + L"<" ) == 0 ) {
wstring stype = s1323.substr( s7::s1356.size()+1, s1323.size() - (s7::s1356.size() + 2) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s968.s1000( L"missing element type" );
s1161( s1170->Pass(), s1170->Pass()->TR().s1352( s ), s1273, s644 );
if( !s644.empty() && ( s644[0] == L'[' || s644[0] == L']' ) )
sv = s644;
if( !s1273.empty() ) {
s813::Cont s588;
pt = s1195( s1170, s1273, s2236, s588 );
vt = s588[2];}
else {
pt = vt = 0;}}
else
return false;;
return true;}
void s316::s500( const s272* s879, bool ){
wstring s77 = L"";
TDException s968( s7::s923, s932, s603() );
if( s349.size() == 2 && s349[0].s13() )
s77 = s349[1]->to_wstring();
if( s879->s494() != s476 ||
( (s272*)s879 )->s299() != s7::s1356 || s300->s1330() ) {
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( s325, (s272*)s879, s879->s834() ) );}
else {
for( size_t n = 0; n < s349.size(); ++n ) {
if( s349[n]->s494() == s475 ) {
s349[n]->s500( s879, false );
s349[n] = ( s483* ) s349[n].s15<s371*>()->s377()->s335( NULL, NULL );}
s485 s1088 = s271::s1018( s300, s349[n], (s272*)s879, (s591*)s879, s879->s298(), false );
s349[n] = s1088->s497( 0, 0 ).s15<s271*>();
if( !s325 )
s325 = s349[0]->s352();
else if( s325 != s349[n]->s352() )
throw s968.s1000( L"elements have different types" );}}
if( s493 || s493 == s1719 ) {
if( !s325 )
throw s968.s1000( L"vector's element type is not specified" );
s813::Cont s588 = { s1719, 1, s325, 0 };
s493 = s300->TR().s1046( s588 );}
s1262();}}
void s316::s969( const wstring& s824, const s1720& tbfr, s272* s588,
const s263* ast_ ){
TDException s968( s7::s924, s932, ast_ );
vector<wstring> s805;
s4::s57( s4::s52( s824, s48 ), tbfr.rowSep, s805 );
s1695 s1748 = s1736;
s1748.s1697 = tbfr.s1697;
for( wstring row : s805 ) {
if( !tbfr.mixedTypes ) {
s349.push_back( new s316( s300, s300, row, NULL, tbfr.s1697 ) );}
else {
s959* pd = (s959*)s300->TR().s1007( s325 )->s335(0,0);
pd->load( row, s588, s1748 );
s349.push_back( pd );}}}
void s316::s350(){
s1576<s1418, s485, s316>::s350();
s348 = s1576<s1418, s485, s316>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s316::s1236, s1152,
{ s1122(), s1122( { s7::s1393, s7::s1399 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s348.emplace( make_pair( L"set", new s337( L"set", &s316::s387, s1152,
{ s1122( { s1512::s1507 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"set-el", new s337( L"set-el", &s316::s1264, s1152,
{ s1122( { s1512::s1549, s7::s1397 } ) }, 2, 2, false ) ) );
s348.emplace( make_pair( L"get", new s337( L"get", &s316::s327, 0,
{ s1122( { s1512::s1549 } ) }, 1, 1, true ) ) );
s348.emplace( make_pair( L"append", new s337( L"append", &s316::s1314, s1152,
{ s1122( { s7::s1397 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"sum", new s337( L"sum", &s316::s388, 0,
{ s1122( { s7::s1394, s7::s1399 } ) }, 1, 100 )));
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s316::s393, s1152,
{ s1122( { s7::s1394, s7::s1399 } ) }, 1, 100 )));
s348.emplace( make_pair( L"mul", new s337( L"mul", &s316::s390, 0,
{ s1122( { s1512::s1549 } ) }, 1, 1, true ) ) );
s348.emplace( make_pair( L"erase", new s337( L"erase", &s316::s333, s1152,
{ s1122( { s1512::s1549 } ), s1122( { s1512::s1549, s1512::s1549 } ) }, 1, 2, false ) ) );
s348.emplace( make_pair( L"resize", new s337( L"resize", &s316::s329, s1152,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"reserve", new s337( L"reserve", &s316::s1889, s1152,
{ s1122( { s1512::s1549 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"eq", new s337( L"eq", &s316::s398, s1151,
{ s1122( { s7::s1394 } ) }, 1, 1, true ) ) );
s348.emplace( make_pair( L"for-each", new s337( L"for-each", &s316::s1745, s1152,
{ s1122( { s7::s1398 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"load-table", new s337( L"load-table", &s316::s802,
s1151, { s1122( { s7::s1393, s7::s1399 } ) }, 0, 0, false, { L":mixedTypes", 
L":stringsQuoted", L":promInts", L"colNames", L"fieldSep:", L"rowSep:", L":emptyElements" } ) ) );
s348.equal_range( L"get" ).first->second->s1261( true );
s348.equal_range( s7::s1356 ).first->second->s1261( true );
s348.equal_range( L"sum" ).first->second->s1261( true );
s348.equal_range( L"mul" ).first->second->s1261( true );
s300->TR().s1162( s493, s7::s1412, s1512::s1508 );
s300->TR().s1162( s493, s7::s1410, s1512::s1506 );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s483* s316::s355( s272* s588, const vector<s271*>& l, const s263* ast_ ) const{
if( !s325 )
throw new s16( L"vector's element type is not specified" );
return new s316( s300, l, s588, ast_, s493, s325 );}
s483* s316::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s316* s685 = new s316( s300, 0, NULL );
s685->ns = s588;
s685->s325 = vt[2];
s813 s619( vt );
s685->s493 = s300->TR().s1011( s619 );
return s685;}
s1061 s316::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" )
s685 = s325;
else if( s1553 == s7::s1356 || s1553 == L"sum" || s1553 == L"mul" )
s685 = s493;
else
s685 = s1576::s1188( s1553, l );
return s685;}
inline bool
s316::s501( const s483* s502 ) const{
return ( ( (s316*)s502 )->s325 == s325 );}
s271* s316::s335( s591* s2057, s272* impl ) const{
return new s316( *this, impl, s603() );}
void s316::s356( s271* p ) const{
s316* pv = (s316*)p;
pv->s349.assign( s349.begin(), s349.end() );
pv->s1679( wh );}
s483* s316::s1536( const s483* p ) const{
if( s352() == p->s352() ) {
s483* s685 = (s483*)p->s335(0,0);
return s685;}
else if( s300->TR().s1465( p->s352(), s1512::s1507 ) ) {
const s483* proto = s300->TR().s1007( s317 );
s316* s685 = (s316*)p->s503()->s335( 0, ns );
s685->s493 = s493;
s685->s325 = s325;
if( proto->s494() == s478 ) {
Iterator* s1020 = ( (s326*)p )->s314( NULL );
while( 1 ) {
s485 s2185 = s1020->s315();
if( s2185.s13() )
break;
s685->s349.push_back( proto->s355( ns, vector<s271*>( { s2185 } ), s603() ) );}}
s685->s1262();
return s685;}
throw new s16( L"no conversion from '" + s353() + L"' to '" + p->s353() + L"'" );}
Iterator* s316::s1164( const s483* idx ){
s1418::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s964( s300, this, it, it == s349.end() ? it : it+1 );}
Iterator* s316::s1183( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( it->s15<s483*>()->operator==( _val ) )
return new s964( s300, this, it, it+1 );
return new s964( s300, this, end( s349 ), end( s349 ));}
s483* s316::s1190( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s964*)it )->s1145() );
return new s346( s300, (int)n );}
Iterator* s316::s1185() {
if( s349.size() )
return new s964( s300, this, s349.begin(), s349.begin()+1 ); 
return new s964( s300, this, s349.end(), s349.end() ); }
Iterator* s316::s1189() {
return new s964( s300, this, s349.end(), s349.end() ); }
void s316::add( s484* el ){
s349.push_back( (s483*) el->s335( 0, ns ) );}
#undef s698
#define s698 ((s316*)(s484*)*s274)
inline void s316::s1236( s483** s274, size_t s498 ){
s316* ps = (s316*)DR;
s316* s685;
if( s498 == 2 ) {
s685 = (s316*)( s274[1] )->s335( 0, ps->ns );}
else if( s274[2]->s1196().s352() == s1719 ) {
s685 = (s316*) ps->s1536( s274[2] );}
else if( s274[2]->s1196().s352() == s1415 ) {
auto pr = (s385*)s274[2];
auto rp = pr->s1194();
typename s1386::iterator s1519, s1520;
s1519 = rp.first.s15<s1139*>()->s1145();
s1520 = rp.second.s15<s1139*>()->s1145();
s685 = new s316( ps->s300, vector<s271*>(), ps->ns, ps->s603() );
s685->s349.assign( s1519, s1520 );}
else {
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
s685 = new s316( ps->s300, v, ps->ns, ps->s603(), ps->s493,
ps->s325 );}
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s316::s387( s483** s274, size_t s498 ){
s316* v = ( (s316*)DR );
s326* seq = (s326*)s274[2];
Iterator* s1020 = seq->s314( NULL );
v->s349.clear();
while( 1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
v->s349.push_back( p );}}
inline void s316::s1264( s483** s274, size_t s498 ){
s316* v = ( (s316*)DR );
size_t idx = (size_t)(int)*s274[2];
if( idx >= v->size() )
throw new s16( L"vector index is out of range",
(uint32_t)s16::s17::s24 );
s271* el = v->s349[idx];
s274[3]->s356( el );
el->s1262();}
inline void s316::s327( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
int idx = (int)*s274[2];
if( idx < 0 ) {
idx = (int)pv->s349.size() + idx;
if( idx < 0 )
throw new s16( L"negative index is out of bound" );}
if( idx >= (int)pv->s349.size() )
throw new s16( L"index is out of bound" );
*s274 = (s483*)(s271*)pv->s349[idx];}
inline void s316::s333( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
int idx = (int)*s274[2];
int s163 = 1;
if( s498 > 3 )
s163 = (int)*s274[3];
if( idx >= (int)pv->s349.size() )
throw new s16( L"index is out of bound" );
auto it1 = pv->s349.begin() + idx;
s1418::iterator it2;
if( idx + s163 >= pv->s349.size() )
it2 = pv->s349.end();
else
it2 = pv->s349.begin() + idx + s163;
pv->s349.erase( it1, it2 );}
inline void s316::s1314( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
const s483* s1552 = pv->s300->TR().s1007( pv->s325 );
( (s316*)DR )->s349.push_back( s1552->s1536( s274[2] ) );}
inline void s316::s388( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
s698->s349 = ((s316*)pv)->s349;
for( size_t n = 2; n < s498; ++n )
s698->s349.insert( s698->s349.end(), ((s316*)PARN( n ))->s349.begin(),
((s316*)PARN( n ))->s349.end() );}
inline void s316::s393( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
for( size_t n = 2; n < s498; ++n )
pv->s349.insert( pv->s349.end(), ((s316*)PARN( n ))->s349.begin(),
((s316*)PARN( n ))->s349.end() );}
inline void s316::s1745( s483** s274, size_t s498 ){
using s1130 = s316;
using s939 = s964;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s838* s1763 = (s838*)s274[2];
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename s1386::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
while( s1519 != s1520 ) {
s1763->s596( vector<s485>( { *s1519 } ) );
s1763->s497( 0, 0 );
++s1519;}}
inline void s316::s1889( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
pv->s349.reserve( (int)*s274[2] );}
inline void s316::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
s316* pv = ( (s316*)DR );
int oldsize = (int)( (s316*)DR )->s349.size();
pv->s349.resize( size );
for( int i = oldsize; i < size; ++i ) {
pv->s349[i] = pv->s300->TR().s518( pv->s325, pv->s300, pv->s499 );
pv->s349[i]->s500( pv->ns, true );}}
inline void s316::s390( s483** s274, size_t s498 ){
int s163 = (int)*s274[2];
s316* pv = ( (s316*)DR );
s316* s685 = (s316*)pv->s335( 0, 0 );
for( size_t n = 0; n < s163; ++n ) {
s685->s349.insert( s685->s349.end(), pv->s349.begin(), pv->s349.end() );}
*s274 = s685;}
inline void s316::s398( s483** s274, size_t s498 ){
size_t size = ( (s316*)DR )->s349.size();
s316* right = (s316*)s274[2];
if( right->s349.size() != size ) {
*( (s346*)*s274 )->s357() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( ! right->s349[n].s15<s483*>()->operator==( ( (s316*)DR )->s349[n].s15<s483*>() )) {
*( (s346*)*s274 )->s357() = 0;
return;}}
*( (s346*)*s274 )->s357() = 1;}
inline void s316::s802( s483** s274, size_t s498 ){
s316* pv = ( (s316*)DR );
const wstring& s824 = PARN( 2 )->to_wstring();
s1720 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par_ = s274[n];
s472 pc = par_->s494();
if( pc == s1063 ) {
s485 par;
s489 rf;
rf = par_.s15<s371*>();
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1755 ) {
tbfr.mixedTypes = true;}
else if( rf->Id() == s1753 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1751 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1750 ) {
tbfr.s1697 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1752 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1842 ) {
tbfr.s1826 = true;}
else if( rf->Id() == s1749 ) {
if( s498 < n + 2 )
throw new s16( L"Vector::(load-table): the 'colNames:' value is missing" );
tbfr.s1734 = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Vector::(load-table): unknown parameters" );
++n;}
pv->s969( s824, tbfr, pv->ns, pv->s603() );}
struct s850{
vector<s485>& s349;
s850( vector<s485>& s695 ) : s349( s695 ) {}
bool operator()( const s485 l, const s485 r ) const{
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
s483* s316::sort( bool s884, s840* cmp ){
s850 s849( s349 );
if( s884 ) {
if( cmp )
std::sort( s349.rbegin(), s349.rend(), *cmp );
else
std::sort( s349.rbegin(), s349.rend(), s849 );}
else {
if( cmp )
std::sort( s349.begin(), s349.end(), *cmp );
else
std::sort( s349.begin(), s349.end(), s849 );}
return this;}
wstring s316::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s316::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
bool s2072 = s1934->s2067();
s1934->s2066();
ss << L"[";
if( s618() == s7::s868 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n ) {
s349[n].s15<s483*>()->s1935( s1934 );
if( n < s349.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2072 )
s1934->s2065();}
void s316::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Vector : " << this << endl;
for( size_t n = 0; n < s349.size(); ++n ) {
s349[n]->s304( pd, s197 + s419 );
buf << endl;}}
size_t s316::s322() const{
size_t s685 = 0;
for( size_t n = 0; n < s349.size(); ++n )
s685 = s685 * ( ( s483* )&( *s349[n] ) )->s322() << 1;
return s685;}
bool s316::operator==( const s483* p ) const{
if( ( (s316*)p )->s349.size() != s349.size() )
return false;
for( size_t n = 0; n < s349.size(); ++n )
if( !( ( s271* )&( *s349[n] ) == (s271*)( (s316*)p )->s349[n] ) )
return false;
return true;}
bool s316::operator<( const s483* p ) const{
return false;}
Iterator* s316::s314( s385* rv ){
if( !rv )
return new s964( s300, this, begin( s349 ), end( s349 ) );
s1144 pr = rv->s1194( this );
return new s964( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
s750::s750( s262* s300, s272* s588, const wstring& s77,
const s263* ast_, const s1720& tbfr )
: s326( s300, s588, ast_ ){
if( s77.size() ) {
s1695 s1759;
s1759.s151 = true;
s1759.s1732 = tbfr.stringsQuoted;
s1759.s1744 = tbfr.s1826;
vector<s1::s9<s6::s141>> s153;
const s945* s1051 = NULL;
if( ast_ )
s1051 = ast_->Nqj()->s1006();
if( s77[0] == L'[' ) {
size_t pos = 0;
s6::s178( s1051, s77, pos, s153, s1759 );}
else
s6::s178( s1051, s77, s153, s1759 );
s947 s225;
for( size_t n = 0; n < s153.size(); ++n ) {
s225 = new s263( L"", *s153[n], NULL );
if( ( !tbfr.stringsQuoted && s153[n]->s164() == s134 ) ||
s153[n]->s164() == s139 || s225->s297() == s228 ) {
s225->s1344( Types.String );
s225->s1872( s224::s225 );
s225->s1768( L"\"" + 
s225->s291() + 
L"\"" );}
else if( tbfr.promInts && s153[n]->s164() == s140 )
s225->s1344( s1150 );
if( s225->s291().empty() ) {
if( s1759.s1744 )
s225->s1768( Types( s300, Types.String )->s353() + L"()" );
else
throw new s16( L"empty element in an UntypedVector. To allow"
L" empty elements, use the ':emptyEls' marker." );}
s349.push_back( (s483*) s271::s504( *s225, s300, s588, s588->s298() ) );}}
s493 = s1718;}
s750::s750( s262* s300, const vector<s271*>& l,
const s263* ast_ )
: s326( s300, NULL, ast_ ){
for( auto s1060 : l )
s349.push_back( (s483*)s1060 );
s493 = s1718;}
s750::s750( const s750& right )
: s326( right ){
s349 = right.s349;
s493 = right.s493;}
s750::~s750(){
s349.clear();
s499.clear();}
void s750::s1160( s1905& s77, wstring& s1273, wstring& s644,
vector<s1::s9<s6::s141>>& s94, const s263* ast_, const s1695& s1759 ){
assert( !s77.empty() );
if( s77[0] == L'[' ) {
size_t pos = 0;
const s945* s1051 = NULL;
if( ast_ && ast_->Nqj() )
s1051 = ast_->Nqj()->s1006();
s6::s178( s1051, s77, pos, s94, s1759 );}
else
s1161( s300, s77, s1273, s644 );}
s483* s750::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s701.s291();
wstring sv;
wstring s347 = s353();
if( s.find( L"UVector[" ) == 0 )
sv = s.substr( 7 );
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong vector constructor syntax" );
sv = s4::s52( sv.substr( 1, sv.size() - 2 ), L" " );}
else
return 0;
return new s750( s300, s588, sv, &s701 );}
void s750::s500( const s272* s879, bool ){
for( size_t n = 0; n < s349.size(); ++n ) {
if( s349[n]->s494() == s475 ) {
s349[n]->s500( s879, true );
s349[n] = s349[n].s15<s371*>()->s377();}
s485 s1088 = s271::s1018( s300, s349[n], (s272*)s879, NULL, s879->s298(), false );
s349[n] = s1088;}
s493 = s1718;
s1679( s7::s867 );
s499 = s879->s834();}
void s750::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s750::s387, s1152,
{ s1122( { s1151, s7::s1393, s7::s1399 } ) }, 2, (size_t)-1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s750::s327, 0,
{ s1122( { s1151 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"fst", new s337( L"fst", &s750::s1002, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"snd", new s337( L"snd", &s750::s1075, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"append", new s337( L"append", &s750::s1314, s1152,
{ s1122( { s7::s1393, s7::s1399 } ) }, 1, (size_t)-1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s750::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"resize", new s337( L"resize", &s750::s329, s1152,
{ s1122( { s1151 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s750::s330, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s750::s398, s1151,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"for-each", new s337( L"for-each", &s750::s1745, s1152,
{ s1122( { s7::s1398 } ) }, 1, 1 ) ) );
s348.equal_range( L"get" ).first->second->s1261( true );
s348.equal_range( L"fst" ).first->second->s1261( true );
s348.equal_range( L"snd" ).first->second->s1261( true );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s483* s750::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s750( s300, s588, L"", ast_, s1738 );}
s483* s750::s355( s272* s588, const std::vector<s1061>& vt ) const{
assert( 0 );
return 0;}
s1061 s750::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"fst" )
s685 = s349[0]->s352();
else if( s1553 == L"snd" )
s685 = s349[1]->s352();
else if( s1553 == L"get" ) {
return s7::s1554 + 1;
if( l[0]->s352() != s1151 )
throw new s16( L"individual elements of an UntypedVector can be accessed "
"only by a literal numerical index" );
int n = (int)*l[0];
s685 = s349[n]->s352();}
return s685;}
inline bool
s750::s501( const s483* s502 ) const{
return ( ( (s316*)s502 )->s352() == s352() );}
s1061 s750::s319() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s271* s750::s335( s591* s2057, s272* impl ) const{
return new s750( *this );}
void s750::s356( s271* p ) const{
p = new s750( *this );}
void s750::assign( const vector<s485>& p ){
s349.assign( begin( p ), end( p ) );}
Iterator* s750::s1185() {
if( s349.size() )
return new s961( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s961( s300, this, s349.end(), s349.end() ); }
Iterator* s750::s1189(){
return new s961( s300, this, s349.end(), s349.end() ); }
s1144 s750::s1194(){
return std::make_pair( s1185(), s1189() );}
#undef s698
#define s698 ((s750*)(s484*)*s274)
inline void s750::s387( s483** s274, size_t s498 ){
s274[3]->s356( ( (s750*)DR )->s349[(int)*s274[2]] );}
inline void s750::s327( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[(int)*s274[2]];}
inline void s750::s1002( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[0];}
inline void s750::s1075( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[1];}
inline void s750::s1314( s483** s274, size_t s498 ){
/*if( ( (s750*)DR )->s319() != s274[2]->s495() )
throw new s16( L"unmatched element type" );*/
( (s750*)DR )->s349.push_back( (s483*)s274[2]->s335(0,0) );}
inline void s750::s328( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s750*)DR )->s349.size();}
inline void s750::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
( (s750*)DR )->s349.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s750*)DR )->s349[i] = ( (s750*)DR )->s300->s216(
( (s750*)DR )->s317, ( (s750*)DR )->s499 ).s15<s484*>();*/
}
inline void s750::s330( s483** s274, size_t s498 ){
( (s750*)DR )->s349.clear();}
inline void s750::s1745( s483** s274, size_t s498 ){
using s1130 = s750;
using s939 = s961;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s838* s1763 = (s838*)s274[2];
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename s1386::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
while( s1519 != s1520 ) {
s1763->s596( vector<s485>( { *s1519 } ) );
s1763->s497( 0, 0 );
++s1519;}}
inline void s750::s398( s483** s274, size_t s498 ){
size_t size = ( (s750*)DR )->s349.size();
s750* right = (s750*)s274[2];
if( right->s349.size() != size ) {
*( (s346*)*s274 )->s357() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s750*)DR )->s349[n] ) {
*( (s346*)*s274 )->s357() = 0;
return;}}
*( (s346*)*s274 )->s357() = 1;}
inline void s750::s331( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s750*)DR )->s349.size();}
wstring s750::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"UT[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s750::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
bool s2072 = s1934->s2067();
s1934->s2066();
ss << L"[";
if( s618() == s7::s868 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n ) {
s349[n].s15<s483*>()->s1935( s1934 );
if( n < s349.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2072 )
s1934->s2065();}
void s750::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );}
size_t s750::s322() const{
size_t s685 = 1;
for( size_t n = 0; n < s349.size(); ++n )
s685 = s685 * ( ( s483* )&( *s349[n] ) )->s322() << 1;
return s685;}
bool s750::operator==( const s483* p ) const{
if( ( (s750*)p )->s349.size() != s349.size() )
return false;
for( size_t n = 0; n < s349.size(); ++n ) {
const s483* l = s349[n].s15<s483*>();
const s483* r = ( (const s750*)p )->s349[n].s15<s483*>();
if( !( *l == r ) )
return false;}
return true;}
bool s750::operator<( const s483* p ) const{
return false;}
Iterator* s750::s314( s385* rv ){
return NULL;}
/*s486 s750::s315()
{
if( s318 == s349.end() ) {
return NULL;}
s486 s685 = ( *s318 ).s15<s483*>();
s318++;
return s685;
}*/
s959::s959( s262* s300, s272* s588, s1905& s77, const s263* ast_, const s1695& s1759 )
: s750( s300, s588, ast_ ){
s1200 = s1151;
if( s77.size() ) {
s1160( s77, s588, s1759 );}
if( !s493 )
s493 = Types.Tuple;}
s959::s959( s262* s300, const std::vector<s271*>& l, const s263* ast_ )
: s750( s300, l, ast_ ){
s493 = s1717;}
s959::s959( const s959& right, const s263* ast_ )
: s750( right ){
s349.assign( begin( right.s349 ), end( right.s349 ) );
s493 = right.s493;
s317 = right.s317;
s1200 = right.s1200;
s325 = right.s325;}
s483* s959::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s = s300->TR().s1275( s701.s291(), s334);
wstring sv;
wstring s347 = s353();
if( s.find( L"[[" ) == 0 )
sv = s;// s.substr( 1, s.size() - 2 );
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
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
s959* s685 = new s959( s300, s588, sv, &s701 );
return s685;}
void s959::s500( const s272* s879, bool ){
wstring s77 = L"";
TDException s968( s7::s923, s932, s603() );
if( s349.size() == 2 && s349[0].s13() )
s77 = s349[1]->to_wstring();
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
s947 ast_ = new s263( s77.substr( 9, s77.size() - snum.size() - 10 ), s603()->Nqj(), (s263*)s603() );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( *(s263*)ast_, (s272*)s879, s879->s834() ) );}
else if( s349.size() ) {
s813::Cont s1279;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<";
for( size_t n = 0; n < s349.size(); ++n ) {
if( s349[n]->s494() == s475 ) {
s349[n]->s500( s879 );
s349[n] = s349[n].s15<s371*>()->s377();}
s485 s1088 = s271::s1018( s300, s349[n], (s272*)s879, NULL, s879->s298(), false );
s349[n] = s1088;
ts += s300->TR().s1352( s1088->s353() );
if( n < s349.size() - 1 )
ts += L" ";}
ts += L">";
s493 = s1195( ts, s1279 );}
s1679( s7::s867 );
s499 = s879->s298();}
void s959::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s959::s387, s1152,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s959::s1265, s1152,
{ s1122( { s1512::s1549, s7::s1393, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s959::s327, 0,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"fst", new s337( L"fst", &s959::s1002, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"snd", new s337( L"snd", &s959::s1075, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"append", new s337( L"append", &s959::s1314, s1152,
{ s1122( { s7::s1393, s7::s1399 } ) }, 1, (size_t)-1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s959::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"resize", new s337( L"resize", &s959::s329, s1152,
{ s1122( { s1512::s1549 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s959::s330, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s959::s398, s1151,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"for-each", new s337( L"for-each", &s750::s1745, s1152,
{ s1122( { s7::s1398 } ) }, 1, 1 ) ) );
s348.equal_range( L"get" ).first->second->s1261( true );
s348.equal_range( L"fst" ).first->second->s1261( true );
s348.equal_range( L"snd" ).first->second->s1261( true );}
s483* s959::s355( s272* s588, const std::vector<s1061>& vt ) const{
s959* s685 = new s959( s300, s588, L"" );
s813 s619( vt );
s685->s493 = s685->s317 = s685->s325 = s300->TR().s1011( s619 );
return s685;}
s483* s959::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
s959* s685 = new s959( s300, l, ast_ );
return s685;}
void s959::s1160( const wstring& s77,	s272* s588, const s1695& s1759 ){
assert( !s77.empty() );
wstring s1273, s644, s1266;
if( s77[0] == L'[' ) {
s1266 = s77.substr( 1, s77.size() - 2 );}
else {
s1161( s300, s77, s1273, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1266 = s644.substr( 1, s644.size() - 2 );
if( !s1273.empty() )
s1158( s1273 );}
if( !s1266.empty() ) {
load( s1266, s588, s1759 );}
else if( !s644.empty() ) {
if( s644.find_first_not_of( s4::digits ) == string::npos ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, s644, ns ) );}}}
void s959::s1158( const std::wstring& s1273 ){
s813::Cont vt;
size_t pos = 0;
s300->TR().s1056( s1273, pos, vt );
s813::Cont s1282( begin( vt ), end( vt ) );
if( s1282.size() > 2 )
s325 = s300->TR().s1046( s1282 );
else
s325 = s1282[0];
s493 = s317 = s325;}
s1061 s959::s1195( const std::wstring& s1273, s813::Cont& s588 ){
s1061 s685;
s813::Cont vt;
size_t pos = 0;
s300->TR().s1056( s1273, pos, vt );
s685 = s300->TR().s1011( s813( vt ), false );
if( s685 ) {
s588.assign( vt.begin(), vt.end() );
return s685;}
s685 = s300->TR().s1046( vt );
s588.assign( vt.begin(), vt.end() );
return s685;}
void s959::load( const wstring& s77, s272* s588, const s1695& s1759 ){
TDException s968( s7::s1128, s932, s603() );
size_t pos = 0;
const s945* s1051 = NULL;
if( s603() && s603()->Nqj() )
s1051 = s603()->Nqj()->s1006();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1051, s77, pos, s94, s1759 );
if( s94.size() ) {
s813::Cont s1279;
if( s493 ) {
const s813& vt = s300->TR().s1013( s493 );
s1279.assign( vt.s819().begin(), vt.s819().end() );
if( s94.size() != ( s1279.size() - 2 ) / 2 )
throw s968.s1000( L"wrong number of elements passed for inititalizing tuple" );}
else
s1279.push_back( s1717 );
for( size_t n = 0; n < s94.size(); ++n ) {
s947 s225 = new s263( L"", *s94[n], NULL );
s271* p = NULL;
if( s225->s291().empty() ) {
if( s1759.s1744 && s493 ) {
s225->s1768( s300->TR().s804( s1279[( n + 1 ) * 2] ) + L"()" );
p = s271::s504( *s225, s300, s588, s588->s298() );
p->s1679( s7::s1747 );}}
else {
if( s493 )
s225->s1344( s1279[( n + 1 ) * 2] );
p = s271::s504( *s225, s300, s588, s588->s298() );}
s349.push_back( (s483*) p );
if( s493 ) {
(void)0;}
else {
s1279.push_back( p->s352() );
s1279.push_back( 0 );}}
s1279.insert( s1279.begin() + 1, (s1061)( s1279.size() - 1 ) / 2 );
if( !s325 ) {
s493 = s300->TR().s1046( s1279 );
s325 = s317 = s493;}}
s1262();}
s1061 s959::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"fst" )
s685 = s300->TR().s1013( s493 ).s352( ( 0 + 1 ) * 2 );
else if( s1553 == L"snd" )
s685 = s300->TR().s1013( s493 ).s352( ( 1 + 1 ) * 2 );
else if( s1553 == L"get" ) {
int n = (int)*l[0].s15<s271*>()->s496();
s685 = s300->TR().s1013( s493 ).s352( ( n + 1 ) * 2 );}
return s685;}
bool s959::operator<( const s483* p ) const{
if( ( (s959*)p )->s349.size() != s349.size() )
return false;
for( size_t n = 0; n < s349.size(); ++n ) {
const s483* l = s349[n].s15<s483*>();
const s483* r = ( (const s959*)p )->s349[n].s15<s483*>();
if( !( *l < r ) )
return false;}
return true;}
#undef s698
#define s698 ((s959*)(s484*)*s274)
inline void s959::s387( s483** s274, size_t s498 ){
s959* s823 = ( (s959*)DR );
if( s823->s352() != s274[2]->s352() )
throw new s16( L"mismatched types in assignment expression" );
s274[2]->s356( s823 );}
inline void s959::s1265( s483** s274, size_t s498 ){
s959* s823 = ( (s959*)DR );
size_t idx = (int)*s274[2];
s271* el = s823->s349[idx];
if( ! s274[3]->s1541( el->s352()) )
throw new s16( L"mismatched types in assignment expression" );
s274[3]->s356( ( (s959*)DR )->s349[(int)*s274[2]] );}
inline void s959::s327( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s959*)DR )->s349[(int)*s274[2]];}
inline void s959::s1002( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s959*)DR )->s349[0];}
inline void s959::s1075( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s959*)DR )->s349[1];}
inline void s959::s1314( s483** s274, size_t s498 ){
s959* s823 = ( (s959*)DR );
const s959* pro = (s959*)s823->s300->TR().s1007( DR->s352() );
size_t n = s823->s349.size();
if( n >= pro->s349.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s349[n]->s501( s274[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s750*)DR )->s319() != s274[2]->s495() )
*/
s823->s349.push_back( (s483*)s274[2]->s335(0,0) );}
inline void s959::s328( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s959*)DR )->s349.size();}
inline void s959::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
( (s959*)DR )->s349.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s750*)DR )->s349[i] = ( (s750*)DR )->s300->s216(
( (s750*)DR )->s317, ( (s750*)DR )->s499 ).s15<s484*>();*/
}
inline void s959::s330( s483** s274, size_t s498 ){
( (s959*)DR )->s349.clear();}
inline void s959::s398( s483** s274, size_t s498 ){
size_t size = ( (s959*)DR )->s349.size();
s959* right = (s959*)s274[2];
if( right->s349.size() != size ) {
*( (s346*)*s274 )->s357() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s959*)DR )->s349[n] ) {
*( (s346*)*s274 )->s357() = 0;
return;}}
*( (s346*)*s274 )->s357() = 1;}
inline void s959::s331( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s959*)DR )->s349.size();}
s271* s959::s335( s591* s2057, s272* impl ) const{
return new s959( *this );}
void s959::s356( s271* p ) const{
*p = *this;}
bool s959::s2179( s1905& s ){
if( s.size() < 4 )
return false;
if( s[0] != L'[' || s[1] != L'[' )
return false;
size_t pl = s.rfind( L",[" );
if( pl == string::npos ) {
return ( s[1] == L'[' );}
int s2181 = (int)s4::count( s, L"[", pl, string::npos, true );
int s2182 = (int)s4::count( s, L"]", pl, string::npos, true );
return ( s2182 - s2181 > 1 );}
wstring s959::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"[[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]]";
return s685;}
void s959::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
ss << L"[[";
if( s618() == s7::s868 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n ) {
s349[n].s15<s483*>()->s1935( s1934 );
if( n < s349.size() - 1 )
ss << L", ";}}
ss << L"]]";}
s1292::s1292( s262* s300, s272* s588, const wstring& s77, const s263* ast_,
const s1695& s1759 )
: s1401( s300, s588, ast_ ){
s1160( s77, s588, s1759 );
if( !s493 )
s493 = Types.ByteArray;}
s1292::s1292( const s1292& right, const s263* ast_ )
: s1401( right.s300, NULL, ast_ ){
s349 = right.s349;
s1200 = right.s1200;
s325 = right.s325;
s317 = right.s317;
s493 = right.s493;
wh = right.wh;}
s1292::s1292( s262* s300, const std::vector<s271*>& l, const s263* ast_ )
: s1401( s300, NULL, ast_ ){
s1160( L"", NULL, s1736 );
if( l.size() ) {
s317 = l[0]->s352();
for( size_t n = 0; n < l.size(); ++n )
s349.push_back( *( (s1295*)l[n] )->s357() );}
if( !s493 )
s493 = Types.ByteArray;}
s1292::~s1292(){
s349.clear();}
void s1292::s1160( const wstring& s77, s483* s588, const s1695& s1759 ){
s1200 = s1151;
s325 = s1308;
s813::Cont v = { s1717, 2, s1151, 0, s325, 0 };
s317 = s300->TR().s1046( v );
s493 = s1149;
if( s77.empty() )
return;
wstring s1273, s644, s1266;
if( s77[0] == L'[' ) {
s1266 = s77;}
else {
s1161( s300, s77, s1273, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1266 = s644;
if( s1273 != s353() )
throw new s16( L"wrong syntax of ByteArray declaration" );}
if( !s1266.empty() ) {
load( s1266, s588, s1759 );}
else if( !s644.empty() ) {
if( s644[0] == L']' && s644.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
wstring snum = s644.substr( s644.rfind( L" " ) );
size_t s163 = std::stoi( snum );
s349.resize( s163 );}}}
void s1292::load( s1905& s77, s483* s588, const s1695& s1759 ){
TDException s968( s7::s1298, s932, s603() );
size_t pos = 0;
const s945* s1051 = NULL;
if( s603() && s603()->Nqj() )
s1051 = s603()->Nqj()->s1006();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1051, s77, pos, s94, s1759 );
if( s94.size() ) {
for( size_t n = 0; n < s94.size(); ++n ) {
size_t s163 = s94[n]->s56();
s349.push_back( (tdbyte_t)s163 );}}}
s483* s1292::s354( const s263& s701, s272* s588, s1905& s334 ) const{
TDException s968( s7::s1296, s932, &s701,
L"wrong ByteArray constructor syntax" );
wstring s = s300->TR().s1275( s701.s291(), s334 );
wstring sv;
wstring s347 = s353();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s968.s1000( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1292* s685 = new s1292( s300, s588, sv, &s701 );
return s685;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1321( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1292::s500( const s272* s879, bool ){
s1679( s7::s867 );
if( s879 )
s499 = s879->s834();}
void s1292::s350(){
s1401<s1375, tdbyte_t, s1292, s1295>::s350();
s348 = s1401<s1375, tdbyte_t, s1292, s1295>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1292::s1236, s1149,
{ s1122(), s1122( { s7::s1393, s7::s1399 } ) }, 0, 1 ) ) );
s348.emplace( make_pair( L"set", new s337( L"set", &s1292::s387, s1152,
{ s1122( { s1512::s1507 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"set-el", new s337( L"set-el", &s1292::s1264, s1152,
{ s1122( { s1151, s1151 } ) }, 2, 2 ) ) );
s348.emplace( make_pair( L"get", new s337( L"get", &s1292::s327, s1308,
{ s1122( { s1151 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"append", new s337( L"append", &s1292::s1314, s1152,
{ s1122( { s7::s1397 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"resize", new s337( L"resize", &s1292::s329, s1152,
{ s1122( { s1151 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"eq", new s337( L"eq", &s1292::s398, s1148,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s300->TR().s1162( s493, s7::s1412, s1512::s1508 );
s300->TR().s1162( s493, s7::s1410, s1512::s1506 );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s483* s1292::s355( s272* s588, const vector<s271*>& l, const s263* ast_ ) const{
return new s1292( s300, s588, L"", ast_ );}
s483* s1292::s355( s272* s588, const std::vector<s1061>& vt ) const{
return new s1292( s300, s588, L"" );}
inline bool
s1292::s501( const s483* s502 ) const{
return ( ( (s1292*)s502 )->s352() == s352() );}
s271* s1292::s335( s591* s2057, s272* impl ) const{
return new s1292( *this );}
void s1292::s356( s271* p ) const{
p = new s1292( *this );}
Iterator* s1292::s1164( const s483* idx ){
s1375::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s1293( s300, this, it, it == s349.end() ? it : it + 1 );}
Iterator* s1292::s1183( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( *it == *( (s1295*)_val )->s357() )
return new s1293( s300, this, it, it + 1 );
return new s1293( s300, this, end( s349 ), end( s349 ) );}
s483* s1292::s1190( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s1293*)it )->s1145() );
return new s346( s300, (int)n );}
Iterator* s1292::s1185() {
if( s349.size() )
return new s1293( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s1293( s300, this, s349.end(), s349.end() ); }
Iterator* s1292::s1189() {
return new s1293( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s1292*)(s484*)*s274)
inline void s1292::s1236( s483** s274, size_t s498 ){
s1292* ps = (s1292*)DR;
s1292* s685 = NULL;
if( s498 == 2 ) {
s685 = (s1292*)( s274[1] )->s335(0,0);}
else if( s274[2]->s1196().s352() == s1719 ) {
s316* pv = (s316*)s274[2];
s685 = new s1292( ps->s300, ps->ns, L"", ps->s603() );
for( size_t n = 0; n < pv->s320().size(); ++n ) {
s685->s349.push_back( (int)*pv->s320()[n] );}}
else if( s274[2]->s352() == s1415 ) {
auto pr = (s385*)s274[2];
auto rp = pr->s1194();
typename s1386::iterator s1519, s1520;
s1519 = rp.first.s15<s1139*>()->s1145();
s1520 = rp.second.s15<s1139*>()->s1145();
s685 = new s1292( ps->s300, ps->ns, L"", ps->s603() );
s685->s349.assign( s1519, s1520 );}
else
assert( 0 );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1292::s387( s483** s274, size_t s498 ){
s1292* v = ( (s1292*)DR );
s326* seq = (s326*)s274[2];
s385 range( 0, -1 );
Iterator* s1020 = seq->s314( &range );
while( 1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
v->s349.push_back( *p.s15<s1295*>()->s357() );}}
inline void s1292::s1264( s483** s274, size_t s498 ){
assert( s274[3]->s352() == s1151 );
assert( s274[2]->s352() == s1151 );
s1292* v = ( (s1292*)DR );
size_t idx = (size_t)(int)*s274[2];
v->s349[idx] = *( (s1295*)s274[3] )->s357();}
inline void s1292::s327( s483** s274, size_t s498 ){
s1295* s685 = new s1295( ( (s1292*)DR )->s300,
( (s1292*)DR )->s349[(int)*s274[2]] );
*s274 = (s483*)(s271*)s685;}
inline void s1292::s1314( s483** s274, size_t s498 ){
assert( s274[2]->s352() == s1308 );
( (s1292*)DR )->s349.push_back( *( (s1295*)s274[2] )->s357() );}
inline void s1292::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
( (s1292*)DR )->s349.resize( size );}
inline void s1292::s398( s483** s274, size_t s498 ){
size_t size = ( (s1292*)DR )->s349.size();
s1292* right = (s1292*)s274[2];
if( right->s349.size() != size ) {
*( (s360*)*s274 )->s357() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s1292*)DR )->s349[n] ) {
*( (s360*)*s274 )->s357() = false;
return;}}
*( (s360*)*s274 )->s357() = true;}
wstring s1292::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += std::to_wstring( s349[n] ) + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s1292::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1292::s322() const{
size_t s685 = 0;
for( size_t n = 0; n < s349.size(); ++n )
s685 = ( s685 * s349[n] ) << 1;
return s685;}
bool s1292::operator==( const s483* p ) const{
if( ( (s1292*)p )->s349.size() != s349.size() )
return false;
for( size_t n = 0; n < s349.size(); ++n )
if( !( s349[n] == ( (s1292*)p )->s349[n] ) )
return false;
return true;}
bool s1292::operator<( const s483* p ) const{
return false;}
Iterator* s1292::s314( s385* rv ){
s1144 pr = rv->s1194( this );
return new s1293( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
s324::s324( s262* s300, s1061 s1201, s1061 s1276, s1061 s1181,
s1061 s709, s272* s588, const s263* ast_ )
: s1369( s300, s588, ast_ ){
assert( s1201 && s1276 );
this->s1200 = s1201;
s325 = s1276;
if( s1181 )
s317 = s1181;
else {
s813 s1182( s813::Cont( { s1717, 2, s1200, 0, s325, 0 } ) );
s317 = s300->TR().s1011( s1182 );}
if( s709 )
s493 = s709;
else {
s493 = s300->TR().s1046( s813::Cont( { Types.Index, 2, s1201, 0, s1276, 0 } ) );}}
s324::s324( const s324& right, const s263* ast_ )
: s1369( right.s300, right.ns, ast_ ){
s349 = right.s349;
s493 = right.s493;
s1200 = right.s1200;
s325 = right.s325;
s317 = right.s317;
wh = right.wh;}
s324::s324( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1061 s709, s1061 s1181,
s1061 s1638, s1061 s1276 )
: s1369( s300, s588, ast_ ){
s1200 = s1638;
s325 = s1276;
s317 = s1181;
s493 = s709;
if( l.size() && ( l.front()->s352() == s352() ||
l.front()->s352() == Types.Index ) ) {
s349 = ( (s324*)l.front() )->s349;}}
void s324::s1160( s1905& s77, wstring& s1273, wstring& s644,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s945 s1052( L"", true, s1736 );
s1052.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1161( s300, s77, s1273, s644 );}
s483* 
s324::s354( const s263& s701, s272* s588, s1905& s334 ) const{
s1061 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s2229( (s326*)this, s1715, pt, et, vt, kt, sv, s701, s588, s334 ) )
return NULL;
s324* s685 = new s324( s300, vector<s271*>({ }), s588, &s701,
pt, et, kt, vt );
wstring ownerName = s701.s268( s2100 ).s169();
bool s1326 = false;
if( ( s701.s268( s2101 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1356 || ownerName.find( s7::s1356 + L"<" ) == 0 ) )
s1326 = true;
std::function<void(pair<s486, s486>)> s2240 = [s685]( std::pair<s486, s486> pr )
{s685->s349.insert( make_pair( pr.first, pr.second ) ); };
load( s685, sv, s588, L",", s685->s1200, s685->s325, s2240 );
if( !s1326 && s349.size() ) {
if( !s317 && s349.begin()->second->s352() ) {
s685->s317 = s300->TR().s1046( { s1717, 2, s349.begin()->first->s352(), 0,
s349.begin()->second->s352(), 0 } );
s813::Cont v1 = { Types.Index, 2, s349.begin()->first->s352(), 0,
s349.begin()->second->s352(), 0 };
s685->s493 = s300->TR().s1046( v1 );}
else if( s325 != s349.begin()->second->s352() )
throw new s16( L"index' element type doesn't match the index type" );}
return s685;}
bool s324::s2229( s326* s1170, s1061 s2236, s1061& pt, s1061& et, s1061& vt,
s1061& kt, std::wstring& sv, const s263& s701, s272* s588, s1905& s334 ){
wstring s347 = s1170->s353();
wstring s = s1170->Pass()->TR().s1275( s701.s291(), s334 );
wstring si;
wstring s1273, s644;
if( s701.s268( s2101 ).s169() == L"CallSite" ) {
wstring s1323 = s701.s268( s2100 ).s169();
if( s1323.find( s7::s1356 + L"<" + s347 + L"<" ) == 0 ) {
wstring stype = s1323.substr( s7::s1356.size()+1, s1323.size() - ( s7::s1356.size() + 2 ) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
sv = s; // s4::s52( s, L"{}" );
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );
s1161( s1170->Pass(), s, s1273, s644 );
if( !s644.empty() && ( s644[0] == L'{' || s644[0] == L'}' ) )
sv = s644;
if( !s1273.empty() ) {
s813::Cont s588;
pt = s1195( s1170, s1273, s1715, s588, et, kt, vt );}}
else
return false;
return true;}
s1061 s324::s1195( s271* s1170, s1905& s1273, s1061 s2236, s813::Cont& s588,
s1061& et, s1061& kt, s1061& vt ){
s1061 s685;
s813::Cont s1279;
size_t pos = 0;
s262* s2230 = s1170->Pass();
s2230->TR().s1056( s2230->TR().s1352( s1273 ), pos, s1279 );
s685 = s2230->TR().s1011( s813( s1279 ), false );
if( s685 ) {
s813 s1100( s1279 );
kt = s1100.s352( 2 );
vt = s1100.s352( 4 );
s588 = { Types.Index, 2, kt, 0, vt, 0 };
et = s2230->TR().s1046(
s813::Cont( { s1717, 2, kt, 0, vt, 0 } ) );
return s685;}
s813::Cont s1468, s1515;
size_t idx = 2;
s491::s2119( s1279, idx, s1468 );
s813 s1022( s1468[0] );
kt = s2230->TR().s1011( s1022 );
s491::s2119( s1279, idx, s1515 );
if( s1515.size() > 2 )
vt = s2230->TR().s1046( s1515 );
else
vt = s1515[0];
et = s2230->TR().s1046( 
s813::Cont( { s1717, 2, kt, 0, vt, 0 } ) );
s588 = { Types.Index, 2, kt, 0, vt, 0 };
s685 = s2230->TR().s1046( s588 );
return s685;}
void s324::load( s271* s1170, s1905& s77, s272* s588, s1905& s72, s1061& kt, s1061& vt, 
const std::function<void(std::pair<s486,s486>)> s2240 ){
TDException s968( s7::s1597, s932, s1170->s603() );
vector<pair<wstring, s1::s9<s6::s141>>> s94;
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s945 s1052( L"", true, s1736 );
s1052.s170( s77, pos, ob );
ob->s160( s94 );}
if( s94.empty() )
return;
for( size_t n = 0; n < s94.size(); ++n ) {
s947 s975 = new s263( s94[n].first, s1170->s603()->Nqj(), (s263*)s1170->s603() );
s483* s1057 = (s483*)s271::s504( *s975, s1170->Pass(), s588, s588->s298() );
s1057->s1262();
basic_stringstream<wchar_t> s1084;
s94[n].second->s155( &s1084 );
s947 s225 = new s263( s1084.str(), s1170->s603()->Nqj(), (s263*)s1170->s603() );
s483* s1065 = (s483*)s271::s504( *s225, s1170->Pass(), s588, s588->s298() );
s1065->s500( s588, false );
s1065->s1262();
if( !kt ) {
kt = s1057->s352();
vt = s1065->s352();}
if( kt != s1057->s352() || vt != s1065->s352() )
throw s968.s1000( L"incompatible types in the index initialization list" );
s2240( make_pair( s1057, s1065 ) );}}
void s324::s2227( s271* s1170, s1905& s77, s272* s588, s1061& kt, s1061& s2251,
const std::function<void( std::pair<s486, s486> )> s2240 ){
TDException s968( s7::s923, s932, s1170->s603(), L"wrong Index definition" );
s262* s2230 = s1170->Pass();
if( s77.find( L"Index<" ) == 0 ) {
assert( 0 );
s813::Cont vt, s1022, s1103;
size_t pos = 0;
s2230->TR().s1056( s77, pos, vt );
size_t idx = 2;
s491::s2119( vt, idx, s1022 );
s813 s1021( s1022[0] );
kt = s2230->TR().s1011( s1021 );
s491::s2119( vt, idx, s1103 );
s813 s1100( s1103[0] );
s2251 = s2230->TR().s1011( s1100 );}
else if( s77[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s141>> s153;
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s945 s1052( L"", true, s1736 );
s1052.s170( s77, pos, ob );
vector<pair<wstring, s142>> s144;
ob->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s947 s975 = new s263( s144[n].first, s1170->s603()->Nqj(), (s263*)s1170->s603() );
s483* s1057 = (s483*)s271::s504( *s975, s2230, s588, s588->s298() );
basic_stringstream<wchar_t> s1084;
s144[n].second->s155( &s1084 );
s947 s225 = new s263( s1084.str(), s1170->s603()->Nqj(), (s263*)s1170->s603() );
s483* s1065 = (s483*)s271::s504( *s225, s2230, s588, s588->s298() );
if( !kt ) {
kt = s1057->s352();
s2251 = s1065->s352();}
if( kt != s1057->s352() || s2251 != s1065->s352() )
throw s968.s1000( L"incompatible types in the index initialization list" );
s2240( make_pair( s1057, s1065 ) );}}
s1170->s1262();}
void s324::s500( const s272* s879, bool ){
s2227( this, s499, (s272*)s879, s1200, s325,
[this]( std::pair<s486, s486> pr ) {this->s349.insert( make_pair( pr.first, pr.second ) ); } );}
void s324::s350(){
s1369<s1387, s486, s486, s324>::s350();
s348 = s1369<s1387, s486, s486, s324>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s324::s1236, s1152,
{ s1122(), s1122( { s7::s1393, s7::s1399 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s348.insert( make_pair( L"insert", new s337( L"insert", &s324::s332, s1152,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s324::s780, 0,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s324::s327, 0,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get-val", new s337( L"get-val", &s324::s1463, 0,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"values", new s337( L"values", &s324::s2216, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s324::s387, s1152,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s324::s1592, s1148,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s324::s333, s1152,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s324::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.equal_range( L"find" ).first->second->s1261( true );
s348.equal_range( L"get" ).first->second->s1261( true );
s348.equal_range( L"get-val" ).first->second->s1261( true );
s348.equal_range( L"values" ).first->second->s1261( true );
s300->TR().s1162( s493, s7::s1410, s1512::s1506 );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s483* s324::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
assert( 0 );
return NULL;}
s483* s324::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s813::Cont s1022, s1103;
s491::s2119( vt, idx, s1022 );
s813 s1021( s1022[0] );
s1061 s1201 = s300->TR().s1011( s1021 );
s491::s2119( vt, idx, s1103 );
s813 s1100( s1103[0] );
s1061 s1276 = s300->TR().s1011( s1100 );
s1061 s1181 = s300->TR().s1046( s813::Cont { s1717, 2,
s1201, 0, s1276, 0 } );
s324* s685 = new s324( s300, s1201, s1276, s1181, 0, s588, NULL );
return s685;}
else {
assert( 0 );
s813::Cont s992;
s491::s2119( vt, idx, s992 );
s813 s991( s992[0] );
s1061 s1181 = s300->TR().s1011( s991 );
const s813& s1099 = s300->TR().s1013( s1181 );
s813::Cont s1022, s1103;
idx = 2;
s491::s2119( s1099.s819(), idx, s1022 );
s813 s1021( s1022[0] );
s1061 s1201 = s300->TR().s1011( s1021 );
s491::s2119( s1099.s819(), idx, s1103 );
s813 s1100( s1103[0] );
s1061 s1276 = s300->TR().s1011( s1100 );
s324* s685 = new s324( s300, s1201, s1276, s1181, 0, s588, NULL );
return s685;}}
s1061 s324::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" ) {
s685 = s317;}
else if( s1553 == L"get-val" ) {
s685 = s317;}
else if( s1553 == L"values" ) {
s813::Cont s1279;
wstring ts = this->s300->TR().s1352( 
Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, s325 )->s353() + L">" );
s685 = ((s316*)Types( s300, Types.Vector ))->s1195( (s271*)this, ts, s1719, s1279 );}
else
s685 = s1369::s1188( s1553, l );
return s685;}
inline bool
s324::s501( const s483* s502 ) const{
return 0; /* ( ( (s316*)s502 )->s317 == s317 );*/
}
s271* s324::s335( s591* s2057, s272* impl ) const{
return new s324( *this, s603() );}
void s324::s356( s271* p ) const{
p = new s324( *this );}
size_t s324::s322() const{
return (size_t)this;}
bool s324::operator==( const s483* p ) const{
return ( this == p );}
bool s324::operator<( const s483* p ) const{
return false;}
Iterator* s324::s1185() {
auto it = begin( s349 );
return new s938( s300, this, s349.begin(), ++it ); }
Iterator* s324::s1189() {
return new s938( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s324*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
inline void s324::s1236( s483** s274, size_t s498 ){
s324* ps = (s324*)DR;
s324* s685 = NULL;
if( s498 == 2 ) {
s685 = (s324*)( s274[1] )->s335(0,0);}
else if( s274[2]->s1196().s352() == s1715 ) {
s685 = (s324*)( s274[2] )->s335(0,0);}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 ) { return v.push_back( (s271*)s349 ); } );}
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s324::s332( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s324* dr = (s324*)DR;
if( dr->s1200 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s349.insert( make_pair( s152, s349 ) );}
inline void s324::s780( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s324::s327( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
throw new s16( L"key doesn't exist: '" + s274[2]->to_wstring() + L"'" );
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );
s274[0]->s1262();//s500( p->ns, true );
}}
inline void s324::s1463( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() ) {
*s274 = new s959( p->s300, vector<s271*>(
{ (s483*)PARN( 2 ), (s483*)PARN( 3 ) } ) );}
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>()->s335(0,0), it->second.s15<s484*>()->s335(0,0) } ) );}
s274[0]->s1262();//s500( p->ns, true );
}
inline void s324::s2216( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s316* s685 = new s316( p->s300, p->ValType(), p->ns, p->s603() );
s1386::iterator it = p->s349.begin();
vector<s485>& v = s685->s320();
v.resize( p->s349.size() );
size_t idx = 0;
for( ; it != p->s349.end(); ++it )
v[idx++] = it->second.s15<s271*>();
s685->s1262();
*s274 = s685;}
inline void s324::s387( s483** s274, size_t s498 ){
s324* l = (s324*)DR;
s324* right = (s324*)PARN( 2 );
*l = *right;}
inline void s324::s1592( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s324* dr = (s324*)DR;
if( dr->s1200 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1386::iterator it = dr->s349.find( (s483*)PARN( 2 ) );
if( it == dr->s349.end() ) {
s486 s1241 = (s483*)s349->s335(0,0);
s486 s1594 = (s483*)s152->s335(0,0);
dr->s349.insert( make_pair( s1594, s1241 ) );
*s274 = s369;}
else {
it->second = (s483*)s349->s335(0,0);
*s274 = s370;}}
inline void s324::s333( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
p->s349.erase( (s483*)PARN( 2 ) );}
inline void s324::s328( s483** s274, size_t s498 ){}
inline void s324::s331( s483** s274, size_t s498 ){}
Iterator* s324::s314( s385* rv ){
if( !rv )
return new s938( s300, this, begin( s349 ), end( s349 ) );
s1144 pr = rv->s1194( this );
return new s938( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
wstring s324::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"{ ";
for( auto it = begin( s349 ); it != end( s349 ); ++it )
s685 += ( it == begin( s349 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s685 += L" }";
return s685;}
void s324::s1935( Stream* s1934 ) const{
s2231( (s271*)this, s1934, ((s324*)this)->s314( NULL ) );}
void s324::s2231( s271* subj, Stream* s1934, Iterator* it ){
s1500& ss = s1934->s1964();
bool s2072 = s1934->s2067();
s1934->s2066();
ss << L"{";
if( subj->s618() == s7::s868 )
ss << L"_not_set_";
else {
bool s2249 = true;
for( ; ; ) {
s485 s2185 = it->s315();
if( s2185.s13() )
break;
if( !s2249 )
ss << L", ";
else
s2249 = false;
s2185.s15<s959*>()->s320()[0].s15<s483*>()->s1935( s1934 );
ss << L" : ";
s2185.s15<s959*>()->s320()[1].s15<s483*>()->s1935( s1934 );}}
ss << L"}";
if( !s2072 )
s1934->s2065();}
void s324::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Index : " << endl;
for( auto it = begin( s349 ); it != end( s349 ); ++it ) {
buf << s4::fill_n_ch( L' ', s197 ) << it->first->to_wstring() + L" : ";
it->second->s304( pd, s197 + s419 );}}
s1382::s1382( s262* s300, s1061 s1201, s1061 s1276, s1061 s1181,
s1061 s709, s272* s588, const s263* ast_ )
: s1369( s300, s588, ast_ ){
assert( s1201 && s1276 );
this->s1200 = s1201;
s325 = s1276;
if( s1181 )
s317 = s1181;
else {
s813 s1182( s813::Cont( { s1717, 2, s1200, 0, s325, 0 } ) );
s317 = s300->TR().s1011( s1182 );}
if( s709 )
s493 = s709;
else {
s493 = s300->TR().s1046( s813::Cont( { Types.HashIndex, 2, s1201, 0, s1276, 0 } ) );}}
s1382::s1382( const s1382& right, const s263* ast_ )
: s1369( right.s300, NULL, ast_ ){
s349 = right.s349;
s493 = right.s493;
s1200 = right.s1200;
s325 = right.s325;
s317 = right.s317;
wh = right.wh;}
s1382::s1382( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1061 s709, s1061 s1181,
s1061 s1638, s1061 s1276 )
: s1369( s300, s588, ast_ ){
s1200 = s1638;
s325 = s1276;
s317 = s1181;
s493 = s709;
if( l.size() && ( l.front()->s352() == s352() ||
l.front()->s352() == Types.Index ) ) {
s349 = ( (s1382*)l.front() )->s349;}}
void s1382::s1160( const wstring& s77, wstring& s1273, wstring& s644,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s945 s1052( L"", true, s1736 );
s1052.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1161( s300, s77, s1273, s644 );}
s483* 
s1382::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
s1061 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s324::s2229( (s326*)this, s1715, pt, et, vt, kt, sv, s701, s588, s334 ) )
return NULL;
s1382* s685 = new s1382( s300, vector<s271*>( { } ), s588, &s701,
pt, et, kt, vt );
wstring ownerName = s701.s268( s2100 ).s169();
bool s1326 = false;
if( ( s701.s268( s2101 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1356 || ownerName.find( s7::s1356 + L"<" ) == 0 ) )
s1326 = true;
auto s2240 = [s685]( std::pair<s486, s486> pr ) {s685->s349.insert( make_pair( pr.first, pr.second ) ); };
s324::load( s685, sv, s588, L",", s685->s1200, s685->s325, s2240 );
if( !s1326 && s349.size() ) {
if( !s317 && s349.begin()->second->s352() ) {
s685->s317 = s300->TR().s1046( { s1717, 2, s349.begin()->first->s352(), 0,
s349.begin()->second->s352(), 0 } );
s813::Cont v1 = { Types.Index, 2, s349.begin()->first->s352(), 0,
s349.begin()->second->s352(), 0 };
s685->s493 = s300->TR().s1046( v1 );}
else if( s325 != s349.begin()->second->s352() )
throw new s16( L"index' element type doesn't match the index type" );}
return s685;}
void s1382::s500( const s272* s879, bool ){
s324::s2227( this, s499, (s272*)s879, s1200, s325,
[this]( std::pair<s486, s486> pr ) {this->s349.insert( make_pair( pr.first, pr.second ) ); } );}
void s1382::s350(){
s1369<s1381, s486, s486, s1382>::s350();
s348 = s1369<s1381, s486, s486, s1382>::s342();
s348.insert( make_pair( L"insert", new s337( L"insert", &s1382::s332, s1152,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s1382::s780, 0,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s1382::s327, 0,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get-val", new s337( L"get-val", &s1382::s1463, 0,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s1382::s387, s1148,
{ s1122( { s7::s1396, s7::s1397 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s1382::s333, s1152,
{ s1122( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s1382::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.equal_range( L"find" ).first->second->s1261( true );
s348.equal_range( L"get" ).first->second->s1261( true );
s348.equal_range( L"get-val" ).first->second->s1261( true );}
s483* s1382::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
assert( 0 );
return NULL;}
s483* s1382::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s813::Cont s1022, s1103;
s491::s2119( vt, idx, s1022 );
s813 s1021( s1022[0] );
s1061 s1201 = s300->TR().s1011( s1021 );
s491::s2119( vt, idx, s1103 );
s813 s1100( s1103[0] );
s1061 s1276 = s300->TR().s1011( s1100 );
s1061 s1181 = s300->TR().s1046( s813::Cont { s1717, 2,
s1201, 0, s1276, 0 } );
s1382* s685 = new s1382( s300, s1201, s1276, s1181, 0, s588, NULL );
return s685;}
else {
assert( 0 );
s813::Cont s992;
s491::s2119( vt, idx, s992 );
s813 s991( s992[0] );
s1061 s1181 = s300->TR().s1011( s991 );
const s813& s1099 = s300->TR().s1013( s1181 );
s813::Cont s1022, s1103;
idx = 2;
s491::s2119( s1099.s819(), idx, s1022 );
s813 s1021( s1022[0] );
s1061 s1201 = s300->TR().s1011( s1021 );
s491::s2119( s1099.s819(), idx, s1103 );
s813 s1100( s1103[0] );
s1061 s1276 = s300->TR().s1011( s1100 );
s1382* s685 = new s1382( s300, s1201, s1276, s1181, 0, s588, NULL );
return s685;}}
s1061 s1382::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" ) {
s685 = s317;}
else if( s1553 == L"get-s" ) {
s685 = s317;}
return s685;}
inline bool
s1382::s501( const s483* s502 ) const{
return ( s502->s352() == s352() );}
s271* s1382::s335( s591* s2057, s272* impl ) const{
return new s1382( *this );}
void s1382::s356( s271* p ) const{
p = new s1382( *this );}
size_t s1382::s322() const{
return (size_t)this;}
bool s1382::operator==( const s483* p ) const{
return ( this == p );}
bool s1382::operator<( const s483* p ) const{
return false;}
Iterator* s1382::s1185() {
auto it = begin( s349 );
return new s1383( s300, this, s349.begin(), ++it ); }
Iterator* s1382::s1189() {
return new s1383( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s1382*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
inline void s1382::s332( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s1382* dr = (s1382*)DR;
if( dr->s1200 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s349.insert( make_pair( s152, s349 ) );}
inline void s1382::s780( s483** s274, size_t s498 ){
s1382* p = (s1382*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s1382::s327( s483** s274, size_t s498 ){
s1382* p = (s1382*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s1382::s1463( s483** s274, size_t s498 ){
s1382* p = (s1382*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() ) {
*s274 = new s959( p->s300, vector<s271*>(
{ (s483*)PARN( 2 ), (s483*)PARN( 3 ) } ) );}
else {
*s274 = new s959( p->s300, vector<s271*>(
{ it->first.s15<s484*>()->s335(0,0), it->second.s15<s484*>()->s335(0,0) } ) );}}
inline void s1382::s387( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s1382* dr = (s1382*)DR;
if( dr->s1200 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1386::iterator it = dr->s349.find( (s483*)PARN( 2 ) );
if( it == dr->s349.end() ) {
s483* s1241 = (s483*)s349->s335(0,0);
dr->s349.insert( make_pair( (s483*)s152->s335(0,0), s1241 ) );
*s274 = s369;}
else {
it->second = (s483*)s349->s335(0,0);
*s274 = s370;}}
inline void s1382::s333( s483** s274, size_t s498 ){
s1382* p = (s1382*)DR;
p->s349.erase( (s483*)PARN( 2 ) );}
inline void s1382::s328( s483** s274, size_t s498 ){}
inline void s1382::s331( s483** s274, size_t s498 ){}
Iterator* s1382::s314( s385* rv ){
if( !rv )
return new s1383( s300, this, begin( s349 ), end( s349 ) );
s1144 pr = rv->s1194( this );
return new s1383( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
wstring s1382::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"{ ";
for( auto it = begin( s349 ); it != end( s349 ); ++it )
s685 += ( it == begin( s349 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s685 += L" }";
return s685;}
void s1382::s1935( Stream* s1934 ) const{
s324::s2231( (s271*)this, s1934, ((s1382*)this)->s314(NULL) );}
void s1382::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );*/
}
s2222::s2222( s262* s300, s272* s588, s1905& s77, const s263* ast_,
const s1695& s1759 )
: s1576( s300, s588, ast_ ){
if( s77.size() )
load( s77, s588, s1759 );
if( !s493 )
s493 = Types.Vector;}
s2222::s2222( const s2222& right, s272* _ns, const s263* ast_ )
: s1576( right.s300, _ns, ast_ ){
for( auto it = right.s349.begin(); it != right.s349.end(); ++it )
s349.insert( (s483*)(*it)->s335( NULL, _ns ));
s325 = right.s325;
s493 = right.s493;
s1679( right.s618() );}
s2222::s2222( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1061 s709, s1061 s1276 )
: s1576( s300, s588, ast_ ){
s325 = s1276;
if( s709 )
s493 = s709;
else
s493 = Types.Set;
if( l.size() ) {
if( l[0]->s352() == s352() || l[0]->s352() == s2225 ) {
s2221* ps = &( (s2222*)l[0] )->s349;
for( auto it = (*ps).begin(); it != (*ps).end(); ++it )
s349.insert( (s483*)( *it )->s335( NULL, ((s2222*)l[0])->ns ) );}
else if( l[0]->s352() == s1151 ) {
s349.insert( 0 );
s349.insert( new s359( s300, L"] " + l[0]->to_wstring() ) );}}}
s2222::s2222( s262* s300, s1061 s1277, s272* s588, const s263* ast_ )
: s1576( s300, s588, ast_ ){
s325 = s1277;
if( s1277 ) {
s813::Cont v = { s2225, 1, s325, 0 };
s493 = s300->TR().s1046( v );}}
void s2222::s1160( s1905& s77, s272* s588, const s1695& s1759 ){
assert( !s77.empty() );
wstring s1273, s644, s1266;
if( s77[0] == L'[' ) {
s1266 = s77;}
else {
s1161( s300, s77, s1273, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1266 = s644;
if( !s1273.empty() ) {
s813::Cont s588;
s493 = s316::s1195( this, s1273, s2225, s588 );
s325 = s588[2];}}
if( !s1266.empty() ) {
load( s1266, s588, s1759 );}
else if( !s644.empty() ) {
if( s644[0] == L']' && s644.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
s349.insert( 0 );
s349.insert( new s359( s300, s644, ns ) );}}}
s483*
s2222::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
s1061 pt = 0, vt = 0;
wstring sv;
if( !s316::s2229( (s326*)this, s2225, pt, vt, sv, s701, s588, s334 ) )
return NULL;
s2222* s685 = new s2222( s300, vector<s271*>( { } ), s588, &s701,
pt, vt );
s685->load( sv, s588, s1736 );
return s685;}
void s2222::load( s1905& s77, s272* s588, const s6::s1695& s1759 ){
TDException s968( s7::s1129, s932, s603() );
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.insert( s300->TR().s518( s325, s588, s588->s298() ) );
return;}
size_t pos = 0;
const s945* s1051 = NULL;
if( s603() && s603()->Nqj() )
s1051 = s603()->Nqj()->s1006();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1051, s77, pos, s94, s1759 );
wstring ownerName = s603()->s268( s2100 ).s169();
bool s1326 = false;
if( ( s603()->s268( s2101 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1356 || ownerName.find( s7::s1356 + L"<" ) == 0 ) )
s1326 = true;
if( s94.size() ) {
s1061 pt = 0;
for( size_t n = 0; n < s94.size(); ++n ) {
s947 s225 = new s263( L"", *s94[n], NULL );
s225->s1344( s325 );
s271* s1065 = s271::s504( *s225, s300, s588, s588->s298() );
s349.insert( (s483*)s1065 );
if( s1065->s494() != s475 ) {
if( n == 0 )
pt = s1065->s352();
s1065->s2198( s2203 );}}
if( !s1326 ) {
auto it = s349.begin();
if( !s325 && (*it)->s352() ) {
s325 = ( *it )->s352();
s813::Cont v1 = { s1719, 1, s325, 0 };
s493 = s300->TR().s1046( v1 );}
else if( s325 != ( *it )->s352() )
throw s968.s1000( L"vector's element type doesn't match the vector type" );}}}
void s2222::s500( const s272* s879, bool ){
wstring s77 = L"";
TDException s968( s7::s2217, s932, s603() );
s1386::iterator it = s349.begin();
if( s349.size() == 2 && it->s13() ) {
++it;
s77 = (*it)->to_wstring();}
if( s879->s494() != s476 ||
( (s272*)s879 )->s299() != s7::s1356 || s300->s1330() ) {
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.insert( s300->TR().s518( s325, (s272*)s879, s879->s834() ) );}
else {
for( it = s349.begin(); it != s349.end(); ++it ) {
s271* tmp = (*it).s15<s271*>();
if( tmp->s494() == s475 ) {
tmp->s500( s879, false );
tmp = ((s371*)tmp)->s377()->s335( NULL, NULL );}
s271* s1088 = s271::s1018( s300, tmp, (s272*)s879, (s591*)s879, s879->s298(), false );
s1088 = s1088->s497( 0, 0 ).s15<s484*>();
s349.erase( it );
s349.insert( (s483*)s1088 );
if( !s325 )
s325 = s1088->s352();
else if( s325 != s1088->s352() )
throw s968.s1000( L"elements have different types" );}}
if( s493 || s493 == s2225 ) {
if( !s325 )
throw s968.s1000( L"vector's element type is not specified" );
s813::Cont s588 = { s2225, 1, s325, 0 };
s493 = s300->TR().s1046( s588 );}
s1262();}}
void s2222::s350(){
s1576<s2221, s485, s2222>::s350();
s348 = s1576<s2221, s485, s2222>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s2222::s1236, s1152,
{ s1122(), s1122( { s7::s1393, s7::s1399 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s348.emplace( make_pair( L"set", new s337( L"set", &s2222::s387, s1152,
{ s1122( { s1512::s1507 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"insert", new s337( L"insert", &s2222::s332, s1152,
{ s1122( { s7::s1397 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"sort", new s337( L"sort", &s2222::s2247, 0,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.equal_range( s7::s1356 ).first->second->s1261( true );
s300->TR().s1162( s493, s7::s1410, s1512::s1506 );
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );}
s483* s2222::s355( s272* s588, const vector<s271*>& l, const s263* ast_ ) const{
if( !s325 )
throw new s16( L"set's element type is not specified" );
return new s2222( s300, l, s588, ast_, s493, s325 );}
s483* s2222::s355( s272* s588, const std::vector<s1061>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s2222* s685 = new s2222( s300, 0, NULL );
s685->ns = s588;
s685->s325 = vt[2];
s813 s619( vt );
s685->s493 = s300->TR().s1011( s619 );
return s685;}
s1061 s2222::s1188( s1905& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get" )
s685 = s325;
else if( s1553 == s7::s1356 || s1553 == L"sum" )
s685 = s493;
else
s685 = s1576::s1188( s1553, l );
return s685;}
inline bool
s2222::s501( const s483* s502 ) const{
return ( ( (s2222*)s502 )->s325 == s325 );}
s271* s2222::s335( s591* s2057, s272* impl ) const{
return new s2222( *this, impl, s603() );}
void s2222::s356( s271* p ) const{
s2222* pv = (s2222*)p;
pv->s349 = s349;
pv->s1679( wh );}
s483* s2222::s1536( const s483* p ) const{
if( s352() == p->s352() ) {
s483* s685 = (s483*)p->s335( 0, 0 );
return s685;}
else if( s300->TR().s1465( p->s352(), s1512::s1507 ) ) {
const s483* proto = s300->TR().s1007( s317 );
s2222* s685 = (s2222*)p->s503()->s335( 0, ns );
s685->s493 = s493;
s685->s325 = s325;
if( proto->s494() == s478 ) {
Iterator* s1020 = ( (s326*)p )->s314( NULL );
while( 1 ) {
s485 s2185 = s1020->s315();
if( s2185.s13() )
break;
s685->s349.insert( proto->s355( ns, vector<s271*>( { s2185 } ), s603() ) );}}
s685->s1262();
return s685;}
throw new s16( L"no conversion from '" + s353() + L"' to '" + p->s353() + L"'" );}
size_t s2222::s322() const{
return (size_t)this;}
bool s2222::operator==( const s483* p ) const{
return ( this == p );}
bool s2222::operator<( const s483* p ) const{
return false;}
Iterator* s2222::s1185(){
auto it = begin( s349 );
return new s2223( s300, this, s349.begin(), ++it );}
Iterator* s2222::s1189(){
return new s2223( s300, this, s349.end(), s349.end() );}
#undef s698
#define s698 ((s2222*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
inline void s2222::s1236( s483** s274, size_t s498 ){
s2222* ps = (s2222*)DR;
s2222* s685 = NULL;
if( s498 == 2 ) {
s685 = (s2222*)( s274[1] )->s335( 0, 0 );}
else if( s274[2]->s1196().s352() == s2225 ) {
s685 = (s2222*)( s274[2] )->s335( 0, 0 );}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 ) { return v.push_back( (s271*)s349 ); } );}
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s2222::s387( s483** s274, size_t s498 ){
s2222* v = ( (s2222*)DR );
s326* seq = (s326*)s274[2];
Iterator* s1020 = seq->s314( NULL );
v->s349.clear();
while( 1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
v->s349.insert( p.s15<s483*>() );}}
inline void s2222::s332( s483** s274, size_t s498 ){
s483* s349 = (s483*)PARN( 2 );
s2222* dr = (s2222*)DR;
if(  dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted into a Set" );
dr->s349.insert( s349 );}
inline void s2222::s780( s483** s274, size_t s498 ){
s2222* p = (s2222*)DR;
s1386::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = it->s15<s483*>();}}
inline void s2222::s2247( s483** s274, size_t s498 ){
throw new s16( L"method is not implemented" );}
Iterator* s2222::s314( s385* rv ){
if( !rv )
return new s2223( s300, this, begin( s349 ), end( s349 ) );
s1144 pr = rv->s1194( this );
return new s2223( s300, this,
pr.first.s15<s1139*>()->s1145(), pr.second.s15<s1139*>()->s1145() );}
wstring s2222::to_wstring( uint32_t s1565 ) const{
wstring s685 = L"[ ";
for( auto it = begin( s349 ); it != end( s349 ); ++it )
s685 += ( it == begin( s349 ) ? L"" : L", " ) + it->s15<s483*>()->to_wstring();
s685 += L" ]";
return s685;}
void s2222::s1935( Stream* s1934 ) const{
s1500& ss = s1934->s1964();
bool s2072 = s1934->s2067();
s1934->s2066();
ss << L"[";
if( s618() == s7::s868 )
ss << L"_not_set_";
else {
for( auto it = begin( s349 ); it != end( s349 ); ++it ) {
if( it != begin( s349 ) )
ss << L", ";
it->s15<s483*>()->s1935( s1934 );}}
ss << L"]";
if( !s2072 )
s1934->s2065();}
void s2222::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Set : " << this << endl;
for( auto it = s349.begin(); it != s349.end(); ++it ) {
(*it)->s304( pd, s197 + s419 );
buf << endl;}}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
s415::s415( s262* s300, s1905& s77, const s263* ast_ )
: s336( s300, NULL, ast_ ), s754( s300, Types.String, NULL ), s809( s300, Types.String, NULL ){
s493 = Types.s414;
s754.s11();
s809.s11();
s754.s1262();
s809.s1262();}
s415::s415( const s415& right, const s263* ast_ )
: s336( right.s300, right.ns, ast_ ), s754( right.s300, NULL, L"" ), s809( right.s300, NULL, L"" ){
s754 = right.s754;
s809 = right.s809;
s754.s1262();
s809.s1262();
s493 = right.s493;}
s483* s415::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return new s415( s300, L"", &s701 );}
void s415::s500( const s272* s879, bool ){
s1262();}
void s415::s350(){
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1061 s1517 = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s415::s1236, s1907,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"read", new s337( L"read", &s415::s409, s1152,
{ s1122( { Types.String, Types.String } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"read-rec", new s337( L"read-rec", &s415::s1677, s1152,
{ s1122( { Types.String, Types.String } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"reset", new s337( L"reset", &s415::s416, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"files", new s337( L"files", &s415::s417, s1517,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"dirs", new s337( L"dirs", &s415::s990, s1517,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s415::s328, s1151,
{ s1122() }, 0, 0 ) ) );}
s483* s415::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s415( s300, L"", ast_ );}
inline bool
s415::s501( const s483* s502 ) const{
return ( ((s415*)s502)->s352() == s352() );}
s271* s415::s335( s591* s2057, s272* impl ) const{
return s485( new s415( *this ) );}
void s415::s356( s271* p ) const{
p = new s415( *this );}
#undef s698
#define s698 ((s415*)(s484*)*s274)
inline void s415::s1236( s483** s274, size_t s498 ){
s415* s782 = (s415*)DR;
s415* s685 = new s415( s782->s300, L"", s782->s603() );
s685->s500( s782->ns, true );
*s274 = s685;}
void _findFiles( s1905& path, const wregex& rgPatt, vector<wstring>& s40,	vector<wstring>& s41 ){
vector<wstring> s788, s796;
s3::s32( path, L".*", s788, s796 );
for( size_t n = 0; n < s788.size(); ++n ) {
wstring s1676 = path + s788[n];
if( regex_match( s1676, rgPatt ) ) 
s40.push_back( s1676 );}
for( size_t n = 0; n < s796.size(); ++n ) {
if( s796[n] == L".." ||  s796[n] == L"." )
continue;
wstring s1676 = path + s796[n];
s41.push_back( s1676 );
s4::s61( s1676 );
_findFiles( s1676, rgPatt, s40, s41 );}}
inline void s415::s409( s483** s274, size_t s498 ){
wstring path = ((s359*)PARN( 2 ) )->to_wstring();
const wstring& s524 = ((s359*)PARN( 3 ))->to_wstring();
vector<wstring> s788, s796;
s415* s782 = (s415*)DR;
s782->s754.clear();
s782->s809.clear();
if( !s3::s724( path ) )
path = s782->s300->s716() + path;
s4::s61( path );
s3::s32( path, s524, s788, s796 );
std::sort( begin( s788 ), end( s788 ) );
std::sort( begin( s796 ), end( s796 ) );
for( auto f : s788 )
s782->s754.add( new s359( s782->s300, s4::s746( path + f ), s782->ns ) );
for( auto f : s796 )
s782->s809.add( new s359( s782->s300, s4::s746( path + f ), s782->ns ) );}
inline void s415::s1677( s483** s274, size_t s498 ){
wstring path = ( (s359*)PARN( 2 ) )->to_wstring();
const wstring& s524 = ( (s359*)PARN( 3 ) )->to_wstring();
wregex rg( s524 );
vector<wstring> s788, s796;
s415* s782 = (s415*)DR;
s782->s754.clear();
s782->s809.clear();
if( !s3::s724( path ) )
path = s782->s300->s716() + path;
s4::s61( path );
_findFiles( path, rg, s788, s796 );
std::sort( begin( s788 ), end( s788 ) );
std::sort( begin( s796 ), end( s796 ) );
for( auto f : s788 )
s782->s754.add( new s359( s782->s300, s4::s746( f ), s782->ns ) );
for( auto f : s796 )
s782->s809.add( new s359( s782->s300, s4::s746( f ), s782->ns ) );}
inline void s415::s416( s483** s274, size_t s498 ){
s415* s782 = (s415*)DR;
s782->s754.clear();
s782->s809.clear();}
inline void s415::s417( s483** s274, size_t s498 ){
*s274 = &( (s415*)DR )->s754;}
inline void s415::s990( s483** s274, size_t s498 ){
*s274 = &( (s415*)DR )->s809;}
inline void s415::s328( s483** s274, size_t s498 ){
s415* s782 = (s415*)DR;
*( (s346*)*s274 )->s357() = (int)(s782->s754.size() + s782->s809.size());}
wstring s415::to_wstring( uint32_t s1565 ) const{
wstring s685;
for( size_t n = 0; n < s809.size(); ++n )
s685 += ( n ? L" \"" : L"\"" ) + s809[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s754.size(); ++n )
s685 += ( n ? L" \"":L"\"") + s754[n]->to_wstring() + L"\"";
return s685;}
void s415::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Directory : " << endl;
for( size_t n = 0; n < s809.size(); ++n )
s809[n]->s304( pd, s197 + s419 );
for( size_t n = 0; n < s754.size(); ++n )
s754[n]->s304( pd, s197 + s419 );}
size_t s415::s322() const{
size_t s685 = 0;
for( size_t n = 0; n < s809.size(); ++n )
s685 = s685 * ( (s483*)&(s809[n]) )->s322() << 1;
for( size_t n = 0; n < s754.size(); ++n )
s685 = s685 * ( (s483*)&(s754[n]) )->s322() << 1;
return s685;}
bool s415::operator==( const s483* p ) const{
if( ( (s415*)p )->s754.size() != s754.size() )
return false;
if( ( (s415*)p )->s809.size() != s809.size() )
return false;
for( size_t n = 0; n < s754.size(); ++n )
if( !( ( s271* )&( *s754[n] ) == (s271*)( (s415*)p )->s754[n] ) )
return false;
for( size_t n = 0; n < s809.size(); ++n )
if( !( ( s271* )&( *s809[n] ) == (s271*)( (s415*)p )->s809[n] ) )
return false;
return true;}
bool s415::operator<( const s483* p ) const{
return false;}
vector<wstring> s1606( { L":append" } );
s1605::s1605( s262* s300, s272* s592, s591* s593,
const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1616, s701 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s274.assign( l.begin(), l.end() );
s493 = s1152;
s591::s1242( ( vector<s271*>& )l, s1606 );}
void
s1605::s500( const s272* s1672, bool proc ){
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.s272 )->s353() + L">";
s493 = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s591::s500( s1672, proc );}
s486 s1605::s497( s483** s691, size_t s697 ){
s1611( s691, s697 );
s316* pv = s586.s15<s316*>();
wstring s194 = s583[1]->to_wstring();
s194 = s4::s746( s194 );
vector<s9<s143>> s662;
s948 s1051 = new s945( s194 );
s1051->read( s662, /*s7::s1106*/ L"" );
for( size_t m = 0; m < s662.size(); m++ ) {
s1602* po = new s1602( pv->Pass(), this, s662[m], NULL );
pv->add( po );}
return s586;}
s271* s1605::s335( s591* s2057, s272* impl ) const{
return new s1605( *this );}
s1061 s1512::s1505 = 0;
s1061 s1512::s1509 = 0;
s1061 s1512::s1504 = 0;
void Stream::s1461( std::wstring& s153, size_t s1472 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1480( s1905& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1462( std::wstring& s153, s1905& s72 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1481( s1905& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1460( s1322& s153, size_t s1472 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1479( const s1322& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1459( s1322& s153, const s1322& s72 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1478( const s1322& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
void Stream::s1913( wchar_t c ){
throw new s2::s16( L"stream method is not implemented: fill" );}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1567(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1475 )
*s1475 << std::resetiosflags( f );}
template<class s1420, class s1422>
Stream::s1924 s1406<s1420, s1422>::s1930() const{
return s1475->flags();}
template<class s1420, class s1422>
Stream::s1925 s1406<s1420, s1422>::s1931() const{
return s1475->precision();}
template<class s1420, class s1422>
bool s1406<s1420, s1422>::s2067() const{
return s2073;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1929(){
if( s1475 )
*s1475 << std::showpos;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1927(){
if( s1475 )
*s1475 << std::noshowpos;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s2066(){
s2073 = true;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s2065(){
s2073 = false;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1957(){
if( s1475 )
*s1475 << std::boolalpha;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1958(){
if( s1475 )
*s1475 << std::noboolalpha;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1568( int n ){
if( s1475 )
*s1475 << std::setw( n );}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1928( int n ){
if( s1475 )
*s1475 << std::setprecision( n );}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1915(){
if( s1475 )
*s1475 << std::left;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1916(){
if( s1475 )
*s1475 << std::right;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1914(){
if( s1475 )
*s1475 << std::internal;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1926(){
if( s1475 )
*s1475 << std::fixed;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1566(){
if( s1475 )
*s1475 << std::showpos;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1955(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1474 )
*s1474 >> std::resetiosflags( f );}
template<class s1420, class s1422>
Stream::s1924 s1406<s1420, s1422>::s1961() const{
return s1474->flags();}
template<class s1420, class s1422>
Stream::s1925 s1406<s1420, s1422>::s1962() const{
return s1474->precision();}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1951(){
if( s1474 )
*s1474 >> std::boolalpha;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1953(){
if( s1474 )
*s1474 >> std::noboolalpha;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1952(){
if( s1474 )
*s1474 >> std::fixed;}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1956( int n ){
if( s1474 )
*s1474 >> std::setw( n );}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1954( int n ){
if( s1474 )
*s1474 >> std::setprecision( n );}
s507::s507( s262* s300, s272* ns_, const s263* ast_ )
: s1406( s300, ns_, ast_ ){
s493 = Types.s789;
s1474 = (basic_istringstream<wchar_t>*) &ss;
s1475 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s507::s507( const s507& r, const s263* ast_ )
: s1406( r.s300, r.ns, ast_ ), ss( r.ss.str() ){
s493 = Types.s789;
s1474 = (basic_istringstream<wchar_t>*) &ss;
s1475 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s483* s507::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s507( s300, s588, ast_ );}
void s507::s350(){
s1406<s1971,s1972>::s350();
s348 = s1406<s1971, s1972>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s507::s1236, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"str", new s337( L"str", &s507::s508, Types.String,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s507::s330, s1910,
{ s1122() }, 0, 0 ) ) );
s300->TR().s1162( s493, s7::s1409, s1512::s1505 );
s300->TR().s1162( s493, s7::s1414, s1512::s1509 );
s300->TR().s1162( s493, s7::s1408, s1512::s1504 );}
void s507::s500( const s272*, bool ){
s1262();}
void s507::release(){
ss.clear();}
s483* s507::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"StringStream(" ) == 0 )
return new s507( s300, s588, &s701 );
return NULL;}
s271* s507::s335( s591* s2057, s272* impl ) const{
return new s507( *this );}
void s507::s356( s271* p ) const{
if( p->s352() == s1910 )
((s507*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s352() ) );}
void s507::s1461( std::wstring& s153, size_t s1472 ){
s153 = ss.str().substr( 0, s1472 );}
void s507::s1480( s1905& src ){
ss << src;}
void s507::s1462( std::wstring& s153, s1905& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
std::getline( ss, s153, s72[0] );}
void s507::s1481( s1905& src ){
ss << src << endl;}
void s507::s1460( s1322& s153, size_t s1472 ){
s153 = (tdbyte_t*)U8( ss.str().substr( 0, s1472 )).data();}
void s507::s1479( const s1322& src ){
ss << U16( (char*)src.c_str() );}
void s507::s1459( s1322& s153, const s1322& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s72.c_str()) + L"'" );
s153.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s72.c_str())[0]);}
void s507::s1478( const s1322& src ){
ss << U16( (char*)src.c_str() ) << endl;}
void s507::s1913( wchar_t c ){
if( s1475 )
*s1475 << std::setfill( c );}
wstring s507::to_wstring( uint32_t s1565 ) const{
return ss.str(); }
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s507*)(s484*)*s274)
inline void s507::s1236( s483** s274, size_t s498 ){
s507* ps = (s507*)DR;
s507* s685 = new s507( ps->s300, ps->ns, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s507::s508( s483** s274, size_t s498 ){
s507* pst = (s507*)DR;
*( (s359*)s274[0] )->s357() = pst->ss.str();}
inline void s507::s330( s483** s274, size_t s498 ){
((s507*)DR)->ss.rdbuf()->str(L"");}
void s507::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << ss.str() << endl;}
size_t s507::s322() const{
return hash<wstring>{}(ss.str());}
bool s507::operator==( const s483* p ) const{
return ( (s507*)p )->ss.str() == ss.str();}
bool s507::operator<( const s483* p ) const{
return ss.str() < ( (s507*)p )->ss.str();}
s1294::s1294( s262* s300, s272* ns_, const s263* ast_ )
: s1406( s300, ns_, ast_ ){
s493 = Types.ByteStream;
s1474 = (basic_istringstream<tdbyte_t>*) &bs;
s1475 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1294::s1294( const s1294& r, const s263* ast_ )
: s1406( r.s300, r.ns, ast_ ), bs( r.bs.str() ){
s493 = Types.ByteStream;}
s483* s1294::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1294( s300, ast_ );}
void s1294::s350(){
s1406<s1495, s1498>::s350();
s348 = s1406<s1495, s1498>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1294::s1236, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"array", new s337( L"array", &s1294::s1315, Types.String,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s1294::s330, s1906,
{ s1122() }, 0, 0 ) ) );
s300->TR().s1162( s493, s7::s1409, s1512::s1505 );
s300->TR().s1162( s493, s7::s1414, s1512::s1509 );
s300->TR().s1162( s493, s7::s1408, s1512::s1504 );}
void s1294::s500( const s272*, bool ){
s1262();}
void s1294::release(){
bs.clear();}
s483* s1294::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1294( s300 );
return NULL;}
s271* s1294::s335( s591* s2057, s272* impl ) const{
return new s1294( *this );}
void s1294::s356( s271* p ) const{
if( p->s352() == s1906 )
((s1294*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s352() ) );}
void s1294::s1461( std::wstring& s153, size_t s1472 ){
s153 = U16( (char*)bs.str().c_str() ).substr( 0, s1472 );}
void s1294::s1480( s1905& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1294::s1462( std::wstring& s153, s1905& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
s1322 tmp;
std::getline( bs, tmp, (unsigned char)U8(s72.data())[0] );}
void s1294::s1481( s1905& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1294::s1460( s1322& s153, size_t s1472 ){
s153 = bs.str().substr( 0, s1472 );}
void s1294::s1479( const s1322& src ){
bs << src.data();}
void s1294::s1459( s1322& s153, const s1322& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s72.c_str()) + L"'" );
s153.clear();
std::getline( bs, s153, s72[0] );}
void s1294::s1478( const s1322& src ){
bs << src << endl;}
wstring s1294::to_wstring( uint32_t s1565 ) const{
s1322 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1294*)(s484*)*s274)
inline void s1294::s1236( s483** s274, size_t s498 ){
s1294* ps = (s1294*)DR;
s1294* s685 = new s1294( ps->s300, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1294::s1315( s483** s274, size_t s498 ){
s1322 s = ( (s1294*)DR)->bs.str();
( (s1292*)s274[0] )->s320().assign( begin( s ), end( s ) );}
inline void s1294::s330( s483** s274, size_t s498 ){
((s1294*)DR)->bs.rdbuf()->str(0);}
void s1294::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : [...]" << endl;}
size_t s1294::s322() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1294::operator==( const s483* p ) const{
return ( (s1294*)p )->bs.str() == bs.str();}
bool s1294::operator<( const s483* p ) const{
return bs.str() < ( (s1294*)p )->bs.str();}
s1302::s1302( s262* s300, s272* ns_, const s263* ast_ )
: s1406( s300, ns_, ast_ ){
s493 = Types.FileStream;
s1474 = NULL;
s1475 = NULL;}
s1302::s1302( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ )
: s1406( s300, s588, ast_ ){
s493 = Types.FileStream;
s1474 = NULL;
s1475 = NULL;
if( l.size() ) {
if( l[0]->s352() == Types.String )
s1341 = l[0]->to_wstring();
else
s210 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1302::s1302( const s1302& r, const s263* ast_ )
: s1406( r.s300, r.ns, ast_ ), s210( r.s210 ), mode( r.mode ){
s493 = s1908;
s1474 = NULL;
s1475 = NULL;}
s483* s1302::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1302( s300, ast_ );}
void s1302::s350(){
s1406<s1496, s1499>::s350();
s348 = s1406<s1496, s1499>::s342();
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1302::s1236, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"open-r", new s337( L"open-r", &s1302::s2028, s1152,
{ s1122(), s1122( { Types.String } ), s1122( { Types.String, Types.String } ) }, false, s2050 ) ) );
s348.insert( make_pair( L"open-w", new s337( L"open-w", &s1302::s2030, s1152,
{ s1122(), s1122( { Types.String } ), s1122( { Types.String, Types.String } ) }, false, s2050 ) ) );
s348.insert( make_pair( L"open-rw", new s337( L"open-rw", &s1302::s2029, s1152,
{ s1122(), s1122( { Types.String } ), s1122( { Types.String, Types.String } ) }, 0, 2 ) ) );
s348.insert( make_pair( L"close", new s337( L"close", &s1302::s1324, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"read-bytes", new s337( L"read-bytes", &s1302::s2036, s1152,
{ s1122( { s1149 } ), s1122( { s1149, s1151 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"read-lines", new s337( L"read-lines", &s1302::s1484, 0,	
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"read-text", new s337( L"read-text", &s1302::s409, Types.String,	
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"write", new s337( L"write", &s1302::s1355, s1152,
{ s1122( { s1149, s1151 } ) }, 2, 2 ) ) );
s300->TR().s1162( s493, s7::s1409, s1512::s1505 );
s300->TR().s1162( s493, s7::s1414, s1512::s1509 );
s300->TR().s1162( s493, s7::s1408, s1512::s1504 );}
void s1302::s500( const s272*, bool ){
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1061 pt = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s348.equal_range( L"read-lines" ).first->second->s1263( pt );
s1262();}
void s1302::release(){
fs.close();}
s483*
s1302::s354( const s263& s701, s272* s588, s1905& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s271*> s705;
s271::s1333( s701, s300, s588, s334, s705 );
return new s1302( s300, s705, s588, &s701 );}
return NULL;}
s271*
s1302::s335( s591* s2057, s272* impl ) const{
return new s1302( *this );}
void s1302::s356( s271* p ) const{
if( p->s352() == s1908 ) {
((s1302*)p)->s210 = s210;
((s1302*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s353() + L" to " + 
p->s353() );}
void s1302::s1461( std::wstring& s153, size_t s1472 ){
size_t s1111 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1111;
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
enc = s1690;}
else if( c1 == 0xFE && c2 == 0xFF ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1691;}
else if( c1 == 0xFF && c2 == 0xFE ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1692;}
else if( c1 == 0x0 && c2 == 0x0 && c3 == 0xFE && c4 == 0xFF ) {
enc = s1693;
fsz -= 4;}
else if( c1 == 0xFF && c2 == 0xFE && c3 == 0x0 && c4 == 0x0 ) {
enc = s1694;
fsz -= 4;}
else
fs.seekg( 0, ios_base::beg );}
size_t s1503 = s1472 ? ( std::min )( s1472, fsz ) : fsz;
string buf( s1503 + 0, '\0' );
fs.read( &buf[0], s1503 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1341 + L"'" );}
if( !enc || enc == s1690 ) {
s153 = U16( buf );
s153.shrink_to_fit();}
else {
fs.close();
throw new s16( L"file is not in UTF8 encoding and cannot be read as text: '" + s1341 + L"'" );}}
void s1302::s1480( s1905& src ){
fs << U8(src).data();}
void s1302::s1462( std::wstring& s153, s1905& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s153.clear();
if( fs.eof() )
return;
string buf;
char s1471 = U8( s72.data() )[0];
std::getline( fs, buf, s1471 );
s153 = U16( buf.data() );}
void s1302::s1481( s1905& src ){
fs << U8(src).data() << endl;}
void s1302::s1460( s1322& s153, size_t s1472 ){
size_t s1111 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios::end ).tellg() - s1111;
fs.seekg( s1111 );
size_t s1503 = s1472 ? (std::min)( s1472, fsz ) : fsz;
s153.resize( s1503 );
fs.read( (char*)&s153[0], s1503 );}
void s1302::s1479( const s1322& src ){
fs << *(string*)&src;}
void s1302::s1459( s1322& s153, const s1322& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s72.c_str() ) + L"'" );
string buf;
s153.clear();
std::getline( fs, buf, (char)s72[0] );
std::swap( buf, *(string*)(&s153) );}
void s1302::s1478( const s1322& src ){
fs << *(string*)&src << endl;}
wstring s1302::to_wstring( uint32_t s1565 ) const{
return L"FileStream"; }
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1302*)(s484*)*s274)
inline void s1302::s1236( s483** s274, size_t s498 ){
s1302* ps = (s1302*)DR;
s1302* s685 = new s1302( *ps );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
void s1302::s2006( s483** s274, size_t s498, wstring& s1345 ){
s1302* pf = (s1302*)DR;
if( s498 > 2 ) {
if( s274[2]->s352() == Types.String ) {
pf->s1341 = s274[2]->to_wstring();
pf->s210 = NULL;}
else {
pf->s210 = s274[2];
pf->s1341 = L"";}}
s485 s2005;
if( s498 > 3 ) {
s2005 = s274[3];
pf->mode = s2005;}
else
s2005 = pf->mode;
if( s2005.s14() ) {
if( s2005->s494() == s476 )
s1345 = s2005->s497( 0, 0 )->to_wstring();
else if( s2005->s494() != s475 )
s1345 = s2005->to_wstring();
else
s1345 = s2005.s15<s371*>()->s377()->to_wstring();}}
inline void s1302::s2028( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
wstring s1345 = L"r";
s2006( s274, s498, s1345 );
if( s1345 != L"r" )
throw new s16( L"file open mode '" + s1345 + 
L"' is incompatible with '(open-r)' method" );
if( pf->s300->s2012( s2050, s2046 ) )
return;
pf->_open( s1345 );}
inline void s1302::s2030( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
wstring s1345 = L"w";
s2006( s274, s498, s1345 );
if( s1345 != L"w" && s1345 != L"x" && s1345 != L"a" )
throw new s16( L"file open mode '" + s1345 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s2012( s2051, s2046 ) )
return;
pf->_open( s1345 );}
inline void s1302::s2029( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
wstring s1345 = L"r+";
s2006( s274, s498, s1345 );
if( s1345 != L"w" && s1345 != L"x" && s1345 != L"a" )
throw new s16( L"file open mode '" + s1345 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s2012( s2050, s2046 ) || 
pf->s300->s2012( s2051, s2046 ))
return;
pf->_open( s1345 );}
inline void s1302::s1324( s483** s274, size_t s498 ){
((s1302*)DR)->_close();
((s1302*)DR)->s1474 = NULL;
((s1302*)DR)->s1475 = NULL;}
inline void s1302::s1355( s483** s274, size_t s498 ){
assert( s498 == 4 );
assert( s274[2]->s352() == s1149 );
s1302* pf = (s1302*)DR;
if( pf->s300->s2012( s2051, s2046 ) )
return;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1341 + L"'." );
s1292* s1334 = (s1292*)s274[2];
s483* s1336 = s274[3];
int s1349 = (int)*s1336;
pf->fs.write( (const char*)s1334->s320().data(), s1349 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1341 + L"'." );}
inline void s1302::s409( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
if( pf->s300->s2012( s2050, s2046 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s359* s685 = (s359*)*s274;
pf->s1461( s685->s320(), 0 );}
inline void s1302::s2036( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
if( pf->s300->s2012( s2050, s2046 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s1292& bar = *(s1292*)s274[2];
pf->s1460(bar.s320(), 0 );}
inline void s1302::s1484( s483** s274, size_t s498 ){
s1302* pf = (s1302*)DR;
if( pf->s300->s2012( s2050, s2046 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)pf->addr();
s316& v = *(s316*)s698;
string buf;
while(std::getline( fs, buf/*, widen('\n')*/ ) ) {
v.s320().push_back( new s359( pf->s300 ) );
v.s320().back().s15<s359*>()->s1960( U16( buf ) );
v.s320().back()->s1262();
if( fs.eof() )
break;}
if( fs.bad() )
throw new s16( L"cannot read from file '" + pf->s1341 + L"'" );}
void s1302::_open( const wstring& s1345 ){
if( fs.is_open() )
fs.close();
wstring path;
if( !s1341.empty() )
path = s1341;
else {
if( s210->s494() != s475 )
path = s210->to_wstring();
else 
path = s210.s15<s371*>()->s377()->to_wstring();
s1341 = path;}
if( !s3::s724( path ) )
path = s300->s716() + path;
s1474 = NULL;
s1475 = NULL;
std::ios_base::openmode md;
if( s1345.empty() || s1345 == L"r" ) {
md = ios::in | ios::binary;
s1474 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1345 == L"w" || s1345 == L"x" ) {
md = ios::out | ios::binary;
s1475 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1345 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1475 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1345 + L"'." );
if( s1345 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1302::_close(){
mode = s210 = NULL;
s1341.clear();
fs.close();}
void s1302::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s1341 << endl;}
size_t s1302::s322() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1302::operator==( const s483* p ) const{
return this == p;}
bool s1302::operator<( const s483* p ) const{
return this < p;}
s1402::s1402( s262* s300, s272* ns_, const s263* ast_ )
: s1406( s300, ns_, ast_ ){
s1474 = &std::wcin;}
s483* s1402::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1402::s350(){
s348.insert( make_pair( L"get", new s337( L"get", &s1402::s327, s1153,
{ s1122() }, 0, 0 ) ) );
s300->TR().s1162( s493, s7::s1409, s1512::s1505 );}
void s1402::s500( const s272*, bool ){
s1262();}
s483* s1402::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return NULL;}
s271* s1402::s335( s591* s2057, s272* impl ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1402::s356( s271* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1402::s1461( std::wstring& s153, size_t s1472 ){
s153.clear();
wcin >> s153;
if( s1472 && s153.size() > s1472 )
s153.resize( s1472 );}
void s1402::s1480( s1905& src ){
throw new s16( L"cannot output to StdIn" );}
void s1402::s1462( std::wstring& s153, s1905& s72 ){
wcin >> std::ws;
s153.clear();
std::getline( wcin, s153 );}
void s1402::s1481( s1905& src ){
throw new s16( L"cannot output to StdIn" );}
void s1402::s1460( s1322& s153, size_t s1472 ){
wstring buf( s1472, L'\0' );
wcin.read( &buf[0], s1472 );
size_t s685 = wcin.gcount();
buf.resize( s685 );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1402::s1479( const s1322& src ){
throw new s16( L"cannot output to StdIn" );}
void s1402::s1459( s1322& s153, const s1322& s72 ){
wstring buf;
std::getline( wcin, buf );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1402::s1478( const s1322& src ){
throw new s16( L"cannot output to StdIn" );}
inline void s1402::s327( s483** s274, size_t s498 ){
s359* s685 = (s359*)*s274;
wchar_t s153;
wcin.get( s153 );
*s685->s357() = wstring( s153, 1 );}
wstring s1402::to_wstring( uint32_t s1565 ) const{
throw new s16( L"22: not implemented" );}
void s1402::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdIn object" << endl;}
size_t s1402::s322() const{
throw new s16( L"15: not implemented" );}
bool s1402::operator==( const s483* p ) const{
throw new s16( L"16: not implemented" );}
bool s1402::operator<( const s483* p ) const{
throw new s16( L"17: not implemented" );}
s1404::s1404( s262* s300, s272* ns_, const s263* ast_ )
: s1406( s300, ns_, ast_ ){
s1475 = &std::wcout;}
s483* s1404::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1404::s350(){
s300->TR().s1162( s493, s7::s1414, s1512::s1509 );}
void s1404::s500( const s272*, bool ){
s1262();}
s483* s1404::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return NULL;}
s271* s1404::s335( s591* s2057, s272* impl ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1404::s356( s271* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1404::s1461( std::wstring& s153, size_t s1472 ){
throw new s16( L"cannot get input from StdOut" );}
void s1404::s1480( s1905& src ){
wcout << src;}
void s1404::s1462( std::wstring& s153, s1905& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1404::s1481( s1905& src ){
wcout << src << endl;}
void s1404::s1460( s1322& s153, size_t s1472 ){
throw new s16( L"cannot get input from StdOut" );}
void s1404::s1479( const s1322& src ){
wcout << U16( (const char*)src.data() );}
void s1404::s1459( s1322& s153, const s1322& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1404::s1478( const s1322& src ){
wcout << U16( (const char*)src.data() ) << endl;}
void s1404::s1913( wchar_t c ){
if( s1475 )
*s1475 << std::setfill( c );}
wstring s1404::to_wstring( uint32_t s1565 ) const{
throw new s16( L"21: not implemented" );}
void s1404::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdOut object" << endl;}
size_t s1404::s322() const{
throw new s16( L"18: not implemented" );}
bool s1404::operator==( const s483* p ) const{
throw new s16( L"19: not implemented" );}
bool s1404::operator<( const s483* p ) const{
throw new s16( L"20: not implemented" );}
s605::s605( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701,
bool s2177 )
: s591( s300, s592, s593, s593, s565, s233, s701, true, s2177 ){
TDException s968( s7::s1688, s932, s701, L"malformed syntax of 'with' statement" );
size_t n = 0;
bool s1168;
for( ; n < l.size(); n += 2 ) {
s1168 = false;
if( ( (s483*)l[n] ) == s1686 ) {
if( l.size() == n )
throw s968.s1000( L"the 'const' keyword should precede the parameter name" );
s1168 = true;
++n;}
if( l[n]->s494() != s475 ) {
if( s1168 )
throw s968.s1000( L"the 'const' keyword should precede the parameter name" );
break;}
s371* s76 = (s371*)l[n];
s483* s619 = (s483*)l[n + 1];
if( s1168 )
s76->s1260();
s628.s541( s76->s617(), s619 );
s274.push_back( s619->s335(0,0) );
s582.push_back( s619 );
s630.push_back( s619 );
s631.push_back( *s76 );}
s584.insert( s584.end(), l.begin() + n, l.end() );}
s605::s605( const s605& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), s603(), true,
right.s2176 ){
s493 = 0;// Types.Null;
}
void
s605::s500( const s272* s1672, bool proc ){
for( size_t n = 0; n < s584.size(); ++n )
s584[n].s15<s561*>()->s2188( true );
s591::s500( this, proc );
if( !s493 )
s493 = s1152;
return;
s671 = proc ? s588->s298() : s1672->s298();
if( s588->s494() == s479 || s588->s494() == s478 || s588->s494() == s2166) {
if( s588->s494() == s478 || s588->s494() == s2166 )
return;}
if( s274.size() > s630.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( par->s494() == s475 ) {
if( par.s15<s371*>()->s381().s13() )
par.s15<s371*>()->s500( this, proc );}
else
s847( par, n, s274[n], s1672, false );}
for( size_t n = 0; n < s274.size(); ++n ) {
s628.s541( s631[n].s617(), s274[n].s15<s483*>(), s482::s147 );
s274[n]->s1679( s7::s867 );
s630[n] = s274[n];}
for( size_t n = 0; n < s584.size(); ++n ) {
if( s584[n]->s494() == s477 ) {
s490 cs = new s561( *s584[n].s15<s561*>() );
s584[n] = s600( cs, s300, s588, this, s588->s298(), true );}
else if( s584[n]->s494() == s475 )
s584[n].s15<s371*>()->s500( s587, proc );
else if( s584[n]->s494() != s476 )
s584[n]->s500( s587 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s584 ) {
if( it->s494() == s476 )
it.s15<Transd*>()->s500( s588, true );}
if( !s493 && s584.size() ) {
s493 = s584.back()->s352();
s586 = s300->TR().s518( s352(), s588, s588->s298() );}}
s486
s605::s497( s483** s691, size_t s697 ){
s486 s685 = s365;
size_t s2248 = 0;
size_t n;
if( s2239 == -1 ) {
s630.resize( s274.size() );
for( size_t n = 0; n < s274.size(); ++n ) {
s486 s153;
if( s274[n]->s494() == s474 || 
s274[n]->s494() == s480 ) {
s153 = (s483*)s274[n]->s335(0,0);}
else {
s153 = s274[n]->s497( NULL, 0 );}
if( s153->s618() < 0 ) {
if( s153->s618() == s7::s866 )
s153->s1679( 0 );
else {
s586 = s153;
return s153;}}
s630[n] = s153.s15<s484*>();}}
else
s2248 = (size_t)s2239;
for( n = s2248; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s691, s697 );
if( s685->s618() < 0 )
break;}
if( s685->s618() != s7::s2238 ) {
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->release();}
s630.clear();
s2239 = -1;}
else
s2239 = (int)n;
s586 = s685;
return s685;}
s305::s305( s262* s300, s272* s592, Transd* s593, const std::vector<s271*>& l, const s263* s701,
bool s2177 )
: s591( s300, s592, s593, s593, s565, s255, s701, true, s2177 ){
if( l.size() < 2 )
throw new s16( s255 + L"(): wrong numbers of arguments" );
s274.push_back( l[0] );
s630.resize( 1 );
s631.push_back( s371( L"@cond", s300 ) );
s584.insert( s584.end(), l.begin() + 1, l.end() );}
s305::s305( const s305& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), s603(), right.s2176 ){}
void
s305::s500( const s272* s1672, bool proc ){
for( size_t n = 0; n < s584.size(); ++n )
s584[n].s15<s561*>()->s2188( true );
s591::s500( s1672, proc );
s306 = s630[0] = s274[0];
s493 = s584.back()->s352();}
s486
s305::s497( s483** s691, size_t s697 ){
s486 s685 = s365, s153;
while( 1 ) {
if( (bool)*s306->s497( 0, 0 ) == false )
return s685; 
for( size_t n = 0; n < s584.size(); ++n ) {
s153 = s584[n]->s497( s691, s697 );
if( s153->s618() < 0 )
break;}
s685 = s153;
if( s685->s618() < 0 /*s685->s618() == s7::s439 || s685->s618() == s7::s440*/ ) {
if( s685->s618() == s7::s439 )
s685 = s365.s15<s483*>();
break;}}
return s685;}
s614::s614( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, s565, s260, s701, true, s2177 ),
s311( s7::s462, s300 ), s312( s300, 0 ){
TDException s968( s7::s1668, s932, s701, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s968.s1000( L"too few arguments" );
s628.s541( s311.s617(), &s312 );
s582.push_back( (s483*)&s312 );
s630.push_back( (s483*)&s312 );
s631.push_back( s371( s311.s617(), s300 ) );
s271* p = l[0];
if( p->s494() != s475 )
throw s968.s1000( L"the variable must be a name" );
s713 = (s371*) l[0];
varval = s365.s15<s483*>();
s371* in = (s371*) l[1];
if( in->s617() != L"in" )
throw s968.s1000( L"the 'in' keyword is missing" );
s308 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s494() != s475 )
throw s968.s1000( actmsg );
if( ((s371*)p)->s617() == L"where" ) {
where = l[4];
idx = 5;}
if( l.size() < ( idx + 2 ) )
throw new s16( actmsg );
p = l[idx];
if( p->s494() != s475 )
throw new s16( actmsg );
if( ((s371*)p)->s617() == L"project" ) {
if( l.size()  )
s1060 = l[idx+1];}
else {
if( ((s371*)p)->s617() != L"do" )
throw new s16( actmsg );
s584.assign( l.begin() + (idx + 1), l.end() );}
s628.s541( s713->s617(), NULL );
s582.push_back( varval );
s630.push_back( varval );
s631.push_back( s371( s713->s617(), s300 ) );}
s614::s614( const s614& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), s603(), true,
right.s2176 ),s713(right.s713),varval(right.varval),s308(right.s308),where(right.where),
s1060(right.s1060),s311( s7::s462, s300 ), s312( s300, 0 ){
s586 = right.s586;
s493 = right.s493;}
void
s614::s500( const s272* s1672, bool proc ){
TDException s968( s7::s1378, s932, s603(), L"malformed syntax of 'for' statement" );
s472 pc = s308->s494();
if( pc == s477 ) {
s485 s592 = s600( s308.s15<s561*>(), s300, s588, this, s298(), proc );
s308 = s592;
s308.s15<Transd*>()->s500( s1672, false );}
else if( pc == s475 ) {
s308.s15<s371*>()->s500( this, proc );}
else if( pc == s474 )
s308->s500( this );
else
throw s968.s1000( L"unknown iterable type" );
s484* s1476 = s308->s496();
s1061 vt = ( (s326*)s1476 )->s319();
varval = s300->TR().s518(vt, s588, s588->s298() );
varval->s1679( s7::s867 );
s713->s382( varval );
s630[1] = varval.s15<s484*>();
s628.s541( s713->s617(), varval.s15<s484*>(), s482::s147 );
if( where ) {
pc = where->s494();
if( pc == s477 ) {
where = s600( where.s15<s561*>(), s300, s588, this, s298(), proc );
where.s15<Transd*>()->s500( s1672, false );}
else
throw s968.s1000( L"WHERE clause must be a lambda" );}
if( s1060 ) {
pc = s1060->s494();
if( pc == s477 ) {
s1060 = s600( s1060.s15<s561*>(), s300, s588, this, s298(), proc );
s1060.s15<Transd*>()->s500( s1672, false );}
else if( pc == s475 ){
s1060.s15<s371*>()->s500( this );}
else if( pc == s474 )
(void)0;
else
throw s968.s1000( L"PROJECT clause must be a lambda." );
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
s300->TR().s804( s1060->s352() ) + L">";
ts = s300->TR().s1352( ts );
s493 = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );}
for( size_t n = 0; n < s584.size(); ++n )
s584[n].s15<s561*>()->s2188( true );
s591::s500( s1672, /*proc*/ false );
}
void s614::s2133( s591* s2057, s272* impl, bool s2177 ){
if( s587 ) s587 = s2057;
if( impl ) s588 = impl;
s591::s2133( this, impl, s2177 );
s308->s2133( this, impl, s2177 );
s1060->s2133( this, impl, s2177 );}
s486 s614::s497( s483** s691, size_t s697 ){
s486 s685 = s586;
size_t s2248 = 0;
size_t n;
bool s2237 = true;
s9<s326> s985;
Iterator* s1020 = NULL;
if( s2239 == -1 ) {
s472 pc = s308->s494();
if( pc == s476 )
s985 = s308->s497( 0, 0 ).s15<s326*>();
else if( pc == s475 )
s985 = ((s326*)s308.s15<s371*>()->s377());
else
s985 = s308.s15<s326*>();
if( s1060.s14() )
s586.s15<s316*>()->clear();
s1020 = s985->s314( NULL );}
else
s2248 = s2239;
while( 1 ) {
if( 1 || !s2237 || s2239 == -1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
s630[0] = s1020->Idx();
s630[1] = p.s15<s484*>();
if( where ) {
if( ((bool)*(s483*)where->s497( 0, 0 )) != true )
continue;}}
if( s1060 ) {
s586.s15<s316*>()->add( 
s1060->s497( 0, 0 ).s15<s484*>());//->s335(0,0) );
}
else {
for( n = s2248; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s691, s697 );
if( s685->s618() < 0 )
break;}
if( s685->s618() < 0 && s685->s618() != s7::s438 ) {
s2239 = -1;
if( s685->s618() == s7::s439 )
s685 = s365.s15<s483*>();
else if( s685->s618() == s7::s2238 )
s2239 = (int)n;
break;}}}
return s685;}
s271* s605::s335( s591* s2057, s272* impl ) const{
s605* s685 = new s605( *this, impl, s2057 );
s685->s2133( s685, impl, s2176 );
return s685;}
s271* s305::s335( s591* s2057, s272* impl ) const{
s305* s685 = new s305( *this, impl, s2057 );
s685->s2133( s685, impl, s2176 );
return s685;}
/*s271* s307::s335( s591* s2057, s272* impl ) const
{
return new s307( *this );}
*/
s271* s614::s335( s591* s2057, s272* impl ) const{
s614* s685 = new s614( *this, impl ? impl : s588.s15<s272*>(), s2057 );
return s685;}
s604::s604( s262* s300, s272* s588, s591* s587,
s563 ct, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s588, s587, s587, ct, l, s701, false, false ){
s576 = s573;}
void s604::s648( s1061 s619, s591* pOvr ){
types.push_back( s619 );
s649.push_back( pOvr );}
s486 s604::s497( s483** s691, size_t s697 ){
return s591::s497( s691, s697 );}
s838::s838( s262* s300 )
: s591( s300, NULL, NULL, NULL, s567, s252, NULL ), s2104( false ){
s492 = s1245;
s493 = Types.Lambda;
if( !s493 )
wh = s7::s868;
else
wh = s7::s867;}
s838::s838( const s838& )
: s591( s300, NULL, NULL, NULL, s567, s252, NULL ){
throw;}
s838::s838( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l, const s263* s701, s1061 s2122, bool s2105,
bool s2177 )
: s591( s300, s592, s593, s592, s567, s252, s701, false,
s2177 ), s2104( s2105 ){
ns = s588;
s492 = s1245;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( n == 0 && l[n]->s494() == s474 ) {
const s813& vt = s300->TR().s1013( l[n]->s352() );
s1061 pt = vt.s819()[0];
if( pt == s1717 )
s2110 = (s959*)l[n];
else
throw new s16( L"unknown first member in lambda definition" );
n -= 1;
continue;}
if( ( (s483*)l[n] ) == s873 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s1903.push_back( l[n + 1]->s352() );
n += 2;
break;}
if( l[n]->s494() != s475 )
break;
s371* s76 = (s371*)l[n];
lang::s656( s76->s617() );
s483* s619 = (s483*)l[n + 1];
s628.s541( s76->s617(), s619 );
s274.push_back( s619 );
s582.push_back( s619 );
s630.push_back( s619 );
s1903.push_back( s619->s352() );
s631.push_back( s371( s76->s617(), s300 ) );}
if( s2122 ) {
const s813& vt = s300->TR().s1013( s2122 );
s1903.clear();
for( size_t n = 2; n < vt.s819().size(); n += 2 )
s1903.push_back( vt.s819()[n] );
s493 = s2122; // s1903.back();
}
else {
if( s1903.empty() )
s1903 = { s1152, s1152 };
else if( s1903.size() == 1 )
s1903.insert( s1903.begin(), s1152 );
s813::Cont vt = { s1716, (s1061)s1903.size() };
for( size_t n = 0; n < s1903.size(); ++n ) {
vt.push_back( s1903[n] );
vt.push_back( 0 );}
s493 = s300->TR().s1046( vt );}
s584.insert( s584.end(), l.begin() + n, l.end() );}
s838::s838( s262* s300, s272* s592, const vector<s1061>& l,
s1061 pt, const s263* s701 )
: s591( s300, s592, NULL, s592, s567, s252, s701 ), s2104( false ){
s492 = s1245;
s493 = pt;
for( size_t n = 2; n < l.size(); n += 2 )
s1903.push_back( l[n] );
for( size_t n = 1; n < s1903.size() - 1; ++n ) {
s630.push_back( s300->TR().s518( s1903[n], s588, s588->s298() ) );
s274.push_back( s630.back() );
s631.push_back( s371(std::to_wstring( n ), s300 ) );
s628.s541( s631.back().s617(), s274.back().s15<s483*>(), s482::s147 );
s582.push_back( s630.back().s15<s483*>() );}
ns = s588;}
s838::s838( s838& s1901, s272* s592, s591* s593, const std::vector<s485>& l, const s263* s701 )
: s591( s1901, s592, s593, s592, vector<s484*>(), s701, false, true ), s2104( s1901.s2104 ),
s2110( s1901.s2110 ){
s492 = s1245;
s493 = s1901.s493;
s1903 = s1901.s1903;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( l[n].s15<s483*>() ) == s873 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s493 = l[n + 1]->s352();
n += 2;
break;}
if( l[n]->s494() != s475 )
break;
s371* s76 =  l[n].s15<s371*>();
lang::s656( s76->s617() );
s483* s619 = l[n + 1].s15<s483*>();
s628.s541( s76->s617(), s619 );
s274.push_back( s619 );
s582.push_back( s619 );
s630.push_back( s619 );
s631.push_back( s371( s76->s617(), s300 ) );}
if( s630.empty() ) {
s1901.s628.copy( s628, (s272*)s592, s593 );
s630 = s1901.s630;
s631 = s1901.s631;
s274 = s1901.s274;
s582 = s1901.s582;}
if( s2110.s14() ) {
const vector<s485>& v = s2110->s320();
for( size_t n = 0; n < v.size(); ++n ) {
s371* ref = v[n].s15<s371*>();
if( ref->s381().s14() ) {
ref->s2133( this, s592, s2183() );
s483* _dv = ref->s377();
if( _dv->s618() == s7::s868 )
_dv->s500( s588, true );}
else if( s300->s1330() && !s628.s156( ref->s617() ) ) {
ref->s500( this, false );
s483* s2109 = ref->s377();
s631.push_back( *ref );
s271* _p = s2109->s335( this, s588 );
s630.push_back( _p );
s628.s541( ref->s617(), s630.back().s15<s484*>() );}}}
s584.insert( s584.end(), l.begin() + n, l.end() );
s1679( s1901.s618() );}
wstring s838::s834() const{
return ns->s834();}
s483* s838::s354( const s263& s701, s272* s588, s1905& s334 ) const{
TDException s968( s7::s1892, s932, &s701,
L"wrong Lambda constructor syntax" );
wstring s = s300->TR().s1352( s300->TR().s1275( s701.s291(), s334 ));
wstring sv;
wstring s773 = Types( s300, Types.Lambda )->s353();
wstring s1273, s644;
s1061 pt = 0;
s838* s685 = NULL;
if( s.find( s7::s1356 + L"<Lambda<" ) == 0 ) {
s1273 = s.substr( s7::s1356.size() + 1, s.size() - ( s7::s1356.size() + 2) );
size_t pl = s701.Src().find( 955 );
if( pl != string::npos ) {
s644 = s701.Src().substr( pl );
s = s1273 + L"(" + s644;}
else
s = s1273 + L"()";}
if( s.find( s773 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s968.s1000( L"missing type signature" );
if( s1273.empty() )
s1161( s300, s, s1273, s644 );
if( s1273.empty() )
throw s968.s1000( L"missing type signature" );
s813::Cont vt;
size_t pos = 0;
s300->TR().s1056( s1273, pos, vt );
pt = s300->TR().s1011( s813( vt ), false );
if( !pt )
pt = s300->TR().s1046( vt );
if( s644.size() ) {
if( s644.find( L"lambda" ) == 0 || s644[0] == 955 ) {
s947 ast_ = new s263( L"(" + s644 + L")", s701.Nqj(), ((s263*)&s701)->s2098() );
s490 cs = s591::s1119( *ast_, s300, s588, s588->s298(), false );
return new s838( s300, s588, NULL, cs->s602(), &s701, pt, false );}
else if( s644[0] != L']' )
throw s968.s1000( L"malformed Lambda initializer" );}
s813::Cont vt1;
s300->TR().s2137( vt, vt1 );
s685 = new s838( s300, s588, vt1, pt, &s701 );}
return s685;}
void
s838::s500( const s272* s215, bool proc ){
s1061 pt = s493;
s2228( s215, proc );
if( s300->s1330() || s2104 ) { 
s493 = 0; // s1152;
if( !s587 ) s587 = (s591*)s215;
for( size_t n = 0; n < s584.size(); ++n )
s584[n].s15<s561*>()->s2188( true );
s591::s500( this, proc ); 
if( s1903.size() < 2 || s1903.back() == s1152 ) {
if( s1903.empty() ) {
s1903.push_back( s1152 );
if( s584.size() )
s1903.push_back( s584.back()->s352() );
else
s1903.push_back( s1152 );}
s1903.back() = s493 ? s493 : s1903.back();
s813::Cont vt = { s1716, (s1061)s1903.size() };
for( size_t n = 0; n < s1903.size(); ++n ) {
vt.push_back( s1903[n] );
vt.push_back( 0 );}
s493 = s300->TR().s1046( vt );}
else
s493 = pt;
s1262();}
if( s586.s13() || s586->s352() != s493 ) {
if( s215 )
s586 = s300->TR().s518( s1328(), (s272*)s215, s215->s2171() );
else
s586 = s300->TR().s518( s1328(), s588, s588->s298() );}
if( s586.s13() )
s586 = s365.s15<s483*>();}
void s838::s2228( const s272* s215, bool proc ){
if( s2110.s14() /*&& (s300->s1330() || s2104 )*/ ) {
const vector<s485>& v = s2110->s320();
size_t s68 = s630.size() - v.size();
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n].s15<s371*>()->s381().s13() ) {
s371* ref = v[n].s15<s371*>();// ->s335();
ref->s500( this, proc );
s483* s2109 = ref->s377();
s631.push_back( *ref );
s271* s2135 = s2109->s335( this, s588 );
if( !s2135->s1204() )
s2135->s500( s215, proc );
s630.push_back( s2135 );
s628.s541( ref->s617(), s630.back().s15<s484*>() );}
else {
if( !s630[n + s68]->s1204() )
s630[n + s68]->s500( s215, proc );}}}}
s486 s838::s497( s483** s691, size_t s697 ){
s486 s685 = s365;
size_t s2248 = 0;
size_t n;
if( s2239 == -1 ) {
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 )
*( s580 + n + shift ) =
(s483*)( ( s371* )*( s581 + n ) )->s377();
else if( pc == s476 ) {
s981[n+shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
*( s580 + n + shift ) = s981[n + shift];}
else if( pc == s474 || pc == s1245 )
*( s580 + n + shift ) = ( s483* )*( s581 + n );}}
if( s583.size() > 1 ) {
for( size_t n = 1; n < s583.size(); ++n )
s630[n - 1] = s583[n];}}
else
s2248 = s2239;
for( n = s2248; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s580, s498 );
if( s685->s618() < 0 ) {
if( s685->s618() == s7::s2238 )
s2239 = (int)n;
break;}}
if( s685->s618() == s7::s2238 )
s2239 = (int)n;
else
s2239 = -1;
return s685;}
s483* s838::s355( s272* s588, const vector<s1061>& vt ) const{
s1061 pt = s300->TR().s1046( vt );
return new s838( s300, s588, vt, pt, NULL );}
s483* s838::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s838( s300, s588, (s591*)s588, l, ast_ );}
s591* s838::s1685( s1905& s676, s591* s215, s272* s1672,
s561* cs ) const{
if( s676 == s7::s1356 ) {
if( cs->s602().size() > 1 && (cs->s602()[1]->s494() != s475 ||
((s371*)cs->s602()[1])->s617()[0] != 955 ))
throw new s16( L"malformed lambda syntax" );
s263* s1923 = (s263*)cs->s603();
s838* s1921 = (s838*) s354( *s1923, s588.s15<s272*>(), s588->s298() );
vector<s271*> s1922( { s1921 } );
return new s1681( s300, s588.s15<s272*>(), s215, &s483::s1895, 
s1922, s7::s1356, 0, cs->s603(), cs->s2183() );}
return s483::s1685( s676, 
/*(s591*)this*/s215, s1672, cs ); // ???DEBUG??? 220113
}
s271* s838::s335( s591* s2057, s272* impl ) const{
s838* s685 = new s838( *(s838*)this, impl ? impl : s588.s15<s272*>(), 
(s591*)this, vector<s485>(), NULL );
return s685;}
void s838::s2133( s591* s2057, s272* impl, bool s2177 ){
if( s2057 && s2177 && !s2104 ) 
s587 = s2057;
s591::s2133( this, impl, s2177 );
if( s2110.s14() ) {
const vector<s485>& v = s2110->s320();
for( size_t n = 0; n < v.size(); ++n ) {			
s371* ref = v[n].s15<s371*>();
ref->s2133( s2057, impl, false );
s483* s2109 = ref->s377();
s271* s2135 = s2109->s335( s2057, s588 );
if( !s2135->s1204() )
s2135->s500( (s272*)s2057, false );
for( size_t m = 0; m < s631.size(); ++m ) {
if( s631[m].s617() == ref->s617() ) {
s630[m] = s2135;
s628.s541( ref->s617(), s630[m].s15<s484*>(), s482::s147 );}}}}}
s483* s838::s1896( s483** s274, size_t s498 ){
s838* s685 = new s838( *(s838*)this, s588, s587, vector<s485>(), NULL );
s685->s500( s587.s15<s272*>(), false ); 
return s685;}
wstring s838::trace( const char* topics ) const{
wstringstream buf;
int s197 = 0;
wstring s1077 = std::to_wstring( reinterpret_cast<long long>(this));
s1077 = s1077.substr( s1077.size() - 5 );
if( !topics ) {
buf << L"Lambda : " << s1077 << endl;
s591::s304( &buf, s197 );}
else {
string s2130 = topics;
if( s2130 == "id" ) 
buf << L"id: " << s1077 << endl;}
return buf.str();}
void s838::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Lambda : " <<  s278 << endl;
s591::s304( pd, s197 );}
s606::s606( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s243, s701 ){
s274.assign( l.begin(), l.end() );
s493 = s1148;}
s486 s606::s497( s483**, size_t s498 ){
*s586.s15<s360*>()->s357() = 0;
for( size_t n = 0; n < s274.size(); ++n ) {
if( ( bool )*( (s484*)( s274[n]->s497( 0, 0 ) ) ) ) {
*s586.s15<s360*>()->s357() = 1;
return s586;}}
return s586;}
s607::s607( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, s565, s243, s701, false, s2177 ){
s274.assign( l.begin(), l.end() );
s493 = s1148;}
s486 s607::s497( s483**, size_t ){
*s586.s15<s360*>()->s357() = 1;
for( size_t n = 0; n < s274.size(); ++n ) {
if( !( bool )*( (s484*)( s274[n]->s497( 0, 0 ) ) ) ) {
*s586.s15<s360*>()->s357() = 0;
return s586;}}
return s586;}
s1407::s1407( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, s565, s1428, s701, false, s2177 ),
s1502( s7::s1374, s300 ),	s311( s7::s462, s300 ), s312( s300, 0 ){
TDException s968( s7::s1669, s932, s701, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s968.s1000( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s628.s541( s311.s617(), &s312 );
s628.s541( s1502.s617(), NULL );
s630.push_back( (s483*)&s312 );
s630.push_back( NULL );
s631.push_back( s371( s311.s617(), s300 ) );
s631.push_back( s371( s1502.s617(), s300 ) );
s308 = l[0];
if( l.size() > 1 )
lambda = l[1];
s493 = s1148;}
void
s1407::s500( const s272* s1672, bool proc ){
TDException s968( s7::s1376, s932, s603(), L"malformed syntax of 'any()' function call" );
s472 pc = s308->s494();
if( pc == s477 ) {
s485 s592 = s600( s308.s15<s561*>(), s300, s588, this, s298(), proc );
s308 = s592;
s308.s15<Transd*>()->s500( s1672, false );}
else if( pc == s475 ) {
s308.s15<s371*>()->s500( this );}
else if( pc == s474 )
s308->s500( this );
else
throw s968.s1000( L"unknown iterable type" );
varval = s300->TR().s518( ( (s326*)s308->s496() )->ValType(), s588, s588->s298() );
varval->s1262();
s1502.s382( varval );
s630[1] = varval.s15<s484*>();
if( lambda.s14() ) {
if( lambda->s494() == s475 ) {
lambda.s15<s371*>()->s500( s587 );}
else {
lambda.s15<s561*>()->s2188( true );
lambda = s271::s1018( s300, lambda, this, this, s587->s298(), true );}}
for( size_t n = 0; n < s584.size(); ++n )
s584[n].s15<s561*>()->s2188( true );
s591::s500( s1672, false );
s1262();}
s486 s1407::s497( s483**, size_t  ){
TDException s968( s7::s1377, s1379, past );
s486 s685 = s586;
*s685.s15<s360*>()->s357() = false;
s472 pc = s308->s494();
s9<s326> s588;
if( pc == s476 )
s588 = s308->s497( 0, 0 ).s15<s326*>();
else if( pc == s475 )
s588 = ( (s326*)s308.s15<s371*>()->s377() );
else
s588 = s308.s15<s326*>();
Iterator* s1020 = s588->s314( NULL );
while( 1 ) {
s485 p = s1020->s315();
if( p.s13() )
break;
s630[0] = s1020->Idx();
s630[1] = p.s15<s484*>();
if( lambda.s14() ) {
if( ( ( bool )*(s483*)lambda->s497( 0, 0 ) ) == true ) {
*s685.s15<s360*>()->s357() = true;
break;}}
else {
if( ( ( bool )*p.s15<s483*>() ) == true ) {
*s685.s15<s360*>()->s357() = true;
break;}}}
return s685;}
s2077::s2077( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s2078, s701 ){
s274.assign( l.begin(), l.end() );
s493 = 0;}
void
s2077::s500( const s272* s1672, bool proc ){
s591::s500( s1672, proc );
s485 par = s274[0];
s485 s2087 = par;
s1061 pt = par->s352();
for( size_t n = 1; n < s274.size(); ++n ) {
par = s274[n];
if( !par->s1541( pt ) ) {
if( s2087->s1541( par->s352() ) ) {
pt = par->s352();
s2087 = par;}
else
throw new s16( L"incompatible types in '(first)' function" );}}
s586 = s300->TR().s518( pt, ns, ns->s298() );
s493 = pt;
s1262();}
s486 s2077::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
for( size_t n = 0; n < s274.size(); ++n ) {
s486 s153 = s274[n]->s497( 0, 0 );
if( ( bool )*( (s484*)( s153 ) ) ) {
s586 = s153;
return s586;}}
return s365;}
s1939::s1939( s262* s300, s272* s592, s591* s593, vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1944, s701 ){
for( size_t n = 1; n < l.size(); ++n ) {
vector<s271*>& pl = ( (s561*)l[n] )->s602();
pl.insert( begin( pl ), l[n-1] );}
s274.push_back( l.back() );}
void
s1939::s500( const s272* s1672, bool proc ){
s591::s500( s1672, proc );
s493 = s274[0]->s352();
s586 = s300->TR().s518( s352(), s588, s588->s298() );
s1262();}
s486 s1939::s497( s483**, size_t  ){
return s274[0]->s497( 0, 0 );}
vector<wstring> s2209( { L"where:" } );
s2210::s2210( s262* s300, s272* s592, s591* s593, vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s2211, s701, true ){
TDException s968( s7::CLTDFilter_ctor1, s932, s701, L"wrong '(filter ...)' call" );
if( l.size() > 5 )
throw s968.s1000( L"too many arguments" );
if( l.size() < 2 )
throw s968.s1000( L"too few arguments" );
s591::s1242( ( vector<s271*>& )l, s2209 );
s2214 = l[0];
size_t bas = 1;
if( l[1]->s352() == s1415 ) {
range = (s385*)l[1];
bas = 2;}
if( l.size() == 1 + bas ) {
s1070 = l[bas];}
if( l.size() == 2 + bas ) {
where = l[1 + bas];}
else if( l.size() == 3 + bas ) {
if( l[bas]->s494() != s1063 || ((s371*)l[bas])->Id() != s1235 )
throw s968.s1000( L"expected the 'where:' clause" );
where = l[1 + bas];
s1070 = l[2 + bas];}
s493 = 0;}
void
s2210::s500( const s272* s879, bool proc ){
TDException s968( s7::s2208, s932, s603(), L"wrong parameters to '(filter ...)' call");
if( s2214.s13() )
return;
if( s2214->s494() == s475 ) {
s489 rf = s2214.s15<s371*>();
if( rf->s381().s13() )
rf->s500( s879 );
s985 = rf.s15<s371*>()->s377();}
else if( s2214->s494() == s477 ) {
s485 tmp = s271::s1018( s300, s2214, (s272*)s879, (s591*)s879, s879->s298(), false );
s2214 = tmp;
s985 = s2214->s496();}
else {
s985 = (s483*)s271::s1018( s300, s2214, (s272*)s879, (s591*)s879, s879->s298(), false );}
if( !s300->TR().s1465( s985->s352(), s1512::s1507 ) )
throw s968.s1000( L"the type is not rangeable: " + s985->s353() );
if( s985->s494() == s474 ) {}
else if( s985->s494() == s480 ) {}
else
throw s968.s1000( L"unsupported container type" );
if( where.s14() ) {
if( where->s494() == s475 )
where.s15<s371*>()->s500( s879 );
else {
s485 tmp = s271::s1018( s300, where, (s272*)this, (s591*)s879, s879->s298(), false );
where = tmp;}}
if( s1070.s14() ) {
if( s1070->s494() == s475 ) {
s1070.s15<s371*>()->s500( s879 );}
else {
if( s1070->s494() != s1245 ) {
s485 tmp = s271::s1018( s300, s1070, (s272*)s879, (s591*)s879, s879->s298(), false );
s1070 = tmp;}}}
s493 = s985->s352();
s586 = s300->TR().s518( s352(), s588, s588->s298() );
s1262();}
s486 s2210::s497( s483**, size_t  ){
std::vector<s485>s861( 1 );
s685 = new s316( s300, s985.s15<s326*>()->ValType(), s588, s603() );
s685->s500( s588, true );
if( s2214->s494() == s476 ) {
s985 = s2214->s497( 0, 0 );}
Iterator* it = s985.s15<s326*>()->s314( NULL );
while( 1 ) {
s485 p = it->s315();
if( p.s13() )
break;
s861[0] = p;
if( where.s14() ) {
where.s15<s838*>()->s596( s861 );
s486 s153 = where->s497( 0, 0 );
if( !(bool)*s153 )
continue;}
if( s1070.s14() ) {
s1070.s15<s838*>()->s596( s861 );
p = s1070->s497( 0, 0 ).s15<s271*>();}
s685->add( p );}
return s685;}
/*
s2224::s2224( s262* s300, s272* s592, s591* s593, s272* ns_, s563 ct,
s1905& s676, const s263* s701, bool s1727, bool _bd )
: s591( s300, s592, s593, ns_, ct, s676, s701, s1727, _bd ){}
s2224::s2224( s262* s300, s272* s592, s591* s593, s272* ns_,
s563 ct, const std::vector<s271*>& l,	const s263* s701, bool s1727=false,
bool _bd=true)
: s591( s300, s592, s593, ns_, ct, l, s701, s1727, _bd ){}
s2224::s2224( const s2224& right, s272* s592, s591* s593,
s272* ns_, const std::vector<s271*>& s705, const s263* s701, bool s2120,
bool _bd)
: s591( right, s592, s593, ns_, s705, s701, s2120, _bd ){}
void
s2224::s500( const s272* s879, bool proc ){
TDException s968( s7::s2220, s932, s603(), L"wrong parameters to '(filter ...)' call");}
s486 s2224::s497( s483**, size_t  ){
std::vector<s485>s861( 1 );
s685 = new s316( s300, s985.s15<s326*>()->ValType(), s588, s603() );
s685->s500( s588, true );
if( s2214->s494() == s476 ) {
s985 = s2214->s497( 0, 0 );}
Iterator* it = s985.s15<s326*>()->s314( NULL );
while( 1 ) {
s485 p = it->s315();
if( p.s13() )
break;
s861[0] = p;
if( where.s14() ) {
where.s15<s838*>()->s596( s861 );
s486 s153 = where->s497( 0, 0 );
if( !(bool)*s153 )
continue;}
if( s1070.s14() ) {
s1070.s15<s838*>()->s596( s861 );
p = s1070->s497( 0, 0 ).s15<s271*>();}
s685->add( p );}
return s685;}
*/
vector<wstring> s958( { L"else", L"elsif" } );
s608::s608( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701,
bool s2177 )
: s591( s300, s592, s593, s593, s565, s230, s701, false, s2177 ){
wstring s711 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s711 + L"too few arguments." );
s274.assign( l.begin(), l.end() );
s591::s1242( ( vector<s271*>& )l, s958 );}
s608::s608( const s608& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), right.s603(), false, right.s2176 ){
for( size_t n = 0; n < right.s620.size(); ++n )
s620.push_back( right.s620[n]->s335( this, s592 ) );
for( size_t n = 0; n < right.s621.size(); ++n ) {
s621.push_back( s579() );
for( size_t m = 0; m < right.s621[n].size(); ++m )
s621.back().push_back( right.s621[n][m]->s335( this, s592 ) );}
s493 = 0;// Types.Null;
}
void s608::s736( bool proc ){
wstring s711 = L"malformed syntax of 'if' statement: ";
s620.push_back( s274[0] );
s621.push_back( s579() );
s621.back().push_back( s274[1] );
if( s274.size() > 2 ) {
size_t n = 2;
while( n < s274.size() ) {
s485 p = s274[n];
s472 pc = s274[n]->s494();
if( pc == s1063 ) {
if( p.s15<s371*>()->Id() == s1224 ) {
if( s274.size() < n + 2 )
throw new s16( s711 + L"incomplete clause" );
s620.push_back( s274[++n] );
s621.push_back( s579() );
s621.back().push_back( s274[n] );}
else if( p.s15<s371*>()->Id() == s1223 ) {
if( s274.size() < n + 1 )
throw new s16( s711 + L"empty clause" );
s621.push_back( s579() );
s621.back().push_back( s274[++n] );}
else
s621.back().push_back( s274[n] );}
else
s621.back().push_back( s274[n] );
n++;}}
if( !proc ) {
size_t s878 = s621[0].size();
s1061 prevPt = s583[s878]->s352();
for( size_t n = 1; n < s621.size(); ++n ) {
s878 += s621[n].size() + 1;
s1061 tmpPt = s583[s878]->s352();
if( tmpPt && tmpPt != Types.No && ( tmpPt != prevPt ) &&
( s583[s878]->s494() == s476 && 
((s591*)s583[s878])->s864() != s2113 ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s493 = prevPt;
if( !s493 ) // e.g. break, continue
s493 = Types.Null;}
else
s493 = Types.Null;}
void
s608::s500( const s272* s1672, bool proc ){
s591::s500( s1672, proc );
s736( proc );
s586 = s300->TR().s518( s352(), s588, s588->s298() );
s583.insert( s583.begin(), s586 );
s1262();}
void s608::s2133( s591* s2057, s272* impl, bool s2177 ){
s591::s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );
for( size_t n = 0; n < s620.size(); ++n )
s620[n]->s2133(  s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );
for( size_t n = 0; n < s621.size(); ++n ) {
for( size_t m = 0; m < s621[n].size(); ++m )
s621[n][m]->s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );}}
s486 s608::s497( s483**, size_t ){
size_t idx = string::npos;
for( size_t n = 0; n < s620.size(); ++n ) {
if( ( bool )*( s620[n]->s497( 0, 0 ).s15<s483*>() ) ) {
idx = n;
break;}}
if( idx != string::npos || s621.size() > s620.size() ) {
if( idx == string::npos )
idx = s621.size() - 1;
s486 s685;
s579& el = s621[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s685 = el[n]->s497( 0, 0 );
if( s685->s618() < 0 )
break;}
return s685;}
return s365;}
s839::s839( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, /*s565*/ s2113, s852, s701, false, s2177 )
{
if( l.size() > 1 )
throw new s16( s852 + L": too many arguments" );
s274.assign( l.begin(), l.end() );
const s141& s153 = s603()->s268( s2102 );
if( &s153 != &s265 )
s493 = (s1061)s153.s56();
else
s493 = 0;
size_t pl1 = s701->Src().find( L"yield" );
if( pl1 < s701->Src().find( L"return" ) )
s2252 = true;
else
s2252 = false;}
s839::s839( const s839& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), right.s603() ), s2252( right.s2252 ){}
void
s839::s500( const s272* s2178, bool proc ){
if( s274.size() ) {
if( !s493 )
s493 = s1152;
s591::s500( s2178, false );
s271* p = s274[0];
if( p->s494() == s475 || p->s494() == s1337) {
s493 = p->s352();
s586 = s300->TR().s518( s493, (s272*)s2178, s2178->s298() );}
else {
s586 = s583[1]->s496();
s493 = s586->s352();}}
else {
s586 = s365.s15<s483*>();
s493 = s1152;}
s1262();}
s486 s839::s497( s483** s705, size_t s498 ){
if( s2239 != -1 ) {
s2239 = -1;
return s365;}
s486 s685;
if( s274.size() ) {
if( s274[0]->s494() == s475 || s274[0]->s494() == s1337 || s274[0]->s494() == s476 ) {
s685 = s1611( s705, s498 );
if( s685 )
return s685;
s685 = s583[1];}
else
s685 = s274[0].s15<s483*>();}
else
s685 = new s364( s300 );
if( s2252 ) {		
s685->s1679( s7::s2238 );
s2239 = 0;}
else
s685->s1679( s7::s866 );
s586 = s685;
return s586;}
s271* s839::s335( s591* s2057, s272* impl ) const{
s839* s685 = new s839( *this, impl ? impl : s588.s15<s272*>(), s2057 );
return s685;}
s896::s896( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s900, s701 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s900 + L": wrong number of arguments" );
if( l.empty() )
s274.push_back( new s346( s300, 0 ) );
else
s274.assign( l.begin(), l.end() );
s493 = s1151;}
void
s896::s500( const s272* s1672, bool proc ){
s591::s500( s1672, false );
if( s274[0]->s352() != s1151 )
throw new s16( L"The parameter to (exit ) must have Integer type." );
s1262();}
s486 s896::s497( s483** s705, size_t s498 ){
s591::s497( s705, s498 );
code = (int)*s583[1];
throw new s16( (uint32_t) code );}
s271* s896::s335( s591* s2057, s272* impl ) const{
return new s896( *this );}
s611::s611( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s259, s701 ), s78( s300 ){
if( l.size() != 1 )
throw new s16( s259 + L": wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.No;
s78.s11();}
s611::s611( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s259, NULL ), s78( s300 ){
s493 = Types.No;
s78.s11();}
void
s611::s500( const s272* s1672, bool proc ){
s78.s363( s274[0]->to_wstring() );
s586 = s366.s15<s483*>();
s583.push_back( s274[0]->s496() );
s1262();}
s486 s611::s497( s483** s705, size_t s498 ){
s78.s363( s274[0]->s497( s705, s498 )->to_wstring() );
return &s78;}
s612::s612( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s257, s701, true ), 
s76( s7::s461, s300 ), s619( s300 ){
if( l.size() < 2 )
throw new s16( s257 + L"(): wrong numbers of arguments" );
if( l.back()->s494() != s477 ||
((s561*)l.back())->s299() != s258 )
throw new s16( L"the catch clause must be the last statement in the try block" );
s628.s541( s76.s617(), &s619 );
s582.push_back( (s483*)&s619 );
s630.push_back( (s483*)&s619 );
s631.push_back( s371( s76.s617(), s300 ) );
s584.assign( l.begin(), l.end() );}
s612::s612( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s257, NULL, true ), 
s76( s7::s461, s300 ), s619( s300 ){}
void
s612::s500( const s272* s1672, bool proc ){
s591::s500( s1672, proc );
ctch = s584.back().s15<s613*>();
s584.pop_back();
s1262();}
s486 s612::s497( s483** s705, size_t s498 ){
s483* s685 = NULL;
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s705, s498 );
if( s685->s618() < 0 ) {
if( s685->s618() == s7::s440 ) {
s619.s363( ((s361*)s685)->Msg() );
s685 = ctch->s497( &s685, 1 );}
break;}}
s586 = s685;
return s685;}
s613::s613( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s258, s701, true, true ){
s584.assign( l.begin(), l.end() );
s493 = Types.Null;}
s613::s613( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s258, NULL ){
s493 = Types.Null;}
s486 s613::s497( s483** s691, size_t s697 ){
s483* s153;
for( size_t n = 0; n < s584.size(); ++n ) {
s153 = s584[n]->s497( s691, s697 );
if( s153->s618() < 0 ) {
return s153;}}
return s365.s15<s483*>();}
s755::s755( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s751, s701 ){}
void
s755::s500( const s272* s1672, bool proc ){}
s486 s755::s497( s483** s705, size_t s498 ){
return 0;}
s1680::s1680( s262* s300, s272* s592, s591* s593, s1682 ptr_,
s561* cs, const s263* s701 )
: s591( s300, s592, s593, s593, s565, L"", s701 ), s1684( ptr_ ){
subject = cs->s602()[0];
s274.assign( cs->s602().begin() + 1, cs->s602().end() );}
void
s1680::s500( const s272* s1672, bool proc ){
s493 = s588->s352();
s591::s500( s1672, proc );
s1262();}
s486 s1680::s497( s483** s705, size_t s498 ){
s487	s1654 = subject->s497( 0, 0 ).s15<s272*>();
return ( *s1654.*s1684)( &s583[0], s498 );}
s1681::s1681( s262* s300, s272* s592, s591* s593, s1683 ptr_,
const vector<s271*>& s1922, const wstring& s676, s1061 s1072, 
const s263* s701, bool _bd )
: s591( s300, s592, s593, s592, s565, s676, s701, false, _bd ), s1684( ptr_ ){
subject = s1922[0];
s274.assign( s1922.begin() + 1, s1922.end() );
s493 = s1072;
ns = s588;}
s1681::s1681( const s1681& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s592, vector<s484*>(), right.s603(), false, right.s2183() ),
s1684( right.s1684 ), subject( right.subject ){}
void
s1681::s500( const s272* s1672, bool proc ){
s485 s703 = subject;
if( s703->s494() == s475 )
s703 = s703.s15<s371*>()->s377();
if( !s493 ) {
if( s703->s494() == s1245 ) {
if( s278 == s7::s1356 || s278 == L"cp" )
s493 = s703->s352();
else
s493 = s703.s15<s838*>()->s1328();}
else {
if( s278 == L"cp" )
s493 = s588->s352();
else
s493 = s703->s352(); }}
s591::s500( s587, proc );
if( 0 && s278 == L"exec" ) {
if( s703->s618() < 0 )
s703->s500( s1672, proc );}
s1262();}
void s1681::s2133( s591* s2057, s272* impl, bool s2177 ){
s591::s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );
s485 s703 = subject;
s703->s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );}
s486 s1681::s497( s483** s705, size_t s498 ){
s485 s703 = subject;
if( s703->s494() == s475 )
s703 = s703.s15<s371*>()->s377();
else if( s703->s494() == s476 ) {
s486 tmp = s703->s497(0,0);
if( tmp->s618() == s7::s866 )
tmp->s1262();
s703 = tmp.s15<s484*>();}
if( s703->s494() == s1245 ) {
if( s278 == s7::s1356 ) {
s838* s685 = new s838( *s703.s15<s838*>(), s588, 
s587, s2115, s603() );
s685->s500( s588, true );
return s685;}
else if( s278 == L"cp" ) {
return (s483*)s703->s335(0,0);}
else if( s278 == L"exec" ) {
s9<s838> pf;
if( s703->s618() < 0 ) {
s703->s500( s587, false );}
else
s703.s15<s838*>()->s2228( s587, false );
pf = s703.s15<s838*>();
vector<s485> s2127;
for( auto par_ : s274 ) {
s483* par = NULL;
if( par_->s494() == s475 )
par = par_.s15<s371*>()->s377();
else
par = par_.s15<s483*>();
s472 pc = par->s494();
if( pc == s1245 ) {
if( par->s618() < 0 )
par->s500( s587, false );
s2127.push_back( par );}
else {
if( pc == s476 ) {
if( par->s618() < 0 )
par->s500( this, false );
else
par->s2133( this, s588, s2183() );}
s2127.push_back( par->s497( 0, 0 ).s15<s484*>() ); }}
pf.s15<s838*>()->s596( s2127 );
pf.s15<s838*>()->s597( this );
pf->s2133( pf, s588, s2183() );
s486 s685 = pf->s497( 0, 0 ).s15<s272*>();
if( s685->s618() == s7::s866 )
s685->s1679( 0 );
return  s685;}
try {
s703.s15<s838*>()->s596( s274 );}
catch( s16* e ) {
wstring s78 = L"in function '" + s278 + L"'";
if( s603() )
s78 += L" :\n" + TDException::s1912( *s603() );
e->s30( s78 );
throw e;}
return s703->s497( 0, 0 ).s15<s272*>();}
else {
s487 s1654 = subject->s497( 0, 0 ).s15<s272*>();
return ( *s1654.*s1684 )( &s583[0], s498 );}}
s1609::s1609( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1619, s701 ){
s274.assign( l.begin(), l.end() );}
s1609::s1609( const s1609& right )
: s591( right ), cmd( right.cmd ){}
void
s1609::s500( const s272* s1672, bool proc ){
s300->s2012( s2053, s2045 );
s493 = s1152;
s591::s500( s1672, proc );
s1262();}
void s1612( const wstring& cmd, wstring* s1646, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1646 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1646 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s486 s1609::s497( s483** s691, size_t s697 ){
if( s300->s2012( s2053, s2046 ) )
return s586;
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
wstring cmd_ = s583[1]->to_wstring(), s1647;
bool* pdone = ( (s360*)s583[2] )->s357();
wstring *s1646 = NULL;
if( s583.size() > 3 )
s1646 = ( (s359*)s583[3] )->s357();
else
s1646 = &s1647;
if( s823.joinable() ) {
s823.join();}
s823 = thread( s1612, cmd_, s1646, pdone );
return s586;}
s1607::s1607( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1617, s701 ){
if( l.size() != 2 )
throw new s16( s1617 + L"(): wrong numbers of arguments" );
if( l[0]->s494() != s475 )
throw new s16( s1617 + L"(): the first argument must be a reference" );
s274.assign( l.begin(), l.end() );}
s1607::s1607( const s1607& right )
: s591( right ){}
void
s1607::s500( const s272* s1672, bool proc ){
s493 = s1152;
s591::s500( s1672, proc );
s1262();}
s486 s1607::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
s371* dr = s274[0].s15<s371*>();
s272* mod = dr->s381().s15<s272*>();
mod->s1657( dr->s617(), s583[2] );
return s586;}
s1604::s1604( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, s565, s1615, s701,
false, s2177 ){
if( l.size() != 2 )
throw new s16( s1615 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1604::s1604( const s1604& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s593, vector<s484*>(), right.s603(),
false, true ){}
void
s1604::s500( const s272* s1672, bool proc ){
s493 = s1152;
s591::s500( s1672, proc );
s1262();}
s486 s1604::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
s272* dr = (s272*)s583[1];
s1602* ob = (s1602*)s583[2];
try {
dr->s1640( ob );}
catch( s16* e ) {
wstring s78 = L"in function " + s299() + L":\n";
s78 += L"during loading object: " + dr->s1673() +
L":" + dr->s353() + L":";
e->s30( s78 );
throw e;}
return s586;}
s1608::s1608( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1618, s701 ){
if( l.size() != 1 )
throw new s16( s1618 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1608::s1608( const s1608& right )
: s591( right ){}
void
s1608::s500( const s272* s1672, bool proc ){
s493 = s1152;
s591::s500( s1672, proc );
s1262();}
s486 s1608::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
int dr = (int)*(s346*)s583[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s586;}
s1603::s1603( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701,
bool s2177 )
: s591( s300, s592, s593, s593, s565, s1614, s701, true, s2177 ){
if( l.size() != 1 )
throw new s16( s1614 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1603::s1603( const s1603& right, s272* s592, s591* s593 )
: s591( right, s592, s593, s593, vector<s484*>(), right.s603(), true, right.s2183() ){
s586 = s300->TR().s518( s493, s588, s588->s298() );}
void
s1603::s500( const s272* s1672, bool proc ){
s493 = Types.String;
s591::s500( s1672, proc );
s1262();}
s486 s1603::s497( s483** s691, size_t s697 ){
wstringstream buf;
s274[0]->s304( &buf );
*s586.s15<s359*>()->s357() = buf.str();
s586->s1262();
return s586;}
s1885::s1885( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1886, s701 ){
if( l.size() > 2 )
throw new s16( s1886 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1885::s1885( const s1885& right )
: s591( right ){}
void
s1885::s500( const s272* s1672, bool proc ){
s493 = s1150;
s591::s500( s1672, proc );
s1262();}
s486 s1885::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);
*s586.s15<s358*>()->s357() = dist( mt );
return s586;}
s271* s608::s335( s591* s2057, s272* impl ) const{
s608* s685 = new s608( *this, impl ? impl : s588.s15<s272*>(), s2057 );
s685->s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2183() );
return s685;}
s271* s606::s335( s591* s2057, s272* impl ) const{
return new s606( *this );}
s271* s607::s335( s591* s2057, s272* impl ) const{
return new s607( *this );}
s271* s1407::s335( s591* s2057, s272* impl ) const{
return new s1407( *this );}
s271* s2077::s335( s591* s2057, s272* impl ) const{
return new s2077( *this );}
s271* s1939::s335( s591* s2057, s272* impl ) const{
return new s1939( *this );}
s271* s2210::s335( s591* s2057, s272* impl ) const{
return new s2210( *this );}
s271* s611::s335( s591* s2057, s272* impl ) const{
return new s611( *this );}
s271* s612::s335( s591* s2057, s272* impl ) const{
return new s612( *this );}
s271* s613::s335( s591* s2057, s272* impl ) const{
return new s613( *this );}
s271* s755::s335( s591* s2057, s272* impl ) const{
return new s755( *this );}
s271* s1680::s335( s591* s2057, s272* impl ) const{
return new s1680( *this );}
s271* s1681::s335( s591* s2057, s272* impl ) const{
s1681* s685 = new s1681( *this, impl, s2057 );
return s685;}
s271* s1609::s335( s591* s2057, s272* impl ) const{
return new s1609( *this );}
s271* s1607::s335( s591* s2057, s272* impl ) const{
return new s1607( *this );}
s271* s1604::s335( s591* s2057, s272* impl ) const{
return new s1604( *this, impl, s2057 );}
s271* s1608::s335( s591* s2057, s272* impl ) const{
return new s1608( *this );}
s271* s1603::s335( s591* s2057, s272* impl ) const{
return new s1603( *this, impl, s2057 );}
s271* s1885::s335( s591* s2057, s272* impl ) const{
return new s1885( *this );}
vector<wstring> s956( { L"to:", L":sign", L":nosign", L":boolalpha", 
L":noboolalpha", L"width:", L"prec:", L"fill:", L":left", L":right", L":internal", 
L":fixed", L":group", L":nl" } );
s609::s609( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, 
const s263* s701, bool s2177 )
: s591( s300, s592, s593, s592, s565, s251, s701, true, s2177 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s701->Src().find( L"lout" );
if( pl1 < s701->Src().find( L"textout" ) )
lout = true;
vector<s271*>tmp( l );
s591::s1242( tmp, s956 );
s274.assign( tmp.begin(), tmp.end() );
s493 = Types.Null;}
s609::s609( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s251, NULL, true, false ), s42( NULL ),
lout( false ){
s493 = Types.Null;}
s609::s609( const s609& right, s272* s592, s591* s593 )
: s591( right, s592, 
s593, s592, vector<s484*>(), right.s603(), true, right.s2183() ), s42( right.s42 ),
lout( right.lout ){
s493 = Types.Null;}
void s609::s500( const s272* s1672, bool proc ){
TDException s968( s7::s1937, s932, s603(), L"malformed '(textout)' function call" );
s591::s500( s1672, proc );
size_t start = 0;
if( s274[0]->s494() == s1063 ) {
if( s274[0].s15<s371*>()->Id() == s1233 ) {
start = 2;
/*s42 = s274[1];
s274.erase( s274.begin(), s274.begin() + 2 );
s583.erase( s583.begin()+1, s583.begin() + 3 );
nlocs = s274.size();
s498 = s583.size();*/
}}
for( size_t n = start; n < s274.size(); ++n ) {
if( s274[n]->s494() == s1063 ) {
int mark = (int)*( s274[n].s15<s371*>() )->s377();
if( mark != s1570 && s274.size() <= n )
s968.s1000( L"incorrect usage of formatting marker: " + (s274[n].s15<s371*>())->s617() );
if( mark == s1571 && !s300->TR().s1465(
s274[n + 1]->s352(), s1512::s1549 ) )
s968.s1000( L"'width:' formatting marker should have an integer parameter" );
if( mark == s1917 && !s300->TR().s1465(
s274[n + 1]->s352(), s1512::s1549 ) )
s968.s1000( L"'fill:' formatting marker should have a char (one symbol string) parameter" );}}
s1262();}
s486 s609::s497( s483** s691, size_t s697 ){
s483* s685 = s1611( s691, s697 );
if( s685 )
return s685;
if( s274[0]->s494() == s1063 ) {
if( s274[0].s15<s371*>()->Id() == s1233 ) {
s42 = s274[1];
s274.erase( s274.begin(), s274.begin() + 2 );
s583.erase( s583.begin()+1, s583.begin() + 3 );
nlocs = s274.size();
s498 = s583.size();}}
s1::s9<Stream> s778;
if( s42.s14() ) {
s472 pc = s42->s494();
if( pc == s476 )
s778 = s42->s497( 0, 0 ).s15<Stream*>();
else if( pc == s475 )
s778 = (Stream*)s42.s15<s371*>()->s377();
else
s778 = s42.s15<Stream*>();}
else
s778 = s1405.s15<Stream*>();
s778->s1567();
uint32_t flags = 0;
for( size_t n = 1; n < s583.size(); ++n ) {
if( s583[n]->s494() == s1063 ) {
int mark = (int)*( (s371*)s583[n] )->s377();
if( mark == s1469 ) {
s778->s1929();}
else if( mark == s1590 ) {
s778->s1927();}
else if( mark == s1967 ) {
s778->s1957();}
else if( mark == s1968 ) {
s778->s1958();}
else if( mark == s1917 ) {
wchar_t c = s583[++n]->to_wstring()[0];
s778->s1913( c );}
else if( mark == s1571 ) {
int w = (int)*s583[++n];
s778->s1568( w );}
else if( mark == s1933 ) {
int pr = (int)*s583[++n];
s778->s1928( pr );}
else if( mark == s1919 ) {
s778->s1915();}
else if( mark == s1920 ) {
s778->s1916();}
else if( mark == s1918 ) {
s778->s1914();}
else if( mark == s1932 ) {
s778->s1926();}
else if( mark == s1569 ) {
flags |= s1559;}
else if( mark == s1570 ) {
s778->s1481( L"" );
n++;}}
else {
s486 s153 = s583[n]->s497( s691, s498 );
s153->s1935( s778 );}}
if( lout )
s778->s1481( L"" );
return s365;}
s271* s609::s335( s591* s2057, s272* impl ) const{
s609* s685 = new s609( *this, impl ? impl : s588.s15<s272*>(), s2057 );
return s685;}
void s609::s2133( s591* s2057, s272* impl, bool s2177 ){
s591::s2133( s2057 ? s2057 : s587.s15<s591*>(), 
impl ? impl : s588.s15<s272*>(), s2177 );
if( s42 )
s42->s2133( s2057 ? s2057 : s587.s15<s591*>(), impl ? impl : s588.s15<s272*>(), s2177 );}
vector<wstring> s1941( { L"from:", L":boolalpha", L":noboolalpha", L"width:", 
L"prec:", L":fixed", L":group", L":nl" } );
s1940::s1940( s262* s300, s272* s592, s591* s593, 
const vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1945, s701 ), source( NULL ),
lin( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s701->Src().find( L"lin" );
if( pl1 < s701->Src().find( L"textin" ) )
lin = true;
vector<s271*>tmp( l );
s591::s1242( tmp, s1941 );
s274.assign( tmp.begin(), tmp.end() );
s493 = Types.Null;}
s1940::s1940( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s1945, NULL ), source( NULL ),
lin( false ){
s493 = Types.Null;}
void s1940::s500( const s272* s1672, bool proc ){
TDException s968( s7::s1936, s932, s603(), L"malformed '(textin)' function call" );
s591::s500( s1672, proc );
if( (s274[0]->s494() == s1063 && s274[0].s15<s371*>()->Id() == s1226 ) ||
(s300->TR().s1465( s274[0]->s352(), s1512::s1505 ))) {
int s375 = 1;
if( s274[0]->s494() == s1063 )
s375 = 2;
source = s274[s375 - 1];
s274.erase( s274.begin(), s274.begin() + s375 );
s583.erase( s583.begin()+1, s583.begin() + s375 + 1 );
nlocs = s274.size();
s498 = s583.size();}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s494() == s1063 ) {
int mark = ( int )*( s274[n].s15<s371*>() )->s377();
if( s274.size() <= n )
s968.s1000( L"incorrect usage of formatting marker: " + ( s274[n].s15<s371*>() )->s617() );
if( mark == s1571 && !s300->TR().s1465(
s274[n + 1]->s352(), s1512::s1549 ) )
s968.s1000( L"'width:' formatting marker should have an integer parameter" );}}
s1262();}
s486 s1940::s497( s483** s691, size_t s697 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 || pc == s1337 )
*( s580 + n + shift ) =
(s483*)( ( s371* )*( s581 + n ) )->s377();
else if( pc == s476 ) {
s981[n + shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
*( s580 + n + shift ) = s981[n + shift];}}}
s1::s9<Stream> src;
if( source.s14() ) {
s472 pc = source->s494();
if( pc == s476 )
src = source->s497( 0, 0 ).s15<Stream*>();
else if( pc == s475 )
src = (Stream*)source.s15<s371*>()->s377();
else
src = source.s15<Stream*>();}
else
src = s1403.s15<Stream*>();
src->s1567();
for( size_t n = 1; n < s583.size(); ++n ) {
if( s583[n]->s494() == s1063 ) {
int mark = (int)*( (s371*)s583[n] )->s377();
if( mark == s1967 ) {
src->s1951();}
else if( mark == s1968 ) {
src->s1953();}
else if( mark == s1571 ) {
int w = (int)*s583[++n];
src->s1956( w );}
else if( mark == s1933 ) {
int pr = (int)*s583[++n];
src->s1954( pr );}
else if( mark == s1932 ) {
src->s1952();}}
else {
s486 s153 = s583[n]->s497( s691, s498 );
s153->s1959( src );}}
if( lin )
src->ws();
return s365;}
s271* s1940::s335( s591* s2057, s272* impl ) const{
return new s1940( *this );}
s610::s610( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s256, s701 ){
if( l.size() != 1 )
throw new s16( s256 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s610::s610( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s256, NULL ){}
void s610::s500( const s272* s592, bool proc ){
s300->s2012( s2052, s2045 );
s813::Cont s1279;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<" + 
Types( s300, Types.Bool )->s353() +
L" " + Types( s300, Types.String )->s353() + L">";
s493 = ((s959*)Types( s300, Types.Tuple ))->s1195( ts, s1279 );
s591::s500( s592, proc );}
s486 s610::s497( s483** s705, size_t s498 ){
s959* s685 = s586.s15<s959*>();
s685->clear();
if( s300->s2012( s2052, s2046 ) ) {
s685->s320().push_back( s370 );
s685->s320().push_back( new s359( s300, L"the '(eval)' function is disabled by current security settings" ) );
return s685;}
try {
s486 s153;
if( s274[0]->s494() == s475 )
s153 = s274[0].s15<s371*>()->s377();
else if( s274[0]->s494() == s476 )
s153 = s274[0].s15<s591*>()->s497( NULL, 0 );
else
s153 = s274[0].s15<s483*>();
wstring f = s153->s497( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s485> s912;
s947 ast_ = new s263( f, s603()->Nqj(), (s263*)s603() );
s490 cs = s591::s1119( *ast_, s300, s588, s298(), true );
s912.push_back( cs );
s488 s910 = s591::s600( cs, s300, s588, this, s298(), false );
s910->s500( s588, true );
s486 res1 = s910->s497( 0, 0 );
if( !res1 || res1->s618() != s7::s440 ) {
s685->s320().push_back( s369 );
s685->s320().push_back( new s359( s300, res1 ? res1->to_wstring() : L"" ) );}
else {
s685->s320().push_back( s370 );
s685->s320().push_back( new s359(s300, res1.s15<s361*>()->Msg() ) );}}
else {
vector<wstring> l;
s486 res1 = s300->callFunc( f, l );
s685->s320().push_back( s369 );
s685->s320().push_back( new s359( s300, res1 ? res1->to_wstring() : L"" ) );}}
catch( s16* e ) {
s685->s320().push_back( s370 );
s685->s320().push_back( new s359(s300, e->Msg() ) );}
return s685;}
s271* s610::s335( s591* s2057, s272* impl ) const{
return new s610( *this );}
s1::s9<s262> s615::s906;
s615::s615( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701, bool s2177 )
: s591( s300, s592, s593, s593, s565, s261, s701, true, s2177 ){
if( l.size() != 1 )
throw new s16( s261 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s615::s615( s262* s300 )
: s591( s300, NULL, NULL, NULL, s565, s261, NULL ){
s493 = Types.Null;}
s486 s615::s497( s483** s705, size_t s498 ){
vector<wstring> s911;
for( size_t n = 0; n < s274.size(); ++n ) {
s911.push_back( s274[n]->s497( 0, 0 )->to_wstring() );}
if( s906.s13() ) {
s906 = new s262();
s906->s1900( true );}
else
s906->reset();
s906->s209( s911[0] );
s586 = s906->run( s911 );
return s586;}
s271* s615::s335( s591* s2057, s272* impl ) const{
return new s615( *this );}
s797::s797( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s772, s701 ){
if( l.size() != 1 )
throw new s16( s772 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s797::s497( s483** s705, size_t s498 ){
wstring s194 = s274[0]->s497( s705, s498 )->to_wstring();
s300->s209( s194 );
return s365;}
s271* s797::s335( s591* s2057, s272* impl ) const{
return new s797( *this );}
s775::s775( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s593, s565, s821, s701 ){
s904 = s592->s298();
if( l.size() != 1 )
throw new s16( s821 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s775::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s902;
if( par->s494() == s475 )
s902 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s902 = par->s497( 0, 0 )->to_wstring();
try {
s272* ob = ((s272*)s300->s641( s904, s904 ));
ob->s555( s902, s904 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s775::s335( s591* s2057, s272* impl ) const{
return new s775( *this );}
s1307::s1307( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1317, s701 ){
if( l.size() != 1 )
throw new s16( s1317 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s1307::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s671;
if( par->s494() == s475 )
s671 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s671 = par->s497( 0, 0 )->to_wstring();
try {
s300->s1351( s671 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s1307::s335( s591* s2057, s272* impl ) const{
return new s1307( *this );}
s1610::s1610( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s593, s565, s1620, s701 ){
if( l.size() != 1 )
throw new s16( s1620 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s1610::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s671;
if( par->s494() == s475 )
s671 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s671 = par->s497( 0, 0 )->to_wstring();
try {
s300->s1665( s671 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s1610::s335( s591* s2057, s272* impl ) const{
return new s1610( *this );}
s1781::~s1781(){
release();}
void s1781::release(){
for( auto i : s871 )
i.second.clear();
s871.clear();}
s1782::s1782( s1781* s1806 ) 
: pdb( s1806 ), fi( s1847), se(s1847) {
ptr = new s1784();}
s1782::~s1782(){
if( ptr ) {
ptr->clear();
delete ptr;}}
const vector<wstring> s1778::s1879 = { L"", L"==", L"<", L">", L"<=", L">=", L"<>" };
s1778::s1778( s262* s300, s272* s588, const std::wstring& s, size_t& pos ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
size_t s69 = s68;
if( s[s68] == L'"' ) {
s4::s1001( s, s69, s4::s48 );
field = s.substr( s68+1, s69 - s68 - 2 );}
else {
s69 = s.find_first_of( s4::s48, s68 );
field = s.substr( s68, s69 - s68 );}
s69 = s68 = s.find_first_not_of( s4::s48, s69 );
s4::s1001( s, s69, s4::s48 );
wstring s1865 = s.substr( s68, s69 - s68 );
auto s1836  = std::find( s1879.begin(), s1879.end(), s1865 );
if( s1836 == s1879.end() )
throw new s16( L"unknown operation in query string: " + s1865 );
op = (s1778::s1791) std::distance( s1879.begin(), s1836 );
s6::s1769.push_back( s1736.s151 );
s6::s142 nq = new s6::s141( NULL, s, s69, s1736 );
s6::s1769.pop_back( );
s947 s701 = new s263( L"", *nq, NULL );
par = s271::s504( *s701, s300, s588, s588->s298() );
pos = s69 == s.size() ? string::npos : s69;
return;}
void s1778::s500( s272* ns ){
if( par->s494() == s475 ) {
par->s500( ns );}}
void s1778::select( s1781* pdb, s1787& s153 ){
if( par->s494() == s475 )
s349 = par.s15<s371*>()->s377();
else
s349 = par;
pdb->select( field, op, s349.s15<s483*>(), s153 );}
s1779::s1779( s262* s300, s272* s588, const std::wstring& s, size_t& pos, s1780 s1803 )
: s1817( s1803 ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
if( s[s68] == L'(' ) {
s1810( s300, s588, s, ++s68 );}
else
s1810( s300, s588, s, s68 );}
s1779::s1779( const s1779& r )
: s1817( r.s1817 ), subs( r.subs ), s1811( r.s1811 ){}
void s1779::s500( s272* ns ){
for( auto i : subs )
i.s500( ns );
for( auto i : s1811 )
i.s500( ns );}
void s1779::s1810( s262* s300, s272* s588, const std::wstring& s, size_t& pos ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
while( s68 != string::npos ) {
if( s[s68] == L')' )
return;
else if( s[s68] == L'(' ) {
size_t s74, s75;
s4::s54( s, s68, L'(', L')', s74, s75 );
if( s75 == string::npos )
throw new s16( L"unmatched parentheses in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 = s.find_first_not_of( s4::s48, s74 + 1 );
subs.push_back( s1779( s300, s588, s, s68, s1813 ) );}
else if( s[s68] == L'A' || s[s68] == L'a' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1869 = s.substr( s68, pl - s68 );
if( s1869 != L"AND" && s1869 != L"and" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 3;
if( s1817 == s1813 )
s1817 = s1812;
else if( s1817 == s1812 )
(void)0;
else {
if( subs.empty() && s1811.empty() )
throw new s16( L"wrong query syntax: 'AND' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1779( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1811.clear();
s1817 = s1812;}}
else if( s[s68] == L'O' || s[s68] == L'o' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1869 = s.substr( s68, s.size() - pl + 1 );
if( s1869 != L"OR" && s1869 != L"or" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 2;
if( s1817 == s1813 )
s1817 = s1814;
else if( s1817 == s1814 )
(void)0;
else {
if( subs.empty() && s1811.empty() )
throw new s16( L"wrong query syntax: 'OR' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1779( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1811.clear();
s1817 = s1814;}}
else {
s1811.push_back( s1778( s300, s588, s, s68 ) );
if( s68 != string::npos )
++s68;}}}
bool s1802( s822 l, s822 r ){
return ( size_t )&( *l ) < ( size_t )&( *r );}
void s1779::select( s1781* pdb, s1782* s153 ){
s1789 s1830;
vector<s1784> s1862;
s1782 *s1877, *s1876;
for( size_t n = 0; n < s1811.size(); ++n ) {
s1787 s1069;
s1811[n].select( pdb, s1069 );
s1830.insert( s1069 );}
s1877 = pdb->s1818();
s1876 = pdb->s1818();
auto it = begin( s1830 );
if( s1830.size() ) {
if( s1817 == s1812 || s1830.size() == 1 ) {
pdb->intersect( *it, s153 );
s153->sort();}}
for( ++it; it != end( s1830 ); ++it ) {
s1877->clear();
if( s1817 == s1812 ) {
pdb->intersect( *it, s1877 );
s1877->sort();
if( s153->empty() )
s153->swap( s1877 );
else {
std::set_intersection( begin( s153->s320() ), end( s153->s320() ), 
begin( s1877->s320() ), end( s1877->s320() ), 
back_inserter( s1876->s320() ), s1802 );
s153->swap( s1876 );
s1876->clear();}}}
for( size_t n = 0; n < subs.size(); ++n ) {
subs[n].select( pdb, s1877 );
if( s1817 == s1812 ) {
s1877->sort();
if( s153->empty() )
s153->swap( s1877 );
else {
std::set_intersection( begin( s153->s320() ), end( s153->s320() ),
begin( s1877->s320() ), end( s1877->s320() ),
back_inserter( s1876->s320() ), s1802 );
s153->swap( s1876 );
s1876->clear();}}
s1877->clear();}}
vector<wstring> s957( { L"select:", L":select", L":update", L"reduce:", 
L":reduce", L"all", L"as:", L"where:", L"satisfying:", L"using:", L":distinct",	
L"sortby:", L":asc", L":desc", L"limit:", L"set:" } );
struct s848{
size_t idx;
s848( size_t s869 ): idx( s869 ){}
bool operator()( const s486 l, const s486 r ) const{
s486 ld = l.s15<s750*>()[idx];
s486 rd = r.s15<s750*>()[idx];
return ld->operator<( (s483*)&(*rd) );}
};
void s791::s1723( const std::vector<s271*>& l_, TDException& s968 ){
const size_t s1055 = 9;
std::vector<s271*> l( s1055, NULL );
s1712* sqr = new s1712;
s1711* sqp = new s1711;
sqr->verb = s744::s1776;
s371* rf = (s371*)l_[1];
if( rf->Id() == s2071 )
l[1] = new s371( L"all", s300, s1063 );
size_t s986 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1063 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1217 ) s986 = 2;
else if( rf->Id() == s1216 ) {
s986 = s1147;
l[1] = l_[n];}
else if( rf->Id() == s1235 ) s986 = 3;
else if( rf->Id() == s1843 ) s986 = 4;
else if( rf->Id() == s1221 ) {
s986 = s1147;
sqr->distinct = 1;}
else if( rf->Id() == s1232 ) {
sqr->s888 = s1712::s837::s828;
s986 = 6;}
else if( rf->Id() == s1218 ) {
if( s986 != 7 )
throw s968.s1000( L"the '" + rf->s617() + L"' specifier is misplaced" );
s986 = s1147;
sqr->s888 = s1712::s837::s828;}
else if( rf->Id() == s1220 ) {
if( s986 != 7 )
throw s968.s1000( L"the '" + rf->s617() + L"' specifier is misplaced" );
s986 = s1147;
sqr->s888 = s1712::s837::s831;}
else if( rf->Id() == s1230 ) 
s986 = 8;
else
throw s968.s1000( L"misplaced query keyword: " + s957[rf->Id()] );}
else
l[s986++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1072 = l[2];
sqp->where = l[3];
sqp->s1867 = l[4];
sqp->s889 = l[6];
sqp->s874 = l[8];}
void s791::s1724( const std::vector<s271*>& l_, TDException& s968 ){
const size_t s1055 = 4;
std::vector<s271*> l( s1055 );
s1722* sqr = new s1722;
s1721* sqp = new s1721;
sqr->verb = s744::s1777;
size_t s986 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1063 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1754 ) s986 = 1;
else if( rf->Id() == s1235 ) s986 = 2;
else if( rf->Id() == s1843 ) s986 = 3;
else
throw s968.s1000( L"misplaced query keyword: " + s957[rf->Id()] );}
else
l[s986++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->where = l[2];
sqp->s1867 = l[3];
if( sqp->what.s13() )
throw s968.s1000( L"the 'UPDATE' query must include 'SET' and `SATISFYING` clauses" );}
void s791::s2002( const std::vector<s271*>& l_, TDException& s968 ){
const size_t s1055 = 6;
std::vector<s271*> l( s1055, NULL );
s1986* sqr = new s1986;
s1985* sqp = new s1985;
sqr->verb = s744::s2059;
s371* rf = (s371*)l_[1];
if( rf->Id() == s2070 )
l[1] = new s371( L"all", s300, s1063 );
size_t s986 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1063 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1217 ) s986 = 2;
else if( rf->Id() == s1216 ) {
s986 = s1147;
l[1] = l_[n];}
else if( rf->Id() == s1235 ) s986 = 3;
else if( rf->Id() == s1843 ) s986 = 4;
else if( rf->Id() == s2021 ) s986 = 5;
else
throw s968.s1000( L"misplaced query keyword: " + s957[rf->Id()] );}
else
l[s986++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1072 = l[2];
sqp->where = l[3];
sqp->s1867 = l[4];
sqp->s2057 = l[5];}
s791::s791( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l_, const s263* s701 )
: s591( s300, s592, s593, s593, s565, s818, s701 ), s2038( s7::s1982, s300 ),
s733( s7::s462, s300 ), s783( new s272( s300, 0, s480, NULL, NULL, s2202 ) ),
s1859( NULL ){
TDException s968( s7::s1110, s932, s701 );
if( l_.size() < 3 )
throw s968.s1000( L"too few arguments." );
s591::s1242( ( vector<s271*>& )l_, s957 );
s628.s541( s733.s617(), s783.s15<s483*>() );
s582.push_back( s783.s15<s483*>() );
s274.push_back( s783.s15<s483*>() );
s630.push_back( s783.s15<s483*>() );
s631.push_back( s371( s733.s617(), s300) );
if( l_[1]->s494() != s1063 )
throw s968.s1000( L"the second participant must be a query verb: SELECT, UPDATE, etc." );
s371* rf = (s371*)l_[1];
if( rf->Id() == s1231 || rf->Id() == s2071 )
s1723( l_, s968 );
else if( rf->Id() == s1756 )
s1724( l_, s968 );
else if( rf->Id() == s2020 || rf->Id() == s2070 )
s2002( l_, s968 );}
s791::~s791(){
if( s1859 )
delete s1859;}
s484* s791::s1805( const std::wstring& s ){
size_t pos = 0;
if( s1859 )
delete s1859;
s1859 = new s1779( s300, this, s, pos, s1779::s1813 );
return NULL;}
void s791::s2063( s1781* base, s485 what, vector<wstring>& s895,
std::vector<s488>& s2061, vector<wstring>& s1868 ){
s472 pc = what->s494();
s486 s1764 = what.s15<s483*>();
if( pc == s475 ) {
s489 rf = what.s15<s371*>();
s1764 = rf->s377();}
else if( pc == s1063 ) {
s489 rf = what.s15<s371*>();
if( rf->s617() == L"all" || rf->s617() == L"ALL" ) {
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1061 s1517 = ((s316*)Types( s300, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s1764 = s300->TR().s518( s1517, ns, ns->s298() );
vector<wstring> s2074;
base->s1832( s2074 );
for( auto s : s2074 )
s1764.s15<s316*>()->add( new s359( s300, s ) );}
else
throw new s16( L"fields for selection are not recognized" );}
else if( pc == s474 ) {
(void)0;}
s813 vt = s300->TR().s1013( s1764->s352() );
if( vt.s352() == s1719 || vt.s352() == s1718 ) {
const vector<s485>* v = NULL;
if( vt.s352() == s1719 )
v = &s1764.s15<s316*>()->s320();
else
v = &s1764.s15<s750*>()->s320();
s2061.resize( v->size() );
for( size_t n = 0; n < v->size(); ++n ) {
wstring s858;
auto it = ( *v )[n];
if( it->s494() == s475 ) {
if( it.s15<s371*>()->s381().s13() )
it->s500( this );
s858 = it.s15<s371*>()->s377()->to_wstring();}
else
s858 = it->to_wstring();
size_t s882 = s4::s88.find( s858[0] );
if( s882 != string::npos )
s858 = s4::s52( s858, wstring( 1, s4::s88[s882] ) );
size_t pl = s858.find( L"|=" );
if( s858[0] == L'(' ) {
vector<wstring> s80;
size_t pos = 0;
s263::s288( s858, pos, s80 );
if( s80.size() > 2 )
throw new s16( L"too many arguments in field expression: " + s858 );
s486 s2011 = s300->TR().s518( base->s2015( s80[1] ), ns, s298() );
std::vector<s271*> pl = { s2011 };
s561 cs( s300, s80[0], pl, NULL );
auto s2055 = s591::s600( &cs, s300, ns, (s591*)this, s298(), false );
s2055->s500( this, false );
s2061[n] = s2055;
s895.push_back( s80[1] );}
else if( pl != string::npos ) {
wstring s2141 = s4::s52( s858.substr( 0, pl ), s4::s48 );
wstring s2140 = s4::s52( s858.substr( pl + 2 ), s4::s48 );
s895.push_back( s2141 );
s1868.push_back( s2140 );}
else {
s895.push_back( s858 );
s1868.push_back( s858 );}}}}
void s791::s1725( const s272* s1672, bool proc ){
TDException s968( s7::s920, s932, past );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s968.s1000( L"the database must be specified by a name or expression." );
s1711* sqp = qp.s15<s1711*>();
if( sqp->s1072.s14() ) {
sqp->s1072->s500( this );
s813::Cont s1279;
wstring sv = sqp->s1072->s353();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + sv + L">";
s493 = ( (s316*)Types( s300, Types.Vector ) )->s1195( this, ts, s1719, s1279 );}
else {
if( s300->TR().s1465( db->s352(), s1512::s1507 ) )
s493 = db.s15<s326*>()->s352();
else
throw s968.s1000( L"the 'AS' clause is missing." );}
s591::s500( s1672, proc );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what->s500( this );}
else if( pc == s475 )
sqp->what.s15<s371*>()->s500( this );
else if( pc == s474 || pc == s1063 )
(void)0;
else
throw s968.s1000( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s352() != Types.String )
throw s968.s1000( L"the 'WHERE' clause must be a string." );
if( s300->TR().s1465( db->s352(), s1512::s1507 ) )
throw s968.s1000( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1805( sqp->where->to_wstring() );}
if( sqp->s1867 ) {
pc = sqp->s1867->s494();
if( pc == s477 ) {
sqp->s1867 = s600( sqp->s1867.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1867.s15<Transd*>()->s500( s1672, false );
s835 s881;
sqp->s1867.s15<Transd*>()->s814( s881 );}
else
throw s968.s1000( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s874.s14() ) {
pc = sqp->s874->s494();
if( pc == s477 ) {
sqp->s874 = s600( sqp->s874.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s874->s500( this );}
else if( pc == s475 )
sqp->s874.s15<s371*>()->s500( this );
else if( sqp->s874->s352() != s1151 )
throw s968.s1000( L"the limit must be specified by a number, variable or expression." );}}
void s791::s1726( const s272* s1672, bool proc ){
s1721* sqp = qp.s15<s1721*>();
s493 = s1151;
TDException s968( s7::s920, s932, past );
s591::s500( s1672, proc );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s968.s1000( L"the database must be specified by a name or expression." );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what.s15<Transd*>()->s500( s1672, false );}
else
throw s968.s1000( L"the 'SET' clause must be a lambda" );
if( sqp->where ) {
if( sqp->where->s352() != Types.String )
throw s968.s1000( L"the 'WHERE' clause must be a string." );
if( s300->TR().s1198( db->s352(), s1512::s1507 ) )
throw s968.s1000( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1805( sqp->where->to_wstring() );}
if( sqp->s1867 ) {
pc = sqp->s1867->s494();
if( pc == s477 ) {
sqp->s1867 = s600( sqp->s1867.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1867.s15<Transd*>()->s500( s1672, false );}
else
throw s968.s1000( L"the 'SATISFYING' clause must be a lambda." );}}
void s791::s2004( const s272* s1672, bool proc ){
s1985* sqp = qp.s15<s1985*>();
/*s813::Cont s1279;
wstring sv = sqp->s1072->s353();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + sv + L">";
s493 = ((s316*)Types( s300, Types.Vector ))->s1195( ts, s1279 );*/
s493 = s1152; // sqp->s1072->s352();
TDException s968( s7::s920, s932, past );
s2038.s379( 0, s2037 );
s2038.s382( (s483*)this );
s591::s500( s1672, proc );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s968.s1000( L"the database must be specified by a name or expression." );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what->s500( this );}
else if( pc == s475 )
sqp->what.s15<s371*>()->s500( this );
else if( pc == s474 || pc == s1063 )
(void)0;
else
throw s968.s1000( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s352() != Types.String )
throw s968.s1000( L"the 'WHERE' clause must be a string." );
sqp->where = s1805( sqp->where->to_wstring() );}
if( sqp->s1867 ) {
pc = sqp->s1867->s494();
if( pc == s477 ) {
sqp->s1867 = s600( sqp->s1867.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1867.s15<Transd*>()->s500( s1672, false );
s835 s881;
sqp->s1867.s15<Transd*>()->s814( s881 );}
else
throw s968.s1000( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s2057 ) {
pc = sqp->s2057->s494();
if( pc == s477 ) {
sqp->s2057 = s600( sqp->s2057.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s2057.s15<Transd*>()->s500( s1672, false );
s835 s881;
sqp->s2057.s15<Transd*>()->s814( s881 );}
else
throw s968.s1000( L"the 'USING' clause must be a lambda." );}}
void
s791::s500( const s272* s1672, bool proc ){
if( s810->verb == s744::s1776 )
s1725( s1672, proc );
else if( s810->verb == s744::s1777 )
s1726( s1672, proc );
else if( s810->verb == s744::s2059 )
s2004( s1672, proc );}
s486 s791::s1731( s483** s274, size_t s498 ){
s1721* sqp = qp.s15<s1721*>();
s486 s685 = s586;
vector<wstring> s895;
vector<wstring> s1868;
s1::s9<s1781> base;
TDException s968( s7::s921, s929, past );
assert( db->s494() == s475 );
s483* s2064 = db.s15<s371*>()->s377();
if( s300->TR().s1465( s2064->s352(), s1512::s1507 ) )
base = new s2062( s300, ns, (s326*)s2064, s603() );
else
base = (s1781*)s2064;
s1::s1289<s1782> dom = base->s1818();
if( s1859 ) {
s1859->select( base, dom );}
else
base->s1870( dom );
s835 s881;	
sqp->what.s15<Transd*>()->s814( s881 );
for( size_t n = 0; n < s881.size(); ++n ) {
s895.push_back( s881[n].first );}
s881.clear();
if( sqp->s1867.s14() ) {
sqp->s1867.s15<Transd*>()->s814( s881 );
if( s881.empty() )
throw s968.s1000( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s881.size(); ++n )
s1868.push_back( s881[n].first );}
vector<s485> s880, pls1;
s880.resize( s1868.size() );
pls1.resize( s895.size() );
int s684 = 0;
dom->s1874();
s486 s153 = s369.s15<s483*>();
while( dom->s1835() ) {
s1::s9<s1783> s1857 = dom->s1845();
if( sqp->s1867.s14() ) {
for( size_t n = 0; n < s1868.size(); ++n )
s880[n] = s1857->s760( s1868[n] ).s15<s484*>();
sqp->s1867.s15<Transd*>()->s596( s880 );
s153 = sqp->s1867->s497( 0, 0 );}
if( s153.s14() && (bool)*s153 ) {
for( size_t n = 0; n < s895.size(); ++n )
pls1[n] = s1857->s760( s895[n] ).s15<s484*>();
sqp->what.s15<Transd*>()->s596( pls1 );
s486 s153 = sqp->what->s497( 0, 0 );
++s684;}}
*s586.s15<s346*>()->s357() = s684;
return s586;}
s486 s791::s1730( s483** s274, size_t s498 ){
s1711* sqp = qp.s15<s1711*>();
s1712* sqr = s810.s15<s1712*>();
s486 s685 = s586;
vector<wstring> s895;
vector<s488> s2061;
vector<wstring> s2158;
vector<wstring> s2153;
s1::s9<s1781> base;
size_t s908 = string::npos;
TDException s968( s7::s921, s929, past );
assert( db->s494() == s475 );
s483* s2064 = db.s15<s371*>()->s377();
if( s300->TR().s1465( s2064->s352(), s1512::s1507 ) )
base = new s2062( s300, ns, (s326*)s2064, s603() );
else
base = (s1781*)s2064;
if( sqp->s874.s14() ) {
if( sqp->s874->s494() == s475 ) {
sqr->s874 = ( int )*( (s346*)sqp->s874.s15<s371*>()->s377() );}
else if( sqp->s874->s494() == s476 ) {
sqr->s874 = (int)*sqp->s874->s497( 0, 0 );}
else
sqr->s874 = (int)*sqp->s874;}
if( sqp->s889.s14() ) {
if( sqp->s889->s494() == s475 ) {
sqr->s887 = sqp->s889.s15<s371*>()->s377()->to_wstring();}
else if( sqp->s889->s494() == s476 ) {
sqr->s887 = sqp->s889->s497( 0, 0 )->to_wstring();}
else
sqr->s887 = sqp->s889->to_wstring();}
s2063( base, sqp->what, s895, s2061, s2158 );
s1::s1289<s1782> dom = base->s1818();
if( s1859 ) {
s1859->select( base, dom );}
else
base->s1870( dom );
s835 s881;
if( sqp->s1867.s14() ) {
sqp->s1867.s15<Transd*>()->s814( s881 );
if( s881.empty() )
throw s968.s1000( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s881.size(); ++n ) {
for( size_t m = 0; m < s2158.size(); ++m ) {
if( s881[n].first == s2158[m] )
s2153.push_back( s895[m] );}}}
vector<s485> s880;
s880.resize( s2153.size() );
s586.s15<s316*>()->clear();
dom->s1874();
while( dom->s1835() ) {
s1783* s1857 = dom->s1845();
s486 s1808;
if( sqp->s1867.s14() ) {
for( size_t n = 0; n < s2153.size(); ++n )
s880[n] = s1857->s760( s2153[n] ).s15<s484*>();
sqp->s1867.s15<Transd*>()->s596( s880 );
s1808 = sqp->s1867->s497( 0, 0 );}
else
s1808 = s369.s15<s483*>();
if( s1808.s14() && (bool)*s1808 ) {
s1::s9<s750> s894 = new s750( s300, NULL, L"" );
if( s895.empty() )
s1857->s863( *s894 );
else {
for( size_t n = 0; n < s895.size(); ++n )
s894->add( s1857->s760( s895[n] ).s15<s271*>() );}
s894->s1679( s7::s867 );
s586.s15<s316*>()->add( s894 );}}
if( sqr->distinct != -1 ) {
vector<s485>& s899 = s586.s15<s316*>()->s320();
for( size_t n = 0; n < s899.size(); ++n ) {
s485 s898 = s899[n];
size_t m = n + 1;
while( m < s899.size() ) {
s485 _el1 = s899[m];
if( *s898.s15<s750*>() == _el1.s15<s483*>() )
s899.erase( s899.begin() + m );
else
m++;}}}
if( sqr->s888 != -1 ) {
if( s895.size() && sqr->s887.size() ) {
auto it = std::find( s895.begin(), s895.end(), sqr->s887 );
if( it != s895.end() )
s908 = std::distance( s895.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s903;
dom->s1831( s903 );
auto it = std::find( s903.begin(), s903.end(), sqr->s887 );
if( it != s903.end() )
s908 = std::distance( s903.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s897> s901 = new s897;
s901->s907( s908 );
s840 s909( s901 );
s586.s15<s316*>()->sort( sqr->s888 == s1712::s831, &s909 );}
if( sqr->s874 != -1 ) {
s586.s15<s316*>()->s320().resize( sqr->s874 );}
return s685;}
s486 s791::s2007( s483** s274, size_t s498 ){
s1985* sqp = qp.s15<s1985*>();
vector<wstring> s895;
vector<wstring> s2158;
vector<wstring> s2153;
vector<s488> s2061;
TDException s968( s7::s921, s929, past );
s1::s9<s1781> base;
if( db->s494() == s475 ) {
s483* s2064 = db.s15<s371*>()->s377();
if( s300->TR().s1465( s2064->s352(), s1512::s1507 ) )
base = new s2062( s300, ns, (s326*)s2064, s603() );
else
base = (s1781*)s2064;}
else if( db->s494() == s476 ) {
s483* s2064 = db->s497( 0, 0 );
if( s300->TR().s1465( s2064->s352(), s1512::s1507 ) )
base = new s2062( s300, ns, (s326*)s2064, s603() );
else
base = (s1781*)s2064;}
else
throw s968.s1000( L"TSD query cannot be performed on a non-TSD object" );
s1786::iterator s1837, s1838;
try {
s2063( base, sqp->what, s895, s2061, s2158 );}
catch( s16* e ) {
throw s968.s1000( L"error while parsing WHAT clause: " + e->Msg() );}
s1::s1289<s1782> dom = base->s1818();
if( s1859 ) {
s1859->select( base, dom );}
else
base->s1870( dom );
s835 s881;
if( sqp->s1867.s14() ) {
sqp->s1867.s15<Transd*>()->s814( s881 );
if( s881.empty() )
throw s968.s1000( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s881.size(); ++n ) {
for( size_t m = 0; m < s2158.size(); ++m ) {
if( s881[n].first == s2158[m] )
s2153.push_back( s895[m] );}
while( s1837 != s1838 ) {
++s1837;}}}
vector<s485> s2032, s2033;
s2032.resize( s2153.size() );
s835 s2058;
if( sqp->s2057.s14() ) {
sqp->s2057.s15<s838*>()->s814( s2058 );
for( auto p: s2058 )
s2033.push_back( p.second->s335(0,0) );
if( s2033.size() != s895.size() )
throw s968.s1000( L"in the REDUCE query the number of selected fields doesn't match "
"the number of parameters to 'using' function");}
else
s2033.resize( s895.size() );
dom->s1874();
s1783* s1857 = dom->s1845();
while( /*dom->s1835()*/ s1857 ) {
s486 s1808;
if( sqp->s1867.s14() ) {
for( size_t n = 0; n < s2153.size(); ++n )
s2032[n] = s1857->s760( s2153[n] ).s15<s484*>();
sqp->s1867.s15<Transd*>()->s596( s2032 );
s1808 = sqp->s1867->s497( 0, 0 );}
else
s1808 = s369.s15<s483*>();
if( s1808.s14() && (bool)*s1808 ) {
if( s895.empty() )
s1857->s863( *s2037 );
else {
for( size_t n = 0; n < s895.size(); ++n ) {
if( s2061[n] ) {
vector<s485> s2031( { s1857->s760( s895[n] ).s15<s484*>() } );
s2061[n]->s596( s2031 );
s2033[n] = s2061[n]->s497( 0, 0 ).s15<s271*>();}
else
s2033[n] = s1857->s760( s895[n] ).s15<s271*>();}}
if( sqp->s2057.s14() ) {
sqp->s2057.s15<Transd*>()->s596( s2033 );
sqp->s2057->s497( 0, 0 );}}
s1857 = dom->s1845();}
return s365; //s2037;
}
s486 s791::s497( s483** s691, size_t s697 ){
if( s810->verb == s744::s1776 )
return s1730( s691, s697 );
else if( s810->verb == s744::s1777 )
return s1731( s691, s697 );
else if( s810->verb == s744::s2059 )
return s2007( s691, s697 );
return NULL;}
bool
s791::s556( const wstring& s676, s371* ref, const wstring& s334, 
bool b ) const{
if( s676 == s7::s1982 ) {
ref->s1343( (s371*)&s2038 );
return true;}
return s591::s556( s676, ref, s334, b ); }
s271* s791::s598( size_t off ){
assert( off == 0 );
if( s2037 )
return s2037;
return (s271*) s2038.s503();}
s271* s791::s335( s591* s2057, s272* impl ) const{
return new s791( *this );}
s776::s776( s262* pass_, s272* s588, const wstring& s768, 
const vector<wstring>& s743, std::vector<s485>& types, const s1720& tbfr )
: s2151( NULL ){
s750 s781( pass_, s588, s768, NULL, tbfr );
s781.s500( s588, true );
vector<s485> s820 = s781.s320();
if( s820.size() > types.size() )
throw new s16( L"The number of record's fields is greater than the number of columns: " + s768 );
for( size_t n = 0; n < s743.size(); ++n ) {
s485 s811;
if( n < s820.size() ) {
if( !s820[n]->s501( types[n].s15< s483*>() ) ) {
if( tbfr.promInts && types[n]->s352() == s1150 && s820[n]->s352() == s1151 )
s820[n] = new s358( pass_, (double)*s820[n].s15<s346*>()->s357() );
else
throw new s16( L"The types of record's fields don't match to the types of columns: " + s768 );}
s811 = s820[n];}
else {
s811 = types[n].s15<s484*>()->s335(0,0);
s811->to_null();}
s762.insert( make_pair( s743[n], s811 ) );
size_t h = s811.s15<s483*>()->s322();
rechash = ( rechash << 1 ) ^ h;}
s2151 = &s762;}
s776::s776( s262* pass_, s1602& obj ){
s2151 = ( std::map<std::wstring, s485>*)&obj.s628.Table();
pobj = &obj;}
size_t s776::s322() const{
return rechash;}
s486 s776::s760( s1905& s76, bool s714 ) const{
auto it = s2151->find( s76 );
if( it == s2151->end() ) {
if( s714 )
throw new s16( L"Record field doesn't exist: " + s76, 
(uint32_t)s16::s17::s23 );
else
return s486();}
return it->second.s15<s483*>();}
void s776::s863( s750& s153 ) const{
for( auto r: *s2151 )
s153.add( r.second );}
void s776::s863( s959& s153 ) const{
for( auto r: *s2151 )
s153.add( r.second );}
void s776::s545( std::vector<std::wstring>& s153 ) const{
for( auto r: *s2151 )
s153.push_back( r.first );}
bool s776::operator==( const s776* p ) const{
return rechash == p->rechash;}
bool s776::operator<( const s776* p ) const{
return rechash < p->rechash;}
wstring s776::to_wstring( uint32_t s1565 ) const{
wstringstream ss;
s304( &ss, 0 );
return ss.str();}
void s776::s304( std::wostream* pd, int s197/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"TSDRecord : " << endl;
for( auto it = begin( *s2151 ); it != end( *s2151 ); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << it->first << L":" << endl;
it->second->s304( pd, s197 + s419 );}}
s812::s812( vector<wstring>& s732, s822 rec ){
for( size_t n = 0; n < s732.size(); ++n ) {
s485 f = rec->s760( s732[n] ).s15<s484*>();
s811.push_back( f );}
for( size_t n = 0; n < s732.size(); ++n ) {
size_t h = s811[n].s15<s483*>()->s322();
s800 = ( s800 << 1 ) ^ h;}}
size_t s812::s322() const{
return s800;}
bool s812::operator==( const s812* p ) const{
return s800 == p->s800;}
bool s812::operator<( const s812* p ) const{
return s800 < p->s800;}
void s812::s304( std::wostream* pd, int s197/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s811.size(); ++n ) {
s811[n]->s304( pd, s197 + s419 );}}
s1796::s1796( s1781* pdb )
: s1782( pdb ), pind(NULL)//, fi1(s1848), se1(s1848)
{}
void s1796::s1871( void* f, void* s ){
pind = (s787*)f;}
void s1796::s1874(){
if( pind )
cur1 = pind->begin();
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1796::s1835(){
if( pind )
return cur1 != pind->end();
else
return cur != se;}
s1783* s1796::s1845(){
if( s1835() ) {
s1783* s685;
if( pind ) {
s685 = cur1->second;
cur1++;}
else {
s685 = *cur;
cur++;}
return s685;}
else
throw new s16( L"TSDBase row iterator is out of range" );}
s650::s650( s262* s300, s272* s588, const s263* ast_ ) 
: s1781( s300, s588, NULL ) {
s493 = Types.TSDBase;}
s650::s650( s262* s300, s272* s588, const wstring& s77, const s263* ast_ )
: s1781( s300, s588, ast_ ){
s499 = s77;
s493 = Types.TSDBase;}
s650::s650( const s650& right, const s263* ast_ )
: s1781( right.s300, right.ns, ast_ ){
s493 = right.s493;}
s483* s650::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return new s650( s300, s588, L"" );}
void s650::s500( const s272*, bool ){
s1262();}
void s650::s350(){
s813::Cont s1279;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" +
Types( s300, Types.String )->s353() + L">";
s1061 s1517 = ( (s316*)Types( s300, Types.Vector ) )->s1195( this, ts, s1719, s1279 );
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s650::s1236, s1798,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"add-file", new s337( L"add-file", &s650::s786, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"add-object", new s337( L"add-object", &s650::s2142, s1152,
{ s1122( { Types.s272 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"set-prim-key", new s337( L"set-prim-key", &s650::s2154, s1152,
{ s1122( { s1517 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"load-table", new s337( L"load-table", &s650::s802, s1152,
{ s1122( { Types.String, Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s348.insert( make_pair( L"select", new s337( L"select", &s650::s752, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"query", new s337( L"query", &s650::s770, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s650::s333, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s650::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"build-index", new s337( L"build-index", &s650::s856, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );}
s483* s650::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s650( s300, s588, L"" );}
inline bool
s650::s501( const s483* s502 ) const{
return ( ((s650*)s502)->s352() == s352() );}
s271* s650::s335( s591* s2057, s272* impl ) const{
return new s650( *this );}
void s650::s356( s271* p ) const{
p = new s650( *this );}
size_t s650::s322() const{
return (size_t)this;}
bool s650::operator==( const s483* p ) const{
return ( this == p );}
bool s650::operator<( const s483* p ) const{
return false;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s650*)(s484*)*s274)
inline void s650::s1236( s483** s274, size_t s498 ){
s650* ps = (s650*)DR;
s650* s685 = new s650( ps->s300, ps->ns, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s650::s786( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s650*)DR )->s654( s194 );}
inline void s650::s2142( s483** s274, size_t s498 ){
s1602* ob = (s1602*)PARN( 2 );
( (s650*)DR )->s379( *ob );}
inline void s650::s2154( s483** s274, size_t s498 ){
s316* pv = (s316*)PARN( 2 );
vector<s485>& s2157 = pv->s320();
( (s650*)DR )->s2145.clear();
for( size_t n = 0; n < s2157.size(); ++n )
( (s650*)DR )->s2145.push_back( s2157[n]->to_wstring() );}
inline void s650::s802( s483** s274, size_t s498 ){
s650* dr = ( (s650*)DR );
const wstring& s824 = PARN( 2 )->to_wstring();
s1720 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par_ = s274[n];
s472 pc = par_->s494();
if( pc == s1063 ) {
s485 par;
s489 rf;
rf = par_.s15<s371*>();
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1753 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1751 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1749 ) {
if( s498 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1734 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1750 ) {
tbfr.s1697 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1842 ) {
tbfr.s1826 = true;}
else if( rf->Id() == s1752 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"TSDBase::(load-table): unknown parameters" );
++n;}
dr->s718( s824, tbfr );}
inline void s650::s752( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s650*)DR )->s655( s194 );}
inline void s650::s770( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s650*)DR )->s655( s194 );}
inline void s650::s333( s483** s274, size_t s498 ){}
inline void s650::s328( s483** s274, size_t s498 ){}
inline void s650::s331( s483** s274, size_t s498 ){}
inline void s650::s856( s483** s274, size_t s498 ){
wstring s858 = PARN( 2 )->to_wstring();
((s650*)DR)->s855( s858 );}
void s650::s654( const wstring& s194 ){
vector<s9<s143>> s662;
s945 s1051( s194 );
s1051.read( s662, s7::s1106 );
for( size_t m = 0; m < s662.size(); m++ ) {
s143* obj = s662[m];
wstring s658 = s4::s52( s263::s302( *obj, s7::s465 ), 
s48 );
if( s658.empty() )
throw new s16( L"Nameless blocks are forbidden." );
vector<pair<wstring, s142>> s144;
obj->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].second->s164() != s134 && s144[n].second->s164() != s139 )
throw new s16( L"unrecognized format of field " + s658 +L"::"+s144[n].first );
wstring sobj = s144[n].second->s169();
wstring srel = s144[n].first;
s651.insert( make_pair( s658, make_pair( srel, sobj ) ) );
s652.insert( make_pair( srel, make_pair( s658, sobj ) ) );
s653.insert( make_pair( sobj, make_pair( s658, srel ) ) );}}}
void s650::s379( s1602& obj ){
s822 rec = new s776( s300, obj );
s734 s152 = new s812( s2145, rec );
s757.insert( make_pair( s152, rec ) );}
void s650::s655( s1905& q ){
vector<wstring> qs;
s4::s57( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s651.begin(); it != s651.end(); ++it )
wcout << it->first;}}
void s650::select( s1905& field, s1778::s1791 op, const s483* s1065,
s1787& s153 ){
auto it = s871.find( field );
if( it == s871.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1778::s1851 ) {
s153.pr = it->second.equal_range( (s483*)s1065 );}
else if( op == s1778::s1854 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s483*)s1065 );}
else if( op == s1778::s1855 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s483*)s1065 );}
else if( op == s1778::s1852 ) {
s153.pr.first = it->second.upper_bound( (s483*)s1065 );
s153.pr.second = it->second.end();}
else if( op == s1778::s1855 ) {
s153.pr.first = it->second.lower_bound( (s483*)s1065 );
s153.pr.second = it->second.end();}
else {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}}
s1782* s650::s1818() const{
return new s1796( (s1781*)this );}
void s650::s1870( s1782* s153 ){
s153->s1871( (void*)&s757, (void*)NULL );}
void s650::intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ){
s1786::iterator it = fi1.pr.first;
wstring attr2 = fi2.s977;
s1785 s1815;
while( it != fi1.pr.second ) {
s486 attr2v = it->second->s760( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1815 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1815 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s650::intersect( const s1787& fi, s1782* s153 ){
s1786::iterator it = fi.pr.first;
s1784 s1877;
s1784& s1860 = ((s1796*)s153)->s320();
bool s1824 = s1860.empty();
while( it != fi.pr.second ) {
if( s1824 || std::binary_search( begin( s1860 ), end( s1860 ), it->second, s1802 ) )
s1877.push_back( it->second );
++it;}
s1860.swap( s1877 );}
void s650::s718( const wstring& s824, const s1720& tbfr ){
wstring s743 = tbfr.s1734;
vector<wstring> s815;
vector<wstring> s731;
vector<wstring> s805;
vector<wstring> s825;
if( s743.size() ) {
s4::s57( s743, tbfr.s1697, s815 );
s4::s57( s4::s52( s824, s48 ), tbfr.rowSep, s805 );}
else {
s743 = s824.substr( 0, s824.find( tbfr.rowSep ) );
s4::s57( s4::s52( s824.substr( s743.size() ), s48 ), tbfr.rowSep, s805 );
if( s743.back() == '\r' )
s743.pop_back();
s4::s57( s743, tbfr.s1697, s815 );}
vector<s485> s1772;
vector<s485> types;
if( !s805.empty() ) {
s750 s781( s300, ns, s805[0], NULL, tbfr );
s781.s500( ns, true );
s1772 = s781.s320();}
for( size_t n = 0; n < s815.size(); ++n ) {
vector<wstring> s1733;
s4::s57( s815[n], L":", s1733 );
s947 s1771;
if( s1733.size() == 2 )
s1771 = new s263( s1733[1] + L"()", NULL, NULL );
else if( n < s1772.size() )
s1771 = new s263( s1772[n]->s353() + L"()", NULL, NULL );
else
s1771 = new s263( Types( s300, Types.String )->s353() + L"()", NULL, NULL );
s485 ptype = s300->TR().s518( *s1771, ns, ns->s298() );
types.push_back( ptype );
if( s1733[0][0] != L'@' )
s731.push_back( s1733[0] );
else {
size_t pl = s1733[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1733[0] );
wstring s76 = s1733[0].substr( pl + 1 );
s731.push_back( s76 );
s825.push_back( s76 );}}
if( !s825.empty() ) {
s757.rehash( (size_t) ( s805.size() * 1.1 ) );
for( auto row : s805 ) {
s822 rec = new s776( s300, ns, row, s731, types, tbfr );
s734 s152 = new s812( s825, rec );
s757.insert( make_pair( s152, rec ) );}}}
void s650::s855( const wstring& s858 ){
auto it = s871.find( s858 );
if( it != end( s871 ) )
s871.erase( it );
s1786& s870 = s871.insert( make_pair( s858, s1786() ) ).first->second;
for( auto it: s757 ) {
s486 pd;
try {
pd = it.second->s760( s858 );}
catch( ... ) {}
if( pd.s14() )
s870.insert( make_pair( pd, it.second ) );}}
bool s650::s2010( s1905& s977 ) const{
assert(0);
return false;}
s1061 s650::s2015( s1905& s858 ) const{
assert( 0 );
return 0;}
void s650::s1832( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
wstring s650::to_wstring( uint32_t s1565 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s650::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"TSDBase : " << endl;
for( auto it = begin( s757 ); it != end( s757 ); ++it ) {
it->first->s304( pd, s197 + s419 );
it->second.s15<s776*>()->s304( pd, s197 + s419 );}}
s1784 s1846 = { new s1800( vector<s486>( {s486()} ), NULL ) };
s1784::iterator s1847 = s1846.begin();
s1800::s1800( const std::vector<s486>& v, s1801* s1807 )
: s1861( v ), s1858( s1807 ){}
s1800::~s1800(){
s1861.clear();}
const s1800::s1793& s1800::s2016() const{
return s1861;}
s486 s1800::s760( s1905& s76, bool s714 ) const{
return s1861[s1858->s1833( s76 )];}
void s1800::s863( s750& s153 ) const{
for( auto r : s1861 )
s153.add( r );}
void s1800::s863( s959& s153 ) const{
for( auto r : s1861 )
s153.add( r );}
void s1800::s545( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
size_t s1800::s322() const{
return rechash;}
s1799::s1799( const s1799& r )
: s1782( r.pdb ){}
s1799::s1799( s1781* pdb )
: s1782( pdb ){}
s1799::~s1799(){}
void s1799::s1871( void* f, void* s ){
fi = *( s1784::iterator* )f;
se = *( s1784::iterator* )s;}
void s1799::s1874(){
if( *fi != *s1847 )
cur = fi;
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1799::s1835(){
return (cur != se);}
s1783* s1799::s1845(){
if( s1835() ) {
s1783* s685 = *cur;
cur++;
return s685;}
else
throw new s16( L"Table row iterator is out of range" );}
void s1799::s1831( std::vector<std::wstring>& s153 ){
((s1801*)pdb)->s1832( s153 );}
s1801::s1801( s262* s300, s272* s588, const s263* ast_ )
: s1781( s300, s588, ast_ ){
s493 = Types.Table;
s2042 = 0;}
s1801::s1801( s262* s300, s272* s588, s1905& s77, const s263* ast_ )
: s1781( s300, s588, ast_ ){
s499 = s77;
s493 = Types.Table;
s2042 = 0;}
s1801::s1801( const s1801& right, const s263* ast_ )
: s1781( right.s300, right.ns, ast_ ){
s493 = right.s493;
s2042 = 0;}
s1801::~s1801(){
release();}
s483* 
s1801::s354( const s263& s701, s272* s588, s1905& s334 ) const{
return new s1801( s300, s588, &s701 );}
void s1801::s500( const s272*, bool ){
s1262();}
void s1801::s350(){
s348.insert( make_pair( s7::s1356, new s337( s7::s1356, &s1801::s1236, s1797,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"load-table", new s337( L"load-table", &s1801::s802, s1152,
{ s1122( { Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls", L":firstRowColNames"} ) ) );
s348.insert( make_pair( L"select", new s337( L"select", &s1801::s752, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"query", new s337( L"query", &s1801::s770, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s1801::s333, s1152,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s1801::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"get-row", new s337( L"get-row", &s1801::s2018, 0,
{ s1122( { s1512::s1549 } ) }, 0, 0 ) ) );
s348.insert( make_pair( L"num-cols", new s337( L"num-cols", &s1801::s2026, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"num-rows", new s337( L"num-rows", &s1801::s2027, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( make_pair( L"build-index", new s337( L"build-index", &s1801::s856, s1152,
{ s1122( { Types.String } ) }, 1, 1 ) ) );
s348.equal_range( L"get-row" ).first->second->s1261( true );}
s1061 s1801::s1188( const wstring& s1553, const vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"get-row" )
s685 = s1718;
else
return s336::s1188( s1553, l );
return s685;}
s483* s1801::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1801( s300, s588, L"" );}
inline bool
s1801::s501( const s483* s502 ) const{
return ( ((s1801*)s502)->s352() == s352() );}
s271* s1801::s335( s591* s2057, s272* impl ) const{
return new s1801( *this );}
void s1801::s356( s271* p ) const{
p = new s1801( *this );}
size_t s1801::s322() const{
return (size_t)this;}
bool s1801::operator==( const s483* p ) const{
return ( this == p );}
bool s1801::operator<( const s483* p ) const{
return false;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1801*)(s484*)*s274)
inline void s1801::s1236( s483** s274, size_t s498 ){
s1801* ps = (s1801*)DR;
s1801* s685 = new s1801( ps->s300, ps->ns, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1801::s802( s483** s274, size_t s498 ){
s1801* dr = ( (s1801*)DR );
const wstring& s824 = ((s359*)PARN( 2 ))->s320();
s1720 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par = s274[n];
s472 pc = par->s494();
if( pc == s1063 ) {
s489 rf = par.s15<s371*>();
if( par->s352() == Types.No ) {
if( rf->Id() == s1753 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1751 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1749 ) {
if( s498 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1734 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1750 ) {
tbfr.s1697 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1842 ) {
tbfr.s1826 = true;}
else if( rf->Id() == s1752 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2019 ) {
tbfr.s2014 = true;}}}
else
throw new s16( L"Table::(load-table): unknown parameters" );
++n;}
dr->s718( s824, tbfr );}
inline void s1801::s752( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1801*)DR )->s655( s194 );}
inline void s1801::s770( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1801*)DR )->s655( s194 );}
inline void s1801::s333( s483** s274, size_t s498 ){}
inline void s1801::s2018( s483** s274, size_t s498 ){
s1801* pt = (s1801*)DR;
int n = (int)*PARN( 2 );
const s1800::s1793& row = pt->s2060[n].s15<s1800*>()->s2016();
vector<s271*> v;
for( auto f : row )
v.push_back( f->s335(0,0) );
*s274 = new s959( pt->s300, v, NULL );
( *s274 )->s500( pt->ns );}
inline void s1801::s328( s483** s274, size_t s498 ){}
inline void s1801::s2026( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s1801*)DR )->s806.size();}
inline void s1801::s2027( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s1801*)DR )->rows.size();}
inline void s1801::s856( s483** s274, size_t s498 ){
wstring s858 = PARN( 2 )->to_wstring();
((s1801*)DR)->s855( s858 );}
void s1801::select( const std::wstring& field, s1778::s1791 op, const s483* s1065,
s1787& s153 ){
auto it = s871.find( field );
if( it == s871.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1778::s1851 ) {
s153.pr = it->second.equal_range( (s483*)s1065 );}
else if( op == s1778::s1854 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s483*)s1065 );}
else if( op == s1778::s1855 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s483*)s1065 );}
else if( op == s1778::s1852 ) {
s153.pr.first = it->second.upper_bound( (s483*)s1065 );
s153.pr.second = it->second.end();}
else if( op == s1778::s1855 ) {
s153.pr.first = it->second.lower_bound( (s483*)s1065 );
s153.pr.second = it->second.end();}
else {
assert( 0 );
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}
s153.s977 = field;
s153.dist = std::distance( s153.pr.first, s153.pr.second );}
void s1801::intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ){
s1786::iterator it = fi1.pr.first;
wstring attr2 = fi2.s977;
s1785 s1815;
while( it != fi1.pr.second ) {
s486 attr2v = it->second->s760( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1815 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1815 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s1801::intersect( const s1787& fi, s1782* s153 ){
s1786::iterator it = fi.pr.first;
s1784 s1877;
s1784& s1860 = ((s1799*)s153)->s320();
bool s1824 = s1860.empty();
while( it != fi.pr.second ) {
if( s1824 || std::binary_search( begin( s1860 ), end( s1860 ), it->second, s1802 ) )
s1877.push_back( it->second );
++it;}
s1860.swap( s1877 );}
void s1801::s1870( s1782* s153 ){
s1784::iterator f = begin( rows );
s1784::iterator s = end( rows );
s153->s1871( (void*)&f, (void*)&s );}
size_t s2001( const std::wstring& s824, const s1720& tbfr ){
size_t s685 = 0, st = 0, en = 0, n;
while( en != string::npos ) {
en = s824.find( tbfr.rowSep, st );
n = s4::count( s824, tbfr.s1697, st, en, true );
if( s685 < n ) s685 = n;
st = en + 1;}
return s685;}
void s1801::s718( s1905& s824, const s1720& tbfr ){
wstring s743 = tbfr.s1734;
vector<wstring> s815;
vector<wstring> s825;
size_t pl = 0;
if( s743.size() ) {
s4::s57( s743, tbfr.s1697, s815 );}
else if( tbfr.s2014 ){
pl = s824.find( tbfr.rowSep );
s743 = s824.substr( 0, pl );
if( s743.back() == '\r' )
s743.pop_back();
s4::s57( s743, tbfr.s1697, s815 );
++pl;}
else {
size_t s2022 = s2001( s824, tbfr );
for( size_t n = 0; n < s2022; ++n )
s815.push_back( std::to_wstring( n ) );}
vector<s486> types;
vector<s485> s1772;
if( 0 /*|| !s805.empty()*/ ) {
++pl;
wstring first = s824.substr( pl, s824.find( tbfr.rowSep, pl ) - pl );
s750 s781( s300, ns, first, NULL, tbfr );
s781.s500( ns, true );
s1772 = s781.s320();}
for( size_t n = 0; n < s815.size(); ++n ) {
vector<wstring> s1733;
s4::s57( s815[n], L":", s1733 );
s947 s1771;
s486 ptype;
if( s1733.size() == 2 )
s1771 = new s263( s1733[1] + L"()", NULL, NULL );
else
s1771 = new s263( Types( s300, Types.String )->s353() + L"()", NULL, NULL );
ptype = s300->TR().s518( *s1771, ns, ns->s298() );
types.push_back( ptype );
if( s1733[0][0] != L'@' )
s806.push_back( s1733[0] );
else {
size_t pl = s1733[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1733[0] );
wstring s76 = s1733[0].substr( pl + 1 );
s806.push_back( s76 );}
s1834[s806.back()] = s806.size() - 1;}
s813::Cont s1279;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<"; 
for( size_t n = 0; n < types.size(); ++n ) {
ts += types[n]->s353();
if( n < types.size() - 1 )
ts += L" ";}
ts += L">";
s2042 = ( (s959*)Types( s300, Types.Tuple ) )->s1195( ts, s1279 );
using namespace chrono;
size_t s1819 = pl, /*s69,*/ s1864, s1820, s1827;
vector<s486> s1829( types.size() );
s947 s208 = new s263( L"", L"" );
rows.clear();
s2060.clear();
while( s1819 != string::npos ) {
s1864 = s1819;
s4::s1001( s824, s1864, tbfr.rowSep );
wstring s1822 = s824.substr( s1819, s1864 - s1819 );
s1827 = s1820 = 0;
for( size_t n = 0; n < types.size(); ++n ) {
s1827 = s1820;
s4::s1001( s1822, s1827, tbfr.s1697 );
if( types[n].s14() ) {
s208->s294( L"" );
s208->s1768( s1822.substr( s1820, s1827 - s1820 ) );
if( types[n]->s352() == Types.String && ( s208->s291().front() != L'"' ||
s208->s291().back() != L'"' ) ) {
wstring dqu = L"\"\"";
s208->s1768( dqu.insert( 1, s4::s1828(  s4::s52( s208->s291(), s4::s48 ) , L'"' )));}
s1829[n] = types[n]->s354( *s208, ns, ns->s298() );}
else {
s1829[n] = s365.s15<s483*>();}
s1820 = s1827 + 1;
if( s1827 == string::npos )
break;}
s1819 = s1864 + 1;
s1783* s1809 = new s1800( s1829, this );
rows.push_back( s1809 );
if( s1864 == string::npos || s1819 == s824.size() )
break;}
s2060.assign( rows.begin(), rows.end() );}
void s1801::s855( s1905& s858 ){
auto it = s871.find( s858 );
if( it != end( s871 ) )
s871.erase( it );
s1786& s870 = s871.insert( make_pair( s858, s1786() ) ).first->second;
for( auto it: rows ) {
s486 pd = it->s760( s858 );
if( pd.s14() )
s870.insert( make_pair( pd, it ) );}}
bool s1801::s2010( s1905& s977 ) const{
if( s1834.find( s977 ) != end( s1834 ) )
return true;
return false;}
s1061 s1801::s2015( s1905& s858 ) const{
if( !s2042 )
throw new s16( L"table is empty" );
const s813& s992 = s300->TR().s1013( s2042 );
s1061 s2043 = s992.s352( (1 + s1833( s858 )) * 2 );
return s2043;}
void s1801::release(){
s1781::release();
rows.clear();}
s1782* s1801::s1818() const{
return new s1799( (s1781*)this );}
size_t s1801::s1833( s1905& s1816 ) const{
auto s685 = s1834.find( s1816 );
if( s685 == s1834.end() )
throw new s16( L"table field does not exist: " + s1816 );
return s685->second;}
wstring s1801::to_wstring( uint32_t s1565 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s1801::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Table : " << endl;
for( auto it = begin( rows ); it != end( rows ); ++it ) {}}
s2076::s2076( s486 d )
: rec( d ){}
s2076::~s2076(){}
s486 s2076::s760( s1905& s76, bool s714 ) const{
return rec;}
void s2076::s863( s750& s153 ) const{
s153.add( rec.s15<s271*>() );}
void s2076::s863( s959& s153 ) const{
s153.add( rec.s15<s271*>() );}
void s2076::s545( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
size_t s2076::s322() const{
return rec->s322();}
s2075::s2075( const s2075& r )
: s1782( r.pdb ){}
s2075::s2075( s1781* pdb )
: s1782( pdb ){}
s2075::~s2075(){}
void s2075::s1871( void* f, void* s ){
s2083 = (s326*)f;
started = false;}
void s2075::s1874(){
started = true;
s2081 = s2083->s314( NULL );}
bool s2075::s1835(){
return !s2081->s1979();}
s1783* s2075::s1845(){
if( s1835() ) {
s1783* s685 = NULL;
if( 0 && started ) {
s685 = new s2076( (s483*)s2081->s962() );
started = false;}
else {
s483* s2082 = (s483*)s2081->s315();
if( s2082 )
s685 = new s2076( s2082 );}
return s685;}
else
return NULL;}
void s2075::s1831( std::vector<std::wstring>& s153 ){
((s2062*)pdb)->s1832( s153 );}
s2062::s2062( s262* s300, s272* s588, s326* pv_, const s263* ast_ )
: s1781( s300, s588, ast_ ), s2080( L"col1"), pv( pv_ ){
s493 = pv->s352();
s2042 = pv->ValType();
s2068 = false;}
s2062::s2062( const s2062& r )
: s1781( r ), pv( r.pv ){
s493 = r.s352();
s2042 = r.s2042;
s2068 = false;
s2080 = r.s2080;}
s2062::~s2062(){
release();}
s483* 
s2062::s354( const s263& s701, s272* s588, s1905& s334 ) const{
assert(0);
return 0;}
void s2062::s500( const s272*, bool ){
s1262();}
s483* s2062::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s2062( s300, s588 );}
void s2062::s350(){
assert(0);}
s271* s2062::s335( s591* s2057, s272* impl ) const{
return new s2062( *this );}
void s2062::s356( s271* p ) const{
p = new s2062( *this );}
size_t s2062::s322() const{
return (size_t)this;}
bool s2062::operator==( const s483* p ) const{
return ( this == p );}
bool s2062::operator<( const s483* p ) const{
return false;}
void s2062::select( const std::wstring& field, s1778::s1791 op, const s483* s1065,
s1787& s153 ){
assert( 0 );
s153.s977 = field;
s153.dist = 0;}
void s2062::intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ){
assert( 0 );}
void s2062::intersect( const s1787& fi, s1782* s153 ){
assert( 0 );}
void s2062::s1870( s1782* s153 ){
s153->s1871( (void*)pv, NULL );}
void s2062::s855( s1905& s858 ){
assert( 0 );}
bool s2062::s2010( s1905& s977 ) const{
if( s2080 == s977 )
return true;
return false;}
s1061 s2062::s2015( s1905& s858 ) const{
if( !s2042 )
throw new s16( L"table is empty" );
return s2042;
const s813& s992 = s300->TR().s1013( s2042 );
s1061 s2043 = s992.s352( (1 + s1833( s858 )) * 2 );
return s2043;}
void s2062::release(){
s1781::release();}
s1782* s2062::s1818() const{
return new s2075( (s1781*)this );}
size_t s2062::s1833( s1905& s1816 ) const{
if( s2080 != s1816 )
throw new s16( L"dataset doesn't contain the attribute: '" + s1816 + L"'" );
return 0;}
wstring s2062::to_wstring( uint32_t s1565 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s2062::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Dataset : " << endl;
pv->s304( pd, s197 );}
vector<wstring> s1372 /*= { L"", s1427, s243, s1428, 
s258, s256, 
s900, s2078, s260, s230, s772, 
s821, s252, s244, s852,
s261, s759, s251, s259, 
s257, s818, s1317, s255, 
s233 }*/;
vector<int> BIFuncs1v = {	0, 
0, 0, s1431, s1432, 0, 
0, s1434, s2212, 0, s1435, s1436, 0, 
0,	s1438, s1623, 0, 0, 0,
s1441, s2234, 0, 0, 0, s1443, 
s1887, s1625, 0, 0, s1444, 
s1563, 0, s1446, s1447,	0, 
0, s1449, s1450
};
std::map<std::wstring, int> s1371;
s1987::s1987(){
reset();}
vector<wstring> s1987::s2049;
void s1987::reset(){
memset( s2041, 0, s1984 * sizeof( s1999 ) );
if( s2049.empty() )
s2049 = { s7::s1994, s7::s1997, s7::s1996,
s7::s1995 };}
s1999 s1987::s2003( s1905& s2039 ){
auto it = std::find( begin(s2049), end(s2049), s2039 );
size_t n = std::distance( begin(s2049), it );
if( n == string::npos )
throw new s16( L"unrecognized restriction switch: " + s2039 );
return (s1999)n;}
void s1987::s2056( const s143& s133 ){
for( size_t n = 0; n < s1984; ++n )
if( s2041[n] )
throw new s16( L"Assembly security restrictions have already been set" );
vector<pair<wstring, s142>> s144;
s133.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].first == s7::s1989 )
s2041[s2050] = s2003( s144[n].second->s169() );
else if( s144[n].first == s7::s1990 )
s2041[s2051] = s2003( s144[n].second->s169() );
else if( s144[n].first == s7::s1991 )
s2041[s2052] = s2003( s144[n].second->s169() );
else if( s144[n].first == s7::s1992 )
s2041[s2053] = s2003( s144[n].second->s169() );
else if( s144[n].first == s7::s1988 ) {
s2041[s2050] = s2003( s144[n].second->s169() );
s2041[s2051] = s2003( s144[n].second->s169() );}
else if( s144[n].first == s7::s1993 ) {
for( size_t n = 1; n < s1984; ++n )
s2041[n] = s2003( s144[n].second->s169() );}}}
void s1987::s2013( const std::vector<s1998>* s2034, s1999 sw ) const{
for( size_t n = 0; n < s2034->size(); ++n ) {
s1998 si = (*s2034)[n];
if( s2041[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );}}
bool s1987::s2012( s1998 si, s1999 sw ) const{
if( s2041[si] == s2048 )
return true;
if( s2041[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );
return false;}
s262::s262()
: s272( this, 0, s473, NULL, this, s2200 ), s701( s227, L"", L"global" ),
s200( L"" ), s203( this ), s1319( false ){}
s262::~s262(){}
void s262::reset(){
s628.reset();
s203.s790();
s199.clear();
s701.reset();
s1319 = false;
s2040.reset();}
void s262::s1900( bool soft /*=false*/ )
{
s336::s784( this, soft );
s203.s290();
s206[s7::s434] = s367.s15<s483*>();
s206[s7::s433] = s368.s15<s483*>();
s851( s7::s436, s369.s15<s483*>() );
s851( s7::s437, s370.s15<s483*>() );
s851( s7::s832, s365.s15<s483*>() );
s1405 = new s1404( this, this );
s1403 = new s1402( this, this );
s851( s7::s1391, s1403.s15<s483*>() );
s851( s7::s1392, s1405.s15<s483*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s359* s1473 = new s359( this, os, this );
s851( s7::s1373, s1473 );
if( s1371.empty() ) {
s1372 = { L"", 
s1427, s243, s1428, s258, s1614, 
s256, s900, s2211, s2078, s260, s230, 
s772,
s821, s252, s1615, s244,s1944,
s1616, 
s852,s2232,s261, s1618, s1619, s759, 
s1886, s1617, s1945, s1943, s251, 
s1562,s259, s257, s818, s1620, 
s1317, s255, s233 };
for( size_t n = 1; n < s1372.size(); ++n )
s1371[s1372[n]] = (int)n;}}
static s6::s1695 s1770( L".", L",", true, true, true );
void s262::s202( s1905& s657, s722& s153 ) {
vector<s9<s143>> s662;
s948 s1051 = new s945( s657, true, s1770 );
s1051->read( s662, s7::s418 );
for( size_t n = 0; n < s662.size(); n++ ) {
wstring s658 = s263::s302( *s662[n], s7::s465 );
if( s658 == s7::s453 ) {
if( ( *s662[n] ).s156( s7::s467 ) ) {
const vector<s142>& s162 = ( *s662[n] ).s158( s7::s467 )->s167();
for( size_t n = 0; n < s162.size(); n++ )
s153.s663.push_back( s162[n]->s169() );}
if( ( *s662[n] ).s156( s7::s466 ) )
s153.entry = ( *s662[n] ).s158( s7::s466 )->s857();
if( ( *s662[n] ).s156( s7::s1983 ) ) {
const s143& s133 = (*s662[n]).s158( s7::s1983 )->s166();
s2040.s2056( s133 );}}}
if( s153.s663.empty() )
s153.s663.push_back( s657 );}
wstring s717( s1905& s753, s1905& s756 ){
if( s3::s724( s756 ) )
return s756;
if( !s3::s724( s753 ) )
throw new s16( L"The root path is not absolute: " + s753 );
if( s756.empty() )
return s753;
wstring path = s756;
wstring root = s753;
s4::s61( path );
s4::s61( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s16( L"The relative path '" + s756 + L"' is incompatible with the root '" + s753 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s16( L"The relative path '" + s756 + L"' is incompatible with the root '" + s753 + L"'." );}
return root + path;}
void s262::s213( s1905& s194, const s143& obj ){
const vector<s142>& s729 = ( obj ).s158( s7::s470 )->s167();
const vector<s142>& packs = ( obj ).s158( s7::s739 )->s167();
vector<wstring> s41;
wstring s741 = s194.substr( 0, s194.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s729.size(); n++ )
s41.push_back( s717( s741, s729[n]->s169() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s169();
if( req.rfind( s7::s457 ) == req.size() - s7::s457.size() ) {
if( std::find( s199.begin(), s199.end(), req ) == s199.end() )
s199.push_back( s717( s741, req ) );}
else {
vector<wstring> matches;
for( size_t n = 0; n < s41.size(); n++ ) {
wstring match;
wstring _dir = s41[n];
s4::s61( _dir );
if( s3::s31( _dir, req + s7::s457, match ) )
matches.push_back( match );}
if( matches.empty() ) {
throw new s16( L"The required library '" + req + L"' is not found." );}
else if( matches.size() > 1 ) {
wstring s738;
s4::s289( matches, L",\n", s738 );
throw new s16( L"The required library's name '" + req + L"' is ambiguous: \n" + s738 );}
if( std::find( s199.begin(), s199.end(), matches[0] ) == s199.end() )
s199.push_back( matches[0] );}}}
void s262::s2175( const s143& obj ){
vector<pair<wstring, s142>> s144;
obj.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].first == s7::s465 )
continue;
s947 past = new s263( s144[n].first, *s144[n].second, NULL );
s483* dv = (s483*)s271::s504( *past, s300, (s272*)this, L"::" );
dv->s1262();}}
void s675( s262* s300, s263& s701, s482& s659,
s623& cl, s622& cnl, s624& al ){
s263::s275& s702 = s701.s293();
s263::s275::iterator it = s702.begin();
s536 am = s510;
for( ; it != s702.end(); ++it ) {
s472 pc = s479;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s688;
s4::s57( it->first, L" ", s688 );
if( s688.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
wstring s658 = s688[1];
size_t idx = s688.size() - 2;
if( s688[idx] == s7::s451 )
pc = s478;
else if( s688[idx] == s7::s452 )
pc = s479;
else if( s688[idx] == s7::s2161 )
pc = s2166;
else
throw new s16( L"unknown object type: " + s688[0] );
if( s688.size() == 3 ) {
if( s688[0] == s7::s448 )
am = s509;
else if( s688[0] == s7::s450 )
am = s511;
else if( s688[0] != s7::s449 )
throw new s16( L"invalid access mode name: " + it->first );
s658 = s688[2];}
it->second->s294( s658 );}
s272* ob = new s272( *it->second, s300, pc, s300, am, cl, cnl, al, s2200 );
s659.s541( ob->s299(), ob );}}
void s262::s209( s1905& s661, bool s1902 ){
s722 s646;
s263* s208 = new s263();
wstring s189 = s4::s746( s661 );
if( !s3::s724( s189 )) {
wstring s1897;
if( s1902 ) {
if( s1898.empty() )
throw new s16( L"can't find the file: " + s661 );
s1897 = s1898;}
else
s1897 = s767;
s4::s61( s1897 );
wstring file = s189.substr( s189.rfind( L"/" ) + 1 );
s189 = s717( s1897, s189.substr(0, s189.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s34( s189 );
if( isf == 2 ) {
s4::s61( s189 );
s189 += s7::s460;
if( s767.empty() )
s767 = s661;}
else if( isf == 1 ) {
if( s767.empty() )
s767 = s189.substr( 0, s189.find_last_of( L"\\/" ) );
}
else
throw new s16( L"cannot find file or directory: " + s661,
(uint32_t)s16::s17::s23 );
s4::s61( s767 );
s202( s189, s646 );
size_t s798 = s199.size();
vector<s9<s143>> s662;
for( size_t n = 0; n < s646.s663.size(); n++ ) {
s662.clear();
wstring s664 = s646.s663[n];
if( s664[0] != L'/' && s664[1] != L':' )
s664 = s767 + s664;
s199.push_back( s664 );}
for( size_t n = s798; n < s199.size(); ++n ) {
s662.clear();
s948 s1051 = new s945( s199[n], true, s1770 );
s1051->read( s662, s7::s418 );
for( size_t m = 0; m < s662.size(); m++ ) {
if( s263::s302( *s662[m], s7::s465 ) == s7::s456 )
s213( s199[n], *s662[m] );
else if( s263::s302( *s662[m], s7::s465 ) == s7::s2169 )
s2175( *s662[m] );
else if( s263::s295( *s662[m], s7::s454 ) == s7::s454 ) {
s662[m]->s159( s7::s1124, new s6::s141( L"\"" 
+ s199[n] + 
L"\"" 
), s143::s145::s147 );
s208->s289( *s662[m], m );}}}
s207( *s208 );
if( s1014.s934() )
throw s935( s935::s17::s999 );
s263::s275& s702 = s208->s293();
for( auto it : s702 ) 
s701.s286( it.second );
if( s200.empty() )
s200 = s646.entry;}
void s262::s207( s263& s208 ){
s482 s659;
s624 m1;
s622 s665;
s623 s666;
vector<wstring> s667;
s675( this, s208, s659, s666, s665, m1 );
typedef std::pair<std::wstring, size_t> s2192;
std::sort( s665.begin(), s665.end(), []( const s2192& l, const s2192& r ) { return l.second < r.second; } );
for( size_t n = 0; n < s665.size(); ++n )
s667.push_back( s665[n].first );
for( size_t n = 0; n < s667.size(); ++n )
if( s203.s156( s667[n] ) )
throw new s16( L"class name already exists: " + s667[n] );
for( size_t n = 0; n < s667.size(); ++n )
s203.s218( s666[s667[n]], s666[s667[n]]->s353() );
s628.s289( s659 );
for( size_t n = 0; n < s667.size(); ++n ) {
s487 ob = (s272*)s203.get( s667[n], false );
if( ob )
ob->s154( *m1[s667[n]] );}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s272* ob = (s272*)s659.get( it->first, false );
if( ob && ob->s494() == s479 ) {
try {
ob->s154( *it->second );}
catch( s16* e ) {
e->s30( L"while constructing module: " + it->first );
throw e;}}}
s659.s500( this, false );}
void s262::s211( s143& obj ){
s263 s208;
s208.s289( obj, 0 );
s207( s208 );}
void s262::s1650( s1905& s671 ){
s483* pd = s628.get( s671 );
if( pd->s494() == s479 )
((s272*)pd)->s1649();}
s483* s262::run( const vector<wstring>& s691 ){
if( s200.empty() )
s200 = s7::s459 + L"::" + s7::s458;
if( !s691.empty() ) {
wstring  s672, s671;
s670( s200, s671, s672 );
s272* mod = (s272*)s628.get( s671 );
s813::Cont s1279;
wstring ts = Types( this, Types.Vector )->s353() + L"<" + Types( this, Types.String )->s353() + L">";
s1061 pt = ((s316*)Types( this, Types.Vector ))->s1195( this, ts, s1719, s1279 );
s316* s911 = (s316*) s300->TR().s1007( pt )->s355( this, vector<s484*>( {} ) );
for( size_t n = 0; n < s691.size(); ++n ) {
s911->add( new s359( this, s691[n], this ) );}
mod->s851( s7::s1572, s911 );
mod->s851( s7::s829, new s346( this, (int)s691.size() ) );}
vector<wstring> l;
return callFunc( s200, l );}
s483* s262::callFunc( s1905& s, vector<wstring>& l ){
wstring  s672, s671;
s670( s, s671, s672 );
s272* mod = (s272*)s628.get( s671 );
s488 s673 = (s591*)mod->s641( s672, L"::" );
vector<s485> s274;
for( size_t n = 0; n < l.size(); n++ ) {
s947 ast_ = new s263( l[n], NULL, NULL );
s490 cs = s591::s1119( *ast_, this, mod, mod->s298(), false );
s274.push_back( cs );}
s673->s596( s274 );
s484* pr = s673->s496();
try {
s1319 = false;
if( !pr )
s673->s500( this, false );
else
s673->s597( this );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s673->s299() + L"' function " );}
s1319 = true;
mod->s1649();
s483* s685 = s673->s497();
if( s685->s618() == s7::s440 )
throw new s16( ( (s361*)s685 )->Msg() );
s1319 = false;
return s685;}
s488 s262::getProc( const std::wstring& s ){
wstring  s672, s671;
s670( s, s671, s672 );
s272* mod = (s272*)s628.get( s671 );
s488 s673 = (s591*)mod->s641( s672, L"::" );
s486 pr = s673->s496();
if( !pr )
s673->s500( mod, true );
return s673;}
/*
void s262::s201( const std::wstring& s661 ){
wstring s189 = s661;
wstring s660;
int isf = s3::s34( s661 );
if( isf == 2 ) {
s4::s61( s189 );
s189 += s7::s460;
s660 = s661;}
else if( isf == 1 )
s660 = s189.substr( 0, s189.find_last_of( L"\\/" ) );
else
throw new s16( L"cannot find file or directory: " + s661, 
(uint32_t)s16::s17::s23 );
s4::s61( s660 );
vector<s9<s143>> s662;
s948 s1051 = new s945( s189 );
s1051->read( s662, s7::s418 );
s722 s646;
for( size_t n = 0; n < s662.size(); n++ ) {
wstring s658 = s263::s302( *s662[n], s7::s465 );
if( s658 == s7::s453 ) {
s202( *s662[n], s646 );
break;}}
s200 = s646.entry;
if( s646.s663.empty() )
s646.s663.push_back( s189 );
for( size_t n = 0; n < s646.s663.size(); n++ ) {
s662.clear();
wstring s664 = s646.s663[n];
if( s664[0] != L'/' && s664[1] != L':' )
s664 = s660 + s664;
s948 s1051 = new s945( s664 );
s1051->read( s662, s7::s418 );
for( size_t m = 0; m < s662.size(); m++ )
if( s263::s295( *s662[m], s7::s454 ) == s7::s454 )
s701.s289( *s662[m] );}}
void s262::s202( const s6::s143& obj, s722& s153 ){
const vector<s142>& s162 = obj.s158( s7::s467 )->s167();
for( size_t n = 0; n < s162.size(); n++ )
s153.s663.push_back( s162[n]->s169() );
if( obj.s156( s7::s466 ) )
s153.entry = obj.s158( s7::s466 )->s169();}
*/
void s262::s2013( const std::vector<s1998>* s2034, s1999 sw ) const{
s2040.s2013( s2034, sw );}
bool s262::s2012( s1998 si, s1999 sw ) const{
return s2040.s2012( si, sw );}
s1061 s262::s218( s483* p, s1905& s347 ){
return s203.s218( p, s347 );}
bool s262::s556( s1905& sym_, s371* ref, s1905& s334, bool fr ) const{
if( !s272::s556( sym_, ref, s334, fr ) ) {
if( sym_ == s7::s1572 ) {
ref->s379( s640( s7::s832 ), s365 );
ref->s382( (s483*)this );
return true;}
return false;}
return true;}
bool s262::s221( s371& rf ) const{
rf.s382( NULL );
s205::const_iterator it = s206.find( rf.s617() );
if( it != end( s206 ) ) {
rf.s382( it->second );
return true;}
return false;}
void s262::s219( s1905& s76, s1905& s334,
vector<wstring>& s153 ){
size_t pl = s76.rfind( L"::" );
s272* mod = NULL;
bool bCl = false;
if( s76.find( L"()" ) == s76.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s674 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );}
mod = (s272*)s628.get( s674 );
if( !mod->s642( sym, s334 ) )
throw new s16( L"Symbol '" + s76 + L"' cannot be imported by '" +
s334 + L"'");
s153.push_back( sym );}
else {
if( bCl ) {
wstring sym = s76.substr( 0, s76.size() - 2 );
s203.get( sym );
s153.push_back( sym );}
else {
mod = (s272*) s628.get( s76 );
mod->s639( s334, s153 );}}}
s591* s262::s214( int s1457, 
s561* cs, s272* s588, s591* s215 ){
s591* s685 = NULL;
const s263* s701 = cs->s603();
std::vector<s271*>& s705 = cs->s602();
bool s2177 = cs->s2183();
if( s1457 == s1436 )
s685 = new s608( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1450 )
s685 = new s605( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1625 )
s685 = new s1607( this, s588, s215, s705, s701 );
else if( s1457 == s1430 )
s685 = new s607( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1431 )
s685 = new s1407( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s2079 )
s685 = new s2077( this, s588, s215, s705, s701 );
else if( s1457 == s1947 )
s685 = new s1939( this, s588, s215, s705, s701 );
else if( s1457 == s2212 )
s685 = new s2210( this, s588, s215, s705, s701 );
else if( s1457 == s1449 )
s685 = new s305( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1440 )
s685 = new s606( this, s588, s215, s705, s701 );
else if( s1457 == s1948 || s1457 == s1946)
s685 = new s1940( this, s588, s215, s705, s701 );
else if( s1457 == s1444 || s1457 == s1563)
s685 = new s609( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1433 )
s685 = new s610( this, s588, s215, s705, s701 );
else if( s1457 == s1438 )
s685 = new s838( this, s588, s215, s705, s701, 0, true, s2177 );
else if( s1457 == s1441 || s1457 == s2234 )
s685 = new s839( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1446 )
s685 = new s612( this, s588, s215, s705, s701 );
else if( s1457 == s1445 )
s685 = new s611( this, s588, s215, s705, s701 );
else if( s1457 == s1432 )
s685 = new s613( this, s588, s215, s705, s701 );
else if( s1457 == s1435 )
s685 = new s614( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1442 )
s685 = new s615( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1439 )
s685 = new s797( this, s588, s215, s705, s701 );
else if( s1457 == s1437 )
s685 = new s775( this, s588, s215, s705, s701 );
else if( s1457 == s1448 )
s685 = new s1307( this, s588, s215, s705, s701 );
else if( s1457 == s1628 )
s685 = new s1610( this, s588, s215, s705, s701 );
else if( s1457 == s1447 )
s685 = new s791( this, s588, s215, s705, s701 );
else if( s1457 == s1624 )
s685 = new s1605( this, s588, s215, s705, s701 );
else if( s1457 == s1626 )
s685 = new s1608( this, s588, s215, s705, s701 );
else if( s1457 == s1623 )
s685 = new s1604( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1443 ) {
s685 = new s817( this, s588, s215, s705, s701 );}
else if( s1457 == s1627 )
s685 = new s1609( this, s588, s215, s705, s701 );
else if( s1457 == s1434 )
s685 = new s896( this, s588, s215, s705, s701 );
else if( s1457 == s1622 )
s685 = new s1603( this, s588, s215, s705, s701, s2177 );
else if( s1457 == s1887 )
s685 = new s1885( this, s588, s215, s705, s701 );
return s685;}
s271*
s262::s222( s1905& s76, s1905& s499, bool s520 /*= true*/ )
{
size_t pl = s76.rfind( L"::" );
s485 s685;
if( pl == string::npos ) {
s685 = (s271*)s203.get( s76, s520 );
if( !s685 ) {
s272* exp = (s272*)s203.get( s7::s455, false );
if( exp )
s685 = exp->s641( s76, s499, s520 );}
return s685;}
wstring s674 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
return ((s272*)s203.get( s674 ))->s641( sym, s499 );	}
void* s262::s223( s1905& s278 ){
s336* s685;
s272* exp = (s272*) s628.get( s7::s455, false );
if( exp )
s685 = (s336*)exp->s641( s278, L"", true );
else
throw new s16( L"no such export variable: " + s278 );
void * pv = s685->addr();
return pv;}
void s262::s1351( s1905& s671 ){
s203.s1878( s671 );
s628.s542( s671 );
if( s203.s156( s671) )
s203.s1666( s671 );}
void s262::s1665( s1905& s1633 ){
vector<wstring> s1643;
for( auto it = s628.Table().begin(); it != s628.Table().end(); ++it ) {
s271* p = it->second.s15<s271*>();
if( p->s494() == s479 || p->s494() == s478 || p->s494() == s2166) {
wstring s189 = ( (s272*)p )->s641( s7::s1124, 
L":::" )->to_wstring();
if( s189 == s1633 )
s1643.push_back( it->first );}}
for( auto mod : s1643 )
s1351( mod );
for( size_t n = 0; n < s199.size(); ++n ) {
if( s199[n] == s1633 ) {
s199.erase( s199.begin() + n );
break;}}}
void s262::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << s278 << L" : " << L"Assembly" << endl;
s203.s304( pd, s197 + s419 );
s628.s304( pd, s197 + s419 );}
map<int, s1::s9<s262>> handles;
HPROG createAssembly(){
static int s684 = 0;
s1::s9<s262> p = new s262();
handles[++s684] = p;
p->s1900( false );
return s684;}
void deleteAssembly( int n ){
auto it = handles.find( n );
if( it == end( handles ) )
throw new s2::s16( L"no assembly with such handle" );
handles.erase( it );}
void loadProgram( HPROG handle, const wstring& s189 ){
s262* p = handles[handle];
p->s1891( s3::s1884() );
p->s209( s189, true );}
TDType* getProc( HPROG handle, const std::wstring& s601 ){
s262* p = handles[handle];
return (TDType*)p->getProc( s601 );}
void s211( HPROG handle, s6::s143& obj ){
s262* p = handles[handle];
p->s211( obj );}
TDType* run( HPROG handle, const vector<wstring>& s691 ){
return handles[handle]->run( s691 );}
void* callFunc( HPROG handle, const std::wstring& s77, vector<wstring>& l ){
s262* p = handles[handle];
return p->callFunc( s77, l );}
void evaluateExpression( const std::wstring& s77 ){}
void* s223( HPROG handle, const std::wstring& s278 ){
s262* p = handles[handle];
return p->s223( s278 );}
void* execute( TDType* p ){
return p->s497().s15<s336*>()->addr();}
void importSymbol( HPROG handle, const std::wstring& s1112, const std::wstring& symName,
const std::wstring& s334 ){
s262* p = handles[handle];
s272* ob = (s272*)p->s641( s1112, s334 );
ob->s555( symName, s334 );}
void importFile( HPROG handle, const std::wstring& s1112, const std::wstring& s44,
const std::wstring& s334 ){
vector<s1::s9<s6::s143>> s662;
s6::s945 s1051( s44 );
s1051.read( s662, s7::s418 );
s262* p = handles[handle];
p->s209( s44 );
s272* ob = (s272*)p->s641( s1112, s334 );
for( size_t n = 0; n < s662.size(); n++ ) {
wstring s658 = s263::s302( *s662[n], s7::s465 );
ob->s555( s658, s334 );}}
HPROG initShell( const std::wstring& s1112, const std::wstring& modText ){
s1::s9<s6::s143> ob = new s6::s143(NULL);
size_t pos = 0;
s6::s1695 s1770( L".", L",", true, true, true );
s6::s945 s1051( L"", true, s1770 );
s1051.s170( modText, pos, ob );
ob->s159( s7::s465, new s6::s141( s1112 ) );
HPROG prog = createAssembly();
s211( prog, *ob );
return prog;}
} // namespace transd
