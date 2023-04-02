//piloteUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/uart.h"
#include "main.h"
#include "piloteUart2.h"

//Definitions privees
//static const char* TAG = "PILOTE UART2";
#define RX_TIMEOUT (100/ portTICK_PERIOD_MS)
#define TX_TIMEOUT (100/ portTICK_PERIOD_MS)

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
int piloteUart2_transmetMessage(char* buffer, size_t nombreDOctetATransmettre)
{
    return (uart_write_bytes(UART_NUM_2, buffer, nombreDOctetATransmettre));
}

int piloteUart2_recoitMessage(char* buffer, uint32_t length)
{
    return uart_read_bytes(UART_NUM_2, buffer, length, RX_TIMEOUT);
}

esp_err_t piloteUart2_attendFinTransmission()
{
    return (uart_wait_tx_done(UART_NUM_2, TX_TIMEOUT));
}

esp_err_t piloteUart2_effaceRxBuffer()
{
    return uart_flush(UART_NUM_2);
}

esp_err_t piloteUart2_termine()
{
    return uart_driver_delete(UART_NUM_2);
}

esp_err_t piloteUart2_initialise(void)
{
    const uart_port_t uart_num = UART_NUM_2;

    uart_config_t uart_config = {
        .baud_rate = PILOTEUART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    }; 
    if(uart_param_config(uart_num, &uart_config)) { return ESP_FAIL; }


    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    if(uart_set_pin(    UART_NUM_2, PILOTEUART2_TX_PIN, PILOTEUART2_RX_PIN, 
                        UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE))
    {
        return ESP_FAIL;
    }

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    if(uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0)) 
    { 
        return ESP_FAIL; 
    }

    return ESP_OK;
}