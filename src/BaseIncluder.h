#pragma once

#include<ChBaseLibrary.h>

#ifdef _WINDOWS
#include<Windows.h>
#include<ChWindowsLibrary.h>
#include<ChDirect3D11Library.h>
#endif

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

#ifndef GAME_WINDOW_WIDTH
#define GAME_WINDOW_WIDTH 1280
#endif

#ifndef GAME_WINDOW_HEIGHT
#define GAME_WINDOW_HEIGHT 720
#endif

#ifndef SCREEN_TO_PROJECTION_X
#define SCREEN_TO_PROJECTION_X(value) TO_FLOATING(value / GAME_WINDOW_WIDTH) * 2.0f - 1.0f
#endif

#ifndef SCREEN_TO_PROJECTION_Y
#define SCREEN_TO_PROJECTION_Y(value) 1.0f - TO_FLOATING(value / GAME_WINDOW_WIDTH) * 2.0f
#endif

template<typename BaseType>
static inline BaseType GetJsonNumber(const std::string _parameter,const ChPtr::Shared<ChCpp::JsonObject>& _json,BaseType _nullValue)
{
	auto&& valueObject = _json->GetJsonNumber(_parameter);
	BaseType value = _nullValue;
	if (valueObject != nullptr)value = *valueObject;
	return value;
}

static inline std::string GetJsonString(const std::string _parameter, const ChPtr::Shared<ChCpp::JsonObject>& _json,const std::string& _nullValue)
{
	auto&& valueObject = _json->GetJsonString(_parameter);
	std::string value = _nullValue;
	if (valueObject != nullptr)value = *valueObject;
	return value;
}

static inline bool GetJsonBoolean(const std::string _parameter, const ChPtr::Shared<ChCpp::JsonObject>& _json, const bool& _nullValue)
{
	auto&& valueObject = _json->GetJsonBoolean(_parameter);
	bool value = _nullValue;
	if (valueObject != nullptr)value = *valueObject;
	return value;
}