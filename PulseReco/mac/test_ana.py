from ROOT import TChain, CrapPulseFinder
import sys

ch=TChain('raw_wf_tree')
ch.AddFile(sys.argv[1])

algo = CrapPulseFinder()

print ch.GetEntries()

for x in xrange(ch.GetEntries()):

    ch.GetEntry(x)

    print ch.wf

    print 'reconstructing...'

    algo.Reconstruct(ch.wf)

    break

    
