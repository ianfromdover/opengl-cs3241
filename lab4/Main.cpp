//============================================================
// STUDENT NAME: Hong Yi En, Ian
// NUS User ID.: E0543721
// COMMENTS TO GRADER: None
// ============================================================

#include "Util.h"
#include "Vector3d.h"
#include "Color.h"
#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Surface.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Scene.h"
#include "Raytrace.h"
#include <string>


// Constants for Scene 1.
static constexpr int imageWidth1 = 640;
static constexpr int imageHeight1 = 480;
static constexpr int reflectLevels1 = 2;  // 0 -- object does not reflect scene.
static constexpr int hasShadow1 = true;
static constexpr std::string_view outImageFile1 = "out1.png";

// Constants for Scene 2.
static constexpr int imageWidth2 = 640;
static constexpr int imageHeight2 = 480;
static constexpr int reflectLevels2 = 2;  // 0 -- object does not reflect scene.
static constexpr int hasShadow2 = true;
static constexpr std::string_view outImageFile2 = "img_scene2.png";



///////////////////////////////////////////////////////////////////////////
// Raytrace the whole image of the scene and write it to a file.
///////////////////////////////////////////////////////////////////////////

void RenderImage( const std::string &imageFilename, const Scene &scene, 
                  int reflectLevels, bool hasShadow )
{
    int imgWidth = scene.camera.getImageWidth();
    int imgHeight = scene.camera.getImageHeight();

    Image image( imgWidth, imgHeight ); // To store the result of ray tracing.

    double startTime = Util::GetCurrRealTime();
    double startCPUTime = Util::GetCurrCPUTime();

    // Generate image, rendering in parallel on Windows and Linux.
    #ifndef __APPLE__
    #pragma warning( push )
    #pragma warning( disable : 6993 )
    #pragma omp parallel for
    #endif
    for ( int y = 0; y < imgHeight; y++ )
    {
        double pixelPosY = y + 0.5;

        for ( int x = 0; x < imgWidth; x++ )
        {
            double pixelPosX = x + 0.5;
            Ray ray = scene.camera.getRay( pixelPosX, pixelPosY );
            Color pixelColor = Raytrace::TraceRay( ray, scene, reflectLevels, hasShadow );
            pixelColor.clamp();
            image.setPixel( x, y, pixelColor );
        }
    }
    #ifndef __APPLE__
    #pragma warning( pop )
    #endif

    double cpuTimeElapsed = Util::GetCurrCPUTime() - startCPUTime;
    double realTimeElapsed = Util::GetCurrRealTime() - startTime;
    std::cout << "CPU time taken = " << cpuTimeElapsed << "sec" << std::endl;
    std::cout << "Real time taken = " << realTimeElapsed << "sec" << std::endl;

    // Write image to file.
    if ( !image.writeToFile( imageFilename ) ) return;
    else Util::ErrorExit("File: %s could not be written.\n", imageFilename.c_str() );
}



// Forward declarations. These functions are defined later in the file.
void DefineScene1( Scene &scene, int imageWidth, int imageHeight );
void DefineScene2( Scene &scene, int imageWidth, int imageHeight );



int main()
{
// Define Scene 1.
    Scene scene1;
    DefineScene1( scene1, imageWidth1, imageHeight1 );

// Render Scene 1.

    std::cout << "Render Scene 1..." << std::endl;
    RenderImage( std::string(outImageFile1), scene1, reflectLevels1, hasShadow1 );
    std::cout << "Scene 1 completed." << std::endl;

// Delete Scene 1 surfaces.

    for (auto& surface : scene1.surfaces)
    {
        delete surface;
    }

// Define Scene 2.

    Scene scene2;
    DefineScene2( scene2, imageWidth2, imageHeight2 );

// Render Scene 2.

    std::cout << "Render Scene 2..." << std::endl;
    RenderImage( std::string(outImageFile2), scene2, reflectLevels2, hasShadow2 );
    std::cout << "Scene 2 completed." << std::endl;

// Delete Scene 2 surfaces.

    for (auto& surface : scene2.surfaces)
    {
        delete surface;
    }

    std::cout << "All done. Press Enter to exit." << std::endl;
    std::cin.get();
    return 0;
}



///////////////////////////////////////////////////////////////////////////
// Modelling of Scene 1.
///////////////////////////////////////////////////////////////////////////

void DefineScene1( Scene &scene, int imageWidth, int imageHeight )
{
    scene.backgroundColor = Color( 0.2f, 0.3f, 0.5f );

    scene.amLight.I_a = Color( 1.0f, 1.0f, 1.0f ) * 0.25f;

// Define materials.

    // Light red.
    Material lightRed = Material();
    lightRed.k_d = Color( 0.8f, 0.4f, 0.4f );
    lightRed.k_a = lightRed.k_d;
    lightRed.k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    lightRed.k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    lightRed.n = 64.0f;

    // Light green.
    Material lightGreen = Material();
    lightGreen.k_d = Color( 0.4f, 0.8f, 0.4f );
    lightGreen.k_a = lightGreen.k_d;
    lightGreen.k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    lightGreen.k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    lightGreen.n = 64.0f;

    // Light blue.
    Material lightBlue = Material();
    lightBlue.k_d = Color( 0.4f, 0.4f, 0.8f ) * 0.9f;
    lightBlue.k_a = lightBlue.k_d;
    lightBlue.k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    lightBlue.k_rg = Color( 0.8f, 0.8f, 0.8f ) / 2.5f;
    lightBlue.n = 64.0f;

    // Yellow.
    Material yellow = Material();
    yellow.k_d = Color( 0.6f, 0.6f, 0.2f );
    yellow.k_a = yellow.k_d;
    yellow.k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    yellow.k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    yellow.n = 64.0f;

    // Gray.
    Material gray = Material();
    gray.k_d = Color( 0.6f, 0.6f, 0.6f );
    gray.k_a = gray.k_d;
    gray.k_r = Color( 0.6f, 0.6f, 0.6f );
    gray.k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    gray.n = 128.0f;

    // Insert into scene materials vector.
    scene.materials = { lightRed, lightGreen, lightBlue, yellow, gray };


// Define point light sources.

    scene.ptLights.resize(2);

    PointLightSource light0 = { Vector3d(100.0, 120.0, 10.0), Color(1.0f, 1.0f, 1.0f) * 0.6f };
    PointLightSource light1 = { Vector3d(5.0, 80.0, 60.0), Color(1.0f, 1.0f, 1.0f) * 0.6f };

    scene.ptLights = { light0, light1 };


// Define surface primitives.

    scene.surfaces.resize(15);

    auto horzPlane = new Plane( 0.0, 1.0, 0.0, 0.0, scene.materials[2] ); // Horizontal plane.
    auto leftVertPlane = new Plane( 1.0, 0.0, 0.0, 0.0, scene.materials[4] ); // Left vertical plane.
    auto rightVertPlane = new Plane( 0.0, 0.0, 1.0, 0.0, scene.materials[4] ); // Right vertical plane.
    auto bigSphere =  new Sphere( Vector3d( 40.0, 20.0, 42.0 ), 22.0, scene.materials[0] ); // Big sphere.
    auto smallSphere = new Sphere( Vector3d( 75.0, 10.0, 40.0 ), 12.0, scene.materials[1] ); // Small sphere.

    // Cube +y face.
    auto cubePosYTri1 = new Triangle( Vector3d( 50.0, 20.0, 90.0 ),
                                      Vector3d( 50.0, 20.0, 70.0 ),
                                      Vector3d( 30.0, 20.0, 70.0 ),
                                      scene.materials[3] );
    auto cubePosYTri2 = new Triangle( Vector3d( 50.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 70.0 ),
                                      Vector3d( 30.0, 20.0, 90.0 ),
                                      scene.materials[3] );

    // Cube +x face.
    auto cubePosXTri1 = new Triangle( Vector3d( 50.0, 0.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 90.0 ),
                                      scene.materials[3]);
    auto cubePosXTri2 = new Triangle( Vector3d( 50.0, 0.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 90.0 ),
                                      Vector3d( 50.0, 0.0, 90.0 ),
                                      scene.materials[3] );

    // Cube -x face.
    auto cubeNegXTri1 = new Triangle( Vector3d( 30.0, 0.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 70.0 ),
                                      scene.materials[3]);
    auto cubeNegXTri2 = new Triangle( Vector3d( 30.0, 0.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 70.0 ),
                                      Vector3d( 30.0, 0.0, 70.0 ),
                                      scene.materials[3] );

    // Cube +z face.
    auto cubePosZTri1 = new Triangle( Vector3d( 50.0, 0.0, 90.0 ),
                                      Vector3d( 50.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 90.0 ),
                                      scene.materials[3]);
    auto cubePosZTri2 = new Triangle( Vector3d( 50.0, 0.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 0.0, 90.0 ),
                                      scene.materials[3] );

    // Cube -z face.
    auto cubeNegZTri1 = new Triangle( Vector3d( 30.0, 0.0, 70.0 ),
                                      Vector3d( 30.0, 20.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 70.0 ),
                                      scene.materials[3] );
    auto cubeNegZTri2 = new Triangle( Vector3d( 30.0, 0.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 70.0 ),
                                      Vector3d( 50.0, 0.0, 70.0 ),
                                      scene.materials[3] );

    scene.surfaces = { horzPlane, leftVertPlane, rightVertPlane, 
                       bigSphere, smallSphere,
                       cubePosXTri1, cubePosXTri2,
                       cubePosYTri1, cubePosYTri2,
                       cubePosZTri1, cubePosZTri2,
                       cubeNegXTri1, cubeNegXTri2,
                       cubeNegZTri1, cubeNegZTri2 };


// Define camera.

    scene.camera = Camera( Vector3d( 150.0, 120.0, 150.0 ),  // eye
                           Vector3d( 45.0, 22.0, 55.0 ),  // lookAt
                           Vector3d( 0.0, 1.0, 0.0 ),  //upVector
                           (-1.0 * imageWidth) / imageHeight,  // left
                           (1.0 * imageWidth) / imageHeight,  // right
                           -1.0, 1.0, 3.0,  // bottom, top, near
                           imageWidth, imageHeight );  // image_width, image_height
}



///////////////////////////////////////////////////////////////////////////
// Modeling of Scene 2.
///////////////////////////////////////////////////////////////////////////

void DefineScene2( Scene &scene, int imageWidth, int imageHeight )
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

// Define colors.
    // light blue cool col temp sun
    Color sun = Color( 0.827f, 0.867f, 0.988f );
    Color waterBlue = Color( 0.435f, 0.670f, 0.941f );
    // Color waterBlue = Color( 0.435f, 0.739f, 0.941f ); // fadedFilterBlue
    Color white = Color( 1.0f, 1.0f, 1.0f );
    Color black = Color( 0.0f, 0.0f, 0.0f );
    Color pink = Color( 0.973f, 0.831f, 0.871f );
    Color blue = Color( 0.0f, 0.0f, 1.0f );


    scene.backgroundColor = Color( 0.2f, 0.3f, 0.5f );
    // scene.amLight.I_a = waterBlue * 0.35f;
    scene.amLight.I_a = white * 0.2f;
    

// Define materials.

    // Reflective water light blue.
    Material water = Material();
    water.k_d = waterBlue;     // diffuse
    water.k_a = water.k_d;     // ambient
    water.k_r = black;         // specular (reflection)
    water.k_rg = white / 2.0;  // reflected ray colour. white = mirror
    water.n = 0.0f;            // shininess coeff, 0 to 128.0 affecting r
                               // specular becomes smaller, sharper
    Material whiteMat = Material();
    whiteMat.k_d = white;
    whiteMat.k_a = whiteMat.k_d;
    whiteMat.k_r = black;
    whiteMat.k_rg = black;
    whiteMat.n = 0.0f;
    
    Material shinyBlack = Material();
    shinyBlack.k_d = black;
    shinyBlack.k_a = shinyBlack.k_d;
    shinyBlack.k_r = white;
    shinyBlack.k_rg = white * 0.2;
    shinyBlack.n = 128.0f;

    Material mirror = Material();
    mirror.k_d = black;
    mirror.k_a = mirror.k_d;
    mirror.k_r = white;
    mirror.k_rg = white;
    mirror.n = 128.0f;
    
    Material shoeBlack = Material();
    shoeBlack.k_d = Color( 0.1f, 0.1f, 0.1f );
    shoeBlack.k_a = shoeBlack.k_d;
    shoeBlack.k_r = white * 0.2;
    shoeBlack.k_rg = black;
    shoeBlack.n = 32.0f;

    Material pinkMat = Material();
    pinkMat.k_d = Color( 0.973f, 0.673f, 0.903f );
    pinkMat.k_a = pinkMat.k_d;
    pinkMat.k_r = Color( 1.0f, 0.8f, 0.9f );
    pinkMat.k_rg = Color( 0.1f, 0.1f, 0.1f );
    pinkMat.n = 64.0f;

    Material yellowMat = Material();
    yellowMat.k_d = Color( 1.0f, 0.92f, 0.0f );
    yellowMat.k_a = yellowMat.k_d;
    yellowMat.k_r = Color( 1.0f, 1.0f, 1.0f );
    yellowMat.k_rg = white * 0.2f;
    yellowMat.n = 72.0f;
    
    Material redShirtMat = Material();
    redShirtMat.k_d = Color( 0.933f, 0.393f, 0.415f );
    redShirtMat.k_a = redShirtMat.k_d;
    redShirtMat.k_r = Color( 1.0f, 1.0f, 1.0f );
    redShirtMat.k_rg = black;
    redShirtMat.n = 72.0f;
    
    
    // Insert into scene materials vector.
    scene.materials = { water, whiteMat, shinyBlack, mirror, 
                        shoeBlack, pinkMat, yellowMat, redShirtMat };


// Define point light sources.

    scene.ptLights.resize(1);

    // Sun.
    PointLightSource light0 = { Vector3d(60.0, 220.0, 90.0), white * 0.7f };

    scene.ptLights = { light0 };
    
// Define surface primitives.
    
    scene.surfaces.resize(9);
    double scale = 7.0;
    double ballHeight = 0.75f;
    Material bodyMat = scene.materials[1];
    Material shirtMat = scene.materials[7];
    Material shoesMat = scene.materials[4];

    // Floor.
    auto horzPlane = new Plane( 0.0, 1.0, 0.0, 0.0, scene.materials[0] );

// Objects around
    auto pinkBall = new Sphere( Vector3d( 7.0 * scale, 3.0 * scale, 13.0 * scale ), 4.0 * scale, scene.materials[5] );
    auto yellowBall = new Sphere( Vector3d( 9.0 * scale, ballHeight * scale, 2.0 * scale ), 1.0 * scale, scene.materials[6] );
    auto yellowBall2 = new Sphere( Vector3d( 0.0 * scale, 7.0 * scale, 22.0 * scale ), 9.0 * scale, scene.materials[6] );
    auto ballMirror = new Sphere( Vector3d( 7.0 * scale, 1.75f * scale, -5.0 * scale ), 2.25 * scale, scene.materials[3] );
    auto shelter = new Triangle( Vector3d( -6.0 * scale, 0.0 * scale, -5.0 * scale ),
                                 Vector3d( 0.0 * scale, 6.0 * scale, 6.0 * scale ),
                                 Vector3d( 7.0 * scale, 11.5 * scale, 0.0 * scale ),
                                 scene.materials[6] );

// Human.
    // Head.
    auto head = new Sphere( Vector3d( 4.0 * scale, 6.0 * scale, 0.0 * scale ), 1.0 * scale, scene.materials[1] );
    auto eyeL = new Sphere( Vector3d( 4.925 * scale, 6.0 * scale, 0.0 * scale ), 0.15 * scale, scene.materials[2] );
    auto eyeR = new Sphere( Vector3d( 4.775 * scale, 6.0 * scale, -0.6 * scale ), 0.15 * scale, scene.materials[2] );

    // Body
    auto bodyLeft = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, 2.0 * scale ),
                                  Vector3d( 0.0 * scale, 1.0 * scale, 1.0 * scale ),
                                  Vector3d( 3.0 * scale, 5.0 * scale, 2.0 * scale ),
                                  shirtMat );

    auto bodyRight = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, -2.0 * scale ),
                                   Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                   Vector3d( 3.0 * scale, 5.0 * scale, -2.0 * scale ),
                                   shirtMat );
    
    auto bodyTop1 = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, -2.0 * scale ),
                                  Vector3d( 2.0 * scale, 6.0 * scale, 2.0 * scale ),
                                  Vector3d( 3.0 * scale, 5.0 * scale, 2.0 * scale ),
                                  shirtMat );

    auto bodyTop2 = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, -2.0 * scale ),
                                  Vector3d( 3.0 * scale, 5.0 * scale, 2.0 * scale ),
                                  Vector3d( 3.0 * scale, 5.0 * scale, -2.0 * scale ),
                                  shirtMat );

    auto bodyFront1 = new Triangle( Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                    Vector3d( 3.0 * scale, 5.0 * scale, -2.0 * scale ),
                                    Vector3d( 3.0 * scale, 5.0 * scale, 2.0 * scale ),
                                    shirtMat );

    auto bodyFront2 = new Triangle( Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                    Vector3d( 3.0 * scale, 5.0 * scale, 2.0 * scale ),
                                    Vector3d( 0.0 * scale, 1.0 * scale, 1.0 * scale ),
                                    shirtMat );

    auto bodyBack1 = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, -2.0 * scale ),
                                   Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                   Vector3d( 2.0 * scale, 6.0 * scale, 2.0 * scale ),
                                   shirtMat );

    auto bodyBack2 = new Triangle( Vector3d( 2.0 * scale, 6.0 * scale, 2.0 * scale ),
                                   Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                   Vector3d( 0.0 * scale, 1.0 * scale, 1.0 * scale ),
                                   shirtMat );
    // Legs: Thighs
    auto legLOut = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, 2.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 1.0 * scale ),
                                 Vector3d( 0.0 * scale, 1.0 * scale, 1.0 * scale ),
                                 bodyMat );
    
    auto legLMid = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, 2.0 * scale ),
                                 Vector3d( 0.0 * scale, 1.0 * scale, 1.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 0.0 * scale ),
                                 bodyMat );

    auto legLTop = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, 2.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 0.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 1.0 * scale ),
                                 bodyMat );

    auto legROut = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, -2.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, -1.0 * scale ),
                                 Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                 bodyMat );

    auto legRMid = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, -2.0 * scale ),
                                 Vector3d( 0.0 * scale, 1.0 * scale, -1.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 0.0 * scale ),
                                 bodyMat );

    auto legRTop = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, -2.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, 0.0 * scale ),
                                 Vector3d( 0.0 * scale, 2.0 * scale, -1.0 * scale ),
                                 bodyMat );

    // Legs: Calves
    auto calfL = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, 2.0 * scale ),
                               Vector3d( 1.0 * scale, 1.0 * scale, 1.0 * scale ),
                               Vector3d( 4.0 * scale, 2.5 * scale, 2.0 * scale ),
                               bodyMat );

    auto calfR = new Triangle( Vector3d( 4.0 * scale, 3.0 * scale, -2.0 * scale ),
                               Vector3d( 1.0 * scale, 1.0 * scale, -1.0 * scale ),
                               Vector3d( 4.0 * scale, 2.5 * scale, -2.0 * scale ),
                               bodyMat );
    
    // Feet
    auto footLTop = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, 1.0 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, 1.5 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, 0.5 * scale ),
                                  shoesMat );

    auto footLOut = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, 1.0 * scale ),
                                  Vector3d( 1.0 * scale, 0.0 * scale, 1.0 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, 1.5 * scale ),
                                  shoesMat );

    auto footLIn = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, 1.0 * scale ),
                                 Vector3d( 3.0 * scale, 0.0 * scale, 0.5 * scale ),
                                 Vector3d( 1.0 * scale, 0.0 * scale, 1.0 * scale ),
                                 shoesMat );

    auto footRTop = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, -1.0 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, -1.5 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, -0.5 * scale ),
                                  shoesMat );

    auto footROut = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, -1.0 * scale ),
                                  Vector3d( 1.0 * scale, 0.0 * scale, -1.0 * scale ),
                                  Vector3d( 3.0 * scale, 0.0 * scale, -1.5 * scale ),
                                  shoesMat );

    auto footRIn = new Triangle( Vector3d( 1.0 * scale, 1.0 * scale, -1.0 * scale ),
                                 Vector3d( 3.0 * scale, 0.0 * scale, -0.5 * scale ),
                                 Vector3d( 1.0 * scale, 0.0 * scale, -1.0 * scale ),
                                 shoesMat );


    scene.surfaces = { pinkBall, yellowBall, yellowBall2, shelter,
                       head, eyeL, eyeR,
                       bodyTop1, bodyTop2,
                       bodyFront1, bodyFront2,
                       bodyBack1, bodyBack2,
                       bodyLeft, bodyRight,
                       legLOut, legLMid, legLTop,
                       legROut, legRMid, legRTop,
                       calfL, calfR,
                       footLTop, footLOut, footLIn,
                       footRTop, footROut, footRIn,
                       horzPlane, ballMirror };
    
// Define camera.

    scene.camera = Camera( Vector3d( 120.0, 120.0, 120.0 ),  // eye
                           Vector3d( 55.0, 50.0, 35.0 ),  // lookAt
                           Vector3d( 0.0, 1.0, 0.0 ),  //upVector
                           (-1.0 * imageWidth) / imageHeight,  // left
                           (1.0 * imageWidth) / imageHeight,  // right
                           -1.0, 1.0, 3.0,  // bottom, top, near
                           imageWidth, imageHeight );  // image_width, image_height
}

