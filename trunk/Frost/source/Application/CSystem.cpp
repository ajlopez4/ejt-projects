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