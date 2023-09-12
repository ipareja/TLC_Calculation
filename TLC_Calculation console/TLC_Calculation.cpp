/**
*	@file TLC_Calculation.cpp
*
*
*	File containing data, main and menu functions to calculate instantaneous TLC_left and TLC_right
*
*
*	@author Ignacio Pareja-Montoro
*	@date 02/08/2023
*	@version 1.0
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

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
double delta_t = 0.017;///< time elapsed between the current and the previous frame

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

int menu();///< Menu

void showStaticVehicleData();///< Show static vehicle data.
void showDynamicVehicleData();///< Show dynamic vehicle data.
void showDynamicRoadData();///< Show dynamic road data.
void showTimeData();///< Show time data.
void showTLC();///< Show TLC_left and TLC_right.
void showTLCAndData();///< Show TLC_left, TLC_right and all data.

void modifyStaticVehicleData();///< Modify static vehicle data and calculate TLC_left and TLC_right.
void modifyDynamicVehicleData();///< Modify dynamic vehicle data and calculate TLC_left and TLC_right.
void modifyDynamicRoadData();///< Modify dynamic road data and calculate TLC_left and TLC_right.
void modifyTimeData();///< Modify time data and calculate TLC_left and TLC_right.
		
void calculateTLC();///< Calculate TLC_left and TLC_right.

/**
*
*	Main function.
*	Firstly shows the units of measure.
*	Then shows a menu.
*
*	@retval		0	no error
*
*/
int main()
{
	int op;
	
	system("mode con: cols=65 lines=30");
	
	cout << endl;
	
	cout << "This application calculates instantaneous TLC_left and TLC_right\nusing equation 15 of the paper.\n\n";
	cout << "As an example, the values of the variables needed to calculate\nTLC_left and TLC_right are set initially but users can modify\nthem.\n\n";
	
	cout << "The units of measurements used are:\n\n";
	cout << "\tLength\t\tmeter (m)\n";
	cout << "\tTime\t\tsecond (s)\n";
	cout << "\tSpeed\t\tmeter per second (m/s)\n";
	cout << "\tRotation\tradian (rad)\n\n";
	
	system("pause");
	
	calculateTLC();

	do
	{	
		system("cls");
		
		op = menu();
		
		system("cls");
		
		switch(op){
			case 1: 
					showTLCAndData();
				 	break;
			case 2: 
					cout << "\nCURRENT DATA\n\n";
					showStaticVehicleData();
					modifyStaticVehicleData();
			 		break;
			case 3: 
					cout << "\nCURRENT DATA\n\n";
					showDynamicVehicleData();
					modifyDynamicVehicleData();
			 		break;
			case 4: 
					cout << "\nCURRENT DATA\n\n";
					showDynamicRoadData();
					modifyDynamicRoadData();
			 		break; 		
			 case 5: 
					cout << "\nCURRENT DATA\n\n";
					showTimeData();
					modifyTimeData();
			 		break;		
			case 6: 
			 		break;
		}
		
		if(op!=6)
			system("pause");
	}
	while (op != 6);
}

/**
*
*	Menu.		
*
*	@return	option chosen
*
*/
int menu()
{	
	int op;
	
	cout << endl;
	
	cout << "MAIN MENU\n";
	cout << "*********\n\n";
	cout << "1. Show TLC_left, TLC_right and data\n";
	cout << "2. Modify static vehicle data\n";
	cout << "3. Modify dynamic vehicle data\n";
	cout << "4. Modify dynamic road data\n";
	cout << "5. Modify time data\n";	
	cout << "6. Exit\n";
	
	cout << endl;
	cout << "Enter option: ";
	cin >> op;
	
	return op;	
}

/**
*
*	Show static vehicle data.
*
*/
void showStaticVehicleData()
{
	cout << "Static vehicle data\n";
	cout << "-------------------\n";
	
	cout << "Vehicle width (W_v)\t\t\t " << W_v << " m\n";
	
	cout << "Vehicle length (L_v)\t\t\t " << L_v << " m\n";
	
	cout << endl;
}

/**
*
*	Show dynamic vehicle data.
*
*/
void showDynamicVehicleData()
{	
	cout << "Dynamic vehicle data\n";
	cout << "--------------------\n";
	
	cout << "Vehicle speed (v)\t\t\t " << v << " m/s\n";
	
	cout << "Previous vehicle speed (v_prev)\t\t " << v_prev << " m/s\n";
	
	cout << "Vehicle position (Y_v)\t\t\t " << Y_v << " m\n";
	
	cout << "Vehicle rotation (alpha_v)\t\t " << alpha_v << " rad\n";

	cout << "Previous vehicle rotation (alpha_v_prev) " << alpha_v_prev << " rad\n";
	
	cout << endl;
}

/**
*
*	Show dynamic road data.
*
*/
void showDynamicRoadData()
{
	cout << "Dynamic road data\n";
	cout << "-----------------\n";
	
	cout << "Lane width (L_w)\t\t\t " << L_w << " m\n";
	
	cout << "Road rotation (alpha_r)\t\t\t " << alpha_r << " rad\n";
	
	cout << "Previous road rotation (alpha_r_prev)\t " << alpha_r_prev << " rad\n";
	
	cout << endl;
}

/**
*
*	Show time data.
*
*/
void showTimeData()
{
	cout << "Time data\n";
	cout << "---------\n";

	cout << "Time elapsed (delta_t)\t\t\t " << delta_t << " s\n";
	
	cout << endl;	
}

/**
*
*	Show TLC_left and TLC_right.
*
*/
void showTLC()
{
	cout << endl;
	
	cout << "\t\tTLC_left\t\t " << TLC_left << " s\n" ;
	
	cout << endl;
	
	cout << "\t\tTLC_right\t\t " << TLC_right << " s\n";
	
	cout << endl;	
}

/**
*
*	Show TLC_left, TLC_right and all data.
*
*/		
void showTLCAndData()
{
	showTLC();
	
	showStaticVehicleData();

	showDynamicVehicleData();
	
	showDynamicRoadData();
	
	showTimeData();
}

/**
*
*	Modify static vehicle data and calculate TLC_left and TLC_right.
*
*/
void modifyStaticVehicleData()
{	
	cout << "\nENTER NEW DATA (you do not need to type the units of measurement!!!) . . .\n\n";				
	
	cout << "Static vehicle data\n";
	cout << "-------------------\n";
	
	cout << "Vehicle width (W_v)\t\t\t ";
	cin >> W_v;
	
	cout << "Vehicle length (L_v)\t\t\t ";
	cin >> L_v;
	
	cout << endl;
	
	calculateTLC();
}

/**
*
*	Modify dynamic vehicle data and calculate TLC_left and TLC_right.
*
*/
void modifyDynamicVehicleData()
{	
	cout << "\nENTER NEW DATA (you do not need to type the units of measurement!!!) . . .\n\n";				
	
	cout << "Dynamic vehicle data\n";
	cout << "--------------------\n";
	
	cout <<  "Vehicle speed (v)\t\t\t ";
	cin >> v;
	
	cout << "Previous vehicle speed (v_prev)\t\t ";
	cin >> v_prev;
	
	cout << "Vehicle position (Y_v)\t\t\t ";
	cin >> Y_v;
	
	cout << "Vehicle rotation (alpha_v)\t\t ";
	cin >> alpha_v;
	
	cout << "Previous vehicle rotation (alpha_v_prev) ";
	cin >> alpha_v_prev;
	
	cout << endl;
	
	calculateTLC();
}

/**
*
*	Modify dynamic road data and calculate TLC_left and TLC_right.
*
*/
void modifyDynamicRoadData()
{
	cout << "\nENTER NEW DATA (you do not need to type the units of measurement!!!) . . .\n\n";				
	
	cout << "Dynamic road data\n";
	cout << "-----------------\n";
	
	cout << "Lane width (L_w)\t\t\t ";
	cin >> L_w;
	
	cout << "Road rotation (alpha_r)\t\t\t ";
	cin >> alpha_r;
	
	cout << "Previous road rotation (alpha_r_prev)\t ";
	cin >> alpha_r_prev;
	
	cout << endl;
	
	calculateTLC();
}

/**
*
*	Modify time data and calculate TLC_left and TLC_right.
*
*/
void modifyTimeData()
{
	cout << "\nENTER NEW DATA (you do not need to type the units of measurement!!!) . . .\n\n";				
	
	cout << "Time data\n";
	cout << "---------\n";

	cout << "Time elapsed (delta_t)\t\t\t ";
	cin >> delta_t;
		
	cout << endl;
	
	calculateTLC();
}

/**
*
*	Calculate TLC_left and TLC_right.
*
*/
void calculateTLC()
{	
	//CALCULATE static vehicle data
		
	sd_v = 0.5*sqrt(W_v*W_v + L_v*L_v);//Calculate SemiDiagonal
	
	gamma = atan(W_v/L_v);//Calculate gamma
	
	//CALCULATE Some common dynamic data
		
	v_prime = v + (v-v_prev)/delta_t;//Calculate projected speed after 1 second
				
	beta = alpha_r - alpha_v;//Calculate beta
	beta_prev = alpha_r_prev - alpha_v_prev;//Calculate beta in the previous frame
	beta_prime = beta + (beta-beta_prev)/delta_t;//Calculate projected beta after 1 second
	
	//CALCULATE TLC left
	 
 	Y_v_prime = -sin(gamma - beta)*sd_v;//when calculating TLCright
 	Y_e = Y_v + Y_v_prime;
 	Y = 0.5*L_w + Y_e; // when calculating TLCleft
 	
 	v_l = -v*sin(beta);// when calculating TLCleft	
	v_l_prime = -v_prime*sin(beta_prime);// when calculating TLCleft
	
	/*cout << "v_l:\t\t" << v_l << endl;
	cout << "v_l':\t\t" << v_l_prime << endl;
	cout << "Y:\t\t" << Y << endl;*/
	
	if(Y < 0 )
		TLC_left = 0;
	else
		if(v_l + v_l_prime == 0)
			TLC_left = numeric_limits<double>::infinity();
		else
			TLC_left = Y/(v_l + v_l_prime);

	//CALCULATE TLC right
	 	
	Y_v_prime = sin(gamma + beta)*sd_v;//when calculating TLCright
	Y_e = Y_v + Y_v_prime;
	Y = 0.5*L_w - Y_e;  // when calculating TLCright
	
	v_l = v*sin(beta);// when calculating TLCright
	v_l_prime = v_prime*sin(beta_prime);// when calculating TLCright
	
	/*cout << "v_l:\t\t" << v_l << endl;
	cout << "v_l':\t\t" << v_l_prime << endl;
	cout << "Y:\t\t" << Y << endl;*/
	
	if(Y < 0 )
		TLC_right= 0;
	else
		if(v_l + v_l_prime == 0)
			TLC_right = numeric_limits<double>::infinity();
		else
			TLC_right = Y/(v_l + v_l_prime);
}


