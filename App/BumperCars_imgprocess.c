#include "common.h"
#include "include.h"
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_H][CAMERA_W];
uint8 cnt_L=0;
uint8 cnt_R=0;

struct P point[12]={0};//��ʼ��ȫ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

/*********ѭ��*********/
void find_way(void)
{
    uint8 i,j;
    uint8 cnt=0;
    
   for(i=0;i<=CAMERA_H-24;i-=4)
        for(j=0;j<CAMERA_W/2;j++)
            if(img[i][j+1]-img[i][j]==255)//�\���׵�����
            {   
                point[cnt].x=CAMERA_H-i-1;
                point[cnt].y=j;     //��¼������������
                cnt_L++;            //��¼��߽���
                break;
            }
   
    cnt_L=cnt;
    cnt=0;//����
    
    for(i=0;i<=CAMERA_H-24;i-=4)
        for(j=CAMERA_W-1;j>=CAMERA_W/2;j--)
            if(img[i][j+1]-img[i][j]==255)//�׵��ڵ�����
            {
                point[cnt].x=CAMERA_H-i-1;
                point[cnt].y=j;     //��¼������������
                cnt_R++;     //��¼�ұ߽���
                break;
            }
    
    cnt_R=cnt;
    cnt=0;//����
}
        
//*****�������ʼ���*****/
/*
float curvature_calculate(struct P point1,struct P point2,struct P point3)
{
    float S;
    float L1,L2,L3;
    int16 x1,y1,x2,y2,x3,y3;
    float curva;
    x1=point1.x;
    x2=point2.x;
    x3=point3.x;
    y1=point1.y;
    y2=point2.y;
    y3=point3.y;
    
    L1=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    L2=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
    L3=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
    
    S=(float)(1.0*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2);
    
    curva=10*4*S/L1/L2/L3;   
    
    return curva;
}*/
 
//*********��ȡ����**********/  
/*
float curvature_get()
{
    float curva_L=0;
    float curva_R=0;
    float curvature;
    uint8 i;
    for(i=0;i<=cnt_L-3;i++)
      if(point[i].x!=0||point[i].y!=0)
      {
          curva_L=curvature_calculate(point[i],point[i+1],point[i+2]);//������������
          break;
      }
     for(i=0;i<=cnt_R-3;i++)
      if(point[i].x!=0||point[i].y!=0)
      {
          curva_R=curvature_calculate(point[i],point[i+1],point[i+2]);//������������
          break;
      }
    
      curvature=MAX(curva_L,curva_R);
    
      return curvature;
 }*/

/********ͼ����**********/
void img_process(void)
{
    find_way();//ѭ��
}  
                      