#include "CListControl.h"

bool CListControl::Create(HWND hParent) {
	hwnd = CreateWindow(
		WC_LISTVIEW,
		"",
		WS_CHILD | LVS_REPORT,
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

bool CListControl::AddColumn(LPSTR str, int width = 100) {
	ColumnStruct* cs = new ColumnStruct;
	LVCOLUMN lvc;
	
	cs->pos = ColumnList.size();
	cs->text = str;


	lvc.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.iSubItem = cs->pos;
	lvc.pszText = cs->text;
	lvc.cx = width;

	if(ListView_InsertColumn(hwnd, cs->pos, &lvc) == -1)
		return false;

	ColumnList.push_back(cs);

	return true;
}

bool CListControl::AddRow(LPSTR rowVals[]) {
	for(int val = 0; val <= sizeof(rowVals); val++) {
		LVITEM lvi;

		lvi.mask = LVIF_TEXT;
		lvi.pszText = rowVals[val];
		lvi.cchTextMax = sizeof(rowVals[val]);
		lvi.iItem = 0;
		lvi.iSubItem = val;

		if(val == 0) {
			if(ListView_InsertItem(hwnd, &lvi) == -1)
				return false;
		} else {
			if(ListView_SetItem(hwnd, &lvi) == -1)
				return false;
		}
	}

	return true;
}

void CListControl::Clear() {
	ListView_DeleteAllItems(hwnd);
}

void CListControl::SetPos(RECT rc) {
	SetWindowPos(hwnd, NULL, rc.left, rc.top, rc.right, rc.bottom, 0);
}