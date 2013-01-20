#ifndef _OFFSETS_H_
#define _OFFSETS_H_

namespace Offsets {
	enum ObjectManager {
		ObjectMgr = 0xE28428,
		CurMgr = 0x462C,
		FirstObject = 0xCC,
		NextObject = 0x3C,
		LocalGuid = 0xD0,
	};

	enum Player {
		InGame = 0xCC9EFA,
	};
}

#endif