ll memo[30][3][4];   string a;
ll dp(int idx,bool flag,int rem)
{
    if(rem > 3) return 0;
    if(idx == a.size())return 1;
    ll &res = memo[idx][flag][rem];
    if(res != -1) return res;
    res = 0;
    if(flag) // constrains
    {
        int g = a[idx] -'0';
        for(int i =0;i<=g;i++)
        {
            res += dp(idx+1,(i==g),rem + (i!=0));
        }
    }else
    {
        for(ll i =0;i<=9;i++)
            res += dp(idx+1,0,rem + (i!=0));
    }
 return res;
}