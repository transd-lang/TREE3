/*
Copyright (c) 2020 Albert Berger

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may view the text of the License in the 'LICENSE' file
shipped with the distribution of FREND shell.

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <algorithm>


#ifdef WIN32
#include <io.h>
#include <fcntl.h>
#endif
#include <iostream>
#include <regex>

#include "transd.hpp"


using namespace std;
using namespace transd;


wstring exprPrompt = L"D : ";
wstring shellModuleName = L"_frend__";
wstring shellCallSite = L"_callSite";
HPROG prog = 0;

wstring version = L"0.1";
wstring buildnum = L"102";
wstring copyright = L"FREND: shell for TransD programming language.\n\nCopyright (c) 2020 Albert Berger."
"\nVersion: " + version + L"." + buildnum;

#define CMD_RUNFILE 1

wstring whitespace = L"\n\r\t ";


wstring clearAll( const std::wstring& s, const std::wstring& c )
{
	size_t pl = s.find_first_not_of( c );
	if( pl == wstring::npos )
		return L"";
	wstring ret = s.substr( pl );
	return ret.substr( 0, ret.find_last_not_of( c ) + 1 );
}

wstring getStringVal_( const wstring& prompt, bool endLn = false )
{
	wcout << prompt; 
	if( endLn ) wcout << endl;
	wstring val;

	getline( wcin, val );

	//wcout << endl;
	return val;
}

void showFrendInfo()
{
	wcout << copyright << endl;
}

void findPairedBlock( const wstring& s, size_t startFrom, wchar_t c, size_t& start, size_t& end )
{
	end = string::npos;
	start = s.find( c, startFrom );
	if( start == string::npos || start == s.size() - 1 )
		return;
	bool backslash = false;
	for( size_t n = start + 1; n < s.size(); ++n ) {
		if( s[n] == L'\\' )
			backslash = !backslash;
		else
			backslash = false;
		if( s[n] == c && !backslash ) {
			end = n;
			return;
		}
	}
}

void parseArgs( const wstring& sf, vector<wstring>& res )
{
	size_t stPos = sf.find_first_not_of( whitespace );
	size_t _frStart, _frEnd;
	while( stPos != string::npos ) {
		wchar_t c = sf[stPos];
		wstring arg;
		if( c == L'\"' || c == L'\'' ) {
			findPairedBlock( sf, stPos, c, _frStart, _frEnd );
			if( _frEnd == string::npos )
				throw TDException( L"Quotes don't match near \'" + sf.substr( stPos, 40 ) + L"...\'" );
			arg = sf.substr( stPos, _frEnd - stPos + 1 );
			stPos = sf.find_first_not_of( whitespace, _frEnd );
		}
		else {
			_frEnd = sf.find_first_of( whitespace );
			arg = sf.substr( stPos, _frEnd - stPos );
			stPos = _frEnd;
		}

		res.push_back( arg );
	}
}

struct OPTIONS
{
	uint32_t cmd;
	wstring fileToRun;
	bool exit;
}opts;

void parseArgs( int argc, KCHAR* argv[] )
{
	opts.exit = false;
	if( argc == 1 )
		return;

	if( argc == 2 ) {
		wstring arg = FROMTERM( argv[1] );
		if( arg[0] != L'-' ) {
			opts.cmd = CMD_RUNFILE;
			opts.fileToRun = arg;
			opts.exit = true;
		}
		else if( arg == L"-version" ) {
			showFrendInfo();
			opts.exit = true;
		}
		return;
	}

	for( int i = 1; i < argc; ++i ) {
		wstring arg = FROMTERM( argv[i] );
		if( arg == L"-version" )
			showFrendInfo();
		else
			throw TDException( L"unknown command line argument: " + arg );
	}
}

void importFile( const wstring& fpath )
{
	transd::importFile( prog, shellModuleName, fpath, shellModuleName );
}

void runFile( const wstring& args_ )
{
	vector<wstring> args;
	parseArgs( args_, args );
	if( args.empty() )
		return;
	try {
		HPROG prog = createAssembly();
		loadProgram( prog, args[0] );
		transd::run( prog, args );
	}
	catch( TDException& e ) {
		wcout << L"TDException has occured: \n\n" << e.Msg() << endl;
	}
	catch( std::exception& e ) {
		wcout << L"std::exception has occured: \n\n" << U16( e.what() ) << endl;
	}
}

void runCommand( const wstring& cmd_ )
{
	if( cmd_[0] != L'(' || cmd_[cmd_.size() - 1] != L')' ) {
		wcout << L"Error: unknown command syntax.";
		return;
	}
	wstring cmd = L"(textout " + cmd_ + L")";
	vector<wstring> pars;
	pars.push_back( cmd );
	transd::callFunc( prog, shellModuleName + L"::" + shellCallSite, pars );
	wcout << endl;
}

#ifdef _WIN32
int wmain( int argc, wchar_t* argv[] )
#else
int main( int argc, char* argv[] )
#endif
{
#ifdef WIN32
	_setmode( _fileno( stdout ), _O_U16TEXT );
	_setmode( _fileno( stdin ), _O_U16TEXT );
#endif

	parseArgs( argc, argv );
	if( opts.cmd == CMD_RUNFILE )
		runFile( clearAll( opts.fileToRun, L" " ) );

	if( opts.exit )
		return 0;

	try {
		wstring modtxt = L"{ " + shellCallSite + L": (lambda f Null() (eval f)) }";
		prog = transd::initShell( shellModuleName, modtxt );

		while( true ) {
			wstring sf = getStringVal_( exprPrompt );

			if( sf[0] == L'(' )
				runCommand( sf );
			else if( sf.find( L"import" ) == 0 )
				importFile( clearAll( sf.substr( 7 ), L" " ) );
			else if( sf.find( L"run " ) == 0 )
				runFile( clearAll( sf.substr( 4 ), L" " ) );
			else if( sf == L"q" )
				break;
			else
				evaluateExpression( sf );
			//wcout << res->to_wstring() << endl << endl;
		}
	}
	catch( TDException& e ) {
		wcout << L"kException was intercepted in main function: \n\n" << e.Msg() << endl;
	}
	catch( std::exception& e ) {
		wcout << L"std::exception was intercepted in main function: \n\n" << U16( e.what() ) << endl;
	}

	return 0;

}
