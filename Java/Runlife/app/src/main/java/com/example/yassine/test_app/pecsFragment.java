package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class pecsFragment extends Fragment {

    Button btn_niv_f_pecs;
    Button btn_niv_m_pecs;
    Button btn_niv_h_pecs;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.pecs, container, false);

        btn_niv_f_pecs = (Button) view.findViewById(R.id.btn_niv_f_pecs);
        btn_niv_f_pecs.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_pecs_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_m_pecs = (Button) view.findViewById(R.id.btn_niv_m_pecs);
        btn_niv_m_pecs.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_pecs_m_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_h_pecs = (Button) view.findViewById(R.id.btn_niv_h_pecs);
        btn_niv_h_pecs.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_pecs_h_Fragment());
                fragmentTransaction.commit();
            }
        });


        return view;

    }
}
