#include "video.h"
#include "mem.h"
unsigned int MailboxWrite(unsigned int fbinfo_addr, unsigned int channel){
	unsigned int mailbox;

	mailbox = 0x2000B880;
	while (1)
		if ((GET32(mailbox + 0x18) & 0x80000000) == 0) break;
	PUT32(mailbox + 0x20, fbinfo_addr + channel);
	return 0;
}

unsigned int MailboxRead(unsigned int channel){
	unsigned int ra;
	unsigned int mailbox;

	mailbox = 0x2000B880;
	while (1) {
		while (1) {
			ra = GET32(mailbox + 0x18);
			if ((ra & 0x40000000) == 0) break;
		}
		//hexstrings(ra);
		ra = GET32(mailbox + 0x00);
		//hexstring(ra);
		if ((ra & 0xF) == channel) break;
	}
	return ra;
}
int video_init(){
	unsigned int rb;



	//timer_init();

	PUT32(0x40040000, SCREEN_WIDTH);        /* #0 Physical Width */
	PUT32(0x40040004, SCREEN_HEIGHT);       /* #4 Physical Height */
	PUT32(0x40040008, SCREEN_WIDTH);        /* #8 Virtual Width */
	PUT32(0x4004000C, SCREEN_HEIGHT);       /* #12 Virtual Height */
	PUT32(0x40040010, 0);                   /* #16 GPU - Pitch */
	PUT32(0x40040014, 16);                  /* #20 Bit Depth */
	PUT32(0x40040018, 0);                   /* #24 X */
	PUT32(0x4004001C, 0);                   /* #28 Y */
	PUT32(0x40040020, 0);                   /* #32 GPU - Pointer */
	PUT32(0x40040024, 0);                   /* #36 GPU - Size */


	MailboxWrite(0x40040000, 1);
	MailboxRead(1);


	rb = GET32(0x40040020);
	return rb;
}
