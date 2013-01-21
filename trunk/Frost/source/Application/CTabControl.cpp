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

#include <Application\CTabControl.h>

bool CTabControl::Create(HWND hParent) {
	hwnd = CreateWindow(
		WC_TABCONTROL,
		"",
		WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
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

bool CTabControl::AddTab(LPSTR title) {
	TabStruct *newTab = new TabStruct;
	TCITEM tie;

	newTab->pos = TabList.size();
	newTab->text = title;

	tie.mask = TCIF_TEXT;
	tie.pszText = newTab->text;

	if(TabCtrl_InsertItem(hwnd, newTab->pos, &tie) == -1)
		return false;

	TabList.push_back(newTab);

	return true;
}

void CTabControl::RemoveTab(LPSTR title) {
	for(list<TabStruct*>::iterator it = TabList.begin(); it != TabList.end(); it++) {
		if(strcmp((*it)->text, title) == 0) {
			TabCtrl_DeleteItem(hwnd, (*it)->pos);
		}
	}
}

void CTabControl::AddControl(LPSTR parent, HWND hControl) {
	for(list<TabStruct*>::iterator it = TabList.begin(); it != TabList.end(); it++) {
		if(strcmp((*it)->text, parent) == 0) {
			(*it)->children.push_back(hControl);
		}
	}
}

void CTabControl::SetSize(RECT newSize) {
	SetWindowPos(hwnd, NULL, newSize.left, newSize.top, newSize.right, newSize.bottom, 0);
}

void CTabControl::SwitchTab(LPSTR title = "", int pos = -1) {
	for(list<TabStruct*>::iterator it = TabList.begin(); it != TabList.end(); it++) {
		for(list<HWND>::iterator it2 = (*it)->children.begin(); it2 != (*it)->children.end(); it2++) {
			if(strcmp((*it)->text, title) == 0 || (*it)->pos == pos) {
				ShowWindow((*it2), SW_SHOW);
			} else {
				ShowWindow((*it2), SW_HIDE);
			}
		}
	}
}