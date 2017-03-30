
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

int lin_class(float *w, float *x){
	float d = 0;
	for(int  i=0; i<784; i++){
			d+= w[i] *x[i];
	}
	if(d>=0){
		return 1;
	}else{
		return 0;
	}
}

int main()
{


    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
	//float err=0;
	float *w = new float[784];
	for(int i =0; i<784;i++){
		w[i]=(float)rand()*2/INT_MAX-1;
	}
    for(int i=0; i<10000; i++) {
		int inf = lin_class(w, test_images[i]); ;
		printf("%u\n", i);
        save_jpg(test_images[i], 28, 28, "%u/%04u.jpg", inf, i);
		//if(inf != test_labels[i]){
			//err++;
		//}
	//printf("Il y a %0.2f%% d'erreur. \n", (err*100)/i);
    }
	//printf("Il y a %0.2f %% d'erreur. \n", err);
    return 0;
}
