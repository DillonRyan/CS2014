#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"

#define MAX_INT 2147483647
// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
  int i;
  struct huffcoder *result;
  result = malloc(sizeof(struct huffcoder));
  for(i = 0; i < NUM_CHARS; i++)
  {
    result -> freqs[i] = 0;
    result -> codes[i] = 0;
    result -> code_lengths[i] = 0;
  }
  result -> tree = malloc(sizeof(struct huffchar));
  return result;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
  unsigned char c;
  FILE *file;
  file = fopen(filename, "r");
  assert(file != NULL);
  c = fgetc(file); 
  while (!feof(file))
  {
      this -> freqs[c]++;
      c = fgetc(file); 
  }
  int i;
  //set chars with frequency 0 to 1
  for(i = 0; i < NUM_CHARS; i++)
  {
    if(this->freqs[i] == 0)
    {
      this->freqs[i] = 1;
    }
  }
  fclose(file); 
}
struct huffchar * compound(struct huffchar * node1, struct huffchar * node2, int index){
 struct huffchar *result;
  result = malloc(sizeof(struct huffchar));
  result -> freq = (node1 -> freq) + (node2 -> freq);
  result -> is_compound = 1;
  result -> u.compound.left = node1;
  result -> u.compound.right = node2;
  result -> seqno = index;
 return result;
}


void sort_list(struct huffchar ** list)
{
  int i, k, min, value, seqVal;
  for(i = 0; i < 2; i++)
  {
    value = MAX_INT;
    seqVal = MAX_INT;
    min = -1;
    for(k = i; k < NUM_CHARS; k++)
    {
      if((list[k] != NULL && list[k]->freq < value) 
            || (list[k] != NULL && list[k] -> freq == value && list[k]->seqno < seqVal))
      {
        min = k;
        value = list[k] -> freq;
        seqVal = list[k] -> seqno;
      }
    }
    struct huffchar * char1;
    char1 = list[i];
    list[i] = list[min];
    list[min] = char1;
  }
}


// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
  struct huffchar * list[NUM_CHARS];
  int i;
  for(i = 0; i < NUM_CHARS; i++)
  {
    list[i] = malloc(sizeof(struct huffchar));
    list[i] -> freq = this -> freqs[i];
    list[i] -> is_compound = 0;
    list[i] -> seqno = i;
    list[i] -> u.c = i;
  }
  int characters= NUM_CHARS;
  for(i = 0; i < NUM_CHARS - 1; i++)
  {
    sort_list(list);
    struct huffchar *tmp1 = list[0];
    struct huffchar *tmp2 = list[1];
    struct huffchar *result;
    result = compound(tmp1, tmp2, characters);
    list[0] = result;
    list[1] = NULL;
    characters++;
  }
  this->tree = list[0];
}

//recursive function to convert huffman tree into a table of huffman codes
void tree2table_recursive(struct huffcoder * this, struct huffchar * node, int path, int depth)
{
  if(node->is_compound == 1){
 path=path<<1;
 tree2table_recursive(this, node->u.compound.left, path, depth+1);
 path = path|1;
 tree2table_recursive(this, node->u.compound.right, path, depth+1);
 }
 else{
 unsigned char index = node->u.c;
 this->codes[index]=path;
 this->code_lengths[index]=depth;
}
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
unsigned int path = 0;
 int depth=0;
 if(this->tree != NULL){
 tree2table_recursive(this, this->tree, path, depth);
}
}


// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for ( i = 0; i < NUM_CHARS; i++ ) 
  {
    // put the code into a string
    //assert(this->code_lengths[i] < NUM_CHARS);
    for ( j = this->code_lengths[i]-1; j >= 0; j--) 
    {
      buffer[this->code_lengths[i]-1-j] = ((this->codes[i] >> j) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';
    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);;
  }
}


void huffcoder_encode(struct huffcoder * this, char * input_filename,
          char * output_filename) {
}
void huffcoder_decode(struct huffcoder * this, char * input_filename,
          char * output_filename) {
}