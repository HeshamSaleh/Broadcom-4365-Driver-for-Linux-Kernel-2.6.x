/*
 *   wep.c - WEP functions
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * $Id: wep.c 281526 2011-09-02 17:10:12Z $
 */

#include <typedefs.h>

#include <osl.h>

#include <bcmutils.h>
#include <bcmcrypto/rc4.h>
#include <bcmcrypto/wep.h>
#include <proto/802.11.h>

void
BCMROMFN(wep_encrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data)
{
	uint8 key_data[16];
	uint32 ICV;
	rc4_ks_t ks;
	uint8 *body = buf + DOT11_IV_LEN;
	uint body_len = buf_len - (DOT11_IV_LEN + DOT11_ICV_LEN);
	uint8 *picv = body + body_len;

	memcpy(key_data, buf, 3);
	memcpy(&key_data[3], sec_data, sec_len);

	prepare_key(key_data, sec_len + 3, &ks);

	ICV = ~hndcrc32(body, body_len, CRC32_INIT_VALUE);
	picv[0] = ICV & 0xff;
	picv[1] = (ICV >> 8) & 0xff;
	picv[2] = (ICV >> 16) & 0xff;
	picv[3] = (ICV >> 24) & 0xff;

	rc4(body, body_len + DOT11_ICV_LEN, &ks);
}

bool
BCMROMFN(wep_decrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data)
{
	uint8 key_data[16];
	rc4_ks_t ks;

	memcpy(key_data, buf, 3);
	memcpy(&key_data[3], sec_data, sec_len);

	prepare_key(key_data, sec_len + 3, &ks);

	rc4(buf + DOT11_IV_LEN, buf_len - DOT11_IV_LEN, &ks);

	return (hndcrc32(buf + DOT11_IV_LEN, buf_len - DOT11_IV_LEN, CRC32_INIT_VALUE) ==
		CRC32_GOOD_VALUE);
}
