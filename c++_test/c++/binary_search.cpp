#include <iostream>
using namespace std;

int binary_search(int arr[],int b,int e,int dst)
{
    if(b <= e){
        int mid = (b + e)/2;
        if(arr[mid] > dst)
            e = mid - 1;
        else if(arr[mid] < dst)
            b = mid + 1;
        else
            return mid;
        return binary_search(arr,b,e,dst);
    }else
        return -1;
}

int binary_search_nonrec(int arr[],int b,int e,int dst)
{
    while(b <= e)
    {
        int mid = (b + e)/2;
        if(arr[mid] > dst)
            e = mid - 1;
        else if(arr[mid] < dst)
            b = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main()
{
    int arr[5] = {1,2,3,4,5};
    int ind = binary_search_nonrec(arr,0,4,7);
    cout << ind << endl;
    return 0;
}
