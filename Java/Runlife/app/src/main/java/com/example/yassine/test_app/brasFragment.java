package com.example.yassine.test_app;



import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;



public class brasFragment extends Fragment {

    Button btn_niv_f_bras;
    Button btn_niv_m_bras;
    Button btn_niv_h_bras;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.bras, container, false);

        Button btn_niv_f_bras0 = (Button) view.findViewById(R.id.btn_niv_f_bras);
        btn_niv_f_bras0.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_bras_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        Button btn_niv_m_bras0 = (Button) view.findViewById(R.id.btn_niv_m_bras);
        btn_niv_m_bras0.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_bras_m_Fragment());
                fragmentTransaction.commit();
            }
        });

        Button btn_niv_h_bras0 = (Button) view.findViewById(R.id.btn_niv_h_bras);
        btn_niv_h_bras0.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout, new prog_bras_h_Fragment());
                fragmentTransaction.commit();
            }
        });


        return view;
    }
}
