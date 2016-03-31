package sonar.systems.framework;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Intent;
import android.os.Bundle;


public class SonarFrameworkActivity extends Cocos2dxActivity
{
	
	private static SonarFrameworkFunctions functions = null;
	private Cocos2dxGLSurfaceView glSurfaceView;
	
	protected SonarFrameworkActivity()
	{
		super();
	}
	
	@Override
	protected void onCreate(Bundle b)
	{
		super.onCreate(b);
		try {
			functions = new SonarFrameworkFunctions(this);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		functions.onCreate(b);
	}
	
	//
    // Fullscreen Mode Begin
	//
	public Cocos2dxGLSurfaceView onCreateView()
    {
        glSurfaceView = new Cocos2dxGLSurfaceView(this);

        this.hideSystemUI();

        // create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }
    

    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus)
        {
            this.hideSystemUI();
        }
    }

    private void hideSystemUI()
    {
        // Set the IMMERSIVE flag.
        // Set the content to appear under the system bars so that the content
        // doesn't resize when the system bars hide and show.
        glSurfaceView.setSystemUiVisibility(
                Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_STABLE 
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }
    // Fullscreen Mode End

	@Override
	protected void onStart() 
	{
		super.onStart();
		functions.onStart();
	}

	@Override
	protected void onStop() 
	{
		super.onStop();
		functions.onStop();
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		functions.onResume();
	}
	
	@Override
	protected void onActivityResult(int request, int response, Intent data)
	{
		super.onActivityResult(request, response, data);
		functions.onActivityResult(request, response, data);
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) 
	{
	    super.onSaveInstanceState(outState);
	    functions.onSaveInstanceState(outState);
	}

	@Override
	public void onPause() 
	{
	    super.onPause();
	    functions.onPause();
	}

	@Override
	public void onDestroy() 
	{
	    super.onDestroy();
	    functions.onDestroy();
	}
	
	@Override
	public void onBackPressed() 
	{
			if(functions.onBackPressed())
				return;
			else
				super.onBackPressed();
	}
	//Cocos2d-x
	static 
	{
			System.loadLibrary("cocos2dcpp");
	}
}