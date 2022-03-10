// StatsViewerForm.cpp : implementation of the CStatsViewerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "StatsViewer.h"
#endif

#include "StatsViewerDoc.h"
#include "StatsViewerForm.h"

#include "DataSetsDlg.h"

#include "TTestDataInputDlg.h"
#include "FTestDataInputDlg.h"

namespace Convert
{
	std::string ToStdString(const CString& str)
	{
		CStringA s(str);
		return std::string(s.GetString());
	}

	CString ToCString(const std::string& str)
	{
		CStringA s(str.c_str());
		return CString(s);
	}
}

namespace {

	void PopulateListControl(CListCtrl& listCtrl, const std::unordered_map<std::string, double>& results)
	{
		listCtrl.DeleteAllItems();

		int i = 0;
		for (const auto& result : results)
		{
			CString strLabel = Convert::ToCString(result.first);
			listCtrl.InsertItem(i, strLabel);

			CString strStatistic;
			strStatistic.Format(_T("%.4f"), result.second);
			listCtrl.SetItemText(i++, 1, strStatistic);
		}
	}

	void ReportException(const std::exception& e)
	{
		CString strError;
		CString strException = Convert::ToCString(e.what());
		strError.Format(_T("Error: %s"), strException.GetString());
		AfxMessageBox(strError, MB_OK | MB_ICONERROR);
		return;
	}
}

//
// CStatsViewerView
//

IMPLEMENT_DYNCREATE(CStatsViewerForm, CFormView)

BEGIN_MESSAGE_MAP(CStatsViewerForm, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CStatsViewerForm::OnFileOpen)
	ON_COMMAND(ID_STATISTICS_DESCRIPTIVE, &CStatsViewerForm::OnStatisticsDescriptive)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_DESCRIPTIVE, &CStatsViewerForm::OnUpdateStatisticsDescriptive)
	ON_COMMAND(ID_STATISTICS_LINEARREGRESSION, &CStatsViewerForm::OnStatisticsLinearRegression)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_LINEARREGRESSION, &CStatsViewerForm::OnUpdateStatisticsLinearRegression)
	ON_COMMAND(ID_STATISTICS_TESTS_TTEST, &CStatsViewerForm::OnStatisticsTestsTtest)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_TESTS_TTEST, &CStatsViewerForm::OnUpdateStatisticsTestsTtest)
	ON_COMMAND(ID_STATISTICS_TESTS_1SAMPLE, &CStatsViewerForm::OnStatisticsTestsOneSample)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_TESTS_1SAMPLE, &CStatsViewerForm::OnUpdateStatisticsTestsOneSample)
	ON_COMMAND(ID_STATISTICS_TESTS_2SAMPLE, &CStatsViewerForm::OnStatisticsTestsTwoSample)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_TESTS_2SAMPLE, &CStatsViewerForm::OnUpdateStatisticsTestsTwoSample)
	ON_COMMAND(ID_STATISTICS_CLEARDATA, &CStatsViewerForm::OnStatisticsClearData)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_CLEARDATA, &CStatsViewerForm::OnUpdateStatisticsClearData)
	ON_COMMAND(ID_STATISTICS_TESTS_FTEST, &CStatsViewerForm::OnStatisticsTestsFTest)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_TESTS_FTEST, &CStatsViewerForm::OnUpdateStatisticsTestsFTest)
	ON_COMMAND(ID_STATISTICS_TESTS_2SAMPLE_FTEST, &CStatsViewerForm::OnStatisticsTestsTwoSampleFTest)
	ON_UPDATE_COMMAND_UI(ID_STATISTICS_TESTS_2SAMPLE_FTEST, &CStatsViewerForm::OnUpdateStatisticsTestsTwoSampleFTest)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LISTCTRL_RESULTS, &CStatsViewerForm::OnNMRClickListctrlResults)
	ON_COMMAND(ID_EDIT_COPY, &CStatsViewerForm::OnResultsCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CStatsViewerForm::OnUpdateResultsCopy)
END_MESSAGE_MAP()

//
// CStatsViewerForm construction
//
CStatsViewerForm::CStatsViewerForm() noexcept
	: CFormView(IDD_STATSVIEWER_FORM)
	, m_nLastColumnIndex(0)
	, m_nMaxRows(0)
	, m_bIndexColumnAdded(false)
{
}

//
// CStatsViewerForm destruction
//
CStatsViewerForm::~CStatsViewerForm()
{
	m_manager.ClearDataSets();
	TRACE("Clearing data sets.\n");
}

//
// Data exchange
//
void CStatsViewerForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL_DATA, m_lvData);
	DDX_Control(pDX, IDC_LISTCTRL_RESULTS, m_lvResults);
	DDX_Control(pDX, IDC_STATIC_RESULTS, m_labResults);
	DDX_Control(pDX, IDC_STATIC_DATA, m_labData);
}

//
// Window creation
//
BOOL CStatsViewerForm::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

//
// Initialise the form view
//
void CStatsViewerForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	InitialiseListControls();

	ResizeParentToFit();
}

// Initialise and re-initialise the list controls
void CStatsViewerForm::InitialiseListControls()
{
	// List control for the data
	// Delete structure
	m_lvData.DeleteAllItems();
	int nColumnCount = m_lvData.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
		m_lvData.DeleteColumn(0);

	// Recreate
	m_nLastColumnIndex = 0;
	m_bIndexColumnAdded = false;
	m_nMaxRows = 0;

	m_lvData.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_lvData.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 90);

	// List control for the results
	// Delete structure
	m_lvResults.DeleteAllItems();
	nColumnCount = m_lvResults.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
		m_lvResults.DeleteColumn(0);

	// Recreate
	m_lvResults.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_lvResults.InsertColumn(0, _T("Label"), LVCFMT_LEFT, 90);
	m_lvResults.InsertColumn(1, _T("Data"), LVCFMT_LEFT, 90);
}

//
// CStatsViewerView diagnostics
//
#ifdef _DEBUG
void CStatsViewerForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CStatsViewerForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStatsViewerDoc* CStatsViewerForm::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatsViewerDoc)));
	return (CStatsViewerDoc*)m_pDocument;
}
#endif //_DEBUG

//
// CStatsViewerView message handlers
//
void CStatsViewerForm::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStatsViewerForm::OnContextMenu(CWnd*, CPoint)
{
}

void CStatsViewerForm::OnFileOpen()
{
	CFileDialog dlg(TRUE,
		_T("*.txt"),
		NULL,
		OFN_HIDEREADONLY | OFN_CREATEPROMPT,
		_T("Stats Data (*.txt)|*.txt|All Files (*.*)|*.*||"),
		AfxGetApp()->m_pMainWnd);

	dlg.m_ofn.lpstrTitle = _T("Stats Data File");

	if (IDOK == dlg.DoModal())
	{
		LoadData(dlg.GetPathName(), dlg.GetFileTitle());
	}
}

void CStatsViewerForm::OnStatisticsDescriptive()
{
	CDataSetsDlg dlg(m_manager.ListDataSets());
	dlg.SetMaxSelection(1);
	if (dlg.DoModal() != IDOK)
		return;

	const CStringArray& arrDataSetNames = dlg.GetSelectedDataSetNames();
	CString strName(arrDataSetNames[0]);

	const std::string name = Convert::ToStdString(strName);
	const std::vector<double> data = m_manager.GetDataSet(name);
	if (data.empty())
	{
		CString strMessage;
		strMessage.Format(_T("The data set (%s) is empty."), strName.GetString());
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
	}
	else
	{
		CString strLabel;
		strLabel.Format(_T("Results for: %s"), strName.GetString());
		m_labResults.SetWindowText(strLabel);

		try
		{
			std::unordered_map<std::string, double> results = Stats::GetDescriptiveStatistics(data);
			PopulateListControl(m_lvResults, results);
			UpdateData(false);
		}
		catch (const std::exception& e)
		{
			ReportException(e);
		}
	}
}

void CStatsViewerForm::OnStatisticsLinearRegression()
{
	CDataSetsDlg dlg(m_manager.ListDataSets());

	dlg.SetMaxSelection(2);
	if (dlg.DoModal() != IDOK)
		return;

	const CStringArray& arrDataSetNames = dlg.GetSelectedDataSetNames();
	if (arrDataSetNames.GetSize() != 2)
		return;

	CString strIndepName(arrDataSetNames[0]);
	CString strDepName(arrDataSetNames[1]);
	const std::string indep_name = Convert::ToStdString(strIndepName);
	const std::string dep_name = Convert::ToStdString(strDepName);

	const std::vector<double> xs = m_manager.GetDataSet(indep_name);
	const std::vector<double> ys = m_manager.GetDataSet(dep_name);
	if (xs.empty())
	{
		CString strMessage;
		strMessage.Format(_T("The data set (%s) is empty."), strIndepName.GetString());
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		return;
	}

	if (ys.empty())
	{
		CString strMessage;
		strMessage.Format(_T("The data set (%s) is empty."), strDepName.GetString());
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		return;
	}

	CString strLabel;
	strLabel.Format(_T("Results for: %s ~ %s"), strDepName.GetString(), strIndepName.GetString());
	m_labResults.SetWindowText(strLabel);

	try
	{
		std::unordered_map<std::string, double> results = Stats::LinearRegression(xs, ys);
		PopulateListControl(m_lvResults, results);

		UpdateData(false);
	}
	catch (const std::exception& e)
	{
		ReportException(e);
	}
}

std::shared_ptr<Stats::StatisticalTest> 
CStatsViewerForm::MakeTest(const StatsViewer::TTestParams& params, const CStringArray& arrDataSetNames, CString& strLabel) const
{
	using namespace StatsViewer;

	std::shared_ptr<Stats::StatisticalTest> test = nullptr;

	switch (params.test_type)
	{
		case TTestParams::TestType::SummaryData:
		{
			strLabel.Format(_T("Results for the t-test"));
			try
			{
				test = std::make_shared<Stats::TTest>(params.mu0, params.xbar, params.sx, params.n);
			}
			catch (const std::exception& e)
			{
				ReportException(e);
			}
		}
		break;
		
		case TTestParams::TestType::OneSample:
		{
			CString strDataSetName(arrDataSetNames[0]);
			strLabel.Format(_T("Results for one-sample t-test: %s, mu = %f."), strDataSetName.GetString(), params.mu0);
			const std::string x1_name = Convert::ToStdString(strDataSetName);

			try
			{
				const std::vector<double> x1 = m_manager.GetDataSet(x1_name);

				test = std::make_shared<Stats::TTest>(params.mu0, x1);
			}
			catch (const std::exception& e)
			{
				ReportException(e);
			}
		}
		break;
		
		case TTestParams::TestType::TwoSample:
		{
			CString strSample1(arrDataSetNames[0]);
			CString strSample2(arrDataSetNames[1]);
			strLabel.Format(_T("Results for two-sample t-test: %s, %s"), strSample1.GetString(), strSample2.GetString());

			const std::string x1_name = Convert::ToStdString(strSample1);
			const std::string x2_name = Convert::ToStdString(strSample2);

			try
			{
				const std::vector<double> x1 = m_manager.GetDataSet(x1_name);
				const std::vector<double> x2 = m_manager.GetDataSet(x2_name);

				test = std::make_shared<Stats::TTest>(x1, x2);
			}
			catch (const std::exception& e)
			{
				ReportException(e);
			}
		}
		break;
		
		default:
		{
			CString strMessage;
			strMessage.Format(_T("The Test Type (%d) was not recognised."), params.test_type);
			AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		}
		break;
	}

	return test;
}

std::shared_ptr<Stats::StatisticalTest>
CStatsViewerForm::MakeTest(const StatsViewer::FTestParams& params, const CStringArray& arrDataSetNames, CString& strLabel) const
{
	using namespace StatsViewer;

	std::shared_ptr<Stats::StatisticalTest> test = nullptr;

	switch (params.test_type)
	{
		case FTestParams::TestType::SummaryData:
		{
			strLabel.Format(_T("Results for the F-test"));
			try
			{
				test = std::make_shared<Stats::FTest>(params.sx1, params.sx2, params.n1, params.n2);
			}
			catch (const std::exception& e)
			{
				ReportException(e);
			}
		}
		break;

		case FTestParams::TestType::TwoSample:
		{
			CString strSample1(arrDataSetNames[0]);
			CString strSample2(arrDataSetNames[1]);
			strLabel.Format(_T("Results for two-sample F-test: %s, %s"), strSample1.GetString(), strSample2.GetString());

			const std::string x1_name = Convert::ToStdString(strSample1);
			const std::string x2_name = Convert::ToStdString(strSample2);

			try
			{
				const std::vector<double> x1 = m_manager.GetDataSet(x1_name);
				const std::vector<double> x2 = m_manager.GetDataSet(x2_name);

				test = std::make_shared<Stats::FTest>(x1, x2);
			}
			catch (const std::exception& e)
			{
				ReportException(e);
			}
		}
		break;

		default:
		{
			CString strMessage;
			strMessage.Format(_T("The Test Type (%d) was not recognised."), params.test_type);
			AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
		}
		break;
	}

	return test;
}

void CStatsViewerForm::PerformTest(const std::shared_ptr<Stats::StatisticalTest>& test, const CString& strLabel)
{
	if (test == nullptr)
	{
		CString strMessage;
		strMessage.Format(_T("Invalid t-test object."));

		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
	}
	else
	{
		try
		{
			const bool result = test->Perform();
			if (!result)
			{
				CString strMessage;
				strMessage.Format(_T("An error occured while performing the test."));

				AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);
			}
			else
			{
				m_labResults.SetWindowText(strLabel);

				const auto results = test->Results();
				PopulateListControl(m_lvResults, results);
			}
		}
		catch (const std::exception& e)
		{
			ReportException(e);
		}
	}
	UpdateData(false);
}

void CStatsViewerForm::OnStatisticsTestsTtest()
{
	StatsViewer::TTestParams params;
	params.test_type = StatsViewer::TTestParams::TestType::SummaryData;

	CTTestDataInputDlg dlg(params);
	if (dlg.DoModal() != IDOK)
		return;

	CString strLabel;
	std::shared_ptr<Stats::StatisticalTest> test = MakeTest(dlg.GetParams(), CStringArray(), strLabel);
	PerformTest(test, strLabel);
}

void CStatsViewerForm::OnStatisticsTestsOneSample()
{
	StatsViewer::TTestParams params;
	params.test_type = StatsViewer::TTestParams::TestType::OneSample;

	CTTestDataInputDlg dlgInputs(params);
	if (dlgInputs.DoModal() != IDOK)
		return;
	// Get the data set
	CDataSetsDlg dlgDataSets(m_manager.ListDataSets());
	dlgDataSets.SetMaxSelection(1);
	if (dlgDataSets.DoModal() != IDOK)
		return;

	CString strLabel;
	const CStringArray& arrDataSetNames = dlgDataSets.GetSelectedDataSetNames();
	std::shared_ptr<Stats::StatisticalTest> test = MakeTest(dlgInputs.GetParams(), arrDataSetNames, strLabel);
	PerformTest(test, strLabel);
}

void CStatsViewerForm::OnStatisticsTestsTwoSample()
{
	CDataSetsDlg dlg(m_manager.ListDataSets());
	dlg.SetMaxSelection(2);
	if (dlg.DoModal() != IDOK)
		return;

	StatsViewer::TTestParams params;
	params.test_type = StatsViewer::TTestParams::TestType::TwoSample;

	CString strLabel;
	const CStringArray& arrDataSetNames = dlg.GetSelectedDataSetNames();
	std::shared_ptr<Stats::StatisticalTest> test = MakeTest(params, arrDataSetNames, strLabel);
	PerformTest(test, strLabel);
}

void CStatsViewerForm::OnStatisticsTestsFTest()
{
	StatsViewer::FTestParams params;
	params.test_type = StatsViewer::FTestParams::TestType::SummaryData;

	CFTestDataInputDlg dlg(params);
	if (dlg.DoModal() != IDOK)
		return;

	CString strLabel;
	std::shared_ptr<Stats::StatisticalTest> test = MakeTest(dlg.GetParams(), CStringArray(), strLabel);
	PerformTest(test, strLabel);
}

void CStatsViewerForm::OnStatisticsTestsTwoSampleFTest()
{
	CDataSetsDlg dlg(m_manager.ListDataSets());
	dlg.SetMaxSelection(2);
	if (dlg.DoModal() != IDOK)
		return;

	StatsViewer::FTestParams params;
	params.test_type = StatsViewer::FTestParams::TestType::TwoSample;

	CString strLabel;
	const CStringArray& arrDataSetNames = dlg.GetSelectedDataSetNames();
	std::shared_ptr<Stats::StatisticalTest> test = MakeTest(params, arrDataSetNames, strLabel);
	PerformTest(test, strLabel);
}

void CStatsViewerForm::OnStatisticsClearData()
{
	m_manager.ClearDataSets();

	m_labResults.SetWindowText(_T("Results"));
	InitialiseListControls();
}

void CStatsViewerForm::OnResultsCopy()
{
	// https://www.johndcook.com/blog/cplusplus_strings/

	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"), MB_OK | MB_ICONERROR);
		return;
	}

	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"), MB_OK | MB_ICONERROR);
		return;
	}

	CString strResults;
	GetResultsData(strResults);

	size_t size = sizeof(TCHAR) * (1 + strResults.GetLength());
	HGLOBAL hResult = GlobalAlloc(GMEM_MOVEABLE, size);
	LPTSTR lptstrCopy = (LPTSTR)GlobalLock(hResult);
	memcpy(lptstrCopy, strResults.GetBuffer(), size);
	GlobalUnlock(hResult);
	// For the appropriate data formats...
#ifndef _UNICODE
	if (::SetClipboardData(CF_TEXT, hResult) == NULL)
#else
	if (::SetClipboardData(CF_UNICODETEXT, hResult) == NULL)
#endif
	{
		CString strMessage;
		strMessage.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		AfxMessageBox(strMessage, MB_OK | MB_ICONERROR);

		CloseClipboard();
		GlobalFree(hResult);
		return;
	}
	CloseClipboard();
}

void CStatsViewerForm::GetResultsData(CString& strResults) const
{
	int itemCount = m_lvResults.GetItemCount();
	for (int i = 0; i < itemCount; ++i)
	{
		CString strItem;
		CString strItemText0 = m_lvResults.GetItemText(i, 0);
		CString strItemText1 = m_lvResults.GetItemText(i, 1);
		strItem.Format(_T("%s\t%s\n"), (LPCTSTR)strItemText0, (LPCTSTR)strItemText1);
		strResults.Append(strItem);
	}
}

//
// Load the data from the file and add to data sets
//
void CStatsViewerForm::LoadData(const CString& strFilename, const CString& strName)
{
	CStdioFile file;
	if (file.Open(strFilename, CFile::modeRead))
	{
		std::vector<double> data;

		CString strLine;
		while (file.ReadString(strLine))
		{
			data.emplace_back(_tstof(strLine));
		}

		if (!data.empty())
		{
			const std::string name = Convert::ToStdString(strName);
			if (!name.empty())
			{
				if (m_manager.Add(name, data))
				{
					PopulateData(strName);
				}
			}
		}
		else
		{
			CString strMessage;
			strMessage.Format(_T("No data found in file: %s"), strFilename.GetString());
			AfxMessageBox(strMessage, MB_ICONINFORMATION | MB_OK);
		}
	}
	else
	{
		CString strError;
		strError.Format(_T("Unable to open the file: %s"), strFilename.GetString());
		AfxMessageBox(strError, MB_ICONERROR | MB_OK);
	}
}

//
// Populate the data list control with the named data set
//
void CStatsViewerForm::PopulateData(const CString& strName)
{
	const std::string name = Convert::ToStdString(strName);
	const std::vector<double> data = m_manager.GetDataSet(name);

	const bool addIndices = data.size() > m_nMaxRows;
	m_lvData.InsertColumn(++m_nLastColumnIndex, strName.GetString(), LVCFMT_LEFT, 90);

	// Insert index column only if the current data set is longer than any previous set
	if (addIndices)
	{
		std::size_t nPrevMax = m_nMaxRows;
		m_nMaxRows = max(nPrevMax, data.size());

		for (std::size_t i = nPrevMax; i < m_nMaxRows; ++i)
		{
			if (!m_bIndexColumnAdded)
			{
				CString strIndex;
				strIndex.Format(_T("[%d]"), (int)(i + 1));
				m_lvData.InsertItem((int)i, strIndex);
			}
		}
	}

	// Insert the data
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		CString strItem;
		strItem.Format(_T("%.4f"), data.at(i));
		m_lvData.SetItemText((int)i, m_nLastColumnIndex, strItem);
	}

	UpdateData(false);
}

//
// UI updates
//
void CStatsViewerForm::OnUpdateStatisticsDescriptive(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 0);
}

void CStatsViewerForm::OnUpdateStatisticsLinearRegression(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 1);
}

void CStatsViewerForm::OnUpdateStatisticsTestsTtest(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CStatsViewerForm::OnUpdateStatisticsTestsOneSample(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 0);
}

void CStatsViewerForm::OnUpdateStatisticsTestsTwoSample(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 1);
}

void CStatsViewerForm::OnUpdateStatisticsClearData(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 0);
}

void CStatsViewerForm::OnUpdateStatisticsTestsFTest(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}

void CStatsViewerForm::OnUpdateStatisticsTestsTwoSampleFTest(CCmdUI* pCmdUI)
{
	std::size_t count = m_manager.CountDataSets();
	pCmdUI->Enable(count > 1);
}

void CStatsViewerForm::OnUpdateResultsCopy(CCmdUI* pCmdUI)
{
	bool hasData = m_lvResults.GetItemCount() > 0;
	pCmdUI->Enable(hasData);
}

void CStatsViewerForm::OnSize(UINT, int, int)
{
	if (m_hWnd != NULL)
	{
		if (m_lvData.m_hWnd != NULL && m_lvResults.m_hWnd != NULL)
		{
			CRect rcClient;
			GetClientRect(&rcClient);

			const int outerMargin = 5;
			const int innerMargin = 25;

			rcClient.top += outerMargin;
			rcClient.left += outerMargin;
			rcClient.bottom -= outerMargin;
			rcClient.right -= outerMargin;

			int outerWidth = rcClient.Width() / 3;

			CRect rcDataLabel(rcClient);
			CRect rcResultsLabel(rcClient);

			rcDataLabel.right = outerWidth * 2;
			rcResultsLabel.left = rcDataLabel.right + outerMargin;

			rcClient.top += innerMargin;
			rcClient.left += innerMargin;
			rcClient.bottom -= innerMargin;
			rcClient.right -= innerMargin;

			int innerWidth = rcClient.Width() / 3;

			CRect rcDataControl(rcClient);
			CRect rcResultsControl(rcClient);

			rcDataControl.right = innerWidth * 2;
			rcResultsControl.left = rcDataLabel.right + innerMargin;

			// Move
			m_lvData.MoveWindow(rcDataControl);
			m_lvResults.MoveWindow(rcResultsControl);

			m_labData.MoveWindow(rcDataLabel);
			m_labResults.MoveWindow(rcResultsLabel);
		}
	}
}

void CStatsViewerForm::OnNMRClickListctrlResults(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CMenu menu;
	menu.LoadMenu(IDR_RESULTS_POPUP);

	CMenu* pSubMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
		CPoint pt(pNMListView->ptAction);
		POINT p;
		p.x = pt.x;
		p.y = pt.y;
		::ClientToScreen(pNMHDR->hwndFrom, &p);

		if (!pPopupMenu->Create(this, p.x, p.y, (HMENU)pSubMenu->m_hMenu, FALSE, TRUE))
			return;

		((CFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
	*pResult = 0;
}
