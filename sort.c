#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heap(int arr[], int N, int i)
{
    int large = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < N && arr[l] > arr[large])
        large = l;
 
    if (r < N && arr[r] > arr[large])
        large = r;
 
	//Use swap statement to check if large is not bigger than i
    if (large != i) {
 
        swap(&arr[i], &arr[large]);
        heap(arr, N, large);
    }
}

// implements heap sort
void heapSort(int arr[], int n)
{
	 for (int i = n / 2 - 1; i >= 0; i--)
 
        heap(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
        heap(arr, i, 0);
    }
}

void merge(int pData[], int left, int mid, int right) {
    int i, j, k;
    int new1 = mid - left + 1;
    int new2 =  right - mid;
	int* arr1 = (int*)malloc(new1 * sizeof(int));
	int* arr2 = (int*)malloc(new2 * sizeof(int));
	extraMemoryAllocated += new1 * sizeof(int) + new2 * sizeof(int);
    for (i = 0; i < new1; i++)
        arr1[i] = pData[left + i];
    for (j = 0; j < new2; j++)
        arr2[j] = pData[mid + 1+ j];
    i = 0;
    j = 0;
    k = left;
    while (i < new1 && j < new2) {
        if (arr1[i] <= arr2[j]) {
            pData[k] = arr1[i];
            i++;
        } else {
            pData[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < new1) {
        pData[k] = arr1[i];
        i++;
        k++;
    }
    while (j < new2) {
        pData[k] = arr2[j];
        j++;
        k++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated 
void mergeSort(int pData[], int l, int r) {

	if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(pData, l, m);
        mergeSort(pData, m+1, r);
        merge(pData, l, m, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		if(i >= dataSz) {
			printf("\n\n");
			return;
		}
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}