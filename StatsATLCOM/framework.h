#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlsafe.h>
#include <comdef.h>

#include <string>
#include <vector>
#include <unordered_map>


#include "Stats.h"
#include "DescriptiveStatistics.h"
#include "StatisticalTests.h"

// Error handling
class COMHRESULT
{
public:
    COMHRESULT(HRESULT hr) {
        m_hr = hr;
        if (FAILED(hr))
            throw _com_error(m_hr);
    }

    COMHRESULT& operator=(HRESULT hr) {
        m_hr = hr;
        if (FAILED(hr))
            throw _com_error(m_hr);
        return *this;
    }

    operator HRESULT() { return m_hr; }

private:
    HRESULT m_hr;
};
