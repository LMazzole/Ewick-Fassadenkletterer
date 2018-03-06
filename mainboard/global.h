#ifndef GLOBAL_H_
#define GLOBAL_H_

/**Keypad Nr. 0 Pin 2*/
#define button0  (2)
/**Keypad Nr. 1 Pin 10*/
#define button1 (10)
/**Keypad Nr. 2 Pin 0*/
#define button2  (0)
/**Keypad Nr. 3 Pin 11*/
#define button3 (11)
/**Keypad Nr. 4 Pin 7*/
#define button4  (7)
/**Keypad Nr. 5 Pin 8*/
#define button5  (8)
/**Keypad Nr. 6 Pin 9*/
#define button6  (9)
/**Keypad Nr. 7 Pin 4*/
#define button7  (4)
/**Keypad Nr. 8 Pin 5*/
#define button8  (5)
/**Keypad Nr. 9 Pin 6*/
#define button9  (6)
/**Keypad Nr. * Pin 1*/
#define buttonStar (1)
/**Keypad Nr. # Pin 3*/
#define buttonHash (3)
/**Green LED Pin 12*/
#define ledOpen   (12)
/**Red LED Pin 13*/
#define ledClose  (13)
/**Operates a 5V Relais Pin A0*/
#define doorPin   (A0)
//NFC
/**NFC Serial Clock Pin A1*/
#define PN532_SCK  (A1)
/**NFC Master Output, Slave Input Pin A2*/
#define PN532_MOSI (A2)
/**NFC Slave Select Pin A3*/
#define PN532_SS   (A3)
 /**NFC Master Input, Slave Output Pin A4*/
#define PN532_MISO (A4)

/**NFC Interrupt Request Pin A1*/
#define PN532_IRQ   (A1)
/**Not connected by default on the NFC Shield*/
#define PN532_RESET (A2)


/** Max length of Input*/
const int maxIN = (10 + 1);

/** customize your Code here */
static char secretCode[] = {button3, button3, button3, button3};

/** customize your authorized cards here */
//const unsigned long int authorizedCards[] = {	3295930656},	// ""TestCard""
//
//char* authorizedCardsName[] = { "TestCard"};



/** Length of your SecretCode */
const int k = sizeof(secretCode) / sizeof(secretCode[0]);

/** Length of your authorizedCards array */
//const int authorizedCardsSize = sizeof(authorizedCards) / sizeof(authorizedCards[0]);






#endif //GLOBAL_H_
