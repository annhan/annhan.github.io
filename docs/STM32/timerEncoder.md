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
  
  
  
```
# cấu hình timer_2 chế độ đọc 4X
void TIM2_EXTI(void)// ham khoi tao doc encoder
{
TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
TIM2->CCER = TIM_CCER_CC1P|TIM_CCER_CC2P;
TIM2->SMCR = TIM_SMCR_SMS_0|TIM_SMCR_SMS_1;
TIM2->ARR = 65535;
TIM2->CNT = 32000;
TIM2->CR1 = TIM_CR1_CEN;
}
# khi xảy ra ngắt timer_3 thì thực hiện đọc encoder
void TIM3_IRQHandler(void)// ham doc xung encoder trong 10ms
{
 
if (TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)
{
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
b=TIM_GetCounter(TIM2)-32000;// doc xung encoder sau thoi gian lay mau
 
c=b+c;// cong don xung encoder sau thoi gian lay mâu= tông xung encoder dem duoc
TIM2->CNT=32000;// het thoi gian lay mau reset lai thanh ghi TIM2=32000, doc encoder lai tu dau
}
}
```
