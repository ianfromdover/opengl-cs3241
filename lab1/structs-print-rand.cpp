#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

typedef struct discType
{
    double pos[2];
    double speed[2];
    double radius;
    unsigned char color[3];
} discType;

void SayCircle(const discType *d)
{
    printf("The radius is:\n");
    std::cout << d -> radius;
    printf("\n");
}

double RandInRange(double min, double max)
{
  int r = rand();
  double rFrac = (double) r / (double) RAND_MAX; // val between 0 to 1

  return (max - min) * rFrac + min;
}

double RandNegInRange(double min, double max)
{
  double r = RandInRange(min, max);
  int positiveIfFirstDgtEven = ((int) (r * 10)) % 2 == 0 ? 1 : -1;

  return (double) positiveIfFirstDgtEven * r;
}

int main()
{
    srand(time(0));
    /*
    printf("Program Start!\n\n");
    discType d{0, 0, 1, 2, 5};

    printf("the Y speed of the circle is:\n");
    std::cout << d.speed[1];
    printf("\n");

    SayCircle(&d);

    printf("sin value is: %f\n", sin(3.141592653 / 2));
    
    printf("the RAND_MAX on this system is:\n");
    std::cout << RAND_MAX;
    printf("\n");
    */
    double min = 0;
    double max = 255.0;

    printf("Rando in range %f, to %f:\n", min, max);
    for (int i = 0; i < 20; i++)
    {
      std::cout << (int) RandInRange(min, max);
      printf("\n");
    }
    printf("\n");

    return 0;
}
