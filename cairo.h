//
// Created by RC on 09.12.2022.
//

#ifndef SYSTEM_CAIRO_H
#define SYSTEM_CAIRO_H

#include <vector>
using namespace std;

class Cairo
{
public:
    static void Create(unsigned int n , unsigned int m, const string& folder="")
    {
        double PI = 3.14159265;
        int a = 472;
        int b = 344;
        int l = 300;
        int c = 376;

//        const int n = 2;
//        const int m = 4;

        const int N=(n*m*5);
        const int NN=N*N;
        const int fact=100000;
        const int order=24;

        double sin60 = sin(PI/3);

        double yd = (2*a-c)/2;
        double xd = yd/2;


        vector<double> x1;
        vector<double> y1;
        vector<double> mx1;
        vector<double> my1;

        vector<double> x2;
        vector<double> y2;
        vector<double> mx2;
        vector<double> my2;

        x1.push_back(0);
        x1.push_back(xd+b/2);
        x1.push_back(xd+b/2);
        x1.push_back(-xd-b/2);
        x1.push_back(-xd-b/2);

        y1.push_back(0);
        y1.push_back(yd*sin60);
        y1.push_back(-yd*sin60);
        y1.push_back(-yd*sin60);
        y1.push_back(yd*sin60);

        mx1.push_back(l*1);
        mx1.push_back(l*0.5);
        mx1.push_back(l*0.5);
        mx1.push_back(l*(-0.5));
        mx1.push_back(l*(-0.5));

        my1.push_back(0);
        my1.push_back(l*sin60);
        my1.push_back(l*(-sin60));
        my1.push_back(l*(-sin60));
        my1.push_back(l*sin60);


        x2 = y1;
        y2 = x1;
        mx2 = my1;
        my2 = mx1;


        vector<double> vx;
        vector<double> vy;
        vector<double> vmx;
        vector<double> vmy;


        vx.reserve(n * m * x1.size());
        vy.reserve(n * m * y1.size());
        vmx.reserve(n * m * mx1.size());
        vmy.reserve(n * m * my1.size());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if( (i%2)^(j%2) == 0 )
                {
                    for(int k = 0; k < x1.size(); k++)
                    {
                        vx.push_back(x1[k]+i*816);
                        vy.push_back(y1[k]+j*816);
                        vmx.push_back(mx1[k]);
                        vmy.push_back(my1[k]);

                    }
                }
                else
                {
                    for(int k = 0; k < x1.size(); k++)
                    {
                        vx.push_back(x2[k]+i*816);
                        vy.push_back(y2[k]+j*816);
                        vmx.push_back(mx2[k]);
                        vmy.push_back(my2[k]);

                    }
                }


        int size_mass = vx.size()*sizeof(double);

        double* x = new double [N];
        double* y = new double [N];
        double* mx = new double [N];
        double* my = new double [N];

        //число семплирований
        unsigned long long int max = pow(2,order);

        //стартовая конфигурация все вниз
        for(int i = 0; i < N; i++)
        {
            x[i] = vx[i];
            //cout<<x[i]<<"\t";
            y[i] = vy[i];

            if(vmy[i]<0)
            {
                //cout<<y[i]<<"\t";
                mx[i] = vmx[i]*(-1);
                //	cout<<mx[i]<<"\t";
                my[i] = vmy[i]*(-1);
                //cout<<my[i]<<endl;
            }
            if(vmy[i]>0 && vmx[i]<0 || vmy[i]>0 && vmx[i]>0)
            {//cout<<y[i]<<"\t";
                mx[i] = vmx[i];
                //	cout<<mx[i]<<"\t";
                my[i] = vmy[i];
                //cout<<my[i]<<endl;
            }
            if(vmy[i]==0 && vmx[i]<0)
            {
                mx[i]=vmx[i]*(-1);
                my[i] = vmy[i];
            }
            if(vmx[i]==0 && vmy[i]<0)
            {
                mx[i]=vmx[i];
                my[i]=vmy[i]*(-1);

            }
            if(vmy[i]==0 && vmx[i]>0)
            {
                mx[i]=vmx[i];
                my[i]=vmy[i];
            }
            if(vmx[i]==0 && vmy[i]>0)
            {
                mx[i]=vmx[i];
                my[i]=vmy[i];
            }
        }

        FILE* f;
        f = fopen((folder + "/Cairo_" + to_string(N) + ".mfsys").c_str(),"w");
//        *************************************************************************************
        fprintf(f,"[header]\ndimensions=2\nsize=%i\nstate=",vx.size());
        for (int i = 0; i<vx.size(); i++) fprintf(f,"0");
        fprintf(f,"\n[parts]\n");
        for (int i = 0; i<vx.size(); i++)
            fprintf(f,"%i\t%.16f\t%.16f\t0\t%.16f\t%.16f\t0\t0\n",i,vx[i],vy[i],mx[i],my[i]);
        fclose(f);
    }
};

#endif //SYSTEM_CAIRO_H
