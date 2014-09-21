#ifndef VEC2
#define VEC2

#include <vector>

using std::vector;

template <class T>
class Vec2D{
public:
    Vec2D(){};
    Vec2D(int width, int height);
   ~Vec2D();
    void resize(int width, int height);
    vector<T> operator[](unsigned i);
    T get(int x, int y);
    T set(int x, int y, T t);
private:
    vector<vector<T> >* v;
};

#endif
