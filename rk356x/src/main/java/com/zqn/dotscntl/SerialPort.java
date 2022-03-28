package com.zqn.dotscntl;

public class SerialPort {
    // Used to load the 'dotscntl' library on application startup.
    static {
        System.loadLibrary("dotscntl");
    }
    public String pathname;
    private int fd;

    SerialPort(String pathname) {
        this.pathname = pathname;
    }
    /**
     * A native method that is implemented by the 'dotscntl' native library,
     * which is packaged with this application.
     */
    public native String NativeFoo(int num);
    public native int open(String path);
    public native void close(int fd);
    public native int set(int fd, int baudrate);
    public native int send(int fd, byte[] tb, int count);
    public native byte[] receive(int fd, int count);
}
