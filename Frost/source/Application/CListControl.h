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

#ifndef _CLISTCONTROL_H_
#define _CLISTCONTROL_H_

#include <Windows.h>
#include <CommCtrl.h>
#include <list>

using namespace std;

class CListControl {
public:
	bool Create(HWND);
	bool AddColumn(LPSTR, int);
	bool AddRow(LPSTR[]);
	void Clear();

	void SetPos(int x, int y, int width, int height);

	HWND Handle() { return hwnd; }
private:
	struct ColumnStruct {
		int pos;
		LPSTR text;
	};

	list<ColumnStruct> ColumnList;

	HWND hwnd;
};

#endif