#include "CMemory.h"

CMemory::CMemory() {
	hProcess = NULL;
	dwProcessID = 0;
	dwBaseAddress = 0;
	ZeroMemory(&szProcessName, sizeof(szProcessName));
	memcpy(&szProcessName, "Wow.exe", 10);
}

CMemory::~CMemory() { 

}

bool CMemory::Initialize() {
	if(!EnablePriv()) {
		return false;
	}

	dwProcessID = GetProcessIDFromName(szProcessName);

	if(dwProcessID == 0) {
		return false;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcessID);

	if(hProcess == NULL) {
		return false;
	}

	dwBaseAddress = GetProcessBaseAddress(dwProcessID);

	if(dwBaseAddress == 0) {
		return false;
	}

	return true;
}

DWORD CMemory::GetProcessIDFromName(const char* ProcessName) {
	HANDLE hSnapshot;
	PROCESSENTRY32 pe32;

	pe32.dwSize = sizeof(PROCESSENTRY32);

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(Process32First(hSnapshot, &pe32) != TRUE)
		return 0;

	do {
		if(strcmp(pe32.szExeFile, szProcessName) == 0)
			return pe32.th32ProcessID;
	} while(Process32Next(hSnapshot, &pe32) != FALSE);

	CloseHandle(hSnapshot);

	return 0;
}

DWORD CMemory::GetProcessBaseAddress(DWORD dwProcessId) {
	HANDLE hSnapshot;
	MODULEENTRY32 me32;

	me32.dwSize = sizeof(MODULEENTRY32);

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);

	if(Module32First(hSnapshot, &me32) != TRUE)
		return 0;

	do {
		if(strcmp(me32.szModule, "WoW.exe") == 0 || strcmp(me32.szModule, "Wow.exe") == 0)
			return (DWORD)me32.modBaseAddr;
	} while(Module32Next(hSnapshot, &me32) != FALSE);

	CloseHandle(hSnapshot);

	return 0;
}

bool CMemory::EnablePriv() {
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	bool bRet = false;
	ZeroMemory(&tkprivs, sizeof(tkprivs));
	if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken)) return FALSE;
	if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)){ CloseHandle(hToken); return FALSE; }
	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if( AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL) )
		bRet = true;
	CloseHandle(hToken);
	return bRet;
}

std::string CMemory::ReadString(unsigned int addr) {
	std::string retstr; // Return string
	char ch; // buffer

	while(true) { // Loop until it hits escape character
		ReadProcessMemory(hProcess, (LPCVOID)addr, &ch, sizeof(ch), 0); // Read memory
		if(ch == 0) break; // If its an escape character, break
		retstr += ch; // Add it to the return string
		addr += sizeof(ch); // Increase address
	}

	return retstr; // Return
}