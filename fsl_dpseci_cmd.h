/* Copyright 2013-2014 Freescale Semiconductor Inc.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of the above-listed copyright holders nor the
* names of any contributors may be used to endorse or promote products
* derived from this software without specific prior written permission.
*
*
* ALTERNATIVELY, this software may be distributed under the terms of the
* GNU General Public License ("GPL") as published by the Free Software
* Foundation, either version 2 of that License or (at your option) any
* later version.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef _FSL_DPSECI_CMD_H
#define _FSL_DPSECI_CMD_H

/* DPSECI Version */
#define DPSECI_VER_MAJOR				2
#define DPSECI_VER_MINOR				0

/* Command IDs */
#define DPSECI_CMDID_CLOSE				0x800
#define DPSECI_CMDID_OPEN				0x809
#define DPSECI_CMDID_CREATE				0x909
#define DPSECI_CMDID_DESTROY				0x900

#define DPSECI_CMDID_ENABLE				0x002
#define DPSECI_CMDID_DISABLE				0x003
#define DPSECI_CMDID_GET_ATTR				0x004
#define DPSECI_CMDID_RESET				0x005
#define DPSECI_CMDID_IS_ENABLED				0x006

#define DPSECI_CMDID_SET_IRQ				0x010
#define DPSECI_CMDID_GET_IRQ				0x011
#define DPSECI_CMDID_SET_IRQ_ENABLE			0x012
#define DPSECI_CMDID_GET_IRQ_ENABLE			0x013
#define DPSECI_CMDID_SET_IRQ_MASK			0x014
#define DPSECI_CMDID_GET_IRQ_MASK			0x015
#define DPSECI_CMDID_GET_IRQ_STATUS			0x016
#define DPSECI_CMDID_CLEAR_IRQ_STATUS			0x017

#define DPSECI_CMDID_SET_RX_QUEUE			0x194
#define DPSECI_CMDID_GET_RX_QUEUE			0x196
#define DPSECI_CMDID_GET_TX_QUEUE			0x197

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_OPEN(cmd, dpseci_id) \
	MC_CMD_OP(cmd, 0, 0,  32, int,      dpseci_id)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_CREATE(cmd, cfg) \
do { \
	MC_CMD_OP(cmd, 0, 8,  8,  uint8_t,  cfg->priorities[0]);\
	MC_CMD_OP(cmd, 0, 16, 8,  uint8_t,  cfg->priorities[1]);\
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_IS_ENABLED(cmd, en) \
	MC_RSP_OP(cmd, 0, 0,  1,  int,	    en)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_SET_IRQ(cmd, irq_index, irq_paddr, irq_val, user_irq_id) \
do { \
	MC_CMD_OP(cmd, 0, 0,  8,  uint8_t,  irq_index);\
	MC_CMD_OP(cmd, 0, 32, 32, uint32_t, irq_val);\
	MC_CMD_OP(cmd, 1, 0,  64, uint64_t, irq_paddr);\
	MC_CMD_OP(cmd, 2, 0,  32, int,	    user_irq_id); \
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_IRQ(cmd, irq_index) \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_IRQ(cmd, type, irq_paddr, irq_val, user_irq_id) \
do { \
	MC_RSP_OP(cmd, 0, 0,  32, uint32_t, irq_val); \
	MC_RSP_OP(cmd, 1, 0,  64, uint64_t, irq_paddr);\
	MC_RSP_OP(cmd, 2, 0,  32, int,	    user_irq_id); \
	MC_RSP_OP(cmd, 2, 32, 32, int,	    type); \
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_SET_IRQ_ENABLE(cmd, irq_index, enable_state) \
do { \
	MC_CMD_OP(cmd, 0, 0,  8,  uint8_t,  enable_state); \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index); \
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_IRQ_ENABLE(cmd, irq_index) \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_IRQ_ENABLE(cmd, enable_state) \
	MC_RSP_OP(cmd, 0, 0,  8,  uint8_t,  enable_state)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_SET_IRQ_MASK(cmd, irq_index, mask) \
do { \
	MC_CMD_OP(cmd, 0, 0,  32, uint32_t, mask); \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index); \
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_IRQ_MASK(cmd, irq_index) \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_IRQ_MASK(cmd, mask) \
	MC_RSP_OP(cmd, 0, 0,  32, uint32_t, mask)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_IRQ_STATUS(cmd, irq_index) \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_IRQ_STATUS(cmd, status) \
	MC_RSP_OP(cmd, 0, 0,  32, uint32_t,  status)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_CLEAR_IRQ_STATUS(cmd, irq_index, status) \
do { \
	MC_CMD_OP(cmd, 0, 0,  32, uint32_t, status); \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  irq_index); \
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_ATTR(cmd, attr) \
do { \
	MC_RSP_OP(cmd, 0, 0,  32, int,	    attr->id); \
	MC_RSP_OP(cmd, 1, 0,  8,  uint8_t,  attr->num_of_priorities); \
	MC_RSP_OP(cmd, 5, 0,  16, uint16_t, attr->version.major);\
	MC_RSP_OP(cmd, 5, 16, 16, uint16_t, attr->version.minor);\
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_SET_RX_QUEUE(cmd, priority, cfg) \
do { \
	MC_CMD_OP(cmd, 0, 0,  32, int,      cfg->dest_cfg.dest_id); \
	MC_CMD_OP(cmd, 0, 32, 8,  uint8_t,  cfg->dest_cfg.priority); \
	MC_CMD_OP(cmd, 0, 40, 8,  uint8_t,  priority); \
	MC_CMD_OP(cmd, 0, 48, 4,  enum dpseci_dest, cfg->dest_cfg.dest_type); \
	MC_CMD_OP(cmd, 1, 0,  64, uint64_t, cfg->user_ctx); \
	MC_CMD_OP(cmd, 2, 0,  32, uint32_t, cfg->options);\
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_RX_QUEUE(cmd, priority) \
	MC_CMD_OP(cmd, 0, 40, 8,  uint8_t,  priority)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_RX_QUEUE(cmd, attr) \
do { \
	MC_RSP_OP(cmd, 0, 0,  32, int,      attr->dest_cfg.dest_id);\
	MC_RSP_OP(cmd, 0, 32, 8,  uint8_t,  attr->dest_cfg.priority);\
	MC_RSP_OP(cmd, 0, 48, 4,  enum dpseci_dest, attr->dest_cfg.dest_type);\
	MC_RSP_OP(cmd, 1, 0,  8,  uint64_t,  attr->user_ctx);\
	MC_RSP_OP(cmd, 2, 0,  32, uint32_t,  attr->fqid);\
} while (0)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_CMD_GET_TX_QUEUE(cmd, priority) \
	MC_CMD_OP(cmd, 0, 40, 8,  uint8_t,  priority)

/*                cmd, param, offset, width, type, arg_name */
#define DPSECI_RSP_GET_TX_QUEUE(cmd, attr) \
	MC_RSP_OP(cmd, 0, 32, 32, uint32_t,  attr->fqid)

#endif /* _FSL_DPSECI_CMD_H */