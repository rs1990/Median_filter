/*
 Class: The lidarFilter class consists of all the functions and update functions.

Funtions : printArrayOutput: Prints array to output.
		   printVectorOutput: Prints vector to output.
		   setWindow: Sets the size of the window based on the value specified in the constructor.
		   arrayToVector: Converts an Input Array to a Vector output. 
		   thresholdScan: This function thresholds the input vector passed in.
		   getColumn: This function gets all the column elements of the arrays.
		   medianUpdate: This function sorts and finds the Median of a number of elements from the input vector and returns the median..




Filters : There are Two Main filters implemented and tested.
    - Range Filter - The range filter Thresholds the minimum and maximum value of the elements of the array to defined values. 
                    This is defined by the lower_threshold_ and upper_threshold_. 

    - Temporal Median Filter - This filter is used to find the median of a set of sorted values  which reduced the noise in case of 
                       large sudden changes and smoothes the output.
                      it is represented by :
                                Yi(t) = median(Xi(t),Xi(t-1),Xi(t-2),.....Xi(t-D)) where D is the size of the window.



 @Author : Raghavendra Sriram
 @Dated : June 6th, 2017.
 @contact : raghavm@uta.edu.
*/



#ifndef LIDAR_RANGE_FILTER_H
#define LIDAR_RANGE_FILTER_H

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class lidarFilter {

private :
    float lower_threshold;
    float upper_threshold;
    vector<vector<float> > window;


public:
            // Constructor to initialize the threshold values and resize the median filter window vector.
   lidarFilter() {
    lower_threshold = 3.0;
    upper_threshold = 10.0;
    window.resize(4);
    }
            //Destructor for lidarFilter.
virtual ~lidarFilter() {}

            // Print the output of Vectors.
void printVectorOutput(vector<float> vectorOutput) {
  cout << "vectorOutput - {";
  for (auto &i : vectorOutput) {                     // Iterate over all elements of Vector.
     cout << i << ",";
  }
  cout << "}\n";
}
            // Print the output of Arrays. Pass in pointer and size of Array.
void printArrayOutput(float *arr, 
                      int n) {

  cout << "ArrayOutput - {";
  for (int i = 0; i < n; i++) {                      // Iterate over size of Array
    cout << arr[i] << ",";
  }
  cout << "}\n";
}

            // Sets the size of the window based on the value specified in the constructor.
void setWindow(int time,
              vector<float> mArray)
{
  window.at(time % 4) = mArray;                      // Finding the remainder and replacing the oldest value with new values from mArray.
}
 
             // Converts an Input Array to a Vector.     
void arrayToVector(float *input_scan, 
                  vector<float> &vectorOutput,
                  int inputScanSize) {

    vectorOutput.assign(input_scan, input_scan + inputScanSize);
    }

            // This function thresholds the input vector passed in.
            // INPUT ARGUMENTS:
            //                   vectorOutput

vector<float> thresholdScan(vector<float> vectorOutput) { 
    for (int i = 0; i < vectorOutput.size(); i++) {  // initializing for loop to iterate over all elements of the vector.
      float elem = vectorOutput[i];                  // copying value from vector index i to elem and comparing it to set threshold values.
      if (elem >= upper_threshold) {                 
        vectorOutput[i] = upper_threshold;           // Replacing value with threshold value if higher.
      } else if (elem <= lower_threshold) {
        vectorOutput[i] = lower_threshold;           // Replacing value with threshold value if lower.
        // cout << elem ;
      } else {  // cout << elem ;
        vectorOutput[i] = elem;                      // if within threshold, keep the same value. 
        // cout << " \n";
      }
    }
    return (vectorOutput);                           // returning thresholded output vector to main.
    }
            // This function gets all the column elements of the arrays
vector<float> getColumn(int n,
                        int time) {

    vector<float> output;                            // Initializing optput vector to save column elements of input vector to.
    output.resize(4);                                // resizing the vector to window size
    output[0] = window[0][n];                        // Saving only column values of all window vector elements for sorting and filtering
    if (time >= 1) output[1] = window[1][n];
    if (time >= 2) {
      output[2] = window[2][n];
    }
    if (time >= 3) {
      output[3] = window[3][n];
    }
    return output;                                    // returning output column vector to main.
    }


            // This function sorts and finds the Median of a number of elements from input column vectors of the input data.
            // INPUT ARGUMENTS:
            //                   mArray : Input data.

float medianUpdate(vector<float> mArray) {          

    sort(mArray.begin(), mArray.end());
    vector<float>::iterator it;                       // Initializing Iterator for vector
    float middle, middlel;
    switch (mArray.size() % 2) {                      // Checking if even or a odd elements in mArray.
      case (0):                                       // even number of elements in array
        it = mArray.begin();
        middlel = mArray.size() / 2;                  // Finds the middle two values and takes the average of the two
        it += middlel; 
        middle = (*it + *(--it)) / 2;                  
        cout << middle;
        break;
      case (1):                                      // odd number of elements in array
        it = mArray.begin();
        middlel = mArray.size() / 2;
        middle = *(it += middlel);                   // Finds the middle value of the vector.
        cout << middle;
        break;
    }
    cout << ",";
    return middle;                                    // returns the median value
  }

};

#endif
