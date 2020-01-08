package com.ty.ballgame;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameView extends SurfaceView implements SurfaceHolder.Callback{

    public static GameManager m_GameManager;
    private MyThread mThread;
    int Width, Height;
    private long m_lLastTime;

    public GameView(Context context) {
        super(context);
        SurfaceHolder holder = getHolder();
        holder.addCallback(this);

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.ball_tour);
        bitmap = Bitmap.createScaledBitmap(bitmap, 512, 1024, true);
        BitmapManager.setBitmap(bitmap);
        Width = GameUtils.getWidth(context);
        Height = GameUtils.getHeight(context);
        BitmapManager.setDisplaySize(Width, Height);

        Log.v("test", ""+bitmap.getWidth());
        Log.v("test", ""+bitmap.getHeight());

        mThread = new MyThread(holder, this);
        m_GameManager = new GameManager();

    }

    public void update() {
        long lCurTime = System.currentTimeMillis();
        m_GameManager.update(((float) (lCurTime - m_lLastTime)) / 1000.0f);
        m_lLastTime = lCurTime;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        mThread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    //Thread Class
    public class MyThread extends Thread
    {
        SurfaceHolder mHolder;
        GameView mGameView;
        public MyThread(SurfaceHolder holder, GameView gameView)
        {
            mHolder = holder;
            mGameView = gameView;

            //연산 부분
        }

        public void drawEverything(Canvas canvas)
        {
            Paint p1 = new Paint();
            p1.setColor(Color.RED);
            p1.setTextSize(50);
            //canvas.drawBitmap(screen, 0, 0, p1);
            canvas.drawText("ASDB", 240, 120, p1);

            BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexBack, 0, 0);
            BitmapManager.DrawBitmap(canvas, BitmapManager.cImageIndexTitle, 0, 0);

            BitmapManager.DrawBitmapNumber(canvas, 0);

        }

        public void run()
        {
            Canvas canvas = null;
            while(true)
            {
                mGameView.update();
                canvas = mHolder.lockCanvas();

                try
                {
                    synchronized(mHolder)
                    {

                        //drawEverything(canvas);
                        m_GameManager.draw(canvas);
                    }
                }
                finally
                {
                    if(canvas != null)
                    {
                        mHolder.unlockCanvasAndPost(canvas);
                    }
                }
            }
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        float x = (event.getX() * 240.0f) / ((float)Width);
        float y = (event.getY() * 400.0f) / ((float)Height);
        if(event.getAction() == MotionEvent.ACTION_DOWN)
        {
            m_GameManager.touchDown(x, y);
        }
        else if(event.getAction() == MotionEvent.ACTION_UP)
        {
            m_GameManager.touchUp(x, y);
        }
        return true;
    }
}
