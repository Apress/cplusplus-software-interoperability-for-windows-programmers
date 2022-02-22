#pragma once

#include "TestParameters.h"

//
// CTTestDataInputDlg dialog
// Used to acquire and validate T-test parameters
//
class CTTestDataInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTTestDataInputDlg)

	// The population mean
	CString m_strMu0;

	// The sample size.
	CString m_strN;

	// The sample standard deviation.
	CString m_strSx;

	// The sample mean.
	CString m_strXbar;

	// Reference to the TTest parameters
	StatsViewer::TTestParams m_params;

public:
	CTTestDataInputDlg(const StatsViewer::TTestParams& params, CWnd* pParent = nullptr);
	virtual ~CTTestDataInputDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TTEST_DATA_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	// Idle processing
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);

	afx_msg void OnUpdateEditMu0(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditN(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditXbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnOk(CCmdUI* pCmdUI);

	// Change notifications
	afx_msg void OnChangeEditMu0();
	afx_msg void OnChangeEditN();
	afx_msg void OnChangeEditSx();
	afx_msg void OnChangeEditXbar();

public:
	// Retrieve the t-test params
	const StatsViewer::TTestParams& GetParams() const { return m_params; }

	virtual void OnOK();
};
