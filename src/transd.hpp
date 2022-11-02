
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
*    transd.hpp
*    ----------
*
*    The minimized distributed header file for C++ embeddable
*    library of Tourbillon virtual compiler.
*
*    Transd Project Website: https://github.com/transd-lang
*/
#include <vector>
#include <map>
#include <list>
#include <codecvt>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cwctype>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>
#if _WIN32 || _WIN64
#if defined(_WIN64)
#define OS_64
#else
#define OS_32
#endif
#endif
#if __GNUC__
#if __x86_64__ || __ppc64__
#define OS_64
#else
#define OS_32
#endif
#endif
#ifndef WIN32
#define _W64
#define __int64 int64_t
#endif
namespace s1 {
#ifdef OS_64
typedef std::int64_t				INT_PTR, *PINT_PTR;
#ifndef _WIN64
typedef std::uint64_t				UINT_PTR, *PUINT_PTR;
typedef long								LONG_PTR, *PLONG_PTR;
typedef unsigned long				ULONG_PTR, *PULONG_PTR;
typedef long long						LONGLONG;
typedef unsigned long long	ULONGLONG;
typedef ULONG_PTR		    		DWORD_PTR, *PDWORD_PTR;
#endif
#else
typedef _W64 int						INT_PTR, *PINT_PTR;
typedef _W64 unsigned int		UINT_PTR, *PUINT_PTR;
typedef _W64 long						LONG_PTR, *PLONG_PTR;
typedef _W64 unsigned long	ULONG_PTR, *PULONG_PTR;
typedef __int64							LONGLONG;
typedef ULONG_PTR		    		DWORD_PTR, *PDWORD_PTR;
#endif
template<class T, class U>
class Conversion{
typedef char Small;
class Big { char dummy[2]; };
static Small Test( U );
static Big Test( ... );
static T MakeT();
public:
enum{
exists =
sizeof( Test( MakeT() ) ) == sizeof( Small )
};
enum { sameType = false };
};
template <class T>
class Conversion<T, T>{
public:
enum { exists = 1, sameType = 1 };
};
#define SUPERSUBCLASS(T, U) \
(Conversion<const U*, const T*>::exists && \
!Conversion<const T*, const void*>::sameType)
template <class F, class T>
T* checked_cast( F* p ){
if( SUPERSUBCLASS( T, F ) )
return p;
return nullptr;}
class s1272{
int refs;
public:
s1272(){
refs=0;}
~s1272(){}
void reset(){
refs = 0;}
int s11(){
refs++;
return refs;}
int s12(){
refs--;
return refs;}
int s1273(){
return refs;}
};
#ifdef s1279
#define s1280(x) x;
#else
#define s1280(x)
#endif
template<bool>
struct s1274{
void s1275(){}
void s1276(){}
};
template<>
struct s1274<true>{
#ifdef s1279
static int s162;
void s1275() { s162++; }
void s1276() { s162--; }
#endif
};
class s10{
int refs;
public:
s10() : refs(0){}
virtual ~s10(){}
void s11(){
refs++;}
void s12(){
if( --refs == 0 )
deallocate();}
int s1273(){
return refs;}
virtual void deallocate(){
delete this;}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template<class C, bool s1307=false>
class s1278
: public s1274<s1307>{
C* p;
s1272*	s1277;
public:
s1278(C *_p)
:p(_p){
if ( p ) {
s1277 = new s1272;
s1277->s11();
s1280( this->s1275() )}}
s1278( const s1278& ptr ){
if ( ptr.p ) {
p = ptr.p;
s1277 = ptr.s1277;
s1277->s11();}
else {
p = nullptr;
s1277 = nullptr;}}
s1278()
:p(nullptr){
s1277 = nullptr;}
template<class D> 
s1278( s1278<D> &pn ){
p = nullptr;
s1277 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1277 = pn.s1294();
s1277->s11();}}}
~s1278(){
if(	p && !s1277->s12()	) {
delete p;
delete s1277;
s1280( this->s1276() )}}
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1278& operator=( s1278<C> &s1335 ){
if ( p  && !s1277->s12() ) {
delete p;
delete s1277;
p = nullptr;
s1277 = nullptr;
s1280( this->s1276() )}
p = s1335.p;
if ( s1335.p ) {
s1277 = s1335.s1277;
s1277->s11();}
return *this;}
s1278& operator=( const s1278<C> &s1335 ){ return operator=((s1278<C>&) s1335); }
s1278& operator=( C* ptr ){
if ( p  && !s1277->s12() ) {
delete p;
delete s1277;
p = nullptr;
s1277 = nullptr;
s1280( this->s1276() )}
p = ptr;
if ( ptr ) {
s1277 = new s1272;
s1277->s11();
s1280( this->s1275() )}
return *this;}
template<class Base>
operator Base*(){
return checked_cast<C, Base>( p );}
template<class D>
s1278& operator=( s1278<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );}
template<class ToType>
ToType s15(){
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast(){
return dynamic_cast<ToType>( p );}
bool operator ==(const s1278<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1278<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1272* s1294() { return s1277; }
int s1273() { return s1277->s1273(); }
void s1329() { s1277->s11(); }
void s1328() {
if ( p  && !s1277->s12() ) {
delete p;
delete s1277;
p = nullptr;
s1277 = nullptr;
s1280( this->s1276() )}}
};
template <class C>
class s9{
C* p;
public:
s9( C* p_ ) : p(p_){
if(p)
p->s11();}
s9(C& p_) {
p = &p_;
if(p)
p->s11();}
s9(){
p = NULL;}
s9(const s9<C> &pn){
p = pn.p;
if(p)
pn.p->s11();}
template<class D> 
s9( s9<D> &pn ){
p = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p)
p->s11();}}
~s9(){
detach();}
operator C*() { return p; }
C& operator*() { return *p; }
const C& operator*()const { return *p; }
C* operator->() { return p; }
const C* operator->()const { return p; }
s9& operator=( s9<C> &p_ ) { return operator=(( C* ) p_); }
s9& operator=( const s9<C> &p_ ) { return operator=( (s9<C>& ) p_ ); }
s9& operator=( C* p_ ){
if(p){
p->s12();}
p = p_;
if(p)
p->s11();
return *this;}
template<class B>
operator B*(){
return checked_cast<C, B>( p );}
template<class D>
s9& operator=( const s9<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);}
template<class ToType>
ToType s15() const{
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast() const{
return dynamic_cast<ToType>( p );}
bool s13()const { return p == nullptr; }
bool s14()const { return p != nullptr; }
void detach(){
if(p){
p->s12();
p = nullptr;}}
bool operator ==( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p == (INT_PTR)p ); }
bool operator !=( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p != (INT_PTR)p ); }
bool operator <( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p < (INT_PTR)p ); }
bool operator ==( const C& s346 )const { return ( *p == s346 ); }
bool operator !=( const C& s346 )const { return ( *p != s346 ); }
bool operator <( const C& s346 )const { return ( *p < s346 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1111();
extern std::vector<std::wstring> s988;
class s16
: public std::exception{
static uint32_t s27;
protected:
std::list<std::wstring> s26;
uint32_t id;
s16() :id( 0 ){};
public:
enum class s17 : uint32_t{
s18 = 0,
s19,
s20,
s21,
s22,
s23,
s24,
s868,
s25
};
s16( const std::wstring& s, uint32_t n = (uint32_t)s17::s19 )
: id( n ){
s26.push_back( s );}
s16( uint32_t n )
: id( n ){
s26.push_back( s988[n] );}
s16( const s16& right )
: id( right.id ){
s26.assign( right.s26.begin(), right.s26.end() );}
static void s29(){
s27 = (uint32_t)s17::s25 + 1;}
static uint32_t s28(){
return s27++;}
virtual std::wstring Msg( size_t s196 = 0 ) const{
std::wstring s680;
std::list<std::wstring>::const_reverse_iterator it = s26.crbegin();
std::wstring s1070( s196, L' ' );
while( it != s26.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s26.crend() )
s680 += s1070;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s680 += ( i++ ? L"" : s1070 ) + s + L"\n";}
return s680;}
const char* what() const noexcept{
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
std::string* s = new std::string( conv.to_bytes( s26.back() ) );
return s->c_str();}
uint32_t which() const { return id; }
s16* s30( const std::wstring& s ){
s26.push_back( s );
return this;}
s16* specify( const std::wstring& s ){
s26.push_front( L"\n  : " + s );
return this;}
};
} // namespace s2
namespace s3 {
bool s31( const std::wstring& _dir, const std::wstring& s521, std::wstring& s152 );
void s32( const std::wstring& _dir, const std::wstring& s521, std::vector<std::wstring>& s40,
std::vector<std::wstring>& s41 );
time_t s33( const std::wstring& f );
uint8_t s34( const std::wstring& f );
bool s717( const std::wstring& f );
bool s35( const std::wstring& s209 );
bool s36( const std::wstring& s209 );
std::wstring s37();
std::wstring s38();
std::wstring s39();
std::wstring s1868();
} // namespace s3
namespace s4 {
extern std::wstring s87;
extern std::wstring s48;
extern std::string s49;
extern std::wstring s50;
extern std::wstring digits;
enum s17 { s23 };
std::wstring s51( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s52( const std::wstring& s, const std::wstring& c );
bool s53( const std::wstring& s, const std::wstring& ss );
void s54( const std::wstring& s, size_t s65, wchar_t left, wchar_t right, 
size_t& start, size_t& end, bool s879 = false );
void s55( const std::wstring& s, size_t s65, wchar_t c, size_t& start, 
size_t& end );
void s993( const std::wstring& s, size_t& s65, const std::wstring& s1082 );
void s1316( const std::wstring& s, size_t& s65, const std::wstring& s1082 );
size_t count( const std::wstring& s77, const std::wstring& s1082, size_t start, size_t end,
bool s879 = false );
int s56( const std::wstring& s77, wchar_t s72, size_t& pos );
void s57( const std::wstring& s, const std::wstring& s72, 
std::vector<std::wstring>& s152, bool clr = true, bool s879 = false, size_t s68 = 0 );
void s288( const std::vector<std::wstring>& v, const std::wstring& s72, std::wstring& s152 );
std::wstring s71( const std::wstring& s77, size_t& pos );
void s58( const std::wstring& s77, const std::wstring& s72, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s59( const std::wstring& s77, const std::wstring& s72,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s60( const std::wstring& s77 );
void s61( std::wstring& s46 );
std::wstring s739( std::wstring path );
bool s62( const wchar_t *str, long *s346, wchar_t **end = NULL );
bool s1532( const wchar_t *str, long long *s346, wchar_t **end = NULL );
bool s1533( const wchar_t *str, unsigned long long *s346, wchar_t **end = NULL );
bool s63( const wchar_t *str, double *s346, wchar_t **end = NULL );
void s870( const std::wstring& s77, std::vector<std::wstring>& s152 );
std::wstring s1813( const std::wstring& s77, wchar_t c );
std::wstring s1242( const std::wstring& s, const std::wstring& chars );
std::string s51( const std::string& l, const std::string& s, const std::string& r );
std::string s52( const std::string& s, const std::string& c );
void s54( const std::string& s, size_t s65, char left, char right, 
size_t& start, size_t& end);
int s56( const std::string& s77, char s72, size_t& pos );
void s57( const std::string& s, const std::string& s72, std::vector<std::string>& s152 );
void s59( const std::string& s77, std::vector<std::pair<std::string, std::string>>& v );
std::string s60( const std::string& s77 );
struct fill_n_ch {
size_t len;
wchar_t ch;
typedef std::basic_ostream<wchar_t, std::char_traits<wchar_t> > wostream;
fill_n_ch( wchar_t c, size_t l ): len(l), ch(c) {}
friend wostream& operator<< ( wostream& os, fill_n_ch fb ){
for ( size_t i = 0; i < fb.len; i++ )
os << fb.ch;
return os;}
};
#define FILL(x) fill_n_ch( L' ', x )
template <typename UINT> 
constexpr UINT rol(UINT s346, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s346 << n) | (s346 >> (sizeof(UINT)*8-n));}
void s64( const std::wstring& s78 );
void s81( std::wstring& s77, std::vector<std::wstring>& s1094, std::map<size_t, size_t>& s1029 );
template<class T>
std::wstring s1551( T value ) {
struct Numpunct : public std::numpunct<wchar_t> {
protected:
virtual wchar_t do_thousands_sep() const { return L','; }
virtual std::string do_grouping() const { return "\03"; }
};
std::wstringstream ss;
ss.imbue( { std::locale(), new Numpunct } );
ss << std::setprecision( 2 ) << std::fixed << value;
return ss.str();}
std::wstring s2169( void* );
} // namespace s4
namespace s5 {
extern std::locale locloc;
extern std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> conv;}
#define U8(x) s5::conv.to_bytes( x )
#define U16(x) s5::conv.from_bytes( x )
#ifdef __LINUX__
#define KCHAR char
#define TOFS(x) s5::conv.to_bytes(x)
#define FROMTERM(x) s5::conv.from_bytes(x)
#define s1548(x) s5::conv.to_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#define s1548(x) x
#endif
namespace consutils {
void s1107();
class s17{
static uint32_t s88;
public:
static void s29();
static uint32_t s89() { return s88; }
};
void s90( const std::wstring& header,
const std::vector<std::wstring>& s91 = { } );
void s95();
void s129( int s73 = 0 );
void s96( bool b = true );
bool s97( const std::wstring& s92 );
int s98( const std::wstring& s92, const std::vector<std::wstring>& s93 );
std::wstring s99( const std::wstring& s92, bool s94 = false );
std::wstring s100( const std::wstring& s92, bool s94 = false );
std::wstring getStringValHist( const std::wstring& s92,
const std::vector<std::wstring>& s101 );
int s102( const std::wstring& s92 );
size_t s103( const std::wstring& s92 );
void s104( int& w, int& h );
void s105( const std::vector<std::wstring>& v, std::vector<std::wstring>& s152,
size_t w, size_t h );
int s106( const std::vector<std::wstring>& v );
#ifdef __LINUX__
char _getch();
#endif
#define s107 372
#define s108 380
#define s109 375
#define s110 377
#define s111 27
#define s112 13
#define s115 224
#define s113 8
#define s114 383
#define s1545 371
#define s1544 379
} // namespace consutils
namespace s6{
enum s130{ s131, s132, s133, s138, 
s134, s135, s139, s136, s137 };
class s140;
class s142;
typedef s1::s9<s140> s141;
struct s1680{
bool s150;
std::wstring s1681;
std::wstring s1682;
bool s1685;
bool s1684;
bool s1686;
bool s1729;
bool s1717;
s1680( const std::wstring& dd=L".", const std::wstring& fs=L",", bool ab=false, bool rb=false,
bool sb=false )
: s150( true ), s1681(dd), s1682(fs), s1685(ab), s1684(rb),
s1686(sb), s1729( true ), s1717( false ) { }
};
extern s1680 s1742;
extern thread_local std::list<bool> s1754;
void s1683( const std::wstring& dd, const std::wstring& fs, bool ab, bool rb, bool sb );
void s1683( const s1680& cnf );
class s937
: public s1::s10{
std::wstring s193;
std::wstring s1104;
std::vector<std::wstring> s1105;
std::map<size_t, size_t> s1106;
size_t s1051;
public:
s1680 s1745;
s937( const std::wstring& file, bool s193 = true, const s1680& s1744=s1742 );
const std::wstring& Path() const { return s193;  }
void read( std::vector<s1::s9<s142>>& s152, 
const std::wstring& s189 = std::wstring(L"") );
void s169( const std::wstring& s77, size_t& pos, s1::s9<s142> s152 );
bool s997( std::wstring& s, size_t s68, size_t s678, size_t& line ) const;
size_t s941() const { return s1051; }
};
typedef s1::s9<s937> s940;
class s142
: public s1::s10{
std::multimap<std::wstring, s141> s143;
s940 src;
public:
enum s144 { s145, s146, s147 };
enum s17 { s18, s148 };
const static s140 s149; // similar to string::npos
s142( const s937* pf ):src( (s937*)pf){}
void s153( const std::wstring& s77, const s1680& s1744 );
void s154( std::wostream* pd, bool s150=false ) const;
bool s155( const std::wstring& s151 ) const;
void s156( const std::wstring& s151, std::vector<s141>& s152 ) const;
const s141 s157( const std::wstring& s151 ) const;
void s158( const std::wstring& s76, s141 s346, s144 ap=s145 );
void s1618( const std::wstring& s76 );
void s159( std::vector<std::pair<std::wstring, s141>>& s152 ) const;
bool operator==( const s142& r )  const;
void s160( std::wostream* pd, int s196 ) const;
};
bool operator==( const std::vector<s1::s9<s140>>& l,
const std::vector<s1::s9<s140>>& r );
class s140
: public s1::s10{
s130 s197;
s142 obj;
std::wstring str;
std::vector<s1::s9<s140>> s161;
double s162;
bool b;
std::pair<size_t, size_t> s1074;
s940 s1073;
public:
s140():s197(s131),obj(NULL){}
s140( const std::wstring& s ):s197(s133),obj(NULL),str(s){}
s140( double d, s130 v = s135 );
s140( const std::vector<s141>& a ): s197(s134),obj(NULL),s161(a){}
s140( const s937* pf, const std::wstring& s77, size_t& pos, const s1680& s1744 );
s130 s163() const { return s197; }
bool s164() const { return s197 == s131; }
const s142& s165() const;
const std::vector<s141>& s166() const;
double s167() const;
int s56() const;
bool s721() const;
const std::wstring& s168() const;
const std::wstring& s858() const;
std::wstring s850() const;
bool s1001( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s937* s998() const { return s1073.s15<s937*>(); }
bool operator==( const s140& r ) const{
return s197 == r.s197 && obj == r.obj && str == r.str && s161 == r.s161 && b == r.b && s162 == r.s162;}
bool is( const s140& r ) const{
return this == &r;}
void s160( std::wostream* pd, int s196 ) const;
void s154( std::wostream* pd, bool s150=false ) const;
};
class s1694{
s1680 conf;
public:
s1694() { }
s1694( const s1680& _cnf )
: conf( _cnf ) {}
s130 s1538( const std::wstring& s77, size_t& pos, double& s152 );
void s177( const s937* pf, const std::wstring& s77, size_t& pos, 
std::vector<s1::s9<s140>>& s152,
bool s150 = false, const std::wstring& s72 = L",");
};
void s170( const std::wstring& s193, 
const std::vector<s1::s9<s142>>& s194 );
void s177( const s937* pf, const std::wstring& s77, size_t& pos,
std::vector<s1::s9<s140>>& s152, const s1680& s1744 );
void s177( const s937* pf, const std::wstring& s77,
std::vector<s1::s9<s140>>& s152, const s1680& s1744 );
} // namespace s6
typedef const std::wstring s1889;
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s921 extern const uint32_t
#define s1675    1
#define s1676 2
#define s1677 3
#define s1678 4
#define s1679 5
namespace transd {
typedef uint32_t s1053;
typedef uint32_t traitnum_t;
typedef unsigned char tdbyte_t;
typedef std::basic_string<tdbyte_t> s1311;
namespace s7 {
s921 s1541;
s921 s1383;
s921 s1384;
s921 s1385;
s921 s1382;
s921 s1381;
s921 s1386;
s921 s1387;
DEFCONST s417;
DEFCONST s418;
DEFCONST s419;
DEFCONST s420;
DEFCONST s421;
DEFCONST s422;
DEFCONST s423;
DEFCONST s424;
DEFCONST s425;
DEFCONST s426;
DEFCONST s1616;
DEFCONST s427;
DEFCONST s428;
DEFCONST s429;
DEFCONST s826;
DEFCONST s430;
DEFCONST s431;
DEFCONST s432;
DEFCONST s758;
DEFCONST s742;
DEFCONST s788;
DEFCONST s433;
DEFCONST s434;
DEFCONST s825;
DEFCONST s933;
DEFCONST s1130;
DEFCONST s1345;
DEFCONST s1379;
DEFCONST s1380;
DEFCONST s1588;
DEFCONST s2123;
DEFCONSTI s859;
DEFCONSTI s2218;
DEFCONSTI s2264;
DEFCONSTI s435;
DEFCONSTI s436;
DEFCONSTI s437;
DEFCONSTI s438;
DEFCONSTI s439;
DEFCONSTI s860;
DEFCONSTI s861;
DEFCONSTI s1732;
DEFCONSTI s1189;
DEFCONST s2299;
DEFCONST s1401;
DEFCONST s1512;
DEFCONST s1399;
DEFCONST s1398;
DEFCONST s1400;
DEFCONST s1397;
DEFCONST s1402;
DEFCONST s1396;
DEFCONST s440;
DEFCONST s441;
DEFCONST s442;
DEFCONST s443;
DEFCONST s444;
DEFCONST s445;
DEFCONST s446;
DEFCONST s447;
DEFCONST s448;
DEFCONST s449;
DEFCONST s2145;
DEFCONST s450;
DEFCONST s451;
DEFCONST s452;
DEFCONST s453;
DEFCONST s2151;
DEFCONST s454;
DEFCONST s456;
DEFCONST s455;
DEFCONST s457;
DEFCONST s458;
DEFCONST s459;
DEFCONST s2471;
DEFCONST s1362;
DEFCONST s1966;
DEFCONST s762;
DEFCONST s796;
DEFCONST s1559;
DEFCONST s822;
DEFCONST s1114;
DEFCONST s1361;
DEFCONST s460;
DEFCONST s461;
DEFCONST s462;
DEFCONST s463;
DEFCONST s464;
DEFCONST s465;
DEFCONST s466;
DEFCONST s732;
DEFCONST s467;
DEFCONST s929;
DEFCONST s1967;
DEFCONST s2144;
DEFCONST s1973;
DEFCONST s1974;
DEFCONST s1975;
DEFCONST s1976;
DEFCONST s1972;
DEFCONST s1977;
DEFCONST s1978;
DEFCONST s1981;
DEFCONST s1980;
DEFCONST s1979;
DEFCONST s908;
DEFCONST s907;
DEFCONST s909;
#define s416 3
#define s1108 L','
DEFCONST s415;
DEFCONST s1096;
#define s1546 1
#define s1547	2
s921 s1289;
s921 s917;
s921 s916;
s921 s1288;
s921 s1119;
s921 s911;
s921 s1097;
s921 s912;
s921 s1098;
s921 s1099;
s921 s1100;
s921 s913;
s921 s914;
s921 s915;
s921 s1116;
s921 s1117;
s921 s1354;
s921 s1355;
s921 s1356;
s921 s1584;
s921 s1118;
s921 s1285;
s921 s1287;
s921 s1286;
s921 s1652;
s921 s1653;
s921 s1366;
s921 s2275;
s921 s1654;
s921 s1364;
s921 s1365;
s921 s1655;
s921 s1510;
s921 s1511;
s921 s1542;
s921 s1672;
s921 s1586;
s921 s1888;
s921 CLObjectVal_ctor1;
s921 s1585;
s921 s1673;
s921 s1687;
s921 s1876;
s921 s1921;
s921 s1920;
s921 s2143;
s921 s2274;
s921 CLTDFilter_ctor1;
s921 s2190;
s921 s2200;
s921 s2201;
s921 s2199;
s921 s2234;
s921 s2233;
extern std::set<std::wstring> s1113;
} // namespace s7
enum s223 { s224, s225, s226, s227 };
extern std::wstring s228[];
extern const std::wstring s248, s1415, s242, s1416,	s257,
s244, s245, s1601, s235, s234, 
s236,	s893, s255, 
s2193, s2062, s259, s238, s240,
s229, s814,
s251, s237, s239, s1927, s765, s1602, s1549, 
s246, s233, s241, s243, s1928, 
s1870, s1603, s1604, s845, s260,
s230, s1605, s1606, s752, s231,
s1929, s250, s256, s811,
s254, s232,
s2213,
s744, 
s249,   s252,			s253,
s258,
s846,  s1306, s1607, 
s1305;
#define s2085		1
#define s2084		2
#define s2086		3
#define s2173  4
#define s2278    5
#define s2298   6
class s261;
class s262;
class s269;
class s270;
class s271;
typedef s269* ( *s272 )( const std::wstring& s277, const std::vector<s270*>& s273 );
typedef s1::s9<s262> s939;
extern const s6::s140 s264;
class s262
: public s1::s10{
public:
typedef std::multimap<std::wstring, s939> s274;
typedef std::map<size_t, s6::s140> s263;
private:
static std::map<std::wstring, s272> s275;
std::wstring s276;
std::wstring s1659;
s223 s278;
std::wstring s279;
s274 s280;
std::wstring src;
s6::s141 s1045;
s263 s265;
s1053 s1339{};
s262* s2091;
s262* s2096;
void s281( s1889& s77 );
void s282( const s6::s142& s132 );
void s283( s1889& s77 );
void s284( s1889& s77 );
void s285( s1889& s337, const s6::s140& obj );
void s995( s1889& s );
static std::wstring s286( s1889& s77, size_t &pos );
public:
enum s17 { s18, s148 };
s262(){ }
s262( s223 at, s1889& qpre, s1889& s76 )
: s276( qpre ), s1659( s76 ), s278( at ), s2091( NULL ), s2096( NULL ){ }
s262( s1889& s76, s1889& s346 )
: s1659( s76 ), s278( s224 ), s279( s346 ), s2091( NULL ), s2096( NULL ){ }
s262( s1889& s337, const s6::s140* s1045, s262* s2092 );
s262( s1889& s76, const s6::s140& s295, s262* s589 );
s262( const s6::s142& s132 );
~s262();
s223 s296() const { return s278; }
void s1856( s223 t ) { s278 = t; }
std::wstring s297() const;
s1889& s298() const { return s1659; }
s1889& Src() const { return src; }
const s6::s140* Nqj() const { return s1045.s15<s6::s140*>(); }
s262* s2082() { return s2091; }
s262* s2083() { return s2096; }
const s6::s140& s267( size_t s2090 ) const;
const s6::s140& s2100( size_t s2090 ) const;
void s268( size_t s2090, const s6::s140& s266 );
void s2107( const s262& s694 );
s1053 s1298() const { return s1339; }
void s1333( s1053 t) { s1339 = t; }
void reset();
static void s287( s1889& s77, size_t& pos, std::vector<std::wstring>& s152 );
void s288( s6::s142& s132, size_t s2176 );
void s285( s262* node );
void s289( s261* s299, size_t s300 = 0 );
s1889& s290() const { return s279; }
const s262* s291( s1889& s277 ) const;
bool s155( s1889& s277 ) const;
s274& s292() { return s280; }
const s274& s292() const { return s280; }
void s293( s1889& s ) { s1659 = s; }
void s1753( s1889& s ) { s279 = s; }
static std::wstring s294( const s6::s142& obj,
s1889& dfault = std::wstring( L"" ) );
static std::wstring s301( const s6::s142& obj,
s1889& s302,	s1889& dfault = std::wstring( L"" ) );
void s2267( const std::pair<std::wstring, std::wstring>& pr );
void s303( std::wostream* pd, int s196 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s936{ s1035, s1034, s1036, s1037, s1033 };
class Msg{
std::wstring func;
std::wstring file;
s936 type;
std::wstring s78;
public:	
Msg( const std::wstring& s, s936 t = s1033 )
: type( t ), s78( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s936 t = s1033 )
: func( f ), file( fi ), /*line( n ),*/ type( t ), s78( s ) {}
s936 s349() const { return type; }
const std::wstring& Text() const { return s78; }
};}
namespace transd {
class s1095{
std::vector<s8::Msg> s26;
size_t s989;
public:
s1095() : s989(0){}
void s963( const std::wstring& s78 );
void s963( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
void s965( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
size_t s927() const { return s989; }
};
extern s1095 s1006;
extern std::vector<std::wstring> s1077;
extern std::vector<std::wstring> s986;
class TDException;
class TDException
: public s2::s16{
public:
enum class Stage : uint32_t{
s1023 = 0,
s1016,
s1021,
s1020,
s1015,
s1017,
s1018,
s1019,
s1022
};
private:
Stage stage;
uint32_t category;
std::wstring s1079;
s939 s694;
public:
TDException( uint32_t cat, uint32_t id, const s262* s694 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s262* s694, const s16& e );
TDException( uint32_t cat, uint32_t id, const s262* s694, s1889& s78, Stage stg = Stage::s1023 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s196 = 0 ) const override;
std::wstring s2152( size_t idx ) const;
uint32_t Category() const { return category;  }
void s1068( Stage st ) { stage = st; }
void s2287( s262* p ) { s694 = p; }
TDException* s992( const std::wstring& s = std::wstring( L"" ) );
static std::wstring s1896( const s262& s694 );
};
class s920
: public s2::s16{
public:
enum class s17 : uint32_t{
s975 = ((uint32_t)s16::s17::s25) + 1,
s1059,
s1042,
s966,
s976,
s1008,
s1011,
s25
};
s920( const std::wstring& s )
: s16( s, (uint32_t)s17::s975){}
s920( s16& e, const s262& s694, s17 code );
};
class s928
: public s2::s16{
public:
enum class s17 : uint32_t{
s1041 = ( (uint32_t)s16::s17::s25 ) + 1,
s991,
s25
};
s928( s17 code );
s928( const std::wstring& s, s17 code )
: s16( s, (uint32_t)code ) {}
};
#define s925		1
#define s924		2
#define s926						3
#define s922					4
#define s923				5
#define s1122		6
#define s1121		7
#define s1367		8
#define s1543	9
#define s1656			10
#define s945(x) throw s946( L"unknown syntax: " + x );
#define s944(x) throw s946( L"syntax error: " + x );
namespace lang {
bool s653( const std::wstring& s, bool s707 = true );
} // namespace tdlang
extern const std::wstring s468;
enum s469 { s470, s471, s472, s1326, s473, s1234, s1235, 
s474, s475, s476, s477, s478, s1055, s2149,
s2306 };
enum s1983 { s2031 = 0, s2032, s2030, s2029 };
enum s1982 { s2038 = 0, s2034, s2035, s2036, s2037 };
enum s2175 { s2186, s2182, s2185, s2187, s2183, s2184 };
#define s1968 5
class s261;
class s479;
class s480;
class s271;
class s588;
class s270;
class s558;
class Stream;
typedef s270 s481;
typedef s270 TDType;
typedef s1::s9<s481> s482;
typedef s1::s9<s480> s483;
typedef s1::s9<s271> s484;
typedef s1::s9<s588> s485;
class s806;
typedef std::map<std::wstring, std::vector<std::wstring>> s919;
extern s919 s985;
class s270
: public s1::s10{
friend class s488;
s939 s968;
protected:
s469 s489;
s1053 s490;
s261* s299;
int wh;
public:
s270( const s262* ast_=NULL ) : s968( (s262*)ast_ ), s489( s470 ), s490( 0 ), 
wh( s7::s861 )  { }
s270( s469 pt_, const s262* ast_=NULL ) : s968( (s262*)ast_ ), s489( pt_ ), s490( 0 ), 
wh( s7::s861 ) { }
s270( s261* pass_, s469 pt_, const s262* ast_=NULL ) : s968( (s262*)ast_ ), s489( pt_ ),
s490( 0 ), s299( pass_ ), wh( s7::s861 )  { }
s270( const s270& r ) : s968( r.s968 ), s489( r.s489 ), s490( r.s490 ),
s299( r.s299 ), wh( r.wh ) {}
virtual ~s270();
s469 s491() const { return s489; }
const s262* s600() const { return s968.s15<s262*>(); }
virtual s480* s493();
virtual s483 s494( s480** s273, size_t s495 );
virtual s1053 s349() const { return s490; }
const s806& s1186() const;
virtual const std::wstring& s350() const;
virtual void s348( s1053 type );
s261* Pass() const  { return s299; }
int s615() const { return wh; }
void s1664( int i ) { wh = i; }
void s1251() { wh = 0; }
void s1249(bool b = true) { if(b) wh |= (1 << (s7::s1189-1)); 
else wh &= ~(1 << (s7::s1189-1));}
bool s1194() const { return wh >= 0 && wh < s7::s861; }
virtual bool s1193() const { return (wh > 0) && (wh & (1 << (s7::s1189-1))); }
virtual void s2180( s2175 st ) { }
virtual bool s498( const s480* s499 ) const;
virtual bool s1529( s1053 tp ) const;
virtual const s919& s996() const { return s985;  }
virtual void s497( const s271* s872, bool b = true );
virtual void release() {}
virtual const s480* s500() const;
virtual s270* s332( s588* s2041, s271* impl ) const;
virtual void s2117( s588* s2041, s271* impl, bool s2158 = true ) { }
static void s1322( const s262& ast_, s261* s299, s271* obj,
s1889& s331, std::vector<s270*>& s152 );
static s270* s501( const s262& s694, s261* s299, s271* obj,
s1889& s331, bool s2158 = false );
static s270* s1010( s261* s299, s270* par, s271* obj, s588* s214,
s1889& s331, bool proc );
static s482 s1009( const std::wstring& s77, const s262* ast_, s261* s299, 
s271* s585 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring( uint32_t s1552 = 0 ) const;
virtual s1311 to_bytes() const;
virtual void to_null();
virtual std::wstring trace( s1889& topics ) const { return L""; }
virtual void s303( std::wostream* pd, int s196 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s481*> s502;
s481* s1110( s502& m, const std::wstring& s151 );
void s665( const std::wstring& s, std::wstring& s1102, std::wstring& s598 );
class s480;
class s368;
class s480
: public s270{
protected:
s271* ns;
s480* s1688( s480** s273, size_t s495 );
s480* s1878( s480** s273, size_t s495 );
s480* s1922( s480** s273, size_t s495 );
s480* s2276( s480** s273, size_t s495 );
s480* s2277( s480** s273, size_t s495 );
s480* s2311( s480** s273, size_t s495 );
virtual s480* s1880( s480** s273, size_t s495 );
public:
s480( s261* s299, s469 pc, const s262* ast_, s271* ns_ ) 
: s270( s299, pc, ast_ ), ns( ns_ ) { }
s480( const s480& r );
virtual ~s480();
virtual void s347() = 0;
virtual s1053 s383( const std::wstring& s340 ) const = 0;
virtual s480* s351( const s262& s694, s271* s585, s1889& s331 ) const = 0;
virtual s480* s352( s271* s585, const std::vector<s270*>& l =
std::vector<s270*>(), const s262* ast_ = NULL ) const = 0;
virtual s480* s352( s271* s585, const std::vector<s1053>& vt ) const;
virtual std::wstring s297() const;
virtual std::wstring s827() const;
virtual std::wstring s2153() const;
virtual s480* s341( s1889& s277, s1889& s331,	bool s517 = true, bool s2150 = true ) const 
{	return NULL;}
virtual s588* s1670( s1889& s277, s588* s214,	s271* s585, s558* cs ) const;
virtual void s353( s270* p ) const = 0;
virtual s480* s1524( const s480* p ) const;
virtual const s480* s500() const override = 0;
void s503( s1889& s ) { /*s369 = s;*/ }
std::wstring s1658() { return L""; }// s369;}
virtual size_t s319() const = 0;
virtual bool operator==( const s480* p ) const = 0;
virtual bool operator<( const s480* p ) const = 0;
s480* s1879( s480** s273, size_t s495 );
s271* s2292() { return ns; }
void s2117( s588* s2041, s271* impl, bool s2158 = true ) override { ns = impl; }
s483 s494( s480** s273, size_t s495 ) override { return this; }
s480* s493() override;
virtual bool s553( s1889& s277, s368* s152, s1889& s331, bool fr ) const	{	return false;	};
virtual s270* s595( size_t off )	{	return NULL; }
virtual s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const;
virtual void s1919( Stream* ) const;
virtual void s1943( Stream* );
virtual void s1944( s1889& s );
};
enum s533 { s506, s507, s508 };
enum s509 { s510, s511, s512 };
typedef s1::s9<s806> s819;
typedef const s806* s918;
class s806
: public s1::s10{
public:
typedef s1053 s730;
typedef s730 s886;
typedef std::vector<s730> Cont;
private:
Cont vt;
size_t s1085;
public:
s806() {}
s806( s730 t1, s730 t2 = (s730)-1, s730 t3 = (s730)-1 );
s806( const s806& right );
s806( const Cont& v );
void s348( s730 t );
void s348( s918 pt );
void s778( s730 t );
void s778( s918 pt );
s886 s349( size_t n = 0 ) const;
const Cont& s812() const { return vt; }
void s812( std::vector<s270*>& s152 ) const;
bool operator==( const s806& p ) const;
size_t s319() const { return s1085; }
};
class s479;
class s261;
class s831;
struct s957{
std::size_t operator()( const s806& k ) const{
return k.s319();}
};
struct s958{
std::size_t operator()( const s806& l, const s806& r ) const{
return l.operator==( r );}
};
class s488{
typedef std::map<std::wstring, s1053> s952;
typedef std::map<s1053, s1::s9<s831>> s2300;
typedef std::unordered_map<s806, s1053, s957, s958> s955;
typedef std::map<std::wstring, std::list<std::wstring>> s1775;
typedef std::map<std::wstring, std::set<std::wstring>> s906;
typedef std::map<s806::s886, s906> s919;
typedef std::map<std::wstring, traitnum_t> s1144;
typedef std::unordered_map<traitnum_t, std::wstring> s1237;
std::vector<s483> s1103;
std::vector<std::wstring> s1086;
std::vector<std::wstring> s2302;
std::vector<s806> s1091;
s952 s1087;
s2300 s2308;
s955 s1092;
s1775 s1826;
s919 s910;
s1144 s885;
s1237 s1248;
traitnum_t s1195;
s1053 s2305;
std::vector<traitnum_t>s1263;
std::vector<s1053>s1499;
std::vector<std::vector<s1053>> s1539;
s261* s299;
s1053 s1060( const s806::Cont& v, s1889& s344 );
void s1161( s1889& alias, s1889& s344, s1889& s1825 );
void s2303( s1889& def, s831* pred, s1889& s1825 );
public:
s488( s261* pass_ );
void reset();
void s289();
void s514( const s479& st );
s1053 s217( s480* p, s1889& s344 );
void s1651( s1889& s344 );
void s1862( s1889& s1102 );
s1053 s1038( const s806::Cont& v );
traitnum_t s1241( s1889& trait, s1053& s1498 );
void s1152( s806::s886 type, s1889& trait, s1053& s1498 );
bool s1188( s1053 s616, traitnum_t tra );
bool s1453( s1053 s616, s1053 alias );
traitnum_t s1145( s1053 s616 ) const { return s1263[s616]; }
traitnum_t s1446( s1053 alias ) const;
void s1521( s1053 s616, s1053 is );
bool s1522( s1053 s616, s1053 is );
bool s1522( const s270* s616, const s270* is );
s480* s515( const s6::s140& s346, s271* s585, s1889& s516 );
s480* s515( const s262& s694, s271* s585, s1889& s516 );
s480* s515( s1053 type, s271* s585, s1889& s516 );
const s480* get( s1889& s76, bool s517 = true ) const;
s1053 s1002( s1889& s344, bool s517=true ) const;
s1053 s1003( const s806& vt, bool s517=true ) const;
const s806& s1005( s1053 t ) const;
const s480* s999( s806::s886 t ) const;
s1889& s797( s1053 n ) const;
bool s155( s1889& s76 ) const;
void s783();
bool s1238();
double s1240();
int s1246();
void s303( std::wostream* pd, int s196 = 0 ) const;
static void s2103( const s806::Cont& v, size_t& idx, s806::Cont& s152 );
static void s1000( const s806::Cont& v, std::vector<size_t>& s2118,
s806::Cont& s152 );
size_t s1048( s1889& s, size_t& pos, s806::Cont& s152 );
std::wstring s1004( const s806::Cont& tp );
s1053 s2473( s1889& s, s806::Cont& vt );
static std::wstring s1341( s1889& tn );
std::wstring s1264( s1889& tn, s1889& s1102 );
void s2121( const s806::Cont& v_, s806::Cont& s152, size_t s2101 = 0 );
};
class s518
: public s1::s10{
std::vector<std::wstring> s519;
s509 pv;
public:
s518() : pv( s510 ) { }
s518( s509 pv, const std::vector<std::wstring>& s520 );
s518( s1889& ag, s1889& s77 );
s509 s557( s1889& s496 ) const;
static std::vector<std::wstring> s522;
};
class s523
: public s1::s10{
typedef std::map<std::wstring, s518*> s524;
s524 s525;
public:
s523( ) { }
void s526( s509 pv, s262* );
void s527( s1889& s, s518& pl );
void s528( s1889& s, s1889& s521 );
s509 s529( s1889& mem, s1889& s496 );
void s530( s1889& s331,
std::vector<std::wstring>& s152 );
};
class s479{
public:
enum s144 { s145, s531, s146, s147 };
typedef std::map<std::wstring, s482> s532;
private:
s532 s550;
s533 s534;
s523* s536;
bool s535( s1889& s76, s144 ap = s145 );
public:
s479( ): s534( s507 ), s536( NULL ) {}
s479( s533 am ) : s534( am ), s536( NULL ) {}
s479( const s479& s537 );
~s479();
const s532& Table() const { return s550; }
void s497( s271* s496, s271* s585, bool s513 = true );
void s1636();
void reset();
size_t s319() const;
bool compare( const s532& r ) const;
void s538( s1889& s76, s270* sym, s144 ap = s145 );
void s538( s1889& s76, s6::s141 s346, s144 ap = s145 );
void s539( s1889& s76 );
void s540( const s6::s142& obj, s144 ap = s145 );
void s288( const s479& t, s144 ap = s145 );
bool empty() const { return s550.empty(); }
bool s155( s1889& s76 ) const;
s480* get( s1889& s76, bool s517 = true ) const;
void s541( std::vector<std::wstring>& s152 ) const;
void s542( std::vector<std::wstring>& s152 ) const;
void s543( std::vector<std::wstring>& s152 ) const;
void s544( const s479& t, std::vector<std::wstring>& s152 ) const;
bool implements( const s479& t ) const;
void copy( s479& t, s271* s585, s588* s584, s144 ap = s145 ) const;
void s545( s479& t ) const;
void s1600( s479& t ) const;
void s546( s509 pv, s262* s79 );
void s530( s1889& s331,
std::vector<std::wstring>& s152 );
bool s547( s1889& s277, s1889& s331 ) const;
std::wstring to_wstring( uint32_t s1552 ) const;
void s303( std::wostream* pd, int s196 = 0 ) const;
};
class s548{
typedef std::pair<s480*, std::wstring> s549;
typedef std::multimap<std::wstring, s549> s532;
s532 s550;
std::vector<std::wstring> s556;
std::wstring s331;
public:
s548();
void s551( s1889& s76 );
bool s2162( s1889& s76 );
void s497( s261* s299, s1889& s555 );
void s1636( s261* s299 );
void s552( s1889& s76, s261* s299, s1889& s555 );
bool s553( s1889& sym, s368* ref );
void copy( s548& t ) const;
};
extern s1::s9<s523> s554;
class s261;
class s333;
typedef void ( *s613 )( s480** s273, size_t n );
namespace s1500 {
extern s1053 s1260;
extern s1053 s1537;}
class s1112{
s333* s585;
std::vector<s1053> s1267;
std::vector<s482> s905;
public:
s1112() : s585( NULL ) {}
s1112( const std::vector<s482>& v, s333* s589 /*= NULL*/ );
s1112( const std::vector<s1053>& v, s333* s589 = NULL )
: s585( s589 ), s1267( v ) {}
bool operator==( const s1112& s521 ) const;
bool operator<( const s1112& s521 ) const;
const s333* Subj() const { return s585; }
const std::vector<s482>& s599() const { return s905; }
std::wstring s1318( s261* s299 ) const;
};
struct s1984{
s1053
s2309,
Bool,
Byte,
ByteArray,
ByteStream,
Char,
DateTime,
s411,
Double,
s358,
FileStream,
Filter,
HashIndex,
HashSet,
Index,
Int,
Lambda,
Long,
No,
Null,
s271,
Position,
Range,
Seq,
Set,
String,
s782,
Table,
TSDBase,
Tuple,
s1516,
s741,
Vector;
s1984() {
s2309 = Bool = Byte =	ByteArray =	ByteStream = Char =	DateTime = s411 = Double =	s358 =
FileStream = Filter =	HashIndex =	HashSet = Index =	Int =	Lambda = Long =	No = Null = s271 =
Position = Range = Seq = Set = String = s782 = Table = TSDBase = Tuple = s1516 =
s741 =	Vector = 0;}
const s480* operator()( s261* s299, s1053 tp );
};
extern s1984 Types;
struct s1132{
s1053 s335;
s613 s336;
bool s1158;
const std::vector<s1982>* s2019;
s1132()
: s335( 0 ), s336( NULL ), s1158( true ), s2019( NULL ) {}
s1132( s1053 pt, s613 fp, bool s1159 = true, 
const std::vector<s1982>* s1992 = NULL )
: s335( pt ), s336( fp ), 
s1158( s1159 ), s2019( s1992 ) {}
};
class s333
: public s480{
public:
class s334{
std::wstring s277;
s1053 s335;
s613 s336;
std::vector<s1112> s1153;
size_t s1030, s1027;
std::vector<std::wstring> s1199;
bool s1169;
bool s1158;
std::vector<s1982> s2028;
public:
enum class s1123 : uint32_t { s1170 = ((uint32_t)s2::s16::s17::s25) + 1 };
s334( const std::wstring& s671, s613 fp, s1053 s337,
const std::vector<s1112>& v=std::vector<s1112>(), 
size_t s1031 = 0, size_t s1028=(size_t)-1, bool s1159 = true,
const std::vector<std::wstring>& s1198 = std::vector<std::wstring>(),
const std::vector<s1982>& s1993 = { s2038 } )
: s277( s671 ), s335( s337 ), s336( fp ), s1153(v), 
s1030(s1031), s1027(s1028), s1199( s1198 ), s1169(false), 
s1158( s1159 ), s2028( s1993 ) {}
s334( const std::wstring& s671, s613 fp, s1053 s337,
const std::vector<s1112>& v, 
bool s1159, const std::vector<s1982>& s1993 )
: s277( s671 ), s335( s337 ), s336( fp ), s1153(v), 
s1030(0), s1027(0), s1169(false), 
s1158( s1159 ), s2028( s1993 ) {}
s334()
: s336( NULL ), s1169( false ), s1158( true ), s2028( { s2038 } ){}
s613 s1126() const { return s336; }
size_t s935() const { return s1030;  }
size_t s934() const { return s1027;  }
const std::vector<std::wstring>& Markers() const { return s1199; }
s1053 s492() const { return s335; }
void s1252( s1053 t) { s335 = t; }
void s1250( bool b ) { s1169 = b; }
bool s1176( ) const { return s1169; }
bool s1193() const { return s1158; }
const std::vector<s1982>* s2001() const { return &s2028; }
bool s1156( const s1112& s686 ) const;
};
protected:
typedef std::multimap<std::wstring, s334*> s338;
virtual const s338& s339() const = 0;
static size_t s751;
public:
s333( s261* s299, s271* ns_, const s262* ast_ ) : s480( s299, s471, ast_, ns_ ) {}
s333( const s333& r ) : s480( r ) {}
virtual ~s333() {}
s1053 s383( const std::wstring& s340 ) const override;
static void s777( s261* s299, bool soft = false );
static size_t s800() { return s751;  }
virtual const std::vector<std::wstring>& s1181( s1889& s340 ) const;
virtual s1132 s1187( s1889& s340 ) const;
virtual s1132 s1182( s1889& s340, s1112& ap ) const;
virtual s1132 s1177( s1889& s340, s1112& ap );
const s480* s500() const override;
virtual void* addr() = 0;
s483 s494( s480** s273, size_t s495 ) override;
static s480* s342( s261* s299, const std::wstring& s346, const std::wstring& s331 );
void s1523( s480* s42 );
};
class s355
: public s333{
static s338 s345;
double s346;
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s385( s480** s273, size_t n );
static void s386( s480** s273, size_t n );
static void s387( s480** s273, size_t n );
static void s388( s480** s273, size_t n );
static void s389( s480** s273, size_t n );
static void s390( s480** s273, size_t n );
static void s391( s480** s273, size_t n );
static void s392( s480** s273, size_t n );
static void s393( s480** s273, size_t n );
static void s394( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s396( s480** s273, size_t n );
static void s397( s480** s273, size_t n );
static void s398( s480** s273, size_t n );
static void s399( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s407( s480** s273, size_t n );
static void s408( s480** s273, size_t n );
static void s401( s480** s273, size_t n );
static void s403( s480** s273, size_t n );
static void s404( s480** s273, size_t n );
static void s409( s480** s273, size_t n );
static void s2197( s480** s273, size_t n );
static void s2195( s480** s273, size_t n );
static void s406( s480** s273, size_t n );
static void s1962( s480** s273, size_t n );
static void s1961( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef double s1374;
s355( s261* s299 ) : s333( s299, NULL, NULL ) {}
s355( const s355& r );
s355( s261* s299, const std::vector<s270*>& l );
s355( s261* s299, double d );
s355( s261* s299, const std::wstring& s, size_t& pos );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
void s497( const s271* s584, bool b = true ) override;	
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
double* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0.0; }
operator int() const override { return (int)s346; }
operator double() const override { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s1944( s1889& s ) override;
void s1943( Stream* ) override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s357
: public s333{
static s338 s345;
bool s346;
static void s384( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
static void s410( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
s357( s261* s299 ) : s333( s299, NULL, NULL ) {}
s357( s261* s299, bool b );
s357( s261* s299, const std::wstring& s, size_t& pos );
s357( const s357& right );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
bool* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
void s497( const s271* s584, bool b = true ) override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
operator bool() const override { return s346; }
operator int() const override { return (int)s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s1944( s1889& s ) override;
void s1943( Stream* ) override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
extern s1::s9<s357> s366;
extern s1::s9<s357> s367;
class s358
: public s333{
enum s2259 { s2261, s2262 };
static s338 s345;
static void s785( s480** s273, size_t n );
static void s505( s480** s273, size_t n );
static void s2265( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
s2259 s2263;
std::wstring s78;
s483 obj;
public:
s358( const s358& right );
s358( s261* s299, const std::wstring& s = std::wstring( L"" ) );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
void create( const std::vector<s482>& l );
s1889& Msg() const { return s78; }
void s360( const std::wstring& s ) { s78 = s; }
void* addr() override { return (void*)0; }
void s497( const s271* s584, bool b = true ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override { return s78; }
operator bool() const override { return false; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s361
: public s333{
static s338 s345;
void s347() override {}
const s338& s339() const override { return s345; }
public:
s361( s261* s299, s271* s585 = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
void* addr() override { return (void*)0; }
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override { }
void s497( const s271* s584, bool b = true ) override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override {	return L"";	}
operator double() const override { return (double)0; }
operator int() const override { return 0; }
operator bool() const override { return false; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
extern s1::s9<s361> s362;
class s381
: public s333{
traitnum_t s1261;
static s338 s345;
void s347() override {}
const s338& s339() const override { return s345; }
public:
s381( s261* s299, s271* ns = NULL, traitnum_t tn = 0, s469 pc = s470 );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
s270* s332( s588* s2041, s271* impl ) const override;
bool s498( const s480* s499 ) const override;
bool s1529( s1053 tp ) const override;
traitnum_t s1528() const { return s1261; }
s1889& s350() const override;
void* addr() override { return (void*)0; }
void s353( s270* p ) const override { }
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s497( const s271* s584, bool b = true ) override;
operator bool() const override { return false; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1691
: public s333{
public:
enum s1690 { s1726, s1725, s1724, s1727, s1808 };
typedef std::chrono::steady_clock s1779;
typedef std::chrono::system_clock s1780;
private:
static s338 s345;
void s347() override;
const s338& s339() const override { return s345; }
static void s384( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
static void s410( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s1834( s480** s273, size_t n );
static void s1857( s480** s273, size_t n );
s1690 s1728;
std::tm s346;
s1780::time_point s1859;
static std::wregex s1750, s1752, s1751, s1848;
bool s1713( const std::wstring& s346, std::tm& t, s1690& s616 ) const;
public:
s1691( s261* s299 );
s1691( s261* s299, const std::wstring& s );
s1691( s261* s299, const std::tm& _t, s1690 s616 );
s1691( const s1691& right );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
void* addr() override { return (void*)0; }
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
void s497( const s271* s584, bool b = true ) override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1944( s1889& s ) override;
operator bool() const override { return false; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1589 
: public s333{
friend class s769;
s479 s625;
static s338 s345;
std::wstring s1632;
static void s1226( s480** s273, size_t n );
static void s1628( s480** s273, size_t n );
static void s1626( s480** s273, size_t n );
static void s1623( s480** s273, size_t n );
static void s1624( s480** s273, size_t n );
static void s1645( s480** s273, size_t n );
static void s1647( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
s1589( s261* s299 ) : s333( s299, NULL, NULL ) {}
s1589( s261* s299, s271* s585, s1889& s77, bool typed=true, const s262* ast_=NULL );
s1589( const s1589& right, s480* s2108 );
s1589( s261* s299, s271* s585, const s6::s142* s1631, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
void* addr() override { return (void*)&s625; }
void s497( const s271* s872, bool b = true ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void load( const std::wstring& s77, bool typed, bool s193 );
void s1629( const s6::s142* ob, bool typed, s479::s144 ap = s479::s145 );
void s1619( s479::s532& st ) const;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1944( s1889& s ) override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
extern s1::s9<s381> s865;
extern s1::s9<s381> s363;
extern s1::s9<s381> s364;
extern s1::s9<s381> s365;
extern s1::s9<s381> s866;
extern s1::s9<s381> s2130;
extern s1::s9<s381> s1671;
extern s1::s9<s381> s1509;
#define s1142 Types.Null
#define s1138 Types.Bool
#define s1297 Types.Byte
#define s1566 Types.Char
#define s1141 Types.Int
#define s1140 Types.Double
#define s1514 Types.Long
#define s1515 Types.s1516
#define s2313 Types.s2309
#define s1143 Types.String
#define s1139 Types.ByteArray
#define s1704 Types.Vector
#define s1703 Types.s741
#define s1700 Types.Index
#define s1702 Types.Tuple
#define s1699 Types.HashIndex
#define s1567 Types.Position
#define s1698 Types.DateTime
#define s1701 Types.Lambda
#define s1783 Types.TSDBase
#define s1782 Types.Table
#define s1891 Types.s411
#define s1403 Types.Range
#define s1893 Types.Filter
#define s1404 Types.Seq
#define s1894 Types.s782
#define s1890 Types.ByteStream
#define s1892 Types.FileStream
#define s2206 Types.Set
#define s2239 Types.HashSet
#define s1137 ( std::numeric_limits<size_t>::max )( )
#define U64_MAX ( std::numeric_limits<uint64_t>::max )( )
typedef s355 TDDouble;
class s368
: public s270{
std::wstring s369;
s482 s370;
const s480* s371;
std::vector<size_t> s372;
size_t s373;
bool s1158;
static size_t s2266;
public:
s368( s1889& s, s261* s299, s469 cat = s470, bool _cnst = false );
s368( const s368& right, s480* s2166 = NULL );
void reset();
s480* s493() override;
const s480* s500() const override { return s371; }
const s482 s378();
bool s1193() const override { return s1158; }
void s1249() { s1158 = true; }
const std::wstring& s614() const { return s369; }
void s2269();
s483 s494( s480** s273, size_t s495 ) override;
s480* s374() const;
s480* s375();
size_t s1293() const { return s373; }
void s376( size_t off, const s480* proto );
void s1332( s368* ptr );
size_t s377() const { return s373; }
uint32_t Id() const { return (uint32_t)s373; }
s270* s332( s588* s2041, s271* impl ) const override;
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
void s497( const s271* s584, bool fr = true ) override;
void s379( s480* p );
void s380( s480* p ) { s371 = p; }
void s974( const std::vector<std::wstring> &v );
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1587
: public s480{
s483 pobj;
protected:
virtual s480* s351( const s262& s694, s271* s585,
s1889& s331 ) const override {	return NULL; }
public:
s1587( s261* s299 )
: s480( s299, s1326, NULL, NULL ), pobj(0) {}
virtual ~s1587() { }
void s1646( s480* obj ) { pobj = obj; }
s483 s2102( ) { return pobj; }
s270* s595( size_t off ) override 
{ return pobj->s595( off ); }
void s347() override {}
s1053 s383( const std::wstring& s340 ) const override { return 0; }
s480* s352( s271* s585, const std::vector<s270*>& l =
std::vector<s270*>(), const s262* ast_ = NULL ) const override { return NULL;	}
void s353( s270* p ) const override {}
s480* s1524( const s480* p ) const override { return NULL; }
const s480* s500() const override { return NULL; }
size_t s319() const override { return 0;  }
bool operator==( const s480* p ) const override { return false; }
bool operator<( const s480* p ) const override { return false; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef s1::s9<s368> s486;
typedef s1::s9<s1587> s2154;
struct s1705{
std::wstring s1682;
std::wstring rowSep;
std::wstring s1719;
std::wstring s1720;
bool stringsQuoted;
bool promInts;
bool mixedTypes;
bool s1811;
bool s1998;
s1705()
: s1682( L"," ), rowSep( L"\n" ), s1720( L"." ), stringsQuoted( false ),
promInts( false ), mixedTypes( false ), s1811( false ), s1998( false )	{	}
s1705( const std::wstring& fs, const std::wstring& rs, const std::wstring& cn,
const std::wstring& dp, bool sq, bool pi, bool mt )
: s1682( fs ), rowSep( rs ), s1720( dp ), stringsQuoted( sq ),
promInts( pi ), mixedTypes( mt ), s1811( false ), s1998( false )	{	}
};
extern s1705 s1723;
extern s6::s1680 s1721;
template<class s1301, class Der>
class s1295 :
public s333{
protected:
typedef Der s1157;
s1301 s346;
static s338 s345;
static void s384( s480** s273, size_t n );
static void s385( s480** s273, size_t n );
static void s386( s480** s273, size_t n );
static void s387( s480** s273, size_t n );
static void s388( s480** s273, size_t n );
static void s389( s480** s273, size_t n );
static void s401( s480** s273, size_t n );
static void s390( s480** s273, size_t n );
static void s391( s480** s273, size_t n );
static void s392( s480** s273, size_t n );
static void s393( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s410( s480** s273, size_t n );
static void s396( s480** s273, size_t n );
static void s397( s480** s273, size_t n );
static void s398( s480** s273, size_t n );
static void s399( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s2081( s480** s273, size_t n );
static void s1950( s480** s273, size_t n );
static void s1949( s480** s273, size_t n );
static void s402( s480** s273, size_t n );
static void s2293( s480** s273, size_t n );
static void s403( s480** s273, size_t n );
static void s404( s480** s273, size_t n );
static void s405( s480** s273, size_t n );
static void s409( s480** s273, size_t n );
static void s1583( s480** s273, size_t n );
static void s1535( s480** s273, size_t n );
static void s1536( s480** s273, size_t n );
static void s1489( s480** s273, size_t n );
static void s406( s480** s273, size_t n );
void s347() override;
const s333::s338& s339() const override;
public:
typedef s1295<s1301, Der> s1309;
s1295( s261* s299, s271* ns_, const s262* ast_ )
: s333( s299, ns_, ast_ ) {}
s1295( const s1309& r )
: s333( r ), s346( r.s346 ) {}
template<class s1518, class s1519>
static void s1520( s480* src, s480* s771 );
s480* s1524( const s480* p ) const override;
s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s343;
class s343
: public s1295<std::int32_t, s343>{
static s338 s345;
static void s1226( s480** s273, size_t n );
static void s2290( s480** s273, size_t n );
static void s2307( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef std::int32_t s1374;
s343( ) : s343( NULL, (s271*)NULL ) {}
s343( s261* s299, s271* s585 = NULL );
s343( const s343& );
s343( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
s343( s261* s299, int i, s271* s585 = NULL );
s343( s261* s299, s1889& s, size_t& pos, s271* s585 = NULL );
virtual ~s343();
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
bool s1529( s1053 tp ) const override;
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
void s497( const s271* s584, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
s1374* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0; }
operator int() const override { return s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void to_null( ) override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1292
: public s1295<std::int64_t, s1292>{
protected:
static s338 s345;
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef std::int64_t s1374;
s1292() : s1292( NULL ) {}
s1292( s261* s299 );
s1292( const s1292& );
s1292( s261* s299, const std::vector<s270*>& l );
s1292( s261* s299, int64_t i );
s1292( s261* s299, s1889& s, size_t& pos );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s584, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
int64_t* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0; }
operator int() const override { return (int)s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
};
class s1517
: public s1295<std::uint64_t, s1517>{
protected:
static s338 s345;
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef std::uint64_t s1374;
s1517() : s1517( NULL, (s271*)NULL ) {}
s1517( s261* s299, s271* s585 = NULL );
s1517( const s1517& );
s1517( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
s1517( s261* s299, uint64_t i, s271* s585 = NULL );
s1517( s261* s299, s1889& s, size_t& pos, s271* s585 = NULL );
s480* s351( const s262& s694, s271* s585, 	s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s584, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
s1374* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0; }
operator int() const override { return (int)s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
};
template <>
inline void s1295<s1517::s1374, s1517>::s401( s480** s273, size_t s495 ){
( (s1517*)s273[0] )->s346 = ( (s1517*)s273[1] )->s346;}
template <>
inline void s1295<s1517::s1374, s1517>::s386( s480** s273, size_t s495 ){
if( s495 == 2 )
( (s1517*)s273[0] )->s346 = ( (s1517*)s273[1] )->s346;
else {
s273[2]->s353( s273[0] );
( (s1517*)s273[0] )->s346 =
( (s1517*)s273[1] )->s346 - ( (s1517*)s273[0] )->s346;}}
class s1284
: public s1295<tdbyte_t, s1284>{
protected:
static s338 s345;
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef tdbyte_t s1374;
s1284() : s1284( NULL ) {}
s1284( s261* s299 );
s1284( const s1284& );
s1284( s261* s299, const std::vector<s270*>& l );
s1284( s261* s299, tdbyte_t i );
s1284( s261* s299, const std::wstring& s, size_t& pos );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s584, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
tdbyte_t* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0; }
operator int() const override { return s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override { return std::to_wstring( s346 ); }
void s1919( Stream* ) const override;
};
class s1560
: public s1295<wchar_t, s1560>{
protected:
static s338 s345;
static void s1226( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s2224( s480** s273, size_t n );
static void s2222( s480** s273, size_t n );
static void s2223( s480** s273, size_t n );
static void s884( s480** s273, size_t n );
static void s883( s480** s273, size_t n );
static void s2281( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
typedef wchar_t s1374;
s1560() : s1560( NULL ) {}
s1560( s261* s299 );
s1560( const s1560& );
s1560( s261* s299, const std::vector<s270*>& l );
s1560( s261* s299, wchar_t i );
s1560( s261* s299, s1889& s, size_t& pos );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s584, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
wchar_t* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return s346 != 0; }
operator int() const override { return s346; }
operator double() const override { return (double)s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override { return std::wstring( 1, s346 ); }
void s1919( Stream* ) const override;
};
typedef s343 TDInt;
#define s2316 INT64_MAX
#define s2317 INT64_MIN
typedef std::vector<int64_t> s2399;
typedef std::list<int64_t> s2379;
typedef std::deque<int64_t> q64_t;
typedef q64_t s2398;
typedef s2398 *s2384;
typedef const s2398 *s2382;
typedef int64_t s2394;
class s2309 {
static const int s2315 = 7;
static const int s2314 =  10000000;
static const int64_t _BASE2 = 100000000000000;
static const int64_t _HP2 = 8388608;
static const int64_t _HP2_LEN = 24;
static s2394 _P2_ARR[];
s2394 s2344;
s2398 _val;
s2382 s2339;
bool s2342;
const s2398& s2323() const { return s2339 ? *s2339 : _val; }
s2398& s1411();
bool s2332() const { return s2339 ? s2339->empty() : _val.empty(); }
static void s2318( const s2398& l, const s2398& r, s2398& s152 );
void s2318( const s2398& b, s2398& s152 ) const;
void s2318( s2394 b, s2398& s152 ) const;
void s2320( const s2309& b, s2309& s152 ) const;
void s2319( const s2309& b, s2309& s152 ) const;
static void s2346( const s2398& l, const s2398& r, s2398& s152 );
static void s2346( const s2398& a, s2394 b, s2398& s152 );
void s2348( const s2309& b, s2309& s152 ) const;
void s2347( const s2309& b, s2309& s152 ) const;
void s2336( const s2309& b, s2309& s152 ) const;
void s2334( const s2309& b, s2309& s152 ) const;
void s2333( const s2398& b, s2398& s152 ) const;
static void s2333( const s2398& a, const s2398& b, s2398& s152 );
static void s2333( const s2398& a, s2394 b, s2398& s152 );
static void s2335( const s2398& a, const s2398& b, 
s2398& s152 );
void s2329( const s2309& b, s2309& quot, s2309& rem ) const;
void s2328( const s2309& b, s2309& quot, s2309& rem ) const;
void _divmod1( const s2398& b, s2398& quot, s2398& rem ) const;
void _divmod2( const s2398& b, s2398& quot, s2398& rem ) const;
static void s2327( const s2398& a, s2394 b, s2398& quot, s2398& rem );
int s2325( s2394 b ) const;
static int s2325( const s2398& a, const s2398& b );
static void s2343( s2394 a, s2398& s152 );
bool s2330() const;
void s2406();
void s2412( const s2309& base, s2309& s152);
s2394 s2456() const;
size_t s2401() const;
static int64_t s2404( const s2309& s346, const s2309& base, s2309& p );
static void s2453( const s2309& s346, bool s2460, std::vector<s2309>& s152 );
static void s2451( const s2309& s346, int64_t s2457, int64_t c, s2309& s152 );
static void _pollardRho2( const s2309& s346, int64_t s2457, int64_t c, s2309& s152 );
static void s2452( const s2309& n, std::vector<s2309>& s152 );
public:
s2309( const std::wstring& s );
s2309( s2394 _sm );
s2309( s2382 s1057, bool s2390 );
s2309( const s2309& r, bool s2390 );
void reset();
void s2360( const s2309& b, s2309& s152 ) const;
void s2396( const s2309& b, s2309& s152 ) const;
void s2381( const s2309& b, s2309& s152 ) const;
void s2367( const s2309& b, s2309& quot, s2309& rem ) const;
void s2360( int64_t b, s2309& s152 ) const;
void s2396( int64_t b, s2309& s152 ) const;
void s2381( int64_t b, s2309& s152 ) const;
void s2367( int64_t b, s2309& quot, s2309& rem ) const;
void s2418( const s2309& b, s2309& s152 ) const;
void s2438( const s2309& b, s2309& s152 ) const;
void s2440( const s2309& exp, const s2309& mod, s2309& s152 ) const;
void s2439( const s2309& b, s2309& s152 ) const;
void s2414( const s2309& b );
void s2441( const s2309& b );
void s2447( const s2309& b );
void s2419( const s2309& b );
void s2395();
void s2463();
void s2383( int32_t e, s2309& s152 ) const;
void s2470( s2394 n );
void s2469( s2394 n );
void s2413( s2309& s152 );
size_t s2393() const;
s2394 s2370() const { return s2344; }
void s2468( const std::wstring& s );
void s2389( s2394 s346 );
void s2387( const s2309& bl );
void s2387( int64_t s346 );
void s2387( const std::wstring& s );
void s2388( bool s2390 );
size_t s319() const;
bool operator==( const s2309& p ) const;
bool operator<( const s2309& p ) const;
int compare( const s2309& b ) const;
int s2417( const s2309& b ) const;
int compare( s2394 b ) const;
bool s2373( const s2309& bl ) const;
bool s2373( s2394 b ) const;
bool s2375( const s2309& bl ) const;
bool s2375( s2394 b ) const;
bool s2374() const;
bool s2429() const;
bool s2428() const;
bool s2424() const;
bool s2425() const;
bool s2462() const;
bool s2423( const s2309& b ) const;
static void gcd( const s2309& a, const s2309& b, s2309& s152 );
int s2422() const;
static bool s2437( const s2309& n, const std::vector<int64_t>& v );
static bool s2437( const s2309& n, const std::vector<s2309>& v );
static void s2445( const s2309& a, const s2309& b, s2309& s152 );
bool s2426( bool s150 ) const;
bool s2427( size_t s2433 ) const;
void s2466( std::vector<s2309>& s152 ) const;
void s1944( const std::wstring& s ); // override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const; // override;
void s303( std::wostream* pd, int s196 = 0 ) const; // override
void s2351();
bool s2354();
};
extern s2309 s2380;
class s2310
: public s333{
static s338 s345;
s2309 s346;
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s401( s480** s273, size_t n );
static void s385( s480** s273, size_t n );
static void s386( s480** s273, size_t n );
static void s387( s480** s273, size_t n );
static void s388( s480** s273, size_t n );
static void s389( s480** s273, size_t n );
static void s390( s480** s273, size_t n );
static void s391( s480** s273, size_t n );
static void s392( s480** s273, size_t n );
static void s393( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s396( s480** s273, size_t n );
static void s397( s480** s273, size_t n );
static void s398( s480** s273, size_t n );
static void s399( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s2431( s480** s273, size_t n );
static void s2430( s480** s273, size_t n );
static void s2467( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
static void s2341( s2310* ob, s270* v );
public:
typedef s2309 s1374;
s2310( s261* s299 ) : s333( s299, NULL, NULL ), s346((uint64_t)0) {}
s2310( const s2310& r );
s2310( s261* s299, const std::vector<s270*>& l );
s2310( s261* s299, const s2309& bl );
s2310( s261* s299, const std::wstring& s, size_t& pos );
s2310( s261* s299, int64_t n );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
void s497( const s271* s584, bool b = true ) override;	
s1053 s1178( s1889& s1540,	const std::vector<s482>& l ) const override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
s2309* s354() { return &s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return false; }
operator int() const override { return 0; }
operator double() const override { return 0.0; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s1944( s1889& s ) override;
void s1943( Stream* ) override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s588;
class s271;
typedef std::vector<std::pair<std::wstring, size_t>> s619;
typedef std::map<std::wstring, s271*> s620;
typedef std::map<std::wstring, s262*> s621;
class s271
: public s480{
protected:
const s271* s622;
const s271* s623;
s486 s1648;
const std::wstring& s344;
std::wstring s277;
std::wstring s624;
s479 s625;
s548* s626;
std::vector<s482> s627;
std::vector<s368> s628;
s2175 s2179;
void s347() override { }
s480* s1689( s480** s273, size_t s495 );
public:
s271( const s271& s629, std::vector<s482>& s273, const s262* ast_/*=NULL*/, s271* ns_/* = NULL*/ );
s271( s261* s299, s1053 s337, s469 pc/* = s470*/, const s262* ast_/* = NULL*/, s271* ns_/* = NULL*/, s2175 st = s2182  );
s271( s1889& s277, s261* s299, s469 pc, const s262* ast_/* = NULL*/, s271* ns_/* = NULL*/, s2175 st = s2182 );
s271( s1889& s344, const std::wstring& s277, s261* s299, s479& s630,
const s479& s625, const s262* ast_/* = NULL*/, s2175 st/* = s2186*/  );
s271( s262& s694, s261* s299, s469 pc, s271* ns, s533 am,
s620& cl, s619& cnl, s621& al, s2175 st );
virtual ~s271();
s1889& s350() const override { return s344; }
virtual s1889& s298() const { return s277; }
std::wstring s297() const override;
std::wstring s827() const override;
s2175 s2177() const { return s2179; }
void s2180( s2175 st ) override { s2179 = st; }
static s270* s631( const s6::s142& obj, s1889& s277, s261* s299 );
static s270* s631( std::multimap<std::wstring, s481*>& v, s481* s584 );
s480* s632( const s262& s694, s480* s585, s1889& s331 ) const;
using s480::s352;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s1524( const s480* p ) const override;
s1053 s383( s1889& s340 ) const override;
bool s498( const s480* s499 ) const override;
const s919& s996() const override { return s985; }
bool s723( s1889& f ) const;
void s844( s1889& s76, s480* s346, s479::s144 ap = s479::s145 );
void s1642( s1889& s76, s480* s346 );
void s1627( const s1589* ob );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
const s480* s500() const override { return s622; }
const s271* s633() const { return s623; }
s1889& s634() const { return s624; }
s480* s341( s1889& s277, s1889& s331,
bool s517 = true, bool s2150 = true ) const override;
s588* s1670( s1889& s277, s588* s214,	s271* s585, s558* cs ) const override;
void s642( s262& s694 );
void s552( s1889& s76, s1889& s555 );
bool s2162( s1889& s76 );
void s635( s262& s694 );
void s962( s262& s694 );
void s636( s1889& s331,	std::vector<std::wstring>& s152 );
bool s553( s1889& s277, s368* s152, s1889& s331, bool fr ) const override;
size_t s637( const std::wstring& s277 ) const;
s270* s595( size_t off ) override;
s480* s638( s1889& s277, s1889& s331,
bool s517=true ) const;
bool s639( s1889& sym, s1889& s496 ) const;
bool s529( s1889& sym );
void s497( const s271* s872, bool b ) override;
void s641( const s479& s273 ); 
void s153( s262& s694 );
void s1636();
void s2117( s588* s2041, s271* impl, bool s2158 = true ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
void s640( s271* s643 ) const;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s1919( Stream* ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s558
: public s270{
const std::wstring s598;
std::vector<s270*> s273;
s939 past;
bool s2158;
public:
s558( s261* pass_, const s262* ast_, bool s2159 = false )
: s270( pass_, s474 ), past( (s262*)ast_ ), s2158( s2159 ){}
s558( s261* pass_, s1889& s1540, const std::vector<s270*>& l, const s262* s694, bool s2159 = false );
s558( const s558& s537 );
s1889& s298() const { return s598; }
void s2170( bool b ) { s2158 = b; }
bool s2165() const { return s2158; }
std::vector<s270*>& s599() { return s273; }
const s262* s600() { return past; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override { }
};
typedef s1::s9<s558> s487;
class s588;
class s261;
typedef s588 TD;
class s333;
typedef s588 Transd;
typedef std::vector<s482> s574;
typedef std::vector<s483> s575;
typedef std::vector<s482> s576;
extern s574 s2099;
class s588
: public s271{
public:
enum s560 { s561, s562, s563, s564, s565, s2097, s566 };
protected:
std::wstring s666;
enum s567 { s568, s569, s570, s571 };
s560 s572;
s567 s573;
s480** s577;
s481** s578;
size_t s495, nlocs;
s575 s579;
s574 s273;
std::vector<s483> s973;
std::vector<s480*> s580;
s576 s581;
std::vector<std::vector<s481*>> s582;
s483 s583;
s484 s585;
s485 s584;
const s262* past;
s2154 s1639;
s482 subject;
const bool intro;
const bool s2158;
int s2219;
void s840( s270* par, size_t pos, s482& s152, const s271* s1657,
bool proc );
void s586( s1889& s331);
void s587( s1889& s331);
s480* s1598( s480** s698, size_t s495 );
virtual void s1895( const s574& pl ) const;
public:
s588( s261* s299, s271* s589, s588* s590, s271* ns_, s560 ct,
s1889& s671, const s262* s694, bool s1712 = false, bool _bd = true );
s588( s261* s299, s271* s585, s588* s584, s271* ns_, s560 ct,
const std::vector<s270*>& l, const s262* s694, bool s1712, bool _bd );
s588( const s588& right, s271* s585, s588* s584, s271* ns_, 
const std::vector<s270*>& s273, const s262* s694, bool s2104=false, 
bool _bd=true );
virtual ~s588();
s560 s857() const { return s572; }
void s591( s567 vt ) { s573 = vt; }
s567 s592() const { return s573; }
const std::wstring& s350() const override { return s270::s350(); }
std::wstring s827() const override;
std::wstring s297() const override;
std::wstring s2153() const override;
bool s2165() const { return s2158; }
bool s2284() const { return ( s2219 == -1 ); }
const s262* s600() const { return past; }
s480* s493() override { return s583; }
void s2171( s368* ref );
virtual s482 s2283();
void s497( const s271* s1657, bool proc ) override;
virtual void s593( const std::vector<s482>& l );
typedef std::vector<std::pair<std::wstring, s483>> s828;
void s807( s828& s152 ) const;
void s594( const s271* s1657 );
void s2113( s574& s2112 );
void s2117( s588* s2041, s271* impl, bool s2158 = true ) override;
bool s553( s1889& s277, s368* ref, s1889& s331, bool ) const override;
s270* s595( size_t off ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
static s588* s596( const s262& s694, s261* s299, s271* obj,
s1889& s277, s1889& s555 );
static s558* s1109( const s262& s694, s261* s299, s271* obj,
s1889& s555, bool s2158 );
static s588* s597( s558* cs, s261* s299, s271* s585, s588* s214,
s1889& s555, bool proc );
static void s1231( std::vector<s270*>& s273, const std::vector<std::wstring>& s1198 );
static void s1231( std::vector<s482>& s273, const std::vector<std::wstring>& s1198 );
void s303( std::wostream* pd, int s196 = 0 ) const override;
std::wstring trace( s1889& topics ) const override;
};
class s834
: public s588{
s613 s559;
bool s1960;
public:
s834( s261* s299, s588* s584, s271* ns, s560 ct, const std::vector<s270*>& l,
s1053 s490, s1889& s1540, const s262* s694, bool _bd = false );
s834( const s834& right, s588* s584, s271* ns );
virtual ~s834();
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
bool s553( s1889& s277, s368* ref,	s1889& s331, bool ) const override;
s270* s332( s588* s2041, s271* impl ) const override;
bool s1193() const override { return s1960; }
};
class s835
: public s588{
public:
s835( s261* s299, s271* s585, s588* s584, s271* ns, s560 ct,
const std::vector<s270*>& l, const s262* s694, bool s2158 = false );
s835( const s835& right, s588* s584, const std::vector<s270*>& s273,
s560 ct, const s262* s694, s271* s585 = NULL, s271* ns = NULL, bool intro = true, bool _bd = false );
virtual ~s835();
s482 s2283() override;
void s1663( s271* s589 ) { s585 = s589; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s2258( const std::vector<s482>& l );
void s2245( );
};
class s1346
: public s835{
public:
s1346( s261* s299, s271* s585, s588* s584, const s262* s694 );
s1346( const s1346& right, s271* s585, s588* s584, const std::vector<s270*>& s273,
const s262* s694 );
virtual ~s1346();
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
namespace s1500 {
extern s1053 s1493;
extern s1053 s1497;
extern s1053 s1492;}
typedef std::basic_istream<wchar_t> s1485;
typedef std::basic_ostream<wchar_t> s1488;
typedef std::basic_istringstream<wchar_t> s1955;
typedef std::basic_ostringstream<wchar_t> s1956;
class Stream
: public s333{
public:
typedef std::ios_base::fmtflags s1908;
typedef std::streamsize s1909;
Stream( s261* s299, s271* ns, const s262* s207 = NULL )
: s333( s299, ns, s207 ) {}
virtual void s1449( std::wstring& s152, size_t s1460 );
virtual void s1468( const std::wstring& src );
virtual void s1450( std::wstring& s152, const std::wstring& s72 = L"\n" );
virtual void s1469( const std::wstring& src );
virtual void s1448( s1311& s152, size_t s1460 );
virtual void s1467( const s1311& src );
virtual void s1447( s1311& s152, const s1311& s72 = s1311( {'\n'} ) );
virtual void s1466( const s1311& src );
virtual void rewind();
virtual void s1913()=0;
virtual void s1911()=0;
virtual void s2050()=0;
virtual void s2049()=0;
virtual void s1941()=0;
virtual void s1942()=0;
virtual void s1555( int n )=0;
virtual void s1912( int n )=0;
virtual void s1897( wchar_t c );
virtual void s1899()=0;
virtual void s1900()=0;
virtual void s1898()=0;
virtual void s1910()=0;
virtual void s1553()=0;
virtual void s1554()=0;
virtual s1908 s1914() const = 0;
virtual s1909 s1915() const = 0;
virtual bool s2051() const = 0;
virtual void s1935()=0;
virtual void s1937()=0;
virtual void s1940( int n )=0;
virtual void s1938( int n )=0;
virtual void s1936()=0;
virtual void s1939()=0;
virtual s1908 s1945() const = 0;
virtual s1909 s1946() const = 0;
virtual void ws() { throw new s2::s16( L"ws not implemented" ); }
virtual s1485& s1947() { throw new s2::s16( L"iwstream not implemented" ); }
virtual s1488& s1948() { throw new s2::s16( L"owstream not implemented" ); }
};
template<class s1408, class s1410>
class s1394
: public Stream{
protected:
typedef s1394<s1408, s1410> s1157;
typedef s333::s338 s338;
s1408 *s1462;
s1410 *s1463;
bool s2057;
static s338 s345;
void s347() override;
const s338& s339() const override { return s345; }
static void s1475( s480** s273, size_t n );
public:
s1394( s261* s299, s271* ns, const s262* s207 = NULL )
: Stream( s299, ns, s207 ), s2057( false ) {}
s1394(): s2057( false ){}
virtual ~s1394() {}
void s1913() override;
void s1911() override;
void s2050() override;
void s2049() override;
void s1941() override;
void s1942() override;
void s1555( int n ) override;
void s1912( int n ) override;
void s1899() override;
void s1900() override;
void s1898() override;
void s1910() override;
void s1553() override;
void s1554() override;
s1908 s1914() const override;
s1909 s1915() const override;
bool s2051() const override;
void s1935() override;
void s1937() override;
void s1940( int n ) override;
void s1938( int n ) override;
void s1936() override;
void s1939() override;
s1908 s1945() const override;
s1909 s1946() const override;
};
template<class s1408, class s1410>
s333::s338 s1394<s1408, s1410>::s345;
template<class s1408, class s1410>
void s1394<s1408, s1410>::s347(){
s345.insert( std::make_pair( L"rewind", new s334( L"rewind", &s1394<s1408,s1410>::s1475, s1142,
{ s1112() }, 0, 0 ) ) );}
template<class s1408, class s1410>
void s1394<s1408, s1410>::s1475( s480** s273, size_t s495 ){
s1157* s1054 = (s1157*)s273[1];
if( s1054->s1462 ) {
if( s1054->s1462->eof() )
s1054->s1462->clear( s1054->s1462->rdstate() &
( s1054->s1462->rdstate() ^ std::ios_base::eofbit ) );
if( !s1054->s1462->good() )
throw new s2::s16( L"file handle is not valid" );
s1054->s1462->seekg( 0 );
s1054->s1462->clear();}
if( s1054->s1463 )
s1054->s1463->seekp( 0 );}
class s504
: public s1394<s1955,s1956>{
protected:
typedef s504 s1157;
static s338 s345;
std::basic_stringstream<wchar_t> ss;
static void s505( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
public:
s504( const s504&, const s262* ast_ = NULL );
s504( s261* s299, s271* ns_ = NULL, const s262* ast_ = NULL );
~s504(){}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s872, bool ) override;
void release() override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void* addr() override { return (void*)&ss; }
s1485& s1947() override { return *s1462; }
s1488& s1948() override { return *s1463; }
void s1449( std::wstring& s152, size_t s1460 ) override;
void s1468( s1889& src ) override;
void s1450( std::wstring& s152, s1889& s72 = L"\n") override;
void s1469( s1889& src ) override;
void s1448( s1311& s152, size_t s1460 ) override;
void s1467( const s1311& src ) override;
void s1447( s1311& s152, const s1311& s72 = s1311( { '\0' } ) ) override;
void s1466( const s1311& src ) override;
void s1897( wchar_t c ) override;
virtual void ws() override { *s1462 >> std::ws; }
virtual std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef std::basic_istringstream<tdbyte_t> s1483;
typedef std::basic_ostringstream<tdbyte_t> s1486;
class s1283
: public s1394<s1483,s1486>{
protected:
typedef s1283 s1157;
static s338 s345;
std::basic_stringstream<tdbyte_t> bs;
static void s1304( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
public:
s1283( const s1283&, const s262* ast_ = NULL );
s1283( s261* s299, s271* ns_ = NULL, const s262* ast_ = NULL );
~s1283(){}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s872, bool ) override;
void release() override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void* addr() override { return (void*)&bs; }
void s1449( std::wstring& s152, size_t s1460 ) override;
void s1468( s1889& src ) override;
void s1450( std::wstring& s152, s1889& s72 = L"\n" ) override;
void s1469( s1889& src ) override;
void s1448( s1311& s152, size_t s1460 ) override;
void s1467( const s1311& src ) override;
void s1447( s1311& s152, const s1311& s72 = s1311( { '\0' } ) ) override;
void s1466( const s1311& src ) override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef std::basic_ifstream<tdbyte_t> s1484;
typedef std::basic_ofstream<tdbyte_t> s1487;
class s1291
: public s1394<s1484,s1487>{
protected:
typedef s1291 s1157;
static s338 s345;
s482 s209;
s482 mode;
std::wstring s1330;
typedef std::basic_fstream<tdbyte_t> s1482;
std::fstream fs;
static void s1226( s480** s273, size_t n );
static void s2012( s480** s273, size_t n );
static void s2014( s480** s273, size_t n );
static void s2013( s480** s273, size_t n );
static void s1313( s480** s273, size_t n );
static void s406( s480** s273, size_t n );
static void s2020( s480** s273, size_t n );
static void s1472( s480** s273, size_t n );
static void s1344( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
static void s1990( s480** s273, size_t s495, std::wstring& s1334 );
void _open( const std::wstring& s1334 );
void _close();
public:
s1291( const s1291&, const s262* ast_ = NULL );
s1291( s261* s299, s271* ns_ = NULL, const s262* ast_ = NULL );
s1291( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL );
~s1291(){}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s872, bool ) override;
void release() override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void* addr() override { return (void*)&fs; }
void s1449( std::wstring& s152, size_t s1460 ) override;
void s1468( s1889& src ) override;
void s1450( std::wstring& s152, s1889& s72 = L"\n" ) override;
void s1469( s1889& src ) override;
void s1448( s1311& s152, size_t s1460 ) override;
void s1467( const s1311& src ) override;
void s1447( s1311& s152, const s1311& s72 = s1311( { '\0' } ) ) override;
void s1466( const s1311& src ) override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1390
: public s1394<std::wistream, std::wostream>{
static s338 s345;
static void s324( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
s1390( const s504&, const s262* ast_ = NULL );
s1390( s261* s299, s271* ns_, const s262* ast_ = NULL );
~s1390(){}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void* addr() override { return NULL/*(void*)&std::wcin*/; }
void s1449( std::wstring& s152, size_t s1460 ) override;
void s1468( s1889& src ) override;
void s1450( std::wstring& s152, s1889& s72 ) override;
void s1469( s1889& src ) override;
void s1448( s1311& s152, size_t s1460 ) override;
void s1467( const s1311& src ) override;
void s1447( s1311& s152, const s1311& s72 ) override;
void s1466( const s1311& src ) override;
virtual std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1392
: public s1394<std::wistream, std::wostream>{
static s338 s345;
static void s505( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
s1392( const s504&, const s262* ast_ = NULL );
s1392( s261* s299, s271* ns_, const s262* ast_ = NULL );
~s1392(){}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void* addr() override { return NULL; }
s1488& s1948() override { return *s1463; }
void s1449( std::wstring& s152, size_t s1460 ) override;
void s1468( s1889& src ) override;
void s1450( std::wstring& s152, s1889& s72 ) override;
void s1469( s1889& src ) override;
void s1448( s1311& s152, size_t s1460 ) override;
void s1467( const s1311& src ) override;
void s1447( s1311& s152, const s1311& s72 ) override;
void s1466( const s1311& src ) override;
void s1897( wchar_t c ) override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
extern s1::s9<s1390> s1391;
extern s1::s9<s1392> s1393;
class s261;
class s382;
class Iterator{
public:
virtual ~Iterator() {}
virtual s270* s312() = 0;
virtual s270* s954() = 0;
virtual const s270* s954() const = 0;
virtual s270* Idx() = 0;
virtual s270* El() = 0;
virtual s1053 s316() const { return ValType(); };
virtual s1053 ValType() const = 0;
virtual bool s1963() const = 0;
virtual bool operator==( const Iterator* r ) const { return this == r; }
virtual bool operator<( const Iterator* r ) const { return this < r; }
};
typedef std::pair<s1::s1278<Iterator>, s1::s1278<Iterator>> s1134;
struct s833;
class s382;
class s323
: public s333{
protected:
s1053 s314;
s1053 s1190;
s1053 s322;
virtual s480* s1180( Iterator* it );
public:
s323( s261* s299, s271* ns_, const s262* ast_ )
: s333( s299, ns_, ast_ ), s314( 0 ), s1190( 0 ), s322( 0 ) {}
s323( const s323& r )
: s333( r ), s314( r.s314 ), s1190( r.s1190 ), s322( r.s322 ) {}
virtual ~s323() {}
virtual size_t s1128() const { return 0; }
virtual Iterator* s311( s382* r, bool s2295 = false ) = 0;
virtual s1053 s316() const { return s314; }
virtual s1053 s930() const { return s1190; }
virtual s1053 ValType() const { return s322; }
virtual Iterator* s1175() = 0;
virtual Iterator* s1179() = 0;
virtual s1134 s1184() = 0;
virtual Iterator* s1154( const s480* idx );
virtual Iterator* s1173( const s480* s346 );
virtual Iterator* s1228( const s480* s346 );
virtual s480* sort( bool reverse, s833* cmp );
};
class s382
: public s323,
public Iterator{
s482 s585;
s1::s9<s323> s977;
s1::s1278<Iterator> s1454;
s482 s1232, s1233;
s483 s1530, s1531;
bool s970, s971;
Iterator* s315;
uint64_t s980, s1534;
int incr;
s1::s9<s1517> s1165;
static s338 s345;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
public:
enum s1131 { s1217, s1224, s1216, s1223, s1225, s1212, s1218 };
s382( s261* s299 );
s382( s261* s299, s323* s585, Iterator* it );
s382( uint64_t b, uint64_t e = U64_MAX );
s382( s261* s299, s1889& s77, const s262* ast_ = NULL );
s382( const s382& right, const s262* ast_ = NULL );
s382( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
~s382();
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s1132 s1187( s1889& s340 ) const override;
s1132 s1182( s1889& s340, s1112& ap ) const override;
s1132 s1177( s1889& s340,	s1112& ap ) override;
s1053 s1178( s1889& s1540,	const std::vector<s482>& l ) const override;
const std::vector<std::wstring>& s1181( s1889& s340 ) const override;
size_t s1128() const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)s315; }
void s497( const s271* s872, bool fr=true ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override { return NULL; }
Iterator* s1179() override { return NULL; }
s1134 s1184() override;
s1134 s1184( s323* s585 );
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s1053 ValType() const override { return s322; }
bool s1963() const override;
s323* s812() { return s977.s14() ? s977.s15<s323*>() : (s323*)this; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1124
: public s323,
public Iterator{
s482 s585;
s483 s977;
s1::s9<s382> range;
s482 where, s1062;
s1::s1278<Iterator> s315, s1477;
s1::s9<s368> s979; // @it - for using in s1192 scope lambdas
s270* s980;
static s338 s345;
s1::s9<s343> s346, s680;
std::wstring s496;
s1053 s1342;
static void s1226( s480** s273, size_t n );
static void s1337( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
enum s1131 { s1217, s1224, s1216, s1223, s1225, s1321, s1218 };
s1124( s261* s299 ) : s323( s299, NULL, NULL ), s979( new s368( s7::s1362, s299, s472 ) ), 
s980(NULL) {}
s1124( s261* s299, s1889& s77, const s262* ast_ = NULL );
s1124( const s1124& r, const s262* ast_ = NULL );
s1124( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s1053 s316() const override { return s680->s349(); }
size_t s1128() const override { return s977.s15<s323*>()->s1128(); }
s1132 s1182( s1889& s340,	s1112& ap ) const override;
s1132 s1177( s1889& s340, s1112& ap ) override;
s1053 s1178( s1889& s1540,	const std::vector<s482>& l ) const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 ValType() const override { return s322; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
bool s553( s1889& s277, s368* s152, s1889& s331,	bool ) const override;
s270* s595( size_t off ) override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
bool s1963() const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
Iterator* s1175() override { return NULL; }
Iterator* s1179() override { return NULL; }
s1134 s1184() override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s943
: public s323,
public Iterator{
s485 s1050;
s485 set;
s485 eq;
s482 start;
s482 end;
s482 incr;
s482 s981;
s482 s1644;
bool s1039;
std::wstring s496;
static s338 s345;
static void s1226( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
enum s1131 { s1217, s1224, s1216, s1223, s1225, s1212, s1218 };
s943( s261* s299 );
s943( s261* s299, s1889& s77, const s262* ast_ = NULL );
s943( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
virtual ~s943();
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s1053 ValType() const override { return s322; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override {}
size_t s319() const override { return 0; }
bool operator==( const s480* p ) const override { return false; }
bool operator<( const s480* p ) const override { return false; }
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
bool s1963() const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
s270* s312() override;
s270* s954() override { return NULL; }
const s270* s954() const override { return NULL; }
s270* Idx() override;
s270* El() override { return NULL; }
s1053 s316() const override { return s322; }
Iterator* s1175() override { return NULL; }
Iterator* s1179() override { return NULL; }
void* addr() override { return NULL; }
s1134 s1184() override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef int HPROG;
typedef std::vector<s482> s2238;
enum s1358{ s1417=1, s1418, s1419, s1420, s1609, 
s1421, s1422, s2194, s2063, s1423, s1424, s1427, 
s1425, s1426, s1610, s1428, s1931, s1611, 
s1429, s2215, s1430, s1613, s1614, s1431,
s1871, s1612,	s1932, s1930, s1432,
s1550, s1433, s1434, s1435, s1615,
s1436,	s1437, s1438 };
extern std::map<std::wstring, int> s1359;
extern std::vector<int> BIFuncs1v;
extern std::vector<std::wstring> s1360;
struct s715{
std::vector<std::wstring> s660;
std::wstring entry;
s1983 restrictions[s1968];
s715() {
memset( &restrictions, 0, s1968 * sizeof(s1983) );}
};
class s1971{
s1983 s2025[s1968];
static std::vector<std::wstring> s2033;
s1983 s1987( const std::wstring& s2023 );
public:
s1971();
void s2040( const s6::s142& s132 );
void reset();
void s1997( const std::vector<s1982>* s2018, s1983 sw ) const;
bool s1996( s1982 si, s1983 sw ) const;
};
class s558;
class s261
: public s271{
private:
std::vector<std::wstring> s198;
s262 s694;
std::wstring s199;
std::wstring s760;
std::wstring s1882;
s1971 s2024;
void s201( s1889& s654, s715& s152 );
void s212( s1889& s193, const s6::s142& obj );
void s2157( const s6::s142& obj );
s488 s202;
s479 s203;
typedef std::map<std::wstring, s480*> s204;
s204 s205;
bool s1308;
std::map<const s480*, s2238*> s2254;
public:
s261();
~s261();
s1889& s709() const { return s760; }
void s1874( s1889& s ) { s760 = s; }
s1889& s1877() const { return s1882; }
void s1875( s1889& s ) { s1882 = s; }
virtual std::wstring s827() const override { return L"::"; }
virtual std::wstring s297() const override { return L"::"; }
void s1884( bool soft = false );
void reset();
void s206( s262& s207 );
void s208( s1889& s209, bool s1886 = false );
void s210( s6::s142& obj );
void s211( s1889& s209 );
s480* run( const std::vector<std::wstring>& s686 );
s480* callFunc( s1889& s598, std::vector<std::wstring>& l );
s485 getProc( s1889& s598 );
bool s1319() const { return s1308; }
void s1637( s1889& s666 );
void s1997( const std::vector<s1982>* s2018, s1983 sw ) const;
bool s1996( s1982 si, s1983 sw ) const;
s488& TR() { return s202; }
s588* s213( int s1445, s558* cs,
s271* s585, s588* s214 );
void s216( s1889& s );
s1053 s217( s480* p, s1889& s344 );
void s218( s1889& s346, s1889& s331, std::vector<std::wstring>& s152 );
virtual bool s553( s1889& s277, s368* s152,	s1889& s331, bool ) const override;
s483 s219( s1889& s346, s1889& s331 );
bool s220( s368& rf ) const;
s270* s221( s1889& sym, s1889& s496, bool s517 = true );
void* s222( s1889& s277 );
void s1340( s1889& s666 );
void s1650( s1889& s1620 );
void s2242( const s480* s151, s2238* s2253 );
s2238* s2248( const s480* s151 );
void s2247( const s480* old, const s480* nw );
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef s1::s9<s261> s714;
namespace s1500 {
extern s1053 s1495;
extern s1053 s1494;
extern s1053 s1496;}
class Iterator;
struct s833;
class s1133;
struct s318{
std::size_t operator()( const s483 k ) const{
return k->s319();}
std::size_t operator()( const s482 k ) const{
return k.s15<s480*>()->s319();}
};
struct s320{
bool operator()( const s483 l, const s483 r ) const{
return l->operator==( ( s480* )&( *r ) );}
bool operator()( const s480* l, const s480* r ) const{
return l->operator==( r );}
bool operator()( const s480& l, const s480& r ) const{
return l.operator==( &r );}
bool operator()( const s482 l, const s482 r ) const{
return l.s15<s480*>()->operator==( r.s15<s480*>() );}
};
struct s2291{
bool operator()( const s483 l, const s483 r ) const{
return l->s319() == r->s319();}
bool operator()( const s480* l, const s480* r ) const{
return l->s319() == r->s319();}
bool operator()( const s480& l, const s480& r ) const{
return l.s319() == r.s319();}
bool operator()( const s482 l, const s482 r ) const{
return l.s15<s480*>()->s319() == r.s15<s480*>()->s319();}
};
struct s1413{
bool operator()( const s483 l, const s483 r ) const{
return l->operator<( ( s480* )&( *r ) );}
bool operator()( const s480* l, const s480* r ) const{
return l->operator<( r );}
bool operator()( const s480& l, const s480& r ) const{
return l.operator<( &r );}
bool operator()( const s482 l, const s482 r ) const{
return l.s15<s480*>()->operator<( r.s15<s480*>() );}
};
void s1151( s261* s299, const std::wstring& s77, 
std::wstring& s1262, std::wstring& s641 );
template<class s1300>
struct s1290 {
bool operator()( const s1300& l, const s1300& r ) { return l < r; }
};
template<class s1300>
struct s1561 {
bool operator()( const s1300& l, const s1300& r ) { return l == r; }
};
template<class s1300, class s1568>
struct s1562{
s485 s852;
std::vector<s482>s854;
s1562() : s852( 0 ),
s854( { new s1568( 0,0 ), new s1568( 0,0 ) } ) {}
bool operator()( const s1300& l, const s1300& r ){
*s854[0].template s15<s1568*>()->s354() = l;
*s854[1].template s15<s1568*>()->s354() = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
};
template<>
struct s1290<s482>{
std::vector<s482>s854;
s485 s852;
s1290() : s852( 0 ) { s854.resize( 2 ); }
bool operator()( const s482& l, const s482& r ){
if( s852.s14() ) {
s854[0] = l;
s854[1] = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l.s15<s480*>()->operator<( r.s15<s480*>() );}
};
template<>
struct s1290<s483>{
std::vector<s482>s854;
s485 s852;
s1290() : s852( 0 ) { s854.resize( 2 ); }
bool operator()( const s483& l, const s483& r ){
if( s852.s14() ) {
s854[0] = l.s15<s270*>();
s854[1] = r.s15<s270*>();
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l->operator<( r.s15<s480*>() );}
};
template<>
struct s1290<tdbyte_t>{
s485 s852;
std::vector<s482>s854;
s1290() : s852( 0 ),
s854( { new s1284( 0,0 ), new s1284( 0,0 ) } ) {}
bool operator()( const tdbyte_t& l, const tdbyte_t& r ){
if( s852.s14() ) {
*s854[0].s15<s1284*>()->s354() = l;
*s854[1].s15<s1284*>()->s354() = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l < r; }
};
template<>
struct s1290<wchar_t>{
s485 s852;
std::vector<s482>s854;
s1290() : s852( 0 ),
s854( { new s1560( 0,0 ), new s1560( 0,0 ) } ) {}
bool operator()( const wchar_t& l, const wchar_t& r ){
if( s852.s14() ) {
*s854[0].s15<s1560*>()->s354() = l;
*s854[1].s15<s1560*>()->s354() = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l < r; }
};
template<>
struct s1561<s482> {
bool operator()( const s482& l, const s482& r ) { 
return l.s15<s480*>()->operator==( r.s15<s480*>() );}
};
template<>
struct s1561<s483> {
bool operator()( const s483& l, const s483& r ) { 
return l->operator==( r.s15<s480*>() );}
};
template<>
struct s1562<s482, s482>{
std::vector<s482>s854;
s485 s852;
s1562() : s852( 0 ) { s854.resize( 2 ); }
bool operator()( const s482& l, const s482& r ){
s854[0] = l;
s854[1] = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
};
template<>
struct s1562<s483, s483>{
std::vector<s482>s854;
s485 s852;
s1562() : s852( 0 ) { s854.resize( 2 ); }
bool operator()( const s483& l, const s483& r ){
s854[0] = l.s15<s270*>();
s854[1] = r.s15<s270*>();
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
};
typedef std::wstring s1564;
template<class _Cont, class s1300, class Der>
class s310 :
public s323{
protected:
typedef Der s1157;
_Cont s346;
static s1290<s1300> s1314;
static s1561<s1300> s1571;
typedef s333::s338 s338;
static s338 s345;
static void s325( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s1243( s480** s273, size_t n );
static void s1256( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
s270* s1324( s1300 el ) { return el; }
static std::pair<typename _Cont::iterator, typename _Cont::iterator> s1412( s480* p, Der* pv );
static s1134 s1414( s480* p, Der** pv );
static s1133* s1959( Der** pv, typename _Cont::iterator& s1965 );
public:
typedef s310<_Cont, s1300, Der> s1160;
s310( s261* s299, s271* ns, const s262* ast_ );
s310( const s1160& r );
virtual ~s310(){}
virtual s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
virtual s1134 s1184() override;
};
template<class _Cont, class s1300, class Der>
s333::s338 s310<_Cont, s1300, Der>::s345;
template<class _Cont, class s1300, class Der>
s1290<s1300> s310<_Cont, s1300, Der>::s1314;
template<class _Cont, class s1300, class Der>
s1561<s1300> s310<_Cont, s1300, Der>::s1571;
template<class _Cont, class s1300, class Der, class s1569>
class s1389 :
public s310<_Cont, s1300, Der>{
protected:
typedef s333::s338 s338;
typedef s333::s334 s334;
static s1562<s1300, s1569> s1572;
static void s1570( s480** s273, size_t n );
static void s1573( s480** s273, size_t n );
static void s1622( s480** s273, size_t n );
static void s1608( s480** s273, size_t n );
static void s1201( s480** s273, size_t n );
static void s1200( s480** s273, size_t n );
static void s2074( s480** s273, size_t n );
static void s2073( s480** s273, size_t n );
static void s2072( s480** s273, size_t n );
static void s1243( s480** s273, size_t n );
static void s1256( s480** s273, size_t n );
static void s2304( s480** s273, size_t n );
static void s1580( s480** s273, size_t n );
static void s1574( s480** s273, size_t n );
static void s773( s480** s273, size_t n );
static void s1481( s480** s273, size_t n );
static void s1730( s480** s273, size_t n );
static void s1934( s480** s273, size_t n );
static void s2078( s480** s273, size_t n );
static void s2221( s480** s273, size_t n );
static s338 s345;
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
virtual void s2472() {}
s270* s1324( s1300 el ) { return el; }
public:
typedef s1389<_Cont, s1300, Der, s1569> s1160;
s1389( s261* s299, s271* ns, const s262* ast_ );
s1389( const s1160& r );
virtual ~s1389(){}
virtual s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
};
template<class _Cont, class s1300, class Der, class s1569>
s333::s338 s1389<_Cont, s1300, Der, s1569>::s345;
template<class _Cont, class s1300, class Der, class s1569>
s1562<s1300, s1569> s1389<_Cont, s1300, Der, s1569>::s1572;
template<class _Cont, class s1300, class Der>
class s1563 :
public s1389<_Cont, s1300, Der, s1300>{
protected:
typedef s333::s338 s338;
typedef s333::s334 s334;
static void s1622( s480** s273, size_t n );
static void s1608( s480** s273, size_t n );
static void s1256( s480** s273, size_t n );
static void s2304( s480** s273, size_t n );
static void s773( s480** s273, size_t n );
static void s1452( s480** s273, size_t n );
static void s1957( s480** s273, size_t n );
static void s2221( s480** s273, size_t n );
static s338 s345;
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
public:
typedef s1563<_Cont, s1300, Der> s1160;
s1563( s261* s299, s271* ns, const s262* ast_ );
s1563( const s1160& r );
virtual ~s1563(){}
virtual s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
};
template<class _Cont, class s1300, class Der>
s333::s338 s1563<_Cont, s1300, Der>::s345;
template<class s1300>
struct s1368 {
bool operator()( const s1300& l, const s1300& r ) { return l < r; }
};
template<>
struct s1368<std::pair<s483, s483>>{
typedef std::pair<s483, s483> s1407;
std::vector<s482>s854;
s485 s852;
s1368() : s852( 0 ) { s854.resize( 2 ); }
bool operator()( const s1407& l, const s1407& r ){
if( s852.s14() ) {
s854[0] = l.first.s15<s270*>();
s854[1] = r.first.s15<s270*>();
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
else
return l.first->operator<( r.first.s15<s480*>() );}
};
template<class _Cont, class s1409, class s1411, class Der>
class s1357 :
public s310<_Cont, s1409, Der>{
protected:
typedef s333::s338 s338;
typedef s333::s334 s334;
s1368<std::pair<s1409, s1411>> s1443;
static void s773( s480** s273, size_t n );
static void s1201( s480** s273, size_t n );
static void s2074( s480** s273, size_t n );
static void s2072( s480** s273, size_t n );
static void s1473( s480** s273, size_t n );
static s338 s345;
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
s270* s1324( std::pair<s1409, s1411>& el );
public:
typedef s1357<_Cont, s1409, s1411, Der> s1160;
s1357( s261* s299, s271* ns, const s262* ast_ );
s1357( const s1160& r );
virtual s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
virtual bool insert( s480* s151, s480* s346 );
virtual s480* find( s480* s151 );
};
template<class _Cont, class s1409, class s1411, class Der>
s333::s338 s1357<_Cont, s1409, s1411, Der>::s345;
template <class _Cont, class s1300, class Der>
s310<_Cont, s1300, Der>::s310( s261* s299, s271* ns_, const s262* ast_ )
: s323( s299, ns_, ast_ ){}
template <class _Cont, class s1300, class Der, class s1569>
s1389<_Cont, s1300, Der, s1569>::s1389( s261* s299, s271* ns_, const s262* ast_ )
: s310<_Cont, s1300, Der>( s299, ns_, ast_ ){}
template <class _Cont, class s1300, class Der>
s1563<_Cont, s1300, Der>::s1563( s261* s299, s271* ns_, const s262* ast_ )
: s1389<_Cont, s1300, Der, s1300>( s299, ns_, ast_ ){}
template <class _Cont, class s1409, class s1411, class Der>
s1357<_Cont, s1409, s1411, Der>::s1357( s261* s299, s271* ns_, const s262* ast_ )
: s310<_Cont, s1409, Der>( s299, ns_, ast_ ){}
#define DR ((s481*)*(s273 + 1))
#define PARN(n)((s481*)*(s273 + n))
template<class _Cont, class s1300, class Der>
s1134
s310<_Cont, s1300, Der>::s1414( s480* p, Der** pv ){
s382* pr = NULL;
if( p->s349() == s1403 ) {
pr = (s382*)p;
*pv = (Der*)pr->s812();}
else
*pv = ( (Der*)p );
s1134 rp;
if( pr ) {
rp = pr->s1184( *pv );}
else
rp = (*pv)->s1184();
return rp;}
template<class _Cont, class s1300, class Der>
std::pair<typename _Cont::iterator, typename _Cont::iterator> 
s310<_Cont, s1300, Der>::s1412( s480* p, Der* pv ){
using s1120 = Der;
using s932 = typename Der::s1129;
s382* pr = NULL;
if( p->s349() == s1403 ) {
pr = (s382*)p;
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)p );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
return std::make_pair( s1507, s1508 );}
template<class _Cont, class s1300, class Der>
void s310<_Cont, s1300, Der>::s325( s480** s273, size_t n ){
using s1120 = Der;//s1157;
s1120* pv = ( (s1120*)s273[1] );
*( (s343*)*s273 )->s354() = (int)pv->s346.size();}
template<class _Cont, class s1300, class Der>
void s310<_Cont, s1300, Der>::s327( s480** s273, size_t n ){
using s1120 = Der;//s1157;
s1120* pv = ( (s1120*)s273[1] );
pv->s346.clear();}
template<class _Cont, class s1300, class Der>
s1134 s310<_Cont, s1300, Der>::s1184(){
return std::make_pair( s1175(), s1179() );}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1243( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
if( ((s323*)pv)->s1128() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
std::reverse( s1507, s1508 );
*s273 = pv;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1580( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
if( ((s323*)pv)->s1128() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
std::mt19937 s1641(std::random_device{}());
std::shuffle( s1507, s1508, s1641 );
*s273 = pv;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2078( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
if( ( (s323*)pv )->s1128() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
std::unique( s1507, s1508 );
*s273 = pv;}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1934( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der *pv = NULL, *pv1 = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
s1134 rp1 = s310<_Cont, s1300, Der>::s1414( s273[2], &pv1 );
s1561<s1300> s1954;
typename _Cont::iterator s1507, s1508, vbeg1, vend1;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
vbeg1 = rp1.first.s15<s932*>()->s1135();
vend1 = rp1.second.s15<s932*>()->s1135();
auto s1933 = std::mismatch( s1507, s1508, vbeg1, vend1, s1954 );
if( s1933.first == s1508 )
s273[0] = new s343( pv->s299, (int)std::distance( s1507, s1508 ) );
else {
auto coinc1 = s1933.first;
++coinc1;
s932 it( pv->s299, pv, s1933.first, coinc1 );
s273[0] = pv->s1180( &it );}}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2072( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der *pv = NULL, *pv1 = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
s1134 rp1 = s310<_Cont, s1300, Der>::s1414( s273[2], &pv1 );
s1290<s1300> s2075;
typename _Cont::iterator s1507, s1508, vbeg1, vend1;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
vbeg1 = rp1.first.s15<s932*>()->s1135();
vend1 = rp1.second.s15<s932*>()->s1135();
bool s152 = std::includes( s1507, s1508, vbeg1, vend1, s2075 );
*((s357*)*s273)->s354() = s152;}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1201( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = ( (Der*)s273[1] );
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s1953;
s1953.s852 = s1196;
typename _Cont::iterator s1202 = std::max_element( s1507, s1508, s1953);
*s273 = (s480*)pv->s1959( &pv, s1202 );}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1200( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
if( s1507 == s1508 )
s273[0] = new s343( pv->s299, -1 );
else {
auto s1202 = std::max_element( s1507, s1508, pv->s1314 );
auto me1 = s1202;
++me1;
s932 it( pv->s299, pv, s1202, me1 );
s273[0] = pv->s1180( &it );}}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2074( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = ( (Der*)s273[1] );
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s1953;
s1953.s852 = s1196;
typename _Cont::iterator s1202 = std::min_element( s1507, s1508, s1953);
*s273 = (s480*)pv->s1959( &pv, s1202 );}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2073( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
if( s1507 == s1508 )
s273[0] = new s343( pv->s299, -1 );
else {
auto s2226 = std::min_element( s1507, s1508, pv->s1314 );
auto me1 = s2226;
++me1;
s932 it( pv->s299, pv, s2226, me1 );
s273[0] = pv->s1180( &it );}}
template<class _Cont, class s1409, class s1411, class Der>
void s1357<_Cont, s1409, s1411, Der>::s1201( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1202 = std::max_element( s1507, s1508, pv->s1443 );
auto tmp = std::make_pair( s1202->first, s1202->second );
*s273 = (s480*)pv->s1324( tmp );}
template<class _Cont, class s1409, class s1411, class Der>
void s1357<_Cont, s1409, s1411, Der>::s2074( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1202 = std::min_element( s1507, s1508, pv->s1443 );
auto tmp = std::make_pair( s1202->first, s1202->second );
*s273 = (s480*)pv->s1324( tmp );}
template<class _Cont, class s1409, class s1411, class Der>
void s1357<_Cont, s1409, s1411, Der>::s2072( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120 *pv, *s2076;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s1134 rp;
if( pr )
rp = pr->s1184( pv );
else
rp = pv->s1184();
if( s273[2]->s349() == s1403 ) {
pr = (s382*)s273[2];
s2076 = (s1120*)pr->s812();}
else
s2076 = ( (s1120*)s273[2] );
s1134 s2077;
if( pr )
s2077 = pr->s1184( s2076 );
else
s2077 = s2076->s1184();
typename _Cont::iterator s1507, s1508, s2079, s2080, cur;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
s2079 = s2077.first.s15<s932*>()->s1135();
s2080 = s2077.second.s15<s932*>()->s1135();
cur = s2079;
/*bool s152 = true;
for( ; cur < s2080; ++cur ) {
auto it = pv->s346.find( cur->first );
if( it != pv->s346.end() || it->second != cur->second ) {
s152 = false;
break;}
}*/
bool s152 = std::includes( s1507, s1508, s2079, s2080 );
*((s357*)*s273)->s354() = s152;}
struct s833{
std::vector<s482>s854;
s485 s852;
s833( s485 s853 ) : s852( s853 ) { s854.resize( 2 ); }
virtual bool operator()( const s482 l, const s482 r ){
s854[0] = l;
s854[1] = r;
s852->s593( s854 );
return (bool)*s852->s494( 0, 0 );}
};
class s356;
class s1565;
class s356
: public s1389<s1564, wchar_t, s356, s1560>{
typedef s1564 s1374;
typedef s356 s1157;
static s338 s345;
std::vector<s482> s273;
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1579( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s1674( s480** s273, size_t n );
static void endsWith_impl( s480** s273, size_t n );
static void s2139( s480** s273, size_t n );
static void s385( s480** s273, size_t n );
static void s390( s480** s273, size_t n );
static void s787( s480** s273, size_t n );
static void s1582( s480** s273, size_t n );
static void s2244( s480** s273, size_t n );
static void s2222( s480** s273, size_t n );
static void s2224( s480** s273, size_t n );
static void s883( s480** s273, size_t n );
static void s884( s480** s273, size_t n );
static void s1575( s480** s273, size_t n );
static void search_impl( s480** s273, size_t n );
static void rsearch_impl( s480** s273, size_t n );
static void s2189( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s396( s480** s273, size_t n );
static void s397( s480** s273, size_t n );
static void s398( s480** s273, size_t n );
static void s399( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s410( s480** s273, size_t n );
static void s1950( s480** s273, size_t n );
static void s1949( s480** s273, size_t n );
static void s406( s480** s273, size_t n );
static void s1471( s480** s273, size_t n );
static void s1026( s480** s273, size_t n );
static void s1336( s480** s273, size_t n );
static void s409( s480** s273, size_t n );
static void s1478( s480** s273, size_t n );
static void s2188( s480** s273, size_t n );
static void s2230( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
public:
typedef s1565 s1129;
s356( const s356&, const s262* ast_ = NULL );
s356( s261* s299, s271* s585, const std::vector<s270*>& l, const s262* ast_ = NULL );
s356( s261* s299, s1889& s = std::wstring( L"" ), s271* s585=NULL, const s262* ast_ = NULL );
s356( s261* s299, s1889& s, size_t& pos, const s262* ast_ = NULL );
virtual ~s356();
s480* s351( const s262& s694, s271* s585, 
const std::wstring& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, 
const s262* ast_ ) const override;
size_t s1128() const override { return 2; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
s1560 operator[]( size_t n ) { return s1560( s299, s346[n] ); }
s1053 s316() const override { return s314; }
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
Iterator* s1154( const s480* idx ) override;
Iterator* s1173( const s480* s346 ) override;
s480* s1180( Iterator* it ) override;
s270* s1324( wchar_t el ) { return new s1560( s299, el ); }
s1374* s354() { return &s346; }
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
void* addr() override { return (void*)&s346; }
operator bool() const override { return !s346.empty(); }
operator int() const override;
operator double() const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s1944( s1889& s ) override;
void s1943( Stream* ) override;
s1311 to_bytes() const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef s356 TDString;
class s810
: public s588{
s482 s756, s716;
s482 s801, s794;
size_t s713, nTo;
int s786, s733;
s1::s9<s356> str;
enum s735 { s712, s767, s757, s809 };
public:
enum s1131{ s1216, s1223, s1215, s1219, s1209, s1205 };
s810( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s810( s261* s299 );
s1889& s298() const override { return s752; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s356;
class s313;
class s743;
class s951;
class s1281;
class s321;
class s1370;
class s2203;
class s2236;
typedef std::vector<s482> s1406;
typedef std::vector<s482> s1405;
typedef s1311 s1363;
typedef std::map<s483, s483, s1413> s1375;
typedef std::unordered_map<s483, s483, s318, s2291> s1369;
typedef std::set<s482, s1413> s2202;
typedef std::unordered_set<s482, s318, s320> s2235;
class s1115
: public Iterator{
protected:
bool s877;
public:
s1115() : s877( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s877;  }
};
class s1127
: public s1115{
public:
};
class s956 
: public s1127{
typedef s1406::iterator s932;
typedef s1406::reverse_iterator s1236;
s1::s9<s313> v;
s932 s1204;
s932 s1078;
s1236 s1247;
s1236 s1476;
uint64_t s1203;
s1::s9<s1517> s1163;
s1::s9<s951> s1162;
public:
s956( s956* it );
s956( s261* s299, s313* v_, s932 it, s932 sent );
s956( s261* s299, s313* v_, s1236 it, s1236 sent );
virtual ~s956() {}
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
void reverse() override;
s932 s1135() { return s1204; }
s1236 s1136() { return s1247; }
s1053 ValType() const override;
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s953
: public Iterator{
typedef s1405::iterator s932;
s1::s9<s743> v;
s932 s1204;
s932 s1078;
uint64_t s1203;
s1::s9<s1517> s1163;
public:
s953( s953* it );
s953( s261* s299, s743* v_, s932 it, s932 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s932 s1135() { return s1204; }
s1053 ValType() const override;
};
class s931
: public s1115{
typedef s1375::iterator s932;
typedef s1375::reverse_iterator s1236;
s1::s9<s321> v;
s932 s1204;
s932 s1078;
s1236 s1247;
s1236 s1476;
s482 s1163;
s1::s9<s951> s1162;
public:
s931( s931* it );
s931( s261* s299, s321* v_, s932 it, s932 sent );
s931( s261* s299, s321* v_, s1236 it, s1236 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s932 s1135() { return s1204; }
void reverse() override;
s1053 s316() const override;
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1371
: public Iterator{
typedef s1369::iterator s932;
s1::s9<s1370> v;
s932 s1204;
s932 s1078;
s482 s1163;
s1::s9<s951> s1162;
public:
s1371( s1371* it );
s1371( s261* s299, s1370* v_, s932 it, s932 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s932 s1135() { return s1204; }
s1053 s316() const override;
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s2204
: public s1115{
typedef s2202::iterator s932;
typedef s2202::reverse_iterator s1236;
s1::s9<s2203> v;
s932 s1204;
s932 s1078;
s1236 s1247;
s1236 s1476;
public:
s2204( s2204* it );
s2204( s261* s299, s2203* v_, s932 it, s932 sent );
s2204( s261* s299, s2203* v_, s1236 it, s1236 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s932 s1135() { return s1204; }
s1236 s1136() { return s1247; }
void reverse() override;
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s2237
: public Iterator{
typedef s2235::iterator s932;
s1::s9<s2236> v;
s932 s1204;
s932 s1078;
public:
s2237( s2237* it );
s2237( s261* s299, s2236* v_, s932 it, s932 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
s932 s1135() { return s1204; }
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1565
: public s1127{
typedef s1564::iterator s932;
typedef s1564::reverse_iterator s1236;
s1::s9<s356> v;
s932 s1204;
s932 s1078;
s1236 s1247;
s1236 s1476;
uint64_t s1203;
s1::s9<s1517> s1163;
s1::s9<s951> s1162;
public:
s1565( s1565* it );
s1565( s261* s299, s356* v_, s932 it, s932 sent );
s1565( s261* s299, s356* v_, s1236 it, s1236 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
void reverse() override;
s932 s1135() { return s1204; }
s1236 s1136() { return s1247; }
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1282
: public s1127{
typedef s1363::iterator s932;
typedef s1363::reverse_iterator s1236;
s1::s9<s1281> v;
s932 s1204;
s932 s1078;
s1236 s1247;
s1236 s1476;
uint64_t s1203;
s1::s9<s1517> s1163;
s1::s9<s951> s1162;
public:
s1282( s1282* it );
s1282( s261* s299, s1281* v_, s932 it, s932 sent );
s1282( s261* s299, s1281* v_, s1236 it, s1236 sent );
bool s1963() const override;
s270* s312() override;
s270* s954() override;
const s270* s954() const override;
s270* Idx() override;
s270* El() override;
void reverse() override;
s932 s1135() { return s1204; }
s1236 s1136() { return s1247; }
s1053 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1133
: public s333{
s482 s585;
s1::s1278<Iterator> s346;
s1053 s314;
s1053 s322;
static s338 s345;
void s347() override;
const s338& s339() const override { return s345; }
static void s395( s480** s273, size_t n );
static void s1964( s480** s273, size_t n );
static void s1576( s480** s273, size_t n );
static void s2249( s480** s273, size_t n );
static void s1731( s480** s273, size_t n );
static void s400( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
public:
s1133( s261* s299 ) : s333( s299, NULL, NULL ), s322(0) {}
s1133( s261* s299, s1889& s77, const s262* ast_ = NULL );
s1133( const s1133& right, const s262* ast_ = NULL );
s1133( s261* s299, s271* context, Iterator* it, const s262* ast_ = NULL );
virtual ~s1133() {}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
void s497( const s271* s872, bool ) override;
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
s1053 s316() const { return s314;  }
s1053 ValType() const { return s322;  }
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
void operator=( const s1133& p );
bool operator==( const s480* p )  const override;
bool operator<( const s480* p )  const override;
operator bool() const override;
void* addr() override { return (void*)&s346; }
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s956;
class s1282;
class s313
: public s1563<s1406, s482, s313>{
s313( const s313& right ) :s1563( 0, 0, 0 ) {
throw; }
protected:
typedef s1406 s1374;
typedef s313 s1157;
static s338 s345;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1253( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1303( s480** s273, size_t n );
static void s385( s480** s273, size_t n );
static void s390( s480** s273, size_t n );
static void s387( s480** s273, size_t n );
static void s330( s480** s273, size_t n );
static void s795( s480** s273, size_t n );
static void s326( s480** s273, size_t n );
static void s1873( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s1730( s480** s273, size_t n );
void s961( s1889& s817, const s1705& tbfr, s271* s585, const s262* ast_	 );
void s347() override;
const s338& s339() const override { return s345; }
void s1150( s1889& s77, s271* s585, const s6::s1680& s1744 );
void s1302( const std::vector<s270*>& v, s271* s585 );
public:
enum s1131 { s1740, s1738, s1736, s1734, s1735, s1737,
s1827 };
typedef s956 s1129;
s313( s261* s299 ) : s1563( s299, NULL, NULL ) {}
s313( s261* s299, s271* s585, const std::wstring& s77, const s262* ast_ = NULL,
const s6::s1680& s1744 = s1721 );
s313( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL, s1053 s702 = 0, s1053 s1265 = 0 );
s313( const s313& right, s271* ns, const s262* ast_ );
s313( s261* s299, s1053 s322, s271* s585, const s262* ast_ = NULL );
virtual ~s313() override;
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
static bool s2210( s323* s1160, s1053 s2217, s1053& pt, s1053& vt, 
std::wstring& sv, const s262& s694, s271* s585, s1889& s331 );
static s1053 s1185( s270* s1160, s1889& s1262, s1053 s2217, s806::Cont& s585 );
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
size_t s1128() const override { return 2; }
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
static void load( s270* s1160, s1053 s2217, s1889& s77, s271* s585, const s6::s1680& s1744,
s1053& pt, s1053& vt, const std::function<void( s483 )> );
void s497( const s271* s872, bool fr=true ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
s480* s1524( const s480* p ) const override;
s483 s494( s480** s273, size_t s495 ) override;
void s2472() override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
s482 operator[]( size_t n ) { return s346[n]; }
const s482& operator[]( size_t n ) const { return s346[n]; }
s1053 s316() const override { return s314; }
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
Iterator* s1154( const s480* idx ) override;
Iterator* s1173( const s480* s346 ) override;
s480* s1180( Iterator* it ) override;
void clear() { s346.clear(); }
void add( s481* el );
void erase( size_t n ) { s346.erase( begin( s346 ) + n ); }
size_t size() const { return s346.size(); }
s480* sort( bool reverse, s833* cmp ) override;
std::vector<s482>& s317() { return s346; }
const std::vector<s482>& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s743
: public s323{
protected:
typedef s1405 s1374;
static s338 s345;
s1374 s346;
s1374::iterator s315;
std::wstring s496;
static void s384( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1303( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s326( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s328( s480** s273, size_t n );
static void s994( s480** s273, size_t n );
static void s1067( s480** s273, size_t n );
static void s1730( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
void s1150( s1889& s77, std::wstring& s1262, std::wstring& s641,
std::vector<s1::s9<s6::s140>>& s93, const s262* ast_, 
const s6::s1680& s1744 );
public:
s743( s261* s299 )
: s323( s299, NULL, NULL ) {}
s743( s261* s299, s271* s585, const s262* ast_ )
: s323( s299, s585, ast_ ) {}
s743( s261* s299, s271* s585, const std::wstring& s77,
const s262* ast_ = NULL, const s1705& tbfr=s1723 );
s743( s261* s299, const std::vector<s270*>& l, const s262* ast_ = NULL );
s743( const s743& right );
virtual ~s743() override;
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s1053 s316() const override;
s1053 s930() const override { return Types.Int; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
size_t s1128() const override { return 2; }
s483 s494( s480** s273, size_t s495 ) override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
s482 operator[]( size_t n ) { return s346[n]; }
const s482& operator[]( size_t n ) const { return s346[n]; }
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
s1134 s1184() override;
void clear() { s346.clear(); }
void add( s482 el ) { s346.push_back( el ); }
void assign( const std::vector<s482>& v );
size_t size() const { return s346.size(); }
std::vector<s482>& s317() { return s346; }
const std::vector<s482>& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s951
: public s743{
static s338 s345;
void s347() override;
const s338& s339() const override { return s345; }
void s1150( s1889& s77, s271* s585, const s6::s1680& s1744 );
virtual void s1148( s1889& s1262 );
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1254( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1303( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s326( s480** s273, size_t n );
static void s327( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s328( s480** s273, size_t n );
static void s994( s480** s273, size_t n );
static void s1067( s480** s273, size_t n );
public:
s951( s261* s299 ) : s743( s299 ) {}
s951( s261* s299, s271* s585, s1889& s77, const s262* ast_ = NULL,
const s6::s1680& s1744 = s1721 );
s951( s261* s299, s271* s585, const std::vector<s270*>& l, 
const s262* ast_ = NULL, s1053 s702 = 0 );
s951( const s951& right, const s262* ast_ = NULL );
virtual ~s951() override {}
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
void s497( const s271* s872, bool fr=true ) override;
s1053 s1185( s1889& s1262, s806::Cont& s585 );
void load( s1889& s77, s271* s585, const s6::s1680& s1744 );
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
bool operator<( const s480* p ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
static bool s2161( s1889& s );
};
class s1281
: public s1389<s1363, tdbyte_t, s1281, s1284>{
protected:
typedef s1363 s1374;
typedef s1281 s1157;
static s338 s345;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1253( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1303( s480** s273, size_t n );
static void s326( s480** s273, size_t n );
static void s395( s480** s273, size_t n );
static void s1327( s480** s273, size_t n );
static void s1343( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
void s1150( s1889& s77,
s480* s585, const s6::s1680& s1744 );
public:
typedef s1282 s1129;
s1281( s261* s299 ) : s1389( s299, NULL, NULL ) {}
s1281( s261* s299, s271* s585, const std::wstring& s77, const s262* ast_ = NULL,
const s6::s1680& s1744=s1721 );
s1281( s261* s299, const std::vector<s270*>& l, const s262* ast_ = NULL );
s1281( const s1281& right, const s262* ast_ = NULL );
virtual ~s1281() override;
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
size_t s1128() const override { return 2; }
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
void load( s1889& s77, s480* s585, const s6::s1680& s1744 );
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
tdbyte_t operator[]( size_t n ) { return s346[n]; }
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
Iterator* s1154( const s480* idx ) override;
Iterator* s1173( const s480* s346 ) override;
s270* s1324( tdbyte_t el ) { return new s1284( s299, el ); }
s480* s1180( Iterator* it ) override;
void clear() { s346.clear(); }
void add( tdbyte_t el ) { s346.push_back( el ); }
void erase( size_t n ) { s346.erase( begin( s346 ) + n ); }
size_t size() const { return s346.size(); }
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s2203;
class s2203
: public s1563<s2202, s482, s2203>{
protected:
typedef s2202 s1374;
typedef s2203 s1157;
static s338 s345;
s1374::iterator s315;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s2227( s480** s273, size_t n );
static void s329( s480** s273, size_t n );
static void s773( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
void s1150( s1889& s77, s271* s585, const s6::s1680& s1744 );
void s1302( const std::vector<s270*>& v, s480* s585 );
public:
typedef s2204 s1129;
s2203( s261* s299 ) : s1563( s299, NULL, NULL ) { }
s2203( s261* s299, s271* s585, s1889& s77, const s262* ast_ = NULL,
const s6::s1680& s1744 = s1721 );
s2203( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL, s1053 s702 = 0, s1053 s1265 = 0 );
s2203( const s2203& right, s271* ns, const s262* ast_ );
s2203( s261* s299, s1053 s322, s271* s585, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s480* s1524( const s480* p ) const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
size_t s1128() const override { return 1; }
void s497( const s271* s872, bool fr = true ) override;
void load( s1889& s77, s271* s585, const s6::s1680& s1744 );
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s2236;
class s2236
: public s1563<s2235, s482, s2236>{
protected:
typedef s2235 s1374;
typedef s2236 s1157;
static s338 s345;
s1374::iterator s315;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s2227( s480** s273, size_t n );
static void s329( s480** s273, size_t n );
static void s773( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
void s1302( const std::vector<s270*>& v, s480* s585 );
public:
typedef s2237 s1129;
s2236( s261* s299 ) : s1563( s299, NULL, NULL ) { }
s2236( s261* s299, s271* s585, s1889& s77, const s262* ast_ = NULL,
const s6::s1680& s1744 = s1721 );
s2236( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL, s1053 s702 = 0, s1053 s1265 = 0 );
s2236( const s2236& right, s271* ns, const s262* ast_ );
s2236( s261* s299, s1053 s322, s271* s585, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s480* s1524( const s480* p ) const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
size_t s1128() const override { return 1; }
void s497( const s271* s872, bool fr = true ) override;
void load( s1889& s77, s271* s585, const s6::s1680& s1744 );
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef s313 TDVector;
class s321;
class s321
: public s1357<s1375, s483, s483, s321>{
protected:
typedef s1375 s1374;
typedef s321 s1157;
static s338 s345;
s1374::iterator s315;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s1617( s480** s273, size_t n );
static void s329( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1451( s480** s273, size_t n );
static void s2294( s480** s273, size_t n );
static void s2198( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1579( s480** s273, size_t n );
static void s330( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s328( s480** s273, size_t n );
virtual void s347() override;
virtual const s338& s339() const override { return s345; }
virtual void s1150( const std::wstring& s77, std::wstring& s1262, std::wstring& s641,
std::vector<std::pair<std::wstring, s6::s141>> s143, const s262* ast_ );
void s1302( const std::vector<s270*>& v, s480* s585 );
public:
typedef s931 s1129;
s321( s261* s299 ) : s1357( s299, NULL, NULL ) {}
s321( s261* s299, s1053 s1191, s1053 s1265, s1053 s1171,
s1053 s702, s271* s585, const s262* ast_ = NULL );
s321( const s321& right, const s262* ast_ = NULL );
s321( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL, s1053 s702 = 0, s1053 s1171 = 0,
s1053 s1625 = 0, s1053 s1265 = 0);
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
static bool s2210( s323* s1160, s1053 s2217, s1053& pt, s1053& et, s1053& vt, 
s1053& kt, std::wstring& sv, const s262& s694, s271* s585, s1889& s331 );
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
static s1053 s1185( s270* s1160, s1889& s1262, s1053 s2217, s806::Cont& s585,
s1053& et, s1053& kt, s1053& vt );
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
size_t s1128() const override { return 1; }
void s497( const s271* s872, bool fr=true ) override;
static void s2208( s270* s1160, s1889& s77, s271* s585, s1053& kt, s1053& vt, 
const std::function<void( std::pair<s483, s483> )> );
static void load( s270* s1160, s1889& s77, s271* s585, s1889& s72, s1053& kt, s1053& vt, 
const std::function<void( std::pair<s483, s483> )> );
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
static void s2212( s270* subj, Stream*, Iterator* );
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1370;
class s1370
: public s1357<s1369, s483, s483, s1370>{
protected:
typedef s1369 s1374;
typedef s1370 s1157;
static s338 s345;
s1374::iterator s315;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s329( s480** s273, size_t n );
static void s773( s480** s273, size_t n );
static void s324( s480** s273, size_t n );
static void s1451( s480** s273, size_t n );
static void s384( s480** s273, size_t n );
static void s1579( s480** s273, size_t n );
static void s330( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s328( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
virtual void s1150( const std::wstring& s77, std::wstring& s1262, std::wstring& s641,
std::vector<std::pair<std::wstring, s6::s141>> s143, const s262* ast_ );
public:
typedef s1371 s1129;
s1370( s261* s299 ) : s1357( s299, NULL, NULL ) {}
s1370( s261* s299, s1053 s1191, s1053 s1265, s1053 s1171,
s1053 s702, s271* s585, const s262* ast_ = NULL );
s1370( const s1370& right, const s262* ast_ = NULL );
s1370( s261* s299, const std::vector<s270*>& l, s271* s585,
const s262* ast_ = NULL, s1053 s702 = 0, s1053 s1171 = 0,
s1053 s1625 = 0, s1053 s1265 = 0 );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s1053 s1185( const std::wstring& s1262, s806::Cont& s585 );
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s346; }
s1053 s1178( const std::wstring& s1540, const std::vector<s482>& l ) const override;
size_t s1128() const override { return 0; }
void s497( const s271* s872, bool fr=true ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
Iterator* s311( s382* r, bool s2295 = false ) override;
Iterator* s1175() override;
Iterator* s1179() override;
s1374& s317() { return s346; }
const s1374& s317() const { return s346; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s1919( Stream* ) const override;
virtual void s303( std::wostream* pd, int s196 = 0 ) const override;
};
typedef s321 TDIndex;
class s951;
class s382;
class s313;
class s601
: public s588{
std::vector<s1053> types;
std::vector<s485> s646;
public:
s601( s261* s299, s271* s585, s588* s584, s560 ct,
const std::vector<s270*>& l, const s262* s694 );
void s645( s1053 type, s588* pOvr );
virtual s483 s494( s480** s273, size_t s495 ) override;
};
class s831
: public s588{
std::vector<s1053> s1887;
bool s2088;
s1::s9<s951> s2094;
s480* s1880( s480** s273, size_t s495 ) override;
s831( const s831& );
public:
s831( s261* s299 );
s831( s261* s299, s271* s589, s588* s590, 
const std::vector<s270*>& l, const s262* s694, s1053 s2105 = 0, bool s2088 = true, bool s2158 = true );
s831( s261* s299, s271* s589, const std::vector<s1053>& l, 
s1053 pt, const s262* s694 );
s831( s831& s1885, s271* s589, s588* s590, const std::vector<s482>& l, const s262* s694 );
std::wstring s827() const override;
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s483 s494( s480** s273, size_t s495 ) override;
void s497( const s271* s1657, bool proc ) override;
s480* s493() override { return this; }
s1053 s1317() const { return s1887.back(); }
s482 s2283() override;
s270* s332( s588* s2041, s271* impl ) const override;
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
void s2209( const s271* s1657, bool proc );
using s480::s352;
using s480::s1879;
s480* s352( s271* s585, const std::vector<s1053>& vt ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l,
const s262* ast_ ) const override;
s588* s1670( s1889& s277, s588* s214,	s271* s585, s558* cs ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
std::wstring trace( s1889& topics ) const override;
};
class s832
: public s588{
bool s2232;
public:
s832( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694, bool s2158 = true );
s832( const s832& right, s271* s589, s588* s590 );
s1889& s298() const override { return s845; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s889
: public s588{
int code;
public:
s889( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s603
: public s588{
public:
s603( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s2061
: public s588{
public:
s2061( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s604
: public s588{
public:
s604( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l,
const s262* s694, bool s2158 = true );
s604( s261* s299 );
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1395
: public s588{
s368 s1490;
s483 varval;
s482 s307;
s368 s308;
s1517 s309;
s482 lambda;
public:
s1395( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694, bool s2158 );
s1395( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1923
: public s588{
public:
s1923( s261* s299, s271* s585, s588* s584, std::vector<s270*>& l, 
const s262* s694 );
s1923( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s2192
: public s588{
s482 s2196;
s483 s977;
s1::s9<s382> range;
s482 where, s1062;
s1::s9<s313> s680;
public:
enum s1131 { s1225 };
s2192( s261* s299, s271* s585, s588* s584, std::vector<s270*>& l, 
const s262* s694 );
s2192( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s605
: public s588{
s576 s617;
std::vector<s576> s618;
public:
enum s1131{ s1213, s1214 };
s605( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694,
bool s2158 = true );
s605( const s605& right, s271* s585, s588* s584 );
void s497( const s271* s1657, bool proc ) override;
void s729( bool proc );
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
};
class s608
: public s588{
s358 s78;
public:
s608( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s608( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s610
: public s588{
public:
s610( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s610( s261* s299 );
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s609
: public s588{
s368 s76;
s358 s616;
s1::s9<s610> ctch;
public:
s609( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s609( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s748
: public s588{
std::vector<std::wstring> fields;
public:
s748( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1665
: public s588{
public:
typedef s480* (s271::*s1667)(s480**, size_t);
private:
s1667 s1669;
s482 subject;
public:
s1665( s261* s299, s271* s585, s588* s584, s1667 _ptr,
s558* cs, const s262* s694 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1666
: public s588{
public:
typedef s480* (s480::*s1668)(s480**, size_t);
private:
s1668 s1669;
s1::s9<s368> s2285;
s482 s2286;
public:
s1666( s261* s299, s271* s585, s588* s584, s1668 _ptr,
const std::vector<s270*>& s273, s1889& s671, s1053 s1064, const s262* s694, bool s2158 );
s1666( const s1666&, s271* s585, s588* s584 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
};
class s1596
: public s588{
s483 cmd;
std::thread s816;
public:
s1596( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1596( const s1596& );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1594
: public s588{
public:
s1594( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1594( const s1594& r, s271* s589, s588* s590 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1591
: public s588{
public:
s1591( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694, bool s2159 );
s1591( const s1591& right, s271* s589, s588* s590 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1595
: public s588{
public:
s1595( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1595( const s1595& );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1590
: public s588{
s1590( const s1590& q):s588(q){ throw; }
public:
s1590( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694,
bool s2158 );
s1590( const s1590& right, s271* s585, s588* s584 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1869
: public s588{
public:
s1869( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1869( const s1869& );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s606
: public s588{
s482 s42;
bool lout;
public:
enum s1131{ s1223, s1457, s1577, s1951, s1952, s1558, s1917, s1901, 
s1903, s1904, s1902, s1916, s1556, s1557 };
s606( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694,
bool s2158 = false );
s606( const s606& right, s271* s585, s588* s584 );
s606( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;	
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
};
class s1924
: public s588{
s482 source;
bool lin;
public:
enum s1131{ s1216, s1951, s1952, s1558, s1917, s1916 };
s1924( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1924( s261* s299 );
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
template<class _Cont, class s1300, class Der>
s1133* s310<_Cont, s1300, Der>::s1959( Der** pv, typename _Cont::iterator& s1965 ){
typename _Cont::iterator s1578 = s1965;
if( s1965 != (*pv)->s346.end() )
++s1578;
s1133* s680 = new s1133( (*pv)->s299, (*pv)->ns,
new typename Der::s1129( (*pv)->s299, *pv, s1965, s1578 ), NULL );
s680->s497( (*pv)->ns, true );
return s680;}
template <class _Cont, class s1300, class Der>
void s310<_Cont, s1300, Der>::s347(){
s299->TR().s1152( s490, s7::s1399, s1500::s1495 );
s345.insert( std::make_pair( L"size", new s334( L"size", &s310<_Cont, s1300, Der>::s325, s1141,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"clear", new s334( L"clear", &s310<_Cont, s1300, Der>::s327, s1142,
{ s1112() }, 0, 0, false ) ) );}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s347(){
s310<_Cont, s1300, Der>::s347();
s345 = s310<_Cont, s1300, Der>::s339();
s345.insert( std::make_pair( L"coincide", new s334( L"coincide", &s1389<_Cont, s1300, Der, s1569>::s1934, s1141,
{ s1112(), s1112( { s1403 } ), s1112( { s7::s1382 } ) }, 0, 1, true,
{L"list:", L":back"}) ) );
s345.insert( std::make_pair( L"max-element", new s334( L"max-element", &s1389<_Cont, s1300, Der, s1569>::s1201,
0, { s1112(), s1112( { s1403 } ), 
s1112( { s1403, s7::s1386 } ),
s1112( { s7::s1386 } ) }, 0, 1 ) ) );
s345.insert( std::make_pair( L"max-element-idx", new s334( L"max-element-idx", &s1389<_Cont, s1300, Der, s1569>::s1200,
s1142, { s1112(), s1112( { s1403 } ) }, 0, 1 ) ) );
s345.insert( std::make_pair( L"min-element", new s334( L"min-element", &s1389<_Cont, s1300, Der, s1569>::s2074,
0, { s1112(), s1112( { s1403 } ), 
s1112( { s1403, s7::s1386 } ),
s1112( { s7::s1386 } ) }, 0, 1 ) ) );
s345.insert( std::make_pair( L"min-element-idx", new s334( L"min-element-idx", &s1389<_Cont, s1300, Der, s1569>::s2073,
s1142, { s1112(), s1112( { s1403 } ) }, 0, 1 ) ) );
s345.insert( std::make_pair( L"is-subset", new s334( L"is-subset", &s1389<_Cont, s1300, Der, s1569>::s2072, s1138,
{ s1112(), s1112( { s1403 } ), s1112( { s7::s1382 } ) }, 0, 1, true ) ) );
s345.insert( std::make_pair( L"sort", new s334( L"sort", &s1389<_Cont, s1300, Der, s1569>::s1256, 0,
{ s1112(), s1112( { s1403 } ) }, 0, 1, false ) ) );
s345.insert( std::make_pair( L"reverse", new s334( L"reverse", &s1389<_Cont, s1300, Der, s1569>::s1243, 0,
{ s1112(), s1112( { s1403 } ) }, 0, 1, false ) ) );
s345.insert( std::make_pair( L"shuffle", new s334( L"shuffle", &s1389<_Cont, s1300, Der, s1569>::s1580, 0,
{ s1112(), s1112( { s1403 } ) }, 0, 1, false ) ) );
s345.insert( std::make_pair( L"unique", new s334( L"unique", &s1389<_Cont, s1300, Der, s1569>::s2078, 0,
{ s1112(), s1112( { s1403 } ) }, 0, 1, true ) ) );
s345.insert( std::make_pair( L"for-each", new s334( L"for-each", &s1389<_Cont, s1300, Der, s1569>::s1730, s1142,
{ s1112(), s1112( { s1403 } ) }, 0, 1, false ) ) );
s345.insert( std::make_pair( L"find-adjacent", new s334( L"find-adjacent", &s1389<_Cont, s1300, Der, s1569>::s1574, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"subseq", new s334( L"subseq", &s1389<_Cont, s1300, Der, s1569>::s1481,
s1403, { s1112( {s1141} ), s1112( { s1141, s1141 } ) }, 1, 2 ) ) );
s345.insert( std::make_pair( L"begin", new s334( L"begin", &s1389<_Cont, s1300, Der, s1569>::s1570, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"end", new s334( L"end", &s1389<_Cont, s1300, Der, s1569>::s1573, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"front", new s334( L"front", &s1389<_Cont, s1300, Der, s1569>::s1622, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"back", new s334( L"back", &s1389<_Cont, s1300, Der, s1569>::s1608, 0,
{ s1112() }, 0, 0 ) ) );
s345.emplace( std::make_pair( L"is-el", new s334( L"is-el", &s1389<_Cont, s1300, Der, s1569>::s2221, s1138,
{ s1112( { s7::s1385 } ) }, 1, 1, true ) ) );
s345.emplace( std::make_pair( L"is-sorted", new s334( L"is-sorted", &s1389<_Cont, s1300, Der, s1569>::s2304, s1138,
{ s1112( ) }, 0, 0, true ) ) );
s345.equal_range( L"begin" ).first->second->s1250( true );
s345.equal_range( L"end" ).first->second->s1250( true );
s345.equal_range( L"front" ).first->second->s1250( true );
s345.equal_range( L"back" ).first->second->s1250( true );
s345.equal_range( L"max-element" ).first->second->s1250( true );
s345.equal_range( L"max-element-idx" ).first->second->s1250( true );
s345.equal_range( L"min-element" ).first->second->s1250( true );
s345.equal_range( L"min-element-idx" ).first->second->s1250( true );
s345.equal_range( L"reverse" ).first->second->s1250( true );
s345.equal_range( L"find-adjacent" ).first->second->s1250( true );
s345.equal_range( L"sort" ).first->second->s1250( true );
s345.equal_range( L"shuffle" ).first->second->s1250( true );
s345.equal_range( L"unique" ).first->second->s1250( true );
this->s299->TR().s1152( this->s490, s7::s1399, s1500::s1495 );}
template <class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s347(){
s1389<_Cont, s1300, Der, s1300>::s347();
s345 = s1389<_Cont, s1300, Der, s1300>::s339();
s1053 tp = s7::s1386;
s345.insert( std::make_pair( L"sort", new s334( L"sort", &s1563<_Cont, s1300, Der>::s1256, 0,
{ s1112( { s1403 } ), s1112( { s1403, tp } ),
s1112( { tp } ), s1112() }, 0, 2/*, {L":asc", L":desc"}*/ ) ) );
s345.insert( std::make_pair( L"group-by", new s334( L"group-by", &s1563::s1452, 0,
{ s1112( { tp } ), s1112()  }, 0, 1 ) ) );
if( s345.count( L"front" ) ) s345.erase( L"front" );
s345.insert( std::make_pair( L"front", new s334( L"front", &s1563<_Cont, s1300, Der>::s1622, 0,
{ s1112() }, 0, 0 ) ) );
if( s345.count( L"back") ) s345.erase( L"back" );
s345.insert( std::make_pair( L"back", new s334( L"back", &s1563<_Cont, s1300, Der>::s1608, 0,
{ s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"join", new s334( L"join", &s1563<_Cont, s1300, Der>::s1957, Types.String,
{ s1112( { s1403, Types.String } ), s1112( { Types.String } ) }, 1, 1 ) ) );
if( s345.count( L"is-el" ) ) s345.erase( L"is-el" );
s345.emplace( std::make_pair( L"is-el", new s334( L"is-el", &s1563<_Cont, s1300, Der>::s2221, s1138,
{ s1112( { s7::s1385 } ) }, 1, 1, true ) ) );
if( s345.count( L"is-sorted" ) ) s345.erase( L"is-sorted" );
s345.emplace( std::make_pair( L"is-sorted", new s334( L"is-sorted", &s1563<_Cont, s1300, Der>::s2304, s1138,
{ s1112( { s1403 } ), s1112( { s1403, tp } ), s1112(), s1112( { tp } ) }, 0, 1, true ) ) );
s345.equal_range( L"front" ).first->second->s1250( true );
s345.equal_range( L"back" ).first->second->s1250( true );
s345.equal_range( L"sort" ).first->second->s1250( true );
s345.equal_range( L"group-by" ).first->second->s1250( true );
this->s299->TR().s1152( this->s490, s7::s1399, s1500::s1495 );}
template <class _Cont, class s1409, class s1411, class Der>
void s1357<_Cont, s1409, s1411, Der>::s347(){
s310<_Cont, s1409, Der>::s347();
s345 = s310<_Cont, s1409, Der>::s339();
s345.insert( std::make_pair( L"max-element", new s334( L"max-element", &s1357::s1201,
0, { s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"min-element", new s334( L"min-element", &s1357::s2074,
0, { s1112() }, 0, 0 ) ) );
s345.insert( std::make_pair( L"is-subset", new s334( L"is-subset", &s1357::s2072, s1138,
{ s1112( { s7::s1382 } ) }, 1, 1 ) ) );
s345.insert( std::make_pair( L"regroup-by", new s334( L"regroup-by", &s1357::s1473, 0,
{ s1112( { s7::s1386 } ) }, 1, 1 ) ) );
s345.emplace( std::make_pair( L"find", new s334( L"find", &s1357::s773, 0,
{ s1112( { s7::s1384 } ) }, 1, 1, true ) ) );
s345.equal_range( L"max-element" ).first->second->s1250( true );
s345.equal_range( L"min-element" ).first->second->s1250( true );
s345.equal_range( L"regroup-by" ).first->second->s1250( true );
s345.equal_range( L"find" ).first->second->s1250( true );
this->s299->TR().s1152( this->s490, s7::s1399, s1500::s1495 );}
template <class _Cont, class s1300, class Der>
s1053 s310<_Cont, s1300, Der>::
s1178( const std::wstring& s1540, const std::vector<s482>& l ) const{
s1053 s680 = 0;
return s680;}
template <class _Cont, class s1300, class Der, class s1569>
s1053 s1389<_Cont, s1300, Der, s1569>::
s1178( const std::wstring& s1540, const std::vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"begin" || s1540 == L"end" ) {
s806::Cont s1268;
s1053 s1444 = this->s316();
s680 = this->s299->TR().s1038( std::vector<s1053>(
{ s1567, 1, s1444/*s1089*/, 0 } ) );
}
else if( s1540 == L"front" || s1540 == L"back" )
s680 = this->ValType();
else if( s1540 == L"max-element-idx" || s1540 == L"min-element-idx" )
s680 = this->s930();
else if( s1540 == L"sort" || s1540 == L"reverse" || s1540 == L"unique" 
|| s1540 == L"shuffle" )
s680 = this->s349();
else if( s1540 == L"find-adjacent" || s1540 == L"max-element" || 
s1540 == L"min-element") {
s806::Cont s1268;
s1053 s1444 = this->s316();
s680 = this->s299->TR().s1038( std::vector<s1053>( 
{ s1567, 1, s1444/*s1089*/, 0 } ) );
}
else
s680 = s310<_Cont, s1300, Der>::s1178( s1540, l );
return s680;}
template <class _Cont, class s1300, class Der>
s1053 s1563<_Cont, s1300, Der>::
s1178( const std::wstring& s1540, const std::vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"front" || s1540 == L"back" )
s680 = this->ValType();
else if( s1540 == L"sort" )
s680 = this->s349();
else if( s1540 == L"group-by" ) {
s806::Cont s1268;
s1053 s1089 = this->s322;
std::wstring ts = this->s299->TR().s1341( Types( this->s299, Types.Vector )->s350() + L"<" +
this->s299->TR().s797( s1089 ) + L">" );
s1053 s1504 = ((s313*)Types( this->s299, Types.Vector ))->s1185( (s313*)this, ts, s1704, s1268 );
s1053 s1455 = s1089;
if( l.size() )
s1455 = l[0].s15<s831*>()->s1317();
s680 = this->s299->TR().s1038( std::vector<s1053>( 
{ Types.Index, 2, s1455, 0, s1504, 0 } ) );}
else
s680 = s1389<_Cont, s1300, Der, s1300>::s1178( s1540, l );
return s680;}
template <class _Cont, class s1409, class s1411, class Der>
s1053 s1357<_Cont, s1409, s1411, Der>::
s1178( const std::wstring& s1540, const std::vector<s482>& l ) const{
s1053 s680 = 0;
if( s1540 == L"max-element" )
s680 = this->s316();
else if( s1540 == L"regroup-by" ) {
s806::Cont s1268;
s1053 s1455 = l[0].s15<s831*>()->s1317();
s1053 s1089 = this->s322;
std::wstring ts = this->s299->TR().s1341( Types( this->s299, Types.Vector )->s350() + L"<" +
this->s299->TR().s797( s1089 ) + L">" );
s1053 s1504 = ( (s313*)Types( this->s299, Types.Vector ) )->s1185( (s313*)this, ts, s1704, s1268 );
s680 = this->s299->TR().s1038( std::vector<s1053>( 
{ Types.Index, 2, s1455, 0, s1504, 0 } ) );}
else if( s1540 == L"find" ) {
s806::Cont s1268;
s1053 s1444 = this->s316();
s680 = this->s299->TR().s1038( std::vector<s1053>( 
{ s1567, 1, s1444, 0 } ) );}
else
s680 = s310<_Cont, s1409, Der>::s1178( s1540, l );
return s680;}
template <class _Cont, class s1409, class s1411, class Der>
s270* s1357<_Cont, s1409, s1411, Der>::s1324( std::pair<s1409, s1411>& el ){
return new s951( this->s299, this->ns, std::vector<s270*>({el.first, el.second}) ); }
template <class _Cont, class s1409, class s1411, class Der>
bool s1357<_Cont, s1409, s1411, Der>::insert( s480* s151, s480* s346 ){
return this->s346.insert( std::make_pair( s151, s346 ) ).second;}
template <class _Cont, class s1409, class s1411, class Der>
s480* s1357<_Cont, s1409, s1411, Der>::find( s480* s151 ){
auto it = this->s346.find( s151 );
if( it != end( this->s346 ) )
return it->second;
return NULL;}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1570( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
*s273 = new s1133( pv->s299, pv->ns, pv->s1175(), NULL );}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1573( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
*s273 = new s1133( pv->s299, pv->ns, pv->s1179(), NULL );}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1481( s480** s273, size_t s495 ){
if( s495 < 3 || s495 > 4 )
throw new s2::s16( L"subseq: wrong number of arguments" );
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv = ( (s1120*)s273[1] );
int s1479 = (int)*s273[2];
int s1480;
if( s495 == 4 )
s1480 = (int)*s273[3];
else
s1480 = (int)pv->s346.size() - 1;
s382 range( s1479, s1480 );
s1134 pr = range.s1184( pv );
s932* s1474;
if( pv->s1128() >= 1 && pr.first.s15<s1115*>()->Reversed() ) {
typename _Cont::reverse_iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1136();
s1508 = pr.second.s15<s932*>()->s1136();
s1474 = new s932( pv->s299, pv, s1507, s1508 );}
else {
typename _Cont::iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1135();
s1508 = pr.second.s15<s932*>()->s1135();
s1474 = new s932( pv->s299, pv, s1507, s1508 );}
s382* s680 = new s382( pv->s299, pv, s1474 );
*s273 = s680;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1256( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 pr = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
if( ( (s323*)pv )->s1128() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s2216;
s2216.s852 = s1196;
if( pv->s1128() >= 1 && pr.first.s15<s1115*>()->Reversed() ) {
typename _Cont::reverse_iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1136();
s1508 = pr.second.s15<s932*>()->s1136();
std::sort( s1507, s1508, s2216 );}
else {
typename _Cont::iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1135();
s1508 = pr.second.s15<s932*>()->s1135();
std::sort( s1507, s1508, s2216 );}
*s273 = pv;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s773( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s2216;
s2216.s852 = s1196;
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1965 = std::find( s1507, s1508, pv->s1571 );
typename _Cont::iterator s1578 = s1965;
if( s1965 != pv->s346.end() )
++s1578;
s1133* s680 = new s1133( pv->s299, pv->ns,
new s932( pv->s299, pv, s1965, s1578 ), NULL );
s680->s497( pv->ns, true );
*s273 = s680;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1574( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1965 = std::adjacent_find( s1507, s1508, pv->s1571 );
typename _Cont::iterator s1578 = s1965;
if( s1965 != pv->s346.end() )
++s1578;
s1133* s680 = new s1133( pv->s299, pv->ns,
new s932( pv->s299, pv, s1965, s1578 ), NULL );
s680->s497( pv->ns, true );
*s273 = s680;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2221( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
s1120* pv;
s382* pr = NULL;
if( s273[1]->s349() == s1403 ) {
pr = (s382*)s273[1];
pv = (s1120*)pr->s812();}
else
pv = ( (s1120*)s273[1] );
s1134 rp;
if( pr ) {
rp = pr->s1184( pv );}
else
rp = pv->s1184();
s1569* s2214 = (s1569*)s273[2];
s1300* el = (s1300*)( (s333*)s2214 )->addr();
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1965 = std::find( s1507, s1508, *el );
*((s357*)*s273)->s354() = ( s1965 != pv->s346.end() );}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s2304( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 pr = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
if( ( (s323*)pv )->s1128() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s2216;
s2216.s852 = s1196;
bool s152;
if( pv->s1128() >= 1 && pr.first.s15<s1115*>()->Reversed() ) {
typename _Cont::reverse_iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1136();
s1508 = pr.second.s15<s932*>()->s1136();
s152 = std::is_sorted( s1507, s1508, s2216 );}
else {
typename _Cont::iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1135();
s1508 = pr.second.s15<s932*>()->s1135();
s152 = std::is_sorted( s1507, s1508, s2216 );}
*((s357*)*s273)->s354() = s152;}
template <class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1730( s480** s273, size_t s495 ){
using s1120 = Der;
using s932 = typename Der::s1129;
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
s932* s1507 = rp.first.s15<s932*>(), *s1508 = rp.second.s15<s932*>();
std::vector<s482> s1824( 1 );
while( !( s1507 == s1508 ) ) {
s1824[0] = s1507->s954();
s1748->s593( s1824 );
s1748->s494( 0, 0 );}}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1622( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
if( pv->s346.empty() )
throw new s2::s16( L"(front) method was called on an empty container",
(uint32_t)s2::s16::s17::s24 );
auto it = pv->s346.begin();
*s273 = (s480*)pv->s1324( *it );}
template<class _Cont, class s1300, class Der, class s1569>
void s1389<_Cont, s1300, Der, s1569>::s1608( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
if( pv->s346.empty() )
throw new s2::s16( L"(back) method was called on an empty container",
(uint32_t)s2::s16::s17::s24 );
auto it = pv->s346.end();
--it;
*s273 = (s480*)pv->s1324( *it );}
template<class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s1622( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
if( pv->s346.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
s480* s1052 = NULL;
if( pv->s346.size() ) {
auto it = pv->s346.begin();
s1052 = it->template s15<s480*>();}
*s273 = s1052;}
template<class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s1608( s480** s273, size_t n ){
Der* pv = ( (Der*)s273[1] );
if( pv->s346.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
s480* s1052 = NULL;
if( pv->s346.size() ) {
auto it = pv->s346.end();
--it;
s1052 = ( &( *it ) )->template s15<s480*>();}
*s273 = s1052;}
template <class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s1256( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 pr = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
if( ( (s323*)pv )->s1128() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s1953;
if( s1196 )
s1953.s852 = s1196;
if( pv->s1128() >= 1 && pr.first.s15<s1115*>()->Reversed() ) {
typename _Cont::reverse_iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1136();
s1508 = pr.second.s15<s932*>()->s1136();
std::sort( s1507, s1508, s1953 );}
else {
typename _Cont::iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1135();
s1508 = pr.second.s15<s932*>()->s1135();
std::sort( s1507, s1508, s1953 );}
*s273 = pv;}
template <class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s2304( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 pr = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
if( ( (s323*)pv )->s1128() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s1953;
if( s1196 )
s1953.s852 = s1196;
bool s152;
if( pv->s1128() >= 1 && pr.first.s15<s1115*>()->Reversed() ) {
typename _Cont::reverse_iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1136();
s1508 = pr.second.s15<s932*>()->s1136();
s152 = std::is_sorted( s1507, s1508, s1953 );}
else {
typename _Cont::iterator s1507, s1508;
s1507 = pr.first.s15<s932*>()->s1135();
s1508 = pr.second.s15<s932*>()->s1135();
s152 = std::is_sorted( s1507, s1508, s1953 );}
*((s357*)*s273)->s354() = s152;}
template <class _Cont, class s1300, class Der>
void s1563<_Cont, s1300, Der>::s773( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
s588* s1196 = NULL;
if( s495 == 3 )
s1196 = (s588*)s273[2];
s1290<s1300> s1953;
if( s1196 )
s1953.s852 = s1196;
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
typename _Cont::iterator s1965 = std::find( s1507, s1508, pv->s1571 );
typename _Cont::iterator s1578 = s1965;
if( s1965 != pv->s346.end() )
++s1578;
s1133* s680 = new s1133( pv->s299, pv->ns,
new s932( pv->s299, pv, s1965, s1578 ), NULL );
s680->s497( pv->ns, true );
*s273 = s680;}
template<class _Cont, class s1300, class Der>
inline void s1563<_Cont, s1300, Der>::s1452( s480** s273, size_t s495 ){
if( s495 < 2 || s495 > 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s495 == 3 && s273[2]->s491() != s1234 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s588* pf = NULL;
if( s495 == 3 )
pf = (s588*)s273[2];
s321* s152 = (s321*)*s273;
std::vector<s482>s854;
s854.resize( 1 );
typename _Cont::iterator s1506 = pv->s346.begin();
for( ; s1506 != pv->s346.end(); ++s1506 ) {
s482 s1057 = *s1506;
s483 s1049;
if( pf ) {
s854[0] = s1057;
pf->s593( s854 );
s1049 = pf->s494( 0, 0 );}
else
s1049 = s1057.s15<s480*>();
s480* s1442 = s152->find( s1049 );
if( s1442 )
((s313*)s1442)->add( s1057->s332(0,0) );
else {
s313* s1470 = new s313( pv->s299, pv->s322, pv->ns, NULL );
s1470->s497( pv->ns );
s1470->add( s1057->s332(0,0) );
s152->insert( (s480*)s1049->s332(0,0), (s480*)s1470 );}}}
template<class _Cont, class s1300, class Der>
inline void s1563<_Cont, s1300, Der>::s1957( s480** s273, size_t s495 ){
Der* pv = ( (Der*)s273[1] );
const std::wstring& s72 = ( (s356*)s273[2] )->s317();
std::wstring s680;
if( pv->s346.empty() ) {
*s273 = new s356( pv->s299 );
(*s273)->s1251();
return;}
typename _Cont::iterator s1506 = pv->s346.begin();
s680 = (*s1506)->to_wstring();
for( ++s1506; s1506 != pv->s346.end(); ++s1506 )
s680 += s72 + (*s1506)->to_wstring();
*s273 = new s356( pv->s299, s680 );
(*s273)->s1251();}
template<class _Cont, class s1300, class Der>
inline void s1563<_Cont, s1300, Der>::s2221( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = NULL;
s1134 rp = s310<_Cont, s1300, Der>::s1414( s273[1], &pv );
pv->s494(0,0);
s483 el = (s480*)s273[2];
el->s494(0,0);
typename _Cont::iterator s1507, s1508;
s1507 = rp.first.s15<s932*>()->s1135();
s1508 = rp.second.s15<s932*>()->s1135();
if( el->s1194() &&
std::find_if( s1507, s1508, [el]( s482 r ) { return el->operator==(r.s15<s480*>()); } ) != s1508 )
*( (s357*)*s273 )->s354() = true;
else
*( (s357*)*s273 )->s354() = false;
(*s273)->s1251();}
template <class _Cont, class s1409, class s1411, class Der>
void s1357<_Cont, s1409, s1411, Der>::s773( s480** s273, size_t s495 ){
using s932 = typename Der::s1129;
Der* pv = (Der*)s273[1];
s480* s2240 = s273[2];	
typename _Cont::iterator s1965;
if( s2240->s1194() )
s1965 = pv->s346.find( s2240 );
else
s1965 = pv->s346.end();
typename _Cont::iterator s1578 = s1965;
if( s1965 != pv->s346.end() )
++s1578;
s1133* s680 = new s1133( pv->s299, pv->ns,
new s932( pv->s299, pv, s1965, s1578 ), NULL );
s680->s497( pv->ns, true );
*s273 = s680;}
template<class _Cont, class s1409, class s1411, class Der>
inline void s1357<_Cont, s1409, s1411, Der>::s1473( s480** s273, size_t s495 ){
if( s495 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s273[2]->s491() != s1234 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s588* pf = (s588*)s273[2];
s321* s152 = (s321*)*s273;
std::vector<s482>s854;
s854.resize( 1 );
typename _Cont::iterator s1506 = pv->s346.begin();
for( ; s1506 != pv->s346.end(); ++s1506 ) {
s482 s1057 = *s1506->second;
s854[0] = s1057;
pf->s593( s854 );
s483 s1049 = pf->s494( 0, 0 );
s480* s1442 = s152->find( s1049 );
if( s1442 )
((s313*)s1442)->add( s1057->s332(0,0) );
else {
s313* s1470 = new s313( pv->s299, pv->s322, pv->ns, NULL );
s1470->s497( pv->ns, true );
s1470->add( s1057->s332(0,0) );
s152->insert( (s480*)s1049->s332(0,0), (s480*)s1470 );}}}
template<>
inline void s1563<s2202, s482, s2203>::s2221( s480** s273, size_t s495 ){
s2203* pv = ( (s2203*)s273[1] );
s482 el = (s480*)s273[2];
if( pv->s346.count( el ) )
*( (s357*)*s273 )->s354() = true;
else
*( (s357*)*s273 )->s354() = false;
( *s273 )->s1251();}
template <>
inline void s1389<s2202, s482, s2203, s482>::s1256( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1563<s2202, s482, s2203>::s1256( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1389<s2202, s482, s2203, s482>::s1580( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );}
template <>
inline void s1389<s2202, s482, s2203, s482>::s2078( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );}
template <>
inline void s1389<s2202, s482, s2203, s482>::s1243( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );}
template<>
inline void s1563<s2235, s482, s2236>::s2221( s480** s273, size_t s495 ){
s2236* pv = ( (s2236*)s273[1] );
s482 el = (s480*)s273[2];
if( pv->s346.count( el ) )
*( (s357*)*s273 )->s354() = true;
else
*( (s357*)*s273 )->s354() = false;
( *s273 )->s1251();}
template <>
inline void s1389<s2235, s482, s2236, s482>::s1256( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1563<s2235, s482, s2236>::s1256( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s1580( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s2078( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s1243( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s1481( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'subseq' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s1608( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'back' operation" );}
template <>
inline void s1563<s2235, s482, s2236>::s1608( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'back' operation" );}
template <>
inline void s1389<s2235, s482, s2236, s482>::s2304( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1563<s2235, s482, s2236>::s2304( s480** s273, size_t s495 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
class s412
: public s333{
static s338 s345;
std::wstring path;
std::wstring s521;
s313 s747;
s313 s802;
static void s1226( s480** s273, size_t n );
static void s406( s480** s273, size_t n );
static void s1662( s480** s273, size_t n );
static void s413( s480** s273, size_t n );
static void s414( s480** s273, size_t n );
static void s982( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
s412( s261* s299 ) : s333( s299, NULL, NULL ), s747(s299), s802(s299) {}
s412( s261* s299, const std::wstring& s77, const s262* ast_=NULL );
s412( const s412& right, const s262* ast_ = NULL );
s412( s261* s299, const std::wstring& s, size_t& pos, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)&s747; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1592
: public s588{
public:
s1592( s261* s299, s271* s589, s588* s590,
const std::vector<s270*>& l, const s262* s694 );
const std::wstring& s298() const override { return s1305; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
} // namespace
namespace transd{
class s602
: public s588{
public:
s602( s261* s299, s271* s589, s588* s590, const std::vector<s270*>& l,
const s262* s694, bool s2158 = false );
s602( const s602& right, s271* s589, s588* s590 );
s1889& s298() const override { return s232; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s705( s1889& s277, s368* ref,
s1889& s331 ) const;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s304
: public s588{
s482 s305;
public:
s304( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l,
const s262* s694,	bool s2158 = false );
s304( const s304& right, s271* s589, s588* s590 );
s1889& s298() const override { return s254; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s611
: public s588{
s486 s706;
s483 varval;
s482 s307;
s482 where;
s482 s1052;
s368 s308;
s1517 s309;
s368 s2474;
s1053 s2475{ 0 };
Iterator* s2273;
s1::s9<s323> s2272;
bool s877;
public:
s611( s261* s299, s271* s585, Transd* s584, const std::vector<s270*>& l,
const s262* s694, bool s2158 = true );
s611( const s611& right, s271* s589, s588* s590 );
s1889& s298() const override { return s259; }
void s497( const s271* s1657, bool proc ) override;
void s2117( s588* s2041, s271* impl, bool s2158 ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s607
: public s588{
public:
s607( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s607( s261* s299 );
s1889& s298() const override { return s255; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s612
: public s588{
static s1::s9<s261> s899;
public:
s612( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694, bool s2159 = true );
s612( s261* s299 );
const std::wstring& s298() const override { return s260; }
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s790
: public s588{
public:
s790( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s790( s261* s299 );
s1889& s298() const override { return s765; }
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s768
: public s588{
std::wstring s897;
public:
s768( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s768( s261* s299 );
const std::wstring& s298() const override { return s814; }
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1296
: public s588{
public:
s1296( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1296( s261* s299 );
s1889& s298() const override { return s1306; }
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1597
: public s588{
public:
s1597( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
s1597( s261* s299 );
s1889& s298() const override { return s1607; }
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
};
class s1768
: public s1::s10{
public:
s1768() { }
virtual ~s1768() { }
virtual s483 s753( const std::wstring& s76, bool s707 = true ) const = 0;
virtual void s856( s743& s152 ) const = 0;
virtual void s856( s951& s152 ) const = 0;
virtual void s542( std::vector<std::wstring>& s152 ) const = 0;
virtual size_t s319() const = 0;
};
class s769;
typedef s1::s9<s1768> s815;
bool s1787( s815 l, s815 r );
struct s737 : public s1::s10{
enum Verb { s1760, s1761, s1759, s1762, s2043, s1758 };
Verb verb;
s737()
: verb( s1760 )
{	}
};
class s1766;
typedef std::multimap<s483, s815, s1413> s1771;
typedef std::pair<s1771::iterator, s1771::iterator> s1773;
typedef std::list<s815> s1769;
extern s1769 s1831;
extern s1769::iterator s1832;
struct s1770{
bool operator()( const s483 l, const s483 r ) const{
return l->operator<( ( s480* )&( *r ) );}
bool operator()( const s480* l, const s480* r ) const{
return l->operator<( r );}
bool operator()( const s483 l, const std::pair<s483, s815>& r ) const{
return l->operator<( ( s480* )&( *r.first ) );}
bool operator()( const std::pair<s483, s815>& l, const s483 r ) const{
return l.first->operator<( ( s480* )&( *r ) );}
};
struct s1772{
s1773 pr;
std::wstring s969;
size_t dist;
bool operator<( s1772 const& r ) const{
return dist < r.dist;}
};
class s1767{
protected:
s1766* pdb;
s1769* ptr;
s1769::iterator fi;
s1769::iterator se;
s1769::iterator cur;
public:
s1767( s1766* s1791 );
virtual ~s1767();
virtual void s1855( void* f, void* s ) = 0;
virtual void s1858() = 0;
virtual bool s1820() = 0;
virtual s1768* s1830() = 0;
void sort() { ptr->sort( s1787 ); }
void clear() { ptr->clear(); }
bool empty() { return ptr->empty(); }
void swap( s1767* r ) { ptr->swap( r->s317() ); }
s1769& s317() { return *ptr; }
s1766* s1777() { return pdb; }
virtual void s1816( std::vector<std::wstring>& s152 ) = 0;
};
struct s1789{
bool operator()( const s1772* l, const s1772* r ) const{
return l->operator<( *r );}
bool operator()( const s1772& l, const s1772& r ) const{
return l.operator<( r );}
};
typedef std::set<s1772, s1789 > s1774;
class s1763{
public:
enum s1776 { s1841, s1836, s1839, s1837, s1840, s1838, s2134 };
private:
std::wstring field;
s1776 op;
s482 par, s346;
static const std::vector<std::wstring> s1863;
public:
s1763( s261* s299, s271* s585, const std::wstring& s, size_t& pos );
void s497( s271* ns );
void select( s1766* pdb, s1772& s152 );
};
class s1764;
class s1764{
public:
enum s1765 { s1798, s1799, s1797 };
private:
s1765 s1802;
std::vector<s1764> subs;
std::vector<s1763> s1796;
public:
s1764( s261* s299, s271* s585, const std::wstring& s, size_t& pos, s1765 s1802 );
s1764( const s1764& r );
void s497( s271* ns );
void s1795( s261* s299, s271* s585, const std::wstring& s, size_t& pos );
void select( s1766* pdb, s1767* s152 );
};
class s1766
: public s333{
protected:
std::map<std::wstring, s1771> s864;
bool s2052;
public:
s1766( s261* s299, s271* ns_, const s262* ast_ )
: s333( s299, ns_, ast_ ), s2052( true )	{	}
virtual ~s1766();
virtual void release() override;
bool s2053() const { return s2052; }
virtual void select( s1889& field, s1763::s1776, const s480* s1057,
s1772& s152 ) = 0;
virtual void intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ) = 0;
virtual void intersect( const s1772& fi, s1767* s152 ) = 0;
virtual void s848( s1889& s851 ) = 0;
virtual s1767* s1803() const = 0;
virtual void s1854( s1767* s152 ) = 0;
virtual bool s1994( s1889& s ) const = 0;
virtual s1053 s1999( s1889& s851 ) const = 0;
virtual void s1817( std::vector<std::wstring>& s152) const = 0;
};
struct s1697 : public s737{
enum s830 { s821=0, s824 };
int distinct;
int	s881;
std::wstring s880;
int s867;
s1697()
: distinct( -1 ), s881( -1 ), s867( -1 )
{	}
};
struct s1707 : public s737{
};
struct s1693 : public s737{
};
struct s1970 : public s737{
};
struct s1695 : public s1::s10 { };
struct s1696 : public s1695{
s482 what;
s482 where;
s482 s1851;
s482 s882;
s482 s1064;
s482 s867;
};
struct s1706 : public s1695{
s482 what;
s482 where;
s482 s1851;
};
struct s1692 : public s1695{
s482 at;
s482 values;
s1::s9<s1706> s1746;
};
struct s1969 : public s1695{
s482 what;
s482 where;
s482 s1851;
s482 s2041;
s482 s1064;
};
class s890
: public s588{
size_t s901;
s483 s680;
protected:
void s1895( const s574& pl ) const override { }
void s593( const s574& pl ) override { s273.assign( pl.begin(), pl.end() ); }
public:
s890() : s588( NULL, NULL, NULL, NULL, s562, L"", NULL ), 
s680( new s357( NULL, false ) ){ }
void s900( size_t idx ) { s901 = idx; }
virtual s483 s494( s480** s698, size_t s495 ) override{
s482 l = s273[0];
s482 r = s273[1];
*s680.s15<s357*>()->s354() = l.s15<s743*>()->operator[]( s901 ).s15<s480*>()->
operator<( r.s15<s743*>()->operator[]( s901 ).s15<s480*>() );
s483 s898 = s680;
return s898;}
};
class s313;
class s784
: public s588{
s482 db;
s368 s2022;
s1::s9<s951> s2021;
s1::s9<s737> s803;
s1::s9<s1695> qp;
s368 s726;
s484 s776;
s1764* s1844;
s481* s1790( const std::wstring& s );
void s2047( s1766* base, s482 what, std::vector<std::wstring>& s888,
std::vector<s485>& s2045, std::vector<std::wstring>& s1852 );
void s1708( const std::vector<s270*>& l_,	TDException& s960 );
void s1710( const s271* s1657, bool proc );
s483 s1715( s480** s273, size_t s495 );
void s1709( const std::vector<s270*>& l_,	TDException& s960 );
void s1711( const s271* s1657, bool proc );
s483 s1716( s480** s273, size_t s495 );
void s1986( const std::vector<s270*>& l_,	TDException& s960 );
void s1988( const s271* s1657, bool proc );
s483 s1991( s480** s273, size_t s495 );
public:
enum s1131{ s1221, s2055, s1741, s2004, s2054, s1206, s1207, s1225, 
s1828, s2005, s1211, s1222, s1208, s1210,	s1220, s1739 };
s784( s261* s299, s271* s585, s588* s584, const std::vector<s270*>& l, const s262* s694 );
~s784();
s1889& s298() const override { return s811; }
void s497( const s271* s1657, bool proc ) override;
s483 s494( s480** s273, size_t s495 ) override;
s270* s332( s588* s2041, s271* impl ) const override;
bool s553( s1889& s277, s368* s152, s1889& s331,	bool ) const override;
s270* s595( size_t off ) override;
};
class s769
: public s1768{
typedef std::map<std::wstring, s482> s720;
s720 s755;
s720* s2135;
size_t rechash;
s1::s9<s1589> pobj;
public:
s769() {}
s769( s261* s299, s271* s585, s1889& rec, const std::vector<std::wstring>& s736,
std::vector<s482>& types, const s1705& tbfr=s1723 );
s769( s261* s299, s1589& s585 );
s483 s753( s1889& s76, bool s707=true ) const override;
void s856( s743& s152 ) const override;
void s856( s951& s152 ) const override;
void s542( std::vector<std::wstring>& s152 ) const override;
size_t s319() const override;
bool operator==( const s769* p ) const;
bool operator<( const s769* p ) const;
std::wstring to_wstring( uint32_t s1552 = 0 ) const;
void s303( std::wostream* pd, int s196 = 0 ) const;
};
class s805
: public s1::s10{
typedef std::vector<s482> s728;
s728 s804;
size_t s793;
public:
s805() {}
s805( std::vector<std::wstring>& s725, s815 rec );
size_t s319() const;
bool operator==( const s805* p ) const;
bool operator<( const s805* p ) const;
void s303( std::wostream* pd, int s196 = 0 ) const;
};
typedef s1::s9<s805> s727;
struct s764{
std::size_t operator()( const s727 k ) const{
return k->s319();}
};
struct s708{
std::size_t operator()( const s727 l, const s727 r ) const{
return l->operator==( ( s805* )&( *r ) );}
};
struct s839{
std::size_t operator()( const s815 k ) const{
return k->s319();}
};
struct s838{
std::size_t operator()( const s815 l, const s815 r ) const{
return l.s15<s769*>()->operator==( ( s769* )&( *r ) );}
};
typedef std::unordered_map<s727, s815, s764, s708> s780;
extern s780::iterator s1833;
class s1781 
: public s1767{
s780* pind;
s780::iterator cur1;
public:
s1781( s1766* pdb );
virtual ~s1781(){}
void s1855( void* f, void* s ) override;
void s1858() override;
bool s1820() override;
s1768* s1830() override;
void s1816( std::vector<std::wstring>& s152 ) override {}
};
class s647
: public s1766{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
private:
static s338 s345;
BaseMap s648, s649, s650;
BaseMap::iterator s315;
s780 s750;
std::vector<std::wstring> s2129;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s779( s480** s273, size_t n );
static void s2126( s480** s273, size_t n );
static void s795( s480** s273, size_t n );
static void s745( s480** s273, size_t n );
static void s763( s480** s273, size_t n );
static void s330( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s328( s480** s273, size_t n );
static void s849( s480** s273, size_t n );
static void s2138( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
enum s1131 { s1738, s1736, s1734, s1735, s1737, s1827 };
s647( s261* s299, s271* s585 = NULL, const s262* ast_ = NULL );
s647( s261* s299, s271* s585, s1889& s77, const s262* ast_ = NULL );
s647( const s647& right, const s262* ast_ = NULL );
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)NULL; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s651( s1889& s193 );
void s376( s1589& obj );
void s652( s1889& q );
void s711( s1889& s817, const s1705& tbfr );
void s848( s1889& s851 ) override;
void select( s1889& field, s1763::s1776, const s480* s1057,	s1772& s152 ) override;
s1767* s1803() const override;
void s1854( s1767* s152 ) override;
void intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ) override;
void intersect( const s1772& fi, s1767* s152 ) override;
bool s1994( s1889& s ) const override;
s1053 s1999( s1889& s851 ) const override;
void s1817( std::vector<std::wstring>& s152) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1786;
class s1785
: public s1768{
public:
typedef std::vector<s483> s1778;
private:
s1778 s1846;
size_t rechash;
s1786* s1843;
public:
s1785() {}
s1785( const std::vector<s483>& v, s1786* s1843 );
s1785( s261* s299, s271* s585, s1889& rec,
const std::vector<std::wstring>& s736,
std::vector<s482>& types, const s1705& tbfr=s1723 ){ }
virtual ~s1785();
s483 s753( s1889& s76, bool s707 = true ) const override;
const s1778& s2000() const;
void s856( s743& s152 ) const override;
void s856( s951& s152 ) const override;
void s542( std::vector<std::wstring>& s152 ) const override;
virtual size_t s319() const override;
bool operator==( const s769* p ) const { return 0; }
bool operator<( const s769* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const{ return L""; }
void s303( std::wostream* pd, int s196 = 0 ) const{ }
};
class s1784 : 
public s1767{
public:
s1784( const s1784& r );
s1784( s1766* pdb );
virtual ~s1784();
void s1855( void* f, void* s ) override;
void s1858() override;
bool s1820() override;
s1768* s1830() override;
void s1816( std::vector<std::wstring>& s152 ) override;
};
class s1786
: public s1766{
public:
private:
static s338 s345;
s1769 rows;
std::vector<std::wstring> s799;
std::map<std::wstring, size_t> s1819;
std::vector<s815> s2044;
s1053 s2026;
std::wstring s496;
static void s1226( s480** s273, size_t n );
static void s795( s480** s273, size_t n );
static void s745( s480** s273, size_t n );
static void s763( s480** s273, size_t n );
static void s330( s480** s273, size_t n );
static void s325( s480** s273, size_t n );
static void s2002( s480** s273, size_t n );
static void s2010( s480** s273, size_t n );
static void s2011( s480** s273, size_t n );
static void s849( s480** s273, size_t n );
void s347() override;
const s338& s339() const override { return s345; }
public:
enum s1131 { s1738, s1736, s1734, s1735, s1737, s1827, 
s2003 };
s1786( s261* s299, s271* s585 = NULL, const s262* ast_ = NULL );
s1786( s261* s299, s271* s585, s1889& s77, const s262* ast_ = NULL );
s1786( const s1786& right, const s262* ast_ = NULL );
virtual ~s1786();
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
s1053 s1178( s1889& s1540, const std::vector<s482>& l ) const override;
void release() override;
bool s498( const s480* s499 ) const override;
void* addr() override { return (void*)NULL; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s651( s1889& s193 );
void s652( s1889& q ){ }
void s711( s1889& s817, const s1705& tbfr );
void s848( s1889& s851 ) override;
void select( s1889& field, s1763::s1776, const s480* s1057,
s1772& s152 ) override;
s1767* s1803() const override;
void s1854( s1767* s152 ) override;
void intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ) override;
void intersect( const s1772& fi, s1767* s152 ) override;
size_t s1818( s1889& s1801 ) const;
void s1817( std::vector<std::wstring>& s152 ) const override { s152 = s799; }
bool s1994( s1889& s ) const override;
s1053 s1999( s1889& s851 ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
class s1786;
class s2060
: public s1768{
private:
s483 rec;
public:
s2060( s483 d );
virtual ~s2060();
s483 s753( s1889& s76, bool s707 = true ) const override;
void s856( s743& s152 ) const override;
void s856( s951& s152 ) const override;
void s542( std::vector<std::wstring>& s152 ) const override;
virtual size_t s319() const override;
bool operator==( const s769* p ) const { return 0; }
bool operator<( const s769* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1552 = 0 ) const{ return L""; }
void s303( std::wostream* pd, int s196 = 0 ) const{ }
};
class s2059 : 
public s1767{
Iterator* s2065;
s323* s2067;
bool started;
public:
s2059( const s2059& r );
s2059( s1766* pdb );
virtual ~s2059();
void s1855( void* f, void* s ) override;
void s1858() override;
bool s1820() override;
s1768* s1830() override;
void s1816( std::vector<std::wstring>& s152 ) override;
};
class s2046
: public s1766{
private:
static s338 s345;
std::wstring s2064;
s323* pv;
s1053 s2026;
std::wstring s496;
void s347() override;
const s338& s339() const override { return s345; }
public:
s2046( s261* s299, s271* s585 = NULL, s323* pv = NULL, const s262* ast_ = NULL );
s2046( const s2046& r );
virtual ~s2046();
s480* s351( const s262& s694, s271* s585, s1889& s331 ) const override;
s480* s352( s271* s585, const std::vector<s270*>& l, const s262* ast_ ) const override;
void release() override;
void* addr() override { return (void*)NULL; }
void s497( const s271* s872, bool ) override;
s270* s332( s588* s2041, s271* impl ) const override;
void s353( s270* p ) const override;
size_t s319() const override;
bool operator==( const s480* p ) const override;
bool operator<( const s480* p ) const override;
void s651( s1889& s193 );
void s652( s1889& q ){ }
void s711( s1889& s817, const s1705& tbfr );
void s848( s1889& s851 ) override;
void select( s1889& field, s1763::s1776, const s480* s1057,
s1772& s152 ) override;
s1767* s1803() const override;
void s1854( s1767* s152 ) override;
void intersect( const s1772& fi1, const s1772& fi2,
s1769& s152 ) override;
void intersect( const s1772& fi, s1767* s152 ) override;
size_t s1818( s1889& s1801 ) const;
void s1817( std::vector<std::wstring>& s152 ) const override { s152.push_back( s2064 ); }
bool s1994( s1889& s ) const override;
s1053 s1999( s1889& s851 ) const override;
std::wstring to_wstring( uint32_t s1552 = 0 ) const override;
void s303( std::wostream* pd, int s196 = 0 ) const override;
};
#define TRANSD_VERSION L"0.517"
void evaluateExpression( const std::wstring& s77 );
HPROG createAssembly();
void deleteAssembly( int n );
void loadProgram( HPROG handle, const std::wstring& s188 );
void s210( HPROG handle, s6::s142& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s686 );
void* callFunc( HPROG handle, const std::wstring& s77, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s598 );
void* s222( HPROG handle, const std::wstring& s277 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1102, const std::wstring& symName,
const std::wstring& s331 );
void importFile( HPROG handle, const std::wstring& s1102, const std::wstring& s44,
const std::wstring& s331 );
HPROG initShell( const std::wstring& s1102, const std::wstring& modText );
typedef s2::s16 TransdException;
} // namespace transd
