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
 *  hal_flash_sector.c -- volatile test environment that provides just two memory banks
 *
 */

#include "hal_flash_sector.h"
#include "btstack_debug.h"

#include "stdint.h"
#include "string.h"

// validate
#include "stdio.h"
#include <stdlib.h>	// exit(..)

#define HAL_FLASH_SECTOR_SIZE 128
#define HAL_FLASH_SECTOR_NUM 2

static uint8_t hal_flash_storage_bank_1[HAL_FLASH_SECTOR_SIZE];
static uint8_t hal_flash_storage_bank_2[HAL_FLASH_SECTOR_SIZE];
static uint8_t * hal_flash_storage_banks[] = {hal_flash_storage_bank_1, hal_flash_storage_bank_2};

// validate that memory isn't written twice
static uint8_t hal_flash_storage_bank_1_written[HAL_FLASH_SECTOR_SIZE];
static uint8_t hal_flash_storage_bank_2_written[HAL_FLASH_SECTOR_SIZE];
static uint8_t * hal_flash_storage_banks_written[] = {hal_flash_storage_bank_1_written, hal_flash_storage_bank_2_written};

uint32_t hal_flash_sector_get_size(void){
	return HAL_FLASH_SECTOR_SIZE;
}

void hal_flash_sector_erase(int bank){
	if (bank > 1) return;
	memset(hal_flash_storage_banks[bank], 0xff, HAL_FLASH_SECTOR_SIZE);
	// validate
	memset(hal_flash_storage_banks_written[bank], 0, HAL_FLASH_SECTOR_SIZE);
}

void hal_flash_sector_init(void){
	hal_flash_sector_erase(0);
	hal_flash_sector_erase(1);
}

void hal_flash_sector_read(int bank, uint32_t offset, uint8_t * buffer, uint32_t size){

	// log_info("read offset %u, len %u", offset, size);

	if (bank > 1) return;
	if (offset > HAL_FLASH_SECTOR_SIZE) return;
	if ((offset + size) > HAL_FLASH_SECTOR_SIZE) return;

	memcpy(buffer, &hal_flash_storage_banks[bank][offset], size);
}

void hal_flash_sector_write(int bank, uint32_t offset, const uint8_t * data, uint32_t size){

	// log_info("write offset %u, len %u", offset, size);

	if (bank > 1) return;
	if (offset > HAL_FLASH_SECTOR_SIZE) return;
	if ((offset + size) > HAL_FLASH_SECTOR_SIZE) return;

	// validate start
	int i;
	for (i=0;i<size;i++){
		if (hal_flash_storage_banks_written[bank][offset+i]) {
			printf("Error: offset %u written twice!\n", offset+i);
			exit(10);
			return;			
		}
	}
	memset(&hal_flash_storage_banks_written[bank][offset], 1, size);
	// validate end

	memcpy(&hal_flash_storage_banks[bank][offset], data, size);
}
