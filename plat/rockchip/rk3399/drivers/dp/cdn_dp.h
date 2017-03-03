/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SOC_ROCKCHIP_RK3399_DP_H__
#define __SOC_ROCKCHIP_RK3399_DP_H__
#include <plat_private.h>

enum {
	CDN_DP_HDCP_1X_KSV_LEN = 5,
	CDN_DP_HDCP_KSV_LEN = 8,
	CDN_DP_HDCP_UID_LEN = 16,
	CDN_DP_HDCP_SHA_LEN = 20,
	CDN_DP_HDCP_DPK_LEN = 280,
	CDN_DP_HDCP_1X_KEYS_LEN	= 285,
	CDN_DP_HDCP_KEY_LEN = 326,
};

struct cdn_dp_hdcp_key_1x {
	uint8_t ksv[CDN_DP_HDCP_KSV_LEN];
	uint8_t device_key[CDN_DP_HDCP_DPK_LEN];
	uint8_t sha1[CDN_DP_HDCP_SHA_LEN];
	uint8_t uid[CDN_DP_HDCP_UID_LEN];
	uint16_t seed;
	uint8_t reserved[10];
};

#define HDCP_KEY_DATA_START_TRANSFER	0
#define HDCP_KEY_DATA_START_DECRYPT	1

uint64_t dp_hdcp_ctrl(uint64_t type);

uint64_t dp_hdcp_store_key(uint64_t x1,
			   uint64_t x2,
			   uint64_t x3,
			   uint64_t x4,
			   uint64_t x5,
			   uint64_t x6);
#endif
