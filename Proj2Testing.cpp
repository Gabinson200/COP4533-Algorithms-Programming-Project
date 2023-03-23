
#include <iostream>
#include <functional>
using namespace std;

//Instantiates block of requested size, no larger than 65536 words; cleans up previous block if applicable.
void initialize(size_t sizeInWords) {
	int word_size = 4;
	if (sizeInWords <= 65536) {
		//a dynamically allocated array of pointers holding the beginning address of each word
		int** word_pointers = new int* [sizeInWords];

		//intialize the actual memory of size word_size*sizeInWords		
		int* mem = new int[word_size * sizeInWords];
		//sets all values in mem array to 0
		for (int i = 0; i < word_size * int(sizeInWords); i++) {
			mem[i] = 0;
			//for every word_size'th have a pointer point to it which is then stored in the word_pointers_array
			if (i % word_size == 0) {
				word_pointers[i / 4] = &mem[i - word_size];
				cout << "Pointers point to elements starting at " << i - word_size << " ending with " << i << " and first element with value " << *word_pointers[i / 4] << endl;
			}
		}
	}
	else {
		cout << "Too many word allocated to memory" << endl;
	}
}

int main() {
	size_t n = 5;
	initialize(n);
	return 0;
}