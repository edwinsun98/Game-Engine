#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <map>
#include <string>
#include "drawable.h"
#include "movement.h"
#include "collidable.h"
#include "straightmovement.h"
#include "cyclicmovement.h"
#include "bordermovement.h"
#include "wasdmovement.h"
using namespace std;

class Object: public Drawable, public Collidable{
    inline static int id_counter = 0;
    bool playerControlled = 0;
    bool forcedDespawn = 0;
    int despawnTickCount = 0;
    int id;
    int type;
    int height;
    int despawnTickLimit;
    bool hidden;
    vector<Movement*> movements;
    map<string, int> attributes;
    int netRowChange = 0;
    int netColChange = 0;
    virtual void savePosition() = 0;
public:
    Object(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
            const vector<Movement*> &movements, const map<string, int> &attributes);
    Object(const Object &other);
    void setNetRowChange(const int &x);
    void setNetColChange(const int &x);
    virtual void restorePosition() = 0;
    void move(const int &tickCount);
    void reverseMovements();
    void addMovement(Movement *movement);
    void setForcedDespawn(const bool &despawn);
    void setHidden(const bool &hid);
    void setPlayerControlled(const bool &controlled);
    void setAttribute(const string &name, const int &val);
    const int &getAttribute(const string &name);
    const bool &getForcedDespawn();
    const bool &isHidden();
    const bool &isPlayerControlled();
    int &getDespawnTickCount();
    const int &getDespawnTickLimit();
    const int &getID();
    const int &getHeight();
    const int &getType();
    const int &getNetRowChange();
    const int &getNetColChange();
    virtual pair<int,int> getCenter() = 0;
    virtual ~Object() = 0;
};

#endif
