/**
*	@file Data.h
*
*
*	Implementation of class Data.
*	Class Data stores, shows and modifies data, and calculate instantaneous TLC_left and TLC_right.
*
*
*	@author Ignacio Pareja-Montoro
*	@date 02/08/2023
*	@version 1.0
*/

#include <iostream>
#include <cmath>
#include <limits>

#include "data.h"

using namespace std;

/**
*
* 	Default constructor: assign example values.
*
*/
Data::Data()
{
	//Example values
	
	W_v = 1.8;
	L_v = 4.0;
	
	v = 25.0;
	v_prev = 24.9;
	Y_v = 0.2;
	alpha_v = 0.0051;
	alpha_v_prev = 0.0052;
	
	L_w = 3.5;
	alpha_r = 0.0201;
	alpha_r_prev = 0.0204;
	
	delta_t = 0.017;
}

/**
*
*	Method to show static vehicle data.
*
*/
void Data::showStaticVehicleData()
{
	cout << "Static vehicle data\n";
	cout << "-------------------\n";
	
	cout << "Vehicle width (W_v)\t\t\t " << W_v << " m\n";
	
	cout << "Vehicle length (L_v)\t\t\t " << L_v << " m\n";
	
	cout << endl;
}

/**
*
*	Method to show dynamic vehicle data.
*
*/
void Data::showDynamicVehicleData()
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
*	Method to show dynamic road data.
*
*/
void Data::showDynamicRoadData()
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
*	Method to show time data.
*
*/
void Data::showTimeData()
{
	cout << "Time data\n";
	cout << "---------\n";

	cout << "Time elapsed (delta_t)\t\t\t " << delta_t << " s\n";
	
	cout << endl;	
}

/**
*
*	Method to show TLC_left and TLC_right.
*
*/
void Data::showTLC()
{
	cout << endl;
	
	cout << "\t\tTLC_left\t\t " << TLC_left << " s\n" ;
	
	cout << endl;
	
	cout << "\t\tTLC_right\t\t " << TLC_right << " s\n";
	
	cout << endl;
}

/**
*
*	Method to show TLC_left, TLC_right and all data.
*
*/	
void Data::showTLCAndData()
{
	showTLC();
	
	showStaticVehicleData();

	showDynamicVehicleData();
	
	showDynamicRoadData();
	
	showTimeData();	
}

/**
*
*	Method to modify static vehicle data and calculate TLC_left and TLC_right.
*
*/
void Data::modifyStaticVehicleData()
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
*	Method to modify dynamic vehicle data and calculate TLC_left and TLC_right.
*
*/
void Data::modifyDynamicVehicleData()
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
*	Method to modify dynamic road data and calculate TLC_left and TLC_right.
*
*/
void Data::modifyDynamicRoadData()
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
*	Method to modify time data and calculate TLC_left and TLC_right.
*
*/
void Data::modifyTimeData()
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
*	Method to calculate TLC_left and TLC_right.
*
*/
void Data::calculateTLC()
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


