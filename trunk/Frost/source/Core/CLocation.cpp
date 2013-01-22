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

#include <CLocation.h>
#include <ObjectManager\CObjectManager.h>

const double CLocation::PI = 3.1415926;

double CLocation::Bearing() {
	CLocation playerPos = ObjectManager->GetLocalPlayer()->Location();
	double facing = NegativeAngle((float)atan2((double)(Y - playerPos.Y), (double)(X - playerPos.X)));
	return (double)(NegativeAngle(facing - ObjectManager->GetLocalPlayer()->Facing()) < PI);
}

double CLocation::GetDistanceTo(CLocation l) {
	return GetDistanceToFlat(l) + abs(Z - l.Z);
}

double CLocation::GetDistanceToFlat(CLocation l) {
	return abs(X - l.X) + abs(Y - l.Y);
}

double CLocation::GetDistanceToSelf() {
	return GetDistanceTo(ObjectManager->GetLocalPlayer()->Location());
}

double CLocation::FacingTo(CLocation l) {
	return NegativeAngle(atan2((l.Y - Y), (l.X - X)));
}

string CLocation::ToString() {
	char buf[64] = {0};
	sprintf_s(buf, "<%4.2f, %4.2f, %4.2f>", X, Y, Z);
	return buf;
}

double CLocation::NegativeAngle(double angle) {
	if(angle < 0) angle += PI * 2;
	return angle;
}
