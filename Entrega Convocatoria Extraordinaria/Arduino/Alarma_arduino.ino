#define trig 2 // emisor señal
#define echo 3 // receptor señal
#define buzzer 12 // alarma

#define led1 8  // led1

#define led2 7 // led2

char caracter;
String comando;
float duracion, distancia;


void setup() {
  pinMode(trig, OUTPUT); // emisor
  pinMode(echo, INPUT); // receptor
  pinMode(buzzer, OUTPUT); 

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

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
        digitalWrite(led2, HIGH);

        
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
          digitalWrite(led1, HIGH);
          
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
          digitalWrite(led1, LOW);

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
          
  
} else {
  digitalWrite(led2, LOW); 
}

 
}
