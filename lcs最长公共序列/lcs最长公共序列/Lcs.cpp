#include<iostream>
#include<string>
#include<vector>
using namespace std;
int Lcs_DP(string X, string Y)
{	int m = X.size();
	int n = Y.size();
	vector<vector<int>>dp(m + 1,vector<int>(n + 1, 0));
	
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (X[i-1] == Y[j-1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[m][n];
}
int Lcs(string X ,int m, string Y,int n)
{
	if (m< 0 || n < 0)
	{
		return 0;
	}
	if (X[m] == Y[n])
	{
		return Lcs(X, m - 1, Y, n - 1)+1;
	}
	else
	{
		int val1 = Lcs(X, m - 1, Y, n);
		int val2 = Lcs(X, m, Y, n - 1);
		return std::max(val1, val2);
	}
}
int main()
{	
	string str1 = "hellow";
	string str2 = "world";
	//int val = Lcs(str1, str1.size() - 1, str2, str2.size() - 1);
	int val = Lcs_DP(str1, str2);
	cout << val << endl;
	return 0;
}