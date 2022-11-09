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
    
    // TODO: use center.xyz!!!
    Vector3d rTranslatedOrig = r.origin() - center;
    
    // to find the intersection, sub the ray eqn P(t) into sphere eqn
    // P • P - r^2 = 0
    // expanding the equation with P(t) = Ro + t * Rd, we get quad eqn
    // at^2 + bt + c = 0, where
    double a = dot( r.direction(), r.direction() );
    double b = dot( r.direction(), rTranslatedOrig ) * 2;
    double c = dot( rTranslatedOrig, rTranslatedOrig ) - ( radius * radius );
    
    double discriminant = ( b * b ) - 4 * ( a * c );

    if ( discriminant < 0 ) return false; // ray does not hit the sphere
    else // discrmt == 0 || discrmt > 0, 1 or 2 intersections with sphere
    {
        // if there are 2 intersections
        // choose the closer intersection (smaller t value)
        double tA = ( -b + sqrt(discriminant) ) / ( 2 * a );
        double tB = ( -b - sqrt(discriminant) ) / ( 2 * a );
        
        double t = ( tA < tB ) ? tA : tB;
        // if there is only 1 intersection, both values will be equal
        
        if ( t < tmin || t > tmax ) return false;
        
        // populate hit record
        rec.t = t;
        rec.p = r.pointAtParam(t);
        rec.material = material;
        
        Vector3d pt = rTranslatedOrig + t * r.direction();
        rec.normal = pt / pt.unitVector();
        return true;
    }
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************


    return false;  // YOU CAN REMOVE/CHANGE THIS IF NEEDED.
}
