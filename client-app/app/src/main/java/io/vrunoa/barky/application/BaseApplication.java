package io.vrunoa.barky.application;

import android.app.Application;
import android.util.Log;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;

import io.vrunoa.barky.services.CloudMessagingService;

public class BaseApplication extends Application {

    private static BaseApplication _instance;
    private String LOG_TAG = BaseApplication.class.getName();

    public BaseApplication() {
        super();
        _instance = this;
    }

    private boolean isGooglePlayServicesAvailable() {
        int status = GoogleApiAvailability.getInstance().isGooglePlayServicesAvailable(this);
        return status != ConnectionResult.SUCCESS ? false : true;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        if(isGooglePlayServicesAvailable()) {
            Log.d(LOG_TAG, "Google Play Services Available");
            CloudMessagingService.prepareService();
        } else {
            Log.d(LOG_TAG, "Google Play Services Not Available");
        }
    }

    public static BaseApplication getInstance() {
        return _instance;
    }
}
