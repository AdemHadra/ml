
#include "jpg.h"
#include "mnist.h"
#include<limits.h>

float euclid(float* v1, float* v2){
	float eucl=0;
	for(int i=0; i<784; i++){
		eucl+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return eucl;
}

/*int lin_class(float *w, float *x){
	float d = 0;
	for(int  i=0; i<784; i++){
			d+= w[i] *x[i];
	}
	if(d>=0){
		return 1;
	}else{
		return -1;
	}
}*/


int main()
{

	const int K=10;
    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");	
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
//--------------------------------K-MEANS----------------------
	float a[K][784];
	float b[K][784];
	int* n=new int[K];
	
	for(int i=0;i<K;i++){
		n[i]=0;
		for(int j=0;j<784; j++){
			a[i][j]=(float)rand()*2/INT_MAX-1;
			b[i][j]=0;
		}
	}


	for(int t=0;t<1000;t++){
		for(int i=0; i<K;i++){
			n[i]=0;
			for(int j =0;j<784;j++)b[i][j]=0;
		}
		for(int i=0;i<60000;i++){
			printf("t=%u, i=%u \n", t, i);
			float argmin= -1;
			int winner=0;
			for(int k=0; k<K;k++){
				float dist=euclid(a[k],images[i]);
				if(dist<=argmin || argmin==-1){
					argmin=dist; winner=k;
				}
			}
			for(int j=0; j<784; j++) b[winner][j] += images[i][j];
			n[winner]++;
		}
		

		for(int k=0; k<K; k++){
			for(int j=0;j<784;j++){
				a[k][j]=b[k][j]/n[k];
			}
		}
		for(int k=0;k<K;k++){
			save_jpg(a[k],28,28, "%u/%u.jpg", k, t);
		}
	}
}		

	/*float err=0;
	float *w = new float[784];
	//STEP I : INITIALIZATION
	for(int i =0; i<784;i++){
		w[i]=(float)rand()*2/INT_MAX-1;
	}

	float gamma = 0.01;

	//STEP II : LEARNING
	for(int i=0; i<60000; i ++){
		// calcul du gradient (g= x*y si err, sinon  0)
		int predict = lin_class(w,images[i]);
		int verite=(labels[i] == 1) ? 1:-1;
		if(verite!=predict){
			printf("ERR \n");
			//w(t+1) = w(t)-gamma*y*x
			for(int j=0; j<784; j++) w[j] += gamma*verite*images[i][j];
		}
	}
	//STEP III : TEST
    for(int i=0; i<10000; i++) {
		int inf = lin_class(w, test_images[i]); ;
		printf("%u\n", i);
        save_jpg(test_images[i], 28, 28, "%u/%04u.jpg", inf, i);
		if((inf == 1 && test_labels[i]!=1)||(inf ==0 && test_labels[i]==1)){
			err++;
		}
	printf("Il y a %0.2f%% d'erreur. \n", (err*100)/i);
    }
	//printf("Il y a %0.2f %% d'erreur. \n", err);
    return 0;
}
*/

