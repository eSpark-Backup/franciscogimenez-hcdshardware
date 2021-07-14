#include "MFRC522_mod.h"


MFRC522 mfrc522Container = MFRC522(chipSelectPin1, resetPin1); // Create instance
MFRC522 mfrc522Tray = MFRC522(chipSelectPin2, resetPin2);

//used in authentication
MFRC522::MIFARE_Key oldKeyA;
MFRC522::MIFARE_Key oldKeyB;
//authentication return status code
MFRC522::StatusCode status;



// FUNCTIONS DECLARATION

void initReader();
void dump_byte_array(byte * buffer_, byte bufferSize);
void refreshReader(MFRC522 xx);
String readCard(MFRC522 xx);
int writeBlock(int blockNumber, byte arrayAddress[]);
int readBlock(int blockNumber, byte arrayAddress[]);
void blockWriting(byte add_, String buff_);
String blockReading(byte add_);



// VARIABLES

const byte counter_block_address = 5,   // address to store counter increment
           block_size_bytes = 16;  // you can string 16 char string from the card

//  block_writing(counter_block_address, num2);  // num2 is 16 char string
//  Serial.println(block_reading(counter_block_address).toInt());

void initReader() {
  SPI.begin();

  mfrc522Tray.PCD_Init();
  mfrc522Tray.PCD_DumpVersionToSerial();

  mfrc522Container.PCD_Init();
  mfrc522Container.PCD_DumpVersionToSerial();



  // Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
  // Since the cards in the kit are new and the keys were never defined, they are 0xFF
  // if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.


  for (byte x = 0; x < 6; x++) {  // this is default
    oldKeyA.keyByte[x] = 0xFF;
    oldKeyB.keyByte[x] = 0xFF;
  }


  Serial.print(F("Using key A:"));
  dump_byte_array(oldKeyA.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();

  Serial.print(F("Using key B:"));
  dump_byte_array(oldKeyB.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();

}



void dump_byte_array(byte * buffer_, byte bufferSize) {
  for (byte x = 0; x < bufferSize; x++) {
    Serial.print(buffer_[x] < 0x10 ? " 0" : " ");
    Serial.print(buffer_[x], HEX);
  }
}

void blockWriting(byte add_, String buff_) {
  byte blockcontent[block_size_bytes];
  byte len_ = buff_.length();

  for ( byte x = 0; x < len_; x++ ) {
    blockcontent[x] = buff_.charAt(x);
  }
  writeBlock(add_, blockcontent);
}


String blockReading(byte add_) {
  byte readbackblock[block_size_bytes + 2];  // put 3 to avoid buffer overflow and program crash
  readBlock(add_, readbackblock);
  String read_ = "";
  for (byte x = 0 ; x < block_size_bytes ; x++)  {   // print the block contents
    char c = readbackblock[x];  // convert ascii to char
    read_ += c;
  }
  Serial.println("\n block read: <<" + read_ + ">>");
  return read_;
}


String readCard(MFRC522 xx) {
  //waiting the card approach
  if ( ! xx.PICC_IsNewCardPresent()) {
    return "";
  }
  // Select a card
  if ( ! xx.PICC_ReadCardSerial()) {
    return "";
  }

  String uid = "";

  for (byte i = 0; i < xx.uid.size; i++) {
    uid.concat(String(xx.uid.uidByte[i] < 0x10 ? " 0" : " "));
    uid.concat(String(xx.uid.uidByte[i], HEX));
  }

  uid.replace(" ", "");
  uid.toUpperCase();  // this is MUST
  Serial.println("\nUID: " + uid + "\n");

  refreshReader(xx);
  return uid;
}

void refreshReader(MFRC522 xx) {
  // Halt PICC
  xx.PICC_HaltA();
  // Stop encryption on PCD
  xx.PCD_StopCrypto1();
}


int writeBlock(int blockNumber, byte arrayAddress[]) {
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3; //determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0) {
    Serial.print(blockNumber);  // block number is a trailer block (modulo 4); quit and send error code 2
    Serial.println(" is a trailer block:");
    return 2;
  }
  Serial.print(blockNumber);
  Serial.println(" is a data block:");


  /*****************************************authentication of the desired block for access***********************************************************/
  Serial.println(F("\nAuthenticating using key A..."));
  status = (MFRC522::StatusCode)mfrc522Container.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &oldKeyA, &(mfrc522Container.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522Container.GetStatusCodeName(status));
    Serial.println("  KEYS MISMATCH 22 !");
    return 0;  // one key mismatch, get out with zero return
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************writing the block***********************************************************/

  status = mfrc522Container.MIFARE_Write(blockNumber, arrayAddress, 16);//valueBlockA is the block number, MIFARE_Write(block number (0-15), byte array containing 16 values, number of bytes in block (=16))
  //status = mfrc522Container.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(status);
    return 4;//return "4" as error message
  }
  Serial.println("block was written");
}

int readBlock(int blockNumber, byte arrayAddress[]) {
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3; //determine trailer block for the sector

  /*****************************************authentication of the desired block for access***********************************************************/
  Serial.println(F("\nAuthenticating using key A..."));
  status = (MFRC522::StatusCode)mfrc522Container.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &oldKeyA, &(mfrc522Container.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522Container.GetStatusCodeName(status));
    Serial.println("  KEYS MISMATCH 33!");
    return 0;  // one key mismatch, get out with zero return
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************reading a block***********************************************************/

  byte buffersize = 18;//we need to define a variable with the read    buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = mfrc522Container.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable;     MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_read() failed: ");
    Serial.println(status);
    return 4; //return "4" as error message
  }
  Serial.println("block was read");
}
