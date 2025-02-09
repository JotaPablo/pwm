# Projeto de Controle PWM com RP2040 - BitDogLab

Projeto desenvolvido para a Unidade 4 - Capítulo 7, demonstrando o uso de PWM (modulação por largura de pulso) para controle de periféricos, como servomotores e LEDs, na placa BitDogLab com RP2040.

## 🎥 Vídeo Demonstrativo
[![Assista ao vídeo no YouTube](https://img.youtube.com/vi/DTxdqxYpCuU/hqdefault.jpg)](https://youtu.be/DTxdqxYpCuU)

## Descrição
Implementação de um sistema para controle de um servomotor ou LED, utilizando a modulação por largura de pulso (PWM). O código permite ajustar o ângulo de um servomotor ou controlar o brilho de um LED RGB de forma suave.

### ATENÇÃO:
- **`USE_LED`**: Este parâmetro deve ser ativado **somente** para testar o código de forma segura. Quando `USE_LED` está ativado, o código controla um LED RGB (GPIO 12), o que evita danos à placa durante os testes.  
- **Uso de Servomotor (GPIO 22)**: Se você deseja usar o servomotor, **comente a linha `#define USE_LED`** e **descomente a linha que habilita o GPIO 22 para controle do motor**. Ao utilizar o servomotor, é necessário usar um circuito de interface adequado, pois o GPIO 22 sozinho pode não fornecer a corrente necessária para o motor e pode danificar a placa.

## Componentes Utilizados
- Placa BitDogLab com RP2040
- Servomotor ou LED RGB (GPIO 12 ou GPIO 22)
- Resistores e fiação adequada para a conexão de componentes

## Funcionalidades Principais

### Controle de Servomotor/LED
- O **servomotor** é controlado pela modulação de PWM, permitindo movimentos suaves entre os ângulos de 0°, 90° e 180°. A frequência é ajustada para **50Hz**, com **duty cycle** variando entre **500μs** (0°), **1470μs** (90°) e **2400μs** (180°).
- O **LED** é controlado através de PWM, ajustando o brilho conforme o **duty cycle**. O PWM modula a intensidade luminosa do LED RGB de forma contínua e gradual.

### Segurança e Impacto do `USE_LED`
- **IMPORTANTE**: Se você estiver testando na **placa BitDogLab real**, **utilize sempre o `USE_LED` ativado** para controlar o LED (GPIO 12). Isso garante a segurança da placa, evitando sobrecarga ou danos ao tentar controlar um servomotor sem um circuito de interface adequado.
  - **Uso de Servomotor**: Se você optar por usar o **servomotor** (GPIO 22), **descomente a linha** `#define USE_LED` e certifique-se de usar um **circuito de interface adequado** para o motor, como um driver ou fonte de alimentação externa. Sem isso, há risco de danificar a placa.

## ⚙️ Instalação e Uso

1. **Pré-requisitos**
   - Clonar o repositório:
     ```bash
     git clone https://github.com/JotaPablo/pwm.git
     cd pwm
     ```
   - Instalar o **Visual Studio Code** com as seguintes extensões:
     - **Raspberry Pi Pico SDK**
     - **Compilador ARM GCC**

2. **Compilação**
   - Compile o projeto no terminal:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
   - Ou utilize a extensão da Raspberry Pi Pico no VS Code.

3. **Execução**
   - **Na placa BitDogLab (real):** 
     - **IMPORTANTE**: Se estiver executando o código na **placa BitDogLab** real, com o **servomotor**, **COMENTE a linha** `#define USE_LED` e **DESCOMENTE a linha** correspondente ao uso do motor (GPIO 22). Certifique-se de usar um circuito de interface adequado para o servomotor, caso contrário, você pode danificar a placa.
     - Conecte a placa ao computador em modo **BOOTSEL**:
       1. Conecte a placa BitDogLab enquanto segura o botão **BOOTSEL**.
       2. Copie o arquivo .uf2 gerado na pasta build para o dispositivo identificado como RPI-RP2, ou envie através da extensão da Raspberry Pi Pico no VS Code.
   
   - **No simulador Wokwi (simulação):**
     - Se estiver executando o código no **simulador Wokwi**, **DEIXE a linha** `#define USE_LED` **DESCOMENTADA**, já que o simulador não necessita de circuitos adicionais, e o LED pode ser utilizado de forma segura para testes.
     - Após compilar o código, basta executar o arquivo `diagram.json` no simulador Wokwi para testar o comportamento do código.
