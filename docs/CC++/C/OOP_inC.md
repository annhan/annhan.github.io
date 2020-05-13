---
layout: default
title: 
---


```
typedef struct PointTag {
    int16_t x; /* x-coordinate */
    int16_t y; /* y-coordinate */
} Point;

void Point_ctor(Point *me, int16_t x, int16_t y) {
    me->x = x;
    me->y = y;
}

void Point_move(Point *me, int16_t dx, int16_t dy) {
    me->x += dx;
    me->y += dy;
}

int16_t Point_dist(Point const *me, Point const *other) {
    int16_t dx = me->x – other->x;
    int16_t dy = me->y – other->y;
    return (int16_t)sqrt(dx*dx + dy*dy);
}

    Point foo, bar, tar; /* multiple instances of Point */
    int16_t dist;
    Point_ctor(&foo, 0, 0);
    Point_ctor(&bar, 1, 1);
    Point_ctor(&tar, -1, 2);
    dist = Point_dist(&foo, &bar);
    Point_move(&tar, 2, 4);
    dist = Point_dist(&bar, &tar);
    

```

**Kế thừa**
--------

```
typedef struct ColoredPointTag {
    Point super; /* derives from Point */
    uint16_t color; /* 16-bit color */
} ColoredPoint;

void ColoredPoint_ctor(ColoredPoint *me,
         int16_t x, int16_t y, uint16_t color)
{
    Point_ctor(&me->super, x, y); /* call superclass’ ctor */
    me->color = color;
}

    ColoredPoint p1, p2;int16_t dist;
    ColoredPoint_ctor(&p1, 0, 2, RED);

    ColoredPoint_ctor(&p2, 0, 2, BLUE);
    /* re-use inherited function */
    dist = Point_dist((Point *)&p1, (Point *)&p2);
```