package com.sightcare.dotscntl;

public class DotsControlPacket {
    public static final int R2S_COMMAND_ALL_DATA = 0;
    public static final int R2S_COMMAND_PART_DATA = 1;
    public static final int R2S_COMMAND_ALL_UP = 2;
    public static final int R2S_COMMAND_ALL_DOWN = 3;

    public static final int S2R_COMMAND_ALL_DATA = 10;

    private int cmdType;
    private int payloadLen;
    private int sqcNum;
    /*! NOTE value range: [0x0000 - 0x00FF] */
    short [] payload;

    DotsControlPacket(int ct, int pl, int sn, short[] p)
    {
        cmdType = ct;
        payloadLen = pl;
        sqcNum = sn;
        payload = p.clone();
    }

    public byte[] buildPacket()
    {
        return build(cmdType, payloadLen, sqcNum, payload);
    }
    private native byte[] build(int cmd_type, int payload_len, int sqc_num, short[] pld);
}
