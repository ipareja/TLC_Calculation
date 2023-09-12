/**
*	@file Data.h
*
*
*	Declaration of class Data.
*	Class Data stores, shows and modifies data, and calculate instantaneous TLC_left and TLC_right.
*
*
*	@author Ignacio Pareja-Montoro
*	@date 02/08/2023
*	@version 1.0
*/

#ifndef _DATA_H_
#define _DATA_H_

class Data
{
	private:
		//The units of mesurements used are:"
			//Length	meter (m)"
			//Time		second (s)"
			//Speed		meter per second (m/s)"
			//Rotation	radian (rad)"
		
		//Static vehicle data
		double W_v;///< vehicle width
		double L_v;///< vehicle length
		
		//Dynamic vehicle data
		double v;///< speed of the vehicle
		double v_prev;///< speed of the vehicle in the previous frame
		double Y_v;///< position of the centre of the vehicle regarding the central axis of the lane
		double alpha_v;///< rotation of the tangent of the vehicle around the vertical axis
		double alpha_v_prev;///< rotation of the tangent of the vehicle around the vertical axis in the previous frame
		
		//Dynamic road data
		double L_w;///< lane width
		double alpha_r;///< rotation of the tangent of the road around the vertical axis
		double alpha_r_prev;///< rotation of the tangent of the road around the vertical axis in the previous frame
		
		//Time data
		double delta_t;///< time elapsed between the current and the previous frame
		
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
		
	public:
		Data();///< Default constructor: assign example values.
		
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
};

#endif
