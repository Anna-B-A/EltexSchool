#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 1024

int main()
{
	int shmFdServer = shm_open("/server", O_RDWR, 0666);
	ftruncate(shmFdServer, SIZE);
	void* strForServer= mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shmFdServer, 0);

	sem_t* sem1 = sem_open("/sem1", O_RDWR|O_CREAT, 0666, 0);
	sprintf(strForServer, "Hi!");
	sem_post(sem1);

	int shmFdClient = shm_open("/client", O_RDWR, 0666);
	ftruncate(shmFdClient, SIZE);
	void* strForClient = mmap(0, SIZE, PROT_READ, MAP_SHARED, shmFdClient, 0);
	
	sem_t* sem2 = sem_open("/sem2", O_RDWR|O_CREAT, 0666, 0);
	sem_wait(sem2);
	printf("%s\n", strForClient);
	sem_post(sem2);

	sem_close(sem2);
    sem_unlink("/sem1");

	munmap(strForClient, SIZE);
    munmap(strForServer, SIZE);

	shm_unlink("/client");
	shm_unlink("/server");

	exit(EXIT_SUCCESS);
}
