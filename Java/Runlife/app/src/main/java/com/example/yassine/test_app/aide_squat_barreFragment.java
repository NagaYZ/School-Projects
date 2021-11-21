package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


/**
 * A simple {@link Fragment} subclass.
 */
public class aide_squat_barreFragment extends Fragment {

    Button valider_squat_barre;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.aide_squat_barre, container, false);


        valider_squat_barre = (Button)view.findViewById(R.id.btn_valider_squat_barre);
        valider_squat_barre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new prog_jambes_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        return view;
    }

}
