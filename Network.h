#ifndef NETWORK
#define NETWORK
class NetworkNodeInterface{
public:
    NetworkNodeInterface(){}
    virtual ~NetworkNodeInterface(){}
    virtual void activate(void* synapse) = 0;
    virtual void calculate() = 0;
    virtual void fire(NetworkNodeInteface* nni) = 0;
};
class Network{
public:
    Network();
    ~Network();
    void addNode(Ne