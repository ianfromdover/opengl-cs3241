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

double findT( const Ray &r, double tmin, double tmax, double radius, Vector3d rTranslatedOrig )
{
    double a = dot( r.direction(), r.direction() );
    double b = dot( r.direction(), rTranslatedOrig ) * 2;
    double c = dot( rTranslatedOrig, rTranslatedOrig ) - ( radius * radius );
    
    double discriminant = ( b * b ) - 4 * ( a * c );

    if ( discriminant < 0 ) return false;
    else
    {
        double tA = ( -b + sqrt(discriminant) ) / ( 2 * a );
        double tB = ( -b - sqrt(discriminant) ) / ( 2 * a );
        
        double t = ( tA < tB ) ? tA : tB;
        
        if ( t < tmin || t > tmax ) return false;
        return t;
    }
}

bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
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
        // since we assume that all objects are opaque
        double tA = ( -b + sqrt(discriminant) ) / ( 2 * a );
        double tB = ( -b - sqrt(discriminant) ) / ( 2 * a );
        
        double t = ( tA < tB ) ? tA : tB;
        // if there is only 1 intersection, both values will be equal
        
        if ( t < tmin || t > tmax ) return false;
        
        Vector3d pt = rTranslatedOrig + t * r.direction();
        // populate hit record
        rec.t = t;
        rec.p = r.pointAtParam(t);
        rec.normal = pt / pt.unitVector();
        rec.material = material;
        return true;
    }
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    // identical logic to above. only change at the bottom line
    Vector3d rTranslatedOrig = r.origin() - center;
    
    double a = dot( r.direction(), r.direction() );
    double b = dot( r.direction(), rTranslatedOrig ) * 2;
    double c = dot( rTranslatedOrig, rTranslatedOrig ) - ( radius * radius );
    
    double discriminant = ( b * b ) - 4 * ( a * c );
    
    if ( discriminant < 0 ) return false;
    else
    {
        double tA = ( -b + sqrt(discriminant) ) / ( 2 * a );
        double tB = ( -b - sqrt(discriminant) ) / ( 2 * a );
        
        double t = ( tA < tB ) ? tA : tB;
        
        return ( t >= tmin && t <= tmax );
    }
}
