class Solution {
public:

    bool check(vector<int> &stalls, int k, int dist) {
        int cnt = 1;
        int prev = stalls[0];

        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - prev >= dist) {
                cnt++;
                prev = stalls[i];
            }
            if (cnt >= k) return true;
        }
        return false;
    }

    int aggressiveCows(vector<int> &stalls, int k) {
        sort(stalls.begin(), stalls.end());

        int low = 1;
        int high = stalls.back() - stalls[0];
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(stalls, k, mid)) {
                ans = mid;       
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};