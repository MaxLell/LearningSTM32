# LearningSTM32
This series attempts to replicate the Blog Article: How to learn a new Microcontroller https://www.embeddedrelated.com/showarticle/1455.php


## 0. GPIOs (Digital Input and Output) and Timers
### 01_BlinkyLed
As the name implies this is the classic busy wait blinky LED with a busy wait. So this is about putting a value on the digital output of the LED pin.

### 02_ButtonPolled
This is about polling the GPIO Button. So this is about capturing the digital in value on the button pin.

### 03_ButtonInterrupt
Blink the led in response to an external interrupt, which originates from the button.

### 04_BlinkyLedTimerInterrupt
Here the Led is toggled by a timer interrup

### 05_ButtonToBlinkyWithTimerInterrupt
Blink an LED with a fixed rate (triggered by a timer interrupt). A button interrupt changes the rate by which the LED is triggered

### 06_RtosButtonToBlinky
- The Button is sampled by the input handler task
- The Output Handler task configures the timer (blink rate) and the blink counter
- The LED is toggled 10 times when a long press occured on the button. (To be done by the timer ist)
- The LED is toggled 2 times when a short press was detected (To be done by the timer isr)

## 1. CLI (UART and Timers)
## 11_LoopedHelloWorldWithTimerInterrupt
Loop-driven UART output: print a fixed string to a terminal emulator.

## 12_PolledCharEcho
Polled UART input: read a character in from the terminal emulator and print it back out (echo it). This is the first step in implementing a CLI (Command Line Interface).

## 13_InterruptDrivenCharEcho
Interrupt-driven UART input: echo based on input interrupt.

## 14_CliGetVersionWithInterrupt
 Interrupt-driven UART CLI: accumulate input characters into a string; on receipt of a CR (Carriage Return), interpret the string as a command in non-interrupt context (for instance, a "version" command that prints a version string). This is the first command in a CLI, and the first major separation of interrupt and non-interrupt code sharing data.

#### 15_CliGetVersionWithDma
DMA: send and receive chunks of data via DMA rather than programmatic character-at-a-time register access.

#### 16_CliSendHeartbeatWithTimer
Timer-driven UART output with input: print a periodic message in response to timer interrupts; change the frequency in response to input commands in the CLI.

#### 17_RtosCliWithDma
- Expand the existing RTOS Application. Use the concepts of the CLI that was implemented in this section
	- The CLI Tool shall be sampled automatically in the background with the help of the DMA. Sending commands from the Mikrocontroller shall also be done by the DMA
	- By sending Commands to the CLI (from the host)
		- the user can control the amounts of blinks that the LED performs
		- the on-time of the blinks shall be controllable
		- the off-time of the blinks shall be controllable
		- The CLI can trigger (same as the button) the blinking of the LED
		- The CLI shall report back the duration of the system being active.


## 2. Sensors and Actuators (SPI and I2C)

## 4. PWMs

## 3. Analogs
