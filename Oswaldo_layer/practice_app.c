//Capa_UsuarioFinal_Aplicacion

//Libraries
#include "practice1.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
//Libraries

void cb_app(uint8_t *data, uint32_t len)
{
	PRINTF((char*)data);
	PRINTF("\n\r");
}

int main(void) {

    //Init_Hardware_Functions
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    //Init_FSL debug console
    BOARD_InitDebugConsole();
#endif

    Ethernet_Configuration_Init(cb_app); //ThisCallback_is_neccesary_here (dont_move...)

    char pck1[] = "Probando_Mensaje_Desencriptado"; 				Ethernet_Data_Transmit((uint8_t*)pck1, sizeof(pck1));
	char pck2[] = "PruebaNumero_2";									Ethernet_Data_Transmit((uint8_t*)pck2, sizeof(pck2));
	char pck3[] = "PruebaNumero_3";									Ethernet_Data_Transmit((uint8_t*)pck3, sizeof(pck3));
	char pck4[] = "Prueba_Numero_4000_naa_es_4";					Ethernet_Data_Transmit((uint8_t*)pck4, sizeof(pck4));
	char pck5[] = "Probando_n5";									Ethernet_Data_Transmit((uint8_t*)pck5, sizeof(pck5));
	char pck6[] = "Probando_n6";									Ethernet_Data_Transmit((uint8_t*)pck6, sizeof(pck6));
	char pck7[] = "Probando_n7";									Ethernet_Data_Transmit((uint8_t*)pck7, sizeof(pck7));
	char pck8[] = "PaquetesTerminados";								Ethernet_Data_Transmit((uint8_t*)pck8, sizeof(pck8));

    while(1) {};

    return 0 ;
}
