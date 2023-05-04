//taskTxUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteUart2.h"
#include "taskTxUart.h"

//Definitions privees
//static const char* TAG = "TASK TX UART2";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
TaskHandle_t xHandleTaskTxUart = NULL;


//Definitions de fonctions publiques:
void taskTxUart()
{
    while(1)
    {
        //if(xQueueReceive(queueTxUart, &))

        


    }

    vTaskDelete(xHandleTaskTxUart);
}





void taskTxUart_initialise(void)
{
  xTaskCreatePinnedToCore(taskTxUart, "Task Tx Uart", TASKTXUART_STACK_SIZE, NULL, TASKTXUART_PRIORITY, &xHandleTaskTxUart, TASKTXUART_CORE);
}