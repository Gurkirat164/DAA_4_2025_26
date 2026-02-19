class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        int result = high;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            long long hrs = 0;
            for (int x : piles) {
                hrs += (x + mid - 1) / mid;  
            }
            if (hrs <= h) {
                result = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return result;
    }
};