//============================================================
// STUDENT NAME: Hong Yi En, Ian
// NUS User ID.: E0543721
// COMMENTS TO GRADER:
//
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    // to find the intersection, sub the ray eqn into sphere eqn
    // P•P - r^2 = 0
    // use center.xyz and radius
    int t = 0;
    // if ( t < tmin || t > tmax ) return false;
    // if ( t >= tmin && t <= tmax )
    /*
    {
        // We have a hit -- populate hit record.
        rec.t = t;
        rec.p = r.pointAtParam(t);
        
        rec.normal = 0;
        rec.material = material;
        return true;
    }
     */
    return false;  // YOU CAN REMOVE/CHANGE THIS IF NEEDED.
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************


    return false;  // YOU CAN REMOVE/CHANGE THIS IF NEEDED.
}
