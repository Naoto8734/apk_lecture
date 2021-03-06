#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count_ave = 0;
double time_ave = 0;

void swap( int *xp, int *yp ){
	int p = *xp;
	*xp = *yp;
	*yp = p;
}

void printData( int size, int data[] ){
	int i;
	for ( i = 1; i <= size; i++ )
		printf( "%d ", data[i] );
	printf( "\n" );
}

void printPlot( int size, int data[] ){
	int i, j;
	for ( i = 1; i <= size; i++ ) {
		printf( "%5d:", i );
		for ( j = 0; j < data[i]; j++ ) {
			printf( "%c", '*' );
		}
	printf( "\n" );
	}
}

void downHeap(int heap[], int leaf, int root){
	int i;
	i = root * 2;
	while (i <= leaf){
		if ( (i<leaf) && (heap[i+1]>heap[i]) ) i++;
		if (heap[root] >= heap[i]) break;
		swap(&heap[root],&heap[i]);
		count_ave++;
		root = i;
		i = root * 2;
	}
}

void heapSort( int n, int heap[] ){
	int leaf, root;

	/* ボトムアップでヒープを作成 */
	leaf = n;
	root = n/2;

	while( root > 0){
		downHeap(heap, leaf, root);
		#ifndef TIME
		printf("root = %2d: ", root);
		printData(n, heap);
		#endif
		root--;
	}
	#ifndef TIME
	printf("heap: ");
	printData(n, heap);
	#endif

	while(leaf > 0){
		#ifndef TIME
		printf("leaf = %2d: ", leaf);
		#endif
		swap(&heap[1], &heap[leaf]);
		count_ave++;
		leaf--;
		downHeap(heap, leaf, 1);
		#ifndef TIME
		printData(n, heap);
		#endif
	}
}

void process(int size){
	int *datap;
	int i;
	clock_t c1, c2;

	/* データ領域の確保 */
	if ( NULL == ( datap = ( int * ) calloc( size+1, sizeof( int ) ) ) ) {
		fprintf( stderr,"ERROR:メモリ領域が確保できませんでした．\n" );
		//return EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}

	/* データを 1, 2, 3, ..., size  で初期化する */
	/*for ( i = 1; i <= size; ++i ) {
		datap[i] = i;
	}*/
	
	/* データをsize回，ランダムに要素を入れ替える */
	/*for ( i = 0; i < size; ++i ) {
		swap( &datap[rand(  ) % size+1], &datap[rand(  ) % size+1] );
	}*/

	/* データを size, size-1, size-2, ..., 0  で初期化する */
	for ( i = 1; i <= size; ++i ) {
		datap[i] = size-i+1;
	}

	/* ソート前のデータを出力する */
	#ifndef TIME
	printf( "ソート前のデータ:\n" );
	printData( size, datap );
	printPlot( size, datap );
	#endif

	/* ソート */
	//printf("%d,",size);
	c1 = clock(  );
	heapSort( size, datap );
	c2 = clock(  );
	//printf("%d,",count_ave);
	//printf( "sort time = %f [s]\n",( double ) ( c2 - c1 ) / CLOCKS_PER_SEC );
	//printf( "%f\n",( double ) ( c2 - c1 ) / CLOCKS_PER_SEC );
	time_ave += ( double ) ( c2 - c1 ) / CLOCKS_PER_SEC;
	
	/* ソート後のデータを出力する */
	#ifndef TIME
	printf( "ソート後のデータ:\n" );
	printData( size, datap );
	printPlot( size, datap );
	#endif

	/* メモリ領域を解放する */
	free( datap );
}

int main(void){
	srand( ( unsigned ) time( NULL ) );
	int j;
	for (j=5000;j<=30000;j+=1000){
		count_ave = 0;
		time_ave= 0;
		process(j);
		printf("%d,",j);
		printf("%d,",count_ave);
		printf( "%f\n",time_ave);
	}
	return EXIT_SUCCESS;
}
