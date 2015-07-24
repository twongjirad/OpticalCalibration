import os,sys
from pmt_chmap import getPMTID, getChannel
from ROOT import *

finput = TFile( "results_04.root", "OPEN" )

outtree = finput.Get("outtree")

canvpos = { 
    # panel 1
    3:(0,1),
    5:(0,3),
    1:(1,0),
    6:(1,4),
    2:(2,0),
    7:(2,4),
    4:(3,2),
    # panel 2
    10:(0,1),
    33:(0,3),
    8:(1,0),
    12:(1,4),
    9:(2,0),
    13:(2,4),
    11:(3,2),
    # panel 3
    16:(0,1),
    34:(0,3),
    14:(1,0),
    18:(1,4),
    15:(2,0),
    19:(2,4),
    17:(3,1),
    35:(3,3),
    # panel 4
    22:(0,2),
    20:(1,0),
    24:(1,4),
    21:(2,0),
    25:(2,4),
    23:(3,1),
    36:(3,3),
    # panel 5
    29:(0,2),
    26:(1,0),
    31:(1,4),
    27:(2,0),
    32:(2,4),
    28:(3,1),
    30:(3,3) }
            

panels = {0:[1,2,3,4,5,6,7],
          1:[8,9,10,11,12,13,33],
          2:[14,15,16,17,18,19,34,35],
          3:[20,21,22,23,24,25,36],
          4:[26,27,28,29,30,31,32] }
canvs = []
hists = {}
for p in xrange(0,5):
    panellist = panels[p]
    cp = TCanvas("canv%d"%(p),"Panel %d"%(p),2000,2000)
    cp.Divide(4,5)
    cp.Draw()
    ipanel = 1
    for pmtid in panellist:
        readch = getChannel(pmtid)
        padid = canvpos[pmtid][1]*4 + canvpos[pmtid][0] + 1
        print "canvas pos: ",canvpos[pmtid], " padid=",padid
        print "panel id: ",ipanel
        cp.cd( padid )
        hname = "h2_ch%d_pmt%d"%(readch,pmtid)
        htitle = "FEMCH %d : PMT POSID %d;max amp;area" % ( readch, pmtid )
        hists[ pmtid ] = TH2D( hname, htitle, 50, 0, 50, 50, 0, 500 )
        hists[ pmtid ].GetXaxis().SetLabelSize(0.08)
        hists[ pmtid ].GetYaxis().SetLabelSize(0.08)
        print "Plotting ",htitle.split(";")[0]
        outtree.Draw("charge:maxamp>>%s"%(hname),"opchannel==%d && maxamp>6.0"%(readch),"COLZ")
        cp.Update()
        ipanel += 1
    cp.SaveAs("figs/wf04/panel%d.pdf"%(p+1))
    canvs.append( cp )

raw_input()
