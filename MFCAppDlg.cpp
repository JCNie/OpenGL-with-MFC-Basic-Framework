
// MFCAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppDlg dialog



CMFCAppDlg::CMFCAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_sizeChange = 0;
}

void CMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCAppDlg message handlers

BOOL CMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rect;

	//get size and position of the picture control
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);

	//convert screen coordinates to client coordinates
	ScreenToClient(rect);

	//create opengl control window
	_openGLControl.oglCreate(rect, this);

	//setup the cube timer
	_openGLControl._Timer = _openGLControl.SetTimer(1, 1, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	_sizeChange++;

	CRect rect;
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);
	//ClientToScreen(rect);

	// TODO: Add your message handler code here
	switch (nType)
	{
		case SIZE_RESTORED:
		{
			if (_openGLControl._isMaximized)
			{
				_openGLControl.OnSize(nType, cx, cy);
				_openGLControl._isMaximized = false;
			}
		
			else if (_sizeChange != 1)
			{
				_openGLControl.OnSize(SIZE_RESIZE, cx, cy);
			}

			break;
		}

		case SIZE_MAXIMIZED:
		{
			_openGLControl.OnSize(nType, cx, cy);
			_openGLControl._isMaximized = true;

			break;
		}

		default:
			break;
		
	}
}

