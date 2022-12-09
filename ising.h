//
// Created by RC on 09.12.2022.
//

#ifndef SYSTEM_ISING_H
#define SYSTEM_ISING_H

#include <vector>
#include <cstdio>
#include <string>
#include <math.h>
using namespace std;

class Ising {
public:
    static void Create(unsigned int n0, unsigned int n1, const string& folder = "") {
        unsigned int N = n0 * n1;

        string filename = folder + "/Ising_" + to_string(N) + ".mfsys";

        FILE *f = fopen(filename.c_str(), "w");

        vector<int> vx;
        vector<int> vy;
        int *x = new int[N];
        int *y = new int[N];
        int *mx = new int[N];
        int *my = new int[N];

        for (int i = 0; i < n0; i++) {
            for (int j = 0; j < n1; j++) {
                vx.push_back(i);
                vy.push_back(j);
            }
        }

        for (int i = 0; i < N; i++) {
            x[i] = vx[i];
            y[i] = vy[i];
        }

        for (int i = 0; i < N; i++) {
            mx[i] = 0;
            my[i] = 1;
        }

        fprintf(f, "[header]\ndimensions=2\nsize=%i\nstate=", N);
        for (int i = 0; i < vx.size(); i++) fprintf(f, "0");
        fprintf(f, "\n[parts]\n");
        for (int i = 0; i < vx.size(); i++)
            fprintf(f, "%i\t%i\t%i\t0\t%i\t%i\t0\t0\n", i, vx[i], vy[i], mx[i], my[i]);
        fclose(f);

    }
};

#endif //SYSTEM_ISING_H
