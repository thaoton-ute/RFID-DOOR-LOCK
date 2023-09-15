/**
 * @file       api_rc522.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <API of RC522>
 */

/* Includes ----------------------------------------------------------- */
#include "api_rc522.h"
#include "driver_flash.h"
#include "main.h"
/* Public defines ----------------------------------------------------- */
#define ADDRESS_STORAGE_ID_CARD_MASTER 0x8008000 // Sector 2
#define ADDRESS_STORAGE_ID_CARD_SUB_FIRST 0x8008006
#define ADDRESS_STORAGE_ID_CARD_SUB_LAST 0x8008400
#define MFRC522_LEN 6
#define MAX_SUB_CARDS 10
/* Public enumerate/structure ----------------------------------------- */
/*Public variables*/
uint8_t flash_read_master_card[MFRC522_LEN] = {0};
uint8_t card_uid[MFRC522_LEN] = {0};
uint8_t id_card_check[MFRC522_LEN] = {0};
uint8_t id_card_master[MFRC522_LEN] = {0};
uint8_t num_sub_cards = 0;
uint8_t id_card_sub[MAX_SUB_CARDS][MFRC522_LEN] = {0};
uint8_t existing_card[MAX_SUB_CARDS * 2][MFRC522_LEN] = {0};

bool test_value = false;
bool card_exists = false;

/* Public function prototypes ----------------------------------------- */
bool check_have_master_card()
{
	flash_read_array(ADDRESS_STORAGE_ID_CARD_MASTER, flash_read_master_card, MFRC522_LEN);
	for (int i = 0; i < MFRC522_LEN; i++)
	{
		if (flash_read_master_card[i] != 0x00 && flash_read_master_card[i] != 0xFF)
		{
			return true;
		}
	}
	return false;
}

void handle_state_master_card()
{
	if (check_have_master_card())
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_master[i] = flash_read_master_card[i];
		}
	}

	else
	{
		mfrc522_status_t status = mfrc522_check(card_uid);
		if (status == MI_OK)
		{
			for (int i = 0; i < MFRC522_LEN; i++)
			{
				id_card_master[i] = card_uid[i];
			}
			flash_write_array(ADDRESS_STORAGE_ID_CARD_MASTER, id_card_master, MFRC522_LEN);
			flash_read_array(ADDRESS_STORAGE_ID_CARD_MASTER, flash_read_master_card, MFRC522_LEN);
		}
	}
}

bool check_master_card()
{
	mfrc522_status_t status = mfrc522_check(card_uid);
	if (status == MI_OK)
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_check[i] = card_uid[i];
		}
	}

	flash_read_array(ADDRESS_STORAGE_ID_CARD_MASTER, flash_read_master_card, MFRC522_LEN);
	uint8_t count_check_master_card = 0;
	for(int i = 0; i < MFRC522_LEN; i++)
	{
		if(id_card_check[i] == id_card_master[i])
		{
			count_check_master_card++;
		}
		else
		{
			break;
		}
	}
	return count_check_master_card == MFRC522_LEN;
}

bool check_have_card_with_timeout()
{
	uint32_t start_time = HAL_GetTick();
	bool value_timeout = true;
	mfrc522_status_t status;
	do
	{
		status = mfrc522_check(card_uid);
		if (status == MI_OK)
		{
			value_timeout = true;
			break;
		}
		uint32_t elapsed_time = HAL_GetTick() - start_time;

		if (elapsed_time >= 10000 && (status != MI_OK))
		{
			value_timeout = false;
			break;
		}
	} while (1);
	return value_timeout;
}

void add_new_sub_card()
{
	flash_read_2d_array(ADDRESS_STORAGE_ID_CARD_SUB_FIRST, existing_card, MAX_SUB_CARDS, MFRC522_LEN);
	mfrc522_status_t status = mfrc522_check(card_uid);

	if (status == MI_OK)
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_check[i] = card_uid[i];
		}
	}

	bool is_match = false;

	for (int i = 0; i < MAX_SUB_CARDS; i++)
	{
		for (int j = 0; j < MFRC522_LEN; j++)
		{
			if ((id_card_check[j] != existing_card[i][j]) && (id_card_check[j] != id_card_sub[i][j]))
			{
				is_match = false;
				break;
			}
			is_match = true;
		}

		if (is_match)
		{
			break;
		}
	}

	if (!is_match && (num_sub_cards < MAX_SUB_CARDS))
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_sub[num_sub_cards][i] = id_card_check[i];
		}
		num_sub_cards++;
		uint32_t next_flash_address = ADDRESS_STORAGE_ID_CARD_SUB_FIRST + (num_sub_cards * MFRC522_LEN);
		// Ghi dãy id_card_sub vào địa chỉ flash tiếp theo
		flash_write_2d_array(next_flash_address, id_card_sub, num_sub_cards + 1, MFRC522_LEN);

	}
}

/* End of file -------------------------------------------------------- */
