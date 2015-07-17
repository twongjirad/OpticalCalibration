#ifndef PEDESTIMATOR_CXX
#define PEDESTIMATOR_CXX

#include "PedEstimator.h"
#include <cmath>
#include <utility>
#include <vector>


////////////////////////////////////////////////////////////////////////////////////
/// This function performs a very basic "denoising" of a waveform by applying    ///
/// a local average replacement. For each point, it scans a nearby neighborhood  ///
/// of specified size and replaces that point with the local average.            ///
////////////////////////////////////////////////////////////////////////////////////

std::vector<float> PedEstimator::SimpleSmooth(std::vector<short> wfm)
{
	int averaging_width = 2;
	std::vector<float> smoothed_wfm;
	int start;
	int finish;

	for (unsigned int i = 0; i < wfm.size(); i ++) {

		if(i < averaging_width) {
			start = 0;
		  }
		   else {
			start = i - averaging_width;
		     }

		if(i >= wfm.size()-averaging_width) {
			finish = wfm.size();
		  }
		   else {
			finish = i + averaging_width;
		     }

		float local_avg = 0;
		for (int j = start; j<=finish; j++) {
			local_avg += wfm[j];
   		  }

		local_avg /= float(2*averaging_width + 1.0);
	
		smoothed_wfm.push_back(local_avg);

	  }
	
	return smoothed_wfm;
}


////////////////////////////////////////////////////////////////////////////////////
/// Reads in a waveform and tries to identify a baseline region. It does this by ///
/// calculating an RMS for successive windows. If the RMS undergoes a rapid	 ///
/// increase in size it is assumed that you have found a peak and the baseline   ///
/// gets cut off and the end returned. Returns -1 if a peak is in the first step ///
////////////////////////////////////////////////////////////////////////////////////

short PedEstimator::IdentifyPedestal(std::vector<short> wfm)
{

	short step = 50;
	float baseline_rms_last = 100000;

	float front_avg = 0;
	float global_avg = 0;

	for (unsigned int i = 0; i < step; i++) {
		
		front_avg += wfm[i];
	   }
	front_avg /= float(step);

	for (unsigned int i = 0; i < wfm.size(); i++) {

		global_avg += wfm[i];

	   }
	global_avg /= float(wfm.size());

	if (front_avg > 2*global_avg) {

		return -1;

	   }

	for (unsigned int i = 0 ; i < wfm.size() ; i+=step) {

		float baseline_avg = 0;
		float baseline_rms = 0;

		for (unsigned int j = i ; j < i+step ; j++) {

			baseline_avg += wfm[j];

		   }
		baseline_avg /= step;

		for (unsigned int j = i ; j < i+step ; j++) {

			baseline_rms += std::pow((wfm[j]-baseline_avg),2);

		   }
		baseline_rms = std::sqrt(baseline_rms / float(step));
					
		if(baseline_rms > 5*baseline_rms_last) {
			
			return i;

		   }

		else {

			baseline_rms_last = baseline_rms;

		   }
	   }


	return wfm.size();

}


////////////////////////////////////////////////////////////////////////////////////
/// Given a waveform and a start and end channel, does a simple calculation of   ///
/// the mean and standard deviation of the baseline.				 ///
////////////////////////////////////////////////////////////////////////////////////

std::pair<float,float> PedEstimator::GetPedestalInfo(std::vector<short> wfm , short end)
{
	
	float baseline_mean = 0;
	float baseline_std = 0; 
	std::pair<float,float> baseline_info;
	
	for (unsigned short i = 0; i <= end; i++) {
		
		baseline_mean += wfm[i];

	   }

	baseline_mean /= (end+1);


	for (unsigned short i = 0; i <= end; i++) {

		baseline_std += std::pow((wfm[i] - baseline_mean),2);

	   }

	baseline_std = std::sqrt(baseline_std/(end+1));

	baseline_info.first = baseline_mean;
	baseline_info.second = baseline_std;


	return baseline_info;
	
}	
		

#endif
