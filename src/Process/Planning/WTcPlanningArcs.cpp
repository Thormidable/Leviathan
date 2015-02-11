
#include "../../main.h"

cUVSphere *cPlanningArcs::gpArcBase=0;

cPlanningArcs::~cPlanningArcs()
{
    if(mpArc) Destroy();
    delete mpOutlineData;
    mpOutlineData=0;
}
cPlanningArcs::cPlanningArcs()
{
cPlanningArcs::gpArcBase=_CREATE(cUVSphere(32,1,0));


 mfYaw[0]=-0.1f;
 mfYaw[1]=0.1f;
 mfPitch[0]=0.0f;
 mfPitch[1]=0.2f;
 mfRange=4000.0f;

 mpArcMesh=0;
 mpOutline=0;
 mpOutlineData=0;
 mpArc=0;
 ConstructArcs();
};
void cPlanningArcs::Yaw(c2DVf lfmfYaw)
{
    mfYaw=lfmfYaw;
};
void cPlanningArcs::Pitch(c2DVf lfmfPitch)
{
    mfPitch=lfmfPitch;
};
void cPlanningArcs::Range(float lfRange)
{
    mfRange=lfRange;
};
void cPlanningArcs::Create(vRenderNode *lpNode)
{
    mpArc=_CREATE(cModel(lpNode));
    mpArc->Shader("SetUniformColorProgram");
    mpArc->SetVariable("ModelColor",PLANNING_FIRE_ARC_COLOR.Color());
    mpArc->Mesh(mpArcMesh);
    mpArc->Transparency(1);
    mpOutline=_CREATE(cLineArray(lpNode));
    mpOutline->Shader("SetUniformColorProgram");
    mpOutline->SetUniform("ModelColor",cRGBA(1.0f,1.0f,0.0f,0.5f).Color());
    mpOutline->Data(mpOutlineData);
    mpOutline->Transparency(1);
};

void cPlanningArcs::Destroy()
{
    _KILL(mpArc);
    mpArc=0;
    _KILL(mpOutline);
    mpOutline=0;
};

void cPlanningArcs::ConstructArcs()
{
    bool lbFound=false;
    uint32 liCentreFace=0;
     //delete mpArcMesh;
     mpArcMesh=new cUVSphere(gpArcBase);
     dynamic_cast<cUVSphere*>(mpArcMesh)->Radius(mfRange);
     strcpy(mpArcMesh->mpFileName,"GeneratedArcMesh");

    for(uint32 liCount=0;liCount<mpArcMesh->Verteces();liCount++)
    {
        float *lpVertex=mpArcMesh->Vertex(liCount);
        float lfYaw=atan2(lpVertex[0],lpVertex[2]);
        float lfScale=sqrt(lpVertex[0]*lpVertex[0]+lpVertex[2]*lpVertex[2]);
        float lfPitch=atan2(lpVertex[1],lfScale);

        while(lfYaw>WT_PI){lfYaw-=WT_PI;}
        while(lfYaw<-WT_PI){lfYaw+=WT_PI;}
        while(lfPitch>WT_PI){lfPitch-=WT_PI;}
        while(lfPitch<-WT_PI){lfPitch+=WT_PI;}

        if(lfYaw<mfYaw[0] || lfYaw>mfYaw[1] || lfPitch<mfPitch[0] || lfPitch>mfPitch[1])
        {
            if(!lbFound)
            {
                liCentreFace=liCount;
                lbFound=true;
                lpVertex[0]=0.0f;
                lpVertex[1]=0.0f;
                lpVertex[2]=0.0f;
            }
            else
            {
                for(uint32 liFace=0;liFace<mpArcMesh->Faces();liFace++)
                {
                    uint16 *lpFace=mpArcMesh->Face(liFace);
                    if(lpFace[0]==liCount) lpFace[0]=liCentreFace;
                    if(lpFace[1]==liCount) lpFace[1]=liCentreFace;
                    if(lpFace[2]==liCount) lpFace[2]=liCentreFace;
                }
            }
        }

    }



    mpArcMesh->RemoveErrorFaces(1.0f);
    //mpArcMesh->RemoveUnusedVertices();
    GenerateOutline(liCentreFace,1.0f);
    mpArcMesh->BufferMesh();

}

void cPlanningArcs::GenerateOutline(uint16 liCentreFace,float lfRange)
{


 if(!mpOutlineData)
 {
     mpOutlineData=_CREATE(cLineArrayData);
 }
 mpOutlineData->Init(100);

 bool lbFound=false;
 uint32 liEnd=0;
 uint32 liLastFace=0;
 uint32 liFirst=0;
 c3DVf lfTemp;
bool lbContinue=true;
while(lbContinue)
{
 lbContinue=false;
 for(uint32 liFace=0;liFace<mpArcMesh->Faces();++liFace)
 {
     uint16 *lpFace=mpArcMesh->Face(liFace);
     uint16 liCount=0;

     if(lpFace[0]==liCentreFace) liCount+=1;
     if(lpFace[1]==liCentreFace) liCount+=2;
     if(lpFace[2]==liCentreFace) liCount+=4;

     if(liCount==1 || liCount==2 || liCount==4)
     {
         if(!lbFound)
         {
             lbFound=true;
             if(liCount==1)
             {
                 lfTemp=mpArcMesh->Vertex(lpFace[1]);
                mpOutlineData->Add(lfTemp);
                lfTemp=mpArcMesh->Vertex(lpFace[2]);
                mpOutlineData->Add(lfTemp);
                liEnd=lpFace[2];
                liFirst=lpFace[1];
             }
             if(liCount==2)
             {
                lfTemp=mpArcMesh->Vertex(lpFace[0]);
                mpOutlineData->Add(lfTemp);
                lfTemp=mpArcMesh->Vertex(lpFace[2]);
                mpOutlineData->Add(lfTemp);
                liEnd=lpFace[2];
                liFirst=lpFace[0];
             }
             if(liCount==4)
             {
                 lfTemp=mpArcMesh->Vertex(lpFace[0]);
                mpOutlineData->Add(lfTemp);
                lfTemp=mpArcMesh->Vertex(lpFace[1]);
                mpOutlineData->Add(lfTemp);
                liEnd=lpFace[1];
                liFirst=lpFace[0];
             }
             liLastFace=liFace;
             lbContinue=true;
         }
         else
         {
             if(liFace!=liLastFace)
             {
                 if(liCount==1)
                 {
                    if(lpFace[1]==liEnd) //mpArcMesh->VertexMatch(lpFace[1],liEnd,lfRange))
                       {
                            lfTemp=mpArcMesh->Vertex(lpFace[2]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[2];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                            }
                           lbContinue=true;
                           continue;
                       }
                    if(lpFace[2]==liEnd) //mpArcMesh->VertexMatch(lpFace[2],liEnd,lfRange))
                       {
                           lfTemp=mpArcMesh->Vertex(lpFace[1]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[1];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                           }
                           lbContinue=true;
                           continue;
                       }
                 }
                 if(liCount==2)
                 {
                    if(lpFace[0]==liEnd) //mpArcMesh->VertexMatch(lpFace[0],liEnd,lfRange))
                       {
                           lfTemp=mpArcMesh->Vertex(lpFace[2]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[2];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                            }
                           lbContinue=true;
                           continue;
                       }
                    if(lpFace[2]==liEnd) //mpArcMesh->VertexMatch(lpFace[2],liEnd,lfRange))
                       {
                           lfTemp=mpArcMesh->Vertex(lpFace[0]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[0];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                            }
                           lbContinue=true;
                           continue;
                       }
                 }
                 if(liCount==4)
                 {
                    if(lpFace[0]==liEnd) //mpArcMesh->VertexMatch(lpFace[0],liEnd,lfRange))
                       {
                           lfTemp=mpArcMesh->Vertex(lpFace[1]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[1];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                            }
                           lbContinue=true;
                           continue;
                       }
                    if(lpFace[1]==liEnd) //mpArcMesh->VertexMatch(lpFace[1],liEnd,lfRange))
                       {
                           lfTemp=mpArcMesh->Vertex(lpFace[0]);
                            mpOutlineData->Add(lfTemp);
                           liEnd=lpFace[0];
                           liLastFace=liFace;
                           if(liEnd==liFirst)
                           {
                               mpOutlineData->Buffer();
                               return;
                            }
                           lbContinue=true;
                           continue;
                       }
                 }

             }
         }

     }
 }
}

mpOutlineData->Buffer();
}

bool cPlanningArcs::Created()
{
    return mpArc;
};
