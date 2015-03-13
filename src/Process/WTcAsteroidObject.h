#ifndef __WTCASTEROIDOBJECT_H__
#define __WTCASTEROIDOBJECT_H__

class cAsteroidObject : public cProcess
{
public:
 cMomentumFRI **mpMomentum;
 cModel **mpModel;
 cMapDisplayObject **mpMapDisplays;
 uint32 miObjects;
public:

cAsteroidObject(uint32 liObjects);
void Run();
void Stop();

};

#endif
