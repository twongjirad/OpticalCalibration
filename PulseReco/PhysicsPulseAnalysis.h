/**
 * \file PhysicsPulseAnalysis.h
 *
 * \ingroup PulseReco
 * 
 * \brief Class def header for a class PhysicsPulseAnalysis
 *
 * @author jarrett
 */

/** \addtogroup PulseReco

    @{*/
#ifndef PHYSICSPULSEANALYSIS_H
#define PHYSICSPULSEANALYSIS_H

#include <iostream>
#include <vector>

/**
   \class PhysicsPulseAnalysis
   User defined class PhysicsPulseAnalysis ... these comments are used to generate
   doxygen documentation!
 */
class PhysicsPulseAnalysis{

public:

  /// Default constructor
  PhysicsPulseAnalysis(){}

  /// Default destructor
  ~PhysicsPulseAnalysis(){}

  std::vector<short> IntegrateMultipleWindows(std::vector<short> wfm , std::vector<short> start_times, short duration);
  int IntegrateWindow(std::vector<short> wfm, unsigned short window_start, unsigned short window_end);
  std::pair<int,float> GetLastTTL(float time , std::vector<float> TTL_times);
};

#endif
/** @} */ // end of doxygen group 

