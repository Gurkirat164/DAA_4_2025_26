#include <iostream>
#include<vector>
using namespace std;
int main() {
    int k,n;
    cin >> k >> n;
    vector<int> arr;
    vector<int> res;
    for( int i =0;i<n;i++) {
        int val;
        cin >> val;
        
        int low = 0;
        int high = arr.size();

        while (low < high) {
            int mid = low + (high - low ) / 2;
            if ( val >= arr[mid]) {
                low = mid + 1;
            } 
            else high = mid;
        }
        arr.insert (arr.begin() + low , val);

        if ( i < k - 1 ) {
            res.push_back(-1); 
        }
        else {
            res.push_back(arr[arr.size()-k]);
        }
    }

    for( int i=0; i<n; i++ ) {
        cout<< res[i]<< endl;
    }

    return 0;
}