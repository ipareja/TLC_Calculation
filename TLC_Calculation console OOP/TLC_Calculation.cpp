/**
*	@file TLC_Calculation.cpp
*
*
*	File containing main and menu functions to calculate instantaneous TLC_left and TLC_right.
*
*
*	@author Ignacio Pareja-Montoro
*	@date 02/08/2023
*	@version 1.0
*/

#include <iostream>
#include "data.h"

using namespace std;

int menu();///< Menu

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
	Data d;
	
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
	
	d.calculateTLC();

	do
	{
		system("cls");
		
		op = menu();
		
		system("cls");
		
		switch(op){
			case 1: 
					d.showTLCAndData();
				 	break;
			case 2: 
					cout << "\nCURRENT DATA\n\n";
					d.showStaticVehicleData();
					d.modifyStaticVehicleData();
			 		break;
			case 3: 
					cout << "\nCURRENT DATA\n\n";
					d.showDynamicVehicleData();
					d.modifyDynamicVehicleData();
			 		break;
			case 4: 
					cout << "\nCURRENT DATA\n\n";
					d.showDynamicRoadData();
					d.modifyDynamicRoadData();
			 		break; 		
			 case 5: 
					cout << "\nCURRENT DATA\n\n";
					d.showTimeData();
					d.modifyTimeData();
			 		break;		
			case 6: 
			 		break;
		}
		
		if(op!=6)
			system("pause");
	}
	while (op != 6);
	
	return 0;
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

