/*
 * Copyright (C) 2017 BlueKitchen GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MATTHIAS RINGWALD AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/*
 *  hal_flash_sector.h
 * 
 *  HAL abstraction for Flash memory that can be written anywhere
 *  after being erased
 */

#ifndef __HAL_FLASH_SECTOR_H
#define __HAL_FLASH_SECTOR_H

#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif

// Number of flash banks
#define HAL_FLASH_SECTOR_NUM 2

/**
 * Initialize flash sector implementation. 
 */

void hal_flash_sector_init(void);

/**
 * Get size of flash banks
 */
uint32_t hal_flash_sector_get_size(void);

/**
 * Erase a bank
 * @param bank
 */
void hal_flash_sector_erase(int bank);

/**
 * Read from flash into provided buffer
 * @param bank
 * @param offset into flash bank
 * @param buffer to read data
 * @param size of data to read
 */
void hal_flash_sector_read(int bank, uint32_t offset, uint8_t * buffer, uint32_t size);

/**
 * Write data into flash. Each offset can only be written once after bank was erased
 * @param bank
 * @param offset into flash bank
  to read data
 * @param size of data to store
 */
void hal_flash_sector_write(int bank, uint32_t offset, const uint8_t * data, uint32_t size);

#if defined __cplusplus
}
#endif
#endif // __HAL_FLASH_SECTOR_H
