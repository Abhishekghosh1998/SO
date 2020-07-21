/*
	The program below uses a single bit to represent a matrix entry. It
	is based on the row major representation of a matrix. What we do here
	is that, according to our memory requirement we create a linear array
	(1D array) of bytes and these bytes are allocated in a contiguous 
	manner. Now using some mathematical calculations we can manipulate a 
	particular bit within a byte which acts as the entry in the matrix...
	
	Moreover the implementation does not depend on the endianness of 
	processor
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define BYTE_SIZE (sizeof(BYTE)*8) //the number of bits in one BYTE 
typedef unsigned char BYTE; //renaming unsigned char as BYTE

struct Byte_Matrix
{
	BYTE* data;
	int width;
	int height;
};

struct Byte_Matrix makeByteMatrix(int row, int col)
{
	int length=ceil((row*col)/BYTE_SIZE);
	struct Byte_Matrix bm;
	bm.data=(BYTE*)malloc(sizeof(BYTE)*length);
	bm.width=col;
	bm.height=row;
	return bm;
}

void set_bit(BYTE* data,int pos,int val)
{
	int index=pos/BYTE_SIZE;//which byte to use
	int offset=pos%BYTE_SIZE;//which bit in the 'index'th byte to use
	if(val)
		data[index]=data[index]|(1<<offset);
	else
		data[index]=data[index]& ~(1<<offset);
}

int test_bit(BYTE* data,int pos)
{
	int index=pos/BYTE_SIZE;//which byte to use
	int offset=pos%BYTE_SIZE;//which bit in the 'index'th byte to use
	return (data[index]&(1<<offset))!=0;	//this step is important such
		//either 1 or 0 is returned,note that we can't test equality
		//for 1 as the term on the LHS is '1' in a particular position
		//of BitVector which might evaluate to something which is power
		//of 2
}

void set_matrix_bit(struct Byte_Matrix* bm,int i,int j,int val)
{
	int pos=i*bm->width+j;
	set_bit(bm->data,pos,val);
}

void display_bit_matrix(struct Byte_Matrix* bm)
{
	int i,j;
	for(i=0;i<bm->height;i++)
	{
		for(j=0;j<bm->width;j++)
			printf("%d\t",test_bit(bm->data,i*bm->width+j));
		printf("\n");
	}
}

int main()
{
	printf("ENTER THE NUMBER OF ROWS : " );
	int r;
	scanf("%d",&r);
	printf("ENTER THE NUMBER OF COLUMNS : ");
	int c;
	scanf("%d",&c);
	struct Byte_Matrix bm=makeByteMatrix(r,c);
	printf("ENTER THE ELEMENTS INTO THE MATRIX \n");
	int i,j;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			printf("A[%d][%d] : ",i,j);
			int data;
			scanf("%d",&data);
			set_matrix_bit(&bm,i,j,data);
		}
	printf("\n");
	display_bit_matrix(&bm);
	free(bm.data);
}
 

