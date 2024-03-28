###################################################################################################  Question  #########################################################################################################################################################

There are n cities labeled from 0 to n-1 with m edges connecting them. Given the array edges where edges[i] = [fromi , toi ,weighti]  represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold. You need to find out a city with the smallest number of cities that are reachable through some path and whose distance is at most Threshold Distance. If there are multiple such cities, our answer will be the city with the greatest label.

Note: The distance of a path connecting cities i and j is equal to the sum of the edge's weights along that path.

Example 1:

Input:
n = 4, m = 4
edges = [[0, 1, 3],
         [1, 2, 1], 
         [1, 3, 4],  
         [2, 3, 1]]
distanceThreshold = 4
Output:
3
Explaination:

The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
Example 2:

Input: 
n = 5, m = 6
edges = [[0, 1, 2],
         [0, 4, 8],
         [1, 2, 3], 
         [1, 4, 2], 
         [2, 3, 1],
         [3, 4, 1]]
distanceThreshold = 2.
Output:
0
Explaination:

The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
Your Task:
You don't need to read input or print anything. Your task is to complete the function findCity( ) which takes a number of nodes n, total number of edges m and vector of edges and distanceThreshold. and return the city with the smallest number of cities that are reachable through some path and whose distance is at most Threshold Distance. If there are multiple such cities, return the city with the greatest label.

Expected Time Complexity: O(n2 + length(edges)*nlog(n) )
Expected Auxiliary Space:  O(n3)

Constraints:
1  ≤  n ≤  100
1 <= m <= n*(n-1)/2
length(edges[i]) == 3
0 <= fromi < toi < n
1 <= weighti distanceThreshold <= 104
All pairs (fromi, toi) are distinct



##################################################################################################  Solution  ##########################################################################################################################################################
//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++
class Solution {
  public:
     int findCity(int n, int m, vector<vector<int>> &edges, int distanceThreshold)
    {
        vector<pair<int, int>> adj[n];
        for (auto i : edges)
        {
            int u = i[0], v = i[1], wt = i[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
    
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        int city = -1, minCount = INT_MAX;
    
        for (int src = 0; src < n; src++)
        {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
            dist[src][src] = 0;
            pq.push({0, src});
    
            while (!pq.empty())
            {
                auto p = pq.top();
                pq.pop();
    
                int w = p.first, node = p.second;
    
                for (auto nei : adj[node])
                {
                    int v = nei.first, wt = nei.second;
    
                    if (w + wt < dist[src][v])
                    {
                        dist[src][v] = w + wt;
                        pq.push({dist[src][v], v});
                    }
                }
            }
    
            int count = 0;
            for (int i = 0; i < n; i++)
                if (src != i and dist[src][i] <= distanceThreshold)
                    count++;
    
            if (count < minCount)
            {
                minCount = count;
                city = src;
            }
            else if (count == minCount)
                city = max(city, src);
        }
    
        return city;
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj;
        // n--;
        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        int dist;
        cin >> dist;
        Solution obj;
        cout << obj.findCity(n, m, adj, dist) << "\n";
    }
}

// } Driver Code Ends


