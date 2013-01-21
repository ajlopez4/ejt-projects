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

#include "MainWindow.h"

MainWindow::MainWindow(const char* windowName, const char* className) : AbstractWindow() {
	_windowName = windowName;
	_className = className;
	_hInstance = GetModuleHandle(NULL);
	_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_x = _y = CW_USEDEFAULT;
	_height = _width = CW_USEDEFAULT;
	_styleEx = 0;
	_hwndParent = 0;
	_hMenu = 0;
}

LRESULT CALLBACK MainWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE:
			{
				MainTab = new CTabControl;
				MainTab->Create(hwnd);
				MainTab->AddTab("General");
				MainTab->AddTab("Object Manager");

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
				ListPlayers->AddColumn("Health", 100);
				ListPlayers->AddColumn("Power", 100);
				ListPlayers->AddColumn("Level", 100);

				ObjectsTab->AddControl("Players", ListPlayers->Handle());

				ListUnits = new CListControl;
				ListUnits->Create(ObjectsTab->Handle());
				ListUnits->AddColumn("GUID", 100);
				ListUnits->AddColumn("Name", 100);
				ListUnits->AddColumn("Health", 100);
				ListUnits->AddColumn("Power", 100);
				ListUnits->AddColumn("Level", 100);

				ObjectsTab->AddControl("Units", ListUnits->Handle());

				ListObjects = new CListControl;
				ListObjects->Create(ObjectsTab->Handle());
				ListObjects->AddColumn("GUID", 100);

				ObjectsTab->AddControl("Objects", ListObjects->Handle());

				MainTab->SwitchTab("General", -1);
				ObjectsTab->SwitchTab("Players", -1);

				SendMessage(hwnd, WM_SIZE, 0, 0); // Force resize

				SetTimer(hwnd, TIMER_PULSE, 1000, NULL);
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
		case WM_SIZE:
			{
				RECT rc;
				GetClientRect(hwnd, &rc);

				MainTab->SetSize(rc);

				rc.top += 28;
				rc.left += 5;
				rc.bottom = rc.bottom - rc.top - 5;
				rc.right = rc.right - rc.left - 5;

				ObjectsTab->SetSize(rc);

				rc.left -= 4;
				rc.top -= 4;
				rc.bottom = rc.bottom - rc.top - 2;
				rc.right = rc.right - rc.left - 3;
				
				ListPlayers->SetPos(rc);
				ListUnits->SetPos(rc);
				ListObjects->SetPos(rc);
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