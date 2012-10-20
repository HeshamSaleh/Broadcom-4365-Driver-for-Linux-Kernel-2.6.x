/*
 * tkmic.h
 * Prototypes for TKIP Message Integrity Check (MIC) functions.
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * $Id: tkmic.h 241182 2011-02-17 21:50:03Z $
 */

#ifndef _TKMIC_H_
#define _TKMIC_H_

#include <typedefs.h>

#define ROTR32(x, n)	(((x)<<(32-(n))) | ((uint32)(x)>>(n)))

#define ROTL32(x, n)	ROTR32(x, 32-n)
#define XSWAP32(x)	((((x)>> 8) & 0x00ff00ff) | (((x)<< 8) & 0xff00ff00))

extern void BCMROMFN(tkip_mic)(uint32 k0, uint32 k1, int n, uint8 *m, uint32 *left, uint32 *right);

extern int BCMROMFN(tkip_mic_eom)(uint8 *m, uint n, uint o);

#endif 
