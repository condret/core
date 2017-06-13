#include <ktypes.h>
//#include <string.h>
#include <console.h>

#define	VIDEO_MEM	(ut16 *)0xb8000

static ut32 line;
static ut32 col;

void kputc (char c)
{
	ut16 *video = VIDEO_MEM;
	video += line * 80 + col;
	if (c == '\n')
		goto newline;
	*video = 0x0700 | c;
	col++;
	if (col > 79) {
newline:
		col = 0;
		line = (line + 1) % 25;
	}
}

void kputs (char *s) {
	ut32 i;
	if (!s)
		return;
	for (i = 0 ; (!!s[i]) && (i < 0xffffffff); i++) {
		kputc (s[i]);
	}
	col = 0;
	line = (line + 1) % 25;
}
