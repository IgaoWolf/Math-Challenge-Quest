#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do endereço I2C do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C 0x27, display 16x2

// Definindo pinos para botões
#define BOTAO_MENU 11       // Botão 1: Selecionar modos de jogo
#define BOTAO_CONFIG 10     // Botão 2: Selecionar modo de exibição (binário ou decimal)
#define BOTAO_INICIAR 9     // Botão 3: Iniciar jogo
#define BOTAO_ENCERRAR 8    // Botão 4: Encerrar jogo e exibir score
#define BOTAO_0 7           // Botão 5: Entrar '0'
#define BOTAO_1 6           // Botão 6: Entrar '1'
#define BOTAO_ENVIAR 5      // Botão 7: Enviar resposta
#define BOTAO_LIMPAR 4      // Botão 8: Limpar último dígito

// Variáveis globais
int modoAtual = 0; // 0: Arcade, 1: Timer, 2: Memória, 3: Hardcore
bool entradaBinaria = false; // Falso para números decimais, verdadeiro para binários
bool jogoEmAndamento = false;
String respostaUsuario = ""; // Armazena a resposta do usuário

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  // Configura os pinos dos botões como entrada com pull-up interno
  pinMode(BOTAO_MENU, INPUT_PULLUP);
  pinMode(BOTAO_CONFIG, INPUT_PULLUP);
  pinMode(BOTAO_INICIAR, INPUT_PULLUP);
  pinMode(BOTAO_ENCERRAR, INPUT_PULLUP);
  pinMode(BOTAO_0, INPUT_PULLUP);
  pinMode(BOTAO_1, INPUT_PULLUP);
  pinMode(BOTAO_ENVIAR, INPUT_PULLUP);
  pinMode(BOTAO_LIMPAR, INPUT_PULLUP);

  exibirModoAtual(); // Exibe o modo inicial ao iniciar
}

void loop() {
  // Verifica se o botão de menu foi pressionado para mudar de modo
  if (digitalRead(BOTAO_MENU) == LOW) {
    delay(200); // Debounce
    modoAtual = (modoAtual + 1) % 4; // Alterna entre 0, 1, 2, 3 (Arcade, Timer, Memória, Hardcore)
    exibirModoAtual();
    delay(300);
  }

  // Verifica se o botão de configuração foi pressionado para mudar o modo de entrada
  if (digitalRead(BOTAO_CONFIG) == LOW) {
    delay(200); // Debounce
    entradaBinaria = !entradaBinaria; // Alterna entre verdadeiro e falso
    exibirModoEntrada();
    delay(300);
  }

  // Verifica se o botão de iniciar foi pressionado
  if (digitalRead(BOTAO_INICIAR) == LOW) {
    delay(200);
    iniciarJogo();
    delay(300);
  }

  // Verifica se o botão de encerrar foi pressionado
  if (digitalRead(BOTAO_ENCERRAR) == LOW) {
    delay(200);
    encerrarJogo();
    delay(300);
  }

  // Verifica os botões para inserir resposta
  if (digitalRead(BOTAO_0) == LOW && jogoEmAndamento) {
    delay(200);
    respostaUsuario += "0";
    atualizarDisplayResposta();
  }

  if (digitalRead(BOTAO_1) == LOW && jogoEmAndamento) {
    delay(200);
    respostaUsuario += "1";
    atualizarDisplayResposta();
  }

  // Verifica se o botão de enviar foi pressionado
  if (digitalRead(BOTAO_ENVIAR) == LOW && jogoEmAndamento) {
    delay(200);
    verificarResposta();
    delay(300);
  }

  // Verifica se o botão de limpar foi pressionado
  if (digitalRead(BOTAO_LIMPAR) == LOW && jogoEmAndamento) {
    delay(200);
    if (respostaUsuario.length() > 0) {
      respostaUsuario.remove(respostaUsuario.length() - 1);
      atualizarDisplayResposta();
    }
  }
}

// Função para exibir o modo de jogo atual
void exibirModoAtual() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (modoAtual) {
    case 0:
      lcd.print("Modo: Arcade");
      break;
    case 1:
      lcd.print("Modo: Timer");
      break;
    case 2:
      lcd.print("Modo: Memoria");
      break;
    case 3:
      lcd.print("Modo: Hardcore");
      break;
  }
}

// Função para exibir o modo de entrada
void exibirModoEntrada() {
  lcd.setCursor(0, 1); // Segunda linha do LCD
  if (entradaBinaria) {
    lcd.print("Entrada: Binario ");
  } else {
    lcd.print("Entrada: Decimal ");
  }
}

// Função para iniciar o jogo
void iniciarJogo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando Jogo...");
  delay(1000);
  jogoEmAndamento = true;
  respostaUsuario = "";
  // Aqui podemos adicionar a lógica de cada modo de jogo
}

// Função para encerrar o jogo e exibir o score
void encerrarJogo() {
  jogoEmAndamento = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogo Encerrado");
  lcd.setCursor(0, 1);
  lcd.print("Score: X pts"); // Substituir "X" pela pontuação real
  delay(2000);
  exibirModoAtual(); // Retorna ao menu de seleção
}

// Função para atualizar o display com a resposta do usuário
void atualizarDisplayResposta() {
  lcd.setCursor(0, 1);
  lcd.print("Resp: " + respostaUsuario);
}

// Função para verificar a resposta do usuário
void verificarResposta() {
  // Adicione a lógica para verificar a resposta do usuário aqui
  // Por exemplo, comparar com a resposta correta e mostrar feedback
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Verificando...");
  delay(1000);
  // Exemplo de lógica fictícia para resposta correta
  if (respostaUsuario == "1010") { // Supondo que a resposta correta seja "1010" para teste
    lcd.setCursor(0, 0);
    lcd.print("Correto!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Errado!");
  }
  delay(1000);
  respostaUsuario = ""; // Reseta a resposta do usuário
  atualizarDisplayResposta();
}
