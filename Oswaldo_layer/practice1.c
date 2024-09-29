
//Libraries
#include "Driver_ETH_MAC.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_enet.h"
#include "fsl_enet_cmsis.h"
#include "fsl_enet_phy_cmsis.h"
#include "fsl_phy.h"
#include "stdlib.h"
#include "fsl_common.h"
#include "fsl_sysmpu.h"
#include "fsl_phyksz8081.h"
#include "fsl_enet_mdio.h"
#include "RTE_Device.h"
#include "fsl_crc.h"
#include "aes.h"
#include "practice1.h"

//Crc32_Aes128_Variables
CRC_Type *base = CRC0;
uint32_t checksum32;

uint8_t key[] = AES128_KEY;
uint8_t iv[] = AES128_IV;
struct AES_ctx ctx;
//Crc32_Aes128_Variables

volatile uint32_t g_rxIndex    = 0;
volatile uint32_t g_rxCheckIdx = 0;
volatile uint32_t g_txCheckIdx = 0;
volatile uint32_t g_testTxNum  = 0;

uint8_t g_frame[ENET_DATA_LENGTH + 14];
uint8_t source_macAddr[6]           = SOURCE_MAC_ADDRESS;
uint8_t destination_macAddr[6]      = DESTINATION_MAC_ADDRESS;
uint8_t flagReception = 0;

receive_cb_function *User_ENET_Receive_Cb;
mdio_handle_t mdioHandle = {.ops = &enet_ops};
phy_handle_t phyHandle   = {.phyAddr = RTE_ENET_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &phyksz8081_ops};



//********************************************************CRC32_Integration************************************************************
static void InitCrc32(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial         = 0x04C11DB7U;
    config.seed               = seed;
    config.reflectIn          = true;
    config.reflectOut         = true;
    config.complementChecksum = true;
    config.crcBits            = kCrcBits32;
    config.crcResult          = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

uint32_t ComputeCRC32(uint8_t *testData, uint32_t size)
{
	InitCrc32(base, 0xFFFFFFFFU);
	CRC_WriteData(base, (uint8_t *)&testData[0], size);
	return CRC_Get32bitResult(base);
} //********************************************************CRC32_Integration************************************************************





//********************************************************AES128_Integration************************************************************
static void aes128_init()
{
	AES_init_ctx_iv(&ctx, key, iv); //Init_AES_Structure
}

static uint32_t aes128_encrypt(uint8_t *data, uint32_t len, uint8_t *output_array)
{
	uint32_t padded_len = len + (16 - (len%16));

	aes128_init();

	memcpy(output_array, data, len); //Add_data_to_final_data_array
	AES_CBC_encrypt_buffer(&ctx, output_array, padded_len); //Encrypt_Data

	return padded_len;
} //********************************************************AES128_Integration******************************************************





uint8_t verifyDataCRC(uint8_t *data, uint32_t size)
{
	uint8_t status = CRC_NOT_OK;
	uint32_t dataCRC32 = 0;
	uint32_t computedCRC32 = 0;
	uint32_t length = data[12] << 8 | data[13];

	dataCRC32 |= data[length + 14 -4] << 24;
	dataCRC32 |= data[length + 14 -3] << 16;
	dataCRC32 |= data[length + 14 -2] << 8;
	dataCRC32 |= data[length + 14 -1];
	computedCRC32 = ComputeCRC32(&data[14], length - 4);

	if(computedCRC32 == dataCRC32) //Compare_crc32_Validation
	{
		status = CRC_OK;
	}

	return status;
}


static uint32_t Ethernet_BufferBroadcast(uint8_t *data, uint32_t len)
{
	uint32_t data_len = 0;

	memset(&g_frame[0], 0, sizeof(g_frame)); 			//Clean_output_F
    memcpy(&g_frame[0], &destination_macAddr[0], 6U); 	//Copy_Destionation_Mac
    memcpy(&g_frame[6], &source_macAddr[0], 6U);		//Copy_Source_Mas
    data_len = aes128_encrypt(data, len, &g_frame[14]);	//Encode_meesage_aes128

	__disable_irq();

	uint32_t dataCRC32 = ComputeCRC32(&g_frame[14], data_len); //Add_checksum
	__enable_irq();

    g_frame[data_len + 14] = (dataCRC32 >> 24) & 0xFFU;
    g_frame[data_len + 15] = (dataCRC32 >> 16) & 0xFFU;
    g_frame[data_len + 16] = (dataCRC32 >> 8) & 0xFFU;
    g_frame[data_len + 17] = dataCRC32 & 0xFFU;

    data_len += 4; //Add_byte_crc32_length
    g_frame[12] = (data_len >> 8) & 0xFFU;
    g_frame[13] = data_len & 0xFFU;

    return (data_len + 14);
}


void Ethernet_Receive_Callback(uint32_t event)
{
	uint32_t size;
	uint32_t len;
	uint32_t data_len;
	uint8_t *data;
	uint8_t prueba[400];

	if (event == ARM_ETH_MAC_EVENT_RX_FRAME)
	{

		/* Get the Frame size */
		size = EXAMPLE_ENET.GetRxFrameSize();
		/* Call ENET_ReadFrame when there is a received frame. */
		if (size != 0)
		{
			/* Received valid frame. Deliver the rx buffer with the size equal to length. */
			data = (uint8_t *)malloc(size);
			if (data)
			{
				len = EXAMPLE_ENET.ReadFrame(data, size);
				if (size == len)
				{

					if (data[0] != 0xFF) {
						// Verify the data with CRC32
						if( verifyDataCRC(data, size) == CRC_OK)
						{
							// Subtract the MAC header and the CRC32 size
							data_len = (data[12] << 8 | data[13]) - 4;

							aes128_init(); 									//Restart_Module_To_Encrypt
							memset(prueba, 0, sizeof(prueba));
							memcpy(&prueba[0], &data[14], data_len);
							AES_CBC_decrypt_buffer(&ctx, prueba, data_len); //Decode_Message

							PRINTF("Decrypted: %s\r\n", prueba);
							flagReception = 1;
						}

						else
						{
							PRINTF("ErrorCRC32!\r\n");
						}
					}
				}
				free(data);
			}
		}
	}


}

uint32_t ENET0_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_CoreSysClk);
}

void Ethernet_Configuration_Init(receive_cb_function callback_function)
{
	if(callback_function != NULL)
	{
		User_ENET_Receive_Cb = callback_function;  //Safe_User_Receive_Callback
	}

    ARM_ETH_LINK_INFO linkInfo;
    SYSMPU_Enable(SYSMPU, false);  //Disable_Sysmpu

    mdioHandle.resource.base        = ENET;
    mdioHandle.resource.csrClock_Hz = ENET0_GetFreq();

    PRINTF("\r\nENET example start.\r\n");
    EXAMPLE_ENET.Initialize(Ethernet_Receive_Callback);
    EXAMPLE_ENET.PowerControl(ARM_POWER_FULL);
    EXAMPLE_ENET.SetMacAddress((ARM_ETH_MAC_ADDR *)source_macAddr);

    PRINTF("Wait for PHY_Init...\r\n");
    while (EXAMPLE_ENET_PHY.PowerControl(ARM_POWER_FULL) != ARM_DRIVER_OK)
    {
        PRINTF("PHY Auto-negotiation failed, please check the cable connection and link partner setting.\r\n");
    }

    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_RX, 1);
    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_TX, 1);
    PRINTF("Wait for PHY link up...\r\n");
    do
    {
        if (EXAMPLE_ENET_PHY.GetLinkState() == ARM_ETH_LINK_UP)
        {
            linkInfo = EXAMPLE_ENET_PHY.GetLinkInfo();
            EXAMPLE_ENET.Control(ARM_ETH_MAC_CONFIGURE, 	linkInfo.speed << ARM_ETH_MAC_SPEED_Pos |
                                                            linkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                                                            ARM_ETH_MAC_ADDRESS_BROADCAST);
            break;
        }
    } while (1);

#if defined(PHY_STABILITY_DELAY_US) && PHY_STABILITY_DELAY_US
    SDK_DelayAtLeastUs(PHY_STABILITY_DELAY_US, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); //Wait for_PHY_Status
#endif

    InitCrc32(base, 0xFFFFFFFFU);
    aes128_init();

}


void Ethernet_Data_Transmit(uint8_t *data, uint32_t len)
{
	uint32_t Bytes_BufferBroadcast=0;
	Bytes_BufferBroadcast = Ethernet_BufferBroadcast(data, len); //Output_Frame
	
	SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
	flagReception = 0;

	if (EXAMPLE_ENET.SendFrame(&g_frame[0], Bytes_BufferBroadcast > 60 ? Bytes_BufferBroadcast : 60, ARM_ETH_MAC_TX_FRAME_EVENT) == ARM_DRIVER_OK)
	{
		while(flagReception == 0) {
			SDK_DelayAtLeastUs(500, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);  //Message "PHY_is_link_up" -- To_wait_Frame
		}
	}

	else
	{
		PRINTF(" \r\nFailure_In_tHE_Transmision!\r\n");
	}

}
