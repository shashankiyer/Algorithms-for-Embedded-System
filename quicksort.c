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
 * @file: stats.h 
 * @brief: Contains a set of functions that compute and display an array's stats
 *
 * Includes functions to compute the minimum, maximum, mean, median. 
 * Also has methods to sort and print the array
 *
 * @author Shashank Iyer
 * @date 08-18-2018
 *
 */


#include <stdio.h>
#include <stdlib.h>

/* Size of the Data Set */
#define SIZE (40)

/* Declaring a typedef for unsigned char */
typedef unsigned char BYTE;

void print_array(BYTE* arr, size_t size); // Given an array of data and a length, prints the array to the screen
void sort_array(BYTE* arr, size_t size); // Given an array of data and a length, sorts the array from largest to smallest.

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  86,  25,  23,
                              200, 122, 150, 90,   92,  85, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  sort_array(test, SIZE);
  print_array(test, SIZE);
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


void bubble_sort(BYTE* arr, size_t size) //Sorts the array in O(n^2)
{
	printf("Not enough memory\nUsing suboptimal sort");
	size_t i, j;
	for(i=0; i<size;i++)
		for(j=i+1;j<size;j++)
			if(arr[i] < arr[j])
				swap(arr + i, arr + j);
}

void sort_array(BYTE* arr, size_t size) //Quicksort algorithm
{
	BYTE *stack =(BYTE*) malloc((size+1) *sizeof(BYTE));// This array is used like a stack to implement iterative Quicksort
	size_t top = 0; // Top of the stack
	size_t start, end, pivot_index, counter;
	
	if ( arr == NULL)
    	return;

    if(stack == NULL)
    	return bubble_sort(arr, size);
 	
 	stack[++top] = 0;
 	stack[++top] = size - 1;
 	counter = 0;

 	//Access the top of the stack till stack is not empty
 	while(top > 0)
 	{
 		end = stack[top--];
 		start = stack[top--];
 		
 		pivot_index = partition(start, end, arr);
 		
 		//If there are elements to the left of the pivot, add them to the stack
 		if(pivot_index>0 && pivot_index - 1 > start)
 		{
 			stack[++top] = start;
 			stack[++top] = pivot_index - 1;
 		}

 		//If there are elements to the right of the pivot, add them to the stack
 		if((pivot_index + 1) < end)
 		{
 			stack[++top] = pivot_index + 1;
 			stack[++top] = end;
 		}

 	}

 	free(stack);
}