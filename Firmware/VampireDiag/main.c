#include "amiga_hardware.h"

#include "minisoc_hardware.h"

void Putint(unsigned int val)
{
	int c;
	int i;
	for(i=0;i<8;++i)
	{
		c=(val>>28)&0xf;
		val<<=4;
		if(c>9)
			c+='A'-10;
		else
			c+='0';
		putchar(c);
	}
}

#if 0
void CheckAlias()
{
	int i1,i2,i3,i4;
	i2=*(volatile int *)0xfc0000;
	i1=*(volatile int *)0xf00000;
	Putint(i1);
	Putint(i2);
	i4=*(volatile int *)0xfc0004;
	i3=*(volatile int *)0xf00004;
	Putint(i3);
	Putint(i4);
	putchar('\n');

	i2=*(volatile int *)0xfc0008;
	i1=*(volatile int *)0xf00008;
	Putint(i1);
	Putint(i2);
	i4=*(volatile int *)0xfc000c;
	i3=*(volatile int *)0xf0000c;
	Putint(i3);
	Putint(i4);
	putchar('\n');
}
#endif

// Check for aliasing of Kickstart
#if 0
int main()
{
	int a,b,c,d,i;

	HW_CIAA(CIAA_DDRA)=0x03;
	HW_CIAA(CIAA_PRA)=0xfc;

//	while(1)
//		HW_AMIGA(COLOR0)=c++;
	Amiga_SetupScreen();
//	Amiga_TestPattern2();

//	putchar('H');
//	putchar('e');
//	putchar('l');
//	putchar('l');
//	putchar('o');
//	putchar('\n');
//	puts("Hello, world!\n");

	a=*(volatile short*)0xfc0000;
	a=*(volatile short*)0xfc0000;
	b=*(volatile short*)0x000004; // Change the data on the bus.
	i=0;
	c=*(volatile short*)0xf00000;
	while(a==c)
	{
		++i;
		b=*(volatile short*)0x000004; // Change the data on the bus.
		c=*(volatile short*)0xf00000;
	}
	d=*(volatile short*)0xfc0004; // Something we can pick up in SignalTap

	puts("Shadow of ");
	Putint(a);
	puts(" persisted for ");
	Putint(i);
	puts(" consecutive reads\n");
	puts("Ending with a read of ");
	Putint(c);

//	CheckAlias();

//	while(1)
//		c=*(volatile int *)0xf00000;

	while(1)
		;
    return 0;
}
#endif

// Display text received from a second CPU, masquerading as a UART.
int main()
{
	HW_CIAA(CIAA_DDRA)=0x03;
	HW_CIAA(CIAA_PRA)=0xfc;
	Amiga_SetupScreen();

	puts("Ready to receive\n");

	while(1)
	{
		int in=HW_PER(PER_UART);
		if(in & (1<<PER_UART_RXINT))
		{
			putchar(in&0xff);
		}
	}

	while(1)
		;
    return 0;
}

