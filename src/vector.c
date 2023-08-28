#include "../include/vector.h"
#define FILL_WITH_RANDOM 1
#ifdef FILL_WITH_RANDOM  
#define RAND_NUMBER(min,max)\
	((rand() % (int) (((max) + 1) - (min))) + (min))
#endif
FILE *fp = NULL; 
#define MALLOC_LOG(x,fp) fwrite(x,sizeof(x),1,fp);
void construct_vector( Vector *vec, const u64 size){
	if( !vec ){
		return;
	}
	vec->m_data = malloc(sizeof(T) * size);
	vec->m_size = size;
	
}

void construct_with_initial_value( Vector * vec, const u64 size,
		const T value){
	fp = fopen("./allocations.txt","w");
	if(!vec){
		vec = malloc(sizeof(Vector));
	}
	if(!vec){
		perror("malloc\n");
		exit(1);
	}
	vec->m_data = malloc( sizeof(T) * size );
	vec->m_size = size;
	if( !vec->m_data ){
		perror("malloc");
		exit( EXIT_FAILURE );
	}
	#ifdef FILL_WITH_RANDOM
	(void) value;
	for( usize i = 0; i < vec->m_size; i++ ){
		int n = RAND_NUMBER(0,1024);
		vec->m_data[i] = n;
	}
	#else
	for( usize i = 0; i < vec->m_size; i++ ){
		vec->m_data[i] = value;
	}
	#endif
}

void destroy_vector( Vector *vec ){
	free( vec->m_data );
	vec->m_data = NULL;
	vec->m_size = 0;
}

void print_vector( Vector const *vec ){
	if(vec == NULL){
		fprintf(stderr,"AVISO: Tentando desreferenciar um ponteiro nulo\n");
		exit(0);
	}
	if(vec->m_data != NULL){
		for( usize i = 0; i < vec->m_size; i++ ){
			fprintf(stdout, "%ld ", vec->m_data[i]);
		}
		puts("");
	}
}

T dot_product( Vector const *m, Vector const *n){
	if( m->m_size != n->m_size ){
		fprintf(stderr,"ERROR: vetores de tamnhos diferentes\n");
		exit(1);
	}
	T sum = 0;
	for( usize i = 0; i < m->m_size; i++){
		sum += m->m_data[i] * n->m_data[i];
	}
	return sum;
}
