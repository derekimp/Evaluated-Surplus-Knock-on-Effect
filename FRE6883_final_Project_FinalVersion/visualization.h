#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Lewei Peng


void plotResults(vector<vector<double>> repeat, int N = 30) {
    FILE* gnuplotPipe, * tempDataFile;
    vector<double> beat1 = repeat[0];
    vector<double> meet1 = repeat[1];
    vector<double> miss1 = repeat[2];
    size_t dataSize = beat1.size() - 1;

    const char* tempDataFileBeat = "Beat";
    const char* tempDataFileMeet = "Meet";
    const char* tempDataFileMiss = "Miss";

    double x1, y1, x2, y2, x3, y3;
    int i;
    // gnuplotPipe = popen("/opt/local/bin/gnuplot","w");
    //gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe", "w");
    gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileBeat, tempDataFileMeet, tempDataFileMiss);
        fflush(gnuplotPipe);

        tempDataFile = fopen(tempDataFileBeat, "w");
        for (i = 0; i <= dataSize; i++) {
            x1 = i - N;
            y1 = beat1[i];
            fprintf(tempDataFile, "%lf %lf\n", x1, y1);
        }
        fclose(tempDataFile);


        tempDataFile = fopen(tempDataFileMeet, "w");
        for (i = 0; i <= dataSize; i++) {
            x2 = i - N;
            y2 = meet1[i];
            fprintf(tempDataFile, "%lf %lf\n", x2, y2);
        }
        fclose(tempDataFile);

        tempDataFile = fopen(tempDataFileMiss, "w");
        for (i = 0; i <= dataSize; i++) {
            x3 = i - N;
            y3 = miss1[i];
            fprintf(tempDataFile, "%lf %lf\n", x3, y3);
        }
        fclose(tempDataFile);

        printf("press enter to continue...");
        getchar();
        //remove(tempDataFileBeat);
        //remove(tempDataFileMeet);
        //remove(tempDataFileMiss);
        fprintf(gnuplotPipe, "exit \n");
    }
    else {
        printf("gnuplot not found...");
    }
}