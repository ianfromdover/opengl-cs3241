//============================================================
// STUDENT NAME: Hong Yi En, Ian
// NUS User ID.: E0543721
// COMMENTS TO GRADER:
//
// The logic has been placed in helper function findT that
// returns a double for both functions.
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;

// returns whether there is a hit and its t-value if there is.
// return type of [bool, double]
double * findT( const Ray &r, double tmin, double tmax, double radius, Vector3d rTranslatedOrig )
{
    static double result[2] = { false, 0 };
    
    // to find the intersection, sub the ray eqn P(t) into sphere eqn
    // P • P - r^2 = 0
    // expanding the equation with P(t) = Ro + t * Rd, we get quad eqn
    // at^2 + bt + c = 0, where
    double a = dot( r.direction(), r.direction() );
    double b = dot( r.direction(), rTranslatedOrig ) * 2;
    double c = dot( rTranslatedOrig, rTranslatedOrig ) - ( radius * radius );
    
    double discriminant = ( b * b ) - 4.0 * ( a * c );

    if ( discriminant < 0 ) return result; // ray does not hit the sphere
    
    else
    {
        // assuming that all objects are opaque
        // if there are 2 intersections
        // choose the closer intersection (smaller t value)
        double tA = ( -b + sqrt(discriminant) ) / ( 2.0 * a );
        double tB = ( -b - sqrt(discriminant) ) / ( 2.0 * a );
        
        double t = ( tA < tB ) ? tA : tB;
        // if there is only 1 intersection, both values will be equal
        
        if ( t < tmin || t > tmax ) return result;
        
        result[0] = true;
        result[1] = t;
        return result;
    }
}

bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    Vector3d rTranslatedOrig = r.origin() - center;
    double *t;
    t = findT( r, tmin, tmax, radius, rTranslatedOrig );
    
    if (!t[0]) return false;
    
    Vector3d pt = rTranslatedOrig + t[1] * r.direction();
    
    // populate hit record
    rec.t = t[1];
    rec.p = r.pointAtParam(t[1]);
    rec.normal = pt / pt.unitVector();
    rec.material = material;
    return true;
}


// ray = the shadow ray that hit the sphere
// returns true if produces shadow
bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    Vector3d rTranslatedOrig = r.origin() - center;
    
    double *t;
    t = findT(r, tmin, tmax, radius, rTranslatedOrig);
    
    return t[0];
}
