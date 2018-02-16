#include "compIterMS.h"

int min(int a, int b){
	if(a > b)
		return b;
	else
		return a;
}

void readrec(char* filename, Element Ls[]){
	FILE *fl;
	fl = fopen(filename, "r");
	char line[50];
	int i=0;
	char *item;
	while(fgets(line,50,fl)){
		item = strtok(line, ",");
		strcpy(Ls[i].name, item);
		item = strtok(NULL, ",");
		Ls[i].cgpa = atof(item);
		i++;
	}
	fclose(fl);
}
	
void print_rec(Element Ls[], int size){
	for (int i = 0; i < size; ++i)
	{
		printf("%d: %s %f\n", i+1 ,Ls[i].name, Ls[i].cgpa);
	}
}

void merge(Element Ls1[], int sz1, Element Ls2[], int sz2, Element Ls[]){
	int i=0, j=0, k=0;
	while(i<sz1 && j<sz2){
		if(Ls1[i].cgpa <= Ls2[j].cgpa){
			Ls[k] = Ls1[i];
			i++;
		}
		else{
			Ls[k] = Ls2[j];
			j++;
		}
		k++;
	}
	while(i<sz1){
		Ls[k] = Ls1[i];
		i++;
		k++;
	}
	while(j<sz2){
		Ls[k] = Ls2[j];
		j++;
		k++;
	}
}

void iterMS(Element Ls[], int n){
	int curr_size=1, ls=0;

	for (int curr_size = 1; curr_size <= n-1; curr_size = 2*curr_size)
	{
		for (int ls = 0; ls < n-1; ls += 2*curr_size)
		{
			int mid = ls + curr_size - 1;
			int re = min(ls + 2*curr_size - 1, n-1);
			int sz = re - ls + 1;
			int n1 = mid - ls + 1;
			int n2 = re - mid;
			Element tmp[sz], arr1[n1], arr2[n2];
			for (int i = 0; i < sz; ++i)
			{
				tmp[i] = Ls[ls + i];
			}
			for (int i = 0; i < n1; ++i)
			{
				arr1[i] = tmp[i];
			}
			for (int i = 0; i < n2; ++i)
			{
				arr2[i] = tmp[n1 + i];
			}

			merge(arr1, n1, arr2, n2, tmp);

			for (int i = 0; i < sz; ++i)
			{
				Ls[ls + i] = tmp[i];
			}
		}
	}
}