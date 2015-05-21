/**
 * @file main.c
 * @author Alexis Marquet
 * @date 29 Apr 2015
 * @brief contains the main application
 **/


/**
 * @mainpage
 * 08_test_CXX: in this one, I tried to get cxx linkage to work. proof with vector, string, and ostream.
 * first you should see the cout << output, then the led_class ctor, and the value "seconds" from the RTC should print.
 * and after 16 seconds, the dtor, and ctor again.
 * the executable size of this example is huge, i dont know why it is THAT huge.
 **/

extern "C" {
#include <stdio.h>
#include "../core/llma.h"
#include "../proc/clock_module.h"
#include "../proc/interrupt.h"
#include "../board/LED.h"
}
#include <vector>
#include <string>
#include <iostream>

using namespace std;
extern "C"
void RTCINT_IRQHandler()
{
   NVIC_ClearPending(RTCINT_IRQn);  // Clear RTC int
   int s = GET32(0x44E3E000+0x00);  // get seconds from RTC
   cout << (s>>4) << (s&0xf) << endl;  // print seconds
}

class test_class
{
public:
   test_class()
   {
      printf("test_class: ctor\n");
   }
   void test()
   {
      printf("test_class: test\n");
   }
   ~test_class()
   {
      printf("test_class: dtor\n");
   }
};

vector <int> *l;

int main ()
{
   string stringtest = "blablabla";
   cout << "test cout: " << stringtest<< endl;
   l = new vector <int>;
   
   l->push_back(0b0000);
   l->push_back(0b0001);
   l->push_back(0b0011);
   l->push_back(0b0010);
   l->push_back(0b0110);
   l->push_back(0b0111);
   l->push_back(0b0101);
   l->push_back(0b0100);
   l->push_back(0b1100);
   l->push_back(0b1101);
   l->push_back(0b1111);
   l->push_back(0b1110);
   l->push_back(0b1010);
   l->push_back(0b1011);
   l->push_back(0b1001);
   l->push_back(0b1000);
   
   CKM_setCLKModuleRegister(CKM_RTC,CKM_RTC_CLKSTCTRL,0x2);   // software wakeup on RTC power domain
   CKM_setCLKModuleRegister(CKM_RTC,CKM_RTC_RTC_CLKCTRL,0x2);   // enable RTC clock power domain
   
   PUT32(0x44E3E000+0x6C,0x83E70B13);     // disable protection on register
   PUT32(0x44E3E000+0x70,0x95A4F1E0);     // disable protection on register
   
   PUT32(0x44E3E000+0x40,0x1);      // run RTC
   
   PUT32(0x44E3E000+0x54,1<<3 | 1<<6); // enable 32khz (bit 6) & select 32 khz osc
   
   while(GET32(0x44E3E000+0x44)&0x1);  // wait until RTC is done updating
   
   PUT32(0x44E3E000+0x48,0x4);   // enable interrupt, every second
   
   NVIC_Enable(RTCINT_IRQn);

   
   printf("l = 0x%x\n",l->size());
   
   // small float test
   volatile float a = 0.707;
   volatile float b = 1.414;
   volatile float c;
   c = b*a;
   cout <<"a*b = "<< a << "*" << b << " = " << c << endl;

   while(true)
   {
      test_class t;
      t.test();
      for(uint32_t i = 0; i < l->size(); i++)
      {
         asm volatile ("wfi");
         LED_setValue(l->at(i));
      }
   }
   for(;;){}
   return 0;
}
