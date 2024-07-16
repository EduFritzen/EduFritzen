package com.edujhuan.adventurequest.Screens;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.utils.Disposable;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.edujhuan.adventurequest.AdventureQuest;

public class Hud implements Disposable{
    public Stage stage;        // when the game moves, the hud must stay in the same position.
    private Viewport viewport; // we need to use a new camera and a new viewport for the hud.
    
    // game widgets
    private Label levelLabel;
    private Label stageLabel;

    public Hud(SpriteBatch batch){

        // setting the hud viewport with a new camera
        viewport = new FitViewport(AdventureQuest.V_WIDTH, AdventureQuest.V_HEIGHT, new OrthographicCamera());
        stage = new Stage(viewport, batch);  // define stage using the new viweport
        Table table = new Table(); // Table helps to organize the labels of the hud
        table.top(); // labels at the top of the screen
        table.setFillParent(true); // table is the size of the stage

        // define the label using a string, a LabelStyle and a color
        levelLabel = new Label("1", new Label.LabelStyle(new BitmapFont(), Color.WHITE));
        stageLabel = new Label("Fase", new Label.LabelStyle(new BitmapFont(), Color.WHITE));


        // add the labels in the table
        table.add(stageLabel).expandX().padTop(10);
        table.row(); // create a new row
        table.add(levelLabel).expandX();

        stage.addActor(table); // add the table in the stage
    }

    @Override
    public void dispose(){
        stage.dispose();
    }

}