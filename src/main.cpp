/*
Copyright (c) 2020-2022 Albert Berger

This file is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may view the text of the License in the 'LICENSE' file
shipped with the distribution of TREE3 interpreter.

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


wstring exprPrompt = L"_) ";
wstring shellModuleName = L"_tree3__";
wstring shellCallSite = L"_callSite";
HPROG prog = 0;

wstring version = L"0.2";
// 221025
wstring buildnum = L"40";
wstring copyright = L"TREE3 (Transd Expression Evaluator, 3rd revision)\nVirtual compiler (interpreter) for Transd programming language."
"\n\nCopyright (c) 2020-2022 Albert Berger."
"\nVersion: " + version + L"." + buildnum + 
L"\n\nThe program uses Tourbillon virtual compiler as a back-end for Transd programming language."
"\nTourbillon compiler version: " + TRANSD_VERSION;

wstring usage = 
L"Usage: tree3 <PROGRAM_FILE_NAME> [ARGUMENTS] \n"
 "   or: tree3 <COMMAND> [ARGUMENTS] \n"
 "   or: tree3 <OPTION> \n"
 "   or: tree3\n\n"
 "The 1st form launches a Transd program with optional arguments.\n"
 "The 2nd form runs a command with optional arguments.\n"
 "The 3rd form starts TREE3 with an option.\n"
 "The 4th form starts an interactive REPL session.\n\n"
 "OPTIONS:\n"
 "   -h, -help:        show this info.\n"
 "   -v, -version:     show the version of TREE3.\n"
 "\n"
 "COMMANDS:\n"
 "   run <FILE_NAME>:  run a Transd program.\n"
;

#define CMD_NONE 0
#define CMD_RUNFILE 1

vector<wstring> hist;

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
	if( endLn ) wcout << endl;
	wstring val;

	val = consutils::getStringValHist( prompt, hist );
	hist.push_back( val );

	wcout << endl;
	return val;
}

void showTree3Info()
{
	wcout << copyright << endl;
}

void showUsage()
{
	wcout << usage << endl;
}

struct OPTIONS
{
	uint32_t cmd;
	wstring fileToRun;
	bool exit;
	vector<wstring> args;
}opts;

void parseArgs( int argc, KCHAR* argv[] )
{
	opts.exit = false;
	if( argc == 1 )
		return;

	opts.cmd = CMD_NONE;

	for( int i = 1; i < argc; ++i ) {
		wstring arg = FROMTERM( argv[i] );
		if( arg == L"-v" || arg == L"-version" ) {
			showTree3Info();
			opts.exit = true;
			return;
		}
		if( arg == L"-h" || arg == L"-help" ) {
			showUsage();
			opts.exit = true;
			return;
		}
		else if( arg == L"run" ) {
			if( opts.cmd != CMD_NONE )
				throw new TransdException( L"multiple commands in arguments" );
			opts.cmd = CMD_RUNFILE;
			opts.fileToRun = clearAll( FROMTERM( argv[++i] ), L" " );
			opts.args.push_back( opts.fileToRun );
			opts.exit = true;			
		}
		else {
			if( i == 1 ) {
				opts.cmd = CMD_RUNFILE;
				opts.fileToRun = clearAll( arg, L" " );
				opts.args.push_back( opts.fileToRun );
				opts.exit = true;			
			}
			else {
				if( arg == L"-args" )
					arg = FROMTERM( argv[++i] );
				opts.args.push_back( arg );
			}
		}
	}
}

void importFile( const wstring& fpath )
{
	transd::importFile( prog, shellModuleName, fpath, shellModuleName );
}

void runFile()
{
	try {
		HPROG prog = createAssembly();
		loadProgram( prog, opts.args[0] );
		transd::run( prog, opts.args );
		deleteAssembly( prog );
	}
	catch( TransdException* e ) {
		wcout << L"Exception was raised: \n\n" << e->Msg() << endl;
	}
	catch( std::exception& e ) {
		wcout << L"std::exception was raised: \n\n" << U16( e.what() ) << endl;
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
	try {
		transd::callFunc( prog, shellModuleName + L"::" + shellCallSite, pars );
		wcout << endl;
	}
	catch( TransdException* e ) {
		wcout << endl << e->Msg() << endl;
	}
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
	std::locale::global ( std::locale ( "" ) );
#else
	std::locale::global( std::locale( "en_US.UTF-8" ) );
#endif

	try {
		parseArgs( argc, argv );
	}
	catch( TransdException* e ) {
		wcout << "Error: " << e->Msg() << endl;
		return -1;
	}
	if( opts.cmd == CMD_RUNFILE )
		runFile( /*clearAll( opts.fileToRun, L" " )*/ );

	if( opts.exit )
		return 0;

	try {
		wstring modtxt = L"{ " + shellCallSite + L": (lambda f Null() (eval \"f\")) }";
		prog = transd::initShell( shellModuleName, modtxt );

		while( true ) {
			wstring sf = getStringVal_( exprPrompt );

			if( sf[0] == L'(' )
				runCommand( sf );
			else if( sf.find( L"import" ) == 0 )
				importFile( clearAll( sf.substr( 7 ), L" " ) );
			else if( sf.find( L"run " ) == 0 ) {
				opts.args.push_back( clearAll( sf.substr( 4 ), L" " ) );
				runFile();
			}
			else if( sf == L"q" )
				break;
			else 
				evaluateExpression( sf );
		}
	}
	catch( TransdException* e ) {
		wcout << L"Unhandled exception: \n\n" << e->Msg() << endl;
	}
	catch( std::exception& e ) {
		wcout << L"Unhandled std::exception: \n\n" << U16( e.what() ) << endl;
	}

	return 0;

}
