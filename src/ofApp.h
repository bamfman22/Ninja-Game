#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Particle.h"
#include "ParticleEmitter.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;



class Emitter;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void checkCollisions();
    
    int level;
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void complexityCheck();
    float x;
    float y;
    Emitter *emitter;
    Emitter *invaderEmitter1;
    Emitter *invaderEmitter2;
    Emitter *invaderEmitter3;
    Emitter *turret;
    
    ofSoundPlayer soundPlayer;
    ofSoundPlayer soundPlayer1;
    ofSoundPlayer soundPlayer2;
    ofSoundPlayer soundPlayer3;
    
    int score = 0;
    int health = 100;
    ofImage ninja;
    ofImage monkey;
    ofImage shurikin;
    ofImage inv1;
    ofImage inv2;
    ofImage inv3;
    ofImage background;
    Sprite bullet;
    bool gameStart;
    
    
    ParticleEmitter explosion;
    ParticleEmitter underside;
    // adding forces
    //
    TurbulenceForce *turbForce;
    GravityForce *gravityForce;
    ImpulseRadialForce *radialForce;
    ImpulseRadialForce *radialForce1;
   
    
    
};

