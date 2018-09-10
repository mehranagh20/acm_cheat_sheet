// The following code for APIO 2010 "Commando" was contributed by Haidar Abboud.
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
const int MAXN = 1000001;
int N , a , b , c;
int x[MAXN];
long long sum[MAXN];
long long dp[MAXN];
// The convex hull trick code below was derived from acquire.cpp
vector <long long> M;
vector <long long> B;
bool bad(int l1,int l2,int l3)
{
        return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
}
void add(long long m,long long b)
{
        M.push_back(m);
        B.push_back(b);
        while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
        {
                M.erase(M.end()-2);
                B.erase(B.end()-2);
        }
}
int pointer;
long long query(long long x)
{
        if (pointer >=M.size())
                pointer=M.size()-1;
        while (pointer<M.size()-1&&
          M[pointer+1]*x+B[pointer+1]>M[pointer]*x+B[pointer])
                pointer++;
        return M[pointer]*x+B[pointer];
}
 
int main(){
        scanf("%d" , &N);
        scanf("%d %d %d" , &a , &b , &c);
        for(int n = 1 ; n <= N ; n++){
                scanf("%d" , &x[n]);
                sum[n] = sum[n - 1] + x[n];
        }
        dp[1] = a * x[1] * x[1] + b * x[1] + c;
        add(-2 * a * x[1] , dp[1] + a * x[1] * x[1] - b * x[1]);
 
        for(int n = 2 ; n <= N ; n++){
                dp[n] = a * sum[n] * sum[n] + b * sum[n] + c;
                dp[n] = max(dp[n] , b * sum[n] + a * sum[n] * sum[n] + c + query(sum[n]));
                add(-2 * a * sum[n] , dp[n] + a * sum[n] * sum[n] - b * sum[n]);
        }
        printf("%lld\n" , dp[N]);
        return 0;
}