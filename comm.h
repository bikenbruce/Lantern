struct PoleComm {
  XBeeAddress64 address;
  int status;
};

struct ReplyBuff {
	uint8_t messageNumber;
	int destination; 
};
