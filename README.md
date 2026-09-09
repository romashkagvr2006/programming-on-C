The list of abbreviations (Перечень сокращений и обозначений)
UART – Universal Asynchronous Receiver/Transmitter – аппаратно – программный интерфейс для передачи данных 
LPC – Low Pin Count – семейство процессоров компании Philips
RS – recommended standard – интерфейс сопряжения между терминальным оборудованием 
и коммуникационным 
ARM – Advanced RISC Machine – архитектура микроконтроллеров 
RISC – Reduced Instruction Set Computer  - компьютер с сокращенным набором инструкций
АМК – автоматизированный метеорологический комплекс 
KEIL 𝛍Vision  - интегрированная среда разработки для создания программного обеспечения микроконтроллеров
МСМ – международная система мониторинга 
ПЭВМ – персональная электронно-вычислительная машина
PPS – Pulse Per Second - сигнал, который срабатывает ровно один раз в секунду
ILR (Interrupt Location Register) — это аппаратный регистр часов RTC
VIC (Vectored Interrupt Controller) — это контроллер прерываний


AMK-04 is spesialized device used to monitore parameters of the bottom Earth's layer.
The main purpose of this project was learning the bases of programming similar systems and researching the data transmission protocol.\
Also through process of making the project skills in debugging code in specialized development environment were acquired 

1) The structure of adoption and transmission of data through microcontroller of the LPC2000 family
   1.1 The biggest problem with interfacing controllers with RS-232 line to transmit the signals is the difference of working voltage  range
   The solution based on MAX3232E device. 
picture with pin's locations in MAX3232E include in file "image.png"
   1.2
   For each command and for most responses, information packets of the same size — 11 bytes — are used, all following the same logical structure. If a particular byte within a given packet is not used, it is still transmitted, with its value set to zero (00 Hex). A single byte is reserved for the checksum of the packet's bytes, which is calculated using the bitwise logical operation XOR.
   There is a table that can describe it
   Also the AMK-04 answers with similar 11 bytes to the controller
   2) Code structure
      it describes in many files, the "ARM_OS.c" file is general, it includes functions to transmit and take data
      "RSS.c" file includes the structure of functions and any important definitions
The PPS flag is set in flag1 when it is time to send the next request, i.e. after one second has elapsed inside the RTC_POLL() function. If ILR is not equal to zero, it means the clock has generated an event (counted one second). ILR = 3 signals the end of the event (otherwise the If condition would remain constantly true), i.e. it resets the counter. Then the PPS value is set in flag1, indicating that one second has passed, and the external program is able to detect this.

Writing zero to this VIC interrupt register is a standard command that tells the processor: "Interrupt handling is complete, you can return to normal operation."

Inside the chip, a timer is ticking. Once per second, it raises a flag in the ILR register.

The main loop constantly, at a very high rate, calls RTC_Poll(). ILR == 0, and the function does nothing. But once per second, it detects the event, clears the hardware flag, and sets the software flag: SETBIT(flag1, PPS).

Upon seeing this raised flag, the program starts sending a request. It selects the required data packet (pressure, temperature, etc.) and sends it to the UART (check_up_flags()).

Then, inside the data transmission function check_up_flags(), this flag is cleared for future repeated transmissions.

The byte transmission function to the weather station:

The U1LSR status register is continuously polled. If it contains the value 0x20, this instructs the microcontroller to check the fifth bit of the register, which indicates the state of the transmit buffer. If the register is not empty (i.e., the previous bit is still being transmitted through the buffer), the logical operation returns 0. The negation specified in the loop turns this 0 into 1, causing the while loop to stay in place and wait for the buffer to become free.

When the buffer is freed, the loop terminates and the subsequent operations are executed, namely the direct write of the value to the U1THR register. After that, the program "forgets" about it, while the UART appends the start and stop bits to the byte and transmits it via the TX pin to the weather station.
