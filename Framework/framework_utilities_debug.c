#include "framework_utilities_debug.h"

//调试时开启
#ifdef _FW_DEBUG
	#include "usart.h"
	#ifdef __GNUC__
		#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#else
		#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#endif 
	PUTCHAR_PROTOTYPE
	{
		HAL_UART_Transmit(&huart3 , (uint8_t *)&ch, 1, 0xFFFF);
		return ch;
	}
#endif
