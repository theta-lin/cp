void exgcd(int &x,int &y,int a,int b)
{
    if(!b)
    {
        x=1;
        y=0;
        return;
    }
    exgcd(x,y,b,a%b);
    int t=x;
    x=y;
    y=t-a/b*y;
}
