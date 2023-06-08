//taskTxUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteUart2.h"
#include "taskTxUart.h"

//Definitions privees
static const char* TAG = "TASK TX UART2";

//Declarations de fonctions privees:
void taskTxUart_prepareLaTransmission(char* donneesATransmettre, unsigned char nombreATransmettre);

//Definitions de variables privees:
char taskTxUart_octetsATransmettre[TASKRXUART_NOMBRE_DE_DONNEES_MAXIMUM];
unsigned char taskTxUart_nombreOctetsATransmettre;
TASKTXUART taskTxUart_infoRecu;


//Definitions de fonctions privees:
void taskTxUart_prepareLaTransmission(char* donneesATransmettre, unsigned char nombreATransmettre)
{
  int i = 0;
  unsigned char checksum = 0;

  taskTxUart_octetsATransmettre[0] = TASKTXUART_DEBUT_DE_TRAME;
  taskTxUart_octetsATransmettre[1] = nombreATransmettre;
  ESP_LOGW(TAG, "%d donneesATransmettre: %s", nombreATransmettre, donneesATransmettre);
  for(i = 2; i < 2 + nombreATransmettre; i++)
  {
    taskTxUart_octetsATransmettre[i] = donneesATransmettre[i-2];
    checksum += taskTxUart_octetsATransmettre[i];
    if(taskTxUart_octetsATransmettre[i] == TASKTXUART_DEBUT_DE_TRAME)
    {
      i++;
      taskTxUart_octetsATransmettre[i] = TASKTXUART_INSERTION;
    } 
  }
  taskTxUart_octetsATransmettre[i] = checksum;
  taskTxUart_nombreOctetsATransmettre = i + 1;
}

//Definitions de variables publiques:
TaskHandle_t xHandleTaskTxUart = NULL;
QueueHandle_t queueTxUart;

//Definitions de fonctions publiques:
void taskTxUart()
{
    int txBytes;

    while(1)
    {
        if(xQueueReceive(queueTxUart, &taskTxUart_infoRecu, portMAX_DELAY) != pdTRUE)
        {
          ESP_LOGE(TAG, "Erreur: Reception QueueTxUart failed");
        }
        taskTxUart_prepareLaTransmission(taskTxUart_infoRecu.octetsATransmettre, taskTxUart_infoRecu.nombreOctetsATransmettre);
        txBytes = piloteUart2_transmetMessage(taskTxUart_octetsATransmettre, taskTxUart_nombreOctetsATransmettre);
        ESP_LOGI(TAG, "Wrote %d bytes: %s", txBytes, taskTxUart_octetsATransmettre);
    }

    vTaskDelete(xHandleTaskTxUart);
}





void taskTxUart_initialise(void)
{
  queueTxUart = xQueueCreate(5, sizeof(TASKTXUART)); 

  xTaskCreatePinnedToCore(  taskTxUart, 
                            "Task Tx Uart", 
                            TASKTXUART_STACK_SIZE, 
                            NULL, 
                            TASKTXUART_PRIORITY, 
                            &xHandleTaskTxUart, 
                            TASKTXUART_CORE);
}