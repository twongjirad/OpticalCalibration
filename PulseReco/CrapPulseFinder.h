/**
 * \file CrapPulseFinder.h
 *
 * \ingroup PulseReco
 * 
 * \brief Class def header for a class CrapPulseFinder
 *
 * @author jarrett
 */

/** \addtogroup PulseReco

    @{*/
#ifndef CRAPPULSEFINDER_H
#define CRAPPULSEFINDER_H

#include <iostream>
#include "PedEstimator.h"
/**
   \class CrapPulseFinder
   User defined class CrapPulseFinder ... these comments are used to generate
   doxygen documentation!
 */

struct Pulse_t {

  short tstart;
  float amp;

  Pulse_t() {
    tstart = -1;
    amp = -1;
  }

};


class CrapPulseFinder{

public:

  /// Default constructor
  CrapPulseFinder(){}

  /// Default destructor
  ~CrapPulseFinder(){}

  std::vector<Pulse_t> Reconstruct(std::vector<unsigned short> wf) {
    
    std::vector<Pulse_t> result;

    auto ped_info = _algo.Calculate(wf);

    std::cout<<"Pedestal Mean: "<< ped_info.first << " ... RMS: " << ped_info.second << std::endl;

    // Find pulse.
    
    // done
    
    return result;

  }

  PedEstimator _algo;

};

#endif
/** @} */ // end of doxygen group 

