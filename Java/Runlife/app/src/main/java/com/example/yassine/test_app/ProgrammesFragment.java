package com.example.yassine.test_app;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.widget.Toast;

public class ProgrammesFragment extends Fragment {

    CheckBox checkBox1;
    CheckBox checkBox2;
    CheckBox checkBox3;
    CheckBox checkBox4;
    Button validation1;
    int valid1 = 0;
    int valid2 = 0;
    int valid3 = 0;
    int valid4 = 0;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_programmes, container, false);

        checkBox1 = (CheckBox) view.findViewById(R.id.checkBox1);
        checkBox2 = (CheckBox) view.findViewById(R.id.checkBox2);
        checkBox3 = (CheckBox) view.findViewById(R.id.checkBox3);
        checkBox4 = (CheckBox) view.findViewById(R.id.checkBox4);
        validation1 = (Button) view.findViewById(R.id.validation);

        validation1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (!checkBox1.isChecked() && !checkBox2.isChecked() && !checkBox3.isChecked() && !checkBox4.isChecked()){

                    Toast.makeText(getActivity(), R.string.msg_no_programmes,
                            Toast.LENGTH_SHORT).show();
                }
                if((checkBox1.isChecked() && checkBox2.isChecked()) || (checkBox1.isChecked() && checkBox3.isChecked()) || (checkBox1.isChecked() && checkBox4.isChecked())
                        || (checkBox2.isChecked() && checkBox3.isChecked()) || (checkBox2.isChecked() && checkBox4.isChecked()) || (checkBox3.isChecked() && checkBox4.isChecked())
                        || (checkBox1.isChecked() && checkBox2.isChecked() && checkBox3.isChecked()) || (checkBox1.isChecked() && checkBox2.isChecked() && checkBox4.isChecked())
                        || (checkBox2.isChecked() && checkBox3.isChecked() && checkBox4.isChecked()) ||(checkBox1.isChecked() && checkBox3.isChecked() && checkBox4.isChecked())){

                    checkBox1.setChecked(false);
                    checkBox2.setChecked(false);
                    checkBox3.setChecked(false);
                    checkBox4.setChecked(false);
                    Toast.makeText(getActivity(), R.string.msg_choix_programmes, 
                            Toast.LENGTH_SHORT).show();
                }
                if(checkBox1.isChecked() && !checkBox2.isChecked() && !checkBox3.isChecked() && !checkBox4.isChecked()){

                    FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                    fragmentTransaction.replace(R.id.main_layout, new abdosFragment());
                    fragmentTransaction.commit();
                }
                if(checkBox2.isChecked() && !checkBox1.isChecked() && !checkBox3.isChecked() && !checkBox4.isChecked()){

                    FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                    fragmentTransaction.replace(R.id.main_layout, new jambesFragment());
                    fragmentTransaction.commit();
                }
                if(checkBox3.isChecked() && !checkBox1.isChecked() && !checkBox2.isChecked() && !checkBox4.isChecked()){

                    FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                    fragmentTransaction.replace(R.id.main_layout, new pecsFragment());
                    fragmentTransaction.commit();
                }
                if(checkBox4.isChecked() && !checkBox1.isChecked() && !checkBox2.isChecked() && !checkBox3.isChecked()){

                    FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                    fragmentTransaction.replace(R.id.main_layout, new brasFragment());
                    fragmentTransaction.commit();
                }

            }
            });

        return view;
    }
}







