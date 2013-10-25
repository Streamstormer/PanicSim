#ifndef StateMachine_hpp
#define StateMachine_hpp
class ClStateMachine
{
public:
    ClStateMachine() {}
    ~ClStateMachine() {}

    bool isInDangerByThreat() {return false;}
    bool isHearThreat() {return true;}

private:

};
#endif // StateMachine_hpp
