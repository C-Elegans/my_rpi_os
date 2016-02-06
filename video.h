#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
unsigned int MailboxWrite(unsigned int fbinfo_addr, unsigned int channel);
unsigned int MailboxRead(unsigned int channel);
short* video_init();
