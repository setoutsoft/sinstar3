//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 2003  Microsoft Corporation.  All rights reserved.
//
//  EnumDisplayAttribureInfo.h
//
//          ITfEnumDisplayAttributeInfo implementation.
//
//////////////////////////////////////////////////////////////////////

#ifndef ENUMDISPLAYATTRIBUTEINFO_H
#define ENUMDISPLAYATTRIBUTEINFO_H

//+---------------------------------------------------------------------------
//
// CEnumDisplayAttributeInfo
//
//----------------------------------------------------------------------------

class CEnumDisplayAttributeInfo : public IEnumTfDisplayAttributeInfo
{
public:
    CEnumDisplayAttributeInfo();
    ~CEnumDisplayAttributeInfo();

    // IUnknown
	IUNKNOWN_BEGIN(IID_IEnumTfDisplayAttributeInfo,IEnumTfDisplayAttributeInfo)
	IUNKNOWN_END()

    // IEnumTfDisplayAttributeInfo
    STDMETHODIMP Clone(IEnumTfDisplayAttributeInfo **ppEnum);
    STDMETHODIMP Next(ULONG ulCount, ITfDisplayAttributeInfo **rgInfo, ULONG *pcFetched);
    STDMETHODIMP Reset();
    STDMETHODIMP Skip(ULONG ulCount);

private:
    LONG _iIndex; // next display attribute to enum
};

#endif ENUMDISPLAYATTRIBUTEINFO_H
