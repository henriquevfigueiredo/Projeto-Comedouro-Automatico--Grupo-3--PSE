Foi utilizada a plataforma do ESP8266 NodeMCU V3. A utilização do Arduino como cliente MQTT pode ser feita seguindo a fonte https://www.dobitaobyte.com.br/como-usar-mqtt-com-arduino/ (com mais detalhes para configuração) : 

 

Cujo código envolve troca do loop por :


void setup()

{

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {

    Serial.println("CONNECTING...");

    delay(300);

  }

  init_hardware();

  init_mqtt();

}

 

void loop()

{

  mqtt->loop();

}


 

Para o teste com o ESP8266 foi utilizada a placa Generic ESP8266 Module:

Para inseri-la basta incluir a mesma na IDE do Arduino ( Arquivo>Preferências> Adicionar URLs adicionais de gerenciadores de placa com o código: 



http://arduino.esp8266.com/stable/package_esp8266com_index.json


e clicar em OK para confirmar).

Além disso, é utilizada a biblioteca PubSubClient que é baixada pela própria IDE do Arduino em:

Ferramentas>Gerenciar Bibliotecas> pesquisar por PubSubClient (selecionar a biblioteca feita por Nick O’Leary)

Após inserir a biblioteca, basta seguir o exemplo do código (em anexo) e compilá-lo no módulo ESP8266 ( lembrando que o mesmo é conectado ao PC via cabo USB tipo A x USB micro B). Nesse código de validação é seguido o procedimento:


	
 Inclusão das bibliotecas;
	
 Definição da Rede;
	
 Definição do Server MQTT;
	
 Definição das variáveis de informação recebida e tempo mínimo de espera;
	
 Inicialização do Cliente Wi-Fi;
	
 Definição do BUFFER para mensagens.
	
 void setup_wifi() é a função que faz a conexão do esp à rede Wi-Fi, usando o ssid e password definidas anteriormente. O esp fica em loop até a conexão ser concluída.
	
 void callback(***) é a função que realiza a leitura de novas informações postadas no tópico passado. Após recebida, é verificada se a mensagem é de alguma das três tags únicas.
	
 void reconnect() é a função que realiza a reconexão ao servidor caso a comunicação falhe, retornando também o tipo de falha. 
	
 void setup() é a função que realiza as inicializações da rotina, definindo a função callback ao cliente, realizando a conexão com o servidor MQTT e a conexão Wi-Fi. 
	
 void loop() é a função que realiza o loop do sistema, verificando se o mesmo está conectado e, caso receba uma mensagem e caso a mensagem seja válida, envia a mensagem recebida ao servidor.


Ao rodar o código o mesmo irá iniciar a comunicação , após escrita da mensagem o hash da mensagem é verificado e o cliente finaliza o programa.
