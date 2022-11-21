// EXPERIMENTOTECA 2022 -- CALCULADORA QUEBRADA -- ELIO

int buzzer = 10;

#include <LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

#include <Keypad.h>

const byte Linhas = 4;                            // Número de Linhas
const byte Colunas = 4;                           // Número de colunas

char Teclado [Linhas][Colunas]={                  // Declaramos o teclado.
{'y','2','3','A'},
{'y','y','y','B'},
{'y','y','y','C'},
{'*','y','#','D'}};

byte pinosLinhas[Linhas]={9,8,7,6};               // Configuração dos pinos das linhas
byte pinosColunas[Colunas]={5,4,3,2};             // Configuração dos pinos das colunas
Keypad keyp = Keypad(makeKeymap(Teclado),pinosLinhas, pinosColunas, Linhas, Colunas); // Criamos o objeto teclado.

bool inicio = true,                             // Variáveis de controle 
      final = false,
numDigitado = false;                          

String num1, num2;                               // Armazenam os números digitados 1 e 2 
int resultado;                                   // Armazena o resultado.
char op;                                         // Armazena a operação



void setup()
{
  pinMode(buzzer, OUTPUT);  
  lcd.begin(16,2);
  delay (100);
  lcd.setCursor(2,0);
  lcd.print("Calculadora");
  lcd.setCursor(3,1);
  lcd.print("Quebrada");
  delay (3000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Operacoes:");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("A = somar"); 
  lcd.setCursor(0,1);
  lcd.print("C = multiplicar");
  delay (3000); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vamos comecar?");
 
  delay(500);
  lcd.clear();
}



void loop()
{
  char key = keyp.getKey();                        // Obtemos a tecla pressionada e armazenamos na variavel key
  delay(50);
  
  if(key != NO_KEY && ( key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {                                                // Se clicou alguma tecla, amazene seu numero
    if(inicio)                                
    { 
      num1 = num1 + key;                           // Armazena o primeiro numero
      lcd.setCursor(0,0);
      lcd.print(num1);                            
      numDigitado = true;   
      tone(buzzer, 294, 70);
    }
    else
    {
      num2 = num2 + key;                            // Armazena o segundo numero
      lcd.setCursor(0,1);
      lcd.print(num2);                             
      final = true;                                
    }
 }
  
 if (inicio && numDigitado == 1 && key != NO_KEY && (key == 'A' || key == 'B' || key == 'C' || key == 'D'))
 {                                                // Se clicou numa tecla de Operação
   inicio = false;  
   op = key;  
   char printOp;
   if     (op=='A')printOp = '+';
   else if(op=='B')printOp = '+';
   else if(op=='C')printOp = 'x';
   else if(op=='D')printOp = 'x';
   else            printOp = '?';
   lcd.setCursor(8,0);
   lcd.print("Op:");
   lcd.setCursor(12,0);
   lcd.print(printOp);                                   
   numDigitado = false;
 }
  
 if(final && key !=NO_KEY && key == '#')          // Se clicou no botão de igual (=) "#"
 {
    if (op == 'A')                                // Operação de soma
    {resultado = num1.toInt() + num2.toInt();}    // Converte de string para inteiro
    if (op == 'B')                                // Operação de subtração
    {resultado = num1.toInt() + num2.toInt();}
    if (op == 'C')                                // Operação de multiplicação
    {resultado = num1.toInt() * num2.toInt();}
    if (op == 'D')                                // Operação de divisão
    {resultado = num1.toInt() * num2.toInt();}
    
    
    lcd.setCursor(8,1);
    lcd.print("R :");
    lcd.setCursor(11,1);
    lcd.print((int)resultado);   
 }

 if(key !=NO_KEY && key == '*')                   // Se clicou, limpa tudo p/ poder re-iniciar
 {                                                
  inicio = true;
  final = false;
  numDigitado = false;
  num1 = "";
  num2 = "";
  resultado = 0;
  op = ' ';
  lcd.clear();
 }

if(key !=NO_KEY && key == 'y')                   // Se clicou, operaciona o resultado;
 {                                                
  inicio = true;
  final = false;
  numDigitado = true;
  num1 = (int)resultado;
  num2 = "";
  //resultado = 0;
  op = ' ';
  lcd.clear();
  num1 = resultado;                           // Restaura o resultado da ultima conta
  lcd.setCursor(0,0);
  lcd.print(num1);                            
  numDigitado = true;   
 }
 
}
