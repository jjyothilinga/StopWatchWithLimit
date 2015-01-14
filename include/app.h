#include "board.h"
#include "typedefs.h"
#include "digitdisplay.h"


typedef enum 
{
	COUNT_STATE = 0,
	HALT_STATE
}APP_STATE;

typedef enum 
{
	START_PB = 0,
	STOP_PB = 1,
	RESET_PB
}PB;

typedef enum
{
	MINUTES_LSB = 0,
	MINUTES_MSB,
	HOURS_LSB,
	HOURS_MSB,
	MINUTES_LSB_MAX = '9',
	MINUTES_MSB_MAX = '5',
	HOURS_LSB_MAX = '9',
	HOURS_MSB_MAX = '2'

}TIME_DIGITS;


extern void APP_init(void);
extern void APP_task(void);
