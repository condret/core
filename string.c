#include <ktypes.h>
#include <string.h>

ut32 strlen (const char *s)
{
	ut32 ret;
	if (!s)
		return 0;
	for (ret = 0; (s[ret] && (ret != 0xffffffff)); ret++) {}
	return ret;
}
