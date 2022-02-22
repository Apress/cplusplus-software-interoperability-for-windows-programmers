// CTTestDataInputDlg.cpp : implementation file
//

#include "pch.h"
#include "StatsViewer.h"
#include "TTestDataInputDlg.h"
#include "afxdialogex.h"


//
// CTTestDataInputDlg dialog
//
IMPLEMENT_DYNAMIC(CTTestDataInputDlg, CDialogEx)

//
// Construction
//
CTTestDataInputDlg::CTTestDataInputDlg(const StatsViewer::TTestParams& params, CWnd* pParent /*=nullptr*/)
	: m_params(params)
	, CDialogEx(IDD_TTEST_DATA_INPUT_DIALOG, pParent)
{
}

//
// Destructor
// 
CTTestDataInputDlg::~CTTestDataInputDlg()
{
}

//
// Data exchange
//
void CTTestDataInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MU0, m_strMu0);
	DDX_Text(pDX, IDC_EDIT_N, m_strN);
	DDX_Text(pDX, IDC_EDIT_SX, m_strSx);
	DDX_Text(pDX, IDC_EDIT_XBAR, m_strXbar);
}

BEGIN_MESSAGE_MAP(CTTestDataInputDlg, CDialogEx)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_MU0, OnUpdateEditMu0)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_N, OnUpdateEditN)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_SX, OnUpdateEditSx)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_XBAR, OnUpdateEditXbar)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateBtnOk)
	ON_EN_CHANGE(IDC_EDIT_MU0, &CTTestDataInputDlg::OnChangeEditMu0)
	ON_EN_CHANGE(IDC_EDIT_N, &CTTestDataInputDlg::OnChangeEditN)
	ON_EN_CHANGE(IDC_EDIT_SX, &CTTestDataInputDlg::OnChangeEditSx)
	ON_EN_CHANGE(IDC_EDIT_XBAR, &CTTestDataInputDlg::OnChangeEditXbar)
END_MESSAGE_MAP()

//
// CTTestDataInputDlg message handlers
//
void CTTestDataInputDlg::OnOK()
{
	UpdateData(true);

	// Update the TTestParams
	m_params.mu0 = _tstof(m_strMu0);
	m_params.xbar = _tstof(m_strXbar);
	m_params.sx = _tstof(m_strSx);
	m_params.n = _tstof(m_strN);

	CDialogEx::OnOK();
}

//
// Idle processing
//
LRESULT CTTestDataInputDlg::OnKickIdle(WPARAM /* wParam */, LPARAM /* lParam */)
{
	UpdateDialogControls(this, TRUE);
	// No more idle processing to do
	return FALSE;
}

//
// Update state
//
void CTTestDataInputDlg::OnUpdateEditMu0(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CTTestDataInputDlg::OnUpdateEditSx(CCmdUI* pCmdUI)
{
	const bool enabled = m_params.test_type == StatsViewer::TTestParams::TestType::OneSample;
	pCmdUI->Enable(!enabled);
}

void CTTestDataInputDlg::OnUpdateEditN(CCmdUI* pCmdUI)
{
	const bool enabled = m_params.test_type == StatsViewer::TTestParams::TestType::OneSample;
	pCmdUI->Enable(!enabled);
}

void CTTestDataInputDlg::OnUpdateEditXbar(CCmdUI* pCmdUI)
{
	const bool enabled = m_params.test_type == StatsViewer::TTestParams::TestType::OneSample;
	pCmdUI->Enable(!enabled);
}

//
// Update Ok button state depending on inputs
//
void CTTestDataInputDlg::OnUpdateBtnOk(CCmdUI* pCmdUI)
{
	if (m_params.test_type == StatsViewer::TTestParams::TestType::OneSample)
	{
		pCmdUI->Enable(m_strMu0.GetLength() > 0);
	}
	else
	{
		const bool isValid =
			StatsViewer::isValidNumber(CStringA(m_strMu0).GetString()) &&
			StatsViewer::isValidNumber(CStringA(m_strSx).GetString()) &&
			StatsViewer::isValidNumber(CStringA(m_strXbar).GetString()) &&
			StatsViewer::isValidNumber(CStringA(m_strN).GetString());

		pCmdUI->Enable(isValid);
	}
}

//
// Edit change handlers: ensure the underlying CString's are kept in sync with edits
//
void CTTestDataInputDlg::OnChangeEditMu0()
{
	UpdateData(true);
}

void CTTestDataInputDlg::OnChangeEditN()
{
	UpdateData(true);
}

void CTTestDataInputDlg::OnChangeEditSx()
{
	UpdateData(true);
}

void CTTestDataInputDlg::OnChangeEditXbar()
{
	UpdateData(true);
}
