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
*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "PulseReco/LogicPulseFinder.h"

#include <vector>

int main(int argc, char** argv){

  //TFile* input = new TFile( "../data/20150721/wf_sequence_highstat.root", "OPEN" );
  //TFile* input = new TFile( "../data/20150721/wf_flasher_highstat_04.root", "OPEN" ); // about 256 ticks per TTL
  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_072515/wf_run_001.root", "OPEN" );
  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_072515/wf_run_002.root", "OPEN" );

  // 2015/07/30: Flasher tuning run
  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_083015/wf_run010.root", "OPEN" );
  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_073015/wf_run012.root", "OPEN" );
  
  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_080115/wf_run005.root", "OPEN" );
  //std::string output = "results_20150801_wf_run_005.root";

  //TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_080515/wf_run001.root", "OPEN" );
  //std::string output = "results_20150806_wf_run_001.root";  

  TFile* input = new TFile( "/home/kterao/LArLite/UserDev/NevisDecoder/Decoder/mac/FlasherData_080715/wf_run004.root", "OPEN" );
  std::string output = "results_20150807_wf_run_004.root";  

  TTree* tree = (TTree*)input->Get( "raw_wf_tree" );

  unsigned short LOGIC_CH = 39;
  
  int baseline_start = 100;
  int baseline_end = 200;
  int pulse_start = 0;
  int pulse_end   = 75;
  int integral_start = 0;
  int integral_end   = 75;

  unsigned short ch;
  unsigned short slot;
  unsigned int event;
  tree->SetBranchAddress("ch",&ch);
  tree->SetBranchAddress("slot",&slot);
  tree->SetBranchAddress("event",&event);
  std::vector< unsigned short >* adcs = NULL;
  TBranch *badc = 0;
  tree->SetBranchAddress("wf",&adcs,&badc);

  int nentries = tree->GetEntries();
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
  double dt_max;
  TTree* outtree = new TTree("outtree","output");
  outtree->Branch( "event", &ievent, "event/I" );
  outtree->Branch( "opchannel", &opchannel, "opchannel/I" );
  outtree->Branch( "charge", &charge, "charge/D" );
  outtree->Branch( "maxamp", &maxamp, "maxamp/D" );
  outtree->Branch( "baseline", &ave_baseline, "baseline/D" );
  outtree->Branch( "dt_max", &dt_max, "dt_max/D" );

  std::vector<int> ttlpulses;
  int entry = 0;
  tree->GetEntry(0);
  current_event = event;
  current_event_start_entry = entry;
  while ( entry<nentries ) {

    // find ttl pulses and then end of event
    tree->GetEntry(entry);

    // ------------------------------------------------------------
    if ( mode==TTLMODE ) {
      // search for TLL
      if ( slot!=6 || ch!=LOGIC_CH ) {
	entry++;
	continue;
      }
      //std::cout << "channel 38! adcs=" << adcs->size() << std::endl;
      //for (int i=0; i<adcs->size(); i++)
      //std::cout << adcs->at(i) << " ";
      //std::cout << std::endl;
      ttlpulses = lpf.Get_TTL_Starts(*adcs);
      std::cout << "Found " << ttlpulses.size() << " TTL pulses on ch=" << ch << std::endl;

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
	    if ( var<5.0 ) {
	      baseline += x/ticks;
	      ngood_baselines += 1.0;
	    }
	  }
	}//end of loop over pulses (for baselines)
	ave_baseline = baseline/ngood_baselines;

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
	  }
	}
      }
    }
    // ------------------------------------------------------------
    entry++;
    //    std::cout << "entry: " << entry << std::endl;
    //if ( mode==TTLMODE && current_event==10 )
    //break;
  }

  outtree->Write();
  return 0;
}
