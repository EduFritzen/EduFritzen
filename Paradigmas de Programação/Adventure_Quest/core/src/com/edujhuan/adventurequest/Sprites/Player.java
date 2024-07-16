package com.edujhuan.adventurequest.Sprites;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.badlogic.gdx.physics.box2d.CircleShape;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.World;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.Gdx;
import com.edujhuan.adventurequest.AdventureQuest;
import com.edujhuan.adventurequest.Screens.PlayScreen;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class Player extends Sprite {
	public enum State {WALKING, ATTACKING, STANDING, JUMPING, DEAD};
	public State currentState;
	public State previousState;

    public World world;
    public Body b2body;

    private TextureRegion playerStand;
    private Animation<TextureRegion> playerWalk;
	private Animation<TextureRegion> playerAttack;
	private TextureRegion playerDead; 

	private float stateTimer;
	private boolean walkingRight;
	private boolean Atacking;
	private boolean playerIsDead;

    public Player(World world, PlayScreen screen){
		// initialize default values
        super(screen.getAtlas().findRegion("front"));
        this.world=world;
        currentState = State.STANDING;
		previousState = State.STANDING;
		stateTimer = 0;
		walkingRight = true;
		Array<TextureRegion> frames = new Array<TextureRegion>();

		// get walk animation and add them to playerWalk
		for(int i = 2; i < 4; i++)
			frames.add(new TextureRegion(getTexture(), i * 65, 0, 58, 58));
		playerWalk = new Animation<TextureRegion>(0.5f, frames);
		frames.clear(); // it need to be clear to set the other animations

		// get attack animation and add them to playerAttack
		for(int i = 0; i < 9; i++)
			frames.add(new TextureRegion(getTexture(), i * 100, 58 ,56, 58));
		playerAttack = new Animation<TextureRegion>(0.1f, frames);
		frames.clear(); // it need to be clear to set the other animations

		playerStand = new TextureRegion(getTexture(), 1330, 65, 58, 58); // create the TextureRegion for player standing
		playerDead= new TextureRegion(getTexture(), 1330, 65, 58, 58); // create the TextureRegion for player dead


		definePlayer(); // define player in Box2D

		// define location and size of the player
        setBounds(0, 0, 25/AdventureQuest.PPM, 25/AdventureQuest.PPM);
        setRegion(playerStand); // initial frame stagnant
    }

    public void update(float delta){
		// update the sprite to override the Box2D body
        setPosition(b2body.getPosition().x - getWidth()/2, b2body.getPosition().y - getHeight()/2);

        setRegion(getFrame(delta)); // update sprite with the appropriate frame
    }

	public TextureRegion getFrame(float delta){
		currentState = getState(); // get the player state
		TextureRegion region;

		switch(currentState){ // get the corect animation KeyFrame depending the currentState
			case WALKING:
				region = playerWalk.getKeyFrame(stateTimer, true);
				break;
			case ATTACKING:
				region = playerAttack.getKeyFrame(stateTimer);
				if(playerAttack.isAnimationFinished(stateTimer))
					Atacking = false;

				break;
			case DEAD:
				region = playerDead;

				break;
			case STANDING:
			default:
				region = playerStand;
				break;
		}

		// if the player is walking in the left direction
		if((b2body.getLinearVelocity().x < 0 || !walkingRight) && !region.isFlipX()){
			region.flip(true, false);
			walkingRight = false;
		}
		// if the player is walking in the right direction
		else if((b2body.getLinearVelocity().x > 0 || walkingRight) && region.isFlipX()){
			region.flip(true, false);
			walkingRight = true;
		}
		
		// if the currentState is equal to the previousState increase the stateTimer, if is not equal reset stateTimer
		stateTimer = currentState == previousState ? stateTimer + delta : 0;

		previousState = currentState; // update the previous state
		return region; // final adjusted frame
	}

	public State getState(){
		// Test Box2D for velocity on the X and Y
		if(b2body.getLinearVelocity().y <= -2){
			playerIsDead = true;
			return State.DEAD;
		}
		else if(b2body.getLinearVelocity().x != 0){
			return State.WALKING;
		}else if(Atacking){
			b2body.setBullet(false);
			return State.ATTACKING;
		}
		else{
			playerIsDead = false;
			return State.STANDING;
		}


	}

	public void Atack(){
		Atacking = true;
		setBounds(getX(), getY(), getWidth(), getHeight());
	}

	public boolean getAtack(){
		if(Atacking == true)
			return true;
		else
			return false;
	}

	public boolean IsDead(){
		return playerIsDead; 
	}

	public float getStateTimer() {
		return stateTimer;
	}

    public void definePlayer(){
        BodyDef bdef = new BodyDef();
        bdef.position.set(200/AdventureQuest.PPM, 200/AdventureQuest.PPM);
        bdef.type = BodyDef.BodyType.DynamicBody;
        b2body = world.createBody(bdef);
        FixtureDef fdef = new FixtureDef();
        CircleShape shape = new CircleShape();
        shape.setRadius(8/AdventureQuest.PPM);
        fdef.shape = shape;
        b2body.createFixture(fdef);
    }
}
