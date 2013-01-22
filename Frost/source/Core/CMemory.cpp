/*	Frost Open-Source World of Warcraft Bot
	Copyright (C) 2013 https://code.google.com/p/ejt-projects/

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <CMemory.h>

CMemory* Mem;

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

std::string CMemory::ReadString(unsigned int addr, int max) {
	std::string retstr; // Return string
	char ch; // buffer
	int result;

	while(true) { // Loop until it hits escape character or max
		result = ReadProcessMemory(hProcess, (LPCVOID)addr, &ch, sizeof(ch), 0); // Read memory
		if(result == 0) // Failed
			return "E";
		if(ch == 0 || (ch & 0xff) == 0xcc) break; // If its an escape character, break
		retstr += ch; // Add it to the return string
		addr += sizeof(ch); // Increase address
	}

	return retstr; // Return
}