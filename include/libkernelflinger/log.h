/*
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 *
 * Author: Jeremy Compostella <jeremy.compostella@intel.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <efi.h>
#include <ui.h>
#include <vars.h>

EFI_STATUS log_flush_to_var(BOOLEAN nonvol);

void log(const CHAR16 *fmt, ...);

#ifdef USER
#define DEBUG_MESSAGES 0
#else
#define DEBUG_MESSAGES 1
#endif

#if DEBUG_MESSAGES
#define debug(fmt, ...) do { \
    log(fmt "\n", ##__VA_ARGS__); \
} while(0)

#define debug_pause(x) pause(x)
#else
#define debug(fmt, ...) (void)0
#define debug_pause(x) (void)(x)
#endif

#define error(x, ...) do { \
  log(x "\n", ##__VA_ARGS__); \
  if (ui_is_ready()) { \
    ui_error(x, ##__VA_ARGS__); \
  } else \
    Print(x "\n", ##__VA_ARGS__); \
  log_flush_to_var(TRUE); \
} while(0)

#define efi_perror(ret, x, ...) do { \
  error(x ": %r", ##__VA_ARGS__, ret); \
} while (0)

#endif	/* _LOG_H_ */
