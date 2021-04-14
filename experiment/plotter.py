import os, sys, argparse
import ROOT as r
r.PyConfig.IgnoreCommandLineOptions = True
r.gROOT.SetBatch(True)
import copy
from numpy import trapz

#-----Histograms------
TotalEnergy = r.TH1F("Energy","Energy",130,0,6)
TotalEnergy.GetXaxis().SetTitle("Energy deposited (keV)")
#-----Histograms------

#-----Data Graph------
meroliData = r.TGraph()
#-----Data Graph------

#----SaveDir----------
outpath = "./plots_ExpMeroli"
if not os.path.isdir(outpath):
    os.system("mkdir -p " + outpath)
#----SaveDir----------

#-----Opening file----
rootFile = r.TFile("build/Histograms.root")
#rootFile.cd("ntuple")
Tree = rootFile.Get("ntuple/Tuple")
#-----Opening file----

#-----Opening Meroli file----
File = open("experiment/exp_Meroli_100MeV_electron_5p6um_Si.dat","r")
data = []
for line in File:
  item = line.rstrip()
  if not item.startswith("#"):
    data.append(item.split())
meroliData.Set(len(data))

#-----Opening Meroli file----

#-----Setting data points----
i = 0
x = []
y = []
for datapoint in data:
  meroliData.SetPoint(i,float(datapoint[0]),float(datapoint[1]))
  x.append(float(datapoint[0]))
  y.append(float(datapoint[1]))
  i += 1

meroliIntegral = trapz(y,x)
#-----Setting data points----

#-----Looping events--
nEvents = Tree.GetEntries()
for events in Tree:
    TotalEnergy.Fill(events.EnergyDep*1000)
integralSimulation = TotalEnergy.Integral()
#-----Looping events--

#-----Legend----------
leg = r.TLegend(0.65, 0.78, 0.9, 0.89)
leg.SetTextFont(42)
leg.SetTextSize(0.025)
leg.SetBorderSize(0)
leg.SetFillColor(10)
leg.SetFillStyle(0)
#-----Legend----------

#-----Drawing---------
c1 = r.TCanvas("canvas_" + TotalEnergy.GetTitle(), "canvas_" + TotalEnergy.GetTitle(), 600, 600)
c1.SetLeftMargin(0.15)
TotalEnergy.Scale(meroliIntegral/integralSimulation, "WIDTH")
TotalEnergy.GetYaxis().SetRangeUser(0,5000)
TotalEnergy.SetTitle("")
c1.SetTitle("")
TotalEnergy.GetYaxis().SetTitle("a.u")
TotalEnergy.GetYaxis().SetTitleOffset(2.1)
TotalEnergy.SetStats(0)
TotalEnergy.Draw("hist")
meroliData.Draw("same")
leg.AddEntry(TotalEnergy, "Geant4 Simulation")
leg.AddEntry(meroliData, "Meroli Data","l")
leg.Draw("same")
c1.Print(outpath + "/" + "Energy" + ".png","png")
c1.Print(outpath + "/" + "Energy" + ".pdf","pdf")
c1.Close()
#-----Drawing---------




rootFile.Close()