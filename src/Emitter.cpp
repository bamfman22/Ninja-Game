


#include "ofMain.h"
#include "Emitter.h"



//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
    sys = spriteSys;
    lifespan = -1;    // milliseconds
    started = false;
    lastSpawned = 0;
    rate = 1;    // sprites/sec
    haveChildImage = false;
    haveImage = false;
    velocity = ofVec3f(0, 0, 0);
    drawable = true;
    width = 50;
    height = 50;
    childWidth = 10;
    childHeight = 10;
    childVelocity = ofVec3f(0,0,0);
}



//sets how we want our child sprites to move
void Emitter::setChildVelocity(ofVec3f v){
    childVelocity = v;
}
//  Draw the Emitter
//
//
void Emitter::draw() {
    if (drawable) {
        
        if (haveImage) {
            image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
        }
        else {
            ofSetColor(0, 0, 255);
            ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
        }
    }
    sys->draw();
    
}



//fire class to shoot off the sprites
//can call this method in update to continually firing sprites based on the rate
void Emitter:: fire(){
    
    float time = ofGetElapsedTimeMillis();
    if ((time - lastSpawned) > (500.0 / rate)) {
        // spawn a new sprite
        Sprite sprite;
        if (haveChildImage) sprite.setImage(childImage);
        
        sprite.velocity = childVelocity;
        sprite.lifespan = lifespan;
        sprite.setPosition(trans);
        sprite.birthtime = time;
        sprite.width = childWidth;
        sprite.height = childHeight;
        sys->add(sprite);
        lastSpawned = time;
    }
    
    sys->draw();
}

//moves our emitter based on velocity and updates the sys
void Emitter::update() {
    
    trans += velocity / ofGetFrameRate();
    sys->update();
   
}

//set velocity for the missiles
void Emitter:: setVelocity(ofVec3f v){
    velocity = v;
}

void Emitter:: setDrawable(bool flag)
{
    drawable = flag;
}

void Emitter::setLifespan(float life) {
    lifespan = life;
}

float Emitter::maxDistPerFrame(){
    return velocity.length()/ofGetFrameRate();
}

void Emitter::setChildImage(ofImage img) {
    childImage = img;
    haveChildImage = true;
    childWidth = img.getWidth();
    childHeight = img.getHeight();
}

void Emitter::setImage(ofImage img) {
    image = img;
    haveImage = true;
}

void Emitter::setRate(float r) {
    rate = r;
}


void Emitter:: setWidth(float w){
    width = w;
}

void Emitter:: setHeight(float h){
    height = h;
}
