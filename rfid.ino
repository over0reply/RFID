#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9       
#define SS_PIN          10       

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup() {
  Serial.begin(9600);  
  while (!Serial);    
  SPI.begin();        
  mfrc522.PCD_Init(); 
  Serial.println("Ready");
}

void loop() {
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
   
    if (isAuthorized()) {
      Serial.println("Admin");
    } else if (isAuthorized1()) {
      Serial.println("user1");
    } else if (isAuthorized2()) {
      Serial.println("user2");
    } else {
      Serial.println("denied");
    }

    mfrc522.PICC_HaltA(); 
    mfrc522.PCD_StopCrypto1(); 
  }
}

bool isAuthorized() {
 
  byte authorizedUID[] = {0x43, 0xB6, 0x6C, 0xF5};

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }
  return true;
}

bool isAuthorized1() {

  byte authorizedUID1[] = {0x53, 0x72, 0x7B, 0xF6};
 
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedUID1[i]) {
      return false;
    }
  }
  return true;
}

bool isAuthorized2() {

  byte authorizedUID2[] = {0xE6, 0x51, 0x7C, 0x72};
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedUID2[i]) {
      return false;
    }
  }
  return true;
}
