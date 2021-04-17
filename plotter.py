import os, sys, re
import ROOT as r
r.PyConfig.IgnoreCommandLineOptions = True
r.gROOT.SetBatch(True)
import copy

def doSpam(text,x1,y1,x2,y2,align=12,fill=False,textSize=0.033):
    cmsprel = r.TPaveText(x1,y1,x2,y2,"NDC NB");
    cmsprel.SetTextSize(textSize);
    cmsprel.SetFillColor(0);
    cmsprel.SetFillStyle(1001 if fill else 0);
    cmsprel.SetLineStyle(2);
    cmsprel.SetLineColor(0);
    cmsprel.SetTextAlign(align);
    cmsprel.SetTextFont(42);
    cmsprel.AddText(text);
    cmsprel.Draw("same");
    return cmsprel


colours = [r.kBlue+0, r.kRed+0, r.kGreen+1, r.kCyan+1, r.kOrange+7, r.kGreen+4]
#----SaveDir----------
outpath = "./plots"
if not os.path.isdir(outpath):
    os.system("mkdir -p " + outpath)


#-----Opening file----
path = "./temp_rootFiles/"
directories = os.listdir(path)
for directory in directories:
  histos_E = []
  histos_Tr = []
  parameter = []
  Mat = "Si"
  Thick = "5.6 #mum"
  En = "100 MeV"
  Part = "e^{-}"
  for rootFileName in os.listdir(path + directory):
    rootFile = r.TFile(path + directory + "/" + rootFileName)
    #Parameters
    material = re.search('G4_(.+?)_', rootFileName).group(1)
    thickness = re.search(material + '_(.+?)_', rootFileName).group(1)
    particle = re.search(thickness + '_(.+?)_', rootFileName).group(1)
    energy = re.search(particle + '_(.+?).root', rootFileName).group(1)
    trackhistoLimit = 16
    if directory == "MaterialVariation":
      parameter.append(material)
      legendEntry = "Material {word}"
      Mat = "Var."
    if directory == "ThicknessVariation":
      parameter.append(thickness)
      legendEntry = "Thickness {word} #mum" 
      trackhistoLimit = 55
      Thick = "Var."
    if directory == "ParticleVariation":
      parameter.append(particle)
      legendEntry = "Particle {word}"
      Part = ""
    if directory == "EnergyVariation":
      parameter.append(energy)
      legendEntry = "Energy {word} MeV"
      En = "Var."
    #Histograms and filling
    Tree = rootFile.Get("ntuple/Tuple")
    TotalEnergy = r.TH1F("Energy" + material + thickness + particle + energy,"Energy" + material + thickness + particle + energy,130,0,20)
    TotalEnergy.SetDirectory(0)
    TrackLenght = r.TH1F("Track" + material + thickness + particle + energy,"Track" + material + thickness + particle + energy,70,0,trackhistoLimit)
    TrackLenght.SetDirectory(0)
    for events in Tree:
      TotalEnergy.Fill(events.EnergyDep*1000) 
      TrackLenght.Fill(events.TrackLength*1000)
    histos_E.append(TotalEnergy)
    histos_Tr.append(TrackLenght)


#  if directory == "MaterialVariation":
#    parameter = ["Si #rho = 2.33 g/cm^{3}", "Cu #rho = 8.96 g/cm^{3}", "Pb #rho = 11.35 g/cm^{3}", "Au #rho = 19.32 g/cm^{3}", "Os #rho = 22.57 g/cm^{3}"]
  cE = r.TCanvas("canvasE_" + directory, "canvasE_" + directory, 600, 600)
  cE.SetLeftMargin(0.15)
  cE.SetRightMargin(0.05)
  #-----Legend----------
  leg = r.TLegend(0.6, 0.75, 0.9, 0.89)
  leg.SetTextFont(42)
  leg.SetTextSize(0.025)
  leg.SetBorderSize(0)
  leg.SetFillColor(10)
  leg.SetFillStyle(0)
  i = 0
  for EnergyHistos in histos_E:
    EnergyHistos.SetTitle("")
    EnergyHistos.GetXaxis().SetTitle("Energy deposited (keV)")
    EnergyHistos.SetLineColor(colours[i])
    EnergyHistos.SetMarkerSize(0)
    EnergyHistos.Draw("Same")
    EnergyHistos.GetYaxis().SetTitle("Events")
    EnergyHistos.GetYaxis().SetTitleOffset(2.1)
    EnergyHistos.GetXaxis().SetTitleOffset(1.4)
    EnergyHistos.SetStats(0)
    leg.AddEntry(EnergyHistos, legendEntry.format(word = parameter[i]), "l")
    i += 1
  leg.Draw("same")
  texto = "Mat: {Mat}    Thickness: {Thick}    E: {En}    {Part}".format(Mat = Mat, Thick = Thick, En = En, Part = Part)
  spamText = doSpam(texto,0.23,0.91,0.9,0.93)
  cE.Print(outpath + "/TotalEnergy_" + directory + ".png","png")
  cE.Print(outpath + "/TotalEnergy_" + directory + ".pdf","pdf")
  cE.Close()
  
  cTr = r.TCanvas("canvasTr_" + directory, "canvasTr_" + directory, 600, 600)
  cTr.SetLeftMargin(0.15)
  cTr.SetRightMargin(0.05)
  #-----Legend----------
  i = 0
  for TrackHistos in histos_Tr:
    TrackHistos.SetTitle("")
    TrackHistos.GetXaxis().SetTitle("Total track lenght (#mum)") 
    TrackHistos.SetLineColor(colours[i])
    TrackHistos.SetMarkerSize(0)
    TrackHistos.Draw("Same")
    TrackHistos.GetYaxis().SetTitle("Events")
    TrackHistos.GetYaxis().SetTitleOffset(2.1)
    TrackHistos.GetXaxis().SetTitleOffset(1.4)
    TrackHistos.SetStats(0)
    i += 1
  leg.Draw("same")
  spamText = doSpam(texto,0.23,0.91,0.9,0.93)
  cTr.Print(outpath + "/TotalTrack_" + directory + ".png","png")
  cTr.Print(outpath + "/TotalTrack_" + directory + ".pdf","pdf")
  cTr.Close()
  





