void allOff() {
  for (int board = 0; board < 11; board++) {
   DmxSimple.write(board * 4 + 1, 0);
   DmxSimple.write(board * 4 + 2, 0);
   DmxSimple.write(board * 4 + 3, 0);
 
 }
}

void allOn(int brightness) {
  for (int board = 0; board < 11; board++) {
   DmxSimple.write(board * 4 + 1, brightness - 30);
   DmxSimple.write(board * 4 + 2, brightness);
   DmxSimple.write(board * 4 + 3, brightness);
 
 }
}

void ledBoardOn(int board) {
   DmxSimple.write(board * 4 + 1, 100);
   DmxSimple.write(board * 4 + 2, 255);
   DmxSimple.write(board * 4 + 3, 100);

}

void ledBoardOff(int board) {
   DmxSimple.write(board * 4 + 1, 0);
   DmxSimple.write(board * 4 + 2, 0);
   DmxSimple.write(board * 4 + 3, 0);

}