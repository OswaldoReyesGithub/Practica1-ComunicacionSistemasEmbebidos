//ArchivoDeConfiguración
#ifndef PRACTICE1_CFG_H_
#define PRACTICE1_CFG_H_

#define EXAMPLE_ENET     Driver_ETH_MAC0
#define EXAMPLE_ENET_PHY Driver_ETH_PHY0
#define ENET_DATA_LENGTH        (999)

//aes.h
#define AES128_KEY	{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06}
#define AES128_IV	{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06}

#ifndef SOURCE_MAC_ADDRESS
#define SOURCE_MAC_ADDRESS {0xd4, 0xbe, 0xd9, 0x45, 0x22, 0x61}
#endif

#ifndef DESTINATION_MAC_ADDRESS
#define DESTINATION_MAC_ADDRESS {0x58, 0x11, 0x22, 0x86, 0x21, 0xe8}
//	#define DESTINATION_MAC_ADDRESS {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
//	#define DESTINATION_MAC_ADDRESS {0xff, 0xff, 0xff, 0xff, 0xff, 0x99}
#endif

#endif /* PRACTICE1_CFG_H_ */
