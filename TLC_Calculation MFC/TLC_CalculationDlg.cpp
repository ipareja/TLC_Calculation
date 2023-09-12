
// TLC_CalculationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TLC_Calculation.h"
#include "TLC_CalculationDlg.h"
#include "afxdialogex.h"
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTLC_CalculationDlg dialog

CTLC_CalculationDlg::CTLC_CalculationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TLC_CALCULATION_DIALOG, pParent)
	/*
	, W_v(0)
	, L_v(0)
	, v(0)
	, v_prev(0)
	, Y_v(0)
	, alpha_v(0)
	, alpha_v_prev(0)
	, L_w(0)
	, alpha_r(0)
	, alpha_r_prev(0)
	, delta_t(0)
	*/ //TLC
{
	CalculateTLC();//TLC
}

void CTLC_CalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_W_v, W_v);
	DDX_Text(pDX, IDC_EDIT_L_v, L_v);

	DDX_Text(pDX, IDC_EDIT_v, v);
	DDX_Text(pDX, IDC_EDIT_v_prev, v_prev);
	DDX_Text(pDX, IDC_EDIT_Y_v, Y_v);
	DDX_Text(pDX, IDC_EDIT_alpha_v, alpha_v);
	DDX_Text(pDX, IDC_EDIT_alpha_v_prev, alpha_v_prev);

	DDX_Text(pDX, IDC_EDIT_L_w, L_w);
	DDX_Text(pDX, IDC_EDIT_alpha_r, alpha_r);
	DDX_Text(pDX, IDC_EDIT_alpha_r_prev, alpha_r_prev);
	
	DDX_Text(pDX, IDC_EDIT_delta_t, delta_t);
	
	DDX_Text(pDX, IDC_EDIT_TLC_left, TLC_left);
	DDX_Text(pDX, IDC_EDIT_TLC_right, TLC_right);
}

BEGIN_MESSAGE_MAP(CTLC_CalculationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTLC_CalculationDlg::CalculateTLC)
	ON_BN_CLICKED(IDC_BUTTON_Copy_v, &CTLC_CalculationDlg::OnBnClickedButtonCopyv)
	ON_BN_CLICKED(IDC_BUTTON_Copy_alpha_v, &CTLC_CalculationDlg::OnBnClickedButtonCopyalphav)
	ON_BN_CLICKED(IDC_BUTTON_Copy_alpha_r, &CTLC_CalculationDlg::OnBnClickedButtonCopyalphar)
	ON_BN_CLICKED(IDC_BUTTON_Copy_all, &CTLC_CalculationDlg::OnBnClickedButtonCopyall)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_EDIT_W_v, IDC_EDIT_delta_t, &CTLC_CalculationDlg::OnEnKillFocus)
END_MESSAGE_MAP()


// CTLC_CalculationDlg message handlers

BOOL CTLC_CalculationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetWindowText(L"TLC Calculation");//TLC
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//TLC. Change Icon

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTLC_CalculationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTLC_CalculationDlg::OnPaint()
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
HCURSOR CTLC_CalculationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//TLC
/**
*
*	Calculate and set TLC_left and TLC_right.
*
*/
void CTLC_CalculationDlg::CalculateTLC()
{
	//CALCULATE fix data

	sd_v = 0.5*sqrt(W_v * W_v + L_v * L_v);//Calculate SemiDiagonal

	gamma = atan(W_v / L_v);//Calculate gamma

	//CALCULATE Some common dynamic data

	v_prime = v + (v - v_prev) / delta_t;//Calculate projected speed after 1 second

	beta = alpha_r - alpha_v;//Calculate beta
	beta_prev = alpha_r_prev - alpha_v_prev;//Calculate beta in the previous frame
	beta_prime = beta + (beta - beta_prev) / delta_t;//Calculate projected beta after 1 second

	//CALCULATE TLC left

	Y_v_prime = -sin(gamma - beta)*sd_v;//when calculating TLCright
	Y_e = Y_v + Y_v_prime;
	Y = 0.5*L_w + Y_e; // when calculating TLCleft

	v_l = -v * sin(beta);// when calculating TLCleft	
	v_l_prime = -v_prime * sin(beta_prime);// when calculating TLCleft

	if (Y < 0)
		TLC_left = 0;
	else
		if (v_l + v_l_prime == 0)
			TLC_left = std::numeric_limits<double>::infinity();
		else
			TLC_left = Y / (v_l + v_l_prime);

	//CALCULATE TLC right

	Y_v_prime = sin(gamma + beta)*sd_v;//when calculating TLCright
	Y_e = Y_v + Y_v_prime;
	Y = 0.5*L_w - Y_e;  // when calculating TLCright

	v_l = v * sin(beta);// when calculating TLCright
	v_l_prime = v_prime * sin(beta_prime);// when calculating TLCright

	if (Y < 0)
		TLC_right = 0;
	else
		if (v_l + v_l_prime == 0)
			TLC_right = std::numeric_limits<double>::infinity();
		else
			TLC_right = Y / (v_l + v_l_prime);
}

/**
*
*	Copy v_prev to v.
*
*/
void CTLC_CalculationDlg::OnBnClickedButtonCopyv()
{
	UpdateData(TRUE);

	v_prev = v;

	CalculateTLC();

	UpdateData(FALSE);
}

/**
*
*	Copy alpha_v_prev to alpha_v.
*
*/
void CTLC_CalculationDlg::OnBnClickedButtonCopyalphav()
{
	UpdateData(TRUE);

	alpha_v_prev = alpha_v;

	CalculateTLC();

	UpdateData(FALSE);
}

/**
*
*	Copy alpha_r_prev to alpha_r.
*
*/
void CTLC_CalculationDlg::OnBnClickedButtonCopyalphar()
{
	UpdateData(TRUE);

	alpha_r_prev = alpha_r;

	CalculateTLC();

	UpdateData(FALSE);
}

/**
*
*	Copy v_prev to v, alpha_v_prev to alpha_v and alpha_r_prev to alpha_r.
*
*/
void CTLC_CalculationDlg::OnBnClickedButtonCopyall()
{
	UpdateData(TRUE);

	v_prev = v;

	alpha_v_prev = alpha_v;

	alpha_r_prev = alpha_r;

	CalculateTLC();

	UpdateData(FALSE);
}

/**
*
*	Calculates TLC_left and TLC_right when an edit control loses the keyboard focus.
*
*/
void CTLC_CalculationDlg::OnEnKillFocus(UINT ID)
{
	UpdateData(TRUE);

	CalculateTLC();

	UpdateData(FALSE);
}
//END TLC
