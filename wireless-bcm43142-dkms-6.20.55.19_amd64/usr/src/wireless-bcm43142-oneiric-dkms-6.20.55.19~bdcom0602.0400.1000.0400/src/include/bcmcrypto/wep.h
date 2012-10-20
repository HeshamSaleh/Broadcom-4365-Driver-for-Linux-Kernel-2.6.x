/*
 * wep.h
 * Prototypes for WEP functions.
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * $Id: wep.h 241182 2011-02-17 21:50:03Z $
 */

#ifndef _WEP_H_
#define _WEP_H_

#include <typedefs.h>

extern void BCMROMFN(wep_encrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data);

extern bool BCMROMFN(wep_decrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data);

#endif 
