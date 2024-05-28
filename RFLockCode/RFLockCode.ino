#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         D3          // Configurable, see typical pin layout above
#define SS_PIN          D8         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode (2,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (16,OUTPUT);
  pinMode (3,OUTPUT);// 
  digitalWrite(4,HIGH); //power dari kunci (putih)
  digitalWrite(2,HIGH);//power source motor (biru)

}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Check if UID matches specified value
	if (mfrc522.uid.uidByte[0] == 0xC3 && 
		mfrc522.uid.uidByte[1] == 0xD5 && 
		mfrc522.uid.uidByte[2] == 0xA6 && 
		mfrc522.uid.uidByte[3] == 0xA6) {
		Serial.println("Access Granted!");
    
     //kunci
    digitalWrite(5,HIGH);//dari esp32 ke rfid
    digitalWrite(16,HIGH);//oke light
    digitalWrite(3,LOW);//no light
    delay(4000);



	} else {
		Serial.println("Access Denied!");
    
    digitalWrite(5,LOW);
    digitalWrite(16,LOW); //oke light
    digitalWrite(3,HIGH); //no light
    delay(3000);
	}
    digitalWrite(16,LOW);//lampu oke mati
    digitalWrite(3,LOW);//lampu no mati
    digitalWrite(5,LOW);//dari rfid mati
 
    delay(1000);
}