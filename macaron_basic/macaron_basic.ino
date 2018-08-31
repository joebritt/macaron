void setup() {

  pinMode( 4,   OUTPUT );
  pinMode( 5,   OUTPUT );
  pinMode( 12,  OUTPUT );
  pinMode( A2,  OUTPUT );

  digitalWrite( 4,  LOW );
  digitalWrite( 5,  LOW );
  digitalWrite( 12, LOW );
  digitalWrite( A2, LOW );

  Serial.begin( 9600 );
  Serial.println("Hello from Macaron!");
}

#define DELAY_TIME      125

void loop() {
  digitalWrite( 4,    HIGH );
  delay( DELAY_TIME );
  digitalWrite( 4,    LOW );

  digitalWrite( 5,    HIGH );
  delay( DELAY_TIME );
  digitalWrite( 5,    LOW );

  digitalWrite( 12,    HIGH );
  delay( DELAY_TIME );
  digitalWrite( 12,    LOW );

  digitalWrite( A2,    HIGH );
  delay( DELAY_TIME );
  digitalWrite( A2,    LOW );

  
}
