package paulscode.android.mupen64plusae.dialog;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import androidx.fragment.app.DialogFragment;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AlertDialog.Builder;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;

import com.bda.controller.Controller;

import app.megaemulators.megan64.beta.R;

import java.util.ArrayList;
import java.util.List;

import paulscode.android.mupen64plusae.input.provider.AbstractProvider;
import paulscode.android.mupen64plusae.input.provider.AbstractProvider.OnInputListener;
import paulscode.android.mupen64plusae.input.provider.AxisProvider;
import paulscode.android.mupen64plusae.input.provider.KeyProvider;
import paulscode.android.mupen64plusae.input.provider.KeyProvider.ImeFormula;
import paulscode.android.mupen64plusae.input.provider.MogaProvider;

public class PromptInputCodeDialog extends DialogFragment
{
    private static final String STATE_TITLE = "STATE_TITLE";
    private static final String STATE_MESSAGE = "STATE_MESSAGE";
    private static final String STATE_NEUTRAL_BUTTON_TEXT = "STATE_NEUTRAL_BUTTON_TEXT";
    private static final String STATE_NUM_ITEMS = "STATE_NUM_ITEMS";
    private static final String STATE_ITEMS = "STATE_ITEMS";

    /**
     * The listener interface for receiving an input code provided by the user.
     * 
     * @see PromptInputCodeDialog
     */
    public interface PromptInputCodeListener
    {
        /**
         * Called when the dialog is dismissed and should be used to process the
         * input code provided by the user.
         * 
         * @param inputCode
         *            The input code provided by the user, or 0 if the user
         *            clicks one of the dialog's buttons.
         * @param hardwareId
         *            The identifier of the source device, or 0 if the user
         *            clicks one of the dialog's buttons.
         * @param which
         *            The DialogInterface button pressed by the user.
         */
        public void onDialogClosed(int inputCode, int hardwareId, int which);
        
        /**
         * Returns an instance of the Moga controller
         * @return instance of the Moga controller
         */
        public Controller getMogaController();
    }

    public static PromptInputCodeDialog newInstance(String title, String message,
        String neutralButtonText, List<Integer> ignoredKeyCodes)
    {
        PromptInputCodeDialog frag = new PromptInputCodeDialog();
        Bundle args = new Bundle();
        args.putString(STATE_TITLE, title);
        args.putString(STATE_MESSAGE, message);
        args.putString(STATE_NEUTRAL_BUTTON_TEXT, neutralButtonText);

        args.putInt(STATE_NUM_ITEMS, ignoredKeyCodes.size());

        for (int index = 0; index < ignoredKeyCodes.size(); ++index)
        {
            Integer seq = ignoredKeyCodes.get(index);
            args.putInt(STATE_ITEMS + index, seq);
        }

        frag.setArguments(args);
        return frag;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        setRetainInstance(true);

        final String title = getArguments().getString(STATE_TITLE);
        final String message = getArguments().getString(STATE_MESSAGE);
        final String neutralButtonText = getArguments().getString(STATE_NEUTRAL_BUTTON_TEXT);
        final int numItems = getArguments().getInt(STATE_NUM_ITEMS);

        List<Integer> ignoredKeyCodes = new ArrayList<Integer>();

        for (int index = 0; index < numItems; ++index)
        {
            Integer seq = getArguments().getInt(STATE_ITEMS + index);
            ignoredKeyCodes.add(seq);
        }

        final ArrayList<AbstractProvider> providers = new ArrayList<AbstractProvider>();

        // Create a widget to dispatch key/motion event data
        FrameLayout view = new FrameLayout(getActivity());
        ImageView image = new ImageView(getActivity());
        image.setImageResource(R.drawable.ic_controller);
        EditText dummyImeListener = new EditText(getActivity());
        dummyImeListener.setVisibility(View.INVISIBLE);
        dummyImeListener.setHeight(0);
        view.addView(image);
        view.addView(dummyImeListener);

        // Set the focus parameters of the view so that it will dispatch events
        view.setFocusable(true);
        view.setFocusableInTouchMode(true);
        view.requestFocus();

        // Create the input event providers
        providers.add(new KeyProvider(view, ImeFormula.DEFAULT, ignoredKeyCodes));
        
        if (getActivity() instanceof PromptInputCodeListener)
        {
            providers.add(new MogaProvider(((PromptInputCodeListener) getActivity()).getMogaController()));
        }
        else
        {
            Log.e("PromptInputCodeDialog", "Activity doesn't implement PromptInputCodeListener");
        }
        
        providers.add(new AxisProvider(view));

        // Notify the client when the user clicks the dialog's positive button
        DialogInterface.OnClickListener clickListener = new OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                onInputCommon(providers, getActivity(), 0, 0, which);
            }
        };

        Builder builder = new Builder(getActivity());
        builder.setTitle(title);
        builder.setMessage(message);
        builder.setCancelable(false);
        builder.setNegativeButton(getActivity().getString(android.R.string.cancel), clickListener);
        builder.setNeutralButton(neutralButtonText, clickListener);
        builder.setPositiveButton(null, null);
        builder.setView(view);
        
        final AlertDialog promptInputCodeDialog = builder.create();

        OnInputListener inputListener = new OnInputListener()
        {
            private float[] mStrengths = null;
            @Override
            public void onInput(int[] inputCodes, float[] strengths, int hardwareId)
            {
                if (inputCodes == null || strengths == null)
                    return;

                // Find the strongest input
                float maxStrength = -1;
                int strongestInputCode = 0;
                Log.e("PromptInputCodeDialog", "Inputs start");
                for (int i = 0; i < inputCodes.length; i++)
                {
                    if(strengths[i] != 0.0f)
                        Log.e("PromptInputCodeDialog", "Inputs[" + i + "] = " + strengths[i] + " maxStrength = " + maxStrength);

                    //The size of the strength array changed. We need to reset
                    if(mStrengths != null && mStrengths.length != inputCodes.length)
                    {
                        mStrengths = null;
                    }

                    // Identify the strongest input and last one to have changed
                    if (Math.abs(strengths[i]) > maxStrength && mStrengths != null && !compareStrengths(mStrengths[i], strengths[i], 0.1f))
                    {
                        Log.e("PromptInputCodeDialog", "Detected change in " + i);

                        maxStrength = strengths[i];
                        strongestInputCode = inputCodes[i];
                    }
                }
                Log.e("PromptInputCodeDialog", "Inputs end");
                //Only allow the input if a significant change is detected
                if(mStrengths != null)
                {
                    // Call the overloaded method with the strongest found
                    onInput(strongestInputCode, maxStrength, hardwareId);
                }

                mStrengths = strengths;
            }

            @Override
            public void onInput(int inputCode, float strength, int hardwareId)
            {
                if (inputCode != 0)
                {
                    onInputCommon(providers, getActivity(), inputCode, hardwareId, DialogInterface.BUTTON_POSITIVE);

                    promptInputCodeDialog.dismiss();
                }
            }
        };

        // Connect the upstream event listeners
        for (AbstractProvider provider : providers)
            provider.registerListener(inputListener);
        
        
        return promptInputCodeDialog;
    }

    /**
     * Returns true if the two float arrays are about the same
     * @param strengths1
     * @param strengths2
     * @return true if the two float arrays are about the same
     */
    private boolean compareStrengths(float strengths1, float strengths2, float delta)
    {
        boolean areTheyAboutSame = true;
        areTheyAboutSame = Math.abs(strengths1 - strengths2) < delta;

        return areTheyAboutSame;
    }

    @Override
    public void onDestroyView()
    {
        // This is needed because of this:
        // https://code.google.com/p/android/issues/detail?id=17423

        if (getDialog() != null && getRetainInstance())
            getDialog().setDismissMessage(null);
        super.onDestroyView();
    }

    void onInputCommon(final ArrayList<AbstractProvider> providers, Activity activity, int inputCode, int hardwareId,
            int which) {
        for (AbstractProvider provider : providers)
            provider.unregisterAllListeners();

        if (activity instanceof PromptInputCodeListener) {
            ((PromptInputCodeListener) activity).onDialogClosed(inputCode, hardwareId, which);
        } else {
            Log.e("PromptInputCodeDialog", "Activity doesn't implement PromptInputCodeListener");
        }
    }
}