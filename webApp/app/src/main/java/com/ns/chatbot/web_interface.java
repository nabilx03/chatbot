package com.ns.chatbot;

import android.content.Context;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

public class web_interface {
    private Context mContext;

    public web_interface(Context context) {
        mContext = context;
    }

    @JavascriptInterface
    public String Test() {
        return "Test"; //anything else xD
    }

    @JavascriptInterface
    public void toastMessage(String m) {
        Toast toast = Toast.makeText(mContext, m, Toast.LENGTH_LONG);
        toast.show();
    }
}
