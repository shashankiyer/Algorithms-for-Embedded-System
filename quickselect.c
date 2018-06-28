/******************************************************************************
 * Copyright (C) 2018 by Shashank Iyer
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Shashank Iyer is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file: quickselect.c 
 * @brief: Contains a method that computes the median of an array in O(n) time and O(1) space.
 *
 * Uses a modified, iterative implementation of the Quickselect algorithm
 *
 * @author Shashank Iyer
 * @date 06-18-2018
 *
 */


#include <stdio.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)

/* Declaring a typedef for unsigned char */
typedef unsigned char BYTE;

BYTE find_median(BYTE* arr, size_t size); // Given an array of data and a length, returns the median value
BYTE find_mean(BYTE* arr, size_t size); // Given an array of data and a length, returns the mean
BYTE find_maximum(BYTE* arr, size_t size); // Given an array of data and a length, returns the maximum
BYTE find_minimum(BYTE* arr, size_t size); // Given an array of data and a length, returns the minimum
void sort_array(BYTE* arr, size_t size); // Given an array of data and a length, sorts the array from largest to smallest.

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  86,  25,  23,
                              200, 122, 150, 90,   92,  85, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  printf("The median of the array is= %d\n",find_median(arr,size));
}

void print_array(BYTE* arr, size_t size)
{
	size_t i;
	if(arr == NULL)
	{
		printf("The array is empty");
		return;
	}
	printf("The elements of the array are\n");
	for(i =0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

static void swap(BYTE* index1, BYTE* index2) // A function that swaps the BYTE values at two location
{
	BYTE temp = *index1;
	*index1 = *index2;
	*index2 = temp;
}

static size_t partition(size_t start, size_t end, BYTE* arr) // Partitions the array around the selected pivot
{
	size_t mid, i, j;
	BYTE pivot;

	if(end - start == 1) // Handles the base case
	{
		BYTE lesser = arr[start] < arr[end]? arr[start]:arr[end];
		arr[start] = arr[start] > arr[end]? arr[start]:arr[end];
		arr[end] = lesser;
		return end;
	}

	mid = (start + end)/2;
	
	/**
	* Median of 3 strategy used for partiton
	*/

	if(arr[mid] > arr[end])
		swap(arr + mid, arr + end);
	if(arr[start] > arr[end])
		swap(arr + start, arr + end);
	if(arr[start] > arr[mid])
		swap(arr + start, arr + mid);

	pivot = arr[mid];

	swap(arr + mid, arr + end);
	i = start; 
	j = end - 1;
	while(i<j)
	{
		while(arr[i] > pivot && i < j)
			i++;
		while(arr[j] <= pivot && j > i)
			j--;

		if(i < j)
			swap(arr + i, arr + j);
	}

	swap(arr + i, arr + end);

	return i;
}

BYTE find_median(BYTE* arr, size_t size) //Quickselect algorithm
{
	BYTE median = 0;
	size_t start, end;
	size_t i, k;
	BYTE pivot;
	if ( arr == NULL)
    	return 0;
  
  	if ( size <= 0 )
  	  size = 1;

  	k = size/2;

  	for(start = 0, end = size - 1; start < end;)
  	{
  		
  		i = partition(start, end, arr);
  		if(i == k)
  			break;
  		else if(i > k)
  			end = i - 1;
  		else 
  			start = i + 1;

  	}

  	return arr[i];

}