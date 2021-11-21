package com.example.yassine.test_app;



import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;



public class jambesFragment extends Fragment {

    Button btn_niv_f_jambes;
    Button btn_niv_m_jambes;
    Button btn_niv_h_jambes;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
            View view = inflater.inflate(R.layout.jambes, container, false);

        btn_niv_f_jambes = (Button) view.findViewById(R.id.btn_niv_f_jambes);
        btn_niv_f_jambes.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_jambes_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_m_jambes = (Button) view.findViewById(R.id.btn_niv_m_jambes);
        btn_niv_m_jambes.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_jambes_m_Fragment());
                fragmentTransaction.commit();
            }
        });

        btn_niv_h_jambes = (Button) view.findViewById(R.id.btn_niv_h_jambes);
        btn_niv_h_jambes.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_jambes_h_Fragment());
                fragmentTransaction.commit();
            }
        });


        return view;
    }

}