#ifndef _S_DRAWABLE_H_
#define _S_DRAWABLE_H_

#include <map>

#include "C_Drawable.h"
#include "Object.h"

class S_Drawable
{
public:
    void Add(std::vector<std::shared_ptr<Object>>& object);

    void ProcessRemovals();

    void Draw(Window& window);

private:
    void Add(std::shared_ptr<Object> object);
    void Sort();

    std::vector<std::shared_ptr<Object>> drawables;

};

#endif /* _S_DRAWABLE_H_ */