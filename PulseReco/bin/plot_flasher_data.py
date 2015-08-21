import os,sys
from pmt_chmap import getPMTID, getChannel
from ROOT import *

gStyle.SetOptStat(0)
gStyle.SetPadLeftMargin(0.15)
gStyle.SetPadBottomMargin(0.20)
gStyle.SetPadTopMargin(0.15)

gStyle.SetTitleX(0.5) 
gStyle.SetTitleY(1.0) 
gStyle.SetTitleW(0.9) 
gStyle.SetTitleH(0.13)


#finput = TFile( "results_20150801_wf_run_005.root", "OPEN" )
#finput = TFile( " ~/working/uboone/data/FlasherData_080115/processed//results_20150801_wf_run_005.root", "OPEN" )
#folder = "figs/20150801_wf005/"
#finput = TFile( " ~/working/uboone/data/FlasherData_080515/results_20150806_wf_run_001.root", "OPEN" )
finput = TFile( " ~/working/uboone/data/FlasherData_080715/processed/results_20150807_wf_run_003.root", "OPEN" )
folder = "figs/20150807_wf003/"
os.system("mkdir -p "+folder)

outtree = finput.Get("outtree")

out = TFile("plotout.root", "RECREATE")

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
hists_zoomout = {}
savehists = []
c2 = TCanvas("c2","",800,600)
c2.Draw()

c3 = TCanvas("c3","",800,600)
c3.Draw()
for p in xrange(0,5):
    panellist = panels[p]
    cp = TCanvas("canv%d"%(p),"Panel %d"%(p),1300,1400)
    cp.Divide(4,5)
    cp.Draw()

    cp_zoomout = TCanvas("canv%d_zoomout"%(p),"Zoom out: Panel %d"%(p),1800,2000)
    cp_zoomout.Divide(4,5)
    cp_zoomout.Draw()

    ipanel = 1
    for pmtid in panellist:
        readch = getChannel(pmtid)
        padid = canvpos[pmtid][1]*4 + canvpos[pmtid][0] + 1
        print "canvas pos: ",canvpos[pmtid], " padid=",padid
        print "panel id: ",ipanel
        cp.cd( padid )
        hname = "h2_ch%d_pmt%d"%(readch,pmtid)
        #htitle = "FEMCH %d : PMT POSID %d;max amp;area" % ( readch, pmtid )
        htitle = "PMT P%02d: spe shape;amp. (ADC counts);area (counts*samples)" % ( pmtid )
        hists[ pmtid ] = TH2D( hname, htitle, 50, 0, 50, 50, 0, 500 )
        hists[ pmtid ].GetXaxis().SetLabelSize(0.09)
        hists[ pmtid ].GetYaxis().SetLabelSize(0.09)
        hists[ pmtid ].GetXaxis().SetTitleSize(0.10)
        hists[ pmtid ].GetYaxis().SetTitleSize(0.09)
        hists[ pmtid ].GetXaxis().SetTitleOffset(0.8)
        hists[ pmtid ].GetYaxis().SetTitleOffset(0.85)
        hists[ pmtid ].GetXaxis().SetNdivisions(505)
        hists[ pmtid ].GetYaxis().SetNdivisions(505)

        print "Plotting ",htitle.split(";")[0]
        outtree.Draw("charge:maxamp>>%s"%(hname),"opchannel==%d && maxamp>7.0 && charge>0.0"%(readch),"COLZ")
        #outtree.Draw("charge:maxamp>>%s"%(hname),"opchannel==%d"%(readch),"COLZ")
        #cp.cd(padid).SetLogz(1)
        cp.Update()

        cp_zoomout.cd( padid )
        hname_zoomout = "h2_ch%d_pmt%d_zoomout"%(readch,pmtid)
        #htitle = "FEMCH %d : PMT POSID %d;max amp;area" % ( readch, pmtid )
        htitle = "PMT P%02d: spe;amp (ADC counts);area (ADC counts*samples)" % ( pmtid )
        hists_zoomout[ pmtid ] = TH2D( hname_zoomout, htitle, 50, 0, 500, 50, 0, 5000 )
        hists_zoomout[ pmtid ].GetXaxis().SetLabelSize(0.08)
        hists_zoomout[ pmtid ].GetYaxis().SetLabelSize(0.08)
        print "Plotting ",htitle.split(";")[0]
        outtree.Draw("charge:maxamp>>%s"%(hname_zoomout),"opchannel==%d && maxamp>7.0 && charge>20.0"%(readch),"COLZ")
        cp_zoomout.cd( padid ).SetLogz(1)
        cp_zoomout.Update()

        # single plot
        c2.cd()
        hsingle = hists[ pmtid ].Clone( hname+"_single" )
        hsingle.GetXaxis().SetLabelSize(0.08)
        hsingle.GetYaxis().SetLabelSize(0.07)
        hsingle.GetXaxis().SetTitleSize(0.09)
        hsingle.GetYaxis().SetTitleSize(0.07)
        hsingle.GetXaxis().SetTitleOffset(1.0)
        hsingle.GetYaxis().SetTitleOffset(1.1)
        hsingle.GetXaxis().SetNdivisions(505)
        hsingle.GetYaxis().SetNdivisions(505)
        hsingle.Draw("COLZ")
        c2.SetLogy(0)
        c2.Update()
        #raw_input()
        c2.SaveAs(folder+"/%s.png"%(hname))
        c2.SaveAs(folder+"/%s.pdf"%(hname))
        c2.SaveAs(folder+"/%s.eps"%(hname))

        # 1D Amplitude
        hxname = "h2_ch%d_pmt%d"%(readch,pmtid)+"_px"
        px = TH1D( hxname,";amplitude (ADC counts);events", 50, 0, 50 )
        px.GetXaxis().SetLabelSize(0.08)
        px.GetYaxis().SetLabelSize(0.07)
        px.GetXaxis().SetTitleSize(0.09)
        px.GetYaxis().SetTitleSize(0.07)
        px.GetXaxis().SetTitleOffset(1.0)
        px.GetYaxis().SetTitleOffset(1.1)
        px.GetXaxis().SetNdivisions(505)
        px.GetYaxis().SetNdivisions(505)
        outtree.Draw("maxamp>>%s"%(hxname),"opchannel==%d && charge>0.0"%(readch),"COLZ")
        savehists.append( px )
        px.Draw()
        c2.SetLogy(1)
        c2.Update()
        c2.SaveAs(folder+"/hamp_ch%d_pmt%d.png"%(readch,pmtid))
        c2.SetLogy(0)
        hlxname = "h2_ch%d_pmt%d_"%(readch,pmtid)+"_linear_px"
        lpx = TH1D( hlxname,";amplitude (ADC counts);events", 50, 0, 50 )
        lpx.GetXaxis().SetLabelSize(0.08)
        lpx.GetYaxis().SetLabelSize(0.07)
        lpx.GetXaxis().SetTitleSize(0.09)
        lpx.GetYaxis().SetTitleSize(0.07)
        lpx.GetXaxis().SetTitleOffset(1.0)
        lpx.GetYaxis().SetTitleOffset(1.1)
        lpx.GetXaxis().SetNdivisions(505)
        lpx.GetYaxis().SetNdivisions(505)
        
        outtree.Draw("maxamp>>%s"%(hlxname),"opchannel==%d && maxamp>6.0 && charge>0.0"%(readch),"COLZ")
        savehists.append( lpx )
        c2.SaveAs(folder+"/hamp_ch%d_pmt%d_linear.png"%(readch,pmtid))
        raw_input()
        
        ipanel += 1
    for ext in ["pdf","eps","png"]:
        cp.SaveAs(folder+"/panel%d.%s"%(p+1,ext))
    cp_zoomout.SaveAs(folder+"/zoomout_panel%d.pdf"%(p+1))
    canvs.append( cp )
    canvs.append( cp_zoomout )
    break

out.Write()
raw_input()
