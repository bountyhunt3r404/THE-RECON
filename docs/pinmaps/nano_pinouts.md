# Pin Assignments: ARDUINO NANO

Pinouts of JoyStick, NRF24L01, Switches, Potentiometers connected to the Arduino Nano


## JoyStick -> Arduino Nano 
* Joystick are 5V logic Level

    | JoyStick | Pins | Arduino Nano |
    | :------: | :--: | :----------: |
    |   Left   |  X  |      A0      |
    |          |  Y  |      A1      |
    |          |  SW  |      D4      |
    |  Right  |  X  |      A7      |
    |          |  Y  |      A6      |
    |          |  SW  |      D7      |

## NRF24L01+ -> Arduino Nano
* Vcc - 3.3v
* Pins are 5V tolerant

    | Pin No. | NRF24L01+ | Arduino Nano |
    | :-----: | :-------: | :----------: |
    |    1    |    GND    |     GND     |
    |    2    |    VCC    |     3.3V     |
    |    3    |    CE    |     D10     |
    |    4    |    CSN    |      D9      |
    |    5    |    SCK    |     D13     |
    |    6    |   MOSI   |     D11     |
    |    7    |   MISO   |     D12     |
    |    8    |    IRQ    |      NC      |

## Rotary potentiometer -> Arduino Nano
* 5v Tolerant

    | Potentiometer | Arduino Nano |
    | :-----------: | :----------: |
    |   Left Pot   |      A2      |
    |   Right Pot   |      A3      |

## Limit Switches -> Arduino Nano
* Default: PULLUP

    |  Tiggers  | Arduino Nano |
    | :--------: | :----------: |
    | Left Trig |      D5      |
    | Right Trig |      D6      |

