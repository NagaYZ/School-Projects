package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class prog_bras_f_Fragment extends Fragment {

    Button ic_info_bras_f_curl;
    Button ic_info_bras_f_poulie;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.prog_bras_f, container, false);

        ic_info_bras_f_poulie = (Button)view.findViewById(R.id.ic_info_bras_f_poulie);
        ic_info_bras_f_poulie.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_poulieFragment());
                fragmentTransaction.commit();
            }
        });

        ic_info_bras_f_curl = (Button) view.findViewById(R.id.ic_info_bras_f_curl);
        ic_info_bras_f_curl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_curlFragment());
                fragmentTransaction.commit();
            }
        });

        return view;
    }

}
