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

#include <Application\CTextControl.h>

bool CTextControl::Create(HWND hParent) {
	hwnd = CreateWindow(
		WC_STATIC,
		"",
		WS_CHILD,
		0,
		0,
		200,
		200,
		hParent,
		(HMENU)NULL,
		GetModuleHandle(NULL),
		NULL);

	if(!hwnd)
		return false;

	return true;
}

void CTextControl::Text(const char* format, ...) {
	char buf[256] = {0};
	va_list args;
	va_start(args, format);
	vsprintf_s(buf, format, args);
	SetWindowText(hwnd, buf);
	va_end(args);
}

void CTextControl::SetPos(int x, int y, int width, int height) {
	SetWindowPos(hwnd, NULL, x, y, width, height, 0);
}