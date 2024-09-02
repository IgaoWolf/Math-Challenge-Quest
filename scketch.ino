#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Inicialização dos LCDs
LiquidCrystal_I2C lcd1(0x27, 16, 2);  // LCD 1 - Endereço 0x27
LiquidCrystal_I2C lcd2(0x26, 16, 2);  // LCD 2 - Endereço 0x26

// Definição dos pinos dos botões
const int btnNextMode = 13;  // Botão para passar os modos de jogo
const int btnSelectMode = 12;  // Botão para selecionar o modo de jogo
const int btnZero = 10;
const int btnOne = 9;
const int btnClear = 8;
const int btnSubmit = 7;

int currentMode = 0; // Variável para armazenar o modo de jogo atual
unsigned long startTime;
int score = 0;
int level = 1;
int correctAnswer;  // Agora, a resposta correta é um número inteiro entre 0 e 100
String input = ""; // Armazena a resposta do usuário em binário

void setup() {
  // Configuração dos pinos dos botões
  pinMode(btnNextMode, INPUT_PULLUP);
  pinMode(btnSelectMode, INPUT_PULLUP);
  pinMode(btnZero, INPUT_PULLUP);
  pinMode(btnOne, INPUT_PULLUP);
  pinMode(btnClear, INPUT_PULLUP);
  pinMode(btnSubmit, INPUT_PULLUP);

  // Inicialização dos LCDs
  Wire.begin();  // Inicializa o I2C
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  lcd1.print("Modo: Arcade");
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Score: 0");
}

void loop() {
  // Verifica qual botão foi pressionado
  if (digitalRead(btnNextMode) == LOW) {
    changeMode();
    delay(300);
  }
  if (digitalRead(btnSelectMode) == LOW) {
    startGame();
    delay(300);
  }
}

void changeMode() {
  currentMode = (currentMode + 1) % 4; // Alterna entre os 4 modos
  lcd1.clear();
  switch (currentMode) {
    case 0:
      lcd1.print("Modo: Arcade");
      break;
    case 1:
      lcd1.print("Modo: Timer");
      break;
    case 2:
      lcd1.print("Modo: Memoria");
      break;
    case 3:
      lcd1.print("Modo: Hardcore");
      break;
  }
}

void startGame() {
  lcd1.clear();
  score = 0;
  level = 1;
  switch (currentMode) {
    case 0:
      startArcadeMode();
      break;
    case 1:
      startTimerMode();
      break;
    case 2:
      startMemoryMode();
      break;
    case 3:
      startHardcoreMode();
      break;
  }
}

// Implementação do Modo Arcade

void startArcadeMode() {
  lcd1.clear();
  lcd2.clear();
  lcd1.print("Arcade Mode");
  delay(1000);
  nextQuestion();
}

void nextQuestion() {
  lcd1.clear();
  int num1, num2;
  char operations[] = {'+', '-', '*', '/'};
  char operation;
  do {
    num1 = random(0, 101);  // Gera número aleatório entre 0 e 100
    num2 = random(1, 101);  // Gera número aleatório entre 1 e 100 para evitar divisão por zero
    operation = operations[random(0, 4)]; // Escolhe uma operação aleatória

    switch (operation) {
      case '+':
        correctAnswer = num1 + num2;
        break;
      case '-':
        correctAnswer = num1 - num2;
        break;
      case '*':
        correctAnswer = num1 * num2;
        break;
      case '/':
        if (num1 % num2 == 0) {  // Verifica se a divisão resulta em um número inteiro
          correctAnswer = num1 / num2;
        } else {
          correctAnswer = -1; // Marca como inválido se o resultado não for um número inteiro
        }
        break;
    }

  } while (correctAnswer < 0 || correctAnswer > 100 || (operation == '/' && num1 % num2 != 0));

  lcd1.setCursor(0, 0);
  lcd1.print(num1); 
  lcd1.print(" ");
  lcd1.print(operation);
  lcd1.print(" ");
  lcd1.print(num2); 
  lcd1.setCursor(0, 1);
  lcd1.print("Resp: ");
  input = ""; // Reseta a entrada do usuário

  waitForInput();
}

void waitForInput() {
  while (true) {
    if (digitalRead(btnZero) == LOW) {
      input += "0";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      delay(300);
    }
    if (digitalRead(btnOne) == LOW) {
      input += "1";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      delay(300);
    }
    if (digitalRead(btnClear) == LOW) {
      input = "";
      lcd1.setCursor(6, 1);
      lcd1.print("    ");  // Limpa a área da resposta
      delay(300);
    }
    if (digitalRead(btnSubmit) == LOW) {
      checkAnswer();
      delay(300);
      break;
    }
  }
}

void checkAnswer() {
  int userAnswer = strtol(input.c_str(), NULL, 2);  // Converte a entrada binária para um número inteiro
  if (userAnswer == correctAnswer) {
    score += 10;  // Incrementa a pontuação
    level++;      // Aumenta o nível
    lcd1.clear();
    lcd1.print("Correto!");
    delay(1000);
  } else {
    score -= 10;  // Diminui a pontuação
    lcd1.clear();
    lcd1.print("Errado!");
    delay(1000);
  }
  updateScore();
  nextQuestion();
}

void updateScore() {
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Score: ");
  lcd2.print(score);
}

// Outras funções de modo de jogo

void startTimerMode() {
  // Lógica do Modo Timer
}

void startMemoryMode() {
  // Lógica do Modo Memória
}

void startHardcoreMode() {
  // Lógica do Modo Hardcore
}

int selectTimer() {
  // Lógica para selecionar o tempo
  return 1; // Retorna o tempo selecionado em minutos
}
