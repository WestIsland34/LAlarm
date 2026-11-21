/* LALARM Timer 7min */

#include <xc.h>

// PIC10F200 Configuration Bits
#pragma config WDTE = OFF     // Watchdog Timer Disable
#pragma config MCLRE = OFF    // MCLR Pin Function Select (GP3 as I/O)

#define _XTAL_FREQ 400000   // internal 4MHz OSC

#define _B500MS  1450       // buzzer 500ms
#define _B1SEC   2900       // buzzer 1sec

// delay(255,0); delay(156,0);  // 1sec
// delay(206,0);                // 500ms

void delay(unsigned char t1,unsigned char t2)
{
    while(t1--){ while(t2--) __nop(); }
}

void buzzer(unsigned int t,unsigned char s)
{
    while(t--){
        GP2 = 1;
        delay(1,s);
        GP2 = 0;
        delay(1,s - 1);
    }
}

void main(void)
{
    unsigned char c;
    unsigned int n;
    OPTION = 0b11000000;    // T0CS=0
    TRISGPIO = 0b11111001;  // digital output for GPIO 2

    for(c = 8;c < 17;c++) buzzer(300,c);
    n = 0;
    while(1){
        c = 0;
        if(n ==  60) c = 1;
        if(n == 119) c = 2;
        if(n == 178) c = 3;
//      if(n == 235) c = 4;
//      if(n == 291) c = 5;
//      if(n == 345) c = 6;
//      if(n > 399) break;      // 7min
        if(n > 235) break;      // 4min
        if(c != 0){
            while(c--){ buzzer(_B500MS,15); delay(206,0); }     // 500ms x 2
        }
        delay(255,0); delay(156,0);                             // 1sec
        n++;
    }
    while(1){
        for(c = 0;c < 2;c++){
            buzzer(300,14);
            buzzer(300,15);
            buzzer(300,16);
        }
        delay(255,0); delay(156,0);     // 1sec
        delay(255,0); delay(156,0);     // 1sec
        delay(255,0); delay(156,0);     // 1sec
    }
    return;
}
