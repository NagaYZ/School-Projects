package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class prog_abdos_f_Fragment extends Fragment {

    Button ic_info_abdos_f_crunch;
    Button ic_info_abdos_f_gainage;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.prog_abdos_f, container, false);

        ic_info_abdos_f_crunch = (Button)view.findViewById(R.id.ic_info_abdos_f_crunch);
        ic_info_abdos_f_crunch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_crunchFragment());
                fragmentTransaction.commit();
            }
        });

        ic_info_abdos_f_gainage = (Button) view.findViewById(R.id.ic_info_abdos_f_gainage);
        ic_info_abdos_f_gainage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_gainageFragment());
                fragmentTransaction.commit();
            }
        });
        return view;

    }

}
