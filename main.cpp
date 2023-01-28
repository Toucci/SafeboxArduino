#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#define ledVermelho 3
#define ledVerde 2

int contador = 0;

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);//pinos do led

String senha = "060919";//senha correta
String buf = "";//armazenamento da senha digitada no teclado
int pinoServo = 13;
Servo s;
int i = 0;//quantidade de digitos da senha que serão armazenados


int buzzer = 12;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11,10,9,8};
byte colPins[COLS] = {7,6,5,4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);//acionamento do serial
  s.attach(pinoServo);//acionamento do pino servo
  s.write(0);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor (0,0);
  lcd.print("INICIALIZANDO... ");//vai aparecer no lcd
  Serial.println("Inicializando...");//vai aparecer no monitor serial
  delay(1000);
}

void loop(){
  
      i=0;
      Serial.println("senha: ");
      lcd.clear();
      buf = "";
      password();//caso for pressionado o * essa função inicia
}

void piscaLed(){
  int lm = 0;
  while (lm < 5){
    lm = lm + 1;
    digitalWrite(ledVermelho, HIGH);
    delay(1000);
    digitalWrite(ledVermelho, LOW);
    delay(1000);
  }
  }
 

void password(){
  while (i<6){// se a senha chegar no 5 ela da como incorreto
    lcd.setCursor (0,0);
    lcd.print("SENHA: ");
    
    char key = keypad.getKey();
    if (key != NO_KEY){
      buf+= key;
        lcd.print(buf);
      i++;
    }
}
  Serial.println(buf);
  
  if(buf == senha){
    lcd.setCursor (0,1);
    lcd.print("COFRE ABERTO");
    Serial.println("Cofre aberto");
    delay(1000);
    digitalWrite(ledVerde, HIGH);//aciona o led
    delay(500);
    s.write(180);
    delay(5000);//cofre permanece aberto por 5 segundos
    s.write(0);
    lcd.clear();
    digitalWrite(ledVerde,LOW);//desliga o led
    lcd.setCursor (0,0);
  }else{
    lcd.setCursor (0,0);
    lcd.print("SENHA INCORRETA");
    Serial.println("Senha incorreta");
    contador++;
    delay(500);
    lcd.clear();
    delay(1000);
  }
  if(contador > 3){
    lcd.setCursor(1,0);
    lcd.print("Acesso Negado!");
    tone(buzzer,440);
    piscaLed();
    delay(500);
    noTone(buzzer);
    lcd.setCursor (0,1);
  }
  
}