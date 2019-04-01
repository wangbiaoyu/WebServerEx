#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
using namespace std;

class Solution {
    public:
            int num = INT_MAX;
                int coinChange(vector<int>& coins, int amount) {
                            if (coins.empty()) return 0;
                                    go(coins,amount,0);
                                            return num != INT_MAX ? num : -1;
                                                }
                    
                    void go(vector<int> coins,int amount,int val){
                                if(amount == 0)
                                                num = min(num,val ? val : INT_MAX);
                                        if(amount < 0)
                                                        return;
                                                for(auto v : coins){
                                                                go(coins,amount - v,val + 1);
                                                                        }
                                                    }
};

int main(){
    Solution a = Solution();
    vector<int> a1{1,2,5,10};
    a.coinChange(a1,27);
    cout << a.num << endl;
    return 0;
}
