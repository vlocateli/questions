#include "../include/types.h"
#include "../include/vector.h"
#include "../include/process.h"
#define NUM_VEC 2
int main( int argc, const char ** const argv )
{
	srand(time(0));
	int shm_id, status;
	Vector **shm;
	pid_t pid;

	if( argc != 2 ){ 
		USAGE
	}
	byte *end = 0;
	const u64 N  = strtol(argv[1],&end, 10);
	shm_id = shmget(IPC_PRIVATE, NUM_VEC * sizeof(Vector), IPC_CREAT | 0666 );
	if( shm_id < 0 ){
		perror("shmget\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout,"servidor recebeu a memoria compartilhada de %lu inteiros de 64 bits sem sinal\n",N);
	shm = (Vector **) shmat(shm_id, NULL, 0); 
#if 0
	if( shm == -1 ){
		perror("shmat\n");
		return EXIT_FAILURE;
	}
#endif
	puts("servidor anexou a memoria compartilhada");
#if 0 
	for( usize i = 0; i < NUM_VEC; i++ ){
		shm[i] = malloc(sizeof(Vector));
	}
#endif
	for( usize i = 0; i < NUM_VEC; i++ ){
		construct_with_initial_value( shm[i], N,1 );
	}
	puts("servidor construiu 2 vetores e preencheu-os com números aleatórios");
	for( usize i = 0; i < NUM_VEC; i++ ){
		print_vector(shm[i]);
	}
	puts("servidor vai fazer um fork");
	T sum = 0;
	pid = fork();
	if( pid < 0 ){
		perror("fork\n");
		return EXIT_FAILURE;
	}
	else if( !pid ){
		sum = client_process( shm[0], shm[1] );
		return EXIT_SUCCESS;
	}
	wait(&status);
	puts("servidor detectou que seu filho terminou");
	fprintf(stdout,"soma vetorial = %lu\n",sum);
	for( usize j = 0; j < NUM_VEC; j++ ){
		destroy_vector( shm[j] );
	}
	shmdt( (void *) shm);
	puts("servidor desanexou sua memoria compartilhada");
	shmctl( shm_id, IPC_RMID, NULL);
	puts("servidor removeu sua memoria compartilhada");
	return EXIT_SUCCESS;
}
