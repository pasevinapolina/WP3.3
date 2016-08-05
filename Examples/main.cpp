#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bool.h> 

void runCurveInterp( char *inVolume1, int x1, int y1, int z1, int depth, 
		    int slice, int method_id, char *outVolume );

int main(int argc, char **argv) {
 bool flag = false;
 if ( argc ==17 ) {
   if ( (argv[1][0] == '-' && argv[1][1] == 'i' ) &&
	(argv[3][0]  == '-' && argv[3][1] == 'x' ) &&
	(argv[5][0]  == '-' && argv[5][1] == 'y' ) &&
	(argv[7][0]  == '-' && argv[7][1] == 'z' ) &&
	(argv[9][0]  == '-' && argv[9][1] == 'd' ) && 
	(argv[11][0] == '-' && argv[11][1] == 's' ) &&
	(argv[13][0] == '-' && argv[13][1] == 'a' ) &&
    (argv[15][0] == '-' && argv[15][1] == 'o' )) {

    runCurveInterp( argv[2], atoi(argv[4]), atoi(argv[6]), atoi(argv[8]), atoi(argv[10]), 
		    atoi(argv[12]), atoi(argv[14]), argv[16] );
    flag = true;
  
   }
 }

 if ( flag==false ) {
   std::cout<<"tcurveinterp require "<<std::endl;
   std::cout<<"\n-i    input image"<<std::endl;
   std::cout<<"\n-x    size of x"<<std::endl;
   std::cout<<"\n-y    size of y"<<std::endl;
   std::cout<<"\n-z    size of z"<<std::endl;
   std::cout<<"\n-d    depth"<<std::endl;   
   std::cout<<"\n-s    processed slice (z coordinate)"<<std::endl;
   std::cout<<"\n-a    interpolation method (0-linear, 1-cubic, 2-spline, 3-splineTK)"<<std::endl;
   std::cout<<"\n-o    output image"<<std::endl;
   std::cout<<"\nExample: tcurveinterp -i curve.raw -x 256 -y 256 -z 100 -d 16 -s 0 -a 0 -o interp_curve.raw"<<std::endl;
 }

}// End main()
