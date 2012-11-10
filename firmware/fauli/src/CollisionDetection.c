// Nothing in this file has been tested, yet.
// TODO adjust to the new Entity class

#include "Drawing.h"

// should be defined in libs/libgraphics/Bitmap.h (includes) -> libs/libgraphics/Pixels/*.h
#ifndef TransparentPixel
#define TransparentPixel 0
#endif

typedef struct {
    int x, y;
    Bitmap* bitmap;
} Sprite;

/// stores an absolute x,y and relative width, height
typedef struct {
    int x, y, width, height;
} Rect;

/// @return true if the rect of @a is neither left, right above or below the rect of @b
bool Sprite_collides(Sprite* a, Sprite* b) {
    return !(a->x < b->x + b->bitmap->width) &&
           !(a->x + a->bitmap->width < b->x) &&
           !(a->y < b->y + b->bitmap->height) &&
           !(a->y + a->bitmap->height < b->y);
}

/// @return a rect that contains the overlapping area between two sprites
Rect Sprite_collisionSubrect(Sprite* a, Sprite* b) {
    Rect subrect;
    subrect.x = a->x > b->x ? a->x : b->x;
    subrect.y = a->y > b->y ? a->y : b->y;
    subrect.width  = (a->x + a->bitmap->width  < b->x + b->bitmap->width  ? a->x + a->bitmap->width  : b->x + b->bitmap->width)  - subrect.x;
    subrect.height = (a->y + a->bitmap->height < b->y + b->bitmap->height ? a->y + a->bitmap->height : b->y + b->bitmap->height) - subrect.y;

    return subrect;
}

////////////////////////////////////////////////////////////////////////////////
/// Step 1 check for boundingbox collision 
/// Step 2 find the colliding sub-rectangle
/// Step 3 check all pixels in the sub-rectangle
///        and return true if both bitmaps have a pixel that is not transparent
///        at the same position
////////////////////////////////////////////////////////////////////////////////
bool Sprite_pixelCollision(Sprite* a, Sprite* b) {
    if (Sprite_collides(a,b)) {
        const Rect collisionRect = Sprite_collisionSubrect(a, b);
    
        // x and y as absolute global pixel position        
        for (int y=collisionRect.y; y < collisionRect.y + collisionRect.height; ++y) {
            for (int x=collisionRect.x; x < collisionRect.x + collisionRect.width; ++x) {
                if (*ConstBitmapPixelPointer(a->bitmap, x - a->x, y - a->y) != TransparentPixel &&
                    *ConstBitmapPixelPointer(b->bitmap, x - b->x, y - b->y) != TransparentPixel) {
                    return true;
                }
            }
        }
    }
    return false;
}

