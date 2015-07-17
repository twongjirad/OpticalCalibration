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

  
};

#endif
/** @} */ // end of doxygen group 

