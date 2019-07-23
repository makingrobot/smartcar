package com.makingrobot.smartcar;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;

/**
 * Joystick view class.
 */
public class JoystickView extends FrameLayout implements View.OnTouchListener {

    private int buttonState;

    public JoystickView(Context context) {
        super(context);
        init(context,null, 0);
    }

    public JoystickView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context, attrs, 0);
    }

    public JoystickView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init(context, attrs, defStyle);
    }

    public int getButtonState() {
        return buttonState;
    }

    private void init(Context context, AttributeSet attrs, int defStyle) {

        View rootView = LayoutInflater.from(context).inflate(R.layout.joystick_view, this, true);

//        backwardPressState = action &= 1; 1 << 0
//        forwardPressState = action &= 2; 1 << 1
//        leftPressState = action &= 4;  1 << 2
//        rightPressState = action &= 8; 1 << 3
//        accelPressState = action &= 16; 1 << 4
//        stopPressState = action &= 32; 1 << 5

        Button downBtn = (Button)rootView.findViewById(R.id.downBtn);
        downBtn.setTag(0);
        downBtn.setOnTouchListener(this);

        Button upBtn = (Button)rootView.findViewById(R.id.upBtn);
        upBtn.setTag(1);
        upBtn.setOnTouchListener(this);

        Button leftBtn = (Button)rootView.findViewById(R.id.leftBtn);
        leftBtn.setTag(2);
        leftBtn.setOnTouchListener(this);

        Button rightBtn = (Button)rootView.findViewById(R.id.rightBtn);
        rightBtn.setTag(3);
        rightBtn.setOnTouchListener(this);

        Button accelBtn = (Button)rootView.findViewById(R.id.accelBtn);
        accelBtn.setTag(4);
        accelBtn.setOnTouchListener(this);

        Button stopBtn = (Button)rootView.findViewById(R.id.stopBtn);
        stopBtn.setTag(5);
        stopBtn.setOnTouchListener(this);

    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        int idx = (Integer)v.getTag();
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN: // press
                buttonState |= (1 << idx);  // 置1
                break;
            case MotionEvent.ACTION_UP: // release
                buttonState &= ~(1 << idx);  // 置0
        }
        return false;
    }
}
