package app.android.IME;

import android.inputmethodservice.InputMethodService;
import android.view.inputmethod.InputConnection;

public class SoftKeyboard extends InputMethodService {
	
	private StringBuilder mComposing = new StringBuilder();
	
	public void onCreate() {
		super.onCreate();
	}
	
	public boolean set_text(String str) {
		mComposing.append(str);
		return true;
	}
	
	public boolean commit_text() {
		InputConnection ic = this.getCurrentInputConnection();
		ic.commitText(mComposing, mComposing.length());
        mComposing.setLength(0);
        return true;
	}

}
