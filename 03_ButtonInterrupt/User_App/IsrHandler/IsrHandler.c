/*
 * IsrHandler.c
 *
 *  Created on: Aug 7, 2025
 *      Author: MaximilianLell
 */

#include "IsrHandler.h"
#include "IsrIds.h"
#include "custom_assert.h"

static IsrHandler_Entry_t *g_atIsrTable;
static bool g_bWasInitialized;

void IsrHandler_Init(IsrHandler_Entry_t *const inout_atIsrTable,
                     const u8 in_u8TableSize) {
  ASSERT(NULL != inout_atIsrTable);
  ASSERT(E_ISR_ID_LAST == in_u8TableSize);
  ASSERT(false == g_bWasInitialized);

  // Initialize all entries in the ISR table to be invalid and empty
  for (u8 u8ArrIdx = 0; u8ArrIdx < in_u8TableSize; u8ArrIdx++) {
    inout_atIsrTable[u8ArrIdx].pfCallback = NULL;
    inout_atIsrTable[u8ArrIdx].ptContext = NULL;
  }

  // set the local static reference
  g_atIsrTable = inout_atIsrTable;
  g_bWasInitialized = true;
}

void IsrHandler_RegisterIsr(const Isr_Id_e in_eId,
                            const IsrCallback_t in_pfIsrCallback,
                            const void *const in_pContext) {
  ASSERT(NULL != g_atIsrTable);
  ASSERT(NULL != in_pfIsrCallback);
  ASSERT(NULL != in_pContext);
  ASSERT(E_ISR_ID_LAST > in_eId);
  ASSERT(E_ISR_ID_INVALID != in_eId);

  // Check if the ISR ID is already registered
  bool bIsrWasRegistered = ((g_atIsrTable[in_eId].pfCallback != NULL) &&
                            (g_atIsrTable[in_eId].ptContext != NULL));
  ASSERT(false == bIsrWasRegistered);

  // Place the ISR entry in the table
  g_atIsrTable[in_eId].pfCallback = in_pfIsrCallback;
  g_atIsrTable[in_eId].ptContext = in_pContext;
}

void IsrHandler_UnregisterIsr(const Isr_Id_e in_eId) {
  ASSERT(NULL != g_atIsrTable);
  ASSERT(E_ISR_ID_LAST > in_eId);
  ASSERT(E_ISR_ID_INVALID != in_eId);

  // Check if the ISR ID is registered
  bool bIsrWasRegistered = ((g_atIsrTable[in_eId].pfCallback != NULL) &&
                            (g_atIsrTable[in_eId].ptContext != NULL));
  ASSERT(true == bIsrWasRegistered);

  // Clear the ISR entry
  g_atIsrTable[in_eId].pfCallback = NULL;
  g_atIsrTable[in_eId].ptContext = NULL;
}

void IsrHandler_DispatchIsr(const Isr_Id_e in_eId) {
  ASSERT(NULL != g_atIsrTable);
  ASSERT(E_ISR_ID_LAST > in_eId);
  ASSERT(E_ISR_ID_INVALID != in_eId);

  ASSERT(NULL != g_atIsrTable[in_eId].pfCallback);
  ASSERT(NULL != g_atIsrTable[in_eId].ptContext);

  // Call the registered ISR callback with its context
  g_atIsrTable[in_eId].pfCallback(g_atIsrTable[in_eId].ptContext);
}
