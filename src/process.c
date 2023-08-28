#include "../include/process.h"
T client_process( Vector * m, Vector *n){
	puts("processo cliente comecou");
	puts("processo cliente achou ");
	u64 sum = dot_product(m, n);
	fprintf(stdout,"produto vetorial\nsoma: %lu\n",sum);
	puts("saindo processo cliente");
	return sum;
}
