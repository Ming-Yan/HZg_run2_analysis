#!/usr/bin/env python

from ROOT import *
import os,sys,json
import numpy as np
gROOT.SetBatch()


import argparse
parser =  argparse.ArgumentParser(description='Limit Tree maker')
parser.add_argument('-b','--blind', dest="blind", action="store_true", default=False,
                    help="Do not try to get observed limits.")
parser.add_argument('-v','--verb', dest="verb", action="store_true", default=False,
                    help="Do more verbosity printout.")
parser.add_argument('-d','--rdir', dest="rdir", type=str, default='hzg-shilpi',
                    help="Path to all higgsCombine root trees")
opt = parser.parse_args()

if not opt.verb:
  gROOT.ProcessLine("gErrorIgnoreLevel = 1001;")

import TdrStyle as tdr
import CMS_lumi

ext = ['.png','.pdf']

  
def getValuesFromFile(fname):
  f = TFile.Open(fname)
  if not f:
    print "This file does not exist.. Just skip this point!"
    return None

  tree = f.Get("limit")
  if tree==None:
    print "\t -->> there is a problem with this limits:", fname
    print "There is no limit tree inside the root file"
    return None
  
  res = []
  for i,l in enumerate(tree):
    # print i, l, l.limit
    if i==0: res.append(float(l.limit))
    if i==1: res.append(float(l.limit))
    if i==2: res.append(float(l.limit))
    if i==3: res.append(float(l.limit))
    if i==4: res.append(float(l.limit))
    if i==5: res.append(float(l.limit))
        
  f.Close()
  return res


def limitVsM(nameTag, par, masses):

  if opt.verb:
    print 'Doing:', nameTag
  
  xAxis = []
  xErr  = []
  obs   = []
  expMean    = []
  exp1SigHi  = []
  exp1SigLow = []
  exp2SigHi  = []
  exp2SigLow = []
  theo = []


  for i,m in enumerate(masses):
    l = getValuesFromFile(opt.rdir+'/higgsCombine_'+nameTag+'.Asymptotic.mH%i.root'%m)
    if l==None:
      return
    if len(l)<4:
      print 'This is strange, the number of limits is not right'
      print m, l
      return
    
    exp2SigLow.append(l[0])
    exp1SigLow.append(l[1])
    expMean.append(l[2])
    exp1SigHi.append(l[3])
    exp2SigHi.append(l[4])
    if not opt.blind:
      try:
        obs.append(l[5])
      except:
        print "You probably only have blinded results, run with -b option"
        return

    xAxis.append(float(m))
    xErr.append(0.5)

    if opt.verb:
      print m, l
      

  zeros_Array = np.zeros(len(xAxis),dtype = float)
  xAxis_Array = np.array(xAxis)
  xErr_Array  = zeros_Array


  if not opt.blind:
    obs_Array = np.array(obs)
  else:
    obs_Array = zeros_Array


  exp_Array = np.array(expMean)
  exp2SigLowErr_Array = np.array([a-b for a,b in zip(expMean,exp2SigLow)])
  exp1SigLowErr_Array = np.array([a-b for a,b in zip(expMean,exp1SigLow)])
  exp1SigHiErr_Array  = np.array([b-a for a,b in zip(expMean,exp1SigHi)])
  exp2SigHiErr_Array  = np.array([b-a for a,b in zip(expMean,exp2SigHi)])

  mg = TMultiGraph()
  mg.SetTitle('')
  
  nPoints  = len(xAxis)
  expected = TGraphAsymmErrors(nPoints,xAxis_Array,exp_Array,zeros_Array,zeros_Array,zeros_Array,zeros_Array)
  oneSigma = TGraphAsymmErrors(nPoints,xAxis_Array,exp_Array,xErr_Array,xErr_Array,exp1SigLowErr_Array,exp1SigHiErr_Array)
  twoSigma = TGraphAsymmErrors(nPoints,xAxis_Array,exp_Array,xErr_Array,xErr_Array,exp2SigLowErr_Array,exp2SigHiErr_Array)
  observed = TGraphAsymmErrors(nPoints,xAxis_Array,obs_Array,zeros_Array,zeros_Array,zeros_Array,zeros_Array)


  oneSigma.SetFillColor(kGreen+1)
  twoSigma.SetFillColor(kYellow-4)

  expected.SetMarkerColor(kBlack)
  expected.SetLineColor(kBlack)
  expected.SetLineWidth(2)
  expected.SetLineStyle(2)
  
  observed.SetMarkerStyle(20)

  mg.Add(twoSigma, '')
  mg.Add(oneSigma, '')
  mg.Add(expected, '')

  if not opt.blind:
    mg.Add(observed)

  mg.Draw('AL3')
  mg.GetXaxis().SetTitle('m_{H} (GeV)')

  mg.SetMinimum(0)
  mg.SetMaximum(par["yAxisMax"])

  mg.GetXaxis().SetLimits(119.5, 130.5)

  mg.GetYaxis().SetTitle('95% CL limit on #sigma/#sigma_{SM}')

  # gPad.RedrawAxis()

  leg = TLegend(0.60,0.68,0.85,0.91)
  #
  leg.SetTextFont(42)
  leg.SetTextSize(0.04)
  leg.SetFillStyle(0)
  leg.SetBorderSize(0)
  
  leg.AddEntry(observed,"Observed", "p")
  leg.AddEntry(expected,"Expected", "l")
  leg.AddEntry(oneSigma,"Expected #pm 1#sigma", "f")
  leg.AddEntry(twoSigma,"Expected #pm 2#sigma", "f")

  leg.Draw()
  CMS_lumi.CMS_lumi(c1, par["cmslumi"]["iPeriod"], par["cmslumi"]["iPos"])


  lat = TLatex()
  lat.SetNDC()
  lat.SetTextColor(kBlack)
  lat.SetTextSize(0.04)
  lat.DrawLatex(0.05,0.02, nameTag)
  #lat.DrawLatex(0.20,0.75, 'H #rightarrow #gamma*#gamma #rightarrow ll#gamma')
  #lat.SetTextSize(0.02)
  #lat.DrawLatex(0.20,0.70, '13 TeV: #mu#mu#gamma, all categ.')
  #lat.DrawLatex(0.20,0.65, ' 8 TeV: #mu#mu#gamma and ee#gamma, all categ.')
   
  for e in ext:
    c1.SaveAs(opt.rdir+'/LimitPlot_'+nameTag+e)
    


def plot125(tags, doHZG=False, doDalitz=False, do8TeV=False):

  if not doHZG and not doDalitz:
    print 'There is nothing to do'
    return

  # First let's define the order in which we add the point on the plots
  # ( From top to bottom)
  HZGOrder = [
    #'hzg_eeg_mmg_cat1234510_13TeV', # HZG Combined
    #'hzg_eeg_mmg_cat12345678910_13TeV', # HZG Combined
    #'hzg_mmg_cat12345_13TeV',
    #'hzg_mmg_cat10_13TeV', 'hzg_mmg_cat5_13TeV', 'hzg_mmg_cat4_13TeV', 'hzg_mmg_cat3_13TeV', 'hzg_mmg_cat2_13TeV', 'hzg_mmg_cat1_13TeV',
    #'hzg_eeg_cat12345_13TeV',
    #'hzg_eeg_cat10_13TeV',
    #'hzg_eeg_cat5_13TeV', 'hzg_eeg_cat4_13TeV', 'hzg_eeg_cat3_13TeV', 'hzg_eeg_cat2_13TeV', 'hzg_eeg_cat1_13TeV',
    'hzg_eeg_mmg_cat6789_13TeV',
  ]

  DalitzOrder = [
    'Dalitz_13TeV', # Combined Dalitz
    'hmmg_13TeV_HR9','hmmg_13TeV_LR9',
    'hmmg_13TeV_VBF', 'hmmg_13TeV_EE', 
    ]


  allCats = []
  
  if doDalitz:
    allCats.extend(DalitzOrder)
    combName='Dalitz_13TeV'
    if not doHZG:
      xMax = 32
  if doHZG:
    allCats.extend(HZGOrder)
    xMax = 70
    combName='HZG_13TeV'
    
  if doHZG and doDalitz:
    allCats.insert(0,'HZG_Dalitz_13TeV')
    combName='HZGandDalitz_13TeV'

  iPeriod = 4
  if do8TeV:
    # Only show few results when combined with 8 TeV
    allCats = []
    if doDalitz:
      xMax = 22
      #allCats.extend(['Dalitz_8and13TeV','Dalitz_8TeV', 'Dalitz_13TeV'])
      allCats.extend(['Dalitz_8and13TeV', 'Dalitz_13TeV','Dalitz_8TeV'])
      if not doHZG:
        allCats.extend(DalitzOrder[1:])
        combName='Dalitz_8and13TeV'
        iPeriod = 5
    if doHZG:
      iPeriod = 7
      #allCats.extend(['HZG_8and13TeV','HZG_7and8TeV', 'hzg_eeg_mmg_cat12345678910_13TeV'])
      allCats.extend(['HZG_8and13TeV', 'hzg_eeg_mmg_cat12345678910_13TeV','HZG_7and8TeV' ])
      if doDalitz:
        combName='HZGandDalitz_7and8and13TeV'
        allCats.insert(0,'HZG_Dalitz_8and13TeV')
      else:
        combName='HZG_7and8and13TeV'
        allCats.extend(HZGOrder[1:])
      
  yAxis = []
  obs   = []
  expMean    = []
  exp1SigHi  = []
  exp1SigLow = []
  exp2SigHi  = []
  exp2SigLow = []
  
  for i,o in enumerate(allCats):
    l = getValuesFromFile(opt.rdir+'/higgsCombine_'+o+'.Asymptotic.mH125.root')
    if l==None:
      print 'Output result from combine not found in the root file, desole... Tag:', o 

      l = [100,100,100,100,100]

    if opt.verb:
      print tags[o]
    
    exp2SigLow.append(l[0])
    exp1SigLow.append(l[1])
    expMean.append(l[2])
    exp1SigHi.append(l[3])
    exp2SigHi.append(l[4])
    
    yAxis.append(float(i))


  
  zeros_Array = np.zeros(len(yAxis),dtype = float)
  yAxis_Array = np.array(yAxis)
  yErr_Array  = np.empty(len(yAxis), dtype = float)
  yErr_Array.fill(0.1)
  
  if not opt.blind:
    obs_Array = np.array(obs)
  else:
    obs_Array = zeros_Array

  exp_Array = np.array(expMean)
  exp2SigLowErr_Array = np.array([a-b for a,b in zip(expMean,exp2SigLow)])
  exp1SigLowErr_Array = np.array([a-b for a,b in zip(expMean,exp1SigLow)])
  exp1SigHiErr_Array  = np.array([b-a for a,b in zip(expMean,exp1SigHi)])
  exp2SigHiErr_Array  = np.array([b-a for a,b in zip(expMean,exp2SigHi)])

  mg = TMultiGraph()
  mg.SetTitle('')

  nPoints  = len(yAxis)
  expected = TGraphAsymmErrors(nPoints,exp_Array,yAxis_Array,zeros_Array,zeros_Array,zeros_Array,zeros_Array)
  oneSigma = TGraphAsymmErrors(nPoints,exp_Array,yAxis_Array,exp1SigLowErr_Array,exp1SigHiErr_Array,yErr_Array,yErr_Array)
  twoSigma = TGraphAsymmErrors(nPoints,exp_Array,yAxis_Array,exp2SigLowErr_Array,exp2SigHiErr_Array,yErr_Array,yErr_Array)
  observed = TGraphAsymmErrors(nPoints,obs_Array,yAxis_Array,zeros_Array,zeros_Array,zeros_Array,zeros_Array)


  oneSigma.SetFillColor(kGreen+1)
  twoSigma.SetFillColor(kYellow-4)

  expected.SetMarkerStyle(21)
  expected.SetMarkerColor(kBlue+2)
  expected.SetLineColor(kBlack)
  expected.SetLineWidth(2)
  expected.SetLineStyle(2)

  observed.SetMarkerStyle(20)

  mg.Add(twoSigma, '2')
  mg.Add(oneSigma, '2')
  mg.Add(expected, 'P')

  if not opt.blind:
    mg.Add(observed)

  mg.Draw('AP')

  mg.SetMinimum(-1)
  #mg.SetMaximum(nPoints)
  mg.SetMaximum(nPoints+3)

  mg.GetYaxis().SetTickLength(0);
  mg.GetYaxis().SetLabelOffset(999);

  mg.GetXaxis().SetLimits(0, xMax)  
  mg.GetXaxis().SetTitle('95% CL upper limit on #sigma/#sigma_{SM}')

  # gPad.RedrawAxis()

  #leg = TLegend(0.70,0.50,0.87,0.65)
  leg = TLegend(0.70,0.25,0.87,0.40)
  leg.SetTextFont(42)
  leg.SetTextSize(0.03)
  leg.SetFillStyle(0)
  leg.SetBorderSize(0)

  leg.AddEntry(observed,"Observed", "p")
  leg.AddEntry(expected,"Expected", "p")
  leg.AddEntry(oneSigma,"#pm 1#sigma", "f")
  leg.AddEntry(twoSigma,"#pm 2#sigma", "f")

  leg.Draw()


  lat = TLatex()
  # Here we add the names of all categories  lat = TLatex()
  lat.SetTextColor(kBlack)
  lat.SetTextSize(0.025)
  lat.SetTextAlign(32)
  for i,o in enumerate(allCats):
    lat.DrawLatex(-0.05*xMax, i, tags[o]["label"])

  # Drow the line
  l1 = TLine(expMean[0],0,expMean[0],len(yAxis))
  l1.SetLineColor(kBlue)
  l1.SetLineWidth(2)
  l1.Draw()

  l2 = TLine(1,-1,1,len(yAxis))
  l2.SetLineColor(kRed+1)
  l2.SetLineWidth(1)
  l2.Draw()


  CMS_lumi.CMS_lumi(c1, iPeriod, 33)
      
  c1.SetLeftMargin(0.30)
  c1.SetRightMargin(0.04)
  c1.Modified()
  c1.Update()
  
  for e in ext:
    c1.SaveAs(opt.rdir+'/plots/LimitPlot_Combine_'+combName+e)    


if __name__ == "__main__":
  print "This is the __main__ part"

  tdr.setTDRStyle()

  masses = xrange(120,131)

  with open('tagParams.json', 'r') as fp:
    myTags = json.load(fp)

    if opt.verb:
      print myTags

    for tagName, par in myTags.iteritems():
      limitVsM(tagName, par, masses)

      
    plot125(myTags, doHZG=True)
    #plot125(myTags, doHZG=True, do8TeV=True)
    #plot125(myTags, doDalitz=True)
    #plot125(myTags, doDalitz=True, do8TeV=True)
    #plot125(myTags, doHZG=True, doDalitz=True)
    #plot125(myTags, doHZG=True, doDalitz=True, do8TeV=True)
    
  
