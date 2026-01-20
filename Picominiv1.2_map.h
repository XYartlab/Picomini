/*
  picobob_map.h - driver code for RP2040 ARM processors

  Part of grblHAL

  Copyright (c) 2021-2023 Andrew Marles

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif 
//不支持trim驱动

#if N_ABC_MOTORS > 1
#error "Axis configuration is not supported!"
#endif
//不支持大于4个轴

#define BOARD_NAME "XYmini Board"
#define BOARD_URL "https://github.com/XYart-labs"

#ifdef PICO_FLASH_SIZE_BYTES
#undef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)
#endif
//设置flash为16M，启用littlefs文件系统，不能重复启用
//#define LITTLEFS_ENABLE 1

// Define step pulse output pins. 定义脉冲由pio生成，起始引脚为22
#define STEP_PORT             GPIO_PIO  // N_AXIS pin PIO SM
#define STEP_PINS_BASE        22        // N_AXIS number of consecutive pins are used by PIO

// Define step direction output pins. 定义方向引脚
#define DIRECTION_PORT        GPIO_OUTPUT
#define DIRECTION_OUTMODE     GPIO_SHIFT6 //map=方向引脚可不连续，性能消耗大，gpio_shift6要求方向引脚连续，性能消耗小
#define X_DIRECTION_PIN       9
#define Y_DIRECTION_PIN       10
#define Z_DIRECTION_PIN       11

// Define stepper driver enable/disable output pin. This is not used on PicoBOB. MachBob没有步进使能引脚
//定义使能引脚
//#define ENABLE_PORT             GPIO_OUTPUT
//#define STEPPERS_ENABLE_PIN     6

// Define homing/hard limit switch input pins. 定义限位引脚 
#define LIMIT_PORT            GPIO_INPUT
#define LIMIT_INMODE          GPIO_MAP
#define X_LIMIT_PIN           2
#define Y_LIMIT_PIN           1
#define Z_LIMIT_PIN           5

// Define ganged axis or A axis step pulse and step direction output pins. 定义A轴/平方轴
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PIN           (STEP_PINS_BASE + 3)
#define M3_DIRECTION_PIN      12
#ifdef M3_LIMIT_ENABLE
#define M3_LIMIT_PIN         0
#else
#define SAFETY_DOOR_PIN       AUXINPUT1_PIN
#endif

//#define LED_PWM_PORT            GPIO_OUTPUT // rail LED strip (PWM), does not work when debugging due to U14/R96 chopping output
//#define LED_PWM_PIN             21
//#if RGB_LED_ENABLE
//#define LED_GPO_PIN             21
//#endif

// Define Aux Outputs 定义数字输出引脚
#if RGB_LED_ENABLE
#define NEOPIXELS_PIN         21
#else
#define AUXOUTPUT0_PORT       GPIO_OUTPUT // Led
#define AUXOUTPUT0_PIN        21
#endif
#define AUXOUTPUT1_PORT       GPIO_OUTPUT // Spindle PWM
#define AUXOUTPUT1_PIN        14
#define AUXOUTPUT2_PORT       GPIO_OUTPUT // Spindle enable
#define AUXOUTPUT2_PIN        13
#define AUXOUTPUT3_PORT       GPIO_OUTPUT // Spindle dir
#define AUXOUTPUT3_PIN        15
#define AUXOUTPUT4_PORT       GPIO_OUTPUT // Mist
#define AUXOUTPUT4_PIN        7
#define AUXOUTPUT5_PORT       GPIO_OUTPUT // Flood
#define AUXOUTPUT5_PIN        8

// Define driver spindle pins 定义主轴引脚 
#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_PORT            GPIO_OUTPUT
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PIN         AUXOUTPUT1_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PIN   AUXOUTPUT3_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA   
#define SPINDLE_ENABLE_PIN      AUXOUTPUT2_PIN
#endif

//定义flood和mist引脚
#if COOLANT_ENABLE
#define COOLANT_PORT            GPIO_OUTPUT
#endif
#if COOLANT_ENABLE & COOLANT_FLOOD
#define COOLANT_FLOOD_PIN       AUXOUTPUT5_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
#define COOLANT_MIST_PIN        AUXOUTPUT4_PIN
#endif

//定义输入引脚
#define AUXINPUT1_PIN           0// Door
#define AUXINPUT2_PIN           3// Reset/EStop
#define AUXINPUT3_PIN           4 // Probe
#define AUXINPUT4_PIN           26 // Feed hold
#define AUXINPUT5_PIN           27 // Cycle start

#if CONTROL_ENABLE & CONTROL_HALT //定义急停引脚
#define RESET_PIN             AUXINPUT2_PIN
#endif

#if PROBE_ENABLE                  //定义对刀引脚
#define PROBE_PIN             AUXINPUT3_PIN
#endif

#if CONTROL_ENABLE & CONTROL_FEED_HOLD  //定义进给保持引脚
#define FEED_HOLD_PIN           AUXINPUT4_PIN
#endif

#if CONTROL_ENABLE & CONTROL_CYCLE_START  //定义循环启动引脚
#define CYCLE_START_PIN         AUXINPUT5_PIN
#endif

#if SAFETY_DOOR_ENABLE          //定义安全门引脚
#define SAFETY_DOOR_PIN         AUXINPUT1_PIN
#endif

//#if I2C_ENABLE
//#define I2C_PORT              0
//#define I2C_SDA               28
//#define I2C_SCL               29
//#endif

// UART 1 (Mpg)
#define UART_1_TX_PIN 28
#define UART_1_RX_PIN 29

#if SDCARD_ENABLE || ETHERNET_ENABLE
#define SPI_PORT              0
#define SPI_SCK_PIN           18
#define SPI_MOSI_PIN          19
#define SPI_MISO_PIN          16

#if SDCARD_ENABLE
#define SD_CS_PIN             6
#endif

#if ETHERNET_ENABLE
#define SPI_CS_PIN            17
#define SPI_IRQ_PIN           20
//#define SPI_RST_PORT        GPIO_OUTPUT
//#define SPI_RST_PIN         21
#endif

#endif  // SDCARD_ENABLE || ETHERNET_ENABLE