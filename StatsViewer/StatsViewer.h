// StatsViewer.h : main header file for the StatsViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

//
// CStatsViewerApp
//
class CStatsViewerApp : public CWinAppEx
{
public:
	CStatsViewerApp() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook{0};
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CStatsViewerApp theApp;
