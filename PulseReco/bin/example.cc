//
// Example C++ routine to run instantiate your sample class
//

/*
******************************************************************************
*Tree    :raw_wf_tree: Raw Waveforms                                          *
*Entries :   446508 : Total =      1714075770 bytes  File  Size =  297638955 *
*        :          : Tree compression factor =   5.76                       *
******************************************************************************
*Br    0 :event     : event/i                                                *
*Entries :   446508 : Total  Size=    1790583 bytes  File Size  =      31042 *
*Baskets :       43 : Basket Size=      51200 bytes  Compression=  57.65     *
*............................................................................*
*Br    1 :slot      : slot/s                                                 *
*Entries :   446508 : Total  Size=     895458 bytes  File Size  =      26320 *
*Baskets :       22 : Basket Size=      51200 bytes  Compression=  33.99     *
*............................................................................*
*Br    2 :ch        : ch/s                                                   *
*Entries :   446508 : Total  Size=     895406 bytes  File Size  =       9809 *
*Baskets :       22 : Basket Size=      51200 bytes  Compression=  91.21     *
*............................................................................*
*Br    3 :frame     : frame/s                                                *
*Entries :   446508 : Total  Size=     895484 bytes  File Size  =      19749 *
*Baskets :       22 : Basket Size=      51200 bytes  Compression=  45.31     *
*............................................................................*
*Br    4 :sample    : sample/s                                               *
*Entries :   446508 : Total  Size=     895510 bytes  File Size  =      59799 *
*Baskets :       22 : Basket Size=      51200 bytes  Compression=  14.96     *
*............................................................................*
*Br    5 :wf        : vector<unsigned short>                                 *
*Entries :   446508 : Total  Size= 1708702854 bytes  File Size  =  297444664 *
*Baskets :     6054 : Basket Size=   25600000 bytes  Compression=   5.74     *
*............................................................................*

******************************************************************************
*Tree    :OpDetWaveforms: PMT Readout Waveforms                                  *
*Entries :    80000 : Total =       326048558 bytes  File  Size =   61947878 *
*        :          : Tree compression factor =   5.27                       *
******************************************************************************
*Br    0 :run       : run/I                                                  *
*Entries :    80000 : Total  Size=     321186 bytes  File Size  =       2618 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression= 122.51     *
*............................................................................*
*Br    1 :subrun    : subrun/I                                               *
*Entries :    80000 : Total  Size=     321225 bytes  File Size  =       2438 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression= 131.56     *
*............................................................................*
*Br    2 :event     : event/I                                                *
*Entries :    80000 : Total  Size=     321212 bytes  File Size  =       5824 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  55.07     *
*............................................................................*
*Br    3 :opcrate   : opcrate/I                                              *
*Entries :    80000 : Total  Size=     321238 bytes  File Size  =       2638 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression= 121.59     *
*............................................................................*
*Br    4 :opslot    : opslot/I                                               *
*Entries :    80000 : Total  Size=     321225 bytes  File Size  =       8544 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  37.54     *
*............................................................................*
*Br    5 :opfemch   : opfemch/I                                              *
*Entries :    80000 : Total  Size=     321238 bytes  File Size  =       6071 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  52.83     *
*............................................................................*
*Br    6 :frame     : frame/I                                                *
*Entries :    80000 : Total  Size=     321212 bytes  File Size  =       5294 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  60.59     *
*............................................................................*
*Br    7 :sample    : sample/I                                               *
*Entries :    80000 : Total  Size=     321225 bytes  File Size  =       8727 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  36.75     *
*............................................................................*
*Br    8 :timestamp : timestamp/D                                            *
*Entries :    80000 : Total  Size=     641908 bytes  File Size  =      14433 *
*Baskets :       15 : Basket Size=      81408 bytes  Compression=  44.43     *
*............................................................................*
*Br    9 :readoutch : readoutch/I                                            *
*Entries :    80000 : Total  Size=     321264 bytes  File Size  =       5030 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  63.77     *
*............................................................................*
*Br   10 :category  : category/I                                             *
*Entries :    80000 : Total  Size=     321251 bytes  File Size  =       4392 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  73.03     *
*............................................................................*
*Br   11 :gaintype  : gaintype/I                                             *
*Entries :    80000 : Total  Size=     321251 bytes  File Size  =       4387 *
*Baskets :        9 : Basket Size=      51200 bytes  Compression=  73.12     *
*............................................................................*
*Br   12 :adcs      : vector<short>                                          *
*Entries :    80000 : Total  Size=  321872600 bytes  File Size  =   61833753 *
*Baskets :     5434 : Basket Size=   25600000 bytes  Compression=   5.20     *
*............................................................................*

*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"

#include "PulseReco/LogicPulseFinder.h"

#include <vector>

#define WFTREE 0
#define RAWDIGITS 1

int main(int argc, char** argv){


  int datafile = RAWDIGITS;
  std::string fname = "/home/tmw/swiz_v4_18_00/workdir/run2219_pmtrawdigits.root";
  std::string output = "results_run2219.root";
  
  TChain* tree;
  
  unsigned short LOGIC_CH = 39;
  
  int baseline_start = 0;
  int baseline_end = 40;
  int pulse_start = 100;
  int pulse_end   = 300;
  int integral_start = 130;
  int integral_end   = 230;

  unsigned short uch;
  unsigned short uslot;
  unsigned int uevent;
  int ch;
  int slot;
  int event;
  std::vector< unsigned short >* adcs = NULL;
  TBranch *badc = 0;
  if ( datafile==WFTREE ) {
    tree = new TChain( "raw_wf_tree" );
    tree->Add( fname.c_str() );
    tree->SetBranchAddress("ch",&uch);
    tree->SetBranchAddress("slot",&uslot);
    tree->SetBranchAddress("event",&uevent);
    tree->SetBranchAddress("wf",&adcs,&badc);
  }
  else {
    tree = new TChain( "rawdigitwriter/RawData/OpDetWaveforms" );
    tree->Add( fname.c_str() );
    tree->SetBranchAddress("opfemch", &ch);
    tree->SetBranchAddress("opslot",&slot);
    tree->SetBranchAddress("event",&event);
    tree->SetBranchAddress("adcs",&adcs,&badc);
  }

  int nentries = tree->GetEntries();
  std::cout << "Input File has " << nentries << " entries" << std::endl;

  LogicPulseFinder<unsigned short> lpf;
  int current_event_start_entry = 0;
  int current_event = 0;

  const int TTLMODE = 0;
  const int CHARGEMODE = 1;
  int mode = TTLMODE;

  TFile* out =  new TFile(output.c_str(), "RECREATE" );
  double charge;
  double maxamp;
  int ievent;
  int opchannel;
  double ave_baseline = 0.;
  double rms_baseline = 0.;
  int ngoodbaselines = 0;
  double dt_max;
  TTree* outtree = new TTree("outtree","output");
  outtree->Branch( "event", &ievent, "event/I" );
  outtree->Branch( "opchannel", &opchannel, "opchannel/I" );
  outtree->Branch( "charge", &charge, "charge/D" );
  outtree->Branch( "maxamp", &maxamp, "maxamp/D" );
  outtree->Branch( "baseline", &ave_baseline, "baseline/D" );
  outtree->Branch( "baselinerms", &rms_baseline, "baselinerms/D" );
  outtree->Branch( "ngoodbaselines", &ngoodbaselines, "ngoodbaselines/I" );
  outtree->Branch( "dt_max", &dt_max, "dt_max/D" );

  std::vector<int> ttlpulses;
  int entry = 0;
  tree->GetEntry(0);
  if ( datafile==WFTREE )
    event = (int)uevent;
  current_event = event;
  current_event_start_entry = entry;
  while ( entry<nentries ) {

    // find ttl pulses and then end of event
    tree->GetEntry(entry);
    if ( datafile==WFTREE ) {
      event = (int)uevent;
      ch = (int)uch;
      slot = (int)uslot;
    }

    //std::cout << "entry " << entry << " mode=" << mode << std::endl;

    // ------------------------------------------------------------
    if ( mode==TTLMODE ) {
      // search for TLL
      if ( slot!=6 || ch!=LOGIC_CH )  {
	entry++;
	//std::cout << "event=" << event << " slot=" << slot << " ch=" << ch << std::endl;
	continue;
      }
      //std::cout << "channel 38! adcs=" << adcs->size() << std::endl;
      //for (int i=0; i<adcs->size(); i++)
      //std::cout << adcs->at(i) << " ";
      //std::cout << std::endl;
      ttlpulses = lpf.Get_TTL_Starts(*adcs);
      std::cout << "Found " << ttlpulses.size() << " TTL pulses on ch=" << ch << std::endl;
      if (ttlpulses.size()==0) {
	for ( int i=0; i<4; i++ ) {
	  int tdc = 100 + 300*i;
	  ttlpulses.push_back( tdc );
	}
      }

      if ( event!=current_event ) {
	// event boundary. move to next mode, change entry
	mode = CHARGEMODE;
	entry = current_event_start_entry-1;
	std::cout << "end of TTL search. go back to beginning of event " << event << " (" << entry+1 << ") " << std::endl;
      }
    }//end of TLL MODE
    // ------------------------------------------------------------
    else if ( mode==CHARGEMODE ) {
      if ( event!=current_event ) {
	mode = TTLMODE;
	ttlpulses.clear();
	current_event = event;
	current_event_start_entry = entry;
	entry--;
	std::cout << "end of charge mode" << std::endl;
      }
      else {
	// otherwise integrate over window
	ave_baseline = 0.0;
	double baseline = 0.0;
	double ngood_baselines  = 0.0;
	for ( int ipulse=0; ipulse<ttlpulses.size(); ipulse++ ) {
	  
	  // baseline
	  double x = 0.;
	  double xx = 0.;
	  double ticks = 0;
	  for ( int tdc=ttlpulses.at(ipulse)+baseline_start; tdc<ttlpulses.at(ipulse)+baseline_end; tdc++ ) {
	    if ( tdc>=adcs->size() )
	      break;
	    x += (double)adcs->at( tdc );
	    xx += ((double)adcs->at( tdc ))*((double)adcs->at(tdc));
	    ticks += 1.0;
	  } 
	  if ( ticks>=20 ) {
	    double var = sqrt( xx/ticks - (x/ticks)*(x/ticks) );
	    //std::cout << "baseline var: " << var << std::endl;
	    if ( var<5.0 ) {
	      baseline += x/ticks;
	      ngood_baselines += 1.0;
	    }
	  }
	}//end of loop over pulses (for baselines)
	ave_baseline = baseline/ngood_baselines;
	ngoodbaselines = int(ngood_baselines);
	if ( ngood_baselines > 1.0 ) {
	  for ( int ipulse=0; ipulse<ttlpulses.size(); ipulse++ ) {
	    int start = ttlpulses.at(ipulse)+pulse_start;
	    int end   = ttlpulses.at(ipulse)+pulse_end;
	    if ( end > adcs->size() )
	      end = adcs->size();
	    double ch_charge = 0.0;
	    maxamp = -1;
	    dt_max = -1;
	    for ( int i=start; i<end; i++ ) {
	      if ( i-ttlpulses.at(ipulse)>=integral_start && i-ttlpulses.at(ipulse)<integral_end )
		ch_charge += adcs->at(i)-ave_baseline;
	      if ( maxamp<adcs->at(i)-ave_baseline ) {
		maxamp = adcs->at(i)-ave_baseline;
		dt_max = (float)i-ttlpulses.at(ipulse);
	      }
	    }
	    
	    charge = ch_charge;
	    opchannel = (int)ch;
	    ievent = (int)event;
	    outtree->Fill();
	    //std::cout << "charge: " << charge << std::endl;
	  }
	}
      }
    }
    // ------------------------------------------------------------
    entry++;
    //    std::cout << "entry: " << entry << std::endl;
    //if ( mode==TTLMODE && current_event==100 )
    //break;
  }

  outtree->Write();
  return 0;
}
