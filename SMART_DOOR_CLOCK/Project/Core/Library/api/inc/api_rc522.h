/**
 * @file       api_rc522.h
 * @brief      Header file for the RC522 RFID module API.
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_API_RC522_H_
#define INC_API_RC522_H_

/* Includes ----------------------------------------------------------- */
#include <driver_rc522.h>
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "main.h"

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initialize the RC522 RFID module and handle sub-cards.
 * @return 0 on success, or an error code on failure.
 */
uint8_t handle_sub_cards();

/**
 * @brief Check if there is a master RFID card stored in flash memory.
 * @return True if a master card is found, otherwise False.
 */
bool check_have_master_card();

/**
 * @brief Check if the scanned RFID card matches the master card.
 * @return True if the card matches the master card, otherwise False.
 */
bool check_master_card();

/**
 * @brief Check if a card is present.
 * @return True if a card is detected, otherwise False.
 */
bool check_have_card();

/**
 * @brief Check if a card is present and wait for up to 10 seconds for a card to be detected.
 * @return True if a card is detected within the timeout, otherwise False.
 */
bool check_have_card_with_timeout();

/**
 * @brief Check if the scanned RFID card is authorized to access.
 * @return True if the card is authorized, otherwise False.
 */
bool check_card_to_access();

/**
 * @brief Read existing RFID cards from flash memory.
 */
void flash_read_existing_card();

/**
 * @brief Add a new sub-card to the list of authorized RFID cards.
 */
void add_new_sub_card();

/**
 * @brief Handle the state of the master RFID card.
 */
void handle_state_master_card();

/**
 * @brief A test function for debugging purposes (can be removed in production).
 */

#endif /* INC_API_RC522_H_ */

/* End of file -------------------------------------------------------- */
