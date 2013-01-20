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

#include "AbstractWindow.h"

bool AbstractWindow::Create() {
	INITCOMMONCONTROLSEX icc;
	icc.dwICC = ICC_STANDARD_CLASSES;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&icc);

	_hwnd = CreateWindowEx(
		_styleEx, _className, _windowName, _style,
		_x, _y, _width, _height,
		_hwndParent, _hMenu, _hInstance, this);

	if(!_hwnd)
		return false;
	return true;
}

LRESULT CALLBACK AbstractWindow::msgRouter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	AbstractWindow *wnd = 0;
	
	if(msg == WM_NCCREATE)
		SetWindowLong(hwnd, GWL_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));

	wnd = (AbstractWindow*)GetWindowLong(hwnd, GWL_USERDATA);

	if(wnd)
		return wnd->wndProc(hwnd, msg, wParam, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}