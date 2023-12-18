#ifndef BLACKPIN_ID_H
#define BLACKPIN_ID_H

/* The gpio number of the pin*/
enum GPIO_ID {
  P8_07 = 66,
  P8_08 = 67,
  P8_09 = 69,
  P8_10 = 68,
  P8_11 = 45,
  P8_12 = 44,
  P8_14 = 26,
  P8_15 = 47,
  P8_16 = 46,
  P8_17 = 27,
  P8_18 = 65,
  P8_26 = 61,
  P9_11 = 30,
  P9_12 = 60,
  P9_13 = 31,
  P9_15 = 48,
  P9_17 = 5,
  P9_18 = 4,
  P9_23 = 49,
  P9_24 = 15,
  P9_26 = 14,
  P9_27 = 115,
  P9_30 = 112,
  P9_41 = 20,
  P9_42 = 7
};

/* The pwm internal class number of the pin*/
enum PWM_ID {
  P8_13 = 0,
  P8_19 = 1,
  P9_14 = 2,
  P9_16 = 3,
  P9_21 = 4,
  P9_22 = 5
};

/* The pwm class internal number of the pin*/
enum ADC_ID {
  P9_39 = 0,
  P9_40 = 1,
  P9_37 = 2,
  P9_38 = 3,
  P9_33 = 4,
  P9_36 = 5,
  P9_35 = 6
};

#endif // BLACKPIN_ID_H
