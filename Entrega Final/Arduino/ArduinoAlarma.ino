#define trig 2 // emisor señal
#define echo 3 // receptor señal
#define buzzer 12 // alarma
char caracter;
  String comando;
  float duracion, distancia;


void setup() {
  pinMode(trig, OUTPUT); // emisor
  pinMode(echo, INPUT); // receptor
  pinMode(buzzer, OUTPUT); 

  Serial.begin(9600);
  
}

void loop()
{
  
  while (Serial.available() > 0)
  {
    caracter = Serial.read();
    comando.concat(caracter);
    delay(10);
  }
  if (comando.equals("a") == true)
  {
        digitalWrite(trig, LOW);
        delay(2);
  
        digitalWrite(trig, HIGH);
        delay(10);
        digitalWrite(trig, LOW);
  
        duracion = pulseIn(echo, HIGH);  // calculo de la distancia
        distancia = (duracion/2)*0.0343;  // en este caso la medimos en cm/ms
        Serial.println(distancia);

        if (distancia < 20)  // x será la distancia que medirá el sensor en reposo
        {
          tone(buzzer, 1000);  // alarma suena con fecuencia de 1000 Hz
          delay(200); // la alarma sonará durante 0,2 segundos

          tone(buzzer, 3000);  // alarma suena con fecuencia de 3000 Hz
          delay(200);  // la alarma sonará durante 0,2 segundos

          tone(buzzer, 1000);  
          delay(200); 
    
          tone(buzzer, 3000);
          delay(200);

          tone(buzzer, 1000);  
          delay(200); 

          tone(buzzer, 3000);
          delay(200);

          tone(buzzer, 1000);  
          delay(200); 
    
          tone(buzzer, 3000);
          delay(200);

          tone(buzzer, 1000);  
          delay(200); 

          tone(buzzer, 3000);
          delay(200);

          Serial.write("c");

          } else {
            noTone(buzzer); // la alarma no suena
          }
          
  
}
 
}
