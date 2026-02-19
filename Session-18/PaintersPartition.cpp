class Solution {
  public:
  
      bool isPossible(int maxTime,  vector<int>& arr, int k) {
        int painters = 1;    
        int currSum = 0;     
        for (int length : arr) {
            if (length > maxTime)
                return false;
            if (currSum + length > maxTime) {
                painters++;        
                currSum = length;  
            } 
            else {
                currSum += length;
            }
        }
        return painters <= k;
    }
    
    int minTime(vector<int>& arr, int k) {
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        int result = high;
        while (low <= high) {
            int mid = (low + high) / 2;

            if (isPossible(mid, arr, k)) {
                result = mid;     
                high = mid - 1;   
            } 
            else {
                low = mid + 1;
            }
        }
        return result;
    }
};