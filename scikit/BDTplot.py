import random

import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score
import pandas.core.common as com
from pandas.core.index import Index

from pandas.tools import plotting
from pandas.tools.plotting import scatter_matrix
from sklearn.metrics import roc_curve, auc
from sklearn.learning_curve import learning_curve

def signal_background(data1, data2, column=None, grid=True,
                      xlabelsize=None, xrot=None, ylabelsize=None,
                      yrot=None, ax=None, sharex=False,
                      sharey=False, figsize=None,
                      layout=None, bins=10, **kwds):
        """Draw histogram of the DataFrame's series comparing the distribution
    in `data1` to `data2`.
    
    data1: DataFrame
    data2: DataFrame
    column: string or sequence
        If passed, will be used to limit data to a subset of columns
    grid : boolean, default True
        Whether to show axis grid lines
    xlabelsize : int, default None
        If specified changes the x-axis label size
    xrot : float, default None
        rotation of x axis labels
    ylabelsize : int, default None
        If specified changes the y-axis label size
    yrot : float, default None
        rotation of y axis labels
    ax : matplotlib axes object, default None
    sharex : bool, if True, the X axis will be shared amongst all subplots.
    sharey : bool, if True, the Y axis will be shared amongst all subplots.
    figsize : tuple
        The size of the figure to create in inches by default
    layout: (optional) a tuple (rows, columns) for the layout of the histograms
    bins: integer, default 10
        Number of histogram bins to be used
    kwds : other plotting keyword arguments
        To be passed to hist function
    """
        if 'alpha' not in kwds:
                kwds['alpha'] = 0.5
        if column is not None:
                if not isinstance(column, (list, np.ndarray, Index)):
                        column = [column]
                        data1 = data1[column]
                        data2 = data2[column]
                        
                data1 = data1._get_numeric_data()
                data2 = data2._get_numeric_data()
                naxes = len(data1.columns)
                        
        
                fig, axes = plotting._subplots(naxes=naxes, ax=ax, squeeze=False,
                                        sharex=sharex,sharey=sharey,
                                        figsize=figsize,layout=layout)
                _axes = plotting._flatten(axes)
                for i, col in enumerate(com._try_sort(data1.columns)):
                        ax = _axes[i]
                        low = min(data1[col].min(), data2[col].min())
                        high = max(data1[col].max(), data2[col].max())
                        ax.hist(data1[col].dropna().values,
                        bins=bins, range=(low,high), **kwds)
                        ax.hist(data2[col].dropna().values,
                        bins=bins, range=(low,high), **kwds)
                        ax.set_title(col)
                        ax.grid(grid)

                plotting._set_ticks_props(axes, xlabelsize=xlabelsize, xrot=xrot,
                                          ylabelsize=ylabelsize, yrot=yrot)
                fig.subplots_adjust(wspace=0.3, hspace=0.7)
                
                return axes              

    # Plot signal and background distributions for some
    # variables
    # The first two arguments select what is "signal"
    # and what is "background". This means you can
    # use it for more general comparisons of two
    # subsets as well.


def correlations(data, **kwds):
        """
#Calculate pairwise correlation between features.
#        Extra arguments are passed on to DataFrame.corr()
        """
        # simply call df.corr() to get a table of
        # correlation values if you do not need
        # the fancy plotting

        corrmat = data.corr(**kwds)
        
        fig, ax1 = plt.subplots(ncols=1, figsize=(6,5))
        
        opts = {'cmap': plt.get_cmap("viridis"),
#                'text': (5,5,df.c)
                'vmin': -1, 'vmax': +1}
        heatmap1 = ax1.pcolor(corrmat, **opts)
        plt.colorbar(heatmap1, ax=ax1)
        
        ax1.set_title("Correlations")
        
        labels = corrmat.columns.values
        for ax in (ax1,):
                # shift location of ticks to center of the bins
                ax.set_xticks(np.arange(len(labels))+0.5, minor=False)
                ax.set_yticks(np.arange(len(labels))+0.5, minor=False)
                ax.set_xticklabels(labels, minor=False, ha='right', rotation=70)
                ax.set_yticklabels(labels, minor=False)
                
                plt.tight_layout()
        
        # remove the y column from the correlation matrix
        # after using it to select background and signal
def compare_train_test(clf, X_train, y_train, X_test, y_test, bins=30):
        decisions = []
        for X,y in ((X_train, y_train), (X_test, y_test)):
                d1 = clf.decision_function(X[y>0.5]).ravel()
                d2 = clf.decision_function(X[y<0.5]).ravel()
                decisions += [d1, d2]

        low = min(np.min(d) for d in decisions)
        high = max(np.max(d) for d in decisions)
        low_high = (low,high)

        plt.hist(decisions[0],color='r', alpha=0.5, range=low_high, bins=bins,histtype='stepfilled', normed=True,label='S (train)')
        plt.hist(decisions[1],color='b', alpha=0.5, range=low_high, bins=bins,
        histtype='stepfilled', normed=True,label='B (train)')
        hist, bins = np.histogram(decisions[2],bins=bins, range=low_high, normed=True)
        scale = len(decisions[2]) / sum(hist)
        err = np.sqrt(hist * scale) / scale

        width = (bins[1] - bins[0])
        center = (bins[:-1] + bins[1:]) / 2
        plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='S (test)')

        hist, bins = np.histogram(decisions[3],bins=bins, range=low_high, normed=True)
        scale = len(decisions[2]) / sum(hist)
        err = np.sqrt(hist * scale) / scale

        plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='B (test)')
        
        plt.xlabel("BDT output")
        plt.ylabel("Arbitrary units")
        plt.legend(loc='best')
        plt.show()
        plt.savefig('overtraining.png')
def roccurve(bdt,X_test,y_test):
        decisions = bdt.decision_function(X_test)
        # Compute ROC curve and area under the curve
        fpr, tpr, thresholds = roc_curve(y_test, decisions)
        roc_auc = auc(fpr, tpr)

        plt.plot(fpr, tpr, lw=1, label='ROC (area = %0.2f)'%(roc_auc))

        plt.plot([0, 1], [0, 1], '--', color=(0.6, 0.6, 0.6), label='Luck')
        plt.xlim([-0.05, 1.05])
        plt.ylim([-0.05, 1.05])
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.title('Receiver operating characteristic')
        plt.legend(loc="lower right")
        plt.grid()

def validation_curve(clfs, train, test):
        X_test, y_test = test
        X_train, y_train = train

        for n,clf in enumerate(clfs):
                test_score = np.empty(len(clf.estimators_))
                train_score = np.empty(len(clf.estimators_))

                for i, pred in enumerate(clf.staged_decision_function(X_test)):
                        test_score[i] = 1-roc_auc_score(y_test, pred)

                for i, pred in enumerate(clf.staged_decision_function(X_train)):
                        train_score[i] = 1-roc_auc_score(y_train, pred)

                best_iter = np.argmin(test_score)
                learn = clf.get_params()['learning_rate']
                depth = clf.get_params()['max_depth']
                test_line = plt.plot(test_score,label='learn=%.1f depth=%i (%.2f)'%(learn,depth,
                                                                                    test_score[best_iter]))
                colour = test_line[-1].get_color()
                plt.plot(train_score, '--', color=colour)

                plt.xlabel("Number of boosting iterations")
                plt.ylabel("1 - area under ROC")
                plt.axvline(x=best_iter, color=colour)
        
        plt.legend(loc='best')

 

        # Taken more or less straight from
        # http://scikit-learn.org/stable/auto_examples/plot_learning_curve.html
def plot_learning_curve(estimator, title, X, y, cv=None,n_jobs=1, train_sizes=np.linspace(.1, 1.0, 5),scoring=None, ax=None, xlabel=True):
        if ax is None:
                plt.figure()
                ax.title(title)
        if xlabel:
                ax.set_xlabel("Training examples")
        ax.set_ylabel("Score")

        train_sizes, train_scores, test_scores = learning_curve(estimator,X,y,cv=cv,n_jobs=n_jobs,
                                                                train_sizes=train_sizes,
                                                                scoring=scoring)
        train_scores_mean = np.mean(train_scores, axis=1)
        train_scores_std = np.std(train_scores, axis=1)
        test_scores_mean = np.mean(test_scores, axis=1)
        test_scores_std = np.std(test_scores, axis=1)
        
                                        
        ax.fill_between(train_sizes, train_scores_mean - train_scores_std,
                        train_scores_mean + train_scores_std, alpha=0.1,
                        color="r")
        ax.fill_between(train_sizes, test_scores_mean - test_scores_std,
                        test_scores_mean + test_scores_std, alpha=0.1, color="g")
        ax.plot(train_sizes, train_scores_mean, 'o-', color="r",
                label="Training score")
        ax.plot(train_sizes, test_scores_mean, 'o-', color="g",
                label="Cross-validation score")

        ax.set_ylim([0.65, 1.0])
        return plt
                                
