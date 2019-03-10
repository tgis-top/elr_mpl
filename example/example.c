#include <stdio.h>
#include <stdlib.h>
#include "elr_mpl.h"

int main()
{
	elr_mpl_t mypool = ELR_MPL_INITIALIZER;
	elr_mpl_t mysubpool = ELR_MPL_INITIALIZER;
    void*  mem = NULL; 
	size_t len = 0;

	elr_mpl_init();	

	mypool = elr_mpl_create(NULL, 256, NULL, NULL);
	printf("%s\n","create a memory pool: mypool. It`s object size is 256.");

	mysubpool = elr_mpl_create(&mypool,128, NULL, NULL);
	printf("%s\n","create a sub memory pool of mypool, name is mysubpool.");

	mem = elr_mpl_alloc(&mysubpool);
	printf("%s\n","alloc a memory block form mysubpool. It`s object size is 128.");

	len = elr_mpl_size(mem);
	printf("the memory block size is %zd.\n",len);

	elr_mpl_free(mem);
	printf("give back the memory block to mysubpool.\n");

	mem = elr_mpl_alloc(&mypool);
	printf("%s\n","alloc a memory block form mypool.");

	len = elr_mpl_size(mem);
	printf("the memory block size is %zd.\n",len);

	elr_mpl_free(mem);
	printf("give back the memory block to mypool.\n");

	mem = elr_mpl_alloc_multi(NULL, 69);
	printf("alloc a random memory block of size 69.\n");

	len = elr_mpl_size(mem);
	printf("the actual memory block size is %zd.\n", len);

	mem = elr_mpl_alloc_multi(NULL, 2096);
	printf("alloc a random memory block of size 2096.\n");

	len = elr_mpl_size(mem);
	printf("the actual memory block size is %zd.\n", len);

	elr_mpl_destroy(&mypool);
	printf("destroy mypool.\n");

	printf("when mypool has destoryed, it`s sub pool, mysubpool, had %s destoryed.\n",
		elr_mpl_avail(&mysubpool) == 0?"also":"not");

	elr_mpl_finalize();

	getchar();
	return 0;
}

