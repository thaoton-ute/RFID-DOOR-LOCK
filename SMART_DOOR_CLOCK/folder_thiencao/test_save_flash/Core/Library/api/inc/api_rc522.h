/**
 * @file       api_rc522.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <API of RC522>
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
uint8_t handle_sub_cards();
bool check_have_master_card();
bool check_master_card();
bool check_have_card();
bool check_have_card_with_timeout();
bool check_card_to_access();
void add_new_sub_card();
void handle_state_master_card();

#endif /* INC_API_RC522_H_ */
/* End of file -------------------------------------------------------- */

