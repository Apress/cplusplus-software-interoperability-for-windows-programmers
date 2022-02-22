// CDataSetsDlg dialog
#pragma once

class CDataSetsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataSetsDlg)

public:
	// Constructor
	CDataSetsDlg(const std::vector<Stats::DataSetInfo>& data_sets, CWnd* pParent = nullptr);

	// Destructor
	virtual ~CDataSetsDlg();

	// Constrain the number of datasets we can sensibly select 
	// for either descriptive statistics (1) or linear regression (2)
	void SetMaxSelection(UINT maxSelection) { m_nMaxSelection = maxSelection; }

	// Retrieve the selected data set name(s)
	const CStringArray& GetSelectedDataSetNames() const { return m_arrSelectedDataSetNames; }

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATASETS };
#endif

protected:
	// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateBtnOk(CCmdUI* pCmdUI);

private:
	// The data sets
	std::vector<Stats::DataSetInfo> m_data_sets;

	// The OK button
	CButton m_btnOk;

	// List box displaying the available data sets
	CListBox m_lbDataSets;

	// The maximum number of items that can be selected
	UINT m_nMaxSelection{};

	// Array of the selected data set names
	CStringArray m_arrSelectedDataSetNames;
};
