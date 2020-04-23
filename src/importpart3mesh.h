#include "coupling.h"
#include "commpart1.h"

namespace coupler {
class Part3Mesh3D{
  public:
    LO  nsurf;    // number of flux surfaces
    LO* versurf=NULL; // numbers of vertice on the flux surfaces
    double* xcoords=NULL;
    LO  li0,li1,li2;
    LO** xboxinds=NULL;  //The indexes of all boxes on the radial dimension
    LO lj0;
    LO* mylk0=NULL;
    LO* mylk1=NULL;
    LO* mylk2=NULL; // The indexes of box along z dimension
    GO boxstar,boxend,boxcount; // The  indexes of the 2d box

    double** Rcoords=NULL;  // The R coordinate of all vertices within the 2d box
    double** Zcoords=NULL;  // The Z coordinate of all vertices within the 2d box
    double** pzcoords=NULL;  // The z coordinates of all points with the 2d box.
    ~Part3Mesh3D()
   {
     delete[] versurf;
     delete[] xboxinds;
     delete[] xcoords;
     delete[] mylk0;
     delete[] mylk1;
     delete[] mylk2;
     delete[] Rcoords;
     delete[] Zcoords;
     delete[] pzcoords;
   }
};

void ImportPart3Mesh3D(Part3Mesh3D &p3m3d, Part1ParalPar3D  &p1pp3d);

void DistriPart3zcoords(Part3Mesh3D &p3m3d, Part1ParalPar3D  &p1pp3d);


LO  minloc(const double* zcoords, const LO n); 

void reshuffle_nodes(double* zcoords,const LO nstart,const LO vertnum);

void DistributePoints(double* exterarr,LO gstart,LO li, double* interarr,Part3Mesh3D &p3m3d,  \
     Part1ParalPar3D  &p1pp3d);

double minimalvalue(const double* array, const LO n);

}
