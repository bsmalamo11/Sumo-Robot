// #include <ESP_I2S.h>
// #include <wav_header.h>

#include <Ps3Controller.h>

#include <dummy.h>

#include <EEPROM.h>

//front right motor pins

const int m_frontRight_forward = 16;
const int m_frontRight_backwards = 17;
const int m_frontRight_pwm = 15;

//front left motor pins

const int m_frontLeft_forward = 25;
const int m_frontLeft_backwards = 33;
const int m_frontLeft_pwm = 32;

//back left motor pins

const int m_backLeft_forward = 26;
const int m_backLeft_backwards = 27;
const int m_backLeft_pwm = 13;

//back right motor pins

const int m_backRight_forward = 19;
const int m_backRight_backwards = 18;
const int m_backRight_pwm = 22;

//ramp motor pins

// const int m_ramp_forward = ;
// const int m_ramp_backwards = ;

//PWM Channels
const int channel_frontRight = 0;
const int channel_frontLeft = 1;
const int channel_backLeft = 2;
const int channel_backRight = 3;

// frequency for the PWM channels
//higher frequencies equal smoother running but can also mean generating more heat and more power consumption
//lower frequencies is the opposite while ensuring higher torque which is useful to us and lowers the noise as well
const int pwmFrequency = 500;

// 8-bit resolution which divides the maximum value into 256(2^8) parts
const int pwmResolution = 8;

//sensor pins

const int sensor_front = 2;
const int sensor_right = 21;

//speed for use later in motors
// const int speed = 150;


enum color {
  white = 0,
  black = 1
};

void onConnect() {
  Serial.println("Ps3 controller ON");
}
void setup() {
  Serial.begin(115200);
  //Motors setup
  pinMode(m_frontRight_forward, OUTPUT);
  pinMode(m_frontRight_backwards, OUTPUT);

  pinMode(m_frontLeft_forward, OUTPUT);
  pinMode(m_frontLeft_backwards, OUTPUT);

  pinMode(m_backLeft_forward, OUTPUT);
  pinMode(m_backLeft_backwards, OUTPUT);

  pinMode(m_backRight_forward, OUTPUT);
  pinMode(m_backRight_backwards, OUTPUT);

  //PWM Channels setupp
  // ledcAttach(m_frontRight_pwm, pwmFrequency, pwmResolution);
  // ledcAttach(m_frontLeft_pwm, pwmFrequency, pwmResolution);
  // ledcAttach(m_backLeft_pwm, pwmFrequency, pwmResolution);
  // ledcAttach(m_backRight_pwm, pwmFrequency, pwmResolution);

  //Old way of reading adc pins
  ledcSetup(channel_frontRight, pwmFrequency, pwmResolution);
  ledcSetup(channel_frontLeft, pwmFrequency, pwmResolution);
  ledcSetup(channel_backLeft, pwmFrequency, pwmResolution);
  ledcSetup(channel_backRight, pwmFrequency, pwmResolution);

  ledcAttachPin(m_frontRight_pwm, channel_frontRight);
  ledcAttachPin(m_frontLeft_pwm, channel_frontLeft);
  ledcAttachPin(m_backLeft_pwm, channel_backLeft);
  ledcAttachPin(m_backRight_pwm, channel_backRight);



  //Sensors setup
  pinMode(sensor_front, INPUT);
  pinMode(sensor_right, INPUT);
  // pinMode(sensor_left, INPUT);

  Ps3.attach(onConnect);
  Ps3.begin("ec:62:60:a2:60:f8");

  Serial.begin(115200);
}

void loop() {
  int front_sensor_color = digitalRead(sensor_front);
  int right_sensor_color = digitalRead(sensor_right);
  // int left_sensor_color = digitalRead(sensor_left);
  // Serial.println(front_sensor_color);

  



  // if (front_sensor_color == black) {
  //   move_backwards(200);
  //   delay(250);
  //   turn_right(-150);
  //   delay(250);
  // }

  // // if (left_sensor_color == black) {
  // //   turn_right(-150);
  // //   delay(250);
  // // }

  // if (right_sensor_color == black) {
  //   turn_left(-150);
  //   delay(250);
  // }


  // if (front_sensor_color == white && left_sensor_color == white && right_sensor_color == white ) {
  //   move_forward(speed);
  // }

  // delay(50);



  // stop_motors();
  // delay(100);
  // move_forward(150);
  // delay(5000);
  // stop_motors();
  // delay(5000);
  // turn_left(150);
  // delay(5000);
  // stop_motors();
  // delay(5000);
  // move_backwards(150);
  // delay(5000);
  // stop_motors();
  // delay(5000);
  // turn_right(150);
  // delay(5000);

  if(Ps3.isConnected()){
  int leftY = Ps3.data.analog.stick.ly;
  int rightX = Ps3.data.analog.stick.rx;
  int R1 = Ps3.data.button.r1;
  int R2 = Ps3.data.button.r2;
  // int ramp_motor = Ps3.data.button.square;
  


  stop_motors();


  //Left joystick is for moving

  if (leftY < -10) {
      if (R1) {
        move_forward(250);
      }

      else {
        move_forward((leftY * -1.5) + 5);
      }



    }

    else if (leftY > 10) {
      if (R2) {
        move_backwards(230);
      }
      else {
         move_backwards((leftY * 1.2) - 5);
      
      }
     

    }


  //Right joystick is for turning

  else if (rightX > 10) {

      if (rightX <= 100) {
        turn_right(110-rightX);
      }

      else if (rightX <= 127) {
        turn_right(-150);
      }

    }

  else if (rightX < -10) {

          if (rightX >= -100) {
                  turn_left(110 + rightX);
          }

          else {
            turn_left(-150);
          }
    }


  else stop_motors();
  }

  // if (ramp_motor) {
  // digitalWrite(m_ramp, HIGH);}


  // stop_motors();
  // delay(100);

  // move_forward(60);
  // delay(3000);

  // stop_motors();
  // delay(3000);

  // move_forward(150);
  // delay(3000);

  // stop_motors();
  // delay(3000);

  // move_forward(250);
  // delay(3000);

  // stop_motors();
  // delay(3000);
}


void stop_motors() {
  digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, LOW);

  digitalWrite(m_frontLeft_forward, LOW);
  digitalWrite(m_frontLeft_backwards, LOW);

  digitalWrite(m_backLeft_forward, LOW);
  digitalWrite(m_backLeft_backwards, LOW);

  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, LOW);
}


void move_forward(int speed) {
  digitalWrite(m_frontRight_forward, HIGH);
  digitalWrite(m_frontRight_backwards, LOW);
  ledcWrite(channel_frontRight, speed);

  digitalWrite(m_frontLeft_forward, HIGH);
  digitalWrite(m_frontLeft_backwards, LOW);
  ledcWrite(channel_frontLeft, speed);

  digitalWrite(m_backLeft_forward, HIGH);
  digitalWrite(m_backLeft_backwards, LOW);
  ledcWrite(channel_backLeft, speed);

  digitalWrite(m_backRight_forward, HIGH);
  digitalWrite(m_backRight_backwards, LOW);
  ledcWrite(channel_backRight, speed);
}

void move_backwards(int speed) {
  digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, HIGH);
  ledcWrite(channel_frontRight, speed);

  digitalWrite(m_frontLeft_forward, LOW);
  digitalWrite(m_frontLeft_backwards, HIGH);
  ledcWrite(channel_frontLeft, speed);

  digitalWrite(m_backLeft_forward, LOW);
  digitalWrite(m_backLeft_backwards, HIGH);
  ledcWrite(channel_backLeft, speed);

  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, HIGH);
  ledcWrite(channel_backRight, speed);
}

void turn_right(int speed) {
if (speed >= 0 ) {
digitalWrite(m_frontRight_forward, HIGH);
  digitalWrite(m_frontRight_backwards, LOW);
  ledcWrite(channel_frontRight, speed);


  digitalWrite(m_backRight_forward, HIGH);
  digitalWrite(m_backRight_backwards, LOW);
  ledcWrite(channel_backRight, speed);
}

else if (speed < 0 ) {
digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, HIGH);
  ledcWrite(channel_frontRight, abs(speed) );


  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, HIGH);
  ledcWrite(channel_backRight, abs(speed) );
}
  

  digitalWrite(m_frontLeft_forward, HIGH);
  digitalWrite(m_frontLeft_backwards, LOW);
  ledcWrite(channel_frontLeft, 250);

  digitalWrite(m_backLeft_forward, HIGH);
  digitalWrite(m_backLeft_backwards, LOW);
  ledcWrite(channel_backLeft, 250);

}

void turn_left(int speed) {
  if (speed >= 0) {
  
    digitalWrite(m_frontLeft_forward, HIGH);
    digitalWrite(m_frontLeft_backwards, LOW);
    ledcWrite(channel_frontLeft, speed);

    digitalWrite(m_backLeft_forward, HIGH);
    digitalWrite(m_backLeft_backwards, LOW);
    ledcWrite(channel_backLeft, speed);
  }

  else if (speed < 0 ) {
  
  
    digitalWrite(m_frontLeft_forward, LOW);
    digitalWrite(m_frontLeft_backwards, HIGH);
    ledcWrite(channel_frontLeft, abs(speed));

    digitalWrite(m_backLeft_forward, LOW);
    digitalWrite(m_backLeft_backwards, HIGH);
    ledcWrite(channel_backLeft, abs(speed));
  }
  digitalWrite(m_frontRight_forward, HIGH);
  digitalWrite(m_frontRight_backwards, LOW);
  ledcWrite(channel_frontRight, 250);


  digitalWrite(m_backRight_forward, HIGH);
  digitalWrite(m_backRight_backwards, LOW);
  ledcWrite(channel_backRight, 250);
}