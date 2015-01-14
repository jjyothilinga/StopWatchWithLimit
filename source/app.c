#include "app.h" 
#include "linearkeypad.h"
#include "timer.h" 


#define NO_OF_DIGITS			(0X04)
#define EEPROM_STATE_ADDRESS	(0x20)
#define EEPROM_RTC_DATA_ADDRESS (1)
#define DUMMY					(1)

/*
*------------------------------------------------------------------------------
* Public Variables 
*------------------------------------------------------------------------------
*/


void APP_conversion(void);
void APP_resetDisplayBuffer(void);
void APP_updateRTC(void);

/*
*------------------------------------------------------------------------------
* app - the app structure. 
*------------------------------------------------------------------------------
*/
typedef struct _App
{
	APP_STATE state;
	
	UINT8 displayBuffer[NO_OF_DIGITS];
	UINT16 time;

}APP;

#pragma idata app_data
APP app = {0};
#pragma idata


/*
*------------------------------------------------------------------------------
* void APP_init(void)
*
* Summary	: Initialize application
*
* Input		: None
*
* Output	: None
*------------------------------------------------------------------------------
*/
void APP_init( void )
{
	UINT8 i;

	APP_resetDisplayBuffer();
	DigitDisplay_updateBuffer(app.displayBuffer);

	// Turn on dot
	DigitDisplay_DotOn(2, 1);

	app.state = HALT_STATE;

}


/*
*------------------------------------------------------------------------------
* void APP_task(void)
*
* Summary	: 
*
* Input		: None
*
* Output	: None
*------------------------------------------------------------------------------
*/


void APP_task( void )
{

	switch(app.state)
	{
		case HALT_STATE: 
			if ((LinearKeyPad_getKeyState(START_PB) == 1))
			{
				app.state = COUNT_STATE;
				time = 0;
				
				APP_resetDisplayBuffer();
				DigitDisplay_updateBuffer(app.displayBuffer);
				// Turn on dot
				DigitDisplay_DotOn(2, 1);
			}
		break;

		case COUNT_STATE:
			if ((LinearKeyPad_getKeyState(STOP_PB) == 1))
			{
				app.state = HALT_STATE;
				//time = 0;
				break;
				
			}
			app.time = time;
	
			if(app.time >= 1000)
			{
				time = 0;
				++app.displayBuffer[2];
				if(app.displayBuffer[2] > '9')
				{
					app.displayBuffer[2] = '0';
					if(++app.displayBuffer[3] > '9')
						app.displayBuffer[3] = '0';
				}
			}
			
			APP_conversion();
			DigitDisplay_updateBuffer(app.displayBuffer);

			// Turn on dot
			DigitDisplay_DotOn(2, 1);

			// Change state on reaching its maximum limit
			if((app.displayBuffer[3] == '9') && (app.displayBuffer[2] == '9') &&
				(app.displayBuffer[1] == '9') && (app.displayBuffer[0] == '9'))
				app.state = HALT_STATE;

		break;

		default:
		break;
	}

}		




void APP_conversion(void)
{
	UINT8 i, temp[3];

	for(i = 0; i < 3; i++)
	{
		temp[i] = app.time % 10 + '0';
		app.time /= 10;
	}
	for(i = 0; i < 2; i++)
	{
		app.displayBuffer[i] = temp[i+1];
	}
}


void APP_resetDisplayBuffer(void)
{
	UINT8 i , temp;
	for(i = 0; i < NO_OF_DIGITS; i++)			//reset all digits
	{
		app.displayBuffer[i] = '0';
	}
}	

