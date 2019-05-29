#include "ofApp.h"
#include "Emitter.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    
    //set up all of the sound players
    soundPlayer.load("missle.mp3");
    soundPlayer1.load("explosion.mp3");
    soundPlayer2.load("hurt.mp3");
    soundPlayer3.load("backGroundMusic.mp3");
    soundPlayer3.setLoop(true);
    
    //create the necessary emitters
    emitter = new Emitter (new SpriteSystem());
    turret = new Emitter (new SpriteSystem());
    invaderEmitter1 = new Emitter(new SpriteSystem());
    invaderEmitter2 = new Emitter(new SpriteSystem());
    invaderEmitter3 = new Emitter(new SpriteSystem());
    
    //load the background
    background.loadImage("background.jpg");
    
    //initialize level to 0
    level = 0;
    
    //load all the images
    monkey.load("monkey.png");
    ninja.load("ninja.png");
    inv1.load("inv1.png");
    inv2.load("inv1.png");
    inv3.load("inv3.png");
    shurikin.load("Shiruken.png");
    
    
    //setting the images
    emitter->setImage(ninja);
    turret->setChildImage(shurikin);
    turret->setDrawable(false);
    underside.setChildImage(monkey);
    invaderEmitter1->setChildImage(inv1);
    invaderEmitter2->setChildImage(inv2);
    invaderEmitter3->setChildImage(inv3);
    
    turret->setChildSize(5,10);
    emitter->setChildSize(5, 10);
    
    
    x = ofGetWindowWidth()/2;
    y = ofGetWindowHeight()/2;
    
    gameStart = false;
    
    //set initial positions for emitters
    invaderEmitter1->setPosition(ofVec3f(-100, 0, 0));
    invaderEmitter2->setPosition(ofVec3f(1100, 0, 0));
    invaderEmitter3->setPosition(ofVec3f(500, -50, 0));
    turret->setPosition(ofVec3f(x,y-10,0));
    turret->setWidth(5);
    turret->setHeight(20);
    emitter->setPosition(ofVec3f(x, y, 0));
    
    //makes it so there is a straight path for bullet emitters
    turret->sys->bullet = true;
    
    
    turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
    gravityForce = new GravityForce(ofVec3f(0, -10, 0));
    radialForce = new ImpulseRadialForce(1000.0);
    
    
    explosion.sys->addForce(turbForce);
    explosion.sys->addForce(gravityForce);
    explosion.sys->addForce(radialForce);
    
    underside.sys->addForce(turbForce);
    underside.sys->addForce(new GravityForce(ofVec3f(0,200,0)));
    underside.sys->addForce(radialForce);
    underside.setVelocity(ofVec3f(-100,-800,0));
    underside.setParticleRadius(20);
    underside.setLifespan(-1);
    
    
    explosion.setVelocity(ofVec3f(1, 1, 0));
    explosion.setOneShot(true);
    explosion.setEmitterType(RadialEmitter);
    explosion.setGroupSize(100);
}



//--------------------------------------------------------------
void ofApp::update(){
   
    //wait for the game to start before doing anything
    if(gameStart){
        
    //set the turret to fire consecitively
    turret->setRate(1000);
        
    //set the rate equal to the level we are on so the difficulty will get increasingly harder
    invaderEmitter1->setRate(.1*level);
    invaderEmitter1->fire();
    invaderEmitter2->setRate(.1*level);
    invaderEmitter2->fire();
    invaderEmitter3->setRate(.1* level);
    invaderEmitter3->fire();
    underside.setRate(.05 * level);
    underside.posi = ofVec3f(ofRandom(20,1000),800,0);
    underside.velocity = ofVec3f(ofRandom(-100,100),0-800,0);
    
        
     //check for collisions
    checkCollisions();
        //update
        invaderEmitter1->update();
        invaderEmitter2->update();
        invaderEmitter3->update();
        turret->update();
        emitter->update();
        explosion.update();
        underside.update();
        
        //this will check our score and what we need to do
        complexityCheck();
    }
    
}


//checks our score and our health
void ofApp::complexityCheck(){
    
    if(score % 20 == 0){
        level++;
        score += 5;
        invaderEmitter1->childVelocity = invaderEmitter1->childVelocity * level;
        invaderEmitter2->childVelocity = invaderEmitter2->childVelocity * level;
        invaderEmitter3->childVelocity = invaderEmitter3->childVelocity * level;
    }
    
    if(health == 0){
        gameStart = false;
        ofSystemAlertDialog("YOU LOSE");
        ofExit();
    }
    
}

//checks for collsions of sprites and particles
void ofApp::checkCollisions(){
    float dist = 30;
    
    //this loop will iterate through each emitters sys and check that none of them are in contact with the bullet
    for(int i = 0; i < turret->sys->sprites.size(); i++){
        if(invaderEmitter1->sys->removeNear(turret->sys->sprites[i].trans, dist) ||
        invaderEmitter2->sys->removeNear(turret->sys->sprites[i].trans, dist) ||
           invaderEmitter3->sys->removeNear(turret->sys->sprites[i].trans, dist)||
           underside.sys->removeNear(turret->sys->sprites[i].trans, dist + 10)){
          
            explosion.sys->reset();
            explosion.start(turret->sys->sprites[i].trans);
            turret->sys->remove(i);
            soundPlayer1.play();
            score += 5;
            
        }
        
        
    }
    
    //this checks if the enemies collide with our hero
    if(invaderEmitter1->sys->removeNear(emitter->trans, dist) ||
       invaderEmitter2->sys->removeNear(emitter->trans, dist) ||
       invaderEmitter3->sys->removeNear(emitter->trans, dist) ||
       underside.sys->removeNear(emitter->trans, dist + 10)){
        health = health -10;
        soundPlayer2.play();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    background.draw(0,0);
    emitter->draw();
    turret->draw();
    invaderEmitter1->draw();
    invaderEmitter2->draw();
    invaderEmitter3->draw();
    
    //set initial velocity of the enemies
    invaderEmitter1->setChildVelocity(ofVec3f(100, 100,0));
    invaderEmitter3->setChildVelocity(ofVec3f(0, 250,0));
    invaderEmitter2->setChildVelocity(ofVec3f(-300, 500,0));
    turret->setChildVelocity(ofVec3f(0,-800,0));
    explosion.draw();
    underside.draw();
    
    
    //this is our scoreboard
    string str;
    str += "Score   Health  Level\n" + std::to_string(score) +"        "+ std::to_string(health) + "     " + std::to_string(level);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(str, ofGetWindowWidth()-170, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    //wait for a spacebar input to start the actual game as well as start our particle emitter
    if(!gameStart){
        switch (key){
            case ' ':
                gameStart= true;
                soundPlayer3.play();
                underside.start(ofVec3f(ofRandom(20,1000),800,0));
        }
    }
    else{
        
        //switch statement to move our hero
        switch(key){
            case 'w':{
                if(emitter->trans.y > 20){
                emitter->velocity=ofVec3f(0,-500,0);
                turret->velocity =ofVec3f(0,-500,0);}
                break;
            }
            case 'a':{
                if(emitter->trans.x > 20){
                emitter->velocity = (ofVec3f(-500,0,0));
                    turret->velocity = (ofVec3f(-500,0,0));}
                break;
            }
            case 's':{
                if(emitter->trans.y < 748){
                emitter->velocity = (ofVec3f(0,500,0));
                turret->velocity = (ofVec3f(0,500,0));}
                y = y + 20;
                break;
            }
            case 'd':{
                if(emitter->trans.x < 1010){
                emitter->velocity = (ofVec3f(500,0,0));
                turret->velocity = (ofVec3f(500,0,0));}
                x = x + 20;
                break;
            }
            case ' ':
            {
                turret->fire();
                soundPlayer.play();
                break;
            }
            
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
    //stops moving our character whatever way it was moving
    switch(key){
        case 'a':
            emitter->velocity = (ofVec3f(0,0,0));
            turret->velocity = (ofVec3f(0,0,0));
            break;
        case 'w':
            emitter->velocity = (ofVec3f(0,0,0));
            turret->velocity = (ofVec3f(0,0,0));
            break;
        case 's':
            emitter->velocity = (ofVec3f(0,0,0));
            turret->velocity = (ofVec3f(0,0,0));
            break;
        case 'd':
            emitter->velocity = (ofVec3f(0,0,0));
            turret->velocity = (ofVec3f(0,0,0));
            break;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
