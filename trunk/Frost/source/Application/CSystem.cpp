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

#include "CSystem.h"

bool CSystem::Initialize() {
	InitializeWindows();

	m_Application = new CApplication;
	if(!m_Application)
		return false;

	if(!m_Application->Initialize())
		return false;

	return true;
}

void CSystem::Shutdown() {
	if(m_Application) {
		m_Application->Shutdown();
		delete m_Application;
		m_Application = 0;
	}

	ShutdownWindows();

	done = true;

	return;
}

void CSystem::Run() {
	MSG msg;
	done = false;

	ZeroMemory(&msg, sizeof(MSG));

	while(GetMessage(&msg, NULL, 0, 0) > 0 && !done) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return;
}

LRESULT CALLBACK CSystem::msgRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_INITDIALOG:
			SetTimer(hWnd, WM_OBJECTMANAGER_PULSE, 1000, NULL);
			break;
		case WM_TIMER:
			switch(wParam) {
				case WM_OBJECTMANAGER_PULSE:
					{
						m_Application->ObjectManager->Pulse();
						
						char level[64] = {0};

						sprintf_s(level, "%d", m_Application->ObjectManager->GetLocalPlayer()->Level());
						
						SetWindowText(GetDlgItem(m_hwnd, IDC_PLAYERLEVEL), level);
						
						char health[64] = {0};

						sprintf_s(health, "%d / %d (%d%%)", m_Application->ObjectManager->GetLocalPlayer()->Health(),
							m_Application->ObjectManager->GetLocalPlayer()->MaxHealth(),
							(m_Application->ObjectManager->GetLocalPlayer()->Health() / m_Application->ObjectManager->GetLocalPlayer()->MaxHealth()) * 100);
						
						SetWindowText(GetDlgItem(m_hwnd, IDC_PLAYERHEALTH), health);

						char power[64] = {0};

						sprintf_s(power, "%d / %d (%d%%)", m_Application->ObjectManager->GetLocalPlayer()->Power(),
							m_Application->ObjectManager->GetLocalPlayer()->MaxPower(),
							(m_Application->ObjectManager->GetLocalPlayer()->Power() / m_Application->ObjectManager->GetLocalPlayer()->MaxPower()) * 100);

						SetWindowText(GetDlgItem(m_hwnd, IDC_PLAYERPOWER), power);
					}
					break;
			}
			break;
		case WM_DESTROY: case WM_QUIT: case WM_CLOSE:
			KillTimer(hWnd, WM_OBJECTMANAGER_PULSE);
			Shutdown();
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

void CSystem::InitializeWindows() {
	ApplicationHandle = this;

	m_hInstance = GetModuleHandle(NULL);

	m_hwnd = CreateDialog(m_hInstance, (LPCSTR)IDD_FROST, NULL, (DLGPROC)WndProc);

	ShowWindow(m_hwnd, SW_SHOW);

	return;
}

void CSystem::ShutdownWindows() {
	DestroyWindow(m_hwnd);
	m_hwnd = 0;

	m_hInstance = NULL;

	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return ApplicationHandle->msgRouter(hWnd, msg, wParam, lParam);
}