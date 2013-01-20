#ifndef _CMEMORY_H_
#define _CMEMORY_H_

#include <Windows.h>
#include <string>
#include <TlHelp32.h>

class CMemory {
public:
	CMemory();
	~CMemory();

	bool Initialize();
	DWORD GetProcessIDFromName(const char* ProcessName);
	DWORD GetProcessBaseAddress(DWORD ProcessId);
	bool EnablePriv();

	template<class T>
	T Read(unsigned int addr) {
		T ret;
		
		ReadProcessMemory(hProcess, (LPCVOID)addr, &ret, sizeof(ret), 0);

		return ret;
	};

	std::string ReadString(unsigned int addr);
	
	char szProcessName[100];
	HANDLE hProcess;
	DWORD dwBaseAddress;
	DWORD dwProcessID;

private:
};

#endif