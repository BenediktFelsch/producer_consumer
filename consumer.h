#ifndef CONSUMER_H
#define CONSUMER_H

#ifdef _WIN32
#  include <windows.h>
DWORD WINAPI consume(LPVOID arg);
#else
void* consume(void *arg);
#endif

#endif
