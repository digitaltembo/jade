template<class KEY, class T>
class MapInterface{
public:
    MapInterface(){
    }
    virtual void hello() = 0;
    virtual T maybeReturn() = 0;
};