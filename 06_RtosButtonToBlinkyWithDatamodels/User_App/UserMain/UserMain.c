/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_MAIN_C_
#define USER_MAIN_C_

#include "../../Core/Inc/main.h"
#include "../../Utils/CommonTypes.h"

void UserMain_Init() {}

void UserMain_Loop() {}

void UserMain( void )
{
    // Init
    UserMain_Init();

    // Loop
    for( ;; )
    {
        UserMain_Loop();
    }
}

#endif /* USER_MAIN_C_ */
