//----------------------------------------------------------------------------------------------
// StdAfx.h
//----------------------------------------------------------------------------------------------
#ifndef STDAFX_H
#define STDAFX_H

#pragma once
#define WIN32_LEAN_AND_MEAN
#define STRICT

//----------------------------------------------------------------------------------------------
// Microsoft Windows SDK for Windows 7
#include <WinSDKVer.h>
#include <new>
#include <windows.h>

//----------------------------------------------------------------------------------------------
// STL
#include <string>
using std::wstring;

#ifdef _DEBUG
#define MF_USE_LOGGING 1
//#define MF_USE_LOGREFCOUNT
//#define MF_TRACE_HANDLER
//#define MF_TRACE_SOURCE
//#define MF_TRACE_EVENTSOURCE
//#define MF_TRACE_OPSOURCE
//#define MF_TRACE_STREAMSOURCE
//#define MF_TRACE_MEDIATYPESOURCE
//#define MF_TRACE_STREAM
//#define MF_TRACE_EVENTSTREAM
//#define MF_TRACE_PARSER
//#define MF_TRACE_BYTESTREAM
#else
#define MF_USE_LOGGING 0
#endif

//----------------------------------------------------------------------------------------------
// Common Project Files
#include "../Common/MFInclude.h"

//----------------------------------------------------------------------------------------------
// Private trace
//#define TRACE_PTSDTS
//#define TRACE_OUTPUT_PTS

//----------------------------------------------------------------------------------------------
// Project Files
#include "Mpeg2Definition.h"
#include "MFByteStream.h"
#include "MFMpeg2Stream.h"
#include "MFSourceOperation.h"
#include "MFParser.h"
#include "MFMpeg2Source.h"
#include "MFMpeg2Handler.h"

#endif