/*
Creator : Ahmed Razim (razim.info)
February 12, 2023
https://github.com/BurnedGalaxy/Kalman_filter_HCSR04
This code uses https://github.com/tomstewart89/BasicLinearAlgebra
*/

#include "BasicLinearAlgebra.h"
using namespace BLA;

// Ultrasonic sensor variables
const int trigPin = 4;
const int echoPin = 3;
float distance;
float duration;
float v=37, dt = 0.150;           // model specific variables

// Initializing Kalman variables
Matrix <2, 2> Pe = {500, 0,
                   0, 50};        // State error covariance matrix

Matrix <2, 2> Pp = {0, 0,
                    0, 0};

Matrix <2, 1> xe = {0, 0};        // Estimated state
Matrix <2, 1> xt = {0, v};        // True value
Matrix <2, 1> xp = {0, v};        // Predicted state

Matrix <1, 1> z = 0;              // Distance Measurement

Matrix <2, 1> G = {0, 0};         // Kalman Gain

const Matrix <2, 2> A = {1, dt,
                         0, 1};   // State Matrix

const Matrix <1, 2> H = {1, 0};   // Measurement Matrix

const float R = 40;              // Measurement noise
const float Q = 200;               // Process noise

Matrix <1, 1> inv_buff;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Ultrasonic sensor

  //flushing the transmitter
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  delayMicroseconds(10);

  // Kalman filter
  z(0) = distance;
  xt = A * xt;

  // Gain
  inv_buff = H * Pp * (~H) + R;
  bool is_invertible = Invert(inv_buff);
  G = Pp * (~H) * inv_buff;

  // Estimation
  xe = xp + G * (z - (H * xp));
  Pe = Pp + G * R * (~G);

  // Prediction
  xp = A * xe;
  Pp = A * Pe * (~A) + Q;

  Serial.print(xt(0));
  Serial.print(",");
  Serial.print(z(0));
  Serial.print(",");
  Serial.println(xe(0));
  delay(1000 * dt);
}
