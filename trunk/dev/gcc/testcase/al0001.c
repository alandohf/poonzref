/**
1.选择排序
http://en.wikipedia.org/wiki/Selection_sort
http://stackoverflow.com/questions/4601057/why-is-selection-sort-not-stable
http://bytes.com/topic/c/answers/221638-using-clock-measure-run-time
http://apps.hi.baidu.com/share/detail/8540616

!!!
http://baike.baidu.com/view/1516611.htm
!!!

**/

#include <io.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include       <dos.h>    

void selection_sort (int *a, int n) {
    int i, j, m, t;
    for (i = 0; i < n; i++) {
        for (j = i+1, m = i; j < n; j++) {
            if (a[j] < a[m])
                m = j;
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}
 

void selection_sort_desc (int *a, int n) {
    int i, j, m, t;
    for (i = 0; i < n; i++) {
        for (j = i+1, m = i; j < n; j++) {
            if (a[j] > a[m]) // a[j] 索引第i+1个元素
                m = j;
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}

int main () {
	clock_t start,end;
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    selection_sort(a, n);
	int i ;
	for ( i = 0 ; i < n ; i++){
		printf("a[%d]:%d\n",i,*(a+i));
	}

		start=clock();

    selection_sort_desc(a, n);
	for ( i = 0 ; i < n ; i++){
		printf("a[%d]:%d\n",i,*(a+i));
	}

	Sleep(150);
	end=clock();
		printf("The time was: %u\n", start);     
		printf("The time was: %u\n", end);     
		printf("The time was: %f\n", (double)(end - start) );     
		//printf("Elapsed time:%f secs.\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}

 


 //// 
 //// int main(int argc, char *argv[]) {
 //// 
 //// 	
 //// 	/* a[0] to a[n-1] is the array to sort */
 //// int iPos;
 //// int iMin;
 ////  
 //// /* advance the position through the entire array */
 //// /*   (could do iPos < n-1 because single element is also min element) */
 //// for (iPos = 0; iPos < n; iPos++) {
 ////     /* find the min element in the unsorted a[iPos .. n-1] */
 ////  
 ////     /* assume the min is the first element */
 ////     iMin = iPos;
 ////     /* test against all other elements */
 ////     for (i = iPos+1; i < n; i++) {
 ////         /* if this element is less, then it is the new minimum */  
 ////         if (a[i] < a[iMin]) {
 ////             /* found new minimum; remember its index */
 ////             iMin = i;
 ////         }
 ////     }
 ////  
 ////     /* iMin is the index of the minimum element. Swap it with the current position */
 ////     if ( iMin != iPos ) {
 ////         swap(a, iPos, iMin);
 ////     }
 //// }
 //// 	
 //// 
 //// 	return 0;
 //// }
 //// 


