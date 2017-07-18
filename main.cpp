/*
Description: This ia a Program to reduce noise and filter data coming out of a LIDAR sensor.
              The data is generated in the form of an array of floats of length N which represents Distance measurements wrt the sensor. 
Parameters: Length of N is generally between [200,1000] measurements 
             Range of data is about ~[0.03,50] meters.

Filters : There are Two Main filters implemented and tested.
    - Range Filter - The range filter Thresholds the minimum and maximum value of the elements of the array to defined values. 
                    This is defined by the lower_threshold_ and upper_threshold_. 

    - Temporal Median Filter - This filter is used to find the median of a set of sorted values  which reduced the noise in case of 
                       large sudden changes and smoothes the output.
                      it is represented by :
                                Yi(t) = median(Xi(t),Xi(t-1),Xi(t-2),.....Xi(t-D)) where D is the size of the window.

 Class: The lidarFilter class consists of all the functions and update functions. It is in the lidar.h file

 @Author : Raghavendra Sriram
 @Dated : June 6th, 2017.
 @contact : raghavm@uta.edu.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "lidar.h"

using namespace std;

 lidarFilter filter1; //initializing Class object - Filter
 
float *testArray(int time) {
  switch (time) {
    case 0: {
      float *array_1 = new float[5];
      array_1[0] = 0.;
      array_1[1] = 1.;
      array_1[2] = 2.;
      array_1[3] = 1.;
      array_1[4] = 3.;
      return array_1;
    } break;
    case 1: {
      float *array_2 = new float[5];
      array_2[0] = 1.;
      array_2[1] = 5.;
      array_2[2] = 7.;
      array_2[3] = 1.;
      array_2[4] = 3.;
      return array_2;
    } break;
    case 2: {
      float *array_3 = new float[5];
      array_3[0] = 2.;
      array_3[1] = 3.;
      array_3[2] = 4.;
      array_3[3] = 1.;
      array_3[4] = 0.;
      return array_3;
    } break;
    case 3: {
      float *array_4 = new float[5];
      array_4[0] = 3.;
      array_4[1] = 3.;
      array_4[2] = 3.;
      array_4[3] = 1.;
      array_4[4] = 3.;
      return array_4;
    } break;
    case 4: {
      float *array_5 = new float[5];
      array_5[0] = 10.;
      array_5[1] = 2.;
      array_5[2] = 4.;
      array_5[3] = 0.;
      array_5[4] = 0.;
      return array_5;
    } break;
    case 5: {
      float *array_6 = new float[5];
      array_6[0] = 10;
      array_6[1] = 2;
      array_6[2] = 4;
      array_6[3] = 0;
      array_6[4] = 0;
      return array_6;
    } break;
    case 6: {
      float *array_7 = new float[5];
      array_7[0] = 10;
      array_7[1] = 2;
      array_7[2] = 4;
      array_7[3] = 0;
      array_7[4] = 0;
      return array_7;
    } break;
    case 7: {
      float *array_8 = new float[5];
      array_8[0] = 10;
      array_8[1] = 2;
      array_8[2] = 4;
      array_8[3] = 0;
      array_8[4] = 0;
      return array_8;
    } break;
  };
  return 0;
}


int main(int argc, char **argv) {
 
  int n = 5; // initializing variable to the size of array (5)
  int a; // User input to select type of input (thresholded or Unthresholded )
  cout << "\n\n\n\nThis program filters LIDAR data by means of a Threshold filter and a Median Filter." << endl;
  cout << "If you want to use raw un-thresholded data please press 1 and enter"<< endl;
  cout <<"Else press 0 and Enter for Thresholed data to be used : (default is un-thresholded data) \n" << endl;
  cin >> a;
                    // This is the main Windowing Function 
  for (int time = 0; time < 8; time++) {
    float *input_scan = testArray(time); // Passing input array data to input_scan pointer.
                cout << "\nMain(): Unfiltered Input Array " << time << endl;
    filter1.printArrayOutput(input_scan,n); // this function prints out the input Array.
    vector<float> mArray;
    filter1.arrayToVector(input_scan, mArray, n);
                    // this function thresholds or doesnt depending on user input.//
    if (a == 1){
      cout << "Main(): Thresholded Input " << time << endl;
      mArray = filter1.thresholdScan(mArray);
      }else if (a == 0){
      cout << "Main(): UnThresholded Input " << time << endl;
      };
    filter1.setWindow(time,mArray); // Defining size of Window for the Median filter.
    filter1.printVectorOutput(mArray);  // this function prints out the Vector.
                cout << "Main() The Input : X(t) = " << time << endl;
                cout << "Main(): Median (Y(t)) is : {";
    vector<float> out(n);
                    // This loop gets the column datapoints to be filtered. 
    for (int data_point = 0; data_point < n; data_point++) {
    vector<float> col = filter1.getColumn(data_point, time);

      if (time == 0) {
        col.resize(1);
      } else if (time <= 3) {
        col.resize(time + 1);
      }
      // Theis function call sorts the column vector and then finds the median of the values and returns it to main.
     out[data_point] = filter1.medianUpdate(col);
    }
              cout << "}\n";
              cout<<"-----------------------------------------------------------------------"<< endl;
  }
  return 0;
}
