/*
  DDRB // controls ports 13 to 8
  PORTB // out/in values of ports 13 to 8
  TCCRXA & TCCRXB // control Timer X
  TCNTX // Timer X value
  TIMSKX // controls Timer X interrupts
  OCRXA & OCRXB // output‐compare values
*/
int printIsValid = 0;
String msg = ".... . ._.. ._.. ___ .__ ___ ._. ._.. _..";
int outputPin = 4;
volatile bool readyToPrint = 0;
const int baseInterval = 100;
void setup() {
  Serial.begin(9600); // used for testing
  cli(); // disable interrupts
  //DDRB |= (1 << 5); // enable LED port for writing
  pinMode(outputPin, OUTPUT);
  TCCR1A = 0x0; // reset Timer1 control registers
  TCCR1B = 0x0; // set WGM_2:0 = 000
  TCCR1B = 0x5; // set Timer1 to clk/256
  TIMSK1 = 0x6; // enable OCR interrupts bits
  OCR1A = 10000; // set Output Compare Value A
  OCR1B = 50000; // set Output Compare Value B
  sei(); // enable interrupts
}

ISR (TIMER1_COMPA_vect) {
  Serial.println("Reached 10000"); // enable
  printIsValid = 1;
}
ISR (TIMER1_COMPB_vect) {
  Serial.println("Reached 50000"); // enable
  //for testing
  Serial.println("TCNT1"); // enable
  Serial.println(TCNT1); // enable
  TCNT1 = 0;
}

void loop() {
  if (printIsValid) {
    printLED(msg);
     printIsValid = 0;
  }else{
    digitalWrite(outputPin,LOW);
    }
  Serial.println(printIsValid);
}
void printLED(String input) {
  for (int i = 0; i < input.length(); ++i) {
    Serial.println(msg[i]);
    if (msg[i] == '.') {
      digitalWrite(outputPin, HIGH);
          Serial.print("output pin:    ");
    Serial.println(digitalRead(outputPin));
      delay(100);
    }
    else if (msg == '_') {
      digitalWrite(outputPin, HIGH);
      delay(100 * 3);
    } else {
      digitalWrite(outputPin, LOW);
      delay(100 * 3);
    }
  }
}
