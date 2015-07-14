from ROOT import std, CrapPulseFinder

wf = std.vector('unsigned short')()

wf.push_back(2)

algo = CrapPulseFinder()

res = algo.Reconstruct(wf)

print res.size(), "pulses found!"
