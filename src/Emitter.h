#pragma once
//----------------------------------------------------------------------------------
//
//
//
//
//  Derek Ortega CS134

#include "Sprite.h"


//  General purpose Emitter class for emitting sprites
//  
//
class Emitter : public BaseObject {
public:
    void move(ofVec3f);
    void fire();
    Emitter(SpriteSystem *);
    void draw();
    void setWidth(float);
    void setHeight(float);
    void setVelocity(ofVec3f);
    void setLifespan(float);
    void setDrawable(bool);
    void setChildImage(ofImage);
    void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
    float maxDistPerFrame();
    void setImage(ofImage);
    void setRate(float);
    void update();
    SpriteSystem *sys;
    float rate;
    ofVec3f velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofVec3f childVelocity;
    void setChildVelocity(ofVec3f v);
    ofImage childImage;
    ofImage image;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
    float childWidth, childHeight;
    
};
