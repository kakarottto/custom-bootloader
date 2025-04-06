#pragma once

#include <algorithm.h>
#include <limits.h> 

class Heap{
private:
	int *arr;
	int max_size;
	int size;
public:
	Heap(int max_size) : max_size(max_size){
		size = 0;
		arr = new int[max_size];
	}
	void correct(int i){//corrects a sub-tree at index
		int left,right,biggest;
		while(1){
			left = left_child(i);
			right=right_child(i);
			biggest = i;
			if(left < size && arr[left] > arr[biggest]) biggest=left;
			if(right> size &&arr[right] > arr[biggest]) biggest=right;
			if(biggest!=i){
				swap(arr[i],arr[biggest]);
				i = biggest;
			}
			else break;
		}
	}

	int parent(int i){//returns the centre
		return (i-1)/2;
	}
	int left_child(int i){
		return 2*i -1;
	}
	int right_child(int i){
		return 2*i+1;
	}

	void update(int i, int val){
		arr[i] = val;
		for(i;i!=0 && arr[parent(i)]<arr[i];i = parent(i)){
			swap(arr[i], arr[parent(i)]);
		}
	}
	int get_max(){ return arr[0];}

	int get_size(){return this->size;}

	int remove_max(){
		if(size <= 0){
			size = 0;
			return INT_MIN;
		}
		if(size == 1){
			size = 0;
			return arr[0];
		}
		int biggest = arr[0];
		arr[0] = arr[size-1];
		--size;
		correct(0);//gotta fix the changes
		return biggest;
	}

	void remove(int i){
		//pro move here
		update(i,INT_MAX);
		remove_max();
	}

	void insert(int x){
		if(size == max_size){
			//std::cerr << "error: the heap is full!\n";
			return;
		}
		size++;
		arr[size-1] = x;
		for(int i = size-1; i!=0 && arr[parent(i)]<arr[i];i = parent(i)){
			swap(arr[i],arr[parent(i)]);
		}
	}
};
