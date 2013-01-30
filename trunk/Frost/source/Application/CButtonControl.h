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

#ifndef _CBUTTONCONTROL_H_
#define _CBUTTONCONTROL_H_

#include <Windows.h>
#include <CommCtrl.h>

class CButtonControl {
public:
	bool Create(HWND);
	void Text(LPSTR text);
	void Disable();
	void Enable();
	bool Enabled();

	void SetPos(int x, int y, int width, int height);

	HWND Handle() { return hwnd; }
private:
	HWND hwnd;
};

#endif