/*
 * Profiler.h
 *
 *  Created on: Aug 7, 2025
 *      Author: MaximilianLell
 */

#ifndef PROFILER_PROFILER_H_
#define PROFILER_PROFILER_H_

#include "../../Utils/common_types.h"

typedef struct {
  u32 u32StartCycles;
  u32 u32StopCycles;
} Profiler_Config_t;

void Profiler_Init(void);

void Profiler_Start(Profiler_Config_t *const inout_ptProfiler);

void Profiler_Stop(Profiler_Config_t *const inout_ptProfiler);

u32 Profiler_GetCycles(const Profiler_Config_t *const inout_ptProfiler);

f32 Profiler_GetUsec(const Profiler_Config_t *const inout_ptProfiler);

#endif /* PROFILER_PROFILER_H_ */
