package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class abdosFragment extends Fragment {

    Button btn_niv_f_abdos;
    Button btn_niv_m_abdos;
    Button btn_niv_h_abdos;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.abdos, container, false);

        btn_niv_f_abdos = (Button) view.findViewById(R.id.btn_niv_f_abdos);
        btn_niv_f_abdos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_abdos_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_m_abdos = (Button) view.findViewById(R.id.btn_niv_m_abdos);
        btn_niv_m_abdos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_abdos_m_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_h_abdos = (Button) view.findViewById(R.id.btn_niv_h_abdos);
        btn_niv_h_abdos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_abdos_h_Fragment());
                fragmentTransaction.commit();
            }
        });


        return view;
    }


}





