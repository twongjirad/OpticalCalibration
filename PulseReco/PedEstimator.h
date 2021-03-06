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
#include <cmath>

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

//  std::pair<short,short> IdentifyPedestal(std::vector<unsigned short> wfm);
  short IdentifyPedestal(std::vector<short> wfm);
  std::vector<float> SimpleSmooth(std::vector<short> wfm);
  std::pair<float,float> GetPedestalInfo(std::vector<short> wfm , short end);
  

};

#endif
/** @} */ // end of doxygen group 

