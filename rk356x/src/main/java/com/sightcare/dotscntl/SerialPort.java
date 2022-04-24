package com.sightcare.dotscntl;

import android.util.Log;

public class SerialPort {
    // Used to load the 'dotscntl' library on application startup.
    static {
        System.loadLibrary("dotscntl");
    }

    private final String TAG = "SerialPort";

    public String pathname;
    private int fd = 0;
    private boolean isopen = false;

    SerialPort(String pathname) {
        this.pathname = pathname;
    }
    /**
     * A native method that is implemented by the 'dotscntl' native library,
     * which is packaged with this application.
     */
    public void openPort()
    {
        if(isopen == true)
            return;

        int ret;
        ret = open(pathname);

        if(ret > 0)
        {
            fd = ret;
            isopen = true;
        }
        /* TODO error handle */
        else
            Log.e(TAG, "Failed to open port.");;
    }

    public void closePort()
    {
        if(isopen == true)
        {
            close(fd);
            isopen = false;
        }
    }

    public void setBaudrate(int baudrate)
    {
        if(fd <= 0)
            return;
        int ret;
        ret = set(fd, baudrate);

        if(ret < 0)
            Log.e(TAG, "Failed to set baudrate.");
    }

    public void sendData(byte[] tb)
    {
        if(fd <= 0)
            return;
        int ret;
        ret = send(fd, tb, tb.length);

        if(ret != tb.length)
            Log.e(TAG, "Failed to send data or send data partly.");
    }

    public byte[] reveiveData(int count)
    {
        if(fd <= 0)
        {
            byte[] b= {0x00};
            return b;
        }
        return receive(fd, count);
    }

    private native int open(String path);
    private native void close(int fd);
    private native int set(int fd, int baudrate);
    private native int send(int fd, byte[] tb, int count);
    private native byte[] receive(int fd, int count);
}
