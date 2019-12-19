package com.soulseek.surfacegame;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.Display;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

public class MySurface extends SurfaceView implements SurfaceHolder.Callback
{
    //SurfaceView
    MyThread mThread;
    SurfaceHolder mHolder;
    Context mContext;

    Bitmap screen;
    int Width, Height;

    public MySurface(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        SurfaceHolder holder = getHolder();
        holder.addCallback(this);

        mThread = new MyThread(holder, context);
        InitApp();
    }

    //App 초기화
    private void InitApp()
    {
        Display display
                = ((WindowManager) mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();

        Width = display.getWidth();
        Height = display.getHeight();

        screen = BitmapFactory.decodeResource(getResources(), R.drawable.screen);
        screen = Bitmap.createScaledBitmap(screen, Width, Height, true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder)
    {
        //Thread Start
        mThread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder arg0, int format, int width, int height)
{

}

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {

    }

    //Thread Class
    public class MyThread extends Thread
    {
        public MyThread(SurfaceHolder holder, Context context)
        {
            mHolder = holder;
            mContext = context;

            //연산 부분
        }

        public void drawEverything(Canvas canvas)
        {
            Paint p1 = new Paint();
            p1.setColor(Color.RED);
            p1.setTextSize(50);
            canvas.drawBitmap(screen, 0, 0, p1);
        }

        public void run()
        {
            Canvas canvas = null;
            while(true)
            {
                canvas = mHolder.lockCanvas();

                try
                {
                    synchronized(mHolder)
                    {
                        drawEverything(canvas);
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
        if(event.getAction() == MotionEvent.ACTION_DOWN)
        {

        }

        return true;
    }
}


