#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "bitset.h"


// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size)
{
    struct bitset*result;
    int size_in_words;
	int i;

    size_in_words = size/sizeof(unsigned int)*8;

    result = malloc(sizeof(struct bitset));

    if(size%(sizeof(unsigned int)*8)!=0){
        size_in_words++;
    }

    result->data = malloc(sizeof(unsigned int) * size_in_words);

    for(i = 0; i<size_in_words;i++){
        result->data[i] = 0;
    }
    result->size_in_bits = size;
    result->size_in_words = size_in_words;

    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this)
{
    int size;
    size  = this->size_in_bits;
    return size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this)
{
    int i;
    int noOfItemsInSet = 0;
    for(i = 0; i < this->size_in_bits; i++){
        if(this->data[i] != 0){
            noOfItemsInSet++;
        }
    }
    return noOfItemsInSet;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item)
{
    int inSet = 0;
    if(this->data[item] == 1){
        inSet = 1;
    }
    return inSet;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item){
    if(this->data[item] == 0) {
        this->data[item] = 1;
    }
    }
// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item)
{
    if(item < 0){
        printf("Error cannot be less than 0");
    }
    if(item < bitset_size(this) && (this->data[item] == 1))
    {
            this->data[item] = 0;
        }
    
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
		  struct bitset * src2)
{
	int i;
    for(i = 0; i < src1->size_in_words; i++){
        if(src1->data[i] == 1 || src2->data[i] == 1)
        {
            dest->data[i] = 1;
        }
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
		      struct bitset * src2)
{
	int i;
    for(i = 0; i < src1->size_in_words; i++){
        if(src1->data[i] == 1 && src2->data[i] == 1)
        {
            dest->data[i] = 1;
        }
    }
}
/*void add_chars_to_set(struct bitset * this, char * s)
{
    int i;
    for (i = 0; s[i]!=0; i++) {
        unsigned char temp = s[i];
        bitset_add(this, temp);
    }
}*/


// print the contents of the bitset
void bitset_print(struct bitset * this)
{
  int i;
  int size = bitset_size(this);
  for ( i = 0; i < size; i++ ) {
    if ( bitset_lookup(this, i) == 1 ) {
      printf("%d ", i);
    }
  }
  printf("\n");
}




