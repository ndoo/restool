/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 * Author: German Rivera <German.Rivera@freescale.com>
 * 	   Lijun Pan <Lijun.Pan@freescale.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation  and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of any
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
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

#ifndef _RESMAN_H_
#define _RESMAN_H_

#include <stdint.h>
#include "fsl_mc_sys.h"
#include "fsl_dpmng.h"
#include "fsl_mc_ioctl.h"

/**
 * MC object type string max length (without including the null terminator)
 */
#define OBJ_TYPE_MAX_LENGTH	4

/**
 * MC resource type string max length (without including the null terminator)
 */
#define RES_TYPE_MAX_LENGTH	15

/**
 * Maximum number of command line options
 */
#define MAX_NUM_CMD_LINE_OPTIONS    (sizeof(uint32_t) * 8)

struct resman;

typedef int resman_cmd_func_t(void);

struct object_command {
	/**
	 * object-specific command found in the command line
	 */
	const char *cmd_name;

	/**
	 * Pointer to array of getopt_long options
	 */
	const struct option *options;

	/**
	 * Pointer to command function
	 */
	resman_cmd_func_t *cmd_func;
};

/**
 * Object command parser structure
 */
struct object_cmd_parser {
	/**
	 * object-type found in the command line
	 */
	const char *obj_type;

	/**
	 * Pointer to array of commands for the object type
	 */
	struct object_command *obj_commands;
};

/**
 * Global state of the resman tool
 */
struct resman {
	/**
	 * Bit mask of command-line options not consumed yet
	 */
	uint32_t global_option_mask;

	/**
	 * Array of option arguments for global options found in the command line,
	 * that have arguments. One entry per option.
	 */
	const char *global_option_args[MAX_NUM_CMD_LINE_OPTIONS];

	/**
	 * Pointer to the command being processed
	 */
	struct object_command *obj_cmd;

	/**
	 * object name found in the command line
	 */
	const char *obj_name;

	/**
	 * Bit mask of command-line options not consumed yet
	 */
	uint32_t cmd_option_mask;

	/**
	 * Array of option arguments for options found in the command line,
	 * that have arguments. One entry per option.
	 */
	const char *cmd_option_args[MAX_NUM_CMD_LINE_OPTIONS];

	/**
	 * MC I/O portal
	 */
	struct fsl_mc_io mc_io;

	/**
	 * MC firmware version
	 */
	struct mc_version mc_fw_version;

	/**
	 * Id for the root DPRC in the system
	 */
	uint16_t root_dprc_id;

	/**
	 * Handle for the root DPRC in the system
	 */
	uint16_t root_dprc_handle;
};

/**
 * Command-line option indices form global resman options
 */
enum global_options {
	GLOBAL_OPT_HELP = 0,
	GLOBAL_OPT_VERSION,
};

int parse_object_name(const char *obj_name, char *expected_obj_type,
		      uint32_t *obj_id);

int open_dprc(uint32_t dprc_id, uint16_t *dprc_handle);

void print_unexpected_options_error(uint32_t option_mask,
				    const struct option *options);

extern struct resman resman;
extern struct object_command dprc_commands[];
extern struct object_command dpni_commands[];
extern struct object_command dpio_commands[];
extern struct object_command dpbp_commands[];

#endif /* _RESMAN_H_ */