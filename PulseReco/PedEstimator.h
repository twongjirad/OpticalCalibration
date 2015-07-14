/**
 * \file PedEstimator.h
 *
 * \ingroup PulseReco
 * 
 * \brief Class def header for a class PedEstimator
 *
 * @author jarrett
 */

/** \addtogroup PulseReco

    @{*/
#ifndef PEDESTIMATOR_H
#define PEDESTIMATOR_H

#include <iostream>
#include <vector>  // this is for std::vector
#include <utility> // this is for std::pair
/**
   \class PedEstimator
   User defined class PedEstimator ... these comments are used to generate
   doxygen documentation!
 */
class PedEstimator{

public:

  /// Default constructor
  PedEstimator(){}

  /// Default destructor
  ~PedEstimator(){}

  /// Compute a pedestal mean (first) & rms (second). If cannot be done, returns (-1,-1)
  std::pair<float,float> Calculate(std::vector<unsigned short> wf)
  {
    std::pair<float,float> res(-1,-1);
    if(wf.size()<1) return res;
    res.first = wf[0];
    res.second= 0.;
    return res;
  }

};

#endif
/** @} */ // end of doxygen group 

