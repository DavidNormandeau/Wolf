//taskTxUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteUart2.h"
#include "taskRxUart.h"     //pour test seulement
#include "taskTxUart.h"

//Definitions privees
static const char* TAG = "TASK TX UART2";
#define TASKTXUART_NOMBRE_DE_OCTETS_MAX 8

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
char txMessage[TASKTXUART_NOMBRE_DE_OCTETS_MAX];
TASKRXUART test;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
TaskHandle_t xHandleTaskTxUart = NULL;
QueueHandle_t queueTxUart;

//Definitions de fonctions publiques:
void taskTxUart()
{
    int txBytes;

    while(1)
    {
        //if(xQueueReceive(queueTxUart, txMessage, portMAX_DELAY) != pdTRUE)
        if(xQueueReceive(queueRxUart, &test, portMAX_DELAY) != pdTRUE)
        {
          ESP_LOGE(TAG, "Erreur: Reception QueueTxUart failed");
        }

        txBytes = piloteUart2_transmetMessage(test.octetsRecus, test.nombreARecevoir);
        ESP_LOGI(TAG, "Wrote %d bytes", txBytes);
    }

    vTaskDelete(xHandleTaskTxUart);
}





void taskTxUart_initialise(void)
{
  queueTxUart = xQueueCreate(5, sizeof(txMessage));
  
  xTaskCreatePinnedToCore(  taskTxUart, 
                            "Task Tx Uart", 
                            TASKTXUART_STACK_SIZE, 
                            NULL, 
                            TASKTXUART_PRIORITY, 
                            &xHandleTaskTxUart, 
                            TASKTXUART_CORE);
}