package com.makingrobot.smartcar;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.Manifest;
import android.app.Fragment;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.calypso.bluelib.bean.MessageBean;
import com.calypso.bluelib.bean.SearchResult;
import com.calypso.bluelib.listener.OnConnectListener;
import com.calypso.bluelib.listener.OnReceiveMessageListener;
import com.calypso.bluelib.listener.OnSearchDeviceListener;
import com.calypso.bluelib.listener.OnSendMessageListener;
import com.calypso.bluelib.manage.BlueManager;
import com.calypso.bluelib.utils.TypeConversion;

public class ChooseBtFragment extends Fragment
{

    public static final String TAG = ChooseBtFragment.class.getSimpleName();

    public interface OnChooseListener {
        void onChoosed(String mac);
        void onCancel();
    }

    private OnChooseListener chooseListener;
    public void setOnChooseListener(OnChooseListener chooseListener) {
        this.chooseListener = chooseListener;
    }

    private View view;
    private BlueManager bluemanage;
    private int progress = 0;
    private TextView statusView;
    private TextView contextView;
    private ProgressBar progressBar;
    private StringBuilder stringBuilder;
    private List<SearchResult> mDevices;
    private DeviceListAdapter mAdapter;
    private RecyclerView recycleView;
    private RelativeLayout devieslist;
    private RelativeLayout deviesinfo;
    private OnConnectListener onConnectListener;
//    private OnSendMessageListener onSendMessageListener;
    private OnSearchDeviceListener onSearchDeviceListener;
//    private OnReceiveMessageListener onReceiveMessageListener;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup viewGroup, Bundle bundler) {
    	if (view == null) {
    		initView(inflater, viewGroup);
    	}
    	
    	return view;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();

        if (handler != null) {
            handler.removeCallbacksAndMessages(null);
            handler = null;
        }
    }

    public void initView(LayoutInflater inflater, ViewGroup container) {

    	view = inflater.inflate(R.layout.fragment_choose_bt, container, false);

        mDevices = new ArrayList<>();
        mAdapter = new DeviceListAdapter(mDevices);
        stringBuilder = new StringBuilder();
        devieslist = (RelativeLayout)view.findViewById(R.id.parent_r1);
        deviesinfo = (RelativeLayout)view.findViewById(R.id.parent_r2);
        progressBar = (ProgressBar)view.findViewById(R.id.progressbar);
        recycleView = (RecyclerView)view.findViewById(R.id.blue_rv);
        recycleView.setLayoutManager(new LinearLayoutManager(getActivity()));
        contextView = (TextView)view.findViewById(R.id.context);
        statusView = (TextView)view.findViewById(R.id.status);
        recycleView.setAdapter(mAdapter);

        if (Build.VERSION.SDK_INT >= 23) {
            if (ContextCompat.checkSelfPermission(getActivity(),
                    Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(getActivity(), new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, 2);
                if (ActivityCompat.shouldShowRequestPermissionRationale(getActivity(),
                        Manifest.permission.READ_CONTACTS)) {
                    Toast.makeText(getContext(), "shouldShowRequestPermissionRationale", Toast.LENGTH_SHORT).show();
                }
            }
        }
        initBlueManager();
        initLisetener();
    }

    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            String message = msg.obj.toString();
            switch (msg.what) {
                case 0:
                    statusView.setText(message);
                    break;
                case 1:
                    stringBuilder.append(message + " \n");
                    contextView.setText(stringBuilder.toString());
                    progress += 4;
                    progressBar.setProgress(progress);
                    break;
                case 2:
                    progress = 100;
                    progressBar.setProgress(progress);
                    break;
                case 3:
                    statusView.setText("接收完成！");
                    stringBuilder.delete(0, stringBuilder.length());
                    stringBuilder.append(message);
                    contextView.setText(stringBuilder.toString());
                    break;
                case 4:
                    deviesinfo.setVisibility(View.VISIBLE);
                    devieslist.setVisibility(View.GONE);

                    String mac = message;

                    if (chooseListener != null) {
                        chooseListener.onChoosed( mac);
                    }

                    break;
            }
        }
    };

    /**
     * 初始化蓝牙管理，设置监听
     */
    public void initBlueManager() {
        onSearchDeviceListener = new OnSearchDeviceListener() {
            @Override
            public void onStartDiscovery() {
                sendMessage(0, "正在搜索设备..");
                Log.d(TAG, "onStartDiscovery()");

            }

            @Override
            public void onNewDeviceFound(BluetoothDevice device) {
                Log.d(TAG, "new device: " + device.getName() + " " + device.getAddress());
            }

            @Override
            public void onSearchCompleted(List<SearchResult> bondedList, List<SearchResult> newList) {
                Log.d(TAG, "SearchCompleted: bondedList" + bondedList.toString());
                Log.d(TAG, "SearchCompleted: newList" + newList.toString());
                sendMessage(0, "搜索完成,点击列表进行连接！");
                mDevices.clear();
                mDevices.addAll(newList);
                mAdapter.notifyDataSetChanged();
                deviesinfo.setVisibility(View.GONE);
                devieslist.setVisibility(View.VISIBLE);
            }

            @Override
            public void onError(Exception e) {
                sendMessage(0, "搜索失败");
            }
        };
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
            }

            @Override
            public void onError(Exception e) {
                sendMessage(0, "连接异常！");
                Log.i("blue", "onError");
            }
        };
//        onSendMessageListener = new OnSendMessageListener() {
//            @Override
//            public void onSuccess(int status, String response) {
//                sendMessage(0, "发送成功！");
//                Log.i("blue", "send message is success ! ");
//            }
//
//            @Override
//            public void onConnectionLost(Exception e) {
//                sendMessage(0, "连接断开！");
//                Log.i("blue", "send message is onConnectionLost ! ");
//            }
//
//            @Override
//            public void onError(Exception e) {
//                sendMessage(0, "发送失败！");
//                Log.i("blue", "send message is onError ! ");
//            }
//        };
//        onReceiveMessageListener = new OnReceiveMessageListener() {
//
//
//            @Override
//            public void onProgressUpdate(String what, int progress) {
//                sendMessage(1, what);
//            }
//
//            @Override
//            public void onDetectDataUpdate(String what) {
//                sendMessage(3, what);
//            }
//
//            @Override
//            public void onDetectDataFinish() {
//                sendMessage(2, "接收完成！");
//                Log.i("blue", "receive message is onDetectDataFinish");
//            }
//
//            @Override
//            public void onNewLine(String s) {
//                sendMessage(3, s);
//            }
//
//            @Override
//            public void onConnectionLost(Exception e) {
//                sendMessage(0, "连接断开");
//                Log.i("blue", "receive message is onConnectionLost ! ");
//            }
//
//            @Override
//            public void onError(Exception e) {
//                Log.i("blue", "receive message is onError ! ");
//            }
//        };
        bluemanage = BlueManager.getInstance(getActivity());
        bluemanage.setOnSearchDeviceListener(onSearchDeviceListener);
        bluemanage.setOnConnectListener(onConnectListener);
//        bluemanage.setOnSendMessageListener(onSendMessageListener);
//        bluemanage.setOnReceiveMessageListener(onReceiveMessageListener);
        bluemanage.requestEnableBt();
    }

    /**
     * 为控件添加事件监听
     */
    public void initLisetener() {

        mAdapter.setOnItemClickListener(new DeviceListAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(DeviceListAdapter adapter, View view, int position) {
                String mac = mDevices.get(position).getAddress();
                bluemanage.connectDevice(mac);
            }
        });

        view.findViewById(R.id.btn_search).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluemanage.setReadVersion(false);
                bluemanage.searchDevices();
            }
        });

        view.findViewById(R.id.get_sn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MessageBean item = new MessageBean(TypeConversion.getDeviceVersion());
                bluemanage.setReadVersion(true);
                bluemanage.sendMessage(item, true);
            }
        });

        view.findViewById(R.id.btn_close).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bluemanage.closeDevice();
                contextView.setText(null);
                devieslist.setVisibility(View.VISIBLE);
                deviesinfo.setVisibility(View.GONE);
            }
        });

        view.findViewById(R.id.btn_send).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluemanage.setReadVersion(false);
                progress = 0;
                progressBar.setProgress(progress);
                stringBuilder.delete(0, stringBuilder.length());
                contextView.setText("");
                MessageBean item = new MessageBean(TypeConversion.startDetect());
                bluemanage.sendMessage(item, true);
            }
        });
    }

    /**
     * @param type    0 修改状态  1 更新进度  2 体检完成  3 体检数据进度
     * @param context
     */
    public void sendMessage(int type, String context) {
        if (handler != null) {
            Message message = handler.obtainMessage();
            message.what = type;
            message.obj = context;
            handler.sendMessage(message);
        }
    }

    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (requestCode == 2) {
            if (permissions[0].equals(Manifest.permission.ACCESS_COARSE_LOCATION) && grantResults[0]
                    == PackageManager.PERMISSION_GRANTED) {
            } else {
                if (!ActivityCompat.shouldShowRequestPermissionRationale(getActivity(), Manifest.
                        permission.ACCESS_COARSE_LOCATION)) {
                    return;
                }
            }
        }
    }

}  
