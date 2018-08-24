
namespace zkwsegment{
    int d[MAXN<<2]; //Ò»¶¨¿ª4±¶
    void build(int n)
    {
        for(bit=1;bit<=n+1;bit<<=1);
        for(int i=bit+1;i<=bit+n;i++)
            scanf("%d",&d[i]);
        for(int i=bit-1;i;i--)
        {
            d[i]=max(d[i<<1],d[i<<1|1]);
            d[i<<1]-=d[i];d[i<<1|1]-=d[i];
        }
    }
    void update(int s,int t,int x)
    {
        int tmp;
        for(d[s]+=x;s>1;s>>=1)
        {
            tmp=max(d[s],d[s^1]);d[s]-=tmp;d[s^1]-=tmp;d[s>>1]+=tmp;
            s>>=1;
        }
    }
    void querySingle(int x)
    {
        int res=0;
        while(x)
            res+=d[x],x>>=1;
        return res;
    }
    void update(int s,int t,int val)
    {
        s+=bit;t+=bit;
        int tmp;
        if(s==t)
        {
            for(d[s]+=val;s>1;s>>=1)
            {
                tmp=max(d[s],d[s^1]);
                d[s]-=tmp;d[s^1]-=tmp;
                d[s>>1]+=tmp;
            }
            return;
        }
        for(d[s]+=val,d[t]+=val;s^t^1;s>>=1,t>>=1)
        {
            if(~s&1)
                d[s^1]+=val;
            if(t&1)
                d[t^1]+=val;
            tmp=max(d[s],d[s^1]);
            d[s]-=tmp;d[s^1]-=tmp;
            d[s>>1]+=tmp;
            tmp=max(d[t],d[t^1]);
            d[t]-=tmp;d[t^1]-=tmp;
            d[t>>1]+=tmp;
        }
        for(;s>1;s>>=1)
        {
            tmp=max(d[s],d[s^1]);
            d[s]-=tmp;d[s^1]-=tmp;
            d[s>>1]+=tmp;
        }
        return;
    }
    int query(int s,int t)
    {
        int lans=0,rans=0,ans;
        if(s==t)
        {
            for(s+=bit;s;s>>=1)
            {
                lans+=d[s];
            }
            return lans;
        }
        for(s+=bit,t+=bit;s^t^1;s>>=1,t>>=1)
        {
            lans+=d[s];rans+=d[t];
            if(~s&1)
                lans=max(lans,d[s^1]);
            if(t&1)
                rans=max(rans,d[t^1]);
        }
        lans+=d[s];rans+=d[t];
        for(ans=max(lans,rans);s>1;)
        {
            s>>=1;
            ans+=d[s];
        }
        return ans;
    }


}
