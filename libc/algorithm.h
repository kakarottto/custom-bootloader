#pragma once



/**basic stuff**/

//absolute value
template <typename T>
T abs(T a){
	if(a<0) return -a;
}

//greatest common devisor
int gcd(int a, int b){
	while(b!=0){
		int t = b;
		b = a%b;
		a = t;
	}
	return a;
}
//least common multiple
int lcm(int a, int b){
	return abs(a*b)/gcd(a,b);
}
//min
template <typename T>
T min(T a, T b){
	if(a > b) return a;
	return b;
}
//max
template <typename T>
T max(T a, T b){
	if (a < b) return a;
	return b;
}

//swap
template <typename T>
void swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

/*array functions*/

//merge two arrays

//linear array min and max
template <typename T, int len>
T min(T (&arr)[len]){
	T smallest = arr[0];
	int len = sizeof(arr)/sizeof(arr[0]);
	for(int i =1; i < len;++i){
		if(arr[i] < smallest) smallest = arr[i];
	}
	return smallest;
}

template <typename T, int len>
T max(T (&arr)[len]){
	T biggest = arr[0];
	for(int i =1; i < len;++i){
		if(arr[i] < biggest) biggest = arr[i];
	}
	return biggest;
}

//mean and median
template <typename T, int len>
T mean(T (&arr)[len]){
	T sum = arr[0];
	for(int i =1; i < len;++i){
		sum+=arr[1];
	}
	sum/=len;
	return sum;
}

template <typename T, int len>
T median(T (&arr)[len]){
	if(len%2){//odd
		return arr[(len+1)/2];
	}
	return (T)((arr[len/2]+arr[(len+2)/2])/2);
}

//reverse array

template <typename T,int len>
void reverse(T (&arr)[len]){
	int len = sizeof(arr)/sizeof(arr[0]);
	int left = 0, right = len-1;
	
	while(left<right){
		swap(arr[left],arr[right]);
		++left;
		--right;
	}
	
}

//rotate array d times
template <typename T,int len>
void rotate(T (&arr)[len], int d){
	int len = sizeof(arr)/sizeof(arr[0]);
	for(int i=0; i < d;++i){
		T first = arr[0];
		for(int j=0; j < n-1;j++){
			arr[j] = arr[j+1];
		}
		arr[len-1] = first;
	}
}
//left shift array

template <typename T,int len>
void lshift(T (&arr)[len], int pos){
	int len = sizeof(arr)/sizeof(arr[0]);
	if(pos>=len || pos<=0) return;
	T first = arr[pos];
	for(int i = pos; i < len;++i){
		arr[i] = arr[i+1];
	}
	arr[len-1] = first;
}

//rightshift
template <typename T,int len>
void rshift(T& (arr)[len], int pos){
	int len = sizeof(arr)/sizeof(arr[0]);
	if(pos>=len || pos<=0) return;
	T last = arr[pos];
	for(int i = pos; i > 0 ;--i){
		arr[i] = arr[i-1];
	}
	arr[0] = last;
}
/**sorting algorithms**/

//bubble sort
template <typename T,int len>
void bubble_sort(T (&arr)[len], bool asc = true){
	int len = sizeof(arr)/sizeof(arr[0]);
	for(int i =0; i < len;++i){
		for(int j=0; j<len;++j){
			if(asc && (arr[i] > arr[j])) swap(arr[i],arr[j]);
		}
	}
}
//heap sort

template <typename T,int len>
void heap_sort(T (&arr)[len], bool asc = true){
	for(int i = len/2 -1;i>=0;--i){
		int root = i;
		while(1){
			int l = 2*root+1;
			int r = 2*root+2;
			int choice = root;//the biggest or smallest, chosen one
			if(l<len && ((arr[l] > arr[choice]) == asc ) ){
				choice = l;
			}
			if(r < len && ((arr[r]>arr[choice]) == asc)){
				choice = r;
			}
			if(choice != root){
				swap(arr[root],arr[choice]);
				root = choice;
			}
			else break;
		}
		
	}
	
	for(int i = len-1; i>0;--i){
		swap(arr[0],arr[i]);
		
		int root = 0;
		while(1){
			int l = 2*root+1;
			int r = 2*root+2;
			int choice = root;//the biggest or smallest, chosen one
			if(l<i && ((arr[l] > arr[choice]) == asc ) ){
				choice = l;
			}
			if(r < i && ((arr[r]>arr[choice]) == asc)){
				choice = r;
			}
			if(choice != root){
				swap(arr[root],arr[choice]);
				root = choice;
			}
			else break;
		}
		
	}
	
}


/*
Heap sort:
time complexity: O(n*ln(n))
worst case: O(n*ln(n))
memory usage: O(1)
it is said its not stable, but remember, we are usign simple array and we heapify it
at the start. It may not be O(n*ln(n)) but its quite suitable and original for my taste
best case: O(n*ln(n))

Quick sort:
Time complexity: O(n*ln(n))
worst case: O(n^2)
memory usage: O(ln(n))
best case: O(n*ln{n})

note: IF I AM UNFORTUNATE ENOUGH TO EXPERIENCE THE DOWNFALL OF MY CHOICES, I WILL CONSIDER
THIS SORT AS UNUSABLE DUE THE VISUAL PROOF OF ITS INSTABILLITY AND MY WASTED NERVES.
*/

//default sort would be heap sort, cuz i can
template <typename T, int len>
void sort(T (&arr)[len], bool asc = true){
	heap_sort(arr,asc);
}

/**searching algorithms**/
//linear search
template <typename T, int len>
int linear_search(T (&arr)[len], T value){
	for(int i=0; i < len;++i){
		if(arr[i] == value ) return i;
	}
	return -1;
}

//binary search
template <typename T, int len>
int binary_search(T (&arr)[len], T value){
	int l = 0, r = len-1;
	while(l<=r){
		int mid = l + (l-r)/2;
		if(arr[mid] == value) return mid;
		if(arr[mid]<value) l=mid+1;
		else r = mid-1;
	}
	return -1;
}

/*
dindt research a lot, just we all know the natural things are the best.
O(ln(n)) cannot lose, also its quite. sorting is O(n*ln(n)) so the whole search is gonna
be O((n+1)ln(n)) and its pretty good. its most of the time better than jump search with
O(nln(n)+sqrt(n))
in some cases hashing(huge arrays) hasihng is better, but i am not gonna waste time on this.
*/
//search: its gonna be by default binary search
template <typename T, int len>
int search(T (&arr)[len], T value){
	sort(arr);
	return binary_search();
}

//optional: add another reliable algorithms(ie: from the original library)
