// StatsViewer.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "StatsViewer.h"
#include "MainFrm.h"

#include "AboutDlg.h"
#include "StatsViewerDoc.h"
#include "StatsViewerForm.h"

//
// CStatsViewerApp
//
BEGIN_MESSAGE_MAP(CStatsViewerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CStatsViewerApp::OnAppAbout)
END_MESSAGE_MAP()

//
// CStatsViewerApp construction
//
CStatsViewerApp::CStatsViewerApp() noexcept
	:	m_bHiColorIcons(TRUE)
{
	// Support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;

	SetAppID(_T("SoftwareInteroperability.StatsViewer.1.0"));
}

//
// The one and only CStatsViewerApp object
//
CStatsViewerApp theApp;

//
// CStatsViewerApp initialization
//
BOOL CStatsViewerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	EnableTaskbarInteraction(FALSE);

	// Standard initialization
	SetRegistryKey(_T("SoftwareInteroperability"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CStatsViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CStatsViewerForm));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

//
// CStatsViewerApp customization load/save methods
//
void CStatsViewerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
}

void CStatsViewerApp::LoadCustomState()
{
}

void CStatsViewerApp::SaveCustomState()
{
}

//
// CStatsViewerApp message handlers
//

// App command to run the dialog
void CStatsViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

int CStatsViewerApp::ExitInstance()
{
	TRACE("Exiting CStatsViewerApp ...\n");

	return CWinAppEx::ExitInstance();
}
