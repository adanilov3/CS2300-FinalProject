#ifndef M4OEP_BMBOWMAN_ADANILOV_BUTTON_H
#define M4OEP_BMBOWMAN_ADANILOV_BUTTON_H

#include "rect.h"
#include <string>

class Button : public Rect {
private:
    std::string label;
    color originalFill, hoverFill, pressFill;

public:
    Button(color fill, point2D center, double width, double height, std::string label);
    virtual ~Button() = default;
    /* Uses OpenGL to draw the box with the label on top */
    void draw() const override;

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the Button when the user is hovering over it */
    void hover();

    /* Change color of the Button when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();
};

#endif //M4OEP_BMBOWMAN_ADANILOV_BUTTON_H