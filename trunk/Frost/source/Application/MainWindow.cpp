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

				MainTab->AddControl("General", 
					CreateWindow(WC_STATIC, "Test General", WS_VISIBLE | WS_CHILD,
					40, 40, 200, 25, MainTab->Handle(), (HMENU)NULL, GetModuleHandle(NULL), NULL));

				MainTab->AddControl("Object Manager", 
					CreateWindow(WC_STATIC, "Test Object Manager", WS_CHILD,
					40, 40, 200, 25, MainTab->Handle(), (HMENU)NULL, GetModuleHandle(NULL), NULL));

				SendMessage(hwnd, WM_SIZE, 0, 0); // Force resize
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
					}
					break;
			}
			break;
		case WM_SIZE:
			{
				RECT rc;
				GetClientRect(hwnd, &rc);

				MainTab->SetSize(rc);
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