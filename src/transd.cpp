
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
uint32_t s16::s27;
std::vector<std::wstring> s1094 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1238(){
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
bool s760( const std::wstring& f ){
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
bool s760( const std::wstring& f ){
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
size_t& start, size_t& end, bool s971/*=false*/ )
{
end = string::npos;
start = string::npos;
int s67 = 0;
wchar_t s958 = 0;
bool esc = false;
for( size_t n = s66; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s958 || !s971 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s67++;}
else if( c == right ) {
if( start == string::npos )
return; // s890
if( --s67 == 0 ) {
end = n;
return;}}
else if( s971 && ( c == L'\'' || c == L'\"' ) ) {
s958 = c;}}
else if( s958 && c == s958 && !esc ) {
s958 = 0;}
else if( c == L'\\' ) {
esc = !esc;}
else
esc = false;}}
void s936( const wstring& s, size_t s66, wchar_t left, wchar_t right,
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
bool s926 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s926 = !s926;
if( s[n] == c && !s926 ) {
end = n;
return;}
if( s[n] != L'\\' )
s926 = false;}}
void s1099( const std::wstring& s, size_t& s66, const std::wstring& s1510 ){
size_t pl = s.find_first_of( s1510, s66 );
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
pl = s.find_first_of( s1510, pl );}
else {
s66 = pl;
return;}}}
void s1494( const std::wstring& s, size_t& s66, const std::wstring& s1206 ){
size_t pl = s.find( s1206, s66 );
if( pl == s66 )
return;
size_t start = s66;
s66 = string::npos;
while( pl < s.size() ) {
if( s1206.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1206.size();
if( pl < s.size() )
pl = s.find( s1206, pl );}
else {
s66 = pl;
return;}}}
size_t count( const std::wstring& s78, const std::wstring& s1206, size_t start, size_t end,
bool s971 ){
size_t s717 = 0;
size_t pl = s78.find( s1206, start );
while( pl < s78.size() && pl <= end) {
if( s971 && pl && s78[pl-1] == '\\' ) {
++pl;}
else {
++s717;
pl += s1206.size();}
if( pl < s78.size() - 1 ) 
pl = s78.find( s1206, pl );}
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
bool s1719( const wchar_t *str, long long *s363, wchar_t **end /*= NULL*/ )
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
bool s1720( const wchar_t *str, unsigned long long *s363, wchar_t **end /*= NULL*/ )
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
void s959( const wstring& s78, vector<wstring>& s156 ){
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
void s58( const wstring& s, const wstring& s73, vector<wstring>& s156, bool clr ){
size_t s69 = 0, s70 = 0;
while( s70 != wstring::npos && s69 < s.size()) {
s70 = s.find( s73, s69 );
wstring seg;
if( clr ) 
seg = s53( s.substr( s69, s70 - s69 ), s49 );
else
seg = s.substr( s69, s70 - s69 );
s69 = s70 + s73.size();
if( seg.size() )
s156.push_back( seg );}}
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
wstring s788( wstring path ){
size_t pl = path.find( L"\\" );
while( pl != string::npos ) {
path = path.replace( pl, 1, L"/" );
pl = path.find( L"\\" );}
if( path.front() == L'\'' || path.front() == L'"' ) {
if( path.back() != path.front() )
throw new s2::s16( L"opening and closing quotes don't match" );
path = path.substr( 1, path.size() - 2 );}
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
void s82( wstring& s78, vector<wstring>& s1221, map<size_t, size_t>& s1145 ){
size_t pos = 0;
wchar_t s83 = 0;
bool s1305 = false;
wchar_t s84 = 0;
bool s85 = false;
bool s86 = false;
size_t s87 = string::npos;
bool s88 = false;
bool s1075 = false;
wstring s89 = L"`'\"";
s1221.reserve( 1000 );
size_t s1139 = 1;
bool s1066 = false;
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
s1145[pos - 2] = s1139;}}
else if( c == '/' ) {
if( !s85 && s84 == '/' ) {
s87 = pos - 1;
s85 = true;
s86 = false;
if( pos > 1 && s78[pos - 2] != '\n')
s1145[pos - 2] = s1139;}
else if( s86 && s84 == '*' ) {
s88 = true;
if( s78[pos+1] == '\n' ){
s1066 = true;}}}
else if( c == '\n' ) {
s1066 = true;
if( s85 ) {
if( !s86 ) {
s88 = true;}
else {
if( !s1075 ) {
s1075 = true;}}}
else {
if( pos && s78[pos-1] != '\n' ) {
s1145[pos - 1] = s1139;}}}
if( c != L'\\' )
s1305 = false;
if( s1066 ) {
size_t pl = s78.rfind( '\n', pos - 1 );
size_t m = (s78[pos] == '\n');
if( pl == string::npos )
s1221.push_back( s78.substr( 0, pos ) );
else
s1221.push_back( s78.substr( pl + 1, pos - pl - m ) );
s1066 = false;
s1139++;}
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
s1075 = false;
s86 = false;
s88 = false;
s84 = 0;}
s84 = c;
pos++;}
if( s85 ) {
auto it = end(s1145);
if( s1145.size() ) it--; 
size_t ln = (it == end(s1145) ? 0 : it->second);
throw new s2::s16( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
}//namespace s4
namespace s5 {
std::locale locloc;
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;}
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
void s1234(){
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
size_t s1228 = s121.size();
size_t s122 = s1228;
while( s612 ) {
s120 = _getch();
switch( s120 ) {
case s113:
if( s1228 > s122 ) {
wcout << '\r' << s121.substr( 0, --s1228 );}
break;
case s114:
if( s1228 < s121.size() )
wcout << s121[s1228++];
break;
case s111:
case s112:
continue;
case s117:
if( ( s1228 > s122 ) && s121.size() ) {
s121.erase( --s1228, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}
break;
case s118:
if( s1228 < s121.size() ) {
s121.erase( s1228, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}
break;
case s116:
s612 = false;
break;
case s119:
break;
default:
if( s1228 < s121.size() )
s121.insert( s1228, 1, s120 );
else
s121 += s120;
++s1228;
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}}
return s121;}
wstring getStringValHist( const wstring& s95, const vector<wstring>& s105 ){
wcout << s95 << endl;
int s120 = 0;
size_t s716 = s105.size();
bool s612 = true;
wstring s121;
size_t s1228 = 0;
while( s612 ) {
s120 = _getch();
#ifdef __LINUX__
if(s120 == 27) {
_getch();
s120 = _getch();
if( s120 == L'A' ) s120 = s111;
else if(s120 == L'B') s120 = s112;
else if(s120 == L'C') s120 = s114;
else if(s120 == L'D') s120 = s113;}
else if( s120 == 10 )
s120 = 13;
else if( s120 == 127 )
s120 = 8;
#else			
if(s120 == 224) {
s120 = _getch();
if( s120 == L'H' ) s120 = s111;
else if(s120 == L'P') s120 = s112;
else if(s120 == L'M') s120 = s114;
else if(s120 == L'K') s120 = s113;}
else if( s120 == 0 ) {
s120 = _getch();
if( s120 = 83 ) s120 = s118; // S
else if( s120 = 71 ) s120 = s1733; // G
else if( s120 = 79 ) s120 = s1732; // O
}
#endif			
switch( s120 ) {
case s113:
if( s1228 > 0 ) {
wcout << '\r' << s121.substr( 0, --s1228 );}
break;
case s114:
if( s1228 < s121.size() )
wcout << s121[s1228++];
break;
case s111:
if( s716 > 0 ) {
if( s716 < s105.size() )
wcout << '\r' << wstring( s121.size(), L' ' );
s121 = s105[--s716];
wcout << '\r' << s121;
s1228 = s121.size();}
break;
case s112:
if( !s105.empty() && s716 < s105.size() - 1 ) {
wcout << '\r' << wstring( s121.size(), L' ');
s121 = s105[++s716];
wcout << '\r' << s121;
s1228 = s121.size();}
break;
case s117:
if( s1228 > 0 && s121.size() ) {
s121.erase( --s1228, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}
break;
case s118:
if( s1228 < s121.size() ) {
s121.erase( s1228, 1 );
wcout << '\r' << wstring( s121.size() + 1, L' ' );
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}
break;
case s1733:
if( s1228 > 0 ) {
wcout << '\r';
s1228 = 0;}
break;
case s1732:
if( s1228 < s121.size() ) {
wcout << '\r' << s121;
s1228 = s121.size();}
break;
case s116:
s612 = false;
break;
case s119:
break;
default:
if( s1228 < s121.size() )
s121.insert( s1228, 1, s120 );
else
s121 += s120;
++s1228;
wcout << '\r' << s121 << '\r' << s121.substr( 0, s1228 );}}
return s121;}
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
wstring s1713 = L"0123456789";
wstring s1714 = L".0123456789";
wstring s190 = L" ,]}\t\r\n";
void s1033::s174( const wstring& s78, size_t& pos, s9<s146> ob, bool s154/*= false*/ )
{
size_t s75, s76;
s55( s78, pos, L'{', L'}', s75, s76, true );
if( s75 == string::npos )
return;
s1169 = s75 - 1;
wstring sob = s78.substr( s75, s76 - s75 + 1 );
pos = s76 + 1;
try {
ob->s157( sob, s154 );}
catch( s16* e ) {
e->s30( L"during reading the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s1033::s1104( wstring& s, size_t s69, size_t s715, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1233.lower_bound( s69 );
auto iten = s1233.lower_bound( s715 );
if( itst == end(s1233) || iten == end(s1233) )
return false;
line = itst->second;
s = s1232[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1232[iten->second-1];
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
s1033::s1033( const std::wstring& file, bool s1811 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s49 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1811 == false )
s1231 = file;
else
s198 = file;}
void s1033::read( vector<s9<s146>>& s156, const wstring& s194 ){
size_t pos = 0;
if( s198.size() ) {
std::ifstream fs( TOFS( s198 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s198 ));
string s195( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1231 = conv.from_bytes( s195 );
s4::s82( s1231, s1232, s1233 );
if( s194.size() ) {
pos = s1231.find( s194 );
if( pos == string::npos )
throw new s16( s194 + L" directive not found in the source file." );
pos += s194.size() + 1;
if( s1231.size() > 13 && s1231[14] == '\r' )
++pos;}}
size_t s196 = pos;
wstring s284;
bool s197 = false;
while( ( pos = s1231.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1231.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s196; subl = pos - s196;}
else
pl += 1;
wstring s1 = s53( s1231.substr( pl, /*pos - pl - 1*/subl ), s49 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s197 = true;
else
s284 = s53( s1, s49 + L":" );}
if( s284.empty() ) {
size_t pl1 = s1231.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s53( s1231.substr( pl1, pl ), s49 );
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
s174( s1231, pos, ob, true );}
catch( s16* e ) {
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
if( s154 )
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
void s180( const wstring& s78, size_t& pos, wstring& s156 ){
if( !std::isgraph<wchar_t>( s78[pos], locloc ) ||
s78[pos] == L':' || s78[pos] == L',' )
throw new s16( L"unrecognized unquoted syntax: " + s78.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s200 = pos;
int shift = 0;
if( s78[pos] == L'(' ) {
s179( s78, s200, L'(', L')', s156 );
if( s200 == s78.size() - 1 )
shift = 1;}
else {
s200 = pos + 1;
while( std::isgraph<wchar_t>( s78[s200], locloc ) &&
s78[s200] != L':' && s78[s200] != L',' ) {
if( s78[s200] == L'<' ) {
s179( s78, s200, L'<', L'>', s156 );}
else if( s78[s200] == L'(' ) {
s179( s78, s200, L'(', L')', s156 );
if( s200 == s78.size() - 1 )
shift = 1;
break;}
else
++s200;}}
s156 = s53( s78.substr( pos, s200 - pos + shift ), s49 );
pos = s200;}
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
void s182( const s1033* pf, const wstring& s78, vector<s9<s144>>& s156, bool s154,
const std::wstring& s73 ){
size_t s69 = s78.find_first_not_of( s49 );
while( true ) {
s156.push_back( s9<s144>(new s144( pf, s78, s69, s154 ) ) );
s4::s1099( s78, s69, s73 );
if( s69 == string::npos )
break;
++s69;}}
void s182( const s1033* pf, const wstring& s78, size_t& pos, vector<s9<s144>>& s156, 
bool s154, const std::wstring& s73 ){
size_t s75, s76, s69 = 0;
s55( s78, pos, L'[', L']', s75, s76, true );
pos = s76 + 1;
wstring ar = s53( s78.substr( s75 + 1, s76 - s75 - 1 ), s49 );
while( true ) {
s156.push_back( s9<s144>(new s144( pf, ar, s69, s154 ) ) );
s4::s1099( ar, s69, s73 );
if( s69 == string::npos )
break;
++s69;}}
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
s134 s1725( const wstring& s78, size_t& pos, double& s156 ){
const wchar_t* ps = s78.c_str();
size_t sz = s78.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1714.find( ps[st+1] ) == string::npos )
return s135;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1713.find( ps[st+1] ) != string::npos ) ||
( s1713.find( ps[st] ) == string::npos ) )
return s135;
size_t s716 = st;
bool pt = false;
while( s716 < sz ) {
if( ps[s716] == L'.' ) {
if( pt ) return s135;
pt = true;}
else if( s1713.find( ps[s716] ) != string::npos )
s716++;
else
break;}
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
s144::s144( const s1033* pf, const wstring& s78, size_t& pos, bool s154/*= false*/ )
: s202( s135 ), obj( pf ), s1193( pos + (pf ? pf->s1038():0), 0 ), s1192( (s1033*)pf ){
size_t s69 = s78.find_first_not_of( L" \n\r\t", pos );
if( s78[s69] == L'{' ) {
size_t s75, s76;
s55( s78, s69, L'{', L'}', s75, s76, true );
pos = s76+1;
obj.s157( s53( s78.substr( s75 + 1, s76 - s75 - 1 ), s49 ), s154 );
s202 = s136;}
else {
pos = s69;
if ( s89.find( s78[pos] ) != string::npos ) {
s176( s78, pos, s78[pos], str, s154 );
s202 = s142;}
else if ( s78[pos] == L'[' ) {
s182( (s1033*)s1192, s78, pos, s165 ); 
s202 = s138;}
else {
s202 = s1725( s78, pos, s166 );
if( s202 != s135 )
(void)0;
else if( s187( s78, pos, b ) )
s202 = s140;
else if( s188( s78, pos ) )
s202 = s141;
else {
s180( s78, pos, str );
s202 = s137;}}}
s1193.second = pf ? pos - 1 + pf->s1038() : 0;}
bool s144::s1109( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1193.first || s1192.s13() )
return false;
f = s1192->Path();
s1192->s1104( s, s1193.first, s1193.second, line );
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
bool s144::s767() const{
if( s202 == s140 )
return b;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s144::s172() const{
if( s202 == s137 || s202 == s142 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s144::s939() const{
if( s202 == s142 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
std::wstring s144::s929() const{
if( s202 == s142 )
return str.substr( 1, str.size() - 2 );
throw new s16( L"NQJ value: wrong variant" );}
void s146::s157( const wstring& s78, bool s154/*=s154*/ )
{
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
s184( s78, s69, s77, s154 );
size_t pl = s78.find_first_not_of( L" \n\r\t", s69 );
if( pl == string::npos || s78[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s78.substr(s69, 50), 
(uint32_t)s16::s17::s20 );
s69 = pl + 1;
s147.insert( make_pair( s77, new s144( src, s78, s69, s154 ) ) );
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
void s146::s1808( const std::wstring& s77 ){
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
} // namespace s6
using namespace s6;
namespace transd {
namespace s7 {
s1015 s1729		= 0x80000000;
s1015 s1567        = s1729 - 1;
s1015 s1568       = s1729 - 2;
s1015 s1569       = s1729 - 3;
s1015 s1566      = s1729 - 4;
s1015 s1565						= s1729 - 8;
s1015 s1570    = s1729 - 9;
s1015 s1571					= s1729 - 10;
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
DEFCONST s1806 = L"@to-String";
DEFCONST s445 = L"thisPtr";
DEFCONST s446 = L"virtual";
DEFCONST s447 = L"override";
DEFCONST s897 = L"return";
DEFCONST s448 = L"continue";
DEFCONST s449 = L"break";
DEFCONST s450 = L"throw";
DEFCONST s811 = L"else";
DEFCONST s792 = L"elsif";
DEFCONST s846 = L"to";
DEFCONST s451 = L"true";
DEFCONST s452 = L"false";
DEFCONST s896 = L"null";
DEFCONST s1028 = L"->";
DEFCONST s1263 = L"const";
DEFCONST s1525 = L"new";
DEFCONST s1563 = L"stdin";
DEFCONST s1564 = L"stdout";
DEFCONST s1778 = L"this";
DEFCONSTI s940 = -1;
DEFCONSTI s455 = -2;
DEFCONSTI s453 = -100;
DEFCONSTI s454 = -101;
DEFCONSTI s456 = 1;
DEFCONSTI s457 = 0;
DEFCONSTI s942 = 0x80000000;
DEFCONSTI s941 = 0;
DEFCONSTI s1342 = 1;
DEFCONST s1585 = L":Number";
DEFCONST s1699 = L":Integer";
DEFCONST s1583 = L":IterableForw";
DEFCONST s1582 = L":IterableBidir";
DEFCONST s1584 = L":IterableRand";
DEFCONST s1581 = L":IStream";
DEFCONST s1586 = L":OStream";
DEFCONST s1580 = L":IOStream";
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
DEFCONST s1034 = L".tsd";
DEFCONST s474 = L"MainModule";
DEFCONST s473 = L"_start";
DEFCONST s475 = L"asm" + s472;
DEFCONST s476 = L"@ex";
DEFCONST s1545 = L"@it";
DEFCONST s477 = L"@idx";
DEFCONST s815 = L"@pars";
DEFCONST s854 = L"@obj";
DEFCONST s889 = L"@numArgs";
DEFCONST s1748 = L"@progArgs";
DEFCONST s1241 = L"@sourceFile";
DEFCONST s1544 = L"@OS_Type";
DEFCONST s482 = L"source";
DEFCONST s478 = L"objectType";
DEFCONST s479 = L"moduleType";
DEFCONST s480 = L"@name";
DEFCONST s481 = L"entryPoint";
DEFCONST s483 = L"perm";
DEFCONST s485 = L"extends";
DEFCONST s779 = L"packages";
DEFCONST s487 = L"searchDirs";
DEFCONST s1023 = L"@attrs";
DEFCONST s1002 = L"is";
DEFCONST s1001 = L"index type";
DEFCONST s1003 = L"value type";
DEFCONST s433 = L"#lang transd";
DEFCONST s1223 = L"#format tsd";
s1015 s1459						= 103;
s1015 s1536					= 104;
s1015 s1010						= 110;
s1015 s1458				=	123;
s1015 s1246						= 124;
s1015 s1011 			=	125;
s1015 s1005			= 201;
s1015 s1224				= 204;
s1015 s1006					= 210;
s1015 s1225					= 304;
s1015 s1226				= 404;
s1015 s1227				= 504;
s1015 s1007					= 510;
s1015 s1008			= 511;
s1015 s1009					= 610;
s1015 s1243							= 710;
s1015 s1244					= 711;
s1015 s1537		= 804;
s1015 s1538				= 904;
s1015 s1539				= 1004;
s1015 s1774					= 1024;
s1015 s1245					= 1124;
s1015 s1455				= 1203;
s1015 s1456				= 1210;
s1015 s1457				= 1224;
s1015 s1844		= 1304;
s1015 s1845						= 1404;
s1015 s1549						= 1410;
s1015 s1846						= 1504;
s1015 s1547						= 1510;
s1015 s1548					= 1511;
s1015 s1847				= 1604;
s1015 s1697					= 1610;
s1015 s1698			= 1611;
s1015 s1730			= 1710;
s1015 s1776	= 1715;
s1015 s1775				= 1824;
set<wstring> s1240 = { s1241, s1563, s1564, s1544, s897, s448,
s449, s450, s811, s792, s846, s451, s452, s896, s1028, s1263,
s1525, s1563, s1564, s1778
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
const wstring s818 = L"load-file";
const wstring s878 = L"import-module";
const wstring s1797 = L"unload-file-modules";
const wstring s1484 = L"unload-module";
const wstring s795 = L"has-field";
const wstring s874 = L"tsd-query";
const wstring s804 = L"substr";
const wstring s924 = L"ret";
const wstring s925 = L"sort";
const wstring s987 = L"exit";
const wstring s1483 = L"to-file";
const wstring s1603 = L"any";
const wstring s1602 = L"all";
const wstring s1737 = L"lout";
const wstring s1793 = L"read-tsd-file";
const wstring s1792 = L"load-from-object";
const wstring s1796 = L"start-process";
const wstring s1794 = L"rebind";
const wstring s1795 = L"sleep";
const wstring s1791 = L"diag";
const std::wstring s271 = L"AttrNA";
s269::s269( const std::wstring& s, const s144* s6 )
: s1161( (s144*)s6 ){
s1101( s );}
s269::s269( const std::wstring& s708, const s6::s144& s302 )
: s284( s708 ), s1161( (s144*)&s302 ){
if( s302.s167() == s137 ) {
wstring s = s302.s172();
s1101( s );}
else if( s302.s167() == s142 ) {
wstring s = //L"\"" +
s302.s172();// +
s290( s );}
else if( s302.s167() == s136 ) {
basic_stringstream<wchar_t> ss;
s302.s158( &ss, true );
if( s284.find( s770->s368() ) == 0 ) {
s290( ss.str() );
s284 = s4::s53( s284.substr( s770->s368().size() ), s49 );}
else {
src = ss.str();
s289( s302.s169() );}}
else if( s302.s167() == s139 )
s290( to_wstring( s302.s171() ) );
else if( s302.s167() == s143 )
s290( to_wstring( s302.s57() ) );
else if( s302.s167() == s140 )
s290( /*to_wstring( s302.s767() )*/ s302.s767() ? L"true" : L"false");
else if( s302.s167() == s138 ) {
basic_stringstream<wchar_t> ss;
s302.s158( &ss );
if( s284.find( L"UVector" ) == 0 ) {
s290( L"UVector" + ss.str() );
s284 = s4::s53( s284.substr( 7 ), s49 );}
else
s290( ss.str() );}
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
void s269::s1101( const wstring& s ){
size_t pos = 0;
wstring s1327 = L"\"'-+[<";
if( s[pos] == L'(' )
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
s287.insert( make_pair( to_wstring( n - 1 ), new s269( s709[n], s1161 ) ) );}
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
map<wstring, s1035>::const_iterator it = s287.begin();
for( ; it != s287.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << it->first << endl;
it->second->s310( pd, s201 + s434 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1222 s1115;
void s1222::s1065( const std::wstring& s79 ){
++s1095;
s26.push_back( Msg( s79 ) );
wcout << s79;}
void s1222::s1065( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line ){
++s1095;
s26.push_back( Msg( s79, U16(func), U16(file), line, s1149 ) );}
void s1222::s1067( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s79, U16(func), U16(file), line, s1152 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1196 = {
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
TDException::TDException( uint32_t s1117, uint32_t cat, const s269* ast_ )
: s16( L"", s1117 ), stage (Stage::s1138 ), category( cat ), s736( ast_ ){}
TDException::TDException( Stage stg, uint32_t s1117, uint32_t cat, const s269* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s736( ast_ ){
if( category ) {
s30( s1092[category] + L":" );}}
TDException::TDException( uint32_t s1117, uint32_t cat, const s269* ast_, const std::wstring& s79 )
: s16( s79, s1117 ), stage (Stage::s1138 ), category( cat ), s736( ast_ ){
if( category ) {
s30( s1092[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1203( e.s1203 ), s736( e.s736 ){}
TDException* TDException::s1098( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s201 ) const{
size_t s1140 = 0;
wstring file, s1194, src;
if( s736 ) {
if( s736->Nqj() && s736->Nqj()->s1109( file, s1194, s1140 ) ) {
wstring s1190 = std::to_wstring( s1140 ) + L": '" + s1194 + L"'";
src = L"\n  in file: " + file + L"\n  on line " + s1190;}
if( !s736->s297().empty() )
src += L"\n  object: '" + s736->s297() + L"', ";
if( !s736->Src().empty() )
src += L"code: '" + s736->Src() + L"', ";}
wstring s = L"Error ";
if( id ) {
wstring s1188;
if( (uint32_t)stage )
s1188 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1188 += std::to_wstring( id );
s += s1188;}
if( (uint32_t)stage ) {
s += L" during " + s1196[(uint32_t)stage];}
s += src + L"\n";
return wstring( s201, L' ' ) + s + s16::Msg( s201 + 2 );}
s1014::s1014( s16& e, const s269& s736, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1140 = 0;
wstring file, s1194, src;
wstring	s79 = L"Error during ";
if( s736.Nqj()->s1109( file, s1194, s1140 ) ) {
src = std::to_wstring( s1140 ) + L": '" + s1194 + L"'";
s79 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s79 += L"object: '" + s736.s297() + L"'; code: " + s736.Src();}
s30( s79 );
s1115.s1065( Msg( 2 ) );}
s1022::s1022( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s1092 = {
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
bool s685( const wstring& s, bool s750 ){
bool s749 = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1240.find( s ) != s7::s1240.end() )
continue;
s749 = true;
break;}
if( s749 && s750 )
throw new s16( L"illegal identifier: " + s );
return (!s749);}
} // namespace tdlang
s1013 s1091;
s277::~s277(){}
s501* s277::s515()
{	throw std::logic_error( "1: not implemented" );}
const s501* s277::s523() const
{	throw std::logic_error( "2: not implemented" );}
s504 s277::s516( s501** s280, size_t s517 )
{	throw std::logic_error( "3: not implemented" ); }
s277* s277::s349() const
{	throw std::logic_error( "4: not implemented" ); }
void s277::s519( const s278* s611 ) {
(void)0;}
inline bool
s277::s521( const s501* s522 ) const{
return ( s522->s366() == s366() );}
inline bool
s277::s1716( s1171 s646 ) const{
return s306->TR().s1709( s366(), s646 );}
const s868& 
s277::s1339() const {
return s306->TR().s1113( s512 ); }
s277::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s277::operator int() const { throw std::logic_error( "6: not implemented" ); }
s277::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s277::to_wstring( uint32_t s1740 ) const { throw std::logic_error( "8: not implemented" ); }
s1489 s277::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s277::s1501( const s269& ast_, s268* s306, s278* obj,
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
s1035 tast = new s269( s78, s736.Nqj() );
p = s615::s1236( *tast, s306, obj, s346 );}
else {
p = s306->TR().s541( s736, obj, s346 );
((s501*)p)->s526( s736.s305() );}}
else if( s736.s303() == s231 )
p = s615::s1236( s736, s306, obj, s346 );
else if( s736.s303() == s233 )
p = new s386( s736.s297(), s306 );
else //if( s736.s303() == s232 )
throw new s16( L"unexpected node type" );
return p;}
s277* 
s277::s1121( s268* s306, s277* par, s278* s612, s615* s219,
const std::wstring& s346 ){
s277* s717;
if( par->s513() == s495 ) {
s508 cs = new s584( *((s584*)par) );
s717 = s615::s624( cs, s306, s612, s219, s346 );
((Transd*)s717)->s519( s612, false );}
else {
par->s519( /*s612*/s219 );
return par;}
return s717;}
s503
s277::s1120( const wstring& s78, const s269* ast_, s268* s306, s278* s612 ){
s1035 ast1 = new s269( s78, ast_->Nqj() );
s503 pr = s277::s524( *ast1, s306, s612, s612->s304() );
if( pr->s513() == s492 ) {
pr->s519( s612 );
pr = pr.s15<s386*>()->s392();}
s503 s717 = s277::s1121( s306, pr, s612, NULL, s612->s304() );
return s717;}
const wstring& 
s277::s368() const{
return s306->TR().s855( s366() );}
void s277::s365( s868::s777 type ){
s512 = type;}
s502* s1237( s525& m, const wstring& s155 ){
if( m.count( s155 ) > 1 )
throw new s16( L"multiple values: " + s155, (uint32_t)s16::s17::s21 );
auto s717 = m.find( s155 );
if( s717 == m.end() )
throw new s16( L"no such key: " + s155, (uint32_t)s16::s17::s23 );
return s717->second;}
void s701( const std::wstring& s, std::wstring& s1229, std::wstring& s625 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1229 = s.substr( 0, pl );
s625 = s.substr( pl + 2 );}
s501* s501::s515(){
return this;}
wstring s501::s304() const { return ns->s304(); }
wstring s501::s899() const { return ns->s899(); }
s501* s501::s1711( const s501* p ) const{
if( s366() == p->s366() ) {
s501* s717 = (s501*)p->s349();
return s717;}
throw new s16( L"no conversion from '" + s368() + L"' to '" + p->s368() + L"'" );}
s501* s501::s370( s278* s612, const std::vector<s1171>& vt ) const{
assert(0);
return 0;}
s1171 s501::s1331( const wstring& s1728, const vector<s503>& l ) const{
throw std::logic_error( "9: not implemented" );}
vector<wstring> s544::s548 = { s7::s461, s7::s459,
s7::s462, s7::s460 };
s1::s9<s549> s580 = new s549();
size_t s1059( const vector<s868::s979>& vt ){
size_t s717 = 0;
for( auto i : vt )
s717 = ( s717 << 7 ) ^ i;
return s717;}
size_t s509::s1164( const wstring& s, size_t& pos, s868::Cont& s156 ){
size_t s69 = pos;
size_t s717 = 0;
if( s[s69] == L' ' )
s69 = s.find_first_not_of( s4::s49, s69 );
while( s69 < s.size() && s[s69] != L'>' && s[s69] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s69 );
wstring stype = s4::s53( s.substr( s69, pl - s69 ), s4::s49 );
s1171 s1207 = get( stype /*+ L"()"*/ )->s366();
s156.push_back( s1207 );
pl = s.find_first_not_of( s4::s49, pl );
s868::Cont s1179;
size_t s1162 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1162 = s1164( s, ++pl, s1179 );}
else if( s[pl] == L',' ) {
s1162 = 0;}}
s156.push_back( ( s868::s979 ) s1162 );
s156.insert( end( s156 ), begin( s1179 ), end( s1179 ) );
s717++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s49, pl );
pos = s69 = pl;}
return s717;}
wstring s1296( const s868::Cont& s1174, size_t& idx, s509& s997 ){
wstring s717 = s997.s855(s1174[idx++]);
size_t n = (size_t)s1174[idx++];
if( n && s717.back() != L'>' ) {
s717 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s717 += ( k ? L" " : L"" ) + s1296( s1174, idx, s997 );}
s717 += L">";}
return s717;}
wstring s509::s1112( const s868::Cont& s1174 ){
assert( s1174.size() );
if( s1174.size() == 1 )
return  s1213[s1174[0]] + L"< 0 >";
size_t idx = 0;
wstring s717;
while( idx < s1174.size() ) {
s717 += s1296( s1174, idx, *this );
if( idx < s1174.size() )
s717 += L" ";}
return s717;}
wstring s509::s1521( const wstring& tn ){
wstring sv = tn;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
return sv;}
void s509::s1108( const s868::Cont& v, size_t& idx, s868::Cont& s156 ){
s156.push_back( v[idx++] );
size_t n = v[idx++];
s156.push_back( (s1171)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s1108( v, idx, s156 );}}
s868::s868( s777 t1, s777 t2/*=(s777)-1*/, s777 t3/*=(s777)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s777)-1 ) {
vt.push_back( t2 );
if( t3 != (s777)-1 )
vt.push_back( t3 );}
s1211 = s1059( vt );}
s868::s868( const s868& right )
: s1211( right.s1211 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s868::s868( const Cont& v ) 
: vt( v ) {
s1211 = s1059( vt );}
s868::s979 s868::s366( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s868::s365( s777 t ){
vt.clear();
vt.push_back( t );}
void s868::s365( s1012 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s868::s835( s777 t ){
vt.push_back( t );}
void s868::s835( s1012 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s868::s876( std::vector<s277*>& s156 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s156.push_back( new s360( NULL, (int)vt[n] ) );}
inline bool s868::operator==( const s868& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s777* pvt1 = (s777*)&vt[0];
s777* pvt2 = (s777*)&p.vt[0];
for( size_t s716 = 0; s716 < sz1; ++s716 )
if( pvt1[s716] != pvt2[s716] )
return false;
return true;}
s509::s509( s268* pass_ ) 
: s306( pass_ ) {
reset();}
void s509::s296(){
for( size_t n = 0; n < s1230.size(); ++n )
if( s1230[n] ) s1230[n]->s364();}
void s509::s539( const s500& st ){}
void s509::reset() {
s1230.clear(); 
s1213.clear();
s1218.clear();
s1214.clear();
s1219.clear();
s1004.clear();
s978.clear();
s1410.clear();
s1428.clear();
s1726.clear();
s1230.push_back( NULL ); 
s1213.push_back( L"" );
s1218.push_back( 0 );
s978[L":Data"] = 1;
s1410[1] = L":Data";
s1350 = 1;
s1428.push_back( 0 );
srand( (unsigned int)time(NULL) );}
void s509::s223( s501* p, const std::wstring& s361 ){
if( s1214.find( s361 ) != s1214.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1213.push_back( s361 );
s1230.push_back( p );
s1171 s1207 = (s1171)s1213.size() - 1;
s1218.push_back( s868( s1207 ) );
p->s365( s1207 );
s1214[s361] = s1207;
s1219[s1218.back()] = s1207;
s1428.push_back( 1 );
s1726.push_back( vector<s1171>() );}
void s509::s1843( const std::wstring& s361 ){
auto it = s1214.find( s361 );
if( it == s1214.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1171 s1207 = it->second;
s1214.erase( it );
s1230[s1207] = NULL;
s1213[s1207] = L"";
s1219.erase( s1218[s1207] );
s1218[s1207] = s868();
s1428[s1207] = 0;
s1726[s1207-1].clear();}
s1171 s509::s1178( const s868::Cont& v, const std::wstring& s361 ){
s868 vt( v );
if( s1219.find( vt ) != s1219.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1213.push_back( s361 );
s1218.push_back( vt );
s1171 s1207 = (s1171)s1213.size() - 1;
s1214[s361] = s1207;
s1219[s1218.back()] = s1207;
s1219[s868( s1207 )] = s1207;
s1230.push_back( s1230[vt.s366( 0 )]->s370( s306, v )	);
s1428.push_back( s1428[vt.s366( 0 )] );
s1726.push_back( vector<s1171>() );
return s1207;}
s1171 s509::s1154( const s868::Cont& v_ ){
assert( all_of( begin( v_ ), end( v_ ), [this]( s1171 t ) { return ( t <= s1218.size() ); } ) );
s868 vt( v_ );
s1171 s717 = 0;
auto it = s1219.find( vt );
if( it == s1219.end() ) {
wstring s1205 = s1112( v_ );
s717 = s1178( v_, s1205 );}
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
traitnum_t s509::s1403( const std::wstring& trait, s1171& s1685 ){
auto it = s978.find( trait );
if( it != end( s978 ) )
return it->second;
s1350 = s1336( s1350 );
s978[trait] = s1350;
s1410[s1350] = trait;
s1685 = s7::s1729 + (s1171)s1686.size();
s1686.push_back( s1350 );
return s1350;}
void s509::s1301( s868::s979 type, const wstring& trait, s1171& s1685 ){
traitnum_t tn;
auto it = s978.find( trait );
if( it == end( s978 ) ) {
tn = s1403( trait, s1685 );
s1428[type] *= tn;}
else {
tn = it->second;
if( !s1341( type, tn ) )
s1428[type] *= tn;}}
traitnum_t s509::s1633( s1171 alias ) const{
return s1686[alias - s7::s1729];}
bool s509::s1341( s1171 s646, traitnum_t tra ) {
double d = (double)s306->TR().s1294( s646 ) / tra;
return ( d == (int)d );}
bool s509::s1640( s1171 s646, s1171 alias ) {
double d = (double)s306->TR().s1294( s646 ) / 
s1686[alias-s7::s1729];
return ( d == (int)d );}
void s509::s1708( s1171 s646, s1171 is ){
s1726[s646].push_back( is );}
bool s509::s1709( s1171 s646, s1171 is ){
if( s646 == is )
return true;
if( s646 >= s1726.size() )
return false;
std::vector<s1171>& v = s1726[s646];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
void s509::s1312( const wstring& alias, const wstring& s361 ){
assert( s1214.find( alias ) == end( s1214 ) );
s1171 typid;
auto it = s1214.find( s361 );
if( it == s1214.end() ) {
s868::Cont vt;
size_t pos = 0;
s1164( s361, pos, vt );
typid = s1154( vt );}
else
typid = it->second;	
s1213.push_back( alias );
s1230.push_back( s1230[typid] );
s1218.push_back( s1218[typid] );
s1428.push_back( s1428[typid] );
s1726.push_back( s1726[typid-1] );
s1214[alias] = typid;}
wstring s509::s1429( const wstring& tn_ ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1214.find( s );
if( it == end( s1214 ) )
return tn_;
const wstring& tn = s1213[s1219[s1218[it->second]]];
if( tn != s ) {
wstring s717 = tn_;
return s717.replace( 0, s.size(), tn );}
return tn_;}
s501* s509::s541( const s269& s736, s278* s612, const wstring& s542 ){
if( s736.s1476() )
return s1230[s736.s1476()]->s369( s736, s612, s542 );
wstring s363 = s736.s297();
if( s363.substr(0,2) == L"[[" )
return s1230[s1214[s1050->s368()]]->s369( s736, s612, s542 );
else if( s363[0] == L'[' )
return s1230[s1214[s764->s368()]]->s369( s736, s612, s542 );
else if( s363.find( L"UVector[" ) == 0 )
return s1230[s1214[s787->s368()]]->s369( s736, s612, s542 );
else if( s363[0] == L'{' )
return s1230[s1214[s770->s368()]]->s369( s736, s612, s542 );
else if( s363.find( L"typealias" ) == 0 ) {
size_t pl = s363.find( L"(" );
wstring s361 = s4::s53( s363.substr( pl + 1, s363.size() - pl - 2 ), s4::s49 );
s1312( s736.s305(), s361 );
return s1230[s1214[s374::proto->s368()]]->s369( s736, s612, s542 );}
wstring s361 = L"";
s501* s717 = NULL;
if( s4::s89.find( s363[0] ) != string::npos )
s361 = s374( s306 ).s368();
else if( isdigit( s363[0] ) || s363[0] == L'-' )
return s350::s359( s306, s363, s542 );
else if( ( s717 = s1230[s1275]->s369( s736, s612, s542 ) ) )
return s717;
else {
size_t pl = s363.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s361 = s363.substr( 0, pl );}
else if( pl == string::npos )
s361 = s363;}
auto it = s1214.find( s361 );
if( it == s1214.end() ) {
auto it1 = s978.find( s361 );
if( it1 == end( s978 ) )
throw new s16( L"Type does not exist: " + s363, (uint32_t)s16::s17::s23 );
return new s399( s306, it1->second, s1396 );}
return s1230[it->second]->s369( s736, s612, s542 );}
s501* s509::s541( s1171 s354, s278* s612, const wstring& s542 ){
if( !s354 || s354 >= s1213.size() )
throw new s16( L"no type with such id: " + to_wstring( s354 ) );
s1171 type = s354;
if( s1218[type].s366() != type )
type = s1218[type].s366();
if( s1218[s354].s876().size() == 1 )
return s1230[type]->s370( s612 );
else {
return s1230[type]->s370( s612, s1218[s354].s876() );}}
const s501* s509::get( const wstring& s77, bool s543/*= true*/ ) const
{
wstring s361 = s77;
size_t pl = s77.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s77.find( L"0" ) == string::npos )
s361 = s77.substr( 0, pl );
auto s717 = s1214.find( s361 );
if( s717 == s1214.end() ) {
if( s543 )
throw new s16( L"1: symbol not found: " + s77 );
else
return NULL;}
return s1230[s717->second].s15<const s501*>();}
bool s509::s159( const std::wstring& s77 ) const{
if( s1214.find( s77 ) == s1214.end() )
return false;
return true;}
const wstring& s509::s855( s1171 n ) const{
if( n >= s1213.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1213[n];}
s1171 s509::s1110( const std::wstring& s361, bool s543 ) const{
auto it = s1214.find( s361 );
if( it == s1214.end() ) {
if( s543 )
throw new s16( L"no such type: " + s361,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1171 s509::s1111( const s868& vt, bool s543 ) const{
auto it = s1219.find( vt );
if( it == end( s1219 ) ) {
if( s543 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s868& s509::s1113( s1171 t ) const{
assert( t && t < s1218.size() );
return s1218[t];}
const s501* s509::s1107( s868::s979 t ) const{
assert( t && t < s1218.size() );
return s1230[t].s15<const s501*>();}
void s509::s840(){
size_t s789 = s350::s859() + 1;
for( size_t n = s789; n < s1213.size(); ++n ) {
s1214.erase( s1213[n] );
s1219.erase( s1218[n] );
s1004.erase( (s1171)n );}
s1213.erase( s1213.begin() + s789, s1213.end() );
s1230.erase( s1230.begin() + s789, s1230.end() );
s1218.erase( s1218.begin() + s789, s1218.end() );}
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
for( size_t n = 0; n < s1213.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s201 + 5 ) << s1213[n] << endl;
s1230[n]->s310( pd, s201 + 10 );}}
s500::s500( const s500& right )
: s576( right.s576 ), s560( right.s560 ), s562( right.s562 ){}
void s500::s519( s278* s961, bool s538/*= true*/ )
{
for( auto sym : s576 ) {
if( sym.second->s513() != s493 ) {
try {
sym.second->s519( s961 );}
catch( TDException* e ) {
e->s1187( TDException::Stage::s1133 );
s1115.s1065( e->Msg( 0 ) );
continue;}}}
if( s1115.s1021() )
return;
if( s538 ) {
for( auto sym : s576 ) {
if( sym.second->s513() == s493 )
sym.second.s15<Transd*>()->s519( s961, true );}}}
void s574::s1826( s268* s306 ){
for( auto sym : s582 ) {
if( sym.find( L"::" ) == string::npos )
s306->s1827( sym );}}
void s500::reset(){
s576.clear();}
void s500::copy( s500& t, s278* s612, s615* s611, s148 ap ) const{
t.s562 = s562;
for( s558::const_iterator it = s576.begin(); it != s576.end(); ++it ) {
if( it->second->s513() == s493 ) {
s615::s586 ct = it->second.s15<Transd*>()->s938();
assert( ct == s615::s591 || ct == s615::s590);
s911* ptr = new s911( *( s911* )&( *it->second ),
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
void s500::s1790( s500& t ) const{
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
throw new TDException( 0, s1848, NULL, s77 );
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
wstring s500::to_wstring( uint32_t s1740 ) const{
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
return pd->s579( mem, ref, s346 );
ref->s398( (s501*)pd->s523() );
ref->s397( pd );
return true;}
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod /*sym*/ ) {
s501* pd = it->second.first;
if( pd->s513() == s497 )
return pd->s579( mem, ref, L"" );
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
wstring s73( s1235, 1 );
s4::s58( l, s73, s156 );
s551[it->first] = new s544( pv, s156 );}}
void s549::s553( const std::wstring& s, s544& pl ){}
void s549::s554( const std::wstring& s, const std::wstring& s547 ){}
s533 s549::s555( const std::wstring& mem, const std::wstring& s518 ){
s550::iterator it = s551.find( mem );
if( it == s551.end() )
return s534;
return it->second->s583( s518 );}
s1171 s1687::s1425 = 0;
s1171 s1687::s1724 = 0;
s350::s355 s399::s362;
s350::s355 s379::s362;
s350::s355 s376::s362;
s350::s355 s375::s362;
s350::s355 s360::s362;
s350::s355 s373::s362;
s350::s355 s1465::s362;
s350::s355 s1704::s362;
s350::s355 s1453::s362;
s350::s355 s1749::s362;
s350::s355 s1779::s362;
s350::s355 s374::s362;
s350::s355 s323::s362;
s350::s355 s793::s362;
s350::s355 s1049::s362;
s350::s355 s332::s362;
s350::s355 s1553::s362;
s350::s355 s1448::s362;
s350::s355 s430::s362;
s350::s355 s1463::s362;
s350::s355 s400::s362;
s350::s355 s1256::s362;
s350::s355 s1040::s362;
s350::s355 s1267::s362;
s350::s355 s679::s362;
s350::s355 s527::s362;
s350::s355 s1451::s362;
s350::s355 s1461::s362;
s350::s355 s1574::s362;
s350::s355 s1576::s362;
size_t s350::s803 = 0;
s9<s399> s828;
s9<s379> s780;
s9<s376> s875;
s504 s375::proto;
s504 s360::proto;
s504 s373::proto;
s504 s1465::proto;
s504 s1704::proto;
s504 s1453::proto;
s504 s1749::proto;
s504 s1779::proto;
s504 s374::proto;
s504 s1267::proto;
s9<s430> s866;
s9<s1463> s1464;
s9<s323> s764;
s9<s793> s787;
s9<s1049> s1050;
s9<s332> s770;
s9<s1553> s1555;
s9<s1448> s1450;
s9<s400> s864;
s9<s1256> s1258;
s9<s1040> s1469;
s9<s527> s870;
s9<s1451> s1452;
s9<s1461> s1462;
s9<s679> s807;
s9<s906> s1264;
s9<s379> s380;
s9<s399> s946;
s9<s399> s381;
s9<s399> s382;
s9<s399> s383;
s9<s399> s950;
s9<s375> s384;
s9<s375> s385;
s9<s1574> s1575;
s9<s1576> s1577;
s9<s399> s1696;
template <class charT, charT s73>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s73; }
};
std::locale exprloc;
s501::~s501(){}
void s350::s834( s268* s306, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
if( !soft ) {
std::vector<s277*> l;
s828 = new s399( s306 );
s780 = new s379( s306 );
s375::proto = new s375( s306 );
s875 = new s376( s306 );
s360::proto = new s360( s306 );
s373::proto = new s373( s306 );
s1465::proto = new s1465( s306 );
s1704::proto = new s1704( s306 );
s1453::proto = new s1453( s306 );
s1749::proto = new s1749( s306 );
s1779::proto = new s1779( s306 );
s374::proto = new s374( s306 );
s1267::proto = new s1267( s306 );
s764 = new s323( s306 );
s787 = new s793( s306 );
s1050 = new s1049( s306 );
s770 = new s332( s306 );
s1555 = new s1553( s306 );
s1450 = new s1448( s306 );
s807 = new s679( s306 );
s864 = new s400( s306 );
s1258 = new s1256( s306 );
s1469 = new s1040( s306 );
s866 = new s430( s306 );
s1264 = new s906( s306 );
s870 = new s527( s306 );
s1452 = new s1451( s306 );
s1462 = new s1461( s306 );}
s306->s223( s828, L"NoValue" );
s306->s223( s780, L"Null" );
s306->s223( s875, L"Exception" );
s306->s223( s375::proto, L"Bool" );
s306->s223( s360::proto, L"Int" );
s306->s223( s373::proto, L"Double" );
s306->s223( s1465::proto, L"Long" );
s306->s223( s1704::proto, L"ULong" );
s306->s223( s1453::proto, L"Byte" );
s306->s223( s1749::proto, L"Char" );
s306->s223( s1779::proto, L"Object" );
s306->s223( s1267::proto, L"Position" );
s306->s223( s764, L"Vector" );
s306->s223( s787, L"UntypedVector" );
s306->s223( s1050, L"Tuple" );
s306->s223( s770, L"Index" );
s306->s223( s1555, L"HashIndex" );
s306->s223( s1450, L"ByteArray" );
s306->s223( s866, L"Directory" );
s306->s223( s864, L"Range" );
s306->s223( s1258, L"Filter" );
s306->s223( s1469, L"Seq" );
s306->s223( s807, L"TSDBase" );
s306->s223( s870, L"StringStream" );
s306->s223( s1452, L"ByteStream" );
s306->s223( s1462, L"FileStream" );
s306->s223( s1264, L"Lambda" );
s306->s223( s374::proto, L"String" );
if( !soft ) {
s803 = s374::proto->s366();
s380 = new s379( s306 );
s946 = new s399( s306, s499 );
s383 = new s399( s306, s499 );
s382 = new s399( s306, s499 );
s381 = new s399( s306, s499 );
s950 = new s399( s306, s499 );
s384 = new s375( s306, true );
s385 = new s375( s306, false );
s946->s1856( s7::s940 );
s383->s1856( s7::s453 );
s382->s1856( s7::s454 );
s381->s1856( s7::s455 );
s384->s1411();
s385->s1411();
s1696 = new s399( s306, s1284, s1396 );}}
s1239::s1239( const std::vector<s503>& v, s350* s616 )
:s612( s616 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s513() != s1173 ) {
s999.push_back( v[n] );
s1432.push_back( v[n]->s366() );}}}
bool s1239::operator==( const s1239& s547 ) const{
bool pend = s1432.empty();
bool send = s547.s1432.empty();
s1171 starred = 0;
size_t n = 0, k = 0;
bool s1421 = true;
s509* ptr = s547.s612 ? &s547.s612->Pass()->TR() : NULL;
while( !send || !pend ) {
s1421 = false;
s1171 s1319 = starred ? starred : (pend ? 0 : s1432[k]);
s1171 s1315 = send ? (s547.s1432.empty() ? 0 : s547.s1432[n-1]) : s547.s1432[n];
s277* s1712 = send ?
( s547.s999.empty() ? NULL : s547.s999[n - 1].s15<s277*>() ) :
s547.s999[n].s15<s277*>();
if( s1315 == s828->s366() )
s1315 = send ? s547.s999[n-1].s15<s399*>()->s1715() : 
s547.s999[n].s15<s399*>()->s1715();
const s868* s1436 = s547.s612 ? &s547.s612->s1339() : NULL;
if( s1319 >= s7::s1571 && s1319 < s7::s1729 && s1315 ) {
if( s1319 == s7::s1565 )
s1421 = true;
else if( s1319 == s7::s1570 ) {
s1171 pt1_ = s547.s999[n]->s1339().s366();
if( pt1_ == s1264->s366() /*&& pt2_ == s1275*/ )
s1421 = true;}
else if( s1319 == s7::s1566 ) {
if( s547.s612 && s1315 == s547.s612->s366())
s1421 = true;}
else if( s1319 == s7::s1567 ) {
if( s547.s612 && s1315 == ( (s336*)s547.s612 )->s327() )
s1421 = true;}
else if( s1319 == s7::s1567 ) {
if( s547.s612 && s1315 == ((s336*)s547.s612)->s327() )
s1421 = true;}
else if( s1319 == s7::s1568 ) {
if( s547.s612 && s1315 == ((s336*)s547.s612)->s1024() )
s1421 = true;}
else if( s1319 == s7::s1569 ) {
if( s547.s612 && s1712->s1716( ((s336*)s547.s612)->ValType() ) )
s1421 = true;}
else if( s1436 &&	s1315 == s1436->s366( (size_t)((int)0 - s1319 )) )
s1421 = true;}
else if( s1319 >= s7::s1729 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1319 );
if( ptr->s1341( s1315, s1688 ) )
s1421 = true;}
else {
if( s1712 && s1712->s1716( s1319 ) )
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
if( !starred && !pend && s1432[k] == s7::s1571 )
starred = s1432[k - 1];}
return s1421;}
bool s1239::operator<( const s1239& s547 ) const{
if( s1432.empty() ) return s547.s1432.size() > 0;
if( s547.s1432.empty() ) return false;
const s868* s1435 = s612 ? &s612->s1339() : NULL;
const s868* s1436 = s547.s612 ? &s547.s612->s1339() : NULL;
s1171 s1419 = 0, s1420 = 0;
s509* ptr = s547.s612 ? &s547.s612->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1432.size() && n < s547.s1432.size()*/; ++n ) {
if( s1432.size() == n )
return s547.s1432.size() > n;
if( s547.s1432.size() == n )
return false;
s1171 s1317 = s1419 ? s1419 : s1432[n];
s1171 s1320 = s1420 ? s1420 : s547.s1432[n];
if( s1317 >= s7::s1571 && s1317 <= s7::s1729 ) {
if( s1317 == s7::s1571 )
s1317 = s1419 = s1432[n - 1];
else if( s1317 == s7::s1565 )
continue;
else if( s1317 == s7::s1566 ) {
if( !s547.s612 )
return true;
s1317 = s547.s612->s366();}
else if( s1317 == s7::s1567 ) {
if( !s547.s612 )
return true;
s1317 = ( (s336*)s547.s612 )->s327();}
else if( s1435 )
s1317 = s1435->s366( (size_t)(int)0 - s1317 );}
else if( s1317 >= s7::s1729 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1317 );
if( ptr->s1341( s1320, s1688 ) )
return true;}
if( s1320 >= s7::s1571 && s1320 <= s7::s1729 ) {
if( s1320 == s7::s1571 )
s1320 = s1420 = s547.s1432[n - 1];
else if( s1320 == s7::s1565 )
continue;
else if( s1320 == s7::s1566 ) {
if( !s612 )
return true;
s1320 = s612->s366();}
else if( s1320 == s7::s1567 ) {
if( !s612 )
return true;
s1320 = ( (s336*)s612 )->s327();}
else if( s1436 )
s1320 = s1436->s366( (size_t)(int)0 - s1320 );}
else if( s1320 >= s7::s1729 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1320 );
if( ptr->s1341( s1317, s1688 ) )
return true;}
if( s1317 < s1320 )
return true;}
return false;}
wstring s1239::s1496( s268* s306 ) const{
wstring s717 = L"( ";
for( auto i : s1432 ) {
s717 += s306->TR().s855( i );
if( s717.back() != L')' ) s717 += L"()";
s717 += L" ";}
s717 += L")";
return s717;}
bool
s350::s351::s1306( /*s350* thi,*/ const s1239& s723 ) const
{
return std::find( s1302.begin(), s1302.end(), s723 ) != end( s1302 );}
s1171
s350::s401( const std::wstring& s357 ) const{
auto it = s356().find( s357 );
if( it == s356().end() )
throw new s16( L"No such operation: " + s368() +	L"::" + s357,
(uint32_t)s16::s17::s23 );
s1171 s717 = it->second->s514();
return s717;}
const s501*
s350::s523() const{
return (s501*)s306->TR().s1107( s366() );}
const vector<wstring>& 
s350::s1334( const wstring& s357 ) const{
auto ran = s356().equal_range( s357 );
if( ran.first == s356().end() )
throw new s16( L"No such method: " + s368() + L"::" + s357,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1266 s350::s1340( const std::wstring& s357 ) const{
s350::s351* s717 = NULL;
auto it = s356().find( s357 );
if( it != s356().end() )
s717 = it->second;
return s717 ? s1266( s717->s514(), s717->s1259(), s717->s1347() ) : s1266();}
s1266
s350::s1335( const wstring& s357, s1239& ap /*const vector<s1171>& s1388*/ ) const
{
auto ran = s356().equal_range( s357 );
if( ran.first == s356().end() )
throw new s16( L"No such method: " + s368() + L"::" + s357,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1329() )
throw new s16( L"", (uint32_t)s351::s1255::s1322 );
s351* s717 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1306( ap ) ) {
s717 = it->second;
break;}}
return s717 ? s1266( s717->s514(), s717->s1259(), s717->s1347() ) : s1266();}
s1266
s350::s1330( const wstring& s357, s1239& ap/*const vector<s1171>& s1388,
const vector<s503>& s280*/ )
{
auto ran = s356().equal_range( s357 );
s351* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1306( ap ) ) {
mi = it->second;
break;}}
s1266 s1385( mi->s514(), mi->s1259(), mi->s1347() );
if( mi )
s1385.s352 = ap.Subj()->s1331( s357, ap.s626() );
return s1385;}
s504 s350::s516( s501** s280, size_t s517 ){
return this;}
void s350::s1710( s501* p ){}
s501* s350::s359( s268* s306, const std::wstring& s363, const std::wstring& s346 ){
s269 s212( s363, NULL );
s501* s717 = NULL;
if( s363.find_first_not_of( L"-0123456789" ) == std::string::npos ||
s363.find( L"Int(" ) == 0 ) {
s717 = s360::proto.s15<s360*>()->s369( s212, NULL, s346 );}
if( !s717 ) {
s717 = s373::proto.s15<s1465*>()->s369( s212, NULL, s346 );
if( !s717  )
s717 = s1465::proto.s15<s1465*>()->s369( s212, NULL, s346 );
if( !s717 )
s717 = s1453::proto.s15<s1453*>()->s369( s212, NULL, s346 );}
return s717;}
#define s733 ((s360*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
s501* s373::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
s.find( L"." ) != std::string::npos ) {
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
wh = s7::s942;}
else {
s512 = s373::proto->s366();
wh = s7::s941;}}
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
s1856( s7::s941 );}
else
s156 = s306->TR().s1402();
s363 = s156;
pos = pend ? pend - pst : string::npos;
s512 = s373::proto->s366();}
s501* s373::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s373( s306, L"", pos );}
void s373::s519( const s278* s961 ){}
void s373::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s373::s1384, s1283,
{ s1239(), s1239( { s1288 } ), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"abs", new s351( L"abs", &s373::s419, s1283,
{ s1239( ) }, 0, 0 )));
s362.insert( make_pair( L"set", new s351( L"set", &s373::s402, s1286,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"sum", new s351( L"sum", &s373::s403, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"dif", new s351( L"dif", &s373::s404, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"mul", new s351( L"mul", &s373::s405, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"div", new s351( L"div", &s373::s406, s1283,
{ s1239( { s1687::s1425 } ) }, 1, 1 )));
s362.insert( make_pair( L"pow", new s351( L"pow", &s373::s407, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"sumeq", new s351( L"sumeq", &s373::s408, s1283,
{ s1239( { s1283 } ), s1239( { s1284, s7::s1571 } ) }, 1, 10 )));
s362.insert( make_pair( L"difeq", new s351( L"difeq", &s373::s409, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"muleq", new s351( L"muleq", &s373::s410, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"diveq", new s351( L"diveq", &s373::s411, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"poweq", new s351( L"poweq", &s373::s412, s1283,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"sqrt", new s351( L"sqrt", &s373::s421, s1283,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"nroot", new s351( L"nroot", &s373::s422, s1283,
{ s1239( { s1284 } ) }, 1, 1 )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s373::s413, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"less", new s351( L"less", &s373::s414, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"greater", new s351( L"greater", &s373::s415, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"leq", new s351( L"leq", &s373::s416, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"geq", new s351( L"geq", &s373::s417, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"neq", new s351( L"neq", &s373::s418, s1275,
{ s1239( { s1283 } ) }, 1, 1 )));
s362.insert( make_pair( L"dcmp", new s351( L"dcmp", &s373::s425, s1284,
{ s1239( { s1283, s1283 } ) }, 2, 2 )));
s362.insert( make_pair( L"dcmpr", new s351( L"dcmpr", &s373::s426, s1284,
{ s1239( { s1283, s1283 } ) }, 2, 2 )));
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s373::s427, s1284,
{ s1239(), s1239( { s1284 } ) }, 0, 1 )));
s306->TR().s1301( s512, s7::s1585, s1687::s1425 );}
s277* s373::s349() const{
return new s373( *this );}
void s373::s371( s277* p ) const{
if( p->s366() == s360::proto->s366() )
*( (s360*)p )->s372() = (int)s363;
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = s363;
else if( p->s366() == s1275 )
*( (s375*)p )->s372() = ( s363 != 0.0 );
else
throw new s16( L"No conversion to type " + s368() );}
std::wstring s373::to_wstring( uint32_t s1740 ) const{
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
lv.s363 = (s1558)*( (s360*)p )->s372();
else if( p->s366() == s1275 )
lv.s363 = ( s1558 )*( (s375*)p )->s372();
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
pd->s363 += ( s1558 )*( (s360*)p )->s372();}
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
int s1498 = -1;
if( s517 == 3 )
s1498 = (int)*s280[2];
double dv = ( (s373*)DR )->s363;
int s717 = (int)dv;
if( s1498 < 0 )
*( (s360*)s280[0] )->s372() = s717;
else if( s1498 == 0 ) 
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
return 1;
return -1;}
inline
int dcmp_( double d1, double d2, double dif ){
double s88 = fabs( d1 - d2 );
if ( s88 < dif )
return 0;
if ( d1 < d2 )
return 1;
return -1;}
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
s1856( s7::s941 );
s512 = s1275;}
s375::s375( const s375& right )
: s350( right.s306, right.ns, NULL ), s363( right.s363 ){
s512 = s1275;
wh = right.wh;}
s375::s375( s268* s306, bool b )
: s350( s306, NULL, NULL ), s363( b ){
if( s375::proto.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = s1275;
s1856( s7::s941 );}}
void s375::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s375::s402, s1286,
{ s1239( { s1275 } ) }, 1, 1, false )));
s362.insert( make_pair( L"new", new s351( L"new", &s375::s1384, s1275,
{ s1239(), s1239( { s1275 } ), s1239( { s1288 } ), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"not", new s351( L"not", &s375::s428, s1275,
{ s1239( ) }, 0, 0, true )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s375::s413, s1275,
{ s1239( { s1275 } ) }, 1, 1, true )));}
void s375::s519( const s278* s961 ){
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
if( p->s366() == s1275 )
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
else if( p->s366() == s1275 )
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
s512 = s875.s13() ? 0 : s875->s366();}
s376::s376( const s376& r )
: s350( r.s306, NULL, NULL ), s79( r.s79 ){
s512 = r.s512;
wh = r.wh;}
void s376::s364(){
s362.insert( make_pair( L"report", new s351( L"report", &s376::s843, s1286,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"str", new s351( L"str", &s376::s528, s1288,
{ s1239() }, 0, 0 )));}
void s376::s519( const s278* s961 ){}
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
inline void s376::s843( s501** s280, size_t s517 ){
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
if( s780.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = s780->s366();
s1856( s7::s941 );}}
void s379::s519( const s278* s961 ){}
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
throw new s16( L"not implemented" );}
bool s379::operator==( const s501* p ) const{
return ( this == p );}
bool s379::operator<( const s501* p ) const{
return false;}
s399::s399( s268* s306, traitnum_t tn, s489 pc ) 
: s350( s306, NULL, NULL ), s1426( tn ){
s511 = pc;
s512 = s828.s13() ? 0 : s828->s366(); }
void s399::s519( const s278* s961 ){}
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
s399::s1716( s1171 s646 ) const{
return s306->TR().s1709( s1426, s646 );}
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
s1779::s1779( s268* s306, s278* s612, const std::wstring& s78, const s269* ast_ )
: s350( s306, s612, ast_ ){
if( s78.size() ) {
load( s78, false );}
if( !s512 )
s512 = ( s1779::proto.s13() ? 0 : s1779::proto->s366() );
if( !s78.empty() )
s1856( s7::s941 );}
s1779::s1779( s268* s306, s278* s612, const s146* s1821, const s269* ast_ )
: s350( s306, s612, ast_ ){
if( s1821->s159( s7::s480 ) ) {
wstring sname = s4::s53( s269::s308( *s1821, s7::s480 ),
s49 );
(( s146*)s1821)->s162( L"name", new s144( sname ) );
(( s146*)s1821)->s1808( s7::s480 );}
s1819( s1821, s500::s149 );}
s1779::s1779( const s1779& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s655( right.s655 ){
s512 = s1779::proto->s366();}
void s1779::s364(){
s362.insert( make_pair( L"get-Int", new s351( L"get-Int", &s1779::s1813, s1284,
{ s1239( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"get-String", new s351( L"get-String", &s1779::s1814, s1288,
{ s1239( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"load", new s351( L"load", &s1779::s1818, s1286,
{ s1239( { s1288 } ) }, 1, 1, true )));
s362.insert( make_pair( L"load-from-file", new s351( L"load-from-file", &s1779::s1816, s1286,
{ s1239( { s1288 } ), s1239( { s1288, s1288 } ) }, 1, 2, true )));}
void s1779::s519( const s278* s961 ){}
s501* s1779::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1779( s306 );}
s501* s1779::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find( L"Object(" ) == 0 ) {
return new s1779( s306, s612, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s370( s612, std::vector<s277*>(), &s736 );}
return NULL;}
s1171 s1779::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get" ) {
auto it = s655.get( l[0]->to_wstring() );
s717 = it->s366();}
return s717;}
void s1779::load( const wstring& s78, bool s1811 ){
TDException s1060( s7::s1775, s1019, s627(), L"Failed to load object" );
s1036 s1159 = new s1033( s78, s1811 );
vector<s9<s146>> s692;
s1159->read( s692, L"" );
if( s692.size() != 1 )
throw s1060.s1098( L"wrong object data: the source contains " + std::to_wstring( s692.size() ) + L"objects"  );
s146* obj = s692[0];
if( obj->s159( s7::s480 ) ) {
wstring sname = s4::s53( s269::s308( *obj, s7::s480 ),
s49 );
obj->s162( L"name", new s144( sname ) );}
s1819( obj );}
void s1779::s1819( const s146* obj, s500::s148 ap ){
vector<pair<wstring, s145>> s147;
obj->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1035 past = new s269( s147[n].first, *s147[n].second );
s501* dv = s306->TR().s541( *past, (s278*)this, L"::" );
dv->s526( s147[n].first );
dv->s1413();
s655.s564( s147[n].first, dv, ap );}}
void s1779::s1809( s500::s558& sm ) const{
const s500::s558& tb = s655.Table();
s500::s558::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s513() == s493 )
(void)0;
else {
s501* dv = (s501*)it->second->s349();
sm.insert( make_pair( it->first, dv ));}}}
s277* s1779::s349() const{
return new s1779( *this );}
void s1779::s371( s277* p ) const{
if( p->s366() == s1779::proto->s366() )
((s1779*)p)->s655 = s655;
else
throw new s16( L"No conversion to type " + s368() );}
#undef s733
#define s733 ((s1779*)(s502*)*s280)
inline void s1779::s1813( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
*((s360*)*s280)->s372() = (int)*( (s1779*)DR )->s655.get( s155 );}
inline void s1779::s1814( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
*((s374*)*s280)->s372() = ( (s1779*)DR )->s655.get( s155 )->to_wstring();}
inline void s1779::s1837( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
s360* pd  = (s360*)( (s1779*)DR )->s655.get( s155 );
*pd->s372() = (int)*s280[3];}
inline void s1779::s1839( s501** s280, size_t s517 ){
wstring s155 = s280[2]->to_wstring();
s374* pd  = (s374*)( (s1779*)DR )->s655.get( s155 );
*pd->s372() = s280[3]->to_wstring();}
inline void s1779::s1818( s501** s280, size_t s517 ){
s1779* po = (s1779*)DR;
wstring s78 = s280[2]->to_wstring();
po->load( s78, false );}
inline void s1779::s1816( s501** s280, size_t s517 ){
s1779* po = (s1779*)DR;
wstring s193 = s280[2]->to_wstring();
po->load( s193, true );}
void s1779::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << to_wstring();}
size_t s1779::s330() const{
return (size_t)this; //hash<bool>{}( s363 );
}
inline bool s1779::operator==( const s501* p ) const{
return this == p; // ( s655 == ( (s1779*)p )->s655 );
}
inline bool s1779::operator<( const s501* p ) const{
return this < p; // ( s655 < ( (s1779*)p )->s655 );
}
wstring s1779::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"Object: { \n";
s717 += s655.to_wstring( s1740 );
s717 += L"\n }";
return s717;}
s386::s386( const std::wstring& s, s268* s306, s489 cat )
: s502( s306, cat ), s387( s ), s391( 0 ){
assert( cat == s490 || cat == s492 || cat == s499 || cat == s1173 );
if( cat == s490 ) {
if( s[0] == L':' ) {
s511 = s1173;
s512 = s828->s366();
s388 = s828.s15<s501*>();}
else if( /*s388.s14() &&*/ s306->s226( *this ) ){
s511 = s499;
s512 = s828->s366();}
else
s511 = s492;}}
s386::s386( const s386& right )
: s502( right.s306, right.s511 ), s387( right.s387 ), s389( right.s389 ), s391( 0 ){
if( s511 == s499 )
s388 = right.s388;}
void s386::s519( const s278* s611 ){
if( false && s306->s226( *this ) ) {
s511 = s499;
s512 = s828->s366();}
else {
if( !s611->s579( s387, this, s611->s899() ) ) {
if( s511 == s1173 )
return;
throw new TDException( 0, s1017, NULL, s387 );}
if( s389 )
s512 = s389->s366();
else if( s511 == s1505 )
s512 = s388.s15<s386*>()->s392()->s366();
else
assert( 0 );}
s1413();}
s501* s386::s392() const{
if( s511 == s1173 )
return s388.s15<s501*>();
else if( s511 == s1505 )
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
void s386::s1078( const std::vector<std::wstring> &s877 ){
auto it = std::find( begin( s877 ), end( s877 ), s643() );
if( it != end( s877 ) ) {
s511 = s1173;
s512 = s828->s366();
s391 = std::distance( begin( s877 ), it );
s388 = new s360( NULL, (int)s391 ); //s828.s15<s501*>();
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
void s386::s1511( s386* ptr ){
s511 = s1505;
s390.clear();
s391 = 0;
s388 = ptr;
s389 = NULL;}
void s386::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"DataRef : " << s387;}
template<class s1479, class Der>
s350::s355 s1471<s1479, Der>::s362;
template<class s1479, class Der>template <class s1705, class s1706>
void s1471<s1479, Der>::s1707( s501* src, s501* s827 ){
*((s1705*)s827)->s372() = (s1706) ( (Der*)src )->s363;}
template <class s1479, class Der>
s501* s1471<s1479, Der>::s1711( const s501* p ) const{
Der* s717 = new Der( p->Pass() );
if( p->s1716( s366() ) )
p->s371( s717 );
s717->s1413();
return s717;}
template <class s1479, class Der>
size_t s1471<s1479, Der>::s330() const{
return (size_t)s363;}
template <class s1479, class Der>
inline bool s1471<s1479, Der>::operator==( const s501* p ) const{
return ( (Der*)p )->s363 == s363;}
template <class s1479, class Der>
inline bool s1471<s1479, Der>::operator<( const s501* p ) const{
return s363 < ( (Der*)p )->s363;}
template <class s1479, class Der>
void s1471<s1479, Der>::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s363 << endl;}
#define s1700 Der::proto->s366()
template <class s1479, class Der>
void s1471<s1479, Der>::s364(){
s362.insert( make_pair( L"abs", new s351( L"abs", &s1471<s1479, Der>::s419, s1700,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s1471<s1479, Der>::s402, s1286,
{ s1239( { /*Der::proto->s366()*/ s1687::s1425 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"sum", new s351( L"sum", &s1471<s1479, Der>::s403, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"dif", new s351( L"dif", &s1471<s1479, Der>::s404, s1700,
{ s1239( { s1687::s1425 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"mul", new s351( L"mul", &s1471<s1479, Der>::s405, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"div", new s351( L"div", &s1471<s1479, Der>::s406, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"pow", new s351( L"pow", &s1471<s1479, Der>::s407, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"pow", new s351( L"pow", &s1471<s1479, Der>::s407, s1283,
{ s1239( { s1283 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"sumeq", new s351( L"sumeq", &s1471<s1479, Der>::s408, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"difeq", new s351( L"difeq", &s1471<s1479, Der>::s409, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"muleq", new s351( L"muleq", &s1471<s1479, Der>::s410, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"diveq", new s351( L"diveq", &s1471<s1479, Der>::s411, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1, false ) ) );
s362.insert( make_pair( L"not", new s351( L"not", &s1471<s1479, Der>::s428, s1275,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s1471<s1479, Der>::s413, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"less", new s351( L"less", &s1471<s1479, Der>::s414, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"greater", new s351( L"greater", &s1471<s1479, Der>::s415, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"leq", new s351( L"leq", &s1471<s1479, Der>::s416, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"geq", new s351( L"geq", &s1471<s1479, Der>::s417, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"neq", new s351( L"neq", &s1471<s1479, Der>::s418, s1275,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"mod", new s351( L"mod", &s1471<s1479, Der>::s420, s1700,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"sqrt", new s351( L"sqrt", &s1471<s1479, Der>::s421, s1283,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"nroot", new s351( L"nroot", &s1471<s1479, Der>::s422, s1283,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"to-Double", new s351( L"to-Double", &s1471<s1479, Der>::s423, s1283,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Byte", new s351( L"to-Byte", &s1471<s1479, Der>::s1773, s1475,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s1471<s1479, Der>::s427, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-Long", new s351( L"to-Long", &s1471<s1479, Der>::s1722, s1701,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"to-ULong", new s351( L"to-ULong", &s1471<s1479, Der>::s1723, s1702,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s1471<s1479, Der>::s424, s1700,
{ s1239() }, 0, 0, false ) ) );}
template<class s1479, class Der>
s1171 s1471<s1479, Der>::
s1331( const std::wstring& s1728, const std::vector<s503>& l ) const{
s1171 s717 = 0;
if( 0 && s1728 == L"mod" )
s717 = this->s366();
return s717;}
#undef s733
#define s733 ((Der*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
template<class s1479, class Der>
inline void s1471<s1479, Der>::s402( s501** s280, size_t n ){
s280[2]->s371( s280[1] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s419( s501** s280, size_t s517 ){
s1479 t = ( (Der*)DR )->s363;
if( t >= 0 )
s733->s363 = t;
else
s733->s363 = -t;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s403( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 + s733->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s404( s501** s280, size_t s517 ){
if( s517 == 2 )
s733->s363 = -( (Der*)DR )->s363;
else {
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 - s733->s363;}}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s405( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 * s733->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s406( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 = ( (Der*)DR )->s363 / s733->s363;
}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s407( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
s733->s363 =(s1479) std::pow( (double)( (Der*)DR )->s363, (double)s733->s363 );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s408( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 += s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s409( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 -= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s410( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 *= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s411( s501** s280, size_t s517 ){
s280[2]->s371( s280[0] );
( (Der*)DR )->s363 /= s733->s363;
s733->s363 = ( (Der*)DR )->s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s413( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 == tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s428( s501** s280, size_t s517 ){
if( ((bool)( (Der*)DR )->s363) == false )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s414( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 < tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s415( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 > tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s416( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 <= tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s417( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 >= tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = true;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s418( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( ( (Der*)DR )->s363 != tmp.s363 )
*s734->s372() = true;
else
*s734->s372() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s420( s501** s280, size_t s517 ){
Der tmp;
s280[2]->s371( &tmp );
if( tmp.s363 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s733->s363 = ((Der*)DR)->s363 % tmp.s363;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s421( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = ::sqrt( (double)*DR );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s422( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = ::pow( ((Der*)DR)->s363, 1.0 / (double)*PARN( 2 ) );
}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s423( s501** s280, size_t s517 ){
*( (s373*)s280[0] )->s372() = (double)*DR;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1773( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s427( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1722( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1723( s501** s280, size_t s517 ){
s280[1]->s371( s280[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1676( s501** s280, size_t s517 ){
*( (s374*)s280[0] )->s372() = DR->to_wstring();}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s424( s501** s280, size_t s517 ){
int i;
wstring s95 = L"";//( (s374*)s280[2] )->to_wstring();
wstring si = consutils::s103( s95, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s733->s363 = i;}
s360::s360( s268* s306 )
: s1471( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1558)s306->TR().s1408();
s1856( s7::s942 );}
s360::s360( s268* s306, int i )
: s1471( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
wh = s7::s942;}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s360::s360( const s360& r )
: s1471( r ){}
s360::s360( s268* s306, const std::wstring& s, size_t& pos )
: s1471( s306, NULL, NULL ){
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
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
if( s == L"-0" )
return s1696;
size_t pos = 0;
try {
s717 = new s360( s306, s, pos );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
s717 = NULL;
else
throw e;}}
else if( s.find( L"Int(" ) == 0 ) {
size_t pos = 0;
s717 = new s360( s306, s.substr( 4, s.size() - 5 ), pos );}
else if( s.find( L"Int" ) == 0 ) {
s717 = s370( NULL, std::vector<s277*>(), &s736 );}
return s717;}
void s360::s364(){
s306->TR().s1301( s512, s7::s1585, s1687::s1425 );
s306->TR().s1301( s512, s7::s1699, s1687::s1724 );
s1471<int32_t, s360>::s364();
s362 = s1471<int32_t, s360>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s360::s1384, s1284,
{ s1239(), s1239( { s1288 } ), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1708( s512, s1465::proto->s366() );}
s501* s360::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s360( s306, L"", pos );}
void s360::s519( const s278* s961 ){}
inline bool
s360::s1716( s1171 s646 ) const{
if( ( s646 == s1702 && s363 >= 0 ) ||
( s646 == s1475 && s363 >= 0 && s363 <= 255 ) )
return true;
return s277::s1716( s646 );}
s277* s360::s349() const{
return new s360( *this );}
void s360::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s360*)p)->s372() = s363;
else if( p->s366() == s1475 )
*((s1453*)p)->s372() = s363;
else if( p->s366() == s1701 )
*((s1465*)p)->s372() = s363;
else if( p->s366() == s1702 )
*((s1704*)p)->s372() = s363;
else if( p->s366() == s1275 )
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
lv.s363 = ( s1558 )*( (s373*)p )->s372();
else if( p->s366() == s1275 )
lv.s363 = ( s1558 )*( (s375*)p )->s372();
else
throw new s16( L"no conversion to Int from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Int() constructor" );}
plv->s1413();
s280[0] = plv;}
wstring s360::to_wstring( uint32_t s1740 ) const {
wstring s717;
if( s363 > 0 && ( s1740 & s1735 ) )
s717 = L"+";
if( s1740 & s1734 )
s717 += s4::s1739( s363 );
else
s717 += std::to_wstring( s363 ); 
return s717;}
s1465::s1465( s268* s306 )
: s1471( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = s306->TR().s1408();
s1856( s7::s942 );}
s1465::s1465( s268* s306, int64_t i )
: s1471( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1465::s1465( const s1465& r )
: s1471( r ){}
s1465::s1465( s268* s306, const std::wstring& s, size_t& pos )
: s1471( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s156 = 0;
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
s363 = (int64_t)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1465::s364(){
s1471<int64_t, s1465>::s364();
s362 = s1471<int64_t, s1465>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1465::s1384, s1701,
{ s1239(), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1585, s1687::s1425 );
s306->TR().s1301( s512, s7::s1699, s1687::s1724 );}
s501* s1465::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1465( s306, L"", pos );}
void s1465::s519( const s278* s961 ){}
s277* s1465::s349() const{
return new s1465( *this );}
void s1465::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s1465*)p)->s372() = s363;
else if( p->s366() == s1284 )
*((s360*)p)->s372() = (s360::s1558)s363;
else if( p->s366() == s1702 )
*((s1704*)p)->s372() = s363;
else if( p->s366() == s1275 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1465::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1465( s306, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1465( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1465::s1384( s501** s280, size_t s517 ){
s1465* plv = new s1465( ( (s1465*)s280[1] )->s306, (s1558)0 );
s1465& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if (s517 == 3){
s501* p = s280[2];
if( p->s366() == s360::proto->s366() )
lv.s363 = *( (s360*)p )->s372();
else if( p->s366() == s1283 )
lv.s363 = (s1558)*( (s373*)p )->s372();
else if( p->s366() == s1275 )
lv.s363 = (s1558)*( (s375*)p )->s372();
else
throw new s16( L"no conversion to Long from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1413();
s280[0] = plv;}
wstring s1465::to_wstring( uint32_t s1740 ) const{
wstring s717;
if( s363 > 0 && ( s1740 & s1735 ) )
s717 = L"+";
if( s1740 & s1734 )
s717 += s4::s1739( s363 );
else
s717 += std::to_wstring( s363 );
return s717;}
s1704::s1704( s268* s306 )
: s1471( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = s306->TR().s1408();
s1856( s7::s942 );}
s1704::s1704( s268* s306, int64_t i )
: s1471( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1704::s1704( const s1704& r )
: s1471( r ){}
s1704::s1704( s268* s306, const std::wstring& s, size_t& pos )
: s1471( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1720( pst, &s156, &pend ) ) {
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
void s1704::s364(){
s1471<s1558, s1704>::s364();
s362 = s1471<s1558, s1704>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1704::s1384, s1702,
{ s1239(), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"abs", new s351( L"abs", &s1704::s419, s1702,
{ s1239(), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s362.insert( make_pair( L"dif", new s351( L"dif", &s1704::s404, s1702,
{ s1239(), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1585, s1687::s1425 );
s306->TR().s1301( s512, s7::s1699, s1687::s1724 );}
s501* s1704::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1704( s306, L"", pos );}
void s1704::s519( const s278* s961 ){}
s277* s1704::s349() const{
return new s1704( *this );}
void s1704::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s1704*)p)->s372() = s363;
else if( p->s366() == s1701 )
*((s1465*)p)->s372() = s363;
else if( p->s366() == s1284 )
*((s360*)p)->s372() = (s360::s1558)s363;
else if( p->s366() == s1275 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1704::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1704( s306, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1704( s306, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1704::s1384( s501** s280, size_t s517 ){
s1704* plv = new s1704( ( (s1704*)s280[1] )->s306, (s1558)0 );
s1704& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if (s517 == 3){
s501* p = s280[2];
if( p->s366() == s360::proto->s366() )
lv.s363 = *( (s360*)p )->s372();
else if( p->s366() == s1465::proto->s366() )
lv.s363 = *( (s1465*)p )->s372();
else if( p->s366() == s1283 )
lv.s363 = (s1558)*( (s373*)p )->s372();
else if( p->s366() == s1275 )
lv.s363 = (s1558)*( (s375*)p )->s372();
else
throw new s16( L"no conversion to ULong from type: " + p->s368() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1413();
s280[0] = plv;}
wstring s1704::to_wstring( uint32_t s1740 ) const{
wstring s717;
if( s363 > 0 && ( s1740 & s1735 ) )
s717 = L"+";
if( s1740 & s1734 )
s717 += s4::s1739( s363 );
else
s717 += std::to_wstring( s363 );
return s717;}
s1453::s1453( s268* s306 )
: s1471( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1558)s306->TR().s1408();
s1856( s7::s942 );}
s1453::s1453( s268* s306, tdbyte_t i )
: s1471( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1453::s1453( const s1453& r )
: s1471( r.s306, r.ns, NULL ){
wh = r.wh;
s512 = r.s512;}
s1453::s1453( s268* s306, const std::wstring& s, size_t& pos )
: s1471( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s63( pst, &s156, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1856( s7::s941 );}
else
s156 = s306->TR().s1408();
s363 = (int)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1453::s364(){
s1471<tdbyte_t, s1453>::s364();
s362 = s1471<tdbyte_t, s1453>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1453::s1384, s1475,
{ s1239(), s1239( { s1687::s1425 } ) }, 0, 1 ) ) );
s306->TR().s1301( s512, s7::s1585, s1687::s1425 );
s306->TR().s1301( s512, s7::s1699, s1687::s1724 );}
s501* s1453::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1453( s306, L"", pos );}
void s1453::s519( const s278* s961 ){}
s277* s1453::s349() const{
return new s1453( *this );}
void s1453::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*((s360*)p)->s372() = s363;
else if( p->s366() == s1701 )
*((s1465*)p)->s372() = s363;
else if( p->s366() == s1702 )
*((s1704*)p)->s372() = s363;
else if( p->s366() == s1275 )
*( (s375*)p )->s372() = (s363 != 0);
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1453::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1453( s306, s, pos );
}*/
if( s736.s1476() == s366() )
return new s1453( s306, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1453( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
inline void s1453::s1384( s501** s280, size_t s517 ){
s1453* plv = new s1453( ( (s1453*)s280[1] )->s306, 0 );
s1453& lv = *plv;
if( s517 == 2 )
lv.s363 = 0;
else if( s517 == 3 )
s280[2]->s371( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1413();
s280[0] = plv;}
s1749::s1749( s268* s306 )
: s1471( s306, NULL, NULL ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s363 = (s1558)s306->TR().s1408();
s1856( s7::s942 );}
s1749::s1749( s268* s306, wchar_t i )
: s1471( s306, NULL, NULL ){
if( proto.s13() ) {
s512 = 0;
s1856( s7::s942 );}
else {
s512 = proto->s366();
s363 = i;
s1413();}}
s1749::s1749( const s1749& r )
: s1471( r.s306, r.ns, NULL ){
wh = r.wh;
s512 = r.s512;}
s1749::s1749( s268* s306, const std::wstring& s, size_t& pos )
: s1471( s306, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s156 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s63( pst, &s156, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1856( s7::s941 );}
else
s156 = s306->TR().s1408();
s363 = (int)s156;
pos = pend ? ( pend - pst ) : string::npos;
s512 = proto->s366();}
void s1749::s364(){
s1471<wchar_t, s1749>::s364();
s362 = s1471<wchar_t, s1749>::s356();}
s501* s1749::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
size_t pos = 0;
return new s1749( s306, L"", pos );}
void s1749::s519( const s278* s961 ){}
s277* s1749::s349() const{
return new s1749( *this );}
void s1749::s371( s277* p ) const{
if( p->s366() == proto->s366() )
*( (s360*)p )->s372() = s363;
else if( p->s366() == s1701 )
*( (s1465*)p )->s372() = s363;
else if( p->s366() == s1702 )
*( (s1704*)p )->s372() = s363;
else if( p->s366() == s1275 )
*( (s375*)p )->s372() = ( s363 != 0 );
else if( p->s366() == s1283 )
*( (s373*)p )->s372() = (double)s363;
else
throw new s16( L"no conversion from " + s368() + L"to " + p->s368() );}
s501* s1749::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1453( s306, s, pos );
}*/
if( s736.s1476() == s366() )
return new s1749( s306, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1749( s306, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s370( NULL, std::vector<s277*>(), &s736 );}
return 0;}
const wstring s488 = L"";
s500 s719;
s278::s278( s268* s306, s1171 s354, s489 pc/* = s490*/, const s269* ast_ )
: s501( s306, pc, ast_, NULL ), s652(NULL), s653(NULL), 
s1840( s7::s1778, s306, s492 ), s361( s488 ), //s661( s719 ),
s656( NULL )//, s1531( ++s1532 )
{
s652 = this;
s512 = s354;}
s278::s278( const s278& proto, std::vector<s503>& s740, const s269* ast_ )
: s501( proto.s306, s498, ast_, proto.ns ), s652( &proto ), s653(NULL), 
s1840( s7::s1778, s306, s492 ), s361( proto.s361 ),
s656( proto.s656 ), //s661( s719 ),
s658( proto.s658 )//, s1531( ++s1532 )
{
s512 = proto.s512;
if( s511 == s496 )
s511 = s498;
if( proto.s653 )
proto.s653->s672( this );
proto.s655.copy( s655, this, NULL, s500::s150 );
for( size_t n = 0; n < s658.size(); ++n )
s657.push_back( s655.get( s658[n] ) );
if( s740.size() ) {
s911* p = (s911*) s655.get( s7::s444 );
p->s620( s740 );
p->s519( this, false );
p->s516( 0, 0 );}}
s278::s278( const wstring& s708, s268* s306, s489 pc, const s269* ast_ )
: s501( s306, pc, ast_, NULL ), s652(NULL), s653(NULL), 
s1840( s7::s1778, s306, s492 ), s361( s488 ), s284( s708 ),
s656( NULL )//, s1531( ++s1532 )//, s661( *new s500() )
{
s652 = this;}
s278::s278( s269& s736, s268* s306, s489 pc, s278* ns_, s559 am,
s650& cl, s649& cnl, s651& al )
: s501( s306, pc, &s736, ns_ ), s652(NULL), s653( NULL ), 
s1840( s7::s1778, s306, s492 ), s361( s736.s305() ), s284( s736.s304() ),
s655( am ), s656( NULL )//, s1531( ++s1532 ) //,s661( *new s500() )
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
s278::s769( const wstring& f ) const{
return s655.s159( f );}
void s278::s157( s269& s736 ){
s269::s281& s737 = s736.s299();
s269::s281::iterator it = s737.begin();
for( ; it != s737.end(); ++it ) {
s269* node = it->second;
if( node->s303() == s230 ) {
wstring s77 = node->s305();
lang::s685( s77 );
if( s77 == s7::s458 )
s674( *node );
else if( s77 == s7::s485 )
s666( *node );
else if( s77 == s7::s1023 )
s1064( *node );
else {
size_t s721 = s77.find_first_of( s4::s49 );
bool s1347 = false;
if( s721 != string::npos ) {
vector<wstring> s720;
s4::s58( s77, wstring( 1, s77[s721] ), s720 );
if( s720.size() > 2 )
throw new s16( L"malformed object declaration: " + s77 );
if( s720[0] == s7::s1263 ) {
s1347 = true;}}
s501* dv = NULL;
try {
dv = s306->TR().s541( *node, this, s284 );}
catch( s16* e ) {
e->s30( L"while constructing object member: " + s77 );
throw e;}
dv->s526( node->s305() );
dv->s1411( s1347 );
try {
s655.s564( node->s305(), dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s284 + L"::" + node->s305() );}
throw e;}
s657.push_back( dv );
s658.push_back( node->s305() );}}
else if( node->s303() == s232 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s278* ob = (s278*)s655.get( it->first );
ob->s157( *it->second );}}
else if( node->s303() == s233 ) {
s501* dv = new s374( s306, node->s297(), node );
dv->s526( node->s305() );
dv->s1411( true );
wstring s1851 = node->s305();
if( node->s305() == s7::s480 )
s1851 = L"name";
try {
s655.s564( s1851, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s284 + L"::" + node->s305() );}
throw e;}
s657.push_back( dv );
s658.push_back( s1851 );}}
it = s737.begin();
for( ; it != s737.end(); ++it ) {
s269* node = it->second;
if( node->s303() == s231 ) {
try {
s506 func = s615::s623( *node, s306, this,
node->s305(), s284 );
s655.s564( func->s305(), func.s15<s501*>() );
s657.push_back( func );
s658.push_back( func->s305() );}
catch( TDException* e ) {
e->s1187( TDException::Stage::s1132 );
e->s30( L"while compiling function '" +s284 + L"::" + node->s305() + L"'" );
s1115.s1065( e->Msg( 0 ) );}}}
if( s511 == s496 ) {
s1527* s1535 = new s1527( s306, this, NULL, NULL );
s655.s564( s7::s1525, s1535 );
s657.push_back( s1535 );
s658.push_back( s7::s1525 );}}
void s278::s519( const s278* s961 ){
if( s511 == s496 || s511 == s497 ) {
if( s654.size() ) {
s653 = (s278*)s306->s227( s654, s961->s899() );
s653->s656->copy( *s656 );}
if( s656 )
s656->s519( s306, s284 );
else
s656 = s652->s656;
s655.s519( /*s961*/this, (s511 == s496));
}
else {
if( s306->s1497() && s655.s159( s7::s444 ) ) {
vector<s502*> s280;
s280.push_back( this );
s911* p = (s911*) s655.get( s7::s444 );
if( p->s644() == s7::s942 )
p->s519( s961, true );
else
p->s621( s961 );
if( s513() == s498 )
p->s516( (s501**)&s280[0], 1 );}
s656 = s652->s656;}
ns = (s278*)s961;}
void s278::s1826(){
if( s513() != s497 || s644() == s7::s941 )
return;
if( s655.s159( s7::s443 ) ) {
vector<s503> s280;
s280.push_back( this );
s911* p = (s911*) s655.get( s7::s443 );
p->s519( (s278*)ns, true );
p->s620( s280 );
p->s516( (s501**)&s280[0], 1 );}
if( s656 ) 
s656->s1826( s306 );
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
void s278::s1064( s269& s736 ){
wstring s1093 = L"wrong syntax of class attributes: " + s736.s297();
s504 dv = s306->TR().s541( s736, this, s284 );
if( dv->s366() != s764->s366() )
throw new s16( s1093 );
vector<s503>& v = dv.s15<s323*>()->s328();
for( auto s_ : v ) {
wstring s = s_.s15<s374*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s1093 );
wstring cat = s4::s53( s.substr( 0, pl ), s4::s49 );
vector<wstring> s156;
s4::s58( s.substr( pl + 1 ), L",", s156 );}}
bool s278::s579( const wstring& sym_, 
s386* ref, const wstring& s346 ) const{
bool s717 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s718 = sym_.substr( 0, pl );
s278* ob = ((s278*)s670( s718, s346, false ));
if( !ob && s718 == s7::s1778 )
ob = (s278*)this;
if( ob ) {
s386 s1835( *ref );
s717 = ob->s579( sym, &s1835, s346 );
if( s717 ) {
if( !ref->s395() )
ref->s397( ( s501* )this );
ref->s394( s668( s718 ), ob );
ob->s579( sym, ref, s346 );}}
else {
if( s656 )
s717 = s656->s579( sym_, ref );}}
else {
const s278* ob = ((s278*)s670( sym, s346, false ));
if( ob ) {
if( !ref->s395() )
ref->s397( ( s501* )this );
ref->s394( s668( sym ), ob );
s717 = true;}
else {
if( sym == s7::s1778 ) {
ob = this;
if( !ref->s395() )
ref->s397( ( s501* )this );
ref->s394( s1271, ob );
s717 = true;}
else if( s656 )
s717 = s656->s579( sym, ref );}}
return s717;}
size_t s278::s668( const std::wstring& s676 ) const{
if( s676 == s7::s1778 )
return s1271;
for( size_t n = 0; n < s657.size(); ++n ) {
if( s658[n] == s676 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s676 );}
s277* s278::s622( size_t off ){
if( off == s1271 )
return this;
return s657[off];}
void s278::s921( const std::wstring& s77, s501* s363, s500::s148 ap ){
s655.s564( s77, s363, ap );
s657.push_back( s363 );
s658.push_back( s77 );}
void s278::s1834( const std::wstring& s77, s501* s363 ){
if( !s655.s159( s77 ) )
throw new s16( L"no such member: " + s77 );
s655.s564( s77, s363, s500::s150 );
for( size_t n = 0; n < s658.size(); ++n ) {
if( s658[n] == s77 )
s657[n] = s363;}}
void s278::s1817( const s1779* ob ){
s657.clear();
s652->s655.s1790( s655 );
for( size_t n = 0; n < s658.size(); ++n )
s657.push_back( s655.get( s658[n] ) );
s500::s558 sm;
ob->s1809( sm );
s500::s558::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s655.s564( it->first, it->second.s15<s501*>(), s500::s150 );
else {
if( !s655.s159( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
it->second.s15<s501*>()->s371( s655.get( it->first ) );}}
for( size_t n = 0; n < s658.size(); ++n )
s657[n] = s655.get( s658[n] );}
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
s1171 s278::s401( const wstring& s357 ) const{
s501* s722 = s655.get( s357 );
s1171 s717 = s722->s366();
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
throw new TDException( 0, s1019, &s736, 
L"Arguments passed to a class without init function." );
else {
wstring str = s736.s297();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s7::s443 );
s269* ast_ = new s269( s7::s444, s144( str ) );
s508 cs = (s584*)s277::s524( *ast_, s306, s717, s346 );
s615* td = s615::s624(
cs, s306, s717, (s615*)s717, s284 );
s717->s655.s564( s7::s444, td );}}
return s717;}
s501* s278::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
vector<wstring> s723;
vector<s503> s280;
s278* s717 = new s278( *this, s280, s627() );
if( l.size() ) {
s615* s724 = (s615*)s655.get( s7::s443, false );
if( !s724 )
throw new TDException( 0, s1019, ast_,
L"Arguments passed to a class without init function." );
else {
s508 cs = new s584( s306, s7::s443, l, ast_ );
cs->s626().insert( cs->s626().begin(), s717 );
s615* td = s615::s624(
cs, s306, s717, (s615*)s612, s284 );
s717->s655.s564( s7::s444, td );}}
s717->s519( (s278*)s612 );
return s717;}
std::wstring s278::s304() const{
if( s513() == s497 )
return s284;
else if( s513() == s496 || s513() == s498 )
return s361;
else if( s513() == s493 || s513() == s1395 )
return s899();
assert( 0 );
return /*s283 + L"::" +*/ s284;
}
s501* s278::s358( const std::wstring& s708, const std::wstring& s346,
bool s543 /*= true*/ ) const
{
s386 ref( s708, s306 );
if( !s579( s708, &ref, s346 ) )
return NULL;
return ref.s393();}
s615* s278::s1861( const std::wstring& s708, vector<s277*>& s740 ) const{
if( s708 == L"getf" ) {
return new s1857( s306, (s278*)this, NULL, &s278::s1860, s740, 
NULL );}
return NULL;}
s501* s278::s1860( s501** s280, size_t s517 ){
s374* pv = (s374*) s280[0];
return s655.get( pv->to_wstring() );}
s277* s278::s349() const{
vector<s503> v;
return new s278( *this, v, NULL );}
void s278::s371( s277* p ) const{
s278* pob = (s278*)p;
s655.s1790( pob->s655 );
for( size_t n = 0; n < pob->s658.size(); ++n ) {
pob->s657[n] = pob->s655.get( pob->s658[n] );}
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
wstring s278::to_wstring( uint32_t s1740 ) const{
if( s655.s159( s7::s1806 ) ) {
s615* s1832 = (s615*)s655.get( s7::s1806 );
s9<s527> s1830 = new s527( (s268*)s306, (s278*)this, s627() );
vector<s503> s740 = { /*(s277*)this,*/ s1830 };
s1832->s620( s740 );
if( s1832->s644() != s7::s941 )
s1832->s519( this, false );
else
s1832->s621( this );
s1832->s516( 0, 0 );
return s1830->to_wstring();}
std::wstringstream buf;
wstring s361;
if( s511 == s496 ) s361 = L"Class";
else if( s511 == s497 ) s361 = L"Module";
else if( s511 == s498 ) s361 = L"Object";
else s361 = L"ERROR";
buf << s361 << L" : " << s284 << L"/" << s387 << endl;
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
s387 << L": " << this << endl;
s655.s310( pd, s201 + s434 );}
s615* s615::s623( const s269& s736, s268* s306, s278* obj,
const wstring& s284, const wstring& s581 ){
const s269::s281& s737 = s736.s299();
size_t s732 = s737.size();
std::vector<s277*> s280;
for( size_t n = 0; n < s732; ++n ) {
s269::s281::const_iterator it = s737.find( std::to_wstring( n ) );
if( it->second->s297() == s7::s1028)
s280.push_back( s950 );
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
s717 = new s911( s306, obj, NULL, s591, s280, &s736 );
s278* pAnc = (s278*)s306->s227( obj->s665(), s581 );
((s628*)pAnc->s358( s720[1], s581 ))->s677( obj->s366(),
s717 );
s717->s284 = s720[1];
s717->s618( s597 );}
else
throw new s16( L"malformed function name: " + s284 );}
else {
s717 = new s911( s306, obj, NULL, s591, s280, &s736 );
s717->s284 = s284;}
return s717;}
s584* s615::s1236( const s269& s736, s268* s306, s278* obj,
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
if( it->second->s297() == s7::s1028 )
s280.push_back( s950 );
else
s280.push_back( s277::s524( *it->second, s306, obj, s581 ) );}
s717 = new s584( s306, s625, s280, &s736 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s625 + L"' function call" );}
return s717;}
void s584::s519( const s278* s961 ){
return;
for( size_t n = 0; n < s280.size(); ++n ) {
s280[n]->s519( s961 );}}
s277* s584::s349() const{
return new s584( *this );}
s615* s615::s624( s584* cs, s268* s306, s278* s612, s615* s219, 
const wstring& s581 ){
wstring s625 = cs->s305();
wstring s739 = s612 ? s612->s304() : L"::";
s503 s738 = NULL;
std::vector<s277*>& s280 = cs->s626();
s506 s741 = NULL;
size_t pl = s625.find( L"<" );
if( pl == string::npos ) {
auto s1626 = s1542.find( s625 );
if( s1626 != end( s1542 ) && BIFuncs1v[s1626->second] )
return s306->s218( s1626->second, cs->s626(), s612, s219, cs->s627() );
s277* par = NULL;
int s1534 = 0;
s1529:
if( s280.size() ) {
par = s280[s1534];
s489 pc = par->s513();
if( pc == s492 ) {
try {
par->s519( s219 );}
catch( TDException* e ) {
if( e->Category() != s1017 || ( 
((s386*)par)->s643()[0] != L':' && ( (s386*)par )->s643().back() != L':' ) )
throw e->s30( L"while compiling function '" + s625 + L"'" );
s1534++;
goto s1529;}
if( ( (s386*)par )->s396().s14() ) {
if( ( (s386*)par )->s643() == s7::s445 )
par = s612;
s738 = ( (s386*)par )->s392();}}
else {
if( pc == s495 ) {
s508 cs = new s584( *(s584*)par );
par = s624( cs, s306, s612, s219, s581 );
( (s615*)par )->s519( s612, false );}
else {
par->s519( s219 );}}
if( par->s513() == s492 /*||  par->s513() == s1505*/ ) {
(void)0;}
else if( par->s513() == s1173 || par->s513() == s499 )
s738 = NULL;
else {
s738 = par->s515();}
s280[s1534] = par;}
else {
s741 = (s615*)s612->s358( s625, s739, false );
if( !s741 )
throw new s16( L"Procedure is not resolved: " + s625 );}
if( s1626 != end( s1542 ) )
return s306->s218( s1626->second, s280, s612, s219, cs->s627() );}
else {
wstring s646 = s625.substr( pl + 1, s625.size() - pl - 2 );
s625 = s625.substr( 0, pl );
try {
s1171 pt = s306->TR().s1110( s646, false );
if( !pt ) {
s868::Cont s1433;
pt = s764->s1338( s646, s1433 );}
s738 = s306->TR().s1107( pt )->s370( s219, s280 );}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s625 + L"' function " );
s1035 ast2 = new s269( s646 + L"()", cs->s627()->Nqj() );
s738 = s306->TR().s541( *ast2, s612, s581 );}
s280.insert( s280.begin(), s738 );}
s615* s717 = NULL;
s506 s742 = NULL;
s1266 s1385;
if( !s741 )  {
s489 s745 = s738->s513();
if( s745 == s492 ) {
s386* ref = (s386*)s738.s15<s502*>();
s738 = (s501*)ref->s523();
s745 = s738->s513();}
try {
assert( s745 != s497 );
if( s745 == s498 || s745 == s496 ) {
s615* ptd = s738.s15<s278*>()->s1861( s625, s280 );
if( ptd )
return ptd;
s742 = (s615*)s738.s15<s278*>()->s358( s625, s739, 
false );}
else if( s745 == s491 )
s1385 = s738.s15<s350*>()->s1340( s625 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s742 && !s1385.s353 )
s741 = (s615*)s612->s358( s625, s739, false );
if( !( s1385.s353 || s741 || s742 ) )
throw new s16( L"Method is not resolved: " + s625 );}
if( s1385.s353 ) {
s717 = new s910( s306, s219, s589, s280,	s1385.s352, s625, cs->s627() );}
else if( s741 ) {
if( s625 == L"new" ) {
assert( 0 );
vector<s277*> s1841( s280.begin() + 1, s280.end() );
s717 = new s1527( *s741.s15<s1527*>(), s612, s219, s1841,
cs->s627() );}
else {
s717 = new s911( /**td*/ *s741.s15<s911*>(), /*s612,*/ s219, s280, 
s590, cs->s627(), /*s612*/ s741->s612 );
}}
else if( s742 ) {
if( s625 == L"new" ) {
s717 = new s1527( *s742.s15<s1527*>(), s738.s15<s278*>(), s219, s280,
cs->s627() );}
else {
s9<s911> td = ( (s911*)s742->s349() );
s717 = new s911( *td, /*s738.s15<s278*>(),*/ s219, s280, s591, 
cs->s627(), s738.s15<s278*>() );}
if( s742->s619() == s596 )
s717->s598 = s592;
else
s717->s598 = s591;}
s717->s284 = s625;
return s717;}
void s615::s1392( vector<s277*>& s280, const vector<wstring>& s1353 ){
for( s277* p : s280 ) {
if( p->s513() == s492 || p->s513() == s1173 )
( (s386*)p )->s1078( s1353 );}}
void s615::s1392( vector<s503>& s280, const vector<wstring>& s1353 ){
for( s277* p : s280 ) {
if( p->s513() == s492 )
( (s386*)p )->s1078( s1353 );}}
s615::s615( s268* s306, s278* s616, s615* s617, s586 ct,
const std::vector<s277*>& l,	const s269* s736 )
: s278( s306, 0, s493, s736 ), s598( ct ), s599( s595 ),
s610( NULL ),	s612( s616 ), s611( s617 ), past( s736 ), s1831( s306 ){
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ((s501*)l[n]) == s950 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s512 = l[n + 1]->s366();
n += 2;
break;}
if( l[n]->s513() != s492 )
break;
s386* s77 = (s386*) l[n];
if( l.size() == n + 1 ) {
break;}
s501* ex = (s501*) l[n + 1];
if( ex->s513() != s491 && ex->s513() != s498 &&
ex->s513() != s497 && ex->s513() != s1396 )
throw new s16( L"incorrect syntax for lambda parameter " + s77->s643() +
L"; should be a type constructor.", (uint32_t)s16::s17::s20 );
s655.s564( s77->s643(), ex );
s606.push_back( (s501*)ex );
s657.push_back( (s501*)ex );
s658.push_back( s77->s643() );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
s615::s615( const s615& right, s278* s616, s615* s617,
const std::vector<s277*>& s740, const s269* s736 )
: s278( right.s306, right.s512, right.s511, s736 ),  
s599( right.s599 ),	s610( NULL ), s612( s616 ), s611( s617 ), 
past( s736 ), s1831( s306 ){
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
s655.s564( s658[n], s280[n].s15<s501*>(), s500::s150 );
s657[n] = s280[n];}}
else {
for( size_t n = 0; n < right.s280.size(); ++n ) {
s280.push_back( right.s280[n]->s349() );}}
for( size_t n = 0; n < right.s608.size(); ++n ) {
s608.push_back( right.s608[n]->s349() );}}
s910::s910( s268* s306, s615* s617, s586 ct, const vector<s277*>& l,
/*s642 s743,*/ s1171 s744, const wstring& s1728, const s269* s736 )
: s615( s306, s617, s617, ct, L"", s736 ), s1308( true )/*,
s585( s743 )*/
{
s284 = s1728;
s599 = s595;
s512 = s744;
s280.assign( l.begin(), l.end() );}
s910::~s910(){}
s911::s911( s268* s306, s278* s612, s615* s611, s586 ct,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s612, s611, ct, l, s736 ){
if( ct == s591 ) {
subject = s612;		}}
s911::s911( const s911& right, /*s501* s616,*/ s615* s617,
const std::vector<s277*>& s740, s586 ct,  const s269* s736, s278* s616 )
: s615( right.s306, s616 ? s616 : right.s612.s15<s278*>(), s617, ct, L"", s736 ){
TDException s1060( s7::s1847, s1019, s736 );
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
throw s1060.s1098( L"too many arguments: expected " + std::to_wstring( s280.size() ) + L", received " +
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
s911::~s911(){}
s584::s584( s268* pass_, const std::wstring& s193, const vector<s277*>& l, 
const s269* ast_ )
: s277( pass_, s495 ), s625( s193 ), past( (s269*)ast_ ){
s280.assign( l.begin(), l.end() );}
s584::s584( const s584& right )
: s277( right.s306, s495 ), s625( right.s625 ), past( right.past ){
for( size_t n = 0; n < right.s280.size(); ++n ) {
s280.push_back( right.s280[n]->s349() );}}
wstring s615::s899() const{
if( s612.s14() )
return s612->s304();
else if( s598 == s589 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
void s615::s917( s277* par, size_t pos, s503& s156, const s278* s1849 ){
if( par->s513() == s495 ) {
s508 cs = new s584( *((s584*)par) );
s156 = s624( cs, s306, (s278*)s1849, this, s612->s304() );
s156.s15<Transd*>()->s519( s1849, false );}
else if( par->s513() == s491 ) {
par->s519( /*s612*/ this );
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
void s615::s519( const s278* s1849, bool proc/*=false*/ )
{
s702 = proc ? s612->s304() : s1849->s304();
if( s612 && (s612->s513() == s497 || s612->s513() == s496 )) {
if( s612->s513() == s496 )
return;}
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( s598 == s589 && n == 1 ) {
s615::s1392( s280, ((s350*)s280[0]->s515())->s1334( s284 ) );}
if( par->s513() == s492 ) {
if( par.s15<s386*>()->s396().s13() ) {
s505 s1852 = s612;
s612 = (s278*)s1849;
par.s15<s386*>()->s519( this );
s612 = s1852;}
s607.push_back( NULL );}
else if( par->s513() == s1173 || par->s513() == s499 )
s607.push_back( /*NULL*/ par.s15<s501*>() );
else {
try {
s917( par, n, s280[n], s1849 );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s284 + L"' function " );}
s607.push_back( s280[n]->s515() );}}
if( s598 == s588 ) {
if( s284 == s238 ) {
for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n], s280[n].s15<s501*>(), s500::s150 );
s280[n]->s1856( s7::s941 );
s657[n] = s280[n];}}
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304() );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( s611 );
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
if( s612.s14() )
s610 = s306->TR().s541( s366(), s612, s612->s304() );
else
s610 = s306->TR().s541( s366(), (s278*)s1849, s1849->s304() );
s610->s519( s611 );
s610->s1856( s7::s941 );
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
s1076.resize( s607.size() );}
void s910::s519( const s278* s1849, bool proc/*=false*/ )
{
s702 = proc ? s612->s304() : s1849->s304();
TDException s1060( s7::s1243, s1254, past );
s615::s519( s1849, proc );
s277* par = s280[0]->s515();
s350* s738 = NULL;
s1266 s1385;
s489 s745 = par->s513();
s1239 ap;
if( s745 == s492 ) {
s386* ref = (s386*)par;
s504 pobj = ref->s392();
s745 = pobj->s513();
s738 = pobj.s15<s350*>();
ap = s1239( s280, s738 );
try {
s1385 = s738->s1335( s284, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s350::s351::s1255::s1322 ) {
s1385 = s738->s1330( s284, ap /*s1387, s280*/ );
}}}
else {
s738 = ( (s350*)par );
ap = s1239( s280, s738 );
try {
s1385 = ( (s350*)s738->s515() )->s1335( s284, ap/*s1387*/ );
}
catch( s16* e ) {
if( e->which() == (uint32_t)s350::s351::s1255::s1322 ) {
s1385 = ( (s350*)s738->s515() )->s1330( s284, ap/*s1387, s280*/ );
}}}
if( !s1385.s353 )
throw s1060.s1098( L"method is not resolved: " + par->s368() + L"::" + s284 + 
ap.s1496( s306 ) );
s512 = s1385.s352;
s585 = s1385.s353;
s1308 = s1385.s1308;
if( !s1308 && s280[0]->s1347() )
throw s1060.s1098( L"non-constant function is applied to a constant variable" );
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
s1076.resize( s607.size() );
s1413();}
void s911::s519( const s278* s1849, bool proc/*=false*/ )
{
TDException s1060( s7::s1697, s1731, s627() );
s702 = proc ? s612->s304() : s1849->s304();
if( s612->s513() == s497 || s612->s513() == s496 ) {
s613( s702 );
if( s612->s513() == s496 )
return;}
if( s280.size() > s657.size() )
throw s1060.s1098( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s492 ) {
s386* s1828 = par.s15<s386*>();
if( s1828->s396().s13() ) {
s1828->s519( /*this*/s611 );
}			}
else
s917( par, n, s280[n], s1849 );
if( s606[n]->s366() == s828->s366() ) {
if( !s606[n]->s521( s280[n].s15<s501*>() ) ) 
throw s1060.s1098( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s606[n]->s368() + L"', received - '" + par->s368() + L"'" );}
else if( !s306->TR().s1709( s280[n]->s366(), s606[n]->s366() ) )
throw s1060.s1098( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s606[n]->s368() + L"', received - '" + par->s368() + L"'" );}
for( size_t n = 0; n < s280.size(); ++n ) {
if( s280[n]->s644() < 0 )
throw s1060.s1098( L"uninitialized function parameter: " + s658[n] );
s657[n] = s280[n];}
s506 s1533 = s611;
s611 = 0;
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304() );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( /*s611*/ s612 );
else if( s608[n]->s513() != s493 && 
s608[n]->s513() != s1395 )
s608[n]->s519( /*s611*/ s612 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s608 ) {
if( it->s513() == s493 )
it.s15<Transd*>()->s519( s612, true );}
s611 = s1533;
if( !s512 ) {
if( s608.size() ) {
s512 = s608.back()->s366();
s610 = s306->TR().s541( s366(), s612, s612->s304() );}
else {
s512 = s1286;
s610 = s380.s15<s501*>();}
s610->s1856( s7::s941 );
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
s1076.resize( s607.size() );
s1413();}
void s615::s620( const vector<s503>& l ){
s280.clear();
s280.assign( l.begin(), l.end() );}
void s615::s621( const s278* s1849 ){
TDException s1060( s7::s1776, s1731, s627() );
if( s598 != s589 && s598 != s588 && s280.size() > s657.size() )
s1060.s1098( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s277* par = s280[n];
if( par->s513() == s495 ) {
s508 cs = new s584( *(s584*)par );
par = s624( cs, s306, s612, /*this*/s611, s612->s304() ); // DEBUG 210910
((s615*)par)->s519( s1849, false );
s280[n] = par;}
if( s280[n]->s513() == s499 ) {
s607.push_back( s280[n]->s515() );}
else if( s280[n]->s513() != s492 ) {
if( ( s598 != s589 && s598 != s588 ) || s284 == s238 ) {
s657[n] = s280[n]->s515();
s657[n]->s1856( s7::s941 );
s655.s564( s658[n], s657[n].s15<s501*>(), s500::s150 );}
s607.push_back( s280[n]->s515() );}
else {
if( s598 != s589 && s598 != s588 ) {
s657[n] = s280[n].s15<s501*>();
s655.s564( s658[n], s280[n].s15<s386*>()->s392(), s500::s150 );}
if( s280[n].s15<s386*>()->s396().s13() ) {
s280[n].s15<s386*>()->s519( s611 /*this*/); // DEBUG: 210910
}
s607.push_back( NULL );}
if( s284 != s238 && n < s657.size() && n < s606.size() && !s657[n].s15<s501*>()->s521( (s501*)s606[n] ) )
s1060.s1098( L"wrong argument's type" );}
for( size_t n = 0; n < s657.size(); ++n ) {
if( s657[n]->s644() == s7::s942 )
s1060.s1098( L"parameter is not provided" );}}
void s615::s869( s900& s156 ) const{
for( size_t n = 0; n < s606.size(); ++n )
s156.push_back( make_pair( s658[n], s606[n] ) );}
void s615::s1788( s501** s723, size_t s732 ){
int shift = 0;
if( s598 == s588 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1505 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1076[n] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1076[n];}}}}
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
s1076[n+shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1076[n + shift];}
else if( pc == s491 )
*( s603 + n + shift ) = (s501*)*( s604 + n );}}
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s603, s517 );
if( s717->s644() < 0 )
break;}
s610 = s717;
return s717;}
s504 s910::s516( s501** s723, size_t s732 ){
s501* s717 = NULL;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1505 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1076[n + shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1076[n + shift];}
else if( pc == s1395 )
(void)0;}}
if( !s1308 && s607[1]->s1347() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s585( s603, s517 );}
catch( s16* e ) {
TDException* s1060 = new TDException( TDException::Stage::s1137, s7::s1244, 
s1253, past,	*e );
delete e;
throw s1060;}
s717 = s607[0];
return s717;}
s504 s911::s516( s501** s723, size_t s732 ){
s501* s717 = s380;
if( subject.s14() )
s1831.s1838( subject->s516( 0, 0 ) );
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
if( s717->s644() == s7::s940 )
s717->s1856( 0 );
break;}}
return s717;}
s1527::s1527( s268* s306, s278* s612, s615* s611, const s269* s736 )
: s911( s306, s612, s611, s591, vector<s277*>(), s736 ){
s1527* pin = (s1527*)s612->s358( s7::s443, s612->s304(), false );
if( pin ) {
pin->s655.copy( s655, (s278*)s612, s611 );
s658 = pin->s658;
s657 = pin->s657;
s606 = pin->s606;}}
s1527::s1527( const s1527& right, s278* s616, s615* s617,
const std::vector<s277*>& s740, const s269* s736 )
: s911( right, /*s616,*/ s617, s740, s591, s736 )
{
s612 = s616;
s280.assign( s740.begin() + 1, s740.end() );
s512 = right.s512;
s610 = (s501*)s740[0];}
s1527::~s1527(){}
void s1527::s519( const s278* s1849, bool proc/*=false*/ )
{
for( size_t n = 0; n < s280.size(); ++n ) {
s280[n]->s1856( s7::s941 );}
s610 = s612.s15<s278*>();
s512 = s610->s366();}
s504 s1527::s516( s501** s723, size_t s732 ){
s621( s612 );
s501* s717 = new s278( *s612, s280, s627() );
s717->s519( s611 );
s717->s1413();
return s717;
wstring s193 = s627()->s297();
wstring s1528 = s627()->Src();
s1528.replace( s1528.find( s193 ), s193.size(), 1, L' ' );
s269* ast_ = new s269( s193, s1528 );
s717 = s610.s15<s278*>()->s663( *ast_, s611, s702 );
s717->s1413();
return s717;
vector<s277*> s1825( begin(s280), end(s280));
s717 = s610->s370( s611, s1825, s627() );
s717->s1413();
return s717;}
bool
s615::s579( const wstring& s708, s386* ref,	
const wstring& s346 ) const{
bool s717 = false;
wstring s284 = s708;
size_t pl = s284.find( L"." );
if( pl == string::npos ) { //a
if( !s655.s159( s284 ) /*!ob*/ ) {
if( s611.s14() && (s612.s13() || s611->s612 == s612 || 
s702 == s611->s702 || s702 != s611->s702) )
s717 = s611->s579( s284, ref, s346 );
if( !s717 ) {
if( s612.s14() )
s717 = s612->s579( s284, ref, s346 );
if( s717 ) {
if( s612->s513() != s497 && ref->s396() == s612.s15<s277*>() ) {
ref->s397( (s501*)&s1831 );
((s1777*)&s1831)->s1838( s612.s15<s501*>() );}}
else
s717 = s306->s579( s284, ref, s346 );}}
else {
size_t off = s668( s284 );
ref->s394( off, ((s502*)&(*s657[off]))->s515()->s523() );
ref->s397( (s501*)this /*(s502**)&s280[off]*/ );
s717 = true;}}
else {// a.y
s284 = s708.substr( pl + 1 );
wstring s718 = s708.substr( 0, pl );
s277* ob = s655.get( s718, false );
if( !ob ) {
s717 = s612->s579( s708, ref, s346 );
if( !s717 && s611.s14() )
s717 = s611->s579( s708, ref, s346 );}
else {
size_t off = s668( s718 );
ref->s394( off, NULL );
s717 = ob->s523()->s579( s284, ref, s346 );
ref->s397( (s501*)this );}}
return s717;}
bool
s910::s579( const wstring& s708, s386* ref, const wstring& s346 ) const{
if( s284 == L"new" &&
s280[0].s15<s501*>()->s579( s708, ref, s346 ) )
return true;
return s615::s579( s708, ref, s346 );}
s277* s615::s622( size_t off ){
return s657[off];}
s277* s615::s349() const{
return new s615( *this );}
s277* s910::s349() const{
return new s910( *this );}
s277* s911::s349() const{
return new s911( *this );}
s277* s1527::s349() const{
return new s1527( *this );}
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
buf << s4::fill_n_ch( L' ', s201 + s434 * 2 ) << s658[n] << endl;}
if( !s657.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"memvec : " << endl;
for( size_t n = 0; n < s657.size(); ++n )
s657[n]->s310( pd, s201 + s434 * 2 );}
if( !s608.empty() ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << L"exprs : " << endl;
for( size_t n = 0; n < s608.size(); ++n )
s608[n]->s310( pd, s201 + s434 * 2 );}}
s374::s374( s268* s306, const std::wstring& s, const s269* ast_ )
: s1573( s306, NULL, ast_ ){
if( s374::proto.s13() ) {
s512 = 0;
wh = s7::s942;}
else {
s512 = s1288;
wh = s7::s941;
s363 = s;}
s334 = s1755;}
s374::s374( s268* s306, s278* s616, const std::vector<s277*>& l, const s269* ast_ )
: s1573( s306, s616, ast_ ){
s280.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s942;
else
wh = s7::s941;
s512 = s1288;
s334 = s1755;}
s374::s374( const s374& r, const s269* ast_ )
: s1573( r.s306, r.ns, ast_ ){
s363 = r.s363;
wh = r.wh;
s512 = r.s512;
s334 = s1755;}
s374::s374( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ )
: s1573( s306, NULL, ast_ ){
s363 = s;
pos = string::npos;
s512 = s1288;
s334 = s1755;
wh = s7::s941;}
s501* s374::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s374( s306, s612, l );}
void s374::s364(){
s1573<s1753, wchar_t, s374, s1749>::s364();
s362 = s1573<s1753, wchar_t, s374, s1749>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s374::s1384, s1288,
{ s1239(), s1239( { s7::s1565, s7::s1571 } ) }, 0, 100 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s374::s829, s1284,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"find-first-not-of", new s351( L"find-first-not-of", &s374::s1765, s1284,
{ s1239( { s1288 } ), s1239( { s1288, s1284 } ), 
s1239( { s1288, s1284, s1284 } )}, 1, 3 )));
s362.insert( make_pair( L"set", new s351( L"set", &s374::s402, s1286,
{ s1239( { s1288 } ), s1239( { s1286 } ) }, 1, 1 )));
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s374::s1769, s1286,
{ s1239( { s1284, s1288 } ), s1239( { s1284, s1755 } ) }, 2, 2 )));
s362.insert( make_pair( L"size", new s351( L"size", &s374::s339, s1284,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"sub", new s351( L"sub", &s374::s845, s1288,
{ s1239( { s1687::s1425 } ), s1239( { s1687::s1425, s1687::s1425 } ) }, 1, 2 )));
s362.insert( make_pair( L"subn", new s351( L"subn", &s374::s1772, s1288,
{ s1239( { s1687::s1425 } ), s1239( { s1687::s1425, s1687::s1425 } ) }, 1, 2 )));
s362.insert( make_pair( L"sum", new s351( L"sum", &s374::s403, s1288,
{ s1239( { s1288, s7::s1571 } ) }, 1, 100 )));
s362.insert( make_pair( L"to-bytes", new s351( L"to-bytes", &s374::s1516, s1450->s366(),
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"to-Int", new s351( L"to-Int", &s374::s427, s1284,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"tolower", new s351( L"tolower", &s374::s976, s1288,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"toupper", new s351( L"toupper", &s374::s977, s1288,
{ s1239() }, 0, 0 )));
s362.insert( make_pair( L"rfind", new s351( L"rfind", &s374::s850, s1284,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"eq", new s351( L"eq", &s374::s413, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"not", new s351( L"not", &s374::s428, s1275,
{ s1239( ) }, 0, 0 )));
s362.insert( make_pair( L"less", new s351( L"less", &s374::s414, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"greater", new s351( L"greater", &s374::s415, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"leq", new s351( L"leq", &s374::s416, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"geq", new s351( L"geq", &s374::s417, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"neq", new s351( L"neq", &s374::s418, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s362.insert( make_pair( L"textin", new s351( L"textin", &s374::s424, s1284,
{ s1239( ), s1239( { s1284 } ), s1239( { s1687::s1680 } ), 
s1239( { s1687::s1680, s1284 } ) }, 1, 2 )));
s362.insert( make_pair( L"getline", new s351( L"getline", &s374::s1658, s1284,
{ s1239(), s1239( { s1687::s1680 } ) }, 0, 1 )));
s362.insert( make_pair( L"match", new s351( L"match", &s374::s1142, s1275,
{ s1239( { s1288 } ) }, 1, 1 )));
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s374::proto->s368() + L">";
s1171 s1692 = s764->s1338( ts, s1433 );
s362.insert( make_pair( L"split", new s351( L"split", &s374::s1665, s1692,
{ s1239(), s1239( { s1288 } ) }, 0, 0 )));}
void s917( s277* par, s268* s306, s278* s612,
s615* s219, s503& s156 ){
if( par->s513() == s495 ) {
s508 cs = new s584( *( (s584*)par ) );
s156 = s615::s624( cs, s306, s612, s219, s612->s304() );
s156.s15<Transd*>()->s519( s612, false );}
else if( 1 && par->s513() == s491 ) {
par->s519( /*s612*/ s612 );
s156 = par;}
else
s156 = par;}
void s374::s519( const s278* s961 ){
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s495 ) {
s917( par, s306, ns, (s615*)ns, s280[n] );}
else if( par->s366() == s1587 ) {
auto pr = par.s15<s400*>();
auto rp = pr->s1337();
typename s1558::iterator s1694, s1695;
s1694 = rp.first.s15<s1262*>()->s1269();
s1695 = rp.second.s15<s1262*>()->s1269();
s1558 news( s1694, s1695 );
s363 += news;}
else if( par->s513() != s492 ) {
s363 += par->to_wstring();}
else {
if( s306->s1497() /*par.s15<s386*>()->s396().s14()*/ )
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
const s1033* s1159 = NULL;
if( s627() && s627()->Nqj() )
s1159 = s627()->Nqj()->s1106();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1159, s, pos, s96, true, L" \n" );
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
return new s374( s306, s363 );}
s277* s374::s349() const{
return new s374( *this );}
s1171 s374::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get" )
s717 = s334;
else
s717 = s1573::s1331( s1728, l );
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
wstring s374::to_wstring( uint32_t s1740 ) const{
if( 0 && s363.front() == '\"' && 
s363.back() == '\"' )
return s363.substr( 1, s363.size() - 2 );
return s363; }
s1489 s374::to_bytes() const{
s1489 s717;
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
inline void s374::s1769( s501** s280, size_t s517 ){
int pl = (int)*s280[2];
wchar_t c;
if( s280[3]->s366() == s1755 )
c = *( (s1749*)s280[3] )->s372();
else
c = ( (s374*)s280[3] )->s363[0];
( (s374*)DR )->s363[pl] = c;}
inline void s374::s339( s501** s280, size_t s517 ){
*( (s360*)s733 )->s372() = (int)( (s374*)DR )->s363.size();}
inline void s374::s403( s501** s280, size_t s517 ){
s733->s363 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s517; ++n )
s733->s363 += PARN( n )->to_wstring();}
inline void s374::s976( s501** s280, size_t s517 ){
s733->s363 = ((s374*)DR)->s363;
std::for_each( s733->s363.begin(), s733->s363.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s374::s977( s501** s280, size_t s517 ){
s733->s363 = ((s374*)DR)->s363;
std::for_each( s733->s363.begin(), s733->s363.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s374::s845( s501** s280, size_t s517 ){
wstring s731 = L"Invalid substring specification: ";
if( s517 < 2 )
throw new s16( s731 + L"too few parameters." );
const wstring& dr = ((s374*)DR)->s363;
int start = 0, end = (int) dr.size() - 1;
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
inline void s374::s1772( s501** s280, size_t s517 ){
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
inline void s374::s829( s501** s280, size_t s517 ){
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
inline void s374::s1765( s501** s280, size_t s517 ){
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
inline void s374::s850( s501** s280, size_t s517 ){
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
Stream* s1652 = NULL;
size_t s1627 = 0;
if( s517 >= 3 ) {
if( s280[2]->s366() == s1284 )
s1627 = (int)*s280[2];
else
s1652 = (Stream*)s280[2];
if( s517 == 4 )
s1627 = (int)*s280[3];
else
s1652 = s1575;}
wstring& s156 = *( (s374*)DR )->s372();
s1652->s1636( s156, s1627 );
int s717 = (int)s156.size();
s156.resize( s717 );
*((s360*)s733)->s372() = s717;}
inline void s374::s1658( s501** s280, size_t s517 ){
Stream* s1652 = NULL;
if( s517 >= 3 ) {
s1652 = (Stream*)s280[2];}
else
s1652 = s1575;
wstring& s156 = *( (s374*)DR )->s372();
s1652->s1637( s156 );
int s717 = (int)s156.size();
s156.resize( s717 );
*( (s360*)s733 )->s372() = s717;}
inline void s374::s1142( s501** s280, size_t s517 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1148;
wstring s = DR->to_wstring();
bool s156 = regex_match( s, s1148, rg );
*s734->s372() = s156;}
inline void s374::s1665( s501** s280, size_t s517 ){
s323* pv = (s323*)s280[0];
pv->clear();
wstring s73 = L"\n";
if( s517 == 3 )
s73 = s280[2]->to_wstring();
wstring& s = ((s374*)DR)->s363;
size_t s69 = 0, s70 = 0;
s1::s9<s374> adds = new s374( ((s374*)DR)->s306 );
while( s70 != wstring::npos && s69 < s.size()) {
s70 = s.find( s73, s69 );
adds->s363 = s.substr( s69, s70 - s69 );
s69 = s70 + s73.size();
if( adds->s363.size() )
pv->s328().push_back( adds->s349() );}}
inline void s374::s1516( s501** s280, size_t s517 ){
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
s1753::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i < 0 ) {
i = (int)s363.size() + i;
if( i < 0 )
i = 0;}
it = s363.begin() + i;}
return new s1754( this, it, it == s363.end() ? it : it + 1 );}
Iterator* s374::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( *it == *( (s1453*)_val )->s372() )
return new s1754( this, it, it + 1 );
return new s1754( this, end( s363 ), end( s363 ) );}
s501* s374::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1754*)it )->s1269() );
return new s360( s306, (int)n );}
Iterator* s374::s1328() {
return new s1754( this, s363.begin(), s363.begin() + 1 ); }
Iterator* s374::s1332() {
return new s1754( this, s363.end(), s363.end() ); }
Iterator* s374::s321( s400* rv ){
s1268 pr = rv->s1337( this );
return new s1754( this,
pr.first.s15<s1262*>()->s1269(), pr.second.s15<s1262*>()->s1269() );}
vector<wstring> s1045( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s873::s873( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s804, s736 ){
TDException s1060( s7::s1226, s1018, s736 );
if( l.empty() )
throw s1060.s1098( L"too few arguments" );
s280.assign( l.begin(), l.end() );
s512 = s1288;
s615::s1392( ( vector<s277*>& )l, s1045 );}
s873::s873( s268* s306 )
: s615( s306, NULL, NULL, s588, s804, NULL ){
s512 = s1288;}
void s873::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
wstring s731 = L"Invalid parameters of 'substr' function: ";
if( s280[0]->s366() != s1288 )
throw new s16( s731 + L"The first parameter is not of String type." );
str = s280[0].s15<s374*>();
size_t s762 = 1;
int s826 = 0;
s783 s812 = s755;
s756 =	nTo = 1;
s844 = s781 = 0;
while( s762 < s280.size() ) {
s503 par_ = s280[s762];
s489 pc = par_->s513();
if(	pc == s492 || pc == s1173 || pc == s491 || pc == s493 ) {
s503 par;
s507 rf;
if( pc == s492 ) {
rf = par_.s15<s386*>();
par = (s277*)rf->s393();}
else if( pc == s1173 ) {
rf = par_.s15<s386*>();
par = par_;}
else
par = par_;
if( par->s366() == s828->s366() ) {
if( rf->Id() == s1372 ) {
if( s826 != 0 )
throw new s16( s731 + L"'from' is misplaced." );
s826 = 1;
s812 = s810;}
else if( rf->Id() == s1380 ) {
if( s826 != 0 )
throw new s16( s731 + L"'to' is misplaced." );
s826 = 1;
s812 = s872;}
else if( rf->Id() == s1364 ) {
if( s812 != s755 && s826 >= 2 )
throw new s16( s731 + L"'before' is misplaced." );
if( s812 == s872 )
s781 = -1;
else
s844 = -1;
s826 = 2;}
else if( rf->Id() == s1360 ) {
if( s812 != s755 && s826 >= 2 )
throw new s16( s731 + L"'after' is misplaced." );
if( s812 == s872 )
s781 = 1;
else
s844 = 1;
s826 = 2;}
else if( rf->Id() == s1371 ) {
if( s812 != s755 && s826 >= 3 )
throw new s16( s731 + L"'first' is misplaced." );
s826 = 3;}
else if( rf->Id() == s1376 ) {
if( s812 != s755 && s826 >= 3 )
throw new s16( s731 + L"'last' is misplaced." );
if( s812 == s872 )
nTo = string::npos;
else
s756 = string::npos;
s826 = 3;}
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
else if( par->s366() == s1288 ) {
if( s812 == s810 )
s860 = par;
else if( s812 == s872 )
s852 = par;
else {
if( s860.s13() && s809.s13() )
s860 = par;
else if( s852.s13() && s759.s13() )
s852 = par;
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
s826 = 0; s812 = (( s812 == s810 || s812 == s755 ) ? s872 : s810 );}
else if( par->s366() == s1284 ) {
if( s812 == s810 )
s809 = par;
else if( s812 == s872 )
s759 = par;
else {
if( s860.s13() && s809.s13() )
s809 = par;
else if( s852.s13() && s759.s13() )
s759 = par;
else
throw new s16( s731 + L"unknown parameter '" + rf->s643() + L"'." );}
s826 = 0; s812 = ( ( s812 == s810 || s812 == s755 ) ? s872 : s810 );}}
s762++;}}
s504 s873::s516( s501** s723, size_t s732 ){
size_t s196 = 0, s715 = string::npos;
wstring s806, s761;
wstring dom = str->s516( 0, 0 )->to_wstring();
if( s809.s14() ) {
if( s809->s513() == s493 )
s196 = (size_t)(int)*s809->s516( 0, 0 );
else
s196 = (size_t)(int)*s809.s15<s360*>();}
else if( s860.s14() ) {
s806 = s860->to_wstring();
if( s756 == 1 )
s196 = dom.find( s806 );
else if( s756 == string::npos )
s196 = dom.rfind( s806 );
else
throw new s16( L"substr: nFrom =" + std::to_wstring( s756 ) );
if( s844 > 0 )
s196 += s806.size();
else
s196 += s844;}
if( s759.s14() ) {
if( s759->s513() == s493 )
s715 = (size_t)(int)*s759->s516( 0, 0 );
else
s715 = (size_t)(int)*s759.s15<s360*>();}
else if( s852.s14() ){
s761 = s852->to_wstring();
if( nTo == 1 )
s715 = dom.find( s761, s196 );
else if( nTo == string::npos )
s715 = dom.rfind( s761 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s756 ) );
s715 += s781;}
if( s196 < 0 || s196 >= s715 || s196 >= dom.size() )
return s504();
wstring s156 = dom.substr( s196, s715 - s196 );
s610 = new s374( s306, s156 );
return s610;}
s277* s873::s349()const{
return new s873( *this );}
s400::s400( s268* s306 )
: s336( s306, NULL, NULL ), s1073( false ), s1074( false ), s1086( 0 )//, s968( false )
{
s512 = s864.s13() ? 0 : s864->s366();
s1393 = new s1704( s306, 0 );
s1394 = new s1704( s306, U64_MAX );
s1316 = new s1704( s306, 0 );}
s400::s400( s268* s306, s336* s612, Iterator* it )
: s336( s306, NULL, NULL ), s1082( s612 ), s1641( it ), s1073( false ), s1074( false ), 
s1086( 0 ){
s512 = s864->s366();}
s400::s400( uint64_t _beg, uint64_t _end )
: s336( NULL, NULL, NULL ), s1073( false ), s1074( false ), s1086( 0 )//, s968( false )
{
s1393 = new s1704( s306, _beg );
s1394 = new s1704( s306, _end );
s512 = s864->s366();
s1316 = new s1704( s306, 0 );}
s400::s400( s268* s306, const wstring& s78, const s269* ast_ )
: s336( s306, NULL, ast_ ), s1073( false ), s1074( false ), s1086( 0 )//, s968( false )
{}
s400::s400( const s400& r, const s269* ast_ )
: s336( r.s306, r.ns, ast_ ), s1073( false ), 
s1074( false ), s1086( r.s1086 ), s1316( r.s1316 )//, s968( r.s968 )
{
s512 = r.s512;}
vector<wstring> s1039( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s400::s400( s268* s306, s278* s616, const vector<s277*>& l_, const s269* ast_ )
: s336( s306, s616, ast_ ), s1073( false ), s1074( false ), s1086( 0 ), 
s1316( new s1704( s306, 0 ) )//, s968( false )
{
s512 = s864->s366();
if( l_.empty() )
return;
TDException s1060( s7::s1224, s1019, ast_ );
if( l_.size() > 9 )
throw s1060.s1098( L"too many arguments" );
s615::s1392( ( vector<s277*>& )l_, s1039 );
const size_t s1163 = 3;
std::vector<s277*> l( s1163 );
if( l_[0]->s513() == s1173 ) {
s386* rf = (s386*)l_[0];
if( rf->Id() == s1374 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1704( s306, 0 );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1704( s306, 0 );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s612 = l[0];
s1393 = l[1];
s1394 = l[2];
if( s612.s13() ) {
s334 = s1704::proto->s366();
s324 = s1704::proto->s366();}
else {
s334 = 0;
s324 = 0;}
s512 = s864->s366();}
s501* s400::s369( const s269& s736, s278* s612, const wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && ( s.size() == s361.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s731 = L"Malformed Range definition: " + s;
vector<s277*> s740;
s277::s1501( s736, s306, s612, s346, s740 );
return new s400( s306, s612, s740 );}
else
return NULL;}
void s400::s519( const s278* s961 ){
TDException s1060( s7::s1006, s1019, s627(), L"wrong Range definition" );
ns = (s278*)s961;
if( s612.s14() ) {
if( s612->s513() == s492 ) {
s612.s15<s386*>()->s519( s961 );
s1082 = (s336*)s612.s15<s386*>()->s392();}
else if( s612->s513() == s495 ) {
s503 tmp = s277::s1121( s306, s612, (s278*)s961, (s615*)s961, s961->s304() );
s612 = tmp;
s1082 = (s336*)s612->s515();}
else {
s1082 = (s336*)s277::s1121( s306, s612, (s278*)s961, (s615*)s961, s961->s304() );}
s334 = s1082->ValType();
s324 = s1082->s327();}
if( s1393.s14() ) {
if( s1393->s513() == s492 )
s1393.s15<s386*>()->s519( s961 );
else {
s503 tmp = s277::s1121( s306, s1393, (s278*)s961, (s615*)s961, s961->s304() );
s1393 = tmp;}}
else
s1393 = s380.s15<s502*>();
if( s1394.s14() ) {
if( s1394->s513() == s492 )
s1394.s15<s386*>()->s519( s961 );
else {
s503 tmp = s277::s1121( s306, s1394, (s278*)s961, (s615*)s961, s961->s304() );
s1394 = tmp;}}
else
s1394 = s380.s15<s502*>();}
void s400::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s400::s1384, s864->s366(),
{ s1239( { s1687::s1724 } ), s1239( { s1284, s1284 } ),
s1239( { s1687::s1682, s1284 } ),
s1239( { s1687::s1682, s1284, s1284 } ) }, 1, 3 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", NULL, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"max-element", new s351( L"resize", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", NULL, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"reverse", new s351( L"reverse", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
s1266 s400::s1340( const std::wstring& s357 ) const{
if( s1082.s14() ) 
return s1082->s1340( s357 );
return s350::s1340( s357 );}
s1266 s400::s1335( const std::wstring& s357, s1239& ap ) const{
if( s357 == L"new" )
return s350::s1335( s357, ap );
if( s1082.s14() )
return s1082->s1335( s357, ap );
assert( 0 );
throw;}
s1266 s400::s1330( const std::wstring& s357,
s1239& ap ) {
if( s357 == L"new" )
return s350::s1330( s357, ap );
if( s1082.s14() )
return s1082->s1330( s357, ap );
assert( 0 );
throw;}
s1171 s400::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"new" ) {
s717 = s1687::s1682;}
else if( s1082.s14() )
return s1082->s1331( s1728, l );
return s717;}
const vector<wstring>&
s400::s1334( const wstring& s357 ) const{
if( s357 == L"new" || s1082.s13() )
return s350::s1334( s357 );
else
return s1082->s1334( s357 );}
s501* s400::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s400( s306, s612, l, ast_ );}
inline bool
s400::s521( const s501* s522 ) const{
return ( ( (s400*)s522 )->s366() == s366() );}
size_t s400::s1261() const{
if( s1082.s14() )
return s1082->s1261();
else
return 0;}
s1268 s400::s1337(){
Iterator *fir = NULL, *sec = NULL;
if( s1082.s14() ) {
if( s1073 )
fir = s1082->s1326( s1393.s15<s501*>() );
else if( s1393 == s1696 )
fir = s1082->s1332();
else
fir = s1082->s1304( s1393.s15<s501*>() );
if( s1074 )
sec = s1082->s1326( s1394.s15<s501*>() );
else if( s1394 == s1696 )
sec = s1082->s1332();
else
sec = s1082->s1304( s1394.s15<s501*>() );
if( s1082->s1261() >= 1 && ( s1393 == s1696 || sec->operator<( fir ) ) ) {
( (s1242*)fir )->reverse();
( (s1242*)sec )->reverse();}}
return s1268( fir, sec );}
s1268 s400::s1337( s336* s616 ){
Iterator *fir, *sec;
if( s1073 )
fir = s616->s1326( s1393.s15<s501*>() );
else if( s1393 == s1696 )
fir = s616->s1332();
else 
fir = s616->s1304( s1393.s15<s501*>() );
if( s1074 )
sec = s616->s1326( s1394.s15<s501*>() );
else if( s1394 == s1696 )
sec = s616->s1332();
else
sec = s616->s1304( s1394.s15<s501*>() );
if( s616->s1261() >= 1 && ( s1393 == s1696 || sec->operator<( fir ) ) ){
( (s1242*)fir )->reverse();
( (s1242*)sec )->reverse();}
return s1268( fir, sec );}
inline void s400::s1384( s501** s280, size_t s517 ){
s400* r = ( (s400*)s280[1] );
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 ) 
{ return v.push_back( (s277*) s363 ); } );
s400* s1645 = new s400( r->s306, r->ns, v );
s1645->s519( r->ns );
*s280 = (s501*)s1645;}
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
s1717 = s1393->s516( 0, 0 );
else if( pc == s492 )
s1717 = s1393.s15<s386*>()->s392();
else
s1717 = s1393.s15<s501*>();}
if( s1394.s14() ) {
s489 pc = s1394->s513();
if( pc == s493 )
s1718 = s1394->s516( 0, 0 );
else if( pc == s492 )
s1718 = s1394.s15<s386*>()->s392();
else
s1718 = s1394.s15<s501*>();}
if( s1082.s14() )
return s1082->s321( this );
s1086 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1393.s15<s501*>();
return this;}
s277* s400::s322(){
if( s1086 == U64_MAX ) {
if( s1717.s14() ) {
if( s1717->s366() == s1702 )
s1086 = *s1717.s15<s1704*>()->s372();
else {
s1465 tmp;
s1717->s371( &tmp );
if( *tmp.s372() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1086 = *tmp.s372();}}
if( s1718.s14() ) {
if( s1718->s366() == s1702 )
s1721 = *s1717.s15<s1704*>()->s372();
else {
s1465 tmp;
s1718->s371( &tmp );
if( *tmp.s372() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1721 = *tmp.s372();}}
if( s1086 > s1721 )
incr = -1;
else
incr = 1;}
else
s1086 += incr;
if( s1086 == s1721 )
return NULL;
*s1316->s372() = s1086;
return s1316;}
s277* s400::s1053(){
return s325->s1053();}
const s277* s400::s1053() const{
return NULL;}
s277* s400::Idx(){
return NULL;}
s277* s400::El(){
return NULL;}
void s400::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Range :: " << L" curit: " << s325 << endl;}
vector<wstring> s1257( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1256::s1256( s268* s306, const wstring& s78, const s269* ast_ )
: s336( s306, NULL, ast_ ), s1085( s7::s1545, s306 ), s1086(NULL), s363( new s360( s306, 0 )), 
s717( new s360( s306, 0 )),s1522(0){
s512 = s1258.s13() ? 0 : s1258->s366();}
s1256::s1256( const s1256& r, const s269* ast_ )
: s336( r.s306, r.ns, ast_ ), s1085( s7::s1545, s306 ), s1086(NULL), s363( new s360( s306, 0 ) ),
s717( new s360( s306, 0 ) ), s1522(r.s1522){
*s363->s372() = (int)*r.s363;
*s717->s372() = (int)*r.s717;
ns = r.ns;
s512 = r.s512;}
s1171 s1628( size_t& idx, const vector<s277*>& l ){
if( l.size() > idx && l[idx]->s513() == s1173 )
idx++;
if( l.size() > idx )
return l[idx]->s366();
return 0;}
s1256::s1256( s268* s306, s278* s616, const vector<s277*>& l_, const s269* ast_ )
: s336( s306, s616, ast_ ), s1085( s7::s1545, s306 ), s1086(NULL),
s363( new s360( s306, 0 ) ),	s717( new s360( s306, 0 ) ),s1522(0){
s512 = s1258->s366();
ns = s616;
if( l_.empty() )
return;
TDException s1060( s7::s1538, s1019, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s1060.s1098( L"too many arguments" );
s615::s1392( ( vector<s277*>& )l_, s1257 );
const size_t s1163 = 3;
std::vector<s277*> l( s1163 );
if( !s306->TR().s1640( l_[0]->s366(), s1687::s1682 ) )
throw s1060.s1098( L"the type is not rangeable: " + l_[0]->s368() );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s366() == s1587 ) {
range = (s400*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s513() != s1173 || ((s386*)l_[bas])->Id() != s1499 )
throw s1060.s1098( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s513() != s1173 || ((s386*)l_[bas])->Id() != s1383 )
throw s1060.s1098( L"expected the 'where:' clause" );
if( l_[bas+2]->s513() != s1173 || ((s386*)l_[bas+2])->Id() != s1499 )
throw s1060.s1098( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s612 = l[0];
where = l[1];
s1180 = l[2];}
s501* s1256::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
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
if( s306->TR().s1640( s280[0]->s366(), s1687::s1682 ) )
return new s1256( s306, s612, s280 );
else
return new s1040( s306, s612, s280 );
/*if( s732 == 1 ) {
s269::s281::const_iterator it = s737.find( L"0" );
la = s277::s524( *it->second, s306, s612, s346 );}
else {
s269::s281::const_iterator it = s737.find( L"0" );
fi = s277::s524( *it->second, s306, s612, s346 );
it = s737.find( L"1" );
la = s277::s524( *it->second, s306, s612, s346 );
if( s732 == 3 ) {
it = s737.find( L"2" );
in = s277::s524( *it->second, s306, s612, s346 );}
}*/
}
else
return NULL;}
void s1256::s519( const s278* s961 ){
TDException s1060( s7::s1006, s1019, s627(), L"wrong Filter definition");
ns = (s278*)s961;
if( s612.s13() )
return;
if( s612->s513() == s492 ) {
s1082 = s612.s15<s386*>()->s392();}
else if( s612->s513() == s495 ) {
s503 tmp = s277::s1121( s306, s612,(s278*)s961, (s615*)s961, s961->s304() );
s612 = tmp;
s1082 = s612->s515();}
else {
s1082 = (s501*)s277::s1121( s306, s612, (s278*)s961, (s615*)s961, s961->s304() );}
if( s1082->s513() == s491 ) {}
else if( s1082->s513() == s498 ) {}
else
throw s1060.s1098( L"unsupported container type" );
s1085.s394( 0, s306->TR().s1107( s1082.s15<s336*>()->ValType() ) );
s1085.s397( (s501*)this );
if( where.s14() ) {
if( where->s513() == s492 )
where.s15<s386*>()->s519( s961 );
else
where = s277::s1121( s306, where, (s278*)this, (s615*)s961, s961->s304() );}
if( s1180.s14() ) {
if( s1180->s513() == s492 ) {
s1180.s15<s386*>()->s519( s961 );
s334 = s1180->s515()->s366();}
else {
s1180 = s277::s1121( s306, s1180, (s278*)s961, (s615*)s961, s961->s304() );
s334 = s1180.s15<s906*>()->s1495();}}
if( !s334 )
s334 = s1082.s15<s336*>()->ValType();
s512 = s306->TR().s1154( s868::Cont( { s1258->s366(), 1, s334, 0 }) );
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + 
s306->TR().s1521( s306->TR().s855( s334 ) ) + L">";
s1522 = s764->s1338( ts, s1433 );
s1413();}
void s1256::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s1256::s1384, s1258->s366(),
{ s1239( { s1284, s1284 } ) }, 1, 2 ) ) );
s362.insert( make_pair( L"to-vector", new s351( L"to-vector", &s1256::s1517, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"max-element", new s351( L"resize", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", NULL, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"reverse", new s351( L"reverse", NULL, s1286,
{ s1239() }, 0, 0 ) ) );
s362.equal_range( L"new" ).first->second->s1412( true );
s362.equal_range( L"to-vector" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
s1266 s1256::s1335( const std::wstring& s357, s1239& ap ) const{
return s350::s1335( s357, ap );
if( s357 == L"new" )
return s350::s1335( s357, ap );
assert( 0 );
throw;}
s1266 s1256::s1330( const std::wstring& s357, s1239& ap ){
if( s357 == L"new" ) {
auto ran = s356().equal_range( s357 );
s351* mi = ran.first->second;
s1266 s1385( s334, mi->s1259(), mi->s1347() );
return s1385;}
else if( s357 == L"to-vector" ) {
auto ran = s356().equal_range( s357 );
s351* mi = ran.first->second;
s1266 s1385( s1522, mi->s1259(), mi->s1347() );
return s1385;}
assert( 0 );
throw;}
s1171 s1256::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"new" ) {
s717 = s1687::s1682;}
else if( s1728 == L"to-vector" ) {
s717 = s1522;}
return s717;}
s501* s1256::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1256( s306, s612, l, ast_ );
s1171 pt = l[0]->s366();
if( s306->TR().s1640( pt, s1687::s1682 ) )
return new s1256( s306, s612, l );
s615::s1392( ( vector<s277*>& )l, s1257 );
s489 pc = l[0]->s513();
vector<s277*> s999;
size_t s390 = 0;
if( pc == s491 ) {
if( pt == s1284 ) {
if( l.size() > 1 && l[1]->s366() == s1284 ) {
s999 = { l[0], l[1] };
s390 = 1;}
else {
s999 = { l[0] };
s390 = 2;}}}
else if( pc == s1173 ) {
if( ( (s386*)l[0] )->s1467() == s1380 ) {
s999 = { l[1] };
s390 = 2;}
else if( ( (s386*)l[0] )->s1467() == s1372 ) {
s999 = { l[1], l[3] };
s390 = 4;}}
vector<s277*> l1 = { new s1040( s306, s612, s999 ) };
l1.insert( l1.end(), l.begin() + s390, l.end() );
return new s1256( s306, s612, l1 );
if( l.size() ) {
if( l[0]->s513() == s492 ) {
l[0]->s519( s612 );
if( s306->TR().s1640( l[0]->s366(), s1687::s1682 )  )
return new s1256( s306, s612, l );}}
else {
return new s1256( s306, s612, l );}
return new s1040( s306, s612, l );}
s501* s1256::s370( s278* s612, const std::vector<s1171>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1256* s717 = new s1256( s306, L"" );
s868::Cont s1183;
s509::s1108( vt, idx, s1183 );
s868 s1181( s1183[0] );
return s717;}
inline bool
s1256::s521( const s501* s522 ) const{
return ( ((s1256*)s522)->s366() == s366() );}
inline void s1256::s1384( s501** s280, size_t s517 ){
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
s1256* pf = (s1256*)s280[1];
*s280 = ( s501* ) pf->s370( pf->ns, v, pf->s627() );
s280[0]->s519( pf->ns );
pf->s1085.s397( s280[0] );
pf->s1086 = ((s1256*)s280[0])->s1086;}
inline void s1256::s1517( s501** s280, size_t s517 ){
s1256* pf = (s1256*)s280[1];
*s280 = ( s501* ) pf->s306->TR().
s1107( pf->s1522 )->s370( pf->ns );
Iterator* s1124 = pf->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
if( p.s13() )
break;
( (s323*)s280[0] )->add( p->s349() );}
s280[0]->s1413();}
s277* s1256::s349() const{
return new s1256( *this );}
void s1256::s371( s277* p ) const{
p = new s1256( *this );}
size_t s1256::s330() const{
return (size_t)this;}
bool s1256::operator==( const s501* p ) const{
return ( this == p );}
bool s1256::operator<( const s501* p ) const{
return false;}
bool
s1256::s579( const wstring& s708, s386* ref, const wstring& s346 ) const{
if( s708 == s7::s1545 ) {
ref->s1511( (s386*)&s1085 );
return true;}
return false; // ns->s579( s708, ref, s346 );
}
s277* s1256::s622( size_t off ){
assert( off == 0 );
if( s1086 )
return s1086;
return (s277*) s1085.s523();}
s1268 s1256::s1337(){
if( range.s14() )
return range->s1337();
else
return s1082.s15<s336*>()->s1337();}
Iterator* s1256::s321( s400* r ){
if( range.s14() ) {
s1268 pr = range->s1337( );
s325 = pr.first;
s1664 = pr.second;}
else {
s1268 pr = s1082.s15<s336*>()->s1337();
s325 = pr.first;
s1664 = pr.second;}
return this;}
s277* s1256::s322(){
while( 1 ) {
s1086 = s325->s322();
if( !s1086 || s325->operator==( s1664 ) )
return NULL;
if( where.s14() && ( false == (bool)*where->s516(0,0) ) )
continue;
break;}
if( s1180.s14() )
return s1180->s516( 0, 0 ).s15<s502*>();
else
return s1086;}
s277* s1256::s1053(){
return s325->s1053();}
const s277* s1256::s1053() const{
return NULL;}
s277* s1256::Idx(){
return NULL;}
s277* s1256::El(){
return NULL;}
void s1256::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s201 ) << L"Input: ";
if( s612.s14() ) {
s1082.s14() ? s1082->s310( pd, s201 + s434 ) : s612->s310( pd, s201 + s434 );}
buf << s4::fill_n_ch( L' ', s201 ) << L"Do: ";
if( s1180.s14() ) s1180->s310( pd, s201 + s434 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s201 ) << L"curitref: ";
s1085.s310( pd, 0 );
buf << endl;}
s1040::s1040( s268* s306 ) 
: s336( s306, NULL, NULL ) {
s512 = s1469.s13() ? 0 : s1469->s366();}
s1040::s1040( s268* s306, s278* s612, const std::vector<s277*>& l, const s269* ast_ )
: s336( s306, s612, ast_ ), s1155( true ){
if( l.empty() )
return;
wstring s1096 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s1096 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s512 = s1469->s366();}
s1040::~s1040(){}
s501* s1040::s369( const s269& s736, s278* s612, const wstring& s346 ){
wstring s = s736.s297();
wstring s361 = s368();
if( s.find( s361 ) == 0 && ( s.size() == s361.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s53( s.substr( s361.size() ), s49 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s731 = L"Malformed Sequence definition: " + s;
vector<s277*> s740;
s277::s1501( s736, s306, s612, s346, s740 );
return new s1040( s306, s612, s740 );}
else
return NULL;}
s501* s1040::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1040( s306, s612, l, ast_ );}
void s1040::s519( const s278* s961 ){
if( end.s13() )
return;
wstring s1096 = L"wrong sequence generator syntax";
s503 tmp = s277::s1121( s306, end, (s278*)s961, (s615*)s961, s961->s304() );
end = tmp;
if( start.s14() ) {
tmp = s277::s1121( s306, start, (s278*)s961, (s615*)s961, s961->s304() );
start = tmp;}
else {
if( end->s366() == s1284 )
start = new s360( s306, 0 );
else {
start = s306->TR().s541( end->s366(), (s278*)s961, s961->s304() );
start->s519( s961 );}}
if( incr.s14() ) {
tmp = s277::s1121( s306, incr, (s278*)s961, (s615*)s961, s961->s304() );
incr = tmp;}
else {
if( start->s366() == s1284 )
incr = new s360( s306, 1 );
else
throw new s16( s1096 + L": increment value is missing" );}
s1087 = start->s349();
s1836 = start->s349();
std::vector<s277*> pl = { s1087, incr };
s584 cs( s306, L"sumeq", pl, NULL );
s1168 = s615::s624( &cs, s306, (s278*)s961, (s615*)s961, s961->s304() );
s1168->s519( s961, false );
std::vector<s277*> pl1 = { s1087, start };
s584 cs1( s306, L"set", pl1, NULL );
set = s615::s624( &cs1, s306, (s278*)s961, (s615*)s961, s961->s304() );
set->s519( s961, false );
std::vector<s277*> pl2 = { s1087, end };
s584 cs2( s306, L"eq", pl2, NULL );
eq = s615::s624( &cs2, s306, (s278*)s961, (s615*)s961, s961->s304() );
eq->s519( s961, false );
s1343 = s1284;
s334 = start->s366();}
s1268 s1040::s1337(){
s1::s1444<Iterator> it = this;
s1::s1444<Iterator> it1 = it;
return make_pair( it, it1 );}
Iterator* s1040::s321( s400* r ){
set->s516( 0, 0 );
s1155 = true;
return this;}
s277* s1040::s322(){
if( s1155 )
s1155 = false;
else
s1168->s516( 0, 0 );
if( (bool)*eq->s516( 0, 0 ) )
return NULL;
s1087.s15<s501*>()->s371( s1836 );
s1836->s1413();
return s1836;}
void s1040::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s1040::s1384, s1469->s366(),
{ s1239( { s1284 } ), s1239( { s1284, s1284 } ), s1239( { s1284, s1284, s1284 } ) }, 
1, 2 ) ) );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
bool s1040::operator==( const Iterator* p ) const{
return false;}
bool s1040::operator<( const Iterator* p ) const{
return this < p;}
inline void s1040::s1384( s501** s280, size_t s517 ){
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
*s280 = ( s501* ) new s1040( ( (s1040*)s280[1] )->s306, NULL, v );
s280[0]->s519( ((s1040*)s280[1])->ns );}
s277* s1040::s349() const{
return new s1040( *this );}
void s1040::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"SequenceGenerator : " << endl;
start->s310( pd, s201 + s434); buf << L", "; end->s310( pd, 0); 
buf << L", "; incr->s310( pd, 0 );}
s1171 s1687::s1682 = 0;
s1171 s1687::s1681 = 0;
s1171 s1687::s1683 = 0;
bool _cmp( const s503& l_, const s503& r_ ){
s501* l = l_.s15<s501*>();
s501* r = r_.s15<s501*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s503 l, const s503 r ) const{
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
struct s1295{
std::vector<s503>s933;
s506 s931;
s1295( /*s506 s932*/ ) : s931( /*s932*/0 ) { s933.resize( 2 ); }
bool operator()( const s503& l, const s503& r ){
if( s931.s14() ) {
s933[0] = l;
s933[1] = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
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
struct s909;
s501* s336::sort( bool, s909* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s956 );}
template <class _Cont, class s1478, class Der>
s320<_Cont, s1478, Der>::s320( const s1311& r )
: s336( r ){}
void s1300( s268* s306, const wstring& s78, wstring& s1427, wstring& s673 ){
assert( !s78.empty() );
wstring sv = s78;
wsmatch s1184, rgres1;
wregex s1406( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
wregex s1407( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(.*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1184, s1407 ) ) {
s868::Cont vt;
s1427 = s1184[1].str();
if( regex_match( sv, rgres1, s1406 ) ) {
s673 = L"] " + //s1427 + L" " +
( s1184[s1184.size()-1].str().empty() ? L"0" : s1184[s1184.size()-1].str() );}
else {
s673 = s1184[2];}}}
s1267::s1267( s268* s306, const std::wstring& s78, const s269* ast_ )
: s350( s306, NULL, ast_ ), s334( 0 ){
if( proto.s13() )
s512 = 0;
else
s512 = proto->s366();
s1856( s7::s942 );}
s1267::s1267( const s1267& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s612( right.s612 ), s363( right.s363 ),
s334( right.s334 ){
s1413();}
s1267::s1267( s268* s306, s278* s612, Iterator* it, const s269* ast_ )
: s350( s306, NULL, ast_ ), s363( it ), s334( 0 ){
s1413();}
s501* s1267::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
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
void s1267::s519( const s278* s961 ){}
s1171 s1267::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get-el" )
s717 = s334;
return s717;}
s501* s1267::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1267( s306, L"", ast_ );}
s501* s1267::s370( s278* s612, const std::vector<s1171>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s868::Cont s1220;
s509::s1108( vt, idx, s1220 );
s1267* s717 = new s1267( s306, 0, NULL );
s717->ns = s612;
s717->s334 = s1220[0];
s868 s646( vt );
s717->s512 = s306->TR().s1111( vt );
return s717;}
void s1267::s364(){
s362.insert( std::make_pair( L"eq", new s351( L"eq", &s1267::s413, s1275,
{ s1239( {s7::s1566} ) }, 1, 1 ) ) );
s362.insert( std::make_pair( L"get-el", new s351( L"get-el", &s1267::s1766, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"neq", new s351( L"neq", &s1267::s418, s1275,
{ s1239( {s7::s1566} ) }, 1, 1 ) ) );
s362.insert( std::make_pair( L"set", new s351( L"set", &s1267::s402, s1286,
{ s1239( {s7::s1566} ) }, 1, 1 ) ) );
s362.equal_range( L"get-el" ).first->second->s1412( true );}
s277* s1267::s349() const{
return new s1267( *this );}
void s1267::s371( s277* p ) const{
p = new s1267( *this );}
size_t s1267::s330() const{
return (size_t)this;}
void s1267::operator=( const s1267& p ){
s612 = p.s612;
s363 = p.s363;
s334 = p.s334;
s512 = p.s512;}
bool s1267::operator==( const s501* p ) const{
return s363->operator==( ((s1267*)p)->s363 );}
bool s1267::operator<( const s501* p ) const{
return s363->operator<( ((s1267*)p)->s363 );}
#undef s733
#define s733 ((s1267*)(s502*)*s280)
#define s734 ((s375*)(s502*)*s280)
inline void s1267::s1766( s501** s280, size_t s517 ){
*s280 = (s501*)((s1267*)DR )->s363->s1053();}
inline void s1267::s413( s501** s280, size_t s517 ){
*s734->s372() = ( (s1267*)DR )->s363->operator==( ( (s1267*)s280[2] )->s363 );}
inline void s1267::s418( s501** s280, size_t s517 ){
*s734->s372() = !( (s1267*)DR )->s363->operator==( ( (s1267*)s280[2] )->s363 );}
inline void s1267::s402( s501** s280, size_t s517 ){
*(s1267*)DR = *(s1267*)s280[2];}
void s1267::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Position : " <<
this << endl;}
s1056::s1056( s323* v_, s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1358( (uint64_t)-1 ), s1314( new s1704(NULL, -1) ), 
s1313( new s1049(NULL, vector<s277*>( { s1314, s380 } )) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1056::s1056( s323* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1663( sent ), s1358( (uint64_t)-1 ), s1314( new s1704(NULL, -1) ), 
s1313( new s1049(NULL, vector<s277*>( { s1314, s380 } )) ){
if( v.s14() ) {
s1358 = v->size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s968 = true;}
s1056::s1056( s1056* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1704(NULL, 0) ), 
s1313( new s1049( NULL, vector<s277*>( { s1314, *s1359 } )) ){
s968 = it->s968;}
void s1056::reverse(){
s968 = true; 
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1056::s322(){
s277* s717 = NULL;
if( !s968 ) {
if( s1359 != s1201 ) {
s717 = *s1359;
s1359++;
s1358++;}}
else {
if( s1409 != s1663 ) {
s717 = *s1409;
s1409++;
s1358--;}}
return s717;}
s277* s1056::s1053(){
if( !s968 )
return *s1359;
else
return *s1409;}
const s277* s1056::s1053() const{
if( !s968 )
return *s1359;
else
return *s1409;}
s277* s1056::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1056::El(){
return *s1359;}
bool s1056::operator==( const Iterator* r ) const{
if( !s968 )
return s1359 == ((s1056*)r)->s1359;
else
return s1409 == ((s1056*)r)->s1409;}
bool s1056::operator<( const Iterator* r ) const{
if( !s968 )
return s1359 < ( (s1056*)r )->s1359;
else
return s1409 < ( (s1056*)r )->s1409;}
s1052::s1052( s793* v_, 
s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1358( (uint64_t)-1 ), s1314( new s1704( NULL, 0 ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1052::s1052( s1052* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1704( NULL, 0 ) ){}
s277* s1052::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = *s1359;
++s1359;
++s1358;}
return s717;}
s277* s1052::s1053(){
return *s1359;}
const s277* s1052::s1053() const{
return *s1359;}
s277* s1052::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1052::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
s1026::s1026( s332* v_, s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1314( s380 ), s1313( new s1049( NULL,
vector<s277*>(	{ s1314, s380 } ) ) ){}
s1026::s1026( s1026* it )
: v( it->v ), s1359( it->s1359 ), s1314( s380 ), s1313( new s1049( NULL, 
vector<s277*>(	{ s1314, s380 } ) ) ){}
s277* s1026::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = s1359->second;
++s1359;}
return s717;}
s277* s1026::s1053(){
return (*s1359).second.s15<s502*>();}
const s277* s1026::s1053() const{
return (*s1359).second.s15<s502*>();}
s277* s1026::Idx(){
return (*s1359).first.s15<s502*>();}
s277* s1026::El(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s1313->assign( vector<s503>(
{ ( *s1359 ).first.s15<s502*>(),( *s1359 ).second.s15<s502*>() } ));
s717 = s1359->second;
++s1359;}
return s717;}
void s1026::reverse(){
s968 = true;
s1409 = std::make_reverse_iterator( s1359 );}
bool s1026::operator==( const Iterator* r ) const{
if( !s968 )
return s1359 == ( (s1026*)r )->s1359;
else
return s1409 == ( (s1026*)r )->s1409;}
s1554::s1554( s1553* v_, s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1314( s380 ), s1313( new s1049( NULL,
vector<s277*>( { s1314, s1359->second } ) ) ){}
s1554::s1554( s1554* it )
: v( it->v ), s1359( it->s1359 ), s1314( s380 ), s1313( new s1049( NULL,
vector<s277*>( { s1314, s1359->second } ) ) ){}
s277* s1554::s322(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s717 = s1359->second;
++s1359;}
return s717;}
s277* s1554::s1053(){
return ( *s1359 ).second.s15<s502*>();}
const s277* s1554::s1053() const{
return ( *s1359 ).second.s15<s502*>();}
s277* s1554::Idx(){
return ( *s1359 ).first.s15<s502*>();}
s277* s1554::El(){
s277* s717 = NULL;
if( s1359 != v->s328().end() ) {
s1313->assign( vector<s503>(
{ ( *s1359 ).first.s15<s502*>(),( *s1359 ).second.s15<s502*>() } ) );
s717 = s1359->second;
++s1359;}
return s717;}
bool s1554::operator==( const Iterator* r ) const{
return s1359 == ( (s1554*)r )->s1359;}
s1449::s1449( s1448* v_, s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1358( (uint64_t)-1 ), s1314( new s1704( NULL, -1 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, s1453::proto } ) ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1449::s1449( s1448* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1663( sent ), s1358( (uint64_t)-1 ), s1314( new s1704( NULL, -1 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, s1453::proto } ) ) ){
if( v.s14() ) {
s1358 = v->size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s968 = true;}
s1449::s1449( s1449* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1704( NULL, 0 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, new s1453( NULL, *s1359)  } ) ) ){
s968 = it->s968;}
void s1449::reverse(){
s968 = true;
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1449::s322(){
s277* s717 = NULL;
if( !s968 ) {
if( s1358 < v->s328().size() )
s717 = new s1453( NULL, v->s328()[s1358++] );}
else {
if( s1358 != U64_MAX )
s717 = new s1453( NULL, v->s328()[s1358--] );}
return s717;}
s277* s1449::s1053(){
return new s1453( NULL, *s1359 );}
const s277* s1449::s1053() const{
return new s1453( NULL, *s1359 );}
s277* s1449::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1449::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
bool s1449::operator==( const Iterator* r ) const{
if( !s968 )
return s1359 == ( (s1449*)r )->s1359;
else
return s1409 == ( (s1449*)r )->s1409;}
bool s1449::operator<( const Iterator* r ) const{
if( !s968 )
return s1359 < ( (s1449*)r )->s1359;
else
return s1409 < ( (s1449*)r )->s1409;}
s1754::s1754( s374* v_, s1027 it, s1027 sent )
: v( v_ ), s1359( it ), s1201( sent ), s1358( (uint64_t)-1 ), s1314( new s1704( NULL, -1 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, s1749::proto } ) ) ){
if( v.s14() ) {
s1358 = std::distance( v->s328().begin(), it );
assert( s1358 >= 0 );}}
s1754::s1754( s374* v_, s1397 it, s1397 sent )
: v( v_ ), s1409( it ), s1663( sent ), s1358( (uint64_t)-1 ), s1314( new s1704( NULL, -1 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, s1749::proto } ) ) ){
if( v.s14() ) {
s1358 = v->s328().size() - std::distance( v->s328().rbegin(), it ) - 1;
assert( s1358 >= 0 );}
s968 = true;}
s1754::s1754( s1754* it )
: v( it->v ), s1359( it->s1359 ), s1358( it->s1358 ), s1314( new s1704( NULL, 0 ) ),
s1313( new s1049( NULL, vector<s277*>( { s1314, new s1749( NULL, *s1359)  } ) ) ){
s968 = it->s968;}
void s1754::reverse(){
s968 = true;
s1409 = std::make_reverse_iterator( s1359 );}
s277* s1754::s322(){
s277* s717 = NULL;
if( !s968 ) {
if( s1358 < v->s328().size() )
s717 = new s1749( NULL, v->s328()[s1358++] );}
else {
if( s1358 != U64_MAX )
s717 = new s1749( NULL, v->s328()[s1358--] );}
return s717;}
s277* s1754::s1053(){
return new s1749( NULL, *s1359 );}
const s277* s1754::s1053() const{
return new s1749( NULL, *s1359 );}
s277* s1754::Idx(){
*s1314->s372() = s1358 - 1;
return s1314;}
s277* s1754::El(){
*s1314->s372() = s1358 - 1;
return s1314;}
bool s1754::operator==( const Iterator* r ) const{
if( !s968 )
return s1359 == ( (s1754*)r )->s1359;
else
return s1409 == ( (s1754*)r )->s1409;}
bool s1754::operator<( const Iterator* r ) const{
if( !s968 )
return s1359 < ( (s1754*)r )->s1359;
else
return s1409 < ( (s1754*)r )->s1409;}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
vector<wstring> s1477( { L":typedTable", L":untypedTable" } );
s323::s323( s268* s306, s278* s612, const wstring& s78, const s269* ast_,
const wstring& s73 )
: s1752( s306, s612, ast_ ){
TDException s1060( s7::s1536, s1019, ast_ );
s1343 = s1284;
if( s78.size() ) {
load( s78, s612, s73 );}
if( !s512 )
s512 = ( s764.s13() ? 0 : s764->s366() );}
s323::s323( const s323& right, const s269* ast_ )
: s1752( right.s306, right.ns, ast_ ){
s363 = right.s363;
s1343 = right.s1343;
s334 = right.s334;
s324 = right.s324;
s512 = right.s512;
s1856( right.s644() );}
s323::s323( s268* s306, const std::vector<s277*>& l,
s278* s612, const s269* ast_, s1171 s744,	s1171 s1430 )
: s1752( s306, s612, ast_ ){
s1343 = s1284;
s334 = s1430;
s324 = s1430;
if( s744 )
s512 = s744;
else
s512 = s764.s13() ? 0 : s764->s366();
if( l.size() )
s615::s1392( ( vector<s277*>& )l, s1477 );
if( l.size() && ( l[0]->s366() == s366() ||
l[0]->s366() == s764->s366() ) ) {
s363.assign( ( (s323*)l[0] )->s363.begin(),
( (s323*)l[0] )->s363.end() );}}
s323::s323( s268* s306, s1171 s1431, s278* s612, const s269* ast_ )
: s1752( s306, s612, ast_ ){
s1343 = s1284;
s334 = s1431;
s324 = s1431;
if( s1431 ) {
s868::Cont v = { s764->s366(), 1, s334, 0 };
s512 = s306->TR().s1154( v );}}
s323::~s323(){
s363.clear();}
void s323::s1480( const vector<s277*>& s740, s278* s612 ){
assert(0);
TDException s1060( s7::s1458, s1019, s627() );
if( s740.empty() )
return;
s489 pc = s740[0]->s513();
if( pc == s492 && s612->s513() != s493 ) {
throw s1060.s1098( L"references are not allowed in constructors of data members" );}
/*if( s740[0]->s366() == s1288 ) {
wstring s1427, s673, s1417;
wstring s78 = s740[0]->to_wstring();
if( s78.empty() )
return;
if( s78[0] == L'[' ) {
s1417 = s78;}
else if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( s334, s612, s612->s899() ) );}
else {
if( s78.find( L'<' ) == string::npos )
throw new s16( L"wrong vector constructor syntax: missing element type" );
s1300( s306, s78, s1427, s673 );
if( !s673.empty() && s673[0] == L'[' )
s1417 = s673;
if( !s1427.empty() )
s1297( s1427, s512, s334 );}
if( !s1417.empty() )
load( s1417, s612, L"," );}
else*/ if( s740[0]->s366() == s366() ||
s740[0]->s366() == s764->s366() ) {
s363.assign( ( (s323*)s740[0] )->s363.begin(),
( (s323*)s740[0] )->s363.end() );}}
void s323::s1299( const wstring& s78, s278* s612, const wstring& s73 ){
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
load( s1417, s612, s73 );}
else if( !s673.empty() ) {
if( s673[0] == L']' && s673.find_first_not_of(
s4::digits + s4::s49, 1 ) == string::npos ) {
s363.push_back( 0 );
s363.push_back( new s374( s306, s673 ) );}}}
s1171 s323::s1338( const std::wstring& s1427, s868::Cont& s612 ){
s1171 s717;
s868::Cont vt;
size_t pos = 0;
s1171 s1431 = 0;
s306->TR().s1164( s1427, pos, vt );
s717 = s306->TR().s1111( s868( vt ), false );
if( s717 ) {
s612 = { s764->s366(), 1, vt[2], 0 };
return s717;}
s868::Cont s1437( begin( vt ) + 2, end( vt ) );
if( s1437.size() > 2 )
s1431 = s306->TR().s1154( s1437 );
else
s1431 = s1437[0];
s612 = { s764->s366(), 1, s1431, 0 };
s717 = s306->TR().s1154( s612 );
return s717;}
void s323::s1297( const std::wstring& s1427, s1171& pt, s1171& vt ){
s868::Cont s612;
pt = s1338( s1427, s612 );
vt = s612[2];}
void s323::load( const wstring& s78, s278* s612, const wstring& s73 ){
TDException s1060( s7::s1246, s1019, s627() );
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( s334, s612, s612->s304() ) );
return;}
size_t pos = 0;
const s1033* s1159 = NULL;
if( s627() && s627()->Nqj() )
s1159 = s627()->Nqj()->s1106();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1159, s78, pos, s96, true, s73 );
wstring ownerName = s627()->s274( L"ownerName" );
bool s1493 = false;
if( ( s627()->s274( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1493 = true;
if( s96.size() ) {
s1171 pt = 0;
for( size_t n = 0; n < s96.size(); ++n ) {
s1035 s230 = new s269( L"", *s96[n] );
s230->s1512( s334 );
s363.push_back( s277::s524( *s230, s306, s612, s612->s304() ) );
if( s363.back()->s513() != s492 ) {
if( n == 0 )
pt = s363.back()->s366();
else if( pt && s363.back()->s366() != pt )
throw s1060.s1098( L"different elements types in vector" );}}
if( !s1493 ) {
if( !s334 && s363[0]->s366() ) {
s334 = s363[0]->s366();
s868::Cont v1 = { s764->s366(), 1, s334, 0 };
s512 = s306->TR().s1154( v1 );}
else if( s334 != s363[0]->s366() )
throw s1060.s1098( L"vector's element type doesn't match the vector type" );}}}
s501* s323::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
TDException s1060( s7::s1459, s1019, &s736,
L"wrong Vector constructor syntax" );
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s361 = s368();
wstring s1427, s673;
s1171 pt = 0, vt = 0;
if( s736.s274( L"ownerType" ) == L"CallSite" ) {
wstring s1490 = s736.s274( L"ownerName" );
if( s1490.find( L"new<Vector<" ) == 0 ) {
wstring stype = s1490.substr( 4, s1490.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s1060.s1098( L"missing element type" );
s1300( s306, s, s1427, s673 );
if( !s673.empty() && ( s673[0] == L'[' || s673[0] == L']' ) )
sv = s673;
if( !s1427.empty() )
s1297( s1427, pt, vt );}
else
return 0;
s323* s717 = new s323( s306, vector<s277*>({ }), s612, &s736,
pt, vt );
s717->load( sv, s612, L"," );
return s717;}
void s323::s519( const s278* s961 ){
wstring s78 = L"";
TDException s1060( s7::s1010, s1019, s627() );
if( s363.size() == 2 && s363[0].s13() )
s78 = s363[1]->to_wstring();
if( s961->s513() != s493 ||
( (s278*)s961 )->s305() != L"new" || s306->s1497() ) {
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( s334, (s278*)s961, s961->s899() ) );}
else {
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s961 );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1204 = s277::s1121( s306, s363[n], (s278*)s961, (s615*)s961, s961->s304() );
s363[n] = s1204->s516( 0, 0 ).s15<s502*>();
if( !s334 )
s334 = s363[0]->s366();
else if( s334 != s363[n]->s366() )
throw s1060.s1098( L"elements have different types" );}}
if( s512 || s512 == s764->s366() ) {
if( !s334 )
throw s1060.s1098( L"vector's element type is not specified" );
s868::Cont s612 = { s764->s366(), 1, s334, 0 };
s512 = s306->TR().s1154( s612 );}
s1413();}}
void s323::s1061( const vector<s277*>& s740, s278* s612,
const s269* ast_ ){
TDException s1060( s7::s1011, s1019, ast_ );
bool typed;
wstring s1102 = L",";
wstring s1141 = L"\n";
wstring str = L"";
if( s740.size() < 2 )
throw s1060.s1098( L"too few arguments" );
if( ( (s386*)s740[0] )->s643() == L":typedTable" )
typed = true;
else if( ( (s386*)s740[0] )->s643() == L":untypedTable" )
typed = false;
else
throw s1060.s1098( L"unrecognized first parameter" );
if( s740.size() > 2 ) {
s1102 = s740[2]->to_wstring(); //s1165->to_wstring();
}
if( s740.size() > 3 ) {
s1141 = s740[3]->to_wstring(); //s1167->to_wstring();
}
if( s740[1]->s513() == s492 ) {
( (s386*)s740[1] )->s519( s612 );
str = ( (s386*)s740[1] )->s392()->to_wstring();}
else
str = s740[1]->to_wstring();
vector<wstring> s856;
s4::s58( s4::s53( str, s49 ), s1141, s856 );
for( wstring row : s856 ) {
if( typed ) {
s363.push_back( new s323( s306, s306, row, NULL, s1102 ) );}
else {
s1049* pd = (s1049*)s306->TR().s1107( s334 )->s349();
pd->load( row, s612, s1102 );
s363.push_back( pd );}}}
void s323::s364(){
s1752<s1590, s503, s323>::s364();
s362 = s1752<s1590, s503, s323>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s323::s1384, s1286,
{ s1239(), s1239( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s362.emplace( make_pair( L"set", new s351( L"set", &s323::s402, s1286,
{ s1239( { s1687::s1682 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"set-el", new s351( L"set-el", &s323::s1415, s1286,
{ s1239( { s1687::s1724, s7::s1569 } ) }, 2, 2 ) ) );
s362.emplace( make_pair( L"get", new s351( L"get", &s323::s337, 0,
{ s1239( { s1687::s1724 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"append", new s351( L"append", &s323::s1481, s1286,
{ s1239( { s7::s1569 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"resize", new s351( L"resize", &s323::s340, s1286,
{ s1239( { s1702 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"eq", new s351( L"eq", &s323::s413, s1284,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"load-table", new s351( L"load-table", &s323::s853,
s1284, { s1239( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"new" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1584, s1687::s1683 );
s306->TR().s1301( s512, s7::s1582, s1687::s1681 );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
s501* s323::s370( s278* s612, const vector<s277*>& l, const s269* ast_ ) const{
if( !s334 )
throw new s16( L"vector's element type is not specified" );
return new s323( s306, l, s612, ast_, s512, s334 );}
s501* s323::s370( s278* s612, const std::vector<s1171>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s323* s717 = new s323( s306, 0, NULL );
s717->ns = s612;
s717->s334 = vt[2];
s868 s646( vt );
s717->s512 = s306->TR().s1111( s646 );
return s717;}
s1171 s323::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get" )
s717 = s334;
else
s717 = s1752::s1331( s1728, l );
return s717;}
inline bool
s323::s521( const s501* s522 ) const{
return ( ( (s323*)s522 )->s324 == s324 );}
s277* s323::s349() const{
return new s323( *this );}
void s323::s371( s277* p ) const{
s323* pv = (s323*)p;
pv->s363.assign( s363.begin(), s363.end() );
pv->s1856( wh );}
Iterator* s323::s1304( const s501* idx ){
s1590::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i < 0 ) {
i = (int)s363.size() + i;
if( i < 0 )
i = 0;}
it = s363.begin() + i;}
return new s1056( this, it, it == s363.end() ? it : it+1 );}
Iterator* s323::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( it->s15<s501*>()->operator==( _val ) )
return new s1056( this, it, it+1 );
return new s1056( this, end( s363 ), end( s363 ));}
s501* s323::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1056*)it )->s1269() );
return new s360( s306, (int)n );}
Iterator* s323::s1328() {
return new s1056( this, s363.begin(), s363.begin()+1 ); }
Iterator* s323::s1332() {
return new s1056( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s323*)(s502*)*s280)
inline void s323::s1384( s501** s280, size_t s517 ){
s323* ps = (s323*)DR;
s323* s717;
if( s517 == 2 ) {
s717 = (s323*)( (s323*)s280[1] )->s349();}
else if( s280[2]->s1339().s366() == s764->s366() ) {
s717 = (s323*)( (s323*)s280[2] )->s349();}
else {
vector<s277*> v;
for_each( s280 + 2, s280 + s517, [&v]( s501* s363 )
{ return v.push_back( (s277*)s363 ); } );
s717 = new s323( ps->s306, v, ps->ns, ps->s627() );}
s717->s519( ps->ns );
*s280 = (s501*)s717;}
inline void s323::s402( s501** s280, size_t s517 ){
s323* v = ( (s323*)DR );
s336* seq = (s336*)s280[2];
Iterator* s1124 = seq->s321( NULL );
v->s363.clear();
while( 1 ) {
s503 p = s1124->s322();
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
inline void s323::s1481( s501** s280, size_t s517 ){
s323* pv = (s323*)DR;
const s501* s1727 = pv->s306->TR().s1107( pv->s334 );
( (s323*)DR )->s363.push_back( (s277*)s1727->s1711( s280[2] ) );}
inline void s323::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
int oldsize = (int)( (s323*)DR )->s363.size();
( (s323*)DR )->s363.resize( size );
for( int i = oldsize; i < size; ++i )
( (s323*)DR )->s363[i] = ( (s323*)DR )->s306->TR().s541(
( (s323*)DR )->s324, ( (s323*)DR )->s306, ( (s323*)DR )->s518 );}
/*
inline void s323::s341( s501** s280, size_t s517 ){
( (s323*)DR )->s363.clear();}
*/
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
inline void s323::s853( s501** s280, size_t s517 ){
s323* pv = ( (s323*)DR );
s489 pc = s280[2]->s513();
if( pc == s1173 ) {
if( ( (s386*)s280[2] )->s643().find( L"typedTable" ) != string::npos ) {
vector<s277*> s740( s517 - 2 );
for( size_t n = 2; n < s517; ++n )s740[n - 2] = s280[n];
pv->s1061( s740, pv->ns, pv->s627() );
return;}}
s336* seq = (s336*)s280[2];
Iterator* s1124 = seq->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
if( p.s13() )
break;
pv->s363.push_back( p );}}
struct s920{
vector<s503>& s363;
s920( vector<s503>& s730 ) : s363( s730 ) {}
bool operator()( const s503 l, const s503 r ) const{
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
s501* s323::sort( bool s968, s909* cmp ){
s920 s919( s363 );
if( s968 ) {
if( cmp )
std::sort( s363.rbegin(), s363.rend(), *cmp );
else
std::sort( s363.rbegin(), s363.rend(), s919 );}
else {
if( cmp )
std::sort( s363.begin(), s363.end(), *cmp );
else
std::sort( s363.begin(), s363.end(), s919 );}
return this;}
wstring s323::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"[";
if( s644() == s7::s942 )
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
return new s1056( this, begin( s363 ), end( s363 ) );
s1268 pr = rv->s1337( this );
return new s1056( this,
pr.first.s15<s1262*>()->s1269(), pr.second.s15<s1262*>()->s1269() );}
s793::s793( s268* s306, s278* s612, const wstring& s78,
const s269* ast_, const wstring& s73 )
: s336( s306, s612, ast_ ){
if( s78.size() ) {
vector<s1::s9<s6::s144>> s156;
const s1033* s1159 = NULL;
if( ast_ )
s1159 = ast_->Nqj()->s1106();
if( s78[0] == L'[' ) {
size_t pos = 0;
s6::s182( s1159, s78, pos, s156, true );}
else
s6::s182( s1159, s78, s156, true );
for( size_t n = 0; n < s156.size(); ++n ) {
s269 s230( L"", *s156[n] );
s363.push_back( s277::s524( s230, s306, s612, s612->s304() ) );}}
s512 = s787.s13() ? 0 : s787->s366();}
s793::s793( s268* s306, const vector<s277*>& l,
const s269* ast_ )
: s336( s306, NULL, ast_ ){
for( auto s1170 : l )
s363.push_back( s1170 );
s512 = s787->s366();}
s793::s793( const s793& right )
: s336( right ){
s363 = right.s363;
s512 = right.s512;}
s793::~s793(){
s363.clear();
s518.clear();}
void s793::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<s1::s9<s6::s144>>& s96, const s269* ast_, const wstring& s73 ){
assert( !s78.empty() );
if( s78[0] == L'[' ) {
size_t pos = 0;
const s1033* s1159 = NULL;
if( ast_ && ast_->Nqj() )
s1159 = ast_->Nqj()->s1106();
s6::s182( s1159, s78, pos, s96, true, s73 );}
else
s1300( s306, s78, s1427, s673 );}
s501* s793::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
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
return new s793( s306, s612, sv, &s736 );}
void s793::s519( const s278* s961 ){
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s961 );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1204 = s277::s1121( s306, s363[n], (s278*)s961, NULL, s961->s304() );
s363[n] = s1204;}
s512 = s787->s366();
s1856( s7::s941 );
s518 = s961->s899();}
void s793::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s793::s402, s1286,
{ s1239( { s1284, s7::s1565, s7::s1571 } ) }, 2, (size_t)-1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s793::s337, 0,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"fst", new s351( L"fst", &s793::s1100, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"snd", new s351( L"snd", &s793::s1185, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"append", new s351( L"append", &s793::s1481, s1286,
{ s1239( { s7::s1565, s7::s1571 } ) }, 1, (size_t)-1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s793::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"resize", new s351( L"resize", &s793::s340, s1286,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s793::s341, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s793::s413, s1284,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"fst" ).first->second->s1412( true );
s362.equal_range( L"snd" ).first->second->s1412( true );}
s501* s793::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s793( s306, s612, L"" );}
s501* s793::s370( s278* s612, const std::vector<s1171>& vt ) const{
assert( 0 );
return 0;}
s1171 s793::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"fst" )
s717 = s363[0]->s366();
else if( s1728 == L"snd" )
s717 = s363[1]->s366();
else if( s1728 == L"get" ) {
int n = (int)*l[0];
s717 = s363[n]->s366();}
return s717;}
inline bool
s793::s521( const s501* s522 ) const{
return ( ( (s323*)s522 )->s366() == s366() );}
s1171 s793::s327() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s277* s793::s349() const{
return new s793( *this );}
void s793::s371( s277* p ) const{
p = new s793( *this );}
void s793::assign( const vector<s503>& p ){
s363.assign( begin( p ), end( p ) );}
Iterator* s793::s1328() {
return new s1052( this, s363.begin(), s363.begin() + 1 ); }
Iterator* s793::s1332(){
return new s1052( this, s363.end(), s363.end() ); }
s1268 s793::s1337(){
return std::make_pair( s1328(), s1332() );}
#undef s733
#define s733 ((s793*)(s502*)*s280)
inline void s793::s402( s501** s280, size_t s517 ){
s280[3]->s371( ( (s793*)DR )->s363[(int)*s280[2]] );}
inline void s793::s337( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s793*)DR )->s363[(int)*s280[2]];}
inline void s793::s1100( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s793*)DR )->s363[0];}
inline void s793::s1185( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s793*)DR )->s363[1];}
inline void s793::s1481( s501** s280, size_t s517 ){
/*if( ( (s793*)DR )->s327() != s280[2]->s514() )
throw new s16( L"unmatched element type" );*/
( (s793*)DR )->s363.push_back( s280[2]->s349() );}
inline void s793::s339( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s793*)DR )->s363.size();}
inline void s793::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
( (s793*)DR )->s363.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s793*)DR )->s363[i] = ( (s793*)DR )->s306->s221(
( (s793*)DR )->s324, ( (s793*)DR )->s518 ).s15<s502*>();*/
}
inline void s793::s341( s501** s280, size_t s517 ){
( (s793*)DR )->s363.clear();}
inline void s793::s413( s501** s280, size_t s517 ){
size_t size = ( (s793*)DR )->s363.size();
s793* right = (s793*)s280[2];
if( right->s363.size() != size ) {
*( (s360*)*s280 )->s372() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s793*)DR )->s363[n] ) {
*( (s360*)*s280 )->s372() = 0;
return;}}
*( (s360*)*s280 )->s372() = 1;}
inline void s793::s342( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s793*)DR )->s363.size();}
wstring s793::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"UT[";
if( s644() == s7::s942 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += s363[n]->to_wstring() + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]";
return s717;}
void s793::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );}
size_t s793::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s363.size(); ++n )
s717 = s717 * ( ( s501* )&( *s363[n] ) )->s330() << 1;
return s717;}
bool s793::operator==( const s501* p ) const{
if( ( (s793*)p )->s363.size() != s363.size() )
return false;
for( size_t n = 0; n < s363.size(); ++n ) {
const s501* l = s363[n].s15<s501*>();
const s501* r = ( (const s793*)p )->s363[n].s15<s501*>();
if( !( *l == r ) )
return false;}
return true;}
bool s793::operator<( const s501* p ) const{
return false;}
Iterator* s793::s321( s400* rv ){
return NULL;}
/*s504 s793::s322()
{
if( s325 == s363.end() ) {
return NULL;}
s504 s717 = ( *s325 ).s15<s501*>();
s325++;
return s717;
}*/
s1049::s1049( s268* s306, s278* s612, const std::wstring& s78,
const s269* ast_, const std::wstring& s73 )
: s793( s306, ast_ ){
s1343 = s1284;
if( s78.size() ) {
s1299( s78, /*s1427, s673,*/ s612, s73 );
}
if( !s512 )
s512 = s1050.s13() ? 0 : s1050->s366();}
s1049::s1049( s268* s306, const std::vector<s277*>& l, const s269* ast_ )
: s793( s306, l, ast_ ){
s512 = s1050->s366();}
s1049::s1049( const s1049& right, const s269* ast_ )
: s793( right ){
s363.assign( begin( right.s363 ), end( right.s363 ) );
s512 = right.s512;
s324 = right.s324;
s1343 = right.s1343;
s334 = right.s334;}
s501* s1049::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
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
s1049* s717 = new s1049( s306, s612, sv, &s736 );
return s717;}
void s1049::s519( const s278* s961 ){
wstring s78 = L"";
TDException s1060( s7::s1010, s1019, s627() );
if( s363.size() == 2 && s363[0].s13() )
s78 = s363[1]->to_wstring();
if( s78[0] == L']' ) {
s363.clear();
wstring snum = s78.substr( s78.rfind( L" " ) );
s1035 ast_ = new s269( s78.substr( 9, s78.size() - snum.size() - 10 ), s627()->Nqj() );
size_t s166 = std::stoi( snum );
for( size_t n = 0; n < s166; ++n )
s363.push_back( s306->TR().s541( *(s269*)ast_, (s278*)s961, s961->s899() ) );}
else {
for( size_t n = 0; n < s363.size(); ++n ) {
if( s363[n]->s513() == s492 ) {
s363[n]->s519( s961 );
s363[n] = s363[n].s15<s386*>()->s392();}
s503 s1204 = s277::s1121( s306, s363[n], (s278*)s961, NULL, s961->s304() );
s363[n] = s1204;}}
s1856( s7::s941 );
s518 = s961->s304();}
void s1049::s364(){
s362.insert( make_pair( L"set", new s351( L"set", &s1049::s402, s1286,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s1049::s1416, s1286,
{ s1239( { s1284, s7::s1565, s7::s1571 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s1049::s337, 0,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"fst", new s351( L"fst", &s1049::s1100, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"snd", new s351( L"snd", &s1049::s1185, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"append", new s351( L"append", &s1049::s1481, s1286,
{ s1239( { s7::s1565, s7::s1571 } ) }, 1, (size_t)-1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1049::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"resize", new s351( L"resize", &s1049::s340, s1286,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s1049::s341, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"eq", new s351( L"eq", &s1049::s413, s1284,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"fst" ).first->second->s1412( true );
s362.equal_range( L"snd" ).first->second->s1412( true );}
s501* s1049::s370( s278* s612, const std::vector<s1171>& vt ) const{
s1049* s717 = new s1049( s306, NULL, L"" );
s868 s646( vt );
s717->s512 = s717->s324 = s717->s334 = s306->TR().s1111( s646 );
return s717;}
s501* s1049::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1049* s717 = new s1049( s306, l, ast_ );
return s717;}
void s1049::s1299( const wstring& s78, /*wstring& s1427, wstring& s673,*/
s278* s612, const wstring& s73 ){
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
load( s1417, s612, s73 );}
else if( !s673.empty() ) {
if( s673.find_first_not_of( s4::digits ) == string::npos ) {
s363.push_back( 0 );
s363.push_back( new s374( s306, s673 ) );}}}
void s1049::s1297( const std::wstring& s1427 ){
s868::Cont vt;
size_t pos = 0;
s306->TR().s1164( s1427, pos, vt );
s868::Cont s1437( begin( vt ), end( vt ) );
if( s1437.size() > 2 )
s334 = s306->TR().s1154( s1437 );
else
s334 = s1437[0];
s512 = s324 = s334;}
void s1049::load( const wstring& s78, s278* s612, const wstring& s73 ){
TDException s1060( s7::s1245, s1019, s627() );
size_t pos = 0;
const s1033* s1159 = NULL;
if( s627() && s627()->Nqj() )
s1159 = s627()->Nqj()->s1106();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1159, s78, pos, s96, true, s73 );
if( s96.size() ) {
s868::Cont s1433;
if( s512 ) {
const s868& vt = s306->TR().s1113( s512 );
s1433.assign( vt.s876().begin(), vt.s876().end() );
if( s96.size() != ( s1433.size() - 2 ) / 2 )
throw s1060.s1098( L"wrong number of elements passed for inititalizing tuple" );}
else
s1433.push_back( s1050->s366() );
for( size_t n = 0; n < s96.size(); ++n ) {
s269 s230( L"", *s96[n] );
s363.push_back( s277::s524( s230, s306, s612, s612->s304() ) );
if( s512 ) {
if( s363.back()->s366() != s1433[( n + 1 ) * 2] )
throw s1060.s1098( L"element type doesn't match the tuple definition" );}
else {
s1433.push_back( s363.back()->s366() );
s1433.push_back( 0 );}}
s1433.insert( s1433.begin() + 1, (s1171)( s1433.size() - 1 ) / 2 );
if( !s334 ) {
s512 = s306->TR().s1154( s1433 );
s334 = s324 = s512;}}
s1413();}
s1171 s1049::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"fst" )
s717 = s306->TR().s1113( s512 ).s366( ( 0 + 1 ) * 2 );
else if( s1728 == L"snd" )
s717 = s306->TR().s1113( s512 ).s366( ( 1 + 1 ) * 2 );
else if( s1728 == L"get" ) {
int n = (int)*l[0];
s717 = s306->TR().s1113( s512 ).s366( ( n + 1 ) * 2 );}
return s717;}
#undef s733
#define s733 ((s1049*)(s502*)*s280)
inline void s1049::s402( s501** s280, size_t s517 ){
s1049* s880 = ( (s1049*)DR );
if( s880->s366() != s280[2]->s366() )
throw new s16( L"mismatched types in assignment expression" );
s280[2]->s371( s880 );}
inline void s1049::s1416( s501** s280, size_t s517 ){
s1049* s880 = ( (s1049*)DR );
size_t idx = (int)*s280[2];
s277* el = s880->s363[idx];
if( ! s280[3]->s1716( el->s366()) )
throw new s16( L"mismatched types in assignment expression" );
s280[3]->s371( ( (s1049*)DR )->s363[(int)*s280[2]] );}
inline void s1049::s337( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1049*)DR )->s363[(int)*s280[2]];}
inline void s1049::s1100( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1049*)DR )->s363[0];}
inline void s1049::s1185( s501** s280, size_t s517 ){
*s280 = (s501*)(s277*)( (s1049*)DR )->s363[1];}
inline void s1049::s1481( s501** s280, size_t s517 ){
s1049* s880 = ( (s1049*)DR );
const s1049* pro = (s1049*)s880->s306->TR().s1107( DR->s366() );
size_t n = s880->s363.size();
if( n >= pro->s363.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s363[n]->s521( s280[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s793*)DR )->s327() != s280[2]->s514() )
*/
s880->s363.push_back( s280[2]->s349() );}
inline void s1049::s339( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s1049*)DR )->s363.size();}
inline void s1049::s340( s501** s280, size_t s517 ){
int size = (int)*s280[2];
( (s1049*)DR )->s363.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s793*)DR )->s363[i] = ( (s793*)DR )->s306->s221(
( (s793*)DR )->s324, ( (s793*)DR )->s518 ).s15<s502*>();*/
}
inline void s1049::s341( s501** s280, size_t s517 ){
( (s1049*)DR )->s363.clear();}
inline void s1049::s413( s501** s280, size_t s517 ){
size_t size = ( (s1049*)DR )->s363.size();
s1049* right = (s1049*)s280[2];
if( right->s363.size() != size ) {
*( (s360*)*s280 )->s372() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s363[n] != ( (s1049*)DR )->s363[n] ) {
*( (s360*)*s280 )->s372() = 0;
return;}}
*( (s360*)*s280 )->s372() = 1;}
inline void s1049::s342( s501** s280, size_t s517 ){
*( (s360*)*s280 )->s372() = (int)( (s1049*)DR )->s363.size();}
s277* s1049::s349() const{
return new s1049( *this );}
void s1049::s371( s277* p ) const{
*p = *this;}
wstring s1049::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"[[";
if( s644() == s7::s942 )
s717 += L"_not_set_";
else {
for( size_t n = 0; n < s363.size(); ++n )
s717 += s363[n]->to_wstring() + ( n == s363.size() - 1 ? L"" : L", " );}
s717 += L"]]";
return s717;}
s1448::s1448( s268* s306, s278* s612, const wstring& s78, const s269* ast_,
const wstring& s73 )
: s1573( s306, s612, ast_ ){
s1299( s78, s612, s73 );}
s1448::s1448( const s1448& right, const s269* ast_ )
: s1573( right.s306, NULL, ast_ ){
s363 = right.s363;
s1343 = right.s1343;
s334 = right.s334;
s324 = right.s324;
s512 = right.s512;}
s1448::s1448( s268* s306, const std::vector<s277*>& l, const s269* ast_ )
: s1573( s306, NULL, ast_ ){
s1299( L"", NULL, L"" );
if( l.size() ) {
s324 = l[0]->s366();
for( size_t n = 0; n < l.size(); ++n )
s363.push_back( *( (s1453*)l[n] )->s372() );}}
s1448::~s1448(){
s363.clear();}
void s1448::s1299( const wstring& s78, s501* s612, const wstring& s73 ){
s1343 = s1284;
s334 = s1475;
s868::Cont v = { s1050->s366(), 2, s1284, 0, s334, 0 };
s324 = s306->TR().s1154( v );
s512 = s1450->s366();
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
load( s1417, s612, s73 );}
else if( !s673.empty() ) {
if( s673[0] == L']' && s673.find_first_not_of(
s4::digits + s4::s49, 1 ) == string::npos ) {
wstring snum = s673.substr( s673.rfind( L" " ) );
size_t s166 = std::stoi( snum );
s363.resize( s166 );}}}
void s1448::load( const wstring& s78, s501* s612, const wstring& s73 ){
TDException s1060( s7::s1457, s1019, s627() );
size_t pos = 0;
const s1033* s1159 = NULL;
if( s627() && s627()->Nqj() )
s1159 = s627()->Nqj()->s1106();
vector<s1::s9<s6::s144>> s96;
s6::s182( s1159, s78, pos, s96, true, s73 );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
wstring sit = s96[n]->s172();
wstring snum = sit.substr( sit.rfind( L" " ) );
size_t s166 = std::stoi( snum );
s363.push_back( (tdbyte_t)s166 );}}}
s501* s1448::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
TDException s1060( s7::s1455, s1019, &s736,
L"wrong ByteArray constructor syntax" );
wstring s = s306->TR().s1429( s736.s297() );
wstring sv;
wstring s361 = s368();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s361 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s1060.s1098( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1448* s717 = new s1448( s306, s612, sv, &s736 );
return s717;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1488( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1448::s519( const s278* s961 ){
s1856( s7::s941 );
if( s961 )
s518 = s961->s899();}
void s1448::s364(){
s320<s1546, tdbyte_t, s1448>::s364();
s362 = s320<s1546, tdbyte_t, s1448>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1448::s1384, s1286,
{ s1239( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s362.emplace( make_pair( L"set", new s351( L"set", &s1448::s402, s1286,
{ s1239( { s1687::s1682 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"set-el", new s351( L"set-el", &s1448::s1415, s1286,
{ s1239( { s1284, s1284 } ) }, 2, 2 ) ) );
s362.emplace( make_pair( L"get", new s351( L"get", &s1448::s337, s1475,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"append", new s351( L"append", &s1448::s1481, s1286,
{ s1239( { s7::s1569 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"resize", new s351( L"resize", &s1448::s340, s1286,
{ s1239( { s1284 } ) }, 1, 1 ) ) );
s362.emplace( make_pair( L"eq", new s351( L"eq", &s1448::s413, s1275,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s306->TR().s1301( s512, s7::s1584, s1687::s1683 );
s306->TR().s1301( s512, s7::s1582, s1687::s1681 );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
s501* s1448::s370( s278* s612, const vector<s277*>& l, const s269* ast_ ) const{
return new s1448( s306, s612, L"", ast_ );}
s501* s1448::s370( s278* s612, const std::vector<s1171>& vt ) const{
return new s1448( s306, s612, L"" );}
inline bool
s1448::s521( const s501* s522 ) const{
return ( ( (s1448*)s522 )->s366() == s366() );}
s277* s1448::s349() const{
return new s1448( *this );}
void s1448::s371( s277* p ) const{
p = new s1448( *this );}
Iterator* s1448::s1304( const s501* idx ){
s1546::iterator it;
int i = (int)*idx;
if( i >= (int)s363.size() )
it = s363.end();
else {
if( i == -1 )
it = end( s363 );
else if( i < 0 ) {
i = (int)s363.size() + ( i + 1 );
if( i < 0 )
throw new s16( L"wrong range definition: a negative index is beyond vector boundaries" );}
else
it = s363.begin() + i;}
return new s1449( this, it, it + 1 );}
Iterator* s1448::s1326( const s501* _val ){
for( auto it = begin( s363 ); it != end( s363 ); ++it )
if( *it == *( (s1453*)_val )->s372() )
return new s1449( this, it, it + 1 );
return new s1449( this, end( s363 ), end( s363 ) );}
s501* s1448::s1333( Iterator* it ){
size_t n = std::distance( begin( s363 ), ( (s1449*)it )->s1269() );
return new s360( s306, (int)n );}
Iterator* s1448::s1328() {
return new s1449( this, s363.begin(), s363.begin() + 1 ); }
Iterator* s1448::s1332() {
return new s1449( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s1448*)(s502*)*s280)
inline void s1448::s1384( s501** s280, size_t s517 ){
s1448* ps = (s1448*)DR;
s1448* s717 = new s1448( ps->s306, ps->s627() );
s717->s519( ps->ns );
*s280 = (s501*)s717;}
inline void s1448::s402( s501** s280, size_t s517 ){
s1448* v = ( (s1448*)DR );
s336* seq = (s336*)s280[2];
Iterator* s1124 = seq->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
if( p.s13() )
break;
v->s363.push_back( *p.s15<s1453*>()->s372() );}}
inline void s1448::s1415( s501** s280, size_t s517 ){
assert( s280[3]->s366() == s1284 );
assert( s280[2]->s366() == s1284 );
s1448* v = ( (s1448*)DR );
size_t idx = (size_t)(int)*s280[2];
v->s363[idx] = *( (s1453*)s280[3] )->s372();}
inline void s1448::s337( s501** s280, size_t s517 ){
s1453* s717 = new s1453( ( (s1448*)DR )->s306,
( (s1448*)DR )->s363[(int)*s280[2]] );
*s280 = (s501*)(s277*)s717;}
inline void s1448::s1481( s501** s280, size_t s517 ){
assert( s280[2]->s366() == s1475 );
( (s1448*)DR )->s363.push_back( *( (s1453*)s280[2] )->s372() );}
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
wstring s1448::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"[";
if( s644() == s7::s942 )
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
s1268 pr = rv->s1337( this );
return new s1449( this,
pr.first.s15<s1262*>()->s1269(), pr.second.s15<s1262*>()->s1269() );}
s332::s332( s268* s306, s1171 s1344, s1171 s1430, 
s278* s612, const s269* ast_ )
: s1540( s306, s612, ast_ ){
assert( s1344 && s1430 );
this->s1343 = s1344;
s334 = s1430;
s868 s1324( s868::Cont( { s1050->s366(), 2, s1343, 0, s334, 0 } ) );
s324 = s306->TR().s1111( s1324 );
s868 s1829( s868::Cont( { s770->s366(), 1, s324, 0 } ) );
s512 = s306->TR().s1111( s1829 );}
s332::s332( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1540( s306, s612, ast_ ){
TDException s1060( s7::s1539, s1019, ast_ );
if( s78.size() ) {
wstring s673, s1427;
vector<pair<wstring, s1::s9<s6::s144>>> s96;
s1299( s78, s1427, s673, s96, ast_ );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
s1035 s1070 = new s269( s96[n].first, s627()->Nqj() );
s501* s1166 = (s501*)s277::s524( *s1070, s306, s612, s612->s304() );
basic_stringstream<wchar_t> s1195;
s96[n].second->s158( &s1195 );
s1035 s230 = new s269( s1195.str(), s627()->Nqj() );
s501* s1175 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
if( !s1343 ) {
s1343 = s1166->s366();
s334 = s1175->s366();}
if( s1343 != s1166->s366() || s334 != s1175->s366() )
throw s1060.s1098( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1166, s1175 ) );}}
else if( s673.size() ) {
s868::Cont vt, s1128, s1220;
size_t pos = 0;
s306->TR().s1164( s78, pos, vt );
size_t idx = 2;
s509::s1108( vt, idx, s1128 );
if( s1128.size() > 2 )
s1343 = s306->TR().s1111( s868( s1128 ), false );
else
s1343 = s306->TR().s1111( 
s868( s868::Cont( { s1128[0] } ) ) );
if( !s1343 ) {
if( s1128.size() > 2 )
s1343 = s306->TR().s1154( s1128 );
else
s1343 = s1128[0];}
s509::s1108( vt, idx, s1220 );
if( s1220.size() > 2 )
s334 = s306->TR().s1111( s868( s1220 ), false );
else
s334 = s306->TR().s1111(
s868( s868::Cont( { s1220[0] } ) ) );
if( !s334 ) {
if( s1220.size() > 2 )
s334 = s306->TR().s1154( s1220 );
else
s334 = s1220[0];}}
else if( false && s78[0] == L'(' ) {
wstring sv = s4::s53( s78.substr( 1, s78.size() - 2 ), L" " );
wsmatch s1184;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1184, rg ) ) {
wstring s1208 = s1184[1].str();
wstring s1209 = s1184[2].str();
sv = L"Index(" + s1208 + L" " + s1209 + L")";
s518 = sv;}}
else
assert( 0 );// s518 = s78;
}
if( s770.s13() )
s512 = 0;
else {
if( s1343 ) {
s324 = s306->TR().s1154( s868::Cont( { s1050->s366(), 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1154( s868::Cont( { s770->s366(), 1, s324, 0 } ) );}
else {
s324 = s512 = 0;}}}
s332::s332( const s332& right, const s269* ast_ )
: s1540( right.s306, NULL, ast_ ){
s363 = right.s363;
s512 = right.s512;}
s332::s332( s268* s306, const std::vector<s277*>& l,
s278* s612, const s269* ast_, s1171 s744, s1171 s1323,
s1171 s1815, s1171 s1430 )
: s1540( s306, s612, ast_ ){
s1343 = s1815;
s334 = s1430;
s324 = s1323;
s512 = s744;
if( l.size() && ( l.front()->s366() == s366() ||
l.front()->s366() == s770->s366() ) ) {
s363 = ( (s332*)l.front() )->s363;}}
void s332::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<pair<wstring, s145>> s96, const s269* ast_ ){
assert( !s78.empty() );
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1033 s1160( L"" );
s1160.s174( s78, pos, ob, true );
ob->s163( s96 );}
else
s1300( s306, s78, s1427, s673 );}
void s332::s1297( const std::wstring& s1427, s1171& pt, 
s1171& et, s1171& kt, s1171& vt ){
s868::Cont s612;
pt = s1338( s1427, s612, et, kt, vt );}
s501* s332::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s = s736.s297();
wstring si;
wstring sv, s1427, s673;
wstring s361 = s368();
s1171 pt = 0, et = 0, kt = 0, vt = 0;
if( s736.s274( L"ownerType" ) == L"CallSite" ) {
wstring s1490 = s736.s274( L"ownerName" );
if( s1490.find( L"new<Index<" ) == 0 ) {
wstring stype = s1490.substr( 4, s1490.size() - 5 );
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
s1171 s332::s1338( const std::wstring& s1427, s868::Cont& s612,
s1171& et, s1171& kt, s1171& vt ){
s1171 s717;
s868::Cont s1433;
size_t pos = 0;
s306->TR().s1164( s1427, pos, s1433 );
s717 = s306->TR().s1111( s868( s1433 ), false );
if( s717 ) {
s612 = { s770->s366(), 1, s1433[2], 0 };
et = s1433[2];
const s868& s1090 = s306->TR().s1113( et );
kt = s1090.s366( 2 );
vt = s1090.s366( 4 );
return s717;}
s868::Cont s1643, s1690;
size_t idx = 2;
s509::s1108( s1433, idx, s1643 );
s868 s1128( s1643[0] );
kt = s306->TR().s1111( s1128 );
s509::s1108( s1433, idx, s1690 );
if( s1690.size() > 2 )
vt = s306->TR().s1154( s1690 );
else
vt = s1690[0];
et = s306->TR().s1154( 
s868::Cont( { s1050->s366(), 2, kt, 0, vt, 0 } ) );
s612 = { s770->s366(), 1, et, 0 };
s717 = s306->TR().s1154( s612 );
return s717;}
void s332::load( const std::wstring& s78, s278* s612, const std::wstring& s73 ){
TDException s1060( s7::s1774, s1019, s627() );
vector<pair<wstring, s1::s9<s6::s144>>> s96;
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1033 s1160( L"" );
s1160.s174( s78, pos, ob, true );
ob->s163( s96 );}
if( s96.empty() )
return;
wstring ownerName = s627()->s274( L"ownerName" );
bool s1493 = false;
if( ( s627()->s274( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1493 = true;
for( size_t n = 0; n < s96.size(); ++n ) {
s1035 s1070 = new s269( s96[n].first, s627()->Nqj() );
s501* s1166 = (s501*)s277::s524( *s1070, s306, s612, s612->s304() );
s1166->s1413();
basic_stringstream<wchar_t> s1195;
s96[n].second->s158( &s1195 );
s1035 s230 = new s269( s1195.str(), s627()->Nqj() );
s501* s1175 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
s1175->s1413();
if( !s1343 ) {
s1343 = s1166->s366();
s334 = s1175->s366();}
if( s1343 != s1166->s366() || s334 != s1175->s366() )
throw s1060.s1098( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1166, s1175 ) );}
if( !s1493 ) {
if( !s324 && s363.begin()->second->s366() ) {
s324 = s306->TR().s1154( { s1050->s366(), 2, s363.begin()->first->s366(), 0,
s363.begin()->second->s366(), 0 } );
s868::Cont v1 = { s770->s366(), 1, s324, 0 };
s512 = s306->TR().s1154( v1 );}
else if( s334 != s363.begin()->second->s366() )
throw s1060.s1098( L"index' element type doesn't match the index type" );}}
void s332::s519( const s278* s961 ){
TDException s1060( s7::s1010, s1019, s627(), L"wrong Index definition" );
const wstring& s78 = s518;
if( s78.find( L"Index<" ) == 0 ) {
assert( 0 );
s868::Cont vt, s1128, s1220;
size_t pos = 0;
s306->TR().s1164( s78, pos, vt );
size_t idx = 2;
s509::s1108( vt, idx, s1128 );
s868 s1127( s1128[0] );
s1343 = s306->TR().s1111( s1127 );
s509::s1108( vt, idx, s1220 );
s868 s1217( s1220[0] );
s334 = s306->TR().s1111( s1217 );}
else if( s78[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s144>> s156;
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1033 s1160( L"" );
s1160.s174( s78, pos, ob, true );
vector<pair<wstring, s145>> s147;
ob->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1035 s1070 = new s269( s147[n].first, s627()->Nqj() );
s501* s1166 = (s501*)s277::s524( *s1070, s306, (s278*)s961, s961->s304() );
basic_stringstream<wchar_t> s1195;
s147[n].second->s158( &s1195 );
s1035 s230 = new s269( s1195.str(), s627()->Nqj() );
s501* s1175 = (s501*)s277::s524( *s230, s306, (s278*)s961, s961->s304() );
if( !s1343 ) {
s1343 = s1166->s366();
s334 = s1175->s366();}
if( s1343 != s1166->s366() || s334 != s1175->s366() )
throw s1060.s1098( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1166, s1175 ) );}}
s1413();}
void s332::s364(){
s1540<s1559, s504, s504, s332>::s364();
s362 = s1540<s1559, s504, s504, s332>::s356();
s362.insert( make_pair( L"insert", new s351( L"insert", &s332::s343, s1286,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s332::s829, 0,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s332::s337, 0,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get-val", new s351( L"get-val", &s332::s1638, 0,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s332::s402, s1286,
{ s1239( { s7::s1566 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"set-el", new s351( L"set-el", &s332::s1769, s1275,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s332::s344, s1286,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s332::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.equal_range( L"find" ).first->second->s1412( true );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"get-val" ).first->second->s1412( true );
s306->TR().s1301( s512, s7::s1582, s1687::s1681 );
s306->TR().s1301( s512, s7::s1583, s1687::s1682 );}
s501* s332::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1::s9<s332> s717 = new s332( s306, s612, L"", ast_ );
s717->s1343 = s1343;
s717->s334 = s334;
return s717;}
s501* s332::s370( s278* s612, const std::vector<s1171>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s868::Cont s1090;
s509::s1108( vt, idx, s1090 );
s868 s1089( s1090[0] );
s1171 s1323 = s306->TR().s1111( s1089 );
const s868& s1216 = s306->TR().s1113( s1323 );
s868::Cont s1128, s1220;
idx = 2;
s509::s1108( s1216.s876(), idx, s1128 );
s868 s1127( s1128[0] );
s1171 s1344 = s306->TR().s1111( s1127 );
s509::s1108( s1216.s876(), idx, s1220 );
s868 s1217( s1220[0] );
s1171 s1430 = s306->TR().s1111( s1217 );
s332* s717 = new s332( s306, s1344, s1430, s612, NULL );
return s717;}
s1171 s332::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get" ) {
s717 = s324;}
else if( s1728 == L"get-val" ) {
s717 = s324;}
else
s717 = s1540::s1331( s1728, l );
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
return new s1026( this, s363.begin(), ++it ); }
Iterator* s332::s1332() {
return new s1026( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s332*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
inline void s332::s343( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s332* dr = (s332*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s363.insert( make_pair( s155, s363 ) );}
inline void s332::s829( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s332::s337( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
throw new s16( L"key doesn't exist" );
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s332::s1638( s501** s280, size_t s517 ){
s332* p = (s332*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() ) {
*s280 = new s1049( p->s306, vector<s277*>(
{ (s501*)PARN( 2 ), (s501*)PARN( 3 ) } ) );}
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>()->s349(), it->second.s15<s502*>()->s349() } ) );}}
inline void s332::s402( s501** s280, size_t s517 ){
s332* l = (s332*)DR;
s332* right = (s332*)PARN( 2 );
*l = *right;}
inline void s332::s1769( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s332* dr = (s332*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1558::iterator it = dr->s363.find( (s501*)PARN( 2 ) );
if( it == dr->s363.end() ) {
s504 s1389 = (s501*)s363->s349();
s504 s1771 = (s501*)s155->s349();
dr->s363.insert( make_pair( s1771, s1389 ) );
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
s1268 pr = rv->s1337( this );
return new s1026( this,
pr.first.s15<s1262*>()->s1269(), pr.second.s15<s1262*>()->s1269() );}
wstring s332::to_wstring( uint32_t s1740 ) const{
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
s1553::s1553( s268* s306, s1171 s1344, s1171 s1430, const s269* ast_ )
: s1540( s306, NULL, ast_ ){
assert( s1344 && s1430 );
s1343 = s1344;
s334 = s1430;
s868 s1324( s868::Cont( { s1050->s366(), 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1111( s1324 );}
s1553::s1553( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s1540( s306, s612, ast_ ){
TDException s1060( s7::s1844, s1019, ast_ );
if( s78.size() ) {
wstring s673, s1427;
vector<pair<wstring, s1::s9<s6::s144>>> s96;
s1299( s78, s1427, s673, s96, ast_ );
if( s96.size() ) {
for( size_t n = 0; n < s96.size(); ++n ) {
s1035 s1070 = new s269( s96[n].first, s627()->Nqj() );
s501* s1166 = (s501*)s277::s524( *s1070, s306, s612, s612->s304() );
basic_stringstream<wchar_t> s1195;
s96[n].second->s158( &s1195 );
s1035 s230 = new s269( s1195.str(), s627()->Nqj() );
s501* s1175 = (s501*)s277::s524( *s230, s306, s612, s612->s304() );
if( !s1343 ) {
s1343 = s1166->s366();
s334 = s1175->s366();}
if( s1343 != s1166->s366() || s334 != s1175->s366() )
throw s1060.s1098( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1166, s1175 ) );}}
else if( s673.size() ) {
s868::Cont vt, s1128, s1220;
size_t pos = 0;
s306->TR().s1164( s78, pos, vt );
size_t idx = 2;
s509::s1108( vt, idx, s1128 );
s868 s1127( s1128[0] );
s1343 = s306->TR().s1111( s1127 );
s509::s1108( vt, idx, s1220 );
s868 s1217( s1220[0] );
s334 = s306->TR().s1111( s1217 );}
else if( false && s78[0] == L'{' ) {
s518 = s78;}
else if( false && s78[0] == L'(' ) {
wstring sv = s4::s53( s78.substr( 1, s78.size() - 2 ), L" " );
wsmatch s1184;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1184, rg ) ) {
wstring s1208 = s1184[1].str();
wstring s1209 = s1184[2].str();
sv = L"Index(" + s1208 + L" " + s1209 + L")";
s518 = sv;}}
else
assert( 0 );}
if( s1555.s13() )
s512 = 0;
else {
if( s1343 ) {
s324 = s306->TR().s1154( s868::Cont( { s1050->s366(), 2, s1343, 0, s334, 0 } ) );
s512 = s306->TR().s1154( s868::Cont( { s1555->s366(), 1, s324, 0 } ) );}
else {
s324 = s512 = 0;}}}
s1553::s1553( const s1553& right, const s269* ast_ )
: s1540( right.s306, NULL, ast_ ){
s363 = right.s363;
s512 = right.s512;}
void s1553::s1299( const wstring& s78, wstring& s1427, wstring& s673,
vector<pair<wstring, s145>> s96, const s269* ast_ ){
assert( !s78.empty() );
if( s78[0] == L'{' ) {
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1033 s1160( L"" );
s1160.s174( s78, pos, ob, true );
ob->s163( s96 );}
else
s1300( s306, s78, s1427, s673 );}
s501* s1553::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
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
return new s1553( s306, s612, si, &s736 );}
void s1553::s519( const s278* s961 ){
TDException s1060( s7::s1010, s1019, s627(), L"wrong Index definition" );
const wstring& s78 = s518;
if( s78.find( L"HashIndex<" ) == 0 ) {
assert( 0 );
s868::Cont vt, s1128, s1220;
size_t pos = 0;
s306->TR().s1164( s78, pos, vt );
size_t idx = 2;
s509::s1108( vt, idx, s1128 );
s868 s1127( s1128[0] );
s1343 = s306->TR().s1111( s1127 );
s509::s1108( vt, idx, s1220 );
s868 s1217( s1220[0] );
s334 = s306->TR().s1111( s1217 );}
else if( s78[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s144>> s156;
s1::s9<s6::s146> ob = new s6::s146( NULL );
size_t pos = 0;
s1033 s1160( L"" );
s1160.s174( s78, pos, ob, true );
vector<pair<wstring, s145>> s147;
ob->s163( s147 );
for( size_t n = 0; n < s147.size(); ++n ) {
s1035 s1070 = new s269( s147[n].first, s627()->Nqj() );
s501* s1166 = (s501*)s277::s524( *s1070, s306, (s278*)s961, s961->s304() );
basic_stringstream<wchar_t> s1195;
s147[n].second->s158( &s1195 );
s1035 s230 = new s269( s1195.str(), s627()->Nqj() );
s501* s1175 = (s501*)s277::s524( *s230, s306, (s278*)s961, s961->s304() );
if( !s1343 ) {
s1343 = s1166->s366();
s334 = s1175->s366();}
if( s1343 != s1166->s366() || s334 != s1175->s366() )
throw s1060.s1098( L"incompatible types in the index initialization list" );
s363.insert( make_pair( s1166, s1175 ) );}}
s518 = s961->s899();}
void s1553::s364(){
s1540<s1552, s504, s504, s1553>::s364();
s362 = s1540<s1552, s504, s504, s1553>::s356();
s362.insert( make_pair( L"insert", new s351( L"insert", &s1553::s343, s1286,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"find", new s351( L"find", &s1553::s829, 0,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get", new s351( L"get", &s1553::s337, 0,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"get-val", new s351( L"get-val", &s1553::s1638, 0,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"set", new s351( L"set", &s1553::s402, s1275,
{ s1239( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s1553::s344, s1286,
{ s1239( { s7::s1568 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1553::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.equal_range( L"find" ).first->second->s1412( true );
s362.equal_range( L"get" ).first->second->s1412( true );
s362.equal_range( L"get-val" ).first->second->s1412( true );}
s501* s1553::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
s1::s9<s1553> s717 = new s1553( s306, s612, L"", ast_ );
s717->s1343 = s1343;
s717->s334 = s334;
return s717;}
s501* s1553::s370( s278* s612, const std::vector<s1171>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s868::Cont s1090;
s509::s1108( vt, idx, s1090 );
s868 s1089( s1090[0] );
s1171 s1323 = s306->TR().s1111( s1089 );
const s868& s1216 = s306->TR().s1113( s1323 );
s868::Cont s1128, s1220;
idx = 2;
s509::s1108( s1216.s876(), idx, s1128 );
s868 s1127( s1128[0] );
s1171 s1344 = s306->TR().s1111( s1127 );
s509::s1108( s1216.s876(), idx, s1220 );
s868 s1217( s1220[0] );
s1171 s1430 = s306->TR().s1111( s1217 );
s1553* s717 = new s1553( s306, s1344, s1430, NULL );
return s717;}
s1171 s1553::s1331( const wstring& s1728, const vector<s503>& l ) const{
s1171 s717 = 0;
if( s1728 == L"get" ) {
s717 = s324;}
else if( s1728 == L"get-s" ) {
s717 = s324;}
return s717;}
inline bool
s1553::s521( const s501* s522 ) const{
return ( s522->s366() == s366() );}
s277* s1553::s349() const{
return new s1553( *this );}
void s1553::s371( s277* p ) const{
p = new s1553( *this );}
size_t s1553::s330() const{
return (size_t)this;}
bool s1553::operator==( const s501* p ) const{
return ( this == p );}
bool s1553::operator<( const s501* p ) const{
return false;}
Iterator* s1553::s1328() {
auto it = begin( s363 );
return new s1554( this, s363.begin(), ++it ); }
Iterator* s1553::s1332() {
return new s1554( this, s363.end(), s363.end() ); }
#undef s733
#define s733 ((s1553*)(s502*)*s280)
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
inline void s1553::s343( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s1553* dr = (s1553*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
dr->s363.insert( make_pair( s155, s363 ) );}
inline void s1553::s829( s501** s280, size_t s517 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s1553::s337( s501** s280, size_t s517 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() )
*s280 = NULL;
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>(), it->second.s15<s502*>() } ) );}}
inline void s1553::s1638( s501** s280, size_t s517 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s363.find( (s501*)PARN( 2 ) );
if( it == p->s363.end() ) {
*s280 = new s1049( p->s306, vector<s277*>(
{ (s501*)PARN( 2 ), (s501*)PARN( 3 ) } ) );}
else {
*s280 = new s1049( p->s306, vector<s277*>(
{ it->first.s15<s502*>()->s349(), it->second.s15<s502*>()->s349() } ) );}}
inline void s1553::s402( s501** s280, size_t s517 ){
s501* s155 = (s501*)PARN( 2 );
s501* s363 = (s501*)PARN( 3 );
s1553* dr = (s1553*)DR;
if( dr->s1343 != s155->s366() || dr->s334 != s363->s366() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1558::iterator it = dr->s363.find( (s501*)PARN( 2 ) );
if( it == dr->s363.end() ) {
s501* s1389 = (s501*)s363->s349();
dr->s363.insert( make_pair( (s501*)s155->s349(), s1389 ) );
*s280 = s384;}
else {
it->second = (s501*)s363->s349();
*s280 = s385;}}
inline void s1553::s344( s501** s280, size_t s517 ){
s1553* p = (s1553*)DR;
p->s363.erase( (s501*)PARN( 2 ) );}
inline void s1553::s339( s501** s280, size_t s517 ){}
inline void s1553::s342( s501** s280, size_t s517 ){}
Iterator* s1553::s321( s400* rv ){
s1268 pr = rv->s1337( this );
return new s1554( this,
pr.first.s15<s1262*>()->s1269(), pr.second.s15<s1262*>()->s1269() );}
wstring s1553::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"{ ";
for( auto it = begin( s363 ); it != end( s363 ); ++it )
s717 += ( it == begin( s363 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s717 += L" }";
return s717;}
void s1553::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s363.size(); ++n )
s363[n]->s310( pd, s201 + s434 );*/
}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
s430::s430( s268* s306, const wstring& s78, const s269* ast_ )
: s350( s306, NULL, ast_ ), s798( s306, s1288, NULL ), s861( s306, s1288, NULL ){
s512 = s866.s13() ? 0 : s866->s366();
s798.s11();
s861.s11();}
s430::s430( const s430& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ), s798( right.s306, NULL, L"" ), s861( right.s306, NULL, L"" ){
s798 = right.s798;
s861 = right.s861;
s512 = right.s512;}
s501* s430::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return new s430( s306, L"", &s736 );}
void s430::s519( const s278* s961 ){
s1413();}
void s430::s364(){
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s374::proto->s368() + L">";
s1171 s1692 = s764->s1338( ts, s1433 );
s362.insert( make_pair( L"new", new s351( L"new", &s430::s1384, s866->s366(),
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s430::s424, s1286,
{ s1239( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"read-rec", new s351( L"read-rec", &s430::s1854, s1286,
{ s1239( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"reset", new s351( L"reset", &s430::s431, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"files", new s351( L"files", &s430::s432, s1692,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"dirs", new s351( L"dirs", &s430::s1088, s1692,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s430::s339, s1284,
{ s1239() }, 0, 0 ) ) );}
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
s430* s831 = (s430*)DR;
s430* s717 = new s430( s831->s306, L"", s831->s627() );
s717->s519( s831->ns );
*s280 = s717;}
void _findFiles( const wstring& path, const wregex& rgPatt, vector<wstring>& s40,
vector<wstring>& s41 ){
vector<wstring> s838, s847;
s3::s32( path, L".*", s838, s847 );
for( size_t n = 0; n < s838.size(); ++n ) {
wstring s1853 = path + s838[n];
if( regex_match( s1853, rgPatt ) ) 
s40.push_back( s1853 );}
for( size_t n = 0; n < s847.size(); ++n ) {
if( s847[n] == L".." ||  s847[n] == L"." )
continue;
wstring s1853 = path + s847[n];
s41.push_back( s1853 );
s4::s62( s1853 );
_findFiles( s1853, rgPatt, s40, s41 );}}
inline void s430::s424( s501** s280, size_t s517 ){
wstring path = ((s374*)PARN( 2 ) )->to_wstring();
const wstring& s547 = ((s374*)PARN( 3 ))->to_wstring();
vector<wstring> s838, s847;
s430* s831 = (s430*)DR;
s831->s798.clear();
s831->s861.clear();
if( !s3::s760( path ) )
path = s831->s306->s752() + path;
s4::s62( path );
s3::s32( path, s547, s838, s847 );
std::sort( begin( s838 ), end( s838 ) );
std::sort( begin( s847 ), end( s847 ) );
for( auto f : s838 )
s831->s798.add( new s374( s831->s306, s4::s788( path + f ) ) );
for( auto f : s847 )
s831->s861.add( new s374( s831->s306, s4::s788( path + f ) ) );}
inline void s430::s1854( s501** s280, size_t s517 ){
wstring path = ( (s374*)PARN( 2 ) )->to_wstring();
const wstring& s547 = ( (s374*)PARN( 3 ) )->to_wstring();
wregex rg( s547 );
vector<wstring> s838, s847;
s430* s831 = (s430*)DR;
s831->s798.clear();
s831->s861.clear();
if( !s3::s760( path ) )
path = s831->s306->s752() + path;
s4::s62( path );
_findFiles( path, rg, s838, s847 );
std::sort( begin( s838 ), end( s838 ) );
std::sort( begin( s847 ), end( s847 ) );
for( auto f : s838 )
s831->s798.add( new s374( s831->s306, s4::s788( f ) ) );
for( auto f : s847 )
s831->s861.add( new s374( s831->s306, s4::s788( f ) ) );}
inline void s430::s431( s501** s280, size_t s517 ){
s430* s831 = (s430*)DR;
s831->s798.clear();
s831->s861.clear();}
inline void s430::s432( s501** s280, size_t s517 ){
*s280 = &( (s430*)DR )->s798;}
inline void s430::s1088( s501** s280, size_t s517 ){
*s280 = &( (s430*)DR )->s861;}
inline void s430::s339( s501** s280, size_t s517 ){
s430* s831 = (s430*)DR;
*( (s360*)*s280 )->s372() = (int)(s831->s798.size() + s831->s861.size());}
wstring s430::to_wstring( uint32_t s1740 ) const{
wstring s717;
for( size_t n = 0; n < s861.size(); ++n )
s717 += ( n ? L" \"" : L"\"" ) + s861[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s798.size(); ++n )
s717 += ( n ? L" \"":L"\"") + s798[n]->to_wstring() + L"\"";
return s717;}
void s430::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Directory : " << endl;
for( size_t n = 0; n < s861.size(); ++n )
s861[n]->s310( pd, s201 + s434 );
for( size_t n = 0; n < s798.size(); ++n )
s798[n]->s310( pd, s201 + s434 );}
size_t s430::s330() const{
size_t s717 = 0;
for( size_t n = 0; n < s861.size(); ++n )
s717 = s717 * ( (s501*)&(s861[n]) )->s330() << 1;
for( size_t n = 0; n < s798.size(); ++n )
s717 = s717 * ( (s501*)&(s798[n]) )->s330() << 1;
return s717;}
bool s430::operator==( const s501* p ) const{
if( ( (s430*)p )->s798.size() != s798.size() )
return false;
if( ( (s430*)p )->s861.size() != s861.size() )
return false;
for( size_t n = 0; n < s798.size(); ++n )
if( !( ( s277* )&( *s798[n] ) == (s277*)( (s430*)p )->s798[n] ) )
return false;
for( size_t n = 0; n < s861.size(); ++n )
if( !( ( s277* )&( *s861[n] ) == (s277*)( (s430*)p )->s861[n] ) )
return false;
return true;}
bool s430::operator<( const s501* p ) const{
return false;}
s1463::s1463( s268* s306, const wstring& s78, s278* ns_, const s269* ast_ )
: s350( s306, ns_, ast_ ){
s512 = s1464.s13() ? 0 : s1464->s366();
if( s78.size() ) {}}
s1463::s1463( const s1463& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ){
s512 = right.s512;}
s501* s1463::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
wstring s363, s;
wstring tn = s368();
if( s_.find( tn + L"(" ) == 0 ) {
s = s4::s53( s_.substr( tn.size() + 1, s_.size() - ( tn.size() + 1 ) ), 
s49 );
if( s.empty() )
return new s1463( s306, L"", s612 );}
else
s = s4::s53( s_, s49 );
return new s1463( s306, L"", s612 );}
void s1463::s519( const s278* s961 ){
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s374::proto->s368() + L">";
s1171 pt = s764->s1338( ts, s1433 );
s362.equal_range( L"files" ).first->second->s1414( pt
/*s306->TR().s1154( s868::Cont( { s764->s366(), s842->s366() }) )*/ );
s362.equal_range( L"dirs" ).first->second->s1414( pt
/*s306->TR().s1154( s868::Cont( { s764->s366(), s842->s366() }) )*/ );
}
void s1463::s364(){
s362.insert( make_pair( L"read", new s351( L"read", &s1463::s424, s1286,
{ s1239( { s1288, s1288 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"reset", new s351( L"reset", &s1463::s1524, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"files", new s351( L"files", &s1463::s1500, 0 /*s764->s366()*/,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"dirs", new s351( L"dirs", &s1463::s1491, 0 /*s764->s366()*/,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s1463::s339, s1284,
{ s1239() }, 0, 0 ) ) );}
s501* s1463::s370( s278* s612, const std::vector<s277*>& l, const s269* ast_ ) const{
return new s1463( s306, L"", s612, ast_ );}
inline bool
s1463::s521( const s501* s522 ) const{
return ( ((s1463*)s522)->s366() == s366() );}
s277* s1463::s349() const{
return s503( new s1463( *this ) );}
void s1463::s371( s277* p ) const{
p = new s1463( *this );}
#undef s733
#define s733 ((s1463*)(s502*)*s280)
inline void s1463::s424( s501** s280, size_t s517 ){}
inline void s1463::s1524( s501** s280, size_t s517 ){}
inline void s1463::s1500( s501** s280, size_t s517 ){}
inline void s1463::s1491( s501** s280, size_t s517 ){}
inline void s1463::s339( s501** s280, size_t s517 ){}
wstring s1463::to_wstring( uint32_t s1740 ) const{
wstring s717 = L"File";
return s717;}
void s1463::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"File : " << endl;}
size_t s1463::s330() const{
size_t s717 = 0;
return s717;}
bool s1463::operator==( const s501* p ) const{
return false;}
bool s1463::operator<( const s501* p ) const{
return false;}
vector<wstring> s1473( { L":append" } );
s1472::s1472( s268* s306, s278* s616, s615* s617,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1483, s736 ){
if( l.size() < 2 || l.size() > 3 )
throw new s16( L"malformed syntax of 'to-file' procedure call." );
s280.assign( l.begin(), l.end() );
s512 = s1286;
s615::s1392( ( vector<s277*>& )l, s1473 );}
void
s1472::s519( const s278* s1849, bool proc ){
obj = s280[0].s15<s501*>();
s214 = s277::s1121( s306, s280[1], s612, this, s304() );
if( s280.size() > 2 )
mode = s277::s1121( s306, s280[2], s612, this, s304() );}
s504 s1472::s516( s501** s740, size_t s517 ){
s489 pc = s280[0]->s513();
s1::s9<s336> s612;
if( pc == s493 ) {
s612 = s280[0]->s516( 0, 0 ).s15<s336*>();}
else
s612 = ((s336*)s280[0].s15<s386*>()->s392());
return 0;}
s277* s1472::s349()const{
return new s1472( *this );}
vector<wstring> s1783( { L":append" } );
s1782::s1782( s268* s306, s278* s616, s615* s617,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1793, s736 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s280.assign( l.begin(), l.end() );
s512 = s1286;
s615::s1392( ( vector<s277*>& )l, s1783 );}
void
s1782::s519( const s278* s1849, bool proc ){
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s1779::proto->s368() + L">";
s512 = s764->s1338( ts, s1433 );
s615::s519( s1849, proc );}
s504 s1782::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
s323* pv = s610.s15<s323*>();
wstring s198 = s607[1]->to_wstring();
vector<s9<s146>> s692;
s1036 s1159 = new s1033( s198 );
s1159->read( s692, /*s7::s1223*/ L"" );
for( size_t m = 0; m < s692.size(); m++ ) {
s1779* po = new s1779( pv->Pass(), this, s692[m], NULL );
pv->add( po );}
return s610;}
s277* s1782::s349()const{
return new s1782( *this );}
s1171 s1687::s1680 = 0;
s1171 s1687::s1684 = 0;
s1171 s1687::s1679 = 0;
void Stream::s1636( std::wstring& s156, size_t s1647 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1655( const std::wstring& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1637( std::wstring& s156, const std::wstring& s73 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1656( const std::wstring& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1635( s1489& s156, size_t s1647 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1654( const s1489& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1634( s1489& s156, const s1489& s73 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1653( const s1489& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
template<class s1592, class s1594>
void s1578<s1592, s1594>::s1742(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1650 )
*s1650 << std::resetiosflags( f );}
template<class s1592, class s1594>
void s1578<s1592, s1594>::s1743(){
if( s1650 )
*s1650 << std::showpos;}
template<class s1592, class s1594>
void s1578<s1592, s1594>::s1744( int n ){
if( s1650 )
*s1650 << std::setw( n );}
template<class s1592, class s1594>
void s1578<s1592, s1594>::s1741(){
if( s1650 )
*s1650 << std::showpos;}
s527::s527( s268* s306, s278* ns_, const s269* ast_ )
: s1578( s306, ns_, ast_ ){
s512 = s870.s13() ? 0 : s870->s366();
s1649 = (basic_istringstream<wchar_t>*) &ss;
s1650 = (basic_ostringstream<wchar_t>*) &ss;}
s527::s527( const s527& r, const s269* ast_ )
: s1578( r.s306, r.ns, ast_ ), ss( r.ss.str() ){
s512 = s870->s366();}
s501* s527::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s527( s306, s612, ast_ );}
void s527::s364(){
s1578<s1672,s1675>::s364();
s362 = s1578<s1672, s1675>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s527::s1384, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"str", new s351( L"str", &s527::s528, s1288,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s527::s341, s870->s366(),
{ s1239() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1581, s1687::s1680 );
s306->TR().s1301( s512, s7::s1586, s1687::s1684 );
s306->TR().s1301( s512, s7::s1580, s1687::s1679 );}
void s527::s519( const s278* s961 ){
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
if( p->s366() == s870->s366() )
((s527*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s366() ) );}
void s527::s1636( std::wstring& s156, size_t s1647 ){
s156 = ss.str().substr( 0, s1647 );}
void s527::s1655( const std::wstring& src ){
ss << src;}
void s527::s1637( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
s156.clear();
std::getline( ss, s156, s73[0] );}
void s527::s1656( const std::wstring& src ){
ss << src << endl;}
void s527::s1635( s1489& s156, size_t s1647 ){
s156 = (tdbyte_t*)U8( ss.str().substr( 0, s1647 )).data();}
void s527::s1654( const s1489& src ){
ss << U16( (char*)src.c_str() );}
void s527::s1634( s1489& s156, const s1489& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s73.c_str()) + L"'" );
s156.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s73.c_str())[0]);}
void s527::s1653( const s1489& src ){
ss << U16( (char*)src.c_str() ) << endl;}
wstring s527::to_wstring( uint32_t s1740 ) const{
return ss.str(); }
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s527*)(s502*)*s280)
inline void s527::s1384( s501** s280, size_t s517 ){
s527* ps = (s527*)DR;
s527* s717 = new s527( ps->s306, ps->ns, ps->s627() );
s717->s519( ps->ns );
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
s1451::s1451( s268* s306, s278* ns_, const s269* ast_ )
: s1578( s306, ns_, ast_ ){
s512 = s1452.s13() ? 0 : s1452->s366();
s1649 = (basic_istringstream<tdbyte_t>*) &bs;
s1650 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1451::s1451( const s1451& r, const s269* ast_ )
: s1578( r.s306, r.ns, ast_ ), bs( r.bs.str() ){
s512 = s1452->s366();}
s501* s1451::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s1451( s306, ast_ );}
void s1451::s364(){
s1578<s1670, s1673>::s364();
s362 = s1578<s1670, s1673>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1451::s1384, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"array", new s351( L"str", &s1451::s1482, s1288,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"clear", new s351( L"clear", &s1451::s341, s1452->s366(),
{ s1239() }, 0, 0 ) ) );
s306->TR().s1301( s512, s7::s1581, s1687::s1680 );
s306->TR().s1301( s512, s7::s1586, s1687::s1684 );
s306->TR().s1301( s512, s7::s1580, s1687::s1679 );}
void s1451::s519( const s278* s961 ){
s1413();}
void s1451::release(){
bs.clear();}
s501* s1451::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1451( s306 );
return NULL;}
s277* s1451::s349() const{
return new s1451( *this );}
void s1451::s371( s277* p ) const{
if( p->s366() == s1452->s366() )
((s1451*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s366() ) );}
void s1451::s1636( std::wstring& s156, size_t s1647 ){
s156 = U16( (char*)bs.str().c_str() ).substr( 0, s1647 );}
void s1451::s1655( const std::wstring& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1451::s1637( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
s156.clear();
s1489 tmp;
std::getline( bs, tmp, (unsigned char)U8(s73.data())[0] );}
void s1451::s1656( const std::wstring& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1451::s1635( s1489& s156, size_t s1647 ){
s156 = bs.str().substr( 0, s1647 );}
void s1451::s1654( const s1489& src ){
bs << src.data();}
void s1451::s1634( s1489& s156, const s1489& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s73.c_str()) + L"'" );
s156.clear();
std::getline( bs, s156, s73[0] );}
void s1451::s1653( const s1489& src ){
bs << src << endl;}
wstring s1451::to_wstring( uint32_t s1740 ) const{
s1489 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s1451*)(s502*)*s280)
inline void s1451::s1384( s501** s280, size_t s517 ){
s1451* ps = (s1451*)DR;
s1451* s717 = new s1451( ps->s306, ps->s627() );
s717->s519( ps->ns );
*s280 = (s501*)s717;}
inline void s1451::s1482( s501** s280, size_t s517 ){
s1489 s = ( (s1451*)DR)->bs.str();
( (s1448*)s280[0] )->s328().assign( begin( s ), end( s ) );}
inline void s1451::s341( s501** s280, size_t s517 ){
((s1451*)DR)->bs.rdbuf()->str(0);}
void s1451::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : [...]" << endl;}
size_t s1451::s330() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1451::operator==( const s501* p ) const{
return ( (s1451*)p )->bs.str() == bs.str();}
bool s1451::operator<( const s501* p ) const{
return bs.str() < ( (s1451*)p )->bs.str();}
s1461::s1461( s268* s306, s278* ns_, const s269* ast_ )
: s1578( s306, ns_, ast_ ){
s512 = s1462.s13() ? 0 : s1462->s366();
s1649 = NULL;
s1650 = NULL;}
s1461::s1461( s268* s306, const std::vector<s277*>& l, s278* s612,
const s269* ast_ )
: s1578( s306, s612, ast_ ){
s512 = s1462->s366();
s1649 = NULL;
s1650 = NULL;
if( l.size() ) {
if( l[0]->s366() == s1288 )
s1509 = l[0]->to_wstring();
else
s214 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1461::s1461( const s1461& r, const s269* ast_ )
: s1578( r.s306, r.ns, ast_ ), s214( r.s214 ), mode( r.mode ){
s512 = s1462->s366();
s1649 = NULL;
s1650 = NULL;}
s501* s1461::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
return new s1461( s306, ast_ );}
void s1461::s364(){
s1578<s1671, s1674>::s364();
s362 = s1578<s1671, s1674>::s356();
s362.insert( make_pair( L"new", new s351( L"new", &s1461::s1384, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"open", new s351( L"open", &s1461::s1500, s1286,
{ s1239(), s1239( { s1288 } ), s1239( { s1288, s1288 } ) }, 0, 2 ) ) );
s362.insert( make_pair( L"close", new s351( L"close", &s1461::s1491, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"read", new s351( L"read", &s1461::s424, s1286,
{ s1239( { s1450->s366(), s1284 } ) }, 2, 2 ) ) );
s362.insert( make_pair( L"read-lines", new s351( L"read-lines", &s1461::s1659, 0,	
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"write", new s351( L"write", &s1461::s1524, s1286,
{ s1239( { s1450->s366(), s1284 } ) }, 2, 2 ) ) );
s306->TR().s1301( s512, s7::s1581, s1687::s1680 );
s306->TR().s1301( s512, s7::s1586, s1687::s1684 );
s306->TR().s1301( s512, s7::s1580, s1687::s1679 );}
void s1461::s519( const s278* s961 ){
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s1450->s368() + L">";
s1171 pt = s764->s1338( ts, s1433 );
s362.equal_range( L"read-lines" ).first->second->s1414( pt );
s1413();}
void s1461::release(){
fs.close();}
s501*
s1461::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
wstring s_ = s736.s297();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s277*> s740;
s277::s1501( s736, s306, s612, s346, s740 );
return new s1461( s306, s740, s612, &s736 );}
return NULL;}
s277*
s1461::s349() const{
return new s1461( *this );}
void s1461::s371( s277* p ) const{
if( p->s366() == s1462->s366() ) {
((s1461*)p)->s214 = s214;
((s1461*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s368() + L" to " + 
p->s368() );}
void s1461::s1636( std::wstring& s156, size_t s1647 ){
size_t s1228 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1228;
fs.seekg( 0, ios_base::beg );
size_t s1678 = s1647 ? (std::min)( s1647, fsz ) : fsz;
string buf( s1678+1, '\0' );
fs.read( &buf[0], s1678 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1509 + L"'" );}
s156 = U16( buf.data() );}
void s1461::s1655( const std::wstring& src ){
fs << U8(src).data();}
void s1461::s1637( std::wstring& s156, const std::wstring& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s73 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s156.clear();
if( fs.eof() )
return;
string buf;
char s1646 = U8( s73.data() )[0];
std::getline( fs, buf, s1646 );
s156 = U16( buf.data() );}
void s1461::s1656( const std::wstring& src ){
fs << U8(src).data() << endl;}
void s1461::s1635( s1489& s156, size_t s1647 ){
size_t s1228 = fs.tellg();
size_t fsz = (size_t)fs.seekg( ios::end ).tellg() - s1228;
fs.seekg( s1228 );
size_t s1678 = s1647 ? (std::min)( s1647, fsz ) : fsz;
s156.resize( s1678 );
fs.read( (char*)&s156[0], s1678 );}
void s1461::s1654( const s1489& src ){
fs << *(string*)&src;}
void s1461::s1634( s1489& s156, const s1489& s73 ){
if( s73.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s73.c_str() ) + L"'" );
string buf;
s156.clear();
std::getline( fs, buf, (char)s73[0] );
std::swap( buf, *(string*)(&s156) );}
void s1461::s1653( const s1489& src ){
fs << *(string*)&src << endl;}
wstring s1461::to_wstring( uint32_t s1740 ) const{
return L"FileStream"; }
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
#undef s733
#define s733 ((s1461*)(s502*)*s280)
inline void s1461::s1384( s501** s280, size_t s517 ){
s1461* ps = (s1461*)DR;
s1461* s717 = new s1461( *ps );
s717->s519( ps->ns );
*s280 = (s501*)s717;}
inline void s1461::s1500( s501** s280, size_t s517 ){
s1461*pf = (s1461*)DR;
if( s517 > 2 ) {
if( s280[2]->s366() == s1288 ) {
pf->s1509 = s280[2]->to_wstring();
pf->s214 = NULL;}
else {
pf->s214 = s280[2];
pf->s1509 = L"";}
if( s517 > 3 ) {
pf->mode = s280[3];}}
pf->_open();}
inline void s1461::s1491( s501** s280, size_t s517 ){
((s1461*)DR)->_close();
((s1461*)DR)->s1649 = NULL;
((s1461*)DR)->s1650 = NULL;}
inline void s1461::s1524( s501** s280, size_t s517 ){
assert( s517 == 4 );
assert( s280[2]->s366() == s1450->s366() );
s1461*pf = (s1461*)DR;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1509 + L"'." );
s1448* s1502 = (s1448*)s280[2];
s501* s1504 = s280[3];
int s1518 = (int)*s1504;
pf->fs.write( (const char*)s1502->s328().data(), s1518 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1509 + L"'." );}
inline void s1461::s424( s501** s280, size_t s517 ){
assert(0);
((s1461*)DR)->_close();}
inline void s1461::s1659( s501** s280, size_t s517 ){
if( !((s1461*)DR)->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)((s1461*)DR)->addr();
s323& v = *(s323*)s733;
s1::s9<s1448> bar = new s1448( ( (s1461*)DR )->s306 );
while( !( (s1461*)DR )->fs.eof()) {
if( !std::getline( fs, *(string*)&bar->s328()/*, widen('\n')*/ ) )
throw new s16( L"cannot read from file '" + ( (s1461*)DR )->s1509 + L"'" );
v.s328().push_back( bar.s15<s502*>() );
v.s328().back()->s1413();
bar = new s1448( ( (s1461*)DR )->s306 );}}
void s1461::_open(){
if( fs.is_open() )
fs.close();
wstring path, s1513 = L"r";
if( !s1509.empty() )
path = s1509;
else {
if( s214->s513() != s492 )
path = s214->to_wstring();
else 
path = s214.s15<s386*>()->s392()->to_wstring();
s1509 = path;}
if( mode.s14() ) {
if( mode->s513() != s492 )
s1513 = mode->to_wstring();
else 
s1513 = mode.s15<s386*>()->s392()->to_wstring();}
if( !s3::s760( path ) )
path = s306->s752() + path;
s1649 = NULL;
s1650 = NULL;
std::ios_base::openmode md;
if( s1513.empty() || s1513 == L"r" ) {
md = ios::in | ios::binary;
s1649 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1513 == L"w" || s1513 == L"x" ) {
md = ios::out | ios::binary;
s1650 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1513 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1650 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1513 + L"'." );
if( s1513 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1461::_close(){
mode = s214 = NULL;
s1509.clear();
fs.close();}
void s1461::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << s368() << L" : " << s1509 << endl;}
size_t s1461::s330() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1461::operator==( const s501* p ) const{
return this == p;}
bool s1461::operator<( const s501* p ) const{
return this < p;}
s1574::s1574( s268* s306, s278* ns_, const s269* ast_ )
: s1578( s306, ns_, ast_ ){
s1649 = &std::wcin;}
s501* s1574::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1574::s364(){
s306->TR().s1301( s512, s7::s1581, s1687::s1680 );}
void s1574::s519( const s278* s961 ){
s1413();}
s501* s1574::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return NULL;}
s277* s1574::s349() const{
throw new s16( L"StdIn object cannot be copied" );}
void s1574::s371( s277* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1574::s1636( std::wstring& s156, size_t s1647 ){
s156.clear();
wcin >> s156;
if( s156.size() > s1647 )
s156.resize( s1647 );}
void s1574::s1655( const std::wstring& src ){
throw new s16( L"cannot output to StdIn" );}
void s1574::s1637( std::wstring& s156, const std::wstring& s73 ){
wcin >> std::ws;
s156.clear();
std::getline( wcin, s156 );}
void s1574::s1656( const std::wstring& src ){
throw new s16( L"cannot output to StdIn" );}
void s1574::s1635( s1489& s156, size_t s1647 ){
wstring buf( s1647, L'\0' );
wcin.read( &buf[0], s1647 );
size_t s717 = wcin.gcount();
buf.resize( s717 );
s156 = (tdbyte_t*)U8( buf ).data();}
void s1574::s1654( const s1489& src ){
throw new s16( L"cannot output to StdIn" );}
void s1574::s1634( s1489& s156, const s1489& s73 ){
wstring buf;
std::getline( wcin, buf );
s156 = (tdbyte_t*)U8( buf ).data();}
void s1574::s1653( const s1489& src ){
throw new s16( L"cannot output to StdIn" );}
wstring s1574::to_wstring( uint32_t s1740 ) const{
throw new s16( L"22: not implemented" );}
void s1574::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"StdIn object" << endl;}
size_t s1574::s330() const{
throw new s16( L"15: not implemented" );}
bool s1574::operator==( const s501* p ) const{
throw new s16( L"16: not implemented" );}
bool s1574::operator<( const s501* p ) const{
throw new s16( L"17: not implemented" );}
s1576::s1576( s268* s306, s278* ns_, const s269* ast_ )
: s1578( s306, ns_, ast_ ){
s1650 = &std::wcout;}
s501* s1576::s370( s278* s612, const std::vector<s277*>&, const s269* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1576::s364(){
s306->TR().s1301( s512, s7::s1586, s1687::s1684 );}
void s1576::s519( const s278* s961 ){
s1413();}
s501* s1576::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return NULL;}
s277* s1576::s349() const{
throw new s16( L"StdOut object cannot be copied" );}
void s1576::s371( s277* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1576::s1636( std::wstring& s156, size_t s1647 ){
throw new s16( L"cannot get input from StdOut" );}
void s1576::s1655( const std::wstring& src ){
wcout << src;}
void s1576::s1637( std::wstring& s156, const std::wstring& s73 ){
throw new s16( L"cannot get input from StdOut" );}
void s1576::s1656( const std::wstring& src ){
wcout << src << endl;}
void s1576::s1635( s1489& s156, size_t s1647 ){
throw new s16( L"cannot get input from StdOut" );}
void s1576::s1654( const s1489& src ){
wcout << U16( (const char*)src.data() );}
void s1576::s1634( s1489& s156, const s1489& s73 ){
throw new s16( L"cannot get input from StdOut" );}
void s1576::s1653( const s1489& src ){
wcout << U16( (const char*)src.data() ) << endl;}
wstring s1576::to_wstring( uint32_t s1740 ) const{
throw new s16( L"21: not implemented" );}
void s1576::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"StdOut object" << endl;}
size_t s1576::s330() const{
throw new s16( L"18: not implemented" );}
bool s1576::operator==( const s501* p ) const{
throw new s16( L"19: not implemented" );}
bool s1576::operator<( const s501* p ) const{
throw new s16( L"20: not implemented" );}
s629::s629( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s238, s736 ){
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( l[n]->s513() != s492 )
break;
s386* s77 = (s386*)l[n];
s501* s646 = (s501*)l[n + 1];
s655.s564( s77->s643(), s646 );
s280.push_back( s646->s349() );
s606.push_back( s646 );
s657.push_back( s646 );
s658.push_back( s77->s643() );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
void
s629::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
if( !s512 )
s512 = s1286;
return;
s702 = proc ? s612->s304() : s1849->s304();
if( s612->s513() == s497 || s612->s513() == s496 ) {
if( s612->s513() == s496 )
return;}
if( s280.size() > s657.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s280.size(); ++n ) {
s503 par = s280[n];
if( par->s513() == s492 ) {
if( par.s15<s386*>()->s396().s13() )
par.s15<s386*>()->s519( this );}
else
s917( par, n, s280[n], s1849 );}
for( size_t n = 0; n < s280.size(); ++n ) {
s655.s564( s658[n], s280[n].s15<s501*>(), s500::s150 );
s280[n]->s1856( s7::s941 );
s657[n] = s280[n];}
for( size_t n = 0; n < s608.size(); ++n ) {
if( s608[n]->s513() == s495 ) {
s508 cs = new s584( *s608[n].s15<s584*>() );
s608[n] = s624( cs, s306, s612, this, s612->s304() );}
else if( s608[n]->s513() == s492 )
s608[n].s15<s386*>()->s519( s611 );
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
return s717;}
s311::s311( s268* s306, s278* s616, Transd* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s260, s736 ){
if( l.size() < 2 )
throw new s16( s260 + L"(): wrong numbers of arguments" );
s280.push_back( l[0] );
s657.resize( 1 );
s658.push_back( L"@cond" );
s608.insert( s608.end(), l.begin() + 1, l.end() );}
void
s311::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
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
: s615( s306, s616, s617, s588, s259, s736 ),
s318( s7::s477, s306 ), s319( s306, 0 ){
if( l.size() < 1 )
throw new s16( s259 + L"(): wrong numbers of arguments" );
s655.s564( s318.s643(), &s319 );
s606.push_back( (s501*)&s319 );
s657.push_back( (s501*)&s319 );
s658.push_back( s318.s643() );
s315 = l[0];
s386* w = (s386*) l[1];
if( w->s643() != L"with" )
throw new s16( L"unknown syntax of 'through' statement" );
s316 = (s386*) l[2];
s655.s564( s316->s643(), s317.s15<s501*>() );
s606.push_back( (s501*)&s319 ); //..
s657.push_back( (s501*)&s319 );
s658.push_back( s316->s643() );
s608.assign( l.begin()+3, l.end() );}
void
s314::s519( const s278* s1849, bool proc ){
s489 pc = s315->s513();
if( pc == s495 ) {
s315 = s624( s315.s15<s584*>(), s306, s612, this, s304() );
s315.s15<Transd*>()->s519( s1849, proc );}
else if( pc == s492 )
s315.s15<s386*>()->s519( this );
else
throw new s16( L"unknown container type" );
s657[1] = s306->TR().s541( ( (s336*)s315->s515() )->s327(), s612, s612->s304() );
s657[1]->s1856( s7::s941 );
s615::s519( s1849, proc );}
s504 s314::s516( s501** s723, size_t s732 ){
s504 s717;
s489 pc = s315->s513();
s1::s9<s336> s612;
if( pc == s493 ) {
s612 = s315->s516(0,0).s15<s336*>();}
else
s612 = ((s336*)s315.s15<s386*>()->s392());
Iterator* s1124 = s612->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
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
: s615( s306, s616, s617, s588, s265, s736 ),
s318( s7::s477, s306 ), s319( s306, 0 ){
TDException s1060( s7::s1845, s1019, s736, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s1060.s1098( L"too few arguments" );
s655.s564( s318.s643(), &s319 );
s606.push_back( (s501*)&s319 );
s657.push_back( (s501*)&s319 );
s658.push_back( s318.s643() );
s277* p = l[0];
if( p->s513() != s492 )
throw s1060.s1098( L"the variable must be a name" );
s748 = (s386*) l[0];
varval = s380.s15<s501*>();
s386* in = (s386*) l[1];
if( in->s643() != L"in" )
throw s1060.s1098( L"the 'in' keyword is missing" );
s315 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s513() != s492 )
throw s1060.s1098( actmsg );
if( ((s386*)p)->s643() == L"where" ) {
where = l[4];
idx = 5;}
if( l.size() < ( idx + 2 ) )
throw new s16( actmsg );
p = l[idx];
if( p->s513() != s492 )
throw new s16( actmsg );
if( ((s386*)p)->s643() == L"select" ) {
if( l.size()  )
select = l[idx+1];}
else {
if( ((s386*)p)->s643() != L"do" )
throw new s16( actmsg );
s608.assign( l.begin() + (idx + 1), l.end() );}
s655.s564( s748->s643(), NULL );
s606.push_back( varval );
s657.push_back( varval );
s658.push_back( s748->s643() );}
void
s640::s519( const s278* s1849, bool proc ){
TDException s1060( s7::s1549, s1019, s627(), L"malformed syntax of 'for' statement" );
s489 pc = s315->s513();
if( pc == s495 ) {
s503 s616 = s624( s315.s15<s584*>(), s306, s612, this, s304() );
s315 = s616;
s315.s15<Transd*>()->s519( s1849, false );}
else if( pc == s492 ) {
s315.s15<s386*>()->s519( this );}
else if( pc == s491 )
s315->s519( this );
else
throw s1060.s1098( L"unknown iterable type" );
s502* s1651 = s315->s515();
s1171 vt = ( (s336*)s1651 )->ValType();
varval = s306->TR().s541(vt, s612, s612->s304() );
varval->s1856( s7::s941 );
s748->s397( varval );
s657[1] = varval.s15<s502*>();
s655.s564( s748->s643(), varval.s15<s502*>(), s500::s150 );
if( where ) {
pc = where->s513();
if( pc == s495 ) {
where = s624( where.s15<s584*>(), s306, s612, this, s304() );
where.s15<Transd*>()->s519( s1849, false );}
else
throw s1060.s1098( L"WHERE clause must be a function." );}
if( select ) {
pc = select->s513();
if( pc == s495 ) {
select = s624( select.s15<s584*>(), s306, s612, this, s304() );
select.s15<Transd*>()->s519( s1849, false );}
else
throw s1060.s1098( L"DO clause must be a function." );}
s615::s519( s1849, proc );}
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
Iterator* s1124 = s612->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
if( p.s13() )
break;
s657[0] = s1124->Idx();
s657[1] = p.s15<s502*>();
if( where ) {
if( ((bool)*(s501*)where->s516( 0, 0 )) != true )
continue;}
if( select ) {
select->s516( 0, 0 );}
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
: s615( s306, s612, s611, ct, l, s736 ){
s599 = s596;}
void s628::s677( s1171 s646, s615* pOvr ){
types.push_back( s646 );
s678.push_back( pOvr );}
s504 s628::s516( s501** s723, size_t s732 ){
return s615::s516( s723, s732 );}
s906::s906( s268* s306 )
: s615( s306, NULL, NULL, s588, s257, NULL ){
s511 = s1395;}
s906::s906( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s257, s736 ){
s284 = s257;
s511 = s1395;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( (s501*)l[n] ) == s950 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s512 = l[n + 1]->s366();
n += 2;
break;}
if( l[n]->s513() != s492 )
break;
s386* s77 = (s386*) l[n];
lang::s685( s77->s643() );
s501* s646 = (s501*) l[n + 1];
s655.s564( s77->s643(), s646 );
s280.push_back( s646 );
s606.push_back( s646 );
s657.push_back( s646 );
s658.push_back( s77->s643() );}
s608.insert( s608.end(), l.begin() + n, l.end() );}
void
s906::s519( const s278* s1849, bool proc ){
s615::s519( s1849, false );
if( s610.s13() )
s610 = s380.s15<s501*>();
s868::Cont v;
v.push_back( s1264->s366() );
v.push_back( (s1171)s606.size() + 1 );
v.push_back( s610->s366() );
v.push_back( 0 );
for( size_t n = 0; n < s606.size(); ++n ) {
v.push_back( s606[n]->s366() ); 
v.push_back( 0 );}
s512 = s306->TR().s1154( v );}
s504 s906::s516( s501** s723, size_t s732 ){
s504 s717;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1076[n+shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1076[n + shift];}
else if( pc == s491 )
*( s603 + n + shift ) = ( s501* )*( s604 + n );}}
if( s607.size() )
s657.assign( s607.begin() + 1, s607.end() );
for( size_t n = 0; n < s608.size(); ++n ) {
s717 = s608[n]->s516( s603, s517 );
if( s717->s644() < 0 )
break;}
return s717;}
s501* s906::s370( s278* s612, const std::vector<s1171>& vt ) const{
return new s906( *this );}
s277* s906::s349()const{
return new s906( *this );}
void s906::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"Lambda : " <<  s284 << endl;
s615::s310( pd, s201 );}
s631::s631( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s248, s736 ){
s280.assign( l.begin(), l.end() );
s512 = s1275;}
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
s512 = s1275;}
s504 s632::s516( s501**, size_t ){
*s610.s15<s375*>()->s372() = 1;
for( size_t n = 0; n < s280.size(); ++n ) {
if( !( bool )*( (s502*)( s280[n]->s516( 0, 0 ) ) ) ) {
*s610.s15<s375*>()->s372() = 0;
return s610;}}
return s610;}
s1579::s1579( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1603, s736 ),s1677( s7::s1545, s306 ),
s318( s7::s477, s306 ), s319( s306, 0 ){
TDException s1060( s7::s1846, s1019, s736, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s1060.s1098( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s655.s564( s318.s643(), &s319 );
s655.s564( s1677.s643(), NULL );
s657.push_back( (s501*)&s319 );
s657.push_back( NULL );
s658.push_back( s318.s643() );
s658.push_back( s1677.s643() );
s315 = l[0];
if( l.size() > 1 )
lambda = l[1];
s512 = s1275;}
void
s1579::s519( const s278* s1849, bool proc ){
TDException s1060( s7::s1547, s1019, s627(), L"malformed syntax of 'any()' function call" );
s489 pc = s315->s513();
if( pc == s495 ) {
s503 s616 = s624( s315.s15<s584*>(), s306, s612, this, s304() );
s315 = s616;
s315.s15<Transd*>()->s519( s1849, false );}
else if( pc == s492 ) {
s315.s15<s386*>()->s519( this );}
else if( pc == s491 )
s315->s519( this );
else
throw s1060.s1098( L"unknown iterable type" );
varval = s306->TR().s541( ( (s336*)s315->s515() )->ValType(), s612, s612->s304() );
varval->s1413();
s1677.s397( varval );
s657[1] = varval.s15<s502*>();
if( lambda.s14() ) {
if( lambda->s513() == s492 ) {
lambda.s15<s386*>()->s519( s611 );}
else {
lambda = s277::s1121( s306, lambda, this, this, s611->s304() );}}
s615::s519( s1849, false );}
s504 s1579::s516( s501**, size_t  ){
TDException s1060( s7::s1548, s1550, past );
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
Iterator* s1124 = s612->s321( NULL );
while( 1 ) {
s503 p = s1124->s322();
if( p.s13() )
break;
s657[0] = s1124->Idx();
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
vector<wstring> s1048( { L"else", L"elsif" } );
s633::s633( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s235, s736 ){
wstring s746 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s746 + L"too few arguments." );
s280.assign( l.begin(), l.end() );
s615::s1392( ( vector<s277*>& )l, s1048 );}
void s633::s776( bool proc ){
wstring s746 = L"malformed syntax of 'if' statement: ";
s647.push_back( s280[0] );
s648.push_back( s602() );
s648.back().push_back( s280[1] );
if( s280.size() > 2 ) {
size_t n = 2;
while( n < s280.size() ) {
s503 p = s280[n];
s489 pc = s280[n]->s513();
if( pc == s1173 ) {
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
size_t s960 = s648[0].size();
s1171 prevPt = s607[s960]->s366();
for( size_t n = 1; n < s648.size(); ++n ) {
s960 += s648[n].size() + 1;
s1171 tmpPt = s607[s960]->s366();
if( tmpPt && tmpPt != s828->s366() && ( tmpPt != prevPt ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s512 = prevPt;
if( !s512 ) // e.g. break, continue
s512 = s780->s366();}
else
s512 = s780->s366();}
void
s633::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
s776( proc );
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
vector<wstring> s1046( { L"to:", L":sign", L":nosign", L":width", L":group", L":nl" } );
s634::s634( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s256, s736 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s736->Src().find( L"lout" );
if( pl1 < s736->Src().find( L"textout" ) )
lout = true;
vector<s277*>tmp( l );
s615::s1392( tmp, s1046 );
s280.assign( tmp.begin(), tmp.end() );
s512 = s780->s366();}
s634::s634( s268* s306 )
: s615( s306, NULL, NULL, s588, s256, NULL ), s42( NULL ),
lout( false ){
s512 = s780->s366();}
void s634::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
if( s280[0]->s513() == s1173 ) {
if( s280[0].s15<s386*>()->Id() == s1380 ) {
s42 = s280[1];
s280.erase( s280.begin(), s280.begin() + 2 );
s607.erase( s607.begin()+1, s607.begin() + 3 );
nlocs = s280.size();
s517 = s607.size();}}
for( size_t n = 0; n < s280.size(); ++n ) {
if( s280[n]->s513() == s1173 ) {
int mark = (int)*( s280[n].s15<s386*>() )->s392();
if( mark != s1746 && s280.size() <= n )
throw new s16( L"incorrect usage of formatting marker: " + (s280[n].s15<s386*>())->s643() );
if( mark == s1747 && s280[n+1]->s366() != s1284 )
throw new s16( L"'" + (s280[n].s15<s386*>())->s643() + L"' formatting marker must have an argument" );}}
s1413();}
s504 s634::s516( s501** s723, size_t s732 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s604 + n ) ) {
s489 pc = ( ( s502* )*( s604 + n ) )->s513();
if( pc == s492 || pc == s1505 )
*( s603 + n + shift ) =
(s501*)( ( s386* )*( s604 + n ) )->s392();
else if( pc == s493 ) {
s1076[n + shift] = (s501*)( ( s615* )*( s604 + n ) )->s516( s723, s732 );
*( s603 + n + shift ) = s1076[n + shift];}}}
s1::s9<Stream> s827;
if( s42.s14() ) {
s489 pc = s42->s513();
if( pc == s493 )
s827 = s42->s516( 0, 0 ).s15<Stream*>();
else if( pc == s492 )
s827 = (Stream*)s42.s15<s386*>()->s392();
else
s827 = s42.s15<Stream*>();}
else
s827 = s1577.s15<Stream*>();
s827->s1742();
uint32_t flags = 0;
for( size_t n = 1; n < s607.size(); ++n ) {
if( s607[n]->s513() == s1173 ) {
int mark = (int)*( (s386*)s607[n] )->s392();
if( mark == s1644 ) {
flags |= s1735;}
if( mark == s1767 ) {
flags &= ~s1735;}
else if( mark == s1747 ) {
int w = (int)*s607[++n];
s827->s1744( w );}
else if( mark == s1745 ) {
flags |= s1734;}
else if( mark == s1746 ) {
s827->s1656( L"" );
n++;}}
else {
s504 s156 = s607[n]->s516( s723, s517 );
s827->s1655( s156->to_wstring( flags ) );}}
if( lout )
s827->s1656( L"" );
return s380;}
s277* s634::s349()const{
return new s634( *this );}
s907::s907( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s924, s736 ){
if( l.size() > 1 )
throw new s16( s924 + L": too many arguments" );
s608.assign( l.begin(), l.end() );}
void
s907::s519( const s278* s1849, bool proc ){
if( s608.size() ) {
s615::s519( s1849, false );
s610 = s608[0]->s515();}
else {
s610 = s380.s15<s501*>();
s512 = s1286;}}
s504 s907::s516( s501** s740, size_t s517 ){
s501* s717;
if( s608.size() )
s717 = s615::s516( s740, s517 );
else
s717 = new s379( s306 );
s717->s1856( s7::s940 );
return s717;}
s277* s907::s349()const{
return new s907( *this );}
s983::s983( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s987, s736 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s987 + L": wrong number of arguments" );
if( l.empty() )
s280.push_back( new s360( s306, 0 ) );
else
s280.assign( l.begin(), l.end() );
s512 = s1284;}
void
s983::s519( const s278* s1849, bool proc ){
s615::s519( s1849, false );
if( s280[0]->s366() != s1284 )
throw new s16( L"The parameter to (exit ) must have Integer type." );}
s504 s983::s516( s501** s740, size_t s517 ){
s615::s516( s740, s517 );
code = (int)*s607[1];
throw new s16( (uint32_t) code );}
s277* s983::s349()const{
return new s983( *this );}
s636::s636( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s264, s736 ), s79( s306 ){
if( l.size() != 1 )
throw new s16( s264 + L": wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s828->s366();
s79.s11();}
s636::s636( s268* s306 )
: s615( s306, NULL, NULL, s588, s264, NULL ), s79( s306 ){
s512 = s828->s366();
s79.s11();}
void
s636::s519( const s278* s1849, bool proc ){
s79.s378( s280[0]->to_wstring() );
s610 = s381.s15<s501*>();
s607.push_back( s280[0]->s515() );}
s504 s636::s516( s501** s740, size_t s517 ){
s79.s378( s280[0]->s516( s740, s517 )->to_wstring() );
return &s79;}
s637::s637( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s262, s736 ), s77( s7::s476, s306 ), s646( s306 ){
if( l.size() < 2 )
throw new s16( s262 + L"(): wrong numbers of arguments" );
s655.s564( s77.s643(), &s646 );
s606.push_back( (s501*)&s646 );
s657.push_back( (s501*)&s646 );
s658.push_back( s77.s643() );
s608.assign( l.begin(), l.end() );
if( ((s584*)l.back())->s305() != s263 )
throw new s16( L"the catch clause must be the last statement in the try block" );}
s637::s637( s268* s306 )
: s615( s306, NULL, NULL, s588, s262, NULL ), s77( s7::s476, s306 ), s646( s306 ){}
void
s637::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );
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
s512 = s780->s366();}
s638::s638( s268* s306 )
: s615( s306, NULL, NULL, s588, s263, NULL ){
s512 = s780->s366();}
s504 s638::s516( s501** s723, size_t s732 ){
s501* s156;
for( size_t n = 0; n < s608.size(); ++n ) {
s156 = s608[n]->s516( s723, s732 );
if( s156->s644() < 0 ) {
return s156;}}
return s380.s15<s501*>();}
s799::s799( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s795, s736 ){}
void
s799::s519( const s278* s1849, bool proc ){}
s504 s799::s516( s501** s740, size_t s517 ){
return 0;}
s1857::s1857( s268* s306, s278* s616, s615* s617, s1858 ptr_,
const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, L"", s736 ), s1859( ptr_ ){
subject = l[0];
s280.assign( l.begin() + 1, l.end() );}
void
s1857::s519( const s278* s1849, bool proc ){
s615::s519( s1849, proc );}
s504 s1857::s516( s501** s740, size_t s517 ){
s505	s1831 = subject->s516( 0, 0 ).s15<s278*>();
return ( *s1831.*s1859)( &s607[0], s517 );
return 0;}
s1786::s1786( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1796, s736 ){
s280.assign( l.begin(), l.end() );}
s1786::s1786( const s1786& right )
: s615( right ), cmd( right.cmd ){}
void
s1786::s519( const s278* s1849, bool proc ){
s512 = s1286;
s615::s519( s1849, proc );}
void s1789( const wstring& cmd, wstring* s1823, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1823 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1823 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s504 s1786::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
wstring cmd_ = s607[1]->to_wstring(), s1824;
bool* pdone = ( (s375*)s607[2] )->s372();
wstring *s1823 = NULL;
if( s607.size() > 3 )
s1823 = ( (s374*)s607[3] )->s372();
else
s1823 = &s1824;
if( s880.joinable() )
s880.join();
s880 = thread( s1789, cmd_, s1823, pdone );
return s610;}
s1784::s1784( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1794, s736 ){
if( l.size() != 2 )
throw new s16( s1794 + L"(): wrong numbers of arguments" );
if( l[0]->s513() != s492 )
throw new s16( s1794 + L"(): the first argument must be a reference" );
s280.assign( l.begin(), l.end() );}
s1784::s1784( const s1784& right )
: s615( right ){}
void
s1784::s519( const s278* s1849, bool proc ){
s512 = s1286;
s615::s519( s1849, proc );}
s504 s1784::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
s386* dr = s280[0].s15<s386*>();
s278* mod = dr->s396().s15<s278*>();
mod->s1834( dr->s643(), s607[2] );
return s610;}
s1781::s1781( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1792, s736 ){
if( l.size() != 2 )
throw new s16( s1792 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1781::s1781( const s1781& right )
: s615( right ){}
void
s1781::s519( const s278* s1849, bool proc ){
s512 = s1286;
s615::s519( s1849, proc );}
s504 s1781::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
s278* dr = (s278*)s607[1];
s1779* ob = (s1779*)s607[2];
try {
dr->s1817( ob );}
catch( s16* e ) {
wstring s79 = L"in function " + s305() + L":\n";
s79 += L"during loading object: " + dr->s1850() +
L":" + dr->s368() + L":";
e->s30( s79 );
throw e;}
return s610;}
s1785::s1785( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1795, s736 ){
if( l.size() != 1 )
throw new s16( s1795 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1785::s1785( const s1785& right )
: s615( right ){}
void
s1785::s519( const s278* s1849, bool proc ){
s512 = s1286;
s615::s519( s1849, proc );}
s504 s1785::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
int dr = (int)*(s360*)s607[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s610;}
s1780::s1780( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s1791, s736 ){
if( l.size() != 1 )
throw new s16( s1791 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );}
s1780::s1780( const s1780& right )
: s615( right ){}
void
s1780::s519( const s278* s1849, bool proc ){
s512 = s1288;
s615::s519( s1849, proc );}
s504 s1780::s516( s501** s723, size_t s732 ){
s1788( s723, s732 );
s501* dr = s607[1];
wstringstream buf;
dr->s310( &buf );
*s610.s15<s374*>()->s372() = buf.str();
return s610;}
s277* s633::s349() const{
return new s633( *this );}
s277* s631::s349() const{
return new s631( *this );}
s277* s632::s349()const{
return new s632( *this );}
s277* s1579::s349()const{
return new s1579( *this );}
s277* s636::s349()const{
return new s636( *this );}
s277* s637::s349() const{
return new s637( *this );}
s277* s638::s349() const{
return new s638( *this );}
s277* s799::s349() const{
return new s799( *this );}
s277* s1857::s349() const{
return new s1857( *this );}
s277* s1786::s349() const{
return new s1786( *this );}
s277* s1784::s349() const{
return new s1784( *this );}
s277* s1781::s349() const{
return new s1781( *this );}
s277* s1785::s349() const{
return new s1785( *this );}
s277* s1780::s349() const{
return new s1780( *this );}
s635::s635( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s261, s736 ){
if( l.size() != 1 )
throw new s16( s261 + L"(): wrong numbers of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s1275;}
s635::s635( s268* s306 )
: s615( s306, NULL, NULL, s588, s261, NULL ){
s512 = s1275;}
void s635::s519( const s278* s616, bool proc ){
s615::s519( s616, proc );}
s504 s635::s516( s501** s740, size_t s517 ){
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
vector<s503> s999;
s1035 ast_ = new s269( f, s627()->Nqj() );
s508 cs = s615::s1236( *ast_, s306, s612, s304() );
s999.push_back( cs );
s506 s997 = s615::s624( cs, s306, s612, this, s304() );
s997->s519( s612, true );
s997->s516( 0, 0 );}
else {
vector<wstring> l;
s306->callFunc( f, l );}}
catch( s16* e ) {
(void)e;
return s385;}
return s384;}
s277* s635::s349() const{
return new s635( *this );}
s268* s641::s993 = NULL;
s641::s641( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s267, s736 ){
if( l.size() != 1 )
throw new s16( s267 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s780->s366();}
s641::s641( s268* s306 )
: s615( s306, NULL, NULL, s588, s267, NULL ){
s512 = s780->s366();}
s504 s641::s516( s501** s740, size_t s517 ){
vector<wstring> s998;
for( size_t n = 0; n < s280.size(); ++n ) {
s998.push_back( s280[n]->s516( 0, 0 )->to_wstring() );}
if( !s993 ) {
s993 = new s268();
s993->s519( true );}
else
s993->reset();
s993->s213( s998[0] );
s993->run( s998 );
return s380;}
s277* s641::s349()const{
return new s641( *this );}
s848::s848( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 )
: s615( s306, s616, s617, s588, s818, s736 ){
if( l.size() != 1 )
throw new s16( s818 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s780->s366();}
s504 s848::s516( s501** s740, size_t s517 ){
s504 s198 = s280[0]->s516( s740, s517 );
s306->s213( s198->to_wstring() );
return s380;}
s277* s848::s349()const{
return new s848( *this );}
s823::s823( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s878, s736 ){
s991 = s616->s304();
if( l.size() != 1 )
throw new s16( s878 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s780->s366();}
s504 s823::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s989;
if( par->s513() == s492 )
s989 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s989 = par->s516( 0, 0 )->to_wstring();
try {
s278* ob = ((s278*)s306->s670( s991, s991 ));
ob->s578( s989, s991 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s823::s349()const{
return new s823( *this );}
s1474::s1474( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s1484, s736 ){
if( l.size() != 1 )
throw new s16( s1484 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s780->s366();}
s504 s1474::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s702;
if( par->s513() == s492 )
s702 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s702 = par->s516( 0, 0 )->to_wstring();
try {
s306->s1520( s702 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s1474::s349()const{
return new s1474( *this );}
s1787::s1787( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 )
: s615( s306, s616, s617, s588, s1797, s736 ){
if( l.size() != 1 )
throw new s16( s1797 + L"(): wrong number of arguments" );
s280.assign( l.begin(), l.end() );
s512 = s780->s366();}
s504 s1787::s516( s501** s740, size_t s517 ){
s277* par = s280[0];
wstring s702;
if( par->s513() == s492 )
s702 = ((s386*)par)->s516( 0, 0 )->to_wstring();
else
s702 = par->s516( 0, 0 )->to_wstring();
try {
s306->s1842( s702 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s380;}
s277* s1787::s349()const{
return new s1787( *this );}
s825::s825( s268* pass_, s278* s612, const wstring& s814, const vector<wstring>& s784,
std::vector<s503>& types ){
s793 s830( pass_, s612, s814 );
s830.s519( s612 );
vector<s503> s877 = s830.s328();
if( s877.size() != types.size() )
throw new s16( L"The number of record's fields doesn't match to the number of columns: " + s814 );
for( size_t n = 0; n < s877.size(); ++n ) {
if( !s877[n]->s521( types[n].s15< s501*>() ) )
throw new s16( L"The types of record's fields don't match to the types of columns: " + s814 );
s808.insert( make_pair( s784[n], s877[n] ) );
size_t h = s877[n].s15<s501*>()->s330();
rechash = ( rechash << 1 ) ^ h;}}
size_t s825::s330() const{
return rechash;}
s504 s825::s805( const std::wstring& s77, bool s750 ) const{
auto it = s808.find( s77 );
if( it == s808.end() ) {
if( s750 )
throw new s16( L"Record field doesn't exist: " + s77, 
(uint32_t)s16::s17::s23 );
else
return s504();}
return it->second.s15<s501*>();}
void s825::s937( s793& s156 ) const{
for( auto r: s808 )
s156.add( r.second );}
void s825::s568( std::vector<std::wstring>& s156 ) const{
for( auto r: s808 )
s156.push_back( r.first );}
bool s825::operator==( const s825* p ) const{
return rechash == p->rechash;}
bool s825::operator<( const s825* p ) const{
return rechash < p->rechash;}
wstring s825::to_wstring( uint32_t s1740 ) const{
wstringstream ss;
s310( &ss, 0 );
return ss.str();}
void s825::s310( std::wostream* pd, int s201/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"TSDRecord : " << endl;
for( auto it = begin( s808 ); it != end( s808 ); ++it ) {
buf << s4::fill_n_ch( L' ', s201 + s434 ) << it->first << L":" << endl;
it->second->s310( pd, s201 + s434 );}}
s867::s867( vector<wstring>& s772, s879 rec ){
for( size_t n = 0; n < s772.size(); ++n ) {
s503 f = rec->s805( s772[n] ).s15<s502*>();
s863.push_back( f );}
for( size_t n = 0; n < s772.size(); ++n ) {
size_t h = s863[n].s15<s501*>()->s330();
s851 = ( s851 << 1 ) ^ h;}}
size_t s867::s330() const{
return s851;}
bool s867::operator==( const s867* p ) const{
return s851 == p->s851;}
bool s867::operator<( const s867* p ) const{
return s851 < p->s851;}
void s867::s310( std::wostream* pd, int s201/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s863.size(); ++n ) {
s863[n]->s310( pd, s201 + s434 );}}
s679::s679( s268* s306, s278* s612, const wstring& s78, const s269* ast_ )
: s350( s306, s612, ast_ ){
s518 = s78;
s512 = s807.s13() ? 0 : s807->s366();}
s679::s679( const s679& right, const s269* ast_ )
: s350( right.s306, right.ns, ast_ ){
s512 = right.s512;}
s501* s679::s369( const s269& s736, s278* s612, const std::wstring& s346 ){
return new s679( s306, s612, L"" );}
void s679::s519( const s278* s961 ){
s1413();}
void s679::s364(){
s362.insert( make_pair( L"new", new s351( L"new", &s679::s1384, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"add-file", new s351( L"add-file", &s679::s836, s1286,
{ s1239( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"load-table", new s351( L"load-table", &s679::s853, s1286,
{ s1239( { s1288, s1288 } ) }, 1, 2 ) ) );
s362.insert( make_pair( L"select", new s351( L"select", &s679::s796, s1286,
{ s1239( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"query", new s351( L"query", &s679::s816, s1286,
{ s1239( { s1288 } ) }, 1, 1 ) ) );
s362.insert( make_pair( L"erase", new s351( L"erase", &s679::s344, s1286,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"size", new s351( L"size", &s679::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( make_pair( L"build-index", new s351( L"build-index", &s679::s928, s1286,
{ s1239( { s1288 } ) }, 1, 1 ) ) );}
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
s717->s519( ps->ns );
*s280 = (s501*)s717;}
inline void s679::s836( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s683( s198 );}
inline void s679::s853( s501** s280, size_t s517 ){
s679* dr = ( (s679*)DR );
const wstring& s881 = PARN( 2 )->to_wstring();
wstring s857;
if( s517 == 4 )
s857 = PARN( 3 )->to_wstring();
dr->s754( s881, s857 );}
inline void s679::s796( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s684( s198 );}
inline void s679::s816( s501** s280, size_t s517 ){
wstring s198 = PARN( 2 )->to_wstring();
( (s679*)DR )->s684( s198 );}
inline void s679::s344( s501** s280, size_t s517 ){}
inline void s679::s339( s501** s280, size_t s517 ){}
inline void s679::s342( s501** s280, size_t s517 ){}
inline void s679::s928( s501** s280, size_t s517 ){
wstring s930 = PARN( 2 )->to_wstring();
((s679*)DR)->s927( s930 );}
void s679::s683( const wstring& s198 ){
vector<s9<s146>> s692;
s1033 s1159( s198 );
s1159.read( s692, s7::s1223 );
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
void s679::select( std::wstring& s930, s504 s684, 
s335::mapped_type::iterator& s948, s335::mapped_type::iterator& s949 ){
auto it = s945.find( s930 );
if( it == s945.end() )
throw new s16( L"Index doesn't exist: " + s930 );
if( s684.s14() ) {
auto s156 = it->second[s930].equal_range( s684 );
s948 = s156.first;
s949 = s156.second;}
else {
s948 = it->second[s930].begin();
s949 = it->second[s930].end();}}
void s679::s754( const wstring& s881, const wstring& s766 ){
wstring s784 = s766;
vector<wstring> s871;
vector<wstring> s771;
vector<wstring> s856;
vector<wstring> s882;
if( s784.size() ) {
s4::s58( s784, L",", s871 );
s4::s58( s4::s53( s881, s49 ), L"\n", s856 );}
else {
s784 = s881.substr( 0, s881.find( L"\n" ) );
s4::s58( s4::s53( s881.substr( s784.size() ), s49 ), L"\n", s856 );
if( s784.back() == '\r' )
s784.pop_back();
s4::s58( s784, L",", s871 );}
for( size_t n = 0; n < s871.size(); ++n ) {
if( s871[n][0] != L'@' )
s771.push_back( s871[n] );
else {
size_t pl = s871[n].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s871[n] );
wstring s77 = s871[n].substr( pl + 1 );
s771.push_back( s77 );
s882.push_back( s77 );}}
if( !s882.empty() ) {
s793 s830( s306, ns, s856[0] );
s830.s519( ns );
vector<s503> types = s830.s328();
for( auto row : s856 ) {
s879 rec = new s825( s306, ns, row, s771, types );
s774 s155 = new s867( s882, rec );
s801.insert( make_pair( s155, rec ) );}}}
void s679::s927( const wstring& s930 ){
auto it = s945.find( s930 );
if( it != end( s945 ) )
s945.erase( it );
s335& s944 = s945.insert( make_pair( s930, s335() ) ).first->second;
for( auto it: s801 ) {
s504 pd = it.second->s805( s930 );
if( pd.s14() )
s944[s930].insert( make_pair( pd, it.second ) );}}
wstring s679::to_wstring( uint32_t s1740 ) const{
basic_stringstream<wchar_t> ss;
s310( &ss, 0 );
return ss.str();}
void s679::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s201 ) << L"TSDBase : " << endl;
for( auto it = begin( s801 ); it != end( s801 ); ++it ) {
it->first->s310( pd, s201 + s434 );
it->second->s310( pd, s201 + s434 );}}
struct s918{
size_t idx;
s918( size_t s943 ): idx( s943 ){}
bool operator()( const s504 l, const s504 r ) const{
s504 ld = l.s15<s793*>()[idx];
s504 rd = r.s15<s793*>()[idx];
return ld->operator<( (s501*)&(*rd) );}
};
vector<wstring> s1047( { L"select:", L"all", L"as:", L"where:", L":distinct",
L"sortby:", L":asc", L":desc", L"limit:" } );
s841::s841( s268* s306, s278* s616, s615* s617, const std::vector<s277*>& l_, const s269* s736 )
: s615( s306, s616, s617, s588, s874, s736 ),
s773( s7::s477, s306 ), s832( new s278( s306, 0, s498 ) ){
TDException s1060( s7::s1227, s1019, s736 );
if( l_.size() < 3 )
throw s1060.s1098( L"too few arguments." );
s615::s1392( ( vector<s277*>& )l_, s1047 );
s655.s564( s773.s643(), s832.s15<s501*>() );
s606.push_back( s832.s15<s501*>() );
s280.push_back( s832.s15<s501*>() );
s657.push_back( s832.s15<s501*>() );
s658.push_back( s773.s643() );
const size_t s1163 = 8;
std::vector<s277*> l( s1163 );
s503 p = l_[0];
if( p->s513() != s492 && p->s513() != s493 )
throw s1060.s1098( L"the database object must be specified by a name or expression." );
l[0] = l_[0];
size_t s1083 = 1;
for( size_t n = 1; n < l_.size() /*&& s1083 < s1163*/; ++n ) {
if( l_[n]->s513() == s1173 ) {
s386* rf = (s386*)l_[n];
if( rf->Id() == s1378 ) s1083 = 1;
else if( rf->Id() == s1362 ) s1083 = 2;
else if( rf->Id() == s1361 ) {
s1083 = s1271;
l[1] = l_[n];}
else if( rf->Id() == s1383 ) s1083 = 3;
else if( rf->Id() == s1367 ) {
s1083 = s1271;
s862.distinct = 1;}
else if( rf->Id() == s1379 ) {
s862.s973 = s785::s905::s888;
s1083 = 5;}
else if( rf->Id() == s1363 ) {
if( s1083 != 6 )
throw s1060.s1098( L"the '" + rf->s643() + L"' specifier is misplaced" );
s1083 = s1271;
s862.s973 = s785::s905::s888;}
else if( rf->Id() == s1366 ) {
if( s1083 != 6 )
throw s1060.s1098( L"the '" + rf->s643() + L"' specifier is misplaced" );
s1083 = s1271;
s862.s973 = s785::s905::s895;}
else if( rf->Id() == s1377 ) s1083 = 7;}
else
l[s1083++] = l_[n];}
db = l[0];
what = l[1];
s1182 = l[2];
where = l[3];
s975 = l[5];
s952 = l[7];
if( s1182.s13() )
throw s1060.s1098( L"the 'as' clause is missing" );}
void
s841::s519( const s278* s1849, bool proc ){
s1182->s519( this );
s868::Cont s1433;
wstring sv = s1182->s368();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n-1] == L'<' )
sv.erase( n--, 1 );
wstring ts = s764->s368() + L"<" + sv + L">";
s512 = s764->s1338( ts, s1433 );
TDException s1060( s7::s1007, s1019, past );
s615::s519( s1849, proc );
s489 pc = db->s513();
if( pc == s495 ) {
db = s624( db.s15<s584*>(), s306, s612, this, s304() );
db->s519( this );}
else if( pc == s492 )
db.s15<s386*>()->s519( this );
else
throw s1060.s1098( L"the database must be specified by a name or expression." );
pc = what->s513();
if( pc == s495 ) {
what = s624( what.s15<s584*>(), s306, s612, this, s304() );
what->s519( this );}
else if( pc == s492 )
what.s15<s386*>()->s519( this );
else if( pc == s491 || pc == s1173 )
(void)0;
else
throw s1060.s1098( L"the query field(s) must be specified by a name or expression." );
if( where ) {
pc = where->s513();
if( pc == s495 ) {
where = s624( where.s15<s584*>(), s306, s612, this, s304() );
where.s15<Transd*>()->s519( s1849, false );
s900 s964;
where.s15<Transd*>()->s869( s964 );}
else
throw s1060.s1098( L"the 'where' clause must be a lambda." );}
else {
std::vector<s277*> s962;
s962.push_back( s384 );
where = (s502*) new s906( s306, 0, 0, s962, NULL );
where.s15<Transd*>()->s519( s1849, false );}
if( s952.s14() ) {
pc = s952->s513();
if( pc == s495 ) {
s952 = s624( s952.s15<s584*>(), s306, s612, this, s304() );
s952->s519( this );}
else if( pc == s492 )
s952.s15<s386*>()->s519( this );
else if( s952->s366() != s1284 )
throw s1060.s1098( L"the limit must be specified by a number, variable or expression." );}}
s504 s841::s516( s501** s723, size_t s732 ){
s504 s717 = s610;
vector<wstring> s981;
vector<wstring> s982;
s679* base;
size_t s995 = string::npos;
TDException s1060( s7::s1008, s1016, past );
assert( db->s513() == s492 );
base = ((s679*)db.s15<s386*>()->s392());
if( s952.s14() ) {
if( s952->s513() == s492 ) {
s862.s952 = (int)*((s360*)s952.s15<s386*>()->s392());}
else if( s952->s513() == s493 ) {
s862.s952 = (int)*s952->s516( 0, 0 );}
else
s862.s952 = (int)*s952;}
if( s975.s14() ) {
if( s975->s513() == s492 ) {
s862.s972 = s975.s15<s386*>()->s392()->to_wstring();}
else if( s975->s513() == s493 ) {
s862.s972 = s975->s516( 0, 0 )->to_wstring();}
else
s862.s972 = s975->to_wstring();}
std::unordered_set<s879, s916, s915> dom;
s679::s335::mapped_type::iterator beg, end;
s489 pc = what->s513();
if( pc == s492 ) {
throw new s16( L"'select REF' : to be implemented." );}
else if( pc == s1173 ) {
s507 rf = what.s15<s386*>();
if( rf->s643() == L"all" || rf->s643() == L"ALL" )
(void)0;
else
throw s1060.s1098( L"fields for selection are not recognized" );}
else if( pc == s491 ) {
const s868& vt = s306->TR().s1113( what->s366() );
if( vt.s366() == s764->s366() ) {
const vector<s503>& v = what.s15<s323*>()->s328();
for( auto it: v ) {
wstring s930 = it->to_wstring();
size_t s965 = s4::s89.find( s930[0] );
if( s965 != string::npos )
s930 = s4::s53( s930, wstring( 1, s4::s89[s965] ) );
s981.push_back( s930 );
if( s982.empty() ) {
base->select( s981.back(), s504(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;}}}}}
s900 s964;
where.s15<Transd*>()->s869( s964 );
for( size_t n = 0; n < s964.size(); ++n ) {
s982.push_back( s964[n].first );
base->select( s982.back(), s504(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;}}
vector<s503> s963;
s963.resize( s982.size() );
s610.s15<s323*>()->clear();
for( auto r : dom ) {
for( size_t n = 0; n < s982.size(); ++n )
s963[n] = r->s805( s982[n] ).s15<s502*>();
where.s15<Transd*>()->s620( s963 );
s504 s156 = where->s516( 0, 0 );// ( (s501**)&s963[0], s963.size() );
if( s156.s14() && (bool)*s156 ) {
s1::s9<s793> s980 = new s793( s306, NULL, L"" );
if( s981.empty() )
r->s937( *s980 );
else {
for( size_t n = 0; n < s981.size(); ++n )
s980->add( r->s805( s981[n] ).s15<s502*>() );}
s980->s1856( s7::s941 );
s610.s15<s323*>()->add( s980 );}}
if( s862.distinct != -1 ) {
vector<s503>& s986 = s610.s15<s323*>()->s328();
for( size_t n = 0; n < s986.size(); ++n ) {
s503 s985 = s986[n];
size_t m = n + 1;
while( m < s986.size() ) {
s503 _el1 = s986[m];
if( *s985.s15<s793*>() == _el1.s15<s501*>() )
s986.erase( s986.begin() + m );
else
m++;}}}
if( s862.s973 != -1 ) {
if( s981.size() && s862.s972.size() ) {
auto it = std::find( s981.begin(), s981.end(), s862.s972 );
if( it != s981.end() )
s995 = std::distance( s981.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s990;
(*dom.begin())->s568( s990 );
auto it = std::find( s990.begin(), s990.end(), s862.s972 );
if( it != s990.end() )
s995 = std::distance( s990.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s984> s988 = new s984;
s988->s994( s995 );
s909 s996( s988 );
s610.s15<s323*>()->sort( s862.s973 == s785::s895, &s996 );}
if( s862.s952 != -1 ) {
s610.s15<s323*>()->s328().resize( s862.s952 );}
return s717;}
s277* s841::s349()const{
return new s841( *this );}
vector<wstring> s1543 /*= { L"", s1602, s248, s1603, 
s263, s261, 
s987, s265, s235, s818, 
s878, s257, s249, s924,
s267, s804, s256, s264, 
s262, s874, s1484, s260, 
s238 }*/;
vector<int> BIFuncs1v = {
0, 0, 0, s1606, s1607, 0, 0, s1609, s1610, 0, 0, 0,
s1613, s1800, 0, 0, s1616, 0, 0, 0, s1618, s1802, 0, 0, 0, s1621, s1622,
0, 0, s1624, s1625
};
std::map<std::wstring, int> s1542;
s268::s268()
: s278( this, 0, s490 ), s736( s232, L"", L"global" ),
s204( L"" ), s207( this ), s1486( false ){}
s268::~s268(){}
void s268::reset(){
s655.reset();
s207.s840();
s203.clear();
s736.reset();
s1486 = false;}
void s268::s519( bool soft /*=false*/ )
{
s350::s834( this, soft );
s207.s296();
s210[s7::s449] = s382.s15<s501*>();
s210[s7::s448] = s383.s15<s501*>();
s921( s7::s451, s384.s15<s501*>() );
s921( s7::s452, s385.s15<s501*>() );
s921( s7::s896, s380.s15<s501*>() );
s1577 = new s1576( this, this );
s1575 = new s1574( this, this );
s921( s7::s1563, s1575.s15<s501*>() );
s921( s7::s1564, s1577.s15<s501*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s374* s1648 = new s374( this, os );
s921( s7::s1544, s1648 );
if( s1542.empty() ) {
s1543 = { L"", s1602, s248, s1603,
s263, s1791, s261,
s987, s265, s235, s818,
s878, s257, s1792, s249,
s1793, s924,
s267, s1795, s1796, s804, s1794,
s256, 
s1737, 
s264,
s262, s874, s1797, 
s1484, s260, s238 };
for( size_t n = 1; n < s1543.size(); ++n )
s1542[s1543[n]] = (int)n;}}
void s695( const std::wstring& s686, s758& s156 ) {
vector<s9<s146>> s692;
s1036 s1159 = new s1033( s686 );
s1159->read( s692, s7::s433 );
for( size_t n = 0; n < s692.size(); n++ ) {
wstring s687 = s269::s308( *s692[n], s7::s480 );
if( s687 == s7::s468 ) {
if( ( *s692[n] ).s159( s7::s482 ) ) {
const vector<s145>& s165 = ( *s692[n] ).s161( s7::s482 )->s170();
for( size_t n = 0; n < s165.size(); n++ )
s156.s693.push_back( s165[n]->s172() );}
if( ( *s692[n] ).s159( s7::s481 ) )
s156.entry = ( *s692[n] ).s161( s7::s481 )->s929();}}
if( s156.s693.empty() )
s156.s693.push_back( s686 );}
wstring s753( const wstring& s797, const wstring& s800 ){
if( s3::s760( s800 ) )
return s800;
if( !s3::s760( s797 ) )
throw new s16( L"The root path is not absolute: " + s797 );
if( s800.empty() )
return s797;
wstring path = s800;
wstring root = s797;
s4::s62( path );
s4::s62( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s16( L"The relative path '" + s800 + L"' is incompatible with the root '" + s797 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s16( L"The relative path '" + s800 + L"' is incompatible with the root '" + s797 + L"'." );}
return root + path;}
void s268::s217( const std::wstring& s198, const s146& obj ){
const vector<s145>& s768 = ( obj ).s161( s7::s487 )->s170();
const vector<s145>& packs = ( obj ).s161( s7::s779 )->s170();
vector<wstring> s41;
wstring s782 = s198.substr( 0, s198.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s768.size(); n++ )
s41.push_back( s753( s782, s768[n]->s172() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s172();
if( req.rfind( s7::s472 ) == req.size() - s7::s472.size() ) {
if( std::find( s203.begin(), s203.end(), req ) == s203.end() )
s203.push_back( s753( s782, req ) );}
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
wstring s778;
s4::s295( matches, L",\n", s778 );
throw new s16( L"The required library's name '" + req + L"' is ambiguous: \n" + s778 );}
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
void s268::s213( const wstring& s691 ){
s758 s675;
s269* s212 = new s269();
wstring s193 = s4::s788( s691 );
if( s813.size() ) {
wstring file = s193.substr( s193.rfind( L"/" ) + 1 );
s193 = s753( s813, s193.substr(0, s193.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s34( s193 );
if( isf == 2 ) {
s4::s62( s193 );
s193 += s7::s475;
if( s813.empty() )
s813 = s691;}
else if( isf == 1 ) {
if( s813.empty() )
s813 = s193.substr( 0, s193.find_last_of( L"\\/" ) );
}
else
throw new s16( L"cannot find file or directory: " + s691,
(uint32_t)s16::s17::s23 );
s4::s62( s813 );
s695( s193, s675 );
size_t s849 = s203.size();
vector<s9<s146>> s692;
for( size_t n = 0; n < s675.s693.size(); n++ ) {
s692.clear();
wstring s694 = s675.s693[n];
if( s694[0] != L'/' && s694[1] != L':' )
s694 = s813 + s694;
s203.push_back( s694 );}
for( size_t n = s849; n < s203.size(); ++n ) {
s692.clear();
s1036 s1159 = new s1033( s203[n] );
s1159->read( s692, s7::s433 );
for( size_t m = 0; m < s692.size(); m++ ) {
if( s269::s308( *s692[m], s7::s480 ) == s7::s471 )
s217( s203[n], *s692[m] );
else if( s269::s301( *s692[m], s7::s469 ) == s7::s469 ) {
s692[m]->s162( s7::s1241, new s6::s144( L"\"" 
+ s203[n] + 
L"\"" 
), s146::s148::s150 );
s212->s295( *s692[m] );}}}
s211( *s212 );
if( s1115.s1021() )
throw s1022( s1022::s17::s1097 );
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
void s268::s1827( const std::wstring& s702 ){
s501* pd = s655.get( s702 );
if( pd->s513() == s497 )
((s278*)pd)->s1826();}
s501* s268::run( const vector<wstring>& s723 ){
if( s204.empty() )
s204 = s7::s474 + L"::" + s7::s473;
if( !s723.empty() ) {
wstring  s703, s702;
s701( s204, s702, s703 );
s278* mod = (s278*)s655.get( s702 );
s868::Cont s1433;
wstring ts = s764->s368() + L"<" + s374::proto->s368() + L">";
s1171 pt = s764->s1338( ts, s1433 );
s323* s998 = (s323*) s306->TR().s1107( pt )->s370( this, vector<s502*>( {} ) );
for( size_t n = 0; n < s723.size(); ++n ) {
s998->add( new s374( this, s723[n] ) );}
mod->s921( s7::s1748, s998 );
mod->s921( s7::s889, new s360( this, (int)s723.size() ) );}
vector<wstring> l;
return callFunc( s204, l );}
s501* s268::callFunc( const wstring& s, vector<wstring>& l ){
wstring  s703, s702;
s701( s, s702, s703 );
s278* mod = (s278*)s655.get( s702 );
s506 s704 = (s615*)mod->s670( s703, L"::" );
vector<s503> s280;
for( size_t n = 0; n < l.size(); n++ ) {
s1035 ast_ = new s269( l[n], NULL );
s508 cs = s615::s1236( *ast_, this, mod, mod->s304() );
s280.push_back( cs );}
s704->s620( s280 );
s502* pr = s704->s515();
try {
s1486 = false;
if( !pr )
s704->s519( this, true );
else
s704->s621( this );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s704->s305() + L"' function " );}
s1486 = true;
mod->s1826();
s501* s717 = s704->s516();
s1486 = false;
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
s1036 s1159 = new s1033( s193 );
s1159->read( s692, s7::s433 );
s758 s675;
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
s1036 s1159 = new s1033( s694 );
s1159->read( s692, s7::s433 );
for( size_t m = 0; m < s692.size(); m++ )
if( s269::s301( *s692[m], s7::s469 ) == s7::s469 )
s736.s295( *s692[m] );}}
void s268::s206( const s6::s146& obj, s758& s156 ){
const vector<s145>& s165 = obj.s161( s7::s482 )->s170();
for( size_t n = 0; n < s165.size(); n++ )
s156.s693.push_back( s165[n]->s172() );
if( obj.s159( s7::s481 ) )
s156.entry = obj.s161( s7::s481 )->s172();}
void s268::s223( s501* p, const wstring& s361 ){
s207.s223( p, s361 );}
bool s268::s579( const wstring& sym_, s386* ref, const wstring& s346 ) const{
if( !s278::s579( sym_, ref, s346 ) ) {
if( sym_ == s7::s1748 ) {
ref->s394( s668( s7::s896 ), s380 );
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
s615* s268::s218( int s1632, 
std::vector<s277*>& s740, s278* s612, s615* s219, const s269* s736 ){
s615* s717 = NULL;
if( s1632 == s1611 )
s717 = new s633( this, s612, s219, s740, s736 );
else if( s1632 == s1625 )
s717 = new s629( this, s612, s219, s740, s736 );
else if( s1632 == s1802 )
s717 = new s1784( this, s612, s219, s740, s736 );
else if( s1632 == s1605 )
s717 = new s632( this, s612, s219, s740, s736 );
else if( s1632 == s1606 )
s717 = new s1579( this, s612, s219, s740, s736 );
else if( s1632 == s1624 )
s717 = new s311( this, s612, s219, s740, s736 );
else if( s1632 == s1615 )
s717 = new s631( this, s612, s219, s740, s736 );
else if( s1632 == s1619 || s1632 == s1738)
s717 = new s634( this, s612, s219, s740, s736 );
else if( s1632 == s1608 )
s717 = new s635( this, s612, s219, s740, s736 );
else if( s1632 == s1613 )
s717 = new s906( this, s612, s219, s740, s736 );
else if( s1632 == s1616 )
s717 = new s907( this, s612, s219, s740, s736 );
else if( s1632 == s1621 )
s717 = new s637( this, s612, s219, s740, s736 );
else if( s1632 == s1620 )
s717 = new s636( this, s612, s219, s740, s736 );
else if( s1632 == s1607 )
s717 = new s638( this, s612, s219, s740, s736 );
else if( s1632 == s1610 )
s717 = new s640( this, s612, s219, s740, s736 );
else if( s1632 == s1617 )
s717 = new s641( this, s612, s219, s740, s736 );
else if( s1632 == s1614 )
s717 = new s848( this, s612, s219, s740, s736 );
else if( s1632 == s1612 )
s717 = new s823( this, s612, s219, s740, s736 );
else if( s1632 == s1623 )
s717 = new s1474( this, s612, s219, s740, s736 );
else if( s1632 == s1805 )
s717 = new s1787( this, s612, s219, s740, s736 );
else if( s1632 == s1622 )
s717 = new s841( this, s612, s219, s740, s736 );
else if( s1632 == s1801 )
s717 = new s1782( this, s612, s219, s740, s736 );
else if( s1632 == s1803 )
s717 = new s1785( this, s612, s219, s740, s736 );
else if( s1632 == s1800 )
s717 = new s1781( this, s612, s219, s740, s736 );
else if( s1632 == s1618 ) {
s717 = new s873( this, s612, s219, s740, s736 );}
else if( s1632 == s1804 )
s717 = new s1786( this, s612, s219, s740, s736 );
else if( s1632 == s1609 )
s717 = new s983( this, s612, s219, s740, s736 );
else if( s1632 == s1799 )
s717 = new s1780( this, s612, s219, s740, s736 );
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
void s268::s1520( const wstring& s702 ){
s655.s565( s702 );
if( s207.s159( s702) )
s207.s1843( s702 );}
void s268::s1842( const wstring& s1810 ){
vector<wstring> s1820;
for( auto it = s655.Table().begin(); it != s655.Table().end(); ++it ) {
s277* p = it->second.s15<s277*>();
if( p->s513() == s497 || p->s513() == s496 ) {
wstring s193 = ( (s278*)p )->s670( s7::s1241, 
L":::" )->to_wstring();
if( s193 == s1810 )
s1820.push_back( it->first );}}
for( auto mod : s1820 )
s1520( mod );
for( size_t n = 0; n < s203.size(); ++n ) {
if( s203[n] == s1810 ) {
s203.erase( s203.begin() + n );
break;}}}
void s268::s310( std::wostream* pd, int s201 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s201 ) << s284 << L" : " << L"Assembly" << endl;
s207.s310( pd, s201 + s434 );
s655.s310( pd, s201 + s434 );}
map<int, s268*> handles;
HPROG createAssembly(){
static int s716 = 0;
s268* p = new s268();
handles[++s716] = p;
p->s519( false );
return s716;}
void loadProgram( HPROG handle, const wstring& s193 ){
s268* p = handles[handle];
p->s213( s193 );}
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
void importSymbol( HPROG handle, const std::wstring& s1229, const std::wstring& symName,
const std::wstring& s346 ){
s268* p = handles[handle];
s278* ob = (s278*)p->s670( s1229, s346 );
ob->s578( symName, s346 );}
void importFile( HPROG handle, const std::wstring& s1229, const std::wstring& s44,
const std::wstring& s346 ){
vector<s1::s9<s6::s146>> s692;
s6::s1033 s1159( s44 );
s1159.read( s692, s7::s433 );
s268* p = handles[handle];
p->s213( s44 );
s278* ob = (s278*)p->s670( s1229, s346 );
for( size_t n = 0; n < s692.size(); n++ ) {
wstring s687 = s269::s308( *s692[n], s7::s480 );
ob->s578( s687, s346 );}}
HPROG initShell( const std::wstring& s1229, const std::wstring& modText ){
s1::s9<s6::s146> ob = new s6::s146(NULL);
size_t pos = 0;
s6::s1033 s1159( L"" );
s1159.s174( modText, pos, ob );
ob->s162( L"name", new s6::s144( s1229 ) );
HPROG prog = createAssembly();
s215( prog, *ob );
return prog;}
} // namespace transd
