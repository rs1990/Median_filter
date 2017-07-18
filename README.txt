
***************************------------------------------************************************
@Author : Raghavendra Sriram
@Date : June 9th, 2017.

Description: This ia a Program to reduce noise and filter data coming out of a LIDAR sensor.
             The data is generated in the form of an array of floats of length N which represents Distance measurements wrt the sensor. 
Parameters:  Length of N is generally between [200,1000] measurements 
             Range of data is about ~[0.03,50] meters.

Filters :    There are Two Main filters implemented and tested.
      - Range Filter - The range filter Thresholds the minimum and maximum value of the elements of the array to defined values. 
             This is defined by the lower_threshold_ and upper_threshold_. 

      - Temporal Median Filter - This filter is used to find the median of a set of sorted values  which reduced the noise in case of 
             large sudden changes and smoothes the output.
             it is represented by :
                                Yi(t) = median(Xi(t),Xi(t-1),Xi(t-2),.....Xi(t-D)) where D is the size of the window.

Class:       The lidarFilter class consists of all the functions and update functions. It is in the lidar.h file


Use :        The Filter allows the user to decide the type of data to be filtered ( thresholded or Unthresholded) 


***************************------------------------------************************************

Instructions :
		1. Open a Terminal
		2. Navigate to directory
		3. run Make : $ make
		4. Execute the output created : $ ./result 
		5. Select what type of data you want to be used and hit enter. ( 1 - thresholded Input array)
									       ( 0 - Unthresholded Input array)

Clean : On terminal run make clean.
	$ make clean

Contact : raghavm@uta.edu



