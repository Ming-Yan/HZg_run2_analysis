#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> comb(int N, int K)
{
	
  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0); // N-K trailing 0's
  int ncomb = 0;
  vector<vector<int>>nsets;
  // print integers and permute bitmask
  do {

	nsets.push_back(vector<int> ());
	  // nsets[K-1][ncomb].clear();
	  for (int i = 0; i < N; ++i) // [0..N-1] integers
      {
		 
        if (bitmask[i]) nsets[ncomb].push_back(i);
		// if(bitmask[i])cout<<K-1<<" "<<ncomb<<" "<<i<<endl;
		// if(bitmask[i]) cout<<i<<" ";
      }
	  // cout<<K-1<<" "<<ncomb<<" "<<nsets[K-1][ncomb].size()<<endl;
	   ncomb++;
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
  return nsets;
}
