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

#include <cdn_dp.h>
#include <smcc.h>
#include <stdlib.h>
#include <string.h>

__asm__(
	".pushsection .text.hdcp_handler, \"ax\", %progbits\n"
	".global hdcp_handler\n"
	".balign 4\n"
	"hdcp_handler:\n"
	".incbin \"" __XSTRING(HDCPFW) "\"\n"
	".type hdcp_handler, %function\n"
	".size hdcp_handler, .- hdcp_handler\n"
	".popsection\n"
);

static uint64_t *hdcp_key_pdata;
static struct cdn_dp_hdcp_key_1x key;

int hdcp_handler(struct cdn_dp_hdcp_key_1x *key);

uint64_t dp_hdcp_ctrl(uint64_t type)
{
	switch (type) {
	case HDCP_KEY_DATA_START_TRANSFER:
		memset(&key, 0x00, sizeof(key));
		hdcp_key_pdata = (uint64_t *)&key;
		return 0;
	case HDCP_KEY_DATA_START_DECRYPT:
		if (hdcp_key_pdata == (uint64_t *)(&key + 1))
			return hdcp_handler(&key);
		else
			return PSCI_E_INVALID_PARAMS;
	default:
		return SMC_UNK;
	}
}

uint64_t dp_hdcp_store_key(uint64_t x1,
			   uint64_t x2,
			   uint64_t x3,
			   uint64_t x4,
			   uint64_t x5,
			   uint64_t x6)
{
	if (hdcp_key_pdata < (uint64_t *)&key ||
		hdcp_key_pdata + 6 > (uint64_t *)(&key + 1))
		return PSCI_E_INVALID_PARAMS;

	hdcp_key_pdata[0] = x1;
	hdcp_key_pdata[1] = x2;
	hdcp_key_pdata[2] = x3;
	hdcp_key_pdata[3] = x4;
	hdcp_key_pdata[4] = x5;
	hdcp_key_pdata[5] = x6;
	hdcp_key_pdata += 6;

	return 0;
}
