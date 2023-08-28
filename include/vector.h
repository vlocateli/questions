#ifndef VECTOR_H
#define VECTOR_H 1 
#include "types.h"
#include<time.h>
#define USAGE\
	do{\
		fprintf(stderr,"ERROR: exercicio1 <tamanho vetor>\n");\
		exit(EXIT_FAILURE);\
	}while(0);

#define T u64
typedef struct{
	T *m_data;
	u64 m_size;
}Vector;

void construct_vector( Vector *vec, const u64 size);
void construct_with_initial_value( Vector * const vec, const u64 size,
		const T value);
void destroy_vector( Vector *vec );
void print_vector( Vector const *vec );
T dot_product( Vector const *m, Vector const *n);
void fill( Vector const *m, T min, T max );
#endif
