package com.edujhuan.adventurequest;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.edujhuan.adventurequest.Screens.GameOverScreen;

public class AdventureQuest extends Game {

	public static final int V_WIDTH = 400;  // Virtual Screen size
	public static final int V_HEIGHT = 208; // Virtual Screen size
	public static final float PPM = 100;    // Box2D(Pixels Per Meter)
	public SpriteBatch batch;	
	public static AssetManager manager;

	@Override
	public void create () {
		batch = new SpriteBatch();
		manager = new AssetManager();
		manager.load("audio/music/stage1.mp3", Music.class);
		manager.finishLoading();

		setScreen(new GameOverScreen(this)); // 
	}

	@Override
	public void render () {
		super.render(); //delegate the render method to the GameOverScreen whatever screen is active at the time
	}
	
}