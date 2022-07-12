#include<Keypad.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);

//Key Setup
#define Password_Length 7
//give enough room for six chars + NULL char
char Data[Password_Length];// 6 is the number of chars it can hold + hold the null char =7
char Master[Password_Length] = "JAE421";
byte data_char =0, data_count, master_count = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = //Maps the rows and columns 
{
  {'A','B','C','1'},
  {'D','E','F','2'},
  {'G','H','I','3'},
  {'*','J','#','4'}
};
bool pin = true;
bool pinStatus = false, readerStatus =false,amountStatus = false;
byte rowPins[ROWS] = {10,11,12,13};
byte colPins[COLS] = {A0,A1,A2,A3};

Keypad customKeypad(makeKeymap(keys),rowPins, colPins, ROWS,COLS);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);

  if(!customKey)
  {
    lcd.setCursor(0,0);
    lcd.print("Enter your Pin: ");
  }
}
void(*resetFunc)(void)=0;//initialized at address 0

void loop() {
  // put your main code here, to run repeatedly:
  getPin();
}
void clearData(){
  while(data_count!=0)
  {
    Data[data_count--]=0; //clear array for new data
  }
  return;
}
void getPin()
{
  customKey = customKeypad.getKey();
  if(customKey)
  {
    Data[data_count]=customKey;
    lcd.setCursor(data_count,1);
    if(customKey =='*')
    {
      lcd.clear();
      resetFunc();
      data_count = 0;
    }
    lcd.print(Data[data_count]);
    data_count++;
  }
  if(data_count == Password_Length - 1)
  {
    if(!strcmp(Data, Master))//equal to (strcmp(Data, Master)==0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Correct Pin!");
//      lcd.setCursor(0,1);
//      lcd.print("Welcome!");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wrong Pin!");
      resetFunc();
    }
  }
   //clearData();
  //pinStatus = true;
}
