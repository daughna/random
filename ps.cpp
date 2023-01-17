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

int main(){
	std::string cmd = "powershell -ExecutionPolicy Bypass -File C:\\Users\\client.LAB\\Desktop\\reg.ps1";
	DWORD procPid = reusableCreateProc((char *)cmd.c_str());
	std::cout << procPid;
}
