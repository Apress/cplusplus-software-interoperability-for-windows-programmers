// AboutDlg.h : header file
//
#pragma once

#include "afxdialogex.h"

//
// CAboutDlg dialog used for App About
//
class CAboutDlg : public CDialogEx
{
public:
	// Constructor
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
