
/************************************************************
*****           NCF prueba de concepto                   ****                        
*****                 by Don_Epel                        ****
*************************************************************/

/* ***************************************************
Prueba de concepto utilizando la interface RFID-RC522 en
arduino MEGA 2560. 

version 1, version inicial 4 Oct 2018, primera prueba
Version 2, integracion de varias funciones por menu para porder 
            gestionar las tarjetas de de forma completa

*/
// Librerias utilizadas
#include <SPI.h>
#include <MFRC522.h>

// Definiciones de puertos ajenos al nfc en si
#define LED_READ 8

// Definiciones de puertos para el modulo RC522
#define RST_PIN	9    //Pin 9 para el reset del RC522
#define SS_PIN	53   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522


//Definiciones del menu operativo
#define MENU    0;
#define LEERID  1;
void setup() 
{
	Serial.begin(115200); //Iniciamos la comunicación  serial
	SPI.begin();        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	pinMode(LED_READ , OUTPUT);  //definir pin como salida
    
}

void loop() 
{
  unsigned char proceso=0; 
  while(1)
  {
    switch (proceso)
    {
      case MENU:
                Serial.println("****************************************");
                Serial.println("*** INTERFACE DE PRUEBA CON TARJETAS ***");
                Serial.println("*********** NFC DE 13,5MHZ *************");
                Serial.println("****************************************");
                Serial.println("");
                Serial.println("");
                break;
      case LEERID:
                	// Revisamos si hay nuevas tarjetas  presentes
                	if ( mfrc522.PICC_IsNewCardPresent()) 
                  {  
                    digitalWrite(LED_READ, HIGH);
          		      //Seleccionamos una tarjeta
                    if ( mfrc522.PICC_ReadCardSerial()) 
                    {
                      // Enviamos serialemente su UID
                      Serial.print("Card UID:");
                      for (byte i = 0; i < mfrc522.uid.size; i++) 
                      {
                        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                        Serial.print(mfrc522.uid.uidByte[i], HEX);   
                      } 
                      Serial.println();
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522.PICC_HaltA();    
                      delay (200);
                      digitalWrite(LED_READ,LOW);     
                    }      
                	}
                 proceso=MENU;
                 break;	
    }
 }
}
