struct PoleComm {
  XBeeAddress64 address;
  int status;
};

struct PoleBuff {
	ZBTxRequest msgToPole;
	uint8_t msgNumber;
	int poleDestination;

};