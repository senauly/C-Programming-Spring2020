#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    char letter;
    int freq;
    struct node *left,*right;
};

char* read_file(char *file,char *str, int *size);
void get_chars(char *str, char *characters, int size);
void get_frequency(char *str, char *characters, int *arr);
struct node* new_node(char character, int freq);
struct node* create_huffman(char *chr, int *freq, int size);
struct node *remove_node(struct node *Heap[], int *heap_size);
void get_codes(struct node *Root, int *arr, int top, char *str,int pattern[][15]);
void encode(int pattern[][15],char *str);
int find_char(char *str,char x);

void main(){
	int *frequency;
	char *characters;
	struct node* huffman = NULL;
	char *text;
	char *file = "reference.txt";
	int size = 0;
	int arr[100];
	int top = 0;
	char *str;

	text = read_file(file,text,&size);   //read file and get the how many char it has.//
	characters = (char *) malloc(size);  //allocate memory in the arrays according to the size of chars.//
	frequency = (int *) malloc(sizeof(int)*size);
	huffman = (struct node *) malloc(sizeof(struct node)*size);
	str = (char *) malloc(size);

	int pattern[size][15];
	
	get_chars(text,characters,size);  //get the chars list.//
	get_frequency(text,characters,frequency);  //get the frequency of each char.//
	
	huffman = create_huffman(characters,frequency,size);   //create huffman tree.//
	get_codes(huffman,arr,top,str,pattern);     //get the codes of each char.//

	for (int i = 0; i < size; ++i){                               //encryption of each char.//
		printf("%c: ",str[i] );
		int j = 0;
		while(pattern[i][j] == 0 || pattern[i][j] == 1){
			printf("%d",pattern[i][j]);
			j ++;
		}

		printf("\n");
	}
	
	encode(pattern,str);   //encoded message.//
	printf("\nMessage is encrypted.\n");
	
	free(frequency);
	free(characters);
	free(text);
	free(str);
}

char* read_file(char *file, char *str, int *size){
	FILE *fp;
	char temp;
	int i = 1;

	fp = fopen(file,"r");

	fscanf(fp,"%c",&temp);  //get the char.//
	str = (char *) malloc(1);  //allocate memory//
	str[0] = temp;
	
	while(!feof(fp)){
		fscanf(fp,"%c",&temp);
		str = (char *) realloc(str,(i+1));

		if(strchr(str,temp) == NULL) (*size)++;  //if char is not in the string we created, increase size.//

		str[i] = temp; 
		i++;
	}

	str[i-1] = '\0';

	return(str);
}

void get_chars(char *str, char *characters, int size){
	int k = 0;
	
	for (int i = 0; i < strlen(str); ++i){
		if(str[i] == '\n');  //ignore.//
		else if(strchr(characters,str[i]) == NULL){  //if char is not in the characters string.//
			characters[k] = str[i];   //add it.//
			k ++;

		}
	}

	characters[k] = '\0';
}

void get_frequency(char *str, char *characters, int *arr){
	int count = 0;
	int k = 0;
	for (int i = 0; i < strlen(characters); ++i){
		count = 0;
		for (int j = 0; j < strlen(str); ++j){    //count the frequency of each char.//
			if(characters[i] == str[j]) count++;
		}

		arr[k] = count;  //add frequencies to an array.//
		k++;
	}
}

struct node* new_node(char character, int freq){
	struct node* new = (struct node *) malloc(sizeof(struct node));  //create new node and assign its values.//
	
	new->letter = character;
	new->freq = freq;
	new->left = NULL;
	new->right = NULL;

	return(new);
}

struct node* create_huffman(char *chr, int *freq, int size){
	int heap_size = 1;
	int current;
	struct node *small1 = NULL,*small2 = NULL;
	struct node *Node = NULL;
	struct node *Heap[size];
	struct node *Root = NULL;
	struct node *temp = NULL;

	
	for (int i = 0; i < size; ++i){
		Node = new_node(chr[i],freq[i]);  //create new node.//
		Heap[heap_size] = Node;  //add the node to Heap.//
		current = heap_size; //current node we're on.//

		while(current > 1){ //when there's only one node there's no need to swap.//
			if(Heap[current]->freq < Heap[current/2]->freq){  //we're creating a min heap, so root should be smallest number. If root is not the smallest swap it.//
				temp = Heap[current/2];                       //root should be smaller then its left and right.//
				Heap[current/2] = Heap[current];
				Heap[current] = temp;

				current = current/2;
			}

			else break; //everything is ordered, break the loop.//
		}

		heap_size++;
	}

	while(heap_size != 1){  //until there's only one node left in the heap.//
		small1 = remove_node(Heap,&heap_size);  //get the smallest frequency.//
		small2 = remove_node(Heap,&heap_size);

		Root = (struct node *) malloc(sizeof(struct node));  //create new internal node.//
		Root->freq = small1->freq + small2->freq;  //we have create a new node with frequency equal to smallest 2 nodes.//
		Root->left = small1;  //root have left children first small node.//
		Root->right = small2; //root have right children second small node.//

		Heap[heap_size] = Root;
		current = heap_size;

		while(current > 1){  //adding the new created loop into heap.//
			if(Heap[current]->freq < Heap[current/2]->freq){  
				temp = Heap[current/2];
				Heap[current/2] = Heap[current];
				Heap[current] = temp;

				current = current/2;
			}

			else break;
		}

		heap_size++;
	}

	Root = small1;  //the last one is the root.//

	return(Root);
}

struct node *remove_node(struct node *Heap[], int *heap_size){
	int current = 1;
	int left,right,new = 0;
	struct node *temp = NULL;
	struct node *root = Heap[1]; //assign the first element of the heap to the root, because it's smallest.//

	Heap[1] = Heap[(*heap_size)-1]; //first element of heap now becomes the last element.//
	(*heap_size)--; //we removed a node so heap_size increased.//

	while(*heap_size != 1){
		left = current*2; //in huffman tree, location of left is double of root.//
		right = (current*2) +1; //location of right.//

		if(left <= *heap_size && Heap[current]->freq > Heap[left]->freq){  //check if left node exist and if it's bigger then curent node.//
			if(right <= *heap_size){ //check if right node exist.//
				if(Heap[left]->freq < Heap[right]->freq) new = left; //left side must be smaller.//
				else new = right;
			}

			else new = left;  //if there's no right node exist.// 
			
			temp = Heap[new];              //swap.//
			Heap[new] = Heap[current];
			Heap[current] = temp;
			current = new;
		}

		else break; //everything is ordered, break the loop.//
	}

	return(root);
}

void get_codes(struct node *Root, int *arr, int top, char *str,int pattern[][15]){ 
    static int count = 0;
    int i;
    if (Root->left != NULL){ //left side is 0.//
        arr[top] = 0; 
        get_codes(Root->left, arr, top + 1,str,pattern); //increase array element.//
    } 
  
    if (Root->right != NULL){  //left side is 1.//
        arr[top] = 1; 
        get_codes(Root->right, arr, top + 1,str,pattern); 
    } 
  
    if (Root->left == NULL && Root->right == NULL){ //if it's a leaf node
        str[count] = Root->letter;  //add the letter at a string.//
    	for (i = 0; i < top; ++i){
    		pattern[count][i] = arr[i];      //add its pattern to 2D array.//
    	}

    	pattern[count][i+1] = 5;  //to specify its end.//
		count ++;
    } 
}

//Prints the last char's code twice, I couldn't fix it.//
void encode(int pattern[][15],char *str){
	FILE *fp;
	FILE *output;
	char x;
	int loc;
	int j = 0;

	fp = fopen("message.txt","r");
	output = fopen("encoded.txt","w"); //I couldn't make .dat file.//

	while(!feof(fp)){
		fscanf(fp,"%c",&x);      //get the char//
		loc = find_char(str,x);  //find it's location at the string which filled with huffman tree.//

		j = 0;
		while(pattern[loc][j] == 0 || pattern[loc][j] == 1){  //get the pattern at the loc we found.//
			fprintf(output,"%d",pattern[loc][j]);   //print it to the file.//
			j++;
		}
	}

	fclose(fp);
	fclose(output);
}

int find_char(char *str,char x){
	int result;

	for (int i = 0; i < strlen(str); ++i){   //find the location of the char in a string.//
		if(str[i] == x) result = i;
	}

	return(result);
}