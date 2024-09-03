```markdown
# Projeto de Jogo Educativo com Arduino
```

Este projeto implementa um jogo educativo em um Arduino que testa habilidades matemáticas e de memória. O jogo possui três modos diferentes: Arcade, Timer e Memória. Ele utiliza LEDs e um buzzer para indicar respostas corretas e incorretas, e dois displays LCD para exibir perguntas e a pontuação do jogador.

## Simulação Online

Você pode visualizar e testar o projeto diretamente no Wokwi:

[🔗 Acesse a Simulação no Wokwi](https://wokwi.com/projects/407576668273449985)


## Funcionalidades

- **Modo Arcade**: Testa habilidades matemáticas com operações de dificuldade crescente.
- **Modo Timer**: Jogo de corrida contra o tempo, onde o usuário deve acertar o máximo de operações possíveis dentro de um tempo escolhido.
- **Modo Memória**: Desafia o jogador a lembrar a última operação mostrada após uma sequência.
- **Feedback Visual e Auditivo**:
  - LEDs indicam se a resposta é correta (LED verde) ou incorreta (LED vermelho).
  - Um buzzer emite diferentes sons para respostas corretas e incorretas.

## Componentes Necessários

- 1 Arduino (UNO, Nano, ou similar)
- 2 LEDs (1 verde para resposta correta, 1 vermelho para resposta incorreta)
- 2 Resistores de 220Ω ou 330Ω (para os LEDs)
- 1 Buzzer (ativo ou passivo)
- 2 Displays LCD 16x2 com interface I2C
- 8 Botões (para entrada de resposta, seleção de modos e controle do jogo)
- Protoboard e Jumpers para conexões

## Diagrama de Montagem

### Conexão dos Componentes

#### LEDs
- **LED Verde (Correto):**
  - Anodo (perna longa) ao pino **D4** do Arduino.
  - Catodo (perna curta) ao GND do Arduino, passando por um resistor de 220Ω ou 330Ω.
  
- **LED Vermelho (Incorreto):**
  - Anodo (perna longa) ao pino **D5** do Arduino.
  - Catodo (perna curta) ao GND do Arduino, passando por um resistor de 220Ω ou 330Ω.

#### Buzzer
- **Buzzer:**
  - Pino positivo ao pino **D3** do Arduino.
  - Pino negativo ao GND do Arduino.

#### Displays LCD
- **LCD 1:**
  - SDA ao pino **A4** do Arduino.
  - SCL ao pino **A5** do Arduino.
  - VCC ao pino **5V** do Arduino.
  - GND ao pino **GND** do Arduino.

- **LCD 2:**
  - SDA ao pino **A2** do Arduino.
  - SCL ao pino **A3** do Arduino.
  - VCC ao pino **5V** do Arduino.
  - GND ao pino **GND** do Arduino.

#### Botões
- **Botão 1 (0):** Conectado ao pino **D10** do Arduino.
- **Botão 2 (1):** Conectado ao pino **D9** do Arduino.
- **Botão 3 (Limpar):** Conectado ao pino **D8** do Arduino.
- **Botão 4 (Enviar):** Conectado ao pino **D7** do Arduino.
- **Botão 5 (Encerrar Jogo):** Conectado ao pino **D6** do Arduino.
- **Botão 6 (Selecionar Modo):** Conectado ao pino **D12** do Arduino.
- **Botão 7 (Próximo Modo):** Conectado ao pino **D13** do Arduino.

## Instruções de Uso

1. **Montagem do Circuito:**
   - Conecte todos os componentes conforme o diagrama de montagem fornecido acima.
   - Verifique as conexões para garantir que todos os pinos estejam corretos.

2. **Upload do Código:**
   - Abra o Arduino IDE e copie o código do projeto para um novo sketch.
   - Conecte o Arduino ao computador via USB.
   - Selecione a placa correta e a porta em `Ferramentas > Placa` e `Ferramentas > Porta`.
   - Clique em "Upload" para enviar o código para o Arduino.

3. **Início do Jogo:**
   - Após o upload, o Arduino inicializará e o jogo começará no modo Arcade.
   - Use o botão de **Próximo Modo** (pino D13) para navegar entre os modos de jogo.
   - Use o botão de **Selecionar Modo** (pino D12) para iniciar o modo escolhido.

4. **Jogando:**
   - **Modo Arcade:** As operações matemáticas são exibidas no display LCD. Insira a resposta em binário usando os botões "0" e "1", e envie a resposta usando o botão de "Enviar".
   - **Modo Timer:** Escolha o tempo desejado (1 a 5 minutos) e tente acertar o máximo de operações dentro do tempo selecionado.
   - **Modo Memória:** Lembre-se da última operação exibida após uma sequência e insira a resposta.

5. **Feedback:**
   - O LED verde piscará e um som de sucesso será emitido quando a resposta estiver correta.
   - O LED vermelho piscará e um som de erro será emitido quando a resposta estiver incorreta.

## Dependências

Este projeto depende das seguintes bibliotecas:

- **LiquidCrystal_I2C**: Biblioteca para controle de displays LCD via I2C.
  - Instale esta biblioteca através do Gerenciador de Bibliotecas do Arduino IDE.
  
## Exemplo de Código

O código completo do projeto está disponível no arquivo `game.ino` neste repositório.

## Dicas de Solução de Problemas

- **Problema:** O display LCD não mostra nada.
  - **Solução:** Verifique as conexões SDA e SCL e assegure-se de que o endereço I2C esteja correto.
- **Problema:** O LED não pisca ou o buzzer não faz som.
  - **Solução:** Verifique as conexões dos LEDs e do buzzer e teste com um sketch simples para garantir que estão funcionando corretamente.

## Créditos

Este projeto foi desenvolvido como parte de um jogo educativo para treinar habilidades matemáticas e de memória, utilizando o Arduino.
```
