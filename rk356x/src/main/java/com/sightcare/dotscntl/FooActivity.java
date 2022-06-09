package com.sightcare.dotscntl;

import static com.sightcare.dotscntl.DotsControlPacket.*;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.sightcare.dotscntl.databinding.ActivityFooBinding;


public class FooActivity extends AppCompatActivity {

    private static final String TAG = "FooActivity";
    private ActivityFooBinding binding;

    private GPIO gpio3_C2 = new GPIO(3 * 32 + 2 * 8 + 2);
    private SerialPort serialPort3 = new SerialPort("/dev/ttyS3");
    private SerialPort serialPort4 = new SerialPort("/dev/ttyS4");
    private byte[] foo = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityFooBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        gpio3_C2.setDirection(gpio3_C2.getNum(), GPIO.GPIO_MODE_TYPE_OUTPUT);

        /* TODO test on board */
        short[] payload = { 0x00, 0x11, 0x22, 0x33,
                            0x44, 0x55, 0x66, 0x77,
                            0x88, 0x99, 0xAA, 0xBB,
                            0xCC, 0xDD, 0xEE, 0xFF};

        DotsControlPacket dcp = new DotsControlPacket(R2S_COMMAND_ALL_DATA, payload.length, 1, payload);
        byte[] packet = dcp.buildPacket();

        serialPort3.sendData(packet);
    }

    public void GPIO3_C2_Output(View view)
    {
        int viewID = view.getId();

        if(viewID == binding.buttonGPIO3C2High.getId())
        {
            gpio3_C2.setHigh(gpio3_C2.getNum());
        }
        else if(viewID == binding.buttonGPIO3C2Low.getId())
        {
            gpio3_C2.setLow(gpio3_C2.getNum());
        }
    }

    public void UARTProcess(View view)
    {
        int viewID = view.getId();

        if(viewID == binding.buttonUART3Open.getId())
        {
            serialPort3.openPort();
            serialPort3.setBaudrate(9600);
        }
        else if(viewID == binding.buttonUART4Open.getId())
        {
            serialPort4.openPort();
            serialPort4.setBaudrate(9600);
        }
        else if(viewID == binding.buttonUART3Close.getId())
        {
            serialPort3.closePort();
        }
        else if(viewID == binding.buttonUART4Close.getId())
        {
            serialPort4.closePort();
        }
        else if(viewID == binding.buttonUART3TX.getId())
        {
            serialPort3.sendData(foo);
        }
        else if(viewID == binding.buttonUART4TX.getId())
        {

        }
        else if(viewID == binding.buttonUART3RX.getId())
        {
            serialPort3.openPort();

            byte[] rb = serialPort3.reveiveData(100);
            String s = new String(rb);

            binding.textViewU3RX.setText(s);
        }
        else if(viewID == binding.buttonUART4RX.getId())
        {

        }
    }
}