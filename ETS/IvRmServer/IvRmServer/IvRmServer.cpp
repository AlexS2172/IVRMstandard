// IvRmServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"

CServer* server = 0;

BOOL 
console_ctrl_handler(DWORD ctrl_id){
	if (server){
		delete server;
	};
	return FALSE;
};
 
int _tmain(int argc, _TCHAR* argv[]) {

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)console_ctrl_handler, TRUE);

	::CoInitializeEx(NULL, COINIT_MULTITHREADED);

	server = new CServer;
	server->Start();
	
	Sleep(INFINITE);
	
	::CoUninitialize();
	return 0;
}

