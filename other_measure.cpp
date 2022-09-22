#include <bits/stdc++.h>
using namespace std;
  
// Function for calculating
// the median
/**/
double findMedian(vector<int> a, long unsigned int n)
{
    // long unsigned int n = a.size();
    // If size of the arr[] is even
    if (n % 2 == 0) {
  
        // Applying nth_element
        // on n/2th index
        nth_element(a.begin(), a.begin() + n / 2, a.end());
  
        // Applying nth_element
        // on (n-1)/2 th index
        nth_element(a.begin(), a.begin() + (n - 1) / 2, a.end());
  
        // Find the average of value at
        // index N/2 and (N-1)/2
        return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
    }
  
    // If size of the arr[] is odd
    else {
  
        // Applying nth_element
        // on n/2
        nth_element(a.begin(),a.begin() + n / 2,a.end());
  
        // Value at index (N/2)th
        // is the median
        return (double)a[n / 2];
    }
}

void Median(int *a,int l,int r){
    if( l < r ){
        int i =l, j=r, x = a[l];
        while(i<j ){
            while(i<j && a[j]>=x){
                j--;
            }
            if(i<j){
                a[i] = a[j];
            }
            while(i<j && a[i]<x){
                i++;
            }
            if(i<j){
                a[j] = a[i];
            }
        }
        a[i] = x;
        Median(a,l,i-1);
        Median(a,i+1,r);
    }
}

float geometricMean(int arr[], int n)
{
    // declare sum variable and
    // initialize it to 1.
    float sum = 0;
 
    // Compute the sum of all the
    // elements in the array.
    for (int i = 0; i < n; i++){
        if(arr[i]==0){
            return 0;
        }
        sum = sum + log(arr[i]);
        // printf("a[%d]:%d sum is %f\n",i,arr[i],sum);

    }
    // compute geometric mean through formula
    // antilog(((log(1) + log(2) + . . . + log(n))/n)
    // and return the value to main function.
    sum = sum/ n;
 
    return exp(sum);
}

// Driver Code
int main()
{
    // Given array arr[]
    vector<int> arr = { 1, 3, 4, 2, 89, 58, 6,7, 4,3,89,1,24,72,27,33,592,22,44,2,7, 5, 8, 6 };
    // int arrg[] = { 1, 3, 4, 2, 89, 58, 6,7, 4,3,89,1,24,72,27,33,592,22,44,2,7, 5, 8, 6 };
    int arrg[] = {1,2,3,4,5,6,7,8,9,0};
    int n = sizeof(arrg) / sizeof(arrg[0]);
    int mid = sizeof(arrg) /sizeof(arrg[0])/2;
    Median(arrg,0,n);
    // Function Call
    cout << "Median (right) = "
        << findMedian(arr,arr.size())
        << " Median (mine) = "
        << arrg[mid]<<endl;

    for(const auto& i: arrg){
        cout <<i<<" ";
    }
    cout<<endl;
    for(int i = 0;i< n;i++){
        cout <<arrg[i]<<" ";
    }
    cout<<endl;
    cout << " Geometry = "
        << geometricMean(arrg,n)
        << endl;
    return 0;
}