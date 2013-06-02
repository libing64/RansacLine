#include"fitline.h"
#include"ransac.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>
const int COUNT = 100;
const int inlierCnt = 40;
const int outlierCnt = COUNT - inlierCnt;
Point2D32f points[COUNT];
float lines[4] = {0.0};//存储直线的参数
int main()
{
	
	//产生随机数
	//inliers
    srand((unsigned int)time(NULL));
    for(int i = 0 ; i < inlierCnt ; i++)
    {
        points[i].x = i;
        points[i].y = i * 2.3 + 45 + rand()%100/1024.0;
    }
    
    //outliers
    for(int i = inlierCnt; i < COUNT; i++)
    {
		points[i].x = 20 + rand()%100;
		points[i].y = 30 + rand()%100;
    }
 	 
 	//直接拟合仅使用inliers
   	FitLine2D(points, inlierCnt, NULL, lines);
   	float a = lines[1]/lines[0];
	float b = lines[3] - a*lines[2];
	printf("least square fit: a: %f  b%f\n", a, b);
   	
	//加权拟合仅使用inliers
	FitLine2D(points, inlierCnt, lines);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("weighted least square fit: a: %f  b%f\n", a, b);
	
	
	
	//Ransac 拟合
	Ransac(points, COUNT, lines);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("ransac fit(including outliers): a: %f  b%f\n", a, b);
	
	int numForEstimate = 5;
	float successProbability = 0.99f;//值越大，则跌代的次数会越大
	float maxOutliersPercentage = (float)outlierCnt/COUNT; //离群的最大概率,估计值
	Ransac(points, COUNT, lines, numForEstimate, successProbability, maxOutliersPercentage);
	a = lines[1]/lines[0];
	b = lines[3] - a*lines[2];
	printf("ransac fit(including outliers): a: %f  b%f\n", a, b);
	
	
	return 0;
}
