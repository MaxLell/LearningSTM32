/*
 * Profiler.c
 *
 *  Created on: Aug 7, 2025
 *      Author: MaximilianLell
 */

#include "Profiler.h"
#include "../../Core/Inc/main.h"
#include "../../Utils/custom_assert.h"


extern u32 SystemCoreClock;
static bool bProfilerWasInitialized = false;

void Profiler_Init(void) {
  // Enable DWT and cycle counter
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

  bProfilerWasInitialized = true;
}

void Profiler_Start(Profiler_Config_t *const inout_ptProfiler) {
  inout_ptProfiler->u32StartCycles = DWT->CYCCNT;
  ASSERT(NULL != inout_ptProfiler);
  ASSERT(bProfilerWasInitialized);
}

void Profiler_Stop(Profiler_Config_t *const inout_ptProfiler) {
  inout_ptProfiler->u32StopCycles = DWT->CYCCNT;
  ASSERT(NULL != inout_ptProfiler);
  ASSERT(bProfilerWasInitialized);
}

u32 Profiler_GetCycles(const Profiler_Config_t *const inout_ptProfiler) {
  ASSERT(NULL != inout_ptProfiler);
  ASSERT(bProfilerWasInitialized);
  return inout_ptProfiler->u32StopCycles - inout_ptProfiler->u32StartCycles;
}

f32 Profiler_GetUsec(const Profiler_Config_t *const inout_ptProfiler) {
  ASSERT(NULL != inout_ptProfiler);
  ASSERT(bProfilerWasInitialized);
  ASSERT(0 != SystemCoreClock);
  return ((f32)Profiler_GetCycles(inout_ptProfiler)) / (SystemCoreClock / 1e6f);
}
