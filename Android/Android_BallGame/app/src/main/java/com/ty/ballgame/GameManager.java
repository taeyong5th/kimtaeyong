package com.ty.ballgame;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.util.Log;

import androidx.core.view.MotionEventCompat;

import java.util.ArrayList;

public class GameManager {

    public static final int GAMESTATE_INTRO = 0;
    public static final int GAMESTATE_TITLE = 1;
    public static final int GAMESTATE_READY = 2;
    public static final int GAMESTATE_PLAY = 3;
    public static final int GAMESTATE_OVERFLASH = 4;
    public static final int GAMESTATE_OVER = 5;

    private float m_fTime;
    private int m_iFingerImageIndex = BitmapManager.cImageIndexJumpNavi1;

    private int gameState = GAMESTATE_INTRO;
    private Ball m_ball;
    private ArrayList<Box> m_boxList;

    private static float[] regenPosX = {0.0f, -20.0f, 220.0f, -20.0f, 220.0f, -20.0f};
    private static float[] regenPosY = {380.0f, 300.0f, 220.0f, 140.0f, 60.0f, -20.0f};

    private boolean m_bScroll;
    private int m_lastBoxDirection = 1;

    private int m_iWhiteAlpha = 0;
    private Paint m_WhitePaint = new Paint();

    private int m_iScore = 0;
    private int m_iBestScore = 0;


    GameManager() {
        gameState = GAMESTATE_TITLE;
        m_boxList = new ArrayList<>();
        m_ball = new Ball();
        m_WhitePaint.setColor(Color.WHITE);
        init();
    }

    private void init(){
        m_iScore = 0;
        m_lastBoxDirection = 1;
        m_bScroll = false;
        m_fTime = 0.0f;
        m_iWhiteAlpha = 0;
        m_ball.init();
        m_boxList.clear();
        for(int i = 0; i < 6; ++i){
            Box box;
            if(i == 0){
                box = new Box(regenPosX[i], regenPosY[i], i,12, 0.0f);
                m_boxList.add(box);
            }
            else if(i % 2 == 0){
                box = new Box(regenPosX[i], regenPosY[i], i, GameUtils.makeRandom(2, 4), -40.0f);
                m_boxList.add(box);
            } else{
                box = new Box(regenPosX[i], regenPosY[i], i, GameUtils.makeRandom(2, 4), 40.0f);
                m_boxList.add(box);
            }
        }

    }

    void touchDown(float x, float y){
        if(gameState == GAMESTATE_READY){
            setGameState(GAMESTATE_PLAY);
        } else if(gameState == GAMESTATE_TITLE){
            setGameState(GAMESTATE_READY);
        } else if(gameState == GAMESTATE_PLAY){
            m_ball.jump();
        }
    }

    void touchUp(float x, float y){
        if(gameState == GAMESTATE_OVER){
            RectF rcPlay = new RectF(33.0f, 292.0f, 116.0f, 332.0f);
            if (rcPlay.contains(x, y)) {
                init();
                gameState = GAMESTATE_READY;
            }
        }
    }

    Box getBoxWithBall(Ball ball){
        for(int i = 0; i < m_boxList.size(); ++i) {
            if(m_boxList.get(i).isCollide(ball.getBallRect())){
                return m_boxList.get(i);
            }
        }
        return null;
    }

    void setScroll(boolean scroll){
        m_bScroll = scroll;
    }

    boolean isScrolling(){return m_bScroll;}

    void addScore(){
        m_iScore++;
        if(m_iScore > m_iBestScore){
            m_iBestScore = m_iScore;
        }
    }

    void setGameState(int state){
        gameState = state;
        m_fTime = 0.0f;
        switch (gameState){
            case GAMESTATE_OVERFLASH:
                m_ball.setState(Ball.BALLSTATE_DIE);
                break;
        }
    }

    void decreaseLine(){
        for(int i = 0; i < m_boxList.size(); ++i){
            m_boxList.get(i).decreaseLine();
        }
        m_lastBoxDirection = -m_lastBoxDirection;
    }

    void createTopBox(){
        if(getBoxWithBall(m_ball) != null){
            Box box = new Box(regenPosX[4 + (m_lastBoxDirection + 1) / 2 ], getBoxWithBall(m_ball).getY() - 80.0f * 4,5, GameUtils.makeRandom(2, 4), 40.0f * m_lastBoxDirection);
            m_boxList.add(box);
        }
    }

    void updateBox(){
        for(int i = 0; i < m_boxList.size(); ++i){
            Box tempBox = m_boxList.get(i);
            if(!tempBox.hasNextBox()){
                if(tempBox.getSpeed() > 0 && tempBox.getX() > 60.0f){
                    int boxLength = GameUtils.makeRandom(2, 4);
                    Box box;
                    box = new Box(tempBox.getX() - 60.0f - boxLength * 20.0f, tempBox.getY(), tempBox.getLine(), boxLength, tempBox.getSpeed());
                    m_boxList.add(box);
                    tempBox.setHasNextBox(true);
                }
                if(tempBox.getSpeed() < 0 && tempBox.getX() + tempBox.getLength() * 20.0f < 240.0f - 60.0f){
                    int boxLength = GameUtils.makeRandom(2, 4);
                    Box box;
                    box = new Box(tempBox.getX() + 60.0f + tempBox.getLength() * 20.0f, tempBox.getY(), tempBox.getLine(), boxLength, tempBox.getSpeed());
                    m_boxList.add(box);
                    tempBox.setHasNextBox(true);
                }
            } else if(tempBox.getDistance() > 400.0f && tempBox.hasNextBox()){
                //m_boxList.remove(tempBox);
            }
        }

        RectF rect = new RectF(-160.0f, -20.0f, 480.0f, 440.0f);

        for(int i = 0; i < m_boxList.size(); ++i) {
            Box box = m_boxList.get(i);
            if (box.getLine() == -1)
                m_boxList.remove(box);
            else if(box.getSpeed() > 0.0f && box.getX() > 240.0f)
                m_boxList.remove(box);
            else if (box.getSpeed() < 0.0f && box.getX() + box.getLength() * 20.0f < 0)
                m_boxList.remove(box);
        }

        Log.v("test", ""+m_boxList.size());
    }

    void draw(Canvas canvas){
        BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexBack, 0, 0);
        switch (gameState){
            case GAMESTATE_TITLE:
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexTitle, 6.0f, 107.0f);
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexTTS, 32.0f, 226.0f);
                break;
            case GAMESTATE_READY:
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexReadyGo, 24.0f, 107.0f);
                BitmapManager.DrawBitmap(canvas, m_iFingerImageIndex, 77.0f, 209.0f);
            case GAMESTATE_PLAY:
                for(int i = 0; i < m_boxList.size(); ++i){
                    m_boxList.get(i).draw(canvas);
                }
                BitmapManager.DrawBitmapNumber(canvas, m_iScore);
                m_ball.draw(canvas);
                break;
            case GAMESTATE_OVERFLASH:
                for(int i = 0; i < m_boxList.size(); ++i){
                    m_boxList.get(i).draw(canvas);
                }
                BitmapManager.DrawBitmapNumber(canvas, m_iScore);
                m_ball.draw(canvas);
                m_WhitePaint.setAlpha(m_iWhiteAlpha);
                canvas.drawPaint(m_WhitePaint);
                break;
            case GAMESTATE_OVER:
                for(int i = 0; i < m_boxList.size(); ++i){
                    m_boxList.get(i).draw(canvas);
                }
                m_ball.draw(canvas);
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexScoreBoard, 33.0f, 176.0f);
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexGameOver, 32.0f, 72.0f);
                BitmapManager.DrawBitmap(canvas, 25, 34.0f, 293.0f);
                BitmapManager.DrawBitmap(canvas, 26, 122.0f, 293.0f);
                BitmapManager.DrawBitmapSmallNumber(canvas, m_iScore, 172, 222, false);
                BitmapManager.DrawBitmapSmallNumber(canvas, m_iBestScore, 172, 256, false);
                break;
        }
    }

    void update(float fTime) {
        m_fTime += fTime;
        switch (gameState){
            case GAMESTATE_INTRO:
                break;
            case GAMESTATE_TITLE:
                break;
            case GAMESTATE_READY:
                if(m_fTime > 0.25f){
                    m_iFingerImageIndex = (m_iFingerImageIndex == BitmapManager.cImageIndexJumpNavi1) ? BitmapManager.cImageIndexJumpNavi2 : BitmapManager.cImageIndexJumpNavi1;
                    m_fTime = 0.0f;
                }
                break;
            case GAMESTATE_PLAY:
                m_ball.update(fTime);
                if(m_bScroll){
                    for(int i = 0; i < m_boxList.size(); ++i) {
                        m_boxList.get(i).offset(0.0f, fTime * 120.0f);
                    }
                    m_ball.offset(0.0f, fTime * 120.0f);
                }
                for(int i = 0; i < m_boxList.size(); ++i) {
                    m_boxList.get(i).update(fTime);
                }
                updateBox();
                m_iWhiteAlpha = (int) (255.0f * m_fTime);
                break;
            case GAMESTATE_OVERFLASH:
                m_iWhiteAlpha = (int) (255.0f * m_fTime);
                if(m_fTime > 1.0f) {
                    setGameState(GAMESTATE_OVER);
                }
                break;
            case GAMESTATE_OVER:

                break;
        }
    }


}
