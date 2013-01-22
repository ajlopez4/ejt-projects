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

#ifndef _OFFSETS_H_
#define _OFFSETS_H_

namespace Offsets {
	enum ObjectManager {		// 5.1.0.16357
		ObjectMgr = 0xE28428,	// 5.1.0.16357
		CurMgr = 0x462C,		// 5.1.0.16357
		FirstObject = 0xCC,		// 5.1.0.16357
		NextObject = 0x3C,		// 5.1.0.16357
		LocalGuid = 0xD0,		// 5.1.0.16357
	};

	enum Unit { // Offsets specific to units (including players)
		UnitCast = 0xC38,		// 5.1.0.16357
		UnitChannel = 0xC58,	// 5.1.0.16357
		UnitName1 = 0x970,		// 5.1.0.16357
		UnitName2 = 0x64,		// 5.1.0.16357
		UnitTarget = 0x4C,		// 5.1.0.16357
		UnitX = 0x7E8,			// 5.1.0.16357
		UnitY = UnitX + 0x4,	// 5.1.0.16357
		UnitZ = UnitY + 0x4,	// 5.1.0.16357
		UnitR = UnitZ + 0x8,	// 5.1.0.16357
	};

	enum Player { // Offsets specific to local player (the person playing the game duh!)
		PlayerName = 0xE28468,	// 5.1.0.16357
		Target = 0xCC9F20,		// 5.1.0.16357
		InGame = 0xCC9EFA,		// 5.1.0.16357
	};

    enum PlayerNameStore {
        nameStorePtr = 0xBF8508 + 0x8,	// 5.1.0.16357
        nameMaskOffset = 0x24,			// 5.1.0.16357
        nameBaseOffset = 0x01C,			// 5.1.0.16357
        nameStringOffset = 0x021,		// 5.1.0.16357
    };

	enum Object { // Object specific offsets
		ObjectType = 0x10,			// 5.1.0.16357
		ObjectX = 0xF0,				// 5.1.0.16357
		ObjectY = ObjectX + 0x4,	// 5.1.0.16357
		ObjectZ = ObjectY + 0x4,	// 5.1.0.16357
		ObjectName1 = 0x1B8,		// 5.1.0.16357
		ObjectName2 = 0xB4,			// 5.1.0.16357
	};
}

#endif