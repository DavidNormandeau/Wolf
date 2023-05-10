//taskRxUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteUart2.h"
#include "taskRxUart.h"

//Definitions privees
static const char* TAG = "TASK RX UART2";
#define TASKRXUART_NOMBRE_DE_OCTETS_MAX     8
#define TASKRXUART_LECTURE_PAS_DISPONIBLE   0
#define TASKRXUART_LECTURE_DISPONIBLE       1
#define TASKRXUART_TEMPS_DEPASSE            1
#define TASKRXUART_TEMPS_PAS_DEPASSE        0

//Declarations de fonctions privees:
void taskRxUart_attendUnDebut(void);
void taskRxUart_attendLaLongueur(void);
void taskRxUart_attendUneDonnee(void);
void taskRxUart_attendUnZero(void);
void taskRxUart_attendUnChecksum(void);
unsigned char taskRxUart_gereLaSynchronisationDesReceptions(void);
unsigned char taskRxUart_gereLeTempsDAttente(void);
unsigned char taskRxUart_gereUneReception(void);

//Definitions de variables privees:
char rxMessage[TASKRXUART_NOMBRE_DE_OCTETS_MAX];
void (*taskRxUart_execute)(void);
char taskRxUart_reception;
TASKRXUART taskRxUart_info;
unsigned char taskRxUart_compteurDeReceptions;
unsigned char taskRxUart_checksumDeReception;


//Definitions de fonctions privees:
void taskRxUart_attendUnDebut(void)
{
  //ESP_LOGI(TAG, "taskRxUart_attendUnDebut");
  if (taskRxUart_gereUneReception() == TASKRXUART_LECTURE_PAS_DISPONIBLE)
  {
    return;
  }

  if (taskRxUart_reception == TASKRXUART_DEBUT_DE_TRAME)
  {
    //taskRxUart_compteurDeTempsDAttente = 0;
    taskRxUart_execute = taskRxUart_attendLaLongueur;
    return;
  }
//   taskRxUart_info.statut = TASKRXUART_ERREUR_EN_ATTENTE;
//   taskRxUart_info.information = INFORMATION_DISPONIBLE;
}

void taskRxUart_attendLaLongueur(void)
{
//   if (taskRxUart_gereLaSynchronisationDesReceptions() == TASKRXUART_RECEPTION_RETARDEE)
//   {
//     return;
//   }
//   if (taskRxUart_gereLeTempsDAttente() == TASKRXUART_TEMPS_DEPASSE)
//   {
//     taskRxUart_info.statut = TASKRXUART_TEMPS_DEPASSE;
//     taskRxUart_info.information = INFORMATION_DISPONIBLE;
//     taskRxUart_execute =
//         taskRxUart_attendUnDebut;
//   }
    ESP_LOGI(TAG, "Attend La longueur");
    if (taskRxUart_gereUneReception() == TASKRXUART_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }

//   taskRxUart_compteurDeTempsDAttente = 0;
    if (taskRxUart_reception == 0x00)
    {
        // taskRxUart_info.statut = TASKRXUART_ERREUR_LONGUEUR_NULLE;
        // taskRxUart_info.information = INFORMATION_DISPONIBLE;
        taskRxUart_execute = taskRxUart_attendUnDebut;
    }
    
    ESP_LOGI(TAG, "Longueur = %d", taskRxUart_reception);

    //à COMPLÉTER
    if (taskRxUart_reception > TASKRXUART_NOMBRE_DE_OCTETS_MAX)
    {
        taskRxUart_info.statut = TASKRXUART_ERREUR_LONGUEUR_TROP_GRANDE;
        // taskRxUart_info.information = INFORMATION_DISPONIBLE;
        ESP_LOGE(TAG, "Erreur longueur trop grande");
        taskRxUart_execute = taskRxUart_attendUnDebut;
    }
    taskRxUart_info.nombreARecevoir = taskRxUart_reception;
    taskRxUart_compteurDeReceptions = 0;
    taskRxUart_checksumDeReception = 0;
    taskRxUart_execute = taskRxUart_attendUneDonnee;
}

void taskRxUart_attendUneDonnee(void)
{
    ESP_LOGI(TAG, "Attend une donnee");
//   if (taskRxUart_gereLaSynchronisationDesReceptions()
//       == TASKRXUART_RECEPTION_RETARDEE)
//   {
//     return;
//   }
//   if (taskRxUart_gereLeTempsDAttente()
//       == TASKRXUART_TEMPS_DEPASSE)
//   {
//     taskRxUart_info.statut = TASKRXUART_TEMPS_DEPASSE;
//     taskRxUart_info.information = INFORMATION_DISPONIBLE;
//     taskRxUart_execute = taskRxUart_attendUnDebut;
//     return;
//   }
  if (taskRxUart_gereUneReception() == TASKRXUART_LECTURE_PAS_DISPONIBLE)
  {
    return;
  }

//   taskRxUart_compteurDeTempsDAttente = 0;
  taskRxUart_info.octetsRecus[taskRxUart_compteurDeReceptions] = taskRxUart_reception;
  taskRxUart_checksumDeReception += taskRxUart_reception;
  taskRxUart_compteurDeReceptions++;
  if (taskRxUart_reception == TASKRXUART_DEBUT_DE_TRAME)
  {
    taskRxUart_execute = taskRxUart_attendUnZero;
    return;
  }
  if (taskRxUart_compteurDeReceptions == taskRxUart_info.nombreARecevoir)
  {
    taskRxUart_execute = taskRxUart_attendUnChecksum;
    return;
  }
}

void taskRxUart_attendUnZero(void)
{
//   if (taskRxUart_gereLaSynchronisationDesReceptions()
//       == TASKRXUART_RECEPTION_RETARDEE)
//   {
//     return;
//   }
//   if (taskRxUart_gereLeTempsDAttente()
//       == TASKRXUART_TEMPS_DEPASSE)
//   {
//     taskRxUart.statut = TASKRXUART_TEMPS_DEPASSE;
//     taskRxUart.information = INFORMATION_DISPONIBLE;
//     taskRxUart_execute = taskRxUart_attendUnDebut;
//     return;
//   }
    if (taskRxUart_gereUneReception() == TASKRXUART_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }

//   taskRxUart_compteurDeTempsDAttente = 0;
    if (taskRxUart_reception > 0x00)
    {
        taskRxUart_info.statut = TASKRXUART_ERREUR_INSERTION_NON_NULLE;
        ESP_LOGE(TAG, "Erreur insertion non nulle!");
        // taskRxUart.information = INFORMATION_DISPONIBLE; 
        taskRxUart_execute = taskRxUart_attendUnDebut;
        return;
    }
    if (taskRxUart_compteurDeReceptions < taskRxUart_info.nombreARecevoir)
    {
        taskRxUart_execute = taskRxUart_attendUneDonnee;
        return;
    }
    taskRxUart_execute = taskRxUart_attendUnChecksum;
}    

void taskRxUart_attendUnChecksum(void)
{
    // if (taskRxUart_gereLaSynchronisationDesReceptions()
    //     == TASKRXUART_RECEPTION_RETARDEE)
    // {
    //     return;
    // }
    // if (taskRxUart_gereLeTempsDAttente()
    //     == TASKRXUART_TEMPS_DEPASSE)
    // {
    //     taskRxUart.statut = TASKRXUART_TEMPS_DEPASSE;
    //     taskRxUart.information = INFORMATION_DISPONIBLE;
    //     taskRxUart_execute = taskRxUart_attendUnDebut;
    //     return;
    // }

    ESP_LOGI(TAG, "Attend un checksum");
    if (taskRxUart_gereUneReception() == TASKRXUART_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }

    // taskRxUart_compteurDeTempsDAttente = 0;
    if (taskRxUart_reception == taskRxUart_checksumDeReception)
    {
        taskRxUart_info.statut = TASKRXUART_PAS_D_ERREURS;
        // taskRxUart.information = INFORMATION_DISPONIBLE;
        xQueueSend(queueRxUart, &taskRxUart_info, 50/portTICK_PERIOD_MS);                  //TIMEOUT à déterminer
        ESP_LOGI(TAG, "Message recu: %s", taskRxUart_info.octetsRecus);
        taskRxUart_execute = taskRxUart_attendUnDebut;      
        return;
    }
    taskRxUart_info.statut = TASKRXUART_ERREUR_MAUVAIS_CHECKSUM;
    ESP_LOGE(TAG, "Erreur Mauvais checksum");
    // taskRxUart.information = INFORMATION_DISPONIBLE;
    taskRxUart_execute = taskRxUart_attendUnDebut;      
}

// unsigned char taskRxUart_gereLaSynchronisationDesReceptions(void)
// {
//   taskRxUart_compteurDeSynchronisationDesReceptions++;
//   if (taskRxUart_compteurDeSynchronisationDesReceptions < TASKRXUART_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION)
//   {
//     return TASKRXUART_RECEPTION_RETARDEE;
//   }
//   taskRxUart_compteurDeSynchronisationDesReceptions = 0;
//   return TASKRXUART_RECEPTION_PERMISE;
// }

// unsigned char taskRxUart_gereLeTempsDAttente(void)
// {
//   taskRxUart_compteurDeTempsDAttente++;
//   if (taskRxUart_compteurDeTempsDAttente <
//       TASKRXUART_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS)
//   {
//     return TASKRXUART_TEMPS_PAS_DEPASSE; 
//   }
//   return TASKRXUART_TEMPS_DEPASSE;
// }

unsigned char taskRxUart_gereUneReception(void)
{
    if(piloteUart2_octetDisponible() == PILOTEUART2_PAS_DISPONIBLE)
    {
        return TASKRXUART_LECTURE_PAS_DISPONIBLE;
    }
    piloteUart2_recoitMessage(&taskRxUart_reception, sizeof(taskRxUart_reception), (10/portTICK_PERIOD_MS));
    return TASKRXUART_LECTURE_DISPONIBLE;
}
//Definitions de variables publiques:
TaskHandle_t xHandleTaskRxUart = NULL;
QueueHandle_t queueRxUart;

//Definitions de fonctions publiques:
// void taskRxUart()
// {
//     int rxBytes;
//     TickType_t xLastWakeTime;
//     const TickType_t xFrequency = 10;

//     xLastWakeTime = xTaskGetTickCount();
//     while(1)
//     {
//         rxBytes = piloteUart2_recoitMessage(rxMessage, sizeof(rxMessage), (50/portTICK_PERIOD_MS));

//         if(rxBytes > 0)
//         {
//             rxMessage[rxBytes] = 0;
//             ESP_LOGI(TAG, "Read %d bytes: '%s'", rxBytes, rxMessage);

//             xQueueSend(queueRxUart, rxMessage, 50/portTICK_PERIOD_MS);
//         }

//         xTaskDelayUntil(&xLastWakeTime, xFrequency);
//     }

//     vTaskDelete(xHandleTaskRxUart);
// }

void taskRxUart()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;

    
    taskRxUart_execute = taskRxUart_attendUnDebut;
    xLastWakeTime = xTaskGetTickCount();    
    while(1)
    {
        taskRxUart_execute();
        
        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }

    vTaskDelete(xHandleTaskRxUart);
}





void taskRxUart_initialise(void)
{
  queueRxUart = xQueueCreate(5, sizeof(taskRxUart_info));
  
  xTaskCreatePinnedToCore(  taskRxUart, 
                            "Task Rx Uart", 
                            TASKRXUART_STACK_SIZE, 
                            NULL, 
                            TASKRXUART_PRIORITY, 
                            &xHandleTaskRxUart, 
                            TASKRXUART_CORE);
}