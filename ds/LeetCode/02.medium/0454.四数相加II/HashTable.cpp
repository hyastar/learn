class Solution{
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D){
        unordered_map<int, int> umap;

        for(int a : A){
            for(int b : B){
                umap[a+b]++;
            }
        }

        int count = 0;

        for(int c : C){
            for(int d : D){
                if(umap.find(0 - (c + d)) != umap.end()){
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }
};
