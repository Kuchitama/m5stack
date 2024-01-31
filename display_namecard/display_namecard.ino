#include <M5Stack.h>
File root;

// the setup routine runs once when M5Stack starts up
void setup(){

  // M5Stackの初期化
  M5.begin();
  // pinMode(10, OUTPUT);

  // LCD display
  SD.begin();
  root = SD.open("/");
  printDirectory(root, 0);
  
  M5.Lcd.print("\n\nM5Stack is running successfully!");

  delay(100);
}

// 無限ループ
void loop() {
  M5.Lcd.drawJpgFile(SD, "/namecard.jpg");

  if (M5.BtnC.wasPressed()) {
    M5.Lcd.println("Pressed C");
    M5.Power.powerOFF();
  }
  M5.update();

}

void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       dir.rewindDirectory();
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       M5.Lcd.print('\t');
     }
     M5.Lcd.print(entry.name());
     if (entry.isDirectory()) {
       M5.Lcd.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       M5.Lcd.println("\t\t");
       //M5.Lcd.println(entry.size(), DEC);
     }
   }
}
