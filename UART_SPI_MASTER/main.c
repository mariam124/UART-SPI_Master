#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "DIO_interface.h"
#include "led_interface.h"
#include "led_precfg.h"
#include "LCD_interface.h"
#include "LCD_PreCFG.h"
#include "UART_interface.h"
#include "UART_Cfg.h"
#include "SPI_interface.h"
#include "SPI_Cfg.h"
//#include <avr/delay.h>
//#include "avr/io.h"

int main (){

	uint8_t Data_Sent , loop = 0 ;

	uint8_t Data_Recieved = 0;

	uint8_t Data_UART[]="ENTER OPERATION";

	str_UartConfg_t Uart_init_STRUC;

	Uart_init_STRUC.u32_BaudRate=9600;

	Uart_init_STRUC.u8_DataBits=UART_8_BIT_MODE;

	Uart_init_STRUC.u8_FlagAction=UART_POLLING;

	MCAL_UART_init(&Uart_init_STRUC);

    MCAL_SPI_MasterInit(SPI_MASTER_FREQUENCY_4);

    HAL_LCD_voidInit();

	DIO_LED_VOIDINIT();

		while(Data_UART[loop] != '\0')
		{
			MCAL_UART_sendByteBusyWait(Data_UART[loop]);

			loop ++ ;
		}

	while (1)
	{

			MCAL_UART_recieveByteBusyWait(&Data_Sent);

			if ((Data_Sent>='0'&&Data_Sent<='9')|| (Data_Sent>='A'&&Data_Sent<='Z')||(Data_Sent>='a'&&Data_Sent<='z')){

				HAL_LCD_voidWriteCharacter((uint8_t)Data_Sent);

				MCAL_SPI_Master_DataBusyWait(Data_Sent, &Data_Recieved);
		}
	}
}

