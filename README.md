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
https://github.com/romashkagvr2006/programming-on-C/blob/main/image.png - picture with pin's locations in MAX3232E
