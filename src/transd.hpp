
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
class s1273{
int refs;
public:
s1273(){
refs=0;}
~s1273(){}
void reset(){
refs = 0;}
int s11(){
refs++;
return refs;}
int s12(){
refs--;
return refs;}
int s1274(){
return refs;}
};
#ifdef s1280
#define s1281(x) x;
#else
#define s1281(x)
#endif
template<bool>
struct s1275{
void s1276(){}
void s1277(){}
};
template<>
struct s1275<true>{
#ifdef s1280
static int s163;
void s1276() { s163++; }
void s1277() { s163--; }
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
int s1274(){
return refs;}
virtual void deallocate(){
delete this;}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template<class C, bool s1308=false>
class s1279
: public s1275<s1308>{
C* p;
s1273*	s1278;
public:
s1279(C *_p)
:p(_p){
if ( p ) {
s1278 = new s1273;
s1278->s11();
s1281( this->s1276() )}}
s1279( const s1279& ptr ){
if ( ptr.p ) {
p = ptr.p;
s1278 = ptr.s1278;
s1278->s11();}
else {
p = nullptr;
s1278 = nullptr;}}
s1279()
:p(nullptr){
s1278 = nullptr;}
template<class D> 
s1279( s1279<D> &pn ){
p = nullptr;
s1278 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1278 = pn.s1295();
s1278->s11();}}}
~s1279(){
if(	p && !s1278->s12()	) {
delete p;
delete s1278;
s1281( this->s1277() )}}
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1279& operator=( s1279<C> &s1336 ){
if ( p  && !s1278->s12() ) {
delete p;
delete s1278;
p = nullptr;
s1278 = nullptr;
s1281( this->s1277() )}
p = s1336.p;
if ( s1336.p ) {
s1278 = s1336.s1278;
s1278->s11();}
return *this;}
s1279& operator=( const s1279<C> &s1336 ){ return operator=((s1279<C>&) s1336); }
s1279& operator=( C* ptr ){
if ( p  && !s1278->s12() ) {
delete p;
delete s1278;
p = nullptr;
s1278 = nullptr;
s1281( this->s1277() )}
p = ptr;
if ( ptr ) {
s1278 = new s1273;
s1278->s11();
s1281( this->s1276() )}
return *this;}
template<class Base>
operator Base*(){
return checked_cast<C, Base>( p );}
template<class D>
s1279& operator=( s1279<D> &p_ ){
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );}
template<class ToType>
ToType s15(){
return static_cast<ToType>( p );}
template<class ToType>
ToType dcast(){
return dynamic_cast<ToType>( p );}
bool operator ==(const s1279<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1279<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1273* s1295() { return s1278; }
int s1274() { return s1278->s1274(); }
void s1330() { s1278->s11(); }
void s1329() {
if ( p  && !s1278->s12() ) {
delete p;
delete s1278;
p = nullptr;
s1278 = nullptr;
s1281( this->s1277() )}}
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
bool operator ==( const C& s347 )const { return ( *p == s347 ); }
bool operator !=( const C& s347 )const { return ( *p != s347 ); }
bool operator <( const C& s347 )const { return ( *p < s347 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1112();
extern std::vector<std::wstring> s989;
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
s869,
s25
};
s16( const std::wstring& s, uint32_t n = (uint32_t)s17::s19 )
: id( n ){
s26.push_back( s );}
s16( uint32_t n )
: id( n ){
s26.push_back( s989[n] );}
s16( const s16& right )
: id( right.id ){
s26.assign( right.s26.begin(), right.s26.end() );}
static void s29(){
s27 = (uint32_t)s17::s25 + 1;}
static uint32_t s28(){
return s27++;}
virtual std::wstring Msg( size_t s197 = 0 ) const{
std::wstring s681;
std::list<std::wstring>::const_reverse_iterator it = s26.crbegin();
std::wstring s1071( s197, L' ' );
while( it != s26.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s26.crend() )
s681 += s1071;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s681 += ( i++ ? L"" : s1071 ) + s + L"\n";}
return s681;}
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
bool s31( const std::wstring& _dir, const std::wstring& s522, std::wstring& s153 );
void s32( const std::wstring& _dir, const std::wstring& s522, std::vector<std::wstring>& s40,
std::vector<std::wstring>& s41 );
time_t s33( const std::wstring& f );
uint8_t s34( const std::wstring& f );
bool s718( const std::wstring& f );
bool s35( const std::wstring& s210 );
bool s36( const std::wstring& s210 );
std::wstring s37();
std::wstring s38();
std::wstring s39();
std::wstring s1869();
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
size_t& start, size_t& end, bool s880 = false );
void s55( const std::wstring& s, size_t s65, wchar_t c, size_t& start, 
size_t& end );
void s994( const std::wstring& s, size_t& s65, const std::wstring& s1083 );
void s1317( const std::wstring& s, size_t& s65, const std::wstring& s1083 );
size_t count( const std::wstring& s77, const std::wstring& s1083, size_t start, size_t end,
bool s880 = false );
int s56( const std::wstring& s77, wchar_t s72, size_t& pos );
void s57( const std::wstring& s, const std::wstring& s72, 
std::vector<std::wstring>& s153, bool clr = true, bool s880 = false );
void s289( const std::vector<std::wstring>& v, const std::wstring& s72, std::wstring& s153 );
std::wstring s71( const std::wstring& s77, size_t& pos );
void s58( const std::wstring& s77, const std::wstring& s72, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s59( const std::wstring& s77, const std::wstring& s72,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s60( const std::wstring& s77 );
void s61( std::wstring& s46 );
std::wstring s740( std::wstring path );
bool s62( const wchar_t *str, long *s347, wchar_t **end = NULL );
bool s1533( const wchar_t *str, long long *s347, wchar_t **end = NULL );
bool s1534( const wchar_t *str, unsigned long long *s347, wchar_t **end = NULL );
bool s63( const wchar_t *str, double *s347, wchar_t **end = NULL );
void s871( const std::wstring& s77, std::vector<std::wstring>& s153 );
std::wstring s1814( const std::wstring& s77, wchar_t c );
std::wstring s1243( const std::wstring& s, const std::wstring& chars );
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
constexpr UINT rol(UINT s347, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s347 << n) | (s347 >> (sizeof(UINT)*8-n));}
void s64( const std::wstring& s78 );
void s81( std::wstring& s77, std::vector<std::wstring>& s1095, std::map<size_t, size_t>& s1030 );
template<class T>
std::wstring s1552( T value ) {
struct Numpunct : public std::numpunct<wchar_t> {
protected:
virtual wchar_t do_thousands_sep() const { return L','; }
virtual std::string do_grouping() const { return "\03"; }
};
std::wstringstream ss;
ss.imbue( { std::locale(), new Numpunct } );
ss << std::setprecision( 2 ) << std::fixed << value;
return ss.str();}
std::wstring s2170( void* );
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
#define s1549(x) s5::conv.to_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#define s1549(x) x
#endif
namespace consutils {
void s1108();
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
#define s1546 371
#define s1545 379
} // namespace consutils
namespace s6{
enum s131{ s132, s133, s134, s139, 
s135, s136, s140, s137, s138 };
class s141;
class s143;
typedef s1::s9<s141> s142;
struct s1681{
bool s151;
std::wstring s1682;
std::wstring s1683;
bool s1686;
bool s1685;
bool s1687;
bool s1730;
bool s1718;
s1681( const std::wstring& dd=L".", const std::wstring& fs=L",", bool ab=false, bool rb=false,
bool sb=false )
: s151( true ), s1682(dd), s1683(fs), s1686(ab), s1685(rb),
s1687(sb), s1730( true ), s1718( false ) { }
};
extern s1681 s1743;
extern thread_local std::list<bool> s1755;
void s1684( const std::wstring& dd, const std::wstring& fs, bool ab, bool rb, bool sb );
void s1684( const s1681& cnf );
class s938
: public s1::s10{
std::wstring s194;
std::wstring s1105;
std::vector<std::wstring> s1106;
std::map<size_t, size_t> s1107;
size_t s1052;
public:
s1681 s1746;
s938( const std::wstring& file, bool s194 = true, const s1681& s1745=s1743 );
const std::wstring& Path() const { return s194;  }
void read( std::vector<s1::s9<s143>>& s153, 
const std::wstring& s190 = std::wstring(L"") );
void s170( const std::wstring& s77, size_t& pos, s1::s9<s143> s153 );
bool s998( std::wstring& s, size_t s68, size_t s679, size_t& line ) const;
size_t s942() const { return s1052; }
};
typedef s1::s9<s938> s941;
class s143
: public s1::s10{
std::multimap<std::wstring, s142> s144;
s941 src;
public:
enum s145 { s146, s147, s148 };
enum s17 { s18, s149 };
const static s141 s150; // similar to string::npos
s143( const s938* pf ):src( (s938*)pf){}
void s154( const std::wstring& s77, const s1681& s1745 );
void s155( std::wostream* pd, bool s151=false ) const;
bool s156( const std::wstring& s152 ) const;
void s157( const std::wstring& s152, std::vector<s142>& s153 ) const;
const s142 s158( const std::wstring& s152 ) const;
void s159( const std::wstring& s76, s142 s347, s145 ap=s146 );
void s1619( const std::wstring& s76 );
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
std::pair<size_t, size_t> s1075;
s941 s1074;
public:
s141():s198(s132),obj(NULL){}
s141( const std::wstring& s ):s198(s134),obj(NULL),str(s){}
s141( double d, s131 v = s136 );
s141( const std::vector<s142>& a ): s198(s135),obj(NULL),s162(a){}
s141( const s938* pf, const std::wstring& s77, size_t& pos, const s1681& s1745 );
s131 s164() const { return s198; }
bool s165() const { return s198 == s132; }
const s143& s166() const;
const std::vector<s142>& s167() const;
double s168() const;
int s56() const;
bool s722() const;
const std::wstring& s169() const;
const std::wstring& s859() const;
std::wstring s851() const;
bool s1002( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s938* s999() const { return s1074.s15<s938*>(); }
bool operator==( const s141& r ) const{
return s198 == r.s198 && obj == r.obj && str == r.str && s162 == r.s162 && b == r.b && s163 == r.s163;}
bool is( const s141& r ) const{
return this == &r;}
void s161( std::wostream* pd, int s197 ) const;
void s155( std::wostream* pd, bool s151=false ) const;
};
class s1695{
s1681 conf;
public:
s1695() { }
s1695( const s1681& _cnf )
: conf( _cnf ) {}
s131 s1539( const std::wstring& s77, size_t& pos, double& s153 );
void s178( const s938* pf, const std::wstring& s77, size_t& pos, 
std::vector<s1::s9<s141>>& s153,
bool s151 = false, const std::wstring& s72 = L",");
};
void s171( const std::wstring& s194, 
const std::vector<s1::s9<s143>>& s195 );
void s178( const s938* pf, const std::wstring& s77, size_t& pos,
std::vector<s1::s9<s141>>& s153, const s1681& s1745 );
void s178( const s938* pf, const std::wstring& s77,
std::vector<s1::s9<s141>>& s153, const s1681& s1745 );
} // namespace s6
typedef const std::wstring s1890;
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s922 extern const uint32_t
#define s1676    1
#define s1677 2
#define s1678 3
#define s1679 4
#define s1680 5
namespace transd {
typedef uint32_t s1054;
typedef uint32_t traitnum_t;
typedef unsigned char tdbyte_t;
typedef std::basic_string<tdbyte_t> s1312;
namespace s7 {
s922 s1542;
s922 s1384;
s922 s1385;
s922 s1386;
s922 s1383;
s922 s1382;
s922 s1387;
s922 s1388;
DEFCONST s418;
DEFCONST s419;
DEFCONST s420;
DEFCONST s421;
DEFCONST s422;
DEFCONST s423;
DEFCONST s424;
DEFCONST s425;
DEFCONST s426;
DEFCONST s427;
DEFCONST s1617;
DEFCONST s428;
DEFCONST s429;
DEFCONST s430;
DEFCONST s827;
DEFCONST s431;
DEFCONST s432;
DEFCONST s433;
DEFCONST s759;
DEFCONST s743;
DEFCONST s789;
DEFCONST s434;
DEFCONST s435;
DEFCONST s826;
DEFCONST s934;
DEFCONST s1131;
DEFCONST s1346;
DEFCONST s1380;
DEFCONST s1381;
DEFCONST s1589;
DEFCONST s2124;
DEFCONSTI s860;
DEFCONSTI s2219;
DEFCONSTI s2265;
DEFCONSTI s436;
DEFCONSTI s437;
DEFCONSTI s438;
DEFCONSTI s439;
DEFCONSTI s440;
DEFCONSTI s861;
DEFCONSTI s862;
DEFCONSTI s1733;
DEFCONSTI s1190;
DEFCONST s1402;
DEFCONST s1513;
DEFCONST s1400;
DEFCONST s1399;
DEFCONST s1401;
DEFCONST s1398;
DEFCONST s1403;
DEFCONST s1397;
DEFCONST s441;
DEFCONST s442;
DEFCONST s443;
DEFCONST s444;
DEFCONST s445;
DEFCONST s446;
DEFCONST s447;
DEFCONST s448;
DEFCONST s449;
DEFCONST s450;
DEFCONST s2146;
DEFCONST s451;
DEFCONST s452;
DEFCONST s453;
DEFCONST s454;
DEFCONST s2152;
DEFCONST s455;
DEFCONST s457;
DEFCONST s456;
DEFCONST s458;
DEFCONST s459;
DEFCONST s460;
DEFCONST s1363;
DEFCONST s1967;
DEFCONST s763;
DEFCONST s797;
DEFCONST s1560;
DEFCONST s823;
DEFCONST s1115;
DEFCONST s1362;
DEFCONST s461;
DEFCONST s462;
DEFCONST s463;
DEFCONST s464;
DEFCONST s465;
DEFCONST s466;
DEFCONST s467;
DEFCONST s733;
DEFCONST s468;
DEFCONST s930;
DEFCONST s1968;
DEFCONST s2145;
DEFCONST s1974;
DEFCONST s1975;
DEFCONST s1976;
DEFCONST s1977;
DEFCONST s1973;
DEFCONST s1978;
DEFCONST s1979;
DEFCONST s1982;
DEFCONST s1981;
DEFCONST s1980;
DEFCONST s909;
DEFCONST s908;
DEFCONST s910;
#define s417 3
#define s1109 L','
DEFCONST s416;
DEFCONST s1097;
#define s1547 1
#define s1548	2
s922 s1290;
s922 s918;
s922 s917;
s922 s1289;
s922 s1120;
s922 s912;
s922 s1098;
s922 s913;
s922 s1099;
s922 s1100;
s922 s1101;
s922 s914;
s922 s915;
s922 s916;
s922 s1117;
s922 s1118;
s922 s1355;
s922 s1356;
s922 s1357;
s922 s1585;
s922 s1119;
s922 s1286;
s922 s1288;
s922 s1287;
s922 s1653;
s922 s1654;
s922 s1367;
s922 s2276;
s922 s1655;
s922 s1365;
s922 s1366;
s922 s1656;
s922 s1511;
s922 s1512;
s922 s1543;
s922 s1673;
s922 s1587;
s922 s1889;
s922 CLObjectVal_ctor1;
s922 s1586;
s922 s1674;
s922 s1688;
s922 s1877;
s922 s1922;
s922 s1921;
s922 s2144;
s922 s2275;
s922 CLTDFilter_ctor1;
s922 s2191;
s922 s2201;
s922 s2202;
s922 s2200;
s922 s2235;
s922 s2234;
extern std::set<std::wstring> s1114;
} // namespace s7
enum s224 { s225, s226, s227, s228 };
extern std::wstring s229[];
extern const std::wstring s249, s1416, s243, s1417,	s258,
s245, s246, s1602, s236, s235, 
s237,	s894, s256, 
s2194, s2063, s260, s239, s241,
s230, s815,
s252, s238, s240, s1928, s766, s1603, s1550, 
s247, s234, s242, s244, s1929, 
s1871, s1604, s1605, s846, s261,
s231, s1606, s1607, s753, s232,
s1930, s251, s257, s812,
s255, s233,
s2214,
s745, 
s250,   s253,			s254,
s259,
s847,  s1307, s1608, 
s1306;
#define s2086		1
#define s2085		2
#define s2087		3
#define s2174  4
#define s2279    5
class s262;
class s263;
class s270;
class s271;
class s272;
typedef s270* ( *s273 )( const std::wstring& s278, const std::vector<s271*>& s274 );
typedef s1::s9<s263> s940;
extern const s6::s141 s265;
class s263
: public s1::s10{
public:
typedef std::multimap<std::wstring, s940> s275;
typedef std::map<size_t, s6::s141> s264;
private:
static std::map<std::wstring, s273> s276;
std::wstring s277;
std::wstring s1660;
s224 s279;
std::wstring s280;
s275 s281;
std::wstring src;
s6::s142 s1046;
s264 s266;
s1054 s1340{};
s263* s2092;
s263* s2097;
void s282( s1890& s77 );
void s283( const s6::s143& s133 );
void s284( s1890& s77 );
void s285( s1890& s77 );
void s286( s1890& s338, const s6::s141& obj );
void s996( s1890& s );
static std::wstring s287( s1890& s77, size_t &pos );
public:
enum s17 { s18, s149 };
s263(){ }
s263( s224 at, s1890& qpre, s1890& s76 )
: s277( qpre ), s1660( s76 ), s279( at ), s2092( NULL ), s2097( NULL ){ }
s263( s1890& s76, s1890& s347 )
: s1660( s76 ), s279( s225 ), s280( s347 ), s2092( NULL ), s2097( NULL ){ }
s263( s1890& s338, const s6::s141* s1046, s263* s2093 );
s263( s1890& s76, const s6::s141& s296, s263* s590 );
s263( const s6::s143& s133 );
~s263();
s224 s297() const { return s279; }
void s1857( s224 t ) { s279 = t; }
std::wstring s298() const;
s1890& s299() const { return s1660; }
s1890& Src() const { return src; }
const s6::s141* Nqj() const { return s1046.s15<s6::s141*>(); }
s263* s2083() { return s2092; }
s263* s2084() { return s2097; }
const s6::s141& s268( size_t s2091 ) const;
const s6::s141& s2101( size_t s2091 ) const;
void s269( size_t s2091, const s6::s141& s267 );
void s2108( const s263& s695 );
s1054 s1299() const { return s1340; }
void s1334( s1054 t) { s1340 = t; }
void reset();
static void s288( s1890& s77, size_t& pos, std::vector<std::wstring>& s153 );
void s289( s6::s143& s133, size_t s2177 );
void s286( s263* node );
void s290( s262* s300, size_t s301 = 0 );
s1890& s291() const { return s280; }
const s263* s292( s1890& s278 ) const;
bool s156( s1890& s278 ) const;
s275& s293() { return s281; }
const s275& s293() const { return s281; }
void s294( s1890& s ) { s1660 = s; }
void s1754( s1890& s ) { s280 = s; }
static std::wstring s295( const s6::s143& obj,
s1890& dfault = std::wstring( L"" ) );
static std::wstring s302( const s6::s143& obj,
s1890& s303,	s1890& dfault = std::wstring( L"" ) );
void s2268( const std::pair<std::wstring, std::wstring>& pr );
void s304( std::wostream* pd, int s197 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s937{ s1036, s1035, s1037, s1038, s1034 };
class Msg{
std::wstring func;
std::wstring file;
s937 type;
std::wstring s78;
public:	
Msg( const std::wstring& s, s937 t = s1034 )
: type( t ), s78( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s937 t = s1034 )
: func( f ), file( fi ), /*line( n ),*/ type( t ), s78( s ) {}
s937 s350() const { return type; }
const std::wstring& Text() const { return s78; }
};}
namespace transd {
class s1096{
std::vector<s8::Msg> s26;
size_t s990;
public:
s1096() : s990(0){}
void s964( const std::wstring& s78 );
void s964( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
void s966( const std::wstring& s78, const std::string& func, 
const std::string& file, uint32_t line );
size_t s928() const { return s990; }
};
extern s1096 s1007;
extern std::vector<std::wstring> s1078;
extern std::vector<std::wstring> s987;
class TDException;
class TDException
: public s2::s16{
public:
enum class Stage : uint32_t{
s1024 = 0,
s1017,
s1022,
s1021,
s1016,
s1018,
s1019,
s1020,
s1023
};
private:
Stage stage;
uint32_t category;
std::wstring s1080;
s940 s695;
public:
TDException( uint32_t cat, uint32_t id, const s263* s695 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s263* s695, const s16& e );
TDException( uint32_t cat, uint32_t id, const s263* s695, s1890& s78, Stage stg = Stage::s1024 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s197 = 0 ) const override;
std::wstring s2153( size_t idx ) const;
uint32_t Category() const { return category;  }
void s1069( Stage st ) { stage = st; }
void s2288( s263* p ) { s695 = p; }
TDException* s993( const std::wstring& s = std::wstring( L"" ) );
static std::wstring s1897( const s263& s695 );
};
class s921
: public s2::s16{
public:
enum class s17 : uint32_t{
s976 = ((uint32_t)s16::s17::s25) + 1,
s1060,
s1043,
s967,
s977,
s1009,
s1012,
s25
};
s921( const std::wstring& s )
: s16( s, (uint32_t)s17::s976){}
s921( s16& e, const s263& s695, s17 code );
};
class s929
: public s2::s16{
public:
enum class s17 : uint32_t{
s1042 = ( (uint32_t)s16::s17::s25 ) + 1,
s992,
s25
};
s929( s17 code );
s929( const std::wstring& s, s17 code )
: s16( s, (uint32_t)code ) {}
};
#define s926		1
#define s925		2
#define s927						3
#define s923					4
#define s924				5
#define s1123		6
#define s1122		7
#define s1368		8
#define s1544	9
#define s1657			10
#define s946(x) throw s947( L"unknown syntax: " + x );
#define s945(x) throw s947( L"syntax error: " + x );
namespace lang {
bool s654( const std::wstring& s, bool s708 = true );
} // namespace tdlang
extern const std::wstring s469;
enum s470 { s471, s472, s473, s1327, s474, s1235, s1236, 
s475, s476, s477, s478, s479, s1056, s2150 };
enum s1984 { s2032 = 0, s2033, s2031, s2030 };
enum s1983 { s2039 = 0, s2035, s2036, s2037, s2038 };
enum s2176 { s2187, s2183, s2186, s2188, s2184, s2185 };
#define s1969 5
class s262;
class s480;
class s481;
class s272;
class s589;
class s271;
class s559;
class Stream;
typedef s271 s482;
typedef s271 TDType;
typedef s1::s9<s482> s483;
typedef s1::s9<s481> s484;
typedef s1::s9<s272> s485;
typedef s1::s9<s589> s486;
class s807;
typedef std::map<std::wstring, std::vector<std::wstring>> s920;
extern s920 s986;
class s271
: public s1::s10{
friend class s489;
s940 s969;
protected:
s470 s490;
s1054 s491;
s262* s300;
int wh;
public:
s271( const s263* ast_=NULL ) : s969( (s263*)ast_ ), s490( s471 ), s491( 0 ), 
wh( s7::s862 )  { }
s271( s470 pt_, const s263* ast_=NULL ) : s969( (s263*)ast_ ), s490( pt_ ), s491( 0 ), 
wh( s7::s862 ) { }
s271( s262* pass_, s470 pt_, const s263* ast_=NULL ) : s969( (s263*)ast_ ), s490( pt_ ),
s491( 0 ), s300( pass_ ), wh( s7::s862 )  { }
s271( const s271& r ) : s969( r.s969 ), s490( r.s490 ), s491( r.s491 ),
s300( r.s300 ), wh( r.wh ) {}
virtual ~s271();
s470 s492() const { return s490; }
const s263* s601() const { return s969.s15<s263*>(); }
virtual s481* s494();
virtual s484 s495( s481** s274 = NULL, size_t s496 = 0 );
virtual s1054 s350() const { return s491; }
const s807& s1187() const;
virtual const std::wstring& s351() const;
virtual void s349( s1054 type );
s262* Pass() const  { return s300; }
int s616() const { return wh; }
void s1665( int i ) { wh = i; }
void s1252() { wh = 0; }
void s1250(bool b = true) { if(b) wh |= (1 << (s7::s1190-1)); 
else wh &= ~(1 << (s7::s1190-1));}
bool s1195() const { return wh >= 0 && wh < s7::s862; }
virtual bool s1194() const { return (wh > 0) && (wh & (1 << (s7::s1190-1))); }
virtual void s2181( s2176 st ) { }
virtual bool s499( const s481* s500 ) const;
virtual bool s1530( s1054 tp ) const;
virtual const s920& s997() const { return s986;  }
virtual void s498( const s272* s873, bool b = true );
virtual void release() {}
virtual const s481* s501() const;
virtual s271* s333( s589* s2042, s272* impl ) const;
virtual void s2118( s589* s2042, s272* impl, bool s2159 = true ) { }
static void s1323( const s263& ast_, s262* s300, s272* obj,
s1890& s332, std::vector<s271*>& s153 );
static s271* s502( const s263& s695, s262* s300, s272* obj,
s1890& s332, bool s2159 = false );
static s271* s1011( s262* s300, s271* par, s272* obj, s589* s215,
s1890& s332, bool proc );
static s483 s1010( const std::wstring& s77, const s263* ast_, s262* s300, 
s272* s586 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring( uint32_t s1553 = 0 ) const;
virtual s1312 to_bytes() const;
virtual void to_null();
virtual std::wstring trace( s1890& topics ) const { return L""; }
virtual void s304( std::wostream* pd, int s197 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s482*> s503;
s482* s1111( s503& m, const std::wstring& s152 );
void s666( const std::wstring& s, std::wstring& s1103, std::wstring& s599 );
class s481;
class s369;
class s481
: public s271{
protected:
s272* ns;
s481* s1689( s481** s274, size_t s496 );
s481* s1879( s481** s274, size_t s496 );
s481* s1923( s481** s274, size_t s496 );
s481* s2277( s481** s274, size_t s496 );
s481* s2278( s481** s274, size_t s496 );
virtual s481* s1881( s481** s274, size_t s496 );
public:
s481( s262* s300, s470 pc, const s263* ast_, s272* ns_ ) 
: s271( s300, pc, ast_ ), ns( ns_ ) { }
s481( const s481& r );
virtual ~s481();
virtual void s348() = 0;
virtual s1054 s384( const std::wstring& s341 ) const = 0;
virtual s481* s352( const s263& s695, s272* s586, s1890& s332 ) const = 0;
virtual s481* s353( s272* s586, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const = 0;
virtual s481* s353( s272* s586, const std::vector<s1054>& vt ) const;
virtual std::wstring s298() const;
virtual std::wstring s828() const;
std::wstring s2154() const;
virtual s481* s342( s1890& s278, s1890& s332,	bool s518 = true, bool s2151 = true ) const 
{	return NULL;}
virtual s589* s1671( s1890& s278, s589* s215,	s272* s586, s559* cs ) const;
virtual void s354( s271* p ) const = 0;
virtual s481* s1525( const s481* p ) const;
virtual const s481* s501() const override = 0;
void s504( s1890& s ) { /*s370 = s;*/ }
std::wstring s1659() { return L""; }// s370;}
virtual size_t s320() const = 0;
virtual bool operator==( const s481* p ) const = 0;
virtual bool operator<( const s481* p ) const = 0;
s481* s1880( s481** s274, size_t s496 );
s272* s2293() { return ns; }
void s2118( s589* s2042, s272* impl, bool s2159 = true ) override { ns = impl; }
s484 s495( s481** s274, size_t s496 ) override { return this; }
s481* s494() override;
virtual bool s554( s1890& s278, s369* s153, s1890& s332, bool fr ) const	{	return false;	};
virtual s271* s596( size_t off )	{	return NULL; }
virtual s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const;
virtual void s1920( Stream* ) const;
virtual void s1944( Stream* );
virtual void s1945( s1890& s );
};
enum s534 { s507, s508, s509 };
enum s510 { s511, s512, s513 };
typedef s1::s9<s807> s820;
typedef const s807* s919;
class s807
: public s1::s10{
public:
typedef s1054 s731;
typedef s731 s887;
typedef std::vector<s731> Cont;
private:
Cont vt;
size_t s1086;
public:
s807() {}
s807( s731 t1, s731 t2 = (s731)-1, s731 t3 = (s731)-1 );
s807( const s807& right );
s807( const Cont& v );
void s349( s731 t );
void s349( s919 pt );
void s779( s731 t );
void s779( s919 pt );
s887 s350( size_t n = 0 ) const;
const Cont& s813() const { return vt; }
void s813( std::vector<s271*>& s153 ) const;
bool operator==( const s807& p ) const;
size_t s320() const { return s1086; }
};
class s480;
class s262;
struct s958{
std::size_t operator()( const s807& k ) const{
return k.s320();}
};
struct s959{
std::size_t operator()( const s807& l, const s807& r ) const{
return l.operator==( r );}
};
class s489{
typedef std::map<std::wstring, s1054> s953;
typedef std::unordered_map<s807, s1054, s958, s959> s956;
typedef std::map<std::wstring, std::list<std::wstring>> s1776;
typedef std::map<std::wstring, std::set<std::wstring>> s907;
typedef std::map<s807::s887, s907> s920;
typedef std::map<std::wstring, traitnum_t> s1145;
typedef std::unordered_map<traitnum_t, std::wstring> s1238;
std::vector<s484> s1104;
std::vector<std::wstring> s1087;
std::vector<s807> s1092;
s953 s1088;
s956 s1093;
s1776 s1827;
s920 s911;
s1145 s886;
s1238 s1249;
traitnum_t s1196;
std::vector<traitnum_t>s1264;
std::vector<s1054>s1500;
std::vector<std::vector<s1054>> s1540;
s262* s300;
s1054 s1061( const s807::Cont& v, s1890& s345 );
void s1162( s1890& alias, s1890& s345, s1890& s1826 );
public:
s489( s262* pass_ );
void reset();
void s290();
void s515( const s480& st );
s1054 s218( s481* p, s1890& s345 );
void s1652( s1890& s345 );
void s1863( s1890& s1103 );
s1054 s1039( const s807::Cont& v );
traitnum_t s1242( s1890& trait, s1054& s1499 );
void s1153( s807::s887 type, s1890& trait, s1054& s1499 );
bool s1189( s1054 s617, traitnum_t tra );
bool s1454( s1054 s617, s1054 alias );
traitnum_t s1146( s1054 s617 ) const { return s1264[s617]; }
traitnum_t s1447( s1054 alias ) const;
void s1522( s1054 s617, s1054 is );
bool s1523( s1054 s617, s1054 is );
bool s1523( const s271* s617, const s271* is );
s481* s516( const s6::s141& s347, s272* s586, s1890& s517 );
s481* s516( const s263& s695, s272* s586, s1890& s517 );
s481* s516( s1054 type, s272* s586, s1890& s517 );
const s481* get( s1890& s76, bool s518 = true ) const;
s1054 s1003( s1890& s345, bool s518=true ) const;
s1054 s1004( const s807& vt, bool s518=true ) const;
const s807& s1006( s1054 t ) const;
const s481* s1000( s807::s887 t ) const;
s1890& s798( s1054 n ) const;
bool s156( s1890& s76 ) const;
void s784();
bool s1239();
double s1241();
int s1247();
void s304( std::wostream* pd, int s197 = 0 ) const;
static void s2104( const s807::Cont& v, size_t& idx, s807::Cont& s153 );
static void s1001( const s807::Cont& v, std::vector<size_t>& s2119,
s807::Cont& s153 );
size_t s1049( s1890& s, size_t& pos, s807::Cont& s153 );
std::wstring s1005( const s807::Cont& tp );
static std::wstring s1342( s1890& tn );
std::wstring s1265( s1890& tn, s1890& s1103 );
void s2122( const s807::Cont& v_, s807::Cont& s153, size_t s2102 = 0 );
};
class s519
: public s1::s10{
std::vector<std::wstring> s520;
s510 pv;
public:
s519() : pv( s511 ) { }
s519( s510 pv, const std::vector<std::wstring>& s521 );
s519( s1890& ag, s1890& s77 );
s510 s558( s1890& s497 ) const;
static std::vector<std::wstring> s523;
};
class s524
: public s1::s10{
typedef std::map<std::wstring, s519*> s525;
s525 s526;
public:
s524( ) { }
void s527( s510 pv, s263* );
void s528( s1890& s, s519& pl );
void s529( s1890& s, s1890& s522 );
s510 s530( s1890& mem, s1890& s497 );
void s531( s1890& s332,
std::vector<std::wstring>& s153 );
};
class s480{
public:
enum s145 { s146, s532, s147, s148 };
typedef std::map<std::wstring, s483> s533;
private:
s533 s551;
s534 s535;
s524* s537;
bool s536( s1890& s76, s145 ap = s146 );
public:
s480( ): s535( s508 ), s537( NULL ) {}
s480( s534 am ) : s535( am ), s537( NULL ) {}
s480( const s480& s538 );
~s480();
const s533& Table() const { return s551; }
void s498( s272* s497, s272* s586, bool s514 = true );
void s1637();
void reset();
size_t s320() const;
bool compare( const s533& r ) const;
void s539( s1890& s76, s271* sym, s145 ap = s146 );
void s539( s1890& s76, s6::s142 s347, s145 ap = s146 );
void s540( s1890& s76 );
void s541( const s6::s143& obj, s145 ap = s146 );
void s289( const s480& t, s145 ap = s146 );
bool empty() const { return s551.empty(); }
bool s156( s1890& s76 ) const;
s481* get( s1890& s76, bool s518 = true ) const;
void s542( std::vector<std::wstring>& s153 ) const;
void s543( std::vector<std::wstring>& s153 ) const;
void s544( std::vector<std::wstring>& s153 ) const;
void s545( const s480& t, std::vector<std::wstring>& s153 ) const;
bool implements( const s480& t ) const;
void copy( s480& t, s272* s586, s589* s585, s145 ap = s146 ) const;
void s546( s480& t ) const;
void s1601( s480& t ) const;
void s547( s510 pv, s263* s79 );
void s531( s1890& s332,
std::vector<std::wstring>& s153 );
bool s548( s1890& s278, s1890& s332 ) const;
std::wstring to_wstring( uint32_t s1553 ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
class s549{
typedef std::pair<s481*, std::wstring> s550;
typedef std::multimap<std::wstring, s550> s533;
s533 s551;
std::vector<std::wstring> s557;
std::wstring s332;
public:
s549();
void s552( s1890& s76 );
bool s2163( s1890& s76 );
void s498( s262* s300, s1890& s556 );
void s1637( s262* s300 );
void s553( s1890& s76, s262* s300, s1890& s556 );
bool s554( s1890& sym, s369* ref );
void copy( s549& t ) const;
};
extern s1::s9<s524> s555;
class s262;
class s334;
typedef void ( *s614 )( s481** s274, size_t n );
namespace s1501 {
extern s1054 s1261;
extern s1054 s1538;}
class s1113{
s334* s586;
std::vector<s1054> s1268;
std::vector<s483> s906;
public:
s1113() : s586( NULL ) {}
s1113( const std::vector<s483>& v, s334* s590 /*= NULL*/ );
s1113( const std::vector<s1054>& v, s334* s590 = NULL )
: s586( s590 ), s1268( v ) {}
bool operator==( const s1113& s522 ) const;
bool operator<( const s1113& s522 ) const;
const s334* Subj() const { return s586; }
const std::vector<s483>& s600() const { return s906; }
std::wstring s1319( s262* s300 ) const;
};
struct s1985{
s1054
Bool,
Byte,
ByteArray,
ByteStream,
Char,
DateTime,
s412,
Double,
s359,
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
s272,
Position,
Range,
Seq,
Set,
String,
s783,
Table,
TSDBase,
Tuple,
s1517,
s742,
Vector;
s1985() {
Bool = Byte =	ByteArray =	ByteStream = Char =	DateTime = s412 = Double =	s359 =
FileStream = Filter =	HashIndex =	HashSet = Index =	Int =	Lambda = Long =	No = Null = s272 =
Position = Range = Seq = Set = String = s783 = Table = TSDBase = Tuple = s1517 =
s742 =	Vector = 0;}
const s481* operator()( s262* s300, s1054 tp );
};
extern s1985 Types;
struct s1133{
s1054 s336;
s614 s337;
bool s1159;
const std::vector<s1983>* s2020;
s1133()
: s336( 0 ), s337( NULL ), s1159( true ), s2020( NULL ) {}
s1133( s1054 pt, s614 fp, bool s1160 = true, 
const std::vector<s1983>* s1993 = NULL )
: s336( pt ), s337( fp ), 
s1159( s1160 ), s2020( s1993 ) {}
};
class s334
: public s481{
public:
class s335{
std::wstring s278;
s1054 s336;
s614 s337;
std::vector<s1113> s1154;
size_t s1031, s1028;
std::vector<std::wstring> s1200;
bool s1170;
bool s1159;
std::vector<s1983> s2029;
public:
enum class s1124 : uint32_t { s1171 = ((uint32_t)s2::s16::s17::s25) + 1 };
s335( const std::wstring& s672, s614 fp, s1054 s338,
const std::vector<s1113>& v=std::vector<s1113>(), 
size_t s1032 = 0, size_t s1029=(size_t)-1, bool s1160 = true,
const std::vector<std::wstring>& s1199 = std::vector<std::wstring>(),
const std::vector<s1983>& s1994 = { s2039 } )
: s278( s672 ), s336( s338 ), s337( fp ), s1154(v), 
s1031(s1032), s1028(s1029), s1200( s1199 ), s1170(false), 
s1159( s1160 ), s2029( s1994 ) {}
s335( const std::wstring& s672, s614 fp, s1054 s338,
const std::vector<s1113>& v, 
bool s1160, const std::vector<s1983>& s1994 )
: s278( s672 ), s336( s338 ), s337( fp ), s1154(v), 
s1031(0), s1028(0), s1170(false), 
s1159( s1160 ), s2029( s1994 ) {}
s335()
: s337( NULL ), s1170( false ), s1159( true ), s2029( { s2039 } ){}
s614 s1127() const { return s337; }
size_t s936() const { return s1031;  }
size_t s935() const { return s1028;  }
const std::vector<std::wstring>& Markers() const { return s1200; }
s1054 s493() const { return s336; }
void s1253( s1054 t) { s336 = t; }
void s1251( bool b ) { s1170 = b; }
bool s1177( ) const { return s1170; }
bool s1194() const { return s1159; }
const std::vector<s1983>* s2002() const { return &s2029; }
bool s1157( const s1113& s687 ) const;
};
protected:
typedef std::multimap<std::wstring, s335*> s339;
virtual const s339& s340() const = 0;
static size_t s752;
public:
s334( s262* s300, s272* ns_, const s263* ast_ ) : s481( s300, s472, ast_, ns_ ) {}
s334( const s334& r ) : s481( r ) {}
virtual ~s334() {}
s1054 s384( const std::wstring& s341 ) const override;
static void s778( s262* s300, bool soft = false );
static size_t s801() { return s752;  }
virtual const std::vector<std::wstring>& s1182( s1890& s341 ) const;
virtual s1133 s1188( s1890& s341 ) const;
virtual s1133 s1183( s1890& s341, s1113& ap ) const;
virtual s1133 s1178( s1890& s341, s1113& ap );
const s481* s501() const override;
virtual void* addr() = 0;
s484 s495( s481** s274, size_t s496 ) override;
static s481* s343( s262* s300, const std::wstring& s347, const std::wstring& s332 );
void s1524( s481* s42 );
};
class s356
: public s334{
static s339 s346;
double s347;
static void s1227( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s386( s481** s274, size_t n );
static void s387( s481** s274, size_t n );
static void s388( s481** s274, size_t n );
static void s389( s481** s274, size_t n );
static void s390( s481** s274, size_t n );
static void s391( s481** s274, size_t n );
static void s392( s481** s274, size_t n );
static void s393( s481** s274, size_t n );
static void s394( s481** s274, size_t n );
static void s395( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s397( s481** s274, size_t n );
static void s398( s481** s274, size_t n );
static void s399( s481** s274, size_t n );
static void s400( s481** s274, size_t n );
static void s401( s481** s274, size_t n );
static void s408( s481** s274, size_t n );
static void s409( s481** s274, size_t n );
static void s402( s481** s274, size_t n );
static void s404( s481** s274, size_t n );
static void s405( s481** s274, size_t n );
static void s410( s481** s274, size_t n );
static void s2198( s481** s274, size_t n );
static void s2196( s481** s274, size_t n );
static void s407( s481** s274, size_t n );
static void s1963( s481** s274, size_t n );
static void s1962( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef double s1375;
s356( s262* s300 ) : s334( s300, NULL, NULL ) {}
s356( const s356& r );
s356( s262* s300, const std::vector<s271*>& l );
s356( s262* s300, double d );
s356( s262* s300, const std::wstring& s, size_t& pos );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void s498( const s272* s585, bool b = true ) override;	
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
double* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0.0; }
operator int() const override { return (int)s347; }
operator double() const override { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void s1945( s1890& s ) override;
void s1944( Stream* ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s358
: public s334{
static s339 s346;
bool s347;
static void s385( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
static void s411( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
s358( s262* s300 ) : s334( s300, NULL, NULL ) {}
s358( s262* s300, bool b );
s358( s262* s300, const std::wstring& s, size_t& pos );
s358( const s358& right );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
bool* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
void s498( const s272* s585, bool b = true ) override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
operator bool() const override { return s347; }
operator int() const override { return (int)s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void s1945( s1890& s ) override;
void s1944( Stream* ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s358> s367;
extern s1::s9<s358> s368;
class s359
: public s334{
enum s2260 { s2262, s2263 };
static s339 s346;
static void s786( s481** s274, size_t n );
static void s506( s481** s274, size_t n );
static void s2266( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
s2260 s2264;
std::wstring s78;
public:
s359( const s359& right );
s359( s262* s300, const std::wstring& s = std::wstring( L"" ) );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void create( const std::vector<s483>& l );
s1890& Msg() const { return s78; }
void s361( const std::wstring& s ) { s78 = s; }
void* addr() override { return (void*)0; }
void s498( const s272* s585, bool b = true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override { return s78; }
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s362
: public s334{
static s339 s346;
void s348() override {}
const s339& s340() const override { return s346; }
public:
s362( s262* s300, s272* s586 = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override { }
void s498( const s272* s585, bool b = true ) override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override {	return L"";	}
operator double() const override { return (double)0; }
operator int() const override { return 0; }
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s362> s363;
class s382
: public s334{
traitnum_t s1262;
static s339 s346;
void s348() override {}
const s339& s340() const override { return s346; }
public:
s382( s262* s300, s272* ns = NULL, traitnum_t tn = 0, s470 pc = s471 );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
s271* s333( s589* s2042, s272* impl ) const override;
bool s499( const s481* s500 ) const override;
bool s1530( s1054 tp ) const override;
traitnum_t s1529() const { return s1262; }
void* addr() override { return (void*)0; }
void s354( s271* p ) const override { }
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s498( const s272* s585, bool b = true ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1692
: public s334{
public:
enum s1691 { s1727, s1726, s1725, s1728, s1809 };
typedef std::chrono::steady_clock s1780;
typedef std::chrono::system_clock s1781;
private:
static s339 s346;
void s348() override;
const s339& s340() const override { return s346; }
static void s385( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
static void s411( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s1835( s481** s274, size_t n );
static void s1858( s481** s274, size_t n );
s1691 s1729;
std::tm s347;
s1781::time_point s1860;
static std::wregex s1751, s1753, s1752, s1849;
bool s1714( const std::wstring& s347, std::tm& t, s1691& s617 ) const;
public:
s1692( s262* s300 );
s1692( s262* s300, const std::wstring& s );
s1692( s262* s300, const std::tm& _t, s1691 s617 );
s1692( const s1692& right );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
void* addr() override { return (void*)0; }
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
void s498( const s272* s585, bool b = true ) override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1945( s1890& s ) override;
operator bool() const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1590 
: public s334{
friend class s770;
s480 s626;
static s339 s346;
std::wstring s1633;
static void s1227( s481** s274, size_t n );
static void s1629( s481** s274, size_t n );
static void s1627( s481** s274, size_t n );
static void s1624( s481** s274, size_t n );
static void s1625( s481** s274, size_t n );
static void s1646( s481** s274, size_t n );
static void s1648( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
s1590( s262* s300 ) : s334( s300, NULL, NULL ) {}
s1590( s262* s300, s272* s586, s1890& s77, bool typed=true, const s263* ast_=NULL );
s1590( const s1590& right, s481* s2109 );
s1590( s262* s300, s272* s586, const s6::s143* s1632, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
void* addr() override { return (void*)&s626; }
void s498( const s272* s873, bool b = true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void load( const std::wstring& s77, bool typed, bool s194 );
void s1630( const s6::s143* ob, bool typed, s480::s145 ap = s480::s146 );
void s1620( s480::s533& st ) const;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1945( s1890& s ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s382> s866;
extern s1::s9<s382> s364;
extern s1::s9<s382> s365;
extern s1::s9<s382> s366;
extern s1::s9<s382> s867;
extern s1::s9<s382> s2131;
extern s1::s9<s382> s1672;
extern s1::s9<s382> s1510;
#define s1143 Types.Null
#define s1139 Types.Bool
#define s1298 Types.Byte
#define s1567 Types.Char
#define s1142 Types.Int
#define s1141 Types.Double
#define s1515 Types.Long
#define s1516 Types.s1517
#define s1144 Types.String
#define s1140 Types.ByteArray
#define s1705 Types.Vector
#define s1704 Types.s742
#define s1701 Types.Index
#define s1703 Types.Tuple
#define s1700 Types.HashIndex
#define s1568 Types.Position
#define s1699 Types.DateTime
#define s1702 Types.Lambda
#define s1784 Types.TSDBase
#define s1783 Types.Table
#define s1892 Types.s412
#define s1404 Types.Range
#define s1894 Types.Filter
#define s1405 Types.Seq
#define s1895 Types.s783
#define s1891 Types.ByteStream
#define s1893 Types.FileStream
#define s2207 Types.Set
#define s2240 Types.HashSet
#define s1138 ( std::numeric_limits<size_t>::max )( )
#define U64_MAX ( std::numeric_limits<uint64_t>::max )( )
typedef s356 TDDouble;
class s369
: public s271{
std::wstring s370;
s483 s371;
const s481* s372;
std::vector<size_t> s373;
size_t s374;
bool s1159;
static size_t s2267;
public:
s369( s1890& s, s262* s300, s470 cat = s471, bool _cnst = false );
s369( const s369& right, s481* s2167 = NULL );
void reset();
s481* s494() override;
const s481* s501() const override { return s372; }
const s483 s379();
bool s1194() const override { return s1159; }
void s1250() { s1159 = true; }
const std::wstring& s615() const { return s370; }
void s2270();
s484 s495( s481** s274, size_t s496 ) override;
s481* s375() const;
s481* s376();
size_t s1294() const { return s374; }
void s377( size_t off, const s481* proto );
void s1333( s369* ptr );
size_t s378() const { return s374; }
uint32_t Id() const { return (uint32_t)s374; }
s271* s333( s589* s2042, s272* impl ) const override;
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
void s498( const s272* s585, bool fr = true ) override;
void s380( s481* p );
void s381( s481* p ) { s372 = p; }
void s975( const std::vector<std::wstring> &v );
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1588
: public s481{
s484 pobj;
protected:
virtual s481* s352( const s263& s695, s272* s586,
s1890& s332 ) const override {	return NULL; }
public:
s1588( s262* s300 )
: s481( s300, s1327, NULL, NULL ), pobj(0) {}
virtual ~s1588() { }
void s1647( s481* obj ) { pobj = obj; }
s484 s2103( ) { return pobj; }
s271* s596( size_t off ) override 
{ return pobj->s596( off ); }
void s348() override {}
s1054 s384( const std::wstring& s341 ) const override { return 0; }
s481* s353( s272* s586, const std::vector<s271*>& l =
std::vector<s271*>(), const s263* ast_ = NULL ) const override { return NULL;	}
void s354( s271* p ) const override {}
s481* s1525( const s481* p ) const override { return NULL; }
const s481* s501() const override { return NULL; }
size_t s320() const override { return 0;  }
bool operator==( const s481* p ) const override { return false; }
bool operator<( const s481* p ) const override { return false; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s1::s9<s369> s487;
typedef s1::s9<s1588> s2155;
struct s1706{
std::wstring s1683;
std::wstring rowSep;
std::wstring s1720;
std::wstring s1721;
bool stringsQuoted;
bool promInts;
bool mixedTypes;
bool s1812;
bool s1999;
s1706()
: s1683( L"," ), rowSep( L"\n" ), s1721( L"." ), stringsQuoted( false ),
promInts( false ), mixedTypes( false ), s1812( false ), s1999( false )	{	}
s1706( const std::wstring& fs, const std::wstring& rs, const std::wstring& cn,
const std::wstring& dp, bool sq, bool pi, bool mt )
: s1683( fs ), rowSep( rs ), s1721( dp ), stringsQuoted( sq ),
promInts( pi ), mixedTypes( mt ), s1812( false ), s1999( false )	{	}
};
extern s1706 s1724;
extern s6::s1681 s1722;
template<class s1302, class Der>
class s1296 :
public s334{
protected:
typedef Der s1158;
s1302 s347;
static s339 s346;
static void s385( s481** s274, size_t n );
static void s386( s481** s274, size_t n );
static void s387( s481** s274, size_t n );
static void s388( s481** s274, size_t n );
static void s389( s481** s274, size_t n );
static void s390( s481** s274, size_t n );
static void s402( s481** s274, size_t n );
static void s391( s481** s274, size_t n );
static void s392( s481** s274, size_t n );
static void s393( s481** s274, size_t n );
static void s394( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s411( s481** s274, size_t n );
static void s397( s481** s274, size_t n );
static void s398( s481** s274, size_t n );
static void s399( s481** s274, size_t n );
static void s400( s481** s274, size_t n );
static void s401( s481** s274, size_t n );
static void s2082( s481** s274, size_t n );
static void s1951( s481** s274, size_t n );
static void s1950( s481** s274, size_t n );
static void s403( s481** s274, size_t n );
static void s2294( s481** s274, size_t n );
static void s404( s481** s274, size_t n );
static void s405( s481** s274, size_t n );
static void s406( s481** s274, size_t n );
static void s410( s481** s274, size_t n );
static void s1584( s481** s274, size_t n );
static void s1536( s481** s274, size_t n );
static void s1537( s481** s274, size_t n );
static void s1490( s481** s274, size_t n );
static void s407( s481** s274, size_t n );
void s348() override;
const s334::s339& s340() const override;
public:
typedef s1296<s1302, Der> s1310;
s1296( s262* s300, s272* ns_, const s263* ast_ )
: s334( s300, ns_, ast_ ) {}
s1296( const s1310& r )
: s334( r ), s347( r.s347 ) {}
template<class s1519, class s1520>
static void s1521( s481* src, s481* s772 );
s481* s1525( const s481* p ) const override;
s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s344;
class s344
: public s1296<std::int32_t, s344>{
static s339 s346;
static void s1227( s481** s274, size_t n );
static void s2291( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef std::int32_t s1375;
s344( ) : s344( NULL, (s272*)NULL ) {}
s344( s262* s300, s272* s586 = NULL );
s344( const s344& );
s344( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
s344( s262* s300, int i, s272* s586 = NULL );
s344( s262* s300, s1890& s, size_t& pos, s272* s586 = NULL );
virtual ~s344();
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s1530( s1054 tp ) const override;
void s498( const s272* s585, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
s1375* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0; }
operator int() const override { return s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void to_null( ) override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1293
: public s1296<std::int64_t, s1293>{
protected:
static s339 s346;
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef std::int64_t s1375;
s1293() : s1293( NULL ) {}
s1293( s262* s300 );
s1293( const s1293& );
s1293( s262* s300, const std::vector<s271*>& l );
s1293( s262* s300, int64_t i );
s1293( s262* s300, s1890& s, size_t& pos );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s585, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
int64_t* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0; }
operator int() const override { return (int)s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
};
class s1518
: public s1296<std::uint64_t, s1518>{
protected:
static s339 s346;
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef std::uint64_t s1375;
s1518() : s1518( NULL, (s272*)NULL ) {}
s1518( s262* s300, s272* s586 = NULL );
s1518( const s1518& );
s1518( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
s1518( s262* s300, uint64_t i, s272* s586 = NULL );
s1518( s262* s300, s1890& s, size_t& pos, s272* s586 = NULL );
s481* s352( const s263& s695, s272* s586, 	s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s585, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
s1375* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0; }
operator int() const override { return (int)s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
};
template <>
inline void s1296<s1518::s1375, s1518>::s402( s481** s274, size_t s496 ){
( (s1518*)s274[0] )->s347 = ( (s1518*)s274[1] )->s347;}
template <>
inline void s1296<s1518::s1375, s1518>::s387( s481** s274, size_t s496 ){
if( s496 == 2 )
( (s1518*)s274[0] )->s347 = ( (s1518*)s274[1] )->s347;
else {
s274[2]->s354( s274[0] );
( (s1518*)s274[0] )->s347 =
( (s1518*)s274[1] )->s347 - ( (s1518*)s274[0] )->s347;}}
class s1285
: public s1296<tdbyte_t, s1285>{
protected:
static s339 s346;
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef tdbyte_t s1375;
s1285() : s1285( NULL ) {}
s1285( s262* s300 );
s1285( const s1285& );
s1285( s262* s300, const std::vector<s271*>& l );
s1285( s262* s300, tdbyte_t i );
s1285( s262* s300, const std::wstring& s, size_t& pos );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s585, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
tdbyte_t* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0; }
operator int() const override { return s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override { return std::to_wstring( s347 ); }
void s1920( Stream* ) const override;
};
class s1561
: public s1296<wchar_t, s1561>{
protected:
static s339 s346;
static void s1227( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s401( s481** s274, size_t n );
static void s2225( s481** s274, size_t n );
static void s2223( s481** s274, size_t n );
static void s2224( s481** s274, size_t n );
static void s885( s481** s274, size_t n );
static void s884( s481** s274, size_t n );
static void s2282( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
typedef wchar_t s1375;
s1561() : s1561( NULL ) {}
s1561( s262* s300 );
s1561( const s1561& );
s1561( s262* s300, const std::vector<s271*>& l );
s1561( s262* s300, wchar_t i );
s1561( s262* s300, s1890& s, size_t& pos );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s585, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
wchar_t* s355() { return &s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return s347 != 0; }
operator int() const override { return s347; }
operator double() const override { return (double)s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override { return std::wstring( 1, s347 ); }
void s1920( Stream* ) const override;
};
typedef s344 TDInt;
class s589;
class s272;
typedef std::vector<std::pair<std::wstring, size_t>> s620;
typedef std::map<std::wstring, s272*> s621;
typedef std::map<std::wstring, s263*> s622;
class s272
: public s481{
protected:
const s272* s623;
const s272* s624;
s369 s1649;
const std::wstring& s345;
std::wstring s278;
std::wstring s625;
s480 s626;
s549* s627;
std::vector<s483> s628;
std::vector<s369> s629;
s2176 s2180;
void s348() override { }
s481* s1690( s481** s274, size_t s496 );
public:
s272( const s272& s630, std::vector<s483>& s274, const s263* ast_/*=NULL*/, s272* ns_/* = NULL*/ );
s272( s262* s300, s1054 s338, s470 pc/* = s471*/, const s263* ast_/* = NULL*/, s272* ns_/* = NULL*/, s2176 st = s2183  );
s272( s1890& s278, s262* s300, s470 pc, const s263* ast_/* = NULL*/, s272* ns_/* = NULL*/, s2176 st = s2183 );
s272( s1890& s345, const std::wstring& s278, s262* s300, s480& s631,
const s480& s626, const s263* ast_/* = NULL*/, s2176 st/* = s2187*/  );
s272( s263& s695, s262* s300, s470 pc, s272* ns, s534 am,
s621& cl, s620& cnl, s622& al, s2176 st );
virtual ~s272();
s1890& s351() const override { return s345; }
virtual s1890& s299() const { return s278; }
std::wstring s298() const override;
std::wstring s828() const override;
s2176 s2178() const { return s2180; }
void s2181( s2176 st ) override { s2180 = st; }
static s271* s632( const s6::s143& obj, s1890& s278, s262* s300 );
static s271* s632( std::multimap<std::wstring, s482*>& v, s482* s585 );
s481* s633( const s263& s695, s481* s586, s1890& s332 ) const;
using s481::s353;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s1525( const s481* p ) const override;
s1054 s384( s1890& s341 ) const override;
bool s499( const s481* s500 ) const override;
const s920& s997() const override { return s986; }
bool s724( s1890& f ) const;
void s845( s1890& s76, s481* s347, s480::s145 ap = s480::s146 );
void s1643( s1890& s76, s481* s347 );
void s1628( const s1590* ob );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
const s481* s501() const override { return s623; }
const s272* s634() const { return s624; }
s1890& s635() const { return s625; }
s481* s342( s1890& s278, s1890& s332,
bool s518 = true, bool s2151 = true ) const override;
s589* s1671( s1890& s278, s589* s215,	s272* s586, s559* cs ) const override;
void s643( s263& s695 );
void s553( s1890& s76, s1890& s556 );
bool s2163( s1890& s76 );
void s636( s263& s695 );
void s963( s263& s695 );
void s637( s1890& s332,	std::vector<std::wstring>& s153 );
bool s554( s1890& s278, s369* s153, s1890& s332, bool fr ) const override;
size_t s638( const std::wstring& s278 ) const;
s271* s596( size_t off ) override;
s481* s639( s1890& s278, s1890& s332,
bool s518=true ) const;
bool s640( s1890& sym, s1890& s497 ) const;
bool s530( s1890& sym );
void s498( const s272* s873, bool b ) override;
void s642( const s480& s274 ); 
void s154( s263& s695 );
void s1637();
void s2118( s589* s2042, s272* impl, bool s2159 = true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
void s641( s272* s644 ) const;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s1920( Stream* ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s559
: public s271{
const std::wstring s599;
std::vector<s271*> s274;
s940 past;
bool s2159;
public:
s559( s262* pass_, const s263* ast_, bool s2160 = false )
: s271( pass_, s475 ), past( (s263*)ast_ ), s2159( s2160 ){}
s559( s262* pass_, s1890& s1541, const std::vector<s271*>& l, const s263* s695, bool s2160 = false );
s559( const s559& s538 );
s1890& s299() const { return s599; }
void s2171( bool b ) { s2159 = b; }
bool s2166() const { return s2159; }
std::vector<s271*>& s600() { return s274; }
const s263* s601() { return past; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override { }
};
typedef s1::s9<s559> s488;
class s589;
class s262;
typedef s589 TD;
class s334;
typedef s589 Transd;
typedef std::vector<s483> s575;
typedef std::vector<s484> s576;
typedef std::vector<s483> s577;
extern s575 s2100;
class s589
: public s272{
public:
enum s561 { s562, s563, s564, s565, s566, s2098, s567 };
protected:
std::wstring s667;
enum s568 { s569, s570, s571, s572 };
s561 s573;
s568 s574;
s481** s578;
s482** s579;
size_t s496, nlocs;
s576 s580;
s575 s274;
std::vector<s484> s974;
std::vector<s481*> s581;
s577 s582;
std::vector<std::vector<s482*>> s583;
s484 s584;
s485 s586;
s486 s585;
const s263* past;
s2155 s1640;
s483 subject;
const bool intro;
const bool s2159;
int s2220;
void s841( s271* par, size_t pos, s483& s153, const s272* s1658,
bool proc );
void s587( s1890& s332);
void s588( s1890& s332);
s481* s1599( s481** s699, size_t s496 );
virtual void s1896( const s575& pl ) const;
public:
s589( s262* s300, s272* s590, s589* s591, s272* ns_, s561 ct,
s1890& s672, const s263* s695, bool s1713 = false, bool _bd = true );
s589( s262* s300, s272* s586, s589* s585, s272* ns_, s561 ct,
const std::vector<s271*>& l, const s263* s695, bool s1713, bool _bd );
s589( const s589& right, s272* s586, s589* s585, s272* ns_, 
const std::vector<s271*>& s274, const s263* s695, bool s2105=false, 
bool _bd=true );
virtual ~s589();
s561 s858() const { return s573; }
void s592( s568 vt ) { s574 = vt; }
s568 s593() const { return s574; }
const std::wstring& s351() const override { return s271::s351(); }
std::wstring s828() const override;
std::wstring s298() const override;
bool s2166() const { return s2159; }
bool s2285() const { return ( s2220 == -1 ); }
const s263* s601() const { return past; }
s481* s494() override { return s584; }
void s2172( s369* ref );
virtual s483 s2284();
void s498( const s272* s1658, bool proc ) override;
virtual void s594( const std::vector<s483>& l );
typedef std::vector<std::pair<std::wstring, s484>> s829;
void s808( s829& s153 ) const;
void s595( const s272* s1658 );
void s2114( s575& s2113 );
void s2118( s589* s2042, s272* impl, bool s2159 = true ) override;
bool s554( s1890& s278, s369* ref, s1890& s332, bool ) const override;
s271* s596( size_t off ) override;
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
static s589* s597( const s263& s695, s262* s300, s272* obj,
s1890& s278, s1890& s556 );
static s559* s1110( const s263& s695, s262* s300, s272* obj,
s1890& s556, bool s2159 );
static s589* s598( s559* cs, s262* s300, s272* s586, s589* s215,
s1890& s556, bool proc );
static void s1232( std::vector<s271*>& s274, const std::vector<std::wstring>& s1199 );
static void s1232( std::vector<s483>& s274, const std::vector<std::wstring>& s1199 );
void s304( std::wostream* pd, int s197 = 0 ) const override;
std::wstring trace( s1890& topics ) const override;
};
class s835
: public s589{
s614 s560;
bool s1961;
public:
s835( s262* s300, s589* s585, s272* ns, s561 ct, const std::vector<s271*>& l,
s1054 s491, s1890& s1541, const s263* s695, bool _bd = false );
s835( const s835& right, s589* s585, s272* ns );
virtual ~s835();
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
bool s554( s1890& s278, s369* ref,	s1890& s332, bool ) const override;
s271* s333( s589* s2042, s272* impl ) const override;
bool s1194() const override { return s1961; }
};
class s836
: public s589{
public:
s836( s262* s300, s272* s586, s589* s585, s272* ns, s561 ct,
const std::vector<s271*>& l, const s263* s695, bool s2159 = false );
s836( const s836& right, s589* s585, const std::vector<s271*>& s274,
s561 ct, const s263* s695, s272* s586 = NULL, s272* ns = NULL, bool intro = true, bool _bd = false );
virtual ~s836();
s483 s2284() override;
void s1664( s272* s590 ) { s586 = s590; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s2259( const std::vector<s483>& l );
void s2246( );
};
class s1347
: public s836{
public:
s1347( s262* s300, s272* s586, s589* s585, const s263* s695 );
s1347( const s1347& right, s272* s586, s589* s585, const std::vector<s271*>& s274,
const s263* s695 );
virtual ~s1347();
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
namespace s1501 {
extern s1054 s1494;
extern s1054 s1498;
extern s1054 s1493;}
typedef std::basic_istream<wchar_t> s1486;
typedef std::basic_ostream<wchar_t> s1489;
typedef std::basic_istringstream<wchar_t> s1956;
typedef std::basic_ostringstream<wchar_t> s1957;
class Stream
: public s334{
public:
typedef std::ios_base::fmtflags s1909;
typedef std::streamsize s1910;
Stream( s262* s300, s272* ns, const s263* s208 = NULL )
: s334( s300, ns, s208 ) {}
virtual void s1450( std::wstring& s153, size_t s1461 );
virtual void s1469( const std::wstring& src );
virtual void s1451( std::wstring& s153, const std::wstring& s72 = L"\n" );
virtual void s1470( const std::wstring& src );
virtual void s1449( s1312& s153, size_t s1461 );
virtual void s1468( const s1312& src );
virtual void s1448( s1312& s153, const s1312& s72 = s1312( {'\n'} ) );
virtual void s1467( const s1312& src );
virtual void rewind();
virtual void s1914()=0;
virtual void s1912()=0;
virtual void s2051()=0;
virtual void s2050()=0;
virtual void s1942()=0;
virtual void s1943()=0;
virtual void s1556( int n )=0;
virtual void s1913( int n )=0;
virtual void s1898( wchar_t c );
virtual void s1900()=0;
virtual void s1901()=0;
virtual void s1899()=0;
virtual void s1911()=0;
virtual void s1554()=0;
virtual void s1555()=0;
virtual s1909 s1915() const = 0;
virtual s1910 s1916() const = 0;
virtual bool s2052() const = 0;
virtual void s1936()=0;
virtual void s1938()=0;
virtual void s1941( int n )=0;
virtual void s1939( int n )=0;
virtual void s1937()=0;
virtual void s1940()=0;
virtual s1909 s1946() const = 0;
virtual s1910 s1947() const = 0;
virtual void ws() { throw new s2::s16( L"ws not implemented" ); }
virtual s1486& s1948() { throw new s2::s16( L"iwstream not implemented" ); }
virtual s1489& s1949() { throw new s2::s16( L"owstream not implemented" ); }
};
template<class s1409, class s1411>
class s1395
: public Stream{
protected:
typedef s1395<s1409, s1411> s1158;
typedef s334::s339 s339;
s1409 *s1463;
s1411 *s1464;
bool s2058;
static s339 s346;
void s348() override;
const s339& s340() const override { return s346; }
static void s1476( s481** s274, size_t n );
public:
s1395( s262* s300, s272* ns, const s263* s208 = NULL )
: Stream( s300, ns, s208 ), s2058( false ) {}
s1395(): s2058( false ){}
virtual ~s1395() {}
void s1914() override;
void s1912() override;
void s2051() override;
void s2050() override;
void s1942() override;
void s1943() override;
void s1556( int n ) override;
void s1913( int n ) override;
void s1900() override;
void s1901() override;
void s1899() override;
void s1911() override;
void s1554() override;
void s1555() override;
s1909 s1915() const override;
s1910 s1916() const override;
bool s2052() const override;
void s1936() override;
void s1938() override;
void s1941( int n ) override;
void s1939( int n ) override;
void s1937() override;
void s1940() override;
s1909 s1946() const override;
s1910 s1947() const override;
};
template<class s1409, class s1411>
s334::s339 s1395<s1409, s1411>::s346;
template<class s1409, class s1411>
void s1395<s1409, s1411>::s348(){
s346.insert( std::make_pair( L"rewind", new s335( L"rewind", &s1395<s1409,s1411>::s1476, s1143,
{ s1113() }, 0, 0 ) ) );}
template<class s1409, class s1411>
void s1395<s1409, s1411>::s1476( s481** s274, size_t s496 ){
s1158* s1055 = (s1158*)s274[1];
if( s1055->s1463 ) {
if( s1055->s1463->eof() )
s1055->s1463->clear( s1055->s1463->rdstate() &
( s1055->s1463->rdstate() ^ std::ios_base::eofbit ) );
if( !s1055->s1463->good() )
throw new s2::s16( L"file handle is not valid" );
s1055->s1463->seekg( 0 );
s1055->s1463->clear();}
if( s1055->s1464 )
s1055->s1464->seekp( 0 );}
class s505
: public s1395<s1956,s1957>{
protected:
typedef s505 s1158;
static s339 s346;
std::basic_stringstream<wchar_t> ss;
static void s506( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
public:
s505( const s505&, const s263* ast_ = NULL );
s505( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s505(){}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s873, bool ) override;
void release() override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void* addr() override { return (void*)&ss; }
s1486& s1948() override { return *s1463; }
s1489& s1949() override { return *s1464; }
void s1450( std::wstring& s153, size_t s1461 ) override;
void s1469( s1890& src ) override;
void s1451( std::wstring& s153, s1890& s72 = L"\n") override;
void s1470( s1890& src ) override;
void s1449( s1312& s153, size_t s1461 ) override;
void s1468( const s1312& src ) override;
void s1448( s1312& s153, const s1312& s72 = s1312( { '\0' } ) ) override;
void s1467( const s1312& src ) override;
void s1898( wchar_t c ) override;
virtual void ws() override { *s1463 >> std::ws; }
virtual std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_istringstream<tdbyte_t> s1484;
typedef std::basic_ostringstream<tdbyte_t> s1487;
class s1284
: public s1395<s1484,s1487>{
protected:
typedef s1284 s1158;
static s339 s346;
std::basic_stringstream<tdbyte_t> bs;
static void s1305( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
public:
s1284( const s1284&, const s263* ast_ = NULL );
s1284( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
~s1284(){}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s873, bool ) override;
void release() override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void* addr() override { return (void*)&bs; }
void s1450( std::wstring& s153, size_t s1461 ) override;
void s1469( s1890& src ) override;
void s1451( std::wstring& s153, s1890& s72 = L"\n" ) override;
void s1470( s1890& src ) override;
void s1449( s1312& s153, size_t s1461 ) override;
void s1468( const s1312& src ) override;
void s1448( s1312& s153, const s1312& s72 = s1312( { '\0' } ) ) override;
void s1467( const s1312& src ) override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef std::basic_ifstream<tdbyte_t> s1485;
typedef std::basic_ofstream<tdbyte_t> s1488;
class s1292
: public s1395<s1485,s1488>{
protected:
typedef s1292 s1158;
static s339 s346;
s483 s210;
s483 mode;
std::wstring s1331;
typedef std::basic_fstream<tdbyte_t> s1483;
std::fstream fs;
static void s1227( s481** s274, size_t n );
static void s2013( s481** s274, size_t n );
static void s2015( s481** s274, size_t n );
static void s2014( s481** s274, size_t n );
static void s1314( s481** s274, size_t n );
static void s407( s481** s274, size_t n );
static void s2021( s481** s274, size_t n );
static void s1473( s481** s274, size_t n );
static void s1345( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
static void s1991( s481** s274, size_t s496, std::wstring& s1335 );
void _open( const std::wstring& s1335 );
void _close();
public:
s1292( const s1292&, const s263* ast_ = NULL );
s1292( s262* s300, s272* ns_ = NULL, const s263* ast_ = NULL );
s1292( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL );
~s1292(){}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s873, bool ) override;
void release() override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void* addr() override { return (void*)&fs; }
void s1450( std::wstring& s153, size_t s1461 ) override;
void s1469( s1890& src ) override;
void s1451( std::wstring& s153, s1890& s72 = L"\n" ) override;
void s1470( s1890& src ) override;
void s1449( s1312& s153, size_t s1461 ) override;
void s1468( const s1312& src ) override;
void s1448( s1312& s153, const s1312& s72 = s1312( { '\0' } ) ) override;
void s1467( const s1312& src ) override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1391
: public s1395<std::wistream, std::wostream>{
static s339 s346;
static void s325( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
s1391( const s505&, const s263* ast_ = NULL );
s1391( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1391(){}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void* addr() override { return NULL/*(void*)&std::wcin*/; }
void s1450( std::wstring& s153, size_t s1461 ) override;
void s1469( s1890& src ) override;
void s1451( std::wstring& s153, s1890& s72 ) override;
void s1470( s1890& src ) override;
void s1449( s1312& s153, size_t s1461 ) override;
void s1468( const s1312& src ) override;
void s1448( s1312& s153, const s1312& s72 ) override;
void s1467( const s1312& src ) override;
virtual std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1393
: public s1395<std::wistream, std::wostream>{
static s339 s346;
static void s506( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
s1393( const s505&, const s263* ast_ = NULL );
s1393( s262* s300, s272* ns_, const s263* ast_ = NULL );
~s1393(){}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void* addr() override { return NULL; }
s1489& s1949() override { return *s1464; }
void s1450( std::wstring& s153, size_t s1461 ) override;
void s1469( s1890& src ) override;
void s1451( std::wstring& s153, s1890& s72 ) override;
void s1470( s1890& src ) override;
void s1449( s1312& s153, size_t s1461 ) override;
void s1468( const s1312& src ) override;
void s1448( s1312& s153, const s1312& s72 ) override;
void s1467( const s1312& src ) override;
void s1898( wchar_t c ) override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
extern s1::s9<s1391> s1392;
extern s1::s9<s1393> s1394;
class s262;
class s383;
class Iterator{
public:
virtual ~Iterator() {}
virtual s271* s313() = 0;
virtual s271* s955() = 0;
virtual const s271* s955() const = 0;
virtual s271* Idx() = 0;
virtual s271* El() = 0;
virtual s1054 s317() const { return ValType(); };
virtual s1054 ValType() const = 0;
virtual bool s1964() const = 0;
virtual bool operator==( const Iterator* r ) const { return this == r; }
virtual bool operator<( const Iterator* r ) const { return this < r; }
};
typedef std::pair<s1::s1279<Iterator>, s1::s1279<Iterator>> s1135;
struct s834;
class s383;
class s324
: public s334{
protected:
s1054 s315;
s1054 s1191;
s1054 s323;
virtual s481* s1181( Iterator* it );
public:
s324( s262* s300, s272* ns_, const s263* ast_ )
: s334( s300, ns_, ast_ ), s315( 0 ), s1191( 0 ), s323( 0 ) {}
s324( const s324& r )
: s334( r ), s315( r.s315 ), s1191( r.s1191 ), s323( r.s323 ) {}
virtual ~s324() {}
virtual size_t s1129() const { return 0; }
virtual Iterator* s312( s383* r ) = 0;
virtual s1054 s317() const { return s315; }
virtual s1054 s931() const { return s1191; }
virtual s1054 ValType() const { return s323; }
virtual Iterator* s1176() = 0;
virtual Iterator* s1180() = 0;
virtual s1135 s1185() = 0;
virtual Iterator* s1155( const s481* idx );
virtual Iterator* s1174( const s481* s347 );
virtual Iterator* s1229( const s481* s347 );
virtual s481* sort( bool reverse, s834* cmp );
};
class s383
: public s324,
public Iterator{
s483 s586;
s1::s9<s324> s978;
s1::s1279<Iterator> s1455;
s483 s1233, s1234;
s484 s1531, s1532;
bool s971, s972;
Iterator* s316;
uint64_t s981, s1535;
int incr;
s1::s9<s1518> s1166;
static s339 s346;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
public:
enum s1132 { s1218, s1225, s1217, s1224, s1226, s1213, s1219 };
s383( s262* s300 );
s383( s262* s300, s324* s586, Iterator* it );
s383( uint64_t b, uint64_t e = U64_MAX );
s383( s262* s300, s1890& s77, const s263* ast_ = NULL );
s383( const s383& right, const s263* ast_ = NULL );
s383( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
~s383();
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1133 s1188( s1890& s341 ) const override;
s1133 s1183( s1890& s341, s1113& ap ) const override;
s1133 s1178( s1890& s341,	s1113& ap ) override;
s1054 s1179( s1890& s1541,	const std::vector<s483>& l ) const override;
const std::vector<std::wstring>& s1182( s1890& s341 ) const override;
size_t s1129() const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)s316; }
void s498( const s272* s873, bool fr=true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
Iterator* s312( s383* r ) override;
Iterator* s1176() override { return NULL; }
Iterator* s1180() override { return NULL; }
s1135 s1185() override;
s1135 s1185( s324* s586 );
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s1054 ValType() const override { return s323; }
bool s1964() const override;
s324* s813() { return s978; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1125
: public s324,
public Iterator{
s483 s586;
s484 s978;
s1::s9<s383> range;
s483 where, s1063;
s1::s1279<Iterator> s316, s1478;
s1::s9<s369> s980; // @it - for using in s1193 scope lambdas
s271* s981;
static s339 s346;
s1::s9<s344> s347, s681;
std::wstring s497;
s1054 s1343;
static void s1227( s481** s274, size_t n );
static void s1338( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
enum s1132 { s1218, s1225, s1217, s1224, s1226, s1322, s1219 };
s1125( s262* s300 ) : s324( s300, NULL, NULL ), s980( new s369( s7::s1363, s300, s473 ) ), 
s981(NULL) {}
s1125( s262* s300, s1890& s77, const s263* ast_ = NULL );
s1125( const s1125& r, const s263* ast_ = NULL );
s1125( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s1054 s317() const override { return s681->s350(); }
size_t s1129() const override { return s978.s15<s324*>()->s1129(); }
s1133 s1183( s1890& s341,	s1113& ap ) const override;
s1133 s1178( s1890& s341, s1113& ap ) override;
s1054 s1179( s1890& s1541,	const std::vector<s483>& l ) const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 ValType() const override { return s323; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
bool s554( s1890& s278, s369* s153, s1890& s332,	bool ) const override;
s271* s596( size_t off ) override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
bool s1964() const override;
Iterator* s312( s383* r ) override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
Iterator* s1176() override { return NULL; }
Iterator* s1180() override { return NULL; }
s1135 s1185() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s944
: public s324,
public Iterator{
s486 s1051;
s486 set;
s486 eq;
s483 start;
s483 end;
s483 incr;
s483 s982;
s483 s1645;
bool s1040;
std::wstring s497;
static s339 s346;
static void s1227( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
enum s1132 { s1218, s1225, s1217, s1224, s1226, s1213, s1219 };
s944( s262* s300 );
s944( s262* s300, s1890& s77, const s263* ast_ = NULL );
s944( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
virtual ~s944();
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1054 ValType() const override { return s323; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override {}
size_t s320() const override { return 0; }
bool operator==( const s481* p ) const override { return false; }
bool operator<( const s481* p ) const override { return false; }
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
bool s1964() const override;
Iterator* s312( s383* r ) override;
s271* s313() override;
s271* s955() override { return NULL; }
const s271* s955() const override { return NULL; }
s271* Idx() override;
s271* El() override { return NULL; }
s1054 s317() const override { return s323; }
Iterator* s1176() override { return NULL; }
Iterator* s1180() override { return NULL; }
void* addr() override { return NULL; }
s1135 s1185() override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef int HPROG;
typedef std::vector<s483> s2239;
enum s1359{ s1418=1, s1419, s1420, s1421, s1610, 
s1422, s1423, s2195, s2064, s1424, s1425, s1428, 
s1426, s1427, s1611, s1429, s1932, s1612, 
s1430, s2216, s1431, s1614, s1615, s1432,
s1872, s1613,	s1933, s1931, s1433,
s1551, s1434, s1435, s1436, s1616,
s1437,	s1438, s1439 };
extern std::map<std::wstring, int> s1360;
extern std::vector<int> BIFuncs1v;
extern std::vector<std::wstring> s1361;
struct s716{
std::vector<std::wstring> s661;
std::wstring entry;
s1984 restrictions[s1969];
s716() {
memset( &restrictions, 0, s1969 * sizeof(s1984) );}
};
class s1972{
s1984 s2026[s1969];
static std::vector<std::wstring> s2034;
s1984 s1988( const std::wstring& s2024 );
public:
s1972();
void s2041( const s6::s143& s133 );
void reset();
void s1998( const std::vector<s1983>* s2019, s1984 sw ) const;
bool s1997( s1983 si, s1984 sw ) const;
};
class s559;
class s262
: public s272{
private:
std::vector<std::wstring> s199;
s263 s695;
std::wstring s200;
std::wstring s761;
std::wstring s1883;
s1972 s2025;
void s202( s1890& s655, s716& s153 );
void s213( s1890& s194, const s6::s143& obj );
void s2158( const s6::s143& obj );
s489 s203;
s480 s204;
typedef std::map<std::wstring, s481*> s205;
s205 s206;
bool s1309;
std::map<const s481*, s2239*> s2255;
public:
s262();
~s262();
s1890& s710() const { return s761; }
void s1875( s1890& s ) { s761 = s; }
s1890& s1878() const { return s1883; }
void s1876( s1890& s ) { s1883 = s; }
virtual std::wstring s828() const override { return L"::"; }
virtual std::wstring s298() const override { return L"::"; }
void s1885( bool soft = false );
void reset();
void s207( s263& s208 );
void s209( s1890& s210, bool s1887 = false );
void s211( s6::s143& obj );
void s212( s1890& s210 );
s481* run( const std::vector<std::wstring>& s687 );
s481* callFunc( s1890& s599, std::vector<std::wstring>& l );
s486 getProc( s1890& s599 );
bool s1320() const { return s1309; }
void s1638( s1890& s667 );
void s1998( const std::vector<s1983>* s2019, s1984 sw ) const;
bool s1997( s1983 si, s1984 sw ) const;
s489& TR() { return s203; }
s589* s214( int s1446, s559* cs,
s272* s586, s589* s215 );
void s217( s1890& s );
s1054 s218( s481* p, s1890& s345 );
void s219( s1890& s347, s1890& s332, std::vector<std::wstring>& s153 );
virtual bool s554( s1890& s278, s369* s153,	s1890& s332, bool ) const override;
s484 s220( s1890& s347, s1890& s332 );
bool s221( s369& rf ) const;
s271* s222( s1890& sym, s1890& s497, bool s518 = true );
void* s223( s1890& s278 );
void s1341( s1890& s667 );
void s1651( s1890& s1621 );
void s2243( const s481* s152, s2239* s2254 );
s2239* s2249( const s481* s152 );
void s2248( const s481* old, const s481* nw );
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s1::s9<s262> s715;
namespace s1501 {
extern s1054 s1496;
extern s1054 s1495;
extern s1054 s1497;}
class Iterator;
struct s834;
class s1134;
struct s319{
std::size_t operator()( const s484 k ) const{
return k->s320();}
std::size_t operator()( const s483 k ) const{
return k.s15<s481*>()->s320();}
};
struct s321{
bool operator()( const s484 l, const s484 r ) const{
return l->operator==( ( s481* )&( *r ) );}
bool operator()( const s481* l, const s481* r ) const{
return l->operator==( r );}
bool operator()( const s481& l, const s481& r ) const{
return l.operator==( &r );}
bool operator()( const s483 l, const s483 r ) const{
return l.s15<s481*>()->operator==( r.s15<s481*>() );}
};
struct s2292{
bool operator()( const s484 l, const s484 r ) const{
return l->s320() == r->s320();}
bool operator()( const s481* l, const s481* r ) const{
return l->s320() == r->s320();}
bool operator()( const s481& l, const s481& r ) const{
return l.s320() == r.s320();}
bool operator()( const s483 l, const s483 r ) const{
return l.s15<s481*>()->s320() == r.s15<s481*>()->s320();}
};
struct s1414{
bool operator()( const s484 l, const s484 r ) const{
return l->operator<( ( s481* )&( *r ) );}
bool operator()( const s481* l, const s481* r ) const{
return l->operator<( r );}
bool operator()( const s481& l, const s481& r ) const{
return l.operator<( &r );}
bool operator()( const s483 l, const s483 r ) const{
return l.s15<s481*>()->operator<( r.s15<s481*>() );}
};
void s1152( s262* s300, const std::wstring& s77, 
std::wstring& s1263, std::wstring& s642 );
template<class s1301>
struct s1291 {
bool operator()( const s1301& l, const s1301& r ) { return l < r; }
};
template<class s1301>
struct s1562 {
bool operator()( const s1301& l, const s1301& r ) { return l == r; }
};
template<class s1301, class s1569>
struct s1563{
s486 s853;
std::vector<s483>s855;
s1563() : s853( 0 ),
s855( { new s1569( 0,0 ), new s1569( 0,0 ) } ) {}
bool operator()( const s1301& l, const s1301& r ){
*s855[0].template s15<s1569*>()->s355() = l;
*s855[1].template s15<s1569*>()->s355() = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
};
template<>
struct s1291<s483>{
std::vector<s483>s855;
s486 s853;
s1291() : s853( 0 ) { s855.resize( 2 ); }
bool operator()( const s483& l, const s483& r ){
if( s853.s14() ) {
s855[0] = l;
s855[1] = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l.s15<s481*>()->operator<( r.s15<s481*>() );}
};
template<>
struct s1291<s484>{
std::vector<s483>s855;
s486 s853;
s1291() : s853( 0 ) { s855.resize( 2 ); }
bool operator()( const s484& l, const s484& r ){
if( s853.s14() ) {
s855[0] = l.s15<s271*>();
s855[1] = r.s15<s271*>();
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l->operator<( r.s15<s481*>() );}
};
template<>
struct s1291<tdbyte_t>{
s486 s853;
std::vector<s483>s855;
s1291() : s853( 0 ),
s855( { new s1285( 0,0 ), new s1285( 0,0 ) } ) {}
bool operator()( const tdbyte_t& l, const tdbyte_t& r ){
if( s853.s14() ) {
*s855[0].s15<s1285*>()->s355() = l;
*s855[1].s15<s1285*>()->s355() = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l < r; }
};
template<>
struct s1291<wchar_t>{
s486 s853;
std::vector<s483>s855;
s1291() : s853( 0 ),
s855( { new s1561( 0,0 ), new s1561( 0,0 ) } ) {}
bool operator()( const wchar_t& l, const wchar_t& r ){
if( s853.s14() ) {
*s855[0].s15<s1561*>()->s355() = l;
*s855[1].s15<s1561*>()->s355() = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l < r; }
};
template<>
struct s1562<s483> {
bool operator()( const s483& l, const s483& r ) { 
return l.s15<s481*>()->operator==( r.s15<s481*>() );}
};
template<>
struct s1562<s484> {
bool operator()( const s484& l, const s484& r ) { 
return l->operator==( r.s15<s481*>() );}
};
template<>
struct s1563<s483, s483>{
std::vector<s483>s855;
s486 s853;
s1563() : s853( 0 ) { s855.resize( 2 ); }
bool operator()( const s483& l, const s483& r ){
s855[0] = l;
s855[1] = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
};
template<>
struct s1563<s484, s484>{
std::vector<s483>s855;
s486 s853;
s1563() : s853( 0 ) { s855.resize( 2 ); }
bool operator()( const s484& l, const s484& r ){
s855[0] = l.s15<s271*>();
s855[1] = r.s15<s271*>();
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
};
typedef std::wstring s1565;
template<class _Cont, class s1301, class Der>
class s311 :
public s324{
protected:
typedef Der s1158;
_Cont s347;
static s1291<s1301> s1315;
static s1562<s1301> s1572;
typedef s334::s339 s339;
static s339 s346;
static void s326( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s1244( s481** s274, size_t n );
static void s1257( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
s271* s1325( s1301 el ) { return el; }
static std::pair<typename _Cont::iterator, typename _Cont::iterator> s1413( s481* p, Der* pv );
static s1135 s1415( s481* p, Der** pv );
static s1134* s1960( Der** pv, typename _Cont::iterator& s1966 );
public:
typedef s311<_Cont, s1301, Der> s1161;
s311( s262* s300, s272* ns, const s263* ast_ );
s311( const s1161& r );
virtual ~s311(){}
virtual s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
virtual s1135 s1185() override;
};
template<class _Cont, class s1301, class Der>
s334::s339 s311<_Cont, s1301, Der>::s346;
template<class _Cont, class s1301, class Der>
s1291<s1301> s311<_Cont, s1301, Der>::s1315;
template<class _Cont, class s1301, class Der>
s1562<s1301> s311<_Cont, s1301, Der>::s1572;
template<class _Cont, class s1301, class Der, class s1570>
class s1390 :
public s311<_Cont, s1301, Der>{
protected:
typedef s334::s339 s339;
typedef s334::s335 s335;
static s1563<s1301, s1570> s1573;
static void s1571( s481** s274, size_t n );
static void s1574( s481** s274, size_t n );
static void s1623( s481** s274, size_t n );
static void s1609( s481** s274, size_t n );
static void s1202( s481** s274, size_t n );
static void s1201( s481** s274, size_t n );
static void s2075( s481** s274, size_t n );
static void s2074( s481** s274, size_t n );
static void s2073( s481** s274, size_t n );
static void s1244( s481** s274, size_t n );
static void s1257( s481** s274, size_t n );
static void s1581( s481** s274, size_t n );
static void s1575( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s1482( s481** s274, size_t n );
static void s1731( s481** s274, size_t n );
static void s1935( s481** s274, size_t n );
static void s2079( s481** s274, size_t n );
static void s2222( s481** s274, size_t n );
static s339 s346;
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
s271* s1325( s1301 el ) { return el; }
public:
typedef s1390<_Cont, s1301, Der, s1570> s1161;
s1390( s262* s300, s272* ns, const s263* ast_ );
s1390( const s1161& r );
virtual ~s1390(){}
virtual s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
};
template<class _Cont, class s1301, class Der, class s1570>
s334::s339 s1390<_Cont, s1301, Der, s1570>::s346;
template<class _Cont, class s1301, class Der, class s1570>
s1563<s1301, s1570> s1390<_Cont, s1301, Der, s1570>::s1573;
template<class _Cont, class s1301, class Der>
class s1564 :
public s1390<_Cont, s1301, Der, s1301>{
protected:
typedef s334::s339 s339;
typedef s334::s335 s335;
static void s1623( s481** s274, size_t n );
static void s1609( s481** s274, size_t n );
static void s1257( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s1453( s481** s274, size_t n );
static void s1958( s481** s274, size_t n );
static void s2222( s481** s274, size_t n );
static s339 s346;
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
public:
typedef s1564<_Cont, s1301, Der> s1161;
s1564( s262* s300, s272* ns, const s263* ast_ );
s1564( const s1161& r );
virtual ~s1564(){}
virtual s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
};
template<class _Cont, class s1301, class Der>
s334::s339 s1564<_Cont, s1301, Der>::s346;
template<class s1301>
struct s1369 {
bool operator()( const s1301& l, const s1301& r ) { return l < r; }
};
template<>
struct s1369<std::pair<s484, s484>>{
typedef std::pair<s484, s484> s1408;
std::vector<s483>s855;
s486 s853;
s1369() : s853( 0 ) { s855.resize( 2 ); }
bool operator()( const s1408& l, const s1408& r ){
if( s853.s14() ) {
s855[0] = l.first.s15<s271*>();
s855[1] = r.first.s15<s271*>();
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
else
return l.first->operator<( r.first.s15<s481*>() );}
};
template<class _Cont, class s1410, class s1412, class Der>
class s1358 :
public s311<_Cont, s1410, Der>{
protected:
typedef s334::s339 s339;
typedef s334::s335 s335;
s1369<std::pair<s1410, s1412>> s1444;
static void s774( s481** s274, size_t n );
static void s1202( s481** s274, size_t n );
static void s2075( s481** s274, size_t n );
static void s2073( s481** s274, size_t n );
static void s1474( s481** s274, size_t n );
static s339 s346;
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
s271* s1325( std::pair<s1410, s1412>& el );
public:
typedef s1358<_Cont, s1410, s1412, Der> s1161;
s1358( s262* s300, s272* ns, const s263* ast_ );
s1358( const s1161& r );
virtual s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
virtual bool insert( s481* s152, s481* s347 );
virtual s481* find( s481* s152 );
};
template<class _Cont, class s1410, class s1412, class Der>
s334::s339 s1358<_Cont, s1410, s1412, Der>::s346;
template <class _Cont, class s1301, class Der>
s311<_Cont, s1301, Der>::s311( s262* s300, s272* ns_, const s263* ast_ )
: s324( s300, ns_, ast_ ){}
template <class _Cont, class s1301, class Der, class s1570>
s1390<_Cont, s1301, Der, s1570>::s1390( s262* s300, s272* ns_, const s263* ast_ )
: s311<_Cont, s1301, Der>( s300, ns_, ast_ ){}
template <class _Cont, class s1301, class Der>
s1564<_Cont, s1301, Der>::s1564( s262* s300, s272* ns_, const s263* ast_ )
: s1390<_Cont, s1301, Der, s1301>( s300, ns_, ast_ ){}
template <class _Cont, class s1410, class s1412, class Der>
s1358<_Cont, s1410, s1412, Der>::s1358( s262* s300, s272* ns_, const s263* ast_ )
: s311<_Cont, s1410, Der>( s300, ns_, ast_ ){}
#define DR ((s482*)*(s274 + 1))
#define PARN(n)((s482*)*(s274 + n))
template<class _Cont, class s1301, class Der>
s1135
s311<_Cont, s1301, Der>::s1415( s481* p, Der** pv ){
s383* pr = NULL;
if( p->s350() == s1404 ) {
pr = (s383*)p;
*pv = (Der*)pr->s813();}
else
*pv = ( (Der*)p );
s1135 rp;
if( pr ) {
rp = pr->s1185( *pv );}
else
rp = (*pv)->s1185();
return rp;}
template<class _Cont, class s1301, class Der>
std::pair<typename _Cont::iterator, typename _Cont::iterator> 
s311<_Cont, s1301, Der>::s1413( s481* p, Der* pv ){
using s1121 = Der;
using s933 = typename Der::s1130;
s383* pr = NULL;
if( p->s350() == s1404 ) {
pr = (s383*)p;
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)p );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
return std::make_pair( s1508, s1509 );}
template<class _Cont, class s1301, class Der>
void s311<_Cont, s1301, Der>::s326( s481** s274, size_t n ){
using s1121 = Der;//s1158;
s1121* pv = ( (s1121*)s274[1] );
*( (s344*)*s274 )->s355() = (int)pv->s347.size();}
template<class _Cont, class s1301, class Der>
void s311<_Cont, s1301, Der>::s328( s481** s274, size_t n ){
using s1121 = Der;//s1158;
s1121* pv = ( (s1121*)s274[1] );
pv->s347.clear();}
template<class _Cont, class s1301, class Der>
s1135 s311<_Cont, s1301, Der>::s1185(){
return std::make_pair( s1176(), s1180() );}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1244( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
if( ((s324*)pv)->s1129() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
std::reverse( s1508, s1509 );
*s274 = pv;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1581( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
if( ((s324*)pv)->s1129() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
std::mt19937 s1642(std::random_device{}());
std::shuffle( s1508, s1509, s1642 );
*s274 = pv;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s2079( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
if( ( (s324*)pv )->s1129() < 1 )
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
std::unique( s1508, s1509 );
*s274 = pv;}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1935( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der *pv = NULL, *pv1 = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
s1135 rp1 = s311<_Cont, s1301, Der>::s1415( s274[2], &pv1 );
s1562<s1301> s1955;
typename _Cont::iterator s1508, s1509, vbeg1, vend1;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
vbeg1 = rp1.first.s15<s933*>()->s1136();
vend1 = rp1.second.s15<s933*>()->s1136();
auto s1934 = std::mismatch( s1508, s1509, vbeg1, vend1, s1955 );
if( s1934.first == s1509 )
s274[0] = new s344( pv->s300, (int)std::distance( s1508, s1509 ) );
else {
auto coinc1 = s1934.first;
++coinc1;
s933 it( pv->s300, pv, s1934.first, coinc1 );
s274[0] = pv->s1181( &it );}}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s2073( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der *pv = NULL, *pv1 = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
s1135 rp1 = s311<_Cont, s1301, Der>::s1415( s274[2], &pv1 );
s1291<s1301> s2076;
typename _Cont::iterator s1508, s1509, vbeg1, vend1;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
vbeg1 = rp1.first.s15<s933*>()->s1136();
vend1 = rp1.second.s15<s933*>()->s1136();
bool s153 = std::includes( s1508, s1509, vbeg1, vend1, s2076 );
*((s358*)*s274)->s355() = s153;}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1202( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = ( (Der*)s274[1] );
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s1954;
s1954.s853 = s1197;
typename _Cont::iterator s1203 = std::max_element( s1508, s1509, s1954);
*s274 = (s481*)pv->s1960( &pv, s1203 );}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1201( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
if( s1508 == s1509 )
s274[0] = new s344( pv->s300, -1 );
else {
auto s1203 = std::max_element( s1508, s1509, pv->s1315 );
auto me1 = s1203;
++me1;
s933 it( pv->s300, pv, s1203, me1 );
s274[0] = pv->s1181( &it );}}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s2075( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = ( (Der*)s274[1] );
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s1954;
s1954.s853 = s1197;
typename _Cont::iterator s1203 = std::min_element( s1508, s1509, s1954);
*s274 = (s481*)pv->s1960( &pv, s1203 );}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s2074( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
if( s1508 == s1509 )
s274[0] = new s344( pv->s300, -1 );
else {
auto s2227 = std::min_element( s1508, s1509, pv->s1315 );
auto me1 = s2227;
++me1;
s933 it( pv->s300, pv, s2227, me1 );
s274[0] = pv->s1181( &it );}}
template<class _Cont, class s1410, class s1412, class Der>
void s1358<_Cont, s1410, s1412, Der>::s1202( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1203 = std::max_element( s1508, s1509, pv->s1444 );
auto tmp = std::make_pair( s1203->first, s1203->second );
*s274 = (s481*)pv->s1325( tmp );}
template<class _Cont, class s1410, class s1412, class Der>
void s1358<_Cont, s1410, s1412, Der>::s2075( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1203 = std::min_element( s1508, s1509, pv->s1444 );
auto tmp = std::make_pair( s1203->first, s1203->second );
*s274 = (s481*)pv->s1325( tmp );}
template<class _Cont, class s1410, class s1412, class Der>
void s1358<_Cont, s1410, s1412, Der>::s2073( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121 *pv, *s2077;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s1135 rp;
if( pr )
rp = pr->s1185( pv );
else
rp = pv->s1185();
if( s274[2]->s350() == s1404 ) {
pr = (s383*)s274[2];
s2077 = (s1121*)pr->s813();}
else
s2077 = ( (s1121*)s274[2] );
s1135 s2078;
if( pr )
s2078 = pr->s1185( s2077 );
else
s2078 = s2077->s1185();
typename _Cont::iterator s1508, s1509, s2080, s2081, cur;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
s2080 = s2078.first.s15<s933*>()->s1136();
s2081 = s2078.second.s15<s933*>()->s1136();
cur = s2080;
/*bool s153 = true;
for( ; cur < s2081; ++cur ) {
auto it = pv->s347.find( cur->first );
if( it != pv->s347.end() || it->second != cur->second ) {
s153 = false;
break;}
}*/
bool s153 = std::includes( s1508, s1509, s2080, s2081 );
*((s358*)*s274)->s355() = s153;}
struct s834{
std::vector<s483>s855;
s486 s853;
s834( s486 s854 ) : s853( s854 ) { s855.resize( 2 ); }
virtual bool operator()( const s483 l, const s483 r ){
s855[0] = l;
s855[1] = r;
s853->s594( s855 );
return (bool)*s853->s495( 0, 0 );}
};
class s357;
class s1566;
class s357
: public s1390<s1565, wchar_t, s357, s1561>{
typedef s1565 s1375;
typedef s357 s1158;
static s339 s346;
std::vector<s483> s274;
static void s1227( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1580( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s1675( s481** s274, size_t n );
static void s2140( s481** s274, size_t n );
static void s386( s481** s274, size_t n );
static void s391( s481** s274, size_t n );
static void s788( s481** s274, size_t n );
static void s1583( s481** s274, size_t n );
static void s2245( s481** s274, size_t n );
static void s2223( s481** s274, size_t n );
static void s2225( s481** s274, size_t n );
static void s884( s481** s274, size_t n );
static void s885( s481** s274, size_t n );
static void s1576( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s793( s481** s274, size_t n );
static void s2190( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s397( s481** s274, size_t n );
static void s398( s481** s274, size_t n );
static void s399( s481** s274, size_t n );
static void s400( s481** s274, size_t n );
static void s401( s481** s274, size_t n );
static void s411( s481** s274, size_t n );
static void s1951( s481** s274, size_t n );
static void s1950( s481** s274, size_t n );
static void s407( s481** s274, size_t n );
static void s1472( s481** s274, size_t n );
static void s1027( s481** s274, size_t n );
static void s1337( s481** s274, size_t n );
static void s410( s481** s274, size_t n );
static void s1479( s481** s274, size_t n );
static void s2189( s481** s274, size_t n );
static void s2231( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
public:
typedef s1566 s1130;
s357( const s357&, const s263* ast_ = NULL );
s357( s262* s300, s272* s586, const std::vector<s271*>& l, const s263* ast_ = NULL );
s357( s262* s300, const std::wstring& s = std::wstring( L"" ), s272* s586=NULL, const s263* ast_ = NULL );
s357( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
virtual ~s357();
s481* s352( const s263& s695, s272* s586, 
const std::wstring& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, 
const s263* ast_ ) const override;
size_t s1129() const override { return 2; }
s1054 s1179( const std::wstring& s1541, 
const std::vector<s483>& l ) const override;
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
s1561 operator[]( size_t n ) { return s1561( s300, s347[n] ); }
s1054 s317() const override { return s315; }
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
Iterator* s1155( const s481* idx ) override;
Iterator* s1174( const s481* s347 ) override;
s481* s1181( Iterator* it ) override;
s271* s1325( wchar_t el ) { return new s1561( s300, el ); }
s1375* s355() { return &s347; }
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
void* addr() override { return (void*)&s347; }
operator bool() const override { return !s347.empty(); }
operator int() const override;
operator double() const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void s1945( s1890& s ) override;
void s1944( Stream* ) override;
s1312 to_bytes() const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s357 TDString;
class s811
: public s589{
s483 s757, s717;
s483 s802, s795;
size_t s714, nTo;
int s787, s734;
s1::s9<s357> str;
enum s736 { s713, s768, s758, s810 };
public:
enum s1132{ s1217, s1224, s1216, s1220, s1210, s1206 };
s811( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s811( s262* s300 );
s1890& s299() const override { return s753; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s357;
class s314;
class s744;
class s952;
class s1282;
class s322;
class s1371;
class s2204;
class s2237;
typedef std::vector<s483> s1407;
typedef std::vector<s483> s1406;
typedef s1312 s1364;
typedef std::map<s484, s484, s1414> s1376;
typedef std::unordered_map<s484, s484, s319, s2292> s1370;
typedef std::set<s483, s1414> s2203;
typedef std::unordered_set<s483, s319, s321> s2236;
class s1116
: public Iterator{
protected:
bool s878;
public:
s1116() : s878( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s878;  }
};
class s1128
: public s1116{
public:
};
class s957 
: public s1128{
typedef s1407::iterator s933;
typedef s1407::reverse_iterator s1237;
s1::s9<s314> v;
s933 s1205;
s933 s1079;
s1237 s1248;
s1237 s1477;
uint64_t s1204;
s1::s9<s1518> s1164;
s1::s9<s952> s1163;
public:
s957( s957* it );
s957( s262* s300, s314* v_, s933 it, s933 sent );
s957( s262* s300, s314* v_, s1237 it, s1237 sent );
virtual ~s957() {}
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s933 s1136() { return s1205; }
s1237 s1137() { return s1248; }
s1054 ValType() const override;
virtual bool operator==( const Iterator* r ) const override;
virtual bool operator<( const Iterator* r ) const override;
};
class s954
: public Iterator{
typedef s1406::iterator s933;
s1::s9<s744> v;
s933 s1205;
s933 s1079;
uint64_t s1204;
s1::s9<s1518> s1164;
public:
s954( s954* it );
s954( s262* s300, s744* v_, s933 it, s933 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s933 s1136() { return s1205; }
s1054 ValType() const override;
};
class s932
: public s1116{
typedef s1376::iterator s933;
typedef s1376::reverse_iterator s1237;
s1::s9<s322> v;
s933 s1205;
s933 s1079;
s1237 s1248;
s1237 s1477;
s483 s1164;
s1::s9<s952> s1163;
public:
s932( s932* it );
s932( s262* s300, s322* v_, s933 it, s933 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s933 s1136() { return s1205; }
void reverse() override;
s1054 s317() const override;
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1372
: public Iterator{
typedef s1370::iterator s933;
s1::s9<s1371> v;
s933 s1205;
s933 s1079;
s483 s1164;
s1::s9<s952> s1163;
public:
s1372( s1372* it );
s1372( s262* s300, s1371* v_, s933 it, s933 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s933 s1136() { return s1205; }
s1054 s317() const override;
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s2205
: public s1116{
typedef s2203::iterator s933;
typedef s2203::reverse_iterator s1237;
s1::s9<s2204> v;
s933 s1205;
s933 s1079;
s1237 s1248;
s1237 s1477;
public:
s2205( s2205* it );
s2205( s262* s300, s2204* v_, s933 it, s933 sent );
s2205( s262* s300, s2204* v_, s1237 it, s1237 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s933 s1136() { return s1205; }
s1237 s1137() { return s1248; }
void reverse() override;
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s2238
: public Iterator{
typedef s2236::iterator s933;
s1::s9<s2237> v;
s933 s1205;
s933 s1079;
public:
s2238( s2238* it );
s2238( s262* s300, s2237* v_, s933 it, s933 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s933 s1136() { return s1205; }
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
};
class s1566
: public s1128{
typedef s1565::iterator s933;
typedef s1565::reverse_iterator s1237;
s1::s9<s357> v;
s933 s1205;
s933 s1079;
s1237 s1248;
s1237 s1477;
uint64_t s1204;
s1::s9<s1518> s1164;
s1::s9<s952> s1163;
public:
s1566( s1566* it );
s1566( s262* s300, s357* v_, s933 it, s933 sent );
s1566( s262* s300, s357* v_, s1237 it, s1237 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s933 s1136() { return s1205; }
s1237 s1137() { return s1248; }
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1283
: public s1128{
typedef s1364::iterator s933;
typedef s1364::reverse_iterator s1237;
s1::s9<s1282> v;
s933 s1205;
s933 s1079;
s1237 s1248;
s1237 s1477;
uint64_t s1204;
s1::s9<s1518> s1164;
s1::s9<s952> s1163;
public:
s1283( s1283* it );
s1283( s262* s300, s1282* v_, s933 it, s933 sent );
s1283( s262* s300, s1282* v_, s1237 it, s1237 sent );
bool s1964() const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
void reverse() override;
s933 s1136() { return s1205; }
s1237 s1137() { return s1248; }
s1054 ValType() const override;
bool operator==( const Iterator* r ) const override;
bool operator<( const Iterator* r ) const override;
};
class s1134
: public s334{
s483 s586;
s1::s1279<Iterator> s347;
s1054 s315;
s1054 s323;
static s339 s346;
void s348() override;
const s339& s340() const override { return s346; }
static void s396( s481** s274, size_t n );
static void s1965( s481** s274, size_t n );
static void s1577( s481** s274, size_t n );
static void s2250( s481** s274, size_t n );
static void s1732( s481** s274, size_t n );
static void s401( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
public:
s1134( s262* s300 ) : s334( s300, NULL, NULL ), s323(0) {}
s1134( s262* s300, s1890& s77, const s263* ast_ = NULL );
s1134( const s1134& right, const s263* ast_ = NULL );
s1134( s262* s300, s272* context, Iterator* it, const s263* ast_ = NULL );
virtual ~s1134() {}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
void s498( const s272* s873, bool ) override;
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
s1054 s317() const { return s315;  }
s1054 ValType() const { return s323;  }
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
void operator=( const s1134& p );
bool operator==( const s481* p )  const override;
bool operator<( const s481* p )  const override;
operator bool() const override;
void* addr() override { return (void*)&s347; }
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s957;
class s1283;
class s314
: public s1564<s1407, s483, s314>{
s314( const s314& right ) :s1564( 0, 0, 0 ) {
throw; }
protected:
typedef s1407 s1375;
typedef s314 s1158;
static s339 s346;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1254( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1304( s481** s274, size_t n );
static void s386( s481** s274, size_t n );
static void s391( s481** s274, size_t n );
static void s388( s481** s274, size_t n );
static void s331( s481** s274, size_t n );
static void s796( s481** s274, size_t n );
static void s327( s481** s274, size_t n );
static void s1874( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s1731( s481** s274, size_t n );
void s962( s1890& s818, const s1706& tbfr, s272* s586, const s263* ast_	 );
void s348() override;
const s339& s340() const override { return s346; }
void s1151( s1890& s77, s272* s586, const s6::s1681& s1745 );
void s1303( const std::vector<s271*>& v, s272* s586 );
public:
enum s1132 { s1741, s1739, s1737, s1735, s1736, s1738,
s1828 };
typedef s957 s1130;
s314( s262* s300 ) : s1564( s300, NULL, NULL ) {}
s314( s262* s300, s272* s586, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1681& s1745 = s1722 );
s314( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL, s1054 s703 = 0, s1054 s1266 = 0 );
s314( const s314& right, s272* ns, const s263* ast_ );
s314( s262* s300, s1054 s323, s272* s586, const s263* ast_ = NULL );
virtual ~s314() override;
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
static bool s2211( s324* s1161, s1054 s2218, s1054& pt, s1054& vt, 
std::wstring& sv, const s263& s695, s272* s586, s1890& s332 );
static s1054 s1186( s271* s1161, s1890& s1263, s1054 s2218, s807::Cont& s586 );
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
size_t s1129() const override { return 2; }
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
static void load( s271* s1161, s1054 s2218, s1890& s77, s272* s586, const s6::s1681& s1745,
s1054& pt, s1054& vt, const std::function<void( s484 )> );
void s498( const s272* s873, bool fr=true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
s481* s1525( const s481* p ) const override;
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
s483 operator[]( size_t n ) { return s347[n]; }
const s483& operator[]( size_t n ) const { return s347[n]; }
s1054 s317() const override { return s315; }
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
Iterator* s1155( const s481* idx ) override;
Iterator* s1174( const s481* s347 ) override;
s481* s1181( Iterator* it ) override;
void clear() { s347.clear(); }
void add( s482* el );
void erase( size_t n ) { s347.erase( begin( s347 ) + n ); }
size_t size() const { return s347.size(); }
s481* sort( bool reverse, s834* cmp ) override;
std::vector<s483>& s318() { return s347; }
const std::vector<s483>& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s744
: public s324{
protected:
typedef s1406 s1375;
static s339 s346;
s1375 s347;
s1375::iterator s316;
std::wstring s497;
static void s385( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1304( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s327( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s329( s481** s274, size_t n );
static void s995( s481** s274, size_t n );
static void s1068( s481** s274, size_t n );
static void s1731( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
void s1151( s1890& s77, std::wstring& s1263, std::wstring& s642,
std::vector<s1::s9<s6::s141>>& s94, const s263* ast_, 
const s6::s1681& s1745 );
public:
s744( s262* s300 )
: s324( s300, NULL, NULL ) {}
s744( s262* s300, s272* s586, const s263* ast_ )
: s324( s300, s586, ast_ ) {}
s744( s262* s300, s272* s586, const std::wstring& s77,
const s263* ast_ = NULL, const s1706& tbfr=s1724 );
s744( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s744( const s744& right );
virtual ~s744() override;
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s1054 s317() const override;
s1054 s931() const override { return Types.Int; }
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
size_t s1129() const override { return 2; }
s484 s495( s481** s274 = NULL, size_t s496 = 0 ) override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
s483 operator[]( size_t n ) { return s347[n]; }
const s483& operator[]( size_t n ) const { return s347[n]; }
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
s1135 s1185() override;
void clear() { s347.clear(); }
void add( s483 el ) { s347.push_back( el ); }
void assign( const std::vector<s483>& v );
size_t size() const { return s347.size(); }
std::vector<s483>& s318() { return s347; }
const std::vector<s483>& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s952
: public s744{
static s339 s346;
void s348() override;
const s339& s340() const override { return s346; }
void s1151( s1890& s77, s272* s586, const s6::s1681& s1745 );
virtual void s1149( s1890& s1263 );
static void s1227( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1255( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1304( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s327( s481** s274, size_t n );
static void s328( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s329( s481** s274, size_t n );
static void s995( s481** s274, size_t n );
static void s1068( s481** s274, size_t n );
public:
s952( s262* s300 ) : s744( s300 ) {}
s952( s262* s300, s272* s586, s1890& s77, const s263* ast_ = NULL,
const s6::s1681& s1745 = s1722 );
s952( s262* s300, s272* s586, const std::vector<s271*>& l, 
const s263* ast_ = NULL, s1054 s703 = 0 );
s952( const s952& right, const s263* ast_ = NULL );
virtual ~s952() override {}
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
void s498( const s272* s873, bool fr=true ) override;
s1054 s1186( s1890& s1263, s807::Cont& s586 );
void load( s1890& s77, s272* s586, const s6::s1681& s1745 );
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
bool operator<( const s481* p ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
static bool s2162( s1890& s );
};
class s1282
: public s1390<s1364, tdbyte_t, s1282, s1285>{
protected:
typedef s1364 s1375;
typedef s1282 s1158;
static s339 s346;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1254( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1304( s481** s274, size_t n );
static void s327( s481** s274, size_t n );
static void s396( s481** s274, size_t n );
static void s1328( s481** s274, size_t n );
static void s1344( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
void s1151( s1890& s77,
s481* s586, const s6::s1681& s1745 );
public:
typedef s1283 s1130;
s1282( s262* s300 ) : s1390( s300, NULL, NULL ) {}
s1282( s262* s300, s272* s586, const std::wstring& s77, const s263* ast_ = NULL,
const s6::s1681& s1745=s1722 );
s1282( s262* s300, const std::vector<s271*>& l, const s263* ast_ = NULL );
s1282( const s1282& right, const s263* ast_ = NULL );
virtual ~s1282() override;
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
size_t s1129() const override { return 2; }
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
void load( s1890& s77, s481* s586, const s6::s1681& s1745 );
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
tdbyte_t operator[]( size_t n ) { return s347[n]; }
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
Iterator* s1155( const s481* idx ) override;
Iterator* s1174( const s481* s347 ) override;
s271* s1325( tdbyte_t el ) { return new s1285( s300, el ); }
s481* s1181( Iterator* it ) override;
void clear() { s347.clear(); }
void add( tdbyte_t el ) { s347.push_back( el ); }
void erase( size_t n ) { s347.erase( begin( s347 ) + n ); }
size_t size() const { return s347.size(); }
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s2204;
class s2204
: public s1564<s2203, s483, s2204>{
protected:
typedef s2203 s1375;
typedef s2204 s1158;
static s339 s346;
s1375::iterator s316;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s2228( s481** s274, size_t n );
static void s330( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
void s1151( s1890& s77, s272* s586, const s6::s1681& s1745 );
void s1303( const std::vector<s271*>& v, s481* s586 );
public:
typedef s2205 s1130;
s2204( s262* s300 ) : s1564( s300, NULL, NULL ) { }
s2204( s262* s300, s272* s586, s1890& s77, const s263* ast_ = NULL,
const s6::s1681& s1745 = s1722 );
s2204( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL, s1054 s703 = 0, s1054 s1266 = 0 );
s2204( const s2204& right, s272* ns, const s263* ast_ );
s2204( s262* s300, s1054 s323, s272* s586, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s481* s1525( const s481* p ) const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
size_t s1129() const override { return 1; }
void s498( const s272* s873, bool fr = true ) override;
void load( s1890& s77, s272* s586, const s6::s1681& s1745 );
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s2237;
class s2237
: public s1564<s2236, s483, s2237>{
protected:
typedef s2236 s1375;
typedef s2237 s1158;
static s339 s346;
s1375::iterator s316;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s2228( s481** s274, size_t n );
static void s330( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
void s1303( const std::vector<s271*>& v, s481* s586 );
public:
typedef s2238 s1130;
s2237( s262* s300 ) : s1564( s300, NULL, NULL ) { }
s2237( s262* s300, s272* s586, s1890& s77, const s263* ast_ = NULL,
const s6::s1681& s1745 = s1722 );
s2237( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL, s1054 s703 = 0, s1054 s1266 = 0 );
s2237( const s2237& right, s272* ns, const s263* ast_ );
s2237( s262* s300, s1054 s323, s272* s586, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s481* s1525( const s481* p ) const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
size_t s1129() const override { return 1; }
void s498( const s272* s873, bool fr = true ) override;
void load( s1890& s77, s272* s586, const s6::s1681& s1745 );
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s314 TDVector;
class s322;
class s322
: public s1358<s1376, s484, s484, s322>{
protected:
typedef s1376 s1375;
typedef s322 s1158;
static s339 s346;
s1375::iterator s316;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s1618( s481** s274, size_t n );
static void s330( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1452( s481** s274, size_t n );
static void s2199( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1580( s481** s274, size_t n );
static void s331( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s329( s481** s274, size_t n );
virtual void s348() override;
virtual const s339& s340() const override { return s346; }
virtual void s1151( const std::wstring& s77, std::wstring& s1263, std::wstring& s642,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
void s1303( const std::vector<s271*>& v, s481* s586 );
public:
typedef s932 s1130;
s322( s262* s300 ) : s1358( s300, NULL, NULL ) {}
s322( s262* s300, s1054 s1192, s1054 s1266, s1054 s1172,
s1054 s703, s272* s586, const s263* ast_ = NULL );
s322( const s322& right, const s263* ast_ = NULL );
s322( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL, s1054 s703 = 0, s1054 s1172 = 0,
s1054 s1626 = 0, s1054 s1266 = 0);
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
static bool s2211( s324* s1161, s1054 s2218, s1054& pt, s1054& et, s1054& vt, 
s1054& kt, std::wstring& sv, const s263& s695, s272* s586, s1890& s332 );
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
static s1054 s1186( s271* s1161, s1890& s1263, s1054 s2218, s807::Cont& s586,
s1054& et, s1054& kt, s1054& vt );
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
size_t s1129() const override { return 1; }
void s498( const s272* s873, bool fr=true ) override;
static void s2209( s271* s1161, s1890& s77, s272* s586, s1054& kt, s1054& vt, 
const std::function<void( std::pair<s484, s484> )> );
static void load( s271* s1161, s1890& s77, s272* s586, s1890& s72, s1054& kt, s1054& vt, 
const std::function<void( std::pair<s484, s484> )> );
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
static void s2213( s271* subj, Stream*, Iterator* );
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1371;
class s1371
: public s1358<s1370, s484, s484, s1371>{
protected:
typedef s1370 s1375;
typedef s1371 s1158;
static s339 s346;
s1375::iterator s316;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s330( s481** s274, size_t n );
static void s774( s481** s274, size_t n );
static void s325( s481** s274, size_t n );
static void s1452( s481** s274, size_t n );
static void s385( s481** s274, size_t n );
static void s1580( s481** s274, size_t n );
static void s331( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s329( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
virtual void s1151( const std::wstring& s77, std::wstring& s1263, std::wstring& s642,
std::vector<std::pair<std::wstring, s6::s142>> s144, const s263* ast_ );
public:
typedef s1372 s1130;
s1371( s262* s300 ) : s1358( s300, NULL, NULL ) {}
s1371( s262* s300, s1054 s1192, s1054 s1266, s1054 s1172,
s1054 s703, s272* s586, const s263* ast_ = NULL );
s1371( const s1371& right, const s263* ast_ = NULL );
s1371( s262* s300, const std::vector<s271*>& l, s272* s586,
const s263* ast_ = NULL, s1054 s703 = 0, s1054 s1172 = 0,
s1054 s1626 = 0, s1054 s1266 = 0 );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s1054 s1186( const std::wstring& s1263, s807::Cont& s586 );
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s347; }
s1054 s1179( const std::wstring& s1541, const std::vector<s483>& l ) const override;
size_t s1129() const override { return 0; }
void s498( const s272* s873, bool fr=true ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
Iterator* s312( s383* r ) override;
Iterator* s1176() override;
Iterator* s1180() override;
s1375& s318() { return s347; }
const s1375& s318() const { return s347; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s1920( Stream* ) const override;
virtual void s304( std::wostream* pd, int s197 = 0 ) const override;
};
typedef s322 TDIndex;
class s952;
class s383;
class s314;
class s602
: public s589{
std::vector<s1054> types;
std::vector<s486> s647;
public:
s602( s262* s300, s272* s586, s589* s585, s561 ct,
const std::vector<s271*>& l, const s263* s695 );
void s646( s1054 type, s589* pOvr );
virtual s484 s495( s481** s274, size_t s496 ) override;
};
class s832
: public s589{
std::vector<s1054> s1888;
bool s2089;
s1::s9<s952> s2095;
s481* s1881( s481** s274, size_t s496 ) override;
s832( const s832& );
public:
s832( s262* s300 );
s832( s262* s300, s272* s590, s589* s591, 
const std::vector<s271*>& l, const s263* s695, s1054 s2106 = 0, bool s2089 = true, bool s2159 = true );
s832( s262* s300, s272* s590, const std::vector<s1054>& l, 
s1054 pt, const s263* s695 );
s832( s832& s1886, s272* s590, s589* s591, const std::vector<s483>& l, const s263* s695 );
std::wstring s828() const override;
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s484 s495( s481** s274, size_t s496 ) override;
void s498( const s272* s1658, bool proc ) override;
s481* s494() override { return this; }
s1054 s1318() const { return s1888.back(); }
s483 s2284() override;
s271* s333( s589* s2042, s272* impl ) const override;
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
void s2210( const s272* s1658, bool proc );
using s481::s353;
using s481::s1880;
s481* s353( s272* s586, const std::vector<s1054>& vt ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l,
const s263* ast_ ) const override;
s589* s1671( s1890& s278, s589* s215,	s272* s586, s559* cs ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
std::wstring trace( s1890& topics ) const override;
};
class s833
: public s589{
bool s2233;
public:
s833( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695, bool s2159 = true );
s833( const s833& right, s272* s590, s589* s591 );
s1890& s299() const override { return s846; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s890
: public s589{
int code;
public:
s890( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s604
: public s589{
public:
s604( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s2062
: public s589{
public:
s2062( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s605
: public s589{
public:
s605( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l,
const s263* s695, bool s2159 = true );
s605( s262* s300 );
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1396
: public s589{
s369 s1491;
s484 varval;
s483 s308;
s369 s309;
s1518 s310;
s483 lambda;
public:
s1396( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695, bool s2159 );
s1396( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1924
: public s589{
public:
s1924( s262* s300, s272* s586, s589* s585, std::vector<s271*>& l, 
const s263* s695 );
s1924( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s2193
: public s589{
s483 s2197;
s484 s978;
s1::s9<s383> range;
s483 where, s1063;
s1::s9<s314> s681;
public:
enum s1132 { s1226 };
s2193( s262* s300, s272* s586, s589* s585, std::vector<s271*>& l, 
const s263* s695 );
s2193( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
/*
class s2206
: public s589,
public Iterator{
public:
s2206( s262* s300, s272* s590, s589* s591, s272* ns_, s561 ct,
s1890& s672, const s263* s695, bool s1713 = false, bool _bd = true );
s2206( s262* s300, s272* s586, s589* s585, s272* ns_, s561 ct,
const std::vector<s271*>& l, const s263* s695, bool s1713, bool _bd );
s2206( const s2206& right, s272* s586, s589* s585, s272* ns_, 
const std::vector<s271*>& s274, const s263* s695, bool s2105=false, 
bool _bd=true );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
s271* s313() override;
s271* s955() override;
const s271* s955() const override;
s271* Idx() override;
s271* El() override;
s1054 ValType() const override { return s323; }
bool s1964() const override;
};
*/
class s606
: public s589{
s577 s618;
std::vector<s577> s619;
public:
enum s1132{ s1214, s1215 };
s606( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695,
bool s2159 = true );
s606( const s606& right, s272* s586, s589* s585 );
void s498( const s272* s1658, bool proc ) override;
void s730( bool proc );
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
};
class s609
: public s589{
s359 s78;
public:
s609( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s609( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s611
: public s589{
public:
s611( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s611( s262* s300 );
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s610
: public s589{
s369 s76;
s359 s617;
s1::s9<s611> ctch;
public:
s610( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s610( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s749
: public s589{
std::vector<std::wstring> fields;
public:
s749( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1666
: public s589{
public:
typedef s481* (s272::*s1668)(s481**, size_t);
private:
s1668 s1670;
s483 subject;
public:
s1666( s262* s300, s272* s586, s589* s585, s1668 _ptr,
s559* cs, const s263* s695 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1667
: public s589{
public:
typedef s481* (s481::*s1669)(s481**, size_t);
private:
s1669 s1670;
s1::s9<s369> s2286;
s483 s2287;
public:
s1667( s262* s300, s272* s586, s589* s585, s1669 _ptr,
const std::vector<s271*>& s274, s1890& s672, s1054 s1065, const s263* s695, bool s2159 );
s1667( const s1667&, s272* s586, s589* s585 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
};
class s1597
: public s589{
s484 cmd;
std::thread s817;
public:
s1597( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1597( const s1597& );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1595
: public s589{
public:
s1595( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1595( const s1595& r, s272* s590, s589* s591 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1592
: public s589{
public:
s1592( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695, bool s2160 );
s1592( const s1592& right, s272* s590, s589* s591 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1596
: public s589{
public:
s1596( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1596( const s1596& );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1591
: public s589{
s1591( const s1591& q):s589(q){ throw; }
public:
s1591( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695,
bool s2159 );
s1591( const s1591& right, s272* s586, s589* s585 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1870
: public s589{
public:
s1870( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1870( const s1870& );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s607
: public s589{
s483 s42;
bool lout;
public:
enum s1132{ s1224, s1458, s1578, s1952, s1953, s1559, s1918, s1902, 
s1904, s1905, s1903, s1917, s1557, s1558 };
s607( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695,
bool s2159 = false );
s607( const s607& right, s272* s586, s589* s585 );
s607( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;	
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
};
class s1925
: public s589{
s483 source;
bool lin;
public:
enum s1132{ s1217, s1952, s1953, s1559, s1918, s1917 };
s1925( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1925( s262* s300 );
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
template<class _Cont, class s1301, class Der>
s1134* s311<_Cont, s1301, Der>::s1960( Der** pv, typename _Cont::iterator& s1966 ){
typename _Cont::iterator s1579 = s1966;
if( s1966 != (*pv)->s347.end() )
++s1579;
s1134* s681 = new s1134( (*pv)->s300, (*pv)->ns,
new typename Der::s1130( (*pv)->s300, *pv, s1966, s1579 ), NULL );
s681->s498( (*pv)->ns, true );
return s681;}
template <class _Cont, class s1301, class Der>
void s311<_Cont, s1301, Der>::s348(){
s300->TR().s1153( s491, s7::s1400, s1501::s1496 );
s346.insert( std::make_pair( L"size", new s335( L"size", &s311<_Cont, s1301, Der>::s326, s1142,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"clear", new s335( L"clear", &s311<_Cont, s1301, Der>::s328, s1143,
{ s1113() }, 0, 0, false ) ) );}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s348(){
s311<_Cont, s1301, Der>::s348();
s346 = s311<_Cont, s1301, Der>::s340();
s346.insert( std::make_pair( L"coincide", new s335( L"coincide", &s1390<_Cont, s1301, Der, s1570>::s1935, s1142,
{ s1113(), s1113( { s1404 } ), s1113( { s7::s1383 } ) }, 0, 1, true,
{L"list:", L":back"}) ) );
s346.insert( std::make_pair( L"max-element", new s335( L"max-element", &s1390<_Cont, s1301, Der, s1570>::s1202,
0, { s1113(), s1113( { s1404 } ), 
s1113( { s1404, s7::s1387 } ),
s1113( { s7::s1387 } ) }, 0, 1 ) ) );
s346.insert( std::make_pair( L"max-element-idx", new s335( L"max-element-idx", &s1390<_Cont, s1301, Der, s1570>::s1201,
s1143, { s1113(), s1113( { s1404 } ) }, 0, 1 ) ) );
s346.insert( std::make_pair( L"min-element", new s335( L"min-element", &s1390<_Cont, s1301, Der, s1570>::s2075,
0, { s1113(), s1113( { s1404 } ), 
s1113( { s1404, s7::s1387 } ),
s1113( { s7::s1387 } ) }, 0, 1 ) ) );
s346.insert( std::make_pair( L"min-element-idx", new s335( L"min-element-idx", &s1390<_Cont, s1301, Der, s1570>::s2074,
s1143, { s1113(), s1113( { s1404 } ) }, 0, 1 ) ) );
s346.insert( std::make_pair( L"is-subset", new s335( L"is-subset", &s1390<_Cont, s1301, Der, s1570>::s2073, s1139,
{ s1113(), s1113( { s1404 } ), s1113( { s7::s1383 } ) }, 0, 1, true ) ) );
s346.insert( std::make_pair( L"sort", new s335( L"sort", &s1390<_Cont, s1301, Der, s1570>::s1257, 0,
{ s1113(), s1113( { s1404 } ) }, 0, 1, false ) ) );
s346.insert( std::make_pair( L"reverse", new s335( L"reverse", &s1390<_Cont, s1301, Der, s1570>::s1244, 0,
{ s1113(), s1113( { s1404 } ) }, 0, 1, false ) ) );
s346.insert( std::make_pair( L"shuffle", new s335( L"shuffle", &s1390<_Cont, s1301, Der, s1570>::s1581, 0,
{ s1113(), s1113( { s1404 } ) }, 0, 1, false ) ) );
s346.insert( std::make_pair( L"unique", new s335( L"unique", &s1390<_Cont, s1301, Der, s1570>::s2079, 0,
{ s1113(), s1113( { s1404 } ) }, 0, 1, true ) ) );
s346.insert( std::make_pair( L"for-each", new s335( L"for-each", &s1390<_Cont, s1301, Der, s1570>::s1731, s1143,
{ s1113(), s1113( { s1404 } ) }, 0, 1, false ) ) );
s346.insert( std::make_pair( L"find-adjacent", new s335( L"find-adjacent", &s1390<_Cont, s1301, Der, s1570>::s1575, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"subseq", new s335( L"subseq", &s1390<_Cont, s1301, Der, s1570>::s1482,
s1404, { s1113( {s1142} ), s1113( { s1142, s1142 } ) }, 1, 2 ) ) );
s346.insert( std::make_pair( L"begin", new s335( L"begin", &s1390<_Cont, s1301, Der, s1570>::s1571, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"end", new s335( L"end", &s1390<_Cont, s1301, Der, s1570>::s1574, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"front", new s335( L"front", &s1390<_Cont, s1301, Der, s1570>::s1623, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"back", new s335( L"back", &s1390<_Cont, s1301, Der, s1570>::s1609, 0,
{ s1113() }, 0, 0 ) ) );
s346.emplace( std::make_pair( L"is-el", new s335( L"is-el", &s1390<_Cont, s1301, Der, s1570>::s2222, s1139,
{ s1113( { s7::s1386 } ) }, 1, 1, true ) ) );
s346.equal_range( L"begin" ).first->second->s1251( true );
s346.equal_range( L"end" ).first->second->s1251( true );
s346.equal_range( L"front" ).first->second->s1251( true );
s346.equal_range( L"back" ).first->second->s1251( true );
s346.equal_range( L"max-element" ).first->second->s1251( true );
s346.equal_range( L"max-element-idx" ).first->second->s1251( true );
s346.equal_range( L"min-element" ).first->second->s1251( true );
s346.equal_range( L"min-element-idx" ).first->second->s1251( true );
s346.equal_range( L"reverse" ).first->second->s1251( true );
s346.equal_range( L"find-adjacent" ).first->second->s1251( true );
s346.equal_range( L"sort" ).first->second->s1251( true );
s346.equal_range( L"shuffle" ).first->second->s1251( true );
s346.equal_range( L"unique" ).first->second->s1251( true );
this->s300->TR().s1153( this->s491, s7::s1400, s1501::s1496 );}
template <class _Cont, class s1301, class Der>
void s1564<_Cont, s1301, Der>::s348(){
s1390<_Cont, s1301, Der, s1301>::s348();
s346 = s1390<_Cont, s1301, Der, s1301>::s340();
s1054 tp = s7::s1387;
s346.insert( std::make_pair( L"sort", new s335( L"sort", &s1564<_Cont, s1301, Der>::s1257, 0,
{ s1113( { s1404 } ), s1113( { s1404, tp } ),
s1113( { tp } ), s1113() }, 0, 2/*, {L":asc", L":desc"}*/ ) ) );
s346.insert( std::make_pair( L"group-by", new s335( L"group-by", &s1564::s1453, 0,
{ s1113( { tp } ) }, 1, 1 ) ) );
if( s346.count( L"front" ) ) s346.erase( L"front" );
s346.insert( std::make_pair( L"front", new s335( L"front", &s1564<_Cont, s1301, Der>::s1623, 0,
{ s1113() }, 0, 0 ) ) );
if( s346.count( L"back") ) s346.erase( L"back" );
s346.insert( std::make_pair( L"back", new s335( L"back", &s1564<_Cont, s1301, Der>::s1609, 0,
{ s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"join", new s335( L"join", &s1564<_Cont, s1301, Der>::s1958, Types.String,
{ s1113( { s1404, Types.String } ), s1113( { Types.String } ) }, 1, 1 ) ) );
if( s346.count( L"is-el" ) ) s346.erase( L"is-el" );
s346.emplace( std::make_pair( L"is-el", new s335( L"is-el", &s1564<_Cont, s1301, Der>::s2222, s1139,
{ s1113( { s7::s1386 } ) }, 1, 1, true ) ) );
s346.equal_range( L"front" ).first->second->s1251( true );
s346.equal_range( L"back" ).first->second->s1251( true );
s346.equal_range( L"sort" ).first->second->s1251( true );
s346.equal_range( L"group-by" ).first->second->s1251( true );
this->s300->TR().s1153( this->s491, s7::s1400, s1501::s1496 );}
template <class _Cont, class s1410, class s1412, class Der>
void s1358<_Cont, s1410, s1412, Der>::s348(){
s311<_Cont, s1410, Der>::s348();
s346 = s311<_Cont, s1410, Der>::s340();
s346.insert( std::make_pair( L"max-element", new s335( L"max-element", &s1358::s1202,
0, { s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"min-element", new s335( L"min-element", &s1358::s2075,
0, { s1113() }, 0, 0 ) ) );
s346.insert( std::make_pair( L"is-subset", new s335( L"is-subset", &s1358::s2073, s1139,
{ s1113( { s7::s1383 } ) }, 1, 1 ) ) );
s346.insert( std::make_pair( L"regroup-by", new s335( L"regroup-by", &s1358::s1474, 0,
{ s1113( { s7::s1387 } ) }, 1, 1 ) ) );
s346.emplace( std::make_pair( L"find", new s335( L"find", &s1358::s774, 0,
{ s1113( { s7::s1385 } ) }, 1, 1, true ) ) );
s346.equal_range( L"max-element" ).first->second->s1251( true );
s346.equal_range( L"min-element" ).first->second->s1251( true );
s346.equal_range( L"regroup-by" ).first->second->s1251( true );
s346.equal_range( L"find" ).first->second->s1251( true );
this->s300->TR().s1153( this->s491, s7::s1400, s1501::s1496 );}
template <class _Cont, class s1301, class Der>
s1054 s311<_Cont, s1301, Der>::
s1179( const std::wstring& s1541, const std::vector<s483>& l ) const{
s1054 s681 = 0;
return s681;}
template <class _Cont, class s1301, class Der, class s1570>
s1054 s1390<_Cont, s1301, Der, s1570>::
s1179( const std::wstring& s1541, const std::vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"begin" || s1541 == L"end" ) {
s807::Cont s1269;
s1054 s1445 = this->s317();
s681 = this->s300->TR().s1039( std::vector<s1054>(
{ s1568, 1, s1445/*s1090*/, 0 } ) );
}
else if( s1541 == L"front" || s1541 == L"back" )
s681 = this->ValType();
else if( s1541 == L"max-element-idx" || s1541 == L"min-element-idx" )
s681 = this->s931();
else if( s1541 == L"sort" || s1541 == L"reverse" || s1541 == L"unique" 
|| s1541 == L"shuffle" )
s681 = this->s350();
else if( s1541 == L"find-adjacent" || s1541 == L"max-element" || 
s1541 == L"min-element") {
s807::Cont s1269;
s1054 s1445 = this->s317();
s681 = this->s300->TR().s1039( std::vector<s1054>( 
{ s1568, 1, s1445/*s1090*/, 0 } ) );
}
else
s681 = s311<_Cont, s1301, Der>::s1179( s1541, l );
return s681;}
template <class _Cont, class s1301, class Der>
s1054 s1564<_Cont, s1301, Der>::
s1179( const std::wstring& s1541, const std::vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"front" || s1541 == L"back" )
s681 = this->ValType();
else if( s1541 == L"sort" )
s681 = this->s350();
else if( s1541 == L"group-by" ) {
s807::Cont s1269;
s1054 s1090 = this->s323;
std::wstring ts = this->s300->TR().s1342( Types( this->s300, Types.Vector )->s351() + L"<" +
this->s300->TR().s798( s1090 ) + L">" );
s1054 s1505 = ((s314*)Types( this->s300, Types.Vector ))->s1186( (s314*)this, ts, s1705, s1269 );
s1054 s1456 = l[0].s15<s832*>()->s1318();
s681 = this->s300->TR().s1039( std::vector<s1054>( 
{ Types.Index, 2, s1456, 0, s1505, 0 } ) );}
else
s681 = s1390<_Cont, s1301, Der, s1301>::s1179( s1541, l );
return s681;}
template <class _Cont, class s1410, class s1412, class Der>
s1054 s1358<_Cont, s1410, s1412, Der>::
s1179( const std::wstring& s1541, const std::vector<s483>& l ) const{
s1054 s681 = 0;
if( s1541 == L"max-element" )
s681 = this->s317();
else if( s1541 == L"regroup-by" ) {
s807::Cont s1269;
s1054 s1090 = this->s323;
s1054 s1456 = l[0].s15<s832*>()->s1318();
s1054 s1445 = this->s300->TR().s1039( std::vector<s1054>( 
{ s1703, 2, s1456, 0, s1090, 0 } ) );
s681 = this->s300->TR().s1039( std::vector<s1054>( 
{ Types.Index, 1, s1445, 0 } ) );}
else if( s1541 == L"find" ) {
s807::Cont s1269;
s1054 s1445 = this->s317();
s681 = this->s300->TR().s1039( std::vector<s1054>( 
{ s1568, 1, s1445, 0 } ) );}
else
s681 = s311<_Cont, s1410, Der>::s1179( s1541, l );
return s681;}
template <class _Cont, class s1410, class s1412, class Der>
s271* s1358<_Cont, s1410, s1412, Der>::s1325( std::pair<s1410, s1412>& el ){
return new s952( this->s300, this->ns, std::vector<s271*>({el.first, el.second}) ); }
template <class _Cont, class s1410, class s1412, class Der>
bool s1358<_Cont, s1410, s1412, Der>::insert( s481* s152, s481* s347 ){
return this->s347.insert( std::make_pair( s152, s347 ) ).second;}
template <class _Cont, class s1410, class s1412, class Der>
s481* s1358<_Cont, s1410, s1412, Der>::find( s481* s152 ){
auto it = this->s347.find( s152 );
if( it != end( this->s347 ) )
return it->second;
return NULL;}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1571( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1134( pv->s300, pv->ns, pv->s1176(), NULL );}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1574( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
*s274 = new s1134( pv->s300, pv->ns, pv->s1180(), NULL );}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1482( s481** s274, size_t s496 ){
if( s496 < 3 || s496 > 4 )
throw new s2::s16( L"subseq: wrong number of arguments" );
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv = ( (s1121*)s274[1] );
int s1480 = (int)*s274[2];
int s1481;
if( s496 == 4 )
s1481 = (int)*s274[3];
else
s1481 = (int)pv->s347.size() - 1;
s383 range( s1480, s1481 );
s1135 pr = range.s1185( pv );
s933* s1475;
if( pv->s1129() >= 1 && pr.first.s15<s1116*>()->Reversed() ) {
typename _Cont::reverse_iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1137();
s1509 = pr.second.s15<s933*>()->s1137();
s1475 = new s933( pv->s300, pv, s1508, s1509 );}
else {
typename _Cont::iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1136();
s1509 = pr.second.s15<s933*>()->s1136();
s1475 = new s933( pv->s300, pv, s1508, s1509 );}
s383* s681 = new s383( pv->s300, pv, s1475 );
*s274 = s681;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1257( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 pr = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
if( ( (s324*)pv )->s1129() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s2217;
s2217.s853 = s1197;
if( pv->s1129() >= 1 && pr.first.s15<s1116*>()->Reversed() ) {
typename _Cont::reverse_iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1137();
s1509 = pr.second.s15<s933*>()->s1137();
std::sort( s1508, s1509, s2217 );}
else {
typename _Cont::iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1136();
s1509 = pr.second.s15<s933*>()->s1136();
std::sort( s1508, s1509, s2217 );}
*s274 = pv;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s774( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s2217;
s2217.s853 = s1197;
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1966 = std::find( s1508, s1509, pv->s1572 );
typename _Cont::iterator s1579 = s1966;
if( s1966 != pv->s347.end() )
++s1579;
s1134* s681 = new s1134( pv->s300, pv->ns,
new s933( pv->s300, pv, s1966, s1579 ), NULL );
s681->s498( pv->ns, true );
*s274 = s681;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1575( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1966 = std::adjacent_find( s1508, s1509, pv->s1572 );
typename _Cont::iterator s1579 = s1966;
if( s1966 != pv->s347.end() )
++s1579;
s1134* s681 = new s1134( pv->s300, pv->ns,
new s933( pv->s300, pv, s1966, s1579 ), NULL );
s681->s498( pv->ns, true );
*s274 = s681;}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s2222( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
s1121* pv;
s383* pr = NULL;
if( s274[1]->s350() == s1404 ) {
pr = (s383*)s274[1];
pv = (s1121*)pr->s813();}
else
pv = ( (s1121*)s274[1] );
s1135 rp;
if( pr ) {
rp = pr->s1185( pv );}
else
rp = pv->s1185();
s1570* s2215 = (s1570*)s274[2];
s1301* el = (s1301*)( (s334*)s2215 )->addr();
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1966 = std::find( s1508, s1509, *el );
*((s358*)*s274)->s355() = ( s1966 != pv->s347.end() );}
template <class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1731( s481** s274, size_t s496 ){
using s1121 = Der;
using s933 = typename Der::s1130;
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
s933* s1508 = rp.first.s15<s933*>(), *s1509 = rp.second.s15<s933*>();
std::vector<s483> s1825( 1 );
while( !( s1508 == s1509 ) ) {
s1825[0] = s1508->s955();
s1749->s594( s1825 );
s1749->s495( 0, 0 );}}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1623( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s347.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
auto it = pv->s347.begin();
*s274 = (s481*)pv->s1325( *it );}
template<class _Cont, class s1301, class Der, class s1570>
void s1390<_Cont, s1301, Der, s1570>::s1609( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s347.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
auto it = pv->s347.end();
--it;
*s274 = (s481*)pv->s1325( *it );}
template<class _Cont, class s1301, class Der>
void s1564<_Cont, s1301, Der>::s1623( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s347.empty() )
throw new s2::s16( L"(front) method was called on an empty container" );
s481* s1053 = NULL;
if( pv->s347.size() ) {
auto it = pv->s347.begin();
s1053 = it->template s15<s481*>();}
*s274 = s1053;}
template<class _Cont, class s1301, class Der>
void s1564<_Cont, s1301, Der>::s1609( s481** s274, size_t n ){
Der* pv = ( (Der*)s274[1] );
if( pv->s347.empty() )
throw new s2::s16( L"(back) method was called on an empty container" );
s481* s1053 = NULL;
if( pv->s347.size() ) {
auto it = pv->s347.end();
--it;
s1053 = ( &( *it ) )->template s15<s481*>();}
*s274 = s1053;}
template <class _Cont, class s1301, class Der>
void s1564<_Cont, s1301, Der>::s1257( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 pr = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
if( ( (s324*)pv )->s1129() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s1954;
if( s1197 )
s1954.s853 = s1197;
if( pv->s1129() >= 1 && pr.first.s15<s1116*>()->Reversed() ) {
typename _Cont::reverse_iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1137();
s1509 = pr.second.s15<s933*>()->s1137();
std::sort( s1508, s1509, s1954 );}
else {
typename _Cont::iterator s1508, s1509;
s1508 = pr.first.s15<s933*>()->s1136();
s1509 = pr.second.s15<s933*>()->s1136();
std::sort( s1508, s1509, s1954 );}
*s274 = pv;}
template <class _Cont, class s1301, class Der>
void s1564<_Cont, s1301, Der>::s774( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = NULL;
s1135 rp = s311<_Cont, s1301, Der>::s1415( s274[1], &pv );
if( ( (s324*)pv )->s1129() < 2 )
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );
s589* s1197 = NULL;
if( s496 == 3 )
s1197 = (s589*)s274[2];
s1291<s1301> s1954;
if( s1197 )
s1954.s853 = s1197;
typename _Cont::iterator s1508, s1509;
s1508 = rp.first.s15<s933*>()->s1136();
s1509 = rp.second.s15<s933*>()->s1136();
typename _Cont::iterator s1966 = std::find( s1508, s1509, pv->s1572 );
typename _Cont::iterator s1579 = s1966;
if( s1966 != pv->s347.end() )
++s1579;
s1134* s681 = new s1134( pv->s300, pv->ns,
new s933( pv->s300, pv, s1966, s1579 ), NULL );
s681->s498( pv->ns, true );
*s274 = s681;}
template<class _Cont, class s1301, class Der>
inline void s1564<_Cont, s1301, Der>::s1453( s481** s274, size_t s496 ){
if( s496 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s492() != s1235 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s589* pf = (s589*)s274[2];
s322* s153 = (s322*)*s274;
std::vector<s483>s855;
s855.resize( 1 );
typename _Cont::iterator s1507 = pv->s347.begin();
for( ; s1507 != pv->s347.end(); ++s1507 ) {
s483 s1058 = *s1507;
s855[0] = s1058;
pf->s594( s855 );
s484 s1050 = pf->s495( 0, 0 );
s481* s1443 = s153->find( s1050 );
if( s1443 )
((s314*)s1443)->add( s1058->s333(0,0) );
else {
s314* s1471 = new s314( pv->s300, pv->s323, pv->ns, NULL );
s1471->s498( pv->ns );
s1471->add( s1058->s333(0,0) );
s153->insert( (s481*)s1050->s333(0,0), (s481*)s1471 );}}}
template<class _Cont, class s1301, class Der>
inline void s1564<_Cont, s1301, Der>::s1958( s481** s274, size_t s496 ){
Der* pv = ( (Der*)s274[1] );
const std::wstring& s72 = ( (s357*)s274[2] )->s318();
std::wstring s681;
if( pv->s347.empty() ) {
*s274 = new s357( pv->s300 );
(*s274)->s1252();
return;}
typename _Cont::iterator s1507 = pv->s347.begin();
s681 = (*s1507)->to_wstring();
for( ++s1507; s1507 != pv->s347.end(); ++s1507 )
s681 += s72 + (*s1507)->to_wstring();
*s274 = new s357( pv->s300, s681 );
(*s274)->s1252();}
template<class _Cont, class s1301, class Der>
inline void s1564<_Cont, s1301, Der>::s2222( s481** s274, size_t s496 ){
Der* pv = ( (Der*)s274[1] );
pv->s495(0,0); // ???DEBUG??? 220816
s484 el = (s481*)s274[2];
el->s495(0,0); // ???DEBUG??? 220909
if( el->s1195() &&
std::find_if( pv->s347.begin(), pv->s347.end(), [el]( s483 r ) { return el->operator==(r.s15<s481*>()); } ) != pv->s347.end() )
*( (s358*)*s274 )->s355() = true;
else
*( (s358*)*s274 )->s355() = false;
(*s274)->s1252();}
template <class _Cont, class s1410, class s1412, class Der>
void s1358<_Cont, s1410, s1412, Der>::s774( s481** s274, size_t s496 ){
using s933 = typename Der::s1130;
Der* pv = (Der*)s274[1];
s481* s2241 = s274[2];	
typename _Cont::iterator s1966;
if( s2241->s1195() )
s1966 = pv->s347.find( s2241 );
else
s1966 = pv->s347.end();
typename _Cont::iterator s1579 = s1966;
if( s1966 != pv->s347.end() )
++s1579;
s1134* s681 = new s1134( pv->s300, pv->ns,
new s933( pv->s300, pv, s1966, s1579 ), NULL );
s681->s498( pv->ns, true );
*s274 = s681;}
template<class _Cont, class s1410, class s1412, class Der>
inline void s1358<_Cont, s1410, s1412, Der>::s1474( s481** s274, size_t s496 ){
if( s496 != 3 )
throw new s2::s16( L"wrong number of arguments" );
if( s274[2]->s492() != s1235 )
throw new s2::s16( L"the parameter must be lambda" );
Der* pv = (Der*)DR;
s589* pf = (s589*)s274[2];
s322* s153 = (s322*)*s274;
std::vector<s483>s855;
s855.resize( 1 );
typename _Cont::iterator s1507 = pv->s347.begin();
for( ; s1507 != pv->s347.end(); ++s1507 ) {
s483 s1058 = *s1507->second;
s855[0] = s1058;
pf->s594( s855 );
s484 s1050 = pf->s495( 0, 0 );
s481* s1443 = s153->find( s1050 );
if( s1443 )
((s314*)s1443)->add( s1058->s333(0,0) );
else {
s314* s1471 = new s314( pv->s300, pv->s323, pv->ns, NULL );
s1471->s498( pv->ns, true );
s1471->add( s1058->s333(0,0) );
s153->insert( (s481*)s1050->s333(0,0), (s481*)s1471 );}}}
template<>
inline void s1564<s2203, s483, s2204>::s2222( s481** s274, size_t s496 ){
s2204* pv = ( (s2204*)s274[1] );
s483 el = (s481*)s274[2];
if( pv->s347.count( el ) )
*( (s358*)*s274 )->s355() = true;
else
*( (s358*)*s274 )->s355() = false;
( *s274 )->s1252();}
template <>
inline void s1390<s2203, s483, s2204, s483>::s1257( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1564<s2203, s483, s2204>::s1257( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1390<s2203, s483, s2204, s483>::s1581( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );}
template <>
inline void s1390<s2203, s483, s2204, s483>::s2079( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );}
template <>
inline void s1390<s2203, s483, s2204, s483>::s1244( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );}
template<>
inline void s1564<s2236, s483, s2237>::s2222( s481** s274, size_t s496 ){
s2237* pv = ( (s2237*)s274[1] );
s483 el = (s481*)s274[2];
if( pv->s347.count( el ) )
*( (s358*)*s274 )->s355() = true;
else
*( (s358*)*s274 )->s355() = false;
( *s274 )->s1252();}
template <>
inline void s1390<s2236, s483, s2237, s483>::s1257( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1564<s2236, s483, s2237>::s1257( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'sort' operation" );}
template <>
inline void s1390<s2236, s483, s2237, s483>::s1581( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'shuffle' operation" );}
template <>
inline void s1390<s2236, s483, s2237, s483>::s2079( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'unique' operation" );}
template <>
inline void s1390<s2236, s483, s2237, s483>::s1244( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'reverse' operation" );}
template <>
inline void s1390<s2236, s483, s2237, s483>::s1482( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'subseq' operation" );}
template <>
inline void s1390<s2236, s483, s2237, s483>::s1609( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'back' operation" );}
template <>
inline void s1564<s2236, s483, s2237>::s1609( s481** s274, size_t s496 ){
throw new s2::s16( L"this type of iterable doesn't support the 'back' operation" );}
class s413
: public s334{
static s339 s346;
std::wstring path;
std::wstring s522;
s314 s748;
s314 s803;
static void s1227( s481** s274, size_t n );
static void s407( s481** s274, size_t n );
static void s1663( s481** s274, size_t n );
static void s414( s481** s274, size_t n );
static void s415( s481** s274, size_t n );
static void s983( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
s413( s262* s300 ) : s334( s300, NULL, NULL ), s748(s300), s803(s300) {}
s413( s262* s300, const std::wstring& s77, const s263* ast_=NULL );
s413( const s413& right, const s263* ast_ = NULL );
s413( s262* s300, const std::wstring& s, size_t& pos, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)&s748; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1593
: public s589{
public:
s1593( s262* s300, s272* s590, s589* s591,
const std::vector<s271*>& l, const s263* s695 );
const std::wstring& s299() const override { return s1306; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
} // namespace
namespace transd{
class s603
: public s589{
public:
s603( s262* s300, s272* s590, s589* s591, const std::vector<s271*>& l,
const s263* s695, bool s2159 = false );
s603( const s603& right, s272* s590, s589* s591 );
s1890& s299() const override { return s233; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s706( s1890& s278, s369* ref,
s1890& s332 ) const;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s305
: public s589{
s483 s306;
public:
s305( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l,
const s263* s695,	bool s2159 = false );
s305( const s305& right, s272* s590, s589* s591 );
s1890& s299() const override { return s255; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s612
: public s589{
s487 s707;
s484 varval;
s483 s308;
s483 where;
s483 s1053;
s369 s309;
s1518 s310;
Iterator* s2274;
s1::s9<s324> s2273;
public:
s612( s262* s300, s272* s586, Transd* s585, const std::vector<s271*>& l,
const s263* s695, bool s2159 = true );
s612( const s612& right, s272* s590, s589* s591 );
s1890& s299() const override { return s260; }
void s498( const s272* s1658, bool proc ) override;
void s2118( s589* s2042, s272* impl, bool s2159 ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s608
: public s589{
public:
s608( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s608( s262* s300 );
s1890& s299() const override { return s256; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s613
: public s589{
static s1::s9<s262> s900;
public:
s613( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695, bool s2160 = true );
s613( s262* s300 );
const std::wstring& s299() const override { return s261; }
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s791
: public s589{
public:
s791( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s791( s262* s300 );
s1890& s299() const override { return s766; }
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s769
: public s589{
std::wstring s898;
public:
s769( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s769( s262* s300 );
const std::wstring& s299() const override { return s815; }
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1297
: public s589{
public:
s1297( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1297( s262* s300 );
s1890& s299() const override { return s1307; }
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1598
: public s589{
public:
s1598( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
s1598( s262* s300 );
s1890& s299() const override { return s1608; }
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
};
class s1769
: public s1::s10{
public:
s1769() { }
virtual ~s1769() { }
virtual s484 s754( const std::wstring& s76, bool s708 = true ) const = 0;
virtual void s857( s744& s153 ) const = 0;
virtual void s857( s952& s153 ) const = 0;
virtual void s543( std::vector<std::wstring>& s153 ) const = 0;
virtual size_t s320() const = 0;
};
class s770;
typedef s1::s9<s1769> s816;
bool s1788( s816 l, s816 r );
struct s738 : public s1::s10{
enum Verb { s1761, s1762, s1760, s1763, s2044, s1759 };
Verb verb;
s738()
: verb( s1761 )
{	}
};
class s1767;
typedef std::multimap<s484, s816, s1414> s1772;
typedef std::pair<s1772::iterator, s1772::iterator> s1774;
typedef std::list<s816> s1770;
extern s1770 s1832;
extern s1770::iterator s1833;
struct s1771{
bool operator()( const s484 l, const s484 r ) const{
return l->operator<( ( s481* )&( *r ) );}
bool operator()( const s481* l, const s481* r ) const{
return l->operator<( r );}
bool operator()( const s484 l, const std::pair<s484, s816>& r ) const{
return l->operator<( ( s481* )&( *r.first ) );}
bool operator()( const std::pair<s484, s816>& l, const s484 r ) const{
return l.first->operator<( ( s481* )&( *r ) );}
};
struct s1773{
s1774 pr;
std::wstring s970;
size_t dist;
bool operator<( s1773 const& r ) const{
return dist < r.dist;}
};
class s1768{
protected:
s1767* pdb;
s1770* ptr;
s1770::iterator fi;
s1770::iterator se;
s1770::iterator cur;
public:
s1768( s1767* s1792 );
virtual ~s1768();
virtual void s1856( void* f, void* s ) = 0;
virtual void s1859() = 0;
virtual bool s1821() = 0;
virtual s1769* s1831() = 0;
void sort() { ptr->sort( s1788 ); }
void clear() { ptr->clear(); }
bool empty() { return ptr->empty(); }
void swap( s1768* r ) { ptr->swap( r->s318() ); }
s1770& s318() { return *ptr; }
s1767* s1778() { return pdb; }
virtual void s1817( std::vector<std::wstring>& s153 ) = 0;
};
struct s1790{
bool operator()( const s1773* l, const s1773* r ) const{
return l->operator<( *r );}
bool operator()( const s1773& l, const s1773& r ) const{
return l.operator<( r );}
};
typedef std::set<s1773, s1790 > s1775;
class s1764{
public:
enum s1777 { s1842, s1837, s1840, s1838, s1841, s1839, s2135 };
private:
std::wstring field;
s1777 op;
s483 par, s347;
static const std::vector<std::wstring> s1864;
public:
s1764( s262* s300, s272* s586, const std::wstring& s, size_t& pos );
void s498( s272* ns );
void select( s1767* pdb, s1773& s153 );
};
class s1765;
class s1765{
public:
enum s1766 { s1799, s1800, s1798 };
private:
s1766 s1803;
std::vector<s1765> subs;
std::vector<s1764> s1797;
public:
s1765( s262* s300, s272* s586, const std::wstring& s, size_t& pos, s1766 s1803 );
s1765( const s1765& r );
void s498( s272* ns );
void s1796( s262* s300, s272* s586, const std::wstring& s, size_t& pos );
void select( s1767* pdb, s1768* s153 );
};
class s1767
: public s334{
protected:
std::map<std::wstring, s1772> s865;
bool s2053;
public:
s1767( s262* s300, s272* ns_, const s263* ast_ )
: s334( s300, ns_, ast_ ), s2053( true )	{	}
virtual ~s1767();
virtual void release() override;
bool s2054() const { return s2053; }
virtual void select( s1890& field, s1764::s1777, const s481* s1058,
s1773& s153 ) = 0;
virtual void intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ) = 0;
virtual void intersect( const s1773& fi, s1768* s153 ) = 0;
virtual void s849( s1890& s852 ) = 0;
virtual s1768* s1804() const = 0;
virtual void s1855( s1768* s153 ) = 0;
virtual bool s1995( s1890& s ) const = 0;
virtual s1054 s2000( s1890& s852 ) const = 0;
virtual void s1818( std::vector<std::wstring>& s153) const = 0;
};
struct s1698 : public s738{
enum s831 { s822=0, s825 };
int distinct;
int	s882;
std::wstring s881;
int s868;
s1698()
: distinct( -1 ), s882( -1 ), s868( -1 )
{	}
};
struct s1708 : public s738{
};
struct s1694 : public s738{
};
struct s1971 : public s738{
};
struct s1696 : public s1::s10 { };
struct s1697 : public s1696{
s483 what;
s483 where;
s483 s1852;
s483 s883;
s483 s1065;
s483 s868;
};
struct s1707 : public s1696{
s483 what;
s483 where;
s483 s1852;
};
struct s1693 : public s1696{
s483 at;
s483 values;
s1::s9<s1707> s1747;
};
struct s1970 : public s1696{
s483 what;
s483 where;
s483 s1852;
s483 s2042;
s483 s1065;
};
class s891
: public s589{
size_t s902;
s484 s681;
protected:
void s1896( const s575& pl ) const override { }
void s594( const s575& pl ) override { s274.assign( pl.begin(), pl.end() ); }
public:
s891() : s589( NULL, NULL, NULL, NULL, s563, L"", NULL ), 
s681( new s358( NULL, false ) ){ }
void s901( size_t idx ) { s902 = idx; }
virtual s484 s495( s481** s699, size_t s496 ) override{
s483 l = s274[0];
s483 r = s274[1];
*s681.s15<s358*>()->s355() = l.s15<s744*>()->operator[]( s902 ).s15<s481*>()->
operator<( r.s15<s744*>()->operator[]( s902 ).s15<s481*>() );
s484 s899 = s681;
return s899;}
};
class s314;
class s785
: public s589{
s483 db;
s369 s2023;
s1::s9<s952> s2022;
s1::s9<s738> s804;
s1::s9<s1696> qp;
s369 s727;
s485 s777;
s1765* s1845;
s482* s1791( const std::wstring& s );
void s2048( s1767* base, s483 what, std::vector<std::wstring>& s889,
std::vector<s486>& s2046, std::vector<std::wstring>& s1853 );
void s1709( const std::vector<s271*>& l_,	TDException& s961 );
void s1711( const s272* s1658, bool proc );
s484 s1716( s481** s274, size_t s496 );
void s1710( const std::vector<s271*>& l_,	TDException& s961 );
void s1712( const s272* s1658, bool proc );
s484 s1717( s481** s274, size_t s496 );
void s1987( const std::vector<s271*>& l_,	TDException& s961 );
void s1989( const s272* s1658, bool proc );
s484 s1992( s481** s274, size_t s496 );
public:
enum s1132{ s1222, s2056, s1742, s2005, s2055, s1207, s1208, s1226, 
s1829, s2006, s1212, s1223, s1209, s1211,	s1221, s1740 };
s785( s262* s300, s272* s586, s589* s585, const std::vector<s271*>& l, const s263* s695 );
~s785();
s1890& s299() const override { return s812; }
void s498( const s272* s1658, bool proc ) override;
s484 s495( s481** s274, size_t s496 ) override;
s271* s333( s589* s2042, s272* impl ) const override;
bool s554( s1890& s278, s369* s153, s1890& s332,	bool ) const override;
s271* s596( size_t off ) override;
};
class s770
: public s1769{
typedef std::map<std::wstring, s483> s721;
s721 s756;
s721* s2136;
size_t rechash;
s1::s9<s1590> pobj;
public:
s770() {}
s770( s262* s300, s272* s586, s1890& rec, const std::vector<std::wstring>& s737,
std::vector<s483>& types, const s1706& tbfr=s1724 );
s770( s262* s300, s1590& s586 );
s484 s754( s1890& s76, bool s708=true ) const override;
void s857( s744& s153 ) const override;
void s857( s952& s153 ) const override;
void s543( std::vector<std::wstring>& s153 ) const override;
size_t s320() const override;
bool operator==( const s770* p ) const;
bool operator<( const s770* p ) const;
std::wstring to_wstring( uint32_t s1553 = 0 ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
class s806
: public s1::s10{
typedef std::vector<s483> s729;
s729 s805;
size_t s794;
public:
s806() {}
s806( std::vector<std::wstring>& s726, s816 rec );
size_t s320() const;
bool operator==( const s806* p ) const;
bool operator<( const s806* p ) const;
void s304( std::wostream* pd, int s197 = 0 ) const;
};
typedef s1::s9<s806> s728;
struct s765{
std::size_t operator()( const s728 k ) const{
return k->s320();}
};
struct s709{
std::size_t operator()( const s728 l, const s728 r ) const{
return l->operator==( ( s806* )&( *r ) );}
};
struct s840{
std::size_t operator()( const s816 k ) const{
return k->s320();}
};
struct s839{
std::size_t operator()( const s816 l, const s816 r ) const{
return l.s15<s770*>()->operator==( ( s770* )&( *r ) );}
};
typedef std::unordered_map<s728, s816, s765, s709> s781;
extern s781::iterator s1834;
class s1782 
: public s1768{
s781* pind;
s781::iterator cur1;
public:
s1782( s1767* pdb );
virtual ~s1782(){}
void s1856( void* f, void* s ) override;
void s1859() override;
bool s1821() override;
s1769* s1831() override;
void s1817( std::vector<std::wstring>& s153 ) override {}
};
class s648
: public s1767{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
private:
static s339 s346;
BaseMap s649, s650, s651;
BaseMap::iterator s316;
s781 s751;
std::vector<std::wstring> s2130;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s780( s481** s274, size_t n );
static void s2127( s481** s274, size_t n );
static void s796( s481** s274, size_t n );
static void s746( s481** s274, size_t n );
static void s764( s481** s274, size_t n );
static void s331( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s329( s481** s274, size_t n );
static void s850( s481** s274, size_t n );
static void s2139( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
enum s1132 { s1739, s1737, s1735, s1736, s1738, s1828 };
s648( s262* s300, s272* s586 = NULL, const s263* ast_ = NULL );
s648( s262* s300, s272* s586, s1890& s77, const s263* ast_ = NULL );
s648( const s648& right, const s263* ast_ = NULL );
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)NULL; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s652( s1890& s194 );
void s377( s1590& obj );
void s653( s1890& q );
void s712( s1890& s818, const s1706& tbfr );
void s849( s1890& s852 ) override;
void select( s1890& field, s1764::s1777, const s481* s1058,	s1773& s153 ) override;
s1768* s1804() const override;
void s1855( s1768* s153 ) override;
void intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ) override;
void intersect( const s1773& fi, s1768* s153 ) override;
bool s1995( s1890& s ) const override;
s1054 s2000( s1890& s852 ) const override;
void s1818( std::vector<std::wstring>& s153) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1787;
class s1786
: public s1769{
public:
typedef std::vector<s484> s1779;
private:
s1779 s1847;
size_t rechash;
s1787* s1844;
public:
s1786() {}
s1786( const std::vector<s484>& v, s1787* s1844 );
s1786( s262* s300, s272* s586, s1890& rec,
const std::vector<std::wstring>& s737,
std::vector<s483>& types, const s1706& tbfr=s1724 ){ }
virtual ~s1786();
s484 s754( s1890& s76, bool s708 = true ) const override;
const s1779& s2001() const;
void s857( s744& s153 ) const override;
void s857( s952& s153 ) const override;
void s543( std::vector<std::wstring>& s153 ) const override;
virtual size_t s320() const override;
bool operator==( const s770* p ) const { return 0; }
bool operator<( const s770* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const{ return L""; }
void s304( std::wostream* pd, int s197 = 0 ) const{ }
};
class s1785 : 
public s1768{
public:
s1785( const s1785& r );
s1785( s1767* pdb );
virtual ~s1785();
void s1856( void* f, void* s ) override;
void s1859() override;
bool s1821() override;
s1769* s1831() override;
void s1817( std::vector<std::wstring>& s153 ) override;
};
class s1787
: public s1767{
public:
private:
static s339 s346;
s1770 rows;
std::vector<std::wstring> s800;
std::map<std::wstring, size_t> s1820;
std::vector<s816> s2045;
s1054 s2027;
std::wstring s497;
static void s1227( s481** s274, size_t n );
static void s796( s481** s274, size_t n );
static void s746( s481** s274, size_t n );
static void s764( s481** s274, size_t n );
static void s331( s481** s274, size_t n );
static void s326( s481** s274, size_t n );
static void s2003( s481** s274, size_t n );
static void s2011( s481** s274, size_t n );
static void s2012( s481** s274, size_t n );
static void s850( s481** s274, size_t n );
void s348() override;
const s339& s340() const override { return s346; }
public:
enum s1132 { s1739, s1737, s1735, s1736, s1738, s1828, 
s2004 };
s1787( s262* s300, s272* s586 = NULL, const s263* ast_ = NULL );
s1787( s262* s300, s272* s586, s1890& s77, const s263* ast_ = NULL );
s1787( const s1787& right, const s263* ast_ = NULL );
virtual ~s1787();
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
s1054 s1179( s1890& s1541, const std::vector<s483>& l ) const override;
void release() override;
bool s499( const s481* s500 ) const override;
void* addr() override { return (void*)NULL; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s652( s1890& s194 );
void s653( s1890& q ){ }
void s712( s1890& s818, const s1706& tbfr );
void s849( s1890& s852 ) override;
void select( s1890& field, s1764::s1777, const s481* s1058,
s1773& s153 ) override;
s1768* s1804() const override;
void s1855( s1768* s153 ) override;
void intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ) override;
void intersect( const s1773& fi, s1768* s153 ) override;
size_t s1819( s1890& s1802 ) const;
void s1818( std::vector<std::wstring>& s153 ) const override { s153 = s800; }
bool s1995( s1890& s ) const override;
s1054 s2000( s1890& s852 ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
class s1787;
class s2061
: public s1769{
private:
s484 rec;
public:
s2061( s484 d );
virtual ~s2061();
s484 s754( s1890& s76, bool s708 = true ) const override;
void s857( s744& s153 ) const override;
void s857( s952& s153 ) const override;
void s543( std::vector<std::wstring>& s153 ) const override;
virtual size_t s320() const override;
bool operator==( const s770* p ) const { return 0; }
bool operator<( const s770* p ) const{  return 0; }
std::wstring to_wstring( uint32_t s1553 = 0 ) const{ return L""; }
void s304( std::wostream* pd, int s197 = 0 ) const{ }
};
class s2060 : 
public s1768{
Iterator* s2066;
s324* s2068;
bool started;
public:
s2060( const s2060& r );
s2060( s1767* pdb );
virtual ~s2060();
void s1856( void* f, void* s ) override;
void s1859() override;
bool s1821() override;
s1769* s1831() override;
void s1817( std::vector<std::wstring>& s153 ) override;
};
class s2047
: public s1767{
private:
static s339 s346;
std::wstring s2065;
s324* pv;
s1054 s2027;
std::wstring s497;
void s348() override;
const s339& s340() const override { return s346; }
public:
s2047( s262* s300, s272* s586 = NULL, s324* pv = NULL, const s263* ast_ = NULL );
s2047( const s2047& r );
virtual ~s2047();
s481* s352( const s263& s695, s272* s586, s1890& s332 ) const override;
s481* s353( s272* s586, const std::vector<s271*>& l, const s263* ast_ ) const override;
void release() override;
void* addr() override { return (void*)NULL; }
void s498( const s272* s873, bool ) override;
s271* s333( s589* s2042, s272* impl ) const override;
void s354( s271* p ) const override;
size_t s320() const override;
bool operator==( const s481* p ) const override;
bool operator<( const s481* p ) const override;
void s652( s1890& s194 );
void s653( s1890& q ){ }
void s712( s1890& s818, const s1706& tbfr );
void s849( s1890& s852 ) override;
void select( s1890& field, s1764::s1777, const s481* s1058,
s1773& s153 ) override;
s1768* s1804() const override;
void s1855( s1768* s153 ) override;
void intersect( const s1773& fi1, const s1773& fi2,
s1770& s153 ) override;
void intersect( const s1773& fi, s1768* s153 ) override;
size_t s1819( s1890& s1802 ) const;
void s1818( std::vector<std::wstring>& s153 ) const override { s153.push_back( s2065 ); }
bool s1995( s1890& s ) const override;
s1054 s2000( s1890& s852 ) const override;
std::wstring to_wstring( uint32_t s1553 = 0 ) const override;
void s304( std::wostream* pd, int s197 = 0 ) const override;
};
#define TRANSD_VERSION L"0.503"
void evaluateExpression( const std::wstring& s77 );
HPROG createAssembly();
void deleteAssembly( int n );
void loadProgram( HPROG handle, const std::wstring& s189 );
void s211( HPROG handle, s6::s143& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s687 );
void* callFunc( HPROG handle, const std::wstring& s77, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s599 );
void* s223( HPROG handle, const std::wstring& s278 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1103, const std::wstring& symName,
const std::wstring& s332 );
void importFile( HPROG handle, const std::wstring& s1103, const std::wstring& s44,
const std::wstring& s332 );
HPROG initShell( const std::wstring& s1103, const std::wstring& modText );
typedef s2::s16 TransdException;
} // namespace transd
