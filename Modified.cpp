#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include "hls_opencv.h"

// Define image size and type
#define MAX_WIDTH  1920
#define MAX_HEIGHT 1080
#define INPUT_IMAGE "bild.png"
#define OUTPUT_IMAGE "output.png"

typedef hls::stream<ap_axiu<24, 1, 1, 1>> AXI_STREAM;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> RGB_IMAGE;

// Function for brightness correction
void BrightnessCorrection(AXI_STREAM& input_stream, AXI_STREAM& output_stream, float brightness_factor) {
#pragma HLS INTERFACE axis port=input_stream
#pragma HLS INTERFACE axis port=output_stream
#pragma HLS INTERFACE s_axilite port=brightness_factor
#pragma HLS INTERFACE s_axilite port=return

    RGB_IMAGE img_0(MAX_HEIGHT, MAX_WIDTH);
    RGB_IMAGE img_1(MAX_HEIGHT, MAX_WIDTH);

    // Convert AXI4 Stream data to hls::mat format
    hls::AXIvideo2Mat(input_stream, img_0);

    // Brightness correction
    // Loop over the image and apply brightness correction
    for (int y = 0; y < img_0.rows; y++) {
        for (int x = 0; x < img_0.cols; x++) {
            hls::Scalar<3, unsigned char> pixel = img_0.read(y * img_0.cols + x);
            for (int c = 0; c < 3; c++) {
                int temp = pixel.val[c] * brightness_factor;
                pixel.val[c] = (temp > 255) ? 255 : temp;
            }
            img_1.write(y * img_1.cols + x, pixel);
        }
    }

    // Convert hls::mat format to AXI4 Stream data
    hls::Mat2AXIvideo(img_1, output_stream);
}

// Top-level function for HLS synthesis
void top_function(AXI_STREAM& input_stream, AXI_STREAM& output_stream, float brightness_factor) {
#pragma HLS DATAFLOW
    BrightnessCorrection(input_stream, output_stream, brightness_factor);
}

int main() {
    // Note: In HLS simulation, AXI streams are connected to image files
    AXI_STREAM input_stream, output_stream;
    // Simulate input stream with an image file
    hls::imread(INPUT_IMAGE, HLS_8UC3, input_stream);

    // Call the top function
    top_function(input_stream, output_stream, 2.5);

    // Simulate output stream by writing to an image file
    hls::imwrite(OUTPUT_IMAGE, output_stream);

    return 0;
}
