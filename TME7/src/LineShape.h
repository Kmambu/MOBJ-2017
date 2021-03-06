#ifndef NETLIST_LINESHAPE_H
#define NETLIST_LINESHAPE_H

#include "Symbol.h"
#include "Shape.h"
#include "Box.h"

namespace Netlist
{
    class LineShape : public Shape
    {
        public:
            LineShape(Symbol*, int x1, int y1, int x2, int y2);
            ~LineShape();
            Box getBoundingBox() const;

            inline int getX1() const {return x1_;}
            inline int getY1() const {return y1_;}
            inline int getX2() const {return x2_;}
            inline int getY2() const {return y2_;}
            LineShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
            void toXml(std::ostream&);
        private:
            int x1_, y1_, x2_, y2;
    }
}
#endif
