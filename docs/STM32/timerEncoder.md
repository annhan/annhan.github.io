---
layout: default
title: 
---
```
void EXTI1_IRQHandler(void)
{
 EXTI->PR |= 1<<1; //clear pending request interrupt flag
 if(GPIOB->IDR & 0x01) //high  on PB 0
 {
  val++;
 }
 else
 {
  val--;
 }
}
void EXTI0_IRQHandler(void)
{
 EXTI->PR |= 1<<1; //clear pending request interrupt flag
 if(GPIOB->IDR & 0x02) //if high  on PB 1
 {
  val++;
 }
 else
 {
  val--;
 }
}

NVIC_EnableIRQ(EXTI1_IRQn); //enable the IRQ line that corresponds to EXT-1
NVIC_EnableIRQ(EXTI0_IRQn); //enable the IRQ line that corresponds to EXT-1
```
