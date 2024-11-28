# Sistema de Gerenciamento de Energia em Ambientes Industriais

## Descrição Geral
Este projeto implementa um sistema baseado em IoT para monitoramento e controle do consumo de energia em ambientes industriais. Utiliza um Arduino Nano para processar os dados de consumo simulados por um potenciômetro, um módulo relé SPDT para controle da carga e um ESP32 para comunicação com a nuvem via protocolo MQTT. O sistema foi projetado para oferecer automação local e controle remoto, com integração à plataforma io.arkfruit para monitoramento em tempo real.

## Código e Documentação
O código principal está localizado na pasta do repositório e foi desenvolvido na Arduino IDE. O arquivo principal sistema_gerenciamento_energia.ino inclui:

   - Conexão do Arduino Nano com o ESP32 via comunicação serial.
   - Configuração da conexão Wi-Fi.
   - Integração com o protocolo MQTT para envio e recebimento de dados.
   - Lógica de controle da carga com base no consumo energético.

O código permite o monitoramento contínuo do consumo e o controle remoto da carga através de comandos enviados via MQTT.

## Hardware Utilizado
1. **Arduino Nano**:
   - Microcontrolador principal para leitura de dados e controle do relé.
   - Porta USB para alimentação e programação.
2. **ESP32 DevKit V1**:
   - Proporciona conectividade Wi-Fi para comunicação com a nuvem.
   - Configurado para atuar como cliente MQTT.
3. **Relé SPDT**:
   - Controla o estado da carga (lâmpada LED).
   - Acionado automaticamente pelo Arduino com base no consumo.
4. **Potenciômetro**:
   - Simula o consumo energético variando a resistência no circuito.
5. **Lâmpada LED**:
   - Representa a carga conectada ao sistema.
6. **Protoboard 830 pontos e fios jumper**:
   - Usados para conexão de todos os componentes.
7. **Fonte de Alimentação 9V**:
   - Fornece energia para o Arduino Nano e os demais componentes.

## Interfaces e Protocolos de Comunicação
O sistema utiliza o protocolo MQTT para comunicação com a plataforma io.arkfruit. Abaixo estão os tópicos configurados:

- `usuario/feeds/consumo`: Publica os valores de corrente simulada (em mA).
- `usuario/feeds/status`: Publica o estado do relé (Ligado ou Desligado).
- `usuario/feeds/controle`: Permite o controle remoto do relé através de comandos MQTT.

Esses feeds são atualizados automaticamente conforme o consumo energético e as condições de operação do sistema.

## Funcionamento Geral
Monitoramento Local:
O potenciômetro simula o consumo de energia ajustando manualmente os valores de corrente no circuito.
O Arduino Nano lê os valores do potenciômetro pela porta analógica e converte-os para corrente (mA).

Controle Automático do Relé:
O relé é acionado automaticamente pelo Arduino Nano quando a corrente simulada ultrapassa o limite predefinido de 4.8 mA.
O relé liga ou desliga a carga (lâmpada LED) para proteger o sistema contra picos de consumo.

Comunicação com a Nuvem:
O ESP32 conecta-se à rede Wi-Fi configurada e publica os dados de consumo no broker MQTT, permitindo o monitoramento remoto pela plataforma io.arkfruit.

Controle Remoto:
O usuário pode desligar a carga remotamente através da plataforma, enviando comandos MQTT para o Arduino Nano.

Feedback e Visualização:
O estado do sistema e os valores de corrente são enviados para o broker e podem ser visualizados em tempo real na interface da plataforma.

## Vídeo demonstrando o funcionamento
https://youtu.be/UfLT7vVots8