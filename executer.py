import os, sys, argparse
import ROOT as r


macpath = "temp_macs"
if not os.path.isdir(macpath):
    os.system("mkdir -p " + macpath)

outpath = "temp_rootFiles"
if not os.path.isdir(outpath):
    os.system("mkdir -p " + outpath)

#----Mac template----
mac_template = "/yourApp/det/setTargetMaterial {material} \n" + "/yourApp/det/setTargetThickness {thickness} um \n" + "/gun/particle {particle} \n" + "/gun/energy {energy} MeV \n" + "/run/initialize \n" + "/run/beamOn {N_events}\n"

#----Simulation parameters----- (Place default values a the first position in the list)
list_material = ["G4_Si", "G4_Au", "G4_Pb", "G4_Os", "G4_Cu"]
list_thickness = ["5.6", "10", "20", "30", "50"]
#list_thickness = ["500000","100000","1000000"]
list_gunParticle = ["e-","proton","gamma", "neutron"]
list_ParticleEnergy = ["100","1000","0.01","0.1","0.012", "0.05"]
N_events = "100000"
execute_mat = True
execute_thick = True
execute_part = True
execute_energ = True

if execute_mat:
  for material in list_material:
    rootFileName = "/Histograms_" + material + "_" + list_thickness[0] + "_" + list_gunParticle[0] + "_" + list_ParticleEnergy[0] + ".root"
    macFileName = "/Run_" + material + "_" + list_thickness[0] + "_" + list_gunParticle[0] + "_" + list_ParticleEnergy[0] + ".mac"
    macFile = open(macpath + macFileName,"w")
    macFile.write(mac_template.format(material = material, thickness = list_thickness[0], particle = list_gunParticle[0], energy = list_ParticleEnergy[0], N_events = N_events))
    macFile.close()
    os.system("./build/main ./" + macpath + macFileName)
    if not os.path.isdir(outpath + "/MaterialVariation"):
      os.system("mkdir -p " + outpath + "/MaterialVariation")
    os.system("mv ./Histograms.root ./" + outpath  + "/MaterialVariation" + rootFileName)
    os.system("rm ./" + macpath + "/*")

if execute_thick:  
  for thickness in list_thickness:
    rootFileName = "/Histograms_" + list_material[0] + "_" + thickness + "_" + list_gunParticle[0] + "_" + list_ParticleEnergy[0] + ".root"
    macFileName = "/Run_" + list_material[0] + "_" + thickness + "_" + list_gunParticle[0] + "_" + list_ParticleEnergy[0] + ".mac"
    macFile = open(macpath + macFileName,"w")
    macFile.write(mac_template.format(material = list_material[0], thickness = thickness, particle = list_gunParticle[0], energy = list_ParticleEnergy[0], N_events = N_events))
    macFile.close()
    os.system("./build/main ./" + macpath + macFileName)
    if not os.path.isdir(outpath + "/ThicknessVariation"):
      os.system("mkdir -p " + outpath + "/ThicknessVariation")
    os.system("mv ./Histograms.root ./" + outpath + "/ThicknessVariation" + rootFileName)
    os.system("rm ./" + macpath + "/*")

if execute_part:
  for gunParticle in list_gunParticle:
    rootFileName = "/Histograms_" + list_material[0] + "_" + list_thickness[0] + "_" + gunParticle + "_" + list_ParticleEnergy[0] + ".root"
    macFileName = "/Run_" + list_material[0] + "_" + list_thickness[0] + "_" + gunParticle + "_" + list_ParticleEnergy[0] + ".mac"
    macFile = open(macpath + macFileName,"w")
    macFile.write(mac_template.format(material = list_material[0], thickness = list_thickness[0], particle = gunParticle, energy = list_ParticleEnergy[0], N_events = N_events))
    macFile.close()
    os.system("./build/main ./" + macpath + macFileName)
    if not os.path.isdir(outpath + "/ParticleVariation"):
      os.system("mkdir -p " + outpath + "/ParticleVariation")
    os.system("mv ./Histograms.root ./" + outpath + "/ParticleVariation" + rootFileName)
    os.system("rm ./" + macpath + "/*")

if execute_energ:
  for ParticleEnergy in list_ParticleEnergy:
    rootFileName = "/Histograms_" + list_material[0] + "_" + list_thickness[0] + "_" + list_gunParticle[0] + "_" + ParticleEnergy + ".root"
    macFileName = "/Run_" + list_material[0] + "_" + list_thickness[0] + "_" + list_gunParticle[0] + "_" + ParticleEnergy + ".mac"
    macFile = open(macpath + macFileName,"w")
    macFile.write(mac_template.format(material = list_material[0], thickness = list_thickness[0], particle = list_gunParticle[0], energy = ParticleEnergy, N_events = N_events))
    macFile.close()
    os.system("./build/main ./" + macpath + macFileName)
    if not os.path.isdir(outpath + "/EnergyVariation"):
      os.system("mkdir -p " + outpath + "/EnergyVariation")
    os.system("mv ./Histograms.root ./" + outpath + "/EnergyVariation" + rootFileName)
    os.system("rm ./" + macpath + "/*")