#include "p33FJ128GP202.h"
#include "unit_param.h"

#define NO_OF_SEGMENTS	8

typedef enum {
MAX6921_RESET,
MAX6921_INIT,
MAX6921_CLK_LO,
MAX6921_SEND_BIT,
MAX6921_CLK_HI,
MAX6921_LOAD_HI,
MAX6921_LOAD_LO,
MAX6921_WAIT
} t_Max6921_State;

extern int volatile Diplay[NO_OF_SEGMENTS];
extern int volatile Bright[NO_OF_SEGMENTS];	
extern long int volatile sw_timer0;
extern long int volatile sw_timer1;
extern long int volatile sw_timer2;
extern long int volatile sw_timer3;

extern int volatile Blik_1ms;

void timer3init(void);
