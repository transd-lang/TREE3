
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
class s1439
{
int refs;
public:
s1439()
{
refs=0;
}
~s1439()
{
}
void reset()
{
refs = 0;
}
int s11()
{
refs++;
return refs;
}
int s12()
{
refs--;
return refs;
}
int s1440()
{
return refs;
}
};
#ifdef s1446
#define s1447(x) x;
#else
#define s1447(x)
#endif
template<bool>
struct s1441
{
void s1442(){}
void s1443(){}
};
template<>
struct s1441<true>
{
#ifdef s1446
static int s167;
void s1442() { s167++; }
void s1443() { s167--; }
#endif
};
class s10
{
int refs;
public:
s10() : refs(0){}
virtual ~s10()
{
}
void s11()
{
refs++;
}
void s12()
{
if( --refs == 0 )
deallocate();
}
int s1440()
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
template<class C, bool bCnt=false>
class s1445
: public s1441<bCnt>
{
C* p;
s1439*	s1444;
public:
/*
*	Constructors.
*/
s1445(C *_p)
:p(_p)
{
if ( p ) {
s1444 = new s1439;
s1444->s11();
s1447( this->s1442() )
}
}
s1445( const s1445& ptr )
{
if ( ptr.p ) {
p = ptr.p;
s1444 = ptr.s1444;
s1444->s11();
}
else {
p = nullptr;
s1444 = nullptr;
}
}
s1445()
:p(nullptr)
{
s1444 = nullptr;
}
template<class D> // converting copy constructor for passing by value
s1445( s1445<D> &pn )
{
p = nullptr;
s1444 = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p) {
s1444 = pn.RefCount();
s1444->s11();
}
}
}
/*
*	Destructor.
*/
~s1445()
{
if(	p && !s1444->s12()	) {
delete p;
delete s1444;
s1447( this->s1443() )
}
}
/*
*	Operators.
*/
operator C*(){return p;}
operator C*()const {return p;}
C& operator*(){return *p;}
const C& operator*()const{return *p;}
C* operator->(){return p;}
const C* operator->()const{return p;}
s1445& operator=( s1445<C> &sptr )
{
if ( p  && !s1444->s12() ) {
delete p;
delete s1444;
p = nullptr;
s1444 = nullptr;
s1447( this->s1443() )
}
p = sptr.p;
if ( sptr.p ) {
s1444 = sptr.s1444;
s1444->s11();
}
return *this;
}
s1445& operator=( const s1445<C> &sptr ){ return operator=((s1445<C>&) sptr); }
s1445& operator=( C* ptr )
{
if ( p  && !s1444->s12() ) {
delete p;
delete s1444;
p = nullptr;
s1444 = nullptr;
s1447( this->s1443() )
}
p = ptr;
if ( ptr ) {
s1444 = new s1439;
s1444->s11();
s1447( this->s1442() )
}
return *this;
}
template<class Base>
operator Base*()
{
return checked_cast<C, Base>( p );
}
template<class D>
s1445& operator=( s1445<D> &p_ )
{
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
return operator=( nullptr );
}
template<class ToType>
ToType s16()
{
return static_cast<ToType>( p );
}
template<class ToType>
ToType dcast()
{
return dynamic_cast<ToType>( p );
}
bool operator ==(const s1445<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
bool operator !=(const s1445<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
bool s13()const{return p == nullptr;}
bool s14()const{return p != nullptr;}
s1439* RefCount() { return s1444; }
int s1440() { return s1444->s1440(); }
void refUpcount() { s1444->s11(); }
void refDowncount() 
{ 
if ( p  && !s1444->s12() ) {
delete p;
delete s1444;
p = nullptr;
s1444 = nullptr;
s1447( this->s1443() )
}		
}	
};
template <class C>
class s9
{
C* p;
public:
s9( C* p_ ) : p(p_)
{
if(p)
p->s11();
}
s9(C& p_) 
{
p = &p_;
if(p)
p->s11();
}
s9()
{
p = NULL;
}
s9(const s9<C> &pn)
{
p = pn.p;
if(p)
pn.p->s11();
}
template<class D> 
s9( s9<D> &pn )
{
p = nullptr;
if ( SUPERSUBCLASS( C, D ) ) {
p = (C*)pn;
if(p)
p->s11();
}
}
~s9()
{
s15();
}
operator C*() { return p; }
C& operator*() { return *p; }
const C& operator*()const { return *p; }
C* operator->() { return p; }
const C* operator->()const { return p; }
s9& operator=( s9<C> &p_ ) { return operator=(( C* ) p_); }
s9& operator=( const s9<C> &p_ ) { return operator=( (s9<C>& ) p_ ); }
s9& operator=( C* p_ )
{
if(p){
p->s12();
}
p = p_;
if(p)
p->s11();
return *this;
}
template<class B>
operator B*()
{
return checked_cast<C, B>( p );
}
template<class D>
s9& operator=( const s9<D> &p_ )
{
if ( SUPERSUBCLASS( C, D ) )
return operator=( ( C* ) p_);
}
template<class ToType>
ToType s16() const
{
return static_cast<ToType>( p );
}
template<class ToType>
ToType dcast() const
{
return dynamic_cast<ToType>( p );
}
bool s13()const { return p == nullptr; }
bool s14()const { return p != nullptr; }
void s15()
{
if(p){
p->s12();
p = nullptr;
}
}
bool operator ==( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p == (INT_PTR)p ); }
bool operator !=( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p != (INT_PTR)p ); }
bool operator <( const s9<C>&ptr )const { return ( (INT_PTR)ptr.p < (INT_PTR)p ); }
bool operator ==( const C& s364 )const { return ( *p == s364 ); }
bool operator !=( const C& s364 )const { return ( *p != s364 ); }
bool operator <( const C& s364 )const { return ( *p < s364 ); }
};
#if defined (_MSC_VER)
#pragma warning( pop )
#endif
} // namespace s1
namespace s2 {
void s1239();
extern std::vector<std::wstring> s1095;
class s17
: public std::exception
{
static uint32_t s28;
protected:
std::list<std::wstring> s27;
uint32_t id;
s17() :id( 0 ){};
public:
enum class s18 : uint32_t
{
s19 = 0,
s20,
s21,
s22,
s23,
s24,
s25,
s957,
s26
};
s17( const std::wstring& s, uint32_t n = (uint32_t)s18::s20 )
: id( n )
{
s27.push_back( s );
}
s17( uint32_t n )
: id( n )
{
s27.push_back( s1095[n] );
}
s17( const s17& right )
: id( right.id )
{
s27.assign( right.s27.begin(), right.s27.end() );
}
static void s30()
{
s28 = (uint32_t)s18::s26 + 1;
}
static uint32_t s29()
{
return s28++;
}
virtual std::wstring Msg( size_t s202 = 0 ) const
{
std::wstring s718;
std::list<std::wstring>::const_reverse_iterator it = s27.crbegin();
std::wstring s1190( s202, L' ' );
while( it != s27.crend() ) {
std::wstring s;
std::wstringstream ss( *it );
++it;
int i = 0;
if( it == s27.crend() )
s718 += s1190;
while( std::getline( ss, s, L'\n' ) )
if( s.size() )
s718 += ( i++ ? L"" : s1190 ) + s + L"\n";
}
return s718;
}
const char* what() const noexcept
{
std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
return conv.to_bytes( s27.back() ).c_str();
}
uint32_t which() const { return id; }
s17* s31( const std::wstring& s )
{
s27.push_back( s );
return this;
}
s17* specify( const std::wstring& s )
{
s27.push_front( L"\n  : " + s );
return this;
}
};
} // namespace s2
namespace s3 {
bool s32( const std::wstring& _dir, const std::wstring& s548, std::wstring& s157 );
void s33( const std::wstring& _dir, const std::wstring& s548, std::vector<std::wstring>& s41,
std::vector<std::wstring>& s42 );
time_t s34( const std::wstring& f );
uint8_t s35( const std::wstring& f );
bool s761( const std::wstring& f );
bool s36( const std::wstring& s215 );
bool s37( const std::wstring& s215 );
std::wstring s38();
std::wstring s39();
std::wstring s40();
} // namespace s3
namespace s4 
{
extern std::wstring s90;
extern std::wstring s50;
extern std::string s51;
extern std::wstring s52;
extern std::wstring digits;
enum s18 { s24 };
std::wstring s53( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s54( const std::wstring& s, const std::wstring& c );
bool s55( const std::wstring& s, const std::wstring& ss );
void s56( const std::wstring& s, size_t s67, wchar_t left, wchar_t right, 
size_t& start, size_t& end, bool s972 = false );
void s57( const std::wstring& s, size_t s67, wchar_t c, size_t& start, 
size_t& end );
void s1100( const std::wstring& s, size_t& s67, const std::wstring& s1207 );
size_t count( const std::wstring& s79, const std::wstring& s1207, size_t start, size_t end,
bool s972 = false );
int s58( const std::wstring& s79, wchar_t s74, size_t& pos );
void s59( const std::wstring& s, const std::wstring& s74, std::vector<std::wstring>& s157, bool clr = true );
void s296( const std::vector<std::wstring>& v, const std::wstring& s74, std::wstring& s157 );
std::wstring s73( const std::wstring& s79, size_t& pos );
void s60( const std::wstring& s79, const std::wstring& s74, 
std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s61( const std::wstring& s79, const std::wstring& s74,
std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s62( const std::wstring& s79 );
void s63( std::wstring& s47 );
std::wstring s789( std::wstring path );
bool s64( const wchar_t *str, long *s364, wchar_t **end = NULL );
bool s65( const wchar_t *str, double *s364, wchar_t **end = NULL );
void s960( const std::wstring& s79, std::vector<std::wstring>& s157 );
std::wstring s1405( const std::wstring& s, const std::wstring& chars );
std::string s53( const std::string& l, const std::string& s, const std::string& r );
std::string s54( const std::string& s, const std::string& c );
void s56( const std::string& s, size_t s67, char left, char right, 
size_t& start, size_t& end);
int s58( const std::string& s79, char s74, size_t& pos );
void s59( const std::string& s, const std::string& s74, std::vector<std::string>& s157 );
void s61( const std::string& s79, std::vector<std::pair<std::string, std::string>>& v );
std::string s62( const std::string& s79 );
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
constexpr UINT rol(UINT s364, size_t n) {
static_assert(std::is_unsigned<UINT>::value,
"Rotate Left only makes sense for unsigned types");
return (s364 << n) | (s364 >> (sizeof(UINT)*8-n));
}
void s66( const std::wstring& s80 );
void s83( std::wstring& s79, std::vector<std::wstring>& s1222, std::map<size_t, size_t>& s1146 );
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
namespace consutils {
void s1235();
class s18
{
static uint32_t s92;
public:
static void s30();
static uint32_t s93() { return s92; }
};
void s94( const std::wstring& header,
const std::vector<std::wstring>& s95 = { } );
void s99();
void s134( int s75 = 0 );
void s101( bool b = true );
bool s102( const std::wstring& s96 );
int s103( const std::wstring& s96, const std::vector<std::wstring>& s97 );
std::wstring s104( const std::wstring& s96, bool s98 = false );
std::wstring s105( const std::wstring& s96, bool s98 = false );
std::wstring getStringValHist( const std::wstring& s96,
const std::vector<std::wstring>& s106 );
int s107( const std::wstring& s96 );
size_t s108( const std::wstring& s96 );
void s109( int& w, int& h );
void s110( const std::vector<std::wstring>& v, std::vector<std::wstring>& s157,
size_t w, size_t h );
int s111( const std::vector<std::wstring>& v );
#ifdef __LINUX__
char _getch();
#endif
#define s112 72
#define s113 80
#define s114 75
#define s115 77
#define s116 27
#define s117 13
#define s120 224
#define s118 8
#define s119 83
} // namespace consutils
namespace s6
{
enum s135{ s136, s137, s138, s143, 
s139, s140, s144, s141, s142 };
class s145;
class s147;
typedef s1::s9<s145> s146;
class s1034
: public s1::s10
{
std::wstring s199;
std::wstring s1232;
std::vector<std::wstring> s1233;
std::map<size_t, size_t> s1234;
size_t s1170;
public:
s1034( const std::wstring& file );
const std::wstring& Path() const { return s199;  }
void read( std::vector<s1::s9<s147>>& s157, 
const std::wstring& s195 = std::wstring(L"") );
void s175( const std::wstring& s79, size_t& pos, s1::s9<s147> s157, bool s155 = false );
bool s1105( std::wstring& s, size_t s70, size_t s716, size_t& line ) const;
size_t s1039() const { return s1170; }
};
typedef s1::s9<s1034> s1037;
class s147
: public s1::s10
{
std::multimap<std::wstring, s146> s148;
s1037 src;
public:
enum s149 { s150, s151, s152 };
enum s18 { s19, s153 };
const static s145 s154; // similar to string::npos
s147( const s1034* pf ):src( (s1034*)pf){}
void s158( const std::wstring& s79, bool s155 = false);
void s159( std::wostream* pd, bool s155=false ) const;
bool s160( const std::wstring& s156 ) const;
void s161( const std::wstring& s156, std::vector<s146>& s157 ) const;
const s146 s162( const std::wstring& s156 ) const;
void s163( const std::wstring& s78, s146 s364, s149 ap=s150 );
void s164( std::vector<std::pair<std::wstring, s146>>& s157 ) const;
bool operator==( const s147& r )  const;
void s165( std::wostream* pd, int s202 ) const;
};
bool operator==( const std::vector<s1::s9<s145>>& l,
const std::vector<s1::s9<s145>>& r );
class s145
: public s1::s10
{
s135 s203;
s147 obj;
std::wstring str;
std::vector<s1::s9<s145>> s166;
double s167;
bool b;
std::pair<size_t, size_t> s1194;
s1037 s1193;
public:
s145():s203(s136),obj(NULL){}
s145( const std::wstring& s ):s203(s138),obj(NULL),str(s){}
s145( const std::vector<s146>& a ): s203(s139),obj(NULL),s166(a){}
s145( const s1034* pf, const std::wstring& s79, size_t& pos, bool s155 = false );
s135 s168() const { return s203; }
bool s169() const { return s203 == s136; }
const s147& s170() const
{
if( s203 == s137 )
return obj;
throw std::runtime_error( "wrong variant" );
}
const std::vector<s146>& s171() const
{
if( s203 == s139 )
return s166;
throw std::runtime_error( "wrong variant" );
}
double s172() const
{
if( s203 == s140 )
return s167;
throw std::runtime_error( "wrong variant" );
}
int s58() const
{
if( s203 == s144 )
return (int)s167;
throw std::runtime_error( "wrong variant" );
}
bool s768() const
{
if( s203 == s141 )
return b;
throw std::runtime_error( "wrong variant" );
}
const std::wstring& s173() const
{
if( s203 == s138 || s203 == s143 )
return str;
throw std::runtime_error( "wrong variant" );
}
const std::wstring& s940() const
{
if( s203 == s143 )
return str;
throw std::runtime_error( "wrong variant" );
}
std::wstring s930() const
{
if( s203 == s143 )
return str.substr( 1, str.size() - 2 );
throw std::runtime_error( "wrong variant" );
}
bool s1110( std::wstring& f, std::wstring& s, size_t& line  ) const;
const s1034* s1107() const { return s1193.s16<s1034*>(); }
bool operator==( const s145& r ) const
{
return s203 == r.s203 && obj == r.obj && str == r.str && s166 == r.s166 && b == r.b && s167 == r.s167;
}
bool is( const s145& r ) const
{
return this == &r;
}
void s165( std::wostream* pd, int s202 ) const;
void s159( std::wostream* pd, bool s155=false ) const;
};
void s176( const std::wstring& s199, 
const std::vector<s1::s9<s147>>& s200 );
void s183( const s1034* pf, const std::wstring& s79, size_t& pos, std::vector<s1::s9<s145>>& s157,
bool s155 = false, const std::wstring& s74 = L",");
void s183( const s1034* pf, const std::wstring& s79, std::vector<s1::s9<s145>>& s157,
bool s155 = false, const std::wstring& s74 = L"," );
} // namespace s6
#define DEFCONST extern const std::wstring
#define DEFCONSTI extern const int
#define s1016 extern const uint32_t
namespace transd {
namespace s7 {
DEFCONST s436;
DEFCONST s437;
DEFCONST s438;
DEFCONST s439;
DEFCONST s440;
DEFCONST s441;
DEFCONST s442;
DEFCONST s443;
DEFCONST s444;
DEFCONST s445;
DEFCONST s1080;
DEFCONST s446;
DEFCONST s447;
DEFCONST s448;
DEFCONST s898;
DEFCONST s449;
DEFCONST s450;
DEFCONST s451;
DEFCONST s812;
DEFCONST s793;
DEFCONST s847;
DEFCONST s452;
DEFCONST s453;
DEFCONST s897;
DEFCONST s1029;
DEFCONST s1264;
DEFCONSTI s941;
DEFCONSTI s454;
DEFCONSTI s455;
DEFCONSTI s456;
DEFCONSTI s457;
DEFCONSTI s458;
DEFCONSTI s942;
DEFCONSTI s943;
DEFCONSTI s1343;
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
DEFCONST s473;
DEFCONST s475;
DEFCONST s474;
DEFCONST s476;
DEFCONST s477;
DEFCONST s478;
DEFCONST s816;
DEFCONST s855;
DEFCONST s890;
DEFCONST s1242;
DEFCONST s479;
DEFCONST s480;
DEFCONST s481;
DEFCONST s482;
DEFCONST s483;
DEFCONST s484;
DEFCONST s486;
DEFCONST s780;
DEFCONST s488;
DEFCONST s1024;
DEFCONST s1003;
DEFCONST s1002;
DEFCONST s1004;
#define s435 3
#define s1236 L','
DEFCONST s434;
DEFCONST s1224;
s1016 CLVecVal_ctor1;
s1016 s1012;
s1016 s1011;
s1016 s1247;
s1016 s1006;
s1016 s1225;
s1016 s1007;
s1016 s1226;
s1016 s1227;
s1016 s1228;
s1016 s1008;
s1016 s1009;
s1016 s1010;
s1016 s1244;
s1016 s1245;
s1016 CLTDMaxElement_ctor1;
s1016 CLFilterVal_ctor1;
s1016 CLIndexVal_ctor1;
s1016 s1246;
extern std::set<std::wstring> s1241;
} // namespace s7
enum s230 { s231, s232, s233, s234 };
extern std::wstring s235[];
extern const std::wstring s236, s237, s238,				s879,
s239,  s240,     s241,    s242,      s243,
s244,  s245, s246, s247,s250,
s248, s249,			s264,	s251,			s263,
s252, s253,     s254,   s255,			s796,
s256,   s257, s258, s259,			s260,
s261, s262,		s265,	s988,			s268,
s266,	 s875,			s805, s925, 	s819,
s926,  /**/s267, s1304;
class s269;
class s270;
class s277;
class s278;
class s279;
typedef s277* ( *s280 )( const std::wstring& s285, const std::vector<s278*>& s281 );
typedef s1::s9<s270> s1036;
extern const std::wstring s272;
class s270
: public s1::s10
{
public:
typedef std::multimap<std::wstring, s1036> s282;
typedef std::map<std::wstring, std::wstring> s271;
private:
static std::map<std::wstring, s280> s283;
std::wstring s284;
std::wstring s285;
s230 s286;
std::wstring s287;
s282 s288;
std::wstring src;
s6::s146 s1162;
s271 s273;
void s289( const std::wstring& s79 );
void s290( const s6::s147& s137 );
void s291( const std::wstring& s79 );
void s292( const std::wstring& s79 );
void s293( const std::wstring& type, const s6::s145& obj );
void s1102( const std::wstring& s );
static std::wstring s294( const std::wstring& s79, size_t &pos );
public:
enum s18 { s19, s153 };
s270(){ }
s270( s230 at, const std::wstring& qpre, const std::wstring& s78 )
: s284( qpre ), s285( s78 ), s286( at ) { }
s270( const std::wstring& s78, const std::wstring& s364 )
: s285( s78 ), s286( s231 ), s287( s364 ) { }
s270( const std::wstring& type, const s6::s145* s1162 );
s270( const std::wstring& s78, const s6::s145& s303 );
s270( const s6::s147& s137 );
~s270();
s230 s304() const { return s286; }
std::wstring s305() const;
const std::wstring& s306() const { return s285; }
const std::wstring& Src() const { return src; }
const s6::s145* Nqj() const { return s1162.s16<s6::s145*>(); }
const std::wstring& s275( const std::wstring& s310 ) const;
void s276( const std::wstring& s310, const std::wstring& s274 );
void reset();
static void s295( const std::wstring& s79, size_t& pos, std::vector<std::wstring>& s157 );
void s296( s6::s147& s137 );
void s293( s270* node );
void s297( s269* s307, size_t s308 = 0 );
const std::wstring& s298() const { return s287; }
const s270* s299( const std::wstring& s285 ) const;
s282& s300() { return s288; }
const s282& s300() const { return s288; }
void s301( const std::wstring& s ) { s285 = s; }
static std::wstring s302( const s6::s147& obj,
const std::wstring& dfault = std::wstring( L"" ) );
static std::wstring s309( const s6::s147& obj,
const std::wstring& s310,
const std::wstring& dfault = std::wstring( L"" ) );
void s311( std::wostream* pd, int s202 = 0 ) const;
};
} // namespace transd
namespace s8{
enum s1033{ s1152, s1151, s1153, s1154, s1150 };
class Msg
{
std::wstring func;
std::wstring file;
uint32_t line;
s1033 type;
std::wstring s80;
public:	
Msg( const std::wstring& s, s1033 t = s1150 )
: type( t ), s80( s ) {}
Msg( const std::wstring& s, const std::wstring& f, const std::wstring& fi,
int n, s1033 t = s1150 )
: func( f ), file( fi ), line( n ), type( t ), s80( s ) {}
s1033 s367() const { return type; }
const std::wstring& Text() const { return s80; }
};
}
namespace transd {
class s1223
{
std::vector<s8::Msg> s27;
size_t s1096;
public:
s1223() : s1096(0){}
void s1066( const std::wstring& s80 );
void s1066( const std::wstring& s80, const std::string& func, 
const std::string& file, uint32_t line );
void s1068( const std::wstring& s80, const std::string& func, 
const std::string& file, uint32_t line );
size_t s1022() const { return s1096; }
};
extern s1223 s1116;
extern std::vector<std::wstring> s1197;
extern std::vector<std::wstring> s1093;
class TDException
: public s2::s17
{
public:
enum class Stage : uint32_t
{
s1139 = 0,
s1132,
s1137,
s1136,
s1131,
s1133,
s1134,
s1135,
s1138
};
private:
Stage stage;
uint32_t category;
std::wstring s1204;
const s270* s737;
public:
TDException( uint32_t cat, uint32_t id, const s270* s737 );
TDException( Stage stage, uint32_t cat, uint32_t id, const s270* s737, const s17& e );
TDException( uint32_t cat, uint32_t id, const s270* s737, const std::wstring& s80 );
TDException( const TDException& e );
virtual std::wstring Msg( size_t s202 = 0 ) const override;
uint32_t Category() const { return category;  }
void s1188( Stage st ) { stage = st; }
TDException* s1099( const std::wstring& s = std::wstring( L"" ) );
};
class s1015
: public s2::s17
{
public:
enum class s18 : uint32_t
{
s1081 = ((uint32_t)s17::s18::s26) + 1,
s1178,
s1159,
s1070,
s1082,
s1120,
s1123,
s26
};
s1015( const std::wstring& s )
: s17( s, (uint32_t)s18::s1081){}
s1015( s17& e, const s270& s737, s18 code );
};
class s1023
: public s2::s17
{
public:
enum class s18 : uint32_t
{
s1158 = ( (uint32_t)s17::s18::s26 ) + 1,
s1098,
s26
};
s1023( s18 code );
s1023( const std::wstring& s, s18 code )
: s17( s, (uint32_t)code ) {}
};
#define s1020		1
#define s1019		2
#define s1021						3
#define s1017					4
#define s1018				5
#define s1255		6
#define s1254		7
#define s1043(x) throw s1044( L"unknown syntax: " + x );
#define s1042(x) throw s1044( L"syntax error: " + x );
namespace lang {
bool s686( const std::wstring& s, bool s751 = true );
} // namespace tdlang
extern const std::wstring s489;
enum s490 { s491, s492, s493, s494, s1396, s1397, 
s496, s497, s498, s499, s500, s1174 };
class s269;
class s501;
class s502;
class s279;
class s616;
class s278;
class s346;
class s585;
typedef s278 s503;
typedef s278 TDType;
typedef s1::s9<s503> s504;
typedef s1::s9<s502> s505;
typedef s1::s9<s279> s506;
typedef s1::s9<s616> s507;
class s869;
typedef std::map<std::wstring, std::vector<std::wstring>> s1014;
extern s1014 s1092;
typedef uint32_t s1172;
typedef uint32_t traitnum_t;
class s278
: public s1::s10
{
friend class s510;
s1036 s1072;
protected:
s490 s512;
s1172 s513;
s269* s307;
int wh;
public:
s278( const s270* ast_=NULL ) : s1072( (s270*)ast_ ), s512( s491 ), s513( 0 ), 
wh( s7::s943 )  { }
s278( s490 pt_, const s270* ast_=NULL ) : s1072( (s270*)ast_ ), s512( pt_ ), s513( 0 ), 
wh( s7::s943 ) { }
s278( s269* pass_, s490 pt_, const s270* ast_=NULL ) : s1072( (s270*)ast_ ), s512( pt_ ),
s513( 0 ), s307( pass_ ), wh( s7::s943 )  { }
s278( const s278& r ) : s1072( r.s1072 ), s512( r.s512 ), s513( r.s513 ),
s307( r.s307 ), wh( r.wh ) {}
virtual ~s278();
s490 s514() const { return s512; }
const s270* s628() const { return s1072.s16<s270*>(); }
virtual s502* s516();
virtual s505 s517( s502** s281 = NULL, size_t s518 = 0 );
virtual s1172 s367() const { return s513; }
const s869& s1340() const;
virtual const std::wstring& s369() const;
virtual void s366( s1172 type );
int s645() const { return wh; }
void setWh( int i ) { wh = i; }
void s1414() { wh = 0; }
void s1412(bool b = true) { if(b) wh |= (1 << (s7::s1343-1)); 
else wh &= ~(1 << (s7::s1343-1));}
bool s1349() const { return wh >= 0; }
bool s1348() const { return wh & (1 << (s7::s1343-1)); }
virtual bool s522( const s502* s523 ) const;
virtual const s1014& s1104() const { return s1092;  }
virtual void s520( s279* s962 );
virtual const s502* s524() const;
virtual s278* s350() const;
static s278* s525( const s270& s737, s269* s307, s279* obj,
const std::wstring& s347 );
static s278* s1122( s269* s307, s278* par, s279* obj, s616* s220,
const std::wstring& s347 );
static s504 s1121( const std::wstring& s79, const s270* ast_, s269* s307, s279* s613 );
virtual operator bool() const;
virtual operator int() const;
virtual operator double() const;
virtual std::wstring to_wstring() const;
/*	static void s295( const std::wstring& s79, size_t& pos,
std::vector<std::wstring>& s157 );
*/
virtual void s311( std::wostream* pd, int s202 = 0 ) const = 0;
};
typedef std::multimap<std::wstring, s503*> s526;
s503* s1238( s526& m, const std::wstring& s156 );
void s702( const std::wstring& s, std::wstring& s1230, std::wstring& s626 );
class s502;
class s387;
class s502
: public s278
{
friend class s510;
protected:
std::wstring s388; // DEBUG
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) = 0;
public:
s502( s269* s307, s490 pc, const s270* ast_ ) : s278( s307, pc, ast_ ) { }
s502( const s502& r ) : s278( r ) { }
virtual ~s502();
virtual void s365() = 0;
virtual s1172 s402( const std::wstring& s358 ) const = 0;
virtual s502* s371( s279* s613, const std::vector<s278*>& l = std::vector<s278*>() ) const = 0;
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const;
virtual void s372( s278* p ) const = 0;
virtual const s502* s524() const override = 0;
void s527( const std::wstring& s ) { s388 = s; }
virtual size_t s331() const = 0;
virtual bool operator==( const s502* p ) const = 0;
virtual bool operator<( const s502* p ) const = 0;
virtual s505 s517( s502** s281, size_t s518 ) override { return this; }
virtual s502* s516() override;
virtual bool s580( const std::wstring& s285, s387* s157,
const std::wstring& s347 ) const	{	return false;	};
virtual s278* s623( size_t off )	{	return NULL; }
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const;
bool s1342( s1172 s647, traitnum_t tra );
};
enum s560 { s531, s532, s533 };
enum s534 { s535, s536, s537 };
typedef s1::s9<s869> s884;
typedef const s869* s1013;
class s869
: public s1::s10
{
public:
typedef s1172 s778;
typedef s778 s980;
typedef std::vector<s778> Cont;
private:
Cont vt;
size_t s1212;
public:
s869() {}
s869( s778 t1, s778 t2 = (s778)-1, s778 t3 = (s778)-1 );
s869( const s869& right );
s869( const Cont& v );
void s366( s778 t );
void s366( s1013 pt );
void s836( s778 t );
void s836( s1013 pt );
s980 s367( size_t n = 0 ) const;
const Cont& s877() const { return vt; }
void s877( std::vector<s278*>& s157 ) const;
bool operator==( const s869& p ) const;
size_t s331() const { return s1212; }
};
class s501;
class s269;
struct s1058
{
std::size_t operator()( const s869& k ) const
{
return k.s331();
}
};
struct s1059
{
std::size_t operator()( const s869& l, const s869& r ) const
{
return l.operator==( r );
}
};
class s510
{
typedef std::map<std::wstring, s1172> s1052;
typedef std::unordered_map<s869, s1172, s1058, s1059> s1055;
typedef std::map<std::wstring, std::set<std::wstring>> s1001;
typedef std::map<s869::s980, s1001> s1014;
typedef std::map<std::wstring, traitnum_t> s1294;
typedef std::unordered_map<traitnum_t, std::wstring> s1399;
std::vector<s505> s1231;
std::vector<std::wstring> s1214;
std::vector<s869> s1219;
s1052 s1215;
s1055 s1220;
s1014 s1005;
s1294 s979;
s1399 s1411;
traitnum_t s1351;
std::vector<traitnum_t>s1429;
s269* s307;
s1172 s1179( const s869::Cont& v, const std::wstring& s362 );
void s1313( const std::wstring& alias, const std::wstring& s362 );
public:
s510( s269* pass_ );
void reset();
void s297();
void s540( const s501& st );
void s224( s502* p, const std::wstring& s362 );
s1172 s1155( const s869::Cont& v );
traitnum_t s1404( const std::wstring& trait );
void s1302( s869::s980 type, const std::wstring& trait );
void s1064( s869::s980 type, const std::wstring& cat, const std::wstring& s1073 );
bool s1117( s869::s980 type, const std::wstring& cat, const std::wstring& s1073 );
void s1106( s869::s980 type, const std::wstring& cat, std::vector<std::wstring>& s157 );
std::wstring s1106( s869::s980 type, const std::wstring& cat );
traitnum_t s1295( s1172 s647 ) const { return s1429[s647]; }
bool s1124( s869::s980 type );
bool s1350( s869::s980 type );
s502* s542( const s6::s145& s364, s279* s613, const std::wstring& s543 );
s502* s542( const s270& s737, s279* s613, const std::wstring& s543 );
s502* s542( s1172 type, s279* s613, const std::wstring& s543 );
const s502* get( const std::wstring& s78, bool s544 = true ) const;
s1172 s1111( const std::wstring& s362 ) const;
s1172 s1112( const s869& vt ) const;
const s869& s1114( s1172 t ) const;
const s502* s1108( s869::s980 t ) const;
const std::wstring& s856( s1172 n ) const;
bool s160( const std::wstring& s78 ) const;
void s841();
bool s1401();
double s1403();
int s1409();
void s311( std::wostream* pd, int s202 = 0 ) const;
static void s1109( const s869::Cont& v, size_t& idx, s869::Cont& s157 );
size_t s1165( const std::wstring& s, size_t& pos, s869::Cont& s157 );
std::wstring s1113( const s869::Cont& tp );
std::wstring s1430( const s270& s737 );
};
class s545
: public s1::s10
{
std::vector<std::wstring> s546;
s534 pv;
public:
s545() : pv( s535 ) { }
s545( s534 pv, const std::vector<std::wstring>& s547 );
s545( const std::wstring& ag, const std::wstring& s79 );
s534 s584( const std::wstring& s519 ) const;
static std::vector<std::wstring> s549;
};
class s550
: public s1::s10
{
typedef std::map<std::wstring, s545*> s551;
s551 s552;
public:
s550( ) { }
void s553( s534 pv, s270* );
void s554( const std::wstring& s, s545& pl );
void s555( const std::wstring& s, const std::wstring& s548 );
s534 s556( const std::wstring& mem, const std::wstring& s519 );
void s557( const std::wstring& s347,
std::vector<std::wstring>& s157 );
};
class s501
{
public:
enum s149 { s150, s558, s151, s152 };
private:
typedef std::map<std::wstring, s505> s559;
s559 s577;
s560 s561;
s550* s563;
bool s562( const std::wstring& s78, s149 ap = s150 );
public:
s501( ): s561( s532 ), s563( NULL ) {}
s501( s560 am ) : s561( am ), s563( NULL ) {}
s501( const s501& s564 );
void s520( s279* s519, bool s539 = true );
void reset();
void s565( const std::wstring& s78, s502* sym, s149 ap = s150 );
void s565( const std::wstring& s78, s6::s146 s364, s149 ap = s150 );
void s566( const std::wstring& s78 );
void s567( const s6::s147& obj, s149 ap = s150 );
void s296( const s501& t, s149 ap = s150 );
bool s160( const std::wstring& s78 ) const;
s502* get( const std::wstring& s78, bool s544 = true ) const;
void s568( std::vector<std::wstring>& s157 ) const;
void s569( std::vector<std::wstring>& s157 ) const;
void s570( std::vector<std::wstring>& s157 ) const;
void s571( const s501& t, std::vector<std::wstring>& s157 ) const;
void copy( s501& t, s279* s613, s616* s612, s149 ap = s150 ) const;
void s572( s501& t ) const;
void s573( s534 pv, s270* s81 );
void s557( const std::wstring& s347,
std::vector<std::wstring>& s157 );
bool s574( const std::wstring& s285, const std::wstring& s347 ) const;
void s311( std::wostream* pd, int s202 = 0 ) const;
};
class s575
{
typedef std::pair<s502*, std::wstring> s576;
typedef std::multimap<std::wstring, s576> s559;
s559 s577;
std::vector<std::wstring> s583;
public:
s575();
void s578( const std::wstring& s );
void s520( s269* s307, const std::wstring& s582 );
void s579( const std::wstring& s78, s269* s307, const std::wstring& s582 );
bool s580( const std::wstring& sym, s387* ref );
void copy( s575& t ) const;
};
extern s1::s9<s550> s581;
class s269;
class s351;
typedef void ( *s643 )( s502** s281, size_t n );
class s1240
{
s351* s613;
std::vector<s1172> s1433;
std::vector<s504> s1000;
public:
s1240( const std::vector<s504>& v, s351* s617 /*= NULL*/ );
s1240( const std::vector<s1172>& v, s351* s617 = NULL )
: s613( s617 ), s1433( v ) {}
bool operator==( const s1240& s548 ) const;
bool operator<( const s1240& s548 ) const;
const s351* Subj() const { return s613; }
const std::vector<s504>& s627() const { return s1000; }
};
struct s1267
{
s1172 s353;
s643 s354;
bool s1309;
s1267()
: s353( 0 ), s354( NULL ), s1309( true ) {}
s1267( s1172 pt, s643 fp, bool s1310 = true )
: s353( pt ), s354( fp ), s1309( s1310 ) {}
};
class s351
: public s502
{
public:
class s352
{
std::wstring s285;
s1172 s353;
s643 s354;
std::vector<s1240> s1303;
size_t s1147, s1144;
std::vector<std::wstring> s1355;
bool s1322;
bool s1309;
public:
enum class s1256 : uint32_t { s1323 = ((uint32_t)s2::s17::s18::s26) + 1 };
s352( const std::wstring& s709, s643 fp, s1172 s355,
const std::vector<s1240>& v=std::vector<s1240>(), 
size_t s1148 = 0, size_t s1145=(size_t)-1, bool s1310 = true,
const std::vector<std::wstring>& s1354 = std::vector<std::wstring>() )
: s285( s709 ), s353( s355 ), s354( fp ), s1303(v), 
s1147(s1148), s1144(s1145), s1355( s1354 ), s1322(false), s1309( s1310 ) {}
s352()
: s354( NULL ), s1322(false), s1309( true )	{}
s643 s1260() const { return s354; }
size_t s1032() const { return s1147;  }
size_t s1031() const { return s1144;  }
const std::vector<std::wstring>& Markers() const { return s1355; }
s1172 s515() const { return s353; }
void s1415( s1172 t) { s353 = t; }
void s1413( bool b ) { s1322 = b; }
bool s1330( ) const { return s1322; }
bool s1348() const { return s1309; }
bool s1307( /*s351* thi,*/ const s1240& s724 ) const;
};
protected:
typedef std::multimap<std::wstring, s352*> s356;
virtual const s356& s357() const = 0;
static size_t s804;
public:
s351( s269* s307, const s270* ast_ ) : s502( s307, s492, ast_ ) {}
s351( const s351& r ) : s502( r ) {}
virtual ~s351() {}
virtual s1172 s402( const std::wstring& s358 ) const override;
static void s835( s269* s307, bool soft = false );
static size_t s860() { return s804;  }
const std::vector<std::wstring>& s1335( const std::wstring& s358 ) const;
virtual s1267 s1341( const std::wstring& s358 ) const;
virtual s1267 s1336( const std::wstring& s358, s1240& ap ) const;
virtual s1267 s1331( const std::wstring& s358, s1240& ap ) const;
virtual const s502* s524() const override;
virtual void* addr() = 0;
virtual s505 s517( s502** s281, size_t s518 ) override;
static s502* s360( s269* s307, const std::wstring& s364, const std::wstring& s347 );
static traitnum_t s1293() { return s1426; }
static traitnum_t s1291() { return s1424; }
static traitnum_t s1290() { return s1423; }
static traitnum_t s1292() { return s1425; }
private:
static traitnum_t s1426, s1424, s1423, s1425;
};
class s361;
class s361
: public s351
{
static s356 s363;
int s364;
static void s403( s502** s281, size_t n );
static void s404( s502** s281, size_t n );
static void s405( s502** s281, size_t n );
static void s406( s502** s281, size_t n );
static void s407( s502** s281, size_t n );
static void s408( s502** s281, size_t n );
static void s409( s502** s281, size_t n );
static void s410( s502** s281, size_t n );
static void s411( s502** s281, size_t n );
static void s412( s502** s281, size_t n );
static void s413( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
static void s415( s502** s281, size_t n );
static void s416( s502** s281, size_t n );
static void s417( s502** s281, size_t n );
static void s418( s502** s281, size_t n );
static void s419( s502** s281, size_t n );
static void s420( s502** s281, size_t n );
static void s421( s502** s281, size_t n );
static void s422( s502** s281, size_t n );
static void s423( s502** s281, size_t n );
static void s424( s502** s281, size_t n );
static void s425( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s361( s269* s307 ) : s351( s307, NULL ) {}
s361( const s361& );
s361( s269* s307, const std::vector<s278*>& l );
s361( s269* s307, int i );
s361( s269* s307, const std::wstring& s, size_t& pos );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void s520( s279* s612 ) override;	
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
int* s373() { return &s364; }
virtual void* addr() override { return (void*)&s364; }
virtual operator bool() const { return s364 != 0; }
virtual operator int() const { return s364; }
virtual operator double() const { return (double)s364; }
virtual std::wstring to_wstring() const { return std::to_wstring( s364 ); }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s374
: public s351
{
static s356 s363;
double s364;
static void s403( s502** s281, size_t n );
static void s404( s502** s281, size_t n );
static void s405( s502** s281, size_t n );
static void s406( s502** s281, size_t n );
static void s407( s502** s281, size_t n );
static void s408( s502** s281, size_t n );
static void s409( s502** s281, size_t n );
static void s410( s502** s281, size_t n );
static void s411( s502** s281, size_t n );
static void s412( s502** s281, size_t n );
static void s413( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
static void s415( s502** s281, size_t n );
static void s416( s502** s281, size_t n );
static void s417( s502** s281, size_t n );
static void s418( s502** s281, size_t n );
static void s419( s502** s281, size_t n );
static void s426( s502** s281, size_t n );
static void s427( s502** s281, size_t n );
static void s420( s502** s281, size_t n );
static void s422( s502** s281, size_t n );
static void s423( s502** s281, size_t n );
static void s428( s502** s281, size_t n );
static void s425( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s374( s269* s307 ) : s351( s307, NULL ) {}
s374( const s374& r );
s374( s269* s307, const std::vector<s278*>& l );
s374( s269* s307, double d );
s374( s269* s307, const std::wstring& s, size_t& pos );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void s520( s279* s612 ) override;	
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
double* s373() { return &s364; }
virtual void* addr() override { return (void*)&s364; }
virtual operator bool() const { return s364 != 0.0; }
virtual operator int() const { return (int)s364; }
virtual operator double() const { return s364; }
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s376
: public s351
{
static s356 s363;
bool s364;
static void s403( s502** s281, size_t n );
static void s429( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s376( s269* s307 ) : s351( s307, NULL ) {}
s376( s269* s307, bool b );
s376( s269* s307, const std::wstring& s, size_t& pos );
s376( const s376& right );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
bool* s373() { return &s364; }
virtual void* addr() override { return (void*)&s364; }
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual void s520( s279* s612 ) override;	
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
virtual operator bool() const { return s364; }
virtual operator int() const override { return (int)s364; }
virtual operator double() const override { return (double)s364; }
virtual std::wstring to_wstring() const override { return ( s364 ? L"true" : L"false" ); }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s376> s385;
extern s1::s9<s376> s386;
class s377
: public s351
{
static s356 s363;
static void s844( s502** s281, size_t n );
static void s529( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
std::wstring s80;
public:
s377( const s377& right );
s377( s269* s307, const std::wstring& s = std::wstring( L"" ) );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
const std::wstring& Msg() const { return s80; }
void s379( const std::wstring& s ) { s80 = s; }
virtual void* addr() override { return (void*)0; }
virtual void s520( s279* s612 ) override;	
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
virtual std::wstring to_wstring() const override { return s80; }
virtual operator bool() const { return false; }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s380
: public s351
{
static s356 s363;
virtual void s365() override {}
virtual const s356& s357() const override { return s363; }
public:
s380( s269* s307 );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void* addr() override { return (void*)0; }
virtual s278* s350() const override;
virtual void s372( s278* p ) const override { }
virtual void s520( s279* s612 ) override;	
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
virtual std::wstring to_wstring() const {	return L"";	}
virtual operator bool() const { return false; }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s380> s381;
class s400
: public s351
{
traitnum_t s1427;
static s356 s363;
virtual void s365() override {}
virtual const s356& s357() const override { return s363; }
public:
s400( s269* s307, traitnum_t tn = 0, s490 pc = s491 );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s278* s350() const override;
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)0; }
virtual void s372( s278* p ) const override { }
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
virtual void s520( s279* s612 ) override;	
virtual operator bool() const { return false; }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s361> s825;
extern s1::s9<s374> s859;
extern s1::s9<s376> s803;
extern s1::s9<s377> s876;
extern s1::s9<s380> s781;
extern s1::s9<s400> s829;
extern s1::s9<s400> s947;
extern s1::s9<s400> s382;
extern s1::s9<s400> s383;
extern s1::s9<s400> s384;
extern s1::s9<s400> s951;
#define s1287 s781->s367()
#define s1276 s803->s367()
#define s1285 s825->s367()
#define s1284 s859->s367()
#define s1289 s843->s367()
#define s1279 (s1172)-1
#define s1282 (s1172)-2
#define s1283 (s1172)-3
#define s1278 (s1172)-4
#define s1280 (s1172)-5
#define s1277 (s1172)-6
#define s1281 (s1172)-7
#define s1275 (s1172)-8
#define s1286 (s1172)-9
#define s1288 (s1172)-10
#define s1272 (size_t)-1
typedef s361 TDInt;
typedef s374 TDDouble;
class s387
: public s278
{
std::wstring s388;
s505 s389;
const s502* s390;
std::vector<size_t> s391;
size_t s392;
public:
s387( const std::wstring& s, s269* s307, s490 cat = s491 );
s387( const s387& right );
virtual s502* s516() override;
virtual const s502* s524() const override { return s390; }
const s505 s397() { return s389; }
const std::wstring& s644() const { return s388; }
virtual s505 s517( s502** s281, size_t s518 ) override;
s502* s393() const;
s502* s394();
void s395( size_t off, const s502* proto );
size_t s396() const { return s392; }
uint32_t Id() const { return (uint32_t)s392; }
virtual s278* s350() const override;
virtual void s520( s279* s612 ) override;
void s398( s502* p ) { s389 = p; }
void s399( s502* p ) { s390 = p; }
void s1079( const std::vector<std::wstring> &v );
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
typedef s1::s9<s387> s508;
class s616;
class s279;
typedef std::vector<std::pair<std::wstring, std::wstring>> s650;
typedef std::map<std::wstring, s279*> s651;
typedef std::map<std::wstring, s270*> s652;
class s279
: public s502
{
protected:
const s279* s653;
const s279* s654;
s279* ns;
const std::wstring& s362;
const std::wstring s285;
std::wstring s655;
s501 s656;
s575* s657;
std::vector<s504> s658;
std::vector<std::wstring> s659;
virtual void s365() override { }
public:
s279( const s279& s661, const s270* ast_=NULL );
s279( s269* s307, s1172 s355, s490 pc/* = s491*/, const s270* ast_ = NULL );
s279( const std::wstring& s285, s269* s307, s490 pc, const s270* ast_ = NULL );
s279( const std::wstring& s362, const std::wstring& s285, s269* s307, s501& s662,
const s501& s656, const s270* ast_ = NULL );
s279( s270& s737, s269* s307, s490 pc, s279* ns, s560 am, 
s651& cl, s650& cnl, s652& al );
const std::wstring& s369() const { return s362; }
const std::wstring& s306() const { return s285; }
std::wstring s305() const;
virtual std::wstring s900() const { return ns->s305(); }
static s278* s663( const s6::s147& obj, const std::wstring& s285, s269* s307 );
static s278* s663( std::multimap<std::wstring, s503*>& v, s503* s612 );
s502* s664( const s270& s737, const std::wstring& s347 );
s502* s664( const s6::s145& s364 );
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s1172 s402( const std::wstring& s358 ) const override;
virtual bool s522( const s502* s523 ) const override;
virtual const s1014& s1104() const override { return s1092; }
bool s770( const std::wstring& f ) const;
void s922( const std::wstring& s78, s502* s364 );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual const s502* s524() const override { return s653; }
const s279* s665() const { return s654; }
const std::wstring& s666() const { return s655; }
s502* s359( const std::wstring& s285, const std::wstring& s347,
bool s544 = true ) const;
void s675( s270& s737 );
void s579( const std::wstring& s78, const std::wstring& s582 );
void s667( s270& s737 );
void s1065( s270& s737 );
void s668( const std::wstring& s347,	std::vector<std::wstring>& s157 );
virtual bool s580( const std::wstring& s285, s387* s157,
const std::wstring& s347 ) const override;
size_t s669( const std::wstring& s285 ) const;
virtual s278* s623( size_t off ) override;
s502* s671( const std::wstring& s285, const std::wstring& s347,
bool s544=true ) const;
bool s672( const std::wstring& sym, const std::wstring& s519 ) const;
bool s556( const std::wstring& sym );
virtual void s520( s279* s962 ) override;
void s674( const s501& s281 ); 
void s158( s270& s737 );
virtual s278* s350() const  override;
virtual void s372( s278* p ) const override;
void s673( s279* s676 ) const;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual std::wstring to_wstring() const override;
virtual void s311( std::wostream* pd, int s202 = 0 ) const;
};
class s585
: public s278
{
const std::wstring s626;
std::vector<s278*> s281;
s1036 past;
public:
s585( s269* pass_, const s270* ast_ )
: s278( pass_, s496 ), past( (s270*)ast_ )
{
}
s585( s269* pass_, const std::wstring& methName, const std::vector<s278*>& l, const s270* s737 );
s585( const s585& s564 );
const std::wstring& s306() const { return s626; }
std::vector<s278*>& s627() { return s281; }
const s270* s628() { return past; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override { }
};
typedef s1::s9<s585> s509;
class s616;
class s269;
typedef s616 TD;
class s351;
typedef s616 Transd;
typedef std::vector<s504> s601;
typedef std::vector<s505> s602;
typedef std::vector<s504> s603;
class s616
: public s279
{
public:
enum s587 { s588, s589, s590, s591, s592, s593 };
protected:
std::wstring s285;
std::wstring s703;
enum s594 { s595, s596, s597, s598 };
s587 s599;
s594 s600;
s502** s604;
s503** s605;
size_t s518, nlocs;
s602 s607;
s601 s281;
std::vector<s505> s1077;
std::vector<s502*> s608;
s603 s609;
std::vector<std::vector<s503*>> s610;
s505 s611;
s506 s613;
s507 s612;
const s270* past;
s278* s918( s278* par );
void s614(const std::wstring& s347);
void s615(const std::wstring& s347);
public:
s616( s269* s307, s279* s617, s616* s618, s587 ct, 
const std::wstring& s709, const s270* s737 )
: s279( s307, 0, s494, s737 ), s285( s709 ), s599( ct ),  
s611( NULL ),	s613( s617 ), s612( s618 ), past( s737 ) { }
s616( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s616( const s616& right, s279* s613, s616* s612, const std::vector<s278*>& s281,
const s270* s737 );
virtual ~s616();
s587 s939() const { return s599; }
void s619( s594 vt ) { s600 = vt; }
s594 s620() const { return s600; }
virtual const std::wstring& s306() const { return s285; }
virtual std::wstring s900() const override;
const s270* s628() const { return past; }
virtual s502* s516() override { return s611; }
virtual void s520( const std::wstring& s347, bool proc );
void s621( const std::vector<s504>& l );
typedef std::vector<std::pair<std::wstring, s505>> s901;
void s870( s901& s157 ) const;
void s622( const std::wstring& s347 );
virtual bool s580( const std::wstring& s285, s387* ref,
const std::wstring& s347 ) const override;
virtual s278* s623( size_t off ) override;
virtual s505 s517( s502** s281 = NULL, size_t s518 = 0 ) override;
virtual s278* s350() const override;
static s616* s624( const s270& s737, s269* s307, s279* obj,
const std::wstring& s285, const std::wstring& s582 );
static s585* s1237( const s270& s737, s269* s307, s279* obj, 
const std::wstring& s582 );
static s616* s625( s585* cs, s269* s307, s279* s613, s616* s220,
const std::wstring& s582 );
static void s1393( std::vector<s278*>& s281, const std::vector<std::wstring>& s1354 );
static void s1393( std::vector<s504>& s281, const std::vector<std::wstring>& s1354 );
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s911
: public s616
{
s643 s586;
bool s1309;
public:
s911( s269* s307, s616* s612, const std::vector<s278*>& l, /*s643 s586,*/
s1172 s513, const std::wstring& methName, const s270* s737 );
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281 = NULL, size_t s518 = 0 ) override;
};
class s912
: public s616
{
public:
s912( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 )
: s616( s307, s613, s612, l, s737 ) {}
s912( const s912& right, s279* s613, s616* s612, const std::vector<s278*>& s281,
const s270* s737 );
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281 = NULL, size_t s518 = 0 ) override;
};
class Stream
{
public:
Stream() {}
virtual ~Stream() {}
virtual void write( s504 p );
};
class s528
: public s351, public Stream
{
static s356 s363;
std::basic_stringstream<wchar_t> ss;
static void s529( s502** s281, size_t n );
static void s342( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s528( const s528&, const s270* ast_ = NULL );
s528( s269* s307, const s270* ast_ = NULL );
~s528(){}
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
virtual void* addr() override { return (void*)&ss; }
virtual void write( s504 p ) override;
virtual std::wstring to_wstring() const override;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s528> s871;
class s375;
class s375
: public s351
{
static s356 s363;
std::wstring s364;
static void s1385( s502** s281, size_t n );
static void s403( s502** s281, size_t n );
static void s404( s502** s281, size_t n );
static void s846( s502** s281, size_t n );
static void s977( s502** s281, size_t n );
static void s978( s502** s281, size_t n );
static void s830( s502** s281, size_t n );
static void s851( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
static void s415( s502** s281, size_t n );
static void s416( s502** s281, size_t n );
static void s417( s502** s281, size_t n );
static void s418( s502** s281, size_t n );
static void s419( s502** s281, size_t n );
static void s425( s502** s281, size_t n );
static void s1143( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s375( const s375&, const s270* ast_ = NULL );
s375( s269* s307, s279* s613, const std::vector<s278*>& l, const s270* ast_ = NULL );
s375( s269* s307, const std::wstring& s = std::wstring( L"" ), const s270* ast_ = NULL );
s375( s269* s307, const std::wstring& s, size_t& pos, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const override;
virtual bool operator<( const s502* p ) const override;
std::wstring* s373() { return &s364; }
virtual void* addr() override { return (void*)&s364; }
virtual operator bool() const override { return !s364.empty(); }
virtual operator int() const override;
virtual operator double() const override;
virtual std::wstring to_wstring() const override;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
typedef s375 TDString;
extern s1::s9<s375> s843;
class s874
: public s616
{
s504 s810, s760;
s504 s861, s853;
size_t s757, nTo;
int s845, s782;
s1::s9<s375> str;
enum s784 { s756, s823, s811, s873 };
public:
enum s1266{ s1373, s1381, s1372, s1377, s1365, s1361 };
s874( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
s874( s269* s307 );
virtual const std::wstring& s306() const override { return s805; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s269;
class s324;
class s333;
class s794;
class s1050;
class s401;
struct s330
{
std::size_t operator()( const s505 k ) const
{
return k->s331();
}
};
struct s332
{
bool operator()( const s505 l, const s505 r ) const
{
return l->operator==( ( s502* )&( *r ) );
}
bool operator()( const s502* l, const s502* r ) const
{
return l->operator==( r );
}
bool operator()( const s502& l, const s502& r ) const
{
return l.operator==( &r );
}
};
class Iterator
{
public:
virtual ~Iterator() {}
virtual s278* s323() = 0;
virtual s278* s1054() = 0;
virtual s278* Idx() = 0;
virtual s278* El() = 0;
virtual bool operator==( const Iterator* r ) { return this == r; }
virtual bool operator<( const Iterator* r ) { return this < r; }
};
class s1243
: public Iterator
{
protected:
bool s969;
public:
s1243() : s969( false ) {}
virtual void reverse() = 0;
bool Reversed() const { return s969;  }
};
class s1261
: public s1243
{
public:
};
struct s910;
class s337
: public s351
{
protected:
s1172 s325;
s1172 s1344;
s1172 s335;
virtual s502* s1334( Iterator* it );
public:
s337( s269* s307, const s270* ast_ )
: s351( s307, ast_ ), s325(0), s1344(0), s335(0) {}
s337( const s337& r )
: s351( r ), s325(r.s325), s1344(r.s1344), s335(r.s335) {}
virtual ~s337() {}
virtual size_t s1262() const { return 0; }
virtual Iterator* s322( s401* r ) = 0;
virtual s1172 s328() const { return s325; }
virtual s1172 s1025() const { return s1344; }
virtual s1172 ValType() const { return s335; }
virtual Iterator* s1329() = 0;
virtual Iterator* s1333() = 0;
virtual Iterator* s1305( const s502* idx );
virtual Iterator* s1327( const s502* s364 );
virtual Iterator* s1387( const s502* s364 );
virtual s502* sort( bool reverse, s910* cmp );
};
class s1057 
: public s1261
{
typedef std::vector<s504>::iterator s1028;
typedef std::vector<s504>::reverse_iterator s1398;
s1::s9<s324> v;
s1028 s1360;
s1398 s1410;
size_t s1359;
s1::s9<s361> s1315;
s1::s9<s1050> s1314;
public:
s1057( s1057* it );
s1057( s324* v_, s1028 it );
s1057( s324* v_, s1398 it );
virtual s278* s323() override;
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
virtual void reverse();
s1028 s1270() { return s1360; }
s1398 s1271() { return s1410; }
virtual bool operator==( const Iterator* r );
virtual bool operator<( const Iterator* r );
};
class s1053
: public Iterator
{
typedef std::vector<s504>::iterator s1028;
s1::s9<s794> v;
s1028 s1360;
size_t s1359;
s1::s9<s361> s1315;
public:
s1053( s1053* it );
s1053( s794* v_, s1028 it );
virtual s278* s323() override;
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
};
class s1027
: public Iterator
{
typedef std::unordered_map<s505, s505, s330, s332>::iterator s1028;
s1::s9<s333> v;
s1028 s1360;
s504 s1315;
s1::s9<s1050> s1314;
public:
s1027( s1027* it );
s1027( s333* v_, s1028 it );
virtual s278* s323() override;
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
};
class s1253
: public s1261
{
typedef std::map<s505, s505, s332>::iterator s1028;
typedef std::map<s505, s505, s332>::reverse_iterator s1398;
s1::s9<s333> v;
s1028 s1360;
s1398 s1410;
s504 s1315;
s1::s9<s1050> s1314;
public:
s1253( s1253* it );
s1253( /*s333* v_,*/ s1028 it );
virtual s278* s323() override;
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
virtual void reverse();
};
/*
*/
class s1268
: public s351
{
s504 s613;
s1::s1445<Iterator> s364;
static s356 s363;
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s1268( s269* s307, const std::wstring& s79, const s270* ast_ = NULL );
s1268( const s1268& right, const s270* ast_ = NULL );
s1268( s269* s307, s279* s613, Iterator* it, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual void* addr() override { return (void*)&s364; }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s401
: public /*s351*/ s337,
public Iterator
{
s1::s1445<Iterator> s1391, s1392;
s504 s1394, s1395;
bool s1074, s1075;
Iterator* s326;
int s1087;
s1::s9<s361> s1317;
s279* ns;
static s356 s363;
std::wstring s519;
static void s1385( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
enum s1266 { s1374, s1382, s1373, s1381, s1384, s1369, s1375 };
typedef std::pair<s1::s1445<Iterator>, s1::s1445<Iterator>> s1269;
s401( s269* s307 );
s401( int b, int e = -1 );
s401( s269* s307, const std::wstring& s79, const s270* ast_ = NULL );
s401( const s401& right, const s270* ast_ = NULL );
s401( s269* s307, s279* s613, const std::vector<s278*>& l, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s1267 s1336( const std::wstring& s358, 
s1240& ap ) const override;
virtual s1267 s1331( const std::wstring& s358,
s1240& ap ) const override;
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)s326; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual Iterator* s322( s401* r ) override;
virtual s278* s323() override;
virtual Iterator* s1329() override { return s1391; }
virtual Iterator* s1333() override { return s1392; }
s1269 s1338( s337* s613 );
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s1257
: public s337,
public Iterator
{
s504 s613;
s505 s1183;
s505 s1083;
s1::s1445<Iterator> s1391, s1392;
s504 start, stop, where, s1181;
int s1198, s1200, s834;
bool s1074, s1075;
Iterator* s326;
s387 s1086; // @it - for using in s1347 scope lambdas
s278* s1087;
s279* ns;
static s356 s363;
s1::s9<s361> s364, s718;
long first{}, last{}, incr{};
s504 fir, las, inc;
std::wstring s519;
static void s1385( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
enum s1266 { s1374, s1382, s1373, s1381, s1384, s1369, s1375 };
s1257( s269* s307 ) : s337( s307, NULL ), s1086( L"@it", s307 ) {}
s1257( s269* s307, const std::wstring& s79, const s270* ast_ = NULL );
s1257( s269* s307, long fi, long la, long inc, const s270* ast_ = NULL );
s1257( s269* s307, s504 fi, s504 la, s504 inc, const s270* ast_ = NULL );
s1257( const s1257& r, const s270* ast_ = NULL );
s1257( s269* s307, s279* s613, const std::vector<s278*>& l, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
virtual s1172 s328() const override { return s718->s367(); }
virtual size_t s1262() const override { return s1083.s16<s337*>()->s1262(); }
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)&s364; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual bool s580( const std::wstring& s285, s387* s157,
const std::wstring& s347 ) const override;
virtual s278* s623( size_t off ) override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual Iterator* s322( s401* r ) override;
virtual s278* s323() override;
virtual s278* s1054() override;
virtual s278* Idx() override;
virtual s278* El() override;
virtual Iterator* s1329() override { return s1391; }
virtual Iterator* s1333() override { return s1392; }
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s1041
: public s1257
{
s507 s1169;
s507 set;
s507 eq;
s504 start;
s504 end;
s504 incr;
s504 s1088;
bool s1156;
public:
s1041( s269* s307, const std::vector<s278*>& l );
virtual void s520( s279* s962 ) override;
virtual Iterator* s322( s401* r ) override;
virtual s278* s323() override;
};
extern s1::s9<s401> s865;
extern s1::s9<s1257> s1259;
class s909;
struct s910;
template<class _Cont, class Der>
class s321 :
public s337
{
protected:
typedef Der s1308;
_Cont s364;
static s356 s363;
static void s340( s502** s281, size_t n );
static void s1357( s502** s281, size_t n );
static void s1356( s502** s281, size_t n );
static void s342( s502** s281, size_t n );
static void s1406( s502** s281, size_t n );
static void s1419( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
typedef s321<_Cont, Der> s1312;
s321( s269* s307, const s270* ast_ )
: s337( s307, ast_ ) {}
s321( const s1312& r )
: s337( r ) {}
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
};
/*
template<class _Cont>
void s321<_Cont>::s403( s502** s281, size_t n )
{
s324* pv = ( (s324*)s281[1] );
size_t idx = (size_t)(int)*s281[2];
v->s364[idx] = (s502*)s281[3]->s350();
}
template<class _Cont>
void s321<_Cont>::s338( s502** s281, size_t n )
{
return pv->s364.size();
}*/
template<class _Cont, class Der>
void s321<_Cont, Der>::s340( s502** s281, size_t n )
{
using s1248 = s1308;
s1248* pv = ( (s1248*)s281[1] );
*( (s361*)*s281 )->s373() = (int)pv->s364.size();
}
template<class _Cont, class Der>
void s321<_Cont, Der>::s342( s502** s281, size_t n )
{
using s1248 = s1308;
s1248* pv = ( (s1248*)s281[1] );
pv->s364.clear();
}
class s324
: public s321<std::vector<s504>, s324>
{
protected:
static s356 s363;
typedef s324 s1308;
typedef std::vector<s504> s1056;
std::wstring s519;
static void s403( s502** s281, size_t n );
static void s1416( s502** s281, size_t n );
static void s338( s502** s281, size_t n );
static void s339( s502** s281, size_t n );
static void s341( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
void s1062( const std::wstring& s79, s279* s613, const s270* ast_ );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
virtual void s1300( const std::wstring& s79, /*std::wstring& s1428, std::wstring& s674,*/
s279* s613, const std::wstring& s74 );
virtual void s1298( const std::wstring& s1428 );
public:
typedef s1057 s1263;
s324( s269* s307 ) : s321( s307, NULL ) {}
s324( s269* s307, s279* s613, const std::wstring& s79, const s270* ast_ = NULL,
const std::wstring& s74 = L"," );
s324( s269* s307, const std::vector<s278*>& l, const s270* ast_ = NULL );
s324( const s324& right, const s270* ast_ = NULL );
s324( s269* s307, s1172 s335, const s270* ast_ = NULL );
virtual ~s324() override;
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
s1172 s1339( const std::wstring& s1428, s869::Cont& s613 );
virtual size_t s1262() const override { return 2; }
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)&s364; }
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
void load( const std::wstring& s79, s279* s613, const std::wstring& s74 );
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
s504 operator[]( size_t n ) { return s364[n]; }
const s504& operator[]( size_t n ) const { return s364[n]; }
virtual Iterator* s322( s401* r ) override;
virtual Iterator* s1329() override { return new s1057( this, s364.begin() ); }
virtual Iterator* s1333() override { return new s1057( this, s364.end() ); }
virtual Iterator* s1305( const s502* idx ) override;
virtual Iterator* s1327( const s502* s364 ) override;
virtual s502* s1334( Iterator* it );
void clear() { s364.clear(); }
void add( s504 el ) { s364.push_back( el ); }
void erase( size_t n ) { s364.erase( begin( s364 ) + n ); }
size_t size() const { return s364.size(); }
virtual s502* sort( bool reverse, s910* cmp ) override;
virtual s502* reverse( bool reverse, s910* cmp );
std::vector<s504>& s329() { return s364; }
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s794
: public s337
{
protected:
typedef std::vector<s504> s1056;
static s356 s363;
std::vector<s504> s364;
std::vector<s504>::iterator s326;
std::wstring s519;
static void s403( s502** s281, size_t n );
static void s338( s502** s281, size_t n );
static void s339( s502** s281, size_t n );
static void s340( s502** s281, size_t n );
static void s341( s502** s281, size_t n );
static void s342( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
static void s343( s502** s281, size_t n );
static void s1101( s502** s281, size_t n );
static void s1186( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
virtual void s1300( const std::wstring& s79, std::wstring& s1428, std::wstring& s674,
std::vector<s1::s9<s6::s145>>& s97, const s270* ast_, const std::wstring& s74 );
public:
s794( s269* s307 )
: s337( s307, NULL ) {}
s794( s269* s307, const s270* ast_ )
: s337( s307, ast_ ) {}
s794( s269* s307, s279* s613, const std::wstring& s79, 
const s270* ast_=NULL, const std::wstring& s74 = L"," );
s794( s269* s307, const std::vector<s278*>& l, const s270* ast_ = NULL );
s794( const s794& right );
virtual ~s794() override;
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
virtual s1172 s328() const override;
virtual s1172 s1025() const override { return s825->s367(); }
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
virtual size_t s1262() const override { return 2; }
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)&s364; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
s504 operator[]( size_t n ) { return s364[n]; }
const s504& operator[]( size_t n ) const { return s364[n]; }
virtual Iterator* s322( s401* r ) override;
virtual Iterator* s1329() override { return new s1053( this, s364.begin() ); }
virtual Iterator* s1333() override { return new s1053( this, s364.end() ); }
void clear() { s364.clear(); }
void add( s504 el ) { s364.push_back( el ); }
void assign( const std::vector<s504>& v );
size_t size() const { return s364.size(); }
std::vector<s504>& s329() { return s364; }
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
class s1050
: public s794
{
static s356 s363;
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
virtual void s1300( const std::wstring& s79, /*std::wstring& s1428, std::wstring& s674,*/
s279* s613, const std::wstring& s74 );
virtual void s1298( const std::wstring& s1428 );
static void s403( s502** s281, size_t n );
static void s1417( s502** s281, size_t n );
static void s338( s502** s281, size_t n );
static void s339( s502** s281, size_t n );
static void s340( s502** s281, size_t n );
static void s341( s502** s281, size_t n );
static void s342( s502** s281, size_t n );
static void s414( s502** s281, size_t n );
static void s343( s502** s281, size_t n );
static void s1101( s502** s281, size_t n );
static void s1186( s502** s281, size_t n );
public:
s1050( s269* s307 ) : s794( s307 ) {}
s1050( s269* s307, s279* s613, const std::wstring& s79, const s270* ast_=NULL,
const std::wstring& s74 = L"," );
s1050( s269* s307, const std::vector<s278*>& l, const s270* ast_ = NULL );
s1050( const s1050& right, const s270* ast_ = NULL );
virtual ~s1050() override {}
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual void s520( s279* s962 ) override;
void load( const std::wstring& s79, s279* s613, const std::wstring& s74 );
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
virtual std::wstring to_wstring() const;
};
class s333
: public s337
{
static s356 s363;
typedef std::unordered_map<s505, s505, s330, s332> s1026;
s1026 s364;
s1026::iterator s326;
std::wstring s519;
static void s344( s502** s281, size_t n );
static void s338( s502** s281, size_t n );
static void s1115( s502** s281, size_t n );
static void s403( s502** s281, size_t n );
static void s345( s502** s281, size_t n );
static void s340( s502** s281, size_t n );
static void s343( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
virtual void s1300( const std::wstring& s79, std::wstring& s1428, std::wstring& s674,
std::vector<std::pair<std::wstring, s6::s146>> s148, const s270* ast_ );
public:
s333( s269* s307 ) : s337( s307, NULL ) {}
s333( s269* s307, s1172 s1344, s1172 s335, const s270* ast_ = NULL );
s333( s269* s307, s279* s613, const std::wstring& s79, const s270* ast_ = NULL );
s333( const s333& right, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)&s364; }
virtual s1172 s1332( const std::wstring& methName, const std::vector<s504>& l ) const override;
virtual size_t s1262() const override { return 2; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual Iterator* s322( s401* r ) override;
virtual Iterator* s1329() override { return new s1027( this, s364.begin() ); }
virtual Iterator* s1333() override { return new s1027( this, s364.end() ); }
s1026& s329() { return s364; }
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s324> s765;
extern s1::s9<s794> s788;
extern s1::s9<s1050> s1051;
extern s1::s9<s333> s771;
typedef s324 TDVector;
typedef s333 TDIndex;
struct s910
{
std::vector<s504>s934;
s507 s932;
s910( s507 s933 ) : s932( s933 ) { s934.resize( 2 ); }
virtual bool operator()( const s504 l, const s504 r )
{
s934[0] = l;
s934[1] = r;
s932->s621( s934 );
return (bool)*s932->s517( 0, 0 );
}
};
class s909
: public s616
{
bool reverse;
s507 s932;
public:
s909( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s926; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s1273
: public s616
{
s504 range;
bool s1346;
s507 s989;
public:
enum s1266 { s1376, s1383, s1366 };
s1273( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s1304; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s431
: public s351
{
static s356 s363;
std::wstring path;
std::wstring s548;
s324 s799;
s324 s862;
static void s425( s502** s281, size_t n );
static void s432( s502** s281, size_t n );
static void s433( s502** s281, size_t n );
static void s1089( s502** s281, size_t n );
static void s340( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s431( s269* s307 ) : s351( s307, NULL ), s799(s307), s862(s307) {}
s431( s269* s307, const std::wstring& s79, const s270* ast_=NULL );
s431( const s431& right, const s270* ast_ = NULL );
s431( s269* s307, const std::wstring& s, size_t& pos, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)&s799; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s431> s867;
} // namespace
namespace transd
{
class s630
: public s616
{
public:
s630( s269* s307, s279* s617, s616* s618, const std::vector<s278*>& l, 
const s270* s737 );
virtual const std::wstring& s306() const override { return s239; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
s278* s748( const std::wstring& s285, s387* ref,
const std::wstring& s347 ) const;
virtual s278* s350() const override;
};
class s312
: public s616
{
s504 s313;
public:
s312( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, 
const s270* s737 );
virtual const std::wstring& s306() const override { return s261; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s315
: public s616
{
s504 s316;
s508 s317;
s505 s318;
s387 s319;
s361 s320;
public:
s315( s269* s307, s279* s613, Transd* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s260; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s641
: public s616
{
s508 s749;
s505 varval;
s504 s316;
s504 where;
s504 select;
s387 s319;
s361 s320;
public:
s641( s269* s307, s279* s613, Transd* s612, const std::vector<s278*>& l, 
const s270* s737 );
virtual const std::wstring& s306() const override { return s266; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s629
: public s616
{
std::vector<s1172> types;
std::vector<s507> s679;
public:
s629( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
void s678( s1172 type, s616* pOvr );
virtual s505 s517( s502** s281, size_t s518 ) override;
};
class s907
: public s616
{
public:
s907( s269* s307 );
s907( s269* s307, s279* s617, s616* s618, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s258; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s502* s516() override { return this; }
virtual s278* s350() const override;
s502* s371( s279* s613, const std::vector<s1172>& vt ) const override;
};
extern s1::s9<s907> s1265;
class s908
: public s616
{
public:
s908( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s925; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s984
: public s616
{
int code;
public:
s984( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s988; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s632
: public s616
{
public:
s632( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s250; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s633
: public s616
{
public:
s633( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s633( s269* s307 );
virtual const std::wstring& s306() const override { return s249; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s634
: public s616
{
s603 s648;
std::vector<s603> s649;
public:
enum s1266{ s1370, s1371 };
s634( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s634( s269* s307 );
virtual const std::wstring& s306() const override { return s236; }
virtual void s520( const std::wstring& s347, bool proc ) override;
void s777( bool proc );
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s635
: public s616
{
s505 s43;
public:
enum s1266{ s1381 };
s635( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s635( s269* s307 );
virtual const std::wstring& s306() const override { return s257; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s637
: public s616
{
s377 s80;
public:
s637( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s637( s269* s307 );
virtual const std::wstring& s306() const override { return s265; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s639
: public s616
{
public:
s639( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s639( s269* s307 );
virtual const std::wstring& s306() const override { return s264; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s638
: public s616
{
s387 s78;
s377 s647;
s1::s9<s639> ctch;
public:
s638( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
s638( s269* s307 );
virtual const std::wstring& s306() const override { return s263; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s640
: public s616
{
s505 s646;
std::vector<s278*> s724;
s505 s718;
public:
s640( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s267; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
bool s580( const std::wstring& s285, s387* ref, 
const std::wstring& s347 ) const override;
virtual s278* s350() const override;
};
class s800
: public s616
{
std::vector<std::wstring> fields;
public:
s800( s269* s307, s279* s613, s616* s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s796; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s636
: public s616
{
public:
s636( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
s636( s269* s307 );
virtual const std::wstring& s306() const override { return s262; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s642
: public s616
{
static s269* s994;
public:
s642( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
s642( s269* s307 );
virtual const std::wstring& s306() const override { return s268; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s849
: public s616
{
public:
s849( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
s849( s269* s307 );
virtual const std::wstring& s306() const override { return s819; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s824
: public s616
{
std::wstring s992;
public:
s824( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
s824( s269* s307 );
virtual const std::wstring& s306() const override { return s879; }
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
class s826
: public s1::s10
{
typedef std::map<std::wstring, s504> s764;
s764 s809;
size_t rechash;
public:
s826() {}
explicit s826( s269* s307, const std::wstring& rec, const std::vector<std::wstring>& s785,
std::vector<s504>& types );
s505 s806( const std::wstring& s78, bool s751=true ) const;
void s938( s794& s157 ) const;
void s569( std::vector<std::wstring>& s157 ) const;
size_t s331() const;
bool operator==( const s826* p ) const;
bool operator<( const s826* p ) const;
std::wstring to_wstring() const;
void s311( std::wostream* pd, int s202 = 0 ) const;
};
typedef s1::s9<s826> s880;
class s868
: public s1::s10
{
typedef std::vector<s504> s776;
s776 s864;
size_t s852;
public:
s868() {}
s868( std::vector<std::wstring>& s773, s880 rec );
size_t s331() const;
bool operator==( const s868* p ) const;
bool operator<( const s868* p ) const;
void s311( std::wostream* pd, int s202 = 0 ) const;
};
typedef s1::s9<s868> s775;
struct s818
{
std::size_t operator()( const s775 k ) const
{
return k->s331();
}
};
struct s752
{
std::size_t operator()( const s775 l, const s775 r ) const
{
return l->operator==( ( s868* )&( *r ) );
}
};
struct s917
{
std::size_t operator()( const s880 k ) const
{
return k->s331();
}
};
struct s916
{
std::size_t operator()( const s880 l, const s880 r ) const
{
return l->operator==( ( s826* )&( *r ) );
}
};
class s680
: public s351
{
public:
typedef std::multimap<std::wstring, std::pair<std::wstring, std::wstring>> BaseMap;
typedef std::map<std::wstring, std::multimap<s505, s880>> s336;
typedef std::unordered_map<s775, s880, s818, s752> s838;
private:
static s356 s363;
std::map<std::wstring, s336> s946;
BaseMap s681, s682, s683;
BaseMap::iterator s326;
s838 s802;
std::wstring s519;
static void s837( s502** s281, size_t n );
static void s854( s502** s281, size_t n );
static void s797( s502** s281, size_t n );
static void s817( s502** s281, size_t n );
static void s345( s502** s281, size_t n );
static void s340( s502** s281, size_t n );
static void s343( s502** s281, size_t n );
static void s929( s502** s281, size_t n );
virtual void s365() override;
virtual const s356& s357() const override { return s363; }
public:
s680( s269* s307 ) : s351( s307, NULL ) {}
s680( s269* s307, const std::vector<s278*>& l, const s270* ast_ = NULL );
s680( s269* s307, const std::wstring& s79, const s270* ast_ = NULL );
s680( const s680& right, const s270* ast_ = NULL );
s680( s269* s307, const std::wstring& s, size_t& pos, const s270* ast_ = NULL );
virtual s502* s370( const s270& s737, s279* s613, const std::wstring& s347 ) override;
virtual s502* s371( s279* s613, const std::vector<s278*>& l ) const override;
virtual bool s522( const s502* s523 ) const override;
virtual void* addr() override { return (void*)NULL; }
virtual void s520( s279* s962 ) override;
virtual s278* s350() const override;
virtual void s372( s278* p ) const override;
virtual size_t s331() const;
virtual bool operator==( const s502* p ) const;
virtual bool operator<( const s502* p ) const;
void s684( const std::wstring& s199 );
void s685( const std::wstring& q );
void s755( const std::wstring& s882, const std::wstring& s785 );
void s928( const std::wstring& s931 );
void select( std::wstring& s931, s505 s685, 
s336::mapped_type::iterator& s949, s336::mapped_type::iterator& s950 );
virtual std::wstring to_wstring() const;
virtual void s311( std::wostream* pd, int s202 = 0 ) const override;
};
extern s1::s9<s680> s808;
} // namespace
namespace transd {
class s822
: public s351
{
};
struct s786
{
enum s906 { s889=0, s896 };
int distinct;
int	s974;
std::wstring s973;
int s953;
s786()
: distinct( -1 ), s974( -1 ), s953( -1 )
{	}
};
class s985
: public s616
{
size_t s996;
s505 s718;
public:
s985() : s616( NULL, NULL, NULL, s589, L"", NULL ), 
s718( new s376( NULL, false ) ){ }
void s995( size_t idx ) { s996 = idx; }
virtual s505 s517( s502** s741, size_t s518 ) override
{
s504 l = s281[0];
s504 r = s281[1];
*s718.s16<s376*>()->s373() = l.s16<s794*>()->operator[]( s996 ).s16<s502*>()->
operator<( r.s16<s794*>()->operator[]( s996 ).s16<s502*>() );
s505 s993 = s718;
return s993;
}
};
class s324;
class s842
: public s616
{
s504 db;
s508 verb;
s504 what;
s504 where;
s504 s976;
s504 s1183;
s504 s953;
s1::s9<s324> s792;
s786 s863;
s387 s774;
s506 s833;
public:
enum s1266{ s1379, s1362, s1363, s1384, s1368, s1380, s1364, s1367,	s1378 };
s842( s269* s307, s506 s613, s507 s612, const std::vector<s278*>& l, const s270* s737 );
virtual const std::wstring& s306() const override { return s875; }
virtual void s520( const std::wstring& s347, bool proc ) override;
virtual s505 s517( s502** s281, size_t s518 ) override;
virtual s278* s350() const override;
};
typedef int HPROG;
struct s759
{
std::vector<std::wstring> s694;
std::wstring entry;
};
class s585;
class s269
: public s279
{
std::vector<std::wstring> s204;
s270 s737;
std::wstring s205;
std::wstring s814;
void s206( const std::wstring& s285 );
void s207( const s6::s147& obj, s759& s157 );
void s218( const std::wstring& s199, const s6::s147& obj );
s510 s208;
s501 s209;
typedef std::map<std::wstring, s502*> s210;
s210 s211;
typedef std::map<uint32_t, std::set<std::wstring>> s1030;
public:
s269();
~s269();
const std::wstring& s753() const { return s814; }
virtual std::wstring s900() const { return L"::"; }
void s520( bool soft = false );
void reset();
void s212( s270& s213 );
void s214( const std::wstring& s215 );
void s216( s6::s147& obj );
void s217( const std::wstring& s215 );
s502* run( const std::vector<std::wstring>& s724 );
s502* callFunc( const std::wstring& s626, std::vector<std::wstring>& l );
s507 getProc( const std::wstring& s626 );
s510& TR() { return s208; }
s616* s219( const std::wstring& s626, std::vector<s278*>& s281, s279* s613, s616* s220,
const s270* s737 );
void s223( const std::wstring& s );
void s224( s502* p, const std::wstring& s362 );
void s225( const std::wstring& s364, const std::wstring& s347,
std::vector<std::wstring>& s157 );
virtual bool s580( const std::wstring& s285, s387* s157,
const std::wstring& s347 ) const override;
s505 s226( const std::wstring& s364, const std::wstring& s347 );
bool s227( const std::wstring& s,	const s502* s1130) const;
s278* s228( const std::wstring& sym, const std::wstring& s519,
bool s544 = true );
void* s229( const std::wstring& s285 );
virtual void s311( std::wostream* pd, int s202 = 0 ) const;
};
typedef s1::s9<s269> s758;
void evaluateExpression( const std::wstring& s79 );
HPROG createAssembly();
void loadProgram( HPROG handle, const std::wstring& s194 );
void s216( HPROG handle, s6::s147& obj );
TDType* run( HPROG handle, const std::vector<std::wstring>& s724 );
void* callFunc( HPROG handle, const std::wstring& s79, std::vector<std::wstring>& l );
TDType* getProc( HPROG handle, const std::wstring& s626 );
void* s229( HPROG handle, const std::wstring& s285 );
void* execute( TDType* func );
void importSymbol( HPROG handle, const std::wstring& s1230, const std::wstring& symName,
const std::wstring& s347 );
void importFile( HPROG handle, const std::wstring& s1230, const std::wstring& s45,
const std::wstring& s347 );
HPROG initShell( const std::wstring& s1230, const std::wstring& modText );
typedef s2::s17 TransDException;
} // namespace transd
