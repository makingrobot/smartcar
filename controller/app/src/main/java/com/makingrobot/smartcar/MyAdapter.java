package com.makingrobot.smartcar;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;

public class MyAdapter extends BaseAdapter {

    private List<BluetoothDevice> mBluelist;
    private LayoutInflater layoutInflater;

    public MyAdapter(Context context, List<BluetoothDevice> list) {
        this.mBluelist = list;
        this.layoutInflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return mBluelist.size();
    }

    @Override
    public Object getItem(int position) {
        return mBluelist.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View view, ViewGroup viewGroup) {

        ViewHolder viewHolder;
        if (view == null) {
            viewHolder = new ViewHolder();
            view = layoutInflater.inflate(R.layout.list_device_item, null);
            viewHolder.deviceName = (TextView)view.findViewById(R.id.device_name);
            viewHolder.deviceAddress = (TextView)view.findViewById(R.id.device_address);
            viewHolder.deviceType = (TextView)view.findViewById(R.id.device_type);
            viewHolder.deviceState = (TextView)view.findViewById(R.id.device_state);
            view.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder) view.getTag();
        }
        //详细参考：http://blog.csdn.net/mirkowu/article/details/53862842
        BluetoothDevice blueDevice = mBluelist.get(position);
        //设备名称
        String deviceName = blueDevice.getName();
        viewHolder.deviceName.setText(TextUtils.isEmpty(deviceName) ? "未知设备" : deviceName);
        //设备的蓝牙地（地址为17位，都为大写字母-该项貌似不可能为空）
        String deviceAddress = blueDevice.getAddress();
        viewHolder.deviceAddress.setText(deviceAddress);
        //设备的蓝牙设备类型（DEVICE_TYPE_CLASSIC 传统蓝牙 常量值：1, DEVICE_TYPE_LE  低功耗蓝牙 常量值：2
        //DEVICE_TYPE_DUAL 双模蓝牙 常量值：3. DEVICE_TYPE_UNKNOWN：未知 常量值：0）
        int deviceType = blueDevice.getType();
        if (deviceType == 0) {
            viewHolder.deviceType.setText("未知类型");
        } else if (deviceType == 1) {
            viewHolder.deviceType.setText("传统蓝牙");
        } else if (deviceType == 2) {
            viewHolder.deviceType.setText("低功耗蓝牙");
        } else if (deviceType == 3) {
            viewHolder.deviceType.setText("双模蓝牙");
        }
        //设备的状态（BOND_BONDED：已绑定 常量值：12, BOND_BONDING：绑定中 常量值：11, BOND_NONE：未匹配 常量值：10）
        int deviceState = blueDevice.getBondState();
        if (deviceState == 10) {
            viewHolder.deviceState.setText("未匹配");
        } else if (deviceState == 11) {
            viewHolder.deviceState.setText("绑定中");
        } else if (deviceState == 12) {
            viewHolder.deviceState.setText("已绑定");
        }
        //返回远程设备支持的UUID。此方法从远程设备检索UUID不启动服务。 而是返回服务UUID的本地缓存。
        //如果需要刷新UUID，使用fetchUuidsWithSdp（）方法
        //ParcelUuid[] deviceUuid = blueDevice.getUuids();
        //blueDevice.fetchUuidsWithSdp(); boolean类型
        return view;
    }

    private class ViewHolder {
        TextView deviceName;
        TextView deviceAddress;
        TextView deviceType;
        TextView deviceState;
    }
}