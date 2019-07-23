package com.makingrobot.smartcar;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;

import org.xclcharts.chart.DialChart;
import org.xclcharts.common.MathHelper;
import org.xclcharts.renderer.XEnum;
import org.xclcharts.renderer.plot.PlotAttrInfo;
import org.xclcharts.renderer.plot.Pointer;
import org.xclcharts.view.GraphicalView;

import java.util.ArrayList;
import java.util.List;

public class DirectionBoard extends GraphicalView {

    private String TAG = "DirectionBoard";

    private DialChart chart = new DialChart();
    private float mPercentage = 0.5f;

    public DirectionBoard(Context context) {
        super(context);
        initView();
    }

    public DirectionBoard(Context context, AttributeSet attrs){
        super(context, attrs);
        initView();
    }

    public DirectionBoard(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        initView();
    }


    private void initView()
    {
        chartRender();
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        chart.setChartRange(w ,h );
    }

    public void chartRender()
    {
        try {

            chart.setStartAngle(180f);
            chart.setTotalAngle(180f);
            //设置标题背景
            //chart.setApplyBackgroundColor(true);
            //chart.setBackgroundColor( Color.rgb(28, 129, 243) );
            //绘制边框
            //chart.showRoundBorder();

            //设置当前百分比
            chart.getPointer().setPercentage(mPercentage);

            //设置指针长度
            chart.getPointer().setLength(0.75f);

            //增加轴
            addAxis();
            /////////////////////////////////////////////////////////////
            //增加指针
            addPointer();
            //设置附加信息
            addAttrInfo();
            /////////////////////////////////////////////////////////////

        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }

    }

    public void addAxis()
    {

        List<Float> ringPercentage = new ArrayList<Float>();
        float rper = MathHelper.getInstance().div(1, 4); //相当于40%	//270, 4
        ringPercentage.add(rper);
        ringPercentage.add(rper);
        ringPercentage.add(rper);
        ringPercentage.add(rper);

        List<Integer> rcolor  = new ArrayList<Integer>();
        rcolor.add(Color.rgb(242, 110, 131));
        rcolor.add(Color.rgb(238, 204, 71));
        rcolor.add(Color.rgb(42, 231, 250));
        rcolor.add(Color.rgb(140, 196, 27));
        chart.addStrokeRingAxis(0.95f,0.8f, ringPercentage, rcolor);

        List<String> rlabels  = new ArrayList<String>();
        rlabels.add("90");
        rlabels.add("45");
        rlabels.add("0");
        rlabels.add("45");
        rlabels.add("90");
        chart.addInnerTicksAxis(0.8f, rlabels);

        //chart.getPlotAxis().get(0).getFillAxisPaint().setColor(Color.rgb(28, 129, 243));
        //chart.getPlotAxis().get(1).getFillAxisPaint().setColor(Color.rgb(28, 129, 243));
        chart.getPlotAxis().get(1).getTickLabelPaint().setColor(Color.BLACK);
        chart.getPlotAxis().get(1).getTickMarksPaint().setColor(Color.BLACK);
        chart.getPlotAxis().get(1).hideAxisLine();
        chart.getPlotAxis().get(1).setDetailModeSteps(3);

        chart.getPointer().setPointerStyle(XEnum.PointerStyle.TRIANGLE);
        chart.getPointer().getPointerPaint().setColor(Color.rgb(217, 34, 34) );
        chart.getPointer().getPointerPaint().setStrokeWidth(3);
        chart.getPointer().getPointerPaint().setStyle(Paint.Style.STROKE);
        chart.getPointer().hideBaseCircle();

    }

    //增加指针
    public void addPointer()
    {
        chart.addPointer();
        List<Pointer> mp = chart.getPlotPointer();
        mp.get(0).setPercentage( mPercentage);
        //设置指针长度
        mp.get(0).setLength(0.75f);
        mp.get(0).getPointerPaint().setColor(Color.WHITE);
        mp.get(0).setPointerStyle(XEnum.PointerStyle.TRIANGLE);
        mp.get(0).hideBaseCircle();

    }


    private void addAttrInfo()
    {
        /////////////////////////////////////////////////////////////
        PlotAttrInfo plotAttrInfo = chart.getPlotAttrInfo();
        //设置附加信息
        Paint paintTB = new Paint();
        paintTB.setColor(Color.BLACK);
        paintTB.setTextAlign(Paint.Align.CENTER);
        paintTB.setTextSize(30);
        paintTB.setAntiAlias(true);
        plotAttrInfo.addAttributeInfo(XEnum.Location.TOP, "方向", 0.3f, paintTB);

        Paint paintBT = new Paint();
        paintBT.setColor(Color.BLACK);
        paintBT.setTextAlign(Paint.Align.CENTER);
        paintBT.setTextSize(35);
        paintBT.setFakeBoldText(true);
        paintBT.setAntiAlias(true);
        plotAttrInfo.addAttributeInfo(XEnum.Location.BOTTOM,
                Float.toString(MathHelper.getInstance().round((Math.abs(mPercentage - 0.5f) * 180),1)), 0.3f, paintBT);

        Paint paintBT2 = new Paint();
        paintBT2.setColor(Color.BLACK);
        paintBT2.setTextAlign(Paint.Align.CENTER);
        paintBT2.setTextSize(30);
        paintBT2.setFakeBoldText(true);
        paintBT2.setAntiAlias(true);
        plotAttrInfo.addAttributeInfo(XEnum.Location.BOTTOM, "", 0.4f, paintBT2);
    }

    public boolean setCurrentStatus(float percentage)
    {
        if (Math.abs(mPercentage - percentage)>0.01) {
            mPercentage = percentage;
            chart.clearAll();

            //设置当前百分比
            chart.getPointer().setPercentage(mPercentage);
            addAxis();
            //增加指针
            addPointer();
            addAttrInfo();
            return true;
        }

        return false;
    }


    @Override
    public void render(Canvas canvas) {
        try{
            chart.render(canvas);
        } catch (Exception e){
            Log.e(TAG, e.toString());
        }
    }

}

