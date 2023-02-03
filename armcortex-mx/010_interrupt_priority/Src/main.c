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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define IRQNO_TIMER2  28
#define IRQNO_I2C1    31

#include<stdio.h>

/* NVIC register addresses. Refer to the processor generic guide */
uint32_t *pNVIC_IPRBase =  (uint32_t*)0xE000E400;
uint32_t *pNVIC_ISERBase = (uint32_t*)0xE000E100;
uint32_t *pNVIC_ISPRBase = (uint32_t*)0XE000E200;


void configure_priority_for_irqs(uint8_t irq_no, uint8_t priority_value)
{
	//1. find out iprx
	uint8_t iprx = irq_no / 4;
	uint32_t *ipr =  pNVIC_IPRBase+iprx;

	//2. position in iprx
	uint8_t pos = (irq_no % 4) * 8;

	//3. configure the priority
	*ipr &= ~(0xFF << pos);//clear
	*ipr |=  (priority_value << pos);

}

int main(void)
{
	//1. Lets configure the priority for the peripherals
	 configure_priority_for_irqs(IRQNO_TIMER2,0x80);
	 configure_priority_for_irqs(IRQNO_I2C1,0x70);

	//2. Set the interrupt pending bit in the NVIC PR
	 *pNVIC_ISPRBase |= ( 1 << IRQNO_TIMER2);

	//3. Enable the IRQs in NVIC ISER
	 *pNVIC_ISERBase |= ( 1 << IRQNO_I2C1);
	 *pNVIC_ISERBase |= ( 1 << IRQNO_TIMER2);


}

//isrs

void TIM2_IRQHandler(void)
{
  printf("[TIM2_IRQHandler]\n");
  /*Here, we are pending I2C interrupt request manually */
  *pNVIC_ISPRBase |= ( 1 << IRQNO_I2C1);
  while(1);

}


void I2C1_EV_IRQHandler(void)
{
  printf("[I2C1_EV_IRQHandler]\n");
}
