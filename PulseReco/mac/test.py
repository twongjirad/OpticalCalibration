from ROOT import std, PedEstimator
wf = std.vector('unsigned short')()

algo = PedEstimator()

wf.push_back(1)
res = algo.Calculate(wf)

print 'Mean:',res.first
print 'RMS:',res.second
