#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#include <stdint.h>

#ifndef NULL
#ifndef __cplusplus
#define NULL (void*)0
#else
#define NULL 0
#endif
#endif

#define UNITY_INCLUDE_EXEC_TIME
#define UNITY_INCLUDE_DOUBLE

#ifdef __cplusplus
extern "C"
{
#endif

void unityOutputStart();
void unityOutputChar(char);
void unityOutputFlush();
void unityOutputComplete();
uint32_t unityClockMs();

#define UNITY_OUTPUT_START()    unityOutputStart()
#define UNITY_OUTPUT_CHAR(c)    unityOutputChar(c)
#define UNITY_OUTPUT_FLUSH()    unityOutputFlush()
#define UNITY_OUTPUT_COMPLETE() unityOutputComplete()
#define UNITY_CLOCK_MS          unityClockMs

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* UNITY_CONFIG_H */