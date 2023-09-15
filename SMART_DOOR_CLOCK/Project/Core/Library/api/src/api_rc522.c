/**
 * @file       api_rc522.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      API for RC522 RFID module.
 */

/* Includes ----------------------------------------------------------- */
#include "api_rc522.h"
#include "driver_flash.h"
#include "main.h"
#include "driver_delay.h"
#include "api_handle_display.h"

/* Public defines ----------------------------------------------------- */
#define ADDRESS_STORAGE_ID_CARD_MASTER 0x8060000 // Sector 7
#define ADDRESS_STORAGE_ID_CARD_SUB_FIRST 0x8060006
#define ADDRESS_STORAGE_NUM_SUB_CARDS 0x0807FFFE
#define MFRC522_LEN 6
#define MAX_SUB_CARDS 10

/* Public variables --------------------------------------------------- */
uint8_t flash_read_master_card[MFRC522_LEN] = {0};
uint8_t card_uid[MFRC522_LEN] = {0};
uint8_t id_card_check[MFRC522_LEN] = {0};
uint8_t id_card_master[MFRC522_LEN] = {0};
uint8_t num_sub_cards = 0;
uint8_t num_sub_cards_from_flash = 0;
uint8_t id_card_sub[MAX_SUB_CARDS][MFRC522_LEN] = {0};
uint8_t existing_card[MAX_SUB_CARDS * 2][MFRC522_LEN] = {0};
uint8_t error_card[MFRC522_LEN] = {0};

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Read existing RFID cards from flash memory.
 */
void flash_read_existing_card()
{
	flash_read_2d_array(ADDRESS_STORAGE_ID_CARD_SUB_FIRST, existing_card, MAX_SUB_CARDS * 2, MFRC522_LEN);
	num_sub_cards_from_flash = 0;

	for (int i = 0; i < MAX_SUB_CARDS * 2; i++)
	{
		bool isValidArray = false;

		for (int j = 0; j < MFRC522_LEN; j++)
		{
			if ((existing_card[i][j] != error_card[j]) && (existing_card[i][j] != 0xFF))
			{
				isValidArray = true;
				break;
			}
		}

		if (isValidArray)
		{
			num_sub_cards_from_flash++;
		}
	}
	num_sub_cards = num_sub_cards_from_flash;
}

/**
 * @brief Check if there is a master RFID card stored in flash memory.
 * @return True if a master card is found, otherwise False.
 */
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

/**
 * @brief Handle the state of the master RFID card.
 */
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
		h_display_tap_master_card();
		while (1)
		{
			if (check_have_card())
			{
				for (int i = 0; i < MFRC522_LEN; i++)
				{
					id_card_master[i] = card_uid[i];
				}
				flash_write_array(ADDRESS_STORAGE_ID_CARD_MASTER, id_card_master, MFRC522_LEN);
				flash_read_array(ADDRESS_STORAGE_ID_CARD_MASTER, flash_read_master_card, MFRC522_LEN);
				break;
			}
		}
	}
}

/**
 * @brief Check if the scanned RFID card matches the master card.
 * @return True if the card matches the master card, otherwise False.
 */
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
	for (int i = 0; i < MFRC522_LEN; i++)
	{
		if (id_card_check[i] == id_card_master[i])
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

/**
 * @brief Check if a card is present and wait for up to 10 seconds for a card to be detected.
 * @return True if a card is detected within the timeout, otherwise False.
 */
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

/**
 * @brief Add a new sub-card to the list of authorized RFID cards.
 */
void add_new_sub_card()
{
	flash_read_2d_array(ADDRESS_STORAGE_ID_CARD_SUB_FIRST, existing_card, MAX_SUB_CARDS * 2, MFRC522_LEN);
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
		is_match = true;
		for (int j = 0; j < MFRC522_LEN; j++)
		{
			if ((id_card_check[j] != existing_card[i][j]) && (id_card_check[j] != id_card_sub[i][j]) && (id_card_check[j] != id_card_master[j]))
			{
				is_match = false;
				break;
			}
		}

		if (is_match)
		{
			break;
		}
	}

	bool already_added = false;

	for (int i = 0; i < num_sub_cards; i++)
	{
		bool card_match = true;
		for (int j = 0; j < MFRC522_LEN; j++)
		{
			if (id_card_check[j] != id_card_sub[i][j])
			{
				card_match = false;
				break;
			}
		}
		if (card_match)
		{
			already_added = true;
			break;
		}
	}

	if (!is_match && !already_added && (num_sub_cards < MAX_SUB_CARDS))
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_sub[num_sub_cards][i] = id_card_check[i];
		}
		num_sub_cards++;
		uint32_t next_flash_address = ADDRESS_STORAGE_ID_CARD_SUB_FIRST + (num_sub_cards * MFRC522_LEN);
		flash_write_2d_array(next_flash_address, id_card_sub, num_sub_cards + 1, MFRC522_LEN);
		flash_read_existing_card();
	}
}

/**
 * @brief Check if the scanned RFID card is authorized to access.
 * @return True if the card is authorized, otherwise False.
 */
bool check_card_to_access()
{
	flash_read_array(ADDRESS_STORAGE_ID_CARD_MASTER, id_card_master, MFRC522_LEN);
	flash_read_2d_array(ADDRESS_STORAGE_ID_CARD_SUB_FIRST, existing_card, MAX_SUB_CARDS * 2, MFRC522_LEN);

	mfrc522_status_t status = mfrc522_check(card_uid);
	bool is_match_access_card = false;

	if (status == MI_OK)
	{
		for (int i = 0; i < MFRC522_LEN; i++)
		{
			id_card_check[i] = card_uid[i];
		}
	}

	for (int i = 0; i < MAX_SUB_CARDS * 2; i++)
	{
		bool cardMatches = false;
		for (int j = 0; j < MFRC522_LEN; j++)
		{
			if (id_card_check[j] != error_card[j])
			{
				if ((id_card_check[j] != id_card_master[j]) && (id_card_check[j] != existing_card[i][j]))
				{
					cardMatches = false;
					break;
				}
				else
				{
					cardMatches = true;
				}
			}
		}

		if (cardMatches)
		{
			is_match_access_card = true;
			break;
		}
		else
		{
			is_match_access_card = false;
		}
	}
	return is_match_access_card;
}

/**
 * @brief Check if a card is present.
 * @return True if a card is detected, otherwise False.
 */
bool check_have_card()
{
	mfrc522_status_t status = mfrc522_check(card_uid);
	bool is_have_card = false;
	if (status == MI_OK)
	{
		is_have_card = true;
	}
	else
	{
		is_have_card = false;
	}
	return is_have_card;
}

/* End of file -------------------------------------------------------- */
