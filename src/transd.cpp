
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
std::vector<std::wstring> s998 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1123(){
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
wstring s1886(){
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
wstring s1886(){
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
size_t& start, size_t& end, bool s887/*=false*/ )
{
end = string::npos;
start = string::npos;
int s66 = 0;
wchar_t s876 = 0;
bool esc = false;
for( size_t n = s65; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s876 || !s887 ) {
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
else if( s887 && ( c == L'\'' || c == L'\"' ) ) {
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
void s1003( const std::wstring& s, size_t& s65, const std::wstring& s1884 ){
size_t s1882 = s65, s1883;
wstring s1344 = s1884 + L"\"";
s65 = string::npos;
bool s1885 = false;
while( true ) {
s1883 = s1882;
s1882 = s.find_first_of( s1344, s1882 );
if( s1882 == string::npos ) {
if( s1885 )
throw new s2::s16( L"no closing parenthesis: " + s.substr(s1883, 20) );
return;}
if( s[s1882] == L'\"' ) {
if( ! (s1882 && s[s1882-1] == '\\' ))
s1885 = !s1885;}
else{
if( !s1885 ) {
s65 = s1882;
return;}}
++s1882;}
return;
size_t pl = s.find_first_of( s1344, s65 );
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
pl = s.find_first_of( s1344, pl );}
else {
s65 = pl;
return;}}}
void s1329( const std::wstring& s, size_t& s65, const std::wstring& s1092 ){
size_t pl = s.find( s1092, s65 );
if( pl == s65 )
return;
size_t start = s65;
s65 = string::npos;
while( pl < s.size() ) {
if( s1092.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1092.size();
if( pl < s.size() )
pl = s.find( s1092, pl );}
else {
s65 = pl;
return;}}}
size_t count( const std::wstring& s77, const std::wstring& s1092, size_t start, size_t end,
bool s887 ){
size_t s685 = 0;
size_t pl = s77.find( s1092, start );
while( pl < s77.size() && pl <= end) {
if( s887 && pl && s77[pl-1] == '\\' ) {
++pl;}
else {
++s685;
pl += s1092.size();}
if( pl < s77.size() - 1 ) 
pl = s77.find( s1092, pl );}
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
bool s1546( const wchar_t *str, long long *s349, wchar_t **end /*= NULL*/ )
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
bool s1547( const wchar_t *str, unsigned long long *s349, wchar_t **end /*= NULL*/ )
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
std::wstring s1830( const std::wstring& s77, wchar_t c ){
size_t pl = s77.find( c ), s1852 = 0, s1823 = 0, s1846;
if( pl == string::npos )
return s77;
wstring s685( s77.size() + 100, L'\0' );
while( pl != string::npos ) { 
s1846 = pl - s1852;
if( s685.size() < s1823 + s1846 + 2 )
s685.resize( (std::max)((size_t)(s685.size()*1.1), s685.size()+100) );
memcpy( (void*)(s685.c_str() + s1823), s77.c_str() + s1852, s1846 * sizeof(wchar_t) );
s685[s1823 + s1846] = L'\\';
s685[s1823 + s1846 + 1] = s77[pl];
s1823 = s1823 + s1846 + 2;
s1852 = pl + 1;
pl = s77.find( c, pl + 1 );}
s1846 = s77.size() - s1852;
memcpy( (void*)(s685.c_str() + s1823), s77.c_str() + s1852, s1846 * sizeof(wchar_t) );
s685.resize( s1823 + s1846/* + 1*/ );
return s685;}
void s57( const wstring& s, const wstring& s72, vector<wstring>& s153, bool clr,
bool s887 ){
size_t s68 = 0, s69 = 0;
while( s69 != wstring::npos && s68 < s.size()) {
if( s887 ) {
s69 = s68;
s4::s1003( s, s69, s72 );}
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
void s81( wstring& s77, vector<wstring>& s1106, map<size_t, size_t>& s1039 ){
size_t pos = 0;
wchar_t s82 = 0;
bool s1167 = false;
wchar_t s83 = 0;
bool s84 = false;
bool s85 = false;
size_t s86 = string::npos;
bool s87 = false;
bool s982 = false;
wstring s88 = L"`'\"";
s1106.reserve( 1000 );
size_t s1034 = 1;
bool s974 = false;
while( pos < s77.size() ) {
wchar_t c = s77[pos];
if( c == '\r' ) {
s77.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1167 = !s1167;}
else if( s82 ) {
if( c == s82 && !s1167 /*s83 != '\\'*/ )
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
s1039[pos - 2] = s1034;}}
else if( c == '/' ) {
if( !s84 && s83 == '/' ) {
s86 = pos - 1;
s84 = true;
s85 = false;
if( pos > 1 && s77[pos - 2] != '\n')
s1039[pos - 2] = s1034;}
else if( s85 && s83 == '*' ) {
s87 = true;
if( s77[pos+1] == '\n' ){
s974 = true;}}}
else if( c == '\n' ) {
s974 = true;
if( s84 ) {
if( !s85 ) {
s87 = true;}
else {
if( !s982 ) {
s982 = true;}}}
else {
if( pos && s77[pos-1] != '\n' ) {
s1039[pos - 1] = s1034;}}}
if( c != L'\\' )
s1167 = false;
if( s974 ) {
size_t pl = s77.rfind( '\n', pos - 1 );
size_t m = (s77[pos] == '\n');
if( pl == string::npos )
s1106.push_back( s77.substr( 0, pos ) );
else
s1106.push_back( s77.substr( pl + 1, pos - pl - m ) );
s974 = false;
s1034++;}
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
s982 = false;
s85 = false;
s87 = false;
s83 = 0;}
s83 = c;
pos++;}
if( s84 ) {
auto it = end(s1039);
if( s1039.size() ) it--; 
size_t ln = (it == end(s1039) ? 0 : it->second);
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
uint32_t s17::s89;
void s17::s29(){
s89 = s16::s28();}
void s1119(){
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
size_t s1113 = s118.size();
size_t s119 = s1113;
while( s588 ) {
s117 = _getch();
switch( s117 ) {
case s110:
if( s1113 > s119 ) {
wcout << '\r' << s118.substr( 0, --s1113 );}
break;
case s111:
if( s1113 < s118.size() )
wcout << s118[s1113++];
break;
case s108:
case s109:
continue;
case s114:
if( ( s1113 > s119 ) && s118.size() ) {
s118.erase( --s1113, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}
break;
case s115:
if( s1113 < s118.size() ) {
s118.erase( s1113, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}
break;
case s113:
s588 = false;
break;
case s116:
break;
default:
if( s1113 < s118.size() )
s118.insert( s1113, 1, s117 );
else
s118 += s117;
++s1113;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}}
return s118;}
wstring getStringValHist( const wstring& s93, const vector<wstring>& s102 ){
wcout << s93;// << endl;
int s117 = 0;
size_t s684 = s102.size();
bool s588 = true;
wstring s118 = s93;
size_t s1890 = s93.size();
size_t s1113 = s1890;
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
else if( s117 == 70 ) s117 = s1559;
else if( s117 == 72 ) s117 = s1560;
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
else if( s117 == 71 ) s117 = s1560; // G
else if( s117 == 79 ) s117 = s1559; // O
}
#endif			
switch( s117 ) {
case s110:
if( s1113 > s1890 ) {
wcout << '\r' << s118.substr( 0, --s1113 );}
break;
case s111:
if( s1113 < s118.size() )
wcout << s118[s1113++];
break;
case s108:
if( s684 > 0 ) {
if( s684 < s102.size() )
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[--s684];
wcout << '\r' << s118;
s1113 = s118.size();}
break;
case s109:
if( !s102.empty() && s684 < s102.size() - 1 ) {
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[++s684];
wcout << '\r' << s118;
s1113 = s118.size();}
break;
case s114:
if( s1113 > s1890 && s118.size() > s1890 ) {
s118.erase( --s1113, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}
break;
case s115:
if( s1113 < s118.size() ) {
s118.erase( s1113, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}
break;
case s1560:
if( s1113 > 0 ) {
wcout << '\r' << s93;
s1113 = s1890;}
break;
case s1559:
if( s1113 < s118.size() ) {
wcout << '\r' << s118;
s1113 = s118.size();}
break;
case s113:
s588 = false;
break;
case s116:
break;
default:
if( s1113 < s118.size() )
s118.insert( s1113, 1, s117 );
else
s118 += s117;
++s1113;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1113 );}}
return s118.substr( s1890 );}
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
wstring s1540 = L"0123456789";
wstring s1541 = L".0123456789";
wstring s186 = L" ,]}\t\r\n";
s1697 s1759;
thread_local std::list<bool> s1771;
void s1700( const wstring& dd, const wstring& fs, bool ab, bool rb, bool sb ){
s1759 = s1697( dd, fs, ab, rb, sb );}
void s1700( const s1697& cnf ){
s1759 = cnf;}
void s947::s170( const wstring& s77, size_t& pos, s9<s143> ob ){
size_t s74, s75;
s54( s77, pos, L'{', L'}', s74, s75, true );
if( s74 == string::npos )
return;
s1061 = s74 - 1;
wstring sob = s77.substr( s74, s75 - s74 + 1 );
pos = s75 + 1;
try {
s1771.push_back( s1762.s151 );
ob->s154( sob, s1762 );
s1771.pop_back();}
catch( s16* e ) {
s1771.pop_back();
e->s30( L"during reading the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s947::s1007( wstring& s, size_t s68, size_t s683, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1118.lower_bound( s68 );
auto iten = s1118.lower_bound( s683 );
if( itst == end(s1118) || iten == end(s1118) )
return false;
line = itst->second;
s = s1117[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1117[iten->second-1];
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
s947::s947( const std::wstring& file, bool s1636, const s1697& s1761 )
: s1762( s1761 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s48 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1636 == false )
s1116 = file;
else
s194 = file;}
void s947::read( vector<s9<s143>>& s153, const wstring& s190 ){
size_t pos = 0;
if( s194.size() ) {
std::ifstream fs( TOFS( s194 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s194 ));
string s191( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1116 = conv.from_bytes( s191 );
s4::s81( s1116, s1117, s1118 );
if( s190.size() ) {
pos = s1116.find( s190 );
if( pos == string::npos )
throw new s16( s190 + L" directive not found in the source file." );
pos += s190.size() + 1;
if( s1116.size() > 13 && s1116[14] == '\r' )
++pos;}}
size_t s192 = pos;
wstring s278;
bool s193 = false;
while( ( pos = s1116.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1116.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s192; subl = pos - s192;}
else
pl += 1;
wstring s1 = s52( s1116.substr( pl, /*pos - pl - 1*/subl ), s48 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s193 = true;
else
s278 = s52( s1, s48 + L":" );}
if( s278.empty() ) {
size_t pl1 = s1116.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s52( s1116.substr( pl1, pl ), s48 );
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
s1771.push_back( s1762.s151 );
s170( s1116, pos, ob );
s1771.pop_back();}
catch( s16* e ) {
s1771.pop_back();
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
if( s1771.back() )
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
if( s[s.size()-1] != q )
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
void s175( const wstring& s77, size_t& pos, wchar_t s1209, wchar_t s1252, wstring& s153 ){
size_t s74, s75;
s54( s77, pos, s1209, s1252, s74, s75, true );
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
s131 s176( const wstring& s77, size_t& pos, wstring& s153, const s1697& s1761 ){
if( s77[pos] == s1761.s1699[0] && s1761.s1746) {
s153 = L"";
return s132;}
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"empty element or unrecognized unquoted syntax: " + s77.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s196 = pos;
int shift = 0;
if( s77[pos] == L'(' && s1761.s1701) {
s175( s77, s196, L'(', L')', s153 );
if( s196 == s77.size() - 1 )
shift = 1;}
else {
s196 = pos + 1;
while( std::isgraph<wchar_t>( s77[s196], locloc ) &&
s77[s196] != L':' && s77[s196] != L',' ) {
if( s77[s196] == L'<'  && s1761.s1702 ) {
s175( s77, s196, L'<', L'>', s153 );}
else if( s77[s196] == L'(' && s1761.s1701 ) {
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
void s178( const s947* pf, const wstring& s77, vector<s9<s141>>& s153, 
const s1697& s1761 ){
size_t s68 = s77.find_first_not_of( s48 );
s1771.push_back( s1761.s1734 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, s77, s68, s1761 ) ) );
s4::s1003( s77, s68, s1761.s1699 );
if( s68 == string::npos )
break;
++s68;}
s1771.pop_back();}
void s178( const s947* pf, const wstring& s77, size_t& pos,
vector<s9<s141>>& s153, const s1697& s1761 ){
size_t s74, s75, s68 = 0;
s54( s77, pos, L'[', L']', s74, s75, true );
pos = s75 + 1;
wstring ar = s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 );
if( ar.empty() )
return;
s1771.push_back( s1761.s1734 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, ar, s68, s1761 ) ) );
s4::s1003( ar, s68, s1761.s1699 );
if( s68 == string::npos )
break;
++s68;}
s1771.pop_back();}
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
while( s77[s196] != L':' && s77[s196] != L',' ) {
if( !std::isalnum<wchar_t>( s77[s196], locloc ) &&
!std::isspace<wchar_t>( s77[s196], locloc ) && s77[s196] != L'_' &&
s77[s196] != L'-' )
throw new s16( L"unrecognized name syntax: " + s77.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
++s196;}
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
s131 s1552( const wstring& s77, size_t& pos, double& s153, const s1697& s1761 ){
const wchar_t* ps = s77.c_str();
size_t sz = s77.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1541.find( ps[st+1] ) == string::npos )
return s132;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1540.find( ps[st+1] ) != string::npos ) ||
( s1540.find( ps[st] ) == string::npos ) )
return s132;
size_t s684 = st;
bool pt = false;
while( s684 < sz ) {
if( ps[s684] == s1761.s1698[0] ) {
if( pt ) return s132;
pt = true;
s684++;}
else if( s1540.find( ps[s684] ) != string::npos )
s684++;
else if( (s48 + s1761.s1699).find( ps[s684] ) != string::npos  )
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
s141::s141( const s947* pf, const wstring& s77, size_t& pos, const s1697& s1761 )
: s198( s132 ), obj( pf ), s1084( pos + (pf ? pf->s951():0), 0 ), s1083( (s947*)pf ){
size_t s68 = s77.find_first_not_of( L" \n\r\t", pos );
if( s68 == string::npos ) {
if( s1761.s1746 )
s198 = s132;
else {
s16* s970 = new s16(wstring( 28, L' ' ) + L"|^|" );
s970->s30( L"empty array item: " + s77.substr( pos - 10, 20 ) );
throw s970;}}
else if( s77[s68] == L'{' ) {
size_t s74, s75;
s54( s77, s68, L'{', L'}', s74, s75, true );
pos = s75+1;
obj.s154( s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 ), s1761 );
s198 = s133;}
else {
pos = s68;
if ( s88.find( s77[pos] ) != string::npos ) {
s172( s77, pos, s77[pos], str, s1761.s151 );
s198 = s139;}
else if ( s77[pos] == L'[' ) {
s178( (s947*)s1083, s77, pos, s162, s1761 ); 
s198 = s135;}
else {
s198 = s1552( s77, pos, s163, s1761 );
if( s198 != s132 )
(void)0;
else if( s183( s77, pos, b ) )
s198 = s137;
else if( s184( s77, pos ) )
s198 = s138;
else
s198 = s176( s77, pos, str, s1761 );;}}
s1084.second = pf ? pos - 1 + pf->s951() : 0;}
bool s141::s1011( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1084.first || s1083.s13() )
return false;
f = s1083->Path();
s1083->s1007( s, s1084.first, s1084.second, line );
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
void s143::s154( const wstring& s77, const s1697& s1761 ){
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
s180( s77, s68, s76, s1761.s151 );
size_t pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl == string::npos || s77[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
s68 = pl + 1;
s144.insert( make_pair( s76, new s141( src, s77, s68, s1761 ) ) );
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
void s143::s1633( const std::wstring& s76 ){
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
s131 s1711::s1552( const std::wstring& s77, size_t& pos, double& s153 ){
return s6::s1552( s77, pos, s153, conf );}
} // namespace s6
using namespace s6;
namespace transd {
namespace s7 {
s930 s1556		= 0x80000000;
s930 s1397        = s1556 - 1;
s930 s1398       = s1556 - 2;
s930 s1399       = s1556 - 3;
s930 s1396      = s1556 - 4;
s930 s1395						= s1556 - 8;
s930 s1400    = s1556 - 9;
s930 s1401					= s1556 - 10;
DEFCONST s420 = L"typeMembers";
DEFCONST s421 = L"typeMember";
DEFCONST s422 = L"typeMethods";
DEFCONST s423 = L"typeMethod";
DEFCONST s424 = L"members";
DEFCONST s425 = L"member";
DEFCONST s426 = L"methods";
DEFCONST s427 = L"method";
DEFCONST s428 = L"@init";
DEFCONST s429 = L"initCall";
DEFCONST s1631 = L"@to-String";
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
DEFCONST s942 = L"->";
DEFCONST s1142 = L"const";
DEFCONST s1358 = L"new";
DEFCONST s1393 = L"stdin";
DEFCONST s1394 = L"stdout";
DEFCONST s1603 = L"this";
DEFCONSTI s866 = -1;
DEFCONSTI s440 = -2;
DEFCONSTI s438 = -100;
DEFCONSTI s439 = -101;
DEFCONSTI s441 = 1;
DEFCONSTI s442 = 0;
DEFCONSTI s868 = 0x80000000;
DEFCONSTI s1749 = 0x80000001;
DEFCONSTI s867 = 0;
DEFCONSTI s1201 = 1;
DEFCONST s1415 = L":Number";
DEFCONST s1526 = L":Integer";
DEFCONST s1413 = L":IterableForw";
DEFCONST s1412 = L":IterableBidir";
DEFCONST s1414 = L":IterableRand";
DEFCONST s1411 = L":IStream";
DEFCONST s1416 = L":OStream";
DEFCONST s1410 = L":IOStream";
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
DEFCONST s453 = L"AssemblyDescription";
DEFCONST s454 = L"ProgramText";
DEFCONST s455 = L"Export";
DEFCONST s456 = L"Require";
DEFCONST s457 = L".td";
DEFCONST s948 = L".tsd";
DEFCONST s459 = L"MainModule";
DEFCONST s458 = L"_start";
DEFCONST s460 = L"asm" + s457;
DEFCONST s461 = L"@ex";
DEFCONST s1376 = L"@it";
DEFCONST s462 = L"@idx";
DEFCONST s1984 = L"@row";
DEFCONST s769 = L"@pars";
DEFCONST s803 = L"@obj";
DEFCONST s829 = L"@numArgs";
DEFCONST s1574 = L"@progArgs";
DEFCONST s1126 = L"@sourceFile";
DEFCONST s1375 = L"@OS_Type";
DEFCONST s467 = L"source";
DEFCONST s463 = L"objectType";
DEFCONST s464 = L"moduleType";
DEFCONST s465 = L"@name";
DEFCONST s466 = L"entryPoint";
DEFCONST s468 = L"perm";
DEFCONST s469 = L"extends";
DEFCONST s739 = L"packages";
DEFCONST s470 = L"searchDirs";
DEFCONST s938 = L"@attrs";
DEFCONST s1985 = L"restrictions";
DEFCONST s1991 = L"FileRead";
DEFCONST s1992 = L"FileWrite";
DEFCONST s1990 = L"FileAll";
DEFCONST s1993 = L"FuncEval";
DEFCONST s1994 = L"FuncStartProcess";
DEFCONST s1995 = L"RestrictionsAll";
DEFCONST s1996 = L"allow";
DEFCONST s1999 = L"noResult";
DEFCONST s1998 = L"noExecute";
DEFCONST s1997 = L"noCompile";
DEFCONST s917 = L"is";
DEFCONST s916 = L"index type";
DEFCONST s918 = L"value type";
DEFCONST s418 = L"#lang transd";
DEFCONST s1108 = L"#format tsd";
s930 s1302						= 103;
s930 s1367					= 104;
s930 s925						= 110;
s930 s1301				=	123;
s930 s1131						= 124;
s930 s926 			=	125;
s930 s920			= 201;
s930 s1109				= 204;
s930 s921					= 210;
s930 s1110					= 304;
s930 s1111				= 404;
s930 s1112				= 504;
s930 s922					= 510;
s930 s923			= 511;
s930 s924					= 610;
s930 s1128							= 710;
s930 s1129					= 711;
s930 s1368		= 804;
s930 s1369				= 904;
s930 s1370				= 1004;
s930 s1599					= 1024;
s930 s1130					= 1124;
s930 s1298				= 1203;
s930 s1299				= 1210;
s930 s1300				= 1224;
s930 s1669		= 1304;
s930 s1670						= 1404;
s930 s1380						= 1410;
s930 s1671						= 1504;
s930 s1378						= 1510;
s930 s1379					= 1511;
s930 s1672				= 1604;
s930 s1524					= 1610;
s930 s1525			= 1611;
s930 s1689			= 1704;
s930 s1557			= 1710;
s930 s1601	= 1715;
s930 s1906	= 1716;
s930 s1600				= 1824;
s930 s1690					= 1904;
s930 s1704				= 2025;
s930 s1894				= 2103;
s930 s1939				= 2210;
s930 s1938					= 2310;
set<wstring> s1125 = { s1126, s1393, s1394, s1375, s833, s433,
s434, s435, s765, s749, s795, s436, s437, s832, s942, s1142,
s1358, s1393, s1394, s1603, L"and", L"or"
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
const wstring s245 = L"dcmp";
const wstring s246 = L"dcmpr";
const wstring s247 = L"mod";
const wstring s248 = L"sqrt";
const wstring s249 = L"abs";
const wstring s250 = L"pow";
const wstring s1947 = L"textin";
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
const wstring s1622 = L"unload-file-modules";
const wstring s1319 = L"unload-module";
const wstring s751 = L"has-field";
const wstring s818 = L"tsd-query";
const wstring s759 = L"substr";
const wstring s852 = L"ret";
const wstring s853 = L"sort";
const wstring s902 = L"exit";
const wstring s1318 = L"to-file";
const wstring s1430 = L"any";
const wstring s1429 = L"all";
const wstring s1946 = L"pipe";
const wstring s1564 = L"lout";
const wstring s1945 = L"lin";
const wstring s1618 = L"read-tsd-file";
const wstring s1617 = L"load-from-object";
const wstring s1621 = L"start-process";
const wstring s1619 = L"rebind";
const wstring s1620 = L"sleep";
const wstring s1616 = L"diag";
const wstring s1888 = L"rand";
const std::wstring s265 = L"AttrNA";
s263::s263( const std::wstring& s, const s141* s6 )
: s1055( (s141*)s6 ){
s1005( s );}
s263::s263( const std::wstring& s676, const s6::s141& s296 )
: s278( s676 ), s1055( (s141*)&s296 ){
if( s296.s164() == s134 ) {
wstring s = s296.s169();
s1005( s );}
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
if( s278.find( L"UVector" ) == 0 ) {
s284( L"UVector" + ss.str() );
s278 = s4::s52( s278.substr( 7 ), s48 );}
else
s284( ss.str() );}
else if( s296.s164() == s132 )
s284( L"" );
else
throw new s16( L"Unhandled nqj variant: " + to_wstring( s296.s164() ) );}
s263::s263( const s6::s143& s133 ){
s283( s133 );}
s263::~s263(){
reset();}
void s263::reset(){
s281.clear();
s266.clear();
s277 = s278 = s280 = src = L"";}
void s263::s1005( const wstring& s ){
size_t pos = 0;
wstring s1186 = L"\"'-+[{<";
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
else if( iswdigit( s[pos] ) || s1186.find( s[pos] ) != string::npos ) {
wstring s77;
s77 = s52( s, s48 );
s284( s77 );}
else
throw new s16( L"Unknown string content: " + s );}
void s263::s282( const std::wstring& s77 ){
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
s281.insert( make_pair( to_wstring( n - 1 ), new s263( s677[n], s1055 ) ) );}
void s263::s284( const std::wstring& s77 ){
src = s77;
s279 = s225;
s280 = s77;}
void s263::s285( const std::wstring& s77 ){
src = s77;
s279 = s228;
s280 = s77;}
void s263::s283( const s6::s143& s133 ){
s278 = s302( s133, s7::s465 );
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
void s263::s289( s6::s143& obj ){
wstring s679 = s4::s52( s302( obj, s7::s465 ), s48 );
wstring s658 = s679;
s678( s658 );
if( s658.empty() )
throw new s16( L"Nameless blocks are forbidden." );
if( s658 != s679 )
obj.s159( s7::s465, s142(new s141( s658 )), s143::s147 );
if( s658 == s278 ) { // partial definition
vector<pair<wstring, s142>> s144;
obj.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n )
s286( s144[n].first, *s144[n].second );}
else {
s281.insert( make_pair( s658, new s263( obj ) ) );}}
void s263::s286( s263* node ){
s281.insert( make_pair( node->s299(), node ) );}
void s263::s286( const std::wstring& s278, const s141& s349 ){
s281.insert( make_pair( s278, new s263( s278, s349 ) ) );}
void s263::s290( s262* s300, size_t s301 /*= 0*/ )
{
s275::iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
if( it->second->s297() == s227 ) {
if( s301 == 0 ) {
it->second->s290( s300, 1 );}
else {}}}}
const s263* s263::s292( const std::wstring& s278 ) const{
size_t s684 = s281.count( s278 );
if( s684 > 1 )
throw new s16( L"multiple values: " + s278, (uint32_t)s149 );
if( s684 == 1 ) {
auto s685 = s281.find( s278 );
return s685->second.s15<s263*>();}
throw new s16( L"node not found: " + s278, (uint32_t)s16::s17::s23 );
s275::const_iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
try {
const s263* s685 = it->second->s292( s278 );
return s685;}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s23 )
continue;
throw e;}}
throw new s16( L"node not found: " + s278, (uint32_t)s16::s17::s23 );}
void s263::s288( const wstring& s77, size_t& pos, vector<wstring>& s153 ){
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
else if( s77[s68] == L'"' ) {
s55( s77, s68, L'"',
s681, s682 );
if( s682 == string::npos )
throw new s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s680 = s77.substr( s68, s682 - s68 + 1 );
s683 = s682 + 1;}
else if( iswdigit( s77[s68] ) ) {
s682 = s77.find_first_of( s48 + L")", s68 );
s680 = s77.substr( s68, s682 - s68 );
s683 = s682;}
else if( iswalpha( s77[s68] ) || s77[s68] == L'_' ) {
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
size_t s1731 = s77.find( L"<" );
if( s1731 != string::npos && s1731 > 0 ) {
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
s685 = s1946;
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
return (s277.size() ? s277 + L"::" : L"") + s278;}
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
const std::wstring& s263::s268( const std::wstring& s303 ) const{
auto it = s266.find( s303 );
if( it != s266.end() )
return it->second;
return s265;}
void s263::s269( const std::wstring& s303, const std::wstring& s267 ){
s266[s303] = s267;}
void s263::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s278 << L" : " << s229[s279] << endl;
buf << s4::fill_n_ch( L' ', s197 ) << L" " << s280 << endl;
map<wstring, s949>::const_iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << it->first << endl;
it->second->s304( pd, s197 + s419 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1107 s1016;
void s1107::s973( const std::wstring& s78 ){
++s999;
s26.push_back( Msg( s78 ) );
wcout << s78;}
void s1107::s973( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
++s999;
s26.push_back( Msg( s78, U16(func), U16(file), line, s1043 ) );}
void s1107::s975( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s78, U16(func), U16(file), line, s1046 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1087 = {
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
TDException::TDException( uint32_t s1017, uint32_t cat, const s263* ast_ )
: s16( L"", s1017 ), stage (Stage::s1033 ), category( cat ), s701( (s263*)ast_ ){}
TDException::TDException( Stage stg, uint32_t s1017, uint32_t cat, const s263* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s701( (s263*)ast_ ){
if( category ) {
s30( L"error code: " + std::to_wstring( s1017 ) );
s30( s996[category] + L":" );}}
TDException::TDException( uint32_t s1017, uint32_t cat, const s263* ast_, const std::wstring& s78 )
: s16( s78, s1017 ), stage (Stage::s1033 ), category( cat ), s701( (s263*)ast_ ){
if( category ) {
s30( s996[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1089( e.s1089 ), s701( e.s701 ){}
TDException* TDException::s1002( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s197 ) const{
wstring src;
if( s701.s14() )
src = s1914( *s701 );
wstring s = L"Error ";
if( id ) {
wstring s1079;
if( (uint32_t)stage )
s1079 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1079 += std::to_wstring( id );
s += s1079;}
if( (uint32_t)stage ) {
s += L" during " + s1087[(uint32_t)stage];}
s += src + L"\n";
return wstring( s197, L' ' ) + s + s16::Msg( s197 + 2 );}
wstring TDException::s1914( const s263& s701 ){
size_t s1035 = 0;
wstring file, s1085, s685;
if( s701.Nqj() && s701.Nqj()->s1011( file, s1085, s1035 ) ) {
wstring s1081 = std::to_wstring( s1035 ) + L": '" + s1085 + L"'";
s685 = L"\n  in file: " + file + L"\n  on line " + s1081;}
if( !s701.s291().empty() )
s685 += L"\n  object: '" + s701.s291() + L"', ";
if( !s701.Src().empty() )
s685 += L"code: '" + s701.Src() + L"', ";
return s685;}
s929::s929( s16& e, const s263& s701, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1035 = 0;
wstring file, s1085, src;
wstring	s78 = L"Error during ";
if( s701.Nqj()->s1011( file, s1085, s1035 ) ) {
src = std::to_wstring( s1035 ) + L": '" + s1085 + L"'";
s78 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s78 += L"object: '" + s701.s291() + L"'; code: " + s701.Src();}
s30( s78 );
s1016.s973( Msg( 2 ) );}
s937::s937( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s996 = {
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
if( s7::s1125.find( s ) != s7::s1125.end() )
continue;
fail = true;
break;}
if( fail && s714 )
throw new s16( L"illegal identifier: " + s );
return (!fail);}
} // namespace tdlang
s928 s995;
s271::~s271(){}
s483* s271::s496()
{	throw std::logic_error( "1: not implemented" );}
const s483* s271::s503() const
{	throw std::logic_error( "2: not implemented" );}
s486 s271::s497( s483** s274, size_t s498 )
{	throw std::logic_error( "3: not implemented" ); }
s271* s271::s335() const
{	throw std::logic_error( "4: not implemented" ); }
void s271::s500( const s272* s587, bool b ) {
(void)0;}
inline bool
s271::s501( const s483* s502 ) const{
return ( s502->s352() == s352() );}
inline bool
s271::s1543( s1063 s619 ) const{
return s300->TR().s1536( s352(), s619 );}
const s813& 
s271::s1198() const {
return s300->TR().s1015( s493 ); }
s271::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s271::operator int() const { throw std::logic_error( "6: not implemented" ); }
s271::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s271::to_wstring( uint32_t s1567 ) const { throw std::logic_error( "8: not implemented" ); }
s1324 s271::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s271::to_null() { s1681( s7::s1749 ); }
void s271::s1335( const s263& ast_, s262* s300, s272* obj,
s1907& s334, vector<s271*>& s153 ){
size_t pos = 0;
vector<wstring> s677;
wstring s77 = ast_.s291();
if( s77.empty() )
return;
/*wstring s = s77;
if( s[0] != L'(' )
s = L"(" + s + L")";*/
s263::s288( s77.substr( s77.find( L"(" ) ), pos, s677 );
if( s677.empty() )
return;
for( size_t n = 0; n < s677.size(); n++ ) {
s263* ast1 = new s263( s677[n], ast_.Nqj() );
s153.push_back(
s271::s504( *ast1, s300, obj, s334 )
);}}
s271* s271::s504( const s263& s701, s262* s300, s272* obj,
s1907& s334 ){
TDException s970( s7::s1704, s934, &s701 );
s271* p;
if( s701.s297() == s225 ) {
wstring s349 = s701.s291();
bool quot = s88.find( s349[0] ) != string::npos;
size_t ppl = s349.find( L"(" );
bool lastp = s349.back() == L')';
wstring ownerName = s701.s268( L"ownerName" );
if( ( s701.s268( L"ownerType" ) == L"CallSite" ) &&
( ownerName != s252 ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s347 = s349.substr( 0, ppl );
wstring s77 = L"(new<" + s347 + L"> " + s349.substr( ppl + 1 );
s949 tast = new s263( s77, s701.Nqj() );
p = s591::s1121( *tast, s300, obj, s334 );}
else {
p = s300->TR().s518( s701, obj, s334 );
if( !p )
throw s970.s1002( L"unrecognized type of the object: " + s701.s291() );
((s483*)p)->s506( s701.s299() );}}
else if( s701.s297() == s226 )
p = s591::s1121( s701, s300, obj, s334 );
else if( s701.s297() == s228 )
p = new s371( s701.s291(), s300 );
else //if( s701.s297() == s227 )
throw new s16( L"unexpected node type" );
return p;}
s271* 
s271::s1020( s262* s300, s271* par, s272* s588, s591* s215,
s1907& s334 ){
s271* s685;
if( par->s494() == s477 ) {
s490 cs = new s561( *((s561*)par) );
s685 = s591::s600( cs, s300, s588, s215, s334, false );
((Transd*)s685)->s500( s588, false );}
else {
par->s500( /*s588*/s215 );
return par;}
return s685;}
s485
s271::s1019( s1907& s77, const s263* ast_, s262* s300, s272* s588 ){
s949 ast1;
if( ast_ )
ast1 = new s263( s77, ast_->Nqj() );
else
ast1 = new s263( L"", s77 );
s485 pr = s271::s504( *ast1, s300, s588, s588->s298() );
if( pr->s494() == s475 ) {
pr->s500( s588 );
pr = pr.s15<s371*>()->s377();}
s485 s685 = s271::s1020( s300, pr, s588, NULL, s588->s298() );
return s685;}
const wstring& 
s271::s353() const{
return s300->TR().s804( s352() );}
void s271::s351( s813::s737 type ){
s493 = type;}
s484* s1122( s505& m, const wstring& s152 ){
if( m.count( s152 ) > 1 )
throw new s16( L"multiple values: " + s152, (uint32_t)s16::s17::s21 );
auto s685 = m.find( s152 );
if( s685 == m.end() )
throw new s16( L"no such key: " + s152, (uint32_t)s16::s17::s23 );
return s685->second;}
void s670( const std::wstring& s, std::wstring& s1114, std::wstring& s601 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1114 = s.substr( 0, pl );
s601 = s.substr( pl + 2 );}
s483::~s483(){}
s483* s483::s496(){
return this;}
void s483::s1962( s1907&) { throw std::logic_error( "from_wstring: not implemented" ); }
wstring s483::s298() const { return ns->s298(); }
wstring s483::s834() const { return ns->s834(); }
s483* s483::s1538( const s483* p ) const{
if( s352() == p->s352() ) {
s483* s685 = (s483*)p->s335();
return s685;}
throw new s16( L"no conversion from '" + s353() + L"' to '" + p->s353() + L"'" );}
s483* s483::s355( s272* s588, const std::vector<s1063>& vt ) const{
assert(0);
return 0;}
s1063 s483::s1190( s1907& s1555, const vector<s485>& l ) const{
throw std::logic_error( "9: not implemented" );}
s591* 
s483::s1687( s1907& s676, s591* s215,
s561* cs ) const{
if( s676 == L"cp" ) {
return new s1683( s300, (s272*)this, s215, &s483::s1705, cs->s602(),
L"cp",	0, cs->s603() );}
else if( s676 == L"exec" ) {
return new s1683( s300, ns, s215, &s483::s1896, cs->s602(), L"exec",
0, cs->s603() );}
else if( s676 == L"_META_type" ) {
return new s1683( s300, ns, s215, &s483::s1940, cs->s602(), 
L"_META_type", Types.String,	cs->s603() );}
return NULL;}
s483* s483::s1705( s483** s274, size_t s498 ){
return (s483*)s335();}
s483* s483::s1896( s483** s274, size_t s498 ){
return s497( s274, s498 );}
s483* s483::s1940( s483** s274, size_t s498 ){
return new s359( s300, s353() );}
s483* s483::s1897( s483** s274, size_t s498 ){
return s1898( s274, s498 );}
s483* s483::s1898( s483** s274, size_t s498 ){
throw std::logic_error( "10: not implemented" );}
void s483::s1937( Stream* s1936 ) const{
s1936->s1482( to_wstring() );}
void s483::s1961( Stream* s1936 ){
wstring s;
s1936->s1463( s, string::npos );
s1962( s );}
vector<wstring> s521::s525 = { s7::s446, s7::s444,
s7::s447, s7::s445 };
s1::s9<s526> s557 = new s526();
size_t s969( const vector<s813::s894>& vt ){
size_t s685 = 0;
for( auto i : vt )
s685 = ( s685 << 7 ) ^ i;
return s685;}
size_t s491::s1058( const wstring& s, size_t& pos, s813::Cont& s153 ){
size_t s68 = pos;
size_t s685 = 0;
if( s[s68] == L' ' )
s68 = s.find_first_not_of( s4::s48, s68 );
while( s68 < s.size() && s[s68] != L'>' && s[s68] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s68 );
wstring stype = s4::s52( s.substr( s68, pl - s68 ), s4::s48 );
s1063 s1093 = get( stype /*+ L"()"*/ )->s352();
s153.push_back( s1093 );
pl = s.find_first_not_of( s4::s48, pl );
s813::Cont s1071;
size_t s1056 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1056 = s1058( s, ++pl, s1071 );}
else if( s[pl] == L',' ) {
s1056 = 0;}}
s153.push_back( ( s813::s894 ) s1056 );
s153.insert( end( s153 ), begin( s1071 ), end( s1071 ) );
s685++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s48, pl );
pos = s68 = pl;}
return s685;}
wstring s1159( const s813::Cont& s1066, size_t& idx, s491& s912 ){
wstring s685 = s912.s804(s1066[idx++]);
size_t n = (size_t)s1066[idx++];
if( n && s685.back() != L'>' ) {
s685 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s685 += ( k ? L" " : L"" ) + s1159( s1066, idx, s912 );}
s685 += L">";}
return s685;}
wstring s491::s1014( const s813::Cont& s1066 ){
assert( s1066.size() );
if( s1066.size() == 1 )
return  s1098[s1066[0]] + L"< 0 >";
size_t idx = 0;
wstring s685;
while( idx < s1066.size() ) {
s685 += s1159( s1066, idx, *this );
if( idx < s1066.size() )
s685 += L" ";}
return s685;}
wstring s491::s1354( const wstring& tn ){
wstring sv = tn;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
return sv;}
void s491::s1010( const s813::Cont& v, size_t& idx, s813::Cont& s153 ){
s153.push_back( v[idx++] );
size_t n = v[idx++];
s153.push_back( (s1063)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s1010( v, idx, s153 );}}
s813::s813( s737 t1, s737 t2/*=(s737)-1*/, s737 t3/*=(s737)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s737)-1 ) {
vt.push_back( t2 );
if( t3 != (s737)-1 )
vt.push_back( t3 );}
s1097 = s969( vt );}
s813::s813( const s813& right )
: s1097( right.s1097 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s813::s813( const Cont& v ) 
: vt( v ) {
s1097 = s969( vt );}
s813::s894 s813::s352( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s813::s351( s737 t ){
vt.clear();
vt.push_back( t );}
void s813::s351( s927 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s813::s785( s737 t ){
vt.push_back( t );}
void s813::s785( s927 pt ){
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
for( size_t n = 0; n < s1115.size(); ++n )
if( s1115[n] ) s1115[n]->s350();}
void s491::s517( const s482& st ){}
void s491::reset() {
s1115.clear(); 
s1098.clear();
s1103.clear();
s1099.clear();
s1104.clear();
s919.clear();
s893.clear();
s1261.clear();
s1276.clear();
s1553.clear();
s1115.push_back( NULL ); 
s1098.push_back( L"" );
s1103.push_back( 0 );
s893[L":Data"] = 1;
s1261[1] = L":Data";
s1207 = 1;
s1276.push_back( 0 );
srand( (unsigned int)time(NULL) );}
s1063 s491::s218( s483* p, const std::wstring& s347 ){
if( s1099.find( s347 ) != s1099.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1098.push_back( s347 );
s1115.push_back( p );
s1063 s1093 = (s1063)s1098.size() - 1;
s1103.push_back( s813( s1093 ) );
p->s351( s1093 );
s1099[s347] = s1093;
s1104[s1103.back()] = s1093;
s1276.push_back( 1 );
s1553.push_back( vector<s1063>() );
return s1093;}
void s491::s1668( const std::wstring& s347 ){
auto it = s1099.find( s347 );
if( it == s1099.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1063 s1093 = it->second;
s1099.erase( it );
s1115[s1093] = NULL;
s1098[s1093] = L"";
s1104.erase( s1103[s1093] );
s1103[s1093] = s813();
s1276[s1093] = 0;
s1553[s1093-1].clear();}
s1063 s491::s1070( const s813::Cont& v, const std::wstring& s347 ){
s813 vt( v );
if( s1104.find( vt ) != s1104.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1098.push_back( s347 );
s1103.push_back( vt );
s1063 s1093 = (s1063)s1098.size() - 1;
s1099[s347] = s1093;
s1104[s1103.back()] = s1093;
s1104[s813( s1093 )] = s1093;
s1115.push_back( s1115[vt.s352( 0 )]->s355( s300, v )	);
s1276.push_back( s1276[vt.s352( 0 )] );
s1553.push_back( vector<s1063>() );
return s1093;}
s1063 s491::s1048( const s813::Cont& v_ ){
assert( all_of( begin( v_ ), end( v_ ), [this]( s1063 t ) { return ( t <= s1103.size() ); } ) );
s813 vt( v_ );
s1063 s685 = 0;
auto it = s1104.find( vt );
if( it == s1104.end() ) {
wstring s1091 = s1014( v_ );
s685 = s1070( v_, s1091 );}
else
s685 = it->second;
return s685;}
uint32_t s1195( uint32_t n ){
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
traitnum_t s491::s1254( const std::wstring& trait, s1063& s1512 ){
auto it = s893.find( trait );
if( it != end( s893 ) )
return it->second;
s1207 = s1195( s1207 );
s893[trait] = s1207;
s1261[s1207] = trait;
s1512 = s7::s1556 + (s1063)s1513.size();
s1513.push_back( s1207 );
return s1207;}
void s491::s1164( s813::s894 type, const wstring& trait, s1063& s1512 ){
traitnum_t tn;
auto it = s893.find( trait );
if( it == end( s893 ) ) {
tn = s1254( trait, s1512 );
s1276[type] *= tn;}
else {
tn = it->second;
if( !s1200( type, tn ) )
s1276[type] *= tn;}}
traitnum_t s491::s1460( s1063 alias ) const{
return s1513[alias - s7::s1556];}
bool s491::s1200( s1063 s619, traitnum_t tra ) {
double d = (double)s300->TR().s1157( s619 ) / tra;
return ( d == (int)d );}
bool s491::s1467( s1063 s619, s1063 alias ) {
double d = (double)s300->TR().s1157( s619 ) / 
s1513[alias-s7::s1556];
return ( d == (int)d );}
void s491::s1535( s1063 s619, s1063 is ){
s1553[s619].push_back( is );}
bool s491::s1536( s1063 s619, s1063 is ){
if( s619 == is )
return true;
if( s619 >= s1553.size() )
return false;
std::vector<s1063>& v = s1553[s619];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
void s491::s1173( const wstring& alias, const wstring& s347, 
const wstring& s1842 ){
assert( s1099.find( alias ) == end( s1099 ) );
s1063 typid;
auto it = s1099.find( s347 );
if( it == s1099.end() ) {
s813::Cont vt;
size_t pos = 0;
s1058( s347, pos, vt );
typid = s1048( vt );}
else
typid = it->second;	
s1098.push_back( alias );
s1115.push_back( s1115[typid] );
s1103.push_back( s1103[typid] );
s1276.push_back( s1276[typid] );
s1553.push_back( s1553[typid-1] );
s1099[alias] = typid;
auto it1 = s1843.find( s1842 );
if( it1 == s1843.end() )
it1 = s1843.insert( make_pair( s1842, list<wstring>() ) ).first;
it1->second.push_back( alias );}
void s491::s1880( const std::wstring& s1114 ){
auto it = s1843.find( s1114 );
if( it != s1843.end() ) {
for( auto it1 = it->second.begin(); it1 != it->second.end(); ++it1 ) {
s1099.erase( *it1 );}}}
wstring s491::s1277( const wstring& tn_ ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1099.find( s );
if( it == end( s1099 ) )
return tn_;
const wstring& tn = s1098[s1104[s1103[it->second]]];
if( tn != s ) {
wstring s685 = tn_;
return s685.replace( 0, s.size(), tn );}
return tn_;}
s483* s491::s518( const s263& s701, s272* s588, const wstring& s519 ){
if( s701.s1311() )
return s1115[s701.s1311()]->s354( s701, s588, s519 );
wstring s349 = s701.s291();
if( s349.substr(0,2) == L"[[" )
return s1115[s1099[Types( s300, Types.Tuple )->s353()]]->s354( s701, s588, s519 );
else if( s349[0] == L'[' )
return s1115[s1099[Types( s300, Types.Vector )->s353()]]->s354( s701, s588, s519 );
else if( s349.find( L"UVector[" ) == 0 )
return s1115[s1099[Types( s300, Types.s748 )->s353()]]->s354( s701, s588, s519 );
else if( s349[0] == L'{' )
return s1115[s1099[Types( s300, Types.Index )->s353()]]->s354( s701, s588, s519 );
else if( s349.find( L"typealias" ) == 0 ) {
size_t pl = s349.find( L"(" );
wstring s347 = s4::s52( s349.substr( pl + 1, s349.size() - pl - 2 ), s4::s48 );
s1173( s701.s299(), s347, s519 );
return s1115[s1099[Types( s300, Types.String )->s353()]]->s354( s701, s588, s519 );}
wstring s347 = L"";
s483* s685 = NULL;
if( s4::s88.find( s349[0] ) != string::npos )
s347 = s359( s300 ).s353();
else if( isdigit( s349[0] ) || s349[0] == L'-' )
return s336::s345( s300, s349, s519 );
else if( ( s685 = s1115[s1150]->s354( s701, s588, s519 ) ) )
return s685;
else {
size_t pl = s349.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s347 = s349.substr( 0, pl );}
else if( pl == string::npos )
s347 = s349;}
auto it = s1099.find( s347 );
if( it == s1099.end() ) {
auto it1 = s893.find( s347 );
if( it1 == end( s893 ) )
throw new s16( L"Type does not exist: " + s349, (uint32_t)s16::s17::s23 );
return new s384( s300, it1->second, s1248 );}
return s1115[it->second]->s354( s701, s588, s519 );}
s483* s491::s518( s1063 s340, s272* s588, const wstring& s519 ){
if( s340 >= s7::s1556 ) {
auto it = s1261.find( s340 - s7::s1556 );
if( it != end( s1261 ) )
return new s384( s300, it->first, s1248 );}
if( !s340 || s340 >= s1098.size() )
throw new s16( L"no type with such id: " + to_wstring( s340 ) );
s1063 type = s340;
if( s1103[type].s352() != type )
type = s1103[type].s352();
if( s1103[s340].s819().size() == 1 )
return s1115[type]->s355( s588 );
else {
return s1115[type]->s355( s588, s1103[s340].s819() );}}
const s483* s491::get( const wstring& s76, bool s520/*= true*/ ) const
{
wstring s347 = s76;
size_t pl = s76.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s76.find( L"0" ) == string::npos )
s347 = s76.substr( 0, pl );
auto s685 = s1099.find( s347 );
if( s685 == s1099.end() ) {
if( s520 )
throw new s16( L"1: symbol not found: " + s76 );
else
return NULL;}
return s1115[s685->second].s15<const s483*>();}
bool s491::s156( const std::wstring& s76 ) const{
if( s1099.find( s76 ) == s1099.end() )
return false;
return true;}
const wstring& s491::s804( s1063 n ) const{
if( n >= s1098.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1098[n];}
s1063 s491::s1012( const std::wstring& s347, bool s520 ) const{
auto it = s1099.find( s347 );
if( it == s1099.end() ) {
if( s520 )
throw new s16( L"no such type: " + s347,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1063 s491::s1013( const s813& vt, bool s520 ) const{
auto it = s1104.find( vt );
if( it == end( s1104 ) ) {
if( s520 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s813& s491::s1015( s1063 t ) const{
assert( t && t < s1103.size() );
return s1103[t];}
const s483* s491::s1009( s813::s894 t ) const{
assert( t && t < s1103.size() );
return s1115[t].s15<const s483*>();}
void s491::s790(){
size_t s747 = s336::s807() + 1;
for( size_t n = s747; n < s1098.size(); ++n ) {
s1099.erase( s1098[n] );
s1104.erase( s1103[n] );
s919.erase( (s1063)n );}
s1098.erase( s1098.begin() + s747, s1098.end() );
s1115.erase( s1115.begin() + s747, s1115.end() );
s1103.erase( s1103.begin() + s747, s1103.end() );}
bool s491::s1251(){
return rand() % 2;}
double s491::s1253(){
return rand() / RAND_MAX;
}
int s491::s1259(){
return rand();}
void s491::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << L"Types :" << endl;
for( size_t n = 0; n < s1098.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s197 + 5 ) << s1098[n] << endl;
s1115[n]->s304( pd, s197 + 10 );}}
s482::s482( const s482& right )
: s553( right.s553 ), s537( right.s537 ), s539( right.s539 ){}
void s482::s500( s272* s879, bool s516/*= true*/ )
{
for( auto sym : s553 ) {
if( sym.second->s494() != s476 ) {
try {
sym.second->s500( s879 );}
catch( TDException* e ) {
e->s1078( TDException::Stage::s1028 );
s1016.s973( e->Msg( 0 ) );
continue;}}}
if( s1016.s936() )
return;
if( s516 ) {
for( auto sym : s553 ) {
if( sym.second->s494() == s476 )
sym.second.s15<Transd*>()->s500( s879, true );}}}
void s551::s1651( s262* s300 ){
for( auto sym : s559 ) {
if( sym.find( L"::" ) == string::npos )
s300->s1652( sym );}}
void s482::reset(){
s553.clear();}
void s482::copy( s482& t, s272* s588, s591* s587, s145 ap ) const{
t.s539 = s539;
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() == s476 ) {
s591::s563 ct = it->second.s15<Transd*>()->s864();
assert( ct == s591::s568 || ct == s591::s567);
s842* ptr = new s842( *( s842* )&( *it->second ),
/*s588,*/ s587, std::vector<s271*>(), ct, 
it->second.s15<Transd*>()->s603(), s588 );
t.s541( it->first,  ptr, ap );}
else {
t.s541( it->first, it->second->s335(), ap );}}}
void s482::s548( s482& t ) const{
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() == s476 )
t.s541( it->first, it->second.s15<s271*>() );
else
t.s541( it->first, it->second->s335() );}}
void s482::s1615( s482& t ) const{
for( s535::const_iterator it = s553.begin(); it != s553.end(); ++it ) {
if( it->second->s494() != s476 ) {
auto it1 = t.s553.find( it->first );
if( it1 == end( t.s553 ) )
t.s553[it->first] = it->second;
else
it->second.s15<s483*>()->s356( it1->second.s15<s271*>() );}}}
bool s482::s538( const std::wstring& s76, s145 ap /*= s146*/ )
{
if( s553.find( s76 ) != s553.end() ) {
wstring rep = s7::s421 + L" name already exists: " + s76;
if( ap == s146 || ap == s534 ) {
if( ap == s146 )
throw new TDException( 0, s1673, NULL, s76 );
return false;}
else if( ap == s148 ) {
return false;}}
return true;}
void s482::s541( const std::wstring& s76, s271* sym, s145 ap/*= s146*/ )
{
if( (ap == s147) || s538( s76, ap ) )
s553[s76] = sym;}
void s482::s541( const std::wstring& s76, s142 s349, s145 ap/*= s146*/ )
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
bool s482::s156( const std::wstring& s76 ) const{
if( s553.find( s76 ) == s553.end() )
return false;
return true;}
s483* s482::get( const wstring& s76, bool s520/*= true*/ ) const
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
void s482::s533( const wstring& s334, vector<wstring>& s153 ){
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
bool s482::s550( const std::wstring& s278,
const std::wstring& s334 ) const{
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
void s482::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << L"Symbols :" << endl;
s535::const_iterator it = s553.begin();
for( ; it != s553.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s304( pd, s197 + s419 * 2 );
buf << endl;}}}
wstring s482::to_wstring( uint32_t s1567 ) const{
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
void s551::s500( s262* s300, const wstring& s558 ){
s334 = s558;
for( size_t n = 0; n < s559.size(); ++n ) {
wstring s76 = s559[n];
vector<wstring> s153;
s300->s219( s76, s558, s153 );
for( size_t m = 0; m < s153.size(); ++m ) {
s76 = s76.substr( 0, s76.find( L"::" ) );
s553.insert( make_pair( s153[m], make_pair( (s483*)s300->s641( 
s559[n],	s558 ), s76) ) );}}}
void s551::s555( const wstring& s76, s262* s300, const wstring& s558 ){
s559.push_back( s76 );
vector<wstring> s153;
s300->s219( s76, s558, s153 );
for( size_t n = 0; n < s153.size(); ++n )
s553.insert( make_pair( s153[n], make_pair( (s483*)s300->s641( 
s76,	s558 ), s76 ) ) );}
void s551::s554( const std::wstring& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s16( L"Unrecognized import syntax: " + s );
s559.push_back( s.substr(1, s.size() - 2 ) );}
bool s551::s556( const std::wstring& sym, s371* ref ){
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
: s522( s523 ), pv( pv_ ){}
s521::s521( const wstring& ag_, const wstring& s77 ){}
s512 s521::s560( const std::wstring& s499 ) const{
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
wstring s72( s1120, 1 );
s4::s57( l, s72, s153 );
s528[it->first] = new s521( pv, s153 );}}
void s526::s530( const std::wstring& s, s521& pl ){}
void s526::s531( const std::wstring& s, const std::wstring& s524 ){}
s512 s526::s532( const std::wstring& mem, const std::wstring& s499 ){
s527::iterator it = s528.find( mem );
if( it == s528.end() )
return s513;
return it->second->s560( s499 );}
s2002 Types;
s1063 s1514::s1273 = 0;
s1063 s1514::s1551 = 0;
s336::s341 s384::s348;
s336::s341 s364::s348;
s336::s341 s361::s348;
s336::s341 s360::s348;
s336::s341 s346::s348;
s336::s341 s358::s348;
s336::s341 s1305::s348;
s336::s341 s1531::s348;
s336::s341 s1297::s348;
s336::s341 s1575::s348;
s336::s341 s1604::s348;
s336::s341 s359::s348;
s336::s341 s316::s348;
s336::s341 s750::s348;
s336::s341 s961::s348;
s336::s341 s324::s348;
s336::s341 s1384::s348;
s336::s341 s1294::s348;
s336::s341 s415::s348;
s336::s341 s385::s348;
s336::s341 s1136::s348;
s336::s341 s953::s348;
s336::s341 s1145::s348;
s336::s341 s1708::s348;
s336::s341 s650::s348;
s336::s341 s1803::s348;
s336::s341 s507::s348;
s336::s341 s1296::s348;
s336::s341 s1304::s348;
s336::s341 s1404::s348;
s336::s341 s1406::s348;
size_t s336::s758 = 0;
s9<s364> s365;
s9<s384> s872;
s9<s384> s366;
s9<s384> s367;
s9<s384> s368;
s9<s384> s873;
s9<s384> s1688;
s9<s360> s369;
s9<s360> s370;
s9<s1404> s1405;
s9<s1406> s1407;
s9<s384> s1523;
template <class charT, charT s72>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s72; }
};
std::locale exprloc;
static s6::s1711 s1760;
s1722 s1740;
s6::s1697 s1738;
const s483* s2002::operator()( s262* s300, s1063 tp ){
return s300->TR().s1009( tp );}
void s336::s784( s262* s300, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
Types.No = s300->s218( new s384( s300 ), L"NoValue" );
Types.Null = s300->s218( new s364( s300 ), L"Null" );
Types.s361 = s300->s218( new s361( s300 ), L"Exception" );
Types.Bool = s300->s218( new s360( s300 ), L"Bool" );
Types.Int = s300->s218( new s346( s300 ), L"Int" );
Types.Double = s300->s218( new s358( s300 ), L"Double" );
Types.Long = s300->s218( new s1305(s300), L"Long" );
Types.s1530 = s300->s218( new s1531( s300 ), L"ULong" );
Types.Byte = s300->s218( new s1297( s300 ), L"Byte" );
Types.Char = s300->s218( new s1575( s300 ), L"Char" );
Types.s272 = s300->s218( new s1604( s300 ), L"Object" );
Types.Position = s300->s218( new s1145( s300 ), L"Position" );
Types.DateTime = s300->s218( new s1708( s300 ), L"DateTime" );
Types.Vector = s300->s218( new s316( s300 ), L"Vector" );
Types.s748 = s300->s218( new s750( s300 ), L"UntypedVector" );
Types.Tuple = s300->s218( new s961( s300 ), L"Tuple" );
Types.Index = s300->s218( new s324( s300 ), L"Index" );
Types.HashIndex = s300->s218( new s1384( s300 ), L"HashIndex" );
Types.ByteArray = s300->s218( new s1294( s300 ), L"ByteArray" );
Types.s414 = s300->s218( new s415( s300 ), L"Directory" );
Types.Range = s300->s218( new s385( s300 ), L"Range" );
Types.Filter = s300->s218( new s1136( s300 ), L"Filter" );
Types.Seq = s300->s218( new s953( s300 ), L"Seq" );
Types.Table = s300->s218( new s1803( s300 ), L"Table" );
Types.TSDBase = s300->s218( new s650( s300 ), L"TSDBase" );
Types.s789 = s300->s218( new s507( s300 ), L"StringStream" );
Types.ByteStream = s300->s218( new s1296( s300 ), L"ByteStream" );
Types.FileStream = s300->s218( new s1304( s300 ), L"FileStream" );
Types.Lambda = s300->s218( new s838( s300 ), L"Lambda" );
Types.String = s300->s218( new s359( s300 ), L"String" );
if( !soft )
s758 = Types.String;
if( s365.s13() ) {
s365 = new s364( s300 );
s872 = new s384( s300, s481 );
s368 = new s384( s300, s481 );
s367 = new s384( s300, s481 );
s366 = new s384( s300, s481 );
s873 = new s384( s300, s481 );
s1688 = new s384( s300, s481 );
s369 = new s360( s300, true );
s370 = new s360( s300, false );
s872->s1681( s7::s866 );
s368->s1681( s7::s438 );
s367->s1681( s7::s439 );
s366->s1681( s7::s440 );
s369->s1262();
s370->s1262();
s1523 = new s384( s300, Types.Int, s1248 );
s1738.s151 = true;
s1738.s1734 = true;
s1738.s1702 = true;
s1738.s1701 = true;
s1738.s1703 = true;}}
s1124::s1124( const std::vector<s485>& v, s336* s592 )
:s588( s592 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s494() != s1065 ) {
s914.push_back( v[n] );
s1280.push_back( v[n]->s352() );}
else if( n > 1 )
break;}}
bool s1124::operator==( const s1124& s524 ) const{
bool pend = s1280.empty();
bool send = s524.s1280.empty();
s1063 starred = 0;
size_t n = 0, k = 0;
bool s1272 = true;
s491* ptr = s524.s588 ? &s524.s588->Pass()->TR() : NULL;
while( !send || !pend ) {
s1272 = false;
s1063 s1179 = starred ? starred : (pend ? 0 : s1280[k]);
s1063 s1176 = send ? (s524.s1280.empty() ? 0 : s524.s1280[n-1]) : s524.s1280[n];
s271* s1539 = send ?
( s524.s914.empty() ? NULL : s524.s914[n - 1].s15<s271*>() ) :
s524.s914[n].s15<s271*>();
if( s1176 == Types.No )
s1176 = send ? s524.s914[n-1].s15<s384*>()->s1542() : 
s524.s914[n].s15<s384*>()->s1542();
const s813* s1283 = s524.s588 ? &s524.s588->s1198() : NULL;
if( s1179 >= s7::s1401 && s1179 < s7::s1556 && s1176 ) {
if( s1179 == s7::s1395 )
s1272 = true;
else if( s1179 == s7::s1400 ) {
s1063 pt1_ = s524.s914[n]->s1198().s352();
if( pt1_ == s1718 /*&& pt2_ == Types.Bool*/ )
s1272 = true;}
else if( s1179 == s7::s1396 ) {
if( s524.s588 && s1176 == s524.s588->s352())
s1272 = true;}
else if( s1179 == s7::s1397 ) {
if( s524.s588 && s1176 == ( (s326*)s524.s588 )->s319() )
s1272 = true;}
else if( s1179 == s7::s1397 ) {
if( s524.s588 && s1176 == ((s326*)s524.s588)->s319() )
s1272 = true;}
else if( s1179 == s7::s1398 ) {
if( s524.s588 && s1176 == ((s326*)s524.s588)->s939() )
s1272 = true;}
else if( s1179 == s7::s1399 ) {
if( s524.s588 && s1539->s1543( ((s326*)s524.s588)->ValType() ) )
s1272 = true;}
else if( s1283 &&	s1176 == s1283->s352( (size_t)((int)0 - s1179 )) )
s1272 = true;}
else if( s1179 >= s7::s1556 && ptr ) {
traitnum_t s1515 = ptr->s1460( s1179 );
if( s1176 && ptr->s1200( s1176, s1515 ) )
s1272 = true;}
else {
if( s1539 && s1539->s1543( s1179 ) )
s1272 = true;}
if( s1272 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s524.s1280.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1280.size() )
pend = true;
if( !starred && !pend && s1280[k] == s7::s1401 )
starred = s1280[k - 1];}
return s1272;}
bool s1124::operator<( const s1124& s524 ) const{
if( s1280.empty() ) return s524.s1280.size() > 0;
if( s524.s1280.empty() ) return false;
const s813* s1282 = s588 ? &s588->s1198() : NULL;
const s813* s1283 = s524.s588 ? &s524.s588->s1198() : NULL;
s1063 s1270 = 0, s1271 = 0;
s491* ptr = s524.s588 ? &s524.s588->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1280.size() && n < s524.s1280.size()*/; ++n ) {
if( s1280.size() == n )
return s524.s1280.size() > n;
if( s524.s1280.size() == n )
return false;
s1063 s1178 = s1270 ? s1270 : s1280[n];
s1063 s1180 = s1271 ? s1271 : s524.s1280[n];
if( s1178 >= s7::s1401 && s1178 <= s7::s1556 ) {
if( s1178 == s7::s1401 )
s1178 = s1270 = s1280[n - 1];
else if( s1178 == s7::s1395 )
continue;
else if( s1178 == s7::s1396 ) {
if( !s524.s588 )
return true;
s1178 = s524.s588->s352();}
else if( s1178 == s7::s1397 ) {
if( !s524.s588 )
return true;
s1178 = ( (s326*)s524.s588 )->s319();}
else if( s1282 )
s1178 = s1282->s352( (size_t)(int)0 - s1178 );}
else if( s1178 >= s7::s1556 && ptr ) {
traitnum_t s1515 = ptr->s1460( s1178 );
if( ptr->s1200( s1180, s1515 ) )
return true;}
if( s1180 >= s7::s1401 && s1180 <= s7::s1556 ) {
if( s1180 == s7::s1401 )
s1180 = s1271 = s524.s1280[n - 1];
else if( s1180 == s7::s1395 )
continue;
else if( s1180 == s7::s1396 ) {
if( !s588 )
return true;
s1180 = s588->s352();}
else if( s1180 == s7::s1397 ) {
if( !s588 )
return true;
s1180 = ( (s326*)s588 )->s319();}
else if( s1283 )
s1180 = s1283->s352( (size_t)(int)0 - s1180 );}
else if( s1180 >= s7::s1556 && ptr ) {
traitnum_t s1515 = ptr->s1460( s1180 );
if( ptr->s1200( s1178, s1515 ) )
return true;}
if( s1178 < s1180 )
return true;}
return false;}
wstring s1124::s1331( s262* s300 ) const{
wstring s685 = L"( ";
for( auto i : s1280 ) {
s685 += s300->TR().s804( i );
if( s685.back() != L')' ) s685 += L"()";
s685 += L" ";}
s685 += L")";
return s685;}
bool
s336::s337::s1168( /*s336* thi,*/ const s1124& s691 ) const
{
return std::find( s1165.begin(), s1165.end(), s691 ) != end( s1165 );}
s1063
s336::s386( s1907& s343 ) const{
auto it = s342().find( s343 );
if( it == s342().end() )
throw new s16( L"No such operation: " + s353() +	L"::" + s343,
(uint32_t)s16::s17::s23 );
s1063 s685 = it->second->s495();
return s685;}
const s483*
s336::s503() const{
return (s483*)s300->TR().s1009( s352() );}
const vector<wstring>& 
s336::s1193( s1907& s343 ) const{
auto ran = s342().equal_range( s343 );
if( ran.first == s342().end() )
throw new s16( L"No such method: " + s353() + L"::" + s343,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1144 s336::s1199( s1907& s343 ) const{
s336::s337* s685 = NULL;
auto it = s342().find( s343 );
if( it != s342().end() )
s685 = it->second;
return s685 ? s1144( s685->s495(), s685->s1138(), s685->s1205(),
s685->s2019() ) : s1144();}
s1144
s336::s1194( s1907& s343, s1124& ap /*const vector<s1063>& s1242*/ ) const
{
auto ran = s342().equal_range( s343 );
if( ran.first == s342().end() )
throw new s16( L"No such method: " + s353() + L"::" + s343,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1188() )
throw new s16( L"", (uint32_t)s337::s1135::s1182 );
s337* s685 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1168( ap ) ) {
s685 = it->second;
break;}}
return s685 ? s1144( s685->s495(), s685->s1138(), s685->s1205(),
s685->s2019() ) : s1144();}
s1144
s336::s1189( s1907& s343, s1124& ap ){
auto ran = s342().equal_range( s343 );
s337* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1168( ap ) ) {
mi = it->second;
break;}}
s1144 s1239( mi->s495(), mi->s1138(), mi->s1205(), mi->s2019() );
if( mi )
s1239.s338 = ap.Subj()->s1190( s343, ap.s602() );
return s1239;}
s486 s336::s497( s483** s274, size_t s498 ){
return this;}
void s336::s1537( s483* p ){}
s483* s336::s345( s262* s300, s1907& s349, s1907& s334 ){
s263 s208( s349, NULL );
s483* s685 = NULL;
double dval;
size_t pos = 0;
s6::s131 s198 = s1760.s1552( s349, pos, dval );
if( s198 != s6::s131::s140 && s198 != s6::s131::s136 )
return NULL;
if( s349.find( L"." ) != std::string::npos )
s685 = ((s358*)Types( s300, Types.Double ))->s354( s208, NULL, s334 );
else {
s685 = ((s346*)Types( s300, Types.Int ))->s354( s208, NULL, s334 );
if( !s685 ) {
if( !s685 )
s685 = ((s1305*)Types( s300, Types.Long ))->s354( s208, NULL, s334 );
if( !s685 )
s685 = ((s1297*)Types( s300, Types.Byte ))->s354( s208, NULL, s334 );}}
return s685;}
#define s698 ((s346*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
s483* s358::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
double s1944( s1907& s, size_t& pos ){
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
s358::s358( s262* s300, s1907& s, size_t& pos )
: s336( s300, NULL, NULL ){
if( !s.empty() ) {
s349 = s1944( s, pos );
s1681( s7::s867 );}
else
s349 = s300->TR().s1253();
s493 = Types.Double;}
s483* s358::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s358( s300, L"", pos );}
void s358::s500( const s272*, bool ){}
void s358::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s358::s1238, Types.Double,
{ s1124(), s1124( { Types.String } ), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"abs", new s337( L"abs", &s358::s404, Types.Double,
{ s1124( ) }, 0, 0 )));
s348.insert( make_pair( L"set", new s337( L"set", &s358::s387, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"sum", new s337( L"sum", &s358::s388, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"dif", new s337( L"dif", &s358::s389, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"mul", new s337( L"mul", &s358::s390, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"div", new s337( L"div", &s358::s391, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"pow", new s337( L"pow", &s358::s392, Types.Double,
{ s1124( { s1514::s1273 } ) }, 1, 1 )));
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s358::s393, Types.Double,
{ s1124( { Types.Double } ), s1124( { Types.Int, s7::s1401 } ) }, 1, 10 )));
s348.insert( make_pair( L"difeq", new s337( L"difeq", &s358::s394, Types.Double,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"muleq", new s337( L"muleq", &s358::s395, Types.Double,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"diveq", new s337( L"diveq", &s358::s396, Types.Double,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"poweq", new s337( L"poweq", &s358::s397, Types.Double,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"sqrt", new s337( L"sqrt", &s358::s406, Types.Double,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"nroot", new s337( L"nroot", &s358::s407, Types.Double,
{ s1124( { Types.Int } ) }, 1, 1 )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s358::s398, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"less", new s337( L"less", &s358::s399, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"greater", new s337( L"greater", &s358::s400, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"leq", new s337( L"leq", &s358::s401, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"geq", new s337( L"geq", &s358::s402, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"neq", new s337( L"neq", &s358::s403, Types.Bool,
{ s1124( { Types.Double } ) }, 1, 1 )));
s348.insert( make_pair( L"dcmp", new s337( L"dcmp", &s358::s410, Types.Int,
{ s1124( { Types.Double, Types.Double } ) }, 2, 2 )));
s348.insert( make_pair( L"dcmpr", new s337( L"dcmpr", &s358::s411, Types.Int,
{ s1124( { Types.Double, Types.Double } ) }, 2, 2 )));
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s358::s412, Types.Int,
{ s1124(), s1124( { Types.Int } ) }, 0, 1 )));
s348.insert( make_pair( L"incr", new s337( L"incr", &s358::s1980, Types.Double,
{ s1124( ) }, 0, 0 )));
s348.insert( make_pair( L"decr", new s337( L"decr", &s358::s1979, Types.Double,
{ s1124( ) }, 0, 0 )));
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );}
s271* s358::s335() const{
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
std::wstring s358::to_wstring( uint32_t s1567 ) const{
wstringstream ss;
wstring s685;
int prec = s1567 << 28 >> 28;
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
void s358::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
/*	auto flags = s1936->s1932();
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss.precision( s1936->s1933() );
*/
ss << s349;}
void s358::s1962( s1907& s ){
size_t pos = 0;
s349 = s1944( s, pos );}
void s358::s1961( Stream* s1936 ){
s1499& ss = s1936->s1965();
ss >> s349;}
#undef s698
#define s698 ((s358*)(s484*)*s274)
#define INTRES ((s346*)(s484*)*s274)
inline void s358::s1238( s483** s274, size_t s498 ){
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
lv.s349 = (s1388)*( (s346*)p )->s357();
else if( p->s352() == Types.Bool )
lv.s349 = ( s1388 )*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Double from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Double() constructor" );}
plv->s1264();
s274[0] = plv;}
inline void s358::s387( s483** s274, size_t s498 ){
( (s358*)DR )->s349 = (double)*PARN( 2 );}
void s358::s404( s483** s274, size_t s498 ){
double t = (double)*DR;
if( t >= 0 )
s698->s349 = t;
else
s698->s349 = -t;}
void s358::s1980( s483** s274, size_t s498 ){
double s685 = (double)*DR;
if (isnan( s685 ) || s685 == -INFINITY || s685 == INFINITY) (void)0;
else if ( s685 == 0.0 ) s685 = DBL_EPSILON;
else {
union s1976 {
int64_t i;
double f;
}conv;
conv.f = s685;
conv.i++;
s685 = conv.f;}
s698->s349 = s685;}
void s358::s1979( s483** s274, size_t s498 ){
double s685 = (double)*DR;
if (isnan( s685 ) || s685 == -INFINITY || s685 == INFINITY) (void)0;
else if ( s685 == 0.0 ) s685 = DBL_EPSILON;
else {
union s1976 {
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
pd->s349 += ( s1388 )*( (s346*)p )->s357();}
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
inline void s358::s412( s483** s274, size_t s498 ){
int s1333 = -1;
if( s498 == 3 )
s1333 = (int)*s274[2];
double dv = ( (s358*)DR )->s349;
int s685 = (int)dv;
if( s1333 < 0 )
*( (s346*)s274[0] )->s357() = s685;
else if( s1333 == 0 ) 
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
s360::s360( s262* s300, s1907& s, size_t& pos )
: s336( s300, NULL, NULL ){
if( s.empty() )
s349 = s300->TR().s1251();
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
s1681( s7::s867 );
s493 = Types.Bool;}
s360::s360( const s360& right )
: s336( right.s300, right.ns, NULL ), s349( right.s349 ){
s493 = Types.Bool;
wh = right.wh;}
s360::s360( s262* s300, bool b )
: s336( s300, NULL, NULL ), s349( b ){
if( !Types.Bool ) {
s493 = 0;
s1681( s7::s868 );}
else {
s493 = Types.Bool;
s1681( s7::s867 );}}
void s360::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s360::s387, Types.Null,
{ s1124( { Types.Bool } ) }, 1, 1, false )));
s348.insert( make_pair( L"new", new s337( L"new", &s360::s1238, Types.Bool,
{ s1124(), s1124( { Types.Bool } ), s1124( { Types.String } ), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s360::s413, Types.Bool,
{ s1124( ) }, 0, 0, true )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s360::s398, Types.Bool,
{ s1124( { Types.Bool } ) }, 1, 1, true )));}
void s360::s500( const s272* s879, bool ){
s1264();}
s483* s360::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s360( s300, false );}
s483* s360::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
s271* s360::s335() const{
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
inline void s360::s1238( s483** s274, size_t s498 ){
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
lv.s1264();
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
wstring s360::to_wstring( uint32_t s1567 ) const{
return ( s349 ? L"true" : L"false" ); }
void s360::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
ss << s349;}
void s360::s1962( s1907& s ){
if( s == L"true" || s == L"1" )
s349 = true;
else if( s == L"false" || s == L"0" )
s349 = false;
else
throw new s16( L"unknown bool value" );}
void s360::s1961( Stream* s1936 ){
s1499& ss = s1936->s1965();
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
s361::s361( s262* s300, s1907& s/* = std::wstring( L"" )*/ )
: s336( s300, NULL, NULL ), s78( s ){
wh = s7::s440;
s493 = Types.No == 0 ? 0 : Types.s361;}
s361::s361( const s361& r )
: s336( r.s300, NULL, NULL ), s78( r.s78 ){
s493 = r.s493;
wh = r.wh;}
void s361::s350(){
s348.insert( make_pair( L"report", new s337( L"report", &s361::s792, Types.Null,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"str", new s337( L"str", &s361::s508, Types.String,
{ s1124() }, 0, 0 )));}
void s361::s500( const s272* s879, bool ){}
s483* s361::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s361( s300 );}
s271* s361::s335() const{
return new s361( *this );}
void s361::s356( s271* p ) const{
((s361*)p)->s78 = s78;}
s483* s361::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
s1681( s7::s868 );}
else {
s493 = Types.Null;
s1681( s7::s867 );}}
void s364::s500( const s272* s879, bool ){}
s483* s364::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s364( s300 );}
s483* s364::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s = s701.s291();
if( s.find( L"Null" ) == 0 )
return s365;
return NULL;}
s271* s364::s335() const{
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
s384::s384( s262* s300, traitnum_t tn, s472 pc ) 
: s336( s300, NULL, NULL ), s1274( tn ){
s492 = pc;
s493 = Types.No == 0 ? 0 : Types.No; }
void s384::s500( const s272* s879, bool ){}
s483* s384::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s384( s300 );}
s483* s384::s354( const s263& s701, s272* s588, s1907& s334 ) const{
throw new s16( L"no parser for NoValue" );
return NULL;}
s271* s384::s335() const{
return (s271*)this;}
inline bool
s384::s501( const s483* s502 ) const{
return s300->TR().s1200( s502->s352(), s1274 );}
inline bool
s384::s1543( s1063 s619 ) const{
return s300->TR().s1536( s1274, s619 );}
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
s1708::s1708( s262* s300 ) 
: s336( s300, NULL, NULL ), s1745( s1743 ) {
if( !Types.DateTime )
s493 = 0;
else
s493 = s1715;
s1681( s7::s868 );}
s1708::s1708( s262* s300, s1907& s )
: s336( s300, NULL, NULL ){
if( !s1730( s, s349, s1745 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1877 = s1797::from_time_t ( std::mktime( &s349 ) );
s493 = s1715;
s1681( s7::s867 );}
s1708::s1708( const s1708& right )
: s336( right.s300, right.ns, NULL ), s349( right.s349 ), s1877( right.s1877 ){
s493 = right.s493;
wh = right.wh;}
s1708::s1708( s262* s300, const std::tm& _t, s1707 s619 )
: s336( s300, NULL, NULL ), s1745( s619 ), s349( _t ){
s493 = s1715;
s1877 = s1797::from_time_t ( std::mktime( &s349 ) );
s1681( s7::s867 );}
wregex s1708::s1767( LR"regex(^\"?(\d\d\d\d-\d\d?-\d\d?)\"?$)regex" );
wregex s1708::s1865( LR"regex(^(\d+)(\.\d+)?$)regex" );
bool 
s1708::s1730( s1907& s349, std::tm& t, s1707& s619 ) const{
wsmatch s1076;
s619 = s1743;
if( regex_match( s349, s1076, s1767 ) ) {
std::wistringstream ss( s1076[1] );
ss >> std::get_time( &t, L"%Y-%m-%d" );
if( ss.fail() )
return false;
s619 = s1741;}
else if( regex_match( s349, s1076, s1767 ) ) {}
else
return false;
return true;}
void s1708::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s1708::s387, Types.Null,
{ s1124( { s1715 } ), s1124( { Types.String } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"new", new s337( L"new", &s1708::s1238, s1715,
{ s1124(), s1124( { s1715 } ), s1124( { Types.String } ), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s1708::s413, Types.Bool,
{ s1124() }, 0, 0, true ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s1708::s398, Types.Bool,
{ s1124( { s1715 } ) }, 1, 1, true ) ) );
s348.insert( make_pair( L"now-delta", new s337( L"now-delta", &s1708::s1851, Types.Double,
{ s1124( ) }, 0, 0, true ) ) );
s348.insert( make_pair( L"set-now", new s337( L"set-now", &s1708::s1875, s1715,
{ s1124( ) }, 0, 0, false ) ) );}
void s1708::s500( const s272* s879, bool ){
s1264();}
s483* s1708::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1708( s300 );}
s483* s1708::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s = s4::s52( s701.s291(), s4::s48 );
if( s.find( L"DateTime(" ) == 0 )
s = s.substr( 9, s.size() - 10 );
if( s.empty() )
return new s1708( s300 );
std::tm t = {};
s1707 s619;
if( s1730( s, t, s619 ) )
return new s1708( s300, t, s619 );
return NULL;}
s271* s1708::s335() const{
return new s1708( *this );}
void s1708::s356( s271* p ) const{
if( p->s352() == s1715 )
( (s1708*)p )->s349 = s349;
else
throw new s16( L"No conversion to type " + s353() );}
void s1708::s1962( s1907& s ){
std::tm t = {};
s1707 s619;
if( !s1730( s, t, s619 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1745 = s619;
s349 = t;
s1681( s7::s867 );}
#undef s698
#define s698 ((s1708*)(s484*)*s274)
inline void s1708::s1238( s483** s274, size_t s498 ){
s1708* s685 = NULL;
if( s498 == 2 )
s685 = new s1708( ( (s1708*)s274[1] )->s300 );
else if( s498 == 3 ) {
s483* p = s274[2];
if( p->s352() == s1715 )
s685 = new s1708( *(s1708*)s274[2] );
else if( p->s352() == Types.String )
s685 = new s1708( ( (s1708*)s274[1] )->s300, s274[2]->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to DateTime() constructor" );
s274[0] = s685;}
inline void s1708::s387( s483** s274, size_t s498 ){
s483* p = s274[2];
if( p->s352() == s1715 ) {
( (s1708*)DR )->s349 = ( (s1708*)p )->s349;
( (s1708*)DR )->s1745 = ( (s1708*)p )->s1745;
( (s1708*)DR )->wh = ( (s1708*)p )->wh;}
else if( p->s352() == Types.String )
( (s1708*)DR )->s1962( p->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s353() );}
inline void s1708::s413( s483** s274, size_t s498 ){
*s699->s357() = !(( (s1708*)DR )->s1745 == s1743);}
inline void s1708::s398( s483** s274, size_t s498 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s699->s357() = 1;
else
*s699->s357() = 0;}
inline void s1708::s1875( s483** s274, size_t s498 ){
s1708* p = (s1708*)DR;
p->s1877 = s1797::now();
time_t t = s1797::to_time_t( p->s1877 );
#ifdef WIN32
localtime_s( &p->s349, &t );
#else
p->s349 = *localtime( &t );
#endif
p->s1745 = s1742;}
inline void s1708::s1851( s483** s274, size_t s498 ){
s1708* p = (s1708*)DR;
std::chrono::duration<double> delta = s1797::now() - p->s1877;
*((s358*)s274[0])->s357() = delta.count();}
void s1708::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << to_wstring()
<< L" (" << std::hex << &s349 << L")";}
size_t s1708::s322() const{
std::tm t = s349;
return hash<time_t>{}( std::mktime( &t ) );}
inline bool s1708::operator==( const s483* p ) const{
return memcmp( &s349, &((s1708*)p )->s349, sizeof(tm) );}
inline bool s1708::operator<( const s483* p ) const{
tm t = s349, t1 = ( (s1708*)p )->s349;
return ( std::mktime( &t ) < std::mktime( &t1 ) );}
wstring s1708::to_wstring( uint32_t s1567 ) const{
wstring s685;
if( s1745 == s1741 || s1745 == s1742 ) {
s685 = std::to_wstring( 1900 + s349.tm_year ) + L"-";
if( s349.tm_mon < 9 )
s685 += L"0";
s685 += std::to_wstring( 1 + s349.tm_mon ) + L"-";
if( s349.tm_mday < 10 )
s685 += L"0";
s685 += std::to_wstring( s349.tm_mday );}
if( s1745 == s1742 )
s685 += L" ";
if( s1745 == s1744 || s1745 == s1742 ) {
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
s1604::s1604( s262* s300, s272* s588, s1907& s77, const s263* ast_ )
: s336( s300, s588, ast_ ){
if( s77.size() ) {
load( s77, false );}
if( !s493 )
s493 = Types.s272;
if( !s77.empty() )
s1681( s7::s867 );}
s1604::s1604( s262* s300, s272* s588, const s143* s1646, const s263* ast_ )
: s336( s300, s588, ast_ ){
if( s1646->s156( s7::s465 ) ) {
wstring sname = s4::s52( s263::s302( *s1646, s7::s465 ),
s48 );
(( s143*)s1646)->s159( L"name", new s141( sname ) );
(( s143*)s1646)->s1633( s7::s465 );}
s1644( s1646, s482::s146 );
s493 = Types.s272;
s1264();}
s1604::s1604( const s1604& right, const s263* ast_ )
: s336( right.s300, right.ns, ast_ ), s628( right.s628 ){
s493 = Types.s272;
wh = right.wh;}
void s1604::s350(){
s348.insert( make_pair( L"get-Int", new s337( L"get-Int", &s1604::s1638, Types.Int,
{ s1124( { Types.String } ) }, 1, 1, true )));
s348.insert( make_pair( L"get-String", new s337( L"get-String", &s1604::s1639, Types.String,
{ s1124( { Types.String } ) }, 1, 1, true )));
s348.insert( make_pair( L"load", new s337( L"load", &s1604::s1643, Types.Null,
{ s1124( { Types.String } ) }, 1, 1, true )));
s348.insert( make_pair( L"load-from-file", new s337( L"load-from-file", &s1604::s1641, Types.Null,
{ s1124( { Types.String } ), s1124( { Types.String, Types.String } ) }, 1, 2, true )));}
void s1604::s500( const s272* s879, bool ){
s1264();}
s483* s1604::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1604( s300 );}
s483* s1604::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s = s701.s291();
if( s.find( L"Object(" ) == 0 ) {
return new s1604( s300, s588, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s355( s588, std::vector<s271*>(), &s701 );}
return NULL;}
s1063 s1604::s1190( s1907& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get" ) {
auto it = s628.get( l[0]->to_wstring() );
s685 = it->s352();}
return s685;}
void s1604::load( s1907& s77, bool s1636 ){
TDException s970( s7::s1600, s934, s603(), L"Failed to load object" );
s950 s1053 = new s947( s77, s1636 );
vector<s9<s143>> s662;
s1053->read( s662, L"" );
if( s662.size() != 1 )
throw s970.s1002( L"wrong object data: the source contains " + std::to_wstring( s662.size() ) + L"objects"  );
s143* obj = s662[0];
if( obj->s156( s7::s465 ) ) {
wstring sname = s4::s52( s263::s302( *obj, s7::s465 ),
s48 );
obj->s159( L"name", new s141( sname ) );}
s1644( obj );}
void s1604::s1644( const s143* obj, s482::s145 ap ){
vector<pair<wstring, s142>> s144;
obj->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s949 past = new s263( s144[n].first, *s144[n].second );
s483* dv = s300->TR().s518( *past, (s272*)this, L"::" );
dv->s506( s144[n].first );
dv->s1264();
s628.s541( s144[n].first, dv, ap );}}
void s1604::s1634( s482::s535& sm ) const{
const s482::s535& tb = s628.Table();
s482::s535::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s494() == s476 )
(void)0;
else {
s483* dv = (s483*)it->second->s335();
sm.insert( make_pair( it->first, dv ));}}}
s271* s1604::s335() const{
return new s1604( *this );}
void s1604::s356( s271* p ) const{
if( p->s352() == Types.s272 )
((s1604*)p)->s628 = s628;
else
throw new s16( L"No conversion to type " + s353() );}
#undef s698
#define s698 ((s1604*)(s484*)*s274)
inline void s1604::s1638( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
*((s346*)*s274)->s357() = (int)*( (s1604*)DR )->s628.get( s152 );}
inline void s1604::s1639( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
*((s359*)*s274)->s357() = ( (s1604*)DR )->s628.get( s152 )->to_wstring();}
inline void s1604::s1662( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
s346* pd  = (s346*)( (s1604*)DR )->s628.get( s152 );
*pd->s357() = (int)*s274[3];}
inline void s1604::s1664( s483** s274, size_t s498 ){
wstring s152 = s274[2]->to_wstring();
s359* pd  = (s359*)( (s1604*)DR )->s628.get( s152 );
*pd->s357() = s274[3]->to_wstring();}
inline void s1604::s1643( s483** s274, size_t s498 ){
s1604* po = (s1604*)DR;
wstring s77 = s274[2]->to_wstring();
po->load( s77, false );}
inline void s1604::s1641( s483** s274, size_t s498 ){
s1604* po = (s1604*)DR;
wstring s189 = s274[2]->to_wstring();
po->load( s189, true );}
void s1604::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << to_wstring();}
size_t s1604::s322() const{
return (size_t)this; //hash<bool>{}( s349 );
}
inline bool s1604::operator==( const s483* p ) const{
return this == p; // ( s628 == ( (s1604*)p )->s628 );
}
inline bool s1604::operator<( const s483* p ) const{
return this < p; // ( s628 < ( (s1604*)p )->s628 );
}
wstring s1604::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"Object: { \n";
s685 += s628.to_wstring( s1567 );
s685 += L"\n }";
return s685;}
void s1604::s1962( s1907& s ) {
load( s, false );}
s371::s371( s1907& s, s262* s300, s472 cat, bool _cnst )
: s484( s300, cat ), s372( s ), s376( 0 ), s1170( _cnst ){
assert( cat == s473 || cat == s475 || cat == s481 || cat == s1065 );
if( cat == s473 ) {
if( 0 && s[0] == L':' ) {
s492 = s1065;
s493 = Types.No;
s373 = (s483*)Types( s300, Types.No );}
else if( s300->s221( *this ) ){
s492 = s481;
s493 = Types.No;}
else
s492 = s475;}}
s371::s371( const s371& right )
: s484( right.s300, right.s492 ), s372( right.s372 ), s374( right.s374 ), 
s376( 0 ), s1170( right.s1170 ){
if( s492 == s481 )
s373 = right.s373;}
void s371::s500( const s272* s587, bool fr ){
if( false && s300->s221( *this ) ) {
s492 = s481;
s493 = Types.No;}
else {
if( !s587->s556( s372, this, s587->s834(), fr ) ) {
if( s492 == s1065 )
return;
throw new TDException( 0, s932, NULL, s372 );}
if( s374 )
s493 = s374->s352();
else if( s492 == s1339 )
s493 = s373.s15<s371*>()->s377()->s352();
else
assert( 0 );}
s1264();}
s483* s371::s377() const{
if( s492 == s1065 )
return s373.s15<s483*>();
else if( s492 == s1339 )
return s373.s15<s371*>()->s377();
if( s375.empty() )
return s373.s15<s483*>();
s484* s685 = s373.s15<s272*>()->s598( *(size_t*)&s375[0] );
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
void s371::s984( const std::vector<std::wstring> &s820 ){
auto it = std::find( begin( s820 ), end( s820 ), s617() );
if( it != end( s820 ) ) {
s492 = s1065;
s493 = Types.No;
s376 = std::distance( begin( s820 ), it );
s373 = new s346( NULL, (int)s376 ); //s779.s15<s483*>();
}}
s486 s371::s497( s483** s274, size_t s498 ){
return s377()->s497( s274, s498 );}
s483* s371::s496(){
return s377()->s496();}
/*bool s371::s501( const s483* s502 ) const
{
if( s502->s494() == s475 )
return s377()->s501( ((s371*)s502)->s377() );
return s377()->s501( s502 );
}*/
s271* s371::s335() const{
return new s371( *this );}
void s371::s379( size_t off, const s483* proto ){
s375.push_back( off );
s376 = s375.size();
s374 = proto;}
void s371::s1345( s371* ptr ){
s492 = s1339;
s375.clear();
s376 = 0;
s373 = ptr;
s374 = NULL;}
void s371::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"DataRef : " << s372;}
template<class s1314, class Der>
s336::s341 s1308<s1314, Der>::s348;
template<class s1314, class Der>
const s336::s341& s1308<s1314, Der>::s342() const{
return s348; }
template<class s1314, class Der>template <class s1532, class s1533>
void s1308<s1314, Der>::s1534( s483* src, s483* s778 ){
*((s1532*)s778)->s357() = (s1533) ( (Der*)src )->s349;}
template <class s1314, class Der>
s483* s1308<s1314, Der>::s1538( const s483* p ) const{
Der* s685 = new Der( p->Pass() );
if( p->s1543( s352() ) )
p->s356( s685 );
s685->s1264();
return s685;}
template <class s1314, class Der>
size_t s1308<s1314, Der>::s322() const{
return (size_t)s349;}
template <class s1314, class Der>
inline bool s1308<s1314, Der>::operator==( const s483* p ) const{
return ( (Der*)p )->s349 == s349;}
template <class s1314, class Der>
inline bool s1308<s1314, Der>::operator<( const s483* p ) const{
return s349 < ( (Der*)p )->s349;}
template <class s1314, class Der>
void s1308<s1314, Der>::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349 << endl;}
#define s1527 s493
template <class s1314, class Der>
void s1308<s1314, Der>::s350(){
s348.insert( make_pair( L"abs", new s337( L"abs", &s1308<s1314, Der>::s404, s1527,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s1308<s1314, Der>::s387, s1527,
{ s1124( { /*Der::proto->s352()*/ s1514::s1273 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"sum", new s337( L"sum", &s1308<s1314, Der>::s388, s1527,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"dif", new s337( L"dif", &s1308<s1314, Der>::s389, s1527,
{ s1124( ), s1124( { s1514::s1273, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"mul", new s337( L"mul", &s1308<s1314, Der>::s390, s1527,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"div", new s337( L"div", &s1308<s1314, Der>::s391, s1527,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"pow", new s337( L"pow", &s1308<s1314, Der>::s392, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"pow", new s337( L"pow", &s1308<s1314, Der>::s392, s1152,
{ s1124( { s1152 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"sumeq", new s337( L"sumeq", &s1308<s1314, Der>::s393, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"difeq", new s337( L"difeq", &s1308<s1314, Der>::s394, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"muleq", new s337( L"muleq", &s1308<s1314, Der>::s395, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"diveq", new s337( L"diveq", &s1308<s1314, Der>::s396, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.insert( make_pair( L"not", new s337( L"not", &s1308<s1314, Der>::s413, s1150,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s1308<s1314, Der>::s398, s1150,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"less", new s337( L"less", &s1308<s1314, Der>::s399, s1150,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"greater", new s337( L"greater", &s1308<s1314, Der>::s400, s1150,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"leq", new s337( L"leq", &s1308<s1314, Der>::s401, s1150,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"geq", new s337( L"geq", &s1308<s1314, Der>::s402, s1150,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"neq", new s337( L"neq", &s1308<s1314, Der>::s403, s1150,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"max", new s337( L"max", &s1308<s1314, Der>::s1967, s1527,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"min", new s337( L"min", &s1308<s1314, Der>::s1968, s1527,
{ s1124( { s1514::s1551, s7::s1401 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"mod", new s337( L"mod", &s1308<s1314, Der>::s405, s1527,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"sqrt", new s337( L"sqrt", &s1308<s1314, Der>::s406, s1152,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"nroot", new s337( L"nroot", &s1308<s1314, Der>::s407, s1152,
{ s1124( { s1153 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"to-Double", new s337( L"to-Double", &s1308<s1314, Der>::s408, s1152,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Byte", new s337( L"to-Byte", &s1308<s1314, Der>::s1598, s1310,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s1308<s1314, Der>::s412, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-Long", new s337( L"to-Long", &s1308<s1314, Der>::s1549, s1528,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"to-ULong", new s337( L"to-ULong", &s1308<s1314, Der>::s1550, s1529,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"read", new s337( L"read", &s1308<s1314, Der>::s409, s1527,
{ s1124() }, 0, 0, false ) ) );}
template<class s1314, class Der>
s1063 s1308<s1314, Der>::
s1190( const std::wstring& s1555, const std::vector<s485>& l ) const{
s1063 s685 = 0;
if( 0 && s1555 == L"mod" )
s685 = this->s352();
return s685;}
#undef s698
#define s698 ((Der*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
template<class s1314, class Der>
inline void s1308<s1314, Der>::s387( s483** s274, size_t n ){
s274[2]->s356( s274[1] );
s274[1]->s1264();}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s404( s483** s274, size_t s498 ){
s1314 t = ( (Der*)DR )->s349;
if( t >= 0 )
s698->s349 = t;
else
s698->s349 = -t;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s388( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 += tmp.s349;}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s389( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
if( s498 == 2 )
s698->s349 = -s698->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 -= tmp.s349;}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s390( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 *= tmp.s349;}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s391( s483** s274, size_t s498 ){
Der tmp;
s698->s349 = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
s698->s349 /= tmp.s349;
}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s392( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
s698->s349 =(s1314) std::pow( (double)( (Der*)DR )->s349, (double)s698->s349 );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s393( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 += s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s394( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 -= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s395( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 *= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s396( s483** s274, size_t s498 ){
s274[2]->s356( s274[0] );
( (Der*)DR )->s349 /= s698->s349;
s698->s349 = ( (Der*)DR )->s349;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s398( s483** s274, size_t s498 ){
bool s685 = true;
Der tmp;
for( size_t i = 2; i < s498; ++i ) {
s274[i]->s356( &tmp );
if( ( (Der*)DR )->s349 != tmp.s349 ) {
s685 = false;
break;}}
*s699->s357() = s685;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s413( s483** s274, size_t s498 ){
if( ((bool)( (Der*)DR )->s349) == false )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s399( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 < tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s400( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 > tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s401( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 <= tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s402( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 >= tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = true;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s403( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( ( (Der*)DR )->s349 != tmp.s349 )
*s699->s357() = true;
else
*s699->s357() = false;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1967( s483** s274, size_t s498 ){
Der tmp;
*s698->s357() = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
if( *s698->s357() < tmp.s349 )
*s698->s357() = tmp.s349;}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1968( s483** s274, size_t s498 ){
Der tmp;
*s698->s357() = ( (Der*)DR )->s349;
for( size_t n = 2; n < s498; ++n ) {
s274[n]->s356( &tmp );
if( *s698->s357() > tmp.s349 )
*s698->s357() = tmp.s349;}}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s405( s483** s274, size_t s498 ){
Der tmp;
s274[2]->s356( &tmp );
if( tmp.s349 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s698->s349 = ((Der*)DR)->s349 % tmp.s349;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s406( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = ::sqrt( (double)*DR );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s407( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = ::pow( ((Der*)DR)->s349, 1.0 / (double)*PARN( 2 ) );
}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s408( s483** s274, size_t s498 ){
*( (s358*)s274[0] )->s357() = (double)*DR;}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1598( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s412( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1549( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1550( s483** s274, size_t s498 ){
s274[1]->s356( s274[0] );}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s1503( s483** s274, size_t s498 ){
*( (s359*)s274[0] )->s357() = DR->to_wstring();}
template<class s1314, class Der>
inline void s1308<s1314, Der>::s409( s483** s274, size_t s498 ){
int i;
wstring s93 = L"";//( (s359*)s274[2] )->to_wstring();
wstring si = consutils::s100( s93, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s698->s349 = i;}
s346::s346( s262* s300 )
: s1308( s300, NULL, NULL ){
s493 = Types.Int;
s349 = (s1388)s300->TR().s1259();
s1681( s7::s868 );}
s346::s346( s262* s300, int i )
: s1308( s300, NULL, NULL ){
if( !Types.Bool ) {
s493 = 0;
wh = s7::s868;}
else {
s493 = Types.Int;
s349 = i;
s1264();}}
s346::s346( const s346& r )
: s1308( r ){}
s346::s346( s262* s300, const std::wstring& s, size_t& pos )
: s1308( s300, NULL, NULL ){
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
s1264();}
else
s153 = s300->TR().s1259();
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
return s1523;
try {
s685 = new s346( s300, s, pos );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
s685 = NULL;
else
throw e;}}
return s685;}
void s346::s350(){
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );
s300->TR().s1164( s493, s7::s1526, s1514::s1551 );
s1308<int32_t, s346>::s350();
s348 = s1308<int32_t, s346>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s346::s1238, s1153,
{ s1124(), s1124( { Types.String } ), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s300->TR().s1535( s493, Types.Long );}
s483* s346::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s346( s300, L"", pos );}
void s346::s500( const s272* s879, bool ){
s1264();}
inline bool
s346::s1543( s1063 s619 ) const{
if( ( s619 == s1529 && s349 >= 0 ) ||
( s619 == s1310 && s349 >= 0 && s349 <= 255 ) )
return true;
return s271::s1543( s619 );}
s271* s346::s335() const{
return new s346( *this );}
void s346::s356( s271* p ) const{
if( p->s352() == Types.Int )
*((s346*)p)->s357() = s349;
else if( p->s352() == s1310 )
*((s1297*)p)->s357() = s349;
else if( p->s352() == s1528 )
*((s1305*)p)->s357() = s349;
else if( p->s352() == s1529 )
*((s1531*)p)->s357() = s349;
else if( p->s352() == s1150 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"No conversion to type " + p->s353() );}
inline void s346::s1238( s483** s274, size_t s498 ){
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
if( p->s352() == s1153 )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == s1152 )
lv.s349 = ( s1388 )*( (s358*)p )->s357();
else if( p->s352() == s1150 )
lv.s349 = ( s1388 )*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Int from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Int() constructor" );}
plv->s1264();
s274[0] = plv;}
wstring s346::to_wstring( uint32_t s1567 ) const {
wstring s685;
if( s349 > 0 && ( s1567 & s1562 ) )
s685 = L"+";
if( s1567 & s1561 )
s685 += s4::s1566( s349 );
else
s685 += std::to_wstring( s349 ); 
return s685;}
void s346::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
ss << s349;}
void s346::to_null(){
s271::to_null();
s349 = 0;}
void s346::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349;}
s1305::s1305( s262* s300 )
: s1308( s300, NULL, NULL ){
s493 = Types.Long;
s349 = s300->TR().s1259();
s1681( s7::s868 );}
s1305::s1305( s262* s300, int64_t i )
: s1308( s300, NULL, NULL ){
if( !Types.Long ) {
s493 = 0;
s1681( s7::s868 );}
else {
s493 = Types.Long;
s349 = i;
s1264();}}
s1305::s1305( const s1305& r )
: s1308( r ){}
s1305::s1305( s262* s300, const std::wstring& s, size_t& pos )
: s1308( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1546( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1264();}
else
s153 = s300->TR().s1259();
s349 = (int64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Long;}
void s1305::s350(){
s1308<int64_t, s1305>::s350();
s348 = s1308<int64_t, s1305>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1305::s1238, s1528,
{ s1124(), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );
s300->TR().s1164( s493, s7::s1526, s1514::s1551 );}
s483* s1305::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1305( s300, L"", pos );}
void s1305::s500( const s272* s879, bool ){
s1264();}
s271* s1305::s335() const{
return new s1305( *this );}
void s1305::s356( s271* p ) const{
if( p->s352() == Types.Long )
*((s1305*)p)->s357() = s349;
else if( p->s352() == s1153 )
*((s346*)p)->s357() = (s346::s1388)s349;
else if( p->s352() == s1529 )
*((s1531*)p)->s357() = s349;
else if( p->s352() == s1150 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1305::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1305( s300, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1305( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1305::s1238( s483** s274, size_t s498 ){
s1305* plv = new s1305( ( (s1305*)s274[1] )->s300, (s1388)0 );
s1305& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if (s498 == 3){
s483* p = s274[2];
if( p->s352() == Types.Int )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == s1152 )
lv.s349 = (s1388)*( (s358*)p )->s357();
else if( p->s352() == s1150 )
lv.s349 = (s1388)*( (s360*)p )->s357();
else
throw new s16( L"no conversion to Long from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1264();
s274[0] = plv;}
wstring s1305::to_wstring( uint32_t s1567 ) const{
wstring s685;
if( s349 > 0 && ( s1567 & s1562 ) )
s685 = L"+";
if( s1567 & s1561 )
s685 += s4::s1566( s349 );
else
s685 += std::to_wstring( s349 );
return s685;}
void s1305::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
ss << s349;}
s1531::s1531( s262* s300 )
: s1308( s300, NULL, NULL ){
s493 = Types.s1530;
s349 = s300->TR().s1259();
s1681( s7::s868 );}
s1531::s1531( s262* s300, int64_t i )
: s1308( s300, NULL, NULL ){
if( !Types.s1530 ) {
s493 = 0;
s1681( s7::s868 );}
else {
s493 = Types.s1530;
s349 = i;
s1264();}}
s1531::s1531( const s1531& r )
: s1308( r ){}
s1531::s1531( s262* s300, const std::wstring& s, size_t& pos )
: s1308( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1547( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1264();}
else
s153 = s300->TR().s1259();
s349 = (uint64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.s1530;}
void s1531::s350(){
s1308<s1388, s1531>::s350();
s348 = s1308<s1388, s1531>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1531::s1238, s1529,
{ s1124(), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"abs", new s337( L"abs", &s1531::s404, s1529,
{ s1124(), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s348.insert( make_pair( L"dif", new s337( L"dif", &s1531::s389, s1529,
{ s1124(), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );
s300->TR().s1164( s493, s7::s1526, s1514::s1551 );}
s483* s1531::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1531( s300, L"", pos );}
void s1531::s500( const s272* s879, bool ){
s1264();}
s271* s1531::s335() const{
return new s1531( *this );}
void s1531::s356( s271* p ) const{
if( p->s352() == Types.s1530 )
*((s1531*)p)->s357() = s349;
else if( p->s352() == s1528 )
*((s1305*)p)->s357() = s349;
else if( p->s352() == s1153 )
*((s346*)p)->s357() = (s346::s1388)s349;
else if( p->s352() == s1150 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1531::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1531( s300, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1531( s300, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1531::s1238( s483** s274, size_t s498 ){
s1531* plv = new s1531( ( (s1531*)s274[1] )->s300, (s1388)0 );
s1531& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if (s498 == 3){
s483* p = s274[2];
if( p->s352() == Types.Int )
lv.s349 = *( (s346*)p )->s357();
else if( p->s352() == Types.Long )
lv.s349 = *( (s1305*)p )->s357();
else if( p->s352() == Types.Double )
lv.s349 = (s1388)*( (s358*)p )->s357();
else if( p->s352() == Types.Bool )
lv.s349 = (s1388)*( (s360*)p )->s357();
else
throw new s16( L"no conversion to ULong from type: " + p->s353() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1264();
s274[0] = plv;}
wstring s1531::to_wstring( uint32_t s1567 ) const{
wstring s685;
if( s349 > 0 && ( s1567 & s1562 ) )
s685 = L"+";
if( s1567 & s1561 )
s685 += s4::s1566( s349 );
else
s685 += std::to_wstring( s349 );
return s685;}
void s1531::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
ss << s349;}
s1297::s1297( s262* s300 )
: s1308( s300, NULL, NULL ){
s493 = Types.Byte;
s349 = (s1388)s300->TR().s1259();
s1681( s7::s868 );}
s1297::s1297( s262* s300, tdbyte_t i )
: s1308( s300, NULL, NULL ){
s493 = Types.Byte;
if( !s493 )
s1681( s7::s868 );
else {
s349 = i;
s1264();}}
s1297::s1297( const s1297& r )
: s1308( r.s300, r.ns, NULL ){
wh = r.wh;
s493 = r.s493;}
s1297::s1297( s262* s300, const std::wstring& s, size_t& pos )
: s1308( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s153, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1681( s7::s867 );}
else
s153 = s300->TR().s1259();
s349 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Byte;}
void s1297::s350(){
s1308<tdbyte_t, s1297>::s350();
s348 = s1308<tdbyte_t, s1297>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1297::s1238, s1310,
{ s1124(), s1124( { s1514::s1273 } ) }, 0, 1 ) ) );
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );
s300->TR().s1164( s493, s7::s1526, s1514::s1551 );}
s483* s1297::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1297( s300, L"", pos );}
void s1297::s500( const s272* s879, bool ){
s1264();}
s271* s1297::s335() const{
return new s1297( *this );}
void s1297::s356( s271* p ) const{
if( p->s352() == Types.Byte )
*((s1297*)p)->s357() = s349;
else if( p->s352() == s1528 )
*((s1305*)p)->s357() = s349;
else if( p->s352() == s1529 )
*((s1531*)p)->s357() = s349;
else if( p->s352() == s1150 )
*( (s360*)p )->s357() = (s349 != 0);
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1297::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1297( s300, s, pos );
}*/
if( s701.s1311() == s352() )
return new s1297( s300, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1297( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
inline void s1297::s1238( s483** s274, size_t s498 ){
s1297* plv = new s1297( ( (s1297*)s274[1] )->s300, 0 );
s1297& lv = *plv;
if( s498 == 2 )
lv.s349 = 0;
else if( s498 == 3 )
s274[2]->s356( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1264();
s274[0] = plv;}
void s1297::s1937( Stream* s1936 ) const{
auto flags = s1936->s1932();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s349;
s1936->s1482( ss.str() );}
s1575::s1575( s262* s300 )
: s1308( s300, NULL, NULL ){
s493 = Types.Char;
s349 = (s1388)s300->TR().s1259();
s1681( s7::s868 );}
s1575::s1575( s262* s300, wchar_t i )
: s1308( s300, NULL, NULL ){
s493 = Types.Char;
if( !s493 )
s1681( s7::s868 );
else {
s349 = i;
s1264();}}
s1575::s1575( const s1575& r )
: s1308( r.s300, r.ns, NULL ){
wh = r.wh;
s493 = r.s493;}
s1575::s1575( s262* s300, const std::wstring& s, size_t& pos )
: s1308( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s153, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1681( s7::s867 );}
else
s153 = s300->TR().s1259();
s349 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s493 = Types.Char;}
void s1575::s350(){
s1308<wchar_t, s1575>::s350();
s348 = s1308<wchar_t, s1575>::s342();
s300->TR().s1164( s493, s7::s1415, s1514::s1273 );
s300->TR().s1164( s493, s7::s1526, s1514::s1551 );}
s483* s1575::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1575( s300, L"", pos );}
void s1575::s500( const s272* s879, bool ){
s1264();}
s271* s1575::s335() const{
return new s1575( *this );}
void s1575::s356( s271* p ) const{
if( p->s352() == Types.Char )
*( (s1575*)p )->s357() = s349;
else if( p->s352() == s1528 )
*( (s1305*)p )->s357() = s349;
else if( p->s352() == s1529 )
*( (s1531*)p )->s357() = s349;
else if( p->s352() == s1150 )
*( (s360*)p )->s357() = ( s349 != 0 );
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = (double)s349;
else
throw new s16( L"no conversion from " + s353() + L"to " + p->s353() );}
s483* 
s1575::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
size_t pos = 0;
if( s701.s1311() == s352() )
return new s1575( s300, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1575( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s355( NULL, std::vector<s271*>(), &s701 );}
return 0;}
void s1575::s1937( Stream* s1936 ) const{
auto flags = s1936->s1932();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s349;
s1936->s1482( ss.str() );}
const wstring s471 = L"";
s482 s687;
s272::s272( s262* s300, s1063 s340, s472 pc/* = s473*/, const s263* ast_ )
: s483( s300, pc, ast_, NULL ), s625(NULL), s626(NULL), 
s1665( s7::s1603, s300, s475 ), s347( s471 ), //s633( s687 ),
s629( NULL )//, s1362( ++s1363 )
{
s625 = this;
s493 = s340;}
s272::s272( const s272& proto, std::vector<s485>& s705, const s263* ast_ )
: s483( proto.s300, s480, ast_, proto.ns ), s625( &proto ), s626(NULL), 
s1665( s7::s1603, s300, s475 ), s347( proto.s347 ),
s629( proto.s629 ), //s633( s687 ),
s631( proto.s631 )//, s1362( ++s1363 )
{
s493 = proto.s493;
if( s492 == s478 )
s492 = s480;
if( proto.s626 )
proto.s626->s643( this );
proto.s628.copy( s628, this, NULL, s482::s147 );
for( size_t n = 0; n < s631.size(); ++n )
s630.push_back( s628.get( s631[n].s617() ) );
if( s705.size() ) {
s842* p = (s842*) s628.get( s7::s429 );
p->s596( s705 );
p->s500( this, false );
p->s497( 0, 0 );}}
s272::s272( s1907& s676, s262* s300, s472 pc, const s263* ast_ )
: s483( s300, pc, ast_, NULL ), s625(NULL), s626(NULL), 
s1665( s7::s1603, s300, s475 ), s347( s471 ), s278( s676 ),
s629( NULL )//, s1362( ++s1363 )//, s633( *new s482() )
{
s625 = this;}
s272::s272( s263& s701, s262* s300, s472 pc, s272* ns_, s536 am,
s623& cl, s622& cnl, s624& al )
: s483( s300, pc, &s701, ns_ ), s625(NULL), s626( NULL ), 
s1665( s7::s1603, s300, s475 ), s347( s701.s299() ), s278( s701.s298() ),
s628( am ), s629( NULL )//, s1362( ++s1363 ) //,s633( *new s482() )
{
if( s278.find( L" " ) != string::npos )
throw new s16( L"Malformed class name: " + s278 );
s625 = this;
if( pc == s478 ) {
wstring anc = L"";
try {
const s263* s693 = s701.s292( s7::s469 );
anc = s693->s291();}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw e;}
cnl.push_back( make_pair( s701.s299(), anc ) );
if( cl.find( s701.s299() ) != cl.end() )
throw new s16( L"class already exists: " + s701.s299() );
cl.insert(make_pair(s701.s299(), this));}
if( al.find( s701.s299() ) != al.end() )
throw new s16( L"object already exists: " + s701.s299() );
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
s272* ob = new s272( *it->second, s300, s478, this, am, cl, cnl, al );
s628.s541( ob->s299(), ob );}}}
for( size_t n = 0; n < s694.size(); ++n ) {
auto it = s702.find( s694[n].first );
s702.insert(make_pair(s694[n].second, it->second ));
s702.erase( it );}}
s272::~s272(){}
s483* s272::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
s272::s730( s1907& f ) const{
return s628.s156( f );}
void s272::s154( s263& s701 ){
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
else if( s76 == s7::s938 )
s972( *node );
else {
size_t s689 = s76.find_first_of( s4::s48 );
bool s1205 = false;
if( s689 != string::npos ) {
vector<wstring> s688;
s4::s57( s76, wstring( 1, s76[s689] ), s688 );
if( s688.size() > 2 )
throw new s16( L"malformed object declaration: " + s76 );
if( s688[0] == s7::s1142 ) {
s1205 = true;
s76 = s688[1];}
node->s294( s76 );}
lang::s656( s76 );
s483* dv = NULL;
try {
dv = s300->TR().s518( *node, this, s278 );}
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
s631.push_back( s371( node->s299(), s300, s475, s1205 ) );}}
else if( node->s297() == s227 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s272* ob = (s272*)s628.get( it->first );
ob->s154( *it->second );}}
else if( node->s297() == s228 ) {
s483* dv = new s359( s300, node->s291(), this, node );
dv->s506( node->s299() );
dv->s1262( true );
wstring s1676 = node->s299();
if( node->s299() == s7::s465 )
s1676 = L"name";
try {
s628.s541( s1676, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s278 + L"::" + node->s299() );}
throw e;}
s630.push_back( dv );
s631.push_back( s371( s1676, s300 ) );}}
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
e->s1078( TDException::Stage::s1027 );
e->s30( L"while compiling function '" +s278 + L"::" + node->s299() + L"'" );
s1016.s973( e->Msg( 0 ) );}}}
if( s492 == s478 ) {
s1359* s1366 = new s1359( s300, this, NULL, NULL );
s628.s541( s7::s1358, s1366 );
s630.push_back( s1366 );
s631.push_back( s371( s7::s1358, s300 ) );}}
void s272::s500( const s272* s879, bool ){
if( s492 == s478 || s492 == s479 ) {
if( s627.size() ) {
s626 = (s272*)s300->s222( s627, s879->s834() );
s626->s629->copy( *s629 );}
if( s629 )
s629->s500( s300, s278 );
else
s629 = s625->s629;
s628.s500( /*s879*/this, (s492 == s478));
}
else {
if( s300->s1332()) {
if( s628.s156( s7::s429 ) ) {
vector<s484*> s274;
s274.push_back( this );
s842* p = (s842*)s628.get( s7::s429 );
if( p->s618() == s7::s868 )
p->s500( s879, true );
else
p->s597( s879 );
if( s494() == s480 )
p->s497( (s483**)&s274[0], 1 );}
s628.s500( this, true);}
s629 = s625->s629;}
ns = (s272*)s879;}
void s272::s1651(){
if( s494() != s479 || s618() == s7::s867 )
return;
if( s628.s156( s7::s428 ) ) {
vector<s485> s274;
s274.push_back( this );
s842* p = (s842*) s628.get( s7::s428 );
p->s500( (s272*)ns, true );
p->s596( s274 );
p->s497( (s483**)&s274[0], 1 );}
if( s629 ) 
s629->s1651( s300 );
s1264();}
void s272::s643( s272* s646 ) const{
if( s626 )
s626->s643( s646 );}
void s272::s645( s263& s701 ){
if( !s629 )
s629 = new s551();
s629->s554( s701.s291() );
return;}
void s272::s639( s1907& s334,	vector<wstring>& s153 ){
s628.s533( s334, s153 );}
void s272::s555( s1907& s76, s1907& s558 ){
if( !s629 )
s629 = new s551();
s629->s555( s76, s300, s558 );}
void s272::s638( s263& s701 ){
s626 = (s272*)s300->s222( s627, s278 );}
void s272::s972( s263& s701 ){
wstring s997 = L"wrong syntax of class attributes: " + s701.s291();
s486 dv = s300->TR().s518( s701, this, s278 );
if( dv->s352() != s1721 )
throw new s16( s997 );
vector<s485>& v = dv.s15<s316*>()->s320();
for( auto s_ : v ) {
wstring s = s_.s15<s359*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s997 );
wstring cat = s4::s52( s.substr( 0, pl ), s4::s48 );
vector<wstring> s153;
s4::s57( s.substr( pl + 1 ), L",", s153 );}}
bool s272::s556( s1907& sym_, s371* ref, s1907& s334,
bool fr ) const{
bool s685 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s686 = sym_.substr( 0, pl );
s272* ob = ((s272*)s641( s686, s334, false ));
if( !ob && s686 == s7::s1603 )
ob = (s272*)this;
if( ob ) {
s371 s1660( *ref );
s685 = ob->s556( sym, &s1660, s334, fr );
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
if( s631[off].s1205() )
ref->s1262();
s685 = true;}
else {
if( sym == s7::s1603 ) {
ob = this;
if( !ref->s380() )
ref->s382( ( s483* )this );
ref->s379( s1149, ob );
s685 = true;}
else if( s629 )
s685 = s629->s556( sym, ref );}}
return s685;}
size_t s272::s640( s1907& s647 ) const{
if( s647 == s7::s1603 )
return s1149;
for( size_t n = 0; n < s630.size(); ++n ) {
if( s631[n].s617() == s647 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s647 );}
s271* s272::s598( size_t off ){
if( off == s1149 )
return this;
return s630[off];}
void s272::s851( s1907& s76, s483* s349, s482::s145 ap ){
s628.s541( s76, s349, ap );
s630.push_back( s349 );
s631.push_back( s371( s76, s300 ) );}
void s272::s1659( s1907& s76, s483* s349 ){
if( !s628.s156( s76 ) )
throw new s16( L"no such member: " + s76 );
s628.s541( s76, s349, s482::s147 );
for( size_t n = 0; n < s631.size(); ++n ) {
if( s631[n].s617() == s76 )
s630[n] = s349;}}
void s272::s1642( const s1604* ob ){
s630.clear();
s625->s628.s1615( s628 );
for( size_t n = 0; n < s631.size(); ++n )
s630.push_back( s628.get( s631[n].s617() ) );
s482::s535 sm;
ob->s1634( sm );
s482::s535::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s628.s541( it->first, it->second.s15<s483*>(), s482::s147 );
else {
if( !s628.s156( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
it->second.s15<s483*>()->s356( s628.get( it->first ) );}}
for( size_t n = 0; n < s631.size(); ++n )
s630[n] = s628.get( s631[n].s617() );}
s483* s272::s641( s1907& sym, s1907& s334,	bool s520/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s272* mod = (s272*) s628.get( smod, s520 );
if( !mod )
return NULL;
return mod->s641( sym1, s334, s520 );}
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
bool s272::s642( const wstring& sym, s1907& s499 ) const{
if( s499 == s347 )
return true;
return s628.s550( sym, s499 );}
s1063 s272::s386( s1907& s343 ) const{
s483* s690 = s628.get( s343 );
s1063 s685 = s690->s352();
if( s685 == 0 ) {
s690->s500( (s272*)this );
s685 = s690->s352();}
return s685;}
s483* s272::s635( const s263& s701, s483* s588, s1907& s334 ) const{
vector<wstring> s691;
vector<s485> s274;
s272* s685 = new s272( *this, s274, &s701 );
size_t pos = s701.s291().find( L"(" );
size_t pos_ = pos;
s263::s288( s701.s291(), pos, s691 );
if( s691.size() ) {
s591* s692 = (s591*) s628.get( s7::s428, false );
if( !s692 )
throw new TDException( 0, s934, &s701, 
L"Arguments passed to a class without init function." );
else {
wstring str = s701.s291();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s7::s428 );
s263* ast_ = new s263( s7::s429, s141( str ) );
s490 cs = (s561*)s271::s504( *ast_, s300, s685, s334 );
s591* td = s591::s600(
cs, s300, s685, (s591*)s685, s278, false );
s685->s628.s541( s7::s429, td );}}
return s685;}
s483* s272::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
vector<wstring> s691;
vector<s485> s274;
s272* s685 = new s272( *this, s274, s603() );
if( l.size() ) {
s591* s692 = (s591*)s628.get( s7::s428, false );
if( !s692 )
throw new TDException( 0, s934, ast_,
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
else if( s494() == s476 || s494() == s1247 )
return s834();
assert( 0 );
return /*s277 + L"::" +*/ s278;
}
s483* s272::s344( s1907& s676, s1907& s334,
bool s520 /*= true*/ ) const
{
s371 ref( s676, s300 );
if( !s556( s676, &ref, s334, true ) )
return NULL;
return ref.s378();}
s591* s272::s1687( s1907& s676, s591* s215,
s561* cs ) const{
if( s676 == L"getf" ) {
return new s1682( s300, (s272*)this, s215, &s272::s1706, cs, 
NULL );}
return s483::s1687( s676, s215, cs );}
s483* s272::s1706( s483** s274, size_t s498 ){
s359* pv = (s359*) s274[1];
return s628.get( pv->to_wstring() );}
s271* s272::s335() const{
vector<s485> v;
return new s272( *this, v, NULL );}
void s272::s356( s271* p ) const{
s272* pob = (s272*)p;
s628.s1615( pob->s628 );
for( size_t n = 0; n < pob->s631.size(); ++n ) {
pob->s630[n] = pob->s628.get( pob->s631[n].s617() );}
return;
throw new s16( L"" );
vector<wstring> fields;
s628.s545( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s483*)s628.get( fields[n] ))->s356( p );}
size_t s272::s322() const{
return (size_t)this;}
bool s272::operator==( const s483* p ) const{
return (this == p);}
bool s272::operator<( const s483* p ) const{
return false;}
wstring s272::to_wstring( uint32_t s1567 ) const{
if( s628.s156( s7::s1631 ) ) {
s591* s1657 = (s591*)s628.get( s7::s1631 );
s9<s507> s1655 = new s507( (s262*)s300, (s272*)this, s603() );
vector<s485> s705 = { /*(s271*)this,*/ s1655 };
s1657->s596( s705 );
if( s1657->s618() != s7::s867 )
s1657->s500( this, false );
else
s1657->s597( this );
s1657->s497( 0, 0 );
return s1655->to_wstring();}
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
/*s372 <<*/ L": " << this << endl;
s628.s304( pd, s197 + s419 );}
s591* s591::s599( const s263& s701, s262* s300, s272* obj,
const wstring& s278, const wstring& s558 ){
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
std::vector<s271*> s274;
for( size_t n = 0; n < s697; ++n ) {
s263::s275::const_iterator it = s702.find( std::to_wstring( n ) );
if( it->second->s291() == s7::s942 )
s274.push_back( s873 );
else if( it->second->s291() == s7::s1142 )
s274.push_back( s1688 );
else
s274.push_back( s271::s504( *it->second, s300, obj, s558 ) );}
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
s685 = new s842( s300, obj, NULL, s568, s274, &s701 );
s272* pAnc = (s272*)s300->s222( obj->s637(), s558 );
((s604*)pAnc->s344( s688[1], s558 ))->s648( obj->s352(),
s685 );
s685->s278 = s688[1];
s685->s594( s574 );}
else
throw new s16( L"malformed function name: " + s278 );}
else {
s685 = new s842( s300, obj, NULL, s568, s274, &s701 );
s685->s278 = s278;}
return s685;}
s561* s591::s1121( const s263& s701, s262* s300, s272* obj,
const wstring& s558 ){
const s263::s275& s702 = s701.s293();
size_t s697 = s702.size();
wstring s601 = s701.s291();
std::vector<s271*> s274;
s561* s685 = NULL;
try {
for( size_t n = 0; n < s697; ++n ) {
s263::s275::const_iterator it = s702.find( std::to_wstring( n ) );
it->second.s15<s263*>()->s269( L"ownerType", L"CallSite" );
it->second.s15<s263*>()->s269( L"ownerName", s601 );
if( it->second->s291() == s7::s942 )
s274.push_back( s873 );
else if( it->second->s291() == s7::s1142 )
s274.push_back( s1688 );
else
s274.push_back( s271::s504( *it->second, s300, obj, s558 ) );}
s685 = new s561( s300, s601, s274, &s701 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s601 + L"' function call" );}
return s685;}
void s561::s500( const s272* s879, bool ){
return;
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s500( s879 );}}
s271* s561::s335() const{
return new s561( *this );}
s591* s591::s600( s561* cs, s262* s300, s272* s588, s591* s215, 
const wstring& s558, bool proc ){
wstring s601 = cs->s299();
wstring s704 = s588 ? s588->s298() : L"::";
s485 s703 = NULL;
std::vector<s271*>& s274 = cs->s602();
s488 s706 = NULL;
s591* s685 = NULL;
size_t pl = s601.find( L"<" );
try {
if( pl == string::npos ) {
auto s1453 = s1373.find( s601 );
if( s1453 != end( s1373 ) && BIFuncs1v[s1453->second] )
return s300->s214( s1453->second, cs->s602(), s588, s215, cs->s603() );
s271* par = NULL;
int s1365 = 0;
s1361:
if( s274.size() ) {
par = s274[s1365];
s472 pc = par->s494();
if( pc == s475 ) {
try {
par->s500( s215, true );}
catch( TDException* e ) {
if( e->Category() != s932 || (
( (s371*)par )->s617()[0] != L':' && ( (s371*)par )->s617().back() != L':' ) )
throw e->s30( L"while compiling function '" + s601 + L"'" );
s1365++;
goto s1361;}
if( ( (s371*)par )->s381().s14() ) {
if( ( (s371*)par )->s617() == s7::s430 )
par = s588;
s703 = ( (s371*)par )->s377();}}
else {
if( pc == s477 ) {
s490 cs = new s561( *(s561*)par );
par = s600( cs, s300, s588, s215, s558, proc );
( (s591*)par )->s500( s588, false );}
else {
par->s500( s215 );}}
if( par->s494() == s475 /*||  par->s494() == s1339*/ ) {
(void)0;}
else if( par->s494() == s1065 || par->s494() == s481 )
s703 = NULL;
else {
s703 = par->s496();}
s274[s1365] = par;}
else {
s706 = (s591*)s588->s344( s601, s704, false );
if( !s706 )
throw new s16( L"Procedure is not resolved: " + s601 );}
if( s1453 != end( s1373 ) )
return s300->s214( s1453->second, s274, s588, s215, cs->s603() );}
else {
wstring s619 = s601.substr( pl + 1, s601.size() - pl - 2 );
s601 = s601.substr( 0, pl );
try {
s1063 pt = s300->TR().s1012( s619, false );
if( !pt ) {
s949 ast2 = new s263( s619 + L"()", cs->s603()->Nqj() );
s703 = s300->TR().s518( *ast2, s588, s558 );}
else
s703 = s300->TR().s1009( pt )->s355( s215, s274, s215->s603() );}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s601 + L"' function " );
s949 ast2 = new s263( s619 + L"()", cs->s603()->Nqj() );
s703 = s300->TR().s518( *ast2, s588, s558 );}
s274.insert( s274.begin(), s703 );}
s488 s707 = NULL;
s1144 s1239;
if( !s706 ) {
s472 s710 = s703->s494();
if( s710 == s475 ) {
s371* ref = (s371*)s703.s15<s484*>();
s703 = (s483*)ref->s503();
s710 = s703->s494();}
try {
assert( s710 != s479 );
if( s710 == s480 || s710 == s478 ) {
s707 = (s591*)s703.s15<s272*>()->s344( s601, s704,
false );}
else if( s710 == s474 )
s1239 = s703.s15<s336*>()->s1199( s601 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s707 && !s1239.s339 )
s706 = (s591*)s588->s344( s601, s704, false );
if( !( s1239.s339 || s706 || s707 ) ) {
s591* ptd = s703.s15<s272*>()->s1687( s601, s215, cs );
if( ptd )
return ptd;
throw new s16( L"Method is not resolved: " + s601 );}}
if( s1239.s339 ) {
s685 = new s841( s300, s215, s566, s274, s1239.s338, s601, cs->s603() );}
else if( s706 ) {
if( s601 == L"new" ) {
assert( 0 );
vector<s271*> s1666( s274.begin() + 1, s274.end() );
s685 = new s1359( *s706.s15<s1359*>(), s588, s215, s1666,
cs->s603() );}
else {
s685 = new s842( /**td*/ *s706.s15<s842*>(), /*s588,*/ s215, s274,
s567, cs->s603(), /*s588*/ s706->s588 );
}}
else if( s707 ) {
if( s601 == L"new" ) {
s685 = new s1359( *s707.s15<s1359*>(), s703.s15<s272*>(), s215, s274,
cs->s603() );}
else {
s9<s842> td = ( (s842*)s707->s335() );
s685 = new s842( *td, /*s703.s15<s272*>(),*/ s215, s274, s568,
cs->s603(), s703.s15<s272*>() );}
if( s707->s595() == s573 )
s685->s575 = s569;
else
s685->s575 = s568;}}
catch( s16* e ) {
throw e->s30( L"while compiling function '" + cs->s603()->Src() + L"'" );}
s685->s278 = s601;
return s685;}
void s591::s1244( vector<s271*>& s274, const vector<wstring>& s1210 ){
for( s271* p : s274 ) {
if( p->s494() == s475 || p->s494() == s1065 )
( (s371*)p )->s984( s1210 );}}
void s591::s1244( vector<s485>& s274, const vector<wstring>& s1210 ){
for( s271* p : s274 ) {
if( p->s494() == s475 )
( (s371*)p )->s984( s1210 );}}
s591::s591( s262* s300, s272* s592, s591* s593, s563 ct,
const std::vector<s271*>& l,	const s263* s701, bool s1729=false )
: s272( s300, 0, s476, s701 ), s575( ct ), s576( s572 ),
s586( NULL ),	s588( s592 ), s587( s593 ), past( s701 ), s1656( s300 ),
intro(s1729){
TDException s970( s7::s1689, s934, s701, L"malformed lambda definition" );
size_t n = 0;
bool s1170;
for( ; n < l.size(); n += 2 ) {
s1170 = false;
if( ((s483*)l[n]) == s873 ) {
if( l.size() == n )
throw s970.s1002( L"the return type is missing" );
s493 = l[n + 1]->s352();
n += 2;
break;}
else if( ((s483*)l[n]) == s1688 ) {
if( l.size() == n )
throw s970.s1002( L"the 'const' keyword should precede the parameter name");
s1170 = true;
++n;}
if( l[n]->s494() != s475 ) {
if( s1170 )
throw s970.s1002( L"the 'const' keyword should precede the parameter name");
break;}
s371* s76 = (s371*) l[n];
if( l.size() == n + 1 ) {
break;}
s483* ex = (s483*) l[n + 1];
s472 s1901 = ex->s494();
if( s1901 != s474 && s1901 != s480 &&	s1901 != s479 && 
s1901 != s1248 && s1901 != s1247 )
throw new s16( L"incorrect syntax for lambda parameter " + s76->s617() +
L"; should be a type constructor.", (uint32_t)s16::s17::s20 );
if( s1170 )
s76->s1262();
s628.s541( s76->s617(), ex );
s582.push_back( (s483*)ex );
s630.push_back( (s483*)ex );
s631.push_back( *s76 );}
s584.insert( s584.end(), l.begin() + n, l.end() );}
s591::s591( const s591& right, s272* s592, s591* s593,
const std::vector<s271*>& s705, const s263* s701 )
: s272( right.s300, right.s493, right.s492, s701 ),  
s576( right.s576 ),	s586( NULL ), s588( s592 ), s587( s593 ), 
past( s701 ), s1656( s300 ), intro(right.intro){
s493 = right.s493;
s575 = right.s575;
s630 = right.s630;
s631 = right.s631;
s628 = right.s628;
s582 = right.s582;
s278 = right.s278;
if( s705.size() ) {
s274.assign( s705.begin(), s705.end() );
for( size_t n = 0; n < s274.size(); ++n ) {
s628.s541( s631[n].s617(), s274[n].s15<s483*>(), s482::s147 );
s630[n] = s274[n];}}
else {
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s335() );}}
for( size_t n = 0; n < right.s584.size(); ++n ) {
s584.push_back( right.s584[n]->s335() );}}
s841::s841( s262* s300, s591* s593, s563 ct, const vector<s271*>& l,
/*s616 s708,*/ s1063 s709, const wstring& s1555, const s263* s701 )
: s591( s300, s593, s593, ct, L"", s701 ), s1978( false )/*,
s562( s708 )*/
{
s278 = s1555;
s576 = s572;
s493 = s709;
s274.assign( l.begin(), l.end() );}
s841::~s841(){}
s842::s842( s262* s300, s272* s588, s591* s587, s563 ct,
const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s588, s587, ct, l, s701 ){
if( ct == s568 ) {
subject = s588;		}}
s842::s842( const s842& right, /*s483* s592,*/ s591* s593,
const std::vector<s271*>& s705, s563 ct,  const s263* s701, 
s272* s592 )
: s591( right.s300, s592 ? s592 : right.s588.s15<s272*>(), 
s593, ct, L"", s701 ){
TDException s970( s7::s1672, s934, s701 );
s575 = right.s575;
s493 = right.s493;
s630 = right.s630;
s631 = right.s631;
s628 = right.s628;
s582 = right.s582;
s576 = right.s576;
s278 = right.s278;
s586 = NULL;
int shift = 0;
if( ct == s568 ) {
if( s705.size() ) {
subject = s705[0];
shift = 1;}
else
subject = s588.s15<s484*>();}
for( size_t n = 0; n < s582.size(); ++n ) {
if( s705.size() > n + shift ) {
s274.push_back( s705[n + shift] );}
else
s274.push_back( s582[n]->s335() );}
if( s705.size() - shift > s274.size() ) 
throw s970.s1002( L"too many arguments: expected " + std::to_wstring( s274.size() ) + L", received " +
std::to_wstring( s705.size() ));
/*for( size_t n = 0; n < s274.size(); ++n ) {
s628.s541( s631[n], s274[n].s15<s483*>(), s482::s147 );
s630[n] = s274[n];
}*/
for( size_t n = 0; n < right.s584.size(); ++n ) {
s584.push_back( right.s584[n]->s335() );}}
s591::~s591(){
/*	for( size_t n = 0; n < s274.size(); ++n ) {
delete s274[n].s15<s484*>();
}*/
}
s842::~s842(){}
s561::s561( s262* pass_, const std::wstring& s189, const vector<s271*>& l, 
const s263* ast_ )
: s271( pass_, s477 ), s601( s189 ), past( (s263*)ast_ ){
s274.assign( l.begin(), l.end() );}
s561::s561( const s561& right )
: s271( right.s300, s477 ), s601( right.s601 ), past( right.past ){
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s335() );}}
wstring s591::s834() const{
if( s588.s14() )
return s588->s298();
else if( s575 == s566 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
void s591::s847( s271* par, size_t pos, s485& s153, const s272* s1674 ){
if( par->s494() == s477 ) {
s490 cs = new s561( *((s561*)par) );
s153 = s600( cs, s300, (s272*)s1674, this, s588->s298(), false );
s153.s15<Transd*>()->s500( s1674, false );}
else if( par->s494() == s474 ) {
par->s500( /*s588*/ this, false );
s153 = par;}
else if( par->s494() == s476 ) {
s153 = par; // par->s496();
}
else
s153 = par;}
void s591::s589(const wstring& s334){
for( size_t n = 0; n < s582.size(); ++n )
s582[n]->s500( s587/*s588*/ );
}
void s591::s500( const s272* s1674, bool proc/*=false*/ )
{
ns = s588;
s671 = proc ? s588->s298() : s1674->s298();
if( s588 && (s588->s494() == s479 || s588->s494() == s478 )) {
if( s588->s494() == s478 )
return;}
if( s575 == s566 && s618() == s7::s867 )
return;
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( s575 == s566 && n == 1 ) {
s591::s1244( s274, ((s336*)s274[0]->s496())->s1193( s278 ) );}
if( par->s494() == s475 ) {
if( par.s15<s371*>()->s381().s13() ) {
s487 s1677 = s588;
s588 = (s272*)s1674;
par.s15<s371*>()->s500( this, false );
s588 = s1677;}
s583.push_back( NULL );}
else if( par->s494() == s1065 || par->s494() == s481 )
s583.push_back( /*NULL*/ par.s15<s483*>() );
else {
try {
s847( par, n, s274[n], s1674 );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s278 + L"' function " );}
s583.push_back( s274[n]->s496() );}}
if( s575 == s565 ) {
if( s278 == s233 ) {
for( size_t n = 0; n < s274.size(); ++n ) {
s628.s541( s631[n].s617(), s274[n].s15<s483*>(), s482::s147 );
s274[n]->s1681( s7::s867 );
s630[n] = s274[n];}}
for( size_t n = 0; n < s584.size(); ++n ) {
if( s584[n]->s494() == s477 ) {
s490 cs = new s561( *s584[n].s15<s561*>() );
s584[n] = s600( cs, s300, s588, this, s588->s298(), true );}
else if( s584[n]->s494() == s475 )
s584[n].s15<s371*>()->s500( s587, true );
else if( s584[n]->s494() != s476 )
s584[n]->s500( s587 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s584 ) {
if( it->s494() == s476 )
it.s15<Transd*>()->s500( s588, true );}
if( !s493 && s584.size() ) {
s493 = s584.back()->s352();}}
if( s493 ) {
if( s588.s14() ) {
if( 0 && s492 == s1247 )
s586 = s300->TR().s518( ((s838*)this)->s1330(), 
s588, s588->s298() );
else
s586 = s300->TR().s518( s352(), s588, s588->s298() );}
else {
if( 0 && s492 == s1247 )
s586 = s300->TR().s518( ((s838*)this)->s1330(), 
(s272*)s1674, s1674->s298() );
else
s586 = s300->TR().s518( s352(), (s272*)s1674, s1674->s298() );}
s586->s500( s587 );
s586->s1681( s7::s867 );
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
s983.resize( s583.size() );}
void s841::s500( const s272* s1674, bool proc/*=false*/ )
{
s671 = proc ? s588->s298() : s1674->s298();
TDException s970( s7::s1128, s1134, past );
s591::s500( s1674, proc );
s271* par = s274[0]->s496();
s336* s703 = NULL;
s1144 s1239;
s472 s710 = par->s494();
s1124 ap;
if( s710 == s475 ) {
s371* ref = (s371*)par;
s486 pobj = ref->s377();
s710 = pobj->s494();
s703 = pobj.s15<s336*>();
ap = s1124( s274, s703 );
try {
s1239 = s703->s1194( s278, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s336::s337::s1135::s1182 ) {
s1239 = s703->s1189( s278, ap /*s1241, s274*/ );
}}}
else {
s703 = ( (s336*)par );
ap = s1124( s274, s703 );
try {
s1239 = ( (s336*)s703->s496() )->s1194( s278, ap/*s1241*/ );
}
catch( s16* e ) {
if( e->which() == (uint32_t)s336::s337::s1135::s1182 ) {
s1239 = ( (s336*)s703->s496() )->s1189( s278, ap/*s1241, s274*/ );
}}}
if( !s1239.s339 )
throw s970.s1002( L"method is not resolved: " + par->s353() + L"::" + s278 + 
ap.s1331( s300 ) );
try {
s300->s2015( s1239.s2037, s2047 );}
catch( s16* e ) {
throw s970.s1002( e->Msg() );}
s493 = s1239.s338;
s562 = s1239.s339;
s1978 = s1239.s1170;
bool s1764;
if( s274[0]->s494() != s476 /*==s475*/ )
s1764 = s274[0]->s1205();
else //if( s274[0]->s494() == s476 )
s1764 = s274[0]->s496()->s1205();
if( !s1978 && s1764 )
throw s970.s1002( L"non-constant function is applied to a constant variable" );
if( s278 == L"new" )
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
s983.resize( s583.size() );
s1264();
s586->s1264();
s586->s1262( s1764 );}
void s842::s500( const s272* s1674, bool proc/*=false*/ )
{
TDException s970( s7::s1524, s1558, s603() );
s671 = proc ? s588->s298() : s1674->s298();
if( s588->s494() == s479 || s588->s494() == s478 ) {
s589( s671 );
if( s588->s494() == s478 )
return;}
if( s274.size() > s630.size() )
throw s970.s1002( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( par->s494() == s475 ) {
s371* s1653 = par.s15<s371*>();
if( s1653->s381().s13() ) {
s1653->s500( /*this*/s587, true );
}}
else
s847( par, n, s274[n], s1674 );
if( s582[n]->s352() == Types.No ) {
if( !s582[n]->s501( s274[n].s15<s483*>() ) )
throw s970.s1002( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
else if( !s300->TR().s1536( s274[n]->s352(), s582[n]->s352() ) ) {
throw s970.s1002( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s618() < 0 )
throw s970.s1002( L"uninitialized function parameter: " + s631[n].s617() );
if( s274[n]->s496()->s1205() && !s631[n].s1205() )
throw s970.s1002( L"constant argument is passed to non-constant function: " + s631[n].s617() );
s630[n] = s274[n];}
s488 s1364 = s587;
s587 = 0;
for( size_t n = 0; n < s584.size(); ++n ) {
if( s584[n]->s494() == s477 ) {
s490 cs = new s561( *s584[n].s15<s561*>() );
s584[n] = s600( cs, s300, s588, this, s588->s298(), true );}
else if( s584[n]->s494() == s475 )
s584[n].s15<s371*>()->s500( /*s587*/ s588, true );
else if( s584[n]->s494() != s476 && 
s584[n]->s494() != s1247 )
s584[n]->s500( /*s587*/ s588 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s584 ) {
if( it->s494() == s476 )
it.s15<Transd*>()->s500( s588, true );}
s587 = s1364;
if( !s493 ) {
if( s584.size() ) {
s493 = s584.back()->s352();
s586 = s300->TR().s518( s352(), s588, s588->s298() );}
else {
s493 = s1154;
s586 = s365.s15<s483*>();}
s586->s1681( s7::s867 );
s583.insert( s583.begin(), s586 );}
if( s274.size() ) {
s581 = (s484**)&s274[0];
nlocs = s274.size();
s580 = NULL;// &s583[0];
s498 = s583.size();}
else {
s581 = NULL;
nlocs = s498 = 0;
s580 = NULL;}
s983.resize( s583.size() );
s1264();}
void s591::s1913( const s577& pl ) const{
TDException s970( s7::s1906, s1558, s603() );
size_t shift = 0;
if( s575 == s568 || s575 == s566 )
shift = 1;
if( pl.size() > s630.size() + shift )
throw s970.s1002( L"too many arguments" );
for( size_t n = shift; n < pl.size(); ++n ) {
s485 par = pl[n];
if( s582[n]->s352() == Types.No ) {
if( !s582[n]->s501( par.s15<s483*>() ) )
throw s970.s1002( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
else if( !s300->TR().s1536( par->s352(), s582[n]->s352() ) ) {
throw s970.s1002( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s582[n]->s353() + L"', received - '" + par->s353() + L"'" );}
if( par->s618() < 0 && par->s618() != s7::s1749 )
throw s970.s1002( L"uninitialized function parameter: " + s631[n].s617() );
if( par->s1205() && !s631[n].s1205() )
throw s970.s1002( L"constant argument is passed to non-constant function: " + s631[n].s617() );}}
void s591::s596( const vector<s485>& l ){
s1913( l );
s274.clear();
s274.assign( l.begin(), l.end() );}
void s591::s597( const s272* s1674 ){
TDException s970( s7::s1601, s1558, s603() );
if( s575 != s566 && s575 != s565 && s274.size() > s630.size() )
s970.s1002( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s271* par = s274[n];
if( par->s494() == s477 ) {
s490 cs = new s561( *(s561*)par );
par = s600( cs, s300, s588, /*this*/s587, s588->s298(), false );
((s591*)par)->s500( s1674, false );
s274[n] = par;}
if( s274[n]->s494() == s481 ) {
s583.push_back( s274[n]->s496() );}
else if( s274[n]->s494() != s475 ) {
if( ( s575 != s566 && s575 != s565 ) || s278 == s233 ) {
s630[n] = s274[n]->s496();
s630[n]->s1681( s7::s867 );
s628.s541( s631[n].s617(), s630[n].s15<s483*>(), s482::s147 );}
s583.push_back( s274[n]->s496() );}
else {
if( s575 != s566 && s575 != s565 ) {
s630[n] = s274[n].s15<s483*>();
s628.s541( s631[n].s617(), s274[n].s15<s371*>()->s377(), s482::s147 );}
if( s274[n].s15<s371*>()->s381().s13() ) {
s274[n].s15<s371*>()->s500( s587 /*this*/, true );
}
s583.push_back( NULL );}
if( s278 != s233 && n < s630.size() && n < s582.size() && !s630[n].s15<s483*>()->s501( (s483*)s582[n] ) )
s970.s1002( L"wrong argument's type" );}
for( size_t n = 0; n < s630.size(); ++n ) {
if( s630[n]->s618() == s7::s868 )
s970.s1002( L"parameter is not provided" );}}
void s591::s814( s835& s153 ) const{
for( size_t n = 0; n < s582.size(); ++n )
s153.push_back( make_pair( s631[n].s617(), s582[n] ) );}
s483* s591::s1613( s483** s691, size_t s697 ){
int shift = 0;
if( s575 == s565 || s575 == s566 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 || pc == s1339 )
*( s580 + n + shift ) =
(s483*)( ( s371* )*( s581 + n ) )->s377();
else if( pc == s476 ) {
s983[n + shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
if( s983[n + shift]->s618() < 0 ) {
if( s983[n + shift]->s618() == s7::s866 )
s983[n + shift]->s1681( 0 );
else if( s983[n + shift]->s618() != s7::s1749 )
return s983[n + shift];}
*( s580 + n + shift ) = s983[n + shift];}
else if( pc == s474 )
*( s580 + n + shift ) = ( s483* )*( s581 + n );
else if( pc == s1247 )
(void)0;}}
return NULL;}
s486 s591::s497( s483** s691, size_t s697 ){
s486 s685;
s685 = s1613( s691, s697 );
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
s685 = s1613( s691, s697 );
if( s685 )
return s685;
if( !s1978 && s583[1]->s1205() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s562( s580, s498 );
s685 = s583[0];}
catch( s16* e ) {
TDException s970( TDException::Stage::s1032, s7::s1129, 
s1133, past,	*e );
delete e;
s685 = new s361( s300, s970.Msg() );
s586 = s685;}
return s685;}
s486 s842::s497( s483** s691, size_t s697 ){
s483* s685 = s365;
if( subject.s14() )
s1656.s1663( subject->s497( 0, 0 ) );
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 ) ( void )0;
else if( pc == s476 )
s630[n] =
(s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );}}
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s580, s498 );
if( s685->s618() < 0 ) {
if( s685->s618() == s7::s866 )
s685->s1681( 0 );
break;}}
return s685;}
s1359::s1359( s262* s300, s272* s588, s591* s587, const s263* s701 )
: s842( s300, s588, s587, s568, vector<s271*>(), s701 ){
s1359* pin = (s1359*)s588->s344( s7::s428, s588->s298(), false );
if( pin ) {
pin->s628.copy( s628, (s272*)s588, s587 );
s631 = pin->s631;
s630 = pin->s630;
s582 = pin->s582;}}
s1359::s1359( const s1359& right, s272* s592, s591* s593,
const std::vector<s271*>& s705, const s263* s701 )
: s842( right, /*s592,*/ s593, s705, s568, s701 )
{
s588 = s592;
s274.assign( s705.begin() + 1, s705.end() );
s493 = right.s493;
s586 = (s483*)s705[0];}
s1359::~s1359(){}
void s1359::s500( const s272* s1674, bool proc/*=false*/ )
{
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s1681( s7::s867 );}
s586 = s588.s15<s272*>();
s493 = s586->s352();}
s486 s1359::s497( s483** s691, size_t s697 ){
s597( s588 );
s483* s685 = NULL;
if( s588->s352() == s1718 ) {
s685 = new s838( *s588.s15<s838*>(), s274, s603() );
s685->s500( s587 );}
else 
s685 = new s272( *s588, s274, s603() );
s685->s1264();
return s685;
wstring s189 = s603()->s291();
wstring s1360 = s603()->Src();
s1360.replace( s1360.find( s189 ), s189.size(), 1, L' ' );
s263* ast_ = new s263( s189, s1360 );
s685 = s586.s15<s272*>()->s635( *ast_, s587, s671 );
s685->s1264();
return s685;
vector<s271*> s1650( begin(s274), end(s274));
s685 = s586->s355( s587, s1650, s603() );
s685->s1264();
return s685;}
bool
s591::s556( const wstring& s676, s371* ref,	
const wstring& s334, bool fr ) const{
bool s685 = false;
wstring s278 = s676;
size_t pl = s278.find( L"." );
if( pl == string::npos ) { //a
if( !s628.s156( s278 ) || ( !fr && !intro ) 
|| ( s587.s14() && !intro ) ) {
if( s587.s14() && (s588.s13() || s587->s588 == s588 || 
s671 == s587->s671 || s671 != s587->s671) )
s685 = s587->s556( s278, ref, s334, true );
if( !s685 ) {
if( s588.s14() )
s685 = s588->s556( s278, ref, s334, true );
if( s685 ) {
if( s588->s494() != s479 && ref->s381() == s588.s15<s271*>() ) {
ref->s382( (s483*)&s1656 );
((s1602*)&s1656)->s1663( s588.s15<s483*>() );}}
else
s685 = s300->s556( s278, ref, s334, true );}}
else {
size_t off = s640( s278 );
ref->s379( off, ((s484*)&(*s630[off]))->s496()->s503() );
if( s631[off].s1205() )
ref->s1262();
ref->s382( (s483*)this /*(s484**)&s274[off]*/ );
s685 = true;}}
else {// a.y
s278 = s676.substr( pl + 1 );
wstring s686 = s676.substr( 0, pl );
s271* ob = s628.get( s686, false );
if( !ob ) {
s685 = s588->s556( s676, ref, s334, true );
if( !s685 && s587.s14() )
s685 = s587->s556( s676, ref, s334, true );}
else {
size_t off = s640( s686 );
ref->s379( off, NULL );
s685 = ob->s503()->s556( s278, ref, s334, true );
ref->s382( (s483*)this );}}
return s685;}
bool
s841::s556( const wstring& s676, s371* ref, const wstring& s334,
bool fr) const{
if( s278 == L"new" &&
s274[0].s15<s483*>()->s556( s676, ref, s334, true ) )
return true;
return s591::s556( s676, ref, s334, true );}
s271* s591::s598( size_t off ){
return s630[off];}
s271* s591::s335() const{
return new s591( *this );}
s271* s841::s335() const{
return new s841( *this );}
s271* s842::s335() const{
return new s842( *this );}
s271* s1359::s335() const{
return new s1359( *this );}
void s591::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Transductor : " <<  s278 << endl;
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"Call type : " << ct[s575] << endl;
if( !s628.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"members : " << endl;
s628.s304( pd, s197 + s419 );}
if( !s582.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"fpars : " << endl;
for( size_t n = 0; n < s582.size(); ++n )
s582[n]->s304( pd, s197 + s419 * 2 );}
if( !s631.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"namvec : " << endl;
for( size_t n = 0; n < s631.size(); ++n )
buf << s4::fill_n_ch( L' ', s197 + s419 * 2 ) << s631[n].s617() << endl;}
if( !s630.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"memvec : " << endl;
for( size_t n = 0; n < s630.size(); ++n )
s630[n]->s304( pd, s197 + s419 * 2 );}
if( !s584.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s419 ) << L"exprs : " << endl;
for( size_t n = 0; n < s584.size(); ++n )
s584[n]->s304( pd, s197 + s419 * 2 );}}
static s6::s1697 s1739;
s359::s359( s262* s300, const std::wstring& s, s272* s588, const s263* ast_ )
: s1403( s300, s588, ast_ ){
s493 = Types.String;
if( !s493 )
wh = s7::s868;
else {
wh = s7::s867;
s349 = s;}
s325 = s1581;}
s359::s359( s262* s300, s272* s592, const std::vector<s271*>& l, const s263* ast_ )
: s1403( s300, s592, ast_ ){
s274.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s868;
else
wh = s7::s867;
s493 = Types.String;
s325 = s1581;}
s359::s359( const s359& r, const s263* ast_ )
: s1403( r.s300, r.ns, ast_ ){
s349 = r.s349;
wh = r.wh;
s493 = r.s493;
s325 = s1581;}
s359::s359( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ )
: s1403( s300, NULL, ast_ ){
s349 = s;
pos = string::npos;
s493 = Types.String;
s325 = s1581;
wh = s7::s867;}
s359::~s359(){}
s483* s359::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s359( s300, s588, l );}
void s359::s350(){
s1403<s1579, wchar_t, s359, s1575>::s350();
s348 = s1403<s1579, wchar_t, s359, s1575>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s359::s1238, Types.String,
{ s1124(), s1124( { s7::s1395, s7::s1401 } ) }, 0, 100 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s359::s780, s1153,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"find-first-not-of", new s337( L"find-first-not-of", &s359::s1590, s1153,
{ s1124( { Types.String } ), s1124( { Types.String, s1153 } ), 
s1124( { Types.String, s1153, s1153 } )}, 1, 3 )));
s348.insert( make_pair( L"set", new s337( L"set", &s359::s387, s1154,
{ s1124( { Types.String } ), s1124( { s1154 } ) }, 1, 1, false )));
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s359::s1594, s1154,
{ s1124( { s1153, Types.String } ), s1124( { s1153, s1581 } ) }, 2, 2 )));
s348.insert( make_pair( L"size", new s337( L"size", &s359::s328, s1153,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"starts-with", new s337( L"starts-with", &s359::s1691, s1150,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"sub", new s337( L"sub", &s359::s794, Types.String,
{ s1124( { s1514::s1273 } ), s1124( { s1514::s1273, s1514::s1273 } ) }, 1, 2 )));
s348.insert( make_pair( L"subn", new s337( L"subn", &s359::s1597, Types.String,
{ s1124( { s1514::s1273 } ), s1124( { s1514::s1273, s1514::s1273 } ) }, 1, 2 )));
s348.insert( make_pair( L"sum", new s337( L"sum", &s359::s388, Types.String,
{ s1124( { Types.String, s7::s1401 } ) }, 1, 100 )));
s348.insert( make_pair( L"to-bytes", new s337( L"to-bytes", &s359::s1349, s1151,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"to-Int", new s337( L"to-Int", &s359::s412, s1153,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"tolower", new s337( L"tolower", &s359::s891, Types.String,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"toupper", new s337( L"toupper", &s359::s892, Types.String,
{ s1124() }, 0, 0 )));
s348.insert( make_pair( L"rfind", new s337( L"rfind", &s359::s799, s1153,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"eq", new s337( L"eq", &s359::s398, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"not", new s337( L"not", &s359::s413, s1150,
{ s1124( ) }, 0, 0 )));
s348.insert( make_pair( L"less", new s337( L"less", &s359::s399, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"greater", new s337( L"greater", &s359::s400, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"leq", new s337( L"leq", &s359::s401, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"geq", new s337( L"geq", &s359::s402, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"neq", new s337( L"neq", &s359::s403, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s348.insert( make_pair( L"textin", new s337( L"textin", &s359::s409, s1153,
{ s1124( ), s1124( { s1153 } ), s1124( { s1514::s1507 } ), 
s1124( { s1514::s1507, s1153 } ) }, 1, 2 )));
s348.insert( make_pair( L"getline", new s337( L"getline", &s359::s1485, s1153,
{ s1124(), s1124( { s1514::s1507 } ) }, 0, 1 )));
s348.insert( make_pair( L"match", new s337( L"match", &s359::s1036, s1150,
{ s1124( { Types.String } ) }, 1, 1 )));
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1063 s1519 = ( (s316*)Types( s300, Types.Vector ) )->s1197( ts, s1281 );
s348.insert( make_pair( L"split", new s337( L"split", &s359::s1492, s1519,
{ s1124(), s1124( { Types.String } ) }, 0, 0 )));
s1739 = s1738;
s1739.s1699 = L" \n";}
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
else if( par->s352() == s1417 ) {
auto pr = par.s15<s385*>();
auto rp = pr->s1196();
typename s1388::iterator s1521, s1522;
s1521 = rp.first.s15<s1141*>()->s1147();
s1522 = rp.second.s15<s1141*>()->s1147();
s1388 news( s1521, s1522 );
s349 += news;}
else if( par->s494() != s475 ) {
s349 += par->to_wstring();}
else {
if( s300->s1332() /*par.s15<s371*>()->s381().s14()*/ )
par.s15<s371*>()->s377()->to_wstring();}}
s1264();}
wstring s700( wchar_t c ){
wstring s685;
if( c == L'n' )
s685 = L"\n";
else if( c == L'r' )
s685 = L"\r";
else if( c == L't' )
s685 = L"    ";
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
return new s359( s300, s588, std::vector<s271*>() );}
else
s = s4::s52( s_, s48 );
if( s.size() ) {
size_t pos = 0;
const s947* s1053 = NULL;
if( s603() && s603()->Nqj() )
s1053 = s603()->Nqj()->s1008();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1053, s, pos, s94, s1739 );
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
s271* s359::s335() const{
return new s359( *this );}
s1063 s359::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get" )
s685 = s325;
else
s685 = s1403::s1190( s1555, l );
return s685;}
void s359::s356( s271* p ) const{
if( p->s352() == Types.String )
*( (s359*)p )->s357() = s349;
else if( p->s352() == s1153 )
*( (s346*)p )->s357() = std::stoi( s349 );
else if( p->s352() == s1152 )
*( (s358*)p )->s357() = std::stof( s349 );
else
throw new s16( L"No conversion to type " + s353() );}
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
wstring s359::to_wstring( uint32_t s1567 ) const{
if( 0 && s349.front() == '\"' && 
s349.back() == '\"' )
return s349.substr( 1, s349.size() - 2 );
return s349; }
inline void s359::s1492( s483** s274, size_t s498 ){
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
pv->s320().push_back( adds->s335() );}}
void s359::s1937( Stream* s1936 ) const{
s1936->s1482( s349 );
return;
s1502& ss = s1936->s1966();
ss << s349;}
void s359::s1962( s1907& s ){
s349 = s;}
void s359::s1961( Stream* s1936 ){
s1936->s1463( s349, string::npos );
return;
s1499& ss = s1936->s1965();
ss >> s349;}
s1324 s359::to_bytes() const{
s1324 s685;
string s = U8(s349);
s685.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s685[n] = s[n];
return s685;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s359*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
inline void s359::s1238( s483** s274, size_t s498 ){
s359* ps = (s359*)s274[1];
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
*s274 = ( s483* ) new s359( ps->s300, ps->s300, v );
s274[0]->s500( ps->ns );}
inline void s359::s387( s483** s274, size_t s498 ){
if( !PARN( 2 ) )
throw new s16( L"cannot assign Null object to String" );
( (s359*)DR )->s349 = ( (s359*)PARN( 2 ))->s349;}
inline void s359::s1594( s483** s274, size_t s498 ){
int pl = (int)*s274[2];
wchar_t c;
if( s274[3]->s352() == s1581 )
c = *( (s1575*)s274[3] )->s357();
else
c = ( (s359*)s274[3] )->s349[0];
( (s359*)DR )->s349[pl] = c;}
inline void s359::s328( s483** s274, size_t s498 ){
*( (s346*)s698 )->s357() = (int)( (s359*)DR )->s349.size();}
inline void s359::s1691( s483** s274, size_t s498 ){
wstring s696 = L"Invalid 'starts-with' syntax: ";
if( s498 < 3 )
throw new s16( s696 + L"too few parameters." );
const wstring& dr = ( (s359*)DR )->s349;
const wstring& str = ( (s359*)s274[2] )->s349;
if( dr.find( str ) == 0 )
*( (s360*)s274[0] )->s357() = true;
else
*( (s360*)s274[0] )->s357() = false;}
inline void s359::s388( s483** s274, size_t s498 ){
s698->s349 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s498; ++n )
s698->s349 += PARN( n )->to_wstring();}
inline void s359::s891( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349;
std::for_each( s698->s349.begin(), s698->s349.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s359::s892( s483** s274, size_t s498 ){
s698->s349 = ((s359*)DR)->s349;
std::for_each( s698->s349.begin(), s698->s349.end(), []( wchar_t & c ) {
c = std::towupper( c );
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
inline void s359::s1597( s483** s274, size_t s498 ){
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
inline void s359::s1590( s483** s274, size_t s498 ){
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
inline void s359::s409( s483** s274, size_t s498 ){
Stream* s1479 = NULL;
size_t s1454 = 0;
if( s498 >= 3 ) {
if( s274[2]->s352() == s1153 )
s1454 = (int)*s274[2];
else
s1479 = (Stream*)s274[2];
if( s498 == 4 )
s1454 = (int)*s274[3];}
else
s1479 = s1405;
wstring& s153 = *( (s359*)DR )->s357();
s1479->s1463( s153, s1454 );
int s685 = (int)s153.size();
s153.resize( s685 );
*((s346*)s698)->s357() = s685;}
inline void s359::s1485( s483** s274, size_t s498 ){
Stream* s1479 = NULL;
if( s498 >= 3 ) {
s1479 = (Stream*)s274[2];}
else
s1479 = s1405;
wstring& s153 = *( (s359*)DR )->s357();
s1479->s1464( s153 );
int s685 = (int)s153.size();
s153.resize( s685 );
*( (s346*)s698 )->s357() = s685;}
inline void s359::s1036( s483** s274, size_t s498 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1042;
wstring s = DR->to_wstring();
bool s153 = regex_match( s, s1042, rg );
*s699->s357() = s153;}
inline void s359::s1349( s483** s274, size_t s498 ){
( (s1294*)s698 )->s320() = DR->to_bytes();}
inline void s359::s412( s483** s274, size_t s498 ){
*( (s346*)s698 )->s357() = (int)*DR;}
void s359::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s349;}
size_t s359::s322() const{
return hash<wstring>{}(s349);}
bool s359::operator==( const s483* p ) const{
return ( (s359*)p )->s349 == s349;}
bool s359::operator<( const s483* p ) const{
return s349 < ( (s359*)p )->s349;}
Iterator* s359::s1166( const s483* idx ){
s1579::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s1580( s300, this, it, it == s349.end() ? it : it + 1 );}
Iterator* s359::s1185( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( *it == *( (s1297*)_val )->s357() )
return new s1580( s300, this, it, it + 1 );
return new s1580( s300, this, end( s349 ), end( s349 ) );}
s483* s359::s1192( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s1580*)it )->s1147() );
return new s346( s300, (int)n );}
Iterator* s359::s1187() {
if( s349.size() )
return new s1580( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s1580( s300, this, s349.end(), s349.end() );}
Iterator* s359::s1191() {
return new s1580( s300, this, s349.end(), s349.end() ); }
Iterator* s359::s314( s385* rv ){
s1146 pr = rv->s1196( this );
return new s1580( s300, this,
pr.first.s15<s1141*>()->s1147(), pr.second.s15<s1141*>()->s1147() );}
vector<wstring> s957( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s817::s817( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s759, s701 ){
TDException s970( s7::s1111, s933, s701 );
if( l.empty() )
throw s970.s1002( L"too few arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.String;
s591::s1244( ( vector<s271*>& )l, s957 );}
s817::s817( s262* s300 )
: s591( s300, NULL, NULL, s565, s759, NULL ){
s493 = Types.String;}
void s817::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
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
if(	pc == s475 || pc == s1065 || pc == s474 || pc == s476 ) {
s485 par;
s489 rf;
if( pc == s475 ) {
rf = par_.s15<s371*>();
par = (s271*)rf->s378();}
else if( pc == s1065 ) {
rf = par_.s15<s371*>();
par = par_;}
else
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1228 ) {
if( s777 != 0 )
throw new s16( s696 + L"'from' is misplaced." );
s777 = 1;
s766 = s764;}
else if( rf->Id() == s1235 ) {
if( s777 != 0 )
throw new s16( s696 + L"'to' is misplaced." );
s777 = 1;
s766 = s816;}
else if( rf->Id() == s1221 ) {
if( s766 != s719 && s777 >= 2 )
throw new s16( s696 + L"'before' is misplaced." );
if( s766 == s816 )
s740 = -1;
else
s793 = -1;
s777 = 2;}
else if( rf->Id() == s1217 ) {
if( s766 != s719 && s777 >= 2 )
throw new s16( s696 + L"'after' is misplaced." );
if( s766 == s816 )
s740 = 1;
else
s793 = 1;
s777 = 2;}
else if( rf->Id() == s1227 ) {
if( s766 != s719 && s777 >= 3 )
throw new s16( s696 + L"'first' is misplaced." );
s777 = 3;}
else if( rf->Id() == s1231 ) {
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
else if( par->s352() == s1153 ) {
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
if( s763->s494() == s476 )
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
if( s793 > 0 )
s192 += s761.size();
else
s192 += s793;}
if( s723.s14() ) {
if( s723->s494() == s476 )
s683 = (size_t)(int)*s723->s497( 0, 0 );
else
s683 = (size_t)(int)*s723.s15<s346*>();}
else if( s801.s14() ){
s725 = s801->to_wstring();
if( nTo == 1 )
s683 = dom.find( s725, s192 );
else if( nTo == string::npos )
s683 = dom.rfind( s725 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s720 ) );
s683 += s740;}
if( s192 < 0 || s192 >= s683 || s192 >= dom.size() )
return s486();
wstring s153 = dom.substr( s192, s683 - s192 );
s586 = new s359( s300, s153, this );
return s586;}
s271* s817::s335()const{
return new s817( *this );}
s385::s385( s262* s300 )
: s326( s300, NULL, NULL ), s980( false ), s981( false ), s990( 0 )//, s885( false )
{
s493 = Types.Range;
s1245 = new s1531( s300, 0 );
s1246 = new s1531( s300, U64_MAX );
s1177 = new s1531( s300, 0 );}
s385::s385( s262* s300, s326* s588, Iterator* it )
: s326( s300, NULL, NULL ), s987( s588 ), s1468( it ), s980( false ), s981( false ), 
s990( 0 ){
s493 = s1417;}
s385::s385( uint64_t _beg, uint64_t _end )
: s326( NULL, NULL, NULL ), s980( false ), s981( false ), s990( 0 )//, s885( false )
{
s1245 = new s1531( s300, _beg );
s1246 = new s1531( s300, _end );
s493 = s1417;
s1177 = new s1531( s300, 0 );}
s385::s385( s262* s300, const wstring& s77, const s263* ast_ )
: s326( s300, NULL, ast_ ), s980( false ), s981( false ), s990( 0 )//, s885( false )
{}
s385::s385( const s385& r, const s263* ast_ )
: s326( r.s300, r.ns, ast_ ), s980( false ), 
s981( false ), s990( r.s990 ), s1177( r.s1177 )//, s885( r.s885 )
{
s493 = r.s493;}
vector<wstring> s952( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s385::s385( s262* s300, s272* s592, const vector<s271*>& l_, const s263* ast_ )
: s326( s300, s592, ast_ ), s980( false ), s981( false ), s990( 0 ), 
s1177( new s1531( s300, 0 ) )//, s885( false )
{
s493 = s1417;
if( l_.empty() )
return;
TDException s970( s7::s1109, s934, ast_ );
if( l_.size() > 9 )
throw s970.s1002( L"too many arguments" );
s591::s1244( ( vector<s271*>& )l_, s952 );
const size_t s1057 = 3;
std::vector<s271*> l( s1057 );
if( l_[0]->s494() == s1065 ) {
s371* rf = (s371*)l_[0];
if( rf->Id() == s1230 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1531( s300, 0 );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1531( s300, 0 );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s588 = l[0];
s1245 = l[1];
s1246 = l[2];
if( s588.s13() ) {
s325 = Types.s1530;
s317 = Types.s1530;}
else {
s325 = 0;
s317 = 0;}
s493 = s1417;}
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
s271::s1335( s701, s300, s588, s334, s705 );
return new s385( s300, s588, s705, &s701 );}
else
return NULL;}
void s385::s500( const s272* s879, bool ){
TDException s970( s7::s921, s934, s603(), L"wrong Range definition" );
ns = (s272*)s879;
bool s1170 = false;
try {
if( s588.s14() ) {
if( s588->s494() == s475 ) {
s588.s15<s371*>()->s500( s879 );
s1170 = s588->s1205();
s987 = (s326*)s588.s15<s371*>()->s377();}
else if( s588->s494() == s477 ) {
s485 tmp = s271::s1020( s300, s588, (s272*)s879, (s591*)s879, s879->s298() );
s588 = tmp;
s987 = (s326*)s588->s496();}
else {
s987 = (s326*)s271::s1020( s300, s588, (s272*)s879, (s591*)s879, s879->s298() );}
s325 = s987->ValType();
s317 = s987->s319();}
if( s1245.s14() ) {
if( s1245->s494() == s475 )
s1245.s15<s371*>()->s500( s879 );
else {
s485 tmp = s271::s1020( s300, s1245, (s272*)s879, (s591*)s879, s879->s298() );
s1245 = tmp;}}
else
s1245 = s365.s15<s484*>();
if( s1246.s14() ) {
if( s1246->s494() == s475 )
s1246.s15<s371*>()->s500( s879 );
else {
s485 tmp = s271::s1020( s300, s1246, (s272*)s879, (s591*)s879, s879->s298() );
s1246 = tmp;}}
else
s1246 = s365.s15<s484*>();}
catch( s16* e ) {
throw e->s30( L"while compiling Range: '" + s603()->Src() + L"'" );}
s1264();
s1262( s1170 );}
void s385::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s385::s1238, s1417,
{ s1124( { s1514::s1551 } ), s1124( { s1153, s1153 } ),
s1124( { s1514::s1509, s1153 } ),
s1124( { s1514::s1509, s1153, s1153 } ) }, 1, 3, true ) ) );
s348.insert( make_pair( L"size", new s337( L"size", NULL, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"max-element", new s337( L"resize", NULL, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", NULL, s1154,
{ s1124() }, 0, 0, false ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", NULL, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"reverse", new s337( L"reverse", NULL, s1154,
{ s1124() }, 0, 0, false ) ) );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s1144 s385::s1199( const std::wstring& s343 ) const{
if( s987.s14() ) 
return s987->s1199( s343 );
return s336::s1199( s343 );}
s1144 s385::s1194( const std::wstring& s343, s1124& ap ) const{
if( s343 == L"new" )
return s336::s1194( s343, ap );
if( s987.s14() )
return s987->s1194( s343, ap );
assert( 0 );
throw;}
s1144 s385::s1189( const std::wstring& s343,
s1124& ap ) {
if( s343 == L"new" )
return s336::s1189( s343, ap );
if( s987.s14() )
return s987->s1189( s343, ap );
assert( 0 );
throw;}
s1063 s385::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"new" ) {
s685 = s1514::s1509;}
else if( s987.s14() )
return s987->s1190( s1555, l );
return s685;}
const vector<wstring>&
s385::s1193( const wstring& s343 ) const{
if( s343 == L"new" || s987.s13() )
return s336::s1193( s343 );
else
return s987->s1193( s343 );}
s483* s385::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s385( s300, s588, l, ast_ );}
inline bool
s385::s501( const s483* s502 ) const{
return ( ( (s385*)s502 )->s352() == s352() );}
size_t s385::s1140() const{
if( s987.s14() )
return s987->s1140();
else
return 0;}
s1146 s385::s1196(){
Iterator *fir = NULL, *sec = NULL;
if( s987.s14() ) {
if( s980 )
fir = s987->s1185( s1245.s15<s483*>() );
else if( s1245 == s1523 )
fir = s987->s1191();
else
fir = s987->s1166( s1245.s15<s483*>() );
if( s981 )
sec = s987->s1185( s1246.s15<s483*>() );
else if( s1246 == s1523 )
sec = s987->s1191();
else
sec = s987->s1166( s1246.s15<s483*>() );
if( s987->s1140() >= 1 && ( s1245 == s1523 || sec->operator<( fir ) ) ) {
( (s1127*)fir )->reverse();
( (s1127*)sec )->reverse();}}
return s1146( fir, sec );}
s1146 s385::s1196( s326* s592 ){
Iterator *fir, *sec;
if( s980 )
fir = s592->s1185( s1245.s15<s483*>() );
else if( s1245 == s1523 )
fir = s592->s1191();
else 
fir = s592->s1166( s1245.s15<s483*>() );
if( s981 )
sec = s592->s1185( s1246.s15<s483*>() );
else if( s1246 == s1523 )
sec = s592->s1191();
else
sec = s592->s1166( s1246.s15<s483*>() );
if( s592->s1140() >= 1 && ( s1245 == s1523 || sec->operator<( fir ) ) ){
( (s1127*)fir )->reverse();
( (s1127*)sec )->reverse();}
return s1146( fir, sec );}
inline void s385::s1238( s483** s274, size_t s498 ){
s385* r = ( (s385*)s274[1] );
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 ) 
{ return v.push_back( (s271*) s349 ); } );
s385* s1472 = new s385( r->s300, r->ns, v );
s1472->s500( r->ns );
*s274 = (s483*)s1472;}
s271* s385::s335() const{
return new s385( *this );}
void s385::s356( s271* p ) const{
p = new s385( *this );}
size_t s385::s322() const{
return (size_t)this;}
bool s385::operator==( const s483* p ) const{
return ( this == p );}
bool s385::operator<( const s483* p ) const{
return false;}
bool s385::s1981() const{
return s990 == s1548;}
Iterator* s385::s314( s385* r ){
if( s1245.s14() ) {
s472 pc = s1245->s494();
if( pc == s476 )
s1544 = s1245->s497( 0, 0 );
else if( pc == s475 )
s1544 = s1245.s15<s371*>()->s377();
else
s1544 = s1245.s15<s483*>();}
if( s1246.s14() ) {
s472 pc = s1246->s494();
if( pc == s476 )
s1545 = s1246->s497( 0, 0 );
else if( pc == s475 )
s1545 = s1246.s15<s371*>()->s377();
else
s1545 = s1246.s15<s483*>();}
if( s987.s14() )
return s987->s314( this );
s990 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1245.s15<s483*>();
return this;}
s271* s385::s315(){
if( s990 == U64_MAX ) {
if( s1544.s14() ) {
if( s1544->s352() == s1529 )
s990 = *s1544.s15<s1531*>()->s357();
else {
s1305 tmp;
s1544->s356( &tmp );
if( *tmp.s357() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s990 = *tmp.s357();}}
if( s1545.s14() ) {
if( s1545->s352() == s1529 )
s1548 = *s1544.s15<s1531*>()->s357();
else {
s1305 tmp;
s1545->s356( &tmp );
if( *tmp.s357() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1548 = *tmp.s357();}}
if( s990 > s1548 )
incr = -1;
else
incr = 1;}
else
s990 += incr;
if( s990 == s1548 )
return NULL;
*s1177->s357() = s990;
return s1177;}
s271* s385::s964(){
return s318->s964();}
const s271* s385::s964() const{
return NULL;}
s271* s385::Idx(){
return NULL;}
s271* s385::El(){
return NULL;}
void s385::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Range :: " << L" curit: " << s318 << endl;}
vector<wstring> s1137( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1136::s1136( s262* s300, const wstring& s77, const s263* ast_ )
: s326( s300, NULL, ast_ ), s989( s7::s1376, s300 ), s990(NULL), s349( new s346( s300, 0 )), 
s685( new s346( s300, 0 )),s1355(0){
s493 = Types.Filter;}
s1136::s1136( const s1136& r, const s263* ast_ )
: s326( r.s300, r.ns, ast_ ), s989( s7::s1376, s300 ), s990(NULL), s349( new s346( s300, 0 ) ),
s685( new s346( s300, 0 ) ), s1355(r.s1355){
*s349->s357() = (int)*r.s349;
*s685->s357() = (int)*r.s685;
ns = r.ns;
s493 = r.s493;}
s1063 s1455( size_t& idx, const vector<s271*>& l ){
if( l.size() > idx && l[idx]->s494() == s1065 )
idx++;
if( l.size() > idx )
return l[idx]->s352();
return 0;}
s1136::s1136( s262* s300, s272* s592, const vector<s271*>& l_, const s263* ast_ )
: s326( s300, s592, ast_ ), s989( s7::s1376, s300 ), s990(NULL),
s349( new s346( s300, 0 ) ),	s685( new s346( s300, 0 ) ),s1355(0){
s493 = s1911;
ns = s592;
if( l_.empty() )
return;
TDException s970( s7::s1369, s934, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s970.s1002( L"too many arguments" );
s591::s1244( ( vector<s271*>& )l_, s1137 );
const size_t s1057 = 3;
std::vector<s271*> l( s1057 );
if( !s300->TR().s1467( l_[0]->s352(), s1514::s1509 ) )
throw s970.s1002( L"the type is not rangeable: " + l_[0]->s353() );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s352() == s1417 ) {
range = (s385*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s494() != s1065 || ((s371*)l_[bas])->Id() != s1334 )
throw s970.s1002( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s494() != s1065 || ((s371*)l_[bas])->Id() != s1237 )
throw s970.s1002( L"expected the 'where:' clause" );
if( l_[bas+2]->s494() != s1065 || ((s371*)l_[bas+2])->Id() != s1334 )
throw s970.s1002( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s588 = l[0];
where = l[1];
s1072 = l[2];}
s483* 
s1136::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
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
if( s300->TR().s1467( s274[0]->s352(), s1514::s1509 ) )
return new s1136( s300, s588, s274 );
else
return new s953( s300, s588, s274 );}
else
return NULL;}
void s1136::s500( const s272* s879, bool ){
TDException s970( s7::s921, s934, s603(), L"wrong Filter definition");
ns = (s272*)s879;
if( s588.s13() )
return;
if( s588->s494() == s475 ) {
s489 rf = s588.s15<s371*>();
if( rf->s381().s13() )
rf->s500( s879 );
s987 = rf.s15<s371*>()->s377();}
else if( s588->s494() == s477 ) {
s485 tmp = s271::s1020( s300, s588,(s272*)s879, (s591*)s879, s879->s298() );
s588 = tmp;
s987 = s588->s496();}
else {
s987 = (s483*)s271::s1020( s300, s588, (s272*)s879, (s591*)s879, s879->s298() );}
if( s987->s494() == s474 ) {}
else if( s987->s494() == s480 ) {}
else
throw s970.s1002( L"unsupported container type" );
s989.s379( 0, s300->TR().s1009( s987.s15<s326*>()->ValType() ) );
s989.s382( (s483*)this );
if( where.s14() ) {
if( where->s494() == s475 )
where.s15<s371*>()->s500( s879 );
else
where = s271::s1020( s300, where, (s272*)this, (s591*)s879, s879->s298() );}
if( s1072.s14() ) {
if( s1072->s494() == s475 ) {
s1072.s15<s371*>()->s500( s879 );
s325 = s1072->s496()->s352();}
else {
if( s1072->s494() != s1247 )
s1072 = s271::s1020( s300, s1072, (s272*)s879, (s591*)s879, s879->s298() );
s325 = s1072.s15<s838*>()->s1330();}}
if( !s325 )
s325 = s987.s15<s326*>()->ValType();
s493 = s300->TR().s1048( s813::Cont( { s1911, 1, s325, 0 }) );
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" +
s300->TR().s1354( s300->TR().s804( s325 ) ) + L">";
s1355 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );
s1264();}
void s1136::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s1136::s1238, s1911,
{ s1124( { s1153, s1153 } ) }, 1, 2 ) ) );
s348.insert( make_pair( L"to-vector", new s337( L"to-vector", &s1136::s1350, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"max-element", new s337( L"resize", NULL, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", NULL, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", NULL, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"reverse", new s337( L"reverse", NULL, s1154,
{ s1124() }, 0, 0 ) ) );
s348.equal_range( L"new" ).first->second->s1263( true );
s348.equal_range( L"to-vector" ).first->second->s1263( true );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s1144 s1136::s1194( const std::wstring& s343, s1124& ap ) const{
return s336::s1194( s343, ap );
if( s343 == L"new" )
return s336::s1194( s343, ap );
assert( 0 );
throw;}
s1144 s1136::s1189( const std::wstring& s343, s1124& ap ){
if( s343 == L"new" ) {
auto ran = s342().equal_range( s343 );
s337* mi = ran.first->second;
s1144 s1239( s325, mi->s1138(), mi->s1205(), mi->s2019() );
return s1239;}
else if( s343 == L"to-vector" ) {
auto ran = s342().equal_range( s343 );
s337* mi = ran.first->second;
s1144 s1239( s1355, mi->s1138(), mi->s1205(), mi->s2019() );
return s1239;}
assert( 0 );
throw;}
s1063 s1136::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"new" ) {
s685 = s1514::s1509;}
else if( s1555 == L"to-vector" ) {
s685 = s1355;}
return s685;}
s483* s1136::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1136( s300, s588, l, ast_ );
s1063 pt = l[0]->s352();
if( s300->TR().s1467( pt, s1514::s1509 ) )
return new s1136( s300, s588, l );
s591::s1244( ( vector<s271*>& )l, s1137 );
s472 pc = l[0]->s494();
vector<s271*> s914;
size_t s375 = 0;
if( pc == s474 ) {
if( pt == s1153 ) {
if( l.size() > 1 && l[1]->s352() == s1153 ) {
s914 = { l[0], l[1] };
s375 = 1;}
else {
s914 = { l[0] };
s375 = 2;}}}
else if( pc == s1065 ) {
if( ( (s371*)l[0] )->s1306() == s1235 ) {
s914 = { l[1] };
s375 = 2;}
else if( ( (s371*)l[0] )->s1306() == s1228 ) {
s914 = { l[1], l[3] };
s375 = 4;}}
vector<s271*> l1 = { new s953( s300, s588, s914 ) };
l1.insert( l1.end(), l.begin() + s375, l.end() );
return new s1136( s300, s588, l1 );
if( l.size() ) {
if( l[0]->s494() == s475 ) {
l[0]->s500( s588 );
if( s300->TR().s1467( l[0]->s352(), s1514::s1509 )  )
return new s1136( s300, s588, l );}}
else {
return new s1136( s300, s588, l );}
return new s953( s300, s588, l );}
s483* s1136::s355( s272* s588, const std::vector<s1063>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1136* s685 = new s1136( s300, L"" );
s813::Cont s1075;
s491::s1010( vt, idx, s1075 );
s813 s1073( s1075[0] );
return s685;}
inline bool
s1136::s501( const s483* s502 ) const{
return ( ((s1136*)s502)->s352() == s352() );}
inline void s1136::s1238( s483** s274, size_t s498 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
s1136* pf = (s1136*)s274[1];
*s274 = ( s483* ) pf->s355( pf->ns, v, pf->s603() );
s274[0]->s500( pf->ns );
pf->s989.s382( s274[0] );
pf->s990 = ((s1136*)s274[0])->s990;}
inline void s1136::s1350( s483** s274, size_t s498 ){
s1136* pf = (s1136*)s274[1];
*s274 = ( s483* ) pf->s300->TR().
s1009( pf->s1355 )->s355( pf->ns );
Iterator* s1022 = pf->s314( NULL );
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() )
break;
( (s316*)s274[0] )->add( p->s335() );}
s274[0]->s1264();}
s271* s1136::s335() const{
return new s1136( *this );}
void s1136::s356( s271* p ) const{
p = new s1136( *this );}
size_t s1136::s322() const{
return (size_t)this;}
bool s1136::operator==( const s483* p ) const{
return ( this == p );}
bool s1136::operator<( const s483* p ) const{
return false;}
bool
s1136::s556( const wstring& s676, s371* ref, const wstring& s334, bool ) const{
if( s676 == s7::s1376 ) {
ref->s1345( (s371*)&s989 );
return true;}
return false; // ns->s556( s676, ref, s334 );
}
s271* s1136::s598( size_t off ){
assert( off == 0 );
if( s990 )
return s990;
return (s271*) s989.s503();}
s1146 s1136::s1196(){
if( range.s14() )
return range->s1196();
else
return s987.s15<s326*>()->s1196();}
Iterator* s1136::s314( s385* r ){
if( range.s14() ) {
s1146 pr = range->s1196( );
s318 = pr.first;
s1491 = pr.second;}
else {
s1146 pr = s987.s15<s326*>()->s1196();
s318 = pr.first;
s1491 = pr.second;}
return this;}
bool s1136::s1981() const{
if( !s990 || s318->operator==( s1491 ) )
return true;
return false;}
s271* s1136::s315(){
while( 1 ) {
s990 = s318->s315();
if( !s990 || s318->operator==( s1491 ) )
return NULL;
if( where.s14() && ( false == (bool)*where->s497(0,0) ) )
continue;
break;}
if( s1072.s14() )
return s1072->s497( 0, 0 ).s15<s484*>();
else
return s990;}
s271* s1136::s964(){
return s318->s964();}
const s271* s1136::s964() const{
return NULL;}
s271* s1136::Idx(){
return NULL;}
s271* s1136::El(){
return NULL;}
void s1136::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s197 ) << L"Input: ";
if( s588.s14() ) {
s987.s14() ? s987->s304( pd, s197 + s419 ) : s588->s304( pd, s197 + s419 );}
buf << s4::fill_n_ch( L' ', s197 ) << L"Do: ";
if( s1072.s14() ) s1072->s304( pd, s197 + s419 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s197 ) << L"curitref: ";
s989.s304( pd, 0 );
buf << endl;}
s953::s953( s262* s300 ) 
: s326( s300, NULL, NULL ) {
s493 = Types.Seq;}
s953::s953( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ )
: s326( s300, s588, ast_ ), s1049( true ){
if( l.empty() )
return;
wstring s1000 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s1000 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s493 = s1418;}
s953::~s953(){}
s483* 
s953::s354( const s263& s701, s272* s588, const wstring& s334 ) const{
wstring s = s701.s291();
wstring s347 = s353();
if( s.find( s347 ) == 0 && ( s.size() == s347.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s347.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s696 = L"Malformed Sequence definition: " + s;
vector<s271*> s705;
s271::s1335( s701, s300, s588, s334, s705 );
return new s953( s300, s588, s705 );}
else
return NULL;}
s483* s953::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s953( s300, s588, l, ast_ );}
void s953::s500( const s272* s879, bool ){
if( end.s13() )
return;
wstring s1000 = L"wrong sequence generator syntax";
s485 tmp = s271::s1020( s300, end, (s272*)s879, (s591*)s879, s879->s298() );
end = tmp;
if( start.s14() ) {
tmp = s271::s1020( s300, start, (s272*)s879, (s591*)s879, s879->s298() );
start = tmp;}
else {
if( end->s352() == s1153 )
start = new s346( s300, 0 );
else {
start = s300->TR().s518( end->s352(), (s272*)s879, s879->s298() );
start->s500( s879 );}}
if( incr.s14() ) {
tmp = s271::s1020( s300, incr, (s272*)s879, (s591*)s879, s879->s298() );
incr = tmp;}
else {
if( start->s352() == s1153 )
incr = new s346( s300, 1 );
else
throw new s16( s1000 + L": increment value is missing" );}
if( start->s494() == s475 ) {
s271* p = start.s15<s371*>()->s377();
s991 = p->s335();
s1661 = p->s335();}
else {
s991 = start->s335();
s1661 = start->s335();}
std::vector<s271*> pl = { s991, incr };
s561 cs( s300, L"sumeq", pl, NULL );
s1060 = s591::s600( &cs, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
s1060->s500( s879, false );
std::vector<s271*> pl1 = { s991, start };
s561 cs1( s300, L"set", pl1, NULL );
set = s591::s600( &cs1, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
set->s500( s879, false );
std::vector<s271*> pl2 = { s991, end };
s561 cs2( s300, L"less", pl2, NULL );
eq = s591::s600( &cs2, s300, (s272*)s879, (s591*)s879, s879->s298(), false );
eq->s500( s879, false );
s1202 = s1153;
s325 = start->s352();
s1264();}
s1146 s953::s1196(){
s1::s1291<Iterator> it = this;
s1::s1291<Iterator> it1 = it;
return make_pair( it, it1 );}
bool s953::s1981() const{
if( (bool)*eq.s15<s591*>()->s497( 0, 0 ) )
return true;
return false;}
Iterator* s953::s314( s385* r ){
set->s497( 0, 0 );
s1049 = true;
return this;}
s271* s953::s315(){
if( s1049 )
s1049 = false;
else
s1060->s497( 0, 0 );
if(! (bool)*eq->s497( 0, 0 ) )
return NULL;
s991.s15<s483*>()->s356( s1661 );
s1661->s1264();
return s1661;}
void s953::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s953::s1238, s1418,
{ s1124( { s1153 } ), s1124( { s1153, s1153 } ), s1124( { s1153, s1153, s1153 } ) }, 
1, 2 ) ) );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s271* s953::Idx(){
return s1661; }
bool s953::operator==( const Iterator* p ) const{
return false;}
bool s953::operator<( const Iterator* p ) const{
return this < p;}
inline void s953::s1238( s483** s274, size_t s498 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s498, [&v]( s483* s349 )
{ return v.push_back( (s271*)s349 ); } );
*s274 = ( s483* ) new s953( ( (s953*)s274[1] )->s300, NULL, v );
s274[0]->s500( ((s953*)s274[1])->ns );}
s271* s953::s335() const{
return new s953( *this );}
void s953::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"SequenceGenerator : " << endl;
start->s304( pd, s197 + s419); buf << L", "; end->s304( pd, 0); 
buf << L", "; incr->s304( pd, 0 );}
s1063 s1514::s1509 = 0;
s1063 s1514::s1508 = 0;
s1063 s1514::s1510 = 0;
bool _cmp( const s485& l_, const s485& r_ ){
s483* l = l_.s15<s483*>();
s483* r = r_.s15<s483*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s485 l, const s485 r ) const{
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
struct s1158{
std::vector<s485>s861;
s488 s859;
s1158( /*s488 s860*/ ) : s859( /*s860*/0 ) { s861.resize( 2 ); }
bool operator()( const s485& l, const s485& r ){
if( s859.s14() ) {
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
Iterator* s326::s1166( const s483* idx ){
throw new s16( L"this iterable type doesn't support access by index" );}
Iterator* s326::s1185( const s483* idx ){
throw new s16( L"this iterable type doesn't support search for value" );}
Iterator* s326::s1240( const s483* idx ){
throw new s16( L"this iterable type doesn't support distancing between elements" );}
s483* s326::s1192( Iterator* ){
throw new s16( L"this iterable type doesn't support indexing" );}
struct s840;
s483* s326::sort( bool, s840* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s875 );}
template <class _Cont, class s1313, class Der>
s313<_Cont, s1313, Der>::s313( const s1172& r )
: s326( r ){}
void s1163( s262* s300, const wstring& s77, wstring& s1275, wstring& s644 ){
assert( !s77.empty() );
wstring sv = s77;
wsmatch s1076, rgres1;
wregex s1257( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
wregex s1258( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(.*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1076, s1258 ) ) {
s813::Cont vt;
s1275 = s1076[1].str();
if( regex_match( sv, rgres1, s1257 ) ) {
s644 = L"] " + //s1275 + L" " +
( s1076[s1076.size()-1].str().empty() ? L"0" : s1076[s1076.size()-1].str() );}
else {
s644 = s1076[2];}}}
s1145::s1145( s262* s300, s1907& s77, const s263* ast_ )
: s336( s300, NULL, ast_ ), s325( 0 ){
s493 = Types.Position;
s1681( s7::s868 );}
s1145::s1145( const s1145& right, const s263* ast_ )
: s336( right.s300, right.ns, ast_ ), s588( right.s588 ), s349( right.s349 ),
s325( right.s325 ){
s493 = right.s493;
s1264();}
s1145::s1145( s262* s300, s272* s588, Iterator* it, const s263* ast_ )
: s336( s300, NULL, ast_ ), s349( it ), s325( 0 ){
s493 = Types.Position;
s1264();}
s483* s1145::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
void s1145::s500( const s272* s879, bool ){
if( s349.s14() && !s325 ) {
s325 = s349->ValType();
s813::Cont v = { s1582, 1, s325, 0 };
s493 = s300->TR().s1048( v );
if( s493 == s1582 ) {
s813::Cont v = { s1582, 1, s325, 0 };
s493 = s300->TR().s1048( v );}}}
s1063 s1145::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get-el" )
s685 = s325;
return s685;}
s483* s1145::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1145( s300, L"", ast_ );}
s483* s1145::s355( s272* s588, const std::vector<s1063>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s813::Cont s1105;
s491::s1010( vt, idx, s1105 );
s1145* s685 = new s1145( s300, 0, NULL );
s685->ns = s588;
s685->s325 = s1105[0];
s813 s619( vt );
s685->s493 = s300->TR().s1013( vt );
return s685;}
void s1145::s350(){
s348.insert( std::make_pair( L"is-end", new s337( L"is-end", &s1145::s1982, s1150,
{ s1124( {s7::s1396} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"eq", new s337( L"eq", &s1145::s398, s1150,
{ s1124( {s7::s1396} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"get-el", new s337( L"get-el", &s1145::s1591, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"get-idx", new s337( L"get-idx", &s1145::s1748, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"neq", new s337( L"neq", &s1145::s403, s1150,
{ s1124( {s7::s1396} ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"set", new s337( L"set", &s1145::s387, s1154,
{ s1124( {s7::s1396} ) }, 1, 1 ) ) );
s348.equal_range( L"get-el" ).first->second->s1263( true );}
s271* s1145::s335() const{
return new s1145( *this );}
void s1145::s356( s271* p ) const{
p = new s1145( *this );}
size_t s1145::s322() const{
return (size_t)this;}
void s1145::operator=( const s1145& p ){
s588 = p.s588;
s349 = p.s349;
s325 = p.s325;
s493 = p.s493;}
bool s1145::operator==( const s483* p ) const{
return s349->operator==( ((s1145*)p)->s349 );}
bool s1145::operator<( const s483* p ) const{
return s349->operator<( ((s1145*)p)->s349 );}
#undef s698
#define s698 ((s1145*)(s484*)*s274)
#define s699 ((s360*)(s484*)*s274)
inline void s1145::s1982( s483** s274, size_t s498 ){
*((s360*)*s274)->s357() = ((s1145*)DR )->s349->s1981();}
inline void s1145::s1591( s483** s274, size_t s498 ){
*s274 = (s483*)((s1145*)DR )->s349->s964();}
inline void s1145::s1748( s483** s274, size_t s498 ){
*s274 = (s483*)((s1145*)DR )->s349->Idx();}
inline void s1145::s398( s483** s274, size_t s498 ){
*s699->s357() = ( (s1145*)DR )->s349->operator==( ( (s1145*)s274[2] )->s349 );}
inline void s1145::s403( s483** s274, size_t s498 ){
*s699->s357() = !( (s1145*)DR )->s349->operator==( ( (s1145*)s274[2] )->s349 );}
inline void s1145::s387( s483** s274, size_t s498 ){
*(s1145*)DR = *(s1145*)s274[2];}
void s1145::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Position : " <<
this << endl;}
s966::s966( s262* s300, s316* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1215( (uint64_t)-1 ), s1175( new s1531(NULL, -1) ), 
s1174( new s961(NULL, vector<s271*>( { s1175, s365 } )) ){
if( v.s14() ) {
s1215 = std::distance( v->s320().begin(), it );
assert( s1215 >= 0 );}}
s966::s966( s262* s300, s316* v_, s1249 it, s1249 sent )
: v( v_ ), s1260( it ), s1490( sent ), s1215( (uint64_t)-1 ), s1175( new s1531(NULL, -1) ), 
s1174( new s961(NULL, vector<s271*>( { s1175, s365 } )) ){
if( v.s14() ) {
s1215 = v->size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1215 >= 0 );}
s885 = true;}
s966::s966( s966* it )
: v( it->v ), s1216( it->s1216 ), s1215( it->s1215 ), s1175( new s1531(NULL, 0) ), 
s1174( new s961( NULL, vector<s271*>( { s1175, *s1216 } )) ){
s885 = it->s885;}
void s966::reverse(){
s885 = true; 
s1260 = std::make_reverse_iterator( s1216 );}
s271* s966::s315(){
s271* s685 = NULL;
if( !s885 ) {
if( s1216 != s1088 ) {
s685 = *s1216;
s1216++;
s1215++;}}
else {
if( s1260 != s1490 ) {
s685 = *s1260;
s1260++;
s1215--;}}
return s685;}
s271* s966::s964(){
if( !s885 ) {
if( s1216 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1216;}
else {
if( s1260 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1260;}}
const s271* s966::s964() const{
if( !s885 ) {
if( s1216 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1216;}
else {
if( s1260 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1260;}}
bool s966::s1981() const{
if( !s885 )
return s1216 == v->s320().end();
return s1260 == v->s320().rend();}
s271* s966::Idx(){
*s1175->s357() = s1215 - 1;
return s1175;}
s271* s966::El(){
if( !s885 ) {
if( s1216 == v->s320().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1216;}
else {
if( s1260 == v->s320().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1260;}}
s1063 s966::ValType() const{
return v->ValType();}
bool s966::operator==( const Iterator* r ) const{
if( !s885 ) {
return s1216 == ( (s966*)r )->s1216;}
else {
return s1260 == ( (s966*)r )->s1260;}}
bool s966::operator<( const Iterator* r ) const{
if( !s885 ) {
if( s1216 == v->s320().end() )
return false;
return s1216 < ( (s966*)r )->s1216;}
else {
if( s1260 == v->s320().rend() )
return false;
return s1260 < ( (s966*)r )->s1260;}}
s963::s963( s262* s300, 
s750* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1215( (uint64_t)-1 ), s1175( new s1531( NULL, 0 ) ){
if( v.s14() ) {
s1215 = std::distance( v->s320().begin(), it );
assert( s1215 >= 0 );}}
s963::s963( s963* it )
: v( it->v ), s1216( it->s1216 ), s1215( it->s1215 ), s1175( new s1531( NULL, 0 ) ){}
bool s963::s1981() const{
return s1216 == v->s320().end();}
s271* s963::s315(){
s271* s685 = NULL;
if( s1216 != v->s320().end() ) {
s685 = *s1216;
++s1216;
++s1215;}
return s685;}
s271* s963::s964(){
return *s1216;}
const s271* s963::s964() const{
return *s1216;}
s271* s963::Idx(){
*s1175->s357() = s1215 - 1;
return s1175;}
s271* s963::El(){
*s1175->s357() = s1215 - 1;
return s1175;}
s1063 s963::ValType() const{
return v->ValType();}
s940::s940( s262* s300, s324* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1175( s365 ), s1174( new s961( NULL,
vector<s271*>(	{ s1175, s365 } ) ) ){}
s940::s940( s940* it )
: v( it->v ), s1216( it->s1216 ), s1175( s365 ), s1174( new s961( NULL, 
vector<s271*>(	{ s1175, s365 } ) ) ){}
bool s940::s1981() const{
if( !s885 )
return s1216 == v->s320().end();
return s1260 == v->s320().rend();}
s271* s940::s315(){
s271* s685 = NULL;
if( s1216 != v->s320().end() ) {
s685 = s1216->second;
++s1216;}
return s685;}
s271* s940::s964(){
return (*s1216).second.s15<s484*>();}
const s271* s940::s964() const{
return (*s1216).second.s15<s484*>();}
s271* s940::Idx(){
return (*s1216).first.s15<s484*>();}
s271* s940::El(){
s271* s685 = NULL;
if( s1216 != v->s320().end() ) {
s1174->assign( vector<s485>(
{ ( *s1216 ).first.s15<s484*>(),( *s1216 ).second.s15<s484*>() } ));
s685 = s1216->second;
++s1216;}
return s685;}
void s940::reverse(){
s885 = true;
s1260 = std::make_reverse_iterator( s1216 );}
s1063 s940::ValType() const{
return v->ValType();}
bool s940::operator==( const Iterator* r ) const{
if( !s885 )
return s1216 == ( (s940*)r )->s1216;
else
return s1260 == ( (s940*)r )->s1260;}
s1385::s1385( s262* s300, s1384* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1175( s365 ), s1174( new s961( NULL,
vector<s271*>( { s1175, s1216->second } ) ) ){}
s1385::s1385( s1385* it )
: v( it->v ), s1216( it->s1216 ), s1175( s365 ), s1174( new s961( NULL,
vector<s271*>( { s1175, s1216->second } ) ) ){}
bool s1385::s1981() const{
return s1216 == v->s320().end();}
s271* s1385::s315(){
s271* s685 = NULL;
if( s1216 != v->s320().end() ) {
s685 = s1216->second;
++s1216;}
return s685;}
s271* s1385::s964(){
return ( *s1216 ).second.s15<s484*>();}
const s271* s1385::s964() const{
return ( *s1216 ).second.s15<s484*>();}
s271* s1385::Idx(){
return ( *s1216 ).first.s15<s484*>();}
s271* s1385::El(){
s271* s685 = NULL;
if( s1216 != v->s320().end() ) {
s1174->assign( vector<s485>(
{ ( *s1216 ).first.s15<s484*>(),( *s1216 ).second.s15<s484*>() } ) );
s685 = s1216->second;
++s1216;}
return s685;}
s1063 s1385::ValType() const{
return v->ValType();}
bool s1385::operator==( const Iterator* r ) const{
return s1216 == ( (s1385*)r )->s1216;}
s1295::s1295( s262* s300, s1294* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1215( (uint64_t)-1 ), s1175( new s1531( NULL, -1 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1215 = std::distance( v->s320().begin(), it );
assert( s1215 >= 0 );}}
s1295::s1295( s262* s300, s1294* v_, s1249 it, s1249 sent )
: v( v_ ), s1260( it ), s1490( sent ), s1215( (uint64_t)-1 ), s1175( new s1531( NULL, -1 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1215 = v->size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1215 >= 0 );}
s885 = true;}
s1295::s1295( s1295* it )
: v( it->v ), s1216( it->s1216 ), s1215( it->s1215 ), s1175( new s1531( NULL, 0 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, new s1297( NULL, *s1216)  } ) ) ){
s885 = it->s885;}
void s1295::reverse(){
s885 = true;
s1260 = std::make_reverse_iterator( s1216 );}
bool s1295::s1981() const{
if( !s885 )
return s1216 == v->s320().end();
return s1260 == v->s320().rend();}
s271* s1295::s315(){
s271* s685 = NULL;
if( !s885 ) {
if( s1215 < v->s320().size() )
s685 = new s1297( NULL, v->s320()[s1215++] );}
else {
if( s1215 != U64_MAX )
s685 = new s1297( NULL, v->s320()[s1215--] );}
return s685;}
s271* s1295::s964(){
return new s1297( NULL, *s1216 );}
const s271* s1295::s964() const{
return new s1297( NULL, *s1216 );}
s271* s1295::Idx(){
*s1175->s357() = s1215 - 1;
return s1175;}
s271* s1295::El(){
*s1175->s357() = s1215 - 1;
return s1175;}
s1063 s1295::ValType() const{
return v->ValType();}
bool s1295::operator==( const Iterator* r ) const{
if( !s885 )
return s1216 == ( (s1295*)r )->s1216;
else
return s1260 == ( (s1295*)r )->s1260;}
bool s1295::operator<( const Iterator* r ) const{
if( !s885 )
return s1216 < ( (s1295*)r )->s1216;
else
return s1260 < ( (s1295*)r )->s1260;}
s1580::s1580( s262* s300, s359* v_, s941 it, s941 sent )
: v( v_ ), s1216( it ), s1088( sent ), s1215( (uint64_t)-1 ), s1175( new s1531( NULL, -1 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1215 = std::distance( v->s320().begin(), it );
assert( s1215 >= 0 );}}
s1580::s1580( s262* s300, s359* v_, s1249 it, s1249 sent )
: v( v_ ), s1260( it ), s1490( sent ), s1215( (uint64_t)-1 ), s1175( new s1531( NULL, -1 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1215 = v->s320().size() - std::distance( v->s320().rbegin(), it ) - 1;
assert( s1215 >= 0 );}
s885 = true;}
s1580::s1580( s1580* it )
: v( it->v ), s1216( it->s1216 ), s1215( it->s1215 ), s1175( new s1531( NULL, 0 ) ),
s1174( new s961( NULL, vector<s271*>( { s1175, new s1575( NULL, *s1216)  } ) ) ){
s885 = it->s885;}
void s1580::reverse(){
s885 = true;
s1260 = std::make_reverse_iterator( s1216 );}
bool s1580::s1981() const{
if( !s885 )
return s1216 == v->s320().end();
return s1260 == v->s320().rend();}
s271* s1580::s315(){
s271* s685 = NULL;
if( !s885 ) {
if( s1215 < v->s320().size() )
s685 = new s1575( NULL, v->s320()[s1215++] );}
else {
if( s1215 != U64_MAX )
s685 = new s1575( NULL, v->s320()[s1215--] );}
return s685;}
s271* s1580::s964(){
return new s1575( NULL, *s1216 );}
const s271* s1580::s964() const{
return new s1575( NULL, *s1216 );}
s271* s1580::Idx(){
*s1175->s357() = s1215 - 1;
return s1175;}
s271* s1580::El(){
*s1175->s357() = s1215 - 1;
return s1175;}
s1063 s1580::ValType() const{
return v->ValType();}
bool s1580::operator==( const Iterator* r ) const{
if( !s885 )
return s1216 == ( (s1580*)r )->s1216;
else
return s1260 == ( (s1580*)r )->s1260;}
bool s1580::operator<( const Iterator* r ) const{
if( !s885 )
return s1216 < ( (s1580*)r )->s1216;
else
return s1260 < ( (s1580*)r )->s1260;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
vector<wstring> s1312( { L":typedTable", L":untypedTable" } );
s316::s316( s262* s300, s272* s588, const wstring& s77, const s263* ast_,
const s1697& s1761 )
: s1578( s300, s588, ast_ ){
TDException s970( s7::s1367, s934, ast_ );
s1202 = s1153;
if( s77.size() ) {
load( s77, s588, s1761 );}
if( !s493 )
s493 = Types.Vector;}
s316::s316( const s316& right, const s263* ast_ )
: s1578( right.s300, right.ns, ast_ ){
s349 = right.s349;
s1202 = right.s1202;
s325 = right.s325;
s317 = right.s317;
s493 = right.s493;
s1681( right.s618() );}
s316::s316( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1063 s709,	s1063 s1278 )
: s1578( s300, s588, ast_ ){
s1202 = s1153;
s325 = s1278;
s317 = s1278;
if( s709 )
s493 = s709;
else
s493 = Types.Vector;
if( l.size() )
s591::s1244( ( vector<s271*>& )l, s1312 );
if( l.size() ) {
if( l[0]->s352() == s352() ||	l[0]->s352() == s1721 ) {
s349.assign( ( (s316*)l[0] )->s349.begin(),
( (s316*)l[0] )->s349.end() );}
else if( l[0]->s352() == s1153 ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, L"] " + l[0]->to_wstring() ) );}}}
s316::s316( s262* s300, s1063 s1279, s272* s588, const s263* ast_ )
: s1578( s300, s588, ast_ ){
s1202 = s1153;
s325 = s1279;
s317 = s1279;
if( s1279 ) {
s813::Cont v = { s1721, 1, s325, 0 };
s493 = s300->TR().s1048( v );}}
s316::~s316(){
s349.clear();}
void s316::s1315( const vector<s271*>& s705, s272* s588 ){
assert(0);
TDException s970( s7::s1301, s934, s603() );
if( s705.empty() )
return;
s472 pc = s705[0]->s494();
if( pc == s475 && s588->s494() != s476 ) {
throw s970.s1002( L"references are not allowed in constructors of data members" );}
if( s705[0]->s352() == s352() ||
s705[0]->s352() == s1721 ) {
s349.assign( ( (s316*)s705[0] )->s349.begin(),
( (s316*)s705[0] )->s349.end() );}}
void s316::s1162( s1907& s77, s272* s588, const s1697& s1761 ){
assert( !s77.empty() );
wstring s1275, s644, s1268;
if( s77[0] == L'[' ) {
s1268 = s77;}
else {
s1163( s300, s77, s1275, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1268 = s644;
if( !s1275.empty() )
s1160( s1275, s493, s325 );}
if( !s1268.empty() ) {
load( s1268, s588, s1761 );}
else if( !s644.empty() ) {
if( s644[0] == L']' && s644.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, s644, ns ) );}}}
s1063 s316::s1197( s1907& s1275, s813::Cont& s588 ) const{
s1063 s685;
s813::Cont vt;
size_t pos = 0;
s1063 s1279 = 0;
s300->TR().s1058( s1275, pos, vt );
s685 = s300->TR().s1013( s813( vt ), false );
if( s685 ) {
s588 = { s1721, 1, vt[2], 0 };
return s685;}
s813::Cont s1284( begin( vt ) + 2, end( vt ) );
if( s1284.size() > 2 )
s1279 = s300->TR().s1048( s1284 );
else
s1279 = s1284[0];
s588 = { s1721, 1, s1279, 0 };
s685 = s300->TR().s1048( s588 );
return s685;}
void s316::s1160( s1907& s1275, s1063& pt, s1063& vt ) const{
s813::Cont s588;
pt = s1197( s1275, s588 );
vt = s588[2];}
void s316::load( const wstring& s77, s272* s588, const s1697& s1761 ){
TDException s970( s7::s1131, s934, s603() );
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( s325, s588, s588->s298() ) );
return;}
size_t pos = 0;
const s947* s1053 = NULL;
if( s603() && s603()->Nqj() )
s1053 = s603()->Nqj()->s1008();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1053, s77, pos, s94, s1761 );
wstring ownerName = s603()->s268( L"ownerName" );
bool s1328 = false;
if( ( s603()->s268( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1328 = true;
if( s94.size() ) {
s1063 pt = 0;
for( size_t n = 0; n < s94.size(); ++n ) {
s949 s225 = new s263( L"", *s94[n] );
s225->s1346( s325 );
s349.push_back( s271::s504( *s225, s300, s588, s588->s298() ) );
if( s349.back()->s494() != s475 ) {
if( n == 0 )
pt = s349.back()->s352();
else if( pt && s349.back()->s352() != pt )
throw s970.s1002( L"different elements types in vector" );}}
if( !s1328 ) {
if( !s325 && s349[0]->s352() ) {
s325 = s349[0]->s352();
s813::Cont v1 = { s1721, 1, s325, 0 };
s493 = s300->TR().s1048( v1 );}
else if( s325 != s349[0]->s352() )
throw s970.s1002( L"vector's element type doesn't match the vector type" );}}}
s483* s316::s354( const s263& s701, s272* s588, s1907& s334 ) const{
TDException s970( s7::s1302, s934, &s701,
L"wrong Vector constructor syntax" );
wstring s = s300->TR().s1277( s701.s291() );
wstring sv;
wstring s347 = s353();
wstring s1275, s644;
s1063 pt = 0, vt = 0;
if( s701.s268( L"ownerType" ) == L"CallSite" ) {
wstring s1325 = s701.s268( L"ownerName" );
if( s1325.find( L"new<Vector<" ) == 0 ) {
wstring stype = s1325.substr( 4, s1325.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s970.s1002( L"missing element type" );
s1163( s300, s, s1275, s644 );
if( !s644.empty() && ( s644[0] == L'[' || s644[0] == L']' ) )
sv = s644;
if( !s1275.empty() )
s1160( s1275, pt, vt );}
else
return 0;
s316* s685 = new s316( s300, vector<s271*>({ }), s588, &s701,
pt, vt );
s685->load( sv, s588, s1738 );
return s685;}
void s316::s500( const s272* s879, bool ){
wstring s77 = L"";
TDException s970( s7::s925, s934, s603() );
if( s349.size() == 2 && s349[0].s13() )
s77 = s349[1]->to_wstring();
if( s879->s494() != s476 ||
( (s272*)s879 )->s299() != L"new" || s300->s1332() ) {
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( s325, (s272*)s879, s879->s834() ) );}
else {
for( size_t n = 0; n < s349.size(); ++n ) {
if( s349[n]->s494() == s475 ) {
s349[n]->s500( s879 );
s349[n] = s349[n].s15<s371*>()->s377();}
s485 s1090 = s271::s1020( s300, s349[n], (s272*)s879, (s591*)s879, s879->s298() );
s349[n] = s1090->s497( 0, 0 ).s15<s484*>();
if( !s325 )
s325 = s349[0]->s352();
else if( s325 != s349[n]->s352() )
throw s970.s1002( L"elements have different types" );}}
if( s493 || s493 == s1721 ) {
if( !s325 )
throw s970.s1002( L"vector's element type is not specified" );
s813::Cont s588 = { s1721, 1, s325, 0 };
s493 = s300->TR().s1048( s588 );}
s1264();}}
void s316::s971( const wstring& s824, const s1722& tbfr, s272* s588,
const s263* ast_ ){
TDException s970( s7::s926, s934, ast_ );
vector<wstring> s805;
s4::s57( s4::s52( s824, s48 ), tbfr.rowSep, s805 );
s1697 s1750 = s1738;
s1750.s1699 = tbfr.s1699;
for( wstring row : s805 ) {
if( !tbfr.mixedTypes ) {
s349.push_back( new s316( s300, s300, row, NULL, tbfr.s1699 ) );}
else {
s961* pd = (s961*)s300->TR().s1009( s325 )->s335();
pd->load( row, s588, s1750 );
s349.push_back( pd );}}}
void s316::s350(){
s1578<s1420, s485, s316>::s350();
s348 = s1578<s1420, s485, s316>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s316::s1238, s1154,
{ s1124(), s1124( { s7::s1395, s7::s1401 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s348.emplace( make_pair( L"set", new s337( L"set", &s316::s387, s1154,
{ s1124( { s1514::s1509 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"set-el", new s337( L"set-el", &s316::s1266, s1154,
{ s1124( { s1514::s1551, s7::s1399 } ) }, 2, 2, false ) ) );
s348.emplace( make_pair( L"get", new s337( L"get", &s316::s327, 0,
{ s1124( { s1514::s1551 } ) }, 1, 1, true ) ) );
s348.emplace( make_pair( L"append", new s337( L"append", &s316::s1316, s1154,
{ s1124( { s7::s1399 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"resize", new s337( L"resize", &s316::s329, s1154,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"reserve", new s337( L"reserve", &s316::s1891, s1154,
{ s1124( { s1514::s1551 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"eq", new s337( L"eq", &s316::s398, s1153,
{ s1124( { s7::s1396 } ) }, 1, 1, true ) ) );
s348.emplace( make_pair( L"for-each", new s337( L"for-each", &s316::s1747, s1154,
{ s1124( { s7::s1400 } ) }, 1, 1, false ) ) );
s348.emplace( make_pair( L"load-table", new s337( L"load-table", &s316::s802,
s1153, { s1124( { s7::s1395, s7::s1401 } ) }, 0, 0, false, { L":mixedTypes", 
L":stringsQuoted", L":promInts", L"colNames", L"fieldSep:", L"rowSep:", L":emptyElements" } ) ) );
s348.equal_range( L"get" ).first->second->s1263( true );
s348.equal_range( L"new" ).first->second->s1263( true );
s300->TR().s1164( s493, s7::s1414, s1514::s1510 );
s300->TR().s1164( s493, s7::s1412, s1514::s1508 );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s483* s316::s355( s272* s588, const vector<s271*>& l, const s263* ast_ ) const{
if( !s325 )
throw new s16( L"vector's element type is not specified" );
return new s316( s300, l, s588, ast_, s493, s325 );}
s483* s316::s355( s272* s588, const std::vector<s1063>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s316* s685 = new s316( s300, 0, NULL );
s685->ns = s588;
s685->s325 = vt[2];
s813 s619( vt );
s685->s493 = s300->TR().s1013( s619 );
return s685;}
s1063 s316::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get" )
s685 = s325;
else if( s1555 == L"new" )
s685 = s493;
else
s685 = s1578::s1190( s1555, l );
return s685;}
inline bool
s316::s501( const s483* s502 ) const{
return ( ( (s316*)s502 )->s317 == s317 );}
s271* s316::s335() const{
return new s316( *this );}
void s316::s356( s271* p ) const{
s316* pv = (s316*)p;
pv->s349.assign( s349.begin(), s349.end() );
pv->s1681( wh );}
Iterator* s316::s1166( const s483* idx ){
s1420::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s966( s300, this, it, it == s349.end() ? it : it+1 );}
Iterator* s316::s1185( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( it->s15<s483*>()->operator==( _val ) )
return new s966( s300, this, it, it+1 );
return new s966( s300, this, end( s349 ), end( s349 ));}
s483* s316::s1192( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s966*)it )->s1147() );
return new s346( s300, (int)n );}
Iterator* s316::s1187() {
if( s349.size() )
return new s966( s300, this, s349.begin(), s349.begin()+1 ); 
return new s966( s300, this, s349.end(), s349.end() ); }
Iterator* s316::s1191() {
return new s966( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s316*)(s484*)*s274)
inline void s316::s1238( s483** s274, size_t s498 ){
s316* ps = (s316*)DR;
s316* s685;
if( s498 == 2 ) {
s685 = (s316*)( (s316*)s274[1] )->s335();}
else if( s274[2]->s1198().s352() == s1721 ) {
s685 = (s316*)( (s316*)s274[2] )->s335();}
else if( s274[2]->s1198().s352() == s1417 ) {
auto pr = (s385*)s274[2];
auto rp = pr->s1196();
typename s1388::iterator s1521, s1522;
s1521 = rp.first.s15<s1141*>()->s1147();
s1522 = rp.second.s15<s1141*>()->s1147();
s685 = new s316( ps->s300, vector<s271*>(), ps->ns, ps->s603() );
s685->s349.assign( s1521, s1522 );}
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
Iterator* s1022 = seq->s314( NULL );
v->s349.clear();
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() )
break;
v->s349.push_back( p );}}
inline void s316::s1266( s483** s274, size_t s498 ){
s316* v = ( (s316*)DR );
size_t idx = (size_t)(int)*s274[2];
if( idx >= v->size() )
throw new s16( L"vector index is out of range",
(uint32_t)s16::s17::s24 );
s271* el = v->s349[idx];
s274[3]->s356( el );
el->s1264();}
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
inline void s316::s1316( s483** s274, size_t s498 ){
s316* pv = (s316*)DR;
const s483* s1554 = pv->s300->TR().s1009( pv->s325 );
( (s316*)DR )->s349.push_back( (s271*)s1554->s1538( s274[2] ) );}
inline void s316::s1747( s483** s274, size_t s498 ){
using s1132 = s316;
using s941 = s966;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
s838* s1765 = (s838*)s274[2];
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename s1388::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
while( s1521 != s1522 ) {
s1765->s596( vector<s485>( { *s1521 } ) );
s1765->s497( 0, 0 );
++s1521;}}
inline void s316::s1891( s483** s274, size_t s498 ){
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
inline void s316::s398( s483** s274, size_t s498 ){
size_t size = ( (s316*)DR )->s349.size();
s316* right = (s316*)s274[2];
if( right->s349.size() != size ) {
*( (s346*)*s274 )->s357() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s316*)DR )->s349[n] ) {
*( (s346*)*s274 )->s357() = 0;
return;}}
*( (s346*)*s274 )->s357() = 1;}
inline void s316::s802( s483** s274, size_t s498 ){
s316* pv = ( (s316*)DR );
const wstring& s824 = PARN( 2 )->to_wstring();
s1722 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par_ = s274[n];
s472 pc = par_->s494();
if( pc == s1065 ) {
s485 par;
s489 rf;
rf = par_.s15<s371*>();
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1757 ) {
tbfr.mixedTypes = true;}
else if( rf->Id() == s1755 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1753 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1752 ) {
tbfr.s1699 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1754 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1844 ) {
tbfr.s1828 = true;}
else if( rf->Id() == s1751 ) {
if( s498 < n + 2 )
throw new s16( L"Vector::(load-table): the 'colNames:' value is missing" );
tbfr.s1736 = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Vector::(load-table): unknown parameters" );
++n;}
pv->s971( s824, tbfr, pv->ns, pv->s603() );}
struct s850{
vector<s485>& s349;
s850( vector<s485>& s695 ) : s349( s695 ) {}
bool operator()( const s485 l, const s485 r ) const{
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
s483* s316::sort( bool s885, s840* cmp ){
s850 s849( s349 );
if( s885 ) {
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
wstring s316::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s316::s1937( Stream* s1936 ) const{
s1502& ss = s1936->s1966();
ss << L"[";
if( s618() == s7::s868 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n ) {
s349[n].s15<s483*>()->s1937( s1936 );
if( n < s349.size() - 1 )
ss << L", ";}}
ss << L"]";}
void s316::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Vector : " << this << endl;
for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );}
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
return new s966( s300, this, begin( s349 ), end( s349 ) );
s1146 pr = rv->s1196( this );
return new s966( s300, this,
pr.first.s15<s1141*>()->s1147(), pr.second.s15<s1141*>()->s1147() );}
s750::s750( s262* s300, s272* s588, const wstring& s77,
const s263* ast_, const s1722& tbfr )
: s326( s300, s588, ast_ ){
if( s77.size() ) {
s1697 s1761;
s1761.s151 = true;
s1761.s1734 = tbfr.stringsQuoted;
s1761.s1746 = tbfr.s1828;
vector<s1::s9<s6::s141>> s153;
const s947* s1053 = NULL;
if( ast_ )
s1053 = ast_->Nqj()->s1008();
if( s77[0] == L'[' ) {
size_t pos = 0;
s6::s178( s1053, s77, pos, s153, s1761 );}
else
s6::s178( s1053, s77, s153, s1761 );
s949 s225;
for( size_t n = 0; n < s153.size(); ++n ) {
s225 = new s263( L"", *s153[n] );
if( ( !tbfr.stringsQuoted && s153[n]->s164() == s134 ) ||
s153[n]->s164() == s139 || s225->s297() == s228 ) {
s225->s1346( Types.String );
s225->s1874( s224::s225 );
s225->s1770( L"\"" + 
s225->s291() + 
L"\"" );}
else if( tbfr.promInts && s153[n]->s164() == s140 )
s225->s1346( s1152 );
if( s225->s291().empty() ) {
if( s1761.s1746 )
s225->s1770( Types( s300, Types.String )->s353() + L"()" );
else
throw new s16( L"empty element in an UntypedVector. To allow"
L" empty elements, use the ':emptyEls' marker." );}
s349.push_back( s271::s504( *s225, s300, s588, s588->s298() ) );}}
s493 = s1720;}
s750::s750( s262* s300, const vector<s271*>& l,
const s263* ast_ )
: s326( s300, NULL, ast_ ){
for( auto s1062 : l )
s349.push_back( s1062 );
s493 = s1720;}
s750::s750( const s750& right )
: s326( right ){
s349 = right.s349;
s493 = right.s493;}
s750::~s750(){
s349.clear();
s499.clear();}
void s750::s1162( s1907& s77, wstring& s1275, wstring& s644,
vector<s1::s9<s6::s141>>& s94, const s263* ast_, const s1697& s1761 ){
assert( !s77.empty() );
if( s77[0] == L'[' ) {
size_t pos = 0;
const s947* s1053 = NULL;
if( ast_ && ast_->Nqj() )
s1053 = ast_->Nqj()->s1008();
s6::s178( s1053, s77, pos, s94, s1761 );}
else
s1163( s300, s77, s1275, s644 );}
s483* s750::s354( const s263& s701, s272* s588, s1907& s334 ) const{
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
s485 s1090 = s271::s1020( s300, s349[n], (s272*)s879, NULL, s879->s298() );
s349[n] = s1090;}
s493 = s1720;
s1681( s7::s867 );
s499 = s879->s834();}
void s750::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s750::s387, s1154,
{ s1124( { s1153, s7::s1395, s7::s1401 } ) }, 2, (size_t)-1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s750::s327, 0,
{ s1124( { s1153 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"fst", new s337( L"fst", &s750::s1004, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"snd", new s337( L"snd", &s750::s1077, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"append", new s337( L"append", &s750::s1316, s1154,
{ s1124( { s7::s1395, s7::s1401 } ) }, 1, (size_t)-1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s750::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"resize", new s337( L"resize", &s750::s329, s1154,
{ s1124( { s1153 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s750::s330, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s750::s398, s1153,
{ s1124( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"for-each", new s337( L"for-each", &s750::s1747, s1154,
{ s1124( { s7::s1400 } ) }, 1, 1 ) ) );
s348.equal_range( L"get" ).first->second->s1263( true );
s348.equal_range( L"fst" ).first->second->s1263( true );
s348.equal_range( L"snd" ).first->second->s1263( true );}
s483* s750::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s750( s300, s588, L"", ast_, s1740 );}
s483* s750::s355( s272* s588, const std::vector<s1063>& vt ) const{
assert( 0 );
return 0;}
s1063 s750::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"fst" )
s685 = s349[0]->s352();
else if( s1555 == L"snd" )
s685 = s349[1]->s352();
else if( s1555 == L"get" ) {
return s7::s1556 + 1;
if( l[0]->s352() != s1153 )
throw new s16( L"individual elements of an UntypedVector can be accessed "
"only by a literal numerical index" );
int n = (int)*l[0];
s685 = s349[n]->s352();}
return s685;}
inline bool
s750::s501( const s483* s502 ) const{
return ( ( (s316*)s502 )->s352() == s352() );}
s1063 s750::s319() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s271* s750::s335() const{
return new s750( *this );}
void s750::s356( s271* p ) const{
p = new s750( *this );}
void s750::assign( const vector<s485>& p ){
s349.assign( begin( p ), end( p ) );}
Iterator* s750::s1187() {
if( s349.size() )
return new s963( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s963( s300, this, s349.end(), s349.end() ); }
Iterator* s750::s1191(){
return new s963( s300, this, s349.end(), s349.end() ); }
s1146 s750::s1196(){
return std::make_pair( s1187(), s1191() );}
#undef s698
#define s698 ((s750*)(s484*)*s274)
inline void s750::s387( s483** s274, size_t s498 ){
s274[3]->s356( ( (s750*)DR )->s349[(int)*s274[2]] );}
inline void s750::s327( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[(int)*s274[2]];}
inline void s750::s1004( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[0];}
inline void s750::s1077( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s750*)DR )->s349[1];}
inline void s750::s1316( s483** s274, size_t s498 ){
/*if( ( (s750*)DR )->s319() != s274[2]->s495() )
throw new s16( L"unmatched element type" );*/
( (s750*)DR )->s349.push_back( s274[2]->s335() );}
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
inline void s750::s1747( s483** s274, size_t s498 ){
using s1132 = s750;
using s941 = s963;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
s838* s1765 = (s838*)s274[2];
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename s1388::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
while( s1521 != s1522 ) {
s1765->s596( vector<s485>( { *s1521 } ) );
s1765->s497( 0, 0 );
++s1521;}}
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
wstring s750::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"UT[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s750::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );}
size_t s750::s322() const{
size_t s685 = 0;
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
s961::s961( s262* s300, s272* s588, s1907& s77, const s263* ast_, const s1697& s1761 )
: s750( s300, ast_ ){
s1202 = s1153;
if( s77.size() ) {
s1162( s77, s588, s1761 );}
if( !s493 )
s493 = Types.Tuple;}
s961::s961( s262* s300, const std::vector<s271*>& l, const s263* ast_ )
: s750( s300, l, ast_ ){
s493 = s1719;}
s961::s961( const s961& right, const s263* ast_ )
: s750( right ){
s349.assign( begin( right.s349 ), end( right.s349 ) );
s493 = right.s493;
s317 = right.s317;
s1202 = right.s1202;
s325 = right.s325;}
s483* s961::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s = s300->TR().s1277( s701.s291() );
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
s961* s685 = new s961( s300, s588, sv, &s701 );
return s685;}
void s961::s500( const s272* s879, bool ){
wstring s77 = L"";
TDException s970( s7::s925, s934, s603() );
if( s349.size() == 2 && s349[0].s13() )
s77 = s349[1]->to_wstring();
if( s77[0] == L']' ) {
s349.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
s949 ast_ = new s263( s77.substr( 9, s77.size() - snum.size() - 10 ), s603()->Nqj() );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s349.push_back( s300->TR().s518( *(s263*)ast_, (s272*)s879, s879->s834() ) );}
else if( s349.size() ) {
s813::Cont s1281;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<";
for( size_t n = 0; n < s349.size(); ++n ) {
if( s349[n]->s494() == s475 ) {
s349[n]->s500( s879 );
s349[n] = s349[n].s15<s371*>()->s377();}
s485 s1090 = s271::s1020( s300, s349[n], (s272*)s879, NULL, s879->s298() );
s349[n] = s1090;
ts += s1090->s353();
if( n < s349.size() - 1 )
ts += L" ";}
ts += L">";
s493 = s1197( ts, s1281 );}
s1681( s7::s867 );
s499 = s879->s298();}
void s961::s350(){
s348.insert( make_pair( L"set", new s337( L"set", &s961::s387, s1154,
{ s1124( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s961::s1267, s1154,
{ s1124( { s1514::s1551, s7::s1395, s7::s1401 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s961::s327, 0,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"fst", new s337( L"fst", &s961::s1004, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"snd", new s337( L"snd", &s961::s1077, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"append", new s337( L"append", &s961::s1316, s1154,
{ s1124( { s7::s1395, s7::s1401 } ) }, 1, (size_t)-1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s961::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"resize", new s337( L"resize", &s961::s329, s1154,
{ s1124( { s1514::s1551 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s961::s330, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"eq", new s337( L"eq", &s961::s398, s1153,
{ s1124( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"for-each", new s337( L"for-each", &s750::s1747, s1154,
{ s1124( { s7::s1400 } ) }, 1, 1 ) ) );
s348.equal_range( L"get" ).first->second->s1263( true );
s348.equal_range( L"fst" ).first->second->s1263( true );
s348.equal_range( L"snd" ).first->second->s1263( true );}
s483* s961::s355( s272* s588, const std::vector<s1063>& vt ) const{
s961* s685 = new s961( s300, NULL, L"" );
s813 s619( vt );
s685->s493 = s685->s317 = s685->s325 = s300->TR().s1013( s619 );
return s685;}
s483* s961::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
s961* s685 = new s961( s300, l, ast_ );
return s685;}
void s961::s1162( const wstring& s77,	s272* s588, const s1697& s1761 ){
assert( !s77.empty() );
wstring s1275, s644, s1268;
if( s77[0] == L'[' ) {
s1268 = s77.substr( 1, s77.size() - 2 );}
else {
s1163( s300, s77, s1275, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1268 = s644.substr( 1, s644.size() - 2 );
if( !s1275.empty() )
s1160( s1275 );}
if( !s1268.empty() ) {
load( s1268, s588, s1761 );}
else if( !s644.empty() ) {
if( s644.find_first_not_of( s4::digits ) == string::npos ) {
s349.push_back( 0 );
s349.push_back( new s359( s300, s644, ns ) );}}}
void s961::s1160( const std::wstring& s1275 ){
s813::Cont vt;
size_t pos = 0;
s300->TR().s1058( s1275, pos, vt );
s813::Cont s1284( begin( vt ), end( vt ) );
if( s1284.size() > 2 )
s325 = s300->TR().s1048( s1284 );
else
s325 = s1284[0];
s493 = s317 = s325;}
s1063 s961::s1197( const std::wstring& s1275, s813::Cont& s588 ){
s1063 s685;
s813::Cont vt;
size_t pos = 0;
s300->TR().s1058( s1275, pos, vt );
s685 = s300->TR().s1013( s813( vt ), false );
if( s685 ) {
s588.assign( vt.begin(), vt.end() );
return s685;}
s685 = s300->TR().s1048( vt );
s588.assign( vt.begin(), vt.end() );
return s685;}
void s961::load( const wstring& s77, s272* s588, const s1697& s1761 ){
TDException s970( s7::s1130, s934, s603() );
size_t pos = 0;
const s947* s1053 = NULL;
if( s603() && s603()->Nqj() )
s1053 = s603()->Nqj()->s1008();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1053, s77, pos, s94, s1761 );
if( s94.size() ) {
s813::Cont s1281;
if( s493 ) {
const s813& vt = s300->TR().s1015( s493 );
s1281.assign( vt.s819().begin(), vt.s819().end() );
if( s94.size() != ( s1281.size() - 2 ) / 2 )
throw s970.s1002( L"wrong number of elements passed for inititalizing tuple" );}
else
s1281.push_back( s1719 );
for( size_t n = 0; n < s94.size(); ++n ) {
s949 s225 = new s263( L"", *s94[n] );
s271* p = NULL;
if( s225->s291().empty() ) {
if( s1761.s1746 && s493 ) {
s225->s1770( s300->TR().s804( s1281[( n + 1 ) * 2] ) + L"()" );
p = s271::s504( *s225, s300, s588, s588->s298() );
p->s1681( s7::s1749 );}}
else {
if( s493 )
s225->s1346( s1281[( n + 1 ) * 2] );
p = s271::s504( *s225, s300, s588, s588->s298() );}
s349.push_back( p );
if( s493 ) {
(void)0;}
else {
s1281.push_back( p->s352() );
s1281.push_back( 0 );}}
s1281.insert( s1281.begin() + 1, (s1063)( s1281.size() - 1 ) / 2 );
if( !s325 ) {
s493 = s300->TR().s1048( s1281 );
s325 = s317 = s493;}}
s1264();}
s1063 s961::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"fst" )
s685 = s300->TR().s1015( s493 ).s352( ( 0 + 1 ) * 2 );
else if( s1555 == L"snd" )
s685 = s300->TR().s1015( s493 ).s352( ( 1 + 1 ) * 2 );
else if( s1555 == L"get" ) {
int n = (int)*l[0];
s685 = s300->TR().s1015( s493 ).s352( ( n + 1 ) * 2 );}
return s685;}
#undef s698
#define s698 ((s961*)(s484*)*s274)
inline void s961::s387( s483** s274, size_t s498 ){
s961* s823 = ( (s961*)DR );
if( s823->s352() != s274[2]->s352() )
throw new s16( L"mismatched types in assignment expression" );
s274[2]->s356( s823 );}
inline void s961::s1267( s483** s274, size_t s498 ){
s961* s823 = ( (s961*)DR );
size_t idx = (int)*s274[2];
s271* el = s823->s349[idx];
if( ! s274[3]->s1543( el->s352()) )
throw new s16( L"mismatched types in assignment expression" );
s274[3]->s356( ( (s961*)DR )->s349[(int)*s274[2]] );}
inline void s961::s327( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s961*)DR )->s349[(int)*s274[2]];}
inline void s961::s1004( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s961*)DR )->s349[0];}
inline void s961::s1077( s483** s274, size_t s498 ){
*s274 = (s483*)(s271*)( (s961*)DR )->s349[1];}
inline void s961::s1316( s483** s274, size_t s498 ){
s961* s823 = ( (s961*)DR );
const s961* pro = (s961*)s823->s300->TR().s1009( DR->s352() );
size_t n = s823->s349.size();
if( n >= pro->s349.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s349[n]->s501( s274[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s750*)DR )->s319() != s274[2]->s495() )
*/
s823->s349.push_back( s274[2]->s335() );}
inline void s961::s328( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s961*)DR )->s349.size();}
inline void s961::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
( (s961*)DR )->s349.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s750*)DR )->s349[i] = ( (s750*)DR )->s300->s216(
( (s750*)DR )->s317, ( (s750*)DR )->s499 ).s15<s484*>();*/
}
inline void s961::s330( s483** s274, size_t s498 ){
( (s961*)DR )->s349.clear();}
inline void s961::s398( s483** s274, size_t s498 ){
size_t size = ( (s961*)DR )->s349.size();
s961* right = (s961*)s274[2];
if( right->s349.size() != size ) {
*( (s346*)*s274 )->s357() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s961*)DR )->s349[n] ) {
*( (s346*)*s274 )->s357() = 0;
return;}}
*( (s346*)*s274 )->s357() = 1;}
inline void s961::s331( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s961*)DR )->s349.size();}
s271* s961::s335() const{
return new s961( *this );}
void s961::s356( s271* p ) const{
*p = *this;}
wstring s961::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"[[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += s349[n]->to_wstring() + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]]";
return s685;}
s1294::s1294( s262* s300, s272* s588, const wstring& s77, const s263* ast_,
const s1697& s1761 )
: s1403( s300, s588, ast_ ){
s1162( s77, s588, s1761 );
if( !s493 )
s493 = Types.ByteArray;}
s1294::s1294( const s1294& right, const s263* ast_ )
: s1403( right.s300, NULL, ast_ ){
s349 = right.s349;
s1202 = right.s1202;
s325 = right.s325;
s317 = right.s317;
s493 = right.s493;
wh = right.wh;}
s1294::s1294( s262* s300, const std::vector<s271*>& l, const s263* ast_ )
: s1403( s300, NULL, ast_ ){
s1162( L"", NULL, s1738 );
if( l.size() ) {
s317 = l[0]->s352();
for( size_t n = 0; n < l.size(); ++n )
s349.push_back( *( (s1297*)l[n] )->s357() );}
if( !s493 )
s493 = Types.ByteArray;}
s1294::~s1294(){
s349.clear();}
void s1294::s1162( const wstring& s77, s483* s588, const s1697& s1761 ){
s1202 = s1153;
s325 = s1310;
s813::Cont v = { s1719, 2, s1153, 0, s325, 0 };
s317 = s300->TR().s1048( v );
s493 = s1151;
if( s77.empty() )
return;
wstring s1275, s644, s1268;
if( s77[0] == L'[' ) {
s1268 = s77;}
else {
s1163( s300, s77, s1275, s644 );
if( !s644.empty() && s644[0] == L'[' )
s1268 = s644;
if( s1275 != s353() )
throw new s16( L"wrong syntax of ByteArray declaration" );}
if( !s1268.empty() ) {
load( s1268, s588, s1761 );}
else if( !s644.empty() ) {
if( s644[0] == L']' && s644.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
wstring snum = s644.substr( s644.rfind( L" " ) );
size_t s163 = std::stoi( snum );
s349.resize( s163 );}}}
void s1294::load( s1907& s77, s483* s588, const s1697& s1761 ){
TDException s970( s7::s1300, s934, s603() );
size_t pos = 0;
const s947* s1053 = NULL;
if( s603() && s603()->Nqj() )
s1053 = s603()->Nqj()->s1008();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1053, s77, pos, s94, s1761 );
if( s94.size() ) {
for( size_t n = 0; n < s94.size(); ++n ) {
size_t s163 = s94[n]->s56();
s349.push_back( (tdbyte_t)s163 );}}}
s483* s1294::s354( const s263& s701, s272* s588, s1907& s334 ) const{
TDException s970( s7::s1298, s934, &s701,
L"wrong ByteArray constructor syntax" );
wstring s = s300->TR().s1277( s701.s291() );
wstring sv;
wstring s347 = s353();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s970.s1002( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1294* s685 = new s1294( s300, s588, sv, &s701 );
return s685;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1323( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1294::s500( const s272* s879, bool ){
s1681( s7::s867 );
if( s879 )
s499 = s879->s834();}
void s1294::s350(){
s1403<s1377, tdbyte_t, s1294, s1297>::s350();
s348 = s1403<s1377, tdbyte_t, s1294, s1297>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1294::s1238, s1151,
{ s1124(), s1124( { s7::s1395, s7::s1401 } ) }, 0, 1 ) ) );
s348.emplace( make_pair( L"set", new s337( L"set", &s1294::s387, s1154,
{ s1124( { s1514::s1509 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"set-el", new s337( L"set-el", &s1294::s1266, s1154,
{ s1124( { s1153, s1153 } ) }, 2, 2 ) ) );
s348.emplace( make_pair( L"get", new s337( L"get", &s1294::s327, s1310,
{ s1124( { s1153 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"append", new s337( L"append", &s1294::s1316, s1154,
{ s1124( { s7::s1399 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"resize", new s337( L"resize", &s1294::s329, s1154,
{ s1124( { s1153 } ) }, 1, 1 ) ) );
s348.emplace( make_pair( L"eq", new s337( L"eq", &s1294::s398, s1150,
{ s1124( { s7::s1396 } ) }, 1, 1 ) ) );
s300->TR().s1164( s493, s7::s1414, s1514::s1510 );
s300->TR().s1164( s493, s7::s1412, s1514::s1508 );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s483* s1294::s355( s272* s588, const vector<s271*>& l, const s263* ast_ ) const{
return new s1294( s300, s588, L"", ast_ );}
s483* s1294::s355( s272* s588, const std::vector<s1063>& vt ) const{
return new s1294( s300, s588, L"" );}
inline bool
s1294::s501( const s483* s502 ) const{
return ( ( (s1294*)s502 )->s352() == s352() );}
s271* s1294::s335() const{
return new s1294( *this );}
void s1294::s356( s271* p ) const{
p = new s1294( *this );}
Iterator* s1294::s1166( const s483* idx ){
s1377::iterator it;
int i = (int)*idx;
if( i >= (int)s349.size() )
it = s349.end();
else {
if( i < 0 ) {
i = (int)s349.size() + i;
if( i < 0 )
i = 0;}
it = s349.begin() + i;}
return new s1295( s300, this, it, it == s349.end() ? it : it + 1 );}
Iterator* s1294::s1185( const s483* _val ){
for( auto it = begin( s349 ); it != end( s349 ); ++it )
if( *it == *( (s1297*)_val )->s357() )
return new s1295( s300, this, it, it + 1 );
return new s1295( s300, this, end( s349 ), end( s349 ) );}
s483* s1294::s1192( Iterator* it ){
size_t n = std::distance( begin( s349 ), ( (s1295*)it )->s1147() );
return new s346( s300, (int)n );}
Iterator* s1294::s1187() {
if( s349.size() )
return new s1295( s300, this, s349.begin(), s349.begin() + 1 ); 
return new s1295( s300, this, s349.end(), s349.end() ); }
Iterator* s1294::s1191() {
return new s1295( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s1294*)(s484*)*s274)
inline void s1294::s1238( s483** s274, size_t s498 ){
s1294* ps = (s1294*)DR;
s1294* s685 = NULL;
if( s498 == 2 ) {
s685 = (s1294*)( (s1294*)s274[1] )->s335();}
else if( s274[2]->s1198().s352() == s1721 ) {
s316* pv = (s316*)s274[2];
s685 = new s1294( ps->s300, ps->ns, L"", ps->s603() );
for( size_t n = 0; n < pv->s320().size(); ++n ) {
s685->s349.push_back( (int)*pv->s320()[n] );}}
else if( s274[2]->s352() == s1417 ) {
auto pr = (s385*)s274[2];
auto rp = pr->s1196();
typename s1388::iterator s1521, s1522;
s1521 = rp.first.s15<s1141*>()->s1147();
s1522 = rp.second.s15<s1141*>()->s1147();
s685 = new s1294( ps->s300, ps->ns, L"", ps->s603() );
s685->s349.assign( s1521, s1522 );}
else
assert( 0 );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1294::s387( s483** s274, size_t s498 ){
s1294* v = ( (s1294*)DR );
s326* seq = (s326*)s274[2];
s385 range( 0, -1 );
Iterator* s1022 = seq->s314( &range );
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() )
break;
v->s349.push_back( *p.s15<s1297*>()->s357() );}}
inline void s1294::s1266( s483** s274, size_t s498 ){
assert( s274[3]->s352() == s1153 );
assert( s274[2]->s352() == s1153 );
s1294* v = ( (s1294*)DR );
size_t idx = (size_t)(int)*s274[2];
v->s349[idx] = *( (s1297*)s274[3] )->s357();}
inline void s1294::s327( s483** s274, size_t s498 ){
s1297* s685 = new s1297( ( (s1294*)DR )->s300,
( (s1294*)DR )->s349[(int)*s274[2]] );
*s274 = (s483*)(s271*)s685;}
inline void s1294::s1316( s483** s274, size_t s498 ){
assert( s274[2]->s352() == s1310 );
( (s1294*)DR )->s349.push_back( *( (s1297*)s274[2] )->s357() );}
inline void s1294::s329( s483** s274, size_t s498 ){
int size = (int)*s274[2];
( (s1294*)DR )->s349.resize( size );}
inline void s1294::s398( s483** s274, size_t s498 ){
size_t size = ( (s1294*)DR )->s349.size();
s1294* right = (s1294*)s274[2];
if( right->s349.size() != size ) {
*( (s360*)*s274 )->s357() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s349[n] != ( (s1294*)DR )->s349[n] ) {
*( (s360*)*s274 )->s357() = false;
return;}}
*( (s360*)*s274 )->s357() = true;}
wstring s1294::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"[";
if( s618() == s7::s868 )
s685 += L"_not_set_";
else {
for( size_t n = 0; n < s349.size(); ++n )
s685 += std::to_wstring( s349[n] ) + ( n == s349.size() - 1 ? L"" : L", " );}
s685 += L"]";
return s685;}
void s1294::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1294::s322() const{
size_t s685 = 0;
for( size_t n = 0; n < s349.size(); ++n )
s685 = ( s685 * s349[n] ) << 1;
return s685;}
bool s1294::operator==( const s483* p ) const{
if( ( (s1294*)p )->s349.size() != s349.size() )
return false;
for( size_t n = 0; n < s349.size(); ++n )
if( !( s349[n] == ( (s1294*)p )->s349[n] ) )
return false;
return true;}
bool s1294::operator<( const s483* p ) const{
return false;}
Iterator* s1294::s314( s385* rv ){
s1146 pr = rv->s1196( this );
return new s1295( s300, this,
pr.first.s15<s1141*>()->s1147(), pr.second.s15<s1141*>()->s1147() );}
s324::s324( s262* s300, s1063 s1203, s1063 s1278, 
s272* s588, const s263* ast_ )
: s1371( s300, s588, ast_ ){
assert( s1203 && s1278 );
this->s1202 = s1203;
s325 = s1278;
s813 s1184( s813::Cont( { s1719, 2, s1202, 0, s325, 0 } ) );
s317 = s300->TR().s1013( s1184 );
s813 s1654( s813::Cont( { Types.Index, 1, s317, 0 } ) );
s493 = s300->TR().s1013( s1654 );}
s324::s324( s262* s300, s272* s588, const wstring& s77, const s263* ast_ )
: s1371( s300, s588, ast_ ){
TDException s970( s7::s1370, s934, ast_ );
if( s77.size() ) {
wstring s644, s1275;
vector<pair<wstring, s1::s9<s6::s141>>> s94;
s1162( s77, s1275, s644, s94, ast_ );
if( s94.size() ) {
for( size_t n = 0; n < s94.size(); ++n ) {
s949 s977 = new s263( s94[n].first, s603()->Nqj() );
s483* s1059 = (s483*)s271::s504( *s977, s300, s588, s588->s298() );
basic_stringstream<wchar_t> s1086;
s94[n].second->s155( &s1086 );
s949 s225 = new s263( s1086.str(), s603()->Nqj() );
s483* s1067 = (s483*)s271::s504( *s225, s300, s588, s588->s298() );
if( !s1202 ) {
s1202 = s1059->s352();
s325 = s1067->s352();}
if( s1202 != s1059->s352() || s325 != s1067->s352() )
throw s970.s1002( L"incompatible types in the index initialization list" );
s349.insert( make_pair( s1059, s1067 ) );}}
else if( s644.size() ) {
s813::Cont vt, s1024, s1105;
size_t pos = 0;
s300->TR().s1058( s77, pos, vt );
size_t idx = 2;
s491::s1010( vt, idx, s1024 );
if( s1024.size() > 2 )
s1202 = s300->TR().s1013( s813( s1024 ), false );
else
s1202 = s300->TR().s1013( 
s813( s813::Cont( { s1024[0] } ) ) );
if( !s1202 ) {
if( s1024.size() > 2 )
s1202 = s300->TR().s1048( s1024 );
else
s1202 = s1024[0];}
s491::s1010( vt, idx, s1105 );
if( s1105.size() > 2 )
s325 = s300->TR().s1013( s813( s1105 ), false );
else
s325 = s300->TR().s1013(
s813( s813::Cont( { s1105[0] } ) ) );
if( !s325 ) {
if( s1105.size() > 2 )
s325 = s300->TR().s1048( s1105 );
else
s325 = s1105[0];}}
else if( false && s77[0] == L'(' ) {
wstring sv = s4::s52( s77.substr( 1, s77.size() - 2 ), L" " );
wsmatch s1076;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1076, rg ) ) {
wstring s1094 = s1076[1].str();
wstring s1095 = s1076[2].str();
sv = L"Index(" + s1094 + L" " + s1095 + L")";
s499 = sv;}}
else
assert( 0 );// s499 = s77;
}
if( !Types.Index )
s493 = 0;
else {
if( s1202 ) {
s317 = s300->TR().s1048( s813::Cont( { s1719, 2, s1202, 0, s325, 0 } ) );
s493 = s300->TR().s1048( s813::Cont( { Types.Index, 1, s317, 0 } ) );}
else {
s317 = s493 = 0;}}}
s324::s324( const s324& right, const s263* ast_ )
: s1371( right.s300, right.ns, ast_ ){
s349 = right.s349;
s493 = right.s493;
s1202 = right.s1202;
s325 = right.s325;
s317 = right.s317;
wh = right.wh;}
s324::s324( s262* s300, const std::vector<s271*>& l,
s272* s588, const s263* ast_, s1063 s709, s1063 s1183,
s1063 s1640, s1063 s1278 )
: s1371( s300, s588, ast_ ){
s1202 = s1640;
s325 = s1278;
s317 = s1183;
s493 = s709;
if( l.size() && ( l.front()->s352() == s352() ||
l.front()->s352() == Types.Index ) ) {
s349 = ( (s324*)l.front() )->s349;}}
void s324::s1162( const wstring& s77, wstring& s1275, wstring& s644,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s947 s1054( L"", true, s1738 );
s1054.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1163( s300, s77, s1275, s644 );}
void s324::s1160( const std::wstring& s1275, s1063& pt, 
s1063& et, s1063& kt, s1063& vt ) const{
s813::Cont s588;
pt = s1197( s1275, s588, et, kt, vt );}
s483* 
s324::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
wstring si;
wstring sv, s1275, s644;
wstring s347 = s353();
s1063 pt = 0, et = 0, kt = 0, vt = 0;
if( s701.s268( L"ownerType" ) == L"CallSite" ) {
wstring s1325 = s701.s268( L"ownerName" );
if( s1325.find( L"new<Index<" ) == 0 ) {
wstring stype = s1325.substr( 4, s1325.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
sv = s; // s4::s52( s, L"{}" );
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );
s1163( s300, s, s1275, s644 );
if( !s644.empty() && ( s644[0] == L'{' || s644[0] == L'}' ) )
sv = s644;
if( !s1275.empty() )
s1160( s1275, pt, et, kt, vt );}
else
return 0;
s324* s685 = new s324( s300, vector<s271*>({ }), s588, &s701,
pt, et, kt, vt );
s685->load( sv, s588, L"," );
return s685;}
s1063 s324::s1197( const std::wstring& s1275, s813::Cont& s588,
s1063& et, s1063& kt, s1063& vt ) const{
s1063 s685;
s813::Cont s1281;
size_t pos = 0;
s300->TR().s1058( s1275, pos, s1281 );
s685 = s300->TR().s1013( s813( s1281 ), false );
if( s685 ) {
s588 = { Types.Index, 1, s1281[2], 0 };
et = s1281[2];
const s813& s994 = s300->TR().s1015( et );
kt = s994.s352( 2 );
vt = s994.s352( 4 );
return s685;}
s813::Cont s1470, s1517;
size_t idx = 2;
s491::s1010( s1281, idx, s1470 );
s813 s1024( s1470[0] );
kt = s300->TR().s1013( s1024 );
s491::s1010( s1281, idx, s1517 );
if( s1517.size() > 2 )
vt = s300->TR().s1048( s1517 );
else
vt = s1517[0];
et = s300->TR().s1048( 
s813::Cont( { s1719, 2, kt, 0, vt, 0 } ) );
s588 = { Types.Index, 1, et, 0 };
s685 = s300->TR().s1048( s588 );
return s685;}
void s324::load( const std::wstring& s77, s272* s588, const std::wstring& s72 ){
TDException s970( s7::s1599, s934, s603() );
vector<pair<wstring, s1::s9<s6::s141>>> s94;
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s947 s1054( L"", true, s1738 );
s1054.s170( s77, pos, ob );
ob->s160( s94 );}
if( s94.empty() )
return;
wstring ownerName = s603()->s268( L"ownerName" );
bool s1328 = false;
if( ( s603()->s268( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1328 = true;
for( size_t n = 0; n < s94.size(); ++n ) {
s949 s977 = new s263( s94[n].first, s603()->Nqj() );
s483* s1059 = (s483*)s271::s504( *s977, s300, s588, s588->s298() );
s1059->s1264();
basic_stringstream<wchar_t> s1086;
s94[n].second->s155( &s1086 );
s949 s225 = new s263( s1086.str(), s603()->Nqj() );
s483* s1067 = (s483*)s271::s504( *s225, s300, s588, s588->s298() );
s1067->s1264();
if( !s1202 ) {
s1202 = s1059->s352();
s325 = s1067->s352();}
if( s1202 != s1059->s352() || s325 != s1067->s352() )
throw s970.s1002( L"incompatible types in the index initialization list" );
s349.insert( make_pair( s1059, s1067 ) );}
if( !s1328 ) {
if( !s317 && s349.begin()->second->s352() ) {
s317 = s300->TR().s1048( { s1719, 2, s349.begin()->first->s352(), 0,
s349.begin()->second->s352(), 0 } );
s813::Cont v1 = { Types.Index, 1, s317, 0 };
s493 = s300->TR().s1048( v1 );}
else if( s325 != s349.begin()->second->s352() )
throw s970.s1002( L"index' element type doesn't match the index type" );}}
void s324::s500( const s272* s879, bool ){
TDException s970( s7::s925, s934, s603(), L"wrong Index definition" );
const wstring& s77 = s499;
if( s77.find( L"Index<" ) == 0 ) {
assert( 0 );
s813::Cont vt, s1024, s1105;
size_t pos = 0;
s300->TR().s1058( s77, pos, vt );
size_t idx = 2;
s491::s1010( vt, idx, s1024 );
s813 s1023( s1024[0] );
s1202 = s300->TR().s1013( s1023 );
s491::s1010( vt, idx, s1105 );
s813 s1102( s1105[0] );
s325 = s300->TR().s1013( s1102 );}
else if( s77[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s141>> s153;
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s947 s1054( L"", true, s1738 );
s1054.s170( s77, pos, ob );
vector<pair<wstring, s142>> s144;
ob->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s949 s977 = new s263( s144[n].first, s603()->Nqj() );
s483* s1059 = (s483*)s271::s504( *s977, s300, (s272*)s879, s879->s298() );
basic_stringstream<wchar_t> s1086;
s144[n].second->s155( &s1086 );
s949 s225 = new s263( s1086.str(), s603()->Nqj() );
s483* s1067 = (s483*)s271::s504( *s225, s300, (s272*)s879, s879->s298() );
if( !s1202 ) {
s1202 = s1059->s352();
s325 = s1067->s352();}
if( s1202 != s1059->s352() || s325 != s1067->s352() )
throw s970.s1002( L"incompatible types in the index initialization list" );
s349.insert( make_pair( s1059, s1067 ) );}}
s1264();}
void s324::s350(){
s1371<s1389, s486, s486, s324>::s350();
s348 = s1371<s1389, s486, s486, s324>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s324::s1238, s1154,
{ s1124(), s1124( { s7::s1395, s7::s1401 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s348.insert( make_pair( L"insert", new s337( L"insert", &s324::s332, s1154,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s324::s780, 0,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s324::s327, 0,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get-val", new s337( L"get-val", &s324::s1465, 0,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s324::s387, s1154,
{ s1124( { s7::s1396 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"set-el", new s337( L"set-el", &s324::s1594, s1150,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s324::s333, s1154,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s324::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.equal_range( L"find" ).first->second->s1263( true );
s348.equal_range( L"get" ).first->second->s1263( true );
s348.equal_range( L"get-val" ).first->second->s1263( true );
s300->TR().s1164( s493, s7::s1412, s1514::s1508 );
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );}
s483* s324::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
s1::s9<s324> s685 = new s324( s300, s588, L"", ast_ );
s685->s1202 = s1202;
s685->s325 = s325;
return s685;}
s483* s324::s355( s272* s588, const std::vector<s1063>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s813::Cont s994;
s491::s1010( vt, idx, s994 );
s813 s993( s994[0] );
s1063 s1183 = s300->TR().s1013( s993 );
const s813& s1101 = s300->TR().s1015( s1183 );
s813::Cont s1024, s1105;
idx = 2;
s491::s1010( s1101.s819(), idx, s1024 );
s813 s1023( s1024[0] );
s1063 s1203 = s300->TR().s1013( s1023 );
s491::s1010( s1101.s819(), idx, s1105 );
s813 s1102( s1105[0] );
s1063 s1278 = s300->TR().s1013( s1102 );
s324* s685 = new s324( s300, s1203, s1278, s588, NULL );
return s685;}
s1063 s324::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get" ) {
s685 = s317;}
else if( s1555 == L"get-val" ) {
s685 = s317;}
else
s685 = s1371::s1190( s1555, l );
return s685;}
inline bool
s324::s501( const s483* s502 ) const{
return 0; /* ( ( (s316*)s502 )->s317 == s317 );*/
}
s271* s324::s335() const{
return new s324( *this, s603() );}
void s324::s356( s271* p ) const{
p = new s324( *this );}
size_t s324::s322() const{
return (size_t)this;}
bool s324::operator==( const s483* p ) const{
return ( this == p );}
bool s324::operator<( const s483* p ) const{
return false;}
Iterator* s324::s1187() {
auto it = begin( s349 );
return new s940( s300, this, s349.begin(), ++it ); }
Iterator* s324::s1191() {
return new s940( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s324*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
inline void s324::s1238( s483** s274, size_t s498 ){
s324* ps = (s324*)DR;
s324* s685 = NULL;
if( s498 == 2 ) {
s685 = (s324*)( (s324*)s274[1] )->s335();}
else if( s274[2]->s1198().s352() == s1717 ) {
s685 = (s324*)( (s324*)s274[2] )->s335();}
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
if( dr->s1202 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s349.insert( make_pair( s152, s349 ) );}
inline void s324::s780( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s324::s327( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
throw new s16( L"key doesn't exist" );
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );
s274[0]->s1264();//s500( p->ns, true );
}}
inline void s324::s1465( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() ) {
*s274 = new s961( p->s300, vector<s271*>(
{ (s483*)PARN( 2 ), (s483*)PARN( 3 ) } ) );}
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>()->s335(), it->second.s15<s484*>()->s335() } ) );}
s274[0]->s1264();//s500( p->ns, true );
}
inline void s324::s387( s483** s274, size_t s498 ){
s324* l = (s324*)DR;
s324* right = (s324*)PARN( 2 );
*l = *right;}
inline void s324::s1594( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s324* dr = (s324*)DR;
if( dr->s1202 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1388::iterator it = dr->s349.find( (s483*)PARN( 2 ) );
if( it == dr->s349.end() ) {
s486 s1243 = (s483*)s349->s335();
s486 s1596 = (s483*)s152->s335();
dr->s349.insert( make_pair( s1596, s1243 ) );
*s274 = s369;}
else {
it->second = (s483*)s349->s335();
*s274 = s370;}}
inline void s324::s333( s483** s274, size_t s498 ){
s324* p = (s324*)DR;
p->s349.erase( (s483*)PARN( 2 ) );}
inline void s324::s328( s483** s274, size_t s498 ){}
inline void s324::s331( s483** s274, size_t s498 ){}
Iterator* s324::s314( s385* rv ){
s1146 pr = rv->s1196( this );
return new s940( s300, this,
pr.first.s15<s1141*>()->s1147(), pr.second.s15<s1141*>()->s1147() );}
wstring s324::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"{ ";
for( auto it = begin( s349 ); it != end( s349 ); ++it )
s685 += ( it == begin( s349 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s685 += L" }";
return s685;}
void s324::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Index : " << endl;
/*for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );*/
}
s1384::s1384( s262* s300, s1063 s1203, s1063 s1278, const s263* ast_ )
: s1371( s300, NULL, ast_ ){
assert( s1203 && s1278 );
s1202 = s1203;
s325 = s1278;
s813 s1184( s813::Cont( { s1719, 2, s1202, 0, s325, 0 } ) );
s493 = s300->TR().s1013( s1184 );}
s1384::s1384( s262* s300, s272* s588, const wstring& s77, const s263* ast_ )
: s1371( s300, s588, ast_ ){
TDException s970( s7::s1669, s934, ast_ );
if( s77.size() ) {
wstring s644, s1275;
vector<pair<wstring, s1::s9<s6::s141>>> s94;
s1162( s77, s1275, s644, s94, ast_ );
if( s94.size() ) {
for( size_t n = 0; n < s94.size(); ++n ) {
s949 s977 = new s263( s94[n].first, s603()->Nqj() );
s483* s1059 = (s483*)s271::s504( *s977, s300, s588, s588->s298() );
basic_stringstream<wchar_t> s1086;
s94[n].second->s155( &s1086 );
s949 s225 = new s263( s1086.str(), s603()->Nqj() );
s483* s1067 = (s483*)s271::s504( *s225, s300, s588, s588->s298() );
if( !s1202 ) {
s1202 = s1059->s352();
s325 = s1067->s352();}
if( s1202 != s1059->s352() || s325 != s1067->s352() )
throw s970.s1002( L"incompatible types in the index initialization list" );
s349.insert( make_pair( s1059, s1067 ) );}}
else if( s644.size() ) {
s813::Cont vt, s1024, s1105;
size_t pos = 0;
s300->TR().s1058( s77, pos, vt );
size_t idx = 2;
s491::s1010( vt, idx, s1024 );
s813 s1023( s1024[0] );
s1202 = s300->TR().s1013( s1023 );
s491::s1010( vt, idx, s1105 );
s813 s1102( s1105[0] );
s325 = s300->TR().s1013( s1102 );}
else if( false && s77[0] == L'{' ) {
s499 = s77;}
else if( false && s77[0] == L'(' ) {
wstring sv = s4::s52( s77.substr( 1, s77.size() - 2 ), L" " );
wsmatch s1076;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1076, rg ) ) {
wstring s1094 = s1076[1].str();
wstring s1095 = s1076[2].str();
sv = L"Index(" + s1094 + L" " + s1095 + L")";
s499 = sv;}}
else
assert( 0 );}
if( !Types.HashIndex )
s493 = 0;
else {
if( s1202 ) {
s317 = s300->TR().s1048( s813::Cont( { s1719, 2, s1202, 0, s325, 0 } ) );
s493 = s300->TR().s1048( s813::Cont( { Types.HashIndex, 1, s317, 0 } ) );}
else {
s317 = s493 = 0;}}}
s1384::s1384( const s1384& right, const s263* ast_ )
: s1371( right.s300, NULL, ast_ ){
s349 = right.s349;
s493 = right.s493;}
void s1384::s1162( const wstring& s77, wstring& s1275, wstring& s644,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s947 s1054( L"", true, s1738 );
s1054.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1163( s300, s77, s1275, s644 );}
s483* 
s1384::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
wstring s = s701.s291();
wstring si;
wstring s347 = s353();
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s52( s, L"{}" );
else if( s.find( s347 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );}
else
return 0;
return new s1384( s300, s588, si, &s701 );}
void s1384::s500( const s272* s879, bool ){
TDException s970( s7::s925, s934, s603(), L"wrong Index definition" );
const wstring& s77 = s499;
if( s77.find( L"HashIndex<" ) == 0 ) {
assert( 0 );
s813::Cont vt, s1024, s1105;
size_t pos = 0;
s300->TR().s1058( s77, pos, vt );
size_t idx = 2;
s491::s1010( vt, idx, s1024 );
s813 s1023( s1024[0] );
s1202 = s300->TR().s1013( s1023 );
s491::s1010( vt, idx, s1105 );
s813 s1102( s1105[0] );
s325 = s300->TR().s1013( s1102 );}
else if( s77[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s141>> s153;
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s947 s1054( L"", true, s1738 );
s1054.s170( s77, pos, ob );
vector<pair<wstring, s142>> s144;
ob->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s949 s977 = new s263( s144[n].first, s603()->Nqj() );
s483* s1059 = (s483*)s271::s504( *s977, s300, (s272*)s879, s879->s298() );
basic_stringstream<wchar_t> s1086;
s144[n].second->s155( &s1086 );
s949 s225 = new s263( s1086.str(), s603()->Nqj() );
s483* s1067 = (s483*)s271::s504( *s225, s300, (s272*)s879, s879->s298() );
if( !s1202 ) {
s1202 = s1059->s352();
s325 = s1067->s352();}
if( s1202 != s1059->s352() || s325 != s1067->s352() )
throw s970.s1002( L"incompatible types in the index initialization list" );
s349.insert( make_pair( s1059, s1067 ) );}}
s499 = s879->s834();}
void s1384::s350(){
s1371<s1383, s486, s486, s1384>::s350();
s348 = s1371<s1383, s486, s486, s1384>::s342();
s348.insert( make_pair( L"insert", new s337( L"insert", &s1384::s332, s1154,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"find", new s337( L"find", &s1384::s780, 0,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get", new s337( L"get", &s1384::s327, 0,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"get-val", new s337( L"get-val", &s1384::s1465, 0,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"set", new s337( L"set", &s1384::s387, s1150,
{ s1124( { s7::s1398, s7::s1399 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s1384::s333, s1154,
{ s1124( { s7::s1398 } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s1384::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.equal_range( L"find" ).first->second->s1263( true );
s348.equal_range( L"get" ).first->second->s1263( true );
s348.equal_range( L"get-val" ).first->second->s1263( true );}
s483* s1384::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
s1::s9<s1384> s685 = new s1384( s300, s588, L"", ast_ );
s685->s1202 = s1202;
s685->s325 = s325;
return s685;}
s483* s1384::s355( s272* s588, const std::vector<s1063>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s813::Cont s994;
s491::s1010( vt, idx, s994 );
s813 s993( s994[0] );
s1063 s1183 = s300->TR().s1013( s993 );
const s813& s1101 = s300->TR().s1015( s1183 );
s813::Cont s1024, s1105;
idx = 2;
s491::s1010( s1101.s819(), idx, s1024 );
s813 s1023( s1024[0] );
s1063 s1203 = s300->TR().s1013( s1023 );
s491::s1010( s1101.s819(), idx, s1105 );
s813 s1102( s1105[0] );
s1063 s1278 = s300->TR().s1013( s1102 );
s1384* s685 = new s1384( s300, s1203, s1278, NULL );
return s685;}
s1063 s1384::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get" ) {
s685 = s317;}
else if( s1555 == L"get-s" ) {
s685 = s317;}
return s685;}
inline bool
s1384::s501( const s483* s502 ) const{
return ( s502->s352() == s352() );}
s271* s1384::s335() const{
return new s1384( *this );}
void s1384::s356( s271* p ) const{
p = new s1384( *this );}
size_t s1384::s322() const{
return (size_t)this;}
bool s1384::operator==( const s483* p ) const{
return ( this == p );}
bool s1384::operator<( const s483* p ) const{
return false;}
Iterator* s1384::s1187() {
auto it = begin( s349 );
return new s1385( s300, this, s349.begin(), ++it ); }
Iterator* s1384::s1191() {
return new s1385( s300, this, s349.end(), s349.end() ); }
#undef s698
#define s698 ((s1384*)(s484*)*s274)
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
inline void s1384::s332( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s1384* dr = (s1384*)DR;
if( dr->s1202 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s349.insert( make_pair( s152, s349 ) );}
inline void s1384::s780( s483** s274, size_t s498 ){
s1384* p = (s1384*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s1384::s327( s483** s274, size_t s498 ){
s1384* p = (s1384*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() )
*s274 = NULL;
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>(), it->second.s15<s484*>() } ) );}}
inline void s1384::s1465( s483** s274, size_t s498 ){
s1384* p = (s1384*)DR;
s1388::iterator it = p->s349.find( (s483*)PARN( 2 ) );
if( it == p->s349.end() ) {
*s274 = new s961( p->s300, vector<s271*>(
{ (s483*)PARN( 2 ), (s483*)PARN( 3 ) } ) );}
else {
*s274 = new s961( p->s300, vector<s271*>(
{ it->first.s15<s484*>()->s335(), it->second.s15<s484*>()->s335() } ) );}}
inline void s1384::s387( s483** s274, size_t s498 ){
s483* s152 = (s483*)PARN( 2 );
s483* s349 = (s483*)PARN( 3 );
s1384* dr = (s1384*)DR;
if( dr->s1202 != s152->s352() || dr->s325 != s349->s352() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1388::iterator it = dr->s349.find( (s483*)PARN( 2 ) );
if( it == dr->s349.end() ) {
s483* s1243 = (s483*)s349->s335();
dr->s349.insert( make_pair( (s483*)s152->s335(), s1243 ) );
*s274 = s369;}
else {
it->second = (s483*)s349->s335();
*s274 = s370;}}
inline void s1384::s333( s483** s274, size_t s498 ){
s1384* p = (s1384*)DR;
p->s349.erase( (s483*)PARN( 2 ) );}
inline void s1384::s328( s483** s274, size_t s498 ){}
inline void s1384::s331( s483** s274, size_t s498 ){}
Iterator* s1384::s314( s385* rv ){
s1146 pr = rv->s1196( this );
return new s1385( s300, this,
pr.first.s15<s1141*>()->s1147(), pr.second.s15<s1141*>()->s1147() );}
wstring s1384::to_wstring( uint32_t s1567 ) const{
wstring s685 = L"{ ";
for( auto it = begin( s349 ); it != end( s349 ); ++it )
s685 += ( it == begin( s349 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s685 += L" }";
return s685;}
void s1384::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s349.size(); ++n )
s349[n]->s304( pd, s197 + s419 );*/
}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
s415::s415( s262* s300, s1907& s77, const s263* ast_ )
: s336( s300, NULL, ast_ ), s754( s300, Types.String, NULL ), s809( s300, Types.String, NULL ){
s493 = Types.s414;
s754.s11();
s809.s11();}
s415::s415( const s415& right, const s263* ast_ )
: s336( right.s300, right.ns, ast_ ), s754( right.s300, NULL, L"" ), s809( right.s300, NULL, L"" ){
s754 = right.s754;
s809 = right.s809;
s493 = right.s493;}
s483* s415::s354( const s263& s701, s272* s588, s1907& s334 ) const{
return new s415( s300, L"", &s701 );}
void s415::s500( const s272* s879, bool ){
s1264();}
void s415::s350(){
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1063 s1519 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );
s348.insert( make_pair( L"new", new s337( L"new", &s415::s1238, s1909,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"read", new s337( L"read", &s415::s409, s1154,
{ s1124( { Types.String, Types.String } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"read-rec", new s337( L"read-rec", &s415::s1679, s1154,
{ s1124( { Types.String, Types.String } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"reset", new s337( L"reset", &s415::s416, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"files", new s337( L"files", &s415::s417, s1519,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"dirs", new s337( L"dirs", &s415::s992, s1519,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s415::s328, s1153,
{ s1124() }, 0, 0 ) ) );}
s483* s415::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s415( s300, L"", ast_ );}
inline bool
s415::s501( const s483* s502 ) const{
return ( ((s415*)s502)->s352() == s352() );}
s271* s415::s335() const{
return s485( new s415( *this ) );}
void s415::s356( s271* p ) const{
p = new s415( *this );}
#undef s698
#define s698 ((s415*)(s484*)*s274)
inline void s415::s1238( s483** s274, size_t s498 ){
s415* s782 = (s415*)DR;
s415* s685 = new s415( s782->s300, L"", s782->s603() );
s685->s500( s782->ns, true );
*s274 = s685;}
void _findFiles( s1907& path, const wregex& rgPatt, vector<wstring>& s40,	vector<wstring>& s41 ){
vector<wstring> s788, s796;
s3::s32( path, L".*", s788, s796 );
for( size_t n = 0; n < s788.size(); ++n ) {
wstring s1678 = path + s788[n];
if( regex_match( s1678, rgPatt ) ) 
s40.push_back( s1678 );}
for( size_t n = 0; n < s796.size(); ++n ) {
if( s796[n] == L".." ||  s796[n] == L"." )
continue;
wstring s1678 = path + s796[n];
s41.push_back( s1678 );
s4::s61( s1678 );
_findFiles( s1678, rgPatt, s40, s41 );}}
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
inline void s415::s1679( s483** s274, size_t s498 ){
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
inline void s415::s992( s483** s274, size_t s498 ){
*s274 = &( (s415*)DR )->s809;}
inline void s415::s328( s483** s274, size_t s498 ){
s415* s782 = (s415*)DR;
*( (s346*)*s274 )->s357() = (int)(s782->s754.size() + s782->s809.size());}
wstring s415::to_wstring( uint32_t s1567 ) const{
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
vector<wstring> s1608( { L":append" } );
s1607::s1607( s262* s300, s272* s592, s591* s593,
const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1618, s701 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s274.assign( l.begin(), l.end() );
s493 = s1154;
s591::s1244( ( vector<s271*>& )l, s1608 );}
void
s1607::s500( const s272* s1674, bool proc ){
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.s272 )->s353() + L">";
s493 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );
s591::s500( s1674, proc );}
s486 s1607::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
s316* pv = s586.s15<s316*>();
wstring s194 = s583[1]->to_wstring();
s194 = s4::s746( s194 );
vector<s9<s143>> s662;
s950 s1053 = new s947( s194 );
s1053->read( s662, /*s7::s1108*/ L"" );
for( size_t m = 0; m < s662.size(); m++ ) {
s1604* po = new s1604( pv->Pass(), this, s662[m], NULL );
pv->add( po );}
return s586;}
s271* s1607::s335()const{
return new s1607( *this );}
s1063 s1514::s1507 = 0;
s1063 s1514::s1511 = 0;
s1063 s1514::s1506 = 0;
void Stream::s1463( std::wstring& s153, size_t s1474 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1482( s1907& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1464( std::wstring& s153, s1907& s72 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1483( s1907& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1462( s1324& s153, size_t s1474 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1481( const s1324& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1461( s1324& s153, const s1324& s72 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1480( const s1324& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
void Stream::s1915( wchar_t c ){
throw new s2::s16( L"stream method is not implemented: fill" );}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1569(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1477 )
*s1477 << std::resetiosflags( f );}
template<class s1422, class s1424>
Stream::s1926 s1408<s1422, s1424>::s1932() const{
return s1477->flags();}
template<class s1422, class s1424>
Stream::s1927 s1408<s1422, s1424>::s1933() const{
return s1477->precision();}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1931(){
if( s1477 )
*s1477 << std::showpos;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1929(){
if( s1477 )
*s1477 << std::noshowpos;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1959(){
if( s1477 )
*s1477 << std::boolalpha;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1960(){
if( s1477 )
*s1477 << std::noboolalpha;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1570( int n ){
if( s1477 )
*s1477 << std::setw( n );}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1930( int n ){
if( s1477 )
*s1477 << std::setprecision( n );}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1917(){
if( s1477 )
*s1477 << std::left;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1918(){
if( s1477 )
*s1477 << std::right;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1916(){
if( s1477 )
*s1477 << std::internal;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1928(){
if( s1477 )
*s1477 << std::fixed;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1568(){
if( s1477 )
*s1477 << std::showpos;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1957(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1476 )
*s1476 >> std::resetiosflags( f );}
template<class s1422, class s1424>
Stream::s1926 s1408<s1422, s1424>::s1963() const{
return s1476->flags();}
template<class s1422, class s1424>
Stream::s1927 s1408<s1422, s1424>::s1964() const{
return s1476->precision();}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1953(){
if( s1476 )
*s1476 >> std::boolalpha;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1955(){
if( s1476 )
*s1476 >> std::noboolalpha;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1954(){
if( s1476 )
*s1476 >> std::fixed;}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1958( int n ){
if( s1476 )
*s1476 >> std::setw( n );}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1956( int n ){
if( s1476 )
*s1476 >> std::setprecision( n );}
s507::s507( s262* s300, s272* ns_, const s263* ast_ )
: s1408( s300, ns_, ast_ ){
s493 = Types.s789;
s1476 = (basic_istringstream<wchar_t>*) &ss;
s1477 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s507::s507( const s507& r, const s263* ast_ )
: s1408( r.s300, r.ns, ast_ ), ss( r.ss.str() ){
s493 = Types.s789;
s1476 = (basic_istringstream<wchar_t>*) &ss;
s1477 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s483* s507::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s507( s300, s588, ast_ );}
void s507::s350(){
s1408<s1973,s1974>::s350();
s348 = s1408<s1973, s1974>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s507::s1238, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"str", new s337( L"str", &s507::s508, Types.String,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s507::s330, s1912,
{ s1124() }, 0, 0 ) ) );
s300->TR().s1164( s493, s7::s1411, s1514::s1507 );
s300->TR().s1164( s493, s7::s1416, s1514::s1511 );
s300->TR().s1164( s493, s7::s1410, s1514::s1506 );}
void s507::s500( const s272*, bool ){
s1264();}
void s507::release(){
ss.clear();}
s483* s507::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"StringStream(" ) == 0 )
return new s507( s300, s588, &s701 );
return NULL;}
s271* s507::s335() const{
return new s507( *this );}
void s507::s356( s271* p ) const{
if( p->s352() == s1912 )
((s507*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s352() ) );}
void s507::s1463( std::wstring& s153, size_t s1474 ){
s153 = ss.str().substr( 0, s1474 );}
void s507::s1482( s1907& src ){
ss << src;}
void s507::s1464( std::wstring& s153, s1907& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
std::getline( ss, s153, s72[0] );}
void s507::s1483( s1907& src ){
ss << src << endl;}
void s507::s1462( s1324& s153, size_t s1474 ){
s153 = (tdbyte_t*)U8( ss.str().substr( 0, s1474 )).data();}
void s507::s1481( const s1324& src ){
ss << U16( (char*)src.c_str() );}
void s507::s1461( s1324& s153, const s1324& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s72.c_str()) + L"'" );
s153.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s72.c_str())[0]);}
void s507::s1480( const s1324& src ){
ss << U16( (char*)src.c_str() ) << endl;}
void s507::s1915( wchar_t c ){
if( s1477 )
*s1477 << std::setfill( c );}
wstring s507::to_wstring( uint32_t s1567 ) const{
return ss.str(); }
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s507*)(s484*)*s274)
inline void s507::s1238( s483** s274, size_t s498 ){
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
s1296::s1296( s262* s300, s272* ns_, const s263* ast_ )
: s1408( s300, ns_, ast_ ){
s493 = Types.ByteStream;
s1476 = (basic_istringstream<tdbyte_t>*) &bs;
s1477 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1296::s1296( const s1296& r, const s263* ast_ )
: s1408( r.s300, r.ns, ast_ ), bs( r.bs.str() ){
s493 = Types.ByteStream;}
s483* s1296::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1296( s300, ast_ );}
void s1296::s350(){
s1408<s1497, s1500>::s350();
s348 = s1408<s1497, s1500>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1296::s1238, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"array", new s337( L"array", &s1296::s1317, Types.String,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"clear", new s337( L"clear", &s1296::s330, s1908,
{ s1124() }, 0, 0 ) ) );
s300->TR().s1164( s493, s7::s1411, s1514::s1507 );
s300->TR().s1164( s493, s7::s1416, s1514::s1511 );
s300->TR().s1164( s493, s7::s1410, s1514::s1506 );}
void s1296::s500( const s272*, bool ){
s1264();}
void s1296::release(){
bs.clear();}
s483* s1296::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1296( s300 );
return NULL;}
s271* s1296::s335() const{
return new s1296( *this );}
void s1296::s356( s271* p ) const{
if( p->s352() == s1908 )
((s1296*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s352() ) );}
void s1296::s1463( std::wstring& s153, size_t s1474 ){
s153 = U16( (char*)bs.str().c_str() ).substr( 0, s1474 );}
void s1296::s1482( s1907& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1296::s1464( std::wstring& s153, s1907& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
s1324 tmp;
std::getline( bs, tmp, (unsigned char)U8(s72.data())[0] );}
void s1296::s1483( s1907& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1296::s1462( s1324& s153, size_t s1474 ){
s153 = bs.str().substr( 0, s1474 );}
void s1296::s1481( const s1324& src ){
bs << src.data();}
void s1296::s1461( s1324& s153, const s1324& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s72.c_str()) + L"'" );
s153.clear();
std::getline( bs, s153, s72[0] );}
void s1296::s1480( const s1324& src ){
bs << src << endl;}
wstring s1296::to_wstring( uint32_t s1567 ) const{
s1324 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1296*)(s484*)*s274)
inline void s1296::s1238( s483** s274, size_t s498 ){
s1296* ps = (s1296*)DR;
s1296* s685 = new s1296( ps->s300, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1296::s1317( s483** s274, size_t s498 ){
s1324 s = ( (s1296*)DR)->bs.str();
( (s1294*)s274[0] )->s320().assign( begin( s ), end( s ) );}
inline void s1296::s330( s483** s274, size_t s498 ){
((s1296*)DR)->bs.rdbuf()->str(0);}
void s1296::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : [...]" << endl;}
size_t s1296::s322() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1296::operator==( const s483* p ) const{
return ( (s1296*)p )->bs.str() == bs.str();}
bool s1296::operator<( const s483* p ) const{
return bs.str() < ( (s1296*)p )->bs.str();}
s1304::s1304( s262* s300, s272* ns_, const s263* ast_ )
: s1408( s300, ns_, ast_ ){
s493 = Types.FileStream;
s1476 = NULL;
s1477 = NULL;}
s1304::s1304( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ )
: s1408( s300, s588, ast_ ){
s493 = Types.FileStream;
s1476 = NULL;
s1477 = NULL;
if( l.size() ) {
if( l[0]->s352() == Types.String )
s1343 = l[0]->to_wstring();
else
s210 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1304::s1304( const s1304& r, const s263* ast_ )
: s1408( r.s300, r.ns, ast_ ), s210( r.s210 ), mode( r.mode ){
s493 = s1910;
s1476 = NULL;
s1477 = NULL;}
s483* s1304::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1304( s300, ast_ );}
void s1304::s350(){
s1408<s1498, s1501>::s350();
s348 = s1408<s1498, s1501>::s342();
s348.insert( make_pair( L"new", new s337( L"new", &s1304::s1238, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"open-r", new s337( L"open-r", &s1304::s2030, s1154,
{ s1124(), s1124( { Types.String } ), s1124( { Types.String, Types.String } ) }, false, s2052 ) ) );
s348.insert( make_pair( L"open-w", new s337( L"open-w", &s1304::s2032, s1154,
{ s1124(), s1124( { Types.String } ), s1124( { Types.String, Types.String } ) }, false, s2052 ) ) );
s348.insert( make_pair( L"open-rw", new s337( L"open-rw", &s1304::s2031, s1154,
{ s1124(), s1124( { Types.String } ), s1124( { Types.String, Types.String } ) }, 0, 2 ) ) );
s348.insert( make_pair( L"close", new s337( L"close", &s1304::s1326, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"read-bytes", new s337( L"read-bytes", &s1304::s2038, s1154,
{ s1124( { s1151 } ), s1124( { s1151, s1153 } ) }, 2, 2 ) ) );
s348.insert( make_pair( L"read-lines", new s337( L"read-lines", &s1304::s1486, 0,	
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"read-text", new s337( L"read-text", &s1304::s409, Types.String,	
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"write", new s337( L"write", &s1304::s1357, s1154,
{ s1124( { s1151, s1153 } ) }, 2, 2 ) ) );
s300->TR().s1164( s493, s7::s1411, s1514::s1507 );
s300->TR().s1164( s493, s7::s1416, s1514::s1511 );
s300->TR().s1164( s493, s7::s1410, s1514::s1506 );}
void s1304::s500( const s272*, bool ){
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
Types( s300, Types.String )->s353() + L">";
s1063 pt = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );
s348.equal_range( L"read-lines" ).first->second->s1265( pt );
s1264();}
void s1304::release(){
fs.close();}
s483*
s1304::s354( const s263& s701, s272* s588, s1907& s334 ) const{
wstring s_ = s701.s291();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s271*> s705;
s271::s1335( s701, s300, s588, s334, s705 );
return new s1304( s300, s705, s588, &s701 );}
return NULL;}
s271*
s1304::s335() const{
return new s1304( *this );}
void s1304::s356( s271* p ) const{
if( p->s352() == s1910 ) {
((s1304*)p)->s210 = s210;
((s1304*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s353() + L" to " + 
p->s353() );}
void s1304::s1463( std::wstring& s153, size_t s1474 ){
size_t s1113 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1113;
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
enc = s1692;}
else if( c1 == 0xFE && c2 == 0xFF ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1693;}
else if( c1 == 0xFF && c2 == 0xFE ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1694;}
else if( c1 == 0x0 && c2 == 0x0 && c3 == 0xFE && c4 == 0xFF ) {
enc = s1695;
fsz -= 4;}
else if( c1 == 0xFF && c2 == 0xFE && c3 == 0x0 && c4 == 0x0 ) {
enc = s1696;
fsz -= 4;}
else
fs.seekg( 0, ios_base::beg );}
size_t s1505 = s1474 ? ( std::min )( s1474, fsz ) : fsz;
string buf( s1505 + 0, '\0' );
fs.read( &buf[0], s1505 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1343 + L"'" );}
if( !enc || enc == s1692 ) {
s153 = U16( buf );
s153.shrink_to_fit();}
else {
fs.close();
throw new s16( L"file is not in UTF8 encoding and cannot be read as text: '" + s1343 + L"'" );}}
void s1304::s1482( s1907& src ){
fs << U8(src).data();}
void s1304::s1464( std::wstring& s153, s1907& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s153.clear();
if( fs.eof() )
return;
string buf;
char s1473 = U8( s72.data() )[0];
std::getline( fs, buf, s1473 );
s153 = U16( buf.data() );}
void s1304::s1483( s1907& src ){
fs << U8(src).data() << endl;}
void s1304::s1462( s1324& s153, size_t s1474 ){
size_t s1113 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios::end ).tellg() - s1113;
fs.seekg( s1113 );
size_t s1505 = s1474 ? (std::min)( s1474, fsz ) : fsz;
s153.resize( s1505 );
fs.read( (char*)&s153[0], s1505 );}
void s1304::s1481( const s1324& src ){
fs << *(string*)&src;}
void s1304::s1461( s1324& s153, const s1324& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s72.c_str() ) + L"'" );
string buf;
s153.clear();
std::getline( fs, buf, (char)s72[0] );
std::swap( buf, *(string*)(&s153) );}
void s1304::s1480( const s1324& src ){
fs << *(string*)&src << endl;}
wstring s1304::to_wstring( uint32_t s1567 ) const{
return L"FileStream"; }
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1304*)(s484*)*s274)
inline void s1304::s1238( s483** s274, size_t s498 ){
s1304* ps = (s1304*)DR;
s1304* s685 = new s1304( *ps );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
void s1304::s2008( s483** s274, size_t s498, wstring& s1347 ){
s1304* pf = (s1304*)DR;
if( s498 > 2 ) {
if( s274[2]->s352() == Types.String ) {
pf->s1343 = s274[2]->to_wstring();
pf->s210 = NULL;}
else {
pf->s210 = s274[2];
pf->s1343 = L"";}}
s485 s2007;
if( s498 > 3 ) {
s2007 = s274[3];
pf->mode = s2007;}
else
s2007 = pf->mode;
if( s2007.s14() ) {
if( s2007->s494() == s476 )
s1347 = s2007->s497( 0, 0 )->to_wstring();
else if( s2007->s494() != s475 )
s1347 = s2007->to_wstring();
else
s1347 = s2007.s15<s371*>()->s377()->to_wstring();}}
inline void s1304::s2030( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
wstring s1347 = L"r";
s2008( s274, s498, s1347 );
if( s1347 != L"r" )
throw new s16( L"file open mode '" + s1347 + 
L"' is incompatible with '(open-r)' method" );
if( pf->s300->s2014( s2052, s2048 ) )
return;
pf->_open( s1347 );}
inline void s1304::s2032( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
wstring s1347 = L"w";
s2008( s274, s498, s1347 );
if( s1347 != L"w" && s1347 != L"x" && s1347 != L"a" )
throw new s16( L"file open mode '" + s1347 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s2014( s2053, s2048 ) )
return;
pf->_open( s1347 );}
inline void s1304::s2031( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
wstring s1347 = L"r+";
s2008( s274, s498, s1347 );
if( s1347 != L"w" && s1347 != L"x" && s1347 != L"a" )
throw new s16( L"file open mode '" + s1347 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s2014( s2052, s2048 ) || 
pf->s300->s2014( s2053, s2048 ))
return;
pf->_open( s1347 );}
inline void s1304::s1326( s483** s274, size_t s498 ){
((s1304*)DR)->_close();
((s1304*)DR)->s1476 = NULL;
((s1304*)DR)->s1477 = NULL;}
inline void s1304::s1357( s483** s274, size_t s498 ){
assert( s498 == 4 );
assert( s274[2]->s352() == s1151 );
s1304* pf = (s1304*)DR;
if( pf->s300->s2014( s2053, s2048 ) )
return;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1343 + L"'." );
s1294* s1336 = (s1294*)s274[2];
s483* s1338 = s274[3];
int s1351 = (int)*s1338;
pf->fs.write( (const char*)s1336->s320().data(), s1351 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1343 + L"'." );}
inline void s1304::s409( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
if( pf->s300->s2014( s2052, s2048 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s359* s685 = (s359*)*s274;
pf->s1463( s685->s320(), 0 );}
inline void s1304::s2038( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
if( pf->s300->s2014( s2052, s2048 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s1294& bar = *(s1294*)s274[2];
pf->s1462(bar.s320(), 0 );}
inline void s1304::s1486( s483** s274, size_t s498 ){
s1304* pf = (s1304*)DR;
if( pf->s300->s2014( s2052, s2048 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)pf->addr();
s316& v = *(s316*)s698;
string buf;
while(std::getline( fs, buf/*, widen('\n')*/ ) ) {
v.s320().push_back( new s359( pf->s300 ) );
v.s320().back().s15<s359*>()->s1962( U16( buf ) );
v.s320().back()->s1264();
if( fs.eof() )
break;}
if( fs.bad() )
throw new s16( L"cannot read from file '" + pf->s1343 + L"'" );}
void s1304::_open( const wstring& s1347 ){
if( fs.is_open() )
fs.close();
wstring path;
if( !s1343.empty() )
path = s1343;
else {
if( s210->s494() != s475 )
path = s210->to_wstring();
else 
path = s210.s15<s371*>()->s377()->to_wstring();
s1343 = path;}
if( !s3::s724( path ) )
path = s300->s716() + path;
s1476 = NULL;
s1477 = NULL;
std::ios_base::openmode md;
if( s1347.empty() || s1347 == L"r" ) {
md = ios::in | ios::binary;
s1476 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1347 == L"w" || s1347 == L"x" ) {
md = ios::out | ios::binary;
s1477 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1347 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1477 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1347 + L"'." );
if( s1347 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1304::_close(){
mode = s210 = NULL;
s1343.clear();
fs.close();}
void s1304::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s353() << L" : " << s1343 << endl;}
size_t s1304::s322() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1304::operator==( const s483* p ) const{
return this == p;}
bool s1304::operator<( const s483* p ) const{
return this < p;}
s1404::s1404( s262* s300, s272* ns_, const s263* ast_ )
: s1408( s300, ns_, ast_ ){
s1476 = &std::wcin;}
s483* s1404::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1404::s350(){
s300->TR().s1164( s493, s7::s1411, s1514::s1507 );}
void s1404::s500( const s272*, bool ){
s1264();}
s483* s1404::s354( const s263& s701, s272* s588, s1907& s334 ) const{
return NULL;}
s271* s1404::s335() const{
throw new s16( L"StdIn object cannot be copied" );}
void s1404::s356( s271* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1404::s1463( std::wstring& s153, size_t s1474 ){
s153.clear();
wcin >> s153;
if( s153.size() > s1474 )
s153.resize( s1474 );}
void s1404::s1482( s1907& src ){
throw new s16( L"cannot output to StdIn" );}
void s1404::s1464( std::wstring& s153, s1907& s72 ){
wcin >> std::ws;
s153.clear();
std::getline( wcin, s153 );}
void s1404::s1483( s1907& src ){
throw new s16( L"cannot output to StdIn" );}
void s1404::s1462( s1324& s153, size_t s1474 ){
wstring buf( s1474, L'\0' );
wcin.read( &buf[0], s1474 );
size_t s685 = wcin.gcount();
buf.resize( s685 );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1404::s1481( const s1324& src ){
throw new s16( L"cannot output to StdIn" );}
void s1404::s1461( s1324& s153, const s1324& s72 ){
wstring buf;
std::getline( wcin, buf );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1404::s1480( const s1324& src ){
throw new s16( L"cannot output to StdIn" );}
wstring s1404::to_wstring( uint32_t s1567 ) const{
throw new s16( L"22: not implemented" );}
void s1404::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdIn object" << endl;}
size_t s1404::s322() const{
throw new s16( L"15: not implemented" );}
bool s1404::operator==( const s483* p ) const{
throw new s16( L"16: not implemented" );}
bool s1404::operator<( const s483* p ) const{
throw new s16( L"17: not implemented" );}
s1406::s1406( s262* s300, s272* ns_, const s263* ast_ )
: s1408( s300, ns_, ast_ ){
s1477 = &std::wcout;}
s483* s1406::s355( s272* s588, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1406::s350(){
s300->TR().s1164( s493, s7::s1416, s1514::s1511 );}
void s1406::s500( const s272*, bool ){
s1264();}
s483* s1406::s354( const s263& s701, s272* s588, s1907& s334 ) const{
return NULL;}
s271* s1406::s335() const{
throw new s16( L"StdOut object cannot be copied" );}
void s1406::s356( s271* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1406::s1463( std::wstring& s153, size_t s1474 ){
throw new s16( L"cannot get input from StdOut" );}
void s1406::s1482( s1907& src ){
wcout << src;}
void s1406::s1464( std::wstring& s153, s1907& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1406::s1483( s1907& src ){
wcout << src << endl;}
void s1406::s1462( s1324& s153, size_t s1474 ){
throw new s16( L"cannot get input from StdOut" );}
void s1406::s1481( const s1324& src ){
wcout << U16( (const char*)src.data() );}
void s1406::s1461( s1324& s153, const s1324& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1406::s1480( const s1324& src ){
wcout << U16( (const char*)src.data() ) << endl;}
void s1406::s1915( wchar_t c ){
if( s1477 )
*s1477 << std::setfill( c );}
wstring s1406::to_wstring( uint32_t s1567 ) const{
throw new s16( L"21: not implemented" );}
void s1406::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdOut object" << endl;}
size_t s1406::s322() const{
throw new s16( L"18: not implemented" );}
bool s1406::operator==( const s483* p ) const{
throw new s16( L"19: not implemented" );}
bool s1406::operator<( const s483* p ) const{
throw new s16( L"20: not implemented" );}
s605::s605( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s233, s701, true ){
TDException s970( s7::s1690, s934, s701, L"malformed syntax of 'with' statement" );
size_t n = 0;
bool s1170;
for( ; n < l.size(); n += 2 ) {
s1170 = false;
if( ( (s483*)l[n] ) == s1688 ) {
if( l.size() == n )
throw s970.s1002( L"the 'const' keyword should precede the parameter name" );
s1170 = true;
++n;}
if( l[n]->s494() != s475 ) {
if( s1170 )
throw s970.s1002( L"the 'const' keyword should precede the parameter name" );
break;}
s371* s76 = (s371*)l[n];
s483* s619 = (s483*)l[n + 1];
if( s1170 )
s76->s1262();
s628.s541( s76->s617(), s619 );
s274.push_back( s619->s335() );
s582.push_back( s619 );
s630.push_back( s619 );
s631.push_back( *s76 );}
s584.insert( s584.end(), l.begin() + n, l.end() );}
void
s605::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
if( !s493 )
s493 = s1154;
return;
s671 = proc ? s588->s298() : s1674->s298();
if( s588->s494() == s479 || s588->s494() == s478 ) {
if( s588->s494() == s478 )
return;}
if( s274.size() > s630.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s485 par = s274[n];
if( par->s494() == s475 ) {
if( par.s15<s371*>()->s381().s13() )
par.s15<s371*>()->s500( this, proc );}
else
s847( par, n, s274[n], s1674 );}
for( size_t n = 0; n < s274.size(); ++n ) {
s628.s541( s631[n].s617(), s274[n].s15<s483*>(), s482::s147 );
s274[n]->s1681( s7::s867 );
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
s630.resize( s274.size() );
for( size_t n = 0; n < s274.size(); ++n ) {
s486 s153;
if( s274[n]->s494() == s474 || 
s274[n]->s494() == s480 )
s153 = (s483*)s274[n]->s335();
else
s153 = s274[n]->s497( NULL, 0 );
if( s153->s618() < 0 ) {
s586 = s153;
return s153;}
s630[n] = s153.s15<s484*>();}
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s691, s697 );
if( s685->s618() < 0 )
break;}
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->release();}
s630.clear();
s586 = s685;
return s685;}
s305::s305( s262* s300, s272* s592, Transd* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s255, s701 ){
if( l.size() < 2 )
throw new s16( s255 + L"(): wrong numbers of arguments" );
s274.push_back( l[0] );
s630.resize( 1 );
s631.push_back( s371( L"@cond", s300 ) );
s584.insert( s584.end(), l.begin() + 1, l.end() );}
void
s305::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
s306 = s274[0];
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
s307::s307( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s254, s701, true ),
s311( s7::s462, s300 ), s312( s300, 0 ){
if( l.size() < 1 )
throw new s16( s254 + L"(): wrong numbers of arguments" );
s628.s541( s311.s617(), &s312 );
s582.push_back( (s483*)&s312 );
s630.push_back( (s483*)&s312 );
s631.push_back( s371( s311.s617(), s300 ) );
s308 = l[0];
s371* w = (s371*) l[1];
if( w->s617() != L"with" )
throw new s16( L"unknown syntax of 'through' statement" );
s309 = (s371*) l[2];
s628.s541( s309->s617(), s310.s15<s483*>() );
s582.push_back( (s483*)&s312 ); //..
s630.push_back( (s483*)&s312 );
s631.push_back( s371( s309->s617(), s300 ) );
s584.assign( l.begin()+3, l.end() );}
void
s307::s500( const s272* s1674, bool proc ){
s472 pc = s308->s494();
if( pc == s477 ) {
s308 = s600( s308.s15<s561*>(), s300, s588, this, s298(), proc );
s308.s15<Transd*>()->s500( s1674, proc );}
else if( pc == s475 )
s308.s15<s371*>()->s500( this, proc );
else
throw new s16( L"unknown container type" );
s630[1] = s300->TR().s518( ( (s326*)s308->s496() )->s319(), s588, s588->s298() );
s630[1]->s1681( s7::s867 );
s591::s500( s1674, proc );}
s486 s307::s497( s483** s691, size_t s697 ){
s486 s685;
s472 pc = s308->s494();
s1::s9<s326> s588;
if( pc == s476 ) {
s588 = s308->s497(0,0).s15<s326*>();}
else
s588 = ((s326*)s308.s15<s371*>()->s377());
Iterator* s1022 = s588->s314( NULL );
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() ) {
s685 = s365.s15<s483*>();
break;}
s630[1] = p;
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s691, s697 );
if( s685->s618() < 0 )
break;}
if( s685->s618() == s7::s439 || s685->s618() == s7::s440 )
break;}
return s685;}
s614::s614( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s565, s260, s701, true ),
s311( s7::s462, s300 ), s312( s300, 0 ){
TDException s970( s7::s1670, s934, s701, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s970.s1002( L"too few arguments" );
s628.s541( s311.s617(), &s312 );
s582.push_back( (s483*)&s312 );
s630.push_back( (s483*)&s312 );
s631.push_back( s371( s311.s617(), s300 ) );
s271* p = l[0];
if( p->s494() != s475 )
throw s970.s1002( L"the variable must be a name" );
s713 = (s371*) l[0];
varval = s365.s15<s483*>();
s371* in = (s371*) l[1];
if( in->s617() != L"in" )
throw s970.s1002( L"the 'in' keyword is missing" );
s308 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s494() != s475 )
throw s970.s1002( actmsg );
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
s1062 = l[idx+1];}
else {
if( ((s371*)p)->s617() != L"do" )
throw new s16( actmsg );
s584.assign( l.begin() + (idx + 1), l.end() );}
s628.s541( s713->s617(), NULL );
s582.push_back( varval );
s630.push_back( varval );
s631.push_back( s371( s713->s617(), s300 ) );}
void
s614::s500( const s272* s1674, bool proc ){
TDException s970( s7::s1380, s934, s603(), L"malformed syntax of 'for' statement" );
s472 pc = s308->s494();
if( pc == s477 ) {
s485 s592 = s600( s308.s15<s561*>(), s300, s588, this, s298(), proc );
s308 = s592;
s308.s15<Transd*>()->s500( s1674, false );}
else if( pc == s475 ) {
s308.s15<s371*>()->s500( this, proc );}
else if( pc == s474 )
s308->s500( this );
else
throw s970.s1002( L"unknown iterable type" );
s484* s1478 = s308->s496();
s1063 vt = ( (s326*)s1478 )->ValType();
varval = s300->TR().s518(vt, s588, s588->s298() );
varval->s1681( s7::s867 );
s713->s382( varval );
s630[1] = varval.s15<s484*>();
s628.s541( s713->s617(), varval.s15<s484*>(), s482::s147 );
if( where ) {
pc = where->s494();
if( pc == s477 ) {
where = s600( where.s15<s561*>(), s300, s588, this, s298(), proc );
where.s15<Transd*>()->s500( s1674, false );}
else
throw s970.s1002( L"WHERE clause must be a lambda" );}
if( s1062 ) {
pc = s1062->s494();
if( pc == s477 ) {
s1062 = s600( s1062.s15<s561*>(), s300, s588, this, s298(), proc );
s1062.s15<Transd*>()->s500( s1674, false );}
else if( pc == s475 ){
s1062.s15<s371*>()->s500( this );}
else if( pc == s474 )
(void)0;
else
throw s970.s1002( L"PROJECT clause must be a lambda." );
s813::Cont s1281;
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + 
s300->TR().s804( s1062->s352() ) + L">";
ts = s300->TR().s1354( ts );
s493 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );}
s591::s500( s1674, proc );}
s486 s614::s497( s483** s691, size_t s697 ){
s486 s685 = s586;
s472 pc = s308->s494();
s9<s326> s588;
if( pc == s476 )
s588 = s308->s497( 0, 0 ).s15<s326*>();
else if( pc == s475 )
s588 = ((s326*)s308.s15<s371*>()->s377());
else
s588 = s308.s15<s326*>();
if( s1062.s14() )
s586.s15<s316*>()->clear();
Iterator* s1022 = s588->s314( NULL );
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() )
break;
s630[0] = s1022->Idx();
s630[1] = p.s15<s484*>();
if( where ) {
if( ((bool)*(s483*)where->s497( 0, 0 )) != true )
continue;}
if( s1062 ) {
s586.s15<s316*>()->add( 
s1062->s497( 0, 0 ).s15<s484*>()->s335() );}
else {
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s691, s697 );
if( s685->s618() < 0 )
break;}
if( s685->s618() == s7::s439 || s685->s618() == s7::s440 ) {
if( s685->s618() == s7::s439 )
s685 = s365.s15<s483*>();
break;}}}
return s685;}
s271* s605::s335()const{
return new s605( *this );}
s271* s305::s335()const{
return new s305( *this );}
s271* s307::s335()const{
return new s307( *this );}
s271* s614::s335()const{
return new s614( *this );}
s604::s604( s262* s300, s272* s588, s591* s587,
s563 ct, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s588, s587, ct, l, s701, false ){
s576 = s573;}
void s604::s648( s1063 s619, s591* pOvr ){
types.push_back( s619 );
s649.push_back( pOvr );}
s486 s604::s497( s483** s691, size_t s697 ){
return s591::s497( s691, s697 );}
s838::s838( s262* s300 )
: s591( s300, NULL, NULL, s565, s252, NULL, true ){
s492 = s1247;
s493 = Types.Lambda;
if( !s493 )
wh = s7::s868;
else
wh = s7::s867;}
s838::s838( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s252, s701, true ){
s492 = s1247;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( (s483*)l[n] ) == s873 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s1905.push_back( l[n + 1]->s352() );
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
s1905.push_back( s619->s352() );
s631.push_back( s371( s76->s617(), s300 ) );}
s584.insert( s584.end(), l.begin() + n, l.end() );
if( s1905.size() ) {
s813::Cont vt = { s1718, (s1063)s1905.size() };
for( size_t n = 0; n < s1905.size(); ++n ) {
vt.push_back( s1905[n] );
vt.push_back( 0 );}
s493 = s300->TR().s1048( vt );}
else
s493 = s1718;}
s838::s838( s262* s300, s272* s592, const vector<s1063>& l,
s1063 pt, const s263* s701 )
: s591( s300, s592, NULL, s565, s252, s701, true ){
s492 = s1247;
s493 = pt;
for( size_t n = 0; n < l.size(); n += 2 )
s1905.push_back( l[n] );}
s838::s838( s838& s1903, const std::vector<s485>& l, const s263* s701 )
: s591( s1903.s300, s1903.s588, (s591*)s1903.s587, s565, s252, s701, true ){
s492 = s1247;
s493 = s1903.s493;
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
s584.insert( s584.end(), l.begin() + n, l.end() );}
s483* s838::s354( const s263& s701, s272* s588, const std::wstring& s334 ) const{
TDException s970( s7::s1894, s934, &s701,
L"wrong Lambda constructor syntax" );
wstring s = s300->TR().s1277( s701.s291() );
wstring sv;
wstring s773 = Types( s300, Types.Lambda )->s353();
wstring s1275, s644;
s1063 pt = 0;
s838* s685 = NULL;
if( s.find( L"new<Lambda<" ) == 0 ) {
s1275 = s.substr( 4, s.size() - 5 );
size_t pl = s701.Src().find( 955 );
if( pl != string::npos ) {
s644 = s701.Src().substr( pl );
s = s1275 + L"(" + s644;}
else
s = s1275 + L"()";}
if( s.find( s773 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s970.s1002( L"missing type signature" );
if( s1275.empty() )
s1163( s300, s, s1275, s644 );
if( s1275.empty() )
throw s970.s1002( L"missing type signature" );
if( s644.size() ) {
if( s644.find( L"lambda" ) == 0 || s644[0] == 955 ) {
s949 ast_ = new s263( L"(" + s644 + L")", s701.Nqj() );
s490 cs = s591::s1121( *ast_, s300, s588, s588->s298() );
return s591::s600( cs, s300, s588, (s838*)this, s588->s298(), false );}
else if( s644[0] != L']' )
throw s970.s1002( L"malformed Lambda initializer" );}
s813::Cont vt;
size_t pos = 0;
s300->TR().s1058( s1275, pos, vt );
pt = s300->TR().s1013( s813( vt ), false );
if( !pt ) {
pt = s300->TR().s1048( vt );}
s685 = new s838( s300, s588, vt, pt, &s701 );}
return s685;}
void
s838::s500( const s272* s1674, bool proc ){
s1063 pt = s493;
s493 = s1154;
s591::s500( s1674, false );
s493 = pt;
if( s1905.empty() ) {
s1905.push_back( s1154 );
if( s584.size() )
s1905.push_back( s584.back()->s352() );
else
s1905.push_back( s1154 );}
if( s1674 )
s586 = s300->TR().s518( s1330(), (s272*)s1674, s1674->s298() );
else
s586 = s300->TR().s518( s1330(), s588, s588->s298() );
if( s586.s13() )
s586 = s365.s15<s483*>();
s1264();}
s486 s838::s497( s483** s691, size_t s697 ){
s486 s685;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 )
*( s580 + n + shift ) =
(s483*)( ( s371* )*( s581 + n ) )->s377();
else if( pc == s476 ) {
s983[n+shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
*( s580 + n + shift ) = s983[n + shift];}
else if( pc == s474 )
*( s580 + n + shift ) = ( s483* )*( s581 + n );}}
if( s583.size() )
s630.assign( s583.begin() + 1, s583.end() );
for( size_t n = 0; n < s584.size(); ++n ) {
s685 = s584[n]->s497( s580, s498 );
if( s685->s618() < 0 )
break;}
return s685;}
s483* s838::s355( s272* s588, const vector<s1063>& vt ) const{
s1063 pt = s300->TR().s1048( vt );
return new s838( s300, s588, vt, pt, NULL );}
s591* s838::s1687( const std::wstring& s676, s591* s215, 
s561* cs ) const{
if( s676 == L"new" ) {
if( cs->s602().size() > 1 && (cs->s602()[1]->s494() != s475 ||
((s371*)cs->s602()[1])->s617()[0] != 955 ))
throw new s16( L"malformed lambda syntax" );
s263* s1925 = (s263*)cs->s603();
s838* s1923 = (s838*) s354( *s1925, s588.s15<s272*>(), s588->s298() );
vector<s271*> s1924( { s1923 } );
return new s1683( s300, s588.s15<s272*>(), s215, &s483::s1897, 
s1924, L"new", 0, cs->s603() );}
return s483::s1687( s676, s215, cs );}
s271* s838::s335()const{
return new s838( *this );}
s483* s838::s1898( s483** s274, size_t s498 ){
return new s838( *this );}
void s838::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Lambda : " <<  s278 << endl;
s591::s304( pd, s197 );}
s606::s606( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s243, s701 ){
s274.assign( l.begin(), l.end() );
s493 = s1150;}
s486 s606::s497( s483**, size_t s498 ){
*s586.s15<s360*>()->s357() = 0;
for( size_t n = 0; n < s274.size(); ++n ) {
if( ( bool )*( (s484*)( s274[n]->s497( 0, 0 ) ) ) ) {
*s586.s15<s360*>()->s357() = 1;
return s586;}}
return s586;}
s607::s607( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s243, s701 ){
s274.assign( l.begin(), l.end() );
s493 = s1150;}
s486 s607::s497( s483**, size_t ){
*s586.s15<s360*>()->s357() = 1;
for( size_t n = 0; n < s274.size(); ++n ) {
if( !( bool )*( (s484*)( s274[n]->s497( 0, 0 ) ) ) ) {
*s586.s15<s360*>()->s357() = 0;
return s586;}}
return s586;}
s1409::s1409( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1430, s701, true ),s1504( s7::s1376, s300 ),
s311( s7::s462, s300 ), s312( s300, 0 ){
TDException s970( s7::s1671, s934, s701, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s970.s1002( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s628.s541( s311.s617(), &s312 );
s628.s541( s1504.s617(), NULL );
s630.push_back( (s483*)&s312 );
s630.push_back( NULL );
s631.push_back( s371( s311.s617(), s300 ) );
s631.push_back( s371( s1504.s617(), s300 ) );
s308 = l[0];
if( l.size() > 1 )
lambda = l[1];
s493 = s1150;}
void
s1409::s500( const s272* s1674, bool proc ){
TDException s970( s7::s1378, s934, s603(), L"malformed syntax of 'any()' function call" );
s472 pc = s308->s494();
if( pc == s477 ) {
s485 s592 = s600( s308.s15<s561*>(), s300, s588, this, s298(), proc );
s308 = s592;
s308.s15<Transd*>()->s500( s1674, false );}
else if( pc == s475 ) {
s308.s15<s371*>()->s500( this );}
else if( pc == s474 )
s308->s500( this );
else
throw s970.s1002( L"unknown iterable type" );
varval = s300->TR().s518( ( (s326*)s308->s496() )->ValType(), s588, s588->s298() );
varval->s1264();
s1504.s382( varval );
s630[1] = varval.s15<s484*>();
if( lambda.s14() ) {
if( lambda->s494() == s475 ) {
lambda.s15<s371*>()->s500( s587 );}
else {
lambda = s271::s1020( s300, lambda, this, this, s587->s298() );}}
s591::s500( s1674, false );}
s486 s1409::s497( s483**, size_t  ){
TDException s970( s7::s1379, s1381, past );
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
Iterator* s1022 = s588->s314( NULL );
while( 1 ) {
s485 p = s1022->s315();
if( p.s13() )
break;
s630[0] = s1022->Idx();
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
s1941::s1941( s262* s300, s272* s592, s591* s593, vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1946, s701, true ){
for( size_t n = 1; n < l.size(); ++n ) {
vector<s271*>& pl = ( (s561*)l[n] )->s602();
pl.insert( begin( pl ), l[n-1] );}
s274.push_back( l.back() );}
void
s1941::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
s493 = s274[0]->s352();}
s486 s1941::s497( s483**, size_t  ){
return s274[0]->s497( 0, 0 );}
vector<wstring> s960( { L"else", L"elsif" } );
s608::s608( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s230, s701 ){
wstring s711 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s711 + L"too few arguments." );
s274.assign( l.begin(), l.end() );
s591::s1244( ( vector<s271*>& )l, s960 );}
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
if( pc == s1065 ) {
if( p.s15<s371*>()->Id() == s1226 ) {
if( s274.size() < n + 2 )
throw new s16( s711 + L"incomplete clause" );
s620.push_back( s274[++n] );
s621.push_back( s579() );
s621.back().push_back( s274[n] );}
else if( p.s15<s371*>()->Id() == s1225 ) {
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
s1063 prevPt = s583[s878]->s352();
for( size_t n = 1; n < s621.size(); ++n ) {
s878 += s621[n].size() + 1;
s1063 tmpPt = s583[s878]->s352();
if( tmpPt && tmpPt != Types.No && ( tmpPt != prevPt ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s493 = prevPt;
if( !s493 ) // e.g. break, continue
s493 = Types.Null;}
else
s493 = Types.Null;}
void
s608::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
s736( proc );
s586 = s300->TR().s518( s352(), s588, s588->s298() );
s583.insert( s583.begin(), s586 );}
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
s839::s839( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s852, s701 ){
if( l.size() > 1 )
throw new s16( s852 + L": too many arguments" );
s584.assign( l.begin(), l.end() );}
void
s839::s500( const s272* s1674, bool proc ){
if( s584.size() ) {
s591::s500( s1674, false );
s586 = s584[0]->s496();}
else {
s586 = s365.s15<s483*>();
s493 = s1154;}}
s486 s839::s497( s483** s705, size_t s498 ){
s483* s685;
if( s584.size() )
s685 = s591::s497( s705, s498 );
else
s685 = new s364( s300 );
s685->s1681( s7::s866 );
return s685;}
s271* s839::s335()const{
return new s839( *this );}
s898::s898( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s902, s701 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s902 + L": wrong number of arguments" );
if( l.empty() )
s274.push_back( new s346( s300, 0 ) );
else
s274.assign( l.begin(), l.end() );
s493 = s1153;}
void
s898::s500( const s272* s1674, bool proc ){
s591::s500( s1674, false );
if( s274[0]->s352() != s1153 )
throw new s16( L"The parameter to (exit ) must have Integer type." );}
s486 s898::s497( s483** s705, size_t s498 ){
s591::s497( s705, s498 );
code = (int)*s583[1];
throw new s16( (uint32_t) code );}
s271* s898::s335()const{
return new s898( *this );}
s611::s611( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s259, s701 ), s78( s300 ){
if( l.size() != 1 )
throw new s16( s259 + L": wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.No;
s78.s11();}
s611::s611( s262* s300 )
: s591( s300, NULL, NULL, s565, s259, NULL ), s78( s300 ){
s493 = Types.No;
s78.s11();}
void
s611::s500( const s272* s1674, bool proc ){
s78.s363( s274[0]->to_wstring() );
s586 = s366.s15<s483*>();
s583.push_back( s274[0]->s496() );}
s486 s611::s497( s483** s705, size_t s498 ){
s78.s363( s274[0]->s497( s705, s498 )->to_wstring() );
return &s78;}
s612::s612( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s257, s701, true ), 
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
: s591( s300, NULL, NULL, s565, s257, NULL, true ), 
s76( s7::s461, s300 ), s619( s300 ){}
void
s612::s500( const s272* s1674, bool proc ){
s591::s500( s1674, proc );
ctch = s584.back().s15<s613*>();
s584.pop_back();}
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
: s591( s300, s592, s593, s565, s258, s701 ){
s584.assign( l.begin(), l.end() );
s493 = Types.Null;}
s613::s613( s262* s300 )
: s591( s300, NULL, NULL, s565, s258, NULL ){
s493 = Types.Null;}
s486 s613::s497( s483** s691, size_t s697 ){
s483* s153;
for( size_t n = 0; n < s584.size(); ++n ) {
s153 = s584[n]->s497( s691, s697 );
if( s153->s618() < 0 ) {
return s153;}}
return s365.s15<s483*>();}
s755::s755( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s751, s701 ){}
void
s755::s500( const s272* s1674, bool proc ){}
s486 s755::s497( s483** s705, size_t s498 ){
return 0;}
s1682::s1682( s262* s300, s272* s592, s591* s593, s1684 ptr_,
s561* cs, const s263* s701 )
: s591( s300, s592, s593, s565, L"", s701 ), s1686( ptr_ ){
subject = cs->s602()[0];
s274.assign( cs->s602().begin() + 1, cs->s602().end() );}
void
s1682::s500( const s272* s1674, bool proc ){
s493 = s588->s352();
s591::s500( s1674, proc );
s1264();}
s486 s1682::s497( s483** s705, size_t s498 ){
s487	s1656 = subject->s497( 0, 0 ).s15<s272*>();
return ( *s1656.*s1686)( &s583[0], s498 );}
s1683::s1683( s262* s300, s272* s592, s591* s593, s1685 ptr_,
const vector<s271*>& s1924, const wstring& s676, s1063 s1074, 
const s263* s701 )
: s591( s300, s592, s593, s565, s676, s701 ), s1686( ptr_ ){
subject = s1924[0];
s274.assign( s1924.begin() + 1, s1924.end() );
s493 = s1074;}
void
s1683::s500( const s272* s1674, bool proc ){
if( !s493 ) {
s485 s703 = subject;
if( s703->s494() == s475 )
s703 = s703.s15<s371*>()->s377();
if( s703->s494() == s1247 ) {
if( s278 == L"new" )
s493 = s703->s352();
else
s493 = s703.s15<s838*>()->s1330();}
else {
s493 = s588->s352(); //subject->s352();
}}
s591::s500( s1674, proc );
s1264();}
s486 s1683::s497( s483** s705, size_t s498 ){
s485 s703 = subject;
if( s703->s494() == s475 )
s703 = s703.s15<s371*>()->s377();
if( s703->s494() == s1247 ) {
if( s278 == L"new" ) {
s838* s685 = new s838( *s703.s15<s838*>() );
s685->s500( s588, true );
return s685;}
try {
s703.s15<s838*>()->s596( s274 );}
catch( s16* e ) {
wstring s78 = L"in function '" + s278 + L"'";
if( s603() )
s78 += L" :\n" + TDException::s1914( *s603() );
e->s30( s78 );
throw e;}
return s703->s497( 0, 0 ).s15<s272*>();}
else {
s487 s1656 = subject->s497( 0, 0 ).s15<s272*>();
return ( *s1656.*s1686 )( &s583[0], s498 );}}
s1611::s1611( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1621, s701 ){
s274.assign( l.begin(), l.end() );}
s1611::s1611( const s1611& right )
: s591( right ), cmd( right.cmd ){}
void
s1611::s500( const s272* s1674, bool proc ){
s300->s2014( s2055, s2047 );
s493 = s1154;
s591::s500( s1674, proc );}
void s1614( const wstring& cmd, wstring* s1648, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1648 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1648 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s486 s1611::s497( s483** s691, size_t s697 ){
if( s300->s2014( s2055, s2048 ) )
return s586;
s1613( s691, s697 );
wstring cmd_ = s583[1]->to_wstring(), s1649;
bool* pdone = ( (s360*)s583[2] )->s357();
wstring *s1648 = NULL;
if( s583.size() > 3 )
s1648 = ( (s359*)s583[3] )->s357();
else
s1648 = &s1649;
if( s823.joinable() ) {
s823.join();}
s823 = thread( s1614, cmd_, s1648, pdone );
return s586;}
s1609::s1609( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1619, s701 ){
if( l.size() != 2 )
throw new s16( s1619 + L"(): wrong numbers of arguments" );
if( l[0]->s494() != s475 )
throw new s16( s1619 + L"(): the first argument must be a reference" );
s274.assign( l.begin(), l.end() );}
s1609::s1609( const s1609& right )
: s591( right ){}
void
s1609::s500( const s272* s1674, bool proc ){
s493 = s1154;
s591::s500( s1674, proc );}
s486 s1609::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
s371* dr = s274[0].s15<s371*>();
s272* mod = dr->s381().s15<s272*>();
mod->s1659( dr->s617(), s583[2] );
return s586;}
s1606::s1606( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1617, s701 ){
if( l.size() != 2 )
throw new s16( s1617 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1606::s1606( const s1606& right )
: s591( right ){}
void
s1606::s500( const s272* s1674, bool proc ){
s493 = s1154;
s591::s500( s1674, proc );}
s486 s1606::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
s272* dr = (s272*)s583[1];
s1604* ob = (s1604*)s583[2];
try {
dr->s1642( ob );}
catch( s16* e ) {
wstring s78 = L"in function " + s299() + L":\n";
s78 += L"during loading object: " + dr->s1675() +
L":" + dr->s353() + L":";
e->s30( s78 );
throw e;}
return s586;}
s1610::s1610( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1620, s701 ){
if( l.size() != 1 )
throw new s16( s1620 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1610::s1610( const s1610& right )
: s591( right ){}
void
s1610::s500( const s272* s1674, bool proc ){
s493 = s1154;
s591::s500( s1674, proc );}
s486 s1610::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
int dr = (int)*(s346*)s583[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s586;}
s1605::s1605( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1616, s701 ){
if( l.size() != 1 )
throw new s16( s1616 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1605::s1605( const s1605& right )
: s591( right ){}
void
s1605::s500( const s272* s1674, bool proc ){
s493 = Types.String;
s591::s500( s1674, proc );}
s486 s1605::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
s483* dr = s583[1];
wstringstream buf;
dr->s304( &buf );
*s586.s15<s359*>()->s357() = buf.str();
return s586;}
s1887::s1887( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1888, s701 ){
if( l.size() > 2 )
throw new s16( s1888 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1887::s1887( const s1887& right )
: s591( right ){}
void
s1887::s500( const s272* s1674, bool proc ){
s493 = s1152;
s591::s500( s1674, proc );}
s486 s1887::s497( s483** s691, size_t s697 ){
s1613( s691, s697 );
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);
*s586.s15<s358*>()->s357() = dist( mt );
return s586;}
s271* s608::s335() const{
return new s608( *this );}
s271* s606::s335() const{
return new s606( *this );}
s271* s607::s335()const{
return new s607( *this );}
s271* s1409::s335()const{
return new s1409( *this );}
s271* s1941::s335() const{
return new s1941( *this );}
s271* s611::s335()const{
return new s611( *this );}
s271* s612::s335() const{
return new s612( *this );}
s271* s613::s335() const{
return new s613( *this );}
s271* s755::s335() const{
return new s755( *this );}
s271* s1682::s335() const{
return new s1682( *this );}
s271* s1683::s335() const{
return new s1683( *this );}
s271* s1611::s335() const{
return new s1611( *this );}
s271* s1609::s335() const{
return new s1609( *this );}
s271* s1606::s335() const{
return new s1606( *this );}
s271* s1610::s335() const{
return new s1610( *this );}
s271* s1605::s335() const{
return new s1605( *this );}
s271* s1887::s335() const{
return new s1887( *this );}
vector<wstring> s958( { L"to:", L":sign", L":nosign", L":boolalpha", 
L":noboolalpha", L"width:", L"prec:", L"fill:", L":left", L":right", L":internal", 
L":fixed", L":group", L":nl" } );
s609::s609( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s251, s701 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s701->Src().find( L"lout" );
if( pl1 < s701->Src().find( L"textout" ) )
lout = true;
vector<s271*>tmp( l );
s591::s1244( tmp, s958 );
s274.assign( tmp.begin(), tmp.end() );
s493 = Types.Null;}
s609::s609( s262* s300 )
: s591( s300, NULL, NULL, s565, s251, NULL ), s42( NULL ),
lout( false ){
s493 = Types.Null;}
void s609::s500( const s272* s1674, bool proc ){
TDException s970( s7::s1939, s934, s603(), L"malformed '(textout)' function call" );
s591::s500( s1674, proc );
if( s274[0]->s494() == s1065 ) {
if( s274[0].s15<s371*>()->Id() == s1235 ) {
s42 = s274[1];
s274.erase( s274.begin(), s274.begin() + 2 );
s583.erase( s583.begin()+1, s583.begin() + 3 );
nlocs = s274.size();
s498 = s583.size();}}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s494() == s1065 ) {
int mark = (int)*( s274[n].s15<s371*>() )->s377();
if( mark != s1572 && s274.size() <= n )
s970.s1002( L"incorrect usage of formatting marker: " + (s274[n].s15<s371*>())->s617() );
if( mark == s1573 && !s300->TR().s1467(
s274[n + 1]->s352(), s1514::s1551 ) )
s970.s1002( L"'width:' formatting marker should have an integer parameter" );
if( mark == s1919 && !s300->TR().s1467(
s274[n + 1]->s352(), s1514::s1551 ) )
s970.s1002( L"'fill:' formatting marker should have a char (one symbol string) parameter" );}}
s1264();}
s486 s609::s497( s483** s691, size_t s697 ){
s483* s685 = s1613( s691, s697 );
if( s685 )
return s685;
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
s778 = s1407.s15<Stream*>();
s778->s1569();
uint32_t flags = 0;
for( size_t n = 1; n < s583.size(); ++n ) {
if( s583[n]->s494() == s1065 ) {
int mark = (int)*( (s371*)s583[n] )->s377();
if( mark == s1471 ) {
s778->s1931();}
else if( mark == s1592 ) {
s778->s1929();}
else if( mark == s1969 ) {
s778->s1959();}
else if( mark == s1970 ) {
s778->s1960();}
else if( mark == s1919 ) {
wchar_t c = s583[++n]->to_wstring()[0];
s778->s1915( c );}
else if( mark == s1573 ) {
int w = (int)*s583[++n];
s778->s1570( w );}
else if( mark == s1935 ) {
int pr = (int)*s583[++n];
s778->s1930( pr );}
else if( mark == s1921 ) {
s778->s1917();}
else if( mark == s1922 ) {
s778->s1918();}
else if( mark == s1920 ) {
s778->s1916();}
else if( mark == s1934 ) {
s778->s1928();}
else if( mark == s1571 ) {
flags |= s1561;}
else if( mark == s1572 ) {
s778->s1483( L"" );
n++;}}
else {
s486 s153 = s583[n]->s497( s691, s498 );
s153->s1937( s778 );}}
if( lout )
s778->s1483( L"" );
return s365;}
s271* s609::s335()const{
return new s609( *this );}
vector<wstring> s1943( { L"from:", L":boolalpha", L":noboolalpha", L"width:", 
L"prec:", L":fixed", L":group", L":nl" } );
s1942::s1942( s262* s300, s272* s592, s591* s593, 
const vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s1947, s701 ), source( NULL ),
lin( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s701->Src().find( L"lin" );
if( pl1 < s701->Src().find( L"textin" ) )
lin = true;
vector<s271*>tmp( l );
s591::s1244( tmp, s1943 );
s274.assign( tmp.begin(), tmp.end() );
s493 = Types.Null;}
s1942::s1942( s262* s300 )
: s591( s300, NULL, NULL, s565, s1947, NULL ), source( NULL ),
lin( false ){
s493 = Types.Null;}
void s1942::s500( const s272* s1674, bool proc ){
TDException s970( s7::s1938, s934, s603(), L"malformed '(textin)' function call" );
s591::s500( s1674, proc );
if( (s274[0]->s494() == s1065 && s274[0].s15<s371*>()->Id() == s1228 ) ||
(s300->TR().s1467( s274[0]->s352(), s1514::s1507 ))) {
int s375 = 1;
if( s274[0]->s494() == s1065 )
s375 = 2;
source = s274[s375 - 1];
s274.erase( s274.begin(), s274.begin() + s375 );
s583.erase( s583.begin()+1, s583.begin() + s375 + 1 );
nlocs = s274.size();
s498 = s583.size();}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s494() == s1065 ) {
int mark = ( int )*( s274[n].s15<s371*>() )->s377();
if( s274.size() <= n )
s970.s1002( L"incorrect usage of formatting marker: " + ( s274[n].s15<s371*>() )->s617() );
if( mark == s1573 && !s300->TR().s1467(
s274[n + 1]->s352(), s1514::s1551 ) )
s970.s1002( L"'width:' formatting marker should have an integer parameter" );}}
s1264();}
s486 s1942::s497( s483** s691, size_t s697 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s581 + n ) ) {
s472 pc = ( ( s484* )*( s581 + n ) )->s494();
if( pc == s475 || pc == s1339 )
*( s580 + n + shift ) =
(s483*)( ( s371* )*( s581 + n ) )->s377();
else if( pc == s476 ) {
s983[n + shift] = (s483*)( ( s591* )*( s581 + n ) )->s497( s691, s697 );
*( s580 + n + shift ) = s983[n + shift];}}}
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
src = s1405.s15<Stream*>();
src->s1569();
for( size_t n = 1; n < s583.size(); ++n ) {
if( s583[n]->s494() == s1065 ) {
int mark = (int)*( (s371*)s583[n] )->s377();
if( mark == s1969 ) {
src->s1953();}
else if( mark == s1970 ) {
src->s1955();}
else if( mark == s1573 ) {
int w = (int)*s583[++n];
src->s1958( w );}
else if( mark == s1935 ) {
int pr = (int)*s583[++n];
src->s1956( pr );}
else if( mark == s1934 ) {
src->s1954();}}
else {
s486 s153 = s583[n]->s497( s691, s498 );
s153->s1961( src );}}
if( lin )
src->ws();
return s365;}
s271* s1942::s335()const{
return new s1942( *this );}
s610::s610( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s256, s701 ){
if( l.size() != 1 )
throw new s16( s256 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s610::s610( s262* s300 )
: s591( s300, NULL, NULL, s565, s256, NULL ){}
void s610::s500( const s272* s592, bool proc ){
s300->s2014( s2054, s2047 );
s813::Cont s1281;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<" + 
Types( s300, Types.Bool )->s353() +
L" " + Types( s300, Types.String )->s353() + L">";
s493 = ((s961*)Types( s300, Types.Tuple ))->s1197( ts, s1281 );
s591::s500( s592, proc );}
s486 s610::s497( s483** s705, size_t s498 ){
s961* s685 = s586.s15<s961*>();
s685->clear();
if( s300->s2014( s2054, s2048 ) ) {
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
vector<s485> s914;
s949 ast_ = new s263( f, s603()->Nqj() );
s490 cs = s591::s1121( *ast_, s300, s588, s298() );
s914.push_back( cs );
s488 s912 = s591::s600( cs, s300, s588, this, s298(), false );
s912->s500( s588, true );
s486 res1 = s912->s497( 0, 0 );
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
s271* s610::s335() const{
return new s610( *this );}
s262* s615::s908 = NULL;
s615::s615( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s261, s701 ){
if( l.size() != 1 )
throw new s16( s261 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s615::s615( s262* s300 )
: s591( s300, NULL, NULL, s565, s261, NULL ){
s493 = Types.Null;}
s486 s615::s497( s483** s705, size_t s498 ){
vector<wstring> s913;
for( size_t n = 0; n < s274.size(); ++n ) {
s913.push_back( s274[n]->s497( 0, 0 )->to_wstring() );}
if( !s908 ) {
s908 = new s262();
s908->s1902( true );}
else
s908->reset();
s908->s209( s913[0] );
s586 = s908->run( s913 );
return s586;}
s271* s615::s335()const{
return new s615( *this );}
s797::s797( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l, const s263* s701 )
: s591( s300, s592, s593, s565, s772, s701 ){
if( l.size() != 1 )
throw new s16( s772 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s797::s497( s483** s705, size_t s498 ){
wstring s194 = s274[0]->s497( s705, s498 )->to_wstring();
s300->s209( s194 );
return s365;}
s271* s797::s335()const{
return new s797( *this );}
s775::s775( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s565, s821, s701 ){
s906 = s592->s298();
if( l.size() != 1 )
throw new s16( s821 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s775::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s904;
if( par->s494() == s475 )
s904 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s904 = par->s497( 0, 0 )->to_wstring();
try {
s272* ob = ((s272*)s300->s641( s906, s906 ));
ob->s555( s904, s906 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s775::s335()const{
return new s775( *this );}
s1309::s1309( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s565, s1319, s701 ){
if( l.size() != 1 )
throw new s16( s1319 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s1309::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s671;
if( par->s494() == s475 )
s671 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s671 = par->s497( 0, 0 )->to_wstring();
try {
s300->s1353( s671 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s1309::s335()const{
return new s1309( *this );}
s1612::s1612( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 )
: s591( s300, s592, s593, s565, s1622, s701 ){
if( l.size() != 1 )
throw new s16( s1622 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s493 = Types.Null;}
s486 s1612::s497( s483** s705, size_t s498 ){
s271* par = s274[0];
wstring s671;
if( par->s494() == s475 )
s671 = ((s371*)par)->s497( 0, 0 )->to_wstring();
else
s671 = par->s497( 0, 0 )->to_wstring();
try {
s300->s1667( s671 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s365;}
s271* s1612::s335()const{
return new s1612( *this );}
s1783::~s1783(){
release();}
void s1783::release(){
for( auto i : s871 )
i.second.clear();
s871.clear();}
s1784::s1784( s1783* s1808 ) 
: pdb( s1808 ), fi( s1849), se(s1849) {
ptr = new s1786();}
s1784::~s1784(){
if( ptr ) {
ptr->clear();
delete ptr;}}
const vector<wstring> s1780::s1881 = { L"", L"==", L"<", L">", L"<=", L">=" };
s1780::s1780( s262* s300, s272* s588, const std::wstring& s, size_t& pos ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
size_t s69 = s68;
if( s[s68] == L'"' ) {
s4::s1003( s, s69, s4::s48 );
field = s.substr( s68+1, s69 - s68 - 2 );}
else {
s69 = s.find_first_of( s4::s48, s68 );
field = s.substr( s68, s69 - s68 );}
s69 = s68 = s.find_first_not_of( s4::s48, s69 );
s4::s1003( s, s69, s4::s48 );
wstring s1867 = s.substr( s68, s69 - s68 );
auto s1838  = std::find( s1881.begin(), s1881.end(), s1867 );
if( s1838 == s1881.end() )
throw new s16( L"unknown operation in query string: " + s1867 );
op = (s1780::s1793) std::distance( s1881.begin(), s1838 );
s69 = s68 = s.find_first_not_of( s4::s48, s69 );
s4::s1003( s, s69, s4::s48 + L")" );
wstring s1868 = s.substr( s68, s69 - s68 );
s949 s701 = new s263( L"", s1868 );
par = s271::s504( *s701, s300, s588, s588->s298() );
pos = s69;}
void s1780::s500( s272* ns ){
if( par->s494() == s475 ) {
par->s500( ns );}}
void s1780::select( s1783* pdb, s1789& s153 ){
if( par->s494() == s475 )
s349 = par.s15<s371*>()->s377();
else
s349 = par;
pdb->select( field, op, s349.s15<s483*>(), s153 );}
s1781::s1781( s262* s300, s272* s588, const std::wstring& s, size_t& pos, s1782 s1805 )
: s1819( s1805 ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
if( s[s68] == L'(' ) {
s1812( s300, s588, s, ++s68 );}
else
s1812( s300, s588, s, s68 );}
s1781::s1781( const s1781& r )
: s1819( r.s1819 ), subs( r.subs ), s1813( r.s1813 ){}
void s1781::s500( s272* ns ){
for( auto i : subs )
i.s500( ns );
for( auto i : s1813 )
i.s500( ns );}
void s1781::s1812( s262* s300, s272* s588, const std::wstring& s, size_t& pos ){
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
subs.push_back( s1781( s300, s588, s, s68, s1815 ) );}
else if( s[s68] == L'A' || s[s68] == L'a' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1871 = s.substr( s68, pl - s68 );
if( s1871 != L"AND" && s1871 != L"and" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 3;
if( s1819 == s1815 )
s1819 = s1814;
else if( s1819 == s1814 )
(void)0;
else {
if( subs.empty() && s1813.empty() )
throw new s16( L"wrong query syntax: 'AND' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1781( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1813.clear();
s1819 = s1814;}}
else if( s[s68] == L'O' || s[s68] == L'o' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1871 = s.substr( s68, s.size() - pl + 1 );
if( s1871 != L"OR" && s1871 != L"or" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 2;
if( s1819 == s1815 )
s1819 = s1816;
else if( s1819 == s1816 )
(void)0;
else {
if( subs.empty() && s1813.empty() )
throw new s16( L"wrong query syntax: 'OR' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1781( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1813.clear();
s1819 = s1816;}}
else {
s1813.push_back( s1780( s300, s588, s, s68 ) );
if( s68 != string::npos )
++s68;}}}
bool s1804( s822 l, s822 r ){
return ( size_t )&( *l ) < ( size_t )&( *r );}
void s1781::select( s1783* pdb, s1784* s153 ){
s1791 s1832;
vector<s1786> s1864;
s1784 *s1879, *s1878;
for( size_t n = 0; n < s1813.size(); ++n ) {
s1789 s1071;
s1813[n].select( pdb, s1071 );
s1832.insert( s1071 );}
s1879 = pdb->s1820();
s1878 = pdb->s1820();
auto it = begin( s1832 );
if( s1832.size() ) {
if( s1819 == s1814 || s1832.size() == 1 ) {
pdb->intersect( *it, s153 );
s153->sort();}}
for( ++it; it != end( s1832 ); ++it ) {
s1879->clear();
if( s1819 == s1814 ) {
pdb->intersect( *it, s1879 );
s1879->sort();
if( s153->empty() )
s153->swap( s1879 );
else {
std::set_intersection( begin( s153->s320() ), end( s153->s320() ), 
begin( s1879->s320() ), end( s1879->s320() ), 
back_inserter( s1878->s320() ), s1804 );
s153->swap( s1878 );
s1878->clear();}}}
for( size_t n = 0; n < subs.size(); ++n ) {
subs[n].select( pdb, s1879 );
if( s1819 == s1814 ) {
s1879->sort();
if( s153->empty() )
s153->swap( s1879 );
else {
std::set_intersection( begin( s153->s320() ), end( s153->s320() ),
begin( s1879->s320() ), end( s1879->s320() ),
back_inserter( s1878->s320() ), s1804 );
s153->swap( s1878 );
s1878->clear();}}
s1879->clear();}}
vector<wstring> s959( { L"select:", L":update", L"reduce:", L"all", L"as:", L"where:",
L"satisfying:", L"using:", L":distinct",	L"sortby:", L":asc", L":desc", L"limit:", L"set:" } );
struct s848{
size_t idx;
s848( size_t s869 ): idx( s869 ){}
bool operator()( const s486 l, const s486 r ) const{
s486 ld = l.s15<s750*>()[idx];
s486 rd = r.s15<s750*>()[idx];
return ld->operator<( (s483*)&(*rd) );}
};
void s791::s1725( const std::vector<s271*>& l_, TDException& s970 ){
const size_t s1057 = 9;
std::vector<s271*> l( s1057, NULL );
s1714* sqr = new s1714;
s1713* sqp = new s1713;
sqr->verb = s744::s1778;
size_t s988 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1065 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1219 ) s988 = 2;
else if( rf->Id() == s1218 ) {
s988 = s1149;
l[1] = l_[n];}
else if( rf->Id() == s1237 ) s988 = 3;
else if( rf->Id() == s1845 ) s988 = 4;
else if( rf->Id() == s1223 ) {
s988 = s1149;
sqr->distinct = 1;}
else if( rf->Id() == s1234 ) {
sqr->s889 = s1714::s837::s828;
s988 = 6;}
else if( rf->Id() == s1220 ) {
if( s988 != 7 )
throw s970.s1002( L"the '" + rf->s617() + L"' specifier is misplaced" );
s988 = s1149;
sqr->s889 = s1714::s837::s828;}
else if( rf->Id() == s1222 ) {
if( s988 != 7 )
throw s970.s1002( L"the '" + rf->s617() + L"' specifier is misplaced" );
s988 = s1149;
sqr->s889 = s1714::s837::s831;}
else if( rf->Id() == s1232 ) 
s988 = 8;
else
throw s970.s1002( L"misplaced query keyword: " + s959[rf->Id()] );}
else
l[s988++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1074 = l[2];
sqp->where = l[3];
sqp->s1869 = l[4];
sqp->s890 = l[6];
sqp->s874 = l[8];
if( sqp->s1074.s13() )
throw s970.s1002( L"the 'as' clause is missing" );}
void s791::s1726( const std::vector<s271*>& l_, TDException& s970 ){
const size_t s1057 = 3;
std::vector<s271*> l( s1057 );
s1724* sqr = new s1724;
s1723* sqp = new s1723;
sqr->verb = s744::s1779;
size_t s988 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1065 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1756 ) s988 = 1;
else if( rf->Id() == s1845 ) s988 = 2;
else
throw s970.s1002( L"misplaced query keyword: " + s959[rf->Id()] );}
else
l[s988++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1869 = l[2];
if( sqp->what.s13() || sqp->s1869.s13() )
throw s970.s1002( L"the 'UPDATE' query must include 'SET' and `SATISFYING` clauses" );}
void s791::s2004( const std::vector<s271*>& l_, TDException& s970 ){
const size_t s1057 = 6;
std::vector<s271*> l( s1057, NULL );
s1988* sqr = new s1988;
s1987* sqp = new s1987;
sqr->verb = s744::s2061;
size_t s988 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s494() == s1065 ) {
s371* rf = (s371*)l_[n];
if( rf->Id() == s1219 ) s988 = 2;
else if( rf->Id() == s1218 ) {
s988 = s1149;
l[1] = l_[n];}
else if( rf->Id() == s1237 ) s988 = 3;
else if( rf->Id() == s1845 ) s988 = 4;
else if( rf->Id() == s2023 ) s988 = 5;
else
throw s970.s1002( L"misplaced query keyword: " + s959[rf->Id()] );}
else
l[s988++] = l_[n];}
s810 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1074 = l[2];
sqp->where = l[3];
sqp->s1869 = l[4];
sqp->s2059 = l[5];}
s791::s791( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l_, const s263* s701 )
: s591( s300, s592, s593, s565, s818, s701 ), s2040( s7::s1984, s300 ),
s733( s7::s462, s300 ), s783( new s272( s300, 0, s480 ) ),
s1861( NULL ){
TDException s970( s7::s1112, s934, s701 );
if( l_.size() < 3 )
throw s970.s1002( L"too few arguments." );
s591::s1244( ( vector<s271*>& )l_, s959 );
s628.s541( s733.s617(), s783.s15<s483*>() );
s582.push_back( s783.s15<s483*>() );
s274.push_back( s783.s15<s483*>() );
s630.push_back( s783.s15<s483*>() );
s631.push_back( s371( s733.s617(), s300) );
s485 p = l_[0];
if( p->s494() != s475 && p->s494() != s476 )
throw s970.s1002( L"the database object must be specified by a name or expression." );
if( l_[1]->s494() != s1065 )
throw s970.s1002( L"the second participant must be a query verb: SELECT, UPDATE, etc." );
s371* rf = (s371*)l_[1];
if( rf->Id() == s1233 )
s1725( l_, s970 );
else if( rf->Id() == s1758 )
s1726( l_, s970 );
else if( rf->Id() == s2022 )
s2004( l_, s970 );}
s791::~s791(){
if( s1861 )
delete s1861;}
s484* s791::s1807( const std::wstring& s ){
size_t pos = 0;
if( s1861 )
delete s1861;
s1861 = new s1781( s300, this, s, pos, s1781::s1815 );
return NULL;}
void s791::s1727( const s272* s1674, bool proc ){
s1713* sqp = qp.s15<s1713*>();
sqp->s1074->s500( this );
s813::Cont s1281;
wstring sv = sqp->s1074->s353();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + sv + L">";
s493 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );
TDException s970( s7::s922, s934, past );
s591::s500( s1674, proc );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s970.s1002( L"the database must be specified by a name or expression." );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what->s500( this );}
else if( pc == s475 )
sqp->what.s15<s371*>()->s500( this );
else if( pc == s474 || pc == s1065 )
(void)0;
else
throw s970.s1002( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s352() != Types.String )
throw s970.s1002( L"the 'WHERE' clause must be a string." );
sqp->where = s1807( sqp->where->to_wstring() );}
else {
std::vector<s271*> s880;
s880.push_back( s369 );
sqp->where = ( s484* ) new s838( s300, 0, 0, s880, NULL );
sqp->where.s15<Transd*>()->s500( s1674, false );}
if( sqp->s1869 ) {
pc = sqp->s1869->s494();
if( pc == s477 ) {
sqp->s1869 = s600( sqp->s1869.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1869.s15<Transd*>()->s500( s1674, false );
s835 s882;
sqp->s1869.s15<Transd*>()->s814( s882 );}
else
throw s970.s1002( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s874.s14() ) {
pc = sqp->s874->s494();
if( pc == s477 ) {
sqp->s874 = s600( sqp->s874.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s874->s500( this );}
else if( pc == s475 )
sqp->s874.s15<s371*>()->s500( this );
else if( sqp->s874->s352() != s1153 )
throw s970.s1002( L"the limit must be specified by a number, variable or expression." );}}
void s791::s1728( const s272* s1674, bool proc ){
s1723* sqp = qp.s15<s1723*>();
s493 = s1153;
TDException s970( s7::s922, s934, past );
s591::s500( s1674, proc );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s970.s1002( L"the database must be specified by a name or expression." );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what.s15<Transd*>()->s500( s1674, false );}
else
throw s970.s1002( L"the 'SET' clause must be a lambda" );
pc = sqp->s1869->s494();
if( pc == s477 ) {
sqp->s1869 = s600( sqp->s1869.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1869.s15<Transd*>()->s500( s1674, false );}
else
throw s970.s1002( L"the 'SATISFYING' clause must be a lambda." );}
void s791::s2006( const s272* s1674, bool proc ){
s1987* sqp = qp.s15<s1987*>();
/*s813::Cont s1281;
wstring sv = sqp->s1074->s353();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s353() + L"<" + sv + L">";
s493 = ((s316*)Types( s300, Types.Vector ))->s1197( ts, s1281 );*/
s493 = s1154; // sqp->s1074->s352();
TDException s970( s7::s922, s934, past );
s2040.s379( 0, s2039 );
s2040.s382( (s483*)this );
s591::s500( s1674, proc );
s472 pc = db->s494();
if( pc == s477 ) {
db = s600( db.s15<s561*>(), s300, s588, this, s298(), false );
db->s500( this );}
else if( pc == s475 )
db.s15<s371*>()->s500( this );
else
throw s970.s1002( L"the database must be specified by a name or expression." );
pc = sqp->what->s494();
if( pc == s477 ) {
sqp->what = s600( sqp->what.s15<s561*>(), s300, s588, this, s298(), false );
sqp->what->s500( this );}
else if( pc == s475 )
sqp->what.s15<s371*>()->s500( this );
else if( pc == s474 || pc == s1065 )
(void)0;
else
throw s970.s1002( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s352() != Types.String )
throw s970.s1002( L"the 'WHERE' clause must be a string." );
sqp->where = s1807( sqp->where->to_wstring() );}
else {
std::vector<s271*> s880;
s880.push_back( s369 );
sqp->where = ( s484* ) new s838( s300, 0, 0, s880, NULL );
sqp->where.s15<Transd*>()->s500( s1674, false );}
if( sqp->s1869 ) {
pc = sqp->s1869->s494();
if( pc == s477 ) {
sqp->s1869 = s600( sqp->s1869.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s1869.s15<Transd*>()->s500( s1674, false );
s835 s882;
sqp->s1869.s15<Transd*>()->s814( s882 );}
else
throw s970.s1002( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s2059 ) {
pc = sqp->s2059->s494();
if( pc == s477 ) {
sqp->s2059 = s600( sqp->s2059.s15<s561*>(), s300, s588, this, s298(), false );
sqp->s2059.s15<Transd*>()->s500( s1674, false );
s835 s882;
sqp->s2059.s15<Transd*>()->s814( s882 );}
else
throw s970.s1002( L"the 'USING' clause must be a lambda." );}}
void
s791::s500( const s272* s1674, bool proc ){
if( s810->verb == s744::s1778 )
s1727( s1674, proc );
else if( s810->verb == s744::s1779 )
s1728( s1674, proc );
else if( s810->verb == s744::s2061 )
s2006( s1674, proc );}
s486 s791::s1733( s483** s274, size_t s498 ){
s1723* sqp = qp.s15<s1723*>();
s486 s685 = s586;
vector<wstring> s896;
vector<wstring> s897;
s1783* base;
TDException s970( s7::s923, s931, past );
assert( db->s494() == s475 );
base = ( (s1783*)db.s15<s371*>()->s377() );
s1791 s1832;
s835 s882;
sqp->s1869.s15<Transd*>()->s814( s882 );
for( size_t n = 0; n < s882.size(); ++n ) {
s897.push_back( s882[n].first );
s1789 s1071;
base->select( s897.back(), s1780::s1858, s486(), s1071 );
s1832.insert( s1071 );}
s1784 *s1879, *s1878;
s1::s1291<s1784> dom = base->s1820();
s1879 = base->s1820();
s1878 = base->s1820();
auto it = begin( s1832 );
if( s1832.size() == 1 ) {
base->intersect( *it, dom );
dom->sort();}
for( ++it; it != end( s1832 ); ++it ) {
s1879->clear();
base->intersect( *it, s1879 );
s1879->sort();
if( dom->empty() )
dom->swap( s1879 );
else {
std::set_intersection( begin( dom->s320() ), end( dom->s320() ),
begin( s1879->s320() ), end( s1879->s320() ),
back_inserter( s1878->s320() ), s1804 );
dom->swap( s1878 );
s1878->clear();}}
s882.clear();
sqp->what.s15<Transd*>()->s814( s882 );
for( size_t n = 0; n < s882.size(); ++n ) {
s896.push_back( s882[n].first );}
vector<s485> s881, pls1;
s881.resize( s897.size() );
pls1.resize( s896.size() );
int s684 = 0;
dom->s1876();
while( dom->s1837() ) {
s1785* s1859 = dom->s1847();
for( size_t n = 0; n < s897.size(); ++n )
s881[n] = s1859->s760( s897[n] ).s15<s484*>();
sqp->s1869.s15<Transd*>()->s596( s881 );
s486 s153 = sqp->s1869->s497( 0, 0 );
if( s153.s14() && (bool)*s153 ) {
for( size_t n = 0; n < s896.size(); ++n )
pls1[n] = s1859->s760( s896[n] ).s15<s484*>();
sqp->what.s15<Transd*>()->s596( pls1 );
s486 s153 = sqp->what->s497( 0, 0 );
++s684;}}
*s586.s15<s346*>()->s357() = s684;
return s586;}
s486 s791::s1732( s483** s274, size_t s498 ){
s1713* sqp = qp.s15<s1713*>();
s1714* sqr = s810.s15<s1714*>();
s486 s685 = s586;
vector<wstring> s896;
vector<wstring> s1870;
s1783* base;
size_t s910 = string::npos;
TDException s970( s7::s923, s931, past );
assert( db->s494() == s475 );
base = ( (s1783*)db.s15<s371*>()->s377() );
if( sqp->s874.s14() ) {
if( sqp->s874->s494() == s475 ) {
sqr->s874 = ( int )*( (s346*)sqp->s874.s15<s371*>()->s377() );}
else if( sqp->s874->s494() == s476 ) {
sqr->s874 = (int)*sqp->s874->s497( 0, 0 );}
else
sqr->s874 = (int)*sqp->s874;}
if( sqp->s890.s14() ) {
if( sqp->s890->s494() == s475 ) {
sqr->s888 = sqp->s890.s15<s371*>()->s377()->to_wstring();}
else if( sqp->s890->s494() == s476 ) {
sqr->s888 = sqp->s890->s497( 0, 0 )->to_wstring();}
else
sqr->s888 = sqp->s890->to_wstring();}
s1788::iterator s1839, s1840;
s472 pc = sqp->what->s494();
s486 s1766 = sqp->what.s15<s483*>();
if( pc == s475 ) {
s489 rf = sqp->what.s15<s371*>();
s1766 = rf->s377();}
else if( pc == s1065 ) {
s489 rf = sqp->what.s15<s371*>();
if( rf->s617() == L"all" || rf->s617() == L"ALL" )
(void)0;
else
throw s970.s1002( L"fields for selection are not recognized" );}
else if( pc == s474 ) {
(void)0;}
s813 vt = s300->TR().s1015( s1766->s352() );
if( vt.s352() == s1721 || vt.s352() == s1720 ) {
const vector<s485>* v = NULL;
if( vt.s352() == s1721 )
v = &s1766.s15<s316*>()->s320();
else
v = &s1766.s15<s750*>()->s320();
for( auto it : *v ) {
wstring s858 = it->to_wstring();
size_t s883 = s4::s88.find( s858[0] );
if( s883 != string::npos )
s858 = s4::s52( s858, wstring( 1, s4::s88[s883] ) );
s896.push_back( s858 );}}
s1::s1291<s1784> dom = base->s1820();
if( s1861 ) {
s1861->select( base, dom );}
else
base->s1872( dom );
s835 s882;
if( sqp->s1869.s14() ) {
sqp->s1869.s15<Transd*>()->s814( s882 );
if( s882.empty() )
throw s970.s1002( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s882.size(); ++n ) {
s1870.push_back( s882[n].first );
while( s1839 != s1840 ) {
++s1839;}}}
vector<s485> s881;
s881.resize( s1870.size() );
s586.s15<s316*>()->clear();
dom->s1876();
while( dom->s1837() ) {
s1785* s1859 = dom->s1847();
s486 s1810;
if( sqp->s1869.s14() ) {
for( size_t n = 0; n < s1870.size(); ++n )
s881[n] = s1859->s760( s1870[n] ).s15<s484*>();
sqp->s1869.s15<Transd*>()->s596( s881 );
s1810 = sqp->s1869->s497( 0, 0 );}
else
s1810 = s369.s15<s483*>();
if( s1810.s14() && (bool)*s1810 ) {
s1::s9<s750> s895 = new s750( s300, NULL, L"" );
if( s896.empty() )
s1859->s863( *s895 );
else {
for( size_t n = 0; n < s896.size(); ++n )
s895->add( s1859->s760( s896[n] ).s15<s484*>() );}
s895->s1681( s7::s867 );
s586.s15<s316*>()->add( s895 );}}
if( sqr->distinct != -1 ) {
vector<s485>& s901 = s586.s15<s316*>()->s320();
for( size_t n = 0; n < s901.size(); ++n ) {
s485 s900 = s901[n];
size_t m = n + 1;
while( m < s901.size() ) {
s485 _el1 = s901[m];
if( *s900.s15<s750*>() == _el1.s15<s483*>() )
s901.erase( s901.begin() + m );
else
m++;}}}
if( sqr->s889 != -1 ) {
if( s896.size() && sqr->s888.size() ) {
auto it = std::find( s896.begin(), s896.end(), sqr->s888 );
if( it != s896.end() )
s910 = std::distance( s896.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s905;
dom->s1833( s905 );
auto it = std::find( s905.begin(), s905.end(), sqr->s888 );
if( it != s905.end() )
s910 = std::distance( s905.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s899> s903 = new s899;
s903->s909( s910 );
s840 s911( s903 );
s586.s15<s316*>()->sort( sqr->s889 == s1714::s831, &s911 );}
if( sqr->s874 != -1 ) {
s586.s15<s316*>()->s320().resize( sqr->s874 );}
return s685;}
s486 s791::s2009( s483** s274, size_t s498 ){
s1987* sqp = qp.s15<s1987*>();
vector<wstring> s896;
vector<wstring> s1870;
vector<s488> s2063;
s1783* base;
TDException s970( s7::s923, s931, past );
assert( db->s494() == s475 );
base = ( (s1783*)db.s15<s371*>()->s377() );
s1788::iterator s1839, s1840;
s472 pc = sqp->what->s494();
s486 s1766 = sqp->what.s15<s483*>();
if( pc == s475 ) {
s489 rf = sqp->what.s15<s371*>();
s1766 = rf->s377();}
else if( pc == s1065 ) {
s489 rf = sqp->what.s15<s371*>();
if( rf->s617() == L"all" || rf->s617() == L"ALL" )
(void)0;
else
throw s970.s1002( L"fields for selection are not recognized" );}
else if( pc == s474 ) {
(void)0;}
s813 vt = s300->TR().s1015( s1766->s352() );
if( vt.s352() == s1721 || vt.s352() == s1720 ) {
const vector<s485>* v = NULL;
if( vt.s352() == s1721 )
v = &s1766.s15<s316*>()->s320();
else
v = &s1766.s15<s750*>()->s320();
s2063.resize( v->size() );
for( size_t n = 0; n < v->size(); ++n ) {
wstring s858;
auto it = (*v)[n];
if( it->s494() == s475 ) {
if( it.s15<s371*>()->s381().s13() )
it->s500( this );
s858 = it.s15<s371*>()->s377()->to_wstring();}
else
s858 = it->to_wstring();
size_t s883 = s4::s88.find( s858[0] );
if( s883 != string::npos )
s858 = s4::s52( s858, wstring( 1, s4::s88[s883] ) );
if( s858[0] == L'(' ) {
vector<wstring> s80;
size_t pos = 0;
s263::s288( s858, pos, s80 );
if( s80.size() > 2 )
throw s970.s1002( L"too many arguments in field expression: " + s858 );
s486 s2013 = s300->TR().s518( base->s2017( s80[1] ), ns, s298() );
std::vector<s271*> pl = { s2013 };
s561 cs( s300, s80[0], pl, NULL );
auto s2057 = s591::s600( &cs, s300, ns, (s591*)this, s298(), false );
s2057->s500( this, false );
s2063[n] = s2057;
s896.push_back( s80[1] );}
else
s896.push_back( s858 );}}
s1::s1291<s1784> dom = base->s1820();
if( s1861 ) {
s1861->select( base, dom );}
else
base->s1872( dom );
s835 s882;
if( sqp->s1869.s14() ) {
sqp->s1869.s15<Transd*>()->s814( s882 );
if( s882.empty() )
throw s970.s1002( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s882.size(); ++n ) {
s1870.push_back( s882[n].first );
while( s1839 != s1840 ) {
++s1839;}}}
vector<s485> s2034, s2035;
s2034.resize( s1870.size() );
s835 s2060;
sqp->s2059.s15<s838*>()->s814( s2060 );
for( auto p: s2060 )
s2035.push_back( p.second->s335() );
if( s2035.size() != s896.size() )
throw s970.s1002( L"in the REDUCE query the number of selected fields doesn't match "
"the number of parameters to 'using' function");
dom->s1876();
while( dom->s1837() ) {
s1785* s1859 = dom->s1847();
s486 s1810;
if( sqp->s1869.s14() ) {
for( size_t n = 0; n < s1870.size(); ++n )
s2034[n] = s1859->s760( s1870[n] ).s15<s484*>();
sqp->s1869.s15<Transd*>()->s596( s2034 );
s1810 = sqp->s1869->s497( 0, 0 );}
else
s1810 = s369.s15<s483*>();
if( s1810.s14() && (bool)*s1810 ) {
if( s896.empty() )
s1859->s863( *s2039 );
else {
for( size_t n = 0; n < s896.size(); ++n ) {
if( s2063[n] ) {
vector<s485> s2033( { s1859->s760( s896[n] ).s15<s484*>() } );
s2063[n]->s596( s2033 );
s2035[n] = s2063[n]->s497( 0, 0 ).s15<s271*>();}
else
s2035[n] = s1859->s760( s896[n] ).s15<s271*>();}}
sqp->s2059.s15<Transd*>()->s596( s2035 );
sqp->s2059->s497( 0, 0 );}}
return s365; //s2039;
}
s486 s791::s497( s483** s691, size_t s697 ){
if( s810->verb == s744::s1778 )
return s1732( s691, s697 );
else if( s810->verb == s744::s1779 )
return s1733( s691, s697 );
else if( s810->verb == s744::s2061 )
return s2009( s691, s697 );
return NULL;}
bool
s791::s556( const wstring& s676, s371* ref, const wstring& s334, 
bool b ) const{
if( s676 == s7::s1984 ) {
ref->s1345( (s371*)&s2040 );
return true;}
return s591::s556( s676, ref, s334, b ); }
s271* s791::s598( size_t off ){
assert( off == 0 );
if( s2039 )
return s2039;
return (s271*) s2040.s503();}
s271* s791::s335()const{
return new s791( *this );}
s776::s776( s262* pass_, s272* s588, const wstring& s768, 
const vector<wstring>& s743, std::vector<s485>& types, const s1722& tbfr ){
s750 s781( pass_, s588, s768, NULL, tbfr );
s781.s500( s588, true );
vector<s485> s820 = s781.s320();
if( s820.size() > types.size() )
throw new s16( L"The number of record's fields is greater than the number of columns: " + s768 );
for( size_t n = 0; n < s743.size(); ++n ) {
s485 s811;
if( n < s820.size() ) {
if( !s820[n]->s501( types[n].s15< s483*>() ) ) {
if( tbfr.promInts && types[n]->s352() == s1152 && s820[n]->s352() == s1153 )
s820[n] = new s358( pass_, (double)*s820[n].s15<s346*>()->s357() );
else
throw new s16( L"The types of record's fields don't match to the types of columns: " + s768 );}
s811 = s820[n];}
else {
s811 = types[n].s15<s484*>()->s335();
s811->to_null();}
s762.insert( make_pair( s743[n], s811 ) );
size_t h = s811.s15<s483*>()->s322();
rechash = ( rechash << 1 ) ^ h;}}
size_t s776::s322() const{
return rechash;}
s486 s776::s760( s1907& s76, bool s714 ) const{
auto it = s762.find( s76 );
if( it == s762.end() ) {
if( s714 )
throw new s16( L"Record field doesn't exist: " + s76, 
(uint32_t)s16::s17::s23 );
else
return s486();}
return it->second.s15<s483*>();}
void s776::s863( s750& s153 ) const{
for( auto r: s762 )
s153.add( r.second );}
void s776::s863( s961& s153 ) const{
for( auto r: s762 )
s153.add( r.second );}
void s776::s545( std::vector<std::wstring>& s153 ) const{
for( auto r: s762 )
s153.push_back( r.first );}
bool s776::operator==( const s776* p ) const{
return rechash == p->rechash;}
bool s776::operator<( const s776* p ) const{
return rechash < p->rechash;}
wstring s776::to_wstring( uint32_t s1567 ) const{
wstringstream ss;
s304( &ss, 0 );
return ss.str();}
void s776::s304( std::wostream* pd, int s197/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"TSDRecord : " << endl;
for( auto it = begin( s762 ); it != end( s762 ); ++it ) {
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
s1798::s1798( s1783* pdb )
: s1784( pdb ), pind(NULL)//, fi1(s1850), se1(s1850)
{}
void s1798::s1873( void* f, void* s ){
pind = (s787*)f;}
void s1798::s1876(){
if( pind )
cur1 = pind->begin();
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1798::s1837(){
if( pind )
return cur1 != pind->end();
else
return cur != se;}
s1785* s1798::s1847(){
if( s1837() ) {
s1785* s685;
if( pind ) {
s685 = cur1->second;
cur1++;}
else {
s685 = *cur;
cur++;}
return s685;}
else
throw new s16( L"TSDBase row iterator is out of range" );}
s650::s650( s262* s300, s272* s588, const wstring& s77, const s263* ast_ )
: s1783( s300, s588, ast_ ){
s499 = s77;
s493 = Types.TSDBase;}
s650::s650( const s650& right, const s263* ast_ )
: s1783( right.s300, right.ns, ast_ ){
s493 = right.s493;}
s483* s650::s354( const s263& s701, s272* s588, s1907& s334 ) const{
return new s650( s300, s588, L"" );}
void s650::s500( const s272*, bool ){
s1264();}
void s650::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s650::s1238, s1800,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"add-file", new s337( L"add-file", &s650::s786, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"load-table", new s337( L"load-table", &s650::s802, s1154,
{ s1124( { Types.String, Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s348.insert( make_pair( L"select", new s337( L"select", &s650::s752, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"query", new s337( L"query", &s650::s770, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s650::s333, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s650::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"build-index", new s337( L"build-index", &s650::s856, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );}
s483* s650::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s650( s300, s588, L"" );}
inline bool
s650::s501( const s483* s502 ) const{
return ( ((s650*)s502)->s352() == s352() );}
s271* s650::s335() const{
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
inline void s650::s1238( s483** s274, size_t s498 ){
s650* ps = (s650*)DR;
s650* s685 = new s650( ps->s300, ps->ns, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s650::s786( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s650*)DR )->s654( s194 );}
inline void s650::s802( s483** s274, size_t s498 ){
s650* dr = ( (s650*)DR );
const wstring& s824 = PARN( 2 )->to_wstring();
s1722 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par_ = s274[n];
s472 pc = par_->s494();
if( pc == s1065 ) {
s485 par;
s489 rf;
rf = par_.s15<s371*>();
par = par_;
if( par->s352() == Types.No ) {
if( rf->Id() == s1755 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1753 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1751 ) {
if( s498 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1736 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1752 ) {
tbfr.s1699 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1844 ) {
tbfr.s1828 = true;}
else if( rf->Id() == s1754 ) {
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
s947 s1053( s194 );
s1053.read( s662, s7::s1108 );
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
void s650::s655( s1907& q ){
vector<wstring> qs;
s4::s57( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s651.begin(); it != s651.end(); ++it )
wcout << it->first;}}
void s650::select( s1907& field, s1780::s1793 op, const s483* s1067,
s1789& s153 ){
auto it = s871.find( field );
if( it == s871.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1780::s1853 ) {
s153.pr = it->second.equal_range( (s483*)s1067 );}
else if( op == s1780::s1856 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s483*)s1067 );}
else if( op == s1780::s1857 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s483*)s1067 );}
else if( op == s1780::s1854 ) {
s153.pr.first = it->second.upper_bound( (s483*)s1067 );
s153.pr.second = it->second.end();}
else if( op == s1780::s1857 ) {
s153.pr.first = it->second.lower_bound( (s483*)s1067 );
s153.pr.second = it->second.end();}
else {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}}
s1784* s650::s1820() const{
return new s1798( (s1783*)this );}
void s650::s1872( s1784* s153 ){
s153->s1873( (void*)&s757, (void*)NULL );}
void s650::intersect( const s1789& fi1, const s1789& fi2,
s1786& s153 ){
s1788::iterator it = fi1.pr.first;
wstring attr2 = fi2.s979;
s1787 s1817;
while( it != fi1.pr.second ) {
s486 attr2v = it->second->s760( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1817 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1817 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s650::intersect( const s1789& fi, s1784* s153 ){
s1788::iterator it = fi.pr.first;
s1786 s1879;
s1786& s1862 = ((s1798*)s153)->s320();
bool s1826 = s1862.empty();
while( it != fi.pr.second ) {
if( s1826 || std::binary_search( begin( s1862 ), end( s1862 ), it->second, s1804 ) )
s1879.push_back( it->second );
++it;}
s1862.swap( s1879 );}
void s650::s718( const wstring& s824, const s1722& tbfr ){
wstring s743 = tbfr.s1736;
vector<wstring> s815;
vector<wstring> s731;
vector<wstring> s805;
vector<wstring> s825;
if( s743.size() ) {
s4::s57( s743, tbfr.s1699, s815 );
s4::s57( s4::s52( s824, s48 ), tbfr.rowSep, s805 );}
else {
s743 = s824.substr( 0, s824.find( tbfr.rowSep ) );
s4::s57( s4::s52( s824.substr( s743.size() ), s48 ), tbfr.rowSep, s805 );
if( s743.back() == '\r' )
s743.pop_back();
s4::s57( s743, tbfr.s1699, s815 );}
vector<s485> types, s1774;
if( !s805.empty() ) {
s750 s781( s300, ns, s805[0], NULL, tbfr );
s781.s500( ns, true );
s1774 = s781.s320();}
for( size_t n = 0; n < s815.size(); ++n ) {
vector<wstring> s1735;
s4::s57( s815[n], L":", s1735 );
s949 s1773;
if( s1735.size() == 2 )
s1773 = new s263( s1735[1] + L"()", NULL );
else if( n < s1774.size() )
s1773 = new s263( s1774[n]->s353() + L"()", NULL );
else
s1773 = new s263( Types( s300, Types.String )->s353() + L"()", NULL );
s485 ptype = s300->TR().s518( *s1773, ns, ns->s298() );
types.push_back( ptype );
if( s1735[0][0] != L'@' )
s731.push_back( s1735[0] );
else {
size_t pl = s1735[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1735[0] );
wstring s76 = s1735[0].substr( pl + 1 );
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
s1788& s870 = s871.insert( make_pair( s858, s1788() ) ).first->second;
for( auto it: s757 ) {
s486 pd = it.second->s760( s858 );
if( pd.s14() )
s870.insert( make_pair( pd, it.second ) );}}
bool s650::s2012( s1907& s979 ) const{
assert(0);
return false;}
s1063 s650::s2017( s1907& s858 ) const{
assert( 0 );
return 0;}
wstring s650::to_wstring( uint32_t s1567 ) const{
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
s1786 s1848 = { new s1802( vector<s486>( {s486()} ), NULL ) };
s1786::iterator s1849 = s1848.begin();
s1802::s1802( const std::vector<s486>& v, s1803* s1809 )
: s1863( v ), s1860( s1809 ){}
s1802::~s1802(){
s1863.clear();}
const s1802::s1795& s1802::s2018() const{
return s1863;}
s486 s1802::s760( s1907& s76, bool s714 ) const{
return s1863[s1860->s1835( s76 )];}
void s1802::s863( s750& s153 ) const{
for( auto r : s1863 )
s153.add( r );}
void s1802::s863( s961& s153 ) const{
for( auto r : s1863 )
s153.add( r );}
void s1802::s545( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
size_t s1802::s322() const{
return rechash;}
s1801::s1801( const s1801& r )
: s1784( r.pdb ){}
s1801::s1801( s1783* pdb )
: s1784( pdb ){}
s1801::~s1801(){}
void s1801::s1873( void* f, void* s ){
fi = *( s1786::iterator* )f;
se = *( s1786::iterator* )s;}
void s1801::s1876(){
if( *fi != *s1849 )
cur = fi;
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1801::s1837(){
return (cur != se);}
s1785* s1801::s1847(){
if( s1837() ) {
s1785* s685 = *cur;
cur++;
return s685;}
else
throw new s16( L"Table row iterator is out of range" );}
void s1801::s1833( std::vector<std::wstring>& s153 ){
((s1803*)pdb)->s1834( s153 );}
s1803::s1803( s262* s300, s272* s588, const s263* ast_ )
: s1783( s300, s588, ast_ ){
s493 = Types.Table;
s2044 = 0;}
s1803::s1803( s262* s300, s272* s588, s1907& s77, const s263* ast_ )
: s1783( s300, s588, ast_ ){
s499 = s77;
s493 = Types.Table;
s2044 = 0;}
s1803::s1803( const s1803& right, const s263* ast_ )
: s1783( right.s300, right.ns, ast_ ){
s493 = right.s493;
s2044 = 0;}
s1803::~s1803(){
release();}
s483* 
s1803::s354( const s263& s701, s272* s588, s1907& s334 ) const{
return new s1803( s300, s588, &s701 );}
void s1803::s500( const s272*, bool ){
s1264();}
void s1803::s350(){
s348.insert( make_pair( L"new", new s337( L"new", &s1803::s1238, s1799,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"load-table", new s337( L"load-table", &s1803::s802, s1154,
{ s1124( { Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls", L":firstRowColNames"} ) ) );
s348.insert( make_pair( L"select", new s337( L"select", &s1803::s752, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"query", new s337( L"query", &s1803::s770, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.insert( make_pair( L"erase", new s337( L"erase", &s1803::s333, s1154,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"size", new s337( L"size", &s1803::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"get-row", new s337( L"get-row", &s1803::s2020, 0,
{ s1124( { s1514::s1551 } ) }, 0, 0 ) ) );
s348.insert( make_pair( L"num-cols", new s337( L"num-cols", &s1803::s2028, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"num-rows", new s337( L"num-rows", &s1803::s2029, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( make_pair( L"build-index", new s337( L"build-index", &s1803::s856, s1154,
{ s1124( { Types.String } ) }, 1, 1 ) ) );
s348.equal_range( L"get-row" ).first->second->s1263( true );}
s1063 s1803::s1190( const wstring& s1555, const vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"get-row" )
s685 = s1720;
else
return s336::s1190( s1555, l );
return s685;}
s483* s1803::s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1803( s300, s588, L"" );}
inline bool
s1803::s501( const s483* s502 ) const{
return ( ((s1803*)s502)->s352() == s352() );}
s271* s1803::s335() const{
return new s1803( *this );}
void s1803::s356( s271* p ) const{
p = new s1803( *this );}
size_t s1803::s322() const{
return (size_t)this;}
bool s1803::operator==( const s483* p ) const{
return ( this == p );}
bool s1803::operator<( const s483* p ) const{
return false;}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
#undef s698
#define s698 ((s1803*)(s484*)*s274)
inline void s1803::s1238( s483** s274, size_t s498 ){
s1803* ps = (s1803*)DR;
s1803* s685 = new s1803( ps->s300, ps->ns, ps->s603() );
s685->s500( ps->ns, true );
*s274 = (s483*)s685;}
inline void s1803::s802( s483** s274, size_t s498 ){
s1803* dr = ( (s1803*)DR );
const wstring& s824 = ((s359*)PARN( 2 ))->s320();
s1722 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s498 ) {
s485 par = s274[n];
s472 pc = par->s494();
if( pc == s1065 ) {
s489 rf = par.s15<s371*>();
if( par->s352() == Types.No ) {
if( rf->Id() == s1755 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1753 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1751 ) {
if( s498 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1736 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1752 ) {
tbfr.s1699 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1844 ) {
tbfr.s1828 = true;}
else if( rf->Id() == s1754 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2021 ) {
tbfr.s2016 = true;}}}
else
throw new s16( L"Table::(load-table): unknown parameters" );
++n;}
dr->s718( s824, tbfr );}
inline void s1803::s752( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1803*)DR )->s655( s194 );}
inline void s1803::s770( s483** s274, size_t s498 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1803*)DR )->s655( s194 );}
inline void s1803::s333( s483** s274, size_t s498 ){}
inline void s1803::s2020( s483** s274, size_t s498 ){
s1803* pt = (s1803*)DR;
int n = (int)*PARN( 2 );
const s1802::s1795& row = pt->s2062[n].s15<s1802*>()->s2018();
vector<s271*> v;
for( auto f : row )
v.push_back( f->s335() );
*s274 = new s961( pt->s300, v, NULL );
( *s274 )->s500( pt->ns );}
inline void s1803::s328( s483** s274, size_t s498 ){}
inline void s1803::s2028( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s1803*)DR )->s806.size();}
inline void s1803::s2029( s483** s274, size_t s498 ){
*( (s346*)*s274 )->s357() = (int)( (s1803*)DR )->rows.size();}
inline void s1803::s856( s483** s274, size_t s498 ){
wstring s858 = PARN( 2 )->to_wstring();
((s1803*)DR)->s855( s858 );}
void s1803::select( const std::wstring& field, s1780::s1793 op, const s483* s1067,
s1789& s153 ){
auto it = s871.find( field );
if( it == s871.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1780::s1853 ) {
s153.pr = it->second.equal_range( (s483*)s1067 );}
else if( op == s1780::s1856 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s483*)s1067 );}
else if( op == s1780::s1857 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s483*)s1067 );}
else if( op == s1780::s1854 ) {
s153.pr.first = it->second.upper_bound( (s483*)s1067 );
s153.pr.second = it->second.end();}
else if( op == s1780::s1857 ) {
s153.pr.first = it->second.lower_bound( (s483*)s1067 );
s153.pr.second = it->second.end();}
else {
assert( 0 );
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}
s153.s979 = field;
s153.dist = std::distance( s153.pr.first, s153.pr.second );}
void s1803::intersect( const s1789& fi1, const s1789& fi2,
s1786& s153 ){
s1788::iterator it = fi1.pr.first;
wstring attr2 = fi2.s979;
s1787 s1817;
while( it != fi1.pr.second ) {
s486 attr2v = it->second->s760( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1817 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1817 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s1803::intersect( const s1789& fi, s1784* s153 ){
s1788::iterator it = fi.pr.first;
s1786 s1879;
s1786& s1862 = ((s1801*)s153)->s320();
bool s1826 = s1862.empty();
while( it != fi.pr.second ) {
if( s1826 || std::binary_search( begin( s1862 ), end( s1862 ), it->second, s1804 ) )
s1879.push_back( it->second );
++it;}
s1862.swap( s1879 );}
void s1803::s1872( s1784* s153 ){
s1786::iterator f = begin( rows );
s1786::iterator s = end( rows );
s153->s1873( (void*)&f, (void*)&s );}
size_t s2003( const std::wstring& s824, const s1722& tbfr ){
size_t s685 = 0, st = 0, en = 0, n;
while( en != string::npos ) {
en = s824.find( tbfr.rowSep, st );
n = s4::count( s824, tbfr.s1699, st, en, true );
if( s685 < n ) s685 = n;
st = en + 1;}
return s685;}
void s1803::s718( s1907& s824, const s1722& tbfr ){
wstring s743 = tbfr.s1736;
vector<wstring> s815;
vector<wstring> s825;
size_t pl = 0;
if( s743.size() ) {
s4::s57( s743, tbfr.s1699, s815 );}
else if( tbfr.s2016 ){
pl = s824.find( tbfr.rowSep );
s743 = s824.substr( 0, pl );
if( s743.back() == '\r' )
s743.pop_back();
s4::s57( s743, tbfr.s1699, s815 );
++pl;}
else {
size_t s2024 = s2003( s824, tbfr );
for( size_t n = 0; n < s2024; ++n )
s815.push_back( std::to_wstring( n ) );}
vector<s486> types;
vector<s485> s1774;
if( 0 /*|| !s805.empty()*/ ) {
++pl;
wstring first = s824.substr( pl, s824.find( tbfr.rowSep, pl ) - pl );
s750 s781( s300, ns, first, NULL, tbfr );
s781.s500( ns, true );
s1774 = s781.s320();}
for( size_t n = 0; n < s815.size(); ++n ) {
vector<wstring> s1735;
s4::s57( s815[n], L":", s1735 );
s949 s1773;
s486 ptype;
if( s1735.size() == 2 )
s1773 = new s263( s1735[1] + L"()", NULL );
else
s1773 = new s263( Types( s300, Types.String )->s353() + L"()", NULL );
ptype = s300->TR().s518( *s1773, ns, ns->s298() );
types.push_back( ptype );
if( s1735[0][0] != L'@' )
s806.push_back( s1735[0] );
else {
size_t pl = s1735[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1735[0] );
wstring s76 = s1735[0].substr( pl + 1 );
s806.push_back( s76 );}
s1836[s806.back()] = s806.size() - 1;}
s813::Cont s1281;
wstring ts = Types( s300, Types.Tuple )->s353() + L"<"; 
for( size_t n = 0; n < types.size(); ++n ) {
ts += types[n]->s353();
if( n < types.size() - 1 )
ts += L" ";}
ts += L">";
s2044 = ( (s961*)Types( s300, Types.Tuple ) )->s1197( ts, s1281 );
using namespace chrono;
size_t s1821 = pl, /*s69,*/ s1866, s1822, s1829;
vector<s486> s1831( types.size() );
s949 s208 = new s263( L"", L"" );
rows.clear();
s2062.clear();
while( s1821 != string::npos ) {
s1866 = s1821;
s4::s1003( s824, s1866, tbfr.rowSep );
wstring s1824 = s824.substr( s1821, s1866 - s1821 );
s1829 = s1822 = 0;
for( size_t n = 0; n < types.size(); ++n ) {
s1829 = s1822;
s4::s1003( s1824, s1829, tbfr.s1699 );
if( types[n].s14() ) {
s208->s294( L"" );
s208->s1770( s1824.substr( s1822, s1829 - s1822 ) );
if( types[n]->s352() == Types.String && ( s208->s291().front() != L'"' ||
s208->s291().back() != L'"' ) ) {
wstring dqu = L"\"\"";
s208->s1770( dqu.insert( 1, s4::s1830(  s4::s52( s208->s291(), s4::s48 ) , L'"' )));}
s1831[n] = types[n]->s354( *s208, ns, ns->s298() );}
else {
s1831[n] = s365.s15<s483*>();}
s1822 = s1829 + 1;
if( s1829 == string::npos )
break;}
s1821 = s1866 + 1;
s1785* s1811 = new s1802( s1831, this );
rows.push_back( s1811 );
if( s1866 == string::npos || s1821 == s824.size() )
break;}
s2062.assign( rows.begin(), rows.end() );}
void s1803::s855( s1907& s858 ){
auto it = s871.find( s858 );
if( it != end( s871 ) )
s871.erase( it );
s1788& s870 = s871.insert( make_pair( s858, s1788() ) ).first->second;
for( auto it: rows ) {
s486 pd = it->s760( s858 );
if( pd.s14() )
s870.insert( make_pair( pd, it ) );}}
bool s1803::s2012( s1907& s979 ) const{
if( s1836.find( s979 ) != end( s1836 ) )
return true;
return false;}
s1063 s1803::s2017( s1907& s858 ) const{
if( !s2044 )
throw new s16( L"table is empty" );
const s813& s994 = s300->TR().s1015( s2044 );
s1063 s2045 = s994.s352( (1 + s1835( s858 )) * 2 );
return s2045;}
void s1803::release(){
s1783::release();
rows.clear();}
s1784* s1803::s1820() const{
return new s1801( (s1783*)this );}
size_t s1803::s1835( s1907& s1818 ) const{
auto s685 = s1836.find( s1818 );
if( s685 == s1836.end() )
throw new s16( L"table field does not exist: " + s1818 );
return s685->second;}
wstring s1803::to_wstring( uint32_t s1567 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s1803::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Table : " << endl;
for( auto it = begin( rows ); it != end( rows ); ++it ) {}}
vector<wstring> s1374 /*= { L"", s1429, s243, s1430, 
s258, s256, 
s902, s260, s230, s772, 
s821, s252, s244, s852,
s261, s759, s251, s259, 
s257, s818, s1319, s255, 
s233 }*/;
vector<int> BIFuncs1v = {	0, 
0, 0, s1433, s1434, 0, 
0, s1436, s1437, 0, 0, 
0,	s1440, s1625, 0, 0, 0,
s1443, 0, 0, 0, s1445, 
s1889, s1627, 0, 0, 0, 
0, 0, s1448, s1449,	0, 
0, s1451, s1452
};
std::map<std::wstring, int> s1373;
s1989::s1989(){
reset();}
vector<wstring> s1989::s2051;
void s1989::reset(){
memset( s2043, 0, s1986 * sizeof( s2001 ) );
if( s2051.empty() )
s2051 = { s7::s1996, s7::s1999, s7::s1998,
s7::s1997 };}
s2001 s1989::s2005( const wstring& s2041 ){
auto it = std::find( begin(s2051), end(s2051), s2041 );
size_t n = std::distance( begin(s2051), it );
if( n == string::npos )
throw new s16( L"unrecognized restriction switch: " + s2041 );
return (s2001)n;}
void s1989::s2058( const s143& s133 ){
for( size_t n = 0; n < s1986; ++n )
if( s2043[n] )
throw new s16( L"Assembly security restrictions have already been set" );
vector<pair<wstring, s142>> s144;
s133.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].first == s7::s1991 )
s2043[s2052] = s2005( s144[n].second->s169() );
else if( s144[n].first == s7::s1992 )
s2043[s2053] = s2005( s144[n].second->s169() );
else if( s144[n].first == s7::s1993 )
s2043[s2054] = s2005( s144[n].second->s169() );
else if( s144[n].first == s7::s1994 )
s2043[s2055] = s2005( s144[n].second->s169() );
else if( s144[n].first == s7::s1990 ) {
s2043[s2052] = s2005( s144[n].second->s169() );
s2043[s2053] = s2005( s144[n].second->s169() );}
else if( s144[n].first == s7::s1995 ) {
for( size_t n = 1; n < s1986; ++n )
s2043[n] = s2005( s144[n].second->s169() );}}}
void s1989::s2015( const std::vector<s2000>* s2036, s2001 sw ) const{
for( size_t n = 0; n < s2036->size(); ++n ) {
s2000 si = (*s2036)[n];
if( s2043[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );}}
bool s1989::s2014( s2000 si, s2001 sw ) const{
if( s2043[si] == s2050 )
return true;
if( s2043[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );
return false;}
s262::s262()
: s272( this, 0, s473 ), s701( s227, L"", L"global" ),
s200( L"" ), s203( this ), s1321( false ){}
s262::~s262(){}
void s262::reset(){
s628.reset();
s203.s790();
s199.clear();
s701.reset();
s1321 = false;
s2042.reset();}
void s262::s1902( bool soft /*=false*/ )
{
s336::s784( this, soft );
s203.s290();
s206[s7::s434] = s367.s15<s483*>();
s206[s7::s433] = s368.s15<s483*>();
s851( s7::s436, s369.s15<s483*>() );
s851( s7::s437, s370.s15<s483*>() );
s851( s7::s832, s365.s15<s483*>() );
s1407 = new s1406( this, this );
s1405 = new s1404( this, this );
s851( s7::s1393, s1405.s15<s483*>() );
s851( s7::s1394, s1407.s15<s483*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s359* s1475 = new s359( this, os, this );
s851( s7::s1375, s1475 );
if( s1373.empty() ) {
s1374 = { L"", 
s1429, s243, s1430, s258, s1616, 
s256, s902, s260, s230, s772,
s821, s252, s1617, s244,s1946,
s1618, 
s852,s261, s1620, s1621, s759, 
s1888, s1619, s1947, s1945, s251, 
s1564,s259, s257, s818, s1622, 
s1319, s255, s233 };
for( size_t n = 1; n < s1374.size(); ++n )
s1373[s1374[n]] = (int)n;}}
static s6::s1697 s1772( L".", L",", true, true, true );
void s262::s202( const std::wstring& s657, s722& s153 ) {
vector<s9<s143>> s662;
s950 s1053 = new s947( s657, true, s1772 );
s1053->read( s662, s7::s418 );
for( size_t n = 0; n < s662.size(); n++ ) {
wstring s658 = s263::s302( *s662[n], s7::s465 );
if( s658 == s7::s453 ) {
if( ( *s662[n] ).s156( s7::s467 ) ) {
const vector<s142>& s162 = ( *s662[n] ).s158( s7::s467 )->s167();
for( size_t n = 0; n < s162.size(); n++ )
s153.s663.push_back( s162[n]->s169() );}
if( ( *s662[n] ).s156( s7::s466 ) )
s153.entry = ( *s662[n] ).s158( s7::s466 )->s857();
if( ( *s662[n] ).s156( s7::s1985 ) ) {
const s143& s133 = (*s662[n]).s158( s7::s1985 )->s166();
s2042.s2058( s133 );}}}
if( s153.s663.empty() )
s153.s663.push_back( s657 );}
wstring s717( const wstring& s753, const wstring& s756 ){
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
void s262::s213( const std::wstring& s194, const s143& obj ){
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
s272* ob = new s272( *it->second, s300, pc, s300, am, cl, cnl, al );
s659.s541( ob->s299(), ob );}}
void s262::s209( const wstring& s661, bool s1904 ){
s722 s646;
s263* s208 = new s263();
wstring s189 = s4::s746( s661 );
if( !s3::s724( s189 )) {
wstring s1899;
if( s1904 ) {
if( s1900.empty() )
throw new s16( L"can't find the file: " + s661 );
s1899 = s1900;}
else
s1899 = s767;
s4::s61( s1899 );
wstring file = s189.substr( s189.rfind( L"/" ) + 1 );
s189 = s717( s1899, s189.substr(0, s189.rfind( L"/" ) + 1 )) + file;
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
s950 s1053 = new s947( s199[n], true, s1772 );
s1053->read( s662, s7::s418 );
for( size_t m = 0; m < s662.size(); m++ ) {
if( s263::s302( *s662[m], s7::s465 ) == s7::s456 )
s213( s199[n], *s662[m] );
else if( s263::s295( *s662[m], s7::s454 ) == s7::s454 ) {
s662[m]->s159( s7::s1126, new s6::s141( L"\"" 
+ s199[n] + 
L"\"" 
), s143::s145::s147 );
s208->s289( *s662[m] );}}}
s207( *s208 );
if( s1016.s936() )
throw s937( s937::s17::s1001 );
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
size_t s668 = s665.size();
while( s667.size() < s668 ) {
size_t s669 = s665.size();
for( size_t n = 0; n < s665.size(); ++n ) {
if( s665[n].second.empty() ||
std::find( s667.begin(), s667.end(), s665[n].second )
!= s667.end() ) {
s667.push_back( s665[n].first );
s665.erase( s665.begin() + n-- );
continue;}}
if( s669 == s665.size() )
throw new s16( L"unresolved parent class: " + s665[0].second );}
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
s208.s289( obj );
s207( s208 );}
void s262::s1652( const std::wstring& s671 ){
s483* pd = s628.get( s671 );
if( pd->s494() == s479 )
((s272*)pd)->s1651();}
s483* s262::run( const vector<wstring>& s691 ){
if( s200.empty() )
s200 = s7::s459 + L"::" + s7::s458;
if( !s691.empty() ) {
wstring  s672, s671;
s670( s200, s671, s672 );
s272* mod = (s272*)s628.get( s671 );
s813::Cont s1281;
wstring ts = Types( this, Types.Vector )->s353() + L"<" + Types( this, Types.String )->s353() + L">";
s1063 pt = ((s316*)Types( this, Types.Vector ))->s1197( ts, s1281 );
s316* s913 = (s316*) s300->TR().s1009( pt )->s355( this, vector<s484*>( {} ) );
for( size_t n = 0; n < s691.size(); ++n ) {
s913->add( new s359( this, s691[n], this ) );}
mod->s851( s7::s1574, s913 );
mod->s851( s7::s829, new s346( this, (int)s691.size() ) );}
vector<wstring> l;
return callFunc( s200, l );}
s483* s262::callFunc( const wstring& s, vector<wstring>& l ){
wstring  s672, s671;
s670( s, s671, s672 );
s272* mod = (s272*)s628.get( s671 );
s488 s673 = (s591*)mod->s641( s672, L"::" );
vector<s485> s274;
for( size_t n = 0; n < l.size(); n++ ) {
s949 ast_ = new s263( l[n], NULL );
s490 cs = s591::s1121( *ast_, this, mod, mod->s298() );
s274.push_back( cs );}
s673->s596( s274 );
s484* pr = s673->s496();
try {
s1321 = false;
if( !pr )
s673->s500( this, true );
else
s673->s597( this );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s673->s299() + L"' function " );}
s1321 = true;
mod->s1651();
s483* s685 = s673->s497();
if( s685->s618() == s7::s440 )
throw new s16( ( (s361*)s685 )->Msg() );
s1321 = false;
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
s950 s1053 = new s947( s189 );
s1053->read( s662, s7::s418 );
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
s950 s1053 = new s947( s664 );
s1053->read( s662, s7::s418 );
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
void s262::s2015( const std::vector<s2000>* s2036, s2001 sw ) const{
s2042.s2015( s2036, sw );}
bool s262::s2014( s2000 si, s2001 sw ) const{
return s2042.s2014( si, sw );}
s1063 s262::s218( s483* p, const wstring& s347 ){
return s203.s218( p, s347 );}
bool s262::s556( const wstring& sym_, s371* ref, const wstring& s334, bool fr ) const{
if( !s272::s556( sym_, ref, s334, fr ) ) {
if( sym_ == s7::s1574 ) {
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
void s262::s219( const wstring& s76, const wstring& s334,
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
s591* s262::s214( int s1459, 
std::vector<s271*>& s705, s272* s588, s591* s215, const s263* s701 ){
s591* s685 = NULL;
if( s1459 == s1438 )
s685 = new s608( this, s588, s215, s705, s701 );
else if( s1459 == s1452 )
s685 = new s605( this, s588, s215, s705, s701 );
else if( s1459 == s1627 )
s685 = new s1609( this, s588, s215, s705, s701 );
else if( s1459 == s1432 )
s685 = new s607( this, s588, s215, s705, s701 );
else if( s1459 == s1433 )
s685 = new s1409( this, s588, s215, s705, s701 );
else if( s1459 == s1949 )
s685 = new s1941( this, s588, s215, s705, s701 );
else if( s1459 == s1451 )
s685 = new s305( this, s588, s215, s705, s701 );
else if( s1459 == s1442 )
s685 = new s606( this, s588, s215, s705, s701 );
else if( s1459 == s1950 || s1459 == s1948)
s685 = new s1942( this, s588, s215, s705, s701 );
else if( s1459 == s1446 || s1459 == s1565)
s685 = new s609( this, s588, s215, s705, s701 );
else if( s1459 == s1435 )
s685 = new s610( this, s588, s215, s705, s701 );
else if( s1459 == s1440 )
s685 = new s838( this, s588, s215, s705, s701 );
else if( s1459 == s1443 )
s685 = new s839( this, s588, s215, s705, s701 );
else if( s1459 == s1448 )
s685 = new s612( this, s588, s215, s705, s701 );
else if( s1459 == s1447 )
s685 = new s611( this, s588, s215, s705, s701 );
else if( s1459 == s1434 )
s685 = new s613( this, s588, s215, s705, s701 );
else if( s1459 == s1437 )
s685 = new s614( this, s588, s215, s705, s701 );
else if( s1459 == s1444 )
s685 = new s615( this, s588, s215, s705, s701 );
else if( s1459 == s1441 )
s685 = new s797( this, s588, s215, s705, s701 );
else if( s1459 == s1439 )
s685 = new s775( this, s588, s215, s705, s701 );
else if( s1459 == s1450 )
s685 = new s1309( this, s588, s215, s705, s701 );
else if( s1459 == s1630 )
s685 = new s1612( this, s588, s215, s705, s701 );
else if( s1459 == s1449 )
s685 = new s791( this, s588, s215, s705, s701 );
else if( s1459 == s1626 )
s685 = new s1607( this, s588, s215, s705, s701 );
else if( s1459 == s1628 )
s685 = new s1610( this, s588, s215, s705, s701 );
else if( s1459 == s1625 )
s685 = new s1606( this, s588, s215, s705, s701 );
else if( s1459 == s1445 ) {
s685 = new s817( this, s588, s215, s705, s701 );}
else if( s1459 == s1629 )
s685 = new s1611( this, s588, s215, s705, s701 );
else if( s1459 == s1436 )
s685 = new s898( this, s588, s215, s705, s701 );
else if( s1459 == s1624 )
s685 = new s1605( this, s588, s215, s705, s701 );
else if( s1459 == s1889 )
s685 = new s1887( this, s588, s215, s705, s701 );
return s685;}
s271*
s262::s222( const wstring& s76, const wstring& s499, bool s520 /*= true*/ )
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
void* s262::s223( const std::wstring& s278 ){
s336* s685;
s272* exp = (s272*) s628.get( s7::s455, false );
if( exp )
s685 = (s336*)exp->s641( s278, L"", true );
else
throw new s16( L"no such export variable: " + s278 );
void * pv = s685->addr();
return pv;}
void s262::s1353( const wstring& s671 ){
s203.s1880( s671 );
s628.s542( s671 );
if( s203.s156( s671) )
s203.s1668( s671 );}
void s262::s1667( const wstring& s1635 ){
vector<wstring> s1645;
for( auto it = s628.Table().begin(); it != s628.Table().end(); ++it ) {
s271* p = it->second.s15<s271*>();
if( p->s494() == s479 || p->s494() == s478 ) {
wstring s189 = ( (s272*)p )->s641( s7::s1126, 
L":::" )->to_wstring();
if( s189 == s1635 )
s1645.push_back( it->first );}}
for( auto mod : s1645 )
s1353( mod );
for( size_t n = 0; n < s199.size(); ++n ) {
if( s199[n] == s1635 ) {
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
p->s1902( false );
return s684;}
void deleteAssembly( int n ){
auto it = handles.find( n );
if( it == end( handles ) )
throw new s2::s16( L"no assembly with such handle" );
handles.erase( it );}
void loadProgram( HPROG handle, const wstring& s189 ){
s262* p = handles[handle];
p->s1893( s3::s1886() );
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
void importSymbol( HPROG handle, const std::wstring& s1114, const std::wstring& symName,
const std::wstring& s334 ){
s262* p = handles[handle];
s272* ob = (s272*)p->s641( s1114, s334 );
ob->s555( symName, s334 );}
void importFile( HPROG handle, const std::wstring& s1114, const std::wstring& s44,
const std::wstring& s334 ){
vector<s1::s9<s6::s143>> s662;
s6::s947 s1053( s44 );
s1053.read( s662, s7::s418 );
s262* p = handles[handle];
p->s209( s44 );
s272* ob = (s272*)p->s641( s1114, s334 );
for( size_t n = 0; n < s662.size(); n++ ) {
wstring s658 = s263::s302( *s662[n], s7::s465 );
ob->s555( s658, s334 );}}
HPROG initShell( const std::wstring& s1114, const std::wstring& modText ){
s1::s9<s6::s143> ob = new s6::s143(NULL);
size_t pos = 0;
s6::s1697 s1772( L".", L",", true, true, true );
s6::s947 s1053( L"", true, s1772 );
s1053.s170( modText, pos, ob );
ob->s159( s7::s465, new s6::s141( s1114 ) );
HPROG prog = createAssembly();
s211( prog, *ob );
return prog;}
} // namespace transd
