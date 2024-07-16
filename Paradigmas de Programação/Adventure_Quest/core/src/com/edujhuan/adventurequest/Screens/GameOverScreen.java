package com.edujhuan.adventurequest.Screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.edujhuan.adventurequest.AdventureQuest;

public class GameOverScreen implements Screen {
    private Image img;
    private Viewport viewport;
    private Stage stage;
    private AdventureQuest game;
    private Table table;

    public GameOverScreen(AdventureQuest game){
        this.game = game;
        viewport = new FitViewport(AdventureQuest.V_WIDTH, AdventureQuest.V_HEIGHT, new OrthographicCamera());
        stage = new Stage(viewport, ((AdventureQuest) game).batch);
		img = new Image(new Texture("adventurequest.png"));

        table = new Table();
        table.center();
        table.setFillParent(true);

        table.add(img).expandX();
        stage.addActor(table);


    }
	
    @Override
    public void show() {
    }
	
    @Override
    public void render(float delta) {

        if((Gdx.input.isKeyJustPressed(Input.Keys.ENTER))){
			game.setScreen(new PlayScreen(game));
        }
		
        Gdx.gl.glClearColor(0, 0, 0, 1);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        stage.draw();

    }

    @Override
    public void resize(int width, int height) {
    }

    @Override
    public void pause() {
    }

    @Override
    public void resume() {
    }

    @Override
    public void hide() {
    }

	@Override
	public void dispose() {
	}
}
