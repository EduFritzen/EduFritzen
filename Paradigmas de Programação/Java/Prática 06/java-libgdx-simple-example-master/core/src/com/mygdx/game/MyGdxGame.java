package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.Input.Keys;

public class MyGdxGame extends ApplicationAdapter {
	SpriteBatch batch;
	Texture img;
	Music peakyMusic;
	OrthographicCamera camera;
	Rectangle bucket;

	@Override
	public void create () {
		batch = new SpriteBatch();
		img = new Texture("Cavalo.jpg");
		peakyMusic = Gdx.audio.newMusic(Gdx.files.internal("music.mp3"));
		peakyMusic.setLooping(true);
		peakyMusic.play();
	
		camera = new OrthographicCamera();
		camera.setToOrtho(false, 800, 480);
		
		// create a Rectangle to logically represent the bucket
		bucket = new Rectangle();
		bucket.x = 200 / 2 - 64 / 2; // center the bucket horizontally
		bucket.y = 60; // bottom left corner of the bucket is 20 pixels above the bottom screen edge
		bucket.width = 64;
		bucket.height = 64;
	}

	@Override
	public void render () {
		ScreenUtils.clear(1, 1, 0, 1);
		batch.begin();
		//batch.draw(img, 0, 0);

		batch.draw(img, bucket.x, bucket.y);
  
		batch.end();
		
		// process user input
  
		if(Gdx.input.isKeyPressed(Keys.LEFT)) bucket.x -= 200 * Gdx.graphics.getDeltaTime();
		if(Gdx.input.isKeyPressed(Keys.RIGHT)) bucket.x += 200 * Gdx.graphics.getDeltaTime();
		if(Gdx.input.isKeyPressed(Keys.DOWN)) bucket.y -= 200 * Gdx.graphics.getDeltaTime();
		if(Gdx.input.isKeyPressed(Keys.UP)) bucket.y += 200 * Gdx.graphics.getDeltaTime();
	}
	
	@Override
	public void dispose () {
		batch.dispose();
		img.dispose();
	}


}
