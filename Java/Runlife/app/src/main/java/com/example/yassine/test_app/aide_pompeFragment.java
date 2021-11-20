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
public class aide_pompeFragment extends Fragment {

    Button valider_pompe;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.aide_pompe, container, false);


        valider_pompe = (Button)view.findViewById(R.id.btn_valider_pompe);
        valider_pompe.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
                fragmentTransaction.replace(R.id.main_layout,new prog_pecs_f_Fragment());
                fragmentTransaction.commit();
            }
        });

        return view;
    }

}
