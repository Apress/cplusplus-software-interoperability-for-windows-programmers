// StatsViewerForm.h : interface of the CStatsViewerView class
//
#pragma once

#include "TestParameters.h"

class CStatsViewerForm : public CFormView
{
protected: // create from serialization only
	CStatsViewerForm() noexcept;
	DECLARE_DYNCREATE(CStatsViewerForm)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_STATSVIEWER_FORM };
#endif

// Attributes
public:
	CStatsViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);
	
	virtual void OnInitialUpdate();

// Implementation
public:
	virtual ~CStatsViewerForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

private:
	// Initialise and re-initialise the list controls
	void InitialiseListControls();

	// Load the data from the file and add to data sets
	void LoadData(const CString& strFilename, const CString& strName);

	// Populate the data list control with the named data set
	void PopulateData(const CString& strName);

	// Create the t-test
	std::shared_ptr<Stats::StatisticalTest>
		MakeTest(const StatsViewer::TTestParams& params, const CStringArray& arrDataSetNames, CString& strLabel) const;

	// Create the F-test
	std::shared_ptr<Stats::StatisticalTest>
		MakeTest(const StatsViewer::FTestParams& params, const CStringArray& arrDataSetNames, CString& strLabel) const;

	// Perform the test
	void PerformTest(const std::shared_ptr<Stats::StatisticalTest>& test, const CString& strLabel);

	// Retrieve the results as a string
	void GetResultsData(CString& strResults) const;

private:
	// List control with the data sets
	CListCtrl m_lvData;

	// Static data group and label
	CStatic m_labData;

	// Static results group and label
	CStatic m_labResults;

	// List control to hold the results
	CListCtrl m_lvResults;

	// The index of the final column; this ensures that subitems are added correctly
	UINT m_nLastColumnIndex;

	// The maximum number of rows currently displayed
	std::size_t m_nMaxRows;

	// Flag to indicate that the data list control already has an initial column
	bool m_bIndexColumnAdded;

	// Utility class to manage named data sets
	Stats::DataManager m_manager;

public:
	afx_msg void OnStatisticsDescriptive();
	afx_msg void OnUpdateStatisticsDescriptive(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsLinearRegression();
	afx_msg void OnUpdateStatisticsLinearRegression(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsTestsTtest();
	afx_msg void OnUpdateStatisticsTestsTtest(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsTestsOneSample();
	afx_msg void OnUpdateStatisticsTestsOneSample(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsTestsTwoSample();
	afx_msg void OnUpdateStatisticsTestsTwoSample(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsClearData();
	afx_msg void OnUpdateStatisticsClearData(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsTestsFTest();
	afx_msg void OnUpdateStatisticsTestsFTest(CCmdUI* pCmdUI);
	afx_msg void OnStatisticsTestsTwoSampleFTest();
	afx_msg void OnUpdateStatisticsTestsTwoSampleFTest(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMRClickListctrlResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnResultsCopy();
	afx_msg void OnUpdateResultsCopy(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in StatsViewerForm.cpp
inline CStatsViewerDoc* CStatsViewerForm::GetDocument() const
   { return reinterpret_cast<CStatsViewerDoc*>(m_pDocument); }
#endif
