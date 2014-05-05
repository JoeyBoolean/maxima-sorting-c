/* Joey Bachand
z294u882
Maximal Sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUF_LINE 200
#define ARRAY_SIZE 50000

#define FALSE 0
#define TRUE 1

struct A {
    int where;
    bool maximal;
	float x, y;
} POINTS[ARRAY_SIZE], pointsA[ARRAY_SIZE], pointsB[ARRAY_SIZE];

int set = 0;

struct Counts {
    int sortTime;
    int sortCount;
    int maxCountA;
    int maxNumA;
    int maxCountB;
    int maxTimeB;
    int maxNumB;
    struct Counts *next;
} C[100];


void printA(struct A a[], int number){
    int i =1;
    printf("OUTPUT FOR %d-th SET OF POINTS\n", set);
    printf("Input Size = %d\n", number-1);
    printf("sortCount = %d sortTime = %d\n", C[set].sortCount, C[set].sortTime);
    printf("maxCountA = %d maxTimeA = %d\n", C[set].maxCountA, C[set].maxCountA);
    printf("maxNumA: %d\n\n", C[set].maxNumA);
    printf("Maxima(S) from AlgorithmA (where, x, y)\n---------------------------------------\n");
    while (i < number+1){
        if(a[i].maximal == TRUE){
            printf("%d:  %f, %f\n", a[i].where, a[i].x, a[i].y);
        }
        i++;
    }
    printf("\n");
}

void printB(int head){

    int tmp = head;
    while(tmp != 0){
        tmp = pointsB[tmp].where;
        C[set].maxNumB++;        
    }
    printf("maxCountB = %d maxTimeB = %d \nmaxNumB = %d\n\n", C[set].maxCountB, C[set].maxTimeB, C[set].maxNumB);
    
    printf("Maxima(S) from AlgorithmB (where, x, y)\n---------------------------------------\n");
    while(head != 0){
        printf("%d:  %f, %f\n", head, pointsB[head].x, pointsB[head].y);
        head = pointsB[head].where;
    }
    printf("\n==============================================================\n\n");
    set++;
}

void merge(struct A a[], int p, int q, int r)
{
    C[set].sortTime++;
    struct A L[ARRAY_SIZE];
    struct A R[ARRAY_SIZE];
    int i, j, k;

    int nl = (q-p)+1; 
    int nr = r-q;

    for(i = 1; i <= nl; i++){
        C[set].sortTime++;
        L[i] = a[p+i-1];
    }

    for(j = 1; j <= nr; j++){
        C[set].sortTime++;
        R[j] = a[q+j];
    }

    L[nl + 1].x = 100;
    R[nr + 1].x = 100;
    i=1;
    j=1;
    for( k = p; k <= r; k++){
        C[set].sortTime++;
        if (L[i].x <= R[j].x){
            C[set].sortCount++;
            a[k] = L[i];
            ++i;
        }
        else{
            C[set].sortCount++;
            a[k] = R[j];
            ++j;
        }
    }

}
  
void mergesort(struct A list[], int p, int r)
{
    C[set].sortTime++;
    if (p < r) {
        int q = (p + r)/2;
        mergesort(list, p, q);
        mergesort(list, q + 1, r);
        merge(list, p, q, r);
    }
}

void findMaximal(struct A list[], int num){
    list[num].maximal = TRUE;
    int i, high = num;
    for (i = (num); i > 1; i--){
        C[set].maxCountA++;
        if(list[i].y > list[high].y){
            C[set].maxNumA++;
            list[i].maximal = TRUE;
            high = i;
        }
    }
}


int FindMaxB(int p, int r){
    int q, headL, headR, head;
    C[set].maxTimeB++;
    if(p == r){
        pointsB[p].maximal = TRUE;
        head = p;
        pointsB[p].where = 0;
        return p;
    }
    else{
        q = (p + r) / 2;
        headL = FindMaxB(p, q);
        headR = FindMaxB(q+1, r);
        head = maxMerge(headL, headR);
        return head;
    }
}

int maxMerge(int headL, int headR){
    int head = 0;
    int tail = 0;
    while((headL != 0) && (headR != 0)){
        C[set].maxCountB++;
        C[set].maxTimeB++;
        if(pointsB[headL].x <= pointsB[headR].x){

            if(pointsB[headL].y <= pointsB[headR].y){
                C[set].maxCountB++;
                pointsB[headL].maximal = 0;
                headL = pointsB[headL].where;
            }
            else{
                C[set].maxCountB++;
                if(head == 0){
                    head = headL;
                    tail = headL;
                    headL = pointsB[headL].where;
                }
                else{
                    pointsB[tail].where = headL;
                    tail = headL;
                    headL = pointsB[headL].where;
                }
            }

        }
        else{
            if(pointsB[headR].y <= pointsB[headL].y){
                C[set].maxCountB++;
                pointsB[headR].maximal = 0;
                headR = pointsB[headR].where;
            }
            else{
                C[set].maxCountB++;
                if(head == 0){
                    head = headR;
                    tail = headR;
                    headR = pointsB[headR].where;
                }
                else{
                    pointsB[tail].where = headR;
                    tail = headR;
                    headR = pointsB[headR].where;
                }
            }

        }
    }

    if(headL == 0){
        if(head != 0){
            pointsB[tail].where = headR;
        }else{
            head = headR;
            tail = headR;
        }
    }
    else{
        if(head != 0){
            pointsB[tail].where = headL;
        }else{
            head = headL;
            tail = headL;
        }
    }

    return head;
}


void doSorts(int number){
    int i;
    for(i = 1; i < (number + 1); i++){
    pointsA[i] = POINTS[i];
    pointsB[i] = POINTS[i];
    }
    mergesort(pointsA, 1, number-1);
    findMaximal(pointsA, number-1);
    printA(pointsA, number);
    int head = FindMaxB(1, number-1);
    printB(head);
}

void setC(){

    C[set].sortTime = 0;
    C[set].sortCount = 0;
    C[set].maxCountA = 0;
    C[set].maxNumA = 1;
    C[set].maxCountB = 0;
    C[set].maxTimeB = 0;
    C[set].maxNumB = 0;
}

void printEnd(){
    int i;

    printf("Statistics for the %d iterations:\n\n", set);
    printf("Iter SortCt sortTime MaxCtA maxTimeA SortCt+MaxCtA MaxCtB maxTimeB\n" );
    printf("------------------------------------------------------------------\n");
    for(i=0; i<set; i++){
        int srtMax = C[i].sortCount + C[i].maxCountA;
        printf("  %d  %d   %d    %d     %d        %d      %d    %d\n", i, C[i].sortCount, C[i].sortTime, C[i].maxCountA, C[i].maxCountA, srtMax, C[i].maxCountB, C[i].maxTimeB);
    }
}


int main(int argc, char *argv[]) {

    int numbers = 0;
    FILE* pFile;
    char * pch;
    char buffer[BUF_LINE];
    int where = 1;
    pFile = fopen("points1.txt", "r");

    while(fgets (buffer, BUF_LINE, pFile) != NULL){
        if (numbers == 0){
            numbers = atoi(buffer);
            if(where != 1){
                doSorts(where);
            }
            where = 1;
            setC();
        }
        else{
            pch = strtok(buffer, " ");
            float x = atof(pch);
            pch = strtok(NULL, " ");
            float y = atof(pch);
            POINTS[where].where = where;
            POINTS[where].x = x;
            POINTS[where].y = y;
                numbers--;
                where++;
        }
    }
    doSorts(where);


    printEnd();


	return 0;
}