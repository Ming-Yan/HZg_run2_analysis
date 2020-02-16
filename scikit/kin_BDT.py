import random

import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import argparse

from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score

from root_numpy import root2array, rec2array

#from BDTplot import signal_background,correlations
from BDTplot import *

# transform 
branch_names = """lepEta1, lepEta2, phoEta,phoMVA,phoR9, ZgPTt,mllgptdmllg,Phi,cosTheta,costheta""".split(",")
branch_names = [c.strip() for c in branch_names]
branch_names = (b.replace(" ", "_") for b in branch_names)
branch_names = list(b.replace("-", "_") for b in branch_names)

ggF        = root2array("MVAfiles/mc_MVA_new_HZg_ggF_125GeV.root",
                                                "tMVA",
                                                branch_names)
ggF        = rec2array(ggF)
ggFwei     = root2array("MVAfiles/mc_MVA_new_HZg_ggF_125GeV.root",
                                                "tMVA",
                                                "mcwei")

VBF	   = root2array("MVAfiles/mc_MVA_new_HZg_VBF_125GeV.root",
                        "tMVA",
                        branch_names)
VBF        = rec2array(VBF)
VBFwei     = root2array("MVAfiles/mc_MVA_new_HZg_VBF_125GeV.root",
                        "tMVA",
                        "mcwei")
ttH        = root2array("MVAfiles/mc_MVA_new_HZg_ttH_125GeV.root",
                        "tMVA",
                        branch_names)
ttH        = rec2array(ttH)
ttHwei     = root2array("MVAfiles/mc_MVA_new_HZg_ttH_125GeV.root",
                                                "tMVA",
                                                "mcwei")
ZH        = root2array("MVAfiles/mc_MVA_new_HZg_ZH_125GeV.root",
                       "tMVA",
                       branch_names)
ZH        = rec2array(ZH)
ZHwei     = root2array("MVAfiles/mc_MVA_new_HZg_ZH_125GeV.root",
                                                "tMVA",
                                                "mcwei")
WplusH        = root2array("MVAfiles/mc_MVA_new_HZg_WplusH_125GeV.root",
                                                "tMVA",
                                                branch_names)
WplusH        = rec2array(WplusH)
WplusHwei     = root2array("MVAfiles/mc_MVA_new_HZg_WplusH_125GeV.root",
                                                "tMVA",
                                                "mcwei")
WminusH        = root2array("MVAfiles/mc_MVA_new_HZg_WminusH_125GeV.root",
                                                "tMVA",
                                                branch_names)
WminusH        = rec2array(WminusH)
WminusHwei     = root2array("MVAfiles/mc_MVA_new_HZg_WminusH_125GeV.root",
                                                "tMVA",
                                                "mcwei")
DYjet = root2array("MVAfiles/mc_MVA_new_DYJetsToLL_m50_aMCatNLO.root",
                    "tMVA",
                    branch_names)
DYjet = rec2array(DYjet)
DYwei = root2array("MVAfiles/mc_MVA_new_DYJetsToLL_m50_aMCatNLO.root",
                      "tMVA",
                      "mcwei")
SMZg = root2array("MVAfiles/mc_MVA_new_Zg_aMCatNLO.root",
                    "tMVA",
                    branch_names)
SMZg = rec2array(SMZg)
Zgwei= root2array("MVAfiles/mc_MVA_new_Zg_aMCatNLO.root",
                  "tMVA",
                  "mcwei")
TT2L2Nu = root2array("MVAfiles/mc_MVA_new_TTTo2L2Nu_powheg.root",
                     "tMVA",
                     branch_names)
TT2L2Nu = rec2array(TT2L2Nu)
TTwei   = root2array("MVAfiles/mc_MVA_new_TTTo2L2Nu_powheg.root",
                     "tMVA",
                     "mcwei")
signal = np.concatenate((ggF,VBF,ttH,ZH,WplusH,WminusH))
bkg    = np.concatenate((DYjet,SMZg,TT2L2Nu))
sigwei = np.concatenate((ggFwei,VBFwei,ttHwei,ZHwei,WplusHwei,WminusHwei))
bkgwei = np.concatenate((DYwei,Zgwei,TTwei))
sigev = sum(range(len(sigwei)))
bkgev = sum(range(len(bkgwei)))
sigwei = [x*1000000/sigev for x in sigwei]
bkgwei = [x*1000000/bkgev for x in bkgwei]

# for sklearn data is usually organised
# into one 2D array of shape (n_samples x n_features)
# containing all the data and one array of categories
# of length n_samples
X = np.concatenate((signal,bkg))
y = np.concatenate((np.ones(signal.shape[0]), np.zeros(bkg.shape[0])))


#df = pd.DataFrame(np.hstack((X, y.reshape(y.shape[0], -1))),columns=branch_names)
weight = np.concatenate((sigwei,bkgwei))
#np.concatenate((ggFwei,VBFwei,ttHwei,ZHwei,WplusHwei,WminusHwei,DYwei,Zgwei,TTwei))

#print weight
from sklearn.cross_validation import train_test_split

X_dev,X_eval, wei_dev, wei_eval,y_dev,y_eval = train_test_split(X, weight, y, test_size=0.5, random_state=42)
X_train,X_test, wei_train, wei_test,y_train,y_test = train_test_split(X_dev, wei_dev,y_dev,test_size=0.5, random_state=492)

from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score

dt = DecisionTreeClassifier(max_depth=3,min_samples_leaf=5)
bdt = AdaBoostClassifier(dt,  algorithm='SAMME', n_estimators=200, learning_rate=1)
bdt.fit(X_train, y_train, wei_train)
print 'training done!!!'
##################################################
#roccurve(bdt,X_test,y_test)
#fig1 = plt.figure(1)
#fig1.savefig('roc.png')

compare_train_test(bdt, X_train, y_train, X_test, y_test)
plt.show()
#fig2 = plt.figure(1)
#fig2.savefig('overtraining.png')


from sklearn import cross_validation
from sklearn.ensemble import GradientBoostingClassifier


gbt = GradientBoostingClassifier(n_estimators=200,
                                 max_depth=1,
                                 subsample=0.5,
                                 max_features=0.5,
                                 learning_rate=0.02)

scores = cross_validation.cross_val_score(gbt,
                                          X_dev, y_dev,
                                          scoring="roc_auc",
                                          n_jobs=6,
                                          cv=3)
print "Accuracy: %0.5f (+/- %0.5f)"%(scores.mean(), scores.std())




clfs = []
params = ((1.,1), (1.,4),(1.,8),(0.2,1), (0.2,4),(0.2,8))
for learn,depth in params:
    gbt_clf = GradientBoostingClassifier(max_depth=depth,
                                         learning_rate=learn,
                                         n_estimators=200)
    gbt_clf.fit(X_train, y_train,wei_train)
    clfs.append(gbt_clf)
validation_curve(clfs, (X_train,y_train),  (X_test,y_test))
fig3 = plt.figure(3)
fig3.savefig('crossvalid_curve.png')

simpleton = GradientBoostingClassifier(max_depth=1,
                                       learning_rate=0.1,
                                       n_estimators=50)
classifiers = [simpleton, clfs[0], clfs[1], clfs[3]]

fig, axes = plt.subplots(nrows=len(classifiers), sharex=True)

for clf, ax in zip(classifiers, axes):
    plot_learning_curve(clf,
                        "Learning curves",
                        X_dev, y_dev,wei_dev,
                        scoring='roc_auc',
                        n_jobs=7, cv=4,
                        ax=ax, xlabel=False)

axes[0].legend(loc="best")
axes[-1].set_xlabel("Training examples")

fig4 = plt.figure(4)
fig4.savefig('learningcurve.png')
            
