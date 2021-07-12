#include<bits/stdc++.h>
using namespace std;

double dis[30][30];
int tour[31];
int Near_Tour[31];
int Cheap_Tour[31];
int opt2_route[31];
int opt3_route[31];

class city{
public:
    int x;
    int y;
    city() {
        x=0;
        y=0;
    }
    city(int a,int b) {
        x=a;
        y=b;
    }
};


double distance_between(city a,city b) {
    return sqrt((pow((a.x-b.x),2)+pow((a.y-b.y),2)));
}

void distance_array(city c[20],int n) {
    //double **dis=0;
    //dis=new double*[n];
    for(int i=0;i<n;i++) {
        //dis[i]=new double[n];
        for(int j=0;j<n;j++) {
            //city a=c[i];
            //city b=c[j];
            //double d=distance(a,b);
            dis[i][j]=distance_between(c[i],c[j]);
        }
    }
    //return dis;
}

void Nearest_Neighbor(int n) {
    //int *tour=new int[n];
    bool visited[n];
    memset(visited,false,sizeof(visited));
    srand(time(NULL));
    int x=rand()%n;
    visited[x]=true;
    int c=0,i,j,y;
    tour[c++]=x;
    //cout<<x;
    //cout<<c<<" ";

    for(i=0;i<n-1;i++) {
        double d=FLT_MAX;
        //cout<<i<<" th x "<<x<<endl;
        for(j=0;j<n;j++) {
            if(dis[x][j]<d && j!=x && visited[j]==false) {
                d=dis[x][j];
                y=j;
                //cout<<"i "<<i<<" y "<<y<<" ";
            }
        }
        x=y;
        visited[x]=true;
        tour[c++]=x;
        //cout<<x<<c<<" ";
        //cout<<endl;
    }
    tour[c]=tour[0];
    //cout<<tour[c]<<endl;
    //cout<<c<<endl;
    //return tour;

}

void Nearest_Insertion(int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));
    srand(time(NULL));
    int x=rand()%n;
    //int x=3;
    visited[x]=true;
    int c=0,y,z;
    Near_Tour[c++]=x;
    Near_Tour[c++]=x;
    while(c<=n) {
        double d=FLT_MAX;
        for(int i=0;i<c;i++) {
            x=Near_Tour[i];
            for(int j=0;j<n;j++) {
                if(dis[x][j]<d && j!=x && visited[j]==false) {
                    d=dis[x][j];
                    y=j;
                }
            }
        }

        //cout<<y<<" "<<c<<endl;
        visited[y]=true;
        double dn=FLT_MAX;
        for(int i=0;i<c-1;i++) {
            double dcheck=dis[Near_Tour[i]][y]+dis[y][Near_Tour[i+1]]-dis[Near_Tour[i]][Near_Tour[i+1]];
            if(dcheck<dn) {
                dn=dcheck;
                z=i;
            }
        }
        //cout<<"z "<<z+1<<endl;
        // Near_Tour[z+3]=Near
        //Near_Tour[z+2]=Near_Tour[z+1];
        //Near_Tour[z+1]=y;
        for(int i=c;i>z+1;i--) {
            Near_Tour[i]=Near_Tour[i-1];
        }
        Near_Tour[z+1]=y;
        c++;
//        cout<<Near_Tour[z]+1<<" "<<Near_Tour[z+1]+1<<" "<<Near_Tour[z+2]+1<<endl;
//        for(int i=0;i<c;i++) {
//            cout<<Near_Tour[i]+1<<" ";
//        }
//
//        cout<<endl;
//        cout<<"c "<<c<<endl;

        //Near_Tour[c++]=y;
    }
}


void Cheapest_Insertion(int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));
    srand(time(NULL));
    int x=rand()%n;
    //int x=3;
    visited[x]=true;
    int c=0,y,z;
    Cheap_Tour[c++]=x;
    Cheap_Tour[c++]=x;
    //cout<<x+1<<endl;
    //cout<<c<<endl;
    while(c<=n) {
        double dn=FLT_MAX;
        for(int i=0;i<n;i++) {
            if(visited[i]==false) {
                for(int j=0;j<c-1;j++) {
                    double dcheck=dis[Cheap_Tour[j]][i]+dis[i][Cheap_Tour[j+1]]-dis[Cheap_Tour[j]][Cheap_Tour[j+1]];
                    if(dcheck<dn) {
                        dn=dcheck;
                        z=j;
                        y=i;
                    }
                }

            }
        }
        //cout<<y+1<<endl;
        visited[y]=true;
        //cout<<y<<" ";


        //cout<<"z "<<z+1<<endl;
        // Near_Tour[z+3]=Near
        //Near_Tour[z+2]=Near_Tour[z+1];
        //Near_Tour[z+1]=y;
        for(int i=c;i>z+1;i--) {
            Cheap_Tour[i]=Cheap_Tour[i-1];
        }
        Cheap_Tour[z+1]=y;
        c++;
    }
}

void Swap_opt2(int i,int k,int n) {
    int s=k-i+1;
    int temp[s];
    for(int j=0;j<s;j++) {
        temp[j]=opt2_route[k-j];
    }
    for(int j=0;j<s;j++) {
        opt2_route[i+j]=temp[j];
    }
}

double calculate_distance(int n) {
    double cost=0;
    for(int i=0;i<n;i++) {
        cost=cost+dis[opt2_route[i]][opt2_route[i+1]];
    }
    return cost;
}

double calculate_distance3(int n) {
    double cost=0;
    for(int i=0;i<n;i++) {
        cost=cost+dis[opt3_route[i]][opt3_route[i+1]];
    }
    return cost;
}

double reverse_segment_if_better(int i,int j,int k,int n) {
    int A=opt3_route[i];
    int B=opt3_route[i+1];
    int C=opt3_route[j];
    int D=opt3_route[j+1];
    int E=opt3_route[k];
    int F=opt3_route[k+1];

    double d0=dis[A][B]+dis[C][D]+dis[E][F];
    double d1=dis[A][C]+dis[B][D]+dis[E][F];
    double d2=dis[A][B]+dis[C][E]+dis[D][F];
    double d3=dis[A][D]+dis[E][B]+dis[C][F];
    double d4=dis[F][B]+dis[C][D]+dis[E][A];

    if(d0>d1) {
        int temp=opt3_route[C];
        opt3_route[C]=opt3_route[B];
        opt3_route[B]=temp;
        return (-d0+d1);
    }

    else if(d0>d2) {
        int temp=opt3_route[D];
        opt3_route[D]=opt3_route[E];
        opt3_route[E]=temp;
        return (-d0+d2);
    }

    else if(d0>d4) {
        int temp=opt3_route[A];
        opt3_route[A]=opt3_route[F];
        opt3_route[F]=temp;
        return (-d0+d4);
    }

    else if(d0>d3) {
        int temp1=opt3_route[D];
        opt3_route[D]=opt3_route[B];
        opt3_route[B]=temp1;

        int temp2=opt3_route[C];
        opt3_route[C]=opt3_route[E];
        opt3_route[E]=temp2;

        return (-d0+d3);
    }

    else return d0;

}

int main() {

    int n;
    cout<<"Enter City Number:";
    cin>>n;
    city cities[n];
    for(int i=0;i<n;i++) {
        cin>>cities[i].x>>cities[i].y;
    }

    distance_array(cities,n);
    cout<<"Distance Array"<<endl<<endl;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<setw(10)<<dis[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
    cout<<"Nearest Neighbor Heuristic"<<endl;
    cout<<"--------------------------"<<endl;

    Nearest_Neighbor(n);
    cout<<"The Tour: ";
    for(int i=0;i<=n;i++) cout<<tour[i]+1<<" ";
    cout<<endl;
    double Neighbor_cost=0;
    for(int i=0;i<n;i++) {
        Neighbor_cost=Neighbor_cost+dis[tour[i]][tour[i+1]];
    }
    cout<<"Tour Cost:"<<Neighbor_cost<<endl<<endl;

    cout<<"Nearest Insertion Heuristic"<<endl;
    cout<<"---------------------------"<<endl;

    Nearest_Insertion(n);
    cout<<"The Tour: ";
    for(int i=0;i<=n;i++) cout<<Near_Tour[i]+1<<" ";
    cout<<endl;
    double Near_cost=0;
    for(int i=0;i<n;i++) {
        Near_cost=Near_cost+dis[Near_Tour[i]][Near_Tour[i+1]];
    }
    cout<<"Tour Cost:"<<Near_cost<<endl<<endl;

    cout<<"Cheapest Insertion Heuristic"<<endl;
    cout<<"----------------------------"<<endl;
    Cheapest_Insertion(n);
    cout<<"The Tour :";
    for(int i=0;i<=n;i++) cout<<Cheap_Tour[i]+1<<" ";
    cout<<endl;
    double Cheap_cost=0;
    for(int i=0;i<n;i++) {
       Cheap_cost=Cheap_cost+dis[Cheap_Tour[i]][Cheap_Tour[i+1]];
    }
    cout<<"Tour Cost:"<<Cheap_cost<<endl<<endl;


    cout<<"2-opt Heuristic"<<endl;
    cout<<"---------------"<<endl;
    for(int i=0;i<n;i++) {
        opt2_route[i]=i;
    }
    opt2_route[n]=0;

    int flag=1,loop=1;
    while(flag==1) {
        //cout<<"hello"<<endl;
        flag=0;
        double best=calculate_distance(n);
        //cout<<best<<endl;
        for(int i=1;i<n-1;i++) {
            for(int k=i+1;k<n;k++) {
                Swap_opt2(i,k,n);
                double d=calculate_distance(n);
                //cout<<d<<endl;
                if(d<best) {
                    flag=1;
                    loop=0;
                    break;
                }
            }
            if(loop==0) {
                //cout<<"ureka"<<endl;
                break;
            }
        }

    }
    cout<<"The Tour: ";
    for(int i=0;i<=n;i++) {
        cout<<opt2_route[i]+1<<" ";
    }
    cout<<endl<<"Tour Cost: "<<calculate_distance(n)<<endl<<endl;


    cout<<"3-opt Heuristic"<<endl;
    cout<<"---------------"<<endl;
    for(int i=0;i<n;i++) {
        opt3_route[i]=i;
    }
    opt3_route[n]=0;
    int temp3[n+1];


    double cost3=calculate_distance3(n);
    int f1=1,f2=1,f3=1;
    while(1) {
        f1=0;
        for(int i=0;i<n-4;i++) {

            for(int j=i+2;j<n-2;j++) {
                f2=0;
                for(int k=j+2;k<n;k++) {
                    f3=0;
                    if(k==0 && k==n-1) continue;
                    for(int m=0;m<=n;m++) {
                        temp3[m]=opt3_route[m];
                    }
                    reverse_segment_if_better(i,j,k,n);
                    double del=calculate_distance3(n);
                    if(del<cost3) {
                        cost3=del;
                        f3=1;
                        break;
                    }
                    else {
                        for(int m=0;m<=n;m++) {
                            opt3_route[m]=temp3[m];
                        }
                    }
                }
                if(f3==1) {
                    f2=1;
                    break;
                }

            }
            if(f2==1) {
                f1=1;
                break;
            }
        }
        if(f1==0) break;
    }


    cout<<"The Tour: ";
    for(int i=0;i<=n;i++) {
        cout<<opt3_route[i]+1<<" ";
    }
    cout<<endl<<"Tour Cost: "<<calculate_distance3(n)<<endl;




    return 0;

}

