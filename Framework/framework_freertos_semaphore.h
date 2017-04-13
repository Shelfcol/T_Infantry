#ifndef FRAMEWORK_FREERTOS_SEMAPHORE_H
#define FRAMEWORK_FREERTOS_SEMAPHORE_H

#include "cmsis_os.h"

extern osSemaphoreId motorCanTransmitSemaphoreHandle;
extern osSemaphoreId readMPU6050SemaphoreHandle;
extern osSemaphoreId refreshMPU6050SemaphoreHandle;
extern xSemaphoreHandle xSemaphore_uart;
extern xSemaphoreHandle xSemaphore_rcuart;
extern xSemaphoreHandle motorCanReceiveSemaphore;

#endif
