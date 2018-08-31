
/*  Macaron is an Arduino shield based on the Petit Biscuit educational Arduino board.

    Petit Biscuit was designed by Saandial as a tool for introductory embedded programming
    using the Arduino IDE. There are 2 versions.
    
    The "saveur fraise" model has:
      16 LEDs (4 red, 4 yellow, 4 green, 4 blue)
      2 momentary pushbuttons
      Atmel ATMega328P with Arduino bootloader
      Reset button
      Crystal
      Header for FTDI-style serial interface
      
    The "saveur vanille" model has mostly the same parts, but these differences:
      Only 15 LEDs (3 red, 4 yellow, 4 green, 4 blue)
      Potentiometer
      Slide switch

    I think these were great little boards for teaching basic embedded programming. It's very
    easy to see how the I/O pins connect to the LEDs, switches, and potentiometer, and easy to
    understand how the software interacts with and controls them. 
    Saandial, thank you for designing these!!

    I decided to build my own version for my kids (and myself :-), partly because I had some small
    linear potentiometers I wanted to use and partly because I wanted to try some interesting
    looking surface mount high-efficiency LEDs.

    The result is Macaron, a bit of a hybrid of the Vanille and Fraise Petit Biscuits, and built
    as an Arduino Shield.

    Some notes:

    The LEDs are all on dedicated I/O pins, so they can always be directly controlled.
    The LED on the linear potentiometer slider is connected to the Arduino TX line. It will flicker
    when there is serial traffic. You can also just turn the TX line (1) into an digital output
    and control it directly.

    The potentiometer is connected to A5. There is also a button between A5 and ground. Normally you
    will use analogRead( A5 ) to get the slider position (0-1023). If you push the A5 button, it will
    pull A5 to ground, and you'll read 0. You can use the very cool Arduino map() function to map the
    0-1023 value onto any other range you want -- or even reverse the range.

    The other button is simply connected to digital pin 2, so you can just configure it as an input
    with pullup and use digitalRead(2) to get it's state. If it's down, it will read as 0 (or false).
*/

#define DELAY_TIME      125         // default time between LED animation "frames" in milliseconds
int delay_time = DELAY_TIME;        // variable that holds time to wait between LED animation "frames"
bool pause_flag = false;            // if true, pause the running animation
bool mode_flag = true;

void wipe_diag_down_right();
void wipe_diag_down_left();
void wipe_random(bool mode, int loops);
void wipe_lanes();

void flash_all( int count );


/*
    set_xy lets you specify a particular LED by its X/Y position
    instead of by the names of the signals that connect to them.
    
    X goes 0 -> 3, left to right
    Y goes 0 -> 3, top to bottom
*/

void set_xy( int x, int y, bool state ) {
  switch( x ) {
    case 0: switch( y ) {
              case 0: digitalWrite( 4, state );         break;
              case 1: digitalWrite( 8, state );         break;
              case 2: digitalWrite( 7, state );         break;
              case 3: digitalWrite( 6, state );         break;
            }
            break;
            
    case 1: switch( y ) {
              case 0: digitalWrite( 5, state );         break;
              case 1: digitalWrite( 9, state );         break;
              case 2: digitalWrite( 10, state );        break;
              case 3: digitalWrite( 11, state );        break;
            }
            break;
            
    case 2: switch( y ) {
              case 0: digitalWrite( 12, state );        break;
              case 1: digitalWrite( 13, state );        break;
              case 2: digitalWrite( A0, state );        break;
              case 3: digitalWrite( A1, state );        break;
            }
            break;
            
    case 3: switch( y ) {
              case 0: digitalWrite( A2, state );        break;
              case 1: digitalWrite( A3, state );        break;
              case 2: digitalWrite( A4, state );        break;
              case 3: digitalWrite( 3, state );         break;
            }
            break;
  }
}

void set_all( bool state ) {
  int x,y;
  for( x = 0; x != 4; x++ )
    for( y = 0; y != 4; y++ )
      set_xy( x, y, state );
}

void flash_all( int count, int rate ) {
  
  while( count-- ) {
    set_all( true );
    delay( rate );
    set_all( false );
    delay( rate );
  } 
}



void setup() {

  // LED Row 1
  pinMode( 3,     OUTPUT );
  digitalWrite( 3, 0 );
  pinMode( A4,    OUTPUT );
  digitalWrite( A4, 0 );
  pinMode( A3,    OUTPUT );
  digitalWrite( A3, 0 );
  pinMode( A2,    OUTPUT );
  digitalWrite( A2, 0 );

  // LED Row 2
  pinMode( A1,     OUTPUT );
  digitalWrite( A1, 0 );
  pinMode( A0,     OUTPUT );
  digitalWrite( A0, 0 );
  pinMode( 13,     OUTPUT );
  digitalWrite( 13, 0 );
  pinMode( 12,     OUTPUT );
  digitalWrite( 12, 0 );

  // LED Row 3
  pinMode( 11,     OUTPUT );
  digitalWrite( 11, 0 );
  pinMode( 10,     OUTPUT );
  digitalWrite( 10, 0 );
  pinMode( 9,     OUTPUT );
  digitalWrite( 9, 0 );
  pinMode( 5,     OUTPUT );
  digitalWrite( 5, 0 );  

  // LED Row 4
  pinMode( 6,     OUTPUT );
  digitalWrite( 6, 0 );
  pinMode( 7,     OUTPUT );
  digitalWrite( 7, 0 );
  pinMode( 8,     OUTPUT );
  digitalWrite( 8, 0 );
  pinMode( 4,     OUTPUT );
  digitalWrite( 4, 0 );   

  // '2' Button
  pinMode( 2, INPUT_PULLUP );

  // A5 Button / Slider doesn't need pinMode(), just use analogRead()

  Serial.begin( 9600 );
  Serial.println("Hello from Macaron!");
}


// use red LED column to "track" slider position

int slider_bar() {
  int reading = analogRead( A5 );
  
  Serial.println( reading );              // read and print the slider value

  if( reading > 0 )
    digitalWrite( 4, 1 );
  else
    digitalWrite( 4, 0 );

  if( reading > 300 )
    digitalWrite( 8, 1 );
  else
    digitalWrite( 8, 0 );

  if( reading > 700 )
    digitalWrite( 7, 1 );
  else
    digitalWrite( 7, 0 );

  if( reading > 1000 )
    digitalWrite( 6, 1 );
  else
    digitalWrite( 6, 0 );   
}

void check_pause() {
  if( digitalRead( 2 ) == 0 ) {
    pause_flag = !pause_flag;
    digitalWrite( A2, HIGH );
    while( digitalRead( 2 ) == 0 )        // wait for user to release button
      ;
  } else {
    digitalWrite( A2, LOW );
  }
}


void loop() {

  delay_time = map( analogRead( A5 ), 0, 1023, 50, 250 );

  if( !pause_flag ) {
    
    //wipe_random( mode_flag, map( analogRead( A5 ), 0, 1023, 8, 32 ) );
    wipe_lanes();
    
  } 

  if( digitalRead( 2 ) == 0 ) {
    mode_flag = !mode_flag;
    flash_all( 2, 250 );
    while( digitalRead( 2 ) == 0 )        // wait for user to release button
      ;
  }
  
  //check_pause();
  
  //slider_bar();
  
  //delay( 500 );                           // wait 500ms (1/2 second) so we don't print too quickly
  delay( delay_time );
}


void wipe_diag_down_right() {
    digitalWrite( 4,    HIGH );
    delay( delay_time );
    digitalWrite( 4,    LOW );
  
    digitalWrite( 5,    HIGH );
    digitalWrite( 8,    HIGH );
    delay( delay_time );
    digitalWrite( 5,    LOW );
    digitalWrite( 8,    LOW );
    
    digitalWrite( 12,    HIGH );
    digitalWrite( 9,    HIGH );
    digitalWrite( 7,    HIGH );
    delay( delay_time );
    digitalWrite( 12,    LOW );
    digitalWrite( 9,    LOW );
    digitalWrite( 7,    LOW );
    
    digitalWrite( A2,    HIGH );
    digitalWrite( 13,    HIGH );
    digitalWrite( 10,    HIGH );
    digitalWrite( 6,    HIGH );
    delay( delay_time );
    digitalWrite( A2,    LOW );
    digitalWrite( 13,    LOW );
    digitalWrite( 10,    LOW );
    digitalWrite( 6,    LOW );
      
    digitalWrite( A3,    HIGH );
    digitalWrite( A0,    HIGH );
    digitalWrite( 11,    HIGH );
    delay( delay_time );
    digitalWrite( A3,    LOW );
    digitalWrite( A0,    LOW );
    digitalWrite( 11,    LOW );

    digitalWrite( A4,    HIGH );
    digitalWrite( A1,    HIGH );
    delay( delay_time );
    digitalWrite( A4,    LOW );
    digitalWrite( A1,    LOW );
    
    digitalWrite( 3,    HIGH );
    delay( delay_time );
    digitalWrite( 3,    LOW );    
}


void wipe_diag_down_left() {
    digitalWrite( A2,    HIGH );
    delay( delay_time );
    digitalWrite( A2,    LOW );
  
    digitalWrite( 12,    HIGH );
    digitalWrite( A3,    HIGH );
    delay( delay_time );
    digitalWrite( 12,    LOW );
    digitalWrite( A3,    LOW );
    
    digitalWrite( 5,    HIGH );
    digitalWrite( 13,    HIGH );
    digitalWrite( A4,    HIGH );
    delay( delay_time );
    digitalWrite( 5,    LOW );
    digitalWrite( 13,    LOW );
    digitalWrite( A4,    LOW );
    
    digitalWrite( 4,    HIGH );
    digitalWrite( 9,    HIGH );
    digitalWrite( A0,    HIGH );
    digitalWrite( 3,    HIGH );
    delay( delay_time );
    digitalWrite( 4,    LOW );
    digitalWrite( 9,    LOW );
    digitalWrite( A0,    LOW );
    digitalWrite( 3,    LOW );
      
    digitalWrite( 8,    HIGH );
    digitalWrite( 10,    HIGH );
    digitalWrite( A1,    HIGH );
    delay( delay_time );
    digitalWrite( 8,    LOW );
    digitalWrite( 10,    LOW );
    digitalWrite( A1,    LOW );

    digitalWrite( 7,    HIGH );
    digitalWrite( 11,    HIGH );
    delay( delay_time );
    digitalWrite( 7,    LOW );
    digitalWrite( 11,    LOW );
    
    digitalWrite( 6,    HIGH );
    delay( delay_time );
    digitalWrite( 6,    LOW );    
}


void wipe_random(bool mode, int loops) {
  randomSeed( analogRead( A5 ) );

  if( mode ) {
    set_all( false );
  }

  while( loops-- ) {
    set_xy( random( 4 ), random( 4 ), (random( 512 ) > 255) );
    delay( delay_time );
  }
}


int clock_speed_0 = 1;
int clock_count_0;
int bit_pattern_0 = 0b1010001110010000;

int clock_speed_1 = 3;
int clock_count_1;
int bit_pattern_1 = 0b0110010010010000;

int clock_speed_2 = 4;
int clock_count_2;
int bit_pattern_2 = 0b0011110001001000;

int clock_speed_3 = 5;
int clock_count_3;
int bit_pattern_3 = 0b1001010010101000;


int rotate_left( int bits ) {
  return( (bits << 1) | ((bits & 0x8000) ? 1 : 0) );  
}

void drive_x_bits( int y, int bits ) {
  set_xy( 0, y, (bits & 0b0000000000001000) );
  set_xy( 1, y, (bits & 0b0000000000000100) );
  set_xy( 2, y, (bits & 0b0000000000000010) );
  set_xy( 3, y, (bits & 0b0000000000000001) );
}

void wipe_lanes() {
  clock_count_0++;
  if( clock_count_0 == clock_speed_0 ) {
    clock_count_0 = 0;
    bit_pattern_0 = rotate_left( bit_pattern_0 ); 
  }

  clock_count_1++;
  if( clock_count_1 == clock_speed_1 ) {
    clock_count_1 = 0;
    bit_pattern_1 = rotate_left( bit_pattern_1 ); 
  }
  
  clock_count_2++;
  if( clock_count_2 == clock_speed_2 ) {
    clock_count_2 = 0;
    bit_pattern_2 = rotate_left( bit_pattern_2 ); 
  }

  clock_count_3++;
  if( clock_count_3 == clock_speed_3 ) {
    clock_count_3 = 0;
    bit_pattern_3 = rotate_left( bit_pattern_3 ); 
  }    

  drive_x_bits( 0, bit_pattern_0 );
  drive_x_bits( 1, bit_pattern_1 );
  drive_x_bits( 2, bit_pattern_2 );
  drive_x_bits( 3, bit_pattern_3 );

  //delay( delay_time );
}



