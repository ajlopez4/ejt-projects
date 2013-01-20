#ifndef _WOWOBJECT_H_
#define _WOWOBJECT_H_

#include "../../../Common.h"

#include "../Offsets/Constants.h"
#include "../Offsets/Descriptors.h"
#include "../Offsets/Offsets.h"

class WoWObject {
public:
	WoWObject(unsigned int objPtr);
	~WoWObject();

	int Type();
	unsigned long Guid();

	template<class T>
	T GetDescriptorField(unsigned int field) {
		field *= Descriptors::DescriptorMulti;
		unsigned int descPtr = Mem->Read<unsigned int>(ObjectPointer + Descriptors::DescriptorOffset);
		return (T)Mem->Read<T>(descPtr + field);
	};

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif