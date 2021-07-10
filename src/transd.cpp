
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
uint32_t s17::s28;
std::vector<std::wstring> s1095 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1239(){
s17::s30();}}
using namespace s2;
using s2::s17;
namespace s3 {
time_t s34( const std::wstring& f ){
int err;
#ifndef WIN32
struct stat st;
err = stat( U8( f ).c_str(), &st );
#else
struct _stat st;
err = _wstat( f.c_str(), &st );
#endif
if( err )
throw new s17( L"cannot get mtime of: " + f, 
(uint32_t)s17::s18::s24 );
return st.st_mtime;}
uint8_t s35( const std::wstring& f ){
int err;
#ifndef WIN32
struct stat st;
err = stat( U8( f ).c_str(), &st );
#else
struct _stat st;
err = _wstat( f.c_str(), &st );
#endif
if( err )
throw new s17( L"file system object does not exist: " + f,
(uint32_t)s17::s18::s24 );
if( st.st_mode & S_IFREG )
return 1;
else if( st.st_mode & S_IFDIR )
return 2;
return 0;}
bool s37( const wstring& s215 ){
try {
s35( s215 );}
catch( s17& ) {
return false;}
return true;}
bool s36( const wstring& s215 ){
try {
if( s35( s215 ) != 1 )
throw new s17( L"Cannot find data file: " + s215,
(uint32_t)s17::s18::s24 );}
catch( s17* e ) { // file don't exist
if( e->which() != (uint32_t)s17::s18::s24 )
throw;
return false;}
return true;}
} // namespace s3
#ifdef __LINUX__
using namespace std;
using namespace s2;
using namespace s5;
namespace s3 {
wstring s38(){
char buf[1024];
memset( buf, 0, 1024 );
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );}
wstring s39(){
wstring s718 = s38();
size_t pl = s718.rfind( '/' );
if( pl == string::npos )
s718 = L"";
else
s718 = s718.substr( 0, pl );
return s718;}
bool s32( const wstring& s47, const wstring& s548, wstring& s157 ){
struct dirent *entry;
DIR *dp;
wregex rg( s548 );
bool s718 = false;
dp = opendir( conv.to_bytes( s47.c_str() ).c_str() );
if( dp == NULL ) {
wstring s732 = conv.from_bytes( strerror( errno ) );
throw new s17( L"cannot open directory: " + s47 + L";\nerror: " + s732,
(uint32_t)s17::s18::s23 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s157 = s47 + L"/" + conv.from_bytes( entry->d_name );
s718 = true;
break;}}
closedir( dp );
return s718;}
void s33( const wstring& s47, const wstring& s548, vector<wstring>& s41, vector<wstring>& s42 ){
struct dirent *entry;
DIR *dp;
wregex rg( s548 );
dp = opendir( conv.to_bytes( s47.c_str() ).c_str() );
if( dp == NULL ) {
wstring s732 = conv.from_bytes( strerror( errno ) );
throw new s17( L"cannot open directory: " + s47 + L";\nerror: " + s732,
(uint32_t)s17::s18::s23 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
wstring item = conv.from_bytes( entry->d_name );
wstring s = s47 + L"/" + item;
uint8_t is = s35( s );
if( is == 1 )
s41.push_back( item );
else if( is == 2 )
s42.push_back( item );}}
closedir( dp );}
bool s761( const std::wstring& f ){
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
wstring s38(){
wchar_t s43[1024];
DWORD length = GetModuleFileNameW( NULL, s43, 1024 );
return s43;}
wstring s39(){
wchar_t s43[1024];
DWORD length = GetModuleFileNameW( NULL, s43, 1024 );
PathRemoveFileSpecW( s43 );
return s43;}
bool s32( const wstring& _dir, const wstring& s548, wstring& s157 ){
HANDLE s49;
WIN32_FIND_DATAW s44;
wstring s45, s46;
wregex rg( s548.c_str() );
bool s718 = false;
wstring s47 = _dir;
if( s47.back() != L'/' && s47.back() != L'\\' )
s47 += L'\\';
if( ( s49 = FindFirstFileW( ( s47 + L"*" ).c_str(), &s44 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s49, &s44 ) ) {
s45 = s44.cFileName;
s46 = s47 + s45;
if( regex_match( s45, rg ) ) {
s157 = s46;
s718 = true;
break;}}
return s718;}
void s33( const wstring& _dir, const wstring& s548, vector<wstring>& s41, vector<wstring>& s42 ){
HANDLE s49;
WIN32_FIND_DATAW s44;
wstring s45, s46;
wregex rg( s548.c_str() );
wstring s47 = _dir;
if( s47.back() != L'/' && s47.back() != L'\\' )
s47 += L'\\';
if( ( s49 = FindFirstFileW( ( s47 + L"*" ).c_str(), &s44 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s49, &s44 ) ) {
s45 = s44.cFileName;
s46 = s47 + s45;
if( regex_match( s45, rg ) ) {
uint8_t is = s35( s46 );
if( is == 1 )
s41.push_back( s45 );
else if( is == 2 )
s42.push_back( s45 );}}}
bool s761( const std::wstring& f ){
if( f.size() && f[1] == ':' )
return true;
return false;}
} // namespace s3
#endif // WIN32
namespace s4 {
wstring s90 = L"\"`'";
wstring s50 = L"\n\r\t ";
string s51 = "\n\r\t ";
wstring s52 = L"";
wstring digits = L"0123456789";
void s56( const wstring& s, size_t s67, wchar_t left, wchar_t right,
size_t& start, size_t& end, bool s972/*=false*/ )
{
end = string::npos;
start = string::npos;
int s68 = 0;
wchar_t s959 = 0;
for( size_t n = s67; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s959 || !s972 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s68++;}
else if( c == right ) {
if( start == string::npos )
return; // s891
if( --s68 == 0 ) {
end = n;
return;}}
else if( s972 && ( c == L'\'' || c == L'\"' ) ) {
s959 = c;}}
else if( s959 && c == s959 ) {
s959 = 0;}}}
void s937( const wstring& s, size_t s67, wchar_t left, wchar_t right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s67 );
if( start == string::npos || start == s.size() - 1 )
return;
int s68 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s68;
continue;}
if( s[n] == right )
--s68;
if( s68 == 0 ) {
end = n;
return;}}}
void s57( const wstring& s, size_t s67, wchar_t c, size_t& start, size_t& end ){
end = string::npos;
start = s.find( c, s67 );
if( start == string::npos || start == s.size() - 1 )
return;
bool s927 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s927 = !s927;
if( s[n] == c && !s927 ) {
end = n;
return;}
if( s[n] != L'\\' )
s927 = false;}}
void s1100( const std::wstring& s, size_t& s67, const std::wstring& s1510 ){
size_t pl = s.find_first_of( s1510, s67 );
if( pl == s67 )
return;
size_t start = s67;
s67 = string::npos;
while( pl < s.size() ) {
if( s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl++;
if( pl < s.size() )
pl = s.find_first_of( s1510, pl );}
else {
s67 = pl;
return;}}}
void s1494( const std::wstring& s, size_t& s67, const std::wstring& s1207 ){
size_t pl = s.find( s1207, s67 );
if( pl == s67 )
return;
size_t start = s67;
s67 = string::npos;
while( pl < s.size() ) {
if( s1207.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1207.size();
if( pl < s.size() )
pl = s.find( s1207, pl );}
else {
s67 = pl;
return;}}}
size_t count( const std::wstring& s79, const std::wstring& s1207, size_t start, size_t end,
bool s972 ){
size_t s718 = 0;
size_t pl = s79.find( s1207, start );
while( pl < s79.size() && pl <= end) {
if( s972 && pl && s79[pl-1] == '\\' ) {
++pl;}
else {
++s718;
pl += s1207.size();}
if( pl < s79.size() - 1 ) 
pl = s79.find( s1207, pl );}
return s718;}
int s58( const wstring& s79, wchar_t s74, size_t& pos ){
size_t s72 = s79.find( s74, pos );
if( s72 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s54( s79.substr( pos, s72 - pos ), L" " );
int s718 = stoi( s );
pos = s79.find_first_not_of( s50 + s74, s72 );
return s718;}
bool s64( const wchar_t *str, long *s364, wchar_t **end /*= NULL*/ )
{
wchar_t *s69;
bool s718 = true;
errno = 0;
*s364 = std::wcstol( str, &s69, 0 );
if( s69 == str || ( !end && *s69 != '\0' ) ||
( ( *s364 == LONG_MIN || *s364 == LONG_MAX ) && errno == ERANGE ) )
s718 = false;
if( end )
*end = s69;
return s718;}
bool s1719( const wchar_t *str, long long *s364, wchar_t **end /*= NULL*/ )
{
wchar_t *s69;
bool s718 = true;
errno = 0;
*s364 = std::wcstoll( str, &s69, 0 );
if( s69 == str || ( !end && *s69 != '\0' ) ||
( ( *s364 == LLONG_MIN || *s364 == LLONG_MAX ) && errno == ERANGE ) )
s718 = false;
if( end )
*end = s69;
return s718;}
bool s1720( const wchar_t *str, unsigned long long *s364, wchar_t **end /*= NULL*/ )
{
wchar_t *s69;
bool s718 = true;
errno = 0;
*s364 = std::wcstoull( str, &s69, 0 );
if( s69 == str || ( !end && *s69 != '\0' ) ||
( ( *s364 == ULLONG_MAX ) && errno == ERANGE ) )
s718 = false;
if( end )
*end = s69;
return s718;}
bool s65( const wchar_t *str, double *s364, wchar_t **end /*= NULL*/ )
{
wchar_t *s69;
bool s718 = true;
errno = 0;
*s364 = std::wcstod( str, &s69 );
if( s69 == str || ( !end && *s69 != '\0' ) ||
( ( *s364 == HUGE_VAL || *s364 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s718 = false;
if( end )
*end = s69;
return s718;}
void s960( const wstring& s79, vector<wstring>& s157 ){
size_t s70 = s79.find_first_not_of( s50 );
size_t s714, s715;
while( s70 != string::npos ) {
wchar_t c = s79[s70];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s57( s79, s70, c, s714, s715 );
if( s715 == string::npos )
throw s2::s17( L"Quotes don't match near \'" + s79.substr( s70, 40 ) + L"...\'" );
arg = s79.substr( s70, s715 - s70 + 1 );
s70 = s79.find_first_not_of( s50, ++s715 );}
else {
s715 = s79.find_first_of( s50 );
arg = s79.substr( s70, s715 - s70 );
s70 = s715;}
s157.push_back( arg );}}
void s59( const wstring& s, const wstring& s74, vector<wstring>& s157, bool clr ){
size_t s70 = 0, s71 = 0;
while( s71 != wstring::npos && s70 < s.size()) {
s71 = s.find( s74, s70 );
wstring seg;
if( clr ) 
seg = s54( s.substr( s70, s71 - s70 ), s50 );
else
seg = s.substr( s70, s71 - s70 );
s70 = s71 + s74.size();
if( seg.size() )
s157.push_back( seg );}}
void s296( const vector<wstring>& v, const wstring& s74, wstring& s157 ){
if( v.empty() )
return;
s157 = v[0];
for( size_t n = 1; n < v.size(); ++n )
s157 += (s74 + v[n]);}
wstring s73( const wstring& s79, size_t& pos ){
size_t pl = s79.find( L'\n', pos );
wstring line = s54( s79.substr( pos, pl - pos ), s50 );
pos = pl == string::npos ? pl : pl + 1;
return line;}
void s60( const wstring& s79, const wstring& s74, 
pair<wstring, wstring>& pr, size_t& pos ){
size_t pl = s79.find( L'\n', pos );
wstring line = s54( s79.substr( pos, pl - pos ), s50 );
pos = pl == string::npos ? pl : pl + 1;
pl = line.find( s74 );
if( pl == string::npos ) 
throw s2::s17( L"invalid pair syntax: " + line );
wstring s78 = s54( line.substr( 0, pl ), s50 );
wstring s364 = s54( line.substr( pl + s74.size() ), s50 );
pr.first = s78;
pr.second = s364;}
void s61( const wstring& s79, const wstring& s74, vector<pair<wstring, wstring>>& v ){
vector<wstring> s75;
s59( s54( s79, s50 ), L"\n", s75 );
for( size_t n = 0; n < s75.size(); ++n ) {
size_t pl = s75[n].find( s74 );
wstring s78 = s54( s75[n].substr( 0, pl ), s50 );
wstring s364 = s54( s75[n].substr( pl + s74.size() ), s50 );
v.push_back( make_pair( s78, s364 ) );}}
wstring s53( const std::wstring& l, const std::wstring& s, const std::wstring& r ){
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s718 = s.substr( pl );
return s718.substr( 0, s718.find_last_not_of( r ) + 1 );}
wstring s54( const std::wstring& s, const std::wstring& c ){
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s718 = s.substr( pl );
return s718.substr( 0, s718.find_last_not_of( c ) + 1 );}
wstring s62( const wstring& s79 ){
if( s79[0] != L'{' )
return s79;
size_t s76, s77;
s56( s79, 0, L'{', L'}', s76, s77 );
wstring s81 = s79.substr( s76 + 1, s77 - s76 - 1 );
vector<wstring> s82;
s59( s54( s81, L" " ), L"|", s82 );
#ifdef WIN32	
return s82[0] + s79.substr( s77 + 1 );
#else
return s82[1] + s79.substr( s77 + 1 );
#endif	
}
bool s55( const std::wstring& s, const std::wstring& ss ){
if( s.substr( s.size() - ss.size() ) == ss )
return true;
return false;}
void s63( wstring& s47 ){
#ifdef WIN32
if( s47.back() != L'/' &&
s47.back() != L'\\' ) {
size_t pl = s47.find( L"\\" );
size_t pl1 = s47.find( L"/" );
if( pl != string::npos && pl > pl1 )
s47 += L"\\";
else
s47 += L"/";
}
#else
if( s47.back() != L'/' )
s47 += L"/";
#endif
}
wstring s789( wstring path ){
size_t pl = path.find( L"\\" );
while( pl != string::npos ) {
path = path.replace( pl, 1, L"/" );
pl = path.find( L"\\" );}
if( path.front() == L'\'' || path.front() == L'"' ) {
if( path.back() != path.front() )
throw new s2::s17( L"opening and closing quotes don't match" );
path = path.substr( 1, path.size() - 2 );}
return path;}
void s66( const std::wstring& s80 ){}
void s56( const string& s, size_t s67, char left, char right,
size_t& start, size_t& end ){
end = string::npos;
start = s.find( left, s67 );
if( start == string::npos || start == s.size() - 1 )
return;
int s68 = 1;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == left ) {
++s68;
continue;}
if( s[n] == right )
--s68;
if( s68 == 0 ) {
end = n;
return;}}}
int s58( const string& s79, char s74, size_t& pos ){
size_t s72 = s79.find( s74, pos );
if( s72 == string::npos )
throw invalid_argument( "separator not found" );
string s = s54( s79.substr( pos, s72 - pos ), " " );
int s718 = stoi( s );
pos = s79.find_first_not_of( s51 + s74, s72 );
return s718;}
void s59( const string& s, const string& s74, vector<string>& s157 ){
size_t s70 = 0, s71 = 0;
while( s71 != string::npos ) {
s71 = s.find( s74, s70 );
string seg = s54( s.substr( s70, s71 - s70 ), s51 );
s70 = s71 + s74.size();
s157.push_back( seg );}}
void s61( const string& s79, vector<pair<string, string>>& v ){
vector<string> s75;
s59( s54( s79, s51 ), "\n", s75 );
for( size_t n = 0; n < s75.size(); ++n ) {
size_t pl = s75[n].find( ':' );
string s78 = s54( s75[n].substr( 0, pl ), s51 );
string s364 = s54( s75[n].substr( pl + 1 ), s51 );
v.push_back( make_pair( s78, s364 ) );}}
string s53( const std::string& l, const std::string& s, const std::string& r ){
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s718 = s.substr( pl );
return s718.substr( 0, s718.find_last_not_of( r ) + 1 );}
string s54( const std::string& s, const std::string& c ){
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s718 = s.substr( pl );
return s718.substr( 0, s718.find_last_not_of( c ) + 1 );}
string s62( const string& s79 ){
if( s79[0] != '{' )
return s79;
size_t s76, s77;
s56( s79, 0, '{', '}', s76, s77 );
string s81 = s79.substr( s76 + 1, s77 - s76 - 1 );
vector<string> s82;
s59( s54( s81, " " ), "|", s82 );
#ifdef WIN32	
return s82[0] + s79.substr( s77 + 1 );
#else
return s82[1] + s79.substr( s77 + 1 );
#endif	
}
void s83( wstring& s79, vector<wstring>& s1222, map<size_t, size_t>& s1146 ){
size_t pos = 0;
wchar_t s84 = 0;
bool s1306 = false;
wchar_t s85 = 0;
bool s86 = false;
bool s87 = false;
size_t s88 = string::npos;
bool s89 = false;
bool s1076 = false;
wstring s90 = L"`'\"";
s1222.reserve( 1000 );
size_t s1140 = 1;
bool s1067 = false;
while( pos < s79.size() ) {
wchar_t c = s79[pos];
if( c == '\r' ) {
s79.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1306 = !s1306;}
else if( s84 ) {
if( c == s84 && !s1306 /*s85 != '\\'*/ )
s84 = 0;}
else if( s90.find( c ) != string::npos ) {
if( !s86 ) {
s84 = c;}}
else if( c == '*' ) {
if( !s86 && s85 == '/' ) {
s86 = true;
s87 = true;
s88 = pos - 1;
if( pos > 1 && s79[pos - 2] != '\n')
s1146[pos - 2] = s1140;}}
else if( c == '/' ) {
if( !s86 && s85 == '/' ) {
s88 = pos - 1;
s86 = true;
s87 = false;
if( pos > 1 && s79[pos - 2] != '\n')
s1146[pos - 2] = s1140;}
else if( s87 && s85 == '*' ) {
s89 = true;
if( s79[pos+1] == '\n' ){
s1067 = true;}}}
else if( c == '\n' ) {
s1067 = true;
if( s86 ) {
if( !s87 ) {
s89 = true;}
else {
if( !s1076 ) {
s1076 = true;}}}
else {
if( pos && s79[pos-1] != '\n' ) {
s1146[pos - 1] = s1140;}}}
if( c != L'\\' )
s1306 = false;
if( s1067 ) {
size_t pl = s79.rfind( '\n', pos - 1 );
size_t m = (s79[pos] == '\n');
if( pl == string::npos )
s1222.push_back( s79.substr( 0, pos ) );
else
s1222.push_back( s79.substr( pl + 1, pos - pl - m ) );
s1067 = false;
s1140++;}
if( s89 ) {
int m = 0;
if( s87 )
m = 1;
if(	s79[pos] == '\n' && ( !s88 || s79[s88 -1] == '\n' ) )
m = 1;
if( m ) {
s79.replace( s88, pos - s88 + m, L"");
pos = s88 - 1;}
else {
s79.replace( s88, pos - s88 + m, L" ");
pos = s88 + 1;}
s88 = string::npos;
s86 = false;
s1076 = false;
s87 = false;
s89 = false;
s85 = 0;}
s85 = c;
pos++;}
if( s86 ) {
auto it = end(s1146);
if( s1146.size() ) it--; 
size_t ln = (it == end(s1146) ? 0 : it->second);
throw new s2::s17( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
}//namespace s4
namespace s5 {
std::locale locloc;
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;}
#ifdef WIN32
#include <conio.h>
#endif
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace s4;
namespace consutils {
uint32_t s18::s92;
void s18::s30(){
s92 = s17::s29();}
void s1235(){
s18::s30();}
bool s102( const wstring& s96 ){
wcout << s96 << L" [Y]es | [n]o :";
wstring ans;
getline( wcin, ans );
if( ans.size() && s54( ans, L" " ).empty() )
throw new s17( s18::s93() );
if( ans.size() && ( ans[0] == L'N' || ans[0] == L'n' ) )
return false;
return true;}
int s103( const wstring& s96, const vector<wstring>& s97 ){
int s718;
while( true ) {
s134();
wcout << s96 << endl << endl;
for( size_t i = 0; i < s97.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s97[i] << endl;}
s718 = s107( L"Please, enter your answer's number: " );
if( s718 < 0 || s718 > ( int ) s97.size() ) {
wcout << "No variant with such number." << endl;
s99();
continue;}
break;}
return s718;}
wstring s104( const wstring& s96, bool s98 ){
if( !s96.empty() )
wcout << s96;
wstring s364;
if( s98 )
s101( false );
getline( wcin, s364 );
if( s98 )
s101( true );
return s364;}
wstring s105( const wstring& s96, bool s98 ){
wcout << s96;
int s121 = 0;
bool s613 = true;
wstring s122 = s96;
size_t s1229 = s122.size();
size_t s123 = s1229;
while( s613 ) {
s121 = _getch();
switch( s121 ) {
case s114:
if( s1229 > s123 ) {
wcout << '\r' << s122.substr( 0, --s1229 );}
break;
case s115:
if( s1229 < s122.size() )
wcout << s122[s1229++];
break;
case s112:
case s113:
continue;
case s118:
if( ( s1229 > s123 ) && s122.size() ) {
s122.erase( --s1229, 1 );
wcout << '\r' << wstring( s122.size() + 1, L' ' );
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}
break;
case s119:
if( s1229 < s122.size() ) {
s122.erase( s1229, 1 );
wcout << '\r' << wstring( s122.size() + 1, L' ' );
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}
break;
case s117:
s613 = false;
break;
case s120:
break;
default:
if( s1229 < s122.size() )
s122.insert( s1229, 1, s121 );
else
s122 += s121;
++s1229;
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}}
return s122;}
wstring getStringValHist( const wstring& s96, const vector<wstring>& s106 ){
wcout << s96 << endl;
int s121 = 0;
size_t s717 = s106.size();
bool s613 = true;
wstring s122;
size_t s1229 = 0;
while( s613 ) {
s121 = _getch();
wcout << L"[" << s121 << L"]" << endl;
#ifdef __LINUX__
if(s121 == 27) {
_getch();
s121 = _getch();
if( s121 == L'A' ) s121 = s112;
else if(s121 == L'B') s121 = s113;
else if(s121 == L'C') s121 = s115;
else if(s121 == L'D') s121 = s114;}
else if( s121 == 10 )
s121 = 13;
else if( s121 == 127 )
s121 = 8;
#else			
if(s121 == 224) {
s121 = _getch();
wcout << L"<" << s121 << L">" << endl;
if( s121 == L'H' ) s121 = s112;
else if(s121 == L'P') s121 = s113;
else if(s121 == L'M') s121 = s115;
else if(s121 == L'K') s121 = s114;}
else if( s121 == 0 ) {
s121 = _getch();
wcout << L"<" << s121 << L">" << endl;
if( s121 = 83 ) s121 = s119; // S
else if( s121 = 71 ) s121 = KB_HOME; // G
else if( s121 = 79 ) s121 = KB_END; // O
}
#endif			
switch( s121 ) {
case s114:
if( s1229 > 0 ) {
wcout << '\r' << s122.substr( 0, --s1229 );}
break;
case s115:
if( s1229 < s122.size() )
wcout << s122[s1229++];
break;
case s112:
if( s717 > 0 ) {
if( s717 < s106.size() )
wcout << '\r' << wstring( s122.size(), L' ' );
s122 = s106[--s717];
wcout << '\r' << s122;
s1229 = s122.size();}
break;
case s113:
if( !s106.empty() && s717 < s106.size() - 1 ) {
wcout << '\r' << wstring( s122.size(), L' ');
s122 = s106[++s717];
wcout << '\r' << s122;
s1229 = s122.size();}
break;
case s118:
if( s1229 > 0 && s122.size() ) {
s122.erase( --s1229, 1 );
wcout << '\r' << wstring( s122.size() + 1, L' ' );
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}
break;
case s119:
if( s1229 < s122.size() ) {
s122.erase( s1229, 1 );
wcout << '\r' << wstring( s122.size() + 1, L' ' );
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}
break;
case KB_HOME:
if( s1229 > 0 ) {
wcout << '\r';
s1229 = 0;}
break;
case KB_END:
if( s1229 < s122.size() ) {
wcout << '\r' << s122;
s1229 = s122.size();}
break;
case s117:
s613 = false;
break;
case s120:
break;
default:
if( s1229 < s122.size() )
s122.insert( s1229, 1, s121 );
else
s122 += s121;
++s1229;
wcout << '\r' << s122 << '\r' << s122.substr( 0, s1229 );}}
return s122;}
int s107( const std::wstring & s96 ){
int s718;
while( true ) {
wcout << s96;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s718 = stoi( inp );}
catch( std::invalid_argument& ) {
continue;}
break;}
return s718;}
void s94( const wstring& header, const std::vector<std::wstring>& s95 ){
s134();
wcout << endl << "  " << header << endl << fill_n_ch( L'-', header.size() + 4 )
<< endl << endl;
if( s95.size() ) {
wcout << L"Keyboard shortcuts: " << endl;
for( size_t n = 0; n < s95.size(); n += 2 )
wcout << setw( 10 ) << left << s95[n] << L" - " << s95[n + 1] << endl;}
wcout << endl;}
size_t s108( const std::wstring & s96 ){
wcout << s96 << endl << endl <<
L"Please, enter the number of menu item: " << endl <<
L"1 - Skip this item" << endl << L"2 - Overwrite this item" << endl <<
L"3 - Skip all already existing items" << endl <<
L"4 - Overwrite all already existing items" << endl << "5 or any key - Cancel operation" << endl;
wstring s133;
getline( wcin, s133 );
int i;
try { i = stoi( s133 ); }
catch( std::invalid_argument* ) {
i = 5;}
if( i < 1 || i > 5 )
i = 5;
return i;}
void s110( const vector<wstring>& v, vector<wstring>& s157, size_t w, size_t h ){
size_t s124 = v.size() / h + 1;
size_t s125 = v.size() / s124;
vector<size_t> s126;
size_t s717 = 0;
for( auto it : v ) {
if( s717 == 0 )
s126.push_back( 0 );
if( it.size() > s126.back() )
s126.back() = it.size();
if( ++s717 == s125 )
s717 = 0;}
size_t s127 = 0, s128 = 0;
size_t s129 = 0;
for( size_t n = 0; n < s124; ++n ) {
s129 += s126[n] + 5;
if( n == s124 - 1 || s129 + s126[n + 1] + 5 > w ) {
size_t s130 = n - s127 + 1;
s129 = 0;
if( s127 ) {
if( s104( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}
for( size_t m = s128;
m < min( s128 + s125, v.size() );	++m ) {
wostringstream ss;
for( size_t k = 0;
k < min( s130, ( v.size() - m - 1 ) / s125 + 1 ); ++k )
ss << setw( 3 ) << right << m + s125 * k + 1 << L". " << setw( s126[s127 + k] ) <<
left << v[m + s125 * k];
s157.push_back( ss.str() );}
s128 += s130 * s125;
s127 = n + 1;}}}
int s111( const std::vector<std::wstring>& v ){
int w, h;
s109( w, h );
std::vector<std::wstring> rows;
s110( v, rows, w, h );
size_t s131 = 0;
for( auto it : rows ) {
wcout << it << endl;
if( ++s131 % h == 0 ) {
if( s104( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}}
int s132;
while( true ) {
wcout << endl;
wstring s133 = s104( L"Enter the item's number or <Space> to cancel..." );
if( s133 == L" " )
return -1;
try { s132 = stoi( s133 ); }
catch( std::invalid_argument& ) {
continue;}
break;}
if( s132 > (int)v.size() ) {
wcout << L"No record with such number." << endl;
return -1;}
return s132;}
} // namespace consutils
#ifdef __LINUX__
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
namespace consutils {
wstring s38(){
char buf[1024];
readlink( "/proc/self/exe", buf, 1023 );
return wstring( conv.from_bytes( buf ) );}
void s99(){
wcout << endl << L"Press 'Return' to continue..." << endl;
std::system( "read" );}
void s134( int s75 ){
std::system( "clear" );
for( int i = 0; i < s75; ++i )
wcout << endl;}
void s101( bool b ){
struct termios tty;
tcgetattr( STDIN_FILENO, &tty );
if( !b )
tty.c_lflag &= ~ECHO;
else
tty.c_lflag |= ECHO;
(void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );}
void s109( int& w, int& h ){
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
if( buf[2] == 65 ) buf[0] = s112;
if( buf[2] == 66 ) buf[0] = s113;
if( buf[2] == 67 ) buf[0] = s115;
if( buf[2] == 68 ) buf[0] = s114;}
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
void s99(){
wcout << endl;
std::system( "pause" );}
void s134( int s75 ){
std::system( "CLS" );
for( int i = 0; i < s75; ++i )
wcout << endl;}
void s101( bool b ){
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode;
GetConsoleMode( hStdin, &mode );
if( !b )
mode &= ~ENABLE_ECHO_INPUT;
else
mode |= ENABLE_ECHO_INPUT;
SetConsoleMode( hStdin, mode );}
void s109( int& w, int& h ){
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;}
} // namespace consutils
#endif // WIN32
using namespace s1;
using namespace s5;
namespace s6{
wstring s190 = L"-.0123456789";
wstring s1713 = L"0123456789";
wstring s1714 = L".0123456789";
wstring s191 = L" ,]}\t\r\n";
void s1034::s175( const wstring& s79, size_t& pos, s9<s147> ob, bool s155/*= false*/ )
{
size_t s76, s77;
s56( s79, pos, L'{', L'}', s76, s77, true );
if( s76 == string::npos )
return;
s1170 = s76 - 1;
wstring sob = s79.substr( s76, s77 - s76 + 1 );
pos = s77 + 1;
ob->s158( sob, s155 );}
bool s1034::s1105( wstring& s, size_t s70, size_t s716, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1234.lower_bound( s70 );
auto iten = s1234.lower_bound( s716 );
if( itst == end(s1234) || iten == end(s1234) )
return false;
line = itst->second;
s = s1233[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1233[iten->second-1];
return true;}
void s192( wstring& s79 ){
wregex s193(
LR"regex(\n\r?\/\/.*?\n\r?)regex"
);
wsmatch sm;
wstring::const_iterator itst = s79.begin();
wstring::const_iterator iten = s79.end();
while( std::regex_search( itst, iten, sm, s193 ) ) {
s79.erase( sm.position(), sm.length() - 
(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
itst = s79.begin();
iten = s79.end();}}
s1034::s1034( const std::wstring& file ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s50 );
if( pl == string::npos )
return;
if( file[pl] == L'{' )
s1232 = file;
else
s199 = file;}
void s1034::read( vector<s9<s147>>& s157, const wstring& s195 ){
size_t pos = 0;
if( s199.size() ) {
std::ifstream fs( TOFS( s199 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s199 ));
string s196( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1232 = conv.from_bytes( s196 );
s4::s83( s1232, s1233, s1234 );
if( s195.size() ) {
pos = s1232.find( s195 );
if( pos == string::npos )
throw new s17( s195 + L" directive not found in the source file." );
pos += s195.size() + 1;
if( s1232.size() > 13 && s1232[14] == '\r' )
++pos;}}
size_t s197 = pos;
wstring s285;
bool s198 = false;
while( ( pos = s1232.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1232.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s197; subl = pos - s197;}
else
pl += 1;
wstring s1 = s54( s1232.substr( pl, /*pos - pl - 1*/subl ), s50 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s17( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s17::s18::s21 );
if( s1.size() == 1 )
s198 = true;
else
s285 = s54( s1, s50 + L":" );}
if( s285.empty() ) {
size_t pl1 = s1232.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s54( s1232.substr( pl1, pl ), s50 );
if( s1.size() ) {
if( ( !s198 && s1[s1.size() - 1] != L':' ) ||
( s198 && s1[s1.size() - 1] == L':' ) ||
(!s198 && s1.size() == 1 ) )
throw new s17( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s17::s18::s21 );
s285 = s54( s1, s50 + L":" );}}}
if( s90.find( s285[0] ) != string::npos ) {
if( s285[0] != s285[s285.size()-1] )
throw new s17( L"Malformed block name: " + s285.substr( 0, 20 ) + L"...",
(uint32_t)s17::s18::s21 );}
else {
if(	iswdigit( s285[0] ) )
throw new s17( L"wrong unquoted syntax: " + s285.substr( 0, 20 ) + L"...",
(uint32_t)s17::s18::s21 );}
s9<s147> ob = new s147( this );
s175( s1232, pos, ob, true );
if( s285.size() )
ob->s163( L"name", new s145( s285 ) );
s285 = L"";
s198 = false;
s157.push_back( ob );}}
void s176( const wstring& s199, const vector<s1::s9<s147>>& s200 ){
std::ofstream fs( TOFS( s199 ), ios::out | ios::trunc | ios::binary );
if( !fs.good() )
throw runtime_error( "Reading state file failed: " + U8( s199 ) );
for( auto ob : s200 ) {
basic_stringstream<wchar_t> ss;
ob->s159( &ss );
string s = U8( ss.str() );
s += "\n\n";
fs.write( s.c_str(), s.size() );}}
void s177( const wstring& s79, size_t& pos, wchar_t quote, wstring& s157, bool s155 = false ){
size_t s76, s77;
s57( s79, pos, quote, s76, s77 );
if( s77 != string::npos ) {
pos = s77 + 1;
if( s155 )
s157 = s54( s79.substr( s76, s77 - s76 + 1), s50 ); 
else
s157 = s54( s79.substr( s76+1, s77 - s76 - 1 ), s50 ); }
else
pos = string::npos;}
void s178( wostream* pd, const wstring& s ){
wchar_t q = L'\"';
if( s90.find( s[0] ) != string::npos )
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
void s179( const wstring& s79, size_t& pos, wstring& s157 ){
if( !std::isgraph<wchar_t>( s79[pos], locloc ) ||
s79[pos] == L':' || s79[pos] == L',' )
throw new s17( L"unrecognized unquoted syntax: " + s79.substr(pos, 20), 
(uint32_t)s17::s18::s21 );
size_t s201 = pos + 1;
while( std::isgraph<wchar_t>( s79[s201], locloc ) &&
s79[s201] != L':' && s79[s201] != L',' )
++s201;
s157 = s54( s79.substr( pos, s201 - pos ), s50 );
pos = s201;}
void s180( const wstring& s79, size_t& pos, wchar_t s1353, wchar_t s1402, wstring& s157 ){
size_t s76, s77;
s56( s79, pos, s1353, s1402, s76, s77, true );
if( s77 == string::npos )
throw new s17( L"unmatched unquoted parentheses: " + s79.substr(pos, 20), 
(uint32_t)s17::s18::s21 );
if( s77 == s79.size() - 1 ) {
pos = s77;}
else {
size_t pl = s79.find_first_not_of( s50, s77 + 1 );
if( pl == string::npos && s79[pl] != L',' && s79[pl] != L'}' )
throw new s17( L"wrong unquoted parentheses syntax: " + s79.substr( pos, 20 ),
(uint32_t)s17::s18::s21 );
pos = s77 + 1;}}
void s181( const wstring& s79, size_t& pos, wstring& s157 ){
if( !std::isgraph<wchar_t>( s79[pos], locloc ) ||
s79[pos] == L':' || s79[pos] == L',' )
throw new s17( L"unrecognized unquoted syntax: " + s79.substr( pos, 20 ),
(uint32_t)s17::s18::s21 );
size_t s201 = pos;
int shift = 0;
if( s79[pos] == L'(' ) {
s180( s79, s201, L'(', L')', s157 );
if( s201 == s79.size() - 1 )
shift = 1;}
else {
s201 = pos + 1;
while( std::isgraph<wchar_t>( s79[s201], locloc ) &&
s79[s201] != L':' && s79[s201] != L',' ) {
if( s79[s201] == L'<' ) {
s180( s79, s201, L'<', L'>', s157 );}
else if( s79[s201] == L'(' ) {
s180( s79, s201, L'(', L')', s157 );
break;}
else
++s201;}}
s157 = s54( s79.substr( pos, s201 - pos + shift ), s50 );
pos = s201;}
void s182( wostream* pd, const wstring& s ){
if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
s[s.size()-1] == L'"' )
throw new s17( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s17::s18::s21 );
for( size_t n = 0; n < s.size(); ++n ) 
if( !std::isgraph<wchar_t>( s[n], locloc ) )
throw new s17( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s17::s18::s21 );
*pd << s;}
void s183( const s1034* pf, const wstring& s79, vector<s9<s145>>& s157, bool s155,
const std::wstring& s74 ){
size_t s70 = s79.find_first_not_of( s50 );
while( true ) {
s157.push_back( s9<s145>(new s145( pf, s79, s70, s155 ) ) );
s4::s1100( s79, s70, s74 );
if( s70 == string::npos )
break;
++s70;}}
void s183( const s1034* pf, const wstring& s79, size_t& pos, vector<s9<s145>>& s157, 
bool s155, const std::wstring& s74 ){
size_t s76, s77, s70 = 0;
s56( s79, pos, L'[', L']', s76, s77, true );
pos = s77 + 1;
wstring ar = s54( s79.substr( s76 + 1, s77 - s76 - 1 ), s50 );
while( true ) {
s157.push_back( s9<s145>(new s145( pf, ar, s70, s155 ) ) );
s4::s1100( ar, s70, s74 );
if( s70 == string::npos )
break;
++s70;}}
void s184( wostream* pd, const vector<s9<s145>>& v, bool s155=false ){
*pd << L'[';
for( size_t n = 0; n < v.size(); ++n ) {
v[n]->s159( pd, s155 );
if( n != v.size() - 1 )
*pd << L',';}
*pd << L']';}
void s185( const wstring& s79, size_t& pos, wstring& s157, bool s155 = false ){
size_t pl = s79.find_first_not_of( L", \n\r\t", pos );
if( s90.find( s79[pl] ) != string::npos ) 
s177( s79, pos, s79[pl], s157, s155 );
else {
if( !std::isgraph<wchar_t>( s79[pos], locloc ) ||
s79[pos] == L':' || s79[pos] == L',' )
throw new s17( L"unrecognized name syntax: " + s79.substr( pos, 20 ) +
L"...",	(uint32_t)s17::s18::s21 );
size_t s201 = pos + 1;
while( s79[s201] != L':' && s79[s201] != L',' ) {
if( !std::isalnum<wchar_t>( s79[s201], locloc ) &&
!std::isspace<wchar_t>( s79[s201], locloc ) && s79[s201] != L'_' &&
s79[s201] != L'-' )
throw new s17( L"unrecognized name syntax: " + s79.substr( pos, 20 ) +
L"...",	(uint32_t)s17::s18::s21 );
++s201;}
s157 = s54( s79.substr( pos, s201 - pos ), s50 );
pos = s201;}}
void s186( wostream* pd, const wstring& s, bool s155=false ){
bool space = false;
for( size_t n = 0; n < s.size(); ++n )
if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
space = true;
break;}
if( !space && !s155 && s90.find( s[0] ) == string::npos )
s182( pd, s );
else
s178( pd, s );}
s135 s187( const wstring& s79, size_t& pos, double& s157 ){
s135 s718 = s144;
size_t pl = s79.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s79.find( L".", pl );
if( pl1 < pl )
s718 = s140;
if( pl == string::npos )
s157 = stod( s79.substr( pos ) );
else
s157 = stod( s79.substr( pos, pl - pos ) );
pos = pl;
return s718;}
s135 s1725( const wstring& s79, size_t& pos, double& s157 ){
const wchar_t* ps = s79.c_str();
size_t sz = s79.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1714.find( ps[st+1] ) == string::npos )
return s136;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1713.find( ps[st+1] ) != string::npos ) ||
( s1713.find( ps[st] ) == string::npos ) )
return s136;
size_t s717 = st;
bool pt = false;
while( s717 < sz ) {
if( ps[s717] == L'.' ) {
if( pt ) return s136;
pt = true;}
if( s1713.find( ps[s717] ) != string::npos )
s717++;
else
break;}
s135 s718 = s144;
if( pt )
s718 = s140;
if( s717 == sz )
s157 = stod( s79.substr( pos ) );
else
s157 = stod( s79.substr( pos, s717 - pos ) );
pos = s717;
return s718;}
bool s188( const wstring& s79, size_t& pos, bool& s157 ){
size_t pl = 0;
if( s79.find( L"true", pos, 4 ) == pos )
pl = 4;
else if( s79.find( L"false", pos, 5 ) == pos )
pl = 5;
if( pl ) {
if( s191.find( s79[pos+pl] ) != string::npos ) {
pos += pl;
s157 = (pl == 4);
return true;}}
return false;}
bool s189( const wstring& s79, size_t& pos ){
if( s79.find( L"null", pos, 4 ) == pos ) {
if( s191.find( s79[pos+4] ) != string::npos ) {
pos += 4;
return true;}}
return false;}
s145::s145( const s1034* pf, const wstring& s79, size_t& pos, bool s155/*= false*/ )
: s203( s136 ), obj( pf ), s1194( pos + (pf ? pf->s1039():0), 0 ), s1193( (s1034*)pf ){
size_t s70 = s79.find_first_not_of( L" \n\r\t", pos );
if( s79[s70] == L'{' ) {
size_t s76, s77;
s56( s79, s70, L'{', L'}', s76, s77, true );
pos = s77+1;
obj.s158( s54( s79.substr( s76 + 1, s77 - s76 - 1 ), s50 ), s155 );
s203 = s137;}
else {
pos = s70;
if ( s90.find( s79[pos] ) != string::npos ) {
s177( s79, pos, s79[pos], str, s155 );
s203 = s143;}
else if ( s79[pos] == L'[' ) {
s183( (s1034*)s1193, s79, pos, s166 ); 
s203 = s139;}
else {
s203 = s1725( s79, pos, s167 );
if( s203 != s136 )
(void)0;
else if( s188( s79, pos, b ) )
s203 = s141;
else if( s189( s79, pos ) )
s203 = s142;
else {
s181( s79, pos, str );
s203 = s138;}}}
s1194.second = pf ? pos - 1 + pf->s1039() : 0;}
bool s145::s1110( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1194.first || s1193.s13() )
return false;
f = s1193->Path();
s1193->s1105( s, s1194.first, s1194.second, line );
return true;}
void s147::s158( const wstring& s79, bool s155/*=s155*/ )
{
s148.clear();
size_t s70;
size_t pl = s79.find_first_not_of( L" \n\r\t" );
if( pl == string::npos )
return;
if( s79[pl] == L'{' )
s70 = s79.find_first_not_of( L" \n\r\t", pl + 1 );
else
s70 = pl;
while( true ) {
wstring s78;
s185( s79, s70, s78, s155 );
size_t pl = s79.find_first_not_of( L" \n\r\t", s70 );
if( pl == string::npos || s79[pl] != L':' )
throw new s17( L"unrecognized nqj syntax: " + s79.substr(s70, 50), 
(uint32_t)s17::s18::s21 );
s70 = pl + 1;
s148.insert( make_pair( s78, new s145( src, s79, s70, s155 ) ) );
pl = s79.find_first_not_of( L" \n\r\t", s70 );
if( pl != string::npos && s191.find( s79[pl] ) == string::npos ) 
throw new s17( L"wrong nqj syntax: missed separator or closing brace: " + s79.substr(s70, 50), 
(uint32_t)s17::s18::s21 );
if( pl != string::npos )
pl = s79.find_first_not_of( L" \n\r\t", pl+1 );
if( pl == string::npos )
break;
s70 = pl;}}
bool s147::operator==( const s147& r )  const{
bool s718 = true;
for( auto it = s148.begin(); it != s148.end(); ++it ) {
auto it1 = r.s148.find( it->first );
if( it1 == r.s148.end() || !( *( it->second ) == *( it->second ) ) ) {
s718 = false;
break;}}
return s718;}
void s147::s159( wostream* pd, bool s155 ) const{
*pd << L"{\n";
for( auto it = s148.begin(); it != s148.end(); ++it ) {
if( it != s148.begin() )
*pd << L",\n";
s186( pd, it->first, s155 );
*pd << L" : ";
it->second->s159( pd );}
*pd << L"\n}";}
void s145::s159( wostream* pd, bool s155 ) const{
if( s203 == s137 )
obj.s159( pd, s155 );
else if( s203 == s139 )
s184( pd, s166, s155 );
else if( s203 == s138 )
s186( pd, str, s155 );
else if( s203 == s143 )
s186( pd, str, true );
else if( s203 == s140 )
*pd << to_wstring( s167 );
else if( s203 == s144 )
*pd << to_wstring( (int)s167 );
else if( s203 == s141 )
*pd << ( b ? L"true" : L"false" );
else if( s203 == s142 )
*pd << L"null" << endl;
else
throw new s17( L"unknown variant" );}
bool s147::s160( const wstring& s156 ) const{
if( s148.find( s156 ) != s148.end() )
return true;
return false;}
void s147::s161( const wstring& s156, vector<s9<s145>>& s157 ) const{
auto i = s148.equal_range( s156 );
if( i.first == i.second )
return;
for( auto it = i.first; it != i.second; ++it )
s157.push_back( it->second );}
const s146 s147::s162( const wstring& s156 ) const{
if( s148.count( s156 ) > 1 )
throw new s17( L"multiple values: " + s156, (uint32_t)s153 );
auto s718 = s148.find( s156 );
return s718->second;}
void s147::s163( const std::wstring& s78, s146 s364, s149 ap ){
if( s148.find( s78 ) != s148.end() ) {
if( ap == s150 )
throw new s17( L"Field already exists: " + s78, (uint32_t)s17::s18::s22 );
else if( ap == s152 )
return;
else if( ap == s151 )
s148.erase( s78 );}
s148.insert( make_pair( s78, s364 ) );}
void s147::s164( vector<pair<wstring, s9<s145>>>& s157 ) const{
for( auto it = s148.begin(); it != s148.end(); ++it ) 
s157.push_back( *it );}
void s147::s165( wostream* pd, int s202 ) const{
for( auto it = s148.begin(); it != s148.end(); ++it ) {
*pd << FILL(s202) << it->first << " : " << endl;
it->second->s165( pd, s202 + 2 );}}
void s145::s165( wostream* pd, int s202 ) const{
if( s203 == s137 )
obj.s165( pd, s202 + 2 );
else if( s203 == s139 ) {
for( size_t n = 0; n < s166.size(); ++n ) {
s166[n]->s165( pd, s202 );
if( n < s166.size() - 1 )
*pd << endl;}}
else if( s203 == s138 )
*pd << FILL( s202 ) << str << endl;
else if( s203 == s140 )
*pd << FILL( s202 ) << s167 << endl;
else if( s203 == s144 )
*pd << FILL( s202 ) << s167 << endl;
else if( s203 == s141 )
*pd << FILL( s202 ) << b << endl;
else if( s203 == s142 )
*pd << FILL( s202 ) << L"null" << endl;
else
throw new s17( L"unknown variant" );}
bool operator==( const std::vector<s9<s145>>& l,
const std::vector<s9<s145>>& r ){
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
s1016 NCTraitNumAlias0		= 0x80000000;
s1016 s1567        = NCTraitNumAlias0 - 1;
s1016 s1568       = NCTraitNumAlias0 - 2;
s1016 s1569       = NCTraitNumAlias0 - 3;
s1016 s1566      = NCTraitNumAlias0 - 4;
s1016 s1565						= NCTraitNumAlias0 - 8;
s1016 s1570    = NCTraitNumAlias0 - 9;
s1016 s1571					= NCTraitNumAlias0 - 10;
DEFCONST s436 = L"typeMembers";
DEFCONST s437 = L"typeMember";
DEFCONST s438 = L"typeMethods";
DEFCONST s439 = L"typeMethod";
DEFCONST s440 = L"members";
DEFCONST s441 = L"member";
DEFCONST s442 = L"methods";
DEFCONST s443 = L"method";
DEFCONST s444 = L"@init";
DEFCONST s445 = L"initCall";
DEFCONST s1080 = L"@str";
DEFCONST s446 = L"thisPtr";
DEFCONST s447 = L"virtual";
DEFCONST s448 = L"override";
DEFCONST s898 = L"return";
DEFCONST s449 = L"continue";
DEFCONST s450 = L"break";
DEFCONST s451 = L"throw";
DEFCONST s812 = L"else";
DEFCONST s793 = L"elsif";
DEFCONST s847 = L"to";
DEFCONST s452 = L"true";
DEFCONST s453 = L"false";
DEFCONST s897 = L"null";
DEFCONST s1029 = L"->";
DEFCONST s1264 = L"const";
DEFCONST s1525 = L"new";
DEFCONST s1563 = L"stdin";
DEFCONST s1564 = L"stdout";
DEFCONSTI s941 = -1;
DEFCONSTI s456 = -2;
DEFCONSTI s454 = -100;
DEFCONSTI s455 = -101;
DEFCONSTI s457 = 1;
DEFCONSTI s458 = 0;
DEFCONSTI s943 = 0x80000000;
DEFCONSTI s942 = 0;
DEFCONSTI s1343 = 1;
DEFCONST s1585 = L":Number";
DEFCONST s1699 = L":Integer";
DEFCONST s1583 = L":IterableForw";
DEFCONST s1582 = L":IterableBidir";
DEFCONST s1584 = L":IterableRand";
DEFCONST s1581 = L":IStream";
DEFCONST s1586 = L":OStream";
DEFCONST s1580 = L":IOStream";
DEFCONST s459 = L"import";
DEFCONST s460 = L"input";
DEFCONST s461 = L"output";
DEFCONST s462 = L"export";
DEFCONST s463 = L"opaque";
DEFCONST s464 = L"public";
DEFCONST s465 = L"private";
DEFCONST s466 = L"secure";
DEFCONST s467 = L"class";
DEFCONST s468 = L"module";
DEFCONST s469 = L"AssemblyDescription";
DEFCONST s470 = L"ProgramText";
DEFCONST s471 = L"Export";
DEFCONST s472 = L"Require";
DEFCONST s473 = L".td";
DEFCONST s1035 = L".tsd";
DEFCONST s475 = L"MainModule";
DEFCONST s474 = L"_start";
DEFCONST s476 = L"asm" + s473;
DEFCONST s477 = L"@ex";
DEFCONST s1545 = L"@it";
DEFCONST s478 = L"@idx";
DEFCONST s816 = L"@pars";
DEFCONST s855 = L"@obj";
DEFCONST s890 = L"@num_args";
DEFCONST s1242 = L"@sourceFile";
DEFCONST s1544 = L"@OS_Type";
DEFCONST s483 = L"source";
DEFCONST s479 = L"objectType";
DEFCONST s480 = L"moduleType";
DEFCONST s481 = L"name";
DEFCONST s482 = L"entryPoint";
DEFCONST s484 = L"perm";
DEFCONST s486 = L"extends";
DEFCONST s780 = L"packages";
DEFCONST s488 = L"searchDirs";
DEFCONST s1024 = L"@attrs";
DEFCONST s1003 = L"is";
DEFCONST s1002 = L"index type";
DEFCONST s1004 = L"value type";
DEFCONST s434 = L"#lang transd";
DEFCONST s1224 = L"#format tsd";
s1016 s1459						= 103;
s1016 s1536					= 104;
s1016 s1011						= 110;
s1016 s1458				=	123;
s1016 s1012 			=	124;
s1016 s1247						= 125;
s1016 s1006			= 201;
s1016 s1225				= 204;
s1016 s1007					= 210;
s1016 s1226					= 304;
s1016 s1227				= 404;
s1016 s1228				= 504;
s1016 s1008					= 510;
s1016 s1009			= 511;
s1016 s1010					= 610;
s1016 s1244							= 710;
s1016 s1245					= 711;
s1016 s1537		= 804;
s1016 s1538				= 904;
s1016 s1539				= 1004;
s1016 s1246					= 1124;
s1016 s1457				= 1224;
s1016 CLHashIndexVal_ctor1		= 1304;
s1016 CLTDFor_ctor1						= 1404;
s1016 s1549						= 1410;
s1016 CLTDAny_ctor1						= 1504;
s1016 s1547						= 1510;
s1016 s1548					= 1511;
s1016 CLTransdFT_ctor1				= 1604;
s1016 s1697					= 1610;
s1016 s1698			= 1611;
s1016 CLTransductor_init			= 1710;
set<wstring> s1241 = { s1242, s1563, s1564, s1544 };
} // namespace s7
std::wstring s235[] = { L"value", L"function", L"object", L"name" };
const wstring s236 = L"if";
const wstring s237 = L"set";
const wstring s238 = L"sum";
const wstring s239 = L"with";
const wstring s240 = L"mul";
const wstring s241 = L"div";
const wstring s242 = L"dif";
const wstring s243 = L"eq";
const wstring s244 = L"less";
const wstring s245 = L"greater";
const wstring s246 = L"leq";
const wstring s247 = L"geq";
const wstring s248 = L"neq";
const wstring s249 = L"and";
const wstring s250 = L"or";
const wstring s251 = L"dcmp";
const wstring s252 = L"dcmpr";
const wstring s253 = L"mod";
const wstring s254 = L"sqrt";
const wstring s255 = L"abs";
const wstring s256 = L"pow";
const wstring s257 = L"textout";
const wstring s258 = L"lambda";
const wstring s259 = L"proc";
const wstring s261 = L"while";
const wstring s262 = L"eval";
const wstring s263 = L"try";
const wstring s264 = L"catch";
const wstring s265 = L"throw";
const wstring s260 = L"through";
const wstring s266 = L"for";
const wstring s268 = L"run-file";
const wstring s819 = L"load-file";
const wstring s879 = L"import-module";
const wstring s1484 = L"unload-module";
const wstring s796 = L"has-field";
const wstring s875 = L"tsd-query";
const wstring s805 = L"substr";
const wstring s925 = L"ret";
const wstring s926 = L"sort";
const wstring s988 = L"exit";
const wstring s1483 = L"to-file";
const wstring s1603 = L"any";
const wstring s1602 = L"all";
const std::wstring s272 = L"AttrNA";
s270::s270( const std::wstring& s, const s145* s6 )
: s1162( (s145*)s6 ){
s1102( s );}
s270::s270( const std::wstring& s709, const s6::s145& s303 )
: s285( s709 ), s1162( (s145*)&s303 ){
if( s303.s168() == s138 ) {
wstring s = s303.s173();
s1102( s );}
else if( s303.s168() == s143 ) {
wstring s = //L"\"" +
s303.s173();// +
s291( s );}
else if( s303.s168() == s137 ) {
basic_stringstream<wchar_t> ss;
s303.s159( &ss, true );
if( s285.find( s771->s369() ) == 0 ) {
s291( ss.str() );
s285 = s4::s54( s285.substr( s771->s369().size() ), s50 );}
else {
src = ss.str();
s290( s303.s170() );}}
else if( s303.s168() == s140 )
s291( to_wstring( s303.s172() ) );
else if( s303.s168() == s144 )
s291( to_wstring( s303.s58() ) );
else if( s303.s168() == s141 )
s291( /*to_wstring( s303.s768() )*/ s303.s768() ? L"true" : L"false");
else if( s303.s168() == s139 ) {
basic_stringstream<wchar_t> ss;
s303.s159( &ss );
if( s285.find( L"UVector" ) == 0 ) {
s291( L"UVector" + ss.str() );
s285 = s4::s54( s285.substr( 7 ), s50 );}
else
s291( ss.str() );}
else
throw new s17( L"Unhandled nqj variant: " + to_wstring( s303.s168() ) );}
s270::s270( const s6::s147& s137 ){
s290( s137 );}
s270::~s270(){
reset();}
void s270::reset(){
s288.clear();
s273.clear();
s284 = s285 = s287 = src = L"";}
void s270::s1102( const wstring& s ){
size_t pos = 0;
wstring s1328 = L"\"'-+[<";
if( s[pos] == L'(' )
s289( s );
else if( iswalpha( s[pos] ) || s[pos] == L'_' || s[pos] == L'@' || s[pos] == L':' ) {
if( s.find( L'(' ) != string::npos )
s291( s );
else
s292( s );}
else if( iswdigit( s[pos] ) || s1328.find( s[pos] ) != string::npos ) {
wstring s79;
s79 = s54( s, s50 );
s291( s79 );}
else
throw new s17( L"Unknown string content: " + s );}
void s270::s289( const std::wstring& s79 ){
src = s79;
size_t pos = 0;
vector<wstring> s710;
s295( s79, pos, s710 );
if( s710.empty() )
return;
s286 = s232;
size_t s70 = 0;
s287 = s294( s710[0], s70 );
for( size_t n = 1; n < s710.size(); n++ )
s288.insert( make_pair( to_wstring( n - 1 ), new s270( s710[n], s1162 ) ) );}
void s270::s291( const std::wstring& s79 ){
src = s79;
s286 = s231;
s287 = s79;}
void s270::s292( const std::wstring& s79 ){
src = s79;
s286 = s234;
s287 = s79;}
void s270::s290( const s6::s147& s137 ){
s285 = s309( s137, s7::s481 );
s286 = s233;
vector<pair<wstring, s146>> s148;
s137.s164( s148 );
for( size_t n = 0; n < s148.size(); ++n ) {
if( s148[n].first != s7::s481 )
s293( s148[n].first, *s148[n].second );}}
void s711( wstring& s ){
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
void s270::s296( s6::s147& obj ){
wstring s712 = s4::s54( s309( obj, s7::s481 ), s50 );
wstring s688 = s712;
s711( s688 );
if( s688.empty() )
throw new s17( L"Nameless blocks are forbidden." );
if( s688 != s712 )
obj.s163( s7::s481, s146(new s145( s688 )), s147::s151 );
if( s688 == s285 ) { // partial definition
vector<pair<wstring, s146>> s148;
obj.s164( s148 );
for( size_t n = 0; n < s148.size(); ++n )
s293( s148[n].first, *s148[n].second );}
else {
s288.insert( make_pair( s688, new s270( obj ) ) );}}
void s270::s293( s270* node ){
s288.insert( make_pair( node->s306(), node ) );}
void s270::s293( const std::wstring& s285, const s145& s364 ){
s288.insert( make_pair( s285, new s270( s285, s364 ) ) );}
void s270::s297( s269* s307, size_t s308 /*= 0*/ )
{
s282::iterator it = s288.begin();
for( ; it != s288.end(); ++it ) {
if( it->second->s304() == s233 ) {
if( s308 == 0 ) {
it->second->s297( s307, 1 );}
else {}}}}
const s270* s270::s299( const std::wstring& s285 ) const{
size_t s717 = s288.count( s285 );
if( s717 > 1 )
throw new s17( L"multiple values: " + s285, (uint32_t)s153 );
if( s717 == 1 ) {
auto s718 = s288.find( s285 );
return s718->second.s16<s270*>();}
throw new s17( L"node not found: " + s285, (uint32_t)s17::s18::s24 );
s282::const_iterator it = s288.begin();
for( ; it != s288.end(); ++it ) {
try {
const s270* s718 = it->second->s299( s285 );
return s718;}
catch( s17* e ) {
if( e->which() == (uint32_t)s17::s18::s24 )
continue;
throw e;}}
throw new s17( L"node not found: " + s285, (uint32_t)s17::s18::s24 );}
void s270::s295( const wstring& s79, size_t& pos, vector<wstring>& s157 ){
size_t s76, s77;
s56( s79, pos, L'(', L')', s76, s77, true );
if( s76 != pos || s77 == string::npos )
throw new s17( L"Parentheses don't match near \"" + 
s79.substr( 0, 40 ) + L"...\"" );
pos = s77;
size_t s70 = s79.find_first_not_of( s50, s76 + 1 );
if( s79[s70] == L')' )
return;
size_t s716 = s70;
wstring s713;
while( s716 < s77 ) {
s70 = s79.find_first_not_of( s50 + L")", s716 );
if( s70 >= s77 )
break;
size_t s714, s715;
if( s79[s70] == L'(' ) {
s56( s79, s70, L'(', L')', s714, s715, true );
if( s715 == s77 )
throw new s17( L"Parentheses don't match near \'" + s79.substr( s70, 40 ) + L"...\'" );
s713 = s79.substr( s70, s715 - s70 + 1 );
s716 = s715 + 1;}
else if( s79[s70] == L'[' ) {
s56( s79, s70, L'[', L']', s714, s715, true );
if( s715 == s77 )
throw new s17( L"Brackets don't match near \'" + s79.substr( s70, 40 ) + L"...\'" );
s713 = s79.substr( s70, s715 - s70 + 1 );
s716 = s715 + 1;}
else if( s79[s70] == L'"' ) {
s57( s79, s70, L'"',
s714, s715 );
if( s715 == string::npos )
throw new s17( L"Quotes don't match near \'" + s79.substr( s70, 40 ) + L"...\'" );
s713 = s79.substr( s70, s715 - s70 + 1 );
s716 = s715 + 1;}
else if( iswdigit( s79[s70] ) ) {
s715 = s79.find_first_of( s50 + L")", s70 );
s713 = s79.substr( s70, s715 - s70 );
s716 = s715;}
else if( iswalpha( s79[s70] ) || s79[s70] == L'_' ) {
s715 = s79.find_first_of( s50 + L")", s70 );
size_t pl = s79.find( L'(', s70 );
if( pl < s715 ) {
s56( s79, pl, L'(', L')', s714, s715, true );
if( s715 == s77 )
throw new s17( L"Parentheses don't match near \'" + s79.substr( s70, 40 ) + L"...\'" );
s713 = s79.substr( s70, s715 - s70 + 1 );
s716 = s715 + 1;}
else {
s713 = s79.substr( s70, s715 - s70 );
s716 = s715;}}
else {
s715 = s79.find_first_of( s50 + L")", s70 );
s713 = s79.substr( s70, s715 - s70 );
s716 = s715;}
s157.push_back( s713 );}}
wstring s270::s294( const std::wstring& s79, size_t &pos ){
wstring s718;
if( s79[pos] == L'+' && s79[pos + 1] != L'=' )
s718 = s238;
else if( s79[pos] == L'-' && s79[pos + 1] != L'=' )
s718 = s242;
else if( s79[pos] == L'*' && s79[pos + 1] != L'=' )
s718 = s240;
else if( s79[pos] == L'/' && s79[pos + 1] != L'=' )
s718 = s241;
else if( s79[pos] == L'^' && s79[pos + 1] != L'=' )
s718 = s256;
else if( s79[pos] == L'=' && s79[pos + 1] != L'=' )
s718 = s237;
else if( s79[pos] == L'<' && s79[pos + 1] != L'=' )
s718 = s244;
else if( s79[pos] == L'>' && s79[pos + 1] != L'=' )
s718 = s245;
else if( s79[pos] == 955 /*L'λ'*/ )
s718 = s258;
if( s718.size() ) {
if( s79.size() > pos + 1 && s79.find_first_of( s50 + L")", pos ) != pos + 1 )
throw new s17( L"1: unknown syntax: " + s79.substr(pos, 40),
(uint32_t)s17::s18::s21 );
pos += 1;
return s718;}
if( s79.substr( pos, 2 ) == L"+=" )
s718 = L"sumeq";
else if( s79.substr( pos, 2 ) == L"-=" )
s718 = L"difeq";
else if( s79.substr( pos, 2 ) == L"*=" )
s718 = L"muleq";
else if( s79.substr( pos, 2 ) == L"/=" )
s718 = L"diveq";
else if( s79.substr( pos, 2 ) == L"^=" )
s718 = L"poweq";
else if( s79.substr( pos, 2 ) == L"<=" )
s718 = L"leq";
else if( s79.substr( pos, 2 ) == L">=" )
s718 = L"geq";
else if( s79.substr( pos, 2 ) == L"==" )
s718 = L"eq";
else if( s79.substr( pos, 2 ) == L"!=" )
s718 = L"neq";
if( s718.size() ) {
if( s79.size() > pos + 2 && s79.find_first_of( s50 + L")", pos ) != pos + 2 )
throw new s17( L"2: unknown syntax: " + s79.substr( pos, 40 ), 
(uint32_t)s17::s18::s21 );
pos += 2;
return s718;}
size_t s716 = s79.find_first_of( s50 + L")", pos );
s718 = s79.substr( pos, s716 - pos );
pos = s716;
return s718;}
std::wstring s270::s305() const{
return (s284.size() ? s284 + L"::" : L"") + s285;}
wstring s270::s302( const s6::s147& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s160( s7::s480 ) )
return obj.s162( s7::s480 )->s173();
return def;}
std::wstring s270::s309( const s6::s147& obj,
const std::wstring& s310,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s160( s310 ) )
return obj.s162( s310 )->s173();
return def;}
const std::wstring& s270::s275( const std::wstring& s310 ) const{
auto it = s273.find( s310 );
if( it != s273.end() )
return it->second;
return s272;}
void s270::s276( const std::wstring& s310, const std::wstring& s274 ){
s273[s310] = s274;}
void s270::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s285 << L" : " << s235[s286] << endl;
buf << s4::fill_n_ch( L' ', s202 ) << L" " << s287 << endl;
map<wstring, s1036>::const_iterator it = s288.begin();
for( ; it != s288.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << it->first << endl;
it->second->s311( pd, s202 + s435 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1223 s1116;
void s1223::s1066( const std::wstring& s80 ){
++s1096;
s27.push_back( Msg( s80 ) );
wcout << s80;}
void s1223::s1066( const std::wstring& s80, const std::string& func, 
const std::string& file, uint32_t line ){
++s1096;
s27.push_back( Msg( s80, U16(func), U16(file), line, s1150 ) );}
void s1223::s1068( const std::wstring& s80, const std::string& func, 
const std::string& file, uint32_t line ){
s27.push_back( Msg( s80, U16(func), U16(file), line, s1153 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1197 = {
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
TDException::TDException( uint32_t s1118, uint32_t cat, const s270* ast_ )
: s17( L"", s1118 ), stage (Stage::s1139 ), category( cat ), s737( ast_ ){}
TDException::TDException( Stage stg, uint32_t s1118, uint32_t cat, const s270* ast_, const s17& e )
: s17( e ), stage ( stg ), category( cat ), s737( ast_ ){
if( category ) {
s31( s1093[category] + L":" );}}
TDException::TDException( uint32_t s1118, uint32_t cat, const s270* ast_, const std::wstring& s80 )
: s17( s80, s1118 ), stage (Stage::s1139 ), category( cat ), s737( ast_ ){
if( category ) {
s31( s1093[category] + L":" );}}
TDException::TDException( const TDException& e )
: s17( e ), stage( e.stage ), category( e.category ), s1204( e.s1204 ), s737( e.s737 ){}
TDException* TDException::s1099( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s202 ) const{
size_t s1141 = 0;
wstring file, s1195, src;
if( s737 ) {
if( s737->Nqj() && s737->Nqj()->s1110( file, s1195, s1141 ) ) {
wstring s1191 = std::to_wstring( s1141 ) + L": '" + s1195 + L"'";
src = L"\n  in file: " + file + L"\n  on line " + s1191;}
if( !s737->s298().empty() )
src += L"\n  object: '" + s737->s298() + L"', ";
if( !s737->Src().empty() )
src += L"code: '" + s737->Src() + L"', ";}
wstring s = L"Error ";
if( id ) {
wstring s1189;
if( (uint32_t)stage )
s1189 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1189 += std::to_wstring( id );
s += s1189;}
if( (uint32_t)stage ) {
s += L" during " + s1197[(uint32_t)stage];}
s += src + L"\n";
return wstring( s202, L' ' ) + s + s17::Msg( s202 + 2 );}
s1015::s1015( s17& e, const s270& s737, s18 code )
: s17( e ){
id = (uint32_t) code;
size_t s1141 = 0;
wstring file, s1195, src;
wstring	s80 = L"Error during ";
if( s737.Nqj()->s1110( file, s1195, s1141 ) ) {
src = std::to_wstring( s1141 ) + L": '" + s1195 + L"'";
s80 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s80 += L"object: '" + s737.s298() + L"'; code: " + s737.Src();}
s31( s80 );
s1116.s1066( Msg( 2 ) );}
s1023::s1023( s18 code )
: s17( L"" ){
id = (uint32_t) code;}
vector<wstring> s1093 = {
L"error",
L"incorrect call of object constructor",
L"incorrect call of builtin function",
L"incorrectly formed TSD query",
L"TSD query failed",
L"symbol is not resolved",
L"incorrect call of builtin type object's method",
L"the call of a builtin type object's method failed",
L"error during execution of built-in function",
L"error during object initialization"
};
namespace lang {
bool s686( const wstring& s, bool s751 ){
bool s750 = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1241.find( s ) != s7::s1241.end() )
continue;
s750 = true;
break;}
if( s750 && s751 )
throw new s17( L"illegal identifier: " + s );
return (!s750);}
} // namespace tdlang
s1014 s1092;
s278::~s278(){}
s502* s278::s516()
{	throw std::logic_error( "1: not implemented" );}
const s502* s278::s524() const
{	throw std::logic_error( "2: not implemented" );}
s505 s278::s517( s502** s281, size_t s518 )
{	throw std::logic_error( "3: not implemented" ); }
s278* s278::s350() const
{	throw std::logic_error( "4: not implemented" ); }
void s278::s520( s502* s612 ) {
(void)0;}
inline bool
s278::s522( const s502* s523 ) const{
return ( s523->s367() == s367() );}
inline bool
s278::s1716( s1172 s647 ) const{
return s307->TR().s1709( s367(), s647 );}
const s869& 
s278::s1340() const {
return s307->TR().s1114( s513 ); }
s278::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s278::operator int() const { throw std::logic_error( "6: not implemented" ); }
s278::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s278::to_wstring() const { throw std::logic_error( "8: not implemented" ); }
s1489 s278::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s278::s1501( const s270& ast_, s269* s307, s502* obj,
const wstring& s347, vector<s278*>& s157 ){
size_t pos = 0;
vector<wstring> s710;
wstring s79 = ast_.s298();
if( s79.empty() )
return;
/*wstring s = s79;
if( s[0] != L'(' )
s = L"(" + s + L")";*/
s270::s295( s79.substr( s79.find( L"(" ) ), pos, s710 );
if( s710.empty() )
return;
for( size_t n = 0; n < s710.size(); n++ ) {
s270* ast1 = new s270( s710[n], ast_.Nqj() );
s157.push_back(
s278::s525( *ast1, s307, obj, s347 )
);}}
s278* s278::s525( const s270& s737, s269* s307, s502* obj,
const wstring& s347 ){
s278* p;
if( s737.s304() == s231 ) {
wstring s364 = s737.s298();
bool quot = s90.find( s364[0] ) != string::npos;
size_t ppl = s364.find( L"(" );
bool lastp = s364.back() == L')';
wstring ownerName = s737.s275( L"ownerName" );
if( ( s737.s275( L"ownerType" ) == L"CallSite" ) &&
( ownerName != s258 ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s362 = s364.substr( 0, ppl );
wstring s79 = L"(new<" + s362 + L"> " + s364.substr( ppl + 1 );
s1036 tast = new s270( s79, s737.Nqj() );
p = s616::s1237( *tast, s307, obj, s347 );}
else {
p = s307->TR().s542( s737, obj, s347 );
((s502*)p)->s527( s737.s306() );}}
else if( s737.s304() == s232 )
p = s616::s1237( s737, s307, obj, s347 );
else if( s737.s304() == s234 )
p = new s387( s737.s298(), s307 );
else //if( s737.s304() == s233 )
throw new s17( L"unexpected node type" );
return p;}
s278* 
s278::s1122( s269* s307, s278* par, s502* s613, s616* s220,
const std::wstring& s347 ){
s278* s718;
if( par->s514() == s496 ) {
s509 cs = new s585( *((s585*)par) );
s718 = s616::s625( cs, s307, s613, s220, s347 );
((Transd*)s718)->s520( s347, false );}
else {
par->s520( /*s613*/s220 );
return par;}
return s718;}
s504
s278::s1121( const wstring& s79, const s270* ast_, s269* s307, s502* s613 ){
s1036 ast1 = new s270( s79, ast_->Nqj() );
s504 pr = s278::s525( *ast1, s307, s613, s613->s305() );
if( pr->s514() == s493 ) {
pr->s520( s613 );
pr = pr.s16<s387*>()->s393();}
s504 s718 = s278::s1122( s307, pr, s613, NULL, s613->s305() );
return s718;}
const wstring& 
s278::s369() const{
return s307->TR().s856( s367() );}
void s278::s366( s869::s778 type ){
s513 = type;}
s503* s1238( s526& m, const wstring& s156 ){
if( m.count( s156 ) > 1 )
throw new s17( L"multiple values: " + s156, (uint32_t)s17::s18::s22 );
auto s718 = m.find( s156 );
if( s718 == m.end() )
throw new s17( L"no such key: " + s156, (uint32_t)s17::s18::s24 );
return s718->second;}
void s702( const std::wstring& s, std::wstring& s1230, std::wstring& s626 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s17( L"unknown format of qualified name: " + s, (uint32_t)s17::s18::s21 );
s1230 = s.substr( 0, pl );
s626 = s.substr( pl + 2 );}
s502* s502::s516(){
return this;}
s502* s502::s1711( const s502* p ) const{
if( s367() == p->s367() )
return (s502*)p->s350();
throw new s17( L"no conversion from '" + s369() + L"' to '" + p->s369() + L"'" );}
s502* s502::s371( s502* s613, const std::vector<s1172>& vt ) const{
assert(0);
return 0;}
s1172 s502::s1332( const wstring& s1728, const vector<s504>& l ) const{
throw std::logic_error( "9: not implemented" );}
vector<wstring> s545::s549 = { s7::s462, s7::s460,
s7::s463, s7::s461 };
s1::s9<s550> s581 = new s550();
size_t s1060( const vector<s869::s980>& vt ){
size_t s718 = 0;
for( auto i : vt )
s718 = ( s718 << 7 ) ^ i;
return s718;}
size_t s510::s1165( const wstring& s, size_t& pos, s869::Cont& s157 ){
size_t s70 = pos;
size_t s718 = 0;
if( s[s70] == L' ' )
s70 = s.find_first_not_of( s4::s50, s70 );
while( s70 < s.size() && s[s70] != L'>' && s[s70] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s70 );
wstring stype = s4::s54( s.substr( s70, pl - s70 ), s4::s50 );
s1172 s1208 = get( stype /*+ L"()"*/ )->s367();
s157.push_back( s1208 );
pl = s.find_first_not_of( s4::s50, pl );
s869::Cont s1180;
size_t s1163 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1163 = s1165( s, ++pl, s1180 );}
else if( s[pl] == L',' ) {
s1163 = 0;}}
s157.push_back( ( s869::s980 ) s1163 );
s157.insert( end( s157 ), begin( s1180 ), end( s1180 ) );
s718++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s50, pl );
pos = s70 = pl;}
return s718;}
wstring s1297( const s869::Cont& s1175, size_t& idx, s510& s998 ){
wstring s718 = s998.s856(s1175[idx++]);
size_t n = (size_t)s1175[idx++];
if( n && s718.back() != L'>' ) {
s718 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s718 += ( k ? L" " : L"" ) + s1297( s1175, idx, s998 );}
s718 += L">";}
return s718;}
wstring s510::s1113( const s869::Cont& s1175 ){
assert( s1175.size() );
if( s1175.size() == 1 )
return  s1214[s1175[0]] + L"< 0 >";
size_t idx = 0;
wstring s718;
while( idx < s1175.size() ) {
s718 += s1297( s1175, idx, *this );
if( idx < s1175.size() )
s718 += L" ";}
return s718;}
wstring s510::s1521( const wstring& tn ){
wstring sv = tn;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
return sv;}
void s510::s1109( const s869::Cont& v, size_t& idx, s869::Cont& s157 ){
s157.push_back( v[idx++] );
size_t n = v[idx++];
s157.push_back( (s1172)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s1109( v, idx, s157 );}}
s869::s869( s778 t1, s778 t2/*=(s778)-1*/, s778 t3/*=(s778)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s778)-1 ) {
vt.push_back( t2 );
if( t3 != (s778)-1 )
vt.push_back( t3 );}
s1212 = s1060( vt );}
s869::s869( const s869& right )
: s1212( right.s1212 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s869::s869( const Cont& v ) 
: vt( v ) {
s1212 = s1060( vt );}
s869::s980 s869::s367( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s869::s366( s778 t ){
vt.clear();
vt.push_back( t );}
void s869::s366( s1013 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s869::s836( s778 t ){
vt.push_back( t );}
void s869::s836( s1013 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s869::s877( std::vector<s278*>& s157 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s157.push_back( new s361( NULL, (int)vt[n] ) );}
inline bool s869::operator==( const s869& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s778* pvt1 = (s778*)&vt[0];
s778* pvt2 = (s778*)&p.vt[0];
for( size_t s717 = 0; s717 < sz1; ++s717 )
if( pvt1[s717] != pvt2[s717] )
return false;
return true;}
s510::s510( s269* pass_ ) 
: s307( pass_ ) {
reset();}
void s510::s297(){
s1726.clear();
s1726.resize( s1231.size() );
for( auto type : s1231 )
if( type ) type->s365();}
void s510::s540( const s501& st ){}
void s510::reset() {
s1231.clear(); 
s1214.clear();
s1219.clear();
s1215.clear();
s1220.clear();
s1005.clear();
s979.clear();
s1411.clear();
s1429.clear();
s1231.push_back( NULL ); 
s1214.push_back( L"" );
s1219.push_back( 0 );
s979[L":Data"] = 1;
s1411[1] = L":Data";
s1351 = 1;
s1429.push_back( 0 );
srand( (unsigned int)time(NULL) );}
void s510::s224( s502* p, const std::wstring& s362 ){
if( s1215.find( s362 ) != s1215.end() )
throw new s17( (uint32_t)s17::s18::s22 );
s1214.push_back( s362 );
s1231.push_back( p );
s1172 s1208 = (s1172)s1214.size() - 1;
s1219.push_back( s869( s1208 ) );
p->s366( s1208 );
s1215[s362] = s1208;
s1220[s1219.back()] = s1208;
s1429.push_back( 1 );}
s1172 s510::s1179( const s869::Cont& v, const std::wstring& s362 ){
s869 vt( v );
if( s1220.find( vt ) != s1220.end() )
throw new s17( (uint32_t)s17::s18::s22 );
s1214.push_back( s362 );
s1219.push_back( vt );
s1172 s1208 = (s1172)s1214.size() - 1;
s1215[s362] = s1208;
s1220[s1219.back()] = s1208;
s1220[s869( s1208 )] = s1208;
s1231.push_back( s1231[vt.s367( 0 )]->s371( s307, v )	);
s1429.push_back( s1429[vt.s367( 0 )] );
return s1208;}
s1172 s510::s1155( const s869::Cont& v_ ){
assert( all_of( begin( v_ ), end( v_ ), [this]( s1172 t ) { return ( t && t <= s1219.size() ); } ) );
s869::Cont v( { v_[0], (s1172)v_.size() - 1 });
for( size_t n = 1; n < v_.size(); ++n ) {
v.push_back( v_[n] );
v.push_back( 0 );}
s869 vt( v );
s1172 s718 = 0;
auto it = s1220.find( vt );
if( it == s1220.end() ) {
wstring s1206 = s1113( v );
s718 = s1179( v, s1206 );}
else
s718 = it->second;
return s718;}
uint32_t s1337( uint32_t n ){
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
traitnum_t s510::s1404( const std::wstring& trait, s1172& s1685 ){
auto it = s979.find( trait );
if( it != end( s979 ) )
return it->second;
s1351 = s1337( s1351 );
s979[trait] = s1351;
s1411[s1351] = trait;
s1686.push_back( s1351 );
s1685 = s7::NCTraitNumAlias0 + (s1172)s1686.size();
return s1351;}
void s510::s1302( s869::s980 type, const wstring& trait, s1172& s1685 ){
traitnum_t tn;
auto it = s979.find( trait );
if( it == end( s979 ) )
tn = s1404( trait, s1685 );
else
tn = it->second;
s1429[type] *= tn;}
traitnum_t s510::s1633( s1172 alias ) const{
return s1686[alias - s7::NCTraitNumAlias0 - 1];}
bool s510::s1342( s1172 s647, traitnum_t tra ) {
double d = (double)s307->TR().s1295( s647 ) / tra;
return ( d == (int)d );}
bool s510::s1640( s1172 s647, s1172 alias ) {
double d = (double)s307->TR().s1295( s647 ) / 
s1686[alias-s7::NCTraitNumAlias0-1];
return ( d == (int)d );}
void s510::s1708( s1172 s647, s1172 is ){
s1726[s647].push_back( is );}
bool s510::s1709( s1172 s647, s1172 is ){
if( s647 == is )
return true;
if( s647 >= s1726.size() )
return false;
std::vector<s1172>& v = s1726[s647];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
void s510::s1313( const wstring& alias, const wstring& s362 ){
assert( s1215.find( alias ) == end( s1215 ) );
s1172 typid;
auto it = s1215.find( s362 );
if( it == s1215.end() ) {
s869::Cont vt;
size_t pos = 0;
s1165( s362, pos, vt );
for( size_t n = 1; n < vt.size(); n += 2 ) vt[n] = 0;
vt.erase( std::remove( begin( vt ), end( vt ), 0 ), end( vt ) );
typid = s1155( vt );}
else
typid = it->second;	
s1214.push_back( alias );
s1231.push_back( s1231[typid] );
s1219.push_back( s1219[typid] );
s1429.push_back( s1429[typid] );
s1215[alias] = typid;}
wstring s510::s1430( const wstring& tn_ ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1215.find( s );
if( it == end( s1215 ) )
return tn_;
const wstring& tn = s1214[s1220[s1219[it->second]]];
if( tn != s ) {
wstring s718 = tn_;
return s718.replace( 0, s.size(), tn );}
return tn_;}
s502* s510::s542( const s270& s737, s502* s613, const wstring& s543 ){
if( s737.s1476() )
return s1231[s737.s1476()]->s370( s737, s613, s543 );
wstring s364 = s737.s298();
if( s364.substr(0,2) == L"[[" )
return s1231[s1215[s1051->s369()]]->s370( s737, s613, s543 );
else if( s364[0] == L'[' )
return s1231[s1215[s765->s369()]]->s370( s737, s613, s543 );
else if( s364.find( L"UVector[" ) == 0 )
return s1231[s1215[s788->s369()]]->s370( s737, s613, s543 );
else if( s364[0] == L'{' )
return s1231[s1215[s771->s369()]]->s370( s737, s613, s543 );
else if( s364.find( L"typealias" ) == 0 ) {
size_t pl = s364.find( L"(" );
wstring s362 = s4::s54( s364.substr( pl + 1, s364.size() - pl - 2 ), s4::s50 );
s1313( s737.s306(), s362 );
return s1231[s1215[s843->s369()]]->s370( s737, s613, s543 );}
wstring s362 = L"";
s502* s718 = NULL;
if( s4::s90.find( s364[0] ) != string::npos )
s362 = s375( s307 ).s369();
else if( isdigit( s364[0] ) || s364[0] == L'-' )
return s351::s360( s307, s364, s543 );
else if( ( s718 = s1231[s1276]->s370( s737, s613, s543 ) ) )
return s718;
else {
size_t pl = s364.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s362 = s364.substr( 0, pl );}
else if( pl == string::npos )
s362 = s364;}
auto it = s1215.find( s362 );
if( it == s1215.end() ) {
auto it1 = s979.find( s362 );
if( it1 == end( s979 ) )
throw new s17( L"Type does not exist: " + s364, (uint32_t)s17::s18::s24 );
return new s400( s307, it1->second, s1397 );}
return s1231[it->second]->s370( s737, s613, s543 );}
s502* s510::s542( s1172 s355, s502* s613, const wstring& s543 ){
if( !s355 || s355 >= s1214.size() )
throw new s17( L"no type with such id: " + to_wstring( s355 ) );
s1172 type = s355;
if( s1219[type].s367() != type )
type = s1219[type].s367();
if( s1219[s355].s877().size() == 1 )
return s1231[type]->s371( s613 );
else {
return s1231[type]->s371( s613, s1219[s355].s877() );}}
const s502* s510::get( const wstring& s78, bool s544/*= true*/ ) const
{
wstring s362 = s78;
size_t pl = s78.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s78.find( L"0" ) == string::npos )
s362 = s78.substr( 0, pl );
auto s718 = s1215.find( s362 );
if( s718 == s1215.end() ) {
if( s544 )
throw new s17( L"1: symbol not found: " + s78 );
else
return NULL;}
return s1231[s718->second].s16<const s502*>();}
bool s510::s160( const std::wstring& s78 ) const{
if( s1215.find( s78 ) == s1215.end() )
return false;
return true;}
const wstring& s510::s856( s1172 n ) const{
if( n >= s1214.size() )
throw new s17( L"no type with such ordinal: " + std::to_wstring( n ) );
return s1214[n];}
s1172 s510::s1111( const std::wstring& s362, bool s544 ) const{
auto it = s1215.find( s362 );
if( it == s1215.end() ) {
if( s544 )
throw new s17( L"no such type: " + s362,
(uint32_t)s17::s18::s24 );
else
return 0;}
return it->second;}
s1172 s510::s1112( const s869& vt, bool s544 ) const{
auto it = s1220.find( vt );
if( it == end( s1220 ) ) {
if( s544 )
throw new s17( (uint32_t)s17::s18::s24 );
else
return 0;}
return it->second;}
const s869& s510::s1114( s1172 t ) const{
assert( t && t < s1219.size() );
return s1219[t];}
const s502* s510::s1108( s869::s980 t ) const{
assert( t && t < s1219.size() );
return s1231[t].s16<const s502*>();}
void s510::s841(){
size_t s790 = s351::s860() + 1;
for( size_t n = s790; n < s1214.size(); ++n ) {
s1215.erase( s1214[n] );
s1220.erase( s1219[n] );
s1005.erase( (s1172)n );}
s1214.erase( s1214.begin() + s790, s1214.end() );
s1231.erase( s1231.begin() + s790, s1231.end() );
s1219.erase( s1219.begin() + s790, s1219.end() );}
bool s510::s1401(){
return rand() % 2;}
double s510::s1403(){
return rand() / RAND_MAX;
}
int s510::s1409(){
return rand();}
void s510::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s202 ) << L"Types :" << endl;
for( size_t n = 0; n < s1214.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s202 + 5 ) << s1214[n] << endl;
s1231[n]->s311( pd, s202 + 10 );}}
s501::s501( const s501& right )
: s577( right.s577 ), s561( right.s561 ), s563( right.s563 ){}
void s501::s520( s502* s962, bool s539/*= true*/ )
{
for( auto sym : s577 ) {
if( sym.second->s514() != s494 ) {
try {
sym.second->s520( s962 );}
catch( TDException* e ) {
e->s1188( TDException::Stage::s1134 );
s1116.s1066( e->Msg( 0 ) );
continue;}}}
if( s1116.s1022() )
return;
if( s539 ) {
for( auto sym : s577 ) {
if( sym.second->s514() == s494 )
sym.second.s16<Transd*>()->s520( s962->s900(), true );}}}
void s501::reset(){
for( auto it = s577.begin(); it != s577.end(); ++it )
delete it->second.s16<s503*>();
s577.clear();}
void s501::copy( s501& t, s279* s613, s616* s612, s149 ap ) const{
t.s563 = s563;
for( s559::const_iterator it = s577.begin(); it != s577.end(); ++it ) {
if( it->second->s514() == s494 ) {
t.s565( it->first, new s616( *( s616* )&( *it->second ),
s613, s612, std::vector<s278*>(), it->second.s16<Transd*>()->s628() ), ap );}
else {
t.s565( it->first, ((s502*)it->second->s350()), ap );}}}
void s501::s572( s501& t ) const{
for( s559::const_iterator it = s577.begin(); it != s577.end(); ++it ) {
if( it->second->s514() == s494 )
t.s565( it->first, it->second.s16<s502*>() );
else
t.s565( it->first, ((s502*)it->second->s350()) );}}
bool s501::s562( const std::wstring& s78, s149 ap /*= s150*/ )
{
if( s577.find( s78 ) != s577.end() ) {
wstring rep = s7::s437 + L" name already exists: " + s78;
if( ap == s150 || ap == s558 ) {
if( ap == s150 )
throw new s17( (uint32_t)s17::s18::s22 );
return false;}
else if( ap == s152 ) {
return false;}}
return true;}
void s501::s565( const std::wstring& s78, s502* sym, s149 ap/*= s150*/ )
{
if( (ap == s151) || s562( s78, ap ) )
s577[s78] = sym;}
void s501::s565( const std::wstring& s78, s146 s364, s149 ap/*= s150*/ )
{
throw new s17( (uint32_t)s17::s18::s22 );}
void s501::s566( const std::wstring& s78 ){
auto it = s577.find( s78 );
if( it == s577.end() )
return;
s577.erase( it );}
void s501::s567( const s6::s147& s81, s149 ap/*= s150*/ )
{
vector<pair<wstring, s146>> s148;
s81.s164( s148 );
for( size_t n = 0; n < s148.size(); ++n )
s565( s148[n].first, s148[n].second );}
bool s501::s160( const std::wstring& s78 ) const{
if( s577.find( s78 ) == s577.end() )
return false;
return true;}
s502* s501::get( const wstring& s78, bool s544/*= true*/ ) const
{
auto s718 = s577.find( s78 );
if( s718 == s577.end() ) {
if( s544 )
throw new s17( L"2: symbol not found: " + s78 );
else
return NULL;}
return s718->second.s16<s502*>();}
void s501::s570( std::vector<std::wstring>& s157 ) const{
for( auto sym : s577 )
s157.push_back( sym.first );}
void s501::s568( vector<wstring>& s157 ) const{
for( auto sym : s577 ) {
if( sym.second->s514() == s494 )
s157.push_back( sym.first );}}
void s501::s569( vector<wstring>& s157 ) const{
for( auto sym : s577 ) {
if( sym.second->s514() == s492 ||
sym.second->s514() == s499 || sym.second->s514() == s498 )
s157.push_back( sym.first );}}
void s501::s571( const s501& t,
vector<wstring>& s157 ) const{
for( auto sym : s577 ) {
if( t.s160( sym.first ) )
s157.push_back( sym.first );}}
void s501::s296( const s501& t, s149 ap /*= s150*/ )
{
if( ap != s151 ) 
for( auto sym : t.s577 )
s562( sym.first, ap );
for( auto sym : t.s577 )
s565( sym.first, sym.second.s16<s502*>(), ap );}
void s501::s573( s534 pv, s270* s81 ){
if( !s563 )
s563 = new s550();
s563->s553( pv, s81 );}
void s501::s557( const wstring& s347, vector<wstring>& s157 ){
for( s559::iterator it = s577.begin(); it != s577.end(); ++it ) {
s534 pv = s535;
if( s563 )
pv = s563->s556( it->first, s347 );
if( pv == s535 ) {
if( s561 == s531 )
pv = s536;
else if( s561 == s533 )
pv = s537;
else {
if( it->second->s514() == s494 )
pv = s536;
else
pv = s537;}}
if( pv == s536 )
s157.push_back( it->first );}}
bool s501::s574( const std::wstring& s285,
const std::wstring& s347 ) const{
if( s563 ) {
s534 pv = s563->s556( s285, s347 );
if( pv == s536 )
return true;
else if( pv == s535 ) {
if( s561 == s531 )
pv = s536;
else if( s561 == s533 )
pv = s537;
else {
auto it = s577.find( s285 );
if( it == s577.end() )
throw new s17( L"1: Symbol does not exist: " + s285 );
size_t cat = it->second->s514();
if( cat == s494 || cat == s497 || cat == s499 )
return true;}}
return false;}
return true;}
void s501::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s202 ) << L"Symbols :" << endl;
s559::const_iterator it = s577.begin();
for( ; it != s577.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << it->first << endl;
if( it->second.s14() )
it->second->s311( pd, s202 + s435 * 2 );}}
s575::s575(){}
void s575::s520( s269* s307, const wstring& s582 ){
for( size_t n = 0; n < s583.size(); ++n ) {
wstring s78 = s583[n];
vector<wstring> s157;
s307->s225( s78, s582, s157 );
for( size_t m = 0; m < s157.size(); ++m ) {
s577.insert( make_pair( s157[m], make_pair( (s502*)s307->s671( 
s583[n],	s582 ), s78) ) );}}}
void s575::s579( const wstring& s78, s269* s307, const wstring& s582 ){
s583.push_back( s78 );
vector<wstring> s157;
s307->s225( s78, s582, s157 );
for( size_t n = 0; n < s157.size(); ++n )
s577.insert( make_pair( s157[n], make_pair( (s502*)s307->s671( 
s78,	s582 ), s78 ) ) );}
void s575::s578( const std::wstring& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s17( L"Unrecognized import syntax: " + s );
s583.push_back( s.substr(1, s.size() - 2 ) );}
bool s575::s580( const std::wstring& sym, s387* ref ){
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );}
else
mem = sym;
size_t s717 = s577.count( mem );
if( !s717 )
return false;
if( s717 > 1 && mod.empty() )
throw new s17( L"ambigous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s577.equal_range( mem );
if( s717 == 1 && mod.empty() )
return range.first->second.first->s580( mem, ref, L"" );
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod )
return it->second.first->s580( mem, ref, L"" );}
return false;}
void s575::copy( s575& t ) const{
for( s559::const_iterator it = s577.begin(); it != s577.end(); ++it )
t.s577.insert( make_pair( it->first, it->second ) );}
s545::s545( s534 pv_, const vector<wstring>& s547 )
: s546( s547 ), pv( pv_ ){}
s545::s545( const wstring& ag_, const wstring& s79 ){}
s534 s545::s584( const std::wstring& s519 ) const{
for( size_t n = 0; n < s546.size(); ++n )
if( s546[n] == s519 || s546[n] == L"_" )
return pv;
if( pv == s537 )
return s536;
return s537;}
void s550::s553( s534 pv, s270* s737 ){
s270::s282& s738 = s737->s300();
s270::s282::iterator it = s738.begin();
for( ; it != s738.end(); ++it ) {
wstring l = it->second->s298().substr( 1, it->second->s298().size() - 2 );
vector<wstring> s157;
wstring s74( s1236, 1 );
s4::s59( l, s74, s157 );
s552[it->first] = new s545( pv, s157 );}}
void s550::s554( const std::wstring& s, s545& pl ){}
void s550::s555( const std::wstring& s, const std::wstring& s548 ){}
s534 s550::s556( const std::wstring& mem, const std::wstring& s519 ){
s551::iterator it = s552.find( mem );
if( it == s552.end() )
return s535;
return it->second->s584( s519 );}
s1172 s1687::s1426 = 0;
s1172 s1687::s1724 = 0;
s351::s356 s400::s363;
s351::s356 s380::s363;
s351::s356 s377::s363;
s351::s356 s376::s363;
s351::s356 s361::s363;
s351::s356 s374::s363;
s351::s356 s1465::s363;
s351::s356 s1704::s363;
s351::s356 s1454::s363;
s351::s356 s375::s363;
s351::s356 s324::s363;
s351::s356 s794::s363;
s351::s356 s1050::s363;
s351::s356 s333::s363;
s351::s356 s1553::s363;
s351::s356 s1449::s363;
s351::s356 s431::s363;
s351::s356 s1463::s363;
s351::s356 s401::s363;
s351::s356 s1257::s363;
s351::s356 s1041::s363;
s351::s356 s1268::s363;
s351::s356 s680::s363;
s351::s356 s528::s363;
s351::s356 s1452::s363;
s351::s356 s1461::s363;
s351::s356 s1574::s363;
s351::s356 s1576::s363;
size_t s351::s804 = 0;
s9<s400> s829;
s9<s380> s781;
s9<s377> s876;
s9<s376> s803;
s505 s361::proto;
s9<s374> s859;
s505 s1465::proto;
s505 s1704::proto;
s505 s1454::proto;
s9<s375> s843;
s9<s431> s867;
s9<s1463> s1464;
s9<s324> s765;
s9<s794> s788;
s9<s1050> s1051;
s9<s333> s771;
s9<s1553> s1555;
s9<s1449> s1451;
s9<s401> s865;
s9<s1257> s1259;
s9<s1041> s1469;
s9<s528> s871;
s9<s1452> s1453;
s9<s1461> s1462;
s9<s680> s808;
s9<s907> s1265;
s9<s380> s381;
s9<s400> s947;
s9<s400> s382;
s9<s400> s383;
s9<s400> s384;
s9<s400> s951;
s9<s376> s385;
s9<s376> s386;
s9<s1574> s1575;
s9<s1576> s1577;
s9<s400> s1696;
template <class charT, charT s74>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s74; }
};
std::locale exprloc;
s502::~s502(){}
void s351::s835( s269* s307, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
if( !soft ) {
std::vector<s278*> l;
s829 = new s400( s307 );
s781 = new s380( s307 );
s803 = new s376( s307 );
s876 = new s377( s307 );
s361::proto = new s361( s307 );
s859 = new s374( s307 );
s1465::proto = new s1465( s307 );
s1704::proto = new s1704( s307 );
s1454::proto = new s1454( s307 );
s843 = new s375( s307 );
s765 = new s324( s307 );
s788 = new s794( s307 );
s1051 = new s1050( s307 );
s771 = new s333( s307 );
s1555 = new s1553( s307 );
s1451 = new s1449( s307 );
s808 = new s680( s307 );
s865 = new s401( s307 );
s1259 = new s1257( s307 );
s1469 = new s1041( s307 );
s867 = new s431( s307 );
s1265 = new s907( s307 );
s871 = new s528( s307 );
s1453 = new s1452( s307 );
s1462 = new s1461( s307 );}
s307->s224( s829, L"NoValue" );
s307->s224( s781, L"Null" );
s307->s224( s876, L"Exception" );
s307->s224( s803, L"Bool" );
s307->s224( s361::proto, L"Int" );
s307->s224( s859, L"Double" );
s307->s224( s1465::proto, L"Long" );
s307->s224( s1704::proto, L"ULong" );
s307->s224( s1454::proto, L"Byte" );
s307->s224( s765, L"Vector" );
s307->s224( s788, L"UntypedVector" );
s307->s224( s1051, L"Tuple" );
s307->s224( s771, L"Index" );
s307->s224( s1555, L"HashIndex" );
s307->s224( s1451, L"ByteArray" );
s307->s224( s867, L"Directory" );
s307->s224( s865, L"Range" );
s307->s224( s1259, L"Filter" );
s307->s224( s1469, L"Seq" );
s307->s224( s808, L"TSDBase" );
s307->s224( s871, L"StringStream" );
s307->s224( s1453, L"ByteStream" );
s307->s224( s1462, L"FileStream" );
s307->s224( s1265, L"Lambda" );
s307->s224( s843, L"String" );
if( !soft ) {
s804 = s843->s367();
s381 = new s380( s307 );
s947 = new s400( s307, s500 );
s384 = new s400( s307, s500 );
s383 = new s400( s307, s500 );
s382 = new s400( s307, s500 );
s951 = new s400( s307, s500 );
s385 = new s376( s307, true );
s386 = new s376( s307, false );
s947->setWh( s7::s941 );
s384->setWh( s7::s454 );
s383->setWh( s7::s455 );
s382->setWh( s7::s456 );
s385->s1412();
s386->s1412();
s1696 = new s400( s307, s1285, s1397 );}}
s1240::s1240( const std::vector<s504>& v, s351* s617 )
:s613( s617 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s514() != s1174 ) {
s1000.push_back( v[n] );
s1433.push_back( v[n]->s367() );}}}
bool s1240::operator==( const s1240& s548 ) const{
bool pend = s1433.empty();
bool send = s548.s1433.empty();
s1172 starred = 0;
size_t n = 0, k = 0;
bool s1422 = true;
s510* ptr = s548.s613 ? &s548.s613->Pass()->TR() : NULL;
while( !send || !pend ) {
s1422 = false;
s1172 s1320 = starred ? starred : (pend ? 0 : s1433[k]);
s1172 s1316 = send ? (s548.s1433.empty() ? 0 : s548.s1433[n-1]) : s548.s1433[n];
s278* s1712 = send ?
( s548.s1000.empty() ? NULL : s548.s1000[n - 1].s16<s278*>() ) :
s548.s1000[n].s16<s278*>();
if( s1316 == s829->s367() )
s1316 = send ? s548.s1000[n-1].s16<s400*>()->s1715() : 
s548.s1000[n].s16<s400*>()->s1715();
const s869* s1437 = s548.s613 ? &s548.s613->s1340() : NULL;
if( s1320 >= s7::s1571 && s1320 < s7::NCTraitNumAlias0 && s1316 ) {
if( s1320 == s7::s1565 )
s1422 = true;
else if( s1320 == s7::s1570 ) {
s1172 pt1_ = s548.s1000[n]->s1340().s367();
if( pt1_ == s1265->s367() /*&& pt2_ == s1276*/ )
s1422 = true;}
else if( s1320 == s7::s1566 ) {
if( s548.s613 && s1316 == s548.s613->s367())
s1422 = true;}
else if( s1320 == s7::s1567 ) {
if( s548.s613 && s1316 == ( (s337*)s548.s613 )->s328() )
s1422 = true;}
else if( s1320 == s7::s1567 ) {
if( s548.s613 && s1316 == ((s337*)s548.s613)->s328() )
s1422 = true;}
else if( s1320 == s7::s1568 ) {
if( s548.s613 && s1316 == ((s337*)s548.s613)->s1025() )
s1422 = true;}
else if( s1320 == s7::s1569 ) {
if( s548.s613 && s1712->s1716( ((s337*)s548.s613)->ValType() ) )
s1422 = true;}
else if( s1437 &&	s1316 == s1437->s367( (size_t)((int)0 - s1320 )) )
s1422 = true;}
else if( s1320 >= s7::NCTraitNumAlias0 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1320 );
if( ptr->s1342( s1316, s1688 ) )
s1422 = true;}
else {
if( s1712 && s1712->s1716( s1320 ) )
s1422 = true;}
if( s1422 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s548.s1433.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1433.size() )
pend = true;
if( !starred && !pend && s1433[k] == s7::s1571 )
starred = s1433[k - 1];}
return s1422;}
bool s1240::operator<( const s1240& s548 ) const{
if( s1433.empty() ) return s548.s1433.size() > 0;
if( s548.s1433.empty() ) return false;
const s869* s1436 = s613 ? &s613->s1340() : NULL;
const s869* s1437 = s548.s613 ? &s548.s613->s1340() : NULL;
s1172 s1420 = 0, s1421 = 0;
s510* ptr = s548.s613 ? &s548.s613->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1433.size() && n < s548.s1433.size()*/; ++n ) {
if( s1433.size() == n )
return s548.s1433.size() > n;
if( s548.s1433.size() == n )
return false;
s1172 s1318 = s1420 ? s1420 : s1433[n];
s1172 s1321 = s1421 ? s1421 : s548.s1433[n];
if( s1318 >= s7::s1571 && s1318 <= s7::NCTraitNumAlias0 ) {
if( s1318 == s7::s1571 )
s1318 = s1420 = s1433[n - 1];
else if( s1318 == s7::s1565 )
continue;
else if( s1318 == s7::s1566 ) {
if( !s548.s613 )
return true;
s1318 = s548.s613->s367();}
else if( s1318 == s7::s1567 ) {
if( !s548.s613 )
return true;
s1318 = ( (s337*)s548.s613 )->s328();}
else if( s1436 )
s1318 = s1436->s367( (size_t)(int)0 - s1318 );}
else if( s1318 >= s7::NCTraitNumAlias0 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1318 );
if( ptr->s1342( s1321, s1688 ) )
return true;}
if( s1321 >= s7::s1571 && s1321 <= s7::NCTraitNumAlias0 ) {
if( s1321 == s7::s1571 )
s1321 = s1421 = s548.s1433[n - 1];
else if( s1321 == s7::s1565 )
continue;
else if( s1321 == s7::s1566 ) {
if( !s613 )
return true;
s1321 = s613->s367();}
else if( s1321 == s7::s1567 ) {
if( !s613 )
return true;
s1321 = ( (s337*)s613 )->s328();}
else if( s1437 )
s1321 = s1437->s367( (size_t)(int)0 - s1321 );}
else if( s1321 >= s7::NCTraitNumAlias0 && ptr ) {
traitnum_t s1688 = ptr->s1633( s1321 );
if( ptr->s1342( s1318, s1688 ) )
return true;}
if( s1318 < s1321 )
return true;}
return false;}
wstring s1240::s1496( s269* s307 ) const{
wstring s718 = L"( ";
for( auto i : s1433 ) {
s718 += s307->TR().s856( i );
if( s718.back() != L')' ) s718 += L"()";
s718 += L" ";}
s718 += L")";
return s718;}
bool
s351::s352::s1307( /*s351* thi,*/ const s1240& s724 ) const
{
return std::find( s1303.begin(), s1303.end(), s724 ) != end( s1303 );}
s1172
s351::s402( const std::wstring& s358 ) const{
auto it = s357().find( s358 );
if( it == s357().end() )
throw new s17( L"No such operation: " + s369() +	L"::" + s358,
(uint32_t)s17::s18::s24 );
s1172 s718 = it->second->s515();
return s718;}
const s502*
s351::s524() const{
return (s502*)s307->TR().s1108( s367() );}
const vector<wstring>& 
s351::s1335( const wstring& s358 ) const{
auto ran = s357().equal_range( s358 );
if( ran.first == s357().end() )
throw new s17( L"No such method: " + s369() + L"::" + s358,
(uint32_t)s17::s18::s24 );
return ran.first->second->Markers();}
s1267 s351::s1341( const std::wstring& s358 ) const{
s351::s352* s718 = NULL;
auto it = s357().find( s358 );
if( it != s357().end() )
s718 = it->second;
return s718 ? s1267( s718->s515(), s718->s1260(), s718->s1348() ) : s1267();}
s1267
s351::s1336( const wstring& s358, s1240& ap /*const vector<s1172>& s1389*/ ) const
{
auto ran = s357().equal_range( s358 );
if( ran.first == s357().end() )
throw new s17( L"No such method: " + s369() + L"::" + s358,
(uint32_t)s17::s18::s24 );
if( ran.first->second->s1330() )
throw new s17( L"", (uint32_t)s352::s1256::s1323 );
s352* s718 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1307( ap ) ) {
s718 = it->second;
break;}}
return s718 ? s1267( s718->s515(), s718->s1260(), s718->s1348() ) : s1267();}
s1267
s351::s1331( const wstring& s358, s1240& ap/*const vector<s1172>& s1389,
const vector<s504>& s281*/ )
{
auto ran = s357().equal_range( s358 );
s352* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1307( ap ) ) {
mi = it->second;
break;}}
s1267 s1386( mi->s515(), mi->s1260(), mi->s1348() );
if( mi )
s1386.s353 = ap.Subj()->s1332( s358, ap.s627() );
return s1386;}
s505 s351::s517( s502** s281, size_t s518 ){
return this;}
void s351::s1710( s502* p ){}
s502* s351::s360( s269* s307, const std::wstring& s364, const std::wstring& s347 ){
s270 s213( s364, NULL );
s502* s718 = NULL;
if( s364.find_first_not_of( L"-0123456789" ) == std::string::npos ||
s364.find( L"Int(" ) == 0 ) {
s718 = s361::proto.s16<s361*>()->s370( s213, NULL, s347 );}
if( !s718 ) {
s718 = s859->s370( s213, NULL, s347 );
if( !s718  )
s718 = s1465::proto.s16<s1465*>()->s370( s213, NULL, s347 );
if( !s718 )
s718 = s1454::proto.s16<s1454*>()->s370( s213, NULL, s347 );}
return s718;}
#define s734 ((s361*)(s503*)*s281)
#define s735 ((s376*)(s503*)*s281)
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
s502* s374::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
s.find( L"." ) != std::string::npos ) {
size_t pos = 0;
return new s374( s307, s, pos );}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s374( s307, s4::s54( s.substr( 7, s.size() - 8 ), s4::s50 ),
pos );}
else if( s.find( L"Double" ) == 0 ) {
return s371( s613, std::vector<s278*>(), &s737 );}
return 0;}
void s361::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << s364;}
s374::s374( s269* s307, double d ) 
: s351( s307, NULL, NULL ), s364( d ){
if( s859.s13() ) {
s513 = 0;
wh = s7::s943;}
else {
s513 = s859->s367();
wh = s7::s942;}}
s374::s374( const s374& r )
: s351( r.s307, r.ns, r.s628() ), s364( r.s364 ){
wh = r.wh;
s513 = r.s513;}
s374::s374( s269* s307, const std::wstring& s, size_t& pos )
: s351( s307, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
double s157 = 0.0;
if( !s.empty() ) {
pst = s.c_str();
if( !s65( pst, &s157, &pend ) )
throw new s17( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s21 );
setWh( s7::s942 );}
else
s157 = s307->TR().s1403();
s364 = s157;
pos = pend ? pend - pst : string::npos;
s513 = s859->s367();}
s502* s374::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
size_t pos = 0;
return new s374( s307, L"", pos );}
void s374::s520( s502* s962 ){}
void s374::s365(){
s363.insert( make_pair( L"abs", new s352( L"abs", &s374::s420, s1284,
{ s1240( ) }, 0, 0 )));
s363.insert( make_pair( L"set", new s352( L"set", &s374::s403, s1287,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"sum", new s352( L"sum", &s374::s404, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"dif", new s352( L"dif", &s374::s405, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"mul", new s352( L"mul", &s374::s406, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"div", new s352( L"div", &s374::s407, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"pow", new s352( L"pow", &s374::s408, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"sumeq", new s352( L"sumeq", &s374::s409, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"difeq", new s352( L"difeq", &s374::s410, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"muleq", new s352( L"muleq", &s374::s411, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"diveq", new s352( L"diveq", &s374::s412, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"poweq", new s352( L"poweq", &s374::s413, s1284,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"sqrt", new s352( L"sqrt", &s374::s422, s1284,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"nroot", new s352( L"nroot", &s374::s423, s1284,
{ s1240( { s1285 } ) }, 1, 1 )));
s363.insert( make_pair( L"eq", new s352( L"eq", &s374::s414, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"less", new s352( L"less", &s374::s415, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"greater", new s352( L"greater", &s374::s416, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"leq", new s352( L"leq", &s374::s417, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"geq", new s352( L"geq", &s374::s418, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"neq", new s352( L"neq", &s374::s419, s1276,
{ s1240( { s1284 } ) }, 1, 1 )));
s363.insert( make_pair( L"dcmp", new s352( L"dcmp", &s374::s426, s1285,
{ s1240( { s1284, s1284 } ) }, 2, 2 )));
s363.insert( make_pair( L"dcmpr", new s352( L"dcmpr", &s374::s427, s1285,
{ s1240( { s1284, s1284 } ) }, 2, 2 )));
s363.insert( make_pair( L"to-Int", new s352( L"to-Int", &s374::s428, s1285,
{ s1240(), s1240( { s1285 } ) }, 0, 1 )));
s307->TR().s1302( s513, s7::s1585, s1687::s1426 );}
s278* s374::s350() const{
return new s374( *this );}
void s374::s372( s278* p ) const{
if( p->s367() == s361::proto->s367() )
*( (s361*)p )->s373() = (int)s364;
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = s364;
else if( p->s367() == s803->s367() )
*( (s376*)p )->s373() = ( s364 != 0.0 );
else
throw new s17( L"No conversion to type " + s369() );}
std::wstring s374::to_wstring() const {
wstring s = std::to_wstring( s364 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
return s.substr(0, pl);}
#undef s734
#define s734 ((s374*)(s503*)*s281)
#define INTRES ((s361*)(s503*)*s281)
inline void s374::s403( s502** s281, size_t s518 ){
( (s374*)DR )->s364 = (double)*PARN( 2 );}
void s374::s420( s502** s281, size_t s518 ){
double t = (double)*DR;
if( t >= 0 )
s734->s364 = t;
else
s734->s364 = -t;}
inline void s374::s406( s502** s281, size_t s518 ){
s734->s364 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
s734->s364 *= (double)*PARN( n );}
inline void s374::s404( s502** s281, size_t s518 ){
s734->s364 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
s734->s364 += (double)*PARN( n );}
inline void s374::s407( s502** s281, size_t s518 ){
s734->s364 = ( (double)*DR ) / (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
s734->s364 /= (double)*PARN( n );
}
inline void s374::s405( s502** s281, size_t s518 ){
s734->s364 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
s734->s364 -= (double)*PARN( n );}
inline void s374::s409( s502** s281, size_t s518 ){
( (s374*)DR )->s364 += (double)*PARN(2);
for( size_t n = 3; n < s518; ++n )
( (s374*)DR )->s364 += (double)*PARN(n);
s734->s364 = ( (double)*DR );}
inline void s374::s410( s502** s281, size_t s518 ){
( (s374*)DR )->s364 -= (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
( (s374*)DR )->s364 -= (double)*PARN( n );
s734->s364 = ( (double)*DR );}
inline void s374::s411( s502** s281, size_t s518 ){
( (s374*)DR )->s364 *= (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
( (s374*)DR )->s364 *= (double)*PARN( n );
s734->s364 = ( (double)*DR );}
inline void s374::s412( s502** s281, size_t s518 ){
( (s374*)DR )->s364 /= (double)*PARN( 2 );
for( size_t n = 3; n < s518; ++n )
( (s374*)DR )->s364 /= (double)*PARN( n );
s734->s364 = ( (double)*DR );}
inline void s374::s413( s502** s281, size_t s518 ){
( (s374*)DR )->s364 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s518; ++n )
( (s374*)DR )->s364 = ::pow( (double)*DR, (double)*PARN( n ) );
s734->s364 = ( (double)*DR );}
inline void s374::s414( s502** s281, size_t s518 ){
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s415( s502** s281, size_t s518 ){
if( ((double)*DR) < (double)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s416( s502** s281, size_t s518 ){
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s417( s502** s281, size_t s518 ){
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s418( s502** s281, size_t s518 ){
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s419( s502** s281, size_t s518 ){
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s374::s422( s502** s281, size_t s518 ){
s734->s364 = ::sqrt((double)*DR);}
inline void s374::s423( s502** s281, size_t s518 ){
*( (s374*)s281[0] )->s373() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s374::s426( s502** s281, size_t s518 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s373() = 0;
else
*INTRES->s373() = 1;}
else {
if( dr - dl <= diff )
*INTRES->s373() = 0;
else
*INTRES->s373() = -1;}}
inline void s374::s427( s502** s281, size_t s518 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s373() = 0;
else
*INTRES->s373() = 1;}
else {
if( dr / dl - 1 <= diff )
*INTRES->s373() = 0;
else
*INTRES->s373() = -1;}}
inline void s374::s408( s502** s281, size_t s518 ){
s734->s364 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );}
inline void s374::s428( s502** s281, size_t s518 ){
int s1498 = -1;
if( s518 == 3 )
s1498 = (int)*s281[2];
double dv = ( (s374*)DR )->s364;
int s718 = (int)dv;
if( s1498 < 0 )
*( (s361*)s281[0] )->s373() = s718;
else if( s1498 == 0 ) 
*( (s361*)s281[0] )->s373() = (dv - s718 > 0.5 ? s718 + 1 : s718);
else
*( (s361*)s281[0] )->s373() = s718 + 1;}
void s374::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << s364;}
size_t s374::s331() const{
return hash<double>{}( s364 );}
inline
int dcmp( double d1, double d2, int iDigs ){
double s89 = fabs( d1 - d2 );
double prec = 1 / pow( (double)10.0, iDigs );
if ( s89 < prec )
return 0;
if ( d1 < d2 )
return 1;
return -1;}
inline
int dcmp_( double d1, double d2, double dif ){
double s89 = fabs( d1 - d2 );
if ( s89 < dif )
return 0;
if ( d1 < d2 )
return 1;
return -1;}
inline bool s374::operator==( const s502* p ) const{
return ( dcmp_( ( (s374*)p )->s364, s364, 0.00000001 ) == 0 ); // FIX:
}
inline bool s374::operator<( const s502* p ) const{
return ( dcmp_( s364, ( (s374*)p )->s364, 0.00000001 ) < 0 ); // FIX:
}
s376::s376( s269* s307, const std::wstring& s, size_t& pos )
: s351( s307, NULL, NULL ){
if( s.empty() )
s364 = s307->TR().s1401();
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s364 = (s[0] == L'1');
pos++;}
else if( s.find( s7::s452 ) == 0 ) {
s364 = true;
pos += 4;}
else if( s.find( s7::s453 ) == 0 ) {
s364 = false;
pos += 5;}
else
throw new s17( L"unknown bool format: " + s.substr( 0, 20 ) );
if( !s.empty() )
setWh( s7::s942 );
s513 = s803->s367();}
s376::s376( const s376& right )
: s351( right.s307, right.ns, NULL ), s364( right.s364 ){
s513 = s803->s367();}
s376::s376( s269* s307, bool b )
: s351( s307, NULL, NULL ), s364( b ){
if( s803.s13() ) {
s513 = 0;
setWh( s7::s943 );}
else {
s513 = s803->s367();
setWh( s7::s942 );}}
void s376::s365(){
s363.insert( make_pair( L"set", new s352( L"set", &s376::s403, s1287,
{ s1240( { s1276 } ) }, 1, 1, false )));
s363.insert( make_pair( L"not", new s352( L"not", &s376::s429, s1276,
{ s1240( ) }, 0, 0, true )));
s363.insert( make_pair( L"eq", new s352( L"eq", &s376::s414, s1276,
{ s1240( { s1276 } ) }, 1, 1, true )));}
void s376::s520( s502* s962 ){}
s502* s376::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s376( s307, false );}
s502* s376::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find( s7::s452 ) == 0 || s.find( s7::s453 ) == 0 )
return new s376( s307, ( s.find( s7::s452 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s376( s307, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Bool" ) == 0 ) {
return s371( s613, std::vector<s278*>(), &s737 );}
return NULL;}
s278* s376::s350() const{
return new s376( *this );}
void s376::s372( s278* p ) const{
if( p->s367() == s1276 )
((s376*)p)->s364 = s364;
else if( p->s367() == s361::proto->s367() )
*( (s361*)p )->s373() = (int)s364;
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = (double)s364;
else
throw new s17( L"No conversion to type " + s369() );}
#undef s734
#define s734 ((s376*)(s503*)*s281)
inline void s376::s403( s502** s281, size_t s518 ){
( (s376*)DR )->s364 = ( (s376*)PARN( 2 ) )->s364;}
inline void s376::s429( s502** s281, size_t s518 ){
s734->s364 = !( (s376*)DR )->s364;}
inline void s376::s414( s502** s281, size_t s518 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s735->s373() = 1;
else
*s735->s373() = 0;}
void s376::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << to_wstring();}
size_t s376::s331() const{
return hash<bool>{}( s364 );}
inline bool s376::operator==( const s502* p ) const{
return ( s364 == ((s376*)p)->s364 );}
inline bool s376::operator<( const s502* p ) const{
return ( s364 < ((s376*)p)->s364 );}
s377::s377( s269* s307, const std::wstring& s/* = std::wstring( L"" )*/ )
: s351( s307, NULL, NULL ), s80( s ){
wh = s7::s456;
s513 = s876.s13() ? 0 : s876->s367();}
s377::s377( const s377& r )
: s351( r.s307, NULL, NULL ), s80( r.s80 ){
s513 = r.s513;
wh = r.wh;}
void s377::s365(){
s363.insert( make_pair( L"report", new s352( L"report", &s377::s844, s1287,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"str", new s352( L"str", &s377::s529, s1289,
{ s1240() }, 0, 0 )));}
void s377::s520( s502* s962 ){}
s502* s377::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s377( s307 );}
s278* s377::s350() const{
return new s377( *this );}
void s377::s372( s278* p ) const{
((s377*)p)->s80 = s80;}
s502* s377::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find( L"Exception(" ) == 0 )
return new s377( s307, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s371( s613, std::vector<s278*>(), &s737 );
return NULL;}
#undef s734
#define s734 ((s377*)(s503*)*s281)
inline void s377::s844( s502** s281, size_t s518 ){
wcout << ( (s377*)DR )->s80;}
inline void s377::s529( s502** s281, size_t s518 ){
*( (s375*)s281[0] )->s373() = ( (s377*)DR )->s80;}
void s377::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : -";}
size_t s377::s331() const{
throw new s17( L"9: not implemented" );}
bool s377::operator==( const s502* p ) const{
return ( (s377*)p )->s80 == s80;}
bool s377::operator<( const s502* p ) const{
return s80 < ( (s377*)p )->s80;}
s380::s380( s269* s307 ) 
: s351( s307, NULL, NULL ){
if( s781.s13() ) {
s513 = 0;
setWh( s7::s943 );}
else {
s513 = s781->s367();
setWh( s7::s942 );}}
void s380::s520( s502* s962 ){}
s502* s380::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s380( s307 );}
s502* s380::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find( L"Null" ) == 0 )
return s381;
return NULL;}
s278* s380::s350() const{
return (s278*)this;}
void s380::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : -";}
size_t s380::s331() const{
throw new s17( L"not implemented" );}
bool s380::operator==( const s502* p ) const{
return ( this == p );}
bool s380::operator<( const s502* p ) const{
return false;}
s400::s400( s269* s307, traitnum_t tn, s490 pc ) 
: s351( s307, NULL, NULL ), s1427( tn ){
s512 = pc;
s513 = s829.s13() ? 0 : s829->s367(); }
void s400::s520( s502* s962 ){}
s502* s400::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s400( s307 );}
s502* s400::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
throw new s17( L"no parser for NoValue" );
return NULL;}
s278* s400::s350() const{
return (s278*)this;}
inline bool
s400::s522( const s502* s523 ) const{
double d = (double)s523->s367() / s1427;
return ( d == (int)d );}
inline bool
s400::s1716( s1172 s647 ) const{
return s307->TR().s1709( s1427, s647 );}
void s400::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : -" << endl;}
size_t s400::s331() const{
throw new s17( L"not implemented" );}
bool s400::operator==( const s502* p ) const{
return false;}
bool s400::operator<( const s502* p ) const{
return false;}
s387::s387( const std::wstring& s, s269* s307, s490 cat )
: s503( s307, cat ), s388( s ), s392( 0 ){
assert( cat == s491 || cat == s493 || cat == s500 || cat == s1174 );
if( cat == s491 ) {
if( s[0] == L':' ) {
s512 = s1174;
s513 = s829->s367();
s389 = s829.s16<s502*>();}
/*else if( s389.s14() && s307->s227( s388, (s502*)s389 ) ) {
s512 = s500;
s513 = s829->s367();
}*/
else
s512 = s493;}}
s387::s387( const s387& right )
: s503( right.s307, s493 ), s388( right.s388 ), s390( right.s390 ), s392( 0 ){}
void s387::s520( s502* s612 ){
if( false && s307->s227( s388, s389.s16<s502*>() ) ) {
s512 = s500;
s513 = s829->s367();}
else {
if( !s612->s580( s388, this, s612->s900() ) ) {
if( s512 == s1174 )
return;
throw new TDException( 0, s1018, NULL, s388 );}
if( s390 )
s513 = s390->s367();
else if( s512 == s1505 )
s513 = s389.s16<s387*>()->s393()->s367();
else
assert( 0 );}}
s502* s387::s393() const{
if( s512 == s1174 )
return s389.s16<s502*>();
else if( s512 == s1505 )
return s389.s16<s387*>()->s393();
if( s391.empty() )
return s389.s16<s502*>();
s503* s718 = s389.s16<s279*>()->s623( *(size_t*)&s391[0] );
for( size_t n = 1; n < s392; ++n )
s718 = ((s279*)s718->s516())->s623( *( (size_t*)&s391[0] + n ) );
return s718->s516();}
s502* s387::s394(){
if( s391.empty() )
return s389.s16<s502*>();
s502*	s718 = ((s502*)s389.s16<s279*>()->s623( *(size_t*)&s391[0] ));
for( size_t n = 1; n < s392; ++n )
s718 = (s502*)((s279*)s718)->s623( *( (size_t*)&s391[0] + n ) );
return s718;}
void s387::s1079( const std::vector<std::wstring> &s878 ){
auto it = std::find( begin( s878 ), end( s878 ), s644() );
if( it != end( s878 ) ) {
s512 = s1174;
s513 = s829->s367();
s392 = std::distance( begin( s878 ), it );
s389 = new s361( NULL, (int)s392 ); //s829.s16<s502*>();
}}
s505 s387::s517( s502** s281, size_t s518 ){
return s393()->s517( s281, s518 );}
s502* s387::s516(){
return s393()->s516();}
/*bool s387::s522( const s502* s523 ) const
{
if( s523->s514() == s493 )
return s393()->s522( ((s387*)s523)->s393() );
return s393()->s522( s523 );
}*/
s278* s387::s350() const{
return new s387( *this );}
void s387::s395( size_t off, const s502* proto ){
s391.push_back( off );
s392 = s391.size();
s390 = proto;}
void s387::s1511( s387* ptr ){
s512 = s1505;
s391.clear();
s392 = 0;
s389 = ptr;
s390 = NULL;}
void s387::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"DataRef : " << s388;}
template<class s1479, class Der>
s351::s356 s1471<s1479, Der>::s363;
template<class s1479, class Der>template <class s1705, class s1706>
void s1471<s1479, Der>::s1707( s502* src, s502* s828 ){
*((s1705*)s828)->s373() = (s1706) ( (Der*)src )->s364;}
template <class s1479, class Der>
s502* s1471<s1479, Der>::s1711( const s502* p ) const{
Der* s718 = new Der( p->Pass() );
if( p->s1716( s367() ) )
p->s372( s718 );
s718->s1414();
return s718;}
template <class s1479, class Der>
size_t s1471<s1479, Der>::s331() const{
return (size_t)s364;}
template <class s1479, class Der>
inline bool s1471<s1479, Der>::operator==( const s502* p ) const{
return ( (Der*)p )->s364 == s364;}
template <class s1479, class Der>
inline bool s1471<s1479, Der>::operator<( const s502* p ) const{
return s364 < ( (Der*)p )->s364;}
template <class s1479, class Der>
void s1471<s1479, Der>::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << s364 << endl;}
#define s1700 Der::proto->s367()
template <class s1479, class Der>
void s1471<s1479, Der>::s365(){
s363.insert( make_pair( L"abs", new s352( L"abs", &s1471<s1479, Der>::s420, s1700,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"set", new s352( L"set", &s1471<s1479, Der>::s403, s1287,
{ s1240( { /*Der::proto->s367()*/ s1687::s1426 } ) }, 1, 1, false ) ) );
s363.insert( make_pair( L"sum", new s352( L"sum", &s1471<s1479, Der>::s404, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"dif", new s352( L"dif", &s1471<s1479, Der>::s405, s1700,
{ s1240( { s1687::s1426 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"mul", new s352( L"mul", &s1471<s1479, Der>::s406, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"div", new s352( L"div", &s1471<s1479, Der>::s407, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"pow", new s352( L"pow", &s1471<s1479, Der>::s408, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"pow", new s352( L"pow", &s1471<s1479, Der>::s408, s1284,
{ s1240( { s1284 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"sumeq", new s352( L"sumeq", &s1471<s1479, Der>::s409, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1, false ) ) );
s363.insert( make_pair( L"difeq", new s352( L"difeq", &s1471<s1479, Der>::s410, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1, false ) ) );
s363.insert( make_pair( L"muleq", new s352( L"muleq", &s1471<s1479, Der>::s411, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1, false ) ) );
s363.insert( make_pair( L"diveq", new s352( L"diveq", &s1471<s1479, Der>::s412, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1, false ) ) );
s363.insert( make_pair( L"not", new s352( L"not", &s1471<s1479, Der>::s429, s1276,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"eq", new s352( L"eq", &s1471<s1479, Der>::s414, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"less", new s352( L"less", &s1471<s1479, Der>::s415, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"greater", new s352( L"greater", &s1471<s1479, Der>::s416, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"leq", new s352( L"leq", &s1471<s1479, Der>::s417, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"geq", new s352( L"geq", &s1471<s1479, Der>::s418, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"neq", new s352( L"neq", &s1471<s1479, Der>::s419, s1276,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"mod", new s352( L"mod", &s1471<s1479, Der>::s421, s1700,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"sqrt", new s352( L"sqrt", &s1471<s1479, Der>::s422, s1284,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"nroot", new s352( L"nroot", &s1471<s1479, Der>::s423, s1284,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"to-Double", new s352( L"to-Double", &s1471<s1479, Der>::s424, s1284,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"to-Long", new s352( L"to-Long", &s1471<s1479, Der>::s1722, s1701,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"to-ULong", new s352( L"to-ULong", &s1471<s1479, Der>::s1723, s1702,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"read", new s352( L"read", &s1471<s1479, Der>::s425, s1700,
{ s1240() }, 0, 0, false ) ) );}
template<class s1479, class Der>
s1172 s1471<s1479, Der>::
s1332( const std::wstring& s1728, const std::vector<s504>& l ) const{
s1172 s718 = 0;
if( 0 && s1728 == L"mod" )
s718 = this->s367();
return s718;}
#undef s734
#define s734 ((Der*)(s503*)*s281)
#define s735 ((s376*)(s503*)*s281)
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
template<class s1479, class Der>
inline void s1471<s1479, Der>::s403( s502** s281, size_t n ){
s281[2]->s372( s281[1] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s420( s502** s281, size_t s518 ){
s1479 t = ( (Der*)DR )->s364;
if( t >= 0 )
s734->s364 = t;
else
s734->s364 = -t;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s404( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
s734->s364 = ( (Der*)DR )->s364 + s734->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s405( s502** s281, size_t s518 ){
if( s518 == 2 )
s734->s364 = -( (Der*)DR )->s364;
else {
s281[2]->s372( s281[0] );
s734->s364 = ( (Der*)DR )->s364 - s734->s364;}}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s406( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
s734->s364 = ( (Der*)DR )->s364 * s734->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s407( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
s734->s364 = ( (Der*)DR )->s364 / s734->s364;
}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s408( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
s734->s364 =(s1479) std::pow( (double)( (Der*)DR )->s364, (double)s734->s364 );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s409( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
( (Der*)DR )->s364 += s734->s364;
s734->s364 = ( (Der*)DR )->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s410( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
( (Der*)DR )->s364 -= s734->s364;
s734->s364 = ( (Der*)DR )->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s411( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
( (Der*)DR )->s364 *= s734->s364;
s734->s364 = ( (Der*)DR )->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s412( s502** s281, size_t s518 ){
s281[2]->s372( s281[0] );
( (Der*)DR )->s364 /= s734->s364;
s734->s364 = ( (Der*)DR )->s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s414( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 == tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s429( s502** s281, size_t s518 ){
if( ((bool)( (Der*)DR )->s364) == false )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s415( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 < tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s416( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 > tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s417( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 <= tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s418( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 >= tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = true;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s419( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( ( (Der*)DR )->s364 != tmp.s364 )
*s735->s373() = true;
else
*s735->s373() = false;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s421( s502** s281, size_t s518 ){
Der tmp;
s281[2]->s372( &tmp );
if( tmp.s364 == 0 )
throw new s17( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s734->s364 = ((Der*)DR)->s364 % tmp.s364;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s422( s502** s281, size_t s518 ){
*( (s374*)s281[0] )->s373() = ::sqrt( (double)*DR );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s423( s502** s281, size_t s518 ){
*( (s374*)s281[0] )->s373() = ::pow( ((Der*)DR)->s364, 1.0 / (double)*PARN( 2 ) );
}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s424( s502** s281, size_t s518 ){
*( (s374*)s281[0] )->s373() = (double)*DR;}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1722( s502** s281, size_t s518 ){
s281[1]->s372( s281[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1723( s502** s281, size_t s518 ){
s281[1]->s372( s281[0] );}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s1676( s502** s281, size_t s518 ){
*( (s375*)s281[0] )->s373() = DR->to_wstring();}
template<class s1479, class Der>
inline void s1471<s1479, Der>::s425( s502** s281, size_t s518 ){
int i;
wstring s96 = L"";//( (s375*)s281[2] )->to_wstring();
wstring si = consutils::s104( s96, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s17( L"Error: invalid input; integer is required." );}
s734->s364 = i;}
s361::s361( s269* s307 )
: s1471( s307, NULL, NULL ){
if( proto.s13() )
s513 = 0;
else
s513 = proto->s367();
s364 = (s1558)s307->TR().s1409();
setWh( s7::s943 );}
s361::s361( s269* s307, int i )
: s1471( s307, NULL, NULL ){
if( proto.s13() ) {
s513 = 0;
wh = s7::s943;}
else {
s513 = proto->s367();
s364 = i;
s1414();}}
s361::s361( const s361& r )
: s1471( r ){}
s361::s361( s269* s307, const std::wstring& s, size_t& pos )
: s1471( s307, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s157 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s64( pst, &s157, &pend ) ) {
if( errno == ERANGE )
throw new s17( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s25 );
throw new s17( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s21 );}
s1414();}
else
s157 = s307->TR().s1409();
s364 = (int)s157;
pos = pend ? ( pend - pst ) : string::npos;
s513 = proto->s367();}
s502* s361::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
s502* s718 = NULL;
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
if( s == L"-0" )
return s1696;
size_t pos = 0;
try {
s718 = new s361( s307, s, pos );}
catch( s17* e ) {
if( e->which() == (uint32_t)s17::s18::s25 )
s718 = NULL;
else
throw e;}}
else if( s.find( L"Int(" ) == 0 ) {
size_t pos = 0;
s718 = new s361( s307, s.substr( 4, s.size() - 5 ), pos );}
else if( s.find( L"Int" ) == 0 ) {
s718 = s371( NULL, std::vector<s278*>(), &s737 );}
return s718;}
void s361::s365(){
s307->TR().s1302( s513, s7::s1585, s1687::s1426 );
s307->TR().s1302( s513, s7::s1699, s1687::s1724 );
s1471<int32_t, s361>::s365();
s363 = s1471<int32_t, s361>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s361::s1385, s1701,
{ s1240(), s1240( { s1687::s1426 } ) }, 0, 1 ) ) );
s307->TR().s1708( s513, s1465::proto->s367() );}
s502* s361::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
size_t pos = 0;
return new s361( s307, L"", pos );}
void s361::s520( s502* s962 ){}
inline bool
s361::s1716( s1172 s647 ) const{
if( ( s647 == s1702 && s364 >= 0 ) ||
( s647 == s1475 && s364 >= 0 && s364 <= 255 ) )
return true;
return s278::s1716( s647 );}
s278* s361::s350() const{
return new s361( *this );}
void s361::s372( s278* p ) const{
if( p->s367() == proto->s367() )
*((s361*)p)->s373() = s364;
else if( p->s367() == s1701 )
*((s1465*)p)->s373() = s364;
else if( p->s367() == s1702 )
*((s1704*)p)->s373() = s364;
else if( p->s367() == s803->s367() )
*( (s376*)p )->s373() = (s364 != 0);
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = (double)s364;
else
throw new s17( L"No conversion to type " + s369() );}
inline void s361::s1385( s502** s281, size_t s518 ){
s361* plv = new s361( ( (s361*)s281[1] )->s307, 0 );
s361& lv = *plv;
if( s518 == 2 )
lv.s364 = 0;
else if( s518 == 3 ) {
s502* p = s281[2];
if( p->s367() == s361::proto->s367() )
lv.s364 = *( (s361*)p )->s373();
else if( p->s367() == s859->s367() )
lv.s364 = ( s1558 )*( (s374*)p )->s373();
else if( p->s367() == s803->s367() )
lv.s364 = ( s1558 )*( (s376*)p )->s373();
else
throw new s17( L"no conversion to Int from type: " + p->s369() );}
else
throw new s17( L"unknown parameters to Int() constructor" );
lv.s1414();
s281[0] = plv;}
s1465::s1465( s269* s307 )
: s1471( s307, NULL, NULL ){
if( proto.s13() )
s513 = 0;
else
s513 = proto->s367();
s364 = s307->TR().s1409();
setWh( s7::s943 );}
s1465::s1465( s269* s307, int64_t i )
: s1471( s307, NULL, NULL ){
if( proto.s13() ) {
s513 = 0;
setWh( s7::s943 );}
else {
s513 = proto->s367();
s364 = i;
s1414();}}
s1465::s1465( const s1465& r )
: s1471( r ){}
s1465::s1465( s269* s307, const std::wstring& s, size_t& pos )
: s1471( s307, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s157 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1719( pst, &s157, &pend ) ) {
if( errno == ERANGE )
throw new s17( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s25 );
throw new s17( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s21 );}
s1414();}
else
s157 = s307->TR().s1409();
s364 = (int64_t)s157;
pos = pend ? ( pend - pst ) : string::npos;
s513 = proto->s367();}
void s1465::s365(){
s1471<int64_t, s1465>::s365();
s363 = s1471<int64_t, s1465>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s1465::s1385, s1701,
{ s1240(), s1240( { s1687::s1426 } ) }, 0, 1 ) ) );
s307->TR().s1302( s513, s7::s1585, s1687::s1426 );
s307->TR().s1302( s513, s7::s1699, s1687::s1724 );}
s502* s1465::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
size_t pos = 0;
return new s1465( s307, L"", pos );}
void s1465::s520( s502* s962 ){}
s278* s1465::s350() const{
return new s1465( *this );}
void s1465::s372( s278* p ) const{
if( p->s367() == proto->s367() )
*((s1465*)p)->s373() = s364;
else if( p->s367() == s1285 )
*((s361*)p)->s373() = (s361::s1558)s364;
else if( p->s367() == s1702 )
*((s1704*)p)->s373() = s364;
else if( p->s367() == s803->s367() )
*( (s376*)p )->s373() = (s364 != 0);
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = (double)s364;
else
throw new s17( L"no conversion from " + s369() + L"to " + p->s369() );}
s502* s1465::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1465( s307, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1465( s307, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s371( NULL, std::vector<s278*>(), &s737 );}
return 0;}
inline void s1465::s1385( s502** s281, size_t s518 ){
s1465* plv = new s1465( ( (s1465*)s281[1] )->s307, (s1558)0 );
s1465& lv = *plv;
if( s518 == 2 )
lv.s364 = 0;
else if (s518 == 3){
s502* p = s281[2];
if( p->s367() == s361::proto->s367() )
lv.s364 = *( (s361*)p )->s373();
else if( p->s367() == s859->s367() )
lv.s364 = (s1558)*( (s374*)p )->s373();
else if( p->s367() == s803->s367() )
lv.s364 = (s1558)*( (s376*)p )->s373();
else
throw new s17( L"no conversion to Long from type: " + p->s369() );}
else
throw new s17( L"unknown parameters to Long() constructor" );
lv.s1414();
s281[0] = plv;}
s1704::s1704( s269* s307 )
: s1471( s307, NULL, NULL ){
if( proto.s13() )
s513 = 0;
else
s513 = proto->s367();
s364 = s307->TR().s1409();
setWh( s7::s943 );}
s1704::s1704( s269* s307, int64_t i )
: s1471( s307, NULL, NULL ){
if( proto.s13() ) {
s513 = 0;
setWh( s7::s943 );}
else {
s513 = proto->s367();
s364 = i;
s1414();}}
s1704::s1704( const s1704& r )
: s1471( r ){}
s1704::s1704( s269* s307, const std::wstring& s, size_t& pos )
: s1471( s307, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s157 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1720( pst, &s157, &pend ) ) {
if( errno == ERANGE )
throw new s17( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s25 );
throw new s17( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s21 );}
s1414();}
else
s157 = s307->TR().s1409();
s364 = (uint64_t)s157;
pos = pend ? ( pend - pst ) : string::npos;
s513 = proto->s367();}
void s1704::s365(){
s1471<s1558, s1704>::s365();
s363 = s1471<s1558, s1704>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s1704::s1385, s1702,
{ s1240(), s1240( { s1687::s1426 } ) }, 0, 1 ) ) );
s363.insert( make_pair( L"abs", new s352( L"abs", &s1704::s420, s1702,
{ s1240(), s1240( { s1687::s1426 } ) }, 0, 1 ) ) );
s363.insert( make_pair( L"dif", new s352( L"dif", &s1704::s405, s1702,
{ s1240(), s1240( { s1687::s1426 } ) }, 0, 1 ) ) );
s307->TR().s1302( s513, s7::s1585, s1687::s1426 );
s307->TR().s1302( s513, s7::s1699, s1687::s1724 );}
s502* s1704::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
size_t pos = 0;
return new s1704( s307, L"", pos );}
void s1704::s520( s502* s962 ){}
s278* s1704::s350() const{
return new s1704( *this );}
void s1704::s372( s278* p ) const{
if( p->s367() == proto->s367() )
*((s1704*)p)->s373() = s364;
else if( p->s367() == s1701 )
*((s1465*)p)->s373() = s364;
else if( p->s367() == s1285 )
*((s361*)p)->s373() = (s361::s1558)s364;
else if( p->s367() == s803->s367() )
*( (s376*)p )->s373() = (s364 != 0);
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = (double)s364;
else
throw new s17( L"no conversion from " + s369() + L"to " + p->s369() );}
s502* s1704::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1704( s307, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1704( s307, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s371( NULL, std::vector<s278*>(), &s737 );}
return 0;}
inline void s1704::s1385( s502** s281, size_t s518 ){
s1704* plv = new s1704( ( (s1704*)s281[1] )->s307, (s1558)0 );
s1704& lv = *plv;
if( s518 == 2 )
lv.s364 = 0;
else if (s518 == 3){
s502* p = s281[2];
if( p->s367() == s361::proto->s367() )
lv.s364 = *( (s361*)p )->s373();
else if( p->s367() == s1465::proto->s367() )
lv.s364 = *( (s1465*)p )->s373();
else if( p->s367() == s859->s367() )
lv.s364 = (s1558)*( (s374*)p )->s373();
else if( p->s367() == s803->s367() )
lv.s364 = (s1558)*( (s376*)p )->s373();
else
throw new s17( L"no conversion to ULong from type: " + p->s369() );}
else
throw new s17( L"unknown parameters to ULong() constructor" );
lv.s1414();
s281[0] = plv;}
s1454::s1454( s269* s307 )
: s1471( s307, NULL, NULL ){
if( proto.s13() )
s513 = 0;
else
s513 = proto->s367();
s364 = (s1558)s307->TR().s1409();
setWh( s7::s943 );}
s1454::s1454( s269* s307, tdbyte_t i )
: s1471( s307, NULL, NULL ){
if( proto.s13() ) {
s513 = 0;
setWh( s7::s943 );}
else {
s513 = proto->s367();
s364 = i;
s1414();}}
s1454::s1454( const s1454& r )
: s1471( r.s307, r.ns, NULL ){
wh = r.wh;
s513 = r.s513;}
s1454::s1454( s269* s307, const std::wstring& s, size_t& pos )
: s1471( s307, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s157 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s64( pst, &s157, &pend ) )
throw new s17( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s17::s18::s21 );
setWh( s7::s942 );}
else
s157 = s307->TR().s1409();
s364 = (int)s157;
pos = pend ? ( pend - pst ) : string::npos;
s513 = proto->s367();}
void s1454::s365(){
s1471<tdbyte_t, s1454>::s365();
s363 = s1471<tdbyte_t, s1454>::s357();
s307->TR().s1302( s513, s7::s1585, s1687::s1426 );
s307->TR().s1302( s513, s7::s1699, s1687::s1724 );}
s502* s1454::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
size_t pos = 0;
return new s1454( s307, L"", pos );}
void s1454::s520( s502* s962 ){}
s278* s1454::s350() const{
return new s1454( *this );}
void s1454::s372( s278* p ) const{
if( p->s367() == proto->s367() )
*((s361*)p)->s373() = s364;
else if( p->s367() == s1701 )
*((s1465*)p)->s373() = s364;
else if( p->s367() == s1702 )
*((s1704*)p)->s373() = s364;
else if( p->s367() == s803->s367() )
*( (s376*)p )->s373() = (s364 != 0);
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = (double)s364;
else
throw new s17( L"no conversion from " + s369() + L"to " + p->s369() );}
s502* s1454::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1454( s307, s, pos );
}*/
if( s737.s1476() == s367() )
return new s1454( s307, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1454( s307, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s371( NULL, std::vector<s278*>(), &s737 );}
return 0;}
const wstring s489 = L"";
uint32_t s279::s1532 = 0;
s501 s720;
s279::s279( s269* s307, s1172 s355, s490 pc/* = s491*/, const s270* ast_ )
: s502( s307, pc, ast_, NULL ), s653(NULL), s654(NULL), s362( s489 ), //s662( s720 ),
s657( NULL ), s1531( ++s1532 ){
s653 = this;
s513 = s355;}
s279::s279( const s279& proto, const s270* ast_ )
: s502( proto.s307, proto.s512, ast_, proto.ns ), s653( &proto ), s654(NULL), s362( proto.s285 ),
s657( proto.s657 ), //s662( s720 ),
s659( proto.s659 ), s1531( ++s1532 ){
s513 = proto.s513;
if( s512 == s497 )
s512 = s499;
if( proto.s654 )
proto.s654->s673( this );
proto.s656.copy( s656, this, NULL, s501::s151 );
for( size_t n = 0; n < s659.size(); ++n )
s658.push_back( s656.get( s659[n] ) );}
s279::s279( const wstring& s709, s269* s307, s490 pc, const s270* ast_ )
: s502( s307, pc, ast_, NULL ), s653(NULL), s654(NULL), s362( s489 ), s285( s709 ),
s657( NULL ), s1531( ++s1532 )//, s662( *new s501() )
{
s653 = this;}
s279::s279( s270& s737, s269* s307, s490 pc, s502* ns_, s560 am, 
s651& cl, s650& cnl, s652& al )
: s502( s307, pc, &s737, ns_ ), s653(NULL), s654( NULL ), s362( s737.s306() ), s285( s737.s305() ),
s656( am ), s657( NULL ), s1531( ++s1532 ) //,s662( *new s501() )
{
if( s285.find( L" " ) != string::npos )
throw new s17( L"Malformed class name: " + s285 );
s653 = this;
if( pc == s497 ) {
wstring anc = L"";
try {
const s270* s726 = s737.s299( s7::s486 );
anc = s726->s298();}
catch( s17* e ) {
if( e->which() != (uint32_t)s17::s18::s24 )
throw e;}
cnl.push_back( make_pair( s737.s306(), anc ) );
if( cl.find( s737.s306() ) != cl.end() )
throw new s17( L"class already exists: " + s737.s306() );
cl.insert(make_pair(s737.s306(), this));}
if( al.find( s737.s306() ) != al.end() )
throw new s17( L"object already exists: " + s737.s306() );
al.insert(make_pair(s737.s306(), &s737));
s527( L"proto" );
s270::s282& s738 = s737.s300();
s270::s282::iterator it = s738.begin();
vector<pair<wstring,wstring>> s727;
for( ; it != s738.end(); ++it ) {
if( it->second->s304() == s231 ) {
if( it->first == s7::s486 ) {
s655 = it->second->s298();}}
else if( it->second->s304() == s233 ) {
wstring s688 = it->first;
s534 pv = s537;
am = s532;
size_t s722 = s688.find_first_of( s4::s50 );
if( s722 != string::npos ) {
vector<wstring> s721;
s4::s59( it->first, wstring( 1, s688[s722] ), s721 );
if( s721.size() > 3 )
throw new s17( L"malformed block name: " + it->first );
if( s721[0] == s7::s467 || s721.size() == 3 ) {
pc = s497;
if( s721.size() == 3 ) {
if( s721[0] == s7::s464 )
am = s531;
else if( s721[0] == s7::s466 )
am = s533;
else if( s721[0] != s7::s465 )
throw new s17( L"invalid access mode name: " + it->first );
s688 = s721[2];}
else
s688 = s721[1];
if( s738.find( s688 ) != s738.end() )
throw new s17( L"duplicated object name: " + it->first );
it->second->s301( s688 );
s727.push_back( make_pair( it->first, s688 ) );}
else if( s721[0] == L"access" && ( s721[1] == L"allow" || s721[1] == L"deny" )) {
if( s721[1] == L"allow" )
pv = s536;
pc = s498;}
else
throw new s17( L"unknown object type: " + s721[0] );}
if( pc == s498 ) {
s656.s573( pv, it->second );}
else {
s279* ob = new s279( *it->second, s307, s497, this, am, cl, cnl, al );
s656.s565( ob->s306(), ob );}}}
for( size_t n = 0; n < s727.size(); ++n ) {
auto it = s738.find( s727[n].first );
s738.insert(make_pair(s727[n].second, it->second ));
s738.erase( it );}}
s502* s279::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
return s664( s737, s613, s347 );}
void s279::s674( const s501& s281 ){}
bool
s279::s522( const s502* s523 ) const{
if( s523->s367() == s367() )
return true;
if( s654 )
return s654->s522( s523 );
return false;}
bool
s279::s770( const wstring& f ) const{
return s656.s160( f );}
void s279::s158( s270& s737 ){
s270::s282& s738 = s737.s300();
s270::s282::iterator it = s738.begin();
for( ; it != s738.end(); ++it ) {
s270* node = it->second;
if( node->s304() == s231 ) {
wstring s78 = node->s306();
lang::s686( s78 );
if( s78 == s7::s459 )
s675( *node );
else if( s78 == s7::s486 )
s667( *node );
else if( s78 == s7::s1024 )
s1065( *node );
else {
size_t s722 = s78.find_first_of( s4::s50 );
bool s1348 = false;
if( s722 != string::npos ) {
vector<wstring> s721;
s4::s59( s78, wstring( 1, s78[s722] ), s721 );
if( s721.size() > 2 )
throw new s17( L"malformed object declaration: " + s78 );
if( s721[0] == s7::s1264 ) {
s1348 = true;}}
s502* dv = s307->TR().s542( *node, this, s285 );
dv->s527( node->s306() );
dv->s1412( s1348 );
try {
s656.s565( node->s306(), dv );}
catch( s17* e ) {
if( e->which() == (uint32_t)s17::s18::s22 ) {
e->s31( L"Symbol already defined: " + s285 + L"::" + node->s306() );}
throw e;}
s658.push_back( dv );
s659.push_back( node->s306() );}}
else if( node->s304() == s233 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s279* ob = (s279*)s656.get( it->first );
ob->s158( *it->second );}}
else if( node->s304() == s234 ) {}}
it = s738.begin();
for( ; it != s738.end(); ++it ) {
s270* node = it->second;
if( node->s304() == s232 ) {
try {
s507 func = s616::s624( *node, s307, this,
node->s306(), s285 );
s656.s565( func->s306(), func.s16<s502*>() );
s658.push_back( func );
s659.push_back( func->s306() );}
catch( TDException* e ) {
e->s1188( TDException::Stage::s1133 );
e->s31( L"while compiling function '" +s285 + L"::" + node->s306() + L"'" );
s1116.s1066( e->Msg( 0 ) );}}}
if( s512 == s497 ) {
s1527* s1535 = new s1527( s307, this, NULL, vector<s278*>(), NULL );
s656.s565( s7::s1525, s1535 );
s658.push_back( s1535 );
s659.push_back( s7::s1525 );}}
void s279::s520( s502* s962 ){
if( s512 == s497 || s512 == s498 ) {
if( s655.size() ) {
s654 = (s279*)s307->s228( s655, s962->s900() );
s654->s657->copy( *s657 );}
if( s657 )
s657->s520( s307, s285 );
else
s657 = s653->s657;
s656.s520( s962, (s512 == s497));}
else {
if( s656.s160( s7::s445 ) ) {
vector<s503*> s281;
s281.push_back( this );
s912* p = (s912*) s656.get( s7::s445 );
p->s520( s962->s900(), true );
p->s517( (s502**)&s281[0], 1 );}}}
void s279::s673( s279* s676 ) const{
if( s654 )
s654->s673( s676 );}
void s279::s675( s270& s737 ){
if( !s657 )
s657 = new s575();
s657->s578( s737.s298() );
return;}
void s279::s668( const wstring& s347,	vector<wstring>& s157 ){
s656.s557( s347, s157 );}
void s279::s579( const wstring& s78, const wstring& s582 ){
if( !s657 )
s657 = new s575();
s657->s579( s78, s307, s582 );}
void s279::s667( s270& s737 ){
s654 = (s279*)s307->s228( s655, s285 );}
void s279::s1065( s270& s737 ){
wstring s1094 = L"wrong syntax of class attributes: " + s737.s298();
s505 dv = s307->TR().s542( s737, this, s285 );
if( dv->s367() != s765->s367() )
throw new s17( s1094 );
vector<s504>& v = dv.s16<s324*>()->s329();
for( auto s_ : v ) {
wstring s = s_.s16<s375*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s17( s1094 );
wstring cat = s4::s54( s.substr( 0, pl ), s4::s50 );
vector<wstring> s157;
s4::s59( s.substr( pl + 1 ), L",", s157 );}}
bool s279::s580( const wstring& sym_, 
s387* ref, const wstring& s347 ) const{
bool s718 = false;
wstring sym = sym_;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s719 = sym_.substr( 0, pl );
s279* ob = ((s279*)s671( s719, s347, false ));
if( ob ) {
s718 = ob->s580( sym, ref, s347 );}
else {
s718 = s657->s580( sym, ref );}}
else {
s279* ob = ((s279*)s671( sym, s347, false ));
if( ob ) {
if( !ref->s396() )
ref->s398( ( s502* )this );
ref->s395( s669( sym ), ob );
s718 = true;}
else {
if( s657 )
s718 = s657->s580( sym, ref );}}
return s718;}
size_t s279::s669( const std::wstring& s677 ) const{
for( size_t n = 0; n < s658.size(); ++n ) {
if( s659[n] == s677 )
return n;}
throw new s17( L"3: Symbol does not exist: " + s677 );}
s278* s279::s623( size_t off ){
return s658[off];}
void s279::s922( const std::wstring& s78, s502* s364 ){
s656.s565( s78, s364 );
s658.push_back( s364 );
s659.push_back( s78 );}
s502* s279::s671( const wstring& sym, const wstring& s347, 
bool s544/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s279* mod = (s279*) s656.get( smod, s544 );
if( !mod )
return NULL;
return mod->s671( sym1, s347, s544 );}
wstring sym1 = sym;
if( sym.size() > 2 && ( sym.find( L"()" ) == sym.size() - 2 ) )
sym1 = sym.substr( 0, sym.size() - 2 );
s505 s718 = s656.get( sym1, false );
if( !s718 && s544 )
throw new s17( L"4: Symbol does not exist: " + sym, 
(uint32_t)s17::s18::s24 );
if( s718 && !s672( sym1, s347 ) ) {
if( s544 )
throw new s17( L"4: Symbol not found: " + sym,
(uint32_t)s17::s18::s24 );
s718 = NULL;}
return s718;}
bool s279::s672( const wstring& sym, const wstring& s519 ) const{
return s656.s574( sym, s519 );}
s1172 s279::s402( const wstring& s358 ) const{
s502* s723 = s656.get( s358 );
s1172 s718 = s723->s367();
if( s718 == 0 ) {
s723->s520( (s279*)this );
s718 = s723->s367();}
return s718;}
s502* s279::s664( const s270& s737, s502* s613, const std::wstring& s347 ){
vector<wstring> s724;
vector<s278*> s281;
s279* s718 = new s279( *this );
size_t pos = s737.s298().find( L"(" );
size_t pos_ = pos;
s270::s295( s737.s298(), pos, s724 );
if( s724.size() ) {
s616* s725 = (s616*) s656.get( s7::s444, false );
if( !s725 )
throw new TDException( 0, s1020, &s737, 
L"Arguments passed to a class without init function." );
else {
wstring str = s737.s298();
if( str[pos_ + 1] != L' ' )
str.insert( pos_ + 1, L" " );
str = str.substr( pos_ ).insert( 1, s7::s444 );
s270* ast_ = new s270( s7::s445, s145( str ) );
s509 cs = (s585*)s278::s525( *ast_, s307, s718, s347 );
s616* td = s616::s625(
cs, s307, s718, (s616*)s718, s285 );
s718->s656.s565( s7::s445, td );}}
return s718;}
s502* s279::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
vector<wstring> s724;
vector<s278*> s281;
s279* s718 = new s279( *this );
if( l.size() ) {
s616* s725 = (s616*)s656.get( s7::s444, false );
if( !s725 )
throw new TDException( 0, s1020, ast_,
L"Arguments passed to a class without init function." );
else {
s509 cs = new s585( s307, s7::s444, l, ast_ );
cs->s627().insert( cs->s627().begin(), s718 );
s616* td = s616::s625(
cs, s307, s718, (s616*)s613, s285 );
s718->s656.s565( s7::s445, td );}}
s718->s520( s613 );
return s718;}
std::wstring s279::s305() const{
return /*s284 + L"::" +*/ s285;
}
s502* s279::s359( const std::wstring& s709, const std::wstring& s347,
bool s544 /*= true*/ ) const
{
s387 ref( s709, s307 );
if( !s580( s709, &ref, s347 ) )
return NULL;
return ref.s394();}
s278* s279::s350() const{
return new s279( *this );}
void s279::s372( s278* p ) const{
throw new s17( L"" );
vector<wstring> fields;
s656.s569( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s502*)s656.get( fields[n] ))->s372( p );}
size_t s279::s331() const{
return (size_t)this;}
bool s279::operator==( const s502* p ) const{
return (this == p);}
bool s279::operator<( const s502* p ) const{
return false;}
wstring s279::to_wstring() const{
return L"";}
void s279::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s362;
if( s512 == s497 ) s362 = L"Class";
else if( s512 == s498 ) s362 = L"Module";
else if( s512 == s499 ) s362 = L"Object";
else s362 = L"ERROR";
buf << s4::fill_n_ch( L' ', s202 ) << s362 << L" : " << s285 << L"/" << s388 << endl;
s656.s311( pd, s202 + s435 );}
s616* s616::s624( const s270& s737, s269* s307, s279* obj,
const wstring& s285, const wstring& s582 ){
const s270::s282& s738 = s737.s300();
size_t s733 = s738.size();
std::vector<s278*> s281;
for( size_t n = 0; n < s733; ++n ) {
s270::s282::const_iterator it = s738.find( std::to_wstring( n ) );
if( it->second->s298() == s7::s1029)
s281.push_back( s951 );
else
s281.push_back( s278::s525( *it->second, s307, obj, s582 ) );}
Transd* s718 = NULL;
size_t s722 = s285.find_first_of( s4::s50 );
if( s722 != string::npos ) {
vector<wstring> s721;
s4::s59( s285, wstring( 1, s285[s722] ), s721 );
if( s721.size() > 2 )
throw new s17( L"malformed function name: " + s285 );
if( s721[0] == s7::s447 ) {
s718 = new s629( s307, obj, NULL, s281, &s737 );
s718->s285 = s721[1];}
else if( s721[0] == s7::s448 ) {
s718 = new s912( s307, obj, NULL, s281, &s737 );
s279* pAnc = (s279*)s307->s228( obj->s666(), s582 );
((s629*)pAnc->s359( s721[1], s582 ))->s678( obj->s367(),
s718 );
s718->s285 = s721[1];
s718->s619( s598 );}
else
throw new s17( L"malformed function name: " + s285 );}
else {
s718 = new s912( s307, obj, NULL, s281, &s737 );
s718->s285 = s285;}
return s718;}
s585* s616::s1237( const s270& s737, s269* s307, s502* obj,
const wstring& s582 ){
const s270::s282& s738 = s737.s300();
size_t s733 = s738.size();
wstring s626 = s737.s298();
std::vector<s278*> s281;
s585* s718 = NULL;
try {
for( size_t n = 0; n < s733; ++n ) {
s270::s282::const_iterator it = s738.find( std::to_wstring( n ) );
it->second.s16<s270*>()->s276( L"ownerType", L"CallSite" );
it->second.s16<s270*>()->s276( L"ownerName", s626 );
if( it->second->s298() == s7::s1029 )
s281.push_back( s951 );
else
s281.push_back( s278::s525( *it->second, s307, obj, s582 ) );}
s718 = new s585( s307, s626, s281, &s737 );}
catch( s17* e ) {
throw e->s31( L"\nwhile processing '" + s626 + L"' function call" );}
return s718;}
void s585::s520( s502* s962 ){
return;
for( size_t n = 0; n < s281.size(); ++n ) {
s281[n]->s520( s962 );}}
s278* s585::s350() const{
return new s585( *this );}
s616* s616::s625( s585* cs, s269* s307, s502* s613, s616* s220, 
const wstring& s582 ){
wstring s626 = cs->s306();
wstring s740 = s613 ? s613->s305() : L"::";
s504 s739 = NULL;
std::vector<s278*>& s281 = cs->s627();
s507 s742 = NULL;
size_t pl = s626.find( L"<" );
if( pl == string::npos ) {
auto s1626 = s1542.find( s626 );
if( s1626 != end( s1542 ) && BIFuncs1v[s1626->second] )
return s307->s219( s1626->second, cs->s627(), s613, s220, cs->s628() );
s278* par = NULL;
int s1534 = 0;
s1529:
if( s281.size() ) {
par = s281[s1534];
s490 pc = par->s514();
if( pc == s493 ) {
try {
par->s520( s220 );}
catch( TDException* e ) {
if( e->Category() != s1018 || ( 
((s387*)par)->s644()[0] != L':' && ( (s387*)par )->s644().back() != L':' ) )
throw e->s31( L"while compiling function '" + s626 + L"'" );
s1534++;
goto s1529;}
if( ( (s387*)par )->s397().s14() ) {
if( ( (s387*)par )->s644() == s7::s446 )
par = s613;
s739 = ( (s387*)par )->s393();}}
else {
if( pc == s496 ) {
s509 cs = new s585( *(s585*)par );
par = s625( cs, s307, s613, s220, s582 );
( (s616*)par )->s520( s740, false );}
else {
par->s520( s220 );}}
if( par->s514() == s493 /*||  par->s514() == s1505*/ ) {
(void)0;}
else if( par->s514() == s1174 || par->s514() == s500 )
s739 = NULL;
else {
s739 = par->s516();}
s281[s1534] = par;}
else {
s742 = (s616*)s613->s359( s626, s740, false );
if( !s742 )
throw new s17( L"Procedure is not resolved: " + s626 );}
if( s1626 != end( s1542 ) )
return s307->s219( s1626->second, s281, s613, s220, cs->s628() );}
else {
wstring s647 = s626.substr( pl + 1, s626.size() - pl - 2 );
s626 = s626.substr( 0, pl );
try {
s1172 pt = s307->TR().s1111( s647, false );
if( !pt ) {
s869::Cont s1434;
pt = s765->s1339( s647, s1434 );}
s739 = s307->TR().s1108( pt )->s371( s220, s281 );}
catch( s17* e ) {
if( 1 || e->which() != (uint32_t)s17::s18::s24 )
throw e->s31( L"\nwhile compiling '" + s626 + L"' function " );
s1036 ast2 = new s270( s647 + L"()", cs->s628()->Nqj() );
s739 = s307->TR().s542( *ast2, s613, s582 );}
s281.insert( s281.begin(), s739 );}
s616* s718 = NULL;
s507 s743 = NULL;
s1267 s1386;
if( !s742 )  {
s490 s746 = s739->s514();
if( s746 == s493 ) {
s387* ref = (s387*)s739.s16<s503*>();
s739 = (s502*)ref->s524();
s746 = s739->s514();}
try {
if( s746 == s499 || s746 == s498 )
s743 = (s616*)s739.s16<s279*>()->s359( s626, s740, false );
else if( s746 == s492 )
s1386 = s739.s16<s351*>()->s1341( s626 );}
catch( s17* e ) {
if( e->which() != (uint32_t)s17::s18::s24 )
throw;}
if( !s743 && !s1386.s354 )
s742 = (s616*)s613->s359( s626, s740, false );
if( !( s1386.s354 || s742 || s743 ) )
throw new s17( L"Method is not resolved: " + s626 );}
if( s1386.s354 ) {
s718 = new s911( s307, s220, s281,	s1386.s353, s626, cs->s628() );
s718->s599 = s590;}
else if( s742 ) {
s718 = new s912( *s742.s16<s912*>(), s613, s220, s281, cs->s628() );
s718->s599 = s591;}
else if( s743 ) {
if( s626 == L"new" ) {
s718 = new s1527( *s743.s16<s1527*>(), s613, s220, s281,
cs->s628() );}
else {
s9<s912> td = ( (s912*)s743->s350() );
s281.erase( s281.begin() );
s718 = new s912( *td, s739.s16<s279*>(), s220, s281, cs->s628() );}
if( s743->s620() == s597 )
s718->s599 = s593;
else
s718->s599 = s592;}
s718->s285 = s626;
return s718;}
void s616::s1393( vector<s278*>& s281, const vector<wstring>& s1354 ){
for( s278* p : s281 ) {
if( p->s514() == s493 )
( (s387*)p )->s1079( s1354 );}}
void s616::s1393( vector<s504>& s281, const vector<wstring>& s1354 ){
for( s278* p : s281 ) {
if( p->s514() == s493 )
( (s387*)p )->s1079( s1354 );}}
s616::s616( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l,
const s270* s737 )
: s279( s307, 0, s494, s737 ), s600( s596 ),
s611( NULL ),	s613( s617 ), s612( s618 ), past( s737 ){
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ((s502*)l[n]) == s951 ) {
if( l.size() == n )
throw new s17( L"malformed lambda definition" );
s513 = l[n + 1]->s367();
n += 2;
break;}
if( l[n]->s514() != s493 )
break;
s387* s78 = (s387*) l[n];
s502* ex = (s502*) l[n + 1];
if( ex->s514() != s492 && ex->s514() != s499 && 
ex->s514() != s498 && ex->s514() != s1397 )
throw new s17( L"incorrect syntax for lambda parameter " + s78->s644() +
L"; should be a type constructor.", (uint32_t)s17::s18::s21 );
s656.s565( s78->s644(), ex );
s607.push_back( (s502*)ex );
s658.push_back( (s502*)ex );
s659.push_back( s78->s644() );}
s609.insert( s609.end(), l.begin() + n, l.end() );}
s616::s616( const s616& right, s502* s617, s616* s618,
const std::vector<s278*>& s741, const s270* s737 )
: s279( right.s307, right.s513, right.s512, s737 ),  
s600( right.s600 ),	s611( NULL ), s613( s617 ), s612( s618 ), past( s737 ){
s513 = right.s513;
s599 = right.s599;
s658 = right.s658;
s659 = right.s659;
s656 = right.s656;
s607 = right.s607;
s285 = right.s285;
if( s741.size() ) {
s281.assign( s741.begin(), s741.end() );
for( size_t n = 0; n < s281.size(); ++n ) {
s656.s565( s659[n], s281[n].s16<s502*>(), s501::s151 );
s658[n] = s281[n];}}
else
s281.assign( right.s281.begin(), right.s281.end() );
s609 = right.s609;}
s911::s911( s269* s307, s616* s618, const vector<s278*>& l,
/*s643 s744,*/ s1172 s745, const wstring& s1728, const s270* s737 )
: s616( s307, s618, s618, s590, L"", s737 ), s1309( true )/*,
s586( s744 )*/
{
s285 = s1728;
s600 = s596;
s513 = s745;
s281.assign( l.begin(), l.end() );}
s912::s912( const s912& right, s502* s617, s616* s618,
const std::vector<s278*>& s741, const s270* s737 )
: s616( right.s307, s617, s618, s592, L"", s737 ){
TDException s1061( s7::CLTransdFT_ctor1, s1020, s737 );
s599 = right.s599;
s513 = right.s513;
s658 = right.s658;
s659 = right.s659;
s656 = right.s656;
s607 = right.s607;
s600 = right.s600;
s285 = right.s285;
s611 = NULL;
for( size_t n = 0; n < s607.size(); ++n ) {
if( s741.size() > n ) {
s281.push_back( s741[n] );}
else
s281.push_back( s607[n]->s350() );}
if( s741.size() > s281.size() ) 
throw s1061.s1099( L"too many arguments: expected " + std::to_wstring( s281.size() ) + L", received " +
std::to_wstring( s741.size() ));
/*for( size_t n = 0; n < s281.size(); ++n ) {
s656.s565( s659[n], s281[n].s16<s502*>(), s501::s151 );
s658[n] = s281[n];
}*/
s609 = right.s609;}
s1527::s1527( const s1527& right, s502* s617, s616* s618,
const std::vector<s278*>& s741, const s270* s737 )
: s912( right.s307, s617, s618, s741, s737 ){
s281.assign( s741.begin(), s741.end() );
s513 = right.s513;
s611 = (s502*)s741[0];}
s616::~s616(){
/*	for( size_t n = 0; n < s281.size(); ++n ) {
delete s281[n].s16<s503*>();
}*/
}
s585::s585( s269* pass_, const std::wstring& s194, const vector<s278*>& l, 
const s270* ast_ )
: s278( pass_, s496 ), s626( s194 ), past( (s270*)ast_ ){
s281.assign( l.begin(), l.end() );}
s585::s585( const s585& right )
: s278( right.s307, s496 ), s626( right.s626 ), past( right.past ){
for( size_t n = 0; n < right.s281.size(); ++n ) {
s281.push_back( right.s281[n]->s350() );}}
wstring s616::s900() const{
if( s613.s14() )
return s613->s305();
else if( s599 == s590 )
return L"::";
else
throw new s17( L"Cannot get module name." );}
s278* s616::s918( s278* par ){
s278* s718;
if( par->s514() == s496 ) {
s509 cs = new s585( *((s585*)par) );
s718 = s625( cs, s307, s613, this, s305() );
((Transd*)s718)->s520( s703, false );}
else if( 1 && par->s514() == s492 ) {
par->s520( /*s613*/ this );
return par;}
else
return par;
return s718;}
void s616::s614(const wstring& s347){
for( size_t n = 0; n < s607.size(); ++n )
s607[n]->s520( /*s612*/s613 );
}
void s616::s520( const wstring& s347, bool proc/*=false*/ )
{
s703 = s347;
if( s613 && (s613->s514() == s498 || s613->s514() == s497 )) {
s614( s347 );
if( s613->s514() == s497 )
return;}
for( size_t n = 0; n < s281.size(); ++n ) {
s504 par = s281[n];
if( s599 == s590 && n == 1 ) {
s616::s1393( s281, ((s351*)s281[0]->s516())->s1335( s285 ) );}
if( par->s514() == s493 ) {
if( par.s16<s387*>()->s397().s13() )
par.s16<s387*>()->s520( this );
s608.push_back( NULL );}
else if( par->s514() == s1174 || par->s514() == s500 )
s608.push_back( /*NULL*/ par.s16<s502*>() );
else {
try {
s281[n] = s918( par );}
catch( s17* e ) {
throw e->s31( L"\nwhile linking '" + s285 + L"' function " );}
s608.push_back( s281[n]->s516() );}}
if( s599 == s589 ) {
if( s285 == s239 ) {
for( size_t n = 0; n < s281.size(); ++n ) {
s656.s565( s659[n], s281[n].s16<s502*>(), s501::s151 );
s281[n]->setWh( s7::s942 );
s658[n] = s281[n];}}
for( size_t n = 0; n < s609.size(); ++n ) {
if( s609[n]->s514() == s496 ) {
s509 cs = new s585( *s609[n].s16<s585*>() );
s609[n] = s625( cs, s307, s613, this, s613->s305() );}
else if( s609[n]->s514() == s493 )
s609[n].s16<s387*>()->s520( s612 );
else if( s609[n]->s514() != s494 )
s609[n]->s520( s612 );
else // lambda - ?
throw new s17( L"unhandled expression" );}
for( auto it : s609 ) {
if( it->s514() == s494 )
it.s16<Transd*>()->s520( s347, true );}
if( !s513 && s609.size() ) {
s513 = s609.back()->s367();}}
if( s513 ) {
s611 = s307->TR().s542( s367(), s613, s347 );
s611->s520( s612 );
s611->setWh( s7::s942 );
s608.insert( s608.begin(), s611 );
if( s281.size() ) {
s605 = (s503**)&s281[0];
nlocs = s281.size();
s604 = &s608[0];
s518 = s608.size();}
else {
s605 = NULL;
s604 = NULL;
nlocs = s518 = 0;}}
s1077.resize( s608.size() );}
void s911::s520( const wstring& s347, bool proc/*=false*/ )
{
s703 = s347;
TDException s1061( s7::s1244, s1255, past );
s616::s520( s347, proc );
s278* par = s281[0]->s516();
s351* s739 = NULL;
s1267 s1386;
s490 s746 = par->s514();
s1240 ap;
if( s746 == s493 ) {
s387* ref = (s387*)par;
s505 pobj = ref->s393();
s746 = pobj->s514();
s739 = pobj.s16<s351*>();
ap = s1240( s281, s739 );
try {
s1386 = s739->s1336( s285, ap );}
catch( s17* e ) {
if( e->which() == (uint32_t)s351::s352::s1256::s1323 ) {
s1386 = s739->s1331( s285, ap /*s1388, s281*/ );
}}}
else {
s739 = ( (s351*)par );
ap = s1240( s281, s739 );
try {
s1386 = ( (s351*)s739->s516() )->s1336( s285, ap/*s1388*/ );
}
catch( s17* e ) {
if( e->which() == (uint32_t)s351::s352::s1256::s1323 ) {
s1386 = ( (s351*)s739->s516() )->s1331( s285, ap/*s1388, s281*/ );
}}}
if( !s1386.s354 )
throw s1061.s1099( L"method is not resolved: " + par->s369() + L"::" + s285 + 
ap.s1496( s307 ) );
s513 = s1386.s353;
s586 = s1386.s354;
s1309 = s1386.s1309;
if( !s1309 && s281[0]->s1348() )
throw s1061.s1099( L"non-constant function is applied to a constant variable" );
if( s285 == L"new" )
s611 = s281[0].s16<s502*>();
if( s611.s13() ) {
s611 = s307->TR().s542( s367(), s613, s347 );
s611->s520( s612 );
s608.insert( s608.begin(), s611 );
if( s281.size() ) {
s605 = (s503**)&s281[0];
nlocs = s281.size();
s604 = &s608[0];
s518 = s608.size();}
else {
s605 = NULL;
s604 = NULL;
nlocs = s518 = 0;}}
s1077.resize( s608.size() );}
void s912::s520( const wstring& s347, bool proc/*=false*/ )
{
TDException s1061( s7::s1697, ECFailedInitializeObject, s628() );
s703 = s347;
if( s613->s514() == s498 || s613->s514() == s497 ) {
s614( s347 );
if( s613->s514() == s497 )
return;}
if( s281.size() > s658.size() )
throw new s17( L"too many arguments" );
for( size_t n = 0; n < s281.size(); ++n ) {
s504 par = s281[n];
if( par->s514() == s493 ) {
if( par.s16<s387*>()->s397().s13() )
par.s16<s387*>()->s520( /*this*/s612 );
}
else
s281[n] = s918( par );
if( !s307->TR().s1709( s281[n]->s367(), s607[n]->s367() ) )
throw s1061.s1099( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s607[n]->s369() + L"', received - '" + par->s369() + L"'" );}
for( size_t n = 0; n < s281.size(); ++n ) {
s656.s565( s659[n], s281[n].s16<s502*>(), s501::s151 );
s281[n]->setWh( s7::s942 );
s658[n] = s281[n];}
s507 s1533 = s612;
s612 = 0;
for( size_t n = 0; n < s609.size(); ++n ) {
if( s609[n]->s514() == s496 ) {
s509 cs = new s585( *s609[n].s16<s585*>() );
s609[n] = s625( cs, s307, s613, this, s613->s305() );}
else if( s609[n]->s514() == s493 )
s609[n].s16<s387*>()->s520( /*s612*/ s613 );
else if( s609[n]->s514() != s494 && 
s609[n]->s514() != s1396 )
s609[n]->s520( /*s612*/ s613 );
else // lambda - ?
throw new s17( L"unhandled expression" );}
for( auto it : s609 ) {
if( it->s514() == s494 )
it.s16<Transd*>()->s520( s347, true );}
s612 = s1533;
if( !s513 && s609.size() ) {
s513 = s609.back()->s367();
s611 = s307->TR().s542( s367(), s613, s347 );
s611->setWh( s7::s942 );
s608.insert( s608.begin(), s611 );}
if( s281.size() ) {
s605 = (s503**)&s281[0];
nlocs = s281.size();
s604 = NULL;// &s608[0];
s518 = s608.size();}
else {
s605 = NULL;
nlocs = s518 = 0;
s604 = NULL;}
s1077.resize( s608.size() );}
void s1527::s520( const wstring& s347, bool proc/*=false*/ )
{
if( s281.empty() )
s611 = s613;
else
s611 = s281[0].s16<s502*>();
s513 = s611->s367();}
void s616::s621( const vector<s504>& l ){
s281.clear();
s281.assign( l.begin(), l.end() );}
void s616::s622( const wstring& s347 ){
if( s599 != s590 && s599 != s589 && s281.size() > s658.size() )
throw new s17( L"too many arguments" );
for( size_t n = 0; n < s281.size(); ++n ) {
s278* par = s281[n];
if( par->s514() == s496 ) {
s509 cs = new s585( *(s585*)par );
par = s625( cs, s307, s613, this, s305() );
((s616*)par)->s520( s347, false );
s281[n] = par;}
if( s281[n]->s514() == s500 ) {
s608.push_back( s281[n]->s516() );}
else if( s281[n]->s514() != s493 ) {
if( ( s599 != s590 && s599 != s589 ) || s285 == s239 ) {
s658[n] = s281[n]->s516();
s658[n]->setWh( s7::s942 );
s656.s565( s659[n], s658[n].s16<s502*>(), s501::s151 );}
s608.push_back( s281[n]->s516() );}
else {
if( s599 != s590 && s599 != s589 ) {
s658[n] = s281[n].s16<s502*>();
s656.s565( s659[n], s281[n].s16<s387*>()->s393(), s501::s151 );}
if( s281[n].s16<s387*>()->s397().s13() ) {
s281[n].s16<s387*>()->s520( this );}
s608.push_back( NULL );}
if( s285 != s239 && n < s658.size() && n < s607.size() && !s658[n].s16<s502*>()->s522( (s502*)s607[n] ) )
throw new s17( L"wrong argument's type" );}
for( size_t n = 0; n < s658.size(); ++n ) {
if( s658[n]->s645() == s7::s943 )
throw new s17( L"parameter is not provided" );}}
void s616::s870( s901& s157 ) const{
for( size_t n = 0; n < s607.size(); ++n )
s157.push_back( make_pair( s659[n], s607[n] ) );}
s505 s616::s517( s502** s724, size_t s733 ){
s505 s718;
size_t shift = 0;
if( s599 == s592 || s599 == s590 || s599 == s589 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s605 + n ) ) {
s490 pc = ( ( s503* )*( s605 + n ) )->s514();
if( pc == s493 )
*( s604 + n + shift ) =
(s502*)( ( s387* )*( s605 + n ) )->s393();
else if( pc == s494 ) {
s1077[n+shift] = (s502*)( ( s616* )*( s605 + n ) )->s517( s724, s733 );
*( s604 + n + shift ) = s1077[n + shift];}
else if( pc == s492 )
*( s604 + n + shift ) = (s502*)*( s605 + n );}}
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s604, s518 );
if( s718->s645() < 0 )
break;}
return s718;}
s505 s911::s517( s502** s724, size_t s733 ){
s502* s718 = NULL;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s605 + n ) ) {
s490 pc = ( ( s503* )*( s605 + n ) )->s514();
if( pc == s493 || pc == s1505 )
*( s604 + n + shift ) =
(s502*)( ( s387* )*( s605 + n ) )->s393();
else if( pc == s494 ) {
s1077[n + shift] = (s502*)( ( s616* )*( s605 + n ) )->s517( s724, s733 );
*( s604 + n + shift ) = s1077[n + shift];}
else if( pc == s1396 )
(void)0;}}
if( !s1309 && s608[1]->s1348() )
throw new s17( L"non-constant function is applied to a constant variable" );
try {
s586( s604, s518 );}
catch( s17* e ) {
TDException* s1061 = new TDException( TDException::Stage::s1138, s7::s1245, 
s1254, past,	*e );
delete e;
throw s1061;}
s718 = s608[0];
return s718;}
s505 s912::s517( s502** s724, size_t s733 ){
s502* s718 = NULL;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s605 + n ) ) {
s490 pc = ( ( s503* )*( s605 + n ) )->s514();
if( pc == s493 ) ( void )0;
else if( pc == s494 )
(s502*)( ( s616* )*( s605 + n ) )->s517( s724, s733 );}}
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s604, s518 );
if( s718->s645() < 0 )
break;}
return s718;}
s505 s1527::s517( s502** s724, size_t s733 ){
s502* s718 = new s279( *s281[0].s16<s279*>(), s628() );
s718->s520( s612 );
s718->s1414();
return s718;
wstring s194 = s628()->s298();
wstring s1528 = s628()->Src();
s1528.replace( s1528.find( s194 ), s194.size(), 1, L' ' );
s270* ast_ = new s270( s194, s1528 );
s718 = s611.s16<s279*>()->s664( *ast_, s612, s703 );
s718->s1414();
return s718;
vector<s278*> s741( begin(s281), end(s281));
s718 = s611->s371( s612, s741, s628() );
s718->s1414();
return s718;}
bool
s616::s580( const wstring& s709, s387* ref,	
const wstring& s347 ) const{
bool s718 = false;
wstring s285 = s709;
size_t pl = s285.find( L"." );
if( pl == string::npos ) { //a
if( !s656.s160( s285 ) /*!ob*/ ) {
if( s612.s14() && (s613.s13() || s612->s613 == s613 || 
s703 == s612->s703 ) )
s718 = s612->s580( s285, ref, s347 );
if( !s718 ) {
if( s613.s14() )
s718 = s613->s580( s285, ref, s347 );
if( !s718 )
s718 = s307->s580( s285, ref, s347 );}}
else {
size_t off = s669( s285 );
ref->s395( off, ((s503*)&(*s658[off]))->s516()->s524() );
ref->s398( (s502*)this /*(s503**)&s281[off]*/ );
s718 = true;}}
else {// a.y
s285 = s709.substr( pl + 1 );
wstring s719 = s709.substr( 0, pl );
s278* ob = s656.get( s719, false );
if( !ob ) {
s718 = s613->s580( s709, ref, s347 );
if( !s718 && s612.s14() )
s718 = s612->s580( s285, ref, s347 );}
else {
size_t off = s669( s719 );
ref->s395( off, NULL );
s718 = ob->s524()->s580( s285, ref, s347 );
ref->s398( (s502*)this );}}
return s718;}
bool
s911::s580( const wstring& s709, s387* ref, const wstring& s347 ) const{
if( s285 == L"new" &&
s281[0].s16<s502*>()->s580( s709, ref, s347 ) )
return true;
return s616::s580( s709, ref, s347 );}
s278* s616::s623( size_t off ){
return s658[off];}
s278* s616::s350() const{
return new s616( *this );}
void s616::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Transductor : " <<  s285 << endl;
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"Call type : " << ct[s599] << endl;
if( !s656.empty() ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"members : " << endl;
s656.s311( pd, s202 + s435 );}
if( !s607.empty() ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"fpars : " << endl;
for( size_t n = 0; n < s607.size(); ++n )
s607[n]->s311( pd, s202 + s435 * 2 );}
if( !s659.empty() ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"namvec : " << endl;
for( size_t n = 0; n < s659.size(); ++n )
buf << s4::fill_n_ch( L' ', s202 + s435 * 2 ) << s659[n] << endl;}
if( !s658.empty() ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"memvec : " << endl;
for( size_t n = 0; n < s658.size(); ++n )
s658[n]->s311( pd, s202 + s435 * 2 );}
if( !s609.empty() ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << L"exprs : " << endl;
for( size_t n = 0; n < s609.size(); ++n )
s609[n]->s311( pd, s202 + s435 * 2 );}}
s375::s375( s269* s307, const std::wstring& s, const s270* ast_ )
: s351( s307, NULL, ast_ ), s364( s ){
if( s843.s13() ) {
s513 = 0;
wh = s7::s943;}
else {
s513 = s1289;
wh = s7::s942;}}
s375::s375( s269* s307, s502* s617, const std::vector<s278*>& l, const s270* ast_ )
: s351( s307, s617, ast_ ){
s281.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s943;
else
wh = s7::s942;
s513 = s1289;}
s375::s375( const s375& r, const s270* ast_ )
: s351( r.s307, r.ns, ast_ ), s364( r.s364 ){
wh = r.wh;
s513 = r.s513;}
s375::s375( s269* s307, const std::wstring& s, size_t& pos, const s270* ast_ )
:s351( s307, NULL, ast_ ){
s364 = s;
pos = string::npos;
s513 = s1289;
wh = s7::s942;}
s502* s375::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s375( s307, s613, l );}
void s375::s365(){
s363.insert( make_pair( L"new", new s352( L"new", &s375::s1385, s843->s367(),
{ s1240(), s1240( { s7::s1565, s7::s1571 } ) }, 0, 100 ) ) );
s363.insert( make_pair( L"set", new s352( L"set", &s375::s403, s1287,
{ s1240( { s1289 } ), s1240( { s1287 } ) }, 1, 1 )));
s363.insert( make_pair( L"size", new s352( L"size", &s375::s340, s1285,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"sum", new s352( L"sum", &s375::s404, s1289,
{ s1240( { s1289, s7::s1571 } ) }, 1, 100 )));
s363.insert( make_pair( L"sub", new s352( L"sub", &s375::s846, s1289,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"tolower", new s352( L"tolower", &s375::s977, s1289,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"toupper", new s352( L"toupper", &s375::s978, s1289,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"to-bytes", new s352( L"to-bytes", &s375::s1516, s1451->s367(),
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"to-Int", new s352( L"to-Int", &s375::s428, s1285,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"find", new s352( L"find", &s375::s830, s1285,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"rfind", new s352( L"rfind", &s375::s851, s1285,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"eq", new s352( L"eq", &s375::s414, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"less", new s352( L"less", &s375::s415, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"greater", new s352( L"greater", &s375::s416, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"leq", new s352( L"leq", &s375::s417, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"geq", new s352( L"geq", &s375::s418, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"neq", new s352( L"neq", &s375::s419, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"textin", new s352( L"textin", &s375::s425, s1285,
{ s1240( ), s1240( { s1285 } ), s1240( { s1687::s1680 } ), 
s1240( { s1687::s1680, s1285 } ) }, 1, 2 )));
s363.insert( make_pair( L"getline", new s352( L"getline", &s375::s1658, s1285,
{ s1240(), s1240( { s1687::s1680 } ) }, 0, 1 )));
s363.insert( make_pair( L"match", new s352( L"match", &s375::s1143, s1276,
{ s1240( { s1289 } ) }, 1, 1 )));
s363.insert( make_pair( L"reverse", new s352( L"reverse", &s375::s1406, s1289,
{ s1240() }, 0, 0 )));
s363.insert( make_pair( L"sort", new s352( L"sort", &s375::s1419, s1289,
{ s1240() }, 0, 0 )));
s869::Cont s1434;
wstring ts = s765->s369() + L"<" + s843->s369() + L">";
s1172 s1692 = s765->s1339( ts, s1434 );
s363.insert( make_pair( L"split", new s352( L"split", &s375::s1665, s1692,
{ s1240() }, 0, 0 )));}
void s375::s520( s502* s962 ){
for( size_t n = 0; n < s281.size(); ++n ) {
s504 par = s281[n];
if( par->s514() != s493 )
s364 += par->to_wstring();
else {
if( s307->s1497() /*par.s16<s387*>()->s397().s14()*/ )
par.s16<s387*>()->s393()->to_wstring();}}
s1414();}
wstring s736( wchar_t c ){
wstring s718;
if( c == L'n' )
s718 = L"\n";
else if( c == L'r' )
s718 = L"\r";
else if( c == L't' )
s718 = L"    ";
else if( c == L'\\' )
s718 = L"\\";
else {
s718 = c;}
return s718;}
s502* s375::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s_ = s737.s298();
wstring s364, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s54( s_.substr( 7, s_.size() - 8 ), s50 );
if( s.empty() )
return new s375( s307, s613, std::vector<s278*>() );}
else
s = s4::s54( s_, s50 );
if( s.size() ) {
size_t pos = 0;
const s1034* s1160 = NULL;
if( s628() && s628()->Nqj() )
s1160 = s628()->Nqj()->s1107();
vector<s1::s9<s6::s145>> s97;
s6::s183( s1160, s, pos, s97, true, L" \n" );
if( s97.size() ) {
s = L"";
for( size_t n = 0; n < s97.size(); ++n ) {
wstring tmp = s97[n]->s173();
pl = s90.find( tmp[0] );
if( pl != string::npos && tmp.back() == s90[pl] )
tmp = s4::s54( tmp, wstring( 1, s90[pl] ) );
s += tmp;}}}
if( s.size() == 2 && s[0] == L'\\' )
s364 = s736( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s364 = s;
while( pl != string::npos ) {
if( pl == s364.size() - 1 )
break;
if( s364[pl + 1] != L'\\' ) {
wstring code = s736( s364[pl + 1] );
s364 = s364.replace( pl, 2, code );
pl = s364.find( L"\\", pl + 1 );}
else {
s364.erase( pl, 1 );
pl = s364.find( L"\\", pl + 1 );}}}
if( s364.empty() )
s364 = s;
return new s375( s307, s364 );}
s278* s375::s350() const{
return new s375( *this );}
void s375::s372( s278* p ) const{
if( p->s367() == s1289 )
*( (s375*)p )->s373() = s364;
else if( p->s367() == s1285 )
*( (s361*)p )->s373() = std::stoi( s364 );
else if( p->s367() == s859->s367() )
*( (s374*)p )->s373() = std::stof( s364 );
else
throw new s17( L"No conversion to type " + s369() );}
s375::operator int() const{
long s718;
if( !s4::s64( s364.c_str(), &s718 ) )
throw new s17( L"cannot cast String " + s364 + L" to Int" );
if( s718 > (std::numeric_limits<int>::max)() )
throw new s17( L"cannot cast String to Int: the value is too big: " + s364 );
return (int) s718;}
s375::operator double() const {
double s718;
if( !s4::s65( s364.c_str(), &s718 ) )
throw new s17( L"cannot cast String '" + s364 + L"' to Double" );
return s718;}
wstring s375::to_wstring() const {
if( 0 && s364.front() == '\"' && 
s364.back() == '\"' )
return s364.substr( 1, s364.size() - 2 );
return s364; }
s1489 s375::to_bytes() const{
s1489 s718;
string s = U8(s364);
s718.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s718[n] = s[n];
return s718;}
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
#undef s734
#define s734 ((s375*)(s503*)*s281)
#define s735 ((s376*)(s503*)*s281)
inline void s375::s1385( s502** s281, size_t s518 ){
s375* ps = (s375*)s281[1];
vector<s278*> v;
for_each( s281 + 2, s281 + s518, [&v]( s502* s364 )
{ return v.push_back( (s278*)s364 ); } );
*s281 = ( s502* ) new s375( ps->s307, ps->s307, v );
s281[0]->s520( ps->ns );}
inline void s375::s403( s502** s281, size_t s518 ){
( (s375*)DR )->s364 = ( (s375*)PARN( 2 ))->s364;}
inline void s375::s340( s502** s281, size_t s518 ){
*( (s361*)s734 )->s373() = (int)( (s375*)DR )->s364.size();}
inline void s375::s404( s502** s281, size_t s518 ){
s734->s364 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s518; ++n )
s734->s364 += PARN( n )->to_wstring();}
inline void s375::s977( s502** s281, size_t s518 ){
s734->s364 = ((s375*)DR)->s364;
std::for_each( s734->s364.begin(), s734->s364.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s375::s978( s502** s281, size_t s518 ){
s734->s364 = ((s375*)DR)->s364;
std::for_each( s734->s364.begin(), s734->s364.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s375::s846( s502** s281, size_t s518 ){
wstring s732 = L"Invalid substring specification: ";
if( s518 < 2 )
throw new s17( s732 + L"too few parameters." );
const wstring& dr = ((s375*)DR)->s364;
int start = 0, end = (int) dr.size() - 1;
if( s518 > 2 ) {
start = (int)*s281[2];
if( s518 > 3 )
end = (int)*s281[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s17( s732 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s17( s732 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s17( s732 + L"the end position is less than 0." );
if( start > end )
throw new s17( s732 + L"the start position is greater than string's length." );}
s734->s364 = dr.substr( start, end - start );}
inline void s375::s830( s502** s281, size_t s518 ){
wstring s732 = L"Invalid 'find' syntax: ";
if( s518 < 3 )
throw new s17( s732 + L"too few parameters." );
const wstring& dr = ( (s375*)DR )->s364;
const wstring& str = ( (s375*)s281[2] )->s364;
int start = 0; 
if( s518 > 3 ) {
start = (int)*s281[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s17( s732 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s17( s732 + L"the start position is greater than string's length." );}
*((s361*)s281[0])->s373() = (int)dr.find( str, start );}
inline void s375::s851( s502** s281, size_t s518 ){
wstring s732 = L"Invalid 'rfind' syntax: ";
if( s518 < 3 )
throw new s17( s732 + L"too few parameters." );
const wstring& dr = ( (s375*)DR )->s364;
const wstring& str = ( (s375*)s281[2] )->s364;
int start = (std::numeric_limits<int>::max)();
if( s518 > 3 ) {
start = (int)*s281[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s17( s732 + L"the start position is less than 0." );}
*( (s361*)s281[0] )->s373() = (int)dr.rfind( str, start );}
inline void s375::s414( s502** s281, size_t s518 ){
if( DR->to_wstring() == PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s415( s502** s281, size_t s518 ){
if( DR->to_wstring() < PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s416( s502** s281, size_t s518 ){
if( DR->to_wstring() > PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s417( s502** s281, size_t s518 ){
if( DR->to_wstring() <= PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s418( s502** s281, size_t s518 ){
if( DR->to_wstring() >= PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s419( s502** s281, size_t s518 ){
if( DR->to_wstring() != PARN( 2 )->to_wstring() )
*s735->s373() = 1;
else
*s735->s373() = 0;}
inline void s375::s425( s502** s281, size_t s518 ){
Stream* s1652 = NULL;
size_t s1627 = 0;
if( s518 >= 3 ) {
s1652 = (Stream*)s281[2];
if( s518 == 4 )
s1627 = (int)*s281[3];}
else
s1652 = s1575;
wstring& s157 = *( (s375*)DR )->s373();
s1652->s1636( s157, s1627 );
int s718 = (int)s157.size();
s157.resize( s718 );
*((s361*)s734)->s373() = s718;}
inline void s375::s1658( s502** s281, size_t s518 ){
Stream* s1652 = NULL;
if( s518 >= 3 ) {
s1652 = (Stream*)s281[2];}
else
s1652 = s1575;
wstring& s157 = *( (s375*)DR )->s373();
s1652->s1637( s157 );
int s718 = (int)s157.size();
s157.resize( s718 );
*( (s361*)s734 )->s373() = s718;}
inline void s375::s1143( s502** s281, size_t s518 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1149;
wstring s = DR->to_wstring();
bool s157 = regex_match( s, s1149, rg );
*s735->s373() = s157;}
inline void s375::s1665( s502** s281, size_t s518 ){
s324* pv = (s324*)s281[0];
wstring s74 = L"\n";
if( s518 == 3 )
s74 = s281[2]->to_wstring();
wstring& s = ((s375*)DR)->s364;
size_t s70 = 0, s71 = 0;
s1::s9<s375> adds = new s375( ((s375*)DR)->s307 );
while( s71 != wstring::npos && s70 < s.size()) {
s71 = s.find( s74, s70 );
adds->s364 = s.substr( s70, s71 - s70 );
s70 = s71 + s74.size();
if( adds->s364.size() )
pv->s329().push_back( adds->s350() );}}
inline void s375::s1516( s502** s281, size_t s518 ){
( (s1449*)s734 )->s329() = DR->to_bytes();}
inline void s375::s1406( s502** s281, size_t s518 ){
s734->s364 = ((s375*)DR)->s364;
std::reverse( s734->s364.begin(), s734->s364.end() );}
inline void s375::s1419( s502** s281, size_t s518 ){
s734->s364 = ((s375*)DR)->s364;
std::sort( s734->s364.begin(), s734->s364.end() );}
inline void s375::s428( s502** s281, size_t s518 ){
*( (s361*)s734 )->s373() = (int)*DR;}
void s375::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << s364 << endl;}
size_t s375::s331() const{
return hash<wstring>{}(s364);}
bool s375::operator==( const s502* p ) const{
return ( (s375*)p )->s364 == s364;}
bool s375::operator<( const s502* p ) const{
return s364 < ( (s375*)p )->s364;}
vector<wstring> s1046( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s874::s874( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s805, s737 ){
TDException s1061( s7::s1227, s1019, s737 );
if( l.empty() )
throw s1061.s1099( L"too few arguments" );
s281.assign( l.begin(), l.end() );
s513 = s1289;
s616::s1393( ( vector<s278*>& )l, s1046 );}
s874::s874( s269* s307 )
: s616( s307, NULL, NULL, s589, s805, NULL ){
s513 = s1289;}
void s874::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
wstring s732 = L"Invalid parameters of 'substr' function: ";
if( s281[0]->s367() != s1289 )
throw new s17( s732 + L"The first parameter is not of String type." );
str = s281[0].s16<s375*>();
size_t s763 = 1;
int s827 = 0;
s784 s813 = s756;
s757 =	nTo = 1;
s845 = s782 = 0;
while( s763 < s281.size() ) {
s504 par_ = s281[s763];
s490 pc = par_->s514();
if(	pc == s493 || pc == s1174 || pc == s492 || pc == s494 ) {
s504 par;
s508 rf;
if( pc == s493 ) {
rf = par_.s16<s387*>();
par = (s278*)rf->s394();}
else if( pc == s1174 ) {
rf = par_.s16<s387*>();
par = par_;}
else
par = par_;
if( par->s367() == s829->s367() ) {
if( rf->Id() == s1373 ) {
if( s827 != 0 )
throw new s17( s732 + L"'from' is misplaced." );
s827 = 1;
s813 = s811;}
else if( rf->Id() == s1381 ) {
if( s827 != 0 )
throw new s17( s732 + L"'to' is misplaced." );
s827 = 1;
s813 = s873;}
else if( rf->Id() == s1365 ) {
if( s813 != s756 && s827 >= 2 )
throw new s17( s732 + L"'before' is misplaced." );
if( s813 == s873 )
s782 = -1;
else
s845 = -1;
s827 = 2;}
else if( rf->Id() == s1361 ) {
if( s813 != s756 && s827 >= 2 )
throw new s17( s732 + L"'after' is misplaced." );
if( s813 == s873 )
s782 = 1;
else
s845 = 1;
s827 = 2;}
else if( rf->Id() == s1372 ) {
if( s813 != s756 && s827 >= 3 )
throw new s17( s732 + L"'first' is misplaced." );
s827 = 3;}
else if( rf->Id() == s1377 ) {
if( s813 != s756 && s827 >= 3 )
throw new s17( s732 + L"'last' is misplaced." );
if( s813 == s873 )
nTo = string::npos;
else
s757 = string::npos;
s827 = 3;}
else
throw new s17( s732 + L"unknown parameter '" + rf->s644() + L"'." );}
else if( par->s367() == s1289 ) {
if( s813 == s811 )
s861 = par;
else if( s813 == s873 )
s853 = par;
else {
if( s861.s13() && s810.s13() )
s861 = par;
else if( s853.s13() && s760.s13() )
s853 = par;
else
throw new s17( s732 + L"unknown parameter '" + rf->s644() + L"'." );}
s827 = 0; s813 = (( s813 == s811 || s813 == s756 ) ? s873 : s811 );}
else if( par->s367() == s1285 ) {
if( s813 == s811 )
s810 = par;
else if( s813 == s873 )
s760 = par;
else {
if( s861.s13() && s810.s13() )
s810 = par;
else if( s853.s13() && s760.s13() )
s760 = par;
else
throw new s17( s732 + L"unknown parameter '" + rf->s644() + L"'." );}
s827 = 0; s813 = ( ( s813 == s811 || s813 == s756 ) ? s873 : s811 );}}
s763++;}}
s505 s874::s517( s502** s724, size_t s733 ){
size_t s197 = 0, s716 = string::npos;
wstring s807, s762;
wstring dom = str->s517( 0, 0 )->to_wstring();
if( s810.s14() ) {
if( s810->s514() == s494 )
s197 = (size_t)(int)*s810->s517( 0, 0 );
else
s197 = (size_t)(int)*s810.s16<s361*>();}
else if( s861.s14() ) {
s807 = s861->to_wstring();
if( s757 == 1 )
s197 = dom.find( s807 );
else if( s757 == string::npos )
s197 = dom.rfind( s807 );
else
throw new s17( L"substr: nFrom =" + std::to_wstring( s757 ) );
if( s845 > 0 )
s197 += s807.size();
else
s197 += s845;}
if( s760.s14() ) {
if( s760->s514() == s494 )
s716 = (size_t)(int)*s760->s517( 0, 0 );
else
s716 = (size_t)(int)*s760.s16<s361*>();}
else if( s853.s14() ){
s762 = s853->to_wstring();
if( nTo == 1 )
s716 = dom.find( s762 );
else if( nTo == string::npos )
s716 = dom.rfind( s762 );
else
throw new s17( L"substr: nTo =" + std::to_wstring( s757 ) );
s716 += s782;}
if( s197 < 0 || s197 >= s716 || s197 >= dom.size() )
return s505();
wstring s157 = dom.substr( s197, s716 - s197 );
s611 = new s375( s307, s157 );
return s611;}
s278* s874::s350()const{
return new s874( *this );}
s401::s401( s269* s307 )
: s337( s307, NULL, NULL ), s1074( false ), s1075( false ), s1087( 0 )//, s969( false )
{
s513 = s865.s13() ? 0 : s865->s367();
s1394 = new s1704( s307, 0 );
s1395 = new s1704( s307, s1272 );
s1317 = new s1704( s307, 0 );}
s401::s401( s269* s307, s337* s613, Iterator* it )
: s337( s307, NULL, NULL ), s1083( s613 ), s1641( it ), s1074( false ), s1075( false ), 
s1087( 0 ){
s513 = s865->s367();}
s401::s401( uint64_t _beg, uint64_t _end )
: s337( NULL, NULL, NULL ), s1074( false ), s1075( false ), s1087( 0 )//, s969( false )
{
s1394 = new s1704( s307, _beg );
s1395 = new s1704( s307, _end );
s513 = s865->s367();
s1317 = new s1704( s307, 0 );}
s401::s401( s269* s307, const wstring& s79, const s270* ast_ )
: s337( s307, NULL, ast_ ), s1074( false ), s1075( false ), s1087( 0 )//, s969( false )
{}
s401::s401( const s401& r, const s270* ast_ )
: s337( r.s307, r.ns, ast_ ), s1074( false ), 
s1075( false ), s1087( r.s1087 ), s1317( r.s1317 )//, s969( r.s969 )
{
s513 = r.s513;}
vector<wstring> s1040( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s401::s401( s269* s307, s502* s617, const vector<s278*>& l_, const s270* ast_ )
: s337( s307, s617, ast_ ), s1074( false ), s1075( false ), s1087( 0 ), 
s1317( new s1704( s307, 0 ) )//, s969( false )
{
s513 = s865->s367();
if( l_.empty() )
return;
TDException s1061( s7::s1225, s1020, ast_ );
if( l_.size() > 9 )
throw s1061.s1099( L"too many arguments" );
s616::s1393( ( vector<s278*>& )l_, s1040 );
const size_t s1164 = 3;
std::vector<s278*> l( s1164 );
if( l_[0]->s514() == s1174 ) {
s387* rf = (s387*)l_[0];
if( rf->Id() == s1375 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1704( s307, 0 );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1704( s307, 0 );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s613 = l[0];
s1394 = l[1];
s1395 = l[2];
if( s613.s13() ) {
s335 = s1704::proto->s367();
s325 = s1704::proto->s367();}
else {
s335 = 0;
s325 = 0;}
s513 = s865->s367();}
s502* s401::s370( const s270& s737, s502* s613, const wstring& s347 ){
wstring s = s737.s298();
wstring s362 = s369();
if( s.find( s362 ) == 0 && ( s.size() == s362.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s54( s.substr( s362.size() ), s50 );
if( sv.size() && sv[0] != L'(' )
throw new s17( L"wrong range constructor syntax" );
wstring s732 = L"Malformed Range definition: " + s;
vector<s278*> s741;
s278::s1501( s737, s307, s613, s347, s741 );
return new s401( s307, s613, s741 );}
else
return NULL;}
void s401::s520( s502* s962 ){
TDException s1061( s7::s1007, s1020, s628(), L"wrong Range definition" );
ns = s962;
if( s613.s14() ) {
if( s613->s514() == s493 ) {
s613.s16<s387*>()->s520( s962 );
s1083 = (s337*)s613.s16<s387*>()->s393();}
else if( s613->s514() == s496 ) {
s504 tmp = s278::s1122( s307, s613, s962, (s616*)s962, s962->s305() );
s613 = tmp;
s1083 = (s337*)s613->s516();}
else {
s1083 = (s337*)s278::s1122( s307, s613, s962, (s616*)s962, s962->s305() );}
s335 = s1083->ValType();
s325 = s1083->s328();}
if( s1394.s14() ) {
if( s1394->s514() == s493 )
s1394.s16<s387*>()->s520( s962 );
else {
s504 tmp = s278::s1122( s307, s1394, s962, (s616*)s962, s962->s305() );
s1394 = tmp;}}
else
s1394 = s381.s16<s503*>();
if( s1395.s14() ) {
if( s1395->s514() == s493 )
s1395.s16<s387*>()->s520( s962 );
else {
s504 tmp = s278::s1122( s307, s1395, s962, (s616*)s962, s962->s305() );
s1395 = tmp;}}
else
s1395 = s381.s16<s503*>();}
void s401::s365(){
s363.insert( make_pair( L"new", new s352( L"new", &s401::s1385, s865->s367(),
{ s1240( { s1687::s1724 } ), s1240( { s1285, s1285 } ),
s1240( { s1687::s1682, s1285 } ),
s1240( { s1687::s1682, s1285, s1285 } ) }, 1, 3 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", NULL, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"max-element", new s352( L"resize", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"eq", new s352( L"eq", NULL, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"reverse", new s352( L"reverse", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
s1267 s401::s1341( const std::wstring& s358 ) const{
if( s1083.s14() ) 
return s1083->s1341( s358 );
return s351::s1341( s358 );}
s1267 s401::s1336( const std::wstring& s358, s1240& ap ) const{
if( s358 == L"new" )
return s351::s1336( s358, ap );
if( s1083.s14() )
return s1083->s1336( s358, ap );
assert( 0 );
throw;}
s1267 s401::s1331( const std::wstring& s358,
s1240& ap ) {
if( s358 == L"new" )
return s351::s1331( s358, ap );
if( s1083.s14() )
return s1083->s1331( s358, ap );
assert( 0 );
throw;}
s1172 s401::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"new" ) {
s718 = s1687::s1682;}
else if( s1083.s14() )
return s1083->s1332( s1728, l );
return s718;}
const vector<wstring>&
s401::s1335( const wstring& s358 ) const{
if( s358 == L"new" || s1083.s13() )
return s351::s1335( s358 );
else
return s1083->s1335( s358 );}
s502* s401::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s401( s307, s613, l, ast_ );}
inline bool
s401::s522( const s502* s523 ) const{
return ( ( (s401*)s523 )->s367() == s367() );}
size_t s401::s1262() const{
if( s1083.s14() )
return s1083->s1262();
else
return 0;}
s1269 s401::s1338(){
Iterator *fir = NULL, *sec = NULL;
if( s1083.s14() ) {
if( s1074 )
fir = s1083->s1327( s1394.s16<s502*>() );
else if( s1394 == s1696 )
fir = s1083->s1333();
else
fir = s1083->s1305( s1394.s16<s502*>() );
if( s1075 )
sec = s1083->s1327( s1395.s16<s502*>() );
else if( s1395 == s1696 )
sec = s1083->s1333();
else
sec = s1083->s1305( s1395.s16<s502*>() );
if( s1083->s1262() >= 1 && ( s1394 == s1696 || sec->operator<( fir ) ) ) {
( (s1243*)fir )->reverse();
( (s1243*)sec )->reverse();}}
return s1269( fir, sec );}
s1269 s401::s1338( s337* s617 ){
Iterator *fir, *sec;
if( s1074 )
fir = s617->s1327( s1394.s16<s502*>() );
else if( s1394 == s1696 )
fir = s617->s1333();
else 
fir = s617->s1305( s1394.s16<s502*>() );
if( s1075 )
sec = s617->s1327( s1395.s16<s502*>() );
else if( s1395 == s1696 )
sec = s617->s1333();
else
sec = s617->s1305( s1395.s16<s502*>() );
if( s617->s1262() >= 1 && ( s1394 == s1696 || sec->operator<( fir ) ) ){
( (s1243*)fir )->reverse();
( (s1243*)sec )->reverse();}
return s1269( fir, sec );}
inline void s401::s1385( s502** s281, size_t s518 ){
s401* r = ( (s401*)s281[1] );
vector<s278*> v;
for_each( s281 + 2, s281 + s518, [&v]( s502* s364 ) 
{ return v.push_back( (s278*) s364 ); } );
s401* s1645 = new s401( r->s307, r->ns, v );
s1645->s520( r->ns );
*s281 = (s502*)s1645;}
s278* s401::s350() const{
return new s401( *this );}
void s401::s372( s278* p ) const{
p = new s401( *this );}
size_t s401::s331() const{
return (size_t)this;}
bool s401::operator==( const s502* p ) const{
return ( this == p );}
bool s401::operator<( const s502* p ) const{
return false;}
Iterator* s401::s322( s401* r ){
if( s1394.s14() ) {
s490 pc = s1394->s514();
if( pc == s494 )
s1717 = s1394->s517( 0, 0 );
else if( pc == s493 )
s1717 = s1394.s16<s387*>()->s393();
else
s1717 = s1394.s16<s502*>();}
if( s1395.s14() ) {
s490 pc = s1395->s514();
if( pc == s494 )
s1718 = s1395->s517( 0, 0 );
else if( pc == s493 )
s1718 = s1395.s16<s387*>()->s393();
else
s1718 = s1395.s16<s502*>();}
if( s1083.s14() )
return s1083->s322( this );
s1087 = s1272;//( std::numeric_limits<int>::max )( );// (int)*s1394.s16<s502*>();
return this;}
s278* s401::s323(){
if( s1087 == s1272 ) {
if( s1717.s14() ) {
if( s1717->s367() == s1702 )
s1087 = *s1717.s16<s1704*>()->s373();
else {
s1465 tmp;
s1717->s372( &tmp );
if( *tmp.s373() < 0 )
throw new s17( L"relative indices are not allowed for a range of natural numbers" );
s1087 = *tmp.s373();}}
if( s1718.s14() ) {
if( s1718->s367() == s1702 )
s1721 = *s1717.s16<s1704*>()->s373();
else {
s1465 tmp;
s1718->s372( &tmp );
if( *tmp.s373() < 0 )
throw new s17( L"relative indices are not allowed for a range of natural numbers" );
s1721 = *tmp.s373();}}
if( s1087 > s1721 )
incr = -1;
else
incr = 1;}
else
s1087 += incr;
if( s1087 == s1721 )
return NULL;
*s1317->s373() = s1087;
return s1317;}
s278* s401::s1054(){
return s326->s1054();}
s278* s401::Idx(){
return NULL;}
s278* s401::El(){
return NULL;}
void s401::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Range :: " << L" curit: " << s326 << endl;}
vector<wstring> s1258( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1257::s1257( s269* s307, const wstring& s79, const s270* ast_ )
: s337( s307, NULL, ast_ ), s1086( s7::s1545, s307 ), s1087(NULL), s364( new s361( s307, 0 )), 
s718( new s361( s307, 0 )),s1522(0){
s513 = s1259.s13() ? 0 : s1259->s367();}
s1257::s1257( const s1257& r, const s270* ast_ )
: s337( r.s307, r.ns, ast_ ), s1086( s7::s1545, s307 ), s1087(NULL), s364( new s361( s307, 0 ) ),
s718( new s361( s307, 0 ) ), s1522(r.s1522){
*s364->s373() = (int)*r.s364;
*s718->s373() = (int)*r.s718;
ns = r.ns;
s513 = r.s513;}
s1172 s1628( size_t& idx, const vector<s278*>& l ){
if( l.size() > idx && l[idx]->s514() == s1174 )
idx++;
if( l.size() > idx )
return l[idx]->s367();
return 0;}
s1257::s1257( s269* s307, s502* s617, const vector<s278*>& l_, const s270* ast_ )
: s337( s307, s617, ast_ ), s1086( s7::s1545, s307 ), s1087(NULL),
s364( new s361( s307, 0 ) ),	s718( new s361( s307, 0 ) ),s1522(0){
s513 = s1259->s367();
ns = s617;
if( l_.empty() )
return;
TDException s1061( s7::s1538, s1020, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s1061.s1099( L"too many arguments" );
s616::s1393( ( vector<s278*>& )l_, s1258 );
const size_t s1164 = 3;
std::vector<s278*> l( s1164 );
if( !s307->TR().s1640( l_[0]->s367(), s1687::s1682 ) )
throw s1061.s1099( L"the type is not rangeable: " + l_[0]->s369() );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s367() == s1587 ) {
range = (s401*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s514() != s1174 || ((s387*)l_[bas])->Id() != s1499 )
throw s1061.s1099( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s514() != s1174 || ((s387*)l_[bas])->Id() != s1384 )
throw s1061.s1099( L"expected the 'where:' clause" );
if( l_[bas+2]->s514() != s1174 || ((s387*)l_[bas+2])->Id() != s1499 )
throw s1061.s1099( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s613 = l[0];
where = l[1];
s1181 = l[2];}
s502* s1257::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
wstring s362 = s369();
if( s.find( s362 ) == 0 && ( s.size() == s362.size() || s[s.size() - 1] == L')' ) ) {
s504 fi = new s361( s307, 0 ), la = new s361( s307, 0 ), in = new s361( s307, 1 );
wstring sv = s4::s54( s.substr( s362.size() ), s50 );
if( sv.size() && sv[0] != L'(' )
throw new s17( L"wrong filter constructor syntax" );
wstring s732 = L"Malformed Filter definition: " + s;
const s270::s282& s738 = s737.s300();
size_t s733 = s738.size();
if( /*!s733 ||*/ s733 > 3 )
throw new s17( s732 );
std::vector<s278*> s281;
for( size_t n = 0; n < s733; ++n ) {
s270::s282::const_iterator it = s738.find( std::to_wstring( n ) );
s281.push_back( s278::s525( *it->second, s307, s613, s347 ) );}
return s371( s613, s281, &s737 );
if( s307->TR().s1640( s281[0]->s367(), s1687::s1682 ) )
return new s1257( s307, s613, s281 );
else
return new s1041( s307, s613, s281 );
/*if( s733 == 1 ) {
s270::s282::const_iterator it = s738.find( L"0" );
la = s278::s525( *it->second, s307, s613, s347 );}
else {
s270::s282::const_iterator it = s738.find( L"0" );
fi = s278::s525( *it->second, s307, s613, s347 );
it = s738.find( L"1" );
la = s278::s525( *it->second, s307, s613, s347 );
if( s733 == 3 ) {
it = s738.find( L"2" );
in = s278::s525( *it->second, s307, s613, s347 );}
}*/
}
else
return NULL;}
void s1257::s520( s502* s962 ){
TDException s1061( s7::s1007, s1020, s628(), L"wrong Filter definition");
ns = s962;
if( s613.s13() )
return;
if( s613->s514() == s493 ) {
s1083 = s613.s16<s387*>()->s393();}
else if( s613->s514() == s496 ) {
s504 tmp = s278::s1122( s307, s613, s962, (s616*)s962, s962->s305() );
s613 = tmp;
s1083 = s613->s516();}
else {
s1083 = (s502*)s278::s1122( s307, s613, s962, (s616*)s962, s962->s305() );}
if( s1083->s514() == s492 ) {}
else if( s1083->s514() == s499 ) {}
else
throw s1061.s1099( L"unsupported container type" );
s1086.s395( 0, s307->TR().s1108( s1083.s16<s337*>()->ValType() ) );
s1086.s398( (s502*)this );
if( where.s14() ) {
if( where->s514() == s493 )
where.s16<s387*>()->s520( s962 );
else
where = s278::s1122( s307, where, this, (s616*)s962, s962->s305() );}
if( s1181.s14() ) {
if( s1181->s514() == s493 ) {
s1181.s16<s387*>()->s520( s962 );
s335 = s1181->s516()->s367();}
else {
s1181 = s278::s1122( s307, s1181, s962, (s616*)s962, s962->s305() );
s335 = s1181.s16<s907*>()->s1495();}}
if( !s335 )
s335 = s1083.s16<s337*>()->ValType();
s513 = s307->TR().s1155( s869::Cont( { s1259->s367(), s335 }) );
s869::Cont s1434;
wstring ts = s765->s369() + L"<" + 
s307->TR().s1521( s307->TR().s856( s335 ) ) + L">";
s1522 = s765->s1339( ts, s1434 );
s1414();}
void s1257::s365(){
s363.insert( make_pair( L"new", new s352( L"new", &s1257::s1385, s1259->s367(),
{ s1240( { s1285, s1285 } ) }, 1, 2 ) ) );
s363.insert( make_pair( L"to-vector", new s352( L"to-vector", &s1257::s1517, 0,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"max-element", new s352( L"resize", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"eq", new s352( L"eq", NULL, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"reverse", new s352( L"reverse", NULL, s1287,
{ s1240() }, 0, 0 ) ) );
s363.equal_range( L"new" ).first->second->s1413( true );
s363.equal_range( L"to-vector" ).first->second->s1413( true );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
s1267 s1257::s1336( const std::wstring& s358, s1240& ap ) const{
return s351::s1336( s358, ap );
if( s358 == L"new" )
return s351::s1336( s358, ap );
assert( 0 );
throw;}
s1267 s1257::s1331( const std::wstring& s358, s1240& ap ){
if( s358 == L"new" ) {
auto ran = s357().equal_range( s358 );
s352* mi = ran.first->second;
s1267 s1386( s335, mi->s1260(), mi->s1348() );
return s1386;}
else if( s358 == L"to-vector" ) {
auto ran = s357().equal_range( s358 );
s352* mi = ran.first->second;
s1267 s1386( s1522, mi->s1260(), mi->s1348() );
return s1386;}
assert( 0 );
throw;}
s1172 s1257::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"new" ) {
s718 = s1687::s1682;}
else if( s1728 == L"to-vector" ) {
s718 = s1522;}
return s718;}
s502* s1257::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s1257( s307, s613, l, ast_ );
s1172 pt = l[0]->s367();
if( s307->TR().s1640( pt, s1687::s1682 ) )
return new s1257( s307, s613, l );
s616::s1393( ( vector<s278*>& )l, s1258 );
s490 pc = l[0]->s514();
vector<s278*> s1000;
size_t s391 = 0;
if( pc == s492 ) {
if( pt == s1285 ) {
if( l.size() > 1 && l[1]->s367() == s1285 ) {
s1000 = { l[0], l[1] };
s391 = 1;}
else {
s1000 = { l[0] };
s391 = 2;}}}
else if( pc == s1174 ) {
if( ( (s387*)l[0] )->s1467() == s1381 ) {
s1000 = { l[1] };
s391 = 2;}
else if( ( (s387*)l[0] )->s1467() == s1373 ) {
s1000 = { l[1], l[3] };
s391 = 4;}}
vector<s278*> l1 = { new s1041( s307, s613, s1000 ) };
l1.insert( l1.end(), l.begin() + s391, l.end() );
return new s1257( s307, s613, l1 );
if( l.size() ) {
if( l[0]->s514() == s493 ) {
l[0]->s520( s613 );
if( s307->TR().s1640( l[0]->s367(), s1687::s1682 )  )
return new s1257( s307, s613, l );}}
else {
return new s1257( s307, s613, l );}
return new s1041( s307, s613, l );}
s502* s1257::s371( s502* s613, const std::vector<s1172>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1257* s718 = new s1257( s307, L"" );
s869::Cont s1184;
s510::s1109( vt, idx, s1184 );
s869 s1182( s1184[0] );
return s718;}
inline bool
s1257::s522( const s502* s523 ) const{
return ( ((s1257*)s523)->s367() == s367() );}
inline void s1257::s1385( s502** s281, size_t s518 ){
vector<s278*> v;
for_each( s281 + 2, s281 + s518, [&v]( s502* s364 )
{ return v.push_back( (s278*)s364 ); } );
s1257* pf = (s1257*)s281[1];
*s281 = ( s502* ) pf->s371( pf->ns, v, pf->s628() );
s281[0]->s520( pf->ns );
pf->s1086.s398( s281[0] );
pf->s1087 = ((s1257*)s281[0])->s1087;}
inline void s1257::s1517( s502** s281, size_t s518 ){
s1257* pf = (s1257*)s281[1];
*s281 = ( s502* ) pf->s307->TR().
s1108( pf->s1522 )->s371( pf->ns );
Iterator* s1125 = pf->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
( (s324*)s281[0] )->add( p->s350() );}
s281[0]->s1414();}
s278* s1257::s350() const{
return new s1257( *this );}
void s1257::s372( s278* p ) const{
p = new s1257( *this );}
size_t s1257::s331() const{
return (size_t)this;}
bool s1257::operator==( const s502* p ) const{
return ( this == p );}
bool s1257::operator<( const s502* p ) const{
return false;}
bool
s1257::s580( const wstring& s709, s387* ref, const wstring& s347 ) const{
if( s709 == s7::s1545 ) {
ref->s1511( (s387*)&s1086 );
return true;}
return false; // ns->s580( s709, ref, s347 );
}
s278* s1257::s623( size_t off ){
assert( off == 0 );
if( s1087 )
return s1087;
return (s278*) s1086.s524();}
s1269 s1257::s1338(){
if( range.s14() )
return range->s1338();
else
return s1083.s16<s337*>()->s1338();}
Iterator* s1257::s322( s401* r ){
if( range.s14() ) {
s1269 pr = range->s1338( );
s326 = pr.first;
s1664 = pr.second;}
else {
s1269 pr = s1083.s16<s337*>()->s1338();
s326 = pr.first;
s1664 = pr.second;}
return this;}
s278* s1257::s323(){
while( 1 ) {
s1087 = s326->s323();
if( !s1087 || s326->operator==(s1664) )
return NULL;
if( where.s14() && ( false == (bool)*where->s517(0,0) ) )
continue;
break;}
if( s1181.s14() )
return s1181->s517( 0, 0 ).s16<s503*>();
else
return s1087;}
s278* s1257::s1054(){
return s326->s1054();}
s278* s1257::Idx(){
return NULL;}
s278* s1257::El(){
return NULL;}
void s1257::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s202 ) << L"Input: ";
if( s613.s14() ) {
s1083.s14() ? s1083->s311( pd, s202 + s435 ) : s613->s311( pd, s202 + s435 );}
buf << s4::fill_n_ch( L' ', s202 ) << L"Do: ";
if( s1181.s14() ) s1181->s311( pd, s202 + s435 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s202 ) << L"curitref: ";
s1086.s311( pd, 0 );
buf << endl;}
s1041::s1041( s269* s307 ) 
: s337( s307, NULL, NULL ) {
s513 = s1469.s13() ? 0 : s1469->s367();}
s1041::s1041( s269* s307, s502* s613, const std::vector<s278*>& l, const s270* ast_ )
: s337( s307, s613, ast_ ), s1156( true ){
if( l.empty() )
return;
wstring s1097 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s17( s1097 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s513 = s1469->s367();}
s1041::~s1041(){}
s502* s1041::s370( const s270& s737, s502* s613, const wstring& s347 ){
wstring s = s737.s298();
wstring s362 = s369();
if( s.find( s362 ) == 0 && ( s.size() == s362.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s54( s.substr( s362.size() ), s50 );
if( sv.size() && sv[0] != L'(' )
throw new s17( L"wrong range constructor syntax" );
wstring s732 = L"Malformed Sequence definition: " + s;
vector<s278*> s741;
s278::s1501( s737, s307, s613, s347, s741 );
return new s1041( s307, s613, s741 );}
else
return NULL;}
s502* s1041::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s1041( s307, s613, l, ast_ );}
void s1041::s520( s502* s962 ){
if( end.s13() )
return;
wstring s1097 = L"wrong sequence generator syntax";
s504 tmp = s278::s1122( s307, end, s962, (s616*)s962, s962->s305() );
end = tmp;
if( start.s14() ) {
tmp = s278::s1122( s307, start, s962, (s616*)s962, s962->s305() );
start = tmp;}
else {
if( end->s367() == s1285 )
start = new s361( s307, 0 );
else {
start = s307->TR().s542( end->s367(), s962, s962->s305() );
start->s520( s962 );}}
if( incr.s14() ) {
tmp = s278::s1122( s307, incr, s962, (s616*)s962, s962->s305() );
incr = tmp;}
else {
if( start->s367() == s1285 )
incr = new s361( s307, 1 );
else
throw new s17( s1097 + L": increment value is missing" );}
s1088 = start->s350();
std::vector<s278*> pl = { s1088, incr };
s585 cs( s307, L"sumeq", pl, NULL );
s1169 = s616::s625( &cs, s307, s962, (s616*)s962, s962->s305() );
s1169->s520( s962->s305(), false );
std::vector<s278*> pl1 = { s1088, start };
s585 cs1( s307, L"set", pl1, NULL );
set = s616::s625( &cs1, s307, s962, (s616*)s962, s962->s305() );
set->s520( s962->s305(), false );
std::vector<s278*> pl2 = { s1088, end };
s585 cs2( s307, L"eq", pl2, NULL );
eq = s616::s625( &cs2, s307, s962, (s616*)s962, s962->s305() );
eq->s520( s962->s305(), false );
s1344 = s1285;
s335 = start->s367();}
s1269 s1041::s1338(){
s1::s1445<Iterator> it = this;
s1::s1445<Iterator> it1 = it;
return make_pair( it, it1 );}
Iterator* s1041::s322( s401* r ){
set->s517( 0, 0 );
s1156 = true;
return this;}
s278* s1041::s323(){
if( s1156 )
s1156 = false;
else
s1169->s517( 0, 0 );
if( (bool)*eq->s517( 0, 0 ) )
return NULL;
return s1088;}
void s1041::s365(){
s363.insert( make_pair( L"new", new s352( L"new", &s1041::s1385, s1469->s367(),
{ s1240( { s1285 } ), s1240( { s1285, s1285 } ) }, 1, 2 ) ) );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
bool s1041::operator==( const Iterator* p ){
return (this == p && (bool)*eq->s517( 0, 0 ));}
bool s1041::operator<( const Iterator* p ){
return this < p;}
inline void s1041::s1385( s502** s281, size_t s518 ){
vector<s278*> v;
for_each( s281 + 2, s281 + s518, [&v]( s502* s364 )
{ return v.push_back( (s278*)s364 ); } );
*s281 = ( s502* ) new s1041( ( (s1041*)s281[1] )->s307, NULL, v );
s281[0]->s520( ((s1041*)s281[1])->ns );}
void s1041::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"SequenceGenerator : " << endl;
start->s311( pd, s202 + s435); buf << L", "; end->s311( pd, 0); 
buf << L", "; incr->s311( pd, 0 );}
s1172 s1687::s1682 = 0;
s1172 s1687::s1681 = 0;
s1172 s1687::s1683 = 0;
bool _cmp( const s504& l_, const s504& r_ ){
s502* l = l_.s16<s502*>();
s502* r = r_.s16<s502*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s504 l, const s504 r ) const{
return l.s16<s502*>()->operator<( r.s16<s502*>() );}
};
struct s1296{
std::vector<s504>s934;
s507 s932;
s1296( /*s507 s933*/ ) : s932( /*s933*/0 ) { s934.resize( 2 ); }
bool operator()( const s504& l, const s504& r ){
if( s932.s14() ) {
s934[0] = l;
s934[1] = r;
s932->s621( s934 );
return (bool)*s932->s517( 0, 0 );}
else
return l.s16<s502*>()->operator<( r.s16<s502*>() );}
};
Iterator* s337::s1305( const s502* idx ){
throw new s17( L"this iterable type doesn't support access by index" );}
Iterator* s337::s1327( const s502* idx ){
throw new s17( L"this iterable type doesn't support search for value" );}
Iterator* s337::s1387( const s502* idx ){
throw new s17( L"this iterable type doesn't support distancing between elements" );}
s502* s337::s1334( Iterator* ){
throw new s17( L"this iterable type doesn't support indexing" );}
struct s910;
s502* s337::sort( bool, s910* ){
throw new s17( L"not implemented", (uint32_t) s17::s18::s957 );}
template <class _Cont, class s1478, class Der>
s321<_Cont, s1478, Der>::s321( const s1312& r )
: s337( r ){}
void s1301( s269* s307, const wstring& s79, wstring& s1428, wstring& s674 ){
assert( !s79.empty() );
wstring sv = s79;
wsmatch s1185, rgres1;
wregex s1407( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
wregex s1408( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(.*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1185, s1408 ) ) {
s869::Cont vt;
s1428 = s1185[1].str();
if( regex_match( sv, rgres1, s1407 ) ) {
s674 = L"] " + //s1428 + L" " +
( s1185[s1185.size()-1].str().empty() ? L"0" : s1185[s1185.size()-1].str() );}
else {
s674 = s1185[2];}}}
s1268::s1268( s269* s307, const std::wstring& s79, const s270* ast_ )
: s351( s307, NULL, ast_ ){}
s1268::s1268( const s1268& right, const s270* ast_ )
: s351( right.s307, right.ns, ast_ ), s364( right.s364 ){}
s1268::s1268( s269* s307, s502* s613, Iterator* it, const s270* ast_ )
: s351( s307, NULL, ast_ ), s364( it ){}
s502* s1268::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
wstring s362 = s369();
if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
wstring sv = s4::s54( s.substr( s362.size() ), s50 );
if( sv[0] != L'(' )
throw new s17( L"wrong Position constructor syntax" );
wstring s732 = L"Malformed Position declaration: " + s;
const s270::s282& s738 = s737.s300();
size_t s733 = s738.size();
if( s733 )
throw new s17( s732 );
return s371( s613, vector<s278*>(), &s737 );}
else
return NULL;}
s502* s1268::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s1268( s307, L"", ast_ );}
void s1268::s520( s502* s962 ){}
void s1268::s365(){}
s278* s1268::s350() const{
return new s1268( *this );}
void s1268::s372( s278* p ) const{
p = new s1268( *this );}
size_t s1268::s331() const{
return (size_t)this;}
bool s1268::operator==( const s502* p ) const{
return this == p;}
bool s1268::operator<( const s502* p ) const{
return this < p;}
void s1268::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Position : " <<
this << endl;}
s1057::s1057( s324* v_, s1028 it, s1028 sent )
: v( v_ ), s1360( it ), s1202( sent ), s1359( (uint64_t)-1 ), s1315( new s1704(NULL, -1) ), 
s1314( new s1050(NULL, vector<s278*>( { s1315, s381 } )) ){
if( v.s14() ) {
s1359 = std::distance( v->s329().begin(), it );
assert( s1359 >= 0 );}}
s1057::s1057( s324* v_, s1398 it, s1398 sent )
: v( v_ ), s1410( it ), s1663( sent ), s1359( (uint64_t)-1 ), s1315( new s1704(NULL, -1) ), 
s1314( new s1050(NULL, vector<s278*>( { s1315, s381 } )) ){
if( v.s14() ) {
s1359 = v->size() - std::distance( v->s329().rbegin(), it ) - 1;
assert( s1359 >= 0 );}
s969 = true;}
s1057::s1057( s1057* it )
: v( it->v ), s1360( it->s1360 ), s1359( it->s1359 ), s1315( new s1704(NULL, 0) ), 
s1314( new s1050( NULL, vector<s278*>( { s1315, *s1360 } )) ){
s969 = it->s969;}
void s1057::reverse(){
s969 = true; 
s1410 = std::make_reverse_iterator( s1360 );}
s278* s1057::s323(){
s278* s718 = NULL;
if( !s969 ) {
if( s1360 != s1202 ) {
s718 = *s1360;
s1360++;
s1359++;}}
else {
if( s1410 != s1663 ) {
s718 = *s1410;
s1410++;
s1359--;}}
return s718;}
s278* s1057::s1054(){
if( !s969 )
return *s1360;
else
return *s1410;}
s278* s1057::Idx(){
*s1315->s373() = s1359 - 1;
return s1315;}
s278* s1057::El(){
*s1315->s373() = (int)s1359 - 1;
return s1315;}
bool s1057::operator==( const Iterator* r ){
if( !s969 )
return s1360 == ((s1057*)r)->s1360;
else
return s1410 == ((s1057*)r)->s1410;}
bool s1057::operator<( const Iterator* r ){
if( !s969 )
return s1360 < ( (s1057*)r )->s1360;
else
return s1410 < ( (s1057*)r )->s1410;}
s1053::s1053( s794* v_, 
s1028 it, s1028 sent )
: v( v_ ), s1360( it ), s1202( sent ), s1359( (uint64_t)-1 ), s1315( new s1704( NULL, 0 ) ){
if( v.s14() ) {
s1359 = std::distance( v->s329().begin(), it );
assert( s1359 >= 0 );}}
s1053::s1053( s1053* it )
: v( it->v ), s1360( it->s1360 ), s1359( it->s1359 ), s1315( new s1704( NULL, 0 ) ){}
s278* s1053::s323(){
s278* s718 = NULL;
if( s1360 != v->s329().end() ) {
s718 = *s1360;
++s1360;
++s1359;}
return s718;}
s278* s1053::s1054(){
return *s1360;}
s278* s1053::Idx(){
*s1315->s373() = s1359 - 1;
return s1315;}
s278* s1053::El(){
*s1315->s373() = s1359 - 1;
return s1315;}
s1027::s1027( s333* v_, s1028 it, s1028 sent )
: v( v_ ), s1360( it ), s1202( sent ), s1315( s381 ), s1314( new s1050( NULL,
vector<s278*>(	{ s1315, s1360->second } ) ) ){}
s1027::s1027( s1027* it )
: v( it->v ), s1360( it->s1360 ), s1315( s381 ), s1314( new s1050( NULL, 
vector<s278*>(	{ s1315, s1360->second } ) ) ){}
s278* s1027::s323(){
s278* s718 = NULL;
if( s1360 != v->s329().end() ) {
s718 = s1360->second;
++s1360;}
return s718;}
s278* s1027::s1054(){
return (*s1360).second.s16<s503*>();}
s278* s1027::Idx(){
return (*s1360).first.s16<s503*>();}
s278* s1027::El(){
s278* s718 = NULL;
if( s1360 != v->s329().end() ) {
s1314->assign( vector<s504>(
{ ( *s1360 ).first.s16<s503*>(),( *s1360 ).second.s16<s503*>() } ));
s718 = s1360->second;
++s1360;}
return s718;}
void s1027::reverse(){
s969 = true;
s1410 = std::make_reverse_iterator( s1360 );}
s1554::s1554( s1553* v_, s1028 it, s1028 sent )
: v( v_ ), s1360( it ), s1202( sent ), s1315( s381 ), s1314( new s1050( NULL,
vector<s278*>( { s1315, s1360->second } ) ) ){}
s1554::s1554( s1554* it )
: v( it->v ), s1360( it->s1360 ), s1315( s381 ), s1314( new s1050( NULL,
vector<s278*>( { s1315, s1360->second } ) ) ){}
s278* s1554::s323(){
s278* s718 = NULL;
if( s1360 != v->s329().end() ) {
s718 = s1360->second;
++s1360;}
return s718;}
s278* s1554::s1054(){
return ( *s1360 ).second.s16<s503*>();}
s278* s1554::Idx(){
return ( *s1360 ).first.s16<s503*>();}
s278* s1554::El(){
s278* s718 = NULL;
if( s1360 != v->s329().end() ) {
s1314->assign( vector<s504>(
{ ( *s1360 ).first.s16<s503*>(),( *s1360 ).second.s16<s503*>() } ) );
s718 = s1360->second;
++s1360;}
return s718;}
s1450::s1450( s1449* v_, s1028 it, s1028 sent )
: v( v_ ), s1360( it ), s1202( sent ), s1359( (uint64_t)-1 ), s1315( new s1704( NULL, -1 ) ),
s1314( new s1050( NULL, vector<s278*>( { s1315, s1454::proto } ) ) ){
if( v.s14() ) {
s1359 = std::distance( v->s329().begin(), it );
assert( s1359 >= 0 );}}
s1450::s1450( s1449* v_, s1398 it, s1398 sent )
: v( v_ ), s1410( it ), s1663( sent ), s1359( (uint64_t)-1 ), s1315( new s1704( NULL, -1 ) ),
s1314( new s1050( NULL, vector<s278*>( { s1315, s1454::proto } ) ) ){
if( v.s14() ) {
s1359 = v->size() - std::distance( v->s329().rbegin(), it ) - 1;
assert( s1359 >= 0 );}
s969 = true;}
s1450::s1450( s1450* it )
: v( it->v ), s1360( it->s1360 ), s1359( it->s1359 ), s1315( new s1704( NULL, 0 ) ),
s1314( new s1050( NULL, vector<s278*>( { s1315, new s1454( NULL, *s1360)  } ) ) ){
s969 = it->s969;}
void s1450::reverse(){
s969 = true;
s1410 = std::make_reverse_iterator( s1360 );}
s278* s1450::s323(){
s278* s718 = NULL;
if( !s969 ) {
if( s1359 < v->s329().size() )
s718 = new s1454( NULL, v->s329()[s1359++] );}
else {
if( s1359 != s1272 )
s718 = new s1454( NULL, v->s329()[s1359--] );}
return s718;}
s278* s1450::s1054(){
return new s1454( NULL, *s1360 );}
s278* s1450::Idx(){
*s1315->s373() = s1359 - 1;
return s1315;}
s278* s1450::El(){
*s1315->s373() = s1359 - 1;
return s1315;}
bool s1450::operator==( const Iterator* r ){
if( !s969 )
return s1360 == ( (s1450*)r )->s1360;
else
return s1410 == ( (s1450*)r )->s1410;}
bool s1450::operator<( const Iterator* r ){
if( !s969 )
return s1360 < ( (s1450*)r )->s1360;
else
return s1410 < ( (s1450*)r )->s1410;}
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
vector<wstring> s1477( { L":typedTable", L":untypedTable" } );
s324::s324( s269* s307, s502* s613, const wstring& s79, const s270* ast_,
const wstring& s74 )
: s1573( s307, s613, ast_ ){
TDException s1061( s7::s1536, s1020, ast_ );
s1344 = s1285;
if( s79.size() ) {
load( s79, s613, s74 );}
if( !s513 )
s513 = ( s765.s13() ? 0 : s765->s367() );}
s324::s324( const s324& right, const s270* ast_ )
: s1573( right.s307, right.ns, ast_ ){
s364 = right.s364;
s1344 = right.s1344;
s335 = right.s335;
s325 = right.s325;
s513 = right.s513;
setWh( right.s645() );}
s324::s324( s269* s307, const std::vector<s278*>& l,
s502* s613, const s270* ast_, s1172 s745, s1172 s1324,
s1172 s1431 )
: s1573( s307, s613, ast_ ){
s1344 = s1285;
s335 = s1431;
s325 = s1324;
if( s745 )
s513 = s745;
else
s513 = s765.s13() ? 0 : s765->s367();
if( l.size() )
s616::s1393( ( vector<s278*>& )l, s1477 );
s1480( l, s613 );}
s324::s324( s269* s307, s1172 s1432, s502* s613, const s270* ast_ )
: s1573( s307, s613, ast_ ){
s1344 = s1285;
s335 = s1432;
if( s1432 ) {
s869::Cont v = { s1051->s367(), s1344, s335 };
s325 = s307->TR().s1155( v );
s869::Cont v1 = { s765->s367(), s325 };
s513 = s307->TR().s1155( v1 );}}
s324::~s324(){
s364.clear();}
void s324::s1480( const vector<s278*>& s741, s502* s613 ){
TDException s1061( s7::s1458, s1020, s628() );
if( s741.empty() )
return;
s490 pc = s741[0]->s514();
if( pc == s493 && s613->s514() != s494 ) {
throw s1061.s1099( L"references are not allowed in constructors of data members" );}
if( s741[0]->s367() == s1289 ) {
wstring s1428, s674, s1418;
wstring s79 = s741[0]->to_wstring();
if( s79.empty() )
return;
if( s79[0] == L'[' ) {
s1418 = s79;}
else if( s79[0] == L']' ) {
s364.clear();
wstring snum = s79.substr( s79.rfind( L" " ) );
size_t s167 = std::stoi( snum );
for( size_t n = 0; n < s167; ++n )
s364.push_back( s307->TR().s542( s335, s613, s613->s900() ) );}
else {
if( s79.find( L'<' ) == string::npos )
throw new s17( L"wrong vector constructor syntax: missing element type" );
s1301( s307, s79, s1428, s674 );
if( !s674.empty() && s674[0] == L'[' )
s1418 = s674;
if( !s1428.empty() )
s1298( s1428, s513, s325, s335 );}
if( !s1418.empty() )
load( s1418, s613, L"," );}
else if( s741[0]->s367() == s367() ||
s741[0]->s367() == s765->s367() ) {
s364.assign( ( (s324*)s741[0] )->s364.begin(),
( (s324*)s741[0] )->s364.end() );}}
void s324::s1300( const wstring& s79, /*wstring& s1428, wstring& s674,*/
s502* s613, const wstring& s74 ){
assert( !s79.empty() );
wstring s1428, s674, s1418;
if( s79[0] == L'[' ) {
s1418 = s79;}
else {
s1301( s307, s79, s1428, s674 );
if( !s674.empty() && s674[0] == L'[' )
s1418 = s674;
if( !s1428.empty() )
s1298( s1428, s513, s325, s335 );}
if( !s1418.empty() ) {
load( s1418, s613, s74 );}
else if( !s674.empty() ) {
if( s674[0] == L']' && s674.find_first_not_of(
s4::digits + s4::s50, 1 ) == string::npos ) {
s364.push_back( 0 );
s364.push_back( new s375( s307, s674 ) );}}}
s1172 s324::s1339( const std::wstring& s1428, s869::Cont& s613 ){
s1172 s718;
s869::Cont vt;
size_t pos = 0;
s1172 s1432 = 0;
s307->TR().s1165( s1428, pos, vt );
s718 = s307->TR().s1112( s869( vt ), false );
if( s718 )
return s718;
for( size_t n = 1; n < vt.size(); n += 2 ) vt[n] = 0;
vt.erase( std::remove( begin( vt ), end( vt ), 0 ), end( vt ) );
s869::Cont s1438( begin( vt ) + 1, end( vt ) );
if( s1438.size() > 1 )
s1432 = s307->TR().s1155( s1438 );
else
s1432 = s1438[0];
s869::Cont v = { s1051->s367(), s1285, s1432 };
s1172 s1326 = s307->TR().s1155( v );
s613 = { s765->s367(), s1326 };
s718 = s307->TR().s1155( s613 );
return s718;}
void s324::s1298( const std::wstring& s1428, s1172& pt, s1172& et,
s1172& vt ){
s869::Cont s613;
pt = s1339( s1428, s613 );
et = s613[1];
const s869& s1435 = s307->TR().s1114( et );
vt = s1435.s367( 4 );
return;
s869::Cont s1434;
size_t pos = 0;
s307->TR().s1165( s1428, pos, s1434 );
for( size_t n = 1; n < s1434.size(); n += 2 ) s1434[n] = 0;
s1434.erase( std::remove( begin( s1434 ), end( s1434 ), 0 ), end( s1434 ) );
s869::Cont s1438( begin( s1434 ) + 1, end( s1434 ) );
if( s1438.size() > 1 )
s335 = s307->TR().s1155( s1438 );
else
s335 = s1438[0];
s869::Cont v = { s1051->s367(), s1344, s335 };
s325 = s307->TR().s1155( v );
s869::Cont v1 = { s765->s367(), s325 };
s513 = s307->TR().s1155( v1 );}
void s324::load( const wstring& s79, s502* s613, const wstring& s74 ){
TDException s1061( s7::s1247, s1020, s628() );
size_t pos = 0;
const s1034* s1160 = NULL;
if( s628() && s628()->Nqj() )
s1160 = s628()->Nqj()->s1107();
vector<s1::s9<s6::s145>> s97;
s6::s183( s1160, s79, pos, s97, true, s74 );
wstring ownerName = s628()->s275( L"ownerName" );
bool s1493 = false;
if( ( s628()->s275( L"ownerType" ) == L"CallSite" ) &&
( ownerName == L"new" || ownerName.find( L"new<" ) == 0 ) )
s1493 = true;
if( s97.size() ) {
s1172 pt = 0;
for( size_t n = 0; n < s97.size(); ++n ) {
s1036 s231 = new s270( L"", *s97[n] );
s231->s1512( s335 );
s364.push_back( s278::s525( *s231, s307, s613, s613->s305() ) );
if( s364.back()->s514() != s493 ) {
if( n == 0 )
pt = s364.back()->s367();
else if( pt && s364.back()->s367() != pt )
throw s1061.s1099( L"different elements types in vector" );}}
if( !s1493 ) {
if( !s335 && s364[0]->s367() ) {
s335 = s364[0]->s367();
s869::Cont v = { s1051->s367(), s1344, s335 };
s325 = s307->TR().s1155( v );
s869::Cont v1 = { s765->s367(), s325 };
s513 = s307->TR().s1155( v1 );}
else if( s335 != s364[0]->s367() )
throw s1061.s1099( L"vector's element type doesn't match the vector type" );}}}
s502* s324::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
TDException s1061( s7::s1459, s1020, &s737,
L"wrong vector constructor syntax" );
wstring s = s307->TR().s1430( s737.s298() );
wstring sv;
wstring s362 = s369();
wstring s1428, s674;
s1172 pt = 0, et = 0, vt = 0;
if( s737.s275( L"ownerType" ) == L"CallSite" ) {
wstring s1490 = s737.s275( L"ownerName" );
if( s1490.find( L"new<Vector<" ) == 0 ) {
wstring stype = s1490.substr( 4, s1490.size() - 5 );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s1061.s1099( L"missing element type" );
s1301( s307, s, s1428, s674 );
if( !s674.empty() && ( s674[0] == L'[' || s674[0] == L']' ) )
sv = s674;
if( !s1428.empty() )
s1298( s1428, pt, et, vt );}
else if( 0 && s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
vector<s278*> s741;
wstring stype = s.substr( 0, s.rfind( L">" ) + 1 );
s869::Cont ct;
s1172 s1522 = s1339( stype, ct );
s1172 s1324 = ct[1];
const s869& s1435 = s307->TR().s1114( s1324 );
s1172 s1431 = s1435.s367( 4 );
s278::s1501( s737, s307, s613, s347, s741 );
return new s324( s307, s741, s613, s628(), s1522, s1324, s1431 );}
else
return 0;
return new s324( s307, { new s375( s307,sv ) }, s613, &s737,
pt, et, vt );}
void s324::s520( s502* s962 ){
wstring s79 = L"";
TDException s1061( s7::s1011, s1020, s628() );
if( s364.size() == 2 && s364[0].s13() )
s79 = s364[1]->to_wstring();
if( s962->s514() != s494 ||
( (s279*)s962 )->s306() != L"new" || s307->s1497() ) {
if( s79[0] == L']' ) {
s364.clear();
wstring snum = s79.substr( s79.rfind( L" " ) );
size_t s167 = std::stoi( snum );
for( size_t n = 0; n < s167; ++n )
s364.push_back( s307->TR().s542( /**(s270*)ast_*/s335, s962, s962->s900() ) );
}
else {
for( size_t n = 0; n < s364.size(); ++n ) {
if( s364[n]->s514() == s493 ) {
s364[n]->s520( s962 );
s364[n] = s364[n].s16<s387*>()->s393();}
s504 s1205 = s278::s1122( s307, s364[n], s962, (s616*)s962, s962->s305() );
s364[n] = s1205->s517( 0, 0 ).s16<s503*>();
if( !s335 )
s335 = s364[0]->s367();
else if( s335 != s364[n]->s367() )
throw s1061.s1099( L"elements have different types" );}}
if( !s325 ) {
if( !s335 )
throw s1061.s1099( L"vector's element type is not specified" );
s869::Cont v = { s1051->s367(), s1285, s335 };
s1172 s1326 = s307->TR().s1155( v );
s869::Cont s613 = { s765->s367(), s1326 };
s513 = s307->TR().s1155( s613 );}
s1414();}}
void s324::s1062( const vector<s278*>& s741, s502* s613,
const s270* ast_ ){
TDException s1061( s7::s1012, s1020, ast_ );
bool typed;
wstring s1103 = L",";
wstring s1142 = L"\n";
wstring str = L"";
if( s741.size() < 2 )
throw s1061.s1099( L"too few arguments" );
if( ( (s387*)s741[0] )->s644() == L":typedTable" )
typed = true;
else if( ( (s387*)s741[0] )->s644() == L":untypedTable" )
typed = false;
else
throw s1061.s1099( L"unrecognized first parameter" );
if( s741.size() > 2 ) {
s1103 = s741[2]->to_wstring(); //s1166->to_wstring();
}
if( s741.size() > 3 ) {
s1142 = s741[3]->to_wstring(); //s1168->to_wstring();
}
if( s741[1]->s514() == s493 ) {
( (s387*)s741[1] )->s520( s613 );
str = ( (s387*)s741[1] )->s393()->to_wstring();}
else
str = s741[1]->to_wstring();
vector<wstring> s857;
s4::s59( s4::s54( str, s50 ), s1142, s857 );
for( wstring row : s857 ) {
if( typed ) {
s364.push_back( new s324( s307, s307, row, NULL, s1103 ) );}
else {
s1050* pd = (s1050*)s307->TR().s1108( s335 )->s350();
pd->load( row, s613, s1103 );
s364.push_back( pd );}}}
void s324::s365(){
s1573<s1590, s504, s324>::s365();
s363 = s1573<s1590, s504, s324>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s324::s1385, s1287,
{ s1240(), s1240( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s363.emplace( make_pair( L"set", new s352( L"set", &s324::s403, s1287,
{ s1240( { s1687::s1682 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"set-el", new s352( L"set-el", &s324::s1416, s1287,
{ s1240( { s1687::s1724, s7::s1569 } ) }, 2, 2 ) ) );
s363.emplace( make_pair( L"get", new s352( L"get", &s324::s338, 0,
{ s1240( { s1687::s1724 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"append", new s352( L"append", &s324::s1481, s1287,
{ s1240( { s7::s1569 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"resize", new s352( L"resize", &s324::s341, s1287,
{ s1240( { s1702 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"eq", new s352( L"eq", &s324::s414, s1285,
{ s1240( { s7::s1566 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"load-table", new s352( L"load-table", &s324::s854,
s1285, { s1240( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s363.equal_range( L"get" ).first->second->s1413( true );
s363.equal_range( L"new" ).first->second->s1413( true );
s307->TR().s1302( s513, s7::s1584, s1687::s1683 );
s307->TR().s1302( s513, s7::s1582, s1687::s1681 );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
s502* s324::s371( s502* s613, const vector<s278*>& l, const s270* ast_ ) const{
if( !s335 )
throw new s17( L"vector's element type is not specified" );
return new s324( s307, l, s613, ast_, s513, s325, s335 );}
s502* s324::s371( s502* s613, const std::vector<s1172>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s869::Cont s1091, s1221;
s510::s1109( vt, idx, s1091 );
s869 s1090 = s307->TR().s1114( s1091[0] );
s324* s718 = new s324( s307, 0, NULL );
s718->ns = s613;
s718->s325 = s307->TR().s1112( s1090 );
s718->s335 = s1090.s367( 4 );
s869 s647( vt );
s718->s513 = s307->TR().s1112( s647 );
return s718;}
s1172 s324::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"get" )
s718 = s335;
else
s718 = s1573::s1332( s1728, l );
return s718;}
inline bool
s324::s522( const s502* s523 ) const{
return ( ( (s324*)s523 )->s325 == s325 );}
s278* s324::s350() const{
return new s324( *this );}
void s324::s372( s278* p ) const{
p = new s324( *this );}
Iterator* s324::s1305( const s502* idx ){
s1590::iterator it;
int i = (int)*idx;
if( i >= (int)s364.size() )
it = s364.end();
else {
if( i < 0 ) {
i = (int)s364.size() + i;
if( i < 0 )
i = 0;}
it = s364.begin() + i;}
return new s1057( this, it, it == s364.end() ? it : it+1 );}
Iterator* s324::s1327( const s502* _val ){
for( auto it = begin( s364 ); it != end( s364 ); ++it )
if( it->s16<s502*>()->operator==( _val ) )
return new s1057( this, it, it+1 );
return new s1057( this, end( s364 ), end( s364 ));}
s502* s324::s1334( Iterator* it ){
size_t n = std::distance( begin( s364 ), ( (s1057*)it )->s1270() );
return new s361( s307, (int)n );}
Iterator* s324::s1329() {
return new s1057( this, s364.begin(), s364.begin()+1 ); }
Iterator* s324::s1333() {
return new s1057( this, s364.end(), s364.end() ); }
#undef s734
#define s734 ((s324*)(s503*)*s281)
inline void s324::s1385( s502** s281, size_t s518 ){
s324* ps = (s324*)DR;
s324* s718;
if( s518 == 2 ) {
s718 = (s324*)( (s324*)s281[1] )->s350();}
else if( s281[2]->s1340().s367() == s765->s367() ) {
s718 = (s324*)( (s324*)s281[2] )->s350();}
else {
vector<s278*> v;
for_each( s281 + 2, s281 + s518, [&v]( s502* s364 )
{ return v.push_back( (s278*)s364 ); } );
s718 = new s324( ps->s307, v, ps->ns, ps->s628() );}
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s324::s403( s502** s281, size_t s518 ){
s324* v = ( (s324*)DR );
s337* seq = (s337*)s281[2];
Iterator* s1125 = seq->s322( NULL );
v->s364.clear();
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
v->s364.push_back( p );}}
inline void s324::s1416( s502** s281, size_t s518 ){
s324* v = ( (s324*)DR );
size_t idx = (size_t)(int)*s281[2];
if( idx >= v->size() )
throw new s17( L"vector index is out of range",
(uint32_t)s17::s18::s25 );
s281[3]->s372( v->s364[idx] );}
inline void s324::s338( s502** s281, size_t s518 ){
s324* pv = (s324*)DR;
int idx = (int)*s281[2];
if( idx < 0 ) {
idx = (int)pv->s364.size() + idx;
if( idx < 0 )
throw new s17( L"negative index is out of bound" );}
if( idx >= (int)pv->s364.size() )
throw new s17( L"index is out of bound" );
*s281 = (s502*)(s278*)pv->s364[idx];}
inline void s324::s1481( s502** s281, size_t s518 ){
s324* pv = (s324*)DR;
const s502* s1727 = pv->s307->TR().s1108( pv->s335 );
( (s324*)DR )->s364.push_back( (s278*)s1727->s1711( s281[2] ) );}
inline void s324::s341( s502** s281, size_t s518 ){
int size = (int)*s281[2];
int oldsize = (int)( (s324*)DR )->s364.size();
( (s324*)DR )->s364.resize( size );
for( int i = oldsize; i < size; ++i )
( (s324*)DR )->s364[i] = ( (s324*)DR )->s307->TR().s542(
( (s324*)DR )->s325, ( (s324*)DR )->s307, ( (s324*)DR )->s519 );}
/*
inline void s324::s342( s502** s281, size_t s518 ){
( (s324*)DR )->s364.clear();}
*/
inline void s324::s414( s502** s281, size_t s518 ){
size_t size = ( (s324*)DR )->s364.size();
s324* right = (s324*)s281[2];
if( right->s364.size() != size ) {
*( (s361*)*s281 )->s373() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s364[n] != ( (s324*)DR )->s364[n] ) {
*( (s361*)*s281 )->s373() = 0;
return;}}
*( (s361*)*s281 )->s373() = 1;}
inline void s324::s854( s502** s281, size_t s518 ){
s324* pv = ( (s324*)DR );
s490 pc = s281[2]->s514();
if( pc == s1174 ) {
if( ( (s387*)s281[2] )->s644().find( L"typedTable" ) != string::npos ) {
vector<s278*> s741( s518 - 2 );
for( size_t n = 2; n < s518; ++n )s741[n - 2] = s281[n];
pv->s1062( s741, pv->ns, pv->s628() );
return;}}
s337* seq = (s337*)s281[2];
Iterator* s1125 = seq->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
pv->s364.push_back( p );}}
struct s921{
vector<s504>& s364;
s921( vector<s504>& s731 ) : s364( s731 ) {}
bool operator()( const s504 l, const s504 r ) const{
return l.s16<s502*>()->operator<( r.s16<s502*>() );}
};
s502* s324::sort( bool s969, s910* cmp ){
s921 s920( s364 );
if( s969 ) {
if( cmp )
std::sort( s364.rbegin(), s364.rend(), *cmp );
else
std::sort( s364.rbegin(), s364.rend(), s920 );}
else {
if( cmp )
std::sort( s364.begin(), s364.end(), *cmp );
else
std::sort( s364.begin(), s364.end(), s920 );}
return this;}
wstring s324::to_wstring() const{
wstring s718 = L"[";
if( s645() == s7::s943 )
s718 += L"_not_set_";
else {
for( size_t n = 0; n < s364.size(); ++n )
s718 += s364[n]->to_wstring() + ( n == s364.size() - 1 ? L"" : L", " );}
s718 += L"]";
return s718;}
void s324::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Vector : " << endl;
for( size_t n = 0; n < s364.size(); ++n )
s364[n]->s311( pd, s202 + s435 );}
size_t s324::s331() const{
size_t s718 = 0;
for( size_t n = 0; n < s364.size(); ++n )
s718 = s718 * ( ( s502* )&( *s364[n] ) )->s331() << 1;
return s718;}
bool s324::operator==( const s502* p ) const{
if( ( (s324*)p )->s364.size() != s364.size() )
return false;
for( size_t n = 0; n < s364.size(); ++n )
if( !( ( s278* )&( *s364[n] ) == (s278*)( (s324*)p )->s364[n] ) )
return false;
return true;}
bool s324::operator<( const s502* p ) const{
return false;}
Iterator* s324::s322( s401* rv ){
if( !rv )
return new s1057( this, begin( s364 ), end( s364 ) );
s1269 pr = rv->s1338( this );
return new s1057( this,
pr.first.s16<s1263*>()->s1270(), pr.second.s16<s1263*>()->s1270() );}
s794::s794( s269* s307, s502* s613, const wstring& s79,
const s270* ast_, const wstring& s74 )
: s337( s307, s613, ast_ ){
if( s79.size() ) {
vector<s1::s9<s6::s145>> s157;
const s1034* s1160 = NULL;
if( ast_ )
s1160 = ast_->Nqj()->s1107();
if( s79[0] == L'[' ) {
size_t pos = 0;
s6::s183( s1160, s79, pos, s157, true );}
else
s6::s183( s1160, s79, s157, true );
for( size_t n = 0; n < s157.size(); ++n ) {
s270 s231( L"", *s157[n] );
s364.push_back( s278::s525( s231, s307, s613, s613->s305() ) );}}
s513 = s788.s13() ? 0 : s788->s367();}
s794::s794( s269* s307, const vector<s278*>& l,
const s270* ast_ )
: s337( s307, NULL, ast_ ){
for( auto s1171 : l )
s364.push_back( s1171 );
s513 = s788->s367();}
s794::s794( const s794& right )
: s337( right ){
s364 = right.s364;
s513 = right.s513;}
s794::~s794(){
s364.clear();
s519.clear();}
void s794::s1300( const wstring& s79, wstring& s1428, wstring& s674,
vector<s1::s9<s6::s145>>& s97, const s270* ast_, const wstring& s74 ){
assert( !s79.empty() );
if( s79[0] == L'[' ) {
size_t pos = 0;
const s1034* s1160 = NULL;
if( ast_ && ast_->Nqj() )
s1160 = ast_->Nqj()->s1107();
s6::s183( s1160, s79, pos, s97, true, s74 );}
else
s1301( s307, s79, s1428, s674 );}
s502* s794::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
wstring sv;
wstring s362 = s369();
if( s.find( L"UVector[" ) == 0 )
sv = s.substr( 7 );
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s54( s.substr( s362.size() ), s50 );
if( sv[0] != L'(' )
throw new s17( L"wrong vector constructor syntax" );
sv = s4::s54( sv.substr( 1, sv.size() - 2 ), L" " );}
else
return 0;
return new s794( s307, s613, sv, &s737 );}
void s794::s520( s502* s962 ){
for( size_t n = 0; n < s364.size(); ++n ) {
if( s364[n]->s514() == s493 ) {
s364[n]->s520( s962 );
s364[n] = s364[n].s16<s387*>()->s393();}
s504 s1205 = s278::s1122( s307, s364[n], s962, NULL, s962->s305() );
s364[n] = s1205;}
s513 = s788->s367();
setWh( s7::s942 );
s519 = s962->s900();}
void s794::s365(){
s363.insert( make_pair( L"set", new s352( L"set", &s794::s403, s1287,
{ s1240( { s1285, s7::s1565, s7::s1571 } ) }, 2, (size_t)-1 ) ) );
s363.insert( make_pair( L"get", new s352( L"get", &s794::s338, 0,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"fst", new s352( L"fst", &s794::s1101, 0,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"snd", new s352( L"snd", &s794::s1186, 0,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"append", new s352( L"append", &s794::s1481, s1287,
{ s1240( { s7::s1565, s7::s1571 } ) }, 1, (size_t)-1 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s794::s340, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"resize", new s352( L"resize", &s794::s341, s1287,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", &s794::s342, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"eq", new s352( L"eq", &s794::s414, s1285,
{ s1240( { s7::s1566 } ) }, 1, 1 ) ) );
s363.equal_range( L"get" ).first->second->s1413( true );
s363.equal_range( L"fst" ).first->second->s1413( true );
s363.equal_range( L"snd" ).first->second->s1413( true );}
s502* s794::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s794( s307, s613, L"" );}
s502* s794::s371( s502* s613, const std::vector<s1172>& vt ) const{
assert( 0 );
return 0;}
s1172 s794::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"fst" )
s718 = s364[0]->s367();
else if( s1728 == L"snd" )
s718 = s364[1]->s367();
else if( s1728 == L"get" ) {
int n = (int)*l[0];
s718 = s364[n]->s367();}
return s718;}
inline bool
s794::s522( const s502* s523 ) const{
return ( ( (s324*)s523 )->s367() == s367() );}
s1172 s794::s328() const{
throw new s17( L"UntypedVector doesn't have element type." );}
s278* s794::s350() const{
return new s794( *this );}
void s794::s372( s278* p ) const{
p = new s794( *this );}
void s794::assign( const vector<s504>& p ){
s364.assign( begin( p ), end( p ) );}
Iterator* s794::s1329() {
return new s1053( this, s364.begin(), s364.begin() + 1 ); }
Iterator* s794::s1333(){
return new s1053( this, s364.end(), s364.end() ); }
s1269 s794::s1338(){
return std::make_pair( s1329(), s1333() );}
#undef s734
#define s734 ((s794*)(s503*)*s281)
inline void s794::s403( s502** s281, size_t s518 ){
s281[3]->s372( ( (s794*)DR )->s364[(int)*s281[2]] );}
inline void s794::s338( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s794*)DR )->s364[(int)*s281[2]];}
inline void s794::s1101( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s794*)DR )->s364[0];}
inline void s794::s1186( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s794*)DR )->s364[1];}
inline void s794::s1481( s502** s281, size_t s518 ){
/*if( ( (s794*)DR )->s328() != s281[2]->s515() )
throw new s17( L"unmatched element type" );*/
( (s794*)DR )->s364.push_back( s281[2]->s350() );}
inline void s794::s340( s502** s281, size_t s518 ){
*( (s361*)*s281 )->s373() = (int)( (s794*)DR )->s364.size();}
inline void s794::s341( s502** s281, size_t s518 ){
int size = (int)*s281[2];
( (s794*)DR )->s364.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s794*)DR )->s364[i] = ( (s794*)DR )->s307->s222(
( (s794*)DR )->s325, ( (s794*)DR )->s519 ).s16<s503*>();*/
}
inline void s794::s342( s502** s281, size_t s518 ){
( (s794*)DR )->s364.clear();}
inline void s794::s414( s502** s281, size_t s518 ){
size_t size = ( (s794*)DR )->s364.size();
s794* right = (s794*)s281[2];
if( right->s364.size() != size ) {
*( (s361*)*s281 )->s373() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s364[n] != ( (s794*)DR )->s364[n] ) {
*( (s361*)*s281 )->s373() = 0;
return;}}
*( (s361*)*s281 )->s373() = 1;}
inline void s794::s343( s502** s281, size_t s518 ){
*( (s361*)*s281 )->s373() = (int)( (s794*)DR )->s364.size();}
wstring s794::to_wstring() const{
wstring s718 = L"UT[";
if( s645() == s7::s943 )
s718 += L"_not_set_";
else {
for( size_t n = 0; n < s364.size(); ++n )
s718 += s364[n]->to_wstring() + ( n == s364.size() - 1 ? L"" : L", " );}
s718 += L"]";
return s718;}
void s794::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s364.size(); ++n )
s364[n]->s311( pd, s202 + s435 );}
size_t s794::s331() const{
size_t s718 = 0;
for( size_t n = 0; n < s364.size(); ++n )
s718 = s718 * ( ( s502* )&( *s364[n] ) )->s331() << 1;
return s718;}
bool s794::operator==( const s502* p ) const{
if( ( (s794*)p )->s364.size() != s364.size() )
return false;
for( size_t n = 0; n < s364.size(); ++n ) {
const s502* l = s364[n].s16<s502*>();
const s502* r = ( (const s794*)p )->s364[n].s16<s502*>();
if( !( *l == r ) )
return false;}
return true;}
bool s794::operator<( const s502* p ) const{
return false;}
Iterator* s794::s322( s401* rv ){
return NULL;}
/*s505 s794::s323()
{
if( s326 == s364.end() ) {
return NULL;}
s505 s718 = ( *s326 ).s16<s502*>();
s326++;
return s718;
}*/
s1050::s1050( s269* s307, s502* s613, const std::wstring& s79,
const s270* ast_, const std::wstring& s74 )
: s794( s307, ast_ ){
s1344 = s1285;
if( s79.size() ) {
s1300( s79, /*s1428, s674,*/ s613, s74 );
}
if( !s513 )
s513 = s1051.s13() ? 0 : s1051->s367();}
s1050::s1050( s269* s307, const std::vector<s278*>& l, const s270* ast_ )
: s794( s307, l, ast_ ){
s513 = s1051->s367();}
s1050::s1050( const s1050& right, const s270* ast_ )
: s794( right ){
s364.assign( begin( right.s364 ), end( right.s364 ) );
s513 = right.s513;
s325 = right.s325;
s1344 = right.s1344;
s335 = right.s335;}
s502* s1050::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s307->TR().s1430( s737.s298() );
wstring sv;
wstring s362 = s369();
if( s.find( L"[[" ) == 0 )
sv = s.substr( 1, s.size() - 2 );
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
if( b == string::npos || e == string::npos )
throw new s17( L"wrong tuple constructor syntax: missing element types" );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );}
else
return 0;
s1050* s718 = new s1050( s307, s613, sv, &s737 );
return s718;}
void s1050::s520( s502* s962 ){
wstring s79 = L"";
TDException s1061( s7::s1011, s1020, s628() );
if( s364.size() == 2 && s364[0].s13() )
s79 = s364[1]->to_wstring();
if( s79[0] == L']' ) {
s364.clear();
wstring snum = s79.substr( s79.rfind( L" " ) );
s1036 ast_ = new s270( s79.substr( 9, s79.size() - snum.size() - 10 ), s628()->Nqj() );
size_t s167 = std::stoi( snum );
for( size_t n = 0; n < s167; ++n )
s364.push_back( s307->TR().s542( *(s270*)ast_, s962, s962->s900() ) );}
else {
for( size_t n = 0; n < s364.size(); ++n ) {
if( s364[n]->s514() == s493 ) {
s364[n]->s520( s962 );
s364[n] = s364[n].s16<s387*>()->s393();}
s504 s1205 = s278::s1122( s307, s364[n], s962, NULL, s962->s305() );
s364[n] = s1205;}}
setWh( s7::s942 );
s519 = s962->s900();}
void s1050::s365(){
s363.insert( make_pair( L"set", new s352( L"set", &s1050::s403, s1287,
{ s1240( { s7::s1566 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"set-el", new s352( L"set-el", &s1050::s1417, s1287,
{ s1240( { s1285, s7::s1565, s7::s1571 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"get", new s352( L"get", &s1050::s338, 0,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"fst", new s352( L"fst", &s1050::s1101, 0,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"snd", new s352( L"snd", &s1050::s1186, 0,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"append", new s352( L"append", &s1050::s1481, s1287,
{ s1240( { s7::s1565, s7::s1571 } ) }, 1, (size_t)-1 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s1050::s340, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"resize", new s352( L"resize", &s1050::s341, s1287,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", &s1050::s342, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"eq", new s352( L"eq", &s1050::s414, s1285,
{ s1240( { s7::s1566 } ) }, 1, 1 ) ) );
s363.equal_range( L"get" ).first->second->s1413( true );
s363.equal_range( L"fst" ).first->second->s1413( true );
s363.equal_range( L"snd" ).first->second->s1413( true );}
s502* s1050::s371( s502* s613, const std::vector<s1172>& vt ) const{
s1050* s718 = new s1050( s307, NULL, L"" );
s869 s647( vt );
s718->s513 = s718->s325 = s718->s335 = s307->TR().s1112( s647 );
return s718;}
s502* s1050::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
s1050* s718 = new s1050( s307, l, ast_ );
return s718;}
void s1050::s1300( const wstring& s79, /*wstring& s1428, wstring& s674,*/
s502* s613, const wstring& s74 ){
assert( !s79.empty() );
wstring s1428, s674, s1418;
if( s79[0] == L'[' ) {
s1418 = s79.substr( 1, s79.size() - 2 );}
else {
s1301( s307, s79, s1428, s674 );
if( !s674.empty() && s674[0] == L'[' )
s1418 = s674.substr( 1, s674.size() - 2 );
if( !s1428.empty() )
s1298( s1428 );}
if( !s1418.empty() ) {
load( s1418, s613, s74 );}
else if( !s674.empty() ) {
if( s674.find_first_not_of( s4::digits ) == string::npos ) {
s364.push_back( 0 );
s364.push_back( new s375( s307, s674 ) );}}}
void s1050::s1298( const std::wstring& s1428 ){
s869::Cont vt;
size_t pos = 0;
s307->TR().s1165( s1428, pos, vt );
for( size_t n = 1; n < vt.size(); n += 2 ) vt[n] = 0;
vt.erase( std::remove( begin( vt ), end( vt ), 0 ), end( vt ) );
s869::Cont s1438( begin( vt ), end( vt ) );
if( s1438.size() > 1 )
s335 = s307->TR().s1155( s1438 );
else
s335 = s1438[0];
s513 = s325 = s335;}
void s1050::load( const wstring& s79, s502* s613, const wstring& s74 ){
TDException s1061( s7::s1246, s1020, s628() );
size_t pos = 0;
const s1034* s1160 = NULL;
if( s628() && s628()->Nqj() )
s1160 = s628()->Nqj()->s1107();
vector<s1::s9<s6::s145>> s97;
s6::s183( s1160, s79, pos, s97, true, s74 );
if( s97.size() ) {
s869::Cont s1434;
if( s513 ) {
const s869& vt = s307->TR().s1114( s513 );
s1434.assign( vt.s877().begin(), vt.s877().end() );
if( s97.size() != ( s1434.size() - 2 ) / 2 )
throw s1061.s1099( L"wrong number of elements passed for inititalizing tuple" );}
else
s1434.push_back( s1051->s367() );
for( size_t n = 0; n < s97.size(); ++n ) {
s270 s231( L"", *s97[n] );
s364.push_back( s278::s525( s231, s307, s613, s613->s305() ) );
if( s513 ) {
if( s364.back()->s367() != s1434[( n + 1 ) * 2] )
throw s1061.s1099( L"element type doesn't match the tuple definition" );}
else
s1434.push_back( s364.back()->s367() );}
if( !s335 ) {
s513 = s307->TR().s1155( s1434 );
s335 = s325 = s513;}}
s1414();}
s1172 s1050::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"fst" )
s718 = s307->TR().s1114( s513 ).s367( ( 0 + 1 ) * 2 );
else if( s1728 == L"snd" )
s718 = s307->TR().s1114( s513 ).s367( ( 1 + 1 ) * 2 );
else if( s1728 == L"get" ) {
int n = (int)*l[0];
s718 = s307->TR().s1114( s513 ).s367( ( n + 1 ) * 2 );}
return s718;}
#undef s734
#define s734 ((s1050*)(s503*)*s281)
inline void s1050::s403( s502** s281, size_t s518 ){
s1050* s881 = ( (s1050*)DR );
if( s881->s367() != s281[2]->s367() )
throw new s17( L"mismatched types in assignment expression" );
s281[2]->s372( s881 );}
inline void s1050::s1417( s502** s281, size_t s518 ){
s1050* s881 = ( (s1050*)DR );
if( s881->s367() != s281[3]->s367() )
throw new s17( L"mismatched types in assignment expression" );
s281[3]->s372( ( (s1050*)DR )->s364[(int)*s281[2]] );}
inline void s1050::s338( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s1050*)DR )->s364[(int)*s281[2]];}
inline void s1050::s1101( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s1050*)DR )->s364[0];}
inline void s1050::s1186( s502** s281, size_t s518 ){
*s281 = (s502*)(s278*)( (s1050*)DR )->s364[1];}
inline void s1050::s1481( s502** s281, size_t s518 ){
s1050* s881 = ( (s1050*)DR );
const s1050* pro = (s1050*)s881->s307->TR().s1108( DR->s367() );
size_t n = s881->s364.size();
if( n >= pro->s364.size() )
throw new s17( L"unmatched element type" );
if( false == pro->s364[n]->s522( s281[2] ) )
throw new s17( L"unmatched element type" );
/*if( ( (s794*)DR )->s328() != s281[2]->s515() )
*/
s881->s364.push_back( s281[2]->s350() );}
inline void s1050::s340( s502** s281, size_t s518 ){
*( (s361*)*s281 )->s373() = (int)( (s1050*)DR )->s364.size();}
inline void s1050::s341( s502** s281, size_t s518 ){
int size = (int)*s281[2];
( (s1050*)DR )->s364.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s794*)DR )->s364[i] = ( (s794*)DR )->s307->s222(
( (s794*)DR )->s325, ( (s794*)DR )->s519 ).s16<s503*>();*/
}
inline void s1050::s342( s502** s281, size_t s518 ){
( (s1050*)DR )->s364.clear();}
inline void s1050::s414( s502** s281, size_t s518 ){
size_t size = ( (s1050*)DR )->s364.size();
s1050* right = (s1050*)s281[2];
if( right->s364.size() != size ) {
*( (s361*)*s281 )->s373() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s364[n] != ( (s1050*)DR )->s364[n] ) {
*( (s361*)*s281 )->s373() = 0;
return;}}
*( (s361*)*s281 )->s373() = 1;}
inline void s1050::s343( s502** s281, size_t s518 ){
*( (s361*)*s281 )->s373() = (int)( (s1050*)DR )->s364.size();}
s278* s1050::s350() const{
return new s1050( *this );}
void s1050::s372( s278* p ) const{
*p = *this;}
wstring s1050::to_wstring() const{
wstring s718 = L"[[";
if( s645() == s7::s943 )
s718 += L"_not_set_";
else {
for( size_t n = 0; n < s364.size(); ++n )
s718 += s364[n]->to_wstring() + ( n == s364.size() - 1 ? L"" : L", " );}
s718 += L"]]";
return s718;}
s1449::s1449( s269* s307, s502* s613, const wstring& s79, const s270* ast_,
const wstring& s74 )
: s321( s307, s613, ast_ ){
s1300( s79, s613, s74 );}
s1449::s1449( const s1449& right, const s270* ast_ )
: s321( right.s307, NULL, ast_ ){
s364 = right.s364;
s1344 = right.s1344;
s335 = right.s335;
s325 = right.s325;
s513 = right.s513;}
s1449::s1449( s269* s307, const std::vector<s278*>& l, const s270* ast_ )
: s321( s307, NULL, ast_ ){
s1300( L"", NULL, L"" );
if( l.size() ) {
s325 = l[0]->s367();
for( size_t n = 0; n < l.size(); ++n )
s364.push_back( *( (s1454*)l[n] )->s373() );}}
s1449::~s1449(){
s364.clear();}
void s1449::s1300( const wstring& s79, s502* s613, const wstring& s74 ){
s1344 = s1285;
s335 = s1475;
s869::Cont v = { s1051->s367(), s1285, s335 };
s325 = s307->TR().s1155( v );
s513 = s1451->s367();
if( s79.empty() )
return;
wstring s1428, s674, s1418;
if( s79[0] == L'[' ) {
s1418 = s79;}
else {
s1301( s307, s79, s1428, s674 );
if( !s674.empty() && s674[0] == L'[' )
s1418 = s674;
if( s1428 != s369() )
throw new s17( L"wrong syntax of ByteArray declaration" );}
if( !s1418.empty() ) {
load( s1418, s613, s74 );}
else if( !s674.empty() ) {
if( s674[0] == L']' && s674.find_first_not_of(
s4::digits + s4::s50, 1 ) == string::npos ) {
wstring snum = s674.substr( s674.rfind( L" " ) );
size_t s167 = std::stoi( snum );
s364.resize( s167 );}}}
void s1449::load( const wstring& s79, s502* s613, const wstring& s74 ){
TDException s1061( s7::s1457, s1020, s628() );
size_t pos = 0;
const s1034* s1160 = NULL;
if( s628() && s628()->Nqj() )
s1160 = s628()->Nqj()->s1107();
vector<s1::s9<s6::s145>> s97;
s6::s183( s1160, s79, pos, s97, true, s74 );
if( s97.size() ) {
for( size_t n = 0; n < s97.size(); ++n ) {
wstring sit = s97[n]->s173();
wstring snum = sit.substr( sit.rfind( L" " ) );
size_t s167 = std::stoi( snum );
s364.push_back( (tdbyte_t)s167 );}}}
s502* s1449::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s307->TR().s1430( s737.s298() );
wstring sv;
wstring s362 = s369();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw new s17( L"wrong ByteArray constructor syntax: '<' is not allowed here" );}
else
return 0;
return new s1449( s307, s613, sv, &s737 );}
bool s1488( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1449::s520( s502* s962 ){
setWh( s7::s942 );
if( s962 )
s519 = s962->s900();}
void s1449::s365(){
s321<s1546, tdbyte_t, s1449>::s365();
s363 = s321<s1546, tdbyte_t, s1449>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s1449::s1385, s1287,
{ s1240( { s7::s1565, s7::s1571 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s363.emplace( make_pair( L"set", new s352( L"set", &s1449::s403, s1287,
{ s1240( { s1687::s1682 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"set-el", new s352( L"set-el", &s1449::s1416, s1287,
{ s1240( { s1285, s1285 } ) }, 2, 2 ) ) );
s363.emplace( make_pair( L"get", new s352( L"get", &s1449::s338, s1475,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"append", new s352( L"append", &s1449::s1481, s1287,
{ s1240( { s7::s1569 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"resize", new s352( L"resize", &s1449::s341, s1287,
{ s1240( { s1285 } ) }, 1, 1 ) ) );
s363.emplace( make_pair( L"eq", new s352( L"eq", &s1449::s414, s1276,
{ s1240( { s7::s1566 } ) }, 1, 1 ) ) );
s307->TR().s1302( s513, s7::s1584, s1687::s1683 );
s307->TR().s1302( s513, s7::s1582, s1687::s1681 );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
s502* s1449::s371( s502* s613, const vector<s278*>& l, const s270* ast_ ) const{
return new s1449( s307, s613, L"", ast_ );}
s502* s1449::s371( s502* s613, const std::vector<s1172>& vt ) const{
return new s1449( s307, s613, L"" );}
inline bool
s1449::s522( const s502* s523 ) const{
return ( ( (s1449*)s523 )->s367() == s367() );}
s278* s1449::s350() const{
return new s1449( *this );}
void s1449::s372( s278* p ) const{
p = new s1449( *this );}
Iterator* s1449::s1305( const s502* idx ){
s1546::iterator it;
int i = (int)*idx;
if( i >= (int)s364.size() )
it = s364.end();
else {
if( i == -1 )
it = end( s364 );
else if( i < 0 ) {
i = (int)s364.size() + ( i + 1 );
if( i < 0 )
throw new s17( L"wrong range definition: a negative index is beyond vector boundaries" );}
else
it = s364.begin() + i;}
return new s1450( this, it, it + 1 );}
Iterator* s1449::s1327( const s502* _val ){
for( auto it = begin( s364 ); it != end( s364 ); ++it )
if( *it == *( (s1454*)_val )->s373() )
return new s1450( this, it, it + 1 );
return new s1450( this, end( s364 ), end( s364 ) );}
s502* s1449::s1334( Iterator* it ){
size_t n = std::distance( begin( s364 ), ( (s1450*)it )->s1270() );
return new s361( s307, (int)n );}
Iterator* s1449::s1329() {
return new s1450( this, s364.begin(), s364.begin() + 1 ); }
Iterator* s1449::s1333() {
return new s1450( this, s364.end(), s364.end() ); }
#undef s734
#define s734 ((s1449*)(s503*)*s281)
inline void s1449::s1385( s502** s281, size_t s518 ){
s1449* ps = (s1449*)DR;
s1449* s718 = new s1449( ps->s307, ps->s628() );
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s1449::s403( s502** s281, size_t s518 ){
s1449* v = ( (s1449*)DR );
s337* seq = (s337*)s281[2];
Iterator* s1125 = seq->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
v->s364.push_back( *p.s16<s1454*>()->s373() );}}
inline void s1449::s1416( s502** s281, size_t s518 ){
assert( s281[3]->s367() == s1285 );
assert( s281[2]->s367() == s1285 );
s1449* v = ( (s1449*)DR );
size_t idx = (size_t)(int)*s281[2];
v->s364[idx] = *( (s1454*)s281[3] )->s373();}
inline void s1449::s338( s502** s281, size_t s518 ){
s1454* s718 = new s1454( ( (s1449*)DR )->s307,
( (s1449*)DR )->s364[(int)*s281[2]] );
*s281 = (s502*)(s278*)s718;}
inline void s1449::s1481( s502** s281, size_t s518 ){
assert( s281[2]->s367() == s1475 );
( (s1449*)DR )->s364.push_back( *( (s1454*)s281[2] )->s373() );}
inline void s1449::s341( s502** s281, size_t s518 ){
int size = (int)*s281[2];
( (s1449*)DR )->s364.resize( size );}
inline void s1449::s414( s502** s281, size_t s518 ){
size_t size = ( (s1449*)DR )->s364.size();
s1449* right = (s1449*)s281[2];
if( right->s364.size() != size ) {
*( (s376*)*s281 )->s373() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s364[n] != ( (s1449*)DR )->s364[n] ) {
*( (s376*)*s281 )->s373() = false;
return;}}
*( (s376*)*s281 )->s373() = true;}
wstring s1449::to_wstring() const{
wstring s718 = L"[";
if( s645() == s7::s943 )
s718 += L"_not_set_";
else {
for( size_t n = 0; n < s364.size(); ++n )
s718 += std::to_wstring( s364[n] ) + ( n == s364.size() - 1 ? L"" : L", " );}
s718 += L"]";
return s718;}
void s1449::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1449::s331() const{
size_t s718 = 0;
for( size_t n = 0; n < s364.size(); ++n )
s718 = ( s718 * s364[n] ) << 1;
return s718;}
bool s1449::operator==( const s502* p ) const{
if( ( (s1449*)p )->s364.size() != s364.size() )
return false;
for( size_t n = 0; n < s364.size(); ++n )
if( !( s364[n] == ( (s1449*)p )->s364[n] ) )
return false;
return true;}
bool s1449::operator<( const s502* p ) const{
return false;}
Iterator* s1449::s322( s401* rv ){
s1269 pr = rv->s1338( this );
return new s1450( this,
pr.first.s16<s1263*>()->s1270(), pr.second.s16<s1263*>()->s1270() );}
s333::s333( s269* s307, s1172 s1345, s1172 s1431, 
s502* s613, const s270* ast_ )
: s1540( s307, s613, ast_ ){
assert( s1345 && s1431 );
this->s1344 = s1345;
s335 = s1431;
s869 s1325( s869::Cont( { s1051->s367(), 2, s1344, 0, s335, 0 } ) );
s325 = s513 = s307->TR().s1112( s1325 );}
s333::s333( s269* s307, s502* s613, const wstring& s79, const s270* ast_ )
: s1540( s307, s613, ast_ ){
TDException s1061( s7::s1539, s1020, ast_ );
if( s79.size() ) {
wstring s674, s1428;
vector<pair<wstring, s1::s9<s6::s145>>> s97;
s1300( s79, s1428, s674, s97, ast_ );
if( s97.size() ) {
for( size_t n = 0; n < s97.size(); ++n ) {
s1036 s1071 = new s270( s97[n].first, s628()->Nqj() );
s502* s1167 = (s502*)s278::s525( *s1071, s307, s613, s613->s305() );
basic_stringstream<wchar_t> s1196;
s97[n].second->s159( &s1196 );
s1036 s231 = new s270( s1196.str(), s628()->Nqj() );
s502* s1176 = (s502*)s278::s525( *s231, s307, s613, s613->s305() );
if( !s1344 ) {
s1344 = s1167->s367();
s335 = s1176->s367();}
if( s1344 != s1167->s367() || s335 != s1176->s367() )
throw s1061.s1099( L"incompatible types in the index initialization list" );
s364.insert( make_pair( s1167, s1176 ) );}}
else if( s674.size() ) {
s869::Cont vt, s1129, s1221;
size_t pos = 0;
s307->TR().s1165( s79, pos, vt );
size_t idx = 2;
s510::s1109( vt, idx, s1129 );
s869 s1128( s1129[0] );
s1344 = s307->TR().s1112( s1128 );
s510::s1109( vt, idx, s1221 );
s869 s1218( s1221[0] );
s335 = s307->TR().s1112( s1218 );}
else if( false && s79[0] == L'{' ) {
s519 = s79;}
else if( false && s79[0] == L'(' ) {
wstring sv = s4::s54( s79.substr( 1, s79.size() - 2 ), L" " );
wsmatch s1185;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1185, rg ) ) {
wstring s1209 = s1185[1].str();
wstring s1210 = s1185[2].str();
sv = L"Index(" + s1209 + L" " + s1210 + L")";
s519 = sv;}}
else
assert( 0 );// s519 = s79;
}
if( s771.s13() )
s513 = 0;
else {
if( s1344 ) {
s325 = s307->TR().s1155( s869::Cont( { s1051->s367(), s1344, s335 } ) );
s513 = s307->TR().s1155( s869::Cont( { s771->s367(), s325 } ) );}
else {
s325 = s513 = 0;}}}
s333::s333( const s333& right, const s270* ast_ )
: s1540( right.s307, NULL, ast_ ){
s364 = right.s364;
s513 = right.s513;}
void s333::s1300( const wstring& s79, wstring& s1428, wstring& s674,
vector<pair<wstring, s146>> s97, const s270* ast_ ){
assert( !s79.empty() );
if( s79[0] == L'{' ) {
s1::s9<s6::s147> ob = new s6::s147( NULL );
size_t pos = 0;
s1034 s1161( L"" );
s1161.s175( s79, pos, ob, true );
ob->s164( s97 );}
else
s1301( s307, s79, s1428, s674 );}
s502* s333::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
wstring si;
wstring s362 = s369();
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s54( s, L"{}" );
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s17( L"wrong index constructor syntax" );}
else
return 0;
return new s333( s307, s613, si, &s737 );}
s1172 s333::s1339( const std::wstring& s1428, s869::Cont& s613 ){
s1172 s718;
s869::Cont s1434;
size_t pos = 0;
s307->TR().s1165( s1428, pos, s1434 );
s869 vt( s1434 );
s718 = s307->TR().s1112( vt, false );
if( s718 )
return s718;
s869::Cont s1643, s1690;
size_t idx = 2;
s510::s1109( s1434, idx, s1643 );
s869 s1129( s1643[0] );
s1172 s1598 = s307->TR().s1112( s1129 );
s510::s1109( s1434, idx, s1690 );
s869 s1221( s1690[0] );
s1172 s1601 = s307->TR().s1112( s1221 );
s1172 s1596 = s307->TR().s1155( 
s869::Cont( { s1051->s367(), s1598, s1601 } ) );
s718 = s307->TR().s1155( s869::Cont( { s771->s367(), s1596 } ) );
return s718;}
void s333::s520( s502* s962 ){
TDException s1061( s7::s1011, s1020, s628(), L"wrong Index definition" );
const wstring& s79 = s519;
if( s79.find( L"Index<" ) == 0 ) {
assert( 0 );
s869::Cont vt, s1129, s1221;
size_t pos = 0;
s307->TR().s1165( s79, pos, vt );
size_t idx = 2;
s510::s1109( vt, idx, s1129 );
s869 s1128( s1129[0] );
s1344 = s307->TR().s1112( s1128 );
s510::s1109( vt, idx, s1221 );
s869 s1218( s1221[0] );
s335 = s307->TR().s1112( s1218 );}
else if( s79[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s145>> s157;
s1::s9<s6::s147> ob = new s6::s147( NULL );
size_t pos = 0;
s1034 s1161( L"" );
s1161.s175( s79, pos, ob, true );
vector<pair<wstring, s146>> s148;
ob->s164( s148 );
for( size_t n = 0; n < s148.size(); ++n ) {
s1036 s1071 = new s270( s148[n].first, s628()->Nqj() );
s502* s1167 = (s502*)s278::s525( *s1071, s307, s962, s962->s305() );
basic_stringstream<wchar_t> s1196;
s148[n].second->s159( &s1196 );
s1036 s231 = new s270( s1196.str(), s628()->Nqj() );
s502* s1176 = (s502*)s278::s525( *s231, s307, s962, s962->s305() );
if( !s1344 ) {
s1344 = s1167->s367();
s335 = s1176->s367();}
if( s1344 != s1167->s367() || s335 != s1176->s367() )
throw s1061.s1099( L"incompatible types in the index initialization list" );
s364.insert( make_pair( s1167, s1176 ) );}}
s1414();}
void s333::s365(){
s1540<s1559, s505, s505, s333>::s365();
s363 = s1540<s1559, s505, s505, s333>::s357();
s363.insert( make_pair( L"insert", new s352( L"insert", &s333::s344, s1287,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"find", new s352( L"find", &s333::s830, 0,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"get", new s352( L"get", &s333::s338, 0,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"get-val", new s352( L"get-val", &s333::s1638, 0,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"set", new s352( L"set", &s333::s403, s1276,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"erase", new s352( L"erase", &s333::s345, s1287,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s333::s340, s1285,
{ s1240() }, 0, 0 ) ) );
s363.equal_range( L"find" ).first->second->s1413( true );
s363.equal_range( L"get" ).first->second->s1413( true );
s363.equal_range( L"get-val" ).first->second->s1413( true );
s307->TR().s1302( s513, s7::s1582, s1687::s1681 );
s307->TR().s1302( s513, s7::s1583, s1687::s1682 );}
s502* s333::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
s1::s9<s333> s718 = new s333( s307, s613, L"", ast_ );
s718->s1344 = s1344;
s718->s335 = s335;
return s718;}
s502* s333::s371( s502* s613, const std::vector<s1172>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s869::Cont s1091;
s510::s1109( vt, idx, s1091 );
s869 s1090( s1091[0] );
s1172 s1324 = s307->TR().s1112( s1090 );
const s869& s1217 = s307->TR().s1114( s1324 );
s869::Cont s1129, s1221;
idx = 2;
s510::s1109( s1217.s877(), idx, s1129 );
s869 s1128( s1129[0] );
s1172 s1345 = s307->TR().s1112( s1128 );
s510::s1109( s1217.s877(), idx, s1221 );
s869 s1218( s1221[0] );
s1172 s1431 = s307->TR().s1112( s1218 );
s333* s718 = new s333( s307, s1345, s1431, s613, NULL );
return s718;}
s1172 s333::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"get" ) {
s718 = s325;}
else if( s1728 == L"get-val" ) {
s718 = s325;}
else
s718 = s1540::s1332( s1728, l );
return s718;}
inline bool
s333::s522( const s502* s523 ) const{
return 0; /* ( ( (s324*)s523 )->s325 == s325 );*/
}
s278* s333::s350() const{
return new s333( *this );}
void s333::s372( s278* p ) const{
p = new s333( *this );}
size_t s333::s331() const{
return (size_t)this;}
bool s333::operator==( const s502* p ) const{
return ( this == p );}
bool s333::operator<( const s502* p ) const{
return false;}
Iterator* s333::s1329() {
auto it = begin( s364 );
return new s1027( this, s364.begin(), ++it ); }
Iterator* s333::s1333() {
return new s1027( this, s364.end(), s364.end() ); }
#undef s734
#define s734 ((s333*)(s503*)*s281)
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
inline void s333::s344( s502** s281, size_t s518 ){
s502* s156 = (s502*)PARN( 2 );
s502* s364 = (s502*)PARN( 3 );
s333* dr = (s333*)DR;
if( dr->s1344 != s156->s367() || dr->s335 != s364->s367() )
throw new s17( L"non-compatible types cannot be inserted to an Index" );
dr->s364.insert( make_pair( s156, s364 ) );}
inline void s333::s830( s502** s281, size_t s518 ){
s333* p = (s333*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() )
*s281 = NULL;
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>(), it->second.s16<s503*>() } ) );}}
inline void s333::s338( s502** s281, size_t s518 ){
s333* p = (s333*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() )
*s281 = NULL;
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>(), it->second.s16<s503*>() } ) );}}
inline void s333::s1638( s502** s281, size_t s518 ){
s333* p = (s333*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() ) {
*s281 = new s1050( p->s307, vector<s278*>(
{ (s502*)PARN( 2 ), (s502*)PARN( 3 ) } ) );}
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>()->s350(), it->second.s16<s503*>()->s350() } ) );}}
inline void s333::s403( s502** s281, size_t s518 ){
s502* s156 = (s502*)PARN( 2 );
s502* s364 = (s502*)PARN( 3 );
s333* dr = (s333*)DR;
if( dr->s1344 != s156->s367() || dr->s335 != s364->s367() )
throw new s17( L"non-compatible types cannot be inserted to an Index" );
s1558::iterator it = dr->s364.find( (s502*)PARN( 2 ) );
if( it == dr->s364.end() ) {
s502* s1390 = (s502*)s364->s350();
dr->s364.insert( make_pair( (s502*)s156->s350(), s1390 ) );
*s281 = s385;}
else {
it->second = (s502*)s364->s350();
*s281 = s386;}}
inline void s333::s345( s502** s281, size_t s518 ){
s333* p = (s333*)DR;
p->s364.erase( (s502*)PARN( 2 ) );}
inline void s333::s340( s502** s281, size_t s518 ){}
inline void s333::s343( s502** s281, size_t s518 ){}
Iterator* s333::s322( s401* rv ){
s1269 pr = rv->s1338( this );
return new s1027( this,
pr.first.s16<s1263*>()->s1270(), pr.second.s16<s1263*>()->s1270() );}
wstring s333::to_wstring() const{
wstring s718 = L"{ ";
for( auto it = begin( s364 ); it != end( s364 ); ++it )
s718 += ( it == begin( s364 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s718 += L" }";
return s718;}
void s333::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Index : " << endl;
/*for( size_t n = 0; n < s364.size(); ++n )
s364[n]->s311( pd, s202 + s435 );*/
}
s1553::s1553( s269* s307, s1172 s1345, s1172 s1431, const s270* ast_ )
: s1540( s307, NULL, ast_ ){
assert( s1345 && s1431 );
s1344 = s1345;
s335 = s1431;
s869 s1325( s869::Cont( { s1051->s367(), 2, s1344, 0, s335, 0 } ) );
s513 = s307->TR().s1112( s1325 );}
s1553::s1553( s269* s307, s502* s613, const wstring& s79, const s270* ast_ )
: s1540( s307, s613, ast_ ){
TDException s1061( s7::CLHashIndexVal_ctor1, s1020, ast_ );
if( s79.size() ) {
wstring s674, s1428;
vector<pair<wstring, s1::s9<s6::s145>>> s97;
s1300( s79, s1428, s674, s97, ast_ );
if( s97.size() ) {
for( size_t n = 0; n < s97.size(); ++n ) {
s1036 s1071 = new s270( s97[n].first, s628()->Nqj() );
s502* s1167 = (s502*)s278::s525( *s1071, s307, s613, s613->s305() );
basic_stringstream<wchar_t> s1196;
s97[n].second->s159( &s1196 );
s1036 s231 = new s270( s1196.str(), s628()->Nqj() );
s502* s1176 = (s502*)s278::s525( *s231, s307, s613, s613->s305() );
if( !s1344 ) {
s1344 = s1167->s367();
s335 = s1176->s367();}
if( s1344 != s1167->s367() || s335 != s1176->s367() )
throw s1061.s1099( L"incompatible types in the index initialization list" );
s364.insert( make_pair( s1167, s1176 ) );}}
else if( s674.size() ) {
s869::Cont vt, s1129, s1221;
size_t pos = 0;
s307->TR().s1165( s79, pos, vt );
size_t idx = 2;
s510::s1109( vt, idx, s1129 );
s869 s1128( s1129[0] );
s1344 = s307->TR().s1112( s1128 );
s510::s1109( vt, idx, s1221 );
s869 s1218( s1221[0] );
s335 = s307->TR().s1112( s1218 );}
else if( false && s79[0] == L'{' ) {
s519 = s79;}
else if( false && s79[0] == L'(' ) {
wstring sv = s4::s54( s79.substr( 1, s79.size() - 2 ), L" " );
wsmatch s1185;
wregex rg( LR"regex(^\s*([_[:alpha:]][\w_ \(\)]+\))\s*([_[:alpha:]][\w_ \(\)]+\))\s*$)regex" );
if( sv.size() && regex_match( sv, s1185, rg ) ) {
wstring s1209 = s1185[1].str();
wstring s1210 = s1185[2].str();
sv = L"Index(" + s1209 + L" " + s1210 + L")";
s519 = sv;}}
else
assert( 0 );}
if( s1555.s13() )
s513 = 0;
else {
if( s1344 ) {
s325 = s307->TR().s1155( s869::Cont( { s1051->s367(), s1344, s335 } ) );
s513 = s307->TR().s1155( s869::Cont( { s1555->s367(), s325 } ) );}
else {
s325 = s513 = 0;}}}
s1553::s1553( const s1553& right, const s270* ast_ )
: s1540( right.s307, NULL, ast_ ){
s364 = right.s364;
s513 = right.s513;}
void s1553::s1300( const wstring& s79, wstring& s1428, wstring& s674,
vector<pair<wstring, s146>> s97, const s270* ast_ ){
assert( !s79.empty() );
if( s79[0] == L'{' ) {
s1::s9<s6::s147> ob = new s6::s147( NULL );
size_t pos = 0;
s1034 s1161( L"" );
s1161.s175( s79, pos, ob, true );
ob->s164( s97 );}
else
s1301( s307, s79, s1428, s674 );}
s502* s1553::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s = s737.s298();
wstring si;
wstring s362 = s369();
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
si = s; // s4::s54( s, L"{}" );
else if( s.find( s362 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s17( L"wrong index constructor syntax" );}
else
return 0;
return new s1553( s307, s613, si, &s737 );}
void s1553::s520( s502* s962 ){
TDException s1061( s7::s1011, s1020, s628(), L"wrong Index definition" );
const wstring& s79 = s519;
if( s79.find( L"HashIndex<" ) == 0 ) {
assert( 0 );
s869::Cont vt, s1129, s1221;
size_t pos = 0;
s307->TR().s1165( s79, pos, vt );
size_t idx = 2;
s510::s1109( vt, idx, s1129 );
s869 s1128( s1129[0] );
s1344 = s307->TR().s1112( s1128 );
s510::s1109( vt, idx, s1221 );
s869 s1218( s1221[0] );
s335 = s307->TR().s1112( s1218 );}
else if( s79[0] == L'{' ) {
assert( 0 );
vector<s1::s9<s6::s145>> s157;
s1::s9<s6::s147> ob = new s6::s147( NULL );
size_t pos = 0;
s1034 s1161( L"" );
s1161.s175( s79, pos, ob, true );
vector<pair<wstring, s146>> s148;
ob->s164( s148 );
for( size_t n = 0; n < s148.size(); ++n ) {
s1036 s1071 = new s270( s148[n].first, s628()->Nqj() );
s502* s1167 = (s502*)s278::s525( *s1071, s307, s962, s962->s305() );
basic_stringstream<wchar_t> s1196;
s148[n].second->s159( &s1196 );
s1036 s231 = new s270( s1196.str(), s628()->Nqj() );
s502* s1176 = (s502*)s278::s525( *s231, s307, s962, s962->s305() );
if( !s1344 ) {
s1344 = s1167->s367();
s335 = s1176->s367();}
if( s1344 != s1167->s367() || s335 != s1176->s367() )
throw s1061.s1099( L"incompatible types in the index initialization list" );
s364.insert( make_pair( s1167, s1176 ) );}}
s519 = s962->s900();}
void s1553::s365(){
s1540<s1552, s505, s505, s1553>::s365();
s363 = s1540<s1552, s505, s505, s1553>::s357();
s363.insert( make_pair( L"insert", new s352( L"insert", &s1553::s344, s1287,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"find", new s352( L"find", &s1553::s830, 0,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"get", new s352( L"get", &s1553::s338, 0,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"get-val", new s352( L"get-val", &s1553::s1638, 0,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"set", new s352( L"set", &s1553::s403, s1276,
{ s1240( { s7::s1568, s7::s1569 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"erase", new s352( L"erase", &s1553::s345, s1287,
{ s1240( { s7::s1568 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s1553::s340, s1285,
{ s1240() }, 0, 0 ) ) );
s363.equal_range( L"find" ).first->second->s1413( true );
s363.equal_range( L"get" ).first->second->s1413( true );
s363.equal_range( L"get-val" ).first->second->s1413( true );}
s502* s1553::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
s1::s9<s1553> s718 = new s1553( s307, s613, L"", ast_ );
s718->s1344 = s1344;
s718->s335 = s335;
return s718;}
s502* s1553::s371( s502* s613, const std::vector<s1172>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s869::Cont s1091;
s510::s1109( vt, idx, s1091 );
s869 s1090( s1091[0] );
s1172 s1324 = s307->TR().s1112( s1090 );
const s869& s1217 = s307->TR().s1114( s1324 );
s869::Cont s1129, s1221;
idx = 2;
s510::s1109( s1217.s877(), idx, s1129 );
s869 s1128( s1129[0] );
s1172 s1345 = s307->TR().s1112( s1128 );
s510::s1109( s1217.s877(), idx, s1221 );
s869 s1218( s1221[0] );
s1172 s1431 = s307->TR().s1112( s1218 );
s1553* s718 = new s1553( s307, s1345, s1431, NULL );
return s718;}
s1172 s1553::s1332( const wstring& s1728, const vector<s504>& l ) const{
s1172 s718 = 0;
if( s1728 == L"get" ) {
s718 = s325;}
else if( s1728 == L"get-s" ) {
s718 = s325;}
return s718;}
inline bool
s1553::s522( const s502* s523 ) const{
return ( s523->s367() == s367() );}
s278* s1553::s350() const{
return new s1553( *this );}
void s1553::s372( s278* p ) const{
p = new s1553( *this );}
size_t s1553::s331() const{
return (size_t)this;}
bool s1553::operator==( const s502* p ) const{
return ( this == p );}
bool s1553::operator<( const s502* p ) const{
return false;}
Iterator* s1553::s1329() {
auto it = begin( s364 );
return new s1554( this, s364.begin(), ++it ); }
Iterator* s1553::s1333() {
return new s1554( this, s364.end(), s364.end() ); }
#undef s734
#define s734 ((s1553*)(s503*)*s281)
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
inline void s1553::s344( s502** s281, size_t s518 ){
s502* s156 = (s502*)PARN( 2 );
s502* s364 = (s502*)PARN( 3 );
s1553* dr = (s1553*)DR;
if( dr->s1344 != s156->s367() || dr->s335 != s364->s367() )
throw new s17( L"non-compatible types cannot be inserted to an Index" );
dr->s364.insert( make_pair( s156, s364 ) );}
inline void s1553::s830( s502** s281, size_t s518 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() )
*s281 = NULL;
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>(), it->second.s16<s503*>() } ) );}}
inline void s1553::s338( s502** s281, size_t s518 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() )
*s281 = NULL;
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>(), it->second.s16<s503*>() } ) );}}
inline void s1553::s1638( s502** s281, size_t s518 ){
s1553* p = (s1553*)DR;
s1558::iterator it = p->s364.find( (s502*)PARN( 2 ) );
if( it == p->s364.end() ) {
*s281 = new s1050( p->s307, vector<s278*>(
{ (s502*)PARN( 2 ), (s502*)PARN( 3 ) } ) );}
else {
*s281 = new s1050( p->s307, vector<s278*>(
{ it->first.s16<s503*>()->s350(), it->second.s16<s503*>()->s350() } ) );}}
inline void s1553::s403( s502** s281, size_t s518 ){
s502* s156 = (s502*)PARN( 2 );
s502* s364 = (s502*)PARN( 3 );
s1553* dr = (s1553*)DR;
if( dr->s1344 != s156->s367() || dr->s335 != s364->s367() )
throw new s17( L"non-compatible types cannot be inserted to an Index" );
s1558::iterator it = dr->s364.find( (s502*)PARN( 2 ) );
if( it == dr->s364.end() ) {
s502* s1390 = (s502*)s364->s350();
dr->s364.insert( make_pair( (s502*)s156->s350(), s1390 ) );
*s281 = s385;}
else {
it->second = (s502*)s364->s350();
*s281 = s386;}}
inline void s1553::s345( s502** s281, size_t s518 ){
s1553* p = (s1553*)DR;
p->s364.erase( (s502*)PARN( 2 ) );}
inline void s1553::s340( s502** s281, size_t s518 ){}
inline void s1553::s343( s502** s281, size_t s518 ){}
Iterator* s1553::s322( s401* rv ){
s1269 pr = rv->s1338( this );
return new s1554( this,
pr.first.s16<s1263*>()->s1270(), pr.second.s16<s1263*>()->s1270() );}
wstring s1553::to_wstring() const{
wstring s718 = L"{ ";
for( auto it = begin( s364 ); it != end( s364 ); ++it )
s718 += ( it == begin( s364 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s718 += L" }";
return s718;}
void s1553::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s364.size(); ++n )
s364[n]->s311( pd, s202 + s435 );*/
}
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
s431::s431( s269* s307, const wstring& s79, const s270* ast_ )
: s351( s307, NULL, ast_ ), s799( s307, s1289, NULL ), s862( s307, s1289, NULL ){
s513 = s867.s13() ? 0 : s867->s367();
s799.s11();
s862.s11();}
s431::s431( const s431& right, const s270* ast_ )
: s351( right.s307, right.ns, ast_ ), s799( right.s307, NULL, L"" ), s862( right.s307, NULL, L"" ){
s799 = right.s799;
s862 = right.s862;
s513 = right.s513;}
s502* s431::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
return new s431( s307, L"" );}
void s431::s520( s502* s962 ){}
void s431::s365(){
s869::Cont s1434;
wstring ts = s765->s369() + L"<" + s843->s369() + L">";
s1172 s1692 = s765->s1339( ts, s1434 );
s363.insert( make_pair( L"read", new s352( L"read", &s431::s425, s1287,
{ s1240( { s1289, s1289 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"reset", new s352( L"reset", &s431::s432, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"files", new s352( L"files", &s431::s433, s1692,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"dirs", new s352( L"dirs", &s431::s1089, s1692,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s431::s340, s1285,
{ s1240() }, 0, 0 ) ) );}
s502* s431::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s431( s307, L"", ast_ );}
inline bool
s431::s522( const s502* s523 ) const{
return ( ((s431*)s523)->s367() == s367() );}
s278* s431::s350() const{
return s504( new s431( *this ) );}
void s431::s372( s278* p ) const{
p = new s431( *this );}
#undef s734
#define s734 ((s431*)(s503*)*s281)
inline void s431::s425( s502** s281, size_t s518 ){
wstring path = ((s375*)PARN( 2 ) )->to_wstring();
const wstring& s548 = ((s375*)PARN( 3 ))->to_wstring();
vector<wstring> s839, s848;
s431* s832 = (s431*)DR;
s832->s799.clear();
s832->s862.clear();
if( !s3::s761( path ) )
path = s832->s307->s753() + path;
s4::s63( path );
s3::s33( path, s548, s839, s848 );
std::sort( begin(s839 ), end(s839));
std::sort( begin(s848 ), end(s848));
for( auto f : s839 )
s832->s799.add( new s375( s832->s307, s4::s789( path + f ) ) );
for( auto f : s848 )
s832->s862.add( new s375( s832->s307, s4::s789( path + f ) ) );}
inline void s431::s432( s502** s281, size_t s518 ){
s431* s832 = (s431*)DR;
s832->s799.clear();
s832->s862.clear();}
inline void s431::s433( s502** s281, size_t s518 ){
*s281 = &( (s431*)DR )->s799;}
inline void s431::s1089( s502** s281, size_t s518 ){
*s281 = &( (s431*)DR )->s862;}
inline void s431::s340( s502** s281, size_t s518 ){
s431* s832 = (s431*)DR;
*( (s361*)*s281 )->s373() = (int)(s832->s799.size() + s832->s862.size());}
wstring s431::to_wstring() const{
wstring s718;
for( size_t n = 0; n < s862.size(); ++n )
s718 += ( n ? L" \"" : L"\"" ) + s862[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s799.size(); ++n )
s718 += ( n ? L" \"":L"\"") + s799[n]->to_wstring() + L"\"";
return s718;}
void s431::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Directory : " << endl;
for( size_t n = 0; n < s862.size(); ++n )
s862[n]->s311( pd, s202 + s435 );
for( size_t n = 0; n < s799.size(); ++n )
s799[n]->s311( pd, s202 + s435 );}
size_t s431::s331() const{
size_t s718 = 0;
for( size_t n = 0; n < s862.size(); ++n )
s718 = s718 * ( (s502*)&(s862[n]) )->s331() << 1;
for( size_t n = 0; n < s799.size(); ++n )
s718 = s718 * ( (s502*)&(s799[n]) )->s331() << 1;
return s718;}
bool s431::operator==( const s502* p ) const{
if( ( (s431*)p )->s799.size() != s799.size() )
return false;
if( ( (s431*)p )->s862.size() != s862.size() )
return false;
for( size_t n = 0; n < s799.size(); ++n )
if( !( ( s278* )&( *s799[n] ) == (s278*)( (s431*)p )->s799[n] ) )
return false;
for( size_t n = 0; n < s862.size(); ++n )
if( !( ( s278* )&( *s862[n] ) == (s278*)( (s431*)p )->s862[n] ) )
return false;
return true;}
bool s431::operator<( const s502* p ) const{
return false;}
s1463::s1463( s269* s307, const wstring& s79, s502* ns_, const s270* ast_ )
: s351( s307, ns_, ast_ ){
s513 = s1464.s13() ? 0 : s1464->s367();
if( s79.size() ) {}}
s1463::s1463( const s1463& right, const s270* ast_ )
: s351( right.s307, right.ns, ast_ ){
s513 = right.s513;}
s502* s1463::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s_ = s737.s298();
wstring s364, s;
wstring tn = s369();
if( s_.find( tn + L"(" ) == 0 ) {
s = s4::s54( s_.substr( tn.size() + 1, s_.size() - ( tn.size() + 1 ) ), 
s50 );
if( s.empty() )
return new s1463( s307, L"", s613 );}
else
s = s4::s54( s_, s50 );
return new s1463( s307, L"", s613 );}
void s1463::s520( s502* s962 ){
s869::Cont s1434;
wstring ts = s765->s369() + L"<" + s843->s369() + L">";
s1172 pt = s765->s1339( ts, s1434 );
s363.equal_range( L"files" ).first->second->s1415( pt
/*s307->TR().s1155( s869::Cont( { s765->s367(), s843->s367() }) )*/ );
s363.equal_range( L"dirs" ).first->second->s1415( pt
/*s307->TR().s1155( s869::Cont( { s765->s367(), s843->s367() }) )*/ );
}
void s1463::s365(){
s363.insert( make_pair( L"read", new s352( L"read", &s1463::s425, s1287,
{ s1240( { s1289, s1289 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"reset", new s352( L"reset", &s1463::s1524, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"files", new s352( L"files", &s1463::s1500, 0 /*s765->s367()*/,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"dirs", new s352( L"dirs", &s1463::s1491, 0 /*s765->s367()*/,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s1463::s340, s1285,
{ s1240() }, 0, 0 ) ) );}
s502* s1463::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s1463( s307, L"", s613, ast_ );}
inline bool
s1463::s522( const s502* s523 ) const{
return ( ((s1463*)s523)->s367() == s367() );}
s278* s1463::s350() const{
return s504( new s1463( *this ) );}
void s1463::s372( s278* p ) const{
p = new s1463( *this );}
#undef s734
#define s734 ((s1463*)(s503*)*s281)
inline void s1463::s425( s502** s281, size_t s518 ){}
inline void s1463::s1524( s502** s281, size_t s518 ){}
inline void s1463::s1500( s502** s281, size_t s518 ){}
inline void s1463::s1491( s502** s281, size_t s518 ){}
inline void s1463::s340( s502** s281, size_t s518 ){}
wstring s1463::to_wstring() const{
wstring s718 = L"File";
return s718;}
void s1463::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"File : " << endl;}
size_t s1463::s331() const{
size_t s718 = 0;
return s718;}
bool s1463::operator==( const s502* p ) const{
return false;}
bool s1463::operator<( const s502* p ) const{
return false;}
vector<wstring> s1473( { L":append" } );
s1472::s1472( s269* s307, s502* s617, s616* s618,
const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s1483, s737 ){
if( l.size() < 2 || l.size() > 3 )
throw new s17( L"malformed syntax of 'to-file' procedure call." );
s281.assign( l.begin(), l.end() );
s513 = s1287;
s616::s1393( ( vector<s278*>& )l, s1473 );}
void
s1472::s520( const wstring& s347, bool proc ){
obj = s281[0].s16<s502*>();
s215 = s278::s1122( s307, s281[1], s613, this, s305() );
if( s281.size() > 2 )
mode = s278::s1122( s307, s281[2], s613, this, s305() );}
s505 s1472::s517( s502** s741, size_t s518 ){
s490 pc = s281[0]->s514();
s1::s9<s337> s613;
if( pc == s494 ) {
s613 = s281[0]->s517( 0, 0 ).s16<s337*>();}
else
s613 = ((s337*)s281[0].s16<s387*>()->s393());
return 0;}
s278* s1472::s350()const{
return new s1472( *this );}
s1172 s1687::s1680 = 0;
s1172 s1687::s1684 = 0;
s1172 s1687::s1679 = 0;
void Stream::s1636( std::wstring& s157, size_t s1647 ){
throw new s2::s17( L"stream method is not implemented: get_text" );}
void Stream::s1655( const std::wstring& src ){
throw new s2::s17( L"stream method is not implemented: put_text" );}
void Stream::s1637( std::wstring& s157, const std::wstring& s74 ){
throw new s2::s17( L"stream method is not implemented: get_text_line" );}
void Stream::s1656( const std::wstring& src ){
throw new s2::s17( L"stream method is not implemented: put_text_line" );}
void Stream::s1635( s1489& s157, size_t s1647 ){
throw new s2::s17( L"stream method is not implemented: get_bytes" );}
void Stream::s1654( const s1489& src ){
throw new s2::s17( L"stream method is not implemented: put_bytes" );}
void Stream::s1634( s1489& s157, const s1489& s74 ){
throw new s2::s17( L"stream method is not implemented: get_byte_line" );}
void Stream::s1653( const s1489& src ){
throw new s2::s17( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s17( L"stream method is not implemented: rewind" );}
s528::s528( s269* s307, s502* ns_, const s270* ast_ )
: s1578( s307, ns_, ast_ ){
s513 = s871.s13() ? 0 : s871->s367();
s1649 = (basic_istringstream<wchar_t>*) &ss;
s1650 = (basic_ostringstream<wchar_t>*) &ss;}
s528::s528( const s528& r, const s270* ast_ )
: s1578( r.s307, r.ns, ast_ ), ss( r.ss.str() ){
s513 = s871->s367();}
s502* s528::s371( s502* s613, const std::vector<s278*>&, const s270* ast_ ) const{
return new s528( s307, s613, ast_ );}
void s528::s365(){
s1578<s1672,s1675>::s365();
s363 = s1578<s1672, s1675>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s528::s1385, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"str", new s352( L"str", &s528::s529, s843->s367(),
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", &s528::s342, s871->s367(),
{ s1240() }, 0, 0 ) ) );
s307->TR().s1302( s513, s7::s1581, s1687::s1680 );
s307->TR().s1302( s513, s7::s1586, s1687::s1684 );
s307->TR().s1302( s513, s7::s1580, s1687::s1679 );}
void s528::s520( s502* s962 ){
s1414();}
void s528::release(){
ss.clear();}
s502* s528::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s_ = s737.s298();
if( s_.find( L"StringStream(" ) == 0 )
return new s528( s307, s613, &s737 );
return NULL;}
s278* s528::s350() const{
return new s528( *this );}
void s528::s372( s278* p ) const{
if( p->s367() == s871->s367() )
((s528*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s17( L"No conversion to type " + std::to_wstring( p->s367() ) );}
void s528::s1636( std::wstring& s157, size_t s1647 ){
s157 = ss.str().substr( 0, s1647 );}
void s528::s1655( const std::wstring& src ){
ss << src;}
void s528::s1637( std::wstring& s157, const std::wstring& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-char line separators are not supported: '" + s74 + L"'" );
s157.clear();
std::getline( ss, s157, s74[0] );}
void s528::s1656( const std::wstring& src ){
ss << src << endl;}
void s528::s1635( s1489& s157, size_t s1647 ){
s157 = (tdbyte_t*)U8( ss.str().substr( 0, s1647 )).data();}
void s528::s1654( const s1489& src ){
ss << U16( (char*)src.c_str() );}
void s528::s1634( s1489& s157, const s1489& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-byte line separators are not supported: '" + 
U16((char*)s74.c_str()) + L"'" );
s157.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s74.c_str())[0]);}
void s528::s1653( const s1489& src ){
ss << U16( (char*)src.c_str() ) << endl;}
wstring s528::to_wstring() const {
return ss.str(); }
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
#undef s734
#define s734 ((s528*)(s503*)*s281)
inline void s528::s1385( s502** s281, size_t s518 ){
s528* ps = (s528*)DR;
s528* s718 = new s528( ps->s307, ps->ns, ps->s628() );
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s528::s529( s502** s281, size_t s518 ){
*( (s375*)s281[0] )->s373() = ( (s528*)DR)->ss.str();}
inline void s528::s342( s502** s281, size_t s518 ){
((s528*)DR)->ss.rdbuf()->str(L"");}
void s528::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << ss.str() << endl;}
size_t s528::s331() const{
return hash<wstring>{}(ss.str());}
bool s528::operator==( const s502* p ) const{
return ( (s528*)p )->ss.str() == ss.str();}
bool s528::operator<( const s502* p ) const{
return ss.str() < ( (s528*)p )->ss.str();}
s1452::s1452( s269* s307, s502* ns_, const s270* ast_ )
: s1578( s307, ns_, ast_ ){
s513 = s1453.s13() ? 0 : s1453->s367();
s1649 = (basic_istringstream<tdbyte_t>*) &bs;
s1650 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1452::s1452( const s1452& r, const s270* ast_ )
: s1578( r.s307, r.ns, ast_ ), bs( r.bs.str() ){
s513 = s1453->s367();}
s502* s1452::s371( s502* s613, const std::vector<s278*>&, const s270* ast_ ) const{
return new s1452( s307, ast_ );}
void s1452::s365(){
s1578<s1670, s1673>::s365();
s363 = s1578<s1670, s1673>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s1452::s1385, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"array", new s352( L"str", &s1452::s1482, s843->s367(),
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"clear", new s352( L"clear", &s1452::s342, s1453->s367(),
{ s1240() }, 0, 0 ) ) );
s307->TR().s1302( s513, s7::s1581, s1687::s1680 );
s307->TR().s1302( s513, s7::s1586, s1687::s1684 );
s307->TR().s1302( s513, s7::s1580, s1687::s1679 );}
void s1452::s520( s502* s962 ){
s1414();}
void s1452::release(){
bs.clear();}
s502* s1452::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s_ = s737.s298();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1452( s307 );
return NULL;}
s278* s1452::s350() const{
return new s1452( *this );}
void s1452::s372( s278* p ) const{
if( p->s367() == s1453->s367() )
((s1452*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s17( L"No conversion to type " + std::to_wstring( p->s367() ) );}
void s1452::s1636( std::wstring& s157, size_t s1647 ){
s157 = U16( (char*)bs.str().c_str() ).substr( 0, s1647 );}
void s1452::s1655( const std::wstring& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1452::s1637( std::wstring& s157, const std::wstring& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-char line separators are not supported: '" + s74 + L"'" );
s157.clear();
s1489 tmp;
std::getline( bs, tmp, (unsigned char)U8(s74.data())[0] );}
void s1452::s1656( const std::wstring& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1452::s1635( s1489& s157, size_t s1647 ){
s157 = bs.str().substr( 0, s1647 );}
void s1452::s1654( const s1489& src ){
bs << src.data();}
void s1452::s1634( s1489& s157, const s1489& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-byte line separators are not supported: '" + U16((char*)s74.c_str()) + L"'" );
s157.clear();
std::getline( bs, s157, s74[0] );}
void s1452::s1653( const s1489& src ){
bs << src << endl;}
wstring s1452::to_wstring() const {
s1489 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
#undef s734
#define s734 ((s1452*)(s503*)*s281)
inline void s1452::s1385( s502** s281, size_t s518 ){
s1452* ps = (s1452*)DR;
s1452* s718 = new s1452( ps->s307, ps->s628() );
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s1452::s1482( s502** s281, size_t s518 ){
s1489 s = ( (s1452*)DR)->bs.str();
( (s1449*)s281[0] )->s329().assign( begin( s ), end( s ) );}
inline void s1452::s342( s502** s281, size_t s518 ){
((s1452*)DR)->bs.rdbuf()->str(0);}
void s1452::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : [...]" << endl;}
size_t s1452::s331() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1452::operator==( const s502* p ) const{
return ( (s1452*)p )->bs.str() == bs.str();}
bool s1452::operator<( const s502* p ) const{
return bs.str() < ( (s1452*)p )->bs.str();}
s1461::s1461( s269* s307, s502* ns_, const s270* ast_ )
: s1578( s307, ns_, ast_ ){
s513 = s1462.s13() ? 0 : s1462->s367();
s1649 = NULL;
s1650 = NULL;}
s1461::s1461( s269* s307, const std::vector<s278*>& l, s502* s613,
const s270* ast_ )
: s1578( s307, s613, ast_ ){
s513 = s1462->s367();
s1649 = NULL;
s1650 = NULL;
if( l.size() ) {
if( l[0]->s367() == s1289 )
s1509 = l[0]->to_wstring();
else
s215 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1461::s1461( const s1461& r, const s270* ast_ )
: s1578( r.s307, r.ns, ast_ ), s215( r.s215 ), mode( r.mode ){
s513 = s1462->s367();
s1649 = NULL;
s1650 = NULL;}
s502* s1461::s371( s502* s613, const std::vector<s278*>&, const s270* ast_ ) const{
return new s1461( s307, ast_ );}
void s1461::s365(){
s1578<s1671, s1674>::s365();
s363 = s1578<s1671, s1674>::s357();
s363.insert( make_pair( L"new", new s352( L"new", &s1461::s1385, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"open", new s352( L"open", &s1461::s1500, s1287,
{ s1240(), s1240( { s1289 } ), s1240( { s1289, s1289 } ) }, 0, 2 ) ) );
s363.insert( make_pair( L"close", new s352( L"close", &s1461::s1491, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"read", new s352( L"read", &s1461::s425, s1287,
{ s1240( { s1451->s367(), s1285 } ) }, 2, 2 ) ) );
s363.insert( make_pair( L"read-lines", new s352( L"read-lines", &s1461::s1659, 0,	
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"write", new s352( L"write", &s1461::s1524, s1287,
{ s1240( { s1451->s367(), s1285 } ) }, 2, 2 ) ) );
s307->TR().s1302( s513, s7::s1581, s1687::s1680 );
s307->TR().s1302( s513, s7::s1586, s1687::s1684 );
s307->TR().s1302( s513, s7::s1580, s1687::s1679 );}
void s1461::s520( s502* s962 ){
s869::Cont s1434;
wstring ts = s765->s369() + L"<" + s1451->s369() + L">";
s1172 pt = s765->s1339( ts, s1434 );
s363.equal_range( L"read-lines" ).first->second->s1415( pt );
s1414();}
void s1461::release(){
fs.close();}
s502*
s1461::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
wstring s_ = s737.s298();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s278*> s741;
s278::s1501( s737, s307, s613, s347, s741 );
return new s1461( s307, s741, s613, &s737 );}
return NULL;}
s278*
s1461::s350() const{
return new s1461( *this );}
void s1461::s372( s278* p ) const{
if( p->s367() == s1462->s367() ) {
((s1461*)p)->s215 = s215;
((s1461*)p)->mode = mode;}
else
throw new s17( L"No conversion from " + s369() + L" to " + 
p->s369() );}
void s1461::s1636( std::wstring& s157, size_t s1647 ){
size_t s1229 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1229;
fs.seekg( 0, ios_base::beg );
size_t s1678 = s1647 ? (std::min)( s1647, fsz ) : fsz;
string buf( s1678+1, '\0' );
fs.read( &buf[0], s1678 );
if( !fs.good() ) {
fs.close();
throw new s17( L"could not read file '" + s1509 + L"'" );}
s157 = U16( buf.data() );}
void s1461::s1655( const std::wstring& src ){
fs << U8(src).data();}
void s1461::s1637( std::wstring& s157, const std::wstring& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-char line separators are not supported: '" + s74 + L"'" );
if( !fs )
throw new s17( L"file stream is not valid" );
s157.clear();
if( fs.eof() )
return;
string buf;
char s1646 = U8( s74.data() )[0];
std::getline( fs, buf, s1646 );
s157 = U16( buf.data() );}
void s1461::s1656( const std::wstring& src ){
fs << U8(src).data() << endl;}
void s1461::s1635( s1489& s157, size_t s1647 ){
size_t s1229 = fs.tellg();
size_t fsz = (size_t)fs.seekg( ios::end ).tellg() - s1229;
fs.seekg( s1229 );
size_t s1678 = s1647 ? (std::min)( s1647, fsz ) : fsz;
s157.resize( s1678 );
fs.read( (char*)&s157[0], s1678 );}
void s1461::s1654( const s1489& src ){
fs << *(string*)&src;}
void s1461::s1634( s1489& s157, const s1489& s74 ){
if( s74.size() > 1 )
throw new s17( L"multi-byte line separators are not supported: '" + U16( (char*)s74.c_str() ) + L"'" );
string buf;
s157.clear();
std::getline( fs, buf, (char)s74[0] );
std::swap( buf, *(string*)(&s157) );}
void s1461::s1653( const s1489& src ){
fs << *(string*)&src << endl;}
wstring s1461::to_wstring() const {
return L"FileStream"; }
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
#undef s734
#define s734 ((s1461*)(s503*)*s281)
inline void s1461::s1385( s502** s281, size_t s518 ){
s1461* ps = (s1461*)DR;
s1461* s718 = new s1461( *ps );
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s1461::s1500( s502** s281, size_t s518 ){
s1461*pf = (s1461*)DR;
if( s518 > 2 ) {
if( s281[2]->s367() == s1289 ) {
pf->s1509 = s281[2]->to_wstring();
pf->s215 = NULL;}
else {
pf->s215 = s281[2];
pf->s1509 = L"";}
if( s518 > 3 ) {
pf->mode = s281[3];}}
pf->_open();}
inline void s1461::s1491( s502** s281, size_t s518 ){
((s1461*)DR)->_close();
((s1461*)DR)->s1649 = NULL;
((s1461*)DR)->s1650 = NULL;}
inline void s1461::s1524( s502** s281, size_t s518 ){
assert( s518 == 4 );
assert( s281[2]->s367() == s1451->s367() );
s1461*pf = (s1461*)DR;
if( !pf->fs.good() )
throw new s17( L"cannot write to file '" + pf->s1509 + L"'." );
s1449* s1502 = (s1449*)s281[2];
s502* s1504 = s281[3];
int s1518 = (int)*s1504;
pf->fs.write( (const char*)s1502->s329().data(), s1518 );
if( !pf->fs.good() )
throw new s17( L"failed to write to file '" + pf->s1509 + L"'." );}
inline void s1461::s425( s502** s281, size_t s518 ){
assert(0);
((s1461*)DR)->_close();}
inline void s1461::s1659( s502** s281, size_t s518 ){
if( !((s1461*)DR)->fs )
throw new s17( L"file stream is not valid" );
fstream& fs = *(fstream*)((s1461*)DR)->addr();
s324& v = *(s324*)s734;
s1::s9<s1449> bar = new s1449( ( (s1461*)DR )->s307 );
while( !( (s1461*)DR )->fs.eof()) {
if( !std::getline( fs, *(string*)&bar->s329()/*, widen('\n')*/ ) )
throw new s17( L"cannot read from file '" + ( (s1461*)DR )->s1509 + L"'" );
v.s329().push_back( bar.s16<s503*>() );
v.s329().back()->s1414();
bar = new s1449( ( (s1461*)DR )->s307 );}}
void s1461::_open(){
if( fs.is_open() )
fs.close();
wstring path, s1513 = L"r";
if( !s1509.empty() )
path = s1509;
else {
if( s215->s514() != s493 )
path = s215->to_wstring();
else 
path = s215.s16<s387*>()->s393()->to_wstring();
s1509 = path;}
if( mode.s14() ) {
if( mode->s514() != s493 )
s1513 = mode->to_wstring();
else 
s1513 = mode.s16<s387*>()->s393()->to_wstring();}
if( !s3::s761( path ) )
path = s307->s753() + path;
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
throw new s17( L"unrecognized file open mode: '" + s1513 + L"'." );
if( s1513 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s17( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s17( L"cannot open file '" + path + L"'." );}
void s1461::_close(){
mode = s215 = NULL;
s1509.clear();
fs.close();}
void s1461::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << s369() << L" : " << s1509 << endl;}
size_t s1461::s331() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1461::operator==( const s502* p ) const{
return this == p;}
bool s1461::operator<( const s502* p ) const{
return this < p;}
s1574::s1574( s269* s307, s502* ns_, const s270* ast_ )
: s1578( s307, ns_, ast_ ){
s1649 = &std::wcin;}
s502* s1574::s371( s502* s613, const std::vector<s278*>&, const s270* ast_ ) const{
throw new s17( L" StdIn object cannot be instantiated" );}
void s1574::s365(){
s307->TR().s1302( s513, s7::s1581, s1687::s1680 );}
void s1574::s520( s502* s962 ){
s1414();}
s502* s1574::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
return NULL;}
s278* s1574::s350() const{
throw new s17( L"StdIn object cannot be copied" );}
void s1574::s372( s278* p ) const{
throw new s17( L"StdIn object cannot be copied" );}
void s1574::s1636( std::wstring& s157, size_t s1647 ){
s157.resize( s1647 );
wcin.read( &s157[0], s1647 );
size_t s718 = wcin.gcount();
s157.resize( s718 );}
void s1574::s1655( const std::wstring& src ){
throw new s17( L"cannot output to StdIn" );}
void s1574::s1637( std::wstring& s157, const std::wstring& s74 ){
s157.clear();
std::getline( wcin, s157 );}
void s1574::s1656( const std::wstring& src ){
throw new s17( L"cannot output to StdIn" );}
void s1574::s1635( s1489& s157, size_t s1647 ){
wstring buf( s1647, L'\0' );
wcin.read( &buf[0], s1647 );
size_t s718 = wcin.gcount();
buf.resize( s718 );
s157 = (tdbyte_t*)U8( buf ).data();}
void s1574::s1654( const s1489& src ){
throw new s17( L"cannot output to StdIn" );}
void s1574::s1634( s1489& s157, const s1489& s74 ){
wstring buf;
std::getline( wcin, buf );
s157 = (tdbyte_t*)U8( buf ).data();}
void s1574::s1653( const s1489& src ){
throw new s17( L"cannot output to StdIn" );}
wstring s1574::to_wstring() const {
throw new s17( L"22: not implemented" );}
void s1574::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"StdIn object" << endl;}
size_t s1574::s331() const{
throw new s17( L"15: not implemented" );}
bool s1574::operator==( const s502* p ) const{
throw new s17( L"16: not implemented" );}
bool s1574::operator<( const s502* p ) const{
throw new s17( L"17: not implemented" );}
s1576::s1576( s269* s307, s502* ns_, const s270* ast_ )
: s1578( s307, ns_, ast_ ){
s1650 = &std::wcout;}
s502* s1576::s371( s502* s613, const std::vector<s278*>&, const s270* ast_ ) const{
throw new s17( L"StdOut object cannot be instantiated" );}
void s1576::s365(){
s307->TR().s1302( s513, s7::s1586, s1687::s1684 );}
void s1576::s520( s502* s962 ){
s1414();}
s502* s1576::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
return NULL;}
s278* s1576::s350() const{
throw new s17( L"StdOut object cannot be copied" );}
void s1576::s372( s278* p ) const{
throw new s17( L"StdOut object cannot be copied" );}
void s1576::s1636( std::wstring& s157, size_t s1647 ){
throw new s17( L"cannot get input from StdOut" );}
void s1576::s1655( const std::wstring& src ){
wcout << src;}
void s1576::s1637( std::wstring& s157, const std::wstring& s74 ){
throw new s17( L"cannot get input from StdOut" );}
void s1576::s1656( const std::wstring& src ){
wcout << src << endl;}
void s1576::s1635( s1489& s157, size_t s1647 ){
throw new s17( L"cannot get input from StdOut" );}
void s1576::s1654( const s1489& src ){
wcout << U16( (const char*)src.data() );}
void s1576::s1634( s1489& s157, const s1489& s74 ){
throw new s17( L"cannot get input from StdOut" );}
void s1576::s1653( const s1489& src ){
wcout << U16( (const char*)src.data() ) << endl;}
wstring s1576::to_wstring() const {
throw new s17( L"21: not implemented" );}
void s1576::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"StdOut object" << endl;}
size_t s1576::s331() const{
throw new s17( L"18: not implemented" );}
bool s1576::operator==( const s502* p ) const{
throw new s17( L"19: not implemented" );}
bool s1576::operator<( const s502* p ) const{
throw new s17( L"20: not implemented" );}
s630::s630( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s239, s737 ){
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( l[n]->s514() != s493 )
break;
s387* s78 = (s387*)l[n];
s502* s647 = (s502*)l[n + 1];
s656.s565( s78->s644(), s647 );
s281.push_back( s647 );
s607.push_back( s647 );
s658.push_back( s647 );
s659.push_back( s78->s644() );}
s609.insert( s609.end(), l.begin() + n, l.end() );}
void
s630::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
if( !s513 )
s513 = s1287;
return;
s703 = s347;
if( s613->s514() == s498 || s613->s514() == s497 ) {
if( s613->s514() == s497 )
return;}
if( s281.size() > s658.size() )
throw new s17( L"too many arguments" );
for( size_t n = 0; n < s281.size(); ++n ) {
s504 par = s281[n];
if( par->s514() == s493 ) {
if( par.s16<s387*>()->s397().s13() )
par.s16<s387*>()->s520( this );}
else
s281[n] = s918( par );}
for( size_t n = 0; n < s281.size(); ++n ) {
s656.s565( s659[n], s281[n].s16<s502*>(), s501::s151 );
s281[n]->setWh( s7::s942 );
s658[n] = s281[n];}
for( size_t n = 0; n < s609.size(); ++n ) {
if( s609[n]->s514() == s496 ) {
s509 cs = new s585( *s609[n].s16<s585*>() );
s609[n] = s625( cs, s307, s613, this, s613->s305() );}
else if( s609[n]->s514() == s493 )
s609[n].s16<s387*>()->s520( s612 );
else if( s609[n]->s514() != s494 )
s609[n]->s520( s612 );
else // lambda - ?
throw new s17( L"unhandled expression" );}
for( auto it : s609 ) {
if( it->s514() == s494 )
it.s16<Transd*>()->s520( s347, true );}
if( !s513 && s609.size() ) {
s513 = s609.back()->s367();
s611 = s307->TR().s542( s367(), s613, s347 );}}
s505
s630::s517( s502** s724, size_t s733 ){
s505 s718 = s381, s157;
for( size_t n = 0; n < s281.size(); ++n ) {
s505 s157 = s281[n]->s517( NULL, 0 );
if( s157->s645() < 0 )
return s718;
s658[n] = s157.s16<s503*>();}
for( size_t n = 0; n < s609.size(); ++n ) {
s157 = s609[n]->s517( s724, s733 );
s718 = s157;
if( s157->s645() < 0 )
break;}
for( size_t n = 0; n < s281.size(); ++n ) {
s281[n]->release();}
return s718;}
s312::s312( s269* s307, s502* s617, Transd* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s261, s737 ){
if( l.size() < 2 )
throw new s17( s261 + L"(): wrong numbers of arguments" );
s281.push_back( l[0] );
s658.resize( 1 );
s659.push_back( L"@cond" );
s609.insert( s609.end(), l.begin() + 1, l.end() );}
void
s312::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
s313 = s281[0];
s513 = s609.back()->s367();}
s505
s312::s517( s502** s724, size_t s733 ){
s505 s718 = s381, s157;
while( 1 ) {
if( (bool)*s313->s517( 0, 0 ) == false )
return s718; 
for( size_t n = 0; n < s609.size(); ++n ) {
s157 = s609[n]->s517( s724, s733 );
if( s157->s645() < 0 )
break;}
s718 = s157;
if( s157->s645() == s7::s455 || s157->s645() == s7::s456 )
break;}
return s718;}
s315::s315( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s260, s737 ),
s319( s7::s478, s307 ), s320( s307, 0 ){
if( l.size() < 1 )
throw new s17( s260 + L"(): wrong numbers of arguments" );
s656.s565( s319.s644(), &s320 );
s607.push_back( (s502*)&s320 );
s658.push_back( (s502*)&s320 );
s659.push_back( s319.s644() );
s316 = l[0];
s387* w = (s387*) l[1];
if( w->s644() != L"with" )
throw new s17( L"unknown syntax of 'through' statement" );
s317 = (s387*) l[2];
s656.s565( s317->s644(), s318.s16<s502*>() );
s607.push_back( (s502*)&s320 ); //..
s658.push_back( (s502*)&s320 );
s659.push_back( s317->s644() );
s609.assign( l.begin()+3, l.end() );}
void
s315::s520( const wstring& s347, bool proc ){
s490 pc = s316->s514();
if( pc == s496 ) {
s316 = s625( s316.s16<s585*>(), s307, s613, this, s305() );
s316.s16<Transd*>()->s520( s347, proc );}
else if( pc == s493 )
s316.s16<s387*>()->s520( this );
else
throw new s17( L"unknown container type" );
s658[1] = s307->TR().s542( ( (s337*)s316->s516() )->s328(), s613, s347 );
s658[1]->setWh( s7::s942 );
s616::s520( s347, proc );}
s505 s315::s517( s502** s724, size_t s733 ){
s505 s718;
s490 pc = s316->s514();
s1::s9<s337> s613;
if( pc == s494 ) {
s613 = s316->s517(0,0).s16<s337*>();}
else
s613 = ((s337*)s316.s16<s387*>()->s393());
Iterator* s1125 = s613->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() ) {
s718 = s381.s16<s502*>();
break;}
s658[1] = p;
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s724, s733 );
if( s718->s645() < 0 )
break;}
if( s718->s645() == s7::s455 || s718->s645() == s7::s456 )
break;}
return s718;}
s641::s641( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l,
const s270* s737 )
: s616( s307, s617, s618, s589, s266, s737 ),
s319( s7::s478, s307 ), s320( s307, 0 ){
TDException s1061( s7::CLTDFor_ctor1, s1020, s737, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s1061.s1099( L"too few arguments" );
s656.s565( s319.s644(), &s320 );
s607.push_back( (s502*)&s320 );
s658.push_back( (s502*)&s320 );
s659.push_back( s319.s644() );
s278* p = l[0];
if( p->s514() != s493 )
throw s1061.s1099( L"the variable must be a name" );
s749 = (s387*) l[0];
varval = s381.s16<s502*>();
s387* in = (s387*) l[1];
if( in->s644() != L"in" )
throw s1061.s1099( L"the 'in' keyword is missing" );
s316 = l[2];
p = l[3];
size_t idx = 3; 
wstring actmsg = L"the DO clause is non-conforming: should begin with 'select' "
"or 'do' keyword and contain at least one statement.";
if( p->s514() != s493 )
throw s1061.s1099( actmsg );
if( ((s387*)p)->s644() == L"where" ) {
where = l[4];
idx = 5;}
if( l.size() < ( idx + 2 ) )
throw new s17( actmsg );
p = l[idx];
if( p->s514() != s493 )
throw new s17( actmsg );
if( ((s387*)p)->s644() == L"select" ) {
if( l.size()  )
select = l[idx+1];}
else {
if( ((s387*)p)->s644() != L"do" )
throw new s17( actmsg );
s609.assign( l.begin() + (idx + 1), l.end() );}
s656.s565( s749->s644(), NULL );
s607.push_back( varval );
s658.push_back( varval );
s659.push_back( s749->s644() );}
void
s641::s520( const wstring& s347, bool proc ){
TDException s1061( s7::s1549, s1020, s628(), L"malformed syntax of 'for' statement" );
s490 pc = s316->s514();
if( pc == s496 ) {
s504 s617 = s625( s316.s16<s585*>(), s307, s613, this, s305() );
s316 = s617;
s316.s16<Transd*>()->s520( s347, false );}
else if( pc == s493 ) {
s316.s16<s387*>()->s520( this );}
else if( pc == s492 )
s316->s520( this );
else
throw s1061.s1099( L"unknown iterable type" );
s503* s1651 = s316->s516();
s1172 vt = ( (s337*)s1651 )->ValType();
varval = s307->TR().s542(vt, s613, s347 );
varval->setWh( s7::s942 );
s749->s398( varval );
s658[1] = varval.s16<s503*>();
if( where ) {
pc = where->s514();
if( pc == s496 ) {
where = s625( where.s16<s585*>(), s307, s613, this, s305() );
where.s16<Transd*>()->s520( s347, false );}
else
throw s1061.s1099( L"WHERE clause must be a function." );}
if( select ) {
pc = select->s514();
if( pc == s496 ) {
select = s625( select.s16<s585*>(), s307, s613, this, s305() );
select.s16<Transd*>()->s520( s347, false );}
else
throw s1061.s1099( L"DO clause must be a function." );}
s616::s520( s347, proc );}
s505 s641::s517( s502** s724, size_t s733 ){
s505 s718 = s611;
s490 pc = s316->s514();
s9<s337> s613;
if( pc == s494 )
s613 = s316->s517( 0, 0 ).s16<s337*>();
else if( pc == s493 )
s613 = ((s337*)s316.s16<s387*>()->s393());
else
s613 = s316.s16<s337*>();
Iterator* s1125 = s613->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
s658[0] = s1125->Idx();
s658[1] = p.s16<s503*>();
if( where ) {
if( ((bool)*(s502*)where->s517( 0, 0 )) != true )
continue;}
if( select ) {
select->s517( 0, 0 );}
else {
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s724, s733 );
if( s718->s645() < 0 )
break;}
if( s718->s645() == s7::s455 || s718->s645() == s7::s456 )
break;}}
return s718;}
s278* s630::s350()const{
return new s630( *this );}
s278* s312::s350()const{
return new s312( *this );}
s278* s315::s350()const{
return new s315( *this );}
s278* s641::s350()const{
return new s641( *this );}
s629::s629( s269* s307, s502* s613, s616* s612, const std::vector<s278*>& l,
const s270* s737 )
: s616( s307, s613, s612, l, s737 ){
s600 = s597;}
void s629::s678( s1172 s647, s616* pOvr ){
types.push_back( s647 );
s679.push_back( pOvr );}
s505 s629::s517( s502** s724, size_t s733 ){
return s616::s517( s724, s733 );}
s907::s907( s269* s307 )
: s616( s307, NULL, NULL, s589, s258, NULL ){
s512 = s1396;}
s907::s907( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s258, s737 ){
s285 = s258;
s512 = s1396;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( (s502*)l[n] ) == s951 ) {
if( l.size() == n )
throw new s17( L"malformed lambda definition" );
s513 = l[n + 1]->s367();
n += 2;
break;}
if( l[n]->s514() != s493 )
break;
s387* s78 = (s387*) l[n];
lang::s686( s78->s644() );
s502* s647 = (s502*) l[n + 1];
s656.s565( s78->s644(), s647 );
s281.push_back( s647 );
s607.push_back( s647 );
s658.push_back( s647 );
s659.push_back( s78->s644() );}
s609.insert( s609.end(), l.begin() + n, l.end() );}
void
s907::s520( const wstring& s347, bool proc ){
s616::s520( s347, false );
s869::Cont v;
v.push_back( s1265->s367() );
v.push_back( s611->s367() );
for( size_t n = 0; n < s607.size(); ++n )
v.push_back( s607[n]->s367() ); 
s513 = s307->TR().s1155( v );}
s505 s907::s517( s502** s724, size_t s733 ){
s505 s718;
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s605 + n ) ) {
s490 pc = ( ( s503* )*( s605 + n ) )->s514();
if( pc == s493 )
*( s604 + n + shift ) =
(s502*)( ( s387* )*( s605 + n ) )->s393();
else if( pc == s494 ) {
s1077[n+shift] = (s502*)( ( s616* )*( s605 + n ) )->s517( s724, s733 );
*( s604 + n + shift ) = s1077[n + shift];}
else if( pc == s492 )
*( s604 + n + shift ) = ( s502* )*( s605 + n );}}
s658.assign( s608.begin() + 1, s608.end() );
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s604, s518 );
if( s718->s645() < 0 )
break;}
return s718;}
s502* s907::s371( s502* s613, const std::vector<s1172>& vt ) const{
return new s907( *this );}
s278* s907::s350()const{
return new s907( *this );}
void s907::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"Lambda : " <<  s285 << endl;
s616::s311( pd, s202 );}
s632::s632( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s249, s737 ){
s281.assign( l.begin(), l.end() );}
s505 s632::s517( s502** s281, size_t s518 ){
return NULL;}
s633::s633( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s249, s737 ){
s281.assign( l.begin(), l.end() );
s513 = s803->s367();}
s505 s633::s517( s502**, size_t ){
*s611.s16<s361*>()->s373() = 1;
for( size_t n = 0; n < s281.size(); ++n ) {
if( !( bool )*( (s503*)( s281[n]->s517( 0, 0 ) ) ) ) {
*s611.s16<s361*>()->s373() = 0;
return s611;}}
return s611;}
s1579::s1579( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s1603, s737 ),s1677( s7::s1545, s307 ),
s319( s7::s478, s307 ), s320( s307, 0 ){
TDException s1061( s7::CLTDAny_ctor1, s1020, s737, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s1061.s1099( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s656.s565( s319.s644(), &s320 );
s656.s565( s1677.s644(), NULL );
s658.push_back( (s502*)&s320 );
s658.push_back( NULL );
s659.push_back( s319.s644() );
s659.push_back( s1677.s644() );
s316 = l[0];
if( l.size() > 1 )
lambda = l[1];
s513 = s803->s367();}
void
s1579::s520( const wstring& s347, bool proc ){
TDException s1061( s7::s1547, s1020, s628(), L"malformed syntax of 'any()' function call" );
s490 pc = s316->s514();
if( pc == s496 ) {
s504 s617 = s625( s316.s16<s585*>(), s307, s613, this, s305() );
s316 = s617;
s316.s16<Transd*>()->s520( s347, false );}
else if( pc == s493 ) {
s316.s16<s387*>()->s520( this );}
else if( pc == s492 )
s316->s520( this );
else
throw s1061.s1099( L"unknown iterable type" );
varval = s307->TR().s542( ( (s337*)s316->s516() )->ValType(), s613, s347 );
varval->s1414();
s1677.s398( varval );
s658[1] = varval.s16<s503*>();
if( lambda.s14() ) {
if( lambda->s514() == s493 ) {
lambda.s16<s387*>()->s520( s612 );}
else {
lambda = s278::s1122( s307, lambda, this, this, s612->s305() );}}
s616::s520( s347, false );}
s505 s1579::s517( s502**, size_t  ){
TDException s1061( s7::s1548, s1550, past );
s505 s718 = s611;
*s718.s16<s376*>()->s373() = false;
s490 pc = s316->s514();
s9<s337> s613;
if( pc == s494 )
s613 = s316->s517( 0, 0 ).s16<s337*>();
else if( pc == s493 )
s613 = ( (s337*)s316.s16<s387*>()->s393() );
else
s613 = s316.s16<s337*>();
Iterator* s1125 = s613->s322( NULL );
while( 1 ) {
s504 p = s1125->s323();
if( p.s13() )
break;
s658[0] = s1125->Idx();
s658[1] = p.s16<s503*>();
if( lambda.s14() ) {
if( ( ( bool )*(s502*)lambda->s517( 0, 0 ) ) == true ) {
*s718.s16<s376*>()->s373() = true;
break;}}
else {
if( ( ( bool )*p.s16<s502*>() ) == true ) {
*s718.s16<s376*>()->s373() = true;
break;}}}
return s718;}
vector<wstring> s1049( { L"else", L"elsif" } );
s634::s634( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s236, s737 ){
wstring s747 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s17( s747 + L"too few arguments." );
s281.assign( l.begin(), l.end() );
s616::s1393( ( vector<s278*>& )l, s1049 );}
void s634::s777( bool proc ){
wstring s747 = L"malformed syntax of 'if' statement: ";
s648.push_back( s281[0] );
s649.push_back( s603() );
s649.back().push_back( s281[1] );
if( s281.size() > 2 ) {
size_t n = 2;
while( n < s281.size() ) {
s504 p = s281[n];
s490 pc = s281[n]->s514();
if( pc == s1174 ) {
if( p.s16<s387*>()->Id() == s1371 ) {
if( s281.size() < n + 2 )
throw new s17( s747 + L"incomplete clause" );
s648.push_back( s281[++n] );
s649.push_back( s603() );
s649.back().push_back( s281[n] );}
else if( p.s16<s387*>()->Id() == s1370 ) {
if( s281.size() < n + 1 )
throw new s17( s747 + L"empty clause" );
s649.push_back( s603() );
s649.back().push_back( s281[++n] );}
else
s649.back().push_back( s281[n] );}
else
s649.back().push_back( s281[n] );
n++;}}
if( !proc ) {
size_t s961 = s649[0].size();
s1172 prevPt = s608[s961]->s367();
for( size_t n = 1; n < s649.size(); ++n ) {
s961 += s649[n].size() + 1;
s1172 tmpPt = s608[s961]->s367();
if( tmpPt && tmpPt != s829->s367() && ( tmpPt != prevPt ) )
throw new s17( L"the return type of 'if' branches doesn't match" );}
s513 = prevPt;}
else
s513 = s781->s367();}
void
s634::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
s777( proc );
s611 = s307->TR().s542( s367(), s613, s347 );
s608.insert( s608.begin(), s611 );}
s505 s634::s517( s502**, size_t ){
size_t idx = string::npos;
for( size_t n = 0; n < s648.size(); ++n ) {
if( ( bool )*( s648[n]->s517( 0, 0 ).s16<s502*>() ) )
idx = n;}
if( idx != string::npos || s649.size() > s648.size() ) {
if( idx == string::npos )
idx = s649.size() - 1;
s505 s718;
s603& el = s649[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s718 = el[n]->s517( 0, 0 );
if( s718->s645() < 0 )
break;}
return s718;}
return s381;}
vector<wstring> s1047( { L"to:", L":sign" } );
s635::s635( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s257, s737 ), s43( NULL ){
if( l.empty() )
throw new s17( L"Wrong numbers of arguments" );
vector<s278*>tmp( l );
s616::s1393( tmp, s1047 );
s281.assign( tmp.begin(), tmp.end() );
s513 = s781->s367();}
s635::s635( s269* s307 )
: s616( s307, NULL, NULL, s589, s257, NULL ), s43( NULL ){
s513 = s781->s367();}
void s635::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
if( s281[0]->s514() == s1174 ) {
if( s281[0].s16<s387*>()->Id() == s1381 ) {
s43 = s281[1];
s281.erase( s281.begin(), s281.begin() + 2 );
s608.erase( s608.begin()+1, s608.begin() + 3 );
nlocs = s281.size();
s518 = s608.size();}}}
s505 s635::s517( s502** s724, size_t s733 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s605 + n ) ) {
s490 pc = ( ( s503* )*( s605 + n ) )->s514();
if( pc == s493 || pc == s1505 )
*( s604 + n + shift ) =
(s502*)( ( s387* )*( s605 + n ) )->s393();
else if( pc == s494 ) {
s1077[n + shift] = (s502*)( ( s616* )*( s605 + n ) )->s517( s724, s733 );
*( s604 + n + shift ) = s1077[n + shift];}}}
s1::s9<Stream> s828;
if( s43.s14() ) {
s490 pc = s43->s514();
if( pc == s494 )
s828 = s43->s517( 0, 0 ).s16<Stream*>();
else if( pc == s493 )
s828 = (Stream*)s43.s16<s387*>()->s393();
else
s828 = s43.s16<Stream*>();}
else
s828 = s1577.s16<Stream*>();
for( size_t n = 1; n < s608.size(); ++n ) {
if( s608[n]->s514() == s1174 ) {
int mark = (int)*( (s387*)s608[n] )->s393();
if( mark == s1644 ) {
if( n < s608.size() + 1 &&
s307->TR().s1640( s608[n + 1]->s367(), s1687::s1426 ) ) {
if( (int)*s608[n+1] < 0 )
(void)0;//s828->s1655( L"-" );
else
s828->s1655( L"+" );}}}
else {
s505 s157 = s608[n]->s517( s724, s518 );
s828->s1655( s157->to_wstring() ); }}
return s381;}
s278* s635::s350()const{
return new s635( *this );}
s908::s908( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s925, s737 ){
if( l.size() != 1 )
throw new s17( s925 + L": wrong number of arguments" );
s609.assign( l.begin(), l.end() );}
void
s908::s520( const wstring& s347, bool proc ){
s616::s520( s347, false );
s611 = s609[0]->s516();}
s505 s908::s517( s502** s741, size_t s518 ){
return s616::s517( s741, s518 );}
s278* s908::s350()const{
return new s908( *this );}
s984::s984( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s988, s737 ), code( 0 ){
if( l.size() > 1 )
throw new s17( s988 + L": wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s1285;}
void
s984::s520( const wstring& s347, bool proc ){
s616::s520( s347, false );
if( s281[0]->s367() != s1285 )
throw new s17( L"The parameter to (exit ) must have Integer type." );}
s505 s984::s517( s502** s741, size_t s518 ){
s616::s517( s741, s518 );
code = (int)*s608[1];
throw new s17( (uint32_t) code );}
s278* s984::s350()const{
return new s984( *this );}
s637::s637( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s265, s737 ), s80( s307 ){
if( l.size() != 1 )
throw new s17( s265 + L": wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s829->s367();
s80.s11();}
s637::s637( s269* s307 )
: s616( s307, NULL, NULL, s589, s265, NULL ), s80( s307 ){
s513 = s829->s367();
s80.s11();}
void
s637::s520( const wstring& s347, bool proc ){
s80.s379( s281[0]->to_wstring() );
s611 = s382.s16<s502*>();
s608.push_back( s281[0]->s516() );}
s505 s637::s517( s502** s741, size_t s518 ){
s80.s379( s281[0]->s517( s741, s518 )->to_wstring() );
return &s80;}
s638::s638( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s263, s737 ), s78( s7::s477, s307 ), s647( s307 ){
if( l.size() < 2 )
throw new s17( s263 + L"(): wrong numbers of arguments" );
s656.s565( s78.s644(), &s647 );
s607.push_back( (s502*)&s647 );
s658.push_back( (s502*)&s647 );
s659.push_back( s78.s644() );
s609.assign( l.begin(), l.end() );
if( ((s585*)l.back())->s306() != s264 )
throw new s17( L"the catch clause must be the last statement in the try block" );}
s638::s638( s269* s307 )
: s616( s307, NULL, NULL, s589, s263, NULL ), s78( s7::s477, s307 ), s647( s307 ){}
void
s638::s520( const wstring& s347, bool proc ){
s616::s520( s347, proc );
ctch = s609.back().s16<s639*>();
s609.pop_back();}
s505 s638::s517( s502** s741, size_t s518 ){
s502* s718 = NULL;
for( size_t n = 0; n < s609.size(); ++n ) {
s718 = s609[n]->s517( s741, s518 );
if( s718->s645() < 0 ) {
if( s718->s645() == s7::s456 ) {
s647.s379( ((s377*)s718)->Msg() );
s718 = ctch->s517( &s718, 1 );}
break;}}
return s718;}
s639::s639( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s264, s737 ){
s609.assign( l.begin(), l.end() );
s513 = s781->s367();}
s639::s639( s269* s307 )
: s616( s307, NULL, NULL, s589, s264, NULL ){
s513 = s781->s367();}
s505 s639::s517( s502** s724, size_t s733 ){
s502* s157;
for( size_t n = 0; n < s609.size(); ++n ) {
s157 = s609[n]->s517( s724, s733 );
if( s157->s645() < 0 ) {
return s157;}}
return s381.s16<s502*>();}
s800::s800( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s796, s737 ){}
void
s800::s520( const wstring& s347, bool proc ){}
s505 s800::s517( s502** s741, size_t s518 ){
return 0;}
s278* s634::s350() const{
return new s634( *this );}
s278* s632::s350() const{
return new s632( *this );}
s278* s633::s350()const{
return new s633( *this );}
s278* s1579::s350()const{
return new s1579( *this );}
s278* s637::s350()const{
return new s637( *this );}
s278* s638::s350()const{
return new s638( *this );}
s278* s639::s350()const{
return new s639( *this );}
s278* s800::s350()const{
return new s800( *this );}
s636::s636( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s262, s737 ){
if( l.size() != 1 )
throw new s17( s262 + L"(): wrong numbers of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s803->s367();}
s636::s636( s269* s307 )
: s616( s307, NULL, NULL, s589, s262, NULL ){
s513 = s803->s367();}
void s636::s520( const wstring& s582, bool proc ){
s616::s520( s582, proc );}
s505 s636::s517( s502** s741, size_t s518 ){
try {
s505 s157;
if( s281[0]->s514() == s493 )
s157 = s281[0].s16<s387*>()->s393();
else if( s281[0]->s514() == s494 )
s157 = s281[0].s16<s616*>()->s517( NULL, 0 );
else
s157 = s281[0].s16<s502*>();
wstring f = s157->s517( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s504> s1000;
s1036 ast_ = new s270( f, s628()->Nqj() );
s509 cs = s616::s1237( *ast_, s307, s613, s305() );
s1000.push_back( cs );
s507 s998 = s616::s625( cs, s307, s613, this, s305() );
s998->s520( s305(), true );
s998->s517( 0, 0 );}
else {
vector<wstring> l;
s307->callFunc( f, l );}}
catch( s17* e ) {
(void)e;
return s386;}
return s385;}
s278* s636::s350() const{
return new s636( *this );}
s269* s642::s994 = NULL;
s642::s642( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s268, s737 ){
if( l.size() != 1 )
throw new s17( s268 + L"(): wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s781->s367();}
s642::s642( s269* s307 )
: s616( s307, NULL, NULL, s589, s268, NULL ){
s513 = s781->s367();}
s505 s642::s517( s502** s741, size_t s518 ){
vector<wstring> s999;
for( size_t n = 0; n < s281.size(); ++n ) {
s999.push_back( s281[n]->s517( 0, 0 )->to_wstring() );}
if( !s994 ) {
s994 = new s269();
s994->s520( true );}
else
s994->reset();
s994->s214( s999[0] );
s994->run( s999 );
return s381;}
s278* s642::s350()const{
return new s642( *this );}
s849::s849( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s617, s618, s589, s819, s737 ){
if( l.size() != 1 )
throw new s17( s819 + L"(): wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s781->s367();}
s505 s849::s517( s502** s741, size_t s518 ){
s505 s199 = s281[0]->s517( s741, s518 );
s307->s214( s199->to_wstring() );
return s381;}
s278* s849::s350()const{
return new s849( *this );}
s824::s824( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l,
const s270* s737 )
: s616( s307, s617, s618, s589, s879, s737 ){
s992 = s617->s305();
if( l.size() != 1 )
throw new s17( s879 + L"(): wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s781->s367();}
s505 s824::s517( s502** s741, size_t s518 ){
s278* par = s281[0];
wstring s990;
if( par->s514() == s493 )
s990 = ((s387*)par)->s517( 0, 0 )->to_wstring();
else
s990 = par->s517( 0, 0 )->to_wstring();
try {
s279* ob = ((s279*)s307->s671( s992, s992 ));
ob->s579( s990, s992 );}
catch( s17* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s381;}
s278* s824::s350()const{
return new s824( *this );}
s1474::s1474( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l,
const s270* s737 )
: s616( s307, s617, s618, s589, s1484, s737 ){
if( l.size() != 1 )
throw new s17( s1484 + L"(): wrong number of arguments" );
s281.assign( l.begin(), l.end() );
s513 = s781->s367();}
s505 s1474::s517( s502** s741, size_t s518 ){
s278* par = s281[0];
wstring s703;
if( par->s514() == s493 )
s703 = ((s387*)par)->s517( 0, 0 )->to_wstring();
else
s703 = par->s517( 0, 0 )->to_wstring();
try {
s307->s1520( s703 );}
catch( s17* e ) {
wcout << L"An error occured while uloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s381;}
s278* s1474::s350()const{
return new s1474( *this );}
s826::s826( s269* pass_, const wstring& s815, const vector<wstring>& s785,
std::vector<s504>& types ){
s794 s831( pass_, pass_, s815 );
s831.s520( pass_ );
vector<s504> s878 = s831.s329();
if( s878.size() != types.size() )
throw new s17( L"The number of record's fields doesn't match to the number of columns: " + s815 );
for( size_t n = 0; n < s878.size(); ++n ) {
if( !s878[n]->s522( types[n].s16< s502*>() ) )
throw new s17( L"The types of record's fields don't match to the types of columns: " + s815 );
s809.insert( make_pair( s785[n], s878[n] ) );
size_t h = s878[n].s16<s502*>()->s331();
rechash = ( rechash << 1 ) ^ h;}}
size_t s826::s331() const{
return rechash;}
s505 s826::s806( const std::wstring& s78, bool s751 ) const{
auto it = s809.find( s78 );
if( it == s809.end() ) {
if( s751 )
throw new s17( L"Record field doesn't exist: " + s78, 
(uint32_t)s17::s18::s24 );
else
return s505();}
return it->second.s16<s502*>();}
void s826::s938( s794& s157 ) const{
for( auto r: s809 )
s157.add( r.second );}
void s826::s569( std::vector<std::wstring>& s157 ) const{
for( auto r: s809 )
s157.push_back( r.first );}
bool s826::operator==( const s826* p ) const{
return rechash == p->rechash;}
bool s826::operator<( const s826* p ) const{
return rechash < p->rechash;}
wstring s826::to_wstring() const{
wstringstream ss;
s311( &ss, 0 );
return ss.str();}
void s826::s311( std::wostream* pd, int s202/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"TSDRecord : " << endl;
for( auto it = begin( s809 ); it != end( s809 ); ++it ) {
buf << s4::fill_n_ch( L' ', s202 + s435 ) << it->first << L":" << endl;
it->second->s311( pd, s202 + s435 );}}
s868::s868( vector<wstring>& s773, s880 rec ){
for( size_t n = 0; n < s773.size(); ++n ) {
s504 f = rec->s806( s773[n] ).s16<s503*>();
s864.push_back( f );}
for( size_t n = 0; n < s773.size(); ++n ) {
size_t h = s864[n].s16<s502*>()->s331();
s852 = ( s852 << 1 ) ^ h;}}
size_t s868::s331() const{
return s852;}
bool s868::operator==( const s868* p ) const{
return s852 == p->s852;}
bool s868::operator<( const s868* p ) const{
return s852 < p->s852;}
void s868::s311( std::wostream* pd, int s202/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s864.size(); ++n ) {
s864[n]->s311( pd, s202 + s435 );}}
s680::s680( s269* s307, const wstring& s79, const s270* ast_ )
: s351( s307, NULL, ast_ ){
s519 = s79;
s513 = s808.s13() ? 0 : s808->s367();}
s680::s680( const s680& right, const s270* ast_ )
: s351( right.s307, right.ns, ast_ ){
s513 = right.s513;}
s502* s680::s370( const s270& s737, s502* s613, const std::wstring& s347 ){
return new s680( s307, L"" );}
void s680::s520( s502* s962 ){
s1414();}
void s680::s365(){
s363.insert( make_pair( L"new", new s352( L"new", &s680::s1385, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"add-file", new s352( L"add-file", &s680::s837, s1287,
{ s1240( { s1289 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"load-table", new s352( L"load-table", &s680::s854, s1287,
{ s1240( { s1289, s1289 } ) }, 1, 2 ) ) );
s363.insert( make_pair( L"select", new s352( L"select", &s680::s797, s1287,
{ s1240( { s1289 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"query", new s352( L"query", &s680::s817, s1287,
{ s1240( { s1289 } ) }, 1, 1 ) ) );
s363.insert( make_pair( L"erase", new s352( L"erase", &s680::s345, s1287,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"size", new s352( L"size", &s680::s340, s1285,
{ s1240() }, 0, 0 ) ) );
s363.insert( make_pair( L"build-index", new s352( L"build-index", &s680::s929, s1287,
{ s1240( { s1289 } ) }, 1, 1 ) ) );}
s502* s680::s371( s502* s613, const std::vector<s278*>& l, const s270* ast_ ) const{
return new s680( s307, L"" );}
inline bool
s680::s522( const s502* s523 ) const{
return ( ((s680*)s523)->s367() == s367() );}
s278* s680::s350() const{
return new s680( *this );}
void s680::s372( s278* p ) const{
p = new s680( *this );}
size_t s680::s331() const{
return (size_t)this;}
bool s680::operator==( const s502* p ) const{
return ( this == p );}
bool s680::operator<( const s502* p ) const{
return false;}
#define DR ((s503*)*(s281 + 1))
#define PARN(n)((s503*)*(s281 + n))
#undef s734
#define s734 ((s680*)(s503*)*s281)
inline void s680::s1385( s502** s281, size_t s518 ){
s680* ps = (s680*)DR;
s680* s718 = new s680( ps->s307, ps->s628() );
s718->s520( ps->ns );
*s281 = (s502*)s718;}
inline void s680::s837( s502** s281, size_t s518 ){
wstring s199 = PARN( 2 )->to_wstring();
( (s680*)DR )->s684( s199 );}
inline void s680::s854( s502** s281, size_t s518 ){
s680* dr = ( (s680*)DR );
const wstring& s882 = PARN( 2 )->to_wstring();
wstring s858;
if( s518 == 4 )
s858 = PARN( 3 )->to_wstring();
dr->s755( s882, s858 );}
inline void s680::s797( s502** s281, size_t s518 ){
wstring s199 = PARN( 2 )->to_wstring();
( (s680*)DR )->s685( s199 );}
inline void s680::s817( s502** s281, size_t s518 ){
wstring s199 = PARN( 2 )->to_wstring();
( (s680*)DR )->s685( s199 );}
inline void s680::s345( s502** s281, size_t s518 ){}
inline void s680::s340( s502** s281, size_t s518 ){}
inline void s680::s343( s502** s281, size_t s518 ){}
inline void s680::s929( s502** s281, size_t s518 ){
wstring s931 = PARN( 2 )->to_wstring();
((s680*)DR)->s928( s931 );}
void s680::s684( const wstring& s199 ){
vector<s9<s147>> s693;
s1034 s1160( s199 );
s1160.read( s693, s7::s1224 );
for( size_t m = 0; m < s693.size(); m++ ) {
s147* obj = s693[m];
wstring s688 = s4::s54( s270::s309( *obj, s7::s481 ), 
s50 );
if( s688.empty() )
throw new s17( L"Nameless blocks are forbidden." );
vector<pair<wstring, s146>> s148;
obj->s164( s148 );
for( size_t n = 0; n < s148.size(); ++n ) {
if( s148[n].second->s168() != s138 && s148[n].second->s168() != s143 )
throw new s17( L"unrecognized format of field " + s688 +L"::"+s148[n].first );
wstring sobj = s148[n].second->s173();
wstring srel = s148[n].first;
s681.insert( make_pair( s688, make_pair( srel, sobj ) ) );
s682.insert( make_pair( srel, make_pair( s688, sobj ) ) );
s683.insert( make_pair( sobj, make_pair( s688, srel ) ) );}}}
void s680::s685( const std::wstring& q ){
vector<wstring> qs;
s4::s59( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s681.begin(); it != s681.end(); ++it )
wcout << it->first;}}
void s680::select( std::wstring& s931, s505 s685, 
s336::mapped_type::iterator& s949, s336::mapped_type::iterator& s950 ){
auto it = s946.find( s931 );
if( it == s946.end() )
throw new s17( L"Index doesn't exist: " + s931 );
if( s685.s14() ) {
auto s157 = it->second[s931].equal_range( s685 );
s949 = s157.first;
s950 = s157.second;}
else {
s949 = it->second[s931].begin();
s950 = it->second[s931].end();}}
void s680::s755( const wstring& s882, const wstring& s767 ){
wstring s785 = s767;
vector<wstring> s872;
vector<wstring> s772;
vector<wstring> s857;
vector<wstring> s883;
if( s785.size() ) {
s4::s59( s785, L",", s872 );
s4::s59( s4::s54( s882, s50 ), L"\n", s857 );}
else {
s785 = s882.substr( 0, s882.find( L"\n" ) );
s4::s59( s4::s54( s882.substr( s785.size() ), s50 ), L"\n", s857 );
if( s785.back() == '\r' )
s785.pop_back();
s4::s59( s785, L",", s872 );}
for( size_t n = 0; n < s872.size(); ++n ) {
if( s872[n][0] != L'@' )
s772.push_back( s872[n] );
else {
size_t pl = s872[n].find( L"_" );
if( pl == string::npos )
throw new s17( L"Invalid column name: " + s872[n] );
wstring s78 = s872[n].substr( pl + 1 );
s772.push_back( s78 );
s883.push_back( s78 );}}
if( !s883.empty() ) {
s794 s831( s307, s307, s857[0] );
s831.s520( s307 );
vector<s504> types = s831.s329();
for( auto row : s857 ) {
s880 rec = new s826( s307, row, s772, types );
s775 s156 = new s868( s883, rec );
s802.insert( make_pair( s156, rec ) );}}}
void s680::s928( const wstring& s931 ){
auto it = s946.find( s931 );
if( it != end( s946 ) )
s946.erase( it );
s336& s945 = s946.insert( make_pair( s931, s336() ) ).first->second;
for( auto it: s802 ) {
s505 pd = it.second->s806( s931 );
if( pd.s14() )
s945[s931].insert( make_pair( pd, it.second ) );}}
wstring s680::to_wstring() const{
basic_stringstream<wchar_t> ss;
s311( &ss, 0 );
return ss.str();}
void s680::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s202 ) << L"TSDBase : " << endl;
for( auto it = begin( s802 ); it != end( s802 ); ++it ) {
it->first->s311( pd, s202 + s435 );
it->second->s311( pd, s202 + s435 );}}
struct s919{
size_t idx;
s919( size_t s944 ): idx( s944 ){}
bool operator()( const s505 l, const s505 r ) const{
s505 ld = l.s16<s794*>()[idx];
s505 rd = r.s16<s794*>()[idx];
return ld->operator<( (s502*)&(*rd) );}
};
vector<wstring> s1048( { L"select:", L"all", L"as:", L"where:", L":distinct",
L"sortby:", L":asc", L":desc", L"limit:" } );
s842::s842( s269* s307, s502* s617, s616* s618, const std::vector<s278*>& l_, const s270* s737 )
: s616( s307, s617, s618, s589, s875, s737 ),
s774( s7::s478, s307 ), s833( new s279( s307, 0, s499 ) ){
TDException s1061( s7::s1228, s1020, s737 );
if( l_.size() < 3 )
throw s1061.s1099( L"too few arguments." );
s616::s1393( ( vector<s278*>& )l_, s1048 );
s656.s565( s774.s644(), s833.s16<s502*>() );
s607.push_back( s833.s16<s502*>() );
s281.push_back( s833.s16<s502*>() );
s658.push_back( s833.s16<s502*>() );
s659.push_back( s774.s644() );
const size_t s1164 = 8;
std::vector<s278*> l( s1164 );
s504 p = l_[0];
if( p->s514() != s493 && p->s514() != s494 )
throw s1061.s1099( L"the database object must be specified by a name or expression." );
l[0] = l_[0];
size_t s1084 = 1;
for( size_t n = 1; n < l_.size() /*&& s1084 < s1164*/; ++n ) {
if( l_[n]->s514() == s1174 ) {
s387* rf = (s387*)l_[n];
if( rf->Id() == s1379 ) s1084 = 1;
else if( rf->Id() == s1363 ) s1084 = 2;
else if( rf->Id() == s1362 ) {
s1084 = s1272;
l[1] = l_[n];}
else if( rf->Id() == s1384 ) s1084 = 3;
else if( rf->Id() == s1368 ) {
s1084 = s1272;
s863.distinct = 1;}
else if( rf->Id() == s1380 ) {
s863.s974 = s786::s906::s889;
s1084 = 5;}
else if( rf->Id() == s1364 ) {
if( s1084 != 6 )
throw s1061.s1099( L"the '" + rf->s644() + L"' specifier is misplaced" );
s1084 = s1272;
s863.s974 = s786::s906::s889;}
else if( rf->Id() == s1367 ) {
if( s1084 != 6 )
throw s1061.s1099( L"the '" + rf->s644() + L"' specifier is misplaced" );
s1084 = s1272;
s863.s974 = s786::s906::s896;}
else if( rf->Id() == s1378 ) s1084 = 7;}
else
l[s1084++] = l_[n];}
db = l[0];
what = l[1];
s1183 = l[2];
where = l[3];
s976 = l[5];
s953 = l[7];
if( s1183.s13() )
throw s1061.s1099( L"the 'as' clause is missing" );}
void
s842::s520( const wstring& s347, bool proc ){
s1183->s520( this );
s869::Cont s1434;
wstring sv = s1183->s369();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n-1] == L'<' )
sv.erase( n--, 1 );
wstring ts = s765->s369() + L"<" + sv + L">";
s513 = s765->s1339( ts, s1434 );
TDException s1061( s7::s1008, s1020, past );
s616::s520( s347, proc );
s490 pc = db->s514();
if( pc == s496 ) {
db = s625( db.s16<s585*>(), s307, s613, this, s305() );
db->s520( this );}
else if( pc == s493 )
db.s16<s387*>()->s520( this );
else
throw s1061.s1099( L"the database must be specified by a name or expression." );
pc = what->s514();
if( pc == s496 ) {
what = s625( what.s16<s585*>(), s307, s613, this, s305() );
what->s520( this );}
else if( pc == s493 )
what.s16<s387*>()->s520( this );
else if( pc == s492 || pc == s1174 )
(void)0;
else
throw s1061.s1099( L"the query field(s) must be specified by a name or expression." );
if( where ) {
pc = where->s514();
if( pc == s496 ) {
where = s625( where.s16<s585*>(), s307, s613, this, s305() );
where.s16<Transd*>()->s520( s347, false );
s901 s965;
where.s16<Transd*>()->s870( s965 );}
else
throw s1061.s1099( L"the 'where' clause must be a lambda." );}
else {
std::vector<s278*> s963;
s963.push_back( s385 );
where = (s503*) new s907( s307, 0, 0, s963, NULL );
where.s16<Transd*>()->s520( s347, false );}
if( s953.s14() ) {
pc = s953->s514();
if( pc == s496 ) {
s953 = s625( s953.s16<s585*>(), s307, s613, this, s305() );
s953->s520( this );}
else if( pc == s493 )
s953.s16<s387*>()->s520( this );
else if( s953->s367() != s1285 )
throw s1061.s1099( L"the limit must be specified by a number, variable or expression." );}}
s505 s842::s517( s502** s724, size_t s733 ){
s505 s718 = s611;
vector<wstring> s982;
vector<wstring> s983;
s680* base;
size_t s996 = string::npos;
TDException s1061( s7::s1009, s1017, past );
assert( db->s514() == s493 );
base = ((s680*)db.s16<s387*>()->s393());
if( s953.s14() ) {
if( s953->s514() == s493 ) {
s863.s953 = (int)*((s361*)s953.s16<s387*>()->s393());}
else if( s953->s514() == s494 ) {
s863.s953 = (int)*s953->s517( 0, 0 );}
else
s863.s953 = (int)*s953;}
if( s976.s14() ) {
if( s976->s514() == s493 ) {
s863.s973 = s976.s16<s387*>()->s393()->to_wstring();}
else if( s976->s514() == s494 ) {
s863.s973 = s976->s517( 0, 0 )->to_wstring();}
else
s863.s973 = s976->to_wstring();}
std::unordered_set<s880, s917, s916> dom;
s680::s336::mapped_type::iterator beg, end;
s490 pc = what->s514();
if( pc == s493 ) {
throw new s17( L"'select REF' : to be implemented." );}
else if( pc == s1174 ) {
s508 rf = what.s16<s387*>();
if( rf->s644() == L"all" || rf->s644() == L"ALL" )
(void)0;
else
throw s1061.s1099( L"fields for selection are not recognized" );}
else if( pc == s492 ) {
const s869& vt = s307->TR().s1114( what->s367() );
if( vt.s367() == s765->s367() ) {
const vector<s504>& v = what.s16<s324*>()->s329();
for( auto it: v ) {
wstring s931 = it->to_wstring();
size_t s966 = s4::s90.find( s931[0] );
if( s966 != string::npos )
s931 = s4::s54( s931, wstring( 1, s4::s90[s966] ) );
s982.push_back( s931 );
if( s983.empty() ) {
base->select( s982.back(), s505(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;}}}}}
s901 s965;
where.s16<Transd*>()->s870( s965 );
for( size_t n = 0; n < s965.size(); ++n ) {
s983.push_back( s965[n].first );
base->select( s983.back(), s505(), beg, end );
while( beg != end ) {
dom.insert( beg->second );
++beg;}}
vector<s504> s964;
s964.resize( s983.size() );
s611.s16<s324*>()->clear();
for( auto r : dom ) {
for( size_t n = 0; n < s983.size(); ++n )
s964[n] = r->s806( s983[n] ).s16<s503*>();
where.s16<Transd*>()->s621( s964 );
s505 s157 = where->s517( 0, 0 );// ( (s502**)&s964[0], s964.size() );
if( s157.s14() && (bool)*s157 ) {
s1::s9<s794> s981 = new s794( s307, NULL, L"" );
if( s982.empty() )
r->s938( *s981 );
else {
for( size_t n = 0; n < s982.size(); ++n )
s981->add( r->s806( s982[n] ).s16<s503*>() );}
s981->setWh( s7::s942 );
s611.s16<s324*>()->add( s981 );}}
if( s863.distinct != -1 ) {
vector<s504>& s987 = s611.s16<s324*>()->s329();
for( size_t n = 0; n < s987.size(); ++n ) {
s504 s986 = s987[n];
size_t m = n + 1;
while( m < s987.size() ) {
s504 _el1 = s987[m];
if( *s986.s16<s794*>() == _el1.s16<s502*>() )
s987.erase( s987.begin() + m );
else
m++;}}}
if( s863.s974 != -1 ) {
if( s982.size() && s863.s973.size() ) {
auto it = std::find( s982.begin(), s982.end(), s863.s973 );
if( it != s982.end() )
s996 = std::distance( s982.begin(), it );
else
throw new s17( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s991;
(*dom.begin())->s569( s991 );
auto it = std::find( s991.begin(), s991.end(), s863.s973 );
if( it != s991.end() )
s996 = std::distance( s991.begin(), it );
else
throw new s17( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s985> s989 = new s985;
s989->s995( s996 );
s910 s997( s989 );
s611.s16<s324*>()->sort( s863.s974 == s786::s896, &s997 );}
if( s863.s953 != -1 ) {
s611.s16<s324*>()->s329().resize( s863.s953 );}
return s718;}
s278* s842::s350()const{
return new s842( *this );}
vector<wstring> s1543 /*= { L"", s1602, s249, s1603, 
s264, s262, 
s988, s266, s236, s819, 
s879, s258, s250, s925,
s268, s805, s257, s265, 
s263, s875, s1484, s261, 
s239 }*/;
vector<int> BIFuncs1v = {
0, 0, 0, s1606, s1607, 0, s1609, s1610, 0, 0, 0,
s1613, 0, s1616, 0, s1618, 0, 0, s1621, s1622,
0, s1624, s1625
};
std::map<std::wstring, int> s1542;
s269::s269()
: s279( this, 0, s491 ), s737( s233, L"", L"global" ),
s205( L"" ), s208( this ), s1486( false ){}
s269::~s269(){}
void s269::reset(){
s656.reset();
s208.s841();
s204.clear();
s737.reset();
s1486 = false;}
void s269::s520( bool soft /*=false*/ )
{
s351::s835( this, soft );
s208.s297();
s211[s7::s450] = s383.s16<s502*>();
s211[s7::s449] = s384.s16<s502*>();
s922( s7::s452, s385.s16<s502*>() );
s922( s7::s453, s386.s16<s502*>() );
s922( s7::s897, s381.s16<s502*>() );
s1577 = new s1576( this, this );
s1575 = new s1574( this, this );
s922( s7::s1563, s1575.s16<s502*>() );
s922( s7::s1564, s1577.s16<s502*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s375* s1648 = new s375( this, os );
s922( s7::s1544, s1648 );
if( s1542.empty() ) {
s1543 = { L"", s1602, s249, s1603,
s264, s262,
s988, s266, s236, s819,
s879, s258, s250, s925,
s268, s805, s257, s265,
s263, s875, s1484, s261,
s239 };
for( size_t n = 1; n < s1543.size(); ++n )
s1542[s1543[n]] = (int)n;}}
void s696( const std::wstring& s687, s759& s157 ) {
vector<s9<s147>> s693;
s1037 s1160 = new s1034( s687 );
s1160->read( s693, s7::s434 );
for( size_t n = 0; n < s693.size(); n++ ) {
wstring s688 = s270::s309( *s693[n], s7::s481 );
if( s688 == s7::s469 ) {
if( ( *s693[n] ).s160( s7::s483 ) ) {
const vector<s146>& s166 = ( *s693[n] ).s162( s7::s483 )->s171();
for( size_t n = 0; n < s166.size(); n++ )
s157.s694.push_back( s166[n]->s173() );}
if( ( *s693[n] ).s160( s7::s482 ) )
s157.entry = ( *s693[n] ).s162( s7::s482 )->s930();}}
if( s157.s694.empty() )
s157.s694.push_back( s687 );}
wstring s754( const wstring& s798, const wstring& s801 ){
if( s3::s761( s801 ) )
return s801;
if( !s3::s761( s798 ) )
throw new s17( L"The root path is not absolute: " + s798 );
if( s801.empty() )
return s798;
wstring path = s801;
wstring root = s798;
s4::s63( path );
s4::s63( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s17( L"The relative path '" + s801 + L"' is incompatible with the root '" + s798 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s17( L"The relative path '" + s801 + L"' is incompatible with the root '" + s798 + L"'." );}
return root + path;}
void s269::s218( const std::wstring& s199, const s147& obj ){
const vector<s146>& s769 = ( obj ).s162( s7::s488 )->s171();
const vector<s146>& packs = ( obj ).s162( s7::s780 )->s171();
vector<wstring> s42;
wstring s783 = s199.substr( 0, s199.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s769.size(); n++ )
s42.push_back( s754( s783, s769[n]->s173() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s173();
if( req.rfind( s7::s473 ) == req.size() - s7::s473.size() ) {
if( std::find( s204.begin(), s204.end(), req ) == s204.end() )
s204.push_back( s754( s783, req ) );}
else {
vector<wstring> matches;
for( size_t n = 0; n < s42.size(); n++ ) {
wstring match;
if( s3::s32( s42[n], req + s7::s473, match ) )
matches.push_back( match );}
if( matches.empty() ) {
throw new s17( L"The required library '" + req + L"' is not found." );}
else if( matches.size() > 1 ) {
wstring s779;
s4::s296( matches, L",\n", s779 );
throw new s17( L"The required library's name '" + req + L"' is ambiguous: \n" + s779 );}
if( std::find( s204.begin(), s204.end(), matches[0] ) == s204.end() )
s204.push_back( matches[0] );}}}
void s708( s269* s307, s270& s737, s501& s690,
s651& cl, s650& cnl, s652& al ){
s270::s282& s738 = s737.s300();
s270::s282::iterator it = s738.begin();
s560 am = s532;
for( ; it != s738.end(); ++it ) {
s490 pc = s498;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s721;
s4::s59( it->first, L" ", s721 );
if( s721.size() > 3 )
throw new s17( L"malformed block name: " + it->first );
wstring s688 = s721[1];
size_t idx = s721.size() - 2;
if( s721[idx] == s7::s467 )
pc = s497;
else if( s721[idx] == s7::s468 )
pc = s498;
else
throw new s17( L"unknown object type: " + s721[0] );
if( s721.size() == 3 ) {
if( s721[0] == s7::s464 )
am = s531;
else if( s721[0] == s7::s466 )
am = s533;
else if( s721[0] != s7::s465 )
throw new s17( L"invalid access mode name: " + it->first );
s688 = s721[2];}
it->second->s301( s688 );}
s279* ob = new s279( *it->second, s307, pc, s307, am, cl, cnl, al );
s690.s565( ob->s306(), ob );}}
void s269::s214( const wstring& s692 ){
s759 s676;
s270* s213 = new s270();
wstring s194 = s4::s789( s692 );
if( s814.size() ) {
wstring file = s194.substr( s194.rfind( L"/" ) + 1 );
s194 = s754( s814, s194.substr(0, s194.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s35( s194 );
if( isf == 2 ) {
s4::s63( s194 );
s194 += s7::s476;
if( s814.empty() )
s814 = s692;}
else if( isf == 1 ) {
if( s814.empty() )
s814 = s194.substr( 0, s194.find_last_of( L"\\/" ) );
}
else
throw new s17( L"cannot find file or directory: " + s692,
(uint32_t)s17::s18::s24 );
s4::s63( s814 );
s696( s194, s676 );
size_t s850 = s204.size();
vector<s9<s147>> s693;
for( size_t n = 0; n < s676.s694.size(); n++ ) {
s693.clear();
wstring s695 = s676.s694[n];
if( s695[0] != L'/' && s695[1] != L':' )
s695 = s814 + s695;
s204.push_back( s695 );}
for( size_t n = s850; n < s204.size(); ++n ) {
s693.clear();
s1037 s1160 = new s1034( s204[n] );
s1160->read( s693, s7::s434 );
for( size_t m = 0; m < s693.size(); m++ ) {
if( s270::s309( *s693[m], s7::s481 ) == s7::s472 )
s218( s204[n], *s693[m] );
else if( s270::s302( *s693[m], s7::s470 ) == s7::s470 ) {
s693[m]->s163( L"@sourceFile", new s6::s145( L"\"" 
+ s204[n] + 
L"\"" 
), s147::s149::s151 );
s213->s296( *s693[m] );}}}
s212( *s213 );
if( s1116.s1022() )
throw s1023( s1023::s18::s1098 );
s270::s282& s738 = s213->s300();
for( auto it : s738 ) 
s737.s293( it.second );
if( s205.empty() )
s205 = s676.entry;}
void s269::s212( s270& s213 ){
s501 s690;
s652 m1;
s650 s697;
s651 s698;
vector<wstring> s699;
s708( this, s213, s690, s698, s697, m1 );
size_t s700 = s697.size();
while( s699.size() < s700 ) {
size_t s701 = s697.size();
for( size_t n = 0; n < s697.size(); ++n ) {
if( s697[n].second.empty() ||
std::find( s699.begin(), s699.end(), s697[n].second )
!= s699.end() ) {
s699.push_back( s697[n].first );
s697.erase( s697.begin() + n-- );
continue;}}
if( s701 == s697.size() )
throw new s17( L"unresolved parent class: " + s697[0].second );}
for( size_t n = 0; n < s699.size(); ++n )
if( s208.s160( s699[n] ) )
throw new s17( L"class name already exists: " + s699[n] );
for( size_t n = 0; n < s699.size(); ++n )
s208.s224( s698[s699[n]], s698[s699[n]]->s369() );
s656.s296( s690 );
for( size_t n = 0; n < s699.size(); ++n ) {
s506 ob = (s279*)s208.get( s699[n], false );
if( ob )
ob->s158( *m1[s699[n]] );}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s279* ob = (s279*)s690.get( it->first, false );
if( ob && ob->s514() == s498 )
ob->s158( *it->second );}
s690.s520( this, false );}
void s269::s216( s147& obj ){
s270 s213;
s213.s296( obj );
s212( s213 );}
s502* s269::run( const vector<wstring>& s724 ){
if( s205.empty() )
s205 = s7::s475 + L"::" + s7::s474;
if( !s724.empty() ) {
wstring  s704, s703;
s702( s205, s703, s704 );
s279* mod = (s279*)s656.get( s703 );
for( size_t n = 0; n < s724.size(); ++n )
mod->s922( L"@" + std::to_wstring( n ), new s375( this, s724[n] ) );
mod->s922( s7::s890, new s361( this, (int)s724.size() ) );}
vector<wstring> l;
return callFunc( s205, l );}
s502* s269::callFunc( const wstring& s, vector<wstring>& l ){
wstring  s704, s703;
s702( s, s703, s704 );
s279* mod = (s279*)s656.get( s703 );
s507 s705 = (s616*)mod->s671( s704, L"::" );
vector<s504> s281;
for( size_t n = 0; n < l.size(); n++ ) {
s1036 ast_ = new s270( l[n], NULL );
s509 cs = s616::s1237( *ast_, this, mod, mod->s305() );
s281.push_back( cs );}
s705->s621( s281 );
s503* pr = s705->s516();
try {
s1486 = false;
if( !pr )
s705->s520( L"::", true );
else
s705->s622( L"::" );}
catch( s17* e ) {
throw e->s31( L"\nwhile linking '" + s705->s306() + L"' function " );}
s1486 = true;
s502* s718 = s705->s517();
s1486 = false;
return s718;}
s507 s269::getProc( const std::wstring& s ){
wstring  s704, s703;
s702( s, s703, s704 );
s279* mod = (s279*)s656.get( s703 );
s507 s705 = (s616*)mod->s671( s704, L"::" );
s505 pr = s705->s516();
if( !pr )
s705->s520( mod->s305(), true );
return s705;}
void s269::s206( const std::wstring& s692 ){
wstring s194 = s692;
wstring s691;
int isf = s3::s35( s692 );
if( isf == 2 ) {
s4::s63( s194 );
s194 += s7::s476;
s691 = s692;}
else if( isf == 1 )
s691 = s194.substr( 0, s194.find_last_of( L"\\/" ) );
else
throw new s17( L"cannot find file or directory: " + s692, 
(uint32_t)s17::s18::s24 );
s4::s63( s691 );
vector<s9<s147>> s693;
s1037 s1160 = new s1034( s194 );
s1160->read( s693, s7::s434 );
s759 s676;
for( size_t n = 0; n < s693.size(); n++ ) {
wstring s688 = s270::s309( *s693[n], s7::s481 );
if( s688 == s7::s469 ) {
s207( *s693[n], s676 );
break;}}
s205 = s676.entry;
if( s676.s694.empty() )
s676.s694.push_back( s194 );
for( size_t n = 0; n < s676.s694.size(); n++ ) {
s693.clear();
wstring s695 = s676.s694[n];
if( s695[0] != L'/' && s695[1] != L':' )
s695 = s691 + s695;
s1037 s1160 = new s1034( s695 );
s1160->read( s693, s7::s434 );
for( size_t m = 0; m < s693.size(); m++ )
if( s270::s302( *s693[m], s7::s470 ) == s7::s470 )
s737.s296( *s693[m] );}}
void s269::s207( const s6::s147& obj, s759& s157 ){
const vector<s146>& s166 = obj.s162( s7::s483 )->s171();
for( size_t n = 0; n < s166.size(); n++ )
s157.s694.push_back( s166[n]->s173() );
if( obj.s160( s7::s482 ) )
s157.entry = obj.s162( s7::s482 )->s173();}
void s269::s224( s502* p, const wstring& s362 ){
s208.s224( p, s362 );}
bool s269::s580( const wstring& sym_, s387* ref, const wstring& s347 ) const{
if( !s279::s580( sym_, ref, s347 ) ) {
if( sym_[0] == L'@' && sym_.substr(1).find_first_not_of(L"0123456789") == string::npos ) {
ref->s395( s669( s7::s897 ), s381 );
ref->s398( (s502*)this );
return true;}
return false;}
return true;}
bool s269::s227( const std::wstring& s, const s502* s1130 ) const{
s1130 = NULL;
s210::const_iterator it = s211.find( s );
if( it != end( s211 ) ) {
s1130 = it->second;
return true;}
return false;}
void s269::s225( const wstring& s78, const wstring& s347,
vector<wstring>& s157 ){
size_t pl = s78.rfind( L"::" );
s279* mod = NULL;
bool bCl = false;
if( s78.find( L"()" ) == s78.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s707 = s78.substr( 0, pl );
wstring sym = s78.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );}
mod = (s279*)s656.get( s707 );
if( !mod->s672( sym, s347 ) )
throw new s17( L"Symbol '" + s78 + L"' cannot be imported by '" +
s347 + L"'");
s157.push_back( sym );}
else {
if( bCl ) {
wstring sym = s78.substr( 0, s78.size() - 2 );
s208.get( sym );
s157.push_back( sym );}
else {
mod = (s279*) s656.get( s78 );
mod->s668( s347, s157 );}}}
s616* s269::s219( int s1632, 
std::vector<s278*>& s741, s502* s613, s616* s220, const s270* s737 ){
s616* s718 = NULL;
if( s1632 == s1611 )
s718 = new s634( this, s613, s220, s741, s737 );
else if( s1632 == s1625 )
s718 = new s630( this, s613, s220, s741, s737 );
else if( s1632 == s1605 )
s718 = new s633( this, s613, s220, s741, s737 );
else if( s1632 == s1606 )
s718 = new s1579( this, s613, s220, s741, s737 );
else if( s1632 == s1624 )
s718 = new s312( this, s613, s220, s741, s737 );
else if( s1632 == s1615 )
s718 = new s632( this, s613, s220, s741, s737 );
else if( s1632 == s1619 )
s718 = new s635( this, s613, s220, s741, s737 );
else if( s1632 == s1608 )
s718 = new s636( this, s613, s220, s741, s737 );
else if( s1632 == s1613 )
s718 = new s907( this, s613, s220, s741, s737 );
else if( s1632 == s1616 )
s718 = new s908( this, s613, s220, s741, s737 );
else if( s1632 == s1621 )
s718 = new s638( this, s613, s220, s741, s737 );
else if( s1632 == s1620 )
s718 = new s637( this, s613, s220, s741, s737 );
else if( s1632 == s1607 )
s718 = new s639( this, s613, s220, s741, s737 );
else if( s1632 == s1610 )
s718 = new s641( this, s613, s220, s741, s737 );
else if( s1632 == s1617 )
s718 = new s642( this, s613, s220, s741, s737 );
else if( s1632 == s1614 )
s718 = new s849( this, s613, s220, s741, s737 );
else if( s1632 == s1612 )
s718 = new s824( this, s613, s220, s741, s737 );
else if( s1632 == s1623 )
s718 = new s1474( this, s613, s220, s741, s737 );
else if( s1632 == s1622 )
s718 = new s842( this, s613, s220, s741, s737 );
else if( s1632 == s1618 ) {
s718 = new s874( this, s613, s220, s741, s737 );}
else if( s1632 == s1609 )
s718 = new s984( this, s613, s220, s741, s737 );
return s718;}
s278*
s269::s228( const wstring& s78, const wstring& s519, bool s544 /*= true*/ )
{
size_t pl = s78.rfind( L"::" );
s504 s718;
if( pl == string::npos ) {
s718 = (s278*)s208.get( s78, s544 );
if( !s718 ) {
s279* exp = (s279*)s208.get( s7::s471, false );
if( exp )
s718 = exp->s671( s78, s519, s544 );}
return s718;}
wstring s707 = s78.substr( 0, pl );
wstring sym = s78.substr( pl + 2 );
return ((s279*)s208.get( s707 ))->s671( sym, s519 );	}
void* s269::s229( const std::wstring& s285 ){
s351* s718;
s279* exp = (s279*) s656.get( s7::s471, false );
if( exp )
s718 = (s351*)exp->s671( s285, L"", true );
else
throw new s17( L"no such export variable: " + s285 );
void * pv = s718->addr();
return pv;}
void s269::s1520( const wstring& s703 ){
s656.s566( s703 );}
void s269::s311( std::wostream* pd, int s202 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s202 ) << s285 << L" : " << L"Assembly" << endl;
s208.s311( pd, s202 + s435 );
s656.s311( pd, s202 + s435 );}
map<int, s269*> handles;
HPROG createAssembly(){
static int s717 = 0;
s269* p = new s269();
handles[++s717] = p;
p->s520( false );
return s717;}
void loadProgram( HPROG handle, const wstring& s194 ){
s269* p = handles[handle];
p->s214( s194 );}
TDType* getProc( HPROG handle, const std::wstring& s626 ){
s269* p = handles[handle];
return (TDType*)p->getProc( s626 );}
void s216( HPROG handle, s6::s147& obj ){
s269* p = handles[handle];
p->s216( obj );}
TDType* run( HPROG handle, const vector<wstring>& s724 ){
return handles[handle]->run( s724 );}
void* callFunc( HPROG handle, const std::wstring& s79, vector<wstring>& l ){
s269* p = handles[handle];
return p->callFunc( s79, l );}
void evaluateExpression( const std::wstring& s79 ){}
void* s229( HPROG handle, const std::wstring& s285 ){
s269* p = handles[handle];
return p->s229( s285 );}
void* execute( TDType* p ){
return p->s517().s16<s351*>()->addr();}
void importSymbol( HPROG handle, const std::wstring& s1230, const std::wstring& symName,
const std::wstring& s347 ){
s269* p = handles[handle];
s279* ob = (s279*)p->s671( s1230, s347 );
ob->s579( symName, s347 );}
void importFile( HPROG handle, const std::wstring& s1230, const std::wstring& s45,
const std::wstring& s347 ){
vector<s1::s9<s6::s147>> s693;
s6::s1034 s1160( s45 );
s1160.read( s693, s7::s434 );
s269* p = handles[handle];
p->s214( s45 );
s279* ob = (s279*)p->s671( s1230, s347 );
for( size_t n = 0; n < s693.size(); n++ ) {
wstring s688 = s270::s309( *s693[n], s7::s481 );
ob->s579( s688, s347 );}}
HPROG initShell( const std::wstring& s1230, const std::wstring& modText ){
s1::s9<s6::s147> ob = new s6::s147(NULL);
size_t pos = 0;
s6::s1034 s1160( L"" );
s1160.s175( modText, pos, ob );
ob->s163( L"name", new s6::s145( s1230 ) );
HPROG prog = createAssembly();
s216( prog, *ob );
return prog;}
} // namespace transd
