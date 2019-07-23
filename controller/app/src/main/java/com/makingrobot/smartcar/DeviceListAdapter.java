package com.makingrobot.smartcar;

import android.support.annotation.LayoutRes;
import android.support.annotation.Nullable;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.calypso.bluelib.bean.SearchResult;

import java.util.List;

public class DeviceListAdapter extends RecyclerView.Adapter {

    public static interface OnItemClickListener {
        void onItemClick(DeviceListAdapter adapter, View view, int position);
     }

     private OnItemClickListener onItemClickListener;

     public void setOnItemClickListener(OnItemClickListener itemClickListener) {
         this.onItemClickListener = itemClickListener;
     }

    private static final String TAG = DeviceListAdapter.class.getSimpleName();

    private List<SearchResult> list;

    public DeviceListAdapter(@Nullable List<SearchResult> data) {
        this.list = data;
    }

    @Override
     public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
         Log.d(TAG, "onCreateViewHolder, i: " + i);
         View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.device_list_item, null);
         LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
         view.setLayoutParams(lp);
         return new DeviceViewHolder(this, view);
     }

     @Override
     public void onBindViewHolder(RecyclerView.ViewHolder viewHolder, int i) {
         Log.d(TAG, "onBindViewHolder, i: " + i + ", viewHolder: " + viewHolder);
         DeviceViewHolder holder = (DeviceViewHolder) viewHolder;
         holder.position = i;
         SearchResult result = list.get(i);
         holder.nameText.setText(result.getName());
         holder.macText.setText(result.getAddress());
         holder.rssiText.setText(String.format("Rssi: %d", result.getRssi()));
     }

     @Override
     public int getItemCount() {
         return list != null ? list.size() : 0;
     }

     class DeviceViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener
     {
         public View rootView;
         public TextView nameText;
         public TextView macText;
         public TextView rssiText;

         private DeviceListAdapter adapter;
         public int position;

         public DeviceViewHolder(DeviceListAdapter adapter, View itemView) {
             super(itemView);
             this.adapter = adapter;
             nameText = (TextView) itemView.findViewById(R.id.name);
             macText = (TextView) itemView.findViewById(R.id.mac);
             rssiText = (TextView) itemView.findViewById(R.id.rssi);

             rootView = itemView.findViewById(R.id.device_item);
             rootView.setOnClickListener(this);
         }

         @Override
         public void onClick(View v) {
             if (null != onItemClickListener) {
                 onItemClickListener.onItemClick(adapter, itemView, position);
             }
         }
     }

}
