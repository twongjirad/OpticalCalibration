from ROOT import std ,PedEstimator, PhysicsPulseAnalysis, LogicPulseFinder
import ROOT
from ROOT import *
import sys
import matplotlib.pyplot as plt
import array

LogicPulseFinder = LogicPulseFinder()
PhysicsPulseAnalysis = PhysicsPulseAnalysis()
PedEstimator = PedEstimator()

input_file_name = sys.argv[1]
output_file_name = sys.argv[2]
input_file = ROOT.TFile(input_file_name)
output_file = ROOT.TFile(output_file_name,'RECREATE')
input_tree = input_file.Get('rawdigitwriter/RawData/OpDetWaveforms')
output_tree = ROOT.TTree('output_tree','output_tree')

charge = array.array('f',[0])
event  = array.array('I',[0])
TTLNo  = array.array('I',[0])
baseline_stdev = array.array('f',[0])
baseline_mean = array.array('f',[0])
pedestal_end = array.array('I',[0])
output_tree.Branch('charge',charge,'charge/F')
output_tree.Branch('event',event,'event/I')
output_tree.Branch('TTLNo',TTLNo,'TTLNo/I')
output_tree.Branch('baseline_stdev',baseline_stdev,'baseline_stdev/F')
output_tree.Branch('baseline_mean',baseline_mean,'baseline_mean/F')
output_tree.Branch('pedestal_end',pedestal_end,'pedestal_end/I')

events = 10
TTLs_for_event = []

for x in range(events):
	TTLs_for_event.append([x])

#Cycle through all entries in the tree looking for TTL type waveforms (i.e. right channel or # entries)
for entry in input_tree:

	waveform = std.vector('short')()

	if(entry.readoutch != 37):
		continue

	else:
		waveform = entry.adcs

		StartVec = LogicPulseFinder.Get_TTL_Starts(waveform) 

		frame_start = entry.timestamp
	
		for x in range(StartVec.size()):
			event_number = entry.event -1
			####This part is definitely very much clumsy... I'm sure it is better to store
			####an std:: vector full of other vectors, but can't figure out how to do this quickly
			TTLs_for_event[event_number].append(15.625*StartVec[x] + frame_start)
			#now we have a list filled with a list of TTL times for each event

window_width = 300
	
for entry in input_tree:

	window_charge = 0

	waveform = std.vector('short')()
	if(entry.adcs.size() != 1500):

		continue

	else:
		waveform       = entry.adcs
		ped_end        = PedEstimator.IdentifyPedestal(waveform)
		ped_info       = PedEstimator.GetPedestalInfo(waveform,ped_end)
		baseline_avg     = ped_info.first
		baseline_std     = ped_info.second

		window_charge  = PhysicsPulseAnalysis.IntegrateWindow(waveform,ped_end,ped_end + window_width)			
		window_charge  = window_charge - baseline_avg*(window_width + 1)

		event_num = entry.event - 1
		tmp = std.vector('float')()
		for x in range(len(TTLs_for_event[event_num])):
			tmp.push_back(TTLs_for_event[event_num][x])
				
		last_TTL_info  = PhysicsPulseAnalysis.GetLastTTL(ped_end*15.625 + entry.timestamp , tmp)
		which_TTL  	 = last_TTL_info.first
		t_to_last_TTL    = last_TTL_info.second

		charge[0]          = window_charge
		event[0]           = entry.event
		TTLNo[0]           = which_TTL
		baseline_mean[0]   = baseline_avg
		baseline_stdev[0]  = baseline_std
		pedestal_end[0]	   = ped_end

	output_tree.Fill()

output_file.Write()





			





	
