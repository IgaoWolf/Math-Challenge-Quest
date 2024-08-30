#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do LCD 1
LiquidCrystal_I2C lcd1(0x27, 16, 2); // Endereço I2C pode ser 0x27 ou 0x3F

// Configuração dos pinos dos botões
const int buttonSelect = 11; // Botão para selecionar modo
const int buttonStart = 10;  // Botão para iniciar o jogo
const int debounceDelay = 200; // Tempo de debounce para os botões

// Definição dos modos de jogo
enum GameMode { ARCADE, TIMER, MEMORIA, HARDCORE };
GameMode currentMode = ARCADE;

// Função para exibir o modo de jogo atual no LCD
void displayMode(GameMode mode) {
  lcd1.clear();
  lcd1.print("Modo: ");
  switch (mode) {
    case ARCADE:
      lcd1.print("Arcade");
      break;
    case TIMER:
      lcd1.print("Timer");
      break;
    case MEMORIA:
      lcd1.print("Memoria");
      break;
    case HARDCORE:
      lcd1.print("Hardcore");
      break;
  }
}

void setup() {
  // Inicializa o LCD 1
  lcd1.begin(16, 2);
  lcd1.backlight();
  displayMode(currentMode);

  // Configura os botões como entrada
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
}

void loop() {
  static unsigned long lastDebounceTime = 0; // Armazena o tempo do último debounce

  // Verifica se o botão de seleção foi pressionado
  if (digitalRead(buttonSelect) == LOW) {
    if (millis() - lastDebounceTime > debounceDelay) {
      currentMode = static_cast<GameMode>((currentMode + 1) % 4); // Alterna entre os modos
      displayMode(currentMode);
      lastDebounceTime = millis(); // Atualiza o tempo do último debounce
    }
  }

  // Verifica se o botão de início foi pressionado
  if (digitalRead(buttonStart) == LOW) {
    if (millis() - lastDebounceTime > debounceDelay) {
      lcd1.clear();
      lcd1.print("Iniciando ");
      displayMode(currentMode); // Exibe o modo selecionado
      delay(1000); // Tempo de espera para iniciar o jogo
      // Aqui você pode adicionar a lógica para iniciar o jogo conforme o modo selecionado
      lastDebounceTime = millis(); // Atualiza o tempo do último debounce
    }
  }
}
