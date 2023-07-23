#pragma once

#include<Windows.h>
#include<ChBaseLibrary.h>
#include<ChWindowsLibrary.h>
#include<ChDirect3D11Library.h>


#ifndef TO_STRING

#ifdef UNICODE

#define TO_STRING(define) L#define

#else

#define TO_STRING(define) #define

#endif

#endif

#ifndef TO_FLOATING
#define TO_FLOATING(define) static_cast<float>(define)
#endif