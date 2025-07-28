/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_APP_C_
#define USER_APP_C_

#include "main.h"

void user_main(void) {
  // Init

  // Loop
  for (;;) {
    // Do something
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    HAL_Delay(500);
  }
}

#endif /* USER_APP_C_ */
