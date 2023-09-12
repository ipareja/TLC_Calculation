
// TLC_CalculationDlg.h : header file
//

#pragma once


// CTLC_CalculationDlg dialog
class CTLC_CalculationDlg : public CDialogEx
{
// Construction
public:
	CTLC_CalculationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TLC_CALCULATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//TLC
	//The units of mesurements used are:"
		//Length	meter (m)"
		//Time		second (s)"
		//Speed		meter per second (m/s)"
		//Rotation	radian (rad)"

	//Static vehicle data
	double W_v = 1.8;///< vehicle width
	double L_v = 4.0;///< vehicle length

	//Dynamic vehicle data
	double v = 25.0;///< speed of the vehicle
	double v_prev = 24.9;///< speed of the vehicle in the previous frame
	double Y_v = 0.2;///< position of the centre of the vehicle regarding the central axis of the lane
	double alpha_v = 0.0051;///< rotation of the tangent of the vehicle around the vertical axis
	double alpha_v_prev = 0.0052;///< rotation of the tangent of the vehicle around the vertical axis in the previous frame

	//Dynamic road data
	double L_w = 3.5;///< lane width
	double alpha_r = 0.0201;///< rotation of the tangent of the road around the vertical axis
	double alpha_r_prev = 0.0204;///< rotation of the tangent of the road around the vertical axis in the previous frame

	//Time data
	double delta_t = 0.017;// time elapsed between the current and the previous frame

	//Calculated static vehicle data
	double sd_v;///< length of the semi-diagonal of the vehicle
	double gamma;///< angle between the longitudinal axis of the vehicle and the semi-diagonal

	//Common calculated dynamic data
	double beta;///< angle beta
	double beta_prev;///< angle beta in the previous frame
	double v_prime;///< projected speed after one second
	double beta_prime;///< projected angle beta after one second
	double Y_e;///< relative position of the front edge of the vehicle to the central axis of the lane

	//Side-related calculated dynamic data
	double Y_v_prime;///< relative position of the front edge of the vehicle to the line t
	double v_l;///< lateral speed
	double v_l_prime;///< projected lateral speed after one second
	double Y;///< lateral distance between the front edge of the vehicle and the lane boundary
	double TLC_left;///< time to line crossing (left)
	double TLC_right;///< time to line crossing (right)

	afx_msg void CalculateTLC();///< Calculate and set TLC_left and TLC_right.
	afx_msg void OnBnClickedButtonCopyv();///< Copy v_prev to v.
	afx_msg void OnBnClickedButtonCopyalphav();///< Copy alpha_v_prev to alpha_v.
	afx_msg void OnBnClickedButtonCopyalphar();///< Copy alpha_r_prev to alpha_r.
	afx_msg void OnBnClickedButtonCopyall();///< Copy v_prev to v, alpha_v_prev to alpha_v and alpha_r_prev to alpha_r.
	afx_msg void OnEnKillFocus(UINT ID);///< Calculates TLC_left and TLC_right when an edit control loses the keyboard focus.

//END TLC
	
};
