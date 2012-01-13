/**
1.—°‘Ò≈≈–Ú
http://en.wikipedia.org/wiki/Selection_sort
http://stackoverflow.com/questions/4601057/why-is-selection-sort-not-stable
**/

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void selection_sort (int *a, int n) {
    int i, j, m, t;
    for (i = 0; i < n; i++) {
        for (j = i, m = i; j < n; j++) {
            if (a[j] < a[m])
                m = j;
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}
 
int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    selection_sort(a, n);
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