/* includes */
#include <iostream>
#include <cstring>
#include <vector>
#include <aInterpCurveLinear.h>
#include <aInputOutput.h>
#include <aPoint.h>

/** \fm getContour
* Scan the image in column direction. If a point of intensity bigger than threshold is reached,
* stop scanning for the column and store coordinates of this point in cont.
*/
template<class T,class U>
int getContour(aImage<T> &volume1, int slice, T threshold, std::vector<aPoint<U> > &cont) {
    int x = volume1.getSizeX();
    int y = volume1.getSizeY();
    int z = volume1.getSizeZ();
    long bandsize=x*y;

    if ( slice <0 || slice >= z ) {
        return 0;
    }

    cont.clear();
    T *p1=(T *)volume1.getPtr();
    
	bool containsX = false;

    for ( int i=0; i<x; i++ ) {
		containsX = false;
        for ( int j=0; j<y; j++ ) {
			if (!containsX) {
				T val = *(p1 + j*x + i);
				if (val >= (T)threshold) {
					aPoint<U> tmp(i, j, slice);
					cont.push_back(tmp);
					containsX = true;
				}
			}// end if
        }// end for i
    }// end for j
    return cont.size();
}// end getContour

/** \fm projectContourOnImage
* Assign contour points on the volume1 the intensity value fg.
*/
template<class T,class U>
int projectContourOnImage(aImage<T> &volume1, std::vector<aPoint<U> > &cont, T fg) {
   int x = volume1.getSizeX();
   int y = volume1.getSizeY();
   int z = volume1.getSizeZ();

   // floor coordinates
   int X,Y,Z;
   aPoint<U> P;

   int count = 0;
   for ( int i=0; i<cont.size(); i++ ) {
       P = cont[i];
       X = (int)(P.x+0.5);
       Y = (int)(P.y+0.5);
       Z = (int)(P.z+0.5);
       if ( X>=0 && X<x && Y>=0 && Y<y && Z>=0 && Z<z ) {
           volume1.elem(X,Y,Z) = fg;
           count ++;
       }
   } // end for
   return count;
}

/** \fm
* curve interpolation example
*/
void runCurveInterp( char *inVolume1, int x1, int y1, int z1, int depth, 
		    int slice, int method_id, char *outVolume ) {

 const char program[]="runInterpCurve";
 std::cout<<program<<" is running"<<std::endl;

 switch(depth) {
    case 8: { 
        std::cout<<"depth = 8"<<std::endl;
        aInterpCurve<float> *pInterpCurve = aInterpCurve<float>::make_interp(method_id);
        if ( pInterpCurve == 0 ) {
            std::cout<<"Cannot create a aInterpCurve object for the specified method id: "<<(int)method_id<<std::endl;
            return;
        }

        aImage<unsigned char> volume1( x1, y1, z1 );

        aInputOutput<unsigned char> ioObj;
        ioObj.readRaw( inVolume1, volume1 );

        std::cout<<"Make curve interpolation"<<std::endl;
        std::vector<aPoint<float> > cont;
        std::vector<aPoint<float> > interp_cont;
        unsigned char threshold = 128;
        if ( getContour(volume1, slice, threshold, cont) >0 ) {
            // Get interpolated curve
            pInterpCurve->make( cont, interp_cont );
            if ( !pInterpCurve->isOK() ) {
                std::cout<<pInterpCurve->getLastError()<<std::endl;
                return;
            }
        }
        // For simplicity reasons, write the contour to the image
        unsigned char curve_intensity = 255;
        projectContourOnImage(volume1, interp_cont, curve_intensity);
        std::cout<<"Write to file ..."<<std::endl;
        ioObj.writeRaw( outVolume, volume1 );

        // Clean memory
        delete pInterpCurve;

        std::cout<<"Done ... "<<std::endl;

    } break;
    default: {
        std::cout<<"ERROR: wrong data type"<<std::endl;
    }
 }// end switch

}// End runCurveInterp
