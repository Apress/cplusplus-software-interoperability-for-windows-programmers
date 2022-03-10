// DataSetsDlg.cpp : implementation file
//

#include "pch.h"
#include "StatsViewer.h"
#include "DataSetsDlg.h"
#include "afxdialogex.h"

//
// CDataSetsDlg dialog
//
IMPLEMENT_DYNAMIC(CDataSetsDlg, CDialogEx)

//
// Construction
//
CDataSetsDlg::CDataSetsDlg(const std::vector<Stats::DataSetInfo>& data_sets, CWnd* pParent /*=nullptr*/)
	: m_data_sets(data_sets)
    , CDialogEx(IDD_DIALOG_DATASETS, pParent)
{
}

//
// Destructor
//
CDataSetsDlg::~CDataSetsDlg()
{
}

//
// Data exchange
//
void CDataSetsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DATASETS, m_lbDataSets);
}

BEGIN_MESSAGE_MAP(CDataSetsDlg, CDialogEx)
    ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
    ON_UPDATE_COMMAND_UI(IDOK, OnUpdateBtnOk)
    ON_BN_CLICKED(IDOK, &CDataSetsDlg::OnBnClickedOk)
END_MESSAGE_MAP()

//
// CDataSetsDlg message handlers
//
BOOL CDataSetsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    if (!m_data_sets.empty())
    {
        for (std::size_t i = 0; i < m_data_sets.size(); ++i)
        {
            const auto& data_set = m_data_sets.at(i);
            CString strItem(CA2W(data_set.first.c_str()));
            m_lbDataSets.AddString(strItem);
        }
    }

	return TRUE;
}

//
// Idle processing
//
LRESULT CDataSetsDlg::OnKickIdle(WPARAM /* wParam */, LPARAM /* lParam */)
{
    UpdateDialogControls(this, TRUE);
    // No more idle processing to do
    return FALSE;
}

//
// Update state of the OK button
//
void CDataSetsDlg::OnUpdateBtnOk(CCmdUI* pCmdUI)
{
    const int selection_count = m_lbDataSets.GetSelCount();
    pCmdUI->Enable(static_cast<UINT>(selection_count) == m_nMaxSelection);
}

//
// Process selected items in the list box
//
void CDataSetsDlg::OnBnClickedOk()
{
    const int count = m_lbDataSets.GetSelCount();
    std::vector<int> selected_items(m_nMaxSelection, 0);
    m_lbDataSets.GetSelItems(m_nMaxSelection, &selected_items[0]);

    for (std::size_t i = 0; i < selected_items.size(); ++i)
    {
        CString strItem;
        m_lbDataSets.GetText(selected_items[i], strItem);
        m_arrSelectedDataSetNames.Add(strItem);
    }

    CDialogEx::OnOK();
}
