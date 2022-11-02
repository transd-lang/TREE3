
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
using namespace s2;
using namespace s1;
using namespace s5;
using namespace s4;
namespace s6{
wstring s184 = L"-.0123456789";
wstring s1526 = L"0123456789";
wstring s1527 = L".0123456789";
wstring s185 = L" ,]}\t\r\n";
wstring s2132 = L"-_[]@";
s1680 s1742;
thread_local std::list<bool> s1754;
void s1683( const wstring& dd, const wstring& fs, bool ab, bool rb, bool sb ){
s1742 = s1680( dd, fs, ab, rb, sb );}
void s1683( const s1680& cnf ){
s1742 = cnf;}
void s937::s169( const wstring& s77, size_t& pos, s9<s142> ob ){
size_t s74, s75;
s54( s77, pos, L'{', L'}', s74, s75, true );
if( s74 == string::npos )
return;
s1051 = s74 - 1;
wstring sob = s77.substr( s74, s75 - s74 + 1 );
pos = s75 + 1;
try {
s1754.push_back( s1745.s150 );
ob->s153( sob, s1745 );
s1754.pop_back();}
catch( s16* e ) {
s1754.pop_back();
e->s30( L"failed to read the object: " + sob.substr( 0, 50 ) + L"...");
throw e;}}
bool s937::s997( wstring& s, size_t s68, size_t s678, size_t& line ) const{
line = 0;
s = L"";
auto itst = s1106.lower_bound( s68 );
auto iten = s1106.lower_bound( s678 );
if( itst == end(s1106) || iten == end(s1106) )
return false;
line = itst->second;
s = s1105[itst->second-1];
if( iten != itst )
s += L"\n ...\n" + s1105[iten->second-1];
return true;}
void s186( wstring& s77 ){
wregex s187(
LR"regex(\n\r?\/\/.*?\n\r?)regex"
);
wsmatch sm;
wstring::const_iterator itst = s77.begin();
wstring::const_iterator iten = s77.end();
while( std::regex_search( itst, iten, sm, s187 ) ) {
s77.erase( sm.position(), sm.length() - 
(sm[0].str()[sm.length()-1]=='\r' ? 2 : 1 ) );
itst = s77.begin();
iten = s77.end();}}
s937::s937( const std::wstring& file, bool s1621, const s1680& s1744 )
: s1745( s1744 ){
if( file.empty() )
return;
size_t pl = file.find_first_not_of( s4::s48 );
if( pl == string::npos )
return;
if( file[pl] == L'{' || s1621 == false )
s1104 = file;
else
s193 = file;}
void s937::read( vector<s9<s142>>& s152, const wstring& s189 ){
size_t pos = 0;
if( s193.size() ) {
std::ifstream fs( TOFS( s193 ));
if( !fs.good() )
throw runtime_error( "Failed to read TSD file: " + U8( s193 ));
string s190( (std::istreambuf_iterator<char>( fs )), std::istreambuf_iterator<char>());
s1104 = conv.from_bytes( s190 );
s4::s81( s1104, s1105, s1106 );
if( s189.size() ) {
pos = s1104.find( s189 );
if( pos == string::npos )
throw new s16( s189 + L" directive not found in the source file." );
pos += s189.size() + 1;
if( s1104.size() > 13 && s1104[14] == '\r' )
++pos;}}
size_t s191 = pos;
wstring s277;
bool s192 = false;
while( ( pos = s1104.find( L'{', pos ) ) != string::npos ) {
size_t pl = s1104.rfind( '}', pos );
size_t subl = pos - pl - 1;
if( string::npos == pl ) {
pl = s191; subl = pos - s191;}
else
pl += 1;
wstring s1 = s52( s1104.substr( pl, /*pos - pl - 1*/subl ), s48 );
if( s1.size() ) {
if( s1[s1.size()-1] != L':' )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
if( s1.size() == 1 )
s192 = true;
else
s277 = s52( s1, s48 + L":" );}
if( s277.empty() ) {
size_t pl1 = s1104.rfind( '\n', pl );
if( pl1 < pl - 1 ) {
wstring s1 = s52( s1104.substr( pl1, pl ), s48 );
if( s1.size() ) {
if( ( !s192 && s1[s1.size() - 1] != L':' ) ||
( s192 && s1[s1.size() - 1] == L':' ) ||
(!s192 && s1.size() == 1 ) )
throw new s16( L"Malformed syntax: " + s1.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );
s277 = s52( s1, s48 + L":" );}}}
if( s87.find( s277[0] ) != string::npos ) {
if( s277[0] != s277[s277.size()-1] )
throw new s16( L"Malformed block name: " + s277.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
else {
if(	iswdigit( s277[0] ) )
throw new s16( L"wrong unquoted syntax: " + s277.substr( 0, 20 ) + L"...",
(uint32_t)s16::s17::s20 );}
s9<s142> ob = new s142( this );
try {
s1754.push_back( s1745.s150 );
s169( s1104, pos, ob );
s1754.pop_back();}
catch( s16* e ) {
s1754.pop_back();
e->s30( L"during reading the file: " + s193 );
throw e;}
if( s277.size() )
ob->s158( L"@name", new s140( s277 ), s142::s144::s146 );
s277 = L"";
s192 = false;
s152.push_back( ob );}}
void s170( const wstring& s193, const vector<s1::s9<s142>>& s194 ){
std::ofstream fs( TOFS( s193 ), ios::out | ios::trunc | ios::binary );
if( !fs.good() )
throw runtime_error( "Reading state file failed: " + U8( s193 ) );
for( auto ob : s194 ) {
basic_stringstream<wchar_t> ss;
ob->s154( &ss );
string s = U8( ss.str() );
s += "\n\n";
fs.write( s.c_str(), s.size() );}}
void s171( const wstring& s77, size_t& pos, wchar_t quote, wstring& s152, bool s150 = false ){
size_t s74, s75;
s55( s77, pos, quote, s74, s75 );
if( s75 != string::npos ) {
pos = s75 + 1;
if( !s1754.empty() && s1754.back() )
s152 = s52( s77.substr( s74, s75 - s74 + 1), s48 ); 
else
s152 = s52( s77.substr( s74+1, s75 - s74 - 1 ), s48 ); }
else
pos = string::npos;}
void s172( wostream* pd, const wstring& s ){
wchar_t q = L'\"';
if( s87.find( s[0] ) != string::npos )
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
void s173( const wstring& s77, size_t& pos, wstring& s152 ){
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"unrecognized unquoted syntax: " + s77.substr(pos, 20), 
(uint32_t)s16::s17::s20 );
size_t s195 = pos + 1;
while( std::isgraph<wchar_t>( s77[s195], locloc ) &&
s77[s195] != L':' && s77[s195] != L',' )
++s195;
s152 = s52( s77.substr( pos, s195 - pos ), s48 );
pos = s195;}
void s174( const wstring& s77, size_t& pos, wchar_t s1197, wchar_t s1239, wstring& s152 ){
size_t s74, s75;
s54( s77, pos, s1197, s1239, s74, s75, true );
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
s130 s175( const wstring& s77, size_t& pos, wstring& s152, const s1680& s1744 ){
if( s77[pos] == s1744.s1682[0] && s1744.s1729) {
s152 = L"";
return s131;}
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"empty element or unrecognized unquoted syntax: " + s77.substr( pos, 20 ),
(uint32_t)s16::s17::s20 );
size_t s195 = pos;
int shift = 0;
if( s77[pos] == L'(' && s1744.s1684) {
s174( s77, s195, L'(', L')', s152 );
if( s195 == s77.size() - 1 )
shift = 1;}
else {
s195 = pos + 1;
while( std::isgraph<wchar_t>( s77[s195], locloc ) &&
s77[s195] != L':' && s77[s195] != L',' ) {
if( s77[s195] == L'<'  && s1744.s1685 ) {
s174( s77, s195, L'<', L'>', s152 );}
else if( s77[s195] == L'(' && s1744.s1684 ) {
s174( s77, s195, L'(', L')', s152 );
if( s195 == s77.size() - 1 )
shift = 1;
break;}
else
++s195;}}
s152 = s52( s77.substr( pos, s195 - pos + shift ), s48 );
pos = s195;
return s133;}
void s176( wostream* pd, const wstring& s ){
if( ( !std::isalpha<wchar_t>( s[0], locloc ) && s[0] != L'_' ) ||
s[s.size()-1] == L'"' )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
for( size_t n = 0; n < s.size(); ++n ) 
if( !std::isgraph<wchar_t>( s[n], locloc ) )
throw new s16( L"wrong unquoted syntax: " + s.substr(0, 20),
(uint32_t)s16::s17::s20 );
*pd << s;}
void s177( const s937* pf, const wstring& s77, vector<s9<s140>>& s152, 
const s1680& s1744 ){
size_t s68 = s77.find_first_not_of( s48 );
s1754.push_back( s1744.s1717 );
while( true ) {
s152.push_back( s9<s140>(new s140( pf, s77, s68, s1744 ) ) );
s4::s993( s77, s68, s1744.s1682 );
if( s68 == string::npos )
break;
++s68;}
s1754.pop_back();}
void s177( const s937* pf, const wstring& s77, size_t& pos,
vector<s9<s140>>& s152, const s1680& s1744 ){
size_t s74, s75, s68 = 0;
s54( s77, pos, L'[', L']', s74, s75, true );
pos = s75 + 1;
wstring ar = s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 );
if( ar.empty() )
return;
s1754.push_back( s1744.s1717 );
while( true ) {
s152.push_back( s9<s140>(new s140( pf, ar, s68, s1744 ) ) );
s4::s993( ar, s68, s1744.s1682 );
if( s68 == string::npos )
break;
++s68;}
s1754.pop_back();}
void s178( wostream* pd, const vector<s9<s140>>& v, bool s150=false ){
*pd << L'[';
for( size_t n = 0; n < v.size(); ++n ) {
v[n]->s154( pd, s150 );
if( n != v.size() - 1 )
*pd << L',';}
*pd << L']';}
void s179( const wstring& s77, size_t& pos, wstring& s152, bool s150 = false ){
size_t pl = s77.find_first_not_of( L", \n\r\t", pos );
if( s87.find( s77[pl] ) != string::npos ) 
s171( s77, pos, s77[pl], s152, s150 );
else {
if( !std::isgraph<wchar_t>( s77[pos], locloc ) ||
s77[pos] == L':' || s77[pos] == L',' )
throw new s16( L"unrecognized name syntax: " + s77.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
size_t s195 = pos + 1;
wchar_t c = s77[s195];
while( c != L':' && c != L',' ) {
if( !std::isalnum<wchar_t>( c, locloc ) &&	!std::isspace<wchar_t>( c, locloc ) && 
s2132.find( c ) == string::npos )
throw new s16( L"unrecognized name syntax: " + s77.substr( pos, 20 ) +
L"...",	(uint32_t)s16::s17::s20 );
c = s77[++s195];}
s152 = s52( s77.substr( pos, s195 - pos ), s48 );
pos = s195;}}
void s180( wostream* pd, const wstring& s, bool s150=false ){
bool space = false;
for( size_t n = 0; n < s.size(); ++n )
if( !std::isgraph<wchar_t>( s[n], locloc ) ) {
space = true;
break;}
if( !space && !s150 && s87.find( s[0] ) == string::npos )
s176( pd, s );
else
s172( pd, s );}
s130 s181( const wstring& s77, size_t& pos, double& s152 ){
s130 s680 = s139;
size_t pl = s77.find_first_not_of( L"-0123456789.", pos );
size_t pl1 = s77.find( L".", pl );
if( pl1 < pl )
s680 = s135;
if( pl == string::npos )
s152 = stod( s77.substr( pos ) );
else
s152 = stod( s77.substr( pos, pl - pos ) );
pos = pl;
return s680;}
s130 s1538( const wstring& s77, size_t& pos, double& s152, const s1680& s1744 ){
const wchar_t* ps = s77.c_str();
size_t sz = s77.size();
size_t st = pos;
if( ps[st] == L'-' ) {
if( sz == st+1 || s1527.find( ps[st+1] ) == string::npos )
return s131;
st += 1;}
if( ( ps[st] == L'0' && sz > st + 1 && s1526.find( ps[st+1] ) != string::npos ) ||
( s1526.find( ps[st] ) == string::npos ) )
return s131;
size_t s679 = st;
bool pt = false;
while( s679 < sz ) {
if( ps[s679] == s1744.s1681[0] ) {
if( pt ) return s131;
pt = true;
s679++;}
else if( s1526.find( ps[s679] ) != string::npos )
s679++;
else if( (s48 + s1744.s1682 + L"}").find( ps[s679] ) != string::npos  )
break;
else
return s131;}
s130 s680 = s139;
if( pt )
s680 = s135;
if( s679 == sz )
s152 = stod( s77.substr( pos ) );
else
s152 = stod( s77.substr( pos, s679 - pos ) );
pos = s679;
return s680;}
bool s182( const wstring& s77, size_t& pos, bool& s152 ){
size_t pl = 0;
if( s77.find( L"true", pos, 4 ) == pos )
pl = 4;
else if( s77.find( L"false", pos, 5 ) == pos )
pl = 5;
if( pl ) {
if( s185.find( s77[pos+pl] ) != string::npos ) {
pos += pl;
s152 = (pl == 4);
return true;}}
return false;}
bool s183( const wstring& s77, size_t& pos ){
if( s77.find( L"null", pos, 4 ) == pos ) {
if( s185.find( s77[pos+4] ) != string::npos ) {
pos += 4;
return true;}}
return false;}
s140::s140( const s937* pf, const wstring& s77, size_t& pos, const s1680& s1744 )
: s197( s131 ), obj( pf ), s1074( pos + (pf ? pf->s941():0), 0 ), s1073( (s937*)pf ){
size_t s68 = s77.find_first_not_of( L" \n\r\t", pos );
if( s68 == string::npos ) {
if( s1744.s1729 )
s197 = s131;
else {
s16* s960 = new s16(wstring( 28, L' ' ) + L"|^|" );
s960->s30( L"empty array item: " + s77.substr( pos - 10, 20 ) );
throw s960;}}
else if( s77[s68] == L'{' ) {
size_t s74, s75;
s54( s77, s68, L'{', L'}', s74, s75, true );
pos = s75+1;
obj.s153( s52( s77.substr( s74 + 1, s75 - s74 - 1 ), s48 ), s1744 );
s197 = s132;}
else {
pos = s68;
if ( s87.find( s77[pos] ) != string::npos ) {
s171( s77, pos, s77[pos], str, s1744.s150 );
s197 = s138;}
else if ( s77[pos] == L'[' ) {
s177( (s937*)s1073, s77, pos, s161, s1744 ); 
s197 = s134;}
else {
s197 = s1538( s77, pos, s162, s1744 );
if( s197 != s131 )
(void)0;
else if( s182( s77, pos, b ) )
s197 = s136;
else if( s183( s77, pos ) )
s197 = s137;
else
s197 = s175( s77, pos, str, s1744 );;}}
s1074.second = pf ? pos - 1 + pf->s941() : 0;}
s140::s140( double d, s130 v ) 
: s197( v ), obj( NULL ), s162( d ) {
assert( v == s135 || v == s139 );}
bool s140::s1001( wstring& f, std::wstring& s, size_t& line  ) const{
if( !s1074.first || s1073.s13() )
return false;
f = s1073->Path();
s1073->s997( s, s1074.first, s1074.second, line );
return true;}
const s142& s140::s165() const{
if( s197 == s132 )
return obj;
throw new s16( L"NQJ value: wrong variant" );}
const std::vector<s141>& s140::s166() const{
if( s197 == s134 )
return s161;
throw new s16( L"NQJ value: wrong variant" );}
double s140::s167() const{
if( s197 == s135 )
return s162;
throw new s16( L"NQJ value: wrong variant" );}
int s140::s56() const{
if( s197 == s139 )
return (int)s162;
throw new s16( L"NQJ value: wrong variant" );}
bool s140::s721() const{
if( s197 == s136 )
return b;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s140::s168() const{
if( s197 == s133 || s197 == s138 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
const std::wstring& s140::s858() const{
if( s197 == s138 )
return str;
throw new s16( L"NQJ value: wrong variant" );}
std::wstring s140::s850() const{
if( s197 == s138 )
return str.substr( 1, str.size() - 2 );
throw new s16( L"NQJ value: wrong variant" );}
void s142::s153( const wstring& s77, const s1680& s1744 ){
s143.clear();
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
s179( s77, s68, s76, s1744.s150 );
size_t pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl == string::npos || s77[pl] != L':' )
throw new s16( L"unrecognized nqj syntax: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
s68 = pl + 1;
s143.insert( make_pair( s76, new s140( src, s77, s68, s1744 ) ) );
pl = s77.find_first_not_of( L" \n\r\t", s68 );
if( pl != string::npos && s185.find( s77[pl] ) == string::npos ) 
throw new s16( L"wrong nqj syntax: missed separator or closing brace: " + s77.substr(s68, 50), 
(uint32_t)s16::s17::s20 );
if( pl != string::npos )
pl = s77.find_first_not_of( L" \n\r\t", pl+1 );
if( pl == string::npos )
break;
s68 = pl;}}
bool s142::operator==( const s142& r )  const{
bool s680 = true;
for( auto it = s143.begin(); it != s143.end(); ++it ) {
auto it1 = r.s143.find( it->first );
if( it1 == r.s143.end() || !( *( it->second ) == *( it->second ) ) ) {
s680 = false;
break;}}
return s680;}
void s142::s154( wostream* pd, bool s150 ) const{
*pd << L"{\n";
for( auto it = s143.begin(); it != s143.end(); ++it ) {
if( it != s143.begin() )
*pd << L",\n";
s180( pd, it->first, s150 );
*pd << L" : ";
it->second->s154( pd );}
*pd << L"\n}";}
void s140::s154( wostream* pd, bool s150 ) const{
if( s197 == s132 )
obj.s154( pd, s150 );
else if( s197 == s134 )
s178( pd, s161, s150 );
else if( s197 == s133 )
s180( pd, str, s150 );
else if( s197 == s138 )
s180( pd, str, true );
else if( s197 == s135 )
*pd << to_wstring( s162 );
else if( s197 == s139 )
*pd << to_wstring( (int)s162 );
else if( s197 == s136 )
*pd << ( b ? L"true" : L"false" );
else if( s197 == s137 )
*pd << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool s142::s155( const wstring& s151 ) const{
if( s143.find( s151 ) != s143.end() )
return true;
return false;}
void s142::s156( const wstring& s151, vector<s9<s140>>& s152 ) const{
auto i = s143.equal_range( s151 );
if( i.first == i.second )
return;
for( auto it = i.first; it != i.second; ++it )
s152.push_back( it->second );}
const s141 s142::s157( const wstring& s151 ) const{
if( s143.count( s151 ) > 1 )
throw new s16( L"multiple values: " + s151, (uint32_t)s148 );
auto s680 = s143.find( s151 );
return s680->second;}
void s142::s158( const std::wstring& s76, s141 s346, s144 ap ){
if( s143.find( s76 ) != s143.end() ) {
if( ap == s145 )
throw new s16( L"Field already exists: " + s76, (uint32_t)s16::s17::s21 );
else if( ap == s147 )
return;
else if( ap == s146 )
s143.erase( s76 );}
s143.insert( make_pair( s76, s346 ) );}
void s142::s1618( const std::wstring& s76 ){
if( s143.find( s76 ) == s143.end() )
throw new s16( L"Attribute doesn't exist: " + s76, (uint32_t)s16::s17::s21 );
s143.erase( s76 );}
void s142::s159( vector<pair<wstring, s9<s140>>>& s152 ) const{
for( auto it = s143.begin(); it != s143.end(); ++it ) 
s152.push_back( *it );}
void s142::s160( wostream* pd, int s196 ) const{
for( auto it = s143.begin(); it != s143.end(); ++it ) {
*pd << FILL(s196) << it->first << " : " << endl;
it->second->s160( pd, s196 + 2 );}}
void s140::s160( wostream* pd, int s196 ) const{
if( s197 == s132 )
obj.s160( pd, s196 + 2 );
else if( s197 == s134 ) {
for( size_t n = 0; n < s161.size(); ++n ) {
s161[n]->s160( pd, s196 );
if( n < s161.size() - 1 )
*pd << endl;}}
else if( s197 == s133 )
*pd << FILL( s196 ) << str << endl;
else if( s197 == s135 )
*pd << FILL( s196 ) << s162 << endl;
else if( s197 == s139 )
*pd << FILL( s196 ) << s162 << endl;
else if( s197 == s136 )
*pd << FILL( s196 ) << b << endl;
else if( s197 == s137 )
*pd << FILL( s196 ) << L"null" << endl;
else
throw new s16( L"unknown variant" );}
bool operator==( const std::vector<s9<s140>>& l,
const std::vector<s9<s140>>& r ){
if( l.size() == r.size() ) {
for( size_t n = 0; n < l.size(); ++n )
if( !(*( l[n] ) == *( r[n] ) ) )
return false;
return true;}
return false;}
s130 s1694::s1538( const std::wstring& s77, size_t& pos, double& s152 ){
return s6::s1538( s77, pos, s152, conf );}
} // namespace s6
namespace s2 {
uint32_t s16::s27;
std::vector<std::wstring> s988 = {
L"no error",
L"general error",
L"syntax error",
L"object already exists",
L"operation failed",
L"object doesn't exist",
L"index is out of range",
L"method is not implemented"
};
void s1111(){
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
bool s36( const wstring& s209 ){
try {
s34( s209 );}
catch( s16& ) {
return false;}
return true;}
bool s35( const wstring& s209 ){
try {
if( s34( s209 ) != 1 )
throw new s16( L"Cannot find data file: " + s209,
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
wstring s680 = s37();
size_t pl = s680.rfind( '/' );
if( pl == string::npos )
s680 = L"";
else
s680 = s680.substr( 0, pl );
return s680;}
wstring s1868(){
char buf[2000];
memset( buf, 0, 2000 );
getcwd( buf, 2000 );
return wstring( conv.from_bytes( buf ) );}
bool s31( const wstring& s46, const wstring& s521, wstring& s152 ){
struct dirent *entry;
DIR *dp;
wregex rg( s521 );
bool s680 = false;
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s689 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s689,
(uint32_t)s16::s17::s22 );}
while( ( entry = readdir( dp ) ) ) {
if( regex_match( conv.from_bytes( entry->d_name ), rg ) ) {
s152 = s46 + conv.from_bytes( entry->d_name );
s680 = true;
break;}}
closedir( dp );
return s680;}
void s32( const wstring& s46, const wstring& s521, vector<wstring>& s40, vector<wstring>& s41 ){
struct dirent *entry;
DIR *dp;
wregex rg( s521 );
dp = opendir( conv.to_bytes( s46.c_str() ).c_str() );
if( dp == NULL ) {
wstring s689 = conv.from_bytes( strerror( errno ) );
throw new s16( L"cannot open directory: " + s46 + L";\nerror: " + s689,
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
bool s717( const std::wstring& f ){
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
wstring s1868(){
wchar_t buf[2000];
memset( buf, 0, 4000 );
_wgetcwd( buf, 2000 );
return wstring( buf );}
bool s31( const wstring& _dir, const wstring& s521, wstring& s152 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s521.c_str() );
bool s680 = false;
wstring s46 = _dir;
if( s46.back() != L'/' && s46.back() != L'\\' )
s46 += L'\\';
if( ( s47 = FindFirstFileW( ( s46 + L"*" ).c_str(), &s43 ) ) == INVALID_HANDLE_VALUE )
throw runtime_error( "no such directory" );
while( FindNextFileW( s47, &s43 ) ) {
s44 = s43.cFileName;
s45 = s46 + s44;
if( regex_match( s44, rg ) ) {
s152 = s45;
s680 = true;
break;}}
return s680;}
void s32( const wstring& _dir, const wstring& s521, vector<wstring>& s40, vector<wstring>& s41 ){
HANDLE s47;
WIN32_FIND_DATAW s43;
wstring s44, s45;
wregex rg( s521.c_str() );
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
bool s717( const std::wstring& f ){
if( f.size() && f[1] == ':' )
return true;
return false;}
} // namespace s3
#endif // WIN32
namespace s4 {
wstring s87 = L"\"`'";
wstring s48 = L"\n\r\t ";
string s49 = "\n\r\t ";
wstring s50 = L"";
wstring digits = L"0123456789";
void s54( const wstring& s, size_t s65, wchar_t left, wchar_t right,
size_t& start, size_t& end, bool s879/*=false*/ )
{
end = string::npos;
start = string::npos;
int s66 = 0;
wchar_t s869 = 0;
bool esc = false;
for( size_t n = s65; n < s.size(); ++n ) {
wchar_t c = s[n];
if( !s869 || !s879 ) {
if( c == left ) {
if( start == string::npos )
start = n;
s66++;}
else if( c == right ) {
if( start == string::npos )
return; // s823
if( --s66 == 0 ) {
end = n;
return;}}
else if( s879 && ( c == L'\'' || c == L'\"' ) ) {
s869 = c;}}
else if( s869 && c == s869 && !esc ) {
s869 = 0;}
else if( c == L'\\' ) {
esc = !esc;}
else
esc = false;}}
void s855( const wstring& s, size_t s65, wchar_t left, wchar_t right,
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
bool s847 = false;
for( size_t n = start + 1; n < s.size(); ++n ) {
if( s[n] == L'\\' /*&& n && s[n-1] == L'\\'*/ )
s847 = !s847;
if( s[n] == c && !s847 ) {
end = n;
return;}
if( s[n] != L'\\' )
s847 = false;}}
void s993( const std::wstring& s, size_t& s65, const std::wstring& s1866 ){
size_t s1864 = s65, s1865;
wstring s1331 = s1866 + L"\"";
s65 = string::npos;
bool s1867 = false;
while( true ) {
s1865 = s1864;
s1864 = s.find_first_of( s1331, s1864 );
if( s1864 == string::npos ) {
if( s1867 )
throw new s2::s16( L"no closing quote: " + s.substr(s1865, 20) );
return;}
if( s[s1864] == L'\"' ) {
if( ! (s1864 && s[s1864-1] == '\\' ))
s1867 = !s1867;}
else{
if( !s1867 ) {
s65 = s1864;
return;}}
++s1864;}
return;
size_t pl = s.find_first_of( s1331, s65 );
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
pl = s.find_first_of( s1331, pl );}
else {
s65 = pl;
return;}}}
void s1316( const std::wstring& s, size_t& s65, const std::wstring& s1082 ){
size_t pl = s.find( s1082, s65 );
if( pl == s65 )
return;
size_t start = s65;
s65 = string::npos;
while( pl < s.size() ) {
if( s1082.size() == 1 && s[pl - 1] == '\\' ) {
++pl;
continue;}
if( count( s, L"\"", start, pl, true ) % 2 ) {
pl += s1082.size();
if( pl < s.size() )
pl = s.find( s1082, pl );}
else {
s65 = pl;
return;}}}
size_t count( const std::wstring& s77, const std::wstring& s1082, size_t start, size_t end,
bool s879 ){
size_t s680 = 0;
size_t pl = s77.find( s1082, start );
while( pl < s77.size() && pl <= end) {
if( s879 && pl && s77[pl-1] == '\\' ) {
++pl;}
else {
++s680;
pl += s1082.size();}
if( pl < s77.size() - 1 ) 
pl = s77.find( s1082, pl );}
return s680;}
int s56( const wstring& s77, wchar_t s72, size_t& pos ){
size_t s70 = s77.find( s72, pos );
if( s70 == wstring::npos )
throw invalid_argument( "separator not found" );
wstring s = s52( s77.substr( pos, s70 - pos ), L" " );
int s680 = stoi( s );
pos = s77.find_first_not_of( s48 + s72, s70 );
return s680;}
bool s62( const wchar_t *str, long *s346, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s680 = true;
errno = 0;
try {
*s346 = std::wcstol( str, &s67, 0 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string to number: " + U16( e.what() ));}
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s346 == LONG_MIN || *s346 == LONG_MAX ) && errno == ERANGE ) )
s680 = false;
if( end )
*end = s67;
return s680;}
bool s1532( const wchar_t *str, long long *s346, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s680 = true;
errno = 0;
*s346 = std::wcstoll( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s346 == LLONG_MIN || *s346 == LLONG_MAX ) && errno == ERANGE ) )
s680 = false;
if( end )
*end = s67;
return s680;}
bool s1533( const wchar_t *str, unsigned long long *s346, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s680 = true;
errno = 0;
*s346 = std::wcstoull( str, &s67, 0 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s346 == ULLONG_MAX ) && errno == ERANGE ) )
s680 = false;
if( end )
*end = s67;
return s680;}
bool s63( const wchar_t *str, double *s346, wchar_t **end /*= NULL*/ )
{
wchar_t *s67;
bool s680 = true;
errno = 0;
*s346 = std::wcstod( str, &s67 );
if( s67 == str || ( !end && *s67 != '\0' ) ||
( ( *s346 == HUGE_VAL || *s346 == HUGE_VALF || HUGE_VALL ) && errno == ERANGE ) )
s680 = false;
if( end )
*end = s67;
return s680;}
void s870( const wstring& s77, vector<wstring>& s152 ){
size_t s68 = s77.find_first_not_of( s48 );
size_t s676, s677;
while( s68 != string::npos ) {
wchar_t c = s77[s68];
wstring arg;
if( c == L'\"' || c == L'\'' ) {
s55( s77, s68, c, s676, s677 );
if( s677 == string::npos )
throw s2::s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
arg = s77.substr( s68, s677 - s68 + 1 );
s68 = s77.find_first_not_of( s48, ++s677 );}
else {
s677 = s77.find_first_of( s48 );
arg = s77.substr( s68, s677 - s68 );
s68 = s677;}
s152.push_back( arg );}}
std::wstring s1813( const std::wstring& s77, wchar_t c ){
size_t pl = s77.find( c ), s1835 = 0, s1806 = 0, s1829;
if( pl == string::npos )
return s77;
wstring s680( s77.size() + 100, L'\0' );
while( pl != string::npos ) { 
s1829 = pl - s1835;
if( s680.size() < s1806 + s1829 + 2 )
s680.resize( (std::max)((size_t)(s680.size()*1.1), s680.size()+100) );
memcpy( (void*)(s680.c_str() + s1806), s77.c_str() + s1835, s1829 * sizeof(wchar_t) );
s680[s1806 + s1829] = L'\\';
s680[s1806 + s1829 + 1] = s77[pl];
s1806 = s1806 + s1829 + 2;
s1835 = pl + 1;
pl = s77.find( c, pl + 1 );}
s1829 = s77.size() - s1835;
memcpy( (void*)(s680.c_str() + s1806), s77.c_str() + s1835, s1829 * sizeof(wchar_t) );
s680.resize( s1806 + s1829/* + 1*/ );
return s680;}
void s57( const wstring& s, const wstring& s72, vector<wstring>& s152, bool clr,
bool s879, size_t s2345 ){
size_t s68 = s2345, s69 = 0;
while( s69 != wstring::npos && s68 < s.size()) {
if( s879 ) {
s69 = s68;
s4::s993( s, s69, s72 );}
else
s69 = s.find( s72, s68 );
wstring seg;
if( clr )
seg = s52( s.substr( s68, s69 - s68 ), s48 );
else
seg = s.substr( s68, s69 - s68 );
s68 = s69 + s72.size();
if( seg.size() )
s152.push_back( seg );
if( s69 != string::npos && s152.capacity() <= s152.size() )
s152.reserve( s152.size() * ( s.size() / s68 ) + 100 );
}}
void s288( const vector<wstring>& v, const wstring& s72, wstring& s152 ){
if( v.empty() )
return;
s152 = v[0];
for( size_t n = 1; n < v.size(); ++n )
s152 += (s72 + v[n]);}
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
wstring s346 = s52( line.substr( pl + s72.size() ), s48 );
pr.first = s76;
pr.second = s346;}
void s59( const wstring& s77, const wstring& s72, vector<pair<wstring, wstring>>& v ){
vector<wstring> s73;
s57( s52( s77, s48 ), L"\n", s73 );
for( size_t n = 0; n < s73.size(); ++n ) {
size_t pl = s73[n].find( s72 );
wstring s76 = s52( s73[n].substr( 0, pl ), s48 );
wstring s346 = s52( s73[n].substr( pl + s72.size() ), s48 );
v.push_back( make_pair( s76, s346 ) );}}
wstring s51( const std::wstring& l, const std::wstring& s, const std::wstring& r ){
size_t pl = s.find_first_not_of( l );
if( pl == wstring::npos )
return L"";
wstring s680 = s.substr( pl );
return s680.substr( 0, s680.find_last_not_of( r ) + 1 );}
wstring s52( const std::wstring& s, const std::wstring& c ){
size_t pl = s.find_first_not_of( c );
if( pl == wstring::npos )
return L"";
wstring s680 = s.substr( pl );
return s680.substr( 0, s680.find_last_not_of( c ) + 1 );}
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
wstring s739( wstring path ){
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
int s680 = stoi( s );
pos = s77.find_first_not_of( s49 + s72, s70 );
return s680;}
void s57( const string& s, const string& s72, vector<string>& s152 ){
size_t s68 = 0, s69 = 0;
while( s69 != string::npos ) {
s69 = s.find( s72, s68 );
string seg = s52( s.substr( s68, s69 - s68 ), s49 );
s68 = s69 + s72.size();
s152.push_back( seg );}}
void s59( const string& s77, vector<pair<string, string>>& v ){
vector<string> s73;
s57( s52( s77, s49 ), "\n", s73 );
for( size_t n = 0; n < s73.size(); ++n ) {
size_t pl = s73[n].find( ':' );
string s76 = s52( s73[n].substr( 0, pl ), s49 );
string s346 = s52( s73[n].substr( pl + 1 ), s49 );
v.push_back( make_pair( s76, s346 ) );}}
string s51( const std::string& l, const std::string& s, const std::string& r ){
size_t pl = s.find_first_not_of( l );
if( pl == string::npos )
return "";
string s680 = s.substr( pl );
return s680.substr( 0, s680.find_last_not_of( r ) + 1 );}
string s52( const std::string& s, const std::string& c ){
size_t pl = s.find_first_not_of( c );
if( pl == string::npos )
return "";
string s680 = s.substr( pl );
return s680.substr( 0, s680.find_last_not_of( c ) + 1 );}
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
void s81( wstring& s77, vector<wstring>& s1094, map<size_t, size_t>& s1029 ){
size_t pos = 0;
wchar_t s82 = 0;
bool s1155 = false;
wchar_t s83 = 0;
bool s84 = false;
bool s85 = false;
size_t s86 = string::npos;
bool rem = false;
bool s972 = false;
wstring s87 = L"`'\"";
s1094.reserve( 1000 );
size_t s1024 = 1;
bool s964 = false;
while( pos < s77.size() ) {
wchar_t c = s77[pos];
if( c == '\r' ) {
s77.erase( pos, 1 );
continue;}
if( c == L'\\' ) {
s1155 = !s1155;}
else if( s82 ) {
if( c == s82 && !s1155 /*s83 != '\\'*/ )
s82 = 0;}
else if( s87.find( c ) != string::npos ) {
if( !s84 ) {
s82 = c;}}
else if( c == '*' ) {
if( !s84 && s83 == '/' ) {
s84 = true;
s85 = true;
s86 = pos - 1;
if( pos > 1 && s77[pos - 2] != '\n')
s1029[pos - 2] = s1024;}}
else if( c == '/' ) {
if( !s84 && s83 == '/' ) {
s86 = pos - 1;
s84 = true;
s85 = false;
if( pos > 1 && s77[pos - 2] != '\n')
s1029[pos - 2] = s1024;}
else if( s85 && s83 == '*' ) {
rem = true;
if( s77[pos+1] == '\n' ){
s964 = true;}}}
else if( c == '\n' ) {
s964 = true;
if( s84 ) {
if( !s85 ) {
rem = true;}
else {
if( !s972 ) {
s972 = true;}}}
else {
if( pos && s77[pos-1] != '\n' ) {
s1029[pos - 1] = s1024;}}}
if( c != L'\\' )
s1155 = false;
if( s964 ) {
size_t pl = s77.rfind( '\n', pos - 1 );
size_t m = (s77[pos] == '\n');
if( pl == string::npos )
s1094.push_back( s77.substr( 0, pos ) );
else
s1094.push_back( s77.substr( pl + 1, pos - pl - m ) );
s964 = false;
s1024++;}
if( rem ) {
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
s972 = false;
s85 = false;
rem = false;
s83 = 0;}
s83 = c;
pos++;}
if( s84 ) {
auto it = end(s1029);
if( s1029.size() ) it--; 
size_t ln = (it == end(s1029) ? 0 : it->second);
throw new s2::s16( L"TSD file is malformed: unclosed comment on line " + to_wstring( ln )  );}}
std::wstring s2169( void* p ){
wstring s680( 21, '\0' );
#ifdef WIN32		
_swprintf( (wchar_t*)s680.c_str(), L"%p", (uint64_t*)p );
#else
swprintf( (wchar_t*)s680.c_str(), 20, L"%06x", (uint64_t*)p );
#endif	
return s680;}
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
uint32_t s17::s88;
void s17::s29(){
s88 = s16::s28();}
void s1107(){
s17::s29();}
bool s97( const wstring& s92 ){
wcout << s92 << L" [Y]es | [n]o :";
wstring ans;
getline( wcin, ans );
if( ans.size() && s52( ans, L" " ).empty() )
throw new s16( s17::s89() );
if( ans.size() && ( ans[0] == L'N' || ans[0] == L'n' ) )
return false;
return true;}
int s98( const wstring& s92, const vector<wstring>& s93 ){
int s680;
while( true ) {
s129();
wcout << s92 << endl << endl;
for( size_t i = 0; i < s93.size(); ++i ) {
wcout << L"   " << i + 1 << L": " << s93[i] << endl;}
s680 = s102( L"Please, enter your answer's number: " );
if( s680 < 0 || s680 > ( int ) s93.size() ) {
wcout << "No variant with such number." << endl;
s95();
continue;}
break;}
return s680;}
wstring s99( const wstring& s92, bool s94 ){
if( !s92.empty() )
wcout << s92;
wstring s346;
if( s94 )
s96( false );
getline( wcin, s346 );
if( s94 )
s96( true );
return s346;}
wstring s100( const wstring& s92, bool s94 ){
wcout << s92;
int s116 = 0;
bool s585 = true;
wstring s117 = s92;
size_t s1101 = s117.size();
size_t s118 = s1101;
while( s585 ) {
s116 = _getch();
switch( s116 ) {
case s109:
if( s1101 > s118 ) {
wcout << '\r' << s117.substr( 0, --s1101 );}
break;
case s110:
if( s1101 < s117.size() )
wcout << s117[s1101++];
break;
case s107:
case s108:
continue;
case s113:
if( ( s1101 > s118 ) && s117.size() ) {
s117.erase( --s1101, 1 );
wcout << '\r' << wstring( s117.size() + 1, L' ' );
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}
break;
case s114:
if( s1101 < s117.size() ) {
s117.erase( s1101, 1 );
wcout << '\r' << wstring( s117.size() + 1, L' ' );
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}
break;
case s112:
s585 = false;
break;
case s115:
break;
default:
if( s1101 < s117.size() )
s117.insert( s1101, 1, s116 );
else
s117 += s116;
++s1101;
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}}
return s117;}
wstring getStringValHist( const wstring& s92, const vector<wstring>& s101 ){
wcout << s92;// << endl;
int s116 = 0;
size_t s679 = s101.size();
bool s585 = true;
wstring s117 = s92;
size_t s1872 = s92.size();
size_t s1101 = s1872;
while( s585 ) {
s116 = _getch();
#ifdef __LINUX__
if( s116 == 27 ) {
s116 = _getch();
s116 = _getch();
if( s116 == L'A' ) s116 = s107;
else if( s116 == L'B' ) s116 = s108;
else if( s116 == L'C' ) s116 = s110;
else if( s116 == L'D' ) s116 = s109;
else if( s116 == 51 ) {
s116 = _getch();
s116 = s114;}
else if( s116 == 70 ) s116 = s1544;
else if( s116 == 72 ) s116 = s1545;
else if( s116 == 54 || s116 == 53 ) {
s116 = _getch();
continue;}}
else if( s116 == 10 )
s116 = 13;
else if( s116 == 127 )
s116 = 8;
#else			
if( s116 == 224 ) {
s116 = _getch();
if( s116 == L'H' ) s116 = s107;
else if( s116 == L'P' ) s116 = s108;
else if( s116 == L'M' ) s116 = s110;
else if( s116 == L'K' ) s116 = s109;}
else if( s116 == 0 ) {
s116 = _getch();
if( s116 == 83 ) s116 = s114; // S
else if( s116 == 71 ) s116 = s1545; // G
else if( s116 == 79 ) s116 = s1544; // O
}
#endif			
switch( s116 ) {
case s109:
if( s1101 > s1872 ) {
wcout << '\r' << s117.substr( 0, --s1101 );}
break;
case s110:
if( s1101 < s117.size() )
wcout << s117[s1101++];
break;
case s107:
if( s679 > 0 ) {
if( s679 < s101.size() )
wcout << '\r' << wstring( s117.size(), L' ' );
s117 = s92 + s101[--s679];
wcout << '\r' << s117;
s1101 = s117.size();}
break;
case s108:
if( !s101.empty() && s679 < s101.size() - 1 ) {
wcout << '\r' << wstring( s117.size(), L' ' );
s117 = s92 + s101[++s679];
wcout << '\r' << s117;
s1101 = s117.size();}
break;
case s113:
if( s1101 > s1872 && s117.size() > s1872 ) {
s117.erase( --s1101, 1 );
wcout << '\r' << wstring( s117.size() + 1, L' ' );
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}
break;
case s114:
if( s1101 < s117.size() ) {
s117.erase( s1101, 1 );
wcout << '\r' << wstring( s117.size() + 1, L' ' );
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}
break;
case s1545:
if( s1101 > 0 ) {
wcout << '\r' << s92;
s1101 = s1872;}
break;
case s1544:
if( s1101 < s117.size() ) {
wcout << '\r' << s117;
s1101 = s117.size();}
break;
case s112:
s585 = false;
break;
case s115:
break;
default:
if( s1101 < s117.size() )
s117.insert( s1101, 1, s116 );
else
s117 += s116;
++s1101;
wcout << '\r' << s117 << '\r' << s117.substr( 0, s1101 );}}
return s117.substr( s1872 );}
int s102( const std::wstring & s92 ){
int s680;
while( true ) {
wcout << s92;
std::wcin.sync();
std::wstring inp;
std::getline( std::wcin, inp );
try {
s680 = stoi( inp );}
catch( std::invalid_argument& ) {
continue;}
break;}
return s680;}
void s90( const wstring& header, const std::vector<std::wstring>& s91 ){
s129();
wcout << endl << "  " << header << endl << fill_n_ch( L'-', header.size() + 4 )
<< endl << endl;
if( s91.size() ) {
wcout << L"Keyboard shortcuts: " << endl;
for( size_t n = 0; n < s91.size(); n += 2 )
wcout << setw( 10 ) << left << s91[n] << L" - " << s91[n + 1] << endl;}
wcout << endl;}
size_t s103( const std::wstring & s92 ){
wcout << s92 << endl << endl <<
L"Please, enter the number of menu item: " << endl <<
L"1 - Skip this item" << endl << L"2 - Overwrite this item" << endl <<
L"3 - Skip all already existing items" << endl <<
L"4 - Overwrite all already existing items" << endl << "5 or any key - Cancel operation" << endl;
wstring s128;
getline( wcin, s128 );
int i;
try { i = stoi( s128 ); }
catch( std::invalid_argument* ) {
i = 5;}
if( i < 1 || i > 5 )
i = 5;
return i;}
void s105( const vector<wstring>& v, vector<wstring>& s152, size_t w, size_t h ){
size_t s119 = v.size() / h + 1;
size_t s120 = v.size() / s119;
vector<size_t> s121;
size_t s679 = 0;
for( auto it : v ) {
if( s679 == 0 )
s121.push_back( 0 );
if( it.size() > s121.back() )
s121.back() = it.size();
if( ++s679 == s120 )
s679 = 0;}
size_t s122 = 0, s123 = 0;
size_t s124 = 0;
for( size_t n = 0; n < s119; ++n ) {
s124 += s121[n] + 5;
if( n == s119 - 1 || s124 + s121[n + 1] + 5 > w ) {
size_t s125 = n - s122 + 1;
s124 = 0;
if( s122 ) {
if( s99( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}
for( size_t m = s123;
m < min( s123 + s120, v.size() );	++m ) {
wostringstream ss;
for( size_t k = 0;
k < min( s125, ( v.size() - m - 1 ) / s120 + 1 ); ++k )
ss << setw( 3 ) << right << m + s120 * k + 1 << L". " << setw( s121[s122 + k] ) <<
left << v[m + s120 * k];
s152.push_back( ss.str() );}
s123 += s125 * s120;
s122 = n + 1;}}}
int s106( const std::vector<std::wstring>& v ){
int w, h;
s104( w, h );
std::vector<std::wstring> rows;
s105( v, rows, w, h );
size_t s126 = 0;
for( auto it : rows ) {
wcout << it << endl;
if( ++s126 % h == 0 ) {
if( s99( L"Press <Return> to continue listing or <q> to stop... " ) == L"q" )
break;}}
int s127;
while( true ) {
wcout << endl;
wstring s128 = s99( L"Enter the item's number or <Space> to cancel..." );
if( s128 == L" " )
return -1;
try { s127 = stoi( s128 ); }
catch( std::invalid_argument& ) {
continue;}
break;}
if( s127 > (int)v.size() ) {
wcout << L"No record with such number." << endl;
return -1;}
return s127;}
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
void s95(){
wcout << endl << L"Press 'Return' to continue..." << endl;
std::system( "read" );}
void s129( int s73 ){
std::system( "clear" );
for( int i = 0; i < s73; ++i )
wcout << endl;}
void s96( bool b ){
struct termios tty;
tcgetattr( STDIN_FILENO, &tty );
if( !b )
tty.c_lflag &= ~ECHO;
else
tty.c_lflag |= ECHO;
(void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );}
void s104( int& w, int& h ){
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
if( buf[2] == 65 ) buf[0] = s107;
if( buf[2] == 66 ) buf[0] = s108;
if( buf[2] == 67 ) buf[0] = s110;
if( buf[2] == 68 ) buf[0] = s109;}
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
void s95(){
wcout << endl;
std::system( "pause" );}
void s129( int s73 ){
std::system( "CLS" );
for( int i = 0; i < s73; ++i )
wcout << endl;}
void s96( bool b ){
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode;
GetConsoleMode( hStdin, &mode );
if( !b )
mode &= ~ENABLE_ECHO_INPUT;
else
mode |= ENABLE_ECHO_INPUT;
SetConsoleMode( hStdin, mode );}
void s104( int& w, int& h ){
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;}
} // namespace consutils
#endif // WIN32
using namespace s6;
namespace transd {
namespace s7 {
s921 s1541		= 0x80000000;
s921 s1383        = s1541 - 1;
s921 s1384       = s1541 - 2;
s921 s1385       = s1541 - 3;
s921 s1382      = s1541 - 4;
s921 s1381						= s1541 - 8;
s921 s1386    = s1541 - 9;
s921 s1387					= s1541 - 10;
DEFCONST s417 = L"typeMembers";
DEFCONST s418 = L"typeMember";
DEFCONST s419 = L"typeMethods";
DEFCONST s420 = L"typeMethod";
DEFCONST s421 = L"members";
DEFCONST s422 = L"member";
DEFCONST s423 = L"methods";
DEFCONST s424 = L"method";
DEFCONST s425 = L"@init";
DEFCONST s426 = L"@initCall";
DEFCONST s1616 = L"@to-String";
DEFCONST s427 = L"thisPtr";
DEFCONST s428 = L"virtual";
DEFCONST s429 = L"override";
DEFCONST s826 = L"return";
DEFCONST s430 = L"continue";
DEFCONST s431 = L"break";
DEFCONST s432 = L"throw";
DEFCONST s758 = L"else";
DEFCONST s742 = L"elsif";
DEFCONST s788 = L"to";
DEFCONST s433 = L"true";
DEFCONST s434 = L"false";
DEFCONST s825 = L"null";
DEFCONST s933 = L"->";
DEFCONST s1130 = L"const";
DEFCONST s1345 = L"@new";
DEFCONST s1379 = L"stdin";
DEFCONST s1380 = L"stdout";
DEFCONST s1588 = L"this";
DEFCONST s2123 = L"locals:";
DEFCONSTI s859 = -1;
DEFCONSTI s2218 = -2;
DEFCONSTI s2264 = -3;
DEFCONSTI s437 = -4;
DEFCONSTI s435 = -100;
DEFCONSTI s436 = -101;
DEFCONSTI s438 = 1;
DEFCONSTI s439 = 0;
DEFCONSTI s861 = 0x40000000;
DEFCONSTI s1732 = 0x60000000;
DEFCONSTI s860 = 0;
DEFCONSTI s1189 = 1;
DEFCONST s2299 = L":Data";
DEFCONST s1401 = L":Number";
DEFCONST s1512 = L":Integer";
DEFCONST s1399 = L":IterableForw";
DEFCONST s1398 = L":IterableBidir";
DEFCONST s1400 = L":IterableRand";
DEFCONST s1397 = L":IStream";
DEFCONST s1402 = L":OStream";
DEFCONST s1396 = L":IOStream";
DEFCONST s440 = L"import";
DEFCONST s441 = L"input";
DEFCONST s442 = L"output";
DEFCONST s443 = L"export";
DEFCONST s444 = L"opaque";
DEFCONST s445 = L"public";
DEFCONST s446 = L"private";
DEFCONST s447 = L"secure";
DEFCONST s448 = L"class";
DEFCONST s449 = L"module";
DEFCONST s2145 = L"interface";
DEFCONST s450 = L"AssemblyDescription";
DEFCONST s451 = L"ProgramText";
DEFCONST s452 = L"Export";
DEFCONST s453 = L"Require";
DEFCONST s2151 = L"TypeAlias";
DEFCONST s454 = L".td";
DEFCONST s938 = L".tsd";
DEFCONST s456 = L"MainModule";
DEFCONST s455 = L"_start";
DEFCONST s457 = L"asm" + s454;
DEFCONST s458 = L"@ex";
DEFCONST s1362 = L"@it";
DEFCONST s459 = L"@idx";
DEFCONST s2471 = L"@projRes";
DEFCONST s1966 = L"@row";
DEFCONST s762 = L"@pars";
DEFCONST s796 = L"@obj";
DEFCONST s822 = L"@numArgs";
DEFCONST s1559 = L"@progArgs";
DEFCONST s1114 = L"@sourceFile";
DEFCONST s1361 = L"@OS_Type";
DEFCONST s464 = L"source";
DEFCONST s460 = L"objectType";
DEFCONST s461 = L"moduleType";
DEFCONST s462 = L"@name";
DEFCONST s463 = L"entryPoint";
DEFCONST s465 = L"perm";
DEFCONST s466 = L"extends";
DEFCONST s732 = L"packages";
DEFCONST s467 = L"searchDirs";
DEFCONST s929 = L"@attrs";
DEFCONST s1967 = L"restrictions";
DEFCONST s2144 = L"@impl";
DEFCONST s1973 = L"FileRead";
DEFCONST s1974 = L"FileWrite";
DEFCONST s1972 = L"FileAll";
DEFCONST s1975 = L"FuncEval";
DEFCONST s1976 = L"FuncStartProcess";
DEFCONST s1977 = L"RestrictionsAll";
DEFCONST s1978 = L"allow";
DEFCONST s1981 = L"noResult";
DEFCONST s1980 = L"noExecute";
DEFCONST s1979 = L"noCompile";
DEFCONST s908 = L"is";
DEFCONST s907 = L"index type";
DEFCONST s909 = L"value type";
DEFCONST s415 = L"#lang transd";
DEFCONST s1096 = L"#format tsd";
s921 s1289						= 103;
s921 s916						= 110;
s921 s1288				=	123;
s921 s1119						= 124;
s921 s917 			=	125;
s921 s911			= 201;
s921 s1097				= 204;
s921 s912					= 210;
s921 s1098					= 304;
s921 s1099				= 404;
s921 s1100				= 504;
s921 s913					= 510;
s921 s914			= 511;
s921 s915					= 610;
s921 s1116							= 710;
s921 s1117					= 711;
s921 s1354		= 804;
s921 s1355				= 904;
s921 s1356				= 1004;
s921 s1584					= 1024;
s921 s1118					= 1124;
s921 s1285				= 1203;
s921 s1286				= 1210;
s921 s1287				= 1224;
s921 s1652		= 1304;
s921 s1653						= 1404;
s921 s1366						= 1410;
s921 s2275					= 1411;
s921 s1654						= 1504;
s921 s1364						= 1510;
s921 s1365					= 1511;
s921 s1655				= 1604;
s921 s1510					= 1610;
s921 s1511			= 1611;
s921 s1672			= 1704;
s921 s1542			= 1710;
s921 s1586	= 1715;
s921 s1888	= 1716;
s921 CLObjectVal_ctor1				= 1810;
s921 s1585				= 1824;
s921 s1673					= 1904;
s921 s1687				= 2025;
s921 s1876				= 2103;
s921 s1921				= 2210;
s921 s1920					= 2310;
s921 s2143			= 2409;
s921 s2274						= 2410;
s921 CLTDFilter_ctor1				= 2504;
s921 s2190					= 2510;
s921 s2201						= 2603;
s921 s2199						= 2610;
s921 s2200						= 2624;
s921 s2234				= 2703;
s921 s2233				= 2710;
set<wstring> s1113 = { s1114, s1379, s1380, s1361, s826, s430,
s431, s432, s758, s742, s788, s433, s434, s825, s933, s1130,
s1345, s1379, s1380, s1588, L"and", L"or"
};
} // namespace s7
std::wstring s228[] = { L"value", L"function", L"object", L"name" };
const wstring s229 = L"if";
const wstring s230 = L"set";
const wstring s231 = L"sum";
const wstring s232 = L"with";
const wstring s233 = L"mul";
const wstring s234 = L"div";
const wstring s235 = L"dif";
const wstring s236 = L"eq";
const wstring s237 = L"less";
const wstring s238 = L"greater";
const wstring s239 = L"leq";
const wstring s240 = L"geq";
const wstring s241 = L"neq";
const wstring s242 = L"and";
const wstring s243 = L"or";
const wstring s2062 = L"first";
const wstring s244 = L"dcmp";
const wstring s245 = L"dcmpr";
const wstring s246 = L"mod";
const wstring s247 = L"sqrt";
const wstring s248 = L"abs";
const wstring s249 = L"pow";
const wstring s1929 = L"textin";
const wstring s250 = L"textout";
const wstring s251 = L"lambda";
const wstring s252 = L"proc";
const wstring s254 = L"while";
const wstring s255 = L"eval";
const wstring s256 = L"try";
const wstring s257 = L"catch";
const wstring s258 = L"throw";
const wstring s253 = L"through";
const wstring s259 = L"for";
const wstring s260 = L"run-file";
const wstring s765 = L"load-file";
const wstring s814 = L"import-module";
const wstring s1607 = L"unload-file-modules";
const wstring s1306 = L"unload-module";
const wstring s744 = L"has-field";
const wstring s811 = L"tql";
const wstring s752 = L"substr";
const wstring s845 = L"ret";
const wstring s846 = L"sort";
const wstring s893 = L"exit";
const wstring s1305 = L"to-file";
const wstring s1416 = L"any";
const wstring s1415 = L"all";
const wstring s1928 = L"pipe";
const wstring s2193 = L"filter";
const wstring s1549 = L"lout";
const wstring s1927 = L"lin";
const wstring s1603 = L"read-tsd-file";
const wstring s1602 = L"load-from-object";
const wstring s1606 = L"start-process";
const wstring s1604 = L"rebind";
const wstring s1605 = L"sleep";
const wstring s1601 = L"diag";
const wstring s1870 = L"rand";
const wstring s2213 = L"yield";
const s140 s264(L"AttrNA");
s262::s262( s1889& s, const s140* s6, s262* s2092 )
: s1045( (s140*)s6 ), s2091( s2092 ), s2096( NULL ){
s995( s );}
s262::s262( s1889& s671, const s6::s140& s295, s262* s589 )
: s1659( s671 ), s1045( (s140*)&s295 ), s2091( NULL ), s2096( s589 ){
if( s295.s163() == s133 ) {
wstring s = s295.s168();
s995( s );}
else if( s295.s163() == s138 ) {
wstring s = //L"\"" +
s295.s168();// +
s283( s );}
else if( s295.s163() == s132 ) {
basic_stringstream<wchar_t> ss;
s295.s154( &ss, true );
if( 0 ) {
s283( ss.str() );}
else {
src = ss.str();
s282( s295.s165() );}}
else if( s295.s163() == s135 )
s283( to_wstring( s295.s167() ) );
else if( s295.s163() == s139 )
s283( to_wstring( s295.s56() ) );
else if( s295.s163() == s136 )
s283( /*to_wstring( s295.s721() )*/ s295.s721() ? L"true" : L"false" );
else if( s295.s163() == s134 ) {
basic_stringstream<wchar_t> ss;
s295.s154( &ss );
if( s1659.find( L"UVector" ) == 0 ) {
s283( L"UVector" + ss.str() );
s1659 = s4::s52( s1659.substr( 7 ), s48 );}
else
s283( ss.str() );}
else if( s295.s163() == s131 )
s283( L"" );
else
throw new s16( L"Unhandled nqj variant: " + to_wstring( s295.s163() ) );}
s262::s262( const s6::s142& s132 )
: s2091( NULL ), s2096( NULL ){
s282( s132 );}
s262::~s262(){
reset();}
void s262::reset(){
s280.clear();
s265.clear();
s276 = s1659 = s279 = src = L"";}
void s262::s995( s1889& s ){
size_t pos = 0;
wstring s1174 = L"\"'`-+[{<";
if( s.empty() ) {
s283( s );}
else if( s[pos] == L'(' )
s281( s );
else if( iswalpha( s[pos] ) || s[pos] == L'_' || s[pos] == L'@' || s[pos] == L':' ) {
if( s.find( L'(' ) != string::npos || s.find( L"true" ) == 0 
|| s.find( L"false" ) == 0)
s283( s );
else
s284( s );}
else if( iswdigit( s[pos] ) || s1174.find( s[pos] ) != string::npos ) {
wstring s77;
s77 = s52( s, s48 );
s283( s77 );}
else
throw new s16( L"Unknown string content: " + s );}
void s262::s281( s1889& s77 ){
src = s77;
size_t pos = 0;
vector<wstring> s672;
s287( s77, pos, s672 );
if( s672.empty() )
return;
s278 = s225;
size_t s68 = 0;
s279 = s286( s672[0], s68 );
for( size_t n = 1; n < s672.size(); n++ )
s280.insert( make_pair( to_wstring( n - 1 ), new s262( s672[n], s1045, this ) ) );}
void s262::s283( s1889& s77 ){
src = s77;
s278 = s224;
s279 = s77;}
void s262::s284( s1889& s77 ){
if( s77.find( L"." ) != string::npos ) {
s276 = L".";}
src = s77;
s278 = s227;
s279 = s77;}
void s262::s282( const s6::s142& s132 ){
s1659 = s301( s132, s7::s462 );
s278 = s226;
vector<pair<wstring, s141>> s143;
s132.s159( s143 );
for( size_t n = 0; n < s143.size(); ++n ) {
s285( s143[n].first, *s143[n].second );}}
void s673( wstring& s ){
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
void s262::s288( s6::s142& obj, size_t s2176 ){
wstring s674 = s4::s52( s301( obj, s7::s462 ), s48 );
wstring s655 = s674;
s673( s655 );
if( s655.empty() )
throw new s16( L"Nameless blocks are forbidden." );
if( s655 != s674 )
obj.s158( s7::s462, s141(new s140( s655 )), s142::s146 );
if( s655 == s1659 ) { // partial definition
vector<pair<wstring, s141>> s143;
obj.s159( s143 );
for( size_t n = 0; n < s143.size(); ++n )
s285( s143[n].first, *s143[n].second );}
else {
wstring s2181 = s655;
s262* s2178 = new s262( obj );
s2178->s268( s2173, s140( (double)s2176, s139 ) );
s280.insert( make_pair( s2181, s2178 ) );}}
void s262::s285( s262* node ){
s280.insert( make_pair( node->s298(), node ) );}
void s262::s285( s1889& s76, const s140& s346 ){
s280.insert( make_pair( s76, new s262( s76, s346, this ) ) );}
void s262::s289( s261* s299, size_t s300 /*= 0*/ )
{
s274::iterator it = s280.begin();
for( ; it != s280.end(); ++it ) {
if( it->second->s296() == s226 ) {
if( s300 == 0 ) {
it->second->s289( s299, 1 );}
else {}}}}
bool s262::s155( s1889& s76 ) const{
if( s280.find( s76 ) == end( s280 ) )
return false;
return true;}
const s262* s262::s291( s1889& s76 ) const{
size_t s679 = s280.count( s76 );
if( s679 > 1 )
throw new s16( L"multiple values: " + s76, (uint32_t)s148 );
if( s679 == 1 ) {
auto s680 = s280.find( s76 );
return s680->second.s15<s262*>();}
throw new s16( L"node not found: " + s76, (uint32_t)s16::s17::s23 );}
void s262::s287( s1889& s77, size_t& pos, vector<wstring>& s152 ){
size_t s74, s75;
wregex rg( LR"regex(\s*[@\w]+\([\s\S.[:space:][:blank:][:cntrl:][:graph:]\n\r]*)regex" );
wregex rg1( LR"regex(^\s*[@\w]+\s*<)regex" );
wsmatch s1066;
s54( s77, pos, L'(', L')', s74, s75, true );
if( s74 != pos || s75 == string::npos )
throw new s16( L"Parentheses don't match near \"" + 
s77.substr( 0, 40 ) + L"...\"" );
pos = s75;
size_t s68 = s77.find_first_not_of( s48, s74 + 1 );
if( s77[s68] == L')' )
return;
size_t s678 = s68;
wstring s675;
while( s678 < s75 ) {
s68 = s77.find_first_not_of( s48 + L")", s678 );
if( s68 >= s75 )
break;
size_t s676, s677;
if( s77[s68] == L'(' ) {
s54( s77, s68, L'(', L')', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else if( s77[s68] == L'[' ) {
s54( s77, s68, L'[', L']', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else if( s77[s68] == L'{' ) {
s54( s77, s68, L'{', L'}', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Curly brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else if( s4::s87.find ( s77[s68] ) != string::npos ) {
wchar_t _q = s77[s68];
s55( s77, s68, _q,	s676, s677 );
if( s677 == string::npos )
throw new s16( L"Quotes don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else if( iswdigit( s77[s68] ) ) {
s677 = s77.find_first_of( s48 + L")", s68 );
s675 = s77.substr( s68, s677 - s68 );
s678 = s677;}
else if( iswalpha( s77[s68] ) || s77[s68] == L'_' || s77[s68] == L'@' ) {
s677 = s77.find_first_of( s48 + L")", s68 );
size_t s2256 = s77.find_first_of( L"(", s68 );
size_t s2255 = s77.find_first_of( L"<", s68 );
if( s77[s68] == 955 ) { 
s675 = s77[s68];
s678 = s68 + 1;}
else if( s77.find( L"lambda", s68 ) == s68 ) {
s675 = L"lambda";
s678 = s68 + 6;}
else if( s2256 < s677 ) {
s54( s77, s2256, L'(', L')', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else if( s2255 < s677 ) {
s54( s77, s2255, L'<', L'>', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Angle brackets don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );
if( s77[s677+1] == L'(' ) {
s54( s77, s2255, L'(', L')', s676, s677, true );
if( s677 == s75 )
throw new s16( L"Parentheses don't match near \'" + s77.substr( s68, 40 ) + L"...\'" );}
s675 = s77.substr( s68, s677 - s68 + 1 );
s678 = s677 + 1;}
else {
s677 = s77.find_first_of( s48 + L")", s68 );
s675 = s77.substr( s68, s677 - s68 );
s678 = s677;}}
else {
s677 = s77.find_first_of( s48 + L")", s68 );
s675 = s77.substr( s68, s677 - s68 );
s678 = s677;}
s152.push_back( s675 );}}
wstring s262::s286( const std::wstring& s77, size_t &pos ){
size_t s1714 = s77.find( L"<" );
if( s1714 != string::npos && s1714 > 0 ) {
return s77;}
wstring s680;
if( s77[pos] == L'+' && s77[pos + 1] != L'=' )
s680 = s231;
else if( s77[pos] == L'-' && s77[pos + 1] != L'=' && s77[pos + 1] != L'|')
s680 = s235;
else if( s77[pos] == L'*' && s77[pos + 1] != L'=' )
s680 = s233;
else if( s77[pos] == L'/' && s77[pos + 1] != L'=' )
s680 = s234;
else if( s77[pos] == L'^' && s77[pos + 1] != L'=' )
s680 = s249;
else if( s77[pos] == L'=' && s77[pos + 1] != L'=' )
s680 = s230;
else if( s77[pos] == L'<' && s77[pos + 1] != L'=' )
s680 = s237;
else if( s77[pos] == L'>' && s77[pos + 1] != L'=' )
s680 = s238;
else if( s77[pos] == 955 /*L'λ'*/ )
s680 = s251;
if( s680.size() ) {
if( s77.size() > pos + 1 && s77.find_first_of( s48 + L")", pos ) != pos + 1 )
throw new s16( L"1: unknown syntax: " + s77.substr(pos, 40),
(uint32_t)s16::s17::s20 );
pos += 1;
return s680;}
if( s77.substr( pos, 2 ) == L"+=" )
s680 = L"sumeq";
else if( s77.substr( pos, 2 ) == L"-=" )
s680 = L"difeq";
else if( s77.substr( pos, 2 ) == L"*=" )
s680 = L"muleq";
else if( s77.substr( pos, 2 ) == L"/=" )
s680 = L"diveq";
else if( s77.substr( pos, 2 ) == L"^=" )
s680 = L"poweq";
else if( s77.substr( pos, 2 ) == L"<=" )
s680 = L"leq";
else if( s77.substr( pos, 2 ) == L">=" )
s680 = L"geq";
else if( s77.substr( pos, 2 ) == L"==" )
s680 = L"eq";
else if( s77.substr( pos, 2 ) == L"!=" )
s680 = L"neq";
else if( s77.substr( pos, 2 ) == L"-|" )
s680 = s1928;
if( s680.size() ) {
if( s77.size() > pos + 2 && s77.find_first_of( s48 + L")", pos ) != pos + 2 )
throw new s16( L"2: unknown syntax: " + s77.substr( pos, 40 ), 
(uint32_t)s16::s17::s20 );
pos += 2;
return s680;}
size_t s678 = s77.find_first_of( s48 + L")", pos );
s680 = s77.substr( pos, s678 - pos );
pos = s678;
return s680;}
std::wstring s262::s297() const{
return (s276.size() ? s276 + L"::" : L"") + s1659;}
wstring s262::s294( const s6::s142& obj,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s155( s7::s461 ) )
return obj.s157( s7::s461 )->s168();
return def;}
std::wstring s262::s301( const s6::s142& obj,
const std::wstring& s302,
const std::wstring& def /*= std::wstring( L"" )*/ )
{
if( obj.s155( s302 ) )
return obj.s157( s302 )->s168();
return def;}
void s262::s2267( const std::pair<wstring, wstring>& pr ){
if( s280.size() ) {
for( auto sn : s280 )
sn.second->s2267( pr );}
else {
if( s279.find( L"Lambda<" ) == 0 ) {
size_t lpl = s279.find( 955 );
size_t rpl = s279.find(L"]]");
if( s279.find( L"(", lpl ) < rpl )
return;
if( s279.find( pr.first ) > rpl )
return;}
if( s279.find( L"(" ) != string::npos || s279.find( L"[" ) == 0 ) {
size_t pl = 0;
s4::s1316( s279, pl, pr.first );
size_t len = pr.first.size();
while( pl != string::npos ) {
if( ( pl && ( s279[pl - 1] == L'(' || s279[pl - 1] == L' ' ||
s279[pl - 1] == ',' || s279[pl - 1] == '[' || s279[pl - 1] == '{' ||
s279[pl - 1] == ':' ) ) &&
( s279[pl + len] == L')' || s279[pl + len] == L' ' || s279[pl + len] == L'\n' ||
s279[pl + len] == ',' || s279[pl + len] == '.' || s279[pl + len] == ']' ||
s279[pl + len] == '}' || s279[pl + len] == ':' ) )
s279.replace( pl, len, pr.second );
++pl;
s4::s1316( s279, pl, pr.first );}}
else if( s276 == L"." ) {
if( s279.find( pr.first ) == 0 && s279[pr.first.size()] == L'.' )
s279.replace( 0, pr.first.size(), pr.second );}
else if( s279 == pr.first )
s279 = pr.second;}}
const s6::s140& s262::s267( size_t s2090 ) const{
auto it = s265.find( s2090 );
if( it != s265.end() )
return it->second;
return s264;}
const s6::s140& s262::s2100( size_t s2090 ) const{
auto it = s265.find( s2090 );
if( it == s265.end() ) {
if( s2091 )
return s2091->s2100( s2090 );
else
return s264;}
return it->second;}
void s262::s268( size_t s2090, const s6::s140& s266 ){
s265[s2090] = s266;}
void s262::s2107( const s262& s694 ){
for( auto i : s694.s265 )
s265.insert( make_pair( i.first, i.second ) );}
void s262::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s1659 << L" : " << s228[s278] << endl;
buf << s4::fill_n_ch( L' ', s196 ) << L" " << s279 << endl;
map<wstring, s939>::const_iterator it = s280.begin();
for( ; it != s280.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << it->first << endl;
it->second->s303( pd, s196 + s416 * 2 );}}
} // namespace transd
using namespace s8;
namespace transd {
s1095 s1006;
void s1095::s963( const std::wstring& s78 ){
++s989;
s26.push_back( Msg( s78 ) );
wcout << s78;}
void s1095::s963( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
++s989;
s26.push_back( Msg( s78, U16(func), U16(file), line, s1033 ) );}
void s1095::s965( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line ){
s26.push_back( Msg( s78, U16(func), U16(file), line, s1036 ) );}
} // namespace expr
namespace transd {
std::vector<std::wstring> s1077 = {
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
TDException::TDException( uint32_t s1007, uint32_t cat, const s262* ast_ )
: s16( L"", s1007 ), stage (Stage::s1023 ), category( cat ), s694( (s262*)ast_ ){}
TDException::TDException( Stage stg, uint32_t s1007, uint32_t cat, const s262* ast_, const s16& e )
: s16( e ), stage ( stg ), category( cat ), s694( (s262*)ast_ ){
if( category ) {
s30( L"error code: " + std::to_wstring( s1007 ) );
s30( s986[category] + L":" );}}
TDException::TDException( uint32_t s1007, uint32_t cat, const s262* ast_, s1889& s78, Stage stg )
: s16( s78, s1007 ), stage ( stg ), category( cat ), s694( (s262*)ast_ ){
if( category ) {
s30( s986[category] + L":" );}}
TDException::TDException( const TDException& e )
: s16( e ), stage( e.stage ), category( e.category ), s1079( e.s1079 ), s694( e.s694 ){}
TDException* TDException::s992( const std::wstring& s ){
specify( s );
return new TDException( *this );}
wstring TDException::Msg( size_t s196 ) const{
wstring src;
if( s694.s14() )
src = s1896( *s694 );
wstring s = L"Error ";
if( id ) {
wstring s1069;
if( (uint32_t)stage )
s1069 = L" " + std::to_wstring( (uint32_t)stage ) + L":";
s1069 += std::to_wstring( id );
s += s1069;}
if( (uint32_t)stage ) {
s += L" during " + s1077[(uint32_t)stage];}
s += src + L"\n";
return wstring( s196, L' ' ) + s + s16::Msg( s196 + 2 );}
wstring TDException::s2152( size_t idx ) const{
if( s26.size() < idx )
return L"";
auto it = begin( s26 );
std::advance( it, idx );
return *it;}
wstring TDException::s1896( const s262& s694 ){
size_t s1025 = 0;
wstring file, s1075, s680;
if( s694.Nqj() && s694.Nqj()->s1001( file, s1075, s1025 ) ) {
wstring s1071 = std::to_wstring( s1025 ) + L": '" + s1075 + L"'";
s680 = L"\n  in file: " + file + L"\n  on line " + s1071;}
if( !s694.s290().empty() )
s680 += L"\n  object: '" + s694.s290() + L"', ";
if( !s694.Src().empty() )
s680 += L"code: '" + s694.Src() + L"', ";
return s680;}
s920::s920( s16& e, const s262& s694, s17 code )
: s16( e ){
id = (uint32_t) code;
size_t s1025 = 0;
wstring file, s1075, src;
wstring	s78 = L"Error during ";
if( s694.Nqj()->s1001( file, s1075, s1025 ) ) {
src = std::to_wstring( s1025 ) + L": '" + s1075 + L"'";
s78 += L"in file: " + file + L";\nline " + src + L";\n";}
else {
s78 += L"object: '" + s694.s290() + L"'; code: " + s694.Src();}
s30( s78 );
s1006.s963( Msg( 2 ) );}
s928::s928( s17 code )
: s16( L"" ){
id = (uint32_t) code;}
vector<wstring> s986 = {
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
bool s653( const wstring& s, bool s707 ){
bool fail = false;
for( size_t n = 0; n < s.size(); ++n ) {
wchar_t c = s[n];
if( iswalpha( c ) ||
c == L'_' ||
( isdigit( c ) && n ) ) {
continue;}
if( s7::s1113.find( s ) != s7::s1113.end() )
continue;
fail = true;
break;}
if( fail && s707 )
throw new s16( L"illegal identifier: " + s );
return (!fail);}
} // namespace tdlang
s919 s985;
s270::~s270(){}
s480* s270::s493()
{	throw std::logic_error( "1: not implemented" );}
const s480* s270::s500() const
{	throw std::logic_error( "2: not implemented" );}
s483 s270::s494( s480** s273, size_t s495 )
{	throw std::logic_error( "3: not implemented" ); }
s270* s270::s332( s588* s2041, s271* impl ) const
{	throw std::logic_error( "4: not implemented" ); }
void s270::s497( const s271* s584, bool b ) {
(void)0;}
inline bool
s270::s498( const s480* s499 ) const{
return ( s499->s349() == s349() );}
inline bool
s270::s1529( s1053 s616 ) const{
return s299->TR().s1522( s349(), s616 );}
const s806& 
s270::s1186() const {
return s299->TR().s1005( s490 ); }
s270::operator bool() const { throw std::logic_error( "5: not implemented" ); }
s270::operator int() const { throw std::logic_error( "6: not implemented" ); }
s270::operator double() const { throw std::logic_error( "7: not implemented" ); }
wstring s270::to_wstring( uint32_t s1552 ) const { throw std::logic_error( "8: not implemented" ); }
s1311 s270::to_bytes() const { throw std::logic_error( "9: not implemented" ); }
void s270::to_null() { s1664( s7::s1732 ); }
void s270::s1322( const s262& ast_, s261* s299, s271* obj,
s1889& s331, vector<s270*>& s152 ){
assert( ast_.s290().size() );
size_t pos = 0;
vector<wstring> s672;
wstring s77;
if( ast_.s290().find( '(' ) == string::npos )
s77 = L"(" + ast_.s290() + L")";
else
s77 = ast_.s290();
if( s77.empty() )
return;
/*wstring s = s77;
if( s[0] != L'(' )
s = L"(" + s + L")";*/
s262::s287( s77.substr( s77.find( L"(" ) ), pos, s672 );
if( s672.empty() )
return;
for( size_t n = 0; n < s672.size(); n++ ) {
s262* ast1 = new s262( s672[n], ast_.Nqj(), (s262*)&ast_ );
s152.push_back(
s270::s501( *ast1, s299, obj, s331, false )
);}}
s270* s270::s501( const s262& s694, s261* s299, s271* obj,
s1889& s331, bool s2159 ){
TDException s960( s7::s1687, s925, &s694 );
s270* p;
if( s694.s296() == s224 ) {
wstring s346 = s694.s290();
bool quot = s87.find( s346[0] ) != string::npos;
size_t ppl = s346.find( L"(" );
bool lastp = s346.back() == L')';
s1889& ownerName = s694.s267( s2084 ).s168();
if( ( s694.s267( s2278 ).s168() == L"locals" || 
( s694.s267( s2085 ).s168() == L"CallSite" &&
ownerName != s251 ) ) &&
!quot && lastp && ppl > 0 && ppl < string::npos ) {
wstring s344 = s346.substr( 0, ppl );
wstring s77 = L"(" + s7::s1345 + L"<" + s344 + L"> " + s346.substr( ppl + 1 );
s939 tast = new s262( s77, s694.Nqj(), (s262*)&s694 );
p = s588::s1109( *tast, s299, obj, s331, s2159 );}
else {
p = s299->TR().s515( s694, obj, s331 );
if( !p )
throw s960.s992( L"unrecognized type of the object: " + s694.s290() );
((s480*)p)->s503( s694.s298() );}}
else if( s694.s296() == s225 )
p = s588::s1109( s694, s299, obj, s331, s2159 );
else if( s694.s296() == s227 )
p = new s368( s694.s290(), s299 );
else //if( s694.s296() == s226 )
throw new s16( L"unexpected node type" );
return p;}
s270* 
s270::s1010( s261* s299, s270* par, s271* s585, s588* s214,
s1889& s331, bool proc ){
s270* s680;
if( par->s491() == s474 ) {
s487 cs = new s558( *((s558*)par) );
s680 = s588::s597( cs, s299, s585, s214, s331, proc );
((Transd*)s680)->s497( s585, proc );}
else {
par->s497( /*s585*/s214 ? s214 : s585, proc );
return par;}
return s680;}
s482
s270::s1009( s1889& s77, const s262* ast_, s261* s299, s271* s585 ){
s939 ast1;
if( ast_ )
ast1 = new s262( s77, ast_->Nqj(), (s262*)ast_ );
else
ast1 = new s262( L"", s77 );
s482 pr = s270::s501( *ast1, s299, s585, s585->s297() );
if( pr->s491() == s472 ) {
pr->s497( s585 );
pr = pr.s15<s368*>()->s374();}
s482 s680 = s270::s1010( s299, pr, s585, NULL, s585->s297(), false );
return s680;}
const wstring& 
s270::s350() const{
return s299->TR().s797( s349() );}
void s270::s348( s806::s730 type ){
s490 = type;}
s481* s1110( s502& m, const wstring& s151 ){
if( m.count( s151 ) > 1 )
throw new s16( L"multiple values: " + s151, (uint32_t)s16::s17::s21 );
auto s680 = m.find( s151 );
if( s680 == m.end() )
throw new s16( L"no such key: " + s151, (uint32_t)s16::s17::s23 );
return s680->second;}
void s665( const std::wstring& s, std::wstring& s1102, std::wstring& s598 ){
size_t pl = s.find( L"::" );
if( pl == string::npos || s.find( L"::", pl + 1 ) != string::npos )
throw new s16( L"unknown format of qualified name: " + s, (uint32_t)s16::s17::s20 );
s1102 = s.substr( 0, pl );
s598 = s.substr( pl + 2 );}
s480::s480( const s480& r ) 
: s270( r ), ns( r.ns ){}
s480::~s480(){}
s480* s480::s493(){
return this;}
void s480::s1944( s1889&) { throw std::logic_error( "from_wstring: not implemented" ); }
wstring s480::s297() const { return ns->s297(); }
wstring s480::s827() const { return ns->s827(); }
wstring s480::s2153() const { return ns->s827(); }
s480* s480::s1524( const s480* p ) const{
if( s349() == p->s349() ) {
s480* s680 = (s480*)p->s332(0,0);
return s680;}
throw new s16( L"no conversion from '" + p->s350() + L"' to '" + s350() + L"'" );}
s480* s480::s352( s271* s585, const std::vector<s1053>& vt ) const{
assert(0);
return 0;}
s1053 s480::s1178( s1889& s1540, const vector<s482>& l ) const{
throw std::logic_error( "9: not implemented" );}
s588* 
s480::s1670( s1889& s671, s588* s214, s271* s1657,
s558* cs ) const{
if( s671 == L"cp" ) {
return new s1666( s299, s1657, s214, &s480::s1688, cs->s599(),
L"cp",	0, cs->s600(), cs->s2165() );}
else if( s671 == L"exec" ) {
return new s1666( s299, s1657, s214, &s480::s1878, cs->s599(), L"exec",
0, cs->s600(), cs->s2165() );}
else if( s671 == L"_META_type" ) {
return new s1666( s299, s1657, s214, &s480::s1922, cs->s599(),
L"_META_type", Types.String,	cs->s600(), cs->s2165() );}
else if( s671 == L"is-def" ) {
return new s1666( s299, s1657, s214, &s480::s2276, cs->s599(),
L"is-def", Types.Bool,	cs->s600(), cs->s2165() );}
else if( s671 == L"undef" ) {
return new s1666( s299, s1657, s214, &s480::s2277, cs->s599(),
L"undef", Types.Null,	cs->s600(), cs->s2165() );}
else if( s671 == L"call" ) {
return new s1666( s299, s1657, s214, &s480::s2311, cs->s599(), L"call",
0, cs->s600(), cs->s2165() );}
return NULL;}
s480* s480::s1688( s480** s273, size_t s495 ){
return (s480*)s332(0,0);}
s480* s480::s1878( s480** s273, size_t s495 ){
return s494( s273, s495 );}
s480* s480::s2311( s480** s273, size_t s495 ){
return s494( s273, s495 );}
s480* s480::s1922( s480** s273, size_t s495 ){
return new s356( s299, s350() );}
s480* s480::s2276( s480** s273, size_t s495 ){
return new s357( s299, s1194() );}
s480* s480::s2277( s480** s273, size_t s495 ){
s1664( s7::s861 );
return s362;}
s480* s480::s1879( s480** s273, size_t s495 ){
return s1880( s273, s495 );}
s480* s480::s1880( s480** s273, size_t s495 ){
throw std::logic_error( "10: not implemented" );}
void s480::s1919( Stream* s1918 ) const{
s1918->s1468( to_wstring() );}
void s480::s1943( Stream* s1918 ){
wstring s;
s1918->s1449( s, string::npos );
s1944( s );}
#define s2297 1000000
vector<wstring> s518::s522 = { s7::s443, s7::s441,
s7::s444, s7::s442 };
s1::s9<s523> s554 = new s523();
size_t s959( const vector<s806::s886>& vt ){
size_t s680 = 0;
for( auto i : vt )
s680 = ( s680 << 7 ) ^ i;
return s680;}
size_t s488::s1048( s1889& s, size_t& pos, s806::Cont& s152 ){
size_t s68 = pos;
size_t s680 = 0;
if( s[s68] == L' ' )
s68 = s.find_first_not_of( s4::s48, s68 );
while( s68 < s.size() && s[s68] != L'>' && s[s68] != L'(' ) {
size_t pl = s.find_first_of( L"< >", s68 );
wstring stype = s4::s52( s.substr( s68, pl - s68 ), s4::s48 );
s1053 s1083 = s1002( stype ); // ???DEBUG??? 220929
s152.push_back( s1083 );
pl = s.find_first_not_of( s4::s48, pl );
s806::Cont s1061;
size_t s1046 = 0;
if( pl != string::npos ) {
if( s[pl] == L'<' ) {
s1046 = s1048( s, ++pl, s1061 );}
else if( s[pl] == L',' ) {
s1046 = 0;}}
s152.push_back( ( s806::s886 ) s1046 );
s152.insert( end( s152 ), begin( s1061 ), end( s1061 ) );
s680++;
if( pl != string::npos )
pl = s.find_first_not_of( s4::s48, pl );
pos = s68 = pl;}
pos++;
return s680;}
wstring s1147( const s806::Cont& s1056, size_t& idx, s488& s903 ){
wstring s680 = s903.s797(s1056[idx++]);
size_t n = (size_t)s1056[idx++];
if( n && s680.back() != L'>' ) {
s680 += L"<" + to_wstring( n ) + L" ";
for( size_t k = 0; k < n; ++k ) {
s680 += ( k ? L" " : L"" ) + s1147( s1056, idx, s903 );}
s680 += L">";}
return s680;}
wstring s488::s1004( const s806::Cont& s1056 ){
assert( s1056.size() );
if( s1056.size() == 1 )
return  s1086[s1056[0]] + L"< 0 >";
size_t idx = 0;
wstring s680;
while( idx < s1056.size() ) {
s680 += s1147( s1056, idx, *this );
if( idx < s1056.size() )
s680 += L" ";}
return s680;}
s1053 s488::s2473( s1889& s1262, s806::Cont& s2241 ){
s806::Cont vt;
size_t pos = 0;
s299->TR().s1048( s1262, pos, vt );
s1053 pt = s299->TR().s1003( s806( vt ), false );
if( !pt )
pt = s299->TR().s1038( vt );
s2121( vt, s2241 );
return pt;}
wstring s488::s1341( s1889& tn ){
wstring sv = tn;
size_t s2110 = sv.find( L"(" );
size_t b = sv.find( L'<' );
size_t e = sv.rfind( L'>', s2110 );
if( b == string::npos || e == string::npos )
return sv;
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' ) {
sv.erase( n--, 1 );
--e;}
return sv;}
void s488::s2103( const s806::Cont& v, size_t& idx, s806::Cont& s152 ){
s152.push_back( v[idx++] );
size_t n = v[idx++];
s152.push_back( (s1053)n );
if( n == 0 )
return;
for( size_t k = 0; k < n; ++k ) {
s2103( v, idx, s152 );}}
void s2087( const s806::Cont& v, size_t& s2101,
s806::Cont& s152 ){
s152.push_back( v[s2101++] );
size_t s2109 = v[s2101++];
s152.push_back( ( s806::s886 ) s2109 );
while( s2109-- ) {
s2087( v, s2101, s152 );}}
void s488::s1000( const s806::Cont& v, vector<size_t>& s2118, 
s806::Cont& s152 ){
size_t s2101 = 1;
size_t s2109 = v[s2101++];
size_t s2098 = 0;
size_t s2095 = s2118[0];
s806::Cont s2115;
assert( s2095 < s2109 );
while( s2098++ <= s2095 ) {
s2115.clear();
s2087( v, s2101, s2115 );}
if( s2118.size() > 1 ) {
vector<size_t> s2116( s2118.begin() + 1, s2118.end() );
s1000( v, s2116, s2115 );}
else
s152 = s2115;}
s806::s806( s730 t1, s730 t2/*=(s730)-1*/, s730 t3/*=(s730)-1*/ )
{
vt.push_back( t1 );
if( t2 != (s730)-1 ) {
vt.push_back( t2 );
if( t3 != (s730)-1 )
vt.push_back( t3 );}
s1085 = s959( vt );}
s806::s806( const s806& right )
: s1085( right.s1085 ){
vt.assign( right.vt.begin(), right.vt.end() );}
s806::s806( const Cont& v ) 
: vt( v ) {
s1085 = s959( vt );}
s806::s886 s806::s349( size_t n/* = 0*/ ) const
{
if( vt.empty() )
return 0;
return vt.size() ? vt[n] : 0;}
void s806::s348( s730 t ){
vt.clear();
vt.push_back( t );}
void s806::s348( s918 pt ){
vt.clear();
vt.assign( pt->vt.begin(), pt->vt.end() );}
void s806::s778( s730 t ){
vt.push_back( t );}
void s806::s778( s918 pt ){
vt.insert( vt.end(), pt->vt.begin(), pt->vt.end() );}
void s806::s812( std::vector<s270*>& s152 ) const{
for( size_t n = 0; n < vt.size(); ++n )
s152.push_back( new s343( NULL, (int)vt[n] ) );}
inline bool s806::operator==( const s806& p ) const{
size_t sz1 = vt.size();
size_t sz2 = p.vt.size();
if( sz1 != sz2 )
return false;
s730* pvt1 = (s730*)&vt[0];
s730* pvt2 = (s730*)&p.vt[0];
for( size_t s679 = 0; s679 < sz1; ++s679 )
if( pvt1[s679] != pvt2[s679] )
return false;
return true;}
s488::s488( s261* pass_ ) 
: s299( pass_ ){
reset();}
void s488::s289(){
for( size_t n = 0; n < s1103.size(); ++n ) {
if( s1103[n] ) {
s1103[n]->s347();}}}
void s488::s514( const s479& st ){}
void s488::reset() {
s1103.clear(); 
s1086.clear();
s1091.clear();
s1087.clear();
s2308.clear();
s1092.clear();
s910.clear();
s885.clear();
s1248.clear();
s1263.clear();
s1539.clear();
s2305 = s2297;
s1103.push_back( NULL ); 
s1086.push_back( L"" );
s1091.push_back( 0 );
s885[s7::s2299] = 1;
s1248[1] = s7::s2299;
s1087[s7::s2299] = s2305++;
s2302.push_back( s7::s2299 );
s1195 = 1;
s1263.push_back( 0 );
s1539.push_back( vector<s1053>() );
srand( (unsigned int)time(NULL) );}
s1053 s488::s217( s480* p, s1889& s344 ){
if( s1087.find( s344 ) != s1087.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1086.push_back( s344 );
s1103.push_back( p );
s1053 s1083 = (s1053)s1086.size() - 1;
s1091.push_back( s806( s1083 ) );
p->s348( s1083 );
s1087[s344] = s1083;
s1092[s1091.back()] = s1083;
s1263.push_back( 1 );
s1539.push_back( vector<s1053>() );
return s1083;}
void s488::s1651( s1889& s344 ){
auto it = s1087.find( s344 );
if( it == s1087.end() )
throw new s16( (uint32_t)s16::s17::s23 );
s1053 s1083 = it->second;
s1087.erase( it );
s1103[s1083] = NULL;
s1086[s1083] = L"";
s1092.erase( s1091[s1083] );
s1091[s1083] = s806();
s1263[s1083] = 0;
s1539[s1083-1].clear();}
s1053 s488::s1060( const s806::Cont& v, s1889& s344 ){
s806 vt( v );
if( s1092.find( vt ) != s1092.end() )
throw new s16( (uint32_t)s16::s17::s21 );
s1086.push_back( s344 );
s1091.push_back( vt );
s1053 s1083 = (s1053)s1086.size() - 1;
s1087[s344] = s1083;
s1092[s1091.back()] = s1083;
s1092[s806( s1083 )] = s1083;
s1263.push_back( s1263[vt.s349( 0 )] );
s1539.push_back( vector<s1053>() );
s1103.push_back( s1103[vt.s349( 0 )] );
size_t s2296 = s1103.size();
s1103[s2296-1] = s1103[s1083]->s352( s299, v );
return s1083;}
void s488::s2121( const s806::Cont& v, s806::Cont& s152, size_t s2101  ){
assert( v.size() );
s152.push_back( v[0] );
if( !s2101 ) s2101 = 1;
size_t s2109 = v[s2101++];
s152.push_back( (s1053)s2109 );
size_t s2098 = 0;
s806::Cont s2115;
while( s2098++ < s2109 ) {
s2115.clear();
s2087( v, s2101, s2115 );
s1053 s2120 = 0;
if( s2115.size() == 2 && s2115[1] == 0 )
s2120 = s2115[0];
else
s2120 = s1038( s2115 );
s152.push_back( s2120 );
s152.push_back( 0 );}}
s1053 s488::s1038( const s806::Cont& v_ ){
s806::Cont v;
s2121( v_, v );
s806 vt( v );
s1053 s680 = 0;
auto it = s1092.find( vt );
if( it == s1092.end() ) {
wstring s1081 = s1004( v );
s680 = s1060( v, s1081 );}
else
s680 = it->second;
return s680;}
uint32_t s1183( uint32_t n ){
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
traitnum_t s488::s1241( s1889& trait, s1053& s1498 ){
auto it = s885.find( trait );
if( it != end( s885 ) )
return it->second;
s1195 = s1183( s1195 );
s885[trait] = s1195;
s1248[s1195] = trait;
s1498 = s7::s1541 + (s1053)s1499.size();
s1499.push_back( s1195 );
s1087[trait] = s2305++;
s2302.push_back( trait );
return s1195;}
void s488::s1152( s806::s886 type, s1889& trait, s1053& s1498 ){
traitnum_t tn;
auto it = s885.find( trait );
if( it == end( s885 ) ) {
tn = s1241( trait, s1498 );
s1263[type] *= tn;}
else {
tn = it->second;
if( !s1188( type, tn ) )
s1263[type] *= tn;}}
traitnum_t s488::s1446( s1053 alias ) const{
return s1499[alias - s7::s1541];}
bool s488::s1188( s1053 s616, traitnum_t tra ) {
assert( s616 && s616 < s1091.size() );
double d = (double)s299->TR().s1145( s616 ) / tra;
return ( d == (int)d );}
bool s488::s1453( s1053 s616, s1053 alias ) {
assert( s616 && s616 < s1091.size() );
double d = (double)s299->TR().s1145( s616 ) /
s1499[alias-s7::s1541];
return ( d == (int)d );}
void s488::s1521( s1053 s616, s1053 is ){
s1539[s616].push_back( is );}
bool s488::s1522( s1053 s616, s1053 is ){
if( s616 == is )
return true;
if( s616 >= s1539.size() )
return false;
std::vector<s1053>& v = s1539[s616];
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n] == is )
return true;}
return false;}
bool s488::s1522( const s270* s616, const s270* is ){
if( !s1522( s616->s349(), is->s349() ) ) {
if( !s616->s498( (s480*)is ) ) {
s1053 pt = is->s349();
if( is->s349() == Types.No )
pt = (s1053)( (s381*)is )->s1528();
auto it = s2308.find( pt );
if( it != s2308.end() ) {
if( it->second->s491() == s474 ) {
s482 tmp = s270::s1010( s299, s299, s299, NULL, L"::", false );
s2308[pt] = tmp.s15<s831*>();
it = s2308.find( pt );}
if( !it->second->s1194() )
it->second->s497( s299, false );
vector<s482> s273 = { (s270*)s616 };
it->second->s593( s273 );
if( (bool)*it->second->s494( 0, 0 ) )
return true;}
return false;}}
return true;}
void s488::s1161( s1889& alias, s1889& s344, s1889& s1825 ){
assert( s1087.find( alias ) == end( s1087 ) );
s1053 typid;
auto it = s1087.find( s344 );
if( it == s1087.end() ) {
s806::Cont vt;
size_t pos = 0;
s1048( s344, pos, vt );
if( vt[0] == s1700 ) {
s1053 et_, kt_, vt_;
s321* s2207 = (s321*)s999( s1700 );
typid = s2207->s1185( s2207, s344, s1700, vt, et_, kt_, vt_ );}
else
typid = s1038( vt );}
else
typid = it->second;	
s1086.push_back( alias );
s1103.push_back( s1103[typid] );
s1091.push_back( s1091[typid] );
s1263.push_back( s1263[typid] );
s1539.push_back( s1539[typid-1] );
s1087[alias] = typid;
auto it1 = s1826.find( s1825 );
if( it1 == s1826.end() )
it1 = s1826.insert( make_pair( s1825, list<wstring>() ) ).first;
it1->second.push_back( alias );}
void s488::s2303( s1889& def, s831* pred, s1889& s1825 ){
if( s1087.find( def ) != end( s1087 ) )
throw new s16( L"type definition already exists" );
s1053 typid;
typid = s2305++; //(s1053)s1086.size();
s2308[typid] = pred;
s1087[def] = typid;
s2302.push_back( def );
auto it1 = s1826.find( s1825 );
if( it1 == s1826.end() )
it1 = s1826.insert( make_pair( s1825, list<wstring>() ) ).first;
it1->second.push_back( def );}
void s488::s1862( s1889& s1102 ){
auto it = s1826.find( s1102 );
if( it != s1826.end() ) {
for( auto it1 = it->second.begin(); it1 != it->second.end(); ++it1 ) {
s1087.erase( *it1 );}}}
wstring s488::s1264( s1889& tn_, s1889& s1102 ){
wstring s = tn_.substr(0, tn_.find_first_of( L" (" ));
auto it = s1087.find( s );
if( it == end( s1087 ) )
return tn_;
const wstring& tn = s1086[s1092[s1091[it->second]]];
if( tn != s ) {
auto it1 = s1826.find( s1102 );
if( it1 != end( s1826 ) ) {
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() ) {
it1 = s1826.find( L"::" );
if( std::find( it1->second.begin(), it1->second.end(), s ) == it1->second.end() )
return tn_;}}
wstring s680 = tn_;
return s680.replace( 0, s.size(), tn );}
return tn_;}
s480* s488::s515( const s262& s694, s271* s585, s1889& s516 ){
if( s694.s1298() )
return s1103[s694.s1298()]->s351( s694, s585, s516 );
wstring s346 = s694.s290();
if( s346.substr(0,2) == L"[[" && s951::s2161( s346 ) )
return s1103[s1087[Types( s299, Types.Tuple )->s350()]]->s351( s694, s585, s516 );
else if( s346[0] == L'[' )
return s1103[s1087[Types( s299, Types.Vector )->s350()]]->s351( s694, s585, s516 );
else if( s346.find( L"UVector[" ) == 0 )
return s1103[s1087[Types( s299, Types.s741 )->s350()]]->s351( s694, s585, s516 );
else if( s346[0] == L'{' )
return s1103[s1087[Types( s299, Types.Index )->s350()]]->s351( s694, s585, s516 );
else if( s346.find( L"typealias" ) == 0 ) {
size_t pl = s346.find( L"(" );
wstring s344 = s4::s52( s346.substr( pl + 1, s346.size() - pl - 2 ), s4::s48 );
s1161( s694.s298(), s344, s516 );
return s1103[s1087[Types( s299, Types.String )->s350()]]->s351( s694, s585, s516 );}
else if( s346.find( L"typedef" ) == 0 ) {
size_t pl = s346.find( L"(" );
wstring s344 = s4::s52( s346.substr( pl + 1, s346.size() - pl - 2 ), s4::s48 );
s939 ast1 = new s262( s344, NULL, NULL );
size_t pos = 0;
ast1->s268( s2298, s140( NULL, L"true,", pos, s1721 ) );
s2303( s694.s298(), 
(s831*)s1103[s1087.find( L"Lambda" )->second]->s351( *ast1, s585, s516 ),
s516 );
return s1103[s1087[Types( s299, Types.String )->s350()]]->s351( s694, s585, s516 );}
wstring s344 = L"";
s480* s680 = NULL;
if( s4::s87.find( s346[0] ) != string::npos )
s344 = s356( s299 ).s350();
else if( isdigit( s346[0] ) || s346[0] == L'-' )
return s333::s342( s299, s346, s516 );
else if( ( s680 = s1103[s1138]->s351( s694, s585, s516 ) ) )
return s680;
else {
size_t pl = s346.find_first_of( L"(<" );
if( pl != 0 && pl != string::npos ) {
s344 = s346.substr( 0, pl );}
else if( pl == string::npos )
s344 = s346;}
auto it = s1087.find( s344 );
if( it == s1087.end() )
throw new s16( L"Type does not exist: " + s346, (uint32_t)s16::s17::s23 );
if( it->second >= s2297 ) {
auto it1 = s885.find( s344 );
if( it1 != end( s885 ) )
return new s381( s299, s585, it1->second, s1235 );
auto it2 = s2308.find( it->second );
if( it2 != s2308.end() ) {
return new s381( s299, s585, it->second, s2306 );}
throw new s16( L"Type does not exist: " + s346, (uint32_t)s16::s17::s23 );}
return s1103[it->second]->s351( s694, s585, s516 );}
s480* s488::s515( s1053 s337, s271* s585, s1889& s516 ){
if( s337 >= s7::s1541 ) {
auto it = s1248.find( s337 - s7::s1541 );
if( it != end( s1248 ) )
return new s381( s299, s585, it->first, s1235 );}
if( !s337 || s337 >= s1086.size() )
throw new s16( L"no type with such id: " + to_wstring( s337 ) );
s1053 type = s337;
if( s1091[type].s349() != type )
type = s1091[type].s349();
if( s1091[s337].s812().size() == 1 )
return s1103[type]->s352( s585 ); 
else
return s1103[type]->s352( s585, s1091[s337].s812() );}
const s480* s488::get( s1889& s76, bool s517/*= true*/ ) const
{
wstring s344 = s76;
size_t pl = s76.find( L"<" );
if( 0 && pl != 0 && pl != string::npos && s76.find( L"0" ) == string::npos )
s344 = s76.substr( 0, pl );
auto s680 = s1087.find( s344 );
if( s680 == s1087.end() ) {
if( s517 )
throw new s16( L"1: symbol not found: " + s76 );
else
return NULL;}
if( s680->second >= s2297 )
return NULL;
return s1103[s680->second].s15<const s480*>();}
bool s488::s155( s1889& s76 ) const{
if( s1087.find( s76 ) == s1087.end() )
return false;
return true;}
const wstring& s488::s797( s1053 n ) const{
if( n >= s1086.size() && n > s2297 && (n - s2297) > s2302.size() )
throw new s16( L"no type with such ordinal: " + std::to_wstring( n ) );
if( n < s2297 )
return s1086[n];
return s2302[n - s2297];}
s1053 s488::s1002( s1889& s344, bool s517 ) const{
auto it = s1087.find( s344 );
if( it == s1087.end() ) {
if( s517 )
throw new s16( L"no such type: " + s344,
(uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
s1053 s488::s1003( const s806& vt, bool s517 ) const{
auto it = s1092.find( vt );
if( it == end( s1092 ) ) {
if( s517 )
throw new s16( (uint32_t)s16::s17::s23 );
else
return 0;}
return it->second;}
const s806& s488::s1005( s1053 t ) const{
assert( t && t < s1091.size() );
return s1091[t];}
const s480* s488::s999( s806::s886 t ) const{
assert( t && t < s1091.size() );
return s1103[t].s15<const s480*>();}
void s488::s783(){
size_t s740 = s333::s800() + 1;
for( size_t n = s740; n < s1086.size(); ++n ) {
s1087.erase( s1086[n] );
s1092.erase( s1091[n] );
s910.erase( (s1053)n );}
s1086.erase( s1086.begin() + s740, s1086.end() );
s1103.erase( s1103.begin() + s740, s1103.end() );
s1091.erase( s1091.begin() + s740, s1091.end() );}
bool s488::s1238(){
return rand() % 2;}
double s488::s1240(){
return rand() / RAND_MAX;
}
int s488::s1246(){
return rand();}
void s488::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s196 ) << L"Types :" << endl;
for( size_t n = 0; n < s1086.size(); ++n ) {
buf << s4::fill_n_ch( L' ', s196 + 5 ) << s1086[n] << endl;
s1103[n]->s303( pd, s196 + 10 );}}
s479::s479( const s479& right )
: s550( right.s550 ), s534( right.s534 ), s536( right.s536 ){}
s479::~s479(){
s550.clear();}
void s479::s497( s271* s872, s271* s585, bool s513/*= true*/ )
{
for( auto sym : s550 ) {
if( sym.second->s491() != s473 && sym.second->s491() != s2149 
&& !( s585 && s585->s491() == s477 && sym.second->s491() == s1234 ) // ???DEBUG??? 220711
) {
try {
sym.second->s497( s872 );}
catch( TDException* e ) {
e->s1068( TDException::Stage::s1018 );
s1006.s963( e->Msg( 0 ) );
continue;}}}
if( s1006.s927() )
return;
if( 0 && s513 ) {// ???DEBUG??? 220710
for( auto sym : s550 ) {
if( sym.second->s491() == s473 )
sym.second.s15<Transd*>()->s497( s872, false );}}}
void s548::s1636( s261* s299 ){
for( auto sym : s556 ) {
if( sym.find( L"::" ) == string::npos )
s299->s1637( sym );}}
void s479::reset(){
s550.clear();}
void s479::copy( s479& t, s271* s585, s588* s584, s144 ap ) const{
t.s536 = s536;
for( s532::const_iterator it = s550.begin(); it != s550.end(); ++it ) {
if( it->second->s491() != s473 ) {
s270* p = it->second->s332( s584, s585 );
t.s538( it->first, p, ap );}}
for( s532::const_iterator it = s550.begin(); it != s550.end(); ++it ) {
if( it->second->s491() == s473 ) {
s588::s560 ct = it->second.s15<Transd*>()->s857();
s588* ptr = NULL;
if( ct == s588::s565 || ct == s588::s564 )
ptr = (s588*)it->second->s332( s584, s585 );
else if( ct == s588::s563 )
ptr = new s834( *( s834* )&( *it->second ), s584, s585 );
else
ptr = (s588*)it->second->s332( s584, s585 );
t.s538( it->first, ptr, ap );}}}
void s479::s545( s479& t ) const{
for( s532::const_iterator it = s550.begin(); it != s550.end(); ++it ) {
if( it->second->s491() == s473 )
t.s538( it->first, it->second.s15<s270*>() );
else
t.s538( it->first, it->second->s332(0,0) );}}
void s479::s1600( s479& t ) const{
for( s532::const_iterator it = s550.begin(); it != s550.end(); ++it ) {
if( it->second->s491() != s473 ) {
auto it1 = t.s550.find( it->first );
if( it1 == end( t.s550 ) )
t.s550[it->first] = it->second;
else
it->second.s15<s480*>()->s353( it1->second.s15<s270*>() );}}}
bool s479::s535( s1889& s76, s144 ap /*= s145*/ )
{
if( s550.find( s76 ) != s550.end() ) {
wstring rep = s7::s418 + L" name already exists: " + s76;
if( ap == s145 || ap == s531 ) {
if( ap == s145 )
throw new TDException( 0, s1656, NULL, s76 );
return false;}
else if( ap == s147 ) {
return false;}}
return true;}
void s479::s538( s1889& s76, s270* sym, s144 ap/*= s145*/ )
{
if( (ap == s146) || s535( s76, ap ) )
s550[s76] = sym;}
void s479::s538( s1889& s76, s141 s346, s144 ap/*= s145*/ )
{
throw new s16( (uint32_t)s16::s17::s21 );}
void s479::s539( const std::wstring& s76 ){
auto it = s550.find( s76 );
if( it == s550.end() )
return;
s550.erase( it );}
void s479::s540( const s6::s142& s79, s144 ap/*= s145*/ )
{
vector<pair<wstring, s141>> s143;
s79.s159( s143 );
for( size_t n = 0; n < s143.size(); ++n )
s538( s143[n].first, s143[n].second );}
bool s479::s155( s1889& s76 ) const{
if( s550.find( s76 ) == s550.end() )
return false;
return true;}
s480* s479::get( s1889& s76, bool s517/*= true*/ ) const
{
auto s680 = s550.find( s76 );
if( s680 == s550.end() ) {
if( s517 )
throw new s16( L"2: symbol not found: " + s76 );
else
return NULL;}
return s680->second.s15<s480*>();}
void s479::s543( std::vector<std::wstring>& s152 ) const{
for( auto sym : s550 )
s152.push_back( sym.first );}
void s479::s541( vector<wstring>& s152 ) const{
for( auto sym : s550 ) {
if( sym.second->s491() == s473 )
s152.push_back( sym.first );}}
void s479::s542( vector<wstring>& s152 ) const{
for( auto sym : s550 ) {
if( sym.second->s491() == s471 ||
sym.second->s491() == s477 || sym.second->s491() == s476 )
s152.push_back( sym.first );}}
void s479::s544( const s479& t,
vector<wstring>& s152 ) const{
for( auto sym : s550 ) {
if( t.s155( sym.first ) )
s152.push_back( sym.first );}}
bool s479::implements( const s479& t ) const{
for( auto sym : t.s550 ) {
if( !s155( sym.first ) )
return false;}
return true;}
void s479::s288( const s479& t, s144 ap /*= s145*/ )
{
if( ap != s146 ) 
for( auto sym : t.s550 )
s535( sym.first, ap );
for( auto sym : t.s550 )
s538( sym.first, sym.second.s15<s480*>(), ap );}
void s479::s546( s509 pv, s262* s79 ){
if( !s536 )
s536 = new s523();
s536->s526( pv, s79 );}
void s479::s530( s1889& s331, vector<wstring>& s152 ){
for( s532::iterator it = s550.begin(); it != s550.end(); ++it ) {
s509 pv = s510;
if( s536 )
pv = s536->s529( it->first, s331 );
if( pv == s510 ) {
if( s534 == s506 )
pv = s511;
else if( s534 == s508 )
pv = s512;
else {
if( it->second->s491() == s473 )
pv = s511;
else
pv = s512;}}
if( pv == s511 )
s152.push_back( it->first );}}
bool s479::s547( s1889& s277,	s1889& s331 ) const{
if( s536 ) {
s509 pv = s536->s529( s277, s331 );
if( pv == s511 )
return true;
else if( pv == s510 ) {
if( s534 == s506 )
pv = s511;
else if( s534 == s508 )
pv = s512;
else {
auto it = s550.find( s277 );
if( it == s550.end() )
throw new s16( L"1: Symbol does not exist: " + s277 );
size_t cat = it->second->s491();
if( cat == s473 || cat == s475 || cat == s477 )
return true;}}
return false;}
return true;}
size_t s479::s319() const{
s532::const_iterator it = s550.begin();
size_t s680 = 1;
for( ; it != s550.end(); ++it ) {
if( it->first[0] != '@' && it->second->s491() != s473 
&& it->second->s491() != s1234 ) {
size_t h = it->second.s15<s480*>()->s319();
if(!h) h = 501316864073;
s680 = s680 * h << 1;}}
return s680;}
bool s479::compare( const s532& r ) const{
if( r.size() != s550.size() )
return false;
s532::const_iterator it = s550.begin();
for( ; it != s550.end(); ++it ) {
auto s2225 = r.find( it->first );
if( s2225 == r.end() )
return false;
if( !it->second.s15<s480*>()->operator==( s2225->second.s15<s480*>() ) )
return false;}
return true;}
void s479::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Symbols :" << endl;
s532::const_iterator it = s550.begin();
for( ; it != s550.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << it->first << L" :" << endl;
if( it->second.s14() ) {
it->second->s303( pd, s196 + s416 * 2 );
buf << endl;}}}
wstring s479::to_wstring( uint32_t s1552 ) const{
std::wostringstream buf;
buf << endl << s4::fill_n_ch( L' ', 0 ) << L"Symbols :" << endl;
s532::const_iterator it = s550.begin();
for( ; it != s550.end(); ++it ) {
buf << s4::fill_n_ch( L' ', s416 ) << it->first << endl;
if( it->second.s14() ) {
it->second->s303( &buf, s416 * 2 );
buf << endl;}}
return buf.str();}
s548::s548(){}
void s548::s497( s261* s299, s1889& s555 ){
s331 = s555;
for( size_t n = 0; n < s556.size(); ++n ) {
wstring s76 = s556[n];
vector<wstring> s152;
s299->s218( s76, s555, s152 );
for( size_t m = 0; m < s152.size(); ++m ) {
s76 = s76.substr( 0, s76.find( L"::" ) );
s550.insert( make_pair( s152[m], make_pair( (s480*)s299->s638( 
s556[n],	s555 ), s76) ) );}}}
void s548::s552( s1889& s76, s261* s299, s1889& s555 ){
s556.push_back( s76 );
vector<wstring> s152;
s299->s218( s76, s555, s152 );
for( size_t n = 0; n < s152.size(); ++n )
s550.insert( make_pair( s152[n], make_pair( (s480*)s299->s638( 
s76,	s555 ), s76 ) ) );}
void s548::s551( s1889& s ){
if( s[0] != L'"' || s[s.size() - 1] != L'"' )
throw new s16( L"Unrecognized import syntax: " + s );
s556.push_back( s.substr(1, s.size() - 2 ) );}
bool s548::s2162( s1889& s76 ){
if( std::find( begin( s556 ), end( s556 ), s76 ) !=
end( s556) )
return true;
return false;}
bool s548::s553( s1889& sym, s368* ref ){
wstring mod, mem;
size_t pl = sym.rfind( L"::" );
if( pl != string::npos ) {
mod = sym.substr( 0, pl );
mem = sym.substr( mod.size() + 2 );}
else
mem = sym;
size_t s679 = s550.count( mem );
if( !s679 )
return false;
if( s679 > 1 && mod.empty() )
throw new s16( L"ambiguous name: " + sym + L" - the symbol is contained in more than one "
"imported modules. Try to use a qualified name." );
auto range = s550.equal_range( mem );
if( s679 == 1 && mod.empty() ) {
s480* pd = range.first->second.first;
if( pd->s491() == s476 || pd->s491() == s475 )
return pd->s553( mem, ref, s331, true );
ref->s380( (s480*)pd->s500() );
ref->s379( pd );
return true;}
for( auto it = range.first; it != range.second; ++it ) {
if( it->second.second == mod /*sym*/ ) {
s480* pd = it->second.first;
if( pd->s491() == s476 )
return pd->s553( mem, ref, L"", true );
ref->s380( (s480*)pd->s500() );
ref->s379( pd );
return true;}}
return false;}
void s548::copy( s548& t ) const{
for( s532::const_iterator it = s550.begin(); it != s550.end(); ++it )
t.s550.insert( make_pair( it->first, it->second ) );}
s518::s518( s509 pv_, const vector<wstring>& s520 )
: pv( pv_ ){
for( auto p : s520 ) {
if( p.empty() )
throw new s16( L"empty values in permissions list are not allowed" );
if( p[0] == L'"' ) {
if( p.size() < 3 || p[p.size()-1] != L'"' )
throw new s16( L"unmatched quotes in a value in permission list" );
p = p.substr( 1, p.size() - 2 );}
s519.push_back( p );}}
s518::s518( s1889& ag_, s1889& s77 ){}
s509 s518::s557( s1889& s496 ) const{
for( size_t n = 0; n < s519.size(); ++n )
if( s519[n] == s496 || s519[n] == L"_" )
return pv;
if( pv == s512 )
return s511;
return s512;}
void s523::s526( s509 pv, s262* s694 ){
s262::s274& s695 = s694->s292();
s262::s274::iterator it = s695.begin();
for( ; it != s695.end(); ++it ) {
wstring l = it->second->s290().substr( 1, it->second->s290().size() - 2 );
vector<wstring> s152;
wstring s72( s1108, 1 );
s4::s57( l, s72, s152 );
s525[it->first] = new s518( pv, s152 );}}
void s523::s527( s1889& s, s518& pl ){}
void s523::s528( s1889& s, s1889& s521 ){}
s509 s523::s529( s1889& mem, s1889& s496 ){
s524::iterator it = s525.find( mem );
if( it == s525.end() )
return s510;
return it->second->s557( s496 );}
s1984 Types;
s1053 s1500::s1260 = 0;
s1053 s1500::s1537 = 0;
s333::s338 s381::s345;
s333::s338 s361::s345;
s333::s338 s358::s345;
s333::s338 s357::s345;
s333::s338 s343::s345;
s333::s338 s355::s345;
s333::s338 s1292::s345;
s333::s338 s1517::s345;
s333::s338 s2310::s345;
s333::s338 s1284::s345;
s333::s338 s1560::s345;
s333::s338 s1589::s345;
s333::s338 s356::s345;
s333::s338 s313::s345;
s333::s338 s743::s345;
s333::s338 s951::s345;
s333::s338 s321::s345;
s333::s338 s1370::s345;
s333::s338 s1281::s345;
s333::s338 s412::s345;
s333::s338 s382::s345;
s333::s338 s1124::s345;
s333::s338 s943::s345;
s333::s338 s1133::s345;
s333::s338 s1691::s345;
s333::s338 s647::s345;
s333::s338 s1786::s345;
s333::s338 s504::s345;
s333::s338 s1283::s345;
s333::s338 s1291::s345;
s333::s338 s1390::s345;
s333::s338 s1392::s345;
s333::s338 s2046::s345;
s333::s338 s2203::s345;
s333::s338 s2236::s345;
size_t s333::s751 = 0;
s9<s361> s362;
s9<s381> s865;
s9<s381> s363;
s9<s381> s364;
s9<s381> s365;
s9<s381> s866;
s9<s381> s1671;
s9<s381> s2130;
s9<s357> s366;
s9<s357> s367;
s9<s1390> s1391;
s9<s1392> s1393;
s9<s381> s1509;
template <class charT, charT s72>
class punct_facet : public std::numpunct<charT>{
protected:
charT do_decimal_point() const { return s72; }
};
std::locale exprloc;
static s6::s1694 s1743;
s1705 s1723;
s6::s1680 s1721;
const s480* s1984::operator()( s261* s299, s1053 tp ){
return s299->TR().s999( tp );}
void s333::s777( s261* s299, bool soft/*= false*/ )
{
setlocale( LC_NUMERIC, "C" );
Types.No = s299->s217( new s381( s299 ), L"NoValue" );
Types.Null = s299->s217( new s361( s299 ), L"Null" );
Types.s358 = s299->s217( new s358( s299 ), L"Exception" );
Types.Bool = s299->s217( new s357( s299 ), L"Bool" );
Types.Int = s299->s217( new s343( s299 ), L"Int" );
Types.Double = s299->s217( new s355( s299 ), L"Double" );
Types.Long = s299->s217( new s1292(s299), L"Long" );
Types.s1516 = s299->s217( new s1517( s299 ), L"ULong" );
Types.s2309 = s299->s217( new s2310( s299 ), L"BigLong" );
Types.Byte = s299->s217( new s1284( s299 ), L"Byte" );
Types.Char = s299->s217( new s1560( s299 ), L"Char" );
Types.s271 = s299->s217( new s1589( s299 ), L"Object" );
Types.Position = s299->s217( new s1133( s299 ), L"Position" );
Types.DateTime = s299->s217( new s1691( s299 ), L"DateTime" );
Types.Vector = s299->s217( new s313( s299 ), L"Vector" );
Types.s741 = s299->s217( new s743( s299 ), L"UntypedVector" );
Types.Tuple = s299->s217( new s951( s299 ), L"Tuple" );
Types.Set = s299->s217( new s2203( s299 ), L"Set" );
Types.HashSet = s299->s217( new s2236( s299 ), L"HashSet" );
Types.Index = s299->s217( new s321( s299 ), L"Index" );
Types.HashIndex = s299->s217( new s1370( s299 ), L"HashIndex" );
Types.ByteArray = s299->s217( new s1281( s299 ), L"ByteArray" );
Types.s411 = s299->s217( new s412( s299 ), L"Directory" );
Types.Range = s299->s217( new s382( s299 ), L"Range" );
Types.Filter = s299->s217( new s1124( s299 ), L"Filter" );
Types.Seq = s299->s217( new s943( s299 ), L"Seq" );
Types.Table = s299->s217( new s1786( s299 ), L"Table" );
Types.TSDBase = s299->s217( new s647( s299 ), L"TSDBase" );
Types.s782 = s299->s217( new s504( s299 ), L"StringStream" );
Types.ByteStream = s299->s217( new s1283( s299 ), L"ByteStream" );
Types.FileStream = s299->s217( new s1291( s299 ), L"FileStream" );
Types.Lambda = s299->s217( new s831( s299 ), L"Lambda" );
Types.String = s299->s217( new s356( s299 ), L"String" );
if( !soft )
s751 = Types.String;
if( s362.s13() ) {
s362 = new s361( s299 );
s865 = new s381( s299, NULL, s478 );
s365 = new s381( s299, NULL, s478 );
s364 = new s381( s299, NULL, s478 );
s363 = new s381( s299, NULL, s478 );
s866 = new s381( s299, NULL, s478 );
s1671 = new s381( s299, NULL, s478 );
s2130 = new s381( s299, NULL, s478 );
s366 = new s357( s299, true );
s367 = new s357( s299, false );
s865->s1664( s7::s859 );
s365->s1664( s7::s435 );
s364->s1664( s7::s436 );
s363->s1664( s7::s437 );
s366->s1249();
s367->s1249();
s1509 = new s381( s299, NULL, Types.Int, s1235 );
s1721.s150 = true;
s1721.s1717 = true;
s1721.s1685 = true;
s1721.s1684 = true;
s1721.s1686 = true;}}
s1112::s1112( const std::vector<s482>& v, s333* s589 )
:s585( s589 ){
for( size_t n = 1; n < v.size(); ++n ) {
if( v[n]->s491() != s1055 ) {
s905.push_back( v[n] );
s1267.push_back( v[n]->s349() );}
else if( n > 1 )
break;}}
bool s1112::operator==( const s1112& s521 ) const{
bool pend = s1267.empty();
bool send = s521.s1267.empty();
s1053 starred = 0;
size_t n = 0, k = 0;
bool s1259 = true;
s488* ptr = s521.s585 ? &s521.s585->Pass()->TR() : NULL;
while( !send || !pend ) {
if( send && !starred ) // ???DEBUG??? 220821
return false; // ???DEBUG??? 220920
s1259 = false;
s1053 s1167 = starred ? starred : (pend ? 0 : s1267[k]);
s1053 s1164 = send ? (s521.s1267.empty() ? 0 : s521.s1267[n-1]) : s521.s1267[n];
s270* s1525 = send ?
( s521.s905.empty() ? NULL : s521.s905[n - 1].s15<s270*>() ) :
s521.s905[n].s15<s270*>();
if( s1164 == Types.No )
s1164 = send ? s521.s905[n-1].s15<s381*>()->s1528() : 
s521.s905[n].s15<s381*>()->s1528();
const s806* s1270 = s521.s585 ? &s521.s585->s1186() : NULL;
if( s1167 >= s7::s1387 && s1167 < s7::s1541 && s1164 ) {
if( s1167 == s7::s1381 )
s1259 = true;
else if( s1167 == s7::s1386 ) {
s1053 pt1_ = s521.s905[n]->s1186().s349();
if( pt1_ == s1701 /*&& pt2_ == Types.Bool*/ )
s1259 = true;}
else if( s1167 == s7::s1382 ) {
if( s521.s585 && s1164 == s521.s585->s349())
s1259 = true;}
else if( s1167 == s7::s1383 ) {
if( s521.s585 && s1164 == ( (s323*)s521.s585 )->s316() )
s1259 = true;}
else if( s1167 == s7::s1383 ) {
if( s521.s585 && s1164 == ((s323*)s521.s585)->s316() )
s1259 = true;}
else if( s1167 == s7::s1384 ) {
if( s521.s585 && s1164 == ((s323*)s521.s585)->s930() )
s1259 = true;}
else if( s1167 == s7::s1385 ) {
if( s521.s585 && s1525->s1529( ((s323*)s521.s585)->ValType() ) )
s1259 = true;}
else if( s1270 &&	s1164 == s1270->s349( (size_t)((int)0 - s1167 )) )
s1259 = true;}
else if( s1167 >= s7::s1541 && ptr ) {
traitnum_t s1501 = ptr->s1446( s1167 );
if( s1164 && ptr->s1188( s1164, s1501 ) )
s1259 = true;}
else {
if( s1525 && s1525->s1529( s1167 ) )
s1259 = true;}
if( s1259 ) {
if( !send )
n++;}
else {
if( !starred )
return false;
else 
starred = 0;}
if( n == s521.s1267.size() ) {
send = true;
starred = 0;}
if( !starred && !pend ) {
k++;}
if( k == s1267.size() )
pend = true;
if( !starred && !pend && s1267[k] == s7::s1387 )
starred = s1267[k - 1];}
return s1259;}
bool s1112::operator<( const s1112& s521 ) const{
if( s1267.empty() ) return s521.s1267.size() > 0;
if( s521.s1267.empty() ) return false;
const s806* s1269 = s585 ? &s585->s1186() : NULL;
const s806* s1270 = s521.s585 ? &s521.s585->s1186() : NULL;
s1053 s1257 = 0, s1258 = 0;
s488* ptr = s521.s585 ? &s521.s585->Pass()->TR() : NULL;
for( size_t n = 0; /*n < s1267.size() && n < s521.s1267.size()*/; ++n ) {
if( s1267.size() == n )
return s521.s1267.size() > n;
if( s521.s1267.size() == n )
return false;
s1053 s1166 = s1257 ? s1257 : s1267[n];
s1053 s1168 = s1258 ? s1258 : s521.s1267[n];
if( s1166 >= s7::s1387 && s1166 <= s7::s1541 ) {
if( s1166 == s7::s1387 )
s1166 = s1257 = s1267[n - 1];
else if( s1166 == s7::s1381 )
continue;
else if( s1166 == s7::s1382 ) {
if( !s521.s585 )
return true;
s1166 = s521.s585->s349();}
else if( s1166 == s7::s1383 ) {
if( !s521.s585 )
return true;
s1166 = ( (s323*)s521.s585 )->s316();}
else if( s1269 )
s1166 = s1269->s349( (size_t)(int)0 - s1166 );}
else if( s1166 >= s7::s1541 && ptr ) {
traitnum_t s1501 = ptr->s1446( s1166 );
if( ptr->s1188( s1168, s1501 ) )
return true;}
if( s1168 >= s7::s1387 && s1168 <= s7::s1541 ) {
if( s1168 == s7::s1387 )
s1168 = s1258 = s521.s1267[n - 1];
else if( s1168 == s7::s1381 )
continue;
else if( s1168 == s7::s1382 ) {
if( !s585 )
return true;
s1168 = s585->s349();}
else if( s1168 == s7::s1383 ) {
if( !s585 )
return true;
s1168 = ( (s323*)s585 )->s316();}
else if( s1270 )
s1168 = s1270->s349( (size_t)(int)0 - s1168 );}
else if( s1168 >= s7::s1541 && ptr ) {
traitnum_t s1501 = ptr->s1446( s1168 );
if( ptr->s1188( s1166, s1501 ) )
return true;}
if( s1166 < s1168 )
return true;}
return false;}
wstring s1112::s1318( s261* s299 ) const{
wstring s680 = L"( ";
for( auto i : s1267 ) {
s680 += s299->TR().s797( i );
if( s680.back() != L')' ) s680 += L"()";
s680 += L" ";}
s680 += L")";
return s680;}
bool
s333::s334::s1156( /*s333* thi,*/ const s1112& s686 ) const
{
return std::find( s1153.begin(), s1153.end(), s686 ) != end( s1153 );}
s1053
s333::s383( s1889& s340 ) const{
auto it = s339().find( s340 );
if( it == s339().end() )
throw new s16( L"No such operation: " + s350() +	L"::" + s340,
(uint32_t)s16::s17::s23 );
s1053 s680 = it->second->s492();
return s680;}
const s480*
s333::s500() const{
return (s480*)s299->TR().s999( s349() );}
const vector<wstring>& 
s333::s1181( s1889& s340 ) const{
auto ran = s339().equal_range( s340 );
if( ran.first == s339().end() )
throw new s16( L"No such method: " + s350() + L"::" + s340,
(uint32_t)s16::s17::s23 );
return ran.first->second->Markers();}
s1132 s333::s1187( s1889& s340 ) const{
s333::s334* s680 = NULL;
auto it = s339().find( s340 );
if( it != s339().end() )
s680 = it->second;
return s680 ? s1132( s680->s492(), s680->s1126(), s680->s1193(),
s680->s2001() ) : s1132();}
s1132
s333::s1182( s1889& s340, s1112& ap /*const vector<s1053>& s1229*/ ) const
{
auto ran = s339().equal_range( s340 );
if( ran.first == s339().end() )
throw new s16( L"No such method: " + s350() + L"::" + s340,
(uint32_t)s16::s17::s23 );
if( ran.first->second->s1176() )
throw new s16( L"", (uint32_t)s334::s1123::s1170 );
s334* s680 = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1156( ap ) ) {
s680 = it->second;
break;}}
return s680 ? s1132( s680->s492(), s680->s1126(), s680->s1193(),
s680->s2001() ) : s1132();}
s1132
s333::s1177( s1889& s340, s1112& ap ){
auto ran = s339().equal_range( s340 );
s334* mi = NULL;
for( auto it = ran.first; it != ran.second; ++it ) {
if( it->second->s1156( ap ) ) {
mi = it->second;
break;}}
if( !mi )
throw new s16( L"method '" + s299->TR().s1341( s350() ) + L"::" + s340 + 
ap.s1318( s299 ) + L"' is not resolved" );
s1132 s1227( mi->s492(), mi->s1126(), mi->s1193(), mi->s2001() );
s1227.s335 = ap.Subj()->s1178( s340, ap.s599() );
return s1227;}
s483 s333::s494( s480** s273, size_t s495 ){
return this;}
void s333::s1523( s480* p ){}
s480* s333::s342( s261* s299, s1889& s346, s1889& s331 ){
s262 s207( s346, NULL, NULL );
s480* s680 = NULL;
double dval;
size_t pos = 0;
s6::s130 s197 = s1743.s1538( s346, pos, dval );
if( s197 != s6::s130::s139 && s197 != s6::s130::s135 )
return NULL;
if( s346.find( L"." ) != std::string::npos )
s680 = ((s355*)Types( s299, Types.Double ))->s351( s207, NULL, s331 );
else {
s680 = ((s343*)Types( s299, Types.Int ))->s351( s207, NULL, s331 );
if( !s680 ) {
if( !s680 )
s680 = ((s1292*)Types( s299, Types.Long ))->s351( s207, NULL, s331 );
if( !s680 )
s680 = ((s2310*)Types( s299, Types.Long ))->s351( s207, NULL, s331 );
if( !s680 )
s680 = ((s1284*)Types( s299, Types.Byte ))->s351( s207, NULL, s331 );}}
return s680;}
#define s691 ((s343*)(s481*)*s273)
#define s692 ((s357*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
s480* s355::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
if( s.find_first_not_of( L"-0123456789." ) == std::string::npos &&
1/*s.find( L"." ) != std::string::npos*/ ) {
size_t pos = 0;
return new s355( s299, s, pos );}
else if( s.find( L"Double(" ) == 0 ) {
size_t pos = 0;
return new s355( s299, s4::s52( s.substr( 7, s.size() - 8 ), s4::s48 ),
pos );}
else if( s.find( L"Double" ) == 0 ) {
return s352( s585, std::vector<s270*>(), &s694 );}
return 0;}
s355::s355( s261* s299, double d ) 
: s333( s299, NULL, NULL ), s346( d ){
if( !Types.Double ) {
s490 = 0;
wh = s7::s861;}
else {
s490 = Types.Double;
wh = s7::s860;}}
s355::s355( const s355& r )
: s333( r.s299, r.ns, r.s600() ), s346( r.s346 ){
wh = r.wh;
s490 = r.s490;}
double s1926( s1889& s, size_t& pos ){
assert( !s.empty() );
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
double s152 = 0.0;
pst = s.c_str();
if( !s63( pst, &s152, &pend ) )
throw new s16( L"2: unknown syntax near \"" + s.substr( pos, 40 ) + L"\"",
(uint32_t)s16::s17::s20 );
pos = pend - pst;
return s152;}
s355::s355( s261* s299, s1889& s, size_t& pos )
: s333( s299, NULL, NULL ){
if( !s.empty() ) {
s346 = s1926( s, pos );
s1664( s7::s860 );}
else
s346 = s299->TR().s1240();
s490 = Types.Double;}
s480* s355::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s355( s299, L"", pos );}
void s355::s497( const s271*, bool ){
s1251();}
void s355::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s355::s1226, Types.Double,
{ s1112(), s1112( { Types.String } ), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"abs", new s334( L"abs", &s355::s401, Types.Double,
{ s1112( ) }, 0, 0 )));
s345.insert( make_pair( L"set", new s334( L"set", &s355::s384, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"sum", new s334( L"sum", &s355::s385, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"dif", new s334( L"dif", &s355::s386, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"mul", new s334( L"mul", &s355::s387, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"div", new s334( L"div", &s355::s388, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"pow", new s334( L"pow", &s355::s389, Types.Double,
{ s1112( { s1500::s1260 } ) }, 1, 1 )));
s345.insert( make_pair( L"sumeq", new s334( L"sumeq", &s355::s390, Types.Double,
{ s1112( { Types.Double } ), s1112( { Types.Int, s7::s1387 } ) }, 1, 10 )));
s345.insert( make_pair( L"difeq", new s334( L"difeq", &s355::s391, Types.Double,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"muleq", new s334( L"muleq", &s355::s392, Types.Double,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"diveq", new s334( L"diveq", &s355::s393, Types.Double,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"poweq", new s334( L"poweq", &s355::s394, Types.Double,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"sqrt", new s334( L"sqrt", &s355::s403, Types.Double,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"nroot", new s334( L"nroot", &s355::s404, Types.Double,
{ s1112( { Types.Int } ) }, 1, 1 )));
s345.insert( make_pair( L"eq", new s334( L"eq", &s355::s395, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"less", new s334( L"less", &s355::s396, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"greater", new s334( L"greater", &s355::s397, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"leq", new s334( L"leq", &s355::s398, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"geq", new s334( L"geq", &s355::s399, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"neq", new s334( L"neq", &s355::s400, Types.Bool,
{ s1112( { Types.Double } ) }, 1, 1 )));
s345.insert( make_pair( L"dcmp", new s334( L"dcmp", &s355::s407, Types.Int,
{ s1112( { Types.Double, Types.Double } ) }, 2, 2 )));
s345.insert( make_pair( L"dcmpr", new s334( L"dcmpr", &s355::s408, Types.Int,
{ s1112( { Types.Double, Types.Double } ) }, 2, 2 )));
s345.insert( make_pair( L"floor", new s334( L"floor", &s355::s2197, Types.Double,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"ceil", new s334( L"ceil", &s355::s2195, Types.Double,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"to-Int", new s334( L"to-Int", &s355::s409, Types.Int,
{ s1112(), s1112( { Types.Int } ) }, 0, 1 )));
s345.insert( make_pair( L"incr", new s334( L"incr", &s355::s1962, Types.Double,
{ s1112( ) }, 0, 0 )));
s345.insert( make_pair( L"decr", new s334( L"decr", &s355::s1961, Types.Double,
{ s1112( ) }, 0, 0 )));
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );}
s270* s355::s332( s588* s2041, s271* impl ) const{
return new s355( *this );}
void s355::s353( s270* p ) const{
if( p->s349() == Types.Int )
*( (s343*)p )->s354() = (int)s346;
else if( p->s349() == Types.Double )
*( (s355*)p )->s354() = s346;
else if( p->s349() == Types.Bool )
*( (s357*)p )->s354() = ( s346 != 0.0 );
else
throw new s16( L"No conversion to type " + s350() );}
std::wstring s355::to_wstring( uint32_t s1552 ) const{
wstringstream ss;
wstring s680;
int prec = s1552 << 28 >> 28;
if( prec ) {
ss << setprecision( prec ) << s346;
s680 = ss.str();}
else {
wstring s = std::to_wstring( s346 );
size_t pl = s.find_last_not_of( L'0' );
if( s[pl] != L'.' && s[pl] != L',' )
++pl;
s680 = s.substr(0, pl);}
return s680;}
void s355::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
/*	auto flags = s1918->s1914();
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss.precision( s1918->s1915() );
*/
ss << s346;}
void s355::s1944( s1889& s ){
size_t pos = 0;
s346 = s1926( s, pos );}
void s355::s1943( Stream* s1918 ){
s1485& ss = s1918->s1947();
ss >> s346;}
#undef s691
#define s691 ((s355*)(s481*)*s273)
#define INTRES ((s343*)(s481*)*s273)
inline void s355::s1226( s480** s273, size_t s495 ){
s355* plv = NULL;
if( s495 == 3 && s273[2]->s349() == Types.String ) {
size_t pos = 0;
plv = new s355( ((s355*)s273[1] )->s299, *((s356*)s273[2])->s354(), pos );}
else {
plv = new s355( ( (s355*)s273[1] )->s299, 0.0 );
s355& lv = *plv;
if( s495 == 2 )
lv.s346 = 0;
else if( s495 == 3 ) {
s480* p = s273[2];
if( p->s349() == Types.Double )
lv.s346 = *( (s355*)p )->s354();
else if( p->s349() == Types.Int )
lv.s346 = (s1374)*( (s343*)p )->s354();
else if( p->s349() == Types.Bool )
lv.s346 = ( s1374 )*( (s357*)p )->s354();
else
throw new s16( L"no conversion to Double from type: " + p->s350() );}
else
throw new s16( L"unknown parameters to Double() constructor" );}
plv->s1251();
s273[0] = plv;}
inline void s355::s384( s480** s273, size_t s495 ){
( (s355*)DR )->s346 = (double)*PARN( 2 );}
void s355::s401( s480** s273, size_t s495 ){
double t = (double)*DR;
if( t >= 0 )
s691->s346 = t;
else
s691->s346 = -t;}
void s355::s1962( s480** s273, size_t s495 ){
double s680 = (double)*DR;
if (isnan( s680 ) || s680 == -INFINITY || s680 == INFINITY) (void)0;
else if ( s680 == 0.0 ) s680 = DBL_EPSILON;
else {
union s1958 {
int64_t i;
double f;
}conv;
conv.f = s680;
conv.i++;
s680 = conv.f;}
s691->s346 = s680;}
void s355::s1961( s480** s273, size_t s495 ){
double s680 = (double)*DR;
if (isnan( s680 ) || s680 == -INFINITY || s680 == INFINITY) (void)0;
else if ( s680 == 0.0 ) s680 = DBL_EPSILON;
else {
union s1958 {
int64_t i;
double f;
}conv;
conv.f = s680;
conv.i--;
s680 = conv.f;}
s691->s346 = s680;}
inline void s355::s387( s480** s273, size_t s495 ){
s691->s346 = ( (double)*DR ) * (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
s691->s346 *= (double)*PARN( n );}
inline void s355::s385( s480** s273, size_t s495 ){
s691->s346 = ( (double)*DR ) + (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
s691->s346 += (double)*PARN( n );}
inline void s355::s388( s480** s273, size_t s495 ){
s273[2]->s353( s273[0] );
s691->s346 = ( (s355*) DR )->s346 / s691->s346;
}
inline void s355::s386( s480** s273, size_t s495 ){
s691->s346 = ( (double)*DR ) - (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
s691->s346 -= (double)*PARN( n );}
inline void s355::s390( s480** s273, size_t s495 ){
s355* pd = (s355*) s273[1];
for( size_t n = 2; n < s495; ++n ) {
s480* p = s273[n];
if( p->s349() == Types.Double )
pd->s346 += *( (s355*)p )->s354();
else if( p->s349() == Types.Int )
pd->s346 += ( s1374 )*( (s343*)p )->s354();}
s691->s346 = ( (double)*DR );}
inline void s355::s391( s480** s273, size_t s495 ){
( (s355*)DR )->s346 -= (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
( (s355*)DR )->s346 -= (double)*PARN( n );
s691->s346 = ( (double)*DR );}
inline void s355::s392( s480** s273, size_t s495 ){
( (s355*)DR )->s346 *= (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
( (s355*)DR )->s346 *= (double)*PARN( n );
s691->s346 = ( (double)*DR );}
inline void s355::s393( s480** s273, size_t s495 ){
( (s355*)DR )->s346 /= (double)*PARN( 2 );
for( size_t n = 3; n < s495; ++n )
( (s355*)DR )->s346 /= (double)*PARN( n );
s691->s346 = ( (double)*DR );}
inline void s355::s394( s480** s273, size_t s495 ){
( (s355*)DR )->s346 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s495; ++n )
( (s355*)DR )->s346 = ::pow( (double)*DR, (double)*PARN( n ) );
s691->s346 = ( (double)*DR );}
inline void s355::s395( s480** s273, size_t s495 ){
double d = (double)*DR;
if( std::abs( d - (double)*PARN(2) ) < 0.000001  ) // FIX:
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s396( s480** s273, size_t s495 ){
if( ((double)*DR) < (double)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s397( s480** s273, size_t s495 ){
if( ( (double)*DR ) > (double)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s398( s480** s273, size_t s495 ){
if( ( (double)*DR ) <= (double)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s399( s480** s273, size_t s495 ){
if( ( (double)*DR ) >= (double)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s400( s480** s273, size_t s495 ){
if( ( (double)*DR ) != (double)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s355::s403( s480** s273, size_t s495 ){
s691->s346 = ::sqrt((double)*DR);}
inline void s355::s404( s480** s273, size_t s495 ){
*( (s355*)s273[0] )->s354() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s355::s407( s480** s273, size_t s495 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl - dr <= diff )
*INTRES->s354() = 0;
else
*INTRES->s354() = 1;}
else {
if( dr - dl <= diff )
*INTRES->s354() = 0;
else
*INTRES->s354() = -1;}}
inline void s355::s408( s480** s273, size_t s495 ){
double dl = (double)*DR;
double dr = (double)*PARN( 2 );
double diff = (double)*PARN( 3 );
if( dl > dr ) {
if( dl / dr - 1 <= diff )
*INTRES->s354() = 0;
else
*INTRES->s354() = 1;}
else {
if( dr / dl - 1 <= diff )
*INTRES->s354() = 0;
else
*INTRES->s354() = -1;}}
inline void s355::s389( s480** s273, size_t s495 ){
s691->s346 = std::pow( ( (double)*DR ), (double)*PARN( 2 ) );}
inline void s355::s2197( s480** s273, size_t s495 ){
double dv = ( (s355*)DR )->s346;
*( (s355*)s273[0] )->s354() = floor( dv );}
inline void s355::s2195( s480** s273, size_t s495 ){
double dv = ( (s355*)DR )->s346;
*( (s355*)s273[0] )->s354() = ceil( dv );}
inline void s355::s409( s480** s273, size_t s495 ){
int s1320 = -1;
if( s495 == 3 )
s1320 = (int)*s273[2];
double dv = ( (s355*)DR )->s346;
int s680 = (int)dv;
if( s1320 < 0 )
*( (s343*)s273[0] )->s354() = s680;
else if( s1320 == 0 ) 
*( (s343*)s273[0] )->s354() = (dv - s680 > 0.5 ? s680 + 1 : s680);
else
*( (s343*)s273[0] )->s354() = s680 + 1;}
void s355::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << s346;}
size_t s355::s319() const{
return hash<double>{}( s346 );}
inline
int dcmp( double d1, double d2, int iDigs ){
double rem = fabs( d1 - d2 );
double prec = 1 / pow( (double)10.0, iDigs );
if ( rem < prec )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline
int dcmp_( double d1, double d2, double dif ){
double rem = fabs( d1 - d2 );
if ( rem < dif )
return 0;
if ( d1 < d2 )
return -1;
return 1;}
inline bool s355::operator==( const s480* p ) const{
return ( dcmp_( ( (s355*)p )->s346, s346, 0.00000001 ) == 0 ); // FIX:
}
inline bool s355::operator<( const s480* p ) const{
return ( dcmp_( s346, ( (s355*)p )->s346, 0.00000001 ) < 0 ); // FIX:
}
s357::s357( s261* s299, s1889& s, size_t& pos )
: s333( s299, NULL, NULL ){
if( s.empty() )
s346 = s299->TR().s1238();
else if( ( s[0] == L'0' || s[0] == L'1' ) && s.find_first_not_of( L".-0123456789" ) == 1 ) {
s346 = (s[0] == L'1');
pos++;}
else if( s.find( s7::s433 ) == 0 ) {
s346 = true;
pos += 4;}
else if( s.find( s7::s434 ) == 0 ) {
s346 = false;
pos += 5;}
else
throw new s16( L"unknown bool format: " + s.substr( 0, 20 ) );
if( !s.empty() )
s1664( s7::s860 );
s490 = Types.Bool;}
s357::s357( const s357& right )
: s333( right.s299, right.ns, NULL ), s346( right.s346 ){
s490 = Types.Bool;
wh = right.wh;}
s357::s357( s261* s299, bool b )
: s333( s299, NULL, NULL ), s346( b ){
if( !Types.Bool ) {
s490 = 0;
s1664( s7::s861 );}
else {
s490 = Types.Bool;
s1664( s7::s860 );}}
void s357::s347(){
s345.insert( make_pair( L"set", new s334( L"set", &s357::s384, Types.Null,
{ s1112( { Types.Bool } ) }, 1, 1, false )));
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s357::s1226, Types.Bool,
{ s1112(), s1112( { Types.Bool } ), s1112( { Types.String } ), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"not", new s334( L"not", &s357::s410, Types.Bool,
{ s1112( ) }, 0, 0, true )));
s345.insert( make_pair( L"eq", new s334( L"eq", &s357::s395, Types.Bool,
{ s1112( { Types.Bool } ) }, 1, 1, true )));}
void s357::s497( const s271* s872, bool ){
s1251();}
s480* s357::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s357( s299, false );}
s480* s357::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s4::s52( s694.s290(), s4::s48 );
if( s.find( s7::s433 ) == 0 || s.find( s7::s434 ) == 0 )
return new s357( s299, ( s.find( s7::s433 ) == 0 ) );
else if( s.find( L"Bool(" ) == 0 ) {
size_t pos = 0;
return new s357( s299, 
s4::s52( s.substr( 5, s.size() - 6 ), s4::s48 ), pos );}
else if( s.find( L"Bool" ) == 0 ) {
return s352( s585, std::vector<s270*>(), &s694 );}
return NULL;}
s270* s357::s332( s588* s2041, s271* impl ) const{
return new s357( *this );}
void s357::s353( s270* p ) const{
if( p->s349() == Types.Bool )
((s357*)p)->s346 = s346;
else if( p->s349() == Types.Int )
*( (s343*)p )->s354() = (int)s346;
else if( p->s349() == Types.Double )
*( (s355*)p )->s354() = (double)s346;
else
throw new s16( L"No conversion to type " + s350() );}
#undef s691
#define s691 ((s357*)(s481*)*s273)
inline void s357::s1226( s480** s273, size_t s495 ){
s357* plv = new s357( ( (s357*)s273[1] )->s299, 0 );
s357& lv = *plv;
if( s495 == 2 )
lv.s346 = false;
else if( s495 == 3 ) {
s480* p = s273[2];
if( p->s349() == Types.Int )
lv.s346 = *( (s343*)p )->s354() != 0;
else if( p->s349() == Types.Double )
lv.s346 = *( (s355*)p )->s354() != 0.0;
else if( p->s349() == Types.Bool )
lv.s346 = *( (s357*)p )->s354();
else if( p->s349() == Types.String )
lv.s346 = ( (s356*)p )->s354()->size() > 0;
else
throw new s16( L"no conversion to Bool from type: " + p->s350() );}
else
throw new s16( L"unknown parameters to Bool() constructor" );
lv.s1251();
s273[0] = plv;}
inline void s357::s384( s480** s273, size_t s495 ){
( (s357*)DR )->s346 = ( (s357*)PARN( 2 ) )->s346;}
inline void s357::s410( s480** s273, size_t s495 ){
s691->s346 = !( (s357*)DR )->s346;}
inline void s357::s395( s480** s273, size_t s495 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
wstring s357::to_wstring( uint32_t s1552 ) const{
return ( s346 ? L"true" : L"false" ); }
void s357::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
ss << s346;}
void s357::s1944( s1889& s ){
if( s == L"true" || s == L"1" )
s346 = true;
else if( s == L"false" || s == L"0" )
s346 = false;
else
throw new s16( L"unknown bool value" );}
void s357::s1943( Stream* s1918 ){
s1485& ss = s1918->s1947();
ss >> s346;}
void s357::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << to_wstring()
<< L" (" << std::hex << &s346 << L")";}
size_t s357::s319() const{
return hash<bool>{}( s346 );}
inline bool s357::operator==( const s480* p ) const{
return ( s346 == ((s357*)p)->s346 );}
inline bool s357::operator<( const s480* p ) const{
return ( s346 < ((s357*)p)->s346 );}
vector<wstring> s2260( { L":general", L":stopIter" } );
s358::s358( s261* s299, s1889& s/* = std::wstring( L"" )*/ )
: s333( s299, NULL, NULL ), s2263( s2261 ), s78( s ){
wh = s7::s437;
s490 = Types.No == 0 ? 0 : Types.s358;}
s358::s358( const s358& r )
: s333( r.s299, NULL, NULL ), s2263( r.s2263 ), s78( r.s78 ), obj( r.obj ){
s490 = r.s490;
wh = r.wh;}
void s358::create( const vector<s482>& l ){
if( l.size() ) {
s2263 = s2261;
if( l[0]->s491() == s472 || l[0]->s491() == s1055 ) {
s368* rf = l[0].s15<s368*>();
rf->s974( s2260 );
s2263 = (s2259) rf->s1293();}
obj = l.back().s15<s480*>()->s494(0,0);}
else if( s78.size() ) {
obj = new s356( s299, s78 );}}
void s358::s347(){
s345.insert( make_pair( L"report", new s334( L"report", &s358::s785, Types.Null,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"str", new s334( L"str", &s358::s505, Types.String,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"is-type", new s334( L"is-type", &s358::s2265, Types.Bool,
{ s1112() }, 0, 0, true, s2260 )));}
void s358::s497( const s271* s872, bool ){}
s483 s358::s494( s480** s273, size_t s495 ){
return obj->s494(0,0);}
s480* s358::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s358( s299 );}
s270* s358::s332( s588* s2041, s271* impl ) const{
return new s358( *this );}
void s358::s353( s270* p ) const{
((s358*)p)->s2263 = s2263;
((s358*)p)->s78 = s78;
((s358*)p)->obj = obj;}
s480* s358::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
if( s.find( L"Exception(" ) == 0 )
return new s358( s299, s.substr( 10, s.size() - 11 ) );
else if( s.find( L"Exception" ) == 0 )
return s352( s585, std::vector<s270*>(), &s694 );
return NULL;}
#undef s691
#define s691 ((s358*)(s481*)*s273)
inline void s358::s785( s480** s273, size_t s495 ){
if( ( (s358*)DR )->obj.s14() )
wcout << ( (s358*)DR )->obj->s494( 0, 0 )->to_wstring();}
inline void s358::s505( s480** s273, size_t s495 ){
if( ( (s358*)DR )->obj.s14() )
*( (s356*)s273[0] )->s354() = ( (s358*)DR )->obj->s494( 0, 0 )->to_wstring();}
inline void s358::s2265( s480** s273, size_t s495 ){
s358* dr = (s358*)DR;
int idx = (int)*((s368*)s273[2])->s374();
if( dr->s2263 == (s2259)idx )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}
void s358::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : -";}
size_t s358::s319() const{
throw new s16( L"9: not implemented" );}
bool s358::operator==( const s480* p ) const{
return ( (s358*)p )->s78 == s78;}
bool s358::operator<( const s480* p ) const{
return s78 < ( (s358*)p )->s78;}
s361::s361( s261* s299, s271* s585 ) 
: s333( s299, s585, NULL ){
if( !Types.Null ) {
s490 = 0;
s1664( s7::s861 );}
else {
s490 = Types.Null;
s1664( s7::s860 );}}
void s361::s497( const s271* s872, bool ){}
s480* s361::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s361( s299, s585 );}
s480* s361::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
if( s.find( L"Null" ) == 0 )
return s362;
return NULL;}
s270* s361::s332( s588* s2041, s271* impl ) const{
return (s270*)this;}
void s361::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : -";}
size_t s361::s319() const{
return 0xfeeb1e;}
bool s361::operator==( const s480* p ) const{
return ( this == p );}
bool s361::operator<( const s480* p ) const{
return false;}
s381::s381( s261* s299, s271* ns_, traitnum_t tn, s469 pc ) 
: s333( s299, ns_, NULL ), s1261( tn ){
s489 = pc;
s490 = Types.No == 0 ? 0 : Types.No; }
void s381::s497( const s271* s872, bool ){
ns = (s271*)s872;}
s480* s381::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s381( s299, s585 );}
s480* s381::s351( const s262& s694, s271* s585, s1889& s331 ) const{
throw new s16( L"no parser for NoValue" );
return NULL;}
s1889& s381::s350() const{
if( s489 == s2306 )
return s299->TR().s797( s1261 );
return s333::s350();}
s270* s381::s332( s588* s2041, s271* impl ) const{
return (s270*)this;}
inline bool
s381::s498( const s480* s499 ) const{
if( s489 == s2306 )
return s299->TR().s1522( s499, this );
return s299->TR().s1188( s499->s349(), s1261 );}
inline bool
s381::s1529( s1053 s616 ) const{
return s299->TR().s1522( s1261, s616 );}
void s381::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : -" << endl;}
size_t s381::s319() const{
throw new s16( L"not implemented" );}
bool s381::operator==( const s480* p ) const{
return false;}
bool s381::operator<( const s480* p ) const{
return false;}
s1691::s1691( s261* s299 ) 
: s333( s299, NULL, NULL ), s1728( s1726 ) {
if( !Types.DateTime )
s490 = 0;
else
s490 = s1698;
s1664( s7::s861 );}
s1691::s1691( s261* s299, s1889& s )
: s333( s299, NULL, NULL ){
if( !s1713( s, s346, s1728 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1859 = s1780::from_time_t ( std::mktime( &s346 ) );
s490 = s1698;
s1664( s7::s860 );}
s1691::s1691( const s1691& right )
: s333( right.s299, right.ns, NULL ), s1728( right.s1728 ), 
s346( right.s346 ), s1859( right.s1859 ){
s490 = right.s490;
wh = right.wh;}
s1691::s1691( s261* s299, const std::tm& _t, s1690 s616 )
: s333( s299, NULL, NULL ), s1728( s616 ), s346( _t ){
s490 = s1698;
s1859 = s1780::from_time_t ( std::mktime( &s346 ) );
s1664( s7::s860 );}
wregex s1691::s1750( LR"regex(^\"?(\d\d\d\d-\d\d?-\d\d?)\"?$)regex" );
wregex s1691::s1848( LR"regex(^(\d+)(\.\d+)?$)regex" );
bool 
s1691::s1713( s1889& s346, std::tm& t, s1690& s616 ) const{
wsmatch s1066;
s616 = s1726;
if( regex_match( s346, s1066, s1750 ) ) {
std::wistringstream ss( s1066[1] );
ss >> std::get_time( &t, L"%Y-%m-%d" );
if( ss.fail() )
return false;
s616 = s1724;}
else if( regex_match( s346, s1066, s1750 ) ) {}
else
return false;
return true;}
void s1691::s347(){
s345.insert( make_pair( L"set", new s334( L"set", &s1691::s384, Types.Null,
{ s1112( { s1698 } ), s1112( { Types.String } ) }, 1, 1, false ) ) );
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1691::s1226, s1698,
{ s1112(), s1112( { s1698 } ), s1112( { Types.String } ), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"not", new s334( L"not", &s1691::s410, Types.Bool,
{ s1112() }, 0, 0, true ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s1691::s395, Types.Bool,
{ s1112( { s1698 } ) }, 1, 1, true ) ) );
s345.insert( make_pair( L"now-delta", new s334( L"now-delta", &s1691::s1834, Types.Double,
{ s1112( ) }, 0, 0, true ) ) );
s345.insert( make_pair( L"set-now", new s334( L"set-now", &s1691::s1857, s1698,
{ s1112( ) }, 0, 0, false ) ) );}
void s1691::s497( const s271* s872, bool ){
s1251();}
s480* s1691::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s1691( s299 );}
s480* s1691::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s4::s52( s694.s290(), s4::s48 );
if( s.find( L"DateTime(" ) == 0 )
s = s.substr( 9, s.size() - 10 );
if( s.empty() )
return new s1691( s299 );
std::tm t = {};
s1690 s616;
if( s1713( s, t, s616 ) )
return new s1691( s299, t, s616 );
return NULL;}
s270* s1691::s332( s588* s2041, s271* impl ) const{
return new s1691( *this );}
void s1691::s353( s270* p ) const{
if( p->s349() == s1698 )
( (s1691*)p )->s346 = s346;
else
throw new s16( L"No conversion to type " + s350() );}
void s1691::s1944( s1889& s ){
std::tm t = {};
s1690 s616;
if( !s1713( s, t, s616 ) )
throw new s16( L"unrecognized Date/Time format",
(uint32_t)s16::s17::s20 );
s1728 = s616;
s346 = t;
s1664( s7::s860 );}
#undef s691
#define s691 ((s1691*)(s481*)*s273)
inline void s1691::s1226( s480** s273, size_t s495 ){
s1691* s680 = NULL;
if( s495 == 2 )
s680 = new s1691( ( (s1691*)s273[1] )->s299 );
else if( s495 == 3 ) {
s480* p = s273[2];
if( p->s349() == s1698 )
s680 = new s1691( *(s1691*)s273[2] );
else if( p->s349() == Types.String )
s680 = new s1691( ( (s1691*)s273[1] )->s299, s273[2]->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s350() );}
else
throw new s16( L"unknown parameters to DateTime() constructor" );
s273[0] = s680;}
inline void s1691::s384( s480** s273, size_t s495 ){
s480* p = s273[2];
if( p->s349() == s1698 ) {
( (s1691*)DR )->s346 = ( (s1691*)p )->s346;
( (s1691*)DR )->s1728 = ( (s1691*)p )->s1728;
( (s1691*)DR )->wh = ( (s1691*)p )->wh;}
else if( p->s349() == Types.String )
( (s1691*)DR )->s1944( p->to_wstring() );
else
throw new s16( L"no conversion to DateTime from type: " + p->s350() );}
inline void s1691::s410( s480** s273, size_t s495 ){
*s692->s354() = !(( (s1691*)DR )->s1728 == s1726);}
inline void s1691::s395( s480** s273, size_t s495 ){
if( ( (bool)*DR ) == (bool)*PARN( 2 ) )
*s692->s354() = 1;
else
*s692->s354() = 0;}
inline void s1691::s1857( s480** s273, size_t s495 ){
s1691* p = (s1691*)DR;
p->s1859 = s1780::now();
time_t t = s1780::to_time_t( p->s1859 );
#ifdef WIN32
localtime_s( &p->s346, &t );
#else
p->s346 = *localtime( &t );
#endif
p->s1728 = s1725;}
inline void s1691::s1834( s480** s273, size_t s495 ){
s1691* p = (s1691*)DR;
std::chrono::duration<double> delta = s1780::now() - p->s1859;
*((s355*)s273[0])->s354() = delta.count();}
void s1691::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << to_wstring()
<< L" (" << std::hex << &s346 << L")";}
size_t s1691::s319() const{
std::tm t = s346;
return hash<time_t>{}( std::mktime( &t ) );}
inline bool s1691::operator==( const s480* p ) const{
return memcmp( &s346, &((s1691*)p )->s346, sizeof(tm) );}
inline bool s1691::operator<( const s480* p ) const{
tm t = s346, t1 = ( (s1691*)p )->s346;
return ( std::mktime( &t ) < std::mktime( &t1 ) );}
wstring s1691::to_wstring( uint32_t s1552 ) const{
wstring s680;
if( s1728 == s1724 || s1728 == s1725 ) {
s680 = std::to_wstring( 1900 + s346.tm_year ) + L"-";
if( s346.tm_mon < 9 )
s680 += L"0";
s680 += std::to_wstring( 1 + s346.tm_mon ) + L"-";
if( s346.tm_mday < 10 )
s680 += L"0";
s680 += std::to_wstring( s346.tm_mday );}
if( s1728 == s1725 )
s680 += L" ";
if( s1728 == s1727 || s1728 == s1725 ) {
if( s346.tm_hour < 10 )
s680 += L"0";
s680 += std::to_wstring( s346.tm_hour ) + L":";
if( s346.tm_min < 10 )
s680 += L"0";
std::to_wstring( s346.tm_min ) + L":";
if( s346.tm_sec < 10 )
s680 += L"0";
std::to_wstring( s346.tm_sec );}
return s680;}
s1589::s1589( s261* s299, s271* s585, s1889& s77, bool typed, const s262* ast_ )
: s333( s299, s585, ast_ ){
if( s77.size() )
load( s77, typed, false );
if( !s490 )
s490 = Types.s271;
if( !s77.empty() )
s1664( s7::s860 );}
s1589::s1589( s261* s299, s271* s585, const s142* s1631, const s262* ast_ )
: s333( s299, s585, ast_ ){
TDException s960( s7::CLObjectVal_ctor1, s925, ast_ );
if( s1631->s155( s7::s462 ) ) {
wstring sname = s4::s52( s262::s301( *s1631, s7::s462 ),
s48 );
(( s142*)s1631)->s158( L"name", new s140( sname ) );
(( s142*)s1631)->s1618( s7::s462 );}
try {
s1629( s1631, true, s479::s145 );}
catch( s16* e ) {
throw s960.s992( L"construction of TSD object failed: " + e->Msg() );}
s490 = Types.s271;
s1251();}
s1589::s1589( const s1589& right, s480* s2108 )
: s333( right.s299, (s271*)s2108, right.s600() ), s625( right.s625 ){
s490 = Types.s271;
wh = right.wh;}
void s1589::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1589::s1226, Types.s271,
{ s1112(), s1112( { s1143 } ), s1112( { Types.String, Types.Bool } ) }, 0, 2 ) ) );
s345.insert( make_pair( L"get-Int", new s334( L"get-Int", &s1589::s1623, Types.Int,
{ s1112( { Types.String } ) }, 1, 1, true )));
s345.insert( make_pair( L"get-String", new s334( L"get-String", &s1589::s1624, Types.String,
{ s1112( { Types.String } ) }, 1, 1, true )));
s345.insert( make_pair( L"load", new s334( L"load", &s1589::s1628, Types.Null,
{ s1112( { Types.String } ), s1112( { Types.String, Types.Bool } ) }, 1, 2, true )));
s345.insert( make_pair( L"load-from-file", new s334( L"load-from-file", &s1589::s1626, Types.Null,
{ s1112( { Types.String } ), s1112( { Types.String, Types.String } ) }, 1, 2, true )));}
void s1589::s497( const s271* s872, bool ){
s1251();}
s480* s1589::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s1589( s299, s585, L"", ast_ );}
s480* s1589::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
if( s.find( L"Object(" ) == 0 ) {
return new s1589( s299, s585, s.substr( 7, s.size() - 8 ) );}
else if( s.find( L"Object" ) == 0 ) {
return s352( s585, std::vector<s270*>(), &s694 );}
return NULL;}
s1053 s1589::s1178( s1889& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" ) {
auto it = s625.get( l[0]->to_wstring() );
s680 = it->s349();}
return s680;}
void s1589::load( s1889& s77, bool typed, bool s1621 ){
TDException s960( s7::s1585, s925, s600(), L"Failed to load object" );
s940 s1043 = new s937( s77, s1621 );
vector<s9<s142>> s659;
s1043->read( s659, L"" );
if( s659.size() != 1 )
throw s960.s992( L"wrong object data: the source contains " + std::to_wstring( s659.size() ) + L" objects"  );
s142* obj = s659[0];
if( obj->s155( s7::s462 ) ) {
wstring sname = s4::s52( s262::s301( *obj, s7::s462 ),
s48 );
obj->s158( L"name", new s140( sname ) );}
s1629( obj, typed );}
void s1589::s1629( const s142* obj, bool typed, s479::s144 ap ){
vector<pair<wstring, s141>> s143;
obj->s159( s143 );
for( size_t n = 0; n < s143.size(); ++n ) {
if( typed ) {
s939 past = new s262( s143[n].first, *s143[n].second, NULL );
s480* dv = s299->TR().s515( *past, (s271*)this, L"::" );
dv->s503( s143[n].first );
dv->s1251();
s625.s538( s143[n].first, dv, ap );}
else {
s625.s538( s143[n].first, s143[n].second, ap );}}}
void s1589::s1619( s479::s532& sm ) const{
const s479::s532& tb = s625.Table();
s479::s532::const_iterator it = tb.begin();
for( ; it != tb.end(); ++it ) {
if( it->second->s491() == s473 )
(void)0;
else {
s480* dv = (s480*)it->second->s332(0,0);
sm.insert( make_pair( it->first, dv ));}}}
s270* s1589::s332( s588* s2041, s271* impl ) const{
return new s1589( *this, impl ? impl : ns );}
void s1589::s353( s270* p ) const{
if( p->s349() == Types.s271 )
((s1589*)p)->s625 = s625;
else
throw new s16( L"No conversion to type " + s350() );}
#undef s691
#define s691 ((s1589*)(s481*)*s273)
inline void s1589::s1226( s480** s273, size_t s495 ){
s1589* r = (s1589*)s273[1];
wstring sobj;
bool typed = true;
if( s495 > 2 ) {
sobj = ( (s356*)s273[2] )->s317();
if( s495 == 4 )
typed = (bool)*s273[3];}
s1589* s2133 = new s1589( r->s299, r->ns, sobj, typed );
s2133->s497( r->ns );
*s273 = (s480*)s2133;}
inline void s1589::s1623( s480** s273, size_t s495 ){
wstring s151 = s273[2]->to_wstring();
*((s343*)*s273)->s354() = (int)*( (s1589*)DR )->s625.get( s151 );}
inline void s1589::s1624( s480** s273, size_t s495 ){
wstring s151 = s273[2]->to_wstring();
*((s356*)*s273)->s354() = ( (s1589*)DR )->s625.get( s151 )->to_wstring();}
inline void s1589::s1645( s480** s273, size_t s495 ){
wstring s151 = s273[2]->to_wstring();
s343* pd  = (s343*)( (s1589*)DR )->s625.get( s151 );
*pd->s354() = (int)*s273[3];}
inline void s1589::s1647( s480** s273, size_t s495 ){
wstring s151 = s273[2]->to_wstring();
s356* pd  = (s356*)( (s1589*)DR )->s625.get( s151 );
*pd->s354() = s273[3]->to_wstring();}
inline void s1589::s1628( s480** s273, size_t s495 ){
s1589* po = (s1589*)DR;
wstring s77 = s273[2]->to_wstring();
bool typed = true;
if( s495 == 3 )
typed = (bool)*s273[2];
po->load( s77, typed, false );}
inline void s1589::s1626( s480** s273, size_t s495 ){
s1589* po = (s1589*)DR;
wstring s188 = s273[2]->to_wstring();
bool typed = true;
if( s495 == 3 )
typed = (bool)*s273[2];
po->load( s188, typed, true );}
size_t s1589::s319() const{
return (size_t)this; //hash<bool>{}( s346 );
}
inline bool s1589::operator==( const s480* p ) const{
return this == p; // ( s625 == ( (s1589*)p )->s625 );
}
inline bool s1589::operator<( const s480* p ) const{
return this < p; // ( s625 < ( (s1589*)p )->s625 );
}
wstring s1589::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"Object: { \n";
s680 += s625.to_wstring( s1552 );
s680 += L"\n }";
return s680;}
void s1589::s1944( s1889& s ) {
load( s, true, false );}
void s1589::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << endl;
s625.s303( pd, s196 + s416 );}
size_t s368::s2266 = 1;
s368::s368( s1889& s, s261* s299, s469 cat, bool _cnst )
: s481( s299, cat ), s369( s ), s373( 0 ), s1158( _cnst )//, s2282( false )
{
assert( cat == s470 || cat == s472 || cat == s478 || cat == s1055 );
if( cat == s470 ) {
if( 0 && s[0] == L':' ) {
s489 = s1055;
s490 = Types.No;
s370 = (s480*)Types( s299, Types.No );}
else if( s299->s220( *this ) ){
s489 = s478;
s490 = Types.No;}
else
s489 = s472;}}
s368::s368( const s368& right, s480* s2166 )
: s481( right.s299, right.s489 ), s369( right.s369 ),
s370( s2166 ? s2166 : right.s370 ), s371( right.s371 ), 
s372( right.s372 ),s373( right.s373 ), s1158( right.s1158 )//, s2282( right.s2282 )
{
if( s489 == s478 )
s370 = right.s370;
s490 = right.s490;
wh = right.wh;}
void s368::s2269(){
s369 += L"_@" + std::to_wstring( s2266++ );}
void s368::s497( const s271* s584, bool fr ){
if( false && s299->s220( *this ) ) {
s489 = s478;
s490 = Types.No;}
else if( s489 == s478 )
(void)0;
else {
if( !s584->s553( s369, this, s584->s2153(), fr ) ) {
if( s489 == s1055 )
return;
throw new TDException( (uint32_t)0, s923, NULL, s369 );}
if( s371 )
s490 = s371->s349();
else if( s489 == s1326 )
s490 = s370.s15<s368*>()->s374()->s349();
else
assert( 0 );}
s1251();}
void s368::reset(){
if( s491() == s1055 || 
s491() == s478 )
return;
s372.clear();
s373 = 0;
s371 = NULL;
s370 = NULL;}
const s482 s368::s378() {
if( s370.s14() && s370->s491() == s1326 )
return s370.s15<s1587*>()->s2102().s15<s481*>();
return s370; }
void s368::s379( s480* p ){
s370 = p; }
s480* s368::s374() const{
if( s489 == s1055 )
return s370.s15<s480*>();
else if( s489 == s1326 )
return s370.s15<s368*>()->s374();
if( s372.empty() )
return s370.s15<s480*>();
s481* s680 = NULL;
if( s370->s491() == s1326 )
s680 = s370.s15<s1587*>()->s595( *(size_t*)&s372[0] );
else
s680 = s370.s15<s271*>()->s595( *(size_t*)&s372[0] );	
for( size_t n = 1; n < s373; ++n )
s680 = ((s271*)s680->s493())->s595( *( (size_t*)&s372[0] + n ) );
return s680->s493();}
s480* s368::s375(){
if( s372.empty() )
return s370.s15<s480*>();
s480*	s680 = ((s480*)s370.s15<s271*>()->s595( *(size_t*)&s372[0] ));
for( size_t n = 1; n < s373; ++n )
s680 = (s480*)((s271*)s680)->s595( *( (size_t*)&s372[0] + n ) );
return s680;}
void s368::s974( const std::vector<std::wstring> &s813 ){
auto it = std::find( begin( s813 ), end( s813 ), s614() );
if( it != end( s813 ) ) {
s489 = s1055;
s490 = Types.No;
s373 = std::distance( begin( s813 ), it );
s370 = new s343( NULL, (int)s373 ); //s772.s15<s480*>();
}}
s483 s368::s494( s480** s273, size_t s495 ){
return s374()->s494( s273, s495 );}
s480* s368::s493(){
s482 s680 = s374();
if( s680.s14() )
return s680->s493();
else
return NULL;}
/*bool s368::s498( const s480* s499 ) const
{
if( s499->s491() == s472 )
return s374()->s498( ((s368*)s499)->s374() );
return s374()->s498( s499 );
}*/
s270* s368::s332( s588* s2041, s271* impl ) const{
s368* s680 = new s368( *this, NULL );
return s680;}
void s368::s2117( s588* s2041, s271* impl, bool s2159 ){
if( s489 != s1055 && (1 || s370.s14() )) {
reset();
s497( (s271*)s2041, s2159 );}}
void s368::s376( size_t off, const s480* proto ){
s372.push_back( off );
s373 = s372.size();
s371 = proto;}
void s368::s1332( s368* ptr ){
s489 = s1326;
s372.clear();
s373 = 0;
s370 = ptr;
s371 = NULL;}
void s368::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2140[20];
#ifdef WIN32		
_swprintf( s2140, L"%p", (uint64_t*)s370.s15<void*>() );
#else
swprintf( s2140, 20, L"%06x", (uint64_t*)s370.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s196 ) << L"DataRef : " << s369
<< L"; Root: " << s2140;
if( s372.size() )
buf << L"; off: " << s372[0];
buf << endl;
if( !s196 && s370.s14() ) {
buf << s4::fill_n_ch( L' ', s196 ) << L"RootPtr : " << endl;
s370->s303( pd, s196 + s416 );}}
void s1587::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
wchar_t s2172[20];
#ifdef WIN32		
_swprintf( s2172, L"%p", (uint64_t*)pobj.s15<void*>() );
#else
swprintf( s2172, 20, L"%06x", (uint64_t*)pobj.s15<void*>() );
#endif	
buf << s4::fill_n_ch( L' ', s196 ) << L"DataPointer : " 
<< L" Pointer: " << s2172 << endl;
if( pobj.s14() ) {
buf << s4::fill_n_ch( L' ', s196 ) << L"Object : " << endl;
pobj->s303( pd, s196 + s416 );}}
template<class s1301, class Der>
s333::s338 s1295<s1301, Der>::s345;
template<class s1301, class Der>
const s333::s338& s1295<s1301, Der>::s339() const{
return s345; }
template<class s1301, class Der>template <class s1518, class s1519>
void s1295<s1301, Der>::s1520( s480* src, s480* s771 ){
*((s1518*)s771)->s354() = (s1519) ( (Der*)src )->s346;}
template <class s1301, class Der>
s480* s1295<s1301, Der>::s1524( const s480* p ) const{
Der* s680 = new Der( p->Pass() );
if( p->s1529( s349() ) )
p->s353( s680 );
s680->s1251();
return s680;}
template <class s1301, class Der>
size_t s1295<s1301, Der>::s319() const{
return (size_t)s346;}
template <class s1301, class Der>
inline bool s1295<s1301, Der>::operator==( const s480* p ) const{
return ( (Der*)p )->s346 == s346;}
template <class s1301, class Der>
inline bool s1295<s1301, Der>::operator<( const s480* p ) const{
return s346 < ( (Der*)p )->s346;}
template <class s1301, class Der>
void s1295<s1301, Der>::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << s346 << endl;}
#define s1513 s490
template <class s1301, class Der>
void s1295<s1301, Der>::s347(){
s345.insert( make_pair( L"abs", new s334( L"abs", &s1295<s1301, Der>::s401, s1513,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"set", new s334( L"set", &s1295<s1301, Der>::s384, s1513,
{ s1112( { /*Der::proto->s349()*/ s1500::s1260 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"sum", new s334( L"sum", &s1295<s1301, Der>::s385, s1513,
{ s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"dif", new s334( L"dif", &s1295<s1301, Der>::s386, s1513,
{ s1112( ), s1112( { s1500::s1260, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"mul", new s334( L"mul", &s1295<s1301, Der>::s387, s1513,
{ s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"div", new s334( L"div", &s1295<s1301, Der>::s388, s1513,
{ s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"pow", new s334( L"pow", &s1295<s1301, Der>::s389, s1514,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"pow", new s334( L"pow", &s1295<s1301, Der>::s389, s1140,
{ s1112( { s1140 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"sumeq", new s334( L"sumeq", &s1295<s1301, Der>::s390, s1513,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"difeq", new s334( L"difeq", &s1295<s1301, Der>::s391, s1513,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"muleq", new s334( L"muleq", &s1295<s1301, Der>::s392, s1513,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"diveq", new s334( L"diveq", &s1295<s1301, Der>::s393, s1513,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"not", new s334( L"not", &s1295<s1301, Der>::s410, s1138,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s1295<s1301, Der>::s395, s1138,
{ s1112( { s1500::s1537, s7::s1387 } ), s1112( { s1142 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"less", new s334( L"less", &s1295<s1301, Der>::s396, s1138,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"greater", new s334( L"greater", &s1295<s1301, Der>::s397, s1138,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"leq", new s334( L"leq", &s1295<s1301, Der>::s398, s1138,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"geq", new s334( L"geq", &s1295<s1301, Der>::s399, s1138,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"neq", new s334( L"neq", &s1295<s1301, Der>::s400, s1138,
{ s1112( { s1500::s1537 } ), s1112( { s1142 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"within", new s334( L"within", &s1295<s1301, Der>::s2081, s1138,
{ s1112( { s1500::s1537, s1500::s1537 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"max", new s334( L"max", &s1295<s1301, Der>::s1949, s1513,
{ s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"min", new s334( L"min", &s1295<s1301, Der>::s1950, s1513,
{ s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"mod", new s334( L"mod", &s1295<s1301, Der>::s402, s1513,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"divrem", new s334( L"divrem", &s1295<s1301, Der>::s2293, s1513,
{ //s1112( { s1500::s1537 } ), 
s1112( { s1500::s1537, s1500::s1537, s1500::s1537 } ) }, 3, 3 ) ) );
s345.insert( make_pair( L"sqrt", new s334( L"sqrt", &s1295<s1301, Der>::s403, s1140,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"nroot", new s334( L"nroot", &s1295<s1301, Der>::s404, s1140,
{ s1112( { s1141 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"to-Double", new s334( L"to-Double", &s1295<s1301, Der>::s405, s1140,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"to-Byte", new s334( L"to-Byte", &s1295<s1301, Der>::s1583, s1297,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"to-Int", new s334( L"to-Int", &s1295<s1301, Der>::s409, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"to-Long", new s334( L"to-Long", &s1295<s1301, Der>::s1535, s1514,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"to-ULong", new s334( L"to-ULong", &s1295<s1301, Der>::s1536, s1515,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"to-String", new s334( L"to-String", &s1295<s1301, Der>::s1489, s1143,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"read", new s334( L"read", &s1295<s1301, Der>::s406, s1513,
{ s1112() }, 0, 0, false ) ) );}
template<class s1301, class Der>
s1053 s1295<s1301, Der>::
s1178( const std::wstring& s1540, const std::vector<s482>& l ) const{
s1053 s680 = 0;
if( 0 && s1540 == L"mod" )
s680 = this->s349();
return s680;}
#undef s691
#define s691 ((Der*)(s481*)*s273)
#define s692 ((s357*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
template<class s1301, class Der>
inline void s1295<s1301, Der>::s384( s480** s273, size_t n ){
s273[2]->s353( s273[1] );
s273[1]->s1251();
*s273 = s273[1];}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s401( s480** s273, size_t s495 ){
s1301 t = ( (Der*)DR )->s346;
if( t >= 0 )
s691->s346 = t;
else
s691->s346 = -t;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s385( s480** s273, size_t s495 ){
Der tmp;
s691->s346 = ( (Der*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
s691->s346 += tmp.s346;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s386( s480** s273, size_t s495 ){
Der tmp;
s691->s346 = ( (Der*)DR )->s346;
if( s495 == 2 )
s691->s346 = -s691->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
s691->s346 -= tmp.s346;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s387( s480** s273, size_t s495 ){
Der tmp;
s691->s346 = ( (Der*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
s691->s346 *= tmp.s346;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s388( s480** s273, size_t s495 ){
Der tmp;
s691->s346 = ( (Der*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
s691->s346 /= tmp.s346;
}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s389( s480** s273, size_t s495 ){
if( DR->s349() == Types.Double || s273[2]->s349() == Types.Double ) {
s273[2]->s353( s273[0] );
*( (s1292*)s273[0] )->s354() = (s1301)std::pow( (double)( (Der*)DR )->s346, (double)*( (s1292*)s273[0] )->s354() );}
else {
int64_t i = ( (Der*)DR )->s346;
s273[2]->s353( s273[0] );
int64_t e = *((s1292*)s273[0])->s354();
int64_t s680 = -1;
if( e == 0 ) s680 = 1;
else if( e == 1 ) s680 = i;
else {
s680 = 1;
while( 1 ) {
if( ( e & 1 ) == 1 ) {
s680 = s680 * i;
--e;}
if( e == 0 ) break;
e /= 2;
i *= i;}}
*( (s1292*)s273[0] )->s354() = s680;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s390( s480** s273, size_t s495 ){
s273[2]->s353( s273[0] );
( (Der*)DR )->s346 += s691->s346;
s691->s346 = ( (Der*)DR )->s346;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s391( s480** s273, size_t s495 ){
s273[2]->s353( s273[0] );
( (Der*)DR )->s346 -= s691->s346;
s691->s346 = ( (Der*)DR )->s346;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s392( s480** s273, size_t s495 ){
s273[2]->s353( s273[0] );
( (Der*)DR )->s346 *= s691->s346;
s691->s346 = ( (Der*)DR )->s346;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s393( s480** s273, size_t s495 ){
s273[2]->s353( s273[0] );
( (Der*)DR )->s346 /= s691->s346;
s691->s346 = ( (Der*)DR )->s346;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s395( s480** s273, size_t s495 ){
bool s680 = true;
Der tmp;
for( size_t i = 2; i < s495; ++i ) {
s273[i]->s353( &tmp );
if( ( (Der*)DR )->s346 != tmp.s346 ) {
s680 = false;
break;}}
*s692->s354() = s680;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s410( s480** s273, size_t s495 ){
if( ((bool)( (Der*)DR )->s346) == false )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s396( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( ( (Der*)DR )->s346 < tmp.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s397( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( ( (Der*)DR )->s346 > tmp.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s398( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( ( (Der*)DR )->s346 <= tmp.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s399( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( ( (Der*)DR )->s346 >= tmp.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s400( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( ( (Der*)DR )->s346 != tmp.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s2081( s480** s273, size_t s495 ){
Der tmp, tmp1;
s273[2]->s353( &tmp );
s273[3]->s353( &tmp1 );
if( ( (Der*)DR )->s346 >= tmp.s346 && ((Der*)DR)->s346 <= tmp1.s346 )
*s692->s354() = true;
else
*s692->s354() = false;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1949( s480** s273, size_t s495 ){
Der tmp;
*s691->s354() = ( (Der*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
if( *s691->s354() < tmp.s346 )
*s691->s354() = tmp.s346;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1950( s480** s273, size_t s495 ){
Der tmp;
*s691->s354() = ( (Der*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
s273[n]->s353( &tmp );
if( *s691->s354() > tmp.s346 )
*s691->s354() = tmp.s346;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s402( s480** s273, size_t s495 ){
Der tmp;
s273[2]->s353( &tmp );
if( tmp.s346 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
s691->s346 = ((Der*)DR)->s346 % tmp.s346;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s2293( s480** s273, size_t s495 ){
Der _div;
s273[2]->s353( &_div );
if( _div.s346 == 0 )
throw new s16( L"division by zero: " + std::to_wstring( (int)*DR ) + L" % 0" );
if( s495 == 5 ) {
s355 _dnum( s273[1]->Pass(), 0.0 );
s273[1]->s353( &_dnum );
double d = *_dnum.s354() / _div.s346;
std::int64_t _quot = (std::int64_t)floor( d );
((Der*)s273[3])->s346 = (s1301) _quot;
std::int64_t _rem = (std::int64_t)*_dnum.s354() - _quot * _div.s346;
((Der*)s273[4])->s346 = (s1301)_rem;
s273[3]->s1251();
s273[4]->s1251();
s691->s346 = (s1301)_rem;}}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s403( s480** s273, size_t s495 ){
*( (s355*)s273[0] )->s354() = ::sqrt( (double)*DR );}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s404( s480** s273, size_t s495 ){
*( (s355*)s273[0] )->s354() = ::pow( ((Der*)DR)->s346, 1.0 / (double)*PARN( 2 ) );
}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s405( s480** s273, size_t s495 ){
*( (s355*)s273[0] )->s354() = (double)*DR;}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1583( s480** s273, size_t s495 ){
s273[1]->s353( s273[0] );}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s409( s480** s273, size_t s495 ){
s273[1]->s353( s273[0] );}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1535( s480** s273, size_t s495 ){
s273[1]->s353( s273[0] );}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1536( s480** s273, size_t s495 ){
s273[1]->s353( s273[0] );}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s1489( s480** s273, size_t s495 ){
*( (s356*)s273[0] )->s354() = DR->to_wstring();}
template<class s1301, class Der>
inline void s1295<s1301, Der>::s406( s480** s273, size_t s495 ){
int i;
wstring s92 = L"";//( (s356*)s273[2] )->to_wstring();
wstring si = consutils::s99( s92, false );
try {
i = std::stoi( si );}
catch( std::invalid_argument& ) {
throw new s16( L"Error: invalid input; integer is required." );}
s691->s346 = i;}
s343::s343( s261* s299, s271* s585 )
: s1295( s299, s585, NULL ){
s490 = Types.Int;
s346 = (s1374)s299->TR().s1246();
s1664( s7::s861 );}
s343::s343( s261* s299, int i, s271* s585 )
: s1295( s299, s585, NULL ){
if( !Types.Bool ) {
s490 = 0;
wh = s7::s861;}
else {
s490 = Types.Int;
s346 = i;
s1251();}}
s343::s343( const s343& r )
: s1295( r ){
s299->s2247( &r, this );}
s343::s343( s261* s299, s271* s585, const vector<s270*>& l, const s262* ast_ )
: s1295( s299, s585, ast_ ){
if( l.size() ) {
s2238* s273 = new s2238();
s273->assign( begin( l ), end( l ) );
s299->s2242( this, s273 );}
s490 = Types.Int;
s346 = (s1374)s299->TR().s1246();
s1664( s7::s861 );}
s343::s343( s261* s299, const std::wstring& s, size_t& pos, s271* s585 )
: s1295( s299, s585, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s152 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s152, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1251();}
else
s152 = s299->TR().s1246();
s346 = (int)s152;
pos = pend ? ( pend - pst ) : string::npos;
s490 = Types.Int;}
s343::~s343(){
if( s299 )
s299->s2248( this );}
s480* 
s343::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s_ = s694.s290();
size_t pos = 0;
if( s_.find( L"Int(" ) == 0 ) {
wstring s = s4::s52( s_.substr( 4, s_.size() - 5 ), s48 );
if( s.empty() )
return new s343( s299, s585 );
vector<s270*> s698;
s270::s1322( s694, s299, s585, s331, s698 );
return new s343( s299, s585, s698, &s694 );}
else {
if( s_ == L"-0" )
return s1509;
try {
return new s343( s299, s_, pos, s585 );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s24 )
return NULL;
else
throw e;}}
return NULL;}
void s343::s347(){
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );
s299->TR().s1152( s490, s7::s1512, s1500::s1537 );
s1295<int32_t, s343>::s347();
s345 = s1295<int32_t, s343>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s343::s1226, s1141,
{ s1112(), s1112( { Types.String } ), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"to-Char", new s334( L"to-Char", &s343::s2290, s1566,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"randr", new s334( L"randr", &s343::s2307, s1141, //0
{ s1112( { s1500::s1260 } ), s1112() }, 0, 1 ) ) );
s299->TR().s1521( s490, Types.Long );}
s1053 s343::s1178( s1889& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"randr" )
s680 = s1141;
else
s680 = s1295::s1178( s1540, l );
return s680;}
s480* s343::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s343( s299, s585, l, ast_ );}
void s343::s497( const s271* s872, bool ){
auto s273 = s299->s2248( this );
if( s273 ) {
assert( s273->size() == 1 );
for( size_t n = 0; n < s273->size(); ++n ) {
s482 par = s273->at( n );
if( par->s491() == s471 ) {
s346 = (int)*par;}
else if( par->s491() != s472 ) {
s482 s152 = s270::s1010( s299, par, ns, (s588*)ns, ns->s2153(), false );
if( s299->s1319() ) {
s346 = (int)*s152->s494( 0, 0 );}
else {
s273->at( n ) = s152;}}
else {
if( 1 || s299->s1319() /*par.s15<s368*>()->s378().s14()*/ ) {
if( par.s15<s368*>()->s378().s13() )
par->s497( s872, false );
s346 = (int)*par.s15<s368*>()->s374();}}}
delete s273;
s1251(); // ???DEBUG??? 220703
}}
inline bool
s343::s1529( s1053 s616 ) const{
if( ( s616 == s1515 && s346 >= 0 ) ||
( s616 == s1297 && s346 >= 0 && s346 <= 255 ) )
return true;
return s270::s1529( s616 );}
s270* s343::s332( s588* s2041, s271* impl ) const{
return new s343( *this );}
void s343::s353( s270* p ) const{
if( p->s349() == Types.Int )
*((s343*)p)->s354() = s346;
else if( p->s349() == s1297 )
*((s1284*)p)->s354() = s346;
else if( p->s349() == s1514 )
*((s1292*)p)->s354() = s346;
else if( p->s349() == s1515 )
*((s1517*)p)->s354() = s346;
else if( p->s349() == s1138 )
*( (s357*)p )->s354() = (s346 != 0);
else if( p->s349() == s1140 )
*( (s355*)p )->s354() = (double)s346;
else if( p->s349() == s1566 )
*( (s1560*)p )->s354() = (s1560::s1374)s346;
else
throw new s16( L"No conversion from " + s350() + L" to " + p->s350() );}
inline void s343::s1226( s480** s273, size_t s495 ){
s343* plv = NULL;
if( s495 == 3 && s273[2]->s349() == Types.String ) {
size_t pos = 0;
plv = new s343( ( (s343*)s273[1] )->s299, *( (s356*)s273[2] )->s354(), pos, 
( (s343*)s273[1] )->ns );
plv->s1251();}
else {
plv = new s343( ( (s343*)s273[1] )->s299, ( (s343*)s273[1] )->ns );
s343& lv = *plv;
if( s495 == 2 )
;// lv.s346 = 0;
else if( s495 == 3 ) {
s480* p = s273[2];
if( p->s349() == s1141 )
lv.s346 = *( (s343*)p )->s354();
else if( p->s349() == s1140 )
lv.s346 = ( s1374 )*( (s355*)p )->s354();
else if( p->s349() == s1138 )
lv.s346 = ( s1374 )*( (s357*)p )->s354();
else
throw new s16( L"no conversion to Int from type: " + p->s350() );
plv->s1251();}
else
throw new s16( L"unknown parameters to Int() constructor" );}
s273[0] = plv;}
inline void s343::s2290( s480** s273, size_t s495 ){
*((s1560*)s273[0])->s354() = (wchar_t)(int)*s273[1];}
inline void s343::s2307( s480** s273, size_t s495 ){
int mn, mx;
if( s495 == 2 ) {
mn = 0;
mx = (int)*s273[1];}
else {
mn = (int)*s273[1];
mx = (int)*s273[2];}
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(mn, mx);
*((s343*)s273[0])->s354() = dist( mt );}
wstring s343::to_wstring( uint32_t s1552 ) const {
wstring s680;
if( s346 > 0 && ( s1552 & s1547 ) )
s680 = L"+";
if( s1552 & s1546 )
s680 += s4::s1551( s346 );
else
s680 += std::to_wstring( s346 ); 
return s680;}
void s343::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
if( s1194() )
ss << s346;
else
ss << L"_undef_";}
void s343::to_null(){
s270::to_null();
s346 = 0;}
void s343::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << s346;}
s1292::s1292( s261* s299 )
: s1295( s299, NULL, NULL ){
s490 = Types.Long;
s346 = s299->TR().s1246();
s1664( s7::s861 );}
s1292::s1292( s261* s299, int64_t i )
: s1295( s299, NULL, NULL ){
if( !Types.Long ) {
s490 = 0;
s1664( s7::s861 );}
else {
s490 = Types.Long;
s346 = i;
s1251();}}
s1292::s1292( const s1292& r )
: s1295( r ){}
s1292::s1292( s261* s299, const std::wstring& s, size_t& pos )
: s1295( s299, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long long s152 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1532( pst, &s152, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1251();}
else
s152 = s299->TR().s1246();
s346 = (int64_t)s152;
pos = pend ? ( pend - pst ) : string::npos;
s490 = Types.Long;}
void s1292::s347(){
s1295<int64_t, s1292>::s347();
s345 = s1295<int64_t, s1292>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1292::s1226, s1514,
{ s1112(), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );
s299->TR().s1152( s490, s7::s1512, s1500::s1537 );}
s480* s1292::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s1292( s299, L"", pos );}
void s1292::s497( const s271* s872, bool ){
s1251();}
s270* s1292::s332( s588* s2041, s271* impl ) const{
return new s1292( *this );}
void s1292::s353( s270* p ) const{
if( p->s349() == Types.Long )
*((s1292*)p)->s354() = s346;
else if( p->s349() == s1141 )
*((s343*)p)->s354() = (s343::s1374)s346;
else if( p->s349() == s1515 )
*((s1517*)p)->s354() = s346;
else if( p->s349() == s1138 )
*( (s357*)p )->s354() = (s346 != 0);
else if( p->s349() == s1140 )
*( (s355*)p )->s354() = (double)s346;
else
throw new s16( L"no conversion from " + s350() + L" to " + p->s350() );}
s480* 
s1292::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s = s694.s290();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1292( s299, s, pos );}
else if( s.find( L"Long(" ) == 0 ) {
size_t pos = 0;
return new s1292( s299, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Long" ) == 0 ) {
return s352( NULL, std::vector<s270*>(), &s694 );}
return 0;}
inline void s1292::s1226( s480** s273, size_t s495 ){
s1292* plv = new s1292( ( (s1292*)s273[1] )->s299, (s1374)0 );
s1292& lv = *plv;
if( s495 == 2 )
lv.s346 = 0;
else if (s495 == 3){
s480* p = s273[2];
if( p->s349() == Types.Int )
lv.s346 = *( (s343*)p )->s354();
else if( p->s349() == s1140 )
lv.s346 = (s1374)*( (s355*)p )->s354();
else if( p->s349() == s1138 )
lv.s346 = (s1374)*( (s357*)p )->s354();
else
throw new s16( L"no conversion to Long from type: " + p->s350() );}
else
throw new s16( L"unknown parameters to Long() constructor" );
lv.s1251();
s273[0] = plv;}
wstring s1292::to_wstring( uint32_t s1552 ) const{
wstring s680;
if( s346 > 0 && ( s1552 & s1547 ) )
s680 = L"+";
if( s1552 & s1546 )
s680 += s4::s1551( s346 );
else
s680 += std::to_wstring( s346 );
return s680;}
void s1292::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
ss << s346;}
s1517::s1517( s261* s299, s271* s585 )
: s1295( s299, s585, NULL ){
s490 = Types.s1516;
s346 = s299->TR().s1246();
s1664( s7::s861 );}
s1517::s1517( s261* s299, uint64_t i, s271* s585 )
: s1295( s299, s585, NULL ){
if( !Types.s1516 ) {
s490 = 0;
s1664( s7::s861 );}
else {
s490 = Types.s1516;
s346 = i;
s1251();}}
s1517::s1517( const s1517& r )
: s1295( r ){
s299->s2247( &r, this );}
s1517::s1517( s261* s299, s271* s585, const vector<s270*>& l, const s262* ast_ )
: s1295( s299, s585, ast_ ){
if( l.size() ) {
s2238* s273 = new s2238();
s273->assign( begin( l ), end( l ) );
s299->s2242( this, s273 );}
s490 = Types.Int;
s346 = (s1374)s299->TR().s1246();
s1664( s7::s861 );}
s1517::s1517( s261* s299, const std::wstring& s, size_t& pos, s271* s585 )
: s1295( s299, s585, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
unsigned long long s152 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s1533( pst, &s152, &pend ) ) {
if( errno == ERANGE )
throw new s16( L"value is out of range: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s24 );
throw new s16( L"1: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );}
s1251();}
else
s152 = s299->TR().s1246();
s346 = (uint64_t)s152;
pos = pend ? ( pend - pst ) : string::npos;
s490 = Types.s1516;}
void s1517::s347(){
s1295<s1374, s1517>::s347();
s345 = s1295<s1374, s1517>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1517::s1226, s1515,
{ s1112(), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"abs", new s334( L"abs", &s1517::s401, s1515,
{ s1112(), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"dif", new s334( L"dif", &s1517::s386, s1515,
{ s1112(), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );
s299->TR().s1152( s490, s7::s1512, s1500::s1537 );}
s480* s1517::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s1517( s299, L"", pos );}
void s1517::s497( const s271* s872, bool ){
s1251();}
s270* s1517::s332( s588* s2041, s271* impl ) const{
return new s1517( *this );}
void s1517::s353( s270* p ) const{
if( p->s349() == Types.s1516 )
*((s1517*)p)->s354() = s346;
else if( p->s349() == s1514 )
*((s1292*)p)->s354() = s346;
else if( p->s349() == s1141 )
*((s343*)p)->s354() = (s343::s1374)s346;
else if( p->s349() == s1138 )
*( (s357*)p )->s354() = (s346 != 0);
else if( p->s349() == s1140 )
*( (s355*)p )->s354() = (double)s346;
else
throw new s16( L"no conversion from " + s350() + L" to " + p->s350() );}
s480* 
s1517::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s = s694.s290();
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1517( s299, s, pos );}
else if( s.find( L"ULong(" ) == 0 ) {
size_t pos = 0;
return new s1517( s299, s.substr( 6, s.size() - 7 ), pos );}
else if( s.find( L"ULong" ) == 0 ) {
return s352( NULL, std::vector<s270*>(), &s694 );}
return 0;}
inline void s1517::s1226( s480** s273, size_t s495 ){
s1517* plv = new s1517( ( (s1517*)s273[1] )->s299, (s1374)0 );
s1517& lv = *plv;
if( s495 == 2 )
lv.s346 = 0;
else if (s495 == 3){
s480* p = s273[2];
if( p->s349() == Types.Int )
lv.s346 = *( (s343*)p )->s354();
else if( p->s349() == Types.Long )
lv.s346 = *( (s1292*)p )->s354();
else if( p->s349() == Types.Double )
lv.s346 = (s1374)*( (s355*)p )->s354();
else if( p->s349() == Types.Bool )
lv.s346 = (s1374)*( (s357*)p )->s354();
else
throw new s16( L"no conversion to ULong from type: " + p->s350() );}
else
throw new s16( L"unknown parameters to ULong() constructor" );
lv.s1251();
s273[0] = plv;}
wstring s1517::to_wstring( uint32_t s1552 ) const{
wstring s680;
if( s346 > 0 && ( s1552 & s1547 ) )
s680 = L"+";
if( s1552 & s1546 )
s680 += s4::s1551( s346 );
else
s680 += std::to_wstring( s346 );
return s680;}
void s1517::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
ss << s346;}
s1284::s1284( s261* s299 )
: s1295( s299, NULL, NULL ){
s490 = Types.Byte;
s346 = (s1374)s299->TR().s1246();
s1664( s7::s861 );}
s1284::s1284( s261* s299, tdbyte_t i )
: s1295( s299, NULL, NULL ){
s490 = Types.Byte;
if( !s490 )
s1664( s7::s861 );
else {
s346 = i;
s1251();}}
s1284::s1284( const s1284& r )
: s1295( r.s299, r.ns, NULL ){
wh = r.wh;
s490 = r.s490;}
s1284::s1284( s261* s299, const std::wstring& s, size_t& pos )
: s1295( s299, NULL, NULL ){
const wchar_t* pst = NULL;
wchar_t* pend = NULL;
long s152 = 0;
if( !s.empty() ) {
pst = s.c_str();
if( !s62( pst, &s152, &pend ) )
throw new s16( L"2: unknown syntax: " + s.substr( pos, 40 ),
(uint32_t)s16::s17::s20 );
s1664( s7::s860 );}
else
s152 = s299->TR().s1246();
s346 = (int)s152;
pos = pend ? ( pend - pst ) : string::npos;
s490 = Types.Byte;}
void s1284::s347(){
s1295<tdbyte_t, s1284>::s347();
s345 = s1295<tdbyte_t, s1284>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1284::s1226, s1297,
{ s1112(), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );
s299->TR().s1152( s490, s7::s1512, s1500::s1537 );}
s480* s1284::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s1284( s299, L"", pos );}
void s1284::s497( const s271* s872, bool ){
s1251();}
s270* s1284::s332( s588* s2041, s271* impl ) const{
return new s1284( *this );}
void s1284::s353( s270* p ) const{
if( p->s349() == Types.Byte )
*((s1284*)p)->s354() = s346;
else if( p->s349() == s1514 )
*((s1292*)p)->s354() = s346;
else if( p->s349() == s1515 )
*((s1517*)p)->s354() = s346;
else if( p->s349() == s1138 )
*( (s357*)p )->s354() = (s346 != 0);
else if( p->s349() == s1140 )
*( (s355*)p )->s354() = (double)s346;
else
throw new s16( L"no conversion from " + s350() + L" to " + p->s350() );}
s480* 
s1284::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s = s694.s290();
size_t pos = 0;
/*if( s.find_first_not_of( L"-0123456789" ) == std::string::npos ) {
size_t pos = 0;
return new s1284( s299, s, pos );
}*/
if( s694.s1298() == s349() )
return new s1284( s299, s, pos );
else if( s.find( L"Byte(" ) == 0  ) {
return new s1284( s299, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Byte" ) == 0 ) {
return s352( NULL, std::vector<s270*>(), &s694 );}
return 0;}
inline void s1284::s1226( s480** s273, size_t s495 ){
s1284* plv = new s1284( ( (s1284*)s273[1] )->s299, 0 );
s1284& lv = *plv;
if( s495 == 2 )
lv.s346 = 0;
else if( s495 == 3 )
s273[2]->s353( plv );
else
throw new s16( L"unknown parameters to Byte() constructor" );
lv.s1251();
s273[0] = plv;}
void s1284::s1919( Stream* s1918 ) const{
auto flags = s1918->s1914();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s346;
s1918->s1468( ss.str() );}
s1560::s1560( s261* s299 )
: s1295( s299, NULL, NULL ){
s490 = Types.Char;
s346 = (s1374)s299->TR().s1246();
s1664( s7::s861 );}
s1560::s1560( s261* s299, wchar_t i )
: s1295( s299, NULL, NULL ){
s490 = Types.Char;
if( !s490 )
s1664( s7::s861 );
else {
s346 = i;
s1251();}}
s1560::s1560( const s1560& r )
: s1295( r.s299, r.ns, NULL ){
wh = r.wh;
s490 = r.s490;}
s1560::s1560( s261* s299, const std::wstring& s, size_t& pos )
: s1295( s299, NULL, NULL ){
if( s.size() ) {
s346 = s[pos];}
s490 = Types.Char;}
void s1560::s347(){
s1295<wchar_t, s1560>::s347();
s345 = s1295<wchar_t, s1560>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1560::s1226, s1566,
{ s1112(), s1112( { s1566 } ), s1112( { s1143 } ), s1112( { s1141 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s1560::s395, s1138,
{ s1112( { s1566 } ), s1112( { s1143 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"neq", new s334( L"neq", &s1560::s400, s1138,
{ s1112( { s1566 } ), s1112( { s1143 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"isupper", new s334( L"isupper", &s1560::s2224, s1138,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"islower", new s334( L"islower", &s1560::s2222, s1138,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"isspace", new s334( L"isspace", &s1560::s2223, s1138,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"tolower", new s334( L"tolower", &s1560::s883, s1566,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"toupper", new s334( L"toupper", &s1560::s884, s1566,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"code-unit", new s334( L"code-unit", &s1560::s2281, s1141,
{ s1112() }, 0, 0 )));
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );
s299->TR().s1152( s490, s7::s1512, s1500::s1537 );}
s480* s1560::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s1560( s299, L"", pos );}
void s1560::s497( const s271* s872, bool ){
s1251();}
s270* s1560::s332( s588* s2041, s271* impl ) const{
return new s1560( *this );}
void s1560::s353( s270* p ) const{
if( p->s349() == Types.Char )
*( (s1560*)p )->s354() = s346;
else if( p->s349() == s1141 )
*( (s343*)p )->s354() = s346;
else if( p->s349() == s1514 )
*( (s1292*)p )->s354() = s346;
else if( p->s349() == s1515 )
*( (s1517*)p )->s354() = s346;
else if( p->s349() == s1138 )
*( (s357*)p )->s354() = ( s346 != 0 );
else if( p->s349() == s1140 )
*( (s355*)p )->s354() = (double)s346;
else
throw new s16( L"no conversion from " + s350() + L" to " + p->s350() );}
s480* 
s1560::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s = s694.s290();
size_t pos = 0;
if( s694.s1298() == s349() )
return new s1560( s299, s, pos );
else if( s.find( L"Char(" ) == 0 ) {
return new s1560( s299, s.substr( 5, s.size() - 6 ), pos );}
else if( s.find( L"Char" ) == 0 ) {
return s352( NULL, std::vector<s270*>(), &s694 );}
return 0;}
inline void s1560::s1226( s480** s273, size_t s495 ){
s1560* plv = new s1560( ( (s1560*)s273[1] )->s299, 0 );
s1560& lv = *plv;
if( s495 == 2 )
lv.s346 = 0;
else if( s495 == 3 )
s273[2]->s353( plv );
else
throw new s16( L"unknown parameter to Char() constructor" );
lv.s1251();
s273[0] = plv;}
inline void s1560::s395( s480** s273, size_t s495 ){
s1560* plv = (s1560*)s273[1];
s480* s2257 = s273[2];
if( s2257->s349() == s1566 ) {
if( *plv->s354() == *((s1560*)s2257)->s354() )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}
else {
if( ((s356*)s2257)->s354()->size() == 1 && *plv->s354() == ((s356*)s2257)->s354()->at(0) )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}}
inline void s1560::s400( s480** s273, size_t s495 ){
s1560* plv = (s1560*)s273[1];
s480* s2257 = s273[2];
if( s2257->s349() == s1566 ) {
if( *plv->s354() != *((s1560*)s2257)->s354() )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}
else {
if( ((s356*)s2257)->s354()->size() == 1 && *plv->s354() == ((s356*)s2257)->s354()->at(0) )
*( (s357*)s273[0] )->s354() = false;
else
*( (s357*)s273[0] )->s354() = true;}}
inline void s1560::s2224( s480** s273, size_t s495 ){
wchar_t wc = ((s1560*)DR)->s346;
*((s357*)*s273)->s354() = iswupper( wc );}
inline void s1560::s2222( s480** s273, size_t s495 ){
wchar_t wc = ((s1560*)DR)->s346;
*((s357*)*s273)->s354() = iswlower( wc );}
inline void s1560::s2223( s480** s273, size_t s495 ){
wchar_t wc = ((s1560*)DR)->s346;
*((s357*)*s273)->s354() = iswspace( wc );}
inline void s1560::s884( s480** s273, size_t s495 ){
wchar_t wc = ((s1560*)DR)->s346;
((s1560*)DR)->s346 = towupper( wc );
*s273 = s273[1];}
inline void s1560::s883( s480** s273, size_t s495 ){
wchar_t wc = ((s1560*)DR)->s346;
((s1560*)DR)->s346 = towlower( wc );
*s273 = s273[1];}
inline void s1560::s2281( s480** s273, size_t s495 ){
*((s343*)s273)->s354() = (int)((s1560*)DR)->s346;}
void s1560::s1919( Stream* s1918 ) const{
auto flags = s1918->s1914();
wstringstream ss;
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss << s346;
s1918->s1468( ss.str() );}
s2394 s2309::_P2_ARR[] = {1,2,4,8,16,32,64,128,256,512,1024,
2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,
2097152,4194304,8388608};
s2309 s2380( std::to_wstring( s2316 ) );
void s2352( s2398& v ){
if( v.empty() ) return;
int i = (int)v.size();
while( i > 0 && v[--i] == 0 );
v.resize( i + 1 );}
s2309::s2309( const s2309& r, bool s2390 )
: s2344( r.s2344 ), _val( r._val ), s2339( r.s2339 ),
s2342( s2390 ){
if( s2332() ) {
if( ( s2342 && s2344 > 0 ) || ( !s2342 && s2344 < 0 ) )
s2344 = -s2344;}}
s2309::s2309( s2382 s1057, bool s2390 )
: s2344(0), s2339( s1057 ), s2342( s2390 ){}
s2309::s2309( const wstring& s )
: s2344(0), s2339( NULL ), s2342( false ){
s1944( s );}
s2309::s2309( s2394 sm )
: s2344( sm ), s2339( NULL ), s2342( sm < 0 ){}
void s2309::reset(){
_val.clear();
s2344 = 0;
s2339 = NULL;
s2342 = false;}
s2398& s2309::s1411(){
if( s2339 ) s2339 = NULL;
return _val;}
void s2309::s2406(){
if( _val.empty() ) return;
s2352( _val );
s2354();}
void s2309::s2413( s2309& s152 ){
s152.s2387( *this );
s152.s2388( false );}
int s2309::s2325( const s2398& l, const s2398& r ){
if( l.size() != r.size() ) {
return l.size() > r.size() ? 1 : -1;}
for(auto s2376 = l.rbegin(),s2377 = r.rbegin(); s2376 != l.rend(); s2376++,s2377++) {
if (*s2376 != *s2377) return *s2376 > *s2377 ? 1 : -1;}
return 0;}
int s2309::s2325( s2394 b ) const{
if( !s2332() )	return 1;
if( std::abs( s2344) > std::abs( b ) )
return 1;
return ( std::abs( s2344) < std::abs( b ) ) ?
-1 : 0;}
size_t s2309::s2393() const{
if( _val.size() )
return 0;
if( s2344 <= INT8_MAX )
return 8;
if( s2344 <= INT16_MAX )
return 16;
if( s2344 <= INT32_MAX )
return 32;
if( s2344 <= INT64_MAX )
return 64;
return 0;}
bool s2309::s2330() const{
if( s2323().size() != 3 )
return s2323().size() < 3;
if( s2323()[2] != 92233 ) return s2323()[2] < 92233;
if( s2323()[1] != 7203685 ) return s2323()[1] < 7203685;
return (s2323()[0] - s2342 ) <= 4775807;}
double s2353( double d ){
if( d > 0 ) return std::floor( d );
return std::ceil( d );}
void s2309::s2351(){
if( !_val.empty() ) return;
s2394 s346;
bool s2421 = false;
if( s2344 == s2317 ) {
s346 = std::abs( s2344 + 1 );
s2421 = true;}
else s346 = std::abs( s2344 );
if( s346 < s2314 )
_val.push_back( s346 );
else if( s346 < _BASE2 ) {
_val.push_back( s346 % s2314 );
_val.push_back( (s2394) std::floor( ((double)s346) / s2314 ) );
}
else {
_val.push_back( s346 % s2314 );
_val.push_back( ((s2394) std::floor( ((double)s346) / s2314 )) % s2314 );
_val.push_back( (s2394) std::floor( ((double)s346) / _BASE2 ) );
if( s2421 ) _val[0] += 1;}
s2342 = ( s2344 < 0 );
s2344 = 0;
s2339 = NULL;}
bool s2309::s2354(){
if( s2332() )
return true;
if( s2330() ) {
size_t l = s2323().size();
if( l == 0 ) s2344 = 0;
else if( l == 1 ) s2344 = s2323()[0];
else if( l == 2 ) s2344 = s2323()[0] + s2323()[1] * s2314;
else if( l == 3 ) s2344 =  s2323()[0] + (s2323()[1] + s2323()[2] * s2314 ) * s2314;
else throw;
_val.clear();
if( s2344 == 0 ) s2342 = false;
if( s2342 ) s2344 *= -1;
return true;}
return false;}
void s2309::s2343( s2394 a, s2398& s152 ){
if( a < s2314 )
s152.push_back( a );
else if( a < _BASE2 ) {
s152.push_back( a % s2314 );
s152.push_back( (s2394) std::floor( ((long double)a ) / s2314 ) );
}
else {
s152.push_back( a % s2314 );
s152.push_back( ((s2394)std::floor( ((long double) a) / s2314 )) % s2314 );
s152.push_back( (s2394) std::floor( ((long double)a ) / _BASE2 ));
}}
size_t s2309::s319() const{
if( s2332() )
return (size_t) s2344;
size_t s680 = _val.size();
for(auto x : _val) {
x = ((x >> 32) ^ x) * 0xE1B250D31686427B;
x = (x >> 32) ^ x;
s680 ^= x + 0x21854D3C9E3779B9 + (s680 << 6) + (s680 >> 2);}
return s680;}
void s2309::s2318( const s2398& b, s2398& s152 ) const{
assert( s2323().size() >= b.size() );
const s2398& a = s2323();
size_t s2361 = a.size();
size_t s2363 = b.size();
s2394 s2324 = 0, s2349;
size_t i = 0;
s152.resize( s2361 );
for( i = 0; i < s2363; ++i ) {
s2349 = a[i] + b[i] + s2324;
s2324 = (s2349 >= s2314 ? 1 : 0);
s152[i] = s2349 - s2324 * s2314;}
while( i < s2361 ) {
s2349 = a[i] + s2324;
s2324 = (s2349 == s2314 ? 1 : 0);
s152[i++] = s2349 - s2324 * s2314;}
if( s2324 > 0 ) s152.push_back( s2324 );}
void s2309::s2318( s2394 s2324, s2398& s152 ) const{
assert( !s2332() );
const s2398& a = s2323();
size_t s2361 = a.size();
s2394 s2349;
size_t i = 0;
s152.resize( s2361 );
for( i = 0; i < s2361; ++i ) {
s2349 = a[i] - s2314 + s2324;
s2324 = (s2394) std::floor( ((long double)s2349) / s2314 );
s152[i] = s2349 - s2324++ * s2314;}
while( s2324 ) {
s152[i++] = s2324 % s2314;
s2324 = (s2394) std::floor( ((long double)s2324) / s2314 );
}}
void s2309::s2320( const s2309& b, s2309& s152 ) const{
if( s2332() ) {
if( (!b.s2342 && s2344 > s2316 - b.s2344) ||
( b.s2342 && s2344 < s2317 - b.s2344) ) {
s2309 _a( s2344, s2342 );
_a.s2351();
_a.s2318( b.s2344, s152.s1411() );}
else
s152.s2344 = s2344 + b.s2344;}
else {
s2318( std::abs( b.s2344 ), s152.s1411() );}
s152.s2388( s2342 );}
void s2309::s2319( const s2309& b, s2309& s152 ) const{
if( s2332() ) 
b.s2318( s2344, s152.s1411() );
else {
if( s2323().size() >= b.s2323().size() ) 
s2318( b.s2323(), s152.s1411() );
else
b.s2318( s2323(), s152.s1411() );}
s152.s2388( s2342 );}
void s2309::s2318( const s2398& l, const s2398& r,
s2398& s152 ){
s2384 pa, pb;
if( l.size() > r.size() ) { pa = (s2384) &l; pb = (s2384) &r; }
else { pa = (s2384) &r; pb = (s2384) &l; }
const s2398& a = *pa;
const s2398& b = *pb;
size_t s2361 = a.size();
size_t s2363 = b.size();
s2394 s2324 = 0, s2349;
size_t i = 0;
s152.resize( s2361 );
for( i = 0; i < s2363; ++i ) {
s2349 = a[i] + b[i] + s2324;
s2324 = (s2349 >= s2314 ? 1 : 0);
s152[i] = s2349 - s2324 * s2314;}
while( i < s2361 ) {
s2349 = a[i] + s2324;
s2324 = (s2349 == s2314 ? 1 : 0);
s152[i++] = s2349 - s2324 * s2314;}
if( s2324 > 0 ) s152.push_back( s2324 );}
void s2309::s2360( const s2309& b, s2309& s152 ) const{
s152.reset();
if( s2342 != b.s2342 )
s2396( s2309( b, !b.s2342 ), s152 );
else {
if( b.s2332() )
s2320( b, s152 );
else
s2319( b, s152 );}}
void s2309::s2414( const s2309& b ){
s2309 tmp(0);
s2360( b, tmp );
s2387( tmp );}
void s2309::s2441( const s2309& b ){
s2309 tmp(0);
s2381( b, tmp );
s2387( tmp );}
void s2309::s2419( const s2309& b ){
s2309 tmp(0);
s2418( b, tmp );
s2387( tmp );}
void s2309::s2447( const s2309& b ){
s2309 tmp(0);
s2396( b, tmp );
s2387( tmp );}
/*void s2309::s2346( const s2398& b, s2398& s152 ) const
{
const s2398& a = _val;
int s2361 = (int)a.size();
int s2363 = (int)b.size();
s152.resize( s2361 );
int64_t s2322 = 0, s2326, i = 0;
for( i = 0; i < s2363; ++i ) {
s2326 = a[i] - s2322 - b[i];
if( s2326 < 0 ) {
s2326 += s2314;
s2322 = 1;}
else
s2322 = 0;
s152[i] = s2326;}
for(; i < s2361; ++i )
s152[i] = a[i];
s152.resize( i -1 );
}*/
void s2309::s2346( const s2398& l, const s2398& r, s2398& s152 ){
s2384 pa, pb;
if( l.size() >= r.size() ) { pa = (s2384) &l; pb = (s2384) &r; }
else { pa = (s2384) &r; pb = (s2384) &l; }
const s2398& a = *pa;
const s2398& b = *pb;
size_t s2361 = a.size();
size_t s2363 = b.size();
s152.resize( s2361 );
int64_t s2322 = 0, s2326;
size_t i = 0;
for( i = 0; i < s2363; ++i ) {
s2326 = a[i] - s2322 - b[i];
if( s2326 < 0 ) {
s2326 += s2314;
s2322 = 1;}
else
s2322 = 0;
s152[i] = s2326;}
for( i = s2363; i < s2361; ++i ) {
s2326 = a[i] - s2322;
if( s2326 < 0 ) s2326 += s2314;
else {
s152[i++] = s2326;
break;}
s152[i] = s2326;}
for(; i < s2361; ++i )
s152[i] = a[i];
s2352( s152 );}
void s2309::s2346( const s2398& a, s2394 b, s2398& s152 ){
size_t s2361 = a.size();
s152.resize( s2361 );
s2394 s2324 = -b, s2326;
size_t i;
for( i = 0; i < s2361; ++i ) {
s2326 = a[i] + s2324;
s2324 = (s2394) std::floor( ((long double)s2326) / s2314 );
s2326 %= s2314;
s152[i] = s2326 < 0 ? s2326 + s2314 : s2326;}}
void s2309::s2348( const s2309& b, s2309& s152 ) const{
if( s2332() ) {
assert( b.s2342 == s2342 );{
s152.s2344 = s2344 - b.s2344;
if( s152.s2344 < 0 ) s152.s2342 = true;}}
else {
s2346( s2323(), std::abs( b.s2344 ), s152.s1411() );
s152.s2388( s2342 );}}
void s2309::s2347( const s2309& b, s2309& s152 ) const{
if( s2325( s2323(), b.s2323() ) >= 0 ) {
s2346( s2323(), b.s2323(), s152.s1411() );
s152.s2342 = s2342;}
else {
s2346( b.s2323(), s2323(), s152.s1411() );
s152.s2342 = !s2342;}}
void s2309::s2396( const s2309& b, s2309& s152 ) const{
s152.reset();
if( s2342 != b.s2342 ) {
s2360( s2309( b, !b.s2342 ), s152 );}
else {
if( b.s2332() )
s2348( b, s152 );
else
s2347( b, s152 );}
s152.s2406();}
void s2309::s2333( const s2398& b, s2398& s152 ) const{
const s2398& a = s2323();
size_t s2361 = a.size();
size_t s2363 = b.size();
size_t s2366 = s2361 + s2363;
s152.resize( s2366 );
s2394 s2337, s2324, s2355, s2362;
size_t i, j;
for( i = 0; i < s2361; ++i ) {
s2355 = a[i];
for( j = 0; j < s2363; ++j ) {
s2362 = b[j];
s2337 = s2355 * s2362 + s152[i + j];
s2324 = (s2394) std::floor( ((long double) s2337 ) / s2314 );
s152[i + j] = s2337 - s2324 * s2314;
s152[i + j + 1] += s2324;}}
s2352( s152 );}
void s2309::s2333( const s2398& a, const s2398& b, s2398& s152 ){
size_t s2361 = a.size();
size_t s2363 = b.size();
size_t s2366 = s2361 + s2363;
s152.resize( s2366 );
s2394 s2337, s2324, s2355, s2362;
size_t i, j;
for( i = 0; i < s2361; ++i ) {
s2355 = a[i];
for( j = 0; j < s2363; ++j ) {
s2362 = b[j];
s2337 = s2355 * s2362 + s152[i + j];
s2324 = (s2394) std::floor( ((double) s2337 ) / s2314 );
s152[i + j] = s2337 - s2324 * s2314;
s152[i + j + 1] += s2324;}}
s2352( s152 );}
void s2309::s2333( const s2398& a, s2394 b, s2398& s152 ){
size_t s2361 = a.size();
s152.resize( s2361 + 2 );
s2394 s2324 = 0, s2337;
size_t i;
for( i = 0; i < s2361; ++i ) {
s2337 = a[i] * b + s2324;
s2324 = (s2394) std::floor( ((double) s2337 ) / s2314 );
s152[i] = s2337 - s2324 * s2314;}
while( s2324 > 0 ) {
s152[i++] = s2324 % s2314;
s2324 = (s2394) std::floor( ((double) s2324 ) / s2314 );
}
s2352( s152 );}
s2398& s2392( const s2398& x, size_t n, s2398& s152 ){
s152.clear();
s152.resize( n + x.size() );
std::copy( x.begin(), x.end(), s152.begin() + n );
return s152;}
void s2309::s2335( const s2398& x, const s2398& y, 
s2398& s152 ){
size_t n = x.size() > y.size() ? x.size() : y.size();
if( n <= 30 ) {
s2333( x, y, s152 );
return;}
n = (size_t) std::ceil( ((double) n) / 2 );
size_t nx = (std::min)(x.size(), n);
size_t ny = (std::min)(y.size(), n);
s2398 a( x.begin(), x.begin() + nx );
s2398 b( x.begin() + nx, x.end() );
s2398 c( y.begin(), y.begin() + ny );
s2398 d( y.begin() + ny, y.end() );
s2398 ac, s2158, s2357, aAb, s2365;
s2335( a, c, ac );
s2335( b, d, s2158 );
s2318( a, b, aAb );
s2318( c, d, s2365 );
s2335( aAb, s2365, s2357 );
s2398 s2358, x1Sbd, SHx2, acAx3, SHx4;
s2346( s2357, ac, s2358 );
s2346( s2358, s2158, x1Sbd );
s2392( x1Sbd, n, SHx2 );
s2318( ac, SHx2, acAx3 );
s2318( acAx3, s2392( s2158, 2*n, SHx4), s152 );
s2352( s152 );}
bool s2397( double l1, double l2 ){
return -0.012 * l1 - 0.012 * l2 + 0.000015 * l1 * l2 > 0;}
void s2309::s2336( const s2309& b, s2309& s152 ) const{
if( s2332() ) {
if( ( s2344 == -1 && b.s2344 == s2317 ) ||
( b.s2344 == -1 && s2344 == s2317 ) ||
( b.s2344 && s2344 > s2316 / b.s2344 ) ||
( b.s2344 && s2344 < s2317 / b.s2344 ) ) {
s2309 _a( s2344, s2342 );
_a.s2351();
if( b.s2344 < s2314 )
s2333( _a.s2323(), b.s2344, s152.s1411() );
else {
s2309 _b( b );
_b.s2351();
s2333( _a.s2323(), _b.s2323(), s152.s1411() );}}
else {
s152.s2344 = s2344 * b.s2344;
s152.s2342 = (s152.s2344 < 0);}}
else {
s2309 _b( b );
_b.s2351();
s2333( s2323(), _b.s2323(), s152.s1411() );}}
void s2309::s2334( const s2309& b, s2309& s152 ) const{
if( s2332() )  {
if( s2344 < s2314 ) {
switch( s2344 ) {
case 0:	
s152.s2389( 0 ); break;
case 1:
s152.s2387( b ); break;
case -1:
s152.s2387( b ); s152.s2342 = !b.s2342; break;
default:
s2333( b.s2323(), s2344, s152.s1411() );}}
else {
s2309 _a( s2344, s2342 );
_a.s2351();
_a.s2333( b.s2323(), s152.s1411() );}}
else {
if( s2397( (double)s2323().size(), (double)b.s2323().size() ) )
s2335( s2323(), b.s2323(), s152.s1411() );
else
s2333( b.s2323(), s152.s1411() );}}
void s2309::s2381( const s2309& b, s2309& s152 ) const{
s152.reset();
if( b.s2332() )
s2336( b, s152 );
else
s2334( b, s152 );
s152.s2406();}
void s2309::_divmod1( const s2398& b, s2398& quot, s2398& rem ) const{
size_t s2361 = s2323().size();
size_t s2363 = b.size();
quot.resize( s2361 );
s2394 s2368 = b.back();
s2394 s2378 = (s2394) std::ceil( ((double)s2314) / ( 2 * s2368 ) );
s2398 s2369, s2386;
s2333( s2323(), s2378, s2386 );
s2333( b, s2378, s2369 );
s2394 s2385, s2324, s2321, q;
size_t i, l;
int s2391;
if( s2386.size() <= s2361 ) s2386.push_back( 0 );
s2369.push_back( 0 );
s2368 = s2369[ s2363 - 1 ];
for( s2391 = (int)(s2361 - s2363); s2391 >= 0; --s2391 ) {
s2385 = s2314 - 1;
if( s2386[s2391 + s2363] != s2368 ) {
s2385 = (s2394) std::floor( ((double)
s2386[s2391 + s2363] * s2314 + s2386[s2391 + s2363 - 1]) / s2368 );
}
s2324 = 0;
s2321 = 0;
l = s2369.size();
for( i = 0; i < l; ++i ) {
s2324 += s2385 * s2369[i];
q = (s2394) std::floor( ((double)s2324) / s2314 );
s2321 += s2386[s2391 + i] - (s2324 - q * s2314);
s2324 = q;
if( s2321 < 0 ) {
s2386[s2391 + i] = s2321 + s2314;
s2321 = -1;}
else {
s2386[s2391 + i] = s2321;
s2321 = 0;}}
while( s2321 != 0 ) {
s2385 -= 1;
s2324 = 0;
for( i = 0; i < l; ++i ) {
s2324 += s2386[s2391 + i] - s2314 + s2369[i];
if( s2324 < 0 ) {
s2386[s2391 + i] = s2324 + s2314;
s2324 = 0;}
else {
s2386[s2391 + i] = s2324;
s2324 = 1;}}
s2321 += s2324;}
quot[s2391] = s2385;}
s2352( quot );
s2309 s2340( &s2386, false );
s2398 s2350;
s2327( s2340.s2323(), s2378, rem, s2350 );}
void s2309::_divmod2( const s2398& b, s2398& quot, s2398& rem ) const{
size_t s2361 = s2323().size();
size_t s2363 = b.size();
s2394 s2331, xl, s2371, s2372;
s2398 s2338, ch;
while( s2361 ) {
s2338.push_front( s2323()[--s2361] );
s2352( s2338 );
if( s2325( s2338, b ) < 0 ) {
quot.push_back( 0 );
continue;}
xl = s2338.size();
s2371 = s2338.back() * s2314 + s2338[(size_t)xl - 2];
s2372 = b.back() * s2314 + b[s2363 - 2];
if( xl > (s2394)s2363 )
s2371 = ( s2371 + 1 ) * s2314;
s2331 = (s2394) std::ceil( ((long double) s2371) / s2372 );
do {
s2333( b, s2331, ch );
if( s2325( ch, s2338 ) ) break;
--s2331;
} while( s2331 );
quot.push_back( s2331 );
s2346( s2338, ch, rem );}
std::reverse( begin( quot  ), end( quot ) );}
void s2309::s2327( const s2398& a, s2394 b, s2398& quot, s2398& rem ){
size_t s2361 = a.size();
quot.resize( s2361 );
int i;
s2394 s2386 = 0, s2369, q;
for( i = (int)s2361 - 1; i >= 0; --i ) {
s2369 = s2386 * s2314 + a[i];
q = (s2394) s2353( (double) s2369 / b );
s2386 = s2369 - q * b;
quot[i] = (int) q;}
s2352( quot );
s2343( s2386, rem );}
void s2309::s2329( const s2309& b, s2309& quot, s2309& rem ) const{
if( !b.s2344 )
throw;
if( s2332() ) {
if( s2344 == s2317 && b.s2344 == -1 ) {
s2309 _a( s2344, s2342 );
_a.s2351();
_a.s2367( b, quot, rem );}
else {
auto s1793 = std::lldiv( s2344, b.s2344 );
quot.s2389( s1793.quot );
rem.s2389( s1793.rem );}}
else {
if( b.s2344 == 1 ) {
quot.s2387( *this );
rem.s2389( 0 );
return;}
if( b.s2344 == -1 ) {
quot.s2387( *this );
quot.s2342 = !s2342;
rem.s2389( 0 );
return;}
s2394 s2359 = abs( b.s2344 );
if( s2359 < s2314 ) {
s2327( s2323(), s2359, quot.s1411(), rem.s1411() );
rem.s2388( s2342 );
if( s2342 != b.s2342 )
quot.s2388( true );
return;}
s2309 _b( b, b.s2342 );
_b.s2351();
s2328( _b, quot, rem );}}
void s2309::s2328( const s2309& b, s2309& quot, s2309& rem ) const{
int _cmp = s2325( s2323(), b.s2323() );
if( _cmp == -1 ) {
quot.s2389( 0 );
rem.s2387( *this );
return;}
if( _cmp == 0 ) {
quot.s2389( s2342 == b.s2342 ? 1 : -1 );
rem.s2389( 0 );
return;}
if( s2323().size() + b.s2323().size() <= 200 )
_divmod1( b.s2323(), quot.s1411(), rem.s1411() );
else
_divmod2( b.s2323(), quot.s1411(), rem.s1411() );
if( s2342 != b.s2342 )
quot.s2388( quot.s2342 );
rem.s2388( s2342 );}
void s2309::s2367( const s2309& b, s2309& quot, s2309& rem ) const{
quot.reset();
rem.reset();
if( b.s2332() )
s2329( b, quot, rem );
else
s2328( b, quot, rem );	
rem.s2406();
quot.s2406();}
void s2309::s2360( int64_t b, s2309& s152 ) const{
s152.reset();
bool s2416 = ( b < 0 );
if( s2342 != s2416 )
s2348( s2309( s2416 ? b : -b ), s152 );
else
s2320( s2309( b ), s152 );
s152.s2406();}
void s2309::s2396( int64_t b, s2309& s152 ) const{
s152.reset();
bool s2416 = ( b < 0 );
if( s2342 != s2416 )
s2320( s2309( s2416 ? b : -b ), s152 );
else
s2348( s2309( b ), s152 );
s152.s2406();}
void s2309::s2381( int64_t b, s2309& s152 ) const{
s152.reset();
s2309 _b( b );
s2336( _b, s152 );
s152.s2406();}
void s2309::s2367( int64_t b, s2309& quot, s2309& rem ) const{
quot.reset();
rem.reset();
s2309 _b( b );
s2329( _b, quot, rem );
rem.s2406();
quot.s2406();}
void s2309::s2395(){
if( s2332() ) {
s2394 s892 = s2344;
if( s2344 && (s2344 > s2316 / s2344 )) {
s2309 s1793( 0 );
s2351();
if( s892 < s2314 )
s2333( s2323(), s892, s1793.s1411() );
else
s2333( s2323(), s2323(), s1793.s1411() );
s2387( s1793 );}
else
s2344 = s892 * s892;}
else {
s2309 s1793( 0 );
size_t len = s2323().size();
s1793.s2351();
s1793._val.resize( len + len );
s2394 s2337, s2324, s2355, s2356;
for( size_t i = 0; i < len; ++i ) {
s2355 = _val[i];
s2324 = 0 - s2355 * s2355;
for( size_t j = i; j < len; ++j ) {
s2356 = _val[j];
s2337 = 2 * (s2355 * s2356) + s1793._val[i + j] + s2324;
s2324 = (s2394) std::floor( ((double) s2337) / s2314 );
s1793._val[i + j] = s2337 - s2324 * s2314;}
s1793._val[i + len] = s2324;}
s2352( s1793.s1411() );
s2387( s1793 );}}
void s2309::s2469( s2394 n ){
if( std::abs( n ) > s2314 ) throw;
if( s2429() ) return;
if( n < 0 ) return s2470( -n );
s2309 s2411( *this ), _hp2(_HP2);
while( n >= _HP2_LEN ) {
s2411.s2441( _hp2 );
n -= ( _HP2_LEN - 1 );}
s2411.s2381( s2309( _P2_ARR[n] ), *this );}
void s2309::s2470( s2394 n ){
if( std::abs( n ) > s2314 ) throw;
if( s2429() ) return;
if( n < 0 ) return s2469( -n );
s2309 s2411( *this ), _hp2(_HP2), s2454(0), s2455(0);
while( n >= _HP2_LEN ) {
if( s2411.s2429() || (s2411.s2424() && s2411.s2428()) ) { s2387( s2411 ); return; }
s2411.s2367( _hp2, s2454, s2455 );
s2411.s2387( s2454 );
if( s2455.s2424() ) s2411.s2447( 1 );
n -= ( _HP2_LEN - 1 );}
s2411.s2367( _P2_ARR[n], s2454, s2455 );
s2387( s2454 );
if( s2455.s2424() ) s2447( 1 );}
void s2309::s2463(){
if( s2342 ) throw;
if( s2332() ) { s2389( (s2394)std::sqrt( s2344 ) ); return;}
s2394 bl = s2401() + 1; bl = bl >> (s2394)1;
s2309 a( ((s2394)1 << bl) ), b(0), _t(0);
while( true ) {
s2418( a, _t ); _t.s2414( a ); _t.s2470( 1 );
b.s2387( _t );
if( !a.s2375( b ) ){ s2387( a ); return; }
a.s2387( b );}}
int64_t s2312(int64_t i, int64_t e){
if( e == 0 ) return 1;
if( e == 1 ) return i;
int64_t s680 = 1;
while( 1 ) {
if ((e & 1) == 1) {
s680 = s680 * i;
--e;}
if( e == 0 ) break;
e /= 2;
i *= i;}
return s680;}
void s2309::s2383( int32_t b, s2309& s152 ) const{
s152.reset();
if( b == 0 ) s152.s2389( 1 );
else if( s2332() && s2344 == 0 ) s152.s2389( 0 );
else if( s2332() && s2344 == 1 ) s152.s2389( 1 );
else if( s2332() && s2344 == -1 ) {
if( s2374() ) s152.s2389( 1 );
else s152.s2389( -1 );}
else if( s2342 ) s152.s2389( 0 );
else {
double _d = NAN;
if( s2332() )
_d = std::pow( s2344, b );
if( isnormal( _d ) && _d < s2316 ) {
s152.s2389( (s2394) s2312( s2344, b ) );
return;}
s152.s2389( 1 );
s152.s2351();
s2309 _res1( 0 );
s2309 x( *this );
x.s2351();
while( true ) {
if( ( b & 1 ) == 1 ) {
s2333( s152.s2323(), x.s2323(), _res1.s1411() );
--b;
s152.s2387( _res1 );
_res1._val.clear(); _res1._val.push_back(0);}
if( !b ) break;
b /= 2;
x.s2395();}
s2352( s152.s1411() );}
s152.s2406();}
void s2309::s2418( const s2309& b, s2309& s152 ) const{
s2309 r(0);
s2367( b, s152, r );
s152.s2406();}
void s2309::s2438( const s2309& b, s2309& s152 ) const{
s2309 q(0);
s2367( b, q, s152 );
s152.s2406();}
void s2309::s2439( const s2309& b, s2309& s152 ) const{
s152.reset();
s2309 t(0), s2444(1), s2443( *this, false ), r( b ),
q(0), s2435(0),	s2434(0), s2411(0);
while( !s2443.s2429() ) {
r.s2418( s2443, q );
s2435.s2387( t );
s2434.s2387( r );
q.s2333( s2444.s2323(), s2411.s1411() );
s2346( s2435.s2323(), s2411.s2323(), s2444.s1411() );
q.s2333( s2443.s2323(), s2411.s1411() );
s2346( s2434.s2323(), s2411.s2323(), s2443.s1411() );}
if( !r.s2428() ) throw; // not co-prime
if( t.s2375( 0 ) ) t.s2414( b );
if( s2424() ) t.s2388( false );
s152.s2387( t );
s152.s2406();}
void s2309::s2440( const s2309& s2420, const s2309& mod, s2309& s152 ) const{
s152.reset();
if( mod.s2429() ) throw;
s152.s2387( 1 );
s2309 base(0);
s2438( mod, base );
s2309 exp( s2420 );
s2309 s2411(0);
if( exp.s2424() ) {
exp.s2441( s2309( -1 ) );
s2309 s2411(0);
base.s2439( mod, s2411 );
base.s2387( s2411 );}
while( exp.s2425() ) {
if( base.s2429() ) {
s152.s2387( 0 );
break;}
if( !exp.s2374() ) {
s152.s2381( base, s2411 );
s2411.s2438( mod, s152 );}
exp.s2419( s2309( 2 ) );
base.s2395();
base.s2438( mod, s2411 );
base.s2387( s2411 );}
s152.s2406();}
void s2309::s2468( const std::wstring& s ){
reset();
s1944( s );}
void s2309::s2389( s2394 s346 ){
_val.clear();
s2339 = NULL;
s2344 = s346;
s2342 = (s346 < 0);}
void s2309::s2387( const s2309& bl ){
_val = bl._val;
s2339 = bl.s2339;
s2344 = bl.s2344;
s2342 = bl.s2342;}
void s2309::s2387( int64_t s346 ){
_val.clear();
s2339 = NULL;
s2344 = s346;
s2342 = ( s346 < 0 );
s2351();}
void s2309::s2387( const wstring& s ){
reset();
s1944( s );
s2351();}
void s2309::s2388( bool s2390 ){
s2342 = s2390;
if( s2332() ) {
if( s2344 < 0 && !s2342 ) {
if( s2344 == s2317 )
s2351();
else
s2344 *= -1;}
else if( s2344 > 0 && s2342 )
s2344 *= -1;}}
bool s2309::s2373( const s2309& bl ) const{
if( s2332() != bl.s2332() )
return false;
if( s2332() )
return s2344 == bl.s2344;
if( s2342 != bl.s2342 || s2325( s2323(), bl.s2323() ) != 0 )
return false;
return true;}
bool s2309::s2373( s2394 b ) const{
if( s2332() ) return s2344 == b;
return false;}
bool s2309::s2375( const s2309& bl ) const{
if( s2342 != bl.s2342 )
return  s2342;
if( s2332() ) {
if( !bl.s2332() ) return true;
return s2344 < bl.s2344;}
int _cmp = s2325( s2323(), bl.s2323() );
if( ( _cmp > 0 && s2342 ) || ( _cmp < 0 && !s2342 ) )
return true;
return false;}
bool s2309::s2375( s2394 b ) const{
if( s2342 != ( b < 0 ) )
return  s2342;
int _cmp = s2325( b );
if( ( _cmp > 0 && s2342 ) || ( _cmp < 0 && !s2342 ) )
return true;
return false;}
bool s2309::s2374() const{
if( _val.empty() )
return ( ( s2344 & 1 ) == 0 );
else
return ( ( _val[0] & 1 ) == 0 );}
bool s2309::s2429() const{
if( s2332() ) return s2344 == 0;
return s2323().size() == 1 && s2323()[0] == 0;}
bool s2309::s2424() const{
if( s2332() )
return s2344< 0;
return s2342;}
bool s2309::s2425() const{
if( s2332() )
return s2344 > 0; // sic
return !s2342;}
bool s2309::s2428() const{
if( s2332() ) return s2344 == 1;
return s2323().size() == 1 && s2323()[0] == 1;}
bool s2309::s2462() const{
s2309 t( *this );
t.s2463();
t.s2395();
return s2373( t );}
int64_t s2309::s2404( const s2309& s346, const s2309& base, s2309& p ){
if( base.compare( s346 ) <= 0 ) {
s2309 s2446( base );
s2446.s2395();
int64_t e = s2404( s346, s2446, p );
s2309 t( 0 );
p.s2381( base, t );
if( t.compare( s346 ) <= 0 ) {
p.s2387( t ); return e * 2 + 1;}
else 
return e * 2;	}
p.s2389( 1 );
return 0;}
size_t s2309::s2401() const{
s2309 n( *this );
if( s2424() ) {
n.s2388( false );
n.s2447( 1 );}
if( n.s2429() ) return 0;
s2309 s2410( 0 );
auto s152 = s2404( n, 2, s2410 );
return (size_t) s152 + 1;}
bool s2309::s2423( const s2309& b ) const{
if( b.s2429() ) return false;
if( b.s2428() ) return true;
if( b.s2325( 2 ) == 0 ) return s2374();
s2309 rem( 0 );
s2438( b, rem );
return rem.s2429();}
s2394 s2309::s2456() const{
int64_t s2465 = 1 << 30;
int64_t s2464 = (s2314 & -s2314) * (s2314 & -s2314) | s2465;
s2394 s680;
if( s2332() )
s680 = s2344 | s2465;
else
s680 = ( _val[0] + _val[1] * s2314 ) | s2464;
return s680 & (-s680 + 1);}
void s2309::gcd( const s2309& _a, const s2309& _b, s2309& s152 ){
if( _a.s2373( _b ) || _b.s2429() ) {
s152.s2387( _a ); return;}
if( _a.s2429() ){
s152.s2387( _b ); return;}
s2309 a(_a, false), b(_b, false), c( 1 ), d( 0 ), t( 0 );
while( a.s2374() && b.s2374() ) {
s2309 d ((std::min)( a.s2456(), b.s2456() ));
a.s2419( d );
b.s2419( d );
c.s2441( d );}
while( a.s2374() ) a.s2419( a.s2456() );
while( true ) {
while( b.s2374() ) b.s2419( b.s2456() );
if( b.s2375( a ) ) {
s2309 t( b );
b.s2387( a );
a.s2387( t );}
b.s2447( a );
if( b.s2429() ) break;		}
if( c.s2428() ) s152.s2387( a );
else a.s2381( c, s152 );}
int s2309::s2422() const{
s2309 ab( *this, false );
if( ab.s2428() ) return 0;
if( ab.s2332() && ( ab.s2344== 2 || ab.s2344== 3 ||
ab.s2344== 5 ) ) return 1;
if( ab.s2374() || ab.s2423( s2309( 3 ) ) || 
ab.s2423( s2309( 5 ) ) ) return 0;
if( s2375( s2309( 49 ) ) ) return 1;
return -1;}
bool s2309::s2437( const s2309& n, const vector<int64_t>& a ){
s2309 s2442( n );
s2442.s2447( 1 );
s2309 b( s2442 );
s2309 x( 0 ), s2411( 0 );
size_t r = 0, d, i;
bool s585 = false;
while( b.s2374() ) {	b.s2419( 2 ); ++r; }
for( i = 0; i < a.size(); ++i ) {
if( n.s2375( a[i] ) ) continue;
s2309( a[i] ).s2440( b, n, x );
if( x.s2428() || x.s2373( s2442 )) continue;
for( d = r - 1; d != 0; --d ) {
x.s2395(); x.s2438( n, s2411 );
x.s2387( s2411 );
if( x.s2428() ) return false;
if( x.s2373( s2442 ) ) { s585 = true; break; }}
if( s585 ) { s585 = false; continue; }
return false;}
return true;}
bool s2309::s2437( const s2309& n, const vector<s2309>& a ){
s2309 s2442( n );
s2442.s2447( 1 );
s2309 b( s2442 );
s2309 x( 0 ), s2411( 0 );
size_t r = 0, d, i;
bool s585 = false;
while( b.s2374() ) {	b.s2419( 2 ); ++r; }
for( i = 0; i < a.size(); ++i ) {
if( n.s2375( a[i] ) ) continue;
a[i].s2440( b, n, x );
if( x.s2428() || x.s2373( s2442 )) continue;
for( d = r - 1; d != 0; --d ) {
x.s2395(); x.s2438( n, s2411 );
x.s2387( s2411 );
if( x.s2428() ) return false;
if( x.s2373( s2442 ) ) { s585 = true; break; }}
if( s585 ) { s585 = false; continue; }
return false;}
return true;}
bool s2309::s2426( bool s150 ) const{
int s2432 = s2422();
if( s2432 != -1 ) return s2432;
s2309 n( *this, false );
size_t s2415 = n.s2401();
if( s2415 <= 64 ) {
return s2437( n, vector<int64_t> ( { 2,3,5,11,13,17,19,
23,29,31,37 } ) );}
double s2436 = 0.6931471805599453 * s2415;
size_t t = (size_t) std::ceil( s150 ? 
(2.0 * std::pow( s2436, 2.0 )) : s2436 );
vector<int64_t> a;
for( size_t i = 0; i < t; ++i )
a.push_back( i + 2 );
return s2437( n, a );}
bool s2309::s2427( size_t s2433 = 5 ) const{
int s2432 = s2422();
if( s2432 != -1 ) return s2432;
s2309 n( *this, false ), tw( 2 );
n.s2447( 2 );
vector<s2309> a;
for( size_t i = 0; i < s2433; ++i ) {
s2309 _t( 0 );
s2445( tw, n, _t );
a.push_back( _t );}
return s2437( *this, a );}
void s2309::s2445( const s2309& a, const s2309& b, s2309& s152 ){
std::random_device rd;
std::mt19937_64 mt(rd());
s2309 range(0);
b.s2396( a, range );
range.s2414( 1 );
if( range.s2332() ) {
std::uniform_int_distribution<int64_t> dist( 0, range.s2344 );
a.s2320( dist( mt ), s152 );
return;}
s2309 s2403(0), s2411(0);
std::uniform_real_distribution<double> dist( 0.0, 1.0 );
range.s2412( s2314, s2403 );
bool s2407 = true;
for( size_t i = 0; i < s2403._val.size(); ++i ) {
s2394 s2448 = s2407 ? s2403._val[i] : s2314;
double s2408 = dist( mt );
s2394 s2402 = (s2394) (s2408 * s2448);
s2411._val.push_back( s2402 );
if( s2402 < s2448 ) s2407 = false;}
std::reverse( begin( s2411._val ), end( s2411._val ) );
s152.s2387( s2411 );}
void s2309::_pollardRho2( const s2309& n, int64_t s2457, int64_t s2459, s2309& s152 ){
s2309 g( n ), y(2), c(1), m(100), x(0), ys(0), _t(0), k(0), q(0);
while( g.s2373( n ) ) {
s2445( s2309(0), n, y );
s2445( s2309(0), n, c );
s2445( s2309(0), n, m );
size_t r = 1;
g.s2389( 1 ); q.s2389( 1 );
while( g.s2373( 1 ) ) {
k.s2389( 0 );
size_t i, s2448;
x.s2387( y );
for( i = 0; i < r; ++i ) {
_t.s2387(y); _t.s2395(); _t.s2414( c ); _t.s2438(n, y);}
while( k.s2375( r ) && g.s2373( 1 ) ) {
ys.s2387( y );
if( m.s2375( r - k.s2344 ) ) s2448 = m.s2344;
else s2448 = r - k.s2344;
for( i = 0; i < s2448; ++i ) {
_t.s2387(y); _t.s2395(); _t.s2414( c ); _t.s2438(n, y);
x.s2396(y, _t); _t.s2441( q ); _t.s2438( n, q );}
s2309::gcd(q, n, g);
k.s2414( m );}
r *= 2;
if( r > 1000000000 ) g.s2387( n );}
if( g.s2373( n ) ) {
while( true ) {
_t.s2387(ys); _t.s2395(); _t.s2414( c ); _t.s2438(n, ys);
x.s2396( ys, _t);
s2309::gcd( _t, n, g );
if( g.compare( 1 ) == 1 ) break;}}}
s152.s2387( g );}
void s2309::s2451( const s2309& s346, int64_t s2457, int64_t c, s2309& s152 ){
wcout << L"in Rho: " << s346.to_wstring() << endl;	
std::function<void( s2309& a )> g = [c,s346]( s2309& a ) -> void 
{ s2309 _t( a ); _t.s2395(); _t.s2414( s2309( c ) ); _t.s2438( s346, a ); };
s152.s2389( 1 );
s2309 x( s2457 ), y( s2457 ), z( 1 ), s2411( 0 );
int64_t s2450 = 0;
while( true ) {
g( x ); g( y ); g( y );
x.s2396( y, s2411 );
if( s2411.s2429() ) {
s152.s2389( 0 );
return;}
s2411.s2388( false );
s2411.s2438( s346, s152 );
z.s2441( s152 );
++s2450;
if( s2450 == 100 ) { 
s2309::gcd( z, s346, s152 );
if( s152.compare( 1 ) != 0 ) break;
wcout << z._val.back() << endl;
z.s2389( 1 );
s2450 = 0;}}
if( s152.s2373( s346 ) ) s152.s2389( 0 );}
void s2309::s2452( const s2309& _n, vector<s2309>& s152 ){
s2309 n( _n );
s2394 inc[] = { 4,2,4,2,4,6,2,6 };
s2309 k( 37 ), _t( 37 * 37 );
s2394 i = 0;
while( !n.s2375( _t ) ) {
if( n.s2423( k ) ) {
s152.push_back( k );
n.s2419( k );}
else {
k.s2414( inc[i] );
i = (i + 1) % 8;
k.s2381(k, _t);}}
if( n.compare( 1 ) == 1 ) s152.push_back( n );}
void s2309::s2453( const s2309& s346, bool s2460, vector<s2309>& s152 ){
if( s346.s2427( 15 ) ) {
s152.push_back( s346 );
return;}
s2309 n( s346 );
int64_t s2457 = 2, c = 1;
bool s2449 = true;
int64_t s2458 = 100000000000;
if( s2460 ) {
for( auto p : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 } ) {
while( n.s2423( p ) ) {
s152.push_back( s2309( p ) );
n.s2419( s2309( p ) );}}}
while( !n.s2375( 2 ) ) {
if( s2449 && n.s2427( 10 ) ) {
s152.push_back( n );
break;}
if( !n.s2375( s2458 ) ) {
s2309 d( 0 );
_pollardRho2( n, s2457, c, d );
if( !d.s2429() ) {
s2309::s2453( d, false, s152 );
n.s2419( d );
s2449 = true;}
else if( c == 1 ) {
if( n.s2462() ) {
vector<s2309> s1793;
n.s2463();
s2453( n, true, s1793 );
s152.insert( end( s152 ), begin(s1793), end(s1793));
s152.insert( end( s152 ), begin(s1793), end(s1793));}
else {
c = 2;
s2449 = false;}}
else if( c < 101 ) ++c;
else if( s2457 < 101 ) ++s2457;
else { s2452( n, s152 ); break; }}
else {
s2452( n, s152 ); break;}}
std::sort( begin( s152 ), end( s152 ) );}
void s2309::s2466( std::vector<s2309>& s152 ) const{
s2453( *this, true, s152 );}
void s2309::s2412( const s2309& base, s2309& s152){
if( base.s2375( 2 ) )
throw;
s2309 s2405( *this, false );
s2309 q( 0 ), r( 0 );
while( !s2405.s2375( base ) ) {
s2405.s2367( base, q, r );
s2405.s2387( q );
s152._val.push_back( r.s2344 );}
s152._val.push_back( q.s2344 );
std::reverse( begin( s152._val ), end( s152._val ) );
s152.s2388( s2342 );}
bool s2309::operator==( const s2309& b ) const{
if( ( s2342 != b.s2342 ) || s2332() != b.s2332() )
return false;
if( s2332() ) return s2344 == b.s2344;
return s2325( s2323(), b.s2323() ) == 0;}
bool s2309::operator<( const s2309& b ) const{
if( s2342 != b.s2342 ) return s2342;
if( s2332() != b.s2332() ) return s2332();
if( s2332() ) return s2344< b.s2344;
return s2325( s2323(), b.s2323() ) == -1;}
int s2309::compare( const s2309& b ) const{
if( s2342 != b.s2342 ) return s2342 ? -1 : 1;
if( s2332() != b.s2332() ) return s2332() ? -1 : 1;
if( s2332() ) {
if( s2344== b.s2344) return 0;
return s2344< b.s2344? -1 : 1;}
return s2325( s2323(), b.s2323() );}
int s2309::compare( s2394 b ) const{
if( s2342 != (b < 0) ) return s2342 ? -1 : 1;
if( !s2332() ) return 1;
if( s2344 == b ) return 0;
return s2344 < b ? -1 : 1;}
int s2309::s2417( const s2309& b ) const{
if( b.s2332() ) return s2325( b.s2344 );
if( s2332() ) return -1;
return s2325( s2323(), b.s2323() );}
void s2309::s1944( const wstring& s ){
assert( _val.empty() );
if( s.empty() )
throw;
s2339 = NULL;
s2344 = 0;
if( s.size() < 21 ) {
wchar_t *s67;
errno = 0;
s2344 = std::wcstoll( s.c_str(), &s67, 0 );
if( *s67 != '\0' ||
( ( s2344 == LLONG_MIN || s2344 == LLONG_MAX ) && 
errno == ERANGE ) )
s2344 = 0;
else {
if( s2344 < 0 )
s2342 = true;
return;}}
int s68 = 0;
s2342 = (s[0] == L'-' ? true : false);
if( s2342 ) s68 = 1;
if( s.find_first_not_of( L"-0987654321") != string::npos )
throw;
int l = s2315, pos = (int) s.size() - l;
while( 1 ) {
if( pos < s68 ) {
l = l + pos - s68;
pos = s68;}
_val.push_back( stoi( s.substr( pos, l ) ) );
if( pos == s68 ) break;
pos -= l;}}
wstring s2309::to_wstring( uint32_t s1552 ) const{
if( _val.empty() )
return std::to_wstring( s2344 );
int l = (int) _val.size() - 1;
wstring s152 = s2342 ? L"-" : L"";
s152 += std::to_wstring( _val[l--] );
wstring zz = L"0000000";
wstring dig = L"";
while( l >= 0 ) {
dig = std::to_wstring( _val[l--] );
s152 += zz.substr( dig.size() ) + dig;}
return s152;}
void s2309::s303( std::wostream* pd, int s196 ) const{
std::wostream& buf = *pd;
if( _val.empty() )
buf << s2344;
else {
for( size_t n = 0; n < _val.size(); ++n ) {
buf << _val[n];
if( n < _val.size() - 1 ) buf << L",";}}}
#undef s691
#define s691 ((s2310*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
s480* s2310::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s299->TR().s1264( s694.s290(), s331 );
if( s.find_first_not_of( L"-0123456789" ) == std::string::npos &&
1/*s.find( L"." ) != std::string::npos*/ ) {
size_t pos = 0;
return new s2310( s299, s, pos );}
else if( s.find( L"BigLong(" ) == 0 ) {
size_t pos = 0;
return new s2310( s299, s4::s52( s.substr( 8, s.size() - 9 ), s4::s48 + L"\""
), pos );}
else if( s.find( L"BigLong" ) == 0 ) {
return s352( s585, std::vector<s270*>(), &s694 );}
return 0;}
s2310::s2310( s261* s299, const s2309& bl )
: s333( s299, NULL, NULL ), s346( bl ){
if( !Types.s2309 ) {
s490 = 0;
wh = s7::s861;}
else {
s490 = Types.s2309;
wh = s7::s860;}}
s2310::s2310( const s2310& r )
: s333( r.s299, r.ns, r.s600() ), s346( r.s346 ){
wh = r.wh;
s490 = r.s490;}
s2310::s2310( s261* s299, s1889& s, size_t& pos )
: s333( s299, NULL, NULL ), s346( s.empty() ? L"0" : s ){
if( !s.empty() )
s1664( s7::s860 );
else
s346.s2389( (int64_t)s299->TR().s1246() );
s490 = Types.s2309;}
s2310::s2310( s261* s299, int64_t n)
: s333( s299, NULL, NULL ), s346( n ){
s1664( s7::s860 );
s490 = Types.s2309;}
s480* s2310::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
size_t pos = 0;
return new s2310( s299, L"", pos );}
void s2310::s497( const s271*, bool ){
s1251();}
void s2310::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s2310::s1226, Types.s2309,
{ s1112(), s1112( { Types.String } ), s1112( { s1500::s1260 } ) }, 0, 1 ) ) );
s345.insert( make_pair( L"set", new s334( L"set", &s2310::s384, Types.s2309,
{ s1112( { Types.s2309 } ), s1112( { Types.String } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"sum", new s334( L"sum", &s2310::s385, Types.s2309,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 )));
s345.insert( make_pair( L"dif", new s334( L"dif", &s2310::s386, Types.s2309,
{ s1112( ), s1112( { Types.s2309 } ), s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 )));
s345.insert( make_pair( L"mul", new s334( L"mul", &s2310::s387, Types.s2309,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 )));
s345.insert( make_pair( L"div", new s334( L"div", &s2310::s388, Types.s2309,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537, s7::s1387 } ) }, 1, 1 )));
s345.insert( make_pair( L"pow", new s334( L"pow", &s2310::s389, Types.s2309,
{ s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"sumeq", new s334( L"sumeq", &s2310::s390, Types.Null,
{ s1112( { Types.s2309 } ), s1112( { Types.Int, s7::s1387 } ) }, 1, 10 )));
s345.insert( make_pair( L"difeq", new s334( L"difeq", &s2310::s391, Types.Null,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"muleq", new s334( L"muleq", &s2310::s392, Types.Null,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"diveq", new s334( L"diveq", &s2310::s393, Types.Null,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"eq", new s334( L"eq", &s2310::s395, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { Types.String } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"less", new s334( L"less", &s2310::s396, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"greater", new s334( L"greater", &s2310::s397, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"leq", new s334( L"leq", &s2310::s398, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"geq", new s334( L"geq", &s2310::s399, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"neq", new s334( L"neq", &s2310::s400, Types.Bool,
{ s1112( { Types.s2309 } ), s1112( { Types.String } ), s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"is-probable-prime", new s334( L"is-probable-prime", 
&s2310::s2431, Types.Bool,	{ s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"is-prime", new s334( L"is-prime", 
&s2310::s2430, Types.Bool,	{ s1112( ), s1112( { Types.Bool } ) }, 0, 1 )));
s345.insert( make_pair( L"prime-factors", new s334( L"prime-factors",
&s2310::s2467, 0,	{ s1112() }, 0, 0 )));
s345.equal_range( L"prime-factors" ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1401, s1500::s1260 );}
s1053 s2310::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"prime-factors" ) {
s806::Cont s1268;
wstring ts = this->s299->TR().s1341( 
Types( s299, Types.Vector )->s350() + L"<" + s350() + L">" );
s680 = ((s313*)Types( s299, Types.Vector ))->s1185( (s270*)this, ts, s1704, s1268 );}
else
s680 = s333::s1178( s1540, l );
return s680;}
s270* s2310::s332( s588* s2041, s271* impl ) const{
return new s2310( *this );}
void s2310::s353( s270* p ) const{
size_t s2364 = s346.s2393();
if( p->s349() == Types.Int && s2364 <= 32 )
*( (s343*)p )->s354() = (int)s346.s2370();
else if( p->s349() == Types.Double && s2364 <= 53 )
*( (s355*)p )->s354() = (double)s346.s2370();
else if( p->s349() == Types.s2309 )
( (s2310*)p )->s346.s2387( s346 );
else if( p->s349() == Types.Bool )
*( (s357*)p )->s354() = ( !s2364 || s346.s2370() );
else
throw new s16( L"No conversion to type " + s350() );}
std::wstring s2310::to_wstring( uint32_t s1552 ) const{
return s346.to_wstring();}
void s2310::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
/*	auto flags = s1918->s1914();
ss.imbue( std::locale( "C" ) );
ss.flags( flags );
ss.precision( s1918->s1915() );
*/
ss << s346.to_wstring();}
void s2310::s1944( s1889& s ){
s346.s1944( s );}
void s2310::s1943( Stream* s1918 ){
s1485& ss = s1918->s1947();
wstring s;
ss >> s;
s346.s1944( s );}
void s2310::s2341( s2310* ob, s270* p ){
if( p->s349() == Types.Long )
ob->s346.s2389( (int64_t)*((s1292*)p)->s354() );
else if( p->s349() == Types.s1516 )
ob->s346.s2389( (uint64_t)*((s1517*)p)->s354() );
else if( p->s349() == Types.Int )
ob->s346.s2389( (int64_t)*((s343*)p)->s354() );
else if( p->s349() == Types.s2309 )
ob->s346.s2387( ((s2310*)p)->s346 );
else if( p->s349() == Types.String )
ob->s346.s2468( ((s356*)p)->to_wstring() );
else
throw new s16( L"no conversion to " + ob->s350() + L" from type: " + p->s350() );}
#undef s691
#define s691 ((s2310*)(s481*)*s273)
#define INTRES ((s343*)(s481*)*s273)
#define s692 ((s357*)(s481*)*s273)
inline void s2310::s1226( s480** s273, size_t s495 ){
s2310* plv = NULL;
if( s495 == 3 && s273[2]->s349() == Types.String ) {
size_t pos = 0;
plv = new s2310( ((s2310*)s273[1] )->s299, *((s356*)s273[2])->s354(), pos );}
else {
plv = new s2310( ( (s2310*)s273[1] )->s299, 0 );
if( s495 == 3 ) {
s480* p = s273[2];
s2341(plv,  p );}
else
throw new s16( L"unknown parameters to " + plv->s350() + L"() constructor" );}
plv->s1251();
s273[0] = plv;}
inline void s2310::s384( s480** s273, size_t s495 ){
s2341( (s2310*)s273[1], s273[2] );}
void s2310::s401( s480** s273, size_t s495 ){
((s2309*)DR)->s2413( s691->s346 );}
/*void s2310::s1962( s480** s273, size_t s495 )
{
double s680 = (double)*DR;
if (isnan( s680 ) || s680 == -INFINITY || s680 == INFINITY) (void)0;
else if ( s680 == 0.0 ) s680 = DBL_EPSILON;
else {
union s1958 {
int64_t i;
double f;
}conv;
conv.f = s680;
conv.i++;
s680 = conv.f;}
s691->s346 = s680;}
void s2310::s1961( s480** s273, size_t s495 ){
double s680 = (double)*DR;
if (isnan( s680 ) || s680 == -INFINITY || s680 == INFINITY) (void)0;
else if ( s680 == 0.0 ) s680 = DBL_EPSILON;
else {
union s1958 {
int64_t i;
double f;
}conv;
conv.f = s680;
conv.i--;
s680 = conv.f;}
s691->s346 = s680;}
*/
inline void s2310::s387( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2381( ((s2310*)s273[2])->s346, s691->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2381( *lv.s354(), s691->s346 );}}
inline void s2310::s385( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2360( ((s2310*)s273[2])->s346, s691->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2360( *lv.s354(), s691->s346 );}}
inline void s2310::s388( s480** s273, size_t s495 ){
s2309 rem( 0 );
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2367( ((s2310*)s273[2])->s346, s691->s346, rem );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2367( *lv.s354(), s691->s346, rem );}}
inline void s2310::s386( s480** s273, size_t s495 ){
if( s495 == 2 ) {
s691->s346 = ((s2310*)DR)->s346;
s691->s346.s2388(((s2310*)DR)->s346.s2425());
return;}
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2396( ((s2310*)s273[2])->s346, s691->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2396( *lv.s354(), s691->s346 );}}
inline void s2310::s389( s480** s273, size_t s495 ){
( (s2310*)DR )->s346.s2383( (int)*s273[2], s691->s346 );}
inline void s2310::s390( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2414( ((s2310*)s273[2])->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2414( *lv.s354() );}}
inline void s2310::s391( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2447( ((s2310*)s273[2])->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2447( *lv.s354() );}}
inline void s2310::s392( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2441( ((s2310*)s273[2])->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2441( *lv.s354() );}}
inline void s2310::s393( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
( (s2310*)DR )->s346.s2419( ((s2310*)s273[2])->s346 );
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
( (s2310*)DR )->s346.s2419( *lv.s354() );}}
/*
inline void s2310::s394( s480** s273, size_t s495 ){
( (s2310*)DR )->s346 = ::pow( (double)*DR, (double)*PARN( 2 ) );
for( size_t n = 3; n < s495; ++n )
( (s2310*)DR )->s346 = ::pow( (double)*DR, (double)*PARN( n ) );
s691->s346 = ( (double)*DR );}
*/
inline void s2310::s395( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
*s692->s354() = ((s2310*)DR)->s346.s2373( ((s2310*)s273[2] )->s346 );
else if( s273[2]->s349() == Types.String )
*s692->s354() = DR->to_wstring() == s273[2]->to_wstring();
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
*s692->s354() = ((s2310*)DR)->s346.s2373( *lv.s354() );}}
inline void s2310::s396( s480** s273, size_t s495 ){
*s692->s354() = ((s2310*)DR)->s346.s2375( ((s2310*)s273[2] )->s346 );}
inline void s2310::s397( s480** s273, size_t s495 ){
*s692->s354() = (((s2310*)DR)->s346.compare( ((s2310*)s273[2] )->s346 ) == 1);}
inline void s2310::s398( s480** s273, size_t s495 ){
*s692->s354() = (((s2310*)DR)->s346.compare( ((s2310*)s273[2] )->s346 ) != 1);}
inline void s2310::s399( s480** s273, size_t s495 ){
*s692->s354() = (((s2310*)DR)->s346.compare( ((s2310*)s273[2] )->s346 ) != -1);}
inline void s2310::s400( s480** s273, size_t s495 ){
if( s273[2]->s349() == Types.s2309 )
*s692->s354() = !((s2310*)DR)->s346.s2373( ((s2310*)s273[2] )->s346 );
else if( s273[2]->s349() == Types.String )
*s692->s354() = DR->to_wstring() != s273[2]->to_wstring();
else {
s1292 lv( 0, 0 );
s273[2]->s353( &lv );
*s692->s354() = !((s2310*)DR)->s346.s2373( *lv.s354() );}}
void s2310::s2431( s480** s273, size_t s495 ){
*s692->s354() = ((s2310*)DR)->s346.s2427( (int)*s273[2] );}
void s2310::s2430( s480** s273, size_t s495 ){
bool s2409 = false;
if( s495 == 3 )
s2409 = (bool)*s273[2];
*s692->s354() = ((s2310*)DR)->s346.s2426( s2409 );}
void s2310::s2467( s480** s273, size_t n ){
s2310* p = (s2310*)DR;
s313* s680 = new s313( p->s299, p->s349(), p->ns, p->s600() );
vector<s482>& v = s680->s317();
vector<s2309> s2461;
p->s346.s2466( s2461 );
for( auto bl: s2461 ) v.push_back( new s2310( p->s299, bl ) );
s680->s1251();
*s273 = s680;}
/*
inline void s2310::s403( s480** s273, size_t s495 ){
s691->s346 = ::sqrt((double)*DR);}
inline void s2310::s404( s480** s273, size_t s495 ){
*( (s2310*)s273[0] )->s354() = ::pow( (double)*DR, (double)*PARN( 2 ) );}
inline void s2310::s409( s480** s273, size_t s495 ){
int s1320 = -1;
if( s495 == 3 )
s1320 = (int)*s273[2];
double dv = ( (s2310*)DR )->s346;
int s680 = (int)dv;
if( s1320 < 0 )
*( (s343*)s273[0] )->s354() = s680;
else if( s1320 == 0 ) 
*( (s343*)s273[0] )->s354() = (dv - s680 > 0.5 ? s680 + 1 : s680);
else
*( (s343*)s273[0] )->s354() = s680 + 1;}
void s2310::s303( std::wostream* pd, int s196 ) const{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << s346;}
*/
size_t s2310::s319() const{
return 0;}
inline bool s2310::operator==( const s480* p ) const{
return s346.s2373( ((s2310*)p )->s346 );}
inline bool s2310::operator<( const s480* p ) const{
return s346.s2375( ( (s2310*)p )->s346 );}
void s2310::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"BigLong : " << s346.to_wstring() << endl;;}
const wstring s468 = L"";
s479 s682;
s271::s271( s261* s299, s1053 s337, s469 pc/* = s470*/, const s262* ast_, s271* ns_, s2175 st )
: s480( s299, pc, ast_, ns_ ), s622( NULL ), s623( NULL ), 
s1648( new s368( s7::s1588, s299, s472 )), s344( s468 ), //s630( s682 ),
s626( NULL )/*, s1349( ++s1350 )*/, s2179( st )
{
s622 = this;
s490 = s337;}
s271::s271( const s271& proto, std::vector<s482>& s698, const s262* ast_, s271* ns_ )
: s480( proto.s299, /*s477*/proto.s489, ast_, ns_ ? ns_ : proto.ns ), s622( &proto ), 
s623(NULL), s1648( new s368( s7::s1588, s299, s472 )), s344( proto.s344 ),
s626( proto.s626 ), //s630( s682 ),
s628( proto.s628 ), s2179( proto.s2179 )//, s1349( ++s1350 )
{
s490 = proto.s490;
if( s489 == s475 || s489 == s2149 )
s489 = s477;
if( proto.s623 )
proto.s623->s640( this );
proto.s625.copy( s625, this, NULL, s479::s146 );
for( size_t n = 0; n < s628.size(); ++n )
s627.push_back( s625.get( s628[n].s614() ) );
if( s698.size() ) {
s835* p = (s835*)s625.get( s7::s426 );
p->s2258( s698 );}
s1648->s348( s490 );
if( s489 == s477 )
s1664( proto.s615() );}
s271::s271( s1889& s671, s261* s299, s469 pc, const s262* ast_, s271* ns_,
s2175 st )
: s480( s299, pc, ast_, ns_ ), s622( NULL ), s623( NULL ), 
s1648( new s368( s7::s1588, s299, s472 )), s344( s468 ), s277( s671 ),
s626( NULL ), s2179( st )//, s1349( ++s1350 )//, s630( *new s479() )
{
s622 = this;}
s271::s271( s262& s694, s261* s299, s469 pc, s271* ns_, s533 am,
s620& cl, s619& cnl, s621& al, s2175 st )
: s480( s299, pc, &s694, ns_ ), s622(NULL), s623( NULL ), 
s1648( new s368( s7::s1588, s299, s472 )), s344( s694.s298() ), s277( s694.s297() ),
s625( am ), s626( NULL ), s2179( st )//, s1349( ++s1350 ) //,s630( *new s479() )
{
if( s277.find( L" " ) != string::npos )
throw new s16( L"Malformed class name: " + s277 );
s622 = this;
if( pc == s475 || pc == s2149 ) {
if( cl.find( s694.s298() ) != cl.end() )
throw new s16( L"class already exists: " + s694.s298() );
size_t s2148 = cnl.size();
size_t s2176 = s694.s267( s2173 ).s56();
if( s694.s155( s7::s466 ) ) {
wstring anc = s694.s291( s7::s466 )->s290();
cnl.push_back( make_pair( s694.s298(), /*anc*/s2176 ) );
}
if( s694.s155( s7::s2144 ) ) {
wstring s2146 = s694.s291( s7::s2144 )->s290();
cnl.push_back( make_pair( s694.s298(), /*s2146*/s2176 ) );
}
if( cnl.size() == s2148 )
cnl.push_back( make_pair( s694.s298(), /*L""*/s2176 ) );
cl.insert(make_pair(s694.s298(), this));}
if( al.find( s694.s298() ) != al.end() )
throw new s16( L"module already defined: " + s694.s298() );
al.insert(make_pair(s694.s298(), &s694));
s503( L"proto" );
s262::s274& s695 = s694.s292();
s262::s274::iterator it = s695.begin();
vector<pair<wstring,wstring>> s687;
for( ; it != s695.end(); ++it ) {
if( it->second->s296() == s224 ) {
if( it->first == s7::s466 ) {
s624 = it->second->s290();}}
else if( it->second->s296() == s226 ) {
wstring s655 = it->first;
s509 pv = s512;
am = s507;
size_t s684 = s655.find_first_of( s4::s48 );
if( s684 != string::npos ) {
vector<wstring> s683;
s4::s57( it->first, wstring( 1, s655[s684] ), s683 );
if( s683.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
if( s683[0] == s7::s448 || s683.size() == 3 ) {
pc = s475;
if( s683.size() == 3 ) {
if( s683[0] == s7::s445 )
am = s506;
else if( s683[0] == s7::s447 )
am = s508;
else if( s683[0] != s7::s446 )
throw new s16( L"invalid access mode name: " + it->first );
s655 = s683[2];}
else
s655 = s683[1];
if( s695.find( s655 ) != s695.end() )
throw new s16( L"duplicated object name: " + it->first );
it->second->s293( s655 );
s687.push_back( make_pair( it->first, s655 ) );}
else if( s683[0] == L"access" && ( s683[1] == L"allow" || s683[1] == L"deny" )) {
if( s683[1] == L"allow" )
pv = s511;
pc = s476;}
else
throw new s16( L"unknown object type: " + s683[0] );}
if( pc == s476 ) {
s625.s546( pv, it->second );}
else {
s271* ob = new s271( *it->second, s299, s475, this, am, cl, cnl, al, s2182 );
s625.s538( ob->s298(), ob );}}}
for( size_t n = 0; n < s687.size(); ++n ) {
auto it = s695.find( s687[n].first );
s695.insert(make_pair(s687[n].second, it->second ));
s695.erase( it );}}
s271::~s271(){
s625.reset();
s627.clear();
s628.clear();}
s480* s271::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return s632( s694, s585, s331 );}
void s271::s641( const s479& s273 ){}
wstring s271::s827() const {
if( s489 == s477 )
return s344;
return /*ns->s297()*/ s277; 
}
bool
s271::s498( const s480* s499 ) const{
if( s499->s349() == s349() )
return true;
if( s623 )
return s623->s498( s499 );
return false;}
bool
s271::s723( s1889& f ) const{
return s625.s155( f );}
void s271::s153( s262& s694 ){
TDException s960( s7::s2143, s925, &s694 );
s262::s274& s695 = s694.s292();
s262::s274::iterator it = s695.begin();
for( ; it != s695.end(); ++it ) {
s262* node = it->second;
if( node->s296() == s224 ) {
wstring s76 = node->s298();
if( s76 == s7::s440 )
s642( *node );
else if( s76 == s7::s466 )
s635( *node );
else if( s76 == s7::s929 )
s962( *node );
else {
size_t s684 = s76.find_first_of( s4::s48 );
bool s1193 = false;
if( s684 != string::npos ) {
vector<wstring> s683;
s4::s57( s76, wstring( 1, s76[s684] ), s683 );
if( s683.size() > 2 )
throw s960.s992( L"malformed object declaration: " + s76 );
if( s683[0] == s7::s1130 ) {
s1193 = true;
s76 = s683[1];}
node->s293( s76 );}
try { lang::s653( s76 ); }
catch( s16* e ) {
throw s960.s992( e->Msg() );}
s480* dv = NULL;
try {
dv = s299->TR().s515( *node, this, s277 );
dv->s2180( s2185 );}
catch( TDException* e ) {
if( e->Category() == s923 ) {
wstring sym = e->s2152( 0 );
wstring s616 = node->s290();
s616 = s616.substr( 0, s616.find( L"(" ) );
s1053 pt = s299->TR().s1002( s616 );
const s480* proto = s299->TR().s999( pt );
if( proto->s491() == s475 && ((s271*)proto)->s2162( s277 ) )
e->s30( L"recursive import between '" + s616 + L"' and '" + s277 + 
L"'.\n   Recursive import in classes is not allowed." );}
e->s30( L"while constructing object member: " + s76 );
throw e;}
catch( s16* e ) {
e->s30( L"while constructing object member: " + s76 );
throw e;}
dv->s503( node->s298() );
try {
s625.s538( node->s298(), dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s277 + L"::" + node->s298() );}
throw e;}
s627.push_back( dv );
s628.push_back( s368( node->s298(), s299, s472, s1193 ) );}}
else if( node->s296() == s226 ) {
if( 0 && it->first.find( L"access" ) != 0 ) {
s271* ob = (s271*)s625.get( it->first );
ob->s153( *it->second );}}
else if( node->s296() == s227 ) {
if( node->s298() == s7::s2144 ) {
s1053 s2147 = s299->TR().s1002( node->s290() );
s625.s538( node->s298(), new s1517( s299, s2147 ) );
continue;}
s480* dv = new s356( s299, node->s290(), this, node );
dv->s503( node->s298() );
dv->s1249( true );
wstring s1659 = node->s298();
if( node->s298() == s7::s462 )
s1659 = L"name";
try {
s625.s538( s1659, dv );}
catch( s16* e ) {
if( e->which() == (uint32_t)s16::s17::s21 ) {
e->s30( L"Symbol is already defined: " + s277 + L"::" + node->s298() );}
throw e;}
s627.push_back( dv );
s628.push_back( s368( s1659, s299 ) );}}
it = s695.begin();
for( ; it != s695.end(); ++it ) {
s262* node = it->second;
if( node->s296() == s225 ) {
try {
s485 func = s588::s596( *node, s299, this,
node->s298(), s277 );
s625.s538( func->s298(), func.s15<s480*>() );
s627.push_back( func );
s628.push_back( s368( func->s298(), s299 ) );}
catch( TDException* e ) {
e->s1068( TDException::Stage::s1017 );
e->s30( L"while compiling function '" +s277 + L"::" + node->s298() + L"'" );
s1006.s963( e->Msg( 0 ) );}}}
if( s489 == s475 ) {
s1346* s1353 = new s1346( s299, this, NULL, NULL );
s625.s538( s7::s1345, s1353 );
s627.push_back( s1353 );
s628.push_back( s368( s7::s1345, s299 ) );
if( s625.s155( s7::s425 ) ) {
s835* s2168 = (s835*)s625.get( s7::s425 );
vector<s270*> s1824 = { this };
s588::s828 s874;
s2168->s807( s874 );
for( size_t n = 0; n < s874.size(); ++n )
s1824.push_back( s874[n].second );
s835* td = new s835( *s2168, (s588*)this, s1824, s588::s565,
&s694, this, this, false );
s625.s538( s7::s426, td );}
if( s625.s155( s7::s2144 ) ) {
s1053 s2252 = (s1053)(int)*s625.get( s7::s2144 );
s271* s2251 = (s271*)s299->TR().s999( s2252 );
if( !s625.implements( s2251->s625 ) )
throw new s16( L"the '" + s277 + L"' class doesn't implement '" + 
s2251->s350() + L"' interface" );
s299->TR().s1521( s349(), s2252 );}}
else if( s489 == s476 ) {
if( 0 && s625.s155( s7::s425 ) ) {
s835* s2168 = (s835*)s625.get( s7::s425 );
vector<s482> s1824 = { this };
s588::s828 s874;
s2168->s807( s874 );
for( size_t n = 0; n < s874.size(); ++n )
s1824.push_back( s874[n].second );
s2168->s593( s1824 );}}}
void s271::s497( const s271* s872, bool ){
assert( s489 != s2149 );
if( s489 == s475 || s489 == s476 ) {
if( s624.size() ) {
s623 = (s271*)s299->s221( s624, s872->s827() );
s623->s626->copy( *s626 );}
if( s626 )
s626->s497( s299, s277 );
else
s626 = s622->s626;
s625.s497( this, NULL, false );}
else {
if( 1 || s299->s1319()) {
try {
if( ( s299->s1319() || s2179 == s2185 ) && s625.s155( s7::s426 ) ) {
vector<s481*> s273;
s273.push_back( this );
s835* p = (s835*)s625.get( s7::s426 );
if( p->s615() == s7::s861 ) {
p->s2117( (s588*)s872, this );
p->s497( s872, false );}
else
p->s594( s872 );
if( s491() == s477 ) {
p->s2245();
s1648->s379( this );
p->s2171( s1648 );
p->s494( (s480**)&s273[0], 1 );}}
s625.s497( (s271*)s872, this, s299->s1319() );}
catch( s16* e ) {
throw new TDException( TDException::Stage::s1018, s7::s2274, s1543, s600(), *e );}}
s626 = s622->s626;
s1648->s348( s490 );}
ns = (s271*)s872;}
void s271::s2117( s588* s2041, s271* impl, bool s2158 ){
return s480::s2117( s2041, impl, s2158 );
for( auto it = s625.Table().begin(); it != s625.Table().end(); ++it ) {
s270* p = it->second.s15<s270*>();
p->s2117( s2041, this, s2158 );}}
void s271::s1636(){
if( s491() != s476 || s615() == s7::s860 )
return;
if( s625.s155( s7::s425 ) ) {
s835* p = (s835*) s625.get( s7::s425 );
p->s497( (s271*)ns, true );
p->s494( 0,0 );}
s1251();
if( s626 ) 
s626->s1636( s299 );}
void s271::s640( s271* s643 ) const{
if( s623 )
s623->s640( s643 );}
void s271::s642( s262& s694 ){
if( !s626 )
s626 = new s548();
s626->s551( s694.s290() );
return;}
void s271::s636( s1889& s331,	vector<wstring>& s152 ){
s625.s530( s331, s152 );}
void s271::s552( s1889& s76, s1889& s555 ){
if( !s626 )
s626 = new s548();
s626->s552( s76, s299, s555 );}
bool s271::s2162( s1889& s76 ){
if( s626 )
return s626->s2162( s76 );
return false;}
void s271::s635( s262& s694 ){
s623 = (s271*)s299->s221( s624, s277 );}
void s271::s962( s262& s694 ){
wstring s987 = L"wrong syntax of class attributes: " + s694.s290();
s483 dv = s299->TR().s515( s694, this, s277 );
if( dv->s349() != s1704 )
throw new s16( s987 );
vector<s482>& v = dv.s15<s313*>()->s317();
for( auto s_ : v ) {
wstring s = s_.s15<s356*>()->to_wstring();
size_t pl = s.find( L":" );
if( pl == string::npos )
throw new s16( s987 );
wstring cat = s4::s52( s.substr( 0, pl ), s4::s48 );
vector<wstring> s152;
s4::s57( s.substr( pl + 1 ), L",", s152 );}}
bool s271::s553( s1889& sym_, s368* ref, s1889& s331,
bool fr ) const{
size_t pl0 = sym_.find( L"::" );
wstring sym;
if( pl0 != string::npos ) {
wstring smod = sym_.substr( 0, pl0 );
if( smod == s277 )
sym = sym_.substr( pl0 + 2 );
else
sym = sym_;}
else
sym = sym_;
bool s680 = false;
size_t pl = sym.find( L"." );
if( pl != string::npos ) {
sym = sym_.substr( pl + 1 );
wstring s681 = sym_.substr( 0, pl );
s271* ob = ((s271*)s638( s681, s331, false ));
if( !ob && s681 == s7::s1588 )
ob = (s271*)this;
if( ob ) {
s368 s1643( *ref );
s680 = ob->s553( sym, &s1643, s331, fr );
if( s680 ) {
if( !ref->s377() )
ref->s379( ( s480* )this );
ref->s376( s637( s681 ), ob );
ob->s553( sym, ref, s331, fr );}}
else {
if( s626 )
s680 = s626->s553( sym_, ref );}}
else {
const s271* ob = ((s271*)s638( sym, s331, false ));
if( ob ) {
if( !ref->s377() )
ref->s379( ( s480* )this );
size_t off = s637( sym );
ref->s376( off, ob );
if( s628[off].s1193() )
ref->s1249();
s680 = true;}
else {
if( sym == s7::s1588 ) {
ob = this;
if( !ref->s377() )
ref->s379( ( s480* )this );
ref->s376( s1137, ob );
s680 = true;}
else if( s626 )
s680 = s626->s553( sym, ref );}}
return s680;}
size_t s271::s637( s1889& s644 ) const{
if( s644 == s7::s1588 )
return s1137;
/*???DEBUG??? 220119	size_t pl = s644.find( L"::" );
if( pl != string::npos ) {
wstring smod = s644.substr( 0, pl );
wstring sym1 = s644.substr( pl + 2 );
s271* mod = (s271*)s625.get( smod, false );
if( !mod )
return NULL;
return mod->s637( sym1 );}
*/
for( size_t n = 0; n < s627.size(); ++n ) {
if( s628[n].s614() == s644 )
return n;}
throw new s16( L"3: Symbol does not exist: " + s644 );}
s270* s271::s595( size_t off ){
if( off == s1137 )
return this;
return s627[off];}
void s271::s844( s1889& s76, s480* s346, s479::s144 ap ){
s625.s538( s76, s346, ap );
s627.push_back( s346 );
s628.push_back( s368( s76, s299 ) );}
void s271::s1642( s1889& s76, s480* s346 ){
if( !s625.s155( s76 ) )
throw new s16( L"no such member: " + s76 );
s625.s538( s76, s346, s479::s146 );
for( size_t n = 0; n < s628.size(); ++n ) {
if( s628[n].s614() == s76 ) {
s627[n] = s346;
break;}}}
void s271::s1627( const s1589* ob ){
s627.clear();
s622->s625.s1600( s625 );
for( size_t n = 0; n < s628.size(); ++n )
s627.push_back( s625.get( s628[n].s614() ) );
s479::s532 sm;
ob->s1619( sm );
s479::s532::const_iterator it = sm.begin();
for( ; it != sm.end(); ++it ) {
if( it->first == L"class" || it->first == L"name" )
s625.s538( it->first, it->second.s15<s480*>(), s479::s146 );
else {
if( !s625.s155( it->first ) )
throw new s16( L"the field " + it->first + L" doesn't exist" );
s480* mem = s625.get( it->first );
mem = mem->s1524( it->second.s15<s480*>() );
s625.s538( it->first, mem, s479::s146 );}}
for( size_t n = 0; n < s628.size(); ++n ) {
s627[n] = s625.get( s628[n].s614() );}
/*	auto s817 = s625.Table();
auto it1 = s817.begin();
for( ; it1 != s817.end(); ++it1 )
it1->second->s2117( this );*/
}
s480* s271::s1524( const s480* p ) const{
if( p->s1529( s349() ) ) {
s271* s680 = (s271*)p->s332( NULL, ns );
if( s680->s615() == s7::s861 )
s680->s497( ns, true );
return s680;}
vector<s482> s273;
s273.push_back( (s270*)p );
s271* s680 = new s271( *(s271*)this, s273, s600(), (s271*)this );
s680->s497( this, false );
return s680;}
s480* s271::s638( s1889& sym, s1889& s331,	bool s517/*= true*/ ) const
{
size_t pl = sym.find( L"::" );
if( pl != string::npos ) {
wstring smod = sym.substr( 0, pl );
wstring sym1 = sym.substr( pl + 2 );
s271* mod = (s271*) s625.get( smod, s517 );
if( !mod )
return NULL;
return mod->s638( sym1, s331, s517 );
/* ???DEBUG??? 220119		s480* s152 = mod->s638( sym1, s331, s517 );
if( s152 ) {
if( sym1.find( L"." ) != string::npos )
return s152;
else
return mod;}
return NULL;*/
}
wstring sym1 = sym;
if( sym.size() > 2 && ( sym.find( L"()" ) == sym.size() - 2 ) )
sym1 = sym.substr( 0, sym.size() - 2 );
s483 s680 = s625.get( sym1, false );
if( !s680 && s517 )
throw new s16( L"4: Symbol does not exist: " + sym, 
(uint32_t)s16::s17::s23 );
if( s680 && !s639( sym1, s331 ) && (s331 != L":::") ) {
if( s517 )
throw new s16( L"4: Symbol not found: " + sym,
(uint32_t)s16::s17::s23 );
s680 = NULL;}
return s680;}
bool s271::s639( const wstring& sym, s1889& s496 ) const{
if( s496 == s344 )
return true;
return s625.s547( sym, s496 );}
s1053 s271::s383( s1889& s340 ) const{
s480* s685 = s625.get( s340 );
s1053 s680 = s685->s349();
if( s680 == 0 ) {
s685->s497( (s271*)this );
s680 = s685->s349();}
return s680;}
s480* s271::s632( const s262& s694, s480* s585, s1889& s331 ) const{
vector<wstring> s686;
vector<s482> s273;
vector<s270*> s698;
s270::s1322( s694, s299, (s271*)s585, s331, s698 );
for( auto pr : s698 )s273.push_back( pr );
s271* s680 = new s271( *this, s273, &s694, (s271*)s585 );
return s680;}
s480* s271::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
vector<wstring> s686;
vector<s482> s273;
if( s299->s1319() )
for( auto p : l ) s273.push_back( p ); 
s271* s680 = new s271( *this, s273, s600(), s585 );
return s680;}
std::wstring s271::s297() const{
if( s491() == s476 )
return s277;
else if( s491() == s475 || s491() == s477 )
return s344;
assert( 0 );
return s277;}
s480* s271::s341( s1889& s671, s1889& s331,
bool s517 /*= true*/, bool s2150 /*= true*/ ) const
{
s368 ref( s671, s299 );
if( !s553( s671, &ref, s331, true ) )
return NULL;
if( !s2150 && ref.s378().s15<s271*>() != this )
return NULL;
s480* s680 = ref.s375();
if( s680->s491() != s473 )
return NULL;
return s680;}
s588* s271::s1670( s1889& s671, s588* s214, s271* s1657,
s558* cs ) const{
if( s671 == L"getf" ) {
return new s1665( s299, (s271*)this, s214, &s271::s1689, cs, 
NULL );}
return s480::s1670( s671, s214, s1657, cs );}
s480* s271::s1689( s480** s273, size_t s495 ){
s356* pv = (s356*) s273[1];
return s625.get( pv->to_wstring() );}
s270* s271::s332( s588* s2041, s271* impl ) const{
vector<s482> v;
return new s271( *this, v, NULL, ns );}
void s271::s353( s270* p ) const{
s271* pob = (s271*)p;
s625.s1600( pob->s625 );
for( size_t n = 0; n < pob->s628.size(); ++n ) {
pob->s627[n] = pob->s625.get( pob->s628[n].s614() );}
return;
throw new s16( L"" );
vector<wstring> fields;
s625.s542( fields );
for( size_t n = 0; n < fields.size(); n++ )
((s480*)s625.get( fields[n] ))->s353( p );}
size_t s271::s319() const{
return s625.s319();}
bool s271::operator==( const s480* p ) const{
return s625.compare( ( (s271*)p )->s625.Table() );}
bool s271::operator<( const s480* p ) const{
return false;}
void s271::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
if( s625.s155( s7::s1616 ) ) {
s588* s1640 = (s588*)s625.get( s7::s1616 );
s9<s504> s1638 = new s504( (s261*)s299, (s271*)this, s600() );
vector<s482> s698 = { /*(s270*)this,*/ s1638 };
s1640->s593( s698 );
s1640->s2117(NULL, (s271*)this);
if( s1640->s615() != s7::s860 )
s1640->s497( this, true );
else
s1640->s594( this );
s1640->s494( 0, 0 );
ss << s1638->to_wstring();
return;}
std::wstringstream buf;
wstring s344;
if( s489 == s475 ) s344 = L"Class";
else if( s489 == s476 ) s344 = L"Module";
else if( s489 == s477 ) s344 = L"Object";
else s344 = L"ERROR";
buf << s344 << L" : " << s277 << L"/" /*<< s369*/ << endl;
s625.s303( &buf, s416 );
buf << endl;
ss << buf.str();}
wstring s271::to_wstring( uint32_t s1552 ) const{
if( s625.s155( s7::s1616 ) ) {
s588* s1640 = (s588*)s625.get( s7::s1616 );
s9<s504> s1638 = new s504( (s261*)s299, (s271*)this, s600() );
vector<s482> s698 = { /*(s270*)this,*/ s1638 };
s1640->s593( s698 );
if( s1640->s615() != s7::s860 )
s1640->s497( this, false );
else
s1640->s594( this );
s1640->s494( 0, 0 );
return s1638->to_wstring();}
std::wstringstream buf;
wstring s344;
if( s489 == s475 ) s344 = L"Class";
else if( s489 == s476 ) s344 = L"Module";
else if( s489 == s477 ) s344 = L"Object";
else s344 = L"ERROR";
buf << s344 << L" : " << s277 << L"/" /*<< s369*/ << endl;
s625.s303( &buf, s416 );
buf << endl;
return buf.str();}
void s271::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
wstring s344;
if( s489 == s475 ) s344 = L"Class";
else if( s489 == s476 ) s344 = L"Module";
else if( s489 == s477 ) s344 = L"Object";
else s344 = L"ERROR";
buf << s4::fill_n_ch( L' ', s196 ) << s344 << L" : " << s277 << L"/" << 
L": " << s4::s2169( (void*)this ).c_str() << endl;
s625.s303( pd, s196 + s416 );}
s574 s2099;
s588* s588::s596( const s262& s694, s261* s299, s271* obj,
const wstring& s277, const wstring& s555 ){
const s262::s274& s695 = s694.s292();
size_t s690 = s695.size();
std::vector<s270*> s273;
bool s2131 = false;
bool formals = true;
vector<std::pair<wstring, wstring>> s2268;
for( size_t n = 0; n < s690; ++n ) {
s262::s274::const_iterator it = s695.find( std::to_wstring( n ) );
if( it->second->s290() == s7::s933 )
s273.push_back( s866 );
else if( it->second->s290() == s7::s1130 )
s273.push_back( s1671 );
else if( it->second->s290() == s7::s2123 ) {
s273.push_back( s2130 );
s2131 = true;
formals = false;}
else {
if( formals && (( s273.empty() && it->second->s296() != s227 ) ||
( s273.size() && s273.back()->s491() != s472 && it->second->s296() != s227 )))
formals = false;
if( s2131 && s273.back()->s491() != s472 && it->second->s296() != s227 ) 
s2131 = false;
for( auto mn : s2268 )
it->second.s15<s262*>()->s2267( mn );
if( s2131 )
it->second.s15<s262*>()->s268( s2278, s140( L"locals" ) );
s270* ex = s270::s501( *it->second, s299, obj, s555, !s2131 ); // ???DEBUG??? 220701
s273.push_back( ex );
if( (s2131 || formals) && ex->s491() == s472 && ( (s368*)ex )->s614()[0] != L'_' ) {
wstring s2270 = ( (s368*)ex )->s614();
lang::s653( s2270 );
( (s368*)ex )->s2269();
s2268.push_back( make_pair( s2270, ( (s368*)ex )->s614() ) );}}}
Transd* s680 = NULL;
size_t s684 = s277.find_first_of( s4::s48 );
if( s684 != string::npos ) {
vector<wstring> s683;
s4::s57( s277, wstring( 1, s277[s684] ), s683 );
if( s683.size() > 2 )
throw new s16( L"malformed function name: " + s277 );
if( s683[0] == s7::s428 ) {
s680 = new s601( s299, obj, NULL, s565, s273, &s694 );
s680->s277 = s683[1];}
else if( s683[0] == s7::s429 ) {
s680 = new s835( s299, obj, NULL, obj, s565, s273, &s694 );
s271* pAnc = (s271*)s299->s221( obj->s634(), s555 );
((s601*)pAnc->s341( s683[1], s555 ))->s645( obj->s349(),
s680 );
s680->s277 = s683[1];
s680->s591( s571 );}
else
throw new s16( L"malformed function name: " + s277 );}
else {
s680 = new s835( s299, obj, NULL, obj, s565, s273, &s694, true );
s680->s277 = s277;}
return s680;}
s558* s588::s1109( const s262& s694, s261* s299, s271* obj,
s1889& s555, bool s2159 ){
const s262::s274& s695 = s694.s292();
size_t s690 = s695.size();
wstring s598 = s694.s290();
std::vector<s270*> s273;
s558* s680 = NULL;
try {
for( size_t n = 0; n < s690; ++n ) {
s262::s274::const_iterator it = s695.find( std::to_wstring( n ) );
it->second.s15<s262*>()->s268( s2085, s140(L"CallSite") );
it->second.s15<s262*>()->s268( s2084, s140(s598) );
if( it->second->s290() == s7::s933 )
s273.push_back( s866 );
else if( it->second->s290() == s7::s1130 )
s273.push_back( s1671 );
else if( it->second->s290() == s7::s2123 )
s273.push_back( s2130 );
else
s273.push_back( s270::s501( *it->second, s299, obj, s555, false ) );}
s680 = new s558( s299, s598, s273, &s694, s2159 );}
catch( s16* e ) {
throw e->s30( L"\nwhile processing '" + s598 + L"' function call" );}
return s680;}
void s558::s497( const s271* s872, bool ){
return;
for( size_t n = 0; n < s273.size(); ++n ) {
s273[n]->s497( s872 );}}
s270* s558::s332( s588* s2041, s271* impl ) const{
return new s558( *this );}
s588* s588::s597( s558* cs, s261* s299, s271* s585, s588* s214, 
s1889& s555, bool proc ){
wstring s598 = cs->s298();
wstring s697 = s585 ? s585->s2153() : L"::";
s482 s696 = NULL;
std::vector<s270*>& s273 = cs->s599();
s485 s699 = NULL;
s588* s680 = NULL;
size_t pl = s598.find( L"<" );
try {
if( pl == string::npos ) {
auto s1439 = s1359.find( s598 );
if( s1439 != end( s1359 ) && BIFuncs1v[s1439->second] )
return s299->s213( s1439->second, cs, s585, s214 );
s270* par = NULL;
int s1352 = 0;
s1348:
if( s273.size() ) {
par = s273[s1352];
s469 pc = par->s491();
if( pc == s472 ) {
try {
par->s497( s214, proc ); }
catch( TDException* e ) {
if( e->Category() != s923 || (
( (s368*)par )->s614()[0] != L':' && ( (s368*)par )->s614().back() != L':' ) )
throw e->s30( L"while compiling function '" + s598 + L"'" );
s1352++;
goto s1348;}
if( ( (s368*)par )->s378().s14() ) {
if( ( (s368*)par )->s614() == s7::s427 )
par = s585;
s696 = ( (s368*)par )->s374();}}
else {
if( pc == s474 ) {
s487 cs = new s558( *(s558*)par );
par = s597( cs, s299, s585, s214, s555, false ); // ???DEBUG??? 220214
( (s588*)par )->s497( s585, false );}
else {
par->s497( s214 );}}
if( par->s491() == s472 /*||  par->s491() == s1326*/ ) {
(void)0;}
else if( par->s491() == s1055 || par->s491() == s478 )
s696 = NULL;
else {
s696 = par->s493();}
s273[s1352] = par;}
else {
s699 = (s588*)s585->s341( s598, s697, false );
if( !s699 )
throw new s16( L"Procedure is not resolved: " + s598 );}
if( s1439 != end( s1359 ) )
return s299->s213( s1439->second, cs, s585, s214 );}
else {
wstring s2122 = s598.substr( pl + 1, s598.size() - pl - 2 );
wstring s616 = s299->TR().s1264( s2122, s555 );
s598 = s598.substr( 0, pl );
if( s616 != s2122 ) {
s2122 = s299->TR().s1341( s299->TR().s1264( s2122, s555 ) );
((s262*)cs->s600())->s1753( s598 + L"<" + s2122 + L">" );}
try {
s1053 pt = s299->TR().s1002( s616, false );
if( !pt ) {
s939 ast2 = new s262( s616 + L"()", cs->s600()->Nqj(), (s262*)s214->s600() );
s696 = s299->TR().s515( *ast2, s585, s555 );}
else {
s696 = s299->TR().s999( pt )->s352( s214, s273, s214->s600() );
s696->s2180( s2184 );}}
catch( s16* e ) {
if( 1 || e->which() != (uint32_t)s16::s17::s23 )
throw e->s30( L"\nwhile compiling '" + s598 + L"' function " );
s939 ast2 = new s262( s616 + L"()", cs->s600()->Nqj(), (s262*)s214->s600() );
s696 = s299->TR().s515( *ast2, s585, s555 );}
s273.insert( s273.begin(), s696 );
if( s696->s491() == s1234) {
s588* ptd = s696.s15<s271*>()->s1670( s598, s214, s585, cs );
if( ptd )
return ptd;}}
s485 s700 = NULL;
s1132 s1227;
if( !s699 ) {
s469 s703 = s696->s491();
if( s703 == s472 ) {
s368* ref = (s368*)s696.s15<s481*>();
s696 = (s480*)ref->s500();
s703 = s696->s491();}
try {
assert( s703 != s476 && s703 != s2149 );
if( s703 == s477 || s703 == s475 ) {
s700 = (s588*)s696.s15<s271*>()->s341( s598, s697, false, false );}
else if( s703 == s471 )
s1227 = s696.s15<s333*>()->s1187( s598 );}
catch( s16* e ) {
if( e->which() != (uint32_t)s16::s17::s23 )
throw;}
if( !s700 && !s1227.s336 )
s699 = (s588*)s585->s341( s598, s697, false );
if( !( s1227.s336 || s699 || s700 ) ) {
s588* ptd = s696.s15<s271*>()->s1670( s598, s214, s585, cs );
if( ptd )
return ptd;
throw new s16( L"Method is not resolved: " + s598 );}}
if( s1227.s336 ) {
s680 = new s834( s299, s214, s585, s563, s273, s1227.s335, s598, cs->s600(), proc );}
else if( s699 ) {
if( s598 == s7::s1345 ) {
assert( 0 );
vector<s270*> s1649( s273.begin() + 1, s273.end() );
s680 = new s1346( *s699.s15<s1346*>(), s585, s214, s1649,
cs->s600() );}
else {
s680 = new s835( *s699.s15<s835*>(), s214, s273,
s564, cs->s600(), s699->s585, s214->s585, false, proc ); //???DEBUG??? 220828
}}
else if( s700 ) {
if( s598 == s7::s1345 ) {
s680 = new s1346( *s700.s15<s1346*>(), s696.s15<s271*>(), s214, s273,
cs->s600() );}
else {
s680 = new s835( *s700.s15<s835*>(), s214, s273, s565,
cs->s600(), s696.s15<s271*>(), s214, true, proc );}
if( s700->s592() == s570 )
s680->s572 = s566;
else
s680->s572 = s565;}}
catch( s16* e ) {
throw e->s30( L"while compiling function '" + cs->s600()->Src() + L"'" );}
s680->s277 = s598;
return s680;}
void s588::s1231( vector<s270*>& s273, const vector<wstring>& s1198 ){
for( s270* p : s273 ) {
if( p->s491() == s472 || p->s491() == s1055 )
( (s368*)p )->s974( s1198 );}}
void s588::s1231( vector<s482>& s273, const vector<wstring>& s1198 ){
for( s270* p : s273 ) {
if( p->s491() == s472 )
( (s368*)p )->s974( s1198 );}}
s588::s588( s261* s299, s271* s589, s588* s590, s271* ns_, s560 ct,
s1889& s671, const s262* s694, bool s1712, bool _bd )
: s271( s671, s299, s473, s694, ns_ ), s572( ct ),
s583( NULL ), s585( s589 ), s584( s590 ), past( s694 ), s1639( new s1587( s299 ) ),
intro( s1712 ), s2158( _bd ), s2219( -1 ){}
s588::s588( s261* s299, s271* s589, s588* s590, s271* ns_,
s560 ct, const std::vector<s270*>& l,	const s262* s694, bool s1712=false,
bool _bd=true)
: s271( s299, 0, s473, s694, ns_ ), s572( ct ), s573( s569 ),
s583( NULL ),	s585( s589 ), s584( s590 ), past( s694 ), s1639( new s1587( s299 ) ),
intro(s1712), s2158(_bd), s2219( -1 ){
TDException s960( s7::s1672, s925, s694, L"malformed lambda definition" );
size_t n = 0;
bool s2136 = false;
bool s2131 = false;
bool s1158;
for( ; n < l.size(); n += 2 ) {
s1158 = false;
if( ((s480*)l[n]) == s866 ) {
if( l.size() == n || s2131 )
throw s960.s992( L"the return type is missing" );
s490 = l[n + 1]->s349();
s2136 = true;
continue;}
if( ((s480*)l[n]) == s2130 ) {
s2131 = true;
n -= 1;
continue;}
else if( ((s480*)l[n]) == s1671 ) {
if( l.size() == n )
throw s960.s992( L"the 'const' keyword should precede the parameter name");
s1158 = true;
++n;}
if( l[n]->s491() != s472 ) {
if( s1158 )
throw s960.s992( L"the 'const' keyword should precede the parameter name");
break;}
s368* s76 = (s368*) l[n];
if( l.size() == n + 1 ) {
throw new s16( L"incorrect syntax for lambda parameter " + s76->s614() +
L": missing type specifier.", (uint32_t)s16::s17::s20 );}
s480* ex = (s480*) l[n + 1];
s469 s1883 = ex->s491();
if( //s1883 != s471 && s1883 != s477 &&	s1883 != s476 && 
s1883 == s472 ||
(s1883 == s473 && !s2131 ) )
throw new s16( L"incorrect syntax for lambda parameter " + s76->s614() +
L": should be a type constructor.", (uint32_t)s16::s17::s20 );
if( s1158 )
s76->s1249();
s625.s538( s76->s614(), ex );
if( !s2131 )
s579.push_back( (s480*)ex );
s273.push_back( (s480*)ex );
s627.push_back( (s480*)ex );
s628.push_back( *s76 );}
s581.insert( s581.end(), l.begin() + n, l.end() );
if( s600() )
((s262*)s600())->s268( s2086, s140( (double)s490, s139 ) );}
s588::s588( const s588& right, s271* s589, s588* s590,
s271* ns_, const std::vector<s270*>& s698, const s262* s694, bool s2104,
bool _bd)
: s271( right, s2099, s694, ns_ ), 
s573( right.s573 ),	s583( NULL ), s585( s589 ), s584( s590 ), 
past( s694 ), s1639( new s1587( s299 ) ), intro( s2104 ), s2158( _bd ), s2219( right.s2219 ){
s572 = right.s572;
s579 = right.s579;
s277 = right.s277;
if( s698.size() ) {
s273.assign( s698.begin(), s698.end() );}
else {
s273.clear();
for( size_t n = 0; n < right.s273.size(); ++n ) {
s273.push_back( right.s273[n]->s332( this, s589 ) );}}
if( s572 == s564 ) { 
for( size_t n = 0; n < s273.size(); ++n ) {
s482 tmp = s627[n];
s625.s538( right.s628[n].s614(), tmp.s15<s481*>(), s479::s146 );
s627[n] = s273[n];}}
for( size_t n = 0; n < right.s581.size(); ++n )
s581.push_back( right.s581[n]->s332( this, NULL ) );
nlocs = right.nlocs;
s495 = right.s495;
s578 = nlocs ? (s481**)&s273[0] : NULL;
s580 = right.s580;
s577 = s495 ? (s480**)&s580[0] : NULL;
s973 = right.s973;}
s834::s834( s261* s299, s588* s590, s271* ns_, s560 ct, const vector<s270*>& l,
s1053 s702, s1889& s1540, const s262* s694, bool _bd )
: s588( s299, s590, s590, ns_, ct, L"", s694, false, _bd ), s1960( false )/*, s559( s701 )*/
{
s277 = s1540;
if( s277 == s7::s1345 )
l[0]->s2117( this, this );
s573 = s569;
s490 = s702;
s273.assign( l.begin(), l.end() );}
s834::s834( const s834& right, s588* s590, s271* ns_ )
: s588( right, NULL, s590, ns_, vector<s481*>(), right.s600(),
false, right.s2158 ), 
s559( right.s559 ), s1960( right.s1960 ){
s277 = right.s277;
s573 = s569;
s490 = right.s490;
s583 = (s480*)right.s583->s332(0,0);
s580.resize( right.s580.size() );
s580[0] = s583;}
s834::~s834(){}
s835::s835( s261* s299, s271* s589, s588* s590, s271* ns_, s560 ct,
const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, ns_, ct, l, s694, false, s2159 ){
if( ct == s565 ) {
subject = s589;		}}
s835::s835( const s835& right, s588* s590,
const std::vector<s270*>& s698, s560 ct,  const s262* s694, 
s271* s589, s271* ns_, bool s2104, bool s2159 )
: s588( right, s589, 
s590, ns_, vector<s481*>(), s694, s2104, s2159 ){
TDException s960( s7::s1655, s925, s694 );
s572 = ct;
int shift = 0;
if( ct == s565 || ct == s564 ) { // ???DEBUG??? 220728 
if( ct == s565 && s698.size() ) {
subject = s698[0];
shift = 1;}
else
subject = s585.s15<s481*>();}
for( size_t n = 0; n < s579.size(); ++n ) {
if( s698.size() > n + shift ) {
s469 pc = s698[n]->s491();
if( ( pc == s472 || pc == s1326 ) && s698[n]->s1193() && !s628[n].s1193() )
throw s960.s992( L"constant argument is passed to non-constant function: " + s628[n].s614() );
s273[n] = s698[n + shift];}}
if( s273.size() ) {
for( size_t n = 0; n < s273.size(); ++n ) { // ???DEBUG??? 220802
s627[n] = s273[n]; // ???DEBUG??? 220802
}}
if( s698.size() - shift > s273.size() ) 
throw s960.s992( L"too many arguments: expected " + std::to_wstring( s273.size() ) + L", received " +
std::to_wstring( s698.size() ));}
s588::~s588(){
s273.clear();
s579.clear();
s973.clear();
s580.clear();}
s835::~s835(){}
s558::s558( s261* pass_, s1889& s188, const vector<s270*>& l, 
const s262* ast_, bool s2159 )
: s270( pass_, s474 ), s598( s188 ), past( (s262*)ast_ ), s2158( s2159 ){
s273.assign( l.begin(), l.end() );}
s558::s558( const s558& right )
: s270( right.s299, s474 ), s598( right.s598 ), past( right.past ),
s2158( right.s2158 ){
for( size_t n = 0; n < right.s273.size(); ++n ) {
s273.push_back( right.s273[n]->s332(0,0) );}}
wstring s588::s827() const{
if( s585.s14() )
return s585->s297();
else if( s572 == s563 )
return L"::";
else
throw new s16( L"Cannot get module name." );}
std::wstring s588::s297() const{
return ns->s827();}
std::wstring s588::s2153() const{
if( s2158 )
return ns->s827();
return s584.s14() ? s584->s2153() : s585->s827();}
void s588::s840( s270* par, size_t pos, s482& s152, const s271* s1657, bool proc ){
if( par->s491() == s474 ) {
s487 cs = new s558( *((s558*)par) );
s152 = s597( cs, s299, (s271*)s1657, this, s1657->s2153(), cs->s2165() );
s152.s15<Transd*>()->s497( s585 ? s585 : s1657, cs->s2165() );}
else if( par->s491() == s471 ) {
par->s497( /*s585*/ this, false );
s152 = par;}
else if( par->s491() == s473 ) {
s152 = par; // par->s493();
s152->s2117( this, (s271*)s1657, s152.s15<Transd*>()->s2165()  );	  //???DEBUG??? 220828
}
else if( par->s491() == s1234 ) {
if( this->s491() == s1234 )
( (s831*)par )->s585 = this; 
par->s497( this, false );
s152 = par;}
else
s152 = par;}
void s588::s586(const wstring& s331){}
void s588::s497( const s271* s2160, bool proc/*=false*/ )
{
s1648->s348( s490 );
s666 = proc ? s2153() : s2160->s2153(); // ???DEBUG??? 220420
if( s585 && (s585->s491() == s476 || s585->s491() == s475 )) {
if( 0 && s585->s491() == s475 ) 
return;}
if( s572 == s563 && s615() == s7::s860 )
return;
s580.clear();
for( size_t n = 0; n < s273.size(); ++n ) {
s482 par = s273[n];
if( s572 == s563 && n == 1 ) {
s588::s1231( s273, ((s333*)s273[0]->s493())->s1181( s277 ) );}
if( par->s491() == s472 ) {
if( 1 || par.s15<s368*>()->s378().s13() || s572 == s565 ) { 
if( ! par.s15<s368*>()->s378().s13() )
par.s15<s368*>()->reset();
s484 s1660 = s585;
if( s2160 != this )
s585 = (s271*)s2160;
par.s15<s368*>()->s497( s584, s2158 );
s585 = s1660;}
s580.push_back( par.s15<s368*>()->s374() );}
else if( par->s491() == s1055 || par->s491() == s478 )
s580.push_back( /*NULL*/ par.s15<s480*>() );
else {
try {
s840( par, n, s273[n], s2160, proc );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s277 + L"' function " );}
s580.push_back( s273[n]->s493() );}
if( s277 == s232 || s572 == s564 || s572 == s565 ) {
s480* par = s273[n]->s491() == s473 ? s273[n]->s493() : s273[n].s15<s480*>();
s625.s538( s628[n].s614(), par, s479::s146 );
s273[n]->s1664( s7::s860 );
s627[n] = par;}}
if( s572 == s562 || s572 == s564 ) {
for( size_t n = 0; n < s581.size(); ++n ) {
if( s581[n]->s491() == s474 ) {
s487 cs = new s558( *s581[n].s15<s558*>() );
s581[n] = s597( cs, s299, s585, this, s585->s2153(), cs->s2165() );}
else if( s581[n]->s491() == s472 )
s581[n].s15<s368*>()->s497( s584, false );
else if( s581[n]->s491() != s473 )
s581[n]->s497( s584 );
else if( s489 != s1234 )
throw new s16( L"unhandled expression" );}
for( auto it : s581 ) {
if( it->s491() == s473 )
it.s15<Transd*>()->s497( s2160, false );
else if( it->s491() == s1234 )
it.s15<Transd*>()->s497( s584, false );}
if( !s490 && s581.size() ) {
s490 = s581.back()->s349();}}
if( s490 ) {
if( s585.s14() ) {
s583 = s299->TR().s515( s349(), s585, s585->s297() );}
else {
s583 = s299->TR().s515( s349(), (s271*)s2160, s2160->s2153() );}
s583->s497( s584, proc );
s583->s1664( s7::s860 );
s580.insert( s580.begin(), s583 );
if( s273.size() ) {
s578 = (s481**)&s273[0];
nlocs = s273.size();
s577 = &s580[0];
s495 = s580.size();}
else {
s578 = NULL;
s577 = NULL;
nlocs = s495 = 0;}}
s973.resize( s580.size() );}
void s834::s497( const s271* s1657, bool proc/*=false*/ )
{
TDException s960( s7::s1116, s1122, past );
s588::s497( s1657, proc );
s270* par = s273[0]->s493();
s333* s696 = NULL;
s1132 s1227;
s469 s703 = par->s491();
s1112 ap;
if( s703 == s472 ) {
s368* ref = (s368*)par;
s483 pobj = ref->s374();
s703 = pobj->s491();
s696 = pobj.s15<s333*>();
ap = s1112( s273, s696 );
try {
s1227 = s696->s1182( s277, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s333::s334::s1123::s1170 ) {
s1227 = s696->s1177( s277, ap );}}}
else {
s696 = ( (s333*)par );
ap = s1112( s273, s696 );
try {
s1227 = ( (s333*)s696->s493() )->s1182( s277, ap );}
catch( s16* e ) {
if( e->which() == (uint32_t)s333::s334::s1123::s1170 ) {
s1227 = ( (s333*)s696->s493() )->s1177( s277, ap );}}}
if( !s1227.s336 )
throw s960.s992( L"method is not resolved: " + par->s350() + L"::" + s277 + 
ap.s1318( s299 ) );
try {
s299->s1997( s1227.s2019, s2029 );}
catch( s16* e ) {
throw s960.s992( e->Msg() );}
s490 = s1227.s335;
s559 = s1227.s336;
s1960 = s1227.s1158;
bool s1747;
if( s273[0]->s491() != s473 /*==s472*/ )
s1747 = s273[0]->s1193();
else //if( s273[0]->s491() == s473 )
s1747 = s273[0]->s493()->s1193();
if( !s1960 && s1747 )
throw s960.s992( L"non-constant function is applied to a constant variable" );
if( s277 == s7::s1345 )
s583 = s273[0].s15<s480*>();
if( s583.s13() ) {
s583 = s299->TR().s515( s349(), s585, s585->s297() );
s583->s497( s584 );
s580.insert( s580.begin(), s583 );}
if( s273.size() ) {
s578 = (s481**)&s273[0];
nlocs = s273.size();
s577 = &s580[0];
s495 = s580.size();}
else {
s578 = NULL;
s577 = NULL;
nlocs = s495 = 0;}
s973.resize( s580.size() );
s1251();
s583->s1251();
s583->s1249( s1747 );}
void s835::s497( const s271* s1657, bool proc/*=false*/ )
{
TDException s960( s7::s1510, s1543, s600() );
s666 = proc ? s585->s297() : s1657->s297();
if( ns->s491() == s476 || ns->s491() == s475 ) {
s586( s666 );
if( s585->s491() == s475 )
return;}
if( s273.size() > s627.size() )
throw s960.s992( L"too many arguments" );
for( size_t n = 0; n < s273.size(); ++n ) {
if( s572 != s564 && n == 0 && s273[n]->s615() == s7::s860 )
continue;
s482 par = s273[n];
if( par->s491() == s472 ) {
if( !par.s15<s368*>()->s378().s13() )
par.s15<s368*>()->reset();
par.s15<s368*>()->s497( s584.s14() ? s584.s15<s588*>() 
: s1657, false ); 
s580.push_back( par.s15<s368*>()->s374() );}
else
s840( par, n, s273[n], s1657, proc );
s480* par_ = s273[n]->s491() == s473 ? s273[n]->s493() : s273[n].s15<s480*>();
s625.s538( s628[n].s614(), par_, s479::s146 );
s627[n] = par_;
if( s579.size() > n ) {
if( s579[n]->s349() == Types.No ) {
if( !s579[n]->s498( s273[n].s15<s480*>() ) )
throw s960.s992( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s579[n]->s350() + L"', received - '" + par->s350() + L"'" );}
else if( !s299->TR().s1522( s273[n]->s349(), s579[n]->s349() ) ) {
throw s960.s992( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s579[n]->s350() + L"', received - '" + par->s350() + L"'" );}}}
for( size_t n = 0; n < s273.size(); ++n ) {
if( s273[n]->s493()->s1193() && !s628[n].s1193() )
throw s960.s992( L"constant argument is passed to non-constant function: " + s628[n].s614() );
s627[n] = s273[n];}
s485 s1351 = s584;
s584 = 0;
for( size_t n = 0; n < s581.size(); ++n ) {
if( s581[n]->s491() == s474 ) {
s487 cs = new s558( *s581[n].s15<s558*>() );
s581[n] = s597( cs, s299, s585, this, s585->s297(), cs->s2165() );}
else if( s581[n]->s491() == s472 )
s581[n].s15<s368*>()->s497( s585, true );
else if( s581[n]->s491() != s473 &&
s581[n]->s491() != s1234 )
s581[n]->s497( s585 );
else // lambda - ?
;// throw new s16( L"unhandled expression" );
}
for( auto it : s581 ) {
if( it->s491() == s473 )
it.s15<Transd*>()->s497( s585, it.s15<Transd*>()->s2165() );}
s584 = s1351;
if( !s490 ) {
if( s581.size() ) {
s490 = s581.back()->s349();
s583 = s299->TR().s515( s349(), s585, s585->s297() );}
else {
s490 = s1142;
s583 = s362.s15<s480*>();}
s583->s1664( s7::s860 );
s580.insert( s580.begin(), s583 );}
else
s583 = (s480*)s299->TR().s999( s349() )->s332( s584, s585 );
if( s273.size() ) {
s578 = (s481**)&s273[0];
nlocs = s273.size();
s577 = NULL;// &s580[0];
s495 = s580.size();}
else {
s578 = NULL;
nlocs = s495 = 0;
s577 = NULL;}
s973.resize( s580.size() );
s1251();}
void s588::s1895( const s574& pl ) const{
TDException s960( s7::s1888, s1543, s600() );
size_t shift = 0;
if( s572 == s565 || s572 == s563 )
shift = 1;
if( pl.size() > s627.size() + shift )
throw s960.s992( L"too many arguments to lambda call" );
if( pl.size() < s579.size() )
throw s960.s992( L"too few arguments to lambda call" );
for( size_t n = shift; n < pl.size(); ++n ) {
s482 par = pl[n];
if( s579[n]->s349() == Types.No ) {
if( !s579[n]->s498( par.s15<s480*>() ) )
throw s960.s992( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s579[n]->s350() + L"', received - '" + par->s350() + L"'" );}
else if( !s299->TR().s1522( par.s15<s270*>(), s579[n].s15<s270*>() ) ) {
throw s960.s992( L"wrong argument type: for #" + std::to_wstring( n ) + L" parameter expected '" +
s579[n]->s350() + L"', received - '" + par->s350() + L"'" );}
if( par->s615() == s7::s861 )
throw s960.s992( L"uninitialized function parameter: " + s628[n].s614() );
if( par->s493()->s1193() && !s628[n].s1193() )
throw s960.s992( L"constant argument is passed to non-constant function: " + s628[n].s614() );}}
void s588::s2171( s368* ref ){
subject = ref;}
void s588::s593( const vector<s482>& l ){
s1895( l );
for( size_t n = 0; n < l.size(); ++n )
s273[n] = l[n];}
void s835::s2258( const std::vector<s482>& l ){
for( size_t n = 0; n < l.size(); ++n )
s273[n] = l[n];}
void s835::s2245( ){
s1895( s273 );}
s482 s588::s2283() {
if( s584.s15<s480*>() != this )
return s584->s2283();
return NULL;}
s482 s835::s2283() {
if( subject->s491() == s472 )
return subject.s15<s368*>()->s374(); 
return s1639->s2102().s15<s481*>(); // ???DEBUG??? 220802
}
void s588::s594( const s271* s1657 ){
TDException s960( s7::s1586, s1543, s600() );
if( s572 != s563 && s572 != s562 && s273.size() > s627.size() )
throw s960.s992( L"too many arguments" );
for( size_t n = 0; n < s273.size(); ++n ) {
s270* par = s273[n];
if( par->s491() == s474 ) {
s487 cs = new s558( *(s558*)par );
par = s597( cs, s299, (s271*)s1657, /*this*/s584, s585->s297(), false );
((s588*)par)->s497( s1657, false );
s273[n] = par;}
if( s273[n]->s491() == s478 ) {
s580.push_back( s273[n]->s493() );}
else if( s273[n]->s491() != s472 ) {
if( ( s572 != s563 && s572 != s562 ) || s277 == s232 ) {
s273[n]->s497( s1657, s2165() );
s627[n] = s273[n]->s493();
s627[n]->s1664( s7::s860 );
s625.s538( s628[n].s614(), s627[n].s15<s480*>(), s479::s146 );}}
else {
if( s572 != s563 && s572 != s562 ) {
s627[n] = s273[n].s15<s480*>();
s625.s538( s628[n].s614(), s273[n].s15<s368*>()->s374(), s479::s146 );}
if( s273[n].s15<s368*>()->s378().s13() ) {
s273[n].s15<s368*>()->s497( s584, s2158 );}}
if( s277 != s232 && n < s627.size() && n < s579.size() && !s627[n].s15<s480*>()->s498( (s480*)s579[n] ) )
throw s960.s992( L"wrong argument's type" );}
for( size_t n = 0; n < s627.size(); ++n ) {
if( s627[n]->s615() == s7::s861 )
throw s960.s992( L"parameter is not provided" );}}
void s588::s807( s828& s152 ) const{
for( size_t n = 0; n < s579.size(); ++n )
s152.push_back( make_pair( s628[n].s614(), s579[n] ) );}
void s588::s2113( s574& s2112 ){
for( size_t n = 0; n < s273.size(); ++n ) {
if( s273[n]->s491() == s472 ) {
s368* ref = s273[n].s15<s368*>();
ref->reset();
ref->s379( s2112[n].s15<s480*>() );}
else if( s273[n]->s491() == s471 ) {
s273[n] = s2112[n];}
s627[n] = s2112[n];}}
void s588::s2117( s588* s2041, s271* impl, bool proc ){
if( s2041 && s2041 != this && s2041 != s584 ) s584 = s2041;
if( 0 && subject.s14() ) // ???DEBUG??? 220728 V
subject->s2117( s584, s585, false );
for( size_t n = 0; n < s273.size(); ++n ) {
s273[n]->s2117( this, s585, false ); // ???DEBUG??? 220702
if( n < s627.size() ) {
s627[n]->s2117( this, s585, false ); // ???DEBUG??? 220702
s625.s538( s628[n].s614(), s627[n].s15<s481*>(), s479::s146 );}}
for( size_t n = 0; n < s581.size(); ++n )
s581[n]->s2117( this, s585,  false );}
s480* s588::s1598( s480** s686, size_t s690 ){
size_t shift = 0;
if( s572 == s562 || s572 == s563 || s572 == s2097 )
shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s578 + n ) ) {
s469 pc = ( ( s481* )*( s578 + n ) )->s491();
if( pc == s472 || pc == s1326 ) {
s480* p = (s480*)( ( s368* )*( s578 + n ) )->s374();
*(s577 + n + shift) = p;}
else if( pc == s473 ) {
s973[n + shift] = (s480*)( ( s588* )*( s578 + n ) )->s494( s686, s690 );
if( s973[n + shift]->s615() < 0 ) {
int s152 = s973[n + shift]->s615();
if( s152 == s7::s859 || s152 == s7::s2218 )
s973[n + shift]->s1664( 0 );
else
return s973[n + shift];}
*( s577 + n + shift ) = s973[n + shift];}
else if( pc == s471 )
*( s577 + n + shift ) = ( s480* )*( s578 + n );
else if( pc == s1234 )
(void)0;}}
return NULL;}
s483 s588::s494( s480** s686, size_t s690 ){
s483 s680;
s680 = s1598( s686, s690 );
if( s680.s14() )
return s680;
for( size_t n = 0; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s577, s495 );
if( s680->s615() < 0 )
break;}
s583 = s680;
return s680;}
s483 s834::s494( s480** s686, size_t s690 ){
s480* s680 = NULL;
s680 = s1598( s686, s690 );
if( s680 )
return s680;
if( !s1960 && s580[1]->s1193() )
throw new s16( L"non-constant function is applied to a constant variable" );
try {
s559( s577, s495 );
s680 = s580[0];}
catch( s16* e ) {
TDException s960( TDException::Stage::s1022, s7::s1117, 
s1121, past,	*e );
delete e;
s680 = new s358( s299, s960.Msg() );
s583 = s680;}
return s680;}
s483 s835::s494( s480** s686, size_t s690 ){
s480* s680 = s362;
if( subject.s14() && (s572 == s565 || s572 == s564 )) {
if( subject->s491() == s472 ) {
if( s277 != s7::s425 )
subject->s2117( this, s585, false );
s1639->s1646( subject.s15<s368*>()->s374() );}
else if( subject->s491() == s473 )
s1639->s1646( subject->s494(0,0) );
else {
if( s585->s491() == s477 && s584.s14() )
subject = s584->s2283();
s1639->s1646( subject.s15<s480*>() );}}
for( size_t n = 0; n < s579.size()/*nlocs*/; ++n ) {
if( *( s578 + n ) ) {
if( !( ( s481* )*( s578 + n ) )->s1194() )
throw new s16( L"uninitialized function parameter: " + s628[n].s614() );
s469 pc = ( ( s481* )*( s578 + n ) )->s491();
if( pc == s472 ) {
s480* par =( ( s368* )*( s578 + n ) )->s374();
if( par->s491() == s1234 ) {
par->s497( this, false );}
s627[n] = par;}
else if( pc == s473 ) {
s627[n] =
(s480*)( ( s588* )*( s578 + n ) )->s494( s686, s690 );
if( s627[n]->s615() < 0 ) {
int s152 = s627[n]->s615();
if( s152 == s7::s859 || s152 == s7::s2218 )
s627[n]->s1664( 0 );
else
return s627[n].s15<s480*>();}}
else if( pc == s471 )
s627[n] = *( s578 + n );}}
for( size_t n = s579.size(); n < nlocs; ++n ) {
if( *( s578 + n ) ) {
s469 pc = ( ( s481* )*( s578 + n ) )->s491();
if( pc == s472 ) {
s480* par = ( ( s368* )*( s578 + n ) )->s374();
if( par->s491() == s1234 ) {
s627[n] = par->s332(0,0);
s627[n]->s497( this, false );}}
else if( pc == s473 ) {
s627[n] =
(s480*)( ( s588* )*( s578 + n ) )->s494( s686, s690 );
if( s627[n]->s615() < 0 ) {
int s152 = s627[n]->s615();
if( s152 == s7::s859 || s152 == s7::s2218 )
s627[n]->s1664( 0 );
else
return s627[n].s15<s480*>();}}
else if( pc == s471 )
s627[n] = ( ( s481* )*( s578 + n ) )->s332(0,0);
else if( pc == s477 ) {
s627[n] = ( ( s481* )*( s578 + n ) )->s332( 0, 0 );
s627[n]->s497( this, false );}}}
for( size_t n = 0; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s577, s495 );
if( s680->s615() < 0 ) {
if( s680->s615() == s7::s859 )
s680->s1664( 0 );
break;}}
return s680;}
s1346::s1346( s261* s299, s271* s589, s588* s584, const s262* s694 )
: s835( s299, s589, s584, s589, s565, vector<s270*>(), s694 ){
s1346* pin = (s1346*)s585->s341( s7::s425, s585->s297(), false );
if( pin ) {
pin->s625.copy( s625, (s271*)s585, s584 );
s628 = pin->s628;
s627 = pin->s627;
s579 = pin->s579;}}
s1346::s1346( const s1346& right, s271* s589, s588* s590,
const std::vector<s270*>& s698, const s262* s694 )
: s835( right, s590, vector<s481*>(), s565, s694 ){
s585 = s589;
s273.assign( s698.begin() + 1, s698.end() );
s490 = right.s490;
s583 = (s480*)s698[0];}
s1346::~s1346(){}
void s1346::s497( const s271* s1657, bool proc/*=false*/ )
{
s583 = s585.s15<s271*>();
s490 = s583->s349();
s588::s497( s1657, proc );// ???DEBUG??? 220717
s580.erase( s580.begin() );// ???DEBUG??? 220717
s1251();}
s483 s1346::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
if( s585->s349() == s1701 ) {
s680 = new s831( *s585.s15<s831*>(), ns, s585.s15<s588*>(), s273, s600() );
s680->s497( s584 );}
else {
s574 s2279;
s2279.assign( s580.begin(), s580.end() );
s680 = new s271( *s585, s2279, s600(), ns );
s680->s497( s584 );
s680->s2117( NULL, (s271*)s680, s2158 );}
s680->s1251();
return s680;
wstring s188 = s600()->s290();
wstring s1347 = s600()->Src();
s1347.replace( s1347.find( s188 ), s188.size(), 1, L' ' );
s262* ast_ = new s262( s188, s1347 );
s680 = s583.s15<s271*>()->s632( *ast_, s584, s666 );
s680->s1251();
return s680;
vector<s270*> s1635( begin(s273), end(s273));
s680 = s583->s352( s584, s1635, s600() );
s680->s1251();
return s680;}
bool
s588::s553( const wstring& s671, s368* ref,	
const wstring& s331, bool fr ) const{
bool s680 = false;
wstring s76 = s671;
size_t pl = s76.find( L"." );
if( pl == string::npos ) { //a
bool s2127 = s625.s155( s76 );
bool s2128 = true;
if( s2127 ) {
size_t off = s637( s76 );
if( 0 && off >= s579.size() ) // ???DEBUG??? 220721
s2128 = false;}
if( ( !s2127 && !s2158 ) || ( !s2127 && !fr ) || (!s2127 && s2158 && fr) ||
( s2127 && !s2158 && !fr && !intro )
/*|| ( s584.s14() && !intro && s2128 )*/ ) {
if( s584.s14() && ((s572 == s562 || s572 == s2097) || !fr ||
(s489 == s1234 && !s2158 ) ) ) 
s680 = s584->s553( s76, ref, s331, s2158 );
if( !s680 ) {
if( s585.s14() )
s680 = s585->s553( s76, ref, s331, s2158 );
if( s680 ) {
if( s585->s491() != s476 && ref->s378() == s585.s15<s270*>() ) {
ref->s379( s1639.s15<s480*>() );
if( s1639.s15<s1587*>()->s2102().s13() ) // ???DEBUG??? 220904
s1639.s15<s1587*>()->s1646( s585.s15<s480*>() );}}}
if( ! s680 )
s680 = s299->s553( s76, ref, s331, true );}
if( !s680 && s2127 ) {
size_t off = s637( s76 );
s270* s1052 = s627[off].s15<s270*>()->s493();
if( !s1052 )
s1052 = (s270*)s299->TR().s999( s627[off]->s349() );
assert( s1052 != ref );
ref->s376( off, s1052->s500() );
if( s628[off].s1193() )
ref->s1249();
ref->s379( (s480*)this /*(s481**)&s273[off]*/ );
s680 = true;}}
else {// a.y
s76 = s671.substr( pl + 1 );
wstring s681 = s671.substr( 0, pl );
s270* ob = s625.get( s681, false );
if( !ob ) {
s680 = s585->s553( s671, ref, s331, true );
if( !s680 && s584.s14() )
s680 = s584->s553( s671, ref, s331, true );}
else {
size_t off = s637( s681 );
ref->s376( off, NULL );
s680 = ob->s500()->s553( s76, ref, s331, true );
ref->s379( (s480*)this );}}
return s680;}
bool
s834::s553( const wstring& s671, s368* ref, const wstring& s331,
bool fr) const{
if( s277 == s7::s1345 &&
s273[0].s15<s480*>()->s553( s671, ref, s331, fr ) )
return true;
return s588::s553( s671, ref, s331, fr );}
s270* s588::s595( size_t off ){
s270* s680 = s627[off];
return s680;}
s270* s588::s332( s588* s2041, s271* impl ) const{
return new s588( *this );}
s270* s834::s332( s588* s2041, s271* impl ) const{
return new s834( *this, s2041 ? s2041 : s584.s15<s588*>(), ns );}
s270* s835::s332( s588* s2041, s271* impl ) const{
auto s680 = new s835( *this, s2041, std::vector<s270*>(), s572, s600(), 
impl ? impl : s585.s15<s271*>(), s585.s15<s271*>(), intro, s2158 );
return s680;}
s270* s1346::s332( s588* s2041, s271* impl ) const{
return new s1346( *this );}
void s588::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
wstring ct []{ L"notInit", L"BIFunc", L"BIMeth", L"FTFunc", L"FTMeth" };
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Transductor : " <<  s277 << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"this : " << 
s4::s2169( (void*)this ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"subject : " << 
s4::s2169( subject.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"Type : " << 
s490 << L" (" << s350() << L")" << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"State : " << wh << endl;
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"Call type : " << ct[s572] << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"cont : " << 
s4::s2169( s585.s15<void*>() ).c_str() << endl;
buf << s4::fill_n_ch( L' ', s196 + s416) << L"pout : " << 
s4::s2169( s584.s15<void*>() ).c_str() << endl;
if( !s625.empty() ) {
s625.s303( pd, s196 + s416 );}
if( !s579.empty() ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"fpars : " << endl;
for( size_t n = 0; n < s579.size(); ++n ) {
s579[n]->s303( pd, s196 + s416 * 2 );}
buf << endl;}
if( !s273.empty() ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"pars : " << endl;
for( size_t n = 0; n < s273.size(); ++n ) {
s273[n]->s303( pd, s196 + s416 * 2 );
buf << endl;}
buf << endl;}
if( !s628.empty() ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"namvec : " << endl;
for( size_t n = 0; n < s628.size(); ++n )
buf << s4::fill_n_ch( L' ', s196 + s416 * 2 ) << s628[n].s614()
<< "; ";
buf << endl;}
if( !s627.empty() ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"memvec : " << endl;
for( size_t n = 0; n < s627.size(); ++n ) {
s627[n]->s303( pd, s196 + s416 * 2 );}
buf << endl;}
if( !s581.empty() ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << L"exprs : " << endl;
for( size_t n = 0; n < s581.size(); ++n ) {
s581[n]->s303( pd, s196 + s416 * 2 );}
buf << endl;}}
wstring s588::trace( s1889& topics ) const{
wstringstream buf;
int s196 = 0;
wstring s1069 = std::to_wstring( reinterpret_cast<long long>(this));
s1069 = s1069.substr( s1069.size() - 5 );
if( topics.empty() ) {
s588::s303( &buf, s196 );}
else {
buf << L"Transductor : " << s1069 << endl;
if( topics == L"id" ) 
buf << L"id: " << s1069 << endl;}
return buf.str();}
static s6::s1680 s1722;
s356::s356( s261* s299, const std::wstring& s, s271* s585, const s262* ast_ )
: s1389( s299, s585, ast_ ){
s490 = Types.String;
if( !s490 )
wh = s7::s861;
else {
wh = s7::s860;
s346 = s;}
s322 = s1566;}
s356::s356( s261* s299, s271* s589, const std::vector<s270*>& l, const s262* ast_ )
: s1389( s299, s589, ast_ ){
s273.assign( begin( l ), end( l ) );
if( l.empty() )
wh = s7::s861;
else
wh = s7::s860;
s490 = Types.String;
s322 = s1566;}
s356::s356( const s356& r, const s262* ast_ )
: s1389( r.s299, r.ns, ast_ ){
s346 = r.s346;
for( auto p : r.s273 )
s273.push_back( p->s332( 0, (s271*)r.ns ) );
wh = r.wh;
s490 = r.s490;
s322 = s1566;}
s356::s356( s261* s299, const std::wstring& s, size_t& pos, const s262* ast_ )
: s1389( s299, NULL, ast_ ){
s346 = s;
pos = string::npos;
s490 = Types.String;
s322 = s1566;
wh = s7::s860;}
s356::~s356(){}
s480* s356::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s356( s299, s585, l );}
void s356::s347(){
s1389<s1564, wchar_t, s356, s1560>::s347();
s345 = s1389<s1564, wchar_t, s356, s1560>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s356::s1226, Types.String,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 100 ) ) );
s345.insert( make_pair( L"index-of", new s334( L"index-of", &s356::search_impl, s1141,
{ s1112( { Types.String } ), s1112( { s1143, s1500::s1537 } ) }, 1, 1, true, {L":rev"} )));
s345.insert( make_pair( L"find-first-not-of", new s334( L"find-first-not-of", &s356::s1575, s1141,
{ s1112( { Types.String } ), s1112( { Types.String, s1141 } ), 
s1112( { Types.String, s1141, s1141 } )}, 1, 3 )));
s345.insert( make_pair( L"contains", new s334( L"contains", &s356::s2189, s1138,
{ s1112( { Types.String } ), s1112( { Types.Char } ) }, 1, 1 )));
s345.insert( make_pair( L"set", new s334( L"set", &s356::s384, s1143,
{ s1112( { Types.String } ), s1112( { s1142 } ) }, 1, 1, false )));
s345.insert( make_pair( L"set-el", new s334( L"set-el", &s356::s1579, s1143,
{ s1112( { s1141, Types.String } ), s1112( { s1141, s1566 } ) }, 2, 2 )));
s345.insert( make_pair( L"size", new s334( L"size", &s356::s325, s1141,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"starts-with", new s334( L"starts-with", &s356::s1674, s1138,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"ends-with", new s334( L"ends-with", &s356::endsWith_impl, s1138,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"strip", new s334( L"strip", &s356::s2139, s1143,
{ s1112(), s1112( { Types.String } ), s1112( { Types.String, Types.String } ) }, 
0, 2 ) ) );
s345.insert( make_pair( L"sub", new s334( L"sub", &s356::s787, Types.String,
{ s1112( { s1500::s1537 } ), s1112( { s1500::s1260, s1500::s1260 } ) }, 1, 2 )));
s345.insert( make_pair( L"subn", new s334( L"subn", &s356::s1582, Types.String,
{ s1112( { s1500::s1537 } ), s1112( { s1500::s1260, s1500::s1260 } ) }, 1, 2 )));
s345.insert( make_pair( L"charn", new s334( L"charn", &s356::s2244, Types.Char,
{ s1112( { s1500::s1537 } ) }, 1, 1 )));
s345.insert( make_pair( L"sum", new s334( L"sum", &s356::s385, Types.String,
{ s1112( { Types.String, s7::s1387 } ) }, 1, 100 )));
s345.insert( make_pair( L"sumeq", new s334( L"sumeq", &s356::s390, Types.String,
{ s1112( { Types.String, s7::s1387 } ) }, 1, 100 )));
s345.insert( make_pair( L"to-bytes", new s334( L"to-bytes", &s356::s1336, s1139,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"to-Int", new s334( L"to-Int", &s356::s409, s1141,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"tolower", new s334( L"tolower", &s356::s883, Types.String,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"toupper", new s334( L"toupper", &s356::s884, Types.String,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"islower", new s334( L"islower", &s356::s2222, s1138,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"isupper", new s334( L"isupper", &s356::s2224, s1138,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"swapcase", new s334( L"swapcase", &s356::s2230, Types.String,
{ s1112() }, 0, 0 )));
s345.insert( make_pair( L"rindex-of", new s334( L"rindex-of", &s356::rsearch_impl, s1141,
{ s1112( { Types.String } ), s1112( { Types.String, s1500::s1537 } ) }, 1, 2 )));
s345.insert( make_pair( L"eq", new s334( L"eq", &s356::s395, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"not", new s334( L"not", &s356::s410, s1138,
{ s1112( ) }, 0, 0 )));
s345.insert( make_pair( L"less", new s334( L"less", &s356::s396, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"greater", new s334( L"greater", &s356::s397, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"leq", new s334( L"leq", &s356::s398, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"geq", new s334( L"geq", &s356::s399, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"neq", new s334( L"neq", &s356::s400, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"max", new s334( L"max", &s356::s1949, s1143,
{ s1112( { Types.String, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"min", new s334( L"min", &s356::s1950, s1143,
{ s1112( { Types.String, s7::s1387 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"read", new s334( L"read", &s356::s406, s1143,
{ s1112( ), s1112( { s1141 } ), s1112( { s1500::s1493 } ), 
s1112( { s1500::s1493, s1141 } ) }, 1, 2 )));
s345.insert( make_pair( L"getline", new s334( L"getline", &s356::s1471, s1141,
{ s1112(), s1112( { s1500::s1493 } ) }, 0, 1 )));
s345.insert( make_pair( L"match", new s334( L"match", &s356::s1026, s1138,
{ s1112( { Types.String } ) }, 1, 1 )));
s345.insert( make_pair( L"replace", new s334( L"replace", &s356::s2188, s1143,
{ s1112( { Types.String, Types.String/*, Types.String*/ } ),
s1112( { Types.String, Types.String, Types.String, Types.Int } ),
s1112( { Types.String, Types.String, Types.String, Types.Int, Types.Int } ),
}, 3, 5 )));
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, Types.String )->s350() + L">";
s1053 s1505 = ( (s313*)Types( s299, Types.Vector ) )->s1185( this, ts, s1704, s1268 );
s345.insert( make_pair( L"split", new s334( L"split", &s356::s1478, s1505,
{ s1112(), s1112( { Types.String } ) }, 0, 0, true, {L"plain:", L"regex:"} )));
s299->TR().s1152( s490, s7::s1400, s1500::s1496 );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );
s1722 = s1721;
s1722.s1682 = L" \n";}
void s840( s270* par, s261* s299, s271* s585,
s588* s214, s482& s152 ){
if( par->s491() == s474 ) {
s487 cs = new s558( *( (s558*)par ) );
s152 = s588::s597( cs, s299, s585, s214, s585->s297(), false );
s152.s15<Transd*>()->s497( s585, false );}
else if( 1 && par->s491() == s471 ) {
par->s497( /*s585*/ s585 );
s152 = par;}
else
s152 = par;}
void s356::s497( const s271* s872, bool ){
s314 = s299->TR().s1038( std::vector<s1053>(
{ s1702, 2, s1141, 0, s322, 0 } ) );
for( size_t n = 0; n < s273.size(); ++n ) {
s482 par = s273[n];
if( par->s491() == s474 ) {
s840( par, s299, ns, (s588*)ns, s273[n] );}
else if( par->s349() == s1403 ) {
auto pr = par.s15<s382*>();
auto rp = pr->s1184();
typename s1374::iterator s1507, s1508;
s1507 = rp.first.s15<s1129*>()->s1135();
s1508 = rp.second.s15<s1129*>()->s1135();
s1374 news( s1507, s1508 );
s346 += news;}
else if( par->s491() != s472 ) {
s346 += par->to_wstring();}
else {
if( s299->s1319() /*par.s15<s368*>()->s378().s14()*/ ) {
if( par.s15<s368*>()->s378().s13() )
par->s497( s872, false );
s346 = par.s15<s368*>()->s374()->to_wstring();}}}
s1251();}
wstring s693( wchar_t c ){
wstring s680;
if( c == L'n' )
s680 = L"\n";
else if( c == L'r' )
s680 = L"\r";
else if( c == L't' )
s680 = L"\t";
else if( c == L'\\' )
s680 = L"\\";
else {
s680 = c;}
return s680;}
s480* s356::s351( const s262& s694, s271* s585, 
const std::wstring& s331 ) const{
wstring s_ = s694.s290();
wstring s346, s;
size_t pl;
if( s_.find( L"String(" ) == 0 ) {
s = s4::s52( s_.substr( 7, s_.size() - 8 ), s48 );
if( s.empty() )
return new s356( s299, s585, std::vector<s270*>() );
vector<s270*> s698;
s270::s1322( s694, s299, s585, s331, s698 );
return s352( s585, s698, &s694 );}
else
s = s4::s52( s_, s48 );
if( s.size() ) {
size_t pos = 0;
const s937* s1043 = NULL;
if( s600() && s600()->Nqj() )
s1043 = s600()->Nqj()->s998();
vector<s1::s9<s6::s140>> s93;
s6::s177( s1043, s, pos, s93, s1722 );
if( s93.size() ) {
s = L"";
for( size_t n = 0; n < s93.size(); ++n ) {
wstring tmp = s93[n]->s168();
pl = s87.find( tmp[0] );
if( pl != string::npos && tmp.back() == s87[pl] )
tmp = tmp.substr( 1, tmp.size() - 2 );
s += tmp;}}}
if( s.size() == 2 && s[0] == L'\\' )
s346 = s693( s[1] );
else if( ( pl = s.find( L"\\" ) ) != string::npos ) {
s346 = s;
while( pl != string::npos ) {
if( pl == s346.size() - 1 )
break;
if( s346[pl + 1] != L'\\' ) {
wstring code = s693( s346[pl + 1] );
s346 = s346.replace( pl, 2, code );
pl = s346.find( L"\\", pl + 1 );}
else {
s346.erase( pl, 1 );
pl = s346.find( L"\\", pl + 1 );}}}
if( s346.empty() )
s346 = s;
return new s356( s299, s346, s585, &s694 );}
s270* s356::s332( s588* s2041, s271* impl ) const{
return new s356( *this );}
s1053 s356::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" )
s680 = s322;
else
s680 = s1389::s1178( s1540, l );
return s680;}
void s356::s353( s270* p ) const{
if( p->s349() == Types.String )
*( (s356*)p )->s354() = s346;
else if( p->s349() == s1141 ) {
try {
*( (s343*)p )->s354() = std::stoi( s346 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string '" + s346 + 
L"' to integer: " + U16( e.what() ) );}}
else if( p->s349() == s1140 ) {
try {
*( (s355*)p )->s354() = std::stof( s346 );}
catch( std::exception& e ) {
throw new s2::s16( L"cannot convert string '" + s346 + 
L"' to double: " + U16( e.what() ) );}}
else if( p->s349() == s1566 )
*( (s1560*)p )->s354() = s346[0];
else
throw new s16( L"No conversion from " + s350() + L" to " + p->s350() );}
s356::operator int() const{
long s680;
if( !s4::s62( s346.c_str(), &s680 ) )
throw new s16( L"cannot cast String " + s346 + L" to Int" );
if( s680 > (std::numeric_limits<int>::max)() )
throw new s16( L"cannot cast String to Int: the value is too big: " + s346 );
return (int) s680;}
s356::operator double() const {
double s680;
if( !s4::s63( s346.c_str(), &s680 ) )
throw new s16( L"cannot cast String '" + s346 + L"' to Double" );
return s680;}
wstring s356::to_wstring( uint32_t s1552 ) const{
if( 0 && s346.front() == '\"' && 
s346.back() == '\"' )
return s346.substr( 1, s346.size() - 2 );
return s346; }
inline void s356::s1478( s480** s273, size_t s495 ){
s313* pv = (s313*)s273[0];
pv->clear();
wstring s72 = L"";
bool s2243 = false;
bool breg = false;
if( s495 > 2 ) {
if( s495 == 4 ) {
if( s273[2]->s491() == s1055 &&
s273[2]->s349() ) {
s486 rf = (s368*)s273[2];
if( rf->Id() == 1 )
breg = true;
s72 = s273[3]->to_wstring();}
else
throw new s16( L"unrecognized 2-nd parameter" );}
else
s72 = s273[2]->to_wstring();
s2243 = true;}
wstring& s = ((s356*)DR)->s346;
size_t s68 = 0, s69 = 0;
s1::s9<s356> adds = new s356( ((s356*)DR)->s299, L"", ( (s356*)DR )->ns );
if( !s2243 ) {
while( s69 != string::npos ) {
s68 = s.find_first_not_of( L" \n\r\t", s69 );
if( s68 == string::npos )
break;
s69 = s.find_first_of( L" \n\r\t", s68 );
adds->s346 = s.substr( s68, s69 - s68 );
if( adds->s346.size() )
pv->s317().push_back( (s480*)adds->s332( 0,0 ) );}}
else {
if( breg ) {
size_t s1804 = 0;
wsmatch sm;
wregex rg( s72 );
wstring::const_iterator itst = s.begin();
wstring::const_iterator iten = s.end();
while( std::regex_search( itst, iten, sm, rg ) ) {
adds->s346 = s.substr( s1804, sm.position( 0 ) );
if( adds->s346.size() )
pv->s317().push_back( (s480*)adds->s332( 0,0 ) );
s1804 = s1804 + sm.position( 0 ) + sm.length( 0 );
itst = s.begin() + s1804;}}
else {
while( s69 != wstring::npos && s68 < s.size()) {
if( s72.size() )
s69 = s.find( s72, s68 );
else
s69 = s68 + 1;
adds->s346 = s.substr( s68, s69 - s68 );
s68 = s69 + s72.size();
if( adds->s346.size() )
pv->s317().push_back( (s480*)adds->s332( 0,0 ) );}}}}
void s356::s1919( Stream* s1918 ) const{
if( s1918->s2051() && (s346[0] != L'"' 
&& s346.back() != L'"' ))
s1918->s1468( L"\"" 
+ s346 + 
L"\"" );
else
s1918->s1468( s346 );
return;
s1488& ss = s1918->s1948();
ss << s346;}
void s356::s1944( s1889& s ){
s346 = s;}
void s356::s1943( Stream* s1918 ){
s1918->s1449( s346, string::npos );
return;
s1485& ss = s1918->s1947();
ss >> s346;}
s1311 s356::to_bytes() const{
s1311 s680;
string s = U8(s346);
s680.resize( s.size() );
for( size_t n = 0; n < s.size(); ++n ) s680[n] = s[n];
return s680;}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s356*)(s481*)*s273)
#define s692 ((s357*)(s481*)*s273)
inline void s356::s1226( s480** s273, size_t s495 ){
s356* ps = (s356*)s273[1];
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 )
{ return v.push_back( (s270*)s346 ); } );
*s273 = ( s480* ) new s356( ps->s299, ps->s299, v );
if( v.size() )
s273[0]->s497( ps->ns );}
inline void s356::s384( s480** s273, size_t s495 ){
if( !PARN( 2 ) )
throw new s16( L"cannot assign Null object to String" );
( (s356*)DR )->s346 = ( (s356*)PARN( 2 ))->s346;
DR->s1251();
*s273 = (s480*)DR;}
inline void s356::s1579( s480** s273, size_t s495 ){
int pl = (int)*s273[2];
wchar_t c;
if( s273[3]->s349() == s1566 )
c = *( (s1560*)s273[3] )->s354();
else
c = ( (s356*)s273[3] )->s346[0];
( (s356*)DR )->s346[pl] = c;
*s273 = (s480*)DR;}
inline void s356::s325( s480** s273, size_t s495 ){
*( (s343*)s691 )->s354() = (int)( (s356*)DR )->s346.size();}
inline void s356::s1674( s480** s273, size_t s495 ){
const wstring& dr = ( (s356*)DR )->s346;
const wstring& str = ( (s356*)s273[2] )->s346;
if( dr.find( str ) == 0 )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}
inline void s356::endsWith_impl( s480** s273, size_t s495 ){
const wstring& dr = ( (s356*)DR )->s346;
const wstring& str = ( (s356*)s273[2] )->s346;
if( dr.rfind( str ) == dr.size() - str.size() )
*( (s357*)s273[0] )->s354() = true;
else
*( (s357*)s273[0] )->s354() = false;}
inline void s356::s2139( s480** s273, size_t s495 ){
wstring& dr = ( (s356*)DR )->s346;
wstring str;
if( s495 == 2 )
str = L" \r\n\t";
else
str = ( (s356*)s273[2] )->s346;
if( s495 < 4 )
dr = s4::s52( dr, str );
else {
wstring& str1 = ( (s356*)s273[3] )->s346;
dr = s4::s51( str, dr, str1 );}
*s273 = (s480*)DR;}
inline void s356::s385( s480** s273, size_t s495 ){
s691->s346 = DR->to_wstring() + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s495; ++n )
s691->s346 += PARN( n )->to_wstring();}
inline void s356::s390( s480** s273, size_t s495 ){
s691->s346 = ((s356*)DR)->s346 + PARN( 2 )->to_wstring();
for( size_t n = 3; n < s495; ++n )
s691->s346 += PARN( n )->to_wstring();
((s356*)DR)->s346 = s691->s346;}
inline void s356::s2222( s480** s273, size_t s495 ){
wstring& str = ((s356*)DR)->s346;
bool s680 = true;
for( size_t n = 0; n < str.size(); ++n ) {
if( ! iswlower( str[0] ) ) {
s680 = false;
break;}}
*((s357*)*s273)->s354() = s680;}
inline void s356::s2224( s480** s273, size_t s495 ){
wstring& str = ((s356*)DR)->s346;
bool s680 = true;
for( size_t n = 0; n < str.size(); ++n ) {
if( ! iswupper( str[0] ) ) {
s680 = false;
break;}}
*((s357*)*s273)->s354() = s680;}
inline void s356::s883( s480** s273, size_t s495 ){
s691->s346 = ((s356*)DR)->s346;
std::for_each( s691->s346.begin(), s691->s346.end(), []( wchar_t & c ) {
c = std::towlower( c );
} );}
inline void s356::s884( s480** s273, size_t s495 ){
s691->s346 = ((s356*)DR)->s346;
std::for_each( s691->s346.begin(), s691->s346.end(), []( wchar_t & c ) {
c = std::towupper( c );
} );}
inline void s356::s2230( s480** s273, size_t s495 ){
s691->s346 = ((s356*)DR)->s346;
std::for_each( s691->s346.begin(), s691->s346.end(), []( wchar_t & c ) {
if( std::iswlower( c  ) ) c = towupper( c ); else c = tolower( c );
} );}
inline void s356::s787( s480** s273, size_t s495 ){
wstring s689 = L"Invalid substring specification: ";
if( s495 < 2 )
throw new s16( s689 + L"too few parameters." );
const wstring& dr = ((s356*)DR)->s346;
int start = 0, end = (int) dr.size();
if( s495 > 2 ) {
start = (int)*s273[2];
if( s495 > 3 )
end = (int)*s273[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is less than 0." );
if( start > (int)dr.size() - 1 )
throw new s16( s689 + L"the start position is greater than string's length." );
if( end < 0 )
end = (int)dr.size() + start;
if( end < 0 )
throw new s16( s689 + L"the end position is less than 0." );
if( start > end )
throw new s16( s689 + L"the start position is greater than string's length." );}
s691->s346 = dr.substr( start, end - start );}
inline void s356::s1582( s480** s273, size_t s495 ){
wstring s689 = L"Invalid substring specification: ";
if( s495 < 2 )
throw new s16( s689 + L"too few parameters." );
const wstring& dr = ((s356*)DR)->s346;
int start = 0, s679 = 1;
if( s495 > 2 ) {
start = (int)*s273[2];
if( s495 > 3 )
s679 = (int)*s273[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( s689 + L"the start position is greater than string's length" );
if( s679 < 0 )
throw new s16( s689 + L"the characters count cannot be less than 0" );}
s691->s346 = dr.substr( start, s679 );}
inline void s356::s2244( s480** s273, size_t s495 ){
const wstring& dr = ((s356*)DR)->s346;
int start = 0;
if( s495 > 2 ) {
start = (int)*s273[2];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( L"charn: the char position is less than 0" );
if( start > (int)dr.size() - 1 )
throw new s16( L"charn: the char position is greater than string's length" );}
*((s1560*)s273[0])->s354() = dr[start];}
inline void s356::search_impl( s480** s273, size_t s495 ){
wstring s689 = L"Invalid 'index-of' syntax: ";
const wstring& dr = ( (s356*)DR )->s346;
int start = 0; 
bool brev = false;
size_t count = dr.size() - 1;
size_t curIdx = 3;
if( s495 > 3 ) {
if( s273[2]->s491() == s1055 &&
s273[2]->s349() ) {
brev = true;
curIdx = 4;
start = count - 1;}
if( s495 > curIdx ) {
start = (int)*s273[curIdx];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s689 + L"the start position is greater than string's length." );}}
const wstring& str = ( (s356*)s273[curIdx - 1] )->s346;
if( !brev )
*((s343*)s273[0])->s354() = (int)dr.find( str, start );
else
*( (s343*)s273[0] )->s354() = (int)dr.rfind( str, start );}
inline void s356::rsearch_impl( s480** s273, size_t s495 ){
wstring s689 = L"Invalid 'rsearch' syntax: ";
const wstring& dr = ( (s356*)DR )->s346;
const wstring& str = ( (s356*)s273[2] )->s346;
int start = (std::numeric_limits<int>::max)();
if( s495 > 3 ) {
start = (int)*s273[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is less than 0." );}
*( (s343*)s273[0] )->s354() = (int)dr.rfind( str, start );}
inline void s356::s1575( s480** s273, size_t s495 ){
wstring s689 = L"Invalid 'find-first-not-of' syntax: ";
const wstring& dr = ( (s356*)DR )->s346;
const wstring& str = ( (s356*)s273[2] )->s346;
int start = 0;
if( s495 > 3 ) {
start = (int)*s273[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s689 + L"the start position is greater than string's length." );}
*((s343*)s273[0])->s354() = (int)dr.find_first_not_of( str.c_str(), start );}
inline void s356::s2189( s480** s273, size_t s495 ){
wstring s689 = L"Invalid 'contains' syntax: ";
const wstring& dr = ( (s356*)DR )->s346;
const wstring& str = ( (s356*)s273[2] )->to_wstring();
int start = 0; 
if( s495 > 3 ) {
start = (int)*s273[3];
if( start < 0 )
start = (int)dr.size() + start;
if( start < 0 )
throw new s16( s689 + L"the start position is negative." );
if( start > (int) dr.size() - 1 )
throw new s16( s689 + L"the start position is greater than string's length." );}
*((s357*)s273[0])->s354() = ( dr.find( str, start ) != string::npos );}
inline void s356::s395( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() == *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s410( s480** s273, size_t s495 ){
*s692->s354() = ( (s356*)DR )->s354()->empty();}
inline void s356::s396( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() < *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s397( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() > *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s398( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() <= *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s399( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() >= *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s400( s480** s273, size_t s495 ){
*s692->s354() = *( (s356*)DR )->s354() != *( (s356*)PARN( 2 ) )->s354();}
inline void s356::s1949( s480** s273, size_t s495 ){
*s691->s354() = ( (s356*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
if( *((s356*)s273[n])->s354() > *s691->s354() )
*s691->s354() = *( (s356*)s273[n] )->s354();}}
inline void s356::s1950( s480** s273, size_t s495 ){
*s691->s354() = ( (s356*)DR )->s346;
for( size_t n = 2; n < s495; ++n ) {
if( *((s356*)s273[n])->s354() < *s691->s354() )
*s691->s354() = *( (s356*)s273[n] )->s354();}}
inline void s356::s406( s480** s273, size_t s495 ){
Stream* s1465 = NULL;
size_t s1440 = 0;
if( s495 >= 3 ) {
if( s273[2]->s349() == s1141 )
s1440 = (int)*s273[2];
else
s1465 = (Stream*)s273[2];
if( s495 == 4 )
s1440 = (int)*s273[3];}
else
s1465 = s1391;
wstring& s152 = *( (s356*)DR )->s354();
s1465->s1449( s152, s1440 );
int s680 = (int)s152.size();
s152.resize( s680 );
s273[0] = s273[1];}
inline void s356::s1471( s480** s273, size_t s495 ){
Stream* s1465 = NULL;
if( s495 >= 3 ) {
s1465 = (Stream*)s273[2];}
else
s1465 = s1391;
wstring& s152 = *( (s356*)DR )->s354();
s1465->s1450( s152 );
int s680 = (int)s152.size();
s152.resize( s680 );
*( (s343*)s691 )->s354() = s680;}
inline void s356::s1026( s480** s273, size_t s495 ){
wregex rg( PARN( 2 )->to_wstring() );
wsmatch s1032;
wstring s = DR->to_wstring();
bool s152 = regex_match( s, s1032, rg );
*s692->s354() = s152;}
inline void s356::s2188( s480** s273, size_t s495 ){
wstring s = DR->to_wstring();
wregex rg( PARN( 2 )->to_wstring() );
wstring rep( PARN( 3 )->to_wstring() );
*((s356*)*s273)->s354() = regex_replace( s, rg, rep );}
inline void s356::s1336( s480** s273, size_t s495 ){
( (s1281*)s691 )->s317() = DR->to_bytes();}
inline void s356::s409( s480** s273, size_t s495 ){
s356* ps = (s356*)DR;
wstring sv = ps->s317();
assert( !sv.empty() );
int s162;
wsmatch s1066;
static wregex s2069( LR"regex(^\w*(\d+)\w*$)regex" );
static wregex s2068( LR"regex(^\w*([[:alnum:]]+)\:(\d+)\w*$)regex" );
if( regex_match( sv, s1066, s2069 ) ) {
s162 = (int)*DR;}
else if( regex_match( sv, s1066, s2068 ) ) {
wstring snum = s1066[1].str();
wstring s2070 = s1066[2].str();
int base = std::stoi( s2070, NULL, 10 );
s162 = std::stoi( snum, NULL, base );}
else
throw new s16( L"string cannot be converted to int: " + sv );
*( (s343*)s691 )->s354() = s162;}
void s356::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " 
<< (s346.size() ? s346 : L"\"\"") ;}
size_t s356::s319() const{
return hash<wstring>{}(s346);}
bool s356::operator==( const s480* p ) const{
return ( (s356*)p )->s346 == s346;}
bool s356::operator<( const s480* p ) const{
return s346 < ( (s356*)p )->s346;}
Iterator* s356::s1154( const s480* idx ){
s1564::iterator it;
int i = (int)*idx;
if( i >= (int)s346.size() )
it = s346.end();
else {
if( i < 0 ) {
i = (int)s346.size() + i;
if( i < 0 )
i = 0;}
it = s346.begin() + i;}
return new s1565( s299, this, it, it == s346.end() ? it : it + 1 );}
Iterator* s356::s1173( const s480* _val ){
for( auto it = begin( s346 ); it != end( s346 ); ++it )
if( *it == *( (s1284*)_val )->s354() )
return new s1565( s299, this, it, it + 1 );
return new s1565( s299, this, end( s346 ), end( s346 ) );}
s480* s356::s1180( Iterator* it ){
size_t n = std::distance( begin( s346 ), ( (s1565*)it )->s1135() );
return new s343( s299, (int)n );}
Iterator* s356::s1175() {
if( s346.size() )
return new s1565( s299, this, s346.begin(), s346.begin() + 1 ); 
return new s1565( s299, this, s346.end(), s346.end() );}
Iterator* s356::s1179() {
return new s1565( s299, this, s346.end(), s346.end() ); }
Iterator* s356::s311( s382* rv, bool s2295 ){
if( !rv ) {
if( !s2295 )
return new s1565( s299, this, begin( s346 ), end( s346 ) );
else
return new s1565( s299, this, rbegin( s346 ), rend( s346 ) );}
s1134 pr = rv->s1184( this );
return new s1565( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
vector<wstring> s947( { L"from:", L"to:", L"first:", L"last:", L"before:", L"after:" } );
s810::s810( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s752, s694, true,
false ){
TDException s960( s7::s1099, s924, s694 );
if( l.empty() )
throw s960.s992( L"too few arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.String;
s588::s1231( ( vector<s270*>& )l, s947 );}
s810::s810( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s752, NULL, true,
false ){
s490 = Types.String;}
void s810::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
wstring s689 = L"Invalid parameters of 'substr' function: ";
if( s273[0]->s349() != Types.String )
throw new s16( s689 + L"The first parameter is not of String type." );
str = s273[0].s15<s356*>();
size_t s719 = 1;
int s770 = 0;
s735 s759 = s712;
s713 =	nTo = 1;
s786 = s733 = 0;
while( s719 < s273.size() ) {
s482 par_ = s273[s719];
s469 pc = par_->s491();
if(	pc == s472 || pc == s1055 || pc == s471 || pc == s473 ) {
s482 par;
s486 rf;
if( pc == s472 ) {
rf = par_.s15<s368*>();
par = (s270*)rf->s375();}
else if( pc == s1055 ) {
rf = par_.s15<s368*>();
par = par_;}
else
par = par_;
if( par->s349() == Types.No ) {
if( rf->Id() == s1216 ) {
if( s770 != 0 )
throw new s16( s689 + L"'from' is misplaced." );
s770 = 1;
s759 = s757;}
else if( rf->Id() == s1223 ) {
if( s770 != 0 )
throw new s16( s689 + L"'to' is misplaced." );
s770 = 1;
s759 = s809;}
else if( rf->Id() == s1209 ) {
if( s759 != s712 && s770 >= 2 )
throw new s16( s689 + L"'before' is misplaced." );
if( s759 == s809 )
s733 = -1;
else
s786 = -1;
s770 = 2;}
else if( rf->Id() == s1205 ) {
if( s759 != s712 && s770 >= 2 )
throw new s16( s689 + L"'after' is misplaced." );
if( s759 == s809 )
s733 = 1;
else
s786 = 1;
s770 = 2;}
else if( rf->Id() == s1215 ) {
if( s759 != s712 && s770 >= 3 )
throw new s16( s689 + L"'first' is misplaced." );
s770 = 3;}
else if( rf->Id() == s1219 ) {
if( s759 != s712 && s770 >= 3 )
throw new s16( s689 + L"'last' is misplaced." );
if( s759 == s809 )
nTo = string::npos;
else
s713 = string::npos;
s770 = 3;}
else
throw new s16( s689 + L"unknown parameter '" + rf->s614() + L"'." );}
else if( par->s349() == Types.String ) {
if( s759 == s757 )
s801 = par;
else if( s759 == s809 )
s794 = par;
else {
if( s801.s13() && s756.s13() )
s801 = par;
else if( s794.s13() && s716.s13() )
s794 = par;
else
throw new s16( s689 + L"unknown parameter '" + rf->s614() + L"'." );}
s770 = 0; s759 = (( s759 == s757 || s759 == s712 ) ? s809 : s757 );}
else if( par->s349() == s1141 ) {
if( s759 == s757 )
s756 = par;
else if( s759 == s809 )
s716 = par;
else {
if( s801.s13() && s756.s13() )
s756 = par;
else if( s794.s13() && s716.s13() )
s716 = par;
else
throw new s16( s689 + L"unknown parameter '" + rf->s614() + L"'." );}
s770 = 0; s759 = ( ( s759 == s757 || s759 == s712 ) ? s809 : s757 );}}
s719++;}
s1251();}
s483 s810::s494( s480** s686, size_t s690 ){
size_t s191 = 0, s678 = string::npos;
wstring s754, s718;
wstring dom = str->s494( 0, 0 )->to_wstring();
if( s756.s14() ) {
s469 pc = s756->s491();
if( pc == s472 || pc == s1326 )
s191 = (size_t)(int)*s756.s15<s368*>()->s374();
else if( s756->s491() == s473 )
s191 = (size_t)(int)*s756->s494( 0, 0 );
else
s191 = (size_t)(int)*s756.s15<s343*>();}
else if( s801.s14() ) {
s754 = s801->to_wstring();
if( s713 == 1 )
s191 = dom.find( s754 );
else if( s713 == string::npos )
s191 = dom.rfind( s754 );
else
throw new s16( L"substr: nFrom =" + std::to_wstring( s713 ) );
if( s191 != string::npos ) {
if( s786 > 0 )
s191 += s754.size();
else
s191 += s786;}}
if( s716.s14() ) {
s469 pc = s716->s491();
if( pc == s472 || pc == s1326 )
s678 = (size_t)(int)*s716.s15<s368*>()->s374();
else if( s716->s491() == s473 )
s678 = (size_t)(int)*s716->s494( 0, 0 );
else
s678 = (size_t)(int)*s716.s15<s343*>();}
else if( s794.s14() ){
s718 = s794->to_wstring();
if( nTo == 1 )
s678 = dom.find( s718, s191 + 1 );
else if( nTo == string::npos )
s678 = dom.rfind( s718 );
else
throw new s16( L"substr: nTo =" + std::to_wstring( s713 ) );
if( s678 != string::npos )
s678 += s733;}
wstring s152;
if( s191 == string::npos || s191 >= s678 || s191 >= dom.size() )
s152 = L"";
else
s152 = dom.substr( s191, s678 - s191 );
s583 = new s356( s299, s152, this );
return s583;}
s270* s810::s332( s588* s2041, s271* impl ) const{
return new s810( *this );}
s382::s382( s261* s299 )
: s323( s299, NULL, NULL ), s970( false ), s971( false ), s980( 0 )//, s877( false )
{
s490 = Types.Range;
s1232 = new s1517( s299, 0, NULL );
s1233 = new s1517( s299, U64_MAX );
s1165 = new s1517( s299, 0, NULL );}
s382::s382( s261* s299, s323* s585, Iterator* it )
: s323( s299, NULL, NULL ), s977( s585 ), s1454( it ), s970( false ), s971( false ), 
s980( 0 ){
s490 = s1403;}
s382::s382( uint64_t _beg, uint64_t _end )
: s323( NULL, NULL, NULL ), s970( false ), s971( false ), s980( 0 )//, s877( false )
{
s1232 = new s1517( s299, _beg );
s1233 = new s1517( s299, _end );
s490 = s1403;
s1165 = new s1517( s299, 0, NULL );}
s382::s382( s261* s299, const wstring& s77, const s262* ast_ )
: s323( s299, NULL, ast_ ), s970( false ), s971( false ), s980( 0 )//, s877( false )
{}
s382::s382( const s382& r, const s262* ast_ )
: s323( r.s299, r.ns, ast_ ), s970( false ), 
s971( false ), s980( r.s980 ), s1165( r.s1165 )//, s877( r.s877 )
{
s490 = r.s490;}
vector<wstring> s942( { L"i:", L"v:", L"from:", L"to:", L"where:", L"do:", L"in:" } );
s382::s382( s261* s299, s271* s589, const vector<s270*>& l_, const s262* ast_ )
: s323( s299, s589, ast_ ), s970( false ), s971( false ), s980( 0 ), 
s1165( new s1517( s299, 0, NULL ) )//, s877( false )
{
s490 = s1403;
if( l_.empty() )
return;
TDException s960( s7::s1097, s925, ast_ );
if( l_.size() > 9 )
throw s960.s992( L"too many arguments" );
s588::s1231( ( vector<s270*>& )l_, s942 );
const size_t s1047 = 3;
std::vector<s270*> l( s1047 );
if( l_[0]->s491() == s1055 ) {
s368* rf = (s368*)l_[0];
if( rf->Id() == s1218 ) {
l[0] = l_[1];
if( l_.size() == 3 ) {
l[1] = new s1517( s299, 0, NULL );
l[2] = l_[2];}
else {
l[1] = l_[2];
l[2] = l_[3];}}}
else if( l_.size() == 1) {
l[1] = new s1517( s299, 0, NULL );
l[2] = l_[0];}
else {
l[1] = l_[0];
l[2] = l_[1];}
s585 = l[0];
s1232 = l[1];
s1233 = l[2];
if( s585.s13() ) {
s322 = Types.s1516;
s314 = Types.s1516;}
else {
s322 = 0;
s314 = 0;}
s490 = s1403;}
s382::~s382(){
s1165 = NULL;}
s480* 
s382::s351( const s262& s694, s271* s585, const wstring& s331 ) const{
wstring s = s694.s290();
wstring s344 = s350();
if( s.find( s344 ) == 0 && ( s.size() == s344.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s344.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s689 = L"Malformed Range definition: " + s;
vector<s270*> s698;
s270::s1322( s694, s299, s585, s331, s698 );
return new s382( s299, s585, s698, &s694 );}
else
return NULL;}
void s382::s497( const s271* s872, bool ){
TDException s960( s7::s912, s925, s600(), L"wrong Range definition" );
ns = (s271*)s872;
bool s1158 = false;
try {
if( s585.s14() ) {
if( s585->s491() == s472 ) {
s585.s15<s368*>()->s497( s872 );
s1158 = s585->s1193();
s977 = (s323*)s585.s15<s368*>()->s374();}
else if( s585->s491() == s474 ) {
s482 tmp = s270::s1010( s299, s585, (s271*)s872, (s588*)s872, s872->s297(), false );
s585 = tmp;
s977 = (s323*)s585->s493();}
else {
s977 = (s323*)s270::s1010( s299, s585, (s271*)s872, (s588*)s872, s872->s297(), false );}
s322 = s977->ValType();
s314 = s977->s316();}
if( s1232.s14() ) {
if( s1232->s491() == s472 )
s1232.s15<s368*>()->s497( s872 );
else {
s482 tmp = s270::s1010( s299, s1232, (s271*)s872, (s588*)s872, s872->s297(), false );
s1232 = tmp;}}
else
s1232 = s362.s15<s481*>();
if( s1233.s14() ) {
if( s1233->s491() == s472 )
s1233.s15<s368*>()->s497( s872, false );
else {
s482 tmp = s270::s1010( s299, s1233, (s271*)s872, (s588*)s872, s872->s297(), false );
s1233 = tmp;}}
else
s1233 = s362.s15<s481*>();}
catch( s16* e ) {
throw e->s30( L"while compiling Range: '" + s600()->Src() + L"'" );}
s1251();
s1249( s1158 );}
void s382::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s382::s1226, s1403,
{ s1112( { s1500::s1537 } ), s1112( { s1500::s1537, s1500::s1537 } ),
s1112( { s1500::s1495, s1141 } ),
s1112( { s1500::s1495, s1141, s1141 } ) }, 1, 3, true ) ) );
s345.insert( make_pair( L"size", new s334( L"size", NULL, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"max-element", new s334( L"resize", NULL, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", NULL, s1142,
{ s1112() }, 0, 0, false ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s382::s395, s1138,
{ s1112( { s1500::s1495 } ) }, 1, 1, true ) ) );
s345.insert( make_pair( L"reverse", new s334( L"reverse", NULL, s1142,
{ s1112() }, 0, 0, false ) ) );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s1132 s382::s1187( const std::wstring& s340 ) const{
if( s340 == s7::s1345 || s340 == L"eq" )
return s333::s1187( s340 );
if( s977.s14() ) 
return s977->s1187( s340 );
return s1132();}
s1132 s382::s1182( const std::wstring& s340, s1112& ap ) const{
if( s340 == s7::s1345 || s340 == L"eq" )
return s333::s1182( s340, ap );
if( s977.s14() )
return s977->s1182( s340, ap );
assert( 0 );
throw;}
s1132 s382::s1177( const std::wstring& s340,
s1112& ap ) {
if( s340 == s7::s1345 )
return s333::s1177( s340, ap );
if( s977.s14() )
return s977->s1177( s340, ap );
assert( 0 );
throw;}
s1053 s382::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == s7::s1345 ) {
s680 = s1500::s1495;}
else if( s977.s14() )
return s977->s1178( s1540, l );
return s680;}
const vector<wstring>&
s382::s1181( const wstring& s340 ) const{
if( s340 == s7::s1345 || s977.s13() )
return s333::s1181( s340 );
else
return s977->s1181( s340 );}
s480* s382::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s382( s299, s585, l, ast_ );}
inline bool
s382::s498( const s480* s499 ) const{
if( s499->s349() != s349() ) {
return s299->TR().s1453( s499->s349(), s1500::s1495 );}
return true;}
size_t s382::s1128() const{
if( s977.s14() )
return s977->s1128();
else
return 0;}
s1134 s382::s1184(){
Iterator *fir = NULL, *sec = NULL;
if( s977.s14() ) {
if( s970 )
fir = s977->s1173( s1232.s15<s480*>() );
else if( s1232 == s1509 )
fir = s977->s1179();
else
fir = s977->s1154( s1232.s15<s480*>() );
if( s971 )
sec = s977->s1173( s1233.s15<s480*>() );
else if( s1233 == s1509 )
sec = s977->s1179();
else
sec = s977->s1154( s1233.s15<s480*>() );
if( s977->s1128() >= 1 && ( s1232 == s1509 || sec->operator<( fir ) ) ) {
( (s1115*)fir )->reverse();
( (s1115*)sec )->reverse();}}
return s1134( fir, sec );}
s1134 s382::s1184( s323* s589 ){
Iterator *fir, *sec;
if( s970 )
fir = s589->s1173( s1232.s15<s480*>() );
else if( s1232 == s1509 )
fir = s589->s1179();
else 
fir = s589->s1154( s1232.s15<s480*>() );
if( s971 )
sec = s589->s1173( s1233.s15<s480*>() );
else if( s1233 == s1509 )
sec = s589->s1179();
else
sec = s589->s1154( s1233.s15<s480*>() );
if( s589->s1128() >= 1 && ( s1232 == s1509 || sec->operator<( fir ) ) ){
( (s1115*)fir )->reverse();
( (s1115*)sec )->reverse();}
return s1134( fir, sec );}
inline void s382::s1226( s480** s273, size_t s495 ){
s382* r = ( (s382*)s273[1] );
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 ) 
{ return v.push_back( (s270*) s346 ); } );
s382* s1458 = new s382( r->s299, r->ns, v );
s1458->s497( r->ns );
*s273 = (s480*)s1458;}
inline void s382::s395( s480** s273, size_t s495 ){
Iterator* it = ( (s382*)s273[1] )->s311( NULL );
Iterator* it1;
if( s273[2]->s349() == s1403 )
it1 = ( (s382*)s273[2] )->s311( NULL );
else
it1 = ( (s323*)s273[2] )->s311( NULL );
bool s680 = true;
while( 1 ) {
s482 p = it->s312();
s482 p1 = it1->s312();
if( p.s13() ) {
if( p1.s14() )
s680 = false;
break;}
if( p1.s13() ) {
s680 = false;
break;}
if( !p.s15<s480*>()->operator==( p1.s15<s480*>() ) ) {
s680 = false;
break;}}
*( (s357*)(s481*)*s273 )->s354() = s680;}
s270* s382::s332( s588* s2041, s271* impl ) const{
return new s382( *this );}
void s382::s353( s270* p ) const{
p = new s382( *this );}
size_t s382::s319() const{
return (size_t)this;}
bool s382::operator==( const s480* p ) const{
return ( this == p );}
bool s382::operator<( const s480* p ) const{
return false;}
bool s382::s1963() const{
return s980 == s1534;}
Iterator* s382::s311( s382* r, bool s2295 ){
if( s1232.s14() ) {
s469 pc = s1232->s491();
if( pc == s473 )
s1530 = s1232->s494( 0, 0 );
else if( pc == s472 )
s1530 = s1232.s15<s368*>()->s374();
else
s1530 = s1232.s15<s480*>();}
if( s1233.s14() ) {
s469 pc = s1233->s491();
if( pc == s473 )
s1531 = s1233->s494( 0, 0 );
else if( pc == s472 )
s1531 = s1233.s15<s368*>()->s374();
else
s1531 = s1233.s15<s480*>();}
if( s977.s14() )
return s977->s311( this, s2295 );
s980 = U64_MAX;//( std::numeric_limits<int>::max )( );// (int)*s1232.s15<s480*>();
return this;}
s270* s382::s312(){
if( s980 == U64_MAX ) {
if( s1530.s14() ) {
if( s1530->s349() == s1515 )
s980 = *s1530.s15<s1517*>()->s354();
else {
s1292 tmp;
s1530->s353( &tmp );
if( *tmp.s354() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s980 = *tmp.s354();}}
if( s1531.s14() ) {
if( s1531->s349() == s1515 )
s1534 = *s1530.s15<s1517*>()->s354();
else {
s1292 tmp;
s1531->s353( &tmp );
if( *tmp.s354() < 0 )
throw new s16( L"relative indices are not allowed for a range of natural numbers" );
s1534 = *tmp.s354();}}
if( s980 > s1534 )
incr = -1;
else
incr = 1;}
else
s980 += incr;
if( s980 == s1534 ) {
s980 = U64_MAX;
return NULL;}
*s1165->s354() = s980;
return s1165;}
s270* s382::s954(){
return s315->s954();}
const s270* s382::s954() const{
return NULL;}
s270* s382::Idx(){
return NULL;}
s270* s382::El(){
return NULL;}
void s382::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Range :: " << L" curit: " << s315 << endl;}
wstring s382::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[";
if( s615() == s7::s861 )
s680 += L"_not_set_";
else {
Iterator* it = ((s382*)this)->s311( NULL );
bool b = false;
while( 1 ) {
s482 p = it->s312();
if( p.s13() )
break;
if( b ) s680 += L", ";
else b = true;
s680 += p->to_wstring();}}
s680 += L"]";
return s680;}
vector<wstring> s1125( { L"i:", L"v:", L"from:", L"to:", L"where:", L"apply:", L"in:" } );
s1124::s1124( s261* s299, const wstring& s77, const s262* ast_ )
: s323( s299, NULL, ast_ ), s979( new s368( s7::s1362, s299, s472 ) ), s980(NULL), s346( new s343( s299, 0 )), 
s680( new s343( s299, 0 )),s1342(0){
s490 = Types.Filter;}
s1124::s1124( const s1124& r, const s262* ast_ )
: s323( r.s299, r.ns, ast_ ), s979( new s368( s7::s1362, s299, s472 ) ), s980(NULL), s346( new s343( s299, 0 ) ),
s680( new s343( s299, 0 ) ), s1342(r.s1342){
*s346->s354() = (int)*r.s346;
*s680->s354() = (int)*r.s680;
ns = r.ns;
s490 = r.s490;}
s1053 s1441( size_t& idx, const vector<s270*>& l ){
if( l.size() > idx && l[idx]->s491() == s1055 )
idx++;
if( l.size() > idx )
return l[idx]->s349();
return 0;}
s1124::s1124( s261* s299, s271* s589, const vector<s270*>& l_, const s262* ast_ )
: s323( s299, s589, ast_ ), s979( new s368( s7::s1362, s299, s472 )), s980(NULL),
s346( new s343( s299, 0 ) ),	s680( new s343( s299, 0 ) ),s1342(0){
s490 = s1893;
ns = s589;
if( l_.empty() )
return;
TDException s960( s7::s1355, s925, ast_, L"wrong Filter definition" );
if( l_.size() > 6 )
throw s960.s992( L"too many arguments" );
s588::s1231( ( vector<s270*>& )l_, s1125 );
const size_t s1047 = 3;
std::vector<s270*> l( s1047 );
l[0] = l_[0];
size_t bas = 1;
if( l_[1]->s349() == s1403 ) {
range = (s382*)l_[1];
bas = 2;}
if( l_.size() == 2 + bas ) {
l[2] = l_[1 + bas];
if( l_[bas]->s491() != s1055 || ((s368*)l_[bas])->Id() != s1321 )
throw s960.s992( L"expected the 'apply:' clause" );}
else if( l_.size() == 4 + bas ) {
if( l_[bas]->s491() != s1055 || ((s368*)l_[bas])->Id() != s1225 )
throw s960.s992( L"expected the 'where:' clause" );
if( l_[bas+2]->s491() != s1055 || ((s368*)l_[bas+2])->Id() != s1321 )
throw s960.s992( L"expected the 'apply:' clause" );
l[1] = l_[1 + bas];
l[2] = l_[3 + bas];}
s585 = l[0];
where = l[1];
s1062 = l[2];}
s480* 
s1124::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
wstring s = s694.s290();
wstring s344 = s350();
if( s.find( s344 ) == 0 && ( s.size() == s344.size() || s[s.size() - 1] == L')' ) ) {
s482 fi = new s343( s299, 0 ), la = new s343( s299, 0 ), in = new s343( s299, 1 );
wstring sv = s4::s52( s.substr( s344.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong filter constructor syntax" );
wstring s689 = L"Malformed Filter definition: " + s;
const s262::s274& s695 = s694.s292();
size_t s690 = s695.size();
if( /*!s690 ||*/ s690 > 3 )
throw new s16( s689 );
std::vector<s270*> s273;
for( size_t n = 0; n < s690; ++n ) {
s262::s274::const_iterator it = s695.find( std::to_wstring( n ) );
s273.push_back( s270::s501( *it->second, s299, s585, s331 ) );}
return s352( s585, s273, &s694 );
if( s299->TR().s1453( s273[0]->s349(), s1500::s1495 ) )
return new s1124( s299, s585, s273 );
else
return new s943( s299, s585, s273 );}
else
return NULL;}
void s1124::s497( const s271* s872, bool ){
TDException s960( s7::s912, s925, s600(), L"wrong Filter definition");
ns = (s271*)s872;
if( s585.s13() )
return;
if( s585->s491() == s472 ) {
s486 rf = s585.s15<s368*>();
if( rf->s378().s13() )
rf->s497( s872 );
s977 = rf.s15<s368*>()->s374();}
else if( s585->s491() == s474 ) {
s482 tmp = s270::s1010( s299, s585,(s271*)s872, (s588*)s872, s872->s297(), false );
s585 = tmp;
s977 = s585->s493();}
else {
s977 = (s480*)s270::s1010( s299, s585, (s271*)s872, (s588*)s872, s872->s297(), false );}
if( !s299->TR().s1453( s977->s349(), s1500::s1495 ) )
throw s960.s992( L"the type is not rangeable: " + s977->s350() );
if( s977->s491() == s471 ) {}
else if( s977->s491() == s477 ) {}
else
throw s960.s992( L"unsupported container type" );
s979->s376( 0, s299->TR().s999( s977.s15<s323*>()->ValType() ) );
s979->s379( (s480*)this );
if( where.s14() ) {
if( where->s491() == s472 )
where.s15<s368*>()->s497( s872 );
else
where = s270::s1010( s299, where, (s271*)this, (s588*)s872, s872->s297(), false );}
if( s1062.s14() ) {
if( s1062->s491() == s472 ) {
s1062.s15<s368*>()->s497( s872 );
s322 = s1062->s493()->s349();}
else {
if( s1062->s491() != s1234 )
s1062 = s270::s1010( s299, s1062, (s271*)s872, (s588*)s872, s872->s297(), false );
s322 = s1062.s15<s831*>()->s1317();}}
if( !s322 )
s322 = s977.s15<s323*>()->ValType();
s490 = s299->TR().s1038( s806::Cont( { s1893, 1, s322, 0 }) );
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" +
s299->TR().s1341( s299->TR().s797( s322 ) ) + L">";
s1342 = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s1251();}
void s1124::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1124::s1226, s1893,
{ s1112( { s1141, s1141 } ) }, 1, 2 ) ) );
s345.insert( make_pair( L"to-vector", new s334( L"to-vector", &s1124::s1337, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"max-element", new s334( L"resize", NULL, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", NULL, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", NULL, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"reverse", new s334( L"reverse", NULL, s1142,
{ s1112() }, 0, 0 ) ) );
s345.equal_range( s7::s1345 ).first->second->s1250( true );
s345.equal_range( L"to-vector" ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s1132 s1124::s1182( const std::wstring& s340, s1112& ap ) const{
return s333::s1182( s340, ap );
if( s340 == s7::s1345 )
return s333::s1182( s340, ap );
assert( 0 );
throw;}
s1132 s1124::s1177( const std::wstring& s340, s1112& ap ){
if( s340 == s7::s1345 ) {
auto ran = s339().equal_range( s340 );
s334* mi = ran.first->second;
s1132 s1227( s322, mi->s1126(), mi->s1193(), mi->s2001() );
return s1227;}
else if( s340 == L"to-vector" ) {
auto ran = s339().equal_range( s340 );
s334* mi = ran.first->second;
s1132 s1227( s1342, mi->s1126(), mi->s1193(), mi->s2001() );
return s1227;}
assert( 0 );
throw;}
s1053 s1124::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == s7::s1345 ) {
s680 = s1500::s1495;}
else if( s1540 == L"to-vector" ) {
s680 = s1342;}
return s680;}
s480* s1124::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s1124( s299, s585, l, ast_ );
s1053 pt = l[0]->s349();
if( s299->TR().s1453( pt, s1500::s1495 ) )
return new s1124( s299, s585, l );
s588::s1231( ( vector<s270*>& )l, s1125 );
s469 pc = l[0]->s491();
vector<s270*> s905;
size_t s372 = 0;
if( pc == s471 ) {
if( pt == s1141 ) {
if( l.size() > 1 && l[1]->s349() == s1141 ) {
s905 = { l[0], l[1] };
s372 = 1;}
else {
s905 = { l[0] };
s372 = 2;}}}
else if( pc == s1055 ) {
if( ( (s368*)l[0] )->s1293() == s1223 ) {
s905 = { l[1] };
s372 = 2;}
else if( ( (s368*)l[0] )->s1293() == s1216 ) {
s905 = { l[1], l[3] };
s372 = 4;}}
vector<s270*> l1 = { new s943( s299, s585, s905 ) };
l1.insert( l1.end(), l.begin() + s372, l.end() );
return new s1124( s299, s585, l1 );
if( l.size() ) {
if( l[0]->s491() == s472 ) {
l[0]->s497( s585 );
if( s299->TR().s1453( l[0]->s349(), s1500::s1495 )  )
return new s1124( s299, s585, l );}}
else {
return new s1124( s299, s585, l );}
return new s943( s299, s585, l );}
s480* s1124::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s1124* s680 = new s1124( s299, L"" );
s806::Cont s1065;
s488::s2103( vt, idx, s1065 );
s806 s1063( s1065[0] );
return s680;}
inline bool
s1124::s498( const s480* s499 ) const{
return ( ((s1124*)s499)->s349() == s349() );}
inline void s1124::s1226( s480** s273, size_t s495 ){
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 )
{ return v.push_back( (s270*)s346 ); } );
s1124* pf = (s1124*)s273[1];
*s273 = ( s480* ) pf->s352( pf->ns, v, pf->s600() );
s273[0]->s497( pf->ns );
pf->s979->s379( s273[0] );
pf->s980 = ((s1124*)s273[0])->s980;}
inline void s1124::s1337( s480** s273, size_t s495 ){
s1124* pf = (s1124*)s273[1];
*s273 = ( s480* ) pf->s299->TR().
s999( pf->s1342 )->s352( pf->ns );
Iterator* s1012 = pf->s311( NULL );
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
( (s313*)s273[0] )->add( p->s332(0,0) );}
s273[0]->s1251();}
s270* s1124::s332( s588* s2041, s271* impl ) const{
return new s1124( *this );}
void s1124::s353( s270* p ) const{
p = new s1124( *this );}
size_t s1124::s319() const{
return (size_t)this;}
bool s1124::operator==( const s480* p ) const{
return ( this == p );}
bool s1124::operator<( const s480* p ) const{
return false;}
bool
s1124::s553( const wstring& s671, s368* ref, const wstring& s331, bool ) const{
if( s671 == s7::s1362 ) {
ref->s1332( s979.s15<s368*>() );
return true;}
return false; // ns->s553( s671, ref, s331 );
}
s270* s1124::s595( size_t off ){
assert( off == 0 );
if( s980 )
return s980;
return (s270*) s979->s500();}
s1134 s1124::s1184(){
if( range.s14() )
return range->s1184();
else
return s977.s15<s323*>()->s1184();}
Iterator* s1124::s311( s382* r, bool s2295 ){
if( range.s14() ) {
s1134 pr = range->s1184( );
s315 = pr.first;
s1477 = pr.second;}
else {
s315 = s977.s15<s323*>()->s311( NULL, s2295 );
s1477 = NULL;}
return this;}
bool s1124::s1963() const{
if( !s980 || s315->s1963() ) //???DEBUG??? 220706
return true;
return false;}
s270* s1124::s312(){
while( 1 ) {
s980 = s315->s312();
if( !s980 && !(s1477 && s315->operator==( s1477 ) )) //???DEBUG??? 220706_1
return NULL;
if( where.s14() && ( false == (bool)*where->s494(0,0) ) )
continue;
break;}
if( s1062.s14() )
return s1062->s494( 0, 0 ).s15<s481*>();
else
return s980;}
s270* s1124::s954(){
return s315->s954();}
const s270* s1124::s954() const{
return NULL;}
s270* s1124::Idx(){
return NULL;}
s270* s1124::El(){
return NULL;}
void s1124::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Filter : " << endl <<
s4::fill_n_ch( L' ', s196 ) << L"Input: ";
if( s585.s14() ) {
s977.s14() ? s977->s303( pd, s196 + s416 ) : s585->s303( pd, s196 + s416 );}
buf << s4::fill_n_ch( L' ', s196 ) << L"Do: ";
if( s1062.s14() ) s1062->s303( pd, s196 + s416 );
else	buf << L"None" << endl;
buf <<  s4::fill_n_ch( L' ', s196 ) << L"curitref: ";
s979->s303( pd, 0 );
buf << endl;}
s943::s943( s261* s299 ) 
: s323( s299, NULL, NULL ) {
s490 = Types.Seq;}
s943::s943( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ )
: s323( s299, s585, ast_ ), s1039( true ){
if( l.empty() )
return;
wstring s990 = L"wrong sequence generator syntax";
if( l.size() > 3 )
throw new s16( s990 + L": too many arguments" );
if( l.size() == 1 ) {
end = l[0];}
else {
start = l[0];
end = l[1];
if( l.size() == 3 )
incr = l[2];}
s490 = s1404;}
s943::~s943(){}
s480* 
s943::s351( const s262& s694, s271* s585, const wstring& s331 ) const{
wstring s = s694.s290();
wstring s344 = s350();
if( s.find( s344 ) == 0 && ( s.size() == s344.size() || s[s.size() - 1] == L')' ) ) {
wstring sv = s4::s52( s.substr( s344.size() ), s48 );
if( sv.size() && sv[0] != L'(' )
throw new s16( L"wrong range constructor syntax" );
wstring s689 = L"Malformed Sequence definition: " + s;
vector<s270*> s698;
s270::s1322( s694, s299, s585, s331, s698 );
return new s943( s299, s585, s698 );}
else
return NULL;}
s480* s943::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s943( s299, s585, l, ast_ );}
void s943::s497( const s271* s872, bool ){
if( end.s13() )
return;
wstring s990 = L"wrong sequence generator syntax";
s482 tmp = s270::s1010( s299, end, (s271*)s872, (s588*)s872, s872->s297(), false );
end = tmp;
if( start.s14() ) {
tmp = s270::s1010( s299, start, (s271*)s872, (s588*)s872, s872->s297(), false );
start = tmp;}
else {
if( end->s349() == s1141 )
start = new s343( s299, 0 );
else {
start = s299->TR().s515( end->s349(), (s271*)s872, s872->s297() );
start->s497( s872 );}}
if( incr.s14() ) {
tmp = s270::s1010( s299, incr, (s271*)s872, (s588*)s872, s872->s297(), false );
incr = tmp;}
else {
if( start->s349() == s1141 )
incr = new s343( s299, 1 );
else
throw new s16( s990 + L": increment value is missing" );}
if( start->s491() == s472 ) {
s270* p = start.s15<s368*>()->s374();
s981 = p->s332(0,0);
s1644 = p->s332(0,0);}
else {
s981 = start->s332(0,0);
s1644 = start->s332(0,0);}
std::vector<s270*> pl = { s981, incr };
s558 cs( s299, L"sumeq", pl, NULL );
s1050 = s588::s597( &cs, s299, (s271*)s872, (s588*)s872, s872->s297(), false );
s1050->s497( s872, false );
std::vector<s270*> pl1 = { s981, start };
s558 cs1( s299, L"set", pl1, NULL );
set = s588::s597( &cs1, s299, (s271*)s872, (s588*)s872, s872->s297(), false );
set->s497( s872, false );
std::vector<s270*> pl2 = { s981, end };
s558 cs2( s299, L"less", pl2, NULL );
eq = s588::s597( &cs2, s299, (s271*)s872, (s588*)s872, s872->s297(), false );
eq->s497( s872, false );
s1190 = s1141;
s322 = start->s349();
s1251();}
s1134 s943::s1184(){
s1::s1278<Iterator> it = this;
s1::s1278<Iterator> it1 = it;
return make_pair( it, it1 );}
bool s943::s1963() const{
if( (bool)*eq.s15<s588*>()->s494( 0, 0 ) )
return true;
return false;}
Iterator* s943::s311( s382* r, bool s2295 ){
assert( !s2295 );
set->s494( 0, 0 );
s1039 = true;
return this;}
s270* s943::s312(){
if( s1039 )
s1039 = false;
else
s1050->s494( 0, 0 );
if(! (bool)*eq->s494( 0, 0 ) )
return NULL;
s981.s15<s480*>()->s353( s1644 );
s1644->s1251();
return s1644;}
void s943::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s943::s1226, s1404,
{ s1112( { s1141 } ), s1112( { s1141, s1141 } ), s1112( { s1141, s1141, s1141 } ) }, 
1, 2 ) ) );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s270* s943::Idx(){
return s1644; }
bool s943::operator==( const Iterator* p ) const{
return false;}
bool s943::operator<( const Iterator* p ) const{
return this < p;}
inline void s943::s1226( s480** s273, size_t s495 ){
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 )
{ return v.push_back( (s270*)s346 ); } );
*s273 = ( s480* ) new s943( ( (s943*)s273[1] )->s299, NULL, v );
s273[0]->s497( ((s943*)s273[1])->ns );}
s270* s943::s332( s588* s2041, s271* impl ) const{
return new s943( *this );}
void s943::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"SequenceGenerator : " << endl;
start->s303( pd, s196 + s416); buf << L", "; end->s303( pd, 0); 
buf << L", "; incr->s303( pd, 0 );}
s1053 s1500::s1495 = 0;
s1053 s1500::s1494 = 0;
s1053 s1500::s1496 = 0;
bool _cmp( const s482& l_, const s482& r_ ){
s480* l = l_.s15<s480*>();
s480* r = r_.s15<s480*>();
return  l->operator<( r );}
struct _containerSortComp1{
bool operator()( const s482 l, const s482 r ) const{
return l.s15<s480*>()->operator<( r.s15<s480*>() );}
};
struct s1146{
std::vector<s482>s854;
s485 s852;
s1146( /*s485 s853*/ ) : s852( /*s853*/0 ) { s854.resize( 2 ); }
bool operator()( const s482& l, const s482& r ){
if( s852.s14() ) {
s854[0] = l;
s854[1] = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l.s15<s480*>()->operator<( r.s15<s480*>() );}
};
Iterator* s323::s1154( const s480* idx ){
throw new s16( L"this iterable type doesn't support access by index" );}
Iterator* s323::s1173( const s480* idx ){
throw new s16( L"this iterable type doesn't support search for value" );}
Iterator* s323::s1228( const s480* idx ){
throw new s16( L"this iterable type doesn't support distancing between elements" );}
s480* s323::s1180( Iterator* ){
throw new s16( L"this iterable type doesn't support indexing" );}
struct s833;
s480* s323::sort( bool, s833* ){
throw new s16( L"not implemented", (uint32_t) s16::s17::s868 );}
template <class _Cont, class s1300, class Der>
s310<_Cont, s1300, Der>::s310( const s1160& r )
: s323( r ){}
void s1151( s261* s299, const wstring& s77, wstring& s1262, wstring& s641 ){
assert( !s77.empty() );
wsmatch s1066;
wregex s1244( LR"regex(^(\w+(?:<.*>)?)\s*\(\s*(\d*)\s*\)\s*$)regex" );
if( regex_match( s77, s1066, s1244 ) ) {
s1262 = s1066[1].str();
s641 = L"] " + 
( s1066[s1066.size()-1].str().empty() ? L"0" : s1066[s1066.size()-1].str() );}
else {
size_t s2256 = s77.find( L"(" );
size_t s2255 = s77.find( L"<" );
if( s2255 < s2256 ) {
size_t pl = s77.find( L">(" );
s1262 = s77.substr( 0, pl + 1 );
s641 = s4::s52( s77.substr( pl + 2, s77.size() - pl - 3 ), 
s4::s48 );}
else {
s1262 = s77.substr( 0, s2256 );
s641 = s4::s52( s77.substr( s2256 + 1, s77.size() - s2256 - 2 ), 
s4::s48 );}}
return;
assert( !s77.empty() );
wstring sv = s77;
wsmatch /*s1066,*/ rgres1;
wregex s1245( LR"regex(^(\w+(?:<[^\(]*>)?)\s*\(\s*([\w\W]*?)\s*\)\s*$)regex" );
if( sv.size() && regex_match( sv, s1066, s1245 ) ) {
s806::Cont vt;
s1262 = s1066[1].str();
if( regex_match( sv, rgres1, s1244 ) ) {
s641 = L"] " + //s1262 + L" " +
( s1066[s1066.size()-1].str().empty() ? L"0" : s1066[s1066.size()-1].str() );}
else {
s641 = s1066[2];}}}
s1133::s1133( s261* s299, s1889& s77, const s262* ast_ )
: s333( s299, NULL, ast_ ), s314( 0 ), s322( 0 ){
s490 = Types.Position;
s1664( s7::s861 );}
s1133::s1133( const s1133& right, const s262* ast_ )
: s333( right.s299, right.ns, ast_ ), s585( right.s585 ), s346( right.s346 ),
s314( right.s314 ), s322( right.s322 ){
s490 = right.s490;
s1251();}
s1133::s1133( s261* s299, s271* s585, Iterator* it, const s262* ast_ )
: s333( s299, NULL, ast_ ), s346( it ), s314(0), s322( 0 ){
s490 = Types.Position;
s1251();}
s480* s1133::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
wstring s344 = s350();
if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
wstring sv = s4::s52( s.substr( s344.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong Position constructor syntax" );
wstring s689 = L"Malformed Position declaration: " + s;
const s262::s274& s695 = s694.s292();
size_t s690 = s695.size();
if( s690 )
throw new s16( s689 );
return s352( s585, vector<s270*>(), &s694 );}
else
return NULL;}
void s1133::s497( const s271* s872, bool ){
if( s346.s14() ) {
if( !s322 ) {
s322 = s346->ValType();
s806::Cont v = { s1567, 1, s314, 0 };
s490 = s299->TR().s1038( v );
if( s490 == s1567 ) {
s806::Cont v = { s1567, 1, s314, 0 };
s490 = s299->TR().s1038( v );}}}
if( !s322 && s314 )
s322 = s299->TR().s1005( s314 ).s349( 4 );}
s1053 s1133::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get-el" )
s680 = s314;
else if( s1540 == L"get-val" )
s680 = s322;
return s680;}
s480* s1133::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s1133( s299, L"", ast_ );}
s480* s1133::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 1 );
s806::Cont s1093;
s488::s2103( vt, idx, s1093 );
s1133* s680 = new s1133( s299, 0, NULL );
s680->ns = s585;
s680->s314 = s1093[0];
s806 s616( vt );
s680->s490 = s299->TR().s1003( vt );
return s680;}
void s1133::s347(){
s345.insert( std::make_pair( L"is-end", new s334( L"is-end", &s1133::s1964, s1138,
{ s1112( {s7::s1382} ) }, 1, 1 ) ) );
s345.insert( std::make_pair( L"eq", new s334( L"eq", &s1133::s395, s1138,
{ s1112( {s7::s1382} ) }, 1, 1 ) ) );
s345.insert( std::make_pair( L"get-el", new s334( L"get-el", &s1133::s1576, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"get-val", new s334( L"get-val", &s1133::s2249, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"get-idx", new s334( L"get-idx", &s1133::s1731, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"neq", new s334( L"neq", &s1133::s400, s1138,
{ s1112( {s7::s1382} ) }, 1, 1 ) ) );
s345.insert( std::make_pair( L"set", new s334( L"set", &s1133::s384, s1142,
{ s1112( {s7::s1382} ) }, 1, 1 ) ) );
s345.equal_range( L"get-el" ).first->second->s1250( true );
s345.equal_range( L"get-val" ).first->second->s1250( true );}
s270* s1133::s332( s588* s2041, s271* impl ) const{
return new s1133( *this );}
void s1133::s353( s270* p ) const{
p = new s1133( *this );}
size_t s1133::s319() const{
return (size_t)this;}
void s1133::operator=( const s1133& p ){
s585 = p.s585;
s346 = p.s346;
s322 = p.s322;
s314 = p.s314;
s490 = p.s490;}
bool s1133::operator==( const s480* p ) const{
return s346->operator==( ((s1133*)p)->s346 );}
bool s1133::operator<( const s480* p ) const{
return s346->operator<( ((s1133*)p)->s346 );}
s1133::operator bool() const{
if( s346->s1963() )
return false;
return true;}
#undef s691
#define s691 ((s1133*)(s481*)*s273)
#define s692 ((s357*)(s481*)*s273)
inline void s1133::s1964( s480** s273, size_t s495 ){
*((s357*)*s273)->s354() = ((s1133*)DR )->s346->s1963();}
inline void s1133::s1576( s480** s273, size_t s495 ){
s480* s680 = (s480*)((s1133*)DR )->s346->El();
*s273 = s680 ? s680 : s362;}
inline void s1133::s2249( s480** s273, size_t s495 ){
*s273 = (s480*)((s1133*)DR )->s346->s954();}
inline void s1133::s1731( s480** s273, size_t s495 ){
*s273 = (s480*)((s1133*)DR )->s346->Idx();}
inline void s1133::s395( s480** s273, size_t s495 ){
*s692->s354() = ( (s1133*)DR )->s346->operator==( ( (s1133*)s273[2] )->s346 );}
inline void s1133::s400( s480** s273, size_t s495 ){
*s692->s354() = !( (s1133*)DR )->s346->operator==( ( (s1133*)s273[2] )->s346 );}
inline void s1133::s384( s480** s273, size_t s495 ){
*(s1133*)DR = *(s1133*)s273[2];}
void s1133::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Position : " <<
this << endl;}
s956::s956( s261* s299, s313* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1203( (uint64_t)-1 ), s1163( new s1517(s299, -1) ){
if( v.s14() ) {
s1203 = std::distance( v->s317().begin(), it );
assert( s1203 >= 0 );}}
s956::s956( s261* s299, s313* v_, s1236 it, s1236 sent )
: v( v_ ), s1247( it ), s1476( sent ), s1203( (uint64_t)-1 ), s1163( new s1517(s299, -1) ){
if( v.s14() ) {
s1203 = v->size() - std::distance( v->s317().rbegin(), it ) - 1;
assert( s1203 >= 0 );}
s877 = true;}
s956::s956( s956* it )
: v( it->v ), s1204( it->s1204 ), s1203( it->s1203 ), s1163( new s1517(it->s1163->Pass(), 0, NULL) ){
s877 = it->s877;}
void s956::reverse(){
s877 = true; 
s1247 = std::make_reverse_iterator( s1204 );}
s270* s956::s312(){
s270* s680 = NULL;
if( !s877 ) {
if( s1204 != s1078 ) {
s680 = *s1204;
s1204++;
s1203++;}}
else {
if( s1247 != s1476 ) {
s680 = *s1247;
s1247++;
s1203--;}}
return s680;}
s270* s956::s954(){
if( !s877 ) {
if( s1204 == v->s317().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1204;}
else {
if( s1247 == v->s317().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return *s1247;}}
const s270* s956::s954() const{
s270* s680 = ((s956*)this)->s954();
return s680;}
bool s956::s1963() const{
if( !s877 )
return s1204 == s1078;
return s1247 == s1476;
if( !s877 )
return s1204 == v->s317().end();
return s1247 == v->s317().rend();}
s270* s956::Idx(){
*s1163->s354() = s1203 - 1;
return s1163;}
s270* s956::El(){
if( !s877 ) {
if( s1204 == v->s317().end() )
throw new s16( (uint32_t)s16::s17::s24 );
auto s680 = new s951( NULL, NULL, vector<s270*>( { s1163, *s1204 } ) );
s680->s1664( s7::s860 );
return s680;}
else {
if( s1247 == v->s317().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
auto s680 = new s951( NULL, NULL, vector<s270*>( { s1163, *s1247 } ) );
s680->s1664( s7::s860 );
return s680;}}
s1053 s956::ValType() const{
return v->ValType();}
bool s956::operator==( const Iterator* r ) const{
if( !s877 ) {
return s1204 == ( (s956*)r )->s1204;}
else {
return s1247 == ( (s956*)r )->s1247;}}
bool s956::operator<( const Iterator* r ) const{
if( !s877 ) {
if( s1204 == v->s317().end() )
return false;
return s1204 < ( (s956*)r )->s1204;}
else {
if( s1247 == v->s317().rend() )
return false;
return s1247 < ( (s956*)r )->s1247;}}
s953::s953( s261* s299, 
s743* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1203( (uint64_t)-1 ), s1163( new s1517( s299, 0, NULL ) ){
if( v.s14() ) {
s1203 = std::distance( v->s317().begin(), it );
assert( s1203 >= 0 );}}
s953::s953( s953* it )
: v( it->v ), s1204( it->s1204 ), s1203( it->s1203 ), s1163( new s1517( it->s1163->Pass(), 0, NULL ) ){}
bool s953::s1963() const{
return s1204 == v->s317().end();}
s270* s953::s312(){
s270* s680 = NULL;
if( s1204 != v->s317().end() ) {
s680 = *s1204;
++s1204;
++s1203;}
return s680;}
s270* s953::s954(){
return *s1204;}
const s270* s953::s954() const{
return *s1204;}
s270* s953::Idx(){
*s1163->s354() = s1203 - 1;
return s1163;}
s270* s953::El(){
*s1163->s354() = s1203 - 1;
return s1163;}
s1053 s953::ValType() const{
return v->ValType();}
s931::s931( s261* s299, s321* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1163( s362 ), s1162( new s951( s299, NULL,
vector<s270*>(	{ 
s299->TR().s515( v_->s930(), s299, v_->s2153() ),
s299->TR().s515( v_->ValType(), s299, v_->s2153() )
} ) ) ){
s1162->s497( s299, true );}
s931::s931( s261* s299, s321* v_, s1236 it, s1236 sent )
: v( v_ ), s1247( it ), s1476( sent ), s1163( s362 ), s1162( new s951( s299, NULL,
vector<s270*>(	{ 
s299->TR().s515( v_->s930(), s299, v_->s2153() ),
s299->TR().s515( v_->ValType(), s299, v_->s2153() )
} ) ) ){
s1162->s497( s299, true );
s877 = true;}
s931::s931( s931* it )
: v( it->v ), s1204( it->s1204 ), s1163( s362 ), s1162( new s951( it->s1162->Pass(), NULL,
vector<s270*>(	{ 
s1204->first->s500()->s352( it->s1162->Pass() ),
s1204->second->s500()->s352( it->s1162->Pass() ) } ) ) ) // ???DEBUG??? 220514
{
s1162->s497( it->s1162->Pass(), true );}
bool s931::s1963() const{
if( !s877 )
return s1204 == v->s317().end();
return s1247 == v->s317().rend();}
s270* s931::s312(){
s270* s680 = NULL;
if( !s877 ) {
if( s1204 != s1078 ) {
s680 = El(); 
++s1204;}}
else {
if( s1247 != s1476 ) {
s680 = El(); 
++s1247;}}
return s680;}
s270* s931::s954(){
return (*s1204).second.s15<s481*>();}
const s270* s931::s954() const{
return (*s1204).second.s15<s481*>();}
s270* s931::Idx(){
return s1162->s317().at(0).s15<s481*>(); // ???DEBUG??? 220514
}
s270* s931::El(){
s270* s680 = NULL;
if( !s877 ) {
if( s1204 != v->s317().end() ) {
s1162->assign( vector<s482>(
{ ( *s1204 ).first.s15<s270*>(),( *s1204 ).second.s15<s270*>() } ));
s680 = s1162; }}
else{
if( s1247 != v->s317().rend() ) {
s1162->assign( vector<s482>(
{ ( *s1247 ).first.s15<s270*>(),( *s1247 ).second.s15<s270*>() } ));
s680 = s1162; }}
return s680;}
void s931::reverse(){
s877 = true;
s1247 = std::make_reverse_iterator( s1204 );
s1476 = std::make_reverse_iterator( s1078 );}
s1053 s931::s316() const{
return v->s316();}
s1053 s931::ValType() const{
return v->ValType();}
bool s931::operator==( const Iterator* r ) const{
if( !s877 )
return s1204 == ( (s931*)r )->s1204;
else
return s1247 == ( (s931*)r )->s1247;}
s1371::s1371( s261* s299, s1370* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1163( s362 ), s1162( new s951( s299, NULL,
vector<s270*>( {
s299->TR().s515( v_->s930(), s299, v_->s2153() ),
s299->TR().s515( v_->ValType(), s299, v_->s2153() )
} ) ) ){
s1162->s497( s299, true );}
s1371::s1371( s1371* it )
: v( it->v ), s1204( it->s1204 ), s1163( s362 ), s1162( new s951( it->s1162->Pass(), NULL,
vector<s270*>( {
s1204->first->s500()->s352( it->s1162->Pass() ),
s1204->second->s500()->s352( it->s1162->Pass() ) } ) ) ){
s1162->s497( it->s1162->Pass(), true );}
bool s1371::s1963() const{
return s1204 == v->s317().end();}
s270* s1371::s312(){
s270* s680 = NULL;
if( s1204 != s1078 ) {
s680 = El();
++s1204;}
return s680;}
s270* s1371::s954(){
return ( *s1204 ).second.s15<s481*>();}
const s270* s1371::s954() const{
return ( *s1204 ).second.s15<s481*>();}
s270* s1371::Idx(){
return s1162->s317().at( 0 ).s15<s481*>(); // ???DEBUG??? 220514
}
s270* s1371::El(){
s270* s680 = NULL;
if( s1204 != v->s317().end() ) {
s1162->assign( vector<s482>(
{ ( *s1204 ).first.s15<s270*>(),( *s1204 ).second.s15<s270*>() } ) );
s680 = s1162;}
return s680;}
s1053 s1371::s316() const{
return v->s316();}
s1053 s1371::ValType() const{
return v->ValType();}
bool s1371::operator==( const Iterator* r ) const{
return s1204 == ( (s1371*)r )->s1204;}
s2204::s2204( s261* s299, s2203* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ){}
s2204::s2204( s261* s299, s2203* v_, s1236 it, s1236 sent )
: v( v_ ), s1247( it ), s1476( sent ){}
s2204::s2204( s2204* it )
: v( it->v ), s1204( it->s1204 ){}
bool s2204::s1963() const{
if( !s877 )
return s1204 == v->s317().end();
return s1247 == v->s317().rend();}
s270* s2204::s312(){
s270* s680 = NULL;
if( s1204 != s1078 ) {
s680 = El(); // ???DEBUG??? 220514
++s1204;}
return s680;}
s270* s2204::s954(){
return El();}
const s270* s2204::s954() const{
return ((s2204*)this)->El();}
s270* s2204::Idx(){
throw new s16( L"container is not indexable" );}
s270* s2204::El(){
if( !s877 ) {
if( s1204 == v->s317().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1204->s15<s270*>();}
else {
if( s1247 == v->s317().rend() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1247->s15<s270*>();}}
void s2204::reverse(){
s877 = true;
s1247 = std::make_reverse_iterator( s1204 );}
s1053 s2204::ValType() const{
return v->ValType();}
bool s2204::operator==( const Iterator* r ) const{
if( !s877 )
return s1204 == ( (s2204*)r )->s1204;
else
return s1247 == ( (s2204*)r )->s1247;}
s2237::s2237( s261* s299, s2236* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ){}
s2237::s2237( s2237* it )
: v( it->v ), s1204( it->s1204 ){}
bool s2237::s1963() const{
return s1204 == v->s317().end();}
s270* s2237::s312(){
s270* s680 = NULL;
if( s1204 != s1078 ) {
s680 = El(); // ???DEBUG??? 220514
++s1204;}
return s680;}
s270* s2237::s954(){
return El();}
const s270* s2237::s954() const{
return ( (s2237*)this )->El();}
s270* s2237::Idx(){
throw new s16( L"container is not indexable" );}
s270* s2237::El(){
if( s1204 == v->s317().end() )
throw new s16( (uint32_t)s16::s17::s24 );
return s1204->s15<s270*>();}
s1053 s2237::ValType() const{
return v->ValType();}
bool s2237::operator==( const Iterator* r ) const{
return s1204 == ( (s2237*)r )->s1204;}
s1282::s1282( s261* s299, s1281* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1203( (uint64_t)-1 ), s1163( new s1517( s299, -1 ) ),
s1162( new s951( NULL, NULL, vector<s270*>( { s1163, (s270*)Types( s299, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1203 = std::distance( v->s317().begin(), it );
assert( s1203 >= 0 );}}
s1282::s1282( s261* s299, s1281* v_, s1236 it, s1236 sent )
: v( v_ ), s1247( it ), s1476( sent ), s1203( (uint64_t)-1 ), s1163( new s1517( s299, -1 ) ),
s1162( new s951( NULL, NULL, vector<s270*>( { s1163, (s270*)Types( s299, Types.Byte ) } ) ) ){
if( v.s14() ) {
s1203 = v->size() - std::distance( v->s317().rbegin(), it ) - 1;
assert( s1203 >= 0 );}
s877 = true;}
s1282::s1282( s1282* it )
: v( it->v ), s1204( it->s1204 ), s1203( it->s1203 ), s1163( new s1517( it->s1163->Pass(), 0, NULL ) ),
s1162( new s951( v->Pass(), NULL, vector<s270*>( { s1163, new s1284( NULL, *s1204)  } ) ) ){
s877 = it->s877;}
void s1282::reverse(){
s877 = true;
s1247 = std::make_reverse_iterator( s1204 );}
bool s1282::s1963() const{
if( !s877 )
return s1204 == v->s317().end();
return s1247 == v->s317().rend();}
s270* s1282::s312(){
s270* s680 = NULL;
if( !s877 ) {
if( s1203 < v->s317().size() )
s680 = new s1284( v->Pass(), v->s317()[s1203++] );}
else {
if( s1203 != U64_MAX )
s680 = new s1284( v->Pass(), v->s317()[s1203--] );}
return s680;}
s270* s1282::s954(){
return new s1284( v->Pass(), *s1204 );}
const s270* s1282::s954() const{
return new s1284( v->Pass(), *s1204 );}
s270* s1282::Idx(){
*s1163->s354() = s1203 - 1;
return s1163;}
s270* s1282::El(){
*s1163->s354() = s1203 - 1;
return s1163;}
s1053 s1282::ValType() const{
return v->ValType();}
bool s1282::operator==( const Iterator* r ) const{
if( !s877 )
return s1204 == ( (s1282*)r )->s1204;
else
return s1247 == ( (s1282*)r )->s1247;}
bool s1282::operator<( const Iterator* r ) const{
if( !s877 )
return s1204 < ( (s1282*)r )->s1204;
else
return s1247 < ( (s1282*)r )->s1247;}
s1565::s1565( s261* s299, s356* v_, s932 it, s932 sent )
: v( v_ ), s1204( it ), s1078( sent ), s1203( (uint64_t)-1 ), s1163( new s1517( s299, -1 ) ),
s1162( new s951( v->Pass(), NULL, vector<s270*>( { s1163, (s270*)Types( s299, Types.Char ) } ) ) ){
if( v.s14() ) {
s1203 = std::distance( v->s317().begin(), it );
assert( s1203 >= 0 );}}
s1565::s1565( s261* s299, s356* v_, s1236 it, s1236 sent )
: v( v_ ), s1247( it ), s1476( sent ), s1203( (uint64_t)-1 ), s1163( new s1517( s299, -1 ) ),
s1162( new s951( v->Pass(), NULL, vector<s270*>( { s1163, (s270*)Types( s299, Types.Char ) } ) ) ){
if( v.s14() ) {
s1203 = v->s317().size() - std::distance( v->s317().rbegin(), it ) - 1;
assert( s1203 >= 0 );}
s877 = true;}
s1565::s1565( s1565* it )
: v( it->v ), s1204( it->s1204 ), s1203( it->s1203 ), s1163( new s1517( it->s1163->Pass(), 0, NULL ) ),
s1162( new s951( v->Pass(), NULL, vector<s270*>( { s1163, new s1560( v->Pass(), *s1204)  } ) ) ){
s877 = it->s877;}
void s1565::reverse(){
s877 = true;
s1247 = std::make_reverse_iterator( s1204 );}
bool s1565::s1963() const{
if( !s877 )
return s1204 == v->s317().end();
return s1247 == v->s317().rend();}
s270* s1565::s312(){
s270* s680 = NULL;
if( s1204 != v->s317().end() ) {
s680 = new s1560( v->Pass(), *s1204++ );
++s1203;}
return s680;}
s270* s1565::s954(){
return new s1560( v->Pass(), *s1204 );}
const s270* s1565::s954() const{
return new s1560( v->Pass(), *s1204 );}
s270* s1565::Idx(){
*s1163->s354() = s1203 - 1;
return s1163;}
s270* s1565::El(){
auto c = new s1560( v->Pass(), *s1204 );
s1162 = new s951( v->Pass(), NULL, vector<s270*>( { s1163, c } ) );
return s1162.s15<s270*>();}
s1053 s1565::ValType() const{
return v->ValType();}
bool s1565::operator==( const Iterator* r ) const{
if( !s877 )
return s1204 == ( (s1565*)r )->s1204;
else
return s1247 == ( (s1565*)r )->s1247;}
bool s1565::operator<( const Iterator* r ) const{
if( !s877 )
return s1204 < ( (s1565*)r )->s1204;
else
return s1247 < ( (s1565*)r )->s1247;}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
vector<wstring> s1299( { L":typedTable", L":untypedTable" } );
s313::s313( s261* s299, s271* s585, const wstring& s77, const s262* ast_,
const s1680& s1744 )
: s1563( s299, s585, ast_ ){
assert( 0 );}
s313::s313( const s313& right, s271* _ns, const s262* ast_ )
: s1563( right.s299, _ns, ast_ ){
s346.resize( right.s346.size() );
for( size_t n = 0; n < right.s346.size(); ++n )
s346[n] = (s480*)right.s346[n]->s332( NULL, _ns );
s1190 = right.s1190;
s322 = right.s322;
s314 = right.s314;
s490 = right.s490;
s1664( right.s615() );}
s313::s313( s261* s299, const std::vector<s270*>& l,
s271* s585, const s262* ast_, s1053 s702,	s1053 s1265 )
: s1563( s299, s585, ast_ ){
s1190 = s1141;
s322 = s1265;
if( s322 )
s314 = s299->TR().s1038( std::vector<s1053>(
{ s1702, 2, s1190, 0, s322, 0 } ) );
if( s702 )
s490 = s702;
else
s490 = Types.Vector;
if( l.size() )
s588::s1231( ( vector<s270*>& )l, s1299 );
if( l.size() ) {
if( l[0]->s349() == s349() ||	l[0]->s349() == s1704 ) {
s346.assign( ( (s313*)l[0] )->s346.begin(),
( (s313*)l[0] )->s346.end() );}
else if( l[0]->s349() == s1141 ) {
s346.push_back( 0 );
s346.push_back( new s356( s299, L"] " + l[0]->to_wstring() ) );}}}
s313::s313( s261* s299, s1053 s1266, s271* s585, const s262* ast_ )
: s1563( s299, s585, ast_ ){
s1190 = s1141;
s322 = s1266;
if( s1266 ) {
s806::Cont v = { s1704, 1, s322, 0 };
s490 = s299->TR().s1038( v );}}
s313::~s313(){
s346.clear();}
void s313::s1302( const vector<s270*>& s698, s271* s585 ){
assert(0);
TDException s960( s7::s1288, s925, s600() );
if( s698.empty() )
return;
s469 pc = s698[0]->s491();
if( pc == s472 && s585->s491() != s473 ) {
throw s960.s992( L"references are not allowed in constructors of data members" );}
if( s698[0]->s349() == s349() ||
s698[0]->s349() == s1704 ) {
s346.assign( ( (s313*)s698[0] )->s346.begin(),
( (s313*)s698[0] )->s346.end() );}}
s1053 s313::s1185( s270* s1160, s1889& s1262, s1053 s2217, s806::Cont& s585 ){
s1053 s680;
s806::Cont vt;
size_t pos = 0;
s1053 s1266 = 0;
s1160->Pass()->TR().s1048( s1262, pos, vt );
s680 = s1160->Pass()->TR().s1003( s806( vt ), false );
if( s680 ) {
s585 = { s2217, 1, vt[2], 0 };
return s680;}
s806::Cont s1271( begin( vt ) + 2, end( vt ) );
if( s1271.size() > 2 )
s1266 = s1160->Pass()->TR().s1038( s1271 );
else
s1266 = s1271[0];
s585 = { s2217, 1, s1266, 0 };
s680 = s1160->Pass()->TR().s1038( s585 );
return s680;}
void s313::load( s270* s1160, s1053 s2217, s1889& s77, s271* s585, const s6::s1680& s1744,
s1053& pt, s1053& vt, const function<void( s483 )> s2220 ){
TDException s960( s7::s1119, s925, s1160->s600() );
if( s77[0] == L']' ) {
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s2220( s1160->Pass()->TR().s515( vt, s585, s585->s297() ) );
return;}
size_t pos = 0;
const s937* s1043 = NULL;
if( s1160->s600() && s1160->s600()->Nqj() )
s1043 = s1160->s600()->Nqj()->s998();
vector<s1::s9<s6::s140>> s93;
s6::s177( s1043, s77, pos, s93, s1744 );
wstring ownerName = s1160->s600()->s267( s2084 ).s168();
bool s1315 = false;
if( ( s1160->s600()->s267( s2085 ).s168() == L"CallSite" ) &&
( ownerName == s7::s1345 || ownerName.find( s7::s1345 + L"<" ) == 0 ) )
s1315 = true;
if( s93.size() ) {
s1053 s2241 = 0;
for( size_t n = 0; n < s93.size(); ++n ) {
s939 s224 = new s262( L"", *s93[n], NULL );
s224->s1333( ((s323*)s1160)->ValType() );
s224->s268( s2278, s140( L"locals" ) );
s270* s1052 = s270::s501( *s224, s1160->Pass(), s585, s585->s297() );
s2220( (s480*) s1052 );
if( s1052->s491() != s472 ) {
if( s2241 == 0 ) {
s2241 = s1052->s349();}
s1052->s2180( s2185 );}}
if( !s1315 ) {
if( !( (s323*)s1160 )->ValType() && s2241 ) {
vt = s2241;
s806::Cont v1 = { s2217, 1, vt, 0 };
pt = s1160->Pass()->TR().s1038( v1 );}
else if( vt != s2241 )
throw s960.s992( L"vector's element type doesn't match the vector type" );}
else if( !vt ) // ???DEBUG??? 220706
vt = s2241;}}
s480* s313::s351( const s262& s694, s271* s585, s1889& s331 ) const{
s1053 pt = 0, vt = 0;
wstring sv;
if( !s2210( (s323*)this, s1704, pt, vt, sv, s694, s585, s331 ) )
return NULL;
s313* s680 = new s313( s299, vector<s270*>({ }), s585, &s694,
pt, vt );
std::function<void( s483 )> s2220 = [s680]( s483 pr )
{s680->s346.push_back( pr ); };
s680->load( s680, s1704, sv, s585, s1721, s680->s490, s680->s322, s2220 );
if( !s680->s314 )
s680->s314 = s299->TR().s1038( std::vector<s1053>(
{ s1702, 2, s680->s1190, 0, s680->s322, 0 } ) );
return s680;}
bool s313::s2210( s323* s1160, s1053 s2217, s1053& pt, s1053& vt, 
wstring& sv, const s262& s694, s271* s585, s1889& s331 ){
wstring s344 = s1160->s350();
TDException s960( s7::s1289, s925, &s694,
L"wrong " + s344 + L" constructor syntax" );
wstring s = s1160->Pass()->TR().s1264( s694.s290(), s331 );
wstring s1262, s641;
if( s694.s267( s2085 ).s168() == L"CallSite" ) {
wstring s1312 = s694.s267( s2084 ).s168();
if( s1312.find( s7::s1345 + L"<" + s344 + L"<" ) == 0 ) {
wstring stype = s1312.substr( s7::s1345.size()+1, s1312.size() - (s7::s1345.size() + 2) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'[' && s[s.size() - 1] == L']' ) {
sv = s;}
else if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s960.s992( L"missing element type" );
s1151( s1160->Pass(), s1160->Pass()->TR().s1341( s ), s1262, s641 );
if( !s641.empty() && ( s641[0] == L'[' || s641[0] == L']' ) )
sv = s641;
if( !s1262.empty() ) {
s806::Cont s585;
pt = s1185( s1160, s1262, s2217, s585 );
vt = s585[2];}
else {
pt = vt = 0;}}
else
return false;
return true;}
void s313::s497( const s271* s872, bool ){
wstring s77 = L"";
TDException s960( s7::s916, s925, s600() );
if( s346.size() == 2 && s346[0].s13() )
s77 = s346[1]->to_wstring();
if(1 || s872->s491() != s473 ||( (s271*)s872 )->s298() == s7::s1345 || s299->s1319() ) { // ???DEBUG??? 221028
if( s77[0] == L']' ) {
s346.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s346.push_back( s299->TR().s515( s322, (s271*)s872, s872->s827() ) );}
else {
for( size_t n = 0; n < s346.size(); ++n ) {
if( s346[n]->s491() == s472 ) {
if( !s346[n]->s1194() )
s346[n]->s497( s872, false );
if( s299->s1319() )
s346[n] = ( s480* ) s346[n].s15<s368*>()->s374()->s332( NULL, NULL );
else
s346[n] = (s480*)s346[n].s15<s368*>()->s332( NULL, NULL );}
else {
if( !s346[n]->s1194() ) {
s482 s1080 = s270::s1010( s299, s346[n], (s271*)s872, (s588*)s872, s872->s297(), false );
s346[n] = s1080;}}
if( !s322 )
s322 = s346[0]->s349();
else if( s346[n]->s349() && s322 != s346[n]->s349() /*&& s299->s1319()*/ )
throw s960.s992( L"elements have different types" );}}
if( s490 || s490 == s1704 ) {
if( !s322 )
throw s960.s992( L"vector's element type is not specified" );
if( !s314 )
s314 = s299->TR().s1038( std::vector<s1053>(
{ s1702, 2, s1190, 0, s322, 0 } ) );
s806::Cont s585 = { s1704, 1, s322, 0 };
s490 = s299->TR().s1038( s585 );}
s1251();}}
void s313::s2472(){
for( size_t n = 0; n < s346.size(); ++n ) {
if( s346[n]->s491() == s472 ) {
s482 tmp = s346[n].s15<s368*>()->s374()->s494( 0, 0 )->s332( 0, 0 );
s346[n] = tmp;}
else {
s482 s1080 = s346[n]->s494( 0, 0 ).s15<s270*>();
s346[n] = s1080;}}}
s483 s313::s494( s480** s273, size_t s495 ){
s2472();
return this;}
void s313::s961( const wstring& s817, const s1705& tbfr, s271* s585,
const s262* ast_ ){
TDException s960( s7::s917, s925, ast_ );
vector<wstring> s798;
s4::s57( s4::s52( s817, s48 ), tbfr.rowSep, s798 );
s1680 s1733 = s1721;
s1733.s1682 = tbfr.s1682;
for( wstring row : s798 ) {
if( !tbfr.mixedTypes ) {
s346.push_back( new s313( s299, s299, row, NULL, tbfr.s1682 ) );}
else {
s951* pd = (s951*)s299->TR().s999( s322 )->s332(0,0);
pd->load( row, s585, s1733 );
s346.push_back( pd );}}}
void s313::s347(){
s1563<s1406, s482, s313>::s347();
s345 = s1563<s1406, s482, s313>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s313::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s345.emplace( make_pair( L"set", new s334( L"set", &s313::s384, s1142,
{ s1112( { s1500::s1495 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"set-el", new s334( L"set-el", &s313::s1253, s1142,
{ s1112( { s1500::s1537, s7::s1385 } ) }, 2, 2, false ) ) );
s345.emplace( make_pair( L"get", new s334( L"get", &s313::s324, 0,
{ s1112( { s1500::s1537 } ) }, 1, 1, true ) ) );
s345.emplace( make_pair( L"append", new s334( L"append", &s313::s1303, s1142,
{ s1112( { s7::s1385 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"sum", new s334( L"sum", &s313::s385, 0,
{ s1112( { s7::s1382, s7::s1387 } ) }, 1, 100 )));
s345.insert( make_pair( L"sumeq", new s334( L"sumeq", &s313::s390, s1142,
{ s1112( { s7::s1382, s7::s1387 } ) }, 1, 100 )));
s345.emplace( make_pair( L"mul", new s334( L"mul", &s313::s387, 0,
{ s1112( { s1500::s1537 } ) }, 1, 1, true ) ) );
s345.emplace( make_pair( L"erase", new s334( L"erase", &s313::s330, 0,
{ s1112( { s1500::s1537 } ), s1112( { s1500::s1537, s1500::s1537 } ) }, 1, 2, false ) ) );
s345.emplace( make_pair( L"resize", new s334( L"resize", &s313::s326, s1142,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"reserve", new s334( L"reserve", &s313::s1873, s1142,
{ s1112( { s1500::s1537 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"eq", new s334( L"eq", &s313::s395, s1141,
{ s1112( { s7::s1382 } ) }, 1, 1, true ) ) );
s345.emplace( make_pair( L"for-each", new s334( L"for-each", &s313::s1730, s1142,
{ s1112( { s7::s1386 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"load-table", new s334( L"load-table", &s313::s795,
s1141, { s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":mixedTypes", 
L":stringsQuoted", L":promInts", L"colNames", L"fieldSep:", L"rowSep:", L":emptyElements" } ) ) );
s345.equal_range( L"get" ).first->second->s1250( true );
s345.equal_range( s7::s1345 ).first->second->s1250( true );
s345.equal_range( L"sum" ).first->second->s1250( true );
s345.equal_range( L"mul" ).first->second->s1250( true );
s345.equal_range( L"erase" ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1400, s1500::s1496 );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s313::s352( s271* s585, const vector<s270*>& l, const s262* ast_ ) const{
if( !s322 )
throw new s16( L"vector's element type is not specified" );
return new s313( s299, l, s585, ast_, s490, s322 );}
s480* s313::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s313* s680 = new s313( s299, vt[2], s585 );
return s680;}
s1053 s313::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" )
s680 = s322;
else if( s1540 == s7::s1345 || s1540 == L"sum" || s1540 == L"mul" || s1540 == L"erase")
s680 = s490;
else
s680 = s1563::s1178( s1540, l );
return s680;}
inline bool
s313::s498( const s480* s499 ) const{
return ( ( (s313*)s499 )->s322 == s322 );}
s270* s313::s332( s588* s2041, s271* impl ) const{
return new s313( *this, impl, s600() );}
void s313::s353( s270* p ) const{
s313* pv = (s313*)p;
pv->s346.assign( s346.begin(), s346.end() );
pv->s1664( wh );}
s480* s313::s1524( const s480* p ) const{
if( s349() == p->s349() ) {
s480* s680 = (s480*)p->s332(0,0);
return s680;}
else if( s299->TR().s1453( p->s349(), s1500::s1495 ) ) {
const s480* proto = s299->TR().s999( s322 );
s313* s680 = (s313*)p->s500()->s332( 0, ns );
s680->s490 = s490;
s680->s322 = s322;
s680->s314 = s314;
if( proto->s491() == s475 ) {
Iterator* s1012 = ( (s323*)p )->s311( NULL );
while( 1 ) {
s482 s2167 = s1012->s312();
if( s2167.s13() )
break;
s480* p = proto->s352( ns, vector<s270*>( { s2167 } ), s600() );
p->s497( ns, true );
s680->s346.push_back( p );}}
s680->s1251();
return s680;}
throw new s16( L"no conversion from '" + s350() + L"' to '" + p->s350() + L"'" );}
Iterator* s313::s1154( const s480* idx ){
s1406::iterator it;
int i = (int)*idx;
if( i >= (int)s346.size() )
it = s346.end();
else {
if( i < 0 ) {
i = (int)s346.size() + i;
if( i < 0 )
i = 0;}
it = s346.begin() + i;}
return new s956( s299, this, it, it == s346.end() ? it : it+1 );}
Iterator* s313::s1173( const s480* _val ){
for( auto it = begin( s346 ); it != end( s346 ); ++it )
if( it->s15<s480*>()->operator==( _val ) )
return new s956( s299, this, it, it+1 );
return new s956( s299, this, end( s346 ), end( s346 ));}
s480* s313::s1180( Iterator* it ){
size_t n = std::distance( begin( s346 ), ( (s956*)it )->s1135() );
return new s343( s299, (int)n );}
Iterator* s313::s1175() {
if( s346.size() )
return new s956( s299, this, s346.begin(), s346.begin()+1 ); 
return new s956( s299, this, s346.end(), s346.end() ); }
Iterator* s313::s1179() {
return new s956( s299, this, s346.end(), s346.end() ); }
void s313::add( s481* el ){
s346.push_back( (s480*) el->s332( 0, ns ) );}
#undef s691
#define s691 ((s313*)(s481*)*s273)
inline void s313::s1226( s480** s273, size_t s495 ){
s313* ps = (s313*)DR;
s313* s680;
if( s495 == 2 ) {
s680 = (s313*)( s273[1] )->s332( 0, ps->ns );}
else if( s273[2]->s1186().s349() == s1704 ) {
s680 = (s313*)ps->s1524( s273[2] );
s680->s2472();}
else if( s273[2]->s1186().s349() == s1403 ) {
auto pr = (s382*)s273[2];
auto rp = pr->s1184();
typename s1374::iterator s1507, s1508;
s1507 = rp.first.s15<s1129*>()->s1135();
s1508 = rp.second.s15<s1129*>()->s1135();
s680 = new s313( ps->s299, vector<s270*>(), ps->ns, ps->s600() );
s680->s346.assign( s1507, s1508 );}
else {
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 )
{ return v.push_back( (s270*)s346 ); } );
s680 = new s313( ps->s299, v, ps->ns, ps->s600(), ps->s490,
ps->s322 );}
if( !s680->s1194() )
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s313::s384( s480** s273, size_t s495 ){
s313* v = ( (s313*)DR );
s323* seq = (s323*)s273[2];
Iterator* s1012 = seq->s311( NULL );
v->s346.clear();
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
v->s346.push_back( p );}}
inline void s313::s1253( s480** s273, size_t s495 ){
s313* v = ( (s313*)DR );
size_t idx = (size_t)(int)*s273[2];
if( idx >= v->size() )
throw new s16( L"vector index is out of range",
(uint32_t)s16::s17::s24 );
s270* el = v->s346[idx];
s273[3]->s353( el );
el->s1251();}
inline void s313::s324( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
int idx = (int)*s273[2];
if( idx < 0 ) {
idx = (int)pv->s346.size() + idx;
if( idx < 0 )
throw new s16( L"negative index is out of bound" );}
if( idx >= (int)pv->s346.size() )
throw new s16( L"index is out of bound" );
*s273 = (s480*)(s270*)pv->s346[idx];}
inline void s313::s330( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
int idx = (int)*s273[2];
int s162 = 1;
if( s495 > 3 )
s162 = (int)*s273[3];
if( idx >= (int)pv->s346.size() )
throw new s16( L"index is out of bound" );
auto it1 = pv->s346.begin() + idx;
s1406::iterator it2;
if( idx + s162 >= pv->s346.size() )
it2 = pv->s346.end();
else
it2 = pv->s346.begin() + idx + s162;
pv->s346.erase( it1, it2 );
*s273 = pv;}
inline void s313::s1303( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
pv->s346.push_back( s273[2]->s332(0,0)->s494(0,0).s15<s270*>());
( (s313*)DR )->s346.back()->s497( s273[0]->s2292(), true );}
inline void s313::s385( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
s691->s346 = ((s313*)pv)->s346;
for( size_t n = 2; n < s495; ++n )
s691->s346.insert( s691->s346.end(), ((s313*)PARN( n ))->s346.begin(),
((s313*)PARN( n ))->s346.end() );}
inline void s313::s390( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
for( size_t n = 2; n < s495; ++n )
pv->s346.insert( pv->s346.end(), ((s313*)PARN( n ))->s346.begin(),
((s313*)PARN( n ))->s346.end() );}
inline void s313::s1730( s480** s273, size_t s495 ){
using s1120 = s313;
using s932 = s956;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s831* s1748 = (s831*)s273[2];
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename s1374::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
while( s1507 != s1508 ) {
s1748->s593( vector<s482>( { *s1507 } ) );
s1748->s494( 0, 0 );
++s1507;}}
inline void s313::s1873( s480** s273, size_t s495 ){
s313* pv = (s313*)DR;
pv->s346.reserve( (int)*s273[2] );}
inline void s313::s326( s480** s273, size_t s495 ){
int size = (int)*s273[2];
s313* pv = ( (s313*)DR );
int oldsize = (int)( (s313*)DR )->s346.size();
pv->s346.resize( size );
for( int i = oldsize; i < size; ++i ) {
pv->s346[i] = pv->s299->TR().s515( pv->s322, pv->s299, pv->s496 );
pv->s346[i]->s497( pv->ns, true );}}
inline void s313::s387( s480** s273, size_t s495 ){
int s162 = (int)*s273[2];
s313* pv = ( (s313*)DR );
s313* s680 = (s313*)pv->s332( 0, 0 );
for( size_t n = 0; n < s162 - 1; ++n ) {
s680->s346.insert( s680->s346.end(), pv->s346.begin(), pv->s346.end() );}
*s273 = s680;}
inline void s313::s395( s480** s273, size_t s495 ){
size_t size = ( (s313*)DR )->s346.size();
s313* right = (s313*)s273[2];
if( right->s346.size() != size ) {
*( (s343*)*s273 )->s354() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( ! right->s346[n].s15<s480*>()->operator==( ( (s313*)DR )->s346[n].s15<s480*>() )) {
*( (s343*)*s273 )->s354() = 0;
return;}}
*( (s343*)*s273 )->s354() = 1;}
inline void s313::s795( s480** s273, size_t s495 ){
s313* pv = ( (s313*)DR );
const wstring& s817 = PARN( 2 )->to_wstring();
s1705 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s495 ) {
s482 par_ = s273[n];
s469 pc = par_->s491();
if( pc == s1055 ) {
s482 par;
s486 rf;
rf = par_.s15<s368*>();
par = par_;
if( par->s349() == Types.No ) {
if( rf->Id() == s1740 ) {
tbfr.mixedTypes = true;}
else if( rf->Id() == s1738 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1736 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1735 ) {
tbfr.s1682 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1737 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1827 ) {
tbfr.s1811 = true;}
else if( rf->Id() == s1734 ) {
if( s495 < n + 2 )
throw new s16( L"Vector::(load-table): the 'colNames:' value is missing" );
tbfr.s1719 = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"Vector::(load-table): unknown parameters" );
++n;}
pv->s961( s817, tbfr, pv->ns, pv->s600() );}
struct s843{
vector<s482>& s346;
s843( vector<s482>& s688 ) : s346( s688 ) {}
bool operator()( const s482 l, const s482 r ) const{
return l.s15<s480*>()->operator<( r.s15<s480*>() );}
};
s480* s313::sort( bool s877, s833* cmp ){
s843 s842( s346 );
if( s877 ) {
if( cmp )
std::sort( s346.rbegin(), s346.rend(), *cmp );
else
std::sort( s346.rbegin(), s346.rend(), s842 );}
else {
if( cmp )
std::sort( s346.begin(), s346.end(), *cmp );
else
std::sort( s346.begin(), s346.end(), s842 );}
return this;}
wstring s313::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[";
if( s615() == s7::s861 )
s680 += L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n )
s680 += s346[n]->to_wstring() + ( n == s346.size() - 1 ? L"" : L", " );}
s680 += L"]";
return s680;}
void s313::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
bool s2056 = s1918->s2051();
s1918->s2050();
ss << L"[";
if( s615() == s7::s861 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n ) {
s346[n].s15<s480*>()->s1919( s1918 );
if( n < s346.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2056 )
s1918->s2049();}
void s313::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Vector : " << this << endl;
for( size_t n = 0; n < s346.size(); ++n ) {
s346[n]->s303( pd, s196 + s416 );
buf << endl;}}
size_t s313::s319() const{
size_t s680 = 0;
for( size_t n = 0; n < s346.size(); ++n )
s680 = s680 * ( ( s480* )&( *s346[n] ) )->s319() << 1;
return s680;}
bool s313::operator==( const s480* p ) const{
if( ( (s313*)p )->s346.size() != s346.size() )
return false;
for( size_t n = 0; n < s346.size(); ++n )
if( ! s346[n].s15<s480*>()->operator==( ((s313*)p )->s346[n].s15<s480*>()) ) // ???DEBUG??? 221028
return false;
return true;}
bool s313::operator<( const s480* p ) const{
return false;}
Iterator* s313::s311( s382* rv, bool s2295 ){
if( !rv ) {
if( !s2295 )
return new s956( s299, this, begin( s346 ), end( s346 ) );
else
return new s956( s299, this, rbegin( s346 ), rend( s346 ) );}
s1134 pr = rv->s1184( this );
return new s956( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
s743::s743( s261* s299, s271* s585, const wstring& s77,
const s262* ast_, const s1705& tbfr )
: s323( s299, s585, ast_ ){
if( s77.size() ) {
s1680 s1744;
s1744.s150 = true;
s1744.s1717 = tbfr.stringsQuoted;
s1744.s1729 = tbfr.s1811;
vector<s1::s9<s6::s140>> s152;
const s937* s1043 = NULL;
if( ast_ )
s1043 = ast_->Nqj()->s998();
if( s77[0] == L'[' ) {
size_t pos = 0;
s6::s177( s1043, s77, pos, s152, s1744 );}
else
s6::s177( s1043, s77, s152, s1744 );
s939 s224;
for( size_t n = 0; n < s152.size(); ++n ) {
s224 = new s262( L"", *s152[n], NULL );
if( ( !tbfr.stringsQuoted && s152[n]->s163() == s133 ) ||
s152[n]->s163() == s138 || s224->s296() == s227 ) {
s224->s1333( Types.String );
s224->s1856( s223::s224 );
s224->s1753( L"\"" + 
s224->s290() + 
L"\"" );}
else if( tbfr.promInts && s152[n]->s163() == s139 )
s224->s1333( s1140 );
if( s224->s290().empty() ) {
if( s1744.s1729 )
s224->s1753( Types( s299, Types.String )->s350() + L"()" );
else
throw new s16( L"empty element in an UntypedVector. To allow"
L" empty elements, use the ':emptyEls' marker." );}
s346.push_back( (s480*) s270::s501( *s224, s299, s585, s585->s297() ) );}}
s490 = s1703;}
s743::s743( s261* s299, const vector<s270*>& l,
const s262* ast_ )
: s323( s299, NULL, ast_ ){
for( auto s1052 : l )
s346.push_back( (s480*)s1052 );
s490 = s1703;}
s743::s743( const s743& right )
: s323( right ){
s346.resize( right.s346.size() );
for( size_t n = 0; n < right.s346.size(); ++n )
s346[n] = (s480*)right.s346[n]->s332( NULL, right.ns );
s490 = right.s490;}
s743::~s743(){
s346.clear();
s496.clear();}
void s743::s1150( s1889& s77, wstring& s1262, wstring& s641,
vector<s1::s9<s6::s140>>& s93, const s262* ast_, const s1680& s1744 ){
assert( !s77.empty() );
if( s77[0] == L'[' ) {
size_t pos = 0;
const s937* s1043 = NULL;
if( ast_ && ast_->Nqj() )
s1043 = ast_->Nqj()->s998();
s6::s177( s1043, s77, pos, s93, s1744 );}
else
s1151( s299, s77, s1262, s641 );}
s480* s743::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s694.s290();
wstring sv;
wstring s344 = s350();
if( s.find( L"UVector[" ) == 0 )
sv = s.substr( 7 );
else if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s4::s52( s.substr( s344.size() ), s48 );
if( sv[0] != L'(' )
throw new s16( L"wrong vector constructor syntax" );
sv = s4::s52( sv.substr( 1, sv.size() - 2 ), L" " );}
else
return 0;
return new s743( s299, s585, sv, &s694 );}
void s743::s497( const s271* s872, bool ){
for( size_t n = 0; n < s346.size(); ++n ) {
if( s346[n]->s491() == s472 ) {
s346[n]->s497( s872, true );}
else {
s482 s1080 = s270::s1010( s299, s346[n], (s271*)s872, (s588*)s872, s872->s297(), false );
s346[n] = s1080;}}
s490 = s1703;
s1664( s7::s860 );
s496 = s872->s827();}
s483 s743::s494( s480** s273, size_t s495 ){
for( size_t n = 0; n < s346.size(); ++n ) {
if( s346[n]->s491() == s472 ) {
s346[n] = s346[n].s15<s368*>()->s374()->s494(0,0)->s332(0,0);}
else {
s482 s1080 = s346[n]->s494( 0, 0 ).s15<s270*>();
s346[n] = s1080;}}
return this;}
void s743::s347(){
s345.insert( make_pair( L"set", new s334( L"set", &s743::s384, s1142,
{ s1112( { s1141, s7::s1381, s7::s1387 } ) }, 2, (size_t)-1 ) ) );
s345.insert( make_pair( L"get", new s334( L"get", &s743::s324, 0,
{ s1112( { s1141 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"fst", new s334( L"fst", &s743::s994, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"snd", new s334( L"snd", &s743::s1067, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"append", new s334( L"append", &s743::s1303, s1142,
{ s1112( { s7::s1381, s7::s1387 } ) }, 1, (size_t)-1 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s743::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"resize", new s334( L"resize", &s743::s326, s1142,
{ s1112( { s1141 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", &s743::s327, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s743::s395, s1141,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"for-each", new s334( L"for-each", &s743::s1730, s1142,
{ s1112( { s7::s1386 } ) }, 1, 1 ) ) );
s345.equal_range( L"get" ).first->second->s1250( true );
s345.equal_range( L"fst" ).first->second->s1250( true );
s345.equal_range( L"snd" ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s743::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s743( s299, s585, L"", ast_, s1723 );}
s480* s743::s352( s271* s585, const std::vector<s1053>& vt ) const{
assert( 0 );
return 0;}
s1053 s743::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"fst" )
s680 = s346[0]->s349();
else if( s1540 == L"snd" )
s680 = s346[1]->s349();
else if( s1540 == L"get" ) {
return s7::s1541 + 1;
if( l[0]->s349() != s1141 )
throw new s16( L"individual elements of an UntypedVector can be accessed "
"only by a literal numerical index" );
int n = (int)*l[0];
s680 = s346[n]->s349();}
return s680;}
inline bool
s743::s498( const s480* s499 ) const{
return ( ( (s313*)s499 )->s349() == s349() );}
s1053 s743::s316() const{
throw new s16( L"UntypedVector doesn't have element type." );}
s270* s743::s332( s588* s2041, s271* impl ) const{
return new s743( *this );}
void s743::s353( s270* p ) const{
p = new s743( *this );}
void s743::assign( const vector<s482>& p ){
s346.assign( begin( p ), end( p ) );}
Iterator* s743::s1175() {
if( s346.size() )
return new s953( s299, this, s346.begin(), s346.begin() + 1 ); 
return new s953( s299, this, s346.end(), s346.end() ); }
Iterator* s743::s1179(){
return new s953( s299, this, s346.end(), s346.end() ); }
s1134 s743::s1184(){
return std::make_pair( s1175(), s1179() );}
#undef s691
#define s691 ((s743*)(s481*)*s273)
inline void s743::s384( s480** s273, size_t s495 ){
s273[3]->s353( ( (s743*)DR )->s346[(int)*s273[2]] );}
inline void s743::s324( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s743*)DR )->s346[(int)*s273[2]];}
inline void s743::s994( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s743*)DR )->s346[0];}
inline void s743::s1067( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s743*)DR )->s346[1];}
inline void s743::s1303( s480** s273, size_t s495 ){
/*if( ( (s743*)DR )->s316() != s273[2]->s492() )
throw new s16( L"unmatched element type" );*/
( (s743*)DR )->s346.push_back( (s480*)s273[2]->s332(0,0) );}
inline void s743::s325( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s743*)DR )->s346.size();}
inline void s743::s326( s480** s273, size_t s495 ){
int size = (int)*s273[2];
( (s743*)DR )->s346.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s743*)DR )->s346[i] = ( (s743*)DR )->s299->s215(
( (s743*)DR )->s314, ( (s743*)DR )->s496 ).s15<s481*>();*/
}
inline void s743::s327( s480** s273, size_t s495 ){
( (s743*)DR )->s346.clear();}
inline void s743::s1730( s480** s273, size_t s495 ){
using s1120 = s743;
using s932 = s953;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s831* s1748 = (s831*)s273[2];
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename s1374::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
while( s1507 != s1508 ) {
s1748->s593( vector<s482>( { *s1507 } ) );
s1748->s494( 0, 0 );
++s1507;}}
inline void s743::s395( s480** s273, size_t s495 ){
size_t size = ( (s743*)DR )->s346.size();
s743* right = (s743*)s273[2];
if( right->s346.size() != size ) {
*( (s343*)*s273 )->s354() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s346[n] != ( (s743*)DR )->s346[n] ) {
*( (s343*)*s273 )->s354() = 0;
return;}}
*( (s343*)*s273 )->s354() = 1;}
inline void s743::s328( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s743*)DR )->s346.size();}
wstring s743::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"UT[";
if( s615() == s7::s861 )
s680 += L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n )
s680 += s346[n]->to_wstring() + ( n == s346.size() - 1 ? L"" : L", " );}
s680 += L"]";
return s680;}
void s743::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
bool s2056 = s1918->s2051();
s1918->s2050();
ss << L"[";
if( s615() == s7::s861 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n ) {
s346[n].s15<s480*>()->s1919( s1918 );
if( n < s346.size() - 1 )
ss << L", ";}}
ss << L"]";
if( !s2056 )
s1918->s2049();}
void s743::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"UntypedVector : " << endl;
for( size_t n = 0; n < s346.size(); ++n )
s346[n]->s303( pd, s196 + s416 );}
size_t s743::s319() const{
size_t s680 = 1;
for( size_t n = 0; n < s346.size(); ++n ) {
size_t h = ( ( s480* )&( *s346[n] ) )->s319();
if(!h) h = 501316864073;
s680 = s680 * h << 1;}
return s680;}
bool s743::operator==( const s480* p ) const{
if( ( (s743*)p )->s346.size() != s346.size() )
return false;
for( size_t n = 0; n < s346.size(); ++n ) {
const s480* l = s346[n].s15<s480*>();
const s480* r = ( (const s743*)p )->s346[n].s15<s480*>();
if( !( *l == r ) )
return false;}
return true;}
bool s743::operator<( const s480* p ) const{
return false;}
Iterator* s743::s311( s382* rv, bool s2295 ){
return NULL;}
/*s483 s743::s312()
{
if( s315 == s346.end() ) {
return NULL;}
s483 s680 = ( *s315 ).s15<s480*>();
s315++;
return s680;
}*/
s951::s951( s261* s299, s271* s585, s1889& s77, const s262* ast_, const s1680& s1744 )
: s743( s299, s585, ast_ ){
s1190 = s1141;
if( s77.size() ) {
s1150( s77, s585, s1744 );}
if( !s490 )
s490 = Types.Tuple;}
s951::s951( s261* s299, s271* s585, const vector<s270*>& l,
const s262* ast_, s1053 s702 )
: s743( s299, l, ast_ ){
if( s702 )
s490 = s702;
else
s490 = s1702;}
s951::s951( const s951& right, const s262* ast_ )
: s743( right ){
s490 = right.s490;
s314 = right.s314;
s1190 = right.s1190;
s322 = right.s322;}
s480* s951::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s = s299->TR().s1264( s694.s290(), s331);
wstring sv;
wstring s344 = s350();
if( s.find( L"[[" ) == 0 )
sv = s;// s.substr( 1, s.size() - 2 );
else if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
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
s951* s680 = new s951( s299, s585, sv, &s694 );
return s680;}
void s951::s497( const s271* s872, bool ){
wstring s77 = L"";
TDException s960( s7::s916, s925, s600() );
if( s346.size() == 2 && s346[0].s13() )
s77 = s346[1]->to_wstring();
if( s77[0] == L']' ) {
s346.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
s939 ast_ = new s262( s77.substr( 9, s77.size() - snum.size() - 10 ), s600()->Nqj(), (s262*)s600() );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s346.push_back( s299->TR().s515( *(s262*)ast_, (s271*)s872, s872->s827() ) );}
else if( s346.size() ) {
s806::Cont s1268;
wstring ts = Types( s299, Types.Tuple )->s350() + L"<";
for( size_t n = 0; n < s346.size(); ++n ) {
if( s346[n]->s491() == s472 ) {
if( !s346[n]->s1194() )
s346[n]->s497( s872, false );
if( s299->s1319() )
s346[n] = (s480*)s346[n].s15<s368*>()->s374()->s332( NULL, NULL );
else {
s346[n] = (s480*)s346[n].s15<s368*>()->s332( NULL, NULL ); // ???DEBUG??? 220805
}}
else {
s482 s1080;
if( !s346[n]->s1194() ) {
s1080 = s270::s1010( s299, s346[n], (s271*)s872, (s588*)s872, s872->s297(), false );
s346[n] = s1080;}}
ts += s299->TR().s1341( s346[n]->s350() );
if( n < s346.size() - 1 )
ts += L" ";}
ts += L">";
s490 = s1185( ts, s1268 );}
s1664( s7::s860 );
s496 = s872->s297();}
void s951::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s951::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false ) ) );
s345.insert( make_pair( L"set", new s334( L"set", &s951::s384, s1142,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"set-el", new s334( L"set-el", &s951::s1254, s1142,
{ s1112( { s1500::s1537, s7::s1381, s7::s1387 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"get", new s334( L"get", &s951::s324, 0,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"fst", new s334( L"fst", &s951::s994, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"snd", new s334( L"snd", &s951::s1067, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"append", new s334( L"append", &s951::s1303, s1142,
{ s1112( { s7::s1381, s7::s1387 } ) }, 1, (size_t)-1 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s951::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"resize", new s334( L"resize", &s951::s326, s1142,
{ s1112( { s1500::s1537 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", &s951::s327, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"eq", new s334( L"eq", &s951::s395, s1141,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"for-each", new s334( L"for-each", &s743::s1730, s1142,
{ s1112( { s7::s1386 } ) }, 1, 1 ) ) );
s345.equal_range( s7::s1345 ).first->second->s1250( true );
s345.equal_range( L"get" ).first->second->s1250( true );
s345.equal_range( L"fst" ).first->second->s1250( true );
s345.equal_range( L"snd" ).first->second->s1250( true );}
s480* s951::s352( s271* s585, const std::vector<s1053>& vt ) const{
s951* s680 = new s951( s299, s585, L"" );
s806 s616( vt );
s680->s490 = s680->s314 = s680->s322 = s299->TR().s1003( s616 );
return s680;}
s480* s951::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
s951* s680 = new s951( s299, s585, l, ast_, s490 );
return s680;}
void s951::s1150( const wstring& s77,	s271* s585, const s1680& s1744 ){
assert( !s77.empty() );
wstring s1262, s641, s1255;
if( s77[0] == L'[' ) {
s1255 = s77.substr( 1, s77.size() - 2 );}
else {
s1151( s299, s77, s1262, s641 );
if( !s641.empty() && s641[0] == L'[' )
s1255 = s641.substr( 1, s641.size() - 2 );
if( !s1262.empty() )
s1148( s1262 );}
if( !s1255.empty() ) {
load( s1255, s585, s1744 );}
else if( !s641.empty() ) {
if( s641.find_first_not_of( s4::digits ) == string::npos ) {
s346.push_back( 0 );
s346.push_back( new s356( s299, s641, ns ) );}}}
void s951::s1148( const std::wstring& s1262 ){
s806::Cont vt;
size_t pos = 0;
s299->TR().s1048( s1262, pos, vt );
s806::Cont s1271( begin( vt ), end( vt ) );
if( s1271.size() > 2 )
s322 = s299->TR().s1038( s1271 );
else
s322 = s1271[0];
s490 = s314 = s322;}
s1053 s951::s1185( const std::wstring& s1262, s806::Cont& s585 ){
s1053 s680;
s806::Cont vt;
size_t pos = 0;
s299->TR().s1048( s1262, pos, vt );
s680 = s299->TR().s1003( s806( vt ), false );
if( s680 ) {
s585.assign( vt.begin(), vt.end() );
return s680;}
s680 = s299->TR().s1038( vt );
s585.assign( vt.begin(), vt.end() );
return s680;}
void s951::load( const wstring& s77, s271* s585, const s1680& s1744 ){
TDException s960( s7::s1118, s925, s600() );
size_t pos = 0;
const s937* s1043 = NULL;
if( s600() && s600()->Nqj() )
s1043 = s600()->Nqj()->s998();
vector<s1::s9<s6::s140>> s93;
s6::s177( s1043, s77, pos, s93, s1744 );
if( s93.size() ) {
s806::Cont s1268;
if( s490 ) {
const s806& vt = s299->TR().s1005( s490 );
s1268.assign( vt.s812().begin(), vt.s812().end() );
if( s93.size() != ( s1268.size() - 2 ) / 2 )
throw s960.s992( L"wrong number of elements passed for inititalizing tuple" );}
else
s1268.push_back( s1702 );
for( size_t n = 0; n < s93.size(); ++n ) {
s939 s224 = new s262( L"", *s93[n], NULL );
s270* p = NULL;
if( s224->s290().empty() ) {
if( s1744.s1729 && s490 ) {
s224->s1753( s299->TR().s797( s1268[( n + 1 ) * 2] ) + L"()" );
p = s270::s501( *s224, s299, s585, s585->s297() );
p->s1664( s7::s1732 );}}
else {
s224->s268( s2278, s140( L"locals" ) );
if( s490 )
s224->s1333( s1268[( n + 1 ) * 2] );
p = s270::s501( *s224, s299, s585, s585->s297() );}
s346.push_back( (s480*) p );
if( s490 ) {
(void)0;}
else {
s1268.push_back( p->s349() );
s1268.push_back( 0 );}}
s1268.insert( s1268.begin() + 1, (s1053)( s1268.size() - 1 ) / 2 );
if( !s322 ) {
s490 = s299->TR().s1038( s1268 );
s322 = s314 = s490;}}
s1251();}
s1053 s951::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == s7::s1345 )
s680 = s490;
else if( s1540 == L"fst" )
s680 = s299->TR().s1005( s490 ).s349( ( 0 + 1 ) * 2 );
else if( s1540 == L"snd" )
s680 = s299->TR().s1005( s490 ).s349( ( 1 + 1 ) * 2 );
else if( s1540 == L"get" ) {
int n = (int)*l[0].s15<s270*>()->s493();
s680 = s299->TR().s1005( s490 ).s349( ( n + 1 ) * 2 );}
return s680;}
bool s951::operator<( const s480* p ) const{
if( ( (s951*)p )->s346.size() != s346.size() )
return false;
for( size_t n = 0; n < s346.size(); ++n ) {
const s480* l = s346[n].s15<s480*>();
const s480* r = ( (const s951*)p )->s346[n].s15<s480*>();
if( !( *l < r ) )
return false;}
return true;}
#undef s691
#define s691 ((s951*)(s481*)*s273)
inline void s951::s1226( s480** s273, size_t s495 ){
s951* ps = (s951*)DR;
s951* s680;
if( s495 == 2 ) {
s680 = (s951*)( s273[1] )->s332( 0, ps->ns );}
else if( s495 == 3 && s273[2]->s1186().s349() == s1702 ) {
s680 = (s951*) ps->s1524( s273[2] );}
else {
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 )
{ return v.push_back( (s270*)s346 ); } );
s680 = new s951( ps->s299, ps->ns, v, ps->s600() );}
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s951::s384( s480** s273, size_t s495 ){
s951* s816 = ( (s951*)DR );
if( s816->s349() != s273[2]->s349() )
throw new s16( L"mismatched types in assignment expression" );
s273[2]->s353( s816 );}
inline void s951::s1254( s480** s273, size_t s495 ){
s951* s816 = ( (s951*)DR );
size_t idx = (int)*s273[2];
s270* el = s816->s346[idx];
if( ! s273[3]->s1529( el->s349()) )
throw new s16( L"mismatched types in assignment expression" );
s273[3]->s353( ( (s951*)DR )->s346[(int)*s273[2]] );}
inline void s951::s324( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s951*)DR )->s346[(int)*s273[2]];}
inline void s951::s994( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s951*)DR )->s346[0];}
inline void s951::s1067( s480** s273, size_t s495 ){
*s273 = (s480*)(s270*)( (s951*)DR )->s346[1];}
inline void s951::s1303( s480** s273, size_t s495 ){
s951* s816 = ( (s951*)DR );
const s951* pro = (s951*)s816->s299->TR().s999( DR->s349() );
size_t n = s816->s346.size();
if( n >= pro->s346.size() )
throw new s16( L"unmatched element type" );
if( false == pro->s346[n]->s498( s273[2] ) )
throw new s16( L"unmatched element type" );
/*if( ( (s743*)DR )->s316() != s273[2]->s492() )
*/
s816->s346.push_back( (s480*)s273[2]->s332(0,0) );}
inline void s951::s325( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s951*)DR )->s346.size();}
inline void s951::s326( s480** s273, size_t s495 ){
int size = (int)*s273[2];
( (s951*)DR )->s346.resize( size );
/*for( int i = oldsize; i < size; ++i )
( (s743*)DR )->s346[i] = ( (s743*)DR )->s299->s215(
( (s743*)DR )->s314, ( (s743*)DR )->s496 ).s15<s481*>();*/
}
inline void s951::s327( s480** s273, size_t s495 ){
( (s951*)DR )->s346.clear();}
inline void s951::s395( s480** s273, size_t s495 ){
size_t size = ( (s951*)DR )->s346.size();
s951* right = (s951*)s273[2];
if( right->s346.size() != size ) {
*( (s343*)*s273 )->s354() = 0;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s346[n] != ( (s951*)DR )->s346[n] ) {
*( (s343*)*s273 )->s354() = 0;
return;}}
*( (s343*)*s273 )->s354() = 1;}
inline void s951::s328( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s951*)DR )->s346.size();}
s270* s951::s332( s588* s2041, s271* impl ) const{
return new s951( *this );}
void s951::s353( s270* p ) const{
s951* pv = (s951*)p;
pv->s346.assign( s346.begin(), s346.end() );
pv->s1664( wh );}
bool s951::s2161( s1889& s ){
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
int s2163 = (int)s4::count( s, L"[", sm.position( 0 ), string::npos, true );
int s2164 = (int)s4::count( s, L"]", sm.position( 0 ), string::npos, true );
return ( s2164 - s2163 > 1 );}
wstring s951::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[[";
if( s615() == s7::s861 )
s680 += L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n )
s680 += s346[n]->to_wstring() + ( n == s346.size() - 1 ? L"" : L", " );}
s680 += L"]]";
return s680;}
void s951::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
ss << L"[[";
if( s615() == s7::s861 )
ss << L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n ) {
s346[n].s15<s480*>()->s1919( s1918 );
if( n < s346.size() - 1 )
ss << L", ";}}
ss << L"]]";}
s1281::s1281( s261* s299, s271* s585, const wstring& s77, const s262* ast_,
const s1680& s1744 )
: s1389( s299, s585, ast_ ){
s1150( s77, s585, s1744 );
if( !s490 )
s490 = Types.ByteArray;}
s1281::s1281( const s1281& right, const s262* ast_ )
: s1389( right.s299, NULL, ast_ ){
s346 = right.s346;
s1190 = right.s1190;
s322 = right.s322;
s314 = right.s314;
s490 = right.s490;
wh = right.wh;}
s1281::s1281( s261* s299, const std::vector<s270*>& l, const s262* ast_ )
: s1389( s299, NULL, ast_ ){
s1150( L"", NULL, s1721 );
if( l.size() ) {
s314 = l[0]->s349();
for( size_t n = 0; n < l.size(); ++n )
s346.push_back( *( (s1284*)l[n] )->s354() );}
if( !s490 )
s490 = Types.ByteArray;}
s1281::~s1281(){
s346.clear();}
void s1281::s1150( const wstring& s77, s480* s585, const s1680& s1744 ){
s1190 = s1141;
s322 = s1297;
s806::Cont v = { s1702, 2, s1141, 0, s322, 0 };
s314 = s299->TR().s1038( v );
s490 = s1139;
if( s77.empty() )
return;
wstring s1262, s641, s1255;
if( s77[0] == L'[' ) {
s1255 = s77;}
else {
s1151( s299, s77, s1262, s641 );
if( !s641.empty() && s641[0] == L'[' )
s1255 = s641;
if( s1262 != s350() )
throw new s16( L"wrong syntax of ByteArray declaration" );}
if( !s1255.empty() ) {
load( s1255, s585, s1744 );}
else if( !s641.empty() ) {
if( s641[0] == L']' && s641.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
wstring snum = s641.substr( s641.rfind( L" " ) );
size_t s162 = std::stoi( snum );
s346.resize( s162 );}}}
void s1281::load( s1889& s77, s480* s585, const s1680& s1744 ){
TDException s960( s7::s1287, s925, s600() );
size_t pos = 0;
const s937* s1043 = NULL;
if( s600() && s600()->Nqj() )
s1043 = s600()->Nqj()->s998();
vector<s1::s9<s6::s140>> s93;
s6::s177( s1043, s77, pos, s93, s1744 );
if( s93.size() ) {
for( size_t n = 0; n < s93.size(); ++n ) {
size_t s162 = s93[n]->s56();
s346.push_back( (tdbyte_t)s162 );}}}
s480* s1281::s351( const s262& s694, s271* s585, s1889& s331 ) const{
TDException s960( s7::s1285, s925, &s694,
L"wrong ByteArray constructor syntax" );
wstring s = s299->TR().s1264( s694.s290(), s331 );
wstring sv;
wstring s344 = s350();
if( s[0] == L'[' && s[s.size() - 1] == L']' )
sv = s;
else if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
sv = s;
if( sv.find( L'<' ) != string::npos )
throw s960.s992( L"'<' symbol is not allowed here" );}
else
return NULL;
try {
s1281* s680 = new s1281( s299, s585, sv, &s694 );
return s680;}
catch( s16* e ) {
e->s30( L"while parsing ByteArray definition" );
throw e;}}
bool s1310( const tdbyte_t& l, const tdbyte_t& r ){
return l < r;}
void s1281::s497( const s271* s872, bool ){
s1664( s7::s860 );
if( s872 )
s496 = s872->s827();}
void s1281::s347(){
s1389<s1363, tdbyte_t, s1281, s1284>::s347();
s345 = s1389<s1363, tdbyte_t, s1281, s1284>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1281::s1226, s1139,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 1 ) ) );
s345.emplace( make_pair( L"set", new s334( L"set", &s1281::s384, s1142,
{ s1112( { s1500::s1495 } ) }, 1, 1 ) ) );
s345.emplace( make_pair( L"set-el", new s334( L"set-el", &s1281::s1253, s1142,
{ s1112( { s1141, s1141 } ) }, 2, 2 ) ) );
s345.emplace( make_pair( L"get", new s334( L"get", &s1281::s324, s1297,
{ s1112( { s1141 } ) }, 1, 1 ) ) );
s345.emplace( make_pair( L"append", new s334( L"append", &s1281::s1303, s1142,
{ s1112( { s7::s1385 } ) }, 1, 1 ) ) );
s345.emplace( make_pair( L"resize", new s334( L"resize", &s1281::s326, s1142,
{ s1112( { s1141 } ) }, 1, 1 ) ) );
s345.emplace( make_pair( L"eq", new s334( L"eq", &s1281::s395, s1138,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s299->TR().s1152( s490, s7::s1400, s1500::s1496 );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s1281::s352( s271* s585, const vector<s270*>& l, const s262* ast_ ) const{
return new s1281( s299, s585, L"", ast_ );}
s480* s1281::s352( s271* s585, const std::vector<s1053>& vt ) const{
return new s1281( s299, s585, L"" );}
inline bool
s1281::s498( const s480* s499 ) const{
return ( ( (s1281*)s499 )->s349() == s349() );}
s270* s1281::s332( s588* s2041, s271* impl ) const{
return new s1281( *this );}
void s1281::s353( s270* p ) const{
p = new s1281( *this );}
Iterator* s1281::s1154( const s480* idx ){
s1363::iterator it;
int i = (int)*idx;
if( i >= (int)s346.size() )
it = s346.end();
else {
if( i < 0 ) {
i = (int)s346.size() + i;
if( i < 0 )
i = 0;}
it = s346.begin() + i;}
return new s1282( s299, this, it, it == s346.end() ? it : it + 1 );}
Iterator* s1281::s1173( const s480* _val ){
for( auto it = begin( s346 ); it != end( s346 ); ++it )
if( *it == *( (s1284*)_val )->s354() )
return new s1282( s299, this, it, it + 1 );
return new s1282( s299, this, end( s346 ), end( s346 ) );}
s480* s1281::s1180( Iterator* it ){
size_t n = std::distance( begin( s346 ), ( (s1282*)it )->s1135() );
return new s343( s299, (int)n );}
Iterator* s1281::s1175() {
if( s346.size() )
return new s1282( s299, this, s346.begin(), s346.begin() + 1 ); 
return new s1282( s299, this, s346.end(), s346.end() ); }
Iterator* s1281::s1179() {
return new s1282( s299, this, s346.end(), s346.end() ); }
#undef s691
#define s691 ((s1281*)(s481*)*s273)
inline void s1281::s1226( s480** s273, size_t s495 ){
s1281* ps = (s1281*)DR;
s1281* s680 = NULL;
if( s495 == 2 ) {
s680 = (s1281*)( s273[1] )->s332(0,0);}
else if( s273[2]->s1186().s349() == s1704 ) {
s313* pv = (s313*)s273[2];
s680 = new s1281( ps->s299, ps->ns, L"", ps->s600() );
for( size_t n = 0; n < pv->s317().size(); ++n ) {
s680->s346.push_back( (int)*pv->s317()[n] );}}
else if( s273[2]->s349() == s1403 ) {
auto pr = (s382*)s273[2];
auto rp = pr->s1184();
typename s1374::iterator s1507, s1508;
s1507 = rp.first.s15<s1129*>()->s1135();
s1508 = rp.second.s15<s1129*>()->s1135();
s680 = new s1281( ps->s299, ps->ns, L"", ps->s600() );
s680->s346.assign( s1507, s1508 );}
else
assert( 0 );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s1281::s384( s480** s273, size_t s495 ){
s1281* v = ( (s1281*)DR );
s323* seq = (s323*)s273[2];
s382 range( 0, -1 );
Iterator* s1012 = seq->s311( &range );
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
v->s346.push_back( *p.s15<s1284*>()->s354() );}}
inline void s1281::s1253( s480** s273, size_t s495 ){
assert( s273[3]->s349() == s1141 );
assert( s273[2]->s349() == s1141 );
s1281* v = ( (s1281*)DR );
size_t idx = (size_t)(int)*s273[2];
v->s346[idx] = *( (s1284*)s273[3] )->s354();}
inline void s1281::s324( s480** s273, size_t s495 ){
s1284* s680 = new s1284( ( (s1281*)DR )->s299,
( (s1281*)DR )->s346[(int)*s273[2]] );
*s273 = (s480*)(s270*)s680;}
inline void s1281::s1303( s480** s273, size_t s495 ){
assert( s273[2]->s349() == s1297 );
( (s1281*)DR )->s346.push_back( *( (s1284*)s273[2] )->s354() );}
inline void s1281::s326( s480** s273, size_t s495 ){
int size = (int)*s273[2];
( (s1281*)DR )->s346.resize( size );}
inline void s1281::s395( s480** s273, size_t s495 ){
size_t size = ( (s1281*)DR )->s346.size();
s1281* right = (s1281*)s273[2];
if( right->s346.size() != size ) {
*( (s357*)*s273 )->s354() = false;
return;}
for( size_t n = 0; n < size; ++n ) {
if( right->s346[n] != ( (s1281*)DR )->s346[n] ) {
*( (s357*)*s273 )->s354() = false;
return;}}
*( (s357*)*s273 )->s354() = true;}
wstring s1281::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[";
if( s615() == s7::s861 )
s680 += L"_not_set_";
else {
for( size_t n = 0; n < s346.size(); ++n )
s680 += std::to_wstring( s346[n] ) + ( n == s346.size() - 1 ? L"" : L", " );}
s680 += L"]";
return s680;}
void s1281::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"ByteArray : " << endl;
to_wstring();}
size_t s1281::s319() const{
size_t s680 = 0;
for( size_t n = 0; n < s346.size(); ++n )
s680 = ( s680 * s346[n] ) << 1;
return s680;}
bool s1281::operator==( const s480* p ) const{
if( ( (s1281*)p )->s346.size() != s346.size() )
return false;
for( size_t n = 0; n < s346.size(); ++n )
if( !( s346[n] == ( (s1281*)p )->s346[n] ) )
return false;
return true;}
bool s1281::operator<( const s480* p ) const{
return false;}
Iterator* s1281::s311( s382* rv, bool s2295 ){
s1134 pr = rv->s1184( this );
return new s1282( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
s321::s321( s261* s299, s1053 s1191, s1053 s1265, s1053 s1171,
s1053 s702, s271* s585, const s262* ast_ )
: s1357( s299, s585, ast_ ){
assert( s1191 && s1265 );
this->s1190 = s1191;
s322 = s1265;
if( s1171 )
s314 = s1171;
else {
s806 s1172( s806::Cont( { s1702, 2, s1190, 0, s322, 0 } ) );
s314 = s299->TR().s1003( s1172 );}
if( s702 )
s490 = s702;
else {
s490 = s299->TR().s1038( s806::Cont( { Types.Index, 2, s1191, 0, s1265, 0 } ) );}}
s321::s321( const s321& right, const s262* ast_ )
: s1357( right.s299, right.ns, ast_ ){
s346 = right.s346;
s490 = right.s490;
s1190 = right.s1190;
s322 = right.s322;
s314 = right.s314;
wh = right.wh;}
s321::s321( s261* s299, const std::vector<s270*>& l,
s271* s585, const s262* ast_, s1053 s702, s1053 s1171,
s1053 s1625, s1053 s1265 )
: s1357( s299, s585, ast_ ){
s1190 = s1625;
s322 = s1265;
s314 = s1171;
s490 = s702;
if( l.size() && ( l.front()->s349() == s349() ||
l.front()->s349() == Types.Index ) ) {
s346 = ( (s321*)l.front() )->s346;}}
void s321::s1150( s1889& s77, wstring& s1262, wstring& s641,
vector<pair<wstring, s141>> s93, const s262* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s142> ob = new s6::s142( NULL );
size_t pos = 0;
s937 s1044( L"", true, s1721 );
s1044.s169( s77, pos, ob );
ob->s159( s93 );}
else
s1151( s299, s77, s1262, s641 );}
s480* 
s321::s351( const s262& s694, s271* s585, s1889& s331 ) const{
s1053 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s2210( (s323*)this, s1700, pt, et, vt, kt, sv, s694, s585, s331 ) )
return NULL;
s321* s680 = new s321( s299, vector<s270*>({ }), s585, &s694,
pt, et, kt, vt );
wstring ownerName = s694.s267( s2084 ).s168();
bool s1315 = false;
if( ( s694.s267( s2085 ).s168() == L"CallSite" ) &&
( ownerName == s7::s1345 || ownerName.find( s7::s1345 + L"<" ) == 0 ) )
s1315 = true;
std::function<void(pair<s483, s483>)> s2220 = [s680]( std::pair<s483, s483> pr )
{s680->s346.insert( make_pair( pr.first, pr.second ) ); };
load( s680, sv, s585, L",", s680->s1190, s680->s322, s2220 );
if( !s1315 && s346.size() ) {
if( !s314 && s346.begin()->second->s349() ) {
s680->s314 = s299->TR().s1038( { s1702, 2, s346.begin()->first->s349(), 0,
s346.begin()->second->s349(), 0 } );
s806::Cont v1 = { Types.Index, 2, s346.begin()->first->s349(), 0,
s346.begin()->second->s349(), 0 };
s680->s490 = s299->TR().s1038( v1 );}
else if( s322 != s346.begin()->second->s349() )
throw new s16( L"index' element type doesn't match the index type" );}
return s680;}
bool s321::s2210( s323* s1160, s1053 s2217, s1053& pt, s1053& et, s1053& vt,
s1053& kt, std::wstring& sv, const s262& s694, s271* s585, s1889& s331 ){
wstring s344 = s1160->s350();
wstring s = s1160->Pass()->TR().s1264( s694.s290(), s331 );
wstring si;
wstring s1262, s641;
if( s694.s267( s2085 ).s168() == L"CallSite" ) {
wstring s1312 = s694.s267( s2084 ).s168();
if( s1312.find( s7::s1345 + L"<" + s344 + L"<" ) == 0 ) {
wstring stype = s1312.substr( s7::s1345.size()+1, s1312.size() - ( s7::s1345.size() + 2 ) );
s = stype + L"(" + s + L")";}}
if( s[0] == L'{' && s[s.size() - 1] == L'}' )
sv = s; // s4::s52( s, L"{}" );
else if( s.find( s344 ) == 0 && s[s.size() - 1] == L')' ) {
si = s;
if( si.find( L'<' ) == string::npos )
throw new s16( L"wrong index constructor syntax" );
s1151( s1160->Pass(), s, s1262, s641 );
if( !s641.empty() && ( s641[0] == L'{' || s641[0] == L'}' ) )
sv = s641;
if( !s1262.empty() ) {
s806::Cont s585;
pt = s1185( s1160, s1262, s1700, s585, et, kt, vt );}}
else
return false;
return true;}
s1053 s321::s1185( s270* s1160, s1889& s1262, s1053 s2217, s806::Cont& s585,
s1053& et, s1053& kt, s1053& vt ){
s1053 s680;
s806::Cont s1268;
size_t pos = 0;
s261* s2211 = s1160->Pass();
s2211->TR().s1048( s2211->TR().s1341( s1262 ), pos, s1268 );
s680 = s2211->TR().s1003( s806( s1268 ), false );
if( s680 ) {
s806 s1090( s1268 );
kt = s1090.s349( 2 );
vt = s1090.s349( 4 );
s585 = { Types.Index, 2, kt, 0, vt, 0 };
et = s2211->TR().s1038(
s806::Cont( { s1702, 2, kt, 0, vt, 0 } ) );
return s680;}
s806::Cont s1456, s1503;
size_t idx = 2;
s488::s2103( s1268, idx, s1456 );
if( s1456.size() > 2 )
kt = s2211->TR().s1038( s1456 );
else
kt = s1456[0];
s488::s2103( s1268, idx, s1503 );
if( s1503.size() > 2 )
vt = s2211->TR().s1038( s1503 );
else
vt = s1503[0];
et = s2211->TR().s1038( 
s806::Cont( { s1702, 2, kt, 0, vt, 0 } ) );
s585 = { Types.Index, 2, kt, 0, vt, 0 };
s680 = s2211->TR().s1038( s585 );
return s680;}
void s321::load( s270* s1160, s1889& s77, s271* s585, s1889& s72, s1053& kt, s1053& vt, 
const std::function<void(std::pair<s483,s483>)> s2220 ){
TDException s960( s7::s1584, s925, s1160->s600() );
vector<pair<wstring, s1::s9<s6::s140>>> s93;
if( s77[0] == L'{' ) {
s1::s9<s6::s142> ob = new s6::s142( NULL );
size_t pos = 0;
s937 s1044( L"", true, s1721 );
s1044.s169( s77, pos, ob );
ob->s159( s93 );}
if( s93.empty() )
return;
wstring ownerName = s1160->s600()->s267( s2084 ).s168();
bool s1315 = false;
if( ( s1160->s600()->s267( s2085 ).s168() == L"CallSite" ) &&
( ownerName == s7::s1345 || ownerName.find( s7::s1345 + L"<" ) == 0 ) )
s1315 = true;
for( size_t n = 0; n < s93.size(); ++n ) {
s939 s967 = new s262( s93[n].first, s1160->s600()->Nqj(), (s262*)s1160->s600() );
s482 s1049 = s270::s501( *s967, s1160->Pass(), s585, s585->s297() );
basic_stringstream<wchar_t> s1076;
s93[n].second->s154( &s1076 );
s939 s224 = new s262( s1076.str(), s1160->s600()->Nqj(), (s262*)s1160->s600() );
s482 s1057 = s270::s501( *s224, s1160->Pass(), s585, s585->s297() );
s2220( make_pair( s1049.s15<s480*>(), s1057.s15<s480*>() ) );
if( s1049->s491() != s472 ) {
if( kt == 0 ) {
kt = s1049->s349();}
s1049->s2180( s2185 );}
if( s1057->s491() != s472 ) {
if( vt == 0 ) {
vt = s1057->s349();}
s1057->s2180( s2185 );}}}
void s321::s2208( s270* s1160, s1889& s77, s271* s585, s1053& kt, s1053& s2231,
const std::function<void( std::pair<s483, s483> )> s2220 ){
TDException s960( s7::s916, s925, s1160->s600(), L"wrong Index definition" );
s1160->s1251();}
void s321::s497( const s271* s872, bool ){
if( s872->s491() != s473 ||
( (s271*)s872 )->s298() != s7::s1345 || s299->s1319() ) {
auto it = begin( s346 );
while( it != end( s346 ) ) {
s270* pk = it->first.s15<s270*>();
s270* pv = it->second.s15<s270*>();
pk->s497( s872, false );
if( pk->s491() == s472 ) {
pk = ( (s368*)pk )->s374()->s332( NULL, NULL );}
pv->s497( s872, false );
if( pv->s491() == s472 ) {
pv = ( (s368*)pv )->s374()->s332( NULL, NULL );}
s482 s2288 = s270::s1010( s299, pk, (s271*)s872, (s588*)s872, s872->s297(), false );
s482 s2289 = s270::s1010( s299, pv, (s271*)s872, (s588*)s872, s872->s297(), false );
if( !s322 )
s322 = s346[0]->s349();
else if( s322 != s2289->s349() )
throw new s16( L"elements have different types" );
auto it1 = it;
it++;
s346.erase( it1 );
s346.insert( make_pair( s2288->s494( 0, 0 ), s2289->s494( 0, 0 ) ) );}
s1251();}}
void s321::s347(){
s1357<s1375, s483, s483, s321>::s347();
s345 = s1357<s1375, s483, s483, s321>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s321::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s345.insert( make_pair( L"insert", new s334( L"insert", &s321::s329, s1142,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"get", new s334( L"get", &s321::s324, 0,
{ s1112( { s7::s1384 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"get-val", new s334( L"get-val", &s321::s1451, 0,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"keys", new s334( L"keys", &s321::s2294, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"values", new s334( L"values", &s321::s2198, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"set", new s334( L"set", &s321::s384, s1142,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"set-el", new s334( L"set-el", &s321::s1579, s1138,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"erase", new s334( L"erase", &s321::s330, s1142,
{ s1112( { s7::s1384 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s321::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.equal_range( L"get" ).first->second->s1250( true );
s345.equal_range( L"get-val" ).first->second->s1250( true );
s345.equal_range( L"keys" ).first->second->s1250( true );
s345.equal_range( L"values" ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s321::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
assert( 0 );
return NULL;}
s480* s321::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s806::Cont s1014, s1093;
s488::s2103( vt, idx, s1014 );
s806 s1013( s1014[0] );
s1053 s1191 = s299->TR().s1003( s1013 );
s488::s2103( vt, idx, s1093 );
s806 s1090( s1093[0] );
s1053 s1265 = s299->TR().s1003( s1090 );
s1053 s1171 = s299->TR().s1038( s806::Cont { s1702, 2,
s1191, 0, s1265, 0 } );
s321* s680 = new s321( s299, s1191, s1265, s1171, 0, s585, NULL );
return s680;}
else {
assert( 0 );
s806::Cont s984;
s488::s2103( vt, idx, s984 );
s806 s983( s984[0] );
s1053 s1171 = s299->TR().s1003( s983 );
const s806& s1089 = s299->TR().s1005( s1171 );
s806::Cont s1014, s1093;
idx = 2;
s488::s2103( s1089.s812(), idx, s1014 );
s806 s1013( s1014[0] );
s1053 s1191 = s299->TR().s1003( s1013 );
s488::s2103( s1089.s812(), idx, s1093 );
s806 s1090( s1093[0] );
s1053 s1265 = s299->TR().s1003( s1090 );
s321* s680 = new s321( s299, s1191, s1265, s1171, 0, s585, NULL );
return s680;}}
s1053 s321::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" ) {
s680 = s322;}
else if( s1540 == L"get-val" ) {
s680 = s322;}
else if( s1540 == L"keys" ) {
s806::Cont s1268;
wstring ts = this->s299->TR().s1341( 
Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, s1190 )->s350() + L">" );
s680 = ((s313*)Types( s299, Types.Vector ))->s1185( (s270*)this, ts, s1704, s1268 );}
else if( s1540 == L"values" ) {
s806::Cont s1268;
wstring ts = this->s299->TR().s1341( 
Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, s322 )->s350() + L">" );
s680 = ((s313*)Types( s299, Types.Vector ))->s1185( (s270*)this, ts, s1704, s1268 );}
else
s680 = s1357::s1178( s1540, l );
return s680;}
inline bool
s321::s498( const s480* s499 ) const{
return 0; /* ( ( (s313*)s499 )->s314 == s314 );*/
}
s270* s321::s332( s588* s2041, s271* impl ) const{
return new s321( *this, s600() );}
void s321::s353( s270* p ) const{
p = new s321( *this );}
size_t s321::s319() const{
return (size_t)this;}
bool s321::operator==( const s480* p ) const{
return ( this == p );}
bool s321::operator<( const s480* p ) const{
return false;}
Iterator* s321::s1175() {
auto it = begin( s346 );
return new s931( s299, this, s346.begin(), ++it ); }
Iterator* s321::s1179() {
return new s931( s299, this, s346.end(), s346.end() ); }
#undef s691
#define s691 ((s321*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
inline void s321::s1226( s480** s273, size_t s495 ){
s321* ps = (s321*)DR;
s321* s680 = NULL;
if( s495 == 2 ) {
s680 = (s321*)( s273[1] )->s332(0, ps->ns);}
else if( s273[2]->s1186().s349() == s1700 ) {
s680 = (s321*)ps->s1524( s273[2] );}
else {
assert( 0 );
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 ) { return v.push_back( (s270*)s346 ); } );}
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s321::s329( s480** s273, size_t s495 ){
s483 s151 = (s480*)PARN( 2 )->s494(0,0);
s321* dr = (s321*)DR;
s1374::iterator it = dr->s346.find( s151 );
if( it == dr->s346.end() ) {
s480* s1057 = (s480*)PARN( 3 );
if( dr->s1190 != s151->s349() || dr->s322 != s1057->s349() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s483 s346 = s1057->s332(0,0)->s494(0,0);
dr->s346.insert( make_pair( s151, s346 ) );}}
inline void s321::s324( s480** s273, size_t s495 ){
s321* p = (s321*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() )
throw new s16( L"key doesn't exist: '" + s273[2]->to_wstring() + L"'" );
else {
*s273 = it->second.s15<s480*>();}}
inline void s321::s1451( s480** s273, size_t s495 ){
s321* p = (s321*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() ) {
*s273 = (s480*)PARN( 3 )->s332(0,0);}
else {
*s273 = (s480*)it->second->s332(0,0);
s273[0]->s1251();//s497( p->ns, true );
}}
inline void s321::s2294( s480** s273, size_t s495 ){
s321* p = (s321*)DR;
s313* s680 = new s313( p->s299, p->ValType(), p->ns, p->s600() );
s1374::iterator it = p->s346.begin();
vector<s482>& v = s680->s317();
v.resize( p->s346.size() );
size_t idx = 0;
for( ; it != p->s346.end(); ++it )
v[idx++] = it->first.s15<s270*>();
s680->s1251();
*s273 = s680;}
inline void s321::s2198( s480** s273, size_t s495 ){
s321* p = (s321*)DR;
s313* s680 = new s313( p->s299, p->ValType(), p->ns, p->s600() );
s1374::iterator it = p->s346.begin();
vector<s482>& v = s680->s317();
v.resize( p->s346.size() );
size_t idx = 0;
for( ; it != p->s346.end(); ++it )
v[idx++] = it->second.s15<s270*>();
s680->s1251();
*s273 = s680;}
inline void s321::s384( s480** s273, size_t s495 ){
s321* l = (s321*)DR;
s321* right = (s321*)PARN( 2 );
*l = *right;}
inline void s321::s1579( s480** s273, size_t s495 ){
s483 s151 = (s480*)PARN( 2 )->s494(0,0);
s480* s346 = (s480*)PARN( 3 );
s321* dr = (s321*)DR;
if( dr->s1190 != s151->s349() || dr->s322 != s346->s349() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1374::iterator it = dr->s346.find( (s480*)PARN( 2 ) );
if( it == dr->s346.end() ) {
s483 s1230 = (s480*)s346->s332(0,0)->s494(0,0);
s483 s1581 = (s480*)s151->s332(0,0);
dr->s346.insert( make_pair( s1581, s1230 ) );
*s273 = s366;}
else {
it->second = (s480*)s346->s332(0,0)->s494(0,0);
*s273 = s367;}}
inline void s321::s330( s480** s273, size_t s495 ){
s321* p = (s321*)DR;
p->s346.erase( (s480*)PARN( 2 ) );}
inline void s321::s325( s480** s273, size_t s495 ){}
inline void s321::s328( s480** s273, size_t s495 ){}
Iterator* s321::s311( s382* rv, bool s2295 ){
if( !rv ) {
if( !s2295 )
return new s931( s299, this, begin( s346 ), end( s346 ) );
else
return new s931( s299, this, rbegin( s346 ), rend( s346 ) );}
s1134 pr = rv->s1184( this );
return new s931( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
wstring s321::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"{ ";
for( auto it = begin( s346 ); it != end( s346 ); ++it )
s680 += ( it == begin( s346 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s680 += L" }";
return s680;}
void s321::s1919( Stream* s1918 ) const{
s2212( (s270*)this, s1918, ((s321*)this)->s311( NULL ) );}
void s321::s2212( s270* subj, Stream* s1918, Iterator* it ){
s1488& ss = s1918->s1948();
bool s2056 = s1918->s2051();
s1918->s2050();
ss << L"{";
if( subj->s615() == s7::s861 )
ss << L"_not_set_";
else {
bool s2229 = true;
for( ; ; ) {
s482 s2167 = it->s312();
if( s2167.s13() )
break;
if( !s2229 )
ss << L", ";
else
s2229 = false;
s2167.s15<s951*>()->s317()[0].s15<s480*>()->s1919( s1918 );
ss << L" : ";
s2167.s15<s951*>()->s317()[1].s15<s480*>()->s1919( s1918 );}}
ss << L"}";
if( !s2056 )
s1918->s2049();}
void s321::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Index : " << endl;
for( auto it = begin( s346 ); it != end( s346 ); ++it ) {
buf << s4::fill_n_ch( L' ', s196 ) << it->first->to_wstring() + L" : ";
it->second->s303( pd, s196 + s416 );}}
s1370::s1370( s261* s299, s1053 s1191, s1053 s1265, s1053 s1171,
s1053 s702, s271* s585, const s262* ast_ )
: s1357( s299, s585, ast_ ){
assert( s1191 && s1265 );
this->s1190 = s1191;
s322 = s1265;
if( s1171 )
s314 = s1171;
else {
s806 s1172( s806::Cont( { s1702, 2, s1190, 0, s322, 0 } ) );
s314 = s299->TR().s1003( s1172 );}
if( s702 )
s490 = s702;
else {
s490 = s299->TR().s1038( s806::Cont( { Types.HashIndex, 2, s1191, 0, s1265, 0 } ) );}}
s1370::s1370( const s1370& right, const s262* ast_ )
: s1357( right.s299, right.ns, ast_ ){
s346 = right.s346;
s490 = right.s490;
s1190 = right.s1190;
s322 = right.s322;
s314 = right.s314;
wh = right.wh;}
s1370::s1370( s261* s299, const std::vector<s270*>& l,
s271* s585, const s262* ast_, s1053 s702, s1053 s1171,
s1053 s1625, s1053 s1265 )
: s1357( s299, s585, ast_ ){
s1190 = s1625;
s322 = s1265;
s314 = s1171;
s490 = s702;
if( l.size() && ( l.front()->s349() == s349() ||
l.front()->s349() == Types.Index ) ) {
s346 = ( (s1370*)l.front() )->s346;}}
void s1370::s1150( const wstring& s77, wstring& s1262, wstring& s641,
vector<pair<wstring, s141>> s93, const s262* ast_ ){
assert( !s77.empty() );
if( s77[0] == L'{' ) {
s1::s9<s6::s142> ob = new s6::s142( NULL );
size_t pos = 0;
s937 s1044( L"", true, s1721 );
s1044.s169( s77, pos, ob );
ob->s159( s93 );}
else
s1151( s299, s77, s1262, s641 );}
s480* 
s1370::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
s1053 pt = 0, et = 0, kt = 0, vt = 0;
wstring sv;
if( !s321::s2210( (s323*)this, s1700, pt, et, vt, kt, sv, s694, s585, s331 ) )
return NULL;
s1370* s680 = new s1370( s299, vector<s270*>( { } ), s585, &s694,
pt, et, kt, vt );
wstring ownerName = s694.s267( s2084 ).s168();
bool s1315 = false;
if( ( s694.s267( s2085 ).s168() == L"CallSite" ) &&
( ownerName == s7::s1345 || ownerName.find( s7::s1345 + L"<" ) == 0 ) )
s1315 = true;
auto s2220 = [s680]( std::pair<s483, s483> pr ) {s680->s346.insert( make_pair( pr.first, pr.second ) ); };
s321::load( s680, sv, s585, L",", s680->s1190, s680->s322, s2220 );
if( !s1315 && s346.size() ) {
if( !s314 && s346.begin()->second->s349() ) {
s680->s314 = s299->TR().s1038( { s1702, 2, s346.begin()->first->s349(), 0,
s346.begin()->second->s349(), 0 } );
s806::Cont v1 = { Types.Index, 2, s346.begin()->first->s349(), 0,
s346.begin()->second->s349(), 0 };
s680->s490 = s299->TR().s1038( v1 );}
else if( s322 != s346.begin()->second->s349() )
throw new s16( L"index' element type doesn't match the index type" );}
return s680;}
void s1370::s497( const s271* s872, bool ){
s321::s2208( this, s496, (s271*)s872, s1190, s322,
[this]( std::pair<s483, s483> pr ) {this->s346.insert( make_pair( pr.first, pr.second ) ); } );}
void s1370::s347(){
s1357<s1369, s483, s483, s1370>::s347();
s345 = s1357<s1369, s483, s483, s1370>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1370::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s345.insert( make_pair( L"insert", new s334( L"insert", &s1370::s329, s1142,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"find", new s334( L"find", &s1370::s773, 0,
{ s1112( { s7::s1384 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"get", new s334( L"get", &s1370::s324, 0,
{ s1112( { s7::s1384 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"get-val", new s334( L"get-val", &s1370::s1451, 0,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"set", new s334( L"set", &s1370::s384, s1138,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"set-el", new s334( L"set-el", &s1370::s1579, s1138,
{ s1112( { s7::s1384, s7::s1385 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"erase", new s334( L"erase", &s1370::s330, s1142,
{ s1112( { s7::s1384 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s1370::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.equal_range( L"find" ).first->second->s1250( true );
s345.equal_range( L"get" ).first->second->s1250( true );
s345.equal_range( L"get-val" ).first->second->s1250( true );}
s480* s1370::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
assert( 0 );
return NULL;}
s480* s1370::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1], idx = 2;
assert( n == 2 || n == 1 );
if( n == 2 ) {
s806::Cont s1014, s1093;
s488::s2103( vt, idx, s1014 );
s806 s1013( s1014[0] );
s1053 s1191 = s299->TR().s1003( s1013 );
s488::s2103( vt, idx, s1093 );
s806 s1090( s1093[0] );
s1053 s1265 = s299->TR().s1003( s1090 );
s1053 s1171 = s299->TR().s1038( s806::Cont { s1702, 2,
s1191, 0, s1265, 0 } );
s1370* s680 = new s1370( s299, s1191, s1265, s1171, 0, s585, NULL );
return s680;}
else {
assert( 0 );
s806::Cont s984;
s488::s2103( vt, idx, s984 );
s806 s983( s984[0] );
s1053 s1171 = s299->TR().s1003( s983 );
const s806& s1089 = s299->TR().s1005( s1171 );
s806::Cont s1014, s1093;
idx = 2;
s488::s2103( s1089.s812(), idx, s1014 );
s806 s1013( s1014[0] );
s1053 s1191 = s299->TR().s1003( s1013 );
s488::s2103( s1089.s812(), idx, s1093 );
s806 s1090( s1093[0] );
s1053 s1265 = s299->TR().s1003( s1090 );
s1370* s680 = new s1370( s299, s1191, s1265, s1171, 0, s585, NULL );
return s680;}}
s1053 s1370::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" ) {
s680 = s322;}
else if( s1540 == L"get-val" ) {
s680 = s322;}
else if( s1540 == L"values" ) {
s806::Cont s1268;
wstring ts = this->s299->TR().s1341(
Types( s299, Types.Vector )->s350() + L"<" +
Types( s299, s322 )->s350() + L">" );
s680 = ( (s313*)Types( s299, Types.Vector ) )->s1185( (s270*)this, ts, s1704, s1268 );}
else
s680 = s1357::s1178( s1540, l );
return s680;}
inline bool
s1370::s498( const s480* s499 ) const{
return ( s499->s349() == s349() );}
s270* s1370::s332( s588* s2041, s271* impl ) const{
return new s1370( *this );}
void s1370::s353( s270* p ) const{
p = new s1370( *this );}
size_t s1370::s319() const{
return (size_t)this;}
bool s1370::operator==( const s480* p ) const{
return ( this == p );}
bool s1370::operator<( const s480* p ) const{
return false;}
Iterator* s1370::s1175() {
auto it = begin( s346 );
return new s1371( s299, this, s346.begin(), ++it ); }
Iterator* s1370::s1179() {
return new s1371( s299, this, s346.end(), s346.end() ); }
#undef s691
#define s691 ((s1370*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
inline void s1370::s1226( s480** s273, size_t s495 ){
s1370* ps = (s1370*)DR;
s1370* s680 = NULL;
if( s495 == 2 ) {
s680 = (s1370*)( s273[1] )->s332( 0, ps->ns );}
else if( s273[2]->s1186().s349() == s1699 ) {
s680 = (s1370*)ps->s1524( s273[2] );}
else {
assert( 0 );
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 ) { return v.push_back( (s270*)s346 ); } );}
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s1370::s329( s480** s273, size_t s495 ){
s483 s151 = (s480*)PARN( 2 )->s494(0,0);
s1370* dr = (s1370*)DR;
s1374::iterator it = dr->s346.find( s151 );
if( it == dr->s346.end() ) {
s480* s1057 = (s480*)PARN( 3 );
if( dr->s1190 != s151->s349() || dr->s322 != s1057->s349() )
throw new s16( L"non-compatible types cannot be inserted to HashIndex" );
s483 s346 = s1057->s332(0,0)->s494(0,0);
dr->s346.insert( make_pair( s151, s346 ) );}
else
throw new s16( L"key already exists: " + s151->to_wstring() );}
inline void s1370::s1579( s480** s273, size_t s495 ){
s483 s151 = (s480*)PARN( 2 )->s494(0,0);
s480* s346 = (s480*)PARN( 3 );
s1370* dr = (s1370*)DR;
if( dr->s1190 != s151->s349() || dr->s322 != s346->s349() )
throw new s16( L"non-compatible types cannot be inserted to an HashIndex" );
s1374::iterator it = dr->s346.find( s151 );
if( it == dr->s346.end() ) {
s483 s1230 = (s480*)s346->s332(0,0)->s494(0,0);
s483 s1581 = (s480*)s151->s332(0,0);
dr->s346.insert( make_pair( s1581, s1230 ) );
*s273 = s366;}
else {
it->second = (s480*)s346->s332(0,0)->s494(0,0);
*s273 = s367;}}
inline void s1370::s773( s480** s273, size_t s495 ){
s1370* p = (s1370*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() )
*s273 = NULL;
else {
*s273 = new s951( p->s299, p->ns, vector<s270*>(
{ it->first.s15<s481*>(), it->second.s15<s481*>() } ) );}}
inline void s1370::s324( s480** s273, size_t s495 ){
s1370* p = (s1370*)DR;
s483 s1049 = (s480*)PARN( 2 )->s494(0,0);
s1374::iterator it = p->s346.find( s1049 );
if( it == p->s346.end() )
*s273 = NULL;
else {
*s273 = it->second.s15<s480*>();}}
inline void s1370::s1451( s480** s273, size_t s495 ){
s1370* p = (s1370*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() )
*s273 = (s480*)PARN( 3 )->s332( 0, 0 );
else {
*s273 = (s480*)it->second->s332( 0, 0 );
s273[0]->s1251();}}
inline void s1370::s384( s480** s273, size_t s495 ){
s480* s151 = (s480*)PARN( 2 );
s480* s346 = (s480*)PARN( 3 );
s1370* dr = (s1370*)DR;
if( dr->s1190 != s151->s349() || dr->s322 != s346->s349() )
throw new s16( L"non-compatible types cannot be inserted to an Index" );
s1374::iterator it = dr->s346.find( (s480*)PARN( 2 ) );
if( it == dr->s346.end() ) {
s480* s1230 = (s480*)s346->s332(0,0);
dr->s346.insert( make_pair( (s480*)s151->s332(0,0), s1230 ) );
*s273 = s366;}
else {
it->second = (s480*)s346->s332(0,0);
*s273 = s367;}}
inline void s1370::s330( s480** s273, size_t s495 ){
s1370* p = (s1370*)DR;
p->s346.erase( (s480*)PARN( 2 ) );}
inline void s1370::s325( s480** s273, size_t s495 ){}
inline void s1370::s328( s480** s273, size_t s495 ){}
Iterator* s1370::s311( s382* rv, bool s2295 ){
assert( !s2295 );
if( !rv )
return new s1371( s299, this, begin( s346 ), end( s346 ) );
s1134 pr = rv->s1184( this );
return new s1371( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
wstring s1370::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"{ ";
for( auto it = begin( s346 ); it != end( s346 ); ++it )
s680 += ( it == begin( s346 ) ? L"" : L", " ) + it->first->to_wstring() + L" : " +
it->second->to_wstring();
s680 += L" }";
return s680;}
void s1370::s1919( Stream* s1918 ) const{
s321::s2212( (s270*)this, s1918, ((s1370*)this)->s311(NULL) );}
void s1370::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"HashIndex : " << endl;
/*for( size_t n = 0; n < s346.size(); ++n )
s346[n]->s303( pd, s196 + s416 );*/
}
s2203::s2203( s261* s299, s271* s585, s1889& s77, const s262* ast_,
const s1680& s1744 )
: s1563( s299, s585, ast_ ){
if( s77.size() )
load( s77, s585, s1744 );
if( !s490 )
s490 = Types.Vector;}
s2203::s2203( const s2203& right, s271* _ns, const s262* ast_ )
: s1563( right.s299, _ns, ast_ ){
for( auto it = right.s346.begin(); it != right.s346.end(); ++it )
s346.insert( (s480*)(*it)->s332( NULL, _ns ));
s322 = right.s322;
s490 = right.s490;
s1664( right.s615() );}
s2203::s2203( s261* s299, const std::vector<s270*>& l,
s271* s585, const s262* ast_, s1053 s702, s1053 s1265 )
: s1563( s299, s585, ast_ ){
s322 = s1265;
if( s702 )
s490 = s702;
else
s490 = Types.Set;
if( l.size() ) {
if( l[0]->s349() == s349() || l[0]->s349() == s2206 ) {
s2202* ps = &( (s2203*)l[0] )->s346;
for( auto it = (*ps).begin(); it != (*ps).end(); ++it )
s346.insert( (s480*)( *it )->s332( NULL, ((s2203*)l[0])->ns ) );}
else if( l[0]->s349() == s1141 ) {
s346.insert( 0 );
s346.insert( new s356( s299, L"] " + l[0]->to_wstring() ) );}}}
s2203::s2203( s261* s299, s1053 s1266, s271* s585, const s262* ast_ )
: s1563( s299, s585, ast_ ){
s322 = s1266;
if( s1266 ) {
s806::Cont v = { s2206, 1, s322, 0 };
s490 = s299->TR().s1038( v );}}
void s2203::s1150( s1889& s77, s271* s585, const s1680& s1744 ){
assert( !s77.empty() );
wstring s1262, s641, s1255;
if( s77[0] == L'[' ) {
s1255 = s77;}
else {
s1151( s299, s77, s1262, s641 );
if( !s641.empty() && s641[0] == L'[' )
s1255 = s641;
if( !s1262.empty() ) {
s806::Cont s585;
s490 = s313::s1185( this, s1262, s2206, s585 );
s322 = s585[2];}}
if( !s1255.empty() ) {
load( s1255, s585, s1744 );}
else if( !s641.empty() ) {
if( s641[0] == L']' && s641.find_first_not_of(
s4::digits + s4::s48, 1 ) == string::npos ) {
s346.insert( 0 );
s346.insert( new s356( s299, s641, ns ) );}}}
s480*
s2203::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
s1053 pt = 0, vt = 0;
wstring sv;
if( !s313::s2210( (s323*)this, s2206, pt, vt, sv, s694, s585, s331 ) )
return NULL;
s2203* s680 = new s2203( s299, vector<s270*>( { } ), s585, &s694,
pt, vt );
s680->load( sv, s585, s1721 );
return s680;}
void s2203::load( s1889& s77, s271* s585, const s6::s1680& s1744 ){
TDException s960( s7::s1119, s925, s600() );
if( s77[0] == L']' ) {
s346.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s346.insert( s299->TR().s515( s322, s585, s585->s297() ) );
return;}
size_t pos = 0;
const s937* s1043 = NULL;
if( s600() && s600()->Nqj() )
s1043 = s600()->Nqj()->s998();
vector<s1::s9<s6::s140>> s93;
s6::s177( s1043, s77, pos, s93, s1744 );
wstring ownerName = s600()->s267( s2084 ).s168();
bool s1315 = false;
if( ( s600()->s267( s2085 ).s168() == L"CallSite" ) &&
( ownerName == s7::s1345 || ownerName.find( s7::s1345 + L"<" ) == 0 ) )
s1315 = true;
if( s93.size() ) {
s1053 pt = 0;
for( size_t n = 0; n < s93.size(); ++n ) {
s939 s224 = new s262( L"", *s93[n], NULL );
s224->s1333( s322 );
s270* s1057 = s270::s501( *s224, s299, s585, s585->s297() );
s346.insert( (s480*)s1057 );
if( s1057->s491() != s472 ) {
if( n == 0 )
pt = s1057->s349();
s1057->s2180( s2185 );}}
if( !s1315 ) {
auto it = s346.begin();
if( !s322 && (*it)->s349() ) {
s322 = ( *it )->s349();
s806::Cont v1 = { s1704, 1, s322, 0 };
s490 = s299->TR().s1038( v1 );}
else if( s322 != ( *it )->s349() )
throw s960.s992( L"vector's element type doesn't match the vector type" );}}}
void s2203::s497( const s271* s872, bool ){
wstring s77 = L"";
TDException s960( s7::s2199, s925, s600() );
s1374::iterator it = s346.begin();
if( s346.size() == 2 && it->s13() ) {
++it;
s77 = (*it)->to_wstring();}
if( s872->s491() != s473 ||
( (s271*)s872 )->s298() != s7::s1345 || s299->s1319() ) {
if( s77[0] == L']' ) {
s346.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s346.insert( s299->TR().s515( s322, (s271*)s872, s872->s827() ) );}
else {
for( it = s346.begin(); it != s346.end(); ++it ) {
s270* tmp = (*it).s15<s270*>();
if( tmp->s491() == s472 ) {
tmp->s497( s872, false );
tmp = ((s368*)tmp)->s374()->s332( NULL, NULL );}
s270* s1080 = s270::s1010( s299, tmp, (s271*)s872, (s588*)s872, s872->s297(), false );
s1080 = s1080->s494( 0, 0 ).s15<s481*>();
s346.erase( it );
s346.insert( (s480*)s1080 );
if( !s322 )
s322 = s1080->s349();
else if( s322 != s1080->s349() )
throw s960.s992( L"elements have different types" );}}
if( s490 || s490 == s2206 ) {
if( !s322 )
throw s960.s992( L"vector's element type is not specified" );
s806::Cont s585 = { s2206, 1, s322, 0 };
s490 = s299->TR().s1038( s585 );}
s1251();}}
void s2203::s347(){
s1563<s2202, s482, s2203>::s347();
s345 = s1563<s2202, s482, s2203>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s2203::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s345.emplace( make_pair( L"set", new s334( L"set", &s2203::s384, s1142,
{ s1112( { s1500::s1495 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"insert", new s334( L"insert", &s2203::s329, s1142,
{ s1112( { s7::s1385 } ) }, 1, 1, false ) ) );
s345.insert( make_pair( L"sort", new s334( L"sort", &s2203::s2227, 0,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.equal_range( s7::s1345 ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s2203::s352( s271* s585, const vector<s270*>& l, const s262* ast_ ) const{
if( !s322 )
throw new s16( L"set's element type is not specified" );
return new s2203( s299, l, s585, ast_, s490, s322 );}
s480* s2203::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s2203* s680 = new s2203( s299, 0, NULL );
s680->ns = s585;
s680->s322 = vt[2];
s806 s616( vt );
s680->s490 = s299->TR().s1003( s616 );
return s680;}
s1053 s2203::s1178( s1889& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" )
s680 = s322;
else if( s1540 == s7::s1345 || s1540 == L"sum" )
s680 = s490;
else
s680 = s1563::s1178( s1540, l );
return s680;}
inline bool
s2203::s498( const s480* s499 ) const{
return ( ( (s2203*)s499 )->s322 == s322 );}
s270* s2203::s332( s588* s2041, s271* impl ) const{
return new s2203( *this, impl, s600() );}
void s2203::s353( s270* p ) const{
s2203* pv = (s2203*)p;
pv->s346 = s346;
pv->s1664( wh );}
s480* s2203::s1524( const s480* p ) const{
if( s349() == p->s349() ) {
s480* s680 = (s480*)p->s332( 0, 0 );
return s680;}
else if( s299->TR().s1453( p->s349(), s1500::s1495 ) ) {
const s480* proto = s299->TR().s999( s314 );
s2203* s680 = (s2203*)p->s500()->s332( 0, ns );
s680->s490 = s490;
s680->s322 = s322;
if( proto->s491() == s475 ) {
Iterator* s1012 = ( (s323*)p )->s311( NULL );
while( 1 ) {
s482 s2167 = s1012->s312();
if( s2167.s13() )
break;
s680->s346.insert( proto->s352( ns, vector<s270*>( { s2167 } ), s600() ) );}}
s680->s1251();
return s680;}
throw new s16( L"no conversion from '" + s350() + L"' to '" + p->s350() + L"'" );}
size_t s2203::s319() const{
return (size_t)this;}
bool s2203::operator==( const s480* p ) const{
return ( this == p );}
bool s2203::operator<( const s480* p ) const{
return false;}
Iterator* s2203::s1175(){
auto it = begin( s346 );
return new s2204( s299, this, s346.begin(), ++it );}
Iterator* s2203::s1179(){
return new s2204( s299, this, s346.end(), s346.end() );}
#undef s691
#define s691 ((s2203*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
inline void s2203::s1226( s480** s273, size_t s495 ){
s2203* ps = (s2203*)DR;
s2203* s680 = NULL;
if( s495 == 2 ) {
s680 = (s2203*)( s273[1] )->s332( 0, 0 );}
else if( s273[2]->s1186().s349() == s2206 ) {
s680 = (s2203*)( s273[2] )->s332( 0, 0 );}
else {
assert( 0 );
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 ) { return v.push_back( (s270*)s346 ); } );}
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s2203::s384( s480** s273, size_t s495 ){
s2203* v = ( (s2203*)DR );
s323* seq = (s323*)s273[2];
Iterator* s1012 = seq->s311( NULL );
v->s346.clear();
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
v->s346.insert( p.s15<s480*>() );}}
inline void s2203::s329( s480** s273, size_t s495 ){
s480* s346 = (s480*)PARN( 2 );
s2203* dr = (s2203*)DR;
if(  dr->s322 != s346->s349() )
throw new s16( L"non-compatible types cannot be inserted into a Set" );
dr->s346.insert( s346 );}
inline void s2203::s773( s480** s273, size_t s495 ){
s2203* p = (s2203*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() )
*s273 = NULL;
else {
*s273 = it->s15<s480*>();}}
inline void s2203::s2227( s480** s273, size_t s495 ){
throw new s16( L"method is not implemented" );}
Iterator* s2203::s311( s382* rv, bool s2295 ){
if( !rv ) {
if( !s2295 )
return new s2204( s299, this, begin( s346 ), end( s346 ) );
else
return new s2204( s299, this, rbegin( s346 ), rend( s346 ) );}
s1134 pr = rv->s1184( this );
return new s2204( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
wstring s2203::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[ ";
for( auto it = begin( s346 ); it != end( s346 ); ++it )
s680 += ( it == begin( s346 ) ? L"" : L", " ) + it->s15<s480*>()->to_wstring();
s680 += L" ]";
return s680;}
void s2203::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
bool s2056 = s1918->s2051();
s1918->s2050();
ss << L"[";
if( s615() == s7::s861 )
ss << L"_not_set_";
else {
for( auto it = begin( s346 ); it != end( s346 ); ++it ) {
if( it != begin( s346 ) )
ss << L", ";
it->s15<s480*>()->s1919( s1918 );}}
ss << L"]";
if( !s2056 )
s1918->s2049();}
void s2203::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Set : " << this << endl;
for( auto it = s346.begin(); it != s346.end(); ++it ) {
(*it)->s303( pd, s196 + s416 );
buf << endl;}}
s2236::s2236( s261* s299, s271* s585, s1889& s77, const s262* ast_,
const s1680& s1744 )
: s1563( s299, s585, ast_ ){
if( s77.size() )
s313::load( this, s2239, s77, s585, s1744, s490, s322, 
[this]( s483 pr ) {this->s346.insert( pr ); } );
if( !s490 )
s490 = Types.Vector;}
s2236::s2236( const s2236& right, s271* _ns, const s262* ast_ )
: s1563( right.s299, _ns, ast_ ){
for( auto it = right.s346.begin(); it != right.s346.end(); ++it )
s346.insert( (s480*)(*it)->s332( NULL, _ns ));
s322 = right.s322;
s490 = right.s490;
s1664( right.s615() );}
s2236::s2236( s261* s299, const std::vector<s270*>& l,
s271* s585, const s262* ast_, s1053 s702, s1053 s1265 )
: s1563( s299, s585, ast_ ){
s322 = s1265;
if( s702 )
s490 = s702;
else
s490 = Types.HashSet;
if( l.size() ) {
if( l[0]->s349() == s349() || l[0]->s349() == s2239 ) {
s2235* ps = &( (s2236*)l[0] )->s346;
for( auto it = (*ps).begin(); it != (*ps).end(); ++it )
s346.insert( (s480*)( *it )->s332( NULL, ((s2236*)l[0])->ns ) );}
else if( l[0]->s349() == s1141 ) {
s346.insert( 0 );
s346.insert( new s356( s299, L"] " + l[0]->to_wstring() ) );}}}
s2236::s2236( s261* s299, s1053 s1266, s271* s585, const s262* ast_ )
: s1563( s299, s585, ast_ ){
s322 = s1266;
if( s1266 ) {
s806::Cont v = { s2239, 1, s322, 0 };
s490 = s299->TR().s1038( v );}}
s480*
s2236::s351( const s262& s694, s271* s585, const std::wstring& s331 ) const{
s1053 pt = 0, vt = 0;
wstring sv;
if( !s313::s2210( (s323*)this, s2239, pt, vt, sv, s694, s585, s331 ) )
return NULL;
s2236* s680 = new s2236( s299, vector<s270*>( { } ), s585, &s694,
pt, vt );
s313::load( s680, s2239, sv, s585, s1721, s680->s490, s680->s322,
[s680]( s483 pr ) {s680->s346.insert( pr ); } );
return s680;}
void s2236::s497( const s271* s872, bool ){
wstring s77 = L"";
TDException s960( s7::s2233, s925, s600() );
s1374::iterator it = s346.begin();
if( s346.size() == 2 && it->s13() ) {
++it;
s77 = (*it)->to_wstring();}
if( s872->s491() != s473 ||
( (s271*)s872 )->s298() != s7::s1345 || s299->s1319() ) {
if( s77[0] == L']' ) {
s346.clear();
wstring snum = s77.substr( s77.rfind( L" " ) );
size_t s162 = std::stoi( snum );
for( size_t n = 0; n < s162; ++n )
s346.insert( s299->TR().s515( s322, (s271*)s872, s872->s827() ) );}
else {
for( it = s346.begin(); it != s346.end(); ++it ) {
s270* tmp = (*it).s15<s270*>();
if( tmp->s491() == s472 ) {
tmp->s497( s872, false );
tmp = ((s368*)tmp)->s374()->s332( NULL, NULL );}
s270* s1080 = s270::s1010( s299, tmp, (s271*)s872, (s588*)s872, s872->s297(), false );
s1080 = s1080->s494( 0, 0 ).s15<s481*>();
s346.erase( it );
s346.insert( (s480*)s1080 );
if( !s322 )
s322 = s1080->s349();
else if( s322 != s1080->s349() )
throw s960.s992( L"elements have different types" );}}
if( s490 || s490 == s2239 ) {
if( !s322 )
throw s960.s992( L"hashset's element type is not specified" );
s806::Cont s585 = { s2239, 1, s322, 0 };
s490 = s299->TR().s1038( s585 );}
s1251();}}
void s2236::s347(){
s1563<s2235, s482, s2236>::s347();
s345 = s1563<s2235, s482, s2236>::s339();
s345.emplace( make_pair( s7::s1345, new s334( s7::s1345, &s2236::s1226, s1142,
{ s1112(), s1112( { s7::s1381, s7::s1387 } ) }, 0, 0, false, { L":typedTable", L":untypedTable" } ) ) );
s345.emplace( make_pair( L"set", new s334( L"set", &s2236::s384, s1142,
{ s1112( { s1500::s1495 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"insert", new s334( L"insert", &s2236::s329, s1142,
{ s1112( { s7::s1385 } ) }, 1, 1, false ) ) );
s345.emplace( make_pair( L"sort", new s334( L"sort", &s2236::s2227, 0,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.emplace( make_pair( L"is-sorted", new s334( L"is-sorted", &s2236::s2227, 0,
{ s1112( {  s7::s1381, s7::s1387 } ) }, 0, 1 ) ) );
s345.equal_range( s7::s1345 ).first->second->s1250( true );
s299->TR().s1152( s490, s7::s1398, s1500::s1494 );
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );}
s480* s2236::s352( s271* s585, const vector<s270*>& l, const s262* ast_ ) const{
if( !s322 )
throw new s16( L"hashset's element type is not specified" );
return new s2236( s299, l, s585, ast_, s490, s322 );}
s480* s2236::s352( s271* s585, const std::vector<s1053>& vt ) const{
size_t n = vt[1];
assert( n == 1 );
s2236* s680 = new s2236( s299, 0, NULL );
s680->ns = s585;
s680->s322 = vt[2];
s806 s616( vt );
s680->s490 = s299->TR().s1003( s616 );
return s680;}
s1053 s2236::s1178( s1889& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get" )
s680 = s322;
else if( s1540 == s7::s1345 || s1540 == L"sum" )
s680 = s490;
else
s680 = s1563::s1178( s1540, l );
return s680;}
inline bool
s2236::s498( const s480* s499 ) const{
return ( ( (s2236*)s499 )->s322 == s322 );}
s270* s2236::s332( s588* s2041, s271* impl ) const{
return new s2236( *this, impl, s600() );}
void s2236::s353( s270* p ) const{
s2236* pv = (s2236*)p;
pv->s346 = s346;
pv->s1664( wh );}
s480* s2236::s1524( const s480* p ) const{
if( s349() == p->s349() ) {
s480* s680 = (s480*)p->s332( 0, 0 );
return s680;}
else if( s299->TR().s1453( p->s349(), s1500::s1495 ) ) {
const s480* proto = s299->TR().s999( s314 );
s2236* s680 = (s2236*)p->s500()->s332( 0, ns );
s680->s490 = s490;
s680->s322 = s322;
if( proto->s491() == s475 ) {
Iterator* s1012 = ( (s323*)p )->s311( NULL );
while( 1 ) {
s482 s2167 = s1012->s312();
if( s2167.s13() )
break;
s680->s346.insert( proto->s352( ns, vector<s270*>( { s2167 } ), s600() ) );}}
s680->s1251();
return s680;}
throw new s16( L"no conversion from '" + s350() + L"' to '" + p->s350() + L"'" );}
size_t s2236::s319() const{
return (size_t)this;}
bool s2236::operator==( const s480* p ) const{
return ( this == p );}
bool s2236::operator<( const s480* p ) const{
return false;}
Iterator* s2236::s1175(){
auto it = begin( s346 );
return new s2237( s299, this, s346.begin(), ++it );}
Iterator* s2236::s1179(){
return new s2237( s299, this, s346.end(), s346.end() );}
#undef s691
#define s691 ((s2236*)(s481*)*s273)
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
inline void s2236::s1226( s480** s273, size_t s495 ){
s2236* ps = (s2236*)DR;
s2236* s680 = NULL;
if( s495 == 2 ) {
s680 = (s2236*)( s273[1] )->s332( 0, 0 );}
else if( s273[2]->s1186().s349() == s2239 ) {
s680 = (s2236*)( s273[2] )->s332( 0, 0 );}
else {
assert( 0 );
vector<s270*> v;
for_each( s273 + 2, s273 + s495, [&v]( s480* s346 ) { return v.push_back( (s270*)s346 ); } );}
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s2236::s384( s480** s273, size_t s495 ){
s2236* v = ( (s2236*)DR );
s323* seq = (s323*)s273[2];
Iterator* s1012 = seq->s311( NULL );
v->s346.clear();
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
v->s346.insert( p.s15<s480*>() );}}
inline void s2236::s329( s480** s273, size_t s495 ){
s480* s688 = (s480*)PARN( 2 );
s2236* dr = (s2236*)DR;
if(  dr->s322 != s688->s349() )
throw new s16( L"non-compatible types cannot be inserted into a HashSet" );
dr->s346.insert( (s270*)s688 );}
inline void s2236::s773( s480** s273, size_t s495 ){
s2236* p = (s2236*)DR;
s1374::iterator it = p->s346.find( (s480*)PARN( 2 ) );
if( it == p->s346.end() )
*s273 = NULL;
else {
*s273 = it->s15<s480*>();}}
inline void s2236::s2227( s480** s273, size_t s495 ){
throw new s16( L"method is not implemented" );}
Iterator* s2236::s311( s382* rv, bool s2295 ){
assert( !s2295 );
if( !rv )
return new s2237( s299, this, begin( s346 ), end( s346 ) );
s1134 pr = rv->s1184( this );
return new s2237( s299, this,
pr.first.s15<s1129*>()->s1135(), pr.second.s15<s1129*>()->s1135() );}
wstring s2236::to_wstring( uint32_t s1552 ) const{
wstring s680 = L"[ ";
for( auto it = begin( s346 ); it != end( s346 ); ++it )
s680 += ( it == begin( s346 ) ? L"" : L", " ) + it->s15<s480*>()->to_wstring();
s680 += L" ]";
return s680;}
void s2236::s1919( Stream* s1918 ) const{
s1488& ss = s1918->s1948();
bool s2056 = s1918->s2051();
s1918->s2050();
ss << L"[";
if( s615() == s7::s861 )
ss << L"_not_set_";
else {
for( auto it = begin( s346 ); it != end( s346 ); ++it ) {
if( it != begin( s346 ) )
ss << L", ";
it->s15<s480*>()->s1919( s1918 );}}
ss << L"]";
if( !s2056 )
s1918->s2049();}
void s2236::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"HashSet : " << this << endl;
for( auto it = s346.begin(); it != s346.end(); ++it ) {
(*it)->s303( pd, s196 + s416 );
buf << endl;}}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
s412::s412( s261* s299, s1889& s77, const s262* ast_ )
: s333( s299, NULL, ast_ ), s747( s299, Types.String, NULL ), s802( s299, Types.String, NULL ){
s490 = Types.s411;
s747.s11();
s802.s11();
s747.s1251();
s802.s1251();}
s412::s412( const s412& right, const s262* ast_ )
: s333( right.s299, right.ns, ast_ ), s747( right.s299, NULL, L"" ), s802( right.s299, NULL, L"" ){
s747 = right.s747;
s802 = right.s802;
s747.s1251();
s802.s1251();
s490 = right.s490;}
s480* s412::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return new s412( s299, L"", &s694 );}
void s412::s497( const s271* s872, bool ){
s1251();}
void s412::s347(){
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, Types.String )->s350() + L">";
s1053 s1505 = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s412::s1226, s1891,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"read", new s334( L"read", &s412::s406, s1142,
{ s1112( { Types.String, Types.String } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"read-rec", new s334( L"read-rec", &s412::s1662, s1142,
{ s1112( { Types.String, Types.String } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"reset", new s334( L"reset", &s412::s413, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"files", new s334( L"files", &s412::s414, s1505,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"dirs", new s334( L"dirs", &s412::s982, s1505,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s412::s325, s1141,
{ s1112() }, 0, 0 ) ) );}
s480* s412::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s412( s299, L"", ast_ );}
inline bool
s412::s498( const s480* s499 ) const{
return ( ((s412*)s499)->s349() == s349() );}
s270* s412::s332( s588* s2041, s271* impl ) const{
return s482( new s412( *this ) );}
void s412::s353( s270* p ) const{
p = new s412( *this );}
#undef s691
#define s691 ((s412*)(s481*)*s273)
inline void s412::s1226( s480** s273, size_t s495 ){
s412* s775 = (s412*)DR;
s412* s680 = new s412( s775->s299, L"", s775->s600() );
s680->s497( s775->ns, true );
*s273 = s680;}
void _findFiles( s1889& path, const wregex& rgPatt, vector<wstring>& s40,	vector<wstring>& s41 ){
vector<wstring> s781, s789;
s3::s32( path, L".*", s781, s789 );
for( size_t n = 0; n < s781.size(); ++n ) {
wstring s1661 = path + s781[n];
if( regex_match( s1661, rgPatt ) ) 
s40.push_back( s1661 );}
for( size_t n = 0; n < s789.size(); ++n ) {
if( s789[n] == L".." ||  s789[n] == L"." )
continue;
wstring s1661 = path + s789[n];
s41.push_back( s1661 );
s4::s61( s1661 );
_findFiles( s1661, rgPatt, s40, s41 );}}
inline void s412::s406( s480** s273, size_t s495 ){
wstring path = ((s356*)PARN( 2 ) )->to_wstring();
const wstring& s521 = ((s356*)PARN( 3 ))->to_wstring();
vector<wstring> s781, s789;
s412* s775 = (s412*)DR;
s775->s747.clear();
s775->s802.clear();
if( !s3::s717( path ) )
path = s775->s299->s709() + path;
s4::s61( path );
s3::s32( path, s521, s781, s789 );
std::sort( begin( s781 ), end( s781 ) );
std::sort( begin( s789 ), end( s789 ) );
for( auto f : s781 )
s775->s747.add( new s356( s775->s299, s4::s739( path + f ), s775->ns ) );
for( auto f : s789 )
s775->s802.add( new s356( s775->s299, s4::s739( path + f ), s775->ns ) );}
inline void s412::s1662( s480** s273, size_t s495 ){
wstring path = ( (s356*)PARN( 2 ) )->to_wstring();
const wstring& s521 = ( (s356*)PARN( 3 ) )->to_wstring();
wregex rg( s521 );
vector<wstring> s781, s789;
s412* s775 = (s412*)DR;
s775->s747.clear();
s775->s802.clear();
if( !s3::s717( path ) )
path = s775->s299->s709() + path;
s4::s61( path );
_findFiles( path, rg, s781, s789 );
std::sort( begin( s781 ), end( s781 ) );
std::sort( begin( s789 ), end( s789 ) );
for( auto f : s781 )
s775->s747.add( new s356( s775->s299, s4::s739( f ), s775->ns ) );
for( auto f : s789 )
s775->s802.add( new s356( s775->s299, s4::s739( f ), s775->ns ) );}
inline void s412::s413( s480** s273, size_t s495 ){
s412* s775 = (s412*)DR;
s775->s747.clear();
s775->s802.clear();}
inline void s412::s414( s480** s273, size_t s495 ){
*s273 = &( (s412*)DR )->s747;}
inline void s412::s982( s480** s273, size_t s495 ){
*s273 = &( (s412*)DR )->s802;}
inline void s412::s325( s480** s273, size_t s495 ){
s412* s775 = (s412*)DR;
*( (s343*)*s273 )->s354() = (int)(s775->s747.size() + s775->s802.size());}
wstring s412::to_wstring( uint32_t s1552 ) const{
wstring s680;
for( size_t n = 0; n < s802.size(); ++n )
s680 += ( n ? L" \"" : L"\"" ) + s802[n]->to_wstring() + L"\"";
for( size_t n = 0; n < s747.size(); ++n )
s680 += ( n ? L" \"":L"\"") + s747[n]->to_wstring() + L"\"";
return s680;}
void s412::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Directory : " << endl;
for( size_t n = 0; n < s802.size(); ++n )
s802[n]->s303( pd, s196 + s416 );
for( size_t n = 0; n < s747.size(); ++n )
s747[n]->s303( pd, s196 + s416 );}
size_t s412::s319() const{
size_t s680 = 0;
for( size_t n = 0; n < s802.size(); ++n )
s680 = s680 * ( (s480*)&(s802[n]) )->s319() << 1;
for( size_t n = 0; n < s747.size(); ++n )
s680 = s680 * ( (s480*)&(s747[n]) )->s319() << 1;
return s680;}
bool s412::operator==( const s480* p ) const{
if( ( (s412*)p )->s747.size() != s747.size() )
return false;
if( ( (s412*)p )->s802.size() != s802.size() )
return false;
for( size_t n = 0; n < s747.size(); ++n )
if( !( ( s270* )&( *s747[n] ) == (s270*)( (s412*)p )->s747[n] ) )
return false;
for( size_t n = 0; n < s802.size(); ++n )
if( !( ( s270* )&( *s802[n] ) == (s270*)( (s412*)p )->s802[n] ) )
return false;
return true;}
bool s412::operator<( const s480* p ) const{
return false;}
vector<wstring> s1593( { L":append" } );
s1592::s1592( s261* s299, s271* s589, s588* s590,
const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1603, s694 ){
if( l.size() < 1 || l.size() > 2 )
throw new s16( L"malformed syntax of 'read-tsd-file' procedure call" );
s273.assign( l.begin(), l.end() );
s490 = s1142;
s588::s1231( ( vector<s270*>& )l, s1593 );}
void
s1592::s497( const s271* s1657, bool proc ){
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, Types.s271 )->s350() + L">";
s490 = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s588::s497( s1657, proc );}
s483 s1592::s494( s480** s686, size_t s690 ){
s1598( s686, s690 );
s313* pv = s583.s15<s313*>();
wstring s193 = s580[1]->to_wstring();
s193 = s4::s739( s193 );
vector<s9<s142>> s659;
s940 s1043 = new s937( s193 );
s1043->read( s659, /*s7::s1096*/ L"" );
for( size_t m = 0; m < s659.size(); m++ ) {
s1589* po = new s1589( pv->Pass(), this, s659[m], NULL );
pv->add( po );}
return s583;}
s270* s1592::s332( s588* s2041, s271* impl ) const{
return new s1592( *this );}
s1053 s1500::s1493 = 0;
s1053 s1500::s1497 = 0;
s1053 s1500::s1492 = 0;
void Stream::s1449( std::wstring& s152, size_t s1460 ){
throw new s2::s16( L"stream method is not implemented: get_text" );}
void Stream::s1468( s1889& src ){
throw new s2::s16( L"stream method is not implemented: put_text" );}
void Stream::s1450( std::wstring& s152, s1889& s72 ){
throw new s2::s16( L"stream method is not implemented: get_text_line" );}
void Stream::s1469( s1889& src ){
throw new s2::s16( L"stream method is not implemented: put_text_line" );}
void Stream::s1448( s1311& s152, size_t s1460 ){
throw new s2::s16( L"stream method is not implemented: get_bytes" );}
void Stream::s1467( const s1311& src ){
throw new s2::s16( L"stream method is not implemented: put_bytes" );}
void Stream::s1447( s1311& s152, const s1311& s72 ){
throw new s2::s16( L"stream method is not implemented: get_byte_line" );}
void Stream::s1466( const s1311& src ){
throw new s2::s16( L"stream method is not implemented: put_byte_line" );}
void Stream::rewind(){
throw new s2::s16( L"stream method is not implemented: rewind" );}
void Stream::s1897( wchar_t c ){
throw new s2::s16( L"stream method is not implemented: fill" );}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1554(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1463 )
*s1463 << std::resetiosflags( f );}
template<class s1408, class s1410>
Stream::s1908 s1394<s1408, s1410>::s1914() const{
return s1463->flags();}
template<class s1408, class s1410>
Stream::s1909 s1394<s1408, s1410>::s1915() const{
return s1463->precision();}
template<class s1408, class s1410>
bool s1394<s1408, s1410>::s2051() const{
return s2057;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1913(){
if( s1463 )
*s1463 << std::showpos;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1911(){
if( s1463 )
*s1463 << std::noshowpos;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s2050(){
s2057 = true;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s2049(){
s2057 = false;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1941(){
if( s1463 )
*s1463 << std::boolalpha;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1942(){
if( s1463 )
*s1463 << std::noboolalpha;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1555( int n ){
if( s1463 )
*s1463 << std::setw( n );}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1912( int n ){
if( s1463 )
*s1463 << std::setprecision( n );}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1899(){
if( s1463 )
*s1463 << std::left;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1900(){
if( s1463 )
*s1463 << std::right;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1898(){
if( s1463 )
*s1463 << std::internal;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1910(){
if( s1463 )
*s1463 << std::fixed;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1553(){
if( s1463 )
*s1463 << std::showpos;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1939(){
std::ios_base::fmtflags f = (std::ios_base::fmtflags) 0;
if( s1462 )
*s1462 >> std::resetiosflags( f );}
template<class s1408, class s1410>
Stream::s1908 s1394<s1408, s1410>::s1945() const{
return s1462->flags();}
template<class s1408, class s1410>
Stream::s1909 s1394<s1408, s1410>::s1946() const{
return s1462->precision();}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1935(){
if( s1462 )
*s1462 >> std::boolalpha;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1937(){
if( s1462 )
*s1462 >> std::noboolalpha;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1936(){
if( s1462 )
*s1462 >> std::fixed;}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1940( int n ){
if( s1462 )
*s1462 >> std::setw( n );}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1938( int n ){
if( s1462 )
*s1462 >> std::setprecision( n );}
s504::s504( s261* s299, s271* ns_, const s262* ast_ )
: s1394( s299, ns_, ast_ ){
s490 = Types.s782;
s1462 = (basic_istringstream<wchar_t>*) &ss;
s1463 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s504::s504( const s504& r, const s262* ast_ )
: s1394( r.s299, r.ns, ast_ ), ss( r.ss.str() ){
s490 = Types.s782;
s1462 = (basic_istringstream<wchar_t>*) &ss;
s1463 = (basic_ostringstream<wchar_t>*) &ss;
ss.imbue( std::locale( "C" ) );}
s480* s504::s352( s271* s585, const std::vector<s270*>&, const s262* ast_ ) const{
return new s504( s299, s585, ast_ );}
void s504::s347(){
s1394<s1955,s1956>::s347();
s345 = s1394<s1955, s1956>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s504::s1226, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"str", new s334( L"str", &s504::s505, Types.String,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", &s504::s327, s1894,
{ s1112() }, 0, 0 ) ) );
s299->TR().s1152( s490, s7::s1397, s1500::s1493 );
s299->TR().s1152( s490, s7::s1402, s1500::s1497 );
s299->TR().s1152( s490, s7::s1396, s1500::s1492 );}
void s504::s497( const s271*, bool ){
s1251();}
void s504::release(){
ss.clear();}
s480* s504::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s_ = s694.s290();
if( s_.find( L"StringStream(" ) == 0 )
return new s504( s299, s585, &s694 );
return NULL;}
s270* s504::s332( s588* s2041, s271* impl ) const{
return new s504( *this );}
void s504::s353( s270* p ) const{
if( p->s349() == s1894 )
((s504*)p)->ss.rdbuf()->str( ss.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s349() ) );}
void s504::s1449( std::wstring& s152, size_t s1460 ){
s152 = ss.str().substr( 0, s1460 );}
void s504::s1468( s1889& src ){
ss << src;}
void s504::s1450( std::wstring& s152, s1889& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s152.clear();
std::getline( ss, s152, s72[0] );}
void s504::s1469( s1889& src ){
ss << src << endl;}
void s504::s1448( s1311& s152, size_t s1460 ){
s152 = (tdbyte_t*)U8( ss.str().substr( 0, s1460 )).data();}
void s504::s1467( const s1311& src ){
ss << U16( (char*)src.c_str() );}
void s504::s1447( s1311& s152, const s1311& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + 
U16((char*)s72.c_str()) + L"'" );
s152.clear();
wstring tmp;
std::getline( ss, tmp, U16((char*)s72.c_str())[0]);}
void s504::s1466( const s1311& src ){
ss << U16( (char*)src.c_str() ) << endl;}
void s504::s1897( wchar_t c ){
if( s1463 )
*s1463 << std::setfill( c );}
wstring s504::to_wstring( uint32_t s1552 ) const{
return ss.str(); }
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s504*)(s481*)*s273)
inline void s504::s1226( s480** s273, size_t s495 ){
s504* ps = (s504*)DR;
s504* s680 = new s504( ps->s299, ps->ns, ps->s600() );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s504::s505( s480** s273, size_t s495 ){
s504* pst = (s504*)DR;
*( (s356*)s273[0] )->s354() = pst->ss.str();}
inline void s504::s327( s480** s273, size_t s495 ){
((s504*)DR)->ss.rdbuf()->str(L"");}
void s504::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << ss.str() << endl;}
size_t s504::s319() const{
return hash<wstring>{}(ss.str());}
bool s504::operator==( const s480* p ) const{
return ( (s504*)p )->ss.str() == ss.str();}
bool s504::operator<( const s480* p ) const{
return ss.str() < ( (s504*)p )->ss.str();}
s1283::s1283( s261* s299, s271* ns_, const s262* ast_ )
: s1394( s299, ns_, ast_ ){
s490 = Types.ByteStream;
s1462 = (basic_istringstream<tdbyte_t>*) &bs;
s1463 = (basic_ostringstream<tdbyte_t>*) &bs;}
s1283::s1283( const s1283& r, const s262* ast_ )
: s1394( r.s299, r.ns, ast_ ), bs( r.bs.str() ){
s490 = Types.ByteStream;}
s480* s1283::s352( s271* s585, const std::vector<s270*>&, const s262* ast_ ) const{
return new s1283( s299, ast_ );}
void s1283::s347(){
s1394<s1483, s1486>::s347();
s345 = s1394<s1483, s1486>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1283::s1226, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"array", new s334( L"array", &s1283::s1304, Types.String,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"clear", new s334( L"clear", &s1283::s327, s1890,
{ s1112() }, 0, 0 ) ) );
s299->TR().s1152( s490, s7::s1397, s1500::s1493 );
s299->TR().s1152( s490, s7::s1402, s1500::s1497 );
s299->TR().s1152( s490, s7::s1396, s1500::s1492 );}
void s1283::s497( const s271*, bool ){
s1251();}
void s1283::release(){
bs.clear();}
s480* s1283::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s_ = s694.s290();
if( s_.find( L"ByteStream(" ) == 0 )
return new s1283( s299 );
return NULL;}
s270* s1283::s332( s588* s2041, s271* impl ) const{
return new s1283( *this );}
void s1283::s353( s270* p ) const{
if( p->s349() == s1890 )
((s1283*)p)->bs.rdbuf()->str( bs.str() );
else
throw new s16( L"No conversion to type " + std::to_wstring( p->s349() ) );}
void s1283::s1449( std::wstring& s152, size_t s1460 ){
s152 = U16( (char*)bs.str().c_str() ).substr( 0, s1460 );}
void s1283::s1468( s1889& src ){
bs << (tdbyte_t*)U8( src ).c_str();}
void s1283::s1450( std::wstring& s152, s1889& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
s152.clear();
s1311 tmp;
std::getline( bs, tmp, (unsigned char)U8(s72.data())[0] );}
void s1283::s1469( s1889& src ){
bs << (tdbyte_t*)U8(src).c_str() << endl;}
void s1283::s1448( s1311& s152, size_t s1460 ){
s152 = bs.str().substr( 0, s1460 );}
void s1283::s1467( const s1311& src ){
bs << src.data();}
void s1283::s1447( s1311& s152, const s1311& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16((char*)s72.c_str()) + L"'" );
s152.clear();
std::getline( bs, s152, s72[0] );}
void s1283::s1466( const s1311& src ){
bs << src << endl;}
wstring s1283::to_wstring( uint32_t s1552 ) const{
s1311 s = bs.str();
string s1( s.size(), 0 );
for( size_t n = 0; n < s.size(); ++n ) s1[n] = s[n];
return U16( s1 );}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s1283*)(s481*)*s273)
inline void s1283::s1226( s480** s273, size_t s495 ){
s1283* ps = (s1283*)DR;
s1283* s680 = new s1283( ps->s299, ps->s600() );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s1283::s1304( s480** s273, size_t s495 ){
s1311 s = ( (s1283*)DR)->bs.str();
( (s1281*)s273[0] )->s317().assign( begin( s ), end( s ) );}
inline void s1283::s327( s480** s273, size_t s495 ){
((s1283*)DR)->bs.rdbuf()->str(0);}
void s1283::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : [...]" << endl;}
size_t s1283::s319() const{
return hash<uint64_t>{}( (uint64_t)this );}
bool s1283::operator==( const s480* p ) const{
return ( (s1283*)p )->bs.str() == bs.str();}
bool s1283::operator<( const s480* p ) const{
return bs.str() < ( (s1283*)p )->bs.str();}
s1291::s1291( s261* s299, s271* ns_, const s262* ast_ )
: s1394( s299, ns_, ast_ ){
s490 = Types.FileStream;
s1462 = NULL;
s1463 = NULL;}
s1291::s1291( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ )
: s1394( s299, s585, ast_ ){
s490 = Types.FileStream;
s1462 = NULL;
s1463 = NULL;
if( l.size() ) {
if( l[0]->s349() == Types.String )
s1330 = l[0]->to_wstring();
else
s209 = l[0];}
if( l.size() == 2 )
mode = l[1];}
s1291::s1291( const s1291& r, const s262* ast_ )
: s1394( r.s299, r.ns, ast_ ), s209( r.s209 ), mode( r.mode ){
s490 = s1892;
s1462 = NULL;
s1463 = NULL;}
s480* s1291::s352( s271* s585, const std::vector<s270*>&, const s262* ast_ ) const{
return new s1291( s299, ast_ );}
void s1291::s347(){
s1394<s1484, s1487>::s347();
s345 = s1394<s1484, s1487>::s339();
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1291::s1226, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"open-r", new s334( L"open-r", &s1291::s2012, s1142,
{ s1112(), s1112( { Types.String } ), s1112( { Types.String, Types.String } ) }, false, s2034 ) ) );
s345.insert( make_pair( L"open-w", new s334( L"open-w", &s1291::s2014, s1142,
{ s1112(), s1112( { Types.String } ), s1112( { Types.String, Types.String } ) }, false, s2034 ) ) );
s345.insert( make_pair( L"open-rw", new s334( L"open-rw", &s1291::s2013, s1142,
{ s1112(), s1112( { Types.String } ), s1112( { Types.String, Types.String } ) }, 0, 2 ) ) );
s345.insert( make_pair( L"close", new s334( L"close", &s1291::s1313, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"read-bytes", new s334( L"read-bytes", &s1291::s2020, s1142,
{ s1112( { s1139 } ), s1112( { s1139, s1141 } ) }, 2, 2 ) ) );
s345.insert( make_pair( L"read-lines", new s334( L"read-lines", &s1291::s1472, 0,	
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"read-text", new s334( L"read-text", &s1291::s406, Types.String,	
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"write", new s334( L"write", &s1291::s1344, s1142,
{ s1112( { s1139, s1141 } ) }, 2, 2 ) ) );
s299->TR().s1152( s490, s7::s1397, s1500::s1493 );
s299->TR().s1152( s490, s7::s1402, s1500::s1497 );
s299->TR().s1152( s490, s7::s1396, s1500::s1492 );}
void s1291::s497( const s271*, bool ){
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, Types.String )->s350() + L">";
s1053 pt = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s345.equal_range( L"read-lines" ).first->second->s1252( pt );
s1251();}
void s1291::release(){
fs.close();}
s480*
s1291::s351( const s262& s694, s271* s585, s1889& s331 ) const{
wstring s_ = s694.s290();
if( s_.find( L"FileStream(" ) == 0 ) {
vector<s270*> s698;
s270::s1322( s694, s299, s585, s331, s698 );
return new s1291( s299, s698, s585, &s694 );}
return NULL;}
s270*
s1291::s332( s588* s2041, s271* impl ) const{
return new s1291( *this );}
void s1291::s353( s270* p ) const{
if( p->s349() == s1892 ) {
((s1291*)p)->s209 = s209;
((s1291*)p)->mode = mode;}
else
throw new s16( L"No conversion from " + s350() + L" to " + 
p->s350() );}
void s1291::s1449( std::wstring& s152, size_t s1460 ){
size_t s1101 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios_base::end ).tellg() - s1101;
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
enc = s1675;}
else if( c1 == 0xFE && c2 == 0xFF ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1676;}
else if( c1 == 0xFF && c2 == 0xFE ) {
fs.seekg( 2, ios_base::beg );
fsz -= 2;
enc = s1677;}
else if( c1 == 0x0 && c2 == 0x0 && c3 == 0xFE && c4 == 0xFF ) {
enc = s1678;
fsz -= 4;}
else if( c1 == 0xFF && c2 == 0xFE && c3 == 0x0 && c4 == 0x0 ) {
enc = s1679;
fsz -= 4;}
else
fs.seekg( 0, ios_base::beg );}
size_t s1491 = s1460 ? ( std::min )( s1460, fsz ) : fsz;
string buf( s1491 + 0, '\0' );
fs.read( &buf[0], s1491 );
if( !fs.good() ) {
fs.close();
throw new s16( L"could not read file '" + s1330 + L"'" );}
if( !enc || enc == s1675 ) {
s152 = U16( buf );
s152.shrink_to_fit();}
else {
fs.close();
throw new s16( L"file is not in UTF8 encoding and cannot be read as text: '" + s1330 + L"'" );}}
void s1291::s1468( s1889& src ){
fs << U8(src).data();}
void s1291::s1450( std::wstring& s152, s1889& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-char line separators are not supported: '" + s72 + L"'" );
if( !fs )
throw new s16( L"file stream is not valid" );
s152.clear();
if( fs.eof() )
return;
string buf;
char s1459 = U8( s72.data() )[0];
std::getline( fs, buf, s1459 );
s152 = U16( buf.data() );}
void s1291::s1469( s1889& src ){
fs << U8(src).data() << endl;}
void s1291::s1448( s1311& s152, size_t s1460 ){
size_t s1101 = fs.tellg();
size_t fsz = (size_t)fs.seekg( 0, ios::end ).tellg() - s1101;
fs.seekg( s1101 );
size_t s1491 = s1460 ? (std::min)( s1460, fsz ) : fsz;
s152.resize( s1491 );
fs.read( (char*)&s152[0], s1491 );}
void s1291::s1467( const s1311& src ){
fs << *(string*)&src;}
void s1291::s1447( s1311& s152, const s1311& s72 ){
if( s72.size() > 1 )
throw new s16( L"multi-byte line separators are not supported: '" + U16( (char*)s72.c_str() ) + L"'" );
string buf;
s152.clear();
std::getline( fs, buf, (char)s72[0] );
std::swap( buf, *(string*)(&s152) );}
void s1291::s1466( const s1311& src ){
fs << *(string*)&src << endl;}
wstring s1291::to_wstring( uint32_t s1552 ) const{
return L"FileStream"; }
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s1291*)(s481*)*s273)
inline void s1291::s1226( s480** s273, size_t s495 ){
s1291* ps = (s1291*)DR;
s1291* s680 = new s1291( *ps );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
void s1291::s1990( s480** s273, size_t s495, wstring& s1334 ){
s1291* pf = (s1291*)DR;
if( s495 > 2 ) {
if( s273[2]->s349() == Types.String ) {
pf->s1330 = s273[2]->to_wstring();
pf->s209 = NULL;}
else {
pf->s209 = s273[2];
pf->s1330 = L"";}}
s482 s1989;
if( s495 > 3 ) {
s1989 = s273[3];
pf->mode = s1989;}
else
s1989 = pf->mode;
if( s1989.s14() ) {
if( s1989->s491() == s473 )
s1334 = s1989->s494( 0, 0 )->to_wstring();
else if( s1989->s491() != s472 )
s1334 = s1989->to_wstring();
else
s1334 = s1989.s15<s368*>()->s374()->to_wstring();}}
inline void s1291::s2012( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
wstring s1334 = L"r";
s1990( s273, s495, s1334 );
if( s1334 != L"r" )
throw new s16( L"file open mode '" + s1334 + 
L"' is incompatible with '(open-r)' method" );
if( pf->s299->s1996( s2034, s2030 ) )
return;
pf->_open( s1334 );}
inline void s1291::s2014( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
wstring s1334 = L"w";
s1990( s273, s495, s1334 );
if( s1334 != L"w" && s1334 != L"x" && s1334 != L"a" )
throw new s16( L"file open mode '" + s1334 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s299->s1996( s2035, s2030 ) )
return;
pf->_open( s1334 );}
inline void s1291::s2013( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
wstring s1334 = L"r+";
s1990( s273, s495, s1334 );
if( s1334 != L"w" && s1334 != L"x" && s1334 != L"a" )
throw new s16( L"file open mode '" + s1334 + 
L"' is incompatible with '(open-w)' method" );
if( pf->s299->s1996( s2034, s2030 ) || 
pf->s299->s1996( s2035, s2030 ))
return;
pf->_open( s1334 );}
inline void s1291::s1313( s480** s273, size_t s495 ){
((s1291*)DR)->_close();
((s1291*)DR)->s1462 = NULL;
((s1291*)DR)->s1463 = NULL;}
inline void s1291::s1344( s480** s273, size_t s495 ){
assert( s495 == 4 );
assert( s273[2]->s349() == s1139 );
s1291* pf = (s1291*)DR;
if( pf->s299->s1996( s2035, s2030 ) )
return;
if( !pf->fs.good() )
throw new s16( L"cannot write to file '" + pf->s1330 + L"'." );
s1281* s1323 = (s1281*)s273[2];
s480* s1325 = s273[3];
int s1338 = (int)*s1325;
pf->fs.write( (const char*)s1323->s317().data(), s1338 );
if( !pf->fs.good() )
throw new s16( L"failed to write to file '" + pf->s1330 + L"'." );}
inline void s1291::s406( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
if( pf->s299->s1996( s2034, s2030 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s356* s680 = (s356*)*s273;
pf->s1449( s680->s317(), 0 );}
inline void s1291::s2020( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
if( pf->s299->s1996( s2034, s2030 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
s1281& bar = *(s1281*)s273[2];
pf->s1448(bar.s317(), 0 );}
inline void s1291::s1472( s480** s273, size_t s495 ){
s1291* pf = (s1291*)DR;
if( pf->s299->s1996( s2034, s2030 ) )
return;
if( !pf->fs )
throw new s16( L"file stream is not valid" );
fstream& fs = *(fstream*)pf->addr();
s313& v = *(s313*)s691;
string buf;
while(std::getline( fs, buf/*, widen('\n')*/ ) ) {
v.s317().push_back( new s356( pf->s299 ) );
v.s317().back().s15<s356*>()->s1944( U16( buf ) );
v.s317().back()->s1251();
if( fs.eof() )
break;}
if( fs.bad() )
throw new s16( L"cannot read from file '" + pf->s1330 + L"'" );}
void s1291::_open( const wstring& s1334 ){
if( fs.is_open() )
fs.close();
wstring path;
if( !s1330.empty() )
path = s1330;
else {
if( s209->s491() != s472 )
path = s209->to_wstring();
else 
path = s209.s15<s368*>()->s374()->to_wstring();
s1330 = path;}
if( !s3::s717( path ) )
path = s299->s709() + path;
s1462 = NULL;
s1463 = NULL;
std::ios_base::openmode md;
if( s1334.empty() || s1334 == L"r" ) {
md = ios::in | ios::binary;
s1462 = ( basic_ifstream<tdbyte_t>* ) &fs;}
else if( s1334 == L"w" || s1334 == L"x" ) {
md = ios::out | ios::binary;
s1463 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else if( s1334 == L"a" ) {
md = ios::out | ios::binary | ios::app;
s1463 = ( basic_ofstream<tdbyte_t>* ) &fs;}
else
throw new s16( L"unrecognized file open mode: '" + s1334 + L"'." );
if( s1334 == L"x" ) {
fs.open( TOFS(path.c_str()), ios::in );
if( fs )
throw new s16( L"the file '" + path + L"' already exists and cannot be opened with 'x' mode." );
fs.close();}
fs.open( TOFS(path.c_str()), md );
if( !fs.good() )
throw new s16( L"cannot open file '" + path + L"'." );}
void s1291::_close(){
mode = s209 = NULL;
s1330.clear();
fs.close();}
void s1291::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << s350() << L" : " << s1330 << endl;}
size_t s1291::s319() const{
return hash<uint64_t>{}((uint64_t)this);}
bool s1291::operator==( const s480* p ) const{
return this == p;}
bool s1291::operator<( const s480* p ) const{
return this < p;}
s1390::s1390( s261* s299, s271* ns_, const s262* ast_ )
: s1394( s299, ns_, ast_ ){
s1462 = &std::wcin;}
s480* s1390::s352( s271* s585, const std::vector<s270*>&, const s262* ast_ ) const{
throw new s16( L" StdIn object cannot be instantiated" );}
void s1390::s347(){
s345.insert( make_pair( L"get", new s334( L"get", &s1390::s324, s1143,
{ s1112() }, 0, 0 ) ) );
s299->TR().s1152( s490, s7::s1397, s1500::s1493 );}
void s1390::s497( const s271*, bool ){
s1251();}
s480* s1390::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return NULL;}
s270* s1390::s332( s588* s2041, s271* impl ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1390::s353( s270* p ) const{
throw new s16( L"StdIn object cannot be copied" );}
void s1390::s1449( std::wstring& s152, size_t s1460 ){
s152.clear();
wcin >> s152;
if( s1460 && s152.size() > s1460 )
s152.resize( s1460 );
wcin >> std::ws;}
void s1390::s1468( s1889& src ){
throw new s16( L"cannot output to StdIn" );}
void s1390::s1450( std::wstring& s152, s1889& s72 ){
s152.clear();
std::getline( wcin, s152 );}
void s1390::s1469( s1889& src ){
throw new s16( L"cannot output to StdIn" );}
void s1390::s1448( s1311& s152, size_t s1460 ){
wstring buf( s1460, L'\0' );
wcin.read( &buf[0], s1460 );
size_t s680 = wcin.gcount();
buf.resize( s680 );
s152 = (tdbyte_t*)U8( buf ).data();}
void s1390::s1467( const s1311& src ){
throw new s16( L"cannot output to StdIn" );}
void s1390::s1447( s1311& s152, const s1311& s72 ){
wstring buf;
std::getline( wcin, buf );
s152 = (tdbyte_t*)U8( buf ).data();}
void s1390::s1466( const s1311& src ){
throw new s16( L"cannot output to StdIn" );}
inline void s1390::s324( s480** s273, size_t s495 ){
s356* s680 = (s356*)*s273;
wchar_t s152;
wcin.get( s152 );
*s680->s354() = wstring( s152, 1 );}
wstring s1390::to_wstring( uint32_t s1552 ) const{
throw new s16( L"22: not implemented" );}
void s1390::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"StdIn object" << endl;}
size_t s1390::s319() const{
throw new s16( L"15: not implemented" );}
bool s1390::operator==( const s480* p ) const{
throw new s16( L"16: not implemented" );}
bool s1390::operator<( const s480* p ) const{
throw new s16( L"17: not implemented" );}
s1392::s1392( s261* s299, s271* ns_, const s262* ast_ )
: s1394( s299, ns_, ast_ ){
s1463 = &std::wcout;}
s480* s1392::s352( s271* s585, const std::vector<s270*>&, const s262* ast_ ) const{
throw new s16( L"StdOut object cannot be instantiated" );}
void s1392::s347(){
s299->TR().s1152( s490, s7::s1402, s1500::s1497 );}
void s1392::s497( const s271*, bool ){
s1251();}
s480* s1392::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return NULL;}
s270* s1392::s332( s588* s2041, s271* impl ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1392::s353( s270* p ) const{
throw new s16( L"StdOut object cannot be copied" );}
void s1392::s1449( std::wstring& s152, size_t s1460 ){
throw new s16( L"cannot get input from StdOut" );}
void s1392::s1468( s1889& src ){
wcout << src;}
void s1392::s1450( std::wstring& s152, s1889& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1392::s1469( s1889& src ){
wcout << src << endl;}
void s1392::s1448( s1311& s152, size_t s1460 ){
throw new s16( L"cannot get input from StdOut" );}
void s1392::s1467( const s1311& src ){
wcout << U16( (const char*)src.data() );}
void s1392::s1447( s1311& s152, const s1311& s72 ){
throw new s16( L"cannot get input from StdOut" );}
void s1392::s1466( const s1311& src ){
wcout << U16( (const char*)src.data() ) << endl;}
void s1392::s1897( wchar_t c ){
if( s1463 )
*s1463 << std::setfill( c );}
wstring s1392::to_wstring( uint32_t s1552 ) const{
throw new s16( L"21: not implemented" );}
void s1392::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"StdOut object" << endl;}
size_t s1392::s319() const{
throw new s16( L"18: not implemented" );}
bool s1392::operator==( const s480* p ) const{
throw new s16( L"19: not implemented" );}
bool s1392::operator<( const s480* p ) const{
throw new s16( L"20: not implemented" );}
s602::s602( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694,
bool s2159 )
: s588( s299, s589, s590, s590, s562, s232, s694, true, s2159 ){
TDException s960( s7::s1673, s925, s694, L"malformed syntax of 'with' statement" );
size_t n = 0;
bool s1158;
for( ; n < l.size(); n += 2 ) {
s1158 = false;
if( ( (s480*)l[n] ) == s1671 ) {
if( l.size() == n )
throw s960.s992( L"the 'const' keyword should precede the parameter name" );
s1158 = true;
++n;}
if( l[n]->s491() != s472 ) {
if( s1158 )
throw s960.s992( L"the 'const' keyword should precede the parameter name" );
break;}
s368* s76 = (s368*)l[n];
s480* s616 = (s480*)l[n + 1];
if( s1158 )
s76->s1249();
s625.s538( s76->s614(), s616 );
s273.push_back( s616->s332(0,0) );
s579.push_back( s616 );
s627.push_back( s616 );
s628.push_back( *s76 );}
s581.insert( s581.end(), l.begin() + n, l.end() );}
s602::s602( const s602& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), s600(), true,
right.s2158 ){
s490 = 0;// Types.Null;
}
void
s602::s497( const s271* s1657, bool proc ){
for( size_t n = 0; n < s581.size(); ++n )
s581[n].s15<s558*>()->s2170( true );
s588::s497( this, proc );
if( !s490 )
s490 = s1142;
return;
s666 = proc ? s585->s297() : s1657->s297();
if( s585->s491() == s476 || s585->s491() == s475 || s585->s491() == s2149) {
if( s585->s491() == s475 || s585->s491() == s2149 )
return;}
if( s273.size() > s627.size() )
throw new s16( L"too many arguments" );
for( size_t n = 0; n < s273.size(); ++n ) {
s482 par = s273[n];
if( par->s491() == s472 ) {
if( par.s15<s368*>()->s378().s13() )
par.s15<s368*>()->s497( this, proc );}
else
s840( par, n, s273[n], s1657, false );}
for( size_t n = 0; n < s273.size(); ++n ) {
s625.s538( s628[n].s614(), s273[n].s15<s480*>(), s479::s146 );
s273[n]->s1664( s7::s860 );
s627[n] = s273[n];}
for( size_t n = 0; n < s581.size(); ++n ) {
if( s581[n]->s491() == s474 ) {
s487 cs = new s558( *s581[n].s15<s558*>() );
s581[n] = s597( cs, s299, s585, this, s585->s297(), true );}
else if( s581[n]->s491() == s472 )
s581[n].s15<s368*>()->s497( s584, proc );
else if( s581[n]->s491() != s473 )
s581[n]->s497( s584 );
else // lambda - ?
throw new s16( L"unhandled expression" );}
for( auto it : s581 ) {
if( it->s491() == s473 )
it.s15<Transd*>()->s497( s585, true );}
if( !s490 && s581.size() ) {
s490 = s581.back()->s349();
s583 = s299->TR().s515( s349(), s585, s585->s297() );}}
s483
s602::s494( s480** s686, size_t s690 ){
s483 s680 = s362;
size_t s2228 = 0;
size_t n;
if( s2219 == -1 ) {
s627.resize( s273.size() );
for( size_t n = 0; n < s273.size(); ++n ) {
s483 s152;
if( s273[n]->s491() == s471 || 
s273[n]->s491() == s477 ) {
s152 = (s480*)s273[n]->s332(0,0);
s152->s497( this, true );}
else {
s152 = s273[n]->s494( NULL, 0 );}
if( s152->s615() < 0 ) {
if( s152->s615() == s7::s859 )
s152->s1664( 0 );
else {
s583 = s152;
return s152;}}
s627[n] = s152.s15<s481*>();}}
else
s2228 = (size_t)s2219;
for( n = s2228; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s686, s690 );
if( s680->s615() < 0 )
break;}
if( s680->s615() != s7::s2218 ) {
for( size_t n = 0; n < s273.size(); ++n ) {
s273[n]->release();}
s2219 = -1;}
else
s2219 = (int)n;
s583 = s680;
return s680;}
s304::s304( s261* s299, s271* s589, Transd* s590, const std::vector<s270*>& l, const s262* s694,
bool s2159 )
: s588( s299, s589, s590, s590, s562, s254, s694, true, s2159 ){
if( l.size() < 2 )
throw new s16( s254 + L"(): wrong numbers of arguments" );
s273.push_back( l[0] );
s627.resize( 1 );
s628.push_back( s368( L"@cond", s299 ) );
s581.insert( s581.end(), l.begin() + 1, l.end() );}
s304::s304( const s304& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), s600(), right.s2158 ){}
void
s304::s497( const s271* s1657, bool proc ){
for( size_t n = 0; n < s581.size(); ++n )
s581[n].s15<s558*>()->s2170( true );
s588::s497( s1657, proc );
s305 = s627[0] = s273[0];
s490 = s581.back()->s349();}
s483
s304::s494( s480** s686, size_t s690 ){
s483 s680 = s362, s152;
while( 1 ) {
if( (bool)*s305->s494( 0, 0 ) == false )
return s680; 
for( size_t n = 0; n < s581.size(); ++n ) {
s152 = s581[n]->s494( s686, s690 );
if( s152->s615() < 0 )
break;}
s680 = s152;
if( s680->s615() < 0 
&& (s680->s615() != s7::s435 )
) {
if( s680->s615() == s7::s436 )
s680 = s362.s15<s480*>();
break;}}
return s680;}
s611::s611( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l,
const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, s562, s259, s694, true, s2159 ),
s308( s7::s459, s299 ), s309( s299, 0, NULL ), s2474( s7::s2471, s299 ), 
s2273( NULL ), s877( false ){
TDException s960( s7::s1653, s925, s694, L"malformed syntax of 'for' statement" );
if( l.size() < 5 )
throw s960.s992( L"too few arguments" );
s625.s538( s308.s614(), &s309 );
s579.push_back( (s480*)&s309 );
s627.push_back( (s480*)&s309 );
s628.push_back( s368( s308.s614(), s299 ) );
s309.s11();
s270* p = l[0];
if( p->s491() != s472 )
throw s960.s992( L"the variable must be a name" );
s706 = (s368*) l[0];
varval = s362.s15<s480*>();
s368* in = (s368*) l[1];
if( in->s614() != L"in" )
throw s960.s992( L"the 'in' keyword is missing" );
s307 = l[2];
p = l[3];
size_t idx = 4; 
wstring s987 = L"malformed 'for' statement";
if( p->s491() != s472 )
throw s960.s992( s987 );
if( ((s368*)p)->s614() == L":rev" ) {
s877 = true;
p = l[idx++];}
if( ((s368*)p)->s614() == L"where" ) {
if( l.size() < ( idx + 2 ) )
throw new s16( s987 );
where = l[idx++];
p = l[idx++];}
if( p->s491() != s472 )
throw new s16( s987 + L": the DO clause is missing" );
if( ((s368*)p)->s614().find( L"project" ) == 0 ) {
if( l.size()  )
s1052 = l[idx];
size_t pl = ( (s368*)p )->s614().find( L"<" );
if( pl == 7 ) {
wstring s2477 = ( (s368*)p )->s614().substr( pl );
s2477 = s4::s51( L"<" + s4::s48, s2477, s4::s48 );
s2477 = s2477.substr( 0, s2477.size() - 1 );
s806::Cont vt;
s2475 = s299->TR().s2473( s2477, vt );}}
else {
if( ((s368*)p)->s614() != L"do" )
throw new s16( s987 );
s581.assign( l.begin() + idx, l.end() );}
s625.s538( s706->s614(), NULL );
s579.push_back( varval );
s627.push_back( varval );
s628.push_back( s368( s706->s614(), s299 ) );
s628.push_back( s368( s2474.s614(), s299 ) );}
s611::s611( const s611& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), s600(), true,
right.s2158 ),s706(right.s706),varval(right.varval),s307(right.s307),where(right.where),
s1052(right.s1052),s308( s7::s459, right.s299 ), s309( right.s299, 0, NULL ), 
s2474(s7::s2471, right.s299), s2273( NULL ){
s583 = right.s583;
s490 = right.s490;}
void
s611::s497( const s271* s1657, bool proc ){
TDException s960( s7::s1366, s925, s600(), L"malformed syntax of 'for' statement" );
s469 pc = s307->s491();
if( pc == s474 ) {
s482 s589 = s597( s307.s15<s558*>(), s299, s585, this, s297(), proc );
s307 = s589;
s307.s15<Transd*>()->s497( s1657, false );}
else if( pc == s472 ) {
s307.s15<s368*>()->s497( this, proc );}
else if( pc == s471 )
s307->s497( this );
else
throw s960.s992( L"unknown iterable type" );
s481* s1464;
if( s307->s349() == Types.Range )
s1464 = ((s382*)s307->s493())->s812();
else
s1464 = s307->s493();
s1053 vt;
if( s299->TR().s1453( s1464->s349(), s1500::s1496 ) )
vt = ( (s323*)s1464 )->ValType();
else
vt = ( (s323*)s1464 )->s316();
if( s877 && !s299->TR().s1453( s1464->s349(), s1500::s1494 ) )
throw s960.s992( L"iterable doesn't support the reverse iteration" );
varval = s299->TR().s515(vt, s585, s585->s297() );
varval->s1664( s7::s860 );
s706->s379( varval );
s627[1] = varval.s15<s481*>();
s625.s538( s706->s614(), varval.s15<s481*>(), s479::s146 );
if( where ) {
pc = where->s491();
if( pc == s474 ) {
where = s597( where.s15<s558*>(), s299, s585, this, s297(), proc );
where.s15<Transd*>()->s497( s1657, false );}
else
throw s960.s992( L"WHERE clause must be a lambda" );}
s483 s2476;
if( s1052 ) {
if( s2475 ) {
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
s299->TR().s797( s2475 ) + L">";
ts = s299->TR().s1341( ts );
s490 = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s625.s538( s2474.s614(), (s481*)s299->TR().s999( s490 ), s479::s146 );
s2476 = s299->TR().s515( s349(), s585, s585->s297() );
s2476->s497( s584, proc );
s2476->s1664( s7::s860 );
s627.push_back( s2476.s15<s270*>() );}
pc = s1052->s491();
if( pc == s474 ) {
s1052 = s597( s1052.s15<s558*>(), s299, s585, this, s297(), proc );
s1052.s15<Transd*>()->s497( s1657, false );}
else if( pc == s472 ){
s1052.s15<s368*>()->s497( this );}
else if( pc == s471 ) {
s1052->s497( this, false );}
else
throw s960.s992( L"PROJECT clause must be a lambda." );
if( !s2475 ) {
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" +
s299->TR().s797( s1052->s349() ) + L">";
ts = s299->TR().s1341( ts );
s490 = ( (s313*)Types( s299, Types.Vector ) )->s1185( this, ts, s1704, s1268 );}}
for( size_t n = 0; n < s581.size(); ++n )
s581[n].s15<s558*>()->s2170( true );
s588::s497( s1657, false );
if( s2475 )s583 = s2476;}
void s611::s2117( s588* s2041, s271* impl, bool s2159 ){
if( s584 ) s584 = s2041;
if( impl ) s585 = impl;
s588::s2117( this, impl, s2159 );
s307->s2117( this, impl, s2159 );
if( s1052.s14() )
s1052->s2117( this, impl, s2159 );}
s483 s611::s494( s480** s686, size_t s690 ){
TDException s960(  s7::s2275,
s1367, NULL, L"error during running 'for' loop", TDException::Stage::s1022 );
s483 s680 = s583;
size_t s2228 = 0;
size_t n;
s9<s323> s977;
Iterator* s1012 = NULL;
if( s2219 == -1 ) {
s469 pc = s307->s491();
if( pc == s473 )
s977 = s307->s494( 0, 0 ).s15<s323*>();
else if( pc == s472 ) {
s977 = ( (s323*)s307.s15<s368*>()->s374() );}
else
s977 = s307.s15<s323*>();
assert( s977.s14() );
if( s977->s615() < 0 ) {
wstring s78 = L"failed to initialize iterable object";
if( s977->s349() == Types.s358 )
s78 += L": " + ((s358*)s977.s15<s270*>())->Msg();
s960.s2287( (s262*)s977->s600() );
throw s960.s992( s78 );}
if( s1052.s14() ) {
s583.s15<s313*>()->clear();}
s1012 = s977->s311( NULL, s877 );}
else {
s2228 = s2219;
s1012 = s2273;}
while( 1 ) {
if( !s2228 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
s627[0] = s1012->Idx();
s627[1] = p.s15<s481*>();
if( where ) {
if( ((bool)*(s480*)where->s494( 0, 0 )) != true )
continue;}}
if( s1052 ) {
s482 s2350 = s1052->s494( 0, 0 ).s15<s481*>();
if( s2350->s349() != s1142 )
s583.s15<s313*>()->add( s2350	);//->s332(0,0) );
}
else {
for( n = s2228; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s686, s690 );
if( s680->s615() < 0 )
break;}
if( s680->s615() < 0 && s680->s615() != s7::s435 ) {
if( s680->s615() == s7::s436 )
s680 = s362.s15<s480*>();
else if( s680->s615() == s7::s2218 ) {
s2219 = (int)n;
if( !s2273 ) {
s2273 = s1012;
s2272 = s977;}}
else if( s680->s615() == s7::s2264 ) {
s2219 = (int)n + 1;
if( s2219 == s581.size() )
s2219 = 0;
s680->s1664( s7::s2218 );
if( !s2273 ) {
s2273 = s1012;
s2272 = s977;}}
else {
s2219 = -1;
s2273 = NULL;
s2272 = NULL;}
break;}}}
if( s680.s13() || s680->s615() == s7::s435 )
return s362;
return s680;}
s270* s602::s332( s588* s2041, s271* impl ) const{
s602* s680 = new s602( *this, impl, s2041 );
s680->s2117( s680, impl, s2158 );
return s680;}
s270* s304::s332( s588* s2041, s271* impl ) const{
s304* s680 = new s304( *this, impl, s2041 );
s680->s2117( s680, impl, s2158 );
return s680;}
/*s270* s306::s332( s588* s2041, s271* impl ) const
{
return new s306( *this );}
*/
s270* s611::s332( s588* s2041, s271* impl ) const{
s611* s680 = new s611( *this, impl ? impl : s585.s15<s271*>(), s2041 );
return s680;}
s601::s601( s261* s299, s271* s585, s588* s584,
s560 ct, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s585, s584, s584, ct, l, s694, false, false ){
s573 = s570;}
void s601::s645( s1053 s616, s588* pOvr ){
types.push_back( s616 );
s646.push_back( pOvr );}
s483 s601::s494( s480** s686, size_t s690 ){
return s588::s494( s686, s690 );}
s831::s831( s261* s299 )
: s588( s299, NULL, NULL, NULL, s564, s251, NULL ), s2088( false ){
s489 = s1234;
s490 = Types.Lambda;
if( !s490 )
wh = s7::s861;
else
wh = s7::s860;}
s831::s831( const s831& )
: s588( s299, NULL, NULL, NULL, s564, s251, NULL ){
throw;}
s831::s831( s261* s299, s271* s589, s588* s590, 
const std::vector<s270*>& l, const s262* s694, s1053 s2106, bool s2089,
bool s2159 )
: s588( s299, s589, s590, s589, s564, s251, s694, false,
s2159 ), s2088( s2089 ){
ns = s585;
s489 = s1234;
bool s1158;
bool s2131 = false;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
s1158 = false;
if( n == 0 && l[n]->s491() == s471 ) {
const s806& vt = s299->TR().s1005( l[n]->s349() );
s1053 pt = vt.s812()[0];
if( pt == s1702 )
s2094 = (s951*)l[n];
else
throw new s16( L"unknown first member in lambda definition" );
n -= 1;
continue;}
if( ( (s480*)l[n] ) == s866 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s1887.push_back( l[n + 1]->s349() );
n += 2;
break;}
if( ((s480*)l[n]) == s2130 ) {
s2131 = true;
n -= 1;
continue;}
else if( ((s480*)l[n]) == s1671 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition: the 'const' keyword ");
s1158 = true;
++n;}
if( l[n]->s491() != s472 )
break;
s368* s76 = (s368*)l[n];
if( s1158 )
s76->s1249();
s480* s616 = (s480*)l[n + 1];
s625.s538( s76->s614(), s616 );
s273.push_back( s616 );
if( !s2131 )
s579.push_back( s616 );
else
s616->s2180( s2184 );
s627.push_back( s616 );
s1887.push_back( s616->s349() );
s628.push_back( s368( s76->s614(), s299 ) );}
if( s2106 ) {
const s806& vt = s299->TR().s1005( s2106 );
s1887.clear();
for( size_t n = 2; n < vt.s812().size(); n += 2 )
s1887.push_back( vt.s812()[n] );
s490 = s2106; // s1887.back();
}
else {
if( s1887.empty() )
s1887 = { s1142, s1142 };
else if( s1887.size() == 1 )
s1887.insert( s1887.begin(), s1142 );
s806::Cont vt = { s1701, (s1053)s1887.size() };
for( size_t n = 0; n < s1887.size(); ++n ) {
vt.push_back( s1887[n] );
vt.push_back( 0 );}
s490 = s299->TR().s1038( vt );}
s581.insert( s581.end(), l.begin() + n, l.end() );}
s831::s831( s261* s299, s271* s589, const vector<s1053>& l,
s1053 pt, const s262* s694 )
: s588( s299, s589, NULL, s589, s564, s251, s694 ), s2088( false ){
s489 = s1234;
s490 = pt;
for( size_t n = 2; n < l.size(); n += 2 )
s1887.push_back( l[n] );
for( size_t n = 1; n < s1887.size() - 1; ++n ) {
s627.push_back( s299->TR().s515( s1887[n], s585, s585->s297() ) );
s273.push_back( s627.back() );
s628.push_back( s368(std::to_wstring( n ), s299 ) );
s625.s538( s628.back().s614(), s273.back().s15<s480*>(), s479::s146 );
s579.push_back( s627.back().s15<s480*>() );}
ns = s585;}
s831::s831( s831& s1885, s271* s589, s588* s590, const std::vector<s482>& l, const s262* s694 )
: s588( s1885, s589, s590, s589, vector<s481*>(), s694, false, true ), s2088( s1885.s2088 ),
s2094( s1885.s2094 ){
s489 = s1234;
s490 = s1885.s490;
s1887 = s1885.s1887;
size_t n = 0;
for( ; n < l.size(); n += 2 ) {
if( ( l[n].s15<s480*>() ) == s866 ) {
if( l.size() == n )
throw new s16( L"malformed lambda definition" );
s490 = l[n + 1]->s349();
n += 2;
break;}
if( l[n]->s491() != s472 )
break;
s368* s76 =  l[n].s15<s368*>();
lang::s653( s76->s614() );
s480* s616 = l[n + 1].s15<s480*>();
s625.s538( s76->s614(), s616 );
s273.push_back( s616 );
s579.push_back( s616 );
s627.push_back( s616 );
s628.push_back( s368( s76->s614(), s299 ) );}
if( s627.empty() ) {
s1885.s625.copy( s625, (s271*)s589, s590 );
s627 = s1885.s627;
s628 = s1885.s628;
s273 = s1885.s273;
s579 = s1885.s579;}
if( s2094.s14() ) {
bool _b = ( s628.size() == s273.size() );
const vector<s482>& v = s2094->s317();
for( size_t n = 0; n < v.size(); ++n ) {
s368* ref = v[n].s15<s368*>();
if( ref->s378().s14() ) {
ref->s2117( s590, s589, s2165() ); // ???DEBUG??? 220828
s480* _dv = ref->s374();
if( _dv->s615() == s7::s861 )
_dv->s497( s585, true );
if( _b ) {
s628.push_back( *ref );
s270* _p = _dv->s332( this, s585 );
s627.push_back( _p );
s625.s538( ref->s614(), s627.back().s15<s481*>() );}}
else if( s299->s1319() && !s625.s155( ref->s614() ) ) {
ref->s497( this, false );
s480* s2093 = ref->s374();
s628.push_back( *ref );
s270* _p = s2093->s332( this, s585 );
s627.push_back( _p );
s625.s538( ref->s614(), s627.back().s15<s481*>() );}}}
s581.insert( s581.end(), l.begin() + n, l.end() );
s1664( s1885.s615() );}
wstring s831::s827() const{
return ns->s827();}
s482 s831::s2283(){
return s585;
} // ???DEBUG??? 220801
s480* s831::s351( const s262& s694, s271* s585, s1889& s331 ) const{
TDException s960( s7::s1876, s925, &s694,
L"wrong Lambda constructor syntax" );
wstring s = s299->TR().s1341( s299->TR().s1264( s694.s290(), s331 ));
wstring sv;
wstring s766 = Types( s299, Types.Lambda )->s350();
wstring s1262, s641;
s1053 pt = 0;
s831* s680 = NULL;
if( s.find( s7::s1345 + L"<Lambda<" ) == 0 ) {
s1262 = s.substr( s7::s1345.size() + 1, s.size() - ( s7::s1345.size() + 2) );
size_t pl = s694.Src().find( 955 );
if( pl != string::npos ) {
s641 = s694.Src().substr( pl );
s = s1262 + L"(" + s641;}
else
s = s1262 + L"()";}
if( s.find( s766 ) == 0 && s[s.size() - 1] == L')' ) {
if( s.find( L'<' ) == string::npos )
throw s960.s992( L"missing type signature" );
if( s1262.empty() )
s1151( s299, s, s1262, s641 );
if( s1262.empty() )
throw s960.s992( L"missing type signature" );
s806::Cont vt;
pt = s299->TR().s2473( s1262, vt );
if( s641.size() ) {
if( s641.find( L"lambda" ) == 0 || s641[0] == 955 ) {
s939 ast_ = new s262( L"(" + s641 + L")", s694.Nqj(), ((s262*)&s694)->s2082() );
s487 cs = s588::s1109( *ast_, s299, s585, s585->s297(), false );
const s140& nv = s694.s267( s2298 );
bool s2301 = false;
if( !( nv == s264 ) )
s2301 = nv.s721();
return new s831( s299, s585, NULL, cs->s599(), &s694, pt, s2301 );}
else if( s641[0] != L']' )
throw s960.s992( L"malformed Lambda initializer" );}
s680 = new s831( s299, s585, vt, pt, &s694 );}
return s680;}
void
s831::s497( const s271* s214, bool proc ){
s1053 pt = s490;
if( s584.s13() )
s584 = (s588*)s214; 
s2209( s214, proc );
if( s299->s1319() || s2088 ) { 
s490 = 0; // s1142;
if( !s584 ) s584 = (s588*)s214;
for( size_t n = 0; n < s581.size(); ++n ) {
if( s581[n]->s491() == s474 )
s581[n].s15<s558*>()->s2170( true );}
s588::s497( s585->s491() == s477 ? s585.s15<s271*>() : (s271*)this, proc ); // ???DEBUG??? 220830
if( s1887.size() < 2 || s1887.back() == s1142 ) {
if( s1887.empty() ) {
s1887.push_back( s1142 );
if( s581.size() )
s1887.push_back( s581.back()->s349() );
else
s1887.push_back( s1142 );}
s1887.back() = s490 ? s490 : s1887.back();
s806::Cont vt = { s1701, (s1053)s1887.size() };
for( size_t n = 0; n < s1887.size(); ++n ) {
vt.push_back( s1887[n] );
vt.push_back( 0 );}
s490 = s299->TR().s1038( vt );}
else
s490 = pt;
s1251();}
if( s583.s13() || s583->s349() != s490 ) {
if( s214 )
s583 = s299->TR().s515( s1317(), (s271*)s214, s214->s2153() );
else
s583 = s299->TR().s515( s1317(), s585, s585->s297() );}
if( s583.s13() )
s583 = s362.s15<s480*>();}
void s831::s2209( const s271* s214, bool proc ){
if( s2094.s14() /*&& (s299->s1319() || s2088 )*/ ) {
const vector<s482>& v = s2094->s317();
size_t s68 = s627.size() - v.size();
for( size_t n = 0; n < v.size(); ++n ) {
if( v[n].s15<s368*>()->s378().s13() ) {
s368* ref = v[n].s15<s368*>();// ->s332();
ref->s497( this, proc );
s480* s2093 = ref->s374();
s628.push_back( *ref );
s270* s2119 = s2093->s332( this, s585 );
if( !s2119->s1194() )
s2119->s497( s214, proc );
s627.push_back( s2119 );
s625.s538( ref->s614(), s627.back().s15<s481*>() );}
else {
if( !s627[n + s68]->s1194() ) {
s627[n + s68]->s497( s214, proc );}
else {
s628[n + s68].s2117( this, (s271*)s214, proc );
s627[n + s68] = s628[n + s68].s374(); // ???DEBUG??? 220827
}}}}}
s483 s831::s494( s480** s686, size_t s690 ){
s483 s680 = s362;
size_t s2228 = 0;
size_t n;
if( s2219 == -1 ) {
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s578 + n ) ) {
s469 pc = ( ( s481* )*( s578 + n ) )->s491();
if( pc == s472 )
s627[n] =
(s480*)( ( s368* )*( s578 + n ) )->s374();
else if( pc == s473 ) {
s973[n+shift] = (s480*)( ( s588* )*( s578 + n ) )->s494( s686, s690 );
s627[n] = s973[n + shift].s15<s270*>();}
else if( pc == s471 || pc == s1234 ) {
if( n < s579.size() )
s627[n] = ( s480* )*( s578 + n );
else
s627[n] = ( s480* )((s481*)*( s578 + n ))->s332( 0, 0 );}
else if( pc == s477 ) {
s627[n] = ( s480* )( ( s481* )*( s578 + n ) )->s332( 0, 0 );
s271* po = s627[n].s15<s271*>();
if( !po->s1194() )
s627[n]->s497( this, false );}}}
if( 0 && s580.size() > 1 ) {
for( size_t n = 1; n < s580.size(); ++n )
s627[n - 1] = s580[n];}}
else {
s2228 = s2219;}
for( n = s2228; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s577, s495 );
if( s680->s615() < 0 ) {
if( s680->s615() == s7::s2218 )
s2219 = (int)n;
else if( s680->s615() == s7::s2264 ) {
s2219 = (int)n + 1;
if( s2219 == s581.size() )
s2219 = 0;
else
s680->s1664( s7::s2218 );}
else {
if( s680->s615() == s7::s859 )
s680->s1664( 0 );
s2219 = -1;}
break;}}
return s680;}
s480* s831::s352( s271* s585, const vector<s1053>& vt ) const{
s1053 pt = s299->TR().s1038( vt );
return new s831( s299, s585, vt, pt, NULL );}
s480* s831::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s831( s299, s585, (s588*)s585, l, ast_ );}
s588* s831::s1670( s1889& s671, s588* s214, s271* s1657,
s558* cs ) const{
if( s671 == s7::s1345 ) {
if( cs->s599().size() > 1 && (cs->s599()[1]->s491() != s472 ||
((s368*)cs->s599()[1])->s614()[0] != 955 ))
throw new s16( L"malformed lambda syntax" );
s262* s1907 = (s262*)cs->s600();
s831* s1905 = (s831*) s351( *s1907, s585.s15<s271*>(), s585->s297() );
vector<s270*> s1906( { s1905 } );
return new s1666( s299, s585.s15<s271*>(), s214, &s480::s1879, 
s1906, s7::s1345, 0, cs->s600(), cs->s2165() );}
return s480::s1670( s671, s214, s1657, cs );}
s270* s831::s332( s588* s2041, s271* impl ) const{
s831* s680 = new s831( *(s831*)this, impl ? impl : s585.s15<s271*>(), 
(s588*)this, vector<s482>(), NULL );
return s680;}
void s831::s2117( s588* s2041, s271* impl, bool s2159 ){
if( s2041 && s2159 && !s2088 ) 
s584 = s2041;
s588::s2117( this, impl, s2159 );
if( s2094.s14() ) {
const vector<s482>& v = s2094->s317();
for( size_t n = 0; n < v.size(); ++n ) {			
s368* ref = v[n].s15<s368*>();
ref->s2117( s2041, impl, false );
s480* s2093 = ref->s374();
s270* s2119 = s2093->s332( s2041, s585 );
if( !s2119->s1194() )
s2119->s497( (s271*)s2041, false );
for( size_t m = 0; m < s628.size(); ++m ) {
if( s628[m].s614() == ref->s614() ) {
s627[m] = s2119;
s625.s538( ref->s614(), s627[m].s15<s481*>(), s479::s146 );}}}}}
s480* s831::s1880( s480** s273, size_t s495 ){
s831* s680 = new s831( *(s831*)this, s585, s584, vector<s482>(), NULL );
s680->s497( s584.s15<s271*>(), false ); 
return s680;}
wstring s831::trace( s1889& topics ) const{
wstringstream buf;
int s196 = 0;
wstring s1069 = std::to_wstring( reinterpret_cast<long long>( this ) );
s1069 = s1069.substr( s1069.size() - 5 );
if( topics.empty() ) {
buf << L"Lambda : " << s1069 << endl;
s588::s303( &buf, s196 );}
else {
if( topics == L"id" )
buf << L"id: " << s1069;
else if( topics == L"nexpr" )
buf << L"nexpr: " << s2219;}
return buf.str();}
void s831::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Lambda : " <<  s277 << endl;
s588::s303( pd, s196 );}
s603::s603( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s242, s694 ){
s273.assign( l.begin(), l.end() );
s490 = s1138;}
s483 s603::s494( s480**, size_t s495 ){
*s583.s15<s357*>()->s354() = 0;
for( size_t n = 0; n < s273.size(); ++n ) {
if( ( bool )*( (s481*)( s273[n]->s494( 0, 0 ) ) ) ) {
*s583.s15<s357*>()->s354() = 1;
return s583;}}
return s583;}
s604::s604( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, s562, s242, s694, false, s2159 ){
s273.assign( l.begin(), l.end() );
s490 = s1138;}
s483 s604::s494( s480**, size_t ){
*s583.s15<s357*>()->s354() = 1;
for( size_t n = 0; n < s273.size(); ++n ) {
if( !( bool )*( (s481*)( s273[n]->s494( 0, 0 ) ) ) ) {
*s583.s15<s357*>()->s354() = 0;
return s583;}}
return s583;}
s1395::s1395( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, s562, s1416, s694, false, s2159 ),
s1490( s7::s1362, s299 ),	s308( s7::s459, s299 ), s309( s299, 0, (s271*)NULL ){
TDException s960( s7::s1654, s925, s694, L"malformed syntax of 'any()' function call" );
if( l.size() < 1 || l.size() > 2 )
throw s960.s992( L"'any()' function requires one or two arguments, " +
std::to_wstring( l.size() ) + L" were given" );
s625.s538( s308.s614(), &s309 );
s625.s538( s1490.s614(), NULL );
s627.push_back( (s480*)&s309 );
s627.push_back( NULL );
s628.push_back( s368( s308.s614(), s299 ) );
s628.push_back( s368( s1490.s614(), s299 ) );
s307 = l[0];
if( l.size() > 1 )
lambda = l[1];
s490 = s1138;}
void
s1395::s497( const s271* s1657, bool proc ){
TDException s960( s7::s1364, s925, s600(), L"malformed syntax of 'any()' function call" );
s469 pc = s307->s491();
if( pc == s474 ) {
s482 s589 = s597( s307.s15<s558*>(), s299, s585, this, s297(), proc );
s307 = s589;
s307.s15<Transd*>()->s497( s1657, false );}
else if( pc == s472 ) {
s307.s15<s368*>()->s497( this );}
else if( pc == s471 )
s307->s497( this );
else
throw s960.s992( L"unknown iterable type" );
varval = s299->TR().s515( ( (s323*)s307->s493() )->ValType(), s585, s585->s297() );
varval->s1251();
s1490.s379( varval );
s627[1] = varval.s15<s481*>();
if( lambda.s14() ) {
if( lambda->s491() == s472 ) {
lambda.s15<s368*>()->s497( s584 );}
else {
lambda.s15<s558*>()->s2170( true );
lambda = s270::s1010( s299, lambda, this, this, s584->s297(), true );}}
for( size_t n = 0; n < s581.size(); ++n )
s581[n].s15<s558*>()->s2170( true );
s588::s497( s1657, false );
s1251();}
s483 s1395::s494( s480**, size_t  ){
TDException s960( s7::s1365, s1367, past );
s483 s680 = s583;
*s680.s15<s357*>()->s354() = false;
s469 pc = s307->s491();
s9<s323> s585;
if( pc == s473 )
s585 = s307->s494( 0, 0 ).s15<s323*>();
else if( pc == s472 )
s585 = ( (s323*)s307.s15<s368*>()->s374() );
else
s585 = s307.s15<s323*>();
Iterator* s1012 = s585->s311( NULL );
while( 1 ) {
s482 p = s1012->s312();
if( p.s13() )
break;
s627[0] = s1012->Idx();
s627[1] = p.s15<s481*>();
if( lambda.s14() ) {
if( ( ( bool )*(s480*)lambda->s494( 0, 0 ) ) == true ) {
*s680.s15<s357*>()->s354() = true;
break;}}
else {
if( ( ( bool )*p.s15<s480*>() ) == true ) {
*s680.s15<s357*>()->s354() = true;
break;}}}
return s680;}
s2061::s2061( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s2062, s694 ){
s273.assign( l.begin(), l.end() );
s490 = 0;}
void
s2061::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
s482 par = s273[0];
s482 s2071 = par;
s1053 pt = par->s349();
for( size_t n = 1; n < s273.size(); ++n ) {
par = s273[n];
if( !par->s1529( pt ) ) {
if( s2071->s1529( par->s349() ) ) {
pt = par->s349();
s2071 = par;}
else
throw new s16( L"incompatible types in '(first)' function" );}}
s583 = s299->TR().s515( pt, ns, ns->s297() );
s490 = pt;
s1251();}
s483 s2061::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
for( size_t n = 0; n < s273.size(); ++n ) {
s483 s152 = s273[n]->s494( 0, 0 );
if( ( bool )*( (s481*)( s152 ) ) ) {
s583 = s152;
return s583;}}
return s362;}
s1923::s1923( s261* s299, s271* s589, s588* s590, vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1928, s694 ){
for( size_t n = 1; n < l.size(); ++n ) {
vector<s270*>& pl = ( (s558*)l[n] )->s599();
pl.insert( begin( pl ), l[n-1] );}
s273.push_back( l.back() );}
void
s1923::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
s490 = s273[0]->s349();
s583 = s299->TR().s515( s349(), s585, s585->s297() );
s1251();}
s483 s1923::s494( s480**, size_t  ){
return s273[0]->s494( 0, 0 );}
vector<wstring> s2191( { L"where:" } );
s2192::s2192( s261* s299, s271* s589, s588* s590, vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s2193, s694, true ){
TDException s960( s7::CLTDFilter_ctor1, s925, s694, L"wrong '(filter ...)' call" );
if( l.size() > 5 )
throw s960.s992( L"too many arguments" );
if( l.size() < 2 )
throw s960.s992( L"too few arguments" );
s588::s1231( ( vector<s270*>& )l, s2191 );
s2196 = l[0];
size_t bas = 1;
if( l[1]->s349() == s1403 ) {
range = (s382*)l[1];
bas = 2;}
if( l.size() == 1 + bas ) {
s1062 = l[bas];}
if( l.size() == 2 + bas ) {
where = l[1 + bas];}
else if( l.size() == 3 + bas ) {
if( l[bas]->s491() != s1055 || ((s368*)l[bas])->Id() != s1225 )
throw s960.s992( L"expected the 'where:' clause" );
where = l[1 + bas];
s1062 = l[2 + bas];}
s490 = 0;}
void
s2192::s497( const s271* s872, bool proc ){
TDException s960( s7::s2190, s925, s600(), L"wrong parameters to '(filter ...)' call");
if( s2196.s13() )
return;
if( s2196->s491() == s472 ) {
s486 rf = s2196.s15<s368*>();
if( rf->s378().s13() )
rf->s497( s872 );
s977 = rf.s15<s368*>()->s374();}
else if( s2196->s491() == s474 ) {
s482 tmp = s270::s1010( s299, s2196, (s271*)s872, (s588*)s872, s872->s297(), false );
s2196 = tmp;
s977 = s2196->s493();}
else {
s977 = (s480*)s270::s1010( s299, s2196, (s271*)s872, (s588*)s872, s872->s297(), false );}
if( !s299->TR().s1453( s977->s349(), s1500::s1495 ) )
throw s960.s992( L"the type is not rangeable: " + s977->s350() );
if( s977->s491() == s471 ) {}
else if( s977->s491() == s477 ) {}
else
throw s960.s992( L"unsupported container type" );
if( where.s14() ) {
if( where->s491() == s472 )
where.s15<s368*>()->s497( s872 );
else {
s482 tmp = s270::s1010( s299, where, (s271*)this, (s588*)s872, s872->s297(), false );
where = tmp;}}
if( s1062.s14() ) {
if( s1062->s491() == s472 ) {
s1062.s15<s368*>()->s497( s872 );}
else {
if( s1062->s491() != s1234 ) {
s482 tmp = s270::s1010( s299, s1062, (s271*)s872, (s588*)s872, s872->s297(), false );
s1062 = tmp;}}}
s490 = s977->s349();
s583 = s299->TR().s515( s349(), s585, s585->s297() );
s1251();}
s483 s2192::s494( s480**, size_t  ){
std::vector<s482>s854( 1 );
s680 = new s313( s299, s977.s15<s323*>()->ValType(), s585, s600() );
s680->s497( s585, true );
if( s2196->s491() == s473 ) {
s977 = s2196->s494( 0, 0 );}
Iterator* it = s977.s15<s323*>()->s311( NULL );
while( 1 ) {
s482 p = it->s312();
if( p.s13() )
break;
s854[0] = p;
if( where.s14() ) {
where.s15<s831*>()->s593( s854 );
s483 s152 = where->s494( 0, 0 );
if( !(bool)*s152 )
continue;}
if( s1062.s14() ) {
s1062.s15<s831*>()->s593( s854 );
p = s1062->s494( 0, 0 ).s15<s270*>();}
s680->add( p );}
return s680;}
vector<wstring> s950( { L"else", L"elsif" } );
s605::s605( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694,
bool s2159 )
: s588( s299, s589, s590, s590, s562, s229, s694, false, s2159 ){
wstring s704 = L"malformed syntax of 'if' statement: ";
if( l.size() < 2 )
throw new s16( s704 + L"too few arguments." );
s273.assign( l.begin(), l.end() );
s588::s1231( ( vector<s270*>& )l, s950 );}
s605::s605( const s605& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), right.s600(), false, right.s2158 ){
for( size_t n = 0; n < right.s617.size(); ++n )
s617.push_back( right.s617[n]->s332( this, s589 ) );
for( size_t n = 0; n < right.s618.size(); ++n ) {
s618.push_back( s576() );
for( size_t m = 0; m < right.s618[n].size(); ++m )
s618.back().push_back( right.s618[n][m]->s332( this, s589 ) );}
s490 = 0;// Types.Null;
}
void s605::s729( bool proc ){
wstring s704 = L"malformed syntax of 'if' statement: ";
s617.push_back( s273[0] );
s618.push_back( s576() );
s618.back().push_back( s273[1] );
if( s273.size() > 2 ) {
size_t n = 2;
while( n < s273.size() ) {
s482 p = s273[n];
s469 pc = s273[n]->s491();
if( pc == s1055 ) {
if( p.s15<s368*>()->Id() == s1214 ) {
if( s273.size() < n + 2 )
throw new s16( s704 + L"incomplete clause" );
s617.push_back( s273[++n] );
s618.push_back( s576() );
s618.back().push_back( s273[n] );}
else if( p.s15<s368*>()->Id() == s1213 ) {
if( s273.size() < n + 1 )
throw new s16( s704 + L"empty clause" );
s618.push_back( s576() );
s618.back().push_back( s273[++n] );}
else
s618.back().push_back( s273[n] );}
else
s618.back().push_back( s273[n] );
n++;}}
if( !proc ) {
size_t s871 = s618[0].size();
s1053 prevPt = s580[s871]->s349();
for( size_t n = 1; n < s618.size(); ++n ) {
s871 += s618[n].size() + 1;
s1053 tmpPt = s580[s871]->s349();
if( tmpPt && tmpPt != Types.No && ( tmpPt != prevPt ) &&
( s580[s871]->s491() == s473 && 
((s588*)s580[s871])->s857() != s2097 ) )
throw new s16( L"the return type of 'if' branches doesn't match" );}
s490 = prevPt;
if( !s490 ) // e.g. break, continue
s490 = Types.Null;}
else
s490 = Types.Null;}
void
s605::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
s729( proc );
s583 = s299->TR().s515( s349(), s585, s585->s297() );
s580.insert( s580.begin(), s583 );
s1251();}
void s605::s2117( s588* s2041, s271* impl, bool s2159 ){
s588::s2117( s2041 ? s2041 : s584.s15<s588*>(), impl ? impl : s585.s15<s271*>(), s2159 );
for( size_t n = 0; n < s617.size(); ++n )
s617[n]->s2117( this, impl ? impl : s585.s15<s271*>(), s2159 ); // ???DEBUG??? 220908
for( size_t n = 0; n < s618.size(); ++n ) {
for( size_t m = 0; m < s618[n].size(); ++m )
s618[n][m]->s2117( this, impl ? impl : s585.s15<s271*>(), s2159 ); // ???DEBUG??? 220907 V
}}
s483 s605::s494( s480**, size_t ){
size_t idx = string::npos;
for( size_t n = 0; n < s617.size(); ++n ) {
if( ( bool )*( s617[n]->s494( 0, 0 ).s15<s480*>() ) ) {
idx = n;
break;}}
if( idx != string::npos || s618.size() > s617.size() ) {
if( idx == string::npos )
idx = s618.size() - 1;
s483 s680;
s576& el = s618[idx];
for( size_t n = 0; n < el.size(); ++n ) {
s680 = el[n]->s494( 0, 0 );
if( s680->s615() < 0 )
break;}
return s680;}
return s362;}
s832::s832( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, /*s562*/ s2097, s845, s694, false, s2159 )
{
if( l.size() > 1 )
throw new s16( s845 + L": too many arguments" );
s273.assign( l.begin(), l.end() );
const s140& s152 = s600()->s267( s2086 );
if( &s152 != &s264 )
s490 = (s1053)s152.s56();
else
s490 = 0;
size_t pl1 = s694->Src().find( L"yield" );
if( pl1 < s694->Src().find( L"return" ) )
s2232 = true;
else
s2232 = false;}
s832::s832( const s832& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), right.s600() ), s2232( right.s2232 ){}
void
s832::s497( const s271* s2160, bool proc ){
if( s273.size() ) {
if( !s490 )
s490 = s1142;
s588::s497( s2160, false );
s270* p = s273[0];
if( p->s491() == s472 || p->s491() == s1326) {
s490 = p->s349();
s583 = s299->TR().s515( s490, (s271*)s2160, s2160->s297() );}
else {
s583 = s580[1]->s493();
s490 = s583->s349();}}
else {
s583 = s362.s15<s480*>();
s490 = s1142;}
s1251();}
s483 s832::s494( s480** s698, size_t s495 ){
if( s2219 != -1 ) {
s2219 = -1;
return s362;}
s483 s680;
if( s273.size() ) {
if( s273[0]->s491() == s472 || s273[0]->s491() == s1326 || s273[0]->s491() == s473 ) {
s680 = s1598( s698, s495 );
if( s680 )
return s680;
s680 = s580[1];}
else {
s680 = s273[0].s15<s480*>();
s680->s497( this, true );}}
else
s680 = new s361( s299 );
if( s2232 ) {		
s680->s1664( s7::s2264 );}
else
s680->s1664( s7::s859 );
s583 = s680;
return s583;}
s270* s832::s332( s588* s2041, s271* impl ) const{
s832* s680 = new s832( *this, impl ? impl : s585.s15<s271*>(), s2041 );
return s680;}
s889::s889( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s893, s694 ), code( 0 ){
if( l.size() > 1 )
throw new s16( s893 + L": wrong number of arguments" );
if( l.empty() )
s273.push_back( new s343( s299, 0 ) );
else
s273.assign( l.begin(), l.end() );
s490 = s1141;}
void
s889::s497( const s271* s1657, bool proc ){
s588::s497( s1657, false );
if( s273[0]->s349() != s1141 )
throw new s16( L"The parameter to (exit ) must have Integer type." );
s1251();}
s483 s889::s494( s480** s698, size_t s495 ){
s588::s494( s698, s495 );
code = (int)*s580[1];
throw new s16( (uint32_t) code );}
s270* s889::s332( s588* s2041, s271* impl ) const{
return new s889( *this );}
vector<wstring> s2400( { L":stopIter" } );
s608::s608( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s258, s694 ), s78( s299 ){
if( l.size() > 2 )
throw new s16( s258 + L": wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.No;
s78.s11();
s588::s1231( ( vector<s270*>& )l, s2400 );}
s608::s608( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s258, NULL ), s78( s299 ){
s490 = Types.No;
s78.s11();}
void
s608::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
s583 = s363.s15<s480*>();
s1251();}
s483 s608::s494( s480** s698, size_t s495 ){
s78.create( s273 );
return &s78;}
s609::s609( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s256, s694, true ), 
s76( s7::s458, s299 ), s616( s299 ){
if( l.size() < 2 )
throw new s16( s256 + L"(): wrong numbers of arguments" );
if( l.back()->s491() != s474 ||
((s558*)l.back())->s298() != s257 )
throw new s16( L"the catch clause must be the last statement in the try block" );
s625.s538( s76.s614(), &s616 );
s579.push_back( (s480*)&s616 );
s627.push_back( (s480*)&s616 );
s628.push_back( s368( s76.s614(), s299 ) );
s581.assign( l.begin(), l.end() );}
s609::s609( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s256, NULL, true ), 
s76( s7::s458, s299 ), s616( s299 ){}
void
s609::s497( const s271* s1657, bool proc ){
s588::s497( s1657, proc );
ctch = s581.back().s15<s610*>();
s581.pop_back();
s1251();}
s483 s609::s494( s480** s698, size_t s495 ){
s480* s680 = NULL;
for( size_t n = 0; n < s581.size(); ++n ) {
s680 = s581[n]->s494( s698, s495 );
if( s680->s615() < 0 ) {
if( s680->s615() == s7::s437 ) {
( (s358*)s680 )->s353( &s616 );
s616.create( vector<s482>{} );
s680 = ctch->s494( &s680, 1 );}
break;}}
s583 = s680;
return s680;}
s610::s610( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s257, s694, true, true ){
s581.assign( l.begin(), l.end() );
s490 = Types.Null;}
s610::s610( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s257, NULL ){
s490 = Types.Null;}
s483 s610::s494( s480** s686, size_t s690 ){
s480* s152;
for( size_t n = 0; n < s581.size(); ++n ) {
s152 = s581[n]->s494( s686, s690 );
if( s152->s615() < 0 ) {
return s152;}}
return s362.s15<s480*>();}
s748::s748( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s744, s694 ){}
void
s748::s497( const s271* s1657, bool proc ){}
s483 s748::s494( s480** s698, size_t s495 ){
return 0;}
s1665::s1665( s261* s299, s271* s589, s588* s590, s1667 ptr_,
s558* cs, const s262* s694 )
: s588( s299, s589, s590, s590, s562, L"", s694 ), s1669( ptr_ ){
subject = cs->s599()[0];
s273.assign( cs->s599().begin() + 1, cs->s599().end() );}
void
s1665::s497( const s271* s1657, bool proc ){
s490 = s585->s349();
s588::s497( s1657, proc );
s1251();}
s483 s1665::s494( s480** s698, size_t s495 ){
s484	s1639 = subject->s494( 0, 0 ).s15<s271*>();
return ( *s1639.*s1669)( &s580[0], s495 );}
s1666::s1666( s261* s299, s271* s589, s588* s590, s1668 ptr_,
const vector<s270*>& s1906, const wstring& s671, s1053 s1064, 
const s262* s694, bool _bd )
: s588( s299, s589, s590, s589, s562, s671, s694, false, _bd ), s1669( ptr_ ){
subject = s1906[0];
s273.assign( s1906.begin() + 1, s1906.end() );
s490 = s1064;
ns = s585;}
s1666::s1666( const s1666& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s589, vector<s481*>(), right.s600(), false, right.s2165() ),
s1669( right.s1669 ){
subject = right.subject;}
void
s1666::s497( const s271* s1657, bool proc ){
s482 s696 = subject;
if( s696->s491() == s472 )
s696 = s696.s15<s368*>()->s374();
if( !s490 ) {
if( s696->s491() == s1234 ) {
if( s277 == s7::s1345 || s277 == L"cp" )
s490 = s696->s349();
else
s490 = s696.s15<s831*>()->s1317();}
else {
if( s277 == L"cp" )
s490 = s696->s349(); }}
s588::s497( s584, proc );
if( 0 && s277 == L"exec" ) {
if( !s696->s1194() )
s696->s497( s1657, proc );}
s1251();}
void s1666::s2117( s588* s2041, s271* impl, bool s2159 ){
s588::s2117( s2041 ? s2041 : s584.s15<s588*>(), impl ? impl : s585.s15<s271*>(), s2159 );
s482 s696 = subject;
s696->s2117( s2041 ? s2041 : s584.s15<s588*>(), impl ? impl : s585.s15<s271*>(), s2159 );}
s483 s1666::s494( s480** s698, size_t s495 ){
s482 s696 = subject;
if( s696->s491() == s472 ) {
s2285 = new s368( *subject.s15<s368*>(), NULL );
s696 = s696.s15<s368*>()->s374();
s2286 = s696;}
else if( s696->s491() == s473 ) {
s483 tmp = s696->s494(0,0);
if( tmp->s615() == s7::s859 )
tmp->s1251();
s696 = tmp.s15<s481*>();}
if( s696->s491() == s1234 ) {
if( s277 == s7::s1345 ) {
auto _subject = s584->s2283();
s831* s680 = new s831( *s696.s15<s831*>(), _subject.s15<s271*>(), 
s584, s2099, s600() );
if( s584->s298() == s232 )
s680->s2180( s2187 );
else
s680->s2180( s2184 );
s680->s497( s585, true );
return s680;}
else if( s277 == L"cp" ) {
return (s480*)s696->s332(0,0);}
else if( s277 == L"exec" ) {
s9<s831> pf;
if( s2285.s14() ) {
s482 tmp = s2285->s374();
if( tmp != s2286 )
s696 = s2286 = tmp;}
if( !s696->s1194() ) {
subject = s696->s332( 0, 0 );
subject->s497( s584, false );
s696 = subject;}
else {
s696.s15<s831*>()->s2209( s584, false );}
pf = s696.s15<s831*>();
if( pf->s2284() ) {
vector<s482> s2111;
for( auto par_ : s273 ) {
s480* par = NULL;
if( par_->s491() == s472 )
par = par_.s15<s368*>()->s374();
else
par = par_.s15<s480*>();
s469 pc = par->s491();
if( pc == s1234 ) {
if( !par->s1194() )
par->s497( s584, false );
s2111.push_back( par );}
else {
if( pc == s473 ) {
if( !par->s1194() )
par->s497( this, false );
else
par->s2117( this, s585, s2165() );}
s2111.push_back( par->s494( 0, 0 ).s15<s481*>() );}}
pf->s2117( pf, s585, s2165() ); 
pf.s15<s831*>()->s593( s2111 );}
s483 s680 = pf->s494( 0, 0 ).s15<s271*>();
if( s680->s615() == s7::s859 || s680->s615() == s7::s2218 ||
s680->s615() == s7::s2264 )
s680->s1664( 0 );
return  s680;}
try {
s696.s15<s831*>()->s593( s273 );}
catch( s16* e ) {
wstring s78 = L"in function '" + s277 + L"'";
if( s600() )
s78 += L" :\n" + TDException::s1896( *s600() );
e->s30( s78 );
throw e;}
return s696->s494( 0, 0 ).s15<s271*>();}
else {
s484 s1639 = subject->s494( 0, 0 ).s15<s271*>();
return ( *s1639.*s1669 )( &s580[0], s495 );}}
s1596::s1596( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1606, s694 ){
s273.assign( l.begin(), l.end() );}
s1596::s1596( const s1596& right )
: s588( right ), cmd( right.cmd ){}
void
s1596::s497( const s271* s1657, bool proc ){
s299->s1996( s2037, s2029 );
s490 = s1142;
s588::s497( s1657, proc );
s1251();}
void s1599( const wstring& cmd, wstring* s1633, bool* done ){
FILE* handle;
char buf[2560];
int status;
#ifdef WIN32
handle = _wpopen( cmd.c_str(), L"rt" );
if( handle == NULL )
perror( "_popen error" );
while( fgets( buf, sizeof( buf ), handle ) ) {
*s1633 += U16(buf);}
status = _pclose( handle );
#else
handle = popen( U8( cmd ).c_str(), "r" );
if( handle == NULL ) {
wcout << L"popen error" << endl;
return;}
while( fgets( buf, sizeof( buf ), handle ) )
*s1633 += U16( buf );
status = pclose( handle );
#endif
if( status == -1 )	{
perror( "_pclose error" );}
*done = true;}
s483 s1596::s494( s480** s686, size_t s690 ){
if( s299->s1996( s2037, s2030 ) )
return s583;
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
wstring cmd_ = s580[1]->to_wstring(), s1634;
bool* pdone = ( (s357*)s580[2] )->s354();
wstring *s1633 = NULL;
if( s580.size() > 3 )
s1633 = ( (s356*)s580[3] )->s354();
else
s1633 = &s1634;
if( s816.joinable() ) {
s816.join();}
s816 = thread( s1599, cmd_, s1633, pdone );
return s583;}
s1594::s1594( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1604, s694 ){
if( l.size() != 2 )
throw new s16( s1604 + L"(): wrong numbers of arguments" );
if( l[0]->s491() != s472 )
throw new s16( s1604 + L"(): the first argument must be a reference" );
s273.assign( l.begin(), l.end() );}
s1594::s1594( const s1594& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s590, vector<s481*>(), right.s600(),
false, true ){}
void
s1594::s497( const s271* s1657, bool proc ){
s490 = s1142;
s588::s497( s1657, proc );
s1251();}
s483 s1594::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
s368* dr = s273[0].s15<s368*>();
s271* mod = dr->s378().s15<s271*>();
mod->s1642( dr->s614(), s580[2] );
return s583;}
s1591::s1591( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, s562, s1602, s694,
false, s2159 ){
if( l.size() != 2 )
throw new s16( s1602 + L"(): wrong numbers of arguments" );
s273.assign( l.begin(), l.end() );}
s1591::s1591( const s1591& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s590, vector<s481*>(), right.s600(),
false, true ){}
void
s1591::s497( const s271* s1657, bool proc ){
s490 = s1142;
s588::s497( s1657, proc );
s1251();}
s483 s1591::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
s271* dr = (s271*)s580[1];
s1589* ob = (s1589*)s580[2];
try {
dr->s1627( ob );}
catch( s16* e ) {
wstring s78 = L"in function " + s298() + L":\n";
s78 += L"during loading object: " + dr->s1658() +
L":" + dr->s350() + L":";
e->s30( s78 );
throw e;}
return s583;}
s1595::s1595( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1605, s694 ){
if( l.size() != 1 )
throw new s16( s1605 + L"(): wrong numbers of arguments" );
s273.assign( l.begin(), l.end() );}
s1595::s1595( const s1595& right )
: s588( right ){}
void
s1595::s497( const s271* s1657, bool proc ){
s490 = s1142;
s588::s497( s1657, proc );
s1251();}
s483 s1595::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
int dr = (int)*(s343*)s580[1];
std::this_thread::sleep_for(std::chrono::milliseconds( dr ) );
return s583;}
s1590::s1590( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694,
bool s2159 )
: s588( s299, s589, s590, s590, s562, s1601, s694, true, s2159 ){
if( l.empty() )
throw new s16( s1601 + L"(): too few arguments" );
s273.assign( l.begin(), l.end() );}
s1590::s1590( const s1590& right, s271* s589, s588* s590 )
: s588( right, s589, s590, s590, vector<s481*>(), right.s600(), true, right.s2165() ){
s583 = s299->TR().s515( s490, s585, s585->s297() );}
void
s1590::s497( const s271* s1657, bool proc ){
s490 = Types.String;
s588::s497( s1657, proc );
s1251();}
s483 s1590::s494( s480** s686, size_t s690 ){
if( s273.size() == 1 ) {
wstringstream buf;
s273[0]->s303( &buf );
*s583.s15<s356*>()->s354() = buf.str();}
else {
s480* pd;
if( s273[0]->s491() == s472 ) {
pd = s273[0].s15<s368*>()->s374();
if( pd == s362 )
pd = s585;}
else
pd = s273[0].s15<s480*>();
*s583.s15<s356*>()->s354() = L"";
for( size_t n = 1; n < s273.size(); ++n ) {
*s583.s15<s356*>()->s354() += pd->trace( s273[n]->to_wstring() );
if( n < s273.size() - 1 )
*s583.s15<s356*>()->s354() += L"; ";}}
s583->s1251();
return s583;}
s1869::s1869( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1870, s694 ){
if( l.size() > 2 )
throw new s16( s1870 + L"(): wrong numbers of arguments" );
s273.assign( l.begin(), l.end() );}
s1869::s1869( const s1869& right )
: s588( right ){}
void
s1869::s497( const s271* s1657, bool proc ){
s490 = s1140;
s588::s497( s1657, proc );
s1251();}
s483 s1869::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);
*s583.s15<s355*>()->s354() = dist( mt );
return s583;}
s270* s605::s332( s588* s2041, s271* impl ) const{
s605* s680 = new s605( *this, impl ? impl : s585.s15<s271*>(), s2041 );
return s680;}
s270* s603::s332( s588* s2041, s271* impl ) const{
return new s603( *this );}
s270* s604::s332( s588* s2041, s271* impl ) const{
return new s604( *this );}
s270* s1395::s332( s588* s2041, s271* impl ) const{
return new s1395( *this );}
s270* s2061::s332( s588* s2041, s271* impl ) const{
return new s2061( *this );}
s270* s1923::s332( s588* s2041, s271* impl ) const{
return new s1923( *this );}
s270* s2192::s332( s588* s2041, s271* impl ) const{
return new s2192( *this );}
s270* s608::s332( s588* s2041, s271* impl ) const{
return new s608( *this );}
s270* s609::s332( s588* s2041, s271* impl ) const{
return new s609( *this );}
s270* s610::s332( s588* s2041, s271* impl ) const{
return new s610( *this );}
s270* s748::s332( s588* s2041, s271* impl ) const{
return new s748( *this );}
s270* s1665::s332( s588* s2041, s271* impl ) const{
return new s1665( *this );}
s270* s1666::s332( s588* s2041, s271* impl ) const{
s1666* s680 = new s1666( *this, impl, s2041 );
return s680;}
s270* s1596::s332( s588* s2041, s271* impl ) const{
return new s1596( *this );}
s270* s1594::s332( s588* s2041, s271* impl ) const{
return new s1594( *this, impl, s2041 );}
s270* s1591::s332( s588* s2041, s271* impl ) const{
return new s1591( *this, impl, s2041 );}
s270* s1595::s332( s588* s2041, s271* impl ) const{
return new s1595( *this );}
s270* s1590::s332( s588* s2041, s271* impl ) const{
return new s1590( *this, impl, s2041 );}
s270* s1869::s332( s588* s2041, s271* impl ) const{
return new s1869( *this );}
vector<wstring> s948( { L"to:", L":sign", L":nosign", L":boolalpha", 
L":noboolalpha", L"width:", L"prec:", L"fill:", L":left", L":right", L":internal", 
L":fixed", L":group", L":nl" } );
s606::s606( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, 
const s262* s694, bool s2159 )
: s588( s299, s589, s590, s589, s562, s250, s694, true, s2159 ), s42( NULL ),
lout( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s694->Src().find( L"lout" );
if( pl1 < s694->Src().find( L"textout" ) )
lout = true;
vector<s270*>tmp( l );
s588::s1231( tmp, s948 );
s273.assign( tmp.begin(), tmp.end() );
s490 = Types.Null;}
s606::s606( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s250, NULL, true, false ), s42( NULL ),
lout( false ){
s490 = Types.Null;}
s606::s606( const s606& right, s271* s589, s588* s590 )
: s588( right, s589, 
s590, s589, vector<s481*>(), right.s600(), true, right.s2165() ), s42( right.s42 ),
lout( right.lout ){
s490 = Types.Null;}
void s606::s497( const s271* s1657, bool proc ){
TDException s960( s7::s1921, s925, s600(), L"malformed '(textout)' function call" );
s588::s497( s1657, proc );
size_t start = 0;
if( s273[0]->s491() == s1055 ) {
if( s273[0].s15<s368*>()->Id() == s1223 ) {
start = 2;
/*s42 = s273[1];
s273.erase( s273.begin(), s273.begin() + 2 );
s580.erase( s580.begin()+1, s580.begin() + 3 );
nlocs = s273.size();
s495 = s580.size();*/
}}
for( size_t n = start; n < s273.size(); ++n ) {
if( s273[n]->s491() == s1055 ) {
int mark = (int)*( s273[n].s15<s368*>() )->s374();
if( mark != s1557 && s273.size() <= n )
s960.s992( L"incorrect usage of formatting marker: " + (s273[n].s15<s368*>())->s614() );
if( mark == s1558 && !s299->TR().s1453(
s273[n + 1]->s349(), s1500::s1537 ) )
s960.s992( L"'width:' formatting marker should have an integer parameter" );
if( mark == s1901 && !s299->TR().s1453(
s273[n + 1]->s349(), s1500::s1537 ) )
s960.s992( L"'fill:' formatting marker should have a char (one symbol string) parameter" );}}
s1251();}
s483 s606::s494( s480** s686, size_t s690 ){
s480* s680 = s1598( s686, s690 );
if( s680 )
return s680;
if( s273[0]->s491() == s1055 ) {
if( s273[0].s15<s368*>()->Id() == s1223 ) {
s42 = s273[1];
s273.erase( s273.begin(), s273.begin() + 2 );
s580.erase( s580.begin()+1, s580.begin() + 3 );
nlocs = s273.size();
s495 = s580.size();}}
s1::s9<Stream> s771;
if( s42.s14() ) {
s469 pc = s42->s491();
if( pc == s473 )
s771 = s42->s494( 0, 0 ).s15<Stream*>();
else if( pc == s472 )
s771 = (Stream*)s42.s15<s368*>()->s374();
else
s771 = s42.s15<Stream*>();}
else
s771 = s1393.s15<Stream*>();
s771->s1554();
uint32_t flags = 0;
for( size_t n = 1; n < s580.size(); ++n ) {
if( s580[n]->s491() == s1055 ) {
int mark = (int)*( (s368*)s580[n] )->s374();
if( mark == s1457 ) {
s771->s1913();}
else if( mark == s1577 ) {
s771->s1911();}
else if( mark == s1951 ) {
s771->s1941();}
else if( mark == s1952 ) {
s771->s1942();}
else if( mark == s1901 ) {
wchar_t c = s580[++n]->to_wstring()[0];
s771->s1897( c );}
else if( mark == s1558 ) {
int w = (int)*s580[++n];
s771->s1555( w );}
else if( mark == s1917 ) {
int pr = (int)*s580[++n];
s771->s1912( pr );}
else if( mark == s1903 ) {
s771->s1899();}
else if( mark == s1904 ) {
s771->s1900();}
else if( mark == s1902 ) {
s771->s1898();}
else if( mark == s1916 ) {
s771->s1910();}
else if( mark == s1556 ) {
flags |= s1546;}
else if( mark == s1557 ) {
s771->s1469( L"" );
n++;}}
else {
s483 s152 = s580[n]->s494( s686, s495 );
s152->s1919( s771 );}}
if( lout )
s771->s1469( L"" );
return s362;}
s270* s606::s332( s588* s2041, s271* impl ) const{
s606* s680 = new s606( *this, impl ? impl : s585.s15<s271*>(), s2041 );
return s680;}
void s606::s2117( s588* s2041, s271* impl, bool s2159 ){
s588::s2117( s2041 ? s2041 : s584.s15<s588*>(), 
impl ? impl : s585.s15<s271*>(), s2159 );
if( s42 )
s42->s2117( s2041 ? s2041 : s584.s15<s588*>(), impl ? impl : s585.s15<s271*>(), s2159 );}
vector<wstring> s1925( { L"from:", L":boolalpha", L":noboolalpha", L"width:", 
L"prec:", L":fixed", L":group", L":nl" } );
s1924::s1924( s261* s299, s271* s589, s588* s590, 
const vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1929, s694 ), source( NULL ),
lin( false ){
if( l.empty() )
throw new s16( L"Wrong numbers of arguments" );
size_t pl1 = s694->Src().find( L"lin" );
if( pl1 < s694->Src().find( L"textin" ) )
lin = true;
vector<s270*>tmp( l );
s588::s1231( tmp, s1925 );
s273.assign( tmp.begin(), tmp.end() );
s490 = Types.Null;}
s1924::s1924( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s1929, NULL ), source( NULL ),
lin( false ){
s490 = Types.Null;}
void s1924::s497( const s271* s1657, bool proc ){
TDException s960( s7::s1920, s925, s600(), L"malformed '(textin)' function call" );
s588::s497( s1657, proc );
if( (s273[0]->s491() == s1055 && s273[0].s15<s368*>()->Id() == s1216 ) ||
(s299->TR().s1453( s273[0]->s349(), s1500::s1493 ))) {
int s372 = 1;
if( s273[0]->s491() == s1055 )
s372 = 2;
source = s273[s372 - 1];
s273.erase( s273.begin(), s273.begin() + s372 );
s580.erase( s580.begin()+1, s580.begin() + s372 + 1 );
nlocs = s273.size();
s495 = s580.size();}
for( size_t n = 0; n < s273.size(); ++n ) {
if( s273[n]->s491() == s1055 ) {
int mark = ( int )*( s273[n].s15<s368*>() )->s374();
if( s273.size() <= n )
s960.s992( L"incorrect usage of formatting marker: " + ( s273[n].s15<s368*>() )->s614() );
if( mark == s1558 && !s299->TR().s1453(
s273[n + 1]->s349(), s1500::s1537 ) )
s960.s992( L"'width:' formatting marker should have an integer parameter" );}}
s1251();}
s483 s1924::s494( s480** s686, size_t s690 ){
size_t shift = 1;
for( size_t n = 0; n < nlocs; ++n ) {
if( *( s578 + n ) ) {
s469 pc = ( ( s481* )*( s578 + n ) )->s491();
if( pc == s472 || pc == s1326 )
*( s577 + n + shift ) =
(s480*)( ( s368* )*( s578 + n ) )->s374();
else if( pc == s473 ) {
s973[n + shift] = (s480*)( ( s588* )*( s578 + n ) )->s494( s686, s690 );
*( s577 + n + shift ) = s973[n + shift];}}}
s1::s9<Stream> src;
if( source.s14() ) {
s469 pc = source->s491();
if( pc == s473 )
src = source->s494( 0, 0 ).s15<Stream*>();
else if( pc == s472 )
src = (Stream*)source.s15<s368*>()->s374();
else
src = source.s15<Stream*>();}
else
src = s1391.s15<Stream*>();
src->s1554();
for( size_t n = 1; n < s580.size(); ++n ) {
if( s580[n]->s491() == s1055 ) {
int mark = (int)*( (s368*)s580[n] )->s374();
if( mark == s1951 ) {
src->s1935();}
else if( mark == s1952 ) {
src->s1937();}
else if( mark == s1558 ) {
int w = (int)*s580[++n];
src->s1940( w );}
else if( mark == s1917 ) {
int pr = (int)*s580[++n];
src->s1938( pr );}
else if( mark == s1916 ) {
src->s1936();}}
else {
s483 s152 = s580[n]->s494( s686, s495 );
s152->s1943( src );}}
if( lin )
src->ws();
return s362;}
s270* s1924::s332( s588* s2041, s271* impl ) const{
return new s1924( *this );}
s607::s607( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s255, s694 ){
if( l.size() != 1 )
throw new s16( s255 + L"(): wrong numbers of arguments" );
s273.assign( l.begin(), l.end() );}
s607::s607( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s255, NULL ){}
void s607::s497( const s271* s589, bool proc ){
s299->s1996( s2036, s2029 );
s806::Cont s1268;
wstring ts = Types( s299, Types.Tuple )->s350() + L"<" + 
Types( s299, Types.Bool )->s350() +
L" " + Types( s299, Types.String )->s350() + L">";
s490 = ((s951*)Types( s299, Types.Tuple ))->s1185( ts, s1268 );
s588::s497( s589, proc );}
s483 s607::s494( s480** s698, size_t s495 ){
s951* s680 = s583.s15<s951*>();
s680->clear();
if( s299->s1996( s2036, s2030 ) ) {
s680->s317().push_back( s367 );
s680->s317().push_back( new s356( s299, L"the '(eval)' function is disabled by current security settings" ) );
return s680;}
try {
s483 s152;
if( s273[0]->s491() == s472 )
s152 = s273[0].s15<s368*>()->s374();
else if( s273[0]->s491() == s473 )
s152 = s273[0].s15<s588*>()->s494( NULL, 0 );
else
s152 = s273[0].s15<s480*>();
wstring f = s152->s494( 0, 0 )->to_wstring();
if( f[0] == L'(' ) {
vector<s482> s905;
s939 ast_ = new s262( f, s600()->Nqj(), (s262*)s600() );
s487 cs = s588::s1109( *ast_, s299, s585, s297(), true );
s905.push_back( cs );
s485 s903 = s588::s597( cs, s299, s585, this, s297(), false );
s903->s497( s585, true );
s483 res1 = s903->s494( 0, 0 );
if( !res1 || res1->s615() != s7::s437 ) {
s680->s317().push_back( s366 );
s680->s317().push_back( new s356( s299, res1 ? res1->to_wstring() : L"" ) );}
else {
s680->s317().push_back( s367 );
s680->s317().push_back( new s356(s299, res1.s15<s358*>()->Msg() ) );}}
else {
vector<wstring> l;
s483 res1 = s299->callFunc( f, l );
s680->s317().push_back( s366 );
s680->s317().push_back( new s356( s299, res1 ? res1->to_wstring() : L"" ) );}}
catch( s16* e ) {
s680->s317().push_back( s367 );
s680->s317().push_back( new s356(s299, e->Msg() ) );}
return s680;}
s270* s607::s332( s588* s2041, s271* impl ) const{
return new s607( *this );}
s1::s9<s261> s612::s899;
s612::s612( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694, bool s2159 )
: s588( s299, s589, s590, s590, s562, s260, s694, true, s2159 ){
if( l.size() != 1 )
throw new s16( s260 + L"(): wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.Null;}
s612::s612( s261* s299 )
: s588( s299, NULL, NULL, NULL, s562, s260, NULL ){
s490 = Types.Null;}
s483 s612::s494( s480** s698, size_t s495 ){
vector<wstring> s904;
for( size_t n = 0; n < s273.size(); ++n ) {
s904.push_back( s273[n]->s494( 0, 0 )->to_wstring() );}
if( s899.s13() ) {
s899 = new s261();
s899->s1884( true );}
else
s899->reset();
s899->s208( s904[0] );
s583 = s899->run( s904 );
return s583;}
s270* s612::s332( s588* s2041, s271* impl ) const{
return new s612( *this );}
s790::s790( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s765, s694 ){
if( l.size() != 1 )
throw new s16( s765 + L"(): wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.Null;}
s483 s790::s494( s480** s698, size_t s495 ){
wstring s193 = s273[0]->s494( s698, s495 )->to_wstring();
s299->s208( s193 );
return s362;}
s270* s790::s332( s588* s2041, s271* impl ) const{
return new s790( *this );}
s768::s768( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l,
const s262* s694 )
: s588( s299, s589, s590, s590, s562, s814, s694 ){
s897 = s589->s297();
if( l.size() != 1 )
throw new s16( s814 + L"(): wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.Null;}
s483 s768::s494( s480** s698, size_t s495 ){
s270* par = s273[0];
wstring s895;
if( par->s491() == s472 )
s895 = ((s368*)par)->s494( 0, 0 )->to_wstring();
else
s895 = par->s494( 0, 0 )->to_wstring();
try {
s271* ob = ((s271*)s299->s638( s897, s897 ));
ob->s552( s895, s897 );}
catch( s16* e ) {
wcout << L"TDException was raised: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;}
return s362;}
s270* s768::s332( s588* s2041, s271* impl ) const{
return new s768( *this );}
s1296::s1296( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l,
const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1306, s694 ){
if( l.size() != 1 )
throw new s16( s1306 + L"(): wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.Null;}
s483 s1296::s494( s480** s698, size_t s495 ){
s270* par = s273[0];
wstring s666;
if( par->s491() == s472 )
s666 = ((s368*)par)->s494( 0, 0 )->to_wstring();
else
s666 = par->s494( 0, 0 )->to_wstring();
try {
s299->s1340( s666 );}
catch( s16* e ) {
wcout << L"An error occured while unloading module: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s362;}
s270* s1296::s332( s588* s2041, s271* impl ) const{
return new s1296( *this );}
s1597::s1597( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l,
const s262* s694 )
: s588( s299, s589, s590, s590, s562, s1607, s694 ){
if( l.size() != 1 )
throw new s16( s1607 + L"(): wrong number of arguments" );
s273.assign( l.begin(), l.end() );
s490 = Types.Null;}
s483 s1597::s494( s480** s698, size_t s495 ){
s270* par = s273[0];
wstring s666;
if( par->s491() == s472 )
s666 = ((s368*)par)->s494( 0, 0 )->to_wstring();
else
s666 = par->s494( 0, 0 )->to_wstring();
try {
s299->s1650( s666 );}
catch( s16* e ) {
wcout << L"An error occured while unloading file modules: \n\n" << e->Msg() << endl;}
catch( std::exception& e ) {
wcout << L"An exception was raised: \n\n" << U16( e.what() ) << endl;}
return s362;}
s270* s1597::s332( s588* s2041, s271* impl ) const{
return new s1597( *this );}
s1766::~s1766(){
release();}
void s1766::release(){
for( auto i : s864 )
i.second.clear();
s864.clear();}
s1767::s1767( s1766* s1791 ) 
: pdb( s1791 ), fi( s1832), se(s1832) {
ptr = new s1769();}
s1767::~s1767(){
if( ptr ) {
ptr->clear();
delete ptr;}}
const vector<wstring> s1763::s1863 = { L"", L"==", L"<", L">", L"<=", L">=", L"<>" };
s1763::s1763( s261* s299, s271* s585, const std::wstring& s, size_t& pos ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
size_t s69 = s68;
if( s[s68] == L'"' ) {
s4::s993( s, s69, s4::s48 );
field = s.substr( s68+1, s69 - s68 - 2 );}
else {
s69 = s.find_first_of( s4::s48, s68 );
field = s.substr( s68, s69 - s68 );}
s69 = s68 = s.find_first_not_of( s4::s48, s69 );
s4::s993( s, s69, s4::s48 );
wstring s1850 = s.substr( s68, s69 - s68 );
auto s1821  = std::find( s1863.begin(), s1863.end(), s1850 );
if( s1821 == s1863.end() )
throw new s16( L"unknown operation in query string: " + s1850 );
op = (s1763::s1776) std::distance( s1863.begin(), s1821 );
s6::s1754.push_back( s1721.s150 );
s6::s141 nq = new s6::s140( NULL, s, s69, s1721 );
s6::s1754.pop_back( );
s939 s694 = new s262( L"", *nq, NULL );
par = s270::s501( *s694, s299, s585, s585->s297() );
pos = s69 == s.size() ? string::npos : s69;
return;}
void s1763::s497( s271* ns ){
if( par->s491() == s472 ) {
par->s497( ns );}}
void s1763::select( s1766* pdb, s1772& s152 ){
if( par->s491() == s472 )
s346 = par.s15<s368*>()->s374();
else
s346 = par;
pdb->select( field, op, s346.s15<s480*>(), s152 );}
s1764::s1764( s261* s299, s271* s585, const std::wstring& s, size_t& pos, s1765 s1788 )
: s1802( s1788 ){
size_t s68 = s.find_first_not_of( s4::s48, pos );
if( s[s68] == L'(' ) {
s1795( s299, s585, s, ++s68 );}
else
s1795( s299, s585, s, s68 );}
s1764::s1764( const s1764& r )
: s1802( r.s1802 ), subs( r.subs ), s1796( r.s1796 ){}
void s1764::s497( s271* ns ){
for( auto i : subs )
i.s497( ns );
for( auto i : s1796 )
i.s497( ns );}
void s1764::s1795( s261* s299, s271* s585, const std::wstring& s, size_t& pos ){
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
subs.push_back( s1764( s299, s585, s, s68, s1798 ) );}
else if( s[s68] == L'A' || s[s68] == L'a' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1853 = s.substr( s68, pl - s68 );
if( s1853 != L"AND" && s1853 != L"and" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 3;
if( s1802 == s1798 )
s1802 = s1797;
else if( s1802 == s1797 )
(void)0;
else {
if( subs.empty() && s1796.empty() )
throw new s16( L"wrong query syntax: 'AND' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1764( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1796.clear();
s1802 = s1797;}}
else if( s[s68] == L'O' || s[s68] == L'o' ) {
size_t pl = s.find_first_of( s4::s48, s68 );
wstring s1853 = s.substr( s68, s.size() - pl + 1 );
if( s1853 != L"OR" && s1853 != L"or" )
throw new s16( L"unrecognized keyword in the query string: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
s68 += 2;
if( s1802 == s1798 )
s1802 = s1799;
else if( s1802 == s1799 )
(void)0;
else {
if( subs.empty() && s1796.empty() )
throw new s16( L"wrong query syntax: 'OR' connector is misplaced: " +
s.substr( pos, 20 ), (uint32_t)s16::s17::s20 );
subs.push_back( s1764( *this ) );
subs.erase( subs.begin(), subs.begin() + ( subs.size() - 2 ) );
s1796.clear();
s1802 = s1799;}}
else {
s1796.push_back( s1763( s299, s585, s, s68 ) );
if( s68 != string::npos )
++s68;}}}
bool s1787( s815 l, s815 r ){
return ( size_t )&( *l ) < ( size_t )&( *r );}
void s1764::select( s1766* pdb, s1767* s152 ){
s1774 s1815;
vector<s1769> s1847;
s1767 *s1861, *s1860;
for( size_t n = 0; n < s1796.size(); ++n ) {
s1772 s1061;
s1796[n].select( pdb, s1061 );
s1815.insert( s1061 );}
s1861 = pdb->s1803();
s1860 = pdb->s1803();
auto it = begin( s1815 );
if( s1815.size() ) {
if( s1802 == s1797 || s1815.size() == 1 ) {
pdb->intersect( *it, s152 );
s152->sort();}}
for( ++it; it != end( s1815 ); ++it ) {
s1861->clear();
if( s1802 == s1797 ) {
pdb->intersect( *it, s1861 );
s1861->sort();
if( s152->empty() )
s152->swap( s1861 );
else {
std::set_intersection( begin( s152->s317() ), end( s152->s317() ), 
begin( s1861->s317() ), end( s1861->s317() ), 
back_inserter( s1860->s317() ), s1787 );
s152->swap( s1860 );
s1860->clear();}}}
for( size_t n = 0; n < subs.size(); ++n ) {
subs[n].select( pdb, s1861 );
if( s1802 == s1797 ) {
s1861->sort();
if( s152->empty() )
s152->swap( s1861 );
else {
std::set_intersection( begin( s152->s317() ), end( s152->s317() ),
begin( s1861->s317() ), end( s1861->s317() ),
back_inserter( s1860->s317() ), s1787 );
s152->swap( s1860 );
s1860->clear();}}
s1861->clear();}}
vector<wstring> s949( { L"select:", L":select", L":update", L"reduce:", 
L":reduce", L"all", L"as:", L"where:", L"satisfying:", L"using:", L":distinct",	
L"sortby:", L":asc", L":desc", L"limit:", L"set:" } );
struct s841{
size_t idx;
s841( size_t s862 ): idx( s862 ){}
bool operator()( const s483 l, const s483 r ) const{
s483 ld = l.s15<s743*>()[idx];
s483 rd = r.s15<s743*>()[idx];
return ld->operator<( (s480*)&(*rd) );}
};
void s784::s1708( const std::vector<s270*>& l_, TDException& s960 ){
const size_t s1047 = 9;
std::vector<s270*> l( s1047, NULL );
s1697* sqr = new s1697;
s1696* sqp = new s1696;
sqr->verb = s737::s1761;
s368* rf = (s368*)l_[1];
if( rf->Id() == s2055 )
l[1] = new s368( L"all", s299, s1055 );
size_t s978 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s491() == s1055 ) {
s368* rf = (s368*)l_[n];
if( rf->Id() == s1207 ) s978 = 2;
else if( rf->Id() == s1206 ) {
s978 = s1137;
l[1] = l_[n];}
else if( rf->Id() == s1225 ) s978 = 3;
else if( rf->Id() == s1828 ) s978 = 4;
else if( rf->Id() == s1211 ) {
s978 = s1137;
sqr->distinct = 1;}
else if( rf->Id() == s1222 ) {
sqr->s881 = s1697::s830::s821;
s978 = 6;}
else if( rf->Id() == s1208 ) {
if( s978 != 7 )
throw s960.s992( L"the '" + rf->s614() + L"' specifier is misplaced" );
s978 = s1137;
sqr->s881 = s1697::s830::s821;}
else if( rf->Id() == s1210 ) {
if( s978 != 7 )
throw s960.s992( L"the '" + rf->s614() + L"' specifier is misplaced" );
s978 = s1137;
sqr->s881 = s1697::s830::s824;}
else if( rf->Id() == s1220 ) 
s978 = 8;
else
throw s960.s992( L"misplaced query keyword: " + s949[rf->Id()] );}
else
l[s978++] = l_[n];}
s803 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1064 = l[2];
sqp->where = l[3];
sqp->s1851 = l[4];
sqp->s882 = l[6];
sqp->s867 = l[8];}
void s784::s1709( const std::vector<s270*>& l_, TDException& s960 ){
const size_t s1047 = 4;
std::vector<s270*> l( s1047 );
s1707* sqr = new s1707;
s1706* sqp = new s1706;
sqr->verb = s737::s1762;
size_t s978 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s491() == s1055 ) {
s368* rf = (s368*)l_[n];
if( rf->Id() == s1739 ) s978 = 1;
else if( rf->Id() == s1225 ) s978 = 2;
else if( rf->Id() == s1828 ) s978 = 3;
else
throw s960.s992( L"misplaced query keyword: " + s949[rf->Id()] );}
else
l[s978++] = l_[n];}
s803 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->where = l[2];
sqp->s1851 = l[3];
if( sqp->what.s13() )
throw s960.s992( L"the 'UPDATE' query must include 'SET' and `SATISFYING` clauses" );}
void s784::s1986( const std::vector<s270*>& l_, TDException& s960 ){
const size_t s1047 = 6;
std::vector<s270*> l( s1047, NULL );
s1970* sqr = new s1970;
s1969* sqp = new s1969;
sqr->verb = s737::s2043;
s368* rf = (s368*)l_[1];
if( rf->Id() == s2054 )
l[1] = new s368( L"all", s299, s1055 );
size_t s978 = 1;
for( size_t n = 2; n < l_.size(); ++n ) {
if( l_[n]->s491() == s1055 ) {
s368* rf = (s368*)l_[n];
if( rf->Id() == s1207 ) s978 = 2;
else if( rf->Id() == s1206 ) {
s978 = s1137;
l[1] = l_[n];}
else if( rf->Id() == s1225 ) s978 = 3;
else if( rf->Id() == s1828 ) s978 = 4;
else if( rf->Id() == s2005 ) s978 = 5;
else
throw s960.s992( L"misplaced query keyword: " + s949[rf->Id()] );}
else
l[s978++] = l_[n];}
s803 = sqr;
qp = sqp;
db = l_[0];
sqp->what = l[1];
sqp->s1064 = l[2];
sqp->where = l[3];
sqp->s1851 = l[4];
sqp->s2041 = l[5];}
s784::s784( s261* s299, s271* s589, s588* s590, 
const std::vector<s270*>& l_, const s262* s694 )
: s588( s299, s589, s590, s590, s562, s811, s694 ), s2022( s7::s1966, s299 ),
s726( s7::s459, s299 ), s776( new s271( s299, 0, s477, NULL, NULL, s2184 ) ),
s1844( NULL ){
TDException s960( s7::s1100, s925, s694 );
if( l_.size() < 3 )
throw s960.s992( L"too few arguments." );
s588::s1231( ( vector<s270*>& )l_, s949 );
s625.s538( s726.s614(), s776.s15<s480*>() );
s579.push_back( s776.s15<s480*>() );
s273.push_back( s776.s15<s480*>() );
s627.push_back( s776.s15<s480*>() );
s628.push_back( s368( s726.s614(), s299) );
if( l_[1]->s491() != s1055 )
throw s960.s992( L"the second participant must be a query verb: SELECT, UPDATE, etc." );
s368* rf = (s368*)l_[1];
if( rf->Id() == s1221 || rf->Id() == s2055 )
s1708( l_, s960 );
else if( rf->Id() == s1741 )
s1709( l_, s960 );
else if( rf->Id() == s2004 || rf->Id() == s2054 )
s1986( l_, s960 );}
s784::~s784(){
if( s1844 )
delete s1844;}
s481* s784::s1790( const std::wstring& s ){
size_t pos = 0;
if( s1844 )
delete s1844;
s1844 = new s1764( s299, this, s, pos, s1764::s1798 );
return NULL;}
void s784::s2047( s1766* base, s482 what, vector<wstring>& s888,
std::vector<s485>& s2045, vector<wstring>& s1852 ){
s469 pc = what->s491();
s483 s1749 = what.s15<s480*>();
if( pc == s472 ) {
s486 rf = what.s15<s368*>();
s1749 = rf->s374();}
else if( pc == s1055 ) {
s486 rf = what.s15<s368*>();
if( rf->s614() == L"all" || rf->s614() == L"ALL" ) {
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + 
Types( s299, Types.String )->s350() + L">";
s1053 s1505 = ((s313*)Types( s299, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s1749 = s299->TR().s515( s1505, ns, ns->s297() );
vector<wstring> s2058;
base->s1817( s2058 );
for( auto s : s2058 )
s1749.s15<s313*>()->add( new s356( s299, s ) );}
else
throw new s16( L"fields for selection are not recognized" );}
else if( pc == s471 ) {
(void)0;}
s806 vt = s299->TR().s1005( s1749->s349() );
if( vt.s349() == s1704 || vt.s349() == s1703 ) {
const vector<s482>* v = NULL;
if( vt.s349() == s1704 )
v = &s1749.s15<s313*>()->s317();
else
v = &s1749.s15<s743*>()->s317();
s2045.resize( v->size() );
for( size_t n = 0; n < v->size(); ++n ) {
wstring s851;
auto it = ( *v )[n];
if( it->s491() == s472 ) {
if( it.s15<s368*>()->s378().s13() )
it->s497( this );
s851 = it.s15<s368*>()->s374()->to_wstring();}
else
s851 = it->to_wstring();
size_t s875 = s4::s87.find( s851[0] );
if( s875 != string::npos )
s851 = s4::s52( s851, wstring( 1, s4::s87[s875] ) );
size_t pl = s851.find( L"|=" );
if( s851[0] == L'(' ) {
vector<wstring> s80;
size_t pos = 0;
s262::s287( s851, pos, s80 );
if( s80.size() > 2 )
throw new s16( L"too many arguments in field expression: " + s851 );
s483 s1995 = s299->TR().s515( base->s1999( s80[1] ), ns, s297() );
std::vector<s270*> pl = { s1995 };
s558 cs( s299, s80[0], pl, NULL );
auto s2039 = s588::s597( &cs, s299, ns, (s588*)this, s297(), false );
s2039->s497( this, false );
s2045[n] = s2039;
s888.push_back( s80[1] );}
else if( pl != string::npos ) {
wstring s2125 = s4::s52( s851.substr( 0, pl ), s4::s48 );
wstring s2124 = s4::s52( s851.substr( pl + 2 ), s4::s48 );
s888.push_back( s2125 );
s1852.push_back( s2124 );}
else {
s888.push_back( s851 );
s1852.push_back( s851 );}}}}
void s784::s1710( const s271* s1657, bool proc ){
TDException s960( s7::s913, s925, past );
s469 pc = db->s491();
if( pc == s474 ) {
db = s597( db.s15<s558*>(), s299, s585, this, s297(), false );
db->s497( this );}
else if( pc == s472 )
db.s15<s368*>()->s497( this );
else
throw s960.s992( L"the database must be specified by a name or expression." );
s1696* sqp = qp.s15<s1696*>();
if( sqp->s1064.s14() ) {
sqp->s1064->s497( this );
s806::Cont s1268;
wstring sv = sqp->s1064->s350();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + sv + L">";
s490 = ( (s313*)Types( s299, Types.Vector ) )->s1185( this, ts, s1704, s1268 );}
else {
if( s299->TR().s1453( db->s349(), s1500::s1495 ) )
s490 = db.s15<s323*>()->s349();
else
throw s960.s992( L"the 'AS' clause is missing." );}
s588::s497( s1657, proc );
pc = sqp->what->s491();
if( pc == s474 ) {
sqp->what = s597( sqp->what.s15<s558*>(), s299, s585, this, s297(), false );
sqp->what->s497( this );}
else if( pc == s472 )
sqp->what.s15<s368*>()->s497( this );
else if( pc == s471 || pc == s1055 )
(void)0;
else
throw s960.s992( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s349() != Types.String )
throw s960.s992( L"the 'WHERE' clause must be a string." );
if( s299->TR().s1453( db->s349(), s1500::s1495 ) )
throw s960.s992( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1790( sqp->where->to_wstring() );}
if( sqp->s1851 ) {
pc = sqp->s1851->s491();
if( pc == s474 ) {
sqp->s1851 = s597( sqp->s1851.s15<s558*>(), s299, s585, this, s297(), false );
sqp->s1851.s15<Transd*>()->s497( s1657, false );
s828 s874;
sqp->s1851.s15<Transd*>()->s807( s874 );}
else
throw s960.s992( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s867.s14() ) {
pc = sqp->s867->s491();
if( pc == s474 ) {
sqp->s867 = s597( sqp->s867.s15<s558*>(), s299, s585, this, s297(), false );
sqp->s867->s497( this );}
else if( pc == s472 )
sqp->s867.s15<s368*>()->s497( this );
else if( sqp->s867->s349() != s1141 )
throw s960.s992( L"the limit must be specified by a number, variable or expression." );}}
void s784::s1711( const s271* s1657, bool proc ){
s1706* sqp = qp.s15<s1706*>();
s490 = s1141;
TDException s960( s7::s913, s925, past );
s588::s497( s1657, proc );
s469 pc = db->s491();
if( pc == s474 ) {
db = s597( db.s15<s558*>(), s299, s585, this, s297(), false );
db->s497( this );}
else if( pc == s472 )
db.s15<s368*>()->s497( this );
else
throw s960.s992( L"the database must be specified by a name or expression." );
pc = sqp->what->s491();
if( pc == s474 ) {
sqp->what = s597( sqp->what.s15<s558*>(), s299, s585, this, s297(), false );
sqp->what.s15<Transd*>()->s497( s1657, false );}
else
throw s960.s992( L"the 'SET' clause must be a lambda" );
if( sqp->where ) {
if( sqp->where->s349() != Types.String )
throw s960.s992( L"the 'WHERE' clause must be a string." );
if( s299->TR().s1188( db->s349(), s1500::s1495 ) )
throw s960.s992( L"the 'WHERE' clause cannot be used in Dataset queries." );
sqp->where = s1790( sqp->where->to_wstring() );}
if( sqp->s1851 ) {
pc = sqp->s1851->s491();
if( pc == s474 ) {
sqp->s1851 = s597( sqp->s1851.s15<s558*>(), s299, s585, this, s297(), false );
sqp->s1851.s15<Transd*>()->s497( s1657, false );}
else
throw s960.s992( L"the 'SATISFYING' clause must be a lambda." );}}
void s784::s1988( const s271* s1657, bool proc ){
s1969* sqp = qp.s15<s1969*>();
/*s806::Cont s1268;
wstring sv = sqp->s1064->s350();
size_t b = sv.find( L'<' );
size_t e = sv.find( L'>' );
for( size_t n = b; n < e; ++n )
if( isdigit( sv[n] ) && sv[n - 1] == L'<' )
sv.erase( n--, 1 );
wstring ts = Types( s299, Types.Vector )->s350() + L"<" + sv + L">";
s490 = ((s313*)Types( s299, Types.Vector ))->s1185( ts, s1268 );*/
s490 = s1142; // sqp->s1064->s349();
TDException s960( s7::s913, s925, past );
s2022.s376( 0, s2021 );
s2022.s379( (s480*)this );
s588::s497( s1657, proc );
s469 pc = db->s491();
if( pc == s474 ) {
db = s597( db.s15<s558*>(), s299, s585, this, s297(), false );
db->s497( this );}
else if( pc == s472 )
db.s15<s368*>()->s497( this );
else
throw s960.s992( L"the database must be specified by a name or expression." );
pc = sqp->what->s491();
if( pc == s474 ) {
sqp->what = s597( sqp->what.s15<s558*>(), s299, s585, this, s297(), false );
sqp->what->s497( this );}
else if( pc == s472 )
sqp->what.s15<s368*>()->s497( this );
else if( pc == s471 || pc == s1055 )
(void)0;
else
throw s960.s992( L"the query field(s) must be specified by a name or expression." );
if( sqp->where ) {
if( sqp->where->s349() != Types.String )
throw s960.s992( L"the 'WHERE' clause must be a string." );
sqp->where = s1790( sqp->where->to_wstring() );}
if( sqp->s1851 ) {
pc = sqp->s1851->s491();
if( pc == s474 ) {
sqp->s1851 = s597( sqp->s1851.s15<s558*>(), s299, s585, this, s297(), false );
sqp->s1851.s15<Transd*>()->s497( s1657, false );
s828 s874;
sqp->s1851.s15<Transd*>()->s807( s874 );}
else
throw s960.s992( L"the 'SATISFYING' clause must be a lambda." );}
else {}
if( sqp->s2041 ) {
pc = sqp->s2041->s491();
if( pc == s474 ) {
sqp->s2041 = s597( sqp->s2041.s15<s558*>(), s299, s585, this, s297(), false );
sqp->s2041.s15<Transd*>()->s497( s1657, false );
s828 s874;
sqp->s2041.s15<Transd*>()->s807( s874 );}
else
throw s960.s992( L"the 'USING' clause must be a lambda." );}}
void
s784::s497( const s271* s1657, bool proc ){
if( s803->verb == s737::s1761 )
s1710( s1657, proc );
else if( s803->verb == s737::s1762 )
s1711( s1657, proc );
else if( s803->verb == s737::s2043 )
s1988( s1657, proc );
s1251();}
s483 s784::s1716( s480** s273, size_t s495 ){
s1706* sqp = qp.s15<s1706*>();
s483 s680 = s583;
vector<wstring> s888;
vector<wstring> s1852;
s1::s9<s1766> base;
TDException s960( s7::s914, s922, past );
assert( db->s491() == s472 );
s480* s2048 = db.s15<s368*>()->s374();
if( s299->TR().s1453( s2048->s349(), s1500::s1495 ) )
base = new s2046( s299, ns, (s323*)s2048, s600() );
else
base = (s1766*)s2048;
s1::s1278<s1767> dom = base->s1803();
if( s1844 ) {
s1844->select( base, dom );}
else
base->s1854( dom );
s828 s874;	
sqp->what.s15<Transd*>()->s807( s874 );
for( size_t n = 0; n < s874.size(); ++n ) {
s888.push_back( s874[n].first );}
s874.clear();
if( sqp->s1851.s14() ) {
sqp->s1851.s15<Transd*>()->s807( s874 );
if( s874.empty() )
throw s960.s992( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s874.size(); ++n )
s1852.push_back( s874[n].first );}
vector<s482> s873, pls1;
s873.resize( s1852.size() );
pls1.resize( s888.size() );
int s679 = 0;
dom->s1858();
s483 s152 = s366.s15<s480*>();
while( dom->s1820() ) {
s1::s9<s1768> s1842 = dom->s1830();
if( sqp->s1851.s14() ) {
for( size_t n = 0; n < s1852.size(); ++n )
s873[n] = s1842->s753( s1852[n] ).s15<s481*>();
sqp->s1851.s15<Transd*>()->s593( s873 );
s152 = sqp->s1851->s494( 0, 0 );}
if( s152.s14() && (bool)*s152 ) {
for( size_t n = 0; n < s888.size(); ++n )
pls1[n] = s1842->s753( s888[n] ).s15<s481*>();
sqp->what.s15<Transd*>()->s593( pls1 );
s483 s152 = sqp->what->s494( 0, 0 );
++s679;}}
*s583.s15<s343*>()->s354() = s679;
return s583;}
s483 s784::s1715( s480** s273, size_t s495 ){
s1696* sqp = qp.s15<s1696*>();
s1697* sqr = s803.s15<s1697*>();
s483 s680 = s583;
vector<wstring> s888;
vector<s485> s2045;
vector<wstring> s2142;
vector<wstring> s2137;
s1::s9<s1766> base;
size_t s901 = string::npos;
TDException s960( s7::s914, s922, past );
assert( db->s491() == s472 );
s480* s2048 = db.s15<s368*>()->s374();
if( s299->TR().s1453( s2048->s349(), s1500::s1495 ) )
base = new s2046( s299, ns, (s323*)s2048, s600() );
else
base = (s1766*)s2048;
if( sqp->s867.s14() ) {
if( sqp->s867->s491() == s472 ) {
sqr->s867 = ( int )*( (s343*)sqp->s867.s15<s368*>()->s374() );}
else if( sqp->s867->s491() == s473 ) {
sqr->s867 = (int)*sqp->s867->s494( 0, 0 );}
else
sqr->s867 = (int)*sqp->s867;}
if( sqp->s882.s14() ) {
if( sqp->s882->s491() == s472 ) {
sqr->s880 = sqp->s882.s15<s368*>()->s374()->to_wstring();}
else if( sqp->s882->s491() == s473 ) {
sqr->s880 = sqp->s882->s494( 0, 0 )->to_wstring();}
else
sqr->s880 = sqp->s882->to_wstring();}
s2047( base, sqp->what, s888, s2045, s2142 );
s1::s1278<s1767> dom = base->s1803();
if( s1844 ) {
s1844->select( base, dom );}
else
base->s1854( dom );
s828 s874;
if( sqp->s1851.s14() ) {
sqp->s1851.s15<Transd*>()->s807( s874 );
if( s874.empty() )
throw s960.s992( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s874.size(); ++n ) {
for( size_t m = 0; m < s2142.size(); ++m ) {
if( s874[n].first == s2142[m] )
s2137.push_back( s888[m] );}}}
vector<s482> s873;
s873.resize( s2137.size() );
s583.s15<s313*>()->clear();
dom->s1858();
while( dom->s1820() ) {
s1768* s1842 = dom->s1830();
s483 s1793;
if( sqp->s1851.s14() ) {
for( size_t n = 0; n < s2137.size(); ++n )
s873[n] = s1842->s753( s2137[n] ).s15<s481*>();
sqp->s1851.s15<Transd*>()->s593( s873 );
s1793 = sqp->s1851->s494( 0, 0 );}
else
s1793 = s366.s15<s480*>();
if( s1793.s14() && (bool)*s1793 ) {
s1::s9<s743> s887 = new s743( s299, NULL, L"" );
if( s888.empty() )
s1842->s856( *s887 );
else {
for( size_t n = 0; n < s888.size(); ++n )
s887->add( s1842->s753( s888[n] ).s15<s270*>() );}
s887->s1664( s7::s860 );
s583.s15<s313*>()->add( s887 );}}
if( sqr->distinct != -1 ) {
vector<s482>& s892 = s583.s15<s313*>()->s317();
for( size_t n = 0; n < s892.size(); ++n ) {
s482 s891 = s892[n];
size_t m = n + 1;
while( m < s892.size() ) {
s482 _el1 = s892[m];
if( *s891.s15<s743*>() == _el1.s15<s480*>() )
s892.erase( s892.begin() + m );
else
m++;}}}
if( sqr->s881 != -1 ) {
if( s888.size() && sqr->s880.size() ) {
auto it = std::find( s888.begin(), s888.end(), sqr->s880 );
if( it != s888.end() )
s901 = std::distance( s888.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
else {
vector<wstring> s896;
dom->s1816( s896 );
auto it = std::find( s896.begin(), s896.end(), sqr->s880 );
if( it != s896.end() )
s901 = std::distance( s896.begin(), it );
else
throw new s16( L"TSD query is incosistent: the sort field is not in the result." );}
s1::s9<s890> s894 = new s890;
s894->s900( s901 );
s833 s902( s894 );
s583.s15<s313*>()->sort( sqr->s881 == s1697::s824, &s902 );}
if( sqr->s867 != -1 ) {
s583.s15<s313*>()->s317().resize( sqr->s867 );}
return s680;}
s483 s784::s1991( s480** s273, size_t s495 ){
s1969* sqp = qp.s15<s1969*>();
vector<wstring> s888;
vector<wstring> s2142;
vector<wstring> s2137;
vector<s485> s2045;
TDException s960( s7::s914, s922, past );
s1::s9<s1766> base;
if( db->s491() == s472 ) {
s480* s2048 = db.s15<s368*>()->s374();
if( s299->TR().s1453( s2048->s349(), s1500::s1495 ) )
base = new s2046( s299, ns, (s323*)s2048, s600() );
else
base = (s1766*)s2048;}
else if( db->s491() == s473 ) {
s480* s2048 = db->s494( 0, 0 );
if( s299->TR().s1453( s2048->s349(), s1500::s1495 ) )
base = new s2046( s299, ns, (s323*)s2048, s600() );
else
base = (s1766*)s2048;}
else
throw s960.s992( L"TSD query cannot be performed on a non-TSD object" );
s1771::iterator s1822, s1823;
try {
s2047( base, sqp->what, s888, s2045, s2142 );}
catch( s16* e ) {
throw s960.s992( L"error while parsing WHAT clause: " + e->Msg() );}
s1::s1278<s1767> dom = base->s1803();
if( s1844 ) {
s1844->select( base, dom );}
else
base->s1854( dom );
s828 s874;
if( sqp->s1851.s14() ) {
sqp->s1851.s15<Transd*>()->s807( s874 );
if( s874.empty() )
throw s960.s992( L"SATISFYING condition must have at least one parameter" );
for( size_t n = 0; n < s874.size(); ++n ) {
for( size_t m = 0; m < s2142.size(); ++m ) {
if( s874[n].first == s2142[m] )
s2137.push_back( s888[m] );}
while( s1822 != s1823 ) {
++s1822;}}}
vector<s482> s2016, s2017;
s2016.resize( s2137.size() );
s828 s2042;
if( sqp->s2041.s14() ) {
sqp->s2041.s15<s831*>()->s807( s2042 );
for( auto p: s2042 )
s2017.push_back( p.second->s332(0,0) );
if( s2017.size() != s888.size() )
throw s960.s992( L"in the REDUCE query the number of selected fields doesn't match "
"the number of parameters to 'using' function");}
else
s2017.resize( s888.size() );
dom->s1858();
s1768* s1842 = dom->s1830();
while( /*dom->s1820()*/ s1842 ) {
s483 s1793;
if( sqp->s1851.s14() ) {
for( size_t n = 0; n < s2137.size(); ++n )
s2016[n] = s1842->s753( s2137[n] ).s15<s481*>();
sqp->s1851.s15<Transd*>()->s593( s2016 );
s1793 = sqp->s1851->s494( 0, 0 );}
else
s1793 = s366.s15<s480*>();
if( s1793.s14() && (bool)*s1793 ) {
if( s888.empty() )
s1842->s856( *s2021 );
else {
for( size_t n = 0; n < s888.size(); ++n ) {
if( s2045[n] ) {
vector<s482> s2015( { s1842->s753( s888[n] ).s15<s481*>() } );
s2045[n]->s593( s2015 );
s2017[n] = s2045[n]->s494( 0, 0 ).s15<s270*>();}
else
s2017[n] = s1842->s753( s888[n] ).s15<s270*>();}}
if( sqp->s2041.s14() ) {
sqp->s2041.s15<Transd*>()->s593( s2017 );
sqp->s2041->s494( 0, 0 );}}
s1842 = dom->s1830();}
return s362; //s2021;
}
s483 s784::s494( s480** s686, size_t s690 ){
if( s803->verb == s737::s1761 )
return s1715( s686, s690 );
else if( s803->verb == s737::s1762 )
return s1716( s686, s690 );
else if( s803->verb == s737::s2043 )
return s1991( s686, s690 );
return NULL;}
bool
s784::s553( const wstring& s671, s368* ref, const wstring& s331, 
bool b ) const{
if( s671 == s7::s1966 ) {
ref->s1332( (s368*)&s2022 );
return true;}
return s588::s553( s671, ref, s331, b ); }
s270* s784::s595( size_t off ){
assert( off == 0 );
if( s2021 )
return s2021;
return (s270*) s2022.s500();}
s270* s784::s332( s588* s2041, s271* impl ) const{
return new s784( *this );}
s769::s769( s261* pass_, s271* s585, const wstring& s761, 
const vector<wstring>& s736, std::vector<s482>& types, const s1705& tbfr )
: s2135( NULL ){
s743 s774( pass_, s585, s761, NULL, tbfr );
s774.s497( s585, true );
vector<s482> s813 = s774.s317();
if( s813.size() > types.size() )
throw new s16( L"The number of record's fields is greater than the number of columns: " + s761 );
for( size_t n = 0; n < s736.size(); ++n ) {
s482 s804;
if( n < s813.size() ) {
if( !s813[n]->s498( types[n].s15< s480*>() ) ) {
if( tbfr.promInts && types[n]->s349() == s1140 && s813[n]->s349() == s1141 )
s813[n] = new s355( pass_, (double)*s813[n].s15<s343*>()->s354() );
else
throw new s16( L"The types of record's fields don't match to the types of columns: " + s761 );}
s804 = s813[n];}
else {
s804 = types[n].s15<s481*>()->s332(0,0);
s804->to_null();}
s755.insert( make_pair( s736[n], s804 ) );
size_t h = s804.s15<s480*>()->s319();
rechash = ( rechash << 1 ) ^ h;}
s2135 = &s755;}
s769::s769( s261* pass_, s1589& obj ){
s2135 = ( std::map<std::wstring, s482>*)&obj.s625.Table();
pobj = &obj;}
size_t s769::s319() const{
return rechash;}
s483 s769::s753( s1889& s76, bool s707 ) const{
auto it = s2135->find( s76 );
if( it == s2135->end() ) {
if( s707 )
throw new s16( L"Record field doesn't exist: " + s76, 
(uint32_t)s16::s17::s23 );
else
return s483();}
return it->second.s15<s480*>();}
void s769::s856( s743& s152 ) const{
for( auto r: *s2135 )
s152.add( r.second );}
void s769::s856( s951& s152 ) const{
for( auto r: *s2135 )
s152.add( r.second );}
void s769::s542( std::vector<std::wstring>& s152 ) const{
for( auto r: *s2135 )
s152.push_back( r.first );}
bool s769::operator==( const s769* p ) const{
return rechash == p->rechash;}
bool s769::operator<( const s769* p ) const{
return rechash < p->rechash;}
wstring s769::to_wstring( uint32_t s1552 ) const{
wstringstream ss;
s303( &ss, 0 );
return ss.str();}
void s769::s303( std::wostream* pd, int s196/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"TSDRecord : " << endl;
for( auto it = begin( *s2135 ); it != end( *s2135 ); ++it ) {
buf << s4::fill_n_ch( L' ', s196 + s416 ) << it->first << L":" << endl;
it->second->s303( pd, s196 + s416 );}}
s805::s805( vector<wstring>& s725, s815 rec ){
for( size_t n = 0; n < s725.size(); ++n ) {
s482 f = rec->s753( s725[n] ).s15<s481*>();
s804.push_back( f );}
for( size_t n = 0; n < s725.size(); ++n ) {
size_t h = s804[n].s15<s480*>()->s319();
s793 = ( s793 << 1 ) ^ h;}}
size_t s805::s319() const{
return s793;}
bool s805::operator==( const s805* p ) const{
return s793 == p->s793;}
bool s805::operator<( const s805* p ) const{
return s793 < p->s793;}
void s805::s303( std::wostream* pd, int s196/* = 0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"PrimKey : " << endl;
for( size_t n = 0; n < s804.size(); ++n ) {
s804[n]->s303( pd, s196 + s416 );}}
s1781::s1781( s1766* pdb )
: s1767( pdb ), pind(NULL)//, fi1(s1833), se1(s1833)
{}
void s1781::s1855( void* f, void* s ){
pind = (s780*)f;}
void s1781::s1858(){
if( pind )
cur1 = pind->begin();
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1781::s1820(){
if( pind )
return cur1 != pind->end();
else
return cur != se;}
s1768* s1781::s1830(){
if( s1820() ) {
s1768* s680;
if( pind ) {
s680 = cur1->second;
cur1++;}
else {
s680 = *cur;
cur++;}
return s680;}
else
throw new s16( L"TSDBase row iterator is out of range" );}
s647::s647( s261* s299, s271* s585, const s262* ast_ ) 
: s1766( s299, s585, NULL ) {
s490 = Types.TSDBase;}
s647::s647( s261* s299, s271* s585, const wstring& s77, const s262* ast_ )
: s1766( s299, s585, ast_ ){
s496 = s77;
s490 = Types.TSDBase;}
s647::s647( const s647& right, const s262* ast_ )
: s1766( right.s299, right.ns, ast_ ){
s490 = right.s490;}
s480* s647::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return new s647( s299, s585, L"" );}
void s647::s497( const s271*, bool ){
s1251();}
void s647::s347(){
s806::Cont s1268;
wstring ts = Types( s299, Types.Vector )->s350() + L"<" +
Types( s299, Types.String )->s350() + L">";
s1053 s1505 = ( (s313*)Types( s299, Types.Vector ) )->s1185( this, ts, s1704, s1268 );
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s647::s1226, s1783,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"add-file", new s334( L"add-file", &s647::s779, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"add-object", new s334( L"add-object", &s647::s2126, s1142,
{ s1112( { Types.s271 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"set-prim-key", new s334( L"set-prim-key", &s647::s2138, s1142,
{ s1112( { s1505 } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"load-table", new s334( L"load-table", &s647::s795, s1142,
{ s1112( { Types.String } ) }, 1, 1, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls"} ) ) );
s345.insert( make_pair( L"select", new s334( L"select", &s647::s745, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"query", new s334( L"query", &s647::s763, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"erase", new s334( L"erase", &s647::s330, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s647::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"build-index", new s334( L"build-index", &s647::s849, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );}
s480* s647::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s647( s299, s585, L"" );}
inline bool
s647::s498( const s480* s499 ) const{
return ( ((s647*)s499)->s349() == s349() );}
s270* s647::s332( s588* s2041, s271* impl ) const{
return new s647( *this );}
void s647::s353( s270* p ) const{
p = new s647( *this );}
size_t s647::s319() const{
return (size_t)this;}
bool s647::operator==( const s480* p ) const{
return ( this == p );}
bool s647::operator<( const s480* p ) const{
return false;}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s647*)(s481*)*s273)
inline void s647::s1226( s480** s273, size_t s495 ){
s647* ps = (s647*)DR;
s647* s680 = new s647( ps->s299, ps->ns, ps->s600() );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s647::s779( s480** s273, size_t s495 ){
wstring s193 = PARN( 2 )->to_wstring();
( (s647*)DR )->s651( s193 );}
inline void s647::s2126( s480** s273, size_t s495 ){
s1589* ob = (s1589*)PARN( 2 );
( (s647*)DR )->s376( *ob );}
inline void s647::s2138( s480** s273, size_t s495 ){
s313* pv = (s313*)PARN( 2 );
vector<s482>& s2141 = pv->s317();
( (s647*)DR )->s2129.clear();
for( size_t n = 0; n < s2141.size(); ++n )
( (s647*)DR )->s2129.push_back( s2141[n]->to_wstring() );}
inline void s647::s795( s480** s273, size_t s495 ){
s647* dr = ( (s647*)DR );
const wstring& s817 = PARN( 2 )->to_wstring();
s1705 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s495 ) {
s482 par_ = s273[n];
s469 pc = par_->s491();
if( pc == s1055 ) {
s482 par;
s486 rf;
rf = par_.s15<s368*>();
par = par_;
if( par->s349() == Types.No ) {
if( rf->Id() == s1738 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1736 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1734 ) {
if( s495 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1719 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1735 ) {
tbfr.s1682 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1827 ) {
tbfr.s1811 = true;}
else if( rf->Id() == s1737 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}}}
else
throw new s16( L"TSDBase::(load-table): unknown parameters" );
++n;}
dr->s711( s817, tbfr );}
inline void s647::s745( s480** s273, size_t s495 ){
wstring s193 = PARN( 2 )->to_wstring();
( (s647*)DR )->s652( s193 );}
inline void s647::s763( s480** s273, size_t s495 ){
wstring s193 = PARN( 2 )->to_wstring();
( (s647*)DR )->s652( s193 );}
inline void s647::s330( s480** s273, size_t s495 ){}
inline void s647::s325( s480** s273, size_t s495 ){}
inline void s647::s328( s480** s273, size_t s495 ){}
inline void s647::s849( s480** s273, size_t s495 ){
wstring s851 = PARN( 2 )->to_wstring();
((s647*)DR)->s848( s851 );}
void s647::s651( const wstring& s193 ){
vector<s9<s142>> s659;
s937 s1043( s193 );
s1043.read( s659, s7::s1096 );
for( size_t m = 0; m < s659.size(); m++ ) {
s142* obj = s659[m];
wstring s655 = s4::s52( s262::s301( *obj, s7::s462 ), 
s48 );
if( s655.empty() )
throw new s16( L"Nameless blocks are forbidden." );
vector<pair<wstring, s141>> s143;
obj->s159( s143 );
for( size_t n = 0; n < s143.size(); ++n ) {
if( s143[n].second->s163() != s133 && s143[n].second->s163() != s138 )
throw new s16( L"unrecognized format of field " + s655 +L"::"+s143[n].first );
wstring sobj = s143[n].second->s168();
wstring srel = s143[n].first;
s648.insert( make_pair( s655, make_pair( srel, sobj ) ) );
s649.insert( make_pair( srel, make_pair( s655, sobj ) ) );
s650.insert( make_pair( sobj, make_pair( s655, srel ) ) );}}}
void s647::s376( s1589& obj ){
s815 rec = new s769( s299, obj );
s727 s151 = new s805( s2129, rec );
s750.insert( make_pair( s151, rec ) );}
void s647::s652( s1889& q ){
vector<wstring> qs;
s4::s57( q, L" ", qs );
wstring verb = qs[0];
if( verb == L"select" ) {
for( auto it = s648.begin(); it != s648.end(); ++it )
wcout << it->first;}}
void s647::select( s1889& field, s1763::s1776 op, const s480* s1057,
s1772& s152 ){
auto it = s864.find( field );
if( it == s864.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1763::s1836 ) {
s152.pr = it->second.equal_range( (s480*)s1057 );}
else if( op == s1763::s1839 ) {
s152.pr.first = it->second.begin();
s152.pr.second = it->second.lower_bound( (s480*)s1057 );}
else if( op == s1763::s1840 ) {
s152.pr.first = it->second.begin();
s152.pr.second = it->second.upper_bound( (s480*)s1057 );}
else if( op == s1763::s1837 ) {
s152.pr.first = it->second.upper_bound( (s480*)s1057 );
s152.pr.second = it->second.end();}
else if( op == s1763::s1840 ) {
s152.pr.first = it->second.lower_bound( (s480*)s1057 );
s152.pr.second = it->second.end();}
else {
s152.pr.first = it->second.begin();
s152.pr.second = it->second.end();}}
s1767* s647::s1803() const{
return new s1781( (s1766*)this );}
void s647::s1854( s1767* s152 ){
s152->s1855( (void*)&s750, (void*)NULL );}
void s647::intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ){
s1771::iterator it = fi1.pr.first;
wstring attr2 = fi2.s969;
s1770 s1800;
while( it != fi1.pr.second ) {
s483 attr2v = it->second->s753( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1800 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1800 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s152.push_back( it->second );
++lb2;}}
++it;}}
void s647::intersect( const s1772& fi, s1767* s152 ){
s1771::iterator it = fi.pr.first;
s1769 s1861;
s1769& s1845 = ((s1781*)s152)->s317();
bool s1809 = s1845.empty();
while( it != fi.pr.second ) {
if( s1809 || std::binary_search( begin( s1845 ), end( s1845 ), it->second, s1787 ) )
s1861.push_back( it->second );
++it;}
s1845.swap( s1861 );}
void s647::s711( const wstring& s817, const s1705& tbfr ){
wstring s736 = tbfr.s1719;
vector<wstring> s808;
vector<wstring> s724;
vector<wstring> s798;
vector<wstring> s818;
if( s736.size() ) {
s4::s57( s736, tbfr.s1682, s808 );
s4::s57( s4::s52( s817, s48 ), tbfr.rowSep, s798 );}
else {
s736 = s817.substr( 0, s817.find( tbfr.rowSep ) );
s4::s57( s4::s52( s817.substr( s736.size() ), s48 ), tbfr.rowSep, s798 );
if( s736.back() == '\r' )
s736.pop_back();
s4::s57( s736, tbfr.s1682, s808 );}
vector<s482> s1757;
vector<s482> types;
if( !s798.empty() ) {
s743 s774( s299, ns, s798[0], NULL, tbfr );
s774.s497( ns, true );
s1757 = s774.s317();}
for( size_t n = 0; n < s808.size(); ++n ) {
vector<wstring> s1718;
s4::s57( s808[n], L":", s1718 );
s939 s1756;
if( s1718.size() == 2 )
s1756 = new s262( s1718[1] + L"()", NULL, NULL );
else if( n < s1757.size() )
s1756 = new s262( s1757[n]->s350() + L"()", NULL, NULL );
else
s1756 = new s262( Types( s299, Types.String )->s350() + L"()", NULL, NULL );
s482 ptype = s299->TR().s515( *s1756, ns, ns->s297() );
types.push_back( ptype );
if( s1718[0][0] != L'@' )
s724.push_back( s1718[0] );
else {
size_t pl = s1718[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1718[0] );
wstring s76 = s1718[0].substr( pl + 1 );
s724.push_back( s76 );
s818.push_back( s76 );}}
if( !s818.empty() ) {
s750.rehash( (size_t) ( s798.size() * 1.1 ) );
for( auto row : s798 ) {
s815 rec = new s769( s299, ns, row, s724, types, tbfr );
s727 s151 = new s805( s818, rec );
s750.insert( make_pair( s151, rec ) );}}}
void s647::s848( const wstring& s851 ){
auto it = s864.find( s851 );
if( it != end( s864 ) )
s864.erase( it );
s1771& s863 = s864.insert( make_pair( s851, s1771() ) ).first->second;
for( auto it: s750 ) {
s483 pd;
try {
pd = it.second->s753( s851 );}
catch( ... ) {}
if( pd.s14() )
s863.insert( make_pair( pd, it.second ) );}}
bool s647::s1994( s1889& s969 ) const{
assert(0);
return false;}
s1053 s647::s1999( s1889& s851 ) const{
assert( 0 );
return 0;}
void s647::s1817( std::vector<std::wstring>& s152 ) const{
assert( 0 );}
wstring s647::to_wstring( uint32_t s1552 ) const{
basic_stringstream<wchar_t> ss;
s303( &ss, 0 );
return ss.str();}
void s647::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"TSDBase : " << endl;
for( auto it = begin( s750 ); it != end( s750 ); ++it ) {
it->first->s303( pd, s196 + s416 );
it->second.s15<s769*>()->s303( pd, s196 + s416 );}}
s1769 s1831 = { new s1785( vector<s483>( {s483()} ), NULL ) };
s1769::iterator s1832 = s1831.begin();
s1785::s1785( const std::vector<s483>& v, s1786* s1792 )
: s1846( v ), s1843( s1792 ){}
s1785::~s1785(){
s1846.clear();}
const s1785::s1778& s1785::s2000() const{
return s1846;}
s483 s1785::s753( s1889& s76, bool s707 ) const{
return s1846[s1843->s1818( s76 )];}
void s1785::s856( s743& s152 ) const{
for( auto r : s1846 )
s152.add( r );}
void s1785::s856( s951& s152 ) const{
for( auto r : s1846 )
s152.add( r );}
void s1785::s542( std::vector<std::wstring>& s152 ) const{
assert( 0 );}
size_t s1785::s319() const{
return rechash;}
s1784::s1784( const s1784& r )
: s1767( r.pdb ){}
s1784::s1784( s1766* pdb )
: s1767( pdb ){}
s1784::~s1784(){}
void s1784::s1855( void* f, void* s ){
fi = *( s1769::iterator* )f;
se = *( s1769::iterator* )s;}
void s1784::s1858(){
if( *fi != *s1832 )
cur = fi;
else {
fi = cur = ptr->begin();
se = ptr->end();}}
bool s1784::s1820(){
return (cur != se);}
s1768* s1784::s1830(){
if( s1820() ) {
s1768* s680 = *cur;
cur++;
return s680;}
else
throw new s16( L"Table row iterator is out of range" );}
void s1784::s1816( std::vector<std::wstring>& s152 ){
((s1786*)pdb)->s1817( s152 );}
s1786::s1786( s261* s299, s271* s585, const s262* ast_ )
: s1766( s299, s585, ast_ ){
s490 = Types.Table;
s2026 = 0;}
s1786::s1786( s261* s299, s271* s585, s1889& s77, const s262* ast_ )
: s1766( s299, s585, ast_ ){
s496 = s77;
s490 = Types.Table;
s2026 = 0;}
s1786::s1786( const s1786& right, const s262* ast_ )
: s1766( right.s299, right.ns, ast_ ){
s490 = right.s490;
s2026 = 0;}
s1786::~s1786(){
release();}
s480* 
s1786::s351( const s262& s694, s271* s585, s1889& s331 ) const{
return new s1786( s299, s585, &s694 );}
void s1786::s497( const s271*, bool ){
s1251();}
void s1786::s347(){
s345.insert( make_pair( s7::s1345, new s334( s7::s1345, &s1786::s1226, s1782,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"load-table", new s334( L"load-table", &s1786::s795, s1142,
{ s1112( { Types.String } ) }, 1, 2, false, { L":stringsQuoted", L":integers", L"colNames:",
L"fieldSep:", L"rowSep:", L":emptyEls", L":firstRowColNames"} ) ) );
s345.insert( make_pair( L"select", new s334( L"select", &s1786::s745, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"query", new s334( L"query", &s1786::s763, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.insert( make_pair( L"erase", new s334( L"erase", &s1786::s330, s1142,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"size", new s334( L"size", &s1786::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"get-row", new s334( L"get-row", &s1786::s2002, 0,
{ s1112( { s1500::s1537 } ) }, 0, 0 ) ) );
s345.insert( make_pair( L"num-cols", new s334( L"num-cols", &s1786::s2010, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"num-rows", new s334( L"num-rows", &s1786::s2011, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( make_pair( L"build-index", new s334( L"build-index", &s1786::s849, s1142,
{ s1112( { Types.String } ) }, 1, 1 ) ) );
s345.equal_range( L"get-row" ).first->second->s1250( true );}
s1053 s1786::s1178( const wstring& s1540, const vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"get-row" )
s680 = s1703;
else
return s333::s1178( s1540, l );
return s680;}
s480* s1786::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s1786( s299, s585, L"" );}
inline bool
s1786::s498( const s480* s499 ) const{
return ( ((s1786*)s499)->s349() == s349() );}
s270* s1786::s332( s588* s2041, s271* impl ) const{
return new s1786( *this );}
void s1786::s353( s270* p ) const{
p = new s1786( *this );}
size_t s1786::s319() const{
return (size_t)this;}
bool s1786::operator==( const s480* p ) const{
return ( this == p );}
bool s1786::operator<( const s480* p ) const{
return false;}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
#undef s691
#define s691 ((s1786*)(s481*)*s273)
inline void s1786::s1226( s480** s273, size_t s495 ){
s1786* ps = (s1786*)DR;
s1786* s680 = new s1786( ps->s299, ps->ns, ps->s600() );
s680->s497( ps->ns, true );
*s273 = (s480*)s680;}
inline void s1786::s795( s480** s273, size_t s495 ){
s1786* dr = ( (s1786*)DR );
const wstring& s817 = ((s356*)PARN( 2 ))->s317();
s1705 tbfr( L",", L"\n", L"", L".", false, false, false );
size_t n = 3;
while( n < s495 ) {
s482 par = s273[n];
s469 pc = par->s491();
if( pc == s1055 ) {
s486 rf = par.s15<s368*>();
if( par->s349() == Types.No ) {
if( rf->Id() == s1738 ) {
tbfr.stringsQuoted = true;}
else if( rf->Id() == s1736 ) {
tbfr.promInts = true;}
else if( rf->Id() == s1734 ) {
if( s495 < n + 2 )
throw new s16( L"TSDBase::(load-table): the 'colNames:' value is missing" );
tbfr.s1719 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1735 ) {
tbfr.s1682 = PARN( ++n )->to_wstring();}
else if( rf->Id() == s1827 ) {
tbfr.s1811 = true;}
else if( rf->Id() == s1737 ) {
tbfr.rowSep = PARN( ++n )->to_wstring();}
else if( rf->Id() == s2003 ) {
tbfr.s1998 = true;}}}
else
throw new s16( L"Table::(load-table): unknown parameters" );
++n;}
dr->s711( s817, tbfr );}
inline void s1786::s745( s480** s273, size_t s495 ){
wstring s193 = PARN( 2 )->to_wstring();
( (s1786*)DR )->s652( s193 );}
inline void s1786::s763( s480** s273, size_t s495 ){
wstring s193 = PARN( 2 )->to_wstring();
( (s1786*)DR )->s652( s193 );}
inline void s1786::s330( s480** s273, size_t s495 ){}
inline void s1786::s2002( s480** s273, size_t s495 ){
s1786* pt = (s1786*)DR;
int n = (int)*PARN( 2 );
const s1785::s1778& row = pt->s2044[n].s15<s1785*>()->s2000();
vector<s270*> v;
for( auto f : row )
v.push_back( f->s332(0,0) );
*s273 = new s951( pt->s299, pt->ns, v, NULL );
( *s273 )->s497( pt->ns );}
inline void s1786::s325( s480** s273, size_t s495 ){}
inline void s1786::s2010( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s1786*)DR )->s799.size();}
inline void s1786::s2011( s480** s273, size_t s495 ){
*( (s343*)*s273 )->s354() = (int)( (s1786*)DR )->rows.size();}
inline void s1786::s849( s480** s273, size_t s495 ){
wstring s851 = PARN( 2 )->to_wstring();
((s1786*)DR)->s848( s851 );}
void s1786::select( const std::wstring& field, s1763::s1776 op, const s480* s1057,
s1772& s152 ){
auto it = s864.find( field );
if( it == s864.end() )
throw new s16( L"Index doesn't exist: " + field,
(uint32_t)s16::s17::s23 );
if( op == s1763::s1836 ) {
s152.pr = it->second.equal_range( (s480*)s1057 );}
else if( op == s1763::s1839 ) {
s152.pr.first = it->second.begin();
s152.pr.second = it->second.lower_bound( (s480*)s1057 );}
else if( op == s1763::s1840 ) {
s152.pr.first = it->second.begin();
s152.pr.second = it->second.upper_bound( (s480*)s1057 );}
else if( op == s1763::s1837 ) {
s152.pr.first = it->second.upper_bound( (s480*)s1057 );
s152.pr.second = it->second.end();}
else if( op == s1763::s1840 ) {
s152.pr.first = it->second.lower_bound( (s480*)s1057 );
s152.pr.second = it->second.end();}
else {
assert( 0 );
s152.pr.first = it->second.begin();
s152.pr.second = it->second.end();}
s152.s969 = field;
s152.dist = std::distance( s152.pr.first, s152.pr.second );}
void s1786::intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ){
s1771::iterator it = fi1.pr.first;
wstring attr2 = fi2.s969;
s1770 s1800;
while( it != fi1.pr.second ) {
s483 attr2v = it->second->s753( attr2, false );
if( attr2v.s14() ) {
auto lb2 = std::lower_bound( fi2.pr.first, fi2.pr.second, attr2v, s1800 );
auto ub2 = std::upper_bound( fi2.pr.first, fi2.pr.second, attr2v, s1800 );
while( lb2 != ub2 ) {
if( it->second == lb2->second )
s152.push_back( it->second );
++lb2;}}
++it;}}
void s1786::intersect( const s1772& fi, s1767* s152 ){
s1771::iterator it = fi.pr.first;
s1769 s1861;
s1769& s1845 = ((s1784*)s152)->s317();
bool s1809 = s1845.empty();
while( it != fi.pr.second ) {
if( s1809 || std::binary_search( begin( s1845 ), end( s1845 ), it->second, s1787 ) )
s1861.push_back( it->second );
++it;}
s1845.swap( s1861 );}
void s1786::s1854( s1767* s152 ){
s1769::iterator f = begin( rows );
s1769::iterator s = end( rows );
s152->s1855( (void*)&f, (void*)&s );}
size_t s1985( const std::wstring& s817, const s1705& tbfr ){
size_t s680 = 0, st = 0, en = 0, n;
while( en != string::npos ) {
en = s817.find( tbfr.rowSep, st );
n = s4::count( s817, tbfr.s1682, st, en, true );
if( s680 < n ) s680 = n;
st = en + 1;}
return s680;}
void s1786::s711( s1889& s817, const s1705& tbfr ){
wstring s736 = tbfr.s1719;
vector<wstring> s808;
vector<wstring> s818;
size_t pl = 0;
if( s736.size() ) {
s4::s57( s736, tbfr.s1682, s808 );}
else if( tbfr.s1998 ){
pl = s817.find( tbfr.rowSep );
s736 = s817.substr( 0, pl );
if( s736.back() == '\r' )
s736.pop_back();
s4::s57( s736, tbfr.s1682, s808 );
++pl;}
else {
size_t s2006 = s1985( s817, tbfr );
for( size_t n = 0; n < s2006; ++n )
s808.push_back( std::to_wstring( n ) );}
vector<s483> types;
vector<s482> s1757;
if( 0 /*|| !s798.empty()*/ ) {
++pl;
wstring first = s817.substr( pl, s817.find( tbfr.rowSep, pl ) - pl );
s743 s774( s299, ns, first, NULL, tbfr );
s774.s497( ns, true );
s1757 = s774.s317();}
for( size_t n = 0; n < s808.size(); ++n ) {
vector<wstring> s1718;
s4::s57( s808[n], L":", s1718 );
s939 s1756;
s483 ptype;
if( s1718.size() == 2 )
s1756 = new s262( s1718[1] + L"()", NULL, NULL );
else
s1756 = new s262( Types( s299, Types.String )->s350() + L"()", NULL, NULL );
ptype = s299->TR().s515( *s1756, ns, ns->s297() );
types.push_back( ptype );
if( s1718[0][0] != L'@' )
s799.push_back( s1718[0] );
else {
size_t pl = s1718[0].find( L"_" );
if( pl == string::npos )
throw new s16( L"Invalid column name: " + s1718[0] );
wstring s76 = s1718[0].substr( pl + 1 );
s799.push_back( s76 );}
s1819[s799.back()] = s799.size() - 1;}
s806::Cont s1268;
wstring ts = Types( s299, Types.Tuple )->s350() + L"<"; 
for( size_t n = 0; n < types.size(); ++n ) {
ts += types[n]->s350();
if( n < types.size() - 1 )
ts += L" ";}
ts += L">";
s2026 = ( (s951*)Types( s299, Types.Tuple ) )->s1185( ts, s1268 );
using namespace chrono;
size_t s1804 = pl, /*s69,*/ s1849, s1805, s1812;
vector<s483> s1814( types.size() );
s939 s207 = new s262( L"", L"" );
rows.clear();
s2044.clear();
while( s1804 != string::npos ) {
s1849 = s1804;
s4::s993( s817, s1849, tbfr.rowSep );
wstring s1807 = s817.substr( s1804, s1849 - s1804 );
s1812 = s1805 = 0;
for( size_t n = 0; n < types.size(); ++n ) {
s1812 = s1805;
s4::s993( s1807, s1812, tbfr.s1682 );
if( types[n].s14() ) {
s207->s293( L"" );
s207->s1753( s1807.substr( s1805, s1812 - s1805 ) );
if( types[n]->s349() == Types.String && ( s207->s290().front() != L'"' ||
s207->s290().back() != L'"' ) ) {
wstring dqu = L"\"\"";
s207->s1753( dqu.insert( 1, s4::s1813(  s4::s52( s207->s290(), s4::s48 ) , L'"' )));}
s1814[n] = types[n]->s351( *s207, ns, ns->s297() );}
else {
s1814[n] = s362.s15<s480*>();}
s1805 = s1812 + 1;
if( s1812 == string::npos )
break;}
s1804 = s1849 + 1;
s1768* s1794 = new s1785( s1814, this );
rows.push_back( s1794 );
if( s1849 == string::npos || s1804 == s817.size() )
break;}
s2044.assign( rows.begin(), rows.end() );}
void s1786::s848( s1889& s851 ){
auto it = s864.find( s851 );
if( it != end( s864 ) )
s864.erase( it );
s1771& s863 = s864.insert( make_pair( s851, s1771() ) ).first->second;
for( auto it: rows ) {
s483 pd = it->s753( s851 );
if( pd.s14() )
s863.insert( make_pair( pd, it ) );}}
bool s1786::s1994( s1889& s969 ) const{
if( s1819.find( s969 ) != end( s1819 ) )
return true;
return false;}
s1053 s1786::s1999( s1889& s851 ) const{
if( !s2026 )
throw new s16( L"table is empty" );
const s806& s984 = s299->TR().s1005( s2026 );
s1053 s2027 = s984.s349( (1 + s1818( s851 )) * 2 );
return s2027;}
void s1786::release(){
s1766::release();
rows.clear();}
s1767* s1786::s1803() const{
return new s1784( (s1766*)this );}
size_t s1786::s1818( s1889& s1801 ) const{
auto s680 = s1819.find( s1801 );
if( s680 == s1819.end() )
throw new s16( L"table field does not exist: " + s1801 );
return s680->second;}
wstring s1786::to_wstring( uint32_t s1552 ) const{
basic_stringstream<wchar_t> ss;
s303( &ss, 0 );
return ss.str();}
void s1786::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Table : " << endl;
for( auto it = begin( rows ); it != end( rows ); ++it ) {}}
s2060::s2060( s483 d )
: rec( d ){}
s2060::~s2060(){}
s483 s2060::s753( s1889& s76, bool s707 ) const{
return rec;}
void s2060::s856( s743& s152 ) const{
s152.add( rec.s15<s270*>() );}
void s2060::s856( s951& s152 ) const{
s152.add( rec.s15<s270*>() );}
void s2060::s542( std::vector<std::wstring>& s152 ) const{
assert( 0 );}
size_t s2060::s319() const{
return rec->s319();}
s2059::s2059( const s2059& r )
: s1767( r.pdb ){}
s2059::s2059( s1766* pdb )
: s1767( pdb ){}
s2059::~s2059(){}
void s2059::s1855( void* f, void* s ){
s2067 = (s323*)f;
started = false;}
void s2059::s1858(){
started = true;
s2065 = s2067->s311( NULL );}
bool s2059::s1820(){
return !s2065->s1963();}
s1768* s2059::s1830(){
if( s1820() ) {
s1768* s680 = NULL;
if( 0 && started ) {
s680 = new s2060( (s480*)s2065->s954() );
started = false;}
else {
s480* s2066 = (s480*)s2065->s312();
if( s2066 )
s680 = new s2060( s2066 );}
return s680;}
else
return NULL;}
void s2059::s1816( std::vector<std::wstring>& s152 ){
((s2046*)pdb)->s1817( s152 );}
s2046::s2046( s261* s299, s271* s585, s323* pv_, const s262* ast_ )
: s1766( s299, s585, ast_ ), s2064( L"col1"), pv( pv_ ){
s490 = pv->s349();
s2026 = pv->ValType();
s2052 = false;}
s2046::s2046( const s2046& r )
: s1766( r ), pv( r.pv ){
s490 = r.s349();
s2026 = r.s2026;
s2052 = false;
s2064 = r.s2064;}
s2046::~s2046(){
release();}
s480* 
s2046::s351( const s262& s694, s271* s585, s1889& s331 ) const{
assert(0);
return 0;}
void s2046::s497( const s271*, bool ){
s1251();}
s480* s2046::s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const{
return new s2046( s299, s585 );}
void s2046::s347(){
assert(0);}
s270* s2046::s332( s588* s2041, s271* impl ) const{
return new s2046( *this );}
void s2046::s353( s270* p ) const{
p = new s2046( *this );}
size_t s2046::s319() const{
return (size_t)this;}
bool s2046::operator==( const s480* p ) const{
return ( this == p );}
bool s2046::operator<( const s480* p ) const{
return false;}
void s2046::select( const std::wstring& field, s1763::s1776 op, const s480* s1057,
s1772& s152 ){
assert( 0 );
s152.s969 = field;
s152.dist = 0;}
void s2046::intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ){
assert( 0 );}
void s2046::intersect( const s1772& fi, s1767* s152 ){
assert( 0 );}
void s2046::s1854( s1767* s152 ){
s152->s1855( (void*)pv, NULL );}
void s2046::s848( s1889& s851 ){
assert( 0 );}
bool s2046::s1994( s1889& s969 ) const{
if( s2064 == s969 )
return true;
return false;}
s1053 s2046::s1999( s1889& s851 ) const{
if( !s2026 )
throw new s16( L"table is empty" );
return s2026;
const s806& s984 = s299->TR().s1005( s2026 );
s1053 s2027 = s984.s349( (1 + s1818( s851 )) * 2 );
return s2027;}
void s2046::release(){
s1766::release();}
s1767* s2046::s1803() const{
return new s2059( (s1766*)this );}
size_t s2046::s1818( s1889& s1801 ) const{
if( s2064 != s1801 )
throw new s16( L"dataset doesn't contain the attribute: '" + s1801 + L"'" );
return 0;}
wstring s2046::to_wstring( uint32_t s1552 ) const{
basic_stringstream<wchar_t> ss;
s303( &ss, 0 );
return ss.str();}
void s2046::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << s4::fill_n_ch( L' ', s196 ) << L"Dataset : " << endl;
pv->s303( pd, s196 );}
vector<wstring> s1360 /*= { L"", s1415, s242, s1416, 
s257, s255, 
s893, s2062, s259, s229, s765, 
s814, s251, s243, s845,
s260, s752, s250, s258, 
s256, s811, s1306, s254, 
s232 }*/;
vector<int> BIFuncs1v = {	0, 
0, 0, s1419, s1420, 0, 
0, s1422, s2194, 0, s1423, s1424, 0, 
0,	s1426, s1610, 0, 0, 0,
s1429, s2215, 0, 0, 0, s1431, 
s1871, s1612, 0, 0, s1432, 
s1550, s1433, s1434, s1435,	0, 
0, s1437, s1438
};
std::map<std::wstring, int> s1359;
s1971::s1971(){
reset();}
vector<wstring> s1971::s2033;
void s1971::reset(){
memset( s2025, 0, s1968 * sizeof( s1983 ) );
if( s2033.empty() )
s2033 = { s7::s1978, s7::s1981, s7::s1980,
s7::s1979 };}
s1983 s1971::s1987( s1889& s2023 ){
auto it = std::find( begin(s2033), end(s2033), s2023 );
size_t n = std::distance( begin(s2033), it );
if( n == string::npos )
throw new s16( L"unrecognized restriction switch: " + s2023 );
return (s1983)n;}
void s1971::s2040( const s142& s132 ){
for( size_t n = 0; n < s1968; ++n )
if( s2025[n] )
throw new s16( L"Assembly security restrictions have already been set" );
vector<pair<wstring, s141>> s143;
s132.s159( s143 );
for( size_t n = 0; n < s143.size(); ++n ) {
if( s143[n].first == s7::s1973 )
s2025[s2034] = s1987( s143[n].second->s168() );
else if( s143[n].first == s7::s1974 )
s2025[s2035] = s1987( s143[n].second->s168() );
else if( s143[n].first == s7::s1975 )
s2025[s2036] = s1987( s143[n].second->s168() );
else if( s143[n].first == s7::s1976 )
s2025[s2037] = s1987( s143[n].second->s168() );
else if( s143[n].first == s7::s1972 ) {
s2025[s2034] = s1987( s143[n].second->s168() );
s2025[s2035] = s1987( s143[n].second->s168() );}
else if( s143[n].first == s7::s1977 ) {
for( size_t n = 1; n < s1968; ++n )
s2025[n] = s1987( s143[n].second->s168() );}}}
void s1971::s1997( const std::vector<s1982>* s2018, s1983 sw ) const{
for( size_t n = 0; n < s2018->size(); ++n ) {
s1982 si = (*s2018)[n];
if( s2025[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );}}
bool s1971::s1996( s1982 si, s1983 sw ) const{
if( s2025[si] == s2032 )
return true;
if( s2025[si] >= sw )
throw new s16( L"not compatible with current security restrictions" );
return false;}
s261::s261()
: s271( this, 0, s470, NULL, this, s2182 ), s694( s226, L"", L"global" ),
s199( L"" ), s202( this ), s1308( false ){}
s261::~s261(){
for( auto it = s2254.begin(); it != s2254.end(); ++it ) {
it->second->clear();
delete it->second;}
s2254.clear();}
void s261::reset(){
s625.reset();
s202.s783();
s198.clear();
s694.reset();
s1308 = false;
s2024.reset();}
void s261::s1884( bool soft /*=false*/ )
{
s333::s777( this, soft );
s202.s289();
s205[s7::s431] = s364.s15<s480*>();
s205[s7::s430] = s365.s15<s480*>();
s844( s7::s433, s366.s15<s480*>() );
s844( s7::s434, s367.s15<s480*>() );
s844( s7::s825, s362.s15<s480*>() );
s1393 = new s1392( this, this );
s1391 = new s1390( this, this );
s844( s7::s1379, s1391.s15<s480*>() );
s844( s7::s1380, s1393.s15<s480*>() );
#ifdef WIN32
wstring os = L"Windows";
#else 
#if defined(__LINUX__) || defined(_linux_)
wstring os = L"Linux";
#else
wstring os = L"Unknown";
#endif
#endif
s356* s1461 = new s356( this, os, this );
s844( s7::s1361, s1461 );
if( s1359.empty() ) {
s1360 = { L"", 
s1415, s242, s1416, s257, s1601, 
s255, s893, s2193, s2062, s259, s229, 
s765,
s814, s251, s1602, s243,s1928,
s1603, 
s845,s2213,s260, s1605, s1606, s752, 
s1870, s1604, s1929, s1927, s250, 
s1549,s258, s256, s811, s1607, 
s1306, s254, s232 };
for( size_t n = 1; n < s1360.size(); ++n )
s1359[s1360[n]] = (int)n;}}
static s6::s1680 s1755( L".", L",", true, true, true );
void s261::s201( s1889& s654, s715& s152 ) {
vector<s9<s142>> s659;
s940 s1043 = new s937( s654, true, s1755 );
s1043->read( s659, s7::s415 );
for( size_t n = 0; n < s659.size(); n++ ) {
wstring s655 = s262::s301( *s659[n], s7::s462 );
if( s655 == s7::s450 ) {
if( ( *s659[n] ).s155( s7::s464 ) ) {
const vector<s141>& s161 = ( *s659[n] ).s157( s7::s464 )->s166();
for( size_t n = 0; n < s161.size(); n++ )
s152.s660.push_back( s161[n]->s168() );}
if( ( *s659[n] ).s155( s7::s463 ) )
s152.entry = ( *s659[n] ).s157( s7::s463 )->s850();
if( ( *s659[n] ).s155( s7::s1967 ) ) {
const s142& s132 = (*s659[n]).s157( s7::s1967 )->s165();
s2024.s2040( s132 );}}}
if( s152.s660.empty() )
s152.s660.push_back( s654 );}
wstring s710( s1889& s746, s1889& s749 ){
if( s3::s717( s749 ) )
return s749;
if( !s3::s717( s746 ) )
throw new s16( L"The root path is not absolute: " + s746 );
if( s749.empty() )
return s746;
wstring path = s749;
wstring root = s746;
s4::s61( path );
s4::s61( root );
while( path.find( L"./" ) == 0 )
path = path.substr( 2 );
while( path.find( L"../" ) == 0 ) {
if( root.size() > 1 ) {
size_t pl = root.rfind( L'/', root.size()-2 ) + 1;
if( pl == string::npos )
throw new s16( L"The relative path '" + s749 + L"' is incompatible with the root '" + s746 + L"'." );
root = root.substr( 0, pl );
path = path.size() > 3 ? path.substr( 3 ) : L"";}
else
throw new s16( L"The relative path '" + s749 + L"' is incompatible with the root '" + s746 + L"'." );}
return root + path;}
void s261::s212( s1889& s193, const s142& obj ){
const vector<s141>& s722 = ( obj ).s157( s7::s467 )->s166();
const vector<s141>& packs = ( obj ).s157( s7::s732 )->s166();
vector<wstring> s41;
wstring s734 = s193.substr( 0, s193.rfind( L"/" ) + 1 );
for( size_t n = 0; n < s722.size(); n++ )
s41.push_back( s710( s734, s722[n]->s168() ) );
for( size_t n = 0; n < packs.size(); n++ ) {
wstring req = packs[n]->s168();
if( req.rfind( s7::s454 ) == req.size() - s7::s454.size() ) {
if( std::find( s198.begin(), s198.end(), req ) == s198.end() )
s198.push_back( s710( s734, req ) );}
else {
vector<wstring> matches;
for( size_t n = 0; n < s41.size(); n++ ) {
wstring match;
wstring _dir = s41[n];
s4::s61( _dir );
if( s3::s31( _dir, req + s7::s454, match ) )
matches.push_back( match );}
if( matches.empty() ) {
throw new s16( L"The required library '" + req + L"' is not found." );}
else if( matches.size() > 1 ) {
wstring s731;
s4::s288( matches, L",\n", s731 );
throw new s16( L"The required library's name '" + req + L"' is ambiguous: \n" + s731 );}
if( std::find( s198.begin(), s198.end(), matches[0] ) == s198.end() )
s198.push_back( matches[0] );}}}
void s261::s2157( const s142& obj ){
vector<pair<wstring, s141>> s143;
obj.s159( s143 );
for( size_t n = 0; n < s143.size(); ++n ) {
if( s143[n].first == s7::s462 )
continue;
s939 past = new s262( s143[n].first, *s143[n].second, NULL );
s480* dv = (s480*)s270::s501( *past, s299, (s271*)this, L"::" );
dv->s1251();}}
void s670( s261* s299, s262& s694, s479& s656,
s620& cl, s619& cnl, s621& al ){
s262::s274& s695 = s694.s292();
s262::s274::iterator it = s695.begin();
s533 am = s507;
for( ; it != s695.end(); ++it ) {
s469 pc = s476;
if( it->first.find( L" " ) != string::npos ) {
vector<wstring> s683;
s4::s57( it->first, L" ", s683 );
if( s683.size() > 3 )
throw new s16( L"malformed block name: " + it->first );
wstring s655 = s683[1];
size_t idx = s683.size() - 2;
if( s683[idx] == s7::s448 )
pc = s475;
else if( s683[idx] == s7::s449 )
pc = s476;
else if( s683[idx] == s7::s2145 )
pc = s2149;
else
throw new s16( L"unknown object type: " + s683[0] );
if( s683.size() == 3 ) {
if( s683[0] == s7::s445 )
am = s506;
else if( s683[0] == s7::s447 )
am = s508;
else if( s683[0] != s7::s446 )
throw new s16( L"invalid access mode name: " + it->first );
s655 = s683[2];}
it->second->s293( s655 );}
s271* ob = new s271( *it->second, s299, pc, s299, am, cl, cnl, al, s2182 );
s656.s538( ob->s298(), ob );}}
void s261::s208( s1889& s658, bool s1886 ){
s715 s643;
s262* s207 = new s262();
wstring s188 = s4::s739( s658 );
if( !s3::s717( s188 )) {
wstring s1881;
if( s1886 ) {
if( s1882.empty() )
throw new s16( L"can't find the file: " + s658 );
s1881 = s1882;}
else
s1881 = s760;
s4::s61( s1881 );
wstring file = s188.substr( s188.rfind( L"/" ) + 1 );
s188 = s710( s1881, s188.substr(0, s188.rfind( L"/" ) + 1 )) + file;
}
int isf = s3::s34( s188 );
if( isf == 2 ) {
s4::s61( s188 );
s188 += s7::s457;
if( s760.empty() )
s760 = s658;}
else if( isf == 1 ) {
if( s760.empty() )
s760 = s188.substr( 0, s188.find_last_of( L"\\/" ) );
}
else
throw new s16( L"cannot find file or directory: " + s658,
(uint32_t)s16::s17::s23 );
s4::s61( s760 );
s201( s188, s643 );
size_t s791 = s198.size();
vector<s9<s142>> s659;
for( size_t n = 0; n < s643.s660.size(); n++ ) {
s659.clear();
wstring s661 = s643.s660[n];
if( s661[0] != L'/' && s661[1] != L':' )
s661 = s760 + s661;
s198.push_back( s661 );}
for( size_t n = s791; n < s198.size(); ++n ) {
s659.clear();
s940 s1043 = new s937( s198[n], true, s1755 );
s1043->read( s659, s7::s415 );
for( size_t m = 0; m < s659.size(); m++ ) {
if( s262::s301( *s659[m], s7::s462 ) == s7::s453 )
s212( s198[n], *s659[m] );
else if( s262::s301( *s659[m], s7::s462 ) == s7::s2151 )
s2157( *s659[m] );
else if( s262::s294( *s659[m], s7::s451 ) == s7::s451 ) {
s659[m]->s158( s7::s1114, new s6::s140( L"\"" 
+ s198[n] + 
L"\"" 
), s142::s144::s146 );
s207->s288( *s659[m], m );}}}
s206( *s207 );
if( s1006.s927() )
throw s928( s928::s17::s991 );
s262::s274& s695 = s207->s292();
for( auto it : s695 ) 
s694.s285( it.second );
if( s199.empty() )
s199 = s643.entry;}
void s261::s206( s262& s207 ){
s479 s656;
s621 m1;
s619 s662;
s620 s663;
vector<wstring> s664;
s670( this, s207, s656, s663, s662, m1 );
typedef std::pair<std::wstring, size_t> s2174;
std::sort( s662.begin(), s662.end(), []( const s2174& l, const s2174& r ) { return l.second < r.second; } );
for( size_t n = 0; n < s662.size(); ++n )
s664.push_back( s662[n].first );
for( size_t n = 0; n < s664.size(); ++n )
if( s202.s155( s664[n] ) )
throw new s16( L"class name already exists: " + s664[n] );
for( size_t n = 0; n < s664.size(); ++n )
s202.s217( s663[s664[n]], s663[s664[n]]->s350() );
s625.s288( s656 );
for( size_t n = 0; n < s664.size(); ++n ) {
s484 ob = (s271*)s202.get( s664[n], false );
if( ob )
ob->s153( *m1[s664[n]] );}
for( auto it = m1.begin(); it != m1.end(); ++it ) {
s271* ob = (s271*)s656.get( it->first, false );
if( ob && ob->s491() == s476 ) {
try {
ob->s153( *it->second );}
catch( s16* e ) {
e->s30( L"while constructing module: " + it->first );
throw e;}}}
s656.s497( this, NULL, false );}
void s261::s210( s142& obj ){
s262 s207;
s207.s288( obj, 0 );
s206( s207 );}
void s261::s1637( s1889& s666 ){
s480* pd = s625.get( s666 );
if( pd->s491() == s476 )
((s271*)pd)->s1636();}
s480* s261::run( const vector<wstring>& s686 ){
if( s199.empty() )
s199 = s7::s456 + L"::" + s7::s455;
if( !s686.empty() ) {
wstring  s667, s666;
s665( s199, s666, s667 );
s271* mod = (s271*)s625.get( s666 );
s806::Cont s1268;
wstring ts = Types( this, Types.Vector )->s350() + L"<" + Types( this, Types.String )->s350() + L">";
s1053 pt = ((s313*)Types( this, Types.Vector ))->s1185( this, ts, s1704, s1268 );
s313* s904 = (s313*) s299->TR().s999( pt )->s352( this, vector<s481*>( {} ) );
for( size_t n = 0; n < s686.size(); ++n ) {
s904->add( new s356( this, s686[n], this ) );}
s904->s497( this, true );
mod->s844( s7::s1559, s904 );
mod->s844( s7::s822, new s343( this, (int)s686.size() ) );}
vector<wstring> l;
return callFunc( s199, l );}
s480* s261::callFunc( s1889& s, vector<wstring>& l ){
wstring  s667, s666;
s665( s, s666, s667 );
s271* mod = (s271*)s625.get( s666 );
s485 s668 = (s588*)mod->s638( s667, L"::" );
vector<s482> s273;
for( size_t n = 0; n < l.size(); n++ ) {
s939 ast_ = new s262( l[n], NULL, NULL );
s487 cs = s588::s1109( *ast_, this, mod, mod->s297(), false );
s273.push_back( cs );}
s668->s593( s273 );
s481* pr = s668->s493();
try {
s1308 = false;
if( !pr )
s668->s497( mod, false ); 
else
s668->s594( mod );}
catch( s16* e ) {
throw e->s30( L"\nwhile linking '" + s668->s298() + L"' function " );}
s1308 = true;
mod->s1636();
s480* s680 = s668->s494(0,0);
if( s680->s615() == s7::s437 )
throw new s16( ( (s358*)s680 )->Msg() );
s1308 = false;
return s680;}
s485 s261::getProc( const std::wstring& s ){
wstring  s667, s666;
s665( s, s666, s667 );
s271* mod = (s271*)s625.get( s666 );
s485 s668 = (s588*)mod->s638( s667, L"::" );
s483 pr = s668->s493();
if( !pr )
s668->s497( mod, true );
return s668;}
/*
void s261::s200( const std::wstring& s658 ){
wstring s188 = s658;
wstring s657;
int isf = s3::s34( s658 );
if( isf == 2 ) {
s4::s61( s188 );
s188 += s7::s457;
s657 = s658;}
else if( isf == 1 )
s657 = s188.substr( 0, s188.find_last_of( L"\\/" ) );
else
throw new s16( L"cannot find file or directory: " + s658, 
(uint32_t)s16::s17::s23 );
s4::s61( s657 );
vector<s9<s142>> s659;
s940 s1043 = new s937( s188 );
s1043->read( s659, s7::s415 );
s715 s643;
for( size_t n = 0; n < s659.size(); n++ ) {
wstring s655 = s262::s301( *s659[n], s7::s462 );
if( s655 == s7::s450 ) {
s201( *s659[n], s643 );
break;}}
s199 = s643.entry;
if( s643.s660.empty() )
s643.s660.push_back( s188 );
for( size_t n = 0; n < s643.s660.size(); n++ ) {
s659.clear();
wstring s661 = s643.s660[n];
if( s661[0] != L'/' && s661[1] != L':' )
s661 = s657 + s661;
s940 s1043 = new s937( s661 );
s1043->read( s659, s7::s415 );
for( size_t m = 0; m < s659.size(); m++ )
if( s262::s294( *s659[m], s7::s451 ) == s7::s451 )
s694.s288( *s659[m] );}}
void s261::s201( const s6::s142& obj, s715& s152 ){
const vector<s141>& s161 = obj.s157( s7::s464 )->s166();
for( size_t n = 0; n < s161.size(); n++ )
s152.s660.push_back( s161[n]->s168() );
if( obj.s155( s7::s463 ) )
s152.entry = obj.s157( s7::s463 )->s168();}
*/
void s261::s1997( const std::vector<s1982>* s2018, s1983 sw ) const{
s2024.s1997( s2018, sw );}
bool s261::s1996( s1982 si, s1983 sw ) const{
return s2024.s1996( si, sw );}
s1053 s261::s217( s480* p, s1889& s344 ){
return s202.s217( p, s344 );}
bool s261::s553( s1889& sym_, s368* ref, s1889& s331, bool fr ) const{
if( !s271::s553( sym_, ref, s331, fr ) ) {
if( sym_ == s7::s1559 ) {
ref->s376( s637( s7::s825 ), s362 );
ref->s379( (s480*)this );
return true;}
return false;}
return true;}
bool s261::s220( s368& rf ) const{
rf.s379( NULL );
s204::const_iterator it = s205.find( rf.s614() );
if( it != end( s205 ) ) {
rf.s379( it->second );
return true;}
return false;}
void s261::s218( s1889& s76, s1889& s331,
vector<wstring>& s152 ){
size_t pl = s76.rfind( L"::" );
s271* mod = NULL;
bool bCl = false;
if( s76.find( L"()" ) == s76.size() - 2 )
bCl = true;
if( pl != string::npos ) {
wstring s669 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
if( bCl ) {
sym = sym.substr( 0, sym.size() - 2 );}
mod = (s271*)s625.get( s669 );
if( !mod->s639( sym, s331 ) )
throw new s16( L"Symbol '" + s76 + L"' cannot be imported by '" +
s331 + L"'");
s152.push_back( sym );}
else {
if( bCl ) {
wstring sym = s76.substr( 0, s76.size() - 2 );
s202.get( sym );
s152.push_back( sym );}
else {
mod = (s271*) s625.get( s76 );
mod->s636( s331, s152 );}}}
s588* s261::s213( int s1445, 
s558* cs, s271* s585, s588* s214 ){
s588* s680 = NULL;
const s262* s694 = cs->s600();
std::vector<s270*>& s698 = cs->s599();
bool s2159 = cs->s2165();
if( s1445 == s1424 )
s680 = new s605( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1438 )
s680 = new s602( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1612 )
s680 = new s1594( this, s585, s214, s698, s694 );
else if( s1445 == s1418 )
s680 = new s604( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1419 )
s680 = new s1395( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s2063 )
s680 = new s2061( this, s585, s214, s698, s694 );
else if( s1445 == s1931 )
s680 = new s1923( this, s585, s214, s698, s694 );
else if( s1445 == s2194 )
s680 = new s2192( this, s585, s214, s698, s694 );
else if( s1445 == s1437 )
s680 = new s304( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1428 )
s680 = new s603( this, s585, s214, s698, s694 );
else if( s1445 == s1932 || s1445 == s1930)
s680 = new s1924( this, s585, s214, s698, s694 );
else if( s1445 == s1432 || s1445 == s1550)
s680 = new s606( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1421 )
s680 = new s607( this, s585, s214, s698, s694 );
else if( s1445 == s1426 )
s680 = new s831( this, s585, s214, s698, s694, 0, true, s2159 );
else if( s1445 == s1429 || s1445 == s2215 )
s680 = new s832( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1434 )
s680 = new s609( this, s585, s214, s698, s694 );
else if( s1445 == s1433 )
s680 = new s608( this, s585, s214, s698, s694 );
else if( s1445 == s1420 )
s680 = new s610( this, s585, s214, s698, s694 );
else if( s1445 == s1423 )
s680 = new s611( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1430 )
s680 = new s612( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1427 )
s680 = new s790( this, s585, s214, s698, s694 );
else if( s1445 == s1425 )
s680 = new s768( this, s585, s214, s698, s694 );
else if( s1445 == s1436 )
s680 = new s1296( this, s585, s214, s698, s694 );
else if( s1445 == s1615 )
s680 = new s1597( this, s585, s214, s698, s694 );
else if( s1445 == s1435 )
s680 = new s784( this, s585, s214, s698, s694 );
else if( s1445 == s1611 )
s680 = new s1592( this, s585, s214, s698, s694 );
else if( s1445 == s1613 )
s680 = new s1595( this, s585, s214, s698, s694 );
else if( s1445 == s1610 )
s680 = new s1591( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1431 ) {
s680 = new s810( this, s585, s214, s698, s694 );}
else if( s1445 == s1614 )
s680 = new s1596( this, s585, s214, s698, s694 );
else if( s1445 == s1422 )
s680 = new s889( this, s585, s214, s698, s694 );
else if( s1445 == s1609 )
s680 = new s1590( this, s585, s214, s698, s694, s2159 );
else if( s1445 == s1871 )
s680 = new s1869( this, s585, s214, s698, s694 );
return s680;}
s270*
s261::s221( s1889& s76, s1889& s496, bool s517 /*= true*/ )
{
size_t pl = s76.rfind( L"::" );
s482 s680;
if( pl == string::npos ) {
s680 = (s270*)s202.get( s76, s517 );
if( !s680 ) {
s271* exp = (s271*)s202.get( s7::s452, false );
if( exp )
s680 = exp->s638( s76, s496, s517 );}
return s680;}
wstring s669 = s76.substr( 0, pl );
wstring sym = s76.substr( pl + 2 );
return ((s271*)s202.get( s669 ))->s638( sym, s496 );	}
void* s261::s222( s1889& s277 ){
s333* s680;
s271* exp = (s271*) s625.get( s7::s452, false );
if( exp )
s680 = (s333*)exp->s638( s277, L"", true );
else
throw new s16( L"no such export variable: " + s277 );
void * pv = s680->addr();
return pv;}
void s261::s1340( s1889& s666 ){
s202.s1862( s666 );
s625.s539( s666 );
if( s202.s155( s666) )
s202.s1651( s666 );}
void s261::s1650( s1889& s1620 ){
vector<wstring> s1630;
for( auto it = s625.Table().begin(); it != s625.Table().end(); ++it ) {
s270* p = it->second.s15<s270*>();
if( p->s491() == s476 || p->s491() == s475 || p->s491() == s2149) {
wstring s188 = ( (s271*)p )->s638( s7::s1114, 
L":::" )->to_wstring();
if( s188 == s1620 )
s1630.push_back( it->first );}}
for( auto mod : s1630 )
s1340( mod );
for( size_t n = 0; n < s198.size(); ++n ) {
if( s198[n] == s1620 ) {
s198.erase( s198.begin() + n );
break;}}}
void s261::s2242( const s480* s151, s2238* s2253 ){
assert( s2254.find( s151 ) == s2254.end() );
s2254.insert( make_pair( s151, s2253 ) );}
s2238* s261::s2248( const s480* s151 ){
if( s2254.empty() )
return NULL;
auto it = s2254.find( s151 );
if( it == s2254.end() )
return NULL;
s2238* s680 = it->second;
s2254.erase( it );
return s680;}
void s261::s2247( const s480* old, const s480* nw ){
auto it = s2254.find( old );
if( it == s2254.end() )
return;
s2238* s273 = new s2238();
s273->assign( begin( *it->second ), end( *it->second ) );
s2254.insert( make_pair( nw, s273 ) );}
void s261::s303( std::wostream* pd, int s196 /*=0*/ ) const
{
std::wostream& buf = *pd;
buf << endl << s4::fill_n_ch( L' ', s196 ) << s277 << L" : " << L"Assembly" << endl;
s202.s303( pd, s196 + s416 );
s625.s303( pd, s196 + s416 );}
map<int, s1::s9<s261>> handles;
HPROG createAssembly(){
static int s679 = 0;
s1::s9<s261> p = new s261();
handles[++s679] = p;
p->s1884( false );
return s679;}
void deleteAssembly( int n ){
auto it = handles.find( n );
if( it == end( handles ) )
throw new s2::s16( L"no assembly with such handle" );
handles.erase( it );}
void loadProgram( HPROG handle, const wstring& s188 ){
s261* p = handles[handle];
p->s1875( s3::s1868() );
p->s208( s188, true );}
TDType* getProc( HPROG handle, const std::wstring& s598 ){
s261* p = handles[handle];
return (TDType*)p->getProc( s598 );}
void s210( HPROG handle, s6::s142& obj ){
s261* p = handles[handle];
p->s210( obj );}
TDType* run( HPROG handle, const vector<wstring>& s686 ){
return handles[handle]->run( s686 );}
void* callFunc( HPROG handle, const std::wstring& s77, vector<wstring>& l ){
s261* p = handles[handle];
return p->callFunc( s77, l );}
void evaluateExpression( const std::wstring& s77 ){}
void* s222( HPROG handle, const std::wstring& s277 ){
s261* p = handles[handle];
return p->s222( s277 );}
void* execute( TDType* p ){
return p->s494(0, 0).s15<s333*>()->addr();}
void importSymbol( HPROG handle, const std::wstring& s1102, const std::wstring& symName,
const std::wstring& s331 ){
s261* p = handles[handle];
s271* ob = (s271*)p->s638( s1102, s331 );
ob->s552( symName, s331 );}
void importFile( HPROG handle, const std::wstring& s1102, const std::wstring& s44,
const std::wstring& s331 ){
vector<s1::s9<s6::s142>> s659;
s6::s937 s1043( s44 );
s1043.read( s659, s7::s415 );
s261* p = handles[handle];
p->s208( s44 );
s271* ob = (s271*)p->s638( s1102, s331 );
for( size_t n = 0; n < s659.size(); n++ ) {
wstring s655 = s262::s301( *s659[n], s7::s462 );
ob->s552( s655, s331 );}}
HPROG initShell( const std::wstring& s1102, const std::wstring& modText ){
s1::s9<s6::s142> ob = new s6::s142(NULL);
size_t pos = 0;
s6::s1680 s1755( L".", L",", true, true, true );
s6::s937 s1043( L"", true, s1755 );
s1043.s169( modText, pos, ob );
ob->s158( s7::s462, new s6::s140( s1102 ) );
HPROG prog = createAssembly();
s210( prog, *ob );
return prog;}
} // namespace transd
