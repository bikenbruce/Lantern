void allOff() {
  Serial.println("all off.");
  for (int board = 0; board < 11; board++) {
   DmxSimple.write(board * 4 + 1, 0);
   DmxSimple.write(board * 4 + 2, 0);
   DmxSimple.write(board * 4 + 3, 0);
 
 }
}

void allOn() {
  Serial.println("all on.");
  for (int board = 0; board < 11; board++) {
   DmxSimple.write(board * 4 + 1, 255);
   DmxSimple.write(board * 4 + 2, 255);
   DmxSimple.write(board * 4 + 3, 255);
 
 }
}