import os, sys, argparse
import ROOT as r
r.PyConfig.IgnoreCommandLineOptions = True
r.gROOT.SetBatch(True)
import copy


#-----Histograms------
TotalEnergy = r.TH1F("Energy","Energy",70,0,0.02)
TrackLenght = r.TH1F("Track","Track",40,0,0.02)
histos = [TotalEnergy, TrackLenght]
#-----Histograms------

#----SaveDir----------
outpath = "./plots"
if not os.path.isdir(outpath):
    os.system("mkdir -p " + outpath)
#----SaveDir----------

#-----Opening file----
rootFile = r.TFile("build/Histograms.root")
#rootFile.cd("ntuple")
Tree = rootFile.Get("ntuple/Tuple")
#-----Opening file----

#-----Looping events--
nEvents = Tree.GetEntries()
for events in Tree:
    TotalEnergy.Fill(events.EnergyDep)
    TrackLenght.Fill(events.TrackLength)
#-----Looping events--

#-----Drawing---------
for histograms in histos:
    c1 = r.TCanvas("canvas_" + histograms.GetTitle(), "canvas_" + histograms.GetTitle(), 600, 600)
    histograms.Draw()
    c1.Print(outpath + "/" + histograms.GetTitle() + ".png","png")
    c1.Print(outpath + "/" + histograms.GetTitle() + ".pdf","pdf")
    c1.Close()
#-----Drawing---------




rootFile.Close()