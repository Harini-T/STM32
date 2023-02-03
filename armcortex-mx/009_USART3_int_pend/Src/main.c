/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define USART3_IRQNO	39

int main(void)
{
	//Manually pend the pending bit for USART3 IRQ number in NVIC
	uint32_t *pISPR1 = (uint32_t*)0xE000E204;
	*pISPR1 |= (1<<(USART3_IRQNO % 32));

	//Enable the USART3 IRQ number in NVIC
	uint32_t *pISER1 = (uint32_t*)0xE000E104;
	*pISER1 |= (1<<(USART3_IRQNO % 32));

    /* Loop forever */
	for(;;);
}

void USART3_IRQHandler(void){
	printf("in USART3 isr\n");
}
