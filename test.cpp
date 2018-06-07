#include<opencv2/features2d/features2d.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/core/core.hpp>
#include <time.h>  
#include<iostream>
using namespace std;
using namespace cv;
int main()

{   
    double dResult;  
    long lBefore = clock(); 
    Mat SrcImage1 = imread("image1.jpg", 1);
    Mat SrcImage2 = imread("image2.jpg", 1);
    Mat image1;
    Mat image2;   
    //pyrDown(SrcImage1,image1,Size(SrcImage1.cols/2,SrcImage1.rows/2)); 
    //pyrDown(SrcImage2,image2,Size(SrcImage2.cols/2,SrcImage2.rows/2));
    cvtColor(SrcImage1,image1,COLOR_BGR2GRAY);
    cvtColor(SrcImage2,image2,COLOR_BGR2GRAY);
 int rows=image1.rows;
 int cols=image1.cols;
 Mat result(image1.size(),CV_8UC1,Scalar::all(0));
//如何评价两个点的距离很近，是对应点
//对第一幅图像，在第二幅中找对应点
 int kcor;const int size=3;
 const int windowsize=(2*size+1)*(2*size+1);
 for(int i=size;i<rows-size;i++)
   for(int j=size;j<cols-size;j++)//扫描第一幅图像的所有点
      {
         float minusdistance=1000000.0;
         uchar M[windowsize];int count=0;

         for(int offi=-size;offi<=size;offi++)
         {
         uchar* ptr = image1.ptr<uchar>(i+offi);
         for(int offj=-size;offj<=size;offj++)
         {
          M[count++]=*(ptr+(j+offj));
         }
     }
     //i-4~i+4   j-4~j+4
 for(int k=j-70;k<j;k+=1)
 {  
     uchar N[windowsize];int count=0;
  for(int offi=-size;offi<=size;offi++)
     {
      uchar* ptr = image2.ptr<uchar>(i+offi);
       for(int offj=-size;offj<=size;offj++)
        {
          N[count++]=*(ptr+(k+offj));
        }
     }
   float distance=0;
  for(int i=0;i<windowsize;i++)
  {
  distance+=pow(M[i]-N[i],2);
  }
     if(distance<minusdistance)
     {
         minusdistance=distance;
         kcor=k;
     }
 }//已知image1中（i,j）和image2中的(i,k)匹配，计算深度： z=sf/d  
   //14   
   if(j-kcor>14) 
   //3500
   {      uchar depth=3500/(j-kcor);
         //cout<<j-kcor<<endl;
         result.at<uchar>(i,j)=1.5*depth>255?255:1.5*depth;
    }
 }
        //pyrUp(result,result,Size(result.cols*2,result.rows*2)); 
        //resize(result,result,Size(result.cols*2,result.rows*2));  
        imshow("1", SrcImage1);
	imshow("2", SrcImage2);
	imshow("result", result);
        imwrite("5wR.jpg",result);
        dResult = (double)(clock() - lBefore);  
        printf("\nTotal Time: %f s.\n", dResult/1000/1000);  
	waitKey(0);
	return 0;
}
