/*
 * Mupen64PlusAE, an N64 emulator for the Android platform
 * 
 * Copyright (C) 2013 Paul Lamb
 * 
 * This file is part of Mupen64PlusAE.
 * 
 * Mupen64PlusAE is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * Mupen64PlusAE is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with Mupen64PlusAE. If
 * not, see <http://www.gnu.org/licenses/>.
 * 
 * Authors: Paul Lamb
 */
package paulscode.android.mupen64plusae.cheat;

import app.megaemulators.megan64.beta.R;

import paulscode.android.mupen64plusae.cheat.OptionDialog.Listener;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.res.TypedArray;
import androidx.preference.Preference;
import androidx.preference.PreferenceViewHolder;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.CheckBox;

public class CheatPreference extends Preference implements Listener, View.OnLongClickListener,
        View.OnClickListener

{
    private static final int DEFAULT_VALUE = 0;
    
    private int mValue = DEFAULT_VALUE;
    private CheckBox mCheckbox;
    private final Context mContext;
    private final String mTitle;
    private final String mNotes;
    private final String[] mOptions;
    private final OptionDialog mOptionsDialog;
    private final int mCheatIndex;

    public CheatPreference( Context context, int cheatIndex, String title, String notes, String[] options )
    {
        super( context );
        
        if( TextUtils.isEmpty( title ) )
            title = context.getString( R.string.cheatNotes_title );
        if( TextUtils.isEmpty( notes ) )
            notes = context.getString( R.string.cheatNotes_none );
        
        if( options == null )
        {
            // Binary cheat
            mOptions = null;
            mOptionsDialog = null;
        }
        else
        {
            // Multi-choice cheat
            mOptions = new String[options.length + 1];
            mOptions[0] = context.getString( R.string.cheat_disabled );
            System.arraycopy( options, 0, mOptions, 1, options.length );
            mOptionsDialog = new OptionDialog( context, title, mOptions, this );
        }
        
        mContext = context;
        mCheatIndex = cheatIndex;
        mTitle = title;
        mNotes = notes;
        
        setTitle( title );
        setWidgetLayoutResource( R.layout.widget_checkbox );
    }
    
    public void setValue( int value )
    {
        mValue = value;
        persistInt( mValue );
    }
    
    public String getCheatCodeString( int index )
    {
        String result = Integer.toString( index );
        if( mOptions != null || mValue != 0 )
            result += "-" + Integer.toString( mValue - 1 );
        return result;
    }
    
    private boolean isCheatEnabled()
    {
        return mValue != 0;
    }
    
    @Override
    public CharSequence getSummary()
    {
        if( mOptions == null || mValue == 0 || mValue >= mOptions.length)
            return null;
        else
            return mOptions[mValue];
    }
    
    @Override
    protected Object onGetDefaultValue( TypedArray a, int index )
    {
        return a.getInteger( index, DEFAULT_VALUE );
    }
    
    @Override
    protected void onSetInitialValue( Object defaultValue )
    {
        try
        {
            setValue( getSharedPreferences().contains(getKey()) ? getPersistedInt( mValue ) : (Integer) defaultValue );
        }
        catch( ClassCastException e )
        {
            // Using an obsolete file for persistence
            Log.w( "CheatPreference", "Failure setting initial value", e );
            setValue( DEFAULT_VALUE );
        }
    }
    
    @Override
    public void onBindViewHolder(PreferenceViewHolder holder)
    {
        super.onBindViewHolder( holder );
               
        // Setup the click handling
        holder.itemView.setOnLongClickListener( this );
        holder.itemView.setOnClickListener( this );
        
        // Find and initialize the widgets
        mCheckbox = (CheckBox) holder.findViewById( R.id.widgetCheckbox );
        mCheckbox.setFocusable( false );
        mCheckbox.setFocusableInTouchMode( false );
        mCheckbox.setClickable( false );
        
        // Refresh the widgets
        if( mCheckbox != null )
        {
            mCheckbox.setChecked( isCheatEnabled() );
        }
    }
    
    @Override
    public void onClick( View v )
    {
        if( mOptionsDialog == null )
        {
            // Binary cheat
            if(mValue != 0)
            {
               setValue( DEFAULT_VALUE );
            }
            else
            {
                setValue( 1 );
            }
            refreshWidgets();
        }
        else
        {
            // Multi-choice cheat
            mOptionsDialog.show( mValue );
        }
    }
    
    @Override
    public void onOptionChoice( int choice )
    {
        setValue( choice );
        refreshWidgets();
    }
    
    @Override
    public boolean onLongClick( View v )
    {
        AlertDialog notesDialog;
        // Popup a dialog to display the cheat notes
        notesDialog = new Builder( mContext ).setTitle( mTitle ).setMessage( mNotes ).create();
        notesDialog.show();
        return true;
    }
    
    @Override
    public void onOptionLongPress( int item )
    {
        // TODO: Look through cheat options to see if any have really long strings.
        // If not, then long-pressing on cheat options for full text isn't needed.
        if( item != 0 )
        {
            AlertDialog optionNoteDialog;
            optionNoteDialog = new Builder( mContext ).setTitle(
                mContext.getString( R.string.cheatOption_title ) ).create();
            optionNoteDialog.setMessage( mOptions[item] );
            optionNoteDialog.show();
        }
    }
    
    private void refreshWidgets()
    {
        setSummary( getSummary() );
        if( mCheckbox != null )
        {
            mCheckbox.setChecked( isCheatEnabled() );
        }
    }
    
    public int getCheatIndex()
    {
        return mCheatIndex;
    }
}
