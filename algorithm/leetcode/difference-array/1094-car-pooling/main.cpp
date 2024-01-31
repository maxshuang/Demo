/*
 * There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).
You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi passengers and the locations to pick them up and drop them off are fromi and toi respectively. The locations are given as the number of kilometers due east from the car's initial location.
Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.

Constraints:
1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 105
 */

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // using difference array to reduce to O(m) time complexity
        // change the O(n) range operation to O(1) operation
        // Diff[i]=nums[i]-nums[i-1]
        vector<int> diff(1001, 0);
        for(vector<int> trip: trips) {
            diff[trip[1]]+=trip[0];
            diff[trip[2]]-=trip[0];
        }
        int sum=0;
        for(int d: diff) {
            sum+=d;
            if(sum>capacity){
                return false;
            }
        }

        return true;
    }
};
