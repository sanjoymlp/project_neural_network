/*
I have solved a problem using PSO algorithm:

problem:
    max f(x1,x2)=x1^2+ x2^2-x1*x2+2*x1+4*x2+3;
       0<=x1,x2<=5 
    1. population size: 5;              [i.e means we have to take five points]
    2. c1=c2=1.5;                       [c1 and c2 are acceleration factors]
    3. maximum number of iteration=20;  
    4. dimension of the problem=2;      
    5. r1=0.5, r2=0.7                   [r1 and r2 random points in [0,1]]
*/
#include<bits/stdc++.h>
using namespace std;
float r1=.5,r2=0.7,c1=1.5,c2=1.5,w=0.9;
float a[5][2],b[5][2];
void randomnumber()          // randomly generate five points in [0,5];
{                            // a 2D array contains initial position of particles;
    for(int i=0;i<5;i++)     // b 2D array contains initial velocity of particles;
    {
        float x=random()%5+(float)(random()%1000)/1000;
        float y=random()%5+(float)(random()%1000)/1000;
        
        float xx=(float)(random()%1000)/1000;
        float yy=(float)(random()%1000)/1000;
        a[i][0]=x;
        a[i][1]=y;
        b[i][0]=xx;
        b[i][1]=yy;
        //cout<<xx<<" "<<yy<<"\n";
    }
}
float solve(int x, int y)       // this function gives value of given equation at (x,y);
{
    float s=x*x+y*y-x*y+2*x+4*y+3;   
    return s;
}
float pso(float x11, float v11, float pb11, float gb11)  // pso algorithm 
{
    float v111=w*v11+c1*r1*(pb11-x11)+c2*r2*(gb11-x11);
    float x111=x11+v111;
    if(x111>5)
    x111=5;
    return x111;
}
int main()
{
    randomnumber();
    priority_queue<pair<float,pair<float,float>>> q; //max heap;
    float mx=-10000.979;    // take as a mimimum value;
    int j=0;
    for(int i=0;i<20;i++)
    {
        while(!q.empty())
        {
            q.pop();
        }
        for( j=0;j<5;j++)
        {
            float p=solve(a[j][0],a[j][1]);
            q.push({p,{a[j][0],a[j][1]}});  //push five points in heap as well as value of the given euqtion 
        }                                   // at the points
        
        float pp=q.top().first;
        if(pp>mx)                         // if new value is  greater than then we can update point othewise
        {                                 // points remain unchanged;
            mx=pp;
            for(j=0;j<5;j++){
            float pb11=a[j][0];           // pbest value x-coordinate
            float pb12=a[j][1];           // pbest value y-coordinate
            float gb11=q.top().second.first; // gbest value x-coordinate
            float gb12=q.top().second.second; // gbest value y-coordinate
            float v11=b[j][0];                // velocity x-coordinate
            float v12=b[j][1];               //  velocity y-coordinate
            a[j][0]=pso(pb11,v11,pb11,gb11); // update new position of x-coordinate
            a[j][1]=pso(pb12,v12,pb12,gb12); // update new position of y-coordinate
        }
        }
    }
    int r=q.top().first;
    float xc,yc;
    cout<<"Final position of particles\n";
    while(!q.empty()){
     xc=q.top().second.first;  
     yc=q.top().second.second;
     q.pop();
    cout<<xc<<", "<<yc<<"\n"; // after 20 iteration the position of particles; 
    }
    cout<<"First point is the optimal solution";
}

