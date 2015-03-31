int previousBoard = -1;

void lightUp(int frame) {
  int currentBoard = frame / 10;
  
  DmxSimple.write(currentBoard * 4 + 1, 255);
  DmxSimple.write(currentBoard * 4 + 2, 255);
  DmxSimple.write(currentBoard * 4 + 3, 255);
  
  if (previousBoard != currentBoard) {
    DmxSimple.write(previousBoard * 4 + 1, 0);
    DmxSimple.write(previousBoard * 4 + 2, 0);
    DmxSimple.write(previousBoard * 4 + 3, 0);
    
  }
  
  previousBoard = currentBoard;

}

void allOff() {
  Serial.println("all off.");
  for (int i = 0; i < 11; i++) {
   DmxSimple.write(i * 4 + 1, 0);
   DmxSimple.write(i * 4 + 2, 0);
   DmxSimple.write(i * 4 + 3, 0);
 }
}
