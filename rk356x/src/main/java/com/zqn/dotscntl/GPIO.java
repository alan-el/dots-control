package com.zqn.dotscntl;

/* Just For GPIO Output Mode */

public class GPIO {
    private int num;

    GPIO(int num){
        this.num = num;
    }

    public native void export(int gpio_num);
    public native void unexport(int gpio_num);
    public native void setDirection(int gpio_num, int dirct);
    public native void setHigh(int gpio_num);
    public native void setLow(int gpio_num);
}
