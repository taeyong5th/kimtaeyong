package com.ty.ballgame;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;

public class Box {

    public static final float BOX_SPEED = 2.0f;
    private int m_iBoxLength;
    private float m_fX, m_fY; // x, y
    private RectF m_BoxRect;
    private RectF m_DieRect;
    private float m_fSpeed;
    private int m_iLine;
    private float m_fDistance;
    private boolean m_bHasNextBox;

    Box(float x, float y, int line, int boxLength, float speed){
        this.m_fX = x;
        this.m_fY = y;
        this.m_iBoxLength = boxLength;
        this.m_fSpeed = speed;
        this.m_iLine = line;
        m_fDistance = 0.0f;
        m_bHasNextBox = false;

        m_BoxRect = new RectF();
        m_DieRect = new RectF();
        m_DieRect.set(x, y + 10.0f, x + 20.0f * boxLength, y + 20.0f);
        m_BoxRect.set(m_fX, m_fY, m_fX + 20.0f * m_iBoxLength, m_fY + 20.0f);
    }

    public void offset(float dx, float dy){
        m_fX += dx;
        m_fY += dy;
        m_DieRect.set(m_fX, m_fY + 10.0f, m_fX + 20.0f * m_iBoxLength, m_fY + 20.0f);
        m_BoxRect.set(m_fX, m_fY, m_fX + 20.0f * m_iBoxLength, m_fY + 20.0f);
    }

    public void update(float eTime){
        m_fDistance += Math.abs(eTime * m_fSpeed);
        m_fX += eTime * m_fSpeed;

        m_DieRect.set(m_fX, m_fY + 10.0f, m_fX + 20.0f * m_iBoxLength, m_fY + 20.0f);
        m_BoxRect.set(m_fX, m_fY, m_fX + 20.0f * m_iBoxLength, m_fY + 20.0f);
    }

    public boolean hasNextBox(){return m_bHasNextBox;}
    public void setHasNextBox(boolean hasNext){m_bHasNextBox = hasNext;}

    public boolean isGameOver(RectF rect){
        return m_DieRect.intersect(rect);
    }

    public boolean isCollide(RectF rect){
        return m_BoxRect.intersect(rect);
    }

    public float getDistance(){return m_fDistance;}

    public float getSpeed(){
        return m_fSpeed;
    }

    public int getLine(){
        return m_iLine;
    }
    public void decreaseLine(){ m_iLine--; };

    public int getLength(){
        return m_iBoxLength;
    }

    public float getX(){return m_fX;}
    public float getY(){return m_fY;}

    public void draw(Canvas canvas){
        Paint paint = new Paint();
        paint.setColor(Color.BLACK);
        //canvas.drawText(""+m_fDistance, m_fX, m_fY, paint);
        for(int i = 0; i < m_iBoxLength; ++i){
            if(i == 0) {
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexCambelL, m_fX + 20.0f * i, m_fY);
            } else if(i == m_iBoxLength - 1){
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexCambelR, m_fX + 20.0f * i, m_fY);
            } else {
                BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexCambelC, m_fX + 20.0f * i, m_fY);
            }
        }
    }
}
