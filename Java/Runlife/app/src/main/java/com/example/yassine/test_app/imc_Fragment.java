package com.example.yassine.test_app;

import android.app.Dialog;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class imc_Fragment extends Fragment {

    String monpoids;
    String mataille;
    Button imc_btn;
    float x,y;

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.imc, container, false);

        final EditText poids = (EditText) view.findViewById(R.id.imc_text2_poids);
        final EditText taille = (EditText) view.findViewById(R.id.imc_text2_taille);
        final TextView result1 = (TextView) view.findViewById(R.id.imc_result1);
        final TextView result2 = (TextView) view.findViewById(R.id.imc_result2);
        imc_btn = (Button) view.findViewById(R.id.imc_btn);

        imc_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                monpoids = poids.getText().toString();
                mataille = taille.getText().toString();
                 x=Float.parseFloat(poids.getText().toString());
                 y=Float.parseFloat(taille.getText().toString());
                 double z = x/((y*0.01)*(y*0.01));

                if(!mataille.isEmpty() && !monpoids.isEmpty()) {

                    if (z < 16) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_tres_bas));
                        result2.setTextColor(Color.RED);
                    } else if ((16.5 < z) && (z < 18.5)) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_bas));
                        result2.setTextColor(Color.rgb(255, 160, 0));
                    } else if ((18.5 < z) && (z < 25)) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_normale));
                        result2.setTextColor(Color.GREEN);
                    } else if ((25 < z) && (z < 30)) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_surpoids));
                        result2.setTextColor(Color.rgb(255, 225, 0));
                    } else if ((30 < z) && (z < 35)) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_obesite_mod));
                        result2.setTextColor(Color.rgb(255, 160, 0));
                    } else if ((35 < z) && (z < 40)) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_obesite_ele));
                        result2.setTextColor(Color.RED);
                    } else if (40 < z) {
                        result1.setText(getString(R.string.imc_result) + z);
                        result2.setText(getString(R.string.imc_obesite_mor));
                        result2.setTextColor(Color.BLACK);
                    }
                    }
                }

        });
        return view;
    }
}


