package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class prog_pecs_f_Fragment extends Fragment {

    Button ic_info_pecs_f_pompe;
    Button ic_info_pecs_f_dev_couche;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.prog_pecs_f, container, false);

        ic_info_pecs_f_pompe = (Button)view.findViewById(R.id.ic_info_pecs_f_pompe);
        ic_info_pecs_f_pompe.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_pompeFragment());
                fragmentTransaction.commit();
            }
        });

        ic_info_pecs_f_dev_couche = (Button) view.findViewById(R.id.ic_info_pecs_f_dev_couche);
        ic_info_pecs_f_dev_couche.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new aide_dev_coucheFragment());
                fragmentTransaction.commit();
            }
        });

        return view;
    }

}
