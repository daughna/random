#include <stdio.h>
#include <iostream>
#include <Windows.h>


DWORD WINAPI reusableCreateProc(LPVOID lpParam){
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	if(!CreateProcess(NULL, (char *)lpParam, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
		printf("CreateProcess failed (%d).\n", GetLastError());
	}
	return pi.dwProcessId;
}

void killPid(DWORD pid){
	HANDLE explorer = OpenProcess(PROCESS_TERMINATE, false, pid);
	TerminateProcess(explorer, 1);
	CloseHandle(explorer);
}

HANDLE myGetHandle(DWORD pid){
	return OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
}

int main(int argc, char** argv){
	using namespace std;
	
	if(argc < 2){
		cout << "You must enter an input program";
		return 1;
	}
	
	DWORD notepadPid = reusableCreateProc(argv[1]);
	
	bool running = true;
	string in;
	while(running){
		cin >> in;
		if(in == "stop"){
			killPid(notepadPid);
			return 0;
		}
	}
	return 0;
}
