
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
transd.hpp
----------
The minimized distributed header file for C++ binding embeddable
library of Tourbillon virtual compiler.
Transd Project Website: https://github.com/transd-lang
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
/*
*	Checking convertibility
*/
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
class s1438{
int refs;
public:
s1438(){
refs=0;}
~s1438(){}
void reset(){
refs = 0;}
int s11(){
refs++;
return refs;}
int s12(){
refs--;
return refs;}
int s1439(){
return refs;}
};
#ifdef s1445
#define s1446(x) x;
#else
#define s1446(x)
#endif
template<bool>
struct s1440{
void s1441(){}
void s1442(){}
};
template<>
struct s1440<true>{
#ifdef s1445
static int s166;
void s1441() { s166++; }
void s1442() { s166--; }
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
int s1439(){
return refs;}
virtual void deallocate(){
delete this;}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template<class C, bool s1484=false>
class s1444
: public s1440<s1484>{
C* p;
s1438*	s1443;
public:
/*
*	Constructors.
*/
s1444(C *_p)
:p(_p){
if ( p ) {
s1443 = new s1438;
s1443->s11();
s1446( this->s1441() )}}
s1444( const s1444& ptr ){
if ( ptr.p ) {
p = ptr.p;
s1443 = ptr.s1443;
s1443->s11();}
else {
p = nullptr;
s1443 = nullptr;}}
s1444()
:p(nullptr){
s1443 = nullptr;}
template<class D> // converting copy constructor for passing by value
s1444( s1444<D> &pn ){
p = nullptr;
s1443 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1443 = pn.s1467();
s1443->s11();}}}
/*
*	Destructor.
*/
~s1444(){
if(	p && !s1443->s12()	) {
delete p;
delete s1443;
s1446( this->s1442() )}}
/*
*	Operators.
*/
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1444& operator=( s1444<C> &s1513 ){
if ( p  && !s1443->s12() ) {
delete p;
delete s1443;
p = nullptr;
s1443 = nullptr;
s1446( this->s1442() )}
p = s1513.p;
if ( s1513.p ) {
s1443 = s1513.s1443;
s1443->s11();}
return *this;}
s1444& operator=( const s1444<C> &s1513 ){ return operator=((s1444<C>&) s1513); }
s1444& operator=( C* ptr ){
if ( p  && !s1443->s12() ) {
delete p;
delete s1443;
p = nullptr;
s1443 = nullptr;
s1446( this->s1442() )}
p = ptr;
if ( ptr ) {
s1443 = new s1438;
s1443->s11();
s1446( this->s1441() )}
return *this;}
template<class Base>
operator Base*(){
return checked_cast<C, Base>( p );}
template<class D>
s1444& operator=( s1444<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );}
template<class ToType>
ToType s15(){
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast(){
return dynamic_cast<ToType>( p );}
bool operator ==(const s1444<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1444<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1438* s1467() { return s1443; }
int s1439() { return s1443->s1439(); }
void s1507() { s1443->s11(); }
void s1506() {
if ( p  && !s1443->s12() ) {
delete p;
delete s1443;
p = nullptr;
s1443 = nullptr;
s1446( this->s1442() )}}
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
bool operator ==( const C& s363 )const { return ( *p == s363 ); }
bool operator !=( const C& s363 )const { return ( *p != s363 ); }
bool operator <( const C& s363 )const { return ( *p < s363 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1238();
extern std::vector<std::wstring> s1094;
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
s956,
s25
};
s16( const std::wstring& s, uint32_t n = (uint32_t)s17::s19 )
: id( n ){
s26.push_back( s );}
s16( uint32_t n )
: id( n ){
s26.push_back( s1094[n] );}
s16( const s16& right )
: id( right.id ){
s26.assign( right.s26.begin(), right.s26.end() );}
static void s29(){
s27 = (uint32_t)s17::s25 + 1;}
static uint32_t s28(){
return s27++;}
virtual std::wstring Msg( size_t s201 = 0 ) const{
std::wstring s717;
std::list<std::wstring>::const_reverse_iterator it = s26.crbegin();
std::wstring s1189( s201, L' ' );
while( it != s26.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s26.crend() )
s717 += s1189;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s717 += ( i++ ? L"" : s1189 ) + s + L"\n";}
return s717;}
const char* what() const noexcept{
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
return conv.to_bytes( s26.back() ).c_str();}
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
bool s31( const std::wstring& _dir, const std::wstring& s547, std::wstring& s156 );
void s32( const std::wstring& _dir, const std::wstring& s547, std::vector<std::wstring>& s40,
std::vector<std::wstring>& s41 );
time_t s33( const std::wstring& f );
uint8_t s34( const std::wstring& f );
bool s760( const std::wstring& f );
bool s35( const std::wstring& s214 );
bool s36( const std::wstring& s214 );
std::wstring s37();
std::wstring s38();
std::wstring s39();
} // namespace s3
namespace s4 {
extern std::wstring s89;
extern std::wstring s49;
extern std::string s50;
extern std::wstring s51;
extern std::wstring digits;
enum s17 { s23 };
std::wstring s52( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s53( const std::wstring& s, const std::wstring& c );
bool s54( const std::wstring& s, const std::wstring& ss );
void s55( const std::wstring& s, size_t s66, wchar_t left, wchar_t right, 
size_t& start, size_t& end, bool s971 = false );
void s56( const std::wstring& s, size_t s66, wchar_t c, size_t& start, 
size_t& end );
void s1099( const std::wstring& s, size_t& s66, const std::wstring& s1206 );
size_t count( const std::wstring& s78, const std::wstring& s1206, size_t start, size_t end,
bool s971 = false );
int s57( const std::wstring& s78, wchar_t s73, size_t& pos );
void s58( const std::wstring& s, const std::wstring& s73, std::vector<std::wstring>& s156, bool clr = true );
void s295( const std::vector<std::wstring>& v, const std::wstring& s73, std::wstring& s156 );
std::wstring s72( const std::wstring& s78, size_t& pos );
void s59( const std::wstring& s78, const std::wstring& s73, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s60( const std::wstring& s78, const std::wstring& s73,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s61( const std::wstring& s78 );
void s62( std::wstring& s46 );
std::wstring s788( std::wstring path );
bool s63( const wchar_t *str, long *s363, wchar_t **end = NULL );
bool s1718( const wchar_t *str, long long *s363, wchar_t **end = NULL );
bool s1719( const wchar_t *str, unsigned long long *s363, wchar_t **end = NULL );
bool s64( const wchar_t *str, double *s363, wchar_t **end = NULL );
void s959( const std::wstring& s78, std::vector<std::wstring>& s156 );
std::wstring s1404( const std::wstring& s, const std::wstring& chars );
std::string s52( const std::string& l, const std::string& s, const std::string& r );
std::string s53( const std::string& s, const std::string& c );
void s55( const std::string& s, size_t s66, char left, char right, 
size_t& start, size_t& end);
int s57( const std::string& s78, char s73, size_t& pos );
void s58( const std::string& s, const std::string& s73, std::vector<std::string>& s156 );
void s60( const std::string& s78, std::vector<std::pair<std::string, std::string>>& v );
std::string s61( const std::string& s78 );
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
constexpr UINT rol(UINT s363, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s363 << n) | (s363 >> (sizeof(UINT)*8-n));}
void s65( const std::wstring& s79 );
void s82( std::wstring& s78, std::vector<std::wstring>& s1221, std::map<size_t, size_t>& s1145 );
template<class T>
std::wstring s1738( T value ) {
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
extern std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;}
#define U8(x) s5::conv.to_bytes( x )
#define U16(x) s5::conv.from_bytes( x )
#ifdef __LINUX__
#define KCHAR char
#define TOFS(x) s5::conv.to_bytes(x)
#define FROMTERM(x) s5::conv.from_bytes(x)
#define s1735(x) s5::conv.to_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#define s1735(x) x
#endif
namespace consutils {
void s1234();
class s17{
static uint32_t s91;
public:
static void s29();
static uint32_t s92() { return s91; }
};
void s93( const std::wstring& header,
const std::vector<std::wstring>& s94 = { } );
void s98();
void s133( int s74 = 0 );
void s100( bool b = true );
bool s101( const std::wstring& s95 );
int s102( const std::wstring& s95, const std::vector<std::wstring>& s96 );
std::wstring s103( const std::wstring& s95, bool s97 = false );
std::wstring s104( const std::wstring& s95, bool s97 = false );
std::wstring getStringValHist( const std::wstring& s95,
const std::vector<std::wstring>& s105 );
int s106( const std::wstring& s95 );
size_t s107( const std::wstring& s95 );
void s108( int& w, int& h );
void s109( const std::vector<std::wstring>& v, std::vector<std::wstring>& s156,
size_t w, size_t h );
int s110( const std::vector<std::wstring>& v );
#ifdef __LINUX__
char _getch();
#endif
#define s111 372
#define s112 380
#define s113 375
#define s114 377
#define s115 27
#define s116 13
#define s119 224
#define s117 8
#define s118 383
#define s1732 371
#define s1731 379
} // namespace consutils
namespace s6{
enum s134{ s135, s136, s137, s142, 
s138, s139, s143, s140, s141 };
class s144;
class s146;
typedef s1::s9<s144> s145;
class s1033
: public s1::s10{
std::wstring s198;
std::wstring s1231;
std::vector<std::wstring> s1232;
std::map<size_t, size_t> s1233;
size_t s1169;
public:
s1033( const std::wstring& file, bool s198 = true );
const std::wstring& Path() const { return s198;  }
void read( std::vector<s1::s9<s146>>& s156, 
const std::wstring& s194 = std::wstring(L"") );
void s174( const std::wstring& s78, size_t& pos, s1::s9<s146> s156, bool s154 = false );
bool s1104( std::wstring& s, size_t s69, size_t s715, size_t& line ) const;
size_t s1038() const { return s1169; }
};
typedef s1::s9<s1033> s1036;
class s146
: public s1::s10{
std::multimap<std::wstring, s145> s147;
s1036 src;
public:
enum s148 { s149, s150, s151 };
enum s17 { s18, s152 };
const static s144 s153; // similar to string::npos
s146( const s1033* pf ):src( (s1033*)pf){}
void s157( const std::wstring& s78, bool s154 = false);
void s158( std::wostream* pd, bool s154=false ) const;
bool s159( const std::wstring& s155 ) const;
void s160( const std::wstring& s155, std::vector<s145>& s156 ) const;
const s145 s161( const std::wstring& s155 ) const;
void s162( const std::wstring& s77, s145 s363, s148 ap=s149 );
void s1807( const std::wstring& s77 );
void s163( std::vector<std::pair<std::wstring, s145>>& s156 ) const;
bool operator==( const s146& r )  const;
void s164( std::wostream* pd, int s201 ) const;
};
bool operator==( const std::vector<s1::s9<s144>>& l,
const std::vector<s1::s9<s144>>& r );
class s144
: public s1::s10{
s134 s202;
s146 obj;
std::wstring str;
std::vector<s1::s9<s144>> s165;
double s166;
bool b;
std::pair<size_t, size_t> s1193;
s1036 s1192;
public:
s144():s202(s135),obj(NULL){}
s144( const std::wstring& s ):s202(s137),obj(NULL),str(s){}
s144( const std::vector<s145>& a ): s202(s138),obj(NULL),s165(a){}
s144( const s1033* pf, const std::wstring& s78, size_t& pos, bool s154 = false );
s134 s167() const { return s202; }
bool s168() const { return s202 == s135; }
const s146& s169() const{
if( s202 == s136 )
return obj;
throw std::runtime_error( "wrong variant" );}
const std::vector<s145>& s170() const{
if( s202 == s138 )
return s165;
throw std::runtime_error( "wrong variant" );}
double s171() const{
if( s202 == s139 )
return s166;
throw std::runtime_error( "wrong variant" );}
int s57() const{
if( s202 == s143 )
return (int)s166;
throw std::runtime_error( "wrong variant" );}
bool s767() const{
if( s202 == s140 )
return b;
throw std::runtime_error( "wrong variant" );}
const std::wstring& s172() const{
if( s202 == s137 || s202 == s142 )
return str;
throw std::runtime_error( "wrong variant" );}
const std::wstring& s939() const{
if( s202 == s142 )
return str;
throw std::runtime_error( "wrong variant" );}
std::wstring s929() const{
if( s202 == s142 )
return str.substr( 1, str.size() - 2 );
throw std::runtime_error( "wrong variant" );}
bool s1109( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s1033* s1106() const { return s1192.s15<s1033*>(); }
bool operator==( const s144& r ) const{
return s202 == r.s202 && obj == r.obj && str == r.str && s165 == r.s165 && b == r.b && s166 == r.s166;}
bool is( const s144& r ) const{
return this == &r;}
void s164( std::wostream* pd, int s201 ) const;
void s158( std::wostream* pd, bool s154=false ) const;
};
void s175( const std::wstring& s198, 
const std::vector<s1::s9<s146>>& s199 );
void s182( const s1033* pf, const std::wstring& s78, size_t& pos, std::vector<s1::s9<s144>>& s156,
bool s154 = false, const std::wstring& s73 = L",");
void s182( const s1033* pf, const std::wstring& s78, std::vector<s1::s9<s144>>& s156,
bool s154 = false, const std::wstring& s73 = L"," );
} // namespace s6
#define TRANSD_VERSION L"0.416"
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s1015 extern const uint32_t
namespace transd {
typedef uint32_t s1171;
typedef uint32_t traitnum_t;
typedef unsigned char tdbyte_t;
typedef std::basic_string<tdbyte_t> s1488;
namespace s7 {
s1015 s1728;
s1015 s1566;
s1015 s1567;
s1015 s1568;
s1015 s1565;
s1015 s1564;
s1015 s1569;
s1015 s1570;
DEFCONST s435;
DEFCONST s436;
DEFCONST s437;
DEFCONST s438;
DEFCONST s439;
DEFCONST s440;
DEFCONST s441;
DEFCONST s442;
DEFCONST s443;
DEFCONST s444;
DEFCONST s1805;
DEFCONST s445;
DEFCONST s446;
DEFCONST s447;
DEFCONST s897;
DEFCONST s448;
DEFCONST s449;
DEFCONST s450;
DEFCONST s811;
DEFCONST s792;
DEFCONST s846;
DEFCONST s451;
DEFCONST s452;
DEFCONST s896;
DEFCONST s1028;
DEFCONST s1263;
DEFCONST s1524;
DEFCONST s1562;
DEFCONST s1563;
DEFCONST s1777;
DEFCONSTI s940;
DEFCONSTI s453;
DEFCONSTI s454;
DEFCONSTI s455;
DEFCONSTI s456;
DEFCONSTI s457;
DEFCONSTI s941;
DEFCONSTI s942;
DEFCONSTI s1342;
DEFCONST s1584;
DEFCONST s1698;
DEFCONST s1582;
DEFCONST s1581;
DEFCONST s1583;
DEFCONST s1580;
DEFCONST s1585;
DEFCONST s1579;
DEFCONST s458;
DEFCONST s459;
DEFCONST s460;
DEFCONST s461;
DEFCONST s462;
DEFCONST s463;
DEFCONST s464;
DEFCONST s465;
DEFCONST s466;
DEFCONST s467;
DEFCONST s468;
DEFCONST s469;
DEFCONST s470;
DEFCONST s471;
DEFCONST s472;
DEFCONST s474;
DEFCONST s473;
DEFCONST s475;
DEFCONST s476;
DEFCONST s477;
DEFCONST s1544;
DEFCONST s815;
DEFCONST s854;
DEFCONST s1747;
DEFCONST s889;
DEFCONST s1241;
DEFCONST s1543;
DEFCONST s478;
DEFCONST s479;
DEFCONST s480;
DEFCONST s481;
DEFCONST s482;
DEFCONST s483;
DEFCONST s485;
DEFCONST s779;
DEFCONST s487;
DEFCONST s1023;
DEFCONST s1002;
DEFCONST s1001;
DEFCONST s1003;
#define s434 3
#define s1235 L','
DEFCONST s433;
DEFCONST s1223;
#define s1733 1
#define s1734	2
s1015 s1535;
s1015 s1458;
s1015 s1011;
s1015 s1010;
s1015 s1457;
s1015 s1246;
s1015 s1005;
s1015 s1224;
s1015 s1006;
s1015 s1225;
s1015 s1226;
s1015 s1227;
s1015 s1007;
s1015 s1008;
s1015 s1009;
s1015 s1243;
s1015 s1244;
s1015 s1536;
s1015 s1537;
s1015 s1538;
s1015 s1773;
s1015 s1245;
s1015 s1456;
s1015 s1455;
s1015 s1843;
s1015 s1844;
s1015 s1548;
s1015 s1845;
s1015 s1546;
s1015 s1547;
s1015 s1846;
s1015 s1696;
s1015 s1697;
s1015 s1729;
s1015 s1775;
s1015 s1774;
extern std::set<std::wstring> s1240;
} // namespace s7
enum s229 { s230, s231, s232, s233 };
extern std::wstring s234[];
extern const std::wstring s235, s236, s237,				s878,
s238,  s239,     s240,    s241,      s242,
s243,  s244, s245, s246,s249,
s247, s248,			s263,	s250,			s262,
s251, s252,     s254,		s795,
s255,   s256, s257, s258,			s259,
s260, s261,		s264,	s987,			s267,
s265,	 s874,			s804, s924, 	s818,
s925,  s1483, s1796, s1482, s1602, 
s1601,
s1736,  s1792,  s1791, s1790,
s1795, s1793, s1794;
class s268;
class s269;
class s276;
class s277;
class s278;
typedef s276* ( *s279 )( const std::wstring& s284, const std::vector<s277*>& s280 );
typedef s1::s9<s269> s1035;
extern const std::wstring s271;
class s269
: public s1::s10{
public:
typedef std::multimap<std::wstring, s1035> s281;
typedef std::map<std::wstring, std::wstring> s270;
private:
static std::map<std::wstring, s279> s282;
std::wstring s283;
std::wstring s284;
s229 s285;
std::wstring s286;
s281 s287;
std::wstring src;
s6::s145 s1161;
s270 s272;
s1171 s1518{};
void s288( const std::wstring& s78 );
void s289( const s6::s146& s136 );
void s290( const std::wstring& s78 );
void s291( const std::wstring& s78 );
void s292( const std::wstring& type, const s6::s144& obj );
void s1101( const std::wstring& s );
static std::wstring s293( const std::wstring& s78, size_t &pos );
public:
enum s17 { s18, s152 };
s269(){ }
s269( s229 at, const std::wstring& qpre, const std::wstring& s77 )
: s283( qpre ), s284( s77 ), s285( at ) { }
s269( const std::wstring& s77, const std::wstring& s363 )
: s284( s77 ), s285( s230 ), s286( s363 ) { }
s269( const std::wstring& type, const s6::s144* s1161 );
s269( const std::wstring& s77, const s6::s144& s302 );
s269( const s6::s146& s136 );
~s269();
s229 s303() const { return s285; }
std::wstring s304() const;
const std::wstring& s305() const { return s284; }
const std::wstring& Src() const { return src; }
const s6::s144* Nqj() const { return s1161.s15<s6::s144*>(); }
const std::wstring& s274( const std::wstring& s309 ) const;
void s275( const std::wstring& s309, const std::wstring& s273 );
s1171 s1475() const { return s1518; }
void s1511( s1171 t) { s1518 = t; }
void reset();
static void s294( const std::wstring& s78, size_t& pos, std::vector<std::wstring>& s156 );
void s295( s6::s146& s136 );
void s292( s269* node );
void s296( s268* s306, size_t s307 = 0 );
const std::wstring& s297() const { return s286; }
const s269* s298( const std::wstring& s284 ) const;
s281& s299() { return s287; }
const s281& s299() const { return s287; }
void s300( const std::wstring& s ) { s284 = s; }
static std::wstring s301( const s6::s146& obj,
const std::wstring& dfault = std::wstring( L"" ) );
static std::wstring s308( const s6::s146& obj,
const std::wstring& s309,
const std::wstring& dfault = std::wstring( L"" ) );
void s310( std::wostream* pd, int s201 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s1032{ s1151, s1150, s1152, s1153, s1149 };
class Msg{
std::wstring func;
std::wstring file;
uint32_t line;
s1032 type;
std::wstring s79;
public:	
Msg( const std::wstring& s, s1032 t = s1149 )
: type( t ), s79( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s1032 t = s1149 )
: func( f ), file( fi ), line( n ), type( t ), s79( s ) {}
s1032 s366() const { return type; }
const std::wstring& Text() const { return s79; }
};}
namespace transd {
class s1222{
std::vector<s8::Msg> s26;
size_t s1095;
public:
s1222() : s1095(0){}
void s1065( const std::wstring& s79 );
void s1065( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line );
void s1067( const std::wstring& s79, const std::string& func, 
const std::string& file, uint32_t line );
size_t s1021() const { return s1095; }
};
extern s1222 s1115;
extern std::vector<std::wstring> s1196;
extern std::vector<std::wstring> s1092;
class TDException
: public s2::s16{
public:
enum class Stage : uint32_t{
s1138 = 0,
s1131,
s1136,
s1135,
s1130,
s1132,
s1133,
s1134,
s1137
};
private:
Stage stage;
uint32_t category;
std::wstring s1203;
const s269* s736;
public:
TDException( uint32_t cat, uint32_t id, const s269* s736 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s269* s736, const s16& e );
TDException( uint32_t cat, uint32_t id, const s269* s736, const std::wstring& s79 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s201 = 0 ) const override;
uint32_t Category() const { return category;  }
void s1187( Stage st ) { stage = st; }
TDException* s1098( const std::wstring& s = std::wstring( L"" ) );
};
class s1014
: public s2::s16{
public:
enum class s17 : uint32_t{
s1080 = ((uint32_t)s16::s17::s25) + 1,
s1177,
s1158,
s1069,
s1081,
s1119,
s1122,
s25
};
s1014( const std::wstring& s )
: s16( s, (uint32_t)s17::s1080){}
s1014( s16& e, const s269& s736, s17 code );
};
class s1022
: public s2::s16{
public:
enum class s17 : uint32_t{
s1157 = ( (uint32_t)s16::s17::s25 ) + 1,
s1097,
s25
};
s1022( s17 code );
s1022( const std::wstring& s, s17 code )
: s16( s, (uint32_t)code ) {}
};
#define s1019		1
#define s1018		2
#define s1020						3
#define s1016					4
#define s1017				5
#define s1254		6
#define s1253		7
#define s1549		8
#define s1730	9
#define s1042(x) throw s1043( L"unknown syntax: " + x );
#define s1041(x) throw s1043( L"syntax error: " + x );
namespace lang {
bool s685( const std::wstring& s, bool s750 = true );
} // namespace tdlang
extern const std::wstring s488;
enum s489 { s490, s491, s492, s1504, s493, s1395, s1396, 
s495, s496, s497, s498, s499, s1173 };
class s268;
class s500;
class s501;
class s278;
class s615;
class s277;
class s345;
class s584;
typedef s277 s502;
typedef s277 TDType;
typedef s1::s9<s502> s503;
typedef s1::s9<s501> s504;
typedef s1::s9<s278> s505;
typedef s1::s9<s615> s506;
class s868;
typedef std::map<std::wstring, std::vector<std::wstring>> s1013;
extern s1013 s1091;
class s277
: public s1::s10{
friend class s509;
s1035 s1071;
protected:
s489 s511;
s1171 s512;
s268* s306;
int wh;
public:
s277( const s269* ast_=NULL ) : s1071( (s269*)ast_ ), s511( s490 ), s512( 0 ), 
wh( s7::s942 )  { }
s277( s489 pt_, const s269* ast_=NULL ) : s1071( (s269*)ast_ ), s511( pt_ ), s512( 0 ), 
wh( s7::s942 ) { }
s277( s268* pass_, s489 pt_, const s269* ast_=NULL ) : s1071( (s269*)ast_ ), s511( pt_ ),
s512( 0 ), s306( pass_ ), wh( s7::s942 )  { }
s277( const s277& r ) : s1071( r.s1071 ), s511( r.s511 ), s512( r.s512 ),
s306( r.s306 ), wh( r.wh ) {}
virtual ~s277();
s489 s513() const { return s511; }
const s269* s627() const { return s1071.s15<s269*>(); }
virtual s501* s515();
virtual s504 s516( s501** s280 = NULL, size_t s517 = 0 );
virtual s1171 s366() const { return s512; }
const s868& s1339() const;
virtual const std::wstring& s368() const;
virtual void s365( s1171 type );
s268* Pass() const  { return s306; }
int s644() const { return wh; }
void setWh( int i ) { wh = i; }
void s1413() { wh = 0; }
void s1411(bool b = true) { if(b) wh |= (1 << (s7::s1342-1)); 
else wh &= ~(1 << (s7::s1342-1));}
bool s1348() const { return wh >= 0; }
bool s1347() const { return (wh > 0) && (wh & (1 << (s7::s1342-1))); }
virtual bool s521( const s501* s522 ) const;
virtual bool s1715( s1171 tp ) const;
virtual const s1013& s1103() const { return s1091;  }
virtual void s519( s501* s961 );
virtual void release() {}
virtual const s501* s523() const;
virtual s277* s349() const;
static void s1500( const s269& ast_, s268* s306, s501* obj,
const std::wstring& s346, std::vector<s277*>& s156 );
static s277* s524( const s269& s736, s268* s306, s501* obj,
const std::wstring& s346 );
static s277* s1121( s268* s306, s277* par, s501* obj, s615* s219,
const std::wstring& s346 );
static s503 s1120( const std::wstring& s78, const s269* ast_, s268* s306, s501* s612 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const;
virtual s1488 to_bytes() const;
/*	static void s294( const std::wstring& s78, size_t& pos,
std::vector<std::wstring>& s156 );
*/
virtual void s310( std::wostream* pd, int s201 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s502*> s525;
s502* s1237( s525& m, const std::wstring& s155 );
void s701( const std::wstring& s, std::wstring& s1229, std::wstring& s625 );
class s501;
class s386;
class s501
: public s277{
friend class s509;
protected:
std::wstring s387; // DEBUG
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) = 0;
s501* ns;
public:
s501( s268* s306, s489 pc, const s269* ast_, s501* ns_ ) 
: s277( s306, pc, ast_ ), ns( ns_ ) { }
s501( const s501& r ) : s277( r ) { }
virtual ~s501();
virtual void s364() = 0;
virtual s1171 s401( const std::wstring& s357 ) const = 0;
virtual s501* s370( s501* s612, const std::vector<s277*>& l = 
std::vector<s277*>(), const s269* ast_ = NULL ) const = 0;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const;
virtual std::wstring s304() const { return ns->s304(); }
virtual std::wstring s899() const { return ns->s899(); }
virtual s501* s358( const std::wstring& s284, const std::wstring& s346,
bool s543 = true ) const {	return NULL;}
virtual void s371( s277* p ) const = 0;
virtual s501* s1710( const s501* p ) const;
virtual const s501* s523() const override = 0;
void s526( const std::wstring& s ) { s387 = s; }
std::wstring getValueName( ) { return s387; }
virtual size_t s330() const = 0;
virtual bool operator==( const s501* p ) const = 0;
virtual bool operator<( const s501* p ) const = 0;
virtual s504 s516( s501** s280, size_t s517 ) override { return this; }
virtual s501* s515() override;
virtual bool s579( const std::wstring& s284, s386* s156,
const std::wstring& s346 ) const	{	return false;	};
virtual s277* s622( size_t off )	{	return NULL; }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const;
};
enum s559 { s530, s531, s532 };
enum s533 { s534, s535, s536 };
typedef s1::s9<s868> s883;
typedef const s868* s1012;
class s868
: public s1::s10{
public:
typedef s1171 s777;
typedef s777 s979;
typedef std::vector<s777> Cont;
private:
Cont vt;
size_t s1211;
public:
s868() {}
s868( s777 t1, s777 t2 = (s777)-1, s777 t3 = (s777)-1 );
s868( const s868& right );
s868( const Cont& v );
void s365( s777 t );
void s365( s1012 pt );
void s835( s777 t );
void s835( s1012 pt );
s979 s366( size_t n = 0 ) const;
const Cont& s876() const { return vt; }
void s876( std::vector<s277*>& s156 ) const;
bool operator==( const s868& p ) const;
size_t s330() const { return s1211; }
};
class s500;
class s268;
struct s1057{
std::size_t operator()( const s868& k ) const{
return k.s330();}
};
struct s1058{
std::size_t operator()( const s868& l, const s868& r ) const{
return l.operator==( r );}
};
class s509{
typedef std::map<std::wstring, s1171> s1051;
typedef std::unordered_map<s868, s1171, s1057, s1058> s1054;
typedef std::map<std::wstring, std::set<std::wstring>> s1000;
typedef std::map<s868::s979, s1000> s1013;
typedef std::map<std::wstring, traitnum_t> s1293;
typedef std::unordered_map<traitnum_t, std::wstring> s1398;
std::vector<s504> s1230;
std::vector<std::wstring> s1213;
std::vector<s868> s1218;
s1051 s1214;
s1054 s1219;
s1013 s1004;
s1293 s978;
s1398 s1410;
traitnum_t s1350;
std::vector<traitnum_t>s1428;
std::vector<s1171>s1685;
std::vector<std::vector<s1171>> s1725;
s268* s306;
s1171 s1178( const s868::Cont& v, const std::wstring& s361 );
void s1312( const std::wstring& alias, const std::wstring& s361 );
public:
s509( s268* pass_ );
void reset();
void s296();
void s539( const s500& st );
void s223( s501* p, const std::wstring& s361 );
void s1842( const std::wstring& s361 );
s1171 s1154( const s868::Cont& v );
traitnum_t s1403( const std::wstring& trait, s1171& s1684 );
void s1301( s868::s979 type, const std::wstring& trait, s1171& s1684 );
bool s1341( s1171 s646, traitnum_t tra );
bool s1639( s1171 s646, s1171 alias );
traitnum_t s1294( s1171 s646 ) const { return s1428[s646]; }
traitnum_t s1632( s1171 alias ) const;
void s1707( s1171 s646, s1171 is );
bool s1708( s1171 s646, s1171 is );
s501* s541( const s6::s144& s363, s501* s612, const std::wstring& s542 );
s501* s541( const s269& s736, s501* s612, const std::wstring& s542 );
s501* s541( s1171 type, s501* s612, const std::wstring& s542 );
const s501* get( const std::wstring& s77, bool s543 = true ) const;
s1171 s1110( const std::wstring& s361, bool s543=true ) const;
s1171 s1111( const s868& vt, bool s543=true ) const;
const s868& s1113( s1171 t ) const;
const s501* s1107( s868::s979 t ) const;
const std::wstring& s855( s1171 n ) const;
bool s159( const std::wstring& s77 ) const;
void s840();
bool s1400();
double s1402();
int s1408();
void s310( std::wostream* pd, int s201 = 0 ) const;
static void s1108( const s868::Cont& v, size_t& idx, s868::Cont& s156 );
size_t s1164( const std::wstring& s, size_t& pos, s868::Cont& s156 );
std::wstring s1112( const s868::Cont& tp );
static std::wstring s1520( const std::wstring& tn );
std::wstring s1429( const std::wstring& tn );
};
class s544
: public s1::s10{
std::vector<std::wstring> s545;
s533 pv;
public:
s544() : pv( s534 ) { }
s544( s533 pv, const std::vector<std::wstring>& s546 );
s544( const std::wstring& ag, const std::wstring& s78 );
s533 s583( const std::wstring& s518 ) const;
static std::vector<std::wstring> s548;
};
class s549
: public s1::s10{
typedef std::map<std::wstring, s544*> s550;
s550 s551;
public:
s549( ) { }
void s552( s533 pv, s269* );
void s553( const std::wstring& s, s544& pl );
void s554( const std::wstring& s, const std::wstring& s547 );
s533 s555( const std::wstring& mem, const std::wstring& s518 );
void s556( const std::wstring& s346,
std::vector<std::wstring>& s156 );
};
class s500{
public:
enum s148 { s149, s557, s150, s151 };
typedef std::map<std::wstring, s503> s558;
private:
s558 s576;
s559 s560;
s549* s562;
bool s561( const std::wstring& s77, s148 ap = s149 );
public:
s500( ): s560( s531 ), s562( NULL ) {}
s500( s559 am ) : s560( am ), s562( NULL ) {}
s500( const s500& s563 );
const s558& Table() const { return s576; }
void s519( s501* s518, bool s538 = true );
void s1825();
void reset();
void s564( const std::wstring& s77, s277* sym, s148 ap = s149 );
void s564( const std::wstring& s77, s6::s145 s363, s148 ap = s149 );
void s565( const std::wstring& s77 );
void s566( const s6::s146& obj, s148 ap = s149 );
void s295( const s500& t, s148 ap = s149 );
bool empty() const { return s576.empty(); }
bool s159( const std::wstring& s77 ) const;
s501* get( const std::wstring& s77, bool s543 = true ) const;
void s567( std::vector<std::wstring>& s156 ) const;
void s568( std::vector<std::wstring>& s156 ) const;
void s569( std::vector<std::wstring>& s156 ) const;
void s570( const s500& t, std::vector<std::wstring>& s156 ) const;
void copy( s500& t, s278* s612, s615* s611, s148 ap = s149 ) const;
void s571( s500& t ) const;
void s1789( s500& t ) const;
void s572( s533 pv, s269* s80 );
void s556( const std::wstring& s346,
std::vector<std::wstring>& s156 );
bool s573( const std::wstring& s284, const std::wstring& s346 ) const;
std::wstring to_wstring( uint32_t s1739 ) const;
void s310( std::wostream* pd, int s201 = 0 ) const;
};
class s574{
typedef std::pair<s501*, std::wstring> s575;
typedef std::multimap<std::wstring, s575> s558;
s558 s576;
std::vector<std::wstring> s582;
public:
s574();
void s577( const std::wstring& s );
void s519( s268* s306, const std::wstring& s581 );
void s1825( s268* s306 );
void s578( const std::wstring& s77, s268* s306, const std::wstring& s581 );
bool s579( const std::wstring& sym, s386* ref );
void copy( s574& t ) const;
};
extern s1::s9<s549> s580;
class s268;
class s350;
typedef void ( *s642 )( s501** s280, size_t n );
namespace s1686 {
extern s1171 s1425;
extern s1171 s1723;}
class s1239{
s350* s612;
std::vector<s1171> s1432;
std::vector<s503> s999;
public:
s1239() : s612( NULL ) {}
s1239( const std::vector<s503>& v, s350* s616 /*= NULL*/ );
s1239( const std::vector<s1171>& v, s350* s616 = NULL )
: s612( s616 ), s1432( v ) {}
bool operator==( const s1239& s547 ) const;
bool operator<( const s1239& s547 ) const;
const s350* Subj() const { return s612; }
const std::vector<s503>& s626() const { return s999; }
std::wstring s1495( s268* s306 ) const;
};
struct s1266{
s1171 s352;
s642 s353;
bool s1308;
s1266()
: s352( 0 ), s353( NULL ), s1308( true ) {}
s1266( s1171 pt, s642 fp, bool s1309 = true )
: s352( pt ), s353( fp ), s1308( s1309 ) {}
};
class s350
: public s501{
public:
class s351{
std::wstring s284;
s1171 s352;
s642 s353;
std::vector<s1239> s1302;
size_t s1146, s1143;
std::vector<std::wstring> s1354;
bool s1321;
bool s1308;
public:
enum class s1255 : uint32_t { s1322 = ((uint32_t)s2::s16::s17::s25) + 1 };
s351( const std::wstring& s708, s642 fp, s1171 s354,
const std::vector<s1239>& v=std::vector<s1239>(), 
size_t s1147 = 0, size_t s1144=(size_t)-1, bool s1309 = true,
const std::vector<std::wstring>& s1353 = std::vector<std::wstring>() )
: s284( s708 ), s352( s354 ), s353( fp ), s1302(v), 
s1146(s1147), s1143(s1144), s1354( s1353 ), s1321(false), s1308( s1309 ) {}
s351()
: s353( NULL ), s1321(false), s1308( true )	{}
s642 s1259() const { return s353; }
size_t s1031() const { return s1146;  }
size_t s1030() const { return s1143;  }
const std::vector<std::wstring>& Markers() const { return s1354; }
s1171 s514() const { return s352; }
void s1414( s1171 t) { s352 = t; }
void s1412( bool b ) { s1321 = b; }
bool s1329( ) const { return s1321; }
bool s1347() const { return s1308; }
bool s1306( /*s350* thi,*/ const s1239& s723 ) const;
};
protected:
typedef std::multimap<std::wstring, s351*> s355;
virtual const s355& s356() const = 0;
static size_t s803;
public:
s350( s268* s306, s501* ns_, const s269* ast_ ) : s501( s306, s491, ast_, ns_ ) {}
s350( const s350& r ) : s501( r ) {}
virtual ~s350() {}
virtual s1171 s401( const std::wstring& s357 ) const override;
static void s834( s268* s306, bool soft = false );
static size_t s859() { return s803;  }
virtual const std::vector<std::wstring>& s1334( const std::wstring& s357 ) const;
virtual s1266 s1340( const std::wstring& s357 ) const;
virtual s1266 s1335( const std::wstring& s357, s1239& ap ) const;
virtual s1266 s1330( const std::wstring& s357, s1239& ap );
virtual const s501* s523() const override;
virtual void* addr() = 0;
virtual s504 s516( s501** s280, size_t s517 ) override;
static s501* s359( s268* s306, const std::wstring& s363, const std::wstring& s346 );
void s1709( s501* s42 );
};
class s373
: public s350{
static s355 s362;
double s363;
static void s1384( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s403( s501** s280, size_t n );
static void s404( s501** s280, size_t n );
static void s405( s501** s280, size_t n );
static void s406( s501** s280, size_t n );
static void s407( s501** s280, size_t n );
static void s408( s501** s280, size_t n );
static void s409( s501** s280, size_t n );
static void s410( s501** s280, size_t n );
static void s411( s501** s280, size_t n );
static void s412( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s414( s501** s280, size_t n );
static void s415( s501** s280, size_t n );
static void s416( s501** s280, size_t n );
static void s417( s501** s280, size_t n );
static void s418( s501** s280, size_t n );
static void s425( s501** s280, size_t n );
static void s426( s501** s280, size_t n );
static void s419( s501** s280, size_t n );
static void s421( s501** s280, size_t n );
static void s422( s501** s280, size_t n );
static void s427( s501** s280, size_t n );
static void s424( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef double s1557;
s373( s268* s306 ) : s350( s306, NULL, NULL ) {}
s373( const s373& r );
s373( s268* s306, const std::vector<s277*>& l );
s373( s268* s306, double d );
s373( s268* s306, const std::wstring& s, size_t& pos );
static s504 proto;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s611 ) override;	
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
double* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0.0; }
virtual operator int() const { return (int)s363; }
virtual operator double() const { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s375
: public s350{
static s355 s362;
bool s363;
static void s402( s501** s280, size_t n );
static void s1384( s501** s280, size_t n );
static void s428( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s375( s268* s306 ) : s350( s306, NULL, NULL ) {}
s375( s268* s306, bool b );
s375( s268* s306, const std::wstring& s, size_t& pos );
s375( const s375& right );
static s504 proto;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
bool* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual void s519( s501* s611 ) override;	
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual operator bool() const { return s363; }
virtual operator int() const override { return (int)s363; }
virtual operator double() const override { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override { return ( s363 ? L"true" : L"false" ); }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s375> s384;
extern s1::s9<s375> s385;
class s376
: public s350{
static s355 s362;
static void s843( s501** s280, size_t n );
static void s528( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
std::wstring s79;
public:
s376( const s376& right );
s376( s268* s306, const std::wstring& s = std::wstring( L"" ) );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
const std::wstring& Msg() const { return s79; }
void s378( const std::wstring& s ) { s79 = s; }
virtual void* addr() override { return (void*)0; }
virtual void s519( s501* s611 ) override;	
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override { return s79; }
virtual operator bool() const { return false; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s379
: public s350{
static s355 s362;
virtual void s364() override {}
virtual const s355& s356() const override { return s362; }
public:
s379( s268* s306 );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void* addr() override { return (void*)0; }
virtual s277* s349() const override;
virtual void s371( s277* p ) const override { }
virtual void s519( s501* s611 ) override;	
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override {	return L"";	}
virtual operator bool() const { return false; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s379> s380;
class s399
: public s350{
traitnum_t s1426;
static s355 s362;
virtual void s364() override {}
virtual const s355& s356() const override { return s362; }
public:
s399( s268* s306, traitnum_t tn = 0, s489 pc = s490 );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s277* s349() const override;
virtual bool s521( const s501* s522 ) const override;
virtual bool s1715( s1171 tp ) const;
traitnum_t s1714() const { return s1426; }
virtual void* addr() override { return (void*)0; }
virtual void s371( s277* p ) const override { }
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void s519( s501* s611 ) override;	
virtual operator bool() const { return false; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1778 
: public s350{
s500 s655;
static s355 s362;
std::wstring s1821;
static void s1817( s501** s280, size_t n );
static void s1815( s501** s280, size_t n );
static void s1812( s501** s280, size_t n );
static void s1813( s501** s280, size_t n );
static void s1836( s501** s280, size_t n );
static void s1838( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s1778( s268* s306 ) : s350( s306, NULL, NULL ) {}
s1778( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_=NULL );
s1778( const s1778& right, const s269* ast_ = NULL );
s1778( s268* s306, s501* s612, const s6::s146* s1820, const s269* ast_ = NULL );
static s504 proto;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual void* addr() override { return (void*)&s655; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
void load( const std::wstring& s78, bool s198 );
void s1818( const s6::s146* ob, s500::s148 ap = s500::s149 );
void s1808( s500::s558& st ) const;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s376> s875;
extern s1::s9<s379> s780;
extern s1::s9<s399> s828;
extern s1::s9<s399> s946;
extern s1::s9<s399> s381;
extern s1::s9<s399> s382;
extern s1::s9<s399> s383;
extern s1::s9<s399> s950;
extern s1::s9<s399> s1695;
#define s1286 s780->s366()
#define s1275 s375::proto->s366()
#define s1474 s1453::proto->s366()
#define s1754 s1748::proto->s366()
#define s1284 s360::proto->s366()
#define s1283 s373::proto->s366()
#define s1700 s1464::proto->s366()
#define s1701 s1703::proto->s366()
#define s1288 s374::proto->s366()
#define s1755 s1267::proto->s366()
#define s1586 s864->s366()
#define s1587 s1468->s366()
#define s1271 ( std::numeric_limits<size_t>::max )( )
#define U64_MAX ( std::numeric_limits<uint64_t>::max )( )
typedef s373 TDDouble;
class s386
: public s277{
std::wstring s387;
s503 s388;
const s501* s389;
std::vector<size_t> s390;
size_t s391;
public:
s386( const std::wstring& s, s268* s306, s489 cat = s490 );
s386( const s386& right );
virtual s501* s515() override;
virtual const s501* s523() const override { return s389; }
const s503 s396() { return s388; }
const std::wstring& s643() const { return s387; }
virtual s504 s516( s501** s280, size_t s517 ) override;
s501* s392() const;
s501* s393();
size_t s1466() const { return s391; }
void s394( size_t off, const s501* proto );
void s1510( s386* ptr );
size_t s395() const { return s391; }
uint32_t Id() const { return (uint32_t)s391; }
virtual s277* s349() const override;
virtual void s519( s501* s611 ) override;
void s397( s501* p ) { s388 = p; }
void s398( s501* p ) { s389 = p; }
void s1078( const std::vector<std::wstring> &v );
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1776
: public s501{
s504 pobj;
protected:
virtual s501* s369( const s269& s736, s501* s612,
const std::wstring& s346 ) override {	return NULL; }
public:
s1776( s268* s306 )
: s501( s306, s1504, NULL, NULL ) {}
void s1837( s501* obj ) { pobj = obj; }
virtual s277* s622( size_t off ) override 
{ return pobj->s622( off ); }
virtual void s364() override {}
virtual s1171 s401( const std::wstring& s357 ) const override { return 0; }
virtual s501* s370( s501* s612, const std::vector<s277*>& l =
std::vector<s277*>(), const s269* ast_ = NULL ) const override { return NULL;	}
virtual void s371( s277* p ) const override {}
virtual s501* s1710( const s501* p ) const override { return NULL; }
virtual const s501* s523() const override { return NULL; }
virtual size_t s330() const override { return 0;  }
virtual bool operator==( const s501* p ) const override { return false; }
virtual bool operator<( const s501* p ) const override { return false; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override {}
};
typedef s1::s9<s386> s507;
template<class s1478, class Der>
class s1470 :
public s350{
protected:
typedef Der s1307;
s1478 s363;
static s355 s362;
static void s402( s501** s280, size_t n );
static void s403( s501** s280, size_t n );
static void s404( s501** s280, size_t n );
static void s405( s501** s280, size_t n );
static void s406( s501** s280, size_t n );
static void s407( s501** s280, size_t n );
static void s419( s501** s280, size_t n );
static void s408( s501** s280, size_t n );
static void s409( s501** s280, size_t n );
static void s410( s501** s280, size_t n );
static void s411( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s428( s501** s280, size_t n );
static void s414( s501** s280, size_t n );
static void s415( s501** s280, size_t n );
static void s416( s501** s280, size_t n );
static void s417( s501** s280, size_t n );
static void s418( s501** s280, size_t n );
static void s420( s501** s280, size_t n );
static void s421( s501** s280, size_t n );
static void s422( s501** s280, size_t n );
static void s423( s501** s280, size_t n );
static void s427( s501** s280, size_t n );
static void s1772( s501** s280, size_t n );
static void s1721( s501** s280, size_t n );
static void s1722( s501** s280, size_t n );
static void s1675( s501** s280, size_t n );
static void s424( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef s1470<s1478, Der> s1486;
s1470( s268* s306, s501* ns_, const s269* ast_ )
: s350( s306, ns_, ast_ ) {}
s1470( const s1486& r )
: s350( r ), s363( r.s363 ) {}
template<class s1704, class s1705>
static void s1706( s501* src, s501* s827 );
virtual s501* s1710( const s501* p ) const override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s360;
class s360
: public s1470<std::int32_t, s360>{
static s355 s362;
static void s1384( s501** s280, size_t n );
/*static void s402( s501** s280, size_t n );
static void s403( s501** s280, size_t n );
static void s404( s501** s280, size_t n );
static void s405( s501** s280, size_t n );
static void s406( s501** s280, size_t n );
static void s407( s501** s280, size_t n );
static void s408( s501** s280, size_t n );
static void s409( s501** s280, size_t n );
static void s410( s501** s280, size_t n );
static void s411( s501** s280, size_t n );
static void s412( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s428( s501** s280, size_t n );
static void s414( s501** s280, size_t n );
static void s415( s501** s280, size_t n );
static void s416( s501** s280, size_t n );
static void s417( s501** s280, size_t n );
static void s418( s501** s280, size_t n );
static void s419( s501** s280, size_t n );
static void s420( s501** s280, size_t n );
static void s421( s501** s280, size_t n );
static void s422( s501** s280, size_t n );
static void s423( s501** s280, size_t n );
static void s1675( s501** s280, size_t n );
static void s424( s501** s280, size_t n );*/
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef std::int32_t s1557;
s360( ) : s360( NULL ) {}
s360( s268* s306 );
s360( const s360& );
s360( s268* s306, const std::vector<s277*>& l );
s360( s268* s306, int i );
s360( s268* s306, const std::wstring& s, size_t& pos );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual bool s1715( s1171 tp ) const;
virtual void s519( s501* s611 ) override;	
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
static s504 proto;
s1557* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0; }
virtual operator int() const { return s363; }
virtual operator double() const { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1464
: public s1470<std::int64_t, s1464>{
protected:
static s355 s362;
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef std::int64_t s1557;
s1464() : s1464( NULL ) {}
s1464( s268* s306 );
s1464( const s1464& );
s1464( s268* s306, const std::vector<s277*>& l );
s1464( s268* s306, int64_t i );
s1464( s268* s306, const std::wstring& s, size_t& pos );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s611 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
static s504 proto;
int64_t* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0; }
virtual operator int() const { return (int)s363; }
virtual operator double() const { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
};
class s1703
: public s1470<std::uint64_t, s1703>{
protected:
static s355 s362;
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef std::uint64_t s1557;
s1703() : s1703( NULL ) {}
s1703( s268* s306 );
s1703( const s1703& );
s1703( s268* s306, const std::vector<s277*>& l );
s1703( s268* s306, int64_t i );
s1703( s268* s306, const std::wstring& s, size_t& pos );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s611 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
static s504 proto;
s1557* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0; }
virtual operator int() const { return (int)s363; }
virtual operator double() const { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
};
template <>
inline void s1470<s1703::s1557, s1703>::s419( s501** s280, size_t s517 ){
( (s1703*)s280[0] )->s363 = ( (s1703*)s280[1] )->s363;}
template <>
inline void s1470<s1703::s1557, s1703>::s404( s501** s280, size_t s517 ){
if( s517 == 2 )
( (s1703*)s280[0] )->s363 = ( (s1703*)s280[1] )->s363;
else {
s280[2]->s371( s280[0] );
( (s1703*)s280[0] )->s363 =
( (s1703*)s280[1] )->s363 - ( (s1703*)s280[0] )->s363;}}
class s1453
: public s1470<tdbyte_t, s1453>{
protected:
static s355 s362;
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef tdbyte_t s1557;
s1453() : s1453( NULL ) {}
s1453( s268* s306 );
s1453( const s1453& );
s1453( s268* s306, const std::vector<s277*>& l );
s1453( s268* s306, tdbyte_t i );
s1453( s268* s306, const std::wstring& s, size_t& pos );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s611 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
static s504 proto;
tdbyte_t* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0; }
virtual operator int() const { return s363; }
virtual operator double() const { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override { return std::to_wstring( s363 ); }
};
class s1748
: public s1470<wchar_t, s1748>{
protected:
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef wchar_t s1557;
s1748() : s1748( NULL ) {}
s1748( s268* s306 );
s1748( const s1748& );
s1748( s268* s306, const std::vector<s277*>& l );
s1748( s268* s306, wchar_t i );
s1748( s268* s306, const std::wstring& s, size_t& pos );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s611 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
static s504 proto;
wchar_t* s372() { return &s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const { return s363 != 0; }
virtual operator int() const { return s363; }
virtual operator double() const { return (double)s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override { return std::wstring( 1, s363 ); }
};
typedef s360 TDInt;
class s615;
class s278;
typedef std::vector<std::pair<std::wstring, std::wstring>> s649;
typedef std::map<std::wstring, s278*> s650;
typedef std::map<std::wstring, s269*> s651;
class s278
: public s501{
protected:
const s278* s652;
const s278* s653;
s386 s1839;
const std::wstring& s361;
std::wstring s284;
std::wstring s654;
s500 s655;
s574* s656;
std::vector<s503> s657;
std::vector<std::wstring> s658;
virtual void s364() override { }
public:
s278( const s278& s660, std::vector<s503>& s280, const s269* ast_=NULL );
s278( s268* s306, s1171 s354, s489 pc/* = s490*/, const s269* ast_ = NULL );
s278( const std::wstring& s284, s268* s306, s489 pc, const s269* ast_ = NULL );
s278( const std::wstring& s361, const std::wstring& s284, s268* s306, s500& s661,
const s500& s655, const s269* ast_ = NULL );
s278( s269& s736, s268* s306, s489 pc, s501* ns, s559 am,
s650& cl, s649& cnl, s651& al );
const std::wstring& s368() const { return s361; }
virtual const std::wstring& s305() const { return s284; }
std::wstring s304() const;
virtual std::wstring s899() const override { return ns->s304(); }
static s277* s662( const s6::s146& obj, const std::wstring& s284, s268* s306 );
static s277* s662( std::multimap<std::wstring, s502*>& v, s502* s611 );
s501* s663( const s269& s736, s501* s612, const std::wstring& s346 );
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s1171 s401( const std::wstring& s357 ) const override;
virtual bool s521( const s501* s522 ) const override;
virtual const s1013& s1103() const override { return s1091; }
bool s769( const std::wstring& f ) const;
void s921( const std::wstring& s77, s501* s363, s500::s148 ap = s500::s149 );
void s1833( const std::wstring& s77, s501* s363 );
void s1816( const s1778* ob );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual const s501* s523() const override { return s652; }
const s278* s664() const { return s653; }
const std::wstring& s665() const { return s654; }
s501* s358( const std::wstring& s284, const std::wstring& s346,
bool s543 = true ) const override;
void s674( s269& s736 );
void s578( const std::wstring& s77, const std::wstring& s581 );
void s666( s269& s736 );
void s1064( s269& s736 );
void s667( const std::wstring& s346,	std::vector<std::wstring>& s156 );
virtual bool s579( const std::wstring& s284, s386* s156,
const std::wstring& s346 ) const override;
size_t s668( const std::wstring& s284 ) const;
virtual s277* s622( size_t off ) override;
s501* s670( const std::wstring& s284, const std::wstring& s346,
bool s543=true ) const;
bool s671( const std::wstring& sym, const std::wstring& s518 ) const;
bool s555( const std::wstring& sym );
virtual void s519( s501* s961 ) override;
void s673( const s500& s280 ); 
void s157( s269& s736 );
void s1825();
virtual s277* s349() const  override;
virtual void s371( s277* p ) const override;
void s672( s278* s675 ) const;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const;
};
class s584
: public s277{
const std::wstring s625;
std::vector<s277*> s280;
s1035 past;
public:
s584( s268* pass_, const s269* ast_ )
: s277( pass_, s495 ), past( (s269*)ast_ ){}
s584( s268* pass_, const std::wstring& s1727, const std::vector<s277*>& l, const s269* s736 );
s584( const s584& s563 );
const std::wstring& s305() const { return s625; }
std::vector<s277*>& s626() { return s280; }
const s269* s627() { return past; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override { }
};
typedef s1::s9<s584> s508;
class s615;
class s268;
typedef s615 TD;
class s350;
typedef s615 Transd;
typedef std::vector<s503> s600;
typedef std::vector<s504> s601;
typedef std::vector<s503> s602;
class s615
: public s278{
public:
enum s586 { s587, s588, s589, s590, s591, s592 };
protected:
std::wstring s702;
enum s593 { s594, s595, s596, s597 };
s586 s598;
s593 s599;
s501** s603;
s502** s604;
size_t s517, nlocs;
s601 s606;
s600 s280;
std::vector<s504> s1076;
std::vector<s501*> s607;
s602 s608;
std::vector<std::vector<s502*>> s609;
s504 s610;
s504 s612;
s506 s611;
const s269* past;
s1776 s1830;
s503 subject;
s277* s917( s277* par );
void s613(const std::wstring& s346);
void s614(const std::wstring& s346);
void s1787( s501** s740, size_t s517 );
public:
s615( s268* s306, s501* s616, s615* s617, s586 ct,
const std::wstring& s708, const s269* s736 )
: s278( s708, s306, s493, s736 ), s598( ct ),  
s610( NULL ),	s612( s616 ), s611( s617 ), past( s736 ), s1830(s306) {}
s615( s268* s306, s501* s612, s615* s611, s586 ct, 
const std::vector<s277*>& l, const s269* s736 );
s615( const s615& right, s501* s612, s615* s611, const std::vector<s277*>& s280,
const s269* s736 );
virtual ~s615();
s586 s938() const { return s598; }
void s618( s593 vt ) { s599 = vt; }
s593 s619() const { return s599; }
virtual std::wstring s899() const override;
const s269* s627() const { return past; }
virtual s501* s515() override { return s610; }
virtual void s519( const std::wstring& s346, bool proc );
void s620( const std::vector<s503>& l );
typedef std::vector<std::pair<std::wstring, s504>> s900;
void s869( s900& s156 ) const;
void s621( const std::wstring& s346 );
virtual bool s579( const std::wstring& s284, s386* ref,
const std::wstring& s346 ) const override;
virtual s277* s622( size_t off ) override;
virtual s504 s516( s501** s280 = NULL, size_t s517 = 0 ) override;
virtual s277* s349() const override;
static s615* s623( const s269& s736, s268* s306, s278* obj,
const std::wstring& s284, const std::wstring& s581 );
static s584* s1236( const s269& s736, s268* s306, s501* obj,
const std::wstring& s581 );
static s615* s624( s584* cs, s268* s306, s501* s612, s615* s219,
const std::wstring& s581 );
static void s1392( std::vector<s277*>& s280, const std::vector<std::wstring>& s1353 );
static void s1392( std::vector<s503>& s280, const std::vector<std::wstring>& s1353 );
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s910
: public s615{
s642 s585;
bool s1308;
public:
s910( s268* s306, s615* s611, s586 ct, const std::vector<s277*>& l, /*s642 s585,*/
s1171 s512, const std::wstring& s1727, const s269* s736 );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280 = NULL, size_t s517 = 0 ) override;
bool s579( const std::wstring& s284, s386* ref,
const std::wstring& s346 ) const override;
virtual s277* s349() const override;
};
class s911
: public s615{
protected:
public:
s911( s268* s306, s501* s612, s615* s611, s586 ct,
const std::vector<s277*>& l, const s269* s736 );
s911( const s911& right, s501* s612, s615* s611, const std::vector<s277*>& s280,
s586 ct, const s269* s736 );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280 = NULL, size_t s517 = 0 ) override;
virtual s277* s349() const override;
};
class s1526
: public s911{
public:
s1526( s268* s306, s501* s612, s615* s611, const s269* s736 );
s1526( const s1526& right, s501* s612, s615* s611, const std::vector<s277*>& s280,
const s269* s736 );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280 = NULL, size_t s517 = 0 ) override;
virtual s277* s349() const override;
};
namespace s1686 {
extern s1171 s1679;
extern s1171 s1683;
extern s1171 s1678;}
class Stream
: public s350{
public:
Stream( s268* s306, s501* ns, const s269* s212 = NULL )
: s350( s306, ns, s212 ) {}
virtual void s1635( std::wstring& s156, size_t s1646 );
virtual void s1654( const std::wstring& src );
virtual void s1636( std::wstring& s156, const std::wstring& s73 = L"\n" );
virtual void s1655( const std::wstring& src );
virtual void s1634( s1488& s156, size_t s1646 );
virtual void s1653( const s1488& src );
virtual void s1633( s1488& s156, const s1488& s73 = s1488( {'\n'} ) );
virtual void s1652( const s1488& src );
virtual void rewind();
virtual void s1742()=0;
virtual void s1743( int n )=0;
virtual void s1740()=0;
virtual void s1741()=0;
};
template<class s1591, class s1593>
class s1577
: public Stream{
protected:
typedef s1577<s1591, s1593> s1307;
typedef s350::s355 s355;
s1591 *s1648;
s1593 *s1649;
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
static void s1661( s501** s280, size_t n );
public:
s1577( s268* s306, s501* ns, const s269* s212 = NULL )
: Stream( s306, ns, s212 ) {}
s1577(){}
virtual ~s1577() {}
virtual void s1742();
virtual void s1743( int n );
virtual void s1740();
virtual void s1741();
};
template<class s1591, class s1593>
s350::s355 s1577<s1591, s1593>::s362;
template<class s1591, class s1593>
void s1577<s1591, s1593>::s364(){
s362.insert( std::make_pair( L"rewind", new s351( L"rewind", &s1577<s1591,s1593>::s1661, s1286,
{ s1239() }, 0, 0 ) ) );}
template<class s1591, class s1593>
void s1577<s1591, s1593>::s1661( s501** s280, size_t s517 ){
s1307* s1172 = (s1307*)s280[1];
if( s1172->s1648 ) {
if( s1172->s1648->eof() )
s1172->s1648->clear( s1172->s1648->rdstate() &
( s1172->s1648->rdstate() ^ std::ios_base::eofbit ) );
if( !s1172->s1648->good() )
throw new s2::s16( L"file handle is not valid" );
s1172->s1648->seekg( 0 );
s1172->s1648->clear();}
if( s1172->s1649 )
s1172->s1649->seekp( 0 );}
typedef std::basic_istringstream<wchar_t> s1671;
typedef std::basic_ostringstream<wchar_t> s1674;
class s527
: public s1577<s1671,s1674>{
protected:
typedef s527 s1307;
static s355 s362;
std::basic_stringstream<wchar_t> ss;
static void s528( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s527( const s527&, const s269* ast_ = NULL );
s527( s268* s306, s501* ns_ = NULL, const s269* ast_ = NULL );
~s527(){}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual void release() override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void* addr() override { return (void*)&ss; }
virtual void s1635( std::wstring& s156, size_t s1646 ) override;
virtual void s1654( const std::wstring& src ) override;
virtual void s1636( std::wstring& s156, const std::wstring& s73 = L"\n") override;
virtual void s1655( const std::wstring& src ) override;
virtual void s1634( s1488& s156, size_t s1646 ) override;
virtual void s1653( const s1488& src ) override;
virtual void s1633( s1488& s156, const s1488& s73 = s1488( { '\0' } ) ) override;
virtual void s1652( const s1488& src ) override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
typedef std::basic_istringstream<tdbyte_t> s1669;
typedef std::basic_ostringstream<tdbyte_t> s1672;
class s1451
: public s1577<s1669,s1672>{
protected:
typedef s1451 s1307;
static s355 s362;
std::basic_stringstream<tdbyte_t> bs;
static void s1481( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s1451( const s1451&, const s269* ast_ = NULL );
s1451( s268* s306, s501* ns_ = NULL, const s269* ast_ = NULL );
~s1451(){}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual void release() override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void* addr() override { return (void*)&bs; }
virtual void s1635( std::wstring& s156, size_t s1646 ) override;
virtual void s1654( const std::wstring& src ) override;
virtual void s1636( std::wstring& s156, const std::wstring& s73 = L"\n" ) override;
virtual void s1655( const std::wstring& src ) override;
virtual void s1634( s1488& s156, size_t s1646 ) override;
virtual void s1653( const s1488& src ) override;
virtual void s1633( s1488& s156, const s1488& s73 = s1488( { '\0' } ) ) override;
virtual void s1652( const s1488& src ) override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
#define ENC_UTF8  0
#define ENC_UTF16 1
typedef std::basic_ifstream<tdbyte_t> s1670;
typedef std::basic_ofstream<tdbyte_t> s1673;
class s1460
: public s1577<s1670,s1673>{
protected:
typedef s1460 s1307;
static s355 s362;
s503 s214;
s503 mode;
std::wstring s1508;
typedef std::basic_fstream<tdbyte_t> s1668;
std::fstream fs;
static void s1384( s501** s280, size_t n );
static void s1499( s501** s280, size_t n );
static void s1490( s501** s280, size_t n );
static void s424( s501** s280, size_t n );
static void s1658( s501** s280, size_t n );
static void s1523( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
void _open();
void _close();
public:
s1460( const s1460&, const s269* ast_ = NULL );
s1460( s268* s306, s501* ns_ = NULL, const s269* ast_ = NULL );
s1460( s268* s306, const std::vector<s277*>& l, s501* s612, 
const s269* ast_ = NULL );
~s1460(){}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual void release() override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void* addr() override { return (void*)&fs; }
virtual void s1635( std::wstring& s156, size_t s1646 ) override;
virtual void s1654( const std::wstring& src ) override;
virtual void s1636( std::wstring& s156, const std::wstring& s73 = L"\n" ) override;
virtual void s1655( const std::wstring& src ) override;
virtual void s1634( s1488& s156, size_t s1646 ) override;
virtual void s1653( const s1488& src ) override;
virtual void s1633( s1488& s156, const s1488& s73 = s1488( { '\0' } ) ) override;
virtual void s1652( const s1488& src ) override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1573
: public s1577<std::wistream, std::wostream>{
static s355 s362;
static void s528( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s1573( const s527&, const s269* ast_ = NULL );
s1573( s268* s306, s501* ns_, const s269* ast_ = NULL );
~s1573(){}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void* addr() override { return NULL/*(void*)&std::wcin*/; }
virtual void s1635( std::wstring& s156, size_t s1646 ) override;
virtual void s1654( const std::wstring& src ) override;
virtual void s1636( std::wstring& s156, const std::wstring& s73 ) override;
virtual void s1655( const std::wstring& src ) override;
virtual void s1634( s1488& s156, size_t s1646 ) override;
virtual void s1653( const s1488& src ) override;
virtual void s1633( s1488& s156, const s1488& s73 ) override;
virtual void s1652( const s1488& src ) override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1575
: public s1577<std::wistream, std::wostream>{
static s355 s362;
static void s528( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s1575( const s527&, const s269* ast_ = NULL );
s1575( s268* s306, s501* ns_, const s269* ast_ = NULL );
~s1575(){}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
virtual void* addr() override { return NULL; }
virtual void s1635( std::wstring& s156, size_t s1646 ) override;
virtual void s1654( const std::wstring& src ) override;
virtual void s1636( std::wstring& s156, const std::wstring& s73 ) override;
virtual void s1655( const std::wstring& src ) override;
virtual void s1634( s1488& s156, size_t s1646 ) override;
virtual void s1653( const s1488& src ) override;
virtual void s1633( s1488& s156, const s1488& s73 ) override;
virtual void s1652( const s1488& src ) override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s527> s870;
extern s1::s9<s1451> s1452;
extern s1::s9<s1460> s1461;
extern s1::s9<s1573> s1574;
extern s1::s9<s1575> s1576;
class s268;
class s400;
class Iterator{
public:
virtual ~Iterator() {}
virtual s277* s322() = 0;
virtual s277* s1053() = 0;
virtual const s277* s1053() const = 0;
virtual s277* Idx() = 0;
virtual s277* El() = 0;
virtual bool operator==( const Iterator* r ) const { return this == r; }
virtual bool operator<( const Iterator* r ) const { return this < r; }
};
typedef std::pair<s1::s1444<Iterator>, s1::s1444<Iterator>> s1268;
struct s909;
class s400;
class s336
: public s350{
protected:
s1171 s324;
s1171 s1343;
s1171 s334;
virtual s501* s1333( Iterator* it );
public:
s336( s268* s306, s501* ns_, const s269* ast_ )
: s350( s306, ns_, ast_ ), s324( 0 ), s1343( 0 ), s334( 0 ) {}
s336( const s336& r )
: s350( r ), s324( r.s324 ), s1343( r.s1343 ), s334( r.s334 ) {}
virtual ~s336() {}
virtual size_t s1261() const { return 0; }
virtual Iterator* s321( s400* r ) = 0;
virtual s1171 s327() const { return s324; }
virtual s1171 s1024() const { return s1343; }
virtual s1171 ValType() const { return s334; }
virtual Iterator* s1328() = 0;
virtual Iterator* s1332() = 0;
virtual s1268 s1337() = 0;
virtual Iterator* s1304( const s501* idx );
virtual Iterator* s1326( const s501* s363 );
virtual Iterator* s1386( const s501* s363 );
virtual s501* sort( bool reverse, s909* cmp );
};
class s400
: public s336,
public Iterator{
s503 s612;
s1::s9<s336> s1082;
s1::s1444<Iterator> s1640;
s503 s1393, s1394;
s504 s1716, s1717;
bool s1073, s1074;
Iterator* s325;
uint64_t s1086, s1720;
int incr;
s1::s9<s1703> s1316;
static s355 s362;
std::wstring s518;
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
enum s1265 { s1373, s1381, s1372, s1380, s1383, s1368, s1374 };
s400( s268* s306 );
s400( s268* s306, s336* s612, Iterator* it );
s400( uint64_t b, uint64_t e = U64_MAX );
s400( s268* s306, const std::wstring& s78, const s269* ast_ = NULL );
s400( const s400& right, const s269* ast_ = NULL );
s400( s268* s306, s501* s612, const std::vector<s277*>& l, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s1266 s1340( const std::wstring& s357 ) const;
virtual s1266 s1335( const std::wstring& s357, 
s1239& ap ) const override;
virtual s1266 s1330( const std::wstring& s357,
s1239& ap ) override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual const std::vector<std::wstring>& s1334( const std::wstring& s357 ) const;
virtual size_t s1261() const;
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)s325; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual Iterator* s321( s400* r ) override;
virtual s277* s322() override;
virtual Iterator* s1328() override { return NULL; }
virtual Iterator* s1332() override { return NULL; }
virtual s1268 s1337() override;
s1268 s1337( s336* s612 );
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
s336* s876() { return s1082; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1256
: public s336,
public Iterator{
s503 s612;
s504 s1082;
s1::s9<s400> range;
s503 where, s1180;
s1::s1444<Iterator> s325, s1663;
s386 s1085; // @it - for using in s1346 scope lambdas
s277* s1086;
static s355 s362;
s1::s9<s360> s363, s717;
std::wstring s518;
s1171 s1521;
static void s1384( s501** s280, size_t n );
static void s1516( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
enum s1265 { s1373, s1381, s1372, s1380, s1383, s1498, s1374 };
s1256( s268* s306 ) : s336( s306, NULL, NULL ), s1085( s7::s1544, s306 ), s1086(NULL) {}
s1256( s268* s306, const std::wstring& s78, const s269* ast_ = NULL );
s1256( const s1256& r, const s269* ast_ = NULL );
s1256( s268* s306, s501* s612, const std::vector<s277*>& l, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual s1171 s327() const override { return s717->s366(); }
virtual size_t s1261() const override { return s1082.s15<s336*>()->s1261(); }
virtual s1266 s1335( const std::wstring& s357,
s1239& ap ) const override;
virtual s1266 s1330( const std::wstring& s357,
s1239& ap ) override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual bool s579( const std::wstring& s284, s386* s156,
const std::wstring& s346 ) const override;
virtual s277* s622( size_t off ) override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual Iterator* s321( s400* r ) override;
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
virtual Iterator* s1328() override { return NULL; }
virtual Iterator* s1332() override { return NULL; }
virtual s1268 s1337() override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1040
: public s336,
public Iterator{
s506 s1168;
s506 set;
s506 eq;
s503 start;
s503 end;
s503 incr;
s503 s1087;
s503 s1835;
bool s1155;
std::wstring s518;
static s355 s362;
static void s1384( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
enum s1265 { s1373, s1381, s1372, s1380, s1383, s1368, s1374 };
s1040( s268* s306 );
s1040( s268* s306, const std::wstring& s78, const s269* ast_ = NULL );
s1040( const s1040& r, const s269* ast_ = NULL );
s1040( s268* s306, s501* s612, const std::vector<s277*>& l, const s269* ast_ = NULL );
virtual ~s1040();
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual void s519( s501* s961 ) override;
virtual void s371( s277* p ) const override {}
virtual size_t s330() const { return 0; }
virtual bool operator==( const s501* p ) const { return false; }
virtual bool operator<( const s501* p ) const { return false; }
virtual bool operator==( const Iterator* r ) const;
virtual bool operator<( const Iterator* r ) const;
virtual Iterator* s321( s400* r ) override;
virtual s277* s322() override;
virtual s277* s1053() override { return NULL; }
virtual const s277* s1053() const override { return NULL; }
virtual s277* Idx() override { return NULL; }
virtual s277* El() override { return NULL; }
virtual Iterator* s1328() override { return NULL; }
virtual Iterator* s1332() override { return NULL; }
virtual void* addr() override { return NULL; }
virtual s1268 s1337() override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s400> s864;
extern s1::s9<s1256> s1258;
extern s1::s9<s1040> s1468;
typedef int HPROG;
enum s1540{ s1603=1, s1604, s1605, s1606, s1798, s1607, s1608, s1609, s1610, s1613, s1611, 
s1612, s1799, s1614, s1800, s1615, s1616, s1802, s1803, 
s1617, s1801,
s1618, s1737, s1619, 
s1620, s1621, s1804, s1622,	s1623, s1624 };
extern std::map<std::wstring, int> s1541;
extern std::vector<int> BIFuncs1v;
extern std::vector<std::wstring> s1542;
struct s758{
std::vector<std::wstring> s693;
std::wstring entry;
};
class s584;
class s268
: public s278{
std::vector<std::wstring> s203;
s269 s736;
std::wstring s204;
std::wstring s813;
void s205( const std::wstring& s284 );
void s206( const s6::s146& obj, s758& s156 );
void s217( const std::wstring& s198, const s6::s146& obj );
s509 s207;
s500 s208;
typedef std::map<std::wstring, s501*> s209;
s209 s210;
typedef std::map<uint32_t, std::set<std::wstring>> s1029;
bool s1485;
public:
s268();
~s268();
const std::wstring& s752() const { return s813; }
virtual std::wstring s899() const { return L"::"; }
void s519( bool soft = false );
void reset();
void s211( s269& s212 );
void s213( const std::wstring& s214 );
void s215( s6::s146& obj );
void s216( const std::wstring& s214 );
s501* run( const std::vector<std::wstring>& s723 );
s501* callFunc( const std::wstring& s625, std::vector<std::wstring>& l );
s506 getProc( const std::wstring& s625 );
bool s1496() const { return s1485; }
void s1826( const std::wstring& s702 );
s509& TR() { return s207; }
s615* s218( int s1631, std::vector<s277*>& s280,
s501* s612, s615* s219,	const s269* s736 );
void s222( const std::wstring& s );
void s223( s501* p, const std::wstring& s361 );
void s224( const std::wstring& s363, const std::wstring& s346,
std::vector<std::wstring>& s156 );
virtual bool s579( const std::wstring& s284, s386* s156,
const std::wstring& s346 ) const override;
s504 s225( const std::wstring& s363, const std::wstring& s346 );
bool s226( s386& rf ) const;
s277* s227( const std::wstring& sym, const std::wstring& s518,
bool s543 = true );
void* s228( const std::wstring& s284 );
void s1519( const std::wstring& s702 );
void s1841( const std::wstring& s1809 );
virtual void s310( std::wostream* pd, int s201 = 0 ) const;
};
typedef s1::s9<s268> s757;
namespace s1686 {
extern s1171 s1681;
extern s1171 s1680;
extern s1171 s1682;}
class Iterator;
struct s909;
struct s329{
std::size_t operator()( const s504 k ) const{
return k->s330();}
};
struct s331{
bool operator()( const s504 l, const s504 r ) const{
return l->operator==( ( s501* )&( *r ) );}
bool operator()( const s501* l, const s501* r ) const{
return l->operator==( r );}
bool operator()( const s501& l, const s501& r ) const{
return l.operator==( &r );}
};
struct s1598{
bool operator()( const s504 l, const s504 r ) const{
return l->operator<( ( s501* )&( *r ) );}
bool operator()( const s501* l, const s501* r ) const{
return l->operator<( r );}
bool operator()( const s501& l, const s501& r ) const{
return l.operator<( &r );}
};
void s1300( s268* s306, const std::wstring& s78, 
std::wstring& s1427, std::wstring& s673 );
template<class s1477>
struct s1459 {
bool operator()( const s1477& l, const s1477& r ) { return l < r; }
};
template<class s1477>
struct s1749 {
bool operator()( const s1477& l, const s1477& r ) { return l == r; }
};
template<class s1477, class s1756>
struct s1750{
s506 s931;
std::vector<s503>s933;
s1750() : s931( 0 ),
s933( { new s1756( 0,0 ), new s1756( 0,0 ) } ) {}
bool operator()( const s1477& l, const s1477& r ){
*s933[0].s15<s1756*>()->s372() = l;
*s933[1].s15<s1756*>()->s372() = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
};
template<>
struct s1459<s503>{
std::vector<s503>s933;
s506 s931;
s1459() : s931( 0 ) { s933.resize( 2 ); }
bool operator()( const s503& l, const s503& r ){
if( s931.s14() ) {
s933[0] = l;
s933[1] = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
else
return l.s15<s501*>()->operator<( r.s15<s501*>() );}
};
template<>
struct s1459<s504>{
std::vector<s503>s933;
s506 s931;
s1459() : s931( 0 ) { s933.resize( 2 ); }
bool operator()( const s504& l, const s504& r ){
if( s931.s14() ) {
s933[0] = l.s15<s277*>();
s933[1] = r.s15<s277*>();
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
else
return l->operator<( r.s15<s501*>() );}
};
template<>
struct s1459<tdbyte_t>{
s506 s931;
std::vector<s503>s933;
s1459() : s931( 0 ),
s933( { new s1453( 0,0 ), new s1453( 0,0 ) } ) {}
bool operator()( const tdbyte_t& l, const tdbyte_t& r ){
if( s931.s14() ) {
*s933[0].s15<s1453*>()->s372() = l;
*s933[1].s15<s1453*>()->s372() = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
else
return l < r; }
};
template<>
struct s1459<wchar_t>{
s506 s931;
std::vector<s503>s933;
s1459() : s931( 0 ),
s933( { new s1748( 0,0 ), new s1748( 0,0 ) } ) {}
bool operator()( const wchar_t& l, const wchar_t& r ){
if( s931.s14() ) {
*s933[0].s15<s1748*>()->s372() = l;
*s933[1].s15<s1748*>()->s372() = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
else
return l < r; }
};
template<>
struct s1749<s503> {
bool operator()( const s503& l, const s503& r ) { 
return l.s15<s501*>()->operator==( r.s15<s501*>() );}
};
template<>
struct s1749<s504> {
bool operator()( const s504& l, const s504& r ) { 
return l->operator==( r.s15<s501*>() );}
};
template<>
struct s1750<s503, s503>{
std::vector<s503>s933;
s506 s931;
s1750() : s931( 0 ) { s933.resize( 2 ); }
bool operator()( const s503& l, const s503& r ){
s933[0] = l;
s933[1] = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
};
template<>
struct s1750<s504, s504>{
std::vector<s503>s933;
s506 s931;
s1750() : s931( 0 ) { s933.resize( 2 ); }
bool operator()( const s504& l, const s504& r ){
s933[0] = l.s15<s277*>();
s933[1] = r.s15<s277*>();
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
};
typedef std::wstring s1752;
template<class _Cont, class s1477, class Der>
class s320 :
public s336{
protected:
typedef Der s1307;
_Cont s363;
s1459<s1477> s1491;
s1749<s1477> s1759;
typedef s350::s355 s355;
static s355 s362;
static void s339( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s1405( s501** s280, size_t n );
static void s1418( s501** s280, size_t n );
static void s1514( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
s277* s1502( s1477 el ) { return el; }
static std::pair<typename _Cont::iterator, typename _Cont::iterator> s1596( s501* p, Der* pv );
static s1268 s1599( s501* p, Der** pv );
public:
typedef s320<_Cont, s1477, Der> s1311;
s320( s268* s306, s501* ns, const s269* ast_ );
s320( const s1311& r );
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual s1268 s1337() override;
};
template<class _Cont, class s1477, class Der>
s350::s355 s320<_Cont, s1477, Der>::s362;
template<class _Cont, class s1477, class Der, class s1757>
class s1572 :
public s320<_Cont, s1477, Der>{
protected:
typedef s350::s355 s355;
typedef s350::s351 s351;
s1750<s1477, s1757> s1760;
static void s1758( s501** s280, size_t n );
static void s1761( s501** s280, size_t n );
static void s1811( s501** s280, size_t n );
static void s1797( s501** s280, size_t n );
static void s1356( s501** s280, size_t n );
static void s1355( s501** s280, size_t n );
static void s1405( s501** s280, size_t n );
static void s1418( s501** s280, size_t n );
static void s1769( s501** s280, size_t n );
static void s1763( s501** s280, size_t n );
static void s1667( s501** s280, size_t n );
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
s277* s1502( s1477 el ) { return el; }
public:
typedef s1572<_Cont, s1477, Der, s1757> s1311;
s1572( s268* s306, s501* ns, const s269* ast_ );
s1572( const s1311& r );
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
};
template<class _Cont, class s1477, class Der, class s1757>
s350::s355 s1572<_Cont, s1477, Der, s1757>::s362;
template<class _Cont, class s1477, class Der>
class s1751 :
public s1572<_Cont, s1477, Der, s1477>{
protected:
typedef s350::s355 s355;
typedef s350::s351 s351;
static void s1811( s501** s280, size_t n );
static void s1797( s501** s280, size_t n );
static void s1418( s501** s280, size_t n );
static void s1638( s501** s280, size_t n );
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef s1751<_Cont, s1477, Der> s1311;
s1751( s268* s306, s501* ns, const s269* ast_ );
s1751( const s1311& r );
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
};
template<class _Cont, class s1477, class Der>
s350::s355 s1751<_Cont, s1477, Der>::s362;
template<class s1477>
struct s1550 {
bool operator()( const s1477& l, const s1477& r ) { return l < r; }
};
template<>
struct s1550<std::pair<s504, s504>>{
typedef std::pair<s504, s504> s1590;
std::vector<s503>s933;
s506 s931;
s1550() : s931( 0 ) { s933.resize( 2 ); }
bool operator()( const s1590& l, const s1590& r ){
if( s931.s14() ) {
s933[0] = l.first.s15<s277*>();
s933[1] = r.first.s15<s277*>();
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
else
return l.first->operator<( r.first.s15<s501*>() );}
};
template<class _Cont, class s1592, class s1594, class Der>
class s1539 :
public s320<_Cont, s1592, Der>{
protected:
typedef s350::s355 s355;
typedef s350::s351 s351;
s1550<std::pair<s1592, s1594>> s1629;
static void s1356( s501** s280, size_t n );
static void s1659( s501** s280, size_t n );
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
s277* s1502( std::pair<s1592, s1594>& el );
public:
typedef s1539<_Cont, s1592, s1594, Der> s1311;
s1539( s268* s306, s501* ns, const s269* ast_ );
s1539( const s1311& r );
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual bool insert( s501* s155, s501* s363 );
virtual s501* find( s501* s155 );
};
template<class _Cont, class s1592, class s1594, class Der>
s350::s355 s1539<_Cont, s1592, s1594, Der>::s362;
template <class _Cont, class s1477, class Der>
s320<_Cont, s1477, Der>::s320( s268* s306, s501* ns_, const s269* ast_ )
: s336( s306, ns_, ast_ ){}
template <class _Cont, class s1477, class Der, class s1757>
s1572<_Cont, s1477, Der, s1757>::s1572( s268* s306, s501* ns_, const s269* ast_ )
: s320<_Cont, s1477, Der>( s306, ns_, ast_ ){}
template <class _Cont, class s1477, class Der>
s1751<_Cont, s1477, Der>::s1751( s268* s306, s501* ns_, const s269* ast_ )
: s1572<_Cont, s1477, Der, s1477>( s306, ns_, ast_ ){}
template <class _Cont, class s1592, class s1594, class Der>
s1539<_Cont, s1592, s1594, Der>::s1539( s268* s306, s501* ns_, const s269* ast_ )
: s320<_Cont, s1592, Der>( s306, ns_, ast_ ){}
#define DR ((s502*)*(s280 + 1))
#define PARN(n)((s502*)*(s280 + n))
template<class _Cont, class s1477, class Der>
s1268
s320<_Cont, s1477, Der>::s1599( s501* p, Der** pv ){
using s1247 = Der;
s400* pr = NULL;
if( p->s366() == s1586 ) {
pr = (s400*)p;
*pv = (s1247*)pr->s876();}
else
*pv = ( (s1247*)p );
s1268 rp;
if( pr ) {
rp = pr->s1337( *pv );}
else
rp = (*pv)->s1337();
return rp;}
template<class _Cont, class s1477, class Der>
std::pair<typename _Cont::iterator, typename _Cont::iterator> 
s320<_Cont, s1477, Der>::s1596( s501* p, Der* pv ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s400* pr = NULL;
if( p->s366() == s1586 ) {
pr = (s400*)p;
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)p );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
return std::make_pair( s1693, s1694 );}
template<class _Cont, class s1477, class Der>
void s320<_Cont, s1477, Der>::s339( s501** s280, size_t n ){
using s1247 = Der;//s1307;
s1247* pv = ( (s1247*)s280[1] );
*( (s360*)*s280 )->s372() = (int)pv->s363.size();}
template<class _Cont, class s1477, class Der>
void s320<_Cont, s1477, Der>::s341( s501** s280, size_t n ){
using s1247 = Der;//s1307;
s1247* pv = ( (s1247*)s280[1] );
pv->s363.clear();}
template<class _Cont, class s1477, class Der>
s1268 s320<_Cont, s1477, Der>::s1337(){
return std::make_pair( s1328(), s1332() );}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1405( s501** s280, size_t s517 ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)s280[1] );
if( ((s336*)pv)->s1261() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
std::reverse( s1693, s1694 );}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1769( s501** s280, size_t s517 ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)s280[1] );
if( ((s336*)pv)->s1261() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
std::mt19937 s1832(std::random_device{}());
std::shuffle( s1693, s1694, s1832 );}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1356( s501** s280, size_t s517 ){
using s1027 = typename Der::s1262;
Der* pv = ( (Der*)s280[1] );
typename _Cont::iterator s1693, s1694;
if( s517 == 3 ) {
s400* rv = (s400*)s280[2];
s1268 pr = rv->s1337( pv );
s1693 = pr.first.s15<s1027*>()->s1269();
s1694 = pr.second.s15<s1027*>()->s1269();}
else {
s1693 = pv->s363.begin();
s1694 = pv->s363.end();}
typename _Cont::iterator s1357 = std::max_element( s1693, s1694, pv->s1491 );
*s280 = (s501*)pv->s1502( *s1357 );}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1355( s501** s280, size_t s517 ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)s280[1] );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
auto s1357 = std::max_element( s1693, s1694, pv->s1491 );
s1027 it( pv, s1357, s1357 + 1 );
s280[0] = pv->s1333( &it );}
template<class _Cont, class s1592, class s1594, class Der>
void s1539<_Cont, s1592, s1594, Der>::s1356( s501** s280, size_t s517 ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)s280[1] );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
typename _Cont::iterator s1357 = std::max_element( s1693, s1694, pv->s1629 );
auto tmp = std::make_pair( s1357->first, s1357->second );
*s280 = (s501*)pv->s1502( tmp );}
struct s909{
std::vector<s503>s933;
s506 s931;
s909( s506 s932 ) : s931( s932 ) { s933.resize( 2 ); }
virtual bool operator()( const s503 l, const s503 r ){
s933[0] = l;
s933[1] = r;
s931->s620( s933 );
return (bool)*s931->s516( 0, 0 );}
};
class s374;
class s1753;
class s374
: public s1572<s1752, wchar_t, s374, s1748>{
typedef s1752 s1557;
typedef s374 s1307;
static s355 s362;
std::vector<s503> s280;
static void s1384( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s1768( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s403( s501** s280, size_t n );
static void s845( s501** s280, size_t n );
static void s1771( s501** s280, size_t n );
static void s1764( s501** s280, size_t n );
static void s976( s501** s280, size_t n );
static void s977( s501** s280, size_t n );
static void s829( s501** s280, size_t n );
static void s850( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s414( s501** s280, size_t n );
static void s415( s501** s280, size_t n );
static void s416( s501** s280, size_t n );
static void s417( s501** s280, size_t n );
static void s418( s501** s280, size_t n );
static void s428( s501** s280, size_t n );
static void s424( s501** s280, size_t n );
static void s1657( s501** s280, size_t n );
static void s1142( s501** s280, size_t n );
static void s1515( s501** s280, size_t n );
static void s427( s501** s280, size_t n );
static void s1664( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
typedef s1753 s1262;
s374( const s374&, const s269* ast_ = NULL );
s374( s268* s306, s501* s612, const std::vector<s277*>& l, const s269* ast_ = NULL );
s374( s268* s306, const std::wstring& s = std::wstring( L"" ), const s269* ast_ = NULL );
s374( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual size_t s1261() const override { return 2; }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
static s504 proto;
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const override;
virtual bool operator<( const s501* p ) const override;
s1748 operator[]( size_t n ) { return s1748( s306, s363[n] ); }
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
virtual Iterator* s1304( const s501* idx ) override;
virtual Iterator* s1326( const s501* s363 ) override;
virtual s501* s1333( Iterator* it );
s277* s1502( wchar_t el ) { return new s1748( s306, el ); }
s1557* s372() { return &s363; }
s1557& s328() { return s363; }
virtual void* addr() override { return (void*)&s363; }
virtual operator bool() const override { return !s363.empty(); }
virtual operator int() const override;
virtual operator double() const override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual s1488 to_bytes() const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
typedef s374 TDString;
class s873
: public s615{
s503 s809, s759;
s503 s860, s852;
size_t s756, nTo;
int s844, s781;
s1::s9<s374> str;
enum s783 { s755, s822, s810, s872 };
public:
enum s1265{ s1372, s1380, s1371, s1376, s1364, s1360 };
s873( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s873( s268* s306 );
virtual const std::wstring& s305() const override { return s804; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s374;
class s323;
class s793;
class s1049;
class s1448;
class s332;
class s1552;
typedef std::vector<s503> s1589;
typedef std::vector<s503> s1588;
typedef s1488 s1545;
typedef std::map<s504, s504, s1598> s1558;
typedef std::unordered_map<s504, s504, s329, s331> s1551;
class s1242
: public Iterator{
protected:
bool s968;
public:
s1242() : s968( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s968;  }
};
class s1260
: public s1242{
public:
};
class s1056 
: public s1260{
typedef s1589::iterator s1027;
typedef s1589::reverse_iterator s1397;
s1::s9<s323> v;
s1027 s1359;
s1027 s1201;
s1397 s1409;
s1397 s1662;
uint64_t s1358;
s1::s9<s1703> s1314;
s1::s9<s1049> s1313;
public:
s1056( s1056* it );
s1056( s323* v_, s1027 it, s1027 sent );
s1056( s323* v_, s1397 it, s1397 sent );
virtual ~s1056() {}
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
virtual void reverse();
s1027 s1269() { return s1359; }
s1397 s1270() { return s1409; }
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s1052
: public Iterator{
typedef s1588::iterator s1027;
s1::s9<s793> v;
s1027 s1359;
s1027 s1201;
uint64_t s1358;
s1::s9<s1703> s1314;
public:
s1052( s1052* it );
s1052( s793* v_, s1027 it, s1027 sent );
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
};
class s1026
: public s1242{
typedef s1558::iterator s1027;
typedef s1558::reverse_iterator s1397;
s1::s9<s332> v;
s1027 s1359;
s1027 s1201;
s1397 s1409;
s1397 s1662;
s503 s1314;
s1::s9<s1049> s1313;
public:
s1026( s1026* it );
s1026( s332* v_, s1027 it, s1027 sent );
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
s1027 s1269() { return s1359; }
virtual void reverse();
virtual bool operator==( const Iterator* r ) const override;
};
class s1553
: public Iterator{
typedef s1551::iterator s1027;
s1::s9<s1552> v;
s1027 s1359;
s1027 s1201;
s503 s1314;
s1::s9<s1049> s1313;
public:
s1553( s1553* it );
s1553( s1552* v_, s1027 it, s1027 sent );
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
s1027 s1269() { return s1359; }
virtual bool operator==( const Iterator* r ) const override;
};
class s1753
: public s1260{
typedef s1752::iterator s1027;
typedef s1752::reverse_iterator s1397;
s1::s9<s374> v;
s1027 s1359;
s1027 s1201;
s1397 s1409;
s1397 s1662;
uint64_t s1358;
s1::s9<s1703> s1314;
s1::s9<s1049> s1313;
public:
s1753( s1753* it );
s1753( s374* v_, s1027 it, s1027 sent );
s1753( s374* v_, s1397 it, s1397 sent );
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
virtual void reverse();
s1027 s1269() { return s1359; }
s1397 s1270() { return s1409; }
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s1449
: public s1260{
typedef s1545::iterator s1027;
typedef s1545::reverse_iterator s1397;
s1::s9<s1448> v;
s1027 s1359;
s1027 s1201;
s1397 s1409;
s1397 s1662;
uint64_t s1358;
s1::s9<s1703> s1314;
s1::s9<s1049> s1313;
public:
s1449( s1449* it );
s1449( s1448* v_, s1027 it, s1027 sent );
s1449( s1448* v_, s1397 it, s1397 sent );
virtual s277* s322() override;
virtual s277* s1053() override;
virtual const s277* s1053() const override;
virtual s277* Idx() override;
virtual s277* El() override;
virtual void reverse();
s1027 s1269() { return s1359; }
s1397 s1270() { return s1409; }
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s1267
: public s350{
s503 s612;
s1::s1444<Iterator> s363;
s1171 s334;
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
static void s413( s501** s280, size_t n );
static void s1765( s501** s280, size_t n );
static void s418( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
public:
s1267( s268* s306 ) : s350( s306, NULL, NULL ), s334(0) {}
s1267( s268* s306, const std::wstring& s78, const s269* ast_ = NULL );
s1267( const s1267& right, const s269* ast_ = NULL );
s1267( s268* s306, s501* context, Iterator* it, const s269* ast_ = NULL );
virtual ~s1267() {}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual void s519( s501* s961 ) override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
static s504 proto;
s1171 ValType() const { return s334;  }
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
void operator=( const s1267& p );
virtual bool operator==( const s501* p )  const override;
virtual bool operator<( const s501* p )  const override;
virtual void* addr() override { return (void*)&s363; }
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1056;
class s1449;
class s323
: public s1751<s1589, s503, s323>{
protected:
typedef s1589 s1557;
typedef s323 s1307;
static s355 s362;
std::wstring s518;
static void s1384( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s1415( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1480( s501** s280, size_t n );
static void s853( s501** s280, size_t n );
static void s340( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
void s1061( const std::vector<s277*>& s740, s501* s612, const s269* ast_ );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, s501* s612, const std::wstring& s73 );
void s1479( const std::vector<s277*>& v, s501* s612 );
void s1297( const std::wstring& s1427, s1171& pt, s1171& vt );
public:
typedef s1056 s1262;
s323( s268* s306 ) : s1751( s306, NULL, NULL ) {}
s323( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_ = NULL,
const std::wstring& s73 = L"," );
s323( s268* s306, const std::vector<s277*>& l, s501* s612,
const s269* ast_ = NULL, s1171 s744 = 0, s1171 s1430 = 0 );
s323( const s323& right, const s269* ast_ = NULL );
s323( s268* s306, s1171 s334, s501* s612, const s269* ast_ = NULL );
virtual ~s323() override;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
s1171 s1338( const std::wstring& s1427, s868::Cont& s612 );
virtual size_t s1261() const override { return 2; }
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
void load( const std::wstring& s78, s501* s612, const std::wstring& s73 );
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
s503 operator[]( size_t n ) { return s363[n]; }
const s503& operator[]( size_t n ) const { return s363[n]; }
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
virtual Iterator* s1304( const s501* idx ) override;
virtual Iterator* s1326( const s501* s363 ) override;
virtual s501* s1333( Iterator* it );
void clear() { s363.clear(); }
void add( s502* el ) { s363.push_back( el ); }
void erase( size_t n ) { s363.erase( begin( s363 ) + n ); }
size_t size() const { return s363.size(); }
virtual s501* sort( bool reverse, s909* cmp ) override;
std::vector<s503>& s328() { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s793
: public s336{
protected:
typedef s1588 s1557;
static s355 s362;
s1557 s363;
s1557::iterator s325;
std::wstring s518;
static void s402( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1480( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s340( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s342( s501** s280, size_t n );
static void s1100( s501** s280, size_t n );
static void s1185( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, std::wstring& s1427, std::wstring& s673,
std::vector<s1::s9<s6::s144>>& s96, const s269* ast_, const std::wstring& s73 );
public:
s793( s268* s306 )
: s336( s306, NULL, NULL ) {}
s793( s268* s306, const s269* ast_ )
: s336( s306, NULL, ast_ ) {}
s793( s268* s306, s501* s612, const std::wstring& s78,
const s269* ast_ = NULL, const std::wstring& s73 = L"," );
s793( s268* s306, const std::vector<s277*>& l, const s269* ast_ = NULL );
s793( const s793& right );
virtual ~s793() override;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual s1171 s327() const override;
virtual s1171 s1024() const override { return s360::proto->s366(); }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual size_t s1261() const override { return 2; }
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
s503 operator[]( size_t n ) { return s363[n]; }
const s503& operator[]( size_t n ) const { return s363[n]; }
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
virtual s1268 s1337() override;
void clear() { s363.clear(); }
void add( s503 el ) { s363.push_back( el ); }
void assign( const std::vector<s503>& v );
size_t size() const { return s363.size(); }
std::vector<s503>& s328() { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1049
: public s793{
static s355 s362;
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, /*std::wstring& s1427, std::wstring& s673,*/
s501* s612, const std::wstring& s73 );
virtual void s1297( const std::wstring& s1427 );
static void s402( s501** s280, size_t n );
static void s1416( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1480( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s340( s501** s280, size_t n );
static void s341( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s342( s501** s280, size_t n );
static void s1100( s501** s280, size_t n );
static void s1185( s501** s280, size_t n );
public:
s1049( s268* s306 ) : s793( s306 ) {}
s1049( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_ = NULL,
const std::wstring& s73 = L"," );
s1049( s268* s306, const std::vector<s277*>& l, const s269* ast_ = NULL );
s1049( const s1049& right, const s269* ast_ = NULL );
virtual ~s1049() override {}
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual void s519( s501* s961 ) override;
void load( const std::wstring& s78, s501* s612, const std::wstring& s73 );
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
};
class s1448
: public s1572<s1545, tdbyte_t, s1448, s1453>{
protected:
typedef s1545 s1557;
typedef s1448 s1307;
static s355 s362;
std::wstring s518;
static void s1384( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s1415( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1480( s501** s280, size_t n );
static void s340( s501** s280, size_t n );
static void s413( s501** s280, size_t n );
static void s1505( s501** s280, size_t n );
static void s1522( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, /*std::wstring& s1427, std::wstring& s673,*/
s501* s612, const std::wstring& s73 );
public:
typedef s1449 s1262;
s1448( s268* s306 ) : s1572( s306, NULL, NULL ) {}
s1448( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_ = NULL,
const std::wstring& s73 = L"," );
s1448( s268* s306, const std::vector<s277*>& l, const s269* ast_ = NULL );
s1448( const s1448& right, const s269* ast_ = NULL );
virtual ~s1448() override;
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual size_t s1261() const override { return 2; }
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
void load( const std::wstring& s78, s501* s612, const std::wstring& s73 );
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
tdbyte_t operator[]( size_t n ) { return s363[n]; }
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
virtual Iterator* s1304( const s501* idx ) override;
virtual Iterator* s1326( const s501* s363 ) override;
s277* s1502( tdbyte_t el ) { return new s1453( s306, el ); }
virtual s501* s1333( Iterator* it );
void clear() { s363.clear(); }
void add( tdbyte_t el ) { s363.push_back( el ); }
void erase( size_t n ) { s363.erase( begin( s363 ) + n ); }
size_t size() const { return s363.size(); }
s1557& s328() { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s323> s764;
extern s1::s9<s793> s787;
extern s1::s9<s1049> s1050;
extern s1::s9<s1448> s1450;
typedef s323 TDVector;
class s332;
class s332
: public s1539<s1558, s504, s504, s332>{
protected:
typedef s1558 s1557;
typedef s332 s1307;
static s355 s362;
s1557::iterator s325;
std::wstring s518;
static void s1806( s501** s280, size_t n );
static void s343( s501** s280, size_t n );
static void s829( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1637( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s1768( s501** s280, size_t n );
static void s344( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s342( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, std::wstring& s1427, std::wstring& s673,
std::vector<std::pair<std::wstring, s6::s145>> s147, const s269* ast_ );
void s1297( const std::wstring& s1427, s1171& pt, s1171& et,
s1171& kt, s1171& vt );
void s1479( const std::vector<s277*>& v, s501* s612 );
public:
typedef s1026 s1262;
s332( s268* s306 ) : s1539( s306, NULL, NULL ) {}
s332( s268* s306, s1171 s1343, s1171 s334, s501* s612, const s269* ast_ = NULL );
s332( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_ = NULL );
s332( const s332& right, const s269* ast_ = NULL );
s332( s268* s306, const std::vector<s277*>& l, s501* s612,
const s269* ast_ = NULL, s1171 s744 = 0, s1171 s1323 = 0,
s1171 s1814 = 0, s1171 s1430 = 0);
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
s1171 s1338( const std::wstring& s1427, s868::Cont& s612,
s1171& et,	s1171& kt, s1171& vt );
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual size_t s1261() const override { return 1; }
virtual void s519( s501* s961 ) override;
void load( const std::wstring& s78, s501* s612, const std::wstring& s73 );
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
s1557& s328() { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1552;
class s1552
: public s1539<s1551, s504, s504, s1552>{
protected:
typedef s1551 s1557;
typedef s1552 s1307;
static s355 s362;
s1557::iterator s325;
std::wstring s518;
static void s343( s501** s280, size_t n );
static void s829( s501** s280, size_t n );
static void s337( s501** s280, size_t n );
static void s1637( s501** s280, size_t n );
static void s402( s501** s280, size_t n );
static void s344( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s342( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
virtual void s1299( const std::wstring& s78, std::wstring& s1427, std::wstring& s673,
std::vector<std::pair<std::wstring, s6::s145>> s147, const s269* ast_ );
public:
typedef s1553 s1262;
s1552( s268* s306 ) : s1539( s306, NULL, NULL ) {}
s1552( s268* s306, s1171 s1343, s1171 s334, const s269* ast_ = NULL );
s1552( s268* s306, s501* s612, const std::wstring& s78, const s269* ast_ = NULL );
s1552( const s1552& right, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
s1171 s1338( const std::wstring& s1427, s868::Cont& s612 );
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s363; }
virtual s1171 s1331( const std::wstring& s1727, const std::vector<s503>& l ) const override;
virtual size_t s1261() const override { return 0; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual Iterator* s321( s400* r ) override;
virtual Iterator* s1328() override;
virtual Iterator* s1332() override;
s1557& s328() { return s363; }
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s332> s770;
extern s1::s9<s1552> s1554;
typedef s332 TDIndex;
class s628
: public s615{
std::vector<s1171> types;
std::vector<s506> s678;
public:
s628( s268* s306, s501* s612, s615* s611, s586 ct,
const std::vector<s277*>& l, const s269* s736 );
void s677( s1171 type, s615* pOvr );
virtual s504 s516( s501** s280, size_t s517 ) override;
};
class s906
: public s615{
public:
s906( s268* s306 );
s906( s268* s306, s501* s616, s615* s617, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s257; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s501* s515() override { return this; }
s1171 s1494() const { return s610->s366(); }
virtual s277* s349() const override;
s501* s370( s501* s612, const std::vector<s1171>& vt ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s906> s1264;
class s907
: public s615{
public:
s907( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s924; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s983
: public s615{
int code;
public:
s983( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s987; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s631
: public s615{
public:
s631( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s249; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s632
: public s615{
public:
s632( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s632( s268* s306 );
virtual const std::wstring& s305() const override { return s248; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1578
: public s615{
s386 s1676;
s504 varval;
s503 s315;
s386 s318;
s1703 s319;
s503 lambda;
public:
s1578( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1578( s268* s306 );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual const std::wstring& s305() const override { return s1602; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s633
: public s615{
s602 s647;
std::vector<s602> s648;
public:
enum s1265{ s1369, s1370 };
s633( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s633( s268* s306 );
virtual const std::wstring& s305() const override { return s235; }
virtual void s519( const std::wstring& s346, bool proc ) override;
void s776( bool proc );
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s634
: public s615{
s503 s42;
bool lout;
public:
enum s1265{ s1380, s1643, s1766, s1746, s1744, s1745 };
s634( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s634( s268* s306 );
virtual const std::wstring& s305() const override { return s256; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s636
: public s615{
s376 s79;
public:
s636( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s636( s268* s306 );
virtual const std::wstring& s305() const override { return s264; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s638
: public s615{
public:
s638( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s638( s268* s306 );
virtual const std::wstring& s305() const override { return s263; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s637
: public s615{
s386 s77;
s376 s646;
s1::s9<s638> ctch;
public:
s637( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s637( s268* s306 );
virtual const std::wstring& s305() const override { return s262; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s799
: public s615{
std::vector<std::wstring> fields;
public:
s799( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s795; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1785
: public s615{
s504 cmd;
std::thread s880;
public:
s1785( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1785( const s1785& );
virtual const std::wstring& s305() const override { return s795; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1783
: public s615{
public:
s1783( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1783( const s1783& );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1780
: public s615{
public:
s1780( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1780( const s1780& );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1784
: public s615{
public:
s1784( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1784( const s1784& );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1779
: public s615{
public:
s1779( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1779( const s1779& );
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
template <class _Cont, class s1477, class Der>
void s320<_Cont, s1477, Der>::s364(){
s306->TR().s1301( s512, s7::s1582, s1686::s1681 );
s362.insert( std::make_pair( L"size", new s351( L"size", &s320<_Cont, s1477, Der>::s339, s1284,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"clear", new s351( L"clear", &s320<_Cont, s1477, Der>::s341, s1286,
{ s1239() }, 0, 0 ) ) );}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s364(){
s320<_Cont, s1477, Der>::s364();
s362 = s320<_Cont, s1477, Der>::s356();
s362.insert( std::make_pair( L"max-element", new s351( L"max-element", &s1572<_Cont, s1477, Der, s1757>::s1356,
s1286, { s1239(), s1239( { s1586 } ) }, 0, 1 ) ) );
s362.insert( std::make_pair( L"max-element-idx", new s351( L"max-element-idx", &s1572<_Cont, s1477, Der, s1757>::s1355,
s1286, { s1239(), s1239( { s1586 } ) }, 0, 1 ) ) );
s362.insert( std::make_pair( L"sort", new s351( L"sort", &s1572<_Cont, s1477, Der, s1757>::s1418, s1286,
{ s1239(), s1239( { s1586 } ) }, 0, 1 ) ) );
s362.insert( std::make_pair( L"reverse", new s351( L"reverse", &s1572<_Cont, s1477, Der, s1757>::s1405, s1286,
{ s1239(), s1239( { s1586 } ) }, 0, 1 ) ) );
s362.insert( std::make_pair( L"shuffle", new s351( L"shuffle", &s1572<_Cont, s1477, Der, s1757>::s1769, s1286,
{ s1239(), s1239( { s1586 } ) }, 0, 1 ) ) );
s362.insert( std::make_pair( L"find-adjacent", new s351( L"findAdjacent", &s1572<_Cont, s1477, Der, s1757>::s1763, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"subseq", new s351( L"subseq", &s1572<_Cont, s1477, Der, s1757>::s1667,
s1586, { s1239( {s1284} ), s1239( { s1284, s1284 } ) }, 1, 2 ) ) );
s362.insert( std::make_pair( L"begin", new s351( L"begin", &s1572<_Cont, s1477, Der, s1757>::s1758, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"end", new s351( L"end", &s1572<_Cont, s1477, Der, s1757>::s1761, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"front", new s351( L"front", &s1572<_Cont, s1477, Der, s1757>::s1811, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"back", new s351( L"back", &s1572<_Cont, s1477, Der, s1757>::s1797, 0,
{ s1239() }, 0, 0 ) ) );
s362.equal_range( L"begin" ).first->second->s1412( true );
s362.equal_range( L"end" ).first->second->s1412( true );
s362.equal_range( L"front" ).first->second->s1412( true );
s362.equal_range( L"back" ).first->second->s1412( true );
s362.equal_range( L"max-element" ).first->second->s1412( true );
s362.equal_range( L"max-element-idx" ).first->second->s1412( true );
s362.equal_range( L"reverse" ).first->second->s1412( true );
s362.equal_range( L"find-adjacent" ).first->second->s1412( true );
s362.equal_range( L"sort" ).first->second->s1412( true );
this->s306->TR().s1301( this->s512, s7::s1582, s1686::s1681 );}
template <class _Cont, class s1477, class Der>
void s1751<_Cont, s1477, Der>::s364(){
s1572<_Cont, s1477, Der, s1477>::s364();
s362 = s1572<_Cont, s1477, Der, s1477>::s356();
s1171 tp = s7::s1569;
s362.insert( std::make_pair( L"sort", new s351( L"sort", &s1751<_Cont, s1477, Der>::s1418, s1286,
{ s1239( { s1586 } ), s1239( { s1586, tp } ),
s1239( { tp } ), s1239() }, 0, 2/*, {L":asc", L":desc"}*/ ) ) );
s362.insert( std::make_pair( L"group-by", new s351( L"group-by", &s1751::s1638, 0,
{ s1239( { tp } ) }, 1, 1 ) ) );
s362.insert( std::make_pair( L"front", new s351( L"front", &s1751<_Cont, s1477, Der>::s1811, 0,
{ s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"back", new s351( L"back", &s1751<_Cont, s1477, Der>::s1797, 0,
{ s1239() }, 0, 0 ) ) );
s362.equal_range( L"front" ).first->second->s1412( true );
s362.equal_range( L"back" ).first->second->s1412( true );
s362.equal_range( L"sort" ).first->second->s1412( true );
s362.equal_range( L"group-by" ).first->second->s1412( true );
this->s306->TR().s1301( this->s512, s7::s1582, s1686::s1681 );}
template <class _Cont, class s1592, class s1594, class Der>
void s1539<_Cont, s1592, s1594, Der>::s364(){
s320<_Cont, s1592, Der>::s364();
s362 = s320<_Cont, s1592, Der>::s356();
s362.insert( std::make_pair( L"max-element", new s351( L"max-element", &s1539::s1356,
0, { s1239() }, 0, 0 ) ) );
s362.insert( std::make_pair( L"regroup-by", new s351( L"regroup-by", &s1539::s1659, 0,
{ s1239( { s7::s1569 } ) }, 1, 1 ) ) );
s362.equal_range( L"max-element" ).first->second->s1412( true );
s362.equal_range( L"regroup-by" ).first->second->s1412( true );
this->s306->TR().s1301( this->s512, s7::s1582, s1686::s1681 );}
template <class _Cont, class s1477, class Der>
s1171 s320<_Cont, s1477, Der>::
s1331( const std::wstring& s1727, const std::vector<s503>& l ) const{
s1171 s717 = 0;
return s717;}
template <class _Cont, class s1477, class Der, class s1757>
s1171 s1572<_Cont, s1477, Der, s1757>::
s1331( const std::wstring& s1727, const std::vector<s503>& l ) const{
s1171 s717 = 0;
if( s1727 == L"begin" || s1727 == L"end" ) {
s868::Cont s1433;
s1171 s1216 = this->ValType();
s717 = this->s306->TR().s1154( std::vector<s1171>(
{ s1755, 1, s1216, 0 } ) );}
else if( s1727 == L"front" || s1727 == L"back" )
s717 = this->ValType();
else if( s1727 == L"max-element" )
s717 = this->ValType();
else if( s1727 == L"max-element-idx" )
s717 = this->s1024();
else if( s1727 == L"reverse" )
s717 = this->ValType();
else if( s1727 == L"sort" )
s717 = this->ValType();
else if( s1727 == L"find-adjacent" ) {
s868::Cont s1433;
s1171 s1216 = this->ValType();
s717 = this->s306->TR().s1154( std::vector<s1171>( 
{ s1755, 1, s1216, 0 } ) );}
else
s717 = s320<_Cont, s1477, Der>::s1331( s1727, l );
return s717;}
template <class _Cont, class s1477, class Der>
s1171 s1751<_Cont, s1477, Der>::
s1331( const std::wstring& s1727, const std::vector<s503>& l ) const{
s1171 s717 = 0;
if( s1727 == L"front" || s1727 == L"back" )
s717 = this->ValType();
else if( s1727 == L"sort" )
s717 = this->ValType();
else if( s1727 == L"group-by" ) {
s868::Cont s1433;
s1171 s1216 = this->s334;
std::wstring ts = s764->s368() + L"<" +
this->s306->TR().s1520( this->s306->TR().s855( s1216 ) ) + L">";
s1171 s1690 = s764->s1338( ts, s1433 );
s1171 s1641 = l[0].s15<s906*>()->s1494();
s1171 s1630 = this->s306->TR().s1154( std::vector<s1171>( 
{ s1050->s366(), 2, s1641, 0, s1690, 0 } ) );
s717 = this->s306->TR().s1154( std::vector<s1171>( 
{ s770->s366(), 1, s1630, 0 } ) );}
else
s717 = s1572<_Cont, s1477, Der, s1477>::s1331( s1727, l );
return s717;}
template <class _Cont, class s1592, class s1594, class Der>
s1171 s1539<_Cont, s1592, s1594, Der>::
s1331( const std::wstring& s1727, const std::vector<s503>& l ) const{
s1171 s717 = 0;
if( s1727 == L"max-element" )
s717 = this->s327();
else if( s1727 == L"regroup-by" ) {
s868::Cont s1433;
s1171 s1216 = this->s334;
s1171 s1641 = l[0].s15<s906*>()->s1494();
s1171 s1630 = this->s306->TR().s1154( std::vector<s1171>( 
{ s1050->s366(), 2, s1641, 0, s1216, 0 } ) );
s717 = this->s306->TR().s1154( std::vector<s1171>( 
{ s770->s366(), 1, s1630, 0 } ) );}
else
s717 = s320<_Cont, s1592, Der>::s1331( s1727, l );
return s717;}
template <class _Cont, class s1592, class s1594, class Der>
s277* s1539<_Cont, s1592, s1594, Der>::s1502( std::pair<s1592, s1594>& el ){
return new s1049( this->s306, std::vector<s277*>({el.first, el.second}) ); }
template <class _Cont, class s1592, class s1594, class Der>
bool s1539<_Cont, s1592, s1594, Der>::insert( s501* s155, s501* s363 ){
return this->s363.insert( std::make_pair( s155, s363 ) ).second;}
template <class _Cont, class s1592, class s1594, class Der>
s501* s1539<_Cont, s1592, s1594, Der>::find( s501* s155 ){
auto it = this->s363.find( s155 );
if( it != end( this->s363 ) )
return it->second;
return NULL;}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1758( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
*s280 = new s1267( pv->s306, pv->ns, pv->s1328(), NULL );}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1761( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
*s280 = new s1267( pv->s306, pv->ns, pv->s1332(), NULL );}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1667( s501** s280, size_t s517 ){
if( s517 < 3 || s517 > 4 )
throw new s2::s16( L"subseq: wrong number of arguments" );
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv = ( (s1247*)s280[1] );
int s1665 = (int)*s280[2];
int s1666;
if( s517 == 4 )
s1666 = (int)*s280[3];
else
s1666 = (int)pv->s363.size() - 1;
s400 range( s1665, s1666 );
s1268 pr = range.s1337( pv );
s1027* s1660;
if( pv->s1261() >= 1 && pr.first.s15<s1242*>()->Reversed() ) {
typename _Cont::reverse_iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1270();
s1694 = pr.second.s15<s1027*>()->s1270();
s1660 = new s1027( pv, s1693, s1694 );}
else {
typename _Cont::iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1269();
s1694 = pr.second.s15<s1027*>()->s1269();
s1660 = new s1027( pv, s1693, s1694 );}
s400* s717 = new s400( pv->s306, pv, s1660 );
*s280 = s717;}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1418( s501** s280, size_t s517 ){
using s1027 = typename Der::s1262;
Der* pv = NULL;
s1268 pr = s320<_Cont, s1477, Der>::s1599( s280[1], &pv );
if( ( (s336*)pv )->s1261() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s615* s1351 = NULL;
if( s517 == 3 )
s1351 = (s615*)s280[2];
pv->s1491.s931 = s1351;
if( pv->s1261() >= 1 && pr.first.s15<s1242*>()->Reversed() ) {
typename _Cont::reverse_iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1270();
s1694 = pr.second.s15<s1027*>()->s1270();
std::sort( s1693, s1694, /*cmp_*/pv->s1491 );
}
else {
typename _Cont::iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1269();
s1694 = pr.second.s15<s1027*>()->s1269();
std::sort( s1693, s1694, /*cmp_*/pv->s1491 );
}
*s280 = pv;}
template <class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1763( s501** s280, size_t s517 ){
using s1247 = Der;
using s1027 = typename Der::s1262;
s1247* pv;
s400* pr = NULL;
if( s280[1]->s366() == s1586 ) {
pr = (s400*)s280[1];
pv = (s1247*)pr->s876();}
else
pv = ( (s1247*)s280[1] );
s1268 rp;
if( pr ) {
rp = pr->s1337( pv );}
else
rp = pv->s1337();
typename _Cont::iterator s1693, s1694;
s1693 = rp.first.s15<s1027*>()->s1269();
s1694 = rp.second.s15<s1027*>()->s1269();
typename _Cont::iterator s1357 = std::adjacent_find( s1693, s1694, pv->s1759 );
typename _Cont::iterator s1767 = s1357;
if( s1357 != pv->s363.end() )
++s1767;
*s280 = new s1267( pv->s306, pv->ns,
new s1027( pv, s1357, s1767 ), NULL );}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1811( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
*s280 = (s501*)pv->s1502( pv->s363.front() );}
template<class _Cont, class s1477, class Der, class s1757>
void s1572<_Cont, s1477, Der, s1757>::s1797( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
*s280 = (s501*)pv->s1502( pv->s363.back() );}
template<class _Cont, class s1477, class Der>
void s1751<_Cont, s1477, Der>::s1811( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
s503 s1170 = pv->s363[0];
*s280 = s1170.s15<s501*>();}
template<class _Cont, class s1477, class Der>
void s1751<_Cont, s1477, Der>::s1797( s501** s280, size_t n ){
Der* pv = ( (Der*)s280[1] );
s503 s1170 = pv->s363[pv->s363.size() - 1];
*s280 = s1170.s15<s501*>();}
template <class _Cont, class s1477, class Der>
void s1751<_Cont, s1477, Der>::s1418( s501** s280, size_t s517 ){
using s1027 = typename Der::s1262;
Der* pv = NULL;
s1268 pr = s320<_Cont, s1477, Der>::s1599( s280[1], &pv );
if( ( (s336*)pv )->s1261() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s615* s1351 = NULL;
if( s517 == 3 )
s1351 = (s615*)s280[2];
pv->s1491.s931 = s1351;
if( pv->s1261() >= 1 && pr.first.s15<s1242*>()->Reversed() ) {
typename _Cont::reverse_iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1270();
s1694 = pr.second.s15<s1027*>()->s1270();
std::sort( s1693, s1694, /*cmp_*/pv->s1491 );
}
else {
typename _Cont::iterator s1693, s1694;
s1693 = pr.first.s15<s1027*>()->s1269();
s1694 = pr.second.s15<s1027*>()->s1269();
std::sort( s1693, s1694, /*cmp_*/pv->s1491 );
}
*s280 = pv;}
template<class _Cont, class s1477, class Der>
inline void s1751<_Cont, s1477, Der>::s1638( s501** s280, size_t s517 ){
if( s517 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s280[2]->s513() != s1395 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s615* pf = (s615*)s280[2];
s332* s156 = (s332*)*s280;
std::vector<s503>s933;
s933.resize( 1 );
typename _Cont::iterator s1692 = pv->s363.begin();
for( ; s1692 != pv->s363.end(); ++s1692 ) {
s503 s1175 = *s1692;
s933[0] = s1175;
pf->s620( s933 );
s504 s1166 = pf->s516( 0, 0 );
s501* s1628 = s156->find( s1166 );
if( s1628 )
((s323*)s1628)->add( s1175->s349() );
else {
s323* s1656 = new s323( pv->s306, pv->s334, pv->ns, NULL );
s1656->s519( pv->ns );
s1656->add( s1175->s349() );
s156->insert( (s501*)s1166->s349(), (s501*)s1656 );}}}
template<class _Cont, class s1592, class s1594, class Der>
inline void s1539<_Cont, s1592, s1594, Der>::s1659( s501** s280, size_t s517 ){
if( s517 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s280[2]->s513() != s1395 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s615* pf = (s615*)s280[2];
s332* s156 = (s332*)*s280;
std::vector<s503>s933;
s933.resize( 1 );
typename _Cont::iterator s1692 = pv->s363.begin();
for( ; s1692 != pv->s363.end(); ++s1692 ) {
s503 s1175 = *s1692->second;
s933[0] = s1175;
pf->s620( s933 );
s504 s1166 = pf->s516( 0, 0 );
s501* s1628 = s156->find( s1166 );
if( s1628 )
((s323*)s1628)->add( s1175->s349() );
else {
s323* s1656 = new s323( pv->s306, pv->s334, pv->ns, NULL );
s1656->s519( pv->ns );
s1656->add( s1175->s349() );
s156->insert( (s501*)s1166->s349(), (s501*)s1656 );}}}
class s430
: public s350{
static s355 s362;
std::wstring path;
std::wstring s547;
s323 s798;
s323 s861;
static void s1384( s501** s280, size_t n );
static void s424( s501** s280, size_t n );
static void s431( s501** s280, size_t n );
static void s432( s501** s280, size_t n );
static void s1088( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s430( s268* s306 ) : s350( s306, NULL, NULL ), s798(s306), s861(s306) {}
s430( s268* s306, const std::wstring& s78, const s269* ast_=NULL );
s430( const s430& right, const s269* ast_ = NULL );
s430( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)&s798; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
class s1462
: public s350{
static s355 s362;
std::wstring s198;
std::wstring mode;
FILE* fh;
static void s424( s501** s280, size_t n );
static void s1523( s501** s280, size_t n );
static void s1499( s501** s280, size_t n );
static void s1490( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s1462( s268* s306 ) : s350( s306, NULL, NULL ){}
s1462( s268* s306, const std::wstring& s78, s501* ns_, const s269* ast_=NULL );
s1462( const s1462& right, const s269* ast_ = NULL );
s1462( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return NULL; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s430> s866;
extern s1::s9<s1462> s1463;
class s1471
: public s615{
s504 obj;
s503 s214;
s503 mode;
public:
s1471( s268* s306, s501* s616, s615* s617, 
const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s1482; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1781
: public s615{
public:
s1781( s268* s306, s501* s616, s615* s617,
const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s1482; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
} // namespace
namespace transd{
class s629
: public s615{
public:
s629( s268* s306, s501* s616, s615* s617, const std::vector<s277*>& l,
const s269* s736 );
virtual const std::wstring& s305() const override { return s238; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
s277* s747( const std::wstring& s284, s386* ref,
const std::wstring& s346 ) const;
virtual s277* s349() const override;
};
class s311
: public s615{
s503 s312;
public:
s311( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l,
const s269* s736 );
virtual const std::wstring& s305() const override { return s260; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s314
: public s615{
s503 s315;
s507 s316;
s504 s317;
s386 s318;
s360 s319;
public:
s314( s268* s306, s501* s612, Transd* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s259; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s640
: public s615{
s507 s748;
s504 varval;
s503 s315;
s503 where;
s503 select;
s386 s318;
s1703 s319;
public:
s640( s268* s306, s501* s612, Transd* s611, const std::vector<s277*>& l,
const s269* s736 );
virtual const std::wstring& s305() const override { return s265; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s635
: public s615{
public:
s635( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s635( s268* s306 );
virtual const std::wstring& s305() const override { return s261; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s641
: public s615{
static s268* s993;
public:
s641( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s641( s268* s306 );
virtual const std::wstring& s305() const override { return s267; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s848
: public s615{
public:
s848( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s848( s268* s306 );
virtual const std::wstring& s305() const override { return s818; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s823
: public s615{
std::wstring s991;
public:
s823( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s823( s268* s306 );
virtual const std::wstring& s305() const override { return s878; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1473
: public s615{
public:
s1473( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1473( s268* s306 );
virtual const std::wstring& s305() const override { return s1483; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s1786
: public s615{
public:
s1786( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
s1786( s268* s306 );
virtual const std::wstring& s305() const override { return s1796; }
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
class s825
: public s1::s10{
typedef std::map<std::wstring, s503> s763;
s763 s808;
size_t rechash;
public:
s825() {}
explicit s825( s268* s306, const std::wstring& rec, const std::vector<std::wstring>& s784,
std::vector<s503>& types );
s504 s805( const std::wstring& s77, bool s750=true ) const;
void s937( s793& s156 ) const;
void s568( std::vector<std::wstring>& s156 ) const;
size_t s330() const;
bool operator==( const s825* p ) const;
bool operator<( const s825* p ) const;
std::wstring to_wstring( uint32_t s1739 = 0 ) const;
void s310( std::wostream* pd, int s201 = 0 ) const;
};
typedef s1::s9<s825> s879;
class s867
: public s1::s10{
typedef std::vector<s503> s775;
s775 s863;
size_t s851;
public:
s867() {}
s867( std::vector<std::wstring>& s772, s879 rec );
size_t s330() const;
bool operator==( const s867* p ) const;
bool operator<( const s867* p ) const;
void s310( std::wostream* pd, int s201 = 0 ) const;
};
typedef s1::s9<s867> s774;
struct s817{
std::size_t operator()( const s774 k ) const{
return k->s330();}
};
struct s751{
std::size_t operator()( const s774 l, const s774 r ) const{
return l->operator==( ( s867* )&( *r ) );}
};
struct s916{
std::size_t operator()( const s879 k ) const{
return k->s330();}
};
struct s915{
std::size_t operator()( const s879 l, const s879 r ) const{
return l->operator==( ( s825* )&( *r ) );}
};
class s679
: public s350{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
typedef std::map<std::wstring, std::multimap<s504, s879>> s335;
typedef std::unordered_map<s774, s879, s817, s751> s837;
private:
static s355 s362;
std::map<std::wstring, s335> s945;
BaseMap s680, s681, s682;
BaseMap::iterator s325;
s837 s801;
std::wstring s518;
static void s1384( s501** s280, size_t n );
static void s836( s501** s280, size_t n );
static void s853( s501** s280, size_t n );
static void s796( s501** s280, size_t n );
static void s816( s501** s280, size_t n );
static void s344( s501** s280, size_t n );
static void s339( s501** s280, size_t n );
static void s342( s501** s280, size_t n );
static void s928( s501** s280, size_t n );
virtual void s364() override;
virtual const s355& s356() const override { return s362; }
public:
s679( s268* s306 ) : s350( s306, NULL, NULL ) {}
s679( s268* s306, const std::vector<s277*>& l, const s269* ast_ = NULL );
s679( s268* s306, const std::wstring& s78, const s269* ast_ = NULL );
s679( const s679& right, const s269* ast_ = NULL );
s679( s268* s306, const std::wstring& s, size_t& pos, const s269* ast_ = NULL );
virtual s501* s369( const s269& s736, s501* s612, const std::wstring& s346 ) override;
virtual s501* s370( s501* s612, const std::vector<s277*>& l, const s269* ast_ ) const override;
virtual bool s521( const s501* s522 ) const override;
virtual void* addr() override { return (void*)NULL; }
virtual void s519( s501* s961 ) override;
virtual s277* s349() const override;
virtual void s371( s277* p ) const override;
virtual size_t s330() const;
virtual bool operator==( const s501* p ) const;
virtual bool operator<( const s501* p ) const;
void s683( const std::wstring& s198 );
void s684( const std::wstring& q );
void s754( const std::wstring& s881, const std::wstring& s784 );
void s927( const std::wstring& s930 );
void select( std::wstring& s930, s504 s684, 
s335::mapped_type::iterator& s948, s335::mapped_type::iterator& s949 );
virtual std::wstring to_wstring( uint32_t s1739 = 0 ) const override;
virtual void s310( std::wostream* pd, int s201 = 0 ) const override;
};
extern s1::s9<s679> s807;
} // namespace
namespace transd {
class s821
: public s350{
};
struct s785{
enum s905 { s888=0, s895 };
int distinct;
int	s973;
std::wstring s972;
int s952;
s785()
: distinct( -1 ), s973( -1 ), s952( -1 )
{	}
};
class s984
: public s615{
size_t s995;
s504 s717;
public:
s984() : s615( NULL, NULL, NULL, s588, L"", NULL ), 
s717( new s375( NULL, false ) ){ }
void s994( size_t idx ) { s995 = idx; }
virtual s504 s516( s501** s740, size_t s517 ) override{
s503 l = s280[0];
s503 r = s280[1];
*s717.s15<s375*>()->s372() = l.s15<s793*>()->operator[]( s995 ).s15<s501*>()->
operator<( r.s15<s793*>()->operator[]( s995 ).s15<s501*>() );
s504 s992 = s717;
return s992;}
};
class s323;
class s841
: public s615{
s503 db;
s507 verb;
s503 what;
s503 where;
s503 s975;
s503 s1182;
s503 s952;
s1::s9<s323> s791;
s785 s862;
s386 s773;
s505 s832;
public:
enum s1265{ s1378, s1361, s1362, s1383, s1367, s1379, s1363, s1366,	s1377 };
s841( s268* s306, s501* s612, s615* s611, const std::vector<s277*>& l, const s269* s736 );
virtual const std::wstring& s305() const override { return s874; }
virtual void s519( const std::wstring& s346, bool proc ) override;
virtual s504 s516( s501** s280, size_t s517 ) override;
virtual s277* s349() const override;
};
void evaluateExpression( const std::wstring& s78 );
HPROG createAssembly();
void loadProgram( HPROG handle, const std::wstring& s193 );
void s215( HPROG handle, s6::s146& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s723 );
void* callFunc( HPROG handle, const std::wstring& s78, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s625 );
void* s228( HPROG handle, const std::wstring& s284 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1229, const std::wstring& symName,
const std::wstring& s346 );
void importFile( HPROG handle, const std::wstring& s1229, const std::wstring& s44,
const std::wstring& s346 );
HPROG initShell( const std::wstring& s1229, const std::wstring& modText );
typedef s2::s16 TransDException;
} // namespace transd
