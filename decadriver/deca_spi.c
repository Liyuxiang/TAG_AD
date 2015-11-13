/*
 * deca_spi.c
 *
 *  Created on: 2014-6-5
 *      Author: lanmao2014
 */

#include <msp430.h>
#include "deca_device_api.h"

int writetospi
(
		uint16 		headerLength,
		const uint8  *headerBuffer,
		uint32		bodylength,
		const uint8  *bodyBuffer
)
{
	uint8	i = 0;

	decaIrqStatus_t	stat;
	uint8 temp;
	stat = decamutexon();

	P2OUT &= ~0x10;
	for(i = 0; i < headerLength; i++)
	{
		UCA0TXBUF = headerBuffer[i];
		//while (!(DWT_SPIIFG & UCTXIFG));
		while (!(IFG2 & UCA0RXIFG));
		temp = UCA0RXBUF;
	}
	//temp = UCA0RXBUF;
	for(i = 0; i < bodylength; i++)
	{
		UCA0TXBUF = bodyBuffer[i];
		//while (!(DWT_SPIIFG & UCTXIFG));
		while (!(IFG2 & UCA0RXIFG));
		temp = UCA0RXBUF;
	}

	P2OUT |= 0x10;

	decamutexoff(stat);
	return 0;
}


int readfromspi
(
		uint16		headerLength,
		const uint8  *headerBuffer,
		uint32		readlength,
		uint8		   *readBuffer
)
{
	uint8 i = 0;
	uint8 temp;

	decaIrqStatus_t stat;

	stat = decamutexon();

	P2OUT &= ~0x10;
	//temp = UCA0RXBUF;
	for(i = 0; i < headerLength; i++)
	{
		UCA0TXBUF = headerBuffer[i];
		//while (!(IFG2 & UCA0TXIFG));
		while (!(IFG2 & UCA0RXIFG));
		temp = UCA0RXBUF;
	}

	if(IFG2 & UCA0RXIFG)
		temp = UCA0RXBUF;

	for(i = 0; i < readlength; i++)
	{
		UCA0TXBUF = 0;
		while (!(IFG2 & UCA0RXIFG));
		readBuffer[i] = UCA0RXBUF;
	}

	P2OUT |= 0x10;

	decamutexoff(stat);

	return 0;
}

void decamutexoff(decaIrqStatus_t s)
{
}

decaIrqStatus_t decamutexon(void)
{
	return 0;
}
