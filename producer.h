#ifndef PRODUCER_H
#define PRODUCER_H

#ifdef _WIN32
#  include <windows.h>
DWORD WINAPI produce(LPVOID arg);
#else
void* produce(void *arg);
#endif

#endif
