package edu.harvard.cs50.fiftygram;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.view.View;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.Transformation;
import com.bumptech.glide.request.RequestOptions;

import java.io.FileDescriptor;
import java.io.IOException;

import jp.wasabeef.glide.transformations.GrayscaleTransformation;
import jp.wasabeef.glide.transformations.gpu.KuwaharaFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.PixelationFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SepiaFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SketchFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SwirlFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.ToonFilterTransformation;

public class MainActivity extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback{
    private ImageView imageView;
    private Bitmap original;
    // img stores the bitmap modified
    private Bitmap img;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Setting the layout
        setContentView(R.layout.activity_main);
        // Finding the imageView in the xml
        imageView = findViewById(R.id.image_view);
        // Checking if permission is given for saving photo
        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
    }
    // A helper function to help simplify the transformation
    public void apply(Transformation<Bitmap> filter) {
        if (original != null) {
            Glide
                    .with(this)
                    .load(original)
                    .apply(RequestOptions.bitmapTransform(filter))
                    .into(imageView);
        }
    }
    // The following functions apply the transformation and set into imageView
    public void applySepia(View view) {
        apply(new SepiaFilterTransformation());
    }

    public void applyToon(View view) {
        apply(new ToonFilterTransformation());
    }

    public void applySketch(View view) {
        apply(new SketchFilterTransformation());
    }

    public void applyKuwahara(View view) {
        apply(new KuwaharaFilterTransformation());
    }

    public void applySwirl(View view) {
        apply(new SwirlFilterTransformation());
    }

    public void applyGray(View view) {
        apply(new GrayscaleTransformation());
    }

    public void applyPixel(View view) {
        apply(new PixelationFilterTransformation());
    }
    // Choosing the photo from gallery
    public void choosePhoto(View view) {
        // Creating a new intent which links to the gallery activity in the phone
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        // Type is image
        intent.setType("image/*");
        // Start the intent
        startActivityForResult(intent, 1);
    }
    // Receiving back the data from the above intent, which is to open an image
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        // Confirming if an image is selected or a back button is pressed (which results
        // in nothing to be displayed
        if (resultCode == Activity.RESULT_OK && data != null) {
            try {
                // Getting the location of the data in disk
                Uri uri = data.getData();
                // Opening the file in the form of ParcelFileDescriptor in read mode
                // same like opening a file
                ParcelFileDescriptor parcelFileDescriptor =
                        getContentResolver().openFileDescriptor(uri, "r");
                // Then reads the file content
                FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
                // Convert the content into a bitmap
                original = BitmapFactory.decodeFileDescriptor(fileDescriptor);
                // Close the opened file
                parcelFileDescriptor.close();
                // Put the image into imageView
                imageView.setImageBitmap(original);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    // This function checks if permission is already given previously
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }
    // saving the image
    public void saveImg(View v){
        // Getting the content as drawable from imageView and convert it into bitmap
        img = ((BitmapDrawable)imageView.getDrawable()).getBitmap();
        // This saves the image into gallery
        MediaStore.Images.Media.insertImage(getApplicationContext().getContentResolver(),
                img, "Changed Picture", "A picture that is transformed using filter");
    }
}
