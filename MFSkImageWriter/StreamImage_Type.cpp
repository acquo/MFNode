//----------------------------------------------------------------------------------------------
// StreamImage_Type.cpp
// Copyright (C) 2014 Dumonteil David
//
// MFNode is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MFNode is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------------------------
#include "StdAfx.h"

HRESULT CStreamImage::IsMediaTypeSupported(IMFMediaType* pMediaType, IMFMediaType** ppMediaType){

	TRACE_STREAM((L"ImageStream::IsMediaTypeSupported"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (pMediaType == NULL ? E_INVALIDARG : S_OK));

	AutoLock lock(m_CriticSection);

	IF_FAILED_RETURN(hr = CheckShutdown());

	GUID MajorType = GUID_NULL;
	GUID SubType = GUID_NULL;

	IF_FAILED_RETURN(hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &MajorType));
	IF_FAILED_RETURN(hr = pMediaType->GetGUID(MF_MT_SUBTYPE, &SubType));

	IF_FAILED_RETURN(hr = (MajorType != MFMediaType_Video ? MF_E_INVALIDTYPE : S_OK));
	// MFVideoFormat_RGB24 MFVideoFormat_RGB32
	IF_FAILED_RETURN(hr = (SubType != MFVideoFormat_RGB24 ? MF_E_INVALIDTYPE : S_OK));

	if(ppMediaType){
		*ppMediaType = NULL;
	}

	return hr;
}

HRESULT CStreamImage::GetMediaTypeCount(DWORD* pdwTypeCount){

	TRACE_STREAM((L"ImageStream::GetMediaTypeCount"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (pdwTypeCount == NULL ? E_INVALIDARG : S_OK));

	AutoLock lock(m_CriticSection);

	IF_FAILED_RETURN(hr = CheckShutdown());

	*pdwTypeCount = 1;

	return hr;
}

HRESULT CStreamImage::GetMediaTypeByIndex(DWORD dwIndex, IMFMediaType** ppType){

	TRACE_STREAM((L"ImageStream::GetMediaTypeByIndex"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (ppType == NULL ? E_INVALIDARG : S_OK));
	IF_FAILED_RETURN(hr = (dwIndex != 0 ? MF_E_NO_MORE_TYPES : S_OK));

	AutoLock lock(m_CriticSection);

	IF_FAILED_RETURN(hr = CheckShutdown());

	IMFMediaType* pType = NULL;

	try{

		IF_FAILED_THROW(hr = MFCreateMediaType(&pType));
		IF_FAILED_THROW(hr = pType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
		IF_FAILED_THROW(hr = pType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB24));

		*ppType = pType;
		(*ppType)->AddRef();
	}
	catch(HRESULT){}

	SAFE_RELEASE(pType);

	return hr;
}

HRESULT CStreamImage::SetCurrentMediaType(IMFMediaType* pMediaType){

	TRACE_STREAM((L"ImageStream::SetCurrentMediaType"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (pMediaType == NULL ? E_INVALIDARG : S_OK));

	AutoLock lock(m_CriticSection);

	IF_FAILED_RETURN(hr = CheckShutdown());

	IF_FAILED_RETURN(hr = IsMediaTypeSupported(pMediaType, NULL));
	IF_FAILED_RETURN(hr = MFGetAttributeSize(pMediaType, MF_MT_FRAME_SIZE, &m_uiWidth, &m_uiHeight));

	SAFE_RELEASE(m_pMediaType);
	m_pMediaType = pMediaType;
	m_pMediaType->AddRef();

	m_State = StreamReady;

	return hr;
}

HRESULT CStreamImage::GetCurrentMediaType(IMFMediaType** ppMediaType){

	TRACE_STREAM((L"ImageStream::GetCurrentMediaType"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (ppMediaType == NULL ? E_INVALIDARG : S_OK));

	AutoLock lock(m_CriticSection);

	IF_FAILED_RETURN(hr = CheckShutdown());

	IF_FAILED_RETURN(hr = (m_pMediaType == NULL ? MF_E_NOT_INITIALIZED : S_OK));

	*ppMediaType = m_pMediaType;
	(*ppMediaType)->AddRef();

	return hr;
}

HRESULT CStreamImage::GetMajorType(GUID* pguidMajorType){

	TRACE_STREAM((L"ImageStream::GetMajorType"));

	HRESULT hr;
	IF_FAILED_RETURN(hr = (pguidMajorType == NULL ? E_INVALIDARG : S_OK));

	*pguidMajorType = MFMediaType_Video;

	return hr;
}