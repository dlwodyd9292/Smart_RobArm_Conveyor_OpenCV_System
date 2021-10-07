#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include <Wire.h>

#define AP_SSID "iotsystem1"
#define AP_PASS "iotsystem10"
#define SERVER_NAME "192.168.10.74"
#define SERVER_PORT 5000  
#define LOGID "LJY_SMP"
#define PASSWD "PASSWD"

#define WIFITX 7  //7:TX -->ESP8266 RX
#define WIFIRX 6 //6:RX-->ESP8266 TX

#define CMD_SIZE 50
#define ARR_CNT 5    

#define REDBOX_PIN 3
#define BLUEBOX_PIN 4

SoftwareSerial wifiSerial(WIFIRX, WIFITX); 
WiFiEspClient client;

char sendBuf[CMD_SIZE];

char sendId[10]="LJY_LIN";

bool RedFlag = false;
bool BlueFlag = false;

void setup() 
{
    pinMode(REDBOX_PIN, INPUT);
    pinMode(BLUEBOX_PIN, INPUT);
     
    Serial.begin(115200); //DEBUG

    wifi_Setup();
}

void loop() 
{  
  int Rcur, Bcur, Rbefore = 1, Bbefore = 1;
  static int Rcnt = 0, Bcnt = 0;
  
    Rcur = digitalRead(REDBOX_PIN);
    Bcur = digitalRead(BLUEBOX_PIN);
    delay(1000);
//    Serial.println(cur);

    if(Rcur == LOW && Rbefore == HIGH)
    {
      RedFlag = true;
    }
    Rbefore = Rcur;

    if(Bcur == LOW && Bbefore == HIGH)
    {
      BlueFlag = true;
    }
    Bbefore = Bcur;

   if(RedFlag == true)
  {
    Rcnt++;  
    RedFlag = false;
    sprintf(sendBuf,"[KSP_QT2]SENSOR@%d@n\n", Rcnt);
    Serial.println(sendBuf);
    //delay(1000);
    client.write(sendBuf,strlen(sendBuf));
    client.flush();
  }
  
   if(BlueFlag == true)
  {
    Bcnt++;  
    BlueFlag = false;
    sprintf(sendBuf,"[KSP_QT2]SENSOR@n@%d\n", Bcnt);
    Serial.println(sendBuf);
    //delay(1000);
    client.write(sendBuf,strlen(sendBuf));
    client.flush();
  }
      
  if(client.available()) 
  {
    socketEvent();
  }
  if (!client.connected()) 
  { 
    server_Connect();
  }
}

void socketEvent()
{
  int i=0;
  char * pToken;
  char * pArray[ARR_CNT]={0};
  char recvBuf[CMD_SIZE]={0}; 
  int len;

  static int Rcnt = 0;

  sendBuf[0] ='\0';
  len =client.readBytesUntil('\n',recvBuf,CMD_SIZE); 
  client.flush();
  pToken = strtok(recvBuf,"[@]");
  while(pToken != NULL)
  {
    pArray[i] =  pToken;
    if(++i >= ARR_CNT)
      break;
    pToken = strtok(NULL,"[@]");
  }
  //[KSH_ARD]LED@ON : pArray[0] = "KSH_ARD", pArray[1] = "LED", pArray[2] = "ON"
  if((strlen(pArray[1]) + strlen(pArray[2])) < 16)
  {   
  }
  if(!strncmp(pArray[1]," New",4))  // New Connected
  {
    Serial.write('\n');
    return ;
  }
  else if(!strncmp(pArray[1]," Alr",4)) //Already logged
  {
    Serial.write('\n');
    client.stop();
    server_Connect();
    return ;
  } 
}

void wifi_Setup() 
{
  wifiSerial.begin(19200);
  wifi_Init();
  server_Connect();
}

void wifi_Init()
{
  do {
    WiFi.init(&wifiSerial);
    if (WiFi.status() == WL_NO_SHIELD) {
    }
    else
      break;   
  }while(1);

#ifdef DEBUG_WIFI    
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(AP_SSID);
#endif     
  while(WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {   
#ifdef DEBUG_WIFI  
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(AP_SSID);   
#endif   
  }

  
#ifdef DEBUG_WIFI      
  Serial.println("You're connected to the network");    
  printWifiStatus();
#endif 
}
int server_Connect()
{
#ifdef DEBUG_WIFI     
  Serial.println("Starting connection to server...");
#endif  

  if (client.connect(SERVER_NAME, SERVER_PORT)) {
#ifdef DEBUG_WIFI     
    Serial.println("Connect to server");
#endif  
    client.print("["LOGID":"PASSWD"]"); 
  }
  else
  {
#ifdef DEBUG_WIFI      
     Serial.println("server connection failure");
#endif    
  } 
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
