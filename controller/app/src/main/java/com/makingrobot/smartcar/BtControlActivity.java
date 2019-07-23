package com.makingrobot.smartcar;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


import com.calypso.bluelib.bean.MessageBean;
import com.calypso.bluelib.listener.OnConnectListener;
import com.calypso.bluelib.listener.OnReceiveMessageListener;
import com.calypso.bluelib.listener.OnSendMessageListener;
import com.calypso.bluelib.manage.BlueManager;
import com.calypso.bluelib.utils.TypeConversion;

import java.util.Timer;
import java.util.TimerTask;

public class BtControlActivity extends AppCompatActivity {

    public static final String TAG = BtControlActivity.class.getSimpleName();

    private DrawerLayout drawerLayout;
    private ChooseBtFragment chooseBtFragment;
    private JoystickView joystickView;
    private DirectionBoard directionBoard;
    private SpeedBoard speedBoard;

    private final Timer timer = new Timer();
    private int REQUEST_SELECT_BT = 1;

    private BlueManager blueManager;
    private OnSendMessageListener onSendMessageListener;
    private OnReceiveMessageListener onReceiveMessageListener;
    private OnConnectListener onConnectListener;
    private String blueMac;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bt_control);

        drawerLayout = (DrawerLayout)findViewById(R.id.drawerlayout);
        drawerLayout.setDrawerLockMode(DrawerLayout.LOCK_MODE_LOCKED_CLOSED | DrawerLayout.LOCK_MODE_LOCKED_OPEN);
        drawerLayout.setDrawerListener(new DrawerLayout.DrawerListener() {

            @Override
            public void onDrawerClosed(View arg0) {
            }

            @Override
            public void onDrawerOpened(View arg0) {
            }

            @Override
            public void onDrawerSlide(View arg0, float arg1) {
            }

            @Override
            public void onDrawerStateChanged(int arg0) {
            }

        });

        chooseBtFragment = new ChooseBtFragment();
        chooseBtFragment.setOnChooseListener(new ChooseBtFragment.OnChooseListener() {

            @Override
            public void onChoosed(String mac) {
                drawerLayout.closeDrawer(Gravity.RIGHT);

                initBlueManager(mac);
            }

            @Override
            public void onCancel() {
                drawerLayout.closeDrawer(Gravity.RIGHT);
            }

        });

        getFragmentManager().beginTransaction()
                .replace(R.id.chooseLayout, chooseBtFragment, "main")
                .addToBackStack("main")
                .commit();

        Button selectBtBtn = (Button)findViewById(R.id.selectBtBtn);
        selectBtBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                drawerLayout.openDrawer(Gravity.RIGHT);
            }
        });

        directionBoard = (DirectionBoard)findViewById(R.id.directionBoard);
        speedBoard = (SpeedBoard)findViewById(R.id.speedBoard);

        joystickView = (JoystickView)findViewById(R.id.joystickView);
        timer.schedule(timerTask, 200, 200);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (blueManager != null) {
            blueManager.close();
            blueManager = null;
        }
    }

    private void initBlueManager(String mac) {
        this.blueMac = mac;

        onConnectListener = new OnConnectListener() {
            @Override
            public void onConnectStart() {
                sendMessage(0, "开始连接");
                Log.i("blue", "onConnectStart");
            }

            @Override
            public void onConnectting() {
                sendMessage(0, "正在连接..");
                Log.i("blue", "onConnectting");
            }

            @Override
            public void onConnectFailed() {
                sendMessage(0, "连接失败！");
                Log.i("blue", "onConnectFailed");

            }

            @Override
            public void onConectSuccess(String mac) {
                sendMessage(4, mac);
                Log.i("blue", "onConectSuccess");

                initBlueManager(mac);
            }

            @Override
            public void onError(Exception e) {
                sendMessage(0, "连接异常！");
                Log.i("blue", "onError");
            }
        };
        onSendMessageListener = new OnSendMessageListener() {
            @Override
            public void onSuccess(int status, String response) {
                sendMessage(0, "发送成功！");
                Log.i("blue", "send message is success ! ");
            }

            @Override
            public void onConnectionLost(Exception e) {
                sendMessage(0, "连接断开！");
                Log.i("blue", "send message is onConnectionLost ! ");
                blueManager = null;
                reconnect();
            }

            @Override
            public void onError(Exception e) {
                sendMessage(0, "发送失败！");
                Log.i("blue", "send message is onError ! ");
            }
        };
        onReceiveMessageListener = new OnReceiveMessageListener() {

            @Override
            public void onProgressUpdate(String what, int progress) {
                sendMessage(1, what);
            }

            @Override
            public void onDetectDataUpdate(String what) {
                //sendMessage(3, what);
            }

            @Override
            public void onDetectDataFinish() {
                sendMessage(2, "接收完成！");
                Log.i("blue", "receive message is onDetectDataFinish");
            }

            @Override
            public void onNewLine(String s) {
                sendMessage(3, s);
            }

            @Override
            public void onNewData(int[] data) {
                sendMessage(5, data);
            }

            @Override
            public void onConnectionLost(Exception e) {
                sendMessage(0, "连接断开");
                Log.i("blue", "receive message is onConnectionLost ! ");
                blueManager = null;
                reconnect();
            }

            @Override
            public void onError(Exception e) {
                Log.i("blue", "receive message is onError ! ");
            }
        };
        blueManager = BlueManager.getInstance(getApplicationContext());
        blueManager.setOnConnectListener(onConnectListener);
        blueManager.setOnSendMessageListener(onSendMessageListener);
        blueManager.setOnReceiveMessageListener(onReceiveMessageListener);
        blueManager.setReadVersion(false);
    }

    private void reconnect() {
        blueManager.connectDevice(blueMac);
    }

    /**
     * @param type    0 修改状态  1 更新进度  2 体检完成  3 体检数据进度
     * @param context
     */
    public void sendMessage(int type, Object context) {
        if (msgHandler != null) {
            Message message = msgHandler.obtainMessage();
            message.what = type;
            message.obj = context;
            msgHandler.sendMessage(message);
        }
    }

    Handler msgHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            if (msg.what == 5) {
                int[] data = (int[])msg.obj;
                int carAngleValue = data[0];
                int accelValue = data[1];

                Log.d(TAG, "direction: " + carAngleValue + ", speed: " + accelValue);

                if (directionBoard.setCurrentStatus( (carAngleValue + 45) / 180.0f))
                    directionBoard.invalidate();
                if (speedBoard.setCurrentStatus (accelValue / 60.0f))
                    speedBoard.invalidate();
            } else {
                String message = msg.obj.toString();
                Log.d(TAG, "receive data: " + message);
            }
        }
    };

    Handler timerHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {

            // 要做的事情
            switch (msg.what) {
                case 1:
                    break;
            }
            super.handleMessage(msg);
        }
    };

    TimerTask timerTask = new TimerTask() {
        @Override
        public void run() {

            int joystickState = joystickView.getButtonState();

            if (blueManager != null) {

                MessageBean item = new MessageBean(TypeConversion.startDetect());
                item.data = new char[] {(char)joystickState};
                blueManager.sendMessage(item, true);

                Log.d(TAG, "Joystick State:" + Integer.toBinaryString(joystickState));
            }
        }
    };
}