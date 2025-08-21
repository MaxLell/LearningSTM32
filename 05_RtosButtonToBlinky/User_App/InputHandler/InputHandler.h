/*
 * InputHandler.h
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "../DataModel/DataModel.h"

void InputHandler_Init( DataModel_t *const inout_ptButtonEvent );

void InputHandler_Loop( void );

#endif /* INPUTHANDLER_H */
