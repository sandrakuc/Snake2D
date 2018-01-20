#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(int x, int y);
        virtual ~Point();
        int x;
        int y;
        double getConvertedX();
        double getConvertedZ();
    protected:

    private:
};

#endif // POINT_H
