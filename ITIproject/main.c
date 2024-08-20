
#define F_CPU 8000000UL
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "ADC_interface.h"
#include "TIMER1_interface.h"
#include "TIMER_interface.h"
#include "USART_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "MAP.h"
#include <util/delay.h>
#include <avr/eeprom.h>
#include <string.h>


#define USERNAME_MAX_LEN 10
#define PASSWORD_LEN 5
#define MAX_USERS 10
#define EEPROM_START_ADDRESS 0x00
#define LDR_CHANNEL 0
#define LM35_CHANNEL 1
// Global variables
static u8 door_status=0;
static u8 fan_status=0;
static u8 Light_status=0;

u8 username[USERNAME_MAX_LEN + 1] = {0}; // +1 for null terminator
u8 password[PASSWORD_LEN + 1] = {0}; // +1 for null terminator
u8 eeprom_username[USERNAME_MAX_LEN + 1];
u8 eeprom_password[PASSWORD_LEN + 1];
u16 index = 0;
u8 option, LDR_State;
u8 mode;
u8 buzzer_flag,Reset_flag;

void LDR() ;/*called in the while loop*/
void manual_light();
void LED_Control_PWM(u8 option);
void Smart_Home_Initialization();
void display_welcome();
void scan_eeprom_for_users();
void clear_eeprom();
u8 get_mode_selection();
void user_registration();
u8 check_username();
void user_deletion();
void user_login();
void enable_buzzer();
void door();
u32 measure_temperature();
void fan_auto_control();
void fan_manual_control();
void fan();
void control_status_menu();
void Control_menu();
void Status_menu();
void Login_menu();
void Reset();
void Light();

int main() {
    Smart_Home_Initialization();
    scan_eeprom_for_users();

    while (1) {
    	Reset_flag=0;
    	Login_menu();
    }
    return 0;
}

void Smart_Home_Initialization() {

    DIO_SetPort_Direction(DIO_PORTC, PORT_OUTPUT);
    DIO_SetPort_Direction(DIO_PORTB, PORT_OUTPUT);
    /*ADC*/
    DIO_SetPin_Direction(DIO_PORTA, DIO_PIN0, PIN_INPUT);
    DIO_SetPin_Direction(DIO_PORTA, DIO_PIN1, PIN_INPUT);
    /*oc1*/
    DIO_SetPin_Direction(DIO_PORTD, DIO_PIN5, PIN_OUTPUT);

    /*EXTI INT0*/
    DIO_SetPin_Direction(DIO_PORTD,DIO_PIN2,PIN_INPUT);
    DIO_SetPinValue(DIO_PORTD,DIO_PIN2,PIN_HIGH);

    EXTIvoid_Enable(EXTI_0,2);
    EXTI_Set_voidCallBackINT0(Reset);
    GIE_voidEnable();
    ADC_voidINIT();
	Timer0_voidInit();
    CLCD_voidINIT();
    USART_voidINIT();
    display_welcome();



}

void display_welcome() {
    CLCD_voidSendString("    WELCOME!");
    _delay_ms(1000);
    CLCD_clear();
}

void scan_eeprom_for_users() {
    while (index < MAX_USERS * (USERNAME_MAX_LEN + PASSWORD_LEN)) {
        eeprom_read_block((void*)eeprom_username, (const void*)index, USERNAME_MAX_LEN);
        if (eeprom_username[0] == 0xFF) {
            break;
        }
        index += (USERNAME_MAX_LEN + PASSWORD_LEN);
    }
}
void clear_eeprom() {
    for (u16 addr = EEPROM_START_ADDRESS; addr < index; addr++) {
        eeprom_write_byte((uint8_t*)addr, 0xFF); // Write 0xFF to clear the EEPROM
    }
    index = EEPROM_START_ADDRESS; // Reset the index
    CLCD_clear();
    CLCD_voidSendString("EEPROM Cleared");
    _delay_ms(1000);
}

u8 get_mode_selection() {
	CLCD_clear();
    CLCD_voidGOTOXY(0, 0);
    CLCD_voidSendString("1)Register ");
    CLCD_voidGOTOXY(1, 0);
    CLCD_voidSendString("2)Login 3)Delete");


    mode = USART_u8ReceiveSynhronous();
    CLCD_clear();
    return mode;
}

void user_registration() {
    if (index >= MAX_USERS * (USERNAME_MAX_LEN + PASSWORD_LEN)) {
        CLCD_voidSendString("Max users saved");
        _delay_ms(1000);
        return;
    }

    CLCD_voidSendString("enter username:");
    CLCD_voidGOTOXY(1, 0);
    for (u8 i = 0; i < USERNAME_MAX_LEN; i++) {
        username[i] = USART_u8ReceiveSynhronous();
        if (username[i] == '\r') break;
        CLCD_voidSendData(username[i]);
    }
    username[USERNAME_MAX_LEN] = '\0';
    _delay_ms(500);
    CLCD_clear();

    CLCD_voidSendString("enter password:");
    CLCD_voidGOTOXY(1, 0);
    for (u8 i = 0; i < PASSWORD_LEN; i++) {
        password[i] = USART_u8ReceiveSynhronous();
        CLCD_voidSendData('*');
    }
    password[PASSWORD_LEN] = '\0';
    _delay_ms(500);
    CLCD_clear();

    if (check_username() == 1) {
        CLCD_voidSendString("Already saved!");
        _delay_ms(1000);
    } else {
        eeprom_write_block((const void*)username, (void*)index, USERNAME_MAX_LEN);
        eeprom_write_block((const void*)password, (void*)(index + USERNAME_MAX_LEN), PASSWORD_LEN);
        index += (USERNAME_MAX_LEN + PASSWORD_LEN);
        CLCD_voidSendString("Account Saved");
        _delay_ms(1000);
    }
    CLCD_clear();
}

u8 check_username() {
    for (u16 i = 0; i < index; i += (USERNAME_MAX_LEN + PASSWORD_LEN)) {
        eeprom_read_block((void*)eeprom_username, (const void*)i, USERNAME_MAX_LEN);
        eeprom_username[USERNAME_MAX_LEN] = '\0';

        if (strcmp((char*)eeprom_username, (char*)username) == 0) {
            return 1;
        }
    }
    return 0;
}

void user_deletion() {
    CLCD_voidSendString("enter user to delete:");
    CLCD_voidGOTOXY(1, 0);
    for (u8 i = 0; i < USERNAME_MAX_LEN; i++) {
        username[i] = USART_u8ReceiveSynhronous();
        if (username[i] == '\r') break;
        CLCD_voidSendData(username[i]);
    }
    username[USERNAME_MAX_LEN] = '\0';
    _delay_ms(500);
    CLCD_clear();

    if (check_username() == 0) {
        CLCD_voidSendString("user not found");
        _delay_ms(1000);
    } else {
        for (u16 j = 0; j < index; j += (USERNAME_MAX_LEN + PASSWORD_LEN)) {
            eeprom_read_block((void*)eeprom_username, (const void*)j, USERNAME_MAX_LEN);
            if (strcmp((char*)eeprom_username, (char*)username) == 0) {
                for (u16 k = j; k < index - (USERNAME_MAX_LEN + PASSWORD_LEN); k += (USERNAME_MAX_LEN + PASSWORD_LEN)) {
                    eeprom_read_block((void*)eeprom_username, (const void*)(k + USERNAME_MAX_LEN + PASSWORD_LEN), USERNAME_MAX_LEN);
                    eeprom_read_block((void*)eeprom_password, (const void*)(k + USERNAME_MAX_LEN + PASSWORD_LEN + USERNAME_MAX_LEN), PASSWORD_LEN);

                    eeprom_write_block((const void*)eeprom_username, (void*)k, USERNAME_MAX_LEN);
                    eeprom_write_block((const void*)eeprom_password, (void*)(k + USERNAME_MAX_LEN), PASSWORD_LEN);
                }
                index -= (USERNAME_MAX_LEN + PASSWORD_LEN);
                CLCD_voidSendString("user deleted");
                _delay_ms(1000);
                break;
            }
        }
    }
    CLCD_clear();
}

void user_login() {
	CLCD_clear();
    buzzer_flag = 0;

    while (1) {
        CLCD_voidSendString("enter username:");
        CLCD_voidGOTOXY(1, 0);
        for (u8 i = 0; i < USERNAME_MAX_LEN; i++) {
            username[i] = USART_u8ReceiveSynhronous();
            if (username[i] == '\r') break;
            CLCD_voidSendData(username[i]);
        }
        username[USERNAME_MAX_LEN] = '\0';
        _delay_ms(500);
        CLCD_clear();

        CLCD_voidSendString("enter password:");
        CLCD_voidGOTOXY(1, 0);
        for (u8 i = 0; i < PASSWORD_LEN; i++) {
            password[i] = USART_u8ReceiveSynhronous();
            CLCD_voidSendData('*');
        }
        password[PASSWORD_LEN] = '\0';
        _delay_ms(500);
        CLCD_clear();

        for (u16 i = 0; i < index; i += (USERNAME_MAX_LEN + PASSWORD_LEN)) {
            eeprom_read_block((void*)eeprom_username, (const void*)i, USERNAME_MAX_LEN);
            eeprom_username[USERNAME_MAX_LEN] = '\0';
            eeprom_read_block((void*)eeprom_password, (const void*)(i + USERNAME_MAX_LEN), PASSWORD_LEN);
            eeprom_password[PASSWORD_LEN] = '\0';

            if (strcmp((char*)eeprom_username, (char*)username) == 0 && strcmp((char*)eeprom_password, (char*)password) == 0) {
                CLCD_voidSendString("Login successful");
                //_delay_ms(1000);
                door_status=Servo_Open_Door();
                door_status=Servo_Close_Door();
                control_status_menu();

                return;
            }
        }

        CLCD_voidSendString("Invalid user");
        _delay_ms(1000);
        if (++buzzer_flag == 3) {
            enable_buzzer();
            break;
        }
        CLCD_clear();
    }
}

void enable_buzzer() {
    DIO_SetPinValue(DIO_PORTB, DIO_PIN4, PIN_HIGH); // Alarm
    CLCD_clear();
    CLCD_voidSendString("system locked");
//    _delay_ms(5000);
//    DIO_SetPinValue(DIO_PORTB, DIO_PIN4, PIN_LOW);
}
void door(){
	while(1){
	u8 choice;
	CLCD_clear();
	CLCD_voidGOTOXY(0, 0);
	CLCD_voidSendString("1)Open   2)close");
	CLCD_voidGOTOXY(1, 0);
	CLCD_voidSendString("3)Back ");
	choice= USART_u8ReceiveSynhronous();
	switch(choice){
	case '1':
		if (door_status==1)
			{CLCD_clear();
			CLCD_voidSendString("Already Opened!");
			_delay_ms(500);
			door();}
			else
		door_status=Servo_Open_Door();
	break;
	case '2':
		if (door_status==0)
		{CLCD_clear();
		CLCD_voidSendString("Already closed!");
		_delay_ms(500);
		door();}
		else
		door_status=Servo_Close_Door();
	break;
	case '3':
		Control_menu();
	default:
	CLCD_clear();
	CLCD_voidGOTOXY(0, 0);
	CLCD_voidSendString("Invalid Option!");
	}
	}
}
u32 measure_temperature(){
	 u32 temperature;
	  u16 adc_value=0;

	 adc_value =ADC_u16GetChannelReading(LM35_CHANNEL);
	 temperature=(((u32)adc_value)*500)/1024;

	return temperature;
}

void fan(){
	while(1){
	u8 choice;
	CLCD_clear();
	CLCD_voidGOTOXY(0, 0);
	CLCD_voidSendString("1)Auto  2)manual");
	CLCD_voidGOTOXY(1, 0);
	CLCD_voidSendString("3)Back");
	choice =USART_u8ReceiveSynhronous();
	switch(choice){
	case '1':fan_auto_control();
	break;
	case '2':fan_manual_control();
	break;
	case '3':Control_menu();
	break;
	default:CLCD_clear();
	CLCD_voidGOTOXY(0, 0);
	CLCD_voidSendString("Invalid Choice!");
	}
	}
}
void fan_auto_control()
{  while(1){
	u8 choice;
	u8 fanStat[4];
	if(measure_temperature()>27)
		{DIO_SetPinValue(DIO_PORTB,DIO_PIN5,PIN_HIGH);
		fan_status=1;}
	else
		{DIO_SetPinValue(DIO_PORTB,DIO_PIN5,PIN_LOW);
		fan_status=0;
		}
		CLCD_clear();
		strcpy(fanStat, fan_status ? "ON" : "OFF");
		CLCD_voidGOTOXY(0,0);
		CLCD_voidSendString("temp= ");
		CLCD_voidWriteNumber(measure_temperature(),0,7);
		CLCD_voidGOTOXY(1,0);
		CLCD_voidSendString("Fan: ");
		CLCD_voidSendString(fanStat);
		CLCD_voidGOTOXY(1,9);
		CLCD_voidSendString("1)Back");
		choice=USART_u8ReceiveSynhronous();
		if (choice=='1'){
		fan();
		}
}

}
void fan_manual_control(){
	re:
	while(1){
	u8 choice;
	CLCD_clear();
	CLCD_voidGOTOXY(0, 0);
	CLCD_voidSendString("1)Open   2)Close");
	CLCD_voidGOTOXY(1, 0);
	CLCD_voidSendString("3)Back");
	choice=USART_u8ReceiveSynhronous();
		switch (choice) {
		case '1':
			if (fan_status == 0) {
				DIO_SetPinValue(DIO_PORTB, DIO_PIN5, PIN_HIGH);
				fan_status = 1;
			} else {
				CLCD_clear();
				CLCD_voidSendString("Already Opened!");
				_delay_ms(1000);
				goto re;
			}
			break;
		case '2':
			if (fan_status == 1) {
				DIO_SetPinValue(DIO_PORTB, DIO_PIN5, PIN_LOW);
				fan_status = 0;
			} else {
				CLCD_clear();
				CLCD_voidSendString("Already Closed!");
				_delay_ms(1000);
				fan_manual_control();
			}
			break;
		case '3':
			fan();
		default:
			CLCD_voidGOTOXY(0, 0);
			CLCD_voidSendString("Invalid Choice!");
			fan();
		}
	}
}
void control_status_menu() {
	u8 choice;
	re:
    CLCD_clear();
    CLCD_voidGOTOXY(0, 0);
    CLCD_voidSendString("1)Control");
    CLCD_voidGOTOXY(1, 0);
    CLCD_voidSendString("2)Status  3)Back");

    // Receive user input
    choice = USART_u8ReceiveSynhronous(); // Receive the user's choice

    switch (choice) {
        case '1': // ASCII for '1'
            Control_menu();
            break;
        case '2': // ASCII for '2'
            Status_menu();
            break;
        case '3':
        	Login_menu();

        	break;
        default:
        	CLCD_clear();
            CLCD_voidGOTOXY(0, 0);
            CLCD_voidSendString("Invalid Choice!");
            _delay_ms(1000);
            goto re; // Recursively call to prompt the user again
            break;
    }
}

void Control_menu() {
	re:
	while(1){
    u8 choice;
    CLCD_clear();
    CLCD_voidGOTOXY(0, 0);
    CLCD_voidSendString("1)Door  2)Light");
    CLCD_voidGOTOXY(1, 0);
    CLCD_voidSendString("3)Fan   4)Back");

    // Receive user input
    choice = USART_u8ReceiveSynhronous();

    switch (choice) {
        case '1': // ASCII for '1'
            door();
            break;
        case '2': // ASCII for '2'
           Light();
            break;
        case '3': // ASCII for '3'
            fan();
            break;
        case '4': // ASCII for '4'
            control_status_menu();// Go back to the previous menu
            break;
        default:
        	CLCD_clear();
            CLCD_voidGOTOXY(0, 0);
            CLCD_voidSendString("Invalid Choice!");
            _delay_ms(1000);
            goto re; // Recursively call to prompt the user again
    }
    }
}

void Status_menu() {
	re:
	while(1){
    u8 fanStat[4], doorStat[4],lightStat[4], choice;

    strcpy(doorStat, door_status ? "ON" : "OFF");
    strcpy(fanStat, fan_status ? "ON" : "OFF");
    strcpy(lightStat, Light_status ? "ON" : "OFF");

    CLCD_clear();
    CLCD_voidGOTOXY(0, 0);
    CLCD_voidSendString("Door Light Temp");
    CLCD_voidGOTOXY(1, 0);
    CLCD_voidSendString(doorStat);
    CLCD_voidGOTOXY(1, 5);
    CLCD_voidSendString(lightStat);
     CLCD_voidWriteNumber(measure_temperature(), 1, 12);
    _delay_ms(2000);

    CLCD_clear();
    CLCD_voidGOTOXY(0, 0);
    CLCD_voidSendString("Fan");
    CLCD_voidGOTOXY(1, 0);
    CLCD_voidSendString(fanStat);
    CLCD_voidGOTOXY(1, 10);
    CLCD_voidSendString("1)Back");
    choice=USART_u8ReceiveSynhronous();
    if (choice=='1')
    	control_status_menu();
    else
    {
    	    CLCD_clear();
    	    CLCD_voidGOTOXY(0, 0);
    	    CLCD_voidSendString("Invalid Choice");
    	    _delay_ms(1000);
    	    goto re;
    }

     // Return to the previous menu after displaying the status
	}
}
void LED_Control_PWM(u8 option) {
    u8 duty_cycle;

    /* Set the duty cycle based on the mode */
    switch (option) {
		case 1:
			duty_cycle = 0;  /* 0% brightness */
			break;
        case 2:
            duty_cycle = 25;  /* 25% brightness */
            break;
        case 3:
            duty_cycle = 50;  /* 50% brightness */
            break;
        case 4:
            duty_cycle = 100;  /* 100% brightness */
            break;
        default:
            duty_cycle = 0;   /* LED off for any other value */
            CLCD_clear();
            CLCD_voidSendString("Invalid Option");
            _delay_ms(500);
            return;
    }

    /* Set the duty cycle for PWM */
    Timer0_voidSetCompMatchValue((duty_cycle * 255UL) / 100UL);
}



void manual_light(){
	do{re:
	CLCD_clear();
	CLCD_voidSendString("1)0% 2)25% 3)50%");
	CLCD_voidGOTOXY(1,0);
	CLCD_voidSendString("4)100%  5)back");
     option=USART_u8ReceiveSynhronous();
    if(option=='5')
    {
    	Light(); /*back*/
    }
    else if(option<'5' && option>'0')
	{
		if (option == '1') {
			Light_status = 0;
		} else {
			Light_status = 1;
		}
 	     LED_Control_PWM(option-'0');

	}
	else
	{
		CLCD_clear();
		CLCD_voidSendString("Invalid Option");
		_delay_ms(1000);
		goto re;
	}
	}while(option!='5');

}

void LDR() {
	CLCD_clear();
	CLCD_voidSendString("Auto light:");
	CLCD_voidGOTOXY(1,0);
	CLCD_voidSendString("adjusting light..");
    u16 read;
    u8 value;
    read = ADC_u16GetChannelReading(LDR_CHANNEL);
    value = Map(0, 1023, 0, 15, read);
    if (value > 13) {
            /* 0% */
            LDR_State = 1;
        }
     else if (value > 10) {
            /* 25% light */
            LDR_State = 2;
        }
     else if (value > 5) {
            /* 50% light */
            LDR_State = 3;
        }
     else {
            /* 100% light */
            LDR_State = 4;
        }
	if (LDR_State == 1) {
		Light_status = 0;
	} else {
		Light_status = 1;
	}
    	LED_Control_PWM(LDR_State);
    	_delay_ms(1000);
    	Light();

 }
void Light(){
	re:
	CLCD_clear();
	CLCD_voidSendString("LIGHT:   1)Auto" );
	CLCD_voidGOTOXY(1,0);
	CLCD_voidSendString("2)Manual 3)Back");
	option=USART_u8ReceiveSynhronous();
	switch (option) {

	case '1':
		LDR();
		break;
	case '2':
		manual_light();
		break;
	case '3':
		Control_menu();
		break;
	default:
		CLCD_clear();
		CLCD_voidGOTOXY(0, 0);
		CLCD_voidSendString("Invalid Choice");
		_delay_ms(1000);
		goto re;
		break;

	}
}
 void Login_menu(){


 	get_mode_selection();
     switch (mode) {
         case '1':
             user_registration();
             break;
         case '2':
         	user_login();
         	while((buzzer_flag==3)&&(Reset_flag==0));
             break;
         case '3':
         	user_deletion();
             break;
         default:
             CLCD_voidSendString("Invalid mode!");
             _delay_ms(1000);
             CLCD_clear();
             break;
     }
 }
 void Reset()
 {

	 DIO_SetPinValue(DIO_PORTB, DIO_PIN4, PIN_LOW);
	 clear_eeprom();
	 Reset_flag=1;
 }
