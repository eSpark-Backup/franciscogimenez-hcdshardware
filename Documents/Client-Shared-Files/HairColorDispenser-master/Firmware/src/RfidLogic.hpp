
#pragma once

#include "Libraries/MFRC522.h"

typedef struct 
{
	byte		size;			// Number of bytes in the UID. 4, 7 or 10.
	byte		uidByte[10];
	byte		sak;			// The SAK (Select acknowledge) byte returned from the PICC after successful selection.
} Uid;

class RfidLogic  
{
	private:

	public:

		enum RfidType
		{
			Tray,
			Container
		};

		RfidLogic(RfidType rfidType);
		~RfidLogic();

		Uid ReadCardUid();

};