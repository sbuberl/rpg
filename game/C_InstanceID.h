#ifndef _C_INSTANCE_ID_H_
#define _C_INSTANCE_ID_H_

#include "Component.h"

class C_InstanceID : public Component
{
public:
    C_InstanceID(Object* owner);
    ~C_InstanceID();

    int Get() const;

private:
    static int count;
    int id;
};

#endif /* _C_INSTANCE_ID_H_ */
