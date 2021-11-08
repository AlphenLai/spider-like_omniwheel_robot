#ifndef Config_H_
#define Config_H_

#define pi                  3.14159265359

#define USE_SERVO1          true
#define SERVO1_PULSE_WIDTH  0.001     //0.00125 for white servo, 0.001 for MG995
#define SERVO1_HW_RANGE     180

#define USE_SERVO2          true
#define SERVO2_PULSE_WIDTH  0.001
#define SERVO2_HW_RANGE     180

#define USE_SERVO3          true
#define SERVO3_PULSE_WIDTH  0.001
#define SERVO3_HW_RANGE     180

#define USE_SERVO4          true
#define SERVO4_PULSE_WIDTH  0.001
#define SERVO4_HW_RANGE     180

#define USE_ADC_ROTARY      false
#define ADC_ROTARY_FUNC     SERVO1_CONT
#define ADC_ROTARY_MAX      0.77
#define ADC_ROTARY_MIN      0.4

#define MOTOR_NUMBER        4
#define MOTOR_PWM_PERIOD_MS 10

#define ENC_CYCLE_SIZE      11

#define MOTOR1_HW_INV       1
#define MOTOR2_HW_INV       1
#define MOTOR3_HW_INV       1
#define MOTOR4_HW_INV       1

// ***Define all pin assignments and setup in this file***
#define LD2                 LED1

//PWM1/1-4
#define SERVO1_PIN          PA_10
#define SERVO2_PIN          PA_9
#define SERVO3_PIN          PA_8
#define SERVO4_PIN          PA_11

#define ROTARY_PIN_A        PC_1
#define ROTARY_PIN_B        PC_0
//#define ROTARY_PIN_SW       PB_0

#define ON_BRD_BTN          PC_13

#define ADC_PIN_1           PA_0

//PWM3/1-4
#define MOTOR1_PWM_PIN      PC_8
#define MOTOR1_IN1_PIN      PB_1
#define MOTOR1_IN2_PIN      PB_15
#define MOTOR1_ENC_A        PB_2
#define MOTOR1_ENC_B        PC_3

#define MOTOR2_PWM_PIN      PC_9
#define MOTOR2_IN1_PIN      PB_14
#define MOTOR2_IN2_PIN      PB_13
#define MOTOR2_ENC_A        PC_4
#define MOTOR2_ENC_B        PC_5

#define MOTOR3_PWM_PIN      PC_6
#define MOTOR3_IN1_PIN      PA_14
#define MOTOR3_IN2_PIN      PC_12
#define MOTOR3_ENC_A        PA_6
#define MOTOR3_ENC_B        PA_7

#define MOTOR4_PWM_PIN      PC_7
#define MOTOR4_IN1_PIN      PA_4
#define MOTOR4_IN2_PIN      PB_0
#define MOTOR4_ENC_A        PB_12
#define MOTOR4_ENC_B        PA_13

#define S1TX                PB_6
#define S1RX                PB_7
#define S2TX                PA_2
#define S2RX                PA_3
#define S3TX                PC_10
#define S3RX                PC_11


//4servo    pwmout
//4motor    pwmout
//?reserve more pwmouts
//1lcd?     i2c
//idial     analog
//?comm     serials(as much as it can)
//1sd card  spi

/*  Design pinout of this board
serial:
SERIAL1_TX  PB_6    D10
SERIAL1_RX  PB_7    
SERIAL2_TX  PA_2    D1
SERIAL2_RX  PA_3    D0
SERIAL3_TX  PC_10
SERIAL3_RX  PC_11

i2c:
I2C1_SCL    PB_8    D15
I2C1_SDA    PB_9    D14
I2C2_SCL    PB_10   D6
I2C2_SDA    PB_11

spi:
SPI1_MISO   PB_4    D5
SPI1_MOSI   PB_5    D4
SPI1_SCK    PB_3    D3
SPI1_NSS    PA_15

pwm:
go test signals 
PC_9 and PB_1
PB_15 and PA_10

io:
onboard_btn PC_13
onboard_led PA_5

*/

/*  Quick lookup table for nucleo pins conversion
PA_0    A0
PA_1    A1  PWM2/2
PA_2    D1  PWM2/3      S2_TX       (ANALOG)
PA_3    D0  PWM2/4      S2_RX       (ANALOG)
PA_4    A2              SPI1_NSS
PA_5    D13 LED1/LD2    SPI1_SCK    (ANALOG)
PA_6    D12 PWM3/1      SPI1_MISO   (ANALOG)
PA_7    D11 PWM3/2      SPI1_MOSI   (ANALOG)
PA_9    D8  PWM1/2?     S1_TX
PA_8    D7  PWM1/1?
PA_9    D8  PWM1/2      S1_TX
PA_10   D2  PWM1/3      S1_RX
PA_11       PWM1/4
PA_12
PA_13
PA_14
PA_15       PWM2/1      SPI1_NSS

PB_0    A3  PWM3/3
PB_1        PWM3/4                  (ANALOG)
PB_2
PB_3    D3  PWM2/2      SPI1_SCK
PB_4    D5  PWM3/1      SPI1_MISO
PB_5    D4  PWM3/2      SPI1_MOSI
PB_6    D10 PWMx/y?     S1_TX       CS
PB_7                    S1_RX
PB_8    D15                         I2C1_SCL
PB_9    D14                         I2C1_SDA
PB_10   D6  PWM2/3      S3_TX       I2C2_SCL
PB_11       PWM2/4?     S3_RX       I2C2_SDA
PB_12                   SPI2_NSS
PB_13       PWM1/1N     SPI2_SCK
PB_14       PWM1/2N     SPI2_MISO
PB_15       PWM1/3N     SPI2_MOSI

PC_0    A5
PC_1    A4
PC_4                                (ANALOG)
PC_5                                (ANALOG)
PC_6        PWM3/1
PC_7    D9  PWM3/2
PC_8        PWM3/3
PC_9        PWM3/4
PC_10                   S3_TX
PC_12
PC_13       USER_BUTTON

Alternate pins (Px_y_ALTz)
*/


// Parameters

#endif
