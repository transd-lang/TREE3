/*
This is a distributed file for Transd programming language embedding
library.

Copyright (c) 2020 Albert Berger [alberger at gmail com].
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
	library of Transd programming language.

	Transd Project Website: https://github.com/transd-lang
*/
#include <vector>
#include <map>
#include <list>
#include <codecvt>
#include <set>



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

class s2
{
	int refs;
public:
	s2() : refs(0){}

	virtual ~s2()
	{
	}

	void upcount()
	{
		refs++;
	}

	void downcount()
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
class s3
{
	C* p;
public:
	s3( C* p_ ) : p(p_)
	{
		if(p)
			p->upcount();
	}

	s3(C& p_) 
	{
		p = &p_;
		if(p)
			p->upcount();
	}

	s3()
	{
		p = NULL;
	}

	s3(const s3<C> &pn)
	{
		p = pn.p;
		if(p)
			pn.p->upcount();
	}

	template<class D> 
	s3( s3<D> &pn )
	{
		p = nullptr;
		if ( SUPERSUBCLASS( C, D ) ) {
			p = (C*)pn;
			if(p)
				p->upcount();
		}
	}

	~s3()
	{
		detach();
	}


	operator C*() { return p; }

	C& operator*() { return *p; }

	const C& operator*()const { return *p; }

	C* operator->() { return p; }

	const C* operator->()const { return p; }

	s3& operator=( s3<C> &p_ ) { return operator=(( C* ) p_); }

	s3& operator=( const s3<C> &p_ ) { return operator=( (s3<C>& ) p_ ); }

	s3& operator=( C* p_ )
	{
		if(p){
			p->downcount();
		}

		p = p_;
		if(p)
			p->upcount();
		return *this;
	}


	template<class B>
	operator B*()
	{
		return checked_cast<C, B>( p );
	}

	template<class D>
	s3& operator=( const s3<D> &p_ )
	{
		if ( SUPERSUBCLASS( C, D ) )
			return operator=( ( C* ) p_);
	}

	template<class ToType>
	ToType scast() const
	{
		return static_cast<ToType>( p );
	}
	
	template<class ToType>
	ToType dcast() const
	{
		return dynamic_cast<ToType>( p );
	}

	bool IsNull()const { return p == nullptr; }

	bool IsValid()const { return p != nullptr; }

	void detach()
	{
		if(p){
			p->downcount();
			p = nullptr;
		}
	}

	bool operator ==(const s3<C>&ptr){return ((INT_PTR)ptr.p == (INT_PTR)p);}
	bool operator !=(const s3<C>&ptr){return ((INT_PTR)ptr.p != (INT_PTR)p);}
	bool operator ==(const C& val){return ( *p == val );}
	bool operator !=(const C& val){return ( *p != val );}
};

#if defined (_MSC_VER)
#pragma warning( pop )
#endif

} // namespace s1

namespace s4 {

void kexceptInit();

class s5
								: public std::exception
{
	static uint32_t s16;

	std::list<std::wstring> s15;

	uint32_t id; 
public:
	enum class s6 : uint32_t
	{
		s7 = 0,
		s8,
		s9,
		s10,
		s11,
		s12,
		s13,
		s14
	};

	s5( const std::wstring& s, uint32_t n = (uint32_t)s6::s8 )
		: id( n )
	{
		s15.push_back( s );
	}

	s5( uint32_t n )
		: id( n )
	{
		s15.push_back( L"Exception" );
	}

	static void s231()
	{
		s16 = (uint32_t)s6::s14 + 1;
	}

	static uint32_t nextId()
	{
		return s16++;
	}

	const wchar_t* Msg() const
	{
		if( s15.size() )
			return s15.back().c_str();
		return NULL;
	}

	const char* what() const noexcept
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		return conv.to_bytes( s15.back() ).c_str();
	}
	uint32_t which() const { return id; }

	void addInfo( const std::wstring& s )
	{
		s15.push_back( s );
	}

};

} // namespace s4
namespace s17 {

bool s18( const std::wstring& _dir, const std::wstring& s386, std::wstring& res );
void s19( const std::wstring& _dir, const std::wstring& s386, std::vector<std::wstring>& files,
	std::vector<std::wstring>& dirs );
time_t s20( const std::wstring& f );
uint8_t s21( const std::wstring& f );
bool s22( const std::wstring& s385 );
bool s23( const std::wstring& s385 );
std::wstring s24();


} // namespace s17
namespace s25 
{
extern std::wstring s26;
extern std::string s27;
extern std::wstring s28;
enum s6 { s12 };

std::wstring s29( const std::wstring& l, const std::wstring& s, const std::wstring& r );
std::wstring s30( const std::wstring& s, const std::wstring& c );
bool s31( const std::wstring& s, const std::wstring& ss );
void s32( const std::wstring& s, size_t s390, wchar_t left, wchar_t right, 
		size_t& start, size_t& end);
void s33( const std::wstring& s, size_t s390, wchar_t c, size_t& start, 
		size_t& end );
int s34( const std::wstring& sf, wchar_t s391, size_t& pos );
void s35( const std::wstring& s, const std::wstring& s391, std::vector<std::wstring>& res );
std::wstring s461( const std::wstring& sf, size_t& pos );
void s36( const std::wstring& sf, const std::wstring& s391, 
		std::pair<std::wstring, std::wstring>& pr, size_t& pos );
void s37( const std::wstring& sf, const std::wstring& s391,
		std::vector<std::pair<std::wstring, std::wstring>>& v );
std::wstring s38( const std::wstring& sf );
void s39( std::wstring& dir );
bool s40( const wchar_t *str, long *val, wchar_t **end = NULL );
bool s41( const wchar_t *str, double *val, wchar_t **end = NULL );

std::string s29( const std::string& l, const std::string& s, const std::string& r );
std::string s30( const std::string& s, const std::string& c );
void s32( const std::string& s, size_t s390, char left, char right, 
						size_t& start, size_t& end);
int s34( const std::string& sf, char s391, size_t& pos );
void s35( const std::string& s, const std::string& s391, std::vector<std::string>& res );
void s37( const std::string& sf, std::vector<std::pair<std::string, std::string>>& v );
std::string s38( const std::string& sf );

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
constexpr UINT rol(UINT val, size_t n) {
    static_assert(std::is_unsigned<UINT>::value,
                  "Rotate Left only makes sense for unsigned types");
    return (val << n) | (val >> (sizeof(UINT)*8-n));
}

void s42( const std::wstring& msg );



} // namespace s25
namespace s43 {
extern std::locale locloc;
extern std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
}

#define U8(x) s43::conv.to_bytes( x )
#define U16(x) s43::conv.from_bytes( x )
#ifdef __LINUX__
#define KCHAR char
#define TOFS(x) s43::conv.to_bytes(x)
#define FROMTERM(x) s43::conv.from_bytes(x)
#else
#define KCHAR wchar_t
#define TOFS(x) x
#define FROMTERM(x) x
#endif
namespace s44
{

enum s45{ s46, s47, s48, s53, 
	s49, s50, s54, s51, s52 };


class s55;

typedef s1::s3<s55> s56;

class s57
							: public s1::s2
{
	std::multimap<std::wstring, s56> s58;

public:
	enum s59 { s60, s61, s62 };
	enum s6 { s7, s63 };
	const static s55 s64; // similar to string::npos
	s57(){}

	void s65( const std::wstring& sf );
	void s66( std::wostream* pd, bool strict=false ) const;

	bool s67( const std::wstring& key ) const;
	void s68( const std::wstring& key, std::vector<s56>& res ) const;
	const s56 s69( const std::wstring& key ) const;
	void s70( const std::wstring& nam, s56 val, s59 ap=s60 );
	void s71( std::vector<std::pair<std::wstring, s56>>& res ) const;

	bool operator==( const s57& r )  const;

	void s72( std::wostream* pd, int ind ) const;
};

bool operator==( const std::vector<s1::s3<s55>>& l,
	const std::vector<s1::s3<s55>>& r );

class s55
							: public s1::s2
{
	s45 var;
	s57 obj;
	std::wstring str;
	std::vector<s56> s73;
	double s74;
	bool b;
public:
	s55():var(s46){}
	s55( const std::wstring& s ):var(s48),str(s){}
	s55( const std::vector<s56>& a ): var(s49), s73(a){}

	s55( const std::wstring& sf, size_t& pos );

	s45 Var() const { return var; }

	bool s75() const { return var == s46; }

	const s57& s76() const
	{
		if( var == s47 )
			return obj;
		throw std::runtime_error( "wrong variant" );
	}

	const std::vector<s56>& s77() const
	{
		if( var == s49 )
			return s73;
		throw std::runtime_error( "wrong variant" );
	}

	double s78() const
	{
		if( var == s50 )
			return s74;
		throw std::runtime_error( "wrong variant" );
	}

	int s34() const
	{
		if( var == s54 )
			return (int)s74;
		throw std::runtime_error( "wrong variant" );
	}

	const std::wstring& s79() const
	{
		if( var == s48 || var == s53 )
			return str;
		throw std::runtime_error( "wrong variant" );
	}

	bool operator==( const s55& r ) const
	{
		return var == r.var && obj == r.obj && str == r.str && s73 == r.s73 && b == r.b && s74 == r.s74;
	}

	bool is( const s55& r ) const
	{
		return this == &r;
	}

	void s72( std::wostream* pd, int ind ) const;
	void s66( std::wostream* pd, bool strict=false ) const;
};


void s80( const std::wstring& s397, 
	std::vector<s1::s3<s57>>& res, 
	const std::wstring& sheb = std::wstring(L"") );
void s81( const std::wstring& sf, size_t& pos, s1::s3<s57> res );
void s82( const std::wstring& s397, 
	const std::vector<s1::s3<s57>>& objs );
} // namespace s44

#define DEFCONST extern const std::wstring

namespace transd {
namespace s96 {

DEFCONST s97;
DEFCONST s98;
DEFCONST s99;
DEFCONST s100;
DEFCONST s101;
DEFCONST s102;
DEFCONST s103;
DEFCONST s104;
DEFCONST s105;
DEFCONST s106;
DEFCONST s107;
DEFCONST s108;
DEFCONST s109;


DEFCONST s110;
DEFCONST s111;
DEFCONST s112;
DEFCONST s113;
DEFCONST s114;

DEFCONST s457;
DEFCONST s458;
DEFCONST s459;


DEFCONST s115;
DEFCONST s116;


DEFCONST s117;
DEFCONST s118;
DEFCONST s119;

DEFCONST s120;
DEFCONST s121;
DEFCONST s122;
DEFCONST s123;
DEFCONST s124;
DEFCONST s125;
DEFCONST s127;


#define INDSTEP 3
#define VECELSEP L','

DEFCONST s452;

} // namespace s96
enum s128 { s129, s130, s131, s132 };
extern std::wstring s133[];
extern const std::wstring s134, s135, s136,
s137,  s138,     s139,    s140,      s141,
s142,  s143, s144, s145,
s146, s147,     s148,     s149,
s150, s151,     s152,   s153,
s154,   s155, s156, s157,
s158, s159;

class s160;
class s161;
class s162;
class s163;
class s164;
typedef s162* ( *s165 )( const std::wstring& s170, const std::vector<s163*>& s166 );


class s161
{
public:
	typedef std::multimap<std::wstring, s161*> s167;
private:
	static std::map<std::wstring, s165> s168;

	std::wstring s169;
	std::wstring s170;
	s128 s171;
	std::wstring s172;
	s167 s173;

	void s174( const std::wstring& sf );
	void s175( const s44::s57& s47 );
	void s176( const std::wstring& sf );
	void s177( const std::wstring& sf );
	void s178( const std::wstring& type, const s44::s55& obj );

	static std::wstring s179( const std::wstring& sf, size_t &pos );

public:
	enum s6 { s7, s63 };
	s161(){ }
	s161( s128 at, const std::wstring& qpre, const std::wstring& nam )
		: s171( at ), s169( qpre ), s170( nam ) { }
	s161( const std::wstring& nam, const std::wstring& val )
		: s171( s129 ), s170( nam ), s172( val ) { }
	s161( const std::wstring& type );
	s161( const std::wstring& nam, const s44::s55& s188 );
	s161( const s44::s57& s47 );

	s128 s189() const { return s171; }
	std::wstring s190() const;
	const std::wstring& s191() const { return s170; }

	static void s180( const std::wstring& sf, size_t& pos, std::vector<std::wstring>& res );
	void s181( s44::s57& s47 );
	void s182( s160* s192, size_t s193 = 0 );
	const std::wstring& s183() const { return s172; }
	const s161& s184( const std::wstring& s170 ) const;
	s167& s185() { return s173; }
	void s186( const std::wstring& s ) { s170 = s; }


	static std::wstring s187( const s44::s57& obj,
		const std::wstring& default = std::wstring( L"" ) );
	static std::wstring s194( const s44::s57& obj,
		const std::wstring& s195,
		const std::wstring& default = std::wstring( L"" ) );

	void s196( std::wostream* pd, int ind = 0 ) const;
};
extern const std::wstring s197;

enum s198 { s199, s200, s201, s202, s203, 
							s204, s205, s206, s207 };
class s160;
class s208;
class s209;
class s164;
class s163;
typedef s163 s210;
typedef s163 TDType;
typedef s1::s3<s210> PProj;

class s163
							: public s1::s2
{
	friend class s211;
	static std::map<const s210*, bool> s212;
protected:
	s198 s213;
	size_t s214;
	s160* s192;
public:
	s163() : s213( s199 ), s214(0){ }
	s163( s198 pt_ ) : s213( pt_ ), s214(0) { }
	s163( s160* s466, s198 pt_ ) : s192( s466 ), s213( pt_ ),
		s214(0) { }
	virtual ~s163();
	s198 s437() const { return s213; } // s163 category
	virtual size_t s215() const { return s214; }
	virtual s209* s216();
	virtual s209* s217( s209** s166 = NULL, size_t s218 = 0 );
	virtual size_t s219() const { return 0; } // s183/result type
	virtual bool isTypeOf( const s209* classObj ) const;
	virtual void s221( const std::wstring& s220 );
	bool s222() const;
	virtual const s209* s223() const;
	virtual s163* s224() const;

	static s163* s225( s161& s370, s160* s192, s164* obj, const std::wstring& s226 );

	virtual operator bool() const;
	virtual operator int() const;
	virtual operator double() const;
	virtual std::wstring to_wstring() const;

/*	static void s180( const std::wstring& sf, size_t& pos,
		std::vector<std::wstring>& res );

	*/
	virtual void s196( std::wostream* pd, int ind = 0 ) const = 0;
};

typedef std::multimap<std::wstring, s210*> s227;
s210* s507( s227& m, const std::wstring& key );

class s209;
class s228;

class s209
							: public s163
{
	friend class s211;

protected:
	std::wstring s229; // DEBUG

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) = 0;

public:
	s209( s160* s192, s198 pc ) : s163( s192, pc ) { }
	virtual ~s209();



	static void s231( s160* s192 );
	virtual void s232() = 0;
	virtual size_t s233( const std::wstring& s234 ) const = 0;
	virtual void s235( size_t type ) = 0;
	virtual const std::wstring& s236() const = 0;
	virtual s209* s237() const = 0;
	virtual void s238( s210* p ) const = 0;
	virtual const s209* s223() const override = 0;
	void s239( const std::wstring& s ) { s229 = s; }


	virtual s209* s217( s209** s166, size_t s218 ) override { return this; }
	virtual s209* s216() override;
	virtual bool s240( const std::wstring& s170, s228* res,
		const std::wstring& s226 ) const
	{
		return false;
	};
};

typedef s1::s3<s209> PVal;
enum s453 { s454, s455, s456 };
enum s246 { s247, s248, s249 };

class s208;

class s211
{
	typedef std::map<std::wstring, s209*> s250;
	s250 m;
	std::vector<std::wstring> v;
public:
	s211() { }

	void s272() { m.clear(); v.clear();  }
	void s182();
	void s251( const s208& st );
	void s252( s209* p );
	void s253( s209* p, const std::wstring& s254 );
	s209* s255( s160* s192, const s44::s55& val, const std::wstring& s254 );
	s209* s255( s160* s192, s161& s370, const std::wstring& s254 );
	s209* s255( s160* s192, size_t type, const std::wstring& s254 );
	s209* s255( s160* s192, const std::wstring& val, const std::wstring& s254 );
	s209* get( const std::wstring& nam, bool thr = true ) const;
	bool s67( const std::wstring& nam ) const;

	void s196( std::wostream* pd, int ind = 0 ) const;
};

class s256
								: public s1::s2
{
	std::vector<std::wstring> patterns;
	s246 pv;
public:
	s256() : pv( s247 ) { }
	s256( s246 pv, const std::vector<std::wstring>& s257 );
	s256( const std::wstring& ag, const std::wstring& sf );
	s246 s258( const std::wstring& s220 ) const;

	static std::vector<std::wstring> s259;
};

class s260
								: public s1::s2
{
	typedef std::map<std::wstring, s256*> s261;
	s261 acls;
public:
	s260( ) { }
	void s262( s246 pv, s161* );
	void s263( const std::wstring& s, s256& pl );
	void s264( const std::wstring& s, const std::wstring& s386 );
	s246 s265( const std::wstring& mem, const std::wstring& s220 );
	void s266( const std::wstring& s226,
		std::vector<std::wstring>& res );
};

class s208
{
public:
	enum s59 { s60, s267, s61, s62 };
private:
	typedef std::map<std::wstring, s209*> s268;
	s268 s408;
	s453 s460;

	s260* s269;
	bool s270( const std::wstring& nam, s59 ap = s60 );
public:
	s208( ): s460( s455 ), s269( NULL ) {}
	s208( s453 am ) : s460( am ), s269( NULL ) {}
	s208( const s208& s464 );
	void s221( const std::wstring& s220, bool s271 = true );
	void s272();
	void s273( const std::wstring& nam, s209* s409, s59 ap = s60 );
	void s273( const std::wstring& nam, s44::s56 val, s59 ap = s60 );
	void s274( const std::wstring& nam );
	void s275( const s44::s57& obj, s59 ap = s60 );
	void s181( const s208& t, s59 ap = s60 );
	bool s67( const std::wstring& nam ) const;
	s209* get( const std::wstring& nam, bool thr = true ) const;
	void s276( std::vector<std::wstring>& res ) const;
	void s277( std::vector<std::wstring>& res ) const;
	void s278( std::vector<std::wstring>& res ) const;
	void s279( const s208& t, std::vector<std::wstring>& res ) const;
	void copy( s208& t, s164* s429, s164* s352, s59 ap = s60 ) const;
	void s280( s208& t ) const;
	void s281( s246 pv, s161* block );
	void s266( const std::wstring& s226,
		std::vector<std::wstring>& res );
	bool s283( const std::wstring& s170, const std::wstring& s226 ) const;

	void s196( std::wostream* pd, int ind = 0 ) const;
};

class s284
{
	typedef std::map<std::wstring, s209*> s268;
	s268 s408;
	std::vector<std::wstring> s474;
public:
	s284();
	void s285( const std::wstring& s );
	void s221( s160* s192, const std::wstring& s418 );
	void s482( const std::wstring& nam, s160* s192, const std::wstring& s418 );
	bool s240( const std::wstring& s409, s228* ref );
	void copy( s284& t ) const;

};

extern s1::s3<s260> s286;
class s287;
class s160;
typedef void ( *s292 )( s209** s166, size_t n );

class s288
							: public s163
{
	std::wstring str;
	std::wstring s226;

public:
	s288( s160* s192, const std::wstring& s, const std::wstring& s289 )
		: s163( s192, s203 ), str( s ), s226( s289 ) { }
	s288( const s288& right );
	const std::wstring& Str() const { return str; }
	const std::wstring& s471() const { return s226; }
	virtual s163* s224() const override;

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};

class s291
								: public s209
{
protected:
	s292 s293;

	struct s294

	{
		std::wstring s170;
		size_t s295;
		s292 s412;
		s294( const std::wstring& s296, s292 fp, size_t type_ )
			: s170( s296 ), s295( type_ ), s412( fp )	{}
		s294()
			: s412( NULL )	{}
	};
	typedef std::map<std::wstring, s294*> s297;
	virtual const s297& s298() const = 0;
public:
	s291( s160* s192 ) : s209( s192, s200 ) {}
	virtual size_t s233( const std::wstring& s234 ) const override;
	s292 s299( const std::wstring& s234 )const;
	virtual const s209* s223() const override;
	virtual void* addr() = 0;
	virtual s209* s217( s209** s166, size_t s218 ) override;
	static s209* s301( s160* s192, const std::wstring& val, const std::wstring& s226 );
};

class s302;

class s302
						: public s291
{
	static size_t type;

	static const std::wstring s407;
	static s297 s411;
	int val;

	static void set( s209** s166, size_t n );
	static void sum( s209** s166, size_t n );
	static void dif( s209** s166, size_t n );
	static void mul( s209** s166, size_t n );
	static void div( s209** s166, size_t n );
	static void pow( s209** s166, size_t n );
	static void sumeq( s209** s166, size_t n );
	static void difeq( s209** s166, size_t n );
	static void muleq( s209** s166, size_t n );
	static void diveq( s209** s166, size_t n );
	static void poweq( s209** s166, size_t n );
	static void eq( s209** s166, size_t n );
	static void less( s209** s166, size_t n );
	static void greater( s209** s166, size_t n );
	static void leq( s209** s166, size_t n );
	static void geq( s209** s166, size_t n );
	static void neq( s209** s166, size_t n );
	static void abs( s209** s166, size_t n );
	static void mod( s209** s166, size_t n );
	static void sqrt( s209** s166, size_t n );
	static void nroot( s209** s166, size_t n );
	static void toDouble( s209** s166, size_t n );

	virtual void s232() override;
	virtual const s297& s298() const override { return s411; }
	virtual void s235( size_t type ) override;

public:
	s302( const s302& );
	s302( s160* s192, int i );
	s302( s160* s192, const std::wstring& s, size_t& pos );

	static size_t s303() { return type; }

	virtual const std::wstring& s236() const override { return s407; }

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) override;
	virtual s209* s237() const override;

	virtual size_t s219() const override;


	virtual void s221( const std::wstring& s226 ) override;	
	virtual s209* s224() const override;
	virtual void s238( s210* p ) const override;

	int* Ptr() { return &val; }
	virtual void* addr() override { return (void*)&val; }
	virtual operator bool() const { return val != 0; }
	virtual operator int() const { return val; }
	virtual operator double() const { return (double)val; }
	virtual std::wstring to_wstring() const { return std::to_wstring( val ); }

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};

class s304
								: public s291
{
	static size_t type;

	static const std::wstring s407;
	static s297 s411;
	double val;

	static void set( s209** s166, size_t n );
	static void sum( s209** s166, size_t n );
	static void dif( s209** s166, size_t n );
	static void mul( s209** s166, size_t n );
	static void div( s209** s166, size_t n );
	static void pow( s209** s166, size_t n );
	static void sumeq( s209** s166, size_t n );
	static void difeq( s209** s166, size_t n );
	static void muleq( s209** s166, size_t n );
	static void diveq( s209** s166, size_t n );
	static void poweq( s209** s166, size_t n );
	static void eq( s209** s166, size_t n );
	static void less( s209** s166, size_t n );
	static void greater( s209** s166, size_t n );
	static void leq( s209** s166, size_t n );
	static void geq( s209** s166, size_t n );
	static void neq( s209** s166, size_t n );
	static void dcmp( s209** s166, size_t n );
	static void dcmpr( s209** s166, size_t n );
	static void abs( s209** s166, size_t n );
	static void sqrt( s209** s166, size_t n );
	static void nroot( s209** s166, size_t n );
	static void toInt( s209** s166, size_t n );

	virtual void s232() override;
	virtual const s297& s298() const override { return s411; }
	virtual void s235( size_t type ) override;

public:
	s304( const s304& r );
	s304( s160* s192, double d );
	s304( s160* s192, const std::wstring& s, size_t& pos );

	static size_t s303() { return type; }
	virtual const std::wstring& s236() const override { return s407; }

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) override;
	virtual s209* s237() const override;

	virtual size_t s219() const;
	virtual void s221( const std::wstring& s226 ) override;

	virtual s209* s224() const override;
	virtual void s238( s210* p ) const override;

	double* Ptr() { return &val; }
	virtual void* addr() override { return (void*)&val; }
	virtual operator bool() const { return val != 0.0; }
	virtual operator int() const { return (int)val; }
	virtual operator double() const { return val; }
	virtual std::wstring to_wstring() const;

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};

class s305;

class s305
								: public s291
{
	static size_t type;

	static const std::wstring s407;
	static s297 s411;
	std::wstring val;

	static void set( s209** s166, size_t n );
	static void sum( s209** s166, size_t n );
	static void eq( s209** s166, size_t n );
	static void less( s209** s166, size_t n );
	static void greater( s209** s166, size_t n );
	static void leq( s209** s166, size_t n );
	static void geq( s209** s166, size_t n );
	static void neq( s209** s166, size_t n );

	virtual void s232() override;
	virtual const s297& s298() const override { return s411; }
	virtual void s235( size_t type ) override;

public:
	s305( const s305& );
	s305( s160* s192, const std::wstring& s = std::wstring( L"" ) );
	s305( s160* s192, const std::wstring& s, size_t& pos );

	static size_t s303() { return type; }
	virtual const std::wstring& s236() const override { return s407; }

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) override;
	virtual s209* s237() const override;

	virtual size_t s219() const;

	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s224() const override;
	virtual void s238( s210* p ) const override;

	std::wstring* Ptr() { return &val; }
	virtual void* addr() override { return (void*)&val; }
	virtual operator bool() const { return !val.empty(); }
	virtual operator int() const { return std::stoi( val ); }
	virtual operator double() const { return std::stod(val); }
	virtual std::wstring to_wstring() const { return val; }

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};

class s306
							: public s291
{
	static size_t type;

	static const std::wstring s407;
	static s297 s411;
	virtual void s232() override {}
	virtual const s297& s298() const override { return s411; }
	virtual void s235( size_t type ) override;
public:
	s306( s160* s192 ) : s291( s192 ) { s214 = s306::s303(); }
	static size_t s303() { return type; }

	virtual const std::wstring& s236() const override { return s407; }

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) override;
	virtual s209* s237() const override;

	virtual size_t s219() const;
	virtual void* addr() override { return (void*)0; }

	virtual void s238( s210* p ) const override { }
	virtual void s221( const std::wstring& s226 ) override;
	virtual operator bool() const { return false; }

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};
extern s306 nullobject;

class s307
						: public s291
{
	static size_t type;
	static const std::wstring s407;
	static s297 s411;
	size_t s472;
	std::vector<s163*> val;
	std::wstring s220;

	static void set( s209** s166, size_t n );
	static void get( s209** s166, size_t n );
	static void add( s209** s166, size_t n );
	static void size( s209** s166, size_t n );
	static void resize( s209** s166, size_t n );
	static void eq( s209** s166, size_t n );

	virtual void s232() override;
	virtual const s297& s298() const override { return s411; }
	virtual void s235( size_t type ) override;

public:
	s307( s160* s192, const std::wstring& sf );
	s307( const s307& right );
	s307( s160* s192, const std::wstring& s, size_t& pos );

	static size_t s303() { return type; }
	virtual const std::wstring& s236() const override { return s407; }
	virtual size_t s215() const override;

	virtual s209* s230( const std::wstring& val, const std::wstring& s226 ) override;
	virtual s209* s237() const override;

	virtual size_t s219() const override;
	size_t s310() const { return s472; }
	virtual bool isTypeOf( const s209* classObj ) const override;
	virtual void* addr() override { return (void*)&val; }

	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s224() const override;
	virtual void s238( s210* p ) const override;

	std::vector<s163*>& Ref() { return val; }

	virtual std::wstring to_wstring() const;

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;

};

typedef s302 TDInt;
typedef s304 TDDouble;
typedef s305 TDString;
typedef s307 TDVector;

class s228
						: public s163
{
	std::wstring s229;
	s209* s311;
	const s209* s312;
	std::vector<size_t> s313;
	size_t s314;
public:
	s228( const std::wstring& s, s160* s192 ) : s210( s192, s201 ), s229( s )/*, off(NULL)*/ { }
	s228( const s228& right );

	virtual bool isTypeOf( const s209* classObj ) const override;

	virtual s209* s216() override;
	virtual const s209* s223() const override { return s312; }
	const s209* Root() { return s311; }

	const std::wstring& ValName() const { return s229; }

	virtual s209* s217( s209** s166, size_t s218 ) override;

	s209* s315( s164* ob );
	s209* s315( s209** s316 );
	s209* s318( const s164* ob ) const;
	s209* s319( s164* ob );
	void s317( size_t off, const s209* s473 );
	size_t s321() const { return s314; }
	virtual s163* s224() const override;

	void s221( const s164* s352, const std::wstring& s220 );
	void s322( s209* p ) { s311 = p; }
	void s323( s209* p ) { s312 = p; }

	virtual void s196( std::wostream* pd, int ind = 0 ) const override;
};
class s324;
class s164;
typedef s1::s3<s164> PObject;
typedef std::vector<std::pair<std::wstring, std::wstring>> s477;
typedef std::map<std::wstring, s164*> s476;
typedef std::map<std::wstring, s161*> s478;

class s164
						: public s209
{
protected:
	const s164* s325;
	const s164* s508;
	s164* ns;
	size_t type;
	const std::wstring& s407;
	const std::wstring s170;
	std::wstring s481;

	s208 s326;
	s284* s327;
	std::vector<s210*> s328;
	std::vector<std::wstring> s420;


	s324* s331;

	virtual void s232() override { }
	virtual void s235( size_t type ) override;
public:

	s164( const s164& s419 );
	s164( s160* s192, size_t type_, s198 pc/* = s199*/ );
	s164( const std::wstring& s170, s160* s192, s198 pc );
	s164( const std::wstring& s407, const std::wstring& s170, s160* s192, s208& s330,
		const s208& s326 );
	s164( s161& s370, s160* s192, s198 pc, s164* ns, s453 am, 
		s476& cl, s477& cnl, s478& al );
	const std::wstring& s191() const { return s170; }
	std::wstring s190() const;

	static s163* s475( const s44::s57& obj, const std::wstring& s170, s160* s192 );
	static s163* s475( std::multimap<std::wstring, s210*>& v, s210* s352 );
	s209* s422( s161& s370, const std::wstring& s226 );
	s209* s422( const s44::s55& val );

	virtual s209* s237() const override;
	size_t s303() { return type; }
	virtual size_t s233( const std::wstring& s234 ) const;
	virtual bool isTypeOf( const s209* classObj ) const override;

	virtual s209* s230( s161& s370, const std::wstring& s254 );
	virtual s209* s230( const std::wstring& val, const std::wstring& s254 ) override;


	virtual size_t s219() const override;
	virtual const std::wstring& s236() const override { return s407; }
	virtual const s209* s223() const override { return s325; }
	const s164* s479() const { return s508; }
	const std::wstring& s480() const { return s481; }
	virtual s209* s217( s209** s166, size_t s218 );
	s324* s299( const std::wstring& s170, const std::wstring& s226,
		bool thr = true ) const;
	void s423( s161& s370 );
	void s482( const std::wstring& nam, const std::wstring& s418 );
	void s483( s161& s370 );
	void s424( const std::wstring& s226,	std::vector<std::wstring>& res );

	virtual bool s240( const std::wstring& s170, s228* res,
		const std::wstring& s226 ) const override;
	size_t s333( const std::wstring& s170 ) const;
	s209* s334( const std::wstring& s170, const std::wstring& s226 );
	virtual s163* s335( size_t off );
	s163* s336( const std::wstring& s170, const std::wstring& s226,
		bool thr=true ) const;
	bool s337( const std::wstring& s409, const std::wstring& s220 ) const;
	bool s265( const std::wstring& s409 );


	virtual void s221( const std::wstring& s220 ) override;	
	void s484( const s208& s166 ); 
	void s65( s161& s370 );
	virtual s163* s224() const  override;
	virtual void s238( s210* p ) const override;
	void s485( s164* desc ) const;

	virtual std::wstring to_wstring() const override;

	virtual void s196( std::wostream* pd, int ind = 0 ) const;
};
class s324;
class s160;
typedef s324 TD;
class s291;
class s426;

typedef s324 Transd;

class s324
								: public s164
{
protected:
	std::wstring s170;

	s292 s338;
	enum s339 { s340, s341, s342, s343, s344, s345 };
	enum s486 { s487, s488, s489, s490 };
	s339 s346;
	s486 virtType;

	s209** s347;
	s210** s348;
	size_t s218, s462;

	s208 s349;
	std::vector<s209*> s492;
	std::vector<s210*> s166;
	std::vector<s209*> s350;
	std::vector<s210*> s351;
	std::vector<std::vector<s210*>> s491;
	s209* s447;
	s164* s352;
	s164* s429;
	virtual void s235( size_t type ) override { }
	void s493(const std::wstring& s226);
	void s494(const std::wstring& s226);


public:
	s324( s160* s192, s164* s441, s164* s442, s339 ct, 
							const std::wstring& s296 )
		: s164( s192, 0, s202 ), s447( NULL ), s170( s296 ),
		s429( s441 ), s352( s442 ), s338( NULL ), s346( ct ) { }
	s324( const s324& right, s164* s429, s164* s352,
		const std::vector<s210*>& s166 );
	s324( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s324( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l,
		s292 s338, size_t s214 );
	virtual ~s324();
	void s497( s486 vt ) { virtType = vt; }
	s486 s498() const { return virtType; }
	virtual const std::wstring& s191() const { return s170; }
	virtual s209* s216() override { return s447; }
	virtual void s221( const std::wstring& s226 ) override;
	void s495( const std::vector<s210*>& l );
	void s496( const std::wstring& s226 );
	virtual bool s240( const std::wstring& s170, s228* ref,
		const std::wstring& s226 ) const override;
	virtual s163* s335( size_t off ) override;
	virtual s209* s217( s209** s166 = NULL, size_t s218 = 0 ) override;
	virtual s163* s224() const override;
	static Transd* s354( s161& s370, s160* s192, s164* obj,
		const std::wstring& s170, const std::wstring& s418 );
	static s426* s355( s161& s370, s160* s192, s164* obj, const std::wstring& s418 );
	static Transd* s356( s426* cs, s160* s192, s164* s429, 
		s164* s430, const std::wstring& s418 );

	virtual void s196( std::wostream* pd, int ind = 0 ) const override { }
};

class s426
							: public s163
{
	const std::wstring s357;
	std::vector<s210*> s166;

	s161* s467;

public:
	s426( s160* s466, s161* s465 )
		: s163( s466, s204 ), s467( s465 )
	{
	}
	s426( const std::wstring& s463, const std::vector<s210*>& l );
	s426( const s426& s464 );

	const std::wstring& s191() const { return s357; }
	std::vector<s210*>& s358() { return s166; }
	s161* s359() { return s467; }
	virtual void s221( const std::wstring& s220 ) override;
	virtual s163* s224() const override;
	virtual void s196( std::wostream* pd, int ind = 0 ) const override { }
};

class s499
								: public s324
{
	std::vector<size_t> types;
	std::vector<s324*> ptrs;
public:
	s499( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	void s500( size_t type, s324* pOvr );
	virtual s209* s217( s209** s166, size_t s218 ) override;
};


class s360
						: public s324
{
public:
	s360( s160* s192, s164* s441, s164* s442, const std::vector<s210*>& l );
	virtual const std::wstring& s191() const override { return s137; }
	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s217( s209** s166, size_t s218 ) override;

	s163* s445( const std::wstring& s170, s228* ref,
		const std::wstring& s226 ) const;
	virtual s209* s224() const override;

};

class s362
					: public s324
{
public:
	s362( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s362( s160* s192 );
	virtual const std::wstring& s191() const override { return s148; }
	virtual void s221( const std::wstring& s226 ) override { }
	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;

};

class s363
					: public s324
{
public:
	s363( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s363( s160* s192 );
	virtual const std::wstring& s191() const override { return s147; }

	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;

};

class s364
					: public s324
{
public:
	s364( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s364( s160* s192 );
	virtual const std::wstring& s191() const override { return s134; }
	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;

};

class s365
							: public s324
{
public:
	s365( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s365( s160* s192 );
	virtual const std::wstring& s191() const override { return s155; }
	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;
};

class s366
						: public s324
{
	s324* condition;
	s324* step;
public:
	s366( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s366( s160* s192 );
	virtual const std::wstring& s191() const override { return s158; }
	virtual void s221( const std::wstring& s226 ) override;
	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;

};

class s367
						: public s324
{
public:
	s367( s160* s192, s164* s429, s164* s352, const std::vector<s210*>& l );
	s367( s160* s192 );
	virtual const std::wstring& s191() const override { return s155; }

	virtual s209* s217( s209** s166, size_t s218 ) override;
	virtual s209* s224() const override;
};
extern std::wstring s368;
typedef int HPROG;

class s426;

class s160
							: public s164
{
	std::vector<std::wstring> s369;
	s161 s370;
	std::wstring s371;

	void s373( const std::wstring& s170 );
	void s374( const s44::s57& obj );

	s211 s449;
	s208 s468;
	s208 s469;

public:
	s160();
	~s160();
	void s221();
	void s272();
	void s501( s161& _ast );
	void s502( const std::wstring& s385 );
	void s503( const std::wstring& s385 );
	void s504( s44::s57& obj );
	void s505( const std::wstring& s385 );
	s209* run();
	s209* callFunc( const std::wstring& func, std::vector<std::wstring>& l );

	s324* s377( const std::wstring& s357, std::vector<s210*>& s166, s164* s429, s164* s430 );
	s163* s378( const std::wstring& val, const std::wstring& s226 );
	s209* s379( size_t type, const std::wstring& s226 );
	s209* s379( const std::wstring& val, const std::wstring& s226 );
	s209* s379( s161& s370, const std::wstring& s226 );
	s209* s379( const s288& ds );
	void s380( const std::wstring& s );
	void s252( s209* p );
	void s382( const std::wstring& val, const std::wstring& s226,
		std::vector<std::wstring>& res );
	s209* s383( const std::wstring& val, const std::wstring& s226 );
	s163* s384( const std::wstring& s409, const std::wstring& s220,
		bool thr = true );
	void* getExportVariable( const std::wstring& s170 );

};
void evaluateExpression( const std::wstring& sf );
HPROG createAssembly();
void loadProgram( HPROG handle, const std::wstring& s394 );
void s504( HPROG handle, s44::s57& obj );
s209* run( HPROG handle );
void* callFunc( HPROG handle, const std::wstring& sf, std::vector<std::wstring>& l );
void* getExportVariable( HPROG handle, const std::wstring& s170 );
void* execute( s163* func );
void importSymbol( HPROG handle, const std::wstring& modName, const std::wstring& symName,
										const std::wstring& s226 );
void importFile( HPROG handle, const std::wstring& modName, const std::wstring& s388,
	const std::wstring& s226 );
HPROG initShell( const std::wstring& modName, const std::wstring& modText );


typedef s4::s5 TDException;
} // namespace transd
