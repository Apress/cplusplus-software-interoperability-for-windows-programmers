// CFTestDataInputDlg.cpp : implementation file
//

#include "pch.h"
#include "StatsViewer.h"
#include "FTestDataInputDlg.h"
#include "afxdialogex.h"

//
// CFTestDataInputDlg dialog
//
IMPLEMENT_DYNAMIC(CFTestDataInputDlg, CDialogEx)

//
// Construction
//
CFTestDataInputDlg::CFTestDataInputDlg(const StatsViewer::FTestParams& params, CWnd* pParent /*=nullptr*/)
	: m_params(params)
	, CDialogEx(IDD_FTEST_DATA_INPUT_DIALOG, pParent)
{
}

//
// Destructor
// 
CFTestDataInputDlg::~CFTestDataInputDlg()
{
}

//
// Data exchange
//
void CFTestDataInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SX1, m_strSx1);
	DDX_Text(pDX, IDC_EDIT_N1, m_strN1);
	DDX_Text(pDX, IDC_EDIT_SX2, m_strSx2);
	DDX_Text(pDX, IDC_EDIT_N2, m_strN2);
}

BEGIN_MESSAGE_MAP(CFTestDataInputDlg, CDialogEx)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_SX1, OnUpdateEditSx1)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_N1, OnUpdateEditN1)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_SX2, OnUpdateEditSx2)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_N2, OnUpdateEditN2)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateBtnOk)
	ON_EN_CHANGE(IDC_EDIT_SX1, &CFTestDataInputDlg::OnChangeEditSx1)
	ON_EN_CHANGE(IDC_EDIT_N1, &CFTestDataInputDlg::OnChangeEditN1)
	ON_EN_CHANGE(IDC_EDIT_SX2, &CFTestDataInputDlg::OnChangeEditSx2)
	ON_EN_CHANGE(IDC_EDIT_N2, &CFTestDataInputDlg::OnChangeEditN2)
END_MESSAGE_MAP()

//
// CDataInputDlg message handlers
//
void CFTestDataInputDlg::OnOK()
{
	UpdateData(true);

	// Update the TTestParams
	m_params.sx1 = _tstof(m_strSx1);
	m_params.n1 = _tstof(m_strN1);
	m_params.sx2 = _tstof(m_strSx2);
	m_params.n2 = _tstof(m_strN2);

	CDialogEx::OnOK();
}

//
// Idle processing
//
LRESULT CFTestDataInputDlg::OnKickIdle(WPARAM /* wParam */, LPARAM /* lParam */)
{
	UpdateDialogControls(this, TRUE);
	// No more idle processing to do
	return FALSE;
}

//
// Update state
//
void CFTestDataInputDlg::OnUpdateEditSx1(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CFTestDataInputDlg::OnUpdateEditSx2(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CFTestDataInputDlg::OnUpdateEditN1(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CFTestDataInputDlg::OnUpdateEditN2(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

//
// Update Ok button state depending on inputs
//
void CFTestDataInputDlg::OnUpdateBtnOk(CCmdUI* pCmdUI)
{
	const bool isValid =
		StatsViewer::isValidNumber(CStringA(m_strSx1).GetString()) &&
		StatsViewer::isValidNumber(CStringA(m_strSx2).GetString()) &&
		StatsViewer::isValidNumber(CStringA(m_strN1).GetString()) &&
		StatsViewer::isValidNumber(CStringA(m_strN2).GetString());

	pCmdUI->Enable(isValid);
}

//
// Edit change handlers: ensure the underlying CString's are kept in sync with edits
//
void CFTestDataInputDlg::OnChangeEditSx1()
{
	UpdateData(true);
}

void CFTestDataInputDlg::OnChangeEditN1()
{
	UpdateData(true);
}

void CFTestDataInputDlg::OnChangeEditSx2()
{
	UpdateData(true);
}

void CFTestDataInputDlg::OnChangeEditN2()
{
	UpdateData(true);
}
