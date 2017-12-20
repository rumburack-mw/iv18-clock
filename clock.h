#include "p33FJ128GP202.h"
#include "unit_param.h"


typedef enum {
DISP_CLOCK,
SET_HOURS,
SET_MINS,
SET_SECS,
SET_2,
SET_3,
SET_4,
SET_5,
SET_6,
SET_7,
SET_8,
SET_STORE,
DISP_TEMP_CLEAR,
DISP_TEMP
} t_set;


typedef struct  {
	unsigned int volatile input;
   	unsigned int volatile laststate;
   	unsigned int volatile debounced;
   	unsigned int volatile puls;
   	unsigned int volatile state_debounced_old;
	unsigned int volatile last_state_debounced;
	unsigned int volatile sample_old;
} t_debouncer;

typedef struct  {
	unsigned int volatile input;
   	unsigned int volatile input_pom;
	unsigned int volatile output;
} t_toggle;

void toggle(t_toggle *toggle);
void debouncer(t_debouncer *debouncer, unsigned int volatile sample);