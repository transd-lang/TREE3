
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
namespace s1 
{
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
class Conversion
{
typedef char Small;
class Big { char dummy[2]; };
static Small Test( U );
static Big Test( ... );
static T MakeT();
public:
enum
{
exists =
sizeof( Test( MakeT() ) ) == sizeof( Small )
};
enum { sameType = false };
};
template <class T>
class Conversion<T, T>
{
public:
enum { exists = 1, sameType = 1 };
};
#define SUPERSUBCLASS(T, U) \
(Conversion<const U*, const T*>::exists && \
!Conversion<const T*, const void*>::sameType)
template <class F, class T>
T* checked_cast( F* p )
{
if( SUPERSUBCLASS( T, F ) )
return p;
return nullptr;
}
class s11
{
int refs;
public:
s11() : refs(0){}
virtual ~s11()
{
}
void s12()
{
refs++;
}
void s13()
{
if( --refs == 0 )
deallocate();
}
int getNumRef()
{
return refs;
}
virtual void deallocate()
{
delete this;
}
};
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif
template <class C>
class s10
{
C* p;
public:
s10( C* p_ ) : p(p_)
{
if(p)
p->s12();
}
s10(C& p_) 
{
p = &p_;
if(p)
p->s12();
}
s10()
{
p = NULL;
}
s10(const s10<C> &pn)
{
p = pn.p;
if(p)
pn.p->s12();
}
template<class D> 
s10( s10<D> &pn )
{
p = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p)
p->s12();
}
}
~s10()
{
s16();
}
operator C*() { return p; }
C& operator*() { return *p; }
const C& operator*()const { return *p; }
C* operator->() { return p; }
const C* operator->()const { return p; }
s10& operator=( s10<C> &p_ ) { return operator=(( C* ) p_); }
s10& operator=( const s10<C> &p_ ) { return operator=( (s10<C>& ) p_ ); }
s10& operator=( C* p_ )
{
if(p){
p->s13();
}
p = p_;
if(p)
p->s12();
return *this;
}
template<class B>
operator B*()
{
return checked_cast<C, B>( p );
}
template<class D>
s10& operator=( const s10<D> &p_ )
{
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
}
template<class ToType>
ToType s17() const
{
return static_cast<ToType>( p );
}
template<class ToType>
ToType dcast() const
{
return dynamic_cast<ToType>( p );
}
bool s14()const { return p == nullptr; }
bool s15()const { return p != nullptr; }
void s16()
{
if(p){
p->s13();
p = nullptr;
}
}
bool operator ==( const s10<C>&ptr )const { return ( (INT_PTR)ptr.p == (INT_PTR)p ); }
bool operator !=( const s10<C>&ptr )const { return ( (INT_PTR)ptr.p != (INT_PTR)p ); }
bool operator <( const s10<C>&ptr )const { return ( (INT_PTR)ptr.p < (INT_PTR)p ); }
bool operator ==( const C& s367 )const { return ( *p == s367 ); }
bool operator !=( const C& s367 )const { return ( *p != s367 ); }
bool operator <( const C& s367 )const { return ( *p < s367 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1242();
extern std::vector<std::wstring> s1098;
class s18
: public std::exception
{
static uint32_t s29;
protected:
std::list<std::wstring> s28;
uint32_t id;
s18() :id( 0 ){};
public:
enum class s19 : uint32_t
{
s20 = 0,
s21,
s22,
s23,
s24,
s25,
s26,
s960,
s27
};
s18( const std::wstring& s, uint32_t n = (uint32_t)s19::s21 )
: id( n )
{
s28.push_back( s );
}
s18( uint32_t n )
: id( n )
{
s28.push_back( s1098[n] );
}
s18( const s18& right )
: id( right.id )
{
s28.assign( right.s28.begin(), right.s28.end() );
}
static void s31()
{
s29 = (uint32_t)s19::s27 + 1;
}
static uint32_t s30()
{
return s29++;
}
virtual std::wstring Msg( size_t s205 = 0 ) const
{
std::wstring s721;
std::list<std::wstring>::const_reverse_iterator it = s28.crbegin();
std::wstring s1193( s205, L' ' );
while( it != s28.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s28.crend() )
s721 += s1193;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s721 += ( i++ ? L"" : s1193 ) + s + L"\n";
}
return s721;
}
const char* what() const noexcept
{
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
return conv.to_bytes( s28.back() ).c_str();
}
uint32_t which() const { return id; }
s18* s32( const std::wstring& s )
{
s28.push_back( s );
return this;
}
s18* specify( const std::wstring& s )
{
s28.push_front( L"\n  : " + s );
return this;
}
};
} // namespace s2
namespace s3 {
bool s33( const std::wstring& _dir, const std::wstring& s551, std::wstring& s160 );
void s34( const std::wstring& _dir, const std::wstring& s551, std::vector<std::wstring>& s42,
std::vector<std::wstring>& s43 );
time_t s35( const std::wstring& f );
uint8_t s36( const std::wstring& f );
bool s764( const std::wstring& f );
bool s37( const std::wstring& s218 );
bool s38( const std::wstring& s218 );
std::wstring s39();
std::wstring s40();
std::wstring s41();
} // namespace s3
namespace s4 
{
extern std::wstring s91;
extern std::wstring s51;
extern std::string s52;
extern std::wstring s53;
enum s19 { s25 };
std::wstring s54( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s55( const std::wstring& s, const std::wstring& c );
bool s56( const std::wstring& s, const std::wstring& ss );
void s57( const std::wstring& s, size_t s68, wchar_t left, wchar_t right, 
size_t& start, size_t& end, bool s975 = false );
void s58( const std::wstring& s, size_t s68, wchar_t c, size_t& start, 
size_t& end );
void s1103( const std::wstring& s, size_t& s68, const std::wstring& s1210 );
size_t count( const std::wstring& s80, const std::wstring& s1210, size_t start, size_t end,
bool s975 = false );
int s59( const std::wstring& s80, wchar_t s75, size_t& pos );
void s60( const std::wstring& s, const std::wstring& s75, std::vector<std::wstring>& s160, bool clr = true );
void s299( const std::vector<std::wstring>& v, const std::wstring& s75, std::wstring& s160 );
std::wstring s74( const std::wstring& s80, size_t& pos );
void s61( const std::wstring& s80, const std::wstring& s75, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s62( const std::wstring& s80, const std::wstring& s75,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s63( const std::wstring& s80 );
void s64( std::wstring& s48 );
std::wstring s792( std::wstring path );
bool s65( const wchar_t *str, long *s367, wchar_t **end = NULL );
bool s66( const wchar_t *str, double *s367, wchar_t **end = NULL );
void s963( const std::wstring& s80, std::vector<std::wstring>& s160 );
std::string s54( const std::string& l, const std::string& s, const std::string& r );
std::string s55( const std::string& s, const std::string& c );
void s57( const std::string& s, size_t s68, char left, char right, 
size_t& start, size_t& end);
int s59( const std::string& s80, char s75, size_t& pos );
void s60( const std::string& s, const std::string& s75, std::vector<std::string>& s160 );
void s62( const std::string& s80, std::vector<std::pair<std::string, std::string>>& v );
std::string s63( const std::string& s80 );
struct fill_n_ch {
size_t len;
wchar_t ch;
typedef std::basic_ostream<wchar_t, std::char_traits<wchar_t> > wostream;
fill_n_ch( wchar_t c, size_t l ): len(l), ch(c) {}
friend wostream& operator<< ( wostream& os, fill_n_ch fb )
{
for ( size_t i = 0; i < fb.len; i++ )
os << fb.ch;
return os;
}
};
#define FILL(x) fill_n_ch( L' ', x )
template <typename UINT> 
constexpr UINT rol(UINT s367, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s367 << n) | (s367 >> (sizeof(UINT)*8-n));
}
void s67( const std::wstring& s81 );
void s84( std::wstring& s80, std::vector<std::wstring>& s1225, std::map<size_t, size_t>& s1149 );
} // namespace s4
namespace s5 {
extern std::locale locloc;
extern std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
}
#define U8(x) s5::conv.to_bytes( x )
#define U16(x) s5::conv.from_bytes( x )
#ifdef __LINUX__
#define KCHAR char
#define TOFS(x) s5::conv.to_bytes(x)
#define FROMTERM(x) s5::conv.from_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#endif
namespace s6 {
void s1238();
class s19
{
static uint32_t s93;
public:
static void s31();
static uint32_t s94() { return s93; }
};
void s95( const std::wstring& s96,
const std::vector<std::wstring>& s97 = { } );
void s101();
void s137( int s76 = 0 );
void s103( bool b = true );
bool s104( const std::wstring& s98 );
int s105( const std::wstring& s98, const std::vector<std::wstring>& s99 );
std::wstring s106( const std::wstring& s98, bool s100 = false );
std::wstring s107( const std::wstring& s98, bool s100 = false );
std::wstring s108( const std::wstring& s98,
const std::vector<std::wstring>& s109 );
int s110( const std::wstring& s98 );
size_t s111( const std::wstring& s98 );
void s112( int& w, int& h );
void s113( const std::vector<std::wstring>& v, std::vector<std::wstring>& s160,
size_t w, size_t h );
int s114( const std::vector<std::wstring>& v );
#ifdef __LINUX__
char _getch();
#endif
#define s115 72
#define s116 80
#define s117 75
#define s118 77
#define s119 27
#define s120 13
#define s123 224
#define s121 8
#define s122 83
} // namespace s6
namespace s7
{
enum s138{ s139, s140, s141, s146, 
s142, s143, s147, s144, s145 };
class s148;
class s150;
typedef s1::s10<s148> s149;
class s1037
: public s1::s11
{
std::wstring s202;
std::wstring s1235;
std::vector<std::wstring> s1236;
std::map<size_t, size_t> s1237;
size_t s1173;
public:
s1037( const std::wstring& file );
const std::wstring& Path() const { return s202;  }
void read( std::vector<s1::s10<s150>>& s160, 
const std::wstring& s198 = std::wstring(L"") );
void s178( const std::wstring& s80, size_t& pos, s1::s10<s150> s160, bool s158 = false );
bool s1108( std::wstring& s, size_t s71, size_t s719, size_t& line ) const;
size_t s1042() const { return s1173; }
};
typedef s1::s10<s1037> s1040;
class s150
: public s1::s11
{
std::multimap<std::wstring, s149> s151;
s1040 src;
public:
enum s152 { s153, s154, s155 };
enum s19 { s20, s156 };
const static s148 s157; // similar to string::npos
s150( const s1037* pf ):src( (s1037*)pf){}
void s161( const std::wstring& s80, bool s158 = false);
void s162( std::wostream* pd, bool s158=false ) const;
bool s163( const std::wstring& s159 ) const;
void s164( const std::wstring& s159, std::vector<s149>& s160 ) const;
const s149 s165( const std::wstring& s159 ) const;
void s166( const std::wstring& s79, s149 s367, s152 ap=s153 );
void s167( std::vector<std::pair<std::wstring, s149>>& s160 ) const;
bool operator==( const s150& r )  const;
void s168( std::wostream* pd, int s205 ) const;
};
bool operator==( const std::vector<s1::s10<s148>>& l,
const std::vector<s1::s10<s148>>& r );
class s148
: public s1::s11
{
s138 s206;
s150 obj;
std::wstring str;
std::vector<s1::s10<s148>> s169;
double s170;
bool b;
std::pair<size_t, size_t> s1197;
s1040 s1196;
public:
s148():s206(s139),obj(NULL){}
s148( const std::wstring& s ):s206(s141),obj(NULL),str(s){}
s148( const std::vector<s149>& a ): s206(s142),obj(NULL),s169(a){}
s148( const s1037* pf, const std::wstring& s80, size_t& pos, bool s158 = false );
s138 s171() const { return s206; }
bool s172() const { return s206 == s139; }
const s150& s173() const
{
if( s206 == s140 )
return obj;
throw std::runtime_error( "wrong variant" );
}
const std::vector<s149>& s174() const
{
if( s206 == s142 )
return s169;
throw std::runtime_error( "wrong variant" );
}
double s175() const
{
if( s206 == s143 )
return s170;
throw std::runtime_error( "wrong variant" );
}
int s59() const
{
if( s206 == s147 )
return (int)s170;
throw std::runtime_error( "wrong variant" );
}
bool s771() const
{
if( s206 == s144 )
return b;
throw std::runtime_error( "wrong variant" );
}
const std::wstring& s176() const
{
if( s206 == s141 || s206 == s146 )
return str;
throw std::runtime_error( "wrong variant" );
}
const std::wstring& s943() const
{
if( s206 == s146 )
return str;
throw std::runtime_error( "wrong variant" );
}
std::wstring s933() const
{
if( s206 == s146 )
return str.substr( 1, str.size() - 2 );
throw std::runtime_error( "wrong variant" );
}
bool s1113( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s1037* s1110() const { return s1196.s17<s1037*>(); }
bool operator==( const s148& r ) const
{
return s206 == r.s206 && obj == r.obj && str == r.str && s169 == r.s169 && b == r.b && s170 == r.s170;
}
bool is( const s148& r ) const
{
return this == &r;
}
void s168( std::wostream* pd, int s205 ) const;
void s162( std::wostream* pd, bool s158=false ) const;
};
void s179( const std::wstring& s202, 
const std::vector<s1::s10<s150>>& s203 );
void s186( const s1037* pf, const std::wstring& s80, size_t& pos, std::vector<s1::s10<s148>>& s160,
bool s158 = false, const std::wstring& s75 = L",");
void s186( const s1037* pf, const std::wstring& s80, std::vector<s1::s10<s148>>& s160,
bool s158 = false, const std::wstring& s75 = L"," );
} // namespace s7
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s1019 extern const uint32_t
namespace transd {
namespace s8 {
DEFCONST s439;
DEFCONST s440;
DEFCONST s441;
DEFCONST s442;
DEFCONST s443;
DEFCONST s444;
DEFCONST s445;
DEFCONST s446;
DEFCONST s447;
DEFCONST s448;
DEFCONST s1083;
DEFCONST s449;
DEFCONST s450;
DEFCONST s451;
DEFCONST s901;
DEFCONST s452;
DEFCONST s453;
DEFCONST s454;
DEFCONST s815;
DEFCONST s796;
DEFCONST s850;
DEFCONST s455;
DEFCONST s456;
DEFCONST s900;
DEFCONST s1032;
DEFCONSTI s944;
DEFCONSTI s457;
DEFCONSTI s458;
DEFCONSTI s459;
DEFCONSTI s460;
DEFCONSTI s461;
DEFCONSTI s945;
DEFCONSTI s946;
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
DEFCONST s473;
DEFCONST s474;
DEFCONST s475;
DEFCONST s476;
DEFCONST s478;
DEFCONST s477;
DEFCONST s479;
DEFCONST s480;
DEFCONST s481;
DEFCONST s819;
DEFCONST s858;
DEFCONST s893;
DEFCONST s482;
DEFCONST s483;
DEFCONST s484;
DEFCONST s485;
DEFCONST s486;
DEFCONST s487;
DEFCONST s489;
DEFCONST s783;
DEFCONST s491;
DEFCONST s1027;
DEFCONST s1006;
DEFCONST s1005;
DEFCONST s1007;
#define s438 3
#define s1239 L','
DEFCONST s437;
DEFCONST s1227;
s1019 s1015;
s1019 s1014;
s1019 s1009;
s1019 s1228;
s1019 s1010;
s1019 s1229;
s1019 s1230;
s1019 s1231;
s1019 s1011;
s1019 s1012;
s1019 s1013;
} // namespace s8
enum s233 { s234, s235, s236, s237 };
extern std::wstring s238[];
extern const std::wstring s239, s240, s241,				s882,
s242,  s243,     s244,    s245,      s246,
s247,  s248, s249, s250,s253,
s251, s252,			s267,	s254,			s266,
s255, s256,     s257,   s258,			s799,
s259,   s260, s261, s262,			s263,
s264, s265,		s268,	s270,			s271,
s269,	 s878,			s808, s928, 	s822,
s929,  s991;
class s272;
class s273;
class s280;
class s281;
class s282;
typedef s280* ( *s283 )( const std::wstring& s288, const std::vector<s281*>& s284 );
typedef s1::s10<s273> s1039;
extern const std::wstring s275;
class s273
: public s1::s11
{
public:
typedef std::multimap<std::wstring, s1039> s285;
typedef std::map<std::wstring, std::wstring> s274;
private:
static std::map<std::wstring, s283> s286;
std::wstring s287;
std::wstring s288;
s233 s289;
std::wstring s290;
s285 s291;
std::wstring src;
s7::s149 s1165;
s274 s276;
void s292( const std::wstring& s80 );
void s293( const s7::s150& s140 );
void s294( const std::wstring& s80 );
void s295( const std::wstring& s80 );
void s296( const std::wstring& type, const s7::s148& obj );
void s1105( const std::wstring& s );
static std::wstring s297( const std::wstring& s80, size_t &pos );
public:
enum s19 { s20, s156 };
s273(){ }
s273( s233 at, const std::wstring& qpre, const std::wstring& s79 )
: s287( qpre ), s288( s79 ), s289( at ) { }
s273( const std::wstring& s79, const std::wstring& s367 )
: s288( s79 ), s289( s234 ), s290( s367 ) { }
s273( const std::wstring& type );
s273( const std::wstring& s79, const s7::s148& s306 );
s273( const s7::s150& s140 );
~s273();
s233 s307() const { return s289; }
std::wstring s308() const;
const std::wstring& s309() const { return s288; }
const std::wstring& Src() const { return src; }
const s7::s148* Nqj() const { return s1165.s17<s7::s148*>(); }
const std::wstring& s278( const std::wstring& s313 ) const;
void s279( const std::wstring& s313, const std::wstring& s277 );
void reset();
static void s298( const std::wstring& s80, size_t& pos, std::vector<std::wstring>& s160 );
void s299( s7::s150& s140 );
void s296( s273* node );
void s300( s272* s310, size_t s311 = 0 );
const std::wstring& s301() const { return s290; }
const s273* s302( const std::wstring& s288 ) const;
s285& s303() { return s291; }
const s285& s303() const { return s291; }
void s304( const std::wstring& s ) { s288 = s; }
static std::wstring s305( const s7::s150& obj,
const std::wstring& dfault = std::wstring( L"" ) );
static std::wstring s312( const s7::s150& obj,
const std::wstring& s313,
const std::wstring& dfault = std::wstring( L"" ) );
void s314( std::wostream* pd, int s205 = 0 ) const;
};
} // namespace transd
namespace s9{
enum s1036{ s1155, s1154, s1156, s1157, s1153 };
class Msg
{
std::wstring func;
std::wstring file;
uint32_t line;
s1036 type;
std::wstring s81;
public:	
Msg( const std::wstring& s, s1036 t = s1153 )
: type( t ), s81( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s1036 t = s1153 )
: func( f ), file( fi ), line( n ), type( t ), s81( s ) {}
s1036 s370() const { return type; }
const std::wstring& Text() const { return s81; }
};
}
namespace transd {
class s1226
{
std::vector<s9::Msg> s28;
size_t s1099;
public:
s1226() : s1099(0){}
void s1069( const std::wstring& s81 );
void s1069( const std::wstring& s81, const std::string& func, 
const std::string& file, uint32_t line );
void s1071( const std::wstring& s81, const std::string& func, 
const std::string& file, uint32_t line );
size_t s1025() const { return s1099; }
};
extern s1226 s1119;
extern std::vector<std::wstring> s1200;
extern std::vector<std::wstring> s1096;
class TDException
: public s2::s18
{
public:
enum class Stage : uint32_t
{
s1142 = 0,
s1135,
s1140,
s1139,
s1134,
s1136,
s1137,
s1138,
s1141
};
private:
Stage stage;
uint32_t category;
std::wstring s1207;
const s273* s740;
public:
TDException( uint32_t cat, uint32_t id, const s273* s740 );
TDException( uint32_t cat, uint32_t id, const s273* s740, const std::wstring& s81 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s205 = 0 ) const override;
uint32_t Category() const { return category;  }
void s1191( Stage st ) { stage = st; }
TDException* s1102( const std::wstring& s = std::wstring( L"" ) );
};
class s1018
: public s2::s18
{
public:
enum class s19 : uint32_t
{
s1084 = ((uint32_t)s18::s19::s27) + 1,
s1181,
s1162,
s1073,
s1085,
s1123,
s1126,
s27
};
s1018( const std::wstring& s )
: s18( s, (uint32_t)s19::s1084){}
s1018( s18& e, const s273& s740, s19 code );
};
class s1026
: public s2::s18
{
public:
enum class s19 : uint32_t
{
s1161 = ( (uint32_t)s18::s19::s27 ) + 1,
s1101,
s27
};
s1026( s19 code );
s1026( const std::wstring& s, s19 code )
: s18( s, (uint32_t)code ) {}
};
#define s1023		1
#define s1022		2
#define s1024						3
#define s1020					4
#define s1021				5
#define s1046(x) throw s1047( L"unknown syntax: " + x );
#define s1045(x) throw s1047( L"syntax error: " + x );
namespace lang {
bool s689( const std::wstring& s, bool s754 = true );
} // namespace tdlang
extern const std::wstring s492;
enum s493 { s494, s495, s496, s497, s498, 
s499, s500, s501, s502, s503, s1177 };
class s272;
class s504;
class s505;
class s282;
class s619;
class s281;
class s327;
class s349;
class s588;
typedef s281 s506;
typedef s281 TDType;
typedef s1::s10<s506> s507;
typedef s1::s10<s505> s508;
typedef s1::s10<s282> s509;
typedef s1::s10<s619> s510;
class s872;
typedef std::map<std::wstring, std::vector<std::wstring>> s1017;
extern s1017 s1095;
typedef uint32_t s1175;
class s281
: public s1::s11
{
friend class s513;
s1039 s1075;
protected:
s493 s515;
s1175 s516;
s272* s310;
int wh;
public:
s281( const s273* ast_=NULL ) : s1075( (s273*)ast_ ), s515( s494 ), s516( 0 ), wh(0)  { }
s281( s493 pt_, const s273* ast_=NULL ) : s1075( (s273*)ast_ ), s515( pt_ ), s516( 0 ), 
wh( 0 ) { }
s281( s272* pass_, s493 pt_, const s273* ast_=NULL ) : s1075( (s273*)ast_ ), s515( pt_ ),
s516( 0 ), s310( pass_ ), wh( 0 )  { }
virtual ~s281();
s493 s517() const { return s515; }
const s273* s631() const { return s1075.s17<s273*>(); }
virtual s505* s519();
virtual s508 s520( s505** s284 = NULL, size_t s521 = 0 );
virtual s1175 s370() const { return s516; }
virtual const std::wstring& s372() const;
virtual void s369( s1175 type );
int s648() const { return wh; }
void setWh( int i ) { wh = i; }
virtual bool s525( const s505* s526 ) const;
virtual const s1017& s1107() const { return s1095;  }
virtual void s523( s282* s965 );
virtual const s505* s527() const;
virtual s281* s353() const;
static s281* s528( const s273& s740, s272* s310, s282* obj,
const std::wstring& s350 );
static s281* s1125( s272* s310, s281* par, s282* obj, s619* s223,
const std::wstring& s350 );
static s507 s1124( const std::wstring& s80, const s273* ast_, s272* s310, s282* s616 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring() const;
/*	static void s298( const std::wstring& s80, size_t& pos,
std::vector<std::wstring>& s160 );
*/
virtual void s314( std::wostream* pd, int s205 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s506*> s529;
s506* s1241( s529& m, const std::wstring& s159 );
void s705( const std::wstring& s, std::wstring& s1233, std::wstring& s629 );
class s505;
class s390;
class s505
: public s281
{
friend class s513;
protected:
std::wstring s391; // DEBUG
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) = 0;
public:
s505( s272* s310, s493 pc, const s273* ast_ ) : s281( s310, pc, ast_ ) { }
virtual ~s505();
virtual void s368() = 0;
virtual s1175 s405( const std::wstring& s361 ) const = 0;
virtual s505* s374( s282* s616, const std::vector<s281*>& l = std::vector<s281*>() ) const = 0;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const;
virtual void s375( s507 p ) const = 0;
virtual const s505* s527() const override = 0;
void s530( const std::wstring& s ) { s391 = s; }
virtual size_t s334() const = 0;
virtual bool operator==( const s505* p ) const = 0;
virtual bool operator<( const s505* p ) const = 0;
virtual s508 s520( s505** s284, size_t s521 ) override { return this; }
virtual s505* s519() override;
virtual bool s583( const std::wstring& s288, s390* s160,
const std::wstring& s350 ) const
{
return false;
};
virtual s281* s626( size_t off )
{
return NULL;
}
};
enum s563 { s534, s535, s536 };
enum s537 { s538, s539, s540 };
typedef s1::s10<s872> s887;
typedef const s872* s1016;
class s872
: public s1::s11
{
public:
typedef s1175 s781;
typedef s781 s983;
typedef std::vector<s781> Cont;
private:
Cont vt;
size_t s1215;
public:
s872() {}
s872( s781 t1, s781 t2 = (s781)-1, s781 t3 = (s781)-1 );
s872( const s872& right );
s872( const Cont& v );
void s369( s781 t );
void s369( s1016 pt );
void s839( s781 t );
void s839( s1016 pt );
s983 s370( size_t n = 0 ) const;
const Cont& s880() const { return vt; }
void s880( std::vector<s281*>& s160 ) const;
bool operator==( const s872& p ) const;
size_t s334() const { return s1215; }
};
class s504;
class s272;
struct s1061
{
std::size_t operator()( const s872& k ) const
{
return k.s334();
}
};
struct s1062
{
std::size_t operator()( const s872& l, const s872& r ) const
{
return l.operator==( r );
}
};
class s513
{
typedef std::map<std::wstring, s1175> s1055;
typedef std::unordered_map<s872, s1175, s1061, s1062> s1058;
typedef std::map<std::wstring, std::set<std::wstring>> s1004;
typedef std::map<s872::s983, s1004> s1017;
std::vector<s508> s1234;
std::vector<std::wstring> s1217;
std::vector<s872> s1222;
s1055 s1218;
s1058 s1223;
s1017 s1008;
s272* s310;
public:
s513( s272* pass_ );
void reset();
void s300();
void s543( const s504& st );
void s227( s505* p, const std::wstring& s365 );
s1175 s1182( const s872::Cont& v, const std::wstring& s365 );
s1175 s1158( const s872::Cont& v );
void s1067( s872::s983 type, const std::wstring& cat, const std::wstring& s1076 );
bool s1120( s872::s983 type, const std::wstring& cat, const std::wstring& s1076 );
void s1109( s872::s983 type, const std::wstring& cat, std::vector<std::wstring>& s160 );
std::wstring s1109( s872::s983 type, const std::wstring& cat );
bool s1127( s872::s983 type );
s505* s545( const s7::s148& s367, s282* s616, const std::wstring& s546 );
s505* s545( const s273& s740, s282* s616, const std::wstring& s546 );
s505* s545( s1175 type, s282* s616, const std::wstring& s546 );
const s505* get( const std::wstring& s79, bool s547 = true ) const;
s1175 s1114( const std::wstring& s365 ) const;
s1175 s1115( const s872& vt ) const;
const s872& s1117( s1175 t ) const;
const s505* s1111( s872::s983 t ) const;
const std::wstring& s859( s1175 n ) const;
bool s163( const std::wstring& s79 ) const;
void s844();
void s314( std::wostream* pd, int s205 = 0 ) const;
static void s1112( const s872::Cont& v, size_t& idx, s872::Cont& s160 );
size_t s1168( const std::wstring& s, size_t& pos, s872::Cont& s160 );
std::wstring s1116( const s872::Cont& tp, size_t& idx );
};
class s548
: public s1::s11
{
std::vector<std::wstring> s549;
s537 pv;
public:
s548() : pv( s538 ) { }
s548( s537 pv, const std::vector<std::wstring>& s550 );
s548( const std::wstring& ag, const std::wstring& s80 );
s537 s587( const std::wstring& s522 ) const;
static std::vector<std::wstring> s552;
};
class s553
: public s1::s11
{
typedef std::map<std::wstring, s548*> s554;
s554 s555;
public:
s553( ) { }
void s556( s537 pv, s273* );
void s557( const std::wstring& s, s548& pl );
void s558( const std::wstring& s, const std::wstring& s551 );
s537 s559( const std::wstring& mem, const std::wstring& s522 );
void s560( const std::wstring& s350,
std::vector<std::wstring>& s160 );
};
class s504
{
public:
enum s152 { s153, s561, s154, s155 };
private:
typedef std::map<std::wstring, s508> s562;
s562 s580;
s563 s564;
s553* s566;
bool s565( const std::wstring& s79, s152 ap = s153 );
public:
s504( ): s564( s535 ), s566( NULL ) {}
s504( s563 am ) : s564( am ), s566( NULL ) {}
s504( const s504& s567 );
void s523( s282* s522, bool s542 = true );
void reset();
void s568( const std::wstring& s79, s505* sym, s152 ap = s153 );
void s568( const std::wstring& s79, s7::s149 s367, s152 ap = s153 );
void s569( const std::wstring& s79 );
void s570( const s7::s150& obj, s152 ap = s153 );
void s299( const s504& t, s152 ap = s153 );
bool s163( const std::wstring& s79 ) const;
s505* get( const std::wstring& s79, bool s547 = true ) const;
void s571( std::vector<std::wstring>& s160 ) const;
void s572( std::vector<std::wstring>& s160 ) const;
void s573( std::vector<std::wstring>& s160 ) const;
void s574( const s504& t, std::vector<std::wstring>& s160 ) const;
void copy( s504& t, s282* s616, s619* s615, s152 ap = s153 ) const;
void s575( s504& t ) const;
void s576( s537 pv, s273* s82 );
void s560( const std::wstring& s350,
std::vector<std::wstring>& s160 );
bool s577( const std::wstring& s288, const std::wstring& s350 ) const;
void s314( std::wostream* pd, int s205 = 0 ) const;
};
class s578
{
typedef std::pair<s505*, std::wstring> s579;
typedef std::multimap<std::wstring, s579> s562;
s562 s580;
std::vector<std::wstring> s586;
public:
s578();
void s581( const std::wstring& s );
void s523( s272* s310, const std::wstring& s585 );
void s582( const std::wstring& s79, s272* s310, const std::wstring& s585 );
bool s583( const std::wstring& sym, s390* ref );
void copy( s578& t ) const;
};
extern s1::s10<s553> s584;
class s272;
typedef void ( *s646 )( s505** s284, size_t n );
class s349
: public s281
{
std::wstring str;
std::wstring s350;
public:
s349( s272* s310, const std::wstring& s, const std::wstring& s351 )
: s281( s310, s498 ), str( s ), s350( s351 ) { }
s349( const s349& right );
const std::wstring& Str() const { return str; }
const std::wstring& s352() const { return s350; }
virtual s281* s353() const override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s354
: public s505
{
protected:
struct s355
{
std::wstring s288;
s1175 s356;
s646 s357;
std::vector<s1175> s1072;
size_t s1150, s1147;
s355( const std::wstring& s712, s646 fp, s1175 s358, 
const std::vector<s1175>& v=std::vector<s1175>(), size_t s1151 = 0, 
size_t s1148=(size_t)-1 )
: s288( s712 ), s356( s358 ), s357( fp ), s1072(v), 
s1150(s1151), s1147(s1148) {}
s355()
: s357( NULL )	{}
size_t s1035() const { return s1150;  }
size_t s1034() const { return s1147;  }
};
typedef std::map<std::wstring, s355*> s359;
virtual const s359& s360() const = 0;
static size_t s807;
public:
s354( s272* s310, const s273* ast_ ) : s505( s310, s495, ast_ ) {}
virtual ~s354() {}
virtual s1175 s405( const std::wstring& s361 ) const override;
static void s838( s272* s310, bool soft = false );
static size_t s863() { return s807;  }
s646 s362( const std::wstring& s361 )const;
virtual const s505* s527() const override;
virtual void* addr() = 0;
virtual s508 s520( s505** s284, size_t s521 ) override;
static s505* s363( s272* s310, const std::wstring& s367, const std::wstring& s350 );
};
class s364;
class s364
: public s354
{
static s359 s366;
int s367;
static void s406( s505** s284, size_t n );
static void s407( s505** s284, size_t n );
static void s408( s505** s284, size_t n );
static void s409( s505** s284, size_t n );
static void s410( s505** s284, size_t n );
static void s411( s505** s284, size_t n );
static void s412( s505** s284, size_t n );
static void s413( s505** s284, size_t n );
static void s414( s505** s284, size_t n );
static void s415( s505** s284, size_t n );
static void s416( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
static void s418( s505** s284, size_t n );
static void s419( s505** s284, size_t n );
static void s420( s505** s284, size_t n );
static void s421( s505** s284, size_t n );
static void s422( s505** s284, size_t n );
static void s423( s505** s284, size_t n );
static void s424( s505** s284, size_t n );
static void s425( s505** s284, size_t n );
static void s426( s505** s284, size_t n );
static void s427( s505** s284, size_t n );
static void s428( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s364( const s364& );
s364( s272* s310, const std::vector<s281*>& l );
s364( s272* s310, int i );
s364( s272* s310, const std::wstring& s, size_t& pos );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual void s523( s282* s615 ) override;	
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
int* s376() { return &s367; }
virtual void* addr() override { return (void*)&s367; }
virtual operator bool() const { return s367 != 0; }
virtual operator int() const { return s367; }
virtual operator double() const { return (double)s367; }
virtual std::wstring to_wstring() const { return std::to_wstring( s367 ); }
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s377
: public s354
{
static s359 s366;
double s367;
static void s406( s505** s284, size_t n );
static void s407( s505** s284, size_t n );
static void s408( s505** s284, size_t n );
static void s409( s505** s284, size_t n );
static void s410( s505** s284, size_t n );
static void s411( s505** s284, size_t n );
static void s412( s505** s284, size_t n );
static void s413( s505** s284, size_t n );
static void s414( s505** s284, size_t n );
static void s415( s505** s284, size_t n );
static void s416( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
static void s418( s505** s284, size_t n );
static void s419( s505** s284, size_t n );
static void s420( s505** s284, size_t n );
static void s421( s505** s284, size_t n );
static void s422( s505** s284, size_t n );
static void s429( s505** s284, size_t n );
static void s430( s505** s284, size_t n );
static void s423( s505** s284, size_t n );
static void s425( s505** s284, size_t n );
static void s426( s505** s284, size_t n );
static void s431( s505** s284, size_t n );
static void s428( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s377( const s377& r );
s377( s272* s310, const std::vector<s281*>& l );
s377( s272* s310, double d );
s377( s272* s310, const std::wstring& s, size_t& pos );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual void s523( s282* s615 ) override;	
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
double* s376() { return &s367; }
virtual void* addr() override { return (void*)&s367; }
virtual operator bool() const { return s367 != 0.0; }
virtual operator int() const { return (int)s367; }
virtual operator double() const { return s367; }
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s379
: public s354
{
static s359 s366;
bool s367;
static void s406( s505** s284, size_t n );
static void s432( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s379( s272* s310, bool b );
s379( s272* s310, const std::wstring& s, size_t& pos );
s379( const s379& right );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
bool* s376() { return &s367; }
virtual void* addr() override { return (void*)&s367; }
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual void s523( s282* s615 ) override;	
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
virtual operator bool() const { return s367; }
virtual operator int() const override { return (int)s367; }
virtual operator double() const override { return (double)s367; }
virtual std::wstring to_wstring() const override { return ( s367 ? L"true" : L"false" ); }
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s379> s388;
extern s1::s10<s379> s389;
class s380
: public s354
{
static s359 s366;
static void s847( s505** s284, size_t n );
static void s532( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
std::wstring s81;
public:
s380( const s380& right );
s380( s272* s310, const std::wstring& s = std::wstring( L"" ) );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
const std::wstring& Msg() const { return s81; }
void s382( const std::wstring& s ) { s81 = s; }
virtual void* addr() override { return (void*)0; }
virtual void s523( s282* s615 ) override;	
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
virtual std::wstring to_wstring() const override { return s81; }
virtual operator bool() const { return false; }
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s383
: public s354
{
static s359 s366;
virtual void s368() override {}
virtual const s359& s360() const override { return s366; }
public:
s383( s272* s310 );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual void* addr() override { return (void*)0; }
virtual s281* s353() const override;
virtual void s375( s507 p ) const override { }
virtual void s523( s282* s615 ) override;	
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
virtual std::wstring to_wstring() const {	return L"";	}
virtual operator bool() const { return false; }
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s383> s384;
class s403
: public s354
{
static s359 s366;
virtual void s368() override {}
virtual const s359& s360() const override { return s366; }
public:
s403( s272* s310, s493 pc = s494 );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s281* s353() const override;
virtual void* addr() override { return (void*)0; }
virtual void s375( s507 p ) const override { }
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
virtual void s523( s282* s615 ) override;	
virtual operator bool() const { return false; }
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s364> s828;
extern s1::s10<s377> s862;
extern s1::s10<s379> s806;
extern s1::s10<s380> s879;
extern s1::s10<s383> s784;
extern s1::s10<s403> s832;
extern s1::s10<s403> s950;
extern s1::s10<s403> s385;
extern s1::s10<s403> s386;
extern s1::s10<s403> s387;
extern s1::s10<s403> s954;
typedef s364 TDInt;
typedef s377 TDDouble;
class s390
: public s281
{
std::wstring s391;
s508 s392;
const s505* s393;
std::vector<size_t> s394;
size_t s395;
public:
s390( const std::wstring& s, s272* s310, s493 cat = s496 );
s390( const s390& right );
virtual s505* s519() override;
virtual const s505* s527() const override { return s393; }
const s508 s400() { return s392; }
const std::wstring& s647() const { return s391; }
virtual s508 s520( s505** s284, size_t s521 ) override;
s505* s396() const;
s505* s397();
void s398( size_t off, const s505* proto );
size_t s399() const { return s395; }
virtual s281* s353() const override;
virtual void s523( s282* s615 ) override;
void s401( s505* p ) { s392 = p; }
void s402( s505* p ) { s393 = p; }
void s1082( const std::vector<std::wstring> &v );
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
typedef s1::s10<s390> s511;
class s619;
class s282;
typedef std::vector<std::pair<std::wstring, std::wstring>> s653;
typedef std::map<std::wstring, s282*> s654;
typedef std::map<std::wstring, s273*> s655;
class s282
: public s505
{
protected:
const s282* s656;
const s282* s657;
s282* ns;
const std::wstring& s365;
const std::wstring s288;
std::wstring s658;
s504 s659;
s578* s660;
std::vector<s507> s661;
std::vector<std::wstring> s662;
virtual void s368() override { }
public:
s282( const s282& s664, const s273* ast_=NULL );
s282( s272* s310, s1175 s358, s493 pc/* = s494*/, const s273* ast_ = NULL );
s282( const std::wstring& s288, s272* s310, s493 pc, const s273* ast_ = NULL );
s282( const std::wstring& s365, const std::wstring& s288, s272* s310, s504& s665,
const s504& s659, const s273* ast_ = NULL );
s282( s273& s740, s272* s310, s493 pc, s282* ns, s563 am, 
s654& cl, s653& cnl, s655& al );
const std::wstring& s372() const { return s365; }
const std::wstring& s309() const { return s288; }
std::wstring s308() const;
virtual std::wstring s903() const { return ns->s308(); }
static s281* s666( const s7::s150& obj, const std::wstring& s288, s272* s310 );
static s281* s666( std::multimap<std::wstring, s506*>& v, s506* s615 );
s505* s667( const s273& s740, const std::wstring& s350 );
s505* s667( const s7::s148& s367 );
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s1175 s405( const std::wstring& s361 ) const override;
virtual bool s525( const s505* s526 ) const override;
virtual const s1017& s1107() const override { return s1095; }
bool s773( const std::wstring& f ) const;
void s925( const std::wstring& s79, s505* s367 );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual const s505* s527() const override { return s656; }
const s282* s668() const { return s657; }
const std::wstring& s669() const { return s658; }
s505* s362( const std::wstring& s288, const std::wstring& s350,
bool s547 = true ) const;
void s678( s273& s740 );
void s582( const std::wstring& s79, const std::wstring& s585 );
void s670( s273& s740 );
void s1068( s273& s740 );
void s671( const std::wstring& s350,	std::vector<std::wstring>& s160 );
virtual bool s583( const std::wstring& s288, s390* s160,
const std::wstring& s350 ) const override;
size_t s672( const std::wstring& s288 ) const;
virtual s281* s626( size_t off ) override;
s505* s674( const std::wstring& s288, const std::wstring& s350,
bool s547=true ) const;
bool s675( const std::wstring& sym, const std::wstring& s522 ) const;
bool s559( const std::wstring& sym );
virtual void s523( s282* s965 ) override;
void s677( const s504& s284 ); 
void s161( s273& s740 );
virtual s281* s353() const  override;
virtual void s375( s507 p ) const override;
void s676( s282* s679 ) const;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
virtual std::wstring to_wstring() const override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const;
};
class s588
: public s281
{
const std::wstring s629;
std::vector<s281*> s284;
s1039 past;
public:
s588( s272* pass_, const s273* ast_ )
: s281( pass_, s499 ), past( (s273*)ast_ )
{
}
s588( s272* pass_, const std::wstring& methName, const std::vector<s281*>& l, const s273* s740 );
s588( const s588& s567 );
const std::wstring& s309() const { return s629; }
std::vector<s281*>& s630() { return s284; }
const s273* s631() { return past; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override { }
};
typedef s1::s10<s588> s512;
class s619;
class s272;
typedef s619 TD;
class s354;
typedef s619 Transd;
typedef std::vector<s507> s604;
typedef std::vector<s508> s605;
typedef std::vector<s507> s606;
class s619
: public s282
{
public:
enum s590 { s591, s592, s593, s594, s595, s596 };
protected:
std::wstring s288;
std::wstring s706;
enum s597 { s598, s599, s600, s601 };
s590 s602;
s597 s603;
s505** s607;
s506** s608;
size_t s521, nlocs;
s605 s610;
s604 s284;
std::vector<s508> s1080;
std::vector<s505*> s611;
s606 s612;
std::vector<std::vector<s506*>> s613;
s508 s614;
s509 s616;
s510 s615;
const s273* past;
s281* s921( s281* par );
void s617(const std::wstring& s350);
void s618(const std::wstring& s350);
public:
s619( s272* s310, s282* s620, s619* s621, s590 ct, 
const std::wstring& s712, const s273* s740 )
: s282( s310, 0, s497, s740 ), s288( s712 ), s602( ct ),  
s614( NULL ),	s616( s620 ), s615( s621 ), past( s740 ) { }
s619( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s619( const s619& right, s282* s616, s619* s615, const std::vector<s281*>& s284,
const s273* s740 );
virtual ~s619();
s590 s942() const { return s602; }
void s622( s597 vt ) { s603 = vt; }
s597 s623() const { return s603; }
virtual const std::wstring& s309() const { return s288; }
virtual std::wstring s903() const override;
const s273* s631() const { return past; }
virtual s505* s519() override { return s614; }
virtual void s523( const std::wstring& s350, bool proc );
void s624( const std::vector<s507>& l );
typedef std::vector<std::pair<std::wstring, s508>> s904;
void s873( s904& s160 ) const;
void s625( const std::wstring& s350 );
virtual bool s583( const std::wstring& s288, s390* ref,
const std::wstring& s350 ) const override;
virtual s281* s626( size_t off ) override;
virtual s508 s520( s505** s284 = NULL, size_t s521 = 0 ) override;
virtual s281* s353() const override;
static s619* s627( const s273& s740, s272* s310, s282* obj,
const std::wstring& s288, const std::wstring& s585 );
static s588* s1240( const s273& s740, s272* s310, s282* obj, 
const std::wstring& s585 );
static s619* s628( s588* cs, s272* s310, s282* s616, s619* s223,
const std::wstring& s585 );
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s914
: public s619
{
s646 s589;
public:
s914( s272* s310, s619* s615, const std::vector<s281*>& l, s646 s589,
s1175 s516, const s273* s740 );
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284 = NULL, size_t s521 = 0 ) override;
};
class s915
: public s619
{
public:
s915( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 )
: s619( s310, s616, s615, l, s740 ) {}
s915( const s915& right, s282* s616, s619* s615, const std::vector<s281*>& s284,
const s273* s740 );
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284 = NULL, size_t s521 = 0 ) override;
};
class Stream
{
public:
Stream() {}
virtual ~Stream() {}
virtual void write( s507 p );
};
class s531
: public s354, public Stream
{
static s359 s366;
std::basic_stringstream<wchar_t> ss;
static void s532( s505** s284, size_t n );
static void s345( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s531( const s531&, const s273* ast_ = NULL );
s531( s272* s310, const s273* ast_ = NULL );
~s531(){}
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
virtual void* addr() override { return (void*)&ss; }
virtual void write( s507 p ) override;
virtual std::wstring to_wstring() const override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s531> s874;
class s378;
class s378
: public s354
{
static s359 s366;
std::wstring s367;
static void s406( s505** s284, size_t n );
static void s407( s505** s284, size_t n );
static void s849( s505** s284, size_t n );
static void s980( s505** s284, size_t n );
static void s981( s505** s284, size_t n );
static void s833( s505** s284, size_t n );
static void s854( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
static void s418( s505** s284, size_t n );
static void s419( s505** s284, size_t n );
static void s420( s505** s284, size_t n );
static void s421( s505** s284, size_t n );
static void s422( s505** s284, size_t n );
static void s428( s505** s284, size_t n );
static void s1146( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s378( const s378&, const s273* ast_ = NULL );
s378( s272* s310, s282* s616, const std::vector<s281*>& l, const s273* ast_ = NULL );
s378( s272* s310, const std::wstring& s = std::wstring( L"" ), const s273* ast_ = NULL );
s378( s272* s310, const std::wstring& s, size_t& pos, const s273* ast_ = NULL );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const override;
virtual bool operator<( const s505* p ) const override;
std::wstring* s376() { return &s367; }
virtual void* addr() override { return (void*)&s367; }
virtual operator bool() const override { return !s367.empty(); }
virtual operator int() const override;
virtual operator double() const override;
virtual std::wstring to_wstring() const override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
typedef s378 TDString;
extern s1::s10<s378> s846;
class s877
: public s619
{
s507 s813, s763;
s507 s864, s856;
size_t s760, nTo;
int s848, s785;
s1::s10<s378> str;
enum s787 { s759, s826, s814, s876 };
public:
s877( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
s877( s272* s310 );
virtual const std::wstring& s309() const override { return s808; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s912;
struct s913;
class Iterator
{
public:
virtual s281* s326() = 0;
virtual s281* s1057() = 0;
};
class s340
: public s354
{
public:
s340( s272* s310, const s273* ast_ )
: s354( s310, ast_ ) {}
virtual ~s340() {}
virtual Iterator* s325( s505* start, s505* stop ) = 0;
virtual s1175 s331() const = 0;
virtual s1175 s1028() const { return 0; }
virtual s1175 ValType() const { return 0; }
virtual s505* sort( bool reverse, s913* cmp );
};
class s1060 
: public Iterator
{
typedef std::vector<s507>::iterator s1031;
s1::s10<s327> v;
s1031 s329, s1205;
size_t s1088;
public:
s1060( s1031 start, s1031 stop, s327* v_ );
virtual s281* s326() override;
virtual s281* s1057() override;
};
class s327
: public s340
{
typedef std::vector<s507> s1059;
static s359 s366;
s1175 s328;
s1059 s367;
std::wstring s522;
static void s406( s505** s284, size_t n );
static void s341( s505** s284, size_t n );
static void s342( s505** s284, size_t n );
static void s343( s505** s284, size_t n );
static void s344( s505** s284, size_t n );
static void s345( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
static void s346( s505** s284, size_t n );
void s1065( const std::wstring& s80, s282* s616, const s273* ast_ );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s327( s272* s310, s282* s616, const std::wstring& s80, const s273* ast_=NULL,
const std::wstring& s75 = L"," );
s327( s272* s310, const std::vector<s281*>& l, const s273* ast_=NULL );
s327( const s327& right, const s273* ast_=NULL );
virtual ~s327() override;
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const override;
virtual s1175 s331() const override { return s328; }
virtual s1175 s1028() const override { return s828->s370(); }
virtual s1175 ValType() const { return s328; }
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s367; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
s507 operator[]( size_t n ) { return s367[n]; }
const s507& operator[]( size_t n ) const { return s367[n]; }
virtual Iterator* s325( s505* start, s505* stop) override;
void clear() { s367.clear(); }
void add( s507 el ) { s367.push_back( el ); }
void erase( size_t n ) { s367.erase( begin( s367 ) + n ); }
size_t size() const { return s367.size(); }
virtual s505* sort( bool reverse, s913* cmp ) override;
std::vector<s507>& s332() { return s367; }
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s1056
: public Iterator
{
typedef std::vector<s507>::iterator s1031;
s1031 s329, s1205;
public:
s1056( s1031 start, s1031 stop );
virtual s281* s326() override;
virtual s281* s1057() override;
};
class s797
: public s340
{
protected:
typedef std::vector<s507> s1059;
static s359 s366;
std::vector<s507> s367;
std::vector<s507>::iterator s329;
std::wstring s522;
static void s406( s505** s284, size_t n );
static void s341( s505** s284, size_t n );
static void s342( s505** s284, size_t n );
static void s343( s505** s284, size_t n );
static void s344( s505** s284, size_t n );
static void s345( s505** s284, size_t n );
static void s417( s505** s284, size_t n );
static void s346( s505** s284, size_t n );
static void s1104( s505** s284, size_t n );
static void s1189( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s797( s272* s310, const s273* ast_=NULL )
: s340( s310, ast_ ) {}
s797( s272* s310, s282* s616, const std::wstring& s80, 
const s273* ast_=NULL, const std::wstring& s75 = L"," );
s797( s272* s310, const std::vector<s281*>& l, const s273* ast_ = NULL );
s797( const s797& right, const s273* ast_ = NULL );
virtual ~s797() override;
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const override;
virtual s1175 s331() const override;
virtual s1175 s1028() const override { return s828->s370(); }
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s367; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
s507 operator[]( size_t n ) { return s367[n]; }
const s507& operator[]( size_t n ) const { return s367[n]; }
virtual Iterator* s325( s505* start, s505* stop) override;
void clear() { s367.clear(); }
void add( s507 el ) { s367.push_back( el ); }
void assign( const std::vector<s507>& v );
size_t size() const { return s367.size(); }
std::vector<s507>& s332() { return s367; }
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s1053
: public s797
{
public:
s1053( s272* s310, s282* s616, const std::wstring& s80, const s273* ast_=NULL );
s1053( s272* s310, const std::vector<s281*>& l, const s273* ast_ = NULL );
s1053( const s1053& right, const s273* ast_ = NULL );
virtual ~s1053() override {}
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual void s523( s282* s965 ) override;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const override;
};
class s1041
: public s354
{
static s359 s366;
std::pair<s507, s507> s367;
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
static void s1104( s505** s284, size_t n );
static void s1189( s505** s284, size_t n );
public:
s1041( s272* s310, const std::wstring& s80, const s273* ast_ = NULL );
s1041( s272* s310, const std::vector<s281*>& l, const s273* ast_ = NULL );
s1041( const s797& right, const s273* ast_ = NULL );
virtual ~s1041() override;
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s367; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
s507 first() { return s367.first; }
s507 second() { return s367.second; }
std::pair<s507, s507>& s332() { return s367; }
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
struct s333
{
std::size_t operator()( const s508 k ) const
{
return k->s334();
}
};
struct s335
{
bool operator()( const s508 l, const s508 r ) const
{
return l->operator==( (s505*)&(*r) );
}
bool operator()( const s505* l, const s505* r ) const
{
return l->operator==( r );
}
bool operator()( const s505& l, const s505& r ) const
{
return l.operator==( &r );
}
};
class s1030
: public Iterator
{
typedef std::unordered_map<s508, s508, s333, s335>::iterator s1031;
s1031 s329, s1205;
s1053 s1091;
public:
s1030( s1031 start, s1031 stop );
virtual s281* s326() override;
virtual s281* s1057() override;
};
class s336
: public s340
{
static s359 s366;
s1175 s337;
s1175 s338;
s1175 s328;
typedef std::unordered_map<s508, s508, s333, s335> s1029;
s1029 s367;
s1029::iterator s329;
std::wstring s522;
static void s347( s505** s284, size_t n );
static void s341( s505** s284, size_t n );
static void s1118( s505** s284, size_t n );
static void s406( s505** s284, size_t n );
static void s348( s505** s284, size_t n );
static void s343( s505** s284, size_t n );
static void s346( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s336( s272* s310, const s273* ast_ = NULL );
s336( s272* s310, const std::vector<s281*>& l, const s273* ast_ = NULL );
s336( s272* s310, s282* s616, const std::wstring& s80, const s273* ast_ = NULL );
s336( const s336& right, const s273* ast_ = NULL );
s336( s272* s310, const std::wstring& s, size_t& pos, const s273* ast_ = NULL );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const override;
virtual s1175 s331() const override { return s328; }
virtual s1175 s1028() const override { return s337; }
virtual s1175 ValType() const override { return s338; }
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s367; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
virtual Iterator* s325( s505* start, s505* stop) override;
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s404
: public s340,
public Iterator
{
s507 s616;
s508 s1186;
s508 s1086;
s507 start, stop, where, s1184;
int s1201, s1203, s837;
bool s1077, s1078;
Iterator* s329;
s390 s1089;
s281* s1090;
s282* ns;
static s359 s366;
s1::s10<s364> s367, s721;
long first{}, last{}, incr{};
s507 fir, las, inc;
std::wstring s522;
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s404( s272* s310, const std::wstring& s80, const s273* ast_ = NULL );
s404( s272* s310, long fi, long la, long inc, const s273* ast_ = NULL );
s404( s272* s310, s507 fi, s507 la, s507 inc, const s273* ast_ = NULL );
s404( const s404& right, const s273* ast_ = NULL );
s404( s272* s310, s282* s616, const std::vector<s281*>& l, const s273* ast_ = NULL );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual s505* s374( s282* s616, const std::vector<s1175>& vt ) const override;
virtual s1175 s331() const override { return s721->s370(); }
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s367; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual bool s583( const std::wstring& s288, s390* s160,
const std::wstring& s350 ) const override;
virtual s281* s626( size_t off ) override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
virtual Iterator* s325( s505* start, s505* stop) override;
virtual s281* s326() override;
virtual s281* s1057() override;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
class s1044
: public s404
{
s510 s1172;
s510 set;
s510 eq;
s507 start;
s507 end;
s507 incr;
s507 s1091;
bool s1159;
public:
s1044( s272* s310, const std::vector<s281*>& l );
virtual void s523( s282* s965 ) override;
virtual Iterator* s325( s505* start, s505* stop ) override;
virtual s281* s326() override;
};
extern s1::s10<s327> s768;
extern s1::s10<s797> s791;
extern s1::s10<s1053> s1054;
extern s1::s10<s336> s774;
extern s1::s10<s404> s868;
typedef s327 TDVector;
typedef s336 TDIndex;
struct s913
{
std::vector<s507>s937;
s510 s935;
s913( s510 s936 ) : s935( s936 ) { s937.resize( 2 ); }
virtual bool operator()( const s507 l, const s507 r )
{
s937[0] = l;
s937[1] = r;
s935->s624( s937 );
return (bool)*s935->s520( 0, 0 );
}
};
class s912
: public s619
{
bool reverse;
s510 s935;
public:
s912( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s929; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s434
: public s354
{
static s359 s366;
std::wstring path;
std::wstring s551;
s327 s802;
s327 s865;
static void s428( s505** s284, size_t n );
static void s435( s505** s284, size_t n );
static void s436( s505** s284, size_t n );
static void s1092( s505** s284, size_t n );
static void s343( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s434( s272* s310, const std::wstring& s80, const s273* ast_=NULL );
s434( const s434& right, const s273* ast_ = NULL );
s434( s272* s310, const std::wstring& s, size_t& pos, const s273* ast_ = NULL );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)&s802; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s434> s870;
} // namespace
namespace transd
{
class s633
: public s619
{
public:
s633( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, 
const s273* s740 );
virtual const std::wstring& s309() const override { return s242; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
s281* s751( const std::wstring& s288, s390* ref,
const std::wstring& s350 ) const;
virtual s281* s353() const override;
};
class s315
: public s619
{
s507 s316;
public:
s315( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, 
const s273* s740 );
virtual const std::wstring& s309() const override { return s264; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s318
: public s619
{
s507 s319;
s511 s320;
s508 s321;
s390 s322;
s364 s323;
public:
s318( s272* s310, s282* s616, Transd* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s263; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s644
: public s619
{
s511 s752;
s508 varval;
s507 s319;
s507 where;
s507 select;
s390 s322;
s364 s323;
public:
s644( s272* s310, s282* s616, Transd* s615, const std::vector<s281*>& l, 
const s273* s740 );
virtual const std::wstring& s309() const override { return s269; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s632
: public s619
{
std::vector<s1175> types;
std::vector<s510> s682;
public:
s632( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
void s681( s1175 type, s619* pOvr );
virtual s508 s520( s505** s284, size_t s521 ) override;
};
class s910
: public s619
{
public:
s910( s272* s310, s282* s620, s619* s621, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s261; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s911
: public s619
{
public:
s911( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s928; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s987
: public s619
{
int code;
public:
s987( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s991; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s635
: public s619
{
public:
s635( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s253; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s636
: public s619
{
public:
s636( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s636( s272* s310 );
virtual const std::wstring& s309() const override { return s252; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s637
: public s619
{
s606 s651;
std::vector<s606> s652;
public:
s637( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s637( s272* s310 );
virtual const std::wstring& s309() const override { return s239; }
virtual void s523( const std::wstring& s350, bool proc ) override;
void s780( bool proc );
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s638
: public s619
{
s508 s44;
public:
s638( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s638( s272* s310 );
virtual const std::wstring& s309() const override { return s260; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s640
: public s619
{
s380 s81;
public:
s640( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s640( s272* s310 );
virtual const std::wstring& s309() const override { return s268; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s642
: public s619
{
public:
s642( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s642( s272* s310 );
virtual const std::wstring& s309() const override { return s267; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s641
: public s619
{
s390 s79;
s380 s650;
s1::s10<s642> ctch;
public:
s641( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
s641( s272* s310 );
virtual const std::wstring& s309() const override { return s266; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s643
: public s619
{
s508 s649;
std::vector<s281*> s727;
s508 s721;
public:
s643( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s270; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
bool s583( const std::wstring& s288, s390* ref, 
const std::wstring& s350 ) const override;
virtual s281* s353() const override;
};
class s803
: public s619
{
std::vector<std::wstring> fields;
public:
s803( s272* s310, s282* s616, s619* s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s799; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s639
: public s619
{
public:
s639( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
s639( s272* s310 );
virtual const std::wstring& s309() const override { return s265; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s645
: public s619
{
static s272* s997;
public:
s645( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
s645( s272* s310 );
virtual const std::wstring& s309() const override { return s271; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s852
: public s619
{
public:
s852( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
s852( s272* s310 );
virtual const std::wstring& s309() const override { return s822; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s827
: public s619
{
std::wstring s995;
public:
s827( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
s827( s272* s310 );
virtual const std::wstring& s309() const override { return s882; }
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
class s829
: public s1::s11
{
typedef std::map<std::wstring, s507> s767;
s767 s812;
size_t rechash;
public:
s829() {}
explicit s829( s272* s310, const std::wstring& rec, const std::vector<std::wstring>& s788,
std::vector<s507>& types );
s508 s809( const std::wstring& s79, bool s754=true ) const;
void s941( s797& s160 ) const;
void s572( std::vector<std::wstring>& s160 ) const;
size_t s334() const;
bool operator==( const s829* p ) const;
bool operator<( const s829* p ) const;
std::wstring to_wstring() const;
void s314( std::wostream* pd, int s205 = 0 ) const;
};
typedef s1::s10<s829> s883;
class s871
: public s1::s11
{
typedef std::vector<s507> s779;
s779 s867;
size_t s855;
public:
s871() {}
s871( std::vector<std::wstring>& s776, s883 rec );
size_t s334() const;
bool operator==( const s871* p ) const;
bool operator<( const s871* p ) const;
void s314( std::wostream* pd, int s205 = 0 ) const;
};
typedef s1::s10<s871> s778;
struct s821
{
std::size_t operator()( const s778 k ) const
{
return k->s334();
}
};
struct s755
{
std::size_t operator()( const s778 l, const s778 r ) const
{
return l->operator==( ( s871* )&( *r ) );
}
};
struct s920
{
std::size_t operator()( const s883 k ) const
{
return k->s334();
}
};
struct s919
{
std::size_t operator()( const s883 l, const s883 r ) const
{
return l->operator==( ( s829* )&( *r ) );
}
};
class s683
: public s354
{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
typedef std::map<std::wstring, std::multimap<s508, s883>> s339;
typedef std::unordered_map<s778, s883, s821, s755> s841;
private:
static s359 s366;
std::map<std::wstring, s339> s949;
BaseMap s684, s685, s686;
BaseMap::iterator s329;
s841 s805;
std::wstring s522;
static void s840( s505** s284, size_t n );
static void s857( s505** s284, size_t n );
static void s800( s505** s284, size_t n );
static void s820( s505** s284, size_t n );
static void s348( s505** s284, size_t n );
static void s343( s505** s284, size_t n );
static void s346( s505** s284, size_t n );
static void s932( s505** s284, size_t n );
virtual void s368() override;
virtual const s359& s360() const override { return s366; }
public:
s683( s272* s310, const s273* ast_ = NULL );
s683( s272* s310, const std::vector<s281*>& l, const s273* ast_ = NULL );
s683( s272* s310, const std::wstring& s80, const s273* ast_ = NULL );
s683( const s683& right, const s273* ast_ = NULL );
s683( s272* s310, const std::wstring& s, size_t& pos, const s273* ast_ = NULL );
virtual s505* s373( const s273& s740, s282* s616, const std::wstring& s350 ) override;
virtual s505* s374( s282* s616, const std::vector<s281*>& l ) const override;
virtual bool s525( const s505* s526 ) const override;
virtual void* addr() override { return (void*)NULL; }
virtual void s523( s282* s965 ) override;
virtual s281* s353() const override;
virtual void s375( s507 p ) const override;
virtual size_t s334() const;
virtual bool operator==( const s505* p ) const;
virtual bool operator<( const s505* p ) const;
void s687( const std::wstring& s202 );
void s688( const std::wstring& q );
void s758( const std::wstring& s885, const std::wstring& s788 );
void s931( const std::wstring& s934 );
void select( std::wstring& s934, s508 s688, 
s339::mapped_type::iterator& s952, s339::mapped_type::iterator& s953 );
virtual std::wstring to_wstring() const;
virtual void s314( std::wostream* pd, int s205 = 0 ) const override;
};
extern s1::s10<s683> s811;
} // namespace
namespace transd {
class s825
: public s354
{
};
struct s789
{
enum s909 { s892=0, s899 };
int distinct;
int	s977;
std::wstring s976;
int s956;
s789()
: distinct( -1 ), s977( -1 ), s956( -1 )
{	}
};
class s988
: public s619
{
size_t s999;
s508 s721;
public:
s988() : s619( NULL, NULL, NULL, s592, L"", NULL ), 
s721( new s379( NULL, false ) ){ }
void s998( size_t idx ) { s999 = idx; }
virtual s508 s520( s505** s744, size_t s521 ) override
{
s507 l = s284[0];
s507 r = s284[1];
*s721.s17<s379*>()->s376() = l.s17<s797*>()->operator[]( s999 ).s17<s505*>()->
operator<( r.s17<s797*>()->operator[]( s999 ).s17<s505*>() );
s508 s996 = s721;
return s996;
}
};
class s327;
class s845
: public s619
{
s507 db;
s511 verb;
s507 what;
s507 where;
s507 s956;
s1::s10<s327> s795;
s789 s866;
s390 s777;
s509 s836;
public:
s845( s272* s310, s509 s616, s510 s615, const std::vector<s281*>& l, const s273* s740 );
virtual const std::wstring& s309() const override { return s270; }
virtual void s523( const std::wstring& s350, bool proc ) override;
virtual s508 s520( s505** s284, size_t s521 ) override;
virtual s281* s353() const override;
};
typedef int HPROG;
struct s762
{
std::vector<std::wstring> s697;
std::wstring entry;
};
class s588;
class s272
: public s282
{
std::vector<std::wstring> s207;
s273 s740;
std::wstring s208;
std::wstring s817;
void s209( const std::wstring& s288 );
void s210( const s7::s150& obj, s762& s160 );
void s221( const std::wstring& s202, const s7::s150& obj );
s513 s211;
s504 s212;
typedef std::map<std::wstring, s505*> s213;
s213 s214;
typedef std::map<uint32_t, std::set<std::wstring>> s1033;
public:
s272();
~s272();
const std::wstring& s756() const { return s817; }
virtual std::wstring s903() const { return L"::"; }
void s523( bool soft = false );
void reset();
void s215( s273& s216 );
void s217( const std::wstring& s218 );
void s219( s7::s150& obj );
void s220( const std::wstring& s218 );
s505* run( const std::vector<std::wstring>& s727 );
s505* callFunc( const std::wstring& s629, std::vector<std::wstring>& l );
s510 getProc( const std::wstring& s629 );
s513& TR() { return s211; }
s619* s222( const std::wstring& s629, std::vector<s281*>& s284, s282* s616, s619* s223,
const s273* s740 );
s281* s224( const std::wstring& s367, s282* s616, const std::wstring& s350 );
void s226( const std::wstring& s );
void s227( s505* p, const std::wstring& s365 );
void s228( const std::wstring& s367, const std::wstring& s350,
std::vector<std::wstring>& s160 );
virtual bool s583( const std::wstring& s288, s390* s160,
const std::wstring& s350 ) const override;
s508 s229( const std::wstring& s367, const std::wstring& s350 );
bool s230( const std::wstring& s,	const s505* s1133) const;
s281* s231( const std::wstring& sym, const std::wstring& s522,
bool s547 = true );
void* s232( const std::wstring& s288 );
virtual void s314( std::wostream* pd, int s205 = 0 ) const;
};
typedef s1::s10<s272> s761;
void evaluateExpression( const std::wstring& s80 );
HPROG createAssembly();
void loadProgram( HPROG handle, const std::wstring& s197 );
void s219( HPROG handle, s7::s150& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s727 );
void* callFunc( HPROG handle, const std::wstring& s80, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s629 );
void* s232( HPROG handle, const std::wstring& s288 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1233, const std::wstring& symName,
const std::wstring& s350 );
void importFile( HPROG handle, const std::wstring& s1233, const std::wstring& s46,
const std::wstring& s350 );
HPROG initShell( const std::wstring& s1233, const std::wstring& modText );
typedef s2::s18 TransDException;
} // namespace transd
