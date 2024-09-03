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
const int btnEndGame = 6; // Novo botão para encerrar o jogo

int currentMode = 0; // Variável para armazenar o modo de jogo atual
unsigned long startTime;
int score = 0;
int level = 1;
int correctAnswer;  // Resposta correta é um número inteiro entre 0 e 100
String input = ""; // Armazena a resposta do usuário em binário
int selectedTime = 1; // Tempo selecionado pelo usuário (em minutos)

void setup() {
  Serial.begin(9600); // Inicializa o Serial Console
  Serial.println("Iniciando sistema...");

  // Configuração dos pinos dos botões
  pinMode(btnNextMode, INPUT_PULLUP);
  pinMode(btnSelectMode, INPUT_PULLUP);
  pinMode(btnZero, INPUT_PULLUP);
  pinMode(btnOne, INPUT_PULLUP);
  pinMode(btnClear, INPUT_PULLUP);
  pinMode(btnSubmit, INPUT_PULLUP);
  pinMode(btnEndGame, INPUT_PULLUP); // Configuração do botão de encerrar o jogo

  // Inicialização dos LCDs
  Wire.begin();  // Inicializa o I2C
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  lcd1.print("Modo: Arcade");
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Score: 0");
  Serial.println("Modo inicial: Arcade");
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
  if (digitalRead(btnEndGame) == LOW) {
    endGame(); // Chama a função para encerrar o jogo
    delay(300);
  }
}

void changeMode() {
  currentMode = (currentMode + 1) % 3; // Alterna entre os 3 modos
  lcd1.clear();
  switch (currentMode) {
    case 0:
      lcd1.print("Modo: Arcade");
      Serial.println("Modo alterado para: Arcade");
      break;
    case 1:
      lcd1.print("Modo: Timer");
      Serial.println("Modo alterado para: Timer");
      break;
    case 2:
      lcd1.print("Modo: Memoria");
      Serial.println("Modo alterado para: Memoria");
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
  }
}

// Implementação do Modo Arcade

void startArcadeMode() {
  lcd1.clear();
  lcd2.clear();
  lcd1.print("Arcade Mode");
  Serial.println("Iniciando Modo Arcade");
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
  Serial.print("Nova operação: ");
  Serial.print(num1);
  Serial.print(" ");
  Serial.print(operation);
  Serial.print(" ");
  Serial.println(num2);
  input = ""; // Reseta a entrada do usuário

  waitForInput();
}

void waitForInput() {
  while (true) {
    if (digitalRead(btnZero) == LOW) {
      input += "0";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(300);
    }
    if (digitalRead(btnOne) == LOW) {
      input += "1";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(300);
    }
    if (digitalRead(btnClear) == LOW) {
      input = "";
      lcd1.setCursor(6, 1);
      lcd1.print("    ");  // Limpa a área da resposta
      Serial.println("Entrada limpa");
      delay(300);
    }
    if (digitalRead(btnSubmit) == LOW) {
      checkAnswer();
      delay(300);
      break;
    }
    if (digitalRead(btnEndGame) == LOW) {
      endGame(); // Permite encerrar o jogo durante a espera pela entrada
      delay(300);
      return;
    }
  }
}

void checkAnswer() {
  int userAnswer = strtol(input.c_str(), NULL, 2);  // Converte a entrada binária para um número inteiro
  Serial.print("Resposta do usuário: ");
  Serial.println(userAnswer);
  if (userAnswer == correctAnswer) {
    score += 10;  // Incrementa a pontuação
    level++;      // Aumenta o nível
    lcd1.clear();
    lcd1.print("Correto!");
    Serial.println("Resposta correta!");
    delay(1000);
  } else {
    score -= 10;  // Diminui a pontuação
    lcd1.clear();
    lcd1.print("Errado!");
    Serial.println("Resposta errada!");
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
  Serial.print("Pontuação atual: ");
  Serial.println(score);
}

void endGame() {
  lcd1.clear();
  lcd2.clear();
  lcd1.print("Jogo Encerrado");
  Serial.println("Jogo Encerrado");
  delay(2000); // Exibe mensagem por 2 segundos
  lcd1.clear();
  lcd1.print("Modo: Arcade"); // Volta ao modo inicial ou outro estado padrão
  lcd2.setCursor(0, 0);
  lcd2.print("Score: 0");
  score = 0; // Reseta a pontuação
  currentMode = 0; // Reseta o modo de jogo para o modo padrão (Arcade)
}

// Implementação do Modo Timer

void startTimerMode() {
  lcd1.clear();
  lcd2.clear();
  lcd1.print("Selec. tempo (1-5)");
  lcd2.clear();
  selectedTime = selectTimer(); // Função para escolher o tempo de jogo
  lcd1.clear();
  lcd1.print("Tempo: ");
  lcd1.print(selectedTime);
  lcd1.print(" min");
  Serial.print("Tempo selecionado: ");
  Serial.print(selectedTime);
  Serial.println(" minutos");
  delay(1000);

  unsigned long endTime = millis() + selectedTime * 60000; // Calcula o tempo final
  while (millis() < endTime) {
    if (digitalRead(btnEndGame) == LOW) {
      endGame(); // Permite encerrar o jogo a qualquer momento
      return; // Sai da função para garantir que o jogo não reinicie
    }
    nextQuestionTimer(endTime); // Executa as operações durante o tempo definido
  }

  // Exibe a pontuação final após o tempo acabar
  lcd1.clear();
  lcd1.print("Tempo esgotado!");
  delay(2000);
  lcd1.clear();
  lcd1.print("Pontos finais:");
  lcd1.setCursor(0, 1);
  lcd1.print(score);
  Serial.print("Pontuação final: ");
  Serial.println(score);
  delay(5000); // Mantém a pontuação final na tela por 5 segundos
  endGame(); // Chama a função para encerrar o jogo após o tempo esgotar
}

int selectTimer() {
  int timeSelected = 1;
  while (true) {
    if (digitalRead(btnZero) == LOW) {
      timeSelected = (timeSelected % 5) + 1; // Alterna entre 1 e 5
      lcd1.setCursor(7, 0);
      lcd1.print(timeSelected);
      Serial.print("Tempo escolhido: ");
      Serial.println(timeSelected);
      delay(300);
    }
    if (digitalRead(btnSubmit) == LOW) {
      return timeSelected; // Retorna o tempo selecionado
    }
  }
}

void nextQuestionTimer(unsigned long endTime) {
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
  Serial.print("Operação do modo Timer: ");
  Serial.print(num1);
  Serial.print(" ");
  Serial.print(operation);
  Serial.print(" ");
  Serial.println(num2);

  waitForInputTimer(endTime);
}

void waitForInputTimer(unsigned long endTime) {
  bool buttonZeroPressed = false;
  bool buttonOnePressed = false;
  bool buttonClearPressed = false;
  bool buttonSubmitPressed = false;

  while (millis() < endTime) {
    // Detecta clique no botão '0'
    if (digitalRead(btnZero) == LOW && !buttonZeroPressed) {
      buttonZeroPressed = true; // Marca que o botão foi pressionado
      input += "0";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(200); // Pequeno delay para evitar múltiplas entradas
    } else if (digitalRead(btnZero) == HIGH) {
      buttonZeroPressed = false; // Reseta quando o botão é liberado
    }

    // Detecta clique no botão '1'
    if (digitalRead(btnOne) == LOW && !buttonOnePressed) {
      buttonOnePressed = true;
      input += "1";
      lcd1.setCursor(6, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(200);
    } else if (digitalRead(btnOne) == HIGH) {
      buttonOnePressed = false;
    }

    // Detecta clique no botão 'Clear'
    if (digitalRead(btnClear) == LOW && !buttonClearPressed) {
      buttonClearPressed = true;
      input = "";
      lcd1.setCursor(6, 1);
      lcd1.print("    ");  // Limpa a área da resposta
      Serial.println("Entrada limpa");
      delay(200);
    } else if (digitalRead(btnClear) == HIGH) {
      buttonClearPressed = false;
    }

    // Detecta clique no botão 'Submit'
    if (digitalRead(btnSubmit) == LOW && !buttonSubmitPressed) {
      buttonSubmitPressed = true;
      checkAnswerTimer(endTime);
      delay(200);
      return;
    } else if (digitalRead(btnSubmit) == HIGH) {
      buttonSubmitPressed = false;
    }

    // Detecta clique no botão 'End Game'
    if (digitalRead(btnEndGame) == LOW) {
      endGame();
      delay(300);
      return;
    }

    // Atualiza o tempo restante no LCD2
    lcd2.setCursor(0, 0);
    lcd2.print("Tempo: ");
    lcd2.print((endTime - millis()) / 1000); // Tempo restante em segundos
    delay(100); // Reduz a frequência de atualização para não sobrecarregar o LCD
  }
}

void checkAnswerTimer(unsigned long endTime) {
  int userAnswer = strtol(input.c_str(), NULL, 2);  // Converte a entrada binária para um número inteiro
  Serial.print("Resposta do usuário (Timer): ");
  Serial.println(userAnswer);
  if (userAnswer == correctAnswer) {
    score += 10;  // Incrementa a pontuação
    lcd1.clear();
    lcd1.print("Correto!");
    Serial.println("Resposta correta!");
    delay(1000);
  } else {
    lcd1.clear();
    lcd1.print("Errado!");
    Serial.println("Resposta errada!");
    delay(1000);
  }
  updateScoreTimer(endTime); // Continua o jogo enquanto o tempo não expirar
}

void updateScoreTimer(unsigned long endTime) {
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Score: ");
  lcd2.print(score);
  Serial.print("Pontuação atual: ");
  Serial.println(score);
  
  // Exibir próxima questão se o tempo não tiver acabado
  if (millis() < endTime) {
    nextQuestionTimer(endTime);
  }
}

// Implementação do Modo Memória

void startMemoryMode() {
  lcd1.clear();
  lcd2.clear();
  lcd1.print("Memoria Mode");
  Serial.println("Iniciando Modo Memória");
  delay(1000);

  int num1, num2;
  char operations[] = {'+', '-', '*', '/'};
  char operation;

  // Gerar e mostrar uma sequência de operações
  for (int i = 0; i < 3; i++) { // Mostra 3 operações ao usuário
    do {
      num1 = random(0, 101); 
      num2 = random(1, 101);
      operation = operations[random(0, 4)];
      
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
          if (num1 % num2 == 0) {
            correctAnswer = num1 / num2;
          } else {
            correctAnswer = -1;
          }
          break;
      }
    } while (correctAnswer < 0 || correctAnswer > 100); // Garante que a operação seja válida

    lcd1.setCursor(0, 0);
    lcd1.print(num1);
    lcd1.print(" ");
    lcd1.print(operation);
    lcd1.print(" ");
    lcd1.print(num2);
    Serial.print("Operação exibida: ");
    Serial.print(num1);
    Serial.print(" ");
    Serial.print(operation);
    Serial.print(" ");
    Serial.println(num2);
    delay(2000); // Mostra a operação por 2 segundos
  }

  // Solicita a resposta da última operação mostrada
  lcd1.clear(); 
  lcd1.print("Resp ultima:");
  Serial.println("Solicitando resposta para a última operação exibida.");
  waitForMemoryAnswer();
}

void waitForMemoryAnswer() {
  input = "";
  while (true) {
    if (digitalRead(btnZero) == LOW) {
      input += "0";
      lcd1.setCursor(0, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(300);
    }
    if (digitalRead(btnOne) == LOW) {
      input += "1";
      lcd1.setCursor(0, 1);
      lcd1.print(input);
      Serial.print("Entrada: ");
      Serial.println(input);
      delay(300);
    }
    if (digitalRead(btnClear) == LOW) {
      input = "";
      lcd1.setCursor(0, 1);
      lcd1.print("    ");
      Serial.println("Entrada limpa");
      delay(300);
    }
    if (digitalRead(btnSubmit) == LOW) {
      int userAnswer = strtol(input.c_str(), NULL, 2);
      Serial.print("Resposta do usuário (Memória): ");
      Serial.println(userAnswer);
      if (userAnswer == correctAnswer) {
        lcd1.clear();
        lcd1.print("Correto!");
        score += 10;
        Serial.println("Resposta correta!");
        delay(1000);
        startMemoryMode(); // Volta para o início do Modo Memória
      } else {
        lcd1.clear();
        lcd1.print("Errado!");
        score -= 10;
        Serial.println("Resposta errada!");
        delay(1000);
        startMemoryMode(); // Volta para o início do Modo Memória
      }
      updateScore();
      break;
    }
    if (digitalRead(btnEndGame) == LOW) {
      endGame();
      delay(300);
      return;
    }
  }
}
