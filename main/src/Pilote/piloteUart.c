//piloteUart:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/uart.h"
#include "main.h"
#include "piloteUart.h"

//Definitions privees
//  static const char* TAG = "PILOTEELECTROAIMANT";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteUart_transmet()
{

}

void piloteUart_recoit()
{
    
}

void piloteUart_initialise(void)
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
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    ESP_ERROR_CHECK(uart_set_pin( UART_NUM_2, PILOTEUART_TX_PIN, PILOTEUART_RX_PIN, 
                                    UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, \
                                            uart_buffer_size, 10, &uart_queue, 0));
}