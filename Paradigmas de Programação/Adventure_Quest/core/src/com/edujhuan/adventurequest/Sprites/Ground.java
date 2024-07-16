package com.edujhuan.adventurequest.Sprites;

import com.badlogic.gdx.maps.tiled.TiledMap;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.physics.box2d.World;

public class Ground extends InteractiveTileObject{
    public Ground(World world, TiledMap map, Rectangle bounds){
        super(world, map, bounds);
    }
}
