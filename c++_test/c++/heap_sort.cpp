#include <iostream>
#include <algorithm>

using namespace std;

void swap1(int& a,int& b){
    int temp = a;
    a = b;
    b = temp;
}

void adjust(int arr[],int dad,int len){
    int son = 2 * dad + 1;
    while(son <= len){
        if(son+1 <= len && arr[son] < arr[son+1])
            son++;
        if(arr[son] < arr[dad])
            return;
        else{
            swap1(arr[son],arr[dad]);
            dad = son;
            son = 2 * dad + 1;
        }
    }
}

void heap_sort(int arr[],int len){
    if(len <= 0) return;
    for(int i = len/2; i >= 0;--i)
        adjust(arr,i,len);
    for(int i = len; i > 0;--i){
        swap(arr[0],arr[i]);
        for(int j = 0;j < 6;++j)
            cout << arr[j] << " ";
        cout << endl;
        adjust(arr,0,i-1);
    }
}

int main(){
    int arr[6] = {83,27,38,9,96,11};
    cout << 5/2<<endl;
    heap_sort(arr,5);
    for(int i = 0;i < 6;++i)
        cout << arr[i] <<" ";
    cout << endl;
    return 0;
}
