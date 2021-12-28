
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
class s1285{
int refs;
public:
s1285(){
refs=0;}
~s1285(){}
void reset(){
refs = 0;}
int s11(){
refs++;
return refs;}
int s12(){
refs--;
return refs;}
int s1286(){
return refs;}
};
#ifdef s1292
#define s1293(x) x;
#else
#define s1293(x)
#endif
template<bool>
struct s1287{
void s1288(){}
void s1289(){}
};
template<>
struct s1287<true>{
#ifdef s1292
static int s163;
void s1288() { s163++; }
void s1289() { s163--; }
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
int s1286(){
return refs;}
virtual void deallocate(){
delete this;}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template<class C, bool s1320=false>
class s1291
: public s1287<s1320>{
C* p;
s1285*	s1290;
public:
s1291(C *_p)
:p(_p){
if ( p ) {
s1290 = new s1285;
s1290->s11();
s1293( this->s1288() )}}
s1291( const s1291& ptr ){
if ( ptr.p ) {
p = ptr.p;
s1290 = ptr.s1290;
s1290->s11();}
else {
p = nullptr;
s1290 = nullptr;}}
s1291()
:p(nullptr){
s1290 = nullptr;}
template<class D> 
s1291( s1291<D> &pn ){
p = nullptr;
s1290 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1290 = pn.s1307();
s1290->s11();}}}
~s1291(){
if(	p && !s1290->s12()	) {
delete p;
delete s1290;
s1293( this->s1289() )}}
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1291& operator=( s1291<C> &s1348 ){
if ( p  && !s1290->s12() ) {
delete p;
delete s1290;
p = nullptr;
s1290 = nullptr;
s1293( this->s1289() )}
p = s1348.p;
if ( s1348.p ) {
s1290 = s1348.s1290;
s1290->s11();}
return *this;}
s1291& operator=( const s1291<C> &s1348 ){ return operator=((s1291<C>&) s1348); }
s1291& operator=( C* ptr ){
if ( p  && !s1290->s12() ) {
delete p;
delete s1290;
p = nullptr;
s1290 = nullptr;
s1293( this->s1289() )}
p = ptr;
if ( ptr ) {
s1290 = new s1285;
s1290->s11();
s1293( this->s1288() )}
return *this;}
template<class Base>
operator Base*(){
return checked_cast<C, Base>( p );}
template<class D>
s1291& operator=( s1291<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );}
template<class ToType>
ToType s15(){
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast(){
return dynamic_cast<ToType>( p );}
bool operator ==(const s1291<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1291<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1285* s1307() { return s1290; }
int s1286() { return s1290->s1286(); }
void s1342() { s1290->s11(); }
void s1341() {
if ( p  && !s1290->s12() ) {
delete p;
delete s1290;
p = nullptr;
s1290 = nullptr;
s1293( this->s1289() )}}
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
void s1123();
extern std::vector<std::wstring> s998;
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
s26.push_back( s998[n] );}
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
std::wstring s1080( s197, L' ' );
while( it != s26.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s26.crend() )
s685 += s1080;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s685 += ( i++ ? L"" : s1080 ) + s + L"\n";}
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
std::wstring s1886();
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
size_t& start, size_t& end, bool s887 = false );
void s55( const std::wstring& s, size_t s65, wchar_t c, size_t& start, 
size_t& end );
void s1003( const std::wstring& s, size_t& s65, const std::wstring& s1092 );
size_t count( const std::wstring& s77, const std::wstring& s1092, size_t start, size_t end,
bool s887 = false );
int s56( const std::wstring& s77, wchar_t s72, size_t& pos );
void s57( const std::wstring& s, const std::wstring& s72, 
std::vector<std::wstring>& s153, bool clr = true, bool s887 = false );
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
bool s1546( const wchar_t *str, long long *s349, wchar_t **end = NULL );
bool s1547( const wchar_t *str, unsigned long long *s349, wchar_t **end = NULL );
bool s63( const wchar_t *str, double *s349, wchar_t **end = NULL );
void s877( const std::wstring& s77, std::vector<std::wstring>& s153 );
std::wstring s1830( const std::wstring& s77, wchar_t c );
std::wstring s1255( const std::wstring& s, const std::wstring& chars );
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
void s81( std::wstring& s77, std::vector<std::wstring>& s1106, std::map<size_t, size_t>& s1039 );
template<class T>
std::wstring s1566( T value ) {
struct Numpunct : public std::numpunct<wchar_t> {
protected:
virtual wchar_t do_thousands_sep() const { return L','; }
virtual std::string do_grouping() const { return "\03"; }
};
std::wstringstream ss;
ss.imbue( { std::locale(), new Numpunct } );
ss << std::setprecision( 2 ) << std::fixed << value;
return ss.str();}
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
#define s1563(x) s5::conv.to_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#define s1563(x) x
#endif
namespace consutils {
void s1119();
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
#define s1560 371
#define s1559 379
} // namespace consutils
namespace s6{
enum s131{ s132, s133, s134, s139, 
s135, s136, s140, s137, s138 };
class s141;
class s143;
typedef s1::s9<s141> s142;
struct s1697{
bool s151;
std::wstring s1698;
std::wstring s1699;
bool s1702;
bool s1701;
bool s1703;
bool s1746;
bool s1734;
s1697( const std::wstring& dd=L".", const std::wstring& fs=L",", bool ab=false, bool rb=false,
bool sb=false )
: s151( true ), s1698(dd), s1699(fs), s1702(ab), s1701(rb),
s1703(sb), s1746( true ), s1734( false ) { }
};
extern s1697 s1759;
extern thread_local std::list<bool> s1771;
void s1700( const std::wstring& dd, const std::wstring& fs, bool ab, bool rb, bool sb );
void s1700( const s1697& cnf );
class s947
: public s1::s10{
std::wstring s194;
std::wstring s1116;
std::vector<std::wstring> s1117;
std::map<size_t, size_t> s1118;
size_t s1061;
public:
s1697 s1762;
s947( const std::wstring& file, bool s194 = true, const s1697& s1761=s1759 );
const std::wstring& Path() const { return s194;  }
void read( std::vector<s1::s9<s143>>& s153, 
const std::wstring& s190 = std::wstring(L"") );
void s170( const std::wstring& s77, size_t& pos, s1::s9<s143> s153 );
bool s1007( std::wstring& s, size_t s68, size_t s683, size_t& line ) const;
size_t s951() const { return s1061; }
};
typedef s1::s9<s947> s950;
class s143
: public s1::s10{
std::multimap<std::wstring, s142> s144;
s950 src;
public:
enum s145 { s146, s147, s148 };
enum s17 { s18, s149 };
const static s141 s150; // similar to string::npos
s143( const s947* pf ):src( (s947*)pf){}
void s154( const std::wstring& s77, const s1697& s1761 );
void s155( std::wostream* pd, bool s151=false ) const;
bool s156( const std::wstring& s152 ) const;
void s157( const std::wstring& s152, std::vector<s142>& s153 ) const;
const s142 s158( const std::wstring& s152 ) const;
void s159( const std::wstring& s76, s142 s349, s145 ap=s146 );
void s1633( const std::wstring& s76 );
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
std::pair<size_t, size_t> s1084;
s950 s1083;
public:
s141():s198(s132),obj(NULL){}
s141( const std::wstring& s ):s198(s134),obj(NULL),str(s){}
s141( const std::vector<s142>& a ): s198(s135),obj(NULL),s162(a){}
s141( const s947* pf, const std::wstring& s77, size_t& pos, const s1697& s1761 );
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
bool s1011( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s947* s1008() const { return s1083.s15<s947*>(); }
bool operator==( const s141& r ) const{
return s198 == r.s198 && obj == r.obj && str == r.str && s162 == r.s162 && b == r.b && s163 == r.s163;}
bool is( const s141& r ) const{
return this == &r;}
void s161( std::wostream* pd, int s197 ) const;
void s155( std::wostream* pd, bool s151=false ) const;
};
class s1711{
s1697 conf;
public:
s1711() { }
s1711( const s1697& _cnf )
: conf( _cnf ) {}
s131 s1552( const std::wstring& s77, size_t& pos, double& s153 );
void s178( const s947* pf, const std::wstring& s77, size_t& pos, 
std::vector<s1::s9<s141>>& s153,
bool s151 = false, const std::wstring& s72 = L",");
};
void s171( const std::wstring& s194, 
const std::vector<s1::s9<s143>>& s195 );
void s178( const s947* pf, const std::wstring& s77, size_t& pos,
std::vector<s1::s9<s141>>& s153, const s1697& s1761 );
void s178( const s947* pf, const std::wstring& s77,
std::vector<s1::s9<s141>>& s153, const s1697& s1761 );
} // namespace s6
#define TRANSD_VERSION L"0.429"
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s930 extern const uint32_t
#define s1692    1
#define s1693 2
#define s1694 3
#define s1695 4
#define s1696 5
namespace transd {
typedef uint32_t s1063;
typedef uint32_t traitnum_t;
typedef unsigned char tdbyte_t;
typedef std::basic_string<tdbyte_t> s1324;
namespace s7 {
s930 s1556;
s930 s1397;
s930 s1398;
s930 s1399;
s930 s1396;
s930 s1395;
s930 s1400;
s930 s1401;
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
DEFCONST s1631;
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
DEFCONST s942;
DEFCONST s1142;
DEFCONST s1358;
DEFCONST s1393;
DEFCONST s1394;
DEFCONST s1603;
DEFCONSTI s866;
DEFCONSTI s438;
DEFCONSTI s439;
DEFCONSTI s440;
DEFCONSTI s441;
DEFCONSTI s442;
DEFCONSTI s867;
DEFCONSTI s868;
DEFCONSTI s1749;
DEFCONSTI s1201;
DEFCONST s1415;
DEFCONST s1526;
DEFCONST s1413;
DEFCONST s1412;
DEFCONST s1414;
DEFCONST s1411;
DEFCONST s1416;
DEFCONST s1410;
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
DEFCONST s453;
DEFCONST s454;
DEFCONST s455;
DEFCONST s456;
DEFCONST s457;
DEFCONST s459;
DEFCONST s458;
DEFCONST s460;
DEFCONST s461;
DEFCONST s462;
DEFCONST s1376;
DEFCONST s1984;
DEFCONST s769;
DEFCONST s803;
DEFCONST s1574;
DEFCONST s829;
DEFCONST s1126;
DEFCONST s1375;
DEFCONST s463;
DEFCONST s464;
DEFCONST s465;
DEFCONST s466;
DEFCONST s467;
DEFCONST s468;
DEFCONST s469;
DEFCONST s739;
DEFCONST s470;
DEFCONST s938;
DEFCONST s1985;
DEFCONST s1991;
DEFCONST s1992;
DEFCONST s1993;
DEFCONST s1994;
DEFCONST s1990;
DEFCONST s1995;
DEFCONST s1996;
DEFCONST s1999;
DEFCONST s1998;
DEFCONST s1997;
DEFCONST s917;
DEFCONST s916;
DEFCONST s918;
#define s419 3
#define s1120 L','
DEFCONST s418;
DEFCONST s1108;
#define s1561 1
#define s1562	2
s930 s1367;
s930 s1302;
s930 s926;
s930 s925;
s930 s1301;
s930 s1131;
s930 s920;
s930 s1109;
s930 s921;
s930 s1110;
s930 s1111;
s930 s1112;
s930 s922;
s930 s923;
s930 s924;
s930 s1128;
s930 s1129;
s930 s1368;
s930 s1369;
s930 s1370;
s930 s1599;
s930 s1130;
s930 s1298;
s930 s1300;
s930 s1299;
s930 s1669;
s930 s1670;
s930 s1380;
s930 s1671;
s930 s1378;
s930 s1379;
s930 s1672;
s930 s1524;
s930 s1525;
s930 s1557;
s930 s1689;
s930 s1601;
s930 s1906;
s930 s1600;
s930 s1690;
s930 s1704;
s930 s1894;
s930 s1939;
s930 s1938;
extern std::set<std::wstring> s1125;
} // namespace s7
enum s224 { s225, s226, s227, s228 };
extern std::wstring s229[];
extern const std::wstring s230, s231, s232,				s821,
s233,  s234,     s235,    s236,      s237,
s238,  s239, s240, s241,s244,
s242, s243,			s258,	s245,			s257,
s246, s247,     s249,		s751,
s250,   s251, s252, s253,			s254,
s255, s256,		s259,	s902,			s261,
s260,	 s818,			s759, s852, 	s772,
s853,  s1319, s1622, s1318, s1430, 
s1946,	 s1888,    s1947, s1945,
s1564,  s1618,  s1617, s1616,
s1621, s1619, s1620, s1429;
class s262;
class s263;
class s270;
class s271;
class s272;
typedef s270* ( *s273 )( const std::wstring& s278, const std::vector<s271*>& s274 );
typedef s1::s9<s263> s949;
extern const std::wstring s265;
class s263
: public s1::s10{
public:
typedef std::multimap<std::wstring, s949> s275;
typedef std::map<std::wstring, std::wstring> s264;
private:
static std::map<std::wstring, s273> s276;
std::wstring s277;
std::wstring s278;
s224 s279;
std::wstring s280;
s275 s281;
std::wstring src;
s6::s142 s1055;
s264 s266;
s1063 s1352{};
void s282( const std::wstring& s77 );
void s283( const s6::s143& s133 );
void s284( const std::wstring& s77 );
void s285( const std::wstring& s77 );
void s286( const std::wstring& type, const s6::s141& obj );
void s1005( const std::wstring& s );
static std::wstring s287( const std::wstring& s77, size_t &pos );
public:
enum s17 { s18, s149 };
s263(){ }
s263( s224 at, const std::wstring& qpre, const std::wstring& s76 )
: s277( qpre ), s278( s76 ), s279( at ) { }
s263( const std::wstring& s76, const std::wstring& s349 )
: s278( s76 ), s279( s225 ), s280( s349 ) { }
s263( const std::wstring& type, const s6::s141* s1055 );
s263( const std::wstring& s76, const s6::s141& s296 );
s263( const s6::s143& s133 );
~s263();
s224 s297() const { return s279; }
void s1874( s224 t ) { s279 = t; }
std::wstring s298() const;
const std::wstring& s299() const { return s278; }
const std::wstring& Src() const { return src; }
const s6::s141* Nqj() const { return s1055.s15<s6::s141*>(); }
const std::wstring& s268( const std::wstring& s303 ) const;
void s269( const std::wstring& s303, const std::wstring& s267 );
s1063 s1311() const { return s1352; }
void s1346( s1063 t) { s1352 = t; }
void reset();
static void s288( const std::wstring& s77, size_t& pos, std::vector<std::wstring>& s153 );
void s289( s6::s143& s133 );
void s286( s263* node );
void s290( s262* s300, size_t s301 = 0 );
const std::wstring& s291() const { return s280; }
const s263* s292( const std::wstring& s278 ) const;
s275& s293() { return s281; }
const s275& s293() const { return s281; }
void s294( const std::wstring& s ) { s278 = s; }
void s1770( const std::wstring& s ) { s280 = s; }
static std::wstring s295( const s6::s143& obj,
const std::wstring& dfault = std::wstring( L"" ) );
static std::wstring s302( const s6::s143& obj,
const std::wstring& s303,
const std::wstring& dfault = std::wstring( L"" ) );
void s304( std::wostream* pd, int s197 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s946{ s1045, s1044, s1046, s1047, s1043 };
class Msg{
std::wstring func;
std::wstring file;
s946 type;
std::wstring s78;
public:	
Msg( const std::wstring& s, s946 t = s1043 )
: type( t ), s78( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s946 t = s1043 )
: func( f ), file( fi ), /*line( n ),*/ type( t ), s78( s ) {}
s946 s352() const { return type; }
const std::wstring& Text() const { return s78; }
};}
namespace transd {
class s1107{
std::vector<s8::Msg> s26;
size_t s999;
public:
s1107() : s999(0){}
void s973( const std::wstring& s78 );
void s973( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
void s975( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
size_t s936() const { return s999; }
};
extern s1107 s1016;
extern std::vector<std::wstring> s1087;
extern std::vector<std::wstring> s996;
class TDException
: public s2::s16{
public:
enum class Stage : uint32_t{
s1033 = 0,
s1026,
s1031,
s1030,
s1025,
s1027,
s1028,
s1029,
s1032
};
private:
Stage stage;
uint32_t category;
std::wstring s1089;
s949 s701;
public:
TDException( uint32_t cat, uint32_t id, const s263* s701 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s263* s701, const s16& e );
TDException( uint32_t cat, uint32_t id, const s263* s701, const std::wstring& s78 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s197 = 0 ) const override;
uint32_t Category() const { return category;  }
void s1078( Stage st ) { stage = st; }
TDException* s1002( const std::wstring& s = std::wstring( L"" ) );
static std::wstring s1914( const s263& s701 );
};
class s929
: public s2::s16{
public:
enum class s17 : uint32_t{
s985 = ((uint32_t)s16::s17::s25) + 1,
s1069,
s1052,
s976,
s986,
s1018,
s1021,
s25
};
s929( const std::wstring& s )
: s16( s, (uint32_t)s17::s985){}
s929( s16& e, const s263& s701, s17 code );
};
class s937
: public s2::s16{
public:
enum class s17 : uint32_t{
s1051 = ( (uint32_t)s16::s17::s25 ) + 1,
s1001,
s25
};
s937( s17 code );
s937( const std::wstring& s, s17 code )
: s16( s, (uint32_t)code ) {}
};
#define s934		1
#define s933		2
#define s935						3
#define s931					4
#define s932				5
#define s1134		6
#define s1133		7
#define s1381		8
#define s1558	9
#define s1673			10
#define s955(x) throw s956( L"unknown syntax: " + x );
#define s954(x) throw s956( L"syntax error: " + x );
namespace lang {
bool s656( const std::wstring& s, bool s714 = true );
} // namespace tdlang
extern const std::wstring s471;
enum s472 { s473, s474, s475, s1339, s476, s1247, s1248, 
s477, s478, s479, s480, s481, s1065 };
enum s2001 { s2049 = 0, s2050, s2048, s2047 };
enum s2000 { s2056 = 0, s2052, s2053, s2054, s2055 };
#define s1986 5
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
typedef const std::wstring s1907;
typedef std::map<std::wstring, std::vector<std::wstring>> s928;
extern s928 s995;
class s271
: public s1::s10{
friend class s491;
s949 s978;
protected:
s472 s492;
s1063 s493;
s262* s300;
int wh;
public:
s271( const s263* ast_=NULL ) : s978( (s263*)ast_ ), s492( s473 ), s493( 0 ), 
wh( s7::s868 )  { }
s271( s472 pt_, const s263* ast_=NULL ) : s978( (s263*)ast_ ), s492( pt_ ), s493( 0 ), 
wh( s7::s868 ) { }
s271( s262* pass_, s472 pt_, const s263* ast_=NULL ) : s978( (s263*)ast_ ), s492( pt_ ),
s493( 0 ), s300( pass_ ), wh( s7::s868 )  { }
s271( const s271& r ) : s978( r.s978 ), s492( r.s492 ), s493( r.s493 ),
s300( r.s300 ), wh( r.wh ) {}
virtual ~s271();
s472 s494() const { return s492; }
const s263* s603() const { return s978.s15<s263*>(); }
virtual s483* s496();
virtual s486 s497( s483** s274 = NULL, size_t s498 = 0 );
virtual s1063 s352() const { return s493; }
const s813& s1198() const;
virtual const std::wstring& s353() const;
virtual void s351( s1063 type );
s262* Pass() const  { return s300; }
int s618() const { return wh; }
void s1681( int i ) { wh = i; }
void s1264() { wh = 0; }
void s1262(bool b = true) { if(b) wh |= (1 << (s7::s1201-1)); 
else wh &= ~(1 << (s7::s1201-1));}
bool s1206() const { return wh >= 0; }
virtual bool s1205() const { return (wh > 0) && (wh & (1 << (s7::s1201-1))); }
virtual bool s501( const s483* s502 ) const;
virtual bool s1543( s1063 tp ) const;
virtual const s928& s1006() const { return s995;  }
virtual void s500( const s272* s879, bool b = true );
virtual void release() {}
virtual const s483* s503() const;
virtual s271* s335() const;
static void s1335( const s263& ast_, s262* s300, s272* obj,
const std::wstring& s334, std::vector<s271*>& s153 );
static s271* s504( const s263& s701, s262* s300, s272* obj,
const std::wstring& s334 );
static s271* s1020( s262* s300, s271* par, s272* obj, s591* s215,
const std::wstring& s334 );
static s485 s1019( const std::wstring& s77, const s263* ast_, s262* s300, 
s272* s588 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const;
virtual s1324 to_bytes() const;
virtual void to_null();
virtual void s304( std::wostream* pd, int s197 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s484*> s505;
s484* s1122( s505& m, const std::wstring& s152 );
void s670( const std::wstring& s, std::wstring& s1114, std::wstring& s601 );
class s483;
class s371;
class s483
: public s271{
protected:
s272* ns;
s483* s1705( s483** s274, size_t s498 );
s483* s1896( s483** s274, size_t s498 );
s483* s1940( s483** s274, size_t s498 );
virtual s483* s1898( s483** s274, size_t s498 );
public:
s483( s262* s300, s472 pc, const s263* ast_, s272* ns_ ) 
: s271( s300, pc, ast_ ), ns( ns_ ) { }
s483( const s483& r ) : s271( r ) { }
virtual ~s483();
virtual void s350() = 0;
virtual s1063 s386( const std::wstring& s343 ) const = 0;
virtual s483* s354( const s263& s701, s272* s588, s1907& s334 ) const = 0;
virtual s483* s355( s272* s588, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const = 0;
virtual s483* s355( s272* s588, const std::vector<s1063>& vt ) const;
virtual std::wstring s298() const;
virtual std::wstring s834() const;
virtual s483* s344( s1907& s278, s1907& s334,	bool s520 = true ) const {	return NULL;}
virtual s591* s1687( s1907& s278, s591* s215,	s561* cs ) const;
virtual void s356( s271* p ) const = 0;
virtual s483* s1538( const s483* p ) const;
virtual const s483* s503() const override = 0;
void s506( s1907& s ) { }//{ s372 = s; }
std::wstring s1675() { return L""; }// s372;}
virtual size_t s322() const = 0;
virtual bool operator==( const s483* p ) const = 0;
virtual bool operator<( const s483* p ) const = 0;
s483* s1897( s483** s274, size_t s498 );
s486 s497( s483** s274, size_t s498 ) override { return this; }
s483* s496() override;
virtual bool s556( s1907& s278, s371* s153, s1907& s334, bool fr ) const	{	return false;	};
virtual s271* s598( size_t off )	{	return NULL; }
virtual s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const;
virtual void s1937( Stream* ) const;
virtual void s1961( Stream* );
virtual void s1962( s1907& s );
};
enum s536 { s509, s510, s511 };
enum s512 { s513, s514, s515 };
typedef s1::s9<s813> s826;
typedef const s813* s927;
class s813
: public s1::s10{
public:
typedef s1063 s737;
typedef s737 s894;
typedef std::vector<s737> Cont;
private:
Cont vt;
size_t s1097;
public:
s813() {}
s813( s737 t1, s737 t2 = (s737)-1, s737 t3 = (s737)-1 );
s813( const s813& right );
s813( const Cont& v );
void s351( s737 t );
void s351( s927 pt );
void s785( s737 t );
void s785( s927 pt );
s894 s352( size_t n = 0 ) const;
const Cont& s819() const { return vt; }
void s819( std::vector<s271*>& s153 ) const;
bool operator==( const s813& p ) const;
size_t s322() const { return s1097; }
};
class s482;
class s262;
struct s967{
std::size_t operator()( const s813& k ) const{
return k.s322();}
};
struct s968{
std::size_t operator()( const s813& l, const s813& r ) const{
return l.operator==( r );}
};
class s491{
typedef std::map<std::wstring, s1063> s962;
typedef std::unordered_map<s813, s1063, s967, s968> s965;
typedef std::map<std::wstring, std::list<std::wstring>> s1792;
typedef std::map<std::wstring, std::set<std::wstring>> s915;
typedef std::map<s813::s894, s915> s928;
typedef std::map<std::wstring, traitnum_t> s1156;
typedef std::unordered_map<traitnum_t, std::wstring> s1250;
std::vector<s486> s1115;
std::vector<std::wstring> s1098;
std::vector<s813> s1103;
s962 s1099;
s965 s1104;
s1792 s1843;
s928 s919;
s1156 s893;
s1250 s1261;
traitnum_t s1207;
std::vector<traitnum_t>s1276;
std::vector<s1063>s1513;
std::vector<std::vector<s1063>> s1553;
s262* s300;
s1063 s1070( const s813::Cont& v, const std::wstring& s347 );
void s1173( const std::wstring& alias, const std::wstring& s347, 
const std::wstring& s1842 );
public:
s491( s262* pass_ );
void reset();
void s290();
void s517( const s482& st );
s1063 s218( s483* p, const std::wstring& s347 );
void s1668( const std::wstring& s347 );
void s1880( const std::wstring& s1114 );
s1063 s1048( const s813::Cont& v );
traitnum_t s1254( const std::wstring& trait, s1063& s1512 );
void s1164( s813::s894 type, const std::wstring& trait, s1063& s1512 );
bool s1200( s1063 s619, traitnum_t tra );
bool s1467( s1063 s619, s1063 alias );
traitnum_t s1157( s1063 s619 ) const { return s1276[s619]; }
traitnum_t s1460( s1063 alias ) const;
void s1535( s1063 s619, s1063 is );
bool s1536( s1063 s619, s1063 is );
s483* s518( const s6::s141& s349, s272* s588, const std::wstring& s519 );
s483* s518( const s263& s701, s272* s588, const std::wstring& s519 );
s483* s518( s1063 type, s272* s588, const std::wstring& s519 );
const s483* get( const std::wstring& s76, bool s520 = true ) const;
s1063 s1012( const std::wstring& s347, bool s520=true ) const;
s1063 s1013( const s813& vt, bool s520=true ) const;
const s813& s1015( s1063 t ) const;
const s483* s1009( s813::s894 t ) const;
const std::wstring& s804( s1063 n ) const;
bool s156( const std::wstring& s76 ) const;
void s790();
bool s1251();
double s1253();
int s1259();
void s304( std::wostream* pd, int s197 = 0 ) const;
static void s1010( const s813::Cont& v, size_t& idx, s813::Cont& s153 );
size_t s1058( const std::wstring& s, size_t& pos, s813::Cont& s153 );
std::wstring s1014( const s813::Cont& tp );
static std::wstring s1354( const std::wstring& tn );
std::wstring s1277( const std::wstring& tn );
};
class s521
: public s1::s10{
std::vector<std::wstring> s522;
s512 pv;
public:
s521() : pv( s513 ) { }
s521( s512 pv, const std::vector<std::wstring>& s523 );
s521( const std::wstring& ag, const std::wstring& s77 );
s512 s560( const std::wstring& s499 ) const;
static std::vector<std::wstring> s525;
};
class s526
: public s1::s10{
typedef std::map<std::wstring, s521*> s527;
s527 s528;
public:
s526( ) { }
void s529( s512 pv, s263* );
void s530( const std::wstring& s, s521& pl );
void s531( const std::wstring& s, const std::wstring& s524 );
s512 s532( const std::wstring& mem, const std::wstring& s499 );
void s533( const std::wstring& s334,
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
bool s538( const std::wstring& s76, s145 ap = s146 );
public:
s482( ): s537( s510 ), s539( NULL ) {}
s482( s536 am ) : s537( am ), s539( NULL ) {}
s482( const s482& s540 );
const s535& Table() const { return s553; }
void s500( s272* s499, bool s516 = true );
void s1651();
void reset();
void s541( const std::wstring& s76, s271* sym, s145 ap = s146 );
void s541( const std::wstring& s76, s6::s142 s349, s145 ap = s146 );
void s542( const std::wstring& s76 );
void s543( const s6::s143& obj, s145 ap = s146 );
void s289( const s482& t, s145 ap = s146 );
bool empty() const { return s553.empty(); }
bool s156( const std::wstring& s76 ) const;
s483* get( const std::wstring& s76, bool s520 = true ) const;
void s544( std::vector<std::wstring>& s153 ) const;
void s545( std::vector<std::wstring>& s153 ) const;
void s546( std::vector<std::wstring>& s153 ) const;
void s547( const s482& t, std::vector<std::wstring>& s153 ) const;
void copy( s482& t, s272* s588, s591* s587, s145 ap = s146 ) const;
void s548( s482& t ) const;
void s1615( s482& t ) const;
void s549( s512 pv, s263* s79 );
void s533( const std::wstring& s334,
std::vector<std::wstring>& s153 );
bool s550( const std::wstring& s278, const std::wstring& s334 ) const;
std::wstring to_wstring( uint32_t s1567 ) const;
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
void s554( const std::wstring& s );
void s500( s262* s300, const std::wstring& s558 );
void s1651( s262* s300 );
void s555( const std::wstring& s76, s262* s300, const std::wstring& s558 );
bool s556( const std::wstring& sym, s371* ref );
void copy( s551& t ) const;
};
extern s1::s9<s526> s557;
class s262;
class s336;
typedef void ( *s616 )( s483** s274, size_t n );
namespace s1514 {
extern s1063 s1273;
extern s1063 s1551;}
class s1124{
s336* s588;
std::vector<s1063> s1280;
std::vector<s485> s914;
public:
s1124() : s588( NULL ) {}
s1124( const std::vector<s485>& v, s336* s592 /*= NULL*/ );
s1124( const std::vector<s1063>& v, s336* s592 = NULL )
: s588( s592 ), s1280( v ) {}
bool operator==( const s1124& s524 ) const;
bool operator<( const s1124& s524 ) const;
const s336* Subj() const { return s588; }
const std::vector<s485>& s602() const { return s914; }
std::wstring s1331( s262* s300 ) const;
};
struct s2002{
s1063
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
s1530,
s748,
Vector;
s2002() {
Bool = Byte =	ByteArray =	ByteStream = Char =	DateTime = s414 = Double =	s361 =
FileStream = Filter =	HashIndex =	Index =	Int =	Lambda = Long =	No = Null = s272 =
Position = Range = Seq = String = s789 = Table = TSDBase = Tuple = s1530 =
s748 =	Vector = 0;}
const s483* operator()( s262* s300, s1063 tp );
};
extern s2002 Types;
struct s1144{
s1063 s338;
s616 s339;
bool s1170;
const std::vector<s2000>* s2037;
s1144()
: s338( 0 ), s339( NULL ), s1170( true ), s2037( NULL ) {}
s1144( s1063 pt, s616 fp, bool s1171 = true, 
const std::vector<s2000>* s2010 = NULL )
: s338( pt ), s339( fp ), 
s1170( s1171 ), s2037( s2010 ) {}
};
class s336
: public s483{
public:
class s337{
std::wstring s278;
s1063 s338;
s616 s339;
std::vector<s1124> s1165;
size_t s1040, s1037;
std::vector<std::wstring> s1211;
bool s1181;
bool s1170;
std::vector<s2000> s2046;
public:
enum class s1135 : uint32_t { s1182 = ((uint32_t)s2::s16::s17::s25) + 1 };
s337( const std::wstring& s676, s616 fp, s1063 s340,
const std::vector<s1124>& v=std::vector<s1124>(), 
size_t s1041 = 0, size_t s1038=(size_t)-1, bool s1171 = true,
const std::vector<std::wstring>& s1210 = std::vector<std::wstring>(),
const std::vector<s2000>& s2011 = { s2056 } )
: s278( s676 ), s338( s340 ), s339( fp ), s1165(v), 
s1040(s1041), s1037(s1038), s1211( s1210 ), s1181(false), 
s1170( s1171 ), s2046( s2011 ) {}
s337( const std::wstring& s676, s616 fp, s1063 s340,
const std::vector<s1124>& v, 
bool s1171, const std::vector<s2000>& s2011 )
: s278( s676 ), s338( s340 ), s339( fp ), s1165(v), 
s1040(0), s1037(0), s1181(false), 
s1170( s1171 ), s2046( s2011 ) {}
s337()
: s339( NULL ), s1181( false ), s1170( true ), s2046( { s2056 } ){}
s616 s1138() const { return s339; }
size_t s945() const { return s1040;  }
size_t s944() const { return s1037;  }
const std::vector<std::wstring>& Markers() const { return s1211; }
s1063 s495() const { return s338; }
void s1265( s1063 t) { s338 = t; }
void s1263( bool b ) { s1181 = b; }
bool s1188( ) const { return s1181; }
bool s1205() const { return s1170; }
const std::vector<s2000>* s2019() const { return &s2046; }
bool s1168( const s1124& s691 ) const;
};
protected:
typedef std::multimap<std::wstring, s337*> s341;
virtual const s341& s342() const = 0;
static size_t s758;
public:
s336( s262* s300, s272* ns_, const s263* ast_ ) : s483( s300, s474, ast_, ns_ ) {}
s336( const s336& r ) : s483( r ) {}
virtual ~s336() {}
s1063 s386( const std::wstring& s343 ) const override;
static void s784( s262* s300, bool soft = false );
static size_t s807() { return s758;  }
virtual const std::vector<std::wstring>& s1193( s1907& s343 ) const;
virtual s1144 s1199( s1907& s343 ) const;
virtual s1144 s1194( s1907& s343, s1124& ap ) const;
virtual s1144 s1189( s1907& s343, s1124& ap );
const s483* s503() const override;
virtual void* addr() = 0;
s486 s497( s483** s274, size_t s498 ) override;
static s483* s345( s262* s300, const std::wstring& s349, const std::wstring& s334 );
void s1537( s483* s42 );
};
class s358
: public s336{
static s341 s348;
double s349;
static void s1238( s483** s274, size_t n );
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
static void s1980( s483** s274, size_t n );
static void s1979( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
typedef double s1388;
s358( s262* s300 ) : s336( s300, NULL, NULL ) {}
s358( const s358& r );
s358( s262* s300, const std::vector<s271*>& l );
s358( s262* s300, double d );
s358( s262* s300, const std::wstring& s, size_t& pos );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void s500( const s272* s587, bool b = true ) override;	
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
double* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return s349 != 0.0; }
operator int() const override { return (int)s349; }
operator double() const override { return s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
void s1962( s1907& s ) override;
void s1961( Stream* ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s360
: public s336{
static s341 s348;
bool s349;
static void s387( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s360( s262* s300 ) : s336( s300, NULL, NULL ) {}
s360( s262* s300, bool b );
s360( s262* s300, const std::wstring& s, size_t& pos );
s360( const s360& right );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
bool* s357() { return &s349; }
void* addr() override { return (void*)&s349; }
s271* s335() const override;
void s356( s271* p ) const override;
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
operator bool() const override { return s349; }
operator int() const override { return (int)s349; }
operator double() const override { return (double)s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
void s1962( s1907& s ) override;
void s1961( Stream* ) override;
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
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
s1907& Msg() const { return s78; }
void s363( const std::wstring& s ) { s78 = s; }
void* addr() override { return (void*)0; }
void s500( const s272* s587, bool b = true ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override { return s78; }
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
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s335() const override;
void s356( s271* p ) const override { }
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override {	return L"";	}
operator double() const override { return (double)0; }
operator int() const override { return 0; }
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s364> s365;
class s384
: public s336{
traitnum_t s1274;
static s341 s348;
void s350() override {}
const s341& s342() const override { return s348; }
public:
s384( s262* s300, traitnum_t tn = 0, s472 pc = s473 );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
s271* s335() const override;
bool s501( const s483* s502 ) const override;
bool s1543( s1063 tp ) const override;
traitnum_t s1542() const { return s1274; }
void* addr() override { return (void*)0; }
void s356( s271* p ) const override { }
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s500( const s272* s587, bool b = true ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1708
: public s336{
public:
enum s1707 { s1743, s1742, s1741, s1744, s1825 };
typedef std::chrono::steady_clock s1796;
typedef std::chrono::system_clock s1797;
private:
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s387( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
static void s413( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1851( s483** s274, size_t n );
static void s1875( s483** s274, size_t n );
s1707 s1745;
std::tm s349;
s1797::time_point s1877;
static std::wregex s1767, s1769, s1768, s1865;
bool s1730( const std::wstring& s349, std::tm& t, s1707& s619 ) const;
public:
s1708( s262* s300 );
s1708( s262* s300, const std::wstring& s );
s1708( s262* s300, const std::tm& _t, s1707 s619 );
s1708( const s1708& right );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s335() const override;
void s356( s271* p ) const override;
void s500( const s272* s587, bool b = true ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1962( s1907& s ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1604 
: public s336{
s482 s628;
static s341 s348;
std::wstring s1647;
static void s1643( s483** s274, size_t n );
static void s1641( s483** s274, size_t n );
static void s1638( s483** s274, size_t n );
static void s1639( s483** s274, size_t n );
static void s1662( s483** s274, size_t n );
static void s1664( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1604( s262* s300 ) : s336( s300, NULL, NULL ) {}
s1604( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_=NULL );
s1604( const s1604& right, const s263* ast_ = NULL );
s1604( s262* s300, s272* s588, const s6::s143* s1646, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const override;
void* addr() override { return (void*)&s628; }
void s500( const s272* s879, bool b = true ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void load( const std::wstring& s77, bool s194 );
void s1644( const s6::s143* ob, s482::s145 ap = s482::s146 );
void s1634( s482::s535& st ) const;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1962( s1907& s ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s384> s872;
extern s1::s9<s384> s366;
extern s1::s9<s384> s367;
extern s1::s9<s384> s368;
extern s1::s9<s384> s873;
extern s1::s9<s384> s1688;
extern s1::s9<s384> s1523;
#define s1154 Types.Null
#define s1150 Types.Bool
#define s1310 Types.Byte
#define s1581 Types.Char
#define s1153 Types.Int
#define s1152 Types.Double
#define s1528 Types.Long
#define s1529 Types.s1530
#define s1155 Types.String
#define s1151 Types.ByteArray
#define s1721 Types.Vector
#define s1720 Types.s748
#define s1717 Types.Index
#define s1719 Types.Tuple
#define s1716 Types.HashIndex
#define s1582 Types.Position
#define s1715 Types.DateTime
#define s1718 Types.Lambda
#define s1800 Types.TSDBase
#define s1799 Types.Table
#define s1909 Types.s414
#define s1417 Types.Range
#define s1911 Types.Filter
#define s1418 Types.Seq
#define s1912 Types.s789
#define s1908 Types.ByteStream
#define s1910 Types.FileStream
#define s1149 ( std::numeric_limits<size_t>::max )( )
#define U64_MAX ( std::numeric_limits<uint64_t>::max )( )
typedef s358 TDDouble;
class s371
: public s271{
std::wstring s372;
s485 s373;
const s483* s374;
std::vector<size_t> s375;
size_t s376;
bool s1170;
public:
s371( s1907& s, s262* s300, s472 cat = s473, bool _cnst = false );
s371( const s371& right );
s483* s496() override;
const s483* s503() const override { return s374; }
const s485 s381() { return s373; }
bool s1205() const override { return s1170; }
void s1262() { s1170 = true; }
const std::wstring& s617() const { return s372; }
s486 s497( s483** s274, size_t s498 ) override;
s483* s377() const;
s483* s378();
size_t s1306() const { return s376; }
void s379( size_t off, const s483* proto );
void s1345( s371* ptr );
size_t s380() const { return s376; }
uint32_t Id() const { return (uint32_t)s376; }
s271* s335() const override;
void s500( const s272* s587, bool fr = true ) override;
void s382( s483* p ) { s373 = p; }
void s383( s483* p ) { s374 = p; }
void s984( const std::vector<std::wstring> &v );
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1602
: public s483{
s486 pobj;
protected:
virtual s483* s354( const s263& s701, s272* s588,
s1907& s334 ) const override {	return NULL; }
public:
s1602( s262* s300 )
: s483( s300, s1339, NULL, NULL ) {}
void s1663( s483* obj ) { pobj = obj; }
s271* s598( size_t off ) override 
{ return pobj->s598( off ); }
void s350() override {}
s1063 s386( const std::wstring& s343 ) const override { return 0; }
s483* s355( s272* s588, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const override { return NULL;	}
void s356( s271* p ) const override {}
s483* s1538( const s483* p ) const override { return NULL; }
const s483* s503() const override { return NULL; }
size_t s322() const override { return 0;  }
bool operator==( const s483* p ) const override { return false; }
bool operator<( const s483* p ) const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override {}
};
typedef s1::s9<s371> s489;
struct s1722{
std::wstring s1699;
std::wstring rowSep;
std::wstring s1736;
std::wstring s1737;
bool stringsQuoted;
bool promInts;
bool mixedTypes;
bool s1828;
bool s2016;
s1722()
: s1699( L"," ), rowSep( L"\n" ), s1737( L"." ), stringsQuoted( false ),
promInts( false ), mixedTypes( false ), s1828( false ), s2016( false )	{	}
s1722( const std::wstring& fs, const std::wstring& rs, const std::wstring& cn,
const std::wstring& dp, bool sq, bool pi, bool mt )
: s1699( fs ), rowSep( rs ), s1737( dp ), stringsQuoted( sq ),
promInts( pi ), mixedTypes( mt ), s1828( false ), s2016( false )	{	}
};
extern s1722 s1740;
extern s6::s1697 s1738;
template<class s1314, class Der>
class s1308 :
public s336{
protected:
typedef Der s1169;
s1314 s349;
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
static void s1968( s483** s274, size_t n );
static void s1967( s483** s274, size_t n );
static void s405( s483** s274, size_t n );
static void s406( s483** s274, size_t n );
static void s407( s483** s274, size_t n );
static void s408( s483** s274, size_t n );
static void s412( s483** s274, size_t n );
static void s1598( s483** s274, size_t n );
static void s1549( s483** s274, size_t n );
static void s1550( s483** s274, size_t n );
static void s1503( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
virtual void s350() override;
virtual const s336::s341& s342() const override;
public:
typedef s1308<s1314, Der> s1322;
s1308( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ ) {}
s1308( const s1322& r )
: s336( r ), s349( r.s349 ) {}
template<class s1532, class s1533>
static void s1534( s483* src, s483* s778 );
virtual s483* s1538( const s483* p ) const override;
virtual s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
virtual size_t s322() const override;
virtual bool operator==( const s483* p ) const override;
virtual bool operator<( const s483* p ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s346;
class s346
: public s1308<std::int32_t, s346>{
static s341 s348;
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef std::int32_t s1388;
s346( ) : s346( NULL ) {}
s346( s262* s300 );
s346( const s346& );
s346( s262* s300, const std::vector<s271*>& l );
s346( s262* s300, int i );
s346( s262* s300, const std::wstring& s, size_t& pos );
virtual s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
virtual s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
virtual bool s1543( s1063 tp ) const override;
virtual void s500( const s272* s587, bool ) override;
virtual s271* s335() const override;
virtual void s356( s271* p ) const override;
s1388* s357() { return &s349; }
virtual void* addr() override { return (void*)&s349; }
virtual operator bool() const override { return s349 != 0; }
virtual operator int() const override { return s349; }
virtual operator double() const override { return (double)s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
virtual void to_null( ) override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1305
: public s1308<std::int64_t, s1305>{
protected:
static s341 s348;
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef std::int64_t s1388;
s1305() : s1305( NULL ) {}
s1305( s262* s300 );
s1305( const s1305& );
s1305( s262* s300, const std::vector<s271*>& l );
s1305( s262* s300, int64_t i );
s1305( s262* s300, const std::wstring& s, size_t& pos );
virtual s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
virtual s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
virtual void s500( const s272* s587, bool ) override;
virtual s271* s335() const override;
virtual void s356( s271* p ) const override;
int64_t* s357() { return &s349; }
virtual void* addr() override { return (void*)&s349; }
virtual operator bool() const override { return s349 != 0; }
virtual operator int() const override { return (int)s349; }
virtual operator double() const override { return (double)s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
};
class s1531
: public s1308<std::uint64_t, s1531>{
protected:
static s341 s348;
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef std::uint64_t s1388;
s1531() : s1531( NULL ) {}
s1531( s262* s300 );
s1531( const s1531& );
s1531( s262* s300, const std::vector<s271*>& l );
s1531( s262* s300, int64_t i );
s1531( s262* s300, const std::wstring& s, size_t& pos );
virtual s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
virtual s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
virtual void s500( const s272* s587, bool ) override;
virtual s271* s335() const override;
virtual void s356( s271* p ) const override;
s1388* s357() { return &s349; }
virtual void* addr() override { return (void*)&s349; }
virtual operator bool() const override { return s349 != 0; }
virtual operator int() const override { return (int)s349; }
virtual operator double() const override { return (double)s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
};
template <>
inline void s1308<s1531::s1388, s1531>::s404( s483** s274, size_t s498 ){
( (s1531*)s274[0] )->s349 = ( (s1531*)s274[1] )->s349;}
template <>
inline void s1308<s1531::s1388, s1531>::s389( s483** s274, size_t s498 ){
if( s498 == 2 )
( (s1531*)s274[0] )->s349 = ( (s1531*)s274[1] )->s349;
else {
s274[2]->s356( s274[0] );
( (s1531*)s274[0] )->s349 =
( (s1531*)s274[1] )->s349 - ( (s1531*)s274[0] )->s349;}}
class s1297
: public s1308<tdbyte_t, s1297>{
protected:
static s341 s348;
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef tdbyte_t s1388;
s1297() : s1297( NULL ) {}
s1297( s262* s300 );
s1297( const s1297& );
s1297( s262* s300, const std::vector<s271*>& l );
s1297( s262* s300, tdbyte_t i );
s1297( s262* s300, const std::wstring& s, size_t& pos );
virtual s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
virtual s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
virtual void s500( const s272* s587, bool ) override;
virtual s271* s335() const override;
virtual void s356( s271* p ) const override;
tdbyte_t* s357() { return &s349; }
virtual void* addr() override { return (void*)&s349; }
virtual operator bool() const override { return s349 != 0; }
virtual operator int() const override { return s349; }
virtual operator double() const override { return (double)s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override { return std::to_wstring( s349 ); }
void s1937( Stream* ) const override;
};
class s1575
: public s1308<wchar_t, s1575>{
protected:
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef wchar_t s1388;
s1575() : s1575( NULL ) {}
s1575( s262* s300 );
s1575( const s1575& );
s1575( s262* s300, const std::vector<s271*>& l );
s1575( s262* s300, wchar_t i );
s1575( s262* s300, const std::wstring& s, size_t& pos );
virtual s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
virtual s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
virtual void s500( const s272* s587, bool ) override;
virtual s271* s335() const override;
virtual void s356( s271* p ) const override;
wchar_t* s357() { return &s349; }
virtual void* addr() override { return (void*)&s349; }
virtual operator bool() const override { return s349 != 0; }
virtual operator int() const override { return s349; }
virtual operator double() const override { return (double)s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override { return std::wstring( 1, s349 ); }
void s1937( Stream* ) const override;
};
typedef s346 TDInt;
class s591;
class s272;
typedef std::vector<std::pair<std::wstring, std::wstring>> s622;
typedef std::map<std::wstring, s272*> s623;
typedef std::map<std::wstring, s263*> s624;
class s272
: public s483{
protected:
const s272* s625;
const s272* s626;
s371 s1665;
const std::wstring& s347;
std::wstring s278;
std::wstring s627;
s482 s628;
s551* s629;
std::vector<s485> s630;
std::vector<s371> s631;
void s350() override { }
s483* s1706( s483** s274, size_t s498 );
public:
s272( const s272& s632, std::vector<s485>& s274, const s263* ast_=NULL );
s272( s262* s300, s1063 s340, s472 pc/* = s473*/, const s263* ast_ = NULL );
s272( s1907& s278, s262* s300, s472 pc, const s263* ast_ = NULL );
s272( s1907& s347, const std::wstring& s278, s262* s300, s482& s633,
const s482& s628, const s263* ast_ = NULL );
s272( s263& s701, s262* s300, s472 pc, s272* ns, s536 am,
s623& cl, s622& cnl, s624& al );
virtual ~s272();
s1907& s353() const override { return s347; }
virtual s1907& s299() const { return s278; }
std::wstring s298() const override;
std::wstring s834() const override { return ns->s298(); }
static s271* s634( const s6::s143& obj, s1907& s278, s262* s300 );
static s271* s634( std::multimap<std::wstring, s484*>& v, s484* s587 );
s483* s635( const s263& s701, s483* s588, s1907& s334 ) const;
using s483::s355;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1063 s386( s1907& s343 ) const override;
bool s501( const s483* s502 ) const override;
const s928& s1006() const override { return s995; }
bool s730( s1907& f ) const;
void s851( s1907& s76, s483* s349, s482::s145 ap = s482::s146 );
void s1659( s1907& s76, s483* s349 );
void s1642( const s1604* ob );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
const s483* s503() const override { return s625; }
const s272* s636() const { return s626; }
s1907& s637() const { return s627; }
s483* s344( s1907& s278, s1907& s334,
bool s520 = true ) const override;
s591* s1687( s1907& s278, s591* s215,	s561* cs ) const override;
void s645( s263& s701 );
void s555( s1907& s76, s1907& s558 );
void s638( s263& s701 );
void s972( s263& s701 );
void s639( s1907& s334,	std::vector<std::wstring>& s153 );
bool s556( s1907& s278, s371* s153, s1907& s334, bool fr ) const override;
size_t s640( const std::wstring& s278 ) const;
s271* s598( size_t off ) override;
s483* s641( s1907& s278, s1907& s334,
bool s520=true ) const;
bool s642( s1907& sym, s1907& s499 ) const;
bool s532( s1907& sym );
void s500( const s272* s879, bool b ) override;
void s644( const s482& s274 ); 
void s154( s263& s701 );
void s1651();
s271* s335() const  override;
void s356( s271* p ) const override;
void s643( s272* s646 ) const;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s561
: public s271{
const std::wstring s601;
std::vector<s271*> s274;
s949 past;
public:
s561( s262* pass_, const s263* ast_ )
: s271( pass_, s477 ), past( (s263*)ast_ ){}
s561( s262* pass_, s1907& s1555, const std::vector<s271*>& l, const s263* s701 );
s561( const s561& s540 );
s1907& s299() const { return s601; }
std::vector<s271*>& s602() { return s274; }
const s263* s603() { return past; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
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
class s591
: public s272{
public:
enum s563 { s564, s565, s566, s567, s568, s569 };
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
std::vector<s486> s983;
std::vector<s483*> s583;
s579 s584;
std::vector<std::vector<s484*>> s585;
s486 s586;
s487 s588;
s488 s587;
const s263* past;
s1602 s1656;
s485 subject;
const bool intro;
void s847( s271* par, size_t pos, s485& s153, const s272* s1674 );
void s589( s1907& s334);
void s590( s1907& s334);
s483* s1613( s483** s705, size_t s498 );
virtual void s1913( const s577& pl ) const;
public:
s591( s262* s300, s272* s592, s591* s593, s563 ct,
s1907& s676, const s263* s701, bool s1729=false )
: s272( s676, s300, s476, s701 ), s575( ct ),  
s586( NULL ),	s588( s592 ), s587( s593 ), past( s701 ), s1656(s300),
intro(s1729){}
s591( s262* s300, s272* s588, s591* s587, s563 ct,
const std::vector<s271*>& l, const s263* s701, bool s1729 );
s591( const s591& right, s272* s588, s591* s587, 
const std::vector<s271*>& s274, const s263* s701 );
virtual ~s591();
s563 s864() const { return s575; }
void s594( s570 vt ) { s576 = vt; }
s570 s595() const { return s576; }
const std::wstring& s353() const override { return s271::s353(); }
std::wstring s834() const override;
const s263* s603() const { return past; }
s483* s496() override { return s586; }
void s500( const s272* s1674, bool proc ) override;
void s596( const std::vector<s485>& l );
typedef std::vector<std::pair<std::wstring, s486>> s835;
void s814( s835& s153 ) const;
void s597( const s272* s1674 );
bool s556( const std::wstring& s278, s371* ref,
const std::wstring& s334, bool ) const override;
s271* s598( size_t off ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335() const override;
static s591* s599( const s263& s701, s262* s300, s272* obj,
s1907& s278, s1907& s558 );
static s561* s1121( const s263& s701, s262* s300, s272* obj,
s1907& s558 );
static s591* s600( s561* cs, s262* s300, s272* s588, s591* s215,
s1907& s558, bool proc );
static void s1244( std::vector<s271*>& s274, const std::vector<std::wstring>& s1210 );
static void s1244( std::vector<s485>& s274, const std::vector<std::wstring>& s1210 );
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s841
: public s591{
s616 s562;
bool s1978;
public:
s841( s262* s300, s591* s587, s563 ct, const std::vector<s271*>& l, /*s616 s562,*/
s1063 s493, const std::wstring& s1555, const s263* s701 );
virtual ~s841();
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
bool s556( const std::wstring& s278, s371* ref,
const std::wstring& s334, bool ) const override;
s271* s335() const override;
bool s1205() const override { return s1978; }
};
class s842
: public s591{
public:
s842( s262* s300, s272* s588, s591* s587, s563 ct,
const std::vector<s271*>& l, const s263* s701 );
s842( const s842& right, /*s483* s588,*/ s591* s587, const std::vector<s271*>& s274,
s563 ct, const s263* s701, s272* s588 = NULL );
virtual ~s842();
void s1680( s272* s592 ) { s588 = s592; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335() const override;
};
class s1359
: public s842{
public:
s1359( s262* s300, s272* s588, s591* s587, const s263* s701 );
s1359( const s1359& right, s272* s588, s591* s587, const std::vector<s271*>& s274,
const s263* s701 );
virtual ~s1359();
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274 = NULL, size_t s498 = 0 ) override;
s271* s335() const override;
};
namespace s1514 {
extern s1063 s1507;
extern s1063 s1511;
extern s1063 s1506;}
typedef std::basic_istream<wchar_t> s1499;
typedef std::basic_ostream<wchar_t> s1502;
typedef std::basic_istringstream<wchar_t> s1973;
typedef std::basic_ostringstream<wchar_t> s1974;
class Stream
: public s336{
public:
typedef std::ios_base::fmtflags s1926;
typedef std::streamsize s1927;
Stream( s262* s300, s272* ns, const s263* s208 = NULL )
: s336( s300, ns, s208 ) {}
virtual void s1463( std::wstring& s153, size_t s1474 );
virtual void s1482( const std::wstring& src );
virtual void s1464( std::wstring& s153, const std::wstring& s72 = L"\n" );
virtual void s1483( const std::wstring& src );
virtual void s1462( s1324& s153, size_t s1474 );
virtual void s1481( const s1324& src );
virtual void s1461( s1324& s153, const s1324& s72 = s1324( {'\n'} ) );
virtual void s1480( const s1324& src );
virtual void rewind();
virtual void s1931()=0;
virtual void s1929()=0;
virtual void s1959()=0;
virtual void s1960()=0;
virtual void s1570( int n )=0;
virtual void s1930( int n )=0;
virtual void s1915( wchar_t c );
virtual void s1917()=0;
virtual void s1918()=0;
virtual void s1916()=0;
virtual void s1928()=0;
virtual void s1568()=0;
virtual void s1569()=0;
virtual s1926 s1932() const = 0;
virtual s1927 s1933() const = 0;
virtual void s1953()=0;
virtual void s1955()=0;
virtual void s1958( int n )=0;
virtual void s1956( int n )=0;
virtual void s1954()=0;
virtual void s1957()=0;
virtual s1926 s1963() const = 0;
virtual s1927 s1964() const = 0;
virtual void ws() { throw new s2::s16( L"ws not implemented" ); }
virtual s1499& s1965() { throw new s2::s16( L"iwstream not implemented" ); }
virtual s1502& s1966() { throw new s2::s16( L"owstream not implemented" ); }
};
template<class s1422, class s1424>
class s1408
: public Stream{
protected:
typedef s1408<s1422, s1424> s1169;
typedef s336::s341 s341;
s1422 *s1476;
s1424 *s1477;
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s1489( s483** s274, size_t n );
public:
s1408( s262* s300, s272* ns, const s263* s208 = NULL )
: Stream( s300, ns, s208 ) {}
s1408(){}
virtual ~s1408() {}
void s1931() override;
void s1929() override;
void s1959() override;
void s1960() override;
void s1570( int n ) override;
void s1930( int n ) override;
void s1917() override;
void s1918() override;
void s1916() override;
void s1928() override;
void s1568() override;
void s1569() override;
s1926 s1932() const override;
s1927 s1933() const override;
void s1953() override;
void s1955() override;
void s1958( int n ) override;
void s1956( int n ) override;
void s1954() override;
void s1957() override;
s1926 s1963() const override;
s1927 s1964() const override;
};
template<class s1422, class s1424>
s336::s341 s1408<s1422, s1424>::s348;
template<class s1422, class s1424>
void s1408<s1422, s1424>::s350(){
s348.insert( std::make_pair( L"rewind", new s337( L"rewind", &s1408<s1422,s1424>::s1489, s1154,
{ s1124() }, 0, 0 ) ) );}
template<class s1422, class s1424>
void s1408<s1422, s1424>::s1489( s483** s274, size_t s498 ){
s1169* s1064 = (s1169*)s274[1];
if( s1064->s1476 ) {
if( s1064->s1476->eof() )
s1064->s1476->clear( s1064->s1476->rdstate() &
( s1064->s1476->rdstate() ^ std::ios_base::eofbit ) );
if( !s1064->s1476->good() )
throw new s2::s16( L"file handle is not valid" );
s1064->s1476->seekg( 0 );
s1064->s1476->clear();}
if( s1064->s1477 )
s1064->s1477->seekp( 0 );}
class s507
: public s1408<s1973,s1974>{
protected:
typedef s507 s1169;
static s341 s348;
std::basic_stringstream<wchar_t> ss;
static void s508( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
s507( const s507&, const s263* ast_ = NULL );
s507( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s507(){}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&ss; }
s1499& s1965() override { return *s1476; }
s1502& s1966() override { return *s1477; }
void s1463( std::wstring& s153, size_t s1474 ) override;
void s1482( s1907& src ) override;
void s1464( std::wstring& s153, s1907& s72 = L"\n") override;
void s1483( s1907& src ) override;
void s1462( s1324& s153, size_t s1474 ) override;
void s1481( const s1324& src ) override;
void s1461( s1324& s153, const s1324& s72 = s1324( { '\0' } ) ) override;
void s1480( const s1324& src ) override;
void s1915( wchar_t c ) override;
virtual void ws() override { *s1476 >> std::ws; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_istringstream<tdbyte_t> s1497;
typedef std::basic_ostringstream<tdbyte_t> s1500;
class s1296
: public s1408<s1497,s1500>{
protected:
typedef s1296 s1169;
static s341 s348;
std::basic_stringstream<tdbyte_t> bs;
static void s1317( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
s1296( const s1296&, const s263* ast_ = NULL );
s1296( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s1296(){}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&bs; }
void s1463( std::wstring& s153, size_t s1474 ) override;
void s1482( s1907& src ) override;
void s1464( std::wstring& s153, s1907& s72 = L"\n" ) override;
void s1483( s1907& src ) override;
void s1462( s1324& s153, size_t s1474 ) override;
void s1481( const s1324& src ) override;
void s1461( s1324& s153, const s1324& s72 = s1324( { '\0' } ) ) override;
void s1480( const s1324& src ) override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_ifstream<tdbyte_t> s1498;
typedef std::basic_ofstream<tdbyte_t> s1501;
class s1304
: public s1408<s1498,s1501>{
protected:
typedef s1304 s1169;
static s341 s348;
s485 s210;
s485 mode;
std::wstring s1343;
typedef std::basic_fstream<tdbyte_t> s1496;
std::fstream fs;
static void s1238( s483** s274, size_t n );
static void s2030( s483** s274, size_t n );
static void s2032( s483** s274, size_t n );
static void s2031( s483** s274, size_t n );
static void s1326( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s2038( s483** s274, size_t n );
static void s1486( s483** s274, size_t n );
static void s1357( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
static void s2008( s483** s274, size_t s498, std::wstring& s1347 );
void _open( const std::wstring& s1347 );
void _close();
public:
s1304( const s1304&, const s263* ast_ = NULL );
s1304( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
s1304( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL );
~s1304(){}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
void release() override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return (void*)&fs; }
void s1463( std::wstring& s153, size_t s1474 ) override;
void s1482( s1907& src ) override;
void s1464( std::wstring& s153, s1907& s72 = L"\n" ) override;
void s1483( s1907& src ) override;
void s1462( s1324& s153, size_t s1474 ) override;
void s1481( const s1324& src ) override;
void s1461( s1324& s153, const s1324& s72 = s1324( { '\0' } ) ) override;
void s1480( const s1324& src ) override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1404
: public s1408<std::wistream, std::wostream>{
static s341 s348;
static void s508( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1404( const s507&, const s263* ast_ = NULL );
s1404( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1404(){}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return NULL/*(void*)&std::wcin*/; }
void s1463( std::wstring& s153, size_t s1474 ) override;
void s1482( s1907& src ) override;
void s1464( std::wstring& s153, s1907& s72 ) override;
void s1483( s1907& src ) override;
void s1462( s1324& s153, size_t s1474 ) override;
void s1481( const s1324& src ) override;
void s1461( s1324& s153, const s1324& s72 ) override;
void s1480( const s1324& src ) override;
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1406
: public s1408<std::wistream, std::wostream>{
static s341 s348;
static void s508( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1238( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s1406( const s507&, const s263* ast_ = NULL );
s1406( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1406(){}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void* addr() override { return NULL; }
s1502& s1966() override { return *s1477; }
void s1463( std::wstring& s153, size_t s1474 ) override;
void s1482( s1907& src ) override;
void s1464( std::wstring& s153, s1907& s72 ) override;
void s1483( s1907& src ) override;
void s1462( s1324& s153, size_t s1474 ) override;
void s1481( const s1324& src ) override;
void s1461( s1324& s153, const s1324& s72 ) override;
void s1480( const s1324& src ) override;
void s1915( wchar_t c ) override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s1404> s1405;
extern s1::s9<s1406> s1407;
class s262;
class s385;
class Iterator{
public:
virtual ~Iterator() {}
virtual s271* s315() = 0;
virtual s271* s964() = 0;
virtual const s271* s964() const = 0;
virtual s271* Idx() = 0;
virtual s271* El() = 0;
virtual s1063 ValType() const = 0;
virtual bool s1981() const = 0;
virtual bool operator==( const Iterator* r ) const { return this == r; }
virtual bool operator<( const Iterator* r ) const { return this < r; }
};
typedef std::pair<s1::s1291<Iterator>, s1::s1291<Iterator>> s1146;
struct s840;
class s385;
class s326
: public s336{
protected:
s1063 s317;
s1063 s1202;
s1063 s325;
virtual s483* s1192( Iterator* it );
public:
s326( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ ), s317( 0 ), s1202( 0 ), s325( 0 ) {}
s326( const s326& r )
: s336( r ), s317( r.s317 ), s1202( r.s1202 ), s325( r.s325 ) {}
virtual ~s326() {}
virtual size_t s1140() const { return 0; }
virtual Iterator* s314( s385* r ) = 0;
virtual s1063 s319() const { return s317; }
virtual s1063 s939() const { return s1202; }
virtual s1063 ValType() const { return s325; }
virtual Iterator* s1187() = 0;
virtual Iterator* s1191() = 0;
virtual s1146 s1196() = 0;
virtual Iterator* s1166( const s483* idx );
virtual Iterator* s1185( const s483* s349 );
virtual Iterator* s1240( const s483* s349 );
virtual s483* sort( bool reverse, s840* cmp );
};
class s385
: public s326,
public Iterator{
s485 s588;
s1::s9<s326> s987;
s1::s1291<Iterator> s1468;
s485 s1245, s1246;
s486 s1544, s1545;
bool s980, s981;
Iterator* s318;
uint64_t s990, s1548;
int incr;
s1::s9<s1531> s1177;
static s341 s348;
std::wstring s499;
static void s1238( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
enum s1143 { s1229, s1236, s1228, s1235, s1237, s1224, s1230 };
s385( s262* s300 );
s385( s262* s300, s326* s588, Iterator* it );
s385( uint64_t b, uint64_t e = U64_MAX );
s385( s262* s300, s1907& s77, const s263* ast_ = NULL );
s385( const s385& right, const s263* ast_ = NULL );
s385( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1144 s1199( s1907& s343 ) const override;
s1144 s1194( s1907& s343, s1124& ap ) const override;
s1144 s1189( s1907& s343,	s1124& ap ) override;
s1063 s1190( s1907& s1555,	const std::vector<s485>& l ) const override;
const std::vector<std::wstring>& s1193( s1907& s343 ) const override;
size_t s1140() const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)s318; }
s1063 ValType() const override { return s325; }
void s500( const s272* s879, bool fr=true ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
Iterator* s1187() override { return NULL; }
Iterator* s1191() override { return NULL; }
s1146 s1196() override;
s1146 s1196( s326* s588 );
bool s1981() const override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
s326* s819() { return s987; }
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1136
: public s326,
public Iterator{
s485 s588;
s486 s987;
s1::s9<s385> range;
s485 where, s1072;
s1::s1291<Iterator> s318, s1491;
s371 s989; // @it - for using in s1204 scope lambdas
s271* s990;
static s341 s348;
s1::s9<s346> s349, s685;
std::wstring s499;
s1063 s1355;
static void s1238( s483** s274, size_t n );
static void s1350( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1143 { s1229, s1236, s1228, s1235, s1237, s1334, s1230 };
s1136( s262* s300 ) : s326( s300, NULL, NULL ), s989( s7::s1376, s300 ), s990(NULL) {}
s1136( s262* s300, s1907& s77, const s263* ast_ = NULL );
s1136( const s1136& r, const s263* ast_ = NULL );
s1136( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s1063 s319() const override { return s685->s352(); }
size_t s1140() const override { return s987.s15<s326*>()->s1140(); }
s1144 s1194( s1907& s343,	s1124& ap ) const override;
s1144 s1189( s1907& s343, s1124& ap ) override;
s1063 s1190( s1907& s1555,	const std::vector<s485>& l ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1063 ValType() const override { return s325; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
bool s556( s1907& s278, s371* s153, s1907& s334,	bool ) const override;
s271* s598( size_t off ) override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
bool s1981() const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
Iterator* s1187() override { return NULL; }
Iterator* s1191() override { return NULL; }
s1146 s1196() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s953
: public s326,
public Iterator{
s488 s1060;
s488 set;
s488 eq;
s485 start;
s485 end;
s485 incr;
s485 s991;
s485 s1661;
bool s1049;
std::wstring s499;
static s341 s348;
static void s1238( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1143 { s1229, s1236, s1228, s1235, s1237, s1224, s1230 };
s953( s262* s300 );
s953( s262* s300, s1907& s77, const s263* ast_ = NULL );
s953( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
virtual ~s953();
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1063 ValType() const override { return s325; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override {}
size_t s322() const override { return 0; }
bool operator==( const s483* p ) const override { return false; }
bool operator<( const s483* p ) const override { return false; }
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
bool s1981() const override;
Iterator* s314( s385* r ) override;
s271* s315() override;
s271* s964() override { return NULL; }
const s271* s964() const override { return NULL; }
s271* Idx() override;
s271* El() override { return NULL; }
Iterator* s1187() override { return NULL; }
Iterator* s1191() override { return NULL; }
void* addr() override { return NULL; }
s1146 s1196() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef int HPROG;
enum s1372{ s1431=1, s1432, s1433, s1434, s1624, 
s1435, s1436, s1437, s1438, s1441, 
s1439, s1440, s1625, s1442, s1949, s1626, 
s1443, s1444, s1628, s1629, s1445,
s1889, s1627,	s1950, s1948, s1446,
s1565, s1447, s1448, s1449, s1630,
s1450,	s1451, s1452 };
extern std::map<std::wstring, int> s1373;
extern std::vector<int> BIFuncs1v;
extern std::vector<std::wstring> s1374;
struct s722{
std::vector<std::wstring> s663;
std::wstring entry;
s2001 restrictions[s1986];
s722() {
memset( &restrictions, 0, s1986 * sizeof(s2001) );}
};
class s1989{
s2001 s2043[s1986];
static std::vector<std::wstring> s2051;
s2001 s2005( const std::wstring& s2041 );
public:
s1989();
void s2058( const s6::s143& s133 );
void reset();
void s2015( const std::vector<s2000>* s2036, s2001 sw ) const;
bool s2014( s2000 si, s2001 sw ) const;
};
class s561;
class s262
: public s272{
private:
std::vector<std::wstring> s199;
s263 s701;
std::wstring s200;
std::wstring s767;
std::wstring s1900;
s1989 s2042;
void s202( const std::wstring& s657, s722& s153 );
void s213( const std::wstring& s194, const s6::s143& obj );
s491 s203;
s482 s204;
typedef std::map<std::wstring, s483*> s205;
s205 s206;
typedef std::map<uint32_t, std::set<std::wstring>> s943;
bool s1321;
public:
s262();
~s262();
const std::wstring& s716() const { return s767; }
void s1892( const std::wstring& s ) { s767 = s; }
const std::wstring& s1895() const { return s1900; }
void s1893( const std::wstring& s ) { s1900 = s; }
virtual std::wstring s834() const override { return L"::"; }
virtual std::wstring s298() const override { return L"::"; }
void s1902( bool soft = false );
void reset();
void s207( s263& s208 );
void s209( const std::wstring& s210, bool s1904 = false );
void s211( s6::s143& obj );
void s212( const std::wstring& s210 );
s483* run( const std::vector<std::wstring>& s691 );
s483* callFunc( const std::wstring& s601, std::vector<std::wstring>& l );
s488 getProc( const std::wstring& s601 );
bool s1332() const { return s1321; }
void s1652( const std::wstring& s671 );
void s2015( const std::vector<s2000>* s2036, s2001 sw ) const;
bool s2014( s2000 si, s2001 sw ) const;
s491& TR() { return s203; }
s591* s214( int s1459, std::vector<s271*>& s274,
s272* s588, s591* s215,	const s263* s701 );
void s217( const std::wstring& s );
s1063 s218( s483* p, const std::wstring& s347 );
void s219( const std::wstring& s349, const std::wstring& s334,
std::vector<std::wstring>& s153 );
virtual bool s556( const std::wstring& s278, s371* s153,
const std::wstring& s334, bool ) const override;
s486 s220( const std::wstring& s349, const std::wstring& s334 );
bool s221( s371& rf ) const;
s271* s222( const std::wstring& sym, const std::wstring& s499,
bool s520 = true );
void* s223( const std::wstring& s278 );
void s1353( const std::wstring& s671 );
void s1667( const std::wstring& s1635 );
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s1::s9<s262> s721;
namespace s1514 {
extern s1063 s1509;
extern s1063 s1508;
extern s1063 s1510;}
class Iterator;
struct s840;
class s1145;
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
struct s1427{
bool operator()( const s486 l, const s486 r ) const{
return l->operator<( ( s483* )&( *r ) );}
bool operator()( const s483* l, const s483* r ) const{
return l->operator<( r );}
bool operator()( const s483& l, const s483& r ) const{
return l.operator<( &r );}
};
void s1163( s262* s300, const std::wstring& s77, 
std::wstring& s1275, std::wstring& s644 );
template<class s1313>
struct s1303 {
bool operator()( const s1313& l, const s1313& r ) { return l < r; }
};
template<class s1313>
struct s1576 {
bool operator()( const s1313& l, const s1313& r ) { return l == r; }
};
template<class s1313, class s1583>
struct s1577{
s488 s859;
std::vector<s485>s861;
s1577() : s859( 0 ),
s861( { new s1583( 0,0 ), new s1583( 0,0 ) } ) {}
bool operator()( const s1313& l, const s1313& r ){
*s861[0].template s15<s1583*>()->s357() = l;
*s861[1].template s15<s1583*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
template<>
struct s1303<s485>{
std::vector<s485>s861;
s488 s859;
s1303() : s859( 0 ) { s861.resize( 2 ); }
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
struct s1303<s486>{
std::vector<s485>s861;
s488 s859;
s1303() : s859( 0 ) { s861.resize( 2 ); }
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
struct s1303<tdbyte_t>{
s488 s859;
std::vector<s485>s861;
s1303() : s859( 0 ),
s861( { new s1297( 0,0 ), new s1297( 0,0 ) } ) {}
bool operator()( const tdbyte_t& l, const tdbyte_t& r ){
if( s859.s14() ) {
*s861[0].s15<s1297*>()->s357() = l;
*s861[1].s15<s1297*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l < r; }
};
template<>
struct s1303<wchar_t>{
s488 s859;
std::vector<s485>s861;
s1303() : s859( 0 ),
s861( { new s1575( 0,0 ), new s1575( 0,0 ) } ) {}
bool operator()( const wchar_t& l, const wchar_t& r ){
if( s859.s14() ) {
*s861[0].s15<s1575*>()->s357() = l;
*s861[1].s15<s1575*>()->s357() = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l < r; }
};
template<>
struct s1576<s485> {
bool operator()( const s485& l, const s485& r ) { 
return l.s15<s483*>()->operator==( r.s15<s483*>() );}
};
template<>
struct s1576<s486> {
bool operator()( const s486& l, const s486& r ) { 
return l->operator==( r.s15<s483*>() );}
};
template<>
struct s1577<s485, s485>{
std::vector<s485>s861;
s488 s859;
s1577() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s485& l, const s485& r ){
s861[0] = l;
s861[1] = r;
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
template<>
struct s1577<s486, s486>{
std::vector<s485>s861;
s488 s859;
s1577() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s486& l, const s486& r ){
s861[0] = l.s15<s271*>();
s861[1] = r.s15<s271*>();
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
};
typedef std::wstring s1579;
template<class _Cont, class s1313, class Der>
class s313 :
public s326{
protected:
typedef Der s1169;
_Cont s349;
static s1303<s1313> s1327;
static s1576<s1313> s1586;
typedef s336::s341 s341;
static s341 s348;
static void s328( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s1256( s483** s274, size_t n );
static void s1269( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1337( s1313 el ) { return el; }
static std::pair<typename _Cont::iterator, typename _Cont::iterator> s1426( s483* p, Der* pv );
static s1146 s1428( s483* p, Der** pv );
static s1145* s1977( Der** pv, typename _Cont::iterator& s1983 );
public:
typedef s313<_Cont, s1313, Der> s1172;
s313( s262* s300, s272* ns, const s263* ast_ );
s313( const s1172& r );
virtual ~s313(){}
virtual s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
virtual s1146 s1196() override;
};
template<class _Cont, class s1313, class Der>
s336::s341 s313<_Cont, s1313, Der>::s348;
template<class _Cont, class s1313, class Der>
s1303<s1313> s313<_Cont, s1313, Der>::s1327;
template<class _Cont, class s1313, class Der>
s1576<s1313> s313<_Cont, s1313, Der>::s1586;
template<class _Cont, class s1313, class Der, class s1584>
class s1403 :
public s313<_Cont, s1313, Der>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
static s1577<s1313, s1584> s1587;
static void s1585( s483** s274, size_t n );
static void s1588( s483** s274, size_t n );
static void s1637( s483** s274, size_t n );
static void s1623( s483** s274, size_t n );
static void s1213( s483** s274, size_t n );
static void s1212( s483** s274, size_t n );
static void s1256( s483** s274, size_t n );
static void s1269( s483** s274, size_t n );
static void s1595( s483** s274, size_t n );
static void s1589( s483** s274, size_t n );
static void s1495( s483** s274, size_t n );
static void s1747( s483** s274, size_t n );
static void s1952( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1337( s1313 el ) { return el; }
public:
typedef s1403<_Cont, s1313, Der, s1584> s1172;
s1403( s262* s300, s272* ns, const s263* ast_ );
s1403( const s1172& r );
virtual ~s1403(){}
virtual s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
};
template<class _Cont, class s1313, class Der, class s1584>
s336::s341 s1403<_Cont, s1313, Der, s1584>::s348;
template<class _Cont, class s1313, class Der, class s1584>
s1577<s1313, s1584> s1403<_Cont, s1313, Der, s1584>::s1587;
template<class _Cont, class s1313, class Der>
class s1578 :
public s1403<_Cont, s1313, Der, s1313>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
static void s1637( s483** s274, size_t n );
static void s1623( s483** s274, size_t n );
static void s1269( s483** s274, size_t n );
static void s1466( s483** s274, size_t n );
static void s1975( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef s1578<_Cont, s1313, Der> s1172;
s1578( s262* s300, s272* ns, const s263* ast_ );
s1578( const s1172& r );
virtual ~s1578(){}
virtual s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
};
template<class _Cont, class s1313, class Der>
s336::s341 s1578<_Cont, s1313, Der>::s348;
template<class s1313>
struct s1382 {
bool operator()( const s1313& l, const s1313& r ) { return l < r; }
};
template<>
struct s1382<std::pair<s486, s486>>{
typedef std::pair<s486, s486> s1421;
std::vector<s485>s861;
s488 s859;
s1382() : s859( 0 ) { s861.resize( 2 ); }
bool operator()( const s1421& l, const s1421& r ){
if( s859.s14() ) {
s861[0] = l.first.s15<s271*>();
s861[1] = r.first.s15<s271*>();
s859->s596( s861 );
return (bool)*s859->s497( 0, 0 );}
else
return l.first->operator<( r.first.s15<s483*>() );}
};
template<class _Cont, class s1423, class s1425, class Der>
class s1371 :
public s313<_Cont, s1423, Der>{
protected:
typedef s336::s341 s341;
typedef s336::s337 s337;
s1382<std::pair<s1423, s1425>> s1457;
static void s1213( s483** s274, size_t n );
static void s1487( s483** s274, size_t n );
static s341 s348;
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
s271* s1337( std::pair<s1423, s1425>& el );
public:
typedef s1371<_Cont, s1423, s1425, Der> s1172;
s1371( s262* s300, s272* ns, const s263* ast_ );
s1371( const s1172& r );
virtual s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
virtual bool insert( s483* s152, s483* s349 );
virtual s483* find( s483* s152 );
};
template<class _Cont, class s1423, class s1425, class Der>
s336::s341 s1371<_Cont, s1423, s1425, Der>::s348;
template <class _Cont, class s1313, class Der>
s313<_Cont, s1313, Der>::s313( s262* s300, s272* ns_, const s263* ast_ )
: s326( s300, ns_, ast_ ){}
template <class _Cont, class s1313, class Der, class s1584>
s1403<_Cont, s1313, Der, s1584>::s1403( s262* s300, s272* ns_, const s263* ast_ )
: s313<_Cont, s1313, Der>( s300, ns_, ast_ ){}
template <class _Cont, class s1313, class Der>
s1578<_Cont, s1313, Der>::s1578( s262* s300, s272* ns_, const s263* ast_ )
: s1403<_Cont, s1313, Der, s1313>( s300, ns_, ast_ ){}
template <class _Cont, class s1423, class s1425, class Der>
s1371<_Cont, s1423, s1425, Der>::s1371( s262* s300, s272* ns_, const s263* ast_ )
: s313<_Cont, s1423, Der>( s300, ns_, ast_ ){}
#define DR ((s484*)*(s274 + 1))
#define PARN(n)((s484*)*(s274 + n))
template<class _Cont, class s1313, class Der>
s1146
s313<_Cont, s1313, Der>::s1428( s483* p, Der** pv ){
s385* pr = NULL;
if( p->s352() == s1417 ) {
pr = (s385*)p;
*pv = (Der*)pr->s819();}
else
*pv = ( (Der*)p );
s1146 rp;
if( pr ) {
rp = pr->s1196( *pv );}
else
rp = (*pv)->s1196();
return rp;}
template<class _Cont, class s1313, class Der>
std::pair<typename _Cont::iterator, typename _Cont::iterator> 
s313<_Cont, s1313, Der>::s1426( s483* p, Der* pv ){
using s1132 = Der;
using s941 = typename Der::s1141;
s385* pr = NULL;
if( p->s352() == s1417 ) {
pr = (s385*)p;
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)p );
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
return std::make_pair( s1521, s1522 );}
template<class _Cont, class s1313, class Der>
void s313<_Cont, s1313, Der>::s328( s483** s274, size_t n ){
using s1132 = Der;//s1169;
s1132* pv = ( (s1132*)s274[1] );
*( (s346*)*s274 )->s357() = (int)pv->s349.size();}
template<class _Cont, class s1313, class Der>
void s313<_Cont, s1313, Der>::s330( s483** s274, size_t n ){
using s1132 = Der;//s1169;
s1132* pv = ( (s1132*)s274[1] );
pv->s349.clear();}
template<class _Cont, class s1313, class Der>
s1146 s313<_Cont, s1313, Der>::s1196(){
return std::make_pair( s1187(), s1191() );}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1256( s483** s274, size_t s498 ){
using s1132 = Der;
using s941 = typename Der::s1141;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
if( ((s326*)pv)->s1140() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
std::reverse( s1521, s1522 );
*s274 = pv;}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1595( s483** s274, size_t s498 ){
using s1132 = Der;
using s941 = typename Der::s1141;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
if( ((s326*)pv)->s1140() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
std::mt19937 s1658(std::random_device{}());
std::shuffle( s1521, s1522, s1658 );}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1952( s483** s274, size_t s498 ){
using s941 = typename Der::s1141;
Der *pv = NULL, *pv1 = NULL;
s1146 rp = s313<_Cont, s1313, Der>::s1428( s274[1], &pv );
s1146 rp1 = s313<_Cont, s1313, Der>::s1428( s274[2], &pv1 );
s1576<s1313> s1972;
typename _Cont::iterator s1521, s1522, vbeg1, vend1;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
vbeg1 = rp1.first.s15<s941*>()->s1147();
vend1 = rp1.second.s15<s941*>()->s1147();
auto s1951 = std::mismatch( s1521, s1522, vbeg1, vend1, s1972 );
if( s1951.first == s1522 )
s274[0] = new s346( pv->s300, (int)std::distance( s1521, s1522 ) );
else {
s941 it( pv->s300, pv, s1951.first, s1951.first + 1 );
s274[0] = pv->s1192( &it );}}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1213( s483** s274, size_t s498 ){
using s941 = typename Der::s1141;
Der* pv = ( (Der*)s274[1] );
s1146 rp = s313<_Cont, s1313, Der>::s1428( s274[1], &pv );
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
s591* s1208 = NULL;
if( s498 == 3 )
s1208 = (s591*)s274[2];
s1303<s1313> s1971;
s1971.s859 = s1208;
typename _Cont::iterator s1214 = std::max_element( s1521, s1522, 
/*pv->s1327*/ s1971);
*s274 = (s483*)pv->s1977( &pv, s1214 );}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1212( s483** s274, size_t s498 ){
using s941 = typename Der::s1141;
Der* pv = NULL;
s1146 rp = s313<_Cont, s1313, Der>::s1428( s274[1], &pv );
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
if( s1521 == s1522 )
s274[0] = new s346( pv->s300, -1 );
else {
auto s1214 = std::max_element( s1521, s1522, pv->s1327 );
s941 it( pv->s300, pv, s1214, s1214 + 1 );
s274[0] = pv->s1192( &it );}}
template<class _Cont, class s1423, class s1425, class Der>
void s1371<_Cont, s1423, s1425, Der>::s1213( s483** s274, size_t s498 ){
using s1132 = Der;
using s941 = typename Der::s1141;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
typename _Cont::iterator s1214 = std::max_element( s1521, s1522, pv->s1457 );
auto tmp = std::make_pair( s1214->first, s1214->second );
*s274 = (s483*)pv->s1337( tmp );}
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
class s1580;
class s359
: public s1403<s1579, wchar_t, s359, s1575>{
typedef s1579 s1388;
typedef s359 s1169;
static s341 s348;
std::vector<s485> s274;
static void s1238( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1594( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s1691( s483** s274, size_t n );
static void s388( s483** s274, size_t n );
static void s794( s483** s274, size_t n );
static void s1597( s483** s274, size_t n );
static void s1590( s483** s274, size_t n );
static void s891( s483** s274, size_t n );
static void s892( s483** s274, size_t n );
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
static void s1485( s483** s274, size_t n );
static void s1036( s483** s274, size_t n );
static void s1349( s483** s274, size_t n );
static void s412( s483** s274, size_t n );
static void s1492( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
public:
typedef s1580 s1141;
s359( const s359&, const s263* ast_ = NULL );
s359( s262* s300, s272* s588, const std::vector<s271*>& l, const s263* ast_ = NULL );
s359( s262* s300, const std::wstring& s = std::wstring( L"" ), s272* s588=NULL, const s263* ast_ = NULL );
s359( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
virtual ~s359();
s483* s354( const s263& s701, s272* s588, 
const std::wstring& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
size_t s1140() const override { return 2; }
s1063 s1190( const std::wstring& s1555, 
const std::vector<s485>& l ) const override;
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s1575 operator[]( size_t n ) { return s1575( s300, s349[n] ); }
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
Iterator* s1166( const s483* idx ) override;
Iterator* s1185( const s483* s349 ) override;
s483* s1192( Iterator* it ) override;
s271* s1337( wchar_t el ) { return new s1575( s300, el ); }
s1388* s357() { return &s349; }
s1388& s320() { return s349; }
const s1388& s320() const { return s349; }
void* addr() override { return (void*)&s349; }
operator bool() const override { return !s349.empty(); }
operator int() const override;
operator double() const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
void s1962( s1907& s ) override;
void s1961( Stream* ) override;
s1324 to_bytes() const override;
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
enum s1143{ s1228, s1235, s1227, s1231, s1221, s1217 };
s817( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s817( s262* s300 );
s1907& s299() const override { return s759; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s359;
class s316;
class s750;
class s961;
class s1294;
class s324;
class s1384;
typedef std::vector<s485> s1420;
typedef std::vector<s485> s1419;
typedef s1324 s1377;
typedef std::map<s486, s486, s1427> s1389;
typedef std::unordered_map<s486, s486, s321, s323> s1383;
class s1127
: public Iterator{
protected:
bool s885;
public:
s1127() : s885( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s885;  }
};
class s1139
: public s1127{
public:
};
class s966 
: public s1139{
typedef s1420::iterator s941;
typedef s1420::reverse_iterator s1249;
s1::s9<s316> v;
s941 s1216;
s941 s1088;
s1249 s1260;
s1249 s1490;
uint64_t s1215;
s1::s9<s1531> s1175;
s1::s9<s961> s1174;
public:
s966( s966* it );
s966( s262* s300, s316* v_, s941 it, s941 sent );
s966( s262* s300, s316* v_, s1249 it, s1249 sent );
virtual ~s966() {}
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s941 s1147() { return s1216; }
s1249 s1148() { return s1260; }
s1063 ValType() const override;
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s963
: public Iterator{
typedef s1419::iterator s941;
s1::s9<s750> v;
s941 s1216;
s941 s1088;
uint64_t s1215;
s1::s9<s1531> s1175;
public:
s963( s963* it );
s963( s262* s300, s750* v_, s941 it, s941 sent );
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
s941 s1147() { return s1216; }
s1063 ValType() const override;
};
class s940
: public s1127{
typedef s1389::iterator s941;
typedef s1389::reverse_iterator s1249;
s1::s9<s324> v;
s941 s1216;
s941 s1088;
s1249 s1260;
s1249 s1490;
s485 s1175;
s1::s9<s961> s1174;
public:
s940( s940* it );
s940( s262* s300, s324* v_, s941 it, s941 sent );
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
s941 s1147() { return s1216; }
void reverse() override;
s1063 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1385
: public Iterator{
typedef s1383::iterator s941;
s1::s9<s1384> v;
s941 s1216;
s941 s1088;
s485 s1175;
s1::s9<s961> s1174;
public:
s1385( s1385* it );
s1385( s262* s300, s1384* v_, s941 it, s941 sent );
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
s941 s1147() { return s1216; }
s1063 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1580
: public s1139{
typedef s1579::iterator s941;
typedef s1579::reverse_iterator s1249;
s1::s9<s359> v;
s941 s1216;
s941 s1088;
s1249 s1260;
s1249 s1490;
uint64_t s1215;
s1::s9<s1531> s1175;
s1::s9<s961> s1174;
public:
s1580( s1580* it );
s1580( s262* s300, s359* v_, s941 it, s941 sent );
s1580( s262* s300, s359* v_, s1249 it, s1249 sent );
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s941 s1147() { return s1216; }
s1249 s1148() { return s1260; }
s1063 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1295
: public s1139{
typedef s1377::iterator s941;
typedef s1377::reverse_iterator s1249;
s1::s9<s1294> v;
s941 s1216;
s941 s1088;
s1249 s1260;
s1249 s1490;
uint64_t s1215;
s1::s9<s1531> s1175;
s1::s9<s961> s1174;
public:
s1295( s1295* it );
s1295( s262* s300, s1294* v_, s941 it, s941 sent );
s1295( s262* s300, s1294* v_, s1249 it, s1249 sent );
bool s1981() const override;
s271* s315() override;
s271* s964() override;
const s271* s964() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s941 s1147() { return s1216; }
s1249 s1148() { return s1260; }
s1063 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1145
: public s336{
s485 s588;
s1::s1291<Iterator> s349;
s1063 s325;
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
static void s398( s483** s274, size_t n );
static void s1982( s483** s274, size_t n );
static void s1591( s483** s274, size_t n );
static void s1748( s483** s274, size_t n );
static void s403( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
public:
s1145( s262* s300 ) : s336( s300, NULL, NULL ), s325(0) {}
s1145( s262* s300, s1907& s77, const s263* ast_ = NULL );
s1145( const s1145& right, const s263* ast_ = NULL );
s1145( s262* s300, s272* context, Iterator* it, const s263* ast_ = NULL );
virtual ~s1145() {}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
void s500( const s272* s879, bool ) override;
s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const override;
s1063 ValType() const { return s325;  }
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
void operator=( const s1145& p );
bool operator==( const s483* p )  const override;
bool operator<( const s483* p )  const override;
void* addr() override { return (void*)&s349; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s966;
class s1295;
class s316
: public s1578<s1420, s485, s316>{
protected:
typedef s1420 s1388;
typedef s316 s1169;
static s341 s348;
std::wstring s499;
static void s1238( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1266( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1316( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s1891( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1747( s483** s274, size_t n );
void s971( s1907& s824, const s1722& tbfr, s272* s588, const s263* ast_	 );
void s350() override;
const s341& s342() const override { return s348; }
void s1162( s1907& s77, s272* s588, const s6::s1697& s1761 );
void s1315( const std::vector<s271*>& v, s272* s588 );
void s1160( s1907& s1275, s1063& pt, s1063& vt ) const;
public:
enum s1143 { s1757, s1755, s1753, s1751, s1752, s1754,
s1844 };
typedef s966 s1141;
s316( s262* s300 ) : s1578( s300, NULL, NULL ) {}
s316( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1697& s1761 = s1738 );
s316( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL, s1063 s709 = 0, s1063 s1278 = 0 );
s316( const s316& right, const s263* ast_ = NULL );
s316( s262* s300, s1063 s325, s272* s588, const s263* ast_ = NULL );
virtual ~s316() override;
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s1063 s1197( s1907& s1275, s813::Cont& s588 ) const;
size_t s1140() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const override;
void load( s1907& s77, s272* s588, const s6::s1697& s1761 );
void s500( const s272* s879, bool fr=true ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s485 operator[]( size_t n ) { return s349[n]; }
const s485& operator[]( size_t n ) const { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
Iterator* s1166( const s483* idx ) override;
Iterator* s1185( const s483* s349 ) override;
s483* s1192( Iterator* it ) override;
void clear() { s349.clear(); }
void add( s484* el ) { s349.push_back( el ); }
void erase( size_t n ) { s349.erase( begin( s349 ) + n ); }
size_t size() const { return s349.size(); }
s483* sort( bool reverse, s840* cmp ) override;
std::vector<s485>& s320() { return s349; }
const std::vector<s485>& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s1937( Stream* ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s750
: public s326{
protected:
typedef s1419 s1388;
static s341 s348;
s1388 s349;
s1388::iterator s318;
std::wstring s499;
static void s387( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1316( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s1004( s483** s274, size_t n );
static void s1077( s483** s274, size_t n );
static void s1747( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
void s1162( s1907& s77, std::wstring& s1275, std::wstring& s644,
std::vector<s1::s9<s6::s141>>& s94, const s263* ast_, 
const s6::s1697& s1761 );
public:
s750( s262* s300 )
: s326( s300, NULL, NULL ) {}
s750( s262* s300, const s263* ast_ )
: s326( s300, NULL, ast_ ) {}
s750( s262* s300, s272* s588, const std::wstring& s77,
const s263* ast_ = NULL, const s1722& tbfr=s1740 );
s750( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s750( const s750& right );
virtual ~s750() override;
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s1063 s319() const override;
s1063 s939() const override { return Types.Int; }
s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const override;
size_t s1140() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
s485 operator[]( size_t n ) { return s349[n]; }
const s485& operator[]( size_t n ) const { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
s1146 s1196() override;
void clear() { s349.clear(); }
void add( s485 el ) { s349.push_back( el ); }
void assign( const std::vector<s485>& v );
size_t size() const { return s349.size(); }
std::vector<s485>& s320() { return s349; }
const std::vector<s485>& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s961
: public s750{
static s341 s348;
void s350() override;
const s341& s342() const override { return s348; }
void s1162( s1907& s77, s272* s588, const s6::s1697& s1761 );
virtual void s1160( s1907& s1275 );
static void s387( s483** s274, size_t n );
static void s1267( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1316( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s330( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s1004( s483** s274, size_t n );
static void s1077( s483** s274, size_t n );
public:
s961( s262* s300 ) : s750( s300 ) {}
s961( s262* s300, s272* s588, s1907& s77, const s263* ast_ = NULL,
const s6::s1697& s1761 = s1738 );
s961( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s961( const s961& right, const s263* ast_ = NULL );
virtual ~s961() override {}
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
void s500( const s272* s879, bool fr=true ) override;
s1063 s1197( s1907& s1275, s813::Cont& s588 );
void load( s1907& s77, s272* s588, const s6::s1697& s1761 );
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s271* s335() const override;
void s356( s271* p ) const override;
s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
};
class s1294
: public s1403<s1377, tdbyte_t, s1294, s1297>{
protected:
typedef s1377 s1388;
typedef s1294 s1169;
static s341 s348;
std::wstring s499;
static void s1238( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1266( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1316( s483** s274, size_t n );
static void s329( s483** s274, size_t n );
static void s398( s483** s274, size_t n );
static void s1340( s483** s274, size_t n );
static void s1356( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
void s1162( s1907& s77,
s483* s588, const s6::s1697& s1761 );
public:
typedef s1295 s1141;
s1294( s262* s300 ) : s1403( s300, NULL, NULL ) {}
s1294( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1697& s1761=s1738 );
s1294( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s1294( const s1294& right, const s263* ast_ = NULL );
virtual ~s1294() override;
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
size_t s1140() const override { return 2; }
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
void load( s1907& s77, s483* s588, const s6::s1697& s1761 );
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
tdbyte_t operator[]( size_t n ) { return s349[n]; }
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
Iterator* s1166( const s483* idx ) override;
Iterator* s1185( const s483* s349 ) override;
s271* s1337( tdbyte_t el ) { return new s1297( s300, el ); }
s483* s1192( Iterator* it ) override;
void clear() { s349.clear(); }
void add( tdbyte_t el ) { s349.push_back( el ); }
void erase( size_t n ) { s349.erase( begin( s349 ) + n ); }
size_t size() const { return s349.size(); }
s1388& s320() { return s349; }
const s1388& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s316 TDVector;
class s324;
class s324
: public s1371<s1389, s486, s486, s324>{
protected:
typedef s1389 s1388;
typedef s324 s1169;
static s341 s348;
s1388::iterator s318;
std::wstring s499;
static void s1238( s483** s274, size_t n );
static void s1632( s483** s274, size_t n );
static void s332( s483** s274, size_t n );
static void s780( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1465( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s1594( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
virtual void s350() override;
virtual const s341& s342() const override { return s348; }
virtual void s1162( const std::wstring& s77, std::wstring& s1275, std::wstring& s644,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
void s1160( const std::wstring& s1275, s1063& pt, s1063& et,
s1063& kt, s1063& vt ) const;
void s1315( const std::vector<s271*>& v, s483* s588 );
public:
typedef s940 s1141;
s324( s262* s300 ) : s1371( s300, NULL, NULL ) {}
s324( s262* s300, s1063 s1202, s1063 s325, s272* s588, const s263* ast_ = NULL );
s324( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL );
s324( const s324& right, const s263* ast_ = NULL );
s324( s262* s300, const std::vector<s271*>& l, s272* s588,
const s263* ast_ = NULL, s1063 s709 = 0, s1063 s1183 = 0,
s1063 s1640 = 0, s1063 s1278 = 0);
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s1063 s1197( const std::wstring& s1275, s813::Cont& s588,
s1063& et,	s1063& kt, s1063& vt ) const;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
size_t s1140() const override { return 1; }
void s500( const s272* s879, bool fr=true ) override;
void load( const std::wstring& s77, s272* s588, const std::wstring& s72 );
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
s1388& s320() { return s349; }
const s1388& s320() const { return s349; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1384;
class s1384
: public s1371<s1383, s486, s486, s1384>{
protected:
typedef s1383 s1388;
typedef s1384 s1169;
static s341 s348;
s1388::iterator s318;
std::wstring s499;
static void s332( s483** s274, size_t n );
static void s780( s483** s274, size_t n );
static void s327( s483** s274, size_t n );
static void s1465( s483** s274, size_t n );
static void s387( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
virtual void s1162( const std::wstring& s77, std::wstring& s1275, std::wstring& s644,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
public:
typedef s1385 s1141;
s1384( s262* s300 ) : s1371( s300, NULL, NULL ) {}
s1384( s262* s300, s1063 s1202, s1063 s325, const s263* ast_ = NULL );
s1384( s262* s300, s272* s588, const std::wstring& s77, const s263* ast_ = NULL );
s1384( const s1384& right, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s1063 s1197( const std::wstring& s1275, s813::Cont& s588 );
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s349; }
s1063 s1190( const std::wstring& s1555, const std::vector<s485>& l ) const override;
size_t s1140() const override { return 0; }
void s500( const s272* s879, bool fr=true ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
Iterator* s314( s385* r ) override;
Iterator* s1187() override;
Iterator* s1191() override;
s1388& s320() { return s349; }
const s1388& s320() const { return s349; }
virtual std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s324 TDIndex;
class s604
: public s591{
std::vector<s1063> types;
std::vector<s488> s649;
public:
s604( s262* s300, s272* s588, s591* s587, s563 ct,
const std::vector<s271*>& l, const s263* s701 );
void s648( s1063 type, s591* pOvr );
virtual s486 s497( s483** s274, size_t s498 ) override;
};
class s838
: public s591{
std::vector<s1063> s1905;
s483* s1898( s483** s274, size_t s498 ) override;
public:
s838( s262* s300 );
s838( s262* s300, s272* s592, s591* s593, 
const std::vector<s271*>& l, const s263* s701 );
s838( s262* s300, s272* s592, const std::vector<s1063>& l, 
s1063 pt, const s263* s701 );
s838( s838& s1903, const std::vector<s485>& l, const s263* s701 );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s486 s497( s483** s274, size_t s498 ) override;
void s500( const s272* s1674, bool proc ) override;
s483* s496() override { return this; }
s1063 s1330() const { return s1905.back(); }
s271* s335() const override;
using s483::s355;
using s483::s1897;
s483* s355( s272* s588, const std::vector<s1063>& vt ) const override;
s591* s1687( s1907& s278, s591* s215,	s561* cs ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s839
: public s591{
public:
s839( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s898
: public s591{
int code;
public:
s898( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s606
: public s591{
public:
s606( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s607
: public s591{
public:
s607( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s607( s262* s300 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1409
: public s591{
s371 s1504;
s486 varval;
s485 s308;
s371 s311;
s1531 s312;
s485 lambda;
public:
s1409( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1409( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1941
: public s591{
public:
s1941( s262* s300, s272* s588, s591* s587, std::vector<s271*>& l, 
const s263* s701 );
s1941( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s608
: public s591{
s579 s620;
std::vector<s579> s621;
public:
enum s1143{ s1225, s1226 };
s608( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s608( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
void s736( bool proc );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s611
: public s591{
s361 s78;
public:
s611( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s611( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s613
: public s591{
public:
s613( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s613( s262* s300 );
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s612
: public s591{
s371 s76;
s361 s619;
s1::s9<s613> ctch;
public:
s612( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s612( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s755
: public s591{
std::vector<std::wstring> fields;
public:
s755( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1682
: public s591{
public:
typedef s483* (s272::*s1684)(s483**, size_t);
private:
s1684 s1686;
s485 subject;
public:
s1682( s262* s300, s272* s588, s591* s587, s1684 _ptr,
s561* cs, const s263* s701 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1683
: public s591{
public:
typedef s483* (s483::*s1685)(s483**, size_t);
private:
s1685 s1686;
s485 subject;
public:
s1683( s262* s300, s272* s588, s591* s587, s1685 _ptr,
const std::vector<s271*>& s274, s1907& s676, s1063 s1074, const s263* s701 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1611
: public s591{
s486 cmd;
std::thread s823;
public:
s1611( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1611( const s1611& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1609
: public s591{
public:
s1609( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1609( const s1609& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1606
: public s591{
public:
s1606( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1606( const s1606& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1610
: public s591{
public:
s1610( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1610( const s1610& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1605
: public s591{
public:
s1605( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1605( const s1605& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1887
: public s591{
public:
s1887( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1887( const s1887& );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s609
: public s591{
s485 s42;
bool lout;
public:
enum s1143{ s1235, s1471, s1592, s1969, s1970, s1573, s1935, s1919, 
s1921, s1922, s1920, s1934, s1571, s1572 };
s609( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s609( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s1942
: public s591{
s485 source;
bool lin;
public:
enum s1143{ s1228, s1969, s1970, s1573, s1935, s1934 };
s1942( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1942( s262* s300 );
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
template<class _Cont, class s1313, class Der>
s1145* s313<_Cont, s1313, Der>::s1977( Der** pv, typename _Cont::iterator& s1983 ){
typename _Cont::iterator s1593 = s1983;
if( s1983 != (*pv)->s349.end() )
++s1593;
s1145* s685 = new s1145( (*pv)->s300, (*pv)->ns,
new typename Der::s1141( (*pv)->s300, *pv, s1983, s1593 ), NULL );
s685->s500( (*pv)->ns, true );
return s685;}
template <class _Cont, class s1313, class Der>
void s313<_Cont, s1313, Der>::s350(){
s300->TR().s1164( s493, s7::s1413, s1514::s1509 );
s348.insert( std::make_pair( L"size", new s337( L"size", &s313<_Cont, s1313, Der>::s328, s1153,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"clear", new s337( L"clear", &s313<_Cont, s1313, Der>::s330, s1154,
{ s1124() }, 0, 0, false ) ) );}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s350(){
s313<_Cont, s1313, Der>::s350();
s348 = s313<_Cont, s1313, Der>::s342();
s348.insert( std::make_pair( L"coincide", new s337( L"coincide", &s1403<_Cont, s1313, Der, s1584>::s1952, s1153,
{ s1124(), s1124( { s1417 } ), s1124( { s7::s1396 } ) }, 0, 1, true,
{L"list:", L":back"}) ) );
s348.insert( std::make_pair( L"max-element", new s337( L"max-element", &s1403<_Cont, s1313, Der, s1584>::s1213,
0, { s1124(), s1124( { s1417 } ), 
s1124( { s1417, s7::s1400 } ),
s1124( { s7::s1400 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"max-element-idx", new s337( L"max-element-idx", &s1403<_Cont, s1313, Der, s1584>::s1212,
s1154, { s1124(), s1124( { s1417 } ) }, 0, 1 ) ) );
s348.insert( std::make_pair( L"sort", new s337( L"sort", &s1403<_Cont, s1313, Der, s1584>::s1269, 0,
{ s1124(), s1124( { s1417 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"reverse", new s337( L"reverse", &s1403<_Cont, s1313, Der, s1584>::s1256, 0,
{ s1124(), s1124( { s1417 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"shuffle", new s337( L"shuffle", &s1403<_Cont, s1313, Der, s1584>::s1595, 0,
{ s1124(), s1124( { s1417 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"for-each", new s337( L"for-each", &s1403<_Cont, s1313, Der, s1584>::s1747, s1154,
{ s1124(), s1124( { s1417 } ) }, 0, 1, false ) ) );
s348.insert( std::make_pair( L"find-adjacent", new s337( L"find-adjacent", &s1403<_Cont, s1313, Der, s1584>::s1589, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"subseq", new s337( L"subseq", &s1403<_Cont, s1313, Der, s1584>::s1495,
s1417, { s1124( {s1153} ), s1124( { s1153, s1153 } ) }, 1, 2 ) ) );
s348.insert( std::make_pair( L"begin", new s337( L"begin", &s1403<_Cont, s1313, Der, s1584>::s1585, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"end", new s337( L"end", &s1403<_Cont, s1313, Der, s1584>::s1588, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"front", new s337( L"front", &s1403<_Cont, s1313, Der, s1584>::s1637, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"back", new s337( L"back", &s1403<_Cont, s1313, Der, s1584>::s1623, 0,
{ s1124() }, 0, 0 ) ) );
s348.equal_range( L"begin" ).first->second->s1263( true );
s348.equal_range( L"end" ).first->second->s1263( true );
s348.equal_range( L"front" ).first->second->s1263( true );
s348.equal_range( L"back" ).first->second->s1263( true );
s348.equal_range( L"max-element" ).first->second->s1263( true );
s348.equal_range( L"max-element-idx" ).first->second->s1263( true );
s348.equal_range( L"reverse" ).first->second->s1263( true );
s348.equal_range( L"find-adjacent" ).first->second->s1263( true );
s348.equal_range( L"sort" ).first->second->s1263( true );
s348.equal_range( L"shuffle" ).first->second->s1263( true );
this->s300->TR().s1164( this->s493, s7::s1413, s1514::s1509 );}
template <class _Cont, class s1313, class Der>
void s1578<_Cont, s1313, Der>::s350(){
s1403<_Cont, s1313, Der, s1313>::s350();
s348 = s1403<_Cont, s1313, Der, s1313>::s342();
s1063 tp = s7::s1400;
s348.insert( std::make_pair( L"sort", new s337( L"sort", &s1578<_Cont, s1313, Der>::s1269, 0,
{ s1124( { s1417 } ), s1124( { s1417, tp } ),
s1124( { tp } ), s1124() }, 0, 2/*, {L":asc", L":desc"}*/ ) ) );
s348.insert( std::make_pair( L"group-by", new s337( L"group-by", &s1578::s1466, 0,
{ s1124( { tp } ) }, 1, 1 ) ) );
s348.insert( std::make_pair( L"front", new s337( L"front", &s1578<_Cont, s1313, Der>::s1637, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"back", new s337( L"back", &s1578<_Cont, s1313, Der>::s1623, 0,
{ s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"join", new s337( L"join", &s1578<_Cont, s1313, Der>::s1975, Types.String,
{ s1124( { s1417, Types.String } ), s1124( { Types.String } ) }, 1, 1 ) ) );
s348.equal_range( L"front" ).first->second->s1263( true );
s348.equal_range( L"back" ).first->second->s1263( true );
s348.equal_range( L"sort" ).first->second->s1263( true );
s348.equal_range( L"group-by" ).first->second->s1263( true );
this->s300->TR().s1164( this->s493, s7::s1413, s1514::s1509 );}
template <class _Cont, class s1423, class s1425, class Der>
void s1371<_Cont, s1423, s1425, Der>::s350(){
s313<_Cont, s1423, Der>::s350();
s348 = s313<_Cont, s1423, Der>::s342();
s348.insert( std::make_pair( L"max-element", new s337( L"max-element", &s1371::s1213,
0, { s1124() }, 0, 0 ) ) );
s348.insert( std::make_pair( L"regroup-by", new s337( L"regroup-by", &s1371::s1487, 0,
{ s1124( { s7::s1400 } ) }, 1, 1 ) ) );
s348.equal_range( L"max-element" ).first->second->s1263( true );
s348.equal_range( L"regroup-by" ).first->second->s1263( true );
this->s300->TR().s1164( this->s493, s7::s1413, s1514::s1509 );}
template <class _Cont, class s1313, class Der>
s1063 s313<_Cont, s1313, Der>::
s1190( const std::wstring& s1555, const std::vector<s485>& l ) const{
s1063 s685 = 0;
return s685;}
template <class _Cont, class s1313, class Der, class s1584>
s1063 s1403<_Cont, s1313, Der, s1584>::
s1190( const std::wstring& s1555, const std::vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"begin" || s1555 == L"end" ) {
s813::Cont s1281;
s1063 s1101 = this->ValType();
s685 = this->s300->TR().s1048( std::vector<s1063>(
{ s1582, 1, s1101, 0 } ) );}
else if( s1555 == L"front" || s1555 == L"back" )
s685 = this->ValType();
else if( s1555 == L"max-element-idx" )
s685 = this->s939();
else if( s1555 == L"reverse" )
s685 = this->s352();
else if( s1555 == L"sort" )
s685 = this->s352();
else if( s1555 == L"find-adjacent" || s1555 == L"max-element") {
s813::Cont s1281;
s1063 s1101 = this->ValType();
s685 = this->s300->TR().s1048( std::vector<s1063>( 
{ s1582, 1, s1101, 0 } ) );}
else
s685 = s313<_Cont, s1313, Der>::s1190( s1555, l );
return s685;}
template <class _Cont, class s1313, class Der>
s1063 s1578<_Cont, s1313, Der>::
s1190( const std::wstring& s1555, const std::vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"front" || s1555 == L"back" )
s685 = this->ValType();
else if( s1555 == L"sort" )
s685 = this->s352();
else if( s1555 == L"group-by" ) {
s813::Cont s1281;
s1063 s1101 = this->s325;
std::wstring ts = Types( this->s300, Types.Vector )->s353() + L"<" +
this->s300->TR().s1354( this->s300->TR().s804( s1101 ) ) + L">";
s1063 s1518 = ((s316*)Types( this->s300, Types.Vector ))->s1197( ts, s1281 );
s1063 s1469 = l[0].s15<s838*>()->s1330();
s1063 s1458 = this->s300->TR().s1048( std::vector<s1063>( 
{ s1719, 2, s1469, 0, s1518, 0 } ) );
s685 = this->s300->TR().s1048( std::vector<s1063>( 
{ Types.Index, 1, s1458, 0 } ) );}
else
s685 = s1403<_Cont, s1313, Der, s1313>::s1190( s1555, l );
return s685;}
template <class _Cont, class s1423, class s1425, class Der>
s1063 s1371<_Cont, s1423, s1425, Der>::
s1190( const std::wstring& s1555, const std::vector<s485>& l ) const{
s1063 s685 = 0;
if( s1555 == L"max-element" )
s685 = this->s319();
else if( s1555 == L"regroup-by" ) {
s813::Cont s1281;
s1063 s1101 = this->s325;
s1063 s1469 = l[0].s15<s838*>()->s1330();
s1063 s1458 = this->s300->TR().s1048( std::vector<s1063>( 
{ s1719, 2, s1469, 0, s1101, 0 } ) );
s685 = this->s300->TR().s1048( std::vector<s1063>( 
{ Types.Index, 1, s1458, 0 } ) );}
else
s685 = s313<_Cont, s1423, Der>::s1190( s1555, l );
return s685;}
template <class _Cont, class s1423, class s1425, class Der>
s271* s1371<_Cont, s1423, s1425, Der>::s1337( std::pair<s1423, s1425>& el ){
return new s961( this->s300, std::vector<s271*>({el.first, el.second}) ); }
template <class _Cont, class s1423, class s1425, class Der>
bool s1371<_Cont, s1423, s1425, Der>::insert( s483* s152, s483* s349 ){
return this->s349.insert( std::make_pair( s152, s349 ) ).second;}
template <class _Cont, class s1423, class s1425, class Der>
s483* s1371<_Cont, s1423, s1425, Der>::find( s483* s152 ){
auto it = this->s349.find( s152 );
if( it != end( this->s349 ) )
return it->second;
return NULL;}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1585( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1145( pv->s300, pv->ns, pv->s1187(), NULL );}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1588( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1145( pv->s300, pv->ns, pv->s1191(), NULL );}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1495( s483** s274, size_t s498 ){
if( s498 < 3 || s498 > 4 )
throw new s2::s16( L"subseq: wrong number of arguments" );
using s1132 = Der;
using s941 = typename Der::s1141;
s1132* pv = ( (s1132*)s274[1] );
int s1493 = (int)*s274[2];
int s1494;
if( s498 == 4 )
s1494 = (int)*s274[3];
else
s1494 = (int)pv->s349.size() - 1;
s385 range( s1493, s1494 );
s1146 pr = range.s1196( pv );
s941* s1488;
if( pv->s1140() >= 1 && pr.first.s15<s1127*>()->Reversed() ) {
typename _Cont::reverse_iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1148();
s1522 = pr.second.s15<s941*>()->s1148();
s1488 = new s941( pv->s300, pv, s1521, s1522 );}
else {
typename _Cont::iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1147();
s1522 = pr.second.s15<s941*>()->s1147();
s1488 = new s941( pv->s300, pv, s1521, s1522 );}
s385* s685 = new s385( pv->s300, pv, s1488 );
*s274 = s685;}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1269( s483** s274, size_t s498 ){
using s941 = typename Der::s1141;
Der* pv = NULL;
s1146 pr = s313<_Cont, s1313, Der>::s1428( s274[1], &pv );
if( ( (s326*)pv )->s1140() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s591* s1208 = NULL;
if( s498 == 3 )
s1208 = (s591*)s274[2];
s1303<s1313> qqq;
qqq.s859 = s1208;
if( pv->s1140() >= 1 && pr.first.s15<s1127*>()->Reversed() ) {
typename _Cont::reverse_iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1148();
s1522 = pr.second.s15<s941*>()->s1148();
std::sort( s1521, s1522, /*pv->s1327*/qqq );
}
else {
typename _Cont::iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1147();
s1522 = pr.second.s15<s941*>()->s1147();
std::sort( s1521, s1522, /*pv->s1327*/ qqq );
}
*s274 = pv;}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1589( s483** s274, size_t s498 ){
using s1132 = Der;
using s941 = typename Der::s1141;
s1132* pv;
s385* pr = NULL;
if( s274[1]->s352() == s1417 ) {
pr = (s385*)s274[1];
pv = (s1132*)pr->s819();}
else
pv = ( (s1132*)s274[1] );
s1146 rp;
if( pr ) {
rp = pr->s1196( pv );}
else
rp = pv->s1196();
typename _Cont::iterator s1521, s1522;
s1521 = rp.first.s15<s941*>()->s1147();
s1522 = rp.second.s15<s941*>()->s1147();
typename _Cont::iterator s1983 = std::adjacent_find( s1521, s1522, pv->s1586 );
typename _Cont::iterator s1593 = s1983;
if( s1983 != pv->s349.end() )
++s1593;
s1145* s685 = new s1145( pv->s300, pv->ns,
new s941( pv->s300, pv, s1983, s1593 ), NULL );
s685->s500( pv->ns, true );
*s274 = s685;}
template <class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1747( s483** s274, size_t s498 ){
using s1132 = Der;
using s941 = typename Der::s1141;
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
s941* s1521 = rp.first.s15<s941*>(), *s1522 = rp.second.s15<s941*>();
std::vector<s485> s1841( 1 );
while( !( s1521 == s1522 ) ) {
s1841[0] = s1521->s964();
s1765->s596( s1841 );
s1765->s497( 0, 0 );}}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1637( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
*s274 = (s483*)pv->s1337( pv->s349.front() );}
template<class _Cont, class s1313, class Der, class s1584>
void s1403<_Cont, s1313, Der, s1584>::s1623( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
*s274 = (s483*)pv->s1337( pv->s349.back() );}
template<class _Cont, class s1313, class Der>
void s1578<_Cont, s1313, Der>::s1637( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
s485 s1062 = pv->s349[0];
*s274 = s1062.s15<s483*>();}
template<class _Cont, class s1313, class Der>
void s1578<_Cont, s1313, Der>::s1623( s483** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s349.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
s485 s1062 = pv->s349[pv->s349.size() - 1];
*s274 = s1062.s15<s483*>();}
template <class _Cont, class s1313, class Der>
void s1578<_Cont, s1313, Der>::s1269( s483** s274, size_t s498 ){
using s941 = typename Der::s1141;
Der* pv = NULL;
s1146 pr = s313<_Cont, s1313, Der>::s1428( s274[1], &pv );
if( ( (s326*)pv )->s1140() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s591* s1208 = NULL;
if( s498 == 3 )
s1208 = (s591*)s274[2];
s1303<s1313> s1971;
if( s1208 )
s1971.s859 = s1208;
if( pv->s1140() >= 1 && pr.first.s15<s1127*>()->Reversed() ) {
typename _Cont::reverse_iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1148();
s1522 = pr.second.s15<s941*>()->s1148();
std::sort( s1521, s1522, s1971 );}
else {
typename _Cont::iterator s1521, s1522;
s1521 = pr.first.s15<s941*>()->s1147();
s1522 = pr.second.s15<s941*>()->s1147();
std::sort( s1521, s1522, s1971 );}
*s274 = pv;}
template<class _Cont, class s1313, class Der>
inline void s1578<_Cont, s1313, Der>::s1466( s483** s274, size_t s498 ){
if( s498 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s494() != s1247 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s591* pf = (s591*)s274[2];
s324* s153 = (s324*)*s274;
std::vector<s485>s861;
s861.resize( 1 );
typename _Cont::iterator s1520 = pv->s349.begin();
for( ; s1520 != pv->s349.end(); ++s1520 ) {
s485 s1067 = *s1520;
s861[0] = s1067;
pf->s596( s861 );
s486 s1059 = pf->s497( 0, 0 );
s483* s1456 = s153->find( s1059 );
if( s1456 )
((s316*)s1456)->add( s1067->s335() );
else {
s316* s1484 = new s316( pv->s300, pv->s325, pv->ns, NULL );
s1484->s500( pv->ns );
s1484->add( s1067->s335() );
s153->insert( (s483*)s1059->s335(), (s483*)s1484 );}}}
template<class _Cont, class s1313, class Der>
inline void s1578<_Cont, s1313, Der>::s1975( s483** s274, size_t s498 ){
Der* pv = ( (Der*)s274[1] );
const std::wstring& s72 = ( (s359*)s274[2] )->s320();
std::wstring s685;
if( pv->s349.empty() ) {
*s274 = new s359( pv->s300 );
(*s274)->s1264();
return;}
s685 = pv->s349.front()->to_wstring();
for( size_t n = 1; n < pv->s349.size(); ++n )
s685 += s72 + pv->s349[n]->to_wstring();
*s274 = new s359( pv->s300, s685 );
(*s274)->s1264();}
template<class _Cont, class s1423, class s1425, class Der>
inline void s1371<_Cont, s1423, s1425, Der>::s1487( s483** s274, size_t s498 ){
if( s498 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s494() != s1247 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s591* pf = (s591*)s274[2];
s324* s153 = (s324*)*s274;
std::vector<s485>s861;
s861.resize( 1 );
typename _Cont::iterator s1520 = pv->s349.begin();
for( ; s1520 != pv->s349.end(); ++s1520 ) {
s485 s1067 = *s1520->second;
s861[0] = s1067;
pf->s596( s861 );
s486 s1059 = pf->s497( 0, 0 );
s483* s1456 = s153->find( s1059 );
if( s1456 )
((s316*)s1456)->add( s1067->s335() );
else {
s316* s1484 = new s316( pv->s300, pv->s325, pv->ns, NULL );
s1484->s500( pv->ns, true );
s1484->add( s1067->s335() );
s153->insert( (s483*)s1059->s335(), (s483*)s1484 );}}}
class s415
: public s336{
static s341 s348;
std::wstring path;
std::wstring s524;
s316 s754;
s316 s809;
static void s1238( s483** s274, size_t n );
static void s409( s483** s274, size_t n );
static void s1679( s483** s274, size_t n );
static void s416( s483** s274, size_t n );
static void s417( s483** s274, size_t n );
static void s992( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
s415( s262* s300 ) : s336( s300, NULL, NULL ), s754(s300), s809(s300) {}
s415( s262* s300, const std::wstring& s77, const s263* ast_=NULL );
s415( const s415& right, const s263* ast_ = NULL );
s415( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)&s754; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1607
: public s591{
public:
s1607( s262* s300, s272* s592, s591* s593,
const std::vector<s271*>& l, const s263* s701 );
const std::wstring& s299() const override { return s1318; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
} // namespace
namespace transd{
class s605
: public s591{
public:
s605( s262* s300, s272* s592, s591* s593, const std::vector<s271*>& l,
const s263* s701 );
s1907& s299() const override { return s233; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s712( s1907& s278, s371* ref,
s1907& s334 ) const;
s271* s335() const override;
};
class s305
: public s591{
s485 s306;
public:
s305( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l,
const s263* s701 );
s1907& s299() const override { return s255; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
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
s1907& s299() const override { return s254; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s614
: public s591{
s489 s713;
s486 varval;
s485 s308;
s485 where;
s485 s1062;
s371 s311;
s1531 s312;
public:
s614( s262* s300, s272* s588, Transd* s587, const std::vector<s271*>& l,
const s263* s701 );
s1907& s299() const override { return s260; }
void s500( const s272* s1674, bool proc ) override;
s486 s497( s483** s274, size_t s498 ) override;
s271* s335() const override;
};
class s610
: public s591{
public:
s610( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s610( s262* s300 );
virtual const std::wstring& s299() const override { return s256; }
virtual void s500( const s272* s1674, bool proc ) override;
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s615
: public s591{
static s262* s908;
public:
s615( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s615( s262* s300 );
virtual const std::wstring& s299() const override { return s261; }
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s797
: public s591{
public:
s797( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s797( s262* s300 );
virtual const std::wstring& s299() const override { return s772; }
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s775
: public s591{
std::wstring s906;
public:
s775( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s775( s262* s300 );
virtual const std::wstring& s299() const override { return s821; }
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s1309
: public s591{
public:
s1309( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1309( s262* s300 );
virtual const std::wstring& s299() const override { return s1319; }
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s1612
: public s591{
public:
s1612( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
s1612( s262* s300 );
virtual const std::wstring& s299() const override { return s1622; }
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
};
class s1785
: public s1::s10{
public:
s1785() { }
virtual ~s1785() { }
virtual s486 s760( const std::wstring& s76, bool s714 = true ) const = 0;
virtual void s863( s750& s153 ) const = 0;
virtual void s863( s961& s153 ) const = 0;
virtual void s545( std::vector<std::wstring>& s153 ) const = 0;
virtual size_t s322() const = 0;
};
class s776;
typedef s1::s9<s1785> s822;
bool s1804( s822 l, s822 r );
struct s744 : public s1::s10{
enum Verb { s1777, s1778, s1776, s1779, s2061, s1775 };
Verb verb;
s744()
: verb( s1777 )
{	}
};
class s1783;
typedef std::multimap<s486, s822, s1427> s1788;
typedef std::pair<s1788::iterator, s1788::iterator> s1790;
typedef std::list<s822> s1786;
extern s1786 s1848;
extern s1786::iterator s1849;
struct s1787{
bool operator()( const s486 l, const s486 r ) const{
return l->operator<( ( s483* )&( *r ) );}
bool operator()( const s483* l, const s483* r ) const{
return l->operator<( r );}
bool operator()( const s486 l, const std::pair<s486, s822>& r ) const{
return l->operator<( ( s483* )&( *r.first ) );}
bool operator()( const std::pair<s486, s822>& l, const s486 r ) const{
return l.first->operator<( ( s483* )&( *r ) );}
};
struct s1789{
s1790 pr;
std::wstring s979;
size_t dist;
bool operator<( s1789 const& r ) const{
return dist < r.dist;}
};
class s1784{
protected:
s1783* pdb;
s1786* ptr;
s1786::iterator fi;
s1786::iterator se;
s1786::iterator cur;
public:
s1784( s1783* s1808 );
virtual ~s1784();
virtual void s1873( void* f, void* s ) = 0;
virtual void s1876() = 0;
virtual bool s1837() = 0;
virtual s1785* s1847() = 0;
void sort() { ptr->sort( s1804 ); }
void clear() { ptr->clear(); }
bool empty() { return ptr->empty(); }
void swap( s1784* r ) { ptr->swap( r->s320() ); }
s1786& s320() { return *ptr; }
s1783* s1794() { return pdb; }
virtual void s1833( std::vector<std::wstring>& s153 ) = 0;
};
struct s1806{
bool operator()( const s1789* l, const s1789* r ) const{
return l->operator<( *r );}
bool operator()( const s1789& l, const s1789& r ) const{
return l.operator<( r );}
};
typedef std::set<s1789, s1806 > s1791;
class s1780{
public:
enum s1793 { s1858, s1853, s1856, s1854, s1857, s1855 };
private:
std::wstring field;
s1793 op;
s485 par, s349;
static const std::vector<std::wstring> s1881;
public:
s1780( s262* s300, s272* s588, const std::wstring& s, size_t& pos );
void s500( s272* ns );
void select( s1783* pdb, s1789& s153 );
};
class s1781;
class s1781{
public:
enum s1782 { s1815, s1816, s1814 };
private:
s1782 s1819;
std::vector<s1781> subs;
std::vector<s1780> s1813;
public:
s1781( s262* s300, s272* s588, const std::wstring& s, size_t& pos, s1782 s1819 );
s1781( const s1781& r );
void s500( s272* ns );
void s1812( s262* s300, s272* s588, const std::wstring& s, size_t& pos );
void select( s1783* pdb, s1784* s153 );
};
class s1783
: public s336{
protected:
std::map<std::wstring, s1788> s871;
public:
s1783( s262* s300, s272* ns_, const s263* ast_ )
: s336( s300, ns_, ast_ )	{	}
virtual ~s1783();
virtual void release() override;
virtual void select( s1907& field, s1780::s1793, const s483* s1067,
s1789& s153 ) = 0;
virtual void intersect( const s1789& fi1, const s1789& fi2,
s1786& s153 ) = 0;
virtual void intersect( const s1789& fi, s1784* s153 ) = 0;
virtual void s855( s1907& s858 ) = 0;
virtual s1784* s1820() const = 0;
virtual void s1872( s1784* s153 ) = 0;
virtual bool s2012( s1907& s ) const = 0;
virtual s1063 s2017( s1907& s858 ) const = 0;
};
struct s1714 : public s744{
enum s837 { s828=0, s831 };
int distinct;
int	s889;
std::wstring s888;
int s874;
s1714()
: distinct( -1 ), s889( -1 ), s874( -1 )
{	}
};
struct s1724 : public s744{
};
struct s1710 : public s744{
};
struct s1988 : public s744{
};
struct s1712 : public s1::s10 { };
struct s1713 : public s1712{
s485 what;
s485 where;
s485 s1869;
s485 s890;
s485 s1074;
s485 s874;
};
struct s1723 : public s1712{
s485 what;
s485 s1869;
};
struct s1709 : public s1712{
s485 at;
s485 values;
s1::s9<s1723> s1763;
};
struct s1987 : public s1712{
s485 what;
s485 where;
s485 s1869;
s485 s2059;
s485 s1074;
};
class s899
: public s591{
size_t s910;
s486 s685;
protected:
void s1913( const s577& pl ) const override { }
public:
s899() : s591( NULL, NULL, NULL, s565, L"", NULL ), 
s685( new s360( NULL, false ) ){ }
void s909( size_t idx ) { s910 = idx; }
virtual s486 s497( s483** s705, size_t s498 ) override{
s485 l = s274[0];
s485 r = s274[1];
*s685.s15<s360*>()->s357() = l.s15<s750*>()->operator[]( s910 ).s15<s483*>()->
operator<( r.s15<s750*>()->operator[]( s910 ).s15<s483*>() );
s486 s907 = s685;
return s907;}
};
class s316;
class s791
: public s591{
s485 db;
s371 s2040;
s1::s9<s961> s2039;
s1::s9<s744> s810;
s1::s9<s1712> qp;
s371 s733;
s487 s783;
s1781* s1861;
s484* s1807( const std::wstring& s );
void s1725( const std::vector<s271*>& l_,	TDException& s970 );
void s1727( const s272* s1674, bool proc );
s486 s1732( s483** s274, size_t s498 );
void s1726( const std::vector<s271*>& l_,	TDException& s970 );
void s1728( const s272* s1674, bool proc );
s486 s1733( s483** s274, size_t s498 );
void s2004( const std::vector<s271*>& l_,	TDException& s970 );
void s2006( const s272* s1674, bool proc );
s486 s2009( s483** s274, size_t s498 );
public:
enum s1143{ s1233, s1758, s2022, s1218, s1219, s1237, s1845, s2023, 
s1223, s1234, s1220, s1222,	s1232, s1756 };
s791( s262* s300, s272* s588, s591* s587, const std::vector<s271*>& l, const s263* s701 );
virtual ~s791();
virtual const std::wstring& s299() const override { return s818; }
virtual void s500( const s272* s1674, bool proc ) override;
virtual s486 s497( s483** s274, size_t s498 ) override;
virtual s271* s335() const override;
bool s556( s1907& s278, s371* s153, s1907& s334,	bool ) const override;
s271* s598( size_t off ) override;
};
class s776
: public s1785{
typedef std::map<std::wstring, s485> s727;
s727 s762;
size_t rechash;
public:
s776() {}
explicit s776( s262* s300, s272* s588, s1907& rec, const std::vector<std::wstring>& s743,
std::vector<s485>& types, const s1722& tbfr=s1740 );
s486 s760( s1907& s76, bool s714=true ) const override;
void s863( s750& s153 ) const override;
void s863( s961& s153 ) const override;
void s545( std::vector<std::wstring>& s153 ) const override;
size_t s322() const override;
bool operator==( const s776* p ) const;
bool operator<( const s776* p ) const;
std::wstring to_wstring( uint32_t s1567 = 0 ) const;
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
extern s787::iterator s1850;
class s1798 
: public s1784{
s787* pind;
s787::iterator cur1;
public:
s1798( s1783* pdb );
virtual ~s1798(){}
void s1873( void* f, void* s ) override;
void s1876() override;
bool s1837() override;
s1785* s1847() override;
void s1833( std::vector<std::wstring>& s153 ) override {}
};
class s650
: public s1783{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
private:
static s341 s348;
BaseMap s651, s652, s653;
BaseMap::iterator s318;
s787 s757;
std::wstring s499;
static void s1238( s483** s274, size_t n );
static void s786( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s752( s483** s274, size_t n );
static void s770( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s331( s483** s274, size_t n );
static void s856( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1143 { s1755, s1753, s1751, s1752, s1754, s1844 };
s650( s262* s300, s272* s588 = NULL, const s263* ast_ = NULL ) : s1783( s300, s588, NULL ) {}
s650( s262* s300, s272* s588, s1907& s77, const s263* ast_ = NULL );
s650( const s650& right, const s263* ast_ = NULL );
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)NULL; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s654( s1907& s194 );
void s655( s1907& q );
void s718( s1907& s824, const s1722& tbfr );
void s855( s1907& s858 ) override;
void select( s1907& field, s1780::s1793, const s483* s1067,	s1789& s153 ) override;
s1784* s1820() const override;
void s1872( s1784* s153 ) override;
void intersect( const s1789& fi1, const s1789& fi2,
s1786& s153 ) override;
void intersect( const s1789& fi, s1784* s153 ) override;
bool s2012( s1907& s ) const override;
s1063 s2017( s1907& s858 ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1803;
class s1802
: public s1785{
public:
typedef std::vector<s486> s1795;
private:
s1795 s1863;
size_t rechash;
s1803* s1860;
public:
s1802() {}
s1802( const std::vector<s486>& v, s1803* s1860 );
s1802( s262* s300, s272* s588, s1907& rec,
const std::vector<std::wstring>& s743,
std::vector<s485>& types, const s1722& tbfr=s1740 ){ }
virtual ~s1802();
s486 s760( s1907& s76, bool s714 = true ) const override;
const s1795& s2018() const;
void s863( s750& s153 ) const override;
void s863( s961& s153 ) const override;
void s545( std::vector<std::wstring>& s153 ) const override;
virtual size_t s322() const override;
bool operator==( const s776* p ) const { return 0; }
bool operator<( const s776* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1567 = 0 ) const{ return L""; }
void s304( std::wostream* pd, int s197 = 0 ) const{ }
};
class s1801 : 
public s1784{
public:
s1801( const s1801& r );
s1801( s1783* pdb );
virtual ~s1801();
void s1873( void* f, void* s ) override;
void s1876() override;
bool s1837() override;
s1785* s1847() override;
void s1833( std::vector<std::wstring>& s153 ) override;
};
class s1803
: public s1783{
public:
private:
static s341 s348;
s1786 rows;
std::vector<std::wstring> s806;
std::map<std::wstring, size_t> s1836;
std::vector<s822> s2062;
s1063 s2044;
std::wstring s499;
static void s1238( s483** s274, size_t n );
static void s802( s483** s274, size_t n );
static void s752( s483** s274, size_t n );
static void s770( s483** s274, size_t n );
static void s333( s483** s274, size_t n );
static void s328( s483** s274, size_t n );
static void s2020( s483** s274, size_t n );
static void s2028( s483** s274, size_t n );
static void s2029( s483** s274, size_t n );
static void s856( s483** s274, size_t n );
void s350() override;
const s341& s342() const override { return s348; }
public:
enum s1143 { s1755, s1753, s1751, s1752, s1754, s1844, 
s2021 };
s1803( s262* s300, s272* s588 = NULL, const s263* ast_ = NULL );
s1803( s262* s300, s272* s588, s1907& s77, const s263* ast_ = NULL );
s1803( const s1803& right, const s263* ast_ = NULL );
virtual ~s1803();
s483* s354( const s263& s701, s272* s588, s1907& s334 ) const override;
s483* s355( s272* s588, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1063 s1190( s1907& s1555, const std::vector<s485>& l ) const override;
void release() override;
bool s501( const s483* s502 ) const override;
void* addr() override { return (void*)NULL; }
void s500( const s272* s879, bool ) override;
s271* s335() const override;
void s356( s271* p ) const override;
size_t s322() const override;
bool operator==( const s483* p ) const override;
bool operator<( const s483* p ) const override;
void s654( s1907& s194 );
void s655( s1907& q ){ }
void s718( s1907& s824, const s1722& tbfr );
void s855( s1907& s858 ) override;
void select( s1907& field, s1780::s1793, const s483* s1067,
s1789& s153 ) override;
s1784* s1820() const override;
void s1872( s1784* s153 ) override;
void intersect( const s1789& fi1, const s1789& fi2,
s1786& s153 ) override;
void intersect( const s1789& fi, s1784* s153 ) override;
size_t s1835( s1907& s1818 ) const;
void s1834( std::vector<std::wstring>& s153 ) { s153 = s806; }
bool s2012( s1907& s ) const override;
s1063 s2017( s1907& s858 ) const override;
std::wstring to_wstring( uint32_t s1567 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
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
void importSymbol( HPROG handle, const std::wstring& s1114, const std::wstring& symName,
const std::wstring& s334 );
void importFile( HPROG handle, const std::wstring& s1114, const std::wstring& s44,
const std::wstring& s334 );
HPROG initShell( const std::wstring& s1114, const std::wstring& modText );
typedef s2::s16 TransdException;
} // namespace transd
