#include <WiFi.h>                // Biblioteca para conexão Wi-Fi
#include "AdafruitIO_WiFi.h"     // Biblioteca do Adafruit IO para ESP32

// Configurações do Adafruit IO
#define IO_USERNAME  "" // Substitua pelo seu usuário Adafruit IO
#define IO_KEY       ""          // Substitua pela sua chave do Adafruit IO

// Configurações de Wi-Fi
#define WIFI_SSID    ""                       // Substitua pelo nome da sua rede Wi-Fi
#define WIFI_PASS    ""                      // Substitua pela senha da sua rede Wi-Fi

// Inicializa o Adafruit IO WiFi
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Configurações de feeds no Adafruit IO
AdafruitIO_Feed *correnteFeed = io.feed("corrente");  // Feed para enviar os valores da corrente
AdafruitIO_Feed *statusFeed = io.feed("EnergiaFabrica");      // Feed para enviar o status (Ligado/Desligado)


String numero ;         // Variável numérica recebida
String estado ;    // Variável booleana recebida
String dados = "";      // Buffer para armazenar dados recebidos


void setup() {
    // Configura a comunicação serial
    Serial.begin(9600);
    Serial.println("Iniciando...");

    // Conecta ao Adafruit IO
    Serial.print("Conectando ao Adafruit IO...");
    io.connect();

    // Aguarda a conexão
    while (io.status() < AIO_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    // Mensagem de sucesso
    Serial.println("\nConectado ao Adafruit IO!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

unsigned long ultimaPublicacao = 0; // Armazena o tempo da última publicação
const unsigned long intervaloPublicacao = 6000; // 10 segundos (em milissegundos)

void loop() {
    // Mantém a conexão com o Adafruit IO
    io.run();

    // Verifica se há dados disponíveis
    while (Serial.available() > 0) {
        char caractere = Serial.read(); // Lê o próximo caractere
        if (caractere == '\n') { // Fim da linha (dados completos recebidos)
            // Divide os dados usando a vírgula como delimitador
            int separador = dados.indexOf(',');
            if (separador != -1) {
                numero = dados.substring(0, separador); // Primeiro valor (numérico)
                estado = (dados.substring(separador + 1)); // Segundo valor (booleano)

                unsigned long tempoAtual = millis(); // Obtém o tempo atual
                if (tempoAtual - ultimaPublicacao >= intervaloPublicacao) {
                    ultimaPublicacao = tempoAtual; // Atualiza o tempo da última publicação

                    // Publica os dados nos feeds
                    correnteFeed->save(numero);
                    statusFeed->save(estado);

                    // Exibe os valores recebidos no Monitor Serial
                    Serial.println("Dados enviados para Adafruit IO:");
                    Serial.print("Corrente: ");
                    Serial.println(numero);
                    Serial.print("Estado: ");
                    // Serial.println(estado == "true" ? 1 : 0);
                    Serial.println(estado);
                    Serial.println();
                }
            }
            dados = ""; // Limpa o buffer
        } else {
            dados += caractere; // Concatena o caractere no buffer
        }
    }
}