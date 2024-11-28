int cor = A7;        // Porta A0 para ler a corrente
int tomada1 = 2;
float I = 0;         // Variável para leitura do valor analógico
float corrente = 0.0;// Variável para armazenar a corrente convertida (em mA)
int valorPWM = 0;    // Variável para armazenar o valor de saída PWM
bool isCasaLigada = false;

void setup() {
    Serial.begin(9600);           // Inicializa a comunicação serial
    pinMode(tomada1, OUTPUT);     // Define a porta como saída
}

void loop() {
  I = analogRead(cor);  // Lê o valor do sensor de corrente na porta A0
  
  // Calcula a corrente em mA
  corrente = (I * 5.0) / 1024.0;
  
  // Serial.print("Corrente: ");
  // Serial.print(corrente);
  // Serial.println(" mA");

  // Verifica se a corrente está acima de 4.0 mA
  if (corrente > 4.8) {
    digitalWrite(tomada1, HIGH); //Relé fecha circuito
    isCasaLigada = false;
  } else {
    digitalWrite(tomada1, LOW); // Relé abre circuito
    isCasaLigada = true;
  }

   // Envia as variáveis no formato "numero,estado\n"
    Serial.print(corrente);
    Serial.print(",");
    Serial.println(isCasaLigada); // Converte o booleano para "1" ou "0"

}