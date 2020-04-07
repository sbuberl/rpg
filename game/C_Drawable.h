#ifndef _C_DRAWABLE_H_
#define _C_DRAWABLE_H_

#include <SFML/Graphics.hpp>

#include "Window.h"

class C_Drawable
{
public:
    C_Drawable();
    virtual ~C_Drawable();

    virtual void Draw(Window& window) = 0;

    void SetSortOrder(int order);
    int GetSortOrder() const;

private:
    int sortOrder;
};

#endif /* _C_DRAWABLE_H_ */
