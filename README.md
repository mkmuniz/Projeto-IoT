# Projeto-IoT

 Código fonte do sistema de Alimentador Automático feito em Arduino UNO R3 e NodeMCU com conexão ao broker MQTTP. O objetivo do projeto é auxiliar donos de pets a alimentar seus animais quando não estão disponíveis em casa.
 
# Principais componentes

- Arduino UNO R3
- NodeMCU ESP8266
- Servo Motor S3003
- Sensor de movimento PIR
- Placa protoboard
- Fonte de alimentação 5V bivolt

# Como funciona?

 Há um componente chamado sensor de movimento PIR, ele permite detectar a aproximação de algum ser vivo a uma distância de 6 metros, quando ele detecta, envia um sinal por seu cabo até a porta digital da placa microcontroladora que ele está conectado. Essa informação pode desencadear um efeito em cadeia, neste caso, o de fazer o Servo Motor se movimentar, assim liberando a passagem da comida que está armazenada em um recipiente acima e maior, deixando a ração cair em um recipiente menor logo a baixo. Algumas imagens de exemplo de alimentadores automáticos:

![image](https://user-images.githubusercontent.com/65512888/170822442-515bfc90-d657-447a-af9d-80dd03b04657.png)

![image](https://user-images.githubusercontent.com/65512888/170822446-01c94279-92d8-4058-93b4-fa43c21e44e7.png)

# O que fazer?

1 - Você deve estabelecer uma conexão a rede WiFi utilizando o NodeMCU ESP8266 e então, conectar-se ao broker gratuito disponível em **http://www.hivemq.com/demos/websocket-client/** e **http://www.mqtt-dashboard.com/index.html**. Siga os comentários no código-fonte do respositório para saber
quais variáveis preencher e assim, estabelecer uma conexão.

2 - Após estiver conectado a internet e ao broker, conecte o componente Sensor PIR, utilize o código-fonte. Veja essa imagem abaixo de como conectar os fios:
![image](https://user-images.githubusercontent.com/65512888/170816881-e585386d-6bdf-481d-aca3-cf12aaa0b84c.png)

3 - Conecte o Servo Motor, pegue o loop do código onde toda vez que o Sensor PIR detectar um movimento, o Servo Motor entenderá a informação e irá agir logo em seguida.
![image](https://user-images.githubusercontent.com/65512888/170816920-8d944aa6-7adf-4ba6-a4aa-180a10c0ade3.png)

4 - Utilize a placa Arduino UNO R3 para gerar energia aos componentes, ligue apenas os cabos de VCC e GND de cada componente a placa, enquanto a porta digital será responsável pela NodeMCU ESP8266.

5 - Escolha itens para costumizar o projeto, pegue um recipiente que será colocado na parede e onde você guardará a ração para que seja despejada, em baixo dela, outro recipiente como um ponte para ração de cães. Pegue uma plataforma que será colocada sobre a hélice do Servo Motor, ela segurará a ração e tampará a saída dela.

6 - Seja criativo! Você pode mudar os recipientes para de outros animais e até diminuir o espaço que o projeto ocupará. Escolher itens recicláveis para segurar os itens e etc.

# Plataformas utilizadas

 A principal plataforma utilizada para a codificação foi o ambiente de desenvolvimento do Arduino que se baseia nas linguagens C e C++.
 ![image](https://user-images.githubusercontent.com/65512888/170822299-790b8eef-73f8-44d5-95cf-e9aaa26ee0ec.png)
 
 Outras opções de ambientes são o Visual Studio e NetBeans.
