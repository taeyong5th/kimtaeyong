package com.ty.ballgame;

import android.graphics.Canvas;
import android.graphics.RectF;

public class Ball {

    public static final int BALLSTATE_LIVE = 0;
    public static final int BALLSTATE_DIE = 1;

    private float m_fX, m_fY;
    private float m_fWidth, m_fHeight;
    private float m_fOroginY; // origin Y
    private RectF m_BallRect;

    private float m_fSpeed; // x speed per sec
    private float m_fGravity;

    private boolean m_bIsJumping;
    private float m_fJumpTime;
    private static final float JUMP_TICK = 3.0f;
    private static final float JUMP_HEIGHT = 90.0f;
    private int m_ballState = BALLSTATE_LIVE;

    public Ball() {
        m_BallRect = new RectF();
        init();
    }

    void init(){
        m_ballState = BALLSTATE_LIVE;
        m_bIsJumping = false;
        m_fJumpTime = 0.0f;
        m_fSpeed = 0.0f;
        m_fGravity = 100.0f;
        m_fX = m_fY = 0.0f;
        m_fWidth = 25.0f;
        m_fHeight = 25.0f;
        m_BallRect.set(m_fX, m_fY, m_fX + m_fWidth, m_fY + m_fHeight);
        setPosition(0.0f, 270.0f);
    }

    void setPosition(float x, float y){
        m_fX = x;
        m_fY = y;
        m_BallRect.set(m_fX, m_fY, m_fX + m_fWidth, m_fY + m_fHeight);
    }

    RectF getBallRect(){
        return m_BallRect;
    }
    float getX(){return m_fX;};
    float getY(){return m_fY;};

    public void offset(float dx, float dy){
        m_fX += dx;
        m_fY += dy;
        m_fOroginY += dy;
        m_BallRect.set(m_fX, m_fY, m_fX + m_fWidth, m_fY + m_fHeight);
    }

    void jump(){
        if(!m_bIsJumping){
            m_bIsJumping = true;
            m_fOroginY = m_fY;
        }
    }

    void setState(int state){
        m_ballState = state;
    }

    void update(float eTime){
        if(GameView.m_GameManager.isScreenOut(this)){
            GameView.m_GameManager.setGameState(GameManager.GAMESTATE_OVERFLASH);
            return;
        }

        // when ball is jumping
        if(m_bIsJumping){
            m_fX += eTime * m_fSpeed * 1.4f;
            m_fJumpTime += eTime;
            m_fY = m_fOroginY - (float)Math.sin(m_fJumpTime * Math.PI / 0.8f) * JUMP_HEIGHT;
            setPosition(m_fX, m_fY);
            Box box = GameView.m_GameManager.getBoxWithBall(this);
            if(box != null && box.isGameOver(m_BallRect)){
                GameView.m_GameManager.setGameState(GameManager.GAMESTATE_OVERFLASH);
                return;
            }
            if(box != null && m_fJumpTime > 0.1f){
                m_bIsJumping = false;
                m_fJumpTime = 0.0f;

                if(box.getLine() != 1){
                    //setPosition(m_fX, box.getY() - 25.0f);
                    GameView.m_GameManager.addScore();
                    GameView.m_GameManager.decreaseLine();
                    GameView.m_GameManager.createTopBox();
                    GameView.m_GameManager.setScroll(true);
                } else{
                    m_fY = m_fOroginY;
                }
            }
        } else{
            Box box = GameView.m_GameManager.getBoxWithBall(this);
            if(box == null){
                m_fY += eTime * m_fGravity;
            } else {
                m_fSpeed = box.getSpeed();
                m_fX += eTime * m_fSpeed;
            }
        }

        if(GameView.m_GameManager.isScrolling() && m_fY > 275.0f){
            GameView.m_GameManager.setScroll(false);
        }
        setPosition(m_fX, m_fY);
    }

    public void draw(Canvas canvas){
        switch (m_ballState){
            case BALLSTATE_LIVE:
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexBall, m_fX, m_fY);
                break;
            case BALLSTATE_DIE:
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexBallDie, m_fX, m_fY);
                break;
        }
    }
}
