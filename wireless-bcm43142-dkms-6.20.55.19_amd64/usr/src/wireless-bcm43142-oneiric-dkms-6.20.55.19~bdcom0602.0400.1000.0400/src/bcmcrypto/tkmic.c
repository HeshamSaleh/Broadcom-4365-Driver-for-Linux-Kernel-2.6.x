/*
 *   tkmic.c - TKIP Message Integrity Check (MIC) functions
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * $Id: tkmic.c 241182 2011-02-17 21:50:03Z $
 */

#include <typedefs.h>
#include <bcmendian.h>
#include <bcmcrypto/tkmic.h>

static INLINE void
tkip_micblock(uint32 *left, uint32 *right)
{
	uint32 l = *left;
	uint32 r = *right;

	r ^= ROTR32(l, 15);
	l += r; 
	r ^= XSWAP32(l);
	l += r; 
	r ^= ROTR32(l, 29);
	l += r; 
	r ^= ROTR32(l, 2);
	l += r; 

	*left = l;
	*right = r;
}

void
BCMROMFN(tkip_mic)(uint32 k0, uint32 k1, int n, uint8 *m, uint32 *left, uint32 *right)
{
	uint32 l = k0;
	uint32 r = k1;

	if (((uintptr)m & 3) == 0) {
		for (; n > 0; n -= 4) {
			l ^= ltoh32(*(uint *)m);
			m += 4;
			tkip_micblock(&l, &r);
		}
	} else {
		for (; n > 0; n -= 4) {
			l ^= ltoh32_ua(m);
			m += 4;
			tkip_micblock(&l, &r);
		}
	}
	*left = l;
	*right = r;
}

int
BCMROMFN(tkip_mic_eom)(uint8 *m, uint n, uint o)
{
	uint8 *mend = m + n;
	uint t = n + o;
	mend[0] = 0x5a;
	mend[1] = 0;
	mend[2] = 0;
	mend[3] = 0;
	mend[4] = 0;
	mend += 5;
	o += n + 5;
	while (o++%4) {
		*mend++ = 0;
	}
	return (n+o-1-t);
}
