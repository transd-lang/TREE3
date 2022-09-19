
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
std::vector<std::wstring> s989 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1112(){
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
wstring s681 = s37();
size_t pl = s681.rfind( '/' );
if( pl == string::npos )
s681 = L"";
else
s681 = s681.substr( 0, pl );
return s681;}
wstring s1869(){
char buf[2000];
memset( buf, 0, 2000 );
getcwd( buf, 2000 );
return wstring( conv.from_bytes( buf ) );}
bool s31( const wstring& s46, const wstring& s522, wstring& s153 ){
struct dirent *entry;
DIR *dp;
wregex rg( s522 );
bool s681 = false;
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s690 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s690,
(uint32_t)s16::s17::s22 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s153 = s46 + conv.from_bytes( entry->d_name );
s681 = true;
break;}}
closedir( dp );
return s681;}
void s32( const wstring& s46, const wstring& s522, vector<wstring>& s40, vector<wstring>& s41 ){
struct dirent *entry;
DIR *dp;
wregex rg( s522 );
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s690 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s690,
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
bool s718( const std::wstring& f ){
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
wstring s1869(){
wchar_t buf[2000];
memset( buf, 0, 4000 );
_wgetcwd( buf, 2000 );
return wstring( buf );}
bool s31( const wstring& _dir, const wstring& s522, wstring& s153 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s522.c_str() );
bool s681 = false;
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
s681 = true;
break;}}
return s681;}
void s32( const wstring& _dir, const wstring& s522, vector<wstring>& s40, vector<wstring>& s41 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s522.c_str() );
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
bool s718( const std::wstring& f ){
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
size_t& start, size_t& end, bool s880/*=false*/ )
{
end = string::npos;
start = string::npos;
int s66 = 0;
wchar_t s870 = 0;
bool esc = false;
for( size_t n = s65; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s870 || !s880 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s66++;}
else if( c == right ) {
if( start == string::npos )
return; // s824
if( --s66 == 0 ) {
end = n;
return;}}
else if( s880 && ( c == L'\'' || c == L'\"' ) ) {
s870 = c;}}
else if( s870 && c == s870 && !esc ) {
s870 = 0;}
else if( c == L'\\' ) {
esc = !esc;}
else
esc = false;}}
void s856( const wstring& s, size_t s65, wchar_t left, wchar_t right,
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
bool s848 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s848 = !s848;
if( s[n] == c && !s848 ) {
end = n;
return;}
if( s[n] != L'\\' )
s848 = false;}}
void s994( const std::wstring& s, size_t& s65, const std::wstring& s1867 ){
size_t s1865 = s65, s1866;
wstring s1332 = s1867 + L"\"";
s65 = string::npos;
bool s1868 = false;
while( true ) {
s1866 = s1865;
s1865 = s.find_first_of( s1332, s1865 );
if( s1865 == string::npos ) {
if( s1868 )
throw new s2::s16( L"no closing quote: " + s.substr(s1866, 20) );
return;}
if( s[s1865] == L'\"' ) {
if( ! (s1865 && s[s1865-1] == '\\' ))
s1868 = !s1868;}
else{
if( !s1868 ) {
s65 = s1865;
return;}}
++s1865;}
return;
size_t pl = s.find_first_of( s1332, s65 );
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
pl = s.find_first_of( s1332, pl );}
else {
s65 = pl;
return;}}}
void s1317( const std::wstring& s, size_t& s65, const std::wstring& s1083 ){
size_t pl = s.find( s1083, s65 );
if( pl == s65 )
return;
size_t start = s65;
s65 = string::npos;
while( pl < s.size() ) {
if( s1083.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1083.size();
if( pl < s.size() )
pl = s.find( s1083, pl );}
else {
s65 = pl;
return;}}}
size_t count( const std::wstring& s77, const std::wstring& s1083, size_t start, size_t end,
bool s880 ){
size_t s681 = 0;
size_t pl = s77.find( s1083, start );
while( pl < s77.size() && pl <= end) {
if( s880 && pl && s77[pl-1] == '\\' ) {
++pl;}
else {
++s681;
pl += s1083.size();}
if( pl < s77.size() - 1 ) 
pl = s77.find( s1083, pl );}
return s681;}
int s56( const wstring& s77, wchar_t s72, size_t& pos ){
size_t s70 = s77.find( s72, pos );
if( s70 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s52( s77.substr( pos, s70 - pos ), L" " );
int s681 = stoi( s );
pos = s77.find_first_not_of( s48 + s72, s70 );
return s681;}
bool s62( const wchar_t *str, long *s347, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s681 = true;
errno = 0;
try {
*s347 = std::wcstol( str, &s67, 0 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string to number: " + U16( e.what() ));}
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s347 == LONG_MIN || *s347 == LONG_MAX ) && errno == ERANGE ) )
s681 = false;
if( end )
*end = s67;
return s681;}
bool s1533( const wchar_t *str, long long *s347, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s681 = true;
errno = 0;
*s347 = std::wcstoll( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s347 == LLONG_MIN || *s347 == LLONG_MAX ) && errno == ERANGE ) )
s681 = false;
if( end )
*end = s67;
return s681;}
bool s1534( const wchar_t *str, unsigned long long *s347, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s681 = true;
errno = 0;
*s347 = std::wcstoull( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s347 == ULLONG_MAX ) && errno == ERANGE ) )
s681 = false;
if( end )
*end = s67;
return s681;}
bool s63( const wchar_t *str, double *s347, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s681 = true;
errno = 0;
*s347 = std::wcstod( str, &s67 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s347 == HUGE_VAL || *s347 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s681 = false;
if( end )
*end = s67;
return s681;}
void s871( const wstring& s77, vector<wstring>& s153 ){
size_t s68 = s77.find_first_not_of( s48 );
size_t s677, s678;
while( s68 != string::npos ) {
wchar_t c = s77[s68];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s55( s77, s68, c, s677, s678 );
if( s678 == string::npos )
throw s2::s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
arg = s77.substr( s68, s678 - s68 + 1 );
s68 = s77.find_first_not_of( s48, ++s678 );}
else {
s678 = s77.find_first_of( s48 );
arg = s77.substr( s68, s678 - s68 );
s68 = s678;}
s153.push_back( arg );}}
std::wstring s1814( const std::wstring& s77, wchar_t c ){
size_t pl = s77.find( c ), s1836 = 0, s1807 = 0, s1830;
if( pl == string::npos )
return s77;
wstring s681( s77.size() + 100, L'\0' );
while( pl != string::npos ) { 
s1830 = pl - s1836;
if( s681.size() < s1807 + s1830 + 2 )
s681.resize( (std::max)((size_t)(s681.size()*1.1), s681.size()+100) );
memcpy( (void*)(s681.c_str() + s1807), s77.c_str() + s1836, s1830 * sizeof(wchar_t) );
s681[s1807 + s1830] = L'\\';
s681[s1807 + s1830 + 1] = s77[pl];
s1807 = s1807 + s1830 + 2;
s1836 = pl + 1;
pl = s77.find( c, pl + 1 );}
s1830 = s77.size() - s1836;
memcpy( (void*)(s681.c_str() + s1807), s77.c_str() + s1836, s1830 * sizeof(wchar_t) );
s681.resize( s1807 + s1830/* + 1*/ );
return s681;}
void s57( const wstring& s, const wstring& s72, vector<wstring>& s153, bool clr,
bool s880 ){
size_t s68 = 0, s69 = 0;
while( s69 != wstring::npos && s68 < s.size()) {
if( s880 ) {
s69 = s68;
s4::s994( s, s69, s72 );}
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
wstring s347 = s52( line.substr( pl + s72.size() ), s48 );
pr.first = s76;
pr.second = s347;}
void s59( const wstring& s77, const wstring& s72, vector<pair<wstring, wstring>>& v ){
vector<wstring> s73;
s57( s52( s77, s48 ), L"\n", s73 );
for( size_t n = 0; n < s73.size(); ++n ) {
size_t pl = s73[n].find( s72 );
wstring s76 = s52( s73[n].substr( 0, pl ), s48 );
wstring s347 = s52( s73[n].substr( pl + s72.size() ), s48 );
v.push_back( make_pair( s76, s347 ) );}}
wstring s51( const std::wstring& l, const std::wstring& s, const std::wstring& r ){
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s681 = s.substr( pl );
return s681.substr( 0, s681.find_last_not_of( r ) + 1 );}
wstring s52( const std::wstring& s, const std::wstring& c ){
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s681 = s.substr( pl );
return s681.substr( 0, s681.find_last_not_of( c ) + 1 );}
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
wstring s740( wstring path ){
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
int s681 = stoi( s );
pos = s77.find_first_not_of( s49 + s72, s70 );
return s681;}
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
string s347 = s52( s73[n].substr( pl + 1 ), s49 );
v.push_back( make_pair( s76, s347 ) );}}
string s51( const std::string& l, const std::string& s, const std::string& r ){
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s681 = s.substr( pl );
return s681.substr( 0, s681.find_last_not_of( r ) + 1 );}
string s52( const std::string& s, const std::string& c ){
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s681 = s.substr( pl );
return s681.substr( 0, s681.find_last_not_of( c ) + 1 );}
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
void s81( wstring& s77, vector<wstring>& s1095, map<size_t, size_t>& s1030 ){
size_t pos = 0;
wchar_t s82 = 0;
bool s1156 = false;
wchar_t s83 = 0;
bool s84 = false;
bool s85 = false;
size_t s86 = string::npos;
bool s87 = false;
bool s973 = false;
wstring s88 = L"`'\"";
s1095.reserve( 1000 );
size_t s1025 = 1;
bool s965 = false;
while( pos < s77.size() ) {
wchar_t c = s77[pos];
if( c == '\r' ) {
s77.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1156 = !s1156;}
else if( s82 ) {
if( c == s82 && !s1156 /*s83 != '\\'*/ )
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
s1030[pos - 2] = s1025;}}
else if( c == '/' ) {
if( !s84 && s83 == '/' ) {
s86 = pos - 1;
s84 = true;
s85 = false;
if( pos > 1 && s77[pos - 2] != '\n')
s1030[pos - 2] = s1025;}
else if( s85 && s83 == '*' ) {
s87 = true;
if( s77[pos+1] == '\n' ){
s965 = true;}}}
else if( c == '\n' ) {
s965 = true;
if( s84 ) {
if( !s85 ) {
s87 = true;}
else {
if( !s973 ) {
s973 = true;}}}
else {
if( pos && s77[pos-1] != '\n' ) {
s1030[pos - 1] = s1025;}}}
if( c != L'\\' )
s1156 = false;
if( s965 ) {
size_t pl = s77.rfind( '\n', pos - 1 );
size_t m = (s77[pos] == '\n');
if( pl == string::npos )
s1095.push_back( s77.substr( 0, pos ) );
else
s1095.push_back( s77.substr( pl + 1, pos - pl - m ) );
s965 = false;
s1025++;}
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
s973 = false;
s85 = false;
s87 = false;
s83 = 0;}
s83 = c;
pos++;}
if( s84 ) {
auto it = end(s1030);
if( s1030.size() ) it--; 
size_t ln = (it == end(s1030) ? 0 : it->second);
throw new s2::s16( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
std::wstring s2170( void* p ){
wstring s681( 21, '\0' );
#ifdef WIN32		
_swprintf( (wchar_t*)s681.c_str(), L"%p", (uint64_t*)p );
#else
swprintf( (wchar_t*)s681.c_str(), 20, L"%06x", (uint64_t*)p );
#endif	
return s681;}
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
void s1108(){
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
int s681;
while( true ) {
s130();
wcout << s93 << endl << endl;
for( size_t i = 0; i < s94.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s94[i] << endl;}
s681 = s103( L"Please, enter your answer's number: " );
if( s681 < 0 || s681 > ( int ) s94.size() ) {
wcout << "No variant with such number." << endl;
s96();
continue;}
break;}
return s681;}
wstring s100( const wstring& s93, bool s95 ){
if( !s93.empty() )
wcout << s93;
wstring s347;
if( s95 )
s97( false );
getline( wcin, s347 );
if( s95 )
s97( true );
return s347;}
wstring s101( const wstring& s93, bool s95 ){
wcout << s93;
int s117 = 0;
bool s586 = true;
wstring s118 = s93;
size_t s1102 = s118.size();
size_t s119 = s1102;
while( s586 ) {
s117 = _getch();
switch( s117 ) {
case s110:
if( s1102 > s119 ) {
wcout << '\r' << s118.substr( 0, --s1102 );}
break;
case s111:
if( s1102 < s118.size() )
wcout << s118[s1102++];
break;
case s108:
case s109:
continue;
case s114:
if( ( s1102 > s119 ) && s118.size() ) {
s118.erase( --s1102, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}
break;
case s115:
if( s1102 < s118.size() ) {
s118.erase( s1102, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}
break;
case s113:
s586 = false;
break;
case s116:
break;
default:
if( s1102 < s118.size() )
s118.insert( s1102, 1, s117 );
else
s118 += s117;
++s1102;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}}
return s118;}
wstring getStringValHist( const wstring& s93, const vector<wstring>& s102 ){
wcout << s93;// << endl;
int s117 = 0;
size_t s680 = s102.size();
bool s586 = true;
wstring s118 = s93;
size_t s1873 = s93.size();
size_t s1102 = s1873;
while( s586 ) {
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
else if( s117 == 70 ) s117 = s1545;
else if( s117 == 72 ) s117 = s1546;
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
else if( s117 == 71 ) s117 = s1546; // G
else if( s117 == 79 ) s117 = s1545; // O
}
#endif			
switch( s117 ) {
case s110:
if( s1102 > s1873 ) {
wcout << '\r' << s118.substr( 0, --s1102 );}
break;
case s111:
if( s1102 < s118.size() )
wcout << s118[s1102++];
break;
case s108:
if( s680 > 0 ) {
if( s680 < s102.size() )
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[--s680];
wcout << '\r' << s118;
s1102 = s118.size();}
break;
case s109:
if( !s102.empty() && s680 < s102.size() - 1 ) {
wcout << '\r' << wstring( s118.size(), L' ' );
s118 = s93 + s102[++s680];
wcout << '\r' << s118;
s1102 = s118.size();}
break;
case s114:
if( s1102 > s1873 && s118.size() > s1873 ) {
s118.erase( --s1102, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}
break;
case s115:
if( s1102 < s118.size() ) {
s118.erase( s1102, 1 );
wcout << '\r' << wstring( s118.size() + 1, L' ' );
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}
break;
case s1546:
if( s1102 > 0 ) {
wcout << '\r' << s93;
s1102 = s1873;}
break;
case s1545:
if( s1102 < s118.size() ) {
wcout << '\r' << s118;
s1102 = s118.size();}
break;
case s113:
s586 = false;
break;
case s116:
break;
default:
if( s1102 < s118.size() )
s118.insert( s1102, 1, s117 );
else
s118 += s117;
++s1102;
wcout << '\r' << s118 << '\r' << s118.substr( 0, s1102 );}}
return s118.substr( s1873 );}
int s103( const std::wstring & s93 ){
int s681;
while( true ) {
wcout << s93;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s681 = stoi( inp );}
catch( std::invalid_argument& ) {
continue;}
break;}
return s681;}
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
size_t s680 = 0;
for( auto it : v ) {
if( s680 == 0 )
s122.push_back( 0 );
if( it.size() > s122.back() )
s122.back() = it.size();
if( ++s680 == s121 )
s680 = 0;}
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
wstring s1527 = L"0123456789";
wstring s1528 = L".0123456789";
wstring s186 = L" ,]}\t\r\n";
wstring s2133 = L"-_[]@";
s1681 s1743;
thread_local std::list<bool> s1755;
void s1684( const wstring& dd, const wstring& fs, bool ab, bool rb, bool sb ){
s1743 = s1681( dd, fs, ab, rb, sb );}
void s1684( const s1681& cnf ){
s1743 = cnf;}
void s938::s170( const wstring& s77, size_t& pos, s9<s143> ob ){
size_t s74, s75;
s54( s77, pos, L'{', L'}', s74, s75, true );
if( s74 == string::npos )
return;
s1052 = s74 - 1;
wstring sob = s77.substr( s74, s75 - s74 + 1 );
pos = s75 + 1;
try {
s1755.push_back( s1746.s151 );
ob->s154( sob, s1746 );
s1755.pop_back();}
catch( s16* e ) {
s1755.pop_back();
e->s30( L"during reading the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s938::s998( wstring& s, size_t s68, size_t s679, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1107.lower_bound( s68 );
auto iten = s1107.lower_bound( s679 );
if( itst == end(s1107) || iten == end(s1107) )
return false;
line = itst->second;
s = s1106[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1106[iten->second-1];
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
s938::s938( const std::wstring& file, bool s1622, const s1681& s1745 )
: s1746( s1745 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s48 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1622 == false )
s1105 = file;
else
s194 = file;}
void s938::read( vector<s9<s143>>& s153, const wstring& s190 ){
size_t pos = 0;
if( s194.size() ) {
std::ifstream fs( TOFS( s194 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s194 ));
string s191( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1105 = conv.from_bytes( s191 );
s4::s81( s1105, s1106, s1107 );
if( s190.size() ) {
pos = s1105.find( s190 );
if( pos == string::npos )
throw new s16( s190 + L" directive not found in the source file." );
pos += s190.size() + 1;
if( s1105.size() > 13 && s1105[14] == '\r' )
++pos;}}
size_t s192 = pos;
wstring s278;
bool s193 = false;
while( ( pos = s1105.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1105.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s192; subl = pos - s192;}
else
pl += 1;
wstring s1 = s52( s1105.substr( pl, /*pos - pl - 1*/subl ), s48 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s193 = true;
else
s278 = s52( s1, s48 + L":" );}
if( s278.empty() ) {
size_t pl1 = s1105.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s52( s1105.substr( pl1, pl ), s48 );
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
s1755.push_back( s1746.s151 );
s170( s1105, pos, ob );
s1755.pop_back();}
catch( s16* e ) {
s1755.pop_back();
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
if( !s1755.empty() && s1755.back() )
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
void s175( const wstring& s77, size_t& pos, wchar_t s1198, wchar_t s1240, wstring& s153 ){
size_t s74, s75;
s54( s77, pos, s1198, s1240, s74, s75, true );
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
s131 s176( const wstring& s77, size_t& pos, wstring& s153, const s1681& s1745 ){
if( s77[pos] == s1745.s1683[0] && s1745.s1730) {
s153 = L"";
return s132;}
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"empty element or unrecognized unquoted syntax: " + s77.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s196 = pos;
int shift = 0;
if( s77[pos] == L'(' && s1745.s1685) {
s175( s77, s196, L'(', L')', s153 );
if( s196 == s77.size() - 1 )
shift = 1;}
else {
s196 = pos + 1;
while( std::isgraph<wchar_t>( s77[s196], locloc ) &&
s77[s196] != L':' && s77[s196] != L',' ) {
if( s77[s196] == L'<'  && s1745.s1686 ) {
s175( s77, s196, L'<', L'>', s153 );}
else if( s77[s196] == L'(' && s1745.s1685 ) {
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
void s178( const s938* pf, const wstring& s77, vector<s9<s141>>& s153, 
const s1681& s1745 ){
size_t s68 = s77.find_first_not_of( s48 );
s1755.push_back( s1745.s1718 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, s77, s68, s1745 ) ) );
s4::s994( s77, s68, s1745.s1683 );
if( s68 == string::npos )
break;
++s68;}
s1755.pop_back();}
void s178( const s938* pf, const wstring& s77, size_t& pos,
vector<s9<s141>>& s153, const s1681& s1745 ){
size_t s74, s75, s68 = 0;
s54( s77, pos, L'[', L']', s74, s75, true );
pos = s75 + 1;
wstring ar = s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 );
if( ar.empty() )
return;
s1755.push_back( s1745.s1718 );
while( true ) {
s153.push_back( s9<s141>(new s141( pf, ar, s68, s1745 ) ) );
s4::s994( ar, s68, s1745.s1683 );
if( s68 == string::npos )
break;
++s68;}
s1755.pop_back();}
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
s2133.find( c ) == string::npos )
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
s131 s681 = s140;
size_t pl = s77.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s77.find( L".", pl );
if( pl1 < pl )
s681 = s136;
if( pl == string::npos )
s153 = stod( s77.substr( pos ) );
else
s153 = stod( s77.substr( pos, pl - pos ) );
pos = pl;
return s681;}
s131 s1539( const wstring& s77, size_t& pos, double& s153, const s1681& s1745 ){
const wchar_t* ps = s77.c_str();
size_t sz = s77.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1528.find( ps[st+1] ) == string::npos )
return s132;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1527.find( ps[st+1] ) != string::npos ) ||
( s1527.find( ps[st] ) == string::npos ) )
return s132;
size_t s680 = st;
bool pt = false;
while( s680 < sz ) {
if( ps[s680] == s1745.s1682[0] ) {
if( pt ) return s132;
pt = true;
s680++;}
else if( s1527.find( ps[s680] ) != string::npos )
s680++;
else if( (s48 + s1745.s1683 + L"}").find( ps[s680] ) != string::npos  )
break;
else
return s132;}
s131 s681 = s140;
if( pt )
s681 = s136;
if( s680 == sz )
s153 = stod( s77.substr( pos ) );
else
s153 = stod( s77.substr( pos, s680 - pos ) );
pos = s680;
return s681;}
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
s141::s141( const s938* pf, const wstring& s77, size_t& pos, const s1681& s1745 )
: s198( s132 ), obj( pf ), s1075( pos + (pf ? pf->s942():0), 0 ), s1074( (s938*)pf ){
size_t s68 = s77.find_first_not_of( L" \n\r\t", pos );
if( s68 == string::npos ) {
if( s1745.s1730 )
s198 = s132;
else {
s16* s961 = new s16(wstring( 28, L' ' ) + L"|^|" );
s961->s30( L"empty array item: " + s77.substr( pos - 10, 20 ) );
throw s961;}}
else if( s77[s68] == L'{' ) {
size_t s74, s75;
s54( s77, s68, L'{', L'}', s74, s75, true );
pos = s75+1;
obj.s154( s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 ), s1745 );
s198 = s133;}
else {
pos = s68;
if ( s88.find( s77[pos] ) != string::npos ) {
s172( s77, pos, s77[pos], str, s1745.s151 );
s198 = s139;}
else if ( s77[pos] == L'[' ) {
s178( (s938*)s1074, s77, pos, s162, s1745 ); 
s198 = s135;}
else {
s198 = s1539( s77, pos, s163, s1745 );
if( s198 != s132 )
(void)0;
else if( s183( s77, pos, b ) )
s198 = s137;
else if( s184( s77, pos ) )
s198 = s138;
else
s198 = s176( s77, pos, str, s1745 );;}}
s1075.second = pf ? pos - 1 + pf->s942() : 0;}
s141::s141( double d, s131 v ) 
: s198( v ), obj( NULL ), s163( d ) {
assert( v == s136 || v == s140 );}
bool s141::s1002( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1075.first || s1074.s13() )
return false;
f = s1074->Path();
s1074->s998( s, s1075.first, s1075.second, line );
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
bool s141::s722() const{
if( s198 == s137 )
return b;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s141::s169() const{
if( s198 == s134 || s198 == s139 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s141::s859() const{
if( s198 == s139 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
std::wstring s141::s851() const{
if( s198 == s139 )
return str.substr( 1, str.size() - 2 );
throw new s16( L"NQJ value: wrong variant" );}
void s143::s154( const wstring& s77, const s1681& s1745 ){
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
s180( s77, s68, s76, s1745.s151 );
size_t pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl == string::npos || s77[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
s68 = pl + 1;
s144.insert( make_pair( s76, new s141( src, s77, s68, s1745 ) ) );
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
bool s681 = true;
for( auto it = s144.begin(); it != s144.end(); ++it ) {
auto it1 = r.s144.find( it->first );
if( it1 == r.s144.end() || !( *( it->second ) == *( it->second ) ) ) {
s681 = false;
break;}}
return s681;}
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
auto s681 = s144.find( s152 );
return s681->second;}
void s143::s159( const std::wstring& s76, s142 s347, s145 ap ){
if( s144.find( s76 ) != s144.end() ) {
if( ap == s146 )
throw new s16( L"Field already exists: " + s76, (uint32_t)s16::s17::s21 );
else if( ap == s148 )
return;
else if( ap == s147 )
s144.erase( s76 );}
s144.insert( make_pair( s76, s347 ) );}
void s143::s1619( const std::wstring& s76 ){
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
s131 s1695::s1539( const std::wstring& s77, size_t& pos, double& s153 ){
return s6::s1539( s77, pos, s153, conf );}
} // namespace s6
using namespace s6;
namespace transd {
namespace s7 {
s922 s1542		= 0x80000000;
s922 s1384        = s1542 - 1;
s922 s1385       = s1542 - 2;
s922 s1386       = s1542 - 3;
s922 s1383      = s1542 - 4;
s922 s1382						= s1542 - 8;
s922 s1387    = s1542 - 9;
s922 s1388					= s1542 - 10;
DEFCONST s418 = L"typeMembers";
DEFCONST s419 = L"typeMember";
DEFCONST s420 = L"typeMethods";
DEFCONST s421 = L"typeMethod";
DEFCONST s422 = L"members";
DEFCONST s423 = L"member";
DEFCONST s424 = L"methods";
DEFCONST s425 = L"method";
DEFCONST s426 = L"@init";
DEFCONST s427 = L"@initCall";
DEFCONST s1617 = L"@to-String";
DEFCONST s428 = L"thisPtr";
DEFCONST s429 = L"virtual";
DEFCONST s430 = L"override";
DEFCONST s827 = L"return";
DEFCONST s431 = L"continue";
DEFCONST s432 = L"break";
DEFCONST s433 = L"throw";
DEFCONST s759 = L"else";
DEFCONST s743 = L"elsif";
DEFCONST s789 = L"to";
DEFCONST s434 = L"true";
DEFCONST s435 = L"false";
DEFCONST s826 = L"null";
DEFCONST s934 = L"->";
DEFCONST s1131 = L"const";
DEFCONST s1346 = L"@new";
DEFCONST s1380 = L"stdin";
DEFCONST s1381 = L"stdout";
DEFCONST s1589 = L"this";
DEFCONST s2124 = L"locals:";
DEFCONSTI s860 = -1;
DEFCONSTI s2219 = -2;
DEFCONSTI s2265 = -3;
DEFCONSTI s438 = -4;
DEFCONSTI s436 = -100;
DEFCONSTI s437 = -101;
DEFCONSTI s439 = 1;
DEFCONSTI s440 = 0;
DEFCONSTI s862 = 0x40000000;
DEFCONSTI s1733 = 0x60000000;
DEFCONSTI s861 = 0;
DEFCONSTI s1190 = 1;
DEFCONST s1402 = L":Number";
DEFCONST s1513 = L":Integer";
DEFCONST s1400 = L":IterableForw";
DEFCONST s1399 = L":IterableBidir";
DEFCONST s1401 = L":IterableRand";
DEFCONST s1398 = L":IStream";
DEFCONST s1403 = L":OStream";
DEFCONST s1397 = L":IOStream";
DEFCONST s441 = L"import";
DEFCONST s442 = L"input";
DEFCONST s443 = L"output";
DEFCONST s444 = L"export";
DEFCONST s445 = L"opaque";
DEFCONST s446 = L"public";
DEFCONST s447 = L"private";
DEFCONST s448 = L"secure";
DEFCONST s449 = L"class";
DEFCONST s450 = L"module";
DEFCONST s2146 = L"interface";
DEFCONST s451 = L"AssemblyDescription";
DEFCONST s452 = L"ProgramText";
DEFCONST s453 = L"Export";
DEFCONST s454 = L"Require";
DEFCONST s2152 = L"TypeAlias";
DEFCONST s455 = L".td";
DEFCONST s939 = L".tsd";
DEFCONST s457 = L"MainModule";
DEFCONST s456 = L"_start";
DEFCONST s458 = L"asm" + s455;
DEFCONST s459 = L"@ex";
DEFCONST s1363 = L"@it";
DEFCONST s460 = L"@idx";
DEFCONST s1967 = L"@row";
DEFCONST s763 = L"@pars";
DEFCONST s797 = L"@obj";
DEFCONST s823 = L"@numArgs";
DEFCONST s1560 = L"@progArgs";
DEFCONST s1115 = L"@sourceFile";
DEFCONST s1362 = L"@OS_Type";
DEFCONST s465 = L"source";
DEFCONST s461 = L"objectType";
DEFCONST s462 = L"moduleType";
DEFCONST s463 = L"@name";
DEFCONST s464 = L"entryPoint";
DEFCONST s466 = L"perm";
DEFCONST s467 = L"extends";
DEFCONST s733 = L"packages";
DEFCONST s468 = L"searchDirs";
DEFCONST s930 = L"@attrs";
DEFCONST s1968 = L"restrictions";
DEFCONST s2145 = L"@impl";
DEFCONST s1974 = L"FileRead";
DEFCONST s1975 = L"FileWrite";
DEFCONST s1973 = L"FileAll";
DEFCONST s1976 = L"FuncEval";
DEFCONST s1977 = L"FuncStartProcess";
DEFCONST s1978 = L"RestrictionsAll";
DEFCONST s1979 = L"allow";
DEFCONST s1982 = L"noResult";
DEFCONST s1981 = L"noExecute";
DEFCONST s1980 = L"noCompile";
DEFCONST s909 = L"is";
DEFCONST s908 = L"index type";
DEFCONST s910 = L"value type";
DEFCONST s416 = L"#lang transd";
DEFCONST s1097 = L"#format tsd";
s922 s1290						= 103;
s922 s917						= 110;
s922 s1289				=	123;
s922 s1120						= 124;
s922 s918 			=	125;
s922 s912			= 201;
s922 s1098				= 204;
s922 s913					= 210;
s922 s1099					= 304;
s922 s1100				= 404;
s922 s1101				= 504;
s922 s914					= 510;
s922 s915			= 511;
s922 s916					= 610;
s922 s1117							= 710;
s922 s1118					= 711;
s922 s1355		= 804;
s922 s1356				= 904;
s922 s1357				= 1004;
s922 s1585					= 1024;
s922 s1119					= 1124;
s922 s1286				= 1203;
s922 s1287				= 1210;
s922 s1288				= 1224;
s922 s1653		= 1304;
s922 s1654						= 1404;
s922 s1367						= 1410;
s922 s2276					= 1411;
s922 s1655						= 1504;
s922 s1365						= 1510;
s922 s1366					= 1511;
s922 s1656				= 1604;
s922 s1511					= 1610;
s922 s1512			= 1611;
s922 s1673			= 1704;
s922 s1543			= 1710;
s922 s1587	= 1715;
s922 s1889	= 1716;
s922 CLObjectVal_ctor1				= 1810;
s922 s1586				= 1824;
s922 s1674					= 1904;
s922 s1688				= 2025;
s922 s1877				= 2103;
s922 s1922				= 2210;
s922 s1921					= 2310;
s922 s2144			= 2409;
s922 s2275						= 2410;
s922 CLTDFilter_ctor1				= 2504;
s922 s2191					= 2510;
s922 s2202						= 2603;
s922 s2200						= 2610;
s922 s2201						= 2624;
s922 s2235				= 2703;
s922 s2234				= 2710;
set<wstring> s1114 = { s1115, s1380, s1381, s1362, s827, s431,
s432, s433, s759, s743, s789, s434, s435, s826, s934, s1131,
s1346, s1380, s1381, s1589, L"and", L"or"
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
const wstring s2063 = L"first";
const wstring s245 = L"dcmp";
const wstring s246 = L"dcmpr";
const wstring s247 = L"mod";
const wstring s248 = L"sqrt";
const wstring s249 = L"abs";
const wstring s250 = L"pow";
const wstring s1930 = L"textin";
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
const wstring s766 = L"load-file";
const wstring s815 = L"import-module";
const wstring s1608 = L"unload-file-modules";
const wstring s1307 = L"unload-module";
const wstring s745 = L"has-field";
const wstring s812 = L"tql";
const wstring s753 = L"substr";
const wstring s846 = L"ret";
const wstring s847 = L"sort";
const wstring s894 = L"exit";
const wstring s1306 = L"to-file";
const wstring s1417 = L"any";
const wstring s1416 = L"all";
const wstring s1929 = L"pipe";
const wstring s2194 = L"filter";
const wstring s1550 = L"lout";
const wstring s1928 = L"lin";
const wstring s1604 = L"read-tsd-file";
const wstring s1603 = L"load-from-object";
const wstring s1607 = L"start-process";
const wstring s1605 = L"rebind";
const wstring s1606 = L"sleep";
const wstring s1602 = L"diag";
const wstring s1871 = L"rand";
const wstring s2214 = L"yield";
const s141 s265(L"AttrNA");
s263::s263( s1890& s, const s141* s6, s263* s2093 )
: s1046( (s141*)s6 ), s2092( s2093 ), s2097( NULL ){
s996( s );}
s263::s263( s1890& s672, const s6::s141& s296, s263* s590 )
: s1660( s672 ), s1046( (s141*)&s296 ), s2092( NULL ), s2097( s590 ){
if( s296.s164() == s134 ) {
wstring s = s296.s169();
s996( s );}
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
s284( /*to_wstring( s296.s722() )*/ s296.s722() ? L"true" : L"false" );
else if( s296.s164() == s135 ) {
basic_stringstream<wchar_t> ss;
s296.s155( &ss );
if( s1660.find( L"UVector" ) == 0 ) {
s284( L"UVector" + ss.str() );
s1660 = s4::s52( s1660.substr( 7 ), s48 );}
else
s284( ss.str() );}
else if( s296.s164() == s132 )
s284( L"" );
else
throw new s16( L"Unhandled nqj variant: " + to_wstring( s296.s164() ) );}
s263::s263( const s6::s143& s133 )
: s2092( NULL ), s2097( NULL ){
s283( s133 );}
s263::~s263(){
reset();}
void s263::reset(){
s281.clear();
s266.clear();
s277 = s1660 = s280 = src = L"";}
void s263::s996( s1890& s ){
size_t pos = 0;
wstring s1175 = L"\"'`-+[{<";
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
else if( iswdigit( s[pos] ) || s1175.find( s[pos] ) != string::npos ) {
wstring s77;
s77 = s52( s, s48 );
s284( s77 );}
else
throw new s16( L"Unknown string content: " + s );}
void s263::s282( s1890& s77 ){
src = s77;
size_t pos = 0;
vector<wstring> s673;
s288( s77, pos, s673 );
if( s673.empty() )
return;
s279 = s226;
size_t s68 = 0;
s280 = s287( s673[0], s68 );
for( size_t n = 1; n < s673.size(); n++ )
s281.insert( make_pair( to_wstring( n - 1 ), new s263( s673[n], s1046, this ) ) );}
void s263::s284( s1890& s77 ){
src = s77;
s279 = s225;
s280 = s77;}
void s263::s285( s1890& s77 ){
if( s77.find( L"." ) != string::npos ) {
s277 = L".";}
src = s77;
s279 = s228;
s280 = s77;}
void s263::s283( const s6::s143& s133 ){
s1660 = s302( s133, s7::s463 );
s279 = s227;
vector<pair<wstring, s142>> s144;
s133.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
s286( s144[n].first, *s144[n].second );}}
void s674( wstring& s ){
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
void s263::s289( s6::s143& obj, size_t s2177 ){
wstring s675 = s4::s52( s302( obj, s7::s463 ), s48 );
wstring s656 = s675;
s674( s656 );
if( s656.empty() )
throw new s16( L"Nameless blocks are forbidden." );
if( s656 != s675 )
obj.s159( s7::s463, s142(new s141( s656 )), s143::s147 );
if( s656 == s1660 ) { // partial definition
vector<pair<wstring, s142>> s144;
obj.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n )
s286( s144[n].first, *s144[n].second );}
else {
wstring s2182 = s656;
s263* s2179 = new s263( obj );
s2179->s269( s2174, s141( (double)s2177, s140 ) );
s281.insert( make_pair( s2182, s2179 ) );}}
void s263::s286( s263* node ){
s281.insert( make_pair( node->s299(), node ) );}
void s263::s286( s1890& s76, const s141& s347 ){
s281.insert( make_pair( s76, new s263( s76, s347, this ) ) );}
void s263::s290( s262* s300, size_t s301 /*= 0*/ )
{
s275::iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
if( it->second->s297() == s227 ) {
if( s301 == 0 ) {
it->second->s290( s300, 1 );}
else {}}}}
bool s263::s156( s1890& s76 ) const{
if( s281.find( s76 ) == end( s281 ) )
return false;
return true;}
const s263* s263::s292( s1890& s76 ) const{
size_t s680 = s281.count( s76 );
if( s680 > 1 )
throw new s16( L"multiple values: " + s76, (uint32_t)s149 );
if( s680 == 1 ) {
auto s681 = s281.find( s76 );
return s681->second.s15<s263*>();}
throw new s16( L"node not found: " + s76, (uint32_t)s16::s17::s23 );}
void s263::s288( s1890& s77, size_t& pos, vector<wstring>& s153 ){
size_t s74, s75;
wregex rg( LR"regex(\s*[@\w]+\([\s\S.[:space:][:blank:][:cntrl:][:graph:]\n\r]*)regex" );
wregex rg1( LR"regex(^\s*[@\w]+\s*<)regex" );
wsmatch s1067;
s54( s77, pos, L'(', L')', s74, s75, true );
if( s74 != pos || s75 == string::npos )
throw new s16( L"Parentheses don't match near \"" + 
s77.substr( 0, 40 ) + L"...\"" );
pos = s75;
size_t s68 = s77.find_first_not_of( s48, s74 + 1 );
if( s77[s68] == L')' )
return;
size_t s679 = s68;
wstring s676;
while( s679 < s75 ) {
s68 = s77.find_first_not_of( s48 + L")", s679 );
if( s68 >= s75 )
break;
size_t s677, s678;
if( s77[s68] == L'(' ) {
s54( s77, s68, L'(', L')', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else if( s77[s68] == L'[' ) {
s54( s77, s68, L'[', L']', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else if( s77[s68] == L'{' ) {
s54( s77, s68, L'{', L'}', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Curly brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else if( s4::s88.find ( s77[s68] ) != string::npos ) {
wchar_t _q = s77[s68];
s55( s77, s68, _q,	s677, s678 );
if( s678 == string::npos )
throw new s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else if( iswdigit( s77[s68] ) ) {
s678 = s77.find_first_of( s48 + L")", s68 );
s676 = s77.substr( s68, s678 - s68 );
s679 = s678;}
else if( iswalpha( s77[s68] ) || s77[s68] == L'_' || s77[s68] == L'@' ) {
s678 = s77.find_first_of( s48 + L")", s68 );
size_t s2257 = s77.find_first_of( L"(", s68 );
size_t s2256 = s77.find_first_of( L"<", s68 );
if( s77[s68] == 955 ) { 
s676 = s77[s68];
s679 = s68 + 1;}
else if( s77.find( L"lambda", s68 ) == s68 ) {
s676 = L"lambda";
s679 = s68 + 6;}
else if( s2257 < s678 ) {
s54( s77, s2257, L'(', L')', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else if( s2256 < s678 ) {
s54( s77, s2256, L'<', L'>', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Angle brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
if( s77[s678+1] == L'(' ) {
s54( s77, s2256, L'(', L')', s677, s678, true );
if( s678 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );}
s676 = s77.substr( s68, s678 - s68 + 1 );
s679 = s678 + 1;}
else {
s678 = s77.find_first_of( s48 + L")", s68 );
s676 = s77.substr( s68, s678 - s68 );
s679 = s678;}}
else {
s678 = s77.find_first_of( s48 + L")", s68 );
s676 = s77.substr( s68, s678 - s68 );
s679 = s678;}
s153.push_back( s676 );}}
wstring s263::s287( const std::wstring& s77, size_t &pos ){
size_t s1715 = s77.find( L"<" );
if( s1715 != string::npos && s1715 > 0 ) {
return s77;}
wstring s681;
if( s77[pos] == L'+' && s77[pos + 1] != L'=' )
s681 = s232;
else if( s77[pos] == L'-' && s77[pos + 1] != L'=' && s77[pos + 1] != L'|')
s681 = s236;
else if( s77[pos] == L'*' && s77[pos + 1] != L'=' )
s681 = s234;
else if( s77[pos] == L'/' && s77[pos + 1] != L'=' )
s681 = s235;
else if( s77[pos] == L'^' && s77[pos + 1] != L'=' )
s681 = s250;
else if( s77[pos] == L'=' && s77[pos + 1] != L'=' )
s681 = s231;
else if( s77[pos] == L'<' && s77[pos + 1] != L'=' )
s681 = s238;
else if( s77[pos] == L'>' && s77[pos + 1] != L'=' )
s681 = s239;
else if( s77[pos] == 955 /*L'λ'*/ )
s681 = s252;
if( s681.size() ) {
if( s77.size() > pos + 1 && s77.find_first_of( s48 + L")", pos ) != pos + 1 )
throw new s16( L"1: unknown syntax: " + s77.substr(pos, 40),
(uint32_t)s16::s17::s20 );
pos += 1;
return s681;}
if( s77.substr( pos, 2 ) == L"+=" )
s681 = L"sumeq";
else if( s77.substr( pos, 2 ) == L"-=" )
s681 = L"difeq";
else if( s77.substr( pos, 2 ) == L"*=" )
s681 = L"muleq";
else if( s77.substr( pos, 2 ) == L"/=" )
s681 = L"diveq";
else if( s77.substr( pos, 2 ) == L"^=" )
s681 = L"poweq";
else if( s77.substr( pos, 2 ) == L"<=" )
s681 = L"leq";
else if( s77.substr( pos, 2 ) == L">=" )
s681 = L"geq";
else if( s77.substr( pos, 2 ) == L"==" )
s681 = L"eq";
else if( s77.substr( pos, 2 ) == L"!=" )
s681 = L"neq";
else if( s77.substr( pos, 2 ) == L"-|" )
s681 = s1929;
if( s681.size() ) {
if( s77.size() > pos + 2 && s77.find_first_of( s48 + L")", pos ) != pos + 2 )
throw new s16( L"2: unknown syntax: " + s77.substr( pos, 40 ), 
(uint32_t)s16::s17::s20 );
pos += 2;
return s681;}
size_t s679 = s77.find_first_of( s48 + L")", pos );
s681 = s77.substr( pos, s679 - pos );
pos = s679;
return s681;}
std::wstring s263::s298() const{
return (s277.size() ? s277 + L"::" : L"") + s1660;}
wstring s263::s295( const s6::s143& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s156( s7::s462 ) )
return obj.s158( s7::s462 )->s169();
return def;}
std::wstring s263::s302( const s6::s143& obj,
const std::wstring& s303,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s156( s303 ) )
return obj.s158( s303 )->s169();
return def;}
void s263::s2268( const std::pair<wstring, wstring>& pr ){
if( s281.size() ) {
for( auto sn : s281 )
sn.second->s2268( pr );}
else {
if( s280.find( L"Lambda<" ) == 0 ) {
size_t lpl = s280.find( 955 );
size_t rpl = s280.find(L"]]");
if( s280.find( L"(", lpl ) < rpl )
return;
if( s280.find( pr.first ) > rpl )
return;}
if( s280.find( L"(" ) != string::npos || s280.find( L"[" ) == 0 ) {
size_t pl = 0;
s4::s1317( s280, pl, pr.first );
size_t len = pr.first.size();
while( pl != string::npos ) {
if( ( pl && ( s280[pl - 1] == L'(' || s280[pl - 1] == L' ' ||
s280[pl - 1] == ',' || s280[pl - 1] == '[' || s280[pl - 1] == '{' ||
s280[pl - 1] == ':' ) ) &&
( s280[pl + len] == L')' || s280[pl + len] == L' ' || s280[pl + len] == L'\n' ||
s280[pl + len] == ',' || s280[pl + len] == '.' || s280[pl + len] == ']' ||
s280[pl + len] == '}' || s280[pl + len] == ':' ) )
s280.replace( pl, len, pr.second );
++pl;
s4::s1317( s280, pl, pr.first );}}
else if( s277 == L"." ) {
if( s280.find( pr.first ) == 0 && s280[pr.first.size()] == L'.' )
s280.replace( 0, pr.first.size(), pr.second );}
else if( s280 == pr.first )
s280 = pr.second;}}
const s6::s141& s263::s268( size_t s2091 ) const{
auto it = s266.find( s2091 );
if( it != s266.end() )
return it->second;
return s265;}
const s6::s141& s263::s2101( size_t s2091 ) const{
auto it = s266.find( s2091 );
if( it == s266.end() ) {
if( s2092 )
return s2092->s2101( s2091 );
else
return s265;}
return it->second;}
void s263::s269( size_t s2091, const s6::s141& s267 ){
s266[s2091] = s267;}
void s263::s2108( const s263& s695 ){
for( auto i : s695.s266 )
s266.insert( make_pair( i.first, i.second ) );}
void s263::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s1660 << L" : " << s229[s279] << endl;
buf << s4::fill_n_ch( L' ', s197 ) << L" " << s280 << endl;
map<wstring, s940>::const_iterator it = s281.begin();
for( ; it != s281.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << it->first << endl;
it->second->s304( pd, s197 + s417 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1096 s1007;
void s1096::s964( const std::wstring& s78 ){
++s990;
s26.push_back( Msg( s78 ) );
wcout << s78;}
void s1096::s964( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
++s990;
s26.push_back( Msg( s78, U16(func), U16(file), line, s1034 ) );}
void s1096::s966( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s78, U16(func), U16(file), line, s1037 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1078 = {
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
TDException::TDException( uint32_t s1008, uint32_t cat, const s263* ast_ )
: s16( L"", s1008 ), stage (Stage::s1024 ), category( cat ), s695( (s263*)ast_ ){}
TDException::TDException( Stage stg, uint32_t s1008, uint32_t cat, const s263* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s695( (s263*)ast_ ){
if( category ) {
s30( L"error code: " + std::to_wstring( s1008 ) );
s30( s987[category] + L":" );}}
TDException::TDException( uint32_t s1008, uint32_t cat, const s263* ast_, s1890& s78, Stage stg )
: s16( s78, s1008 ), stage ( stg ), category( cat ), s695( (s263*)ast_ ){
if( category ) {
s30( s987[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1080( e.s1080 ), s695( e.s695 ){}
TDException* TDException::s993( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s197 ) const{
wstring src;
if( s695.s14() )
src = s1897( *s695 );
wstring s = L"Error ";
if( id ) {
wstring s1070;
if( (uint32_t)stage )
s1070 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1070 += std::to_wstring( id );
s += s1070;}
if( (uint32_t)stage ) {
s += L" during " + s1078[(uint32_t)stage];}
s += src + L"\n";
return wstring( s197, L' ' ) + s + s16::Msg( s197 + 2 );}
wstring TDException::s2153( size_t idx ) const{
if( s26.size() < idx )
return L"";
auto it = begin( s26 );
std::advance( it, idx );
return *it;}
wstring TDException::s1897( const s263& s695 ){
size_t s1026 = 0;
wstring file, s1076, s681;
if( s695.Nqj() && s695.Nqj()->s1002( file, s1076, s1026 ) ) {
wstring s1072 = std::to_wstring( s1026 ) + L": '" + s1076 + L"'";
s681 = L"\n  in file: " + file + L"\n  on line " + s1072;}
if( !s695.s291().empty() )
s681 += L"\n  object: '" + s695.s291() + L"', ";
if( !s695.Src().empty() )
s681 += L"code: '" + s695.Src() + L"', ";
return s681;}
s921::s921( s16& e, const s263& s695, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1026 = 0;
wstring file, s1076, src;
wstring	s78 = L"Error during ";
if( s695.Nqj()->s1002( file, s1076, s1026 ) ) {
src = std::to_wstring( s1026 ) + L": '" + s1076 + L"'";
s78 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s78 += L"object: '" + s695.s291() + L"'; code: " + s695.Src();}
s30( s78 );
s1007.s964( Msg( 2 ) );}
s929::s929( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s987 = {
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
bool s654( const wstring& s, bool s708 ){
bool fail = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1114.find( s ) != s7::s1114.end() )
continue;
fail = true;
break;}
if( fail && s708 )
throw new s16( L"illegal identifier: " + s );
return (!fail);}
} // namespace tdlang
s920 s986;
s271::~s271(){}
s481* s271::s494()
{	throw std::logic_error( "1: not implemented" );}
const s481* s271::s501() const
{	throw std::logic_error( "2: not implemented" );}
s484 s271::s495( s481** s274, size_t s496 )
{	throw std::logic_error( "3: not implemented" ); }
s271* s271::s333( s589* s2042, s272* impl ) const
{	throw std::logic_error( "4: not implemented" ); }
void s271::s498( const s272* s585, bool b ) {
(void)0;}
inline bool
s271::s499( const s481* s500 ) const{
return ( s500->s350() == s350() );}
inline bool
s271::s1530( s1054 s617 ) const{
return s300->TR().s1523( s350(), s617 );}
const s807& 
s271::s1187() const {
return s300->TR().s1006( s491 ); }
s271::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s271::operator int() const { throw std::logic_error( "6: not implemented" ); }
s271::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s271::to_wstring( uint32_t s1553 ) const { throw std::logic_error( "8: not implemented" ); }
s1312 s271::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s271::to_null() { s1665( s7::s1733 ); }
void s271::s1323( const s263& ast_, s262* s300, s272* obj,
s1890& s332, vector<s271*>& s153 ){
assert( ast_.s291().size() );
size_t pos = 0;
vector<wstring> s673;
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
s263::s288( s77.substr( s77.find( L"(" ) ), pos, s673 );
if( s673.empty() )
return;
for( size_t n = 0; n < s673.size(); n++ ) {
s263* ast1 = new s263( s673[n], ast_.Nqj(), (s263*)&ast_ );
s153.push_back(
s271::s502( *ast1, s300, obj, s332, false )
);}}
s271* s271::s502( const s263& s695, s262* s300, s272* obj,
s1890& s332, bool s2160 ){
TDException s961( s7::s1688, s926, &s695 );
s271* p;
if( s695.s297() == s225 ) {
wstring s347 = s695.s291();
bool quot = s88.find( s347[0] ) != string::npos;
size_t ppl = s347.find( L"(" );
bool lastp = s347.back() == L')';
s1890& ownerName = s695.s268( s2085 ).s169();
if( ( s695.s268( s2279 ).s169() == L"locals" || 
( s695.s268( s2086 ).s169() == L"CallSite" &&
ownerName != s252 ) ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s345 = s347.substr( 0, ppl );
wstring s77 = L"(" + s7::s1346 + L"<" + s345 + L"> " + s347.substr( ppl + 1 );
s940 tast = new s263( s77, s695.Nqj(), (s263*)&s695 );
p = s589::s1110( *tast, s300, obj, s332, s2160 );}
else {
p = s300->TR().s516( s695, obj, s332 );
if( !p )
throw s961.s993( L"unrecognized type of the object: " + s695.s291() );
((s481*)p)->s504( s695.s299() );}}
else if( s695.s297() == s226 )
p = s589::s1110( s695, s300, obj, s332, s2160 );
else if( s695.s297() == s228 )
p = new s369( s695.s291(), s300 );
else //if( s695.s297() == s227 )
throw new s16( L"unexpected node type" );
return p;}
s271* 
s271::s1011( s262* s300, s271* par, s272* s586, s589* s215,
s1890& s332, bool proc ){
s271* s681;
if( par->s492() == s475 ) {
s488 cs = new s559( *((s559*)par) );
s681 = s589::s598( cs, s300, s586, s215, s332, proc );
((Transd*)s681)->s498( s586, proc );}
else {
par->s498( /*s586*/s215 ? s215 : s586, proc );
return par;}
return s681;}
s483
s271::s1010( s1890& s77, const s263* ast_, s262* s300, s272* s586 ){
s940 ast1;
if( ast_ )
ast1 = new s263( s77, ast_->Nqj(), (s263*)ast_ );
else
ast1 = new s263( L"", s77 );
s483 pr = s271::s502( *ast1, s300, s586, s586->s298() );
if( pr->s492() == s473 ) {
pr->s498( s586 );
pr = pr.s15<s369*>()->s375();}
s483 s681 = s271::s1011( s300, pr, s586, NULL, s586->s298(), false );
return s681;}
const wstring& 
s271::s351() const{
return s300->TR().s798( s350() );}
void s271::s349( s807::s731 type ){
s491 = type;}
s482* s1111( s503& m, const wstring& s152 ){
if( m.count( s152 ) > 1 )
throw new s16( L"multiple values: " + s152, (uint32_t)s16::s17::s21 );
auto s681 = m.find( s152 );
if( s681 == m.end() )
throw new s16( L"no such key: " + s152, (uint32_t)s16::s17::s23 );
return s681->second;}
void s666( const std::wstring& s, std::wstring& s1103, std::wstring& s599 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1103 = s.substr( 0, pl );
s599 = s.substr( pl + 2 );}
s481::s481( const s481& r ) 
: s271( r ), ns( r.ns ){}
s481::~s481(){}
s481* s481::s494(){
return this;}
void s481::s1945( s1890&) { throw std::logic_error( "from_wstring: not implemented" ); }
wstring s481::s298() const { return ns->s298(); }
wstring s481::s828() const { return ns->s828(); }
wstring s481::s2154() const { return ns->s828(); }
s481* s481::s1525( const s481* p ) const{
if( s350() == p->s350() ) {
s481* s681 = (s481*)p->s333(0,0);
return s681;}
throw new s16( L"no conversion from '" + p->s351() + L"' to '" + s351() + L"'" );}
s481* s481::s353( s272* s586, const std::vector<s1054>& vt ) const{
assert(0);
return 0;}
s1054 s481::s1179( s1890& s1541, const vector<s483>& l ) const{
throw std::logic_error( "9: not implemented" );}
s589* 
s481::s1671( s1890& s672, s589* s215, s272* s1658,
s559* cs ) const{
if( s672 == L"cp" ) {
return new s1667( s300, (s272*)this, s215, &s481::s1689, cs->s600(),
L"cp",	0, cs->s601(), cs->s2166() );}
else if( s672 == L"exec" ) {
return new s1667( s300, s1658, s215, &s481::s1879, cs->s600(), L"exec",
0, cs->s601(), cs->s2166() );}
else if( s672 == L"_META_type" ) {
return new s1667( s300, s1658, s215, &s481::s1923, cs->s600(),
L"_META_type", Types.String,	cs->s601(), cs->s2166() );}
else if( s672 == L"is-def" ) {
return new s1667( s300, s1658, s215, &s481::s2277, cs->s600(),
L"is-def", Types.Bool,	cs->s601(), cs->s2166() );}
else if( s672 == L"undef" ) {
return new s1667( s300, s1658, s215, &s481::s2278, cs->s600(),
L"undef", Types.Null,	cs->s601(), cs->s2166() );}
return NULL;}
s481* s481::s1689( s481** s274, size_t s496 ){
return (s481*)s333(0,0);}
s481* s481::s1879( s481** s274, size_t s496 ){
return s495( s274, s496 );}
s481* s481::s1923( s481** s274, size_t s496 ){
return new s357( s300, s351() );}
s481* s481::s2277( s481** s274, size_t s496 ){
return new s358( s300, s1195() );}
s481* s481::s2278( s481** s274, size_t s496 ){
s1665( s7::s862 );
return s363;}
s481* s481::s1880( s481** s274, size_t s496 ){
return s1881( s274, s496 );}
s481* s481::s1881( s481** s274, size_t s496 ){
throw std::logic_error( "10: not implemented" );}
void s481::s1920( Stream* s1919 ) const{
s1919->s1469( to_wstring() );}
void s481::s1944( Stream* s1919 ){
wstring s;
s1919->s1450( s, string::npos );
s1945( s );}
vector<wstring> s519::s523 = { s7::s444, s7::s442,
s7::s445, s7::s443 };
s1::s9<s524> s555 = new s524();
size_t s960( const vector<s807::s887>& vt ){
size_t s681 = 0;
for( auto i : vt )
s681 = ( s681 << 7 ) ^ i;
return s681;}
size_t s489::s1049( s1890& s, size_t& pos, s807::Cont& s153 ){
size_t s68 = pos;
size_t s681 = 0;
if( s[s68] == L' ' )
s68 = s.find_first_not_of( s4::s48, s68 );
while( s68 < s.size() && s[s68] != L'>' && s[s68] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s68 );
wstring stype = s4::s52( s.substr( s68, pl - s68 ), s4::s48 );
s1054 s1084 = get( stype /*+ L"()"*/ )->s350();
s153.push_back( s1084 );
pl = s.find_first_not_of( s4::s48, pl );
s807::Cont s1062;
size_t s1047 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1047 = s1049( s, ++pl, s1062 );}
else if( s[pl] == L',' ) {
s1047 = 0;}}
s153.push_back( ( s807::s887 ) s1047 );
s153.insert( end( s153 ), begin( s1062 ), end( s1062 ) );
s681++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s48, pl );
pos = s68 = pl;}
pos++;
return s681;}
wstring s1148( const s807::Cont& s1057, size_t& idx, s489& s904 ){
wstring s681 = s904.s798(s1057[idx++]);
size_t n = (size_t)s1057[idx++];
if( n && s681.back() != L'>' ) {
s681 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s681 += ( k ? L" " : L"" ) + s1148( s1057, idx, s904 );}
s681 += L">";}
return s681;}
wstring s489::s1005( const s807::Cont& s1057 ){
assert( s1057.size() );
if( s1057.size() == 1 )
return  s1087[s1057[0]] + L"< 0 >";
size_t idx = 0;
wstring s681;
while( idx < s1057.size() ) {
s681 += s1148( s1057, idx, *this );
if( idx < s1057.size() )
s681 += L" ";}
return s681;}
wstring s489::s1342( s1890& tn ){
wstring sv = tn;
size_t s2111 = sv.find( L"(" );
size_t b = sv.find( L'<' );
size_t e = sv.rfind( L'>', s2111 );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' ) {
sv.erase( n--, 1 );
--e;}
return sv;}
void s489::s2104( const s807::Cont& v, size_t& idx, s807::Cont& s153 ){
s153.push_back( v[idx++] );
size_t n = v[idx++];
s153.push_back( (s1054)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s2104( v, idx, s153 );}}
void s2088( const s807::Cont& v, size_t& s2102,
s807::Cont& s153 ){
s153.push_back( v[s2102++] );
size_t s2110 = v[s2102++];
s153.push_back( ( s807::s887 ) s2110 );
while( s2110-- ) {
s2088( v, s2102, s153 );}}
void s489::s1001( const s807::Cont& v, vector<size_t>& s2119, 
s807::Cont& s153 ){
size_t s2102 = 1;
size_t s2110 = v[s2102++];
size_t s2099 = 0;
size_t s2096 = s2119[0];
s807::Cont s2116;
assert( s2096 < s2110 );
while( s2099++ <= s2096 ) {
s2116.clear();
s2088( v, s2102, s2116 );}
if( s2119.size() > 1 ) {
vector<size_t> s2117( s2119.begin() + 1, s2119.end() );
s1001( v, s2117, s2116 );}
else
s153 = s2116;}
s807::s807( s731 t1, s731 t2/*=(s731)-1*/, s731 t3/*=(s731)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s731)-1 ) {
vt.push_back( t2 );
if( t3 != (s731)-1 )
vt.push_back( t3 );}
s1086 = s960( vt );}
s807::s807( const s807& right )
: s1086( right.s1086 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s807::s807( const Cont& v ) 
: vt( v ) {
s1086 = s960( vt );}
s807::s887 s807::s350( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s807::s349( s731 t ){
vt.clear();
vt.push_back( t );}
void s807::s349( s919 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s807::s779( s731 t ){
vt.push_back( t );}
void s807::s779( s919 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s807::s813( std::vector<s271*>& s153 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s153.push_back( new s344( NULL, (int)vt[n] ) );}
inline bool s807::operator==( const s807& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s731* pvt1 = (s731*)&vt[0];
s731* pvt2 = (s731*)&p.vt[0];
for( size_t s680 = 0; s680 < sz1; ++s680 )
if( pvt1[s680] != pvt2[s680] )
return false;
return true;}
s489::s489( s262* pass_ ) 
: s300( pass_ ) {
reset();}
void s489::s290(){
for( size_t n = 0; n < s1104.size(); ++n ) {
if( s1104[n] ) {
s1104[n]->s348();}}}
void s489::s515( const s480& st ){}
void s489::reset() {
s1104.clear(); 
s1087.clear();
s1092.clear();
s1088.clear();
s1093.clear();
s911.clear();
s886.clear();
s1249.clear();
s1264.clear();
s1540.clear();
s1104.push_back( NULL ); 
s1087.push_back( L"" );
s1092.push_back( 0 );
s886[L":Data"] = 1;
s1249[1] = L":Data";
s1196 = 1;
s1264.push_back( 0 );
s1540.push_back( vector<s1054>() );
srand( (unsigned int)time(NULL) );}
s1054 s489::s218( s481* p, s1890& s345 ){
if( s1088.find( s345 ) != s1088.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1087.push_back( s345 );
s1104.push_back( p );
s1054 s1084 = (s1054)s1087.size() - 1;
s1092.push_back( s807( s1084 ) );
p->s349( s1084 );
s1088[s345] = s1084;
s1093[s1092.back()] = s1084;
s1264.push_back( 1 );
s1540.push_back( vector<s1054>() );
return s1084;}
void s489::s1652( s1890& s345 ){
auto it = s1088.find( s345 );
if( it == s1088.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1054 s1084 = it->second;
s1088.erase( it );
s1104[s1084] = NULL;
s1087[s1084] = L"";
s1093.erase( s1092[s1084] );
s1092[s1084] = s807();
s1264[s1084] = 0;
s1540[s1084-1].clear();}
s1054 s489::s1061( const s807::Cont& v, s1890& s345 ){
s807 vt( v );
if( s1093.find( vt ) != s1093.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1087.push_back( s345 );
s1092.push_back( vt );
s1054 s1084 = (s1054)s1087.size() - 1;
s1088[s345] = s1084;
s1093[s1092.back()] = s1084;
s1093[s807( s1084 )] = s1084;
s1104.push_back( s1104[vt.s350( 0 )]->s353( s300, v ) );
s1264.push_back( s1264[vt.s350( 0 )] );
s1540.push_back( vector<s1054>() );
return s1084;}
void s489::s2122( const s807::Cont& v, s807::Cont& s153, size_t s2102  ){
assert( v.size() );
s153.push_back( v[0] );
if( !s2102 ) s2102 = 1;
size_t s2110 = v[s2102++];
s153.push_back( (s1054)s2110 );
size_t s2099 = 0;
s807::Cont s2116;
while( s2099++ < s2110 ) {
s2116.clear();
s2088( v, s2102, s2116 );
s1054 s2121 = 0;
if( s2116.size() == 2 && s2116[1] == 0 )
s2121 = s2116[0];
else
s2121 = s1039( s2116 );
s153.push_back( s2121 );
s153.push_back( 0 );}}
s1054 s489::s1039( const s807::Cont& v_ ){
s807::Cont v;
s2122( v_, v );
s807 vt( v );
s1054 s681 = 0;
auto it = s1093.find( vt );
if( it == s1093.end() ) {
wstring s1082 = s1005( v );
s681 = s1061( v, s1082 );}
else
s681 = it->second;
return s681;}
uint32_t s1184( uint32_t n ){
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
traitnum_t s489::s1242( s1890& trait, s1054& s1499 ){
auto it = s886.find( trait );
if( it != end( s886 ) )
return it->second;
s1196 = s1184( s1196 );
s886[trait] = s1196;
s1249[s1196] = trait;
s1499 = s7::s1542 + (s1054)s1500.size();
s1500.push_back( s1196 );
return s1196;}
void s489::s1153( s807::s887 type, s1890& trait, s1054& s1499 ){
traitnum_t tn;
auto it = s886.find( trait );
if( it == end( s886 ) ) {
tn = s1242( trait, s1499 );
s1264[type] *= tn;}
else {
tn = it->second;
if( !s1189( type, tn ) )
s1264[type] *= tn;}}
traitnum_t s489::s1447( s1054 alias ) const{
return s1500[alias - s7::s1542];}
bool s489::s1189( s1054 s617, traitnum_t tra ) {
assert( s617 && s617 < s1092.size() );
double d = (double)s300->TR().s1146( s617 ) / tra;
return ( d == (int)d );}
bool s489::s1454( s1054 s617, s1054 alias ) {
assert( s617 && s617 < s1092.size() );
double d = (double)s300->TR().s1146( s617 ) /
s1500[alias-s7::s1542];
return ( d == (int)d );}
void s489::s1522( s1054 s617, s1054 is ){
s1540[s617].push_back( is );}
bool s489::s1523( s1054 s617, s1054 is ){
if( s617 == is )
return true;
if( s617 >= s1540.size() )
return false;
std::vector<s1054>& v = s1540[s617];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
bool s489::s1523( const s271* s617, const s271* is ){
if( !s1523( s617->s350(), is->s350() ) ) {
return s617->s499( (s481*)is );}
return true;}
void s489::s1162( s1890& alias, s1890& s345, s1890& s1826 ){
assert( s1088.find( alias ) == end( s1088 ) );
s1054 typid;
auto it = s1088.find( s345 );
if( it == s1088.end() ) {
s807::Cont vt;
size_t pos = 0;
s1049( s345, pos, vt );
if( vt[0] == s1701 ) {
s1054 et_, kt_, vt_;
s322* s2208 = (s322*)s1000( s1701 );
typid = s2208->s1186( s2208, s345, s1701, vt, et_, kt_, vt_ );}
else
typid = s1039( vt );}
else
typid = it->second;	
s1087.push_back( alias );
s1104.push_back( s1104[typid] );
s1092.push_back( s1092[typid] );
s1264.push_back( s1264[typid] );
s1540.push_back( s1540[typid-1] );
s1088[alias] = typid;
auto it1 = s1827.find( s1826 );
if( it1 == s1827.end() )
it1 = s1827.insert( make_pair( s1826, list<wstring>() ) ).first;
it1->second.push_back( alias );}
void s489::s1863( s1890& s1103 ){
auto it = s1827.find( s1103 );
if( it != s1827.end() ) {
for( auto it1 = it->second.begin(); it1 != it->second.end(); ++it1 ) {
s1088.erase( *it1 );}}}
wstring s489::s1265( s1890& tn_, s1890& s1103 ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1088.find( s );
if( it == end( s1088 ) )
return tn_;
const wstring& tn = s1087[s1093[s1092[it->second]]];
if( tn != s ) {
auto it1 = s1827.find( s1103 );
if( it1 != end( s1827 ) ) {
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() ) {
it1 = s1827.find( L"::" );
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() )
return tn_;}}
wstring s681 = tn_;
return s681.replace( 0, s.size(), tn );}
return tn_;}
s481* s489::s516( const s263& s695, s272* s586, s1890& s517 ){
if( s695.s1299() )
return s1104[s695.s1299()]->s352( s695, s586, s517 );
wstring s347 = s695.s291();
if( s347.substr(0,2) == L"[[" && s952::s2162( s347 ) )
return s1104[s1088[Types( s300, Types.Tuple )->s351()]]->s352( s695, s586, s517 );
else if( s347[0] == L'[' )
return s1104[s1088[Types( s300, Types.Vector )->s351()]]->s352( s695, s586, s517 );
else if( s347.find( L"UVector[" ) == 0 )
return s1104[s1088[Types( s300, Types.s742 )->s351()]]->s352( s695, s586, s517 );
else if( s347[0] == L'{' )
return s1104[s1088[Types( s300, Types.Index )->s351()]]->s352( s695, s586, s517 );
else if( s347.find( L"typealias" ) == 0 ) {
size_t pl = s347.find( L"(" );
wstring s345 = s4::s52( s347.substr( pl + 1, s347.size() - pl - 2 ), s4::s48 );
s1162( s695.s299(), s345, s517 );
return s1104[s1088[Types( s300, Types.String )->s351()]]->s352( s695, s586, s517 );}
wstring s345 = L"";
s481* s681 = NULL;
if( s4::s88.find( s347[0] ) != string::npos )
s345 = s357( s300 ).s351();
else if( isdigit( s347[0] ) || s347[0] == L'-' )
return s334::s343( s300, s347, s517 );
else if( ( s681 = s1104[s1139]->s352( s695, s586, s517 ) ) )
return s681;
else {
size_t pl = s347.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s345 = s347.substr( 0, pl );}
else if( pl == string::npos )
s345 = s347;}
auto it = s1088.find( s345 );
if( it == s1088.end() ) {
auto it1 = s886.find( s345 );
if( it1 == end( s886 ) )
throw new s16( L"Type does not exist: " + s347, (uint32_t)s16::s17::s23 );
return new s382( s300, s586, it1->second, s1236 );}
return s1104[it->second]->s352( s695, s586, s517 );}
s481* s489::s516( s1054 s338, s272* s586, s1890& s517 ){
if( s338 >= s7::s1542 ) {
auto it = s1249.find( s338 - s7::s1542 );
if( it != end( s1249 ) )
return new s382( s300, s586, it->first, s1236 );}
if( !s338 || s338 >= s1087.size() )
throw new s16( L"no type with such id: " + to_wstring( s338 ) );
s1054 type = s338;
if( s1092[type].s350() != type )
type = s1092[type].s350();
if( s1092[s338].s813().size() == 1 ) {
s481* p = s1104[type]->s353( s586 );
return p;}
else {
return s1104[type]->s353( s586, s1092[s338].s813() );}}
const s481* s489::get( s1890& s76, bool s518/*= true*/ ) const
{
wstring s345 = s76;
size_t pl = s76.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s76.find( L"0" ) == string::npos )
s345 = s76.substr( 0, pl );
auto s681 = s1088.find( s345 );
if( s681 == s1088.end() ) {
if( s518 )
throw new s16( L"1: symbol not found: " + s76 );
else
return NULL;}
return s1104[s681->second].s15<const s481*>();}
bool s489::s156( s1890& s76 ) const{
if( s1088.find( s76 ) == s1088.end() )
return false;
return true;}
const wstring& s489::s798( s1054 n ) const{
if( n >= s1087.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1087[n];}
s1054 s489::s1003( s1890& s345, bool s518 ) const{
auto it = s1088.find( s345 );
if( it == s1088.end() ) {
if( s518 )
throw new s16( L"no such type: " + s345,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1054 s489::s1004( const s807& vt, bool s518 ) const{
auto it = s1093.find( vt );
if( it == end( s1093 ) ) {
if( s518 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s807& s489::s1006( s1054 t ) const{
assert( t && t < s1092.size() );
return s1092[t];}
const s481* s489::s1000( s807::s887 t ) const{
assert( t && t < s1092.size() );
return s1104[t].s15<const s481*>();}
void s489::s784(){
size_t s741 = s334::s801() + 1;
for( size_t n = s741; n < s1087.size(); ++n ) {
s1088.erase( s1087[n] );
s1093.erase( s1092[n] );
s911.erase( (s1054)n );}
s1087.erase( s1087.begin() + s741, s1087.end() );
s1104.erase( s1104.begin() + s741, s1104.end() );
s1092.erase( s1092.begin() + s741, s1092.end() );}
bool s489::s1239(){
return rand() % 2;}
double s489::s1241(){
return rand() / RAND_MAX;
}
int s489::s1247(){
return rand();}
void s489::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << L"Types :" << endl;
for( size_t n = 0; n < s1087.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s197 + 5 ) << s1087[n] << endl;
s1104[n]->s304( pd, s197 + 10 );}}
s480::s480( const s480& right )
: s551( right.s551 ), s535( right.s535 ), s537( right.s537 ){}
s480::~s480(){
s551.clear();}
void s480::s498( s272* s873, s272* s586, bool s514/*= true*/ )
{
for( auto sym : s551 ) {
if( sym.second->s492() != s474 && sym.second->s492() != s2150 
&& !( s586 && s586->s492() == s478 && sym.second->s492() == s1235 ) // ???DEBUG??? 220711
) {
try {
sym.second->s498( s873 );}
catch( TDException* e ) {
e->s1069( TDException::Stage::s1019 );
s1007.s964( e->Msg( 0 ) );
continue;}}}
if( s1007.s928() )
return;
if( 0 && s514 ) {// ???DEBUG??? 220710
for( auto sym : s551 ) {
if( sym.second->s492() == s474 )
sym.second.s15<Transd*>()->s498( s873, false );}}}
void s549::s1637( s262* s300 ){
for( auto sym : s557 ) {
if( sym.find( L"::" ) == string::npos )
s300->s1638( sym );}}
void s480::reset(){
s551.clear();}
void s480::copy( s480& t, s272* s586, s589* s585, s145 ap ) const{
t.s537 = s537;
for( s533::const_iterator it = s551.begin(); it != s551.end(); ++it ) {
if( it->second->s492() != s474 ) {
s271* p = it->second->s333( s585, s586 );
t.s539( it->first, p, ap );}}
for( s533::const_iterator it = s551.begin(); it != s551.end(); ++it ) {
if( it->second->s492() == s474 ) {
s589::s561 ct = it->second.s15<Transd*>()->s858();
s589* ptr = NULL;
if( ct == s589::s566 || ct == s589::s565 )
ptr = (s589*)it->second->s333( s585, s586 );
else if( ct == s589::s564 )
ptr = new s835( *( s835* )&( *it->second ), s585, s586 );
else
ptr = (s589*)it->second->s333( s585, s586 );
t.s539( it->first, ptr, ap );}}}
void s480::s546( s480& t ) const{
for( s533::const_iterator it = s551.begin(); it != s551.end(); ++it ) {
if( it->second->s492() == s474 )
t.s539( it->first, it->second.s15<s271*>() );
else
t.s539( it->first, it->second->s333(0,0) );}}
void s480::s1601( s480& t ) const{
for( s533::const_iterator it = s551.begin(); it != s551.end(); ++it ) {
if( it->second->s492() != s474 ) {
auto it1 = t.s551.find( it->first );
if( it1 == end( t.s551 ) )
t.s551[it->first] = it->second;
else
it->second.s15<s481*>()->s354( it1->second.s15<s271*>() );}}}
bool s480::s536( s1890& s76, s145 ap /*= s146*/ )
{
if( s551.find( s76 ) != s551.end() ) {
wstring rep = s7::s419 + L" name already exists: " + s76;
if( ap == s146 || ap == s532 ) {
if( ap == s146 )
throw new TDException( 0, s1657, NULL, s76 );
return false;}
else if( ap == s148 ) {
return false;}}
return true;}
void s480::s539( s1890& s76, s271* sym, s145 ap/*= s146*/ )
{
if( (ap == s147) || s536( s76, ap ) )
s551[s76] = sym;}
void s480::s539( s1890& s76, s142 s347, s145 ap/*= s146*/ )
{
throw new s16( (uint32_t)s16::s17::s21 );}
void s480::s540( const std::wstring& s76 ){
auto it = s551.find( s76 );
if( it == s551.end() )
return;
s551.erase( it );}
void s480::s541( const s6::s143& s79, s145 ap/*= s146*/ )
{
vector<pair<wstring, s142>> s144;
s79.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n )
s539( s144[n].first, s144[n].second );}
bool s480::s156( s1890& s76 ) const{
if( s551.find( s76 ) == s551.end() )
return false;
return true;}
s481* s480::get( s1890& s76, bool s518/*= true*/ ) const
{
auto s681 = s551.find( s76 );
if( s681 == s551.end() ) {
if( s518 )
throw new s16( L"2: symbol not found: " + s76 );
else
return NULL;}
return s681->second.s15<s481*>();}
void s480::s544( std::vector<std::wstring>& s153 ) const{
for( auto sym : s551 )
s153.push_back( sym.first );}
void s480::s542( vector<wstring>& s153 ) const{
for( auto sym : s551 ) {
if( sym.second->s492() == s474 )
s153.push_back( sym.first );}}
void s480::s543( vector<wstring>& s153 ) const{
for( auto sym : s551 ) {
if( sym.second->s492() == s472 ||
sym.second->s492() == s478 || sym.second->s492() == s477 )
s153.push_back( sym.first );}}
void s480::s545( const s480& t,
vector<wstring>& s153 ) const{
for( auto sym : s551 ) {
if( t.s156( sym.first ) )
s153.push_back( sym.first );}}
bool s480::implements( const s480& t ) const{
for( auto sym : t.s551 ) {
if( !s156( sym.first ) )
return false;}
return true;}
void s480::s289( const s480& t, s145 ap /*= s146*/ )
{
if( ap != s147 ) 
for( auto sym : t.s551 )
s536( sym.first, ap );
for( auto sym : t.s551 )
s539( sym.first, sym.second.s15<s481*>(), ap );}
void s480::s547( s510 pv, s263* s79 ){
if( !s537 )
s537 = new s524();
s537->s527( pv, s79 );}
void s480::s531( s1890& s332, vector<wstring>& s153 ){
for( s533::iterator it = s551.begin(); it != s551.end(); ++it ) {
s510 pv = s511;
if( s537 )
pv = s537->s530( it->first, s332 );
if( pv == s511 ) {
if( s535 == s507 )
pv = s512;
else if( s535 == s509 )
pv = s513;
else {
if( it->second->s492() == s474 )
pv = s512;
else
pv = s513;}}
if( pv == s512 )
s153.push_back( it->first );}}
bool s480::s548( s1890& s278,	s1890& s332 ) const{
if( s537 ) {
s510 pv = s537->s530( s278, s332 );
if( pv == s512 )
return true;
else if( pv == s511 ) {
if( s535 == s507 )
pv = s512;
else if( s535 == s509 )
pv = s513;
else {
auto it = s551.find( s278 );
if( it == s551.end() )
throw new s16( L"1: Symbol does not exist: " + s278 );
size_t cat = it->second->s492();
if( cat == s474 || cat == s476 || cat == s478 )
return true;}}
return false;}
return true;}
size_t s480::s320() const{
s533::const_iterator it = s551.begin();
size_t s681 = 1;
for( ; it != s551.end(); ++it ) {
if( it->first[0] != '@' && it->second->s492() != s474 
&& it->second->s492() != s1235 ) {
size_t h = it->second.s15<s481*>()->s320();
if(!h) h = 501316864073;
s681 = s681 * h << 1;}}
return s681;}
bool s480::compare( const s533& r ) const{
if( r.size() != s551.size() )
return false;
s533::const_iterator it = s551.begin();
for( ; it != s551.end(); ++it ) {
auto s2226 = r.find( it->first );
if( s2226 == r.end() )
return false;
if( !it->second.s15<s481*>()->operator==( s2226->second.s15<s481*>() ) )
return false;}
return true;}
void s480::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Symbols :" << endl;
s533::const_iterator it = s551.begin();
for( ; it != s551.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << it->first << L" :" << endl;
if( it->second.s14() ) {
it->second->s304( pd, s197 + s417 * 2 );
buf << endl;}}}
wstring s480::to_wstring( uint32_t s1553 ) const{
std::wostringstream buf;
buf << endl << s4::fill_n_ch( L' ', 0 ) << L"Symbols :" << endl;
s533::const_iterator it = s551.begin();
for( ; it != s551.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s417 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s304( &buf, s417 * 2 );
buf << endl;}}
return buf.str();}
s549::s549(){}
void s549::s498( s262* s300, s1890& s556 ){
s332 = s556;
for( size_t n = 0; n < s557.size(); ++n ) {
wstring s76 = s557[n];
vector<wstring> s153;
s300->s219( s76, s556, s153 );
for( size_t m = 0; m < s153.size(); ++m ) {
s76 = s76.substr( 0, s76.find( L"::" ) );
s551.insert( make_pair( s153[m], make_pair( (s481*)s300->s639( 
s557[n],	s556 ), s76) ) );}}}
void s549::s553( s1890& s76, s262* s300, s1890& s556 ){
s557.push_back( s76 );
vector<wstring> s153;
s300->s219( s76, s556, s153 );
for( size_t n = 0; n < s153.size(); ++n )
s551.insert( make_pair( s153[n], make_pair( (s481*)s300->s639( 
s76,	s556 ), s76 ) ) );}
void s549::s552( s1890& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s16( L"Unrecognized import syntax: " + s );
s557.push_back( s.substr(1, s.size() - 2 ) );}
bool s549::s2163( s1890& s76 ){
if( std::find( begin( s557 ), end( s557 ), s76 ) !=
end( s557) )
return true;
return false;}
bool s549::s554( s1890& sym, s369* ref ){
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );}
else
mem = sym;
size_t s680 = s551.count( mem );
if( !s680 )
return false;
if( s680 > 1 && mod.empty() )
throw new s16( L"ambiguous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s551.equal_range( mem );
if( s680 == 1 && mod.empty() ) {
s481* pd = range.first->second.first;
if( pd->s492() == s477 || pd->s492() == s476 )
return pd->s554( mem, ref, s332, true );
ref->s381( (s481*)pd->s501() );
ref->s380( pd );
return true;}
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod /*sym*/ ) {
s481* pd = it->second.first;
if( pd->s492() == s477 )
return pd->s554( mem, ref, L"", true );
ref->s381( (s481*)pd->s501() );
ref->s380( pd );
return true;}}
return false;}
void s549::copy( s549& t ) const{
for( s533::const_iterator it = s551.begin(); it != s551.end(); ++it )
t.s551.insert( make_pair( it->first, it->second ) );}
s519::s519( s510 pv_, const vector<wstring>& s521 )
: pv( pv_ ){
for( auto p : s521 ) {
if( p.empty() )
throw new s16( L"empty values in permissions list are not allowed" );
if( p[0] == L'"' ) {
if( p.size() < 3 || p[p.size()-1] != L'"' )
throw new s16( L"unmatched quotes in a value in permission list" );
p = p.substr( 1, p.size() - 2 );}
s520.push_back( p );}}
s519::s519( s1890& ag_, s1890& s77 ){}
s510 s519::s558( s1890& s497 ) const{
for( size_t n = 0; n < s520.size(); ++n )
if( s520[n] == s497 || s520[n] == L"_" )
return pv;
if( pv == s513 )
return s512;
return s513;}
void s524::s527( s510 pv, s263* s695 ){
s263::s275& s696 = s695->s293();
s263::s275::iterator it = s696.begin();
for( ; it != s696.end(); ++it ) {
wstring l = it->second->s291().substr( 1, it->second->s291().size() - 2 );
vector<wstring> s153;
wstring s72( s1109, 1 );
s4::s57( l, s72, s153 );
s526[it->first] = new s519( pv, s153 );}}
void s524::s528( s1890& s, s519& pl ){}
void s524::s529( s1890& s, s1890& s522 ){}
s510 s524::s530( s1890& mem, s1890& s497 ){
s525::iterator it = s526.find( mem );
if( it == s526.end() )
return s511;
return it->second->s558( s497 );}
s1985 Types;
s1054 s1501::s1261 = 0;
s1054 s1501::s1538 = 0;
s334::s339 s382::s346;
s334::s339 s362::s346;
s334::s339 s359::s346;
s334::s339 s358::s346;
s334::s339 s344::s346;
s334::s339 s356::s346;
s334::s339 s1293::s346;
s334::s339 s1518::s346;
s334::s339 s1285::s346;
s334::s339 s1561::s346;
s334::s339 s1590::s346;
s334::s339 s357::s346;
s334::s339 s314::s346;
s334::s339 s744::s346;
s334::s339 s952::s346;
s334::s339 s322::s346;
s334::s339 s1371::s346;
s334::s339 s1282::s346;
s334::s339 s413::s346;
s334::s339 s383::s346;
s334::s339 s1125::s346;
s334::s339 s944::s346;
s334::s339 s1134::s346;
s334::s339 s1692::s346;
s334::s339 s648::s346;
s334::s339 s1787::s346;
s334::s339 s505::s346;
s334::s339 s1284::s346;
s334::s339 s1292::s346;
s334::s339 s1391::s346;
s334::s339 s1393::s346;
s334::s339 s2047::s346;
s334::s339 s2204::s346;
s334::s339 s2237::s346;
size_t s334::s752 = 0;
s9<s362> s363;
s9<s382> s866;
s9<s382> s364;
s9<s382> s365;
s9<s382> s366;
s9<s382> s867;
s9<s382> s1672;
s9<s382> s2131;
s9<s358> s367;
s9<s358> s368;
s9<s1391> s1392;
s9<s1393> s1394;
s9<s382> s1510;
template <class charT, charT s72>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s72; }
};
std::locale exprloc;
static s6::s1695 s1744;
s1706 s1724;
s6::s1681 s1722;
const s481* s1985::operator()( s262* s300, s1054 tp ){
return s300->TR().s1000( tp );}
void s334::s778( s262* s300, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
Types.No = s300->s218( new s382( s300 ), L"NoValue" );
Types.Null = s300->s218( new s362( s300 ), L"Null" );
Types.s359 = s300->s218( new s359( s300 ), L"Exception" );
Types.Bool = s300->s218( new s358( s300 ), L"Bool" );
Types.Int = s300->s218( new s344( s300 ), L"Int" );
Types.Double = s300->s218( new s356( s300 ), L"Double" );
Types.Long = s300->s218( new s1293(s300), L"Long" );
Types.s1517 = s300->s218( new s1518( s300 ), L"ULong" );
Types.Byte = s300->s218( new s1285( s300 ), L"Byte" );
Types.Char = s300->s218( new s1561( s300 ), L"Char" );
Types.s272 = s300->s218( new s1590( s300 ), L"Object" );
Types.Position = s300->s218( new s1134( s300 ), L"Position" );
Types.DateTime = s300->s218( new s1692( s300 ), L"DateTime" );
Types.Vector = s300->s218( new s314( s300 ), L"Vector" );
Types.s742 = s300->s218( new s744( s300 ), L"UntypedVector" );
Types.Tuple = s300->s218( new s952( s300 ), L"Tuple" );
Types.Set = s300->s218( new s2204( s300 ), L"Set" );
Types.HashSet = s300->s218( new s2237( s300 ), L"HashSet" );
Types.Index = s300->s218( new s322( s300 ), L"Index" );
Types.HashIndex = s300->s218( new s1371( s300 ), L"HashIndex" );
Types.ByteArray = s300->s218( new s1282( s300 ), L"ByteArray" );
Types.s412 = s300->s218( new s413( s300 ), L"Directory" );
Types.Range = s300->s218( new s383( s300 ), L"Range" );
Types.Filter = s300->s218( new s1125( s300 ), L"Filter" );
Types.Seq = s300->s218( new s944( s300 ), L"Seq" );
Types.Table = s300->s218( new s1787( s300 ), L"Table" );
Types.TSDBase = s300->s218( new s648( s300 ), L"TSDBase" );
Types.s783 = s300->s218( new s505( s300 ), L"StringStream" );
Types.ByteStream = s300->s218( new s1284( s300 ), L"ByteStream" );
Types.FileStream = s300->s218( new s1292( s300 ), L"FileStream" );
Types.Lambda = s300->s218( new s832( s300 ), L"Lambda" );
Types.String = s300->s218( new s357( s300 ), L"String" );
if( !soft )
s752 = Types.String;
if( s363.s13() ) {
s363 = new s362( s300 );
s866 = new s382( s300, NULL, s479 );
s366 = new s382( s300, NULL, s479 );
s365 = new s382( s300, NULL, s479 );
s364 = new s382( s300, NULL, s479 );
s867 = new s382( s300, NULL, s479 );
s1672 = new s382( s300, NULL, s479 );
s2131 = new s382( s300, NULL, s479 );
s367 = new s358( s300, true );
s368 = new s358( s300, false );
s866->s1665( s7::s860 );
s366->s1665( s7::s436 );
s365->s1665( s7::s437 );
s364->s1665( s7::s438 );
s367->s1250();
s368->s1250();
s1510 = new s382( s300, NULL, Types.Int, s1236 );
s1722.s151 = true;
s1722.s1718 = true;
s1722.s1686 = true;
s1722.s1685 = true;
s1722.s1687 = true;}}
s1113::s1113( const std::vector<s483>& v, s334* s590 )
:s586( s590 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s492() != s1056 ) {
s906.push_back( v[n] );
s1268.push_back( v[n]->s350() );}
else if( n > 1 )
break;}}
bool s1113::operator==( const s1113& s522 ) const{
bool pend = s1268.empty();
bool send = s522.s1268.empty();
s1054 starred = 0;
size_t n = 0, k = 0;
bool s1260 = true;
s489* ptr = s522.s586 ? &s522.s586->Pass()->TR() : NULL;
while( !send || !pend ) {
if( send && !starred ) // ???DEBUG??? 220821
throw new s16( L"too few arguments" );
s1260 = false;
s1054 s1168 = starred ? starred : (pend ? 0 : s1268[k]);
s1054 s1165 = send ? (s522.s1268.empty() ? 0 : s522.s1268[n-1]) : s522.s1268[n];
s271* s1526 = send ?
( s522.s906.empty() ? NULL : s522.s906[n - 1].s15<s271*>() ) :
s522.s906[n].s15<s271*>();
if( s1165 == Types.No )
s1165 = send ? s522.s906[n-1].s15<s382*>()->s1529() : 
s522.s906[n].s15<s382*>()->s1529();
const s807* s1271 = s522.s586 ? &s522.s586->s1187() : NULL;
if( s1168 >= s7::s1388 && s1168 < s7::s1542 && s1165 ) {
if( s1168 == s7::s1382 )
s1260 = true;
else if( s1168 == s7::s1387 ) {
s1054 pt1_ = s522.s906[n]->s1187().s350();
if( pt1_ == s1702 /*&& pt2_ == Types.Bool*/ )
s1260 = true;}
else if( s1168 == s7::s1383 ) {
if( s522.s586 && s1165 == s522.s586->s350())
s1260 = true;}
else if( s1168 == s7::s1384 ) {
if( s522.s586 && s1165 == ( (s324*)s522.s586 )->s317() )
s1260 = true;}
else if( s1168 == s7::s1384 ) {
if( s522.s586 && s1165 == ((s324*)s522.s586)->s317() )
s1260 = true;}
else if( s1168 == s7::s1385 ) {
if( s522.s586 && s1165 == ((s324*)s522.s586)->s931() )
s1260 = true;}
else if( s1168 == s7::s1386 ) {
if( s522.s586 && s1526->s1530( ((s324*)s522.s586)->ValType() ) )
s1260 = true;}
else if( s1271 &&	s1165 == s1271->s350( (size_t)((int)0 - s1168 )) )
s1260 = true;}
else if( s1168 >= s7::s1542 && ptr ) {
traitnum_t s1502 = ptr->s1447( s1168 );
if( s1165 && ptr->s1189( s1165, s1502 ) )
s1260 = true;}
else {
if( s1526 && s1526->s1530( s1168 ) )
s1260 = true;}
if( s1260 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s522.s1268.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1268.size() )
pend = true;
if( !starred && !pend && s1268[k] == s7::s1388 )
starred = s1268[k - 1];}
return s1260;}
bool s1113::operator<( const s1113& s522 ) const{
if( s1268.empty() ) return s522.s1268.size() > 0;
if( s522.s1268.empty() ) return false;
const s807* s1270 = s586 ? &s586->s1187() : NULL;
const s807* s1271 = s522.s586 ? &s522.s586->s1187() : NULL;
s1054 s1258 = 0, s1259 = 0;
s489* ptr = s522.s586 ? &s522.s586->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1268.size() && n < s522.s1268.size()*/; ++n ) {
if( s1268.size() == n )
return s522.s1268.size() > n;
if( s522.s1268.size() == n )
return false;
s1054 s1167 = s1258 ? s1258 : s1268[n];
s1054 s1169 = s1259 ? s1259 : s522.s1268[n];
if( s1167 >= s7::s1388 && s1167 <= s7::s1542 ) {
if( s1167 == s7::s1388 )
s1167 = s1258 = s1268[n - 1];
else if( s1167 == s7::s1382 )
continue;
else if( s1167 == s7::s1383 ) {
if( !s522.s586 )
return true;
s1167 = s522.s586->s350();}
else if( s1167 == s7::s1384 ) {
if( !s522.s586 )
return true;
s1167 = ( (s324*)s522.s586 )->s317();}
else if( s1270 )
s1167 = s1270->s350( (size_t)(int)0 - s1167 );}
else if( s1167 >= s7::s1542 && ptr ) {
traitnum_t s1502 = ptr->s1447( s1167 );
if( ptr->s1189( s1169, s1502 ) )
return true;}
if( s1169 >= s7::s1388 && s1169 <= s7::s1542 ) {
if( s1169 == s7::s1388 )
s1169 = s1259 = s522.s1268[n - 1];
else if( s1169 == s7::s1382 )
continue;
else if( s1169 == s7::s1383 ) {
if( !s586 )
return true;
s1169 = s586->s350();}
else if( s1169 == s7::s1384 ) {
if( !s586 )
return true;
s1169 = ( (s324*)s586 )->s317();}
else if( s1271 )
s1169 = s1271->s350( (size_t)(int)0 - s1169 );}
else if( s1169 >= s7::s1542 && ptr ) {
traitnum_t s1502 = ptr->s1447( s1169 );
if( ptr->s1189( s1167, s1502 ) )
return true;}
if( s1167 < s1169 )
return true;}
return false;}
wstring s1113::s1319( s262* s300 ) const{
wstring s681 = L"( ";
for( auto i : s1268 ) {
s681 += s300->TR().s798( i );
if( s681.back() != L')' ) s681 += L"()";
s681 += L" ";}
s681 += L")";
return s681;}
bool
s334::s335::s1157( /*s334* thi,*/ const s1113& s687 ) const
{
return std::find( s1154.begin(), s1154.end(), s687 ) != end( s1154 );}
s1054
s334::s384( s1890& s341 ) const{
auto it = s340().find( s341 );
if( it == s340().end() )
throw new s16( L"No such operation: " + s351() +	L"::" + s341,
(uint32_t)s16::s17::s23 );
s1054 s681 = it->second->s493();
return s681;}
const s481*
s334::s501() const{
return (s481*)s300->TR().s1000( s350() );}
const vector<wstring>& 
s334::s1182( s1890& s341 ) const{
auto ran = s340().equal_range( s341 );
if( ran.first == s340().end() )
throw new s16( L"No such method: " + s351() + L"::" + s341,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1133 s334::s1188( s1890& s341 ) const{
s334::s335* s681 = NULL;
auto it = s340().find( s341 );
if( it != s340().end() )
s681 = it->second;
return s681 ? s1133( s681->s493(), s681->s1127(), s681->s1194(),
s681->s2002() ) : s1133();}
s1133
s334::s1183( s1890& s341, s1113& ap /*const vector<s1054>& s1230*/ ) const
{
auto ran = s340().equal_range( s341 );
if( ran.first == s340().end() )
throw new s16( L"No such method: " + s351() + L"::" + s341,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1177() )
throw new s16( L"", (uint32_t)s335::s1124::s1171 );
s335* s681 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1157( ap ) ) {
s681 = it->second;
break;}}
return s681 ? s1133( s681->s493(), s681->s1127(), s681->s1194(),
s681->s2002() ) : s1133();}
s1133
s334::s1178( s1890& s341, s1113& ap ){
auto ran = s340().equal_range( s341 );
s335* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1157( ap ) ) {
mi = it->second;
break;}}
if( !mi )
throw new s16( L"method '" + s300->TR().s1342( s351() ) + L"::" + s341 + 
ap.s1319( s300 ) + L"' is not resolved" );
s1133 s1228( mi->s493(), mi->s1127(), mi->s1194(), mi->s2002() );
s1228.s336 = ap.Subj()->s1179( s341, ap.s600() );
return s1228;}
s484 s334::s495( s481** s274, size_t s496 ){
return this;}
void s334::s1524( s481* p ){}
s481* s334::s343( s262* s300, s1890& s347, s1890& s332 ){
s263 s208( s347, NULL, NULL );
s481* s681 = NULL;
double dval;
size_t pos = 0;
s6::s131 s198 = s1744.s1539( s347, pos, dval );
if( s198 != s6::s131::s140 && s198 != s6::s131::s136 )
return NULL;
if( s347.find( L"." ) != std::string::npos )
s681 = ((s356*)Types( s300, Types.Double ))->s352( s208, NULL, s332 );
else {
s681 = ((s344*)Types( s300, Types.Int ))->s352( s208, NULL, s332 );
if( !s681 ) {
if( !s681 )
s681 = ((s1293*)Types( s300, Types.Long ))->s352( s208, NULL, s332 );
if( !s681 )
s681 = ((s1285*)Types( s300, Types.Byte ))->s352( s208, NULL, s332 );}}
return s681;}
#define s692 ((s344*)(s482*)*s274)
#define s693 ((s358*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
s481* s356::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
1/*s.find( L"." ) != std::string::npos*/ ) {
size_t pos = 0;
return new s356( s300, s, pos );}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s356( s300, s4::s52( s.substr( 7, s.size() - 8 ), s4::s48 ),
pos );}
else if( s.find( L"Double" ) == 0 ) {
return s353( s586, std::vector<s271*>(), &s695 );}
return 0;}
s356::s356( s262* s300, double d ) 
: s334( s300, NULL, NULL ), s347( d ){
if( !Types.Double ) {
s491 = 0;
wh = s7::s862;}
else {
s491 = Types.Double;
wh = s7::s861;}}
s356::s356( const s356& r )
: s334( r.s300, r.ns, r.s601() ), s347( r.s347 ){
wh = r.wh;
s491 = r.s491;}
double s1927( s1890& s, size_t& pos ){
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
s356::s356( s262* s300, s1890& s, size_t& pos )
: s334( s300, NULL, NULL ){
if( !s.empty() ) {
s347 = s1927( s, pos );
s1665( s7::s861 );}
else
s347 = s300->TR().s1241();
s491 = Types.Double;}
s481* s356::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s356( s300, L"", pos );}
void s356::s498( const s272*, bool ){
s1252();}
void s356::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s356::s1227, Types.Double,
{ s1113(), s1113( { Types.String } ), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"abs", new s335( L"abs", &s356::s402, Types.Double,
{ s1113( ) }, 0, 0 )));
s346.insert( make_pair( L"set", new s335( L"set", &s356::s385, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"sum", new s335( L"sum", &s356::s386, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"dif", new s335( L"dif", &s356::s387, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"mul", new s335( L"mul", &s356::s388, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"div", new s335( L"div", &s356::s389, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"pow", new s335( L"pow", &s356::s390, Types.Double,
{ s1113( { s1501::s1261 } ) }, 1, 1 )));
s346.insert( make_pair( L"sumeq", new s335( L"sumeq", &s356::s391, Types.Double,
{ s1113( { Types.Double } ), s1113( { Types.Int, s7::s1388 } ) }, 1, 10 )));
s346.insert( make_pair( L"difeq", new s335( L"difeq", &s356::s392, Types.Double,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"muleq", new s335( L"muleq", &s356::s393, Types.Double,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"diveq", new s335( L"diveq", &s356::s394, Types.Double,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"poweq", new s335( L"poweq", &s356::s395, Types.Double,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"sqrt", new s335( L"sqrt", &s356::s404, Types.Double,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"nroot", new s335( L"nroot", &s356::s405, Types.Double,
{ s1113( { Types.Int } ) }, 1, 1 )));
s346.insert( make_pair( L"eq", new s335( L"eq", &s356::s396, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"less", new s335( L"less", &s356::s397, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"greater", new s335( L"greater", &s356::s398, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"leq", new s335( L"leq", &s356::s399, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"geq", new s335( L"geq", &s356::s400, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"neq", new s335( L"neq", &s356::s401, Types.Bool,
{ s1113( { Types.Double } ) }, 1, 1 )));
s346.insert( make_pair( L"dcmp", new s335( L"dcmp", &s356::s408, Types.Int,
{ s1113( { Types.Double, Types.Double } ) }, 2, 2 )));
s346.insert( make_pair( L"dcmpr", new s335( L"dcmpr", &s356::s409, Types.Int,
{ s1113( { Types.Double, Types.Double } ) }, 2, 2 )));
s346.insert( make_pair( L"floor", new s335( L"floor", &s356::s2198, Types.Double,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"ceil", new s335( L"ceil", &s356::s2196, Types.Double,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"to-Int", new s335( L"to-Int", &s356::s410, Types.Int,
{ s1113(), s1113( { Types.Int } ) }, 0, 1 )));
s346.insert( make_pair( L"incr", new s335( L"incr", &s356::s1963, Types.Double,
{ s1113( ) }, 0, 0 )));
s346.insert( make_pair( L"decr", new s335( L"decr", &s356::s1962, Types.Double,
{ s1113( ) }, 0, 0 )));
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );}
s271* s356::s333( s589* s2042, s272* impl ) const{
return new s356( *this );}
void s356::s354( s271* p ) const{
if( p->s350() == Types.Int )
*( (s344*)p )->s355() = (int)s347;
else if( p->s350() == Types.Double )
*( (s356*)p )->s355() = s347;
else if( p->s350() == Types.Bool )
*( (s358*)p )->s355() = ( s347 != 0.0 );
else
throw new s16( L"No conversion to type " + s351() );}
std::wstring s356::to_wstring( uint32_t s1553 ) const{
wstringstream ss;
wstring s681;
int prec = s1553 << 28 >> 28;
if( prec ) {
ss << setprecision( prec ) << s347;
s681 = ss.str();}
else {
wstring s = std::to_wstring( s347 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
s681 = s.substr(0, pl);}
return s681;}
void s356::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
/*	auto flags = s1919->s1915();
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss.precision( s1919->s1916() );
*/
ss << s347;}
void s356::s1945( s1890& s ){
size_t pos = 0;
s347 = s1927( s, pos );}
void s356::s1944( Stream* s1919 ){
s1486& ss = s1919->s1948();
ss >> s347;}
#undef s692
#define s692 ((s356*)(s482*)*s274)
#define INTRES ((s344*)(s482*)*s274)
inline void s356::s1227( s481** s274, size_t s496 ){
s356* plv = NULL;
if( s496 == 3 && s274[2]->s350() == Types.String ) {
size_t pos = 0;
plv = new s356( ((s356*)s274[1] )->s300, *((s357*)s274[2])->s355(), pos );}
else {
plv = new s356( ( (s356*)s274[1] )->s300, 0.0 );
s356& lv = *plv;
if( s496 == 2 )
lv.s347 = 0;
else if( s496 == 3 ) {
s481* p = s274[2];
if( p->s350() == Types.Double )
lv.s347 = *( (s356*)p )->s355();
else if( p->s350() == Types.Int )
lv.s347 = (s1375)*( (s344*)p )->s355();
else if( p->s350() == Types.Bool )
lv.s347 = ( s1375 )*( (s358*)p )->s355();
else
throw new s16( L"no conversion to Double from type: " + p->s351() );}
else
throw new s16( L"unknown parameters to Double() constructor" );}
plv->s1252();
s274[0] = plv;}
inline void s356::s385( s481** s274, size_t s496 ){
( (s356*)DR )->s347 = (double)*PARN( 2 );}
void s356::s402( s481** s274, size_t s496 ){
double t = (double)*DR;
if( t >= 0 )
s692->s347 = t;
else
s692->s347 = -t;}
void s356::s1963( s481** s274, size_t s496 ){
double s681 = (double)*DR;
if (isnan( s681 ) || s681 == -INFINITY || s681 == INFINITY) (void)0;
else if ( s681 == 0.0 ) s681 = DBL_EPSILON;
else {
union s1959 {
int64_t i;
double f;
}conv;
conv.f = s681;
conv.i++;
s681 = conv.f;}
s692->s347 = s681;}
void s356::s1962( s481** s274, size_t s496 ){
double s681 = (double)*DR;
if (isnan( s681 ) || s681 == -INFINITY || s681 == INFINITY) (void)0;
else if ( s681 == 0.0 ) s681 = DBL_EPSILON;
else {
union s1959 {
int64_t i;
double f;
}conv;
conv.f = s681;
conv.i--;
s681 = conv.f;}
s692->s347 = s681;}
inline void s356::s388( s481** s274, size_t s496 ){
s692->s347 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
s692->s347 *= (double)*PARN( n );}
inline void s356::s386( s481** s274, size_t s496 ){
s692->s347 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
s692->s347 += (double)*PARN( n );}
inline void s356::s389( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
s692->s347 = ( (s356*) DR )->s347 / s692->s347;
}
inline void s356::s387( s481** s274, size_t s496 ){
s692->s347 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
s692->s347 -= (double)*PARN( n );}
inline void s356::s391( s481** s274, size_t s496 ){
s356* pd = (s356*) s274[1];
for( size_t n = 2; n < s496; ++n ) {
s481* p = s274[n];
if( p->s350() == Types.Double )
pd->s347 += *( (s356*)p )->s355();
else if( p->s350() == Types.Int )
pd->s347 += ( s1375 )*( (s344*)p )->s355();}
s692->s347 = ( (double)*DR );}
inline void s356::s392( s481** s274, size_t s496 ){
( (s356*)DR )->s347 -= (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
( (s356*)DR )->s347 -= (double)*PARN( n );
s692->s347 = ( (double)*DR );}
inline void s356::s393( s481** s274, size_t s496 ){
( (s356*)DR )->s347 *= (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
( (s356*)DR )->s347 *= (double)*PARN( n );
s692->s347 = ( (double)*DR );}
inline void s356::s394( s481** s274, size_t s496 ){
( (s356*)DR )->s347 /= (double)*PARN( 2 );
for( size_t n = 3; n < s496; ++n )
( (s356*)DR )->s347 /= (double)*PARN( n );
s692->s347 = ( (double)*DR );}
inline void s356::s395( s481** s274, size_t s496 ){
( (s356*)DR )->s347 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s496; ++n )
( (s356*)DR )->s347 = ::pow( (double)*DR, (double)*PARN( n ) );
s692->s347 = ( (double)*DR );}
inline void s356::s396( s481** s274, size_t s496 ){
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s397( s481** s274, size_t s496 ){
if( ((double)*DR) < (double)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s398( s481** s274, size_t s496 ){
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s399( s481** s274, size_t s496 ){
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s400( s481** s274, size_t s496 ){
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s401( s481** s274, size_t s496 ){
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s356::s404( s481** s274, size_t s496 ){
s692->s347 = ::sqrt((double)*DR);}
inline void s356::s405( s481** s274, size_t s496 ){
*( (s356*)s274[0] )->s355() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s356::s408( s481** s274, size_t s496 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s355() = 0;
else
*INTRES->s355() = 1;}
else {
if( dr - dl <= diff )
*INTRES->s355() = 0;
else
*INTRES->s355() = -1;}}
inline void s356::s409( s481** s274, size_t s496 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s355() = 0;
else
*INTRES->s355() = 1;}
else {
if( dr / dl - 1 <= diff )
*INTRES->s355() = 0;
else
*INTRES->s355() = -1;}}
inline void s356::s390( s481** s274, size_t s496 ){
s692->s347 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );}
inline void s356::s2198( s481** s274, size_t s496 ){
double dv = ( (s356*)DR )->s347;
*( (s356*)s274[0] )->s355() = floor( dv );}
inline void s356::s2196( s481** s274, size_t s496 ){
double dv = ( (s356*)DR )->s347;
*( (s356*)s274[0] )->s355() = ceil( dv );}
inline void s356::s410( s481** s274, size_t s496 ){
int s1321 = -1;
if( s496 == 3 )
s1321 = (int)*s274[2];
double dv = ( (s356*)DR )->s347;
int s681 = (int)dv;
if( s1321 < 0 )
*( (s344*)s274[0] )->s355() = s681;
else if( s1321 == 0 ) 
*( (s344*)s274[0] )->s355() = (dv - s681 > 0.5 ? s681 + 1 : s681);
else
*( (s344*)s274[0] )->s355() = s681 + 1;}
void s356::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << s347;}
size_t s356::s320() const{
return hash<double>{}( s347 );}
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
inline bool s356::operator==( const s481* p ) const{
return ( dcmp_( ( (s356*)p )->s347, s347, 0.00000001 ) == 0 ); // FIX:
}
inline bool s356::operator<( const s481* p ) const{
return ( dcmp_( s347, ( (s356*)p )->s347, 0.00000001 ) < 0 ); // FIX:
}
s358::s358( s262* s300, s1890& s, size_t& pos )
: s334( s300, NULL, NULL ){
if( s.empty() )
s347 = s300->TR().s1239();
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s347 = (s[0] == L'1');
pos++;}
else if( s.find( s7::s434 ) == 0 ) {
s347 = true;
pos += 4;}
else if( s.find( s7::s435 ) == 0 ) {
s347 = false;
pos += 5;}
else
throw new s16( L"unknown bool format: " + s.substr( 0, 20 ) );
if( !s.empty() )
s1665( s7::s861 );
s491 = Types.Bool;}
s358::s358( const s358& right )
: s334( right.s300, right.ns, NULL ), s347( right.s347 ){
s491 = Types.Bool;
wh = right.wh;}
s358::s358( s262* s300, bool b )
: s334( s300, NULL, NULL ), s347( b ){
if( !Types.Bool ) {
s491 = 0;
s1665( s7::s862 );}
else {
s491 = Types.Bool;
s1665( s7::s861 );}}
void s358::s348(){
s346.insert( make_pair( L"set", new s335( L"set", &s358::s385, Types.Null,
{ s1113( { Types.Bool } ) }, 1, 1, false )));
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s358::s1227, Types.Bool,
{ s1113(), s1113( { Types.Bool } ), s1113( { Types.String } ), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"not", new s335( L"not", &s358::s411, Types.Bool,
{ s1113( ) }, 0, 0, true )));
s346.insert( make_pair( L"eq", new s335( L"eq", &s358::s396, Types.Bool,
{ s1113( { Types.Bool } ) }, 1, 1, true )));}
void s358::s498( const s272* s873, bool ){
s1252();}
s481* s358::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s358( s300, false );}
s481* s358::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s4::s52( s695.s291(), s4::s48 );
if( s.find( s7::s434 ) == 0 || s.find( s7::s435 ) == 0 )
return new s358( s300, ( s.find( s7::s434 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s358( s300, 
s4::s52( s.substr( 5, s.size() - 6 ), s4::s48 ), pos );}
else if( s.find( L"Bool" ) == 0 ) {
return s353( s586, std::vector<s271*>(), &s695 );}
return NULL;}
s271* s358::s333( s589* s2042, s272* impl ) const{
return new s358( *this );}
void s358::s354( s271* p ) const{
if( p->s350() == Types.Bool )
((s358*)p)->s347 = s347;
else if( p->s350() == Types.Int )
*( (s344*)p )->s355() = (int)s347;
else if( p->s350() == Types.Double )
*( (s356*)p )->s355() = (double)s347;
else
throw new s16( L"No conversion to type " + s351() );}
#undef s692
#define s692 ((s358*)(s482*)*s274)
inline void s358::s1227( s481** s274, size_t s496 ){
s358* plv = new s358( ( (s358*)s274[1] )->s300, 0 );
s358& lv = *plv;
if( s496 == 2 )
lv.s347 = false;
else if( s496 == 3 ) {
s481* p = s274[2];
if( p->s350() == Types.Int )
lv.s347 = *( (s344*)p )->s355() != 0;
else if( p->s350() == Types.Double )
lv.s347 = *( (s356*)p )->s355() != 0.0;
else if( p->s350() == Types.Bool )
lv.s347 = *( (s358*)p )->s355();
else if( p->s350() == Types.String )
lv.s347 = ( (s357*)p )->s355()->size() > 0;
else
throw new s16( L"no conversion to Bool from type: " + p->s351() );}
else
throw new s16( L"unknown parameters to Bool() constructor" );
lv.s1252();
s274[0] = plv;}
inline void s358::s385( s481** s274, size_t s496 ){
( (s358*)DR )->s347 = ( (s358*)PARN( 2 ) )->s347;}
inline void s358::s411( s481** s274, size_t s496 ){
s692->s347 = !( (s358*)DR )->s347;}
inline void s358::s396( s481** s274, size_t s496 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
wstring s358::to_wstring( uint32_t s1553 ) const{
return ( s347 ? L"true" : L"false" ); }
void s358::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
ss << s347;}
void s358::s1945( s1890& s ){
if( s == L"true" || s == L"1" )
s347 = true;
else if( s == L"false" || s == L"0" )
s347 = false;
else
throw new s16( L"unknown bool value" );}
void s358::s1944( Stream* s1919 ){
s1486& ss = s1919->s1948();
ss >> s347;}
void s358::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << to_wstring()
<< L" (" << std::hex << &s347 << L")";}
size_t s358::s320() const{
return hash<bool>{}( s347 );}
inline bool s358::operator==( const s481* p ) const{
return ( s347 == ((s358*)p)->s347 );}
inline bool s358::operator<( const s481* p ) const{
return ( s347 < ((s358*)p)->s347 );}
vector<wstring> s2261( { L":general", L":stopIter" } );
s359::s359( s262* s300, s1890& s/* = std::wstring( L"" )*/ )
: s334( s300, NULL, NULL ), s2264( s2262 ), s78( s ){
wh = s7::s438;
s491 = Types.No == 0 ? 0 : Types.s359;}
s359::s359( const s359& r )
: s334( r.s300, NULL, NULL ), s2264( r.s2264 ), s78( r.s78 ){
s491 = r.s491;
wh = r.wh;}
void s359::create( const vector<s483>& l ){
s2264 = s2262;
if( l.size() ) {
if( l[0]->s492() == s473 ) {
s369* rf = l[0].s15<s369*>();
rf->s975( s2261 );
s2264 = (s2260) rf->s1294();}
if( l.back()->s492() == s472 )
s78 = l.back()->to_wstring();}}
void s359::s348(){
s346.insert( make_pair( L"report", new s335( L"report", &s359::s786, Types.Null,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"str", new s335( L"str", &s359::s506, Types.String,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"is-type", new s335( L"is-type", &s359::s2266, Types.Bool,
{ s1113() }, 0, 0, true, s2261 )));}
void s359::s498( const s272* s873, bool ){}
s481* s359::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s359( s300 );}
s271* s359::s333( s589* s2042, s272* impl ) const{
return new s359( *this );}
void s359::s354( s271* p ) const{
((s359*)p)->s2264 = s2264;
((s359*)p)->s78 = s78;}
s481* s359::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
if( s.find( L"Exception(" ) == 0 )
return new s359( s300, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s353( s586, std::vector<s271*>(), &s695 );
return NULL;}
#undef s692
#define s692 ((s359*)(s482*)*s274)
inline void s359::s786( s481** s274, size_t s496 ){
wcout << ( (s359*)DR )->s78;}
inline void s359::s506( s481** s274, size_t s496 ){
*( (s357*)s274[0] )->s355() = ( (s359*)DR )->s78;}
inline void s359::s2266( s481** s274, size_t s496 ){
s359* dr = (s359*)DR;
int idx = (int)*((s369*)s274[2])->s375();
if( dr->s2264 == (s2260)idx )
*( (s358*)s274[0] )->s355() = true;
else
*( (s358*)s274[0] )->s355() = false;}
void s359::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : -";}
size_t s359::s320() const{
throw new s16( L"9: not implemented" );}
bool s359::operator==( const s481* p ) const{
return ( (s359*)p )->s78 == s78;}
bool s359::operator<( const s481* p ) const{
return s78 < ( (s359*)p )->s78;}
s362::s362( s262* s300, s272* s586 ) 
: s334( s300, s586, NULL ){
if( !Types.Null ) {
s491 = 0;
s1665( s7::s862 );}
else {
s491 = Types.Null;
s1665( s7::s861 );}}
void s362::s498( const s272* s873, bool ){}
s481* s362::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s362( s300, s586 );}
s481* s362::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
if( s.find( L"Null" ) == 0 )
return s363;
return NULL;}
s271* s362::s333( s589* s2042, s272* impl ) const{
return (s271*)this;}
void s362::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : -";}
size_t s362::s320() const{
return 0xfeeb1e;}
bool s362::operator==( const s481* p ) const{
return ( this == p );}
bool s362::operator<( const s481* p ) const{
return false;}
s382::s382( s262* s300, s272* ns_, traitnum_t tn, s470 pc ) 
: s334( s300, ns_, NULL ), s1262( tn ){
s490 = pc;
s491 = Types.No == 0 ? 0 : Types.No; }
void s382::s498( const s272* s873, bool ){
ns = (s272*)s873;}
s481* s382::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s382( s300, s586 );}
s481* s382::s352( const s263& s695, s272* s586, s1890& s332 ) const{
throw new s16( L"no parser for NoValue" );
return NULL;}
s271* s382::s333( s589* s2042, s272* impl ) const{
return (s271*)this;}
inline bool
s382::s499( const s481* s500 ) const{
return s300->TR().s1189( s500->s350(), s1262 );}
inline bool
s382::s1530( s1054 s617 ) const{
return s300->TR().s1523( s1262, s617 );}
void s382::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : -" << endl;}
size_t s382::s320() const{
throw new s16( L"not implemented" );}
bool s382::operator==( const s481* p ) const{
return false;}
bool s382::operator<( const s481* p ) const{
return false;}
s1692::s1692( s262* s300 ) 
: s334( s300, NULL, NULL ), s1729( s1727 ) {
if( !Types.DateTime )
s491 = 0;
else
s491 = s1699;
s1665( s7::s862 );}
s1692::s1692( s262* s300, s1890& s )
: s334( s300, NULL, NULL ){
if( !s1714( s, s347, s1729 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1860 = s1781::from_time_t ( std::mktime( &s347 ) );
s491 = s1699;
s1665( s7::s861 );}
s1692::s1692( const s1692& right )
: s334( right.s300, right.ns, NULL ), s1729( right.s1729 ), 
s347( right.s347 ), s1860( right.s1860 ){
s491 = right.s491;
wh = right.wh;}
s1692::s1692( s262* s300, const std::tm& _t, s1691 s617 )
: s334( s300, NULL, NULL ), s1729( s617 ), s347( _t ){
s491 = s1699;
s1860 = s1781::from_time_t ( std::mktime( &s347 ) );
s1665( s7::s861 );}
wregex s1692::s1751( LR"regex(^\"?(\d\d\d\d-\d\d?-\d\d?)\"?$)regex" );
wregex s1692::s1849( LR"regex(^(\d+)(\.\d+)?$)regex" );
bool 
s1692::s1714( s1890& s347, std::tm& t, s1691& s617 ) const{
wsmatch s1067;
s617 = s1727;
if( regex_match( s347, s1067, s1751 ) ) {
std::wistringstream ss( s1067[1] );
ss >> std::get_time( &t, L"%Y-%m-%d" );
if( ss.fail() )
return false;
s617 = s1725;}
else if( regex_match( s347, s1067, s1751 ) ) {}
else
return false;
return true;}
void s1692::s348(){
s346.insert( make_pair( L"set", new s335( L"set", &s1692::s385, Types.Null,
{ s1113( { s1699 } ), s1113( { Types.String } ) }, 1, 1, false ) ) );
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1692::s1227, s1699,
{ s1113(), s1113( { s1699 } ), s1113( { Types.String } ), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"not", new s335( L"not", &s1692::s411, Types.Bool,
{ s1113() }, 0, 0, true ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s1692::s396, Types.Bool,
{ s1113( { s1699 } ) }, 1, 1, true ) ) );
s346.insert( make_pair( L"now-delta", new s335( L"now-delta", &s1692::s1835, Types.Double,
{ s1113( ) }, 0, 0, true ) ) );
s346.insert( make_pair( L"set-now", new s335( L"set-now", &s1692::s1858, s1699,
{ s1113( ) }, 0, 0, false ) ) );}
void s1692::s498( const s272* s873, bool ){
s1252();}
s481* s1692::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1692( s300 );}
s481* s1692::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s4::s52( s695.s291(), s4::s48 );
if( s.find( L"DateTime(" ) == 0 )
s = s.substr( 9, s.size() - 10 );
if( s.empty() )
return new s1692( s300 );
std::tm t = {};
s1691 s617;
if( s1714( s, t, s617 ) )
return new s1692( s300, t, s617 );
return NULL;}
s271* s1692::s333( s589* s2042, s272* impl ) const{
return new s1692( *this );}
void s1692::s354( s271* p ) const{
if( p->s350() == s1699 )
( (s1692*)p )->s347 = s347;
else
throw new s16( L"No conversion to type " + s351() );}
void s1692::s1945( s1890& s ){
std::tm t = {};
s1691 s617;
if( !s1714( s, t, s617 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1729 = s617;
s347 = t;
s1665( s7::s861 );}
#undef s692
#define s692 ((s1692*)(s482*)*s274)
inline void s1692::s1227( s481** s274, size_t s496 ){
s1692* s681 = NULL;
if( s496 == 2 )
s681 = new s1692( ( (s1692*)s274[1] )->s300 );
else if( s496 == 3 ) {
s481* p = s274[2];
if( p->s350() == s1699 )
s681 = new s1692( *(s1692*)s274[2] );
else if( p->s350() == Types.String )
s681 = new s1692( ( (s1692*)s274[1] )->s300, s274[2]->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s351() );}
else
throw new s16( L"unknown parameters to DateTime() constructor" );
s274[0] = s681;}
inline void s1692::s385( s481** s274, size_t s496 ){
s481* p = s274[2];
if( p->s350() == s1699 ) {
( (s1692*)DR )->s347 = ( (s1692*)p )->s347;
( (s1692*)DR )->s1729 = ( (s1692*)p )->s1729;
( (s1692*)DR )->wh = ( (s1692*)p )->wh;}
else if( p->s350() == Types.String )
( (s1692*)DR )->s1945( p->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s351() );}
inline void s1692::s411( s481** s274, size_t s496 ){
*s693->s355() = !(( (s1692*)DR )->s1729 == s1727);}
inline void s1692::s396( s481** s274, size_t s496 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s693->s355() = 1;
else
*s693->s355() = 0;}
inline void s1692::s1858( s481** s274, size_t s496 ){
s1692* p = (s1692*)DR;
p->s1860 = s1781::now();
time_t t = s1781::to_time_t( p->s1860 );
#ifdef WIN32
localtime_s( &p->s347, &t );
#else
p->s347 = *localtime( &t );
#endif
p->s1729 = s1726;}
inline void s1692::s1835( s481** s274, size_t s496 ){
s1692* p = (s1692*)DR;
std::chrono::duration<double> delta = s1781::now() - p->s1860;
*((s356*)s274[0])->s355() = delta.count();}
void s1692::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << to_wstring()
<< L" (" << std::hex << &s347 << L")";}
size_t s1692::s320() const{
std::tm t = s347;
return hash<time_t>{}( std::mktime( &t ) );}
inline bool s1692::operator==( const s481* p ) const{
return memcmp( &s347, &((s1692*)p )->s347, sizeof(tm) );}
inline bool s1692::operator<( const s481* p ) const{
tm t = s347, t1 = ( (s1692*)p )->s347;
return ( std::mktime( &t ) < std::mktime( &t1 ) );}
wstring s1692::to_wstring( uint32_t s1553 ) const{
wstring s681;
if( s1729 == s1725 || s1729 == s1726 ) {
s681 = std::to_wstring( 1900 + s347.tm_year ) + L"-";
if( s347.tm_mon < 9 )
s681 += L"0";
s681 += std::to_wstring( 1 + s347.tm_mon ) + L"-";
if( s347.tm_mday < 10 )
s681 += L"0";
s681 += std::to_wstring( s347.tm_mday );}
if( s1729 == s1726 )
s681 += L" ";
if( s1729 == s1728 || s1729 == s1726 ) {
if( s347.tm_hour < 10 )
s681 += L"0";
s681 += std::to_wstring( s347.tm_hour ) + L":";
if( s347.tm_min < 10 )
s681 += L"0";
std::to_wstring( s347.tm_min ) + L":";
if( s347.tm_sec < 10 )
s681 += L"0";
std::to_wstring( s347.tm_sec );}
return s681;}
s1590::s1590( s262* s300, s272* s586, s1890& s77, bool typed, const s263* ast_ )
: s334( s300, s586, ast_ ){
if( s77.size() )
load( s77, typed, false );
if( !s491 )
s491 = Types.s272;
if( !s77.empty() )
s1665( s7::s861 );}
s1590::s1590( s262* s300, s272* s586, const s143* s1632, const s263* ast_ )
: s334( s300, s586, ast_ ){
TDException s961( s7::CLObjectVal_ctor1, s926, ast_ );
if( s1632->s156( s7::s463 ) ) {
wstring sname = s4::s52( s263::s302( *s1632, s7::s463 ),
s48 );
(( s143*)s1632)->s159( L"name", new s141( sname ) );
(( s143*)s1632)->s1619( s7::s463 );}
try {
s1630( s1632, true, s480::s146 );}
catch( s16* e ) {
throw s961.s993( L"construction of TSD object failed: " + e->Msg() );}
s491 = Types.s272;
s1252();}
s1590::s1590( const s1590& right, s481* s2109 )
: s334( right.s300, (s272*)s2109, right.s601() ), s626( right.s626 ){
s491 = Types.s272;
wh = right.wh;}
void s1590::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1590::s1227, Types.s272,
{ s1113(), s1113( { s1144 } ), s1113( { Types.String, Types.Bool } ) }, 0, 2 ) ) );
s346.insert( make_pair( L"get-Int", new s335( L"get-Int", &s1590::s1624, Types.Int,
{ s1113( { Types.String } ) }, 1, 1, true )));
s346.insert( make_pair( L"get-String", new s335( L"get-String", &s1590::s1625, Types.String,
{ s1113( { Types.String } ) }, 1, 1, true )));
s346.insert( make_pair( L"load", new s335( L"load", &s1590::s1629, Types.Null,
{ s1113( { Types.String } ), s1113( { Types.String, Types.Bool } ) }, 1, 2, true )));
s346.insert( make_pair( L"load-from-file", new s335( L"load-from-file", &s1590::s1627, Types.Null,
{ s1113( { Types.String } ), s1113( { Types.String, Types.String } ) }, 1, 2, true )));}
void s1590::s498( const s272* s873, bool ){
s1252();}
s481* s1590::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1590( s300, s586, L"", ast_ );}
s481* s1590::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
if( s.find( L"Object(" ) == 0 ) {
return new s1590( s300, s586, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s353( s586, std::vector<s271*>(), &s695 );}
return NULL;}
s1054 s1590::s1179( s1890& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" ) {
auto it = s626.get( l[0]->to_wstring() );
s681 = it->s350();}
return s681;}
void s1590::load( s1890& s77, bool typed, bool s1622 ){
TDException s961( s7::s1586, s926, s601(), L"Failed to load object" );
s941 s1044 = new s938( s77, s1622 );
vector<s9<s143>> s660;
s1044->read( s660, L"" );
if( s660.size() != 1 )
throw s961.s993( L"wrong object data: the source contains " + std::to_wstring( s660.size() ) + L" objects"  );
s143* obj = s660[0];
if( obj->s156( s7::s463 ) ) {
wstring sname = s4::s52( s263::s302( *obj, s7::s463 ),
s48 );
obj->s159( L"name", new s141( sname ) );}
s1630( obj, typed );}
void s1590::s1630( const s143* obj, bool typed, s480::s145 ap ){
vector<pair<wstring, s142>> s144;
obj->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( typed ) {
s940 past = new s263( s144[n].first, *s144[n].second, NULL );
s481* dv = s300->TR().s516( *past, (s272*)this, L"::" );
dv->s504( s144[n].first );
dv->s1252();
s626.s539( s144[n].first, dv, ap );}
else {
s626.s539( s144[n].first, s144[n].second, ap );}}}
void s1590::s1620( s480::s533& sm ) const{
const s480::s533& tb = s626.Table();
s480::s533::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s492() == s474 )
(void)0;
else {
s481* dv = (s481*)it->second->s333(0,0);
sm.insert( make_pair( it->first, dv ));}}}
s271* s1590::s333( s589* s2042, s272* impl ) const{
return new s1590( *this, impl ? impl : ns );}
void s1590::s354( s271* p ) const{
if( p->s350() == Types.s272 )
((s1590*)p)->s626 = s626;
else
throw new s16( L"No conversion to type " + s351() );}
#undef s692
#define s692 ((s1590*)(s482*)*s274)
inline void s1590::s1227( s481** s274, size_t s496 ){
s1590* r = (s1590*)s274[1];
wstring sobj;
bool typed = true;
if( s496 > 2 ) {
sobj = ( (s357*)s274[2] )->s318();
if( s496 == 4 )
typed = (bool)*s274[3];}
s1590* s2134 = new s1590( r->s300, r->ns, sobj, typed );
s2134->s498( r->ns );
*s274 = (s481*)s2134;}
inline void s1590::s1624( s481** s274, size_t s496 ){
wstring s152 = s274[2]->to_wstring();
*((s344*)*s274)->s355() = (int)*( (s1590*)DR )->s626.get( s152 );}
inline void s1590::s1625( s481** s274, size_t s496 ){
wstring s152 = s274[2]->to_wstring();
*((s357*)*s274)->s355() = ( (s1590*)DR )->s626.get( s152 )->to_wstring();}
inline void s1590::s1646( s481** s274, size_t s496 ){
wstring s152 = s274[2]->to_wstring();
s344* pd  = (s344*)( (s1590*)DR )->s626.get( s152 );
*pd->s355() = (int)*s274[3];}
inline void s1590::s1648( s481** s274, size_t s496 ){
wstring s152 = s274[2]->to_wstring();
s357* pd  = (s357*)( (s1590*)DR )->s626.get( s152 );
*pd->s355() = s274[3]->to_wstring();}
inline void s1590::s1629( s481** s274, size_t s496 ){
s1590* po = (s1590*)DR;
wstring s77 = s274[2]->to_wstring();
bool typed = true;
if( s496 == 3 )
typed = (bool)*s274[2];
po->load( s77, typed, false );}
inline void s1590::s1627( s481** s274, size_t s496 ){
s1590* po = (s1590*)DR;
wstring s189 = s274[2]->to_wstring();
bool typed = true;
if( s496 == 3 )
typed = (bool)*s274[2];
po->load( s189, typed, true );}
size_t s1590::s320() const{
return (size_t)this; //hash<bool>{}( s347 );
}
inline bool s1590::operator==( const s481* p ) const{
return this == p; // ( s626 == ( (s1590*)p )->s626 );
}
inline bool s1590::operator<( const s481* p ) const{
return this < p; // ( s626 < ( (s1590*)p )->s626 );
}
wstring s1590::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"Object: { \n";
s681 += s626.to_wstring( s1553 );
s681 += L"\n }";
return s681;}
void s1590::s1945( s1890& s ) {
load( s, true, false );}
void s1590::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << endl;
s626.s304( pd, s197 + s417 );}
size_t s369::s2267 = 1;
s369::s369( s1890& s, s262* s300, s470 cat, bool _cnst )
: s482( s300, cat ), s370( s ), s374( 0 ), s1159( _cnst )//, s2283( false )
{
assert( cat == s471 || cat == s473 || cat == s479 || cat == s1056 );
if( cat == s471 ) {
if( 0 && s[0] == L':' ) {
s490 = s1056;
s491 = Types.No;
s371 = (s481*)Types( s300, Types.No );}
else if( s300->s221( *this ) ){
s490 = s479;
s491 = Types.No;}
else
s490 = s473;}}
s369::s369( const s369& right, s481* s2167 )
: s482( right.s300, right.s490 ), s370( right.s370 ),
s371( s2167 ? s2167 : right.s371 ), s372( right.s372 ), 
s373( right.s373 ),s374( right.s374 ), s1159( right.s1159 )//, s2283( right.s2283 )
{
if( s490 == s479 )
s371 = right.s371;
s491 = right.s491;
wh = right.wh;}
void s369::s2270(){
s370 += L"_@" + std::to_wstring( s2267++ );}
void s369::s498( const s272* s585, bool fr ){
if( false && s300->s221( *this ) ) {
s490 = s479;
s491 = Types.No;}
else if( s490 == s479 )
(void)0;
else {
if( !s585->s554( s370, this, s585->s2154(), fr ) ) {
if( s490 == s1056 )
return;
throw new TDException( (uint32_t)0, s924, NULL, s370 );}
if( s372 )
s491 = s372->s350();
else if( s490 == s1327 )
s491 = s371.s15<s369*>()->s375()->s350();
else
assert( 0 );}
s1252();}
void s369::reset(){
if( s492() == s1056 || 
s492() == s479 )
return;
s373.clear();
s374 = 0;
s372 = NULL;
s371 = NULL;}
const s483 s369::s379() {
if( s371.s14() && s371->s492() == s1327 )
return s371.s15<s1588*>()->s2103().s15<s482*>();
return s371; }
void s369::s380( s481* p ){
s371 = p; }
s481* s369::s375() const{
if( s490 == s1056 )
return s371.s15<s481*>();
else if( s490 == s1327 )
return s371.s15<s369*>()->s375();
if( s373.empty() )
return s371.s15<s481*>();
s482* s681 = NULL;
if( s371->s492() == s1327 )
s681 = s371.s15<s1588*>()->s596( *(size_t*)&s373[0] );
else
s681 = s371.s15<s272*>()->s596( *(size_t*)&s373[0] );	
for( size_t n = 1; n < s374; ++n )
s681 = ((s272*)s681->s494())->s596( *( (size_t*)&s373[0] + n ) );
return s681->s494();}
s481* s369::s376(){
if( s373.empty() )
return s371.s15<s481*>();
s481*	s681 = ((s481*)s371.s15<s272*>()->s596( *(size_t*)&s373[0] ));
for( size_t n = 1; n < s374; ++n )
s681 = (s481*)((s272*)s681)->s596( *( (size_t*)&s373[0] + n ) );
return s681;}
void s369::s975( const std::vector<std::wstring> &s814 ){
auto it = std::find( begin( s814 ), end( s814 ), s615() );
if( it != end( s814 ) ) {
s490 = s1056;
s491 = Types.No;
s374 = std::distance( begin( s814 ), it );
s371 = new s344( NULL, (int)s374 ); //s773.s15<s481*>();
}}
s484 s369::s495( s481** s274, size_t s496 ){
return s375()->s495( s274, s496 );}
s481* s369::s494(){
s483 s681 = s375();
if( s681.s14() )
return s681->s494();
else
return NULL;}
/*bool s369::s499( const s481* s500 ) const
{
if( s500->s492() == s473 )
return s375()->s499( ((s369*)s500)->s375() );
return s375()->s499( s500 );
}*/
s271* s369::s333( s589* s2042, s272* impl ) const{
s369* s681 = new s369( *this, NULL );
return s681;}
void s369::s2118( s589* s2042, s272* impl, bool s2160 ){
if( s490 != s1056 && (1 || s371.s14() )) {
reset();
s498( (s272*)s2042, s2160 );}}
void s369::s377( size_t off, const s481* proto ){
s373.push_back( off );
s374 = s373.size();
s372 = proto;}
void s369::s1333( s369* ptr ){
s490 = s1327;
s373.clear();
s374 = 0;
s371 = ptr;
s372 = NULL;}
void s369::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2141[20];
#ifdef WIN32		
_swprintf( s2141, L"%p", (uint64_t*)s371.s15<void*>() );
#else
swprintf( s2141, 20, L"%06x", (uint64_t*)s371.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s197 ) << L"DataRef : " << s370
<< L"; Root: " << s2141;
if( s373.size() )
buf << L"; off: " << s373[0];
buf << endl;
if( !s197 && s371.s14() ) {
buf << s4::fill_n_ch( L' ', s197 ) << L"RootPtr : " << endl;
s371->s304( pd, s197 + s417 );}}
void s1588::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2173[20];
#ifdef WIN32		
_swprintf( s2173, L"%p", (uint64_t*)pobj.s15<void*>() );
#else
swprintf( s2173, 20, L"%06x", (uint64_t*)pobj.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s197 ) << L"DataPointer : " 
<< L" Pointer: " << s2173 << endl;
if( pobj.s14() ) {
buf << s4::fill_n_ch( L' ', s197 ) << L"Object : " << endl;
pobj->s304( pd, s197 + s417 );}}
template<class s1302, class Der>
s334::s339 s1296<s1302, Der>::s346;
template<class s1302, class Der>
const s334::s339& s1296<s1302, Der>::s340() const{
return s346; }
template<class s1302, class Der>template <class s1519, class s1520>
void s1296<s1302, Der>::s1521( s481* src, s481* s772 ){
*((s1519*)s772)->s355() = (s1520) ( (Der*)src )->s347;}
template <class s1302, class Der>
s481* s1296<s1302, Der>::s1525( const s481* p ) const{
Der* s681 = new Der( p->Pass() );
if( p->s1530( s350() ) )
p->s354( s681 );
s681->s1252();
return s681;}
template <class s1302, class Der>
size_t s1296<s1302, Der>::s320() const{
return (size_t)s347;}
template <class s1302, class Der>
inline bool s1296<s1302, Der>::operator==( const s481* p ) const{
return ( (Der*)p )->s347 == s347;}
template <class s1302, class Der>
inline bool s1296<s1302, Der>::operator<( const s481* p ) const{
return s347 < ( (Der*)p )->s347;}
template <class s1302, class Der>
void s1296<s1302, Der>::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << s347 << endl;}
#define s1514 s491
template <class s1302, class Der>
void s1296<s1302, Der>::s348(){
s346.insert( make_pair( L"abs", new s335( L"abs", &s1296<s1302, Der>::s402, s1514,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"set", new s335( L"set", &s1296<s1302, Der>::s385, s1514,
{ s1113( { /*Der::proto->s350()*/ s1501::s1261 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"sum", new s335( L"sum", &s1296<s1302, Der>::s386, s1514,
{ s1113( { s1501::s1538, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"dif", new s335( L"dif", &s1296<s1302, Der>::s387, s1514,
{ s1113( ), s1113( { s1501::s1261, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"mul", new s335( L"mul", &s1296<s1302, Der>::s388, s1514,
{ s1113( { s1501::s1538, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"div", new s335( L"div", &s1296<s1302, Der>::s389, s1514,
{ s1113( { s1501::s1538, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"pow", new s335( L"pow", &s1296<s1302, Der>::s390, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"pow", new s335( L"pow", &s1296<s1302, Der>::s390, s1141,
{ s1113( { s1141 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"sumeq", new s335( L"sumeq", &s1296<s1302, Der>::s391, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"difeq", new s335( L"difeq", &s1296<s1302, Der>::s392, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"muleq", new s335( L"muleq", &s1296<s1302, Der>::s393, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"diveq", new s335( L"diveq", &s1296<s1302, Der>::s394, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"not", new s335( L"not", &s1296<s1302, Der>::s411, s1139,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s1296<s1302, Der>::s396, s1139,
{ s1113( { s1501::s1538, s7::s1388 } ), s1113( { s1143 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"less", new s335( L"less", &s1296<s1302, Der>::s397, s1139,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"greater", new s335( L"greater", &s1296<s1302, Der>::s398, s1139,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"leq", new s335( L"leq", &s1296<s1302, Der>::s399, s1139,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"geq", new s335( L"geq", &s1296<s1302, Der>::s400, s1139,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"neq", new s335( L"neq", &s1296<s1302, Der>::s401, s1139,
{ s1113( { s1501::s1538 } ), s1113( { s1143 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"within", new s335( L"within", &s1296<s1302, Der>::s2082, s1139,
{ s1113( { s1501::s1538, s1501::s1538 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"max", new s335( L"max", &s1296<s1302, Der>::s1950, s1514,
{ s1113( { s1501::s1538, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"min", new s335( L"min", &s1296<s1302, Der>::s1951, s1514,
{ s1113( { s1501::s1538, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"mod", new s335( L"mod", &s1296<s1302, Der>::s403, s1514,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"divrem", new s335( L"divrem", &s1296<s1302, Der>::s2294, s1514,
{ //s1113( { s1501::s1538 } ), 
s1113( { s1501::s1538, s1501::s1538, s1501::s1538 } ) }, 3, 3 ) ) );
s346.insert( make_pair( L"sqrt", new s335( L"sqrt", &s1296<s1302, Der>::s404, s1141,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"nroot", new s335( L"nroot", &s1296<s1302, Der>::s405, s1141,
{ s1113( { s1142 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"to-Double", new s335( L"to-Double", &s1296<s1302, Der>::s406, s1141,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"to-Byte", new s335( L"to-Byte", &s1296<s1302, Der>::s1584, s1298,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"to-Int", new s335( L"to-Int", &s1296<s1302, Der>::s410, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"to-Long", new s335( L"to-Long", &s1296<s1302, Der>::s1536, s1515,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"to-ULong", new s335( L"to-ULong", &s1296<s1302, Der>::s1537, s1516,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"to-String", new s335( L"to-String", &s1296<s1302, Der>::s1490, s1144,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"read", new s335( L"read", &s1296<s1302, Der>::s407, s1514,
{ s1113() }, 0, 0, false ) ) );}
template<class s1302, class Der>
s1054 s1296<s1302, Der>::
s1179( const std::wstring& s1541, const std::vector<s483>& l ) const{
s1054 s681 = 0;
if( 0 && s1541 == L"mod" )
s681 = this->s350();
return s681;}
#undef s692
#define s692 ((Der*)(s482*)*s274)
#define s693 ((s358*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
template<class s1302, class Der>
inline void s1296<s1302, Der>::s385( s481** s274, size_t n ){
s274[2]->s354( s274[1] );
s274[1]->s1252();
*s274 = s274[1];}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s402( s481** s274, size_t s496 ){
s1302 t = ( (Der*)DR )->s347;
if( t >= 0 )
s692->s347 = t;
else
s692->s347 = -t;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s386( s481** s274, size_t s496 ){
Der tmp;
s692->s347 = ( (Der*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
s692->s347 += tmp.s347;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s387( s481** s274, size_t s496 ){
Der tmp;
s692->s347 = ( (Der*)DR )->s347;
if( s496 == 2 )
s692->s347 = -s692->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
s692->s347 -= tmp.s347;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s388( s481** s274, size_t s496 ){
Der tmp;
s692->s347 = ( (Der*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
s692->s347 *= tmp.s347;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s389( s481** s274, size_t s496 ){
Der tmp;
s692->s347 = ( (Der*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
s692->s347 /= tmp.s347;
}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s390( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
s692->s347 =(s1302) std::pow( (double)( (Der*)DR )->s347, (double)s692->s347 );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s391( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
( (Der*)DR )->s347 += s692->s347;
s692->s347 = ( (Der*)DR )->s347;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s392( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
( (Der*)DR )->s347 -= s692->s347;
s692->s347 = ( (Der*)DR )->s347;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s393( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
( (Der*)DR )->s347 *= s692->s347;
s692->s347 = ( (Der*)DR )->s347;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s394( s481** s274, size_t s496 ){
s274[2]->s354( s274[0] );
( (Der*)DR )->s347 /= s692->s347;
s692->s347 = ( (Der*)DR )->s347;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s396( s481** s274, size_t s496 ){
bool s681 = true;
Der tmp;
for( size_t i = 2; i < s496; ++i ) {
s274[i]->s354( &tmp );
if( ( (Der*)DR )->s347 != tmp.s347 ) {
s681 = false;
break;}}
*s693->s355() = s681;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s411( s481** s274, size_t s496 ){
if( ((bool)( (Der*)DR )->s347) == false )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s397( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( ( (Der*)DR )->s347 < tmp.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s398( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( ( (Der*)DR )->s347 > tmp.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s399( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( ( (Der*)DR )->s347 <= tmp.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s400( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( ( (Der*)DR )->s347 >= tmp.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s401( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( ( (Der*)DR )->s347 != tmp.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s2082( s481** s274, size_t s496 ){
Der tmp, tmp1;
s274[2]->s354( &tmp );
s274[3]->s354( &tmp1 );
if( ( (Der*)DR )->s347 >= tmp.s347 && ((Der*)DR)->s347 <= tmp1.s347 )
*s693->s355() = true;
else
*s693->s355() = false;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1950( s481** s274, size_t s496 ){
Der tmp;
*s692->s355() = ( (Der*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
if( *s692->s355() < tmp.s347 )
*s692->s355() = tmp.s347;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1951( s481** s274, size_t s496 ){
Der tmp;
*s692->s355() = ( (Der*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
s274[n]->s354( &tmp );
if( *s692->s355() > tmp.s347 )
*s692->s355() = tmp.s347;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s403( s481** s274, size_t s496 ){
Der tmp;
s274[2]->s354( &tmp );
if( tmp.s347 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s692->s347 = ((Der*)DR)->s347 % tmp.s347;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s2294( s481** s274, size_t s496 ){
Der _div;
s274[2]->s354( &_div );
if( _div.s347 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
if( s496 == 5 ) {
s356 _dnum( s274[1]->Pass(), 0.0 );
s274[1]->s354( &_dnum );
double d = *_dnum.s355() / _div.s347;
std::int64_t _quot = (std::int64_t)floor( d );
((Der*)s274[3])->s347 = (s1302) _quot;
std::int64_t _rem = (std::int64_t)*_dnum.s355() - _quot * _div.s347;
((Der*)s274[4])->s347 = (s1302)_rem;
s274[3]->s1252();
s274[4]->s1252();
s692->s347 = (s1302)_rem;}}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s404( s481** s274, size_t s496 ){
*( (s356*)s274[0] )->s355() = ::sqrt( (double)*DR );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s405( s481** s274, size_t s496 ){
*( (s356*)s274[0] )->s355() = ::pow( ((Der*)DR)->s347, 1.0 / (double)*PARN( 2 ) );
}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s406( s481** s274, size_t s496 ){
*( (s356*)s274[0] )->s355() = (double)*DR;}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1584( s481** s274, size_t s496 ){
s274[1]->s354( s274[0] );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s410( s481** s274, size_t s496 ){
s274[1]->s354( s274[0] );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1536( s481** s274, size_t s496 ){
s274[1]->s354( s274[0] );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1537( s481** s274, size_t s496 ){
s274[1]->s354( s274[0] );}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s1490( s481** s274, size_t s496 ){
*( (s357*)s274[0] )->s355() = DR->to_wstring();}
template<class s1302, class Der>
inline void s1296<s1302, Der>::s407( s481** s274, size_t s496 ){
int i;
wstring s93 = L"";//( (s357*)s274[2] )->to_wstring();
wstring si = consutils::s100( s93, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s692->s347 = i;}
s344::s344( s262* s300, s272* s586 )
: s1296( s300, s586, NULL ){
s491 = Types.Int;
s347 = (s1375)s300->TR().s1247();
s1665( s7::s862 );}
s344::s344( s262* s300, int i, s272* s586 )
: s1296( s300, s586, NULL ){
if( !Types.Bool ) {
s491 = 0;
wh = s7::s862;}
else {
s491 = Types.Int;
s347 = i;
s1252();}}
s344::s344( const s344& r )
: s1296( r ){
s300->s2248( &r, this );}
s344::s344( s262* s300, s272* s586, const vector<s271*>& l, const s263* ast_ )
: s1296( s300, s586, ast_ ){
if( l.size() ) {
s2239* s274 = new s2239();
s274->assign( begin( l ), end( l ) );
s300->s2243( this, s274 );}
s491 = Types.Int;
s347 = (s1375)s300->TR().s1247();
s1665( s7::s862 );}
s344::s344( s262* s300, const std::wstring& s, size_t& pos, s272* s586 )
: s1296( s300, s586, NULL ){
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
s1252();}
else
s153 = s300->TR().s1247();
s347 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s491 = Types.Int;}
s344::~s344(){
if( s300 )
s300->s2249( this );}
s481* 
s344::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s_ = s695.s291();
size_t pos = 0;
if( s_.find( L"Int(" ) == 0 ) {
wstring s = s4::s52( s_.substr( 4, s_.size() - 5 ), s48 );
if( s.empty() )
return new s344( s300, s586 );
vector<s271*> s699;
s271::s1323( s695, s300, s586, s332, s699 );
return new s344( s300, s586, s699, &s695 );}
else {
if( s_ == L"-0" )
return s1510;
try {
return new s344( s300, s_, pos, s586 );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
return NULL;
else
throw e;}}
return NULL;}
void s344::s348(){
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );
s300->TR().s1153( s491, s7::s1513, s1501::s1538 );
s1296<int32_t, s344>::s348();
s346 = s1296<int32_t, s344>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s344::s1227, s1142,
{ s1113(), s1113( { Types.String } ), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"to-Char", new s335( L"to-Char", &s344::s2291, s1567,
{ s1113() }, 0, 0 ) ) );
s300->TR().s1522( s491, Types.Long );}
s481* s344::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s344( s300, s586, l, ast_ );}
void s344::s498( const s272* s873, bool ){
auto s274 = s300->s2249( this );
if( s274 ) {
assert( s274->size() == 1 );
for( size_t n = 0; n < s274->size(); ++n ) {
s483 par = s274->at( n );
if( par->s492() == s472 ) {
s347 = (int)*par;}
else if( par->s492() != s473 ) {
s483 s153 = s271::s1011( s300, par, ns, (s589*)ns, ns->s2154(), false );
if( s300->s1320() ) {
s347 = (int)*s153->s495( 0, 0 );}
else {
s274->at( n ) = s153;}}
else {
if( 1 || s300->s1320() /*par.s15<s369*>()->s379().s14()*/ ) {
if( par.s15<s369*>()->s379().s13() )
par->s498( s873, false );
s347 = (int)*par.s15<s369*>()->s375();}}}
delete s274;
s1252(); // ???DEBUG??? 220703
}}
inline bool
s344::s1530( s1054 s617 ) const{
if( ( s617 == s1516 && s347 >= 0 ) ||
( s617 == s1298 && s347 >= 0 && s347 <= 255 ) )
return true;
return s271::s1530( s617 );}
s271* s344::s333( s589* s2042, s272* impl ) const{
return new s344( *this );}
void s344::s354( s271* p ) const{
if( p->s350() == Types.Int )
*((s344*)p)->s355() = s347;
else if( p->s350() == s1298 )
*((s1285*)p)->s355() = s347;
else if( p->s350() == s1515 )
*((s1293*)p)->s355() = s347;
else if( p->s350() == s1516 )
*((s1518*)p)->s355() = s347;
else if( p->s350() == s1139 )
*( (s358*)p )->s355() = (s347 != 0);
else if( p->s350() == s1141 )
*( (s356*)p )->s355() = (double)s347;
else if( p->s350() == s1567 )
*( (s1561*)p )->s355() = (s1561::s1375)s347;
else
throw new s16( L"No conversion from " + s351() + L" to " + p->s351() );}
inline void s344::s1227( s481** s274, size_t s496 ){
s344* plv = NULL;
if( s496 == 3 && s274[2]->s350() == Types.String ) {
size_t pos = 0;
plv = new s344( ( (s344*)s274[1] )->s300, *( (s357*)s274[2] )->s355(), pos, 
( (s344*)s274[1] )->ns );
plv->s1252();}
else {
plv = new s344( ( (s344*)s274[1] )->s300, ( (s344*)s274[1] )->ns );
s344& lv = *plv;
if( s496 == 2 )
;// lv.s347 = 0;
else if( s496 == 3 ) {
s481* p = s274[2];
if( p->s350() == s1142 )
lv.s347 = *( (s344*)p )->s355();
else if( p->s350() == s1141 )
lv.s347 = ( s1375 )*( (s356*)p )->s355();
else if( p->s350() == s1139 )
lv.s347 = ( s1375 )*( (s358*)p )->s355();
else
throw new s16( L"no conversion to Int from type: " + p->s351() );
plv->s1252();}
else
throw new s16( L"unknown parameters to Int() constructor" );}
s274[0] = plv;}
inline void s344::s2291( s481** s274, size_t s496 ){
*((s1561*)s274[0])->s355() = (wchar_t)(int)*s274[1];}
wstring s344::to_wstring( uint32_t s1553 ) const {
wstring s681;
if( s347 > 0 && ( s1553 & s1548 ) )
s681 = L"+";
if( s1553 & s1547 )
s681 += s4::s1552( s347 );
else
s681 += std::to_wstring( s347 ); 
return s681;}
void s344::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
if( s1195() )
ss << s347;
else
ss << L"_undef_";}
void s344::to_null(){
s271::to_null();
s347 = 0;}
void s344::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << s347;}
s1293::s1293( s262* s300 )
: s1296( s300, NULL, NULL ){
s491 = Types.Long;
s347 = s300->TR().s1247();
s1665( s7::s862 );}
s1293::s1293( s262* s300, int64_t i )
: s1296( s300, NULL, NULL ){
if( !Types.Long ) {
s491 = 0;
s1665( s7::s862 );}
else {
s491 = Types.Long;
s347 = i;
s1252();}}
s1293::s1293( const s1293& r )
: s1296( r ){}
s1293::s1293( s262* s300, const std::wstring& s, size_t& pos )
: s1296( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1533( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1252();}
else
s153 = s300->TR().s1247();
s347 = (int64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s491 = Types.Long;}
void s1293::s348(){
s1296<int64_t, s1293>::s348();
s346 = s1296<int64_t, s1293>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1293::s1227, s1515,
{ s1113(), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );
s300->TR().s1153( s491, s7::s1513, s1501::s1538 );}
s481* s1293::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1293( s300, L"", pos );}
void s1293::s498( const s272* s873, bool ){
s1252();}
s271* s1293::s333( s589* s2042, s272* impl ) const{
return new s1293( *this );}
void s1293::s354( s271* p ) const{
if( p->s350() == Types.Long )
*((s1293*)p)->s355() = s347;
else if( p->s350() == s1142 )
*((s344*)p)->s355() = (s344::s1375)s347;
else if( p->s350() == s1516 )
*((s1518*)p)->s355() = s347;
else if( p->s350() == s1139 )
*( (s358*)p )->s355() = (s347 != 0);
else if( p->s350() == s1141 )
*( (s356*)p )->s355() = (double)s347;
else
throw new s16( L"no conversion from " + s351() + L" to " + p->s351() );}
s481* 
s1293::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s = s695.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1293( s300, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1293( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s353( NULL, std::vector<s271*>(), &s695 );}
return 0;}
inline void s1293::s1227( s481** s274, size_t s496 ){
s1293* plv = new s1293( ( (s1293*)s274[1] )->s300, (s1375)0 );
s1293& lv = *plv;
if( s496 == 2 )
lv.s347 = 0;
else if (s496 == 3){
s481* p = s274[2];
if( p->s350() == Types.Int )
lv.s347 = *( (s344*)p )->s355();
else if( p->s350() == s1141 )
lv.s347 = (s1375)*( (s356*)p )->s355();
else if( p->s350() == s1139 )
lv.s347 = (s1375)*( (s358*)p )->s355();
else
throw new s16( L"no conversion to Long from type: " + p->s351() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1252();
s274[0] = plv;}
wstring s1293::to_wstring( uint32_t s1553 ) const{
wstring s681;
if( s347 > 0 && ( s1553 & s1548 ) )
s681 = L"+";
if( s1553 & s1547 )
s681 += s4::s1552( s347 );
else
s681 += std::to_wstring( s347 );
return s681;}
void s1293::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
ss << s347;}
s1518::s1518( s262* s300, s272* s586 )
: s1296( s300, s586, NULL ){
s491 = Types.s1517;
s347 = s300->TR().s1247();
s1665( s7::s862 );}
s1518::s1518( s262* s300, uint64_t i, s272* s586 )
: s1296( s300, s586, NULL ){
if( !Types.s1517 ) {
s491 = 0;
s1665( s7::s862 );}
else {
s491 = Types.s1517;
s347 = i;
s1252();}}
s1518::s1518( const s1518& r )
: s1296( r ){
s300->s2248( &r, this );}
s1518::s1518( s262* s300, s272* s586, const vector<s271*>& l, const s263* ast_ )
: s1296( s300, s586, ast_ ){
if( l.size() ) {
s2239* s274 = new s2239();
s274->assign( begin( l ), end( l ) );
s300->s2243( this, s274 );}
s491 = Types.Int;
s347 = (s1375)s300->TR().s1247();
s1665( s7::s862 );}
s1518::s1518( s262* s300, const std::wstring& s, size_t& pos, s272* s586 )
: s1296( s300, s586, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1534( pst, &s153, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1252();}
else
s153 = s300->TR().s1247();
s347 = (uint64_t)s153;
pos = pend ? ( pend - pst ) : string::npos;
s491 = Types.s1517;}
void s1518::s348(){
s1296<s1375, s1518>::s348();
s346 = s1296<s1375, s1518>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1518::s1227, s1516,
{ s1113(), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"abs", new s335( L"abs", &s1518::s402, s1516,
{ s1113(), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"dif", new s335( L"dif", &s1518::s387, s1516,
{ s1113(), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );
s300->TR().s1153( s491, s7::s1513, s1501::s1538 );}
s481* s1518::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1518( s300, L"", pos );}
void s1518::s498( const s272* s873, bool ){
s1252();}
s271* s1518::s333( s589* s2042, s272* impl ) const{
return new s1518( *this );}
void s1518::s354( s271* p ) const{
if( p->s350() == Types.s1517 )
*((s1518*)p)->s355() = s347;
else if( p->s350() == s1515 )
*((s1293*)p)->s355() = s347;
else if( p->s350() == s1142 )
*((s344*)p)->s355() = (s344::s1375)s347;
else if( p->s350() == s1139 )
*( (s358*)p )->s355() = (s347 != 0);
else if( p->s350() == s1141 )
*( (s356*)p )->s355() = (double)s347;
else
throw new s16( L"no conversion from " + s351() + L" to " + p->s351() );}
s481* 
s1518::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s = s695.s291();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1518( s300, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1518( s300, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s353( NULL, std::vector<s271*>(), &s695 );}
return 0;}
inline void s1518::s1227( s481** s274, size_t s496 ){
s1518* plv = new s1518( ( (s1518*)s274[1] )->s300, (s1375)0 );
s1518& lv = *plv;
if( s496 == 2 )
lv.s347 = 0;
else if (s496 == 3){
s481* p = s274[2];
if( p->s350() == Types.Int )
lv.s347 = *( (s344*)p )->s355();
else if( p->s350() == Types.Long )
lv.s347 = *( (s1293*)p )->s355();
else if( p->s350() == Types.Double )
lv.s347 = (s1375)*( (s356*)p )->s355();
else if( p->s350() == Types.Bool )
lv.s347 = (s1375)*( (s358*)p )->s355();
else
throw new s16( L"no conversion to ULong from type: " + p->s351() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1252();
s274[0] = plv;}
wstring s1518::to_wstring( uint32_t s1553 ) const{
wstring s681;
if( s347 > 0 && ( s1553 & s1548 ) )
s681 = L"+";
if( s1553 & s1547 )
s681 += s4::s1552( s347 );
else
s681 += std::to_wstring( s347 );
return s681;}
void s1518::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
ss << s347;}
s1285::s1285( s262* s300 )
: s1296( s300, NULL, NULL ){
s491 = Types.Byte;
s347 = (s1375)s300->TR().s1247();
s1665( s7::s862 );}
s1285::s1285( s262* s300, tdbyte_t i )
: s1296( s300, NULL, NULL ){
s491 = Types.Byte;
if( !s491 )
s1665( s7::s862 );
else {
s347 = i;
s1252();}}
s1285::s1285( const s1285& r )
: s1296( r.s300, r.ns, NULL ){
wh = r.wh;
s491 = r.s491;}
s1285::s1285( s262* s300, const std::wstring& s, size_t& pos )
: s1296( s300, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s153 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s153, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1665( s7::s861 );}
else
s153 = s300->TR().s1247();
s347 = (int)s153;
pos = pend ? ( pend - pst ) : string::npos;
s491 = Types.Byte;}
void s1285::s348(){
s1296<tdbyte_t, s1285>::s348();
s346 = s1296<tdbyte_t, s1285>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1285::s1227, s1298,
{ s1113(), s1113( { s1501::s1261 } ) }, 0, 1 ) ) );
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );
s300->TR().s1153( s491, s7::s1513, s1501::s1538 );}
s481* s1285::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1285( s300, L"", pos );}
void s1285::s498( const s272* s873, bool ){
s1252();}
s271* s1285::s333( s589* s2042, s272* impl ) const{
return new s1285( *this );}
void s1285::s354( s271* p ) const{
if( p->s350() == Types.Byte )
*((s1285*)p)->s355() = s347;
else if( p->s350() == s1515 )
*((s1293*)p)->s355() = s347;
else if( p->s350() == s1516 )
*((s1518*)p)->s355() = s347;
else if( p->s350() == s1139 )
*( (s358*)p )->s355() = (s347 != 0);
else if( p->s350() == s1141 )
*( (s356*)p )->s355() = (double)s347;
else
throw new s16( L"no conversion from " + s351() + L" to " + p->s351() );}
s481* 
s1285::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s = s695.s291();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1285( s300, s, pos );
}*/
if( s695.s1299() == s350() )
return new s1285( s300, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1285( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s353( NULL, std::vector<s271*>(), &s695 );}
return 0;}
inline void s1285::s1227( s481** s274, size_t s496 ){
s1285* plv = new s1285( ( (s1285*)s274[1] )->s300, 0 );
s1285& lv = *plv;
if( s496 == 2 )
lv.s347 = 0;
else if( s496 == 3 )
s274[2]->s354( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1252();
s274[0] = plv;}
void s1285::s1920( Stream* s1919 ) const{
auto flags = s1919->s1915();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s347;
s1919->s1469( ss.str() );}
s1561::s1561( s262* s300 )
: s1296( s300, NULL, NULL ){
s491 = Types.Char;
s347 = (s1375)s300->TR().s1247();
s1665( s7::s862 );}
s1561::s1561( s262* s300, wchar_t i )
: s1296( s300, NULL, NULL ){
s491 = Types.Char;
if( !s491 )
s1665( s7::s862 );
else {
s347 = i;
s1252();}}
s1561::s1561( const s1561& r )
: s1296( r.s300, r.ns, NULL ){
wh = r.wh;
s491 = r.s491;}
s1561::s1561( s262* s300, const std::wstring& s, size_t& pos )
: s1296( s300, NULL, NULL ){
if( s.size() ) {
s347 = s[pos];}
s491 = Types.Char;}
void s1561::s348(){
s1296<wchar_t, s1561>::s348();
s346 = s1296<wchar_t, s1561>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1561::s1227, s1567,
{ s1113(), s1113( { s1567 } ), s1113( { s1144 } ), s1113( { s1142 } ) }, 0, 1 ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s1561::s396, s1139,
{ s1113( { s1567 } ), s1113( { s1144 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"neq", new s335( L"neq", &s1561::s401, s1139,
{ s1113( { s1567 } ), s1113( { s1144 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"isupper", new s335( L"isupper", &s1561::s2225, s1139,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"islower", new s335( L"islower", &s1561::s2223, s1139,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"isspace", new s335( L"isspace", &s1561::s2224, s1139,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"tolower", new s335( L"tolower", &s1561::s884, s1567,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"toupper", new s335( L"toupper", &s1561::s885, s1567,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"code-unit", new s335( L"code-unit", &s1561::s2282, s1142,
{ s1113() }, 0, 0 )));
s300->TR().s1153( s491, s7::s1402, s1501::s1261 );
s300->TR().s1153( s491, s7::s1513, s1501::s1538 );}
s481* s1561::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
size_t pos = 0;
return new s1561( s300, L"", pos );}
void s1561::s498( const s272* s873, bool ){
s1252();}
s271* s1561::s333( s589* s2042, s272* impl ) const{
return new s1561( *this );}
void s1561::s354( s271* p ) const{
if( p->s350() == Types.Char )
*( (s1561*)p )->s355() = s347;
else if( p->s350() == s1142 )
*( (s344*)p )->s355() = s347;
else if( p->s350() == s1515 )
*( (s1293*)p )->s355() = s347;
else if( p->s350() == s1516 )
*( (s1518*)p )->s355() = s347;
else if( p->s350() == s1139 )
*( (s358*)p )->s355() = ( s347 != 0 );
else if( p->s350() == s1141 )
*( (s356*)p )->s355() = (double)s347;
else
throw new s16( L"no conversion from " + s351() + L" to " + p->s351() );}
s481* 
s1561::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s = s695.s291();
size_t pos = 0;
if( s695.s1299() == s350() )
return new s1561( s300, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1561( s300, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s353( NULL, std::vector<s271*>(), &s695 );}
return 0;}
inline void s1561::s1227( s481** s274, size_t s496 ){
s1561* plv = new s1561( ( (s1561*)s274[1] )->s300, 0 );
s1561& lv = *plv;
if( s496 == 2 )
lv.s347 = 0;
else if( s496 == 3 )
s274[2]->s354( plv );
else
throw new s16( L"unknown parameter to Char() constructor" );
lv.s1252();
s274[0] = plv;}
inline void s1561::s396( s481** s274, size_t s496 ){
s1561* plv = (s1561*)s274[1];
s481* s2258 = s274[2];
if( s2258->s350() == s1567 ) {
if( *plv->s355() == *((s1561*)s2258)->s355() )
*( (s358*)s274[0] )->s355() = true;
else
*( (s358*)s274[0] )->s355() = false;}
else {
if( ((s357*)s2258)->s355()->size() == 1 && *plv->s355() == ((s357*)s2258)->s355()->at(0) )
*( (s358*)s274[0] )->s355() = true;
else
*( (s358*)s274[0] )->s355() = false;}}
inline void s1561::s401( s481** s274, size_t s496 ){
s1561* plv = (s1561*)s274[1];
s481* s2258 = s274[2];
if( s2258->s350() == s1567 ) {
if( *plv->s355() != *((s1561*)s2258)->s355() )
*( (s358*)s274[0] )->s355() = true;
else
*( (s358*)s274[0] )->s355() = false;}
else {
if( ((s357*)s2258)->s355()->size() == 1 && *plv->s355() == ((s357*)s2258)->s355()->at(0) )
*( (s358*)s274[0] )->s355() = false;
else
*( (s358*)s274[0] )->s355() = true;}}
inline void s1561::s2225( s481** s274, size_t s496 ){
wchar_t wc = ((s1561*)DR)->s347;
*((s358*)*s274)->s355() = iswupper( wc );}
inline void s1561::s2223( s481** s274, size_t s496 ){
wchar_t wc = ((s1561*)DR)->s347;
*((s358*)*s274)->s355() = iswlower( wc );}
inline void s1561::s2224( s481** s274, size_t s496 ){
wchar_t wc = ((s1561*)DR)->s347;
*((s358*)*s274)->s355() = iswspace( wc );}
inline void s1561::s885( s481** s274, size_t s496 ){
wchar_t wc = ((s1561*)DR)->s347;
((s1561*)DR)->s347 = towupper( wc );
*s274 = s274[1];}
inline void s1561::s884( s481** s274, size_t s496 ){
wchar_t wc = ((s1561*)DR)->s347;
((s1561*)DR)->s347 = towlower( wc );
*s274 = s274[1];}
inline void s1561::s2282( s481** s274, size_t s496 ){
*((s344*)s274)->s355() = (int)((s1561*)DR)->s347;}
void s1561::s1920( Stream* s1919 ) const{
auto flags = s1919->s1915();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s347;
s1919->s1469( ss.str() );}
const wstring s469 = L"";
s480 s683;
s272::s272( s262* s300, s1054 s338, s470 pc/* = s471*/, const s263* ast_, s272* ns_, s2176 st )
: s481( s300, pc, ast_, ns_ ), s623( NULL ), s624( NULL ), 
s1649( s7::s1589, s300, s473 ), s345( s469 ), //s631( s683 ),
s627( NULL )/*, s1350( ++s1351 )*/, s2180( st )
{
s623 = this;
s491 = s338;}
s272::s272( const s272& proto, std::vector<s483>& s699, const s263* ast_, s272* ns_ )
: s481( proto.s300, /*s478*/proto.s490, ast_, ns_ ? ns_ : proto.ns ), s623( &proto ), 
s624(NULL), s1649( s7::s1589, s300, s473 ), s345( proto.s345 ),
s627( proto.s627 ), //s631( s683 ),
s629( proto.s629 ), s2180( proto.s2180 )//, s1350( ++s1351 )
{
s491 = proto.s491;
if( s490 == s476 || s490 == s2150 )
s490 = s478;
if( proto.s624 )
proto.s624->s641( this );
proto.s626.copy( s626, this, NULL, s480::s147 );
for( size_t n = 0; n < s629.size(); ++n )
s628.push_back( s626.get( s629[n].s615() ) );
if( s699.size() ) {
s836* p = (s836*)s626.get( s7::s427 );
p->s2259( s699 );}
s1649.s349( s491 );
if( s490 == s478 )
s1665( proto.s616() );}
s272::s272( s1890& s672, s262* s300, s470 pc, const s263* ast_, s272* ns_,
s2176 st )
: s481( s300, pc, ast_, ns_ ), s623( NULL ), s624( NULL ), 
s1649( s7::s1589, s300, s473 ), s345( s469 ), s278( s672 ),
s627( NULL ), s2180( st )//, s1350( ++s1351 )//, s631( *new s480() )
{
s623 = this;}
s272::s272( s263& s695, s262* s300, s470 pc, s272* ns_, s534 am,
s621& cl, s620& cnl, s622& al, s2176 st )
: s481( s300, pc, &s695, ns_ ), s623(NULL), s624( NULL ), 
s1649( s7::s1589, s300, s473 ), s345( s695.s299() ), s278( s695.s298() ),
s626( am ), s627( NULL ), s2180( st )//, s1350( ++s1351 ) //,s631( *new s480() )
{
if( s278.find( L" " ) != string::npos )
throw new s16( L"Malformed class name: " + s278 );
s623 = this;
if( pc == s476 || pc == s2150 ) {
if( cl.find( s695.s299() ) != cl.end() )
throw new s16( L"class already exists: " + s695.s299() );
size_t s2149 = cnl.size();
size_t s2177 = s695.s268( s2174 ).s56();
if( s695.s156( s7::s467 ) ) {
wstring anc = s695.s292( s7::s467 )->s291();
cnl.push_back( make_pair( s695.s299(), /*anc*/s2177 ) );
}
if( s695.s156( s7::s2145 ) ) {
wstring s2147 = s695.s292( s7::s2145 )->s291();
cnl.push_back( make_pair( s695.s299(), /*s2147*/s2177 ) );
}
if( cnl.size() == s2149 )
cnl.push_back( make_pair( s695.s299(), /*L""*/s2177 ) );
cl.insert(make_pair(s695.s299(), this));}
if( al.find( s695.s299() ) != al.end() )
throw new s16( L"module already defined: " + s695.s299() );
al.insert(make_pair(s695.s299(), &s695));
s504( L"proto" );
s263::s275& s696 = s695.s293();
s263::s275::iterator it = s696.begin();
vector<pair<wstring,wstring>> s688;
for( ; it != s696.end(); ++it ) {
if( it->second->s297() == s225 ) {
if( it->first == s7::s467 ) {
s625 = it->second->s291();}}
else if( it->second->s297() == s227 ) {
wstring s656 = it->first;
s510 pv = s513;
am = s508;
size_t s685 = s656.find_first_of( s4::s48 );
if( s685 != string::npos ) {
vector<wstring> s684;
s4::s57( it->first, wstring( 1, s656[s685] ), s684 );
if( s684.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
if( s684[0] == s7::s449 || s684.size() == 3 ) {
pc = s476;
if( s684.size() == 3 ) {
if( s684[0] == s7::s446 )
am = s507;
else if( s684[0] == s7::s448 )
am = s509;
else if( s684[0] != s7::s447 )
throw new s16( L"invalid access mode name: " + it->first );
s656 = s684[2];}
else
s656 = s684[1];
if( s696.find( s656 ) != s696.end() )
throw new s16( L"duplicated object name: " + it->first );
it->second->s294( s656 );
s688.push_back( make_pair( it->first, s656 ) );}
else if( s684[0] == L"access" && ( s684[1] == L"allow" || s684[1] == L"deny" )) {
if( s684[1] == L"allow" )
pv = s512;
pc = s477;}
else
throw new s16( L"unknown object type: " + s684[0] );}
if( pc == s477 ) {
s626.s547( pv, it->second );}
else {
s272* ob = new s272( *it->second, s300, s476, this, am, cl, cnl, al, s2183 );
s626.s539( ob->s299(), ob );}}}
for( size_t n = 0; n < s688.size(); ++n ) {
auto it = s696.find( s688[n].first );
s696.insert(make_pair(s688[n].second, it->second ));
s696.erase( it );}}
s272::~s272(){
s626.reset();
s628.clear();
s629.clear();}
s481* s272::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return s633( s695, s586, s332 );}
void s272::s642( const s480& s274 ){}
wstring s272::s828() const {
if( s490 == s478 )
return s345;
return /*ns->s298()*/ s278; 
}
bool
s272::s499( const s481* s500 ) const{
if( s500->s350() == s350() )
return true;
if( s624 )
return s624->s499( s500 );
return false;}
bool
s272::s724( s1890& f ) const{
return s626.s156( f );}
void s272::s154( s263& s695 ){
TDException s961( s7::s2144, s926, &s695 );
s263::s275& s696 = s695.s293();
s263::s275::iterator it = s696.begin();
for( ; it != s696.end(); ++it ) {
s263* node = it->second;
if( node->s297() == s225 ) {
wstring s76 = node->s299();
if( s76 == s7::s441 )
s643( *node );
else if( s76 == s7::s467 )
s636( *node );
else if( s76 == s7::s930 )
s963( *node );
else {
size_t s685 = s76.find_first_of( s4::s48 );
bool s1194 = false;
if( s685 != string::npos ) {
vector<wstring> s684;
s4::s57( s76, wstring( 1, s76[s685] ), s684 );
if( s684.size() > 2 )
throw s961.s993( L"malformed object declaration: " + s76 );
if( s684[0] == s7::s1131 ) {
s1194 = true;
s76 = s684[1];}
node->s294( s76 );}
try { lang::s654( s76 ); }
catch( s16* e ) {
throw s961.s993( e->Msg() );}
s481* dv = NULL;
try {
dv = s300->TR().s516( *node, this, s278 );
dv->s2181( s2186 );}
catch( TDException* e ) {
if( e->Category() == s924 ) {
wstring sym = e->s2153( 0 );
wstring s617 = node->s291();
s617 = s617.substr( 0, s617.find( L"(" ) );
s1054 pt = s300->TR().s1003( s617 );
const s481* proto = s300->TR().s1000( pt );
if( proto->s492() == s476 && ((s272*)proto)->s2163( s278 ) )
e->s30( L"recursive import between '" + s617 + L"' and '" + s278 + 
L"'.\n   Recursive import in classes is not allowed." );}
e->s30( L"while constructing object member: " + s76 );
throw e;}
catch( s16* e ) {
e->s30( L"while constructing object member: " + s76 );
throw e;}
dv->s504( node->s299() );
try {
s626.s539( node->s299(), dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s278 + L"::" + node->s299() );}
throw e;}
s628.push_back( dv );
s629.push_back( s369( node->s299(), s300, s473, s1194 ) );}}
else if( node->s297() == s227 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s272* ob = (s272*)s626.get( it->first );
ob->s154( *it->second );}}
else if( node->s297() == s228 ) {
if( node->s299() == s7::s2145 ) {
s1054 s2148 = s300->TR().s1003( node->s291() );
s626.s539( node->s299(), new s1518( s300, s2148 ) );
continue;}
s481* dv = new s357( s300, node->s291(), this, node );
dv->s504( node->s299() );
dv->s1250( true );
wstring s1660 = node->s299();
if( node->s299() == s7::s463 )
s1660 = L"name";
try {
s626.s539( s1660, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s278 + L"::" + node->s299() );}
throw e;}
s628.push_back( dv );
s629.push_back( s369( s1660, s300 ) );}}
it = s696.begin();
for( ; it != s696.end(); ++it ) {
s263* node = it->second;
if( node->s297() == s226 ) {
try {
s486 func = s589::s597( *node, s300, this,
node->s299(), s278 );
s626.s539( func->s299(), func.s15<s481*>() );
s628.push_back( func );
s629.push_back( s369( func->s299(), s300 ) );}
catch( TDException* e ) {
e->s1069( TDException::Stage::s1018 );
e->s30( L"while compiling function '" +s278 + L"::" + node->s299() + L"'" );
s1007.s964( e->Msg( 0 ) );}}}
if( s490 == s476 ) {
s1347* s1354 = new s1347( s300, this, NULL, NULL );
s626.s539( s7::s1346, s1354 );
s628.push_back( s1354 );
s629.push_back( s369( s7::s1346, s300 ) );
if( s626.s156( s7::s426 ) ) {
s836* s2169 = (s836*)s626.get( s7::s426 );
vector<s271*> s1825 = { this }; // ???DEBUG??? 220615
s589::s829 s875;
s2169->s808( s875 );
for( size_t n = 0; n < s875.size(); ++n )
s1825.push_back( s875[n].second );
s836* td = new s836( *s2169, (s589*)this, s1825, s589::s566,
&s695, this, this, false );
s626.s539( s7::s427, td );}
if( s626.s156( s7::s2145 ) ) {
s1054 s2253 = (s1054)(int)*s626.get( s7::s2145 );
s272* s2252 = (s272*)s300->TR().s1000( s2253 );
if( !s626.implements( s2252->s626 ) )
throw new s16( L"the '" + s278 + L"' class doesn't implement '" + 
s2252->s351() + L"' interface" );
s300->TR().s1522( s350(), s2253 );}}
else if( s490 == s477 ) {
if( 0 && s626.s156( s7::s426 ) ) {
s836* s2169 = (s836*)s626.get( s7::s426 );
vector<s483> s1825 = { this };
s589::s829 s875;
s2169->s808( s875 );
for( size_t n = 0; n < s875.size(); ++n )
s1825.push_back( s875[n].second );
s2169->s594( s1825 );}}}
void s272::s498( const s272* s873, bool ){
assert( s490 != s2150 );
if( s490 == s476 || s490 == s477 ) {
if( s625.size() ) {
s624 = (s272*)s300->s222( s625, s873->s828() );
s624->s627->copy( *s627 );}
if( s627 )
s627->s498( s300, s278 );
else
s627 = s623->s627;
s626.s498( this, NULL, false );}
else {
if( 1 || s300->s1320()) {
try {
if( ( s300->s1320() || s2180 == s2186 ) && s626.s156( s7::s427 ) ) {
vector<s482*> s274;
s274.push_back( this );
s836* p = (s836*)s626.get( s7::s427 );
if( p->s616() == s7::s862 ) {
p->s2118( (s589*)s873, this );
p->s498( s873, false );}
else
p->s595( s873 );
if( s492() == s478 ) {
p->s2246();
s1649.s380( this );
p->s2172( &s1649 );
p->s495( (s481**)&s274[0], 1 );}}
s626.s498( (s272*)s873, this, s300->s1320() ); // ???DEBUG??? 220626
}
catch( s16* e ) {
throw new TDException( TDException::Stage::s1019, s7::s2275, s1544, s601(), *e );}}
s627 = s623->s627;
s1649.s349( s491 );}
ns = (s272*)s873;}
void s272::s2118( s589* s2042, s272* impl, bool s2159 ){
return s481::s2118( s2042, impl, s2159 );
for( auto it = s626.Table().begin(); it != s626.Table().end(); ++it ) {
s271* p = it->second.s15<s271*>();
p->s2118( s2042, this, s2159 );}}
void s272::s1637(){
if( s492() != s477 || s616() == s7::s861 )
return;
if( s626.s156( s7::s426 ) ) {
s836* p = (s836*) s626.get( s7::s426 );
p->s498( (s272*)ns, true );
p->s495( 0,0 );}
s1252();
if( s627 ) 
s627->s1637( s300 );}
void s272::s641( s272* s644 ) const{
if( s624 )
s624->s641( s644 );}
void s272::s643( s263& s695 ){
if( !s627 )
s627 = new s549();
s627->s552( s695.s291() );
return;}
void s272::s637( s1890& s332,	vector<wstring>& s153 ){
s626.s531( s332, s153 );}
void s272::s553( s1890& s76, s1890& s556 ){
if( !s627 )
s627 = new s549();
s627->s553( s76, s300, s556 );}
bool s272::s2163( s1890& s76 ){
if( s627 )
return s627->s2163( s76 );
return false;}
void s272::s636( s263& s695 ){
s624 = (s272*)s300->s222( s625, s278 );}
void s272::s963( s263& s695 ){
wstring s988 = L"wrong syntax of class attributes: " + s695.s291();
s484 dv = s300->TR().s516( s695, this, s278 );
if( dv->s350() != s1705 )
throw new s16( s988 );
vector<s483>& v = dv.s15<s314*>()->s318();
for( auto s_ : v ) {
wstring s = s_.s15<s357*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s988 );
wstring cat = s4::s52( s.substr( 0, pl ), s4::s48 );
vector<wstring> s153;
s4::s57( s.substr( pl + 1 ), L",", s153 );}}
bool s272::s554( s1890& sym_, s369* ref, s1890& s332,
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
bool s681 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s682 = sym_.substr( 0, pl );
s272* ob = ((s272*)s639( s682, s332, false ));
if( !ob && s682 == s7::s1589 )
ob = (s272*)this;
if( ob ) {
s369 s1644( *ref );
s681 = ob->s554( sym, &s1644, s332, fr );
if( s681 ) {
if( !ref->s378() )
ref->s380( ( s481* )this );
ref->s377( s638( s682 ), ob );
ob->s554( sym, ref, s332, fr );}}
else {
if( s627 )
s681 = s627->s554( sym_, ref );}}
else {
const s272* ob = ((s272*)s639( sym, s332, false ));
if( ob ) {
if( !ref->s378() )
ref->s380( ( s481* )this );
size_t off = s638( sym );
ref->s377( off, ob );
if( s629[off].s1194() )
ref->s1250();
s681 = true;}
else {
if( sym == s7::s1589 ) {
ob = this;
if( !ref->s378() )
ref->s380( ( s481* )this );
ref->s377( s1138, ob );
s681 = true;}
else if( s627 )
s681 = s627->s554( sym, ref );}}
return s681;}
size_t s272::s638( s1890& s645 ) const{
if( s645 == s7::s1589 )
return s1138;
/*???DEBUG??? 220119	size_t pl = s645.find( L"::" );
if( pl != string::npos ) {
wstring smod = s645.substr( 0, pl );
wstring sym1 = s645.substr( pl + 2 );
s272* mod = (s272*)s626.get( smod, false );
if( !mod )
return NULL;
return mod->s638( sym1 );}
*/
for( size_t n = 0; n < s628.size(); ++n ) {
if( s629[n].s615() == s645 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s645 );}
s271* s272::s596( size_t off ){
if( off == s1138 )
return this;
return s628[off];}
void s272::s845( s1890& s76, s481* s347, s480::s145 ap ){
s626.s539( s76, s347, ap );
s628.push_back( s347 );
s629.push_back( s369( s76, s300 ) );}
void s272::s1643( s1890& s76, s481* s347 ){
if( !s626.s156( s76 ) )
throw new s16( L"no such member: " + s76 );
s626.s539( s76, s347, s480::s147 );
for( size_t n = 0; n < s629.size(); ++n ) {
if( s629[n].s615() == s76 ) {
s628[n] = s347;
break;}}}
void s272::s1628( const s1590* ob ){
s628.clear();
s623->s626.s1601( s626 );
for( size_t n = 0; n < s629.size(); ++n )
s628.push_back( s626.get( s629[n].s615() ) );
s480::s533 sm;
ob->s1620( sm );
s480::s533::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s626.s539( it->first, it->second.s15<s481*>(), s480::s147 );
else {
if( !s626.s156( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
s481* mem = s626.get( it->first );
mem = mem->s1525( it->second.s15<s481*>() );
s626.s539( it->first, mem, s480::s147 );}}
for( size_t n = 0; n < s629.size(); ++n ) {
s628[n] = s626.get( s629[n].s615() );}
/*	auto s818 = s626.Table();
auto it1 = s818.begin();
for( ; it1 != s818.end(); ++it1 )
it1->second->s2118( this );*/
}
s481* s272::s1525( const s481* p ) const{
if( p->s1530( s350() ) ) {
s272* s681 = (s272*)p->s333( NULL, ns );
if( s681->s616() == s7::s862 )
s681->s498( ns, true );
return s681;}
vector<s483> s274;
s274.push_back( (s271*)p );
s272* s681 = new s272( *(s272*)this, s274, s601(), (s272*)this );
s681->s498( this, false );
return s681;}
s481* s272::s639( s1890& sym, s1890& s332,	bool s518/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s272* mod = (s272*) s626.get( smod, s518 );
if( !mod )
return NULL;
return mod->s639( sym1, s332, s518 );
/* ???DEBUG??? 220119		s481* s153 = mod->s639( sym1, s332, s518 );
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
s484 s681 = s626.get( sym1, false );
if( !s681 && s518 )
throw new s16( L"4: Symbol does not exist: " + sym, 
(uint32_t)s16::s17::s23 );
if( s681 && !s640( sym1, s332 ) && (s332 != L":::") ) {
if( s518 )
throw new s16( L"4: Symbol not found: " + sym,
(uint32_t)s16::s17::s23 );
s681 = NULL;}
return s681;}
bool s272::s640( const wstring& sym, s1890& s497 ) const{
if( s497 == s345 )
return true;
return s626.s548( sym, s497 );}
s1054 s272::s384( s1890& s341 ) const{
s481* s686 = s626.get( s341 );
s1054 s681 = s686->s350();
if( s681 == 0 ) {
s686->s498( (s272*)this );
s681 = s686->s350();}
return s681;}
s481* s272::s633( const s263& s695, s481* s586, s1890& s332 ) const{
vector<wstring> s687;
vector<s483> s274;
vector<s271*> s699;
s271::s1323( s695, s300, (s272*)s586, s332, s699 );
for( auto pr : s699 )s274.push_back( pr );
s272* s681 = new s272( *this, s274, &s695, (s272*)s586 );
return s681;}
s481* s272::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
vector<wstring> s687;
vector<s483> s274;
if( s300->s1320() )
for( auto p : l ) s274.push_back( p ); 
s272* s681 = new s272( *this, s274, s601(), s586 );
return s681;}
std::wstring s272::s298() const{
if( s492() == s477 )
return s278;
else if( s492() == s476 || s492() == s478 )
return s345;
assert( 0 );
return /*s277 + L"::" +*/ s278;
}
s481* s272::s342( s1890& s672, s1890& s332,
bool s518 /*= true*/, bool s2151 /*= true*/ ) const
{
s369 ref( s672, s300 );
if( !s554( s672, &ref, s332, true ) )
return NULL;
if( !s2151 && ref.s379().s15<s272*>() != this )
return NULL;
s481* s681 = ref.s376();
if( s681->s492() != s474 )
return NULL;
return s681;}
s589* s272::s1671( s1890& s672, s589* s215, s272* s1658,
s559* cs ) const{
if( s672 == L"getf" ) {
return new s1666( s300, (s272*)this, s215, &s272::s1690, cs, 
NULL );}
return s481::s1671( s672, s215, s1658, cs );}
s481* s272::s1690( s481** s274, size_t s496 ){
s357* pv = (s357*) s274[1];
return s626.get( pv->to_wstring() );}
s271* s272::s333( s589* s2042, s272* impl ) const{
vector<s483> v;
return new s272( *this, v, NULL, ns );}
void s272::s354( s271* p ) const{
s272* pob = (s272*)p;
s626.s1601( pob->s626 );
for( size_t n = 0; n < pob->s629.size(); ++n ) {
pob->s628[n] = pob->s626.get( pob->s629[n].s615() );}
return;
throw new s16( L"" );
vector<wstring> fields;
s626.s543( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s481*)s626.get( fields[n] ))->s354( p );}
size_t s272::s320() const{
return s626.s320();}
bool s272::operator==( const s481* p ) const{
return s626.compare( ( (s272*)p )->s626.Table() );}
bool s272::operator<( const s481* p ) const{
return false;}
void s272::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
if( s626.s156( s7::s1617 ) ) {
s589* s1641 = (s589*)s626.get( s7::s1617 );
s9<s505> s1639 = new s505( (s262*)s300, (s272*)this, s601() );
vector<s483> s699 = { /*(s271*)this,*/ s1639 };
s1641->s594( s699 );
s1641->s2118(NULL, (s272*)this);
if( s1641->s616() != s7::s861 )
s1641->s498( this, true );
else
s1641->s595( this );
s1641->s495( 0, 0 );
ss << s1639->to_wstring();
return;}
std::wstringstream buf;
wstring s345;
if( s490 == s476 ) s345 = L"Class";
else if( s490 == s477 ) s345 = L"Module";
else if( s490 == s478 ) s345 = L"Object";
else s345 = L"ERROR";
buf << s345 << L" : " << s278 << L"/" /*<< s370*/ << endl;
s626.s304( &buf, s417 );
buf << endl;
ss << buf.str();}
wstring s272::to_wstring( uint32_t s1553 ) const{
if( s626.s156( s7::s1617 ) ) {
s589* s1641 = (s589*)s626.get( s7::s1617 );
s9<s505> s1639 = new s505( (s262*)s300, (s272*)this, s601() );
vector<s483> s699 = { /*(s271*)this,*/ s1639 };
s1641->s594( s699 );
if( s1641->s616() != s7::s861 )
s1641->s498( this, false );
else
s1641->s595( this );
s1641->s495( 0, 0 );
return s1639->to_wstring();}
std::wstringstream buf;
wstring s345;
if( s490 == s476 ) s345 = L"Class";
else if( s490 == s477 ) s345 = L"Module";
else if( s490 == s478 ) s345 = L"Object";
else s345 = L"ERROR";
buf << s345 << L" : " << s278 << L"/" /*<< s370*/ << endl;
s626.s304( &buf, s417 );
buf << endl;
return buf.str();}
void s272::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s345;
if( s490 == s476 ) s345 = L"Class";
else if( s490 == s477 ) s345 = L"Module";
else if( s490 == s478 ) s345 = L"Object";
else s345 = L"ERROR";
buf << s4::fill_n_ch( L' ', s197 ) << s345 << L" : " << s278 << L"/" << 
L": " << s4::s2170( (void*)this ).c_str() << endl;
s626.s304( pd, s197 + s417 );}
s575 s2100;
s589* s589::s597( const s263& s695, s262* s300, s272* obj,
const wstring& s278, const wstring& s556 ){
const s263::s275& s696 = s695.s293();
size_t s691 = s696.size();
std::vector<s271*> s274;
bool s2132 = false;
bool formals = true;
vector<std::pair<wstring, wstring>> s2269;
for( size_t n = 0; n < s691; ++n ) {
s263::s275::const_iterator it = s696.find( std::to_wstring( n ) );
if( it->second->s291() == s7::s934 )
s274.push_back( s867 );
else if( it->second->s291() == s7::s1131 )
s274.push_back( s1672 );
else if( it->second->s291() == s7::s2124 ) {
s274.push_back( s2131 );
s2132 = true;
formals = false;}
else {
if( formals && (( s274.empty() && it->second->s297() != s228 ) ||
( s274.size() && s274.back()->s492() != s473 && it->second->s297() != s228 )))
formals = false;
if( s2132 && s274.back()->s492() != s473 && it->second->s297() != s228 ) 
s2132 = false;
for( auto mn : s2269 )
it->second.s15<s263*>()->s2268( mn );
if( s2132 )
it->second.s15<s263*>()->s269( s2279, s141( L"locals" ) );
s271* ex = s271::s502( *it->second, s300, obj, s556, !s2132 ); // ???DEBUG??? 220701
s274.push_back( ex );
if( (s2132 || formals) && ex->s492() == s473 && ( (s369*)ex )->s615()[0] != L'_' ) {
wstring s2271 = ( (s369*)ex )->s615();
lang::s654( s2271 );
( (s369*)ex )->s2270();
s2269.push_back( make_pair( s2271, ( (s369*)ex )->s615() ) );}}}
Transd* s681 = NULL;
size_t s685 = s278.find_first_of( s4::s48 );
if( s685 != string::npos ) {
vector<wstring> s684;
s4::s57( s278, wstring( 1, s278[s685] ), s684 );
if( s684.size() > 2 )
throw new s16( L"malformed function name: " + s278 );
if( s684[0] == s7::s429 ) {
s681 = new s602( s300, obj, NULL, s566, s274, &s695 );
s681->s278 = s684[1];}
else if( s684[0] == s7::s430 ) {
s681 = new s836( s300, obj, NULL, obj, s566, s274, &s695 );
s272* pAnc = (s272*)s300->s222( obj->s635(), s556 );
((s602*)pAnc->s342( s684[1], s556 ))->s646( obj->s350(),
s681 );
s681->s278 = s684[1];
s681->s592( s572 );}
else
throw new s16( L"malformed function name: " + s278 );}
else {
s681 = new s836( s300, obj, NULL, obj, s566, s274, &s695, true );
s681->s278 = s278;}
return s681;}
s559* s589::s1110( const s263& s695, s262* s300, s272* obj,
s1890& s556, bool s2160 ){
const s263::s275& s696 = s695.s293();
size_t s691 = s696.size();
wstring s599 = s695.s291();
std::vector<s271*> s274;
s559* s681 = NULL;
try {
for( size_t n = 0; n < s691; ++n ) {
s263::s275::const_iterator it = s696.find( std::to_wstring( n ) );
it->second.s15<s263*>()->s269( s2086, s141(L"CallSite") );
it->second.s15<s263*>()->s269( s2085, s141(s599) );
if( it->second->s291() == s7::s934 )
s274.push_back( s867 );
else if( it->second->s291() == s7::s1131 )
s274.push_back( s1672 );
else if( it->second->s291() == s7::s2124 )
s274.push_back( s2131 );
else
s274.push_back( s271::s502( *it->second, s300, obj, s556, false ) );}
s681 = new s559( s300, s599, s274, &s695, s2160 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s599 + L"' function call" );}
return s681;}
void s559::s498( const s272* s873, bool ){
return;
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s498( s873 );}}
s271* s559::s333( s589* s2042, s272* impl ) const{
return new s559( *this );}
s589* s589::s598( s559* cs, s262* s300, s272* s586, s589* s215, 
s1890& s556, bool proc ){
wstring s599 = cs->s299();
wstring s698 = s586 ? s586->s2154() : L"::";
s483 s697 = NULL;
std::vector<s271*>& s274 = cs->s600();
s486 s700 = NULL;
s589* s681 = NULL;
size_t pl = s599.find( L"<" );
try {
if( pl == string::npos ) {
auto s1440 = s1360.find( s599 );
if( s1440 != end( s1360 ) && BIFuncs1v[s1440->second] )
return s300->s214( s1440->second, cs, s586, s215 );
s271* par = NULL;
int s1353 = 0;
s1349:
if( s274.size() ) {
par = s274[s1353];
s470 pc = par->s492();
if( pc == s473 ) {
try {
par->s498( s215, proc ); }
catch( TDException* e ) {
if( e->Category() != s924 || (
( (s369*)par )->s615()[0] != L':' && ( (s369*)par )->s615().back() != L':' ) )
throw e->s30( L"while compiling function '" + s599 + L"'" );
s1353++;
goto s1349;}
if( ( (s369*)par )->s379().s14() ) {
if( ( (s369*)par )->s615() == s7::s428 )
par = s586;
s697 = ( (s369*)par )->s375();}}
else {
if( pc == s475 ) {
s488 cs = new s559( *(s559*)par );
par = s598( cs, s300, s586, s215, s556, false ); // ???DEBUG??? 220214
( (s589*)par )->s498( s586, false );}
else {
par->s498( s215 );}}
if( par->s492() == s473 /*||  par->s492() == s1327*/ ) {
(void)0;}
else if( par->s492() == s1056 || par->s492() == s479 )
s697 = NULL;
else {
s697 = par->s494();}
s274[s1353] = par;}
else {
s700 = (s589*)s586->s342( s599, s698, false );
if( !s700 )
throw new s16( L"Procedure is not resolved: " + s599 );}
if( s1440 != end( s1360 ) )
return s300->s214( s1440->second, cs, s586, s215 );}
else {
wstring s2123 = s599.substr( pl + 1, s599.size() - pl - 2 );
wstring s617 = s300->TR().s1265( s2123, s556 );
s599 = s599.substr( 0, pl );
if( s617 != s2123 ) {
s2123 = s300->TR().s1342( s300->TR().s1265( s2123, s556 ) );
((s263*)cs->s601())->s1754( s599 + L"<" + s2123 + L">" );}
try {
s1054 pt = s300->TR().s1003( s617, false );
if( !pt ) {
s940 ast2 = new s263( s617 + L"()", cs->s601()->Nqj(), (s263*)s215->s601() );
s697 = s300->TR().s516( *ast2, s586, s556 );}
else {
s697 = s300->TR().s1000( pt )->s353( s215, s274, s215->s601() );
s697->s2181( s2185 );}}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s599 + L"' function " );
s940 ast2 = new s263( s617 + L"()", cs->s601()->Nqj(), (s263*)s215->s601() );
s697 = s300->TR().s516( *ast2, s586, s556 );}
s274.insert( s274.begin(), s697 );
if( s697->s492() == s1235) {
s589* ptd = s697.s15<s272*>()->s1671( s599, s215, s586, cs );
if( ptd )
return ptd;}}
s486 s701 = NULL;
s1133 s1228;
if( !s700 ) {
s470 s704 = s697->s492();
if( s704 == s473 ) {
s369* ref = (s369*)s697.s15<s482*>();
s697 = (s481*)ref->s501();
s704 = s697->s492();}
try {
assert( s704 != s477 && s704 != s2150 );
if( s704 == s478 || s704 == s476 ) {
s701 = (s589*)s697.s15<s272*>()->s342( s599, s698, false, false );}
else if( s704 == s472 )
s1228 = s697.s15<s334*>()->s1188( s599 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s701 && !s1228.s337 )
s700 = (s589*)s586->s342( s599, s698, false );
if( !( s1228.s337 || s700 || s701 ) ) {
s589* ptd = s697.s15<s272*>()->s1671( s599, s215, s586, cs );
if( ptd )
return ptd;
throw new s16( L"Method is not resolved: " + s599 );}}
if( s1228.s337 ) {
s681 = new s835( s300, s215, s586, s564, s274, s1228.s336, s599, cs->s601(), proc );}
else if( s700 ) {
if( s599 == s7::s1346 ) {
assert( 0 );
vector<s271*> s1650( s274.begin() + 1, s274.end() );
s681 = new s1347( *s700.s15<s1347*>(), s586, s215, s1650,
cs->s601() );}
else {
s681 = new s836( *s700.s15<s836*>(), s215, s274,
s565, cs->s601(), s700->s586, s215->s586, false, proc ); //???DEBUG??? 220828
}}
else if( s701 ) {
if( s599 == s7::s1346 ) {
s681 = new s1347( *s701.s15<s1347*>(), s697.s15<s272*>(), s215, s274,
cs->s601() );}
else {
s681 = new s836( *s701.s15<s836*>(), s215, s274, s566,
cs->s601(), s697.s15<s272*>(), s215, true, proc );}
if( s701->s593() == s571 )
s681->s573 = s567;
else
s681->s573 = s566;}}
catch( s16* e ) {
throw e->s30( L"while compiling function '" + cs->s601()->Src() + L"'" );}
s681->s278 = s599;
return s681;}
void s589::s1232( vector<s271*>& s274, const vector<wstring>& s1199 ){
for( s271* p : s274 ) {
if( p->s492() == s473 || p->s492() == s1056 )
( (s369*)p )->s975( s1199 );}}
void s589::s1232( vector<s483>& s274, const vector<wstring>& s1199 ){
for( s271* p : s274 ) {
if( p->s492() == s473 )
( (s369*)p )->s975( s1199 );}}
s589::s589( s262* s300, s272* s590, s589* s591, s272* ns_, s561 ct,
s1890& s672, const s263* s695, bool s1713, bool _bd )
: s272( s672, s300, s474, s695, ns_ ), s573( ct ),
s584( NULL ), s586( s590 ), s585( s591 ), past( s695 ), s1640( new s1588( s300 ) ),
intro( s1713 ), s2159( _bd ), s2220( -1 ){}
s589::s589( s262* s300, s272* s590, s589* s591, s272* ns_,
s561 ct, const std::vector<s271*>& l,	const s263* s695, bool s1713=false,
bool _bd=true)
: s272( s300, 0, s474, s695, ns_ ), s573( ct ), s574( s570 ),
s584( NULL ),	s586( s590 ), s585( s591 ), past( s695 ), s1640( new s1588( s300 ) ),
intro(s1713), s2159(_bd), s2220( -1 ){
TDException s961( s7::s1673, s926, s695, L"malformed lambda definition" );
size_t n = 0;
bool s2137 = false;
bool s2132 = false;
bool s1159;
for( ; n < l.size(); n += 2 ) {
s1159 = false;
if( ((s481*)l[n]) == s867 ) {
if( l.size() == n || s2132 )
throw s961.s993( L"the return type is missing" );
s491 = l[n + 1]->s350();
s2137 = true;
continue;}
if( ((s481*)l[n]) == s2131 ) {
s2132 = true;
n -= 1;
continue;}
else if( ((s481*)l[n]) == s1672 ) {
if( l.size() == n )
throw s961.s993( L"the 'const' keyword should precede the parameter name");
s1159 = true;
++n;}
if( l[n]->s492() != s473 ) {
if( s1159 )
throw s961.s993( L"the 'const' keyword should precede the parameter name");
break;}
s369* s76 = (s369*) l[n];
if( l.size() == n + 1 ) {
throw new s16( L"incorrect syntax for lambda parameter " + s76->s615() +
L": missing type specifier.", (uint32_t)s16::s17::s20 );}
s481* ex = (s481*) l[n + 1];
s470 s1884 = ex->s492();
if( //s1884 != s472 && s1884 != s478 &&	s1884 != s477 && 
s1884 == s473 ||
(s1884 == s474 && !s2132 ) )
throw new s16( L"incorrect syntax for lambda parameter " + s76->s615() +
L": should be a type constructor.", (uint32_t)s16::s17::s20 );
if( s1159 )
s76->s1250();
s626.s539( s76->s615(), ex );
if( !s2132 )
s580.push_back( (s481*)ex );
s274.push_back( (s481*)ex );
s628.push_back( (s481*)ex );
s629.push_back( *s76 );}
s582.insert( s582.end(), l.begin() + n, l.end() );
if( s601() )
((s263*)s601())->s269( s2087, s141( (double)s491, s140 ) );}
s589::s589( const s589& right, s272* s590, s589* s591,
s272* ns_, const std::vector<s271*>& s699, const s263* s695, bool s2105,
bool _bd)
: s272( right, s2100, s695, ns_ ), 
s574( right.s574 ),	s584( NULL ), s586( s590 ), s585( s591 ), 
past( s695 ), s1640( new s1588( s300 ) ), intro( s2105 ), s2159( _bd ), s2220( right.s2220 ){
s573 = right.s573;
s580 = right.s580;
s278 = right.s278;
if( s699.size() ) {
s274.assign( s699.begin(), s699.end() );}
else {
s274.clear();
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s333( this, s590 ) );}}
if( s573 == s565 ) { 
for( size_t n = 0; n < s274.size(); ++n ) {
s483 tmp = s628[n];
s626.s539( right.s629[n].s615(), tmp.s15<s482*>(), s480::s147 );
s628[n] = s274[n];}}
for( size_t n = 0; n < right.s582.size(); ++n )
s582.push_back( right.s582[n]->s333( this, NULL ) );
nlocs = right.nlocs;
s496 = right.s496;
s579 = nlocs ? (s482**)&s274[0] : NULL;
s581 = right.s581;
s578 = s496 ? (s481**)&s581[0] : NULL;
s974 = right.s974;}
s835::s835( s262* s300, s589* s591, s272* ns_, s561 ct, const vector<s271*>& l,
s1054 s703, s1890& s1541, const s263* s695, bool _bd )
: s589( s300, s591, s591, ns_, ct, L"", s695, false, _bd ), s1961( false )/*, s560( s702 )*/
{
s278 = s1541;
if( s278 == s7::s1346 )
l[0]->s2118( this, this );
s574 = s570;
s491 = s703;
s274.assign( l.begin(), l.end() );}
s835::s835( const s835& right, s589* s591, s272* ns_ )
: s589( right, NULL, s591, ns_, vector<s482*>(), right.s601(),
false, right.s2159 ), 
s560( right.s560 ), s1961( right.s1961 ){
s278 = right.s278;
s574 = s570;
s491 = right.s491;
s584 = (s481*)right.s584->s333(0,0);
s581.resize( right.s581.size() );
s581[0] = s584;}
s835::~s835(){}
s836::s836( s262* s300, s272* s590, s589* s591, s272* ns_, s561 ct,
const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, ns_, ct, l, s695, false, s2160 ){
if( ct == s566 ) {
subject = s590;		}}
s836::s836( const s836& right, s589* s591,
const std::vector<s271*>& s699, s561 ct,  const s263* s695, 
s272* s590, s272* ns_, bool s2105, bool s2160 )
: s589( right, s590, 
s591, ns_, vector<s482*>(), s695, s2105, s2160 ){
TDException s961( s7::s1656, s926, s695 );
s573 = ct;
int shift = 0;
if( ct == s566 || ct == s565 ) { // ???DEBUG??? 220728 
if( ct == s566 && s699.size() ) {
subject = s699[0];
shift = 1;}
else
subject = s586.s15<s482*>();}
for( size_t n = 0; n < s580.size(); ++n ) {
if( s699.size() > n + shift ) {
s470 pc = s699[n]->s492();
if( ( pc == s473 || pc == s1327 ) && s699[n]->s1194() && !s629[n].s1194() )
throw s961.s993( L"constant argument is passed to non-constant function: " + s629[n].s615() );
s274[n] = s699[n + shift];}}
if( s274.size() ) {
for( size_t n = 0; n < s274.size(); ++n ) { // ???DEBUG??? 220802
s628[n] = s274[n]; // ???DEBUG??? 220802
}}
if( s699.size() - shift > s274.size() ) 
throw s961.s993( L"too many arguments: expected " + std::to_wstring( s274.size() ) + L", received " +
std::to_wstring( s699.size() ));}
s589::~s589(){
s274.clear();
s580.clear();
s974.clear();
s581.clear();}
s836::~s836(){}
s559::s559( s262* pass_, s1890& s189, const vector<s271*>& l, 
const s263* ast_, bool s2160 )
: s271( pass_, s475 ), s599( s189 ), past( (s263*)ast_ ), s2159( s2160 ){
s274.assign( l.begin(), l.end() );}
s559::s559( const s559& right )
: s271( right.s300, s475 ), s599( right.s599 ), past( right.past ),
s2159( right.s2159 ){
for( size_t n = 0; n < right.s274.size(); ++n ) {
s274.push_back( right.s274[n]->s333(0,0) );}}
wstring s589::s828() const{
if( s586.s14() )
return s586->s298();
else if( s573 == s564 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
std::wstring s589::s298() const{
return ns->s828();}
std::wstring s589::s2154() const{
if( s2159 )
return ns->s828();
return s585.s14() ? s585->s2154() : s586->s828();}
void s589::s841( s271* par, size_t pos, s483& s153, const s272* s1658, bool proc ){
if( par->s492() == s475 ) {
s488 cs = new s559( *((s559*)par) );
s153 = s598( cs, s300, (s272*)s1658, this, s1658->s2154(), cs->s2166() );
s153.s15<Transd*>()->s498( s586 ? s586 : s1658, cs->s2166() ); // ???DEBUG??? 220617
}
else if( par->s492() == s472 ) {
par->s498( /*s586*/ this, false );
s153 = par;}
else if( par->s492() == s474 ) {
s153 = par; // par->s494();
s153->s2118( this, (s272*)s1658, s153.s15<Transd*>()->s2166()  );	  //???DEBUG??? 220828
}
else if( par->s492() == s1235 ) {
if( this->s492() == s1235 ) //???DEBUG??? 220622 V
( (s832*)par )->s586 = this; 
par->s498( this, false );
s153 = par;}
else
s153 = par;}
void s589::s587(const wstring& s332){
return; // ???DEBUG??? 220213
for( size_t n = 0; n < s580.size(); ++n )
s580[n]->s498( s585/*s586*/ );
}
void s589::s498( const s272* s2161, bool proc/*=false*/ )
{
s1649.s349( s491 );
s667 = proc ? s2154() : s2161->s2154(); // ???DEBUG??? 220420
if( s586 && (s586->s492() == s477 || s586->s492() == s476 )) {
if( 0 && s586->s492() == s476 ) 
return;}
if( s573 == s564 && s616() == s7::s861 )
return;
s581.clear();
for( size_t n = 0; n < s274.size(); ++n ) {
s483 par = s274[n];
if( s573 == s564 && n == 1 ) {
s589::s1232( s274, ((s334*)s274[0]->s494())->s1182( s278 ) );}
if( par->s492() == s473 ) {
if( 1 || par.s15<s369*>()->s379().s13() || s573 == s566 ) { 
if( ! par.s15<s369*>()->s379().s13() )
par.s15<s369*>()->reset();
s485 s1661 = s586;
if( s2161 != this )
s586 = (s272*)s2161;
par.s15<s369*>()->s498( s585, false ); // ???DEBUG??? 220617
s586 = s1661;}
s581.push_back( par.s15<s369*>()->s375() );}
else if( par->s492() == s1056 || par->s492() == s479 )
s581.push_back( /*NULL*/ par.s15<s481*>() );
else {
try {
s841( par, n, s274[n], s2161, proc );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s278 + L"' function " );}
s581.push_back( s274[n]->s494() );}
if( s278 == s233 || s573 == s565 || s573 == s566 ) {
s481* par = s274[n]->s492() == s474 ? s274[n]->s494() : s274[n].s15<s481*>();
s626.s539( s629[n].s615(), par, s480::s147 );
s274[n]->s1665( s7::s861 );
s628[n] = par;}}
if( s573 == s563 || s573 == s565 ) {
for( size_t n = 0; n < s582.size(); ++n ) {
if( s582[n]->s492() == s475 ) {
s488 cs = new s559( *s582[n].s15<s559*>() );
s582[n] = s598( cs, s300, s586, this, s586->s2154(), cs->s2166() );}
else if( s582[n]->s492() == s473 )
s582[n].s15<s369*>()->s498( s585, false );
else if( s582[n]->s492() != s474 )
s582[n]->s498( s585 );
else if( s490 != s1235 ) // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s582 ) {
if( it->s492() == s474 )
it.s15<Transd*>()->s498( s2161, false );
else if( it->s492() == s1235 )
it.s15<Transd*>()->s498( s585, false );}
if( !s491 && s582.size() ) {
s491 = s582.back()->s350();}}
if( s491 ) {
if( s586.s14() ) {
if( 0 && s490 == s1235 )
s584 = s300->TR().s516( ((s832*)this)->s1318(), 
s586, s586->s298() );
else
s584 = s300->TR().s516( s350(), s586, s586->s298() );}
else {
if( 0 && s490 == s1235 )
s584 = s300->TR().s516( ((s832*)this)->s1318(), 
(s272*)s2161, s2161->s298() );
else
s584 = s300->TR().s516( s350(), (s272*)s2161, s2161->s2154() );}
s584->s498( s585, proc );
s584->s1665( s7::s861 );
s581.insert( s581.begin(), s584 );
if( s274.size() ) {
s579 = (s482**)&s274[0];
nlocs = s274.size();
s578 = &s581[0];
s496 = s581.size();}
else {
s579 = NULL;
s578 = NULL;
nlocs = s496 = 0;}}
s974.resize( s581.size() );}
void s835::s498( const s272* s1658, bool proc/*=false*/ )
{
TDException s961( s7::s1117, s1123, past );
s589::s498( s1658, proc );
s271* par = s274[0]->s494();
s334* s697 = NULL;
s1133 s1228;
s470 s704 = par->s492();
s1113 ap;
if( s704 == s473 ) {
s369* ref = (s369*)par;
s484 pobj = ref->s375();
s704 = pobj->s492();
s697 = pobj.s15<s334*>();
ap = s1113( s274, s697 );
try {
s1228 = s697->s1183( s278, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s334::s335::s1124::s1171 ) {
s1228 = s697->s1178( s278, ap );}}}
else {
s697 = ( (s334*)par );
ap = s1113( s274, s697 );
try {
s1228 = ( (s334*)s697->s494() )->s1183( s278, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s334::s335::s1124::s1171 ) {
s1228 = ( (s334*)s697->s494() )->s1178( s278, ap );}}}
if( !s1228.s337 )
throw s961.s993( L"method is not resolved: " + par->s351() + L"::" + s278 + 
ap.s1319( s300 ) );
try {
s300->s1998( s1228.s2020, s2030 );}
catch( s16* e ) {
throw s961.s993( e->Msg() );}
s491 = s1228.s336;
s560 = s1228.s337;
s1961 = s1228.s1159;
bool s1748;
if( s274[0]->s492() != s474 /*==s473*/ )
s1748 = s274[0]->s1194();
else //if( s274[0]->s492() == s474 )
s1748 = s274[0]->s494()->s1194();
if( !s1961 && s1748 )
throw s961.s993( L"non-constant function is applied to a constant variable" );
if( s278 == s7::s1346 )
s584 = s274[0].s15<s481*>();
if( s584.s13() ) {
s584 = s300->TR().s516( s350(), s586, s586->s298() );
s584->s498( s585 );
s581.insert( s581.begin(), s584 );}
if( s274.size() ) {
s579 = (s482**)&s274[0];
nlocs = s274.size();
s578 = &s581[0];
s496 = s581.size();}
else {
s579 = NULL;
s578 = NULL;
nlocs = s496 = 0;}
s974.resize( s581.size() );
s1252();
s584->s1252();
s584->s1250( s1748 );}
void s836::s498( const s272* s1658, bool proc/*=false*/ )
{
TDException s961( s7::s1511, s1544, s601() );
s667 = proc ? s586->s298() : s1658->s298();
if( ns->s492() == s477 || ns->s492() == s476 ) {
s587( s667 );
if( s586->s492() == s476 )
return;}
if( s274.size() > s628.size() )
throw s961.s993( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
if( s573 != s565 && n == 0 && s274[n]->s616() == s7::s861 )  // ???DEBUG??? 220617
continue;
s483 par = s274[n];
if( par->s492() == s473 ) {
if( !par.s15<s369*>()->s379().s13() )
par.s15<s369*>()->reset();
par.s15<s369*>()->s498( s585.s14() ? s585.s15<s589*>() 
: s1658, false ); // ???DEBUG??? 220618
s581.push_back( par.s15<s369*>()->s375() );}
else
s841( par, n, s274[n], s1658, proc );
s481* par_ = s274[n]->s492() == s474 ? s274[n]->s494() : s274[n].s15<s481*>();
s626.s539( s629[n].s615(), par_, s480::s147 );
s628[n] = par_;
if( 0 && s274[n]->s492() == s474 ) {
s369* ref = new s369( s629[n].s615(), s300, s473 );
size_t off = s638( s629[n].s615() );
s271* s1053 = s628[off].s15<s271*>()->s494();
if( !s1053 )
s1053 = (s271*)s300->TR().s1000( s628[off]->s350() );
ref->s377( off, s1053->s501() );
s274[n].s15<s589*>()->s2172( ref );}
if( s580.size() > n ) {
if( s580[n]->s350() == Types.No ) {
if( !s580[n]->s499( s274[n].s15<s481*>() ) )
throw s961.s993( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s580[n]->s351() + L"', received - '" + par->s351() + L"'" );}
else if( !s300->TR().s1523( s274[n]->s350(), s580[n]->s350() ) ) {
throw s961.s993( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s580[n]->s351() + L"', received - '" + par->s351() + L"'" );}}}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s494()->s1194() && !s629[n].s1194() )
throw s961.s993( L"constant argument is passed to non-constant function: " + s629[n].s615() );
s628[n] = s274[n];}
s486 s1352 = s585;
s585 = 0;
for( size_t n = 0; n < s582.size(); ++n ) {
if( s582[n]->s492() == s475 ) {
s488 cs = new s559( *s582[n].s15<s559*>() );
s582[n] = s598( cs, s300, s586, this, s586->s298(), cs->s2166() );}
else if( s582[n]->s492() == s473 )
s582[n].s15<s369*>()->s498( s586, true );
else if( s582[n]->s492() != s474 &&
s582[n]->s492() != s1235 )
s582[n]->s498( s586 );
else // lambda - ?
;// throw new s16( L"unhandled expression" );
}
for( auto it : s582 ) {
if( it->s492() == s474 )
it.s15<Transd*>()->s498( s586, it.s15<Transd*>()->s2166() );}
s585 = s1352;
if( !s491 ) {
if( s582.size() ) {
s491 = s582.back()->s350();
s584 = s300->TR().s516( s350(), s586, s586->s298() );}
else {
s491 = s1143;
s584 = s363.s15<s481*>();}
s584->s1665( s7::s861 );
s581.insert( s581.begin(), s584 );}
else
s584 = (s481*)s300->TR().s1000( s350() )->s333( s585, s586 );
if( s274.size() ) {
s579 = (s482**)&s274[0];
nlocs = s274.size();
s578 = NULL;// &s581[0];
s496 = s581.size();}
else {
s579 = NULL;
nlocs = s496 = 0;
s578 = NULL;}
s974.resize( s581.size() );
s1252();}
void s589::s1896( const s575& pl ) const{
TDException s961( s7::s1889, s1544, s601() );
size_t shift = 0;
if( s573 == s566 || s573 == s564 )
shift = 1;
if( pl.size() > s628.size() + shift )
throw s961.s993( L"too many arguments to lambda call" );
if( pl.size() < s580.size() )
throw s961.s993( L"too few arguments to lambda call" );
for( size_t n = shift; n < pl.size(); ++n ) {
s483 par = pl[n];
if( s580[n]->s350() == Types.No ) {
if( !s580[n]->s499( par.s15<s481*>() ) )
throw s961.s993( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s580[n]->s351() + L"', received - '" + par->s351() + L"'" );}
else if( !s300->TR().s1523( par.s15<s271*>(), s580[n].s15<s271*>() ) ) {
throw s961.s993( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s580[n]->s351() + L"', received - '" + par->s351() + L"'" );}
if( par->s616() == s7::s862 )
throw s961.s993( L"uninitialized function parameter: " + s629[n].s615() );
if( par->s494()->s1194() && !s629[n].s1194() )
throw s961.s993( L"constant argument is passed to non-constant function: " + s629[n].s615() );}}
void s589::s2172( s369* ref ){
subject = ref;}
void s589::s594( const vector<s483>& l ){
s1896( l );
for( size_t n = 0; n < l.size(); ++n )
s274[n] = l[n];}
void s836::s2259( const std::vector<s483>& l ){
for( size_t n = 0; n < l.size(); ++n )
s274[n] = l[n];}
void s836::s2246( ){
s1896( s274 );}
s483 s589::s2284() {
if( s585.s15<s481*>() != this )
return s585->s2284();
return NULL;}
s483 s836::s2284() {
if( subject->s492() == s473 )
return subject.s15<s369*>()->s375(); 
return s1640->s2103().s15<s482*>(); // ???DEBUG??? 220802
}
void s589::s595( const s272* s1658 ){
TDException s961( s7::s1587, s1544, s601() );
if( s573 != s564 && s573 != s563 && s274.size() > s628.size() )
throw s961.s993( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s271* par = s274[n];
if( par->s492() == s475 ) {
s488 cs = new s559( *(s559*)par );
par = s598( cs, s300, (s272*)s1658, /*this*/s585, s586->s298(), false );
((s589*)par)->s498( s1658, false );
s274[n] = par;}
if( s274[n]->s492() == s479 ) {
s581.push_back( s274[n]->s494() );}
else if( s274[n]->s492() != s473 ) {
if( ( s573 != s564 && s573 != s563 ) || s278 == s233 ) {
s274[n]->s498( s1658, s2166() );
s628[n] = s274[n]->s494();
s628[n]->s1665( s7::s861 );
s626.s539( s629[n].s615(), s628[n].s15<s481*>(), s480::s147 );}}
else {
if( s573 != s564 && s573 != s563 ) {
s628[n] = s274[n].s15<s481*>();
s626.s539( s629[n].s615(), s274[n].s15<s369*>()->s375(), s480::s147 );}
if( s274[n].s15<s369*>()->s379().s13() ) {
s274[n].s15<s369*>()->s498( s585, s2159 );}}
if( s278 != s233 && n < s628.size() && n < s580.size() && !s628[n].s15<s481*>()->s499( (s481*)s580[n] ) )
throw s961.s993( L"wrong argument's type" );}
for( size_t n = 0; n < s628.size(); ++n ) {
if( s628[n]->s616() == s7::s862 )
throw s961.s993( L"parameter is not provided" );}}
void s589::s808( s829& s153 ) const{
for( size_t n = 0; n < s580.size(); ++n )
s153.push_back( make_pair( s629[n].s615(), s580[n] ) );}
void s589::s2114( s575& s2113 ){
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s492() == s473 ) {
s369* ref = s274[n].s15<s369*>();
ref->reset();
ref->s380( s2113[n].s15<s481*>() );}
else if( s274[n]->s492() == s472 ) {
s274[n] = s2113[n];}
s628[n] = s2113[n];}}
void s589::s2118( s589* s2042, s272* impl, bool proc ){
if( s2042 && s2042 != this && s2042 != s585 ) s585 = s2042;
if( 0 && subject.s14() ) // ???DEBUG??? 220728 V
subject->s2118( s585, s586, false );
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s2118( this, s586, false ); // ???DEBUG??? 220702
if( n < s628.size() ) {
s628[n]->s2118( this, s586, false ); // ???DEBUG??? 220702
s626.s539( s629[n].s615(), s628[n].s15<s482*>(), s480::s147 );}}
for( size_t n = 0; n < s582.size(); ++n )
s582[n]->s2118( this, s586,  false );}
s481* s589::s1599( s481** s687, size_t s691 ){
size_t shift = 0;
if( s573 == s563 || s573 == s564 || s573 == s2098 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s579 + n ) ) {
s470 pc = ( ( s482* )*( s579 + n ) )->s492();
if( pc == s473 || pc == s1327 ) {
s481* p = (s481*)( ( s369* )*( s579 + n ) )->s375();
*(s578 + n + shift) = p;}
else if( pc == s474 ) {
s974[n + shift] = (s481*)( ( s589* )*( s579 + n ) )->s495( s687, s691 );
if( s974[n + shift]->s616() < 0 ) {
int s153 = s974[n + shift]->s616();
if( s153 == s7::s860 || s153 == s7::s2219 )
s974[n + shift]->s1665( 0 );
else
return s974[n + shift];}
*( s578 + n + shift ) = s974[n + shift];}
else if( pc == s472 )
*( s578 + n + shift ) = ( s481* )*( s579 + n );
else if( pc == s1235 )
(void)0;}}
return NULL;}
s484 s589::s495( s481** s687, size_t s691 ){
s484 s681;
s681 = s1599( s687, s691 );
if( s681.s14() )
return s681;
for( size_t n = 0; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s578, s496 );
if( s681->s616() < 0 )
break;}
s584 = s681;
return s681;}
s484 s835::s495( s481** s687, size_t s691 ){
s481* s681 = NULL;
s681 = s1599( s687, s691 );
if( s681 )
return s681;
if( !s1961 && s581[1]->s1194() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s560( s578, s496 );
s681 = s581[0];}
catch( s16* e ) {
TDException s961( TDException::Stage::s1023, s7::s1118, 
s1122, past,	*e );
delete e;
s681 = new s359( s300, s961.Msg() );
s584 = s681;}
return s681;}
s484 s836::s495( s481** s687, size_t s691 ){
s481* s681 = s363;
if( subject.s14() && (s573 == s566 || s573 == s565 )) {
if( subject->s492() == s473 ) {
if( s278 != s7::s426 )
subject->s2118( this, s586, false );
s1640->s1647( subject.s15<s369*>()->s375() );}
else if( subject->s492() == s474 )
s1640->s1647( subject->s495(0,0) );
else {
if( s586->s492() == s478 && s585.s14() )
subject = s585->s2284();
s1640->s1647( subject.s15<s481*>() );}}
for( size_t n = 0; n < s580.size()/*nlocs*/; ++n ) {
if( *( s579 + n ) ) {
if( !( ( s482* )*( s579 + n ) )->s1195() )
throw new s16( L"uninitialized function parameter: " + s629[n].s615() );
s470 pc = ( ( s482* )*( s579 + n ) )->s492();
if( pc == s473 ) {
s481* par =( ( s369* )*( s579 + n ) )->s375();
if( par->s492() == s1235 ) {
par->s498( this, false );}
s628[n] = par;}
else if( pc == s474 ) {
s628[n] =
(s481*)( ( s589* )*( s579 + n ) )->s495( s687, s691 );
if( s628[n]->s616() < 0 ) {
int s153 = s628[n]->s616();
if( s153 == s7::s860 || s153 == s7::s2219 )
s628[n]->s1665( 0 );
else
return s628[n].s15<s481*>();}}
else if( pc == s472 )
s628[n] = *( s579 + n );}}
for( size_t n = s580.size(); n < nlocs; ++n ) {
if( *( s579 + n ) ) {
s470 pc = ( ( s482* )*( s579 + n ) )->s492();
if( pc == s473 ) {
s481* par = ( ( s369* )*( s579 + n ) )->s375();
if( par->s492() == s1235 ) {
s628[n] = par->s333(0,0);
s628[n]->s498( this, false );}}
else if( pc == s474 ) {
s628[n] =
(s481*)( ( s589* )*( s579 + n ) )->s495( s687, s691 );
if( s628[n]->s616() < 0 ) {
int s153 = s628[n]->s616();
if( s153 == s7::s860 || s153 == s7::s2219 )
s628[n]->s1665( 0 );
else
return s628[n].s15<s481*>();}}
else if( pc == s472 )
s628[n] = ( ( s482* )*( s579 + n ) )->s333(0,0);
else if( pc == s478 ) {
s628[n] = ( ( s482* )*( s579 + n ) )->s333( 0, 0 );
s628[n]->s498( this, false );}}}
for( size_t n = 0; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s578, s496 );
if( s681->s616() < 0 ) {
if( s681->s616() == s7::s860 )
s681->s1665( 0 );
break;}}
return s681;}
s1347::s1347( s262* s300, s272* s590, s589* s585, const s263* s695 )
: s836( s300, s590, s585, s590, s566, vector<s271*>(), s695 ){
s1347* pin = (s1347*)s586->s342( s7::s426, s586->s298(), false );
if( pin ) {
pin->s626.copy( s626, (s272*)s586, s585 );
s629 = pin->s629;
s628 = pin->s628;
s580 = pin->s580;}}
s1347::s1347( const s1347& right, s272* s590, s589* s591,
const std::vector<s271*>& s699, const s263* s695 )
: s836( right, s591, vector<s482*>(), s566, s695 ){
s586 = s590;
s274.assign( s699.begin() + 1, s699.end() );
s491 = right.s491;
s584 = (s481*)s699[0];}
s1347::~s1347(){}
void s1347::s498( const s272* s1658, bool proc/*=false*/ )
{
s584 = s586.s15<s272*>();
s491 = s584->s350();
s589::s498( s1658, proc );// ???DEBUG??? 220717
s581.erase( s581.begin() );// ???DEBUG??? 220717
s1252();}
s484 s1347::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
if( s586->s350() == s1702 ) {
s681 = new s832( *s586.s15<s832*>(), ns, s586.s15<s589*>(), s274, s601() );
s681->s498( s585 );}
else {
s575 s2280;
s2280.assign( s581.begin(), s581.end() );
s681 = new s272( *s586, s2280, s601(), ns );
s681->s498( s585 );
s681->s2118( NULL, (s272*)s681, s2159 );}
s681->s1252();
return s681;
wstring s189 = s601()->s291();
wstring s1348 = s601()->Src();
s1348.replace( s1348.find( s189 ), s189.size(), 1, L' ' );
s263* ast_ = new s263( s189, s1348 );
s681 = s584.s15<s272*>()->s633( *ast_, s585, s667 );
s681->s1252();
return s681;
vector<s271*> s1636( begin(s274), end(s274));
s681 = s584->s353( s585, s1636, s601() );
s681->s1252();
return s681;}
bool
s589::s554( const wstring& s672, s369* ref,	
const wstring& s332, bool fr ) const{
bool s681 = false;
wstring s76 = s672;
size_t pl = s76.find( L"." );
if( pl == string::npos ) { //a
bool s2128 = s626.s156( s76 );
bool s2129 = true;
if( s2128 ) {
size_t off = s638( s76 );
if( 0 && off >= s580.size() ) // ???DEBUG??? 220721
s2129 = false;}
if( ( !s2128 && !s2159 ) || ( !s2128 && !fr ) || (!s2128 && s2159 && fr) ||
( s2128 && !s2159 && !fr && !intro )
/*|| ( s585.s14() && !intro && s2129 )*/ ) {
if( s585.s14() && ((s573 == s563 || s573 == s2098) || !fr ||
(s490 == s1235 && !s2159 ) ) ) 
s681 = s585->s554( s76, ref, s332, s2159 );
if( !s681 ) {
if( s586.s14() )
s681 = s586->s554( s76, ref, s332, s2159 );
if( s681 ) {
if( s586->s492() != s477 && ref->s379() == s586.s15<s271*>() ) {
ref->s380( s1640.s15<s481*>() );
if( s1640.s15<s1588*>()->s2103().s13() ) // ???DEBUG??? 220904
s1640.s15<s1588*>()->s1647( s586.s15<s481*>() );}}}
if( ! s681 )
s681 = s300->s554( s76, ref, s332, true );}
if( !s681 && s2128 ) {
size_t off = s638( s76 );
s271* s1053 = s628[off].s15<s271*>()->s494();
if( !s1053 )
s1053 = (s271*)s300->TR().s1000( s628[off]->s350() );
assert( s1053 != ref );
ref->s377( off, s1053->s501() );
if( s629[off].s1194() )
ref->s1250();
ref->s380( (s481*)this /*(s482**)&s274[off]*/ );
s681 = true;}}
else {// a.y
s76 = s672.substr( pl + 1 );
wstring s682 = s672.substr( 0, pl );
s271* ob = s626.get( s682, false );
if( !ob ) {
s681 = s586->s554( s672, ref, s332, true );
if( !s681 && s585.s14() )
s681 = s585->s554( s672, ref, s332, true );}
else {
size_t off = s638( s682 );
ref->s377( off, NULL );
s681 = ob->s501()->s554( s76, ref, s332, true );
ref->s380( (s481*)this );}}
return s681;}
bool
s835::s554( const wstring& s672, s369* ref, const wstring& s332,
bool fr) const{
if( s278 == s7::s1346 &&
s274[0].s15<s481*>()->s554( s672, ref, s332, fr ) )
return true;
return s589::s554( s672, ref, s332, fr );}
s271* s589::s596( size_t off ){
s271* s681 = s628[off];
return s681;}
s271* s589::s333( s589* s2042, s272* impl ) const{
return new s589( *this );}
s271* s835::s333( s589* s2042, s272* impl ) const{
return new s835( *this, s2042 ? s2042 : s585.s15<s589*>(), ns );}
s271* s836::s333( s589* s2042, s272* impl ) const{
auto s681 = new s836( *this, s2042, std::vector<s271*>(), s573, s601(), 
impl ? impl : s586.s15<s272*>(), s586.s15<s272*>(), intro, s2159 );
return s681;}
s271* s1347::s333( s589* s2042, s272* impl ) const{
return new s1347( *this );}
void s589::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Transductor : " <<  s278 << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"this : " << 
s4::s2170( (void*)this ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"subject : " << 
s4::s2170( subject.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"Type : " << 
s491 << L" (" << s351() << L")" << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"State : " << wh << endl;
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"Call type : " << ct[s573] << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"cont : " << 
s4::s2170( s586.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s197 + s417) << L"pout : " << 
s4::s2170( s585.s15<void*>() ).c_str() << endl;
if( !s626.empty() ) {
s626.s304( pd, s197 + s417 );}
if( !s580.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"fpars : " << endl;
for( size_t n = 0; n < s580.size(); ++n ) {
s580[n]->s304( pd, s197 + s417 * 2 );}
buf << endl;}
if( !s274.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"pars : " << endl;
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->s304( pd, s197 + s417 * 2 );
buf << endl;}
buf << endl;}
if( !s629.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"namvec : " << endl;
for( size_t n = 0; n < s629.size(); ++n )
buf << s4::fill_n_ch( L' ', s197 + s417 * 2 ) << s629[n].s615()
<< "; ";
buf << endl;}
if( !s628.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"memvec : " << endl;
for( size_t n = 0; n < s628.size(); ++n ) {
s628[n]->s304( pd, s197 + s417 * 2 );}
buf << endl;}
if( !s582.empty() ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << L"exprs : " << endl;
for( size_t n = 0; n < s582.size(); ++n ) {
s582[n]->s304( pd, s197 + s417 * 2 );}
buf << endl;}}
wstring s589::trace( s1890& topics ) const{
wstringstream buf;
int s197 = 0;
wstring s1070 = std::to_wstring( reinterpret_cast<long long>(this));
s1070 = s1070.substr( s1070.size() - 5 );
if( topics.empty() ) {
s589::s304( &buf, s197 );}
else {
buf << L"Transductor : " << s1070 << endl;
if( topics == L"id" ) 
buf << L"id: " << s1070 << endl;}
return buf.str();}
static s6::s1681 s1723;
s357::s357( s262* s300, const std::wstring& s, s272* s586, const s263* ast_ )
: s1390( s300, s586, ast_ ){
s491 = Types.String;
if( !s491 )
wh = s7::s862;
else {
wh = s7::s861;
s347 = s;}
s323 = s1567;}
s357::s357( s262* s300, s272* s590, const std::vector<s271*>& l, const s263* ast_ )
: s1390( s300, s590, ast_ ){
s274.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s862;
else
wh = s7::s861;
s491 = Types.String;
s323 = s1567;}
s357::s357( const s357& r, const s263* ast_ )
: s1390( r.s300, r.ns, ast_ ){
s347 = r.s347;
for( auto p : r.s274 )
s274.push_back( p->s333( 0, (s272*)r.ns ) );
wh = r.wh;
s491 = r.s491;
s323 = s1567;}
s357::s357( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ )
: s1390( s300, NULL, ast_ ){
s347 = s;
pos = string::npos;
s491 = Types.String;
s323 = s1567;
wh = s7::s861;}
s357::~s357(){}
s481* s357::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s357( s300, s586, l );}
void s357::s348(){
s1390<s1565, wchar_t, s357, s1561>::s348();
s346 = s1390<s1565, wchar_t, s357, s1561>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s357::s1227, Types.String,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 100 ) ) );
s346.insert( make_pair( L"find", new s335( L"find", &s357::s774, s1142,
{ s1113( { Types.String } ), s1113( { s1144, s1501::s1538 } ) }, 1, 1 )));
s346.insert( make_pair( L"find-first-not-of", new s335( L"find-first-not-of", &s357::s1576, s1142,
{ s1113( { Types.String } ), s1113( { Types.String, s1142 } ), 
s1113( { Types.String, s1142, s1142 } )}, 1, 3 )));
s346.insert( make_pair( L"contains", new s335( L"contains", &s357::s2190, s1139,
{ s1113( { Types.String } ), s1113( { Types.Char } ) }, 1, 1 )));
s346.insert( make_pair( L"set", new s335( L"set", &s357::s385, s1144,
{ s1113( { Types.String } ), s1113( { s1143 } ) }, 1, 1, false )));
s346.insert( make_pair( L"set-el", new s335( L"set-el", &s357::s1580, s1144,
{ s1113( { s1142, Types.String } ), s1113( { s1142, s1567 } ) }, 2, 2 )));
s346.insert( make_pair( L"size", new s335( L"size", &s357::s326, s1142,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"starts-with", new s335( L"starts-with", &s357::s1675, s1139,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"strip", new s335( L"strip", &s357::s2140, s1144,
{ s1113(), s1113( { Types.String } ), s1113( { Types.String, Types.String } ) }, 
0, 2 ) ) );
s346.insert( make_pair( L"sub", new s335( L"sub", &s357::s788, Types.String,
{ s1113( { s1501::s1538 } ), s1113( { s1501::s1261, s1501::s1261 } ) }, 1, 2 )));
s346.insert( make_pair( L"subn", new s335( L"subn", &s357::s1583, Types.String,
{ s1113( { s1501::s1538 } ), s1113( { s1501::s1261, s1501::s1261 } ) }, 1, 2 )));
s346.insert( make_pair( L"charn", new s335( L"charn", &s357::s2245, Types.Char,
{ s1113( { s1501::s1538 } ) }, 1, 1 )));
s346.insert( make_pair( L"sum", new s335( L"sum", &s357::s386, Types.String,
{ s1113( { Types.String, s7::s1388 } ) }, 1, 100 )));
s346.insert( make_pair( L"sumeq", new s335( L"sumeq", &s357::s391, Types.String,
{ s1113( { Types.String, s7::s1388 } ) }, 1, 100 )));
s346.insert( make_pair( L"to-bytes", new s335( L"to-bytes", &s357::s1337, s1140,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"to-Int", new s335( L"to-Int", &s357::s410, s1142,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"tolower", new s335( L"tolower", &s357::s884, Types.String,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"toupper", new s335( L"toupper", &s357::s885, Types.String,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"islower", new s335( L"islower", &s357::s2223, s1139,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"isupper", new s335( L"isupper", &s357::s2225, s1139,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"swapcase", new s335( L"swapcase", &s357::s2231, Types.String,
{ s1113() }, 0, 0 )));
s346.insert( make_pair( L"rfind", new s335( L"rfind", &s357::s793, s1142,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"eq", new s335( L"eq", &s357::s396, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"not", new s335( L"not", &s357::s411, s1139,
{ s1113( ) }, 0, 0 )));
s346.insert( make_pair( L"less", new s335( L"less", &s357::s397, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"greater", new s335( L"greater", &s357::s398, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"leq", new s335( L"leq", &s357::s399, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"geq", new s335( L"geq", &s357::s400, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"neq", new s335( L"neq", &s357::s401, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"max", new s335( L"max", &s357::s1950, s1144,
{ s1113( { Types.String, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"min", new s335( L"min", &s357::s1951, s1144,
{ s1113( { Types.String, s7::s1388 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"read", new s335( L"read", &s357::s407, s1144,
{ s1113( ), s1113( { s1142 } ), s1113( { s1501::s1494 } ), 
s1113( { s1501::s1494, s1142 } ) }, 1, 2 )));
s346.insert( make_pair( L"getline", new s335( L"getline", &s357::s1472, s1142,
{ s1113(), s1113( { s1501::s1494 } ) }, 0, 1 )));
s346.insert( make_pair( L"match", new s335( L"match", &s357::s1027, s1139,
{ s1113( { Types.String } ) }, 1, 1 )));
s346.insert( make_pair( L"replace", new s335( L"replace", &s357::s2189, s1144,
{ s1113( { Types.String, Types.String/*, Types.String*/ } ),
s1113( { Types.String, Types.String, Types.String, Types.Int } ),
s1113( { Types.String, Types.String, Types.String, Types.Int, Types.Int } ),
}, 3, 5 )));
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, Types.String )->s351() + L">";
s1054 s1506 = ( (s314*)Types( s300, Types.Vector ) )->s1186( this, ts, s1705, s1269 );
s346.insert( make_pair( L"split", new s335( L"split", &s357::s1479, s1506,
{ s1113(), s1113( { Types.String } ) }, 0, 0, true, {L"plain:", L"regex:"} )));
s300->TR().s1153( s491, s7::s1401, s1501::s1497 );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );
s1723 = s1722;
s1723.s1683 = L" \n";}
void s841( s271* par, s262* s300, s272* s586,
s589* s215, s483& s153 ){
if( par->s492() == s475 ) {
s488 cs = new s559( *( (s559*)par ) );
s153 = s589::s598( cs, s300, s586, s215, s586->s298(), false );
s153.s15<Transd*>()->s498( s586, false );}
else if( 1 && par->s492() == s472 ) {
par->s498( /*s586*/ s586 );
s153 = par;}
else
s153 = par;}
void s357::s498( const s272* s873, bool ){
s315 = s300->TR().s1039( std::vector<s1054>(
{ s1703, 2, s1142, 0, s323, 0 } ) );
for( size_t n = 0; n < s274.size(); ++n ) {
s483 par = s274[n];
if( par->s492() == s475 ) {
s841( par, s300, ns, (s589*)ns, s274[n] );}
else if( par->s350() == s1404 ) {
auto pr = par.s15<s383*>();
auto rp = pr->s1185();
typename s1375::iterator s1508, s1509;
s1508 = rp.first.s15<s1130*>()->s1136();
s1509 = rp.second.s15<s1130*>()->s1136();
s1375 news( s1508, s1509 );
s347 += news;}
else if( par->s492() != s473 ) {
s347 += par->to_wstring();}
else {
if( s300->s1320() /*par.s15<s369*>()->s379().s14()*/ ) {
if( par.s15<s369*>()->s379().s13() )
par->s498( s873, false );
s347 = par.s15<s369*>()->s375()->to_wstring();}}}
s1252();}
wstring s694( wchar_t c ){
wstring s681;
if( c == L'n' )
s681 = L"\n";
else if( c == L'r' )
s681 = L"\r";
else if( c == L't' )
s681 = L"\t";
else if( c == L'\\' )
s681 = L"\\";
else {
s681 = c;}
return s681;}
s481* s357::s352( const s263& s695, s272* s586, 
const std::wstring& s332 ) const{
wstring s_ = s695.s291();
wstring s347, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s52( s_.substr( 7, s_.size() - 8 ), s48 );
if( s.empty() )
return new s357( s300, s586, std::vector<s271*>() );
vector<s271*> s699;
s271::s1323( s695, s300, s586, s332, s699 );
return s353( s586, s699, &s695 );}
else
s = s4::s52( s_, s48 );
if( s.size() ) {
size_t pos = 0;
const s938* s1044 = NULL;
if( s601() && s601()->Nqj() )
s1044 = s601()->Nqj()->s999();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1044, s, pos, s94, s1723 );
if( s94.size() ) {
s = L"";
for( size_t n = 0; n < s94.size(); ++n ) {
wstring tmp = s94[n]->s169();
pl = s88.find( tmp[0] );
if( pl != string::npos && tmp.back() == s88[pl] )
tmp = tmp.substr( 1, tmp.size() - 2 );
s += tmp;}}}
if( s.size() == 2 && s[0] == L'\\' )
s347 = s694( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s347 = s;
while( pl != string::npos ) {
if( pl == s347.size() - 1 )
break;
if( s347[pl + 1] != L'\\' ) {
wstring code = s694( s347[pl + 1] );
s347 = s347.replace( pl, 2, code );
pl = s347.find( L"\\", pl + 1 );}
else {
s347.erase( pl, 1 );
pl = s347.find( L"\\", pl + 1 );}}}
if( s347.empty() )
s347 = s;
return new s357( s300, s347, s586, &s695 );}
s271* s357::s333( s589* s2042, s272* impl ) const{
return new s357( *this );}
s1054 s357::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" )
s681 = s323;
else
s681 = s1390::s1179( s1541, l );
return s681;}
void s357::s354( s271* p ) const{
if( p->s350() == Types.String )
*( (s357*)p )->s355() = s347;
else if( p->s350() == s1142 ) {
try {
*( (s344*)p )->s355() = std::stoi( s347 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string '" + s347 + 
L"' to integer: " + U16( e.what() ) );}}
else if( p->s350() == s1141 ) {
try {
*( (s356*)p )->s355() = std::stof( s347 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string '" + s347 + 
L"' to double: " + U16( e.what() ) );}}
else if( p->s350() == s1567 )
*( (s1561*)p )->s355() = s347[0];
else
throw new s16( L"No conversion from " + s351() + L" to " + p->s351() );}
s357::operator int() const{
long s681;
if( !s4::s62( s347.c_str(), &s681 ) )
throw new s16( L"cannot cast String " + s347 + L" to Int" );
if( s681 > (std::numeric_limits<int>::max)() )
throw new s16( L"cannot cast String to Int: the value is too big: " + s347 );
return (int) s681;}
s357::operator double() const {
double s681;
if( !s4::s63( s347.c_str(), &s681 ) )
throw new s16( L"cannot cast String '" + s347 + L"' to Double" );
return s681;}
wstring s357::to_wstring( uint32_t s1553 ) const{
if( 0 && s347.front() == '\"' && 
s347.back() == '\"' )
return s347.substr( 1, s347.size() - 2 );
return s347; }
inline void s357::s1479( s481** s274, size_t s496 ){
s314* pv = (s314*)s274[0];
pv->clear();
wstring s72 = L"";
bool s2244 = false;
bool breg = false;
if( s496 > 2 ) {
if( s496 == 4 ) {
if( s274[2]->s492() == s1056 &&
s274[2]->s350() ) {
s487 rf = (s369*)s274[2];
if( rf->Id() == 2 )
breg = true;
s72 = s274[3]->to_wstring();}
else
throw new s16( L"unrecognized 2-nd parameter" );}
else
s72 = s274[2]->to_wstring();
s2244 = true;}
wstring& s = ((s357*)DR)->s347;
size_t s68 = 0, s69 = 0;
s1::s9<s357> adds = new s357( ((s357*)DR)->s300, L"", ( (s357*)DR )->ns );
if( !s2244 ) {
while( s69 != string::npos ) {
s68 = s.find_first_not_of( L" \n\r\t", s69 );
if( s68 == string::npos )
break;
s69 = s.find_first_of( L" \n\r\t", s68 );
adds->s347 = s.substr( s68, s69 - s68 );
if( adds->s347.size() )
pv->s318().push_back( (s481*)adds->s333( 0,0 ) );}}
else {
if( breg ) {
wsmatch sm;
wregex rg( s72 );
wstring::const_iterator itst = s.begin();
wstring::const_iterator iten = s.end();
while( std::regex_search( itst, iten, sm, rg ) ) {
adds->s347 = s.substr( sm.position( 1 ), sm.length( 1 ) );
s68 = s69 + s72.size();
if( adds->s347.size() )
pv->s318().push_back( (s481*)adds->s333( 0,0 ) );
s.erase( sm.position( 1 ), sm.length( 1 ) );
itst = s.begin() + sm.position( 1 );}}
else {
while( s69 != wstring::npos && s68 < s.size()) {
if( s72.size() )
s69 = s.find( s72, s68 );
else
s69 = s68 + 1;
adds->s347 = s.substr( s68, s69 - s68 );
s68 = s69 + s72.size();
if( adds->s347.size() )
pv->s318().push_back( (s481*)adds->s333( 0,0 ) );}}}}
void s357::s1920( Stream* s1919 ) const{
if( s1919->s2052() )
s1919->s1469( L"\"" 
+ s347 + 
L"\"" );
else
s1919->s1469( s347 );
return;
s1489& ss = s1919->s1949();
ss << s347;}
void s357::s1945( s1890& s ){
s347 = s;}
void s357::s1944( Stream* s1919 ){
s1919->s1450( s347, string::npos );
return;
s1486& ss = s1919->s1948();
ss >> s347;}
s1312 s357::to_bytes() const{
s1312 s681;
string s = U8(s347);
s681.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s681[n] = s[n];
return s681;}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s357*)(s482*)*s274)
#define s693 ((s358*)(s482*)*s274)
inline void s357::s1227( s481** s274, size_t s496 ){
s357* ps = (s357*)s274[1];
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 )
{ return v.push_back( (s271*)s347 ); } );
*s274 = ( s481* ) new s357( ps->s300, ps->s300, v );
if( v.size() )
s274[0]->s498( ps->ns );}
inline void s357::s385( s481** s274, size_t s496 ){
if( !PARN( 2 ) )
throw new s16( L"cannot assign Null object to String" );
( (s357*)DR )->s347 = ( (s357*)PARN( 2 ))->s347;
DR->s1252();
*s274 = (s481*)DR;}
inline void s357::s1580( s481** s274, size_t s496 ){
int pl = (int)*s274[2];
wchar_t c;
if( s274[3]->s350() == s1567 )
c = *( (s1561*)s274[3] )->s355();
else
c = ( (s357*)s274[3] )->s347[0];
( (s357*)DR )->s347[pl] = c;
*s274 = (s481*)DR;}
inline void s357::s326( s481** s274, size_t s496 ){
*( (s344*)s692 )->s355() = (int)( (s357*)DR )->s347.size();}
inline void s357::s1675( s481** s274, size_t s496 ){
wstring s690 = L"Invalid 'starts-with' syntax: ";
if( s496 < 3 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ( (s357*)DR )->s347;
const wstring& str = ( (s357*)s274[2] )->s347;
if( dr.find( str ) == 0 )
*( (s358*)s274[0] )->s355() = true;
else
*( (s358*)s274[0] )->s355() = false;}
inline void s357::s2140( s481** s274, size_t s496 ){
wstring& dr = ( (s357*)DR )->s347;
wstring str;
if( s496 == 2 )
str = L" \r\n\t";
else
str = ( (s357*)s274[2] )->s347;
if( s496 < 4 )
dr = s4::s52( dr, str );
else {
wstring& str1 = ( (s357*)s274[3] )->s347;
dr = s4::s51( str, dr, str1 );}
*s274 = (s481*)DR;}
inline void s357::s386( s481** s274, size_t s496 ){
s692->s347 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s496; ++n )
s692->s347 += PARN( n )->to_wstring();}
inline void s357::s391( s481** s274, size_t s496 ){
s692->s347 = ((s357*)DR)->s347 + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s496; ++n )
s692->s347 += PARN( n )->to_wstring();
((s357*)DR)->s347 = s692->s347;}
inline void s357::s2223( s481** s274, size_t s496 ){
wstring& str = ((s357*)DR)->s347;
bool s681 = true;
for( size_t n = 0; n < str.size(); ++n ) {
if( ! iswlower( str[0] ) ) {
s681 = false;
break;}}
*((s358*)*s274)->s355() = s681;}
inline void s357::s2225( s481** s274, size_t s496 ){
wstring& str = ((s357*)DR)->s347;
bool s681 = true;
for( size_t n = 0; n < str.size(); ++n ) {
if( ! iswupper( str[0] ) ) {
s681 = false;
break;}}
*((s358*)*s274)->s355() = s681;}
inline void s357::s884( s481** s274, size_t s496 ){
s692->s347 = ((s357*)DR)->s347;
std::for_each( s692->s347.begin(), s692->s347.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s357::s885( s481** s274, size_t s496 ){
s692->s347 = ((s357*)DR)->s347;
std::for_each( s692->s347.begin(), s692->s347.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s357::s2231( s481** s274, size_t s496 ){
s692->s347 = ((s357*)DR)->s347;
std::for_each( s692->s347.begin(), s692->s347.end(), []( wchar_t & c ) {
if( std::iswlower( c  ) ) c = towupper( c ); else c = tolower( c );
} );}
inline void s357::s788( s481** s274, size_t s496 ){
wstring s690 = L"Invalid substring specification: ";
if( s496 < 2 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ((s357*)DR)->s347;
int start = 0, end = (int) dr.size();
if( s496 > 2 ) {
start = (int)*s274[2];
if( s496 > 3 )
end = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s16( s690 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s16( s690 + L"the end position is less than 0." );
if( start > end )
throw new s16( s690 + L"the start position is greater than string's length." );}
s692->s347 = dr.substr( start, end - start );}
inline void s357::s1583( s481** s274, size_t s496 ){
wstring s690 = L"Invalid substring specification: ";
if( s496 < 2 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ((s357*)DR)->s347;
int start = 0, s680 = 1;
if( s496 > 2 ) {
start = (int)*s274[2];
if( s496 > 3 )
s680 = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( s690 + L"the start position is greater than string's length" );
if( s680 < 0 )
throw new s16( s690 + L"the characters count cannot be less than 0" );}
s692->s347 = dr.substr( start, s680 );}
inline void s357::s2245( s481** s274, size_t s496 ){
if( s496 < 2 )
throw new s16( L"charn: too few parameters." );
const wstring& dr = ((s357*)DR)->s347;
int start = 0;
if( s496 > 2 ) {
start = (int)*s274[2];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( L"charn: the char position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( L"charn: the char position is greater than string's length" );}
*((s1561*)s274[0])->s355() = dr[start];}
inline void s357::s774( s481** s274, size_t s496 ){
wstring s690 = L"Invalid 'find' syntax: ";
if( s496 < 3 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ( (s357*)DR )->s347;
const wstring& str = ( (s357*)s274[2] )->s347;
int start = 0; 
if( s496 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s690 + L"the start position is greater than string's length." );}
*((s344*)s274[0])->s355() = (int)dr.find( str, start );}
inline void s357::s1576( s481** s274, size_t s496 ){
wstring s690 = L"Invalid 'find-first-not-of' syntax: ";
if( s496 < 3 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ( (s357*)DR )->s347;
const wstring& str = ( (s357*)s274[2] )->s347;
int start = 0;
if( s496 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s690 + L"the start position is greater than string's length." );}
*((s344*)s274[0])->s355() = (int)dr.find_first_not_of( str.c_str(), start );}
inline void s357::s793( s481** s274, size_t s496 ){
wstring s690 = L"Invalid 'rfind' syntax: ";
if( s496 < 3 )
throw new s16( s690 + L"too few parameters." );
const wstring& dr = ( (s357*)DR )->s347;
const wstring& str = ( (s357*)s274[2] )->s347;
int start = (std::numeric_limits<int>::max)();
if( s496 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is less than 0." );}
*( (s344*)s274[0] )->s355() = (int)dr.rfind( str, start );}
inline void s357::s2190( s481** s274, size_t s496 ){
wstring s690 = L"Invalid 'contains' syntax: ";
const wstring& dr = ( (s357*)DR )->s347;
const wstring& str = ( (s357*)s274[2] )->to_wstring();
int start = 0; 
if( s496 > 3 ) {
start = (int)*s274[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s690 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s690 + L"the start position is greater than string's length." );}
*((s358*)s274[0])->s355() = ( dr.find( str, start ) != string::npos );}
inline void s357::s396( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() == *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s411( s481** s274, size_t s496 ){
*s693->s355() = ( (s357*)DR )->s355()->empty();}
inline void s357::s397( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() < *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s398( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() > *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s399( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() <= *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s400( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() >= *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s401( s481** s274, size_t s496 ){
*s693->s355() = *( (s357*)DR )->s355() != *( (s357*)PARN( 2 ) )->s355();}
inline void s357::s1950( s481** s274, size_t s496 ){
*s692->s355() = ( (s357*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
if( *((s357*)s274[n])->s355() > *s692->s355() )
*s692->s355() = *( (s357*)s274[n] )->s355();}}
inline void s357::s1951( s481** s274, size_t s496 ){
*s692->s355() = ( (s357*)DR )->s347;
for( size_t n = 2; n < s496; ++n ) {
if( *((s357*)s274[n])->s355() < *s692->s355() )
*s692->s355() = *( (s357*)s274[n] )->s355();}}
inline void s357::s407( s481** s274, size_t s496 ){
Stream* s1466 = NULL;
size_t s1441 = 0;
if( s496 >= 3 ) {
if( s274[2]->s350() == s1142 )
s1441 = (int)*s274[2];
else
s1466 = (Stream*)s274[2];
if( s496 == 4 )
s1441 = (int)*s274[3];}
else
s1466 = s1392;
wstring& s153 = *( (s357*)DR )->s355();
s1466->s1450( s153, s1441 );
int s681 = (int)s153.size();
s153.resize( s681 );
s274[0] = s274[1];}
inline void s357::s1472( s481** s274, size_t s496 ){
Stream* s1466 = NULL;
if( s496 >= 3 ) {
s1466 = (Stream*)s274[2];}
else
s1466 = s1392;
wstring& s153 = *( (s357*)DR )->s355();
s1466->s1451( s153 );
int s681 = (int)s153.size();
s153.resize( s681 );
*( (s344*)s692 )->s355() = s681;}
inline void s357::s1027( s481** s274, size_t s496 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1033;
wstring s = DR->to_wstring();
bool s153 = regex_match( s, s1033, rg );
*s693->s355() = s153;}
inline void s357::s2189( s481** s274, size_t s496 ){
wstring s = DR->to_wstring();
wregex rg( PARN( 2 )->to_wstring() );
wstring rep( PARN( 3 )->to_wstring() );
*((s357*)*s274)->s355() = regex_replace( s, rg, rep );}
inline void s357::s1337( s481** s274, size_t s496 ){
( (s1282*)s692 )->s318() = DR->to_bytes();}
inline void s357::s410( s481** s274, size_t s496 ){
s357* ps = (s357*)DR;
wstring sv = ps->s318();
assert( !sv.empty() );
int s163;
wsmatch s1067;
static wregex s2070( LR"regex(^\w*(\d+)\w*$)regex" );
static wregex s2069( LR"regex(^\w*([[:alnum:]]+)\:(\d+)\w*$)regex" );
if( regex_match( sv, s1067, s2070 ) ) {
s163 = (int)*DR;}
else if( regex_match( sv, s1067, s2069 ) ) {
wstring snum = s1067[1].str();
wstring s2071 = s1067[2].str();
int base = std::stoi( s2071, NULL, 10 );
s163 = std::stoi( snum, NULL, base );}
else
throw new s16( L"string cannot be converted to int: " + sv );
*( (s344*)s692 )->s355() = s163;}
void s357::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " 
<< (s347.size() ? s347 : L"\"\"") ;}
size_t s357::s320() const{
return hash<wstring>{}(s347);}
bool s357::operator==( const s481* p ) const{
return ( (s357*)p )->s347 == s347;}
bool s357::operator<( const s481* p ) const{
return s347 < ( (s357*)p )->s347;}
Iterator* s357::s1155( const s481* idx ){
s1565::iterator it;
int i = (int)*idx;
if( i >= (int)s347.size() )
it = s347.end();
else {
if( i < 0 ) {
i = (int)s347.size() + i;
if( i < 0 )
i = 0;}
it = s347.begin() + i;}
return new s1566( s300, this, it, it == s347.end() ? it : it + 1 );}
Iterator* s357::s1174( const s481* _val ){
for( auto it = begin( s347 ); it != end( s347 ); ++it )
if( *it == *( (s1285*)_val )->s355() )
return new s1566( s300, this, it, it + 1 );
return new s1566( s300, this, end( s347 ), end( s347 ) );}
s481* s357::s1181( Iterator* it ){
size_t n = std::distance( begin( s347 ), ( (s1566*)it )->s1136() );
return new s344( s300, (int)n );}
Iterator* s357::s1176() {
if( s347.size() )
return new s1566( s300, this, s347.begin(), s347.begin() + 1 ); 
return new s1566( s300, this, s347.end(), s347.end() );}
Iterator* s357::s1180() {
return new s1566( s300, this, s347.end(), s347.end() ); }
Iterator* s357::s312( s383* rv ){
if( !rv )
return new s1566( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s1566( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
vector<wstring> s948( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s811::s811( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s753, s695, true,
false ){
TDException s961( s7::s1100, s925, s695 );
if( l.empty() )
throw s961.s993( L"too few arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.String;
s589::s1232( ( vector<s271*>& )l, s948 );}
s811::s811( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s753, NULL, true,
false ){
s491 = Types.String;}
void s811::s498( const s272* s1658, bool proc ){
s589::s498( s1658, proc );
wstring s690 = L"Invalid parameters of 'substr' function: ";
if( s274[0]->s350() != Types.String )
throw new s16( s690 + L"The first parameter is not of String type." );
str = s274[0].s15<s357*>();
size_t s720 = 1;
int s771 = 0;
s736 s760 = s713;
s714 =	nTo = 1;
s787 = s734 = 0;
while( s720 < s274.size() ) {
s483 par_ = s274[s720];
s470 pc = par_->s492();
if(	pc == s473 || pc == s1056 || pc == s472 || pc == s474 ) {
s483 par;
s487 rf;
if( pc == s473 ) {
rf = par_.s15<s369*>();
par = (s271*)rf->s376();}
else if( pc == s1056 ) {
rf = par_.s15<s369*>();
par = par_;}
else
par = par_;
if( par->s350() == Types.No ) {
if( rf->Id() == s1217 ) {
if( s771 != 0 )
throw new s16( s690 + L"'from' is misplaced." );
s771 = 1;
s760 = s758;}
else if( rf->Id() == s1224 ) {
if( s771 != 0 )
throw new s16( s690 + L"'to' is misplaced." );
s771 = 1;
s760 = s810;}
else if( rf->Id() == s1210 ) {
if( s760 != s713 && s771 >= 2 )
throw new s16( s690 + L"'before' is misplaced." );
if( s760 == s810 )
s734 = -1;
else
s787 = -1;
s771 = 2;}
else if( rf->Id() == s1206 ) {
if( s760 != s713 && s771 >= 2 )
throw new s16( s690 + L"'after' is misplaced." );
if( s760 == s810 )
s734 = 1;
else
s787 = 1;
s771 = 2;}
else if( rf->Id() == s1216 ) {
if( s760 != s713 && s771 >= 3 )
throw new s16( s690 + L"'first' is misplaced." );
s771 = 3;}
else if( rf->Id() == s1220 ) {
if( s760 != s713 && s771 >= 3 )
throw new s16( s690 + L"'last' is misplaced." );
if( s760 == s810 )
nTo = string::npos;
else
s714 = string::npos;
s771 = 3;}
else
throw new s16( s690 + L"unknown parameter '" + rf->s615() + L"'." );}
else if( par->s350() == Types.String ) {
if( s760 == s758 )
s802 = par;
else if( s760 == s810 )
s795 = par;
else {
if( s802.s13() && s757.s13() )
s802 = par;
else if( s795.s13() && s717.s13() )
s795 = par;
else
throw new s16( s690 + L"unknown parameter '" + rf->s615() + L"'." );}
s771 = 0; s760 = (( s760 == s758 || s760 == s713 ) ? s810 : s758 );}
else if( par->s350() == s1142 ) {
if( s760 == s758 )
s757 = par;
else if( s760 == s810 )
s717 = par;
else {
if( s802.s13() && s757.s13() )
s757 = par;
else if( s795.s13() && s717.s13() )
s717 = par;
else
throw new s16( s690 + L"unknown parameter '" + rf->s615() + L"'." );}
s771 = 0; s760 = ( ( s760 == s758 || s760 == s713 ) ? s810 : s758 );}}
s720++;}}
s484 s811::s495( s481** s687, size_t s691 ){
size_t s192 = 0, s679 = string::npos;
wstring s755, s719;
wstring dom = str->s495( 0, 0 )->to_wstring();
if( s757.s14() ) {
s470 pc = s757->s492();
if( pc == s473 || pc == s1327 )
s192 = (size_t)(int)*s757.s15<s369*>()->s375();
else if( s757->s492() == s474 )
s192 = (size_t)(int)*s757->s495( 0, 0 );
else
s192 = (size_t)(int)*s757.s15<s344*>();}
else if( s802.s14() ) {
s755 = s802->to_wstring();
if( s714 == 1 )
s192 = dom.find( s755 );
else if( s714 == string::npos )
s192 = dom.rfind( s755 );
else
throw new s16( L"substr: nFrom =" + std::to_wstring( s714 ) );
if( s192 != string::npos ) {
if( s787 > 0 )
s192 += s755.size();
else
s192 += s787;}}
if( s717.s14() ) {
s470 pc = s717->s492();
if( pc == s473 || pc == s1327 )
s679 = (size_t)(int)*s717.s15<s369*>()->s375();
else if( s717->s492() == s474 )
s679 = (size_t)(int)*s717->s495( 0, 0 );
else
s679 = (size_t)(int)*s717.s15<s344*>();}
else if( s795.s14() ){
s719 = s795->to_wstring();
if( nTo == 1 )
s679 = dom.find( s719, s192 + 1 );
else if( nTo == string::npos )
s679 = dom.rfind( s719 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s714 ) );
if( s679 != string::npos )
s679 += s734;}
wstring s153;
if( s192 == string::npos || s192 >= s679 || s192 >= dom.size() )
s153 = L"";
else
s153 = dom.substr( s192, s679 - s192 );
s584 = new s357( s300, s153, this );
return s584;}
s271* s811::s333( s589* s2042, s272* impl ) const{
return new s811( *this );}
s383::s383( s262* s300 )
: s324( s300, NULL, NULL ), s971( false ), s972( false ), s981( 0 )//, s878( false )
{
s491 = Types.Range;
s1233 = new s1518( s300, 0, NULL );
s1234 = new s1518( s300, U64_MAX );
s1166 = new s1518( s300, 0, NULL );}
s383::s383( s262* s300, s324* s586, Iterator* it )
: s324( s300, NULL, NULL ), s978( s586 ), s1455( it ), s971( false ), s972( false ), 
s981( 0 ){
s491 = s1404;}
s383::s383( uint64_t _beg, uint64_t _end )
: s324( NULL, NULL, NULL ), s971( false ), s972( false ), s981( 0 )//, s878( false )
{
s1233 = new s1518( s300, _beg );
s1234 = new s1518( s300, _end );
s491 = s1404;
s1166 = new s1518( s300, 0, NULL );}
s383::s383( s262* s300, const wstring& s77, const s263* ast_ )
: s324( s300, NULL, ast_ ), s971( false ), s972( false ), s981( 0 )//, s878( false )
{}
s383::s383( const s383& r, const s263* ast_ )
: s324( r.s300, r.ns, ast_ ), s971( false ), 
s972( false ), s981( r.s981 ), s1166( r.s1166 )//, s878( r.s878 )
{
s491 = r.s491;}
vector<wstring> s943( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s383::s383( s262* s300, s272* s590, const vector<s271*>& l_, const s263* ast_ )
: s324( s300, s590, ast_ ), s971( false ), s972( false ), s981( 0 ), 
s1166( new s1518( s300, 0, NULL ) )//, s878( false )
{
s491 = s1404;
if( l_.empty() )
return;
TDException s961( s7::s1098, s926, ast_ );
if( l_.size() > 9 )
throw s961.s993( L"too many arguments" );
s589::s1232( ( vector<s271*>& )l_, s943 );
const size_t s1048 = 3;
std::vector<s271*> l( s1048 );
if( l_[0]->s492() == s1056 ) {
s369* rf = (s369*)l_[0];
if( rf->Id() == s1219 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1518( s300, 0, NULL );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1518( s300, 0, NULL );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s586 = l[0];
s1233 = l[1];
s1234 = l[2];
if( s586.s13() ) {
s323 = Types.s1517;
s315 = Types.s1517;}
else {
s323 = 0;
s315 = 0;}
s491 = s1404;}
s383::~s383(){
s1166 = NULL;}
s481* 
s383::s352( const s263& s695, s272* s586, const wstring& s332 ) const{
wstring s = s695.s291();
wstring s345 = s351();
if( s.find( s345 ) == 0 && ( s.size() == s345.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s345.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s690 = L"Malformed Range definition: " + s;
vector<s271*> s699;
s271::s1323( s695, s300, s586, s332, s699 );
return new s383( s300, s586, s699, &s695 );}
else
return NULL;}
void s383::s498( const s272* s873, bool ){
TDException s961( s7::s913, s926, s601(), L"wrong Range definition" );
ns = (s272*)s873;
bool s1159 = false;
try {
if( s586.s14() ) {
if( s586->s492() == s473 ) {
s586.s15<s369*>()->s498( s873 );
s1159 = s586->s1194();
s978 = (s324*)s586.s15<s369*>()->s375();}
else if( s586->s492() == s475 ) {
s483 tmp = s271::s1011( s300, s586, (s272*)s873, (s589*)s873, s873->s298(), false );
s586 = tmp;
s978 = (s324*)s586->s494();}
else {
s978 = (s324*)s271::s1011( s300, s586, (s272*)s873, (s589*)s873, s873->s298(), false );}
s323 = s978->ValType();
s315 = s978->s317();}
if( s1233.s14() ) {
if( s1233->s492() == s473 )
s1233.s15<s369*>()->s498( s873 );
else {
s483 tmp = s271::s1011( s300, s1233, (s272*)s873, (s589*)s873, s873->s298(), false );
s1233 = tmp;}}
else
s1233 = s363.s15<s482*>();
if( s1234.s14() ) {
if( s1234->s492() == s473 )
s1234.s15<s369*>()->s498( s873, false );
else {
s483 tmp = s271::s1011( s300, s1234, (s272*)s873, (s589*)s873, s873->s298(), false );
s1234 = tmp;}}
else
s1234 = s363.s15<s482*>();}
catch( s16* e ) {
throw e->s30( L"while compiling Range: '" + s601()->Src() + L"'" );}
s1252();
s1250( s1159 );}
void s383::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s383::s1227, s1404,
{ s1113( { s1501::s1538 } ), s1113( { s1142, s1142 } ),
s1113( { s1501::s1496, s1142 } ),
s1113( { s1501::s1496, s1142, s1142 } ) }, 1, 3, true ) ) );
s346.insert( make_pair( L"size", new s335( L"size", NULL, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"max-element", new s335( L"resize", NULL, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", NULL, s1143,
{ s1113() }, 0, 0, false ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s383::s396, s1139,
{ s1113( { s1501::s1496 } ) }, 1, 1, true ) ) );
s346.insert( make_pair( L"reverse", new s335( L"reverse", NULL, s1143,
{ s1113() }, 0, 0, false ) ) );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s1133 s383::s1188( const std::wstring& s341 ) const{
if( s341 == s7::s1346 || s341 == L"eq" )
return s334::s1188( s341 );
if( s978.s14() ) 
return s978->s1188( s341 );
return s1133();}
s1133 s383::s1183( const std::wstring& s341, s1113& ap ) const{
if( s341 == s7::s1346 || s341 == L"eq" )
return s334::s1183( s341, ap );
if( s978.s14() )
return s978->s1183( s341, ap );
assert( 0 );
throw;}
s1133 s383::s1178( const std::wstring& s341,
s1113& ap ) {
if( s341 == s7::s1346 )
return s334::s1178( s341, ap );
if( s978.s14() )
return s978->s1178( s341, ap );
assert( 0 );
throw;}
s1054 s383::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == s7::s1346 ) {
s681 = s1501::s1496;}
else if( s978.s14() )
return s978->s1179( s1541, l );
return s681;}
const vector<wstring>&
s383::s1182( const wstring& s341 ) const{
if( s341 == s7::s1346 || s978.s13() )
return s334::s1182( s341 );
else
return s978->s1182( s341 );}
s481* s383::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s383( s300, s586, l, ast_ );}
inline bool
s383::s499( const s481* s500 ) const{
if( s500->s350() != s350() ) {
return s300->TR().s1454( s500->s350(), s1501::s1496 );}
return true;}
size_t s383::s1129() const{
if( s978.s14() )
return s978->s1129();
else
return 0;}
s1135 s383::s1185(){
Iterator *fir = NULL, *sec = NULL;
if( s978.s14() ) {
if( s971 )
fir = s978->s1174( s1233.s15<s481*>() );
else if( s1233 == s1510 )
fir = s978->s1180();
else
fir = s978->s1155( s1233.s15<s481*>() );
if( s972 )
sec = s978->s1174( s1234.s15<s481*>() );
else if( s1234 == s1510 )
sec = s978->s1180();
else
sec = s978->s1155( s1234.s15<s481*>() );
if( s978->s1129() >= 1 && ( s1233 == s1510 || sec->operator<( fir ) ) ) {
( (s1116*)fir )->reverse();
( (s1116*)sec )->reverse();}}
return s1135( fir, sec );}
s1135 s383::s1185( s324* s590 ){
Iterator *fir, *sec;
if( s971 )
fir = s590->s1174( s1233.s15<s481*>() );
else if( s1233 == s1510 )
fir = s590->s1180();
else 
fir = s590->s1155( s1233.s15<s481*>() );
if( s972 )
sec = s590->s1174( s1234.s15<s481*>() );
else if( s1234 == s1510 )
sec = s590->s1180();
else
sec = s590->s1155( s1234.s15<s481*>() );
if( s590->s1129() >= 1 && ( s1233 == s1510 || sec->operator<( fir ) ) ){
( (s1116*)fir )->reverse();
( (s1116*)sec )->reverse();}
return s1135( fir, sec );}
inline void s383::s1227( s481** s274, size_t s496 ){
s383* r = ( (s383*)s274[1] );
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 ) 
{ return v.push_back( (s271*) s347 ); } );
s383* s1459 = new s383( r->s300, r->ns, v );
s1459->s498( r->ns );
*s274 = (s481*)s1459;}
inline void s383::s396( s481** s274, size_t s496 ){
Iterator* it = ( (s383*)s274[1] )->s312( NULL );
Iterator* it1;
if( s274[2]->s350() == s1404 )
it1 = ( (s383*)s274[2] )->s312( NULL );
else
it1 = ( (s324*)s274[2] )->s312( NULL );
bool s681 = true;
while( 1 ) {
s483 p = it->s313();
s483 p1 = it1->s313();
if( p.s13() ) {
if( p1.s14() )
s681 = false;
break;}
if( p1.s13() ) {
s681 = false;
break;}
if( !p.s15<s481*>()->operator==( p1.s15<s481*>() ) ) {
s681 = false;
break;}}
*( (s358*)(s482*)*s274 )->s355() = s681;}
s271* s383::s333( s589* s2042, s272* impl ) const{
return new s383( *this );}
void s383::s354( s271* p ) const{
p = new s383( *this );}
size_t s383::s320() const{
return (size_t)this;}
bool s383::operator==( const s481* p ) const{
return ( this == p );}
bool s383::operator<( const s481* p ) const{
return false;}
bool s383::s1964() const{
return s981 == s1535;}
Iterator* s383::s312( s383* r ){
if( s1233.s14() ) {
s470 pc = s1233->s492();
if( pc == s474 )
s1531 = s1233->s495( 0, 0 );
else if( pc == s473 )
s1531 = s1233.s15<s369*>()->s375();
else
s1531 = s1233.s15<s481*>();}
if( s1234.s14() ) {
s470 pc = s1234->s492();
if( pc == s474 )
s1532 = s1234->s495( 0, 0 );
else if( pc == s473 )
s1532 = s1234.s15<s369*>()->s375();
else
s1532 = s1234.s15<s481*>();}
if( s978.s14() )
return s978->s312( this );
s981 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1233.s15<s481*>();
return this;}
s271* s383::s313(){
if( s981 == U64_MAX ) {
if( s1531.s14() ) {
if( s1531->s350() == s1516 )
s981 = *s1531.s15<s1518*>()->s355();
else {
s1293 tmp;
s1531->s354( &tmp );
if( *tmp.s355() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s981 = *tmp.s355();}}
if( s1532.s14() ) {
if( s1532->s350() == s1516 )
s1535 = *s1531.s15<s1518*>()->s355();
else {
s1293 tmp;
s1532->s354( &tmp );
if( *tmp.s355() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1535 = *tmp.s355();}}
if( s981 > s1535 )
incr = -1;
else
incr = 1;}
else
s981 += incr;
if( s981 == s1535 ) {
s981 = U64_MAX;
return NULL;}
*s1166->s355() = s981;
return s1166;}
s271* s383::s955(){
return s316->s955();}
const s271* s383::s955() const{
return NULL;}
s271* s383::Idx(){
return NULL;}
s271* s383::El(){
return NULL;}
void s383::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Range :: " << L" curit: " << s316 << endl;}
wstring s383::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[";
if( s616() == s7::s862 )
s681 += L"_not_set_";
else {
Iterator* it = ((s383*)this)->s312( NULL );
bool b = false;
while( 1 ) {
s483 p = it->s313();
if( p.s13() )
break;
if( b ) s681 += L", ";
else b = true;
s681 += p->to_wstring();}}
s681 += L"]";
return s681;}
vector<wstring> s1126( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1125::s1125( s262* s300, const wstring& s77, const s263* ast_ )
: s324( s300, NULL, ast_ ), s980( new s369( s7::s1363, s300, s473 ) ), s981(NULL), s347( new s344( s300, 0 )), 
s681( new s344( s300, 0 )),s1343(0){
s491 = Types.Filter;}
s1125::s1125( const s1125& r, const s263* ast_ )
: s324( r.s300, r.ns, ast_ ), s980( new s369( s7::s1363, s300, s473 ) ), s981(NULL), s347( new s344( s300, 0 ) ),
s681( new s344( s300, 0 ) ), s1343(r.s1343){
*s347->s355() = (int)*r.s347;
*s681->s355() = (int)*r.s681;
ns = r.ns;
s491 = r.s491;}
s1054 s1442( size_t& idx, const vector<s271*>& l ){
if( l.size() > idx && l[idx]->s492() == s1056 )
idx++;
if( l.size() > idx )
return l[idx]->s350();
return 0;}
s1125::s1125( s262* s300, s272* s590, const vector<s271*>& l_, const s263* ast_ )
: s324( s300, s590, ast_ ), s980( new s369( s7::s1363, s300, s473 )), s981(NULL),
s347( new s344( s300, 0 ) ),	s681( new s344( s300, 0 ) ),s1343(0){
s491 = s1894;
ns = s590;
if( l_.empty() )
return;
TDException s961( s7::s1356, s926, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s961.s993( L"too many arguments" );
s589::s1232( ( vector<s271*>& )l_, s1126 );
const size_t s1048 = 3;
std::vector<s271*> l( s1048 );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s350() == s1404 ) {
range = (s383*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s492() != s1056 || ((s369*)l_[bas])->Id() != s1322 )
throw s961.s993( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s492() != s1056 || ((s369*)l_[bas])->Id() != s1226 )
throw s961.s993( L"expected the 'where:' clause" );
if( l_[bas+2]->s492() != s1056 || ((s369*)l_[bas+2])->Id() != s1322 )
throw s961.s993( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s586 = l[0];
where = l[1];
s1063 = l[2];}
s481* 
s1125::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
wstring s = s695.s291();
wstring s345 = s351();
if( s.find( s345 ) == 0 && ( s.size() == s345.size() || s[s.size() - 1] == L')' ) ) {
s483 fi = new s344( s300, 0 ), la = new s344( s300, 0 ), in = new s344( s300, 1 );
wstring sv = s4::s52( s.substr( s345.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong filter constructor syntax" );
wstring s690 = L"Malformed Filter definition: " + s;
const s263::s275& s696 = s695.s293();
size_t s691 = s696.size();
if( /*!s691 ||*/ s691 > 3 )
throw new s16( s690 );
std::vector<s271*> s274;
for( size_t n = 0; n < s691; ++n ) {
s263::s275::const_iterator it = s696.find( std::to_wstring( n ) );
s274.push_back( s271::s502( *it->second, s300, s586, s332 ) );}
return s353( s586, s274, &s695 );
if( s300->TR().s1454( s274[0]->s350(), s1501::s1496 ) )
return new s1125( s300, s586, s274 );
else
return new s944( s300, s586, s274 );}
else
return NULL;}
void s1125::s498( const s272* s873, bool ){
TDException s961( s7::s913, s926, s601(), L"wrong Filter definition");
ns = (s272*)s873;
if( s586.s13() )
return;
if( s586->s492() == s473 ) {
s487 rf = s586.s15<s369*>();
if( rf->s379().s13() )
rf->s498( s873 );
s978 = rf.s15<s369*>()->s375();}
else if( s586->s492() == s475 ) {
s483 tmp = s271::s1011( s300, s586,(s272*)s873, (s589*)s873, s873->s298(), false );
s586 = tmp;
s978 = s586->s494();}
else {
s978 = (s481*)s271::s1011( s300, s586, (s272*)s873, (s589*)s873, s873->s298(), false );}
if( !s300->TR().s1454( s978->s350(), s1501::s1496 ) )
throw s961.s993( L"the type is not rangeable: " + s978->s351() );
if( s978->s492() == s472 ) {}
else if( s978->s492() == s478 ) {}
else
throw s961.s993( L"unsupported container type" );
s980->s377( 0, s300->TR().s1000( s978.s15<s324*>()->ValType() ) );
s980->s380( (s481*)this );
if( where.s14() ) {
if( where->s492() == s473 )
where.s15<s369*>()->s498( s873 );
else
where = s271::s1011( s300, where, (s272*)this, (s589*)s873, s873->s298(), false );}
if( s1063.s14() ) {
if( s1063->s492() == s473 ) {
s1063.s15<s369*>()->s498( s873 );
s323 = s1063->s494()->s350();}
else {
if( s1063->s492() != s1235 )
s1063 = s271::s1011( s300, s1063, (s272*)s873, (s589*)s873, s873->s298(), false );
s323 = s1063.s15<s832*>()->s1318();}}
if( !s323 )
s323 = s978.s15<s324*>()->ValType();
s491 = s300->TR().s1039( s807::Cont( { s1894, 1, s323, 0 }) );
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" +
s300->TR().s1342( s300->TR().s798( s323 ) ) + L">";
s1343 = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s1252();}
void s1125::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1125::s1227, s1894,
{ s1113( { s1142, s1142 } ) }, 1, 2 ) ) );
s346.insert( make_pair( L"to-vector", new s335( L"to-vector", &s1125::s1338, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"max-element", new s335( L"resize", NULL, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", NULL, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", NULL, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"reverse", new s335( L"reverse", NULL, s1143,
{ s1113() }, 0, 0 ) ) );
s346.equal_range( s7::s1346 ).first->second->s1251( true );
s346.equal_range( L"to-vector" ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s1133 s1125::s1183( const std::wstring& s341, s1113& ap ) const{
return s334::s1183( s341, ap );
if( s341 == s7::s1346 )
return s334::s1183( s341, ap );
assert( 0 );
throw;}
s1133 s1125::s1178( const std::wstring& s341, s1113& ap ){
if( s341 == s7::s1346 ) {
auto ran = s340().equal_range( s341 );
s335* mi = ran.first->second;
s1133 s1228( s323, mi->s1127(), mi->s1194(), mi->s2002() );
return s1228;}
else if( s341 == L"to-vector" ) {
auto ran = s340().equal_range( s341 );
s335* mi = ran.first->second;
s1133 s1228( s1343, mi->s1127(), mi->s1194(), mi->s2002() );
return s1228;}
assert( 0 );
throw;}
s1054 s1125::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == s7::s1346 ) {
s681 = s1501::s1496;}
else if( s1541 == L"to-vector" ) {
s681 = s1343;}
return s681;}
s481* s1125::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1125( s300, s586, l, ast_ );
s1054 pt = l[0]->s350();
if( s300->TR().s1454( pt, s1501::s1496 ) )
return new s1125( s300, s586, l );
s589::s1232( ( vector<s271*>& )l, s1126 );
s470 pc = l[0]->s492();
vector<s271*> s906;
size_t s373 = 0;
if( pc == s472 ) {
if( pt == s1142 ) {
if( l.size() > 1 && l[1]->s350() == s1142 ) {
s906 = { l[0], l[1] };
s373 = 1;}
else {
s906 = { l[0] };
s373 = 2;}}}
else if( pc == s1056 ) {
if( ( (s369*)l[0] )->s1294() == s1224 ) {
s906 = { l[1] };
s373 = 2;}
else if( ( (s369*)l[0] )->s1294() == s1217 ) {
s906 = { l[1], l[3] };
s373 = 4;}}
vector<s271*> l1 = { new s944( s300, s586, s906 ) };
l1.insert( l1.end(), l.begin() + s373, l.end() );
return new s1125( s300, s586, l1 );
if( l.size() ) {
if( l[0]->s492() == s473 ) {
l[0]->s498( s586 );
if( s300->TR().s1454( l[0]->s350(), s1501::s1496 )  )
return new s1125( s300, s586, l );}}
else {
return new s1125( s300, s586, l );}
return new s944( s300, s586, l );}
s481* s1125::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1125* s681 = new s1125( s300, L"" );
s807::Cont s1066;
s489::s2104( vt, idx, s1066 );
s807 s1064( s1066[0] );
return s681;}
inline bool
s1125::s499( const s481* s500 ) const{
return ( ((s1125*)s500)->s350() == s350() );}
inline void s1125::s1227( s481** s274, size_t s496 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 )
{ return v.push_back( (s271*)s347 ); } );
s1125* pf = (s1125*)s274[1];
*s274 = ( s481* ) pf->s353( pf->ns, v, pf->s601() );
s274[0]->s498( pf->ns );
pf->s980->s380( s274[0] );
pf->s981 = ((s1125*)s274[0])->s981;}
inline void s1125::s1338( s481** s274, size_t s496 ){
s1125* pf = (s1125*)s274[1];
*s274 = ( s481* ) pf->s300->TR().
s1000( pf->s1343 )->s353( pf->ns );
Iterator* s1013 = pf->s312( NULL );
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
( (s314*)s274[0] )->add( p->s333(0,0) );}
s274[0]->s1252();}
s271* s1125::s333( s589* s2042, s272* impl ) const{
return new s1125( *this );}
void s1125::s354( s271* p ) const{
p = new s1125( *this );}
size_t s1125::s320() const{
return (size_t)this;}
bool s1125::operator==( const s481* p ) const{
return ( this == p );}
bool s1125::operator<( const s481* p ) const{
return false;}
bool
s1125::s554( const wstring& s672, s369* ref, const wstring& s332, bool ) const{
if( s672 == s7::s1363 ) {
ref->s1333( s980.s15<s369*>() );
return true;}
return false; // ns->s554( s672, ref, s332 );
}
s271* s1125::s596( size_t off ){
assert( off == 0 );
if( s981 )
return s981;
return (s271*) s980->s501();}
s1135 s1125::s1185(){
if( range.s14() )
return range->s1185();
else
return s978.s15<s324*>()->s1185();}
Iterator* s1125::s312( s383* r ){
if( range.s14() ) {
s1135 pr = range->s1185( );
s316 = pr.first;
s1478 = pr.second;}
else {
s316 = s978.s15<s324*>()->s312( NULL );
s1478 = NULL;}
return this;}
bool s1125::s1964() const{
if( !s981 || s316->s1964() ) //???DEBUG??? 220706
return true;
return false;}
s271* s1125::s313(){
while( 1 ) {
s981 = s316->s313();
if( !s981 && !(s1478 && s316->operator==( s1478 ) )) //???DEBUG??? 220706_1
return NULL;
if( where.s14() && ( false == (bool)*where->s495(0,0) ) )
continue;
break;}
if( s1063.s14() )
return s1063->s495( 0, 0 ).s15<s482*>();
else
return s981;}
s271* s1125::s955(){
return s316->s955();}
const s271* s1125::s955() const{
return NULL;}
s271* s1125::Idx(){
return NULL;}
s271* s1125::El(){
return NULL;}
void s1125::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s197 ) << L"Input: ";
if( s586.s14() ) {
s978.s14() ? s978->s304( pd, s197 + s417 ) : s586->s304( pd, s197 + s417 );}
buf << s4::fill_n_ch( L' ', s197 ) << L"Do: ";
if( s1063.s14() ) s1063->s304( pd, s197 + s417 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s197 ) << L"curitref: ";
s980->s304( pd, 0 );
buf << endl;}
s944::s944( s262* s300 ) 
: s324( s300, NULL, NULL ) {
s491 = Types.Seq;}
s944::s944( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ )
: s324( s300, s586, ast_ ), s1040( true ){
if( l.empty() )
return;
wstring s991 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s991 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s491 = s1405;}
s944::~s944(){}
s481* 
s944::s352( const s263& s695, s272* s586, const wstring& s332 ) const{
wstring s = s695.s291();
wstring s345 = s351();
if( s.find( s345 ) == 0 && ( s.size() == s345.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s345.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s690 = L"Malformed Sequence definition: " + s;
vector<s271*> s699;
s271::s1323( s695, s300, s586, s332, s699 );
return new s944( s300, s586, s699 );}
else
return NULL;}
s481* s944::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s944( s300, s586, l, ast_ );}
void s944::s498( const s272* s873, bool ){
if( end.s13() )
return;
wstring s991 = L"wrong sequence generator syntax";
s483 tmp = s271::s1011( s300, end, (s272*)s873, (s589*)s873, s873->s298(), false );
end = tmp;
if( start.s14() ) {
tmp = s271::s1011( s300, start, (s272*)s873, (s589*)s873, s873->s298(), false );
start = tmp;}
else {
if( end->s350() == s1142 )
start = new s344( s300, 0 );
else {
start = s300->TR().s516( end->s350(), (s272*)s873, s873->s298() );
start->s498( s873 );}}
if( incr.s14() ) {
tmp = s271::s1011( s300, incr, (s272*)s873, (s589*)s873, s873->s298(), false );
incr = tmp;}
else {
if( start->s350() == s1142 )
incr = new s344( s300, 1 );
else
throw new s16( s991 + L": increment value is missing" );}
if( start->s492() == s473 ) {
s271* p = start.s15<s369*>()->s375();
s982 = p->s333(0,0);
s1645 = p->s333(0,0);}
else {
s982 = start->s333(0,0);
s1645 = start->s333(0,0);}
std::vector<s271*> pl = { s982, incr };
s559 cs( s300, L"sumeq", pl, NULL );
s1051 = s589::s598( &cs, s300, (s272*)s873, (s589*)s873, s873->s298(), false );
s1051->s498( s873, false );
std::vector<s271*> pl1 = { s982, start };
s559 cs1( s300, L"set", pl1, NULL );
set = s589::s598( &cs1, s300, (s272*)s873, (s589*)s873, s873->s298(), false );
set->s498( s873, false );
std::vector<s271*> pl2 = { s982, end };
s559 cs2( s300, L"less", pl2, NULL );
eq = s589::s598( &cs2, s300, (s272*)s873, (s589*)s873, s873->s298(), false );
eq->s498( s873, false );
s1191 = s1142;
s323 = start->s350();
s1252();}
s1135 s944::s1185(){
s1::s1279<Iterator> it = this;
s1::s1279<Iterator> it1 = it;
return make_pair( it, it1 );}
bool s944::s1964() const{
if( (bool)*eq.s15<s589*>()->s495( 0, 0 ) )
return true;
return false;}
Iterator* s944::s312( s383* r ){
set->s495( 0, 0 );
s1040 = true;
return this;}
s271* s944::s313(){
if( s1040 )
s1040 = false;
else
s1051->s495( 0, 0 );
if(! (bool)*eq->s495( 0, 0 ) )
return NULL;
s982.s15<s481*>()->s354( s1645 );
s1645->s1252();
return s1645;}
void s944::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s944::s1227, s1405,
{ s1113( { s1142 } ), s1113( { s1142, s1142 } ), s1113( { s1142, s1142, s1142 } ) }, 
1, 2 ) ) );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s271* s944::Idx(){
return s1645; }
bool s944::operator==( const Iterator* p ) const{
return false;}
bool s944::operator<( const Iterator* p ) const{
return this < p;}
inline void s944::s1227( s481** s274, size_t s496 ){
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 )
{ return v.push_back( (s271*)s347 ); } );
*s274 = ( s481* ) new s944( ( (s944*)s274[1] )->s300, NULL, v );
s274[0]->s498( ((s944*)s274[1])->ns );}
s271* s944::s333( s589* s2042, s272* impl ) const{
return new s944( *this );}
void s944::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"SequenceGenerator : " << endl;
start->s304( pd, s197 + s417); buf << L", "; end->s304( pd, 0); 
buf << L", "; incr->s304( pd, 0 );}
s1054 s1501::s1496 = 0;
s1054 s1501::s1495 = 0;
s1054 s1501::s1497 = 0;
bool _cmp( const s483& l_, const s483& r_ ){
s481* l = l_.s15<s481*>();
s481* r = r_.s15<s481*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s483 l, const s483 r ) const{
return l.s15<s481*>()->operator<( r.s15<s481*>() );}
};
struct s1147{
std::vector<s483>s855;
s486 s853;
s1147( /*s486 s854*/ ) : s853( /*s854*/0 ) { s855.resize( 2 ); }
bool operator()( const s483& l, const s483& r ){
if( s853.s14() ) {
s855[0] = l;
s855[1] = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l.s15<s481*>()->operator<( r.s15<s481*>() );}
};
Iterator* s324::s1155( const s481* idx ){
throw new s16( L"this iterable type doesn't support access by index" );}
Iterator* s324::s1174( const s481* idx ){
throw new s16( L"this iterable type doesn't support search for value" );}
Iterator* s324::s1229( const s481* idx ){
throw new s16( L"this iterable type doesn't support distancing between elements" );}
s481* s324::s1181( Iterator* ){
throw new s16( L"this iterable type doesn't support indexing" );}
struct s834;
s481* s324::sort( bool, s834* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s869 );}
template <class _Cont, class s1301, class Der>
s311<_Cont, s1301, Der>::s311( const s1161& r )
: s324( r ){}
void s1152( s262* s300, const wstring& s77, wstring& s1263, wstring& s642 ){
assert( !s77.empty() );
wsmatch s1067;
wregex s1245( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
if( regex_match( s77, s1067, s1245 ) ) {
s1263 = s1067[1].str();
s642 = L"] " + 
( s1067[s1067.size()-1].str().empty() ? L"0" : s1067[s1067.size()-1].str() );}
else {
size_t s2257 = s77.find( L"(" );
size_t s2256 = s77.find( L"<" );
if( s2256 < s2257 ) {
size_t pl = s77.find( L">(" );
s1263 = s77.substr( 0, pl + 1 );
s642 = s4::s52( s77.substr( pl + 2, s77.size() - pl - 3 ), 
s4::s48 );}
else {
s1263 = s77.substr( 0, s2257 );
s642 = s4::s52( s77.substr( s2257 + 1, s77.size() - s2257 - 2 ), 
s4::s48 );}}
return;
assert( !s77.empty() );
wstring sv = s77;
wsmatch /*s1067,*/ rgres1;
wregex s1246( LR"regex(^(\w+(?:<[^\(]*>)?)\s*\(\s*([\w\W]*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1067, s1246 ) ) {
s807::Cont vt;
s1263 = s1067[1].str();
if( regex_match( sv, rgres1, s1245 ) ) {
s642 = L"] " + //s1263 + L" " +
( s1067[s1067.size()-1].str().empty() ? L"0" : s1067[s1067.size()-1].str() );}
else {
s642 = s1067[2];}}}
s1134::s1134( s262* s300, s1890& s77, const s263* ast_ )
: s334( s300, NULL, ast_ ), s315( 0 ), s323( 0 ){
s491 = Types.Position;
s1665( s7::s862 );}
s1134::s1134( const s1134& right, const s263* ast_ )
: s334( right.s300, right.ns, ast_ ), s586( right.s586 ), s347( right.s347 ),
s315( right.s315 ), s323( right.s323 ){
s491 = right.s491;
s1252();}
s1134::s1134( s262* s300, s272* s586, Iterator* it, const s263* ast_ )
: s334( s300, NULL, ast_ ), s347( it ), s315(0), s323( 0 ){
s491 = Types.Position;
s1252();}
s481* s1134::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
wstring s345 = s351();
if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
wstring sv = s4::s52( s.substr( s345.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong Position constructor syntax" );
wstring s690 = L"Malformed Position declaration: " + s;
const s263::s275& s696 = s695.s293();
size_t s691 = s696.size();
if( s691 )
throw new s16( s690 );
return s353( s586, vector<s271*>(), &s695 );}
else
return NULL;}
void s1134::s498( const s272* s873, bool ){
if( s347.s14() ) {
if( !s323 ) {
s323 = s347->ValType();
s807::Cont v = { s1568, 1, s315, 0 };
s491 = s300->TR().s1039( v );
if( s491 == s1568 ) {
s807::Cont v = { s1568, 1, s315, 0 };
s491 = s300->TR().s1039( v );}}}
if( !s323 && s315 )
s323 = s300->TR().s1006( s315 ).s350( 4 );}
s1054 s1134::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get-el" )
s681 = s315;
else if( s1541 == L"get-val" )
s681 = s323;
return s681;}
s481* s1134::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1134( s300, L"", ast_ );}
s481* s1134::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s807::Cont s1094;
s489::s2104( vt, idx, s1094 );
s1134* s681 = new s1134( s300, 0, NULL );
s681->ns = s586;
s681->s315 = s1094[0];
s807 s617( vt );
s681->s491 = s300->TR().s1004( vt );
return s681;}
void s1134::s348(){
s346.insert( std::make_pair( L"is-end", new s335( L"is-end", &s1134::s1965, s1139,
{ s1113( {s7::s1383} ) }, 1, 1 ) ) );
s346.insert( std::make_pair( L"eq", new s335( L"eq", &s1134::s396, s1139,
{ s1113( {s7::s1383} ) }, 1, 1 ) ) );
s346.insert( std::make_pair( L"get-el", new s335( L"get-el", &s1134::s1577, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"get-val", new s335( L"get-val", &s1134::s2250, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"get-idx", new s335( L"get-idx", &s1134::s1732, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"neq", new s335( L"neq", &s1134::s401, s1139,
{ s1113( {s7::s1383} ) }, 1, 1 ) ) );
s346.insert( std::make_pair( L"set", new s335( L"set", &s1134::s385, s1143,
{ s1113( {s7::s1383} ) }, 1, 1 ) ) );
s346.equal_range( L"get-el" ).first->second->s1251( true );
s346.equal_range( L"get-val" ).first->second->s1251( true );}
s271* s1134::s333( s589* s2042, s272* impl ) const{
return new s1134( *this );}
void s1134::s354( s271* p ) const{
p = new s1134( *this );}
size_t s1134::s320() const{
return (size_t)this;}
void s1134::operator=( const s1134& p ){
s586 = p.s586;
s347 = p.s347;
s323 = p.s323;
s315 = p.s315;
s491 = p.s491;}
bool s1134::operator==( const s481* p ) const{
return s347->operator==( ((s1134*)p)->s347 );}
bool s1134::operator<( const s481* p ) const{
return s347->operator<( ((s1134*)p)->s347 );}
s1134::operator bool() const{
if( s347->s1964() )
return false;
return true;}
#undef s692
#define s692 ((s1134*)(s482*)*s274)
#define s693 ((s358*)(s482*)*s274)
inline void s1134::s1965( s481** s274, size_t s496 ){
*((s358*)*s274)->s355() = ((s1134*)DR )->s347->s1964();}
inline void s1134::s1577( s481** s274, size_t s496 ){
s481* s681 = (s481*)((s1134*)DR )->s347->El();
*s274 = s681 ? s681 : s363;}
inline void s1134::s2250( s481** s274, size_t s496 ){
*s274 = (s481*)((s1134*)DR )->s347->s955();}
inline void s1134::s1732( s481** s274, size_t s496 ){
*s274 = (s481*)((s1134*)DR )->s347->Idx();}
inline void s1134::s396( s481** s274, size_t s496 ){
*s693->s355() = ( (s1134*)DR )->s347->operator==( ( (s1134*)s274[2] )->s347 );}
inline void s1134::s401( s481** s274, size_t s496 ){
*s693->s355() = !( (s1134*)DR )->s347->operator==( ( (s1134*)s274[2] )->s347 );}
inline void s1134::s385( s481** s274, size_t s496 ){
*(s1134*)DR = *(s1134*)s274[2];}
void s1134::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Position : " <<
this << endl;}
s957::s957( s262* s300, s314* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1204( (uint64_t)-1 ), s1164( new s1518(s300, -1) ){
if( v.s14() ) {
s1204 = std::distance( v->s318().begin(), it );
assert( s1204 >= 0 );}}
s957::s957( s262* s300, s314* v_, s1237 it, s1237 sent )
: v( v_ ), s1248( it ), s1477( sent ), s1204( (uint64_t)-1 ), s1164( new s1518(s300, -1) ){
if( v.s14() ) {
s1204 = v->size() - std::distance( v->s318().rbegin(), it ) - 1;
assert( s1204 >= 0 );}
s878 = true;}
s957::s957( s957* it )
: v( it->v ), s1205( it->s1205 ), s1204( it->s1204 ), s1164( new s1518(it->s1164->Pass(), 0, NULL) ){
s878 = it->s878;}
void s957::reverse(){
s878 = true; 
s1248 = std::make_reverse_iterator( s1205 );}
s271* s957::s313(){
s271* s681 = NULL;
if( !s878 ) {
if( s1205 != s1079 ) {
s681 = *s1205;
s1205++;
s1204++;}}
else {
if( s1248 != s1477 ) {
s681 = *s1248;
s1248++;
s1204--;}}
return s681;}
s271* s957::s955(){
if( !s878 ) {
if( s1205 == v->s318().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1205;}
else {
if( s1248 == v->s318().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1248;}}
const s271* s957::s955() const{
s271* s681 = ((s957*)this)->s955();
return s681;}
bool s957::s1964() const{
if( !s878 )
return s1205 == s1079;
return s1248 == s1477;
if( !s878 )
return s1205 == v->s318().end();
return s1248 == v->s318().rend();}
s271* s957::Idx(){
*s1164->s355() = s1204 - 1;
return s1164;}
s271* s957::El(){
if( !s878 ) {
if( s1205 == v->s318().end() )
throw new s16( (uint32_t)s16::s17::s24 );
auto s681 = new s952( NULL, NULL, vector<s271*>( { s1164, *s1205 } ) );
s681->s1665( s7::s861 );
return s681;}
else {
if( s1248 == v->s318().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
auto s681 = new s952( NULL, NULL, vector<s271*>( { s1164, *s1248 } ) );
s681->s1665( s7::s861 );
return s681;}}
s1054 s957::ValType() const{
return v->ValType();}
bool s957::operator==( const Iterator* r ) const{
if( !s878 ) {
return s1205 == ( (s957*)r )->s1205;}
else {
return s1248 == ( (s957*)r )->s1248;}}
bool s957::operator<( const Iterator* r ) const{
if( !s878 ) {
if( s1205 == v->s318().end() )
return false;
return s1205 < ( (s957*)r )->s1205;}
else {
if( s1248 == v->s318().rend() )
return false;
return s1248 < ( (s957*)r )->s1248;}}
s954::s954( s262* s300, 
s744* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1204( (uint64_t)-1 ), s1164( new s1518( s300, 0, NULL ) ){
if( v.s14() ) {
s1204 = std::distance( v->s318().begin(), it );
assert( s1204 >= 0 );}}
s954::s954( s954* it )
: v( it->v ), s1205( it->s1205 ), s1204( it->s1204 ), s1164( new s1518( it->s1164->Pass(), 0, NULL ) ){}
bool s954::s1964() const{
return s1205 == v->s318().end();}
s271* s954::s313(){
s271* s681 = NULL;
if( s1205 != v->s318().end() ) {
s681 = *s1205;
++s1205;
++s1204;}
return s681;}
s271* s954::s955(){
return *s1205;}
const s271* s954::s955() const{
return *s1205;}
s271* s954::Idx(){
*s1164->s355() = s1204 - 1;
return s1164;}
s271* s954::El(){
*s1164->s355() = s1204 - 1;
return s1164;}
s1054 s954::ValType() const{
return v->ValType();}
s932::s932( s262* s300, s322* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1164( s363 ), s1163( new s952( s300, NULL,
vector<s271*>(	{ 
s300->TR().s516( v_->s931(), s300, v_->s2154() ),
s300->TR().s516( v_->ValType(), s300, v_->s2154() )
} ) ) ){
s1163->s498( s300, true );}
s932::s932( s932* it )
: v( it->v ), s1205( it->s1205 ), s1164( s363 ), s1163( new s952( it->s1163->Pass(), NULL,
vector<s271*>(	{ 
s1205->first->s501()->s353( it->s1163->Pass() ),
s1205->second->s501()->s353( it->s1163->Pass() ) } ) ) ) // ???DEBUG??? 220514
{
s1163->s498( it->s1163->Pass(), true );}
bool s932::s1964() const{
if( !s878 )
return s1205 == v->s318().end();
return s1248 == v->s318().rend();}
s271* s932::s313(){
s271* s681 = NULL;
if( s1205 != s1079 ) {
s681 = El(); // ???DEBUG??? 220514
++s1205;}
return s681;}
s271* s932::s955(){
return (*s1205).second.s15<s482*>();}
const s271* s932::s955() const{
return (*s1205).second.s15<s482*>();}
s271* s932::Idx(){
return s1163->s318().at(0).s15<s482*>(); // ???DEBUG??? 220514
}
s271* s932::El(){
s271* s681 = NULL;
if( s1205 != v->s318().end() ) {
s1163->assign( vector<s483>(
{ ( *s1205 ).first.s15<s271*>(),( *s1205 ).second.s15<s271*>() } ));
s681 = s1163; //s1205->second; // ???DEBUG??? 220514
}
return s681;}
void s932::reverse(){
s878 = true;
s1248 = std::make_reverse_iterator( s1205 );}
s1054 s932::s317() const{
return v->s317();}
s1054 s932::ValType() const{
return v->ValType();}
bool s932::operator==( const Iterator* r ) const{
if( !s878 )
return s1205 == ( (s932*)r )->s1205;
else
return s1248 == ( (s932*)r )->s1248;}
s1372::s1372( s262* s300, s1371* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1164( s363 ), s1163( new s952( s300, NULL,
vector<s271*>( {
s300->TR().s516( v_->s931(), s300, v_->s2154() ),
s300->TR().s516( v_->ValType(), s300, v_->s2154() )
} ) ) ){
s1163->s498( s300, true );}
s1372::s1372( s1372* it )
: v( it->v ), s1205( it->s1205 ), s1164( s363 ), s1163( new s952( it->s1163->Pass(), NULL,
vector<s271*>( {
s1205->first->s501()->s353( it->s1163->Pass() ),
s1205->second->s501()->s353( it->s1163->Pass() ) } ) ) ){
s1163->s498( it->s1163->Pass(), true );}
bool s1372::s1964() const{
return s1205 == v->s318().end();}
s271* s1372::s313(){
s271* s681 = NULL;
if( s1205 != s1079 ) {
s681 = El();
++s1205;}
return s681;}
s271* s1372::s955(){
return ( *s1205 ).second.s15<s482*>();}
const s271* s1372::s955() const{
return ( *s1205 ).second.s15<s482*>();}
s271* s1372::Idx(){
return s1163->s318().at( 0 ).s15<s482*>(); // ???DEBUG??? 220514
}
s271* s1372::El(){
s271* s681 = NULL;
if( s1205 != v->s318().end() ) {
s1163->assign( vector<s483>(
{ ( *s1205 ).first.s15<s271*>(),( *s1205 ).second.s15<s271*>() } ) );
s681 = s1163;}
return s681;}
s1054 s1372::s317() const{
return v->s317();}
s1054 s1372::ValType() const{
return v->ValType();}
bool s1372::operator==( const Iterator* r ) const{
return s1205 == ( (s1372*)r )->s1205;}
s2205::s2205( s262* s300, s2204* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ){}
s2205::s2205( s262* s300, s2204* v_, s1237 it, s1237 sent )
: v( v_ ), s1248( it ), s1477( sent ){}
s2205::s2205( s2205* it )
: v( it->v ), s1205( it->s1205 ){}
bool s2205::s1964() const{
if( !s878 )
return s1205 == v->s318().end();
return s1248 == v->s318().rend();}
s271* s2205::s313(){
s271* s681 = NULL;
if( s1205 != s1079 ) {
s681 = El(); // ???DEBUG??? 220514
++s1205;}
return s681;}
s271* s2205::s955(){
return El();}
const s271* s2205::s955() const{
return ((s2205*)this)->El();}
s271* s2205::Idx(){
throw new s16( L"container is not indexable" );}
s271* s2205::El(){
if( !s878 ) {
if( s1205 == v->s318().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1205->s15<s271*>();}
else {
if( s1248 == v->s318().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1248->s15<s271*>();}}
void s2205::reverse(){
s878 = true;
s1248 = std::make_reverse_iterator( s1205 );}
s1054 s2205::ValType() const{
return v->ValType();}
bool s2205::operator==( const Iterator* r ) const{
if( !s878 )
return s1205 == ( (s2205*)r )->s1205;
else
return s1248 == ( (s2205*)r )->s1248;}
s2238::s2238( s262* s300, s2237* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ){}
s2238::s2238( s2238* it )
: v( it->v ), s1205( it->s1205 ){}
bool s2238::s1964() const{
return s1205 == v->s318().end();}
s271* s2238::s313(){
s271* s681 = NULL;
if( s1205 != s1079 ) {
s681 = El(); // ???DEBUG??? 220514
++s1205;}
return s681;}
s271* s2238::s955(){
return El();}
const s271* s2238::s955() const{
return ( (s2238*)this )->El();}
s271* s2238::Idx(){
throw new s16( L"container is not indexable" );}
s271* s2238::El(){
if( s1205 == v->s318().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1205->s15<s271*>();}
s1054 s2238::ValType() const{
return v->ValType();}
bool s2238::operator==( const Iterator* r ) const{
return s1205 == ( (s2238*)r )->s1205;}
s1283::s1283( s262* s300, s1282* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1204( (uint64_t)-1 ), s1164( new s1518( s300, -1 ) ),
s1163( new s952( NULL, NULL, vector<s271*>( { s1164, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1204 = std::distance( v->s318().begin(), it );
assert( s1204 >= 0 );}}
s1283::s1283( s262* s300, s1282* v_, s1237 it, s1237 sent )
: v( v_ ), s1248( it ), s1477( sent ), s1204( (uint64_t)-1 ), s1164( new s1518( s300, -1 ) ),
s1163( new s952( NULL, NULL, vector<s271*>( { s1164, (s271*)Types( s300, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1204 = v->size() - std::distance( v->s318().rbegin(), it ) - 1;
assert( s1204 >= 0 );}
s878 = true;}
s1283::s1283( s1283* it )
: v( it->v ), s1205( it->s1205 ), s1204( it->s1204 ), s1164( new s1518( it->s1164->Pass(), 0, NULL ) ),
s1163( new s952( v->Pass(), NULL, vector<s271*>( { s1164, new s1285( NULL, *s1205)  } ) ) ){
s878 = it->s878;}
void s1283::reverse(){
s878 = true;
s1248 = std::make_reverse_iterator( s1205 );}
bool s1283::s1964() const{
if( !s878 )
return s1205 == v->s318().end();
return s1248 == v->s318().rend();}
s271* s1283::s313(){
s271* s681 = NULL;
if( !s878 ) {
if( s1204 < v->s318().size() )
s681 = new s1285( v->Pass(), v->s318()[s1204++] );}
else {
if( s1204 != U64_MAX )
s681 = new s1285( v->Pass(), v->s318()[s1204--] );}
return s681;}
s271* s1283::s955(){
return new s1285( v->Pass(), *s1205 );}
const s271* s1283::s955() const{
return new s1285( v->Pass(), *s1205 );}
s271* s1283::Idx(){
*s1164->s355() = s1204 - 1;
return s1164;}
s271* s1283::El(){
*s1164->s355() = s1204 - 1;
return s1164;}
s1054 s1283::ValType() const{
return v->ValType();}
bool s1283::operator==( const Iterator* r ) const{
if( !s878 )
return s1205 == ( (s1283*)r )->s1205;
else
return s1248 == ( (s1283*)r )->s1248;}
bool s1283::operator<( const Iterator* r ) const{
if( !s878 )
return s1205 < ( (s1283*)r )->s1205;
else
return s1248 < ( (s1283*)r )->s1248;}
s1566::s1566( s262* s300, s357* v_, s933 it, s933 sent )
: v( v_ ), s1205( it ), s1079( sent ), s1204( (uint64_t)-1 ), s1164( new s1518( s300, -1 ) ),
s1163( new s952( v->Pass(), NULL, vector<s271*>( { s1164, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1204 = std::distance( v->s318().begin(), it );
assert( s1204 >= 0 );}}
s1566::s1566( s262* s300, s357* v_, s1237 it, s1237 sent )
: v( v_ ), s1248( it ), s1477( sent ), s1204( (uint64_t)-1 ), s1164( new s1518( s300, -1 ) ),
s1163( new s952( v->Pass(), NULL, vector<s271*>( { s1164, (s271*)Types( s300, Types.Char ) } ) ) ){
if( v.s14() ) {
s1204 = v->s318().size() - std::distance( v->s318().rbegin(), it ) - 1;
assert( s1204 >= 0 );}
s878 = true;}
s1566::s1566( s1566* it )
: v( it->v ), s1205( it->s1205 ), s1204( it->s1204 ), s1164( new s1518( it->s1164->Pass(), 0, NULL ) ),
s1163( new s952( v->Pass(), NULL, vector<s271*>( { s1164, new s1561( v->Pass(), *s1205)  } ) ) ){
s878 = it->s878;}
void s1566::reverse(){
s878 = true;
s1248 = std::make_reverse_iterator( s1205 );}
bool s1566::s1964() const{
if( !s878 )
return s1205 == v->s318().end();
return s1248 == v->s318().rend();}
s271* s1566::s313(){
s271* s681 = NULL;
if( s1205 != v->s318().end() ) {
s681 = new s1561( v->Pass(), *s1205++ );
++s1204;}
return s681;}
s271* s1566::s955(){
return new s1561( v->Pass(), *s1205 );}
const s271* s1566::s955() const{
return new s1561( v->Pass(), *s1205 );}
s271* s1566::Idx(){
*s1164->s355() = s1204 - 1;
return s1164;}
s271* s1566::El(){
auto c = new s1561( v->Pass(), *s1205 );
s1163 = new s952( v->Pass(), NULL, vector<s271*>( { s1164, c } ) );
return s1163.s15<s271*>();}
s1054 s1566::ValType() const{
return v->ValType();}
bool s1566::operator==( const Iterator* r ) const{
if( !s878 )
return s1205 == ( (s1566*)r )->s1205;
else
return s1248 == ( (s1566*)r )->s1248;}
bool s1566::operator<( const Iterator* r ) const{
if( !s878 )
return s1205 < ( (s1566*)r )->s1205;
else
return s1248 < ( (s1566*)r )->s1248;}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
vector<wstring> s1300( { L":typedTable", L":untypedTable" } );
s314::s314( s262* s300, s272* s586, const wstring& s77, const s263* ast_,
const s1681& s1745 )
: s1564( s300, s586, ast_ ){
assert( 0 );}
s314::s314( const s314& right, s272* _ns, const s263* ast_ )
: s1564( right.s300, _ns, ast_ ){
s347.resize( right.s347.size() );
for( size_t n = 0; n < right.s347.size(); ++n )
s347[n] = (s481*)right.s347[n]->s333( NULL, _ns );
s1191 = right.s1191;
s323 = right.s323;
s315 = right.s315;
s491 = right.s491;
s1665( right.s616() );}
s314::s314( s262* s300, const std::vector<s271*>& l,
s272* s586, const s263* ast_, s1054 s703,	s1054 s1266 )
: s1564( s300, s586, ast_ ){
s1191 = s1142;
s323 = s1266;
if( s323 )
s315 = s300->TR().s1039( std::vector<s1054>(
{ s1703, 2, s1191, 0, s323, 0 } ) );
if( s703 )
s491 = s703;
else
s491 = Types.Vector;
if( l.size() )
s589::s1232( ( vector<s271*>& )l, s1300 );
if( l.size() ) {
if( l[0]->s350() == s350() ||	l[0]->s350() == s1705 ) {
s347.assign( ( (s314*)l[0] )->s347.begin(),
( (s314*)l[0] )->s347.end() );}
else if( l[0]->s350() == s1142 ) {
s347.push_back( 0 );
s347.push_back( new s357( s300, L"] " + l[0]->to_wstring() ) );}}}
s314::s314( s262* s300, s1054 s1267, s272* s586, const s263* ast_ )
: s1564( s300, s586, ast_ ){
s1191 = s1142;
s323 = s1267;
if( s1267 ) {
s807::Cont v = { s1705, 1, s323, 0 };
s491 = s300->TR().s1039( v );}}
s314::~s314(){
s347.clear();}
void s314::s1303( const vector<s271*>& s699, s272* s586 ){
assert(0);
TDException s961( s7::s1289, s926, s601() );
if( s699.empty() )
return;
s470 pc = s699[0]->s492();
if( pc == s473 && s586->s492() != s474 ) {
throw s961.s993( L"references are not allowed in constructors of data members" );}
if( s699[0]->s350() == s350() ||
s699[0]->s350() == s1705 ) {
s347.assign( ( (s314*)s699[0] )->s347.begin(),
( (s314*)s699[0] )->s347.end() );}}
s1054 s314::s1186( s271* s1161, s1890& s1263, s1054 s2218, s807::Cont& s586 ){
s1054 s681;
s807::Cont vt;
size_t pos = 0;
s1054 s1267 = 0;
s1161->Pass()->TR().s1049( s1263, pos, vt );
s681 = s1161->Pass()->TR().s1004( s807( vt ), false );
if( s681 ) {
s586 = { s2218, 1, vt[2], 0 };
return s681;}
s807::Cont s1272( begin( vt ) + 2, end( vt ) );
if( s1272.size() > 2 )
s1267 = s1161->Pass()->TR().s1039( s1272 );
else
s1267 = s1272[0];
s586 = { s2218, 1, s1267, 0 };
s681 = s1161->Pass()->TR().s1039( s586 );
return s681;}
void s314::load( s271* s1161, s1054 s2218, s1890& s77, s272* s586, const s6::s1681& s1745,
s1054& pt, s1054& vt, const function<void( s484 )> s2221 ){
TDException s961( s7::s1120, s926, s1161->s601() );
if( s77[0] == L']' ) {
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s2221( s1161->Pass()->TR().s516( vt, s586, s586->s298() ) );
return;}
size_t pos = 0;
const s938* s1044 = NULL;
if( s1161->s601() && s1161->s601()->Nqj() )
s1044 = s1161->s601()->Nqj()->s999();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1044, s77, pos, s94, s1745 );
wstring ownerName = s1161->s601()->s268( s2085 ).s169();
bool s1316 = false;
if( ( s1161->s601()->s268( s2086 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1346 || ownerName.find( s7::s1346 + L"<" ) == 0 ) )
s1316 = true;
if( s94.size() ) {
s1054 s2242 = 0;
for( size_t n = 0; n < s94.size(); ++n ) {
s940 s225 = new s263( L"", *s94[n], NULL );
s225->s1334( ((s324*)s1161)->ValType() );
s225->s269( s2279, s141( L"locals" ) );
s271* s1053 = s271::s502( *s225, s1161->Pass(), s586, s586->s298() );
s2221( (s481*) s1053 );
if( s1053->s492() != s473 ) {
if( s2242 == 0 ) {
s2242 = s1053->s350();}
s1053->s2181( s2186 );}}
if( !s1316 ) {
if( !( (s324*)s1161 )->ValType() && s2242 ) {
vt = s2242;
s807::Cont v1 = { s2218, 1, vt, 0 };
pt = s1161->Pass()->TR().s1039( v1 );}
else if( vt != s2242 )
throw s961.s993( L"vector's element type doesn't match the vector type" );}
else if( !vt ) // ???DEBUG??? 220706
vt = s2242;}}
s481* s314::s352( const s263& s695, s272* s586, s1890& s332 ) const{
s1054 pt = 0, vt = 0;
wstring sv;
if( !s2211( (s324*)this, s1705, pt, vt, sv, s695, s586, s332 ) )
return NULL;
s314* s681 = new s314( s300, vector<s271*>({ }), s586, &s695,
pt, vt );
std::function<void( s484 )> s2221 = [s681]( s484 pr )
{s681->s347.push_back( pr ); };
s681->load( s681, s1705, sv, s586, s1722, s681->s491, s681->s323, s2221 );
if( !s681->s315 )
s681->s315 = s300->TR().s1039( std::vector<s1054>(
{ s1703, 2, s681->s1191, 0, s681->s323, 0 } ) );
return s681;}
bool s314::s2211( s324* s1161, s1054 s2218, s1054& pt, s1054& vt, 
wstring& sv, const s263& s695, s272* s586, s1890& s332 ){
wstring s345 = s1161->s351();
TDException s961( s7::s1290, s926, &s695,
L"wrong " + s345 + L" constructor syntax" );
wstring s = s1161->Pass()->TR().s1265( s695.s291(), s332 );
wstring s1263, s642;
if( s695.s268( s2086 ).s169() == L"CallSite" ) {
wstring s1313 = s695.s268( s2085 ).s169();
if( s1313.find( s7::s1346 + L"<" + s345 + L"<" ) == 0 ) {
wstring stype = s1313.substr( s7::s1346.size()+1, s1313.size() - (s7::s1346.size() + 2) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s961.s993( L"missing element type" );
s1152( s1161->Pass(), s1161->Pass()->TR().s1342( s ), s1263, s642 );
if( !s642.empty() && ( s642[0] == L'[' || s642[0] == L']' ) )
sv = s642;
if( !s1263.empty() ) {
s807::Cont s586;
pt = s1186( s1161, s1263, s2218, s586 );
vt = s586[2];}
else {
pt = vt = 0;}}
else
return false;
return true;}
void s314::s498( const s272* s873, bool ){
wstring s77 = L"";
TDException s961( s7::s917, s926, s601() );
if( s347.size() == 2 && s347[0].s13() )
s77 = s347[1]->to_wstring();
if( s873->s492() != s474 ||
( (s272*)s873 )->s299() != s7::s1346 || s300->s1320() ) {
if( s77[0] == L']' ) {
s347.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s347.push_back( s300->TR().s516( s323, (s272*)s873, s873->s828() ) );}
else {
for( size_t n = 0; n < s347.size(); ++n ) {
if( s347[n]->s492() == s473 ) {
if( !s347[n]->s1195() )
s347[n]->s498( s873, false );
if( s300->s1320() )
s347[n] = ( s481* ) s347[n].s15<s369*>()->s375()->s333( NULL, NULL );
else
s347[n] = (s481*)s347[n].s15<s369*>()->s333( NULL, NULL );}
else {
if( !s347[n]->s1195() ) {
s483 s1081 = s271::s1011( s300, s347[n], (s272*)s873, (s589*)s873, s873->s298(), false );
s347[n] = s1081;}}
if( !s323 )
s323 = s347[0]->s350();
else if( s347[n]->s350() && s323 != s347[n]->s350() /*&& s300->s1320()*/ )
throw s961.s993( L"elements have different types" );}}
if( s491 || s491 == s1705 ) {
if( !s323 )
throw s961.s993( L"vector's element type is not specified" );
if( !s315 )
s315 = s300->TR().s1039( std::vector<s1054>(
{ s1703, 2, s1191, 0, s323, 0 } ) );
s807::Cont s586 = { s1705, 1, s323, 0 };
s491 = s300->TR().s1039( s586 );}
s1252();}}
s484 s314::s495( s481** s274, size_t s496 ){
for( size_t n = 0; n < s347.size(); ++n ) {
if( s347[n]->s492() == s473 ) {
s347[n] = s347[n].s15<s369*>()->s375()->s495( 0, 0 )->s333( 0, 0 );}
else {
s483 s1081 = s347[n]->s495( 0, 0 ).s15<s271*>();
s347[n] = s1081;}}
return this;}
void s314::s962( const wstring& s818, const s1706& tbfr, s272* s586,
const s263* ast_ ){
TDException s961( s7::s918, s926, ast_ );
vector<wstring> s799;
s4::s57( s4::s52( s818, s48 ), tbfr.rowSep, s799 );
s1681 s1734 = s1722;
s1734.s1683 = tbfr.s1683;
for( wstring row : s799 ) {
if( !tbfr.mixedTypes ) {
s347.push_back( new s314( s300, s300, row, NULL, tbfr.s1683 ) );}
else {
s952* pd = (s952*)s300->TR().s1000( s323 )->s333(0,0);
pd->load( row, s586, s1734 );
s347.push_back( pd );}}}
void s314::s348(){
s1564<s1407, s483, s314>::s348();
s346 = s1564<s1407, s483, s314>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s314::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s346.emplace( make_pair( L"set", new s335( L"set", &s314::s385, s1143,
{ s1113( { s1501::s1496 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"set-el", new s335( L"set-el", &s314::s1254, s1143,
{ s1113( { s1501::s1538, s7::s1386 } ) }, 2, 2, false ) ) );
s346.emplace( make_pair( L"get", new s335( L"get", &s314::s325, 0,
{ s1113( { s1501::s1538 } ) }, 1, 1, true ) ) );
s346.emplace( make_pair( L"append", new s335( L"append", &s314::s1304, s1143,
{ s1113( { s7::s1386 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"sum", new s335( L"sum", &s314::s386, 0,
{ s1113( { s7::s1383, s7::s1388 } ) }, 1, 100 )));
s346.insert( make_pair( L"sumeq", new s335( L"sumeq", &s314::s391, s1143,
{ s1113( { s7::s1383, s7::s1388 } ) }, 1, 100 )));
s346.emplace( make_pair( L"mul", new s335( L"mul", &s314::s388, 0,
{ s1113( { s1501::s1538 } ) }, 1, 1, true ) ) );
s346.emplace( make_pair( L"erase", new s335( L"erase", &s314::s331, s1143,
{ s1113( { s1501::s1538 } ), s1113( { s1501::s1538, s1501::s1538 } ) }, 1, 2, false ) ) );
s346.emplace( make_pair( L"resize", new s335( L"resize", &s314::s327, s1143,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"reserve", new s335( L"reserve", &s314::s1874, s1143,
{ s1113( { s1501::s1538 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"eq", new s335( L"eq", &s314::s396, s1142,
{ s1113( { s7::s1383 } ) }, 1, 1, true ) ) );
s346.emplace( make_pair( L"for-each", new s335( L"for-each", &s314::s1731, s1143,
{ s1113( { s7::s1387 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"load-table", new s335( L"load-table", &s314::s796,
s1142, { s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":mixedTypes", 
L":stringsQuoted", L":promInts", L"colNames", L"fieldSep:", L"rowSep:", L":emptyElements" } ) ) );
s346.equal_range( L"get" ).first->second->s1251( true );
s346.equal_range( s7::s1346 ).first->second->s1251( true );
s346.equal_range( L"sum" ).first->second->s1251( true );
s346.equal_range( L"mul" ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1401, s1501::s1497 );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s314::s353( s272* s586, const vector<s271*>& l, const s263* ast_ ) const{
if( !s323 )
throw new s16( L"vector's element type is not specified" );
return new s314( s300, l, s586, ast_, s491, s323 );}
s481* s314::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s314* s681 = new s314( s300, vt[2], s586 );
return s681;}
s1054 s314::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" )
s681 = s323;
else if( s1541 == s7::s1346 || s1541 == L"sum" || s1541 == L"mul" )
s681 = s491;
else
s681 = s1564::s1179( s1541, l );
return s681;}
inline bool
s314::s499( const s481* s500 ) const{
return ( ( (s314*)s500 )->s323 == s323 );}
s271* s314::s333( s589* s2042, s272* impl ) const{
return new s314( *this, impl, s601() );}
void s314::s354( s271* p ) const{
s314* pv = (s314*)p;
pv->s347.assign( s347.begin(), s347.end() );
pv->s1665( wh );}
s481* s314::s1525( const s481* p ) const{
if( s350() == p->s350() ) {
s481* s681 = (s481*)p->s333(0,0);
return s681;}
else if( s300->TR().s1454( p->s350(), s1501::s1496 ) ) {
const s481* proto = s300->TR().s1000( s323 );
s314* s681 = (s314*)p->s501()->s333( 0, ns );
s681->s491 = s491;
s681->s323 = s323;
s681->s315 = s315;
if( proto->s492() == s476 ) {
Iterator* s1013 = ( (s324*)p )->s312( NULL );
while( 1 ) {
s483 s2168 = s1013->s313();
if( s2168.s13() )
break;
s481* p = proto->s353( ns, vector<s271*>( { s2168 } ), s601() );
p->s498( ns, true ); // ???DEBUG??? 220730
s681->s347.push_back( p );}}
s681->s1252();
return s681;}
throw new s16( L"no conversion from '" + s351() + L"' to '" + p->s351() + L"'" );}
Iterator* s314::s1155( const s481* idx ){
s1407::iterator it;
int i = (int)*idx;
if( i >= (int)s347.size() )
it = s347.end();
else {
if( i < 0 ) {
i = (int)s347.size() + i;
if( i < 0 )
i = 0;}
it = s347.begin() + i;}
return new s957( s300, this, it, it == s347.end() ? it : it+1 );}
Iterator* s314::s1174( const s481* _val ){
for( auto it = begin( s347 ); it != end( s347 ); ++it )
if( it->s15<s481*>()->operator==( _val ) )
return new s957( s300, this, it, it+1 );
return new s957( s300, this, end( s347 ), end( s347 ));}
s481* s314::s1181( Iterator* it ){
size_t n = std::distance( begin( s347 ), ( (s957*)it )->s1136() );
return new s344( s300, (int)n );}
Iterator* s314::s1176() {
if( s347.size() )
return new s957( s300, this, s347.begin(), s347.begin()+1 ); 
return new s957( s300, this, s347.end(), s347.end() ); }
Iterator* s314::s1180() {
return new s957( s300, this, s347.end(), s347.end() ); }
void s314::add( s482* el ){
s347.push_back( (s481*) el->s333( 0, ns ) );}
#undef s692
#define s692 ((s314*)(s482*)*s274)
inline void s314::s1227( s481** s274, size_t s496 ){
s314* ps = (s314*)DR;
s314* s681;
if( s496 == 2 ) {
s681 = (s314*)( s274[1] )->s333( 0, ps->ns );}
else if( s274[2]->s1187().s350() == s1705 ) {
s681 = (s314*) ps->s1525( s274[2] );}
else if( s274[2]->s1187().s350() == s1404 ) {
auto pr = (s383*)s274[2];
auto rp = pr->s1185();
typename s1375::iterator s1508, s1509;
s1508 = rp.first.s15<s1130*>()->s1136();
s1509 = rp.second.s15<s1130*>()->s1136();
s681 = new s314( ps->s300, vector<s271*>(), ps->ns, ps->s601() );
s681->s347.assign( s1508, s1509 );}
else {
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 )
{ return v.push_back( (s271*)s347 ); } );
s681 = new s314( ps->s300, v, ps->ns, ps->s601(), ps->s491,
ps->s323 );}
if( !s681->s1195() )
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s314::s385( s481** s274, size_t s496 ){
s314* v = ( (s314*)DR );
s324* seq = (s324*)s274[2];
Iterator* s1013 = seq->s312( NULL );
v->s347.clear();
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
v->s347.push_back( p );}}
inline void s314::s1254( s481** s274, size_t s496 ){
s314* v = ( (s314*)DR );
size_t idx = (size_t)(int)*s274[2];
if( idx >= v->size() )
throw new s16( L"vector index is out of range",
(uint32_t)s16::s17::s24 );
s271* el = v->s347[idx];
s274[3]->s354( el );
el->s1252();}
inline void s314::s325( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
int idx = (int)*s274[2];
if( idx < 0 ) {
idx = (int)pv->s347.size() + idx;
if( idx < 0 )
throw new s16( L"negative index is out of bound" );}
if( idx >= (int)pv->s347.size() )
throw new s16( L"index is out of bound" );
*s274 = (s481*)(s271*)pv->s347[idx];}
inline void s314::s331( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
int idx = (int)*s274[2];
int s163 = 1;
if( s496 > 3 )
s163 = (int)*s274[3];
if( idx >= (int)pv->s347.size() )
throw new s16( L"index is out of bound" );
auto it1 = pv->s347.begin() + idx;
s1407::iterator it2;
if( idx + s163 >= pv->s347.size() )
it2 = pv->s347.end();
else
it2 = pv->s347.begin() + idx + s163;
pv->s347.erase( it1, it2 );}
inline void s314::s1304( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
pv->s347.push_back( s274[2]->s333(0,0)->s495(0,0).s15<s271*>());
( (s314*)DR )->s347.back()->s498( s274[0]->s2293(), true ); // ???DEBUG??? 220805
}
inline void s314::s386( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
s692->s347 = ((s314*)pv)->s347;
for( size_t n = 2; n < s496; ++n )
s692->s347.insert( s692->s347.end(), ((s314*)PARN( n ))->s347.begin(),
((s314*)PARN( n ))->s347.end() );}
inline void s314::s391( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
for( size_t n = 2; n < s496; ++n )
pv->s347.insert( pv->s347.end(), ((s314*)PARN( n ))->s347.begin(),
((s314*)PARN( n ))->s347.end() );}
inline void s314::s1731( s481** s274, size_t s496 ){
using s1121 = s314;
using s933 = s957;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s832* s1749 = (s832*)s274[2];
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename s1375::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
while( s1508 != s1509 ) {
s1749->s594( vector<s483>( { *s1508 } ) );
s1749->s495( 0, 0 );
++s1508;}}
inline void s314::s1874( s481** s274, size_t s496 ){
s314* pv = (s314*)DR;
pv->s347.reserve( (int)*s274[2] );}
inline void s314::s327( s481** s274, size_t s496 ){
int size = (int)*s274[2];
s314* pv = ( (s314*)DR );
int oldsize = (int)( (s314*)DR )->s347.size();
pv->s347.resize( size );
for( int i = oldsize; i < size; ++i ) {
pv->s347[i] = pv->s300->TR().s516( pv->s323, pv->s300, pv->s497 );
pv->s347[i]->s498( pv->ns, true );}}
inline void s314::s388( s481** s274, size_t s496 ){
int s163 = (int)*s274[2];
s314* pv = ( (s314*)DR );
s314* s681 = (s314*)pv->s333( 0, 0 );
for( size_t n = 0; n < s163 - 1; ++n ) {
s681->s347.insert( s681->s347.end(), pv->s347.begin(), pv->s347.end() );}
*s274 = s681;}
inline void s314::s396( s481** s274, size_t s496 ){
size_t size = ( (s314*)DR )->s347.size();
s314* right = (s314*)s274[2];
if( right->s347.size() != size ) {
*( (s344*)*s274 )->s355() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( ! right->s347[n].s15<s481*>()->operator==( ( (s314*)DR )->s347[n].s15<s481*>() )) {
*( (s344*)*s274 )->s355() = 0;
return;}}
*( (s344*)*s274 )->s355() = 1;}
inline void s314::s796( s481** s274, size_t s496 ){
s314* pv = ( (s314*)DR );
const wstring& s818 = PARN( 2 )->to_wstring();
s1706 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s496 ) {
s483 par_ = s274[n];
s470 pc = par_->s492();
if( pc == s1056 ) {
s483 par;
s487 rf;
rf = par_.s15<s369*>();
par = par_;
if( par->s350() == Types.No ) {
if( rf->Id() == s1741 ) {
tbfr.mixedTypes = true;}
else if( rf->Id() == s1739 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1737 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1736 ) {
tbfr.s1683 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1738 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1828 ) {
tbfr.s1812 = true;}
else if( rf->Id() == s1735 ) {
if( s496 < n + 2 )
throw new s16( L"Vector::(load-table): the 'colNames:' value is missing" );
tbfr.s1720 = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Vector::(load-table): unknown parameters" );
++n;}
pv->s962( s818, tbfr, pv->ns, pv->s601() );}
struct s844{
vector<s483>& s347;
s844( vector<s483>& s689 ) : s347( s689 ) {}
bool operator()( const s483 l, const s483 r ) const{
return l.s15<s481*>()->operator<( r.s15<s481*>() );}
};
s481* s314::sort( bool s878, s834* cmp ){
s844 s843( s347 );
if( s878 ) {
if( cmp )
std::sort( s347.rbegin(), s347.rend(), *cmp );
else
std::sort( s347.rbegin(), s347.rend(), s843 );}
else {
if( cmp )
std::sort( s347.begin(), s347.end(), *cmp );
else
std::sort( s347.begin(), s347.end(), s843 );}
return this;}
wstring s314::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[";
if( s616() == s7::s862 )
s681 += L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n )
s681 += s347[n]->to_wstring() + ( n == s347.size() - 1 ? L"" : L", " );}
s681 += L"]";
return s681;}
void s314::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
bool s2057 = s1919->s2052();
s1919->s2051();
ss << L"[";
if( s616() == s7::s862 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n ) {
s347[n].s15<s481*>()->s1920( s1919 );
if( n < s347.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2057 )
s1919->s2050();}
void s314::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Vector : " << this << endl;
for( size_t n = 0; n < s347.size(); ++n ) {
s347[n]->s304( pd, s197 + s417 );
buf << endl;}}
size_t s314::s320() const{
size_t s681 = 0;
for( size_t n = 0; n < s347.size(); ++n )
s681 = s681 * ( ( s481* )&( *s347[n] ) )->s320() << 1;
return s681;}
bool s314::operator==( const s481* p ) const{
if( ( (s314*)p )->s347.size() != s347.size() )
return false;
for( size_t n = 0; n < s347.size(); ++n )
if( !( ( s271* )&( *s347[n] ) == (s271*)( (s314*)p )->s347[n] ) )
return false;
return true;}
bool s314::operator<( const s481* p ) const{
return false;}
Iterator* s314::s312( s383* rv ){
if( !rv )
return new s957( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s957( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
s744::s744( s262* s300, s272* s586, const wstring& s77,
const s263* ast_, const s1706& tbfr )
: s324( s300, s586, ast_ ){
if( s77.size() ) {
s1681 s1745;
s1745.s151 = true;
s1745.s1718 = tbfr.stringsQuoted;
s1745.s1730 = tbfr.s1812;
vector<s1::s9<s6::s141>> s153;
const s938* s1044 = NULL;
if( ast_ )
s1044 = ast_->Nqj()->s999();
if( s77[0] == L'[' ) {
size_t pos = 0;
s6::s178( s1044, s77, pos, s153, s1745 );}
else
s6::s178( s1044, s77, s153, s1745 );
s940 s225;
for( size_t n = 0; n < s153.size(); ++n ) {
s225 = new s263( L"", *s153[n], NULL );
if( ( !tbfr.stringsQuoted && s153[n]->s164() == s134 ) ||
s153[n]->s164() == s139 || s225->s297() == s228 ) {
s225->s1334( Types.String );
s225->s1857( s224::s225 );
s225->s1754( L"\"" + 
s225->s291() + 
L"\"" );}
else if( tbfr.promInts && s153[n]->s164() == s140 )
s225->s1334( s1141 );
if( s225->s291().empty() ) {
if( s1745.s1730 )
s225->s1754( Types( s300, Types.String )->s351() + L"()" );
else
throw new s16( L"empty element in an UntypedVector. To allow"
L" empty elements, use the ':emptyEls' marker." );}
s347.push_back( (s481*) s271::s502( *s225, s300, s586, s586->s298() ) );}}
s491 = s1704;}
s744::s744( s262* s300, const vector<s271*>& l,
const s263* ast_ )
: s324( s300, NULL, ast_ ){
for( auto s1053 : l )
s347.push_back( (s481*)s1053 );
s491 = s1704;}
s744::s744( const s744& right )
: s324( right ){
s347.resize( right.s347.size() );
for( size_t n = 0; n < right.s347.size(); ++n )
s347[n] = (s481*)right.s347[n]->s333( NULL, right.ns );
s491 = right.s491;}
s744::~s744(){
s347.clear();
s497.clear();}
void s744::s1151( s1890& s77, wstring& s1263, wstring& s642,
vector<s1::s9<s6::s141>>& s94, const s263* ast_, const s1681& s1745 ){
assert( !s77.empty() );
if( s77[0] == L'[' ) {
size_t pos = 0;
const s938* s1044 = NULL;
if( ast_ && ast_->Nqj() )
s1044 = ast_->Nqj()->s999();
s6::s178( s1044, s77, pos, s94, s1745 );}
else
s1152( s300, s77, s1263, s642 );}
s481* s744::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s695.s291();
wstring sv;
wstring s345 = s351();
if( s.find( L"UVector[" ) == 0 )
sv = s.substr( 7 );
else if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s52( s.substr( s345.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong vector constructor syntax" );
sv = s4::s52( sv.substr( 1, sv.size() - 2 ), L" " );}
else
return 0;
return new s744( s300, s586, sv, &s695 );}
void s744::s498( const s272* s873, bool ){
for( size_t n = 0; n < s347.size(); ++n ) {
if( s347[n]->s492() == s473 ) {
s347[n]->s498( s873, true );}
else {
s483 s1081 = s271::s1011( s300, s347[n], (s272*)s873, (s589*)s873, s873->s298(), false );
s347[n] = s1081;}}
s491 = s1704;
s1665( s7::s861 );
s497 = s873->s828();}
s484 s744::s495( s481** s274, size_t s496 ){
for( size_t n = 0; n < s347.size(); ++n ) {
if( s347[n]->s492() == s473 ) {
s347[n] = s347[n].s15<s369*>()->s375()->s495(0,0)->s333(0,0);}
else {
s483 s1081 = s347[n]->s495( 0, 0 ).s15<s271*>();
s347[n] = s1081;}}
return this;}
void s744::s348(){
s346.insert( make_pair( L"set", new s335( L"set", &s744::s385, s1143,
{ s1113( { s1142, s7::s1382, s7::s1388 } ) }, 2, (size_t)-1 ) ) );
s346.insert( make_pair( L"get", new s335( L"get", &s744::s325, 0,
{ s1113( { s1142 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"fst", new s335( L"fst", &s744::s995, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"snd", new s335( L"snd", &s744::s1068, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"append", new s335( L"append", &s744::s1304, s1143,
{ s1113( { s7::s1382, s7::s1388 } ) }, 1, (size_t)-1 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s744::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"resize", new s335( L"resize", &s744::s327, s1143,
{ s1113( { s1142 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", &s744::s328, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s744::s396, s1142,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"for-each", new s335( L"for-each", &s744::s1731, s1143,
{ s1113( { s7::s1387 } ) }, 1, 1 ) ) );
s346.equal_range( L"get" ).first->second->s1251( true );
s346.equal_range( L"fst" ).first->second->s1251( true );
s346.equal_range( L"snd" ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s744::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s744( s300, s586, L"", ast_, s1724 );}
s481* s744::s353( s272* s586, const std::vector<s1054>& vt ) const{
assert( 0 );
return 0;}
s1054 s744::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"fst" )
s681 = s347[0]->s350();
else if( s1541 == L"snd" )
s681 = s347[1]->s350();
else if( s1541 == L"get" ) {
return s7::s1542 + 1;
if( l[0]->s350() != s1142 )
throw new s16( L"individual elements of an UntypedVector can be accessed "
"only by a literal numerical index" );
int n = (int)*l[0];
s681 = s347[n]->s350();}
return s681;}
inline bool
s744::s499( const s481* s500 ) const{
return ( ( (s314*)s500 )->s350() == s350() );}
s1054 s744::s317() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s271* s744::s333( s589* s2042, s272* impl ) const{
return new s744( *this );}
void s744::s354( s271* p ) const{
p = new s744( *this );}
void s744::assign( const vector<s483>& p ){
s347.assign( begin( p ), end( p ) );}
Iterator* s744::s1176() {
if( s347.size() )
return new s954( s300, this, s347.begin(), s347.begin() + 1 ); 
return new s954( s300, this, s347.end(), s347.end() ); }
Iterator* s744::s1180(){
return new s954( s300, this, s347.end(), s347.end() ); }
s1135 s744::s1185(){
return std::make_pair( s1176(), s1180() );}
#undef s692
#define s692 ((s744*)(s482*)*s274)
inline void s744::s385( s481** s274, size_t s496 ){
s274[3]->s354( ( (s744*)DR )->s347[(int)*s274[2]] );}
inline void s744::s325( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s744*)DR )->s347[(int)*s274[2]];}
inline void s744::s995( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s744*)DR )->s347[0];}
inline void s744::s1068( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s744*)DR )->s347[1];}
inline void s744::s1304( s481** s274, size_t s496 ){
/*if( ( (s744*)DR )->s317() != s274[2]->s493() )
throw new s16( L"unmatched element type" );*/
( (s744*)DR )->s347.push_back( (s481*)s274[2]->s333(0,0) );}
inline void s744::s326( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s744*)DR )->s347.size();}
inline void s744::s327( s481** s274, size_t s496 ){
int size = (int)*s274[2];
( (s744*)DR )->s347.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s744*)DR )->s347[i] = ( (s744*)DR )->s300->s216(
( (s744*)DR )->s315, ( (s744*)DR )->s497 ).s15<s482*>();*/
}
inline void s744::s328( s481** s274, size_t s496 ){
( (s744*)DR )->s347.clear();}
inline void s744::s1731( s481** s274, size_t s496 ){
using s1121 = s744;
using s933 = s954;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s832* s1749 = (s832*)s274[2];
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename s1375::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
while( s1508 != s1509 ) {
s1749->s594( vector<s483>( { *s1508 } ) );
s1749->s495( 0, 0 );
++s1508;}}
inline void s744::s396( s481** s274, size_t s496 ){
size_t size = ( (s744*)DR )->s347.size();
s744* right = (s744*)s274[2];
if( right->s347.size() != size ) {
*( (s344*)*s274 )->s355() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s347[n] != ( (s744*)DR )->s347[n] ) {
*( (s344*)*s274 )->s355() = 0;
return;}}
*( (s344*)*s274 )->s355() = 1;}
inline void s744::s329( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s744*)DR )->s347.size();}
wstring s744::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"UT[";
if( s616() == s7::s862 )
s681 += L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n )
s681 += s347[n]->to_wstring() + ( n == s347.size() - 1 ? L"" : L", " );}
s681 += L"]";
return s681;}
void s744::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
bool s2057 = s1919->s2052();
s1919->s2051();
ss << L"[";
if( s616() == s7::s862 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n ) {
s347[n].s15<s481*>()->s1920( s1919 );
if( n < s347.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2057 )
s1919->s2050();}
void s744::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s347.size(); ++n )
s347[n]->s304( pd, s197 + s417 );}
size_t s744::s320() const{
size_t s681 = 1;
for( size_t n = 0; n < s347.size(); ++n ) {
size_t h = ( ( s481* )&( *s347[n] ) )->s320();
if(!h) h = 501316864073;
s681 = s681 * h << 1;}
return s681;}
bool s744::operator==( const s481* p ) const{
if( ( (s744*)p )->s347.size() != s347.size() )
return false;
for( size_t n = 0; n < s347.size(); ++n ) {
const s481* l = s347[n].s15<s481*>();
const s481* r = ( (const s744*)p )->s347[n].s15<s481*>();
if( !( *l == r ) )
return false;}
return true;}
bool s744::operator<( const s481* p ) const{
return false;}
Iterator* s744::s312( s383* rv ){
return NULL;}
/*s484 s744::s313()
{
if( s316 == s347.end() ) {
return NULL;}
s484 s681 = ( *s316 ).s15<s481*>();
s316++;
return s681;
}*/
s952::s952( s262* s300, s272* s586, s1890& s77, const s263* ast_, const s1681& s1745 )
: s744( s300, s586, ast_ ){
s1191 = s1142;
if( s77.size() ) {
s1151( s77, s586, s1745 );}
if( !s491 )
s491 = Types.Tuple;}
s952::s952( s262* s300, s272* s586, const vector<s271*>& l,
const s263* ast_, s1054 s703 )
: s744( s300, l, ast_ ){
if( s703 )
s491 = s703;
else
s491 = s1703;}
s952::s952( const s952& right, const s263* ast_ )
: s744( right ){
s491 = right.s491;
s315 = right.s315;
s1191 = right.s1191;
s323 = right.s323;}
s481* s952::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s = s300->TR().s1265( s695.s291(), s332);
wstring sv;
wstring s345 = s351();
if( s.find( L"[[" ) == 0 )
sv = s;// s.substr( 1, s.size() - 2 );
else if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
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
s952* s681 = new s952( s300, s586, sv, &s695 );
return s681;}
void s952::s498( const s272* s873, bool ){
wstring s77 = L"";
TDException s961( s7::s917, s926, s601() );
if( s347.size() == 2 && s347[0].s13() )
s77 = s347[1]->to_wstring();
if( s77[0] == L']' ) {
s347.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
s940 ast_ = new s263( s77.substr( 9, s77.size() - snum.size() - 10 ), s601()->Nqj(), (s263*)s601() );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s347.push_back( s300->TR().s516( *(s263*)ast_, (s272*)s873, s873->s828() ) );}
else if( s347.size() ) {
s807::Cont s1269;
wstring ts = Types( s300, Types.Tuple )->s351() + L"<";
for( size_t n = 0; n < s347.size(); ++n ) {
if( s347[n]->s492() == s473 ) {
if( !s347[n]->s1195() )
s347[n]->s498( s873, false );
if( s300->s1320() )
s347[n] = (s481*)s347[n].s15<s369*>()->s375()->s333( NULL, NULL );
else {
s347[n] = (s481*)s347[n].s15<s369*>()->s333( NULL, NULL ); // ???DEBUG??? 220805
}}
else {
s483 s1081;
if( !s347[n]->s1195() ) {
s1081 = s271::s1011( s300, s347[n], (s272*)s873, (s589*)s873, s873->s298(), false );
s347[n] = s1081;}}
ts += s300->TR().s1342( s347[n]->s351() );
if( n < s347.size() - 1 )
ts += L" ";}
ts += L">";
s491 = s1186( ts, s1269 );}
s1665( s7::s861 );
s497 = s873->s298();}
void s952::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s952::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false ) ) );
s346.insert( make_pair( L"set", new s335( L"set", &s952::s385, s1143,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"set-el", new s335( L"set-el", &s952::s1255, s1143,
{ s1113( { s1501::s1538, s7::s1382, s7::s1388 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"get", new s335( L"get", &s952::s325, 0,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"fst", new s335( L"fst", &s952::s995, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"snd", new s335( L"snd", &s952::s1068, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"append", new s335( L"append", &s952::s1304, s1143,
{ s1113( { s7::s1382, s7::s1388 } ) }, 1, (size_t)-1 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s952::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"resize", new s335( L"resize", &s952::s327, s1143,
{ s1113( { s1501::s1538 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", &s952::s328, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"eq", new s335( L"eq", &s952::s396, s1142,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"for-each", new s335( L"for-each", &s744::s1731, s1143,
{ s1113( { s7::s1387 } ) }, 1, 1 ) ) );
s346.equal_range( s7::s1346 ).first->second->s1251( true );
s346.equal_range( L"get" ).first->second->s1251( true );
s346.equal_range( L"fst" ).first->second->s1251( true );
s346.equal_range( L"snd" ).first->second->s1251( true );}
s481* s952::s353( s272* s586, const std::vector<s1054>& vt ) const{
s952* s681 = new s952( s300, s586, L"" );
s807 s617( vt );
s681->s491 = s681->s315 = s681->s323 = s300->TR().s1004( s617 );
return s681;}
s481* s952::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
s952* s681 = new s952( s300, s586, l, ast_, s491 );
return s681;}
void s952::s1151( const wstring& s77,	s272* s586, const s1681& s1745 ){
assert( !s77.empty() );
wstring s1263, s642, s1256;
if( s77[0] == L'[' ) {
s1256 = s77.substr( 1, s77.size() - 2 );}
else {
s1152( s300, s77, s1263, s642 );
if( !s642.empty() && s642[0] == L'[' )
s1256 = s642.substr( 1, s642.size() - 2 );
if( !s1263.empty() )
s1149( s1263 );}
if( !s1256.empty() ) {
load( s1256, s586, s1745 );}
else if( !s642.empty() ) {
if( s642.find_first_not_of( s4::digits ) == string::npos ) {
s347.push_back( 0 );
s347.push_back( new s357( s300, s642, ns ) );}}}
void s952::s1149( const std::wstring& s1263 ){
s807::Cont vt;
size_t pos = 0;
s300->TR().s1049( s1263, pos, vt );
s807::Cont s1272( begin( vt ), end( vt ) );
if( s1272.size() > 2 )
s323 = s300->TR().s1039( s1272 );
else
s323 = s1272[0];
s491 = s315 = s323;}
s1054 s952::s1186( const std::wstring& s1263, s807::Cont& s586 ){
s1054 s681;
s807::Cont vt;
size_t pos = 0;
s300->TR().s1049( s1263, pos, vt );
s681 = s300->TR().s1004( s807( vt ), false );
if( s681 ) {
s586.assign( vt.begin(), vt.end() );
return s681;}
s681 = s300->TR().s1039( vt );
s586.assign( vt.begin(), vt.end() );
return s681;}
void s952::load( const wstring& s77, s272* s586, const s1681& s1745 ){
TDException s961( s7::s1119, s926, s601() );
size_t pos = 0;
const s938* s1044 = NULL;
if( s601() && s601()->Nqj() )
s1044 = s601()->Nqj()->s999();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1044, s77, pos, s94, s1745 );
if( s94.size() ) {
s807::Cont s1269;
if( s491 ) {
const s807& vt = s300->TR().s1006( s491 );
s1269.assign( vt.s813().begin(), vt.s813().end() );
if( s94.size() != ( s1269.size() - 2 ) / 2 )
throw s961.s993( L"wrong number of elements passed for inititalizing tuple" );}
else
s1269.push_back( s1703 );
for( size_t n = 0; n < s94.size(); ++n ) {
s940 s225 = new s263( L"", *s94[n], NULL );
s271* p = NULL;
if( s225->s291().empty() ) {
if( s1745.s1730 && s491 ) {
s225->s1754( s300->TR().s798( s1269[( n + 1 ) * 2] ) + L"()" );
p = s271::s502( *s225, s300, s586, s586->s298() );
p->s1665( s7::s1733 );}}
else {
s225->s269( s2279, s141( L"locals" ) );
if( s491 )
s225->s1334( s1269[( n + 1 ) * 2] );
p = s271::s502( *s225, s300, s586, s586->s298() );}
s347.push_back( (s481*) p );
if( s491 ) {
(void)0;}
else {
s1269.push_back( p->s350() );
s1269.push_back( 0 );}}
s1269.insert( s1269.begin() + 1, (s1054)( s1269.size() - 1 ) / 2 );
if( !s323 ) {
s491 = s300->TR().s1039( s1269 );
s323 = s315 = s491;}}
s1252();}
s1054 s952::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == s7::s1346 )
s681 = s491;
else if( s1541 == L"fst" )
s681 = s300->TR().s1006( s491 ).s350( ( 0 + 1 ) * 2 );
else if( s1541 == L"snd" )
s681 = s300->TR().s1006( s491 ).s350( ( 1 + 1 ) * 2 );
else if( s1541 == L"get" ) {
int n = (int)*l[0].s15<s271*>()->s494();
s681 = s300->TR().s1006( s491 ).s350( ( n + 1 ) * 2 );}
return s681;}
bool s952::operator<( const s481* p ) const{
if( ( (s952*)p )->s347.size() != s347.size() )
return false;
for( size_t n = 0; n < s347.size(); ++n ) {
const s481* l = s347[n].s15<s481*>();
const s481* r = ( (const s952*)p )->s347[n].s15<s481*>();
if( !( *l < r ) )
return false;}
return true;}
#undef s692
#define s692 ((s952*)(s482*)*s274)
inline void s952::s1227( s481** s274, size_t s496 ){
s952* ps = (s952*)DR;
s952* s681;
if( s496 == 2 ) {
s681 = (s952*)( s274[1] )->s333( 0, ps->ns );}
else if( s496 == 3 && s274[2]->s1187().s350() == s1703 ) {
s681 = (s952*) ps->s1525( s274[2] );}
else {
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 )
{ return v.push_back( (s271*)s347 ); } );
s681 = new s952( ps->s300, ps->ns, v, ps->s601() );}
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s952::s385( s481** s274, size_t s496 ){
s952* s817 = ( (s952*)DR );
if( s817->s350() != s274[2]->s350() )
throw new s16( L"mismatched types in assignment expression" );
s274[2]->s354( s817 );}
inline void s952::s1255( s481** s274, size_t s496 ){
s952* s817 = ( (s952*)DR );
size_t idx = (int)*s274[2];
s271* el = s817->s347[idx];
if( ! s274[3]->s1530( el->s350()) )
throw new s16( L"mismatched types in assignment expression" );
s274[3]->s354( ( (s952*)DR )->s347[(int)*s274[2]] );}
inline void s952::s325( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s952*)DR )->s347[(int)*s274[2]];}
inline void s952::s995( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s952*)DR )->s347[0];}
inline void s952::s1068( s481** s274, size_t s496 ){
*s274 = (s481*)(s271*)( (s952*)DR )->s347[1];}
inline void s952::s1304( s481** s274, size_t s496 ){
s952* s817 = ( (s952*)DR );
const s952* pro = (s952*)s817->s300->TR().s1000( DR->s350() );
size_t n = s817->s347.size();
if( n >= pro->s347.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s347[n]->s499( s274[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s744*)DR )->s317() != s274[2]->s493() )
*/
s817->s347.push_back( (s481*)s274[2]->s333(0,0) );}
inline void s952::s326( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s952*)DR )->s347.size();}
inline void s952::s327( s481** s274, size_t s496 ){
int size = (int)*s274[2];
( (s952*)DR )->s347.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s744*)DR )->s347[i] = ( (s744*)DR )->s300->s216(
( (s744*)DR )->s315, ( (s744*)DR )->s497 ).s15<s482*>();*/
}
inline void s952::s328( s481** s274, size_t s496 ){
( (s952*)DR )->s347.clear();}
inline void s952::s396( s481** s274, size_t s496 ){
size_t size = ( (s952*)DR )->s347.size();
s952* right = (s952*)s274[2];
if( right->s347.size() != size ) {
*( (s344*)*s274 )->s355() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s347[n] != ( (s952*)DR )->s347[n] ) {
*( (s344*)*s274 )->s355() = 0;
return;}}
*( (s344*)*s274 )->s355() = 1;}
inline void s952::s329( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s952*)DR )->s347.size();}
s271* s952::s333( s589* s2042, s272* impl ) const{
return new s952( *this );}
void s952::s354( s271* p ) const{
s952* pv = (s952*)p;
pv->s347.assign( s347.begin(), s347.end() );
pv->s1665( wh );}
bool s952::s2162( s1890& s ){
if( s.size() < 4 )
return false;
if( s[0] != L'[' || s[1] != L'[' )
return false;
wregex rgBr(
LR"regex(,\s*\[.*?$)regex"
);
wsmatch sm;
if( !std::regex_search( s, sm, rgBr ) )
return ( s[1] == L'[' );
int s2164 = (int)s4::count( s, L"[", sm.position( 0 ), string::npos, true );
int s2165 = (int)s4::count( s, L"]", sm.position( 0 ), string::npos, true );
return ( s2165 - s2164 > 1 );}
wstring s952::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[[";
if( s616() == s7::s862 )
s681 += L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n )
s681 += s347[n]->to_wstring() + ( n == s347.size() - 1 ? L"" : L", " );}
s681 += L"]]";
return s681;}
void s952::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
ss << L"[[";
if( s616() == s7::s862 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n ) {
s347[n].s15<s481*>()->s1920( s1919 );
if( n < s347.size() - 1 )
ss << L", ";}}
ss << L"]]";}
s1282::s1282( s262* s300, s272* s586, const wstring& s77, const s263* ast_,
const s1681& s1745 )
: s1390( s300, s586, ast_ ){
s1151( s77, s586, s1745 );
if( !s491 )
s491 = Types.ByteArray;}
s1282::s1282( const s1282& right, const s263* ast_ )
: s1390( right.s300, NULL, ast_ ){
s347 = right.s347;
s1191 = right.s1191;
s323 = right.s323;
s315 = right.s315;
s491 = right.s491;
wh = right.wh;}
s1282::s1282( s262* s300, const std::vector<s271*>& l, const s263* ast_ )
: s1390( s300, NULL, ast_ ){
s1151( L"", NULL, s1722 );
if( l.size() ) {
s315 = l[0]->s350();
for( size_t n = 0; n < l.size(); ++n )
s347.push_back( *( (s1285*)l[n] )->s355() );}
if( !s491 )
s491 = Types.ByteArray;}
s1282::~s1282(){
s347.clear();}
void s1282::s1151( const wstring& s77, s481* s586, const s1681& s1745 ){
s1191 = s1142;
s323 = s1298;
s807::Cont v = { s1703, 2, s1142, 0, s323, 0 };
s315 = s300->TR().s1039( v );
s491 = s1140;
if( s77.empty() )
return;
wstring s1263, s642, s1256;
if( s77[0] == L'[' ) {
s1256 = s77;}
else {
s1152( s300, s77, s1263, s642 );
if( !s642.empty() && s642[0] == L'[' )
s1256 = s642;
if( s1263 != s351() )
throw new s16( L"wrong syntax of ByteArray declaration" );}
if( !s1256.empty() ) {
load( s1256, s586, s1745 );}
else if( !s642.empty() ) {
if( s642[0] == L']' && s642.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
wstring snum = s642.substr( s642.rfind( L" " ) );
size_t s163 = std::stoi( snum );
s347.resize( s163 );}}}
void s1282::load( s1890& s77, s481* s586, const s1681& s1745 ){
TDException s961( s7::s1288, s926, s601() );
size_t pos = 0;
const s938* s1044 = NULL;
if( s601() && s601()->Nqj() )
s1044 = s601()->Nqj()->s999();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1044, s77, pos, s94, s1745 );
if( s94.size() ) {
for( size_t n = 0; n < s94.size(); ++n ) {
size_t s163 = s94[n]->s56();
s347.push_back( (tdbyte_t)s163 );}}}
s481* s1282::s352( const s263& s695, s272* s586, s1890& s332 ) const{
TDException s961( s7::s1286, s926, &s695,
L"wrong ByteArray constructor syntax" );
wstring s = s300->TR().s1265( s695.s291(), s332 );
wstring sv;
wstring s345 = s351();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s961.s993( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1282* s681 = new s1282( s300, s586, sv, &s695 );
return s681;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1311( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1282::s498( const s272* s873, bool ){
s1665( s7::s861 );
if( s873 )
s497 = s873->s828();}
void s1282::s348(){
s1390<s1364, tdbyte_t, s1282, s1285>::s348();
s346 = s1390<s1364, tdbyte_t, s1282, s1285>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1282::s1227, s1140,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 1 ) ) );
s346.emplace( make_pair( L"set", new s335( L"set", &s1282::s385, s1143,
{ s1113( { s1501::s1496 } ) }, 1, 1 ) ) );
s346.emplace( make_pair( L"set-el", new s335( L"set-el", &s1282::s1254, s1143,
{ s1113( { s1142, s1142 } ) }, 2, 2 ) ) );
s346.emplace( make_pair( L"get", new s335( L"get", &s1282::s325, s1298,
{ s1113( { s1142 } ) }, 1, 1 ) ) );
s346.emplace( make_pair( L"append", new s335( L"append", &s1282::s1304, s1143,
{ s1113( { s7::s1386 } ) }, 1, 1 ) ) );
s346.emplace( make_pair( L"resize", new s335( L"resize", &s1282::s327, s1143,
{ s1113( { s1142 } ) }, 1, 1 ) ) );
s346.emplace( make_pair( L"eq", new s335( L"eq", &s1282::s396, s1139,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s300->TR().s1153( s491, s7::s1401, s1501::s1497 );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s1282::s353( s272* s586, const vector<s271*>& l, const s263* ast_ ) const{
return new s1282( s300, s586, L"", ast_ );}
s481* s1282::s353( s272* s586, const std::vector<s1054>& vt ) const{
return new s1282( s300, s586, L"" );}
inline bool
s1282::s499( const s481* s500 ) const{
return ( ( (s1282*)s500 )->s350() == s350() );}
s271* s1282::s333( s589* s2042, s272* impl ) const{
return new s1282( *this );}
void s1282::s354( s271* p ) const{
p = new s1282( *this );}
Iterator* s1282::s1155( const s481* idx ){
s1364::iterator it;
int i = (int)*idx;
if( i >= (int)s347.size() )
it = s347.end();
else {
if( i < 0 ) {
i = (int)s347.size() + i;
if( i < 0 )
i = 0;}
it = s347.begin() + i;}
return new s1283( s300, this, it, it == s347.end() ? it : it + 1 );}
Iterator* s1282::s1174( const s481* _val ){
for( auto it = begin( s347 ); it != end( s347 ); ++it )
if( *it == *( (s1285*)_val )->s355() )
return new s1283( s300, this, it, it + 1 );
return new s1283( s300, this, end( s347 ), end( s347 ) );}
s481* s1282::s1181( Iterator* it ){
size_t n = std::distance( begin( s347 ), ( (s1283*)it )->s1136() );
return new s344( s300, (int)n );}
Iterator* s1282::s1176() {
if( s347.size() )
return new s1283( s300, this, s347.begin(), s347.begin() + 1 ); 
return new s1283( s300, this, s347.end(), s347.end() ); }
Iterator* s1282::s1180() {
return new s1283( s300, this, s347.end(), s347.end() ); }
#undef s692
#define s692 ((s1282*)(s482*)*s274)
inline void s1282::s1227( s481** s274, size_t s496 ){
s1282* ps = (s1282*)DR;
s1282* s681 = NULL;
if( s496 == 2 ) {
s681 = (s1282*)( s274[1] )->s333(0,0);}
else if( s274[2]->s1187().s350() == s1705 ) {
s314* pv = (s314*)s274[2];
s681 = new s1282( ps->s300, ps->ns, L"", ps->s601() );
for( size_t n = 0; n < pv->s318().size(); ++n ) {
s681->s347.push_back( (int)*pv->s318()[n] );}}
else if( s274[2]->s350() == s1404 ) {
auto pr = (s383*)s274[2];
auto rp = pr->s1185();
typename s1375::iterator s1508, s1509;
s1508 = rp.first.s15<s1130*>()->s1136();
s1509 = rp.second.s15<s1130*>()->s1136();
s681 = new s1282( ps->s300, ps->ns, L"", ps->s601() );
s681->s347.assign( s1508, s1509 );}
else
assert( 0 );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s1282::s385( s481** s274, size_t s496 ){
s1282* v = ( (s1282*)DR );
s324* seq = (s324*)s274[2];
s383 range( 0, -1 );
Iterator* s1013 = seq->s312( &range );
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
v->s347.push_back( *p.s15<s1285*>()->s355() );}}
inline void s1282::s1254( s481** s274, size_t s496 ){
assert( s274[3]->s350() == s1142 );
assert( s274[2]->s350() == s1142 );
s1282* v = ( (s1282*)DR );
size_t idx = (size_t)(int)*s274[2];
v->s347[idx] = *( (s1285*)s274[3] )->s355();}
inline void s1282::s325( s481** s274, size_t s496 ){
s1285* s681 = new s1285( ( (s1282*)DR )->s300,
( (s1282*)DR )->s347[(int)*s274[2]] );
*s274 = (s481*)(s271*)s681;}
inline void s1282::s1304( s481** s274, size_t s496 ){
assert( s274[2]->s350() == s1298 );
( (s1282*)DR )->s347.push_back( *( (s1285*)s274[2] )->s355() );}
inline void s1282::s327( s481** s274, size_t s496 ){
int size = (int)*s274[2];
( (s1282*)DR )->s347.resize( size );}
inline void s1282::s396( s481** s274, size_t s496 ){
size_t size = ( (s1282*)DR )->s347.size();
s1282* right = (s1282*)s274[2];
if( right->s347.size() != size ) {
*( (s358*)*s274 )->s355() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s347[n] != ( (s1282*)DR )->s347[n] ) {
*( (s358*)*s274 )->s355() = false;
return;}}
*( (s358*)*s274 )->s355() = true;}
wstring s1282::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[";
if( s616() == s7::s862 )
s681 += L"_not_set_";
else {
for( size_t n = 0; n < s347.size(); ++n )
s681 += std::to_wstring( s347[n] ) + ( n == s347.size() - 1 ? L"" : L", " );}
s681 += L"]";
return s681;}
void s1282::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1282::s320() const{
size_t s681 = 0;
for( size_t n = 0; n < s347.size(); ++n )
s681 = ( s681 * s347[n] ) << 1;
return s681;}
bool s1282::operator==( const s481* p ) const{
if( ( (s1282*)p )->s347.size() != s347.size() )
return false;
for( size_t n = 0; n < s347.size(); ++n )
if( !( s347[n] == ( (s1282*)p )->s347[n] ) )
return false;
return true;}
bool s1282::operator<( const s481* p ) const{
return false;}
Iterator* s1282::s312( s383* rv ){
s1135 pr = rv->s1185( this );
return new s1283( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
s322::s322( s262* s300, s1054 s1192, s1054 s1266, s1054 s1172,
s1054 s703, s272* s586, const s263* ast_ )
: s1358( s300, s586, ast_ ){
assert( s1192 && s1266 );
this->s1191 = s1192;
s323 = s1266;
if( s1172 )
s315 = s1172;
else {
s807 s1173( s807::Cont( { s1703, 2, s1191, 0, s323, 0 } ) );
s315 = s300->TR().s1004( s1173 );}
if( s703 )
s491 = s703;
else {
s491 = s300->TR().s1039( s807::Cont( { Types.Index, 2, s1192, 0, s1266, 0 } ) );}}
s322::s322( const s322& right, const s263* ast_ )
: s1358( right.s300, right.ns, ast_ ){
s347 = right.s347;
s491 = right.s491;
s1191 = right.s1191;
s323 = right.s323;
s315 = right.s315;
wh = right.wh;}
s322::s322( s262* s300, const std::vector<s271*>& l,
s272* s586, const s263* ast_, s1054 s703, s1054 s1172,
s1054 s1626, s1054 s1266 )
: s1358( s300, s586, ast_ ){
s1191 = s1626;
s323 = s1266;
s315 = s1172;
s491 = s703;
if( l.size() && ( l.front()->s350() == s350() ||
l.front()->s350() == Types.Index ) ) {
s347 = ( (s322*)l.front() )->s347;}}
void s322::s1151( s1890& s77, wstring& s1263, wstring& s642,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s938 s1045( L"", true, s1722 );
s1045.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1152( s300, s77, s1263, s642 );}
s481* 
s322::s352( const s263& s695, s272* s586, s1890& s332 ) const{
s1054 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s2211( (s324*)this, s1701, pt, et, vt, kt, sv, s695, s586, s332 ) )
return NULL;
s322* s681 = new s322( s300, vector<s271*>({ }), s586, &s695,
pt, et, kt, vt );
wstring ownerName = s695.s268( s2085 ).s169();
bool s1316 = false;
if( ( s695.s268( s2086 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1346 || ownerName.find( s7::s1346 + L"<" ) == 0 ) )
s1316 = true;
std::function<void(pair<s484, s484>)> s2221 = [s681]( std::pair<s484, s484> pr )
{s681->s347.insert( make_pair( pr.first, pr.second ) ); };
load( s681, sv, s586, L",", s681->s1191, s681->s323, s2221 );
if( !s1316 && s347.size() ) {
if( !s315 && s347.begin()->second->s350() ) {
s681->s315 = s300->TR().s1039( { s1703, 2, s347.begin()->first->s350(), 0,
s347.begin()->second->s350(), 0 } );
s807::Cont v1 = { Types.Index, 2, s347.begin()->first->s350(), 0,
s347.begin()->second->s350(), 0 };
s681->s491 = s300->TR().s1039( v1 );}
else if( s323 != s347.begin()->second->s350() )
throw new s16( L"index' element type doesn't match the index type" );}
return s681;}
bool s322::s2211( s324* s1161, s1054 s2218, s1054& pt, s1054& et, s1054& vt,
s1054& kt, std::wstring& sv, const s263& s695, s272* s586, s1890& s332 ){
wstring s345 = s1161->s351();
wstring s = s1161->Pass()->TR().s1265( s695.s291(), s332 );
wstring si;
wstring s1263, s642;
if( s695.s268( s2086 ).s169() == L"CallSite" ) {
wstring s1313 = s695.s268( s2085 ).s169();
if( s1313.find( s7::s1346 + L"<" + s345 + L"<" ) == 0 ) {
wstring stype = s1313.substr( s7::s1346.size()+1, s1313.size() - ( s7::s1346.size() + 2 ) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
sv = s; // s4::s52( s, L"{}" );
else if( s.find( s345 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );
s1152( s1161->Pass(), s, s1263, s642 );
if( !s642.empty() && ( s642[0] == L'{' || s642[0] == L'}' ) )
sv = s642;
if( !s1263.empty() ) {
s807::Cont s586;
pt = s1186( s1161, s1263, s1701, s586, et, kt, vt );}}
else
return false;
return true;}
s1054 s322::s1186( s271* s1161, s1890& s1263, s1054 s2218, s807::Cont& s586,
s1054& et, s1054& kt, s1054& vt ){
s1054 s681;
s807::Cont s1269;
size_t pos = 0;
s262* s2212 = s1161->Pass();
s2212->TR().s1049( s2212->TR().s1342( s1263 ), pos, s1269 );
s681 = s2212->TR().s1004( s807( s1269 ), false );
if( s681 ) {
s807 s1091( s1269 );
kt = s1091.s350( 2 );
vt = s1091.s350( 4 );
s586 = { Types.Index, 2, kt, 0, vt, 0 };
et = s2212->TR().s1039(
s807::Cont( { s1703, 2, kt, 0, vt, 0 } ) );
return s681;}
s807::Cont s1457, s1504;
size_t idx = 2;
s489::s2104( s1269, idx, s1457 );
if( s1457.size() > 2 )
kt = s2212->TR().s1039( s1457 );
else
kt = s1457[0];
s489::s2104( s1269, idx, s1504 );
if( s1504.size() > 2 )
vt = s2212->TR().s1039( s1504 );
else
vt = s1504[0];
et = s2212->TR().s1039( 
s807::Cont( { s1703, 2, kt, 0, vt, 0 } ) );
s586 = { Types.Index, 2, kt, 0, vt, 0 };
s681 = s2212->TR().s1039( s586 );
return s681;}
void s322::load( s271* s1161, s1890& s77, s272* s586, s1890& s72, s1054& kt, s1054& vt, 
const std::function<void(std::pair<s484,s484>)> s2221 ){
TDException s961( s7::s1585, s926, s1161->s601() );
vector<pair<wstring, s1::s9<s6::s141>>> s94;
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s938 s1045( L"", true, s1722 );
s1045.s170( s77, pos, ob );
ob->s160( s94 );}
if( s94.empty() )
return;
wstring ownerName = s1161->s601()->s268( s2085 ).s169();
bool s1316 = false;
if( ( s1161->s601()->s268( s2086 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1346 || ownerName.find( s7::s1346 + L"<" ) == 0 ) )
s1316 = true;
for( size_t n = 0; n < s94.size(); ++n ) {
s940 s968 = new s263( s94[n].first, s1161->s601()->Nqj(), (s263*)s1161->s601() );
s483 s1050 = s271::s502( *s968, s1161->Pass(), s586, s586->s298() );
basic_stringstream<wchar_t> s1077;
s94[n].second->s155( &s1077 );
s940 s225 = new s263( s1077.str(), s1161->s601()->Nqj(), (s263*)s1161->s601() );
s483 s1058 = s271::s502( *s225, s1161->Pass(), s586, s586->s298() );
s2221( make_pair( s1050.s15<s481*>(), s1058.s15<s481*>() ) );
if( s1050->s492() != s473 ) {
if( kt == 0 ) {
kt = s1050->s350();}
s1050->s2181( s2186 );}
if( s1058->s492() != s473 ) {
if( vt == 0 ) {
vt = s1058->s350();}
s1058->s2181( s2186 );}}}
void s322::s2209( s271* s1161, s1890& s77, s272* s586, s1054& kt, s1054& s2232,
const std::function<void( std::pair<s484, s484> )> s2221 ){
TDException s961( s7::s917, s926, s1161->s601(), L"wrong Index definition" );
s1161->s1252();}
void s322::s498( const s272* s873, bool ){
if( s873->s492() != s474 ||
( (s272*)s873 )->s299() != s7::s1346 || s300->s1320() ) {
auto it = begin( s347 );
while( it != end( s347 ) ) {
s271* pk = it->first.s15<s271*>();
s271* pv = it->second.s15<s271*>();
pk->s498( s873, false );
if( pk->s492() == s473 ) {
pk = ( (s369*)pk )->s375()->s333( NULL, NULL );}
pv->s498( s873, false );
if( pv->s492() == s473 ) {
pv = ( (s369*)pv )->s375()->s333( NULL, NULL );}
s483 s2289 = s271::s1011( s300, pk, (s272*)s873, (s589*)s873, s873->s298(), false );
s483 s2290 = s271::s1011( s300, pv, (s272*)s873, (s589*)s873, s873->s298(), false );
if( !s323 )
s323 = s347[0]->s350();
else if( s323 != s2290->s350() )
throw new s16( L"elements have different types" );
auto it1 = it;
it++;
s347.erase( it1 );
s347.insert( make_pair( s2289->s495( 0, 0 ), s2290->s495( 0, 0 ) ) );}
s1252();}}
void s322::s348(){
s1358<s1376, s484, s484, s322>::s348();
s346 = s1358<s1376, s484, s484, s322>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s322::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s346.insert( make_pair( L"insert", new s335( L"insert", &s322::s330, s1143,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"get", new s335( L"get", &s322::s325, 0,
{ s1113( { s7::s1385 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"get-val", new s335( L"get-val", &s322::s1452, 0,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"values", new s335( L"values", &s322::s2199, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"set", new s335( L"set", &s322::s385, s1143,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"set-el", new s335( L"set-el", &s322::s1580, s1139,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"erase", new s335( L"erase", &s322::s331, s1143,
{ s1113( { s7::s1385 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s322::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.equal_range( L"get" ).first->second->s1251( true );
s346.equal_range( L"get-val" ).first->second->s1251( true );
s346.equal_range( L"values" ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s322::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
assert( 0 );
return NULL;}
s481* s322::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s807::Cont s1015, s1094;
s489::s2104( vt, idx, s1015 );
s807 s1014( s1015[0] );
s1054 s1192 = s300->TR().s1004( s1014 );
s489::s2104( vt, idx, s1094 );
s807 s1091( s1094[0] );
s1054 s1266 = s300->TR().s1004( s1091 );
s1054 s1172 = s300->TR().s1039( s807::Cont { s1703, 2,
s1192, 0, s1266, 0 } );
s322* s681 = new s322( s300, s1192, s1266, s1172, 0, s586, NULL );
return s681;}
else {
assert( 0 );
s807::Cont s985;
s489::s2104( vt, idx, s985 );
s807 s984( s985[0] );
s1054 s1172 = s300->TR().s1004( s984 );
const s807& s1090 = s300->TR().s1006( s1172 );
s807::Cont s1015, s1094;
idx = 2;
s489::s2104( s1090.s813(), idx, s1015 );
s807 s1014( s1015[0] );
s1054 s1192 = s300->TR().s1004( s1014 );
s489::s2104( s1090.s813(), idx, s1094 );
s807 s1091( s1094[0] );
s1054 s1266 = s300->TR().s1004( s1091 );
s322* s681 = new s322( s300, s1192, s1266, s1172, 0, s586, NULL );
return s681;}}
s1054 s322::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" ) {
s681 = s323;}
else if( s1541 == L"get-val" ) {
s681 = s323;}
else if( s1541 == L"values" ) {
s807::Cont s1269;
wstring ts = this->s300->TR().s1342( 
Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, s323 )->s351() + L">" );
s681 = ((s314*)Types( s300, Types.Vector ))->s1186( (s271*)this, ts, s1705, s1269 );}
else
s681 = s1358::s1179( s1541, l );
return s681;}
inline bool
s322::s499( const s481* s500 ) const{
return 0; /* ( ( (s314*)s500 )->s315 == s315 );*/
}
s271* s322::s333( s589* s2042, s272* impl ) const{
return new s322( *this, s601() );}
void s322::s354( s271* p ) const{
p = new s322( *this );}
size_t s322::s320() const{
return (size_t)this;}
bool s322::operator==( const s481* p ) const{
return ( this == p );}
bool s322::operator<( const s481* p ) const{
return false;}
Iterator* s322::s1176() {
auto it = begin( s347 );
return new s932( s300, this, s347.begin(), ++it ); }
Iterator* s322::s1180() {
return new s932( s300, this, s347.end(), s347.end() ); }
#undef s692
#define s692 ((s322*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
inline void s322::s1227( s481** s274, size_t s496 ){
s322* ps = (s322*)DR;
s322* s681 = NULL;
if( s496 == 2 ) {
s681 = (s322*)( s274[1] )->s333(0, ps->ns);}
else if( s274[2]->s1187().s350() == s1701 ) {
s681 = (s322*)ps->s1525( s274[2] );}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 ) { return v.push_back( (s271*)s347 ); } );}
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s322::s330( s481** s274, size_t s496 ){
s484 s152 = (s481*)PARN( 2 )->s495(0,0);
s322* dr = (s322*)DR;
s1375::iterator it = dr->s347.find( s152 );
if( it == dr->s347.end() ) {
s481* s1058 = (s481*)PARN( 3 );
if( dr->s1191 != s152->s350() || dr->s323 != s1058->s350() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s484 s347 = s1058->s333(0,0)->s495(0,0);
dr->s347.insert( make_pair( s152, s347 ) );}}
inline void s322::s325( s481** s274, size_t s496 ){
s322* p = (s322*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() )
throw new s16( L"key doesn't exist: '" + s274[2]->to_wstring() + L"'" );
else {
*s274 = it->second.s15<s481*>();}}
inline void s322::s1452( s481** s274, size_t s496 ){
s322* p = (s322*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() ) {
*s274 = (s481*)PARN( 3 )->s333(0,0);}
else {
*s274 = (s481*)it->second->s333(0,0);
s274[0]->s1252();//s498( p->ns, true );
}}
inline void s322::s2199( s481** s274, size_t s496 ){
s322* p = (s322*)DR;
s314* s681 = new s314( p->s300, p->ValType(), p->ns, p->s601() );
s1375::iterator it = p->s347.begin();
vector<s483>& v = s681->s318();
v.resize( p->s347.size() );
size_t idx = 0;
for( ; it != p->s347.end(); ++it )
v[idx++] = it->second.s15<s271*>();
s681->s1252();
*s274 = s681;}
inline void s322::s385( s481** s274, size_t s496 ){
s322* l = (s322*)DR;
s322* right = (s322*)PARN( 2 );
*l = *right;}
inline void s322::s1580( s481** s274, size_t s496 ){
s484 s152 = (s481*)PARN( 2 )->s495(0,0);
s481* s347 = (s481*)PARN( 3 );
s322* dr = (s322*)DR;
if( dr->s1191 != s152->s350() || dr->s323 != s347->s350() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1375::iterator it = dr->s347.find( (s481*)PARN( 2 ) );
if( it == dr->s347.end() ) {
s484 s1231 = (s481*)s347->s333(0,0)->s495(0,0);
s484 s1582 = (s481*)s152->s333(0,0);
dr->s347.insert( make_pair( s1582, s1231 ) );
*s274 = s367;}
else {
it->second = (s481*)s347->s333(0,0)->s495(0,0);
*s274 = s368;}}
inline void s322::s331( s481** s274, size_t s496 ){
s322* p = (s322*)DR;
p->s347.erase( (s481*)PARN( 2 ) );}
inline void s322::s326( s481** s274, size_t s496 ){}
inline void s322::s329( s481** s274, size_t s496 ){}
Iterator* s322::s312( s383* rv ){
if( !rv )
return new s932( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s932( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
wstring s322::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"{ ";
for( auto it = begin( s347 ); it != end( s347 ); ++it )
s681 += ( it == begin( s347 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s681 += L" }";
return s681;}
void s322::s1920( Stream* s1919 ) const{
s2213( (s271*)this, s1919, ((s322*)this)->s312( NULL ) );}
void s322::s2213( s271* subj, Stream* s1919, Iterator* it ){
s1489& ss = s1919->s1949();
bool s2057 = s1919->s2052();
s1919->s2051();
ss << L"{";
if( subj->s616() == s7::s862 )
ss << L"_not_set_";
else {
bool s2230 = true;
for( ; ; ) {
s483 s2168 = it->s313();
if( s2168.s13() )
break;
if( !s2230 )
ss << L", ";
else
s2230 = false;
s2168.s15<s952*>()->s318()[0].s15<s481*>()->s1920( s1919 );
ss << L" : ";
s2168.s15<s952*>()->s318()[1].s15<s481*>()->s1920( s1919 );}}
ss << L"}";
if( !s2057 )
s1919->s2050();}
void s322::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Index : " << endl;
for( auto it = begin( s347 ); it != end( s347 ); ++it ) {
buf << s4::fill_n_ch( L' ', s197 ) << it->first->to_wstring() + L" : ";
it->second->s304( pd, s197 + s417 );}}
s1371::s1371( s262* s300, s1054 s1192, s1054 s1266, s1054 s1172,
s1054 s703, s272* s586, const s263* ast_ )
: s1358( s300, s586, ast_ ){
assert( s1192 && s1266 );
this->s1191 = s1192;
s323 = s1266;
if( s1172 )
s315 = s1172;
else {
s807 s1173( s807::Cont( { s1703, 2, s1191, 0, s323, 0 } ) );
s315 = s300->TR().s1004( s1173 );}
if( s703 )
s491 = s703;
else {
s491 = s300->TR().s1039( s807::Cont( { Types.HashIndex, 2, s1192, 0, s1266, 0 } ) );}}
s1371::s1371( const s1371& right, const s263* ast_ )
: s1358( right.s300, right.ns, ast_ ){
s347 = right.s347;
s491 = right.s491;
s1191 = right.s1191;
s323 = right.s323;
s315 = right.s315;
wh = right.wh;}
s1371::s1371( s262* s300, const std::vector<s271*>& l,
s272* s586, const s263* ast_, s1054 s703, s1054 s1172,
s1054 s1626, s1054 s1266 )
: s1358( s300, s586, ast_ ){
s1191 = s1626;
s323 = s1266;
s315 = s1172;
s491 = s703;
if( l.size() && ( l.front()->s350() == s350() ||
l.front()->s350() == Types.Index ) ) {
s347 = ( (s1371*)l.front() )->s347;}}
void s1371::s1151( const wstring& s77, wstring& s1263, wstring& s642,
vector<pair<wstring, s142>> s94, const s263* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s143> ob = new s6::s143( NULL );
size_t pos = 0;
s938 s1045( L"", true, s1722 );
s1045.s170( s77, pos, ob );
ob->s160( s94 );}
else
s1152( s300, s77, s1263, s642 );}
s481* 
s1371::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
s1054 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s322::s2211( (s324*)this, s1701, pt, et, vt, kt, sv, s695, s586, s332 ) )
return NULL;
s1371* s681 = new s1371( s300, vector<s271*>( { } ), s586, &s695,
pt, et, kt, vt );
wstring ownerName = s695.s268( s2085 ).s169();
bool s1316 = false;
if( ( s695.s268( s2086 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1346 || ownerName.find( s7::s1346 + L"<" ) == 0 ) )
s1316 = true;
auto s2221 = [s681]( std::pair<s484, s484> pr ) {s681->s347.insert( make_pair( pr.first, pr.second ) ); };
s322::load( s681, sv, s586, L",", s681->s1191, s681->s323, s2221 );
if( !s1316 && s347.size() ) {
if( !s315 && s347.begin()->second->s350() ) {
s681->s315 = s300->TR().s1039( { s1703, 2, s347.begin()->first->s350(), 0,
s347.begin()->second->s350(), 0 } );
s807::Cont v1 = { Types.Index, 2, s347.begin()->first->s350(), 0,
s347.begin()->second->s350(), 0 };
s681->s491 = s300->TR().s1039( v1 );}
else if( s323 != s347.begin()->second->s350() )
throw new s16( L"index' element type doesn't match the index type" );}
return s681;}
void s1371::s498( const s272* s873, bool ){
s322::s2209( this, s497, (s272*)s873, s1191, s323,
[this]( std::pair<s484, s484> pr ) {this->s347.insert( make_pair( pr.first, pr.second ) ); } );}
void s1371::s348(){
s1358<s1370, s484, s484, s1371>::s348();
s346 = s1358<s1370, s484, s484, s1371>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1371::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s346.insert( make_pair( L"insert", new s335( L"insert", &s1371::s330, s1143,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"find", new s335( L"find", &s1371::s774, 0,
{ s1113( { s7::s1385 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"get", new s335( L"get", &s1371::s325, 0,
{ s1113( { s7::s1385 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"get-val", new s335( L"get-val", &s1371::s1452, 0,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"set", new s335( L"set", &s1371::s385, s1139,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"set-el", new s335( L"set-el", &s1371::s1580, s1139,
{ s1113( { s7::s1385, s7::s1386 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"erase", new s335( L"erase", &s1371::s331, s1143,
{ s1113( { s7::s1385 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s1371::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.equal_range( L"find" ).first->second->s1251( true );
s346.equal_range( L"get" ).first->second->s1251( true );
s346.equal_range( L"get-val" ).first->second->s1251( true );}
s481* s1371::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
assert( 0 );
return NULL;}
s481* s1371::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s807::Cont s1015, s1094;
s489::s2104( vt, idx, s1015 );
s807 s1014( s1015[0] );
s1054 s1192 = s300->TR().s1004( s1014 );
s489::s2104( vt, idx, s1094 );
s807 s1091( s1094[0] );
s1054 s1266 = s300->TR().s1004( s1091 );
s1054 s1172 = s300->TR().s1039( s807::Cont { s1703, 2,
s1192, 0, s1266, 0 } );
s1371* s681 = new s1371( s300, s1192, s1266, s1172, 0, s586, NULL );
return s681;}
else {
assert( 0 );
s807::Cont s985;
s489::s2104( vt, idx, s985 );
s807 s984( s985[0] );
s1054 s1172 = s300->TR().s1004( s984 );
const s807& s1090 = s300->TR().s1006( s1172 );
s807::Cont s1015, s1094;
idx = 2;
s489::s2104( s1090.s813(), idx, s1015 );
s807 s1014( s1015[0] );
s1054 s1192 = s300->TR().s1004( s1014 );
s489::s2104( s1090.s813(), idx, s1094 );
s807 s1091( s1094[0] );
s1054 s1266 = s300->TR().s1004( s1091 );
s1371* s681 = new s1371( s300, s1192, s1266, s1172, 0, s586, NULL );
return s681;}}
s1054 s1371::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" ) {
s681 = s323;}
else if( s1541 == L"get-val" ) {
s681 = s323;}
else if( s1541 == L"values" ) {
s807::Cont s1269;
wstring ts = this->s300->TR().s1342(
Types( s300, Types.Vector )->s351() + L"<" +
Types( s300, s323 )->s351() + L">" );
s681 = ( (s314*)Types( s300, Types.Vector ) )->s1186( (s271*)this, ts, s1705, s1269 );}
else
s681 = s1358::s1179( s1541, l );
return s681;}
inline bool
s1371::s499( const s481* s500 ) const{
return ( s500->s350() == s350() );}
s271* s1371::s333( s589* s2042, s272* impl ) const{
return new s1371( *this );}
void s1371::s354( s271* p ) const{
p = new s1371( *this );}
size_t s1371::s320() const{
return (size_t)this;}
bool s1371::operator==( const s481* p ) const{
return ( this == p );}
bool s1371::operator<( const s481* p ) const{
return false;}
Iterator* s1371::s1176() {
auto it = begin( s347 );
return new s1372( s300, this, s347.begin(), ++it ); }
Iterator* s1371::s1180() {
return new s1372( s300, this, s347.end(), s347.end() ); }
#undef s692
#define s692 ((s1371*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
inline void s1371::s1227( s481** s274, size_t s496 ){
s1371* ps = (s1371*)DR;
s1371* s681 = NULL;
if( s496 == 2 ) {
s681 = (s1371*)( s274[1] )->s333( 0, ps->ns );}
else if( s274[2]->s1187().s350() == s1700 ) {
s681 = (s1371*)ps->s1525( s274[2] );}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 ) { return v.push_back( (s271*)s347 ); } );}
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s1371::s330( s481** s274, size_t s496 ){
s484 s152 = (s481*)PARN( 2 )->s495(0,0);
s1371* dr = (s1371*)DR;
s1375::iterator it = dr->s347.find( s152 );
if( it == dr->s347.end() ) {
s481* s1058 = (s481*)PARN( 3 );
if( dr->s1191 != s152->s350() || dr->s323 != s1058->s350() )
throw new s16( L"non-compatible types cannot be inserted to HashIndex" );
s484 s347 = s1058->s333(0,0)->s495(0,0);
dr->s347.insert( make_pair( s152, s347 ) );}
else
throw new s16( L"key already exists: " + s152->to_wstring() );}
inline void s1371::s1580( s481** s274, size_t s496 ){
s484 s152 = (s481*)PARN( 2 )->s495(0,0);
s481* s347 = (s481*)PARN( 3 );
s1371* dr = (s1371*)DR;
if( dr->s1191 != s152->s350() || dr->s323 != s347->s350() )
throw new s16( L"non-compatible types cannot be inserted to an HashIndex" );
s1375::iterator it = dr->s347.find( s152 );
if( it == dr->s347.end() ) {
s484 s1231 = (s481*)s347->s333(0,0)->s495(0,0);
s484 s1582 = (s481*)s152->s333(0,0);
dr->s347.insert( make_pair( s1582, s1231 ) );
*s274 = s367;}
else {
it->second = (s481*)s347->s333(0,0)->s495(0,0);
*s274 = s368;}}
inline void s1371::s774( s481** s274, size_t s496 ){
s1371* p = (s1371*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() )
*s274 = NULL;
else {
*s274 = new s952( p->s300, p->ns, vector<s271*>(
{ it->first.s15<s482*>(), it->second.s15<s482*>() } ) );}}
inline void s1371::s325( s481** s274, size_t s496 ){
s1371* p = (s1371*)DR;
s484 s1050 = (s481*)PARN( 2 )->s495(0,0);
s1375::iterator it = p->s347.find( s1050 );
if( it == p->s347.end() )
*s274 = NULL;
else {
*s274 = it->second.s15<s481*>();}}
inline void s1371::s1452( s481** s274, size_t s496 ){
s1371* p = (s1371*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() )
*s274 = (s481*)PARN( 3 )->s333( 0, 0 );
else {
*s274 = (s481*)it->second->s333( 0, 0 );
s274[0]->s1252();}}
inline void s1371::s385( s481** s274, size_t s496 ){
s481* s152 = (s481*)PARN( 2 );
s481* s347 = (s481*)PARN( 3 );
s1371* dr = (s1371*)DR;
if( dr->s1191 != s152->s350() || dr->s323 != s347->s350() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1375::iterator it = dr->s347.find( (s481*)PARN( 2 ) );
if( it == dr->s347.end() ) {
s481* s1231 = (s481*)s347->s333(0,0);
dr->s347.insert( make_pair( (s481*)s152->s333(0,0), s1231 ) );
*s274 = s367;}
else {
it->second = (s481*)s347->s333(0,0);
*s274 = s368;}}
inline void s1371::s331( s481** s274, size_t s496 ){
s1371* p = (s1371*)DR;
p->s347.erase( (s481*)PARN( 2 ) );}
inline void s1371::s326( s481** s274, size_t s496 ){}
inline void s1371::s329( s481** s274, size_t s496 ){}
Iterator* s1371::s312( s383* rv ){
if( !rv )
return new s1372( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s1372( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
wstring s1371::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"{ ";
for( auto it = begin( s347 ); it != end( s347 ); ++it )
s681 += ( it == begin( s347 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s681 += L" }";
return s681;}
void s1371::s1920( Stream* s1919 ) const{
s322::s2213( (s271*)this, s1919, ((s1371*)this)->s312(NULL) );}
void s1371::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s347.size(); ++n )
s347[n]->s304( pd, s197 + s417 );*/
}
s2204::s2204( s262* s300, s272* s586, s1890& s77, const s263* ast_,
const s1681& s1745 )
: s1564( s300, s586, ast_ ){
if( s77.size() )
load( s77, s586, s1745 );
if( !s491 )
s491 = Types.Vector;}
s2204::s2204( const s2204& right, s272* _ns, const s263* ast_ )
: s1564( right.s300, _ns, ast_ ){
for( auto it = right.s347.begin(); it != right.s347.end(); ++it )
s347.insert( (s481*)(*it)->s333( NULL, _ns ));
s323 = right.s323;
s491 = right.s491;
s1665( right.s616() );}
s2204::s2204( s262* s300, const std::vector<s271*>& l,
s272* s586, const s263* ast_, s1054 s703, s1054 s1266 )
: s1564( s300, s586, ast_ ){
s323 = s1266;
if( s703 )
s491 = s703;
else
s491 = Types.Set;
if( l.size() ) {
if( l[0]->s350() == s350() || l[0]->s350() == s2207 ) {
s2203* ps = &( (s2204*)l[0] )->s347;
for( auto it = (*ps).begin(); it != (*ps).end(); ++it )
s347.insert( (s481*)( *it )->s333( NULL, ((s2204*)l[0])->ns ) );}
else if( l[0]->s350() == s1142 ) {
s347.insert( 0 );
s347.insert( new s357( s300, L"] " + l[0]->to_wstring() ) );}}}
s2204::s2204( s262* s300, s1054 s1267, s272* s586, const s263* ast_ )
: s1564( s300, s586, ast_ ){
s323 = s1267;
if( s1267 ) {
s807::Cont v = { s2207, 1, s323, 0 };
s491 = s300->TR().s1039( v );}}
void s2204::s1151( s1890& s77, s272* s586, const s1681& s1745 ){
assert( !s77.empty() );
wstring s1263, s642, s1256;
if( s77[0] == L'[' ) {
s1256 = s77;}
else {
s1152( s300, s77, s1263, s642 );
if( !s642.empty() && s642[0] == L'[' )
s1256 = s642;
if( !s1263.empty() ) {
s807::Cont s586;
s491 = s314::s1186( this, s1263, s2207, s586 );
s323 = s586[2];}}
if( !s1256.empty() ) {
load( s1256, s586, s1745 );}
else if( !s642.empty() ) {
if( s642[0] == L']' && s642.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
s347.insert( 0 );
s347.insert( new s357( s300, s642, ns ) );}}}
s481*
s2204::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
s1054 pt = 0, vt = 0;
wstring sv;
if( !s314::s2211( (s324*)this, s2207, pt, vt, sv, s695, s586, s332 ) )
return NULL;
s2204* s681 = new s2204( s300, vector<s271*>( { } ), s586, &s695,
pt, vt );
s681->load( sv, s586, s1722 );
return s681;}
void s2204::load( s1890& s77, s272* s586, const s6::s1681& s1745 ){
TDException s961( s7::s1120, s926, s601() );
if( s77[0] == L']' ) {
s347.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s347.insert( s300->TR().s516( s323, s586, s586->s298() ) );
return;}
size_t pos = 0;
const s938* s1044 = NULL;
if( s601() && s601()->Nqj() )
s1044 = s601()->Nqj()->s999();
vector<s1::s9<s6::s141>> s94;
s6::s178( s1044, s77, pos, s94, s1745 );
wstring ownerName = s601()->s268( s2085 ).s169();
bool s1316 = false;
if( ( s601()->s268( s2086 ).s169() == L"CallSite" ) &&
( ownerName == s7::s1346 || ownerName.find( s7::s1346 + L"<" ) == 0 ) )
s1316 = true;
if( s94.size() ) {
s1054 pt = 0;
for( size_t n = 0; n < s94.size(); ++n ) {
s940 s225 = new s263( L"", *s94[n], NULL );
s225->s1334( s323 );
s271* s1058 = s271::s502( *s225, s300, s586, s586->s298() );
s347.insert( (s481*)s1058 );
if( s1058->s492() != s473 ) {
if( n == 0 )
pt = s1058->s350();
s1058->s2181( s2186 );}}
if( !s1316 ) {
auto it = s347.begin();
if( !s323 && (*it)->s350() ) {
s323 = ( *it )->s350();
s807::Cont v1 = { s1705, 1, s323, 0 };
s491 = s300->TR().s1039( v1 );}
else if( s323 != ( *it )->s350() )
throw s961.s993( L"vector's element type doesn't match the vector type" );}}}
void s2204::s498( const s272* s873, bool ){
wstring s77 = L"";
TDException s961( s7::s2200, s926, s601() );
s1375::iterator it = s347.begin();
if( s347.size() == 2 && it->s13() ) {
++it;
s77 = (*it)->to_wstring();}
if( s873->s492() != s474 ||
( (s272*)s873 )->s299() != s7::s1346 || s300->s1320() ) {
if( s77[0] == L']' ) {
s347.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s347.insert( s300->TR().s516( s323, (s272*)s873, s873->s828() ) );}
else {
for( it = s347.begin(); it != s347.end(); ++it ) {
s271* tmp = (*it).s15<s271*>();
if( tmp->s492() == s473 ) {
tmp->s498( s873, false );
tmp = ((s369*)tmp)->s375()->s333( NULL, NULL );}
s271* s1081 = s271::s1011( s300, tmp, (s272*)s873, (s589*)s873, s873->s298(), false );
s1081 = s1081->s495( 0, 0 ).s15<s482*>();
s347.erase( it );
s347.insert( (s481*)s1081 );
if( !s323 )
s323 = s1081->s350();
else if( s323 != s1081->s350() )
throw s961.s993( L"elements have different types" );}}
if( s491 || s491 == s2207 ) {
if( !s323 )
throw s961.s993( L"vector's element type is not specified" );
s807::Cont s586 = { s2207, 1, s323, 0 };
s491 = s300->TR().s1039( s586 );}
s1252();}}
void s2204::s348(){
s1564<s2203, s483, s2204>::s348();
s346 = s1564<s2203, s483, s2204>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s2204::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s346.emplace( make_pair( L"set", new s335( L"set", &s2204::s385, s1143,
{ s1113( { s1501::s1496 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"insert", new s335( L"insert", &s2204::s330, s1143,
{ s1113( { s7::s1386 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"sort", new s335( L"sort", &s2204::s2228, 0,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.equal_range( s7::s1346 ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s2204::s353( s272* s586, const vector<s271*>& l, const s263* ast_ ) const{
if( !s323 )
throw new s16( L"set's element type is not specified" );
return new s2204( s300, l, s586, ast_, s491, s323 );}
s481* s2204::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s2204* s681 = new s2204( s300, 0, NULL );
s681->ns = s586;
s681->s323 = vt[2];
s807 s617( vt );
s681->s491 = s300->TR().s1004( s617 );
return s681;}
s1054 s2204::s1179( s1890& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" )
s681 = s323;
else if( s1541 == s7::s1346 || s1541 == L"sum" )
s681 = s491;
else
s681 = s1564::s1179( s1541, l );
return s681;}
inline bool
s2204::s499( const s481* s500 ) const{
return ( ( (s2204*)s500 )->s323 == s323 );}
s271* s2204::s333( s589* s2042, s272* impl ) const{
return new s2204( *this, impl, s601() );}
void s2204::s354( s271* p ) const{
s2204* pv = (s2204*)p;
pv->s347 = s347;
pv->s1665( wh );}
s481* s2204::s1525( const s481* p ) const{
if( s350() == p->s350() ) {
s481* s681 = (s481*)p->s333( 0, 0 );
return s681;}
else if( s300->TR().s1454( p->s350(), s1501::s1496 ) ) {
const s481* proto = s300->TR().s1000( s315 );
s2204* s681 = (s2204*)p->s501()->s333( 0, ns );
s681->s491 = s491;
s681->s323 = s323;
if( proto->s492() == s476 ) {
Iterator* s1013 = ( (s324*)p )->s312( NULL );
while( 1 ) {
s483 s2168 = s1013->s313();
if( s2168.s13() )
break;
s681->s347.insert( proto->s353( ns, vector<s271*>( { s2168 } ), s601() ) );}}
s681->s1252();
return s681;}
throw new s16( L"no conversion from '" + s351() + L"' to '" + p->s351() + L"'" );}
size_t s2204::s320() const{
return (size_t)this;}
bool s2204::operator==( const s481* p ) const{
return ( this == p );}
bool s2204::operator<( const s481* p ) const{
return false;}
Iterator* s2204::s1176(){
auto it = begin( s347 );
return new s2205( s300, this, s347.begin(), ++it );}
Iterator* s2204::s1180(){
return new s2205( s300, this, s347.end(), s347.end() );}
#undef s692
#define s692 ((s2204*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
inline void s2204::s1227( s481** s274, size_t s496 ){
s2204* ps = (s2204*)DR;
s2204* s681 = NULL;
if( s496 == 2 ) {
s681 = (s2204*)( s274[1] )->s333( 0, 0 );}
else if( s274[2]->s1187().s350() == s2207 ) {
s681 = (s2204*)( s274[2] )->s333( 0, 0 );}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 ) { return v.push_back( (s271*)s347 ); } );}
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s2204::s385( s481** s274, size_t s496 ){
s2204* v = ( (s2204*)DR );
s324* seq = (s324*)s274[2];
Iterator* s1013 = seq->s312( NULL );
v->s347.clear();
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
v->s347.insert( p.s15<s481*>() );}}
inline void s2204::s330( s481** s274, size_t s496 ){
s481* s347 = (s481*)PARN( 2 );
s2204* dr = (s2204*)DR;
if(  dr->s323 != s347->s350() )
throw new s16( L"non-compatible types cannot be inserted into a Set" );
dr->s347.insert( s347 );}
inline void s2204::s774( s481** s274, size_t s496 ){
s2204* p = (s2204*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() )
*s274 = NULL;
else {
*s274 = it->s15<s481*>();}}
inline void s2204::s2228( s481** s274, size_t s496 ){
throw new s16( L"method is not implemented" );}
Iterator* s2204::s312( s383* rv ){
if( !rv )
return new s2205( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s2205( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
wstring s2204::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[ ";
for( auto it = begin( s347 ); it != end( s347 ); ++it )
s681 += ( it == begin( s347 ) ? L"" : L", " ) + it->s15<s481*>()->to_wstring();
s681 += L" ]";
return s681;}
void s2204::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
bool s2057 = s1919->s2052();
s1919->s2051();
ss << L"[";
if( s616() == s7::s862 )
ss << L"_not_set_";
else {
for( auto it = begin( s347 ); it != end( s347 ); ++it ) {
if( it != begin( s347 ) )
ss << L", ";
it->s15<s481*>()->s1920( s1919 );}}
ss << L"]";
if( !s2057 )
s1919->s2050();}
void s2204::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Set : " << this << endl;
for( auto it = s347.begin(); it != s347.end(); ++it ) {
(*it)->s304( pd, s197 + s417 );
buf << endl;}}
s2237::s2237( s262* s300, s272* s586, s1890& s77, const s263* ast_,
const s1681& s1745 )
: s1564( s300, s586, ast_ ){
if( s77.size() )
s314::load( this, s2240, s77, s586, s1745, s491, s323, 
[this]( s484 pr ) {this->s347.insert( pr ); } );
if( !s491 )
s491 = Types.Vector;}
s2237::s2237( const s2237& right, s272* _ns, const s263* ast_ )
: s1564( right.s300, _ns, ast_ ){
for( auto it = right.s347.begin(); it != right.s347.end(); ++it )
s347.insert( (s481*)(*it)->s333( NULL, _ns ));
s323 = right.s323;
s491 = right.s491;
s1665( right.s616() );}
s2237::s2237( s262* s300, const std::vector<s271*>& l,
s272* s586, const s263* ast_, s1054 s703, s1054 s1266 )
: s1564( s300, s586, ast_ ){
s323 = s1266;
if( s703 )
s491 = s703;
else
s491 = Types.HashSet;
if( l.size() ) {
if( l[0]->s350() == s350() || l[0]->s350() == s2240 ) {
s2236* ps = &( (s2237*)l[0] )->s347;
for( auto it = (*ps).begin(); it != (*ps).end(); ++it )
s347.insert( (s481*)( *it )->s333( NULL, ((s2237*)l[0])->ns ) );}
else if( l[0]->s350() == s1142 ) {
s347.insert( 0 );
s347.insert( new s357( s300, L"] " + l[0]->to_wstring() ) );}}}
s2237::s2237( s262* s300, s1054 s1267, s272* s586, const s263* ast_ )
: s1564( s300, s586, ast_ ){
s323 = s1267;
if( s1267 ) {
s807::Cont v = { s2240, 1, s323, 0 };
s491 = s300->TR().s1039( v );}}
s481*
s2237::s352( const s263& s695, s272* s586, const std::wstring& s332 ) const{
s1054 pt = 0, vt = 0;
wstring sv;
if( !s314::s2211( (s324*)this, s2240, pt, vt, sv, s695, s586, s332 ) )
return NULL;
s2237* s681 = new s2237( s300, vector<s271*>( { } ), s586, &s695,
pt, vt );
s314::load( s681, s2240, sv, s586, s1722, s681->s491, s681->s323,
[s681]( s484 pr ) {s681->s347.insert( pr ); } );
return s681;}
void s2237::s498( const s272* s873, bool ){
wstring s77 = L"";
TDException s961( s7::s2234, s926, s601() );
s1375::iterator it = s347.begin();
if( s347.size() == 2 && it->s13() ) {
++it;
s77 = (*it)->to_wstring();}
if( s873->s492() != s474 ||
( (s272*)s873 )->s299() != s7::s1346 || s300->s1320() ) {
if( s77[0] == L']' ) {
s347.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s163 = std::stoi( snum );
for( size_t n = 0; n < s163; ++n )
s347.insert( s300->TR().s516( s323, (s272*)s873, s873->s828() ) );}
else {
for( it = s347.begin(); it != s347.end(); ++it ) {
s271* tmp = (*it).s15<s271*>();
if( tmp->s492() == s473 ) {
tmp->s498( s873, false );
tmp = ((s369*)tmp)->s375()->s333( NULL, NULL );}
s271* s1081 = s271::s1011( s300, tmp, (s272*)s873, (s589*)s873, s873->s298(), false );
s1081 = s1081->s495( 0, 0 ).s15<s482*>();
s347.erase( it );
s347.insert( (s481*)s1081 );
if( !s323 )
s323 = s1081->s350();
else if( s323 != s1081->s350() )
throw s961.s993( L"elements have different types" );}}
if( s491 || s491 == s2240 ) {
if( !s323 )
throw s961.s993( L"hashset's element type is not specified" );
s807::Cont s586 = { s2240, 1, s323, 0 };
s491 = s300->TR().s1039( s586 );}
s1252();}}
void s2237::s348(){
s1564<s2236, s483, s2237>::s348();
s346 = s1564<s2236, s483, s2237>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s2237::s1227, s1143,
{ s1113(), s1113( { s7::s1382, s7::s1388 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s346.emplace( make_pair( L"set", new s335( L"set", &s2237::s385, s1143,
{ s1113( { s1501::s1496 } ) }, 1, 1, false ) ) );
s346.emplace( make_pair( L"insert", new s335( L"insert", &s2237::s330, s1143,
{ s1113( { s7::s1386 } ) }, 1, 1, false ) ) );
s346.insert( make_pair( L"sort", new s335( L"sort", &s2237::s2228, 0,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.equal_range( s7::s1346 ).first->second->s1251( true );
s300->TR().s1153( s491, s7::s1399, s1501::s1495 );
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );}
s481* s2237::s353( s272* s586, const vector<s271*>& l, const s263* ast_ ) const{
if( !s323 )
throw new s16( L"hashset's element type is not specified" );
return new s2237( s300, l, s586, ast_, s491, s323 );}
s481* s2237::s353( s272* s586, const std::vector<s1054>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s2237* s681 = new s2237( s300, 0, NULL );
s681->ns = s586;
s681->s323 = vt[2];
s807 s617( vt );
s681->s491 = s300->TR().s1004( s617 );
return s681;}
s1054 s2237::s1179( s1890& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get" )
s681 = s323;
else if( s1541 == s7::s1346 || s1541 == L"sum" )
s681 = s491;
else
s681 = s1564::s1179( s1541, l );
return s681;}
inline bool
s2237::s499( const s481* s500 ) const{
return ( ( (s2237*)s500 )->s323 == s323 );}
s271* s2237::s333( s589* s2042, s272* impl ) const{
return new s2237( *this, impl, s601() );}
void s2237::s354( s271* p ) const{
s2237* pv = (s2237*)p;
pv->s347 = s347;
pv->s1665( wh );}
s481* s2237::s1525( const s481* p ) const{
if( s350() == p->s350() ) {
s481* s681 = (s481*)p->s333( 0, 0 );
return s681;}
else if( s300->TR().s1454( p->s350(), s1501::s1496 ) ) {
const s481* proto = s300->TR().s1000( s315 );
s2237* s681 = (s2237*)p->s501()->s333( 0, ns );
s681->s491 = s491;
s681->s323 = s323;
if( proto->s492() == s476 ) {
Iterator* s1013 = ( (s324*)p )->s312( NULL );
while( 1 ) {
s483 s2168 = s1013->s313();
if( s2168.s13() )
break;
s681->s347.insert( proto->s353( ns, vector<s271*>( { s2168 } ), s601() ) );}}
s681->s1252();
return s681;}
throw new s16( L"no conversion from '" + s351() + L"' to '" + p->s351() + L"'" );}
size_t s2237::s320() const{
return (size_t)this;}
bool s2237::operator==( const s481* p ) const{
return ( this == p );}
bool s2237::operator<( const s481* p ) const{
return false;}
Iterator* s2237::s1176(){
auto it = begin( s347 );
return new s2238( s300, this, s347.begin(), ++it );}
Iterator* s2237::s1180(){
return new s2238( s300, this, s347.end(), s347.end() );}
#undef s692
#define s692 ((s2237*)(s482*)*s274)
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
inline void s2237::s1227( s481** s274, size_t s496 ){
s2237* ps = (s2237*)DR;
s2237* s681 = NULL;
if( s496 == 2 ) {
s681 = (s2237*)( s274[1] )->s333( 0, 0 );}
else if( s274[2]->s1187().s350() == s2240 ) {
s681 = (s2237*)( s274[2] )->s333( 0, 0 );}
else {
assert( 0 );
vector<s271*> v;
for_each( s274 + 2, s274 + s496, [&v]( s481* s347 ) { return v.push_back( (s271*)s347 ); } );}
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s2237::s385( s481** s274, size_t s496 ){
s2237* v = ( (s2237*)DR );
s324* seq = (s324*)s274[2];
Iterator* s1013 = seq->s312( NULL );
v->s347.clear();
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
v->s347.insert( p.s15<s481*>() );}}
inline void s2237::s330( s481** s274, size_t s496 ){
s481* s689 = (s481*)PARN( 2 );
s2237* dr = (s2237*)DR;
if(  dr->s323 != s689->s350() )
throw new s16( L"non-compatible types cannot be inserted into a HashSet" );
dr->s347.insert( (s271*)s689 );}
inline void s2237::s774( s481** s274, size_t s496 ){
s2237* p = (s2237*)DR;
s1375::iterator it = p->s347.find( (s481*)PARN( 2 ) );
if( it == p->s347.end() )
*s274 = NULL;
else {
*s274 = it->s15<s481*>();}}
inline void s2237::s2228( s481** s274, size_t s496 ){
throw new s16( L"method is not implemented" );}
Iterator* s2237::s312( s383* rv ){
if( !rv )
return new s2238( s300, this, begin( s347 ), end( s347 ) );
s1135 pr = rv->s1185( this );
return new s2238( s300, this,
pr.first.s15<s1130*>()->s1136(), pr.second.s15<s1130*>()->s1136() );}
wstring s2237::to_wstring( uint32_t s1553 ) const{
wstring s681 = L"[ ";
for( auto it = begin( s347 ); it != end( s347 ); ++it )
s681 += ( it == begin( s347 ) ? L"" : L", " ) + it->s15<s481*>()->to_wstring();
s681 += L" ]";
return s681;}
void s2237::s1920( Stream* s1919 ) const{
s1489& ss = s1919->s1949();
bool s2057 = s1919->s2052();
s1919->s2051();
ss << L"[";
if( s616() == s7::s862 )
ss << L"_not_set_";
else {
for( auto it = begin( s347 ); it != end( s347 ); ++it ) {
if( it != begin( s347 ) )
ss << L", ";
it->s15<s481*>()->s1920( s1919 );}}
ss << L"]";
if( !s2057 )
s1919->s2050();}
void s2237::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"HashSet : " << this << endl;
for( auto it = s347.begin(); it != s347.end(); ++it ) {
(*it)->s304( pd, s197 + s417 );
buf << endl;}}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
s413::s413( s262* s300, s1890& s77, const s263* ast_ )
: s334( s300, NULL, ast_ ), s748( s300, Types.String, NULL ), s803( s300, Types.String, NULL ){
s491 = Types.s412;
s748.s11();
s803.s11();
s748.s1252();
s803.s1252();}
s413::s413( const s413& right, const s263* ast_ )
: s334( right.s300, right.ns, ast_ ), s748( right.s300, NULL, L"" ), s803( right.s300, NULL, L"" ){
s748 = right.s748;
s803 = right.s803;
s748.s1252();
s803.s1252();
s491 = right.s491;}
s481* s413::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return new s413( s300, L"", &s695 );}
void s413::s498( const s272* s873, bool ){
s1252();}
void s413::s348(){
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, Types.String )->s351() + L">";
s1054 s1506 = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s413::s1227, s1892,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"read", new s335( L"read", &s413::s407, s1143,
{ s1113( { Types.String, Types.String } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"read-rec", new s335( L"read-rec", &s413::s1663, s1143,
{ s1113( { Types.String, Types.String } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"reset", new s335( L"reset", &s413::s414, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"files", new s335( L"files", &s413::s415, s1506,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"dirs", new s335( L"dirs", &s413::s983, s1506,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s413::s326, s1142,
{ s1113() }, 0, 0 ) ) );}
s481* s413::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s413( s300, L"", ast_ );}
inline bool
s413::s499( const s481* s500 ) const{
return ( ((s413*)s500)->s350() == s350() );}
s271* s413::s333( s589* s2042, s272* impl ) const{
return s483( new s413( *this ) );}
void s413::s354( s271* p ) const{
p = new s413( *this );}
#undef s692
#define s692 ((s413*)(s482*)*s274)
inline void s413::s1227( s481** s274, size_t s496 ){
s413* s776 = (s413*)DR;
s413* s681 = new s413( s776->s300, L"", s776->s601() );
s681->s498( s776->ns, true );
*s274 = s681;}
void _findFiles( s1890& path, const wregex& rgPatt, vector<wstring>& s40,	vector<wstring>& s41 ){
vector<wstring> s782, s790;
s3::s32( path, L".*", s782, s790 );
for( size_t n = 0; n < s782.size(); ++n ) {
wstring s1662 = path + s782[n];
if( regex_match( s1662, rgPatt ) ) 
s40.push_back( s1662 );}
for( size_t n = 0; n < s790.size(); ++n ) {
if( s790[n] == L".." ||  s790[n] == L"." )
continue;
wstring s1662 = path + s790[n];
s41.push_back( s1662 );
s4::s61( s1662 );
_findFiles( s1662, rgPatt, s40, s41 );}}
inline void s413::s407( s481** s274, size_t s496 ){
wstring path = ((s357*)PARN( 2 ) )->to_wstring();
const wstring& s522 = ((s357*)PARN( 3 ))->to_wstring();
vector<wstring> s782, s790;
s413* s776 = (s413*)DR;
s776->s748.clear();
s776->s803.clear();
if( !s3::s718( path ) )
path = s776->s300->s710() + path;
s4::s61( path );
s3::s32( path, s522, s782, s790 );
std::sort( begin( s782 ), end( s782 ) );
std::sort( begin( s790 ), end( s790 ) );
for( auto f : s782 )
s776->s748.add( new s357( s776->s300, s4::s740( path + f ), s776->ns ) );
for( auto f : s790 )
s776->s803.add( new s357( s776->s300, s4::s740( path + f ), s776->ns ) );}
inline void s413::s1663( s481** s274, size_t s496 ){
wstring path = ( (s357*)PARN( 2 ) )->to_wstring();
const wstring& s522 = ( (s357*)PARN( 3 ) )->to_wstring();
wregex rg( s522 );
vector<wstring> s782, s790;
s413* s776 = (s413*)DR;
s776->s748.clear();
s776->s803.clear();
if( !s3::s718( path ) )
path = s776->s300->s710() + path;
s4::s61( path );
_findFiles( path, rg, s782, s790 );
std::sort( begin( s782 ), end( s782 ) );
std::sort( begin( s790 ), end( s790 ) );
for( auto f : s782 )
s776->s748.add( new s357( s776->s300, s4::s740( f ), s776->ns ) );
for( auto f : s790 )
s776->s803.add( new s357( s776->s300, s4::s740( f ), s776->ns ) );}
inline void s413::s414( s481** s274, size_t s496 ){
s413* s776 = (s413*)DR;
s776->s748.clear();
s776->s803.clear();}
inline void s413::s415( s481** s274, size_t s496 ){
*s274 = &( (s413*)DR )->s748;}
inline void s413::s983( s481** s274, size_t s496 ){
*s274 = &( (s413*)DR )->s803;}
inline void s413::s326( s481** s274, size_t s496 ){
s413* s776 = (s413*)DR;
*( (s344*)*s274 )->s355() = (int)(s776->s748.size() + s776->s803.size());}
wstring s413::to_wstring( uint32_t s1553 ) const{
wstring s681;
for( size_t n = 0; n < s803.size(); ++n )
s681 += ( n ? L" \"" : L"\"" ) + s803[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s748.size(); ++n )
s681 += ( n ? L" \"":L"\"") + s748[n]->to_wstring() + L"\"";
return s681;}
void s413::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Directory : " << endl;
for( size_t n = 0; n < s803.size(); ++n )
s803[n]->s304( pd, s197 + s417 );
for( size_t n = 0; n < s748.size(); ++n )
s748[n]->s304( pd, s197 + s417 );}
size_t s413::s320() const{
size_t s681 = 0;
for( size_t n = 0; n < s803.size(); ++n )
s681 = s681 * ( (s481*)&(s803[n]) )->s320() << 1;
for( size_t n = 0; n < s748.size(); ++n )
s681 = s681 * ( (s481*)&(s748[n]) )->s320() << 1;
return s681;}
bool s413::operator==( const s481* p ) const{
if( ( (s413*)p )->s748.size() != s748.size() )
return false;
if( ( (s413*)p )->s803.size() != s803.size() )
return false;
for( size_t n = 0; n < s748.size(); ++n )
if( !( ( s271* )&( *s748[n] ) == (s271*)( (s413*)p )->s748[n] ) )
return false;
for( size_t n = 0; n < s803.size(); ++n )
if( !( ( s271* )&( *s803[n] ) == (s271*)( (s413*)p )->s803[n] ) )
return false;
return true;}
bool s413::operator<( const s481* p ) const{
return false;}
vector<wstring> s1594( { L":append" } );
s1593::s1593( s262* s300, s272* s590, s589* s591,
const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1604, s695 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s274.assign( l.begin(), l.end() );
s491 = s1143;
s589::s1232( ( vector<s271*>& )l, s1594 );}
void
s1593::s498( const s272* s1658, bool proc ){
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, Types.s272 )->s351() + L">";
s491 = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s589::s498( s1658, proc );}
s484 s1593::s495( s481** s687, size_t s691 ){
s1599( s687, s691 );
s314* pv = s584.s15<s314*>();
wstring s194 = s581[1]->to_wstring();
s194 = s4::s740( s194 );
vector<s9<s143>> s660;
s941 s1044 = new s938( s194 );
s1044->read( s660, /*s7::s1097*/ L"" );
for( size_t m = 0; m < s660.size(); m++ ) {
s1590* po = new s1590( pv->Pass(), this, s660[m], NULL );
pv->add( po );}
return s584;}
s271* s1593::s333( s589* s2042, s272* impl ) const{
return new s1593( *this );}
s1054 s1501::s1494 = 0;
s1054 s1501::s1498 = 0;
s1054 s1501::s1493 = 0;
void Stream::s1450( std::wstring& s153, size_t s1461 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1469( s1890& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1451( std::wstring& s153, s1890& s72 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1470( s1890& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1449( s1312& s153, size_t s1461 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1468( const s1312& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1448( s1312& s153, const s1312& s72 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1467( const s1312& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
void Stream::s1898( wchar_t c ){
throw new s2::s16( L"stream method is not implemented: fill" );}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1555(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1464 )
*s1464 << std::resetiosflags( f );}
template<class s1409, class s1411>
Stream::s1909 s1395<s1409, s1411>::s1915() const{
return s1464->flags();}
template<class s1409, class s1411>
Stream::s1910 s1395<s1409, s1411>::s1916() const{
return s1464->precision();}
template<class s1409, class s1411>
bool s1395<s1409, s1411>::s2052() const{
return s2058;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1914(){
if( s1464 )
*s1464 << std::showpos;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1912(){
if( s1464 )
*s1464 << std::noshowpos;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s2051(){
s2058 = true;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s2050(){
s2058 = false;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1942(){
if( s1464 )
*s1464 << std::boolalpha;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1943(){
if( s1464 )
*s1464 << std::noboolalpha;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1556( int n ){
if( s1464 )
*s1464 << std::setw( n );}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1913( int n ){
if( s1464 )
*s1464 << std::setprecision( n );}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1900(){
if( s1464 )
*s1464 << std::left;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1901(){
if( s1464 )
*s1464 << std::right;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1899(){
if( s1464 )
*s1464 << std::internal;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1911(){
if( s1464 )
*s1464 << std::fixed;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1554(){
if( s1464 )
*s1464 << std::showpos;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1940(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1463 )
*s1463 >> std::resetiosflags( f );}
template<class s1409, class s1411>
Stream::s1909 s1395<s1409, s1411>::s1946() const{
return s1463->flags();}
template<class s1409, class s1411>
Stream::s1910 s1395<s1409, s1411>::s1947() const{
return s1463->precision();}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1936(){
if( s1463 )
*s1463 >> std::boolalpha;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1938(){
if( s1463 )
*s1463 >> std::noboolalpha;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1937(){
if( s1463 )
*s1463 >> std::fixed;}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1941( int n ){
if( s1463 )
*s1463 >> std::setw( n );}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1939( int n ){
if( s1463 )
*s1463 >> std::setprecision( n );}
s505::s505( s262* s300, s272* ns_, const s263* ast_ )
: s1395( s300, ns_, ast_ ){
s491 = Types.s783;
s1463 = (basic_istringstream<wchar_t>*) &ss;
s1464 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s505::s505( const s505& r, const s263* ast_ )
: s1395( r.s300, r.ns, ast_ ), ss( r.ss.str() ){
s491 = Types.s783;
s1463 = (basic_istringstream<wchar_t>*) &ss;
s1464 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s481* s505::s353( s272* s586, const std::vector<s271*>&, const s263* ast_ ) const{
return new s505( s300, s586, ast_ );}
void s505::s348(){
s1395<s1956,s1957>::s348();
s346 = s1395<s1956, s1957>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s505::s1227, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"str", new s335( L"str", &s505::s506, Types.String,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", &s505::s328, s1895,
{ s1113() }, 0, 0 ) ) );
s300->TR().s1153( s491, s7::s1398, s1501::s1494 );
s300->TR().s1153( s491, s7::s1403, s1501::s1498 );
s300->TR().s1153( s491, s7::s1397, s1501::s1493 );}
void s505::s498( const s272*, bool ){
s1252();}
void s505::release(){
ss.clear();}
s481* s505::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s_ = s695.s291();
if( s_.find( L"StringStream(" ) == 0 )
return new s505( s300, s586, &s695 );
return NULL;}
s271* s505::s333( s589* s2042, s272* impl ) const{
return new s505( *this );}
void s505::s354( s271* p ) const{
if( p->s350() == s1895 )
((s505*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s350() ) );}
void s505::s1450( std::wstring& s153, size_t s1461 ){
s153 = ss.str().substr( 0, s1461 );}
void s505::s1469( s1890& src ){
ss << src;}
void s505::s1451( std::wstring& s153, s1890& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
std::getline( ss, s153, s72[0] );}
void s505::s1470( s1890& src ){
ss << src << endl;}
void s505::s1449( s1312& s153, size_t s1461 ){
s153 = (tdbyte_t*)U8( ss.str().substr( 0, s1461 )).data();}
void s505::s1468( const s1312& src ){
ss << U16( (char*)src.c_str() );}
void s505::s1448( s1312& s153, const s1312& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s72.c_str()) + L"'" );
s153.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s72.c_str())[0]);}
void s505::s1467( const s1312& src ){
ss << U16( (char*)src.c_str() ) << endl;}
void s505::s1898( wchar_t c ){
if( s1464 )
*s1464 << std::setfill( c );}
wstring s505::to_wstring( uint32_t s1553 ) const{
return ss.str(); }
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s505*)(s482*)*s274)
inline void s505::s1227( s481** s274, size_t s496 ){
s505* ps = (s505*)DR;
s505* s681 = new s505( ps->s300, ps->ns, ps->s601() );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s505::s506( s481** s274, size_t s496 ){
s505* pst = (s505*)DR;
*( (s357*)s274[0] )->s355() = pst->ss.str();}
inline void s505::s328( s481** s274, size_t s496 ){
((s505*)DR)->ss.rdbuf()->str(L"");}
void s505::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << ss.str() << endl;}
size_t s505::s320() const{
return hash<wstring>{}(ss.str());}
bool s505::operator==( const s481* p ) const{
return ( (s505*)p )->ss.str() == ss.str();}
bool s505::operator<( const s481* p ) const{
return ss.str() < ( (s505*)p )->ss.str();}
s1284::s1284( s262* s300, s272* ns_, const s263* ast_ )
: s1395( s300, ns_, ast_ ){
s491 = Types.ByteStream;
s1463 = (basic_istringstream<tdbyte_t>*) &bs;
s1464 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1284::s1284( const s1284& r, const s263* ast_ )
: s1395( r.s300, r.ns, ast_ ), bs( r.bs.str() ){
s491 = Types.ByteStream;}
s481* s1284::s353( s272* s586, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1284( s300, ast_ );}
void s1284::s348(){
s1395<s1484, s1487>::s348();
s346 = s1395<s1484, s1487>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1284::s1227, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"array", new s335( L"array", &s1284::s1305, Types.String,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"clear", new s335( L"clear", &s1284::s328, s1891,
{ s1113() }, 0, 0 ) ) );
s300->TR().s1153( s491, s7::s1398, s1501::s1494 );
s300->TR().s1153( s491, s7::s1403, s1501::s1498 );
s300->TR().s1153( s491, s7::s1397, s1501::s1493 );}
void s1284::s498( const s272*, bool ){
s1252();}
void s1284::release(){
bs.clear();}
s481* s1284::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s_ = s695.s291();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1284( s300 );
return NULL;}
s271* s1284::s333( s589* s2042, s272* impl ) const{
return new s1284( *this );}
void s1284::s354( s271* p ) const{
if( p->s350() == s1891 )
((s1284*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s350() ) );}
void s1284::s1450( std::wstring& s153, size_t s1461 ){
s153 = U16( (char*)bs.str().c_str() ).substr( 0, s1461 );}
void s1284::s1469( s1890& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1284::s1451( std::wstring& s153, s1890& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s153.clear();
s1312 tmp;
std::getline( bs, tmp, (unsigned char)U8(s72.data())[0] );}
void s1284::s1470( s1890& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1284::s1449( s1312& s153, size_t s1461 ){
s153 = bs.str().substr( 0, s1461 );}
void s1284::s1468( const s1312& src ){
bs << src.data();}
void s1284::s1448( s1312& s153, const s1312& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s72.c_str()) + L"'" );
s153.clear();
std::getline( bs, s153, s72[0] );}
void s1284::s1467( const s1312& src ){
bs << src << endl;}
wstring s1284::to_wstring( uint32_t s1553 ) const{
s1312 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s1284*)(s482*)*s274)
inline void s1284::s1227( s481** s274, size_t s496 ){
s1284* ps = (s1284*)DR;
s1284* s681 = new s1284( ps->s300, ps->s601() );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s1284::s1305( s481** s274, size_t s496 ){
s1312 s = ( (s1284*)DR)->bs.str();
( (s1282*)s274[0] )->s318().assign( begin( s ), end( s ) );}
inline void s1284::s328( s481** s274, size_t s496 ){
((s1284*)DR)->bs.rdbuf()->str(0);}
void s1284::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : [...]" << endl;}
size_t s1284::s320() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1284::operator==( const s481* p ) const{
return ( (s1284*)p )->bs.str() == bs.str();}
bool s1284::operator<( const s481* p ) const{
return bs.str() < ( (s1284*)p )->bs.str();}
s1292::s1292( s262* s300, s272* ns_, const s263* ast_ )
: s1395( s300, ns_, ast_ ){
s491 = Types.FileStream;
s1463 = NULL;
s1464 = NULL;}
s1292::s1292( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ )
: s1395( s300, s586, ast_ ){
s491 = Types.FileStream;
s1463 = NULL;
s1464 = NULL;
if( l.size() ) {
if( l[0]->s350() == Types.String )
s1331 = l[0]->to_wstring();
else
s210 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1292::s1292( const s1292& r, const s263* ast_ )
: s1395( r.s300, r.ns, ast_ ), s210( r.s210 ), mode( r.mode ){
s491 = s1893;
s1463 = NULL;
s1464 = NULL;}
s481* s1292::s353( s272* s586, const std::vector<s271*>&, const s263* ast_ ) const{
return new s1292( s300, ast_ );}
void s1292::s348(){
s1395<s1485, s1488>::s348();
s346 = s1395<s1485, s1488>::s340();
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1292::s1227, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"open-r", new s335( L"open-r", &s1292::s2013, s1143,
{ s1113(), s1113( { Types.String } ), s1113( { Types.String, Types.String } ) }, false, s2035 ) ) );
s346.insert( make_pair( L"open-w", new s335( L"open-w", &s1292::s2015, s1143,
{ s1113(), s1113( { Types.String } ), s1113( { Types.String, Types.String } ) }, false, s2035 ) ) );
s346.insert( make_pair( L"open-rw", new s335( L"open-rw", &s1292::s2014, s1143,
{ s1113(), s1113( { Types.String } ), s1113( { Types.String, Types.String } ) }, 0, 2 ) ) );
s346.insert( make_pair( L"close", new s335( L"close", &s1292::s1314, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"read-bytes", new s335( L"read-bytes", &s1292::s2021, s1143,
{ s1113( { s1140 } ), s1113( { s1140, s1142 } ) }, 2, 2 ) ) );
s346.insert( make_pair( L"read-lines", new s335( L"read-lines", &s1292::s1473, 0,	
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"read-text", new s335( L"read-text", &s1292::s407, Types.String,	
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"write", new s335( L"write", &s1292::s1345, s1143,
{ s1113( { s1140, s1142 } ) }, 2, 2 ) ) );
s300->TR().s1153( s491, s7::s1398, s1501::s1494 );
s300->TR().s1153( s491, s7::s1403, s1501::s1498 );
s300->TR().s1153( s491, s7::s1397, s1501::s1493 );}
void s1292::s498( const s272*, bool ){
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, Types.String )->s351() + L">";
s1054 pt = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s346.equal_range( L"read-lines" ).first->second->s1253( pt );
s1252();}
void s1292::release(){
fs.close();}
s481*
s1292::s352( const s263& s695, s272* s586, s1890& s332 ) const{
wstring s_ = s695.s291();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s271*> s699;
s271::s1323( s695, s300, s586, s332, s699 );
return new s1292( s300, s699, s586, &s695 );}
return NULL;}
s271*
s1292::s333( s589* s2042, s272* impl ) const{
return new s1292( *this );}
void s1292::s354( s271* p ) const{
if( p->s350() == s1893 ) {
((s1292*)p)->s210 = s210;
((s1292*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s351() + L" to " + 
p->s351() );}
void s1292::s1450( std::wstring& s153, size_t s1461 ){
size_t s1102 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1102;
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
enc = s1676;}
else if( c1 == 0xFE && c2 == 0xFF ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1677;}
else if( c1 == 0xFF && c2 == 0xFE ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1678;}
else if( c1 == 0x0 && c2 == 0x0 && c3 == 0xFE && c4 == 0xFF ) {
enc = s1679;
fsz -= 4;}
else if( c1 == 0xFF && c2 == 0xFE && c3 == 0x0 && c4 == 0x0 ) {
enc = s1680;
fsz -= 4;}
else
fs.seekg( 0, ios_base::beg );}
size_t s1492 = s1461 ? ( std::min )( s1461, fsz ) : fsz;
string buf( s1492 + 0, '\0' );
fs.read( &buf[0], s1492 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1331 + L"'" );}
if( !enc || enc == s1676 ) {
s153 = U16( buf );
s153.shrink_to_fit();}
else {
fs.close();
throw new s16( L"file is not in UTF8 encoding and cannot be read as text: '" + s1331 + L"'" );}}
void s1292::s1469( s1890& src ){
fs << U8(src).data();}
void s1292::s1451( std::wstring& s153, s1890& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s153.clear();
if( fs.eof() )
return;
string buf;
char s1460 = U8( s72.data() )[0];
std::getline( fs, buf, s1460 );
s153 = U16( buf.data() );}
void s1292::s1470( s1890& src ){
fs << U8(src).data() << endl;}
void s1292::s1449( s1312& s153, size_t s1461 ){
size_t s1102 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios::end ).tellg() - s1102;
fs.seekg( s1102 );
size_t s1492 = s1461 ? (std::min)( s1461, fsz ) : fsz;
s153.resize( s1492 );
fs.read( (char*)&s153[0], s1492 );}
void s1292::s1468( const s1312& src ){
fs << *(string*)&src;}
void s1292::s1448( s1312& s153, const s1312& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s72.c_str() ) + L"'" );
string buf;
s153.clear();
std::getline( fs, buf, (char)s72[0] );
std::swap( buf, *(string*)(&s153) );}
void s1292::s1467( const s1312& src ){
fs << *(string*)&src << endl;}
wstring s1292::to_wstring( uint32_t s1553 ) const{
return L"FileStream"; }
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s1292*)(s482*)*s274)
inline void s1292::s1227( s481** s274, size_t s496 ){
s1292* ps = (s1292*)DR;
s1292* s681 = new s1292( *ps );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
void s1292::s1991( s481** s274, size_t s496, wstring& s1335 ){
s1292* pf = (s1292*)DR;
if( s496 > 2 ) {
if( s274[2]->s350() == Types.String ) {
pf->s1331 = s274[2]->to_wstring();
pf->s210 = NULL;}
else {
pf->s210 = s274[2];
pf->s1331 = L"";}}
s483 s1990;
if( s496 > 3 ) {
s1990 = s274[3];
pf->mode = s1990;}
else
s1990 = pf->mode;
if( s1990.s14() ) {
if( s1990->s492() == s474 )
s1335 = s1990->s495( 0, 0 )->to_wstring();
else if( s1990->s492() != s473 )
s1335 = s1990->to_wstring();
else
s1335 = s1990.s15<s369*>()->s375()->to_wstring();}}
inline void s1292::s2013( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
wstring s1335 = L"r";
s1991( s274, s496, s1335 );
if( s1335 != L"r" )
throw new s16( L"file open mode '" + s1335 + 
L"' is incompatible with '(open-r)' method" );
if( pf->s300->s1997( s2035, s2031 ) )
return;
pf->_open( s1335 );}
inline void s1292::s2015( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
wstring s1335 = L"w";
s1991( s274, s496, s1335 );
if( s1335 != L"w" && s1335 != L"x" && s1335 != L"a" )
throw new s16( L"file open mode '" + s1335 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s1997( s2036, s2031 ) )
return;
pf->_open( s1335 );}
inline void s1292::s2014( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
wstring s1335 = L"r+";
s1991( s274, s496, s1335 );
if( s1335 != L"w" && s1335 != L"x" && s1335 != L"a" )
throw new s16( L"file open mode '" + s1335 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s300->s1997( s2035, s2031 ) || 
pf->s300->s1997( s2036, s2031 ))
return;
pf->_open( s1335 );}
inline void s1292::s1314( s481** s274, size_t s496 ){
((s1292*)DR)->_close();
((s1292*)DR)->s1463 = NULL;
((s1292*)DR)->s1464 = NULL;}
inline void s1292::s1345( s481** s274, size_t s496 ){
assert( s496 == 4 );
assert( s274[2]->s350() == s1140 );
s1292* pf = (s1292*)DR;
if( pf->s300->s1997( s2036, s2031 ) )
return;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1331 + L"'." );
s1282* s1324 = (s1282*)s274[2];
s481* s1326 = s274[3];
int s1339 = (int)*s1326;
pf->fs.write( (const char*)s1324->s318().data(), s1339 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1331 + L"'." );}
inline void s1292::s407( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
if( pf->s300->s1997( s2035, s2031 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s357* s681 = (s357*)*s274;
pf->s1450( s681->s318(), 0 );}
inline void s1292::s2021( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
if( pf->s300->s1997( s2035, s2031 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s1282& bar = *(s1282*)s274[2];
pf->s1449(bar.s318(), 0 );}
inline void s1292::s1473( s481** s274, size_t s496 ){
s1292* pf = (s1292*)DR;
if( pf->s300->s1997( s2035, s2031 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)pf->addr();
s314& v = *(s314*)s692;
string buf;
while(std::getline( fs, buf/*, widen('\n')*/ ) ) {
v.s318().push_back( new s357( pf->s300 ) );
v.s318().back().s15<s357*>()->s1945( U16( buf ) );
v.s318().back()->s1252();
if( fs.eof() )
break;}
if( fs.bad() )
throw new s16( L"cannot read from file '" + pf->s1331 + L"'" );}
void s1292::_open( const wstring& s1335 ){
if( fs.is_open() )
fs.close();
wstring path;
if( !s1331.empty() )
path = s1331;
else {
if( s210->s492() != s473 )
path = s210->to_wstring();
else 
path = s210.s15<s369*>()->s375()->to_wstring();
s1331 = path;}
if( !s3::s718( path ) )
path = s300->s710() + path;
s1463 = NULL;
s1464 = NULL;
std::ios_base::openmode md;
if( s1335.empty() || s1335 == L"r" ) {
md = ios::in | ios::binary;
s1463 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1335 == L"w" || s1335 == L"x" ) {
md = ios::out | ios::binary;
s1464 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1335 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1464 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1335 + L"'." );
if( s1335 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1292::_close(){
mode = s210 = NULL;
s1331.clear();
fs.close();}
void s1292::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << s351() << L" : " << s1331 << endl;}
size_t s1292::s320() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1292::operator==( const s481* p ) const{
return this == p;}
bool s1292::operator<( const s481* p ) const{
return this < p;}
s1391::s1391( s262* s300, s272* ns_, const s263* ast_ )
: s1395( s300, ns_, ast_ ){
s1463 = &std::wcin;}
s481* s1391::s353( s272* s586, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1391::s348(){
s346.insert( make_pair( L"get", new s335( L"get", &s1391::s325, s1144,
{ s1113() }, 0, 0 ) ) );
s300->TR().s1153( s491, s7::s1398, s1501::s1494 );}
void s1391::s498( const s272*, bool ){
s1252();}
s481* s1391::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return NULL;}
s271* s1391::s333( s589* s2042, s272* impl ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1391::s354( s271* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1391::s1450( std::wstring& s153, size_t s1461 ){
s153.clear();
wcin >> s153;
if( s1461 && s153.size() > s1461 )
s153.resize( s1461 );}
void s1391::s1469( s1890& src ){
throw new s16( L"cannot output to StdIn" );}
void s1391::s1451( std::wstring& s153, s1890& s72 ){
wcin >> std::ws;
s153.clear();
std::getline( wcin, s153 );}
void s1391::s1470( s1890& src ){
throw new s16( L"cannot output to StdIn" );}
void s1391::s1449( s1312& s153, size_t s1461 ){
wstring buf( s1461, L'\0' );
wcin.read( &buf[0], s1461 );
size_t s681 = wcin.gcount();
buf.resize( s681 );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1391::s1468( const s1312& src ){
throw new s16( L"cannot output to StdIn" );}
void s1391::s1448( s1312& s153, const s1312& s72 ){
wstring buf;
std::getline( wcin, buf );
s153 = (tdbyte_t*)U8( buf ).data();}
void s1391::s1467( const s1312& src ){
throw new s16( L"cannot output to StdIn" );}
inline void s1391::s325( s481** s274, size_t s496 ){
s357* s681 = (s357*)*s274;
wchar_t s153;
wcin.get( s153 );
*s681->s355() = wstring( s153, 1 );}
wstring s1391::to_wstring( uint32_t s1553 ) const{
throw new s16( L"22: not implemented" );}
void s1391::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdIn object" << endl;}
size_t s1391::s320() const{
throw new s16( L"15: not implemented" );}
bool s1391::operator==( const s481* p ) const{
throw new s16( L"16: not implemented" );}
bool s1391::operator<( const s481* p ) const{
throw new s16( L"17: not implemented" );}
s1393::s1393( s262* s300, s272* ns_, const s263* ast_ )
: s1395( s300, ns_, ast_ ){
s1464 = &std::wcout;}
s481* s1393::s353( s272* s586, const std::vector<s271*>&, const s263* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1393::s348(){
s300->TR().s1153( s491, s7::s1403, s1501::s1498 );}
void s1393::s498( const s272*, bool ){
s1252();}
s481* s1393::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return NULL;}
s271* s1393::s333( s589* s2042, s272* impl ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1393::s354( s271* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1393::s1450( std::wstring& s153, size_t s1461 ){
throw new s16( L"cannot get input from StdOut" );}
void s1393::s1469( s1890& src ){
wcout << src;}
void s1393::s1451( std::wstring& s153, s1890& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1393::s1470( s1890& src ){
wcout << src << endl;}
void s1393::s1449( s1312& s153, size_t s1461 ){
throw new s16( L"cannot get input from StdOut" );}
void s1393::s1468( const s1312& src ){
wcout << U16( (const char*)src.data() );}
void s1393::s1448( s1312& s153, const s1312& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1393::s1467( const s1312& src ){
wcout << U16( (const char*)src.data() ) << endl;}
void s1393::s1898( wchar_t c ){
if( s1464 )
*s1464 << std::setfill( c );}
wstring s1393::to_wstring( uint32_t s1553 ) const{
throw new s16( L"21: not implemented" );}
void s1393::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"StdOut object" << endl;}
size_t s1393::s320() const{
throw new s16( L"18: not implemented" );}
bool s1393::operator==( const s481* p ) const{
throw new s16( L"19: not implemented" );}
bool s1393::operator<( const s481* p ) const{
throw new s16( L"20: not implemented" );}
s603::s603( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695,
bool s2160 )
: s589( s300, s590, s591, s591, s563, s233, s695, true, s2160 ){
TDException s961( s7::s1674, s926, s695, L"malformed syntax of 'with' statement" );
size_t n = 0;
bool s1159;
for( ; n < l.size(); n += 2 ) {
s1159 = false;
if( ( (s481*)l[n] ) == s1672 ) {
if( l.size() == n )
throw s961.s993( L"the 'const' keyword should precede the parameter name" );
s1159 = true;
++n;}
if( l[n]->s492() != s473 ) {
if( s1159 )
throw s961.s993( L"the 'const' keyword should precede the parameter name" );
break;}
s369* s76 = (s369*)l[n];
s481* s617 = (s481*)l[n + 1];
if( s1159 )
s76->s1250();
s626.s539( s76->s615(), s617 );
s274.push_back( s617->s333(0,0) );
s580.push_back( s617 );
s628.push_back( s617 );
s629.push_back( *s76 );}
s582.insert( s582.end(), l.begin() + n, l.end() );}
s603::s603( const s603& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), s601(), true,
right.s2159 ){
s491 = 0;// Types.Null;
}
void
s603::s498( const s272* s1658, bool proc ){
for( size_t n = 0; n < s582.size(); ++n )
s582[n].s15<s559*>()->s2171( true );
s589::s498( this, proc );
if( !s491 )
s491 = s1143;
return;
s667 = proc ? s586->s298() : s1658->s298();
if( s586->s492() == s477 || s586->s492() == s476 || s586->s492() == s2150) {
if( s586->s492() == s476 || s586->s492() == s2150 )
return;}
if( s274.size() > s628.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s274.size(); ++n ) {
s483 par = s274[n];
if( par->s492() == s473 ) {
if( par.s15<s369*>()->s379().s13() )
par.s15<s369*>()->s498( this, proc );}
else
s841( par, n, s274[n], s1658, false );}
for( size_t n = 0; n < s274.size(); ++n ) {
s626.s539( s629[n].s615(), s274[n].s15<s481*>(), s480::s147 );
s274[n]->s1665( s7::s861 );
s628[n] = s274[n];}
for( size_t n = 0; n < s582.size(); ++n ) {
if( s582[n]->s492() == s475 ) {
s488 cs = new s559( *s582[n].s15<s559*>() );
s582[n] = s598( cs, s300, s586, this, s586->s298(), true );}
else if( s582[n]->s492() == s473 )
s582[n].s15<s369*>()->s498( s585, proc );
else if( s582[n]->s492() != s474 )
s582[n]->s498( s585 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s582 ) {
if( it->s492() == s474 )
it.s15<Transd*>()->s498( s586, true );}
if( !s491 && s582.size() ) {
s491 = s582.back()->s350();
s584 = s300->TR().s516( s350(), s586, s586->s298() );}}
s484
s603::s495( s481** s687, size_t s691 ){
s484 s681 = s363;
size_t s2229 = 0;
size_t n;
if( s2220 == -1 ) {
s628.resize( s274.size() );
for( size_t n = 0; n < s274.size(); ++n ) {
s484 s153;
if( s274[n]->s492() == s472 || 
s274[n]->s492() == s478 ) {
s153 = (s481*)s274[n]->s333(0,0);
s153->s498( this, true );}
else {
s153 = s274[n]->s495( NULL, 0 );}
if( s153->s616() < 0 ) {
if( s153->s616() == s7::s860 )
s153->s1665( 0 );
else {
s584 = s153;
return s153;}}
s628[n] = s153.s15<s482*>();}}
else
s2229 = (size_t)s2220;
for( n = s2229; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s687, s691 );
if( s681->s616() < 0 )
break;}
if( s681->s616() != s7::s2219 ) {
for( size_t n = 0; n < s274.size(); ++n ) {
s274[n]->release();}
s2220 = -1;}
else
s2220 = (int)n;
s584 = s681;
return s681;}
s305::s305( s262* s300, s272* s590, Transd* s591, const std::vector<s271*>& l, const s263* s695,
bool s2160 )
: s589( s300, s590, s591, s591, s563, s255, s695, true, s2160 ){
if( l.size() < 2 )
throw new s16( s255 + L"(): wrong numbers of arguments" );
s274.push_back( l[0] );
s628.resize( 1 );
s629.push_back( s369( L"@cond", s300 ) );
s582.insert( s582.end(), l.begin() + 1, l.end() );}
s305::s305( const s305& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), s601(), right.s2159 ){}
void
s305::s498( const s272* s1658, bool proc ){
for( size_t n = 0; n < s582.size(); ++n )
s582[n].s15<s559*>()->s2171( true );
s589::s498( s1658, proc );
s306 = s628[0] = s274[0];
s491 = s582.back()->s350();}
s484
s305::s495( s481** s687, size_t s691 ){
s484 s681 = s363, s153;
while( 1 ) {
if( (bool)*s306->s495( 0, 0 ) == false )
return s681; 
for( size_t n = 0; n < s582.size(); ++n ) {
s153 = s582[n]->s495( s687, s691 );
if( s153->s616() < 0 )
break;}
s681 = s153;
if( s681->s616() < 0 /*s681->s616() == s7::s437 || s681->s616() == s7::s438*/ ) {
if( s681->s616() == s7::s437 )
s681 = s363.s15<s481*>();
break;}}
return s681;}
s612::s612( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l,
const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, s563, s260, s695, true, s2160 ),
s309( s7::s460, s300 ), s310( s300, 0, NULL ), s2274( NULL ){
TDException s961( s7::s1654, s926, s695, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s961.s993( L"too few arguments" );
s626.s539( s309.s615(), &s310 );
s580.push_back( (s481*)&s310 );
s628.push_back( (s481*)&s310 );
s629.push_back( s369( s309.s615(), s300 ) );
s271* p = l[0];
if( p->s492() != s473 )
throw s961.s993( L"the variable must be a name" );
s707 = (s369*) l[0];
varval = s363.s15<s481*>();
s369* in = (s369*) l[1];
if( in->s615() != L"in" )
throw s961.s993( L"the 'in' keyword is missing" );
s308 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s492() != s473 )
throw s961.s993( actmsg );
if( ((s369*)p)->s615() == L"where" ) {
where = l[4];
idx = 5;}
if( l.size() < ( idx + 2 ) )
throw new s16( actmsg );
p = l[idx];
if( p->s492() != s473 )
throw new s16( actmsg );
if( ((s369*)p)->s615() == L"project" ) {
if( l.size()  )
s1053 = l[idx+1];}
else {
if( ((s369*)p)->s615() != L"do" )
throw new s16( actmsg );
s582.assign( l.begin() + (idx + 1), l.end() );}
s626.s539( s707->s615(), NULL );
s580.push_back( varval );
s628.push_back( varval );
s629.push_back( s369( s707->s615(), s300 ) );}
s612::s612( const s612& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), s601(), true,
right.s2159 ),s707(right.s707),varval(right.varval),s308(right.s308),where(right.where),
s1053(right.s1053),s309( s7::s460, right.s300 ), s310( right.s300, 0, NULL ), s2274( NULL ){
s584 = right.s584;
s491 = right.s491;}
void
s612::s498( const s272* s1658, bool proc ){
TDException s961( s7::s1367, s926, s601(), L"malformed syntax of 'for' statement" );
s470 pc = s308->s492();
if( pc == s475 ) {
s483 s590 = s598( s308.s15<s559*>(), s300, s586, this, s298(), proc );
s308 = s590;
s308.s15<Transd*>()->s498( s1658, false );}
else if( pc == s473 ) {
s308.s15<s369*>()->s498( this, proc );}
else if( pc == s472 )
s308->s498( this );
else
throw s961.s993( L"unknown iterable type" );
s482* s1465;
if( s308->s350() == Types.Range )
s1465 = ((s383*)s308->s494())->s813();
else
s1465 = s308->s494();
s1054 vt;
if( s300->TR().s1454( s1465->s350(), s1501::s1497 ) )
vt = ( (s324*)s1465 )->ValType();
else
vt = ( (s324*)s1465 )->s317();
varval = s300->TR().s516(vt, s586, s586->s298() );
varval->s1665( s7::s861 );
s707->s380( varval );
s628[1] = varval.s15<s482*>();
s626.s539( s707->s615(), varval.s15<s482*>(), s480::s147 );
if( where ) {
pc = where->s492();
if( pc == s475 ) {
where = s598( where.s15<s559*>(), s300, s586, this, s298(), proc );
where.s15<Transd*>()->s498( s1658, false );}
else
throw s961.s993( L"WHERE clause must be a lambda" );}
if( s1053 ) {
pc = s1053->s492();
if( pc == s475 ) {
s1053 = s598( s1053.s15<s559*>(), s300, s586, this, s298(), proc );
s1053.s15<Transd*>()->s498( s1658, false );}
else if( pc == s473 ){
s1053.s15<s369*>()->s498( this );}
else if( pc == s472 )
(void)0;
else
throw s961.s993( L"PROJECT clause must be a lambda." );
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
s300->TR().s798( s1053->s350() ) + L">";
ts = s300->TR().s1342( ts );
s491 = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );}
for( size_t n = 0; n < s582.size(); ++n )
s582[n].s15<s559*>()->s2171( true );
s589::s498( s1658, /*proc*/ false );
}
void s612::s2118( s589* s2042, s272* impl, bool s2160 ){
if( s585 ) s585 = s2042;
if( impl ) s586 = impl;
s589::s2118( this, impl, s2160 );
s308->s2118( this, impl, s2160 );
if( s1053.s14() )
s1053->s2118( this, impl, s2160 );}
s484 s612::s495( s481** s687, size_t s691 ){
TDException s961(  s7::s2276,
s1368, NULL, L"error during running 'for' loop", TDException::Stage::s1023 );
s484 s681 = s584;
size_t s2229 = 0;
size_t n;
s9<s324> s978;
Iterator* s1013 = NULL;
if( s2220 == -1 ) {
s470 pc = s308->s492();
if( pc == s474 )
s978 = s308->s495( 0, 0 ).s15<s324*>();
else if( pc == s473 ) {
s978 = ( (s324*)s308.s15<s369*>()->s375() );}
else
s978 = s308.s15<s324*>();
assert( s978.s14() );
if( s978->s616() < 0 ) {
wstring s78 = L"failed to initialize iterable object";
if( s978->s350() == Types.s359 )
s78 += L": " + ((s359*)s978.s15<s271*>())->Msg();
s961.s2288( (s263*)s978->s601() );
throw s961.s993( s78 );}
if( s1053.s14() )
s584.s15<s314*>()->clear();
s1013 = s978->s312( NULL );}
else {
s2229 = s2220;
s1013 = s2274;}
while( 1 ) {
if( !s2229 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
s628[0] = s1013->Idx();
s628[1] = p.s15<s482*>();
if( where ) {
if( ((bool)*(s481*)where->s495( 0, 0 )) != true )
continue;}}
if( s1053 ) {
s584.s15<s314*>()->add( 
s1053->s495( 0, 0 ).s15<s482*>());//->s333(0,0) );
}
else {
for( n = s2229; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s687, s691 );
if( s681->s616() < 0 )
break;}
if( s681->s616() < 0 && s681->s616() != s7::s436 ) {
if( s681->s616() == s7::s437 )
s681 = s363.s15<s481*>();
else if( s681->s616() == s7::s2219 ) {
s2220 = (int)n;
if( !s2274 ) {
s2274 = s1013;
s2273 = s978;}}
else if( s681->s616() == s7::s2265 ) {
s2220 = (int)n + 1;
if( s2220 == s582.size() )
s2220 = 0;
s681->s1665( s7::s2219 );
if( !s2274 ) {
s2274 = s1013;
s2273 = s978;}}
else {
s2220 = -1;
s2274 = NULL;
s2273 = NULL;}
break;}}}
if( s681->s616() == s7::s436 )
return s363;
return s681;}
s271* s603::s333( s589* s2042, s272* impl ) const{
s603* s681 = new s603( *this, impl, s2042 );
s681->s2118( s681, impl, s2159 );
return s681;}
s271* s305::s333( s589* s2042, s272* impl ) const{
s305* s681 = new s305( *this, impl, s2042 );
s681->s2118( s681, impl, s2159 );
return s681;}
/*s271* s307::s333( s589* s2042, s272* impl ) const
{
return new s307( *this );}
*/
s271* s612::s333( s589* s2042, s272* impl ) const{
s612* s681 = new s612( *this, impl ? impl : s586.s15<s272*>(), s2042 );
return s681;}
s602::s602( s262* s300, s272* s586, s589* s585,
s561 ct, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s586, s585, s585, ct, l, s695, false, false ){
s574 = s571;}
void s602::s646( s1054 s617, s589* pOvr ){
types.push_back( s617 );
s647.push_back( pOvr );}
s484 s602::s495( s481** s687, size_t s691 ){
return s589::s495( s687, s691 );}
s832::s832( s262* s300 )
: s589( s300, NULL, NULL, NULL, s565, s252, NULL ), s2089( false ){
s490 = s1235;
s491 = Types.Lambda;
if( !s491 )
wh = s7::s862;
else
wh = s7::s861;}
s832::s832( const s832& )
: s589( s300, NULL, NULL, NULL, s565, s252, NULL ){
throw;}
s832::s832( s262* s300, s272* s590, s589* s591, 
const std::vector<s271*>& l, const s263* s695, s1054 s2107, bool s2090,
bool s2160 )
: s589( s300, s590, s591, s590, s565, s252, s695, false,
s2160 ), s2089( s2090 ){
ns = s586;
s490 = s1235;
bool s1159;
bool s2132 = false;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
s1159 = false;
if( n == 0 && l[n]->s492() == s472 ) {
const s807& vt = s300->TR().s1006( l[n]->s350() );
s1054 pt = vt.s813()[0];
if( pt == s1703 )
s2095 = (s952*)l[n];
else
throw new s16( L"unknown first member in lambda definition" );
n -= 1;
continue;}
if( ( (s481*)l[n] ) == s867 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s1888.push_back( l[n + 1]->s350() );
n += 2;
break;}
if( ((s481*)l[n]) == s2131 ) {
s2132 = true;
n -= 1;
continue;}
else if( ((s481*)l[n]) == s1672 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition: the 'const' keyword ");
s1159 = true;
++n;}
if( l[n]->s492() != s473 )
break;
s369* s76 = (s369*)l[n];
if( s1159 )
s76->s1250();
s481* s617 = (s481*)l[n + 1];
s626.s539( s76->s615(), s617 );
s274.push_back( s617 );
if( !s2132 )
s580.push_back( s617 );
else
s617->s2181( s2185 );
s628.push_back( s617 );
s1888.push_back( s617->s350() );
s629.push_back( s369( s76->s615(), s300 ) );}
if( s2107 ) {
const s807& vt = s300->TR().s1006( s2107 );
s1888.clear();
for( size_t n = 2; n < vt.s813().size(); n += 2 )
s1888.push_back( vt.s813()[n] );
s491 = s2107; // s1888.back();
}
else {
if( s1888.empty() )
s1888 = { s1143, s1143 };
else if( s1888.size() == 1 )
s1888.insert( s1888.begin(), s1143 );
s807::Cont vt = { s1702, (s1054)s1888.size() };
for( size_t n = 0; n < s1888.size(); ++n ) {
vt.push_back( s1888[n] );
vt.push_back( 0 );}
s491 = s300->TR().s1039( vt );}
s582.insert( s582.end(), l.begin() + n, l.end() );}
s832::s832( s262* s300, s272* s590, const vector<s1054>& l,
s1054 pt, const s263* s695 )
: s589( s300, s590, NULL, s590, s565, s252, s695 ), s2089( false ){
s490 = s1235;
s491 = pt;
for( size_t n = 2; n < l.size(); n += 2 )
s1888.push_back( l[n] );
for( size_t n = 1; n < s1888.size() - 1; ++n ) {
s628.push_back( s300->TR().s516( s1888[n], s586, s586->s298() ) );
s274.push_back( s628.back() );
s629.push_back( s369(std::to_wstring( n ), s300 ) );
s626.s539( s629.back().s615(), s274.back().s15<s481*>(), s480::s147 );
s580.push_back( s628.back().s15<s481*>() );}
ns = s586;}
s832::s832( s832& s1886, s272* s590, s589* s591, const std::vector<s483>& l, const s263* s695 )
: s589( s1886, s590, s591, s590, vector<s482*>(), s695, false, true ), s2089( s1886.s2089 ),
s2095( s1886.s2095 ){
s490 = s1235;
s491 = s1886.s491;
s1888 = s1886.s1888;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( l[n].s15<s481*>() ) == s867 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s491 = l[n + 1]->s350();
n += 2;
break;}
if( l[n]->s492() != s473 )
break;
s369* s76 =  l[n].s15<s369*>();
lang::s654( s76->s615() );
s481* s617 = l[n + 1].s15<s481*>();
s626.s539( s76->s615(), s617 );
s274.push_back( s617 );
s580.push_back( s617 );
s628.push_back( s617 );
s629.push_back( s369( s76->s615(), s300 ) );}
if( s628.empty() ) {
s1886.s626.copy( s626, (s272*)s590, s591 );
s628 = s1886.s628;
s629 = s1886.s629;
s274 = s1886.s274;
s580 = s1886.s580;}
if( s2095.s14() ) {
bool _b = ( s629.size() == s274.size() );
const vector<s483>& v = s2095->s318();
for( size_t n = 0; n < v.size(); ++n ) {
s369* ref = v[n].s15<s369*>();
if( ref->s379().s14() ) {
ref->s2118( s591, s590, s2166() ); // ???DEBUG??? 220828
s481* _dv = ref->s375();
if( _dv->s616() == s7::s862 )
_dv->s498( s586, true );
if( _b ) {
s629.push_back( *ref );
s271* _p = _dv->s333( this, s586 );
s628.push_back( _p );
s626.s539( ref->s615(), s628.back().s15<s482*>() );}}
else if( s300->s1320() && !s626.s156( ref->s615() ) ) {
ref->s498( this, false );
s481* s2094 = ref->s375();
s629.push_back( *ref );
s271* _p = s2094->s333( this, s586 );
s628.push_back( _p );
s626.s539( ref->s615(), s628.back().s15<s482*>() );}}}
s582.insert( s582.end(), l.begin() + n, l.end() );
s1665( s1886.s616() );}
wstring s832::s828() const{
return ns->s828();}
s483 s832::s2284(){
return s586;
} // ???DEBUG??? 220801
s481* s832::s352( const s263& s695, s272* s586, s1890& s332 ) const{
TDException s961( s7::s1877, s926, &s695,
L"wrong Lambda constructor syntax" );
wstring s = s300->TR().s1342( s300->TR().s1265( s695.s291(), s332 ));
wstring sv;
wstring s767 = Types( s300, Types.Lambda )->s351();
wstring s1263, s642;
s1054 pt = 0;
s832* s681 = NULL;
if( s.find( s7::s1346 + L"<Lambda<" ) == 0 ) {
s1263 = s.substr( s7::s1346.size() + 1, s.size() - ( s7::s1346.size() + 2) );
size_t pl = s695.Src().find( 955 );
if( pl != string::npos ) {
s642 = s695.Src().substr( pl );
s = s1263 + L"(" + s642;}
else
s = s1263 + L"()";}
if( s.find( s767 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s961.s993( L"missing type signature" );
if( s1263.empty() )
s1152( s300, s, s1263, s642 );
if( s1263.empty() )
throw s961.s993( L"missing type signature" );
s807::Cont vt;
size_t pos = 0;
s300->TR().s1049( s1263, pos, vt );
pt = s300->TR().s1004( s807( vt ), false );
if( !pt )
pt = s300->TR().s1039( vt );
if( s642.size() ) {
if( s642.find( L"lambda" ) == 0 || s642[0] == 955 ) {
s940 ast_ = new s263( L"(" + s642 + L")", s695.Nqj(), ((s263*)&s695)->s2083() );
s488 cs = s589::s1110( *ast_, s300, s586, s586->s298(), false );
return new s832( s300, s586, NULL, cs->s600(), &s695, pt, false );}
else if( s642[0] != L']' )
throw s961.s993( L"malformed Lambda initializer" );}
s807::Cont vt1;
s300->TR().s2122( vt, vt1 );
s681 = new s832( s300, s586, vt1, pt, &s695 );}
return s681;}
void
s832::s498( const s272* s215, bool proc ){
s1054 pt = s491;
if( s585.s13() )
s585 = (s589*)s215; 
s2210( s215, proc );
if( s300->s1320() || s2089 ) { 
s491 = 0; // s1143;
if( !s585 ) s585 = (s589*)s215;
for( size_t n = 0; n < s582.size(); ++n )
s582[n].s15<s559*>()->s2171( true );
s589::s498( s586->s492() == s478 ? s586.s15<s272*>() : (s272*)this, proc ); // ???DEBUG??? 220830
if( s1888.size() < 2 || s1888.back() == s1143 ) {
if( s1888.empty() ) {
s1888.push_back( s1143 );
if( s582.size() )
s1888.push_back( s582.back()->s350() );
else
s1888.push_back( s1143 );}
s1888.back() = s491 ? s491 : s1888.back();
s807::Cont vt = { s1702, (s1054)s1888.size() };
for( size_t n = 0; n < s1888.size(); ++n ) {
vt.push_back( s1888[n] );
vt.push_back( 0 );}
s491 = s300->TR().s1039( vt );}
else
s491 = pt;
s1252();}
if( s584.s13() || s584->s350() != s491 ) {
if( s215 )
s584 = s300->TR().s516( s1318(), (s272*)s215, s215->s2154() );
else
s584 = s300->TR().s516( s1318(), s586, s586->s298() );}
if( s584.s13() )
s584 = s363.s15<s481*>();}
void s832::s2210( const s272* s215, bool proc ){
if( s2095.s14() /*&& (s300->s1320() || s2089 )*/ ) {
const vector<s483>& v = s2095->s318();
size_t s68 = s628.size() - v.size();
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n].s15<s369*>()->s379().s13() ) {
s369* ref = v[n].s15<s369*>();// ->s333();
ref->s498( this, proc );
s481* s2094 = ref->s375();
s629.push_back( *ref );
s271* s2120 = s2094->s333( this, s586 );
if( !s2120->s1195() )
s2120->s498( s215, proc );
s628.push_back( s2120 );
s626.s539( ref->s615(), s628.back().s15<s482*>() );}
else {
if( !s628[n + s68]->s1195() ) {
s628[n + s68]->s498( s215, proc );}
else {
s629[n + s68].s2118( this, (s272*)s215, proc );
s628[n + s68] = s629[n + s68].s375(); // ???DEBUG??? 220827
}}}}}
s484 s832::s495( s481** s687, size_t s691 ){
s484 s681 = s363;
size_t s2229 = 0;
size_t n;
if( s2220 == -1 ) {
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s579 + n ) ) {
s470 pc = ( ( s482* )*( s579 + n ) )->s492();
if( pc == s473 )
*( s578 + n + shift ) =
(s481*)( ( s369* )*( s579 + n ) )->s375();
else if( pc == s474 ) {
s974[n+shift] = (s481*)( ( s589* )*( s579 + n ) )->s495( s687, s691 );
*( s578 + n + shift ) = s974[n + shift];}
else if( pc == s472 || pc == s1235 ) {
if( n < s580.size() )
*( s578 + n + shift ) = ( s481* )*( s579 + n );
else
*( s578 + n + shift ) = ( s481* )((s482*)*( s579 + n ))->s333( 0, 0 );}
else if( pc == s478 ) {
*( s578 + n + shift ) = ( s481* )( ( s482* )*( s579 + n ) )->s333( 0, 0 );
s272* po = (s272*)( *( s578 + n + shift ) );
if( !po->s1195() ) // ???DEBUG??? 220627
(*( s578 + n + shift ))->s498( this, false );}}}
if( s581.size() > 1 ) {
for( size_t n = 1; n < s581.size(); ++n )
s628[n - 1] = s581[n];}}
else {
s2229 = s2220;}
for( n = s2229; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s578, s496 );
if( s681->s616() < 0 ) {
if( s681->s616() == s7::s2219 )
s2220 = (int)n;
else if( s681->s616() == s7::s2265 ) {
s2220 = (int)n + 1;
if( s2220 == s582.size() )
s2220 = 0;
else
s681->s1665( s7::s2219 );}
else {
if( s681->s616() == s7::s860 )
s681->s1665( 0 );
s2220 = -1;}
break;}}
return s681;}
s481* s832::s353( s272* s586, const vector<s1054>& vt ) const{
s1054 pt = s300->TR().s1039( vt );
return new s832( s300, s586, vt, pt, NULL );}
s481* s832::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s832( s300, s586, (s589*)s586, l, ast_ );}
s589* s832::s1671( s1890& s672, s589* s215, s272* s1658,
s559* cs ) const{
if( s672 == s7::s1346 ) {
if( cs->s600().size() > 1 && (cs->s600()[1]->s492() != s473 ||
((s369*)cs->s600()[1])->s615()[0] != 955 ))
throw new s16( L"malformed lambda syntax" );
s263* s1908 = (s263*)cs->s601();
s832* s1906 = (s832*) s352( *s1908, s586.s15<s272*>(), s586->s298() );
vector<s271*> s1907( { s1906 } );
return new s1667( s300, s586.s15<s272*>(), s215, &s481::s1880, 
s1907, s7::s1346, 0, cs->s601(), cs->s2166() );}
return s481::s1671( s672, s215, s1658, cs );}
s271* s832::s333( s589* s2042, s272* impl ) const{
s832* s681 = new s832( *(s832*)this, impl ? impl : s586.s15<s272*>(), 
(s589*)this, vector<s483>(), NULL );
return s681;}
void s832::s2118( s589* s2042, s272* impl, bool s2160 ){
if( s2042 && s2160 && !s2089 ) 
s585 = s2042;
s589::s2118( this, impl, s2160 );
if( s2095.s14() ) {
const vector<s483>& v = s2095->s318();
for( size_t n = 0; n < v.size(); ++n ) {			
s369* ref = v[n].s15<s369*>();
ref->s2118( s2042, impl, false );
s481* s2094 = ref->s375();
s271* s2120 = s2094->s333( s2042, s586 );
if( !s2120->s1195() )
s2120->s498( (s272*)s2042, false );
for( size_t m = 0; m < s629.size(); ++m ) {
if( s629[m].s615() == ref->s615() ) {
s628[m] = s2120;
s626.s539( ref->s615(), s628[m].s15<s482*>(), s480::s147 );}}}}}
s481* s832::s1881( s481** s274, size_t s496 ){
s832* s681 = new s832( *(s832*)this, s586, s585, vector<s483>(), NULL );
s681->s498( s585.s15<s272*>(), false ); 
return s681;}
wstring s832::trace( s1890& topics ) const{
wstringstream buf;
int s197 = 0;
wstring s1070 = std::to_wstring( reinterpret_cast<long long>( this ) );
s1070 = s1070.substr( s1070.size() - 5 );
if( topics.empty() ) {
buf << L"Lambda : " << s1070 << endl;
s589::s304( &buf, s197 );}
else {
if( topics == L"id" )
buf << L"id: " << s1070;
else if( topics == L"nexpr" )
buf << L"nexpr: " << s2220;}
return buf.str();}
void s832::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Lambda : " <<  s278 << endl;
s589::s304( pd, s197 );}
s604::s604( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s243, s695 ){
s274.assign( l.begin(), l.end() );
s491 = s1139;}
s484 s604::s495( s481**, size_t s496 ){
*s584.s15<s358*>()->s355() = 0;
for( size_t n = 0; n < s274.size(); ++n ) {
if( ( bool )*( (s482*)( s274[n]->s495( 0, 0 ) ) ) ) {
*s584.s15<s358*>()->s355() = 1;
return s584;}}
return s584;}
s605::s605( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, s563, s243, s695, false, s2160 ){
s274.assign( l.begin(), l.end() );
s491 = s1139;}
s484 s605::s495( s481**, size_t ){
*s584.s15<s358*>()->s355() = 1;
for( size_t n = 0; n < s274.size(); ++n ) {
if( !( bool )*( (s482*)( s274[n]->s495( 0, 0 ) ) ) ) {
*s584.s15<s358*>()->s355() = 0;
return s584;}}
return s584;}
s1396::s1396( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, s563, s1417, s695, false, s2160 ),
s1491( s7::s1363, s300 ),	s309( s7::s460, s300 ), s310( s300, 0, (s272*)NULL ){
TDException s961( s7::s1655, s926, s695, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s961.s993( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s626.s539( s309.s615(), &s310 );
s626.s539( s1491.s615(), NULL );
s628.push_back( (s481*)&s310 );
s628.push_back( NULL );
s629.push_back( s369( s309.s615(), s300 ) );
s629.push_back( s369( s1491.s615(), s300 ) );
s308 = l[0];
if( l.size() > 1 )
lambda = l[1];
s491 = s1139;}
void
s1396::s498( const s272* s1658, bool proc ){
TDException s961( s7::s1365, s926, s601(), L"malformed syntax of 'any()' function call" );
s470 pc = s308->s492();
if( pc == s475 ) {
s483 s590 = s598( s308.s15<s559*>(), s300, s586, this, s298(), proc );
s308 = s590;
s308.s15<Transd*>()->s498( s1658, false );}
else if( pc == s473 ) {
s308.s15<s369*>()->s498( this );}
else if( pc == s472 )
s308->s498( this );
else
throw s961.s993( L"unknown iterable type" );
varval = s300->TR().s516( ( (s324*)s308->s494() )->ValType(), s586, s586->s298() );
varval->s1252();
s1491.s380( varval );
s628[1] = varval.s15<s482*>();
if( lambda.s14() ) {
if( lambda->s492() == s473 ) {
lambda.s15<s369*>()->s498( s585 );}
else {
lambda.s15<s559*>()->s2171( true );
lambda = s271::s1011( s300, lambda, this, this, s585->s298(), true );}}
for( size_t n = 0; n < s582.size(); ++n )
s582[n].s15<s559*>()->s2171( true );
s589::s498( s1658, false );
s1252();}
s484 s1396::s495( s481**, size_t  ){
TDException s961( s7::s1366, s1368, past );
s484 s681 = s584;
*s681.s15<s358*>()->s355() = false;
s470 pc = s308->s492();
s9<s324> s586;
if( pc == s474 )
s586 = s308->s495( 0, 0 ).s15<s324*>();
else if( pc == s473 )
s586 = ( (s324*)s308.s15<s369*>()->s375() );
else
s586 = s308.s15<s324*>();
Iterator* s1013 = s586->s312( NULL );
while( 1 ) {
s483 p = s1013->s313();
if( p.s13() )
break;
s628[0] = s1013->Idx();
s628[1] = p.s15<s482*>();
if( lambda.s14() ) {
if( ( ( bool )*(s481*)lambda->s495( 0, 0 ) ) == true ) {
*s681.s15<s358*>()->s355() = true;
break;}}
else {
if( ( ( bool )*p.s15<s481*>() ) == true ) {
*s681.s15<s358*>()->s355() = true;
break;}}}
return s681;}
s2062::s2062( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s2063, s695 ){
s274.assign( l.begin(), l.end() );
s491 = 0;}
void
s2062::s498( const s272* s1658, bool proc ){
s589::s498( s1658, proc );
s483 par = s274[0];
s483 s2072 = par;
s1054 pt = par->s350();
for( size_t n = 1; n < s274.size(); ++n ) {
par = s274[n];
if( !par->s1530( pt ) ) {
if( s2072->s1530( par->s350() ) ) {
pt = par->s350();
s2072 = par;}
else
throw new s16( L"incompatible types in '(first)' function" );}}
s584 = s300->TR().s516( pt, ns, ns->s298() );
s491 = pt;
s1252();}
s484 s2062::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
for( size_t n = 0; n < s274.size(); ++n ) {
s484 s153 = s274[n]->s495( 0, 0 );
if( ( bool )*( (s482*)( s153 ) ) ) {
s584 = s153;
return s584;}}
return s363;}
s1924::s1924( s262* s300, s272* s590, s589* s591, vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1929, s695 ){
for( size_t n = 1; n < l.size(); ++n ) {
vector<s271*>& pl = ( (s559*)l[n] )->s600();
pl.insert( begin( pl ), l[n-1] );}
s274.push_back( l.back() );}
void
s1924::s498( const s272* s1658, bool proc ){
s589::s498( s1658, proc );
s491 = s274[0]->s350();
s584 = s300->TR().s516( s350(), s586, s586->s298() );
s1252();}
s484 s1924::s495( s481**, size_t  ){
return s274[0]->s495( 0, 0 );}
vector<wstring> s2192( { L"where:" } );
s2193::s2193( s262* s300, s272* s590, s589* s591, vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s2194, s695, true ){
TDException s961( s7::CLTDFilter_ctor1, s926, s695, L"wrong '(filter ...)' call" );
if( l.size() > 5 )
throw s961.s993( L"too many arguments" );
if( l.size() < 2 )
throw s961.s993( L"too few arguments" );
s589::s1232( ( vector<s271*>& )l, s2192 );
s2197 = l[0];
size_t bas = 1;
if( l[1]->s350() == s1404 ) {
range = (s383*)l[1];
bas = 2;}
if( l.size() == 1 + bas ) {
s1063 = l[bas];}
if( l.size() == 2 + bas ) {
where = l[1 + bas];}
else if( l.size() == 3 + bas ) {
if( l[bas]->s492() != s1056 || ((s369*)l[bas])->Id() != s1226 )
throw s961.s993( L"expected the 'where:' clause" );
where = l[1 + bas];
s1063 = l[2 + bas];}
s491 = 0;}
void
s2193::s498( const s272* s873, bool proc ){
TDException s961( s7::s2191, s926, s601(), L"wrong parameters to '(filter ...)' call");
if( s2197.s13() )
return;
if( s2197->s492() == s473 ) {
s487 rf = s2197.s15<s369*>();
if( rf->s379().s13() )
rf->s498( s873 );
s978 = rf.s15<s369*>()->s375();}
else if( s2197->s492() == s475 ) {
s483 tmp = s271::s1011( s300, s2197, (s272*)s873, (s589*)s873, s873->s298(), false );
s2197 = tmp;
s978 = s2197->s494();}
else {
s978 = (s481*)s271::s1011( s300, s2197, (s272*)s873, (s589*)s873, s873->s298(), false );}
if( !s300->TR().s1454( s978->s350(), s1501::s1496 ) )
throw s961.s993( L"the type is not rangeable: " + s978->s351() );
if( s978->s492() == s472 ) {}
else if( s978->s492() == s478 ) {}
else
throw s961.s993( L"unsupported container type" );
if( where.s14() ) {
if( where->s492() == s473 )
where.s15<s369*>()->s498( s873 );
else {
s483 tmp = s271::s1011( s300, where, (s272*)this, (s589*)s873, s873->s298(), false );
where = tmp;}}
if( s1063.s14() ) {
if( s1063->s492() == s473 ) {
s1063.s15<s369*>()->s498( s873 );}
else {
if( s1063->s492() != s1235 ) {
s483 tmp = s271::s1011( s300, s1063, (s272*)s873, (s589*)s873, s873->s298(), false );
s1063 = tmp;}}}
s491 = s978->s350();
s584 = s300->TR().s516( s350(), s586, s586->s298() );
s1252();}
s484 s2193::s495( s481**, size_t  ){
std::vector<s483>s855( 1 );
s681 = new s314( s300, s978.s15<s324*>()->ValType(), s586, s601() );
s681->s498( s586, true );
if( s2197->s492() == s474 ) {
s978 = s2197->s495( 0, 0 );}
Iterator* it = s978.s15<s324*>()->s312( NULL );
while( 1 ) {
s483 p = it->s313();
if( p.s13() )
break;
s855[0] = p;
if( where.s14() ) {
where.s15<s832*>()->s594( s855 );
s484 s153 = where->s495( 0, 0 );
if( !(bool)*s153 )
continue;}
if( s1063.s14() ) {
s1063.s15<s832*>()->s594( s855 );
p = s1063->s495( 0, 0 ).s15<s271*>();}
s681->add( p );}
return s681;}
vector<wstring> s951( { L"else", L"elsif" } );
s606::s606( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695,
bool s2160 )
: s589( s300, s590, s591, s591, s563, s230, s695, false, s2160 ){
wstring s705 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s705 + L"too few arguments." );
s274.assign( l.begin(), l.end() );
s589::s1232( ( vector<s271*>& )l, s951 );}
s606::s606( const s606& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), right.s601(), false, right.s2159 ){
for( size_t n = 0; n < right.s618.size(); ++n )
s618.push_back( right.s618[n]->s333( this, s590 ) );
for( size_t n = 0; n < right.s619.size(); ++n ) {
s619.push_back( s577() );
for( size_t m = 0; m < right.s619[n].size(); ++m )
s619.back().push_back( right.s619[n][m]->s333( this, s590 ) );}
s491 = 0;// Types.Null;
}
void s606::s730( bool proc ){
wstring s705 = L"malformed syntax of 'if' statement: ";
s618.push_back( s274[0] );
s619.push_back( s577() );
s619.back().push_back( s274[1] );
if( s274.size() > 2 ) {
size_t n = 2;
while( n < s274.size() ) {
s483 p = s274[n];
s470 pc = s274[n]->s492();
if( pc == s1056 ) {
if( p.s15<s369*>()->Id() == s1215 ) {
if( s274.size() < n + 2 )
throw new s16( s705 + L"incomplete clause" );
s618.push_back( s274[++n] );
s619.push_back( s577() );
s619.back().push_back( s274[n] );}
else if( p.s15<s369*>()->Id() == s1214 ) {
if( s274.size() < n + 1 )
throw new s16( s705 + L"empty clause" );
s619.push_back( s577() );
s619.back().push_back( s274[++n] );}
else
s619.back().push_back( s274[n] );}
else
s619.back().push_back( s274[n] );
n++;}}
if( !proc ) {
size_t s872 = s619[0].size();
s1054 prevPt = s581[s872]->s350();
for( size_t n = 1; n < s619.size(); ++n ) {
s872 += s619[n].size() + 1;
s1054 tmpPt = s581[s872]->s350();
if( tmpPt && tmpPt != Types.No && ( tmpPt != prevPt ) &&
( s581[s872]->s492() == s474 && 
((s589*)s581[s872])->s858() != s2098 ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s491 = prevPt;
if( !s491 ) // e.g. break, continue
s491 = Types.Null;}
else
s491 = Types.Null;}
void
s606::s498( const s272* s1658, bool proc ){
s589::s498( s1658, proc );
s730( proc );
s584 = s300->TR().s516( s350(), s586, s586->s298() );
s581.insert( s581.begin(), s584 );
s1252();}
void s606::s2118( s589* s2042, s272* impl, bool s2160 ){
s589::s2118( s2042 ? s2042 : s585.s15<s589*>(), impl ? impl : s586.s15<s272*>(), s2160 );
for( size_t n = 0; n < s618.size(); ++n )
s618[n]->s2118( this, impl ? impl : s586.s15<s272*>(), s2160 ); // ???DEBUG??? 220908
for( size_t n = 0; n < s619.size(); ++n ) {
for( size_t m = 0; m < s619[n].size(); ++m )
s619[n][m]->s2118( this, impl ? impl : s586.s15<s272*>(), s2160 ); // ???DEBUG??? 220907 V
}}
s484 s606::s495( s481**, size_t ){
size_t idx = string::npos;
for( size_t n = 0; n < s618.size(); ++n ) {
if( ( bool )*( s618[n]->s495( 0, 0 ).s15<s481*>() ) ) {
idx = n;
break;}}
if( idx != string::npos || s619.size() > s618.size() ) {
if( idx == string::npos )
idx = s619.size() - 1;
s484 s681;
s577& el = s619[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s681 = el[n]->s495( 0, 0 );
if( s681->s616() < 0 )
break;}
return s681;}
return s363;}
s833::s833( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, /*s563*/ s2098, s846, s695, false, s2160 )
{
if( l.size() > 1 )
throw new s16( s846 + L": too many arguments" );
s274.assign( l.begin(), l.end() );
const s141& s153 = s601()->s268( s2087 );
if( &s153 != &s265 )
s491 = (s1054)s153.s56();
else
s491 = 0;
size_t pl1 = s695->Src().find( L"yield" );
if( pl1 < s695->Src().find( L"return" ) )
s2233 = true;
else
s2233 = false;}
s833::s833( const s833& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), right.s601() ), s2233( right.s2233 ){}
void
s833::s498( const s272* s2161, bool proc ){
if( s274.size() ) {
if( !s491 )
s491 = s1143;
s589::s498( s2161, false );
s271* p = s274[0];
if( p->s492() == s473 || p->s492() == s1327) {
s491 = p->s350();
s584 = s300->TR().s516( s491, (s272*)s2161, s2161->s298() );}
else {
s584 = s581[1]->s494();
s491 = s584->s350();}}
else {
s584 = s363.s15<s481*>();
s491 = s1143;}
s1252();}
s484 s833::s495( s481** s699, size_t s496 ){
if( s2220 != -1 ) {
s2220 = -1;
return s363;}
s484 s681;
if( s274.size() ) {
if( s274[0]->s492() == s473 || s274[0]->s492() == s1327 || s274[0]->s492() == s474 ) {
s681 = s1599( s699, s496 );
if( s681 )
return s681;
s681 = s581[1];}
else {
s681 = s274[0].s15<s481*>();
s681->s498( this, true );}}
else
s681 = new s362( s300 );
if( s2233 ) {		
s681->s1665( s7::s2265 );}
else
s681->s1665( s7::s860 );
s584 = s681;
return s584;}
s271* s833::s333( s589* s2042, s272* impl ) const{
s833* s681 = new s833( *this, impl ? impl : s586.s15<s272*>(), s2042 );
return s681;}
s890::s890( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s894, s695 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s894 + L": wrong number of arguments" );
if( l.empty() )
s274.push_back( new s344( s300, 0 ) );
else
s274.assign( l.begin(), l.end() );
s491 = s1142;}
void
s890::s498( const s272* s1658, bool proc ){
s589::s498( s1658, false );
if( s274[0]->s350() != s1142 )
throw new s16( L"The parameter to (exit ) must have Integer type." );
s1252();}
s484 s890::s495( s481** s699, size_t s496 ){
s589::s495( s699, s496 );
code = (int)*s581[1];
throw new s16( (uint32_t) code );}
s271* s890::s333( s589* s2042, s272* impl ) const{
return new s890( *this );}
s609::s609( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s259, s695 ), s78( s300 ){
if( l.size() > 2 )
throw new s16( s259 + L": wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.No;
s78.s11();}
s609::s609( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s259, NULL ), s78( s300 ){
s491 = Types.No;
s78.s11();}
void
s609::s498( const s272* s1658, bool proc ){
s78.create( s274 );
s584 = s364.s15<s481*>();
s581.push_back( s274[0]->s494() );
s1252();}
s484 s609::s495( s481** s699, size_t s496 ){
return &s78;}
s610::s610( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s257, s695, true ), 
s76( s7::s459, s300 ), s617( s300 ){
if( l.size() < 2 )
throw new s16( s257 + L"(): wrong numbers of arguments" );
if( l.back()->s492() != s475 ||
((s559*)l.back())->s299() != s258 )
throw new s16( L"the catch clause must be the last statement in the try block" );
s626.s539( s76.s615(), &s617 );
s580.push_back( (s481*)&s617 );
s628.push_back( (s481*)&s617 );
s629.push_back( s369( s76.s615(), s300 ) );
s582.assign( l.begin(), l.end() );}
s610::s610( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s257, NULL, true ), 
s76( s7::s459, s300 ), s617( s300 ){}
void
s610::s498( const s272* s1658, bool proc ){
s589::s498( s1658, proc );
ctch = s582.back().s15<s611*>();
s582.pop_back();
s1252();}
s484 s610::s495( s481** s699, size_t s496 ){
s481* s681 = NULL;
for( size_t n = 0; n < s582.size(); ++n ) {
s681 = s582[n]->s495( s699, s496 );
if( s681->s616() < 0 ) {
if( s681->s616() == s7::s438 ) {
( (s359*)s681 )->s354( &s617 );
s681 = ctch->s495( &s681, 1 );}
break;}}
s584 = s681;
return s681;}
s611::s611( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s258, s695, true, true ){
s582.assign( l.begin(), l.end() );
s491 = Types.Null;}
s611::s611( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s258, NULL ){
s491 = Types.Null;}
s484 s611::s495( s481** s687, size_t s691 ){
s481* s153;
for( size_t n = 0; n < s582.size(); ++n ) {
s153 = s582[n]->s495( s687, s691 );
if( s153->s616() < 0 ) {
return s153;}}
return s363.s15<s481*>();}
s749::s749( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s745, s695 ){}
void
s749::s498( const s272* s1658, bool proc ){}
s484 s749::s495( s481** s699, size_t s496 ){
return 0;}
s1666::s1666( s262* s300, s272* s590, s589* s591, s1668 ptr_,
s559* cs, const s263* s695 )
: s589( s300, s590, s591, s591, s563, L"", s695 ), s1670( ptr_ ){
subject = cs->s600()[0];
s274.assign( cs->s600().begin() + 1, cs->s600().end() );}
void
s1666::s498( const s272* s1658, bool proc ){
s491 = s586->s350();
s589::s498( s1658, proc );
s1252();}
s484 s1666::s495( s481** s699, size_t s496 ){
s485	s1640 = subject->s495( 0, 0 ).s15<s272*>();
return ( *s1640.*s1670)( &s581[0], s496 );}
s1667::s1667( s262* s300, s272* s590, s589* s591, s1669 ptr_,
const vector<s271*>& s1907, const wstring& s672, s1054 s1065, 
const s263* s695, bool _bd )
: s589( s300, s590, s591, s590, s563, s672, s695, false, _bd ), s1670( ptr_ ){
subject = s1907[0];
s274.assign( s1907.begin() + 1, s1907.end() );
s491 = s1065;
ns = s586;}
s1667::s1667( const s1667& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s590, vector<s482*>(), right.s601(), false, right.s2166() ),
s1670( right.s1670 ){
subject = right.subject;}
void
s1667::s498( const s272* s1658, bool proc ){
s483 s697 = subject;
if( s697->s492() == s473 )
s697 = s697.s15<s369*>()->s375();
if( !s491 ) {
if( s697->s492() == s1235 ) {
if( s278 == s7::s1346 || s278 == L"cp" )
s491 = s697->s350();
else
s491 = s697.s15<s832*>()->s1318();}
else {
if( s278 == L"cp" )
s491 = s586->s350();
else
s491 = s697->s350(); }}
s589::s498( s585, proc );
if( 0 && s278 == L"exec" ) {
if( !s697->s1195() )
s697->s498( s1658, proc );}
s1252();}
void s1667::s2118( s589* s2042, s272* impl, bool s2160 ){
s589::s2118( s2042 ? s2042 : s585.s15<s589*>(), impl ? impl : s586.s15<s272*>(), s2160 );
s483 s697 = subject;
s697->s2118( s2042 ? s2042 : s585.s15<s589*>(), impl ? impl : s586.s15<s272*>(), s2160 );}
s484 s1667::s495( s481** s699, size_t s496 ){
s483 s697 = subject;
if( s697->s492() == s473 ) {
s2286 = new s369( *subject.s15<s369*>(), NULL );
s697 = s697.s15<s369*>()->s375();
s2287 = s697;}
else if( s697->s492() == s474 ) {
s484 tmp = s697->s495(0,0);
if( tmp->s616() == s7::s860 )
tmp->s1252();
s697 = tmp.s15<s482*>();}
if( s697->s492() == s1235 ) {
if( s278 == s7::s1346 ) {
auto _subject = s585->s2284();
s832* s681 = new s832( *s697.s15<s832*>(), _subject.s15<s272*>(), 
s585, s2100, s601() );
if( s585->s299() == s233 )
s681->s2181( s2188 );
else
s681->s2181( s2185 );
s681->s498( s586, true );
return s681;}
else if( s278 == L"cp" ) {
return (s481*)s697->s333(0,0);}
else if( s278 == L"exec" ) {
s9<s832> pf;
if( s2286.s14() ) {
s483 tmp = s2286->s375();
if( tmp != s2287 )
s697 = s2287 = tmp;}
if( !s697->s1195() ) {
subject = s697->s333( 0, 0 );
subject->s498( s585, false );
s697 = subject;}
else {
s697.s15<s832*>()->s2210( s585, false );}
pf = s697.s15<s832*>();
if( pf->s2285() ) {
vector<s483> s2112;
for( auto par_ : s274 ) {
s481* par = NULL;
if( par_->s492() == s473 )
par = par_.s15<s369*>()->s375();
else
par = par_.s15<s481*>();
s470 pc = par->s492();
if( pc == s1235 ) {
if( !par->s1195() )
par->s498( s585, false );
s2112.push_back( par );}
else {
if( pc == s474 ) {
if( !par->s1195() )
par->s498( this, false );
else
par->s2118( this, s586, s2166() );}
s2112.push_back( par->s495( 0, 0 ).s15<s482*>() );}}
pf->s2118( pf, s586, s2166() ); 
pf.s15<s832*>()->s594( s2112 );}
s484 s681 = pf->s495( 0, 0 ).s15<s272*>();
if( s681->s616() == s7::s860 || s681->s616() == s7::s2219 ||
s681->s616() == s7::s2265 )
s681->s1665( 0 );
return  s681;}
try {
s697.s15<s832*>()->s594( s274 );}
catch( s16* e ) {
wstring s78 = L"in function '" + s278 + L"'";
if( s601() )
s78 += L" :\n" + TDException::s1897( *s601() );
e->s30( s78 );
throw e;}
return s697->s495( 0, 0 ).s15<s272*>();}
else {
s485 s1640 = subject->s495( 0, 0 ).s15<s272*>();
return ( *s1640.*s1670 )( &s581[0], s496 );}}
s1597::s1597( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1607, s695 ){
s274.assign( l.begin(), l.end() );}
s1597::s1597( const s1597& right )
: s589( right ), cmd( right.cmd ){}
void
s1597::s498( const s272* s1658, bool proc ){
s300->s1997( s2038, s2030 );
s491 = s1143;
s589::s498( s1658, proc );
s1252();}
void s1600( const wstring& cmd, wstring* s1634, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1634 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1634 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s484 s1597::s495( s481** s687, size_t s691 ){
if( s300->s1997( s2038, s2031 ) )
return s584;
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
wstring cmd_ = s581[1]->to_wstring(), s1635;
bool* pdone = ( (s358*)s581[2] )->s355();
wstring *s1634 = NULL;
if( s581.size() > 3 )
s1634 = ( (s357*)s581[3] )->s355();
else
s1634 = &s1635;
if( s817.joinable() ) {
s817.join();}
s817 = thread( s1600, cmd_, s1634, pdone );
return s584;}
s1595::s1595( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1605, s695 ){
if( l.size() != 2 )
throw new s16( s1605 + L"(): wrong numbers of arguments" );
if( l[0]->s492() != s473 )
throw new s16( s1605 + L"(): the first argument must be a reference" );
s274.assign( l.begin(), l.end() );}
s1595::s1595( const s1595& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s591, vector<s482*>(), right.s601(),
false, true ){}
void
s1595::s498( const s272* s1658, bool proc ){
s491 = s1143;
s589::s498( s1658, proc );
s1252();}
s484 s1595::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
s369* dr = s274[0].s15<s369*>();
s272* mod = dr->s379().s15<s272*>();
mod->s1643( dr->s615(), s581[2] );
return s584;}
s1592::s1592( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, s563, s1603, s695,
false, s2160 ){
if( l.size() != 2 )
throw new s16( s1603 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1592::s1592( const s1592& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s591, vector<s482*>(), right.s601(),
false, true ){}
void
s1592::s498( const s272* s1658, bool proc ){
s491 = s1143;
s589::s498( s1658, proc );
s1252();}
s484 s1592::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
s272* dr = (s272*)s581[1];
s1590* ob = (s1590*)s581[2];
try {
dr->s1628( ob );}
catch( s16* e ) {
wstring s78 = L"in function " + s299() + L":\n";
s78 += L"during loading object: " + dr->s1659() +
L":" + dr->s351() + L":";
e->s30( s78 );
throw e;}
return s584;}
s1596::s1596( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1606, s695 ){
if( l.size() != 1 )
throw new s16( s1606 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1596::s1596( const s1596& right )
: s589( right ){}
void
s1596::s498( const s272* s1658, bool proc ){
s491 = s1143;
s589::s498( s1658, proc );
s1252();}
s484 s1596::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
int dr = (int)*(s344*)s581[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s584;}
s1591::s1591( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695,
bool s2160 )
: s589( s300, s590, s591, s591, s563, s1602, s695, true, s2160 ){
if( l.empty() )
throw new s16( s1602 + L"(): too few arguments" );
s274.assign( l.begin(), l.end() );}
s1591::s1591( const s1591& right, s272* s590, s589* s591 )
: s589( right, s590, s591, s591, vector<s482*>(), right.s601(), true, right.s2166() ){
s584 = s300->TR().s516( s491, s586, s586->s298() );}
void
s1591::s498( const s272* s1658, bool proc ){
s491 = Types.String;
s589::s498( s1658, proc );
s1252();}
s484 s1591::s495( s481** s687, size_t s691 ){
if( s274.size() == 1 ) {
wstringstream buf;
s274[0]->s304( &buf );
*s584.s15<s357*>()->s355() = buf.str();}
else {
s481* pd;
if( s274[0]->s492() == s473 ) {
pd = s274[0].s15<s369*>()->s375();
if( pd == s363 )
pd = s586;}
else
pd = s274[0].s15<s481*>();
*s584.s15<s357*>()->s355() = L"";
for( size_t n = 1; n < s274.size(); ++n ) {
*s584.s15<s357*>()->s355() += pd->trace( s274[n]->to_wstring() );
if( n < s274.size() - 1 )
*s584.s15<s357*>()->s355() += L"; ";}}
s584->s1252();
return s584;}
s1870::s1870( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1871, s695 ){
if( l.size() > 2 )
throw new s16( s1871 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s1870::s1870( const s1870& right )
: s589( right ){}
void
s1870::s498( const s272* s1658, bool proc ){
s491 = s1141;
s589::s498( s1658, proc );
s1252();}
s484 s1870::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);
*s584.s15<s356*>()->s355() = dist( mt );
return s584;}
s271* s606::s333( s589* s2042, s272* impl ) const{
s606* s681 = new s606( *this, impl ? impl : s586.s15<s272*>(), s2042 );
return s681;}
s271* s604::s333( s589* s2042, s272* impl ) const{
return new s604( *this );}
s271* s605::s333( s589* s2042, s272* impl ) const{
return new s605( *this );}
s271* s1396::s333( s589* s2042, s272* impl ) const{
return new s1396( *this );}
s271* s2062::s333( s589* s2042, s272* impl ) const{
return new s2062( *this );}
s271* s1924::s333( s589* s2042, s272* impl ) const{
return new s1924( *this );}
s271* s2193::s333( s589* s2042, s272* impl ) const{
return new s2193( *this );}
s271* s609::s333( s589* s2042, s272* impl ) const{
return new s609( *this );}
s271* s610::s333( s589* s2042, s272* impl ) const{
return new s610( *this );}
s271* s611::s333( s589* s2042, s272* impl ) const{
return new s611( *this );}
s271* s749::s333( s589* s2042, s272* impl ) const{
return new s749( *this );}
s271* s1666::s333( s589* s2042, s272* impl ) const{
return new s1666( *this );}
s271* s1667::s333( s589* s2042, s272* impl ) const{
s1667* s681 = new s1667( *this, impl, s2042 );
return s681;}
s271* s1597::s333( s589* s2042, s272* impl ) const{
return new s1597( *this );}
s271* s1595::s333( s589* s2042, s272* impl ) const{
return new s1595( *this, impl, s2042 );}
s271* s1592::s333( s589* s2042, s272* impl ) const{
return new s1592( *this, impl, s2042 );}
s271* s1596::s333( s589* s2042, s272* impl ) const{
return new s1596( *this );}
s271* s1591::s333( s589* s2042, s272* impl ) const{
return new s1591( *this, impl, s2042 );}
s271* s1870::s333( s589* s2042, s272* impl ) const{
return new s1870( *this );}
vector<wstring> s949( { L"to:", L":sign", L":nosign", L":boolalpha", 
L":noboolalpha", L"width:", L"prec:", L"fill:", L":left", L":right", L":internal", 
L":fixed", L":group", L":nl" } );
s607::s607( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, 
const s263* s695, bool s2160 )
: s589( s300, s590, s591, s590, s563, s251, s695, true, s2160 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s695->Src().find( L"lout" );
if( pl1 < s695->Src().find( L"textout" ) )
lout = true;
vector<s271*>tmp( l );
s589::s1232( tmp, s949 );
s274.assign( tmp.begin(), tmp.end() );
s491 = Types.Null;}
s607::s607( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s251, NULL, true, false ), s42( NULL ),
lout( false ){
s491 = Types.Null;}
s607::s607( const s607& right, s272* s590, s589* s591 )
: s589( right, s590, 
s591, s590, vector<s482*>(), right.s601(), true, right.s2166() ), s42( right.s42 ),
lout( right.lout ){
s491 = Types.Null;}
void s607::s498( const s272* s1658, bool proc ){
TDException s961( s7::s1922, s926, s601(), L"malformed '(textout)' function call" );
s589::s498( s1658, proc );
size_t start = 0;
if( s274[0]->s492() == s1056 ) {
if( s274[0].s15<s369*>()->Id() == s1224 ) {
start = 2;
/*s42 = s274[1];
s274.erase( s274.begin(), s274.begin() + 2 );
s581.erase( s581.begin()+1, s581.begin() + 3 );
nlocs = s274.size();
s496 = s581.size();*/
}}
for( size_t n = start; n < s274.size(); ++n ) {
if( s274[n]->s492() == s1056 ) {
int mark = (int)*( s274[n].s15<s369*>() )->s375();
if( mark != s1558 && s274.size() <= n )
s961.s993( L"incorrect usage of formatting marker: " + (s274[n].s15<s369*>())->s615() );
if( mark == s1559 && !s300->TR().s1454(
s274[n + 1]->s350(), s1501::s1538 ) )
s961.s993( L"'width:' formatting marker should have an integer parameter" );
if( mark == s1902 && !s300->TR().s1454(
s274[n + 1]->s350(), s1501::s1538 ) )
s961.s993( L"'fill:' formatting marker should have a char (one symbol string) parameter" );}}
s1252();}
s484 s607::s495( s481** s687, size_t s691 ){
s481* s681 = s1599( s687, s691 );
if( s681 )
return s681;
if( s274[0]->s492() == s1056 ) {
if( s274[0].s15<s369*>()->Id() == s1224 ) {
s42 = s274[1];
s274.erase( s274.begin(), s274.begin() + 2 );
s581.erase( s581.begin()+1, s581.begin() + 3 );
nlocs = s274.size();
s496 = s581.size();}}
s1::s9<Stream> s772;
if( s42.s14() ) {
s470 pc = s42->s492();
if( pc == s474 )
s772 = s42->s495( 0, 0 ).s15<Stream*>();
else if( pc == s473 )
s772 = (Stream*)s42.s15<s369*>()->s375();
else
s772 = s42.s15<Stream*>();}
else
s772 = s1394.s15<Stream*>();
s772->s1555();
uint32_t flags = 0;
for( size_t n = 1; n < s581.size(); ++n ) {
if( s581[n]->s492() == s1056 ) {
int mark = (int)*( (s369*)s581[n] )->s375();
if( mark == s1458 ) {
s772->s1914();}
else if( mark == s1578 ) {
s772->s1912();}
else if( mark == s1952 ) {
s772->s1942();}
else if( mark == s1953 ) {
s772->s1943();}
else if( mark == s1902 ) {
wchar_t c = s581[++n]->to_wstring()[0];
s772->s1898( c );}
else if( mark == s1559 ) {
int w = (int)*s581[++n];
s772->s1556( w );}
else if( mark == s1918 ) {
int pr = (int)*s581[++n];
s772->s1913( pr );}
else if( mark == s1904 ) {
s772->s1900();}
else if( mark == s1905 ) {
s772->s1901();}
else if( mark == s1903 ) {
s772->s1899();}
else if( mark == s1917 ) {
s772->s1911();}
else if( mark == s1557 ) {
flags |= s1547;}
else if( mark == s1558 ) {
s772->s1470( L"" );
n++;}}
else {
s484 s153 = s581[n]->s495( s687, s496 );
s153->s1920( s772 );}}
if( lout )
s772->s1470( L"" );
return s363;}
s271* s607::s333( s589* s2042, s272* impl ) const{
s607* s681 = new s607( *this, impl ? impl : s586.s15<s272*>(), s2042 );
return s681;}
void s607::s2118( s589* s2042, s272* impl, bool s2160 ){
s589::s2118( s2042 ? s2042 : s585.s15<s589*>(), 
impl ? impl : s586.s15<s272*>(), s2160 );
if( s42 )
s42->s2118( s2042 ? s2042 : s585.s15<s589*>(), impl ? impl : s586.s15<s272*>(), s2160 );}
vector<wstring> s1926( { L"from:", L":boolalpha", L":noboolalpha", L"width:", 
L"prec:", L":fixed", L":group", L":nl" } );
s1925::s1925( s262* s300, s272* s590, s589* s591, 
const vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1930, s695 ), source( NULL ),
lin( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s695->Src().find( L"lin" );
if( pl1 < s695->Src().find( L"textin" ) )
lin = true;
vector<s271*>tmp( l );
s589::s1232( tmp, s1926 );
s274.assign( tmp.begin(), tmp.end() );
s491 = Types.Null;}
s1925::s1925( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s1930, NULL ), source( NULL ),
lin( false ){
s491 = Types.Null;}
void s1925::s498( const s272* s1658, bool proc ){
TDException s961( s7::s1921, s926, s601(), L"malformed '(textin)' function call" );
s589::s498( s1658, proc );
if( (s274[0]->s492() == s1056 && s274[0].s15<s369*>()->Id() == s1217 ) ||
(s300->TR().s1454( s274[0]->s350(), s1501::s1494 ))) {
int s373 = 1;
if( s274[0]->s492() == s1056 )
s373 = 2;
source = s274[s373 - 1];
s274.erase( s274.begin(), s274.begin() + s373 );
s581.erase( s581.begin()+1, s581.begin() + s373 + 1 );
nlocs = s274.size();
s496 = s581.size();}
for( size_t n = 0; n < s274.size(); ++n ) {
if( s274[n]->s492() == s1056 ) {
int mark = ( int )*( s274[n].s15<s369*>() )->s375();
if( s274.size() <= n )
s961.s993( L"incorrect usage of formatting marker: " + ( s274[n].s15<s369*>() )->s615() );
if( mark == s1559 && !s300->TR().s1454(
s274[n + 1]->s350(), s1501::s1538 ) )
s961.s993( L"'width:' formatting marker should have an integer parameter" );}}
s1252();}
s484 s1925::s495( s481** s687, size_t s691 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s579 + n ) ) {
s470 pc = ( ( s482* )*( s579 + n ) )->s492();
if( pc == s473 || pc == s1327 )
*( s578 + n + shift ) =
(s481*)( ( s369* )*( s579 + n ) )->s375();
else if( pc == s474 ) {
s974[n + shift] = (s481*)( ( s589* )*( s579 + n ) )->s495( s687, s691 );
*( s578 + n + shift ) = s974[n + shift];}}}
s1::s9<Stream> src;
if( source.s14() ) {
s470 pc = source->s492();
if( pc == s474 )
src = source->s495( 0, 0 ).s15<Stream*>();
else if( pc == s473 )
src = (Stream*)source.s15<s369*>()->s375();
else
src = source.s15<Stream*>();}
else
src = s1392.s15<Stream*>();
src->s1555();
for( size_t n = 1; n < s581.size(); ++n ) {
if( s581[n]->s492() == s1056 ) {
int mark = (int)*( (s369*)s581[n] )->s375();
if( mark == s1952 ) {
src->s1936();}
else if( mark == s1953 ) {
src->s1938();}
else if( mark == s1559 ) {
int w = (int)*s581[++n];
src->s1941( w );}
else if( mark == s1918 ) {
int pr = (int)*s581[++n];
src->s1939( pr );}
else if( mark == s1917 ) {
src->s1937();}}
else {
s484 s153 = s581[n]->s495( s687, s496 );
s153->s1944( src );}}
if( lin )
src->ws();
return s363;}
s271* s1925::s333( s589* s2042, s272* impl ) const{
return new s1925( *this );}
s608::s608( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s256, s695 ){
if( l.size() != 1 )
throw new s16( s256 + L"(): wrong numbers of arguments" );
s274.assign( l.begin(), l.end() );}
s608::s608( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s256, NULL ){}
void s608::s498( const s272* s590, bool proc ){
s300->s1997( s2037, s2030 );
s807::Cont s1269;
wstring ts = Types( s300, Types.Tuple )->s351() + L"<" + 
Types( s300, Types.Bool )->s351() +
L" " + Types( s300, Types.String )->s351() + L">";
s491 = ((s952*)Types( s300, Types.Tuple ))->s1186( ts, s1269 );
s589::s498( s590, proc );}
s484 s608::s495( s481** s699, size_t s496 ){
s952* s681 = s584.s15<s952*>();
s681->clear();
if( s300->s1997( s2037, s2031 ) ) {
s681->s318().push_back( s368 );
s681->s318().push_back( new s357( s300, L"the '(eval)' function is disabled by current security settings" ) );
return s681;}
try {
s484 s153;
if( s274[0]->s492() == s473 )
s153 = s274[0].s15<s369*>()->s375();
else if( s274[0]->s492() == s474 )
s153 = s274[0].s15<s589*>()->s495( NULL, 0 );
else
s153 = s274[0].s15<s481*>();
wstring f = s153->s495( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s483> s906;
s940 ast_ = new s263( f, s601()->Nqj(), (s263*)s601() );
s488 cs = s589::s1110( *ast_, s300, s586, s298(), true );
s906.push_back( cs );
s486 s904 = s589::s598( cs, s300, s586, this, s298(), false );
s904->s498( s586, true );
s484 res1 = s904->s495( 0, 0 );
if( !res1 || res1->s616() != s7::s438 ) {
s681->s318().push_back( s367 );
s681->s318().push_back( new s357( s300, res1 ? res1->to_wstring() : L"" ) );}
else {
s681->s318().push_back( s368 );
s681->s318().push_back( new s357(s300, res1.s15<s359*>()->Msg() ) );}}
else {
vector<wstring> l;
s484 res1 = s300->callFunc( f, l );
s681->s318().push_back( s367 );
s681->s318().push_back( new s357( s300, res1 ? res1->to_wstring() : L"" ) );}}
catch( s16* e ) {
s681->s318().push_back( s368 );
s681->s318().push_back( new s357(s300, e->Msg() ) );}
return s681;}
s271* s608::s333( s589* s2042, s272* impl ) const{
return new s608( *this );}
s1::s9<s262> s613::s900;
s613::s613( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695, bool s2160 )
: s589( s300, s590, s591, s591, s563, s261, s695, true, s2160 ){
if( l.size() != 1 )
throw new s16( s261 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.Null;}
s613::s613( s262* s300 )
: s589( s300, NULL, NULL, NULL, s563, s261, NULL ){
s491 = Types.Null;}
s484 s613::s495( s481** s699, size_t s496 ){
vector<wstring> s905;
for( size_t n = 0; n < s274.size(); ++n ) {
s905.push_back( s274[n]->s495( 0, 0 )->to_wstring() );}
if( s900.s13() ) {
s900 = new s262();
s900->s1885( true );}
else
s900->reset();
s900->s209( s905[0] );
s584 = s900->run( s905 );
return s584;}
s271* s613::s333( s589* s2042, s272* impl ) const{
return new s613( *this );}
s791::s791( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s766, s695 ){
if( l.size() != 1 )
throw new s16( s766 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.Null;}
s484 s791::s495( s481** s699, size_t s496 ){
wstring s194 = s274[0]->s495( s699, s496 )->to_wstring();
s300->s209( s194 );
return s363;}
s271* s791::s333( s589* s2042, s272* impl ) const{
return new s791( *this );}
s769::s769( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l,
const s263* s695 )
: s589( s300, s590, s591, s591, s563, s815, s695 ){
s898 = s590->s298();
if( l.size() != 1 )
throw new s16( s815 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.Null;}
s484 s769::s495( s481** s699, size_t s496 ){
s271* par = s274[0];
wstring s896;
if( par->s492() == s473 )
s896 = ((s369*)par)->s495( 0, 0 )->to_wstring();
else
s896 = par->s495( 0, 0 )->to_wstring();
try {
s272* ob = ((s272*)s300->s639( s898, s898 ));
ob->s553( s896, s898 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s363;}
s271* s769::s333( s589* s2042, s272* impl ) const{
return new s769( *this );}
s1297::s1297( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l,
const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1307, s695 ){
if( l.size() != 1 )
throw new s16( s1307 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.Null;}
s484 s1297::s495( s481** s699, size_t s496 ){
s271* par = s274[0];
wstring s667;
if( par->s492() == s473 )
s667 = ((s369*)par)->s495( 0, 0 )->to_wstring();
else
s667 = par->s495( 0, 0 )->to_wstring();
try {
s300->s1341( s667 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s363;}
s271* s1297::s333( s589* s2042, s272* impl ) const{
return new s1297( *this );}
s1598::s1598( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l,
const s263* s695 )
: s589( s300, s590, s591, s591, s563, s1608, s695 ){
if( l.size() != 1 )
throw new s16( s1608 + L"(): wrong number of arguments" );
s274.assign( l.begin(), l.end() );
s491 = Types.Null;}
s484 s1598::s495( s481** s699, size_t s496 ){
s271* par = s274[0];
wstring s667;
if( par->s492() == s473 )
s667 = ((s369*)par)->s495( 0, 0 )->to_wstring();
else
s667 = par->s495( 0, 0 )->to_wstring();
try {
s300->s1651( s667 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s363;}
s271* s1598::s333( s589* s2042, s272* impl ) const{
return new s1598( *this );}
s1767::~s1767(){
release();}
void s1767::release(){
for( auto i : s865 )
i.second.clear();
s865.clear();}
s1768::s1768( s1767* s1792 ) 
: pdb( s1792 ), fi( s1833), se(s1833) {
ptr = new s1770();}
s1768::~s1768(){
if( ptr ) {
ptr->clear();
delete ptr;}}
const vector<wstring> s1764::s1864 = { L"", L"==", L"<", L">", L"<=", L">=", L"<>" };
s1764::s1764( s262* s300, s272* s586, const std::wstring& s, size_t& pos ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
size_t s69 = s68;
if( s[s68] == L'"' ) {
s4::s994( s, s69, s4::s48 );
field = s.substr( s68+1, s69 - s68 - 2 );}
else {
s69 = s.find_first_of( s4::s48, s68 );
field = s.substr( s68, s69 - s68 );}
s69 = s68 = s.find_first_not_of( s4::s48, s69 );
s4::s994( s, s69, s4::s48 );
wstring s1851 = s.substr( s68, s69 - s68 );
auto s1822  = std::find( s1864.begin(), s1864.end(), s1851 );
if( s1822 == s1864.end() )
throw new s16( L"unknown operation in query string: " + s1851 );
op = (s1764::s1777) std::distance( s1864.begin(), s1822 );
s6::s1755.push_back( s1722.s151 );
s6::s142 nq = new s6::s141( NULL, s, s69, s1722 );
s6::s1755.pop_back( );
s940 s695 = new s263( L"", *nq, NULL );
par = s271::s502( *s695, s300, s586, s586->s298() );
pos = s69 == s.size() ? string::npos : s69;
return;}
void s1764::s498( s272* ns ){
if( par->s492() == s473 ) {
par->s498( ns );}}
void s1764::select( s1767* pdb, s1773& s153 ){
if( par->s492() == s473 )
s347 = par.s15<s369*>()->s375();
else
s347 = par;
pdb->select( field, op, s347.s15<s481*>(), s153 );}
s1765::s1765( s262* s300, s272* s586, const std::wstring& s, size_t& pos, s1766 s1789 )
: s1803( s1789 ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
if( s[s68] == L'(' ) {
s1796( s300, s586, s, ++s68 );}
else
s1796( s300, s586, s, s68 );}
s1765::s1765( const s1765& r )
: s1803( r.s1803 ), subs( r.subs ), s1797( r.s1797 ){}
void s1765::s498( s272* ns ){
for( auto i : subs )
i.s498( ns );
for( auto i : s1797 )
i.s498( ns );}
void s1765::s1796( s262* s300, s272* s586, const std::wstring& s, size_t& pos ){
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
subs.push_back( s1765( s300, s586, s, s68, s1799 ) );}
else if( s[s68] == L'A' || s[s68] == L'a' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1854 = s.substr( s68, pl - s68 );
if( s1854 != L"AND" && s1854 != L"and" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 3;
if( s1803 == s1799 )
s1803 = s1798;
else if( s1803 == s1798 )
(void)0;
else {
if( subs.empty() && s1797.empty() )
throw new s16( L"wrong query syntax: 'AND' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1765( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1797.clear();
s1803 = s1798;}}
else if( s[s68] == L'O' || s[s68] == L'o' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1854 = s.substr( s68, s.size() - pl + 1 );
if( s1854 != L"OR" && s1854 != L"or" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 2;
if( s1803 == s1799 )
s1803 = s1800;
else if( s1803 == s1800 )
(void)0;
else {
if( subs.empty() && s1797.empty() )
throw new s16( L"wrong query syntax: 'OR' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1765( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1797.clear();
s1803 = s1800;}}
else {
s1797.push_back( s1764( s300, s586, s, s68 ) );
if( s68 != string::npos )
++s68;}}}
bool s1788( s816 l, s816 r ){
return ( size_t )&( *l ) < ( size_t )&( *r );}
void s1765::select( s1767* pdb, s1768* s153 ){
s1775 s1816;
vector<s1770> s1848;
s1768 *s1862, *s1861;
for( size_t n = 0; n < s1797.size(); ++n ) {
s1773 s1062;
s1797[n].select( pdb, s1062 );
s1816.insert( s1062 );}
s1862 = pdb->s1804();
s1861 = pdb->s1804();
auto it = begin( s1816 );
if( s1816.size() ) {
if( s1803 == s1798 || s1816.size() == 1 ) {
pdb->intersect( *it, s153 );
s153->sort();}}
for( ++it; it != end( s1816 ); ++it ) {
s1862->clear();
if( s1803 == s1798 ) {
pdb->intersect( *it, s1862 );
s1862->sort();
if( s153->empty() )
s153->swap( s1862 );
else {
std::set_intersection( begin( s153->s318() ), end( s153->s318() ), 
begin( s1862->s318() ), end( s1862->s318() ), 
back_inserter( s1861->s318() ), s1788 );
s153->swap( s1861 );
s1861->clear();}}}
for( size_t n = 0; n < subs.size(); ++n ) {
subs[n].select( pdb, s1862 );
if( s1803 == s1798 ) {
s1862->sort();
if( s153->empty() )
s153->swap( s1862 );
else {
std::set_intersection( begin( s153->s318() ), end( s153->s318() ),
begin( s1862->s318() ), end( s1862->s318() ),
back_inserter( s1861->s318() ), s1788 );
s153->swap( s1861 );
s1861->clear();}}
s1862->clear();}}
vector<wstring> s950( { L"select:", L":select", L":update", L"reduce:", 
L":reduce", L"all", L"as:", L"where:", L"satisfying:", L"using:", L":distinct",	
L"sortby:", L":asc", L":desc", L"limit:", L"set:" } );
struct s842{
size_t idx;
s842( size_t s863 ): idx( s863 ){}
bool operator()( const s484 l, const s484 r ) const{
s484 ld = l.s15<s744*>()[idx];
s484 rd = r.s15<s744*>()[idx];
return ld->operator<( (s481*)&(*rd) );}
};
void s785::s1709( const std::vector<s271*>& l_, TDException& s961 ){
const size_t s1048 = 9;
std::vector<s271*> l( s1048, NULL );
s1698* sqr = new s1698;
s1697* sqp = new s1697;
sqr->verb = s738::s1762;
s369* rf = (s369*)l_[1];
if( rf->Id() == s2056 )
l[1] = new s369( L"all", s300, s1056 );
size_t s979 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s492() == s1056 ) {
s369* rf = (s369*)l_[n];
if( rf->Id() == s1208 ) s979 = 2;
else if( rf->Id() == s1207 ) {
s979 = s1138;
l[1] = l_[n];}
else if( rf->Id() == s1226 ) s979 = 3;
else if( rf->Id() == s1829 ) s979 = 4;
else if( rf->Id() == s1212 ) {
s979 = s1138;
sqr->distinct = 1;}
else if( rf->Id() == s1223 ) {
sqr->s882 = s1698::s831::s822;
s979 = 6;}
else if( rf->Id() == s1209 ) {
if( s979 != 7 )
throw s961.s993( L"the '" + rf->s615() + L"' specifier is misplaced" );
s979 = s1138;
sqr->s882 = s1698::s831::s822;}
else if( rf->Id() == s1211 ) {
if( s979 != 7 )
throw s961.s993( L"the '" + rf->s615() + L"' specifier is misplaced" );
s979 = s1138;
sqr->s882 = s1698::s831::s825;}
else if( rf->Id() == s1221 ) 
s979 = 8;
else
throw s961.s993( L"misplaced query keyword: " + s950[rf->Id()] );}
else
l[s979++] = l_[n];}
s804 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1065 = l[2];
sqp->where = l[3];
sqp->s1852 = l[4];
sqp->s883 = l[6];
sqp->s868 = l[8];}
void s785::s1710( const std::vector<s271*>& l_, TDException& s961 ){
const size_t s1048 = 4;
std::vector<s271*> l( s1048 );
s1708* sqr = new s1708;
s1707* sqp = new s1707;
sqr->verb = s738::s1763;
size_t s979 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s492() == s1056 ) {
s369* rf = (s369*)l_[n];
if( rf->Id() == s1740 ) s979 = 1;
else if( rf->Id() == s1226 ) s979 = 2;
else if( rf->Id() == s1829 ) s979 = 3;
else
throw s961.s993( L"misplaced query keyword: " + s950[rf->Id()] );}
else
l[s979++] = l_[n];}
s804 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->where = l[2];
sqp->s1852 = l[3];
if( sqp->what.s13() )
throw s961.s993( L"the 'UPDATE' query must include 'SET' and `SATISFYING` clauses" );}
void s785::s1987( const std::vector<s271*>& l_, TDException& s961 ){
const size_t s1048 = 6;
std::vector<s271*> l( s1048, NULL );
s1971* sqr = new s1971;
s1970* sqp = new s1970;
sqr->verb = s738::s2044;
s369* rf = (s369*)l_[1];
if( rf->Id() == s2055 )
l[1] = new s369( L"all", s300, s1056 );
size_t s979 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s492() == s1056 ) {
s369* rf = (s369*)l_[n];
if( rf->Id() == s1208 ) s979 = 2;
else if( rf->Id() == s1207 ) {
s979 = s1138;
l[1] = l_[n];}
else if( rf->Id() == s1226 ) s979 = 3;
else if( rf->Id() == s1829 ) s979 = 4;
else if( rf->Id() == s2006 ) s979 = 5;
else
throw s961.s993( L"misplaced query keyword: " + s950[rf->Id()] );}
else
l[s979++] = l_[n];}
s804 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1065 = l[2];
sqp->where = l[3];
sqp->s1852 = l[4];
sqp->s2042 = l[5];}
s785::s785( s262* s300, s272* s590, s589* s591, 
const std::vector<s271*>& l_, const s263* s695 )
: s589( s300, s590, s591, s591, s563, s812, s695 ), s2023( s7::s1967, s300 ),
s727( s7::s460, s300 ), s777( new s272( s300, 0, s478, NULL, NULL, s2185 ) ),
s1845( NULL ){
TDException s961( s7::s1101, s926, s695 );
if( l_.size() < 3 )
throw s961.s993( L"too few arguments." );
s589::s1232( ( vector<s271*>& )l_, s950 );
s626.s539( s727.s615(), s777.s15<s481*>() );
s580.push_back( s777.s15<s481*>() );
s274.push_back( s777.s15<s481*>() );
s628.push_back( s777.s15<s481*>() );
s629.push_back( s369( s727.s615(), s300) );
if( l_[1]->s492() != s1056 )
throw s961.s993( L"the second participant must be a query verb: SELECT, UPDATE, etc." );
s369* rf = (s369*)l_[1];
if( rf->Id() == s1222 || rf->Id() == s2056 )
s1709( l_, s961 );
else if( rf->Id() == s1742 )
s1710( l_, s961 );
else if( rf->Id() == s2005 || rf->Id() == s2055 )
s1987( l_, s961 );}
s785::~s785(){
if( s1845 )
delete s1845;}
s482* s785::s1791( const std::wstring& s ){
size_t pos = 0;
if( s1845 )
delete s1845;
s1845 = new s1765( s300, this, s, pos, s1765::s1799 );
return NULL;}
void s785::s2048( s1767* base, s483 what, vector<wstring>& s889,
std::vector<s486>& s2046, vector<wstring>& s1853 ){
s470 pc = what->s492();
s484 s1750 = what.s15<s481*>();
if( pc == s473 ) {
s487 rf = what.s15<s369*>();
s1750 = rf->s375();}
else if( pc == s1056 ) {
s487 rf = what.s15<s369*>();
if( rf->s615() == L"all" || rf->s615() == L"ALL" ) {
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + 
Types( s300, Types.String )->s351() + L">";
s1054 s1506 = ((s314*)Types( s300, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s1750 = s300->TR().s516( s1506, ns, ns->s298() );
vector<wstring> s2059;
base->s1818( s2059 );
for( auto s : s2059 )
s1750.s15<s314*>()->add( new s357( s300, s ) );}
else
throw new s16( L"fields for selection are not recognized" );}
else if( pc == s472 ) {
(void)0;}
s807 vt = s300->TR().s1006( s1750->s350() );
if( vt.s350() == s1705 || vt.s350() == s1704 ) {
const vector<s483>* v = NULL;
if( vt.s350() == s1705 )
v = &s1750.s15<s314*>()->s318();
else
v = &s1750.s15<s744*>()->s318();
s2046.resize( v->size() );
for( size_t n = 0; n < v->size(); ++n ) {
wstring s852;
auto it = ( *v )[n];
if( it->s492() == s473 ) {
if( it.s15<s369*>()->s379().s13() )
it->s498( this );
s852 = it.s15<s369*>()->s375()->to_wstring();}
else
s852 = it->to_wstring();
size_t s876 = s4::s88.find( s852[0] );
if( s876 != string::npos )
s852 = s4::s52( s852, wstring( 1, s4::s88[s876] ) );
size_t pl = s852.find( L"|=" );
if( s852[0] == L'(' ) {
vector<wstring> s80;
size_t pos = 0;
s263::s288( s852, pos, s80 );
if( s80.size() > 2 )
throw new s16( L"too many arguments in field expression: " + s852 );
s484 s1996 = s300->TR().s516( base->s2000( s80[1] ), ns, s298() );
std::vector<s271*> pl = { s1996 };
s559 cs( s300, s80[0], pl, NULL );
auto s2040 = s589::s598( &cs, s300, ns, (s589*)this, s298(), false );
s2040->s498( this, false );
s2046[n] = s2040;
s889.push_back( s80[1] );}
else if( pl != string::npos ) {
wstring s2126 = s4::s52( s852.substr( 0, pl ), s4::s48 );
wstring s2125 = s4::s52( s852.substr( pl + 2 ), s4::s48 );
s889.push_back( s2126 );
s1853.push_back( s2125 );}
else {
s889.push_back( s852 );
s1853.push_back( s852 );}}}}
void s785::s1711( const s272* s1658, bool proc ){
TDException s961( s7::s914, s926, past );
s470 pc = db->s492();
if( pc == s475 ) {
db = s598( db.s15<s559*>(), s300, s586, this, s298(), false );
db->s498( this );}
else if( pc == s473 )
db.s15<s369*>()->s498( this );
else
throw s961.s993( L"the database must be specified by a name or expression." );
s1697* sqp = qp.s15<s1697*>();
if( sqp->s1065.s14() ) {
sqp->s1065->s498( this );
s807::Cont s1269;
wstring sv = sqp->s1065->s351();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + sv + L">";
s491 = ( (s314*)Types( s300, Types.Vector ) )->s1186( this, ts, s1705, s1269 );}
else {
if( s300->TR().s1454( db->s350(), s1501::s1496 ) )
s491 = db.s15<s324*>()->s350();
else
throw s961.s993( L"the 'AS' clause is missing." );}
s589::s498( s1658, proc );
pc = sqp->what->s492();
if( pc == s475 ) {
sqp->what = s598( sqp->what.s15<s559*>(), s300, s586, this, s298(), false );
sqp->what->s498( this );}
else if( pc == s473 )
sqp->what.s15<s369*>()->s498( this );
else if( pc == s472 || pc == s1056 )
(void)0;
else
throw s961.s993( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s350() != Types.String )
throw s961.s993( L"the 'WHERE' clause must be a string." );
if( s300->TR().s1454( db->s350(), s1501::s1496 ) )
throw s961.s993( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1791( sqp->where->to_wstring() );}
if( sqp->s1852 ) {
pc = sqp->s1852->s492();
if( pc == s475 ) {
sqp->s1852 = s598( sqp->s1852.s15<s559*>(), s300, s586, this, s298(), false );
sqp->s1852.s15<Transd*>()->s498( s1658, false );
s829 s875;
sqp->s1852.s15<Transd*>()->s808( s875 );}
else
throw s961.s993( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s868.s14() ) {
pc = sqp->s868->s492();
if( pc == s475 ) {
sqp->s868 = s598( sqp->s868.s15<s559*>(), s300, s586, this, s298(), false );
sqp->s868->s498( this );}
else if( pc == s473 )
sqp->s868.s15<s369*>()->s498( this );
else if( sqp->s868->s350() != s1142 )
throw s961.s993( L"the limit must be specified by a number, variable or expression." );}}
void s785::s1712( const s272* s1658, bool proc ){
s1707* sqp = qp.s15<s1707*>();
s491 = s1142;
TDException s961( s7::s914, s926, past );
s589::s498( s1658, proc );
s470 pc = db->s492();
if( pc == s475 ) {
db = s598( db.s15<s559*>(), s300, s586, this, s298(), false );
db->s498( this );}
else if( pc == s473 )
db.s15<s369*>()->s498( this );
else
throw s961.s993( L"the database must be specified by a name or expression." );
pc = sqp->what->s492();
if( pc == s475 ) {
sqp->what = s598( sqp->what.s15<s559*>(), s300, s586, this, s298(), false );
sqp->what.s15<Transd*>()->s498( s1658, false );}
else
throw s961.s993( L"the 'SET' clause must be a lambda" );
if( sqp->where ) {
if( sqp->where->s350() != Types.String )
throw s961.s993( L"the 'WHERE' clause must be a string." );
if( s300->TR().s1189( db->s350(), s1501::s1496 ) )
throw s961.s993( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1791( sqp->where->to_wstring() );}
if( sqp->s1852 ) {
pc = sqp->s1852->s492();
if( pc == s475 ) {
sqp->s1852 = s598( sqp->s1852.s15<s559*>(), s300, s586, this, s298(), false );
sqp->s1852.s15<Transd*>()->s498( s1658, false );}
else
throw s961.s993( L"the 'SATISFYING' clause must be a lambda." );}}
void s785::s1989( const s272* s1658, bool proc ){
s1970* sqp = qp.s15<s1970*>();
/*s807::Cont s1269;
wstring sv = sqp->s1065->s351();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s300, Types.Vector )->s351() + L"<" + sv + L">";
s491 = ((s314*)Types( s300, Types.Vector ))->s1186( ts, s1269 );*/
s491 = s1143; // sqp->s1065->s350();
TDException s961( s7::s914, s926, past );
s2023.s377( 0, s2022 );
s2023.s380( (s481*)this );
s589::s498( s1658, proc );
s470 pc = db->s492();
if( pc == s475 ) {
db = s598( db.s15<s559*>(), s300, s586, this, s298(), false );
db->s498( this );}
else if( pc == s473 )
db.s15<s369*>()->s498( this );
else
throw s961.s993( L"the database must be specified by a name or expression." );
pc = sqp->what->s492();
if( pc == s475 ) {
sqp->what = s598( sqp->what.s15<s559*>(), s300, s586, this, s298(), false );
sqp->what->s498( this );}
else if( pc == s473 )
sqp->what.s15<s369*>()->s498( this );
else if( pc == s472 || pc == s1056 )
(void)0;
else
throw s961.s993( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s350() != Types.String )
throw s961.s993( L"the 'WHERE' clause must be a string." );
sqp->where = s1791( sqp->where->to_wstring() );}
if( sqp->s1852 ) {
pc = sqp->s1852->s492();
if( pc == s475 ) {
sqp->s1852 = s598( sqp->s1852.s15<s559*>(), s300, s586, this, s298(), false );
sqp->s1852.s15<Transd*>()->s498( s1658, false );
s829 s875;
sqp->s1852.s15<Transd*>()->s808( s875 );}
else
throw s961.s993( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s2042 ) {
pc = sqp->s2042->s492();
if( pc == s475 ) {
sqp->s2042 = s598( sqp->s2042.s15<s559*>(), s300, s586, this, s298(), false );
sqp->s2042.s15<Transd*>()->s498( s1658, false );
s829 s875;
sqp->s2042.s15<Transd*>()->s808( s875 );}
else
throw s961.s993( L"the 'USING' clause must be a lambda." );}}
void
s785::s498( const s272* s1658, bool proc ){
if( s804->verb == s738::s1762 )
s1711( s1658, proc );
else if( s804->verb == s738::s1763 )
s1712( s1658, proc );
else if( s804->verb == s738::s2044 )
s1989( s1658, proc );
s1252();}
s484 s785::s1717( s481** s274, size_t s496 ){
s1707* sqp = qp.s15<s1707*>();
s484 s681 = s584;
vector<wstring> s889;
vector<wstring> s1853;
s1::s9<s1767> base;
TDException s961( s7::s915, s923, past );
assert( db->s492() == s473 );
s481* s2049 = db.s15<s369*>()->s375();
if( s300->TR().s1454( s2049->s350(), s1501::s1496 ) )
base = new s2047( s300, ns, (s324*)s2049, s601() );
else
base = (s1767*)s2049;
s1::s1279<s1768> dom = base->s1804();
if( s1845 ) {
s1845->select( base, dom );}
else
base->s1855( dom );
s829 s875;	
sqp->what.s15<Transd*>()->s808( s875 );
for( size_t n = 0; n < s875.size(); ++n ) {
s889.push_back( s875[n].first );}
s875.clear();
if( sqp->s1852.s14() ) {
sqp->s1852.s15<Transd*>()->s808( s875 );
if( s875.empty() )
throw s961.s993( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s875.size(); ++n )
s1853.push_back( s875[n].first );}
vector<s483> s874, pls1;
s874.resize( s1853.size() );
pls1.resize( s889.size() );
int s680 = 0;
dom->s1859();
s484 s153 = s367.s15<s481*>();
while( dom->s1821() ) {
s1::s9<s1769> s1843 = dom->s1831();
if( sqp->s1852.s14() ) {
for( size_t n = 0; n < s1853.size(); ++n )
s874[n] = s1843->s754( s1853[n] ).s15<s482*>();
sqp->s1852.s15<Transd*>()->s594( s874 );
s153 = sqp->s1852->s495( 0, 0 );}
if( s153.s14() && (bool)*s153 ) {
for( size_t n = 0; n < s889.size(); ++n )
pls1[n] = s1843->s754( s889[n] ).s15<s482*>();
sqp->what.s15<Transd*>()->s594( pls1 );
s484 s153 = sqp->what->s495( 0, 0 );
++s680;}}
*s584.s15<s344*>()->s355() = s680;
return s584;}
s484 s785::s1716( s481** s274, size_t s496 ){
s1697* sqp = qp.s15<s1697*>();
s1698* sqr = s804.s15<s1698*>();
s484 s681 = s584;
vector<wstring> s889;
vector<s486> s2046;
vector<wstring> s2143;
vector<wstring> s2138;
s1::s9<s1767> base;
size_t s902 = string::npos;
TDException s961( s7::s915, s923, past );
assert( db->s492() == s473 );
s481* s2049 = db.s15<s369*>()->s375();
if( s300->TR().s1454( s2049->s350(), s1501::s1496 ) )
base = new s2047( s300, ns, (s324*)s2049, s601() );
else
base = (s1767*)s2049;
if( sqp->s868.s14() ) {
if( sqp->s868->s492() == s473 ) {
sqr->s868 = ( int )*( (s344*)sqp->s868.s15<s369*>()->s375() );}
else if( sqp->s868->s492() == s474 ) {
sqr->s868 = (int)*sqp->s868->s495( 0, 0 );}
else
sqr->s868 = (int)*sqp->s868;}
if( sqp->s883.s14() ) {
if( sqp->s883->s492() == s473 ) {
sqr->s881 = sqp->s883.s15<s369*>()->s375()->to_wstring();}
else if( sqp->s883->s492() == s474 ) {
sqr->s881 = sqp->s883->s495( 0, 0 )->to_wstring();}
else
sqr->s881 = sqp->s883->to_wstring();}
s2048( base, sqp->what, s889, s2046, s2143 );
s1::s1279<s1768> dom = base->s1804();
if( s1845 ) {
s1845->select( base, dom );}
else
base->s1855( dom );
s829 s875;
if( sqp->s1852.s14() ) {
sqp->s1852.s15<Transd*>()->s808( s875 );
if( s875.empty() )
throw s961.s993( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s875.size(); ++n ) {
for( size_t m = 0; m < s2143.size(); ++m ) {
if( s875[n].first == s2143[m] )
s2138.push_back( s889[m] );}}}
vector<s483> s874;
s874.resize( s2138.size() );
s584.s15<s314*>()->clear();
dom->s1859();
while( dom->s1821() ) {
s1769* s1843 = dom->s1831();
s484 s1794;
if( sqp->s1852.s14() ) {
for( size_t n = 0; n < s2138.size(); ++n )
s874[n] = s1843->s754( s2138[n] ).s15<s482*>();
sqp->s1852.s15<Transd*>()->s594( s874 );
s1794 = sqp->s1852->s495( 0, 0 );}
else
s1794 = s367.s15<s481*>();
if( s1794.s14() && (bool)*s1794 ) {
s1::s9<s744> s888 = new s744( s300, NULL, L"" );
if( s889.empty() )
s1843->s857( *s888 );
else {
for( size_t n = 0; n < s889.size(); ++n )
s888->add( s1843->s754( s889[n] ).s15<s271*>() );}
s888->s1665( s7::s861 );
s584.s15<s314*>()->add( s888 );}}
if( sqr->distinct != -1 ) {
vector<s483>& s893 = s584.s15<s314*>()->s318();
for( size_t n = 0; n < s893.size(); ++n ) {
s483 s892 = s893[n];
size_t m = n + 1;
while( m < s893.size() ) {
s483 _el1 = s893[m];
if( *s892.s15<s744*>() == _el1.s15<s481*>() )
s893.erase( s893.begin() + m );
else
m++;}}}
if( sqr->s882 != -1 ) {
if( s889.size() && sqr->s881.size() ) {
auto it = std::find( s889.begin(), s889.end(), sqr->s881 );
if( it != s889.end() )
s902 = std::distance( s889.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s897;
dom->s1817( s897 );
auto it = std::find( s897.begin(), s897.end(), sqr->s881 );
if( it != s897.end() )
s902 = std::distance( s897.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s891> s895 = new s891;
s895->s901( s902 );
s834 s903( s895 );
s584.s15<s314*>()->sort( sqr->s882 == s1698::s825, &s903 );}
if( sqr->s868 != -1 ) {
s584.s15<s314*>()->s318().resize( sqr->s868 );}
return s681;}
s484 s785::s1992( s481** s274, size_t s496 ){
s1970* sqp = qp.s15<s1970*>();
vector<wstring> s889;
vector<wstring> s2143;
vector<wstring> s2138;
vector<s486> s2046;
TDException s961( s7::s915, s923, past );
s1::s9<s1767> base;
if( db->s492() == s473 ) {
s481* s2049 = db.s15<s369*>()->s375();
if( s300->TR().s1454( s2049->s350(), s1501::s1496 ) )
base = new s2047( s300, ns, (s324*)s2049, s601() );
else
base = (s1767*)s2049;}
else if( db->s492() == s474 ) {
s481* s2049 = db->s495( 0, 0 );
if( s300->TR().s1454( s2049->s350(), s1501::s1496 ) )
base = new s2047( s300, ns, (s324*)s2049, s601() );
else
base = (s1767*)s2049;}
else
throw s961.s993( L"TSD query cannot be performed on a non-TSD object" );
s1772::iterator s1823, s1824;
try {
s2048( base, sqp->what, s889, s2046, s2143 );}
catch( s16* e ) {
throw s961.s993( L"error while parsing WHAT clause: " + e->Msg() );}
s1::s1279<s1768> dom = base->s1804();
if( s1845 ) {
s1845->select( base, dom );}
else
base->s1855( dom );
s829 s875;
if( sqp->s1852.s14() ) {
sqp->s1852.s15<Transd*>()->s808( s875 );
if( s875.empty() )
throw s961.s993( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s875.size(); ++n ) {
for( size_t m = 0; m < s2143.size(); ++m ) {
if( s875[n].first == s2143[m] )
s2138.push_back( s889[m] );}
while( s1823 != s1824 ) {
++s1823;}}}
vector<s483> s2017, s2018;
s2017.resize( s2138.size() );
s829 s2043;
if( sqp->s2042.s14() ) {
sqp->s2042.s15<s832*>()->s808( s2043 );
for( auto p: s2043 )
s2018.push_back( p.second->s333(0,0) );
if( s2018.size() != s889.size() )
throw s961.s993( L"in the REDUCE query the number of selected fields doesn't match "
"the number of parameters to 'using' function");}
else
s2018.resize( s889.size() );
dom->s1859();
s1769* s1843 = dom->s1831();
while( /*dom->s1821()*/ s1843 ) {
s484 s1794;
if( sqp->s1852.s14() ) {
for( size_t n = 0; n < s2138.size(); ++n )
s2017[n] = s1843->s754( s2138[n] ).s15<s482*>();
sqp->s1852.s15<Transd*>()->s594( s2017 );
s1794 = sqp->s1852->s495( 0, 0 );}
else
s1794 = s367.s15<s481*>();
if( s1794.s14() && (bool)*s1794 ) {
if( s889.empty() )
s1843->s857( *s2022 );
else {
for( size_t n = 0; n < s889.size(); ++n ) {
if( s2046[n] ) {
vector<s483> s2016( { s1843->s754( s889[n] ).s15<s482*>() } );
s2046[n]->s594( s2016 );
s2018[n] = s2046[n]->s495( 0, 0 ).s15<s271*>();}
else
s2018[n] = s1843->s754( s889[n] ).s15<s271*>();}}
if( sqp->s2042.s14() ) {
sqp->s2042.s15<Transd*>()->s594( s2018 );
sqp->s2042->s495( 0, 0 );}}
s1843 = dom->s1831();}
return s363; //s2022;
}
s484 s785::s495( s481** s687, size_t s691 ){
if( s804->verb == s738::s1762 )
return s1716( s687, s691 );
else if( s804->verb == s738::s1763 )
return s1717( s687, s691 );
else if( s804->verb == s738::s2044 )
return s1992( s687, s691 );
return NULL;}
bool
s785::s554( const wstring& s672, s369* ref, const wstring& s332, 
bool b ) const{
if( s672 == s7::s1967 ) {
ref->s1333( (s369*)&s2023 );
return true;}
return s589::s554( s672, ref, s332, b ); }
s271* s785::s596( size_t off ){
assert( off == 0 );
if( s2022 )
return s2022;
return (s271*) s2023.s501();}
s271* s785::s333( s589* s2042, s272* impl ) const{
return new s785( *this );}
s770::s770( s262* pass_, s272* s586, const wstring& s762, 
const vector<wstring>& s737, std::vector<s483>& types, const s1706& tbfr )
: s2136( NULL ){
s744 s775( pass_, s586, s762, NULL, tbfr );
s775.s498( s586, true );
vector<s483> s814 = s775.s318();
if( s814.size() > types.size() )
throw new s16( L"The number of record's fields is greater than the number of columns: " + s762 );
for( size_t n = 0; n < s737.size(); ++n ) {
s483 s805;
if( n < s814.size() ) {
if( !s814[n]->s499( types[n].s15< s481*>() ) ) {
if( tbfr.promInts && types[n]->s350() == s1141 && s814[n]->s350() == s1142 )
s814[n] = new s356( pass_, (double)*s814[n].s15<s344*>()->s355() );
else
throw new s16( L"The types of record's fields don't match to the types of columns: " + s762 );}
s805 = s814[n];}
else {
s805 = types[n].s15<s482*>()->s333(0,0);
s805->to_null();}
s756.insert( make_pair( s737[n], s805 ) );
size_t h = s805.s15<s481*>()->s320();
rechash = ( rechash << 1 ) ^ h;}
s2136 = &s756;}
s770::s770( s262* pass_, s1590& obj ){
s2136 = ( std::map<std::wstring, s483>*)&obj.s626.Table();
pobj = &obj;}
size_t s770::s320() const{
return rechash;}
s484 s770::s754( s1890& s76, bool s708 ) const{
auto it = s2136->find( s76 );
if( it == s2136->end() ) {
if( s708 )
throw new s16( L"Record field doesn't exist: " + s76, 
(uint32_t)s16::s17::s23 );
else
return s484();}
return it->second.s15<s481*>();}
void s770::s857( s744& s153 ) const{
for( auto r: *s2136 )
s153.add( r.second );}
void s770::s857( s952& s153 ) const{
for( auto r: *s2136 )
s153.add( r.second );}
void s770::s543( std::vector<std::wstring>& s153 ) const{
for( auto r: *s2136 )
s153.push_back( r.first );}
bool s770::operator==( const s770* p ) const{
return rechash == p->rechash;}
bool s770::operator<( const s770* p ) const{
return rechash < p->rechash;}
wstring s770::to_wstring( uint32_t s1553 ) const{
wstringstream ss;
s304( &ss, 0 );
return ss.str();}
void s770::s304( std::wostream* pd, int s197/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"TSDRecord : " << endl;
for( auto it = begin( *s2136 ); it != end( *s2136 ); ++it ) {
buf << s4::fill_n_ch( L' ', s197 + s417 ) << it->first << L":" << endl;
it->second->s304( pd, s197 + s417 );}}
s806::s806( vector<wstring>& s726, s816 rec ){
for( size_t n = 0; n < s726.size(); ++n ) {
s483 f = rec->s754( s726[n] ).s15<s482*>();
s805.push_back( f );}
for( size_t n = 0; n < s726.size(); ++n ) {
size_t h = s805[n].s15<s481*>()->s320();
s794 = ( s794 << 1 ) ^ h;}}
size_t s806::s320() const{
return s794;}
bool s806::operator==( const s806* p ) const{
return s794 == p->s794;}
bool s806::operator<( const s806* p ) const{
return s794 < p->s794;}
void s806::s304( std::wostream* pd, int s197/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s805.size(); ++n ) {
s805[n]->s304( pd, s197 + s417 );}}
s1782::s1782( s1767* pdb )
: s1768( pdb ), pind(NULL)//, fi1(s1834), se1(s1834)
{}
void s1782::s1856( void* f, void* s ){
pind = (s781*)f;}
void s1782::s1859(){
if( pind )
cur1 = pind->begin();
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1782::s1821(){
if( pind )
return cur1 != pind->end();
else
return cur != se;}
s1769* s1782::s1831(){
if( s1821() ) {
s1769* s681;
if( pind ) {
s681 = cur1->second;
cur1++;}
else {
s681 = *cur;
cur++;}
return s681;}
else
throw new s16( L"TSDBase row iterator is out of range" );}
s648::s648( s262* s300, s272* s586, const s263* ast_ ) 
: s1767( s300, s586, NULL ) {
s491 = Types.TSDBase;}
s648::s648( s262* s300, s272* s586, const wstring& s77, const s263* ast_ )
: s1767( s300, s586, ast_ ){
s497 = s77;
s491 = Types.TSDBase;}
s648::s648( const s648& right, const s263* ast_ )
: s1767( right.s300, right.ns, ast_ ){
s491 = right.s491;}
s481* s648::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return new s648( s300, s586, L"" );}
void s648::s498( const s272*, bool ){
s1252();}
void s648::s348(){
s807::Cont s1269;
wstring ts = Types( s300, Types.Vector )->s351() + L"<" +
Types( s300, Types.String )->s351() + L">";
s1054 s1506 = ( (s314*)Types( s300, Types.Vector ) )->s1186( this, ts, s1705, s1269 );
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s648::s1227, s1784,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"add-file", new s335( L"add-file", &s648::s780, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"add-object", new s335( L"add-object", &s648::s2127, s1143,
{ s1113( { Types.s272 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"set-prim-key", new s335( L"set-prim-key", &s648::s2139, s1143,
{ s1113( { s1506 } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"load-table", new s335( L"load-table", &s648::s796, s1143,
{ s1113( { Types.String } ) }, 1, 1, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s346.insert( make_pair( L"select", new s335( L"select", &s648::s746, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"query", new s335( L"query", &s648::s764, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"erase", new s335( L"erase", &s648::s331, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s648::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"build-index", new s335( L"build-index", &s648::s850, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );}
s481* s648::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s648( s300, s586, L"" );}
inline bool
s648::s499( const s481* s500 ) const{
return ( ((s648*)s500)->s350() == s350() );}
s271* s648::s333( s589* s2042, s272* impl ) const{
return new s648( *this );}
void s648::s354( s271* p ) const{
p = new s648( *this );}
size_t s648::s320() const{
return (size_t)this;}
bool s648::operator==( const s481* p ) const{
return ( this == p );}
bool s648::operator<( const s481* p ) const{
return false;}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s648*)(s482*)*s274)
inline void s648::s1227( s481** s274, size_t s496 ){
s648* ps = (s648*)DR;
s648* s681 = new s648( ps->s300, ps->ns, ps->s601() );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s648::s780( s481** s274, size_t s496 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s648*)DR )->s652( s194 );}
inline void s648::s2127( s481** s274, size_t s496 ){
s1590* ob = (s1590*)PARN( 2 );
( (s648*)DR )->s377( *ob );}
inline void s648::s2139( s481** s274, size_t s496 ){
s314* pv = (s314*)PARN( 2 );
vector<s483>& s2142 = pv->s318();
( (s648*)DR )->s2130.clear();
for( size_t n = 0; n < s2142.size(); ++n )
( (s648*)DR )->s2130.push_back( s2142[n]->to_wstring() );}
inline void s648::s796( s481** s274, size_t s496 ){
s648* dr = ( (s648*)DR );
const wstring& s818 = PARN( 2 )->to_wstring();
s1706 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s496 ) {
s483 par_ = s274[n];
s470 pc = par_->s492();
if( pc == s1056 ) {
s483 par;
s487 rf;
rf = par_.s15<s369*>();
par = par_;
if( par->s350() == Types.No ) {
if( rf->Id() == s1739 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1737 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1735 ) {
if( s496 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1720 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1736 ) {
tbfr.s1683 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1828 ) {
tbfr.s1812 = true;}
else if( rf->Id() == s1738 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"TSDBase::(load-table): unknown parameters" );
++n;}
dr->s712( s818, tbfr );}
inline void s648::s746( s481** s274, size_t s496 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s648*)DR )->s653( s194 );}
inline void s648::s764( s481** s274, size_t s496 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s648*)DR )->s653( s194 );}
inline void s648::s331( s481** s274, size_t s496 ){}
inline void s648::s326( s481** s274, size_t s496 ){}
inline void s648::s329( s481** s274, size_t s496 ){}
inline void s648::s850( s481** s274, size_t s496 ){
wstring s852 = PARN( 2 )->to_wstring();
((s648*)DR)->s849( s852 );}
void s648::s652( const wstring& s194 ){
vector<s9<s143>> s660;
s938 s1044( s194 );
s1044.read( s660, s7::s1097 );
for( size_t m = 0; m < s660.size(); m++ ) {
s143* obj = s660[m];
wstring s656 = s4::s52( s263::s302( *obj, s7::s463 ), 
s48 );
if( s656.empty() )
throw new s16( L"Nameless blocks are forbidden." );
vector<pair<wstring, s142>> s144;
obj->s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].second->s164() != s134 && s144[n].second->s164() != s139 )
throw new s16( L"unrecognized format of field " + s656 +L"::"+s144[n].first );
wstring sobj = s144[n].second->s169();
wstring srel = s144[n].first;
s649.insert( make_pair( s656, make_pair( srel, sobj ) ) );
s650.insert( make_pair( srel, make_pair( s656, sobj ) ) );
s651.insert( make_pair( sobj, make_pair( s656, srel ) ) );}}}
void s648::s377( s1590& obj ){
s816 rec = new s770( s300, obj );
s728 s152 = new s806( s2130, rec );
s751.insert( make_pair( s152, rec ) );}
void s648::s653( s1890& q ){
vector<wstring> qs;
s4::s57( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s649.begin(); it != s649.end(); ++it )
wcout << it->first;}}
void s648::select( s1890& field, s1764::s1777 op, const s481* s1058,
s1773& s153 ){
auto it = s865.find( field );
if( it == s865.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1764::s1837 ) {
s153.pr = it->second.equal_range( (s481*)s1058 );}
else if( op == s1764::s1840 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s481*)s1058 );}
else if( op == s1764::s1841 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s481*)s1058 );}
else if( op == s1764::s1838 ) {
s153.pr.first = it->second.upper_bound( (s481*)s1058 );
s153.pr.second = it->second.end();}
else if( op == s1764::s1841 ) {
s153.pr.first = it->second.lower_bound( (s481*)s1058 );
s153.pr.second = it->second.end();}
else {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}}
s1768* s648::s1804() const{
return new s1782( (s1767*)this );}
void s648::s1855( s1768* s153 ){
s153->s1856( (void*)&s751, (void*)NULL );}
void s648::intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ){
s1772::iterator it = fi1.pr.first;
wstring attr2 = fi2.s970;
s1771 s1801;
while( it != fi1.pr.second ) {
s484 attr2v = it->second->s754( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1801 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1801 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s648::intersect( const s1773& fi, s1768* s153 ){
s1772::iterator it = fi.pr.first;
s1770 s1862;
s1770& s1846 = ((s1782*)s153)->s318();
bool s1810 = s1846.empty();
while( it != fi.pr.second ) {
if( s1810 || std::binary_search( begin( s1846 ), end( s1846 ), it->second, s1788 ) )
s1862.push_back( it->second );
++it;}
s1846.swap( s1862 );}
void s648::s712( const wstring& s818, const s1706& tbfr ){
wstring s737 = tbfr.s1720;
vector<wstring> s809;
vector<wstring> s725;
vector<wstring> s799;
vector<wstring> s819;
if( s737.size() ) {
s4::s57( s737, tbfr.s1683, s809 );
s4::s57( s4::s52( s818, s48 ), tbfr.rowSep, s799 );}
else {
s737 = s818.substr( 0, s818.find( tbfr.rowSep ) );
s4::s57( s4::s52( s818.substr( s737.size() ), s48 ), tbfr.rowSep, s799 );
if( s737.back() == '\r' )
s737.pop_back();
s4::s57( s737, tbfr.s1683, s809 );}
vector<s483> s1758;
vector<s483> types;
if( !s799.empty() ) {
s744 s775( s300, ns, s799[0], NULL, tbfr );
s775.s498( ns, true );
s1758 = s775.s318();}
for( size_t n = 0; n < s809.size(); ++n ) {
vector<wstring> s1719;
s4::s57( s809[n], L":", s1719 );
s940 s1757;
if( s1719.size() == 2 )
s1757 = new s263( s1719[1] + L"()", NULL, NULL );
else if( n < s1758.size() )
s1757 = new s263( s1758[n]->s351() + L"()", NULL, NULL );
else
s1757 = new s263( Types( s300, Types.String )->s351() + L"()", NULL, NULL );
s483 ptype = s300->TR().s516( *s1757, ns, ns->s298() );
types.push_back( ptype );
if( s1719[0][0] != L'@' )
s725.push_back( s1719[0] );
else {
size_t pl = s1719[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1719[0] );
wstring s76 = s1719[0].substr( pl + 1 );
s725.push_back( s76 );
s819.push_back( s76 );}}
if( !s819.empty() ) {
s751.rehash( (size_t) ( s799.size() * 1.1 ) );
for( auto row : s799 ) {
s816 rec = new s770( s300, ns, row, s725, types, tbfr );
s728 s152 = new s806( s819, rec );
s751.insert( make_pair( s152, rec ) );}}}
void s648::s849( const wstring& s852 ){
auto it = s865.find( s852 );
if( it != end( s865 ) )
s865.erase( it );
s1772& s864 = s865.insert( make_pair( s852, s1772() ) ).first->second;
for( auto it: s751 ) {
s484 pd;
try {
pd = it.second->s754( s852 );}
catch( ... ) {}
if( pd.s14() )
s864.insert( make_pair( pd, it.second ) );}}
bool s648::s1995( s1890& s970 ) const{
assert(0);
return false;}
s1054 s648::s2000( s1890& s852 ) const{
assert( 0 );
return 0;}
void s648::s1818( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
wstring s648::to_wstring( uint32_t s1553 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s648::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"TSDBase : " << endl;
for( auto it = begin( s751 ); it != end( s751 ); ++it ) {
it->first->s304( pd, s197 + s417 );
it->second.s15<s770*>()->s304( pd, s197 + s417 );}}
s1770 s1832 = { new s1786( vector<s484>( {s484()} ), NULL ) };
s1770::iterator s1833 = s1832.begin();
s1786::s1786( const std::vector<s484>& v, s1787* s1793 )
: s1847( v ), s1844( s1793 ){}
s1786::~s1786(){
s1847.clear();}
const s1786::s1779& s1786::s2001() const{
return s1847;}
s484 s1786::s754( s1890& s76, bool s708 ) const{
return s1847[s1844->s1819( s76 )];}
void s1786::s857( s744& s153 ) const{
for( auto r : s1847 )
s153.add( r );}
void s1786::s857( s952& s153 ) const{
for( auto r : s1847 )
s153.add( r );}
void s1786::s543( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
size_t s1786::s320() const{
return rechash;}
s1785::s1785( const s1785& r )
: s1768( r.pdb ){}
s1785::s1785( s1767* pdb )
: s1768( pdb ){}
s1785::~s1785(){}
void s1785::s1856( void* f, void* s ){
fi = *( s1770::iterator* )f;
se = *( s1770::iterator* )s;}
void s1785::s1859(){
if( *fi != *s1833 )
cur = fi;
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1785::s1821(){
return (cur != se);}
s1769* s1785::s1831(){
if( s1821() ) {
s1769* s681 = *cur;
cur++;
return s681;}
else
throw new s16( L"Table row iterator is out of range" );}
void s1785::s1817( std::vector<std::wstring>& s153 ){
((s1787*)pdb)->s1818( s153 );}
s1787::s1787( s262* s300, s272* s586, const s263* ast_ )
: s1767( s300, s586, ast_ ){
s491 = Types.Table;
s2027 = 0;}
s1787::s1787( s262* s300, s272* s586, s1890& s77, const s263* ast_ )
: s1767( s300, s586, ast_ ){
s497 = s77;
s491 = Types.Table;
s2027 = 0;}
s1787::s1787( const s1787& right, const s263* ast_ )
: s1767( right.s300, right.ns, ast_ ){
s491 = right.s491;
s2027 = 0;}
s1787::~s1787(){
release();}
s481* 
s1787::s352( const s263& s695, s272* s586, s1890& s332 ) const{
return new s1787( s300, s586, &s695 );}
void s1787::s498( const s272*, bool ){
s1252();}
void s1787::s348(){
s346.insert( make_pair( s7::s1346, new s335( s7::s1346, &s1787::s1227, s1783,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"load-table", new s335( L"load-table", &s1787::s796, s1143,
{ s1113( { Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls", L":firstRowColNames"} ) ) );
s346.insert( make_pair( L"select", new s335( L"select", &s1787::s746, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"query", new s335( L"query", &s1787::s764, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.insert( make_pair( L"erase", new s335( L"erase", &s1787::s331, s1143,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"size", new s335( L"size", &s1787::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"get-row", new s335( L"get-row", &s1787::s2003, 0,
{ s1113( { s1501::s1538 } ) }, 0, 0 ) ) );
s346.insert( make_pair( L"num-cols", new s335( L"num-cols", &s1787::s2011, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"num-rows", new s335( L"num-rows", &s1787::s2012, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( make_pair( L"build-index", new s335( L"build-index", &s1787::s850, s1143,
{ s1113( { Types.String } ) }, 1, 1 ) ) );
s346.equal_range( L"get-row" ).first->second->s1251( true );}
s1054 s1787::s1179( const wstring& s1541, const vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"get-row" )
s681 = s1704;
else
return s334::s1179( s1541, l );
return s681;}
s481* s1787::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s1787( s300, s586, L"" );}
inline bool
s1787::s499( const s481* s500 ) const{
return ( ((s1787*)s500)->s350() == s350() );}
s271* s1787::s333( s589* s2042, s272* impl ) const{
return new s1787( *this );}
void s1787::s354( s271* p ) const{
p = new s1787( *this );}
size_t s1787::s320() const{
return (size_t)this;}
bool s1787::operator==( const s481* p ) const{
return ( this == p );}
bool s1787::operator<( const s481* p ) const{
return false;}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
#undef s692
#define s692 ((s1787*)(s482*)*s274)
inline void s1787::s1227( s481** s274, size_t s496 ){
s1787* ps = (s1787*)DR;
s1787* s681 = new s1787( ps->s300, ps->ns, ps->s601() );
s681->s498( ps->ns, true );
*s274 = (s481*)s681;}
inline void s1787::s796( s481** s274, size_t s496 ){
s1787* dr = ( (s1787*)DR );
const wstring& s818 = ((s357*)PARN( 2 ))->s318();
s1706 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s496 ) {
s483 par = s274[n];
s470 pc = par->s492();
if( pc == s1056 ) {
s487 rf = par.s15<s369*>();
if( par->s350() == Types.No ) {
if( rf->Id() == s1739 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1737 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1735 ) {
if( s496 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1720 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1736 ) {
tbfr.s1683 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1828 ) {
tbfr.s1812 = true;}
else if( rf->Id() == s1738 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2004 ) {
tbfr.s1999 = true;}}}
else
throw new s16( L"Table::(load-table): unknown parameters" );
++n;}
dr->s712( s818, tbfr );}
inline void s1787::s746( s481** s274, size_t s496 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1787*)DR )->s653( s194 );}
inline void s1787::s764( s481** s274, size_t s496 ){
wstring s194 = PARN( 2 )->to_wstring();
( (s1787*)DR )->s653( s194 );}
inline void s1787::s331( s481** s274, size_t s496 ){}
inline void s1787::s2003( s481** s274, size_t s496 ){
s1787* pt = (s1787*)DR;
int n = (int)*PARN( 2 );
const s1786::s1779& row = pt->s2045[n].s15<s1786*>()->s2001();
vector<s271*> v;
for( auto f : row )
v.push_back( f->s333(0,0) );
*s274 = new s952( pt->s300, pt->ns, v, NULL );
( *s274 )->s498( pt->ns );}
inline void s1787::s326( s481** s274, size_t s496 ){}
inline void s1787::s2011( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s1787*)DR )->s800.size();}
inline void s1787::s2012( s481** s274, size_t s496 ){
*( (s344*)*s274 )->s355() = (int)( (s1787*)DR )->rows.size();}
inline void s1787::s850( s481** s274, size_t s496 ){
wstring s852 = PARN( 2 )->to_wstring();
((s1787*)DR)->s849( s852 );}
void s1787::select( const std::wstring& field, s1764::s1777 op, const s481* s1058,
s1773& s153 ){
auto it = s865.find( field );
if( it == s865.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1764::s1837 ) {
s153.pr = it->second.equal_range( (s481*)s1058 );}
else if( op == s1764::s1840 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.lower_bound( (s481*)s1058 );}
else if( op == s1764::s1841 ) {
s153.pr.first = it->second.begin();
s153.pr.second = it->second.upper_bound( (s481*)s1058 );}
else if( op == s1764::s1838 ) {
s153.pr.first = it->second.upper_bound( (s481*)s1058 );
s153.pr.second = it->second.end();}
else if( op == s1764::s1841 ) {
s153.pr.first = it->second.lower_bound( (s481*)s1058 );
s153.pr.second = it->second.end();}
else {
assert( 0 );
s153.pr.first = it->second.begin();
s153.pr.second = it->second.end();}
s153.s970 = field;
s153.dist = std::distance( s153.pr.first, s153.pr.second );}
void s1787::intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ){
s1772::iterator it = fi1.pr.first;
wstring attr2 = fi2.s970;
s1771 s1801;
while( it != fi1.pr.second ) {
s484 attr2v = it->second->s754( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1801 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1801 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s153.push_back( it->second );
++lb2;}}
++it;}}
void s1787::intersect( const s1773& fi, s1768* s153 ){
s1772::iterator it = fi.pr.first;
s1770 s1862;
s1770& s1846 = ((s1785*)s153)->s318();
bool s1810 = s1846.empty();
while( it != fi.pr.second ) {
if( s1810 || std::binary_search( begin( s1846 ), end( s1846 ), it->second, s1788 ) )
s1862.push_back( it->second );
++it;}
s1846.swap( s1862 );}
void s1787::s1855( s1768* s153 ){
s1770::iterator f = begin( rows );
s1770::iterator s = end( rows );
s153->s1856( (void*)&f, (void*)&s );}
size_t s1986( const std::wstring& s818, const s1706& tbfr ){
size_t s681 = 0, st = 0, en = 0, n;
while( en != string::npos ) {
en = s818.find( tbfr.rowSep, st );
n = s4::count( s818, tbfr.s1683, st, en, true );
if( s681 < n ) s681 = n;
st = en + 1;}
return s681;}
void s1787::s712( s1890& s818, const s1706& tbfr ){
wstring s737 = tbfr.s1720;
vector<wstring> s809;
vector<wstring> s819;
size_t pl = 0;
if( s737.size() ) {
s4::s57( s737, tbfr.s1683, s809 );}
else if( tbfr.s1999 ){
pl = s818.find( tbfr.rowSep );
s737 = s818.substr( 0, pl );
if( s737.back() == '\r' )
s737.pop_back();
s4::s57( s737, tbfr.s1683, s809 );
++pl;}
else {
size_t s2007 = s1986( s818, tbfr );
for( size_t n = 0; n < s2007; ++n )
s809.push_back( std::to_wstring( n ) );}
vector<s484> types;
vector<s483> s1758;
if( 0 /*|| !s799.empty()*/ ) {
++pl;
wstring first = s818.substr( pl, s818.find( tbfr.rowSep, pl ) - pl );
s744 s775( s300, ns, first, NULL, tbfr );
s775.s498( ns, true );
s1758 = s775.s318();}
for( size_t n = 0; n < s809.size(); ++n ) {
vector<wstring> s1719;
s4::s57( s809[n], L":", s1719 );
s940 s1757;
s484 ptype;
if( s1719.size() == 2 )
s1757 = new s263( s1719[1] + L"()", NULL, NULL );
else
s1757 = new s263( Types( s300, Types.String )->s351() + L"()", NULL, NULL );
ptype = s300->TR().s516( *s1757, ns, ns->s298() );
types.push_back( ptype );
if( s1719[0][0] != L'@' )
s800.push_back( s1719[0] );
else {
size_t pl = s1719[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1719[0] );
wstring s76 = s1719[0].substr( pl + 1 );
s800.push_back( s76 );}
s1820[s800.back()] = s800.size() - 1;}
s807::Cont s1269;
wstring ts = Types( s300, Types.Tuple )->s351() + L"<"; 
for( size_t n = 0; n < types.size(); ++n ) {
ts += types[n]->s351();
if( n < types.size() - 1 )
ts += L" ";}
ts += L">";
s2027 = ( (s952*)Types( s300, Types.Tuple ) )->s1186( ts, s1269 );
using namespace chrono;
size_t s1805 = pl, /*s69,*/ s1850, s1806, s1813;
vector<s484> s1815( types.size() );
s940 s208 = new s263( L"", L"" );
rows.clear();
s2045.clear();
while( s1805 != string::npos ) {
s1850 = s1805;
s4::s994( s818, s1850, tbfr.rowSep );
wstring s1808 = s818.substr( s1805, s1850 - s1805 );
s1813 = s1806 = 0;
for( size_t n = 0; n < types.size(); ++n ) {
s1813 = s1806;
s4::s994( s1808, s1813, tbfr.s1683 );
if( types[n].s14() ) {
s208->s294( L"" );
s208->s1754( s1808.substr( s1806, s1813 - s1806 ) );
if( types[n]->s350() == Types.String && ( s208->s291().front() != L'"' ||
s208->s291().back() != L'"' ) ) {
wstring dqu = L"\"\"";
s208->s1754( dqu.insert( 1, s4::s1814(  s4::s52( s208->s291(), s4::s48 ) , L'"' )));}
s1815[n] = types[n]->s352( *s208, ns, ns->s298() );}
else {
s1815[n] = s363.s15<s481*>();}
s1806 = s1813 + 1;
if( s1813 == string::npos )
break;}
s1805 = s1850 + 1;
s1769* s1795 = new s1786( s1815, this );
rows.push_back( s1795 );
if( s1850 == string::npos || s1805 == s818.size() )
break;}
s2045.assign( rows.begin(), rows.end() );}
void s1787::s849( s1890& s852 ){
auto it = s865.find( s852 );
if( it != end( s865 ) )
s865.erase( it );
s1772& s864 = s865.insert( make_pair( s852, s1772() ) ).first->second;
for( auto it: rows ) {
s484 pd = it->s754( s852 );
if( pd.s14() )
s864.insert( make_pair( pd, it ) );}}
bool s1787::s1995( s1890& s970 ) const{
if( s1820.find( s970 ) != end( s1820 ) )
return true;
return false;}
s1054 s1787::s2000( s1890& s852 ) const{
if( !s2027 )
throw new s16( L"table is empty" );
const s807& s985 = s300->TR().s1006( s2027 );
s1054 s2028 = s985.s350( (1 + s1819( s852 )) * 2 );
return s2028;}
void s1787::release(){
s1767::release();
rows.clear();}
s1768* s1787::s1804() const{
return new s1785( (s1767*)this );}
size_t s1787::s1819( s1890& s1802 ) const{
auto s681 = s1820.find( s1802 );
if( s681 == s1820.end() )
throw new s16( L"table field does not exist: " + s1802 );
return s681->second;}
wstring s1787::to_wstring( uint32_t s1553 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s1787::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Table : " << endl;
for( auto it = begin( rows ); it != end( rows ); ++it ) {}}
s2061::s2061( s484 d )
: rec( d ){}
s2061::~s2061(){}
s484 s2061::s754( s1890& s76, bool s708 ) const{
return rec;}
void s2061::s857( s744& s153 ) const{
s153.add( rec.s15<s271*>() );}
void s2061::s857( s952& s153 ) const{
s153.add( rec.s15<s271*>() );}
void s2061::s543( std::vector<std::wstring>& s153 ) const{
assert( 0 );}
size_t s2061::s320() const{
return rec->s320();}
s2060::s2060( const s2060& r )
: s1768( r.pdb ){}
s2060::s2060( s1767* pdb )
: s1768( pdb ){}
s2060::~s2060(){}
void s2060::s1856( void* f, void* s ){
s2068 = (s324*)f;
started = false;}
void s2060::s1859(){
started = true;
s2066 = s2068->s312( NULL );}
bool s2060::s1821(){
return !s2066->s1964();}
s1769* s2060::s1831(){
if( s1821() ) {
s1769* s681 = NULL;
if( 0 && started ) {
s681 = new s2061( (s481*)s2066->s955() );
started = false;}
else {
s481* s2067 = (s481*)s2066->s313();
if( s2067 )
s681 = new s2061( s2067 );}
return s681;}
else
return NULL;}
void s2060::s1817( std::vector<std::wstring>& s153 ){
((s2047*)pdb)->s1818( s153 );}
s2047::s2047( s262* s300, s272* s586, s324* pv_, const s263* ast_ )
: s1767( s300, s586, ast_ ), s2065( L"col1"), pv( pv_ ){
s491 = pv->s350();
s2027 = pv->ValType();
s2053 = false;}
s2047::s2047( const s2047& r )
: s1767( r ), pv( r.pv ){
s491 = r.s350();
s2027 = r.s2027;
s2053 = false;
s2065 = r.s2065;}
s2047::~s2047(){
release();}
s481* 
s2047::s352( const s263& s695, s272* s586, s1890& s332 ) const{
assert(0);
return 0;}
void s2047::s498( const s272*, bool ){
s1252();}
s481* s2047::s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const{
return new s2047( s300, s586 );}
void s2047::s348(){
assert(0);}
s271* s2047::s333( s589* s2042, s272* impl ) const{
return new s2047( *this );}
void s2047::s354( s271* p ) const{
p = new s2047( *this );}
size_t s2047::s320() const{
return (size_t)this;}
bool s2047::operator==( const s481* p ) const{
return ( this == p );}
bool s2047::operator<( const s481* p ) const{
return false;}
void s2047::select( const std::wstring& field, s1764::s1777 op, const s481* s1058,
s1773& s153 ){
assert( 0 );
s153.s970 = field;
s153.dist = 0;}
void s2047::intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ){
assert( 0 );}
void s2047::intersect( const s1773& fi, s1768* s153 ){
assert( 0 );}
void s2047::s1855( s1768* s153 ){
s153->s1856( (void*)pv, NULL );}
void s2047::s849( s1890& s852 ){
assert( 0 );}
bool s2047::s1995( s1890& s970 ) const{
if( s2065 == s970 )
return true;
return false;}
s1054 s2047::s2000( s1890& s852 ) const{
if( !s2027 )
throw new s16( L"table is empty" );
return s2027;
const s807& s985 = s300->TR().s1006( s2027 );
s1054 s2028 = s985.s350( (1 + s1819( s852 )) * 2 );
return s2028;}
void s2047::release(){
s1767::release();}
s1768* s2047::s1804() const{
return new s2060( (s1767*)this );}
size_t s2047::s1819( s1890& s1802 ) const{
if( s2065 != s1802 )
throw new s16( L"dataset doesn't contain the attribute: '" + s1802 + L"'" );
return 0;}
wstring s2047::to_wstring( uint32_t s1553 ) const{
basic_stringstream<wchar_t> ss;
s304( &ss, 0 );
return ss.str();}
void s2047::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s197 ) << L"Dataset : " << endl;
pv->s304( pd, s197 );}
vector<wstring> s1361 /*= { L"", s1416, s243, s1417, 
s258, s256, 
s894, s2063, s260, s230, s766, 
s815, s252, s244, s846,
s261, s753, s251, s259, 
s257, s812, s1307, s255, 
s233 }*/;
vector<int> BIFuncs1v = {	0, 
0, 0, s1420, s1421, 0, 
0, s1423, s2195, 0, s1424, s1425, 0, 
0,	s1427, s1611, 0, 0, 0,
s1430, s2216, 0, 0, 0, s1432, 
s1872, s1613, 0, 0, s1433, 
s1551, s1434, s1435, s1436,	0, 
0, s1438, s1439
};
std::map<std::wstring, int> s1360;
s1972::s1972(){
reset();}
vector<wstring> s1972::s2034;
void s1972::reset(){
memset( s2026, 0, s1969 * sizeof( s1984 ) );
if( s2034.empty() )
s2034 = { s7::s1979, s7::s1982, s7::s1981,
s7::s1980 };}
s1984 s1972::s1988( s1890& s2024 ){
auto it = std::find( begin(s2034), end(s2034), s2024 );
size_t n = std::distance( begin(s2034), it );
if( n == string::npos )
throw new s16( L"unrecognized restriction switch: " + s2024 );
return (s1984)n;}
void s1972::s2041( const s143& s133 ){
for( size_t n = 0; n < s1969; ++n )
if( s2026[n] )
throw new s16( L"Assembly security restrictions have already been set" );
vector<pair<wstring, s142>> s144;
s133.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].first == s7::s1974 )
s2026[s2035] = s1988( s144[n].second->s169() );
else if( s144[n].first == s7::s1975 )
s2026[s2036] = s1988( s144[n].second->s169() );
else if( s144[n].first == s7::s1976 )
s2026[s2037] = s1988( s144[n].second->s169() );
else if( s144[n].first == s7::s1977 )
s2026[s2038] = s1988( s144[n].second->s169() );
else if( s144[n].first == s7::s1973 ) {
s2026[s2035] = s1988( s144[n].second->s169() );
s2026[s2036] = s1988( s144[n].second->s169() );}
else if( s144[n].first == s7::s1978 ) {
for( size_t n = 1; n < s1969; ++n )
s2026[n] = s1988( s144[n].second->s169() );}}}
void s1972::s1998( const std::vector<s1983>* s2019, s1984 sw ) const{
for( size_t n = 0; n < s2019->size(); ++n ) {
s1983 si = (*s2019)[n];
if( s2026[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );}}
bool s1972::s1997( s1983 si, s1984 sw ) const{
if( s2026[si] == s2033 )
return true;
if( s2026[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );
return false;}
s262::s262()
: s272( this, 0, s471, NULL, this, s2183 ), s695( s227, L"", L"global" ),
s200( L"" ), s203( this ), s1309( false ){}
s262::~s262(){
for( auto it = s2255.begin(); it != s2255.end(); ++it ) {
it->second->clear();
delete it->second;}
s2255.clear();}
void s262::reset(){
s626.reset();
s203.s784();
s199.clear();
s695.reset();
s1309 = false;
s2025.reset();}
void s262::s1885( bool soft /*=false*/ )
{
s334::s778( this, soft );
s203.s290();
s206[s7::s432] = s365.s15<s481*>();
s206[s7::s431] = s366.s15<s481*>();
s845( s7::s434, s367.s15<s481*>() );
s845( s7::s435, s368.s15<s481*>() );
s845( s7::s826, s363.s15<s481*>() );
s1394 = new s1393( this, this );
s1392 = new s1391( this, this );
s845( s7::s1380, s1392.s15<s481*>() );
s845( s7::s1381, s1394.s15<s481*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s357* s1462 = new s357( this, os, this );
s845( s7::s1362, s1462 );
if( s1360.empty() ) {
s1361 = { L"", 
s1416, s243, s1417, s258, s1602, 
s256, s894, s2194, s2063, s260, s230, 
s766,
s815, s252, s1603, s244,s1929,
s1604, 
s846,s2214,s261, s1606, s1607, s753, 
s1871, s1605, s1930, s1928, s251, 
s1550,s259, s257, s812, s1608, 
s1307, s255, s233 };
for( size_t n = 1; n < s1361.size(); ++n )
s1360[s1361[n]] = (int)n;}}
static s6::s1681 s1756( L".", L",", true, true, true );
void s262::s202( s1890& s655, s716& s153 ) {
vector<s9<s143>> s660;
s941 s1044 = new s938( s655, true, s1756 );
s1044->read( s660, s7::s416 );
for( size_t n = 0; n < s660.size(); n++ ) {
wstring s656 = s263::s302( *s660[n], s7::s463 );
if( s656 == s7::s451 ) {
if( ( *s660[n] ).s156( s7::s465 ) ) {
const vector<s142>& s162 = ( *s660[n] ).s158( s7::s465 )->s167();
for( size_t n = 0; n < s162.size(); n++ )
s153.s661.push_back( s162[n]->s169() );}
if( ( *s660[n] ).s156( s7::s464 ) )
s153.entry = ( *s660[n] ).s158( s7::s464 )->s851();
if( ( *s660[n] ).s156( s7::s1968 ) ) {
const s143& s133 = (*s660[n]).s158( s7::s1968 )->s166();
s2025.s2041( s133 );}}}
if( s153.s661.empty() )
s153.s661.push_back( s655 );}
wstring s711( s1890& s747, s1890& s750 ){
if( s3::s718( s750 ) )
return s750;
if( !s3::s718( s747 ) )
throw new s16( L"The root path is not absolute: " + s747 );
if( s750.empty() )
return s747;
wstring path = s750;
wstring root = s747;
s4::s61( path );
s4::s61( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s16( L"The relative path '" + s750 + L"' is incompatible with the root '" + s747 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s16( L"The relative path '" + s750 + L"' is incompatible with the root '" + s747 + L"'." );}
return root + path;}
void s262::s213( s1890& s194, const s143& obj ){
const vector<s142>& s723 = ( obj ).s158( s7::s468 )->s167();
const vector<s142>& packs = ( obj ).s158( s7::s733 )->s167();
vector<wstring> s41;
wstring s735 = s194.substr( 0, s194.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s723.size(); n++ )
s41.push_back( s711( s735, s723[n]->s169() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s169();
if( req.rfind( s7::s455 ) == req.size() - s7::s455.size() ) {
if( std::find( s199.begin(), s199.end(), req ) == s199.end() )
s199.push_back( s711( s735, req ) );}
else {
vector<wstring> matches;
for( size_t n = 0; n < s41.size(); n++ ) {
wstring match;
wstring _dir = s41[n];
s4::s61( _dir );
if( s3::s31( _dir, req + s7::s455, match ) )
matches.push_back( match );}
if( matches.empty() ) {
throw new s16( L"The required library '" + req + L"' is not found." );}
else if( matches.size() > 1 ) {
wstring s732;
s4::s289( matches, L",\n", s732 );
throw new s16( L"The required library's name '" + req + L"' is ambiguous: \n" + s732 );}
if( std::find( s199.begin(), s199.end(), matches[0] ) == s199.end() )
s199.push_back( matches[0] );}}}
void s262::s2158( const s143& obj ){
vector<pair<wstring, s142>> s144;
obj.s160( s144 );
for( size_t n = 0; n < s144.size(); ++n ) {
if( s144[n].first == s7::s463 )
continue;
s940 past = new s263( s144[n].first, *s144[n].second, NULL );
s481* dv = (s481*)s271::s502( *past, s300, (s272*)this, L"::" );
dv->s1252();}}
void s671( s262* s300, s263& s695, s480& s657,
s621& cl, s620& cnl, s622& al ){
s263::s275& s696 = s695.s293();
s263::s275::iterator it = s696.begin();
s534 am = s508;
for( ; it != s696.end(); ++it ) {
s470 pc = s477;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s684;
s4::s57( it->first, L" ", s684 );
if( s684.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
wstring s656 = s684[1];
size_t idx = s684.size() - 2;
if( s684[idx] == s7::s449 )
pc = s476;
else if( s684[idx] == s7::s450 )
pc = s477;
else if( s684[idx] == s7::s2146 )
pc = s2150;
else
throw new s16( L"unknown object type: " + s684[0] );
if( s684.size() == 3 ) {
if( s684[0] == s7::s446 )
am = s507;
else if( s684[0] == s7::s448 )
am = s509;
else if( s684[0] != s7::s447 )
throw new s16( L"invalid access mode name: " + it->first );
s656 = s684[2];}
it->second->s294( s656 );}
s272* ob = new s272( *it->second, s300, pc, s300, am, cl, cnl, al, s2183 );
s657.s539( ob->s299(), ob );}}
void s262::s209( s1890& s659, bool s1887 ){
s716 s644;
s263* s208 = new s263();
wstring s189 = s4::s740( s659 );
if( !s3::s718( s189 )) {
wstring s1882;
if( s1887 ) {
if( s1883.empty() )
throw new s16( L"can't find the file: " + s659 );
s1882 = s1883;}
else
s1882 = s761;
s4::s61( s1882 );
wstring file = s189.substr( s189.rfind( L"/" ) + 1 );
s189 = s711( s1882, s189.substr(0, s189.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s34( s189 );
if( isf == 2 ) {
s4::s61( s189 );
s189 += s7::s458;
if( s761.empty() )
s761 = s659;}
else if( isf == 1 ) {
if( s761.empty() )
s761 = s189.substr( 0, s189.find_last_of( L"\\/" ) );
}
else
throw new s16( L"cannot find file or directory: " + s659,
(uint32_t)s16::s17::s23 );
s4::s61( s761 );
s202( s189, s644 );
size_t s792 = s199.size();
vector<s9<s143>> s660;
for( size_t n = 0; n < s644.s661.size(); n++ ) {
s660.clear();
wstring s662 = s644.s661[n];
if( s662[0] != L'/' && s662[1] != L':' )
s662 = s761 + s662;
s199.push_back( s662 );}
for( size_t n = s792; n < s199.size(); ++n ) {
s660.clear();
s941 s1044 = new s938( s199[n], true, s1756 );
s1044->read( s660, s7::s416 );
for( size_t m = 0; m < s660.size(); m++ ) {
if( s263::s302( *s660[m], s7::s463 ) == s7::s454 )
s213( s199[n], *s660[m] );
else if( s263::s302( *s660[m], s7::s463 ) == s7::s2152 )
s2158( *s660[m] );
else if( s263::s295( *s660[m], s7::s452 ) == s7::s452 ) {
s660[m]->s159( s7::s1115, new s6::s141( L"\"" 
+ s199[n] + 
L"\"" 
), s143::s145::s147 );
s208->s289( *s660[m], m );}}}
s207( *s208 );
if( s1007.s928() )
throw s929( s929::s17::s992 );
s263::s275& s696 = s208->s293();
for( auto it : s696 ) 
s695.s286( it.second );
if( s200.empty() )
s200 = s644.entry;}
void s262::s207( s263& s208 ){
s480 s657;
s622 m1;
s620 s663;
s621 s664;
vector<wstring> s665;
s671( this, s208, s657, s664, s663, m1 );
typedef std::pair<std::wstring, size_t> s2175;
std::sort( s663.begin(), s663.end(), []( const s2175& l, const s2175& r ) { return l.second < r.second; } );
for( size_t n = 0; n < s663.size(); ++n )
s665.push_back( s663[n].first );
for( size_t n = 0; n < s665.size(); ++n )
if( s203.s156( s665[n] ) )
throw new s16( L"class name already exists: " + s665[n] );
for( size_t n = 0; n < s665.size(); ++n )
s203.s218( s664[s665[n]], s664[s665[n]]->s351() );
s626.s289( s657 );
for( size_t n = 0; n < s665.size(); ++n ) {
s485 ob = (s272*)s203.get( s665[n], false );
if( ob )
ob->s154( *m1[s665[n]] );}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s272* ob = (s272*)s657.get( it->first, false );
if( ob && ob->s492() == s477 ) {
try {
ob->s154( *it->second );}
catch( s16* e ) {
e->s30( L"while constructing module: " + it->first );
throw e;}}}
s657.s498( this, NULL, false );}
void s262::s211( s143& obj ){
s263 s208;
s208.s289( obj, 0 );
s207( s208 );}
void s262::s1638( s1890& s667 ){
s481* pd = s626.get( s667 );
if( pd->s492() == s477 )
((s272*)pd)->s1637();}
s481* s262::run( const vector<wstring>& s687 ){
if( s200.empty() )
s200 = s7::s457 + L"::" + s7::s456;
if( !s687.empty() ) {
wstring  s668, s667;
s666( s200, s667, s668 );
s272* mod = (s272*)s626.get( s667 );
s807::Cont s1269;
wstring ts = Types( this, Types.Vector )->s351() + L"<" + Types( this, Types.String )->s351() + L">";
s1054 pt = ((s314*)Types( this, Types.Vector ))->s1186( this, ts, s1705, s1269 );
s314* s905 = (s314*) s300->TR().s1000( pt )->s353( this, vector<s482*>( {} ) );
for( size_t n = 0; n < s687.size(); ++n ) {
s905->add( new s357( this, s687[n], this ) );}
s905->s498( this, true );
mod->s845( s7::s1560, s905 );
mod->s845( s7::s823, new s344( this, (int)s687.size() ) );}
vector<wstring> l;
return callFunc( s200, l );}
s481* s262::callFunc( s1890& s, vector<wstring>& l ){
wstring  s668, s667;
s666( s, s667, s668 );
s272* mod = (s272*)s626.get( s667 );
s486 s669 = (s589*)mod->s639( s668, L"::" );
vector<s483> s274;
for( size_t n = 0; n < l.size(); n++ ) {
s940 ast_ = new s263( l[n], NULL, NULL );
s488 cs = s589::s1110( *ast_, this, mod, mod->s298(), false );
s274.push_back( cs );}
s669->s594( s274 );
s482* pr = s669->s494();
try {
s1309 = false;
if( !pr )
s669->s498( this, false );
else
s669->s595( this );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s669->s299() + L"' function " );}
s1309 = true;
mod->s1637();
s481* s681 = s669->s495();
if( s681->s616() == s7::s438 )
throw new s16( ( (s359*)s681 )->Msg() );
s1309 = false;
return s681;}
s486 s262::getProc( const std::wstring& s ){
wstring  s668, s667;
s666( s, s667, s668 );
s272* mod = (s272*)s626.get( s667 );
s486 s669 = (s589*)mod->s639( s668, L"::" );
s484 pr = s669->s494();
if( !pr )
s669->s498( mod, true );
return s669;}
/*
void s262::s201( const std::wstring& s659 ){
wstring s189 = s659;
wstring s658;
int isf = s3::s34( s659 );
if( isf == 2 ) {
s4::s61( s189 );
s189 += s7::s458;
s658 = s659;}
else if( isf == 1 )
s658 = s189.substr( 0, s189.find_last_of( L"\\/" ) );
else
throw new s16( L"cannot find file or directory: " + s659, 
(uint32_t)s16::s17::s23 );
s4::s61( s658 );
vector<s9<s143>> s660;
s941 s1044 = new s938( s189 );
s1044->read( s660, s7::s416 );
s716 s644;
for( size_t n = 0; n < s660.size(); n++ ) {
wstring s656 = s263::s302( *s660[n], s7::s463 );
if( s656 == s7::s451 ) {
s202( *s660[n], s644 );
break;}}
s200 = s644.entry;
if( s644.s661.empty() )
s644.s661.push_back( s189 );
for( size_t n = 0; n < s644.s661.size(); n++ ) {
s660.clear();
wstring s662 = s644.s661[n];
if( s662[0] != L'/' && s662[1] != L':' )
s662 = s658 + s662;
s941 s1044 = new s938( s662 );
s1044->read( s660, s7::s416 );
for( size_t m = 0; m < s660.size(); m++ )
if( s263::s295( *s660[m], s7::s452 ) == s7::s452 )
s695.s289( *s660[m] );}}
void s262::s202( const s6::s143& obj, s716& s153 ){
const vector<s142>& s162 = obj.s158( s7::s465 )->s167();
for( size_t n = 0; n < s162.size(); n++ )
s153.s661.push_back( s162[n]->s169() );
if( obj.s156( s7::s464 ) )
s153.entry = obj.s158( s7::s464 )->s169();}
*/
void s262::s1998( const std::vector<s1983>* s2019, s1984 sw ) const{
s2025.s1998( s2019, sw );}
bool s262::s1997( s1983 si, s1984 sw ) const{
return s2025.s1997( si, sw );}
s1054 s262::s218( s481* p, s1890& s345 ){
return s203.s218( p, s345 );}
bool s262::s554( s1890& sym_, s369* ref, s1890& s332, bool fr ) const{
if( !s272::s554( sym_, ref, s332, fr ) ) {
if( sym_ == s7::s1560 ) {
ref->s377( s638( s7::s826 ), s363 );
ref->s380( (s481*)this );
return true;}
return false;}
return true;}
bool s262::s221( s369& rf ) const{
rf.s380( NULL );
s205::const_iterator it = s206.find( rf.s615() );
if( it != end( s206 ) ) {
rf.s380( it->second );
return true;}
return false;}
void s262::s219( s1890& s76, s1890& s332,
vector<wstring>& s153 ){
size_t pl = s76.rfind( L"::" );
s272* mod = NULL;
bool bCl = false;
if( s76.find( L"()" ) == s76.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s670 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );}
mod = (s272*)s626.get( s670 );
if( !mod->s640( sym, s332 ) )
throw new s16( L"Symbol '" + s76 + L"' cannot be imported by '" +
s332 + L"'");
s153.push_back( sym );}
else {
if( bCl ) {
wstring sym = s76.substr( 0, s76.size() - 2 );
s203.get( sym );
s153.push_back( sym );}
else {
mod = (s272*) s626.get( s76 );
mod->s637( s332, s153 );}}}
s589* s262::s214( int s1446, 
s559* cs, s272* s586, s589* s215 ){
s589* s681 = NULL;
const s263* s695 = cs->s601();
std::vector<s271*>& s699 = cs->s600();
bool s2160 = cs->s2166();
if( s1446 == s1425 )
s681 = new s606( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1439 )
s681 = new s603( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1613 )
s681 = new s1595( this, s586, s215, s699, s695 );
else if( s1446 == s1419 )
s681 = new s605( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1420 )
s681 = new s1396( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s2064 )
s681 = new s2062( this, s586, s215, s699, s695 );
else if( s1446 == s1932 )
s681 = new s1924( this, s586, s215, s699, s695 );
else if( s1446 == s2195 )
s681 = new s2193( this, s586, s215, s699, s695 );
else if( s1446 == s1438 )
s681 = new s305( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1429 )
s681 = new s604( this, s586, s215, s699, s695 );
else if( s1446 == s1933 || s1446 == s1931)
s681 = new s1925( this, s586, s215, s699, s695 );
else if( s1446 == s1433 || s1446 == s1551)
s681 = new s607( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1422 )
s681 = new s608( this, s586, s215, s699, s695 );
else if( s1446 == s1427 )
s681 = new s832( this, s586, s215, s699, s695, 0, true, s2160 );
else if( s1446 == s1430 || s1446 == s2216 )
s681 = new s833( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1435 )
s681 = new s610( this, s586, s215, s699, s695 );
else if( s1446 == s1434 )
s681 = new s609( this, s586, s215, s699, s695 );
else if( s1446 == s1421 )
s681 = new s611( this, s586, s215, s699, s695 );
else if( s1446 == s1424 )
s681 = new s612( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1431 )
s681 = new s613( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1428 )
s681 = new s791( this, s586, s215, s699, s695 );
else if( s1446 == s1426 )
s681 = new s769( this, s586, s215, s699, s695 );
else if( s1446 == s1437 )
s681 = new s1297( this, s586, s215, s699, s695 );
else if( s1446 == s1616 )
s681 = new s1598( this, s586, s215, s699, s695 );
else if( s1446 == s1436 )
s681 = new s785( this, s586, s215, s699, s695 );
else if( s1446 == s1612 )
s681 = new s1593( this, s586, s215, s699, s695 );
else if( s1446 == s1614 )
s681 = new s1596( this, s586, s215, s699, s695 );
else if( s1446 == s1611 )
s681 = new s1592( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1432 ) {
s681 = new s811( this, s586, s215, s699, s695 );}
else if( s1446 == s1615 )
s681 = new s1597( this, s586, s215, s699, s695 );
else if( s1446 == s1423 )
s681 = new s890( this, s586, s215, s699, s695 );
else if( s1446 == s1610 )
s681 = new s1591( this, s586, s215, s699, s695, s2160 );
else if( s1446 == s1872 )
s681 = new s1870( this, s586, s215, s699, s695 );
return s681;}
s271*
s262::s222( s1890& s76, s1890& s497, bool s518 /*= true*/ )
{
size_t pl = s76.rfind( L"::" );
s483 s681;
if( pl == string::npos ) {
s681 = (s271*)s203.get( s76, s518 );
if( !s681 ) {
s272* exp = (s272*)s203.get( s7::s453, false );
if( exp )
s681 = exp->s639( s76, s497, s518 );}
return s681;}
wstring s670 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
return ((s272*)s203.get( s670 ))->s639( sym, s497 );	}
void* s262::s223( s1890& s278 ){
s334* s681;
s272* exp = (s272*) s626.get( s7::s453, false );
if( exp )
s681 = (s334*)exp->s639( s278, L"", true );
else
throw new s16( L"no such export variable: " + s278 );
void * pv = s681->addr();
return pv;}
void s262::s1341( s1890& s667 ){
s203.s1863( s667 );
s626.s540( s667 );
if( s203.s156( s667) )
s203.s1652( s667 );}
void s262::s1651( s1890& s1621 ){
vector<wstring> s1631;
for( auto it = s626.Table().begin(); it != s626.Table().end(); ++it ) {
s271* p = it->second.s15<s271*>();
if( p->s492() == s477 || p->s492() == s476 || p->s492() == s2150) {
wstring s189 = ( (s272*)p )->s639( s7::s1115, 
L":::" )->to_wstring();
if( s189 == s1621 )
s1631.push_back( it->first );}}
for( auto mod : s1631 )
s1341( mod );
for( size_t n = 0; n < s199.size(); ++n ) {
if( s199[n] == s1621 ) {
s199.erase( s199.begin() + n );
break;}}}
void s262::s2243( const s481* s152, s2239* s2254 ){
assert( s2255.find( s152 ) == s2255.end() );
s2255.insert( make_pair( s152, s2254 ) );}
s2239* s262::s2249( const s481* s152 ){
if( s2255.empty() )
return NULL;
auto it = s2255.find( s152 );
if( it == s2255.end() )
return NULL;
s2239* s681 = it->second;
s2255.erase( it );
return s681;}
void s262::s2248( const s481* old, const s481* nw ){
auto it = s2255.find( old );
if( it == s2255.end() )
return;
s2239* s274 = new s2239();
s274->assign( begin( *it->second ), end( *it->second ) );
s2255.insert( make_pair( nw, s274 ) );}
void s262::s304( std::wostream* pd, int s197 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s197 ) << s278 << L" : " << L"Assembly" << endl;
s203.s304( pd, s197 + s417 );
s626.s304( pd, s197 + s417 );}
map<int, s1::s9<s262>> handles;
HPROG createAssembly(){
static int s680 = 0;
s1::s9<s262> p = new s262();
handles[++s680] = p;
p->s1885( false );
return s680;}
void deleteAssembly( int n ){
auto it = handles.find( n );
if( it == end( handles ) )
throw new s2::s16( L"no assembly with such handle" );
handles.erase( it );}
void loadProgram( HPROG handle, const wstring& s189 ){
s262* p = handles[handle];
p->s1876( s3::s1869() );
p->s209( s189, true );}
TDType* getProc( HPROG handle, const std::wstring& s599 ){
s262* p = handles[handle];
return (TDType*)p->getProc( s599 );}
void s211( HPROG handle, s6::s143& obj ){
s262* p = handles[handle];
p->s211( obj );}
TDType* run( HPROG handle, const vector<wstring>& s687 ){
return handles[handle]->run( s687 );}
void* callFunc( HPROG handle, const std::wstring& s77, vector<wstring>& l ){
s262* p = handles[handle];
return p->callFunc( s77, l );}
void evaluateExpression( const std::wstring& s77 ){}
void* s223( HPROG handle, const std::wstring& s278 ){
s262* p = handles[handle];
return p->s223( s278 );}
void* execute( TDType* p ){
return p->s495().s15<s334*>()->addr();}
void importSymbol( HPROG handle, const std::wstring& s1103, const std::wstring& symName,
const std::wstring& s332 ){
s262* p = handles[handle];
s272* ob = (s272*)p->s639( s1103, s332 );
ob->s553( symName, s332 );}
void importFile( HPROG handle, const std::wstring& s1103, const std::wstring& s44,
const std::wstring& s332 ){
vector<s1::s9<s6::s143>> s660;
s6::s938 s1044( s44 );
s1044.read( s660, s7::s416 );
s262* p = handles[handle];
p->s209( s44 );
s272* ob = (s272*)p->s639( s1103, s332 );
for( size_t n = 0; n < s660.size(); n++ ) {
wstring s656 = s263::s302( *s660[n], s7::s463 );
ob->s553( s656, s332 );}}
HPROG initShell( const std::wstring& s1103, const std::wstring& modText ){
s1::s9<s6::s143> ob = new s6::s143(NULL);
size_t pos = 0;
s6::s1681 s1756( L".", L",", true, true, true );
s6::s938 s1044( L"", true, s1756 );
s1044.s170( modText, pos, ob );
ob->s159( s7::s463, new s6::s141( s1103 ) );
HPROG prog = createAssembly();
s211( prog, *ob );
return prog;}
} // namespace transd
