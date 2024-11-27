int maxProfit(int* prices, int pricesSize){
    int ans = 0;
    for(int i = 1; i < pricesSize; ++i){
        ans += fmax(0, prices[i] - prices[i - 1]);
    }
    return ans;
}
