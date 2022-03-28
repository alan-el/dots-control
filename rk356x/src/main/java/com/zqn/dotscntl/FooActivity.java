package com.zqn.dotscntl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.zqn.dotscntl.databinding.ActivityFooBinding;


public class FooActivity extends AppCompatActivity {

    private static final String TAG = "FooActivity";
    private ActivityFooBinding binding;

    private SerialPort serialPort = new SerialPort("/dev/ttyS4");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityFooBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        // Example of a call to a native method
        TextView tv = binding.sampleText;

    }


}