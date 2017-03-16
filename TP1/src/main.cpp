
#include "jpg.h"
#include "mnist.h"

float euclid(float* v1, float* v2){
	float eucl=0;
	for(int i=0; i<784; i++){
		eucl+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return eucl;
}

int main()
{


    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");

    for(int i=0; i<10000; i++) {
		float mine=-1;
		int nn;
        for(int j=0; j<10000; j++){
		float eucl = euclid(test_images[i], images[j]);
		if(eucl<mine || mine==-1){
			mine=eucl;
			nn=j;
			}
		}
		int inf = labels[nn];
		printf("%u\n", i);
        save_jpg(test_images[i], 28, 28, "%u/%04u.jpg", inf, i);
    }
    return 0;
}
