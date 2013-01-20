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
/* 
		WARNING!!! UGLY CODE BELOW THIS POINT! SOMEONE HAS A HARD TIME CLEANING UP, ooops thats me :(
		/ Ejt
*/
LRESULT CALLBACK MainWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE:
			break;
		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->code) {
				case TCN_SELCHANGING:
					return false;
					break;
				case TCN_SELCHANGE:
					{
						int page = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);

						if(((LPNMHDR)lParam)->hwndFrom == hwndTab) { // main tab
								ShowWindow(hwndTabObjects, SW_HIDE); // Show objects tab
								ShowWindow(hwndTabObjects, SW_HIDE); // Hide objects tab
							if(page == 0) { // General tab selected
								ShowWindow(hwndTabObjects, SW_SHOW); // Show objects tab
								ShowWindow(hwndLWContainers, SW_HIDE);
								ShowWindow(hwndLWGameObjects, SW_HIDE);
								ShowWindow(hwndLWItems, SW_HIDE);
								ShowWindow(hwndLWPlayers, SW_HIDE);
								ShowWindow(hwndLWUnits, SW_HIDE);
							} else if(page == 1) {
								ShowWindow(hwndTabObjects, SW_SHOW); // Show objects tab
							}
						} else if(((LPNMHDR)lParam)->hwndFrom == hwndTabObjects) {
								ShowWindow(hwndLWContainers, SW_HIDE);
								ShowWindow(hwndLWGameObjects, SW_HIDE);
								ShowWindow(hwndLWItems, SW_HIDE);
								ShowWindow(hwndLWPlayers, SW_HIDE);
								ShowWindow(hwndLWUnits, SW_HIDE);
							if(page == 0) {// Containers
								ShowWindow(hwndLWContainers, SW_SHOW);
							} else if(page == 1) { // Game objects
								ShowWindow(hwndLWGameObjects, SW_SHOW);
							} else if(page == 2) { // Items
								ShowWindow(hwndLWItems, SW_SHOW);
							} else if(page == 3) { // Players
								ShowWindow(hwndLWPlayers, SW_SHOW);
							} else if(page == 4) { // Units
								ShowWindow(hwndLWUnits, SW_SHOW);
							}
						}
					}
					break;
			}
			break;
		case WM_SIZE:
			{
				RECT rc;
				GetClientRect(_hwnd, &rc);
				
				SetWindowPos(hwndTab, NULL, 0, 0, rc.right, rc.bottom, 0);
				SetWindowPos(hwndTabObjects, NULL, 5, 30, rc.right - 10, rc.bottom - 35, 0);
				SetWindowPos(hwndLWContainers, NULL, 1, 25, rc.right - 15, rc.bottom - 50, 0);
				SetWindowPos(hwndLWGameObjects, NULL, 1, 25, rc.right - 15, rc.bottom - 50, 0);
				SetWindowPos(hwndLWItems, NULL, 1, 25, rc.right - 15, rc.bottom - 50, 0);
				SetWindowPos(hwndLWPlayers, NULL, 1, 25, rc.right - 15, rc.bottom - 50, 0);
				SetWindowPos(hwndLWUnits, NULL, 1, 25, rc.right - 15, rc.bottom - 50, 0);
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

bool MainWindow::CreateRest() {
	// Create tabcontrols
	hwndTab = CreateWindow(WC_TABCONTROL, "", WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
		0, 0, 200, 200, _hwnd, (HMENU)NULL, _hInstance, NULL);

	LPSTR tabs[] = { "General", "Objects" };

	for(size_t tab = 0; tab < ARRAYSIZE(tabs); tab++) {
		TCITEM tie;
		tie.mask = TCIF_TEXT;
		tie.pszText = tabs[tab];

		if(TabCtrl_InsertItem(hwndTab, tab, &tie) == -1) {
			DestroyWindow(hwndTab);
			return false;
		}
	}

	hwndTabObjects = CreateWindow(WC_TABCONTROL, "", WS_CHILD | WS_CLIPSIBLINGS,
		0, 0, 200, 200, hwndTab, (HMENU)NULL, _hInstance, NULL);

	LPSTR tabs2[] = { "Containers", "Game Objects", "Items", "Players", "Units" };

	for(size_t tab = 0; tab < ARRAYSIZE(tabs2); tab++) {
		TCITEM tie;
		tie.mask = TCIF_TEXT;
		tie.pszText = tabs2[tab];

		if(TabCtrl_InsertItem(hwndTabObjects, tab, &tie) == -1) {
			DestroyWindow(hwndTabObjects);
			return false;
		}
	}

	struct lvsCols {
		LPSTR str;
		int width;
	};

	hwndLWContainers = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT,
		0, 0, 200, 200, hwndTabObjects, (HMENU)NULL, _hInstance, NULL);

	lvsCols containerCols[] = {
		{ "GUID", 100 },
		{ "Slots", 100 },
		{ "NumSlots", 100 },
	};

	for(int iCol = 0; iCol < ARRAYSIZE(containerCols); iCol++) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iSubItem = iCol;
		lvc.pszText = containerCols[iCol].str;
		lvc.cx = containerCols[iCol].width;

		if(ListView_InsertColumn(hwndLWContainers, iCol, &lvc) == -1)
			return false;
	}

	hwndLWGameObjects = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT,
		0, 0, 200, 200, hwndTabObjects, (HMENU)NULL, _hInstance, NULL);
	
	lvsCols gameObjectsCols[] = {
		{ "GUID", 100 },
		{ "Name", 100 },
	};

	for(int iCol = 0; iCol < ARRAYSIZE(gameObjectsCols); iCol++) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iSubItem = iCol;
		lvc.pszText = gameObjectsCols[iCol].str;
		lvc.cx = gameObjectsCols[iCol].width;

		if(ListView_InsertColumn(hwndLWGameObjects, iCol, &lvc) == -1)
			return false;
	}
	
	hwndLWItems = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT,
		0, 0, 200, 200, hwndTabObjects, (HMENU)NULL, _hInstance, NULL);
	
	lvsCols itemCols[] = {
		{ "GUID", 100 },
		{ "Name", 100 },
	};

	for(int iCol = 0; iCol < ARRAYSIZE(itemCols); iCol++) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iSubItem = iCol;
		lvc.pszText = itemCols[iCol].str;
		lvc.cx = itemCols[iCol].width;

		if(ListView_InsertColumn(hwndLWItems, iCol, &lvc) == -1)
			return false;
	}

	hwndLWPlayers = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT,
		0, 0, 200, 200, hwndTabObjects, (HMENU)NULL, _hInstance, NULL);
	
	lvsCols playerCols[] = {
		{ "GUID", 100 },
		{ "Name", 100 },
		{ "Health", 100 },
		{ "Power", 100 },
		{ "Level", 100 }
	};

	for(int iCol = 0; iCol < ARRAYSIZE(playerCols); iCol++) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iSubItem = iCol;
		lvc.pszText = playerCols[iCol].str;
		lvc.cx = playerCols[iCol].width;

		if(ListView_InsertColumn(hwndLWPlayers, iCol, &lvc) == -1)
			return false;
	}

	hwndLWUnits = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT,
		0, 0, 200, 200, hwndTabObjects, (HMENU)NULL, _hInstance, NULL);
	
	lvsCols unitCols[] = {
		{ "GUID", 100 },
		{ "Name", 100 },
		{ "Health", 100 },
		{ "Power", 100 },
		{ "Level", 100 }
	};

	for(int iCol = 0; iCol < ARRAYSIZE(unitCols); iCol++) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iSubItem = iCol;
		lvc.pszText = unitCols[iCol].str;
		lvc.cx = unitCols[iCol].width;

		if(ListView_InsertColumn(hwndLWUnits, iCol, &lvc) == -1)
			return false;
	}

	SendMessage(_hwnd, WM_SIZE, 0, 0); // Force resize

	return true;
}

void MainWindow::AddList(HWND ch) {

}