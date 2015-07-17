from ROOT import std, LogicPulseFinder,PedEstimator

wave = std.vector('short')()

#pulse_find = LogicPulseFinder()
ped_find = PedEstimator()

wave.push_back(0)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(-2)
wave.push_back(-1)
wave.push_back(-2)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(-1)
wave.push_back(-2)
wave.push_back(-3)
wave.push_back(-3)
wave.push_back(-4)
wave.push_back(-3)
wave.push_back(-4)
wave.push_back(-5)
wave.push_back(-6)
wave.push_back(-7)
wave.push_back(-7)
wave.push_back(-6)
wave.push_back(-7)
wave.push_back(-8)
wave.push_back(-9)
wave.push_back(-8)
wave.push_back(-9)
wave.push_back(-10)
wave.push_back(-11)
wave.push_back(-12)
wave.push_back(-12)
wave.push_back(-13)
wave.push_back(-12)
wave.push_back(-12)
wave.push_back(-11)
wave.push_back(-10)
wave.push_back(-9)
wave.push_back(-8)
wave.push_back(-9)
wave.push_back(-8)
wave.push_back(-7)
wave.push_back(-7)
wave.push_back(-6)
wave.push_back(-5)
wave.push_back(-5)
wave.push_back(-6)
wave.push_back(-4)
wave.push_back(-3)
wave.push_back(-2)
wave.push_back(-1)
wave.push_back(-2)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(-1)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(0)
wave.push_back(-1)
wave.push_back(-1)
wave.push_back(0)


basestartend = ped_find.IdentifyPedestal(wave)
print basestartend

#print basestartend[0]
#print basestartend[1]

#smoothed_vec = ped_find.SimpleSmooth(wave)

#for x in range(smoothed_vec.size()):
#	print smoothed_vec[x]

#StartVec = pulse_find.Get_TTL_Starts(wave)
#Flags = pulse_find.TTL_Health(wave)

#for x in range(StartVec.size()):
#	print StartVec[x]

#print Flags["peak_at_start"]
#print Flags["amp_chi"]

