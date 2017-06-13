#ifndef	KTYPES_H
#define	KTYPES_H

#define	ut8	unsigned char
#define	ut16	unsigned short
#define	ut32	unsigned int
#define	ut64	unsigned long long

#define	st8	char
#define	st16	short
#define	st32	int
#define	st64	long long

typedef	enum {
	false = (0==1),
	true = (1==1)
} bool;

#endif
