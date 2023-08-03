#pragma once

#include<ChBaseLibrary.h>

#ifdef WIN32
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