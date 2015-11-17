#include"fitline.h"
#include"ransac.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>
const int COUNT = 100;
const int inlierCnt = 40;
const int outlierCnt = COUNT - inlierCnt;
Point2D32f points[COUNT];
float lines[4] = {0.0};//line parameters
int main()
{
	srand((unsigned int)time(0));

	float a = rand()%100/5.0;
	float b = rand()%100/5.0;
   	printf("groundtruth: (%f, %f)\n", a, b);

   	//inliers
    for(int i = 0 ; i < inlierCnt ; i++)
    {
        points[i].x = i;
        points[i].y = i * a + b + rand()%100/1024.0;
    }
    
    //outliers
    for(int i = inlierCnt; i < COUNT; i++)
    {
		points[i].x = 20 + rand()%100;
		points[i].y = 30 + rand()%100;
    }
 	 
 	//least square fit with only inliers
   	FitLine2D(points, inlierCnt, NULL, lines);
   	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("least square fit: a: %f  b%f\n", a, b);
   	
	//weighted least square fit with only inliers
	FitLine2D(points, inlierCnt, lines);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("weighted least square fit: a: %f  b%f\n", a, b);
	
	
	
	//Ransac fit with inlier and outlier; note: the result maybe wrong
	Ransac(points, COUNT, lines);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("ransac fit(including outliers): a: %f  b%f\n", a, b);
	
	int numForEstimate = 5;
	float successProbability = 0.999f;
	float maxOutliersPercentage = (float)outlierCnt/COUNT; 
	Ransac(points, COUNT, lines, numForEstimate, successProbability, maxOutliersPercentage);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("ransac fit(including outliers): a: %f  b%f\n", a, b);
	
	return 0;
}
