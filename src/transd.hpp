
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
typedef std::uint64_t				UINT_PTR, *PUINT_PTR;
typedef long								LONG_PTR, *PLONG_PTR;
typedef unsigned long				ULONG_PTR, *PULONG_PTR;
typedef long long						LONGLONG;
typedef unsigned long long	ULONGLONG;
typedef ULONG_PTR		    		DWORD_PTR, *PDWORD_PTR;
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
class s1283{
int refs;
public:
s1283(){
refs=0;}
~s1283(){}
void reset(){
refs = 0;}
int s11(){
refs++;
return refs;}
int s12(){
refs--;
return refs;}
int s1284(){
return refs;}
};
#ifdef s1290
#define s1291(x) x;
#else
#define s1291(x)
#endif
template<bool>
struct s1285{
void s1286(){}
void s1287(){}
};
template<>
struct s1285<true>{
#ifdef s1290
static int s163;
void s1286() { s163++; }
void s1287() { s163--; }
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
int s1284(){
return refs;}
virtual void deallocate(){
delete this;}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template<class C, bool s1318=false>
class s1289
: public s1285<s1318>{
C* p;
s1283*	s1288;
public:
s1289(C *_p)
:p(_p){
if ( p ) {
s1288 = new s1283;
s1288->s11();
s1291( this->s1286() )}}
s1289( const s1289& ptr ){
if ( ptr.p ) {
p = ptr.p;
s1288 = ptr.s1288;
s1288->s11();}
else {
p = nullptr;
s1288 = nullptr;}}
s1289()
:p(nullptr){
s1288 = nullptr;}
template<class D> 
s1289( s1289<D> &pn ){
p = nullptr;
s1288 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1288 = pn.s1305();
s1288->s11();}}}
~s1289(){
if(	p && !s1288->s12()	) {
delete p;
delete s1288;
s1291( this->s1287() )}}
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1289& operator=( s1289<C> &s1346 ){
if ( p  && !s1288->s12() ) {
delete p;
delete s1288;
p = nullptr;
s1288 = nullptr;
s1291( this->s1287() )}
p = s1346.p;
if ( s1346.p ) {
s1288 = s1346.s1288;
s1288->s11();}
return *this;}
s1289& operator=( const s1289<C> &s1346 ){ return operator=((s1289<C>&) s1346); }
s1289& operator=( C* ptr ){
if ( p  && !s1288->s12() ) {
delete p;
delete s1288;
p = nullptr;
s1288 = nullptr;
s1291( this->s1287() )}
p = ptr;
if ( ptr ) {
s1288 = new s1283;
s1288->s11();
s1291( this->s1286() )}
return *this;}
template<class Base>
operator Base*(){
return checked_cast<C, Base>( p );}
template<class D>
s1289& operator=( s1289<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );}
template<class ToType>
ToType s15(){
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast(){
return dynamic_cast<ToType>( p );}
bool operator ==(const s1289<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1289<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1283* s1305() { return s1288; }
int s1284() { return s1288->s1284(); }
void s1340() { s1288->s11(); }
void s1339() {
if ( p  && !s1288->s12() ) {
delete p;
delete s1288;
p = nullptr;
s1288 = nullptr;
s1291( this->s1287() )}}
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
bool operator ==( const C& s349 )const { return ( *p == s349 ); }
bool operator !=( const C& s349 )const { return ( *p != s349 ); }
bool operator <( const C& s349 )const { return ( *p < s349 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1121();
extern std::vector<std::wstring> s996;
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
s875,
s25
};
s16( const std::wstring& s, uint32_t n = (uint32_t)s17::s19 )
: id( n ){
s26.push_back( s );}
s16( uint32_t n )
: id( n ){
s26.push_back( s996[n] );}
s16( const s16& right )
: id( right.id ){
s26.assign( right.s26.begin(), right.s26.end() );}
static void s29(){
s27 = (uint32_t)s17::s25 + 1;}
static uint32_t s28(){
return s27++;}
virtual std::wstring Msg( size_t s197 = 0 ) const{
std::wstring s685;
std::list<std::wstring>::const_reverse_iterator it = s26.crbegin();
std::wstring s1078( s197, L' ' );
while( it != s26.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s26.crend() )
s685 += s1078;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s685 += ( i++ ? L"" : s1078 ) + s + L"\n";}
return s685;}
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
bool s31( const std::wstring& _dir, const std::wstring& s524, std::wstring& s153 );
void s32( const std::wstring& _dir, const std::wstring& s524, std::vector<std::wstring>& s40,
std::vector<std::wstring>& s41 );
time_t s33( const std::wstring& f );
uint8_t s34( const std::wstring& f );
bool s724( const std::wstring& f );
bool s35( const std::wstring& s210 );
bool s36( const std::wstring& s210 );
std::wstring s37();
std::wstring s38();
std::wstring s39();
std::wstring s1884();
} // namespace s3
namespace s4 {
extern std::wstring s88;
extern std::wstring s48;
extern std::string s49;
extern std::wstring s50;
extern std::wstring digits;
enum s17 { s23 };
std::wstring s51( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s52( const std::wstring& s, const std::wstring& c );
bool s53( const std::wstring& s, const std::wstring& ss );
void s54( const std::wstring& s, size_t s65, wchar_t left, wchar_t right, 
size_t& start, size_t& end, bool s886 = false );
void s55( const std::wstring& s, size_t s65, wchar_t c, size_t& start, 
size_t& end );
void s1001( const std::wstring& s, size_t& s65, const std::wstring& s1090 );
size_t count( const std::wstring& s77, const std::wstring& s1090, size_t start, size_t end,
bool s886 = false );
int s56( const std::wstring& s77, wchar_t s72, size_t& pos );
void s57( const std::wstring& s, const std::wstring& s72, 
std::vector<std::wstring>& s153, bool clr = true, bool s886 = false );
void s289( const std::vector<std::wstring>& v, const std::wstring& s72, std::wstring& s153 );
std::wstring s71( const std::wstring& s77, size_t& pos );
void s58( const std::wstring& s77, const std::wstring& s72, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s59( const std::wstring& s77, const std::wstring& s72,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s60( const std::wstring& s77 );
void s61( std::wstring& s46 );
std::wstring s746( std::wstring path );
bool s62( const wchar_t *str, long *s349, wchar_t **end = NULL );
bool s1544( const wchar_t *str, long long *s349, wchar_t **end = NULL );
bool s1545( const wchar_t *str, unsigned long long *s349, wchar_t **end = NULL );
bool s63( const wchar_t *str, double *s349, wchar_t **end = NULL );
void s877( const std::wstring& s77, std::vector<std::wstring>& s153 );
std::wstring s1828( const std::wstring& s77, wchar_t c );
std::wstring s1253( const std::wstring& s, const std::wstring& chars );
std::string s51( const std::string& l, const std::string& s, const std::string& r );
std::string s52( const std::string& s, const std::string& c );
void s54( const std::string& s, size_t s65, char left, char right, 
size_t& start, size_t& end);
int s56( const std::string& s77, char s72, size_t& pos );
void s57( const std::string& s, const std::string& s72, std::vector<std::string>& s153 );
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
constexpr UINT rol(UINT s349, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s349 << n) | (s349 >> (sizeof(UINT)*8-n));}
void s64( const std::wstring& s78 );
void s81( std::wstring& s77, std::vector<std::wstring>& s1104, std::map<size_t, size_t>& s1037 );
template<class T>
std::wstring s1564( T value ) {
struct Numpunct : public std::numpunct<wchar_t> {
protected:
virtual wchar_t do_thousands_sep() const { return L','; }
virtual std::string do_grouping() const { return "\03"; }
};
std::wstringstream ss;
ss.imbue( { std::locale(), new Numpunct } );
ss << std::setprecision( 2 ) << std::fixed << value;
return ss.str();}
std::wstring s2187( void* );
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
#define s1561(x) s5::conv.to_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#define s1561(x) x
#endif
namespace consutils {
void s1117();
class s17{
static uint32_t s89;
public:
static void s29();
static uint32_t s90() { return s89; }
};
void s91( const std::wstring& header,
const std::vector<std::wstring>& s92 = { } );
void s96();
void s130( int s73 = 0 );
void s97( bool b = true );
bool s98( const std::wstring& s93 );
int s99( const std::wstring& s93, const std::vector<std::wstring>& s94 );
std::wstring s100( const std::wstring& s93, bool s95 = false );
std::wstring s101( const std::wstring& s93, bool s95 = false );
std::wstring getStringValHist( const std::wstring& s93,
const std::vector<std::wstring>& s102 );
int s103( const std::wstring& s93 );
size_t s104( const std::wstring& s93 );
void s105( int& w, int& h );
void s106( const std::vector<std::wstring>& v, std::vector<std::wstring>& s153,
size_t w, size_t h );
int s107( const std::vector<std::wstring>& v );
#ifdef __LINUX__
char _getch();
#endif
#define s108 372
#define s109 380
#define s110 375
#define s111 377
#define s112 27
#define s113 13
#define s116 224
#define s114 8
#define s115 383
#define s1558 371
#define s1557 379
} // namespace consutils
namespace s6{
enum s131{ s132, s133, s134, s139, 
s135, s136, s140, s137, s138 };
class s141;
class s143;
typedef s1::s9<s141> s142;
struct s1695{
bool s151;
std::wstring s1696;
std::wstring s1697;
bool s1700;
bool s1699;
bool s1701;
bool s1744;
bool s1732;
s1695( const std::wstring& dd=L".", const std::wstring& fs=L",", bool ab=false, bool rb=false,
bool sb=false )
: s151( true ), s1696(dd), s1697(fs), s1700(ab), s1699(rb),
s1701(sb), s1744( true ), s1732( false ) { }
};
extern s1695 s1757;
extern thread_local std::list<bool> s1769;
void s1698( const std::wstring& dd, const std::wstring& fs, bool ab, bool rb, bool sb );
void s1698( const s1695& cnf );
class s945
: public s1::s10{
std::wstring s194;
std::wstring s1114;
std::vector<std::wstring> s1115;
std::map<size_t, size_t> s1116;
size_t s1059;
public:
s1695 s1760;
s945( const std::wstring& file, bool s194 = true, const s1695& s1759=s1757 );
const std::wstring& Path() const { return s194;  }
void read( std::vector<s1::s9<s143>>& s153, 
const std::wstring& s190 = std::wstring(L"") );
void s170( const std::wstring& s77, size_t& pos, s1::s9<s143> s153 );
bool s1005( std::wstring& s, size_t s68, size_t s683, size_t& line ) const;
size_t s949() const { return s1059; }
};
typedef s1::s9<s945> s948;
class s143
: public s1::s10{
std::multimap<std::wstring, s142> s144;
s948 src;
public:
enum s145 { s146, s147, s148 };
enum s17 { s18, s149 };
const static s141 s150; // similar to string::npos
s143( const s945* pf ):src( (s945*)pf){}
void s154( const std::wstring& s77, const s1695& s1759 );
void s155( std::wostream* pd, bool s151=false ) const;
bool s156( const std::wstring& s152 ) const;
void s157( const std::wstring& s152, std::vector<s142>& s153 ) const;
const s142 s158( const std::wstring& s152 ) const;
void s159( const std::wstring& s76, s142 s349, s145 ap=s146 );
void s1631( const std::wstring& s76 );
void s160( std::vector<std::pair<std::wstring, s142>>& s153 ) const;
bool operator==( const s143& r )  const;
void s161( std::wostream* pd, int s197 ) const;
};
bool operator==( const std::vector<s1::s9<s141>>& l,
const std::vector<s1::s9<s141>>& r );
class s141
: public s1::s10{
s131 s198;
s143 obj;
std::wstring str;
std::vector<s1::s9<s141>> s162;
double s163;
bool b;
std::pair<size_t, size_t> s1082;
s948 s1081;
public:
s141():s198(s132),obj(NULL){}
s141( const std::wstring& s ):s198(s134),obj(NULL),str(s){}
s141( double d, s131 v = s136 );
s141( const std::vector<s142>& a ): s198(s135),obj(NULL),s162(a){}
s141( const s945* pf, const std::wstring& s77, size_t& pos, const s1695& s1759 );
s131 s164() const { return s198; }
bool s165() const { return s198 == s132; }
const s143& s166() const;
const std::vector<s142>& s167() const;
double s168() const;
int s56() const;
bool s728() const;
const std::wstring& s169() const;
const std::wstring& s865() const;
std::wstring s857() const;
bool s1009( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s945* s1006() const { return s1081.s15<s945*>(); }
bool operator==( const s141& r ) const{
return s198 == r.s198 && obj == r.obj && str == r.str && s162 == r.s162 && b == r.b && s163 == r.s163;}
bool is( const s141& r ) const{
return this == &r;}
void s161( std::wostream* pd, int s197 ) const;
void s155( std::wostream* pd, bool s151=false ) const;
};
class s1709{
s1695 conf;
public:
s1709() { }
s1709( const s1695& _cnf )
: conf( _cnf ) {}
s131 s1550( const std::wstring& s77, size_t& pos, double& s153 );
void s178( const s945* pf, const std::wstring& s77, size_t& pos, 
std::vector<s1::s9<s141>>& s153,
bool s151 = false, const std::wstring& s72 = L",");
};
void s171( const std::wstring& s194, 
const std::vector<s1::s9<s143>>& s195 );
void s178( const s945* pf, const std::wstring& s77, size_t& pos,
std::vector<s1::s9<s141>>& s153, const s1695& s1759 );
void s178( const s945* pf, const std::wstring& s77,
std::vector<s1::s9<s141>>& s153, const s1695& s1759 );
} // namespace s6
typedef const std::wstring s1905;
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s928 extern const uint32_t
#define s1690    1
#define s1691 2
#define s1692 3
#define s1693 4
#define s1694 5
namespace transd {
typedef uint32_t s1061;
typedef uint32_t traitnum_t;
typedef unsigned char tdbyte_t;
typedef std::basic_string<tdbyte_t> s1322;
namespace s7 {
s928 s1554;
s928 s1395;
s928 s1396;
s928 s1397;
s928 s1394;
s928 s1393;
s928 s1398;
s928 s1399;
DEFCONST s420;
DEFCONST s421;
DEFCONST s422;
DEFCONST s423;
DEFCONST s424;
DEFCONST s425;
DEFCONST s426;
DEFCONST s427;
DEFCONST s428;
DEFCONST s429;
DEFCONST s1629;
DEFCONST s430;
DEFCONST s431;
DEFCONST s432;
DEFCONST s833;
DEFCONST s433;
DEFCONST s434;
DEFCONST s435;
DEFCONST s765;
DEFCONST s749;
DEFCONST s795;
DEFCONST s436;
DEFCONST s437;
DEFCONST s832;
DEFCONST s940;
DEFCONST s1140;
DEFCONST s1356;
DEFCONST s1391;
DEFCONST s1392;
DEFCONST s1601;
DEFCONST s2139;
DEFCONSTI s866;
DEFCONSTI s438;
DEFCONSTI s439;
DEFCONSTI s440;
DEFCONSTI s441;
DEFCONSTI s442;
DEFCONSTI s867;
DEFCONSTI s868;
DEFCONSTI s1747;
DEFCONSTI s1199;
DEFCONST s1413;
DEFCONST s1524;
DEFCONST s1411;
DEFCONST s1410;
DEFCONST s1412;
DEFCONST s1409;
DEFCONST s1414;
DEFCONST s1408;
DEFCONST s443;
DEFCONST s444;
DEFCONST s445;
DEFCONST s446;
DEFCONST s447;
DEFCONST s448;
DEFCONST s449;
DEFCONST s450;
DEFCONST s451;
DEFCONST s452;
DEFCONST s2161;
DEFCONST s453;
DEFCONST s454;
DEFCONST s455;
DEFCONST s456;
DEFCONST s2169;
DEFCONST s457;
DEFCONST s459;
DEFCONST s458;
DEFCONST s460;
DEFCONST s461;
DEFCONST s462;
DEFCONST s1374;
DEFCONST s1982;
DEFCONST s769;
DEFCONST s803;
DEFCONST s1572;
DEFCONST s829;
DEFCONST s1124;
DEFCONST s1373;
DEFCONST s463;
DEFCONST s464;
DEFCONST s465;
DEFCONST s466;
DEFCONST s467;
DEFCONST s468;
DEFCONST s469;
DEFCONST s739;
DEFCONST s470;
DEFCONST s936;
DEFCONST s1983;
DEFCONST s2160;
DEFCONST s1989;
DEFCONST s1990;
DEFCONST s1991;
DEFCONST s1992;
DEFCONST s1988;
DEFCONST s1993;
DEFCONST s1994;
DEFCONST s1997;
DEFCONST s1996;
DEFCONST s1995;
DEFCONST s915;
DEFCONST s914;
DEFCONST s916;
#define s419 3
#define s1118 L','
DEFCONST s418;
DEFCONST s1106;
#define s1559 1
#define s1560	2
s928 s1365;
s928 s1300;
s928 s924;
s928 s923;
s928 s1299;
s928 s1129;
s928 s918;
s928 s1107;
s928 s919;
s928 s1108;
s928 s1109;
s928 s1110;
s928 s920;
s928 s921;
s928 s922;
s928 s1126;
s928 s1127;
s928 s1366;
s928 s1367;
s928 s1368;
s928 s1597;
s928 s1128;
s928 s1296;
s928 s1298;
s928 s1297;
s928 s1667;
s928 s1668;
s928 s1378;
s928 s1669;
s928 s1376;
s928 s1377;
s928 s1670;
s928 s1522;
s928 s1523;
s928 s1555;
s928 s1687;
s928 s1599;
s928 s1904;
s928 CLObjectVal_ctor1;
s928 s1598;
s928 s1688;
s928 s1702;
s928 s1892;
s928 s1937;
s928 s1936;
s928 s2159;
extern std::set<std::wstring> s1123;
} // namespace s7
enum s224 { s225, s226, s227, s228 };
extern std::wstring s229[];
extern const std::wstring s230, s231, s232,				s821,
s233,  s234,     s235,    s236,      s237,
s238,  s239, s240, s241,s244,
s242, s243,			s258,	s245,			s257,
s246, s247,     s249,		s751,
s250,   s251, s252, s253,			s254,
s255, s256,		s259,	s900,			s261,
s260,	 s818,			s759, s852, 	s772,
s853,  s1317, s1620, s1316, s1428, 
s1944,	 s1886,    s1945, s1943,
s1562,  s1616,  s1615, s1614,
s1619, s1617, s1618, s1427, s2078;
#define s2101		1
#define s2100		2
#define s2102		3
#define s2191  4
class s262;
class s263;
class s270;
class s271;
class s272;
typedef s270* ( *s273 )( const std::wstring& s278, const std::vector<s271*>& s274 );
typedef s1::s9<s263> s947;
extern const s6::s141 s265;
class s263
: public s1::s10{
public:
typedef std::multimap<std::wstring, s947> s275;
typedef std::map<size_t, s6::s141> s264;
private:
static std::map<std::wstring, s273> s276;
std::wstring s277;
std::wstring s1674;
s224 s279;
std::wstring s280;
s275 s281;
std::wstring src;
s6::s142 s1053;
s264 s266;
s1061 s1350{};
s263* s2107;
s263* s2112;
void s282( s1905& s77 );
void s283( const s6::s143& s133 );
void s284( s1905& s77 );
void s285( s1905& s77 );
void s286( s1905& s340, const s6::s141& obj );
void s1003( s1905& s );
static std::wstring s287( s1905& s77, size_t &pos );
public:
enum s17 { s18, s149 };
s263(){ }
s263( s224 at, s1905& qpre, s1905& s76 )
: s277( qpre ), s1674( s76 ), s279( at ), s2107( NULL ), s2112( NULL ){ }
s263( s1905& s76, s1905& s349 )
: s1674( s76 ), s279( s225 ), s280( s349 ), s2107( NULL ), s2112( NULL ){ }
s263( s1905& s340, const s6::s141* s1053, s263* s2108 );
s263( s1905& s76, const s6::s141& s296, s263* s592 );
s263( const s6::s143& s133 );
~s263();
s224 s297() const { return s279; }
void s1872( s224 t ) { s279 = t; }
std::wstring s298() const;
s1905& s299() const { return s1674; }
s1905& Src() const { return src; }
const s6::s141* Nqj() const { return s1053.s15<s6::s141*>(); }
s263* s2098() { return s2107; }
s263* s2099() { return s2112; }
const s6::s141& s268( size_t s2106 ) const;
const s6::s141& s2116( size_t s2106 ) const;
void s269( size_t s2106, const s6::s141& s267 );
void s2123( const s263& s701 );
s1061 s1309() const { return s1350; }
void s1344( s1061 t) { s1350 = t; }
void reset();
static void s288( s1905& s77, size_t& pos, std::vector<std::wstring>& s153 );
void s289( s6::s143& s133, size_t s2194 );
void s286( s263* node );
void s290( s262* s300, size_t s301 = 0 );
s1905& s291() const { return s280; }
const s263* s292( s1905& s278 ) const;
bool s156( s1905& s278 ) const;
s275& s293() { return s281; }
const s275& s293() const { return s281; }
void s294( s1905& s ) { s1674 = s; }
void s1768( s1905& s ) { s280 = s; }
static std::wstring s295( const s6::s143& obj,
s1905& dfault = std::wstring( L"" ) );
static std::wstring s302( const s6::s143& obj,
s1905& s303,	s1905& dfault = std::wstring( L"" ) );
void s304( std::wostream* pd, int s197 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s944{ s1043, s1042, s1044, s1045, s1041 };
class Msg{
std::wstring func;
std::wstring file;
s944 type;
std::wstring s78;
public:	
Msg( const std::wstring& s, s944 t = s1041 )
: type( t ), s78( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s944 t = s1041 )
: func( f ), file( fi ), /*line( n ),*/ type( t ), s78( s ) {}
s944 s352() const { return type; }
const std::wstring& Text() const { return s78; }
};}
namespace transd {
class s1105{
std::vector<s8::Msg> s26;
size_t s997;
public:
s1105() : s997(0){}
void s971( const std::wstring& s78 );
void s971( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
void s973( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
size_t s934() const { return s997; }
};
extern s1105 s1014;
extern std::vector<std::wstring> s1085;
extern std::vector<std::wstring> s994;
class TDException
: public s2::s16{
public:
enum class Stage : uint32_t{
s1031 = 0,
s1024,
s1029,
s1028,
s1023,
s1025,
s1026,
s1027,
s1030
};
private:
Stage stage;
uint32_t category;
std::wstring s1087;
s947 s701;
public:
TDException( uint32_t cat, uint32_t id, const s263* s701 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s263* s701, const s16& e );
TDException( uint32_t cat, uint32_t id, const s263* s701, const std::wstring& s78 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s197 = 0 ) const override;
std::wstring s2170( size_t idx ) const;
uint32_t Category() const { return category;  }
void s1076( Stage st ) { stage = st; }
TDException* s1000( const std::wstring& s = std::wstring( L"" ) );
static std::wstring s1912( const s263& s701 );
};
class s927
: public s2::s16{
public:
enum class s17 : uint32_t{
s983 = ((uint32_t)s16::s17::s25) + 1,
s1067,
s1050,
s974,
s984,
s1016,
s1019,
s25
};
s927( const std::wstring& s )
: s16( s, (uint32_t)s17::s983){}
s927( s16& e, const s263& s701, s17 code );
};
class s935
: public s2::s16{
public:
enum class s17 : uint32_t{
s1049 = ( (uint32_t)s16::s17::s25 ) + 1,
s999,
s25
};
s935( s17 code );
s935( const std::wstring& s, s17 code )
: s16( s, (uint32_t)code ) {}
};
#define s932		1
#define s931		2
#define s933						3
#define s929					4
#define s930				5
#define s1132		6
#define s1131		7
#define s1379		8
#define s1556	9
#define s1671			10
#define s953(x) throw s954( L"unknown syntax: " + x );
#define s952(x) throw s954( L"syntax error: " + x );
namespace lang {
bool s656( const std::wstring& s, bool s714 = true );
} // namespace tdlang
extern const std::wstring s471;
enum s472 { s473, s474, s475, s1337, s476, s1245, s1246, 
s477, s478, s479, s480, s481, s1063, s2166 };
enum s1999 { s2047 = 0, s2048, s2046, s2045 };
enum s1998 { s2054 = 0, s2050, s2051, s2052, s2053 };
enum s2193 { s2204, s2200, s2203, s2205, s2201, s2202 };
#define s1984 5
class s262;
class s482;
class s483;
class s272;
class s591;
class s271;
class s561;
class Stream;
typedef s271 s484;
typedef s271 TDType;
typedef s1::s9<s484> s485;
typedef s1::s9<s483> s486;
typedef s1::s9<s272> s487;
typedef s1::s9<s591> s488;
class s813;
typedef std::map<std::wstring, std::vector<std::wstring>> s926;
extern s926 s993;
class s271
: public s1::s10{
friend class s491;
s947 s976;
protected:
s472 s492;
s1061 s493;
s262* s300;
int wh;
public:
s271( const s263* ast_=NULL ) : s976( (s263*)ast_ ), s492( s473 ), s493( 0 ), 
wh( s7::s868 )  { }
s271( s472 pt_, const s263* ast_=NULL ) : s976( (s263*)ast_ ), s492( pt_ ), s493( 0 ), 
wh( s7::s868 ) { }
s271( s262* pass_, s472 pt_, const s263* ast_=NULL ) : s976( (s263*)ast_ ), s492( pt_ ),
s493( 0 ), s300( pass_ ), wh( s7::s868 )  { }
s271( const s271& r ) : s976( r.s976 ), s492( r.s492 ), s493( r.s493 ),
s300( r.s300 ), wh( r.wh ) {}
virtual ~s271();
s472 s494() const { return s492; }
const s263* s603() const { return s976.s15<s263*>(); }
virtual s483* s496();
virtual s486 s497( s483** s274 = NULL, size_t s498 = 0 );
virtual s1061 s352() const { return s493; }
const s813& s1196() const;
virtual const std::wstring& s353() const;
virtual void s351( s1061 type );
s262* Pass() const  { return s300; }
int s618() const { return wh; }
void s1679( int i ) { wh = i; }
void s1262() { wh = 0; }
void s1260(bool b = true) { if(b) wh |= (1 << (s7::s1199-1)); 
else wh &= ~(1 << (s7::s1199-1));}
bool s1204() const { return wh >= 0; }
virtual bool s1203() const { return (wh > 0) && (wh & (1 << (s7::s1199-1))); }
virtual void s2198( s2193 st ) { }
virtual bool s501( const s483* s502 ) const;
virtual bool s1541( s1061 tp ) const;
virtual const s926& s1004() const { return s993;  }
virtual void s500( const s272* s879, bool b = true );
virtual void release() {}
virtual const s483* s503() const;
virtual s271* s335( s591* s2057, s272* impl ) const;
virtual void s2133( s483* s2124, bool s2176 = true ) { }
static void s1333( const s263& ast_, s262* s300, s272* obj,
s1905& s334, std::vector<s271*>& s153 );
static s271* s504( const s263& s701, s262* s300, s272* obj,
s1905& s334, bool s2176 = false );
static s271* s1018( s262* s300, s271* par, s272* obj, s591* s215,
s1905& s334, bool proc );
static s485 s1017( const std::wstring& s77, const s263* ast_, s262* s300, 
s272* s588 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring( uint32_t s1565 = 0 ) const;
virtual s1322 to_bytes() const;
virtual void to_null();
virtual std::wstring trace( const char* topics ) const { return L""; }
virtual void s304( std::wostream* pd, int s197 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s484*> s505;
s484* s1120( s505& m, const std::wstring& s152 );
void s670( const std::wstring& s, std::wstring& s1112, std::wstring& s601 );
class s483;
class s371;
class s483
: public s271{
protected:
s272* ns;
s483* s1703( s483** s274, size_t s498 );
s483* s1894( s483** s274, size_t s498 );
s483* s1938( s483** s274, size_t s498 );
virtual s483* s1896( s483** s274, size_t s498 );
public:
s483( s262* s300, s472 pc, const s263* ast_, s272* ns_ ) 
: s271( s300, pc, ast_ ), ns( ns_ ) { }
s483( const s483& r );
virtual ~s483();
virtual void s350() = 0;
virtual s1061 s386( const std::wstring& s343 ) const = 0;
virtual s483* s354( const s263& s701, s272* s588, s1905& s334 ) const = 0;
virtual s483* s355( s272* s588, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const = 0;
virtual s483* s355( s272* s588, const std::vector<s1061>& vt ) const;
virtual std::wstring s298() const;
virtual std::wstring s834() const;
std::wstring s2171() const;
virtual s483* s344( s1905& s278, s1905& s334,	bool s520 = true, bool s2167 = true ) const 
{	return NULL;}
virtual s591* s1685( s1905& s278, s591* s215,	s561* cs ) const;
virtual void s356( s271* p ) const = 0;
virtual s483* s1536( const s483* p ) const;
virtual const s483* s503() const override = 0;
void s506( s1905& s ) { }//{ s372 = s; }
std::wstring s1673() { return L""; }// s372;}
virtual size_t s322() const = 0;
virtual bool operator==( const s483* p ) const = 0;
virtual bool operator<( const s483* p ) const = 0;
s483* s1895( s483** s274, size_t s498 );
s486 s497( s483** s274, size_t s498 ) override { return this; }
s483* s496() override;
virtual bool s556( s1905& s278, s371* s153, s1905& s334, bool fr ) const	{	return false;	};
virtual s271* s598( size_t off )	{	return NULL; }
virtual s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const;
virtual void s1935( Stream* ) const;
virtual void s1959( Stream* );
virtual void s1960( s1905& s );
};
enum s536 { s509, s510, s511 };
enum s512 { s513, s514, s515 };
typedef s1::s9<s813> s826;
typedef const s813* s925;
class s813
: public s1::s10{
public:
typedef s1061 s737;
typedef s737 s893;
typedef std::vector<s737> Cont;
private:
Cont vt;
size_t s1095;
public:
s813() {}
s813( s737 t1, s737 t2 = (s737)-1, s737 t3 = (s737)-1 );
s813( const s813& right );
s813( const Cont& v );
void s351( s737 t );
void s351( s925 pt );
void s785( s737 t );
void s785( s925 pt );
s893 s352( size_t n = 0 ) const;
const Cont& s819() const { return vt; }
void s819( std::vector<s271*>& s153 ) const;
bool operator==( const s813& p ) const;
size_t s322() const { return s1095; }
};
class s482;
class s262;
struct s965{
std::size_t operator()( const s813& k ) const{
return k.s322();}
};
struct s966{
std::size_t operator()( const s813& l, const s813& r ) const{
return l.operator==( r );}
};
class s491{
typedef std::map<std::wstring, s1061> s960;
typedef std::unordered_map<s813, s1061, s965, s966> s963;
typedef std::map<std::wstring, std::list<std::wstring>> s1790;
typedef std::map<std::wstring, std::set<std::wstring>> s913;
typedef std::map<s813::s893, s913> s926;
typedef std::map<std::wstring, traitnum_t> s1154;
typedef std::unordered_map<traitnum_t, std::wstring> s1248;
std::vector<s486> s1113;
std::vector<std::wstring> s1096;
std::vector<s813> s1101;
s960 s1097;
s963 s1102;
s1790 s1841;
s926 s917;
s1154 s892;
s1248 s1259;
traitnum_t s1205;
std::vector<traitnum_t>s1274;
std::vector<s1061>s1511;
std::vector<std::vector<s1061>> s1551;
s262* s300;
s1061 s1068( const s813::Cont& v, s1905& s347 );
void s1171( s1905& alias, s1905& s347, s1905& s1840 );
public:
s491( s262* pass_ );
void reset();
void s290();
void s517( const s482& st );
s1061 s218( s483* p, s1905& s347 );
void s1666( s1905& s347 );
void s1878( s1905& s1112 );
s1061 s1046( const s813::Cont& v );
traitnum_t s1252( s1905& trait, s1061& s1510 );
void s1162( s813::s893 type, s1905& trait, s1061& s1510 );
bool s1198( s1061 s619, traitnum_t tra );
bool s1465( s1061 s619, s1061 alias );
traitnum_t s1155( s1061 s619 ) const { return s1274[s619]; }
traitnum_t s1458( s1061 alias ) const;
void s1533( s1061 s619, s1061 is );
bool s1534( s1061 s619, s1061 is );
s483* s518( const s6::s141& s349, s272* s588, s1905& s519 );
s483* s518( const s263& s701, s272* s588, s1905& s519 );
s483* s518( s1061 type, s272* s588, s1905& s519 );
const s483* get( s1905& s76, bool s520 = true ) const;
s1061 s1010( s1905& s347, bool s520=true ) const;
s1061 s1011( const s813& vt, bool s520=true ) const;
const s813& s1013( s1061 t ) const;
const s483* s1007( s813::s893 t ) const;
s1905& s804( s1061 n ) const;
bool s156( s1905& s76 ) const;
void s790();
bool s1249();
double s1251();
int s1257();
void s304( std::wostream* pd, int s197 = 0 ) const;
static void s2119( const s813::Cont& v, size_t& idx, s813::Cont& s153 );
static void s1008( const s813::Cont& v, std::vector<size_t>& s2134,
s813::Cont& s153 );
size_t s1056( s1905& s, size_t& pos, s813::Cont& s153 );
std::wstring s1012( const s813::Cont& tp );
static std::wstring s1352( s1905& tn );
std::wstring s1275( s1905& tn, s1905& s1112 );
void s2137( const s813::Cont& v_, s813::Cont& s153, size_t s2117 = 0 );
};
class s521
: public s1::s10{
std::vector<std::wstring> s522;
s512 pv;
public:
s521() : pv( s513 ) { }
s521( s512 pv, const std::vector<std::wstring>& s523 );
s521( s1905& ag, s1905& s77 );
s512 s560( s1905& s499 ) const;
static std::vector<std::wstring> s525;
};
class s526
: public s1::s10{
typedef std::map<std::wstring, s521*> s527;
s527 s528;
public:
s526( ) { }
void s529( s512 pv, s263* );
void s530( s1905& s, s521& pl );
void s531( s1905& s, s1905& s524 );
s512 s532( s1905& mem, s1905& s499 );
void s533( s1905& s334,
std::vector<std::wstring>& s153 );
};
class s482{
public:
enum s145 { s146, s534, s147, s148 };
typedef std::map<std::wstring, s485> s535;
private:
s535 s553;
s536 s537;
s526* s539;
bool s538( s1905& s76, s145 ap = s146 );
public:
s482( ): s537( s510 ), s539( NULL ) {}
s482( s536 am ) : s537( am ), s539( NULL ) {}
s482( const s482& s540 );
~s482();
const s535& Table() const { return s553; }
void s500( s272* s499, bool s516 = true );
void s1649();
void reset();
void s541( s1905& s76, s271* sym, s145 ap = s146 );
void s541( s1905& s76, s6::s142 s349, s145 ap = s146 );
void s542( s1905& s76 );
void s543( const s6::s143& obj, s145 ap = s146 );
void s289( const s482& t, s145 ap = s146 );
bool empty() const { return s553.empty(); }
bool s156( s1905& s76 ) const;
s483* get( s1905& s76, bool s520 = true ) const;
void s544( std::vector<std::wstring>& s153 ) const;
void s545( std::vector<std::wstring>& s153 ) const;
void s546( std::vector<std::wstring>& s153 ) const;
void s547( const s482& t, std::vector<std::wstring>& s153 ) const;
bool implements( const s482& t ) const;
void copy( s482& t, s272* s588, s591* s587, s145 ap = s146 ) const;
void s548( s482& t ) const;
void s1613( s482& t ) const;
void s549( s512 pv, s263* s79 );
void s533( s1905& s334,
std::vector<std::wstring>& s153 );
bool s550( s1905& s278, s1905& s334 ) const;
std::wstring to_wstring( uint32_t s1565 ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
class s551{
typedef std::pair<s483*, std::wstring> s552;
typedef std::multimap<std::wstring, s552> s535;
s535 s553;
std::vector<std::wstring> s559;
std::wstring s334;
public:
s551();
void s554( s1905& s76 );
bool s2180( s1905& s76 );
void s500( s262* s300, s1905& s558 );
void s1649( s262* s300 );
void s555( s1905& s76, s262* s300, s1905& s558 );
bool s556( s1905& sym, s371* ref );
void copy( s551& t ) const;
};
extern s1::s9<s526> s557;
class s262;
class s336;
typedef void ( *s616 )( s483** s274, size_t n );
namespace s1512 {
extern s1061 s1271;
extern s1061 s1549;}
class s1122{
s336* s588;
std::vector<s1061> s1278;
std::vector<s485> s912;
public:
s1122() : s588( NULL ) {}
s1122( const std::vector<s485>& v, s336* s592 /*= NULL*/ );
s1122( const std::vector<s1061>& v, s336* s592 = NULL )
: s588( s592 ), s1278( v ) {}
bool operator==( const s1122& s524 ) const;
bool operator<( const s1122& s524 ) const;
const s336* Subj() const { return s588; }
const std::vector<s485>& s602() const { return s912; }
std::wstring s1329( s262* s300 ) const;
};
struct s2000{
s1061
Bool,
Byte,
ByteArray,
ByteStream,
Char,
DateTime,
s414,
Double,
s361,
FileStream,
Filter,
HashIndex,
Index,
Int,
Lambda,
Long,
No,
Null,
s272,
Position,
Range,
Seq,
String,
s789,
Table,
TSDBase,
Tuple,
s1528,
s748,
Vector;
s2000() {
Bool = Byte =	ByteArray =	ByteStream = Char =	DateTime = s414 = Double =	s361 =
FileStream = Filter =	HashIndex =	Index =	Int =	Lambda = Long =	No = Null = s272 =
Position = Range = Seq = String = s789 = Table = TSDBase = Tuple = s1528 =
s748 =	Vector = 0;}
const s483* operator()( s262* s300, s1061 tp );
};
extern s2000 Types;
struct s1142{
s1061 s338;
s616 s339;
bool s1168;
const std::vector<s1998>* s2035;
s1142()
: s338( 0 ), s339( NULL ), s1168( true ), s2035( NULL ) {}
s1142( s1061 pt, s616 fp, bool s1169 = true, 
const std::vector<s1998>* s2008 = NULL )
: s338( pt ), s339( fp ), 
s1168( s1169 ), s2035( s2008 ) {}
};
class s336
: public s483{
public:
class s337{
std::wstring s278;
s1061 s338;
s616 s339;
std::vector<s1122> s1163;
size_t s1038, s1035;
std::vector<std::wstring> s1209;
bool s1179;
bool s1168;
std::vector<s1998> s2044;
public:
enum class s1133 : uint32_t { s1180 = ((uint32_t)s2::s16::s17::s25) + 1 };
s337( const std::wstring& s676, s616 fp, s1061 s340,
const std::vector<s1122>& v=std::vector<s1122>(), 
size_t s1039 = 0, size_t s1036=(size_t)-1, bool s1169 = true,
const std::vector<std::wstring>& s1208 = std::vector<std::wstring>(),
const std::vector<s1998>& s2009 = { s2054 } )
: s278( s676 ), s338( s340 ), s339( fp ), s1163(v), 
s1038(s1039), s1035(s1036), s1209( s1208 ), s1179(false), 
s1168( s1169 ), s2044( s2009 ) {}
s337( const std::wstring& s676, s616 fp, s1061 s340,
const std::vector<s1122>& v, 
bool s1169, const std::vector<s1998>& s2009 )
: s278( s676 ), s338( s340 ), s339( fp ), s1163(v), 
s1038(0), s1035(0), s1179(false), 
s1168( s1169 ), s2044( s2009 ) {}
s337()
: s339( NULL ), s1179( false ), s1168( true ), s2044( { s2054 } ){}
s616 s1136() const { return s339; }
size_t s943() const { return s1038;  }
size_t s942() const { return s1035;  }
const std::vector<std::wstring>& Markers() const { return s1209; }
s1061 s495() const { return s338; }
void s1263( s1061 t) { s338 = t; }
void s1261( bool b ) { s1179 = b; }
bool s1186( ) const { return s1179; }
bool s1203() const { return s1168; }
const std::vector<s1998>* s2017() const { return &s2044; }
bool s1166( const s1122& s691 ) const;
};
protected:
typedef std::multimap<std::wstring, s337*> s341;
virtual const s341& s342() const = 0;
static size_t s758;
public:
s336( s262* s300, s272* ns_, const s263* ast_ ) : s483( s300, s474, ast_, ns_ ) {}
s336( const s336& r ) : s483( r ) {}
virtual ~s336() {}
s1061 s386( const std::wstring& s343 ) const override;
static void s784( s262* s300, bool soft = false );
static size_t s807() { return s758;  }
virtual const std::vector<std::wstring>& s1191( s1905& s343 ) const;
virtual s1142 s1197( s1905& s343 ) const;
virtual s1142 s1192( s1905& s343, s1122& ap ) const;
virtual s1142 s1187( s1905& s343, s1122& ap );
const s483* s503() const override;
virtual void* addr() = 0;
s486 s497( s483** s274, size_t s498 ) override;
static s483* s345( s262* s300, const std::wstring& s349, const std::wstring& s334 );
void s1535( s483* s42 );
};
class s358
: public s336{
static s341 s348;
double s349;
static void s1236( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s388( s483** s274, size_t n );
static void s389( s483** s274, size_t n );
static void s390( s483** s274, size_t n );
static void s391( s483** s274, size_t n );
static void s392( s483** s274, size_t n );
static void s393( s483** s274, size_t n );
static void s394( s483** s274, size_t n );
static void s395( s483** s274, size_t n );
static void s396( s483** s274, size_t n );
static void s397( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s399( s483** s274, size_t n );
static void s400( s483** s274, size_t n );
static void s401( s483** s274, size_t n );
static void s402( s483** s274, size_t n );
static void s403( s483** s274, size_t n );
static void s410( s483** s274, size_t n );
static void s411( s483** s274, size_t n );
static void s404( s483** s274, size_t n );
static void s406( s483** s274, size_t n );
static void s407( s483** s274, size_t n );
static void s412( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s1978( s483** s274, size_t n );
static void s1977( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef double s1386;
s358( s262* s300 ) : s336( s300, NULL, NULL ) {}
s358( const s358& r );
s358( s262* s300, const std::vector<s271*>& l );
s358( s262* s300, double d );
s358( s262* s300, const std::wstring& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void s500( const s272* s587, bool b = true ) override;	
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
double* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0.0; }
operator int() const override { return (int)s349; }
operator double() const override { return s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void s1960( s1905& s ) override;
void s1959( Stream* ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s360
: public s336{
static s341 s348;
bool s349;
static void s387( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s360( s262* s300 ) : s336( s300, NULL, NULL ) {}
s360( s262* s300, bool b );
s360( s262* s300, const std::wstring& s, size_t& pos );
s360( const s360& right );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
bool* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
operator bool() const override { return s349; }
operator int() const override { return (int)s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void s1960( s1905& s ) override;
void s1959( Stream* ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s360> s369;
extern s1::s9<s360> s370;
class s361
: public s336{
static s341 s348;
static void s792( s483** s274, size_t n );
static void s508( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
std::wstring s78;
public:
s361( const s361& right );
s361( s262* s300, const std::wstring& s = std::wstring( L"" ) );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
s1905& Msg() const { return s78; }
void s363( const std::wstring& s ) { s78 = s; }
void* addr() override { return (void*)0; }
void s500( const s272* s587, bool b = true ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override { return s78; }
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s364
: public s336{
static s341 s348;
void s350() override {}
const s341& s342() const override { return s348; }
public:
s364( s262* s300 );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override { }
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override {	return L"";	}
operator double() const override { return (double)0; }
operator int() const override { return 0; }
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s364> s365;
class s384
: public s336{
traitnum_t s1272;
static s341 s348;
void s350() override {}
const s341& s342() const override { return s348; }
public:
s384( s262* s300, s272* ns = NULL, traitnum_t tn = 0, s472 pc = s473 );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
s271* s335( s591* s2057, s272* impl ) const override;
bool s501( const s483* s502 ) const override;
bool s1541( s1061 tp ) const override;
traitnum_t s1540() const { return s1272; }
void* addr() override { return (void*)0; }
void s356( s271* p ) const override { }
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s500( const s272* s587, bool b = true ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1706
: public s336{
public:
enum s1705 { s1741, s1740, s1739, s1742, s1823 };
typedef std::chrono::steady_clock s1794;
typedef std::chrono::system_clock s1795;
private:
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s387( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1849( s483** s274, size_t n );
static void s1873( s483** s274, size_t n );
s1705 s1743;
std::tm s349;
s1795::time_point s1875;
static std::wregex s1765, s1767, s1766, s1863;
bool s1728( const std::wstring& s349, std::tm& t, s1705& s619 ) const;
public:
s1706( s262* s300 );
s1706( s262* s300, const std::wstring& s );
s1706( s262* s300, const std::tm& _t, s1705 s619 );
s1706( const s1706& right );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1960( s1905& s ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1602 
: public s336{
friend class s776;
s482 s628;
static s341 s348;
std::wstring s1645;
static void s1236( s483** s274, size_t n );
static void s1641( s483** s274, size_t n );
static void s1639( s483** s274, size_t n );
static void s1636( s483** s274, size_t n );
static void s1637( s483** s274, size_t n );
static void s1660( s483** s274, size_t n );
static void s1662( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1602( s262* s300 ) : s336( s300, NULL, NULL ) {}
s1602( s262* s300, s272* s588, s1905& s77, bool typed=true, const s263* ast_=NULL );
s1602( const s1602& right, s483* s2124 );
s1602( s262* s300, s272* s588, const s6::s143* s1644, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const override;
void* addr() override { return (void*)&s628; }
void s500( const s272* s879, bool b = true ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void load( const std::wstring& s77, bool typed, bool s194 );
void s1642( const s6::s143* ob, bool typed, s482::s145 ap = s482::s146 );
void s1632( s482::s535& st ) const;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1960( s1905& s ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s384> s872;
extern s1::s9<s384> s366;
extern s1::s9<s384> s367;
extern s1::s9<s384> s368;
extern s1::s9<s384> s873;
extern s1::s9<s384> s2146;
extern s1::s9<s384> s1686;
extern s1::s9<s384> s1521;
#define s1152 Types.Null
#define s1148 Types.Bool
#define s1308 Types.Byte
#define s1579 Types.Char
#define s1151 Types.Int
#define s1150 Types.Double
#define s1526 Types.Long
#define s1527 Types.s1528
#define s1153 Types.String
#define s1149 Types.ByteArray
#define s1719 Types.Vector
#define s1718 Types.s748
#define s1715 Types.Index
#define s1717 Types.Tuple
#define s1714 Types.HashIndex
#define s1580 Types.Position
#define s1713 Types.DateTime
#define s1716 Types.Lambda
#define s1798 Types.TSDBase
#define s1797 Types.Table
#define s1907 Types.s414
#define s1415 Types.Range
#define s1909 Types.Filter
#define s1416 Types.Seq
#define s1910 Types.s789
#define s1906 Types.ByteStream
#define s1908 Types.FileStream
#define s1147 ( std::numeric_limits<size_t>::max )( )
#define U64_MAX ( std::numeric_limits<uint64_t>::max )( )
typedef s358 TDDouble;
class s371
: public s271{
std::wstring s372;
s485 s373;
const s483* s374;
std::vector<size_t> s375;
size_t s376;
bool s1168;
public:
s371( s1905& s, s262* s300, s472 cat = s473, bool _cnst = false );
s371( const s371& right, s483* s2184 = NULL );
void reset();
s483* s496() override;
const s483* s503() const override { return s374; }
const s485 s381();
bool s1203() const override { return s1168; }
void s1260() { s1168 = true; }
const std::wstring& s617() const { return s372; }
s486 s497( s483** s274, size_t s498 ) override;
s483* s377() const;
s483* s378();
size_t s1304() const { return s376; }
void s379( size_t off, const s483* proto );
void s1343( s371* ptr );
size_t s380() const { return s376; }
uint32_t Id() const { return (uint32_t)s376; }
s271* s335( s591* s2057, s272* impl ) const override;
void s2133( s483* s2124, bool s2176 ) override;
void s500( const s272* s587, bool fr = true ) override;
void s382( s483* p );
void s383( s483* p ) { s374 = p; }
void s982( const std::vector<std::wstring> &v );
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1600
: public s483{
s486 pobj;
protected:
virtual s483* s354( const s263& s701, s272* s588,
s1905& s334 ) const override {	return NULL; }
public:
s1600( s262* s300 )
: s483( s300, s1337, NULL, NULL ) {}
virtual ~s1600() { }
void s1661( s483* obj ) { pobj = obj; }
s486 s2118( ) { return pobj; }
s271* s598( size_t off ) override 
{ return pobj->s598( off ); }
void s350() override {}
s1061 s386( const std::wstring& s343 ) const override { return 0; }
s483* s355( s272* s588, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const override { return NULL;	}
void s356( s271* p ) const override {}
s483* s1536( const s483* p ) const override { return NULL; }
const s483* s503() const override { return NULL; }
size_t s322() const override { return 0;  }
bool operator==( const s483* p ) const override { return false; }
bool operator<( const s483* p ) const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s1::s9<s371> s489;
typedef s1::s9<s1600> s2172;
struct s1720{
std::wstring s1697;
std::wstring rowSep;
std::wstring s1734;
std::wstring s1735;
bool stringsQuoted;
bool promInts;
bool mixedTypes;
bool s1826;
bool s2014;
s1720()
: s1697( L"," ), rowSep( L"\n" ), s1735( L"." ), stringsQuoted( false ),
promInts( false ), mixedTypes( false ), s1826( false ), s2014( false )	{	}
s1720( const std::wstring& fs, const std::wstring& rs, const std::wstring& cn,
const std::wstring& dp, bool sq, bool pi, bool mt )
: s1697( fs ), rowSep( rs ), s1735( dp ), stringsQuoted( sq ),
promInts( pi ), mixedTypes( mt ), s1826( false ), s2014( false )	{	}
};
extern s1720 s1738;
extern s6::s1695 s1736;
template<class s1312, class Der>
class s1306 :
public s336{
protected:
typedef Der s1167;
s1312 s349;
static s341 s348;
static void s387( s483** s274, size_t n );
static void s388( s483** s274, size_t n );
static void s389( s483** s274, size_t n );
static void s390( s483** s274, size_t n );
static void s391( s483** s274, size_t n );
static void s392( s483** s274, size_t n );
static void s404( s483** s274, size_t n );
static void s393( s483** s274, size_t n );
static void s394( s483** s274, size_t n );
static void s395( s483** s274, size_t n );
static void s396( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s399( s483** s274, size_t n );
static void s400( s483** s274, size_t n );
static void s401( s483** s274, size_t n );
static void s402( s483** s274, size_t n );
static void s403( s483** s274, size_t n );
static void s2097( s483** s274, size_t n );
static void s1966( s483** s274, size_t n );
static void s1965( s483** s274, size_t n );
static void s405( s483** s274, size_t n );
static void s406( s483** s274, size_t n );
static void s407( s483** s274, size_t n );
static void s408( s483** s274, size_t n );
static void s412( s483** s274, size_t n );
static void s1596( s483** s274, size_t n );
static void s1547( s483** s274, size_t n );
static void s1548( s483** s274, size_t n );
static void s1501( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
void s350() override;
const s336::s341& s342() const override;
public:
typedef s1306<s1312, Der> s1320;
s1306( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ ) {}
s1306( const s1320& r )
: s336( r ), s349( r.s349 ) {}
template<class s1530, class s1531>
static void s1532( s483* src, s483* s778 );
s483* s1536( const s483* p ) const override;
s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s346;
class s346
: public s1306<std::int32_t, s346>{
static s341 s348;
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef std::int32_t s1386;
s346( ) : s346( NULL ) {}
s346( s262* s300 );
s346( const s346& );
s346( s262* s300, const std::vector<s271*>& l );
s346( s262* s300, int i );
s346( s262* s300, s1905& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s1541( s1061 tp ) const override;
void s500( const s272* s587, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
s1386* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0; }
operator int() const override { return s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void to_null( ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1303
: public s1306<std::int64_t, s1303>{
protected:
static s341 s348;
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef std::int64_t s1386;
s1303() : s1303( NULL ) {}
s1303( s262* s300 );
s1303( const s1303& );
s1303( s262* s300, const std::vector<s271*>& l );
s1303( s262* s300, int64_t i );
s1303( s262* s300, s1905& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s587, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
int64_t* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0; }
operator int() const override { return (int)s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
};
class s1529
: public s1306<std::uint64_t, s1529>{
protected:
static s341 s348;
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef std::uint64_t s1386;
s1529() : s1529( NULL ) {}
s1529( s262* s300 );
s1529( const s1529& );
s1529( s262* s300, const std::vector<s271*>& l );
s1529( s262* s300, int64_t i );
s1529( s262* s300, s1905& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, 	s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s587, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
s1386* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0; }
operator int() const override { return (int)s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
};
template <>
inline void s1306<s1529::s1386, s1529>::s404( s483** s274, size_t s498 ){
( (s1529*)s274[0] )->s349 = ( (s1529*)s274[1] )->s349;}
template <>
inline void s1306<s1529::s1386, s1529>::s389( s483** s274, size_t s498 ){
if( s498 == 2 )
( (s1529*)s274[0] )->s349 = ( (s1529*)s274[1] )->s349;
else {
s274[2]->s356( s274[0] );
( (s1529*)s274[0] )->s349 =
( (s1529*)s274[1] )->s349 - ( (s1529*)s274[0] )->s349;}}
class s1295
: public s1306<tdbyte_t, s1295>{
protected:
static s341 s348;
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef tdbyte_t s1386;
s1295() : s1295( NULL ) {}
s1295( s262* s300 );
s1295( const s1295& );
s1295( s262* s300, const std::vector<s271*>& l );
s1295( s262* s300, tdbyte_t i );
s1295( s262* s300, const std::wstring& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s587, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
tdbyte_t* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0; }
operator int() const override { return s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override { return std::to_wstring( s349 ); }
void s1935( Stream* ) const override;
};
class s1573
: public s1306<wchar_t, s1573>{
protected:
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef wchar_t s1386;
s1573() : s1573( NULL ) {}
s1573( s262* s300 );
s1573( const s1573& );
s1573( s262* s300, const std::vector<s271*>& l );
s1573( s262* s300, wchar_t i );
s1573( s262* s300, s1905& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s587, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
wchar_t* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0; }
operator int() const override { return s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override { return std::wstring( 1, s349 ); }
void s1935( Stream* ) const override;
};
typedef s346 TDInt;
class s591;
class s272;
typedef std::vector<std::pair<std::wstring, size_t>> s622;
typedef std::map<std::wstring, s272*> s623;
typedef std::map<std::wstring, s263*> s624;
class s272
: public s483{
protected:
const s272* s625;
const s272* s626;
s371 s1663;
const std::wstring& s347;
std::wstring s278;
std::wstring s627;
s482 s628;
s551* s629;
std::vector<s485> s630;
std::vector<s371> s631;
s2193 s2197;
void s350() override { }
s483* s1704( s483** s274, size_t s498 );
public:
s272( const s272& s632, std::vector<s485>& s274, const s263* ast_/*=NULL*/, s272* ns_/* = NULL*/ );
s272( s262* s300, s1061 s340, s472 pc/* = s473*/, const s263* ast_/* = NULL*/, s272* ns_/* = NULL*/, s2193 st = s2200  );
s272( s1905& s278, s262* s300, s472 pc, const s263* ast_/* = NULL*/, s272* ns_/* = NULL*/, s2193 st = s2200 );
s272( s1905& s347, const std::wstring& s278, s262* s300, s482& s633,
const s482& s628, const s263* ast_/* = NULL*/, s2193 st/* = s2204*/  );
s272( s263& s701, s262* s300, s472 pc, s272* ns, s536 am,
s623& cl, s622& cnl, s624& al, s2193 st );
virtual ~s272();
s1905& s353() const override { return s347; }
virtual s1905& s299() const { return s278; }
std::wstring s298() const override;
std::wstring s834() const override { return /*ns->s298()*/ s278;} 
s2193 s2195() const { return s2197; }
void s2198( s2193 st ) override { s2197 = st; }
static s271* s634( const s6::s143& obj, s1905& s278, s262* s300 );
static s271* s634( std::multimap<std::wstring, s484*>& v, s484* s587 );
s483* s635( const s263& s701, s483* s588, s1905& s334 ) const;
using s483::s355;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s1536( const s483* p ) const override;
s1061 s386( s1905& s343 ) const override;
bool s501( const s483* s502 ) const override;
const s926& s1004() const override { return s993; }
bool s730( s1905& f ) const;
void s851( s1905& s76, s483* s349, s482::s145 ap = s482::s146 );
void s1657( s1905& s76, s483* s349 );
void s1640( const s1602* ob );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
const s483* s503() const override { return s625; }
const s272* s636() const { return s626; }
s1905& s637() const { return s627; }
s483* s344( s1905& s278, s1905& s334,
bool s520 = true, bool s2167 = true ) const override;
s591* s1685( s1905& s278, s591* s215,	s561* cs ) const override;
void s645( s263& s701 );
void s555( s1905& s76, s1905& s558 );
bool s2180( s1905& s76 );
void s638( s263& s701 );
void s970( s263& s701 );
void s639( s1905& s334,	std::vector<std::wstring>& s153 );
bool s556( s1905& s278, s371* s153, s1905& s334, bool fr ) const override;
size_t s640( const std::wstring& s278 ) const;
s271* s598( size_t off ) override;
s483* s641( s1905& s278, s1905& s334,
bool s520=true ) const;
bool s642( s1905& sym, s1905& s499 ) const;
bool s532( s1905& sym );
void s500( const s272* s879, bool b ) override;
void s644( const s482& s274 ); 
void s154( s263& s701 );
void s1649();
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
void s643( s272* s646 ) const;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s561
: public s271{
const std::wstring s601;
std::vector<s271*> s274;
s947 past;
bool s2176;
public:
s561( s262* pass_, const s263* ast_, bool s2177 = false )
: s271( pass_, s477 ), past( (s263*)ast_ ), s2176( s2177 ){}
s561( s262* pass_, s1905& s1553, const std::vector<s271*>& l, const s263* s701, bool s2177 = false );
s561( const s561& s540 );
s1905& s299() const { return s601; }
void s2188( bool b ) { s2176 = b; }
bool s2183() const { return s2176; }
std::vector<s271*>& s602() { return s274; }
const s263* s603() { return past; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override { }
};
typedef s1::s9<s561> s490;
class s591;
class s262;
typedef s591 TD;
class s336;
typedef s591 Transd;
typedef std::vector<s485> s577;
typedef std::vector<s486> s578;
typedef std::vector<s485> s579;
extern s577 s2115;
class s591
: public s272{
public:
enum s563 { s564, s565, s566, s567, s568, s2113, s569 };
protected:
std::wstring s671;
enum s570 { s571, s572, s573, s574 };
s563 s575;
s570 s576;
s483** s580;
s484** s581;
size_t s498, nlocs;
s578 s582;
s577 s274;
std::vector<s486> s981;
std::vector<s483*> s583;
s579 s584;
std::vector<std::vector<s484*>> s585;
s486 s586;
s487 s588;
s488 s587;
const s263* past;
s2172 s1654;
s485 subject;
const bool intro;
const bool s2176;
void s847( s271* par, size_t pos, s485& s153, const s272* s1672,
bool proc );
void s589( s1905& s334);
void s590( s1905& s334);
s483* s1611( s483** s705, size_t s498 );
virtual void s1911( const s577& pl ) const;
public:
s591( s262* s300, s272* s592, s591* s593, s272* ns_, s563 ct,
s1905& s676, const s263* s701, bool s1727 = false, bool _bd = true );
s591( s262* s300, s272* s588, s591* s587, s272* ns_, s563 ct,
const std::vector<s271*>& l, const s263* s701, bool s1727, bool _bd );
s591( const s591& right, s272* s588, s591* s587, s272* ns_, 
const std::vector<s271*>& s274, const s263* s701, bool s2120=false, 
bool _bd=true );
virtual ~s591();
s563 s864() const { return s575; }
void s594( s570 vt ) { s576 = vt; }
s570 s595() const { return s576; }
const std::wstring& s353() const override { return s271::s353(); }
std::wstring s834() const override;
std::wstring s298() const override;
bool s2183() const { return s2176; }
const s263* s603() const { return past; }
s483* s496() override { return s586; }
void s2189( s371* ref );
void s500( const s272* s1672, bool proc ) override;
void s596( const std::vector<s485>& l );
typedef std::vector<std::pair<std::wstring, s486>> s835;
void s814( s835& s153 ) const;
void s597( const s272* s1672 );
void s2129( s577& s2128 );
void s2133( s483* s2124, bool s2176 = true ) override;
bool s556( const std::wstring& s278, s371* ref,
const std::wstring& s334, bool ) const override;
s271* s598( size_t off ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
static s591* s599( const s263& s701, s262* s300, s272* obj,
s1905& s278, s1905& s558 );
static s561* s1119( const s263& s701, s262* s300, s272* obj,
s1905& s558, bool s2176 );
static s591* s600( s561* cs, s262* s300, s272* s588, s591* s215,
s1905& s558, bool proc );
static void s1242( std::vector<s271*>& s274, const std::vector<std::wstring>& s1208 );
static void s1242( std::vector<s485>& s274, const std::vector<std::wstring>& s1208 );
void s304( std::wostream* pd, int s197 = 0 ) const override;
std::wstring trace( const char* topics ) const override;
};
class s841
: public s591{
s616 s562;
bool s1976;
public:
s841( s262* s300, s591* s587, s272* ns, s563 ct, const std::vector<s271*>& l,
s1061 s493, const std::wstring& s1553, const s263* s701, bool _bd = false );
s841( const s841& right, s591* s587, s272* ns );
virtual ~s841();
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
bool s556( const std::wstring& s278, s371* ref,
const std::wstring& s334, bool ) const override;
s271* s335( s591* s2057, s272* impl ) const override;
bool s1203() const override { return s1976; }
};
class s842
: public s591{
public:
s842( s262* s300, s272* s588, s591* s587, s272* ns, s563 ct,
const std::vector<s271*>& l, const s263* s701, bool s2176 = false );
s842( const s842& right, s591* s587, const std::vector<s271*>& s274,
s563 ct, const s263* s701, s272* s588 = NULL, s272* ns = NULL, bool intro = true, bool _bd = false );
virtual ~s842();
void s1678( s272* s592 ) { s588 = s592; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1357
: public s842{
public:
s1357( s262* s300, s272* s588, s591* s587, const s263* s701 );
s1357( const s1357& right, s272* s588, s591* s587, const std::vector<s271*>& s274,
const s263* s701 );
virtual ~s1357();
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
namespace s1512 {
extern s1061 s1505;
extern s1061 s1509;
extern s1061 s1504;}
typedef std::basic_istream<wchar_t> s1497;
typedef std::basic_ostream<wchar_t> s1500;
typedef std::basic_istringstream<wchar_t> s1971;
typedef std::basic_ostringstream<wchar_t> s1972;
class Stream
: public s336{
public:
typedef std::ios_base::fmtflags s1924;
typedef std::streamsize s1925;
Stream( s262* s300, s272* ns, const s263* s208 = NULL )
: s336( s300, ns, s208 ) {}
virtual void s1461( std::wstring& s153, size_t s1472 );
virtual void s1480( const std::wstring& src );
virtual void s1462( std::wstring& s153, const std::wstring& s72 = L"\n" );
virtual void s1481( const std::wstring& src );
virtual void s1460( s1322& s153, size_t s1472 );
virtual void s1479( const s1322& src );
virtual void s1459( s1322& s153, const s1322& s72 = s1322( {'\n'} ) );
virtual void s1478( const s1322& src );
virtual void rewind();
virtual void s1929()=0;
virtual void s1927()=0;
virtual void s2066()=0;
virtual void s2065()=0;
virtual void s1957()=0;
virtual void s1958()=0;
virtual void s1568( int n )=0;
virtual void s1928( int n )=0;
virtual void s1913( wchar_t c );
virtual void s1915()=0;
virtual void s1916()=0;
virtual void s1914()=0;
virtual void s1926()=0;
virtual void s1566()=0;
virtual void s1567()=0;
virtual s1924 s1930() const = 0;
virtual s1925 s1931() const = 0;
virtual bool s2067() const = 0;
virtual void s1951()=0;
virtual void s1953()=0;
virtual void s1956( int n )=0;
virtual void s1954( int n )=0;
virtual void s1952()=0;
virtual void s1955()=0;
virtual s1924 s1961() const = 0;
virtual s1925 s1962() const = 0;
virtual void ws() { throw new s2::s16( L"ws not implemented" ); }
virtual s1497& s1963() { throw new s2::s16( L"iwstream not implemented" ); }
virtual s1500& s1964() { throw new s2::s16( L"owstream not implemented" ); }
};
template<class s1420, class s1422>
class s1406
: public Stream{
protected:
typedef s1406<s1420, s1422> s1167;
typedef s336::s341 s341;
s1420 *s1474;
s1422 *s1475;
bool s2073;
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s1487( s483** s274, size_t n );
public:
s1406( s262* s300, s272* ns, const s263* s208 = NULL )
: Stream( s300, ns, s208 ), s2073( false ) {}
s1406(): s2073( false ){}
virtual ~s1406() {}
void s1929() override;
void s1927() override;
void s2066() override;
void s2065() override;
void s1957() override;
void s1958() override;
void s1568( int n ) override;
void s1928( int n ) override;
void s1915() override;
void s1916() override;
void s1914() override;
void s1926() override;
void s1566() override;
void s1567() override;
s1924 s1930() const override;
s1925 s1931() const override;
bool s2067() const override;
void s1951() override;
void s1953() override;
void s1956( int n ) override;
void s1954( int n ) override;
void s1952() override;
void s1955() override;
s1924 s1961() const override;
s1925 s1962() const override;
};
template<class s1420, class s1422>
s336::s341 s1406<s1420, s1422>::s348;
template<class s1420, class s1422>
void s1406<s1420, s1422>::s350(){
s348.insert( std::make_pair( L"rewind", new s337( L"rewind", &s1406<s1420,s1422>::s1487, s1152,
{ s1122() }, 0, 0 ) ) );}
template<class s1420, class s1422>
void s1406<s1420, s1422>::s1487( s483** s274, size_t s498 ){
s1167* s1062 = (s1167*)s274[1];
if( s1062->s1474 ) {
if( s1062->s1474->eof() )
s1062->s1474->clear( s1062->s1474->rdstate() &
( s1062->s1474->rdstate() ^ std::ios_base::eofbit ) );
if( !s1062->s1474->good() )
throw new s2::s16( L"file handle is not valid" );
s1062->s1474->seekg( 0 );
s1062->s1474->clear();}
if( s1062->s1475 )
s1062->s1475->seekp( 0 );}
class s507
: public s1406<s1971,s1972>{
protected:
typedef s507 s1167;
static s341 s348;
std::basic_stringstream<wchar_t> ss;
static void s508( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
s507( const s507&, const s263* ast_ = NULL );
s507( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s507(){}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&ss; }
s1497& s1963() override { return *s1474; }
s1500& s1964() override { return *s1475; }
void s1461( std::wstring& s153, size_t s1472 ) override;
void s1480( s1905& src ) override;
void s1462( std::wstring& s153, s1905& s72 = L"\n") override;
void s1481( s1905& src ) override;
void s1460( s1322& s153, size_t s1472 ) override;
void s1479( const s1322& src ) override;
void s1459( s1322& s153, const s1322& s72 = s1322( { '\0' } ) ) override;
void s1478( const s1322& src ) override;
void s1913( wchar_t c ) override;
virtual void ws() override { *s1474 >> std::ws; }
virtual std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_istringstream<tdbyte_t> s1495;
typedef std::basic_ostringstream<tdbyte_t> s1498;
class s1294
: public s1406<s1495,s1498>{
protected:
typedef s1294 s1167;
static s341 s348;
std::basic_stringstream<tdbyte_t> bs;
static void s1315( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
s1294( const s1294&, const s263* ast_ = NULL );
s1294( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s1294(){}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&bs; }
void s1461( std::wstring& s153, size_t s1472 ) override;
void s1480( s1905& src ) override;
void s1462( std::wstring& s153, s1905& s72 = L"\n" ) override;
void s1481( s1905& src ) override;
void s1460( s1322& s153, size_t s1472 ) override;
void s1479( const s1322& src ) override;
void s1459( s1322& s153, const s1322& s72 = s1322( { '\0' } ) ) override;
void s1478( const s1322& src ) override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_ifstream<tdbyte_t> s1496;
typedef std::basic_ofstream<tdbyte_t> s1499;
class s1302
: public s1406<s1496,s1499>{
protected:
typedef s1302 s1167;
static s341 s348;
s485 s210;
s485 mode;
std::wstring s1341;
typedef std::basic_fstream<tdbyte_t> s1494;
std::fstream fs;
static void s1236( s483** s274, size_t n );
static void s2028( s483** s274, size_t n );
static void s2030( s483** s274, size_t n );
static void s2029( s483** s274, size_t n );
static void s1324( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s2036( s483** s274, size_t n );
static void s1484( s483** s274, size_t n );
static void s1355( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
static void s2006( s483** s274, size_t s498, std::wstring& s1345 );
void _open( const std::wstring& s1345 );
void _close();
public:
s1302( const s1302&, const s263* ast_ = NULL );
s1302( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
s1302( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL );
~s1302(){}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&fs; }
void s1461( std::wstring& s153, size_t s1472 ) override;
void s1480( s1905& src ) override;
void s1462( std::wstring& s153, s1905& s72 = L"\n" ) override;
void s1481( s1905& src ) override;
void s1460( s1322& s153, size_t s1472 ) override;
void s1479( const s1322& src ) override;
void s1459( s1322& s153, const s1322& s72 = s1322( { '\0' } ) ) override;
void s1478( const s1322& src ) override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1402
: public s1406<std::wistream, std::wostream>{
static s341 s348;
static void s327( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1402( const s507&, const s263* ast_ = NULL );
s1402( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1402(){}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return NULL/*(void*)&std::wcin*/; }
void s1461( std::wstring& s153, size_t s1472 ) override;
void s1480( s1905& src ) override;
void s1462( std::wstring& s153, s1905& s72 ) override;
void s1481( s1905& src ) override;
void s1460( s1322& s153, size_t s1472 ) override;
void s1479( const s1322& src ) override;
void s1459( s1322& s153, const s1322& s72 ) override;
void s1478( const s1322& src ) override;
virtual std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1404
: public s1406<std::wistream, std::wostream>{
static s341 s348;
static void s508( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1404( const s507&, const s263* ast_ = NULL );
s1404( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1404(){}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return NULL; }
s1500& s1964() override { return *s1475; }
void s1461( std::wstring& s153, size_t s1472 ) override;
void s1480( s1905& src ) override;
void s1462( std::wstring& s153, s1905& s72 ) override;
void s1481( s1905& src ) override;
void s1460( s1322& s153, size_t s1472 ) override;
void s1479( const s1322& src ) override;
void s1459( s1322& s153, const s1322& s72 ) override;
void s1478( const s1322& src ) override;
void s1913( wchar_t c ) override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s1402> s1403;
extern s1::s9<s1404> s1405;
class s262;
class s385;
class Iterator{
public:
virtual ~Iterator() {}
virtual s271* s315() = 0;
virtual s271* s962() = 0;
virtual const s271* s962() const = 0;
virtual s271* Idx() = 0;
virtual s271* El() = 0;
virtual s1061 ValType() const = 0;
virtual bool s1979() const = 0;
virtual bool operator==( const Iterator* r ) const { return this == r; }
virtual bool operator<( const Iterator* r ) const { return this < r; }
};
typedef std::pair<s1::s1289<Iterator>, s1::s1289<Iterator>> s1144;
struct s840;
class s385;
class s326
: public s336{
protected:
s1061 s317;
s1061 s1200;
s1061 s325;
virtual s483* s1190( Iterator* it );
public:
s326( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ ), s317( 0 ), s1200( 0 ), s325( 0 ) {}
s326( const s326& r )
: s336( r ), s317( r.s317 ), s1200( r.s1200 ), s325( r.s325 ) {}
virtual ~s326() {}
virtual size_t s1138() const { return 0; }
virtual Iterator* s314( s385* r ) = 0;
virtual s1061 s319() const { return s317; }
virtual s1061 s937() const { return s1200; }
virtual s1061 ValType() const { return s325; }
virtual Iterator* s1185() = 0;
virtual Iterator* s1189() = 0;
virtual s1144 s1194() = 0;
virtual Iterator* s1164( const s483* idx );
virtual Iterator* s1183( const s483* s349 );
virtual Iterator* s1238( const s483* s349 );
virtual s483* sort( bool reverse, s840* cmp );
};
class s385
: public s326,
public Iterator{
s485 s588;
s1::s9<s326> s985;
s1::s1289<Iterator> s1466;
s485 s1243, s1244;
s486 s1542, s1543;
bool s978, s979;
Iterator* s318;
uint64_t s988, s1546;
int incr;
s1::s9<s1529> s1175;
static s341 s348;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
enum s1141 { s1227, s1234, s1226, s1233, s1235, s1222, s1228 };
s385( s262* s300 );
s385( s262* s300, s326* s588, Iterator* it );
s385( uint64_t b, uint64_t e = U64_MAX );
s385( s262* s300, s1905& s77, const s263* ast_ = NULL );
s385( const s385& right, const s263* ast_ = NULL );
s385( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1142 s1197( s1905& s343 ) const override;
s1142 s1192( s1905& s343, s1122& ap ) const override;
s1142 s1187( s1905& s343,	s1122& ap ) override;
s1061 s1188( s1905& s1553,	const std::vector<s485>& l ) const override;
const std::vector<std::wstring>& s1191( s1905& s343 ) const override;
size_t s1138() const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)s318; }
s1061 ValType() const override { return s325; }
void s500( const s272* s879, bool fr=true ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
Iterator* s1185() override { return NULL; }
Iterator* s1189() override { return NULL; }
s1144 s1194() override;
s1144 s1194( s326* s588 );
bool s1979() const override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
s326* s819() { return s985; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1134
: public s326,
public Iterator{
s485 s588;
s486 s985;
s1::s9<s385> range;
s485 where, s1070;
s1::s1289<Iterator> s318, s1489;
s1::s9<s371> s987; // @it - for using in s1202 scope lambdas
s271* s988;
static s341 s348;
s1::s9<s346> s349, s685;
std::wstring s499;
s1061 s1353;
static void s1236( s483** s274, size_t n );
static void s1348( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1141 { s1227, s1234, s1226, s1233, s1235, s1332, s1228 };
s1134( s262* s300 ) : s326( s300, NULL, NULL ), s987( new s371( s7::s1374, s300, s475 ) ), 
s988(NULL) {}
s1134( s262* s300, s1905& s77, const s263* ast_ = NULL );
s1134( const s1134& r, const s263* ast_ = NULL );
s1134( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s1061 s319() const override { return s685->s352(); }
size_t s1138() const override { return s985.s15<s326*>()->s1138(); }
s1142 s1192( s1905& s343,	s1122& ap ) const override;
s1142 s1187( s1905& s343, s1122& ap ) override;
s1061 s1188( s1905& s1553,	const std::vector<s485>& l ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1061 ValType() const override { return s325; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
bool s556( s1905& s278, s371* s153, s1905& s334,	bool ) const override;
s271* s598( size_t off ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
bool s1979() const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
Iterator* s1185() override { return NULL; }
Iterator* s1189() override { return NULL; }
s1144 s1194() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s951
: public s326,
public Iterator{
s488 s1058;
s488 set;
s488 eq;
s485 start;
s485 end;
s485 incr;
s485 s989;
s485 s1659;
bool s1047;
std::wstring s499;
static s341 s348;
static void s1236( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1141 { s1227, s1234, s1226, s1233, s1235, s1222, s1228 };
s951( s262* s300 );
s951( s262* s300, s1905& s77, const s263* ast_ = NULL );
s951( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
virtual ~s951();
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1061 ValType() const override { return s325; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override {}
size_t s322() const override { return 0; }
bool operator==( const s483* p ) const override { return false; }
bool operator<( const s483* p ) const override { return false; }
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
bool s1979() const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
s271* s962() override { return NULL; }
const s271* s962() const override { return NULL; }
s271* Idx() override;
s271* El() override { return NULL; }
Iterator* s1185() override { return NULL; }
Iterator* s1189() override { return NULL; }
void* addr() override { return NULL; }
s1144 s1194() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef int HPROG;
enum s1370{ s1429=1, s1430, s1431, s1432, s1622, 
s1433, s1434, s2079, s1435, s1436, s1439, 
s1437, s1438, s1623, s1440, s1947, s1624, 
s1441, s1442, s1626, s1627, s1443,
s1887, s1625,	s1948, s1946, s1444,
s1563, s1445, s1446, s1447, s1628,
s1448,	s1449, s1450 };
extern std::map<std::wstring, int> s1371;
extern std::vector<int> BIFuncs1v;
extern std::vector<std::wstring> s1372;
struct s722{
std::vector<std::wstring> s663;
std::wstring entry;
s1999 restrictions[s1984];
s722() {
memset( &restrictions, 0, s1984 * sizeof(s1999) );}
};
class s1987{
s1999 s2041[s1984];
static std::vector<std::wstring> s2049;
s1999 s2003( const std::wstring& s2039 );
public:
s1987();
void s2056( const s6::s143& s133 );
void reset();
void s2013( const std::vector<s1998>* s2034, s1999 sw ) const;
bool s2012( s1998 si, s1999 sw ) const;
};
class s561;
class s262
: public s272{
private:
std::vector<std::wstring> s199;
s263 s701;
std::wstring s200;
std::wstring s767;
std::wstring s1898;
s1987 s2040;
void s202( s1905& s657, s722& s153 );
void s213( s1905& s194, const s6::s143& obj );
void s2175( const s6::s143& obj );
s491 s203;
s482 s204;
typedef std::map<std::wstring, s483*> s205;
s205 s206;
typedef std::map<uint32_t, std::set<std::wstring>> s941;
bool s1319;
public:
s262();
~s262();
s1905& s716() const { return s767; }
void s1890( s1905& s ) { s767 = s; }
s1905& s1893() const { return s1898; }
void s1891( s1905& s ) { s1898 = s; }
virtual std::wstring s834() const override { return L"::"; }
virtual std::wstring s298() const override { return L"::"; }
void s1900( bool soft = false );
void reset();
void s207( s263& s208 );
void s209( s1905& s210, bool s1902 = false );
void s211( s6::s143& obj );
void s212( s1905& s210 );
s483* run( const std::vector<std::wstring>& s691 );
s483* callFunc( s1905& s601, std::vector<std::wstring>& l );
s488 getProc( s1905& s601 );
bool s1330() const { return s1319; }
void s1650( s1905& s671 );
void s2013( const std::vector<s1998>* s2034, s1999 sw ) const;
bool s2012( s1998 si, s1999 sw ) const;
s491& TR() { return s203; }
s591* s214( int s1457, s561* cs,
s272* s588, s591* s215 );
void s217( s1905& s );
s1061 s218( s483* p, s1905& s347 );
void s219( s1905& s349, s1905& s334, std::vector<std::wstring>& s153 );
virtual bool s556( s1905& s278, s371* s153,	s1905& s334, bool ) const override;
s486 s220( s1905& s349, s1905& s334 );
bool s221( s371& rf ) const;
s271* s222( s1905& sym, s1905& s499, bool s520 = true );
void* s223( s1905& s278 );
void s1351( s1905& s671 );
void s1665( s1905& s1633 );
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s1::s9<s262> s721;
namespace s1512 {
extern s1061 s1507;
extern s1061 s1506;
extern s1061 s1508;}
class Iterator;
struct s840;
class s1143;
struct s321{
std::size_t operator()( const s486 k ) const{
return k->s322();}
};
struct s323{
bool operator()( const s486 l, const s486 r ) const{
return l->operator==( ( s483* )&( *r ) );}
bool operator()( const s483* l, const s483* r ) const{
return l->operator==( r );}
bool operator()( const s483& l, const s483& r ) const{
return l.operator==( &r );}
};
struct s1425{
bool operator()( const s486 l, const s486 r ) const{
return l->operator<( ( s483* )&( *r ) );}
bool operator()( const s483* l, const s483* r ) const{
return l->operator<( r );}
bool operator()( const s483& l, const s483& r ) const{
return l.operator<( &r );}
};
void s1161( s262* s300, const std::wstring& s77, 
std::wstring& s1273, std::wstring& s644 );
template<class s1311>
struct s1301 {
bool operator()( const s1311& l, const s1311& r ) { return l < r; }
};
template<class s1311>
struct s1574 {
bool operator()( const s1311& l, const s1311& r ) { return l == r; }
};
template<class s1311, class s1581>
struct s1575{
s488 s859;
std::vector<s485>s861;
s1575() : s859( 0 ),
s861( { new s1581( 0,0 ), new s1581( 0,0 ) } ) {}
bool operator()( const s1311& l, const s1311& r ){
*s861[0].template s15<s1581*>()->s357() = l;
*s861[1].template s15<s1581*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
template<>
struct s1301<s485>{
std::vector<s485>s861;
s488 s859;
s1301() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s485& l, const s485& r ){
if( s859.s14() ) {
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l.s15<s483*>()->operator<( r.s15<s483*>() );}
};
template<>
struct s1301<s486>{
std::vector<s485>s861;
s488 s859;
s1301() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s486& l, const s486& r ){
if( s859.s14() ) {
s861[0] = l.s15<s271*>();
s861[1] = r.s15<s271*>();
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l->operator<( r.s15<s483*>() );}
};
template<>
struct s1301<tdbyte_t>{
s488 s859;
std::vector<s485>s861;
s1301() : s859( 0 ),
s861( { new s1295( 0,0 ), new s1295( 0,0 ) } ) {}
bool operator()( const tdbyte_t& l, const tdbyte_t& r ){
if( s859.s14() ) {
*s861[0].s15<s1295*>()->s357() = l;
*s861[1].s15<s1295*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l < r; }
};
template<>
struct s1301<wchar_t>{
s488 s859;
std::vector<s485>s861;
s1301() : s859( 0 ),
s861( { new s1573( 0,0 ), new s1573( 0,0 ) } ) {}
bool operator()( const wchar_t& l, const wchar_t& r ){
if( s859.s14() ) {
*s861[0].s15<s1573*>()->s357() = l;
*s861[1].s15<s1573*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l < r; }
};
template<>
struct s1574<s485> {
bool operator()( const s485& l, const s485& r ) { 
return l.s15<s483*>()->operator==( r.s15<s483*>() );}
};
template<>
struct s1574<s486> {
bool operator()( const s486& l, const s486& r ) { 
return l->operator==( r.s15<s483*>() );}
};
template<>
struct s1575<s485, s485>{
std::vector<s485>s861;
s488 s859;
s1575() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s485& l, const s485& r ){
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
template<>
struct s1575<s486, s486>{
std::vector<s485>s861;
s488 s859;
s1575() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s486& l, const s486& r ){
s861[0] = l.s15<s271*>();
s861[1] = r.s15<s271*>();
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
typedef std::wstring s1577;
template<class _Cont, class s1311, class Der>
class s313 :
public s326{
protected:
typedef Der s1167;
_Cont s349;
static s1301<s1311> s1325;
static s1574<s1311> s1584;
typedef s336::s341 s341;
static s341 s348;
static void s328( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1254( s483** s274, size_t n );
static void s1267( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1335( s1311 el ) { return el; }
static std::pair<typename _Cont::iterator, typename _Cont::iterator> s1424( s483* p, Der* pv );
static s1144 s1426( s483* p, Der** pv );
static s1143* s1975( Der** pv, typename _Cont::iterator& s1981 );
public:
typedef s313<_Cont, s1311, Der> s1170;
s313( s262* s300, s272* ns, const s263* ast_ );
s313( const s1170& r );
virtual ~s313(){}
virtual s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
virtual s1144 s1194() override;
};
template<class _Cont, class s1311, class Der>
s336::s341 s313<_Cont, s1311, Der>::s348;
template<class _Cont, class s1311, class Der>
s1301<s1311> s313<_Cont, s1311, Der>::s1325;
template<class _Cont, class s1311, class Der>
s1574<s1311> s313<_Cont, s1311, Der>::s1584;
template<class _Cont, class s1311, class Der, class s1582>
class s1401 :
public s313<_Cont, s1311, Der>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
static s1575<s1311, s1582> s1585;
static void s1583( s483** s274, size_t n );
static void s1586( s483** s274, size_t n );
static void s1635( s483** s274, size_t n );
static void s1621( s483** s274, size_t n );
static void s1211( s483** s274, size_t n );
static void s1210( s483** s274, size_t n );
static void s2090( s483** s274, size_t n );
static void s2089( s483** s274, size_t n );
static void s2088( s483** s274, size_t n );
static void s1254( s483** s274, size_t n );
static void s1267( s483** s274, size_t n );
static void s1593( s483** s274, size_t n );
static void s1587( s483** s274, size_t n );
static void s1493( s483** s274, size_t n );
static void s1745( s483** s274, size_t n );
static void s1950( s483** s274, size_t n );
static void s2094( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1335( s1311 el ) { return el; }
public:
typedef s1401<_Cont, s1311, Der, s1582> s1170;
s1401( s262* s300, s272* ns, const s263* ast_ );
s1401( const s1170& r );
virtual ~s1401(){}
virtual s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
};
template<class _Cont, class s1311, class Der, class s1582>
s336::s341 s1401<_Cont, s1311, Der, s1582>::s348;
template<class _Cont, class s1311, class Der, class s1582>
s1575<s1311, s1582> s1401<_Cont, s1311, Der, s1582>::s1585;
template<class _Cont, class s1311, class Der>
class s1576 :
public s1401<_Cont, s1311, Der, s1311>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
static void s1635( s483** s274, size_t n );
static void s1621( s483** s274, size_t n );
static void s1267( s483** s274, size_t n );
static void s1464( s483** s274, size_t n );
static void s1973( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef s1576<_Cont, s1311, Der> s1170;
s1576( s262* s300, s272* ns, const s263* ast_ );
s1576( const s1170& r );
virtual ~s1576(){}
virtual s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
};
template<class _Cont, class s1311, class Der>
s336::s341 s1576<_Cont, s1311, Der>::s348;
template<class s1311>
struct s1380 {
bool operator()( const s1311& l, const s1311& r ) { return l < r; }
};
template<>
struct s1380<std::pair<s486, s486>>{
typedef std::pair<s486, s486> s1419;
std::vector<s485>s861;
s488 s859;
s1380() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s1419& l, const s1419& r ){
if( s859.s14() ) {
s861[0] = l.first.s15<s271*>();
s861[1] = r.first.s15<s271*>();
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l.first->operator<( r.first.s15<s483*>() );}
};
template<class _Cont, class s1421, class s1423, class Der>
class s1369 :
public s313<_Cont, s1421, Der>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
s1380<std::pair<s1421, s1423>> s1455;
static void s1211( s483** s274, size_t n );
static void s2090( s483** s274, size_t n );
static void s2088( s483** s274, size_t n );
static void s1485( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1335( std::pair<s1421, s1423>& el );
public:
typedef s1369<_Cont, s1421, s1423, Der> s1170;
s1369( s262* s300, s272* ns, const s263* ast_ );
s1369( const s1170& r );
virtual s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
virtual bool insert( s483* s152, s483* s349 );
virtual s483* find( s483* s152 );
};
template<class _Cont, class s1421, class s1423, class Der>
s336::s341 s1369<_Cont, s1421, s1423, Der>::s348;
template <class _Cont, class s1311, class Der>
s313<_Cont, s1311, Der>::s313( s262* s300, s272* ns_, const s263* ast_ )
: s326( s300, ns_, ast_ ){}
template <class _Cont, class s1311, class Der, class s1582>
s1401<_Cont, s1311, Der, s1582>::s1401( s262* s300, s272* ns_, const s263* ast_ )
: s313<_Cont, s1311, Der>( s300, ns_, ast_ ){}
template <class _Cont, class s1311, class Der>
s1576<_Cont, s1311, Der>::s1576( s262* s300, s272* ns_, const s263* ast_ )
: s1401<_Cont, s1311, Der, s1311>( s300, ns_, ast_ ){}
template <class _Cont, class s1421, class s1423, class Der>
s1369<_Cont, s1421, s1423, Der>::s1369( s262* s300, s272* ns_, const s263* ast_ )
: s313<_Cont, s1421, Der>( s300, ns_, ast_ ){}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
template<class _Cont, class s1311, class Der>
s1144
s313<_Cont, s1311, Der>::s1426( s483* p, Der** pv ){
s385* pr = NULL;
if( p->s352() == s1415 ) {
pr = (s385*)p;
*pv = (Der*)pr->s819();}
else
*pv = ( (Der*)p );
s1144 rp;
if( pr ) {
rp = pr->s1194( *pv );}
else
rp = (*pv)->s1194();
return rp;}
template<class _Cont, class s1311, class Der>
std::pair<typename _Cont::iterator, typename _Cont::iterator> 
s313<_Cont, s1311, Der>::s1424( s483* p, Der* pv ){
using s1130 = Der;
using s939 = typename Der::s1139;
s385* pr = NULL;
if( p->s352() == s1415 ) {
pr = (s385*)p;
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)p );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
return std::make_pair( s1519, s1520 );}
template<class _Cont, class s1311, class Der>
void s313<_Cont, s1311, Der>::s328( s483** s274, size_t n ){
using s1130 = Der;//s1167;
s1130* pv = ( (s1130*)s274[1] );
*( (s346*)*s274 )->s357() = (int)pv->s349.size();}
template<class _Cont, class s1311, class Der>
void s313<_Cont, s1311, Der>::s330( s483** s274, size_t n ){
using s1130 = Der;//s1167;
s1130* pv = ( (s1130*)s274[1] );
pv->s349.clear();}
template<class _Cont, class s1311, class Der>
s1144 s313<_Cont, s1311, Der>::s1194(){
return std::make_pair( s1185(), s1189() );}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1254( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
if( ((s326*)pv)->s1138() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
std::reverse( s1519, s1520 );
*s274 = pv;}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1593( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
if( ((s326*)pv)->s1138() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
std::mt19937 s1656(std::random_device{}());
std::shuffle( s1519, s1520, s1656 );
*s274 = pv;}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s2094( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
if( ( (s326*)pv )->s1138() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
std::unique( s1519, s1520 );
*s274 = pv;}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1950( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der *pv = NULL, *pv1 = NULL;
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
s1144 rp1 = s313<_Cont, s1311, Der>::s1426( s274[2], &pv1 );
s1574<s1311> s1970;
typename _Cont::iterator s1519, s1520, vbeg1, vend1;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
vbeg1 = rp1.first.s15<s939*>()->s1145();
vend1 = rp1.second.s15<s939*>()->s1145();
auto s1949 = std::mismatch( s1519, s1520, vbeg1, vend1, s1970 );
if( s1949.first == s1520 )
s274[0] = new s346( pv->s300, (int)std::distance( s1519, s1520 ) );
else {
s939 it( pv->s300, pv, s1949.first, s1949.first + 1 );
s274[0] = pv->s1190( &it );}}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s2088( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der *pv = NULL, *pv1 = NULL;
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
s1144 rp1 = s313<_Cont, s1311, Der>::s1426( s274[2], &pv1 );
s1301<s1311> s2091;
typename _Cont::iterator s1519, s1520, vbeg1, vend1;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
vbeg1 = rp1.first.s15<s939*>()->s1145();
vend1 = rp1.second.s15<s939*>()->s1145();
bool s153 = std::includes( s1519, s1520, vbeg1, vend1, s2091 );
*((s360*)*s274)->s357() = s153;}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1211( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = ( (Der*)s274[1] );
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
s591* s1206 = NULL;
if( s498 == 3 )
s1206 = (s591*)s274[2];
s1301<s1311> s1969;
s1969.s859 = s1206;
typename _Cont::iterator s1212 = std::max_element( s1519, s1520, s1969);
*s274 = (s483*)pv->s1975( &pv, s1212 );}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1210( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = NULL;
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
if( s1519 == s1520 )
s274[0] = new s346( pv->s300, -1 );
else {
auto s1212 = std::max_element( s1519, s1520, pv->s1325 );
s939 it( pv->s300, pv, s1212, s1212 + 1 );
s274[0] = pv->s1190( &it );}}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s2090( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = ( (Der*)s274[1] );
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
s591* s1206 = NULL;
if( s498 == 3 )
s1206 = (s591*)s274[2];
s1301<s1311> s1969;
s1969.s859 = s1206;
typename _Cont::iterator s1212 = std::min_element( s1519, s1520, s1969);
*s274 = (s483*)pv->s1975( &pv, s1212 );}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s2089( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = NULL;
s1144 rp = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
if( s1519 == s1520 )
s274[0] = new s346( pv->s300, -1 );
else {
auto s1212 = std::min_element( s1519, s1520, pv->s1325 );
s939 it( pv->s300, pv, s1212, s1212 + 1 );
s274[0] = pv->s1190( &it );}}
template<class _Cont, class s1421, class s1423, class Der>
void s1369<_Cont, s1421, s1423, Der>::s1211( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
typename _Cont::iterator s1212 = std::max_element( s1519, s1520, pv->s1455 );
auto tmp = std::make_pair( s1212->first, s1212->second );
*s274 = (s483*)pv->s1335( tmp );}
template<class _Cont, class s1421, class s1423, class Der>
void s1369<_Cont, s1421, s1423, Der>::s2090( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
typename _Cont::iterator s1212 = std::min_element( s1519, s1520, pv->s1455 );
auto tmp = std::make_pair( s1212->first, s1212->second );
*s274 = (s483*)pv->s1335( tmp );}
template<class _Cont, class s1421, class s1423, class Der>
void s1369<_Cont, s1421, s1423, Der>::s2088( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130 *pv, *s2092;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s1144 rp;
if( pr )
rp = pr->s1194( pv );
else
rp = pv->s1194();
if( s274[2]->s352() == s1415 ) {
pr = (s385*)s274[2];
s2092 = (s1130*)pr->s819();}
else
s2092 = ( (s1130*)s274[2] );
s1144 s2093;
if( pr )
s2093 = pr->s1194( s2092 );
else
s2093 = s2092->s1194();
typename _Cont::iterator s1519, s1520, s2095, s2096, cur;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
s2095 = s2093.first.s15<s939*>()->s1145();
s2096 = s2093.second.s15<s939*>()->s1145();
cur = s2095;
/*bool s153 = true;
for( ; cur < s2096; ++cur ) {
auto it = pv->s349.find( cur->first );
if( it != pv->s349.end() || it->second != cur->second ) {
s153 = false;
break;}
}*/
bool s153 = std::includes( s1519, s1520, s2095, s2096 );
*((s360*)*s274)->s357() = s153;}
struct s840{
std::vector<s485>s861;
s488 s859;
s840( s488 s860 ) : s859( s860 ) { s861.resize( 2 ); }
virtual bool operator()( const s485 l, const s485 r ){
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
class s359;
class s1578;
class s359
: public s1401<s1577, wchar_t, s359, s1573>{
typedef s1577 s1386;
typedef s359 s1167;
static s341 s348;
std::vector<s485> s274;
static void s1236( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1592( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s1689( s483** s274, size_t n );
static void s2155( s483** s274, size_t n );
static void s388( s483** s274, size_t n );
static void s393( s483** s274, size_t n );
static void s794( s483** s274, size_t n );
static void s1595( s483** s274, size_t n );
static void s1588( s483** s274, size_t n );
static void s890( s483** s274, size_t n );
static void s891( s483** s274, size_t n );
static void s780( s483** s274, size_t n );
static void s799( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s399( s483** s274, size_t n );
static void s400( s483** s274, size_t n );
static void s401( s483** s274, size_t n );
static void s402( s483** s274, size_t n );
static void s403( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s1483( s483** s274, size_t n );
static void s1034( s483** s274, size_t n );
static void s1347( s483** s274, size_t n );
static void s412( s483** s274, size_t n );
static void s1490( s483** s274, size_t n );
static void replace_impl( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef s1578 s1139;
s359( const s359&, const s263* ast_ = NULL );
s359( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s359( s262* s300, const std::wstring& s = std::wstring( L"" ), s272* s588=NULL, const s263* ast_ = NULL );
s359( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
virtual ~s359();
s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
size_t s1138() const override { return 2; }
s1061 s1188( const std::wstring& s1553, 
const std::vector<s485>& l ) const override;
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s1573 operator[]( size_t n ) { return s1573( s300, s349[n] ); }
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
Iterator* s1164( const s483* idx ) override;
Iterator* s1183( const s483* s349 ) override;
s483* s1190( Iterator* it ) override;
s271* s1335( wchar_t el ) { return new s1573( s300, el ); }
s1386* s357() { return &s349; }
s1386& s320() { return s349; }
const s1386& s320() const { return s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return !s349.empty(); }
operator int() const override;
operator double() const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void s1960( s1905& s ) override;
void s1959( Stream* ) override;
s1322 to_bytes() const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s359 TDString;
class s817
: public s591{
s485 s763, s723;
s485 s808, s801;
size_t s720, nTo;
int s793, s740;
s1::s9<s359> str;
enum s742 { s719, s774, s764, s816 };
public:
enum s1141{ s1226, s1233, s1225, s1229, s1219, s1215 };
s817( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s817( s262* s300 );
s1905& s299() const override { return s759; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s359;
class s316;
class s750;
class s959;
class s1292;
class s324;
class s1382;
typedef std::vector<s485> s1418;
typedef std::vector<s485> s1417;
typedef s1322 s1375;
typedef std::map<s486, s486, s1425> s1387;
typedef std::unordered_map<s486, s486, s321, s323> s1381;
class s1125
: public Iterator{
protected:
bool s884;
public:
s1125() : s884( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s884;  }
};
class s1137
: public s1125{
public:
};
class s964 
: public s1137{
typedef s1418::iterator s939;
typedef s1418::reverse_iterator s1247;
s1::s9<s316> v;
s939 s1214;
s939 s1086;
s1247 s1258;
s1247 s1488;
uint64_t s1213;
s1::s9<s1529> s1173;
s1::s9<s959> s1172;
public:
s964( s964* it );
s964( s262* s300, s316* v_, s939 it, s939 sent );
s964( s262* s300, s316* v_, s1247 it, s1247 sent );
virtual ~s964() {}
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s939 s1145() { return s1214; }
s1247 s1146() { return s1258; }
s1061 ValType() const override;
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s961
: public Iterator{
typedef s1417::iterator s939;
s1::s9<s750> v;
s939 s1214;
s939 s1086;
uint64_t s1213;
s1::s9<s1529> s1173;
public:
s961( s961* it );
s961( s262* s300, s750* v_, s939 it, s939 sent );
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
s939 s1145() { return s1214; }
s1061 ValType() const override;
};
class s938
: public s1125{
typedef s1387::iterator s939;
typedef s1387::reverse_iterator s1247;
s1::s9<s324> v;
s939 s1214;
s939 s1086;
s1247 s1258;
s1247 s1488;
s485 s1173;
s1::s9<s959> s1172;
public:
s938( s938* it );
s938( s262* s300, s324* v_, s939 it, s939 sent );
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
s939 s1145() { return s1214; }
void reverse() override;
s1061 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1383
: public Iterator{
typedef s1381::iterator s939;
s1::s9<s1382> v;
s939 s1214;
s939 s1086;
s485 s1173;
s1::s9<s959> s1172;
public:
s1383( s1383* it );
s1383( s262* s300, s1382* v_, s939 it, s939 sent );
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
s939 s1145() { return s1214; }
s1061 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1578
: public s1137{
typedef s1577::iterator s939;
typedef s1577::reverse_iterator s1247;
s1::s9<s359> v;
s939 s1214;
s939 s1086;
s1247 s1258;
s1247 s1488;
uint64_t s1213;
s1::s9<s1529> s1173;
s1::s9<s959> s1172;
public:
s1578( s1578* it );
s1578( s262* s300, s359* v_, s939 it, s939 sent );
s1578( s262* s300, s359* v_, s1247 it, s1247 sent );
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s939 s1145() { return s1214; }
s1247 s1146() { return s1258; }
s1061 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1293
: public s1137{
typedef s1375::iterator s939;
typedef s1375::reverse_iterator s1247;
s1::s9<s1292> v;
s939 s1214;
s939 s1086;
s1247 s1258;
s1247 s1488;
uint64_t s1213;
s1::s9<s1529> s1173;
s1::s9<s959> s1172;
public:
s1293( s1293* it );
s1293( s262* s300, s1292* v_, s939 it, s939 sent );
s1293( s262* s300, s1292* v_, s1247 it, s1247 sent );
bool s1979() const override;
s271* s315() override;
s271* s962() override;
const s271* s962() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s939 s1145() { return s1214; }
s1247 s1146() { return s1258; }
s1061 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1143
: public s336{
s485 s588;
s1::s1289<Iterator> s349;
s1061 s325;
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s398( s483** s274, size_t n );
static void s1980( s483** s274, size_t n );
static void s1589( s483** s274, size_t n );
static void s1746( s483** s274, size_t n );
static void s403( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
public:
s1143( s262* s300 ) : s336( s300, NULL, NULL ), s325(0) {}
s1143( s262* s300, s1905& s77, const s263* ast_ = NULL );
s1143( const s1143& right, const s263* ast_ = NULL );
s1143( s262* s300, s272* context, Iterator* it, const s263* ast_ = NULL );
virtual ~s1143() {}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
void s500( const s272* s879, bool ) override;
s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const override;
s1061 ValType() const { return s325;  }
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
void operator=( const s1143& p );
bool operator==( const s483* p )  const override;
bool operator<( const s483* p )  const override;
void* addr() override { return (void*)&s349; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s964;
class s1293;
class s316
: public s1576<s1418, s485, s316>{
s316( const s316& right ) :s1576( 0, 0, 0 ) {
throw; }
protected:
typedef s1418 s1386;
typedef s316 s1167;
static s341 s348;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1264( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1314( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s1889( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1745( s483** s274, size_t n );
void s969( s1905& s824, const s1720& tbfr, s272* s588, const s263* ast_	 );
void s350() override;
const s341& s342() const override { return s348; }
void s1160( s1905& s77, s272* s588, const s6::s1695& s1759 );
void s1313( const std::vector<s271*>& v, s272* s588 );
void s1158( s1905& s1273, s1061& pt, s1061& vt ) const;
public:
enum s1141 { s1755, s1753, s1751, s1749, s1750, s1752,
s1842 };
typedef s964 s1139;
s316( s262* s300 ) : s1576( s300, NULL, NULL ) {}
s316( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1695& s1759 = s1736 );
s316( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL, s1061 s709 = 0, s1061 s1276 = 0 );
s316( const s316& right, s272* ns, const s263* ast_ );
s316( s262* s300, s1061 s325, s272* s588, const s263* ast_ = NULL );
virtual ~s316() override;
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s1061 s1195( s1905& s1273, s813::Cont& s588 ) const;
size_t s1138() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const override;
void load( s1905& s77, s272* s588, const s6::s1695& s1759 );
void s500( const s272* s879, bool fr=true ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
s483* s1536( const s483* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s485 operator[]( size_t n ) { return s349[n]; }
const s485& operator[]( size_t n ) const { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
Iterator* s1164( const s483* idx ) override;
Iterator* s1183( const s483* s349 ) override;
s483* s1190( Iterator* it ) override;
void clear() { s349.clear(); }
void add( s484* el ) { s349.push_back( el ); }
void erase( size_t n ) { s349.erase( begin( s349 ) + n ); }
size_t size() const { return s349.size(); }
s483* sort( bool reverse, s840* cmp ) override;
std::vector<s485>& s320() { return s349; }
const std::vector<s485>& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s750
: public s326{
protected:
typedef s1417 s1386;
static s341 s348;
s1386 s349;
s1386::iterator s318;
std::wstring s499;
static void s387( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1314( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s1002( s483** s274, size_t n );
static void s1075( s483** s274, size_t n );
static void s1745( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
void s1160( s1905& s77, std::wstring& s1273, std::wstring& s644,
std::vector<s1::s9<s6::s141>>& s94, const s263* ast_, 
const s6::s1695& s1759 );
public:
s750( s262* s300 )
: s326( s300, NULL, NULL ) {}
s750( s262* s300, s272* s588, const s263* ast_ )
: s326( s300, s588, ast_ ) {}
s750( s262* s300, s272* s588, const std::wstring& s77,
const s263* ast_ = NULL, const s1720& tbfr=s1738 );
s750( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s750( const s750& right );
virtual ~s750() override;
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s1061 s319() const override;
s1061 s937() const override { return Types.Int; }
s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const override;
size_t s1138() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s485 operator[]( size_t n ) { return s349[n]; }
const s485& operator[]( size_t n ) const { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
s1144 s1194() override;
void clear() { s349.clear(); }
void add( s485 el ) { s349.push_back( el ); }
void assign( const std::vector<s485>& v );
size_t size() const { return s349.size(); }
std::vector<s485>& s320() { return s349; }
const std::vector<s485>& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s959
: public s750{
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
void s1160( s1905& s77, s272* s588, const s6::s1695& s1759 );
virtual void s1158( s1905& s1273 );
static void s387( s483** s274, size_t n );
static void s1265( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1314( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s1002( s483** s274, size_t n );
static void s1075( s483** s274, size_t n );
public:
s959( s262* s300 ) : s750( s300 ) {}
s959( s262* s300, s272* s588, s1905& s77, const s263* ast_ = NULL,
const s6::s1695& s1759 = s1736 );
s959( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s959( const s959& right, const s263* ast_ = NULL );
virtual ~s959() override {}
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
void s500( const s272* s879, bool fr=true ) override;
s1061 s1195( s1905& s1273, s813::Cont& s588 );
void load( s1905& s77, s272* s588, const s6::s1695& s1759 );
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s1935( Stream* ) const override;
static bool s2179( s1905& s );
};
class s1292
: public s1401<s1375, tdbyte_t, s1292, s1295>{
protected:
typedef s1375 s1386;
typedef s1292 s1167;
static s341 s348;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1264( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1314( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1338( s483** s274, size_t n );
static void s1354( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
void s1160( s1905& s77,
s483* s588, const s6::s1695& s1759 );
public:
typedef s1293 s1139;
s1292( s262* s300 ) : s1401( s300, NULL, NULL ) {}
s1292( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1695& s1759=s1736 );
s1292( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s1292( const s1292& right, const s263* ast_ = NULL );
virtual ~s1292() override;
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
size_t s1138() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
void load( s1905& s77, s483* s588, const s6::s1695& s1759 );
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
tdbyte_t operator[]( size_t n ) { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
Iterator* s1164( const s483* idx ) override;
Iterator* s1183( const s483* s349 ) override;
s271* s1335( tdbyte_t el ) { return new s1295( s300, el ); }
s483* s1190( Iterator* it ) override;
void clear() { s349.clear(); }
void add( tdbyte_t el ) { s349.push_back( el ); }
void erase( size_t n ) { s349.erase( begin( s349 ) + n ); }
size_t size() const { return s349.size(); }
s1386& s320() { return s349; }
const s1386& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s316 TDVector;
class s324;
class s324
: public s1369<s1387, s486, s486, s324>{
protected:
typedef s1387 s1386;
typedef s324 s1167;
static s341 s348;
s1386::iterator s318;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s1630( s483** s274, size_t n );
static void s332( s483** s274, size_t n );
static void s780( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1463( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1592( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
virtual void s1160( const std::wstring& s77, std::wstring& s1273, std::wstring& s644,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
void s1158( const std::wstring& s1273, s1061& pt, s1061& et,
s1061& kt, s1061& vt ) const;
void s1313( const std::vector<s271*>& v, s483* s588 );
public:
typedef s938 s1139;
s324( s262* s300 ) : s1369( s300, NULL, NULL ) {}
s324( s262* s300, s1061 s1201, s1061 s1276, s1061 s1181,
s1061 s709, s272* s588, const s263* ast_ = NULL );
s324( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL );
s324( const s324& right, const s263* ast_ = NULL );
s324( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL, s1061 s709 = 0, s1061 s1181 = 0,
s1061 s1638 = 0, s1061 s1276 = 0);
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s1061 s1195( const std::wstring& s1273, s813::Cont& s588,
s1061& et,	s1061& kt, s1061& vt ) const;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
size_t s1138() const override { return 1; }
void s500( const s272* s879, bool fr=true ) override;
void load( const std::wstring& s77, s272* s588, const std::wstring& s72 );
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
s1386& s320() { return s349; }
const s1386& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1382;
class s1382
: public s1369<s1381, s486, s486, s1382>{
protected:
typedef s1381 s1386;
typedef s1382 s1167;
static s341 s348;
s1386::iterator s318;
std::wstring s499;
static void s332( s483** s274, size_t n );
static void s780( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1463( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
virtual void s1160( const std::wstring& s77, std::wstring& s1273, std::wstring& s644,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
public:
typedef s1383 s1139;
s1382( s262* s300 ) : s1369( s300, NULL, NULL ) {}
s1382( s262* s300, s1061 s1200, s1061 s325, const s263* ast_ = NULL );
s1382( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL );
s1382( const s1382& right, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s1061 s1195( const std::wstring& s1273, s813::Cont& s588 );
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1061 s1188( const std::wstring& s1553, const std::vector<s485>& l ) const override;
size_t s1138() const override { return 0; }
void s500( const s272* s879, bool fr=true ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
Iterator* s1185() override;
Iterator* s1189() override;
s1386& s320() { return s349; }
const s1386& s320() const { return s349; }
virtual std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s324 TDIndex;
class s959;
class s604
: public s591{
std::vector<s1061> types;
std::vector<s488> s649;
public:
s604( s262* s300, s272* s588, s591* s587, s563 ct,
const std::vector<s271*>& l, const s263* s701 );
void s648( s1061 type, s591* pOvr );
virtual s486 s497( s483** s274, size_t s498 ) override;
};
class s838
: public s591{
std::vector<s1061> s1903;
bool s2104;
s1::s9<s959> s2110;
s483* s1896( s483** s274, size_t s498 ) override;
s838( const s838& );
public:
s838( s262* s300 );
s838( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l, const s263* s701, s1061 s2121 = 0, bool s2104 = true, bool s2176 = true );
s838( s262* s300, s272* s592, const std::vector<s1061>& l, 
s1061 pt, const s263* s701 );
s838( s838& s1901, s272* s592, s591* s593, const std::vector<s485>& l, const s263* s701 );
std::wstring s834() const override;
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s486 s497( s483** s274, size_t s498 ) override;
void s500( const s272* s1672, bool proc ) override;
s483* s496() override { return this; }
s1061 s1328() const { return s1903.back(); }
s271* s335( s591* s2057, s272* impl ) const override;
void s2133( s483* s2124, bool s2176 ) override;
using s483::s355;
using s483::s1895;
s483* s355( s272* s588, const std::vector<s1061>& vt ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l,
const s263* ast_ ) const override;
s591* s1685( s1905& s278, s591* s215,	s561* cs ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
std::wstring trace( const char* topics ) const override;
};
class s839
: public s591{
public:
s839( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701, bool s2176 = true );
s839( const s839& right, s272* s592, s591* s593 );
s1905& s299() const override { return s852; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s896
: public s591{
int code;
public:
s896( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s606
: public s591{
public:
s606( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s2077
: public s591{
public:
s2077( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s607
: public s591{
public:
s607( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l,
const s263* s701, bool s2176 = true );
s607( s262* s300 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1407
: public s591{
s371 s1502;
s486 varval;
s485 s308;
s371 s311;
s1529 s312;
s485 lambda;
public:
s1407( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701, bool s2176 );
s1407( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1939
: public s591{
public:
s1939( s262* s300, s272* s588, s591* s587, std::vector<s271*>& l, 
const s263* s701 );
s1939( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s608
: public s591{
s579 s620;
std::vector<s579> s621;
public:
enum s1141{ s1223, s1224 };
s608( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701,
bool s2176 = true );
s608( const s608& right, s272* s588, s591* s587 );
void s500( const s272* s1672, bool proc ) override;
void s736( bool proc );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s2133( s483* s2124, bool s2176 ) override;
};
class s611
: public s591{
s361 s78;
public:
s611( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s611( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s613
: public s591{
public:
s613( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s613( s262* s300 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s612
: public s591{
s371 s76;
s361 s619;
s1::s9<s613> ctch;
public:
s612( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s612( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s755
: public s591{
std::vector<std::wstring> fields;
public:
s755( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1680
: public s591{
public:
typedef s483* (s272::*s1682)(s483**, size_t);
private:
s1682 s1684;
s485 subject;
public:
s1680( s262* s300, s272* s588, s591* s587, s1682 _ptr,
s561* cs, const s263* s701 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1681
: public s591{
public:
typedef s483* (s483::*s1683)(s483**, size_t);
private:
s1683 s1684;
s485 subject;
public:
s1681( s262* s300, s272* s588, s591* s587, s1683 _ptr,
const std::vector<s271*>& s274, s1905& s676, s1061 s1072, const s263* s701, bool s2176 );
s1681( const s1681&, s272* s588, s591* s587 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s2133( s483* s2124, bool s2176 ) override;
};
class s1609
: public s591{
s486 cmd;
std::thread s823;
public:
s1609( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1609( const s1609& );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1607
: public s591{
public:
s1607( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1607( const s1607& );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1604
: public s591{
public:
s1604( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701, bool s2177 );
s1604( const s1604& right, s272* s592, s591* s593 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1608
: public s591{
public:
s1608( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1608( const s1608& );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1603
: public s591{
s1603( const s1603& q):s591(q){ throw; }
public:
s1603( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701,
bool s2176 );
s1603( const s1603& right, s272* s588, s591* s587 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1885
: public s591{
public:
s1885( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1885( const s1885& );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s609
: public s591{
s485 s42;
bool lout;
public:
enum s1141{ s1233, s1469, s1590, s1967, s1968, s1571, s1933, s1917, 
s1919, s1920, s1918, s1932, s1569, s1570 };
s609( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701,
bool s2176 = false );
s609( const s609& right, s272* s588, s591* s587 );
s609( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;	
void s2133( s483* s2124, bool s2176 ) override;
};
class s1940
: public s591{
s485 source;
bool lin;
public:
enum s1141{ s1226, s1967, s1968, s1571, s1933, s1932 };
s1940( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1940( s262* s300 );
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
template<class _Cont, class s1311, class Der>
s1143* s313<_Cont, s1311, Der>::s1975( Der** pv, typename _Cont::iterator& s1981 ){
typename _Cont::iterator s1591 = s1981;
if( s1981 != (*pv)->s349.end() )
++s1591;
s1143* s685 = new s1143( (*pv)->s300, (*pv)->ns,
new typename Der::s1139( (*pv)->s300, *pv, s1981, s1591 ), NULL );
s685->s500( (*pv)->ns, true );
return s685;}
template <class _Cont, class s1311, class Der>
void s313<_Cont, s1311, Der>::s350(){
s300->TR().s1162( s493, s7::s1411, s1512::s1507 );
s348.insert( std::make_pair( L"size", new s337( L"size", &s313<_Cont, s1311, Der>::s328, s1151,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"clear", new s337( L"clear", &s313<_Cont, s1311, Der>::s330, s1152,
{ s1122() }, 0, 0, false ) ) );}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s350(){
s313<_Cont, s1311, Der>::s350();
s348 = s313<_Cont, s1311, Der>::s342();
s348.insert( std::make_pair( L"coincide", new s337( L"coincide", &s1401<_Cont, s1311, Der, s1582>::s1950, s1151,
{ s1122(), s1122( { s1415 } ), s1122( { s7::s1394 } ) }, 0, 1, true,
{L"list:", L":back"}) ) );
s348.insert( std::make_pair( L"max-element", new s337( L"max-element", &s1401<_Cont, s1311, Der, s1582>::s1211,
0, { s1122(), s1122( { s1415 } ), 
s1122( { s1415, s7::s1398 } ),
s1122( { s7::s1398 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"max-element-idx", new s337( L"max-element-idx", &s1401<_Cont, s1311, Der, s1582>::s1210,
s1152, { s1122(), s1122( { s1415 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"min-element", new s337( L"min-element", &s1401<_Cont, s1311, Der, s1582>::s2090,
0, { s1122(), s1122( { s1415 } ), 
s1122( { s1415, s7::s1398 } ),
s1122( { s7::s1398 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"min-element-idx", new s337( L"min-element-idx", &s1401<_Cont, s1311, Der, s1582>::s2089,
s1152, { s1122(), s1122( { s1415 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"is-subset", new s337( L"is-subset", &s1401<_Cont, s1311, Der, s1582>::s2088, s1148,
{ s1122(), s1122( { s1415 } ), s1122( { s7::s1394 } ) }, 0, 1, true ) ) );
s348.insert( std::make_pair( L"sort", new s337( L"sort", &s1401<_Cont, s1311, Der, s1582>::s1267, 0,
{ s1122(), s1122( { s1415 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"reverse", new s337( L"reverse", &s1401<_Cont, s1311, Der, s1582>::s1254, 0,
{ s1122(), s1122( { s1415 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"shuffle", new s337( L"shuffle", &s1401<_Cont, s1311, Der, s1582>::s1593, 0,
{ s1122(), s1122( { s1415 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"unique", new s337( L"unique", &s1401<_Cont, s1311, Der, s1582>::s2094, 0,
{ s1122(), s1122( { s1415 } ) }, 0, 1, true ) ) );
s348.insert( std::make_pair( L"for-each", new s337( L"for-each", &s1401<_Cont, s1311, Der, s1582>::s1745, s1152,
{ s1122(), s1122( { s1415 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"find-adjacent", new s337( L"find-adjacent", &s1401<_Cont, s1311, Der, s1582>::s1587, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"subseq", new s337( L"subseq", &s1401<_Cont, s1311, Der, s1582>::s1493,
s1415, { s1122( {s1151} ), s1122( { s1151, s1151 } ) }, 1, 2 ) ) );
s348.insert( std::make_pair( L"begin", new s337( L"begin", &s1401<_Cont, s1311, Der, s1582>::s1583, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"end", new s337( L"end", &s1401<_Cont, s1311, Der, s1582>::s1586, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"front", new s337( L"front", &s1401<_Cont, s1311, Der, s1582>::s1635, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"back", new s337( L"back", &s1401<_Cont, s1311, Der, s1582>::s1621, 0,
{ s1122() }, 0, 0 ) ) );
s348.equal_range( L"begin" ).first->second->s1261( true );
s348.equal_range( L"end" ).first->second->s1261( true );
s348.equal_range( L"front" ).first->second->s1261( true );
s348.equal_range( L"back" ).first->second->s1261( true );
s348.equal_range( L"max-element" ).first->second->s1261( true );
s348.equal_range( L"max-element-idx" ).first->second->s1261( true );
s348.equal_range( L"min-element" ).first->second->s1261( true );
s348.equal_range( L"min-element-idx" ).first->second->s1261( true );
s348.equal_range( L"reverse" ).first->second->s1261( true );
s348.equal_range( L"find-adjacent" ).first->second->s1261( true );
s348.equal_range( L"sort" ).first->second->s1261( true );
s348.equal_range( L"shuffle" ).first->second->s1261( true );
s348.equal_range( L"unique" ).first->second->s1261( true );
this->s300->TR().s1162( this->s493, s7::s1411, s1512::s1507 );}
template <class _Cont, class s1311, class Der>
void s1576<_Cont, s1311, Der>::s350(){
s1401<_Cont, s1311, Der, s1311>::s350();
s348 = s1401<_Cont, s1311, Der, s1311>::s342();
s1061 tp = s7::s1398;
s348.insert( std::make_pair( L"sort", new s337( L"sort", &s1576<_Cont, s1311, Der>::s1267, 0,
{ s1122( { s1415 } ), s1122( { s1415, tp } ),
s1122( { tp } ), s1122() }, 0, 2/*, {L":asc", L":desc"}*/ ) ) );
s348.insert( std::make_pair( L"group-by", new s337( L"group-by", &s1576::s1464, 0,
{ s1122( { tp } ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"front", new s337( L"front", &s1576<_Cont, s1311, Der>::s1635, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"back", new s337( L"back", &s1576<_Cont, s1311, Der>::s1621, 0,
{ s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"join", new s337( L"join", &s1576<_Cont, s1311, Der>::s1973, Types.String,
{ s1122( { s1415, Types.String } ), s1122( { Types.String } ) }, 1, 1 ) ) );
s348.equal_range( L"front" ).first->second->s1261( true );
s348.equal_range( L"back" ).first->second->s1261( true );
s348.equal_range( L"sort" ).first->second->s1261( true );
s348.equal_range( L"group-by" ).first->second->s1261( true );
this->s300->TR().s1162( this->s493, s7::s1411, s1512::s1507 );}
template <class _Cont, class s1421, class s1423, class Der>
void s1369<_Cont, s1421, s1423, Der>::s350(){
s313<_Cont, s1421, Der>::s350();
s348 = s313<_Cont, s1421, Der>::s342();
s348.insert( std::make_pair( L"max-element", new s337( L"max-element", &s1369::s1211,
0, { s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"min-element", new s337( L"min-element", &s1369::s2090,
0, { s1122() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"is-subset", new s337( L"is-subset", &s1369::s2088, s1148,
{ s1122( { s7::s1394 } ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"regroup-by", new s337( L"regroup-by", &s1369::s1485, 0,
{ s1122( { s7::s1398 } ) }, 1, 1 ) ) );
s348.equal_range( L"max-element" ).first->second->s1261( true );
s348.equal_range( L"min-element" ).first->second->s1261( true );
s348.equal_range( L"regroup-by" ).first->second->s1261( true );
this->s300->TR().s1162( this->s493, s7::s1411, s1512::s1507 );}
template <class _Cont, class s1311, class Der>
s1061 s313<_Cont, s1311, Der>::
s1188( const std::wstring& s1553, const std::vector<s485>& l ) const{
s1061 s685 = 0;
return s685;}
template <class _Cont, class s1311, class Der, class s1582>
s1061 s1401<_Cont, s1311, Der, s1582>::
s1188( const std::wstring& s1553, const std::vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"begin" || s1553 == L"end" ) {
s813::Cont s1279;
s1061 s1099 = this->ValType();
s685 = this->s300->TR().s1046( std::vector<s1061>(
{ s1580, 1, s1099, 0 } ) );}
else if( s1553 == L"front" || s1553 == L"back" )
s685 = this->ValType();
else if( s1553 == L"max-element-idx" || s1553 == L"min-element-idx" )
s685 = this->s937();
else if( s1553 == L"sort" || s1553 == L"reverse" || s1553 == L"unique" )
s685 = this->s352();
else if( s1553 == L"find-adjacent" || s1553 == L"max-element" || 
s1553 == L"min-element") {
s813::Cont s1279;
s1061 s1099 = this->ValType();
s685 = this->s300->TR().s1046( std::vector<s1061>( 
{ s1580, 1, s1099, 0 } ) );}
else
s685 = s313<_Cont, s1311, Der>::s1188( s1553, l );
return s685;}
template <class _Cont, class s1311, class Der>
s1061 s1576<_Cont, s1311, Der>::
s1188( const std::wstring& s1553, const std::vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"front" || s1553 == L"back" )
s685 = this->ValType();
else if( s1553 == L"sort" )
s685 = this->s352();
else if( s1553 == L"group-by" ) {
s813::Cont s1279;
s1061 s1099 = this->s325;
std::wstring ts = Types( this->s300, Types.Vector )->s353() + L"<" +
this->s300->TR().s1352( this->s300->TR().s804( s1099 ) ) + L">";
s1061 s1467 = l[0].s15<s838*>()->s1328();
s685 = this->s300->TR().s1046( std::vector<s1061>( 
{ Types.Index, 2, s1467, 0, s1099, 0 } ) );}
else
s685 = s1401<_Cont, s1311, Der, s1311>::s1188( s1553, l );
return s685;}
template <class _Cont, class s1421, class s1423, class Der>
s1061 s1369<_Cont, s1421, s1423, Der>::
s1188( const std::wstring& s1553, const std::vector<s485>& l ) const{
s1061 s685 = 0;
if( s1553 == L"max-element" )
s685 = this->s319();
else if( s1553 == L"regroup-by" ) {
s813::Cont s1279;
s1061 s1099 = this->s325;
s1061 s1467 = l[0].s15<s838*>()->s1328();
s1061 s1456 = this->s300->TR().s1046( std::vector<s1061>( 
{ s1717, 2, s1467, 0, s1099, 0 } ) );
s685 = this->s300->TR().s1046( std::vector<s1061>( 
{ Types.Index, 1, s1456, 0 } ) );}
else
s685 = s313<_Cont, s1421, Der>::s1188( s1553, l );
return s685;}
template <class _Cont, class s1421, class s1423, class Der>
s271* s1369<_Cont, s1421, s1423, Der>::s1335( std::pair<s1421, s1423>& el ){
return new s959( this->s300, std::vector<s271*>({el.first, el.second}) ); }
template <class _Cont, class s1421, class s1423, class Der>
bool s1369<_Cont, s1421, s1423, Der>::insert( s483* s152, s483* s349 ){
return this->s349.insert( std::make_pair( s152, s349 ) ).second;}
template <class _Cont, class s1421, class s1423, class Der>
s483* s1369<_Cont, s1421, s1423, Der>::find( s483* s152 ){
auto it = this->s349.find( s152 );
if( it != end( this->s349 ) )
return it->second;
return NULL;}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1583( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1143( pv->s300, pv->ns, pv->s1185(), NULL );}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1586( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1143( pv->s300, pv->ns, pv->s1189(), NULL );}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1493( s483** s274, size_t s498 ){
if( s498 < 3 || s498 > 4 )
throw new s2::s16( L"subseq: wrong number of arguments" );
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv = ( (s1130*)s274[1] );
int s1491 = (int)*s274[2];
int s1492;
if( s498 == 4 )
s1492 = (int)*s274[3];
else
s1492 = (int)pv->s349.size() - 1;
s385 range( s1491, s1492 );
s1144 pr = range.s1194( pv );
s939* s1486;
if( pv->s1138() >= 1 && pr.first.s15<s1125*>()->Reversed() ) {
typename _Cont::reverse_iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1146();
s1520 = pr.second.s15<s939*>()->s1146();
s1486 = new s939( pv->s300, pv, s1519, s1520 );}
else {
typename _Cont::iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1145();
s1520 = pr.second.s15<s939*>()->s1145();
s1486 = new s939( pv->s300, pv, s1519, s1520 );}
s385* s685 = new s385( pv->s300, pv, s1486 );
*s274 = s685;}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1267( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = NULL;
s1144 pr = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
if( ( (s326*)pv )->s1138() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s591* s1206 = NULL;
if( s498 == 3 )
s1206 = (s591*)s274[2];
s1301<s1311> qqq;
qqq.s859 = s1206;
if( pv->s1138() >= 1 && pr.first.s15<s1125*>()->Reversed() ) {
typename _Cont::reverse_iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1146();
s1520 = pr.second.s15<s939*>()->s1146();
std::sort( s1519, s1520, /*pv->s1325*/qqq );
}
else {
typename _Cont::iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1145();
s1520 = pr.second.s15<s939*>()->s1145();
std::sort( s1519, s1520, /*pv->s1325*/ qqq );
}
*s274 = pv;}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1587( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
s1130* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1415 ) {
pr = (s385*)s274[1];
pv = (s1130*)pr->s819();}
else
pv = ( (s1130*)s274[1] );
s1144 rp;
if( pr ) {
rp = pr->s1194( pv );}
else
rp = pv->s1194();
typename _Cont::iterator s1519, s1520;
s1519 = rp.first.s15<s939*>()->s1145();
s1520 = rp.second.s15<s939*>()->s1145();
typename _Cont::iterator s1981 = std::adjacent_find( s1519, s1520, pv->s1584 );
typename _Cont::iterator s1591 = s1981;
if( s1981 != pv->s349.end() )
++s1591;
s1143* s685 = new s1143( pv->s300, pv->ns,
new s939( pv->s300, pv, s1981, s1591 ), NULL );
s685->s500( pv->ns, true );
*s274 = s685;}
template <class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1745( s483** s274, size_t s498 ){
using s1130 = Der;
using s939 = typename Der::s1139;
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
s939* s1519 = rp.first.s15<s939*>(), *s1520 = rp.second.s15<s939*>();
std::vector<s485> s1839( 1 );
while( !( s1519 == s1520 ) ) {
s1839[0] = s1519->s962();
s1763->s596( s1839 );
s1763->s497( 0, 0 );}}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1635( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
*s274 = (s483*)pv->s1335( pv->s349.front() );}
template<class _Cont, class s1311, class Der, class s1582>
void s1401<_Cont, s1311, Der, s1582>::s1621( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
*s274 = (s483*)pv->s1335( pv->s349.back() );}
template<class _Cont, class s1311, class Der>
void s1576<_Cont, s1311, Der>::s1635( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
s485 s1060 = pv->s349[0];
*s274 = s1060.s15<s483*>();}
template<class _Cont, class s1311, class Der>
void s1576<_Cont, s1311, Der>::s1621( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
s485 s1060 = pv->s349[pv->s349.size() - 1];
*s274 = s1060.s15<s483*>();}
template <class _Cont, class s1311, class Der>
void s1576<_Cont, s1311, Der>::s1267( s483** s274, size_t s498 ){
using s939 = typename Der::s1139;
Der* pv = NULL;
s1144 pr = s313<_Cont, s1311, Der>::s1426( s274[1], &pv );
if( ( (s326*)pv )->s1138() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s591* s1206 = NULL;
if( s498 == 3 )
s1206 = (s591*)s274[2];
s1301<s1311> s1969;
if( s1206 )
s1969.s859 = s1206;
if( pv->s1138() >= 1 && pr.first.s15<s1125*>()->Reversed() ) {
typename _Cont::reverse_iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1146();
s1520 = pr.second.s15<s939*>()->s1146();
std::sort( s1519, s1520, s1969 );}
else {
typename _Cont::iterator s1519, s1520;
s1519 = pr.first.s15<s939*>()->s1145();
s1520 = pr.second.s15<s939*>()->s1145();
std::sort( s1519, s1520, s1969 );}
*s274 = pv;}
template<class _Cont, class s1311, class Der>
inline void s1576<_Cont, s1311, Der>::s1464( s483** s274, size_t s498 ){
if( s498 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s494() != s1245 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s591* pf = (s591*)s274[2];
s324* s153 = (s324*)*s274;
std::vector<s485>s861;
s861.resize( 1 );
typename _Cont::iterator s1518 = pv->s349.begin();
for( ; s1518 != pv->s349.end(); ++s1518 ) {
s485 s1065 = *s1518;
s861[0] = s1065;
pf->s596( s861 );
s486 s1057 = pf->s497( 0, 0 );
s483* s1454 = s153->find( s1057 );
if( s1454 )
((s316*)s1454)->add( s1065->s335(0,0) );
else {
s316* s1482 = new s316( pv->s300, pv->s325, pv->ns, NULL );
s1482->s500( pv->ns );
s1482->add( s1065->s335(0,0) );
s153->insert( (s483*)s1057->s335(0,0), (s483*)s1482 );}}}
template<class _Cont, class s1311, class Der>
inline void s1576<_Cont, s1311, Der>::s1973( s483** s274, size_t s498 ){
Der* pv = ( (Der*)s274[1] );
const std::wstring& s72 = ( (s359*)s274[2] )->s320();
std::wstring s685;
if( pv->s349.empty() ) {
*s274 = new s359( pv->s300 );
(*s274)->s1262();
return;}
s685 = pv->s349.front()->to_wstring();
for( size_t n = 1; n < pv->s349.size(); ++n )
s685 += s72 + pv->s349[n]->to_wstring();
*s274 = new s359( pv->s300, s685 );
(*s274)->s1262();}
template<class _Cont, class s1421, class s1423, class Der>
inline void s1369<_Cont, s1421, s1423, Der>::s1485( s483** s274, size_t s498 ){
if( s498 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s494() != s1245 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s591* pf = (s591*)s274[2];
s324* s153 = (s324*)*s274;
std::vector<s485>s861;
s861.resize( 1 );
typename _Cont::iterator s1518 = pv->s349.begin();
for( ; s1518 != pv->s349.end(); ++s1518 ) {
s485 s1065 = *s1518->second;
s861[0] = s1065;
pf->s596( s861 );
s486 s1057 = pf->s497( 0, 0 );
s483* s1454 = s153->find( s1057 );
if( s1454 )
((s316*)s1454)->add( s1065->s335(0,0) );
else {
s316* s1482 = new s316( pv->s300, pv->s325, pv->ns, NULL );
s1482->s500( pv->ns, true );
s1482->add( s1065->s335(0,0) );
s153->insert( (s483*)s1057->s335(0,0), (s483*)s1482 );}}}
class s415
: public s336{
static s341 s348;
std::wstring path;
std::wstring s524;
s316 s754;
s316 s809;
static void s1236( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s1677( s483** s274, size_t n );
static void s416( s483** s274, size_t n );
static void s417( s483** s274, size_t n );
static void s990( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s415( s262* s300 ) : s336( s300, NULL, NULL ), s754(s300), s809(s300) {}
s415( s262* s300, const std::wstring& s77, const s263* ast_=NULL );
s415( const s415& right, const s263* ast_ = NULL );
s415( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s754; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1605
: public s591{
public:
s1605( s262* s300, s272* s592, s591* s593,
const std::vector<s271*>& l, const s263* s701 );
const std::wstring& s299() const override { return s1316; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
} // namespace
namespace transd{
class s605
: public s591{
public:
s605( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701, bool s2176 = false );
s605( const s605& right, s272* s592, s591* s593 );
s1905& s299() const override { return s233; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s712( s1905& s278, s371* ref,
s1905& s334 ) const;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s305
: public s591{
s485 s306;
public:
s305( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l,
const s263* s701,	bool s2176 = false );
s305( const s305& right, s272* s592, s591* s593 );
s1905& s299() const override { return s255; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s307
: public s591{
s485 s308;
s489 s309;
s486 s310;
s371 s311;
s346 s312;
public:
s307( s262* s300, s272* s588, Transd* s587, const std::vector<s271*>& l, const s263* s701 );
s1905& s299() const override { return s254; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s614
: public s591{
s489 s713;
s486 varval;
s485 s308;
s485 where;
s485 s1060;
s371 s311;
s1529 s312;
public:
s614( s262* s300, s272* s588, Transd* s587, const std::vector<s271*>& l,
const s263* s701, bool s2176 = true );
s1905& s299() const override { return s260; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s610
: public s591{
public:
s610( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s610( s262* s300 );
s1905& s299() const override { return s256; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s615
: public s591{
static s1::s9<s262> s906;
public:
s615( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701, bool s2177 = true );
s615( s262* s300 );
const std::wstring& s299() const override { return s261; }
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s797
: public s591{
public:
s797( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s797( s262* s300 );
s1905& s299() const override { return s772; }
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s775
: public s591{
std::wstring s904;
public:
s775( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s775( s262* s300 );
const std::wstring& s299() const override { return s821; }
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1307
: public s591{
public:
s1307( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1307( s262* s300 );
s1905& s299() const override { return s1317; }
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1610
: public s591{
public:
s1610( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1610( s262* s300 );
s1905& s299() const override { return s1620; }
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
};
class s1783
: public s1::s10{
public:
s1783() { }
virtual ~s1783() { }
virtual s486 s760( const std::wstring& s76, bool s714 = true ) const = 0;
virtual void s863( s750& s153 ) const = 0;
virtual void s863( s959& s153 ) const = 0;
virtual void s545( std::vector<std::wstring>& s153 ) const = 0;
virtual size_t s322() const = 0;
};
class s776;
typedef s1::s9<s1783> s822;
bool s1802( s822 l, s822 r );
struct s744 : public s1::s10{
enum Verb { s1775, s1776, s1774, s1777, s2059, s1773 };
Verb verb;
s744()
: verb( s1775 )
{	}
};
class s1781;
typedef std::multimap<s486, s822, s1425> s1786;
typedef std::pair<s1786::iterator, s1786::iterator> s1788;
typedef std::list<s822> s1784;
extern s1784 s1846;
extern s1784::iterator s1847;
struct s1785{
bool operator()( const s486 l, const s486 r ) const{
return l->operator<( ( s483* )&( *r ) );}
bool operator()( const s483* l, const s483* r ) const{
return l->operator<( r );}
bool operator()( const s486 l, const std::pair<s486, s822>& r ) const{
return l->operator<( ( s483* )&( *r.first ) );}
bool operator()( const std::pair<s486, s822>& l, const s486 r ) const{
return l.first->operator<( ( s483* )&( *r ) );}
};
struct s1787{
s1788 pr;
std::wstring s977;
size_t dist;
bool operator<( s1787 const& r ) const{
return dist < r.dist;}
};
class s1782{
protected:
s1781* pdb;
s1784* ptr;
s1784::iterator fi;
s1784::iterator se;
s1784::iterator cur;
public:
s1782( s1781* s1806 );
virtual ~s1782();
virtual void s1871( void* f, void* s ) = 0;
virtual void s1874() = 0;
virtual bool s1835() = 0;
virtual s1783* s1845() = 0;
void sort() { ptr->sort( s1802 ); }
void clear() { ptr->clear(); }
bool empty() { return ptr->empty(); }
void swap( s1782* r ) { ptr->swap( r->s320() ); }
s1784& s320() { return *ptr; }
s1781* s1792() { return pdb; }
virtual void s1831( std::vector<std::wstring>& s153 ) = 0;
};
struct s1804{
bool operator()( const s1787* l, const s1787* r ) const{
return l->operator<( *r );}
bool operator()( const s1787& l, const s1787& r ) const{
return l.operator<( r );}
};
typedef std::set<s1787, s1804 > s1789;
class s1778{
public:
enum s1791 { s1856, s1851, s1854, s1852, s1855, s1853, s2150 };
private:
std::wstring field;
s1791 op;
s485 par, s349;
static const std::vector<std::wstring> s1879;
public:
s1778( s262* s300, s272* s588, const std::wstring& s, size_t& pos );
void s500( s272* ns );
void select( s1781* pdb, s1787& s153 );
};
class s1779;
class s1779{
public:
enum s1780 { s1813, s1814, s1812 };
private:
s1780 s1817;
std::vector<s1779> subs;
std::vector<s1778> s1811;
public:
s1779( s262* s300, s272* s588, const std::wstring& s, size_t& pos, s1780 s1817 );
s1779( const s1779& r );
void s500( s272* ns );
void s1810( s262* s300, s272* s588, const std::wstring& s, size_t& pos );
void select( s1781* pdb, s1782* s153 );
};
class s1781
: public s336{
protected:
std::map<std::wstring, s1786> s871;
bool s2068;
public:
s1781( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ ), s2068( true )	{	}
virtual ~s1781();
virtual void release() override;
bool s2069() const { return s2068; }
virtual void select( s1905& field, s1778::s1791, const s483* s1065,
s1787& s153 ) = 0;
virtual void intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ) = 0;
virtual void intersect( const s1787& fi, s1782* s153 ) = 0;
virtual void s855( s1905& s858 ) = 0;
virtual s1782* s1818() const = 0;
virtual void s1870( s1782* s153 ) = 0;
virtual bool s2010( s1905& s ) const = 0;
virtual s1061 s2015( s1905& s858 ) const = 0;
virtual void s1832( std::vector<std::wstring>& s153) const = 0;
};
struct s1712 : public s744{
enum s837 { s828=0, s831 };
int distinct;
int	s888;
std::wstring s887;
int s874;
s1712()
: distinct( -1 ), s888( -1 ), s874( -1 )
{	}
};
struct s1722 : public s744{
};
struct s1708 : public s744{
};
struct s1986 : public s744{
};
struct s1710 : public s1::s10 { };
struct s1711 : public s1710{
s485 what;
s485 where;
s485 s1867;
s485 s889;
s485 s1072;
s485 s874;
};
struct s1721 : public s1710{
s485 what;
s485 where;
s485 s1867;
};
struct s1707 : public s1710{
s485 at;
s485 values;
s1::s9<s1721> s1761;
};
struct s1985 : public s1710{
s485 what;
s485 where;
s485 s1867;
s485 s2057;
s485 s1072;
};
class s897
: public s591{
size_t s908;
s486 s685;
protected:
void s1911( const s577& pl ) const override { }
public:
s897() : s591( NULL, NULL, NULL, NULL, s565, L"", NULL ), 
s685( new s360( NULL, false ) ){ }
void s907( size_t idx ) { s908 = idx; }
virtual s486 s497( s483** s705, size_t s498 ) override{
s485 l = s274[0];
s485 r = s274[1];
*s685.s15<s360*>()->s357() = l.s15<s750*>()->operator[]( s908 ).s15<s483*>()->
operator<( r.s15<s750*>()->operator[]( s908 ).s15<s483*>() );
s486 s905 = s685;
return s905;}
};
class s316;
class s791
: public s591{
s485 db;
s371 s2038;
s1::s9<s959> s2037;
s1::s9<s744> s810;
s1::s9<s1710> qp;
s371 s733;
s487 s783;
s1779* s1859;
s484* s1805( const std::wstring& s );
void s2063( s1781* base, s485 what, std::vector<std::wstring>& s895,
std::vector<s488>& s2061, std::vector<std::wstring>& s1868 );
void s1723( const std::vector<s271*>& l_,	TDException& s968 );
void s1725( const s272* s1672, bool proc );
s486 s1730( s483** s274, size_t s498 );
void s1724( const std::vector<s271*>& l_,	TDException& s968 );
void s1726( const s272* s1672, bool proc );
s486 s1731( s483** s274, size_t s498 );
void s2002( const std::vector<s271*>& l_,	TDException& s968 );
void s2004( const s272* s1672, bool proc );
s486 s2007( s483** s274, size_t s498 );
public:
enum s1141{ s1231, s2071, s1756, s2020, s2070, s1216, s1217, s1235, 
s1843, s2021, s1221, s1232, s1218, s1220,	s1230, s1754 };
s791( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
~s791();
s1905& s299() const override { return s818; }
void s500( const s272* s1672, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335( s591* s2057, s272* impl ) const override;
bool s556( s1905& s278, s371* s153, s1905& s334,	bool ) const override;
s271* s598( size_t off ) override;
};
class s776
: public s1783{
typedef std::map<std::wstring, s485> s727;
s727 s762;
s727* s2151;
size_t rechash;
s1::s9<s1602> pobj;
public:
s776() {}
s776( s262* s300, s272* s588, s1905& rec, const std::vector<std::wstring>& s743,
std::vector<s485>& types, const s1720& tbfr=s1738 );
s776( s262* s300, s1602& s588 );
s486 s760( s1905& s76, bool s714=true ) const override;
void s863( s750& s153 ) const override;
void s863( s959& s153 ) const override;
void s545( std::vector<std::wstring>& s153 ) const override;
size_t s322() const override;
bool operator==( const s776* p ) const;
bool operator<( const s776* p ) const;
std::wstring to_wstring( uint32_t s1565 = 0 ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
class s812
: public s1::s10{
typedef std::vector<s485> s735;
s735 s811;
size_t s800;
public:
s812() {}
s812( std::vector<std::wstring>& s732, s822 rec );
size_t s322() const;
bool operator==( const s812* p ) const;
bool operator<( const s812* p ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
typedef s1::s9<s812> s734;
struct s771{
std::size_t operator()( const s734 k ) const{
return k->s322();}
};
struct s715{
std::size_t operator()( const s734 l, const s734 r ) const{
return l->operator==( ( s812* )&( *r ) );}
};
struct s846{
std::size_t operator()( const s822 k ) const{
return k->s322();}
};
struct s845{
std::size_t operator()( const s822 l, const s822 r ) const{
return l.s15<s776*>()->operator==( ( s776* )&( *r ) );}
};
typedef std::unordered_map<s734, s822, s771, s715> s787;
extern s787::iterator s1848;
class s1796 
: public s1782{
s787* pind;
s787::iterator cur1;
public:
s1796( s1781* pdb );
virtual ~s1796(){}
void s1871( void* f, void* s ) override;
void s1874() override;
bool s1835() override;
s1783* s1845() override;
void s1831( std::vector<std::wstring>& s153 ) override {}
};
class s650
: public s1781{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
private:
static s341 s348;
BaseMap s651, s652, s653;
BaseMap::iterator s318;
s787 s757;
std::vector<std::wstring> s2145;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s786( s483** s274, size_t n );
static void s2142( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s752( s483** s274, size_t n );
static void s770( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s856( s483** s274, size_t n );
static void s2154( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1141 { s1753, s1751, s1749, s1750, s1752, s1842 };
s650( s262* s300, s272* s588 = NULL, const s263* ast_ = NULL );
s650( s262* s300, s272* s588, s1905& s77, const s263* ast_ = NULL );
s650( const s650& right, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)NULL; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s654( s1905& s194 );
void s379( s1602& obj );
void s655( s1905& q );
void s718( s1905& s824, const s1720& tbfr );
void s855( s1905& s858 ) override;
void select( s1905& field, s1778::s1791, const s483* s1065,	s1787& s153 ) override;
s1782* s1818() const override;
void s1870( s1782* s153 ) override;
void intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ) override;
void intersect( const s1787& fi, s1782* s153 ) override;
bool s2010( s1905& s ) const override;
s1061 s2015( s1905& s858 ) const override;
void s1832( std::vector<std::wstring>& s153) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1801;
class s1800
: public s1783{
public:
typedef std::vector<s486> s1793;
private:
s1793 s1861;
size_t rechash;
s1801* s1858;
public:
s1800() {}
s1800( const std::vector<s486>& v, s1801* s1858 );
s1800( s262* s300, s272* s588, s1905& rec,
const std::vector<std::wstring>& s743,
std::vector<s485>& types, const s1720& tbfr=s1738 ){ }
virtual ~s1800();
s486 s760( s1905& s76, bool s714 = true ) const override;
const s1793& s2016() const;
void s863( s750& s153 ) const override;
void s863( s959& s153 ) const override;
void s545( std::vector<std::wstring>& s153 ) const override;
virtual size_t s322() const override;
bool operator==( const s776* p ) const { return 0; }
bool operator<( const s776* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const{ return L""; }
void s304( std::wostream* pd, int s197 = 0 ) const{ }
};
class s1799 : 
public s1782{
public:
s1799( const s1799& r );
s1799( s1781* pdb );
virtual ~s1799();
void s1871( void* f, void* s ) override;
void s1874() override;
bool s1835() override;
s1783* s1845() override;
void s1831( std::vector<std::wstring>& s153 ) override;
};
class s1801
: public s1781{
public:
private:
static s341 s348;
s1784 rows;
std::vector<std::wstring> s806;
std::map<std::wstring, size_t> s1834;
std::vector<s822> s2060;
s1061 s2042;
std::wstring s499;
static void s1236( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s752( s483** s274, size_t n );
static void s770( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s2018( s483** s274, size_t n );
static void s2026( s483** s274, size_t n );
static void s2027( s483** s274, size_t n );
static void s856( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1141 { s1753, s1751, s1749, s1750, s1752, s1842, 
s2019 };
s1801( s262* s300, s272* s588 = NULL, const s263* ast_ = NULL );
s1801( s262* s300, s272* s588, s1905& s77, const s263* ast_ = NULL );
s1801( const s1801& right, const s263* ast_ = NULL );
virtual ~s1801();
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1061 s1188( s1905& s1553, const std::vector<s485>& l ) const override;
void release() override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)NULL; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s654( s1905& s194 );
void s655( s1905& q ){ }
void s718( s1905& s824, const s1720& tbfr );
void s855( s1905& s858 ) override;
void select( s1905& field, s1778::s1791, const s483* s1065,
s1787& s153 ) override;
s1782* s1818() const override;
void s1870( s1782* s153 ) override;
void intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ) override;
void intersect( const s1787& fi, s1782* s153 ) override;
size_t s1833( s1905& s1816 ) const;
void s1832( std::vector<std::wstring>& s153 ) const override { s153 = s806; }
bool s2010( s1905& s ) const override;
s1061 s2015( s1905& s858 ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1801;
class s2076
: public s1783{
private:
s486 rec;
public:
s2076( s486 d );
virtual ~s2076();
s486 s760( s1905& s76, bool s714 = true ) const override;
void s863( s750& s153 ) const override;
void s863( s959& s153 ) const override;
void s545( std::vector<std::wstring>& s153 ) const override;
virtual size_t s322() const override;
bool operator==( const s776* p ) const { return 0; }
bool operator<( const s776* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1565 = 0 ) const{ return L""; }
void s304( std::wostream* pd, int s197 = 0 ) const{ }
};
class s2075 : 
public s1782{
Iterator* s2081;
s326* s2083;
bool started;
public:
s2075( const s2075& r );
s2075( s1781* pdb );
virtual ~s2075();
void s1871( void* f, void* s ) override;
void s1874() override;
bool s1835() override;
s1783* s1845() override;
void s1831( std::vector<std::wstring>& s153 ) override;
};
class s2062
: public s1781{
private:
static s341 s348;
std::wstring s2080;
s326* pv;
s1061 s2042;
std::wstring s499;
void s350() override;
const s341& s342() const override { return s348; }
public:
s2062( s262* s300, s272* s588 = NULL, s326* pv = NULL, const s263* ast_ = NULL );
s2062( const s2062& r );
virtual ~s2062();
s483* s354( const s263& s701, s272* s588, s1905& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void release() override;
void* addr() override { return (void*)NULL; }
void s500( const s272* s879, bool ) override;
s271* s335( s591* s2057, s272* impl ) const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s654( s1905& s194 );
void s655( s1905& q ){ }
void s718( s1905& s824, const s1720& tbfr );
void s855( s1905& s858 ) override;
void select( s1905& field, s1778::s1791, const s483* s1065,
s1787& s153 ) override;
s1782* s1818() const override;
void s1870( s1782* s153 ) override;
void intersect( const s1787& fi1, const s1787& fi2,
s1784& s153 ) override;
void intersect( const s1787& fi, s1782* s153 ) override;
size_t s1833( s1905& s1816 ) const;
void s1832( std::vector<std::wstring>& s153 ) const override { s153.push_back( s2080 ); }
bool s2010( s1905& s ) const override;
s1061 s2015( s1905& s858 ) const override;
std::wstring to_wstring( uint32_t s1565 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
#define TRANSD_VERSION L"0.443"
void evaluateExpression( const std::wstring& s77 );
HPROG createAssembly();
void deleteAssembly( int n );
void loadProgram( HPROG handle, const std::wstring& s189 );
void s211( HPROG handle, s6::s143& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s691 );
void* callFunc( HPROG handle, const std::wstring& s77, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s601 );
void* s223( HPROG handle, const std::wstring& s278 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1112, const std::wstring& symName,
const std::wstring& s334 );
void importFile( HPROG handle, const std::wstring& s1112, const std::wstring& s44,
const std::wstring& s334 );
HPROG initShell( const std::wstring& s1112, const std::wstring& modText );
typedef s2::s16 TransdException;
} // namespace transd
