#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 48
unsigned int MailboxWrite ( unsigned int fbinfo_addr, unsigned int channel );
unsigned int MailboxRead ( unsigned int channel );
int video_init();
