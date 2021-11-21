package com.example.yassine.test_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;



public class aide_crunchFragment extends Fragment {

    Button valider_crunch;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.aide_crunch, container, false);

        valider_crunch = (Button) view.findViewById(R.id.btn_valider_crunch); //La variable "valider_crunch" correspond à un bouton, et est associé à l'identifiant btn_valider_crunch.
        valider_crunch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {  //On met le bouton valider_crunch sur "écoute".
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new prog_abdos_f_Fragment()); //On ouvre le Fragment prog_abdos_f_Fragment.
                fragmentTransaction.commit();
            }
        });

        return view; //On affiche le layout aide_crunch.xml.
    }

}
