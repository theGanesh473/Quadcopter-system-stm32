bool plotmode = 0; 
unsigned long long previousmillis = 0;

float pulseA0 = 0; 
float pulseA1 = 0;

void setup() {
  Serial.begin(115200);

  GPIOB_BASE->CRL |= (1 << 23);
  GPIOB_BASE->CRL &= ~((1 << 22) | (1 << 21) | (1 << 20));

  GPIOA_BASE->CRL |= ((1 << 3) | (1 << 7)); 
  GPIOA_BASE->CRL &= ~(1 | (1 << 1) | (1 << 2) | (1 << 4) | (1 << 5) | (1 << 6));

  GPIOC_BASE->CRH |= ((1 << 20) | (1 << 21)); 
  GPIOC_BASE->CRH &= ~((1 << 22) | (1 << 23));
}

void loop() {    
  plotmode = ((GPIOB_BASE->IDR) >> 5) & 1;  // Read PB5 port

  pulseA0 = (GPIOA_BASE->IDR) & 1;          // Read PA0 port

  if ((GPIOA_BASE->IDR) & 1) {
    GPIOC_BASE->ODR |= (1 << 13);
  } else {
    GPIOC_BASE->ODR &= ~(1 << 13);
  }

  pulseA1 = ((GPIOA_BASE->IDR) >> 1) & 1;   // Read PA1 port

  if (plotmode == 1)   
    roll_graph(25);
}

void roll_graph(unsigned int delayy1) {
  if ((millis() - previousmillis) >= delayy1) { 
    Serial.print(0);
    Serial.print(" ");
    Serial.print(pulseA0);
    Serial.print(" ");
    Serial.println(pulseA1);
    previousmillis = millis();
  }
}
