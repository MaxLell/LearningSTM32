# LearningSTM32
This series attempts to replicate the Blog Article: How to learn a new Microcontroller https://www.embeddedrelated.com/showarticle/1455.php


## 0. GPIOs (Digital Input and Output) and Timers
### 01_BlinkyLed
As the name implies this is the classic busy wait blinky LED with a busy wait. So this is about putting a value on the digital output of the LED pin.

### 02_ButtonPolled
This is about polling the GPIO Button. So this is about capturing the digital in value on the button pin. If the button was pulled, enable the LED for a short period of time to then disable it again.

### 03_ButtonInterrupt
Blink the led in response to an external interrupt, which originates from the button.

### 04_BlinkyLedTimerInterrupt
Here the Led is toggled by a timer interrupt after a long button press. Also make sure to debounce the Button.

### 05_RtosButtonToBlinky
- Pressing a button briefly enables the led
- Pressing a button for a longer period of time toggles the led
- Releasing the button disables the LED
- Implement the Sampling of the Button with an InputHandler Thread. Implement the actuation of the LED by a seperate Task called OutputHandler.

## 1. CLI (UART and Timers)
## 11_PolledEcho
Polled UART IO: read a string in from the terminal emulator and print it back out (echo it). 

## 12_IsrEcho
Interrupt-driven UART input: echo based on input interrupt. Same as before - only report back one character. Make both the RX and the TX part sending and receiving bytes via interrupts.

## 13_CommandLineInterface
- Develop a small CLI which (and this is really up to you which approach of HW-interaction - polled, ISR or DMA on rx and tx side you chose):
  - clears the current screen
  - displays a help menu which lists all commands
  - makes it possible to enable and disable an led

## 2. Sensors and Actuators (SPI and I2C)

## 4. PWMs

## 3. Analogs
