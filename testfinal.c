#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define PF4                     (*((volatile unsigned long *)0x40025040))
#define PF3                     (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))
#define PF1                     (*((volatile unsigned long *)0x40025008))
#define PF0                     (*((volatile unsigned long *)0x40025004))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
#define PF123_mask             0x0E
#define PF04_mask               0x11
#define PF_mask                0x20
void GPIO_Init(void){
SYSCTL_RCGCGPIO_R |= PF_mask; // Clock init for port F
while((SYSCTL_PRGPIO_R & PF_mask) == 0); // delay
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // Lock disable
GPIO_PORTF_CR_R |= 0X18;
GPIO_PORTF_AFSEL_R &= ~0X18;
GPIO_PORTF_AMSEL_R &= ~0X18;
GPIO_PORTF_DEN_R |= 0X18;
GPIO_PORTF_PCTL_R &= ~0x0000FF000;
GPIO_PORTF_DIR_R |= 0X18;
GPIO_PORTF_DATA_R &= ~0X18;
}
void SW_Init(){

GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |= 0X10;
GPIO_PORTF_AFSEL_R &= ~0X10;
GPIO_PORTF_AMSEL_R &= ~0X10;
GPIO_PORTF_DEN_R |= 0X10;
GPIO_PORTF_PCTL_R &= ~0x000F0000;
GPIO_PORTF_DIR_R &= ~0X10;
GPIO_PORTF_PUR_R |= 0X10;
}
void RGB_Output(unsigned char data) {
 GPIO_PORTF_DATA_R &= ~PF123_mask;
 GPIO_PORTF_DATA_R |= data;
}
unsigned char SW1_read(){
return GPIO_PORTF_DATA_R & 0X10;
}

int main(void){
 GPIO_Init();
 SW_Init();

 while (1)
 {
unsigned char SW1;
 SW1 = SW1_read();
if(SW1 != 0x10 ){

 RGB_Output(GREEN);
}
}
}