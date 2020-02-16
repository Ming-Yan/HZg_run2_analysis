void MCpho(TreeReader &data, vector<int> &accepted)
{
    accepted.clear();
    vector<int> passUnsorted;
    passUnsorted.clear();
    vector<float> mcPtUnsorted;
    mcPtUnsorted.clear();
    Int_t  nMC                    = data.GetInt("nMC");
    Int_t* mcPID                  = data.GetPtrInt("mcPID");
    Int_t* mcMomPID              = data.GetPtrInt("mcMomPID");
    float* mcPt                   = data.GetPtrFloat("mcPt");
    float* mcEta                  = data.GetPtrFloat("mcEta");
    float* mcPhi                  = data.GetPtrFloat("mcPhi");
    UShort_t* mcStatusFlag        = (UShort_t*) data.GetPtrShort("mcStatusFlag");
    for (Int_t i=0; i<nMC; ++i)
    {
         if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
                if (((mcStatusFlag[i] >> 0) & 1) == 1 && ((mcStatusFlag[i] >> 1) & 1) == 1)
                {
            if(fabs(mcMomPID[i])!=25) continue;
            if (fabs(mcPID[i]) != 22) continue;
            if(mcPt[i] < 10.) continue;
            if (fabs(mcEta[i]) > 2.5) continue;
            if (fabs(mcEta[i] )< 1.4442 && fabs(mcEta[i]) > 1.566) continue;
            if (mcPt[i] < 10.) continue;
            passUnsorted.push_back(i);
            mcPtUnsorted.push_back(mcPt[i]);
        }
    }
    // sort accepted electrons in descending order of their pt
    int siz = (int) passUnsorted.size();
    if (siz < 1) return;
    int ind[siz];
    TMath::Sort(siz, &mcPtUnsorted.front(), ind);
    for (int i = 0; i < siz; ++i)
    {
        accepted.push_back(passUnsorted[ind[i]]);
    }
}
//MC electron selection sort
void MCele(TreeReader &data, vector<int> &accepted)
{
    accepted.clear();
    vector<int> passUnsorted;
    passUnsorted.clear();
    vector<float> mcPtUnsorted;
    mcPtUnsorted.clear();
    Int_t  nMC                    = data.GetInt("nMC");
    Int_t* mcPID                  = data.GetPtrInt("mcPID");
    float* mcPt                   = data.GetPtrFloat("mcPt");
    float* mcEta                  = data.GetPtrFloat("mcEta");
    float* mcPhi                  = data.GetPtrFloat("mcPhi");
    float* mcMass                 = data.GetPtrFloat("mcMass");
    UShort_t* mcStatusFlag        = (UShort_t*) data.GetPtrShort("mcStatusFlag");
    for (Int_t i=0; i<nMC; ++i)
    {
        if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
                if (((mcStatusFlag[i] >> 0) & 1) == 1 && ((mcStatusFlag[i] >> 1) & 1) == 1)
                {
            if (fabs(mcPID[i]) != 11) continue;
            if(mcPt[i] < 15.) continue;
            if (fabs(mcEta[i] )> 2.5) continue;
            passUnsorted.push_back(i);
            mcPtUnsorted.push_back(mcPt[i]);
        }
        // sort accepted electrons in descending order of their pt
        int siz = (int) passUnsorted.size();
        if (siz < 1) return;
        int ind[siz];
        TMath::Sort(siz, &mcPtUnsorted.front(), ind);
        for (int i = 0; i < siz; ++i)
        {
            accepted.push_back(passUnsorted[ind[i]]);
        }
    }
}
//MC muon selection and sort
    void MCmu(TreeReader &data, vector<int> &accepted)
    {
        accepted.clear();
        vector<int> passUnsorted;
        passUnsorted.clear();
        vector<float> mcPtUnsorted;
        mcPtUnsorted.clear();
        Int_t  nMC                    = data.GetInt("nMC");
        Int_t* mcPID                  = data.GetPtrInt("mcPID");
        float* mcPt                   = data.GetPtrFloat("mcPt");
        float* mcEta                  = data.GetPtrFloat("mcEta");
        float* mcPhi                  = data.GetPtrFloat("mcPhi");
        float* mcMass                 = data.GetPtrFloat("mcMass");
        UShort_t* mcStatusFlag        = (UShort_t*) data.GetPtrShort("mcStatusFlag");
        for (Int_t i=0; i<nMC; ++i)
        {
               if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
                if (((mcStatusFlag[i] >> 0) & 1) == 1 && ((mcStatusFlag[i] >> 1) & 1) == 1)
                {
                if (fabs(mcPID[i]) != 13) continue;
                if(mcPt[i] < 10.) continue;
                if (fabs(mcEta[i]) > 2.4) continue;
                passUnsorted.push_back(i);
                mcPtUnsorted.push_back(mcPt[i]);
            }
            // sort accepted electrons in descending order of their pt
            int siz = (int) passUnsorted.size();
            if (siz < 1) return;
            int ind[siz];
            TMath::Sort(siz, &mcPtUnsorted.front(), ind);
            for (int i = 0; i < siz; ++i)
            {
                accepted.push_back(passUnsorted[ind[i]]);
            }
        }
    }
