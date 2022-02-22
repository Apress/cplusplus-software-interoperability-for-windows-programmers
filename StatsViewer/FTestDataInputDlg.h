#pragma once

#include "TestParameters.h"

//
// CFTestDataInputDlg dialog
// Used to acquire and validate F-test parameters
//
class CFTestDataInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFTestDataInputDlg)

	// The sample standard deviation 1.
	CString m_strSx1;

	// The sample standard deviation 2.
	CString m_strSx2;

	// The sample size 1.
	CString m_strN1;

	// The sample size 2.
	CString m_strN2;

	// Reference to the TTest parameters
	StatsViewer::FTestParams m_params;

public:
	CFTestDataInputDlg(const StatsViewer::FTestParams& params, CWnd* pParent = nullptr);
	virtual ~CFTestDataInputDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	// Idle processing
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);

	afx_msg void OnUpdateEditSx1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSx2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditN1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditN2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnOk(CCmdUI* pCmdUI);

	// Change notifications
	afx_msg void OnChangeEditSx1();
	afx_msg void OnChangeEditN1();
	afx_msg void OnChangeEditSx2();
	afx_msg void OnChangeEditN2();

public:
	// Retrieve the F-test params
	const StatsViewer::FTestParams& GetParams() const { return m_params; }

	virtual void OnOK();
};
