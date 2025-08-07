/*
 * IsrHandler.h
 *
 *  Created on: Aug 7, 2025
 *      Author: MaximilianLell
 */

#ifndef ISRHANDLER_ISRHANDLER_H_
#define ISRHANDLER_ISRHANDLER_H_

#include "IsrIds.h"
#include "common_types.h"

typedef void (*IsrCallback_t)(const void *pContext);

typedef struct {
  IsrCallback_t pfCallback;
  const void *ptContext;
} IsrHandler_Entry_t;

void IsrHandler_Init(IsrHandler_Entry_t *const inout_atIsrTable,
                     const u8 in_u8TableSize);

void IsrHandler_RegisterIsr(const Isr_Id_e in_eId,
                            const IsrCallback_t in_pfIsrCallback,
                            const void *const in_pContext);

void IsrHandler_UnregisterIsr(const Isr_Id_e in_eId);

void IsrHandler_DispatchIsr(const Isr_Id_e in_eIsrId);

#endif /* ISRHANDLER_ISRHANDLER_H_ */
