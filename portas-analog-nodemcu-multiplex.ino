// Programa: Ampliando as portas analógicas do NodeMCU com multiplexador
// Autor : Leandro Chernicharo (p/ FILIPEFLOP.COM)

/*
 * Constante com o número de pinos (bits) do multiplexador
 * que serão utilizados para controlar a porta selecionada.
 * Caso você use um multiplexador diferente do que eu usei,
 * como o 74HC4051, por exemplo, que usa 3 bits para isso,
 * basta alterar aqui.
*/
#define NUM_PINOS_SELECAO_CANAL 2

/*
 * Pinos dos sensores analógicos. Os números representam as
 * portas dentro do multiplexador. Neste caso aqui, seria o
 * seguinte:
 *  SOM_PIN está na porta 2 de um dos canais (X2 ou Y2)
 *  LDR_PIN está na porta 3 de um dos canais (X3 ou Y3)
 * Estas constantes são utilizadas para controlar a abertura
 * correspondente antes da leitura dos dados do sensor.
 */
#define SOM_PIN 2
#define LDR_PIN 3

/*
 * Vetor com os pinos de seleção de canal no multiplexador.
 * Cada porta no vetor representa o pino ao qual está conectada:
 * D2 -> Pino A
 * D1 -> Pino B
 */
const int pinosSelecaoCanal[] = {D2, D1};

void setup() {
  Serial.begin(9600);
  initPinosSelecaoCanal();
}

void loop() {
  /*
   * Antes da leitura dos dados na porta analógica (A0) do
   * NodeMCU, é preciso definir qual porta do multiplexador
   * será lida. Assim, sempre chamamos a função correspondente
   * para realizar essa tarefa para nós.
   */
  ativarPortaAnalogica(SOM_PIN);
  int som = analogRead(A0);

  /*
   * Observe que a leitura é feita sempre na mesma porta
   * física do NodeMCU. O que vai mudar é a origem do sinal
   * a partir do multiplexador.
   */
  ativarPortaAnalogica(LDR_PIN);
  int luz = analogRead(A0);

  Serial.print("Som: ");
  Serial.print(som);
  Serial.print("\tLuz: ");
  Serial.println(luz);

  delay(5000);
}

/*
 * Esta função abre a porta do multiplexador que desejamos
 * utilizar a partir do número do pino passado para ela. É
 * por isso que definimos as constantes dessas portas no
 * início do programa.
 */
void ativarPortaAnalogica(int porta) {
  /*
   * De acordo com a tabela de portas do 74HC4052,
   * a porta 2 (som) é aberta com o pino A LOW e o pino
   * B HIGH. A porta 3 (luz) é aberta com os A e B HIGH.
   */
  if(porta == SOM_PIN) {
      digitalWrite(pinosSelecaoCanal[0], LOW);
      digitalWrite(pinosSelecaoCanal[1], HIGH);

  } else {
      digitalWrite(pinosSelecaoCanal[0], HIGH);
      digitalWrite(pinosSelecaoCanal[1], HIGH);
  }
}

/*
 * Esta função é muito importante. Ela coloca todas as portas
 * digitais do NodeMCU utilizadas para controlar os pinos
 * (A e B, neste caso) em modo de saída (OUTPUT). Dependendo
 * da porta que você escolher, seu comportamento padrão pode
 * ser o de entrada (INPUT), o que fará com que o programa não
 * funcione corretamente. Assim, para garantir o funcionamento
 * independente da porta, sempre chame esta função no setup.
 */
void initPinosSelecaoCanal() {
  for(int i = 0; i < NUM_PINOS_SELECAO_CANAL; i++) {
    pinMode(pinosSelecaoCanal[i], OUTPUT);
  }
}
