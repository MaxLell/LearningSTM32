# LearningSTM32
This series attempts to replicate the Blog Article: How to learn a new Microcontroller https://www.embeddedrelated.com/showarticle/1455.php


## 1. GPIOs (Digital Input and Output) and Timers
### 11_LED_busy_wait 
As the name implies this is the classic busy wait blinky LED with a busy wait. So this is about putting a value on the digital output of the LED pin.

### 12_LED_ButtonPolled
This is about polling the GPIO Button. So this is about capturing the digital in value on the button pin.

### 13_LED_ButtonInterrupt
Blink the led in response to an external interrupt, which originates from the button.

### 14_LED_TimerInterupt
Here the Led is toggled by a timer interrup

### 15_LED_TimerInterrupt_ButtonChange
Blink an LED with a fixed rate (triggered by a timer interrupt). A button interrupt changes the rate by which the LED is triggered

### 16_LED_RTOS_ButtonToBlinky
- The Button is sampled by the input handler task
- The Output Handler task configures the timer (blink rate) and the blink counter
- The LED is toggled 10 times when a long press occured on the button. (To be done by the timer ist)
- The LED is toggled 2 times when a short press was detected (To be done by the timer isr)

## 2. Serial Communication
### 2.1 UART and Timers
#### 211_UART_LoopOut
Loop-driven UART output: print a fixed string to a terminal emulator.

#### 212_UART_PolledEcho
Polled UART input: read a character in from the terminal emulator and print it back out (echo it). This is the first step in implementing a CLI (Command Line Interface).

#### 213_UART_InterruptEcho
Interrupt-driven UART input: echo based on input interrupt.

#### 214_UART_CLI_Interrupt
 Interrupt-driven UART CLI: accumulate input characters into a string; on receipt of a CR (Carriage Return), interpret the string as a command in non-interrupt context (for instance, a "version" command that prints a version string). This is the first command in a CLI, and the first major separation of interrupt and non-interrupt code sharing data.

#### 215_UART_DMA
DMA: send and receive chunks of data via DMA rather than programmatic character-at-a-time register access.

#### 216_UART_TimerPeriodic
Timer-driven UART output: print a periodic message in response to timer interrupts.

#### 217_UART_TimerPeriodic_CLI
Timer-driven UART output with input: print a periodic message in response to timer interrupts; change the frequency in response to input commands in the CLI.

#### 218_Capstone_RTOS_CLI
- Expand the existing RTOS Application. Use the concepts of the CLI that was implemented in this section
	- The CLI Tool shall be sampled automatically in the background with the help of the DMA. Sending commands from the Mikrocontroller shall also be done by the DMA
	- By sending Commands to the CLI (from the host)
		- the user can control the amounts of blinks that the LED performs
		- the on-time of the blinks shall be controllable
		- the off-time of the blinks shall be controllable
		- The CLI can trigger (same as the button) the blinking of the LED
		- The CLI shall report back the duration of the system being active.

