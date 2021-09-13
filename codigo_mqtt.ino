#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 



const char* ssid = "Nome da Rede";                                
const char* password = "Senha da Rede";                                    
const char* mqtt_server = "Server MQTT"; //Exemplo: broker.mqtt-dashboard.com                 
String Data;
int tempEspera = 5000;
int val = 0;


WiFiClient espClient;                                                   
PubSubClient client(espClient);                                         
unsigned long ultimaMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup() {                                                          
  pinMode(BUILTIN_LED, OUTPUT);                                         
  Serial.begin(115200);                                                 
  setup_wifi();                                                         
  client.setServer(mqtt_server, 1883);                                  
  client.setCallback(callback);                                         
}

void setup_wifi() {                                                     

  delay(10);                                                            
  Serial.println();                                                     
  Serial.print("Conectando com Usuário:");                                       
  Serial.println(ssid);                                                 
             
  WiFi.begin(ssid, password);                                           
 
  while (WiFi.status() != WL_CONNECTED) {                               
    delay(500);                                                         
    Serial.print(".");                                                  
  }
  randomSeed(micros());
  Serial.println();                                                     
  Serial.println("Conexão Concluída com Sucesso");                                     
  Serial.println("Endereço de IP: ");                                   
  Serial.println(WiFi.localIP());                                       
}

void callback(char* topic, byte* payload, unsigned int length) {        
  Serial.print("Mensagem recebida [");                                  
  Serial.print(topic);                                                  
  Serial.print("] ");                                                   
  for (int i = 0; i < length; i++) {                                    
    Serial.print((char)payload[i]);                                     
  }
  Serial.println();                                                     

  if ((char)payload[0] == '1') {                                        
    digitalWrite(BUILTIN_LED, LOW);                                     
  } else {                                                              
    digitalWrite(BUILTIN_LED, HIGH);                                    
  }

}

void reconnect() {                                                       
  while (!client.connected()) {                                          
    Serial.print("Aguardando conexão MQTT...");                          
    if (client.connect("ESP8266Client")) {                               
      Serial.println("conectado");                                       
      client.publish("publicacao_alimentador", msg);    
      client.subscribe("subscricao_alimentador");                         
    } else {                                                             
      Serial.print("falhou, rc=");                                       
      Serial.print(client.state());                                      
      Serial.println(" tente novamente em 5s");                          
      delay(5000);                                                       
    }
  }
}
void loop() {                                                            

  if (!client.connected()) {                                             
    reconnect();
  }
  client.loop();                                                         
  
  while(Serial.available()==0){
  }
  long now = millis();                                                   
  if (now - ultimaMsg > tempEspera) {                                            
    ultimaMsg = now;                                                       
    
    Data=Serial.read();
    
    //if(indexOf("RFID",Data)>0 or indexOf("ALMD",Data)>0 or indexOf("CMRA",Data)>0){
      //snprintf(msg, 75, Data,val);               
      snprintf (msg, 75, "hello world #%ld", val);
      Serial.print("Publicando mensagem: ");                                  
      Serial.println(msg);                                                 
      client.publish("publicacao_alimentador", msg);                        
    //}
  }
}
