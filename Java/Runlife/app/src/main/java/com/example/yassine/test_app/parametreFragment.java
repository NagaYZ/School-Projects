package com.example.yassine.test_app;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RatingBar;
import android.widget.TextView;


public class parametreFragment extends Fragment {

    TextView notetext;
    RatingBar notebar;
    SharedPreferences sharedPrefs;
    SharedPreferences.Editor editor;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.parametre, container, false);

        notetext = (TextView) view.findViewById(R.id.notetext);
        notebar = (RatingBar) view.findViewById(R.id.notebar);

        sharedPrefs = PreferenceManager.getDefaultSharedPreferences(getContext());

        float etoile = sharedPrefs.getFloat("numStars", 0);
        notebar.setRating(etoile);

        notebar.setOnRatingBarChangeListener(new RatingBar.OnRatingBarChangeListener() {
            @SuppressLint("SetTextI18n")
            @Override
            public void onRatingChanged(RatingBar ratingBar, float rating, boolean fromUser) {

                editor = getContext().getSharedPreferences("com.example.yassine.test_app", Context.MODE_PRIVATE).edit();
                final int numStars = ratingBar.getNumStars();
                editor = sharedPrefs.edit();
                editor.putFloat("numStars", rating);
                editor.apply();
                notetext.setText(getString(R.string.note_text)+"  " + rating +" " + getString(R.string.etoile));


            }
        });

        return view;
    }

}

