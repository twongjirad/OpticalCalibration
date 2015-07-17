#ifndef PHYSICSPULSEANALYSIS_CXX
#define PHYSICSPULSEANALYSIS_CXX

#include "PhysicsPulseAnalysis.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////////
/// This function takes a waveform which may have several pulses in it and also  ///
/// a vector filled with integration start times (perhaps derived, for instance  ///
/// from logic pulse information). It then integrates over a fixed window after, ///
/// whose duration is also dictated by input. It then returns a vector filled	 ///
/// with total integrated charge for each window. If it detects that the final	 ///
/// integration window will extend beyond the end of the waveform it throws 0    ///
/// for the final peaks integrated charge				         ///
////////////////////////////////////////////////////////////////////////////////////

std::vector<short> PhysicsPulseAnalysis::IntegrateMultipleWindows(std::vector<short> wfm , std::vector<short> start_times, short duration) {

	std::vector<short> WindowCharge;

	if ((start_times.back() + duration ) > wfm.size()) {

		for (unsigned int i = 0; i < (start_times.size()-1); i++) {
	
			short charge = 0;	
			for (int j = 0; j < duration; j ++) {
	
				charge += wfm[start_times[i] + j];
		
			   }
		
			WindowCharge.push_back(charge);

		WindowCharge.push_back(0);

		   }
	   }

	else {

		for (unsigned int i = 0; i < start_times.size(); i++) {
	
			short charge = 0;	
			for (int j = 0; j < duration; j ++) {
	
				charge += wfm[start_times[i] + j];
		
			   }
		
			WindowCharge.push_back(charge);
		   }
	   }

	return WindowCharge;

}


int PhysicsPulseAnalysis::IntegrateWindow(std::vector<short> wfm, unsigned short window_start, unsigned short window_end) {

	int total_charge = 0;

	for (unsigned int i=window_start; i< window_end; i++) {

		total_charge += wfm[i];

	   }


	return total_charge;

}


std::pair<int,float> PhysicsPulseAnalysis::GetLastTTL(float time , std::vector<float> TTL_times)
{

	float diff = 1000000;
	int which_TTL = -1;
	std::pair<unsigned int, float> last_TTL_info;
	
	for (unsigned int i = 0; i < TTL_times.size(); i++) {

		if ((time - TTL_times[i]) < diff && (time-TTL_times[i]) >= 0) {

			diff = (time - TTL_times[i]); 
			which_TTL = i;
		   }
	   }

	last_TTL_info.first = which_TTL;
	last_TTL_info.second = diff;

	return last_TTL_info;

}




#endif
