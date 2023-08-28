#if defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__) || defined (MSC_VER)
#error "ERRO: Esse programa roda apenas em sistemas operacionais Unix\n"
#endif
#include "../include/types.h"
#include "../include/vector.h"
#include "../include/process.h"
#define NUM_VEC 2
#define READ 0
#define WRITE 1
int main( int argc, const char ** const argv )
{
	srand(time(0));
	int shm_id;
	Vector *shm = NULL;
	pid_t pid;
	int  fd[2] = {0};

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
	shm = shmat(shm_id, NULL, 0); 
	if( *(int *) shm == -1){
		perror("shmat\n");
		return EXIT_FAILURE;
	}
	puts("servidor anexou a memoria compartilhada");
	for( usize i = 0; i < NUM_VEC; i++ ){
		construct_with_initial_value( &shm[i], N,1 );
	}
	puts("servidor construiu 2 vetores e preencheu-os com números aleatórios");
	for( usize i = 0; i < NUM_VEC; i++ ){
		print_vector(&shm[i]);
	}
	puts("servidor vai fazer um fork");
	pipe(fd);
	T sum = 0;
	pid = fork();
	if( pid < 0 ){
		perror("fork\n");
		return EXIT_FAILURE;
	}
	if( !pid ){
		close(fd[WRITE]);
		read(fd[READ],&sum,sizeof(sum));
		printf("soma (filho): %lu\n",sum);
		close(fd[READ]);
		_exit(EXIT_SUCCESS);
	}
	else{
		close(fd[READ]);
		sum = client_process( &shm[0], &shm[1] );
		write(fd[WRITE],&sum,sizeof(sum));
		printf("soma (pai): %lu\n",sum);
		close(fd[WRITE]);
	}
	puts("servidor detectou que seu filho terminou");
	for( usize j = 0; j < NUM_VEC; j++ ){
		destroy_vector( &shm[j] );
	}

	shmdt( (void *) shm);
	puts("servidor desanexou sua memoria compartilhada");
	shmctl( shm_id, IPC_RMID, NULL);
	puts("servidor removeu sua memoria compartilhada");
	return EXIT_SUCCESS;
}
