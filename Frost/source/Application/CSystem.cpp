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

#include <Application\CSystem.h>

CSystem::CSystem(const char* wndName, const char* className) : AbstractWindow() {
	_windowName = wndName;
	_className = className;
	_hInstance = GetModuleHandle(NULL);
	_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_x = _y = CW_USEDEFAULT;
	_height = _width = CW_USEDEFAULT;
	_styleEx = 0;
	_hwndParent = 0;
	_hMenu = 0;
}

bool CSystem::Initialize() {
	Mem = new CMemory;
	if(!Mem || !Mem->Initialize())
		return false;

	ObjectManager = new CObjectManager;
	if(!ObjectManager || !ObjectManager->Initialize())
		return false;

	ObjectManager->Pulse(); // Force pulse to get local player

	return true;
}

void CSystem::Shutdown() {
	if(Mem) {
		delete Mem;
		Mem = 0;
	}

	if(ObjectManager) {
		delete ObjectManager;
		ObjectManager = 0;
	}
}

void CSystem::Run() {
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CSystem::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE:
			{
				MainTab = new CTabControl;
				MainTab->Create(hwnd);
				MainTab->AddTab("General");
				MainTab->AddTab("Object Manager");

				/* GENERAL TAB */
				TextPlayerName = new CTextControl;
				TextPlayerName->Create(MainTab->Handle());
				TextPlayerName->Text("Player Name");
				MainTab->AddControl("General", TextPlayerName->Handle());

				TextPlayerHealth = new CTextControl;
				TextPlayerHealth->Create(MainTab->Handle());
				TextPlayerHealth->Text("Player Health");
				MainTab->AddControl("General", TextPlayerHealth->Handle());

				TextPlayerPower = new CTextControl;
				TextPlayerPower->Create(MainTab->Handle());
				TextPlayerPower->Text("Player Power");
				MainTab->AddControl("General", TextPlayerPower->Handle());

				TextPlayerLevel = new CTextControl;
				TextPlayerLevel->Create(MainTab->Handle());
				TextPlayerLevel->Text("Player Level");
				MainTab->AddControl("General", TextPlayerLevel->Handle());

				TextTargetName = new CTextControl;
				TextTargetName->Create(MainTab->Handle());
				TextTargetName->Text("Target Name");
				MainTab->AddControl("General", TextTargetName->Handle());

				TextTargetHealth = new CTextControl;
				TextTargetHealth->Create(MainTab->Handle());
				TextTargetHealth->Text("Target Health");
				MainTab->AddControl("General", TextTargetHealth->Handle());

				TextTargetPower = new CTextControl;
				TextTargetPower->Create(MainTab->Handle());
				TextTargetPower->Text("Target Power");
				MainTab->AddControl("General", TextTargetPower->Handle());

				TextTargetLevel = new CTextControl;
				TextTargetLevel->Create(MainTab->Handle());
				TextTargetLevel->Text("Target Level");
				MainTab->AddControl("General", TextTargetLevel->Handle());

				/* OBJECT MANAGER TAB */
				ObjectsTab = new CTabControl;
				ObjectsTab->Create(MainTab->Handle());
				ObjectsTab->AddTab("Players");
				ObjectsTab->AddTab("Units");
				ObjectsTab->AddTab("Objects");

				MainTab->AddControl("Object Manager", ObjectsTab->Handle());

				ListPlayers = new CListControl;
				ListPlayers->Create(ObjectsTab->Handle());
				ListPlayers->AddColumn("GUID", 100);
				ListPlayers->AddColumn("Name", 100);
				ListPlayers->AddColumn("Health", 150);
				ListPlayers->AddColumn("Power", 150);
				ListPlayers->AddColumn("Level", 100);

				ObjectsTab->AddControl("Players", ListPlayers->Handle());

				ListUnits = new CListControl;
				ListUnits->Create(ObjectsTab->Handle());
				ListUnits->AddColumn("GUID", 100);
				ListUnits->AddColumn("Name", 100);
				ListUnits->AddColumn("Health", 150);
				ListUnits->AddColumn("Power", 150);
				ListUnits->AddColumn("Level", 100);

				ObjectsTab->AddControl("Units", ListUnits->Handle());

				ListObjects = new CListControl;
				ListObjects->Create(ObjectsTab->Handle());
				ListObjects->AddColumn("GUID", 100);

				ObjectsTab->AddControl("Objects", ListObjects->Handle());

				MainTab->SwitchTab("General", -1);
				ObjectsTab->SwitchTab("Players", -1);

				SendMessage(hwnd, WM_SIZE, 0, 0); // Force resize

				SetTimer(hwnd, TIMER_UPDATE_INFO, 1000, (TIMERPROC)NULL);
			}
			break;
		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->code) {
				case TCN_SELCHANGING:
					return false;
					break;
				case TCN_SELCHANGE:
					{
						int page = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
						
						if(((LPNMHDR)lParam)->hwndFrom == MainTab->Handle())
							MainTab->SwitchTab("", page);
						else if(((LPNMHDR)lParam)->hwndFrom == ObjectsTab->Handle())
							ObjectsTab->SwitchTab("", page);
					}
					break;
			}
			break;
		case WM_TIMER:
			switch(wParam) {
				case TIMER_UPDATE_INFO:
					if(ObjectManager->GetLocalPlayer()->InGame()) {
						/* TESTING */
						ListPlayers->Clear();
						for each(WoWPlayer * player in ObjectManager->GetPlayers()) {
							if(player->Guid() != 0) {
								char guid[64] = {0};
								char name[64] = {0};
								char health[64] = {0};
								char power[64] = {0};
								char level[64] = {0};
								sprintf_s(guid, "0x%X", (player->Guid() & 0xFFFFFFFF));
								sprintf_s(name, "%s", player->Name().c_str());
								if(player->Dead()) {
									sprintf_s(health, "Dead");
									sprintf_s(power, "Dead");
								} else {
									sprintf_s(health, "%d/%d (%d%%)", player->Health(), player->MaxHealth(), player->HealthPercentage());
									sprintf_s(power, "%d/%d (%d%%)", player->Power(), player->MaxPower(), player->PowerPercentage());
								}
								sprintf_s(level, "%d", player->Level());
								LPSTR row[] = { guid, name, health, power, level };
								ListPlayers->AddRow(row);
							}
						}

						ListUnits->Clear();
						for each(WoWUnit * unit in ObjectManager->GetUnits()) {
							if(unit->Guid() != 0) {
								char guid[64] = {0};
								char name[64] = {0};
								char health[64] = {0};
								char power[64] = {0};
								char level[64] = {0};
								sprintf_s(guid, "0x%X", (unit->Guid() & 0xFFFFFFFF));
								sprintf_s(name, "%s", unit->Name().c_str());
								if(unit->Dead()) {
									sprintf_s(health, "Dead");
									sprintf_s(power, "Dead");
								} else {
									sprintf_s(health, "%d/%d (%d%%)", unit->Health(), unit->MaxHealth(), unit->HealthPercentage());
									sprintf_s(power, "%d/%d (%d%%)", unit->Power(), unit->MaxPower(), unit->PowerPercentage());
								}
								sprintf_s(level, "%d", unit->Level());
								LPSTR row[] = { guid, name, health, power, level };
								ListUnits->AddRow(row);
							}
						}
						/* END OF TESTING */
						
						TextPlayerName->Text("Name: %s", ObjectManager->GetLocalPlayer()->Name().c_str());
						TextPlayerHealth->Text("Health: %d/%d (%d%%)", ObjectManager->GetLocalPlayer()->Health(),
							ObjectManager->GetLocalPlayer()->MaxHealth(),
							ObjectManager->GetLocalPlayer()->HealthPercentage());
						TextPlayerPower->Text("%s: %d/%d (%d%%)", ObjectManager->GetLocalPlayer()->PowerType(),
							ObjectManager->GetLocalPlayer()->Power(),
							ObjectManager->GetLocalPlayer()->MaxPower(),
							ObjectManager->GetLocalPlayer()->PowerPercentage());
						TextPlayerLevel->Text("Level: %d", ObjectManager->GetLocalPlayer()->Level());

						if(ObjectManager->GetLocalPlayer()->Target().IsValid()) {
							TextTargetName->Text("Name: %s", ObjectManager->GetLocalPlayer()->Target().Name().c_str());
							TextTargetHealth->Text("Health: %d/%d (%d%%)", ObjectManager->GetLocalPlayer()->Target().Health(),
								ObjectManager->GetLocalPlayer()->Target().MaxHealth(),
								ObjectManager->GetLocalPlayer()->Target().HealthPercentage());
							TextTargetPower->Text("%s: %d/%d (%d%%)", ObjectManager->GetLocalPlayer()->Target().PowerType(),
								ObjectManager->GetLocalPlayer()->Target().Power(),
								ObjectManager->GetLocalPlayer()->Target().MaxPower(),
								ObjectManager->GetLocalPlayer()->Target().PowerPercentage());
							TextTargetLevel->Text("Level: %d", ObjectManager->GetLocalPlayer()->Target().Level());
						} else {
							TextTargetName->Text("N/A");
							TextTargetHealth->Text("N/A");
							TextTargetPower->Text("N/A");
							TextTargetLevel->Text("N/A");
						}
					}
					break;
			}
			break;
		case WM_SIZE:
			{
				RECT rcClient;
				RECT rcMain;
				GetClientRect(hwnd, &rcClient);
				GetClientRect(MainTab->Handle(), &rcMain);

				MainTab->SetSize(rcClient);

				rcClient.top += 28;
				rcClient.left += 5;
				rcClient.bottom = rcClient.bottom - rcClient.top - 5;
				rcClient.right = rcClient.right - rcClient.left - 5;

				ObjectsTab->SetSize(rcClient);

				rcClient.left -= 4;
				rcClient.top -= 4;
				rcClient.bottom = rcClient.bottom - rcClient.top - 2;
				rcClient.right = rcClient.right - rcClient.left - 3;
				
				ListPlayers->SetPos(rcClient);
				ListUnits->SetPos(rcClient);
				ListObjects->SetPos(rcClient);
				
				TextPlayerName->SetPos(rcMain.left + 10, rcMain.top + 35, 250, 20);
				TextPlayerHealth->SetPos(rcMain.left + 10, rcMain.top + 55, 250, 20);
				TextPlayerPower->SetPos(rcMain.left + 10, rcMain.top + 75, 250, 20);
				TextPlayerLevel->SetPos(rcMain.left + 10, rcMain.top + 95, 250, 20);
				
				TextTargetName->SetPos(rcMain.left + 260, rcMain.top + 35, 250, 20);
				TextTargetHealth->SetPos(rcMain.left + 260, rcMain.top + 55, 250, 20);
				TextTargetPower->SetPos(rcMain.left + 260, rcMain.top + 75, 250, 20);
				TextTargetLevel->SetPos(rcMain.left + 260, rcMain.top + 95, 250, 20);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}