#include "RfidLogic.hpp"
#include <SPI.h>
#include "Pinout.h"

MFRC522 m_Mfrc522;

RfidLogic::RfidLogic(RfidType rfidType)
{
    if (rfidType == RfidType::Tray)
        m_Mfrc522.PCD_Init(TRAY_SS_PIN, TRAY_RST_PIN);
    else
        m_Mfrc522.PCD_Init(CONTAINER_SS_PIN, CONTAINER_RST_PIN);
}

RfidLogic::~RfidLogic()
{

}

Uid RfidLogic::ReadCardUid()
{
    if ( ! m_Mfrc522.PICC_IsNewCardPresent()) {
		return Uid();
	}

	// Select one of the cards
	if ( ! m_Mfrc522.PICC_ReadCardSerial()) {
		return Uid();
	}

    Uid uid = {m_Mfrc522.uid.size, *m_Mfrc522.uid.uidByte, m_Mfrc522.uid.sak};

    return uid;
}